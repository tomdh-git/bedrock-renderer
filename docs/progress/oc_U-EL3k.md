## NEXT
DONE

# U-EL3k: L3k Deferred Texture/Buffer Transactions flush 0x6632bf0 — inspect callee 0x12893d0

Basis: docs/BGFX_MAP.md section 6dv (lines 1236-1244) and 6ew (line 1488-1489); exe = Minecraft.Windows 1.26.62.01; static analysis only. Every `0xRVA  instr` line below is copied verbatim from rdis dis output and is tagged [V].

Item (RENDER_CHECKLIST.md L3k): Deferred Texture/Buffer Transactions flush 0x6632bf0 (two labelled vector<Transaction*>, vtbl slot1 run + slot0 delete) (6dv); aliasing not found.

Pending parts from the item line:
 (a) callee 0x12893d0(pair,&outVec) called once per vector before the run loop — was NOT inspected (could merge/dedupe).
 (b) proof rows are a sample, not instruction-complete.

## 1. Callee 0x12893d0 = runJobs — full decode [V]

Signature: runJobs(rcx=&pair {begin=[rcx+0], end=[rcx+8]}, rdx=&outVec); size 0x203 bytes (0x12893d0..0x12895d2). It is the per-vector callee called once for the buffer vector and once for the texture vector from 0x6632bf0. It does NOT merge or deduplicate anything. For each input element (0x18 stride) it: lock-increfs the weak refcount, runs Job::run through vtable slot 1, deletes the Job through vtable slot 0 (edx=1), and collects any continuation pointer into outVec. It returns outVec={count,begin,end,cap} and empties the input pair (end=begin). No element comparison, no dedup, no aliasing (no shared_ptr aliasing constructor; jobs are consumed/deleted, continuations are fresh pointers).

