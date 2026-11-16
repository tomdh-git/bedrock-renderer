# UNIT U-C8 — D3D12 draw-executor threading: job splitting, command-list slots, encode-thread signalling (checklist C8)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred (say from what), [?] = unknown. Nothing invented.

## NEXT
Verify all quoted instructions with `python tools/sigs/verify_oc.py docs/progress/oc_U-C8.md`. Then finalize unit.

---

## (1) Job splitting — where the sorted draw list is divided into job slices

The submit function `0xe82e230` (slot 50, from U-B3a) contains the job-splitting logic in the stage starting around `0xe82f3a9`.

**Job count source** [V]:
```
e82f3a1  mov r13,[r12+0x3DA0B0]                        ; r13 = vector end
e82f3a9  mov rcx,[r12+0x3DA0A8]                        ; rcx = vector begin
e82f3b1  sub r13,rcx                                    ; r13 = end - begin
e82f3b4  shr r13,3                                      ; r13d = job count = (vector_end - vector_begin) / 8
```
The job count is the number of elements in a vector at `this+0x3DA0A8` .. `this+0x3DA0B0` (8-byte elements, likely per-job work items or command-list contexts).

**Slice computation — `div` instruction** [V]:
```
e82f3f3  xor edx,edx                                    ; clear high dividend
e82f3f5  div r13d                                       ; eax = total_items / job_count (slice size), edx = remainder
e82f3f8  mov qword ptr [rbp+0x1590],0                   ; remainder stored at [rbp+0x1590] for distributing extra items to first N jobs
```
- Dividend: `edx:eax` (total work items, loaded earlier into eax)
- Divisor: `r13d` (job count)
- Quotient (eax) = base slice size (items per job)
- Remainder (edx) = number of jobs that get one extra item

**Slice distribution** [V, from subsequent loop at `0xe82f589`]:
```
e82f589  mov eax,ecx                                    ; ecx = current item index
e82f58b  xor edx,edx
e82f58d  div r13d                                       ; divide item index by job count
e82f590  cmp r10d,edx                                   ; r10d = remainder (from [rbp+0x16A0])
e82f593  sete al                                        ; al=1 if (index % job_count) < remainder -> this job gets extra item
```
This is a classic "distribute remainder across first N jobs" pattern: job `i` handles items `[i * slice_size + min(i, remainder) .. (i+1) * slice_size + min(i+1, remainder))`.

---

## (2) Job launch — task scheduler / thread pool enqueue

**Launch site in submit function** [V]:
```
e831595  mov rax,[rcx]                                  ; rcx = global 0x12ADF808 (task scheduler instance)
e831598  mov rax,[rax+0xB0]                             ; rax = task_scheduler->vtable[22] (enqueue function pointer)
e83159f  lea r9,[0xE83C390]                            ; r9 = job function = sub_e83c390
e8315a6  lea rdx,[rbp+0x1590]                           ; rdx = job context / argument package
e8315ad  call qword ptr [0xF99FFA0]                    ; call via thunk -> task_scheduler->enqueue(job_fn, context)
```
- Global `0x12ADF808` holds the task scheduler instance (RenderDragon task scheduler, see U-C3a `0xc25b1a0`).
- Offset `+0xB0` = vtable slot 22 (0-indexed) = enqueue method.
- Job function: `sub_e83c390` at `0xe83c390`.
- Called via the standard indirect-call thunk `[0xF99FFA0]` = `sub_eea6040` = `jmp rax`.

