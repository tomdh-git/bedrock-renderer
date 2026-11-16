import struct, sys
lines = open('docs/data/live/light_visitor.txt', encoding='utf-8').read().splitlines()
def f32(b): return struct.unpack('<f', b)[0]
def i32(b): return struct.unpack('<i', b)[0]
def u32(b): return struct.unpack('<I', b)[0]
def q(b): return struct.unpack('<Q', b)[0]
for ln in lines:
    if ln.startswith('#'): continue
    p = ln.split()
    if len(p) < 3: continue
    tag, ptr, hexstr = p[0], p[1], p[2]
    b = bytes.fromhex(hexstr)
    print('=== tag %s ptr %s len %d' % (tag, ptr, len(b)))
    for off in range(0, min(len(b), 0x300), 4):
        d = b[off:off+4]
        print('  +0x%02X %-16s f32=%-12.6g u32=%d' % (off, d.hex(), f32(d), u32(d)))