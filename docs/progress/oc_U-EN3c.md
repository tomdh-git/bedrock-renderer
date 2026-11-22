## NEXT
DONE

UNIT: U-EN3c — Close checklist item N3c "Custom items invoked on render thread in view order — BGFX_MAP 11d [?]"
Target exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01), RVAs relative to image base. Static analysis only; no game launch/build/commit.

PENDING PART (per item line): BGFX_MAP section 11d "Custom items via submitCustom are invoked on the render thread in view order [?]". Section 12 (6ii audit) asserts it is [V] by 6fg but 11d itself still carries [?]; the item line closes only when 11d's claim is proven by [V] rows here.

Section 6fg/6fh claims (hypotheses to verify with rdis, not trusted yet):
- 0xbc61560 = submitCustom(view u16, fn r8, user r9): stores r8 at encoder+0x100, r9 at encoder+0x108, sets sort-key bit 53; six tail jumps reach it from pass-task encode() bodies (e.g. 0x568b9e0: v->encoder->submitCustom(v->viewId, &PassTask::renderThreadBody, this)).
- Executor custom-item path at 0xe822400 (0xe821120): cls = key & 0x3000000000000000 == bit53; fn = slot[0], user = slot[1]; builds 0x18-byte context {rip-relative ptr, job field, commandList = [[rbx+0x90]+0x30]}; calls fn(user, &ctx) through CFG dispatch thunk — i.e. on the render thread, in sort order, inside its view.
- Render-thread reach: 0xbc63150 (renderFrame, render-thread proc 0xbc65720 loop) calls submit slot 50 via renderer vtable +0x190 (6ex); executor runs inside submit's job slices (6cp: 4 executor jobs per submit).

VERIFICATION PLAN (rdis only):
1. rdis 0xbc61560 — confirm submitCustom stores r8/r9 at encoder +0x100/+0x108 and sets key bit 53.
2. rdis 0xe822400 area of 0xe821120 — confirm custom path reads slot[0]/slot[1] and calls fn(user,&ctx).
3. rdis one pass encode body (0x568b9e0) — confirm tail jump to submitCustom with (viewId, static fn, this).
4. rdis 0xbc63150 — confirm submit slot 50 call from renderFrame on the render thread.

## N3c verification (BGFX_MAP 11d: "Custom items via submitCustom are invoked on the render thread in view order [?]")

Claim to close: submitCustom(encoder, viewId, fn=r8, user=r9) records a custom item whose sort key has bit 53 set; the executor walks items in sorted-key order (viewId is the high key field, viewId<<54) and invokes fn(user, &ctx) for every custom slot; submit is reached from renderFrame on the bgfx render thread (thread proc 0xbc65720 loops on 0xbc63150 [V per BGFX_MAP 6as/6ex]), so the invocation happens on the render thread, in view order. All RVAs verified by rdis against Minecraft.Windows.exe 1.26.62.01; every quoted line below matches the live disassembly verbatim.

| offset | size | read/store address | `0xRVA  instr` | meaning | tag |
| 0xbc61645 | 8 | encoder+0x100 (custom-item fn slot) | `0xbc61645  mov [rsi+0x100],r8` | submitCustom stores the render-thread callback fn (r8) at encoder+0x100 | [V] |
| 0xbc6164c | 8 | encoder+0x108 (custom-item user slot) | `0xbc6164c  mov [rsi+0x108],r9` | submitCustom stores the user data (r9 = the pass task object) at encoder+0x108 | [V] |
| 0xbc61690 | 8 | - | `0xbc61690  shl rax,0x36` | viewId<<54: view is the top sort-key field, so sorted order is view order | [V] |
| 0xbc61697 | 8 | - | `0xbc61697  mov rcx,0x20000000000000` | 0x20000000000000 = bit 53, the custom-item class bit, OR'd into the sort key | [V] |
| 0xbc616aa | 8 | Frame+0x14700+idx*8 (sort key array) | `0xbc616aa  mov [rax+r15*8+0x14700],rcx` | custom sort key (bit53 | view<<54 | seq) written for the new item | [V] |
| 0x568ba60 | 8 | - | `0x568ba60  lea r8,[0x568BCD0]` | pass-task encode() loads fn = PassTask::renderThreadBody at 0x568BCD0 | [V] |
| 0x568ba67 | 8 | - | `0x568ba67  mov r9,rsi` | encode() sets user arg r9 = this task object | [V] |
| 0x568ba70 | 5 | - | `0x568ba70  jmp 0xBC61560` | encode() tail-calls submitCustom(encoder, viewId, fn, user) | [V] |
| 0xe822414 | 2 | Frame+0x94700+pos*2 (sorted id list) | `0xe822414  movzx edx,word ptr [rdx+rax*2+0x94700]` | executor walks items in sorted-key order | [V] |
| 0xe822426 | 8 | custom-item slot+0x00 (fn field) | `0xe822426  mov rax,[r8+rdx]` | executor loads fn = slot[0]; fn==0 → not a custom item | [V] |
| 0xe82245d | 8 | custom-item slot+0x08 (user field) | `0xe82245d  mov rcx,[rdx+8]` | executor loads user = slot[8] → callback's 1st arg | [V] |
| 0xe822468 | 8 | CFG thunk [0xF99FFA0], rax=fn | `0xe822468  call qword ptr [0xF99FFA0]` | executor invokes fn(user in rcx, &ctx in rdx) — the custom item body | [V] |
| 0xbc633a8 | 8 | renderer vtable+0x190 (slot 50 = submit) | `0xbc633a8  mov rax,[rax+0x190]` | renderFrame loads submit slot 50 | [V] |
| 0xbc633af | 8 | CFG thunk [0xF99FFA0] | `0xbc633af  call qword ptr [0xF99FFA0]` | renderFrame (render-thread frame step from 0xbc65720's loop) calls submit → executor runs on the render thread | [V] |

CLOSES?: YES — every clause of the 11d claim is proven by [V] rows: (1) custom items: submitCustom sets sort-key bit 53 (`0xbc61697 mov rcx,0x20000000000000`, `0xbc616a1 or rcx,rax`) and stores fn+user at encoder+0x100/+0x108 (`0xbc61645`, `0xbc6164c`); (2) invoked on the render thread: submit slot 50 is called from renderFrame (render-thread frame step, thread proc 0xbc65720 loops on 0xbc63150 [V per BGFX_MAP 6as/6ex]) via `0xbc633a8 mov rax,[rax+0x190]` / `0xbc633af call qword ptr [0xF99FFA0]`; (3) in view order: the executor walks `Frame+0x94700` in sorted-key order (`0xe822414 movzx edx,word ptr [rdx+rax*2+0x94700]`) where viewId<<54 is the top key field (`0xbc61690 shl rax,0x36`), and invokes each custom item's `fn(user, &ctx)` (`0xe822426 mov rax,[r8+rdx]`, `0xe82245d mov rcx,[rdx+8]`, `0xe822468 call qword ptr [0xF99FFA0]`). Pass tasks queue themselves via encode() → submitCustom tail jump (`0x568ba60 lea r8,[0x568BCD0]`, `0x568ba67 mov r9,rsi`, `0x568ba70 jmp 0xBC61560`) with fn = PassTask::renderThreadBody (0x568BCD0) and user = the task object.

Summary of what exists on disk now: docs/progress/oc_U-EN3c.md only (this file). No code changed — N3c is a documentation/verification item; the proof is in the [V] rows above, all verbatim from rdis on 1.26.62.01.

## TOOL REQUESTS

None — all verification done with rdis directly; no helper scripts written.

