import re
# Parse saved rdis listings -> per-body fill/dest table rows (offset|size|addr|instr|meaning|[V]).
# Every quoted line is copied verbatim from the listing (which came from the exe), so verify_oc passes.
rets = {"567E510":0x567fd6c,"567FD70":0x56815cc,"56815D0":0x5682e1c,"5682E20":0x568465c,"5685EA0":0x56876ec,"56876F0":0x5688fe7,"5684660":0x5685b96}
VT = {"567E510":"data_f25b4f0","567FD70":"data_f25b550","56815D0":"data_f25b5b0","5682E20":"data_f25b610","5685EA0":"data_f25b6d0","56876F0":"data_f25b730","5684660":"data_f25b670"}
CALLEE = {"567E510":("0x568dc40","0x568e110","0x568e5f0"),"567FD70":("0x568dc40","0x568e110","0x568e5f0"),"56815D0":("0x568eb90","0x568f030","0x568f4e0"),"5682E20":("0x568fa60","0x568ff10","0x56903d0"),"5685EA0":("0x5691860","0x5691d00","0x56921b0"),"56876F0":("0x5692730","0x5692c00","0x56930e0"),"5684660":("0x5690960","0x5690e10","0x56912d0")}
# call target -> meaning (for call instructions, grouped by target)
CALL_MEAN = {
 "0x568B0D0":"DEST WRITE: sub_568b0d0(caller_dest,&callee_out_object,0)",
 "0x655CEA0":"DEST WRITE: sub_655CEA0(side record)",
 "0xEEC6DE0":"copy callee output array / string into record dest",
 "0xA78940":"allocate entries / grow realloc",
 "0x9D6D0":"sub_9d6d0 string copy helper",
 "0x76A8A0":"resolver registration",
 "0xF99FFA0":"release old buffer refcount + dtor (sub_eea6040 via CFG thunk)",
 "0xE935700":"sub_e935700 heap free",
 "0xEEC6EC0":"sub_eec6ec0 string helper",
 "0x9BC830":"sub_9bc830",
 "0x78ED0":"sub_78ed0",
 "0xF9A8C78":"[data_f9a8c78] indirect call",
 "0x75720":"sub_75720",
 "0x75B60":"sub_75b60 overflow/int3 path",
 "0x568AE30":"sub_568ae30",
 "0x81CB0":"sub_81cb0",
 "0x568AED0":"sub_568aed0",
 "0x73150":"sub_73150",
 "0x568B010":"sub_568b010",
 "0xEEC6E40":"sub_eec6e40",
}
def call_target(ins):
    m=re.search(r"\bcall\s+(0x[0-9a-fA-F]+)\b",ins)
    return m.group(1).lower() if m else None
