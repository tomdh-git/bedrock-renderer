import sys,re
lo=int(sys.argv[1],0); hi=int(sys.argv[2],0)
sys.path.insert(0,'tools/sigs'); sys.argv=['x']
import xref
from capstone import *
M=2**64-1
def fnv1(s,h=0xcbf29ce484222325):
    for c in s: h=((h*0x100000001b3)&M)^c
    return h
names={}
for m in re.finditer(rb'(?<=\x00)[\x20-\x7e]{2,80}(?=\x00)',xref.f):
    names.setdefault(fnv1(m.group()),m.group().decode())
md=Cs(CS_ARCH_X86,CS_MODE_64)
items=[];hashes=[]
for ins in md.disasm(xref.text[lo-xref.tva:hi-xref.tva],lo):
    if ins.mnemonic=='movabs':
        v=int(ins.op_str.split(', ')[1],16); sz=8
        b=v.to_bytes(8,'little')
        if all(32<=x<127 for x in b): items.append((ins.address,b.decode()))
        elif v not in (0x100000001b3,0xcbf29ce484222325) and (v>>40)&0xffffff and not (v&0xfff==0 ): hashes.append((ins.address,v))
    elif ins.mnemonic=='mov' and re.search(r'(dword|word|byte) ptr \[',ins.op_str) and re.search(r', 0x[0-9a-f]+$',ins.op_str):
        v=int(ins.op_str.split(', ')[-1],16); sz={'dword':4,'word':2,'byte':1}[re.search(r'(dword|word|byte)',ins.op_str).group(1)]
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
        s=best[1] if best else s+p
    return s
groups=[];cur=[]
for it in items:
    if cur and it[0]-cur[-1][0]>0x30: groups.append(cur);cur=[]
    cur.append(it)
if cur: groups.append(cur)
inl={}
for g in groups:
    nm=merge([x[1] for x in g]); inl[fnv1(nm.encode())]=(nm,g[0][0])
    for k in range(len(nm)):
        pass
res=[];unk=0
for a,v in hashes:
    if v in inl: res.append((a,v,inl[v][0],'inline'))
    elif v in names: res.append((a,v,names[v],'rdata'))
    else: unk+=1
seen={}
for a,v,n,s in res: seen.setdefault((v,n,s),[]).append(a)
for (v,n,s),al in sorted(seen.items(),key=lambda x:x[1][0]): print(hex(al[0]),f'{v:#x}',repr(n),s,'x%d'%len(al))
print('unresolved',unk)
