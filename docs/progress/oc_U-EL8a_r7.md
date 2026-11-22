## NEXT
DONE

# Unit U-EL8a — L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk); pack->GPU path pending

Scope (checklist item L8a, docs/RENDER_CHECKLIST.md line 344): "[ ] L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk) — pack->GPU path pending". Do ONLY the pending part: does the pack->GPU path (texgroup_load 0x5421c90 / texload 0x58a1310 / texload_task 0x541bf00 / decode chain) contain a createTexture issuance (RendererContext slot 26 = 0xe8143c0 via [reg+0xd0] vcall, or bgfx command byte 14 -> handler 0xbc69487) and a GPU-handle write into TexturePtr/ClientTexture? SDK headers are stubs (TexturePtr.h 32B two shared_ptr; BedrockTexture.h 48B three shared_ptr; ClientTexture.h empty carrier; TextureGroup.h stub) — header layout is NOT the pending part.

Method: static analysis only; RVAs relative to image base; every claim [V] = verbatim from disassembly (cite RVA), [I] = inferred (say from what), [V live] = live capture, [?] = unknown. Sizes from the instruction. One row per distinct offset, all its sites listed; meaning ONLY where an instruction/string shows it, else '-'. No input data pasted as-is; no raw instruction lines outside table cells; no catch-all rows.

## Prior attempts (read first, do NOT redo)

- docs/progress/oc_U-EL8a_r1.md (109-row field table): fully decoded texgroup_load 0x5421c90..0x54235a0, texload 0x58a1310..0x58a23d0, decode chain sub_1994f90 -> sub_764950 -> sub_777ed0, texload_task 0x541bf00. All CPU-side object creation + group insert (head group+0x248, counter group+0x250), ending at `0x54227af  call 0x18718D0`. No createTexture, no slot-26 vcall, no GPU-handle store anywhere. CLOSES? NO.
- docs/progress/oc_U-EL8a_r2.md: decoded callee 0x18718D0 (0x18718d0..0x1871ae4, CPU slot-array bookkeeping over texture+0x30) and sub_186dac0 (0x186dac0..0x186dffc, CPU shared_ptr/string bookkeeping). Negative sweeps: xref.py callers 0xe8143c0 empty; callers 0xbc69487 none; str "createTexture" none; all 16 encodings of `call qword ptr [reg+0xd0]` -> 0 hits each. CLOSES? NO.
- docs/progress/oc_U-EL8a_r3.md: caller scans (22 callers of 0x18718D0 = generic slot allocator; callers of texgroup_load/texload/texload_task) — none reach createTexture. RendererContextD3D12 vtable base 0xF4ED2D0, slot 26 (+0x0D0) = 0xe8143c0 createTexture per BGFX_MAP.md 6k [I]. CLOSES? NO.
- docs/progress/oc_U-EL8a_r4.md: command-byte-14 producer chain located — sub_bc73770 writes byte 0x0E + [u16 handle][u64 Memory*][u32 flags][u8 skip=0] into [ctx+0x1CFD0C8]+0xDC5820 at pos [rbx+0xDC5818], allocates the u16 handle via sub_bc79a60 at ctx+0x1DF3460, returns *outHandle; thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120; dragon-layer entry points 0xc296b50/0xc297000/0xc2a3d90/0xbc63c80. vtable 0xEFCA580 slot 4 = sub_a3f10 is NOT a createTexture caller. None of this unit's functions call any producer address; grep of docs/data/listings negative; no GPU-handle store to TexturePtr+0x00. CLOSES? NO (blocking fact: handle not connected to TexturePtr/ClientTexture from this unit).
- docs/progress/oc_U-EL8a_r5.md (step 2): dispatcher case at 0xBC6A28C decoded; live capture createtexture_callers read (ONE caller, ret=0xBC6A2C8); producer chain re-verified; handle trace attempted. Handle trace stops at the bgfx boundary: created texture object pointer stored at ctx+0x1E55AB8 element+0x10, never connected to a TexturePtr field from this unit. CLOSES? NO (same blocking fact).

## This attempt (final) — new angle: decode the dragon-layer bridge 0xc296b50 and corroborate its callers statically + via live capture

