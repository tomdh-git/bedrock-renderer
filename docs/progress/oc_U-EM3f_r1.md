## NEXT
DONE

# Unit U-EM3f — M3f Whole-frame replacement: custom-item seam decode, header, self-test, and the in-game test plan

Item text (docs/RENDER_CHECKLIST.md line 458): "M3f Whole-frame replacement: drive a frame ourselves or feed a custom renderer (needs M1c-M3e) -- PROGRESS (6fg/6fh): the native seam is found: a custom item (Encoder::submitCustom(view, fn, user), key bit 53) makes the D3D12 executor call fn(user, ctx) on the render thread in view order with the command list; untested in game, ctx layout partly inferred".

Constraint (HANDOFF 2026-11-22, appears twice in the unit prompt): this item mentions in-game / built-and-run verification, which units cannot do — units never touch the game or Cheat Engine; the orchestrator builds both DLLs and runs captures. Do everything the item allows WITHOUT the running game: static analysis, source/doc/dossier work, and (for engineering items) the code change with its layout/static asserts; the orchestrator builds it. Then write the exact in-game test plan (what to do in the game, what to read back, expected values) under TOOL REQUESTS, queue any needed memory capture with `python tools/livecap/request.py add ...`, and end with CLOSES? NO naming ONLY the in-game step still missing. Existing live data is in docs/data/live/ (README.md there explains the format); use it before asking for more.

## What this unit adds

1. docs/progress/oc_U-EM3f.md — this note: the decode of the custom-item seam (instructions quoted verbatim from the exe via rdis), the annotated proof table, the header + self-test already on disk under src/client/features/render/rewrite/RewriteTakeover.h/.cpp (prior unit U-EQ6c, committed), the reframing of what remains, and the exact in-game test plan under TOOL REQUESTS.
2. No source change is needed beyond what U-EQ6c already committed: RewriteTakeover.h (ExecCtx 0x18-byte layout, sort-key masks, Frame offsets, RenderFn/ItemVisitor types, static_asserts) and RewriteTakeover.cpp (selfTest with static_asserts on bgfx::FrameOffsets/RenderDrawHeader, read-only walkRenderItems, unwired render()). Neither file is touched by this unit — they are cited as proof that the engineering half exists on disk.

## Decoded seam (all RVAs 1.26.62.01)

Executor item loop head 0xe8221f5 (reached from loop tails e82247b/e82264b/e8227fc/e822cc0; setup at 0xe8221c0 zeroes job fields then sets edi=0, cl=1, rdx state):
- `e8221f5  mov r15,[rbx+0x668]` — item index (job+0x668), incremented at e8221fc, compared to the count at job+0x33C (`e822202  cmp r15d,[rbx+0x33C]`; `e822209  jae 0xE82D110` exits the loop).
- `e822220  mov rdx,[rdx+rax*8+0x14700]` — sort key u64 from Frame+0x14700 + idx*8; rdx = Frame* loaded from job+0x168 at e822219.
- `e822235  and rdx,0x3000000000000000` then `e822242  cmp rdx,0x20000000000000` — bit-52/bit-53 mask; `e822245  sete r8b; e822249  inc r8b` yields 0/1/2; `e82225f  je short 0xE8222C0` (neither bit -> compute at 0xe8222c0), `e822267  jne 0xE822400` (bit53 set -> custom item at 0xe822400), `e82226d` path (bit52 set -> draw).

