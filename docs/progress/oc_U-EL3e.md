## NEXT
step 2b — find who sets record+0x28 task-kind hash (sub_66b2b30 zeroes it, never sets hash)

# UNIT U-EL3e — L3e Task kind = FNV-1a 64 of a uniform name (UseAlphaRewrite, LightWorldSpaceDirection) — 6ad; record layout mostly mapped

Source exe: C:\Users\Atomi\AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.

## Basis (closed by prior units)

- Checklist part (1) CLOSED [V]: task-kind = FNV-1a 64 of uniform name; render_hashes.txt = FNV-1 family, task-record kinds = FNV-1a family — two hash families.
- Record+0x28 = qword task-kind hash [V] (21 cmp sites 0x66dc900..0x66de900); record+0x34 = u8 flag [V].
REFUTED: TaskList-entry == record hypothesis [V]. Record size/all fields other than +0x28/+0x34 were [?] — NOW MOSTLY MAPPED.

## Call chain (step 2 — DONE, mapped)

sub_66466e0 (visitor caller, 0 xrefs in = indirect entry) [0x66466e0..0x66468f8]
  -> 0x6646848 call sub_6646980 (visitor) with rcx=a0, rdx=&[a0+0xF0] local, r8=&local([rdx_arg])
sub_6646980 (visitor) [0x6646980..0x664fda5], size 0x9425, jump table on byte[r8+8] (tag 0-0xA)
  -> 0x66473e1 jmp sub_66d9af0 (extractor, TAIL CALL). Args to extractor: rcx=rbx=a0, rdx=saved, r8=rdi
  -> calls sub_66b2b30 at 0x6646f86, 0x6649bbd, 0x6649e53 (3 sites)
sub_66d9af0 (extractor) — calls sub_66b2b30 (1 site)

## Record layout from sub_66b2b30 [0x66b2b30..0x66b2dd8] (FULLY MAPPED) [V]

sub_66b2b30(rcx=record ptr, rdx=source; reads [rdx+0x40]->src_obj, then src_obj+0x180..0x1A8). Writes:
+0x00 u32 kind (1-8, cascade from src_obj+0x180/0x181/0x185)
+0x04 u8 = src_obj+0x184
+0x08 u32 (0/1/2 from src_obj+0x1A8)
+0x0C u8 = src_obj+0x188
+0x0D u8 computed
+0x0E u8 (=2 at start 0x66b2b38, overwritten at end 0x66b2dbb)
+0x10 u32 (0 at start, then data_f2bf190 table lookup at 0x66b2c59)
+0x14 u8 = 0
+0x18..0x33 zeroed (movups 0x18 + movups 0x24) — INCLUDES +0x28!
+0x34 u8 = FLAG (record+0x34 = u8 flag ✓ [V])
+0x38 u32, +0x3C u32, +0x40 u32, +0x44 u8, +0x48 u32, +0x4C u32, +0x50 u32
+0x54 u8 = src_obj+0x189, +0x55 u8 = src_obj+0x19C, +0x56 u8 = src_obj+0x194
Record size ~0x58 bytes. sub_66b2b30 does NOT write +0x28 (zeroed only).
Callers of sub_66b2b30 (9 xrefs in): sub_66d9af0(extractor)x1, sub_6646980(visitor)x3, sub_666aca0, sub_66b2de0, sub_66d0a00x2, sub_66e75f0.

## CRITICAL GAP

Record+0x28 (task-kind hash) is ZEROED by sub_66b2b30 but never set to a hash. EC3b fld-0x28 write scan found zero [reg+0x28] stores in .text. Need to find who sets +0x28 = FNV-1a(uniform name).
Hypothesis: extractor or a caller of sub_66b2b30 sets +0x28 AFTER sub_66b2b30 returns, possibly via larger write (e.g. [reg+0x20] movups covering 0x28) or computed address.

## NEXT ACTIONS
1. rdis xr 0x66b2b30 -> find extractor's call site, check if +0x28 set after call
2. If not, search for writes covering +0x28 (rdis fld 0x20/0x18 --w) or scan callers of sub_66b2b30
3. Once +0x28 writer found, record layout complete; optionally livemem read a record

LIVE DATA: batchActor_extractor.txt RCX=3459FFF0F00 desc ptr; RDX=149CB8, R8=149FD0. item_visitor.txt tags 10,6,7,0,1,3,2 descptrs 149FD0/148FE0/1496E0/149E40/14A148/149900/48AF6D0/49BF6D0/149A70/149310.
