import re, subprocess
lines = open('docs/progress/_tmp_chunk_c04.txt','r',encoding='utf-8',errors='replace').read().splitlines()
instrs=[]
for l in lines:
    m=re.match(r'\s+([0-9a-f]{7})\s+(.*)$', l)
    if m: instrs.append((int(m.group(1),16), m.group(2).split(';')[0].strip()))
start,end=0xbca1080,0xbca2785
rng=[i for i in instrs if start<=i[0]<end]
print('n=',len(rng),'first=',hex(rng[0][0]),'last=',hex(rng[-1][0]))
calls=[i for i in rng if re.search(r'\bcall\b',i[1])]
open('docs/progress/_c03_calls.txt','w').write('\n'.join(f"0x{i[0]:x}  call {re.sub(r'^call\s+','',i[1]).split()[0]}" for i in calls)+'\n')
print('calls=',len(calls))
targets=set()
for i in calls:
    t=re.sub(r'^call\s+','',i[1])
    mm=re.match(r'qword ptr \[0x([0-9a-fA-F]+)\]',t) or re.match(r'0x([0-9a-fA-F]+)',t) or re.match(r'(r\d+)',t)
    if mm: targets.add(mm.group(1) if not mm.group(1).startswith('r') else 'reg:'+mm.group(1))
for t in sorted(targets):
    if t.startswith('reg'):
        print(t); continue
    r=subprocess.run(['grep','-i',t,'docs/data/native_boundary.tsv','docs/data/native_functions.tsv'],capture_output=True,text=True).stdout
    print(t,'||',r.strip().replace('\n',' | ')[:150])