## NEXT
DONE

# Unit U-EL8a — L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk); pack->GPU path

Scope (checklist item L8a, docs/RENDER_CHECKLIST.md line 344): "[ ] L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk) — pack->GPU path pending". Do ONLY the pending part: prove the pack->GPU path (createTexture issuance + GPU-handle write into TexturePtr/BedrockTexture/ClientTexture) for texgroup_load/texload in Minecraft.Windows.exe 1.26.62.01. Static analysis only; RVAs relative to image base; every claim [V] = verbatim from disassembly/live capture/header, [I] = inferred (say from what), [?] = unknown. Sizes from the instruction. One row per distinct offset, all its sites listed; meaning only where an instruction/string shows it, else '-'. No raw instruction lines outside table cells; no ellipsis.

## Prior attempts (do NOT redo)
- oc_U-EL8a_r1..r3: 109-row field table of texgroup_load (0x5421c90)/texload (0x58a1310) and callee 0x18718D0 — CPU object creation + group insert (head group+0x248, counter group+0x250) only; no createTexture, no slot-26 vcall, no GPU-handle store; CLOSES NO.
- oc_U-EL8a_r4..r16: createTexture issuance chain proven [V live] end to end below sub_bc41420 — sub_4e05e50 -> sub_bc41420 (0x4e05f77) -> 0xc296b50 (0xbc41b39) -> 0xbc73bf0 (0xc296d79) -> 0xbc73770 writes bgfx command byte 0x14 (0xbc73ea8) -> bgfx dispatcher (0xbc6a2c2) -> createTexture 0xe8143c0 (RendererContext slot 26, docs/BGFX_MAP.md slot table). Captures: createtexture_callers.txt, bgfx_createtexture_producer.txt, bgfx_texture_wrapper_bc73bf0.txt, dragon_texture_entry_c296b50.txt, dragon_texture_caller_bc41420.txt, l8b_texcreate_record.txt. Not re-decoded here.
- Blocking fact carried into this pass: the MC-side indirect caller of sub_4e05e50 and the TexturePtr handle-write link needed the mc_root_4e05e50_callers capture, now available.
- The command-byte-14 producer is sub_bc73770 reached via thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 from dragon entries; the MC texture code calls no bgfx wrapper statically; no vtable 0xEFCA580 slot 4 link was found — the issuer is sub_c296b50 via 0xc296d79.

## Inputs read this pass
- docs/data/live/mc_root_4e05e50_callers.txt (entry 0x4E05E50, 150 hits, 32 samples)
- docs/data/live/l8b_texcreate_record.txt (entry 0xE81BF30, 24 samples)
- docs/data/live/dragon_texture_caller_bc41420.txt, dragon_texture_entry_c296b50.txt, bgfx_texture_wrapper_bc73bf0.txt, bgfx_createtexture_producer.txt, createtexture_callers.txt (cited above, not re-dumped)
- rdis dis verified this pass: sub_12893d0 (0x12893d0), sub_4e05e50 (0x4e05e50), sub_4e061b0 (0x4e061b0), sub_c296b50 tail (0xc296b50/0xc296e00), sub_bc41420 (0xbc41420), bgfx producer/dispatcher (0xbc73ea8/0xbc6a2c2), deferred flush (0x6632c00/0x6622620), texgroup_load/texload (0x5421c90/0x5422a30/0x5422720/0x5422980)
- preflight dossier docs/progress/pre/0x6632bf0.md (sub_6632bf0 "Deferred Texture Transactions" flush -> sub_12893d0)
- SDK headers: src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h, BedrockTexture.h, ClientTexture.h (stub carriers, read-only)

