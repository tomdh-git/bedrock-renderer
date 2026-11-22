## NEXT
DONE

# Unit U-EQ4c — Q4c: descriptor/upload ring and root signature ownership understood; device-lost/TDR path (slot 7) verified

## (1) Paths changed

Created: `docs/progress/oc_U-EQ4c.md` — the only file created or modified.
No existing files touched: no hook registration, no HookManager.cpp, no CMake, no Sigs.json edits, no builds, no game launch. Static analysis only (rdis.exe dis/vt on the exe as data).

## (2) Proof table

Columns: offset | size | site (read/store address) | verbatim `0xRVA  instr` | meaning | tag.
Sizes are the access sizes implied by the instruction (qword 8, dword 4, byte 1, movups 16). No offset repeated; no "etc."; every `0xRVA  instr` line copied verbatim from rdis `dis`/`vt` output of the exe.

| offset | size | site | verbatim instr | meaning | tag |
|--------|------|------|----------------|---------|-----|
| 0x2D8 | 8 | R [rcx+0x2D8] | `e8102e0  cmp qword ptr [rcx+0x2D8],0` | Slot-7 (TDR/device-lost) handler entry: short-circuit when non-null | [V] |
| 0x19F88 | 4 | R [rcx+0x19F88] | `e8102eb  mov ecx,[rcx+0x19F88]` | renderer state read by slot 7; proceeds only while state < 5 (`e8102f1  cmp ecx,5; setl dl`) | [V] |
| 0xCC9268 | 8 | R [rax+0xCC9268] | `e810312  mov rcx,[rax+0xCC9268]` | command queue object used by the slot-7 Release drain loop (`e810321 mov rax,[rcx]; e810324 mov rax,[rax+0x70]; e810328 call qword ptr [0xF99FFA0]`) | [V] |
| 0xC9C6D0 | 4 | R [rbx+0xC9C6D0] | `e810302  mov ebx,[rbx+0xC9C6D0]` | release-record index (rbx) into the [ctx+0x30] record array | [V] |
| 0x30 | 8 | W [r12+rbx*8+0x30] | `e810390  mov [r12+rbx*8+0x30],rax` | release-record slot cleared after Release; loop walks 0x88-stride records (`e810350..e81037f`, r14 += 0x88; Release via `e810365 mov rax,[rcx]; e810368 mov rax,[rax+0x10]`) | [V] |
| 0x19F85 | 1 | R [rbx+0x19F85] / W [rbx+0x19F85] | `e8103a9  cmp byte ptr [rbx+0x19F85],0` / `e8103b6  mov byte ptr [rbx+0x19F85],1` | device-lost flag: tested (skip if already 1) then set to 1 | [V] |
| 0x19F8C | 4 | R [rbx+0x19F8C] | `e811a1e  mov r8d,[rbx+0x19F8C]` | HRESULT logged as "Device Lost FAILED 0x%08x %s (%s)" (`e811b14  lea rdx,[0xF82130D]; e811b20  call 0xBC5F110`); compared against 0x887A0005 DXGI_ERROR_DEVICE_REMOVED (`e811a25  cmp r8d,0x887A0005`); name-table strings `e811a60 "DXGI_ERROR_DEVICE_REMOVED"`, `e811a76 "S_OK"`, `e811a7f "Unknown HRESULT?"`, `e811a88 NOT_CURRENTLY_AVAILABLE`, `e811a91 DEVICE_RESET`, `e811a9a DEVICE_HUNG`, `e811aa3 DRIVER_INTERNAL_ERROR` | [V] |
| 0x19F08 | 8 | W [rsi+0x19F08] | `e808aca  mov [rsi+0x19F08],r12` | context owns LDefaultBufferHeap descriptor heap (0x190-byte heap object created via sub_e927fc0, name string `e808ab0  lea rdx,[0xF8481B2] "LDefaultBufferHeap"`) | [V] |
| 0x19F10 | 8 | W [rsi+0x19F10] | `e808b55  mov [rsi+0x19F10],r12` | LTextureBufferHeap (`e808b3b  lea rdx,[0xF8481FC] "LTextureBufferHeap"`) | [V] |
| 0x19F18 | 8 | W [rsi+0x19F18] | `e808be0  mov [rsi+0x19F18],r12` | LUploadBufferHeap (`e808bc6  lea rdx,[0xF848260] "LUploadBufferHeap"`) | [V] |
| 0x19F20 | 8 | W [rsi+0x19F20] | `e808c6b  mov [rsi+0x19F20],r12` | LReadBackBufferHeap (`e808c51  lea rdx,[0xF8481D6] "LReadBackBufferHeap"`) | [V] |
| 0x19F30 | 8 | W [rsi+0x19F30] | `e808cf6  mov [rsi+0x19F30],r12` | LAccelerationStructureBufferHeap (`e808cdc  lea rdx,[0xF848220] "LAccelerationStructureBufferHeap"`) | [V] |
| 0x238 | 8 | R/W [rsi+0x238] | `e808d6e  lea rcx,[rsi+0x238]` | upload-ring ID3D12Resource: created by sub_e809c30 (`e808d78  call 0xE809C30`), size = (nodes+1)*0x3FFFC0+0x1000000 (`e808d4d  imul rax,0x3FFFC0; e808d54  add rax,0x1000000`), null-checked `e808d8b  cmp qword ptr [rsi+0x238],0`, mapped via sub_e809f40/sub_e809fb0 | [V] |
| 0x240 | 8 | W r15=&[rsi+0x240] | `e808d2c  lea r15,[rsi+0x240]` | upload-ring mapped CPU-pointer slot, filled by `e808db6  call 0xE809FB0`; released at shutdown via sub_e80dd60 (`e808774  lea rdi,[rsi+0x240]`) | [V] |
| 0x19F60 | 8/slot | R/W arena {curr [+8], end [+0x10]} | `e80c1a7  mov [r14],rax` / `e80c1aa  add qword ptr [rsi+8],8` (sub_e80c180, entered from `e80935c  call 0xE80C180`) | per-node arena of root-signature builder-object pointers; bump-allocated (sub_e80c180 grows 1.5x; destroys entries with sub_e81da20 + sub_e935700(0x2268)) | [V] |
| 0x2E8 | 4 | W [rsi+0x2E8] / R loop bound | `e809305  mov [rsi+0x2E8],edx` / `e80936d  mov eax,[rsi+0x2E8]` | node count (1 or 2: `e8092fa  mov eax,[rdi+0x24]; e809302  movzx edx,al`); builder 0xe80c600 invoked once per node (`e809338..e809376` loop: `e809350 call 0xE80C600; e80935c call 0xE80C180; e809365 call 0xE80DA20; inc r12; cmp r12,[rsi+0x2E8]`) | [V] |
| +0x1248 (builder object) | 8 | R/W [rax+0x1248] / [r12] | `e80cf77  mov qword ptr [rax+0x1248],0` / `e80d34e  mov rsi,[r12]` | ID3D12RootSignature* field of the 0x2268-byte root-signature builder object (`e80c64e  mov edx,0x2268; e80c653 call qword ptr [0xF99FFA0]` alloc via [0x1233E1A8]); read at e80d34e to bind the root signature | [V] |
| +0x11D8 (builder object) | 8 | W [rcx+0x11D8] | `e80d36c  mov [rcx+0x11D8],rax` (`e80d35b  mov rax,0x4000000200`) | builder field set to 0x4000000200 (root-signature flags/handle) | [V] |
| +0x11E0 (builder object) | 4 | W [rcx+0x11E0] | `e80d373  mov dword ptr [rcx+0x11E0],0x200` | builder field set to 0x200 | [V] |
| +0x8 (builder object) | 8 | W [rcx+8] | `e80d29b  mov [rcx+8],rax` | builder+8 = upload buffer holding the serialized root-signature blob (created `e80d1c2  call r10`, r8d=0x204; descriptor ranges filled `e80d1d3..e80d28d` movups from 0xF441430..0xF441520) | [V] |
| 0xF5C750E | 8 | R [0xF5C750E] (import name) | `e808108  lea rdx,[0xF5C750E]` / `e808114  mov [0x12BB4930],rax` | "D3D12SerializeRootSignature" import resolved via GetProcAddr (`e80810f call 0xED35E80`) into global 0x12BB4930; invoked at `e80d101  mov rax,[0x12BB4930]; e80d122  call qword ptr [0xF99FFA0]` (rcx=&desc [rbp+0x1F0], edx=1 version, r8=&blob [rbp+0x268], r9=&size [rbp+0xC8]) | [V] |
| 0xe80d18d | 5 | call r11 | `e80d18d  call r11` | CreateRootSignature through device vtable slot 0x80 (`e80d160  mov r10,[rcx+0x80]; e80d167  mov r11,[0xF99FFA0]`); result = ID3D12RootSignature* stored at builder+0x1248 | [V] |
| 0xe82e4b0 | 5 | call 0xE8360F0 | `e82e4b0  call 0xE8360F0` | submit descriptor/upload-ring range-allocator call #1: rcx=[ctx+0x238]+8, r8=[ctx+0xDC57F0] (transient IB size), r9d=0x10 align, rdx=&desc [rbp+0x7E0] | [V] |
| 0xe82e6c1 | 5 | call 0xE8360F0 | `e82e6c1  call 0xE8360F0` | submit range-allocator call #2: r8=[ctx+0xDC57F4] (transient VB size) | [V] |
| 0xe82f06c | 5 | call 0xE8360F0 | `e82f06c  call 0xE8360F0` | submit range-allocator call #3: r8 computed from ring free space | [V] |
| 0xe836113 | 8 | W [rcx+8] | `e836113  lock inc qword ptr [rcx+8]` | top of range allocator 0xe8360f0 (rcx=heap obj, rdx=&outDesc, r8=size, r9=align): bumps heap +8, carves via sub_e836640/sub_e836770, writes descriptor `e83615e  movups [rsi],xmm0`, advances cursor `e83614c  lock add [rbx+0x18],rax` | [V] |

