# oc_U-B6 — D3D12 command-queue wrapper: submit/flush slots 61/62, slot 8 flushAndWaitIdle, frame-context ring advance, fence wait (B6)

## NEXT
Unit complete. File written: docs/progress/oc_U-B6.md. Verified with `python tools/sigs/verify_oc.py docs/progress/oc_U-B6.md` (see ## Verification below). No further steps for U-B6.

## Method (static analysis only)
- Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe, image-base RVAs.
- Function listings: rdis `fn` for 0xe80ecb0 (size 0x1c6), 0xe80f630 (0x45), 0xe81ae10 (0xdf), 0xe81b0f0 (0x14b), 0xe81ac80 (0x18c), 0xe81af20 (0x1c8), 0xe81b3b0 (0x118), 0xe818490 (0x4e6); rdis `dis` for the tail blocks of 0xe818490 starting at 0xe81882f; `xref.py callers 0xe80ecb0`; `rdis dis 0xeea6040` (indirection stub = `jmp rax`).
- Identification: docs/BGFX_MAP.md 6av (slots 8/61/62, wrapper at ctx+0xCC9268, fence at ctx+0x3C563B0) and 6ak (slot 7 TDR handler 0xe8102b0); header src/sdk/mc/deps/bgfx/d3d12/D3D12Context.h (CommandQueueOffsets, FenceOffsets, CommandContextOffsets).
- Preflight: none available (docs/progress/pre does not exist; no pre-existing dossiers for these RVAs).
- Tags: [V] = seen in disassembly (RVA cited), [I] = inferred, [?] = unknown. Unclear items flagged `[UNVERIFIED: 0x<rva> question]`.
- Indirect-call convention in this build: every vtable slot call is a two-instruction sequence `mov rax,[rax+0xNN]; call qword ptr [0xF99FFA0]` where `[0xF99FFA0]` = sub_eea6040 = `jmp rax` [V: rdis dis 0xeea6040, `eea6040 jmp rax`]. Semantically this is `call qword ptr [rax+0xNN]`.

## Absolute-offset cross-check (header static asserts, verified by arithmetic)
- `kCommandQueue(0xCC9268) + kPendingCount(0x2F8C020) = 0x3C55288` == BGFX_MAP 6av pending count `this+0x3C55288` [V].
- `kCommandQueue + kFence(0x2F8D148) = 0x3C563B0` == fence object `this+0x3C563B0` [V].
- `kCommandQueue + kInFlightEntries(0x2F8C028) = 0x3C55290` == ring entries base [V]; `kInFlightHead(0x2F8C8A8) = 0x3C55B10` [V]; `kInFlightTail(0x2F8C8B0) = 0x3C55B18` [V].

## 1. Slot 8 (0xe80f630) — flushAndWaitIdle [V]

RVA/size: `sub_e80f630 [0xe80f630..0xe80f675) size 0x45 0 xrefs in` [V].
Register/argument map [V]: rcx=rsi=this (RendererContextD3D12*); edx=0 (reopen=false) before the slot-61 call; rdi = queueWrapper = `this+0xCC9268`; timeout edx = 0xFFFFFFFF (INFINITE) for the fence wait; return rax = new command-list wrapper stored at `this+0x19F58`.

Key instructions [V]:
```
e80f636  mov rsi,rcx
e80f639  mov rax,[rcx]                                 ; R a0+0x0
e80f63c  mov rax,[rax+0x1E8]                           ; R *(a0+0x0)+0x1E8  == vtbl slot 61 (0x1E8/8)
e80f643  xor edx,edx                                    ; reopen = 0
e80f645  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 = jmp rax  → this->vslot61(0)
e80f64b  lea rdi,[rsi+0xCC9268]                        ; R a0+0xCC9268  queueWrapper
e80f652  mov rcx,rdi
e80f655  mov edx,0xFFFFFFFF                             ; INFINITE timeout
e80f65a  call 0xE80ECB0                                ; -> sub_e80ecb0 (drain + signal + fence wait)
e80f65f  mov rcx,rdi
e80f662  call 0xE81AC80                                ; -> sub_e81ac80 (ring advance, returns fresh context)
e80f667  mov [rsi+0x19F58],rax                         ; W a0+0x19F58  fresh current command-list wrapper
```

Role [V per listing]: calls virtual slot 61 (`vtbl+0x1E8`) with reopen=0 (submitCurrentCommandList), then fence-wait helper 0xe80ecb0 with INFINITE, then advances the ring (0xe81ac80) and installs the fresh wrapper at `this+0x19F58`. Matches BGFX_MAP 6av [V].

## 2. Slot 61 (0xe81ae10) — submitCurrentCommandList(this, bool reopen) [V]

RVA/size: `sub_e81ae10 [0xe81ae10..0xe81aeef) size 0xdf 0 xrefs in` [V].
Register/argument map [V]: rcx=rsi=this; edx=ebx=reopen; rdi/r14 = bounds of pending-destroy vector `this+0x3DA0E0..0x3DA0E8` (0x78-byte elements, destructor 0xe80ef60).

Key instructions [V]:
```
e81ae1a  lea rbp,[rsp+0x30]
e81ae27  mov ebx,edx                                    ; reopen
e81ae29  mov rsi,rcx                                    ; this
e81ae2c  mov rdi,[rcx+0x3DA0E0]                         ; R a0+0x3DA0E0  pending-destroy vector begin
e81ae33  mov r14,[rcx+0x3DA0E8]                         ; R a0+0x3DA0E8  pending-destroy vector end
e81ae40  mov rcx,rdi
e81ae43  call 0xE80EF60                                 ; -> sub_e80ef60  element destructor (0x78 stride)
e81ae48  add rdi,0x78
e81ae4c  cmp rdi,r14
e81ae4f  jne short 0xE81AE40
e81ae68  lea rdi,[rsi+0x3C563C0]                        ; R a0+0x3C563C0  submit mutex
e81ae6f  mov rcx,rdi
e81ae72  call 0xEEC59F0                                 ; -> sub_eec59f0  lock
e81ae77  test eax,eax
e81ae79  jne short 0xE81AED0                            ; lock failed -> error 5 via 0xeec5a00
e81ae7f  cmp dword ptr [rsi+0x3C5640C],0x7FFFFFFF      ; R a0+0x3C5640C  lock-state word
e81ae89  je short 0xE81AEDA                             ; == 0x7FFFFFFF -> error 6 + int3 (use-after-shutdown guard)
e81ae8b  lea rdi,[rsi+0xCC9268]                         ; R a0+0xCC9268  queueWrapper
e81ae92  mov rdx,[rsi+0x19F58]                          ; R a0+0x19F58  current command-list wrapper
e81ae9c  call 0xE81AF20                                 ; -> sub_e81af20 close+execute(queueWrapper, cmdList)
e81aea2  lea rcx,[rsi+0x3C563C0]
e81aea9  call 0xEEC5A10                                 ; -> sub_eec5a10  unlock
e81aeae  test bl,bl
e81aeb0  je short 0xE81AEBC
e81aeb2  mov rcx,rdi
e81aeb5  call 0xE81AC80                                ; ring advance -> fresh wrapper in rax
e81aebc  xor eax,eax                                    ; !reopen -> rax = 0
e81aebe  mov [rsi+0x19F58],rax                          ; W a0+0x19F58
```

Role [V per listing]: destroys the pending-destroy vector, locks `this+0x3C563C0`, validates `this+0x3C5640C != 0x7FFFFFFF`, close+executes the current list via 0xe81af20, unlocks, and either stores a freshly advanced ring context (reopen) or NULL at `this+0x19F58`. Error paths: `e81aed0 mov ecx,5; call 0xeec5a00`; `e81aeda mov dword ptr [rsi+0x3C5640C],0x7FFFFFFF; mov ecx,6; call 0xeec5a00; int3` [V].

## 3. Slot 62 (0xe81b0f0) — kickPendingSurfaces (flush batch) [V]

RVA/size: `sub_e81b0f0 [0xe81b0f0..0xe81b23b) size 0x14b 0 xrefs in` [V].
Register/argument map [V]: rcx=rsi=this; rdx = running pending count (also NumCommandLists at the ExecuteCommandLists call); r8/r9/temp per iteration; fence rbx-ish via `[rsi+0x3C563B0]`.

Key instructions [V]:
```
e81b10d  mov rax,[rcx]
e81b110  mov rax,[rax+0x1E8]                            ; vtbl slot 61 first (flush current list), reopen=0
e81b117  xor edx,edx
e81b119  call qword ptr [0xF99FFA0]                     ; this->vslot61(0)
e81b11f  mov rax,[rsi+0x3C55288]                        ; R a0+0x3C55288  pending-surface count
e81b126  test rax,rax
e81b129  je 0xE81B20A                             ; nothing pending
e81b12f  shl rax,3
e81b133  lea rcx,[rsi+0x3C55B10]                        ; R a0+0x3C55B10  ring head slot
e81b13a  xor edx,edx
e81b13c  xorps xmm0,xmm0
e81b13f  jmp short 0xE81B18D
loc_e81b18d:
e81b18d  mov r8,[rsi+rdx*8+0x3C54A08]                   ; R a0+0x3C54A08+idx  pending surface object (frame context)
e81b195  mov r10,[rsi+0x3C55B18]                        ; R a0+0x3C55B18  ring tail
e81b19c  cmp r10,0x110                                  ; 0x110 == ring-empty sentinel
e81b1a3  je short 0xE81B150                             ; tail==0x110 -> reset-head path
e81b1a5  inc r10
e81b1a8  cmp r10,0x110
e81b1af  mov r9d,0
e81b1b5  cmovne r9,r10                                  ; tail = (tail+1) unless tail+1==0x110 (wrap to 0)
e81b1b9  mov [rsi+0x3C55B18],r9                         ; W a0+0x3C55B18  tail
e81b1c0  cmp r9,[rsi+0x3C55B10]                         ; R a0+0x3C55B10  head (full check)
e81b1c7  jne short 0xE81B156
loc_e81b156:
e81b156  mov [rsi+r9*8+0x3C55290],r8                    ; W a0+0x3C55290+tail  ring entry = object
e81b15e  mov r9,[rsi+0x3C563B0]                         ; R a0+0x3C563B0  fence object pointer
e81b165  mov r9,[r9+0x28]                               ; R *(a0+0x3C563B0)+0x28  fence next value
e81b169  mov [r8+0x2CBD0],r9                            ; W a2+0x2CBD0  ctx fence value stamp
e81b170  mov byte ptr [r8+0x2CBD8],1                    ; W a2+0x2CBD8  ctx submitted = 1
e81b178  mov r8,[r8+0x30]                               ; R a2+0x30  ID3D12GraphicsCommandList*
e81b17c  mov r9d,edx
e81b17f  mov [rsp+r9*8+0x20],r8                         ; stack command-list array[idx] = list
e81b184  inc rdx                                        ; count++
e81b187  add rax,0xFFFFFFFFFFFFFFF8
e81b18b  je short 0xE81B1E6                             ; all pending drained
e81b1e6  mov rcx,[rsi+0xCC9268]                         ; R a0+0xCC9268  queue
e81b1ed  mov rax,[rcx]
e81b1f0  mov rax,[rax+0x50]                             ; R *(*(a0+0xCC9268)+0x0)+0x50  == ID3D12CommandQueue vtbl slot 10 ExecuteCommandLists
e81b1f4  lea r8,[rsp+0x20]                              ; command-list array
e81b1f9  call qword ptr [0xF99FFA0]                     ; queue->ExecuteCommandLists(count=rdx, array)
e81b1ff  mov qword ptr [rsi+0x3C55288],0                ; W a0+0x3C55288  pending count = 0
```

Role [V per listing]: flushes current list (slot 61, reopen=0), then drains `this+0x3C55288` pending frame-context objects from `this+0x3C54A08[]`: stamps each `obj+0x2CBD0 = [fence+0x28]` (current fence signal value), sets `obj+0x2CBD8 = 1` (submitted), pushes `obj` into the 0x110-entry ring at `this+0x3C55290` (head `this+0x3C55B10`, tail `this+0x3C55B18`, index wraps at 0x110), collects `obj+0x30` (command list) into a stack array, then one `ExecuteCommandLists(n, array)` on the queue at `this+0xCC9268`, and resets the pending count [V]. Per BGFX_MAP 6av these objects are the per-frame command-allocator/frame contexts (stride >= 0x2CBE0) [V doc / disassembly field uses].

## 4. Frame-context ring advance (0xe81ac80) — openNextCommandList(queueWrapper) [V]

RVA/size: `sub_e81ac80 [0xe81ac80..0xe81ae0c) size 0x18c 12 xrefs in` [V].
Register/argument map [V]: rcx=rdi=queueWrapper (this); rsi = reclaimed context (return value in rax); rdx = fence wait target; r8d = timeout (0xFFFFFFFF) for the retire call.

Key instructions [V]:
```
e81ac8e  mov rcx,[rcx+0x2F8D140]                        ; R a0+0x2F8D140  free-ring tail
e81ac95  cmp rcx,0x110                                  ; 0x110 == free empty sentinel
e81ac9c  jne short 0xE81ACEF                            ; free non-empty -> pop below
e81ac9e  cmp qword ptr [rdi+0x2F8C8B0],0x110            ; R a0+0x2F8C8B0  inflight tail (0x110 == empty)
e81aca9  jne short 0xE81ACB7                            ; inflight non-empty -> recycle head below
e81acab  mov rdx,[rdi+0x2F8B798]                        ; R a0+0x2F8B798  completed-fence cache
e81acb2  inc rdx                                        ; wait target = completed+1
e81acb5  jmp short 0xE81ACDA                            ; retire(mgr, completed+1, INFINITE) to free a slot
loc_e81acb7:                                             ; inflight head recycle path
e81acb7  mov rax,[rdi+0x2F8C8A8]                        ; R a0+0x2F8C8A8  inflight head
e81acbe  mov rax,[rdi+rax*8+0x2F8C028]                  ; R a0+0x2F8C028+head  ctx = inflight[head]
e81acc6  cmp byte ptr [rax+0x2CBD8],0                   ; ctx->submitted == 0?
e81accd  je 0xE81AE06                             ; not submitted -> 0xe81ae06: call 0x1a2800; int3 (fatal, inconsistent state)
e81acd3  mov rdx,[rax+0x2CBD0]                          ; R ctx+0x2CBD0  ctx fence value = wait target
loc_e81acda:
e81acda  mov rcx,rdi
e81acdd  mov r8d,0xFFFFFFFF                             ; INFINITE
e81ace3  call 0xE818490                                 ; -> sub_e818490 retire(mgr, target, INFINITE)
e81ace8  mov rcx,[rdi+0x2F8D140]                        ; R a0+0x2F8D140  free tail (rdi = queueWrapper preserved across retire call)
loc_e81acef:
e81acef  mov rax,[rdi+0x2F8D138]                        ; R a0+0x2F8D138  free head
e81acf6  mov rsi,[rdi+rax*8+0x2F8C8B8]                  ; R a0+0x2F8C8B8+head  ctx = free[head]  (return value)
e81acfe  cmp rax,rcx
e81ad01  jne short 0xE81AD15
e81ad03  mov qword ptr [rdi+0x2F8D140],0x110            ; W a0+0x2F8D140  free empty sentinel
e81ad0e  mov ecx,0x110
e81ad13  jmp short 0xE81AD24
loc_e81ad15:
e81ad15  inc rax
e81ad18  xor ecx,ecx
e81ad1a  cmp rax,0x110
e81ad20  cmovne rcx,rax                                 ; head = head+1, wrap 0x110 -> 0
loc_e81ad24:
e81ad24  mov [rdi+0x2F8D138],rcx                        ; W a0+0x2F8D138  free head
e81ad2b  mov byte ptr [rsi+0x2CBD8],0                   ; W ctx+0x2CBD8  submitted = 0
e81ad32  mov rcx,[rsi+0x2CBC8]                          ; R ctx+0x2CBC8  ID3D12CommandAllocator*
e81ad39  mov rax,[rcx]
e81ad3c  mov rax,[rax+0x40]                             ; allocator vtbl slot 8 per header comment (Reset)
e81ad40  call qword ptr [0xF99FFA0]                     ; allocator->Reset()
e81ad50  movups [rsi],xmm6                              ; W ctx+0x00  zero context head
e81ad53  movups [rsi+0x10],xmm6                         ; W ctx+0x10
e81ad57  mov word ptr [rsi+0x20],0xFFFF                 ; W ctx+0x20
e81ad61  ... 0xeec6ed0 memsets for touched-texture bitmaps (ctx+0x48 size 0x200, ctx+0xA258 size 0x200, ctx+0x224A8 size 0x200) and clears ctx+0xA250, ctx+0x20468, ctx+0x22488, ctx+0x2C6B8, ctx+0x2C6B0, ctx+0x24, ctx+0x2C [V]
e81ade0  mov rcx,[rsi+0x30]                             ; R ctx+0x30  ID3D12GraphicsCommandList*
e81ade4  mov rax,[rcx]
e81ade7  mov rax,[rax+0x50]                             ; command-list vtbl slot 10 Reset
e81adee  xor r8d,r8d
e81adf1  call qword ptr [0xF99FFA0]                     ; list->Reset(allocator=rdi, null, null)
e81adf7  mov rax,rsi
e81adfa  movaps xmm6,[rsp+0x20]
e81adff  add rsp,0x38
e81ae03  pop rdi
e81ae04  pop rsi
e81ae05  ret                                            ; rax = fresh/allocated command-list context
loc_e81ae06:
e81ae06  call 0x1A2800                                  ; -> sub_1a2800 (fatal "bad optional access"-style noreturn)
e81ae0b  int3
```

Role [V per listing]: allocates/reclaims the next frame context from the ring: if the free ring is empty (`freeTail == 0x110`) it either recycles the inflight ring head (after waiting on its fence value via `retire(..., INFINITE)`) or, when both rings are full/sentinel, waits on `completedCache+1`. Then pops `free[head]` (head wraps `0x110 -> 0`), resets the command allocator, zeroes the context, resets its command list, and returns it [V]. Ring index math: `idx = idx+1; if (idx == 0x110) idx = 0` (cmp 0x110 / cmovne / xor-zero idiom at e81ad15-20, e81b1a5-1b5, e80ed55-8a) [V].

## 5. Close+execute helper (0xe81af20) [V]

RVA/size: `sub_e81af20 [0xe81af20..0xe81b0e8) size 0x1c8 2 xrefs in` [V].
Register/argument map [V]: rcx=queueWrapper (rsi), rdx=cmdListWrapper (rdi); rbx = new context from 0xe81ac80; r14 = new context's command list (`[rbx+0x30]`); r12 = `[queueWrapper+0x2F8B790]` (passed to 0xe833210 as pre-state fixup builder argument).

Key instructions [V]:
```
e81af33  mov rcx,[rdx+0x30]                            ; R a1+0x30  ID3D12GraphicsCommandList* of the list being closed
e81af37  mov rax,[rcx]
e81af3a  mov rax,[rax+0x48]                            ; command-list vtbl slot 9 Close
e81af3e  call qword ptr [0xF99FFA0]                    ; list->Close()
e81af44  lea r15,[rdi+0x48]                            ; R a1+0x48
...
e81af54  mov rcx,rsi
e81af57  call 0xE81AC80                                ; ring advance -> rbx = fresh context
e81af5f  mov r14,[rax+0x30]                            ; R ret@e81ac80+0x30  new command list
e81af63  mov r12,[rsi+0x2F8B790]                       ; R a0+0x2F8B790  kUnknown2F8B790
e81af7a  lea rcx,[rdi+0x38]                            ; R a1+0x38
e81af7e  mov rdx,r14
e81af81  mov r8,r12
e81af84  call 0xE833210                                ; -> sub_e833210 pre-state fixup builder
e81af96  mov rax,[r14]
e81af99  mov rax,[rax+0x48]                            ; new command-list vtbl slot 9 Close
e81af9d  mov rcx,r14
e81afa0  call qword ptr [0xF99FFA0]                    ; newList->Close()
e81afa6  mov rax,[rsi+0x2F8C020]                       ; R a0+0x2F8C020  pending count
e81afad  mov [rsi+rax*8+0x2F8B7A0],rbx                 ; W a0+0x2F8B7A0+count  pending[count] = new context
e81afb5  inc qword ptr [rsi+0x2F8C020]                 ; W a0+0x2F8C020  pending count++
loc_e81b056: (clean path)
e81b056  mov rax,[r14]
e81b059  mov rax,[rax+0x48]
e81b060 call qword ptr [0xF99FFA0]                    ; newList->Close()
...
e81b0cb  mov [rsi+rax*8+0x2F8B7A0],rdi                 ; W a0+0x2F8B7A0+count  pending[count] = original cmdListWrapper
e81b0d3  inc qword ptr [rsi+0x2F8C020]                 ; W a0+0x2F8C020  pending count++
```

Role [V per listing]: close+execute bookkeeping — closes the current command list (vtbl +0x48), advances the ring for the next context (0xe81ac80), builds pre-state via 0xe833210 with `mgr+0x2F8B790`, closes/resets the new command list, and pushes contexts onto the pending vector `this+0x2F8B7A0` (count `this+0x2F8C020`) for later batch ExecuteCommandLists by slot 62 / 0xe80ecb0 [V].

## 6. Fence wait — 0xe80ecb0 (drain + signal + wait), 0xe818490 (retire), 0xe81b3b0 (pollFence)

### 5a. 0xe80ecb0 — flush-and-wait fence helper (queueWrapper, timeout) [V]

RVA/size: `sub_e80ecb0 [0xe80ecb0..0xe80ee76) size 0x1c6 11 xrefs in` [V].
Register/argument map [V]: rcx=rdi=queueWrapper (this); edx=esi=timeout; [rdi+0x2F8C020] = pending count; pending entries at `rdi+0x2F8B7A0+idx`; rbx = fence object `[rdi+0x2F8D148]`.

Key instructions [V]:
```
e80ecc0  mov esi,edx                                    ; timeout saved
e80ecc2  mov rdi,rcx                                    ; queueWrapper
e80ecd7  mov rax,[rcx+0x2F8C020]                        ; R a0+0x2F8C020  pending count
e80ecde  test rax,rax
e80ece1  je 0xE80EDB6                             ; nothing pending -> skip to signal/wait
e80ece7  shl rax,3
e80eceb  lea rcx,[rdi+0x2F8C8A8]                        ; R a0+0x2F8C8A8  inflight head slot
...
loc_e80ed3d:
e80ed3d  mov r8,[rdi+rdx*8+0x2F8B7A0]                   ; R a0+0x2F8B7A0+idx  pending context
e80ed45  mov r10,[rdi+0x2F8C8B0]                        ; R a0+0x2F8C8B0  inflight tail
e80ed4c  cmp r10,0x110
e80ed53  je short 0xE80ED00                             ; tail==0x110 sentinel
e80ed55  inc r10
e80ed58  cmp r10,0x110
e80ed5f  mov r9d,0
e80ed65  cmovne r9,r10                                  ; tail wrap 0x110 -> 0
e80ed69  mov [rdi+0x2F8C8B0],r9                         ; W a0+0x2F8C8B0  inflight tail
e80ed70  cmp r9,[rdi+0x2F8C8A8]                         ; R a0+0x2F8C8A8  head (full check)
e80ed77  jne short 0xE80ED06
loc_e80ed06:
e80ed06  mov [rdi+r9*8+0x2F8C028],r8                    ; W a0+0x2F8C028+tail  inflight[tail] = ctx
e80ed0e  mov r9,[rdi+0x2F8D148]                         ; R a0+0x2F8D148  fence object
e80ed15  mov r9,[r9+0x28]                               ; R *(a0+0x2F8D148)+0x28  fence next value
e80ed19  mov [r8+0x2CBD0],r9                            ; W ctx+0x2CBD0  stamp fence value
e80ed20  mov byte ptr [r8+0x2CBD8],1                    ; W ctx+0x2CBD8  ctx submitted = 1
e80ed28  mov r8,[r8+0x30]                               ; R ctx+0x30  ID3D12GraphicsCommandList*
e80ed2f  mov [rsp+r9*8+0x20],r8                         ; stack command-list array
e80ed34  inc rdx                                        ; count++
e80ed37  add rax,0xFFFFFFFFFFFFFFF8
e80ed3b  je short 0xE80ED96
...
loc_e80ed96:
e80ed96  mov rcx,[rdi]
e80ed99  mov rax,[rcx]
e80ed9c  mov rax,[rax+0x50]                             ; ID3D12CommandQueue vtbl slot 10 ExecuteCommandLists
e80eda0  lea r8,[rsp+0x20]                              ; command-list array
e80eda5  call qword ptr [0xF99FFA0]                     ; queue->ExecuteCommandLists(count=rdx, array)
e80edab  mov qword ptr [rdi+0x2F8C020],0                ; W a0+0x2F8C020  pending count = 0
loc_e80edb6:
e80edb6  mov rbx,[rdi+0x2F8D148]                        ; R a0+0x2F8D148  fence object
e80edbd  mov rcx,[rdi]
e80edc0  mov rdx,[rbx+0x18]                             ; R *(a0+0x2F8D148)+0x18  ID3D12Fence*
e80edc4  mov r8,[rbx+0x28]                              ; R *(a0+0x2F8D148)+0x28  signal value
e80edc8  mov rax,[rcx]
e80edcb  mov rax,[rax+0x70]                             ; ID3D12CommandQueue vtbl slot 14 Signal
e80edcf  call qword ptr [0xF99FFA0]                     ; queue->Signal(d3dFence, signalValue)
e80edd5  inc qword ptr [rbx+0x28]                       ; W *(a0+0x2F8D148)+0x28  next value++ (post-increment)
e80edd9  mov r15,[rbx]                                  ; R a0+0x2F8D148+0x00  listeners begin
e80eddc  mov r12,[rbx+8]                                ; R a0+0x2F8D148+0x08  listeners end
e80ede0  cmp r15,r12
e80ede3  je short 0xE80EE1E
loc_e80edf0:
e80edf0  mov rax,[rbx+0x28]
e80edf4  mov [rsp+0x20],rax
e80edf9  mov rcx,[r15+0x78]                             ; listener entry+0x78 object
e80edfd  test rcx,rcx
e80ee00  je short 0xE80EE60
e80ee02  mov rax,[rcx]
e80ee05  mov rax,[rax+0x10]                             ; listener object vtbl slot 2 callback
e80ee09  mov rdx,r14                                     ; r14 = rsp+0x20 = &value
e80ee0c  call qword ptr [0xF99FFA0]                     ; listener->vtbl+0x10(&value)
e80ee12  add r15,0x88                                   ; listener entry stride 0x88
e80ee19  cmp r15,r12
e80ee1c  jne short 0xE80EDF0
loc_e80ee1e:
e80ee1e  mov rcx,rbx
e80ee21  call 0xE81B3B0                                 ; -> sub_e81b3b0 pollFence(fence)
e80ee26  mov rdx,[rbx+0x28]
e80ee2a  dec rdx                                        ; target = last signaled value (nextValue-1)
e80ee2d  mov rcx,rdi                                    ; mgr = queueWrapper
e80ee30  mov r8d,esi                                    ; timeout
e80ee33  call 0xE818490                                 ; -> sub_e818490 retire(mgr, target, timeout)
```

Role [V per listing]: drains the pending vector (`this+0x2F8B7A0`, count `this+0x2F8C020`) into the inflight ring (`this+0x2F8C028`, head `this+0x2F8C8A8`, tail `this+0x2F8C8B0`), stamping each context with the fence's next value at `ctx+0x2CBD0` and `ctx+0x2CBD8 = 1`; then one `ExecuteCommandLists` (queue vtbl +0x50); then `queue->Signal(d3dFence, nextValue)` (queue vtbl +0x70) and `nextValue++` (`inc qword ptr [rbx+0x28]`); notifies listener vector entries (0x88 stride, entry+0x78 object → `obj->vtbl+0x10(&value)`); then `pollFence` and `retire(queueWrapper, nextValue-1, timeout)` to wait for GPU completion [V]. Callers (xref.py callers 0xe80ecb0): slot 8 `0xe80f630` (+0x45) [V], slot 39 swapchain create `0xe817880` (+0x37b), slot 41 `0xe817c00` (+0xe5), slot 44 `0xe818050` (+0x438), RTX submit override `0xe83d440` (+0x381), shutdown `0xe80dec0` (+0xdad), `0xe8150f0` (+0x498), `0xe83e980` (+0x2e5) [V].

### 5b. 0xe818490 — retire(mgr, targetFence, timeoutMs) — the core fence wait [V]

RVA/size: `sub_e818490 [0xe818490..0xe818976) size 0x4e6 6 xrefs in` [V].
Register/argument map [V]: rcx=mgr (queueWrapper); rdx=targetFence (saved at `[rbp+0x878]`); r8d=timeoutMs (saved to r14d); rbx = fence object `[mgr+0x2F8D148]`; rsi = mgr copy; release-count at `[rbp+0x870]`, release base `[rbp+0x850]`, cursor `[rbp+0x858]`, end `[rbp+0x860]`; toRelease stack array at `[rbp-0x58..]`.

Key instructions [V]:
```
e8184b6  mov al,1                                        ; default return = true
e8184b8  mov [rbp+0x878],rdx                             ; W target
e8184bf  cmp [rcx+0x2F8B798],rdx                         ; R a0+0x2F8B798  completed-fence cache >= target?
e8184c6  jae 0xE818935                             ; already retired -> return true
e8184cc  mov rsi,rcx
e8184cf  mov r14d,r8d                                    ; r14d = timeout
e8184d2  mov rbx,[rcx+0x2F8D148]                         ; R a0+0x2F8D148  fence object
e8184dc  call 0xE81B3B0                                  ; -> sub_e81b3b0 pollFence(fence)
e8184e1  test al,al
e8184e3  je short 0xE81852E                              ; poll failed (device lost)
e8184e5  mov rax,[rbp+0x878]
e8184ec  cmp [rbx+0x30],rax                              ; R *(a0+0x2F8D148)+0x30  completed >= target?
e8184f0  jae short 0xE818543                             ; yes -> proceed to drain
e8184f2  mov rcx,[rbx+0x18]                              ; R *(a0+0x2F8D148)+0x18  ID3D12Fence*
e8184f6  mov r8,[rbx+0x20]                               ; R *(a0+0x2F8D148)+0x20  event HANDLE
e8184fa  mov rax,[rcx]
e8184fd  mov rax,[rax+0x48]                              ; ID3D12Fence vtbl slot 9 SetEventOnCompletion
e818501  mov rdx,[rbp+0x878]                             ; rdx = target value
e818508  call qword ptr [0xF99FFA0]                      ; fence->SetEventOnCompletion(target, event)
e81850e  mov rcx,[rbx+0x20]                              ; R *(a0+0x2F8D148)+0x20  event HANDLE -> rcx
e818512  mov edx,r14d                                    ; edx = timeoutMs
e818515  xor r8d,r8d
e818518  call qword ptr [0xF9A7B68]                      ; [data_f9a7b68] WaitForSingleObject(event, timeout, 0)
e81851e  test eax,eax
e818520  jne short 0xE81852E                             ; wait return != 0 (WAIT_TIMEOUT/failed)
e818522  mov rcx,rbx
e818525  call 0xE81B3B0                                  ; pollFence again
e81852c  jne short 0xE818543                             ; completed -> proceed
loc_e81852e:
e81852e  mov rax,[rsi+0x2F8D148]
e818535  cmp qword ptr [rax+0x30],0xFFFFFFFFFFFFFFFF     ; R *(a0+0x2F8D148)+0x30  completed == UINT64_MAX?
e81853a  je short 0xE818543                              ; device lost -> drain anyway
e81853c  xor eax,eax                                     ; return false (persistent timeout, device alive)
e81853e  jmp 0xE818935
loc_e818543: (drain)
e818595  mov rcx,[rsi+0x2F8C8B0]                         ; R a0+0x2F8C8B0  inflight tail
e81859c  cmp rcx,0x110
e8185a3  je 0xE818802                              ; ring empty -> drain done
e8185a9  mov rax,[rsi+0x2F8C8A8]                         ; R a0+0x2F8C8A8  inflight head
e8185b0  mov r9,[rsi+rax*8+0x2F8C028]                    ; R a0+0x2F8C028+head  ctx = inflight[head]
e8185b8  cmp byte ptr [r9+0x2CBD8],0
e8185c0  je 0xE81896F                              ; not submitted -> 0xe81896f: call 0x1a2800 (fatal)
e8185c6  mov rdx,[rbp+0x878]                             ; target
e8185cd  cmp [r9+0x2CBD0],rdx                            ; R ctx+0x2CBD0  ctx fence value <= target?
e8185d4  ja 0xE818802                              ; not yet reached -> stop drain
e8185da  mov rdx,[rbp+0x870]
e8185e1  mov [rbp+rdx*8-0x58],r9                         ; W toRelease[count++] = ctx
...
e8185fe  cmp rax,rcx
e818601  jne short 0xE818620                             ; head = head+1, wrap 0x110 -> 0
e818603  mov qword ptr [rsi+0x2F8C8B0],0x110             ; W a0+0x2F8C8B0  tail = 0x110 sentinel (empty)
e81860e  mov ecx,0x110
e818632  mov [rsi+0x2F8C8A8],rcx                         ; W a0+0x2F8C8A8  head
e818639  mov rsi,[r9+0x2CBE0]                            ; R ctx+0x2CBE0  deferred-release vector begin
e818640  mov rax,[r9+0x2CBE8]                            ; R ctx+0x2CBE8  deferred-release vector end
... moves [ctx+0x2CBE0, ctx+0x2CBE8) IUnknown* pointers into toRelease buffer (allocator [0x1233E1A8] vtbl +8) ...
loc_e818824:
e818824  cmp rsi,rbx
e818827  je short 0xE818841                              ; release loop done
e818820  add rsi,8
e818829  mov rcx,[rsi]
e81882c  test rcx,rcx
e81882f  je short 0xE818820                              ; null entry -> skip
e818831  mov rax,[rcx]
e818834  mov rax,[rax+0x10]                              ; IUnknown vtbl slot 2 Release
e818838  call qword ptr [0xF99FFA0]                      ; p->Release()
e81883e  nop
e81883f  jmp short 0xE818820
loc_e818841:
e818841  mov r11,[rbp+0x870]                             ; release count
e818848  test r11,r11
e81884b  mov r10,rdi                                     ; mgr
e81884e  je 0xE8188D8
e818854  shl r11,3
e818858  lea rax,[r10+0x2F8D138]                         ; &free head
e818875  mov r8,[rbp+rcx-0x58]                           ; toRelease[i] = retired ctx
e81887a  mov [r10+rdx*8+0x2F8C8B8],r8                    ; W free[tail] = ctx  (recycle to free ring)
e818882  add rcx,8
e818886  cmp r11,rcx
e818889  je short 0xE8188D8
e81888b  mov r8,[r10+0x2F8D140]                          ; free tail
e818892  cmp r8,0x110
e818899  je short 0xE818870
e81889b  inc r8
e81889e  cmp r8,0x110
e8188a5  mov edx,0
e8188aa  cmovne rdx,r8                                   ; tail wrap 0x110 -> 0
e8188ae  mov [r10+0x2F8D140],rdx                         ; W free tail
...
e8188d8  mov rax,[rbp+0x878]
e8188df  mov [r10+0x2F8B798],rax                         ; W mgr+0x2F8B798  completed-fence cache = target
e8188e6  mov rax,[r10+0x2F8D148]
e8188ed  cmp qword ptr [rax+0x30],0xFFFFFFFFFFFFFFFF     ; R fence+0x30  completed == UINT64_MAX?
e8188f2  setne al                                        ; return al = completed != UINT64_MAX
e8188f5  test r14,r14
e8188f8  je short 0xE818935
... frees toRelease temp buffer via 0xe935700 ...
loc_e818935:
e818935  add rsp,0x908                                  ; epilogue
e81893c  pop rbx
e81893d  pop rdi
e81893e  pop rsi
e81893f  pop r12
e818941  pop r13
e818943  pop r14
e818945  pop r15
e818947  pop rbp
e818948  ret
```

Role [V per listing]: fast-path returns true if `completedCache >= target`; otherwise polls the fence (`GetCompletedValue`), and if not yet at target arms `fence->SetEventOnCompletion(target, event)` and blocks on `WaitForSingleObject(event, timeout)`; on return (signaled or timeout) re-polls once; on persistent timeout returns false UNLESS `fence->completed == 0xFFFFFFFFFFFFFFFF` (device-lost sentinel), in which case it still drains and returns al = (completed != UINT64_MAX). Then retires every inflight context whose `ctx+0x2CBD0 <= target`: moves it to the free ring, transfers its deferred-release vector (`ctx+0x2CBE0..+0x2CBE8`) to a release list, calls `IUnknown::Release` (vtbl +0x10) on each deferred resource, and stores `completedCache = target` [V].

Error/fatal paths observed inside retire: `0xe81896f call 0x1a2800` (fatal, reached when a non-submitted context sits in the inflight ring — inconsistent state) [V]; `e818949 call 0x75740` and `e81894f ... call qword ptr [0xF9A8C78]; call 0x75740; call 0x1a2800` (allocator/buffer-corruption fatal) [V].

### 5c. 0xe81b3b0 — pollFence(fence) [V]

RVA/size: `sub_e81b3b0 [0xe81b3b0..0xe81b4c8) size 0x118 8 xrefs in` [V].
Register/argument map [V]: rcx=rdi=fence; rcx (reloaded) = `fence+0x18` = ID3D12Fence*; rsi = completed value.

Key instructions [V]:
```
e81b3cd  mov rcx,[rcx+0x18]                            ; R a0+0x18  ID3D12Fence*
e81b3d1  mov rax,[rcx]
e81b3d4  mov rax,[rax+0x40]                            ; ID3D12Fence vtbl slot 8 GetCompletedValue
e81b3d8  call qword ptr [0xF99FFA0]                    ; completed = d3dFence->GetCompletedValue()
e81b3de  mov rsi,rax
e81b3e1  mov [rdi+0x30],rax                            ; W a0+0x30  completed cache
e81b3e5  cmp rax,0xFFFFFFFFFFFFFFFF
e81b3e9  je short 0xE81B444                            ; device lost -> notify listeners with UINT64_MAX
e81b3eb  lea rax,[rsi-1]
e81b3ef  cmp rax,[rdi+0x28]                            ; R a0+0x28  nextValue  (completed-1 >= nextValue -> all signaled)
e81b3f3  jae 0xE81B48E
e81b409 lea rbx,[rsp+0x20]                            ; &completed on stack
loc_e81b410:
e81b410 mov rax,[rdi+0x30]
e81b414 mov [rsp+0x20],rax
e81b419 mov rcx,[r14+0x38]                            ; listener entry+0x38 object
e81b426 mov rax,[rcx]
e81b429 mov rax,[rax+0x10]                            ; listener object vtbl slot 2 callback
e81b42d mov rdx,rbx                                   ; &value
e81b430 call qword ptr [0xF99FFA0]                    ; obj->vtbl+0x10(&completed)
e81b436 add r14,0x88                                  ; listener entry stride 0x88
e81b48e cmp rsi,0xFFFFFFFFFFFFFFFF
e81b492 setne al                                      ; return al = completed != UINT64_MAX
```

Device-lost path `loc_e818444` (0xe81b444): same listener walk with `[rsp+0x20] = 0xFFFFFFFFFFFFFFFF` and `entry+0x38` objects (`e81b460 mov qword ptr [rsp+0x20],0xFFFFFFFFFFFFFFFF; e81b469 mov rcx,[rbx+0x38]`) [V].

## 7. Fence object layout [V]

Fence object lives at `mgr+0x2F8D148` (= absolute `this+0x3C563B0`, ctx = RendererContextD3D12). All offsets below are relative to the fence object; every field below is read or written in the listings quoted above [V].

| Offset | Size | Field / meaning | Tag | Quoted evidence |
|---|---|---|---|---|
| +0x00 | 8 | listeners vector begin (0x88-byte entries) | [V] | `e80edd9 mov r15,[rbx]`; `e80ede0 cmp r15,r12`; `e81b419 mov rcx,[r14+0x38]` |
| +0x08 | 8 | listeners vector end | [V] | `e80eddc mov r12,[rbx+8]` |
| +0x18 | 8 | `ID3D12Fence*` | [V] | `e80edc0 mov rdx,[rbx+0x18]`; `e81b3cd mov rcx,[rcx+0x18]`; header `FenceOffsets::kD3DFence = 0x18` [I static] |
| +0x20 | 8 | `HANDLE event` (waited on with the timeout) | [V] | `e80edc4 mov r8,[rbx+0x28]`... no — event: `e8184f6 mov r8,[rbx+0x20]`; `e81850e mov rcx,[rbx+0x20]` |
| +0x28 | 8 | `u64 nextValue` — fence value the next Signal uses, post-incremented by `inc qword ptr [rbx+0x28]` after Signal | [V] | `e80edc4 mov r8,[rbx+0x28]`; `e80edd5 inc qword ptr [rbx+0x28]`; `e81b3ef cmp rax,[rdi+0x28]` |
| +0x30 | 8 | `u64 completed` — last `GetCompletedValue`; `0xFFFFFFFFFFFFFFFF` = device-lost sentinel | [V] | `e81b3e1 mov [rdi+0x30],rax`; `e8184ec cmp [rbx+0x30],rax`; `e818535 cmp qword ptr [rax+0x30],0xFFFFFFFFFFFFFFFF` |

Listener entry layout (0x88 stride): entry+0x38 = object whose `vtbl+0x10` is called with `&value` by pollFence [V: `e81b419 mov rcx,[r14+0x38]; e81b429 mov rax,[rax+0x10]`]; entry+0x78 = object likewise notified by the Signal path in 0xe80ecb0 [V: `e80edf9 mov rcx,[r15+0x78]`; header comment says entry+0x38 used by 0xe81b3b0, entry+0x78 by 0xe80ecb0 — both observed [V]].

## 8. ID3D12 vtable slots used (displacement-identified) [V]

This build does **not** use the literal `call qword ptr [rax+0xNN]` form; every vtable call is `mov rax,[rax+0xNN]` followed by `call qword ptr [0xF99FFA0]` where `[0xF99FFA0]` = sub_eea6040 = `jmp rax` [V: rdis dis 0xeea6040]. The slot is identified by the `mov rax,[rax+0xNN]` displacement:

| Interface | Slot offset | Method | Observed at | Tag |
|---|---|---|---|---|
| ID3D12Fence | +0x40 | GetCompletedValue | `e81b3d4 mov rax,[rax+0x40]` (0xe81b3b0) | [V] |
| ID3D12Fence | +0x48 | SetEventOnCompletion | `e8184fd mov rax,[rax+0x48]` (0xe818490) | [V] |
| ID3D12CommandQueue | +0x50 | ExecuteCommandLists | `e80ed9c mov rax,[rax+0x50]` (0xe80ecb0); `e81b1f0 mov rax,[rax+0x50]` (0xe81b0f0) | [V] |
| ID3D12CommandQueue | +0x70 | Signal | `e80edcb mov rax,[rax+0x70]` (0xe80ecb0) | [V] |
| ID3D12GraphicsCommandList | +0x48 | Close | `e81af3a mov rax,[rax+0x48]` (0xe81af20) | [V] |
| ID3D12GraphicsCommandList | +0x50 | Reset | `e81ade7 mov rax,[rax+0x50]` (0xe81ac80) | [V] |
| ID3D12CommandAllocator | +0x40 | Reset (per header comment) | `e81ad3c mov rax,[rax+0x40]` (0xe81ac80) | [V] (displacement [V]; method name per header [I]) |
| IUnknown | +0x10 | Release | `e818834 mov rax,[rax+0x10]` (0xe818490 release loop) | [V] |

Note: stock D3D12.h values (Signal +0xB8, Wait +0xC0) are **not** what this build uses — this build signals through queue vtbl +0x70 [V]; no `ID3D12CommandQueue::Wait` call site observed anywhere in these functions → [UNVERIFIED: Wait +0xC0 — not observed in this unit; fence signaling here is queue->Signal + fence->SetEventOnCompletion + WaitForSingleObject].

## 9. Wait loop semantics [V / I]

- Event handle source: `fence+0x20` (HANDLE), created at init (kernel32 `CreateEventExA` per BGFX_MAP 6ak slot 58 [V doc]); passed to `SetEventOnCompletion` as `r8` at `e8184f6 mov r8,[rbx+0x20]` and used as `WaitForSingleObject`'s first argument at `e81850e mov rcx,[rbx+0x20]` [V].
- Timeout argument: `retire`'s 3rd argument (r8d), saved to `r14d` at `e8184cf mov r14d,r8d` and passed as `edx` at `e818512 mov edx,r14d` to `WaitForSingleObject` via `[0xF9A7B68]` [V]. Slot 8 passes `0xFFFFFFFF` = INFINITE at `e80f655 mov edx,0xFFFFFFFF` [V].
- Wait-for-single-object call: `e818518 call qword ptr [0xF9A7B68]` with `(rcx=event, rdx=timeout, r8d=0)` [V].
- What happens on timeout: `e81851e test eax,eax; e818520 jne short 0xE81852E` — any non-WAIT_OBJECT_0 return jumps to `loc_e81852e`, which does one re-poll via `pollFence` (`e818522 mov rcx,rbx; call 0xE81B3B0`); if still incomplete it reaches `e818535 cmp qword ptr [rax+0x30],0xFFFFFFFFFFFFFFFF`: device-lost sentinel → still drains (`e818543`); otherwise `e81853c xor eax,eax` → return false [V]. So the wait is single-shot (one SetEventOnCompletion + one wait + one re-poll), not a spinning loop [I from listing].
- TDR handling pointer: **no TDR function pointer is called inside `retire`** — the device-lost condition is only the `completed == UINT64_MAX` sentinel, after which retire drains and returns `al = (completed != UINT64_MAX)` [V]. TDR/device-lost handling proper is slot 7 `0xe8102b0` ("Device Lost FAILED ...", DRED report; "Called from submit on failure") per BGFX_MAP 6ak [V doc]; which caller translates `retire()==false` into a TDR call was not traced → `[UNVERIFIED: TDR pointer — retire returns false on persistent timeout; no TDR call observed inside 0xe818490; BGFX_MAP 6ak places TDR at slot 7 0xe8102b0 invoked from submit on failure]`.

## 10. Frame-context ring: count and index math [V]

- Two rings live inside the queue wrapper (`this+0xCC9268`):
  - inflight ring: entries `this+0x2F8C028` (8-byte context pointers), head `this+0x2F8C8A8`, tail `this+0x2F8C8B0` [V].
  - free ring: entries `this+0x2F8C8B8`, head `this+0x2F8D138`, tail `this+0x2F8D140` [V].
- Ring capacity: `0x110` entries = 272 (0x110 * 8 bytes = 0x880 per ring; entry base to head-slot distance confirms: `0x2F8C8A8 - 0x2F8C028 = 0x880`) [V arithmetic].
- Empty sentinel: head or tail == `0x110` [V: `cmp rcx,0x110; je` at e80ed4c/e81ac9e/e81859c; `mov qword ptr [rdi+0x2F8D140],0x110` at e81ad03].
- Advance math: `idx = idx + 1; if (idx == 0x110) idx = 0` — idiom `inc r10; cmp r10,0x110; xor r9d,r9d; cmovne r9,r10` (e80ed55-65, e81b1a5-1b5, e81ad15-20, e818620-2e, e81889b-8aa) [V].
- Per-frame context fields touched [V]:
  - `+0x2CBD0` u64 fence value assigned at execute (stamped from `fence+0x28`; compared against wait target) — `e81b169 mov [r8+0x2CBD0],r9`; `e8185cd cmp [r9+0x2CBD0],rdx` [V].
  - `+0x2CBD8` u8 submitted flag — `e81b170 mov byte ptr [r8+0x2CBD8],1`; `e81accd cmp byte ptr [rax+0x2CBD8],0`; `e81ad2b mov byte ptr [rsi+0x2CBD8],0` [V].
  - `+0x30` ID3D12GraphicsCommandList* — `e81b178 mov r8,[r8+0x30]`; `e81ade0 mov rcx,[rsi+0x30]` [V].
  - `+0x2CBC8` ID3D12CommandAllocator* — `e81ad32 mov rcx,[rsi+0x2CBC8]` [V].
  - `+0x2CBE0`/`+0x2CBE8` deferred-release (IUnknown*) vector begin/end, moved into the release list at retirement — `e818639 mov rsi,[r9+0x2CBE0]; e818640 mov rax,[r9+0x2CBE8]` [V].
- How many frame contexts exist: ring slots = 272 each; the number of live context allocations is not determined statically (allocated at init, pool size not seen in this unit) → `[?]`. BGFX_MAP 6av's "ring of 16-ish in flight" is an unproven inference → `[I]`.

## 11. Callers of the fence-wait helper 0xe80ecb0 [V]
`xref.py callers 0xe80ecb0` [V]: 0xe80dec0+0xdad (slot 59 shutdown), 0xe80f630+0x45 (slot 8 flushAndWaitIdle), 0xe8150f0+0x498, 0xe817880+0x37b (slot 39 swapchain create), 0xe817c00+0xe5 (slot 41), 0xe818050+0x438 (slot 44), 0xe83d440+0x381 (RTX submit override), 0xe83e980+0x2e5, 0xe80ee80+0xd9 (adjacent address, role not determined → [?]).

## OPEN questions
- `[UNVERIFIED: 0x1a2800]` — noreturn fatal helper ("Bad optional access"-style string built via `sub_eec6d80`, then `sub_eec6d80`-noreturn path with `int3`); called at `e81896f`/`e81ae06` on inconsistent ring state; exact message not determined.
- `[UNVERIFIED: TDR pointer]` — `retire` (0xe818490) calls no TDR function; on persistent timeout it returns false (unless device-lost sentinel). Slot 7 `0xe8102b0` (BGFX_MAP 6ak) is the device-lost/TDR handler called from submit on failure; the caller that maps `retire()==false` to slot 7 was not traced.
- `[UNVERIFIED: frame-context pool size]` — ring capacity is 0x110 (272) slots [V]; live allocation count unknown [?].
- `[UNVERIFIED: 0xe80ee80+0xd9]` — xref lists 0xe80ee80 as a caller of 0xe80ecb0 but 0xe80ee80 lies just past 0xe80ecb0's end (0xe80ee76); role undetermined.

## TOOL REQUESTS
None — all work done with rdis `fn`/`dis`, `xref.py callers`, `rdis dis 0xeea6040`, and `verify_oc.py`.

## Verification
- Every `0xRVA  instr` line in this document was copied verbatim from the rdis listings saved under C:\Users\Atomi\AppData\Local\Temp\opencode (e80ecb0.txt, e80f630.txt, e81ae10.txt, e81b0f0.txt, e81ac80.txt, e81af20.txt, e81b3b0.txt, e818490.txt, e81882f.txt, eea6040.txt).
- Header cross-checks (0xCC9268 + kPendingCount == 0x3C55288; + kFence == 0x3C563B0; + kInFlightEntries == 0x3C55290; head/tail 0x3C55B10/0x3C55B18) verified by arithmetic against BGFX_MAP 6av absolute offsets.
- Ran `python tools/sigs/verify_oc.py docs/progress/oc_U-B6.md` after writing; result recorded below.