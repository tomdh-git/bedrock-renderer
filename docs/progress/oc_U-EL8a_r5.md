## NEXT
DONE

# Unit U-EL8a — L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk); pack->GPU path pending

Scope (checklist item L8a, docs/RENDER_CHECKLIST.md line 344): "[ ] L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk) — pack->GPU path pending". Do ONLY the pending part: does the pack->GPU path contain a createTexture issuance (RendererContext slot 26 = 0xe8143c0 via [reg+0xd0] vcall, or bgfx command byte 14 -> handler 0xbc69487) and a GPU-handle write into TexturePtr/ClientTexture? SDK headers are stubs (TexturePtr.h 32B two shared_ptr; BedrockTexture.h 48B three shared_ptr; ClientTexture.h empty carrier; TextureGroup.h stub) — header layout is NOT the pending part.

Method: static analysis only; RVAs relative to image base; every claim [V] = verbatim from disassembly (cite RVA), [I] = inferred (say from what), [?] = unknown. Verbatim `0xRVA  instr` lines below are copied exactly from rdis.exe output (two spaces after the address). One row per distinct offset, all its sites listed; meaning ONLY where an instruction/string shows it, else '-'. No input data pasted as-is; no raw instruction lines outside table cells; no catch-all rows.

## Prior attempts (read first, do NOT redo)

- docs/progress/oc_U-EL8a_r1.md (109-row field table): texgroup_load 0x5421c90..0x54235a0, texload 0x58a1310..0x58a23d0, texload_task 0x541bf00, decode chain sub_1994f90 -> sub_764950 -> sub_777ed0 — all CPU-side object creation + group insert (head group+0x248, counter group+0x250), ending at `0x54227af  call 0x18718D0`. No createTexture, no slot-26 vcall, no GPU-handle store anywhere. CLOSES? NO.
- docs/progress/oc_U-EL8a_r2.md: decoded callee 0x18718D0 (0x18718d0..0x1871ae4: CPU slot-array bookkeeping over texture+0x30) and sub_186dac0 (0x186dac0..0x186dffc: CPU shared_ptr/string bookkeeping). Negative sweeps: xref.py callers 0xe8143c0 empty; callers 0xbc69487 none; str "createTexture" none; all 16 encodings of `call qword ptr [reg+0xd0]` -> 0 hits. CLOSES? NO.
- docs/progress/oc_U-EL8a_r3.md: caller scans (22 callers of 0x18718D0 = generic slot allocator; callers of texgroup_load/texload/texload_task) — none reach createTexture. RendererContextD3D12 vtable base 0xF4ED2D0, slot 26 (+0x0D0) = 0xe8143c0 createTexture per BGFX_MAP.md 6k [I]. CLOSES? NO.
- docs/progress/oc_U-EL8a_r4.md: command-byte-14 producer chain located — sub_bc73770 writes byte 0x0E + [u16 handle][u64 Memory*][u32 flags][u8 skip=0] into [ctx+0x1CFD0C8]+0xDC5820 at pos [rbx+0xDC5818], allocates the u16 handle via sub_bc79a60 at ctx+0x1DF3460, returns *outHandle; thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120; dragon-layer entry points 0xc296b50/0xc297000/0xc2a3d90/0xbc63c80. vtable 0xEFCA580 slot 4 = sub_a3f10 is NOT a createTexture caller. None of this unit's functions call any producer address; grep of docs/data/listings negative; no GPU-handle store to TexturePtr+0x00. CLOSES? NO (blocking fact: handle not connected to TexturePtr/ClientTexture from this unit).

## This attempt (step 2): dispatcher case decoded, live capture read, producer chain re-verified, handle trace attempted

### (1) Who PRODUCES command byte 14

sub_bc73770 (ctx rcx, &outHandle rdx, Memory* r8, flags r9d): `0xbc73aaa  mov byte ptr [rbp+0x2C],0xE` writes cmd byte 0x0E into the command buffer [rbx+0xDC5820] at pos [rbx+0xDC5818] (rbx = [ctx+0x1CFD0C8]), then five memcpy (sub_ebce390) calls append [u16 handle @rbp+0x2E][u64 mem @rbp+0x18][u32 flags @rbp+0x28][u8 skip=0 @rbp+0x2D], bumping pos after each; the handle is allocated by `0xbc7384d  call 0xBC79A60` from ctx+0x1DF3460 (0xFFFF = exhausted) and `0xbc73b74  mov [rsi],di` returns *outHandle. Argument order [u16 handle][u64 mem][u32 flags][u8 skip] matches the handler's read order exactly (0xbc6a2a9..0xbc6a2b1 load handle/mem/flags/skip from the same stack slots the command reader filled).

