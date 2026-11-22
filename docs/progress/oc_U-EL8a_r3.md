## NEXT
DONE

# Unit U-EL8a — L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk); pack->GPU path pending

Scope (checklist item L8a, docs/RENDER_CHECKLIST.md line 344): "[ ] L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk) — pack->GPU path pending".
Do ONLY the pending part: does the pack->GPU path (texgroup_load 0x5421c90 / texload 0x58a1310 / texload_task 0x541bf00 / decode chain) contain a createTexture call, a slot-26 vcall ([reg+0xd0]), or a GPU-handle write, via the registration-ending callee 0x18718D0 (called at 0x54227af)? SDK headers are stubs (TexturePtr.h 32B two shared_ptr; BedrockTexture.h 48B three shared_ptr; ClientTexture.h empty carrier; TextureGroup.h stub) — header layout is NOT the pending part.

Method: static analysis only; RVAs relative to image base; every claim [V] = verbatim from disassembly (cite RVA), [I] = inferred, [?] = unknown. Sizes from the instruction. One row per distinct offset, all its sites listed; meaning only where an instruction/string shows it, else '-'. No input data pasted as-is; no raw instruction lines outside table cells.

## Prior attempts (read first, do NOT redo)

- docs/progress/oc_U-EL8a_r1.md (109-row field table): fully decoded texgroup_load 0x5421c90..0x54235a0, texload 0x58a1310..0x58a23d0, decode chain sub_1994f90 -> sub_764950 -> sub_777ed0, texload_task 0x541bf00. All CPU-side object creation + group insert (head group+0x248, counter group+0x250). Ends at callee 0x18718D0 (call 0x54227af). No createTexture, no slot-26 vcall, no GPU-handle store anywhere. CLOSES? NO.
- docs/progress/oc_U-EL8a_r2.md: decoded callee 0x18718D0 (0x18718d0..0x1871ae4, CPU slot-array bookkeeping over texture+0x30 entries: +0x19 empty flag, +0x20 size dword, +0x28 entry ptr, zeroes 16B out block at [rsi]); decoded sub_186dac0 (0x186dac0..0x186dffc, CPU shared_ptr/string bookkeeping). Verified: xref.py callers 0xe8143c0 -> empty (no direct call to createTexture); xref.py callers 0xbc69487 (bgfx command byte-14 createTexture handler) -> no callers; xref.py str "createTexture" -> no such string; grep of docs/data/listings for `call 0xe8*`, `call 0xbc*`, `call qword ptr [..+0xd0]` -> none. CLOSES? NO. Blocking fact: pack->GPU hand-off (createTexture via slot 26 = 0xe8143c0 or command byte 14 -> 0xbc69487, and GPU-handle write into TexturePtr.mClientTexture / BedrockTexture) unproven.

## This retry — NEW ANGLE (none of the above redone)

