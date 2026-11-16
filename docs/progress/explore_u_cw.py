import struct, os

LIVE = r"C:\Users\Atomi\Desktop\BlueySenseV2\docs\data\live"
files = ["sky_visitor","light_visitor","effect_visitor","item_visitor","ui_visitor"]

def parse(path):
    out=[]
    for line in open(path, encoding="utf-8"):
        line=line.strip()
        if not line or line.startswith("#"): continue
        parts=line.split()
        if len(parts)<3: continue
        tag=int(parts[0]); descptr=parts[1]; hexb=parts[2]
        out.append((tag,descptr,bytes.fromhex(hexb)))
    return out

def rows(b, off):
    return [struct.unpack_from("<4f", b, off+i*0x10) for i in range(4)]

def rownorm(r): return sum(x*x for x in r)**0.5

def colnorm(M, c): return sum(M[r][c]**2 for r in range(4))**0.5

def report_matrix(name, b, off):
    M = rows(b, off)
    print(f"  {name} @ +0x{off:x}:")
    for i,r in enumerate(M):
        print(f"    row{i} {['%.4f'%x for x in r]} len=%.4f" % (rownorm(r),))
    for c in range(4):
        print(f"    col{c} len=%.4f" % colnorm(M,c))

# sky tag 5 (Sky), tag 7 (CelestialBody), tag 6 (Stars) -- the Weather false-positive candidates
for f in ["sky_visitor"]:
    print("="*20, f)
    for tag,descptr,b in parse(os.path.join(LIVE,f+".txt")):
        if tag not in (5,6,7): continue
        print(f"--- tag={tag} descptr={descptr} len={len(b)}")
        # Sky/CelestialBody matrix at +0x28 ; Stars matrix at +0x18
        off = 0x28 if tag in (5,7) else 0x18
        report_matrix("ownmatrix", b, off)
        report_matrix("weather@+0x10", b, 0x10)
        report_matrix("cloudsA@+0x00", b, 0x00)
        report_matrix("cloudsB@+0x40", b, 0x40)