## NEXT
DONE

# Unit U-EL8a — L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk); pack->GPU path pending

Scope (checklist item L8a, docs/RENDER_CHECKLIST.md line 344): "[ ] L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk) — pack->GPU path pending". Do ONLY the pending part: does the pack->GPU path (texgroup_load 0x5421c90 / texload 0x58a1310 / texload_task 0x541bf00 / decode chain) contain a createTexture issuance (RendererContext slot 26 = 0xe8143c0 via [reg+0xd0] vcall, or bgfx command byte 14 -> handler 0xbc69487) and a GPU-handle write into TexturePtr/ClientTexture? SDK headers are stubs (TexturePtr.h 32B two shared_ptr; BedrockTexture.h 48B three shared_ptr; ClientTexture.h empty carrier; TextureGroup.h stub) — header layout is NOT the pending part.

Method: static analysis only; RVAs relative to image base; every claim [V] = verbatim from disassembly (cite RVA), [I] = inferred (say from what), [V live] = live capture, [?] = unknown. Sizes from the instruction. One row per distinct offset, all its sites listed; meaning ONLY where an instruction/string shows it, else '-'. No input data pasted as-is; no raw instruction lines outside table cells; no catch-all rows.

## Prior attempts (read first, do NOT redo)

- docs/progress/oc_U-EL8a_r1.md (109-row field table): fully decoded texgroup_load 0x5421c90..0x54235a0, texload 0x58a1310..0x58a23d0, decode chain sub_1994f90 -> sub_764950 -> sub_777ed0, texload_task 0x541bf00. All CPU-side object creation + group insert (head group+0x248, counter group+0x250), ending at `0x54227af  call 0x18718D0`. No createTexture, no slot-26 vcall, no GPU-handle store anywhere. CLOSES? NO.
- docs/progress/oc_U-EL8a_r2.md: decoded callee 0x18718D0 (0x18718d0..0x1871ae4, CPU slot-array bookkeeping over texture+0x30) and sub_186dac0 (0x186dac0..0x186dffc, CPU shared_ptr/string bookkeeping). Negative sweeps: xref.py callers 0xe8143c0 empty; callers 0xbc69487 none; str "createTexture" none; all 16 encodings of `call qword ptr [reg+0xd0]` -> 0 hits each. CLOSES? NO.
- docs/progress/oc_U-EL8a_r3.md: caller scans (22 callers of 0x18718D0 = generic slot allocator; callers of texgroup_load/texload/texload_task) — none reach createTexture. RendererContextD3D12 vtable base 0xF4ED2D0, slot 26 (+0x0D0) = 0xe8143c0 createTexture per BGFX_MAP.md 6k [I]. CLOSES? NO.
- docs/progress/oc_U-EL8a_r4.md: command-byte-14 producer chain located — sub_bc73770 writes byte 0x0E + [u16 handle][u64 Memory*][u32 flags][u8 skip=0] into [ctx+0x1CFD0C8]+0xDC5820 at pos [rbx+0xDC5818], allocates the u16 handle via sub_bc79a60 at ctx+0x1DF3460, returns *outHandle; thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120; dragon-layer entry points 0xc296b50/0xc297000/0xc2a3d90/0xbc63c80. vtable 0xEFCA580 slot 4 = sub_a3f10 is NOT a createTexture caller. None of this unit's functions call any producer address; grep of docs/data/listings negative; no GPU-handle store to TexturePtr+0x00. CLOSES? NO.
- docs/progress/oc_U-EL8a_r5.md (step 2): dispatcher case at 0xBC6A28C decoded; live capture createtexture_callers read (ONE caller, ret=0xBC6A2C8); producer chain re-verified; handle trace attempted. Handle trace stops at the bgfx boundary: created texture object pointer stored at ctx+0x1E55AB8 element+0x10, never connected to a TexturePtr field from this unit. CLOSES? NO.
- docs/progress/oc_U-EL8a_r6.md: fresh rdis verification + consolidated answer table. Same conclusion: issuance fully proven [V] but lives in dragon layer/dispatcher; no TexturePtr handle write in this unit. CLOSES? NO (blocking fact: handle not connected to TexturePtr/ClientTexture from this unit).
- docs/progress/oc_U-EL8a_r7.md (final): dragon-layer bridge 0xc296b50 decoded — calls wrapper 0xbc73bf0 at `0xc296d79  call 0xBC73BF0`, stores the returned handle at [texture_obj+0x00] via `0xc296e26  mov [rdi],ax` (internal ~0x88B RenderDragon object at RCX=0x53199475D00 / 0x53199475700 / 0x531994715C0 / ...), out-struct store `0xc296f44  mov [rsi],rdi`, success flag at +8; called by sub_bc41420 at `0xbc41b39  call 0xC296B50` (rcx=rbx texture object, rdx=&[rbp+0x180] out-struct, r8=r15 descriptor), which is itself called from 0x4e05e50(+0x224). Live capture dragon_texture_entry_c296b50 confirms CALLER ret=0xBC41B3E RCX=texture object [V live]. CLOSES? NO (same blocking fact: handle lands in the internal dragon object, never connected to a TexturePtr/ClientTexture/BedrockTexture field from within this unit).

