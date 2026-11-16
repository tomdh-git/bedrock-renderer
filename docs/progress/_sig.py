import struct, hashlib
lines = open('docs/data/live/light_visitor.txt', encoding='utf-8').read().splitlines()
samples = {}
for ln in lines:
    if ln.startswith('#'): continue
    p = ln.split()
    if len(p) < 3: continue
    samples.setdefault(p[0], []).append((p[1], p[2]))
for tag in sorted(samples, key=lambda x: int(x)):
    print('TAG', tag, 'n=', len(samples[tag]))
    for ptr, hx in samples[tag]:
        b = bytes.fromhex(hx)
        sig = b[:0x40].hex()
        print('   ptr', ptr, 'len', len(b), 'first0x40', sig)
    # differing offsets
    bs = [bytes.fromhex(h) for _, h in samples[tag]]
    diffs = []
    n = max(len(x) for x in bs)
    for off in range(0, n, 4):
        vals = set(x[off:off+4] for x in bs if off+4 <= len(x))
        if len(vals) > 1:
            diffs.append(off)
    print('   differing 4-byte offsets:', diffs[:40])