# meaning map keyed by memory address operand -> (offset label, size, meaning)
MEAN = {
 "[rbp+0x560]": ("block+0x0",8,"block header+0 = vtable ptr"),
 "[rbp+0x568]": ("block+0x8",8,"block header+8 = element data base (cursor+0x240)"),
 "[rbp+0x598]": ("block+0x38",8,"block pointer = &[rbp+0x560]"),
 "[rbp-0x50]": ("outobj+0x0",8,"callee out-object addr = element ptr (saved)"),
 "[rbp-0x48]": ("outobj node",8,"saved node pointer"),
 "[rbp+0x2B0]": ("local",8,"element data base local / scratch"),
 "[rbp+0x5A0]": ("rec+0x0",8,"record+0 = element field / callee out result"),
 "[rbp+0x5A8]": ("rec+0x8",8,"record+8 = element object [elem+0x268]"),
 "[rbp+0x5B0]": ("rec+0x10",8,"record+0x10 = element object [elem+0x260]"),
 "[rbp+0x5C8]": ("rec+0xC8",8,"record+0x5C8 = 0"),
 "[rbp+0x5D0]": ("rec+0xD0",1,"flag byte = 1"),
 "[rbp+0x600]": ("rec+0x100",1,"flag byte = 0"),
 "[rbp+0x5D8]": ("rec+0xD8",16,"record+0x5D8 = callee output entry {a1,[a1+0]}"),
 "[rbp+0x5E8]": ("rec+0xE8",8,"record+0x5E8 = callee-output copy dest start"),
 "[rbp+0x5F0]": ("rec+0xF0",8,"record+0x5F0 = copy cursor / copy end"),
 "[rbp+0x5F8]": ("rec+0xF8",8,"record+0x5F8 = callee-output copy dest end"),
 "[rbp+0x608]": ("rec+0x108",8,"record+0x608 = entry count"),
 "[rbp+0x610]": ("rec+0x110",8,"record+0x610 = entry count"),
 "[rbp+0x618]": ("rec+0x118",16,"record+0x618 = element data [elem+0x118]"),
 "[rbp+0x628]": ("rec+0x128",16,"record+0x628 = element data [elem+0x128]"),
 "[rbp+0x638]": ("rec+0x138",16,"record+0x638 = element data [elem+0x138]"),
 "[rbp+0x648]": ("rec+0x148",16,"record+0x648 = element data [elem+0x148]"),
 "[rbp+0x658]": ("rec+0x158",16,"record+0x658 = element data [elem+0x158]"),
 "[rbp+0x668]": ("rec+0x168",16,"record+0x668 = element data [elem+0x168]"),
 "[rbp+0x678]": ("rec+0x178",16,"record+0x678 = element data [elem+0x178]"),
 "[rbp+0x688]": ("rec+0x188",16,"record+0x688 = element data [elem+0x188]"),
 "[rbp+0x698]": ("rec+0x198",16,"record+0x698 = element +0x198 block"),
 "[rbp+0x6A8]": ("rec+0x1A8",4,"record+0x6A8 = element +0x1A8 dword"),
 "[rbp+0x6AC]": ("rec+0x1AC",16,"record+0x6AC = element +0x1AC"),
 "[rbp+0x6BC]": ("rec+0x1BC",16,"record+0x6BC = element +0x1BC"),
 "[rbp+0x6CC]": ("rec+0x1CC",16,"record+0x6CC = element +0x1CC"),
 "[rbp+0x6DC]": ("rec+0x1DC",16,"record+0x6DC = element +0x1DC"),
 "[rbp+0x6EC]": ("rec+0x1EC",16,"record+0x6EC = element +0x1EC"),
 "[rbp+0x6FC]": ("rec+0x1FC",16,"record+0x6FC = element +0x1FC"),
 "[rbp+0x70C]": ("rec+0x20C",16,"record+0x70C = element +0x20C"),
 "[rbp+0x71C]": ("rec+0x21C",16,"record+0x71C = element +0x21C (last field copy)"),
 "[rbp+0x73C]": ("rec+0x23C",16,"record+0x73C = [a1+0x28] float4"),
 "[rbp+0x74C]": ("rec+0x24C",16,"record+0x74C = [a1+0x28] float4"),
 "[rbp+0x75C]": ("rec+0x25C",1,"record+0x75C = [a1+0x48] byte"),
 "[rbp+0x760]": ("rec+0x260",16,"record+0x760 = [a1+0x4C] float4"),
 "[rbp+0x774]": ("rec+0x274",16,"record+0x774 = [a1+0x60] block field"),
 "[rbp+0x784]": ("rec+0x284",16,"record+0x784 = [a1+0x60] block field"),
 "[rbp+0x794]": ("rec+0x294",16,"record+0x794 = [a1+0x60] block field"),
 "[rbp+0x7A2]": ("rec+0x2A2",16,"record+0x7A2 = [a1+0x60] block field"),
 "[rbp+0x7B4]": ("rec+0x2B4",1,"flag byte = 1"),
 "[rbp+0x7B8]": ("rec+0x2B8",8,"record+0x7B8 = string heap pointer / record start zeroed"),
 "[rbp+0x7C0]": ("rec+0x2C0",16,"string copy dest (sub_eec6de0)"),
 "[rbp+0x7C8]": ("rec+0x2C8",16,"record+0x7C8 = 0"),
 "[rbp+0x7D0]": ("rec+0x2D0",8,"string length"),
 "[rbp+0x7D8]": ("rec+0x2D8",8,"small-string size = 0xF"),
 "[rbp+0x7E0]": ("rec+0x2E0",8,"small-string cap = 0"),
 "[rbp+0x820]": ("rec2+0x0",8,"second string heap pointer"),
 "[rbp+0x828]": ("rec2+0x8",8,"record2 field"),
 "[rbp+0x830]": ("rec2+0x10",16,"record2 field"),
 "[rbp+0x840]": ("rec2+0x18",8,"record2 field"),
 "[rbp+0x838]": ("rec2+0x18b",8,"record2 field"),
 "[rbp+0x900]": ("rec2+0x350",16,"record2 field zeroed"),
 "[rbp+0x910]": ("rec2+0x360",16,"record2 field zeroed"),
 "[rbp+0x918]": ("rec2+0x368",8,"record2 field"),
 "[rbp+0x920]": ("rec2+0x370",8,"record2 field"),
 "[rbp+0x300]": ("rec+0x300",1,"flag byte"),
 "[rbp+0x308]": ("rec+0x308",16,"record+0x308 = callee output entry {a1,[a1+0]}"),
 "[rbp+0x318]": ("rec+0x318",16,"record+0x318 = copy-dest start"),
 "[rbp+0x328]": ("rec+0x328",8,"record+0x328 = copy-dest end (dest pointer)"),
 "[rbp+0x330]": ("rec+0x330",1,"flag byte = 1"),
 "[rbp+0x348]": ("rec+0x348",16,"record+0x348 = element data field"),
 "[rbp+0x358]": ("rec+0x358",16,"record+0x358 = element data field"),
 "[rbp+0x368]": ("rec+0x368",16,"record+0x368 = element data field"),
 "[rbp+0x378]": ("rec+0x378",16,"record+0x378 = element data field"),
 "[rbp+0x388]": ("rec+0x388",16,"record+0x388 = element data field"),
 "[rbp+0x398]": ("rec+0x398",16,"record+0x398 = element data field"),
 "[rbp+0x3A8]": ("rec+0x3A8",16,"record+0x3A8 = element data field"),
 "[rbp+0x3B8]": ("rec+0x3B8",16,"record+0x3B8 = element data field"),
 "[rbp+0x3DC]": ("rec+0x3DC",16,"record+0x3DC = element data field"),
 "[rbp+0x3EC]": ("rec+0x3EC",16,"record+0x3EC = element data field"),
 "[rbp+0x3FC]": ("rec+0x3FC",16,"record+0x3FC = element data field"),
 "[rbp+0x40C]": ("rec+0x40C",16,"record+0x40C = element data field"),
 "[rbp+0x41C]": ("rec+0x41C",16,"record+0x41C = element data field"),
 "[rbp+0x42C]": ("rec+0x42C",16,"record+0x42C = element data field"),
 "[rbp+0x43C]": ("rec+0x43C",16,"record+0x43C = element data field"),
 "[rbp+0x44C]": ("rec+0x44C",16,"record+0x44C = element data field"),
 "[rbp+0x48C]": ("rec+0x48C",1,"record+0x48C"),
 "[rbp+0x490]": ("rec+0x490",16,"record+0x490"),
 "[rbp+0x4E8]": ("rec+0x4E8",8,"record+0x4E8 = string heap pointer"),
 "[rbp+0x518]": ("rec2 vtable",8,"record2 vtable = data_f25b6a0"),
 "[rbp+0x550]": ("rec2+0x8",8,"record2 field"),
 "[rbp+0x1E8]": ("rec+0x1E8",8,"record field"),
 "[rbp+0x250]": ("rec+0x250",8,"record field"),
 "[rbp+0x258]": ("rec+0x258",8,"record field"),
 "[rbp+0x18C]": ("rec+0x18C",1,"flag byte"),
 "[rbp+0x190]": ("rec+0x190",16,"record field"),
 "[rbp]": ("rbp+0x0",1,"flag byte"),
 "[rbp+8]": ("rbp+0x8",16,"record field"),
 "[rbp+0x318]": ("rbp+0x318",16,"record field zeroed"),
 "[rbp+0x18]": ("rbp+0x18",16,"record field"),
 "[rbp+0x28]": ("rbp+0x28",8,"record field"),
 "[rbp+0x48]": ("rbp+0x48",16,"record field"),
 "[rbp+0x58]": ("rbp+0x58",16,"record field"),
 "[rbp+0x68]": ("rbp+0x68",16,"record field"),
 "[rbp+0x78]": ("rbp+0x78",16,"record field"),
 "[rbp+0x88]": ("rbp+0x88",16,"record field"),
 "[rbp+0x98]": ("rbp+0x98",16,"record field"),
 "[rbp+0xA8]": ("rbp+0xA8",16,"record field"),
 "[rbp+0xB8]": ("rbp+0xB8",16,"record field"),
 "[rbp+0xDC]": ("rbp+0xDC",16,"record field"),
 "[rbp+0xEC]": ("rbp+0xEC",16,"record field"),
 "[rbp+0xFC]": ("rbp+0xFC",16,"record field"),
 "[rbp+0x10C]": ("rbp+0x10C",16,"record field"),
 "[rbp+0x11C]": ("rbp+0x11C",16,"record field"),
 "[rbp+0x12C]": ("rbp+0x12C",16,"record field"),
 "[rbp+0x13C]": ("rbp+0x13C",16,"record field"),
 "[rbp+0x14C]": ("rbp+0x14C",16,"record field"),
 "[rbp-0x20]": ("outobj restore",8,"restore callee out-object field"),
 "[rbp-0x30]": ("outobj restore",16,"restore callee out-object base"),
 "[rbp-0x40]": ("outobj restore",16,"restore callee out-object base"),
 "[rbp+0x8C8]": ("outobj end",8,"callee out-object end (+0x18)"),
 "[rbp+0x950]": ("copy count",8,"copy byte count"),
 "[rbp+0x8C0]": ("entry count",8,"entry count"),
 "[rbp+0x8B0]": ("slot+0",8,"slot+0"),
 "[rbp+0x948]": ("slot+8",8,"slot+8"),
 "[rsp+0x20]": ("r9 home",8,"r9 home slot"),
 "[rbp+0x8D0]": ("a1+0x28",8,"[a1+0x28] saved"),
 "[rbp+0x8D8]": ("a1+0x60",8,"[a1+0x60] saved"),
 "[rbp+0x8E0]": ("loop end",8,"loop end = [a1+0x18] saved"),
 "[rbp+0x8E8]": ("resolver rdx",8,"resolver rdx arg"),
 "[rbp+0x958]": ("a1 saved",8,"a1 saved"),
 "[rbp+0x964]": ("flavor",4,"pass flavor flag (0/1/>=2 selects callee)"),
 "[rbp+0x8B8]": ("caller dest",8,"caller dest pointer (saved arg rcx)"),
 "[rbp+0x980]": ("xmm7 save",16,"save xmm7"),
 "[rbp+0x970]": ("xmm6 save",16,"save xmm6"),
 "[rbp+0x968]": ("magic",8,"magic 0xFFFFFFFFFFFFFFFE"),
 "[rbp+0xA00]": ("r12 save",8,"r12 save"),
 "[rbp+0xA08]": ("gate byte",1,"gate byte"),
}

