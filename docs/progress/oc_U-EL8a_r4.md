## NEXT
DONE

# Unit U-EL8a — L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk); pack->GPU path pending

Scope (checklist item L8a, docs/RENDER_CHECKLIST.md line 344): "[ ] L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk) — pack->GPU path pending".
Do ONLY the pending part: does the pack->GPU path (texgroup_load 0x5421c90 / texload 0x58a1310 / texload_task 0x541bf00 / decode chain) contain a createTexture issuance (RendererContext slot 26 = 0xe8143c0 via [reg+0xd0] vcall, or bgfx command byte 14 -> handler 0xbc69487) and a GPU-handle write into TexturePtr/ClientTexture? SDK headers are stubs (TexturePtr.h 32B two shared_ptr; BedrockTexture.h 48B three shared_ptr; ClientTexture.h empty carrier; TextureGroup.h stub) — header layout is NOT the pending part.

Method: static analysis only; RVAs relative to image base; every claim [V] = verbatim from disassembly (cite RVA), [I] = inferred, [?] = unknown. Sizes from the instruction. One row per distinct offset, all its sites listed; meaning only where an instruction or string shows it, else '-'. No input data pasted as-is; no raw instruction lines outside table cells. Verbatim proof lines are copied exactly from rdis.exe output (`0xRVA  instr`, two spaces after the address).

## Proven before this attempt (unchanged [V]; full 109-row field table in retired oc_U-EL8a_r1.md)

- texgroup_load 0x5421c90 (TextureGroup this = rcx at [rbp+0x228]): CPU object creation only — 0x20-byte handle (vtable 0xF09AA70, refcount 0x100000001), 0x80-byte texture entry, 0x70-byte list node; RB-tree/intrusive-list insert (head group+0x248, counter group+0x250); ends at `0x54227af  call 0x18718D0` (rcx=[rbp+0x70] texture ptr, rdx=&[rbp+0x110] descriptor, r8=[rbp+0x130] owner, r9=&[rbp-0x50]).
- texload 0x58a1310 / texload_task 0x541bf00 / decode chain sub_1994f90 -> sub_764950 -> sub_777ed0: PNG load, per-texture stage/descriptor build (fields +0x178..+0x244), UV matrix, element ranges appended to group via texgroup append 0x5417950. NONE contains createTexture, a slot-26 vcall, or a GPU-handle store.
- Callee 0x18718D0 fully decoded (0x18718d0..0x1871ae4): CPU slot-array bookkeeping over texture+0x30 (+0x19 empty flag, +0x20 size dword, +0x28 entry ptr), zeroes 16B out block, tail-calls sub_186dac0 (0x186dac0..0x186dffc, CPU shared_ptr/string bookkeeping). NO createTexture, NO [reg+0xd0], NO GPU-store.
- Negative sweeps (all [V]): xref.py callers 0xe8143c0 -> empty (no direct createTexture call); ripscan 0xe8143c0 -> only self-refs inside RTX wrapper e83d390; xref.py callers 0xbc69487 (command byte-14 handler) -> no callers; xref.py str "createTexture" -> no such string; all 16 encodings of `call qword ptr [reg+0xd0]` -> 0 hits; grep of listings for `call 0xe8*`, `call 0xbc*`, `call qword ptr [..+0xd0]` -> none.
- Prior attempt oc_U-EL8a_r3.md scanned all callers of 0x18718D0 (22 funcs, generic slot allocator), callers of texgroup_load/texload/texload_task — none reach createTexture.

## This attempt — command-byte-14 producer trace (NEW ANGLE; nothing above redone)

