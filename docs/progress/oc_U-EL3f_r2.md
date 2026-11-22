## NEXT
DONE

# UNIT U-EL3f — DragonFrameResources object size + constructor (L3f pending part)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred from instruction evidence, [?] = unknown / not located. Nothing invented; no offsets, sizes, or meanings beyond what instructions show.

## Basis — already closed (not re-derived in this unit)

- DragonFrameResources task vector at +0x290/+0x298/+0x2A0 = {begin, end/cursor, capacity}, 16-byte {Task*, shared_ptr control block*} elements, stride 0x10 — proven [V] in endFrame 0xe9002e0 (oc_U-EC4a.md, check OK; BGFX_MAP 6cx/1081). Every +0x290/+0x298/+0x2A0 access via a DragonFrameResources pointer is inside 0xe9002e0; no other function reads/writes them [V per prior full-exe field scans, oc_U-C4a2 / bgfx-d3d12-dragon.md].
- DragonFrameResources is embedded at owner object +0x268: the sole endFrame caller passes `rdx = [rsi+0x10] + 0x268` (DragonFrameResources&) at 0x67ca3cd [V: `67ca3bb  mov edx,0x268`; `67ca3c0  add rdx,[rsi+0x10]`]. Hence sizeof(DragonFrameResources) >= 0x2A8 (vector occupies +0x290..+0x2A8) and sizeof(owner) >= 0x268 + 0x2A8 = 0x510 [I].
- +0x08/+0x0C/+0x10/+0x18 seen via rdi are taskList/shared_ptr fields (rdi=taskList until 0xe900483), NOT DragonFrameResources fields [EC4a].

## Retry — new-angle results (this unit)

NEW ANGLE: DFR at owner+0x268, so DFR+0x290/+0x298/+0x2A0 = owner+0x4F8/+0x500/+0x508. Scanning owner-relative displacements across .pdata (`rdis fld 0x4c8/0x4f8/0x500/0x508/0x710/0x958/0x268`):

