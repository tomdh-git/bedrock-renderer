import sys,re
lo=int(sys.argv[1],0); hi=int(sys.argv[2],0)
sys.path.insert(0,'tools/sigs'); sys.argv=['x']
import xref
from capstone import *
md=Cs(CS_ARCH_X86,CS_MODE_64)
items=[]
for ins in md.disasm(xref.text[lo-xref.tva:hi-xref.tva],lo):
    if ins.mnemonic=='movabs': v=int(ins.op_str.split(', ')[1],16); sz=8
    elif ins.mnemonic=='mov' and re.search(r'(dword|word|byte) ptr \[',ins.op_str) and re.search(r', 0x[0-9a-f]+$',ins.op_str):
        v=int(ins.op_str.split(', ')[-1],16); sz={'dword':4,'word':2,'byte':1}[re.search(r'(dword|word|byte)',ins.op_str).group(1)]
    else: continue
    try:b=v.to_bytes(sz,'little')
    except Exception: continue
    if sz>=2 and all(32<=x<127 for x in b): items.append((ins.address,b.decode()))
def merge(parts):
    s=parts[0]
    for p in parts[1:]:
        best=None
        for a,b in ((s,p),(p,s)):
            for k in range(min(len(a),len(b)),0,-1):
                if a[-k:]==b[:k]: best=(k,a+b[k:]);break
            if best: break
        s = best[1] if best else s+p
    return s
groups=[];cur=[]
for it in items:
    if cur and it[0]-cur[-1][0]>0x30: groups.append(cur);cur=[]
    cur.append(it)
if cur: groups.append(cur)
seen={}
for g in groups:
    nm=merge([x[1] for x in g])
    seen.setdefault(nm,[]).append(hex(g[0][0]))
for k,v in seen.items(): print(f'{k!r:50} x{len(v)} {v[0]}')