### (1) Who PRODUCES command byte 14 — proven [V]

sub_bc73770 (ctx rcx, &outHandle rdx, Memory* r8, flags r9d): `0xbc73aaa  mov byte ptr [rbp+0x2C],0xE` writes cmd byte 0x0E into the command buffer [rbx+0xDC5820] at pos [rbx+0xDC5818] (rbx = [ctx+0x1CFD0C8]), then memcpy (sub_ebce390) appends [u16 handle @rbp+0x2E][u64 mem @rbp+0x18][u32 flags @rbp+0x28][u8 skip=0 @rbp+0x2D], bumping pos after each; the handle is allocated by `0xbc7384d  call 0xBC79A60` from ctx+0x1DF3460 (0xFFFF = exhausted) and `0xbc73b74  mov [rsi],di` returns *outHandle. Argument order [u16 handle][u64 mem][u32 flags][u8 skip] matches the handler's read order exactly. xref.py callers 0xbc73770 -> 0xbc73bf0, 0xbc73ed0, 0xbc74120 (thin wrappers) only [V].

### (2) Dragon-layer bridge 0xc296b50 DECODED (new angle, nothing above redone)

sub_c296b50 [0xc296b50..0xc298b50) size 0x2000, 5 static xrefs in. It is shared_ptr/bookkeeping over a texture object (rcx=this), an out-struct (rdx=arg2), a descriptor (r8=arg3), and flags (r9=arg4): increfs the r8 object, swaps interface pointers at this+0x90/+0x98 and this+0x70/+0x78, then (when this+0x0 != 0xFFFF) calls the createTexture wrapper `0xc296d79  call 0xBC73BF0` with the descriptor fields staged on the stack, and on success stores:
- `0xc296e26  mov [rdi],ax` — the returned u16 handle at [rdi] = [texture_obj+0x00] (rdi = rcx = texture object)
- `0xc296e2d  movups xmm0,[r12]` / `0xc296e32  movups [rdi+8],xmm0` — 16 descriptor bytes at [texture_obj+0x08]
- `0xc296e36  mov rdx,[r12+0x10]` / `0xc296e3b  mov [rdi+0x18],rdx` — descriptor+0x10 at [texture_obj+0x18]
- `0xc296f44  mov [rsi],rdi` — texture-object pointer at [out-struct arg2]
- `0xc296f50  mov [rsi+8],al` — success flag at [out-struct+8]
- returns eax = handle read back via `0xc296e99  movzx eax,word ptr [rdi]`; 0xFFFF = failure.

So 0xc296b50 IS the bridge that issues createTexture (via wrapper 0xbc73bf0 -> sub_bc73770 -> cmd byte 14) and writes the returned handle into [texture_obj+0x00].

Static xrefs INTO 0xc296b50: xref.py callers 0xc296b50 -> 0xbc41420(+0xcea), 0xbc42740(+0x860), 0xbc432e0(+0x22b), 0xbc43550(+0xabf), 0xbc44120(+0x47e) — all 0xbc4xxxx dragon/RenderDragon layer, none in this unit [V]. Corroborated statically: sub_bc41420 (0xbc41420..0xbc43420) contains the call site `0xbc41b29  lea rdx,[rbp+0x180]` / `0xbc41b30  mov r9,rbp` / `0xbc41b33  mov rcx,rbx` / `0xbc41b36  mov r8,r15` / `0xbc41b39  call 0xC296B50` (rcx=rbx = texture object, rdx=&[rbp+0x180] out-struct, r8=r15 descriptor) and returns to `0xbc41b3e  movzx eax,byte ptr [rbp+0x188]` [V static]. sub_bc41420 is itself called from 0x4e05e50(+0x224) [V static xref]. None of texgroup_load/texload/texload_task/0x18718D0/sub_186dac0/sub_a3f10 calls 0xc296b50 or any wrapper/producer [V negative grep].

### (3) Live captures confirm the chain end-to-end [V live]