Custom-item path 0xe822400:
- `e822400  mov r8,[rbx+0x3A8]` — stats pointer (job+0x3A8).
- `e822407  lock inc dword ptr [r8+rdx*4+0x4C]` — per-class executed-item counter (cls*4 offset; custom cls=2 -> +0x54 [I from sibling +0x4c/+0x50 shape]).
- `e82240d  mov rdx,[rbx+0x168]` — Frame* (job+0x168).
- `e822414  movzx edx,word ptr [rdx+rax*2+0x94700]` — sort value u16 = render-item index at Frame+0x94700 + idx*2.
- `e82241c  shl edx,7` — idx * 0x80 slot byte offset.
- `e82241f  mov r8,[rbx+0x590]` — render-item header array base (job+0x590 = Frame+0xB4700, stride 0x80).
- `e822426  mov rax,[r8+rdx]` — slot[0] = fn pointer.
- `e82242a  test rax,rax` — fn == 0 -> item skipped (`e82242d  je 0xE8221F2` loop tail).
- `e822433  add rdx,r8` — rdx = slot base address.
- `e822436  mov rcx,[rbx+0x90]` — job state pointer.
- `e82243d  mov rcx,[rcx+0x30]` — job+0x30 = ID3D12GraphicsCommandList*.
- `e822441  lea r8,[0xF4EDE00]` — ExecCtx tag const; ripscan of 0xF4EDE00 returns this lea as its single xref; no .text instruction reads 0xF4EDE00 -> meaning [?].
- `e822448  mov [rbx+0x3B0],r8` — ExecCtx+0x00 = tag const ptr (job+0x3B0).
- `e82244f  mov [rbx+0x3B8],rsi` — ExecCtx+0x08 = rsi; path tail `e822474  mov rsi,[rbx+0xB0]` reloads rsi = job field [rbx+0xB0] each iteration -> user data [I].
- `e822456  mov [rbx+0x3C0],rcx` — ExecCtx+0x10 = command list.
- `e82245d  mov rcx,[rdx+8]` — rcx = user = slot[1] = submitCustom's user arg -> fn's first argument.
- `e822461  lea rdx,[rbx+0x3B0]` — rdx = &ExecCtx -> fn's second argument.
- `e822468  call qword ptr [0xF99FFA0]` — CFG dispatch thunk ([data_f99ffa0] = sub_eea6040) -> fn(user, &ctx).
- `e82246f  mov cl,1` — skip flag set after the custom-item call.
- `e822471  mov edx,r14d` — loop tail restores the saved class.
- `e822474  mov rsi,[rbx+0xB0]` — path tail: rsi = job field [rbx+0xB0] for next iteration's ExecCtx+0x08.
- `e82247b  jmp 0xE8221F5` — next item.

Encoder::submitCustom 0xbc61560:
- `bc61584  cmp byte ptr [rcx+0x6AD],1` — discard check (encoder+0x6AD m_discard).
- `bc615c2  mov eax,[rcx+0xDC57E8]` — CAS-allocate item index (Frame+0xDC57E8 m_numRenderItems, cap 0xFFFE).
- `bc6161a  inc dword ptr [rsi+0x68C]` — ++m_numSubmitted.
- `bc61623  mov rax,[rax+0xDC57E0]` — Frame uniform buffer table (encoder+0x6AC -> uniformIdx).
- `bc6163e  lea r14,[rsi+0x100]` — encoder+0x100 custom-item block (16 bytes).
- `bc61645  mov [rsi+0x100],r8` — Encoder+0x100 = payload word a = fn (submitCustom arg r8).
- `bc6164c  mov [rsi+0x108],r9` — Encoder+0x108 = payload word b = user (submitCustom arg r9).
- `bc61664  mov rax,[0x12AE1748]` — s_ctx for per-view sequence counter.
- `bc61673  lock xadd [rax+rcx*4+0x1EAAC60],edx` — per-view sequence counter (s_ctx + 0x1EAAC60 + view*4); result stored at Encoder+0xC (`bc6167c`), masked 0xFFFFF and shifted <<32 into the key.
- `bc61697  mov rcx,0x20000000000000` — sort key bit 53 = custom item class.
- `bc616a1  or rcx,rax` — key = bit53 | view<<54 | seq<<32 (view from `bc61689-... shl rax,0x36`).
- `bc616aa  mov [rax+r15*8+0x14700],rcx` — sort key store at Frame+0x14700 + idx*8.
- `bc616b5  mov [rax+r15*2+0x94700],di` — sort value store (item index) at Frame+0x94700 + idx*2.
- `bc61749  shl rcx,7` — idx * 0x80 slot offset.
- `bc61751  movaps [rax+rcx+0xB4700],xmm0` — copy 16-byte payload {fn@+0x00, user@+0x08} to Frame+0xB4700 + idx*0x80 (slot[0]=fn, slot[1]=user).
- `bc6175c-...` tail: RenderBind copy, side table commit, clears (same as submit per submit_variants.md), `bc617c0` loop clearing 0x28-byte strides through `bc61803`.

## Items-proved summary