1. Verified the render-thread handler end-to-end: 0xbc69487 (command byte 14 = createTexture) reads [u16 handle][u64 Memory*][u32 flags][u8 skip], checks TEX magic 0x00584554 at `0xbc695a3`, parses the 0x18-byte header, then at `0xbc6a2b1  mov rax,[rax+0xD0]` loads renderer vtable slot 26 and `0xbc6a2c2  call qword ptr [0xF99FFA0]` tail-calls it (thunk sub_eea6040 = `0xeea6040  jmp rax`); on return `0xbc6a49b  mov [r8+0x10],r15` stores the created texture object pointer at handle-table element+0x10 (ctx+0x1E55AB8, element 0x28 bytes). Handle >= 0x1000 requires guard byte ctx+0x1E7DAD0 else fail via 0xbc5f110. BGFX_MAP 6et's "slot 26" reading is confirmed; the earlier TSV "slot 56" label for byte 14 was a script artefact (0xbc6960d is byte 11's handler, slot 56).
2. Found the API-thread producer: sub_bc73770 writes `0xbc73aaa  mov byte ptr [rbp+0x2C],0xE` (command byte 14) into the command buffer [rbx+0xDC5820 + pos at +0xDC5818, rbx = [ctx+0x1CFD0C8]] via `0xbc73ac9  call 0xEBCE390` (memcpy), then `0xbc73af5  call 0xEBCE390` (u16 handle), `0xbc73b1a  call 0xEBCE390` (u64 Memory*), `0xbc73b3f  call 0xEBCE390` (u32 flags), `0xbc73b64  call 0xEBCE390` (u8 skip = 0 at [rbp+0x2D]), bumping `0xbc73ae2  mov [rbx+0xDC5818],ecx` / `0xbc73b6a  inc dword ptr [rbx+0xDC5818]` after each field. Handle allocated by `0xbc7384d  call 0xBC79A60`, stored `0xbc73853  mov [rbp+0x2E],ax` and returned to caller via `0xbc73b74  mov [rsi],di`. Argument order [u16 handle][u64 mem][u32 flags][u8 skip] matches the handler's read order exactly.
3. xref.py callers of the producer: 0xbc73770 -> 0xbc73bf0, 0xbc73ed0, 0xbc74120 (3 thin wrappers; entry `0xbc73bf0  push r15`). Each wrapper also calls validator 0xbc735b0 (texture-description validation, "Texture can't be depth and cube map" strings — it does NOT write command bytes) then 0xbc73770 (the command writer).
4. xref.py callers of the wrappers: 0xbc73bf0 -> 0xbc63c80, 0xc296b50, 0xc297000; 0xbc73ed0 -> 0xc296b50, 0xc2a3d90; 0xbc74120 -> 0xc296b50, 0xc2a3d90. The dragon-layer entry points 0xc296b50 / 0xc297000 / 0xc2a3d90 (and 0xbc63c80, reached from Context::init via 0xbc634b0) are the only static entry points to the producer chain.
5. vtable 0xEFCA580 (the "texture-object init" candidate from the hint): slot 4 (+0x020) = sub_a3f10 (`0xa3f10  push rsi`; body stores interface vtables at +0x00/+0x90/+0xA8 and decrefs via sub_eea6040). It makes NO bgfx call and writes NO command byte — NOT the createTexture producer.
6. Reachability from this unit's functions: none of texgroup_load 0x5421c90 (tail calls 0xE935700, 0x5424000, 0x5424130, 0xEEC6EB0, 0x78ED0, 0x18718D0), texload_task 0x541bf00 (calls 0x1994F90, 0xE935700, 0x78ED0, 0x9BC830), texload 0x58a1310, 0x18718D0, or sub_186dac0 calls 0xbc73770 / 0xbc73bf0 / 0xbc73ed0 / 0xbc74120 / 0xc296b50 / 0xc297000 / 0xc2a3d90 / 0xe8143c0. grep of docs/data/listings for bc73770/bc73bf0/bc73ed0/bc74120/c296b50/c297000/c2a3d90/e8143c0 -> no matches in any listing. No GPU-handle store to TexturePtr+0x00 (mClientTexture shared_ptr) appears anywhere in texgroup_load/texload/texload_task/0x18718D0/sub_186dac0.

## ANSWER TABLE — pack->GPU createTexture issuance (one row per distinct offset; all proof lines verbatim from rdis)