- Live capture createtexture_callers (capture at 0xE8143C0, docs/data/live/createtexture_callers.txt): 1612 hits collapse to ONE caller; every hit ret=0xBC6A2C8 = instruction right after the `0xbc6a2c2  call qword ptr [0xF99FFA0]` slot-26 createTexture call in the dispatcher case block at 0xBC6A28C; RCX = renderer ctx (0x5314A010000); R8 = 0x1C-byte descriptor ("TEX" magic, width/height u16 near the end). Confirms createTexture is issued from the bgfx command-buffer dispatcher, NOT from MC texture code.
- Live capture bgfx_createtexture_producer (capture at 0xBC73770, docs/data/live/bgfx_createtexture_producer.txt): ret=0xBC73EAD (instruction right after `0xbc73ea8  call 0xBC73770` in wrapper 0xbc73bf0), RDX = outHandle 0x14C8D2, R8 = 0x1C-byte descriptor ("TEX"/"siderTEX" tag, width/height u16 near the end). Confirms wrapper -> producer -> cmd byte 14.
- Live capture dragon_texture_entry_c296b50 (capture at 0xC296B50, docs/data/live/dragon_texture_entry_c296b50.txt): CALLER ret=0xBC41B3E (inside sub_bc41420 range 0xbc41420..0xbc43420); RCX = texture object (0x53199475D00, 0x53199475700, 0x531994715C0, ...); RDX/R8/R9 = descriptor/handle values. Confirms sub_bc41420 calls 0xc296b50 with RCX = a texture object [V live].

### (4) Texture-object init in this unit RULED OUT [V negative]

vtable 0xEFCA580 slot 4 = sub_a3f10 (`0xa3f10  push rsi`): stores interface vtables at +0x00/+0x90/+0xA8, decrefs via sub_eea6040; NO bgfx call, NO command-byte-14 write, NO call to 0xc296b50/0xbc73bf0/0xbc73770 — NOT the createTexture-producing texture-object init [V] (negative). All 16 `call qword ptr [reg+0xd0]` encodings -> 0 hits each; xref.py callers 0xe8143c0 empty; preflight: 0 xrefs into createTexture [V negative].

### (5) Handle -> TexturePtr/ClientTexture — NOT found in this unit [V negative]

The handle returned by createTexture is stored by dragon bridge 0xc296b50 at [internal dragon texture object +0x00] (`0xc296e26  mov [rdi],ax`), where that object (RCX=0x53199475D00, 0x53199475700, 0x531994715C0, ...) has fields at +0x00/+0x08/+0x18/+0x28/+0x40/+0x48/+0x78/+0x80 — an ~0x88B RenderDragon internal object, NOT TexturePtr (32B two shared_ptr), NOT BedrockTexture (48B three shared_ptr), NOT ClientTexture (empty carrier). No store of that handle into any TexturePtr+0x00 (mClientTexture shared_ptr) / ClientTexture / BedrockTexture field appears anywhere in texgroup_load/texload/texload_task/0x18718D0/sub_186dac0/sub_a3f10 [V negative]. The TexturePtr<->internal-object mapping / handle write into a TexturePtr field is deferred to the dragon-layer frame-time path (sub_bc41420/0x4e05e50), outside U-EL8a.

## ANSWER TABLE — pack->GPU createTexture issuance and handle trace (one row per distinct offset; proof lines verbatim from rdis unless tagged [V live]/[I])

