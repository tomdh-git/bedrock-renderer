"""Compares every offset and vtable index in src/sdk/OffsetProvider.h with what the reference headers say.

  python tools/sdkgen/check_offsets.py

A field named Class_mMember is a member offset, Class_function is a vtable index. Only what the SDK uses is in
OffsetProvider.h, so only that is checked: the SDK stays as small as the code that needs it.
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(__file__))
import layout as L  # noqa: E402

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
SOURCE = os.path.join(ROOT, 'src', 'sdk', 'OffsetProvider.h')


def reference_value(cls, name):
    lay = L.layout(cls)
    if not lay.known:
        return None, 'no reference header for %s' % cls
    if re.match(r'm[A-Z_]', name):
        for n, off, _, _, _ in lay.members:
            if n == name:
                return off, ''
        return None, 'no member %s' % name
    if name in lay.virtuals:
        return lay.virtuals.index(name), ''
    return None, 'no virtual %s' % name


def main():
    rows = re.findall(r'DEFINE_FIELD\((\w+?)_(\w+),\s*(0x[0-9A-Fa-f]+|\d+)\)', open(SOURCE, encoding='utf-8').read())
    differ = 0
    for cls, name, value in rows:
        ours = int(value, 0)
        ref, why = reference_value(cls, name)
        if ref is None:
            verdict = '-  (%s)' % why
        elif ref == ours:
            verdict = 'same'
        else:
            verdict = 'DIFFERENT: reference %s' % (hex(ref) if name.startswith('m') else ref)
            differ += 1
        print('%-48s %-10s %s' % (cls + '::' + name, value, verdict))
    print('%d fields, %d differ from the reference' % (len(rows), differ))


if __name__ == '__main__':
    main()