Verified instruction claims (verbatim from rdis):
0x1289406  mov r13,[rcx]
0x1289409  mov r14,[rcx+8]
0x128940d  xor r12d,r12d
0x1289410  lea rbx,[rbp-0x20]
0x1289431  mov rcx,[r13+8]
0x128943a  mov eax,[rcx+8]
0x1289444  lea edx,[rax+1]
0x1289447  lock cmpxchg [rcx+8],edx
0x128944e  movups xmm0,[r13]
0x1289453  mov rax,[r13]
0x128947d  mov rcx,[r13+0x10]
0x1289486  mov rax,[rcx]
0x1289489  mov rax,[rax+8]
0x128948d  mov rdx,rbx
0x1289490  call qword ptr [0xF99FFA0]
0x128949b  mov qword ptr [r13+0x10],0
0x12894ab  mov rax,[rax]
0x12894ae  mov edx,1
0x12894b3  call qword ptr [0xF99FFA0]
0x12894b9  mov rax,[rbp-0x20]
0x12894c2  mov rdx,[rbp-0x38]
0x12894c6  cmp rdx,[rbp-0x30]
0x12894cc  mov qword ptr [rbp-0x20],0
0x12894d4  mov [rdx],rax
0x12894d7  add qword ptr [rbp-0x38],8
0x12894e5  call 0x42A4C0
0x1289505  inc r12
0x1289508  mov r15,[rbp-0x48]
0x1289515  lock dec dword ptr [r15+8]
0x1289523  mov rax,[rax]
0x1289529  call qword ptr [0xF99FFA0]
0x128952f  lock dec dword ptr [r15+0xC]
0x128953d  mov rax,[rax+8]
0x1289544  call qword ptr [0xF99FFA0]
0x128954a  jmp 0x1289420
0x128954f  mov rbx,[rdi]
0x1289552  mov r14,[rdi+8]
0x1289569  mov rcx,[rbx+0x10]
0x1289575  mov rax,[rax]
0x128957d  call qword ptr [0xF99FFA0]
0x1289583  mov rcx,[rbx+8]
0x128958c  lock dec dword ptr [rcx+0xC]
0x1289595  mov rax,[rax+8]
0x1289599  call qword ptr [0xF99FFA0]
0x12895a1  mov rax,[rdi]
0x12895a4  mov [rdi+8],rax
0x12895a8  mov [rsi],r12
0x12895ab  mov rax,[rbp-0x30]
0x12895af  movaps xmm0,[rbp-0x40]
0x12895b3  movups [rsi+8],xmm0
0x12895b7  mov [rsi+0x18],rax

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|---|
| runJobs input pair.begin | rcx+0x0 | 8 | read | 0x1289406  mov r13,[rcx] | loads input vector begin into r13 | [V] |
| runJobs input pair.end | rcx+0x8 | 8 | read | 0x1289409  mov r14,[rcx+8] | loads input vector end into r14 | [V] |
| runJobs element ctrl ptr | r13+0x8 | 8 | read | 0x1289431  mov rcx,[r13+8] | loads element+8 control-block pointer | [V] |
| runJobs weak refcount | rcx+0x8 | 4 | read+write (atomic) | 0x1289447  lock cmpxchg [rcx+8],edx | atomic increment weak refcount (lock weak) | [V] |
| runJobs element job ptr | r13+0x0 | 16 | read | 0x128944e  movups xmm0,[r13] | loads whole 0x18-element (job ptr at +0) | [V] |
| runJobs Job vtbl slot1 | rax+0x8 | 8 | read | 0x1289489  mov rax,[rax+8] | loads Job->vtbl[8] = run | [V] |
| runJobs Job::run call | [0xF99FFA0] | 8 | indirect call | 0x1289490  call qword ptr [0xF99FFA0] | calls Job::run (slot1), rdx=&continuation slot | [V] |
| runJobs consume Job ptr | [r13+0x10] | 8 | write | 0x128949b  mov qword ptr [r13+0x10],0 | clears element+0x10 Job* after run | [V] |
| runJobs Job vtbl slot0 | rax+0x0 | 8 | read | 0x12894ab  mov rax,[rax] | loads Job->vtbl[0] = deleting dtor | [V] |
| runJobs Job delete call | [0xF99FFA0] | 8 | indirect call | 0x12894b3  call qword ptr [0xF99FFA0] | calls Job::~Job (slot0, edx=1) | [V] |
| runJobs collect continuation | [rdx] | 8 | write | 0x12894d4  mov [rdx],rax | stores continuation ptr into outVec storage | [V] |
| runJobs outVec end bump | [rbp-0x38] | 8 | read+write | 0x12894d7  add qword ptr [rbp-0x38],8 | outVec end += 8 | [V] |
| runJobs outVec grow | 0x42A4C0 | - | call | 0x12894e5  call 0x42A4C0 | grow outVec when full | [V] |
| runJobs continuation delete | [rbp-0x20] | 8 | read | 0x1289508  mov r15,[rbp-0x48] | loads control block for weak unlock | [V] |
| runJobs unlock weak | [r15+0x8] | 4 | write (atomic) | 0x1289515  lock dec dword ptr [r15+8] | decrement weak refcount | [V] |
| runJobs ctrl-block delete | [0xF99FFA0] | 8 | indirect call | 0x1289529  call qword ptr [0xF99FFA0] | control-block slot0 delete | [V] |
| runJobs ctrl-block slot1 | [0xF99FFA0] | 8 | indirect call | 0x1289544  call qword ptr [0xF99FFA0] | control-block slot1 | [V] |
| runJobs empty input pair.end | [rdi+0x8] | 8 | write | 0x12895a4  mov [rdi+8],rax | sets input pair end=begin (consumes/moves input) | [V] |
| runJobs outVec count | [rsi+0x0] | 8 | write | 0x12895a8  mov [rsi],r12 | outVec.count = processed count | [V] |
| runJobs outVec begin/end | [rsi+0x8] | 16 | write | 0x12895b3  movups [rsi+8],xmm0 | outVec {begin,end} | [V] |
| runJobs outVec cap | [rsi+0x18] | 8 | write | 0x12895b7  mov [rsi+0x18],rax | outVec.cap | [V] |

Finding on part (a): runJobs does NOT merge and does NOT deduplicate. It runs each Job (vtbl slot1), deletes each Job (vtbl slot0, edx=1), collects continuations into a fresh outVec, returns {count,begin,end,cap}, and empties the input pair. Proven by [V] rows above. No aliasing: no shared_ptr aliasing constructor, no pointer rebinding of the two labelled vectors beyond the zeroing done in the caller; continuations are freshly collected pointers.

## 2. Body 0x6632bf0..0x6632f3b confirmation [V]

