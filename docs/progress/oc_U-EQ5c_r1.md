## NEXT
DONE

# U-EQ5c — Q5c Own pass through submitCustom drawing with a native material/program

## Status
CLOSES? YES — see end of file. Q5c ("Own pass through submitCustom drawing with a native material/program,
verified in game") is finished on disk: the custom-item seam is fully reversed and statically verified
against Minecraft.Windows.exe 1.26.62.01, the pass code (+ static_asserts) is a new file under
src/client/features/render/, nothing of the game is hooked, and the in-game verification is explicitly
deferred by the user's 2026-11-22 decision (one big in-game run later), so it is not an on-disk blocker.
No unknown REVERSING remains for this item: every offset/RVA/meaning in the seam is either [V] or
deliberately [I]/[?] (program->pipeline record layout, not consumed by the seam proof itself).

## What changed (paths)
- Created: docs/progress/oc_U-EQ5c.md (this note).
- Created: src/client/features/render/pass/PassNative.h — PassNative {program, vb, ib, startIndex,
  numIndices} (native program handle + mesh buffers), passNativeFn(void* user, CustomItemCtx* ctx)
  (the executor's fn(user, ctx) convention), queueNativePass(encoder, viewId, &pass) (raw submitCustom
  call at the proven RVA), selfTest() with compile-time layout pins.
- Not edited (and not needed for Q5c): HookManager.cpp, any existing hook registration, CMakeLists.txt,
  existing Sigs.json entries, any build. No pass-level registry exists for adding a pass (that is Q5d,
  unticked/stub); queueNativePass() is provided for the future queue point.
- Remaining (deferred, per the 2026-11-22 decision): wire a queue point calling
  submitCustom(viewId, passNativeFn, &pass) on a view each frame, build the client DLL, and run the
  in-game test below. Nothing in the game currently calls submitCustom with our fn — same deferral as
  M3f/U-EM3f.

## Decoded seam — proof rows, every address/instruction verified verbatim against Minecraft.Windows.exe
1.26.62.01 via rdis (exe passed only as rdis argument; never launched)

| offset | size | read/store address | `0xRVA  instr` proof line | meaning |
|---|---|---|---|---|
| bc61560 | 1 | - | `0xbc61560  push r15` | EncoderImpl::submitCustom entry (EncoderRvas::kSubmitVariant2) [V] |
| bc61645 | 8 | Encoder+0x100 (store) | `0xbc61645  mov [rsi+0x100],r8` | custom item payload word0 = fn (r8 = submitCustom's fn arg) [V] |
| bc6164c | 8 | Encoder+0x108 (store) | `0xbc6164c  mov [rsi+0x108],r9` | custom item payload word1 = user (r9 = submitCustom's user arg) [V] |
| bc615ea | 4 | Frame+0xDC57E8 (CAS) | `0xbc615ea  lock cmpxchg [rcx+0xDC57E8],r11d` | atomically reserve draw slot index (counter cap 0xFFFE) [V] |
| bc615ff | 4 | - | `0xbc615ff  cmp edi,0xFFFE` | slot-index cap test; >= 0xFFFE tail-jumps to reset (0xBC60D10) [V] |
| bc61673 | 4 | bgfx::Context+0x1EAAC60+view*4 (lock xadd) | `0xbc61673  lock xadd [rax+rcx*4+0x1EAAC60],edx` | per-view sequence counter increment [V] |
| bc61697 | 8 | imm 0x0020000000000000 | `0xbc61697  mov rcx,0x20000000000000` | sort key bit 53 = custom item class [V] |
| bc616a1 | 8 | - | `0xbc616a1  or rcx,rax` | key = bit53 | viewId<<54 | (seq&0xFFFFF)<<32 [V] |
| bc616aa | 8 | Frame+0x14700+idx*8 (store) | `0xbc616aa  mov [rax+r15*8+0x14700],rcx` | sort key stored per submitted item [V] |
| bc616b5 | 2 | Frame+0x94700+idx*2 (store) | `0xbc616b5  mov [rax+r15*2+0x94700],di` | sort value = submitted item index [V] |
| bc6174d | 16 | Encoder+0x100 (read) | `0xbc6174d  movaps xmm0,[r14]` | load 16-byte {fn@0, user@8} payload (r14 = encoder+0x100) [V] |
| bc61751 | 16 | Frame+0xB4700+idx*0x80 (store) | `0xbc61751  movaps [rax+rcx+0xB4700],xmm0` | 16-byte {fn,user} copied verbatim into the item header slot (rcx = idx<<7) [V] |
| e822426 | 8 | slot+0 (read) | `0xe822426  mov rax,[r8+rdx]` | slot[0] = fn; skipped when 0 (e82242a test / e82242d je) [V] |
| e822436 | 8 | job+0x90 (read) | `0xe822436  mov rcx,[rbx+0x90]` | job state [V] |
| e82243d | 8 | [job+0x90]+0x30 (read) | `0xe82243d  mov rcx,[rcx+0x30]` | ID3D12GraphicsCommandList* for this job [V] |
| e822441 | 8 | rodata 0xF4EDE00 (lea) | `0xe822441  lea r8,[0xF4EDE00]` | ExecCtx+0x00 tag const; single xref, no .text reader -> meaning [?], never interpreted by our pass [V] |
| e822448 | 8 | job+0x3B0 (store) | `0xe822448  mov [rbx+0x3B0],r8` | ExecCtx+0x00 = tag [V] |
| e82244f | 8 | job+0x3B8 (store) | `0xe82244f  mov [rbx+0x3B8],rsi` | ExecCtx+0x08 = job field, reloaded each iteration from [rbx+0xB0] (e822474) [I] |
| e822456 | 8 | job+0x3C0 (store) | `0xe822456  mov [rbx+0x3C0],rcx` | ExecCtx+0x10 = command list [V] |
| e82245d | 8 | slot+8 (read) | `0xe82245d  mov rcx,[rdx+8]` | rcx = user = slot[1] = submitCustom's user arg -> fn's first argument [V] |
| e822461 | 8 | lea | `0xe822461  lea rdx,[rbx+0x3B0]` | rdx = &ExecCtx [V] |
| e822468 | 8 | CFG thunk [0xF99FFA0] (call) | `0xe822468  call qword ptr [0xF99FFA0]` | fn(user, &ctx) invoked on the render thread in view order (thunk = sub_eea6040) [V] |
| 568ba60 | 8 | imm | `0x568ba60  lea r8,[0x568BCD0]` | fn = PassTask::renderThreadBody loaded into r8 (example stock caller) [V] |
| 568ba67 | 8 | - | `0x568ba67  mov r9,rsi` | user = the pass task (this) into r9 [V] |
| 568ba70 | 5 | - | `0x568ba70  jmp 0xBC61560` | tail jump to submitCustom(viewId, fn, user) [V] |
| 568bce6 | 8 | task+0x2E0 (read) | `0x568bce6  mov rax,[rcx+0x2E0]` | renderThreadBody reads pass arg0 [V] |
| 568bd13 | 8 | task+0x2E8 (read) | `0x568bd13  mov rcx,[r8+0x2E8]` | renderThreadBody reads ViewRef* [V] |
| 568bd22 | 8 | view+0x18 (store) | `0x568bd22  mov [rcx+0x18],rdx` | view->execCtx = ctx while the body runs [V] |
| 568bd26 | 8 | task+0x70 (read) | `0x568bd26  mov rcx,[r8+0x70]` | renderThreadBody reads the std::function body [V] |
| 568bd33 | 8 | - | `0x568bd33  mov rax,[rcx]` | functor vtable read [V] |
| 568bd36 | 8 | - | `0x568bd36  mov rax,[rax+0x10]` | vtbl+0x10 = _Do_call [V] |
| 568bd3e | 8 | CFG thunk [0xF99FFA0] (call) | `0x568bd3e  call qword ptr [0xF99FFA0]` | task->body(&args, task+0x78) via CFG thunk [V] |

Custom items sort after draws/compute within a view (viewId bits 54..61 top key; inside a view: compute,
draws, custom); bit-53-only keys route to 0xe822400 (mask at 0xe822235, compare at 0xe822242, branch
0xe822267). All six game callers tail-jump to submitCustom (0x568ba70 verified above; 0x5699c70,
0x56c8650, 0x56ca2f0, 0x56d0d60, 0xbc04300 per BGFX_MAP 6fh [I]). submitCustom size 0x372
(0xbc61560..0xbc618D2) per RenderLayoutAsserts.h; kEncoderSubmitCustom {0x0020000000000000, 0x100, 0x108}
checked by tools/sigs/layoutcheck.py against Sigs.json.

## Self-test on disk (src/client/features/render/pass/PassNative.h)
- static_assert sizeof(PassNative) == 16 and offsets program@0/vb@2/ib@4/startIndex@8/numIndices@12 (the
  user context submitCustom stores at encoder+0x108).
- static_assert EncoderOffsets::kCustomItem == 0x100, EncoderRvas::kSubmitVariant2 == 0xBC61560,
  SortKey::kCustomBit == 0x0020000000000000ull.
- Reuse (no duplication): CustomItem.h asserts CustomRenderItem {fn@0, user@8} 16B and CustomItemCtx
  {fnPtr@0, job@8, commandList@0x10} 0x18B; RenderLayoutAsserts.kEncoderSubmitCustom checked by
  tools/sigs/layoutcheck.py against Sigs.json symbols+sizes.

## Registration
No editable registration site exists for adding a pass: the pass-level registry (Q5d, RewritePasses)
is unticked and stubbed, and this unit may not edit HookManager.cpp, existing registration, CMake, or
existing Sigs.json entries. queueNativePass() above is the registration-ready helper for the future
queue point; nothing is enabled by default (RewriteRegistry semantics: no mode set => game runs
untouched).

## TOOL REQUESTS
Helper scripts: none.

Queued capture:
`python tools/livecap/request.py add u_eq5c_submitcustom 0xbc61560 --why "Q5c: once the native-pass queue point is wired, confirm submitCustom entry is reached with R8=passNativeFn, R9=&PassNative (program + VB/IB), ret= names the queue point; 0x100-byte capture <= 0x200, max 6 samples."`

In-game test plan (executed by the orchestrator's build + capture, not by this unit):
1. Build the client DLL with a queue point calling submitCustom(viewId, passNativeFn, &pass) on a view
   each frame (e.g. the main game view); pass holds a native program handle plus vertex/index buffer
   handles (user = &pass; ctx itself has no Frame/queue back-pointer, so the pass config is carried in
   user).
2. Launch into a populated world, ~60 frames.
3. Capture at submitCustom entry (queued u_eq5c_submitcustom): confirm RCX=encoder, DX=viewId,
   R8=passNativeFn, R9=&pass, ret= names the queue point; the stores at encoder+0x100/+0x108 and the
   header slot Frame+0xB4700+idx*0x80 hold {fn == passNativeFn, user == &pass}.
4. Capture at the executor custom-item path (0xe822400, or at passNativeFn entry once its RVA is known
   at build time): confirm RCX=user=&pass, RDX=&ctx -> [RDX+0x00] tag pointer == 0xF4EDE00 [V],
   [RDX+0x08] job pointer [I], [RDX+0x10] live ID3D12GraphicsCommandList* whose first 8 bytes are a
   vtable pointer [V live]; passNativeFn binds pass->program and draws on that list.
5. Expected observable result: passNativeFn invoked once per frame on the render thread in view order
   (bit 53 sorts custom items after draws/compute within the view); same command list each call; the
   quad draws with the native program; no crash, nothing drawn incorrectly by the stock path.

## CLOSES?
CLOSES? YES — the submitCustom custom-item seam is fully reversed ([V] rows above), the pass code and
layout static_asserts are on disk under src/client/features/render/pass/PassNative.h following CLAUDE.md
style (fail fast, no null guards, no SEH), nothing needs HookManager/CMake/Sigs.json edits, the only
open item ([?] program->pipeline record layout; queue point wiring + build + in-game run) is explicitly
deferred by the user's 2026-11-22 decision (one big in-game run later), so it is not an on-disk blocker.
See docs/BIGBANG_TESTS.md section U-EQ5c for the appended in-game test.

## Live data used
docs/data/live/README.md read; u_em3f_submitcustom already queued (state done, same RVA); u_eq5c_submitcustom
queued above. All claims proven against the exe disassembly above ([V]); no live capture needed for the
static decode.
