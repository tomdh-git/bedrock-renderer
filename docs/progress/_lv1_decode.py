import re, struct

samples = {0:[], 1:[]}
for l in open('docs/data/live/light_visitor.txt', encoding='utf8'):
    l=l.rstrip('\n')
    if l.startswith('#'): continue
    m=re.match(r'(\d+)\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)', l)
    if not m:
        print("NOMATCH:", repr(l[:80])); continue
    tag=int(m.group(1)); hexs=m.group(2)
    b=bytes.fromhex(hexs)
    if tag in samples: samples[tag].append(b)

def f32(b,o): return struct.unpack('<f', b[o:o+4])[0]
def f64(b,o): return struct.unpack('<d', b[o:o+8])[0]
def u16(b,o): return b[o]|b[o+1]<<8
def u32(b,o): return b[o]|b[o+1]<<8|b[o+2]<<16|b[o+3]<<24

for tag in (0,1):
    print(f"=== TAG {tag} : {len(samples[tag])} samples ===")
    for i,b in enumerate(samples[tag]):
        print(f"  sample{i} len={len(b)}")
        if tag==0:
            print(f"    +0x00 double={f64(b,0)}  +0x08 float={f32(b,8)}  +0x10 float={f32(b,0x10)}  +0x14 word={u16(b,0x14):#06x}")
        else:
            print(f"    +0x00 floats={[f32(b,0),f32(b,4),f32(b,8),f32(b,0xc)]}  +0x10 byte={b[0x10]}  +0x14 double={f64(b,0x14)}  +0x1c float={f32(b,0x1c)}  +0x20 word={u16(b,0x20):#06x}")
        nz=[o for o in range(len(b)) if b[o]!=0]
        runs=[]
        for o in nz:
            if runs and o==runs[-1][1]+1: runs[-1][1]=o
            else: runs.append([o,o])
        print(f"    nonzero runs: {[hex(r[0])+'-'+hex(r[1]) for r in runs]}")
        # print hex of first 0x40 bytes for tag1
        if tag==1:
            print(f"    bytes[0:0x40]: {b[0:0x40].hex()}")