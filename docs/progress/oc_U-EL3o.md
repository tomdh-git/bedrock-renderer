## NEXT
DONE

# U-EL3o — L3o Threading, encode-thread side (6cp RVAs re-verified on 1.26.62.01 per 6cw)

Checklist item (RENDER_CHECKLIST.md L3o): "Threading: draw executor runs as parallel jobs, one command list per job (this+0x19F60[job]), job slices of the sorted list (6cp); encode-thread side pending [RVAs in 6cp are 60.05, see 6cw]".

Pending part (the encode-thread side): re-verify on the 1.26.62.01 exe, by content not by prologue bytes (6cw rule):
 (1) draw-executor job wrapper = job lambda `operator()(job*, int jobIndex)` at 0xe83c390 (6cp quotes it from 1.26.60.05; 6cw: NOT shifted in 62.01);
 (2) executor entry 0xe821120 (6cw: NOT shifted; the +0xC00 shift applies to Encoder/submit/PSO, and item-loop loads moved inside the executor);
 (3) job slices of the sorted list: shared job state `job->+8` = {ptr0 submit-side context, ptr1 vector of per-job [begin,end)}, command list from `this+0x19F60[jobIndex]`, slice [begin,end) fed to the executor which walks `sorted[Frame+0x94700+pos*2]`.

Not re-proven here (C8 side, proven in oc_U-C8.md): job count vector this+0x3DA0A8, slice division 0xe82f3f5, scheduler enqueue via global 0x12ADF808 vtable+0xB0 with job fn 0xe83c390, join fence 0xe80ecb0; 0x19F60 array allocation; max job count [UNVERIFIED].

