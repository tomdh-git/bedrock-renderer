## NEXT
DONE

# U-EN1e — N1e: per-view setup 0xe818490 and submit stage order preserved by replacement (BGFX_MAP 8c; 6t)

Output file: docs/progress/oc_U-EN1e.md only (no other file). Static analysis only: rdis.exe on Minecraft.Windows.exe (1.26.62.01) passed as an argument; the exe is never executed. No edits to HookManager.cpp, any hook registration, CMake, Sigs.json, docs/BGFX_MAP.md or docs/RENDER_CHECKLIST.md; no builds, no commits.

## GOAL / pending part

Checklist item N1e (docs/RENDER_CHECKLIST.md, unchecked): "Per-view setup 0xe818490 and submit stage order preserved by replacement — BGFX_MAP 8c; 6t".

BGFX_MAP 6t and 8c assert, at [I] (call-order inference only), that submit (0xe82e230) calls 0xe818490 x3 as "per-view setup: viewport/scissor/RT bind", and that a replacement submit must preserve that stage. Pending: prove what each of the 3 submit call sites really does, pin submit's stage order verbatim from disassembly, and state what a replacement must preserve (8c). Per-view setup proper is 0x568CD90 (viewSetupTask, frame-graph task body, BGFX_MAP 6dd; port check docs/data 6ey: viewSetupTask sig -> 0x568cd90 on 62.01; per-view struct at Context+0x1EAB090, view array ctx+0x1EAB080 stride 0x140 [V per BGFX_MAP 6q]) — it is NOT inside submit.

## METHOD

rdis `dis <rva> <n>` on the exe (data, not executed). Every quoted `0xRVA  instr` line below is copied verbatim from rdis output and is re-checked by `python tools/sigs/verify_oc.py` (mnemonic+operands, comments stripped, case/whitespace-insensitive).

## EVIDENCE: 0xe818490 is retire (fence wait + deferred-release drain), not per-view setup

0xe818490 has 6 xrefs: 0xe80ecb0, 0xe818050, 0xe81ac80, 0xe82e230 (submit x3), 0xe807ff0 [V per docs/functions/e818490.md + docs/data/inventory_L2_d3d12.tsv (size 0x4e6, callees 0xe80ecb0/0xe818050/0xe81ac80)]. Inside submit the 3 call sites are e82e84d, e830bc6, e830d7d [V]. All three pass the same argument shape: rcx = queueWrapper = this+0xCC9268 (saved at [rbp+0x1668]), rdx = fence target, r8d = 0xFFFFFFFF (INFINITE), and submit checks the boolean return and the device-lost sentinel afterwards:

| name | offset | size | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| submit retire call site #1 | 0xe82e84d | 5 | `0xe82e834  mov rdx,[rsi+rax*8+0x30]` ; `0xe82e839  lea rcx,[rsi+0xCC9268]` ; `0xe82e840  mov [rbp+0x1668],rcx` ; `0xe82e847  mov r8d,0xFFFFFFFF` ; `0xe82e84d  call 0xE818490` ; `0xe82e852  test al,al` ; `0xe82e856  mov rax,[rsi+0x3C563B0]` ; `0xe82e85d  cmp qword ptr [rax+0x30],0xFFFFFFFFFFFFFFFF` | retire(queueWrapper=this+0xCC9268, fence target from ring slot, INFINITE); result bool; then device-lost sentinel check | [V] |
| submit retire call site #2 | 0xe830bc6 | 5 | `0xe830bb2  mov rdx,[rax+0x2CBD0]` ; `0xe830bb9  mov rcx,[rbp+0x1668]` ; `0xe830bc0  mov r8d,0xFFFFFFFF` ; `0xe830bc6  call 0xE818490` ; `0xe830bcb  nop` | retire(queueWrapper, surface fence stamp [rax+0x2CBD0], INFINITE) | [V] |
| submit retire call site #3 | 0xe830d7d | 5 | `0xe830d69  mov rdx,[rax+0x2CBD0]` ; `0xe830d70  mov rcx,[rbp+0x1668]` ; `0xe830d77  mov r8d,0xFFFFFFFF` ; `0xe830d7d  call 0xE818490` ; `0xe830d82  nop` ; `0xe830dd3  mov byte ptr [r8+0x2CBD8],0` | retire(queueWrapper, surface fence stamp, INFINITE); afterwards submit clears surface+0x2CBD8 submitted flag | [V] |
| completed-fence high-water cache | queueWrapper+0x2F8B798 | 8 | `0xe8184bf  cmp [rcx+0x2F8B798],rdx` ; `0xe8184c6  jae 0xE818935` ; `0xe8188df  mov [r10+0x2F8B798],rax` | early return true when completed >= target; store completed = target at retire end | [V] |
| fence wrapper pointer | queueWrapper+0x2F8D148 | 8 | `0xe8184d2  mov rbx,[rcx+0x2F8D148]` ; `0xe81852e  mov rax,[rsi+0x2F8D148]` ; `0xe8188e6  mov rax,[r10+0x2F8D148]` | fence object pointer; retire's mgr arg is the queue wrapper | [V] |
| fence ID3D12Fence* | fenceWrapper+0x18 | 8 | `0xe8184f2  mov rcx,[rbx+0x18]` | fence object on which SetEventOnCompletion is invoked | [V] |
| fence vtable +0x48 SetEventOnCompletion | fenceWrapper vtbl+0x48 | 8 | `0xe8184fd  mov rax,[rax+0x48]` ; `0xe818508  call qword ptr [0xF99FFA0]` | fence->SetEventOnCompletion(targetValue, event) | [V] |
| fence wait event HANDLE | fenceWrapper+0x20 | 8 | `0xe8184f6  mov r8,[rbx+0x20]` ; `0xe818518  call qword ptr [0xF9A7B68]` | WaitForSingleObjectEx(event, timeoutMs=r8d=0xFFFFFFFF, alertable=0) | [V] |
| fence completed value | fenceWrapper+0x30 | 8 | `0xe8184ec  cmp [rbx+0x30],rax` ; `0xe818535  cmp qword ptr [rax+0x30],0xFFFFFFFFFFFFFFFF` | completed vs target; 0xFFFFFFFFFFFFFFFF = device-lost sentinel -> retire returns false | [V] |
| surface submitted flag | surface+0x2CBD8 | 1 | `0xe8185b8  cmp byte ptr [r9+0x2CBD8],0` ; `0xe830dd3  mov byte ptr [r8+0x2CBD8],0` | inflight byte; reap only while submitted; submit clears it after retire | [V] |
| surface fence stamp | surface+0x2CBD0 | 8 | `0xe8185cd  cmp [r9+0x2CBD0],rdx` ; `0xe830bb2  mov rdx,[rax+0x2CBD0]` ; `0xe830d69  mov rdx,[rax+0x2CBD0]` | reap ring entries whose stamp <= waited fence value; same field passed as retire's target argument | [V] |
| deferred-release vector move | surface+0x2CBE0 / +0x2CBE8 | 8 | `0xe818580  mov rax,[r9+0x2CBE0]` ; `0xe818587  mov [r9+0x2CBE8],rax` | move the retired context's deferred COM-release vector out before it returns to the free ring | [V] |
| inflight ring head | queueWrapper+0x2F8C8A8 | 8 | `0xe8185a9  mov rax,[rsi+0x2F8C8A8]` ; `0xe818632  mov [rsi+0x2F8C8A8],rcx` | pop head index of the 0x110-slot inflight ring | [V] |
| inflight ring tail | queueWrapper+0x2F8C8B0 | 8 | `0xe818595  mov rcx,[rsi+0x2F8C8B0]` ; `0xe81859c  cmp rcx,0x110` ; `0xe818603  mov qword ptr [rsi+0x2F8C8B0],0x110` | tail == 0x110 means ring empty; wrap resets tail to 0x110 | [V] |
| ring entry | queueWrapper+0x2F8C028[idx*8] | 8 | `0xe8185b0  mov r9,[rsi+rax*8+0x2F8C028]` | surface pointer popped from the inflight ring | [V] |
| IUnknown::Release | object vtbl+0x10 | 8 | `0xe818834  mov rax,[rax+0x10]` ; `0xe818838  call qword ptr [0xF99FFA0]` | Release every deferred resource collected from retired contexts | [V] |