- **DFR vector proven reachable through the owner pointer**: sub_1398f0 (called from sub_139130@0x139330 and sub_14c6a0@0x14c7eb) pushes {ptr,ptr} into [rsi+0x500] via `0x139e11  add qword ptr [rsi+0x500],0x10`, tests end vs capacity via `0x139de2  cmp rdx,[rsi+0x508]`, and loads begin via `0x13a0f5  lea rcx,[rsi+0x4F8]` — the SAME vector endFrame writes at DFR+0x290/0x298/0x2A0 (endFrame: rdi=DFR [V: `0xe900483  mov rdi,[r15+0x20]`, r15=args, BGFX_MAP 6cx args+0x20 = DragonFrameResources*). Identical vector semantics at rsi+0x4F8/0x500/0x508 as at DFR+0x290/0x298/0x2A0 ⇒ DFR starts at rsi+0x268, i.e. DFR embedded at owner+0x268 [I]. BGFX_MAP 6cx line 1454 names the same Context-base offsets +0x4c8/+0x4f8/+0x710/+0x958 ⇒ owner+0x958 = DFR+0x6F0 [I].
- **Constructor located [V]**: sub_2b5670 @ 0x2b5670 is the owner constructor: `0x2b56a7  mov rdi,rcx` (this = owner), `0x2b56c0  lea rax,[0xEFF8DD0]`, `0x2b56c7  mov [rdi],rax` stores vptr 0xEFF8DD0 at object+0x00. The same function zero-inits DFR's vector slots: `0x2b58f0  movdqu [rax+0x4F8],xmm0` (16 bytes: DFR+0x290/0x298 = begin/end via owner+0x4F8/0x500) and `0x2b58f8  mov qword ptr [rax+0x508],0` (DFR+0x2A0 = capacity via owner+0x508). It also ctor-inits DFR+0x240 float (`0x2b57ee  mov [rax+0x4A8],edi`), DFR+0x244 float (`0x2b5899  mov [rax+0x4AC],edi`), DFR+0x248 qword (`0x2b58a9  mov [rax+0x4B0],rdi`, rdi=0xFFFFFFFF00000000 loaded at 0x2b589f), DFR+0x260 qword 0 (`0x2b58bc  mov qword ptr [rax+0x4C8],0`). Called post-allocation by sub_1020d10@0x1020e09, sub_6d9e390@0x6d9e4ab, sub_6db2980@0x6db2bae [V xr]. DFR itself has no separate vptr/ctor — DFR+0x00 is a plain qword field; DFR is initialized embedded by the owner ctor (no standalone DFR allocation anywhere in the exe).
- **Negative searches**: `imm 0x2A8` / `imm 0x6F8` — no DFR-sized allocation or DFR stride; `str "DragonFrame"` — only empty string f8326b0, no code refs, no symbol names. Full fld write scans of +0x268/+0x4F8/+0x958 show 500+ writers each but no instruction reveals DFR's total size.

## Field table — DragonFrameResources (DFR-relative offsets; DFR embedded at owner+0x268 [I])

| offset | size | access | verbatim `0xRVA  instr` proof sites | meaning | tag |
|---|---|---|---|---|---|
| +0x000 | 8 | R/W | `0x158026  mov rcx,[rsi+0x268]`; `0x15804c  mov qword ptr [rsi+0x268],0` | DFR+0x000 qword field at owner+0x268 (read then zeroed in sub_157fe0 dtor; sub_140960 ctor mirrors at [r8+0x268]) — object identity to endFrame's owner via matching +0x228/+0x268/+0x2A8/+0x2E8 member layout [I] | [V] |
| +0x240 | 4 | W | `0x2b57ee  mov [rax+0x4A8],edi` | DFR+0x240 float ctor-init (0.6 / 0.125 / 0.55 per branch) via owner+0x4A8 [I] | [V] |
| +0x244 | 4 | W | `0x2b5899  mov [rax+0x4AC],edi` | DFR+0x244 float ctor-init via owner+0x4AC [I] | [V] |
| +0x248 | 8 | W | `0x2b58a9  mov [rax+0x4B0],rdi` | DFR+0x248 qword = 0xFFFFFFFF00000000 via owner+0x4B0 [I] | [V] |
| +0x260 | 8 | W | `0x2b58bc  mov qword ptr [rax+0x4C8],0` | DFR+0x260 qword zeroed by ctor via owner+0x4C8 [I] | [V] |
| +0x290 | 8 | R/W | `0xe900827  sub rsi,[rdi+0x290]`; `0xe900913  mov r13,[rdi+0x290]`; `0xe9009ff  mov r13,[rdi+0x290]`; `0xe900a71  mov r13,[rdi+0x290]`; `0xe900aba  mov [rdi+0x290],r14`; `0xe900b2d  mov [rdi+0x290],r14` | vector begin — base of the 16-byte element storage; ctor zeroes begin+end via movdqu [rax+0x4F8],xmm0 at 0x2b58f0 (see ctor row) | [V] |
| +0x298 | 8 | R/W | `0xe9004aa  mov r15,[rdi+0x298]`; `0xe9004c5  add qword ptr [rdi+0x298],0x10`; `0xe90091a  mov rax,[rdi+0x298]`; `0xe90096f  mov rax,[rdi+0x298]`; `0xe900a16  mov rsi,[rdi+0x298]`; `0xe900acc  mov [rdi+0x298],rax`; `0xe900b3f  mov [rdi+0x298],rax` | vector end / write cursor; advanced by 0x10 per push; ctor zeroes end via the same movdqu at 0x2b58f0 (see ctor row) | [V] |
| +0x2A0 | 8 | R/W | `0xe9004b1  cmp r15,[rdi+0x2A0]`; `0xe900a7f  mov rdx,[rdi+0x2A0]`; `0xe900add  mov [rdi+0x2A0],rax`; `0xe900b50  mov [rdi+0x2A0],rax`; `0x2b58f8  mov qword ptr [rax+0x508],0` | vector capacity end; ctor zeroes capacity via owner+0x508 [I] | [V] |
| +0x6F0 | 8 | R/W | `0x579790  mov [rsi+0x958],rcx`; `0x570de8  mov qword ptr [rax+0x958],7` | DFR+0x6F0 qword field via owner+0x958 = Context base [I]; highest confirmed DFR offset ⇒ sizeof(DragonFrameResources) >= 0x6F8 [V]; exact total size [?] | [V] |
| ctor | - | - | `0x2b56c7  mov [rdi],rax` (rax = vtable 0xEFF8DD0 loaded by `0x2b56c0  lea rax,[0xEFF8DD0]`); zeroing: `0x2b58f0  movdqu [rax+0x4F8],xmm0`, `0x2b58f8  mov qword ptr [rax+0x508],0` | sub_2b5670 @ 0x2b5670 = owner constructor: vptr 0xEFF8DD0 at object+0x00; zero-inits DFR+0x290/0x298/0x2A0 (=object+0x4F8/0x500/0x508) [V]; called by sub_1020d10@0x1020e09, sub_6d9e390@0x6d9e4ab, sub_6db2980@0x6db2bae [V xr] | [V] |

## Size

sizeof(DragonFrameResources) >= 0x6F8 [V] (DFR+0x6F0 is a qword field, stores at 0x579790/0x570de8 via owner+0x958). Exact total size: [?] — no instruction in the exe shows the object's total size; no standalone DragonFrameResources allocation, no DragonFrameResources memset with a size constant, no DragonFrameResources stride (imm 0x2A8/0x6F8 searches negative). Proven lower bound only.

## CLOSES?

NO — constructor part closed [V]: sub_2b5670 @ 0x2b5670 (owner ctor, vptr 0xEFF8DD0 at object+0x00) zero-inits DFR's vector DFR+0x290/0x298/0x2A0 (=object+0x4F8/0x500/0x508) and ctor-inits DFR+0x240/+0x244/+0x248/+0x260. Object size part NOT closed: exact sizeof(DragonFrameResources) is unknown — highest confirmed field is DFR+0x6F0 (qword) ⇒ size >= 0x6F8 [V], exact total not shown by any instruction. Single blocking fact: no instruction in the executable reveals DragonFrameResources' total size.

## TOOL REQUESTS

- None.