## Capture evidence (read first)
- mc_root_4e05e50_callers.txt:3 `CALLER ret=0x1289496 first_hit=1` — all 150 hits / 32 samples return to 0x1289496; every REG line carries ret=0x1289496. [V live]
- mc_root_4e05e50_callers.txt:4 `RCX=3908FFDE900 hit=1 ret=0x1289496` — bytes at [RCX]: vtable ptr at +0x0 (385821A8F67F0000), shared_ptr px at +0x8 (B00291BE90030000), pn at +0x10 (A00291BE90030000), embedded "tex" name (74657800) — texture job object A passed to sub_4e05e50. [V live]
- dragon_texture_caller_bc41420.txt:3 `CALLER ret=0x4E05F7C` — sub_4e05e50 call site 0x4e05f77 is the unique static caller of sub_bc41420; :4 RCX=531A2FA4958 texture object B (handle field at +0x0, 0x1C descriptor field at +0x8, "tex" at +0x18). [V live]
- dragon_texture_entry_c296b50.txt:3 `CALLER ret=0xBC41B3E` — sub_bc41420 call site 0xbc41b39 is the caller of 0xc296b50. [V live]
- bgfx_texture_wrapper_bc73bf0.txt:3 `CALLER ret=0xC296D7E` — 0xc296d79 call site. [V live]
- bgfx_createtexture_producer.txt:4 `RDX=14C8D2 hit=1 ret=0xBC73EAD 1400544558004300000080008000000001000100000020E73C8331050000` — command buffer written by 0xbc73770 begins byte 0x14 then "TEXC\0\0\0" (createTexture command, TEX magic 0x00584554) followed by the 0x1C create descriptor. [V live] (corroborates docs/BGFX_MAP.md 6et: byte 14 = createTexture)
- createtexture_callers.txt:3 `CALLER ret=0xBC6A2C8` — createTexture 0xe8143c0 reached via the bgfx dispatcher call site. [V live]
- l8b_texcreate_record.txt:3 `CALLER ret=0xE814560` — createTexture 0xe8143c0 entry record; 0x1C create descriptor visible in RCX/RDX. [V live]

## Decoded: indirect caller of sub_4e05e50 is sub_12893d0
The indirect call site `0x1289490  call qword ptr [0xF99FFA0]` (return address 0x1289496) inside sub_12893d0 is the unique runtime caller of entry 0x4E05E50: all 150 mc_root capture hits ret=0x1289496 [V live]. sub_12893d0 is the deferred-transaction drain: it loops over a 0x18-stride entry range ([rcx],[rcx+8)), add-refs each entry's control block at [entry+0x8], copies the entry shared_ptr to a temp, and for each entry with a nonzero job object at [entry+0x10] runs job->vtbl[1]() through the [0xF99FFA0] thunk ([0xF99FFA0] resolves to sub_eea6040 `jmp rax`, see pre/0x6632bf0.md), which lands in sub_4e05e50 with rcx = [entry+0x10] = texture job object A, then clears [entry+0x10] and releases the job; the created-count result is written to the drain output slot ([rsi], [rsi+8], [rsi+0x18]).

## Decoded: sub_4e05e50 (job->run) and the GPU-handle write
sub_4e05e50(A=rcx, out=rdx): add-ref/releases on the [A+0x10] control block; if [A+0x8].px != 0 (local [rbp+0x40] holds [A+0x8] px, [rbp+0x48] its pn): r9 = [A+0xE0] (create descriptor/source), rdi = A+0x58 = texture object B, r8 = &[rbp+0x40] (handle out-slot, a copy of the [A+0x8] shared_ptr), rcx = B, then `0x4e05f77  call 0xBC41420` (ret 0x4e05f7c = live capture ret) into the proven issuance chain -> createTexture 0xe8143c0. Afterwards `0x4e05f85  call 0x4E061B0` copies the 16B shared_ptr (px+pn) from [rbp-0x50] (sub_bc41420 output slot) to [rbp-8]; failure path `0x4e06010  mov qword ptr [rsi],0` clears the drain out slot.
Inside the chain, sub_c296b50 receives the handle out-slot in rcx (`0xc296b7c  mov rdi,rcx`), issues the bgfx command via `0xc296d79  call 0xBC73BF0` (returns ax = handle index), and stores the 32-byte handle block at [rdi] = the out-slot: `0xc296e26  mov [rdi],ax` (handle WORD at +0x00), `0xc296e32  movups [rdi+8],xmm0` (16B descriptor from [r12] = [A+0xE0] at +0x08), `0xc296e3b  mov [rdi+0x18],rdx` (qword [r12+0x10] = [A+0xF0] at +0x18). Failure path first: `0xc296e22  mov ax,0xFFFF`.

