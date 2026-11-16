import re, struct
for l in open('docs/data/live/light_visitor.txt', encoding='utf8'):
    l=l.rstrip('\n')
    if l.startswith('#'): continue
    m=re.match(r'(\d+)\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)', l)
    if not m: continue
    tag=int(m.group(1)); b=bytes.fromhex(m.group(2))
    if tag!=0: continue
    print("tag0 bytes 0x00-0x20:", b[0x00:0x20].hex())
    print("  byte@0x10=%#04x byte@0x14=%#04x byte@0x15=%#04x byte@0x17=%#04x" % (b[0x10],b[0x14],b[0x15],b[0x17]))
    print("  u16@0x14=%#06x" % (b[0x14]|b[0x15]<<8))
    nz=[o for o in range(0x40) if b[o]]
    print("  nonzero in 0x00-0x3f:", [hex(o) for o in nz])