## NEXT
DONE

# U-EL2l — fence wait internals (L2l)

Pending part of checklist item: "L2l Queue wrapper +0xCC9268, current list +0x19F58, submit/flush slots 8/61/62, frame-context ring — 6av; fence wait internals pending". Everything before the semicolon is already [V] in docs/BGFX_MAP.md section 6av (queue wrapper this+0xCC9268, current list this+0x19F58, slot 8 flushAndWaitIdle 0xe80f630, slot 61 submitCurrentCommandList 0xe81ae10, slot 62 kickPendingSurfaces 0xe81b0f0, ring head this+0x3C55B10 / tail this+0x3C55B18 / entries this+0x3C55290 / 0x110 slots). This note decodes ONLY the pending part: the fence wait itself, i.e. sub_e80ecb0(queueWrapper, timeout) and its wait primitive sub_e818490. All RVAs verified by rdis disassembly of the exe (1.26.62.01); verbatim instruction proofs are listed below the table.

Bases: `this` = RendererContext (rcx of the vtable slots); `queueWrapper = this + 0xCC9268` [V]; `fenceWrapper = [queueWrapper + 0x2F8D148] = this + 0x3C563B0` [V: `mov rbx,[rdi+0x2F8D148]`, arithmetic [I]]; a fence slot is a 0x88-stride object bracketed by `fenceWrapper+0x0` (begin) and `fenceWrapper+0x8` (end) [V]. "surface" = per-frame command-allocator/context object (stride >= 0x2CBE0, per 6av).

