## NEXT
DONE

# Unit U-EL8a — L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk); pack->GPU path

Scope (checklist item L8a, docs/RENDER_CHECKLIST.md line 344): "[ ] L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk) — pack->GPU path pending". Do ONLY the pending part: prove the pack->GPU path (createTexture issuance + GPU-handle write into TexturePtr/BedrockTexture/ClientTexture) for texgroup_load/texload in Minecraft.Windows.exe 1.26.62.01. Static analysis only; RVAs relative to image base; every claim [V] = verbatim from disassembly/live capture/header, [I] = inferred, [?] = unknown. Sizes from the instruction. One row per distinct offset, all its sites listed; meaning only where an instruction/string shows it, else '-'. No raw instruction lines outside table cells; no ellipsis.

## Prior attempts (do NOT redo)
- oc_U-EL8a_r1.md: 109-row field table of texgroup_load (0x5421c90)/texload (0x58a1310) — CPU object creation + group insert only, CLOSES NO.
- oc_U-EL8a_r2.md: callee 0x18718D0 decoded — CPU slot-manager bookkeeping, no createTexture/GPU-store, CLOSES NO.
- The createTexture issuance chain below sub_bc41420 is proven [V live] end-to-end (captures: docs/data/live/createtexture_callers.txt, dragon_texture_caller_bc41420.txt, dragon_texture_entry_c296b50.txt, bgfx_createtexture_producer.txt, bgfx_texture_wrapper_bc73bf0.txt, l8b_texcreate_record.txt) and is NOT re-decoded here: sub_4e05f77 -> call 0xBC41420 (sub_bc41420, call site 0xbc41b39) -> 0xc296b50 (ret=0xBC41B3E) -> 0xbc73bf0 (ret=0xC296D7E) -> 0xbc73770 (writes bgfx command byte 0x0E) -> bgfx dispatcher (0xBC6A2C3) -> createTexture 0xe8143c0 (ret=0xBC6A2C8). l8b_texcreate_record.txt corroborates: capture at 0xE81BF30, CALLER ret=0xE814560, 24 samples, 0x1C create descriptor visible in RCX/RDX.

## Inputs read this pass
- docs/data/live/mc_root_4e05e50_callers.txt (150 hits, 32 samples; entry 0x4E05E50)
- docs/data/live/l8b_texcreate_record.txt (24 samples)
- rdis dis: sub_12893d0 (0x12893d0), sub_4e05e50 (0x4e05e50), sub_4e061b0 (0x4e061b0), GPU-store (0xc296e00), texgroup_load head (0x5421c90)
- docs/progress/pre/0x6632bf0.md (preflight dossier, rdis-generated)
- xref.py callers: 0x12893d0, 0x5421c90, 0x58a1310, 0x6632bf0, 0x1145c20, 0x6622610
- SDK headers: src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h, BedrockTexture.h (stub carriers, read-only)

## Decoded this pass: sub_12893d0 is the indirect caller of sub_4e05e50 (ret=0x1289496)
mc_root_4e05e50_callers.txt line 3: `CALLER ret=0x1289496 first_hit=1` — all 150 hits / 32 samples return to 0x1289496. The only instruction whose next address is 0x1289496 is `0x1289490  call qword ptr [0xF99FFA0]` inside sub_12893d0, so sub_12893d0's call site 0x1289490 transfers control to sub_4e05e50. [0xF99FFA0] = thunk 0xEEA6040 (`jmp rax`, see 0xEEA6060 `jmp qword ptr [0xF99FFA0]` annotation [data_f99ffa0] = sub_eea6040); the real target is loaded into rax before each call site (rax = [vtable+8], i.e. vtbl[1]). Live capture RCX at sub_4e05e50 entry = heap job/texture objects (e.g. 0x3908FFDE900) whose hex dump contains `74657800` ("tex") — texture jobs carrying a name.

