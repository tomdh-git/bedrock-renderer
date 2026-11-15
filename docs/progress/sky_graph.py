import json, sys
p = 'graphify-out/graph.json'
d = json.load(open(p, encoding='utf-8'))
nodes = {n['id']: n for n in d['nodes']}
q = sys.argv[1].lower() if len(sys.argv) > 1 else ''
res = []
for n in d['nodes']:
    hay = (n.get('id','') + ' ' + n.get('label','')).lower()
    if q in hay:
        res.append(n)
print('matches', len(res))
for n in res[:60]:
    print(n.get('id'), '|', n.get('label'))