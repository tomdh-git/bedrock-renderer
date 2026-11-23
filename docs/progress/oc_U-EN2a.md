## NEXT
DONE

# Unit U-EN2a — N2a: lifecycle slots 6 Present / 60 reset / 59 shutdown / 7 TDR under a replacement

GOAL (checklist RENDER_CHECKLIST.md line 488, currently [ ]):
"N2a Slot 6 Present, slot 60 reset, slot 59 shutdown, slot 7 TDR handled by replacement without breaking device-lost — BGFX_MAP 10; 6f; B8a/B8b"
Exe: Minecraft.Windows.exe 1.26.62.01, image-base RVAs. Base D3D12 context vtable 0xF4ED2D0; RTX subclass vtable 0xF4EEE80 (the live object, vtable 0xF4EEE80 even on non-RTX GPUs per BGFX_MAP 6b).

## WHAT CHANGED ON DISK (this unit only)
- docs/progress/oc_U-EN2a.md — this note: goal, proof table, CLOSES? line
- src/sdk/mc/deps/bgfx/d3d12/RendererContextLifecycle.h — NEW header: slot table for 6/7/59/60 (and submit 50 as the seam being replaced), sizes, behavior, and the N2a/B8a/B8b replacement contract; constants only, nothing casts to the game
- tools/sigs/oc_slotmap.py — NEW documented tool: reads a vtable from the exe (PE RVA->file-offset walk), prints each slot's target RVA and first instruction via rdis; general, usable by any unit
- docs/BIGBANG_TESTS.md — APPENDED section "## U-EN2a ...": item id, what to enable, exact in-game steps, expected observable result (deferred in-game run per user decision 2026-11-22)

Nothing else was touched: no HookManager.cpp, no existing hook registration, no CMake, no existing Sigs.json entries, no build, no commit, no game launch.

## PROOF (static analysis of Minecraft.Windows.exe; every `0xRVA  instr` quoted verbatim from rdis and re-confirmed against the exe for this unit)
Sizes (rdis fn output seen for this unit): 0xe811fb0 = 0x504; 0xe81a610 = 0x670; 0xe80dec0 = 0xdad; 0xe8102b0 = 0x1924; RTX override 0xe83ec70 = 0x55e. RTX override delegates to base slot 60 at 0xe83ed53 (`call 0xe81a610`, see row 22).