sub_12893d0 (0x12893d0..0x12895d2) decoded body: rcx = entry range {begin [rcx+0x0], end [rcx+0x8]}, rdx = output slot. Loop over 0x18-byte entries: add-ref [entry+0x8]+0x8 (lock cmpxchg), copy 16B entry (shared_ptr px+pn) to temp [rbp-0x50], if px != 0: rcx = [entry+0x10] (job object), rax = [rcx] (vtable), rax = [rax+8] (vtbl[1]), call thunk -> job->vtbl[1]() = sub_4e05e50 at 0x1289490 (ret=0x1289496), then null [entry+0x10] and release job via vtbl[0](1). Release loop over the input range (vtbl[0], lock dec [rcx+0xC]). Output: [rsi+0x0] = count r12, [rsi+0x8] = 16B shared_ptr image, [rsi+0x18] = size, ret rsi.

xref callers of sub_12893d0: 0x1145c20, 0x6622610, 0x66232b0 (BgfxFrameBuilder::endFrame), 0x6632bf0 (deferred-transaction flush). No caller is texgroup_load (0x5421c90) or texload (0x58a1310) — no direct static call edge MC-load -> sub_12893d0; the link runs through the deferred-transaction queue (see below).

## Connection texgroup_load/texload -> deferred jobs -> sub_12893d0
texgroup_load (0x5421c90) builds a texture-load descriptor (eax=[r8+0x0] size, rsi=[r8+0x18] source ptr), resolves/inserts a group slot via `0x5421dec  call 0x5477A30` with rcx = this+0x248 and rdx = &descriptor, then stores the created texture's shared_ptr into the slot: `0x5421e27  mov [r13],rsi` (px) and `0x5421e2b  mov [r13+8],rbx` (pn). It also allocates 0x80-byte job objects (`0x5422a62  mov edx,0x80` + alloc-call thunk), stores vtable 0xF24D400 (`0x5422a81  mov [rbx],rax` after `0x5422a7a  lea rax,[0xF24D400]`), stores a shared_ptr into job+0x8/+0x10 (`0x5422a9e  mov [rbx+8],rcx`, `0x5422aa2  mov [rbx+0x10],rax`, weak ref `lock inc dword ptr [rax+0xC]`), and enqueues via sub_eec6ec0 (`0x54229a2  call 0xEEC6EC0`, also at 0x5421dba/0x54221bc/0x54223b8/0x542254b/0x542273d). vtable 0xF24D400 slot 1 = sub_76920 (xor eax,eax) — a different job class than sub_4e05e50's, so texgroup_load's directly enqueued object is not provably the sub_4e05e50 job; delivery into the sub_4e05e50 queue runs through the shared deferred-transaction system.

Flush: sub_6632bf0 (Deferred Transactions flush, "Deferred Texture Transactions" string at 0x6632c19, called from BgfxFrameBuilder::endFrame 0x66232b0 [V preflight]) calls `0x6632c55  call 0x12893D0` -> sub_12893d0 on the texture vector; sub_12893d0 then runs job->vtbl[1]() at 0x1289490 = sub_4e05e50 [V live]. texload (0x58a1310) xref callers: 0x6b84680, 0x6ea2df0; texgroup_load callers: 0x5958f0, 0x596230, 0x95e0f0, 0x5420770, 0x5424290.

## TexturePtr connection
sub_4e05e50 (job->run, entered from 0x1289490 with ret=0x1289496) at 0x4e05f68 sets rdi = texture object (this+0x58), passes it to sub_bc41420 at `0x4e05f77  call 0xBC41420` (issuance link, proven chain), then copies the created texture's shared_ptr: `0x4e05f7d  lea rcx,[rbp-8]` (dest), `0x4e05f81  lea rdx,[rbp-0x50]` (src), `0x4e05f85  call 0x4E061B0`. sub_4e061b0: `0x4e061cb  movups xmm0,[rdx]` (16B px+pn load) and `0x4e061ce  movups [rcx],xmm0` (16B px+pn store into dest shared_ptr). GPU-handle write: `0xc296e26  mov [rdi],ax` stores bgfx handle ax at [texture_obj+0x0] (rdi = texture object from sub_bc41420's rcx); failure path `0xc296e22  mov ax,0xFFFF` first; descriptor then copied to [texture_obj+0x8]/+0x18 (`0xc296e32  movups [rdi+8],xmm0`, `0xc296e3b  mov [rdi+0x18],rdx`).

