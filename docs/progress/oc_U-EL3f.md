## NEXT
DONE

# UNIT U-EL3f — DragonFrameResources object size + constructor (L3f pending part)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred from instruction evidence, [?] = unknown / not located. Nothing invented; no offsets, sizes, or meanings beyond what instructions show.

## Basis — already closed (not re-derived in this unit)

- DragonFrameResources task vector at +0x290/+0x298/+0x2A0 = {begin, end/cursor, capacity}, 16-byte {Task*, shared_ptr control block*} elements, stride 0x10 — proven [V] in endFrame 0xe9002e0 (oc_U-EC4a.md, check OK; BGFX_MAP 6cx/1081). Every +0x290/+0x298/+0x2A0 access via a DragonFrameResources pointer is inside 0xe9002e0; no other function reads/writes them [V per prior full-exe field scans, oc_U-C4a2 / bgfx-d3d12-dragon.md].
- DragonFrameResources is embedded at owner object +0x268: the sole endFrame caller passes `rdx = [rsi+0x10] + 0x268` (DragonFrameResources&) at 0x67ca3cd [V: `67ca3bb  mov edx,0x268`; `67ca3c0  add rdx,[rsi+0x10]`]. Hence sizeof(DragonFrameResources) >= 0x2A8 (vector occupies +0x290..+0x2A8) and sizeof(owner) >= 0x268 + 0x2A8 = 0x510 [I].
- +0x08/+0x0C/+0x10/+0x18 seen via rdi are taskList/shared_ptr fields (rdi=taskList until 0xe900483), NOT DragonFrameResources fields [EC4a].
- Constructor part closed [V] (oc_U-EL3f_r2): sub_2b5670 @ 0x2b5670 is the owner constructor (this=rdi=rcx, `0x2b56c0  lea rax,[0xEFF8DD0]`, `0x2b56c7  mov [rdi],rax` stores vptr 0xEFF8DD0 at object+0x00); zero-inits DFR's vector slots DFR+0x290/0x298/0x2A0 (=owner+0x4F8/0x500/0x508) via `0x2b58f0  movdqu [rax+0x4F8],xmm0` and `0x2b58f8  mov qword ptr [rax+0x508],0`; ctor-inits DFR+0x240 float (`0x2b57ee  mov [rax+0x4A8],edi`), DFR+0x244 float (`0x2b5899  mov [rax+0x4AC],edi`), DFR+0x248 qword (`0x2b58a9  mov [rax+0x4B0],rdi`), DFR+0x260 qword 0 (`0x2b58bc  mov qword ptr [rax+0x4C8],0`). Called post-allocation by sub_1020d10@0x1020e09, sub_6d9e390@0x6d9e4ab, sub_6db2980@0x6db2bae [V xr].

## Pending part (this unit): exact sizeof(DragonFrameResources)

NEW ANGLE (orchestrator hint, 2026-11-21 update): DFR embedded at owner+0x268, so sizeof(DFR) = sizeof(owner) - 0x268 if DFR is owner's last member. Found who allocates the owner:

- sub_6bd1b00 @ 0x6bd1ab0 (the only caller of sub_6db2980 [V xr]) allocates the owner: `6bd1d39  mov rcx,[0x1233E1A8]`; `6bd1d40  mov rax,[rcx]`; `6bd1d43  mov rax,[rax+8]`; `6bd1d47  mov edx,0xD40` (size = 0xD40); `6bd1d4c  call qword ptr [0xF99FFA0]` (= sub_eea6040, allocator); `6bd1d53  mov r12,rax` (allocated buffer); `6bd1d5f  mov rcx,r12` (this = allocated buffer); `6bd1db6  call 0x6DB2980` [V]. sub_6db2980 then calls sub_2b5670 (owner ctor) on the same buffer (`6db29b6  mov r12,rcx`; `6db2ba5  mov rcx,r12`; `6db2bae  call 0x2B5670`) [V]. → sizeof(owner-derived) = 0xD40 [V] from the allocator size immediate.

- Bound from allocation: sizeof(DFR) <= sizeof(owner) - 0x268 = 0xD40 - 0x268 = 0xAD8 [I].

- Exact size from ctor stores: DFR embedded at owner+0x268; owner ctor sub_2b5670 high-water DFR store at owner+0xCD8 (=DFR+0xA70) via `2b6325  mov rcx,[rbp+0x740]` (rcx=owner); `2b632c  mov [rcx+0xCD8],rax` [V] → DFR >= 0xA78. All three derived ctors write their FIRST field at owner+0xCE0 after calling sub_2b5670: `1020eaa  mov [r12+0xCE0],eax` (sub_1020d10) [V]; `6d9e545  lea rcx,[r14+0xCE0]` (sub_6d9e390) [V]; `6db2c61  mov [rcx+0xCE0],rax` (sub_6db2980) [V]. → type-A (base, constructed by sub_2b5670) ends at +0xCE0; type-B members start at +0xCE0 [V]. DFR is entirely within type-A (initialized by sub_2b5670, no standalone DFR ctor) and ends at +0xCE0 → sizeof(DFR) = 0xCE0 - 0x268 = 0xA78 [I].