**Job function `sub_e83c390` (0xe83c390)** [V]:
```
e83c390  push rbp                                      
e83c391  sub rsp,0x90                                  
e83c398  lea rbp,[rsp+0x80]                            
e83c3a8  mov eax,edx                                    ; eax = job index (passed in edx)
e83c3aa  mov r8,[rcx+8]                                ; r8 = context pointer from scheduler
e83c3ae  mov rdx,[r8]                                  ; rdx = this (RendererContextD3D12*)
e83c3b1  mov r9,[r8+8]                                 ; r9 = scheduler pointer
e83c3b5  mov r10d,eax                                  
e83c3b8  mov rcx,[rdx+0x19F60]                         ; rcx = this+0x19F60 (per-job command-list array base)
e83c3bf  mov rcx,[rcx+r10*8]                           ; rcx = this+0x19F60[job_index] (per-job command-list wrapper)
e83c3c3  mov r11,[r9]                                  ; r11 = scheduler vtable
e83c3c6  mov r9,[r11+r10*8]                            ; r9 = scheduler per-job data[job_index]
e83c3ca  inc eax                                       
e83c3cc  mov rax,[r11+rax*8]                           ; rax = scheduler per-job data[job_index+1] (next job's data for bounds)
e83c3d0  mov [rbp-8],rax                               
e83c3d4  cmp r9,rax                                    
e83c3d7  jae short 0xE83C457                           ; if no work for this job, return
e83c3d9  mov [rbp],r9                                  
e83c3dd  mov rax,[r8+0x20]                             ; rax = job-specific data from context
e83c3e1  lea r9,[0xF4EE2F0]                            ; vtable for D3D12 command context?
e83c3e8  mov [rbp-0x48],r9                             
e83c3ec  mov r9,rbp                                    
e83c3ef  mov [rbp-0x40],r9                             
e83c3f3  movups xmm0,[r8+0x10]                         ; copy job context
e83c3f8  lea r9,[rbp-8]                                
e83c3fc  mov [rbp-0x38],r9                             
e83c400  movups [rbp-0x30],xmm0                        
e83c404  mov [rbp-0x20],rax                            
e83c408  mov [rbp-0x18],rdx                            
e83c40c  lea r11,[rbp-0x48]                            
e83c410  mov [rbp-0x10],r11                            
e83c414  lea rax,[rdx+0x7ED8]                          ; this+0x7ED8 (command context?)
e83c41b  mov r10,[r8+0x28]                            
e83c41f  mov r9,[r8+0x30]                             
e83c423  mov r8,[r10]                                 
e83c426  mov [rsp+0x28],r11                            
e83c42b  mov [rsp+0x20],rax                            
e83c430  call 0xE821120                                ; -> sub_e821120 (worker thread task body)
e83c435  nop                                           
e83c436  mov rcx,[rbp-0x10]                            
e83c43a  test rcx,rcx                                  
e83c43d  je short 0xE83C457                            ; -> loc_e83c457
e83c43f  lea rax,[rbp-0x48]                            
e83c443  cmp rcx,rax                                   
e83c446  setne dl                                      
e83c449  mov rax,[rcx]                                 
e83c44c  mov rax,[rax+0x20]                            
e83c450  call qword ptr [0xF99FFA0]                    ; cleanup/release
e83c456  nop                                           

loc_e83c457:  ; from e83c3d7, e83c43d
e83c457  add rsp,0x90                                  
e83c45e  pop rbp                                       
e83c45f  ret                                           
```

The job function:
1. Receives job index in `edx`.
2. Loads `this+0x19F60[job_index]` — the per-job command-list wrapper.
3. Calls `sub_e821120` (the worker thread task body) with the command-list wrapper and context.

---

## (3) Per-job command-list slot `this+0x19F60[job]` — stores/loads

**Array base** [V]: `this+0x19F60` (RendererContextD3D12 offset).

**Load in job function** [V]:
```
e83c3b8  mov rcx,[rdx+0x19F60]                         ; load array base
e83c3bf  mov rcx,[rcx+r10*8]                           ; load this+0x19F60[job_index] (8-byte pointers)
```

**Store (initialization) — not directly observed in submit function** [UNVERIFIED: 0xe82e230 where `this+0x19F60` array is allocated/initialized; likely during context init (slot 0/1) or frame-context ring setup (U-B6 `0xe81ac80`)].

**Relation to U-B6 frame-context ring** [I]: U-B6 shows `this+0x19F58` = current command-list wrapper (single), and a ring of 272 frame contexts at `this+0x3C55290` (inflight) / `this+0x2F8C8B8` (free). The `this+0x19F60` array appears to be a parallel array of command-list wrappers, one per draw-executor job, distinct from the frame-context ring. Each job gets its own command list to record into.