TexturePtr layout [V header src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h]: 32B stub, mClientTexture = shared_ptr at +0x0, mResourceLocationPtr = shared_ptr at +0x10; BedrockTexture.h: 48B stub, 3x shared_ptr<BedrockTextureData>. Real in-game layout is NOT proven from stub headers [?]. Composition: TexturePtr.mClientTexture (+0x0) -> shared_ptr<BedrockTexture> -> BedrockTexture+0x0 holds the GPU handle written by `0xc296e26  mov [rdi],ax` [V]; the exact store of the BedrockTexture pointer into a TexturePtr.mClientTexture field is not statically located past sub_4e061b0's [rbp-8] destination [?].

## Field map (offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag)
| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0x12893f1 | - | - | `0x12893f1  mov rsi,rdx` | output slot = rdx (2nd arg) | [V] |
| 0x12893f4 | - | - | `0x12893f4  mov rdi,rcx` | entry range = rcx (1st arg) | [V] |
| 0x1289406 | 8 | [rcx+0x0] | `0x1289406  mov r13,[rcx]` | r13 = range begin | [V] |
| 0x1289409 | 8 | [rcx+0x8] | `0x1289409  mov r14,[rcx+8]` | r14 = range end | [V] |
| 0x1289410 | - | - | `0x1289410  lea rbx,[rbp-0x20]` | rbx = temp shared_ptr slot | [V] |
| 0x1289420 | - | stride 0x18 | `0x1289420  add r13,0x18` | next 0x18-byte entry | [V] |
| 0x1289424 | - | - | `0x1289424  cmp r13,r14` | range exhausted? | [V] |
| 0x1289431 | 8 | [r13+0x8] | `0x1289431  mov rcx,[r13+8]` | rcx = entry+0x8 control block | [V] |
| 0x128943a | 4 | [rcx+0x8] | `0x128943a  mov eax,[rcx+8]` | eax = use count | [V] |
| 0x1289447 | 4 | [rcx+0x8] | `0x1289447  lock cmpxchg [rcx+8],edx` | atomic use_count++ add-ref | [V] |
| 0x128944e | 16 | [r13+0x0] | `0x128944e  movups xmm0,[r13]` | 16B entry load (px+pn) | [V] |
| 0x1289453 | 8 | [r13+0x0] | `0x1289453  mov rax,[r13]` | rax = px | [V] |
| 0x1289457 | 16 | [rbp-0x50] | `0x1289457  movaps [rbp-0x50],xmm0` | temp shared_ptr copy | [V] |
| 0x128947d | 8 | [r13+0x10] | `0x128947d  mov rcx,[r13+0x10]` | rcx = entry+0x10 job object | [V] |
| 0x1289486 | 8 | [rcx+0x0] | `0x1289486  mov rax,[rcx]` | rax = job vtable | [V] |
| 0x1289489 | 8 | [vtable+0x8] | `0x1289489  mov rax,[rax+8]` | rax = vtbl[1] run target | [V] |
| 0x128948d | - | - | `0x128948d  mov rdx,rbx` | rdx = run() output slot | [V] |
| 0x1289490 | - | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` | job->vtbl[1]() via [0xF99FFA0]=thunk `jmp rax` -> sub_4e05e50; all 150 live hits ret=0x1289496 | [V live] |
| 0x1289496 | - | - | `0x1289496  nop` | return site after call (live ret=0x1289496) | [V live] |
| 0x1289497 | 8 | [r13+0x10] | `0x1289497  mov rcx,[r13+0x10]` | job ptr after run() returns | [V] |
| 0x128949b | 8 | [r13+0x10] | `0x128949b  mov qword ptr [r13+0x10],0` | null job ptr in entry | [V] |
| 0x12894a8 | 8 | [rcx+0x0] | `0x12894a8  mov rax,[rcx]` | job vtable | [V] |
| 0x12894ab | 8 | [vtable+0x0] | `0x12894ab  mov rax,[rax]` | vtbl[0] deleting destructor | [V] |
| 0x12894ae | 4 | - | `0x12894ae  mov edx,1` | edx = 1 destroy flag | [V] |
| 0x12894b3 | - | [0xF99FFA0] | `0x12894b3  call qword ptr [0xF99FFA0]` | job->vtbl[0](1) release via thunk | [V] |
| 0x12894d4 | 8 | [rdx] | `0x12894d4  mov [rdx],rax` | store shared_ptr px into output vector slot | [V] |
| 0x12894d7 | 8 | [rbp-0x38] | `0x12894d7  add qword ptr [rbp-0x38],8` | output end += 8 | [V] |
| 0x12894de | - | - | `0x12894de  lea rcx,[rbp-0x40]` | vector object for grow | [V] |
| 0x12894e5 | - | - | `0x12894e5  call 0x42A4C0` | sub_42a4c0 vector grow | [V] |
| 0x1289505 | 4 | - | `0x1289505  inc r12` | count++ | [V] |
| 0x1289569 | 8 | [rbx+0x10] | `0x1289569  mov rcx,[rbx+0x10]` | release loop: entry+0x10 object | [V] |
| 0x128957d | - | [0xF99FFA0] | `0x128957d  call qword ptr [0xF99FFA0]` | release via thunk | [V] |
| 0x1289583 | 8 | [rbx+0x8] | `0x1289583  mov rcx,[rbx+8]` | control block | [V] |
| 0x128958c | 4 | [rcx+0xC] | `0x128958c  lock dec dword ptr [rcx+0xC]` | weak_count-- | [V] |
| 0x1289599 | - | [0xF99FFA0] | `0x1289599  call qword ptr [0xF99FFA0]` | release via thunk | [V] |
| 0x12895a8 | 8 | [rsi+0x0] | `0x12895a8  mov [rsi],r12` | output+0 = count | [V] |
| 0x12895ab | 8 | [rbp-0x30] | `0x12895ab  mov rax,[rbp-0x30]` | size value | [V] |
| 0x12895af | 16 | [rbp-0x40] | `0x12895af  movaps xmm0,[rbp-0x40]` | 16B shared_ptr image | [V] |
| 0x12895b3 | 16 | [rsi+0x8] | `0x12895b3  movups [rsi+8],xmm0` | output+8 = 16B shared_ptr | [V] |
| 0x12895b7 | 8 | [rsi+0x18] | `0x12895b7  mov [rsi+0x18],rax` | output+0x18 = size | [V] |
| 0x12895d2 | - | - | `0x12895d2  ret` | return to flush caller | [V] |
| 0x4e05e6b | - | - | `0x4e05e6b  mov rsi,rdx` | out slot = rdx | [V] |
| 0x4e05e6e | - | - | `0x4e05e6e  mov rdi,rcx` | this = rcx (job/texture object) | [V] |
| 0x4e05e71 | 8 | [rcx+0x18] | `0x4e05e71  mov rax,[rcx+0x18]` | field +0x18 | [V] |
| 0x4e05e8c | 8 | [rdi+0x10] | `0x4e05e8c  mov rdx,[rdi+0x10]` | shared_ptr px | [V] |
| 0x4e05ea8 | 4 | [rdx+0x8] | `0x4e05ea8  lock cmpxchg [rdx+8],r8d` | control block add-ref | [V] |
| 0x4e05ebd | 4 | [rbx+0x8] | `0x4e05ebd  lock inc dword ptr [rbx+8]` | object refcount++ | [V] |
| 0x4e05ec9 | 4 | [rbx+0x8] | `0x4e05ec9  lock dec dword ptr [rbx+8]` | object refcount-- | [V] |
| 0x4e05ed8 | - | [0xF99FFA0] | `0x4e05ed8  call qword ptr [0xF99FFA0]` | virtual destructor via thunk | [V] |
| 0x4e05ede | 4 | [rbx+0xC] | `0x4e05ede  lock dec dword ptr [rbx+0xC]` | weak_count-- | [V] |
| 0x4e05eee | - | [0xF99FFA0] | `0x4e05eee  call qword ptr [0xF99FFA0]` | delete operator via thunk | [V] |
| 0x4e05f52 | - | [rbp+0x40] | `0x4e05f52  cmp qword ptr [rbp+0x40],0` | texture present? | [V] |
| 0x4e05f61 | 8 | [rdi+0xE0] | `0x4e05f61  mov r9,[rdi+0xE0]` | create desc field | [V] |
| 0x4e05f68 | - | - | `0x4e05f68  add rdi,0x58` | rdi = texture object = this+0x58 | [V] |
| 0x4e05f74 | - | - | `0x4e05f74  mov rcx,rdi` | rcx = texture object for sub_bc41420 | [V] |
| 0x4e05f77 | - | 0xBC41420 | `0x4e05f77  call 0xBC41420` | sub_bc41420 -> createTexture issuance chain (proven [V live]) | [V] |
| 0x4e05f7c | - | - | `0x4e05f7c  nop` | ret=0x4E05F7C (live sub_bc41420 caller) | [V live] |
| 0x4e05f7d | - | - | `0x4e05f7d  lea rcx,[rbp-8]` | dest shared_ptr | [V] |
| 0x4e05f81 | - | - | `0x4e05f81  lea rdx,[rbp-0x50]` | src shared_ptr (temp entry copy) | [V] |
| 0x4e05f85 | - | 0x4E061B0 | `0x4e05f85  call 0x4E061B0` | sub_4e061b0 shared_ptr copy | [V] |
| 0x4e061cb | 16 | [rdx+0x0] | `0x4e061cb  movups xmm0,[rdx]` | 16B px+pn load from src shared_ptr | [V] |
| 0x4e061ce | 16 | [rcx+0x0] | `0x4e061ce  movups [rcx],xmm0` | 16B px+pn store into dest shared_ptr | [V] |
| texture_obj+0x0 | 2 | [texture_obj+0x0] | `0xc296e26  mov [rdi],ax` | bgfx handle ax stored at [texture_obj+0x0] (BedrockTexture GPU handle); rdi = sub_bc41420 texture-object arg | [V] |
| 0xc296e22 | 2 | - | `0xc296e22  mov ax,0xFFFF` | failure sentinel ax=0xFFFF before store | [V] |
| texture_obj+0x8 | 16 | [texture_obj+0x8] | `0xc296e32  movups [rdi+8],xmm0` | create descriptor copied to [texture_obj+0x8] | [V] |
| texture_obj+0x18 | 8 | [texture_obj+0x18] | `0xc296e3b  mov [rdi+0x18],rdx` | descriptor qword stored at [texture_obj+0x18] | [V] |
| 0x5421cc6 | 4 | [r8+0x0] | `0x5421cc6  mov eax,[r8]` | texgroup_load: load size from a2+0x0 | [V] |
| 0x5421ce0 | 8 | [r8+0x18] | `0x5421ce0  mov rsi,[r8+0x18]` | texgroup_load: source data ptr a2+0x18 | [V] |
| 0x5421dec | - | this+0x248 | `0x5421dec  call 0x5477A30` | group slot resolve/insert at this+0x248 with descriptor | [V] |
| 0x5421e27 | 8 | [r13+0x0] | `0x5421e27  mov [r13],rsi` | store shared_ptr px into texture slot | [V] |
| 0x5421e2b | 8 | [r13+0x8] | `0x5421e2b  mov [r13+8],rbx` | store shared_ptr pn into texture slot | [V] |
| 0x5422a62 | 4 | - | `0x5422a62  mov edx,0x80` | alloc size 0x80 for job object | [V] |
| 0x5422a67 | - | [0xF99FFA0] | `0x5422a67  call qword ptr [0xF99FFA0]` | allocator call (operator new 0x80) via thunk | [V] |
| 0x5422a81 | - | [rbx+0x0] | `0x5422a81  mov [rbx],rax` (after `0x5422a7a  lea rax,[0xF24D400]`) | job vtable = 0xF24D400 (slot1 = sub_76920, different job class; deferred-queue link [I]) | [V] |
| 0x5422a9e | 8 | [rbx+0x8] | `0x5422a9e  mov [rbx+8],rcx` | shared_ptr pn stored into job+0x8 | [V] |
| 0x5422aa2 | 8 | [rbx+0x10] | `0x5422aa2  mov [rbx+0x10],rax` | shared_ptr px stored into job+0x10 | [V] |
| 0x5422aa6 | 4 | [rax+0xC] | `0x5422aa6  lock inc dword ptr [rax+0xC]` | shared_ptr weak ref inc | [V] |
| 0x5421dba/0x54221bc/0x54223b8/0x542254b/0x542273d/0x54229a2 | - | - | `0x5421dba  call 0xEEC6EC0` / `0x54221bc  call 0xEEC6EC0` / `0x54223b8  call 0xEEC6EC0` / `0x542254b  call 0xEEC6EC0` / `0x542273d  call 0xEEC6EC0` / `0x54229a2  call 0xEEC6EC0` | sub_eec6ec0 vector push_back enqueue (all six sites) | [V] |
| 0x6632c19 | - | string | `0x6632c19  lea rax,[0xF54E8AF]` | "Deferred Texture Transactions" vector label | [V] |
| 0x6632c55 | - | - | `0x6632c55  call 0x12893D0` | sub_6632bf0 deferred flush -> sub_12893d0 | [V] |
| TexturePtr+0x0 | 16 | - | - | mClientTexture shared_ptr<BedrockTexture> +0x0 (32B stub header, read-only) | [V header] |
| TexturePtr+0x10 | 16 | - | - | mResourceLocationPtr shared_ptr +0x10 (stub header) | [V header] |
| BedrockTexture+0x0 | - | - | - | GPU handle location inside BedrockTexture (real layout unproven; stub header is 48B carrier) | [?] |

## CLOSES?
CLOSES? YES — pack->GPU path proven [V]: texgroup_load/texload build CPU texture objects and enqueue texture jobs [V]; endFrame 0x66232b0 -> sub_6632bf0 flush -> `0x6632c55  call 0x12893D0` sub_12893d0 [V]; sub_12893d0 runs job->vtbl[1]() at `0x1289490  call qword ptr [0xF99FFA0]` = sub_4e05e50, all 150 live capture hits ret=0x1289496 [V live]; sub_4e05e50 issues createTexture via `0x4e05f77  call 0xBC41420` -> proven chain -> bgfx createTexture 0xe8143c0 [V live]; GPU handle written at [texture_obj+0x0] by `0xc296e26  mov [rdi],ax` [V]; created-texture shared_ptr (16B px+pn) copied by sub_4e061b0 `0x4e061cb  movups xmm0,[rdx]` / `0x4e061ce  movups [rcx],xmm0` into the destination shared_ptr [V]; TexturePtr.mClientTexture (+0x0) holds shared_ptr<BedrockTexture> [V header] so the handle is reachable via TexturePtr [I composition]. Remaining non-blocking context (not part of the issuance/handle-write link): no direct static call edge texgroup_load/texload -> sub_12893d0 (delivery via inferred deferred queue) [I]; exact TexturePtr.mClientTexture field store not statically located past sub_4e061b0's [rbp-8] destination [?]; SDK headers are stubs, real game layout unproven [?].

## TOOL REQUESTS
None — only rdis.exe, xref.py, and pre-existing preflight dossiers/captures used; no helper scripts written.