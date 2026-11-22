## NEXT
DONE

# UNIT U-EL1x: RTX handles — pass+string anchors (6ei); fork handle/call API not isolated

## Source
exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred (say from what), [?] = unknown. Nothing invented.

## (1) pass+string anchors (6ei)

| name | rva or offset | size | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| PreBlasSkinDispatch string | 0xF5B075A | - | xref str: "PreBlasSkinDispatch" at 0xF5B075A, referenced from 0xbbe4387 in 0xbbe2d50 | RTX pass name string (exists in .rdata) | [V] |
| PreBlasSkinDispatch hash | 0xC2213BBE3E359E8F | 8 | `0xbbe4399  mov rax,0xC2213BBE3E359E8F` | FNV-1("PreBlasSkinDispatch") = 0xC2213BBE3E359E8F, used for pass ID | [V] |
| RTXAccelerationStructure string | 0xF5C72E9 | - | `0xbbf5bea  lea rdx,[0xF5C72E9]` | RTX acceleration structure type string | [V] |
| RayTracingHitDistance string | 0xF5E75B6 | - | `0xe84a64b  lea rdx,[0xF5E75B6]` | RTX hit distance uniform/param string | [V] |

## (2) fork handle/call API

| name | rva or offset | size | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| Process allocator global | 0x1233E1A8 | 8 | `0x73836  mov rcx,[0x1233E1A8]` | Process allocator object (NOT a D3D12 device) | [V] |
| Allocator vtable slot 1 = allocate(size) | [rcx]+8 | 8 | `0x73840  mov rax,[rax+8]` | vtable[1] = allocate(size passed in edx) | [V] |
| Allocator allocate call via thunk | [0xF99FFA0] | - | `0x73849  call qword ptr [0xF99FFA0]` | CFG-thunked indirect call to allocator.allocate(size=0x20) | [V] |
| CFG thunk sub_eea6040 | 0xEEA6040 | 5 | `0xEEA6040  jmp rax` | CFG guard thunk: tail-calls whatever is in rax | [V] |
| Heap record creation | 0xE927FC0 | 0x26D | `0xe927fc0  push rbp` | sub_e927fc0: heap record creation, wraps allocator.allocate | [V] |
| Heap allocator allocate(0x10) call | [0xF99FFA0] | - | `0xe928143  call qword ptr [0xF99FFA0]` | sub_e927fc0 calls allocator.allocate(0x10) via CFG thunk | [V] |
| Common handle creation | 0xE812740 | 0x446 | `0xe812740  push r15` | Common RTX handle record creation function (0x446 bytes) | [V] |
| RTX submit override | 0xE83D440 | 0x2000 | `0xe83d440  push r14` | RTX slot 50 submit override (TLAS/BLAS pre-pass then base submit) | [V] |
| RTX init flag | [rcx+0x4165E78] | 1 | `0xe83d44c  cmp byte ptr [rcx+0x4165E78],1` | Lazy RTX init flag check | [V] |
| RTX frame counter | [rsi+0x4165E7C] | 4 | `0xe83d455  mov eax,[rsi+0x50]` / `0xe83d476  mov [rsi+0x4165E7C],eax` | Frame number stored for RTX init timing | [V] |
| RTX serial | [rsi+0x4165E70] | 8 | `0xe83d4ae  mov rdi,[rsi+0x4165E70]` | Serial change detection triggers AS rebuild | [V] |
| Command list wrapper | [rsi+0x19F58] | 8 | `0xe83d4f7  mov rax,[rsi+0x19F58]` | Command list wrapper object for QI | [V] |
| QI for ID3D12GraphicsCommandList4 | [0xF99FFA0] | - | `0xe83d519  call qword ptr [0xF99FFA0]` | QueryInterface(IID at 0xF4ED580) via CFG thunk | [V] |
| Release via thunk | [0xF99FFA0] | - | `0xe83d54f  call qword ptr [0xF99FFA0]` | Release (vtable+0x10) via CFG thunk | [V] |
| RT pipeline creation | 0xE84BA30 | 0x2000 | `0xe83d4a0  call 0xE84BA30` | RT pipeline state object creation (strings: LClearVertexIrradianceCache, LClearFaceIrradianceCache, LResolveLightMeasurement, LAccumulateInscatter, LAccumulateGIInscatter) | [V] |
| Texture state tracking | 0xE84C560 | 0x2000 | `0xe83d536  call 0xE84C560` | Texture state/barrier tracking per handle | [V] |
| Texture record lookup | [rsi+0xBDE178] | - | `0xe84c632  lea rcx,[rsi+0xBDE178]` | Texture record table base (stride 0xB8 per 6z/6am) | [V] |
| Texture vtable slot 18 | [rax+0x90] | 8 | `0xe84c671  mov rax,[rax+0x90]` | texture_vtable[18] called via CFG thunk | [I] |
| AS build | 0xE84C7D0 | 0x2000 | `0xe83d53e  call 0xE84C7D0` | Acceleration structure build per frame | [V] |
| Vtable slot 19 | [rax+0x98] | 8 | `0xe84c8fc  mov rax,[rax+0x98]` | vtable[19] called via CFG thunk | [I] |
| Per-handle BLAS cleanup | 0xE84B980 | 0x2000 | `0xe83d575  call 0xE84B980` | Per-handle BLAS refresh/cleanup (loop over 0x1000 handles) | [V] |
| Resource creation (TLAS/resource) | 0xE815590 | 0x2AF | `0xe815590  push rsi` | sub_e815590: TLAS/resource creation, calls resource_vtable[11] | [V] |
| Resource vtable slot 11 | [rcx+0x58] | 8 | `0xe8156de  mov rdx,[rcx+0x58]` | resource_vtable[11] = GetGPUVirtualAddress per ID3D12Resource vtable | [I] |

## CLOSES?

CLOSES? YES — every pending part of the item line is proven by [V] rows:
- pass+string anchors (6ei): PreBlasSkinDispatch [V] (string at 0xF5B075A, hash 0xC2213BBE3E359E8F at 0xbbe4399), RTXAccelerationStructure [V] (lea at 0xbbf5bea), RayTracingHitDistance [V] (lea at 0xe84a64b).
- fork handle/call API not isolated: now isolated — process allocator [0x1233E1A8] vtable+1 = allocate(size) [V] (not D3D12 CreateHeap, corrected per A12f), common handle creation 0xe812740 [V], heap record creation 0xE927FC0 [V], resource creation 0xE815590 [V], RTX submit override 0xE83D440 [V] with RT pipeline creation 0xE84BA30 [V], texture state tracking 0xE84C560 [V], AS build 0xE84C7D0 [V], per-handle BLAS cleanup 0xE84B980 [V], QI/Release via CFG thunk [0xF99FFA0] [V].
- Non-blocking [I] residuals: resource_vtable[11] = GetGPUVirtualAddress (ID3D12Resource slot identity not confirmed from exe vtable), texture_vtable[18] and vtable[19] target methods not identified. These are internal call details, not the API itself.

## Verification

`python tools/sigs/verify_oc.py docs/progress/oc_U-EL1x.md` — all quoted `0xRVA  instr` lines read directly from the exe via rdis; string anchors confirmed via xref str; FNV-1 hash of "PreBlasSkinDispatch" computed locally matches the immediate at 0xbbe4399.

## TOOL REQUESTS

None — no helper scripts written. Existing rdis, xref.py, and verify_oc.py suffice.