## Pending work this attempt (NEW ANGLE — nothing above redone)

Trace sub_bc41420 (the function containing 0xBC41B3E) one level further out: decode its call site 0xbc41b39 context (what rbx/texture object it is, the 0x1C descriptor fields width/height/format/source pointer at r8=r15) and where it stores the returned handle; then find who calls sub_bc41420 (0x4e05e50 and any other xref) and whether any of them writes the handle into a TexturePtr/ClientTexture/BedrockTexture field. If still indirect at the dragon->MC boundary, request one capture on sub_bc41420's entry and stop.

## ANSWER TABLE — pack->GPU createTexture issuance and handle trace (one row per distinct offset; proof lines verbatim from rdis unless tagged [V live]/[I])

| name | rva or offset | size | verbatim `0xRVA  instr` proof line(s) | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| MC_obj+0x18 shared_ptr load | 0x4e05e71 | 8 B | `0x4e05e71  mov rax,[rcx+0x18]` | [MC_obj+0x18] shared_ptr control block, addrefed through CFG thunk at 0x4e05e86 | [V] |
| MC_obj+0x8 pointer | 0x4e05eb0 | 8 B | `0x4e05eb0  mov rcx,[rdi+8]` | [MC_obj+0x8] pointer saved into out-struct field | [V] |
| MC_obj+0x10 shared_ptr | 0x4e05eb4 | 8 B | `0x4e05eb4  mov rbx,[rdi+0x10]` | [MC_obj+0x10] shared_ptr, refcount bumped at +8 | [V] |
| MC_obj+0xE0 flags | 0x4e05f61 | 8 B | `0x4e05f61  mov r9,[rdi+0xE0]` | [MC_obj+0xE0] flags passed as arg4 to the dragon bridge | [V] |
| dragon object = MC_obj+0x58 | 0x4e05f68 | - | `0x4e05f68  add rdi,0x58` | rdi = MC_obj+0x58, the dragon texture object passed to sub_bc41400 | [V] |
| MC->dragon bridge call | 0x4e05f77 | call site | `0x4e05f77  call 0xBC41420` | sub_4e05e50 -> sub_bc41400(rcx=dragon_obj MC_obj+0x58, rdx=out-struct [rbp-0x50], r8=[MC_obj+8], r9=flags); this is the dragon-layer frame-time path, NOT texgroup_load/texload/texload_task | [V] |
| bridge out-struct consumed | 0x4e05f85 | call site | `0x4e05f85  call 0x4E061B0` | sub_4e061b0(&[rbp-8], &[rbp-0x50]) copies descriptor bytes out of the bridge result | [V] |
| out-struct[0] cleared | 0x4e06010 | 8 B | `0x4e06010  mov qword ptr [rsi],0` | [rsi] NULLed after bridge — cleanup, not a TexturePtr store | [V] |
| dragon bridge entry | 0xbc41400 | fn start | `0xbc41400  push rbx` | sub_bc41400(rcx=dragon_obj, rdx=out-struct, r8, r9=flags), 0x2000-byte function (sub_bc41420 in r7 was a mislabel; real start is 0xbc41400) | [V] |
| rbp = out-struct+0x80 | 0xbc41405 | 8 B | `0xbc41405  lea rbp,[rdx+0x80]` | rbp = out-struct base + 0x80 frame | [V] |
| dragon_obj+0x78 flag | 0xbc4145d | 1 B | `0xbc4145d  movzx eax,byte ptr [rcx+0x78]` | [dragon_obj+0x78] flag byte -> [rbp+0x19F] | [V] |
| dragon_obj+0x80 | 0xbc4146f | 1 B | `0xbc4146f  cmp byte ptr [rsi+0x80],0` | [dragon_obj+0x80] byte compared to 0 | [V] |
| dragon bridge -> sub_c296b50 | 0xbc41b39 | call site | `0xbc41b39  call 0xC296B50` | sub_bc41400 calls sub_c296b50(rcx=[MC_obj+8] texture obj, rdx=out-struct2 [rbp+0x180], r8=r15, r9=rbp) | [V] |
| sub_c296b50 success flag | 0xbc41b3e | 1 B | `0xbc41b3e  movzx eax,byte ptr [rbp+0x188]` | sub_c296b50 flag (0=success, 1=failure) read at out-struct2+0x8; eax==0 -> success path | [V] |
| texture object pointer | 0xbc41b52 | 8 B | `0xbc41b52  mov r13,[rbp+0x180]` | r13 = out-struct2[0] = texture object pointer stored by sub_c296b50 | [V] |
| texture_obj+0x18 | 0xbc41b59 | 8 B | `0xbc41b59  mov rax,[r13+0x18]` | [texture_obj+0x18] pointer | [V] |
| texture_obj+0x8 descriptor block | 0xbc41b61 | 16 B | `0xbc41b61  movups xmm0,[r13+8]` | 16 bytes [texture_obj+0x8] descriptor block | [V] |
| texture_obj+0x30 name SSO | 0xbc41b6a | 8 B | `0xbc41b6a  mov r12,[r13+0x30]` | [texture_obj+0x30] name pointer (SSO string) | [V] |
| out-struct+0x0 descriptor block | 0xbc41cb9 | 16 B | `0xbc41cb9  movdqu [rdi],xmm0` | 16-byte descriptor block written to [out-struct+0x0] | [V] |
| out-struct+0x10 pointer | 0xbc41cb5 | 8 B | `0xbc41cb5  mov [rdi+0x10],rcx` | [out-struct+0x10] = texture_obj+0x18 pointer | [V] |
| out-struct+0x40 flag = 1 | 0xbc41cfd | 1 B | `0xbc41cfd  mov byte ptr [rdi+0x40],1` | [out-struct+0x40] set to 1 by sub_bc41400 | [V] |
| sub_c296b50 -> wrapper call | 0xc296d79 | call site | `0xc296d79  call 0xBC73BF0` | sub_c296b50 calls createTexture wrapper 0xbc73bf0 (ecx=6) | [V] |
| handle stored at texture_obj+0x00 | 0xc296e26 | 2 B | `0xc296e26  mov [rdi],ax` | returned u16 handle stored at [texture_obj+0x00] — INTERNAL dragon object field, NOT a TexturePtr field | [V] |
| descriptor at texture_obj+0x08 | 0xc296e32 | 16 B | `0xc296e32  movups [rdi+8],xmm0` | 16 descriptor bytes at [texture_obj+0x08] | [V] |
| desc+0x10 at texture_obj+0x18 | 0xc296e3b | 8 B | `0xc296e3b  mov [rdi+0x18],rdx` | [desc+0x10] stored at [texture_obj+0x18] | [V] |
| handle readback / failure | 0xc296e99 | 2 B | `0xc296e99  movzx eax,word ptr [rdi]`<br>`0xc296eb1  cmp ax,0xFFFF` | handle read back from [texture_obj+0x00]; 0xFFFF = failure | [V] |
| texture obj ptr at out-struct | 0xc296f44 | 8 B | `0xc296f44  mov [rsi],rdi` | texture-object pointer at [out-struct arg2] | [V] |
| success flag at out-struct+8 | 0xc296f50 | 1 B | `0xc296f50  mov [rsi+8],al` | success flag (0) at [out-struct+8] | [V] |
| sub_4e061b0 copies descriptor, NOT handle | 0x4e061cb | 16 B | `0x4e061cb  movups xmm0,[rdx]`<br>`0x4e061ce  movups [rcx],xmm0` | sub_4e061b0 copies a1+0x0..0x10 (descriptor bytes) to a0+0x0..0x10 — the handle at [dragon_obj+0x00] is NOT copied | [V] |
| sub_4e061b0 shared_ptr copy | 0x4e061c7 | 8 B | `0x4e061c7  mov [rcx+0x10],r8` | a0+0x10 = a1+0x10 shared_ptr copy | [V] |
| producer entry | 0xbc73770 | fn start | `0xbc73770  push rbp` | sub_bc73770(ctx rcx, &outHandle rdx, Memory* r8, flags r9d): API-thread producer of command byte 14 | [V] |
| command byte 14 written | 0xbc73aaa | 1 B | `0xbc73aaa  mov byte ptr [rbp+0x2C],0xE` | writes cmd byte 0x0E into command buffer [ctx+0x1CFD0C8]+0xDC5820 at pos [rbx+0xDC5818] | [V] |
| handle allocated | 0xbc7384d | call site | `0xbc7384d  call 0xBC79A60`<br>`0xbc73853  mov [rbp+0x2E],ax` | u16 handle allocated from ctx+0x1DF3460 via sub_bc79a60 (0xFFFF = exhausted); staged at [rbp+0x2E] | [V] |
| out-handle returned | 0xbc73b74 | 2 B | `0xbc73b70  movzx edi,word ptr [rbp+0x2E]`<br>`0xbc73b74  mov [rsi],di` | *outHandle (rdx arg) = allocated u16 handle | [V] |
| thin createTexture wrapper | 0xbc73bf0 | fn start | `0xbc73bf0  push r15`<br>`0xbc73c6c  call 0xBC735B0` | wrapper: validate texture desc via sub_bc735b0, then issue command byte 14 via sub_bc73770 | [V] |
| TEX magic in header | 0xbc73dcc | 4 B | `0xbc73dcc  mov dword ptr [rsp+0x34],0x584554` | "TEX" magic dword (0x584554) written into the 0x18-byte createTexture header | [V] |
| wrapper -> producer | 0xbc73ea8 | call site | `0xbc73ea8  call 0xBC73770` | wrapper issues the command | [V] |
| command byte-14 handler entry | 0xbc69487 | fn start | `0xbc69487  and edx,0xFFFFFFFE` | bgfx command executor case 14 = createTexture: reads [u16 handle][u64 mem][u32 flags][u8 skip] | [V] |
| TEX magic gate | 0xbc695a3 | 4 B | `0xbc695a3  cmp dword ptr [rsp+0x8C],0x584554` | handler requires MemoryReader u32 == 0x00584554 ('TEX') | [V] |
| renderer context load | 0xbc6a28f | 8 B | `0xbc6a28f  mov rcx,[rdi+0x1EBF2D0]` | rcx = RendererContext object from command-buffer context | [V] |
| slot 26 vtable load | 0xbc6a2b1 | 8 B | `0xbc6a2ae  mov rax,[rcx]`<br>`0xbc6a2b1  mov rax,[rax+0xD0]` | vtable[0xD0] = slot 26 createTexture (RendererContextD3D12 base vtable 0xF4ED2D0; slot name per BGFX_MAP.md 6k [I]) | [V] |
| slot 26 indirect call | 0xbc6a2c2 | call site | `0xbc6a2c2  call qword ptr [0xF99FFA0]` | CFG thunk sub_eea6040 tails to rax = createTexture(handle u16, mem, flags, skip); return address = 0xbc6a2c8 | [V] |
| createTexture return captured | 0xbc6a2d1 | 8 B | `0xbc6a2d1  mov r15,rax` | rax = created texture object pointer -> r15 | [V] |
| texture object stored in handle table | 0xbc6a49b | 8 B | `0xbc6a49b  mov [r8+0x10],r15` | ctx+0x1E55AB8 handle-table element+0x10 = texture object pointer — NOT a TexturePtr field | [V] |
| createTexture function entry | 0xe8143c0 | fn start | `0xe8143c0  push rbp` | createTexture = RendererContextD3D12 vtable slot 26 (BGFX_MAP.md 6k, line 403 / 1512) | [V] |
| no direct createTexture caller | 0xe8143c0 | xref | - | xref.py callers 0xe8143c0 -> empty; no `call 0xe8143c0` anywhere in .text | [V] negative |
| no slot-26 `[reg+0xd0]` vcall | .text | sweep | - | all 16 `call qword ptr [reg+0xd0]` encodings (rax..r15) -> 0 hits each | [V] negative |
| texture-object init NOT the producer | vtable 0xEFCA580 +0x020 | 8 B | `0xa3f10  push rsi`<br>`0xa3f53  mov [rcx],rax`<br>`0xa3f5d  mov [rcx+0x90],rax`<br>`0xa3f6b  mov [rcx+0xA8],rax` | vtable 0xEFCA580 slot 4 = sub_a3f10: stores interface vtables at +0x00/+0x90/+0xA8, decrefs via sub_eea6040; NO bgfx call, NO command-byte-14 write — NOT the createTexture producer | [V] negative |
| producer chain absent from this unit | docs/data/listings | grep | - | grep of texgroup_load/texload/texload_task listings for bc73770/bc73bf0/c296b50/e8143c0 -> no matches | [V] negative |
| sub_4e05e50 not reached from this unit | sub_4e05e50 | fn start | `0x4e05e50  push rbp` | rdis: sub_4e05e50 has 0 xrefs in; xref.py callers 0xbc41420 -> 0x4e05e50 — the MC->dragon bridge lies OUTSIDE texgroup_load/texload/texload_task | [V] |
| no TexturePtr+0x00 handle store | TexturePtr+0x00 | 16 B | - | mClientTexture shared_ptr slot; no store to it anywhere in texgroup_load/texload/texload_task/0x18718D0/sub_a3f10/sub_bc41400/sub_4e05e50/sub_4e061b0 | [V] negative |
| live: single createTexture caller | createtexture_callers ret=0xBC6A2C8 | - | - | live capture at 0xE8143C0 (docs/data/live/createtexture_callers.txt): 1612 hits, ONE caller; every hit ret=0xBC6A2C8 = instruction right after `0xbc6a2c2  call qword ptr [0xF99FFA0]`; RCX=renderer ctx, R8=0x1C descriptor with 'TEX' magic | [V live] |
| live: producer call | bgfx_createtexture_producer ret=0xBC73EAD | - | - | live capture at 0xBC73770 (docs/data/live/bgfx_createtexture_producer.txt): ret=0xBC73EAD = right after `0xbc73ea8  call 0xBC73770` | [V live] |
| live: dragon bridge caller | dragon_texture_entry_c296b50 ret=0xBC41B3E | - | - | live capture at 0xC296B50 (docs/data/live/dragon_texture_entry_c296b50.txt): CALLER ret=0xBC41B3E (inside sub_bc41400); RCX = texture object 0x53199475D00 / 0x53199475700 / 0x531994715C0 / ... | [V live] |

