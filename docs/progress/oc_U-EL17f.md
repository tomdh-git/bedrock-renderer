## NEXT
DONE (2026-11-16): U-EL17f field map written - 13 distinct offsets / 42 verbatim claim lines, all [V]; delegate.py check exits 0 (claimed=42 match=42 mismatch=0 no-such-instr=0); CLOSES? YES for L17f (6ay SyncInterval + 6dn slot-60 present interval both proven)

# L17f frame pacing/vsync — static field map (6ay SyncInterval + 6dn slot 60 present interval)

Unit U-EL17f, output file docs/progress/oc_U-EL17f.md (no other file).
Static analysis only (Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base).

Source: verbatim rdis disassembly, two calls:
- `rdis ... dis 0xe811fb0 220`  -> RendererContext slot 6 Present (sub_e811fb0, 0xe811fb0..0xe813fb0)
- `rdis ... dis 0xe81a610 260`  -> RendererContext slot 60 reset (sub_e81a610, 0xe81a610..0xe81c610)

Cross-checked against docs/BGFX_MAP.md sections 6ay (slot 6 Present -> SyncInterval) and 6dn (slot 60 reset entry applies reset flags incl. present interval). One row per distinct offset; every read/store site of that offset is listed in the address cell; the instruction cell holds all verbatim `0xRVA  instr` lines (two spaces after the address, copied from rdis output) `<br>`-separated; sizes come from the instruction (dword/movss 4, qword 8, word 2, byte 1). Meaning is given only where the instruction itself shows it, else '-'. Tag [V] = seen in the disassembly at the cited RVA.

## 6ay — Present (slot 6, 0xe811fb0): SyncInterval derivation

