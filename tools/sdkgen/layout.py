"""Computes class layouts (member byte offsets) and vtable slots from the reference SDK headers.

the reference SDK declares every data member as  ::ll::TypedStorage<alignment, size, type> mName;
in declaration order, and every virtual in vtable-slot order (verified against the
indices proven live on 1.26.51: getLocalPlayer 31, getOptions 174, grabMouse 310 ...).

  python tools/sdkgen/layout.py Actor mBuiltInComponents      # one member
  python tools/sdkgen/layout.py ClientInstance                # whole layout + vtable

The reference tree is read from REFERENCE (default C:\\Users\\Atomi\\Desktop\\the reference SDK-26.51).
"""
import os
import re
import sys

REFERENCE = os.environ.get('SDK_REFERENCE')  # the reference SDK headers the layouts are read from
assert REFERENCE, 'set SDK_REFERENCE to the reference headers'
ROOTS = [os.path.join(REFERENCE, d) for d in ('src-client', 'src', 'src-server')]

_index = None


def find_header(name):
    """Header path for class `name` (file stem match, client tree preferred)."""
    global _index
    if _index is None:
        _index = {}
        for root in ROOTS:
            for dp, _, fns in os.walk(os.path.join(root, 'mc')):
                for fn in fns:
                    if fn.endswith('.h'):
                        path = os.path.join(dp, fn)
                        cur = _index.get(fn[:-2])
                        # several reference classes share a file name (realms/Player.h vs
                        # world/actor/player/Player.h): the real one is the biggest header
                        if cur is None or os.path.getsize(path) > os.path.getsize(cur):
                            _index[fn[:-2]] = path
    return _index.get(name)


DEFINED = {'LL_PLAT_C', '_MSC_VER', '_WIN32'}  # we are the client (reference also carries the server's LL_PLAT_S layouts)


def client_only(src):
    """Drop what the client build does not compile: #ifdef/#ifndef/#else/#endif on DEFINED; any other #if keeps its
    first branch."""
    out, stack = [], []  # stack of (this branch active, some branch already taken)
    for line in src.split('\n'):
        s = line.strip()
        active = all(a for a, _ in stack)
        m = re.match(r'#\s*(ifdef|ifndef|if)\b\s*(.*)', s)
        if m:
            kind, cond = m.group(1), m.group(2).strip()
            if kind == 'ifdef':
                take = cond in DEFINED
            elif kind == 'ifndef':
                take = cond not in DEFINED
            else:
                d = re.fullmatch(r'defined\s*\(?\s*(\w+)\s*\)?', cond)
                take = (d.group(1) in DEFINED) if d else True
            stack.append((take, take))
            continue
        if re.match(r'#\s*else\b', s) and stack:
            _, taken = stack[-1]
            stack[-1] = (not taken, True)
            continue
        if re.match(r'#\s*elif\b', s) and stack:
            _, taken = stack[-1]
            stack[-1] = (False, taken)
            continue
        if re.match(r'#\s*endif\b', s) and stack:
            stack.pop()
            continue
        if active:
            out.append(line)
    return '\n'.join(out)


MEMBER = re.compile(r'::ll::TypedStorage<\s*(\d+)\s*,\s*(\d+)\s*,\s*(.+?)\s*>\s*(\w+)\s*;', re.S)  # members may span lines
CLASS = re.compile(r'^(?:class|struct)\s+(\w+)\s*(?::\s*([^{;]+))?\{', re.M)


def strip_templates(t):
    out, depth = '', 0
    for ch in t:
        if ch == '<':
            depth += 1
        elif ch == '>':
            depth = max(0, depth - 1)
        elif depth == 0:
            out += ch
    return out


def virtual_name(decl):
    """Function name of a `virtual ...(` declaration: template arguments removed first, so
    `virtual std::function<void()> getX()` yields getX, not void."""
    t = strip_templates(decl)
    m = re.search(r'(operator\s*\S+?|~?\w+)\s*\(', t)
    return m.group(1) if m else '?'


