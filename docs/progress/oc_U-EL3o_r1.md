## NEXT
DONE

# UNIT U-EL3o — L3o Threading, encode-thread side (6cp RVAs re-verified in 62.01 per 6cw)

Checklist item L3o: "Threading: draw executor runs as parallel jobs, one command list per job (this+0x19F60[job]), job slices of the sorted list (6cp); encode-thread side pending [RVAs in 6cp are 60.05, see 6cw]".

Scope (the pending part only): re-verify in the 1.26.62.01 exe the draw-executor wrapper (job lambda `operator()(job*, int jobIndex)`) and the executor entry that 6cp quotes as 0xe83c390 / 0xe821120 from 1.26.60.05, using 6cw's rule (verify by content in 62.01, never by prologue bytes alone). The C8-side facts (job count vector this+0x3DA0A8, slice div, scheduler enqueue global 0x12ADF808 vtable+0xB0, join fence 0xe80ecb0) were proven in oc_U-C8.md and are NOT re-proven here.

Source exegesis (6cp, 60.05 RVAs): "Draw executor job 0xe83c390 (0xd0 bytes) ... reads r8 = job->[+8] = {ptr0 -> submit-side context (rdx), ptr1 -> vector of per-job [begin,end) offsets into the sorted item list (r11[idx], r11[idx+1], u64 each)}, picks the job's command list from this->[+0x19F60][jobIndex] (mov rcx,[rdx+0x19f60]; mov rcx,[rcx+idx*8]), copies a small capture struct and calls the executor 0xe821120(cmdList, ?, ...) with the slice [begin,end)". 6cw addendum: executor entry 0xe821120, wrapper 0xe83c390 and slot 50 0xe82e230 are NOT shifted in 62.01; item-loop loads moved +0xC02 (0xe8222d4/0xe822415/0xe822675). 6cw correction (audit): executor sig was at 0xe820520 in 60.05 = +0xC00 -> 0xe821120 in 62.01 [V per docs/functions/e821120.md]; wrapper/slot 50 "treat as shifted until verified" per the audit, but the wrapper sig matches exactly once on 62.01 per docs/data/port_check_render_sigs.tsv, and docs/data/functions.tsv lists 0xe83c390 as the wrapper on this build. Both are re-verified below by content.

## (1) Draw-executor job wrapper — 0xe83c390 in 1.26.62.01 [V]