`r15d = [this+0x19F80] >> 7 & 1` (bit 7 = vsync flag) is passed as Present's 2nd argument (SyncInterval); `ebp = (r15*4) ^ 4` is passed as the 3rd argument (Flags => 0 when vsync set, else 4 = tearing allowed). Guard: `this+0x2D8` (main swapchain) non-null and `this+0x19F88 >= 5`. Extra windows: for each handle in the u16 array at `this+0x2FC..` (count u16 at `this+0x2F8`), record `this+0xC97698 + h*0x68` with `byte record+0x64 == 1` gets `([rec+0x18])->Present(sync, flags)` via vtable +0x40, then `record+0x64 = 0`. Present timestamp: QPC delta (0xEBDB740 before/after) stored at `this+0x2F0`.

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| Window record swapchain pointer (record+0x18) | 0x18 | 8 | R: 0xe812036 [rdi+0x18] | `0xe812036  mov rcx,[rdi+0x18]<br>0xe81203a  mov rax,[rcx]<br>0xe81203d  mov rax,[rax+0x40]` | IDXGISwapChain* in the window record; indirect call via vtable +0x40 (Present slot) | [V] |
| Window record dirty/present-pending flag (record+0x64) | 0x64 | 1 | R: 0xe81202b [r14+rdi+0x64]; W: 0xe81204d [rdi+0x64] | `0xe81202b  cmp byte ptr [r14+rdi+0x64],1<br>0xe81204d  mov byte ptr [rdi+0x64],0` | == 1 -> Present that window's swapchain, then cleared to 0 | [V] |
| Context reset-flags word (this+0x19F80) | 0x19F80 | 4 | R: 0xe811fe6 [rsi+0x19F80]; R: 0xe81a788 [rsi+0x19F80]; W: 0xe81a7a4 [rsi+0x19F80] | `0xe811fe6  mov r15d,[rsi+0x19F80]<br>0xe811fed  shr r15d,7><br>0xe811ff1  and r15d,1><br>0xe812041  mov edx,r15d><br>0xe812044  mov r8d,ebp><br>0xe812047  call qword ptr [0xF99FFA0]><br>0xe812093  mov edx,r15d><br>0xe812096  mov r8d,ebp><br>0xe812099  call qword ptr [0xF99FFA0]><br>0xe81a788  mov ebp,[rsi+0x19F80]<br>0xe81a79e  or ebp,0x400000<br>0xe81a7a4  mov [rsi+0x19F80],ebp` | bit 7 -> Present arg2 SyncInterval; Present arg3 Flags = (bit7*4) xor 4 => 0 when bit7 set else 4 (same edx/r8d setup in the single-window path at 0xe812075..0xe812099); slot 60 may set bit 0x400000 (from Frame+0xDC5812 bit 6) | [V] |
| Present guard: init-complete level (this+0x19F88) | 0x19F88 | 4 | R: 0xe811fd1 [rcx+0x19F88]; R: 0xe812282 [rsi+0x19F88]; W: 0xe81228b [rsi+0x19F88] | `0xe811fd1  cmp dword ptr [rcx+0x19F88],5<br>0xe812282  cmp dword ptr [rsi+0x19F88],5<br>0xe81228b  mov dword ptr [rsi+0x19F88],4` | Present proceeds only if >= 5; on device-lost/negative HRESULT set to 4 | [V] |
| Present device-lost HRESULT (this+0x19F8C) | 0x19F8C | 4 | W: 0xe812295 [rsi+0x19F8C] | `0xe812295  mov [rsi+0x19F8C],ebx` | u32 HRESULT of a failed Present stored here (0x88760826 compared at 0xe81227a) | [V] |
| Main swapchain pointer (this+0x2D8) | 0x2D8 | 8 | R: 0xe811fc0 [rcx+0x2D8]; R: 0xe812085 [rsi+0x2D8] | `0xe811fc0  cmp qword ptr [rcx+0x2D8],0<br>0xe812085  mov rcx,[rsi+0x2D8]` | must be non-null; loaded as rcx for the indirect Present call [rcx+0x40] | [V] |
| Present/QPC delta (this+0x2F0) | 0x2F0 | 8 | W: 0xe812240 [rsi+0x2F0] | `0xe811fde  call 0xEBDB740<br>0xe812238  call 0xEBDB740<br>0xe81223d  sub rax,rdi<br>0xe812240  mov [rsi+0x2F0],rax` | u64 = QPC after Present minus QPC before Present (frame-pacing timestamp; 0xEBDB740 is QPC per 6ay) | [V] |
| Extra-window count (this+0x2F8) | 0x2F8 | 2 | R: 0xe812000 [rsi+0x2F8] | `0xe812000  movzx ebx,word ptr [rsi+0x2F8]` | u16 count of extra windows; one Present per handle | [V] |
| Window-handle array (this+0x2FC + idx*2) | 0x2FC | 2 | R: 0xe812020 [rsi+r12*2] | `0xe812020  movzx eax,word ptr [rsi+r12*2]` | u16 window handle h; record = this+0xC97698 + h*0x68 | [V] |
| Slot 60 Frame reset flags (Frame+0xDC5810 via [rdi+8], rdi = Frame+0xDC5808) | 0xDC5810 | 4 | R: 0xe81a71a [rdi+8]; R: 0xe81a734 [rdi+8] | `0xe81a71a  test dword ptr [rdi+8],0x100<br>0xe81a734  mov eax,[rdi+8]` | bgfx::reset flags u32; bit 0x100 -> slot-60 sync interval 0x10 else 1; bit 17 -> byte 0x19FDC | [V] |
| Slot 60 applied sync interval (this+0x19FD8) | 0x19FD8 | 4 | W: 0xe81a72e [rsi+0x19FD8] | `0xe81a721  mov eax,1<br>0xe81a726  mov ecx,0x10<br>0xe81a72b  cmove ecx,eax<br>0xe81a72e  mov [rsi+0x19FD8],ecx` | = 0x10 when Frame-reset-flags bit 0x100 is set, else 1 (cmove on the test result) | [V] |
| Slot 60 second present option byte (this+0x19FDC) | 0x19FDC | 1 | R: 0xe81a737 [rsi+0x19FDC]; W: 0xe81a748 [rsi+0x19FDC] | `0xe81a737  movzx ecx,byte ptr [rsi+0x19FDC]<br>0xe81a73e  shr eax,0x11<br>0xe81a741  and eax,1<br>0xe81a744  cmp eax,ecx<br>0xe81a748  mov [rsi+0x19FDC],al` | byte = (Frame-reset-flags >> 17) & 1, written only when it differs from the current byte | [V] |
| Slot 60 context-flag byte (Frame+0xDC5812 via [rdi+0xA]) | 0xDC5812 | 1 | R: 0xe81a781 [rdi+0xA] | `0xe81a781  movzx eax,byte ptr [rdi+0xA]<br>0xe81a785  shr al,6` | bit 6 of this byte gates slot 60 setting context 0x19F80 bit 0x400000 | [V] |

## 6dn — slot 60 reset entry (0xe81a610): present interval applied

