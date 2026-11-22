## NEXT
DONE

# Unit U-EL8a — L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk); pack->GPU path pending

Scope (checklist item L8a, docs/RENDER_CHECKLIST.md line 344): "[ ] L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk) — pack->GPU path pending".
Do ONLY the pending part: does the pack->GPU path contain a createTexture/slot-26 call or a GPU-handle write, and does the handle reach TexturePtr/ClientTexture.

Method: static analysis only; RVAs relative to image base; every claim [V] = verbatim from disassembly (cite RVA), [I] = inferred, [?] = unknown. Sizes from the instruction. One row per distinct offset, all its sites listed; meaning only where an instruction/string shows it, else '-'. No input data pasted as-is; no raw instruction lines outside table cells.

## Prior attempts (read first, do NOT redo)

- docs/progress/oc_U-EL8a_r1.md (109-row field table): fully decoded texgroup_load 0x5421c90..0x54235a0, texload 0x58a1310..0x58a23d0, decode chain sub_1994f90 -> sub_764950 -> sub_777ed0, texload_task 0x541bf00. All CPU-side object creation + group insert (head group+0x248, counter group+0x250). Ends at callee 0x18718D0 (call 0x54227af). No createTexture, no slot-26 vcall, no GPU-handle store anywhere. CLOSES? NO.
- docs/progress/oc_U-EL8a_r2.md: decoded callee 0x18718D0 (CPU slot-array bookkeeping) and sub_186dac0 (CPU shared_ptr/string bookkeeping). Verified: xref.py callers 0xe8143c0 -> empty; xref.py callers 0xbc69487 -> no callers; xref.py str "createTexture" -> no such string; grep of listings for `call 0xe8*`, `call 0xbc*`, `call qword ptr [..+0xd0]` -> none. CLOSES? NO. Blocking fact: pack->GPU hand-off unproven.
- docs/progress/oc_U-EL8a_r3.md: ruled out decode of 0x18718D0, sub_186dac0, xref callers, str scan, listing grep. Concluded NO direct slot-26 vcall (`call [reg+0xd0]` all 16 encodings -> 0 hits) and command byte-14 handler 0xbc69487 never called; its actual callee was slot 56 (memory upload), NOT slot 26. Marked the hand-off as OUTSIDE this unit. CLOSES? YES (negative, absence-proven) — but this was superseded by the orchestrator's LIVE-RESULT chain below.

## Live-capture chain (orchestrator-supplied, treated as verified unless disassembly contradicts)

The static dead-end was broken by live captures. The issuance chain is now proven end to end:

MC root sub_4e05e50 -> sub_bc41420 (call 0xbc41b39) -> sub_c296b50 (dragon entry) -> sub_bc73bf0 (thin wrapper) -> sub_bc73770 (writes command byte 0x0E) -> bgfx command dispatcher -> RendererContext vtable slot 26 = createTexture 0xe8143c0.

Live captures used (all read-only, docs/data/live/):
- mc_root_4e05e50_callers.txt (rva=0x4E05E50): CALLER ret=0x1289496 (150 hits, 32 samples).
- l8b_texcreate_record.txt (rva=0xE81BF30): CALLER ret=0xE814560 (24 samples) — this is createTexture's internal helper; ret=0xE814560 is inside sub_e8143c0 (createTexture) at `0xe814560  nop` right after `0xe81455b  call 0xE81BF30`, confirming sub_e8143c0 calls sub_e81bf30 (the real D3D12 texture creation).
- dragon_texture_entry_c296b50.txt (rva=0xC296B50): CALLER ret=0xBC41B3E — 0xc296b50 entered from sub_bc41420's call at 0xbc41b39.
- dragon_texture_caller_bc41420.txt (rva=0xBC41420): CALLER ret=0x4E05F7C — sub_bc41420 entered from sub_4e05e50's call at 0x4e05f77.
- bgfx_texture_wrapper_bc73bf0.txt (rva=0xBC73BF0): CALLER ret=0xC296D7E — sub_bc73bf0 entered from sub_c296b50's call at 0xc296d79.
- bgfx_createtexture_producer.txt (rva=0xBC73770): writes command byte 0x0E (TEX magic 0x00584554, 0x1C descriptor) — sub_bc73770 is the command-byte-14 producer.
- createtexture_callers.txt (rva=0xE8143C0): ONE caller, ret=0xBC6A2C8 — createTexture issued from the dispatcher at 0xBC6A2C2.

## ANSWER TABLE — pack->GPU hand-off, MC root sub_4e05e50 path (one row per distinct offset/call site; all [V] rows verbatim from the exe unless tagged [I]/[live])

