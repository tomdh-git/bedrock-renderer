## NEXT
DONE

# Unit U-EL8a — L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk); pack->GPU path pending

Scope (checklist item L8a, docs/RENDER_CHECKLIST.md line 344): "[ ] L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk) — pack->GPU path pending".
Do ONLY the pending part: does the pack->GPU path (texgroup_load 0x5421c90 / texload 0x58a1310 / texload_task 0x541bf00 / decode chain) contain a createTexture / slot-26 call or a GPU-handle write, via the registration-ending callee 0x18718D0 (called at 0x54227af)? SDK headers are stubs (TexturePtr.h 32B two shared_ptr; BedrockTexture.h 48B three shared_ptr; ClientTexture.h empty carrier; TextureGroup.h stub) — header layout is NOT the pending part.

Method: static analysis only; RVAs relative to image base; every claim [V] = verbatim from disassembly (cite RVA), [I] = inferred, [?] = unknown. Sizes from the instruction. One row per distinct offset, all its sites listed; meaning only where an instruction/string shows it, else '-'. No input data pasted as-is; no raw instruction lines outside table cells.

## Proven before this retry (unchanged, [V]; full 109-row field table in prior attempt oc_U-EL8a_r1.md)

Pack file bytes -> sub_1994f90 (file-bytes image loader) -> sub_764950 (allocates w*h*comp*4 via [0xF9A6FA0]) -> sub_777ed0 (PNG decoder entry, magic 0x89 at 0x777f55). texgroup_load 0x5421c90 (TextureGroup this = rcx at [rbp+0x228]): RB-tree/intrusive-list insert (head group+0x248, counter group+0x250), creates 0x20-byte handle (vtable 0xF09AA70, refcount 0x100000001), 0x80-byte texture entry, 0x70-byte list node, THEN calls undecoded callee 0x18718D0 at 0x54227af (rcx=[rbp+0x70] texture ptr, rdx=&[rbp+0x110] descriptor, r8=[rbp+0x130] owner, r9=&[rbp-0x50]). texload 0x58a1310: per-texture state, element ranges [rbx+0xE8..0xF0] and [rbx+0x160..0x168] (each 0x30 block -> texgroup append 0x5417950), stage/descriptor fields +0x178..+0x244, 0x40-byte object (vtable 0xF09B320, refcount 0x100000001), image-info reads r13+0x58..+0x88, UV matrix via [0xF9A8E18]/[0xF9A8F48] and 0xAA6580 x3. texload_task 0x541bf00: drives sub_1994F90 and other image-loader/decref calls. NONE of these contains createTexture, a slot-26 vcall ([reg+0xd0]), or a GPU-handle store.

## This retry — new angle: decode the callee 0x18718D0 (the single pending step), then chase the GPU hand-off directly

## ANSWER TABLE — pack->GPU hand-off check (every row [V] verbatim from the exe unless tagged [I])