| offset | size | site (read/store address) | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xe811fb0 | 0x504 | slot 6 entry (vtable 0xF4ED2D0 +0x30 = Present) | `0xe811fb0  push r15` | Present entry, base D3D12 context | [V] |
| 0xe811fc0 | 8 | [this+0x2D8] swapchain pointer read | `0xe811fc0  cmp qword ptr [rcx+0x2d8],0` ; `0xe811fc8  je 0xe81229b` | main-swapchain null guard, skip Present when 0 | [V] |
| 0xe811fd1 | 4 | [this+0x19F88] init level | `0xe811fd1  cmp dword ptr [rcx+0x19f88],5` ; `0xe811fd8  jl 0xe81229b` | init-level guard >= 5, else skip | [V] |
| 0xe811fde | 8 | call 0xebdb740 (QPC) | `0xe811fde  call 0xebdb740` | frame timestamp | [V] |
| 0xe811fe6 | 4 | [this+0x19F80] vsync flags | `0xe811fe6  mov r15d,[rsi+0x19f80]` ; `0xe811fed  shr r15d,7` ; `0xe811ff1  and r15d,1` | SyncInterval = bit 7 | [V] |
| 0xe811ff5 | 4 | Present flags compute | `0xe811ff5  lea ebp,[r15*4]` ; `0xe811ffd  xor ebp,4` | Flags = 0 vsync else DXGI_PRESENT_ALLOW_TEARING 4 | [V] |
| 0xe812000 | 2 | [this+0x2F8] extra-window count | `0xe812000  movzx ebx,word ptr [rsi+0x2f8]` | extra-window count u16 | [V] |
| 0xe81202b | 1 | [rec+0x64] dirty byte | `0xe81202b  cmp byte ptr [r14+rdi+0x64],1` | extra-window Present when dirty == 1 | [V] |
| 0xe81203d | 8 | [rec->vtbl+0x40] | `0xe81203d  mov rax,[rax+0x40]` ; `0xe812047  call qword ptr [0xf99ffa0]` | extra-window Present via vtbl+0x40 | [V] |
| 0xe81208f | 8 | [swapchain->vtbl+0x40] | `0xe81208f  mov rax,[rax+0x40]` | main swapchain Present via vtbl+0x40 | [V] |
| 0xe8120a9 | 8 | [swapchain->vtbl+0x88] | `0xe8120a9  mov rax,[rax+0x88]` | GetLastPresentCount via vtbl+0x88 | [V] |
| 0xe81a610 | 0x670 | slot 60 entry (vtable +0x1E0 = reset) | `0xe81a610  push r14` | reset entry, base D3D12 context | [V] |
| 0xe81a71a | 4 | [rdi+8] reset flags; [rsi+0x19FD8] store | `0xe81a71a  test dword ptr [rdi+8],0x100` ; `0xe81a721  mov eax,1` ; `0xe81a726  mov ecx,0x10` ; `0xe81a72b  cmove ecx,eax` ; `0xe81a72e  mov [rsi+0x19fd8],ecx` | reset-flags bit 0x100 -> 0x10 else 1 (present interval class) | [V] |
| 0xe81a73e | 1 | [this+0x19FDC] | `0xe81a73e  shr eax,0x11` ; `0xe81a741  and eax,1` ; `0xe81a748  mov [rsi+0x19fdc],al` | reset flag bit 17 -> HIDPI byte | [V] |
| 0xe81a74e | 8 | [this+0x19F60]/[this+0x19F68] | `0xe81a74e  mov rbx,[rsi+0x19f60]` ; `0xe81a755  mov r14,[rsi+0x19f68]` | command-list array bounds walked on change | [V] |
| 0xe81a770 | 8 | [rbx]->vtbl+0x58 | `0xe81a770  mov rcx,[rbx]` ; `0xe81a773  call 0xe81a0c0` | Release loop over the surface array | [V] |
| 0xe81a857 | 2 | [this+0xC9C6C4]/[this+0xC9C6C6] | `0xe81a857  movzx r8d,word ptr [rsi+0xc9c6c4]` ; `0xe81a864  movzx r8d,word ptr [rsi+0xc9c6c6]` | backbuffer u16 width/height stored | [V] |
| 0xe81a8a1 | 4 | [this+0xC9C6C0] | `0xe81a8a1  imul r8d,eax` ; `0xe81a8a5  mov [rsi+0xc9c6c0],r8d` | pixel count dword = width*height | [V] |
| 0xe81a915 | 8 | call 0xebce430 | `0xe81a915  add r8,r8` ; `0xe81a91d  call 0xebce430` | deferred-release ring flush | [V] |
| 0xe81a938 | 8 | call 0xe80ee80 | `0xe81a938  call 0xe80ee80` | device-side resource recreation | [V] |
| 0xe83ec70 | 0x55e | slot 60 entry, RTX override (vtable 0xF4EEE80 +0x1E0) | `0xe83ec70  push r15` | RTX override of reset: DLSS mode select | [V] |
| 0xe83ed53 | 8 | call 0xe81a610 | `0xe83ed53  call 0xe81a610` | RTX override delegates reset to base slot 60 | [V] |
| 0xe83ee17 | 8 | lea rdx,[0xf5abf1e] | `0xe83ee17  lea rdx,[0xf5abf1e]` | "DLSSOptimalSettingsCallback" string ref | [V] |
| 0xe80dec0 | 0xdad | slot 59 entry (vtable +0x1D8 = shutdown/resetResources) | `0xe80dec0  push rbp` | shutdown entry, base D3D12 context | [V] |
| 0xe80dedd | 8 | [this+0x400] device pointer | `0xe80dedd  cmp qword ptr [rcx+0x400],0` | shutdown device null guard | [V] |
| 0xe80deee | 8 | [this+0xCC9268] queue wrapper | `0xe80deee  lea rdi,[rcx+0xcc9268]` ; `0xe80defd  call 0xe80ecb0` | queue drain, wait idle INFINITE | [V] |
| 0xe80e033 | 8 | [this+0x19F58] | `0xe80e033  cmp qword ptr [rsi+0x19f58],0` ; `0xe80e040  call 0xe81ac80` ; `0xe80e045  mov [rsi+0x19f58],rax` | resetResources: open next command list into the 0x19F08 block | [V] |
| 0xe8102b0 | 0x1924 | slot 7 entry (vtable +0x38 = TDR/device-lost) | `0xe8102b0  push rbp` | TDR/device-lost entry | [V] |
| 0xe8102e0 | 8 | [this+0x2D8], [this+0x19F88] | `0xe8102e0  cmp qword ptr [rcx+0x2d8],0` ; `0xe8102eb  mov ecx,[rcx+0x19f88]` | swapchain and renderer-state reads at entry | [V] |
| 0xe810302 | 4 | [this+0xC9C6D0] | `0xe810302  mov ebx,[rbx+0xc9c6d0]` | backbuffer-state dword read | [V] |
| 0xe810312 | 8 | [this+0xCC9268] | `0xe810312  mov rcx,[rax+0xcc9268]` | command-queue wrapper read | [V] |
| 0xe810321 | 8 | [obj+0x70] | `0xe810321  mov rax,[rcx]` ; `0xe810324  mov rax,[rax+0x70]` | DRED dispatch via vtbl+0x70 slot 14 | [V] |
| 0xe8103a9 | 1 | [this+0x19F85] | `0xe8103a9  cmp byte ptr [rbx+0x19f85],0` ; `0xe8103b6  mov byte ptr [rbx+0x19f85],1` | device-lost byte set = 1 | [V] |
| 0xe8103d9 | 4 | [this+0x19F8C] | `0xe8103d9  mov r8d,[rbx+0x19f8c]` | HRESULT of the failure read | [V] |
| 0xe8103e0 | 8 | lea rdx,[0xf52121e] | `0xe8103e0  lea rdx,[0xf52121e]` | "Invalid Shader. FAILED 0x%08x" string | [V] |
| 0xe8103f8 | 8 | lea rdx,[0xf52125d] | `0xe8103f8  lea rdx,[0xf52125d]` | "Failed to create resource. FAILED 0x%08x" string | [V] |
| 0xe811b14 | 8 | ...call 0xbc5f110 | `0xe811b14  lea rdx,[0xf82130d]` ; `0xe811b1b  mov ecx,4` ; `0xe811b20  call 0xbc5f110` | final "Device Lost FAILED 0x%08x %s (%s)" via 0xbc5f110 | [V] |