| name | offset | size | verbatim `0xRVA  instr` proof | tag |
|---|---|---|---|---|
| command-queue wrapper base (first qword = ID3D12CommandQueue* [I per 6av]) | this+0xCC9268 | 8 | 0x0E80F64B  lea rdi,[rsi+0xCC9268]; also 0x0E80EE9E | [V] |
| pending-surface count (u64); gate + clear of the ExecuteCommandLists kick | queueWrapper+0x2F8C020 (= this+0x3C55288) | 8 | 0x0E80ECD7  mov rax,[rcx+0x2F8C020]; 0x0E80EDAB  mov qword ptr [rdi+0x2F8C020],0 | [V] |
| pending surface object array (8-byte pointers) | queueWrapper+0x2F8B7A0 (= this+0x3C54A08) | 8 | 0x0E80ED3D  mov r8,[rdi+rdx*8+0x2F8B7A0] | [V] |
| ring head index (u64); movups zeroes head+tail (16B) when tail wraps | queueWrapper+0x2F8C8A8 (= this+0x3C55B10) | 8 | 0x0E80ED70  cmp r9,[rdi+0x2F8C8A8]; 0x0E8185A9  mov rax,[rsi+0x2F8C8A8]; 0x0E818632  mov [rsi+0x2F8C8A8],rcx; 0x0E80ECEB  lea rcx,[rdi+0x2F8C8A8]; 0x0E80ED00  movups [rcx],xmm0 | [V] |
| ring tail index (u64, mod 0x110) | queueWrapper+0x2F8C8B0 (= this+0x3C55B18) | 8 | 0x0E80ED45  mov r10,[rdi+0x2F8C8B0]; 0x0E80ED69  mov [rdi+0x2F8C8B0],r9; 0x0E818595  mov rcx,[rsi+0x2F8C8B0]; 0x0E818603  mov qword ptr [rsi+0x2F8C8B0],0x110 | [V] |
| ring entries (8-byte surface pointers, 0x110 slots) | queueWrapper+0x2F8C028 (= this+0x3C55290) | 8 | 0x0E80ED06  mov [rdi+r9*8+0x2F8C028],r8; 0x0E8185B0  mov r9,[rsi+rax*8+0x2F8C028] | [V] |
| fence wrapper pointer | queueWrapper+0x2F8D148 (= this+0x3C563B0 = fenceWrapper) | 8 | 0x0E80EDB6  mov rbx,[rdi+0x2F8D148]; 0x0E8184D2  mov rbx,[rcx+0x2F8D148] | [V] |
| fence object (ID3D12Fence*; vtable+0x40 = GetCompletedValue, +0x48 = SetEventOnCompletion [I]) | fenceWrapper+0x18 | 8 | 0x0E80EDC0  mov rdx,[rbx+0x18]; 0x0E8184F2  mov rcx,[rbx+0x18] | [V] |
| wait event (HANDLE) | fenceWrapper+0x20 | 8 | 0x0E8184F6  mov r8,[rbx+0x20]; 0x0E81850E  mov rcx,[rbx+0x20] | [V] |
| fence next-value to signal (u64) | fenceWrapper+0x28 | 8 | 0x0E80ED15  mov r9,[r9+0x28]; 0x0E80EDC4  mov r8,[rbx+0x28]; 0x0E80EDD5  inc qword ptr [rbx+0x28]; 0x0E80EE26  mov rdx,[rbx+0x28] | [V] |
| cached completed value (u64, from GetCompletedValue; -1 = invalid fence [I]) | fenceWrapper+0x30 | 8 | 0x0E81B3E1  mov [rdi+0x30],rax; 0x0E8184EC  cmp [rbx+0x30],rax | [V] |
| fence slot-array bounds (+0x0 = begin, +0x8 = end; 0x88-stride slots) | fenceWrapper+0x0 / +0x8 | 8 | 0x0E80EDD9  mov r15,[rbx]; 0x0E80EDDC  mov r12,[rbx+8] | [V] |
| fence slot event object A | fenceSlot+0x78 (stride 0x88) | 8 | 0x0E80EDF9  mov rcx,[r15+0x78] | [V] |
| fence slot event object B | fenceSlot+0x38 (stride 0x88) | 8 | 0x0E81B419  mov rcx,[r14+0x38] | [V] |
| surface fence stamp (u64; receives fenceWrapper+0x28) | surface+0x2CBD0 | 8 | 0x0E80ED19  mov [r8+0x2CBD0],r9; 0x0E8185CD  cmp [r9+0x2CBD0],rdx | [V] |
| surface submitted flag (byte) | surface+0x2CBD8 | 1 | 0x0E80ED20  mov byte ptr [r8+0x2CBD8],1; 0x0E8185B8  cmp byte ptr [r9+0x2CBD8],0 | [V] |
| reap copy: surface+0x2CBE0 -> surface+0x2CBE8 (u64 each) | surface+0x2CBE0 / +0x2CBE8 | 8 | 0x0E818580  mov rax,[r9+0x2CBE0]; 0x0E818587  mov [r9+0x2CBE8],rax | [V] |
| high-water skip (u64; wait skipped when >= value) | queueWrapper+0x2F8B798 | 8 | 0x0E8184BF  cmp [rcx+0x2F8B798],rdx | [V] |
| sub_e80ecb0(queueWrapper rcx, timeout edx) — fence-wait entry (kick + signal + wait) | 0xe80ecb0 | - | 0x0E80ECC0  mov esi,edx; 0x0E80ECC2  mov rdi,rcx | [V] |
| ID3D12CommandQueue::ExecuteCommandLists(count, array) via queue vtable +0x50 [I name per 6av] | 0xe80eda5 (call site) | - | 0x0E80ED9C  mov rax,[rax+0x50]; 0x0E80EDA5  call qword ptr [0xF99FFA0] | [V] |
| queue->Signal(fence = [fenceWrapper+0x18], value = [fenceWrapper+0x28]) via vtable +0x70 [I name] | 0xe80edcf (call site) | - | 0x0E80EDCB  mov rax,[rax+0x70]; 0x0E80EDCF  call qword ptr [0xF99FFA0] | [V] |
| sub_e81b3b0(fenceWrapper) -> al (completed != -1); caches fence->GetCompletedValue (vtable+0x40 [I]) at +0x30 | 0xe81b3b0 | - | 0x0E81B3CD  mov rcx,[rcx+0x18]; 0x0E81B3D4  mov rax,[rax+0x40]; 0x0E81B3E1  mov [rdi+0x30],rax | [V] |
| sub_e818490(queueWrapper, fenceValue, timeout) — the blocking wait | 0xe818490 | - | 0x0E8184BF  cmp [rcx+0x2F8B798],rdx; 0x0E8184FD  mov rax,[rax+0x48]; 0x0E818508  call qword ptr [0xF99FFA0]; 0x0E818518  call qword ptr [0xF9A7B68]; 0x0E818535  cmp qword ptr [rax+0x30],0xFFFFFFFFFFFFFFFF | [V] |
| sub_e80ee80(this, reopen) — flush+wait helper: slot 61 (vtbl+0x1E8, reopen=0), TWO INFINITE fence waits, current list = 0; called from slot 59 shutdown (0xe80dec0) and slot 60 reset (0xe81a610) [V xref callers] | 0xe80ee80 | - | 0x0E80EE98  call qword ptr [0xF99FFA0]; 0x0E80EEA8  mov edx,0xFFFFFFFF; 0x0E80EEAD  call 0xE80ECB0; 0x0E80EEB2  mov qword ptr [rsi+0x19F58],0; 0x0E80EEC5  call 0xE80ECB0 | [V] |
| slot 8 flushAndWaitIdle(this) | 0xe80f630 | - | 0x0E80F645  call qword ptr [0xF99FFA0]; 0x0E80F655  mov edx,0xFFFFFFFF; 0x0E80F65A  call 0xE80ECB0; 0x0E80F662  call 0xE81AC80; 0x0E80F667  mov [rsi+0x19F58],rax | [V] |

