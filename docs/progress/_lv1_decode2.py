import re, struct

samples = {0:[], 1:[]}
for l in open('docs/data/live/light_visitor.txt', encoding='utf8'):
    l=l.rstrip('\n')
    if l.startswith('#'): continue
    m=re.match(r'(\d+)\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)', l)
    if not m: continue
    tag=int(m.group(1)); b=bytes.fromhex(m.group(2))
    if tag in samples: samples[tag].append(b)

def q(b,o): return struct.unpack('<Q', b[o:o+8])[0]
def f32(b,o): return struct.unpack('<f', b[o:o+4])[0]
def f64(b,o): return struct.unpack('<d', b[o:o+8])[0]

for tag in (0,1):
    for i,b in enumerate(samples[tag]):
        print(f"=== TAG {tag} sample{i} ===")
        for o in range(0, 0x40, 8):
            print(f"  +{o:#04x} qword={q(b,o):#018x}  f32@{o:#04x}={f32(b,o):.6g} f32@{o+4:#04x}={f32(b,o+4):.6g}")
        print(f"  +0x14 u16={b[0x14]|b[0x15]<<8:#06x}  +0x10 byte={b[0x10]}  +0x1c f32={f32(b,0x1c):.6g}  +0x20 u16={b[0x20]|b[0x21]<<8:#06x}")