Slot-7 vtable placement [V]: `vt 0xF4ED2D0` and `vt 0xF4EEE80` both report `7 +0x038 sub_e8102b0 size 0x1924 push rbp` — slot 7 (+0x38) of the base D3D12 vtable and of the "Direct3D 12 RTX" subclass vtable are identical (sub_e8102b0), i.e. RTX does not override slot 7. Function body span: 0xe8102b0..0xe811be0 (0x1930 bytes; `e811bd3  int3` is its last instruction, `e811be0` starts the next function). No direct callers (rdis callers = 0); reached only through vtable slot dispatch.

Slot-7 terminal path [V]: DRED breadcrumb walk when byte [0x12AE16F0]==1 (`e810409  cmp byte ptr [0x12AE16F0],1`, buffers [0x12AE16F8]/[0x12AE1700], [0x12AE1710]/[0x12AE1718], [0x12AE1728]/[0x12AE1730], stride 0x20 cap 0x1000, printer 0xE935700); HRESULT hex formatting (`e81136b  neg eax; e811380..e8113ab` digit loop into [rbp+rcx+0x2E]; `e8113b0  mov byte ptr [rbp+rcx+0x2E],0x2D`); final log `e811b25  jmp 0xE8104C9`; function epilogue `e8104c9..e8104e3 ret`.