Verbatim instruction proofs (one line per site, exactly as rdis prints them; these are the verified claims):
    0x0E80F64B  lea rdi,[rsi+0xCC9268]
    0x0E80ECD7  mov rax,[rcx+0x2F8C020]
    0x0E80EDAB  mov qword ptr [rdi+0x2F8C020],0
    0x0E80ED3D  mov r8,[rdi+rdx*8+0x2F8B7A0]
    0x0E80ED70  cmp r9,[rdi+0x2F8C8A8]
    0x0E818632  mov [rsi+0x2F8C8A8],rcx
    0x0E80ED00  movups [rcx],xmm0
    0x0E80ED45  mov r10,[rdi+0x2F8C8B0]
    0x0E80ED69  mov [rdi+0x2F8C8B0],r9
    0x0E818595  mov rcx,[rsi+0x2F8C8B0]
    0x0E818603  mov qword ptr [rsi+0x2F8C8B0],0x110
    0x0E80ED06  mov [rdi+r9*8+0x2F8C028],r8
    0x0E8185B0  mov r9,[rsi+rax*8+0x2F8C028]
    0x0E80EDB6  mov rbx,[rdi+0x2F8D148]
    0x0E8184D2  mov rbx,[rcx+0x2F8D148]
    0x0E80EDC0  mov rdx,[rbx+0x18]
    0x0E8184F2  mov rcx,[rbx+0x18]
    0x0E8184F6  mov r8,[rbx+0x20]
    0x0E81850E  mov rcx,[rbx+0x20]
    0x0E80ED15  mov r9,[r9+0x28]
    0x0E80EDC4  mov r8,[rbx+0x28]
    0x0E80EDD5  inc qword ptr [rbx+0x28]
    0x0E80EE26  mov rdx,[rbx+0x28]
    0x0E81B3E1  mov [rdi+0x30],rax
    0x0E8184EC  cmp [rbx+0x30],rax
    0x0E80EDD9  mov r15,[rbx]
    0x0E80EDF9  mov rcx,[r15+0x78]
    0x0E81B419  mov rcx,[r14+0x38]
    0x0E80ED19  mov [r8+0x2CBD0],r9
    0x0E8185CD  cmp [r9+0x2CBD0],rdx
    0x0E80ED20  mov byte ptr [r8+0x2CBD8],1
    0x0E8185B8  cmp byte ptr [r9+0x2CBD8],0
    0x0E818580  mov rax,[r9+0x2CBE0]
    0x0E818587  mov [r9+0x2CBE8],rax
    0x0E8184BF  cmp [rcx+0x2F8B798],rdx
    0x0E80ECC0  mov esi,edx
    0x0E80ECC2  mov rdi,rcx
    0x0E80ED9C  mov rax,[rax+0x50]
    0x0E80EDA5  call qword ptr [0xF99FFA0]
    0x0E80EDCB  mov rax,[rax+0x70]
    0x0E80EDCF  call qword ptr [0xF99FFA0]
    0x0E81B3D4  mov rax,[rax+0x40]
    0x0E81B3E1  mov [rdi+0x30],rax
    0x0E8184BF  cmp [rcx+0x2F8B798],rdx
    0x0E8184FD  mov rax,[rax+0x48]
    0x0E818508  call qword ptr [0xF99FFA0]
    0x0E818518  call qword ptr [0xF9A7B68]
    0x0E818535  cmp qword ptr [rax+0x30],0xFFFFFFFFFFFFFFFF
    0x0E80EE98  call qword ptr [0xF99FFA0]
    0x0E80EEA8  mov edx,0xFFFFFFFF
    0x0E80EEAD  call 0xE80ECB0
    0x0E80EEB2  mov qword ptr [rsi+0x19F58],0
    0x0E80EEC5  call 0xE80ECB0
    0x0E80F645  call qword ptr [0xF99FFA0]
    0x0E80F655  mov edx,0xFFFFFFFF
    0x0E80F65A  call 0xE80ECB0
    0x0E80F662  call 0xE81AC80
    0x0E80F667  mov [rsi+0x19F58],rax