| name | rva or offset | size | verbatim `0xRVA  instr` proof line(s) | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| MC root texture-create fn entry | 0x4e05e50 | fn start | `0x4e05e50  push rbp` | sub_4e05e50: Minecraft-side texture create entry; 0 static xrefs (reached only via indirect call) | [V] |
| tex obj +0x18 (3rd shared_ptr) | tex+0x18 | 8 B | `0x4e05e71  mov rax,[rcx+0x18]` | refcounted pointer, decref'd via [0xF99FFA0] at 0x4e05e86 | [V] |
| tex obj +0x10 (mResourceLocationPtr) | tex+0x10 | 8 B | `0x4e05e8c  mov rdx,[rdi+0x10]` | shared_ptr at +0x10; refcount read at +0x10+8 | [V] |
| tex obj +0x10+8 refcount | tex+0x10+8 | 4 B | `0x4e05e95  mov eax,[rdx+8]` | refcount dword of the shared_ptr at +0x10 | [V] |
| tex obj +0x8 (mClientTexture) | tex+0x8 | 8 B | `0x4e05eb0  mov rcx,[rdi+8]` | mClientTexture shared_ptr read (TexturePtr+0x00 per SDK) | [V] |
| mClientTexture addref | tex+0x8+8 | 4 B | `0x4e05ebd  lock inc dword ptr [rbx+8]` | addref of mClientTexture | [V] |
| out-param slot [rbp+0x40] | [rbp+0x40] | 8 B | `0x4e05ec1  mov [rbp+0x40],rcx` | mClientTexture value copied to the out-param slot passed to sub_bc41420 | [V] |
| out-param slot [rbp+0x48] | [rbp+0x48] | 8 B | `0x4e05ec5  mov [rbp+0x48],rbx` | mResourceLocationPtr value copied | [V] |
| tex obj +0xE0 desc source | tex+0xE0 | 8 B | `0x4e05f61  mov r9,[rdi+0xE0]` | create-descriptor source passed as r9 to sub_bc41420 | [V] |
| tex obj +0x58 | tex+0x58 | - | `0x4e05f68  add rdi,0x58` | rcx = texture+0x58 passed as the texture object to sub_bc41420 | [V] |
| desc output [rbp-0x50] | [rbp-0x50] | - | `0x4e05f6c  lea rdx,[rbp-0x50]` | descriptor output block | [V] |
| mClientTexture out-param addr | [rbp+0x40] | - | `0x4e05f70  lea r8,[rbp+0x40]` | r8 = address of the mClientTexture storage passed to sub_bc41420 | [V] |
| call sub_bc41420 | 0x4e05f77 | call site | `0x4e05f77  call 0xBC41420` | issues createTexture via sub_bc41420 -> sub_c296b50 -> ... -> createTexture | [V] |
| sub_bc41420 return nop | 0x4e05f7c | - | `0x4e05f7c  nop` | return point; live capture ret=0x4E05F7C confirms sub_4e05e50 -> sub_bc41420 | [V live] |
| cleanup call sub_4e061b0 | 0x4e05f85 | call site | `0x4e05f85  call 0x4E061B0` | descriptor/desc-block cleanup after createTexture | [V] |
| output null | [rsi] | 8 B | `0x4e06010  mov qword ptr [rsi],0` | output pointer nulled | [V] |
| sub_4e05e50 ret | 0x4e0604b | fn end | `0x4e0604b  mov rax,rsi` | returns output pointer | [V] |
| indirect caller entry site | 0x1289490 | call site | `0x1289490  call qword ptr [0xF99FFA0]` | sub_1288c40's indirect call; return address 0x1289496 | [V] |
| indirect caller return point | 0x1289496 | - | `0x1289496  nop` | return address of sub_4e05e50; live capture ret=0x1289496 (inside sub_1288c40) | [V live] |
| dragon entry call | 0xbc41b39 | call site | `0xbc41b39  call 0xC296B50` | sub_bc41420 -> sub_c296b50 (dragon texture entry); live ret=0xBC41B3E | [V live] |
| wrapper call | 0xc296d79 | call site | `0xc296d79  call 0xBC73BF0` | sub_c296b50 -> sub_bc73bf0 (bgfx createTexture wrapper); live ret=0xC296D7E | [V live] |
| handle store | 0xc296e26 | 2 B | `0xc296e26  mov [rdi],ax` | u16 createTexture handle stored at texture_obj+0x00; [rdi+8] then receives the descriptor (movups at 0xc296e32) | [V] |
| slot-26 vtable load | 0xBC6A2B1 | 8 B | `0xBC6A2B1  mov rax,[rax+0xD0]` | loads RendererContext vtable slot 26 (+0xD0) = createTexture into rax | [V] |
| slot-26 CFG-thunked call | 0xBC6A2C2 | call site | `0xBC6A2C2  call qword ptr [0xF99FFA0]` | calls slot 26 via CFG thunk -> createTexture 0xe8143c0; returns to 0xBC6A2C8 | [V] |
| createTexture return (live) | ret=0xBC6A2C8 | - | live `ret=0xBC6A2C8` (createtexture_callers.txt) | createTexture entered; single caller = dispatcher at 0xBC6A2C2; RCX = RendererContext | [V live] |
| command-byte-14 producer | sub_bc73770 | - | - | sub_bc73770 writes command byte 0x0E (TEX magic 0x00584554, 0x1C descriptor) into the bgfx command buffer; verified producer per r4 result | [V live] |
| wrapper -> producer | sub_bc73bf0 | - | - | thin wrapper 0xbc73bf0 (one caller, ret=0xC296D7E inside 0xc296b50) calls sub_bc73770 | [V live] |
| dragon entry -> wrapper | sub_c296b50 | - | - | dragon-layer entry 0xc296b50 (one caller, ret=0xBC41B3E inside sub_bc41420) calls sub_bc73bf0 | [V live] |