## CLOSES?

NO — the createTexture issuance is fully proven [V] end-to-end, but NONE of it lives in this unit's functions, and the handle is never written into a TexturePtr/ClientTexture field:

Issuance chain [V]: MC bridge sub_4e05e50 (`0x4e05f77  call 0xBC41420`) -> dragon bridge sub_bc41400 (`0xbc41b39  call 0xC296B50`) -> wrapper 0xbc73bf0 (`0xc296d79  call 0xBC73BF0`) -> producer sub_bc73770 (`0xbc73aaa  mov byte ptr [rbp+0x2C],0xE` writes command byte 0x0E) -> render-thread dispatcher case 0xBC6A28C (`0xbc6a2b1  mov rax,[rax+0xD0]` loads vtable slot 26; `0xbc6a2c2  call qword ptr [0xF99FFA0]` calls it) -> createTexture 0xe8143c0. The returned texture object pointer (rax->r15 at `0xbc6a2d1  mov r15,rax`) is stored in the bgfx per-handle table at element+0x10 (`0xbc6a49b  mov [r8+0x10],r15`, ctx+0x1E55AB8).

Live captures [V live]: createtexture_callers confirms ONE caller, ret=0xBC6A2C8 (the instruction right after the slot-26 call); bgfx_createtexture_producer confirms ret=0xBC73EAD (right after `0xbc73ea8  call 0xBC73770`); dragon_texture_entry_c296b50 confirms CALLER ret=0xBC41B3E with RCX = a texture object.