| name | rva or offset | size | verbatim `0xRVA  instr` proof line(s) | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| callee 0x18718D0 body | 0x18718d0..0x1871ae4 | fn range | `0x18718d0  push rbp` | sub_18718d0 fully decoded (0x214 bytes): slot-array bookkeeping over texture+0x30 entries (+0x19 empty flag, +0x20 size dword, +0x28 entry ptr), zeroes out block [rsi] 16B, returns rsi; calls only sub_eea6040 via [0xF99FFA0], sub_eec59f0 0xEEC59F0, sub_eec5a10 0xEEC5A10, sub_eec5a00 0xEEC5A00, sub_7705b0 0x7705B0, sub_186dac0 0x186DAC0 — NO 0xe8143c0 createTexture, NO [reg+0xd0] slot-26 vcall, NO GPU-handle store | [V] |
| slot empty flag | entry +0x19 | 1 B | `0x1871906  cmp byte ptr [rdx+0x19],0` | slot free flag scanned in the slot-search loop (0 = empty) | [V] |
| slot size dword | entry +0x20 | 4 B | `0x1871923  cmp [rdx+0x20],r8d` | entry size dword compared against requested size r8d | [V] |
| entry pointer | entry +0x28 | 8 B | `0x18719aa  mov rdi,[rax+0x28]` | selected slot's entry pointer; [rdi+0x10] consumed at 0x18719b3 | [V] |
| out block zeroed | [rsi] | 16 B | `0x1871951  movups [rsi],xmm0` | 16-byte out descriptor block at rsi zeroed | [V] |
| callee dispatch | 0x1871ab7 | call site | `0x1871ab7  call 0x186DAC0` | tail call from 0x18718D0 to sub_186dac0 — shared_ptr / resource-location bookkeeping, CPU only | [V] |
| sub_186dac0 body | 0x186dac0..0x186dffc | fn range | `0x186dac0  push rbp` | sub_186dac0 fully decoded (0x53c bytes, 2 xrefs: one from 0x18718D0): SSO string handling (+0x48/+0x50 vs 0x10), global data_1233e1a8 ([0x1233E1A8]), decrefs via [0xF99FFA0], calls sub_58CA10/sub_71BC70/sub_76AF20/sub_9BC830 — NO createTexture, NO GPU-store | [V] |
| texgroup_load call site | 0x54227af | call site | `0x54227af  call 0x18718D0` | registration hand-off: rcx=[rbp+0x70] texture ptr, rdx=&[rbp+0x110] descriptor, r8=[rbp+0x130] owner, r9=&[rbp-0x50]; target decoded above, CPU only | [V] |
| texgroup_load tail calls | 0x54227f1 / 0x54233e1 | call site | `0x54227f1  call 0xE935700`<br>`0x54233e1  call 0x78ED0` | last call sites of texgroup_load (0x5421c90..0x54235a0); full callee list: 0xE935700, 0x5424000, 0x5424130, 0xEEC6EB0, 0x78ED0, 0x18718D0 — none is 0xe8143c0 createTexture or a [reg+0xd0] slot-26 vcall | [V] |
| texload_task calls | 0x541c229 / 0x541c126 / 0x541c60a / 0x541c615 | call site | `0x541c229  call 0x1994F90`<br>`0x541c126  call 0xE935700`<br>`0x541c60a  call 0x78ED0`<br>`0x541c615  call 0x9BC830` | texload_task (0x541bf00..0x541c6a0) call sites: image loader + decrefs — no createTexture/GPU-store | [V] |
| createTexture slot 26 | RendererContext vtable slot 26 = 0xe8143c0 | - | - | slot 26 = createTexture per BGFX_MAP.md 6k table (base 0xe8143c0; RTX thunk 0xe83d400) — naming [I]; no direct `call 0xe8143c0` anywhere in the exe (xref.py callers of 0xe8143c0: empty) [V]; no `[reg+0xd0]` vcall in any listing [V] | [V] |
| command byte-14 handler | 0xbc69487 | - | - | bgfx command byte 14 = createTexture: reads [u16 handle][u64 mem][u32 flags][u8 skip], TEX magic 0x00584554, calls [rax+0xd0] slot 26 (BGFX_MAP.md 6et — naming/mechanics [I]); xref.py callers of 0xbc69487: no callers found [V]; xref.py str "createTexture": no such string [V] | [V] |

## NEW ANGLES TRIED (all dead-ended — do not redo)

1. Decode callee 0x18718D0 at 0x54227af (the pending step): fully decoded at 0x18718d0..0x1871ae4 — CPU slot-manager bookkeeping, not the GPU hand-off. [V]
2. Follow its callee sub_186dac0 (0x186dac0..0x186dffc): CPU shared_ptr/string bookkeeping only. [V]
3. xref.py callers 0xe8143c0 → no direct callers of createTexture in the exe. [V]
4. xref.py callers 0xbc69487 → no callers of the command byte-14 createTexture handler. [V]
5. xref.py str "createTexture" → no such string in .text. [V]
6. Grep of every docs/data/listing for `call 0xe8*`, `call 0xbc*`, `call qword ptr [..+0xd0]` → none. [V]

## CLOSES?

NO — single blocking fact: the pack->GPU hand-off (createTexture via RendererContext slot 26 = 0xe8143c0, either directly as a [reg+0xd0] vcall or via bgfx command byte 14 → handler 0xbc69487, and the GPU-handle write into TexturePtr.mClientTexture / BedrockTexture) is not present anywhere in texgroup_load 0x5421c90, texload 0x58a1310, texload_task 0x541bf00, the decode chain, callee 0x18718D0 (fully decoded above) or sub_186dac0 — all are CPU-side object creation/group registration/bookkeeping. The issuance site and the handle write lie outside this unit's pending part; next unit: locate the slot-26 vcall site / command-stream producer and trace the handle into TexturePtr.

## TOOL REQUESTS

None