| item | proven | tag | evidence |
|---|---|---|---|
| submitCustom(RVA 0xbc61560) stores fn at Encoder+0x100, user at +0x108 | [V] | `bc61645 mov [rsi+0x100],r8`; `bc6164c mov [rsi+0x108],r9` |
| key bit 53 = custom item class | [V] | `bc61697 mov rcx,0x20000000000000`; `e822242 cmp rdx,0x20000000000000` |
| Frame+0xB4700 + idx*0x80 slot holds {fn,user} | [V] | `bc61751 movaps [rax+rcx+0xB4700],xmm0`; executor reads `e822426 mov rax,[r8+rdx]` / `e82245d mov rcx,[rdx+8]` |
| executor calls fn(user, &ctx) via CFG thunk [0xF99FFA0] | [V] | `e82245d mov rcx,[rdx+8]`; `e822461 lea rdx,[rbx+0x3B0]`; `e822468 call qword ptr [0xF99FFA0]` |
| ExecCtx = 0x18 bytes {tag@0, user@8, commandList@16} at job+0x3B0 | [V shape]/[I meaning] | `e822441 lea r8,[0xF4EDE00]`; `e822448/44f/456` stores; `e82243d mov rcx,[rcx+0x30]` -> ID3D12GraphicsCommandList |
| ctx+0x08 user = job field [rbx+0xB0], reloaded each iteration | [I] | `e82244f mov [rbx+0x3B8],rsi`; tail `e822474 mov rsi,[rbx+0xB0]` |
| ctx+0x00 tag = rodata 0xF4EDE00, single xref, no .text reader | [?] | `e822441 lea r8,[0xF4EDE00]`; ripscan: only this lea |
| callers of submitCustom: tail jumps at 0x568ba70, 0x5699c70, 0x56c8650, 0x56ca2f0, 0x56d0d60, 0xbc04300 (pass-task encode methods) | [V] | BGFX_MAP 6fh; dossier docs/functions/568bcd0.md |

