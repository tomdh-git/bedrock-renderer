import struct, os, math

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

def is_ptr(v):
    # heap ptrs in this proc look like 0x00000346xxxxxxxx (~2e11); as a double they are subnormal/zero.
    if v==0: return False
    if v >= 0x0000010000000000 and v < 0x0000800000000000:
        fv=struct.unpack("<d", struct.pack("<Q", v))[0]
        if fv!=fv: return True            # nan bits -> pointer
        if abs(fv) < 2.2e-308: return True # subnormal/zero -> pointer
        return False
    return False

def mat(b, off):
    return [struct.unpack_from("<4f", b, off+i*0x10) for i in range(4)]

def affine(M, tol=1e-3, scale_lo=0.05, scale_hi=4096.0):
    """A model transform: rows 0-2 share one length (uniform scale), are mutually
    orthogonal, and row3 = [tx,ty,tz, 1.0]. Returns (ok, detail)."""
    r0,r1,r2,r3 = M
    w = r3[3]
    if abs(w-1.0) > tol: return False, f"row3.w={w:.4f}!=1"
    lens = [sum(x*x for x in r)**0.5 for r in (r0,r1,r2)]
    lo,hi = min(lens), max(lens)
    if lo < scale_lo or hi > scale_hi: return False, f"scale {lo:.3f}..{hi:.3f} oob"
    if hi > 0 and (hi-lo)/hi > 0.02: return False, f"non-uniform scale {lo:.3f}..{hi:.3f}"
    dots = [r0[0]*r1[0]+r0[1]*r1[1]+r0[2]*r1[2],
            r0[0]*r2[0]+r0[1]*r2[1]+r0[2]*r2[2],
            r1[0]*r2[0]+r1[1]*r2[1]+r1[2]*r2[2]]
    s = lens[0] or 1.0
    if max(abs(d)/s for d in dots) > tol: return False, f"non-orthogonal dots {[round(d,4) for d in dots]}"
    return True, f"scale={lens[0]:.3f} t=({r3[0]:.2f},{r3[1]:.2f},{r3[2]:.2f})"

def test_clouds(b):
    if len(b)<0xA8: return False,"short",None
    mesh=struct.unpack_from("<Q", b, 0x80)[0]
    A=mat(b,0x00); B=mat(b,0x40)
    okA,dA=affine(A); okB,dB=affine(B)
    col=struct.unpack_from("<4f", b, 0x88)
    colok=all(math.isfinite(c) and abs(c)<1e4 for c in col)
    ok = is_ptr(mesh) and okA and okB and colok
    ev=(f"mesh=0x{mesh:x} ptr={is_ptr(mesh)} | A: {dA} | B: {dB} | col={[round(c,3) for c in col]} finite={colok}")
    return ok, ev, None

def test_weather(b):
    if len(b)<0x12A: return False,"short",None
    mesh=struct.unpack_from("<Q", b, 0x00)[0]
    M=mat(b,0x10)
    okM,dM=affine(M)
    flat=[v for i in range(10) for v in struct.unpack_from("<4f", b, 0x88+i*0x10)]
    sane=all(math.isfinite(v) and abs(v)<1e4 for v in flat)
    i80=struct.unpack_from("<i", b, 0x80)[0]
    d84=struct.unpack_from("<I", b, 0x84)[0]
    w128=struct.unpack_from("<H", b, 0x128)[0]
    ok = is_ptr(mesh) and okM and sane
    ev=(f"mesh=0x{mesh:x} ptr={is_ptr(mesh)} | M: {dM} | i80={i80} d84=0x{d84:x} w128={w128} uniforms_sane={sane}")
    return ok, ev, None

out=[]
for f in files:
    p=os.path.join(LIVE,f+".txt")
    out.append("="*26+" "+f)
    for tag,descptr,b in parse(p):
        c,ce,_=test_clouds(b)
        w,we,_=test_weather(b)
        out.append(f"  tag={tag} descptr={descptr} CLOUDS={c} | WEATHER={w}")
        out.append(f"     C: {ce}")
        out.append(f"     W: {we}")
txt="\n".join(out)
open(r"C:\Users\Atomi\Desktop\BlueySenseV2\docs\progress\decode_u_cw_out.txt","w").write(txt)
print(txt)