class Layout:
    def __init__(self, name):
        self.name = name
        self.path = find_header(name)
        self.bases = []
        self.members = []   # (name, offset, size, align, type)
        self.virtuals = []  # names in slot order (overloads repeat)
        self.size = 0
        self.align = 1
        self.has_vptr = False
        self.own_vptr = False  # vptr at 0, before the (non-polymorphic) bases
        self.known = self.path is not None
        if self.known:
            self._parse()

    def _parse(self):
        if self.name in FIXED:  # members reference declares without TypedStorage
            self.size, self.align = FIXED[self.name]
            self.has_vptr = True
            return
        src = client_only(open(self.path, encoding='utf-8').read())
        m = re.search(r'^(?:class|struct)\s+%s\s*(?::\s*([^{;]+))?\{' % re.escape(self.name), src, re.M)
        if not m:
            self.known = False
            return
        bases = m.group(1) or ''
        self.bases = [re.sub(r'^(public|protected|private)\s+', '', b.strip()).replace('::', '', 1) if b.strip().startswith('::') else
                      re.sub(r'^(public|protected|private)\s+', '', b.strip()) for b in re.split(r',(?![^<]*>)', bases) if b.strip()]
        self.bases = [re.sub(r'^(public|protected|private)\s+', '', b).lstrip(':') for b in self.bases]
        # the class's own body only: up to its closing brace, with nested type bodies cut out
        rest = src[m.end():]
        depth, own, i = 1, [], 0
        while i < len(rest) and depth > 0:
            ch = rest[i]
            if ch == '{':
                depth += 1
            elif ch == '}':
                depth -= 1
            elif depth == 1:
                own.append(ch)
            if depth == 1 and ch == '}':
                own.append(';')
            i += 1
        body = ''.join(own)
        # virtuals, in order (multi-line signatures included)
        lines = body.split('\n')
        for i, l in enumerate(lines):
            if re.match(r'\s*virtual\b', l):
                txt, j = l, i
                while '(' not in txt and j + 1 < len(lines):
                    j += 1
                    txt += lines[j]
                self.virtuals.append(virtual_name(txt))
        # layout: bases first (primary base provides the vptr), then own members
        offset = 0
        align = 1
        expanded = []
        for b in self.bases:
            pay = re.search(r'PayloadPacket<\s*:*(\w+)\s*>', b)  # ll::PayloadPacket<P> is Packet, then P
            expanded += ['Packet', pay.group(1)] if pay else [b]
        # MSVC: the first polymorphic base goes to offset 0 whatever its position in the list; a class with virtuals
        # and no polymorphic base puts its own vptr at 0 and the bases after it.
        sized = [b for b in expanded if layout(re.sub(r'<.*', '', b).strip()).known and layout(re.sub(r'<.*', '', b).strip()).size]
        poly = [b for b in sized if layout(re.sub(r'<.*', '', b).strip()).has_vptr]
        if poly:
            sized.remove(poly[0])
            sized.insert(0, poly[0])
            self.has_vptr = True
        elif self.virtuals:
            self.own_vptr = True
            self.has_vptr = True
            offset = 8
            align = 8
        self.bases = sized
        for b in self.bases:
            bl = layout(re.sub(r'<.*', '', b).strip())
            offset = alignup(offset, bl.align)
            offset += bl.size
            align = max(align, bl.align)
        for mm in MEMBER.finditer(body):
            a, s, t, n = int(mm.group(1)), int(mm.group(2)), mm.group(3), mm.group(4)
            offset = alignup(offset, a)
            self.members.append((n, offset, s, a, t))
            offset += s
            align = max(align, a)
        self.size = alignup(offset, align)
        self.align = align


_cache = {}
FIXED = {'Packet': (0x30, 8)}


def alignup(v, a):
    return (v + a - 1) // a * a


def layout(name):
    if name not in _cache:
        _cache[name] = Layout(name)
    return _cache[name]


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        return
    l = layout(sys.argv[1])
    if not l.known:
        print('no header for', sys.argv[1])
        return
    if len(sys.argv) > 2:
        for n, off, s, a, t in l.members:
            if n == sys.argv[2]:
                print('%s::%s = 0x%X (size %d, align %d, %s)' % (l.name, n, off, s, a, t))
        return
    print('%s: size 0x%X align %d bases %s vptr %s  (%s)' % (l.name, l.size, l.align, l.bases, l.has_vptr, l.path))
    for n, off, s, a, t in l.members:
        print('  +0x%03X  %-40s size %-4d %s' % (off, n, s, t))
    print('  virtuals:', len(l.virtuals))


if __name__ == '__main__':
    main()