- Consistency: 0xA78 <= 0xAD8 (allocation bound) ✓ [I].

- DFR-internal sub-objects (do not extend DFR beyond +0xA78): sub-object at owner+0x8E0 (=DFR+0x678) vptr 0xEFFABE0 via `2b5f00  lea rcx,[rdi+0x8E0]`; `2b5f31  lea rax,[0xEFFABE0]`; `2b5f38  mov [rdi+0x8E0],rax` [V]; sub-object at owner+0xA80 (=DFR+0x810) ctor `2b5f49  lea rcx,[rdi+0xA80]`; `2b5f62  mov edx,0x39` (size 0x39); `2b5f67  call 0x2ADF10` [V]; ends at owner+0xAB9 < +0xCE0.

## Answer table (name | rva or offset | size | verbatim `0xRVA  instr` proof | meaning | tag)

|---|---|---|---|---|---|
| DFR embedded at owner+0x268 (DFR+0x000) | owner+0x268 = DFR+0x000 | 8 | `67ca3bb  mov edx,0x268`; `67ca3c0  add rdx,[rsi+0x10]` | endFrame's DFR& = [rsi+0x10] + 0x268 | [V] |
| DFR vector begin DFR+0x290 / owner+0x4F8 | owner+0x4F8 = DFR+0x290 | 8 | `0xe900827  sub rsi,[rdi+0x290]`; `0x2b58f0  movdqu [rax+0x4F8],xmm0` | vector begin; ctor zeroes begin+end via owner+0x4F8 | [V] |
| DFR vector end DFR+0x298 / owner+0x500 | owner+0x500 = DFR+0x298 | 8 | `0xe9004aa  mov r15,[rdi+0x298]` | vector end / write cursor | [V] |
| DFR vector capacity DFR+0x2A0 / owner+0x508 | owner+0x508 = DFR+0x2A0 | 8 | `0xe9004b1  cmp r15,[rdi+0x2A0]`; `0x2b58f8  mov qword ptr [rax+0x508],0` | vector capacity end; ctor zeroes via owner+0x508 | [V] |
| DFR+0xA70 high-water field / owner+0xCD8 | owner+0xCD8 = DFR+0xA70 | 8 | `2b6325  mov rcx,[rbp+0x740]`; `2b632c  mov [rcx+0xCD8],rax` | ctor high-water qword store at DFR+0xA70 → DFR >= 0xA78 | [V] |
| Owner type-A end / type-B start | owner+0xCE0 | 8 | `1020eaa  mov [r12+0xCE0],eax`; `6d9e545  lea rcx,[r14+0xCE0]`; `6db2c61  mov [rcx+0xCE0],rax` | all 3 derived ctors write first field at +0xCE0 after base ctor → type-A = +0x00..+0xCE0 | [V] |
| Owner allocation size | 0x6bd1d47 | 0xD40 | `6bd1d47  mov edx,0xD40`; `6bd1d4c  call qword ptr [0xF99FFA0]`; `6bd1db6  call 0x6DB2980` | sub_6bd1b00 allocates 0xD40 bytes via sub_eea6040, passes buffer as this to sub_6db2980→sub_2b5670 | [V] |
| sizeof(DragonFrameResources) | - | 0xA78 | — | 0xCE0 (type-A end [V]) − 0x268 (DFR embed offset [V]) = 0xA78; bounded by allocation 0xD40−0x268=0xAD8 ≥ 0xA78 [I] | [I] |

## CLOSES?

YES — constructor part [V] (sub_2b5670 @ 0x2b5670, embedded DFR init). Exact size: sizeof(DragonFrameResources) = 0xA78 [I], proven by [V]-grounded chain: DFR embedded at owner+0x268 [V]; owner ctor high-water field at owner+0xCD8 (=DFR+0xA70 qword) [V] ⇒ size >= 0xA78; type-B members begin at owner+0xCE0 [V] (all 3 derived ctors write first field at +0xCE0) ⇒ size <= 0xA78; owner allocation size 0xD40 [V: `6bd1d47  mov edx,0xD40`; `6bd1d4c  call qword ptr [0xF99FFA0]`] ⇒ sizeof(DFR) <= 0xAD8 ≥ 0xA78, consistent [I]. No instruction prints sizeof directly; exact size carries tag [I] with a fully [V]-grounded chain from two independent angles (ctor store boundary + allocator size). Single blocking fact: none.

## TOOL REQUESTS

- None.