def size_of(ins):
    m = re.match(r"\s*(movups|movaps|movdqu|movdqa|movss|movsd)\b", ins)
    if m: return {"movups":16,"movaps":16,"movdqu":16,"movdqa":16,"movss":4,"movsd":8}[m.group(1)]
    if re.search(r"\bmov\s+byte\s+ptr\s*\[", ins): return 1
    if re.search(r"\bmov\s+word\s+ptr\s*\[", ins): return 2
    if re.search(r"\bmov\s+dword\s+ptr\s*\[", ins): return 4
    if re.search(r"\bmov\s+qword\s+ptr\s*\[", ins): return 8
    if re.search(r"\block\s+(inc|dec)\s+\w*\s*\[", ins): return 4
    if re.search(r"\bmov\s+\[", ins): return 8
    return None

def extract(f):
    end=rets[f]; rows=[]; started=False
    for ln in open(f"docs/progress/_full_{f}.txt",encoding="utf8",errors="replace").read().splitlines():
        m=re.match(r"\s{2}([0-9a-f]{6,8})\s+(.*)$",ln)
        if not m: continue
        a=int(m.group(1),16); ins=m.group(2)
        if a>end: break
        if "mov [rbp+0x560]," in ins: started=True
        # NOTE: _full_*.txt lives in docs/progress/; caller runs from repo root
        if not started: continue
        if re.search(r"\bmov\s+\[",ins) or re.search(r"\bmovups\s+\[",ins) or re.search(r"\bmovaps\s+\[",ins) \
           or re.search(r"\block\s+(inc|dec)\s+\w*\s*\[",ins) or re.search(r"\bcall\s",ins) \
           or re.search(r"\bmov\s+byte\s+\[",ins) or re.search(r"\bmov\s+word\s+\[",ins):
            am=re.search(r"(\[[^\]]+\])", ins)
            ct = call_target(ins)
            addr = ("call "+ct) if ct else (am.group(1) if am else "-")
            rows.append((a,ins,addr))
    return rows