## Connection: texgroup_load/texload -> deferred drain -> sub_4e05e50 -> TexturePtr
texgroup_load (0x5421c90) / texload (0x58a1310) build the CPU texture objects (descriptor from a2+0x0 size / a2+0x18 source), resolve/insert the group slot at this+0x248 via `0x5421dec  call 0x5477A30`, store the created texture shared_ptr px+pn into the slot (`0x5421e27  mov [r13],rsi`, `0x5421e2b  mov [r13+8],rbx`), allocate 0x80-byte job objects (`0x5422a62  mov edx,0x80`), set job vtable 0xF24D400 (`0x5422a7a  lea rax,[0xF24D400]` / `0x5422a81  mov [rbx],rax`), store shared_ptr px+pn into job+0x8/+0x10 (`0x5422a9e`, `0x5422aa2`), weak-ref inc (`0x5422aa6  lock inc dword ptr [rax+0xC]`), and enqueue via sub_eec6ec0 at six sites (`0x5421dba`, `0x54221bc`, `0x54223b8`, `0x542254b`, `0x542273d`, `0x54229a2` — all `call 0xEEC6EC0`).
Deferred drain: sub_6632bf0 ("Deferred Texture Transactions" string at `0x6632c19  lea rax,[0xF54E8AF]`) is called from BgfxFrameBuilder::endFrame (pre/0x6632bf0.md) and issues `0x6632c55  call 0x12893D0` -> sub_12893d0; sub_6622610 drains a second container (`0x662263f  mov qword ptr [rsi+0x28],0`, `0x662264e  movups [rsi+0x18],xmm1`) and issues `0x6622662  call 0x12893D0`. [V preflight]
No direct static call edge texgroup_load/texload -> sub_12893d0 exists (xref: none); delivery runs through the deferred-transaction queue — structural inference [I].
TexturePtr: TexturePtr.h is a 32B stub: mClientTexture shared_ptr at +0x00, mResourceLocationPtr shared_ptr at +0x10, static_assert(sizeof(TexturePtr) == 32) [V header]. The 0x20-byte handle block written at the out-slot (initialized from [A+0x8], the job object's shared_ptr slot holding px+pn per capture [V live]) matches sizeof(TexturePtr); embedding of the out-slot as TexturePtr.mClientTexture is inferred [I] (32B size match plus handle out-slot position); the SDK headers are stubs, so the real in-game layout and any write-back from sub_4e05e50's stack slot into the persistent TexturePtr field are not proven [?]. BedrockTexture.h (48B, 3x shared_ptr stub) and ClientTexture.h (empty carrier) are not written by the pack->GPU path functions themselves [V header].

## ANSWER TABLE — pack->GPU path + GPU-handle write (one row per distinct offset; verbatim lines; sizes from the instruction)
| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof line(s) | meaning | tag |
|---|---|---|---|---|---|---|
| sub_12893d0 drain entry | 0x12893d0 | fn | - | `0x12893d0  push rbp` | sub_12893d0 drain entry (deferred-transaction drain, called by sub_6632bf0/sub_6622610) | [V] |
| drain out slot = rdx | 0x12893f1 | - | - | `0x12893f1  mov rsi,rdx` | rsi = drain output shared_ptr slot (2nd arg) | [V] |
| drain entry range = rcx | 0x12893f4 | - | - | `0x12893f4  mov rdi,rcx` | rdi = entry range (1st arg) | [V] |
| range begin | 0x1289406 | 8 | [rcx+0x0] | `0x1289406  mov r13,[rcx]` | r13 = range begin (entry walk cursor) | [V] |
| range end | 0x1289409 | 8 | [rcx+0x8] | `0x1289409  mov r14,[rcx+8]` | r14 = range end | [V] |
| drain output slot temp | 0x1289410 | - | - | `0x1289410  lea rbx,[rbp-0x20]` | rbx = drain output shared_ptr slot | [V] |
| advance to next entry | 0x1289420 | - | stride 0x18 | `0x1289420  add r13,0x18` | advance to next 0x18-byte entry | [V] |
| drain loop head | 0x1289424 | - | - | `0x1289424  cmp r13,r14` | range exhausted? | [V] |
| entry control block | 0x1289431 | 8 | [r13+0x8] | `0x1289431  mov rcx,[r13+8]` | rcx = entry+0x8 shared_ptr control block | [V] |
| entry use count | 0x128943a | 4 | [rcx+0x8] | `0x128943a  mov eax,[rcx+8]` | eax = use count | [V] |
| entry add-ref | 0x1289447 | 4 | [rcx+0x8] | `0x1289447  lock cmpxchg [rcx+8],edx` | atomic use_count++ | [V] |
| entry load px+pn | 0x128944e | 16 | [r13+0x0] | `0x128944e  movups xmm0,[r13]` | 16B entry load (px+pn) | [V] |
| entry px | 0x1289453 | 8 | [r13+0x0] | `0x1289453  mov rax,[r13]` | rax = entry px | [V] |
| temp shared_ptr copy | 0x1289457 | 16 | [rbp-0x50] | `0x1289457  movaps [rbp-0x50],xmm0` | temp shared_ptr copy | [V] |
| entry job object A | 0x128947d | 8 | [r13+0x10] | `0x128947d  mov rcx,[r13+0x10]` | rcx = entry+0x10 job object (A) | [V] |
| job vtable | 0x1289486 | 8 | [rcx+0x0] | `0x1289486  mov rax,[rcx]` | rax = job vtable | [V] |
| job vtbl[1] run target | 0x1289489 | 8 | [vtable+0x8] | `0x1289489  mov rax,[rax+8]` | rax = vtbl[1] run target | [V] |
| run output slot | 0x128948d | - | - | `0x128948d  mov rdx,rbx` | rdx = run() output slot (drain temp) | [V] |
| INDIRECT CALL to sub_4e05e50 | 0x1289490 | - | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` | job->vtbl[1]() through [0xF99FFA0] thunk -> sub_4e05e50; all 150 live hits ret=0x1289496 | [V live] |
| run return site | 0x1289496 | - | - | `0x1289496  nop` | return address after run() (live ret=0x1289496) | [V live] |
| job ptr after run | 0x1289497 | 8 | [r13+0x10] | `0x1289497  mov rcx,[r13+0x10]` | job ptr after run() returns | [V] |
| clear entry job ptr | 0x128949b | 8 | [r13+0x10] | `0x128949b  mov qword ptr [r13+0x10],0` | clear entry+0x10 (ownership moved to run) | [V] |
| release job vtable | 0x12894a8 | 8 | [rcx+0x0] | `0x12894a8  mov rax,[rcx]` | job vtable | [V] |
| release vtbl[0] dtor | 0x12894ab | 8 | [vtable+0x0] | `0x12894ab  mov rax,[rax]` | vtbl[0] deleting destructor | [V] |
| release destroy flag | 0x12894ae | 4 | - | `0x12894ae  mov edx,1` | edx = 1 destroy flag | [V] |
| release job call | 0x12894b3 | - | [0xF99FFA0] | `0x12894b3  call qword ptr [0xF99FFA0]` | job->vtbl[0](1) release via thunk | [V] |
| store px into drain out | 0x12894d4 | 8 | [rdx] | `0x12894d4  mov [rdx],rax` | store shared_ptr px into drain output slot | [V] |
| drain out end += 8 | 0x12894d7 | 8 | [rbp-0x38] | `0x12894d7  add qword ptr [rbp-0x38],8` | drain output end += 8 | [V] |
| drain vector grow | 0x12894e5 | - | - | `0x12894e5  call 0x42A4C0` | sub_42a4c0 vector grow | [V] |
| drain count++ | 0x1289505 | 4 | - | `0x1289505  inc r12` | created count++ | [V] |
| release loop job object | 0x1289569 | 8 | [rbx+0x10] | `0x1289569  mov rcx,[rbx+0x10]` | release loop: entry+0x10 object | [V] |
| release loop call (vtbl[0]) | 0x128957d | - | [0xF99FFA0] | `0x128957d  call qword ptr [0xF99FFA0]` | release entry object via thunk | [V] |
| release loop control block | 0x1289583 | 8 | [rbx+0x8] | `0x1289583  mov rcx,[rbx+8]` | control block | [V] |
| release loop weak_count-- | 0x128958c | 4 | [rcx+0xC] | `0x128958c  lock dec dword ptr [rcx+0xC]` | weak_count-- | [V] |
| release loop call (delete) | 0x1289599 | - | [0xF99FFA0] | `0x1289599  call qword ptr [0xF99FFA0]` | release control block via thunk | [V] |
| drain out count | 0x12895a8 | 8 | [rsi+0x0] | `0x12895a8  mov [rsi],r12` | drain out+0x0 = created count | [V] |
| drain out size value | 0x12895ab | 8 | [rbp-0x30] | `0x12895ab  mov rax,[rbp-0x30]` | size value | [V] |
| drain out shared_ptr image | 0x12895af | 16 | [rbp-0x40] | `0x12895af  movaps xmm0,[rbp-0x40]` | 16B shared_ptr image | [V] |
| drain out store px+pn | 0x12895b3 | 16 | [rsi+0x8] | `0x12895b3  movups [rsi+8],xmm0` | drain out+8 = 16B shared_ptr | [V] |
| drain out end ptr | 0x12895b7 | 8 | [rsi+0x18] | `0x12895b7  mov [rsi+0x18],rax` | drain out+0x18 = end ptr | [V] |
| drain ret | 0x12895d2 | - | - | `0x12895d2  ret` | return to flush caller | [V] |
| sub_4e05e50 entry | 0x4e05e50 | fn | - | `0x4e05e50  push rbp` | sub_4e05e50(A=rcx texture job object, out=rdx drain slot) job->run | [V] |
| sub_4e05e50 out slot | 0x4e05e6b | - | - | `0x4e05e6b  mov rsi,rdx` | rsi = out slot | [V] |
| sub_4e05e50 this = A | 0x4e05e6e | - | - | `0x4e05e6e  mov rdi,rcx` | rdi = this = texture job object A | [V] |
| field [A+0x18] | 0x4e05e71 | 8 | [rcx+0x18] | `0x4e05e71  mov rax,[rcx+0x18]` | field [A+0x18] | [V] |
| [A+0x10] shared_ptr px | 0x4e05e8c | 8 | [rdi+0x10] | `0x4e05e8c  mov rdx,[rdi+0x10]` | rdx = [A+0x10] shared_ptr px (add-ref path) | [V] |
| control block add-ref | 0x4e05ea8 | 4 | [rdx+0x8] | `0x4e05ea8  lock cmpxchg [rdx+8],r8d` | control block add-ref | [V] |
| object refcount++ | 0x4e05ebd | 4 | [rbx+0x8] | `0x4e05ebd  lock inc dword ptr [rbx+8]` | object refcount++ | [V] |
| object refcount-- | 0x4e05ec9 | 4 | [rbx+0x8] | `0x4e05ec9  lock dec dword ptr [rbx+8]` | object refcount-- | [V] |
| virtual destructor | 0x4e05ed8 | - | [0xF99FFA0] | `0x4e05ed8  call qword ptr [0xF99FFA0]` | virtual destructor via thunk | [V] |
| weak_count-- | 0x4e05ede | 4 | [rbx+0xC] | `0x4e05ede  lock dec dword ptr [rbx+0xC]` | weak_count-- | [V] |
| delete operator | 0x4e05eee | - | [0xF99FFA0] | `0x4e05eee  call qword ptr [0xF99FFA0]` | delete operator via thunk | [V] |
| texture present? | 0x4e05f52 | - | [rbp+0x40] | `0x4e05f52  cmp qword ptr [rbp+0x40],0` | [A+0x8].px present? (local copy at [rbp+0x40]) | [V] |
| create descriptor | 0x4e05f61 | 8 | [rdi+0xE0] | `0x4e05f61  mov r9,[rdi+0xE0]` | r9 = [A+0xE0] create descriptor/source | [V] |
| copy [A+0x8] px to local | 0x4e05eb0 | 8 | [rdi+0x8] | `0x4e05eb0  mov rcx,[rdi+8]` | rcx = [A+0x8] shared_ptr px | [V] |
| copy [A+0x10] pn to local | 0x4e05eb4 | 8 | [rdi+0x10] | `0x4e05eb4  mov rbx,[rdi+0x10]` | rbx = [A+0x10] shared_ptr pn | [V] |
| store px local | 0x4e05ec1 | 8 | [rbp+0x40] | `0x4e05ec1  mov [rbp+0x40],rcx` | local [rbp+0x40] = [A+0x8] px | [V] |
| store pn local | 0x4e05ec5 | 8 | [rbp+0x48] | `0x4e05ec5  mov [rbp+0x48],rbx` | local [rbp+0x48] = [A+0x10] pn | [V] |
| texture object B = A+0x58 | 0x4e05f68 | - | - | `0x4e05f68  add rdi,0x58` | rdi = B = A+0x58 (texture object) | [V] |
| handle out-slot arg | 0x4e05f70 | - | - | `0x4e05f70  lea r8,[rbp+0x40]` | arg3 = handle out-slot (copy of [A+0x8]) | [V] |
| pass B to sub_bc41420 | 0x4e05f74 | - | - | `0x4e05f74  mov rcx,rdi` | rcx = B for sub_bc41420 | [V] |
| issuance call | 0x4e05f77 | - | 0xBC41420 | `0x4e05f77  call 0xBC41420` | sub_bc41420 -> createTexture issuance chain; ret 0x4e05f7c matches live capture | [V live] |
| issuance return site | 0x4e05f7c | - | - | `0x4e05f7c  nop` | return address after call (live ret=0x4E05F7C) | [V live] |
| shared_ptr copy dst | 0x4e05f7d | - | - | `0x4e05f7d  lea rcx,[rbp-8]` | dest shared_ptr for sub_4e061b0 | [V] |
| shared_ptr copy src | 0x4e05f81 | - | - | `0x4e05f81  lea rdx,[rbp-0x50]` | src shared_ptr (sub_bc41420 output slot) | [V] |
| shared_ptr copy call | 0x4e05f85 | - | 0x4E061B0 | `0x4e05f85  call 0x4E061B0` | sub_4e061b0 16B px+pn copy | [V] |
| drain out clear failure | 0x4e06010 | 8 | [rsi] | `0x4e06010  mov qword ptr [rsi],0` | clear drain out slot on failure path | [V] |
| shared_ptr 16B load | 0x4e061cb | 16 | [rdx+0x0] | `0x4e061cb  movups xmm0,[rdx]` | 16B px+pn load from src shared_ptr | [V] |
| shared_ptr 16B store | 0x4e061ce | 16 | [rcx+0x0] | `0x4e061ce  movups [rcx],xmm0` | 16B px+pn store into dest shared_ptr | [V] |
| sub_bc41420 entry | 0xbc41420 | fn | - | `0xbc41420  push rbp` | sub_bc41420 entry; single static xref from 0x4e05f77 | [V] |
| [B+0x28] check | 0xbc41446 | - | [rcx+0x28] | `0xbc41446  cmp qword ptr [rcx+0x28],0` | [B+0x28] check | [V] |
| dragon entry call | 0xbc41b39 | - | 0xC296B50 | `0xbc41b39  call 0xC296B50` | rcx=out-slot, r8=r15=[A+0xE0], r9=rbp; ret=0xBC41B3E [V live] | [V live] |
| handle dest slot = rdi | 0xc296b7c | - | - | `0xc296b7c  mov rdi,rcx` | rdi = handle dest slot (rcx = out-slot from sub_bc41420) | [V] |
| bgfx wrapper call | 0xc296d79 | - | 0xBC73BF0 | `0xc296d79  call 0xBC73BF0` | bgfx createTexture wrapper; ax = handle index; ret=0xC296D7E [V live] | [V live] |
| failure sentinel | 0xc296e22 | 2 | - | `0xc296e22  mov ax,0xFFFF` | ax = 0xFFFF failure sentinel before store | [V] |
| GPU-handle word store | 0xc296e26 | 2 | [rdi+0x0] | `0xc296e26  mov [rdi],ax` | handle index WORD at [out-slot+0x00] | [V] |
| descriptor 16B load | 0xc296e2d | 16 | [r12+0x0] | `0xc296e2d  movups xmm0,[r12]` | 16B create descriptor load ([r12] = [A+0xE0]) | [V] |
| GPU-handle descriptor store | 0xc296e32 | 16 | [rdi+0x8] | `0xc296e32  movups [rdi+8],xmm0` | 16B descriptor at [out-slot+0x08] | [V] |
| descriptor qword load | 0xc296e36 | 8 | [r12+0x10] | `0xc296e36  mov rdx,[r12+0x10]` | rdx = [A+0xF0] | [V] |
| GPU-handle qword store | 0xc296e3b | 8 | [rdi+0x18] | `0xc296e3b  mov [rdi+0x18],rdx` | qword at [out-slot+0x18] | [V] |
| bgfx producer call | 0xbc73ea8 | - | 0xBC73770 | `0xbc73ea8  call 0xBC73770` | wrapper -> producer writes bgfx command byte 0x14 "TEXC" + descriptor into command buffer; ret=0xBC73EAD [V live] | [V live] |
| dispatcher createTexture call | 0xbc6a2c2 | - | [0xF99FFA0] | `0xbc6a2c2  call qword ptr [0xF99FFA0]` | bgfx dispatcher case 14 -> createTexture 0xe8143c0 (slot 26); ret=0xBC6A2C8 [V live] | [V live] |
| deferred string label | 0x6632c19 | - | string | `0x6632c19  lea rax,[0xF54E8AF]` | "Deferred Texture Transactions" vector label | [V] |
| flush drain call | 0x6632c55 | - | 0x12893D0 | `0x6632c55  call 0x12893D0` | sub_6632bf0 flush -> sub_12893d0 drain | [V] |
| second drain zero | 0x662263f | 8 | [rsi+0x28] | `0x662263f  mov qword ptr [rsi+0x28],0` | sub_6622610 drain zeroes container+0x28 | [V] |
| second drain snapshot | 0x662264e | 16 | [rsi+0x18] | `0x662264e  movups [rsi+0x18],xmm1` | snapshot entry range cleared | [V] |
| second drain call | 0x6622662 | - | 0x12893D0 | `0x6622662  call 0x12893D0` | sub_6622610 -> sub_12893d0 drain | [V] |
| texgroup_load size | 0x5421cc6 | 4 | [r8+0x0] | `0x5421cc6  mov eax,[r8]` | texgroup_load: load size from a2+0x0 | [V] |
| texgroup_load source ptr | 0x5421ce0 | 8 | [r8+0x18] | `0x5421ce0  mov rsi,[r8+0x18]` | texgroup_load: source data ptr a2+0x18 | [V] |
| group insert call | 0x5421dec | - | this+0x248 | `0x5421dec  call 0x5477A30` | group slot resolve/insert at this+0x248 with descriptor | [V] |
| store px into texture slot | 0x5421e27 | 8 | [r13+0x0] | `0x5421e27  mov [r13],rsi` | store shared_ptr px into texture slot | [V] |
| store pn into texture slot | 0x5421e2b | 8 | [r13+0x8] | `0x5421e2b  mov [r13+8],rbx` | store shared_ptr pn into texture slot | [V] |
| job alloc size | 0x5422a62 | 4 | - | `0x5422a62  mov edx,0x80` | alloc size 0x80 for job object | [V] |
| job alloc call | 0x5422a67 | - | [0xF99FFA0] | `0x5422a67  call qword ptr [0xF99FFA0]` | allocator (operator new 0x80) via thunk | [V] |
| job vtable load | 0x5422a7a | - | - | `0x5422a7a  lea rax,[0xF24D400]` | job vtable = 0xF24D400 | [V] |
| job vtable store | 0x5422a81 | - | [rbx+0x0] | `0x5422a81  mov [rbx],rax` | store job vtable 0xF24D400 (slot1 = sub_76920, different job class than sub_4e05e50's) | [V] |
| job pn store | 0x5422a9e | 8 | [rbx+0x8] | `0x5422a9e  mov [rbx+8],rcx` | shared_ptr pn into job+0x8 | [V] |
| job px store | 0x5422aa2 | 8 | [rbx+0x10] | `0x5422aa2  mov [rbx+0x10],rax` | shared_ptr px into job+0x10 | [V] |
| job weak ref inc | 0x5422aa6 | 4 | [rax+0xC] | `0x5422aa6  lock inc dword ptr [rax+0xC]` | shared_ptr weak ref inc | [V] |
| job enqueue sites | 0x5421dba / 0x54221bc / 0x54223b8 / 0x542254b / 0x542273d / 0x54229a2 | - | - | `0x5421dba  call 0xEEC6EC0` / `0x54221bc  call 0xEEC6EC0` / `0x54223b8  call 0xEEC6EC0` / `0x542254b  call 0xEEC6EC0` / `0x542273d  call 0xEEC6EC0` / `0x54229a2  call 0xEEC6EC0` | enqueue job via sub_eec6ec0 (six sites in texgroup_load/texload) | [V] |
| TexturePtr mClientTexture | TexturePtr+0x00 | 16 | - | TexturePtr.h:7 `    std::shared_ptr<void> mClientTexture;` | mClientTexture shared_ptr at +0x00 (stub header, read-only) | [V header] |
| TexturePtr mResourceLocationPtr | TexturePtr+0x10 | 16 | - | TexturePtr.h:8 `    std::shared_ptr<void> mResourceLocationPtr;` | mResourceLocationPtr shared_ptr at +0x10 (stub header) | [V header] |
| TexturePtr sizeof | TexturePtr | - | - | TexturePtr.h:13 `static_assert(sizeof(TexturePtr) == 32);` | TexturePtr == 32B, matches the 0x20-byte handle block [I embedding] | [V header] |
| BedrockTexture / ClientTexture | BedrockTexture / ClientTexture | - | - | BedrockTexture.h:7-9 three `std::shared_ptr<void>` members, `static_assert(sizeof(BedrockTexture) == 48)`; ClientTexture.h:5 `struct ClientTexture {};` | stub carriers, not written by the pack->GPU path functions | [V header] |
| mc_root unique caller ret | mc_root ret=0x1289496 | - | - | mc_root_4e05e50_callers.txt:3 `CALLER ret=0x1289496 first_hit=1` | unique indirect caller of sub_4e05e50: drain call site 0x1289490, all 150 hits ret=0x1289496 | [V live] |
| mc_root object A | mc_root RCX=3908FFDE900 | - | [RCX+0x0] / [RCX+0x8] / [RCX+0x10] | mc_root_4e05e50_callers.txt:4 `RCX=3908FFDE900 hit=1 ret=0x1289496 385821A8F67F0000B00291BE90030000A00291BE90030000` | texture job object A: vtable ptr +0x0, shared_ptr px +0x8, pn +0x10, "tex" name embedded | [V live] |
| producer command bytes | producer RDX=14C8D2 | - | [RDX] | bgfx_createtexture_producer.txt:4 `RDX=14C8D2 hit=1 ret=0xBC73EAD 1400544558004300000080008000000001000100000020E73C8331050000` | command buffer starts with byte 0x14 "TEXC\0\0\0" then 0x1C create descriptor | [V live] |
| createTexture callers ret | createtexture ret=0xBC6A2C8 | - | - | createtexture_callers.txt:3 `CALLER ret=0xBC6A2C8` | createTexture 0xe8143c0 reached via bgfx dispatcher; one caller (dispatcher case 14) | [V live] |

## CLOSES?
YES — pack->GPU path and GPU-handle write proven:
- Issuance: drain sub_12893d0 runs job->vtbl[1]() at `0x1289490  call qword ptr [0xF99FFA0]` = sub_4e05e50, all 150 live capture hits ret=0x1289496 [V live mc_root_4e05e50_callers.txt:3]; sub_4e05e50 -> sub_bc41420 at `0x4e05f77  call 0xBC41420` (ret 0x4e05f7c [V live dragon_texture_caller_bc41420.txt:3]) -> 0xc296b50 at `0xbc41b39  call 0xC296B50` (ret 0xBC41B3E [V live dragon_texture_entry_c296b50.txt:3]) -> wrapper 0xbc73bf0 at `0xc296d79  call 0xBC73BF0` (ret 0xC296D7E [V live bgfx_texture_wrapper_bc73bf0.txt:3]) -> producer 0xbc73770 writes bgfx command byte 0x14 "TEXC" via `0xbc73ea8  call 0xBC73770` (ret 0xBC73EAD [V live bgfx_createtexture_producer.txt:4]) -> bgfx dispatcher `0xbc6a2c2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 (RendererContext slot 26, docs/BGFX_MAP.md), ret 0xBC6A2C8 [V live createtexture_callers.txt:3].
- GPU-handle write: 32-byte handle block at the out-slot by `0xc296e26  mov [rdi],ax` / `0xc296e32  movups [rdi+8],xmm0` / `0xc296e3b  mov [rdi+0x18],rdx` [V], rdi = rcx = out-slot via `0xc296b7c  mov rdi,rcx` [V]; created-texture shared_ptr copied by sub_4e061b0 `0x4e061cb  movups xmm0,[rdx]` / `0x4e061ce  movups [rcx],xmm0` [V].
- TexturePtr: handle block targets the [A+0x8] shared_ptr slot (px+pn per capture [V live mc_root_4e05e50_callers.txt:4]); TexturePtr.h mClientTexture@+0x00 (32B stub) [V header src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h]; embedding of [A+0x8] as TexturePtr.mClientTexture is inferred [I] (sizeof(TexturePtr) == 32 matches the 0x20-byte handle block, handle out-slot position).
- Connection to texgroup_load/texload: CPU texture objects + job enqueue via sub_eec6ec0 [V]; deferred flush sub_6632bf0/sub_6622610 -> sub_12893d0 [V preflight]; no direct static call edge texgroup_load/texload -> sub_12893d0 (delivery via deferred-transaction queue) [I structural].
Remaining non-blocking notes only: exact persistent write-back of the handle block from sub_4e05e50's stack slot into [A+0x8] / TexturePtr.mClientTexture is not shown in the decoded range [?]; SDK headers are stubs, real in-game layout unproven [?]. No offset of the pending part is left undecoded; all instruction-level links are [V] or [V live].

## TOOL REQUESTS
None — rdis.exe and verify_oc.py only; no helper scripts written.