The producer is called ONLY by thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 (xref fresh: 0xbc73770 -> those three only). Each wrapper validates the texture desc via sub_bc735b0 (`0xbc73c6c  call 0xBC735B0`), builds the 0x18-byte createTexture header with the "TEX" magic (`0xbc73dcc  mov dword ptr [rsp+0x34],0x584554`), copies 0x18 bytes via the CFG thunk (`0xbc73e84  call qword ptr [0xF99FFA0]`), then issues the command (`0xbc73ea8  call 0xBC73770`) and reads back the handle (`0xbc73ead  movzx eax,word ptr [rsp+0x32]`). Wrapper xrefs (fresh): 0xbc73bf0 -> 0xbc63c80, 0xc296b50, 0xc297000, 0xc2a3d90 (dragon-layer entry points); 0xbc73ed0 -> 0xc296b50, 0xc2a3d90; 0xbc74120 -> 0xc296b50, 0xc2a3d90.

### (2) Trace the returned handle into TexturePtr/ClientTexture

Consumer side (dispatcher case block at 0xBC6A28C, reached from the command executor): `0xbc6a28f  mov rcx,[rdi+0x1EBF2D0]` (renderer ctx), `0xbc6a2ae  mov rax,[rcx]`, `0xbc6a2b1  mov rax,[rax+0xD0]` (vtable slot 26 = createTexture), `0xbc6a2c2  call qword ptr [0xF99FFA0]` (CFG thunk `0xeea6040  jmp rax` tails to rax). Return address = 0xbc6a2c8 (`0xbc6a2c8  test rax,rax`), `0xbc6a2d1  mov r15,rax` captures the created texture object pointer, guard byte `0xbc6a2e3  movzx ecx,byte ptr [rdi+0x1E7DAD0]` for handles >= 0x1000, then `0xbc6a31b  lea rcx,[rdi+0x1E55AB8]` / `0xbc6a322  call 0xBC7A3D0` walk the paged handle table and `0xbc6a49b  mov [r8+0x10],r15` stores the texture object pointer at handle-table element+0x10.

Live capture [V live]: docs/data/live/createtexture_callers.txt (capture createtexture_callers, rva=0xE8143C0): 1612 hits collapse to ONE caller; every hit line has ret=0xBC6A2C8 — exactly the instruction after the 0xbc6a2c2 call — confirming createTexture is issued from the bgfx command-buffer dispatcher, NOT from the MC texture code. RCX = renderer ctx (0x5314A010000); R8 points at a 0x1C-byte create descriptor (dword size 0x1C at +8, "TEX" magic 0x584554 at +0x10 inside the tag field, u32 0x43 at +0x14, u16 width/u16 height at +0x18/+0x1A).

The handle trace stops at the bgfx boundary: *outHandle goes back through the wrapper to the dragon-layer caller; the texture object pointer lives only in ctx+0x1E55AB8 element+0x10. No store to TexturePtr+0x00 (mClientTexture shared_ptr) appears anywhere in texgroup_load/texload/texload_task/0x18718D0/sub_186dac0, none of those functions calls the producer/wrappers/dragon entries (grep of docs/data/listings for bc73770/bc73bf0/bc73ed0/bc74120/c296b50/c297000/c2a3d90/e8143c0 -> no matches), and vtable 0xEFCA580 slot 4 (sub_a3f10, `0xa3f10  push rsi`) stores interface vtables and decrefs only — NOT a createTexture caller. The producer is not statically reachable from this unit; the handle->TexturePtr/ClientTexture wiring is in the dragon-layer frame-time path, outside U-EL8a.

## ANSWER TABLE — pack->GPU createTexture issuance and handle trace (one row per distinct offset; proof lines verbatim from rdis unless tagged [V live]/[I])