Slot 50 submit (`0xe82e230`) guards with `cmp dword [this+0x19F88],5` and, when `this+0x2D8 != 0`, calls virtual `+0x1E0` = slot 60 with `rdx = Frame + 0xDC5808`, aborting submit if slot 60 returns true. Slot 60 (`0xe81a610`, base; RTX override `0xe83ec70`) first flushes the deferred-release ring, then applies the reset flags from `[rdi+8]` = Frame+0xDC5810: `test [rdi+8],0x100; mov eax,1; mov ecx,0x10; cmove ecx,eax; mov [rsi+0x19FD8],ecx` and `( [rdi+8] >> 17 ) & 1 -> byte [rsi+0x19FDC]` (rewritten only on change, which walks command-list arrays `[this+0x19F60]`/`[this+0x19F68]`). So `bgfx::reset(width,height,flags)` = writing Frame+0xDC5808/0xDC5810 on the game thread; the render thread applies the present interval at the top of the next submit via slot 60.

## Claim lines (verbatim, unindented so verify_oc reads them; same sites as the table)

0xe812036  mov rcx,[rdi+0x18]
0xe81203a  mov rax,[rcx]
0xe81203d  mov rax,[rax+0x40]
0xe81202b  cmp byte ptr [r14+rdi+0x64],1
0xe81204d  mov byte ptr [rdi+0x64],0
0xe811fe6  mov r15d,[rsi+0x19F80]
0xe811fed  shr r15d,7
0xe811ff1  and r15d,1
0xe812041  mov edx,r15d
0xe812044  mov r8d,ebp
0xe812047  call qword ptr [0xF99FFA0]
0xe812093  mov edx,r15d
0xe812096  mov r8d,ebp
0xe812099  call qword ptr [0xF99FFA0]
0xe81a788  mov ebp,[rsi+0x19F80]
0xe81a79e  or ebp,0x400000
0xe81a7a4  mov [rsi+0x19F80],ebp
0xe811fd1  cmp dword ptr [rcx+0x19F88],5
0xe812282  cmp dword ptr [rsi+0x19F88],5
0xe81228b  mov dword ptr [rsi+0x19F88],4
0xe812295  mov [rsi+0x19F8C],ebx
0xe811fc0  cmp qword ptr [rcx+0x2D8],0
0xe812085  mov rcx,[rsi+0x2D8]
0xe811fde  call 0xEBDB740
0xe812238  call 0xEBDB740
0xe81223d  sub rax,rdi
0xe812240  mov [rsi+0x2F0],rax
0xe812000  movzx ebx,word ptr [rsi+0x2F8]
0xe812020  movzx eax,word ptr [rsi+r12*2]
0xe81a71a  test dword ptr [rdi+8],0x100
0xe81a721  mov eax,1
0xe81a726  mov ecx,0x10
0xe81a72b  cmove ecx,eax
0xe81a72e  mov [rsi+0x19FD8],ecx
0xe81a734  mov eax,[rdi+8]
0xe81a737  movzx ecx,byte ptr [rsi+0x19FDC]
0xe81a73e  shr eax,0x11
0xe81a741  and eax,1
0xe81a744  cmp eax,ecx
0xe81a748  mov [rsi+0x19FDC],al
0xe81a781  movzx eax,byte ptr [rdi+0xA]
0xe81a785  shr al,6

## CLOSES?

YES. Every part of the item line "L17f frame pacing/vsync — 6ay (SyncInterval), 6dn (slot 60 present interval)" is proven by [V] rows: (1) 6ay SyncInterval = bit 7 of context+0x19F80 (`0xe811fe6  mov r15d,[rsi+0x19F80]`, `0xe811fed  shr r15d,7`, `0xe811ff1  and r15d,1`) passed as Present arg2 at `0xe812041  mov edx,r15d`, with Present arg3 Flags = (bit7*4) xor 4 (0 vs 4) at `0xe812044  mov r8d,ebp` / `0xe812047  call qword ptr [0xF99FFA0]`; (2) 6dn slot 60 (`0xe81a610`) applies the present interval: `[this+0x19FD8] := 0x10` if Frame-reset-flags bit 0x100 set else `1` (`0xe81a72e  mov [rsi+0x19FD8],ecx` after `0xe81a72b  cmove ecx,eax`), and byte `[this+0x19FDC] := (flags >> 17) & 1` (`0xe81a748  mov [rsi+0x19FDC],al`). The one remaining open fact for L17f is live-only (foreground pacing poll, game was backgrounded when polled) and is outside static analysis scope.

## TOOL REQUESTS

None — used only existing tools (rdis.exe `dis` on the two RVAs; no helper scripts written, no temporary files left behind).