Flow (instruction-complete):
1. Kick (sub_e80ecb0): while [queueWrapper+0x2F8C020] != 0, each pending surface at [queueWrapper+rdx*8+0x2F8B7A0] is stamped [surface+0x2CBD0] = [fenceWrapper+0x28] (current fence value), [surface+0x2CBD8] = 1 (submitted), [surface+0x30] (ID3D12CommandList*) collected into a stack array, and the surface pointer is pushed into the ring [queueWrapper+0x2F8C028] at tail [queueWrapper+0x2F8C8B0] mod 0x110; head [queueWrapper+0x2F8C8A8] advances on wrap, and a tail wrap resets head+tail via `movups [rcx],xmm0` (16 bytes at ring base). Then queue vtable +0x50 `ExecuteCommandLists(count, array)` and [queueWrapper+0x2F8C020] = 0. This is slot 62's kickPendingSurfaces body, reused inside the fence wait.
2. Signal + wait: `queue->Signal([fenceWrapper+0x18], [fenceWrapper+0x28])` (queue vtable +0x70), then [fenceWrapper+0x28]++. sub_e81b3b0 caches `fence->GetCompletedValue()` (fence vtable +0x40) at [fenceWrapper+0x30] and returns (completed != -1); sub_e818490(queueWrapper, [fenceWrapper+0x28]-1, timeout) first returns early when [queueWrapper+0x2F8B798] >= value, otherwise does `fence->SetEventOnCompletion(value, [fenceWrapper+0x20])` (fence vtable +0x48) then `WaitForSingleObjectEx([fenceWrapper+0x20], timeout, 0)` via import [0xF9A7B68].
3. Reap (rest of sub_e818490): walks the ring from head; each submitted surface ([surface+0x2CBD8] != 0) whose stamp [surface+0x2CBD0] <= waited value is reaped ([surface+0x2CBE0] -> [surface+0x2CBE8], then 0xEEC6DE0 per entry, 0xE935700 frees; ring indices wrap mod 0x110).

CLOSES? YES — the pending part ("fence wait internals") is fully [V]-proven at instruction level: queue wrapper at this+0xCC9268; fence wrapper at [this+0x3C563B0] with fence +0x18, wait event +0x20, next-value +0x28 (signaled via queue vtable +0x70, then incremented), cached completed +0x30 (fence vtable +0x40), high-water skip at queueWrapper+0x2F8B798, blocking wait = SetEventOnCompletion (vtable +0x48) + WaitForSingleObjectEx via import [0xF9A7B68] with timeout, slot 8 flushAndWaitIdle (0xe80f630) passes 0xFFFFFFFF = INFINITE, and the kick/ring/surface-stamp mechanics match 6av [V]. The only [I] items are the kernel32/D3D12 API names (SetEventOnCompletion, WaitForSingleObjectEx, GetCompletedValue, ExecuteCommandLists), inferred from vtable index and argument shape — no blocking fact remains.

## TOOL REQUESTS
None — used only existing tools (rdis dis, xref.py callers) plus docs/BGFX_MAP.md section 6av.