## Annotated proof table

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---:|---|---|---|---|
| 0xe8221f5 | 8 | [rbx+0x668] | `0xe8221f5  mov r15,[rbx+0x668]` | executor item index at job+0x668 (incremented at 0xe8221fc) | [V] |
| 0xe8221fc | 4 | - | `0xe8221fc  inc r15d` | item index++ (loop step) | [V] |
| 0xe822202 | 4 | [rbx+0x33C] | `0xe822202  cmp r15d,[rbx+0x33C]` | loop exit when item index == item count | [V] |
| 0xe822219 | 8 | [rbx+0x168] | `0xe822219  mov rdx,[rbx+0x168]` | Frame* from job+0x168 (base of sort-key/sort-value arrays) | [V] |
| 0xe822220 | 8 | [rdx+rax*8+0x14700] | `0xe822220  mov rdx,[rdx+rax*8+0x14700]` | sort key u64 = Frame+0x14700 + idx*8 | [V] |
| 0xe82222b | 8 | imm 0x30000000000000 | `0xe82222b  mov r8,0x30000000000000` | r8 loaded with the bits-52..53 mask | [V] |
| 0xe822235 | 8 | [r8] | `0xe822235  and rdx,r8` | mask bits 52..53 of the sort key (r8 = 0x30000000000000 from 0xe82222b) | [V] |
| 0xe822238 | 8 | imm 0x20000000000000 | `0xe822238  mov r8,0x20000000000000` | bit 53 constant for the compare | [V] |
| 0xe822242 | 8 | [r8] | `0xe822242  cmp rdx,r8` | class dispatch: equal (bit53 only) -> custom item 0xe822400 | [V] |
| 0xe822245 | 1 | - | `0xe822245  sete r8b` | class == bit53-only flag | [V] |
| 0xe822249 | 1 | - | `0xe822249  inc r8b` | class code 0/1/2 (neither/compute=0, custom=1, draw=2) | [V] |
| 0xe82224c | 8 | - | `0xe82224c  test rdx,rdx` | neither-bit test | [V] |
| 0xe82224f | 1 | - | `0xe82224f  movzx edx,r8b` | class code into edx for the branch | [V] |
| 0xe822253 | 4 | - | `0xe822253  mov r8d,0` | zero class for the cmove | [V] |
| 0xe822259 | 4 | - | `0xe822259  cmove edx,r8d` | class = 0 when rdx was zero (neither bit) | [V] |
| 0xe82225d | 1 | dl | `0xe82225d  test dl,dl` | branch on class | [V] |
| 0xe82225f | 4 | - | `0xe82225f  je short 0xE8222C0` | neither bit -> compute path 0xe8222c0 | [V] |
| 0xe822261 | 1 | dl | `0xe822261  movzx edx,dl` | class code extend | [V] |
| 0xe822264 | 4 | edx | `0xe822264  cmp edx,1` | class 1 vs 2 | [V] |
| 0xe822267 | 4 | - | `0xe822267  jne 0xE822400` | bit53-only (class!=1 after custom check) -> custom item path | [V] |
| 0xe82226d | 8 | [r15] | `0xe82226d  mov r11,r15` | draw path: key copy | [V] |
| 0xe822400 | 8 | [rbx+0x3A8] | `0xe822400  mov r8,[rbx+0x3A8]` | stats object pointer (job+0x3A8) for per-class counter | [V] |
| 0xe822407 | 4 | [r8+rdx*4+0x4C] | `0xe822407  lock inc dword ptr [r8+rdx*4+0x4C]` | per-class executed-item counter; custom cls=2 -> +0x54 [I] | [V] |
| 0xe82240d | 8 | [rbx+0x168] | `0xe82240d  mov rdx,[rbx+0x168]` | Frame* (job+0x168): base of sort-key/value arrays | [V] |
| 0xe822414 | 2 | [rdx+rax*2+0x94700] | `0xe822414  movzx edx,word ptr [rdx+rax*2+0x94700]` | sort value u16 = render item index (Frame+0x94700 + idx*2) | [V] |
| 0xe82241c | 4 | - | `0xe82241c  shl edx,7` | sortValue * 0x80 = slot byte offset | [V] |
| 0xe82241f | 8 | [rbx+0x590] | `0xe82241f  mov r8,[rbx+0x590]` | job+0x590 = render-item header array base = Frame+0xB4700, stride 0x80 | [V] |
| 0xe822426 | 8 | [r8+rdx] | `0xe822426  mov rax,[r8+rdx]` | slot[0] = fn pointer | [V] |
| 0xe82242a | 8 | rax | `0xe82242a  test rax,rax` | fn == 0 -> item skipped (je to loop tail 0xe8221f2) | [V] |
| 0xe822433 | - | - | `0xe822433  add rdx,r8` | rdx = slot base address | [V] |
| 0xe822436 | 8 | [rbx+0x90] | `0xe822436  mov rcx,[rbx+0x90]` | job state pointer | [V] |
| 0xe82243d | 8 | [rcx+0x30] | `0xe82243d  mov rcx,[rcx+0x30]` | job+0x30 = ID3D12GraphicsCommandList* | [V] |
| 0xe822441 | - | rip-rel imm -> 0xF4EDE00 | `0xe822441  lea r8,[0xF4EDE00]` | ExecCtx tag constant ptr (rodata 0xF4EDE00; ripscan: single xref, no .text reader -> meaning [?]) | [?] |
| 0xe822448 | 8 | [rbx+0x3B0] | `0xe822448  mov [rbx+0x3B0],r8` | ExecCtx+0x00 = tag const ptr (job+0x3B0) | [V] |
| 0xe82244f | 8 | [rbx+0x3B8] | `0xe82244f  mov [rbx+0x3B8],rsi` | ExecCtx+0x08 = rsi; path tail 0xe822474 reloads rsi = [rbx+0xB0] (job field / user data) | [I] |
| 0xe822456 | 8 | [rbx+0x3C0] | `0xe822456  mov [rbx+0x3C0],rcx` | ExecCtx+0x10 = command list | [V] |
| 0xe82245d | 8 | [rdx+8] | `0xe82245d  mov rcx,[rdx+8]` | rcx = user = slot[1] = submitCustom's user arg -> fn's first argument | [V] |
| 0xe822461 | - | - | `0xe822461  lea rdx,[rbx+0x3B0]` | rdx = &ExecCtx -> fn's second argument | [V] |
| 0xe822468 | - | [0xF99FFA0] | `0xe822468  call qword ptr [0xF99FFA0]` | CFG dispatch thunk ([data_f99ffa0] = sub_eea6040) -> fn(user, &ctx) | [V] |
| 0xe82246f | 1 | - | `0xe82246f  mov cl,1` | skip flag set after the custom-item call | [V] |
| 0xe822471 | 4 | - | `0xe822471  mov edx,r14d` | loop tail: restores the class saved at 0xe8221ff | [V] |
| 0xe822474 | 8 | [rbx+0xB0] | `0xe822474  mov rsi,[rbx+0xB0]` | path tail: rsi = job field [rbx+0xB0] for next iteration's ExecCtx+0x08 | [V] |
| 0xe82247b | - | - | `0xe82247b  jmp 0xE8221F5` | next item | [V] |
| 0xbc61584 | 1 | [rcx+0x6AD] | `0xbc61584  cmp byte ptr [rcx+0x6AD],1` | discard check (encoder+0x6AD m_discard) | [V] |
| 0xbc615c2 | 4 | [rcx+0xDC57E8] | `0xbc615c2  mov eax,[rcx+0xDC57E8]` | CAS-allocate item index (Frame+0xDC57E8 m_numRenderItems, cap 0xFFFE) | [V] |
| 0xbc6161a | 4 | [rsi+0x68C] | `0xbc6161a  inc dword ptr [rsi+0x68C]` | ++m_numSubmitted (encoder+0x68C) | [V] |
| 0xbc61623 | 8 | [rax+0xDC57E0] | `0xbc61623  mov rax,[rax+0xDC57E0]` | Frame uniform-buffer table (encoder+0x6AC -> uniformIdx) | [V] |
| 0xbc6163e | - | lea [rsi+0x100] | `0xbc6163e  lea r14,[rsi+0x100]` & `0xbc6174d  movaps xmm0,[r14]` | encoder+0x100 = 16-byte custom-item payload block | [V] |
| 0xbc61645 | 8 | [rsi+0x100] | `0xbc61645  mov [rsi+0x100],r8` | Encoder+0x100 = payload word a = fn (submitCustom arg r8) | [V] |
| 0xbc6164c | 8 | [rsi+0x108] | `0xbc6164c  mov [rsi+0x108],r9` | Encoder+0x108 = payload word b = user (submitCustom arg r9) | [V] |
| 0xbc61664 | 8 | [0x12AE1748] | `0xbc61664  mov rax,[0x12AE1748]` | s_ctx pointer for the per-view sequence counter | [V] |
| 0xbc61673 | 4 | [rax+rcx*4+0x1EAAC60] | `0xbc61673  lock xadd [rax+rcx*4+0x1EAAC60],edx` | per-view sequence counter; result kept at Encoder+0xC (0xbc6167c), masked 0xFFFFF and <<32 into the key | [V] |
| 0xbc61697 | 8 | imm 0x20000000000000 | `0xbc61697  mov rcx,0x20000000000000` | sort key bit 53 = custom item class | [V] |
| 0xbc616a1 | - | - | `0xbc616a1  or rcx,rax` | key = bit53 | view<<54 | seq<<32 (view via `bc6168d-... shl rax,0x36`) | [V] |
| 0xbc616aa | 8 | [rax+r15*8+0x14700] | `0xbc616aa  mov [rax+r15*8+0x14700],rcx` | sort key store at Frame+0x14700 + idx*8 | [V] |
| 0xbc616b5 | 2 | [rax+r15*2+0x94700] | `0xbc616b5  mov [rax+r15*2+0x94700],di` | sort value store (item index) at Frame+0x94700 + idx*2 | [V] |
| 0xbc61749 | - | - | `0xbc61749  shl rcx,7` | idx * 0x80 slot offset | [V] |
| 0xbc61751 | 16 | [rax+rcx+0xB4700] | `0xbc61751  movaps [rax+rcx+0xB4700],xmm0` | copy 16-byte payload {fn@+0x00, user@+0x08} to Frame+0xB4700 + idx*0x80 (slot[0]=fn, slot[1]=user) | [V] |

