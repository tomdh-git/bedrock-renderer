import struct, os, math

LIVE = r"C:\Users\Atomi\Desktop\BlueySenseV2\docs\data\live"

def parse(path):
    out=[]
    for line in open(path, encoding="utf-8"):
        line=line.strip()
        if not line or line.startswith("#"): continue
        parts=line.split()
        if len(parts)<3: continue
        out.append((int(parts[0]),parts[1],bytes.fromhex(parts[2])))
    return out

def u16(b,o): return struct.unpack_from("<H",b,o)[0]
def u32(b,o): return struct.unpack_from("<I",b,o)[0]
def i32(b,o): return struct.unpack_from("<i",b,o)[0]
def f(b,o):  return struct.unpack_from("<f",b,o)[0]
def q(b,o):   return struct.unpack_from("<Q",b,o)[0]
def ptr(b,o):
    v=q(b,o)
    if v==0: return "NULL"
    if 0x0000010000000000 <= v < 0x0000800000000000:
        fv=struct.unpack("<d",struct.pack("<Q",v))[0]
        if fv!=fv or abs(fv)<2.2e-308: return f"0x{v:x}"
    return None

def dump(label, b, checks):
    print(f"  [{label}] nchecks={len(checks)}")
    for name,fmt,o in checks:
        if fmt=="ptr":
            v=ptr(b,o)
            print(f"    +0x{o:02X} {name}: {v if v else f'0x{q(b,o):x} (float-ish)'}")
        elif fmt=="u16": print(f"    +0x{o:02X} {name}: {u16(b,o)}")
        elif fmt=="u32": print(f"    +0x{o:02X} {name}: {u32(b,o)} (0x{u32(b,o):x})")
        elif fmt=="i32": print(f"    +0x{o:02X} {name}: {i32(b,o)}")
        elif fmt=="f":   print(f"    +0x{o:02X} {name}: {f(b,o):.6g}")
        elif fmt=="4f":  print(f"    +0x{o:02X} {name}: {[round(x,4) for x in struct.unpack_from('<4f',b,o)]}")
        elif fmt=="u8":  print(f"    +0x{o:02X} {name}: {b[o]}")

# ---- Atmosphere (sky tag 0) expected fields (AtmosphereDescriptionReads) ----
atm = [("mWord00","u16",0x00),("mDword04","u32",0x04),("mVec08","4f",0x08),
       ("mValue10","f",0x10),("mByteA0","u8",0xA0),("mPtrD8","ptr",0xD8),
       ("mCtrlE0","ptr",0xE0),("mVecE8","4f",0xE8),("mVecF0","4f",0xF0),
       ("mVecF8","4f",0xF8),("mVec100","4f",0x100),("mBlock10C","4f",0x10C),
       ("mVec11C","4f",0x11C),("mValue124","f",0x124),("mBlock128","4f",0x128)]

# ---- Sky (sky tag 5) expected fields (SkyDescriptionReads) ----
sky = [("mMesh","ptr",0x00),("mSkyColor08","4f",0x08),("mFogColor18","4f",0x18),
       ("mWord68","u16",0x68)]

# ---- CelestialBody (sky tag 7) expected fields ----
cb = [("mMesh","ptr",0x00),("mSunMoonColor18","4f",0x18),
       ("mFlags6C","u32",0x6C),("mSkip70","u8",0x70),("mEmissive80","f",0x80),
       ("mWord68","u16",0x68)]

# ---- Stars (sky tag 6) expected fields ----
st = [("mMesh","ptr",0x00),("mStarsColor08","4f",0x08),("mWord58","u16",0x58)]

exp = {0:("Atmosphere",atm),5:("Sky",sky),7:("CelestialBody",cb),6:("Stars",st)}

print("=== sky_visitor: verify each capture against its own tag struct ===")
for tag,descptr,b in parse(os.path.join(LIVE,"sky_visitor.txt")):
    name,checks = exp[tag]
    print(f"-- tag={tag} ({name}) descptr={descptr} len={len(b)}")
    dump(name,b,checks)

print()
print("=== Clouds signature probe: +0x80 must be a heap ptr, +0x00/+0x40 affine ===")
print("=== Weather signature probe: +0x00 heap ptr, +0x10 affine, +0x88..+0x127 ten sane vec4 ===")
for f in ["sky_visitor","light_visitor","effect_visitor","item_visitor","ui_visitor"]:
    for tag,descptr,b in parse(os.path.join(LIVE,f+".txt")):
        m80 = ptr(b,0x80)
        m00 = ptr(b,0x00)
        # clouds: mesh ptr at +0x80 AND affine at +0x00 AND +0x40
        c = m80 is not None
        w = m00 is not None
        if c or w:
            print(f"  HIT? {f} tag={tag} descptr={descptr} clouds_mesh_ptr={m80} weather_mesh_ptr={m00}")
print("(no output above = no capture has a heap pointer at the Clouds +0x80 or Weather +0x00 mesh slot)")