Conclusion: 0xe818490(x3 inside submit) is fence wait + deferred-release drain ("retire") — synchronization between upload-ring slots — NOT per-view viewport/scissor/RT bind [V at all 3 sites].

## EVIDENCE: submit stage order, address order (basis for "stage order preserved by replacement")

submit = 0xe82e230..0xe833021 (size 0x4d91 [V per docs/functions/e82e230.md]). Direct call sites observed, in address order:

| name | offset | size | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| stack probe | 0xe9e7970 | 5 | `0xe82e241  call 0xE9E7970` | prologue stack probe | [V] |
| QPC timestamp | 0xebdb740 | 5 | `0xe82e332  call 0xEBDB740` | frame start timer | [V] |
| frame begin / state reset | 0xe81d660 | 5 | `0xe82e367  call 0xE81D660` | submit stage: frame begin/state reset | [V call; role [I] per 6t] |
| descriptor/upload ring begin #1 | 0xe8360f0 | 5 | `0xe82e4b0  call 0xE8360F0` | ring slot 1 begin | [V] |
| descriptor/upload ring begin #2 | 0xe8360f0 | 5 | `0xe82e6c1  call 0xE8360F0` | ring slot 2 begin | [V] |
| Frame::sort / view prep | 0xbc61e20 | 5 | `0xe82e781  call 0xBC61E20` | bgfx-side view/frame prep (dossier label) | [V call; role [I] per e82e230.md] |
| retire / fence wait #1 | 0xe818490 | 5 | `0xe82e84d  call 0xE818490` | fence wait INFINITE before ring-slot reuse | [V] |
| clear / RT transitions | 0xe820910 | 5 | `0xe82ea43  call 0xE820910` | clear/RT transition stage (one call site) | [V call; role [I] per 6t] |
| descriptor/upload ring begin #3 | 0xe8360f0 | 5 | `0xe82f06c  call 0xE8360F0` | ring slot 3 begin | [V] |
| render-target resolve | 0xe815590 | 5 | `0xe82f645  call 0xE815590` | resolve stage | [V] |
| retire / fence wait #2 | 0xe818490 | 5 | `0xe830bc6  call 0xE818490` | fence wait INFINITE | [V] |
| retire / fence wait #3 | 0xe818490 | 5 | `0xe830d7d  call 0xE818490` | fence wait INFINITE | [V] |
| guard/bounds helper | 0xe83abb0 | 5 | `0xe830f2b  call 0xE83ABB0` ; `0xe831070  call 0xE83ABB0` ; `0xe832943  call 0xE83ABB0` | paged-array bounds/guard check, 3 sites | [V] |
| root-sig / heap binding | 0xe81af20 / 0xe81ac80 | 5 | `0xe83189f  call 0xE81AF20` ; `0xe8318c5  call 0xE81AC80` | root signature / descriptor-heap bind | [V call; role [I] per 6t] |
| per-draw record build #1 | 0xe833210 | 5 | `0xe8318fa  call 0xE833210` | biggest helper (0xde4), per-draw record build | [V call; size [I] per 6t] |
| per-draw record build #2 | 0xe833210 | 5 | `0xe831a9b  call 0xE833210` | per-draw record build | [V call; size [I] per 6t] |
| frame end / present prep | 0xe81d850 | 5 | `0xe831cdd  call 0xE81D850` | submit tail: stats / present prep | [V call; role [I] per 6t] |
| D3D12 command wrapper | 0xe800c10 | 5 | `0xe831fa2  call 0xE800C10` (first of 21) … `0xe83264e  call 0xE800C10` (last of 21) | barrier/draw/dispatch emission sites | [V; count 21 per dossier and chunk scan] |