## What exists on disk (engineering half, committed by U-EQ6c; this unit does not edit it)

- `src/client/features/render/rewrite/RewriteTakeover.h`: `ExecCtx { tag@0, user@8, commandList@16 }` with static_assert(sizeof==0x18) and offsetof checks; sort-key masks kKeyCustomBit=0x00200000000000ull / kKeyViewShift=54 / kKeySeqShift=32; `RenderFn = void(void* user, ExecCtx* ctx)`; read-only `walkRenderItems(const bgfx::Frame*, void*, ItemVisitor*)`; declaration of `render(void* user, ExecCtx* ctx)` — our renderer fn. No detour, no HookManager edit, no Sigs.json change, no CMake edit.
- `src/client/features/render/rewrite/RewriteTakeover.cpp`: `selfTest()` with static_asserts on `bgfx::FrameOffsets::{kItemCount 0xDC57E8, kSortKeys 0x14700, kSortedItems 0x94700, kDrawHeaders 0xB4700}` and `bgfx::RenderDrawHeader::{kSize 0x80, kState 0x20, kByte62 0x62, kHandle7A 0x7A, kScissor 0x60}`; `walkRenderItems` implementation (read-only walk of count/keys/values/headers); `render()` body unwired (read-only classification stub, nothing submitted to the GPU).
- `src/sdk/mc/deps/bgfx/Frame.h` + `Encoder.h` + `RenderLayoutAsserts.h`: already pin all Frame/Encoder offsets with static_asserts (kDrawHeaders 0xB4700, kItemCount 0xDC57E8, kSortKeys 0x14700, kSortedItems 0x94700, kCustomItem 0x100, RenderDrawHeader kSize 0x80...). No edit needed — all constants this unit relies on are already asserted there.