Method: static analysis only (Brief rule 1). RVAs and instruction text from `rdis dis` on the 1.26.62.01 exe; every claim carries [V] (seen in disassembly, RVA cited) and every quoted line is re-checked by `python tools/sigs/verify_oc.py`. 6cw addendum confirmed on this build: 0xe821120 executor entry, 0xe83c390 wrapper and its `call 0xE821120`, and slot 50 0xe82e230 are byte-identical to 60.05 (port_check_render_sigs.tsv lists both as unique 62.01 hits, "/1"). Inside the executor the 60.05 item-loop loads 0xe8216d2/0xe821814/0xe821a73 land at 0xe8222d2/0xe822414/0xe822673 in 62.01 (verified by content below; 6cw's +0xC02 estimate does not match the actual bytes). Wrapper size 0xd0 (entry 0xe83c390 .. ret 0xe83c45f; next function at 0xe83c460) matches 6cp's 0xd0 [V: entry/exit bytes read]. Executor size 0xc3c3 [V per docs/functions/e821120.md].

## (1) Draw-executor job wrapper 0xe83c390 — job lambda operator()(job*, int jobIndex) [V]

Entry `push rbp` at 0xe83c390, exit `ret` at 0xe83c45f, `int3` padding up to the next function at 0xe83c460, so size = 0xd0 = 6cp's size [V]. It has exactly one xref target: `call 0xE821120` at 0xe83c430 (the draw executor, docs/functions/e821120.md) [V]. Every instruction below read from the 62.01 disassembly.

## (2) Executor entry 0xe821120 [V]

Entry prologue matches the dossier: stack frame 0xe238 (`mov eax,0xE238; call 0xE9E7970; sub rsp,rax`), all xmm saved. It stores the per-job command-list wrapper (from `this+0x19F60[job]`) at job+0xA0, the Frame pointer at job+0x168 (used as `Frame*` throughout the item loop), the capture-struct pointer at job+0x3A8, and reads the 5th argument (capture struct) at [rbp+0xE228] [V].

## (3) Job slices of the sorted list — sorted-index u16 loads and strides [V]

6cw quotes three item-loop sorted-index loads; in 62.01 they are (verified by content): `0xe8222d2 movzx r8d,word ptr [rdx+rax*2+0x94700]`, `0xe822414 movzx edx,word ptr [rdx+rax*2+0x94700]`, `0xe822673 movzx eax,word ptr [r10+rax*2+0x94700]` — all read `u16 [Frame + 0x94700 + pos*2]` (Frame* = job+0x168), the sorted item-index list built by Frame::sort (6am), proving the executor walks `sorted[begin..end)` per job slice. Each is followed by `imul idx,0x540` (0x540 RenderDraw record stride: 0xe8222e2 / 0xe82267c) to index the draw record table at Frame+0x8B4700, and the side-table bind key at Frame+0x8B4778+idx*8 (0xe8222e9 / 0xe822683). Header offsets use `shl ...,7` (0x80-byte draw-header stride: 0xe8223b1 / 0xe82241c / 0xe822694). Per-job execution is counted with `lock inc dword ptr [rdx+0x4C]` (0xe8222c7), `[r8+rdx*4+0x4C]` (0xe822407) and `[rdx+0x50]` (0xe822668).

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|---|
| Job wrapper entry (job lambda `operator()(job*, int jobIndex)`) | 0xe83c390 | 1 | - | `0xe83c390  push rbp` | - | [V] |
| job->+8 shared job state = {ptr0 submit-side context, ptr1 slice vector} | job+8 | 8 | [rcx+8] (rcx = job*) | `0xe83c3aa  mov r8,[rcx+8]` | loads shared job state into r8 | [V] |
| shared_state+0 ptr0 = submit-side context (becomes executor arg rdx) | shared_state+0 | 8 | [r8] | `0xe83c3ae  mov rdx,[r8]` | ptr0 -> context, passed as executor rdx | [V] |
| shared_state+8 ptr1 = slice vector of u64 {begin,end} boundaries | shared_state+8 | 8 | [r8+8] | `0xe83c3b1  mov r9,[r8+8]` | ptr1 -> slice vector (N jobs, N+1 boundaries) | [V] |
| this+0x19F60 per-job command-list array base | ctx+0x19F60 | 8 | [rdx+0x19F60] (rdx = shared_state+0 = context) | `0xe83c3b8  mov rcx,[rdx+0x19F60]` | command-list wrapper array at this+0x19F60 | [V] |
| this+0x19F60[jobIndex] per-job command-list wrapper | ctx+0x19F60[job] | 8 | [rcx+r10*8] (r10d = job index from the edx argument) | `0xe83c3bf  mov rcx,[rcx+r10*8]` | one command list per job | [V] |
| slice vector base | slice+0 | 8 | [r9] (r9 = shared_state+8) | `0xe83c3c3  mov r11,[r9]` | slice vector base pointer | [V] |
| slice[jobIndex] = job's slice begin u64 | slice+idx*8 | 8 | [r11+r10*8] | `0xe83c3c6  mov r9,[r11+r10*8]` | begin u64 = vector[idx] | [V] |
| slice[jobIndex+1] = job's slice end u64 (rax = jobIndex+1 after `inc eax`) | slice+(idx+1)*8 | 8 | [r11+rax*8] | `0xe83c3cc  mov rax,[r11+rax*8]` | end u64 = vector[idx+1] | [V] |
| Wrapper -> executor call with the job's command list and slice | call 0xe821120 | - | direct call | `0xe83c430  call 0xE821120` | executor entry, once per job, its only caller | [V] |
| Executor entry | 0xe821120 | 1 | - | `0xe821120  push rbp` | - | [V] |
| job+0x3A8 = executor arg r9 = capture-struct pointer | job+0x3A8 | 8 | [rbx+0x3A8] = r9 | `0xe8211ac  mov [rbx+0x3A8],r9`<br>`0xe8211c1  mov rax,[rbp+0xE228]`<br>`0xe8211c8  mov rcx,[rax+0x38]` | capture struct (5th executor arg) stored per job; its +0x38 object's vcall+0x10 fills begin/end/flags | [V] |
| job+0x168 = executor arg r8 = Frame* | job+0x168 | 8 | [rbx+0x168] = r8 | `0xe8211b3  mov [rbx+0x168],r8` | Frame* used as the Frame base in the item loop | [V] |
| job+0xA0 = executor arg rcx = per-job command-list wrapper | job+0xA0 | 8 | [rbx+0xA0] = rcx | `0xe8211ba  mov [rbx+0xA0],rcx` | this+0x19F60[job] stored per job | [V] |
| Frame+0x94700+pos*2 sorted u16 index (3 loop variants) | Frame+0x94700+pos*2 | 2 | [Frame+0x94700+pos*2] (Frame* = job+0x168) | `0xe8222d2  movzx r8d,word ptr [rdx+rax*2+0x94700]`<br>`0xe822414  movzx edx,word ptr [rdx+rax*2+0x94700]`<br>`0xe822673  movzx eax,word ptr [r10+rax*2+0x94700]` | u16 entry = sorted draw index; executor walks sorted[begin..end) per job slice | [V] |
| job+0x4C per-job executed-item counter | job+0x4C | 4 | [rdx+0x4C] (rdx = [rbx+0x3A8] = job) | `0xe8222c7  lock inc dword ptr [rdx+0x4C]` | executed item count, per job (atomic) | [V] |
| job+0x4C+view*4 per-view counter inside the job | job+0x4C+view*4 | 4 | [r8+rdx*4+0x4C] (r8 = job) | `0xe822407  lock inc dword ptr [r8+rdx*4+0x4C]` | per-view executed count within the job slice | [V] |
| job+0x50 draw counter | job+0x50 | 4 | [rdx+0x50] (rdx = job) | `0xe822668  lock inc dword ptr [rdx+0x50]` | draw counter for the job's draw items | [V] |
| Frame+0x8B4700 0x540-stride draw-record array base | Frame+0x8B4700 | 8 | [rdx+0x8B4700] | `0xe8222db  mov r12,[rdx+0x8B4700]` | base of the 0x540-byte RenderDraw record array | [V] |
| draw record offset idx*0x540 | draw+idx*0x540 | - | computed: `imul rsi,r8,0x540` / `imul r15,rax,0x540` | `0xe8222e2  imul rsi,r8,0x540`<br>`0xe82267c  imul r15,rax,0x540` | 0x540-byte RenderDraw record stride (2 sites) | [V] |
| draw header offset idx*0x80 | header+idx*0x80 | - | computed: `shl r8d,7` / `shl edx,7` / `shl edx,7` | `0xe8223b1  shl r8d,7`<br>`0xe82241c  shl edx,7`<br>`0xe822694  shl edx,7` | 0x80-byte draw-header stride (3 sites) | [V] |
| Frame+0x8B4778+idx*8 side-table bind key u64 | Frame+0x8B4778+idx*8 | 8 | [rdx+r8*8+0x8B4778] / [r10+rax*8+0x8B4778] | `0xe8222e9  mov rax,[rdx+r8*8+0x8B4778]`<br>`0xe822683  mov rdx,[r10+rax*8+0x8B4778]` | RenderBind hash copy stored to job+0x110 / job+0x140 | [V] |
| draw+0x514 bind hash u32 | draw+0x514 | 4 | [r12+rsi+0x514] / [r8+r15+0x514] | `0xe8222f8  mov eax,[r12+rsi+0x514]`<br>`0xe8226e9  mov r8d,[r8+r15+0x514]` | bind hash stored to job+0x178 | [V] |
| job+0x110 / job+0x140 per-job side-table key slots | job+0x110 / job+0x140 | 8 | [rbx+0x110] / [rbx+0x140] | `0xe8222f1  mov [rbx+0x110],rax`<br>`0xe82268b  mov [rbx+0x140],rdx` | side-table key copied per executed item | [V] |

## CLOSES?

YES — every pending part of the item line is proven by [V] rows: (1) job wrapper 0xe83c390 re-verified on 62.01 by content (entry `push rbp`, job->+8 shared state {ptr0 context, ptr1 slice vector}, this+0x19F60[jobIndex] command-list wrapper, `call 0xE821120`, size 0xd0); (2) executor entry 0xe821120 re-verified by content (`push rbp`, frame 0xe238, job+0x3A8=r9 capture struct, job+0x168=r8 Frame*, job+0xA0=rcx command-list wrapper, [rbp+0xE228] 5th arg); (3) job slices of the sorted list proven (slice begin/end u64 from the vector, Frame+0x94700+pos*2 sorted u16 index at 0xe8222d2/0xe822414/0xe822673, imul 0x540 record stride, shl 7 header stride, Frame+0x8B4778+idx*8 side-table key, draw+0x514 bind hash, per-job lock inc counters). Blocking fact: none.

## TOOL REQUESTS

None — all data from `rdis dis` on the 1.26.62.01 exe and docs/BGFX_MAP.md sections 6cp/6cw (already on disk); verification via tools/sigs/verify_oc.py and tools/delegate.py check.

## NEXT
DONE