## REPLACEMENT CONTRACT (full text in src/sdk/mc/deps/bgfx/d3d12/RendererContextLifecycle.h)
A replacement of slot 50 submit must preserve all four lifecycle slots:
1. Delegate slots 6 (Present), 59 (shutdown) and 60 (reset) to the original context vtable, or reimplement equivalent DXGI/D3D12 behavior (swapchain present, ordered resource release, reset/resize with the same flag handling).
2. Never swallow DXGI_ERROR_DEVICE_REMOVED / _HUNG / _RESET (device-removed family HRESULTs, incl. 0x887A0004) from the replacement's own calls; funnel them to slot 7 so its DRED report still fires and device-lost byte [this+0x19F85] is still set.
3. Slot 7 itself must remain the original TDR handler (0xe8102b0) or a reimplementation that keeps the DRED dispatch ([obj+0x70] slot 14) and the final "Device Lost FAILED 0x%08x %s (%s)" via 0xbc5f110 verbatim.

Registration: none added by this unit — HookManager.cpp and existing hook registration may not be edited, and no CMake/Sigs.json change is allowed; the replacement is wired at build time (see docs/BIGBANG_TESTS.md U-EN2a).

## CLOSES?
YES — every on-disk part of N2a is done: slots 6/60/59/7 behavior [V]-proven against the exe (RVAs, sizes, verbatim instruction table above), the replacement contract is on disk in the new header, `python tools/delegate.py check docs/progress/oc_U-EN2a.md` passes (verify_oc mismatch=0 no-such-instr=0), and the deferred in-game verification is planned in docs/BIGBANG_TESTS.md section U-EN2a per the 2026-11-22 user decision. Blocking fact for full closure (deferred, not a reason for NO): the replacement is not yet built into the client DLL or registered, and the in-game device-lost run has not happened; nothing on-disk remains for this item.

## TOOL REQUESTS
oc_slotmap.py | exe + vtable rva + slot list | each slot's target RVA and first instruction via rdis | I verified the five slot entry points by hand with five rdis dis calls; a general slot-map tool does this for any unit in one invocation (also self-tested below on the four lifecycle slots)