| name | rva or offset | size | verbatim `0xRVA  instr` proof line(s) | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| cmd-byte-14 handler entry | 0xbc69487 | fn start | `0xbc69487  and edx,0xFFFFFFFE` | render-thread command interpreter case 14 handler: createTexture; reads [u16 handle][u64 Memory* mem][u32 flags][u8 skip] | [V] |
| TEX magic gate | 0xbc695a3 | 4 B | `0xbc695a3  cmp dword ptr [rsp+0x8C],0x584554` | handler requires MemoryReader u32 == 0x00584554 (BGFX_CHUNK_MAGIC_TEX) else fails at 0xbc6a28c | [V] |
| renderer object load | 0xbc6a28f | 8 B | `0xbc6a28f  mov rcx,[rdi+0x1EBF2D0]` | rcx = RendererContext object from command-buffer context | [V] |
| handle/flags/mem/skip args | 0xbc6a2a9 | 2 B | `0xbc6a2a9  movzx edx,word ptr [rsp+0x6E]` | u16 handle arg (flags r9d=[rsp+0x90], mem r8=[rsp+0x60], skip byte [rsp+0x6A]) | [V] |
| slot-26 vtable load | 0xbc6a2ae | 8 B | `0xbc6a2ae  mov rax,[rcx]`<br>`0xbc6a2b1  mov rax,[rax+0xD0]` | vtable[0xD0] = slot 26 = createTexture (0xe8143c0, RendererContextD3D12 base vtable 0xF4ED2D0) [I slot name per BGFX_MAP 6k] | [V] |
| slot-26 indirect call | 0xbc6a2c2 | call site | `0xbc6a2c2  call qword ptr [0xF99FFA0]` | CFG thunk sub_eea6040 tails to rax = slot 26 createTexture(handle,mem,flags,skip,header*); `0xeea6040  jmp rax` | [V] |
| createTexture return captured | 0xbc6a2d1 | 8 B | `0xbc6a2d1  mov r15,rax` | rax = created texture object pointer | [V] |
| handle-table guard byte | ctx+0x1E7DAD0 | 1 B | `0xbc6a2e3  movzx ecx,byte ptr [rdi+0x1E7DAD0]` | handles >= 0x1000 require this flag, else guarded-array fail via 0xbc5f110 | [V] |
| texture object stored in handle table | 0xbc6a49b | 8 B | `0xbc6a49b  mov [r8+0x10],r15` | ctx+0x1E55AB8 handle-table element (0x28 bytes) element+0x10 = texture object ptr; pages via sub_bc7a3d0 | [V] |
| producer entry | 0xbc73770 | fn start | `0xbc73770  push rbp` | sub_bc73770(context rcx, &outHandle rdx, Memory* r8, flags r9d): API-thread writer of command byte 14 | [V] |
| command byte 14 written | 0xbc73aaa | 1 B | `0xbc73aaa  mov byte ptr [rbp+0x2C],0xE` | writes cmd byte 0x0E into command stream (first field) | [V] |
| command-buffer pos/data | 0xbc73aae | 4 B | `0xbc73aae  mov eax,[rbx+0xDC5818]`<br>`0xbc73ab8  add rcx,0xDC5820` | pos read from [rbx+0xDC5818]; data base [rbx+0xDC5820]; rbx = [ctx+0x1CFD0C8] | [V] |
| cmd-byte memcpy | 0xbc73ac9 | call site | `0xbc73ac9  call 0xEBCE390` | memcpy(data+pos, &byte 0x0E, 1) (sub_ebce390 = memcpy) | [V] |
| pos bump (u16 slot) | 0xbc73ae2 | 4 B | `0xbc73ae2  mov [rbx+0xDC5818],ecx` | pos = align2(pos)+2 | [V] |
| u16 handle memcpy | 0xbc73af5 | call site | `0xbc73af5  call 0xEBCE390` | memcpy(data+pos, [rbp+0x2E], 2) | [V] |
| u64 mem memcpy | 0xbc73b1a | call site | `0xbc73b1a  call 0xEBCE390` | memcpy(data+pos, [rbp+0x18], 8) | [V] |
| u32 flags memcpy | 0xbc73b3f | call site | `0xbc73b3f  call 0xEBCE390` | memcpy(data+pos, [rbp+0x28], 4) | [V] |
| u8 skip memcpy | 0xbc73b64 | call site | `0xbc73b64  call 0xEBCE390`<br>`0xbc73b6a  inc dword ptr [rbx+0xDC5818]` | memcpy(data+pos, [rbp+0x2D], 1) (skip = 0); pos++ | [V] |
| handle allocator call | 0xbc7384d | call site | `0xbc7384d  call 0xBC79A60`<br>`0xbc73853  mov [rbp+0x2E],ax` | allocates u16 handle from ctx+0x1DF3460; 0xFFFF = exhausted; guard for >= 0x1000 at 0xbc7387a | [V] |
| out-handle store | 0xbc73b74 | 2 B | `0xbc73b70  movzx edi,word ptr [rbp+0x2E]`<br>`0xbc73b74  mov [rsi],di` | *outHandle (rdx arg) = allocated u16 handle; handle also registered via sub_bc7a3d0 at ctx+0x1E55AB8 | [V] |
| producer xrefs | sub_bc73770 | xref | - | xref.py callers 0xbc73770 -> 0xbc73bf0, 0xbc73ed0, 0xbc74120 only | [V] |
| thin createTexture wrappers | 0xbc73bf0 / 0xbc73ed0 / 0xbc74120 | fn start | `0xbc73bf0  push r15`<br>`0xbc73c6c  call 0xBC735B0`<br>`...  call 0xbc73770` (in each wrapper body) | each wrapper: validate texture desc via sub_bc735b0 ("Texture can't be depth and cube map" strings), then issue command-byte-14 via sub_bc73770 | [V] |
| wrapper callers (dragon layer) | 0xc296b50 / 0xc297000 / 0xc2a3d90 / 0xbc63c80 | xref | - | xref.py callers: 0xbc73bf0 -> 0xbc63c80, 0xc296b50, 0xc297000; 0xbc73ed0 -> 0xc296b50, 0xc2a3d90; 0xbc74120 -> 0xc296b50, 0xc2a3d90 | [V] |
| texture-object init candidate | vtable 0xEFCA580 +0x020 | 8 B | `0xa3f10  push rsi`<br>`0xa3f53  mov [rcx],rax`<br>`0xa3f5d  mov [rcx+0x90],rax`<br>`0xa3f6b  mov [rcx+0xA8],rax` | vtable 0xEFCA580 slot 4 = sub_a3f10: stores interface vtables (0xEFCA5A0/5D0/5F0) and decrefs via sub_eea6040; NO bgfx call, NO command-byte write — not the producer | [V] (negative) |
| no direct createTexture call | 0xe8143c0 | - | - | xref.py callers 0xe8143c0 -> empty; ripscan 0xe8143c0 -> only self-refs inside RTX override wrapper e83d390 | [V] (negative) |
| no [reg+0xd0] vcall in .text | .text | - | - | all 16 encodings of `call qword ptr [reg+0xd0]` (rax..r15) -> 0 hits each | [V] (negative) |
| producer chain absent from L8a listings | docs/data/listings | - | - | grep for bc73770/bc73bf0/bc73ed0/bc74120/c296b50/c297000/c2a3d90/e8143c0 -> no matches in any listing | [V] (negative) |
| producer chain absent from L8a callees | texgroup_load / texload_task | - | - | texgroup_load tail calls: 0xE935700, 0x5424000, 0x5424130, 0xEEC6EB0, 0x78ED0, 0x18718D0; texload_task calls: 0x1994F90, 0xE935700, 0x78ED0, 0x9BC830 — none is the producer/wrappers/dragon entry | [V] (negative) |
| no GPU-handle store in L8a | TexturePtr+0x00 | 16 B | - | mClientTexture shared_ptr slot; no store to it anywhere in texgroup_load/texload/texload_task/0x18718D0/sub_186dac0 | [V] (negative) |

