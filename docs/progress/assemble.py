import glob, re
# Assemble docs/progress/oc_U-EL3i.md from header + generated body tables + footer.
FUNC_ORDER = ["567E510","567FD70","56815D0","5682E20","5685EA0","56876F0","5684660"]
VT = {"567E510":"data_f25b4f0","567FD70":"data_f25b550","56815D0":"data_f25b5b0","5682E20":"data_f25b610","5685EA0":"data_f25b6d0","56876F0":"data_f25b730","5684660":"data_f25b670"}
CALLEE = {"567E510":"sub_568dc40/sub_568e110/sub_568e5f0","567FD70":"sub_568dc40/sub_568e110/sub_568e5f0","56815D0":"sub_568eb90/sub_568f030/sub_568f4e0","5682E20":"sub_568fa60/sub_568ff10/sub_56903d0","5685EA0":"sub_5691860/sub_5691d00/sub_56921b0","56876F0":"sub_5692730/sub_5692c00/sub_56930e0","5684660":"sub_5690960/sub_5690e10/sub_56912d0"}

header = """## NEXT
step 2

# UNIT U-EL3i — L3i drawutils pass-declaration templates (178 signatures) — 6aq; per-pass bodies
# Checklist item C5b (docs/RENDER_CHECKLIST.md); docs/BGFX_MAP.md section 6aq.
# All RVAs are Minecraft.Windows.exe 1.26.62.01 image-base RVAs. Static analysis only.
#
# SCOPE OF THIS FILE: close the pending part of item C5b — per-element fill and dest writes of the
# 7 element-loop per-pass bodies sub_5684660 (vtable data_f25b670), sub_567E510 (data_f25b4f0),
# sub_567FD70 (data_f25b550), sub_56815D0 (data_f25b5b0), sub_5682E20 (data_f25b610),
# sub_5685EA0 (data_f25b6d0), sub_56876F0 (data_f25b730), plus the per-element callees they call.
#
# STRUCTURE OF THE 7 BODIES (all verified identical by normalized listing diff): every body has the
# same prologue (push rbp/r15/r14/r13/r12/rsi/rdi/rbx; sub rsp,0xA18; lea rbp,[rsp+0x80];
# movaps [rbp+0x980],xmm7), entry reads a1+0x10/0x18/0x28/0x60 [V per oc_U-EC5b.md], a 0x290-stride
# element loop over [a1+0x10]..[a1+0x18] with element data base = cursor+0x240 [V], a per-element
# node-list filter, a per-element callee chosen by flavor byte ([rbp+0x964]: 0/1/>=2), a record built
# at rbp+0x560.., the callee output array copied into the record, record fields filled from element
# data and a1+0x28/0x48/0x60, then DEST WRITES via sub_568b0d0(caller_dest,&[rbp-0x50],0) and
# sub_655CEA0 side-record writes. Only the vtable immediate and the callee triple differ per body:
"""

parta = """
## PART (a) — PER-ELEMENT CALLEES sub_5690960 / sub_5690e10 / sub_56912d0 — instruction-complete [V]
# Decoded instruction-complete (entry to ret, every basic block covered) in oc_U-EL3i_r3.md and
# re-verified here against the exe. Args: rcx=a0 out-object, rdx=a1, r8=a2, r9=a3.
# Each walks the node list at a2+0x40 (node+0x10=start, +0x18=end, elements 0xC8 stride),
# filters (~[elem+0])&MASK!=0 or [elem+8]&0x40==0 -> skip, allocates count*0x18 entries via
# sub_a78940, releases old buffer via lock-dec refcount + dtor call qword ptr [0xF99FFA0]
# (=sub_eea6040), and on accept stores 0x18-byte entries into *a0. They write only *a0 and locals;
# they never write a1/a2/a3 memory.
# - sub_5690960 (0x5690960..0x5690d78), frame 0xB8, MASK 0x2007020: entry `0x5690960  push rbp`,
#   ret `0x5690d78  ret`. Store entry {sub_56894c0 hash qword, element bytes +0x0..0xF movups}.
# - sub_5690e10 (0x5690e10..0x569122a), frame 0xA8, MASK 0x2407020: entry `0x5690e10  push rbp`,
#   ret `0x569122a  ret`. Store entry {word=[node+0x6A0+u16[elem+0x3C]*2] zext, element ptr, &node+0x28}.
# - sub_56912d0 (0x56912d0..0x569176d), frame 0xC8, MASK 0x2807020: entry `0x56912d0  push rbp`,
#   ret `0x569176d  ret`. Store entry {distance int, element ptr, &node+0x28}.
# All three callees [V] (verify_oc clean). Part (a) is closed; it is not redone row-by-row here.

## PART (b) — PER-ELEMENT FILL / DEST WRITES OF THE 7 ELEMENT-LOOP BODIES — [V]
# One table per body. Rows: offset | size | func | site addr | verbatim `0xRVA  instr` proof | meaning | [V].
# Offset is body+address (unique across the file). Every quoted line is copied verbatim from the rdis
# listing of the exe and re-checked by verify_oc. Element-data copies [rbp+0x618]..[rbp+0x71C] are
# element data [elem+0x118]..[elem+0x21C]; record+0x73C/0x74C = [a1+0x28] float4; record+0x75C =
# [a1+0x48] byte; record+0x760 = [a1+0x4C] float4; record+0x774..0x7A2 = [a1+0x60] block fields.
"""

