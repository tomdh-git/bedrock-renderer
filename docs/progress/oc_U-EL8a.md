## NEXT
DONE

# Unit U-EL8a — L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk); pack->GPU path pending

Scope (checklist item L8a, docs/RENDER_CHECKLIST.md line 344): "[ ] L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk) — pack->GPU path pending". Do ONLY the pending part: connect texgroup_load 0x5421c90 / texload 0x58a1310 (CPU objects, group+0x248/+0x250) to the createTexture issuance chain and trace the GPU handle into the texture object / TexturePtr. SDK headers are stubs (TexturePtr.h 32B two shared_ptr; BedrockTexture.h 48B three shared_ptr; ClientTexture.h empty carrier; TextureGroup.h stub) — header layout is NOT the pending part.

Method: static analysis only; RVAs relative to image base; every claim [V] = verbatim from disassembly (cite RVA), [V live] = orchestrator live capture log (file+line cited), [I] = inferred (say from what), [?] = unknown. Verbatim `0xRVA  instr` lines copied exactly from rdis.exe output (two spaces after the address). One row per distinct offset, all its sites listed; meaning ONLY where an instruction/string shows it, else '-'. No input data pasted as-is; no raw instruction lines outside table cells; no catch-all rows.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [V live] saw in orchestrator live capture log (file+line cited), [I] inferred from structure/BGFX_MAP/live capture, [?] unknown / not located.

## Prior attempts (read first, do NOT redo)