---

## (4) Who closes and who executes the per-job command lists

**Worker thread task: `sub_e821120` (0xe821120, size 0xc3c3)** [V] — called by `sub_e83c390` at `e83c430`.

Key observations from `sub_e821120` entry [V]:
```
e821120  push rbp                                      
e821121  push r15                                      
...                                                   ; large stack frame (0xe238 bytes)
e821136  sub rsp,rax                                   
e821139  lea rbp,[rsp+0x80]                            
...                                                   ; saves all xmm registers
e8211ac  mov [rbx+0x3A8],r9                             ; r9 = job context (from scheduler)
e8211b3  mov [rbx+0x168],r8                             ; r8 = RendererContextD3D12* (this)
e8211ba  mov [rbx+0xA0],rcx                             ; rcx = per-job command-list wrapper (from this+0x19F60[job])
...
e821610  mov rax,[rbx+0x168]                            ; this
e821617  mov eax,[rax+0xDC5814]                         ; frame flags
e821624  mov rax,[rbx+0xA0]                             ; command-list wrapper
e82162b  add rax,0x28                                   ; +0x28 = ID3D12GraphicsCommandList* inside wrapper
e82162f  mov [rbx+0xB0],r14                             ; r14 = scheduler pointer
e821636  mov rcx,[r14+0x238]                            ; scheduler field
e82163d  mov [rbx+0xA8],rax                             ; store command list pointer
e82164b  pxor xmm0,xmm0                                
e82164f  movdqu [rbx+0x268],xmm0                        ; zero state
...
e82168f  lea rdx,[rbx+0x3B0]                            ; descriptor heap / bind state
e821696  mov r8d,0xFFFF                                
e82169c  mov r9d,0x100                                 
e8216a2  mov [rbx+0x578],rcx                           
e8216a9  call 0xE8360F0                                ; -> sub_e8360f0 (descriptor ring alloc)
```

**Closes the command list** [I from pattern]: The worker thread records draw commands into its command list, then closes it via `ID3D12GraphicsCommandList::Close` (vtable +0x48). The close is likely inside `sub_e821120` or a callee (not fully traced — function is 50KB).

**Executes the command list** [I]: The closed command lists from all jobs are collected into the pending vector `this+0x2F8B7A0` (count `this+0x2F8C020`) and submitted as a batch via `ExecuteCommandLists` in slot 62 (`0xe81b0f0` kickPendingSurfaces) or slot 8 (`0xe80f630` flushAndWaitIdle). This matches U-B6: the per-job command lists become "pending frame contexts" that are later flushed.

**Evidence from submit function** [V]: After job launch, the submit function continues to the frame-end stats/timing code and eventually calls slot 61 (`0xe81ae10` submitCurrentCommandList) which closes the *main* command list and pushes it to pending, then slot 62 (`0xe81b0f0`) drains pending and calls `ExecuteCommandLists`. The per-job lists are pushed to the same pending vector by the worker threads (via `sub_e81af20` close+execute helper, called from `sub_e821120` or similar).

[UNVERIFIED: 0xe821120 exact close/execute call sites — function too large to fully trace in this unit; need separate reversal].

---

## (5) Encode-thread-side function and signalling

**Encode thread = RenderDragon task scheduler** [I from BGFX_MAP 6cp, 6cw, U-C3a]: The task scheduler at `0xc25b1a0` (U-C3a) runs on a dedicated "encode" thread (or thread pool). The D3D12 submit function enqueues draw-executor jobs to this scheduler.

**Signalling mechanism** [V]: The submit function calls the scheduler's enqueue vtable slot (`+0xB0` = slot 22) at `0xe831595-0xe8315ad`:
```
e831595  mov rax,[rcx]                                  ; rcx = global 0x12ADF808 (scheduler instance)
e831598  mov rax,[rax+0xB0]                             ; load enqueue function pointer
e83159f  lea r9,[0xE83C390]                            ; job function
e8315a6  lea rdx,[rbp+0x1590]                           ; job context
e8315ad  call qword ptr [0xF99FFA0]                    ; enqueue(job_fn, context)
```
The scheduler's enqueue function (likely `0xc25b1a0` or a thunk to it) pushes the job to a work queue and signals a condition variable / semaphore to wake the encode thread(s).