The wrapper is the job lambda `operator()(job*, int jobIndex)` cited by 6cp (0xd0 bytes there). In 62.01 it is at the same RVA: entry `push rbp` at 0xe83c390, exit `ret` at e83c45f followed by `int3` padding up to the next function at e83c4a0, so size = 0xd0 [V: entry/exit bytes read from the 62.01 disassembly; matches 6cp's 0xd0]. Every instruction below was read from the 62.01 disassembly — verbatim in the block, quoted again in the table rows.

```
0xe83c390  push rbp
0xe83c3aa  mov r8,[rcx+8]
0xe83c3ae  mov rdx,[r8]
0xe83c3b1  mov r9,[r8+8]
0xe83c3b8  mov rcx,[rdx+0x19F60]
0xe83c3bf  mov rcx,[rcx+r10*8]
0xe83c3c3  mov r11,[r9]
0xe83c3c6  mov r9,[r11+r10*8]
0xe83c3cc  mov rax,[r11+rax*8]
0xe83c430  call 0xE821120
```

| subject | offset | size | read/store address | `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|---|
| Draw-executor job wrapper entry (job lambda `operator()(job*, int jobIndex)`) | 0xe83c390 | 0xd0 | - | `0xe83c390  push rbp` | - | [V] |
| Job shared-state pointer `job->+8` = {ptr0, ptr1} | job+8 | 8 | [rcx+8] | `0xe83c3aa  mov r8,[rcx+8]` | - | [V] |
| Shared-state ptr0 = submit-side context (becomes executor `rdx`) | shared_state+0 | 8 | [r8] (r8 = [job+8]) | `0xe83c3ae  mov rdx,[r8]` | - | [V] |
| Shared-state ptr1 = slice vector of per-job [begin,end) boundaries | shared_state+8 | 8 | [r8+8] | `0xe83c3b1  mov r9,[r8+8]` | - | [V] |
| `this+0x19F60` per-job command-list array base (rdx = ptr0 = context) | ctx+0x19F60 | 8 | [rdx+0x19F60] | `0xe83c3b8  mov rcx,[rdx+0x19F60]` | - | [V] |
| `this+0x19F60[jobIndex]` per-job command-list wrapper (r10d = job index) | array+0 | 8 | [rcx+r10*8] | `0xe83c3bf  mov rcx,[rcx+r10*8]` | - | [V] |
| Slice vector base pointer | slice+0 | 8 | [r9] (r9 = [job+8+8]) | `0xe83c3c3  mov r11,[r9]` | - | [V] |
| Slice begin u64 = vector[idx] | slice+idx*8 | 8 | [r11+r10*8] | `0xe83c3c6  mov r9,[r11+r10*8]` | - | [V] |
| Slice end u64 = vector[idx+1] (rax = jobIndex+1) | slice+(idx+1)*8 | 8 | [r11+rax*8] | `0xe83c3cc  mov rax,[r11+rax*8]` | - | [V] |
| Wrapper calls the draw executor with the command list and the slice | call target 0xe821120 | - | direct call to 0xe821120 | `0xe83c430  call 0xE821120` | - | [V] |

## (2) Executor entry 0xe821120 and per-job state stores [V]

The executor is the worker task body called by the wrapper at `e83c430` (its only xref [V: rdis reports 1 xref into sub_e821120, from 0xe83c390]). In 62.01 it is at the same RVA as 6cp quotes. Entry prologue matches 6af: stack frame 0xe238 via `mov eax,0xE238; call 0xE9E7970; sub rsp,rax`, all xmm saved. It stores the per-job command-list wrapper (from `this+0x19F60[job]`) at job+0xA0, the Frame pointer at job+0x168 (used as `Frame*` throughout the item loop: `[rbx+0x168]+pos*8+0x14700` sort keys, `[rbx+0x168]+0x8B4700` draw records), and another pointer at job+0x3A8.

```
0xe821120  push rbp
0xe8211ac  mov [rbx+0x3A8],r9
0xe8211b3  mov [rbx+0x168],r8
0xe8211ba  mov [rbx+0xA0],rcx
0xe8211c1  mov rax,[rbp+0xE228]
```

| subject | offset | size | read/store address | `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|---|
| Draw executor worker task entry | 0xe821120 | - | - | `0xe821120  push rbp` | - | [V] |
| Job state job+0x3A8 = pointer stored from executor arg r9 (role not decoded in this unit) | job+0x3A8 | 8 | [rbx+0x3A8] = r9 (store) | `0xe8211ac  mov [rbx+0x3A8],r9` | - | [V] |
| Job state job+0x168 = Frame* (store at entry; loaded as `Frame` in the item loop at `0xe822219` and `0xe82266c`) | job+0x168 | 8 | [rbx+0x168] = r8 (store) | `0xe8211b3  mov [rbx+0x168],r8` | - | [V] |
| Job state job+0xA0 = per-job command-list wrapper (from `this+0x19F60[job]`) | job+0xA0 | 8 | [rbx+0xA0] = rcx (store) | `0xe8211ba  mov [rbx+0xA0],rcx` | - | [V] |
| Executor 5th argument = capture struct pointer (6cp: its +0x38 object's vcall +0x10 fills begin/end/flags) | [rbp+0xE228] | 8 | [rbp+0xE228] | `0xe8211c1  mov rax,[rbp+0xE228]` | - | [V] |

## (3) Job slices of the sorted list — the three sorted-index u16 loads [V]

6cw quotes three item-loop sorted-index loads at 0xe8222d4/0xe822415/0xe822675 (60.05 addresses, +0xC02 shift noted). In 62.01 they are at:
- `e8222d2` movzx r8d,word ptr [rdx+rax*2+0x94700] — draw-item variant (Frame* = rdx = [rbx+0x168], index = rax = pos)
- `e822414` movzx edx,word ptr [rdx+rax*2+0x94700] — variant used at the compute/custom path (e822414)
- `e822673` movzx eax,word ptr [r10+rax*2+0x94700] — variant used at e822673 (branch A/B re-entry)
All three read `u16 [Frame + 0x94700 + pos*2]`, the sorted item-index list built by Frame::sort (6am), proving the executor walks `sorted[begin..end)` per job slice. Each is followed by `imul idx,0x540` to index the 0x540-byte draw record table at Frame+0x8B4700 (e8222e2 / e82241c / e82267c), and the side-table bind key at Frame+0x8B4778+idx*8 (e8222e9 / e822683).

```
0xe8222d2  movzx r8d,word ptr [rdx+rax*2+0x94700]
0xe8222e2  imul rsi,r8,0x540
0xe8222e9  mov rax,[rdx+r8*8+0x8B4778]
0xe8222f1  mov [rbx+0x110],rax
0xe8222f8  mov eax,[r12+rsi+0x514]
0xe822300  mov [rbx+0x178],rax
0xe822414  movzx edx,word ptr [rdx+rax*2+0x94700]
0xe82241c  shl edx,7
0xe822673  movzx eax,word ptr [r10+rax*2+0x94700]
0xe82267c  imul r15,rax,0x540
0xe822683  mov rdx,[r10+rax*8+0x8B4778]
0xe82268b  mov [rbx+0x140],rdx
```

| subject | offset | size | read/store address | `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|---|
| Sorted u16 index list base + entry size | Frame+0x94700 (entry +pos*2) | 2 (u16) | [Frame+0x94700+pos*2], Frame* = job+0x168 | `0xe8222d2  movzx r8d,word ptr [rdx+rax*2+0x94700]`<br>`0xe822414  movzx edx,word ptr [rdx+rax*2+0x94700]`<br>`0xe822673  movzx eax,word ptr [r10+rax*2+0x94700]` | u16 entry = sorted draw index (all three loop variants) | [V] |
| Draw-record / header stride from index | draw record idx*0x540 ; header idx*0x80 | 8 | [Frame+0x94700+pos*2]->index then stride | `0xe8222e2  imul rsi,r8,0x540`<br>`0xe82267c  imul r15,rax,0x540`<br>`0xe82241c  shl edx,7` | 0x540-byte RenderDraw record stride (2 sites); 0x80-byte draw-header stride (1 site) | [V] |
| Side-table bind key u64 | Frame+0x8B4778+idx*8 | 8 | [rdx+r8*8+0x8B4778] / [r10+rax*8+0x8B4778] | `0xe8222e9  mov rax,[rdx+r8*8+0x8B4778]`<br>`0xe822683  mov rdx,[r10+rax*8+0x8B4778]` | RenderBind hash copy stored to job+0x110/job+0x140 | [V] |
| Draw record field at +0x514 (bind hash u32) | draw+0x514 | 4 | [r12+rsi+0x514] (r12 = Frame+0x8B4700 base, rsi = idx*0x540) | `0xe8222f8  mov eax,[r12+rsi+0x514]` | bind hash stored to job+0x178 | [V] |
| Per-job executed-item stat counter | job+0x4C | 4 | [rdx+0x4C] where rdx = job+0x3A8 (job-local stats) | `0xe8222c7  lock inc dword ptr [rdx+0x4C]` | executed item count (per job) | [V] |