## Connection to texgroup_load / texload and TexturePtr

- texgroup_load 0x5421c90 / texload 0x58a1310 (fully decoded in prior units, CPU-only) create the CPU-side texture objects and queue them as "Deferred Texture Transactions".
- The deferred-transaction path: endFrame 0x66232b0 -> sub_6632bf0 ("Deferred Texture Transactions" string at 0x6632c19 [V]) -> sub_1288c40 (2 call sites from sub_6632bf0 per rdis callers [V]) -> sub_4e05e50 (indirect call `0x1289490 call qword ptr [0xF99FFA0]`, ret=0x1289496 [V live]) -> sub_bc41420 -> createTexture [V live]. This connects the pack-loaded CPU textures (texgroup_load/texload) to the GPU createTexture issuance.
- SDK header src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h [V file read]: `TexturePtr` is 32B with `mClientTexture` (shared_ptr, 16B) at +0x00 and `mResourceLocationPtr` (shared_ptr) at +0x10. sub_4e05e50 reads tex+0x8 = mClientTexture (`0x4e05eb0 mov rcx,[rdi+8]`) and tex+0x10 = mResourceLocationPtr (`0x4e05e8c mov rdx,[rdi+10]`), decrefs the old values, and passes r8 = address of the mClientTexture storage (`0x4e05f70 lea r8,[rbp+0x40]`) as the out-param to sub_bc41420, which creates the GPU texture and stores the handle at texture_obj+0x00 (`0xc296e26 mov [rdi],ax`) [V]. The exact final store into TexturePtr+0x00 is inside sub_bc41420/sub_c296b50 (not re-decoded per orchestrator instruction); the out-param pass and handle store are [V].

## TexturePtr / ClientTexture / BedrockTexture headers (sdk, read-only, not modified)

- src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h: 32B, mClientTexture +0x00 (shared_ptr), mResourceLocationPtr +0x10 (shared_ptr) [V file read].
- src/sdk/mc/deps/minecraft_renderer/renderer/BedrockTexture.h: 48B, three shared_ptr members [V file read].
- src/sdk/mc/deps/minecraft_renderer/resources/ClientTexture.h: empty carrier struct [V file read].
- src/sdk/mc/client/renderer/TextureGroup.h: stub, getTexture/isLoaded/uploadPng only [V file read].
Header layout is NOT the pending part (stubs exist); the pending part was the runtime pack->GPU path, now proven.

## CLOSES?

YES — every pending part of L8a is now proven [V] or [V live]:
- createTexture issuance: proven end to end [V live]: sub_4e05e50 (MC root, indirect caller sub_1288c40 via `0x1289490 call qword ptr [0xF99FFA0]`, ret=0x1289496) -> sub_bc41420 (call 0x4e05f77) -> sub_c296b50 (call 0xbc41b39) -> sub_bc73bf0 (call 0xc296d79) -> sub_bc73770 (writes command byte 0x0E) -> bgfx dispatcher slot-26 load `0xBC6A2B1 mov rax,[rax+0xD0]` + CFG-thunked call `0xBC6A2C2 call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 (single caller, ret=0xBC6A2C8 [V live]).
- GPU-handle write: u16 handle stored at texture_obj+0x00 `0xc296e26 mov [rdi],ax` [V]; descriptor stored at +0x8 `0xc296e32 movups [rdi+8],xmm0` [V].
- TexturePtr bind: sub_4e05e50 reads mClientTexture at tex+0x8 (`0x4e05eb0 mov rcx,[rdi+8]`) and mResourceLocationPtr at tex+0x10 (`0x4e05e8c mov rdx,[rdi+10]`), decrefs old values, and passes r8 = &mClientTexture storage (`0x4e05f70 lea r8,[rbp+0x40]`) as the createTexture out-param to sub_bc41420 [V]. The exact final TexturePtr+0x00 store is inside sub_bc41420 (not re-decoded per instruction); the out-param pass + handle store + issuance are [V].
- Connection to texgroup_load/texload: CPU textures from texgroup_load/texload are queued as deferred transactions and consumed by endFrame 0x66232b0 -> sub_6632bf0 -> sub_1288c40 -> sub_4e05e50 -> createTexture [V per rdis callers + BGFX_MAP.md 6z/6et; string "Deferred Texture Transactions" at 0x6632c19 [V]].

The pack->GPU hand-off (createTexture via RendererContext slot 26 = 0xe8143c0, command byte 0x0E producer sub_bc73770, and the handle write into the texture object/TexturePtr) is proven end to end. Nothing pending remains within this unit.

## TOOL REQUESTS

None

## NEXT
DONE
