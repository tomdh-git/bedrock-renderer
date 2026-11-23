## NEXT
DONE

GOAL: Close checklist item N2a: "Slot 6 Present, slot 60 reset, slot 59 shutdown, slot 7 TDR handled by replacement without breaking device-lost — BGFX_MAP 10; 6f; B8a/B8b" (docs/RENDER_CHECKLIST.md line 488, currently [ ]). Exe: Minecraft.Windows.exe 1.26.62.01, image-base RVAs. Base D3D12 context vtable 0xF4ED2D0; RTX subclass vtable 0xF4EEE80 (BGFX_MAP 6al).

Engineering meaning of "handled by replacement without breaking device-lost": a replacement of the submit path (slot 50) must preserve the four D3D12 lifecycle entry points — either delegate them to the original context vtable or reimplement equivalent DXGI/D3D12 behavior — and must never swallow DXGI_ERROR_DEVICE_REMOVED/HUNG/RESET so slot 7's DRED reporting ("Device Lost FAILED 0x%08x %s (%s)") still fires.

VERIFIED (static, rdis on 1.26.62.01 Minecraft.Windows.exe, all quotes copied verbatim from listings):

1. Vtable slot 6 -> Present: base vtable 0xF4ED2D0 +0x30 = sub_e811fb0 size 0x504 [V] (BGFX_MAP 6ay: Present/swap). Slot 6 is NOT RTX-overridden (6al).
2. Present entry guards main swapchain [this+0x2D8] != 0 and init level [this+0x19F88] >= 5, else skips to the exit path [V].
3. SyncInterval = ([this+0x19F80]>>7)&1 = BGFX_RESET_VSYNC 0x80 bit; Flags = 0 with vsync else DXGI_PRESENT_ALLOW_TEARING 4 (`lea ebp,[r15*4]` then `xor ebp,4`) [V].
4. Extra windows: count u16 [this+0x2F8], records at [this+0xC97698+h*0x68], dirty byte +0x64 == 1 -> Present via [rec]->vtbl+0x40; main swapchain Present via [[this+0x2D8]]->vtbl+0x40; GetLastPresentCount vtbl+0x88 [V].
5. Vtable slot 60 -> reset: base sub_e81a610 size 0x670 [V]; RTX vtable 0xF4EEE80 overrides slot 60 with sub_e83ec70 size 0x55e (DLSS mode select) [V, 6al]; the RTX override calls base slot 60 (0xe81a610) for the actual reset [V].
6. Reset applies the reset-flags u32 (Frame+0xDC5810, i.e. [rdi+8] with rdi=Frame+0xDC5808): flags&0x100 -> [this+0x19FD8]=0x10 else 1 (MaxAnisotropy); bit17 -> [this+0x19FDC] (HIDPI, rebuilds command-list arrays +0x19F60/+0x19F68) [V].
7. Reset stores backbuffer u16 w/h at [this+0xC9C6C4]/[this+0xC9C6C6], pixel count dword at [this+0xC9C6C0] (imul), flushes the deferred-release ring (`call 0xebce430`), then device-side recreation (`call 0xe80ee80`) [V].
8. Reset failure HRESULT 0x887A0004 (DXGI_ERROR_DEVICE_REMOVED, constant present in the e81a610 body) funnels into slot 7 TDR when [this+0x19F88]>=5 (6dn) [V].
9. Vtable slot 59 -> shutdown/resetResources: base sub_e80dec0 size 0xdad [V]; RTX override 0xe83e980 [V per 6al]; touches the 0x19F08 block, releases device [this+0x400] and drains queue 0xCC9268, zeroes extra-window records (stride 0x68 at 0xC97698) [V].
10. Vtable slot 7 -> TDR/device-lost: sub_e8102b0 size 0x1924 [V]; reads queue 0xCC9268, [this+0xC9C6D0], [this+0x19F88], [this+0x19F85]; DRED dispatch via [obj+0x70] slot 14 and [obj+0x8]+0x10 slot 2; jump table selects "Invalid Shader. FAILED 0x%08x" / "Failed to create resource. FAILED 0x%08x"; sets device-lost byte [this+0x19F85]=1; final "Device Lost FAILED 0x%08x %s (%s)" via `call 0xbc5f110` [V].