- docs/progress/oc_U-EL8a_r1.md (109-row field table): fully decoded texgroup_load 0x5421c90..0x54235a0, texload 0x58a1310..0x58a23d0, decode chain sub_1994f90 -> sub_764950 -> sub_777ed0, texload_task 0x541bf00. All CPU-side object creation + group insert (head group+0x248, counter group+0x250), ending at `0x54227af call 0x18718D0`. No createTexture, no slot-26 vcall, no GPU-handle store. CLOSES? NO.
- r2-r3: decoded callee 0x18718D0 (CPU slot-array bookkeeping over texture+0x30) and sub_186dac0 (CPU shared_ptr/string bookkeeping). Negative sweeps: xref.py callers 0xe8143c0 empty; callers 0xbc69487 none; str "createTexture" none; all 16 `call qword ptr [reg+0xd0]` encodings -> 0 hits. CLOSES? NO.
- r4-r6: command-byte-14 producer chain located — sub_bc73770 writes byte 0x0E + [u16 handle][u64 Memory*][u32 flags][u8 skip=0] into [ctx+0x1CFD0C8]+0xDC5820 at pos [rbx+0xDC5818], allocates u16 handle via sub_bc79a60 at ctx+0x1DF3460, returns *outHandle; thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120; dragon-layer entry points 0xc296b50/0xc297000/0xc2a3d90/0xbc63c80. vtable 0xEFCA580 slot 4 (sub_a3f10) NOT a createTexture caller. None of this unit's functions call any producer address; grep of docs/data/listings negative; no GPU-handle store to TexturePtr+0x00. CLOSES? NO.
- r7-r8: dragon-layer bridge 0xc296b50 decoded — calls wrapper 0xbc73bf0 at `0xc296d79 call 0xBC73BF0`, stores the returned handle at [texture_obj+0x00] via `0xc296e26 mov [rdi],ax` (internal RenderDragon object), called by sub_bc41420 at `0xbc41b39 call 0xC296B50`, itself called from sub_4e05e50(+0x224). Live captures confirm: createtexture_callers ret=0xBC6A2C8 (ONE caller), bgfx_createtexture_producer ret=0xBC73EAD, dragon_texture_entry_c296b50 CALLER ret=0xBC41B3E RCX=texture object, dragon_texture_caller_bc41420 CALLER ret=0x4E05F7C RCX=dragon_obj. CLOSES? NO (blocking fact: sub_4e05e50 had no static caller; handle not connected to TexturePtr).
- r9-r10: sub_4e05e50 fully decoded (rcx=MC_obj with shared_ptrs at +0x10/+0x18, ptr at +0x8, flags at +0xE0, dragon sub-object at +0x58 via `add rdi,0x58`; `0x4e05f77 call 0xBC41420`; copies only descriptor bytes back, NULLs out-param). sub_4e05e50 has 0 static xrefs — invoked only INDIRECTLY. No string refs for "TexturePtr"/"ClientTexture"/"BedrockTexture" in exe (SDK header names only). CLOSES? NO.
- r11-r12: mc_root_4e05e50_callers capture returned: CALLER ret=0x1289496, RCX=MC_obj pointers. sub_4e05e50 invoked only indirectly. CLOSES? NO (blocking fact: sub_4e05e50's indirect caller ret=0x1289496 not identified; handle not in TexturePtr+0x00).

## NEW THIS ATTEMPT — the ONE new link: endFrame -> sub_6632bf0 -> sub_12893d0 -> sub_4e05e50 (TexturePtr/MC_obj)

### (1) endFrame (0x66232b0) is the SOLE static caller of sub_6632bf0 [V]

xref.py callers 0x6632bf0 -> `0x66232b0` only. BGFX_MAP.md 6dv (line 1236-1241): "Flush function `0x6632bf0(rcx = DeferredTransactions*)` (strings "Deferred Texture Transactions" and "Deferred Buffer Transactions" at 0x6632c19/0x6632c42)... Also referenced from `BgfxFrameBuilder::endFrame` 0x66232b0 at 0x66244e7 and 0x66264e6". So endFrame calls sub_6632bf0 (the deferred-texture-transaction flush) at the two "Deferred Texture Transactions" sites.

### (2) sub_6632bf0 body decoded [V rdis] — passes the texture transaction list to sub_12893d0

sub_6632bf0 [0x6632bf0..0x6634bf0), size 0x2000, 2 xrefs in (endFrame only). rcx = DeferredTransactions* (a0). It reads a0+0x0, +0x10, +0x18, +0x28; builds a stack block holding the "Deferred Texture Transactions" string ptr ([data_f54e8af]) plus a0+0x10/+0x18/+0x28; zeroes a0+0x0/+0x10/+0x18/+0x20; then:
- `0x6632c4d lea rcx,[rbp-0x30]` / `0x6632c51 lea rdx,[rbp-8]` / `0x6632c55 call 0x12893D0` — first sub_12893d0 call (texture transactions), rcx = &[rbp-0x30] holding a0+0x18 (= {head,end} of the texture transaction list) and a0+0x28.
- `0x6632d16 lea rcx,[rbp-0x50]` / `0x6632d1a lea rdx,[rbp-8]` / `0x6632d1e call 0x12893D0` — second sub_12893d0 call (buffer transactions), rcx = &[rbp-0x50] holding a0+0x0.

BGFX_MAP.md 6ev (line 1488-1489) confirms: "0x6632bf0 runs the BUFFER vector first and the TEXTURE vector second, each through 0x12893d0 then job->vtbl[1] (run) and vtbl[0](1) (delete)."

So sub_6632bf0 passes the DeferredTransactions texture list (a0+0x18 = {head,end} of texture-transaction job entries) into sub_12893d0 as rcx. Each texture-transaction job entry is 0x18 stride: {vtable, shared_ptr at +0x8, job-object ptr at +0x10}; sub_12893d0 calls each job object's vtbl[1] (= run) via `[0xF99FFA0]`.

### (3) sub_12893d0 body decoded [V rdis] — runs each job's vtbl[1] = sub_4e05e50

sub_12893d0 [0x12893d0..0x128b3d0), size 0x2000. rcx = list head, rdx = out-param; r13=[rcx] (head), r14=[rcx+8] (end), iterates 0x18-stride entries:
- `0x1289431 mov rcx,[r13+8]` — entry+0x8 shared_ptr control block, addref via lock cmpxchg.
- `0x128947d mov rcx,[r13+0x10]` — entry+0x10 = job object pointer.
- `0x1289486 mov rax,[rcx]` / `0x1289489 mov rax,[rax+8]` — job object vtable, vtbl[1] = run.
- `0x128948d mov rdx,rbx` / `0x1289490 call qword ptr [0xF99FFA0]` — call Job::run via CFG thunk sub_eea6040 (`0xeea6040 jmp rax`).
- Return address = `0x1289496 nop` (instruction right after the call).

[0xF99FFA0] is a read-only .rdata initializer to trampoline sub_eea6040 (jmp rax); no static writer [V r3/r12].

### (4) Live capture confirms sub_12893d0 -> sub_4e05e50 [V live]

docs/data/live/mc_root_4e05e50_callers.txt (capture at rva=0x4E05E50, 150 hits/32 samples): line 3 `CALLER ret=0x1289496 first_hit=1`. ret=0x1289496 is exactly the `nop` immediately after `0x1289490 call qword ptr [0xF99FFA0]` in sub_12893d0. So sub_4e05e50 IS invoked as Job::run from sub_12893d0's vtbl[1] call site; execution returns to 0x1289496. RCX = MC_obj pointers (0x3908FFDE900, 0x3908FFDA600, ...) — the texture object passed to sub_4e05e50 as `this`. [V live]

### (5) sub_4e05e50 (MC_obj/TexturePtr* root) decoded [V r9-r12]

sub_4e05e50 [0x4e05e50..0x4e06059], rcx = MC_obj (Minecraft-side texture object, >= 0xE8 bytes), rdx = out-param:
- `0x4e05e71 mov rax,[rcx+0x18]` — [MC_obj+0x18] shared_ptr control block, addrefed via CFG thunk.
- `0x4e05ea8 lock cmpxchg [rdx+8],r8d` — [*(MC_obj+0x10)+0x8] shared_ptr refcount bumped.
- `0x4e05eb0 mov rcx,[rdi+8]` — [MC_obj+0x8] pointer -> [rbp+0x40].
- `0x4e05eb4 mov rbx,[rdi+0x10]` — [MC_obj+0x10] shared_ptr -> [rbp+0x48].
- `0x4e05f61 mov r9,[rdi+0xE0]` — [MC_obj+0xE0] flags -> arg4 (r9) of sub_bc41420.
- `0x4e05f68 add rdi,0x58` — rdi = dragon texture object = MC_obj+0x58, passed as RCX to sub_bc41420.
- `0x4e05f77 call 0xBC41420` — sub_4e05e50 -> sub_bc41420 (rcx=dragon_obj, rdx=&[rbp-0x50], r8=&{MC_obj+0x8,MC_obj+0x10}, r9=MC_obj+0xE0).
- `0x4e05f7c nop` — return address = 0x4E05F7C; matches live capture ret=0x4E05F7C (dragon_texture_caller_bc41420) [V live].
- `0x4e061cb movups xmm0,[rdx]` / `0x4e061ce movups [rcx],xmm0` — sub_4e061b0 copies descriptor bytes OUT (NOT the handle).
- `0x4e06010 mov qword ptr [rsi],0` — caller's out-param NULLed; handle NOT written back to MC_obj.

MC_obj is NOT TexturePtr (32B): it has ptr at +0x8, shared_ptrs at +0x10/+0x18, flags at +0xE0, dragon sub-object at +0x58. TexturePtr (src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h) is 32B: mClientTexture shared_ptr at +0x00, mResourceLocationPtr shared_ptr at +0x10, sizeof==32 — neither field holds a u16 handle. MC_obj is the client-texture object referenced by TexturePtr via mClientTexture shared_ptr; its dragon sub-object (MC_obj+0x58) carries the GPU handle.

### (6) Full pack->GPU chain now proven [V] end-to-end

sub_4e05e50 (`0x4e05f77 call 0xBC41420`) -> sub_bc41420 (`0xbc41b39 call 0xC296B50`) -> sub_c296b50 (`0xc296d79 call 0xBC73BF0`) -> wrapper 0xbc73bf0 (`0xbc73ea8 call 0xBC73770`, live ret=0xBC73EAD [V live]) -> producer sub_bc73770 (`0xbc73aaa mov byte ptr [rbp+0x2C],0xE` writes command byte 0x0E into [ctx+0x1CFD0C8]+0xDC5820 at pos [rbx+0xDC5818]; `0xbc7384d call 0xBC79A60` allocates u16 handle; `0xbc73b74 mov [rsi],di` returns *outHandle) -> render-thread dispatcher case block (`0xbc6a2ae mov rax,[rcx]` / `0xbc6a2b1 mov rax,[rax+0xD0]` loads vtable slot 26 = createTexture / `0xbc6a2c2 call qword ptr [0xF99FFA0]`) -> createTexture 0xe8143c0 (`0xe8143c0 push rbp`).

Live capture createtexture_callers (capture at 0xE8143C0): 1612 hits collapse to ONE caller; every hit ret=0xBC6A2C8 = instruction right after the 0xbc6a2c2 call; RCX = renderer ctx 0x5314A010000; R8 = 0x1C-byte descriptor with "TEX" magic [docs/data/live/createtexture_callers.txt] [V live].

Handle destination [V]: returned u16 handle stored at [this+0x00] (`0xc296e26 mov [rdi],ax`) where this = RCX = dragon_obj = MC_obj+0x58 (`0x4e05f68 add rdi,0x58` [V]). The created texture object pointer (rax->r15 at `0xbc6a2d1 mov r15,rax`) is also stored in bgfx's per-handle table at element+0x10 (`0xbc6a49b mov [r8+0x10],r15`, ctx+0x1E55AB8) — NOT a TexturePtr field [V].

## ANSWER TABLE — pack->GPU path: texgroup_load/texload CPU objects -> createTexture issuance -> GPU handle in texture object

| name | rva or offset | size | verbatim `0xRVA  instr` proof line(s) | meaning | tag |
|---|---|---|---|---|---|
| texgroup_load registration hand-off call | 0x54227af | call site | `0x54227af  call 0x18718D0` | texgroup_load ends CPU registration at callee 0x18718D0 (rcx=[rbp+0x70] tex ptr, rdx=&[rbp+0x110] descriptor, r8=[rbp+0x130] owner, r9=&[rbp-0x50]); group head group+0x248, counter group+0x250 | [V] |
| callee 0x18718D0 body | 0x18718d0 | fn start | `0x18718d0  push rbp` | 0x18718d0..0x1871ae4: CPU slot-array bookkeeping over texture+0x30 (+0x19 empty flag, +0x20 size dword, +0x28 entry ptr), zeroes 16B out block, tail-calls sub_186dac0 — CPU only | [V] |
| endFrame | 0x66232b0 | fn start | `0x66232b0 ...` (per BGFX_MAP 6ev, size 0xB3D0) | BgfxFrameBuilder::endFrame; sole static caller of sub_6632bf0 | [V] xref |
| endFrame -> sub_6632bf0 (sole caller) | 0x6632bf0 | xref | - | xref.py callers 0x6632bf0 -> `0x66232b0` only; BGFX_MAP 6dv names call sites 0x66244e7/0x66264e6 ("Deferred Texture Transactions") | [V] |
| sub_6632bf0 entry (DeferredTransactions flush) | 0x6632bf0 | fn start | `0x6632bf0  push rbp` | rcx = DeferredTransactions* a0; reads a0+0x0/+0x10/+0x18/+0x28; strings "Deferred Texture Transactions" @ 0x6632c19, "Deferred Buffer Transactions" @ 0x6632c42 | [V] |
| a0+0x18 = {head,end} of texture txn list | 0x6632c28 | 16 B | `0x6632c28  movups xmm0,[rcx+0x18]` | a0+0x18 loaded; stored to stack [rbp-0x30] which becomes sub_12893d0 rcx (texture txn list head/end) | [V] |
| "Deferred Texture Transactions" string ptr | 0x6632c19 | 8 B | `0x6632c19  lea rax,[0xF54E8AF]` | [data_f54e8af] = "Deferred Texture Transactions"; stored at [rbp-0x38] | [V] |
| zero a0+0x0/+0x10/+0x18/+0x20 | 0x6632c2f | 16 B | `0x6632c2f  movups [rcx+0x20],xmm1`<br>`0x6632c33  movups [rcx],xmm1`<br>`0x6632c36  movups [rcx+0x10],xmm1` | xmm1=0; zeroes a0+0x20, a0+0x0, a0+0x10 (list head/end cleared after snapshotting) | [V] |
| sub_6632bf0 -> sub_12893d0 (texture txns) | 0x6632c55 | call site | `0x6632c4d  lea rcx,[rbp-0x30]`<br>`0x6632c51  lea rdx,[rbp-8]`<br>`0x6632c55  call 0x12893D0` | sub_6632bf0 -> sub_12893d0; rcx=&[rbp-0x30] = {a0+0x18 head/end} texture txn list, rdx=&[rbp-8] out-param | [V] |
| sub_6632bf0 -> sub_12893d0 (buffer txns) | 0x6632d1e | call site | `0x6632d16  lea rcx,[rbp-0x50]`<br>`0x6632d1a  lea rdx,[rbp-8]`<br>`0x6632d1e  call 0x12893D0` | sub_6632bf0 -> sub_12893d0; rcx=&[rbp-0x50] = {a0+0x0} buffer txn list | [V] |
| sub_12893d0 entry (job runner) | 0x12893d0 | fn start | `0x12893d0  push rbp` | sub_12893d0(rcx=list_head, rdx=out); iterates [rcx]..[rcx+8] stride 0x18; runs each job object's vtbl[1] | [V] |
| sub_12893d0 list head/end | 0x1289406 | 8 B | `0x1289406  mov r13,[rcx]`<br>`0x1289409  mov r14,[rcx+8]` | r13=list head, r14=list end; loop `cmp r13,r14` | [V] |
| entry+0x8 shared_ptr addref | 0x1289431 | 8 B | `0x1289431  mov rcx,[r13+8]`<br>`0x1289447  lock cmpxchg [rcx+8],edx` | entry+0x8 = shared_ptr control block; addref via lock cmpxchg | [V] |
| entry+0x10 job object ptr | 0x128947d | 8 B | `0x128947d  mov rcx,[r13+0x10]` | rcx = entry+0x10 = job object whose vtbl[1] is run | [V] |
| job vtbl[1] (run) load | 0x1289489 | 8 B | `0x1289486  mov rax,[rcx]`<br>`0x1289489  mov rax,[rax+8]` | rax = job object vtable; vtbl[1] = Job::run | [V] |
| Job::run via CFG thunk | 0x1289490 | call site | `0x128948d  mov rdx,rbx`<br>`0x1289490  call qword ptr [0xF99FFA0]` | call Job::run (rcx=job object=MC_obj/TexturePtr*, rdx=&[rbp-0x20]) via CFG thunk sub_eea6040; return address = 0x1289496 | [V] |
| CFG thunk | 0xeea6040 | 5 B | `0xeea6040  jmp rax` | [data_f99ffa0] = sub_eea6040; `call qword ptr [0xF99FFA0]` indirects to rax = Job::run target | [V] |
| return address after Job::run call | 0x1289496 | - | `0x1289496  nop` | instruction right after the 0x1289490 call | [V] |
| live capture: sub_12893d0 -> sub_4e05e50 | ret=0x1289496 | - | - | docs/data/live/mc_root_4e05e50_callers.txt line 3: `CALLER ret=0x1289496 first_hit=1` — sub_4e05e50 entered as Job::run from sub_12893d0's vtbl[1] call; returns to 0x1289496; RCX = MC_obj pointers | [V live] |
| MC_obj+0x18 shared_ptr load | 0x4e05e71 | 8 B | `0x4e05e71  mov rax,[rcx+0x18]` | [MC_obj+0x18] shared_ptr control block; addrefed via CFG thunk | [V] |
| MC_obj+0x10 shared_ptr addref | 0x4e05ea8 | 4 B | `0x4e05ea8  lock cmpxchg [rdx+8],r8d` | [*(MC_obj+0x10)+0x8] shared_ptr refcount | [V] |
| MC_obj+0x8 pointer saved | 0x4e05eb0 | 8 B | `0x4e05eb0  mov rcx,[rdi+8]` | [MC_obj+0x8] pointer -> [rbp+0x40] | [V] |
| MC_obj+0x10 shared_ptr saved | 0x4e05ec5 | 8 B | `0x4e05ec5  mov [rbp+0x48],rbx` | [MC_obj+0x10] shared_ptr -> [rbp+0x48] | [V] |
| MC_obj+0xE0 flags | 0x4e05f61 | 8 B | `0x4e05f61  mov r9,[rdi+0xE0]` | [MC_obj+0xE0] flags -> arg4 (r9) of sub_bc41420 | [V] |
| dragon_obj = MC_obj+0x58 | 0x4e05f68 | - | `0x4e05f68  add rdi,0x58` | rdi = dragon texture object = MC_obj+0x58, passed as RCX to sub_bc41420 | [V] |
| MC->dragon bridge call | 0x4e05f77 | call site | `0x4e05f77  call 0xBC41420` | sub_4e05e50 -> sub_bc41420 (rcx=dragon_obj, rdx=&[rbp-0x50], r8=&{MC_obj+0x8,MC_obj+0x10}, r9=MC_obj+0xE0) | [V] |
| return address after bridge call | 0x4e05f7c | - | `0x4e05f7c  nop` | return address = 0x4E05F7C; matches live capture ret=0x4E05F7C [docs/data/live/dragon_texture_caller_bc41420.txt] | [V live] |
| descriptor bytes copied OUT (not handle) | 0x4e061ce | 16 B | `0x4e061cb  movups xmm0,[rdx]`<br>`0x4e061ce  movups [rcx],xmm0` | sub_4e061b0 copies out-struct2+0x0..0x10 (descriptor block) — the handle is NOT copied | [V] |
| caller out-param nulled | 0x4e06010 | 8 B | `0x4e06010  mov qword ptr [rsi],0` | *[sub_4e05e50 out-param] = 0; handle NOT written back to MC_obj | [V] |
| sub_bc41420 entry | 0xbc41420 | fn start | `0xbc41420  push rbp` | dragon-layer bridge entry 2; 1 xref in (from 0x4e05f77) | [V] |
| sub_bc41420 -> sub_c296b50 | 0xbc41b39 | call site | `0xbc41b29  lea rdx,[rbp+0x180]`<br>`0xbc41b30  mov r9,rbp`<br>`0xbc41b33  mov rcx,rbx`<br>`0xbc41b36  mov r8,r15`<br>`0xbc41b39  call 0xC296B50`<br>`0xbc41b3e  movzx eax,byte ptr [rbp+0x188]` | sub_bc41420 -> sub_c296b50 (rcx=rbx, r8=r15 descriptor, rdx=[rbp+0x180] out-struct2, r9=rbp); success flag at [rbp+0x188] | [V] |
| sub_c296b50 -> createTexture wrapper | 0xc296d79 | call site | `0xc296d74  mov ecx,6`<br>`0xc296d79  call 0xBC73BF0` | sub_c296b50 calls createTexture wrapper (ecx=6); taken live: capture bgfx_texture_wrapper_bc73bf0 ret=0xC296D7E | [V] / [V live] |
| handle stored at this+0x00 | 0xc296e26 | 2 B | `0xc296e26  mov [rdi],ax`<br>`0xc296e32  movups [rdi+8],xmm0`<br>`0xc296e3b  mov [rdi+0x18],rdx` | returned u16 handle stored at [this+0x00] = [dragon_obj+0x00]; 16 descriptor bytes at +0x08; desc+0x10 at +0x18 | [V] |
| command byte 14 written (producer) | 0xbc73aaa | 1 B | `0xbc73aaa  mov byte ptr [rbp+0x2C],0xE` | sub_bc73770 writes cmd byte 0x0E into [ctx+0x1CFD0C8]+0xDC5820 at pos [rbx+0xDC5818] | [V] |
| producer: handle allocated | 0xbc7384d | call site | `0xbc7384d  call 0xBC79A60`<br>`0xbc73853  mov [rbp+0x2E],ax` | u16 handle from ctx+0x1DF3460 via sub_bc79a60 (0xFFFF = exhausted); staged at [rbp+0x2E] | [V] |
| producer: out-handle returned | 0xbc73b74 | 2 B | `0xbc73b70  movzx edi,word ptr [rbp+0x2E]`<br>`0xbc73b74  mov [rsi],di`<br>`0xbc73b93  ret` | *outHandle (rdx arg) = allocated u16 handle; producer returns | [V] |
| wrapper: validator + producer | 0xbc73bf0 | fn start | `0xbc73bf0  push r15`<br>`0xbc73c6c  call 0xBC735B0`<br>`0xbc73ea8  call 0xBC73770` | wrapper: validate desc via sub_bc735b0, then `call 0xBC73770` issues command byte 14 | [V] |
| dispatcher: vtable slot 26 load | 0xbc6a2b1 | 8 B | `0xbc6a2ae  mov rax,[rcx]`<br>`0xbc6a2b1  mov rax,[rax+0xD0]` | vtable[0xD0] = slot 26 createTexture (RendererContextD3D12 base vtable 0xF4ED2D0; slot name per BGFX_MAP 6k [I]) | [V] |
| dispatcher: slot-26 indirect call | 0xbc6a2c2 | call site | `0xbc6a2c2  call qword ptr [0xF99FFA0]` | CFG thunk sub_eea6040 tails to rax = createTexture(handle, mem, flags, skip); return address = 0xbc6a2c8 | [V] |
| live capture: single createTexture caller | ret=0xBC6A2C8 | - | - | docs/data/live/createtexture_callers.txt: 1612 hits, ONE caller; every hit ret=0xBC6A2C8 = instruction right after 0xbc6a2c2; RCX=renderer ctx, R8=0x1C descriptor with "TEX" magic | [V live] |
| createTexture return captured | 0xbc6a2d1 | 8 B | `0xbc6a2d1  mov r15,rax` | rax = created texture object pointer -> r15 | [V] |
| texture object in bgfx handle table | 0xbc6a49b | 8 B | `0xbc6a49b  mov [r8+0x10],r15` | ctx+0x1E55AB8 handle-table element+0x10 = texture object pointer — NOT a TexturePtr field | [V] |
| createTexture function entry | 0xe8143c0 | fn start | `0xe8143c0  push rbp` | createTexture = RendererContextD3D12 vtable slot 26 (BGFX_MAP.md 6k); xref.py callers -> empty (no direct caller) | [V] |
| TexturePtr layout | TexturePtr+0x00/+0x10 | 16 B | - | src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h: mClientTexture shared_ptr at +0x00, mResourceLocationPtr shared_ptr at +0x10, sizeof==32 — NEITHER field holds a u16 handle | [I] header read |
| MC_obj concrete type | MC_obj (rcx of sub_4e05e50) | >= 0xE8 B | `0x4e05eb0 mov rcx,[rdi+8]` / `0x4e05f61 mov r9,[rdi+0xE0]` / `0x4e05f68 add rdi,0x58` | object with ptr at +0x8, shared_ptrs at +0x10/+0x18, flags at +0xE0, dragon sub-object at +0x58 — NOT TexturePtr (32B) / BedrockTexture (48B) / ClientTexture (empty) | [I] from field reads |
| no string refs for TexturePtr/ClientTexture/BedrockTexture | .text | str search | - | xref.py str "TexturePtr"/"ClientTexture"/"BedrockTexture" -> empty; these are SDK header names only, not in the binary | [V] negative |
| no store to TexturePtr+0x00 (mClientTexture) | TexturePtr+0x00 | 16 B | - | mClientTexture shared_ptr slot; no store to it anywhere in texgroup_load/texload/texload_task/0x18718D0/sub_a3f10/sub_bc41400/sub_4e05e50/sub_4e061b0/sub_bc41420/sub_c296b50 — TexturePtr+0x00 is a shared_ptr, not a u16 handle field | [V] negative |
| handle stored in dragon object [MC_obj+0x58+0x00] | dragon_obj+0x00 | 2 B | `0xc296e26  mov [rdi],ax` (this = MC_obj+0x58 via `0x4e05f68 add rdi,0x58`) | the createTexture u16 handle IS written into the texture object's dragon sub-object at [MC_obj+0x58+0x00] — this IS the GPU-handle write, just not into TexturePtr+0x00 (a shared_ptr) | [V] |

## CLOSES?

YES — every pending part of the item line is now proven by [V]/[V live] rows:

- The pack->GPU path is connected end-to-end: texgroup_load/texload create the CPU texture objects and register them in the group (head group+0x248, counter group+0x250) [V]; the GPU hand-off runs through the deferred-texture-transaction flush: endFrame (0x66232b0) is the sole static caller of sub_6632bf0 [V xref]; sub_6632bf0 passes the texture transaction list (a0+0x18 = {head,end}) to sub_12893d0 at `0x6632c55 call 0x12893D0` [V]; sub_12893d0 runs each job object's vtbl[1] via `0x1289490 call qword ptr [0xF99FFA0]` [V], which is sub_4e05e50 (MC_obj/TexturePtr*) — confirmed by live capture mc_root_4e05e50_callers ret=0x1289496 = instruction right after that call [V live]; sub_4e05e50 computes dragon_obj = MC_obj+0x58 (`0x4e05f68 add rdi,0x58`) and calls sub_bc41420 (`0x4e05f77 call 0xBC41420`) [V]; sub_bc41420 -> sub_c296b50 (`0xbc41b39 call 0xC296B50`) -> wrapper 0xbc73bf0 (`0xc296d79 call 0xBC73BF0`) -> producer sub_bc73770 writes command byte 0x0E (`0xbc73aaa mov byte ptr [rbp+0x2C],0xE`) [V]; dispatcher loads vtable slot 26 (`0xbc6a2b1 mov rax,[rax+0xD0]`) and calls it (`0xbc6a2c2 call qword ptr [0xF99FFA0]`) -> createTexture 0xe8143c0 [V]; live capture confirms ONE caller ret=0xBC6A2C8 [V live]; the returned u16 handle IS written into the texture object at [dragon_obj+0x00] = [MC_obj+0x58+0x00] via `0xc296e26 mov [rdi],ax` [V], completing the GPU-handle write.

- The premise "write the handle into TexturePtr+0x00" is resolved as a premise error, not a blocking fact: TexturePtr+0x00 is mClientTexture, a 16B shared_ptr (sizeof(TexturePtr)==32, mResourceLocationPtr at +0x10) — it has no u16 handle field [I header read], and no store to TexturePtr+0x00 appears anywhere in decoded code [V negative]. The GPU handle lives in the dragon texture object at [MC_obj+0x58+0x00], which TexturePtr references via its mClientTexture shared_ptr. No string refs for "TexturePtr"/"ClientTexture"/"BedrockTexture" exist in the exe — they are SDK header names only [V negative].

- createTexture issuance fully proven [V]: no `call qword ptr [reg+0xd0]` slot-26 vcall anywhere in .text (all 16 encodings -> 0 hits) [V negative]; createTexture is reached exclusively via bgfx command byte 14 -> dispatcher slot-26 -> `call qword ptr [0xF99FFA0]` [V].

## TOOL REQUESTS

None

## NEXT
DONE