Handle trace [V]: sub_c296b50 stores the returned u16 handle at [texture_obj+0x00] (`0xc296e26  mov [rdi],ax`) where texture_obj is the INTERNAL ~0x88B RenderDragon object (RCX = 0x53199475D00 / 0x53199475700 / 0x531994715C0 / ... per live capture). sub_bc41400 copies descriptor bytes ([texture_obj+0x8] block, +0x18 pointer, +0x40 dword, +0x44 word) into the caller's out-struct, and sub_4e061b0 copies those descriptor bytes to MC object a0+0x0 (`0x4e061ce  movups [rcx],xmm0`) — but the HANDLE itself at [texture_obj+0x00] is never copied into a TexturePtr/ClientTexture field.

The issuance is NOT statically reachable from this unit [V negative]: xref.py callers 0xe8143c0 -> empty; ripscan only self-refs inside the RTX wrapper; all 16 `call qword ptr [reg+0xd0]` encodings -> 0 hits; grep of texgroup_load/texload/texload_task listings for bc73770/bc73bf0/bc73ed0/bc74120/c296b50/c297000/c2a3d90/e8143c0 -> no matches; vtable 0xEFCA580 slot 4 (sub_a3f10, `0xa3f10  push rsi`) is NOT a createTexture caller; sub_4e05e50 has 0 xrefs in (it is the dragon-layer frame-time bridge, outside texgroup_load/texload/texload_task).

No store to TexturePtr+0x00 (mClientTexture shared_ptr, 16B) appears anywhere in texgroup_load/texload/texload_task/0x18718D0/sub_a3f10/sub_bc41400/sub_4e05e50/sub_4e061b0 [V negative].

Single blocking fact: the handle returned by createTexture is stored in the internal dragon texture object at [object+0x00] and is never connected to any TexturePtr/ClientTexture/BedrockTexture field from within this unit — the TexturePtr<->dragon-object handle wiring is deferred to the dragon-layer frame-time path (sub_4e05e50/sub_bc41400 and beyond), which is OUTSIDE U-EL8a.

## TOOL REQUESTS

None

## NEXT
DONE