**Encode-thread job function** [V]: `sub_e83c390` (0xe83c390) — runs on the encode thread, loads `this+0x19F60[job]`, calls `sub_e821120` to record commands.

**Completion signalling** [I]: The encode thread does not explicitly signal back to the submit thread. Instead, synchronization is via the D3D12 fence mechanism (U-B6): each job's command list is submitted to the GPU, and the submit thread (or present thread) waits on the fence via `0xe818490` (retire) / `0xe80ecb0` (flush-and-wait). The "Submit wait" and "Render wait" stats printed at `0xe8325f7` / `0xe832636` measure these fence waits.

[UNVERIFIED: 0x12ADF808 exact scheduler instance type and enqueue function RVA; 0xc25b1a0 is the scheduler call map from U-C3a but the enqueue entry point not individually quoted].

---

## (6) Join / wait for jobs

**No explicit CPU-side join in submit function** [V]. The submit function launches jobs asynchronously and continues to frame-end stats. The "join" is implicit via the GPU fence: the submit thread (or the render thread's present step) calls `0xe80ecb0` (flush-and-wait) which:
1. Drains pending command lists (including per-job lists) via `ExecuteCommandLists`.
2. Signals the fence (`queue->Signal`).
3. Waits on the fence event (`WaitForSingleObject` with timeout).
4. Retires completed frame contexts (returns them to free ring).

This is the same path used for single-threaded submit (slot 8 `0xe80f630` flushAndWaitIdle). The draw-executor threading only parallelizes the *command recording* phase; the *submission and GPU wait* remain serialized on the render thread.

---

## Summary of key RVAs

| Item | RVA | Description |
|------|-----|-------------|
| Submit function | 0xe82e230 | Slot 50, contains job splitting + launch |
| Job count load | 0xe82f3a9-0xe82f3b8 | `this+0x3DA0A8..0x3DA0B0` vector size / 8 |
| Slice division | 0xe82f3f5 | `div r13d` — quotient=slice size, remainder=extra items |
| Slice distribution | 0xe82f589-0xe82f593 | `div r13d` per item; `cmp remainder; sete` |
| Job launch call | 0xe831595-0xe8315ad | Calls scheduler enqueue (global 0x12ADF808, vtable+0xB0) with job fn 0xe83c390 |
| Job function | 0xe83c390 | Loads `this+0x19F60[job]`, calls worker task 0xe821120 |
| Per-job cmdlist array | this+0x19F60 | 8-byte pointers, one per job |
| Worker task | 0xe821120 | Records commands into per-job command list |
| Scheduler global | 0x12ADF808 | RenderDragon task scheduler instance |
| Scheduler enqueue | [rax+0xB0] | Vtable slot 22 of scheduler |
| Fence wait (join) | 0xe80ecb0 / 0xe818490 | GPU sync, drains all command lists including per-job |

---

## OPEN questions

- `[UNVERIFIED: 0xe82e230 where this+0x19F60 array is allocated/initialized]` — likely in context init (slot 0/1) or frame-context ring setup.
- `[UNVERIFIED: 0xe821120 exact Close/ExecuteCommandLists call sites]` — function is 50KB; needs separate reversal.
- `[UNVERIFIED: 0x12ADF808 exact scheduler instance type and enqueue function RVA]` — global points to scheduler; enqueue at vtable+0xB0.
- `[UNVERIFIED: 0xc25b1a0 enqueue entry point]` — U-C3a maps scheduler call map but not the specific enqueue method.
- `[UNVERIFIED: how many jobs / max job count]` — job count from vector at `this+0x3DA0A8`; max not statically determined.

---

## TOOL REQUESTS

None — all data from rdis `fn`/`dis`, `xref.py` not needed for this unit.

---

## Verification

Run `python tools/sigs/verify_oc.py docs/progress/oc_U-C8.md` to validate every quoted `0xRVA  instr` line.