| name | rva or offset | size | verbatim `0xRVA  instr` proof line(s) | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| createTexture function entry | 0xe8143c0 | fn start | `0xe8143c0  push rbp` | createTexture = RendererContextD3D12 vtable slot 26 (base vtable 0xF4ED2D0 +0x0D0 per BGFX_MAP.md 6k [I]); preflight: 0 xrefs in — no direct caller anywhere in .text | [V] |
| createTexture args staged | 0xe8143e3 | 4/8 B | `0xe8143e3  mov [rbp+0x28],r9d`<br>`0xe8143e7  mov r14,r8`<br>`0xe8143ef  mov [rbp+0x2E],dx` | flags -> [rbp+0x28]; mem (r8) -> r14; handle (dx) -> [rbp+0x2E] | [V] |
| CFG thunk | 0xeea6040 | 5 B | `0xeea6040  jmp rax` | [data_f99ffa0] = sub_eea6040; `call qword ptr [0xF99FFA0]` indirects through it to rax = slot 26 target | [V] |
| command args read from stream-parsed stack slots | 0xbc6a2a9 | 2 B | `0xbc6a296  movzx r10d,byte ptr [rsp+0x6A]`<br>`0xbc6a29c  mov r9d,[rsp+0x90]`<br>`0xbc6a2a4  mov r8,[rsp+0x60]`<br>`0xbc6a2a9  movzx edx,word ptr [rsp+0x6E]` | case 14 reads fields the command reader placed on the stack: skip=r10b, flags=r9d, mem=r8, handle u16=edx | [V] |
| renderer context load | 0xbc6a28f | 8 B | `0xbc6a28f  mov rcx,[rdi+0x1EBF2D0]` | rcx = RendererContext object from command-buffer context | [V] |
| vtable pointer load | 0xbc6a2ae | 8 B | `0xbc6a2ae  mov rax,[rcx]` | rax = vtable pointer | [V] |
| slot 26 function pointer | 0xbc6a2b1 | 8 B | `0xbc6a2b1  mov rax,[rax+0xD0]` | rax = vtable[0xD0] = slot 26 createTexture | [V] |
| slot 26 indirect call | 0xbc6a2c2 | call site | `0xbc6a2c2  call qword ptr [0xF99FFA0]` | CFG thunk sub_eea6040 tails to rax = createTexture(handle u16=edx, mem r8, flags r9d, skip r10b); return address = 0xbc6a2c8 | [V] |
| live capture: single caller | 0xbc6a2c8 (ret) | - | - | live capture createtexture_callers (capture at 0xE8143C0): 1612 hits, ONE caller; every hit ret=0xBC6A2C8 = instruction right after the 0xbc6a2c2 call; RCX=5314A010000 renderer ctx; R8 = 0x1C-byte descriptor (dword size 0x1C at +8, "TEX" magic at +0x10 inside tag field, u32 0x43 at +0x14, u16 width/u16 height at +0x18/+0x1A) [docs/data/live/createtexture_callers.txt] | [V live] |
| createTexture return captured | 0xbc6a2d1 | 8 B | `0xbc6a2d1  mov r15,rax` | rax = created texture object pointer -> r15 | [V] |
| guard byte load | 0xbc6a2e3 | 1 B | `0xbc6a2e3  movzx ecx,byte ptr [rdi+0x1E7DAD0]` | ctx+0x1E7DAD0 flag required for handles >= 0x1000 | [V] |
| handle-table base | 0xbc6a31b | 8 B | `0xbc6a31b  lea rcx,[rdi+0x1E55AB8]` | rcx = ctx+0x1E55AB8 paged per-handle table (0x28-byte elements per BGFX_MAP.md 6et [I]) | [V] |
| table page walk | 0xbc6a322 | call site | `0xbc6a322  call 0xBC7A3D0` | walk/create the page holding the handle's element | [V] |
| texture object stored in handle table | 0xbc6a49b | 8 B | `0xbc6a49b  mov [r8+0x10],r15` | element+0x10 = texture object pointer; this is where the created object lives — NOT a TexturePtr field | [V] |
| TEX magic gate | 0xbc695a3 | 4 B | `0xbc695a3  cmp dword ptr [rsp+0x8C],0x584554`<br>`0xbc695ae  jne 0xBC6A28C` | handler requires MemoryReader u32 == 0x00584554 ('TEX'); the case block continues at 0xBC6A28C -> slot-26 call | [V] |
| command byte 14 handler entry | 0xbc69487 | fn start | `0xbc69487  and edx,0xFFFFFFFE` | bgfx command executor case 14 = createTexture: reads [u16 handle][u64 mem][u32 flags][u8 skip] | [V] |
| producer entry | 0xbc73770 | fn start | `0xbc73770  push rbp` | sub_bc73770(ctx rcx, &outHandle rdx, Memory* r8, flags r9d): API-thread producer of command byte 14 | [V] |
| skip = 0 staged | 0xbc7379b | 1 B | `0xbc7379b  mov byte ptr [rbp+0x2D],0` | skip byte = 0 | [V] |
| flags/mem staged | 0xbc7379f | 4 B | `0xbc7379f  mov [rbp+0x28],r9d`<br>`0xbc737a3  mov [rbp+0x18],r8` | flags -> [rbp+0x28]; Memory* -> [rbp+0x18] | [V] |
| handle allocated | 0xbc7384d | call site | `0xbc7384d  call 0xBC79A60`<br>`0xbc73853  mov [rbp+0x2E],ax` | u16 handle from ctx+0x1DF3460 (0xFFFF = exhausted); staged at [rbp+0x2E] | [V] |
| command byte 14 written | 0xbc73aaa | 1 B | `0xbc73aaa  mov byte ptr [rbp+0x2C],0xE` | writes cmd byte 0x0E as first field | [V] |
| buffer base/pos | 0xbc73aae | 4 B | `0xbc73aae  mov eax,[rbx+0xDC5818]`<br>`0xbc73ab8  add rcx,0xDC5820` | pos from [rbx+0xDC5818]; data base [rbx+0xDC5820]; rbx = [ctx+0x1CFD0C8] | [V] |
| byte 0x0E memcpy | 0xbc73ac9 | call site | `0xbc73ac9  call 0xEBCE390` | memcpy(data+pos, &byte 0x0E, 1) (sub_ebce390 = memcpy) | [V] |
| pos bump +2 | 0xbc73ae2 | 4 B | `0xbc73ae2  mov [rbx+0xDC5818],ecx` | pos = align2(pos)+2 | [V] |
| handle memcpy | 0xbc73af5 | call site | `0xbc73af5  call 0xEBCE390` | memcpy(data+pos, [rbp+0x2E], 2) | [V] |
| mem memcpy | 0xbc73b1a | call site | `0xbc73b1a  call 0xEBCE390` | memcpy(data+pos, [rbp+0x18], 8) | [V] |
| flags memcpy | 0xbc73b3f | call site | `0xbc73b3f  call 0xEBCE390` | memcpy(data+pos, [rbp+0x28], 4) | [V] |
| skip memcpy + pos++ | 0xbc73b64 | call site | `0xbc73b64  call 0xEBCE390`<br>`0xbc73b6a  inc dword ptr [rbx+0xDC5818]` | memcpy(data+pos, [rbp+0x2D], 1) (skip=0); pos++ | [V] |
| out-handle returned | 0xbc73b74 | 2 B | `0xbc73b70  movzx edi,word ptr [rbp+0x2E]`<br>`0xbc73b74  mov [rsi],di`<br>`0xbc73b93  ret` | *outHandle (rdx arg) = allocated u16 handle; producer returns | [V] |
| producer xrefs | 0xbc73770 | xref | - | xref.py callers 0xbc73770 -> 0xbc73bf0, 0xbc73ed0, 0xbc74120 (thin wrappers) only | [V] |
| wrapper entry + validator | 0xbc73bf0 | fn start | `0xbc73bf0  push r15`<br>`0xbc73c6c  call 0xBC735B0` | wrapper: validate texture desc via sub_bc735b0, then issue command byte 14 | [V] |
| wrapper builds header + calls producer | 0xbc73dcc | 4 B | `0xbc73dcc  mov dword ptr [rsp+0x34],0x584554`<br>`0xbc73e84  call qword ptr [0xF99FFA0]`<br>`0xbc73ea8  call 0xBC73770`<br>`0xbc73ead  movzx eax,word ptr [rsp+0x32]` | "TEX" magic dword (0x584554) written into the 0x18-byte createTexture header; 0x18 bytes copied via CFG thunk; `call 0xBC73770` issues the command; handle read back | [V] |
| wrapper xrefs | 0xbc73bf0 | xref | - | xref.py callers 0xbc73bf0 -> 0xbc63c80, 0xc296b50, 0xc297000, 0xc2a3d90 (dragon-layer entry points); 0xbc73ed0 -> 0xc296b50, 0xc2a3d90; 0xbc74120 -> 0xc296b50, 0xc2a3d90 | [V] |
| no direct createTexture call | 0xe8143c0 | - | - | xref.py callers 0xe8143c0 -> empty; preflight: 0 xrefs in | [V] (negative) |
| no [reg+0xd0] vcall anywhere | .text | - | - | all 16 `call qword ptr [reg+0xd0]` encodings (rax..r15) -> 0 hits each | [V] (negative) |
| producer absent from L8a listings | docs/data/listings | - | - | grep bc73770/bc73bf0/bc73ed0/bc74120/c296b50/c297000/c2a3d90/e8143c0 -> no matches in any listing | [V] (negative) |
| producer absent from L8a callees | texgroup_load/texload_task | - | - | texgroup_load tail calls: 0xE935700, 0x5424000, 0x5424130, 0xEEC6EB0, 0x78ED0, 0x18718D0; texload_task calls: 0x1994F90, 0xE935700, 0x78ED0, 0x9BC830 — none is the producer/wrapper/dragon entry | [V] (negative) |
| texture-object init NOT the producer | vtable 0xEFCA580 +0x020 | 8 B | `0xa3f10  push rsi` | slot 4 = sub_a3f10 (per prior attempt r4 [V]): stores interface vtables at +0x00/+0x90/+0xA8, decrefs via sub_eea6040; NO bgfx call, NO command-byte-14 write — NOT the createTexture producer | [V] (negative) |
| no GPU-handle store in L8a | TexturePtr+0x00 | 16 B | - | mClientTexture shared_ptr; no store to it anywhere in texgroup_load/texload/texload_task/0x18718D0/sub_186dac0 | [V] (negative) |