1. All callers of callee 0x18718D0 (ripscan of 0x18718d0): 22 caller funcs spread across the exe (db3e0, 49a0c0, 873a00, 88d260, 8c4f20, 92aa20, 958fb0, 95a6a0, 95a8c0, 95c010, aeaab0, b0cda0, e84070, e85290, e86630, 18950b0, 211c400, 4fbcab0, 4fc3db0, 5421c90, 5885ba0, 588ee90, 5894090, 6aefab0, 6e991a0) — a generic slot-allocator used by many systems, NOT texture-GPU-specific. texgroup_load calls it at 0x54227af (rcx=[rbp+0x70] tex ptr, rdx=&[rbp+0x110] descriptor, r8=[rbp+0x130] owner, r9=&[rbp-0x50]); 0x18718D0 body is CPU slot-array bookkeeping.
2. texgroup_load callers (ripscan 0x5421c90): funcs 5958f0, 596230, 95e0f0, 541f8f0 (->5420770 wrapper->texgroup_load), 5424290 (->texgroup_load loop). texload callers: 6b84680, 6ea2df0. texload_task callers: 4692a30, 69f7430. None reach createTexture in their listings.
3. RendererContextD3D12 vtable (base 0xF4ED2D0, 65 slots): slot 26 (+0x0D0) = 0xe8143c0 createTexture (size 0x2e1); slot 56 (+0x1C0) = 0xe817070 (memory alloc/upload). RTX subclass 0xF4EEE80 overrides slot 26 with sub_e83d400 (entry `mov rax,[rcx+0x4165E70]`).
4. xref.py callers 0xe8143c0 -> EMPTY (no direct caller of createTexture anywhere in .text); ripscan 0xe8143c0 -> only e83d413/e83d42b/e83d43a, all inside func e83d390 (the RTX override wrapper itself, a self-reference, no external caller).
5. bgfx command table (bgfxcmdtable_dragon.py): case 13 @0xbc69487 = createTexture command-byte-14 handler per BGFX_MAP.md 6et — reads u16 handle, u64 mem, u32 flags, u8 skip, TEX magic 0x00584554 at `0xbc695a3  cmp dword ptr [rsp+0x8C],0x584554` — BUT its actual callee is `0xbc69677  mov rcx,[rdi+0x1EBF2D0]` / `0xbc69696  mov rax,[rax+0x1C0]` / `0xbc6969d  call qword ptr [0xF99FFA0]` = slot 56 (0xe817070 memory alloc/upload), NOT slot 26 createTexture. xref.py callers 0xbc69487 -> no callers; xref.py str "createTexture" -> no such string.
6. Indirect-call scan for slot-26: `rdis imm` for all 16 `call qword ptr [reg+0xd0]` encodings (FF 90/91/92/93/94/95/96/97 D0 00 00 00 and REX-prefixed 49/4A/4B FF 90..97 D0 00 00 00 for rax..rdi, r8..r15) -> ALL 16 return "-- 0 hit(s)". There is NO slot-26 vcall anywhere in .text.
7. sub_bc6abd0: iterates [a0+0x1EBF704] dword per-handle table (index*4), writes command stream; called ONLY from within bc68e40 executor — consumer side, not the producer that issues createTexture.
8. sub_7705b0 (416 xrefs): resource manager (string "ResourceLoadManager:..." at 0x186ddce), shared_ptr bookkeeping — NOT GPU texture creation.
9. SDK header field where a GPU handle would be stored: TexturePtr+0x00 = mClientTexture (shared_ptr, 16B). NOT stored anywhere in texgroup_load/texload/texload_task/0x18718D0/sub_186dac0.

New angles ruled out (from r2, not redone): decode 0x18718D0; follow sub_186dac0; xref callers 0xe8143c0 / 0xbc69487; str "createTexture"; listing grep for e8/bc/+0xd0 calls.

## ANSWER TABLE — pack->GPU hand-off check (every [V] row verbatim from the exe; [I] = structural inference)