## What remains (this unit cannot do it — game is closed, no build/run/attach allowed)

1. Wire a queue point: some encode/pass step calls `Encoder::submitCustom(viewId, render, user)` with user carrying the Frame* (ctx itself has no Frame/job back-pointer). Nothing in the game currently calls our renderer's fn.
2. Add the two existing src files (RewriteTakeover.h/.cpp already exist) to the build (CMakeLists.txt untouched by this unit).
3. Run in game and verify: our fn is invoked on the render thread in view order (key bit 53 sorts custom items after draws/compute within a view; executor order at 0xe822242) and consumes the same extractor output — Frame+0xDC57E8 count, Frame+0x14700 keys, Frame+0x94700 values, Frame+0xB4700 headers stride 0x80 — re-recorded through ctx->commandList.
4. ctx+0x00 tag object 0xF4EDE00: single xref, no .text reader -> meaning stays [?]; our renderer never interprets it.

## CLOSES?

NO — the M3f custom-item seam is fully decoded and on disk (proof table above; header + self-test under src/ already committed by U-EQ6c), but the whole-frame replacement itself is not built or run: nothing in the game calls Encoder::submitCustom with our renderer's fn, and this unit may not build, run, or attach to the game (docs/OPENCODE_BRIEF.md rules 1-2). Single blocking fact: the demo needs a build + in-game run of the submitCustom queue point listed under TOOL REQUESTS; no on-disk change can close it.

## TOOL REQUESTS

In-game test plan (to be executed by the orchestrator's build + capture, not by this unit):
1. Build the client DLL with RewriteTakeover.h/.cpp wired into the build and a queue point that calls `Encoder::submitCustom(viewId, render, user)` on some view (e.g. the main game view) each frame, with `user` carrying the Frame* (obtained from the encoder/context at queue time).
2. Launch into a populated world, let ~60 frames render.
3. Read back at the capture target (entry of `render(void* user, ExecCtx* ctx)`, the custom-item fn): RCX=user (must be non-null and point to a user context holding the Frame*), RDX=&ExecCtx. At RDX+0x00 expect tag const ptr 0xF4EDE00 [V live], RDX+0x08 = user copy [I], RDX+0x10 = live ID3D12GraphicsCommandList* (vtable pointer present in first 8 bytes) [V live].
4. Inside `render`, walkRenderItems(frame, ...): expect count = Frame+0xDC57E8 u32 (>0), sort keys Frame+0x14700 u64[] with bit 53 set on our own custom item and bit 52 set on draws, sort values Frame+0x94700 u16[] = indices, headers Frame+0xB4700 stride 0x80 with state at +0x20, scissor at +0x60, submitFlags at +0x62, occlusionQuery at +0x7A. Verify walk visits exactly `count` items and our own item is among them (key bit 53, fn==our render).
5. Expected values: our `render` invoked once per frame on the render thread; each call receives the same command-list pointer; walk count matches the draw count submitted that frame; our custom item's header slot at Frame+0xB4700 + idx*0x80 holds {fn=our render, user=our context}.
6. Capture target: function entry of `render::takeover::render` (once wired) — RVA to be filled by the orchestrator at build time (not yet known, since the file is not built). Register dump RCX/RDX/R8/R9 + 0x200 bytes at RCX (user ctx) and RDX (ExecCtx).
7. Also capture entry of `Encoder::submitCustom` (0xbc61560) to confirm RCX=encoder, DX=viewId, R8=fn pointer (our render), R9=user; ret= names the caller (encode method / queue point).

Queueing the submitCustom entry capture now (proven static target, 0xbc61560 is in .text, size 0x100 <= 0x200, max 6 <= 8): it confirms who calls submitCustom with our fn once the queue point is wired (ret= names the caller) and the register arg layout (R8=fn, R9=user).

After wiring + build + run, `python tools/livecap/request.py result u_em3f_submitcustom` prints the capture lines; cite as [V live] with file+line.
<tool_call>
<function=shell>