## CLOSES?

NO — the createTexture issuance is fully proven [V]: command byte 14 is produced by sub_bc73770 (writes 0x0E + [u16 handle][u64 Memory*][u32 flags][u8 skip=0] into [ctx+0x1CFD0C8]+0xDC5820 at pos [rbx+0xDC5818], allocates the u16 handle via sub_bc79a60 at ctx+0x1DF3460, returns *outHandle at 0xbc73b74), issued through thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 (xref: 0xbc73bf0 -> 0xbc63c80/0xc296b50/0xc297000/0xc2a3d90), and consumed by the dispatcher case block at 0xBC6A28C which loads vtable slot 26 (`0xbc6a2b1  mov rax,[rax+0xD0]`) and calls it via `0xbc6a2c2  call qword ptr [0xF99FFA0]`; live capture createtexture_callers confirms ONE caller, ret=0xBC6A2C8 (the instruction after that call), RCX = renderer ctx, R8 = 0x1C-byte descriptor with "TEX" magic; the returned texture object pointer (rax->r15 at 0xbc6a2d1) is stored in the bgfx per-handle table at element+0x10 (`0xbc6a49b  mov [r8+0x10],r15`, ctx+0x1E55AB8).
BUT the GPU-handle write into TexturePtr/ClientTexture is NOT proven and is not present in this unit: no store to TexturePtr+0x00 (mClientTexture) anywhere in texgroup_load/texload/texload_task/0x18718D0/sub_186dac0, none of those functions calls the producer/wrappers/dragon entries (grep of docs/data/listings negative), and vtable 0xEFCA580 slot 4 (sub_a3f10) is NOT a createTexture caller. Single blocking fact: the handle returned by createTexture and the texture object pointer in ctx+0x1E55AB8 element+0x10 are never connected to any TexturePtr/ClientTexture/BedrockTexture field from within this unit — the pack->GPU hand-off into the MC texture objects is deferred to the dragon-layer frame-time path (outside U-EL8a).

## TOOL REQUESTS

None

## NEXT
step 2