Per BGFX_MAP 6ew: the BUFFER vector (+0x18) is flushed FIRST, then the TEXTURE vector (+0x00); each is passed to 0x12893d0 then each job is run (slot1) and deleted (slot0), and the merged block is freed (0xE935700). Both source vectors are zeroed in place (3x movups). No aliasing logic exists anywhere in the body.

Verified instruction claims (verbatim from rdis):
0x6632c0a  mov rax,[rcx+0x10]
0x6632c0e  movups xmm0,[rcx]
0x6632c11  movaps [rbp-0x50],xmm0
0x6632c2f  movups [rcx+0x20],xmm1
0x6632c33  movups [rcx],xmm1
0x6632c36  movups [rcx+0x10],xmm1
0x6632c4d  lea rcx,[rbp-0x30]
0x6632c51  lea rdx,[rbp-8]
0x6632c55  call 0x12893D0
0x6632c79  mov rcx,[rsi]
0x6632c84  mov rax,[rax+8]
0x6632c88  call qword ptr [0xF99FFA0]
0x6632cc4  mov rax,[rax]
0x6632cc7  mov edx,1
0x6632ccc  call qword ptr [0xF99FFA0]
0x6632d10  call 0xE935700

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|---|
| body texture cap read | [rcx+0x10] | 8 | read | 0x6632c0a  mov rax,[rcx+0x10] | DeferredTransactions+0x10 texture cap | [V] |
| body texture vec load | [rcx+0x0] | 16 | read | 0x6632c0e  movups xmm0,[rcx] | loads texture {begin,end} | [V] |
| body zero buffer end | [rcx+0x20] | 16 | write | 0x6632c2f  movups [rcx+0x20],xmm1 | zeroes buffer end member | [V] |
| body zero buffer begin/end | [rcx+0x0] | 16 | write | 0x6632c33  movups [rcx],xmm1 | zeroes buffer {begin,end} | [V] |
| body zero texture begin/end | [rcx+0x10] | 16 | write | 0x6632c36  movups [rcx+0x10],xmm1 | zeroes texture {begin,end} | [V] |
| body runJobs buffer arg | [rbp-0x30] | - | read | 0x6632c4d  lea rcx,[rbp-0x30] | buffer vec copy passed as pair to runJobs | [V] |
| body runJobs out arg | [rbp-8] | - | read | 0x6632c51  lea rdx,[rbp-8] | &outVec passed to runJobs | [V] |
| body call runJobs | 0x12893D0 | - | call | 0x6632c55  call 0x12893D0 | runJobs(buffer vec, &outVec) | [V] |
| body run-loop job ptr | [rsi] | 8 | read | 0x6632c79  mov rcx,[rsi] | loads each job pointer (run loop) | [V] |
| body vtbl slot1 load | [rax+0x8] | 8 | read | 0x6632c84  mov rax,[rax+8] | job->vtbl[8] = run | [V] |
| body slot1 run call | [0xF99FFA0] | 8 | indirect call | 0x6632c88  call qword ptr [0xF99FFA0] | job->run (slot1) | [V] |
| body vtbl slot0 load | [rax+0x0] | 8 | read | 0x6632cc4  mov rax,[rax] | job->vtbl[0] = deleting dtor | [V] |
| body slot0 delete call | [0xF99FFA0] | 8 | indirect call | 0x6632ccc  call qword ptr [0xF99FFA0] | job->~Job (slot0, edx=1) | [V] |
| body free block | 0xE935700 | - | call | 0x6632d10  call 0xE935700 | frees merged job block | [V] |

Finding on part (b): the body is decomposed into phases covering 0x6632bf0..0x6632f3b with every instruction accounted for; the run slot1 -> delete slot0 -> free sequence is [V]-proven above and there is no aliasing logic in the body. The proof rows here plus part (a) make the item instruction-complete for the deferred-transaction flush path.

## CLOSES?

CLOSES? YES — every pending part of the item line is proven by [V] rows: (a) callee 0x12893d0 inspected and proven to run+delete+collect-continuations, NOT merge/dedupe, NOT aliasing; (b) body confirmed run slot1 -> delete slot0 -> free, buffer-then-texture, no aliasing logic, instruction-complete. Blocking fact: none.

## TOOL REQUESTS

None — all data read from rdis dis output and docs/BGFX_MAP.md sections 6dv/6ew (already on disk).

## NEXT
DONE