| name | rva or offset | size | verbatim proof line `0xRVA  instr` | tag |
|---|---|---|---|---|
| slot 6 Present entry (vtable 0xF4ED2D0 +0x30) | 0xe811fb0 | 0x504 | `0xe811fb0  push r15` | [V] |
| Present main-swapchain null guard | 0xe811fc0 | 8 | `0xe811fc0  cmp qword ptr [rcx+0x2d8],0` ; `0xe811fc8  je 0xe81229b` | [V] |
| Present init-level guard (>=5) | 0xe811fd1 | 4 | `0xe811fd1  cmp dword ptr [rcx+0x19f88],5` ; `0xe811fd8  jl 0xe81229b` | [V] |
| Present QPC timestamp | 0xe811fde | 8 | `0xe811fde  call 0xebdb740` | [V] |
| Present sync interval = (this+0x19F80>>7)&1 | 0xe811fe6 | 4 | `0xe811fe6  mov r15d,[rsi+0x19f80]` ; `0xe811fed  shr r15d,7` ; `0xe811ff1  and r15d,1` | [V] |
| Present flags = 0 vsync else tearing 4 | 0xe811ff5 | 4->0 | `0xe811ff5  lea ebp,[r15*4]` ; `0xe811ffd  xor ebp,4` | [V] |
| Present extra-window count u16 | 0xe812000 | 2 | `0xe812000  movzx ebx,word ptr [rsi+0x2f8]` | [V] |
| Present extra-window dirty byte +0x64 | 0xe81202b | 1 | `0xe81202b  cmp byte ptr [r14+rdi+0x64],1` | [V] |
| Present extra-window Present vtbl+0x40 | 0xe81203d | 8 | `0xe81203d  mov rax,[rax+0x40]` ; `0xe812047  call qword ptr [0xf99ffa0]` | [V] |
| Present main swapchain Present vtbl+0x40 | 0xe81208f | 8 | `0xe81208f  mov rax,[rax+0x40]` | [V] |
| Present GetLastPresentCount vtbl+0x88 | 0xe8120a9 | 8 | `0xe8120a9  mov rax,[rax+0x88]` | [V] |
| slot 60 reset entry (vtable +0x1e0, base) | 0xe81a610 | 0x670 | `0xe81a610  push r14` | [V] |
| reset flags&0x100 -> MaxAnisotropy 0x10 else 1 | 0xe81a71a | 4 | `0xe81a71a  test dword ptr [rdi+8],0x100` ; `0xe81a721  mov eax,1` ; `0xe81a726  mov ecx,0x10` ; `0xe81a72b  cmove ecx,eax` ; `0xe81a72e  mov [rsi+0x19fd8],ecx` | [V] |
| reset HIDPI byte bit17 -> [this+0x19FDC] | 0xe81a73e | 1 | `0xe81a73e  shr eax,0x11` ; `0xe81a741  and eax,1` ; `0xe81a748  mov [rsi+0x19fdc],al` | [V] |
| reset command-list arrays +0x19F60/+0x19F68 | 0xe81a74e | 8 | `0xe81a74e  mov rbx,[rsi+0x19f60]` ; `0xe81a755  mov r14,[rsi+0x19f68]` | [V] |
| reset Release loop (vtbl+0x58) | 0xe81a770 | 8 | `0xe81a770  mov rcx,[rbx]` ; `0xe81a773  call 0xe81a0c0` | [V] |
| reset backbuffer u16 w/h | 0xe81a857 | 2 | `0xe81a857  movzx r8d,word ptr [rsi+0xc9c6c4]` ; `0xe81a864  movzx r8d,word ptr [rsi+0xc9c6c6]` | [V] |
| reset pixel count dword [this+0xC9C6C0] | 0xe81a8a1 | 4 | `0xe81a8a1  imul r8d,eax` ; `0xe81a8a5  mov [rsi+0xc9c6c0],r8d` | [V] |
| reset deferred-release ring flush | 0xe81a915 | 8 | `0xe81a915  add r8,r8` ; `0xe81a91d  call 0xebce430` | [V] |
| reset device-side recreation | 0xe81a938 | 8 | `0xe81a938  call 0xe80ee80` | [V] |
| slot 60 RTX override entry (DLSS mode select) | 0xe83ec70 | 0x55e | `0xe83ec70  push r15` | [V] |
| RTX override delegates to base slot 60 reset | 0xe83ed53 | 8 | `0xe83ed53  call 0xe81a610` | [V] |
| RTX DLSSOptimalSettingsCallback string ref | 0xe83ee17 | 8 | `0xe83ee17  lea rdx,[0xf5abf1e]` | [V] |
| slot 59 shutdown entry (vtable +0x1d8, base) | 0xe80dec0 | 0xdad | `0xe80dec0  push rbp` | [V] |
| shutdown device [this+0x400] null guard | 0xe80dedd | 8 | `0xe80dedd  cmp qword ptr [rcx+0x400],0` | [V] |
| shutdown queue 0xCC9268 drain | 0xe80deee | 8 | `0xe80deee  lea rdi,[rcx+0xcc9268]` ; `0xe80defd  call 0xe80ecb0` | [V] |
| shutdown resetResources on 0x19F08 block | 0xe80e033 | 8 | `0xe80e033  cmp qword ptr [rsi+0x19f58],0` ; `0xe80e040  call 0xe81ac80` ; `0xe80e045  mov [rsi+0x19f58],rax` | [V] |
| slot 7 TDR entry (vtable +0x38) | 0xe8102b0 | 0x1924 | `0xe8102b0  push rbp` | [V] |
| TDR this+0x2D8 / this+0x19F88 reads | 0xe8102e0 | 8 | `0xe8102e0  cmp qword ptr [rcx+0x2d8],0` ; `0xe8102eb  mov ecx,[rcx+0x19f88]` | [V] |
| TDR [this+0xC9C6D0] read | 0xe810302 | 4 | `0xe810302  mov ebx,[rbx+0xc9c6d0]` | [V] |
| TDR queue 0xCC9268 read | 0xe810312 | 8 | `0xe810312  mov rcx,[rax+0xcc9268]` | [V] |
| TDR DRED dispatch [obj+0x70] slot 14 | 0xe810321 | 8 | `0xe810321  mov rax,[rcx]` ; `0xe810324  mov rax,[rax+0x70]` | [V] |
| TDR device-lost byte [this+0x19F85] set=1 | 0xe8103a9 | 1 | `0xe8103a9  cmp byte ptr [rbx+0x19f85],0` ; `0xe8103b6  mov byte ptr [rbx+0x19f85],1` | [V] |
| TDR [this+0x19F8C] read | 0xe8103d9 | 4 | `0xe8103d9  mov r8d,[rbx+0x19f8c]` | [V] |
| TDR "Invalid Shader. FAILED 0x%08x" ref | 0xe8103e0 | 8 | `0xe8103e0  lea rdx,[0xf52121e]` | [V] |
| TDR "Failed to create resource. FAILED 0x%08x" ref | 0xe8103f8 | 8 | `0xe8103f8  lea rdx,[0xf52125d]` | [V] |
| TDR "Device Lost FAILED 0x%08x %s (%s)" via 0xbc5f110 | 0xe811b14 | 8 | `0xe811b14  lea rdx,[0xf82130d]` ; `0xe811b1b  mov ecx,4` ; `0xe811b20  call 0xbc5f110` | [V] |

CHANGES ON DISK (this unit only):
- docs/progress/oc_U-EN2a.md — this note.

CLOSES?: NO — every slot behavior above is [V]-proven statically and the replacement contract is defined (delegate slots 6/59/60/7 to the original context or reimplement; never swallow DXGI_ERROR_DEVICE_REMOVED/HUNG/RESET so slot 7 DRED reporting still fires), but no replacement submit path is built, installed, or observed preserving device-lost in-game. Single blocking fact: the replacement must be compiled into the client DLL, registered, and verified that slot 7 still fires on DXGI device-removed/hung/reset; builds and live launch are outside this unit.

## NEXT
step 2
