import struct, sys
lines = open('docs/data/live/light_visitor.txt', encoding='utf-8').read().splitlines()
def u32(b): return struct.unpack('<I', b)[0]
def i32(b): return struct.unpack('<i', b)[0]
def f32(b): return struct.unpack('<f', b)[0]
def q(b): return struct.unpack('<Q', b)[0]

samples = {}
for ln in lines:
    if ln.startswith('#'): continue
    p = ln.split()
    if len(p) < 3: continue
    tag = p[0]
    samples.setdefault(tag, []).append(bytes.fromhex(p[2]))

for tag in ['5', '2']:
    samps = samples.get(tag, [])
    print('###### TAG', tag, 'n=', len(samps))
    n = max(len(s) for s in samps)
    for off in range(0, n, 4):
        vals = []
        for s in samps:
            if off+4 <= len(s):
                vals.append(s[off:off+4])
        if not vals: continue
        uniq = set(vals)
        const = (len(uniq) == 1)
        v0 = vals[0]
        # render
        if const:
            d = v0
            print('  +0x%02X %-8s CONST f32=%-12.6g u32=%d i32=%d' % (off, d.hex(), f32(d), u32(d), i32(d)))
        else:
            show = []
            for v in list(uniq)[:6]:
                show.append('%s(f32=%.5g,u32=%d)' % (v.hex(), f32(v), u32(v)))
            print('  +0x%02X VAR   %s' % (off, ' | '.join(show)))
    print()