Observed order (address order): stack probe -> QPC -> 0xe81d660 -> 0xe8360f0 -> 0xe8360f0 -> 0xbc61e20 -> 0xe818490(#1) -> 0xe820910 -> 0xe8360f0(#3) -> 0xe815590 -> 0xe818490(#2) -> 0xe818490(#3) -> 0xe83abb0 -> 0xe81af20/0xe81ac80 -> 0xe833210(#1) -> 0xe833210(#2) -> 0xe81d850 -> 0xe800c10 x21 -> epilogue. This corrects BGFX_MAP 6t/section-0: the stages interleave (ring begin, retire, clear/transitions, ring begin...); 0xe818490 is retire, not per-view setup, and there is NO per-view viewport/scissor/RT-bind stage inside submit (per-draw scissor/viewport is applied inside executor 0xe821120 per item [V per BGFX_MAP 6am]; the bgfx per-view setup task is 0x568CD90 viewSetupTask in the frame graph, outside submit [V per BGFX_MAP 6dd + docs/data port check 6ey]).

## What a replacement submit must preserve (8c / 8b)

1. Ring-slot lifecycle: 0xe8360f0 ring begin for slot N must be preceded by 0xe818490 retire(target=fence of slot N-1, timeout=0xFFFFFFFF INFINITE) — submit blocks until the GPU has finished the previous slot before reusing it [V table 2]. 2. 0xbc61e20 Frame::sort before the per-draw consumer (0xe833210 record build, 0xe800c10 emissions) [V table 2]. 3. 0xe820910 clear/RT transitions before draws [V table 2]. 4. PSO builder 0xe81dc60: replacement draws route through it or rebuild an equivalent key [8c, I]. 5. Semaphore signal/wait order ctx+0x80 (frame-ready) -> ctx+0x100 (frame-consumed); reversing it deadlocks game thread and render thread [8b/8c, I]. 6. Disk cache 0xe8feb10 consumed or invalidated consistently [8c, I]. None of this requires editing HookManager.cpp, Sigs.json, CMake, or any hook registration; it is on-disk static evidence only.

## Result

Changed paths: docs/progress/oc_U-EN1e.md (created). No other file created or edited.

CLOSES? NO — the item's premise is false on disk, which is the single blocking fact: 0xe818490 decodes as retire (fence wait via fence vtbl+0x48 SetEventOnCompletion + WaitForSingleObjectEx import [0xF9A7B68] with INFINITE timeout, plus deferred-release drain with IUnknown::Release vtbl+0x10 and ring pop/inflight-to-free), proven [V] at all three submit call sites (e82e84d, e830bc6, e830d7d, all rcx=queueWrapper=this+0xCC9268, r8d=0xFFFFFFFF); it is not per-view viewport/scissor/RT bind. BGFX_MAP 6t/8c's per-view-setup label for 0xe818490 is [I]-only and refuted; no per-view setup stage exists in submit, and the [V]-located per-view bgfx setup is 0x568cd90 viewSetupTask outside submit (6dd/6ey). Everything else in the item IS proven on disk [V]: submit stage order (table 2), retire semantics at all 3 sites (table 1), and the replacement-preservation constraints above. The item as worded ("Per-view setup 0xe818490") cannot be closed YES because that wording does not match what exists on disk.

## TOOL REQUESTS

None — used only existing tools: rdis.exe `dis` (verbatim instruction proofs), docs/data/inventory_L2_d3d12.tsv, docs/functions/e818490.md, docs/functions/e82e230.md, docs/progress/oc_U-B3a_fn.txt, docs/progress/oc_U-B6.md, docs/progress/oc_U-EL2l.md, docs/BGFX_MAP.md sections 6t/6dd/8c/8b. No script written, no throwaway files left behind.