| name | rva or offset | size | verbatim `0xRVA  instr` proof line(s) | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| producer entry | 0xbc73770 | fn start | `0xbc73770  push rbp` | sub_bc73770(ctx rcx, &outHandle rdx, Memory* r8, flags r9d): API-thread producer of command byte 14 | [V] |
| skip byte staged | 0xbc7379b | 1 B | `0xbc7379b  mov byte ptr [rbp+0x2D],0` | skip byte = 0 | [V] |
| flags/mem staged | 0xbc7379f | 4 B | `0xbc7379f  mov [rbp+0x28],r9d`<br>`0xbc737a3  mov [rbp+0x18],r8` | flags -> [rbp+0x28]; Memory* -> [rbp+0x18] | [V] |
| handle allocated | 0xbc7384d | call site | `0xbc7384d  call 0xBC79A60`<br>`0xbc73853  mov [rbp+0x2E],ax` | u16 handle from ctx+0x1DF3460 via sub_bc79a60 (0xFFFF = exhausted); staged at [rbp+0x2E] | [V] |
| command byte 14 written | 0xbc73aaa | 1 B | `0xbc73aaa  mov byte ptr [rbp+0x2C],0xE` | writes cmd byte 0x0E as first field | [V] |
| buffer base/pos | 0xbc73aae | 4 B | `0xbc73aae  mov eax,[rbx+0xDC5818]`<br>`0xbc73ab8  add rcx,0xDC5820` | pos from [rbx+0xDC5818]; data base [rbx+0xDC5820]; rbx = [ctx+0x1CFD0C8] | [V] |
| byte 0x0E memcpy | 0xbc73ac9 | call site | `0xbc73ac9  call 0xEBCE390` | memcpy(data+pos, &byte 0x0E, 1) (sub_ebce390 = memcpy) | [V] |
| pos bump +2 | 0xbc73ae2 | 4 B | `0xbc73ae2  mov [rbx+0xDC5818],ecx` | pos = align2(pos)+2 | [V] |
| handle memcpy | 0xbc73af5 | call site | `0xbc73af5  call 0xEBCE390` | memcpy(data+pos, [rbp+0x2E], 2) | [V] |
| mem memcpy | 0xbc73b1a | call site | `0xbc73b1a  call 0xEBCE390` | memcpy(data+pos, [rbp+0x18], 8) | [V] |
| flags memcpy | 0xbc73b3f | call site | `0xbc73b3f  call 0xEBCE390` | memcpy(data+pos, [rbp+0x28], 4) | [V] |
| skip memcpy + pos++ | 0xbc73b64 | call site | `0xbc73b64  call 0xEBCE390`<br>`0xbc73b6a  inc dword ptr [rbx+0xDC5818]` | memcpy(data+pos, [rbp+0x2D], 1) (skip=0); pos++ | [V] |
| out-handle returned | 0xbc73b70 | 2 B | `0xbc73b70  movzx edi,word ptr [rbp+0x2E]`<br>`0xbc73b74  mov [rsi],di`<br>`0xbc73b93  ret` | *outHandle (rdx arg) = allocated u16 handle; producer returns | [V] |
| producer xrefs | 0xbc73770 xref | - | - | xref.py callers 0xbc73770 -> 0xbc73bf0, 0xbc73ed0, 0xbc74120 (thin wrappers) only | [V] |
| wrapper entry + validator | 0xbc73bf0 | fn start | `0xbc73bf0  push r15`<br>`0xbc73c6c  call 0xBC735B0` | wrapper: validate texture desc via sub_bc735b0, then issue command byte 14 | [V] |
| wrapper builds header + calls producer | 0xbc73dcc | 4 B | `0xbc73dcc  mov dword ptr [rsp+0x34],0x584554`<br>`0xbc73e84  call qword ptr [0xF99FFA0]`<br>`0xbc73ea8  call 0xBC73770`<br>`0xbc73ead  movzx eax,word ptr [rsp+0x32]` | "TEX" magic dword (0x584554) into the 0x18-byte createTexture header; 0x18 bytes copied via CFG thunk; `call 0xBC73770` issues the command; handle read back | [V] |
| wrapper xrefs | 0xbc73bf0 xref | - | - | xref.py callers 0xbc73bf0 -> 0xbc63c80, 0xc296b50, 0xc297000, 0xc2a3d90; 0xbc73ed0 -> 0xc296b50, 0xc2a3d90; 0xbc74120 -> 0xc296b50, 0xc2a3d90 | [V] |
| dragon bridge entry | 0xc296b50 | fn start | `0xc296b50  push rbp` | sub_c296b50(this rcx, out-struct rdx, desc r8, flags r9): shared_ptr bookkeeping + createTexture-wrapper call + handle store at [this+0x00] | [V] |
| dragon calls createTexture wrapper | 0xc296d79 | call site | `0xc296d79  call 0xBC73BF0` | `call 0xBC73BF0` (wrapper) issues createTexture command byte 14 | [V] |
| dragon handle store | 0xc296e26 | 2 B | `0xc296e26  mov [rdi],ax`<br>`0xc296e2d  movups xmm0,[r12]`<br>`0xc296e32  movups [rdi+8],xmm0`<br>`0xc296e36  mov rdx,[r12+0x10]`<br>`0xc296e3b  mov [rdi+0x18],rdx` | returned u16 handle stored at [rdi]=[texture_obj+0x00]; 16 descriptor bytes at +0x08 (movups=16B); descriptor+0x10 at +0x18 | [V] |
| dragon out-struct store | 0xc296f44 | 8 B | `0xc296f44  mov [rsi],rdi`<br>`0xc296f50  mov [rsi+8],al` | texture-object pointer at [out-struct arg2]; success flag at +8 | [V] |
| dragon handle readback/return | 0xc296e99 | 2 B | `0xc296e99  movzx eax,word ptr [rdi]`<br>`0xc296eb1  cmp ax,0xFFFF` | handle read back from [rdi]; 0xFFFF = failure | [V] |
| sub_bc41420 calls dragon bridge | 0xbc41b39 | call site | `0xbc41b29  lea rdx,[rbp+0x180]`<br>`0xbc41b30  mov r9,rbp`<br>`0xbc41b33  mov rcx,rbx`<br>`0xbc41b36  mov r8,r15`<br>`0xbc41b39  call 0xC296B50`<br>`0xbc41b3e  movzx eax,byte ptr [rbp+0x188]` | sub_bc41420 calls 0xc296b50 with rcx=rbx(texture object), rdx=&[rbp+0x180](out-struct), r8=r15(descriptor); returns to 0xbc41b3e | [V] |
| sub_bc41420 static xref in | 0xbc41420 xref | - | - | xref.py callers 0xbc41420 -> 0x4e05e50(+0x224) (also 0xbc41420 called by 0x4e06430/0x56be030/0x4e067c0/0x5aba280 for the sibling entries); all dragon-layer | [V] |
| live: dragon bridge caller | dragon_texture_entry_c296b50 | - | - | live capture dragon_texture_entry_c296b50 (capture at 0xC296B50, docs/data/live/dragon_texture_entry_c296b50.txt): CALLER ret=0xBC41B3E (inside sub_bc41420); RCX = texture object 0x53199475D00 / 0x53199475700 / 0x531994715C0 / ... | [V live] |
| command byte-14 handler entry | 0xbc69487 | fn start | `0xbc69487  and edx,0xFFFFFFFE` | bgfx command executor case 14 = createTexture: reads [u16 handle][u64 Memory* mem][u32 flags][u8 skip] | [V] |
| TEX magic gate | 0xbc695a3 | 4 B | `0xbc695a3  cmp dword ptr [rsp+0x8C],0x584554` | handler requires MemoryReader u32 == 0x00584554 ('TEX') else fails | [V] |
| renderer object load | 0xbc6a28f | 8 B | `0xbc6a28f  mov rcx,[rdi+0x1EBF2D0]` | rcx = RendererContext object from command-buffer context | [V] |
| vtable pointer load | 0xbc6a2ae | 8 B | `0xbc6a2ae  mov rax,[rcx]` | rax = vtable pointer | [V] |
| slot 26 function pointer | 0xbc6a2b1 | 8 B | `0xbc6a2b1  mov rax,[rax+0xD0]` | rax = vtable[0xD0] = slot 26 createTexture (RendererContextD3D12 base vtable 0xF4ED2D0) [slot name per BGFX_MAP 6k [I]] | [V] |
| slot 26 indirect call | 0xbc6a2c2 | call site | `0xbc6a2c2  call qword ptr [0xF99FFA0]` | CFG thunk sub_eea6040 tails to rax = createTexture(handle u16=edx, mem r8, flags r9d, skip r10b); return address = 0xbc6a2c8 | [V] |
| live: single createTexture caller | createtexture_callers ret | - | - | live capture createtexture_callers (capture at 0xE8143C0, docs/data/live/createtexture_callers.txt): 1612 hits, ONE caller; every hit ret=0xBC6A2C8 = instruction right after the 0xbc6a2c2 call; RCX=5314A010000 renderer ctx; R8 = 0x1C-byte descriptor ("TEX" magic, width/height u16 near end) | [V live] |
| live: producer call | bgfx_createtexture_producer ret | - | - | live capture bgfx_createtexture_producer (capture at 0xBC73770, docs/data/live/bgfx_createtexture_producer.txt): ret=0xBC73EAD (right after `0xbc73ea8  call 0xBC73770`); RDX=outHandle 0x14C8D2; R8=0x1C-byte descriptor | [V live] |
| createTexture return captured | 0xbc6a2d1 | 8 B | `0xbc6a2d1  mov r15,rax` | rax = created texture object pointer -> r15 | [V] |
| guard byte load | 0xbc6a2e3 | 1 B | `0xbc6a2e3  movzx ecx,byte ptr [rdi+0x1E7DAD0]` | ctx+0x1E7DAD0 flag required for handles >= 0x1000 | [V] |
| handle-table base | 0xbc6a31b | 8 B | `0xbc6a31b  lea rcx,[rdi+0x1E55AB8]` | rcx = ctx+0x1E55AB8 paged per-handle table (0x28-byte elements per BGFX_MAP.md 6et [I]) | [V] |
| table page walk | 0xbc6a322 | call site | `0xbc6a322  call 0xBC7A3D0` | walk/create the page holding the handle's element | [V] |
| texture object stored in handle table | 0xbc6a49b | 8 B | `0xbc6a49b  mov [r8+0x10],r15` | element+0x10 = texture object pointer; this is where the created object lives — NOT a TexturePtr field | [V] |
| createTexture function entry | 0xe8143c0 | fn start | `0xe8143c0  push rbp` | createTexture = RendererContextD3D12 vtable slot 26 (base vtable 0xF4ED2D0 +0x0D0 per BGFX_MAP.md 6k [I]); preflight: 0 xrefs in — no direct caller anywhere in .text | [V] |
| createTexture args staged | 0xe8143e3 | 4 B | `0xe8143e3  mov [rbp+0x28],r9d`<br>`0xe8143e7  mov r14,r8`<br>`0xe8143ef  mov [rbp+0x2E],dx` | flags -> [rbp+0x28]; mem (r8) -> r14; handle (dx) -> [rbp+0x2E] | [V] |
| CFG thunk | 0xeea6040 | 5 B | `0xeea6040  jmp rax` | [data_f99ffa0] = sub_eea6040; `call qword ptr [0xF99FFA0]` indirects through it to rax = slot 26 target | [V] |
| no direct createTexture call | 0xe8143c0 xref | - | - | xref.py callers 0xe8143c0 -> empty; preflight: 0 xrefs in | [V] (negative) |
| no [reg+0xd0] vcall anywhere | .text slot-26 sweep | - | - | all 16 `call qword ptr [reg+0xd0]` encodings (rax..r15) -> 0 hits each | [V] (negative) |
| producer absent from L8a listings | docs/data/listings | - | - | grep bc73770/bc73bf0/bc73ed0/bc74120/c296b50/c2967000/c2a3d90/e8143c0 -> no matches in any listing | [V] (negative) |
| producer absent from L8a callees | texgroup_load/texload_task callees | - | - | texgroup_load tail calls: 0xE935700, 0x5424000, 0x5424130, 0xEEC6EB0, 0x78ED0, 0x18718D0; texload_task calls: 0x1994F90, 0xE935700, 0x78ED0, 0x9BC830 — none is the producer/wrapper/dragon entry | [V] (negative) |
| texture-object init NOT the producer | vtable 0xEFCA580 +0x020 | 8 B | `0xa3f10  push rsi`<br>`0xa3f53  mov [rcx],rax`<br>`0xa3f5d  mov [rcx+0x90],rax`<br>`0xa3f6b  mov [rcx+0xA8],rax` | vtable 0xEFCA580 slot 4 = sub_a3f10: stores interface vtables at +0x00/+0x90/+0xA8, decrefs via sub_eea6040; NO bgfx call, NO command-byte-14 write — NOT the createTexture producer | [V] (negative) |
| registration hand-off call | 0x54227af | call site | `0x54227af  call 0x18718D0` | texgroup_load ends registration at CPU callee 0x18718D0 (rcx=[rbp+0x70] tex ptr, rdx=&[rbp+0x110] descriptor, r8=[rbp+0x130] owner, r9=&[rbp-0x50]); 0x18718D0 body is CPU slot-array bookkeeping, no createTexture/GPU-store | [V] |
| texgroup_load tail calls | 0x54227f1 / 0x54233e1 | call site | `0x54227f1  call 0xE935700`<br>`0x54233e1  call 0x78ED0` | last call sites of texgroup_load (0x5421c90..0x54235a0): 0xE935700, 0x5424000, 0x5424130, 0xEEC6EB0, 0x78ED0, 0x18718D0 — none is createTexture or slot-26 | [V] |
| texload_task calls | 0x541c229 / 0x541c126 / 0x541c60a / 0x541c615 | call site | `0x541c229  call 0x1994F90`<br>`0x541c126  call 0xE935700`<br>`0x541c60a  call 0x78ED0`<br>`0x541c615  call 0x9BC830` | texload_task (0x541bf00..0x541c6a0): image loader + decrefs — no createTexture/GPU-store | [V] |
| no GPU-handle store in L8a | TexturePtr+0x00 | 16 B | - | mClientTexture shared_ptr; no store to it anywhere in texgroup_load/texload/texload_task/0x18718D0/sub_186dac0/sub_a3f10 | [V] (negative) |