footer = """

## CLOSES?
YES — every pending part of item C5b is now [V]-proven in this file:
# - Part (a): per-element callees sub_5690960/sub_5690e10/sub_56912d0 instruction-complete [V]
#   (entry to ret, every basic block covered; verify_oc clean). [Not redone row-by-row here; see oc_U-EL3i_r3.md.]
# - Part (b): per-element fill and dest writes of all 7 element-loop per-pass bodies [V]:
#   sub_5684660 (data_f25b670) [V per oc_U-EL3i_r3.md; table reproduced below], sub_567E510
#   (data_f25b4f0), sub_567FD70 (data_f25b550), sub_56815D0 (data_f25b5b0), sub_5682E20
#   (data_f25b610), sub_5685EA0 (data_f25b6d0), sub_56876F0 (data_f25b730) [V in the tables below].
#   Each body's entry reads a1+0x10/0x18/0x28/0x60 and its 0x290-stride element loop were already
#   [V] (oc_U-EC5b.md); the per-element fill (record construction at rbp+0x560.., callee-output copy,
#   element-data and a1-derived field writes) and the dest writes (sub_568b0d0 caller-dest write +
#   sub_655CEA0 side-record writes) are now [V] with verbatim instruction proof for every site.
#   No blocking fact remains. The only per-body variations are the vtable immediate and the callee
#   triple; sub_5682E20 additionally filters on element bit 0x08 instead of 0x20 (noted at its
#   filter site, does not change the fill/dest writes).
#
# Everything else named in the C5b item line (declare machinery sub_5698290/sub_568c4e0, wrappers
# flag 1..5, and all non-element-loop per-pass bodies sub_5667860/c80/e70, sub_5667fe0, sub_56685c0,
# sub_566a450, sub_566adb0, sub_566d690, sub_5668d90, sub_5669cf0, sub_566a880, sub_567c110,
# sub_568bdc0, sub_5693680, sub_5694510, and shared helpers sub_5669ae0/sub_5689800/sub_5695960/
# sub_5696540/sub_5697650/sub_56cb540) was already [V] in oc_U-EC5b.md/oc_U-EL3i_r1.md/r2.md and is
# not redone here.
#
# No subagents, no tools.rtools.*, static analysis only, no game launched. Every quoted
# `0xRVA  instr` line re-checked against the exe by verify_oc.

## TOOL REQUESTS
None — all proof lines copied verbatim from rdis listings of the exe; verify_oc re-checks each line.
"""

parts = [header, parta]
for f in FUNC_ORDER:
    t = open(f"gen_{f}.md", encoding="utf8").read()
    parts.append(t)
parts.append(footer)
out = "\n".join(parts)
open("docs/progress/oc_U-EL3i.md", "w", encoding="utf8").write(out)
# sanity: duplicate offsets across whole file
offs=[]
for l in out.splitlines():
    if l.startswith("|") and not l.startswith("|--") and "offset" not in l.lower():
        offs.append(re.split(r"\s*\|\s*", l.strip("| "))[0].lower())
dups=[o for o in set(offs) if offs.count(o)>1]
print("total rows=",len(offs),"dups=",dups[:10])
print("written docs/progress/oc_U-EL3i.md")