## CLOSES?

NO — every static fact about the createTexture issuance is now proven [V], but the pack->GPU link from this unit's texture objects to it is not: the command-byte-14 producer is sub_bc73770 (write byte 0x0E + [u16 handle][u64 Memory*][u32 flags][u8 skip=0] into [ctx+0x1CFD0C8]+0xDC5820/+0xDC5818, allocate handle via sub_bc79a60, return *outHandle), reachable ONLY through thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 from dragon-layer entry points 0xc296b50/0xc297000/0xc2a3d90/0xbc63c80 (xref evidence above). None of texgroup_load 0x5421c90, texload 0x58a1310, texload_task 0x541bf00, callee 0x18718D0, or sub_186dac0 calls any of those addresses, no listing references them, vtable 0xEFCA580 slot 4 (sub_a3f10) is not a createTexture caller, and no GPU-handle write to TexturePtr+0x00 (mClientTexture) exists anywhere in this unit. Single blocking fact: the handle allocated by the command-byte-14 producer and the texture object stored at handle-table element+0x10 are never connected to a ClientTexture/BedrockTexture/TexturePtr field from within this unit — the pack->GPU hand-off is deferred to the dragon-layer frame-time path, which is outside U-EL8a.

## TOOL REQUESTS

None

## NEXT
step 2
