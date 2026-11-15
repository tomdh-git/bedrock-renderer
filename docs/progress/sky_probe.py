import json, sys
p = 'graphify-out/graph.json'
d = json.load(open(p, encoding='utf-8'))
print(type(d))
if isinstance(d, dict):
    print(list(d.keys())[:30])
    # find nodes
    for k in d:
        v = d[k]
        if isinstance(v, list):
            print(k, 'list len', len(v))
            if v:
                print('  sample:', json.dumps(v[0])[:400])
        elif isinstance(v, dict):
            print(k, 'dict keys', list(v.keys())[:10])
else:
    print(len(d))
    print(json.dumps(d[0])[:500])