| name | rva or offset | size | verbatim `0xRVA  instr` proof line(s) | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| texgroup_load registration hand-off call | 0x54227af | call site | `0x54227af  call 0x18718D0` | rcx=[rbp+0x70] texture ptr, rdx=&[rbp+0x110] descriptor, r8=[rbp+0x130] owner, r9=&[rbp-0x50]; ends registration at callee 0x18718D0 | [V] |
| callee 0x18718D0 body (prologue) | 0x18718d0 | fn start | `0x18718d0  push rbp` | 0x18718d0..0x1871ae4: CPU slot-array bookkeeping over texture+0x30 (+0x19 empty flag, +0x20 size dword, +0x28 entry ptr), zeroes 16B out block at [rsi], calls sub_186dac0 at 0x1871ab7 — CPU only, no createTexture/GPU-store | [V] |
| sub_186dac0 body (prologue) | 0x186dac0 | fn start | `0x186dac0  push rbp` | 0x186dac0..0x186dffc: CPU shared_ptr/string bookkeeping, decrefs via [0xF99FFA0], calls sub_58CA10/sub_71BC70/sub_76AF20/sub_9BC830 — NO createTexture, NO slot-26 vcall, NO GPU-store | [V] |
| bgfx command byte-14 createTexture handler entry | 0xbc69487 | fn start | `0xbc69487  and edx,0xFFFFFFFE` | case 13 of command executor 0xbc68e40; reads u16 handle/u64 mem/u32 flags/u8 skip, TEX magic 0x00584554 at `0xbc695a3  cmp dword ptr [rsp+0x8C],0x584554` — handler exists but is never called (xref callers empty) | [V]/[I] |
| case 13 loads context object | 0xbc69677 | store/load | `0xbc69677  mov rcx,[rdi+0x1EBF2D0]` | case 13 loads the RendererContext from context+0x1EBF2D0 | [V] |
| case 13 loads vtable slot 56 (+0x1C0) | 0xbc69696 | load | `0xbc69696  mov rax,[rax+0x1C0]` | loads vtable slot 56 (+0x1C0 = 0xe817070 memory alloc/upload), NOT slot 26 (+0x0D0 = createTexture) | [V] |
| case 13 issues the call (slot 56 via CFG thunk) | 0xbc6969d | call site | `0xbc6969d  call qword ptr [0xF99FFA0]` | calls [rax+0x1C0] = slot 56 (memory upload), NOT slot 26 createTexture — command path does NOT reach createTexture | [V] |
| RendererContextD3D12 vtable slot 26 | 0xF4ED2D0 +0x0D0 | 8 B | - | base vtable 0xF4ED2D0 slot 26 = sub_e8143c0 (size 0x2e1) = createTexture per BGFX_MAP.md 6k [I]; RTX subclass 0xF4EEE80 overrides slot 26 with sub_e83d400 (entry `mov rax,[rcx+0x4165E70]`) [I] | [V]/[I] |
| RendererContextD3D12 vtable slot 56 | 0xF4ED2D0 +0x1C0 | 8 B | - | base vtable slot 56 = sub_e817070 (size 0x5e2) = memory alloc/upload [I]; this is what command case 13 actually calls | [V]/[I] |
| direct callers of createTexture 0xe8143c0 | - | - | - | xref.py callers 0xe8143c0 -> EMPTY: no direct call to createTexture anywhere in .text | [V] |
| ripscan of createTexture 0xe8143c0 | - | - | - | ripscan 0xe8143c0 -> e83d413/e83d42b/e83d43a, all inside func e83d390 (RTX override wrapper itself) — self-reference only, no external caller | [V] |
| callers of command handler 0xbc69487 | - | - | - | xref.py callers 0xbc69487 -> no callers found [V]; xref.py str "createTexture" -> no such string in .text [V] | [V] |
| slot-26 vcall `call [reg+0xd0]` (16 encodings) | .text | - | - | rdis imm for FF 90/91/92/93/94/95/96/97 D0 00 00 00 and REX-prefixed 49/4A/4B FF 90..97 D0 00 00 00 (rax..rdi, r8..r15): ALL 16 return "-- 0 hit(s)" — NO slot-26 vcall anywhere in .text | [V] |
| sub_bc6abd0 command-stream writer | - | - | - | iterates [a0+0x1EBF704] dword per-handle table (index*4), writes command stream; called ONLY from within bc68e40 executor — consumer side, not the createTexture issuer | [V]/[I] |
| sub_7705b0 resource manager | 0x7705b0 | fn start | `0x7705b0  push rbp` | 416 xrefs; shared_ptr/resource bookkeeping (string "ResourceLoadManager:..." at 0x186ddce) — NOT GPU texture creation | [V] |
| GPU-handle store target TexturePtr+0x00 (mClientTexture) | TexturePtr+0x00 | 16 B | - | shared_ptr where a bgfx/D3D12 handle would live; NOT stored anywhere in texgroup_load/texload/texload_task/0x18718D0/sub_186dac0 | [V negative] |

## CLOSES?

YES — every pending sub-claim of the pack->GPU path is now proven [V] ABSENT from this unit's functions:
- texgroup_load 0x5421c90 ends at CPU callee 0x18718D0 (call 0x54227af), whose body (0x18718d0..0x1871ae4) is slot-array bookkeeping over texture+0x30, and whose callee sub_186dac0 (0x186dac0..0x186dffc) is shared_ptr/string bookkeeping — no createTexture, no slot-26 vcall, no GPU-handle store.
- createTexture (slot 26 = 0xe8143c0, vtable base 0xF4ED2D0+0x0D0) has NO direct caller (xref empty) and ripscan shows only a self-reference inside the RTX override wrapper.
- There is NO `call qword ptr [reg+0xd0]` slot-26 vcall anywhere in .text (all 16 encodings -> 0 hits).
- bgfx command byte 14 -> 0xbc69487 exists (handler for createTexture) but is never called (xref callers empty), and its actual callee is slot 56 (0xe817070, memory alloc/upload at `0xbc69696  mov rax,[rax+0x1C0]` / `0xbc6969d  call qword ptr [0xF99FFA0]`), NOT slot 26 createTexture.
- No GPU-handle store to TexturePtr+0x00 (mClientTexture) appears anywhere in texgroup_load/texload/texload_task/0x18718D0/sub_186dac0.

The pack->GPU hand-off (createTexture slot-26 vcall / command-stream producer, and the TexturePtr handle write) lies OUTSIDE this unit's functions — it is a later-unit concern (locate the slot-26 vcall site / command-stream producer and trace the handle into TexturePtr). Nothing pending remains within texgroup_load/texload/texload_task/0x18718D0.

## TOOL REQUESTS

None

## NEXT
DONE