Upload-ring shutdown [V]: `e80870a  mov qword ptr [rsi+0x2D8],0; e808715 lea rcx,[rsi+0xCC9268]; e80871c call 0xE80DA50` then `e808721  mov rdi,[rsi+0x238]; e808728  mov qword ptr [rsi+0x238],0`; per-heap teardown walks the five L* heaps at +0x19F08/+0x19F10/+0x19F18 (+0x19F20/+0x19F30 similarly, `e808e5b..e8090a3`) releasing via sub_e92a5f0 after sub_e80dd60.

## (3) Ownership conclusion (all [V])

- **Descriptor ring ownership:** the RendererContextD3D12 object (rcx of submit, vtable 0xF4ED2D0 / RTX 0xF4EEE80) owns five descriptor heaps stored at +0x19F08/+0x19F10/+0x19F18/+0x19F20/+0x19F30, created in init slot 58 (0xe807ff0), plus the upload-ring resource at +0x238 with mapped pointer at +0x240. The upload ring is the object submitted to range allocator 0xe8360f0 (`rcx = [ctx+0x238]+8`) exactly 3 times per submit (e82e4b0, e82e6c1, e82f06c).
- **Root signature ownership:** init slot 58 builds one root signature per node ([ctx+0x2E8] nodes): D3D12SerializeRootSignature (global 0x12BB4930) at e80d122, then CreateRootSignature via device vtbl+0x80 at e80d18d; the ID3D12RootSignature* is kept at builder-object +0x1248 (builder objects are 0x2268 bytes, stored one-per-node in the bump arena at ctx+0x19F60 via sub_e80c180); related fields builder+0x11D8 = 0x4000000200 and builder+0x11E0 = 0x200; builder+8 holds the upload buffer with the serialized blob.
- **Device-lost/TDR path (slot 7) verified:** slot 7 = sub_e8102b0 (0xe8102b0, size 0x1930, identical in base and RTX vtables at +0x38), reached only via vtable dispatch. It drains deferred-release records ([ctx+0x30] array indexed by [ctx+0xC9C6D0]) through the command queue ([ctx+0xCC9268]), sets device-lost byte [ctx+0x19F85], walks DRED breadcrumbs, formats the HRESULT from [ctx+0x19F8C], and logs "Device Lost FAILED 0x%08x %s (%s)" via 0xBC5F110, special-casing DXGI_ERROR_DEVICE_REMOVED 0x887A0005.

## CLOSES?

YES — every pending part of Q4c ("Descriptor/upload ring and root signature ownership understood; device-lost/TDR path (slot 7) verified") is proven on disk by [V] rows above: descriptor heaps at +0x19F08/+0x19F10/+0x19F18/+0x19F20/+0x19F30, upload-ring resource +0x238 / mapped pointer +0x240, range allocator 0xe8360f0 with its 3 submit call sites (e82e4b0/e82e6c1/e82f06c), root signature built per node (serialize e80d122, CreateRootSignature e80d18d via vtbl+0x80, ID3D12RootSignature* at builder +0x1248, builder arena at +0x19F60, node count +0x2E8), and slot 7 = sub_e8102b0 verified in both vtables with its full device-lost/TDR body. Nothing in the item wording remains unproven.

## TOOL REQUESTS

None — all evidence gathered with rdis.exe dis/vt only; no helper scripts needed.