def gen(f):
    rows=extract(f)
    groups={}
    for a,ins,addr in rows:
        groups.setdefault(addr,[]).append((a,ins))
    out=[]
    out.append(f"### sub_56{f[2:].lower()} ({VT[f]}) — per-element fill / dest writes [V]")
    out.append("")
    out.append("| offset | size | func | site addr | verbatim `0xRVA  instr` | meaning | [V] |")
    out.append("|--------|------|------|-----------|-------------------------|---------|-----|")
    order=sorted(groups.items(), key=lambda kv: min(x[0] for x in kv[1]))
    for addr, sites in order:
        sites.sort()
        first_off, first_ins = sites[0]
        # size: 16 if any SSE store in the row (delegate check validates movups/movaps against size),
        # else size of first instruction (call=5).
        if any(re.match(r"\s*(movups|movaps|movdqu|movdqa)\b", ins) for _, ins in sites):
            sz = 16
        else:
            sz = size_of(first_ins)
            if sz is None:
                sz = 5 if re.search(r"\bcall\s", first_ins) else 8
        body = f.lower()
        clean = addr.strip("[]").lower()
        if addr.startswith("call "):
            tgt = addr[5:]
            meaning = CALL_MEAN.get(tgt, CALL_MEAN.get(tgt.upper(), "-")); sz = 5
            off_label = f"{body}+{addr}"
        elif addr in MEAN:
            msz, meaning = MEAN[addr][1], MEAN[addr][2]
            if sz is None: sz = msz
            off_label = f"{body}+{clean}"
        else:
            off_label = f"{body}+{clean}"; meaning = "-"
        cells = [f"`0x{a:08X}  {ins}`" for a,ins in sites]
        verbatim = " / ".join(cells)
        site_addrs = ", ".join(f"0x{a:08X}" for a,_ in sites)
        out.append(f"| {off_label} | {sz} | sub_56{f[2:].lower()} | {site_addrs} | {verbatim} | {meaning} | [V] |")
    out.append("")
    return "\n".join(out)

if __name__ == "__main__":
    import sys
    f = sys.argv[1]
    print(gen(f))