## CLOSES?

NO — the createTexture issuance is fully proven [V]: command byte 14 is produced by sub_bc73770 (writes 0x0E + [u16 handle][u64 Memory*][u32 flags][u8 skip=0] into [ctx+0x1CFD0C8]+0xDC5820 at pos [rbx+0xDC5818], allocates the u16 handle via sub_bc79a60 at ctx+0x1DF3460, returns *outHandle at 0xbc73b74), issued through thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 (xref: 0xbc73bf0 -> 0xbc63c80/0xc296b50/0xc297000/0xc2a3d90), consumed by the dragon bridge 0xc296b50 (calls wrapper 0xbc73bf0 at 0xc296d79; stores the returned handle at [texture_obj+0x00] via `0xc296e26  mov [rdi],ax`; called by sub_bc41420 at `0xbc41b39  call 0xC296B50`, live-capture confirmed ret=0xBC41B3E RCX=texture object), then by the dispatcher case block at 0xBC6A28C which loads vtable slot 26 (`0xbc6a2b1  mov rax,[rax+0xD0]`) and calls it via `0xbc6a2c2  call qword ptr [0xF99FFA0]`; live capture createtexture_callers confirms ONE caller, ret=0xBC6A2C8 (the instruction after that call), RCX = renderer ctx, R8 = 0x1C-byte descriptor with "TEX" magic; the returned texture object pointer (rax->r15 at 0xbc6a2d1) is stored in the bgfx per-handle table at element+0x10 (`0xbc6a49b  mov [r8+0x10],r15`, ctx+0x1E55AB8).
BUT the GPU-handle write into TexturePtr/ClientTexture is NOT proven and is not present in this unit: the handle lands in an internal ~0x88B RenderDragon texture object at [object+0x00] (dragon bridge 0xc296b50, called from sub_bc41420/0x4e05e50), while TexturePtr is 32B two shared_ptr, BedrockTexture 48B three shared_ptr, ClientTexture empty carrier — none receives this u16 handle. No store to TexturePtr+0x00 (mClientTexture) anywhere in texgroup_load/texload/texload_task/0x18718D0/sub_186dac0/sub_a3f10, and the unit's own texture-object init (vtable 0xEFCA580 slot 4 = sub_a3f10) does NOT issue createTexture [V negative]. None of this unit's functions call the producer/wrappers/dragon entries/createTexture [V negative grep]. Single blocking fact: the handle returned by createTexture is never connected to any TexturePtr/ClientTexture/BedrockTexture field from within this unit — the TexturePtr<->internal-object handle wiring is deferred to the dragon-layer frame-time path (sub_bc41420/0x4e05e50), outside U-EL8a.

## TOOL REQUESTS

None

## NEXT
DONE
