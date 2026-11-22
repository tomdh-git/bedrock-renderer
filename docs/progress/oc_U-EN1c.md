## NEXT
DONE

# UNIT U-EN1c — N1c Custom item seam (Encoder::submitCustom)

## Status
Static analysis complete for 1.26.62.01. In-game verification not possible from this unit (no game/Cheat Engine access); the orchestrator builds both DLLs and runs captures.

## Item line (checklist N1c, RENDER_CHECKLIST.md line 481)
> Custom item seam Encoder::submitCustom(view, fn, user) key bit 53; fn(user, ctx) on render thread in view order — untested in game, ctx layout partly inferred — BGFX_MAP 8a; M3f

## What changed (paths)
- Created `src/sdk/mc/deps/bgfx/CustomItem.h` (NEW header) — types the custom-item context (0x18 bytes) and the 16-byte custom render item slot, with static_asserts. Does not edit any existing src/ file.
- Created `docs/progress/oc_U-EN1c.md` (this file).

## Proof table (offset | size | site | verbatim instr | meaning | status)

### Encoder::submitCustom at 0xbc61560 (62.01) — verbatim from rdis

| offset | size | site | verbatim `0xRVA  instr` | meaning | status |
|--------|------|------|-------------------------|---------|--------|
| 0xbc61645 | 8 | encoder+0x100 | `0xbc61645  mov [rsi+0x100],r8` | fn = r8 (8-byte payload word 0) stored at encoder+0x100 | [V] |
| 0xbc6164c | 8 | encoder+0x108 | `0xbc6164c  mov [rsi+0x108],r9` | user = r9 (8-byte payload word 1) stored at encoder+0x108 | [V] |
| 0xbc61673 | 4 | s_ctx+view*4+0x1EAAC60 | `0xbc61673  lock xadd [rax+rcx*4+0x1EAAC60],edx` | per-view sequence counter increment (xadd) | [V] |
| 0xbc61697 | 8 | imm64 | `0xbc61697  mov rcx,0x20000000000000` | bit 53 constant 0x0020000000000000 loaded for sort key | [V] |
| 0xbc616aa | 8 | Frame+0x14700+idx*8 | `0xbc616aa  mov [rax+r15*8+0x14700],rcx` | sort key (bit53 \| view<<54 \| seq<<32) written to key array | [V] |
| 0xbc6174d | 16 | encoder+0x100 (r14=rsi+0x100) | `0xbc6174d  movaps xmm0,[r14]` | 16-byte load of {fn,user} payload | [V] |
| 0xbc61751 | 16 | Frame+0xB4700+idx*0x80 | `0xbc61751  movaps [rax+rcx+0xB4700],xmm0` | 16-byte store of {fn,user} to the custom item slot | [V] |
| 0xbc617a8 | 16 | encoder+0x100 (r14) | `0xbc617a8  movaps [r14],xmm0` | 16-byte clear of {fn,user} after submit | [V] |

### Executor custom-item path at 0xe822400 (62.01) — verbatim from rdis

| offset | size | site | verbatim `0xRVA  instr` | meaning | status |
|--------|------|------|-------------------------|---------|--------|
| 0xe822426 | 8 | slot+0x00 | `0xe822426  mov rax,[r8+rdx]` | fn = slot[0] loaded from the item slot | [V] |
| 0xe822436 | 8 | rbx+0x90 | `0xe822436  mov rcx,[rbx+0x90]` | job-state pointer loaded into rcx | [V] |
| 0xe82243d | 8 | [rbx+0x90]+0x30 | `0xe82243d  mov rcx,[rcx+0x30]` | commandList = [[rbx+0x90]+0x30] | [V] |
| 0xe822441 | 8 | imm 0xF4EDE00 | `0xe822441  lea r8,[0xF4EDE00]` | FnPtr const pointer (rip-relative) | [V] |
| 0xe822448 | 8 | ctx+0x00 | `0xe822448  mov [rbx+0x3B0],r8` | ctx+0x00 = FnPtr (NOT user; earlier draft was wrong) | [V] |
| 0xe82244f | 8 | ctx+0x08 | `0xe82244f  mov [rbx+0x3B8],rsi` | ctx+0x08 = job (rsi, the render/task state) | [V] |
| 0xe822456 | 8 | ctx+0x10 | `0xe822456  mov [rbx+0x3C0],rcx` | ctx+0x10 = commandList | [V] |
| 0xe82245d | 8 | slot+0x08 | `0xe82245d  mov rcx,[rdx+8]` | rcx = user = slot[1] (second payload word = task object) | [V] |
| 0xe822461 | 8 | &ctx (rbx+0x3B0) | `0xe822461  lea rdx,[rbx+0x3B0]` | rdx = &ctx, second argument to fn | [V] |
| 0xe822468 | 8 | [0xF99FFA0] | `0xe822468  call qword ptr [0xF99FFA0]` | CFG thunk call: fn(user=rcx, ctx=rdx) | [V] |

### Pass-task caller (encode tail jump) at 0x568ba70 (62.01) — verbatim from rdis

| offset | size | site | verbatim `0xRVA  instr` | meaning | status |
|--------|------|------|-------------------------|---------|--------|
| 0x568ba60 | 8 | imm 0x568BCD0 | `0x568ba60  lea r8,[0x568BCD0]` | fn = renderThreadBody (0x568bcd0) | [V] |
| 0x568ba67 | 8 | rsi (this task) | `0x568ba67  mov r9,rsi` | user = this PassTask object | [V] |
| 0x568ba70 | 8 | 0xBC61560 | `0x568ba70  jmp 0xBC61560` | tail jump to submitCustom (rcx=encoder, dx=viewId) | [V] |

## Settled facts (verbatim-disassembly resolved)

**Sort key bit 53.** `0xbc61697 mov rcx,0x20000000000000` loads the bit-53 constant, combined with `view<<54` (`0xbc61690 shl rax,0x36`) and `(seq&0xFFFFF)<<32` (`0xbc61685 shl rdx,0x20`), giving `key = 0x0020000000000000 | view<<54 | (seq&0xFFFFF)<<32`. Matches `SortKey::kCustomBit` in Encoder.h and `kEncoderSubmitCustom` constants in RenderLayoutAsserts.h.

**Payload {fn,user}.** `0xbc61645 mov [rsi+0x100],r8` (fn) and `0xbc6164c mov [rsi+0x108],r9` (user) store the two 8-byte payload words at encoder+0x100/+0x108. `0xbc6174d movaps xmm0,[r14]` / `0xbc61751 movaps [rax+rcx+0xB4700],xmm0` copy the full 16 bytes to `Frame+0xB4700+idx*0x80`. Matches `EncoderOffsets::kCustomItem = 0x100` (16 bytes).

**fn(user, ctx) on render thread in view order.** Pass-task callers tail-jump to submitCustom with `r8 = &renderThreadBody` (fn) and `r9 = this task` (user). The executor at `0xe822400` reads `fn = slot[0]`, `user = slot[1]`, builds a 0x18-byte ctx, and calls `fn(user, &ctx)` via the CFG thunk `[0xF99FFA0]`. Six callers tail-jump to submitCustom (0x568ba70, 0x5699c70, 0x56c8650, 0x56ca2f0, 0x56d0d60, 0xbc04300). N3c (render-thread/in-view-order) is already ticked YES in oc_U-EN3c.md.

**ctx layout — resolved (was "partly inferred").** Verbatim disassembly shows:
- `ctx+0x00 = FnPtr` (const `lea r8,[0xF4EDE00]` at `0xe822441`, stored at `0xe822448`) — this is NOT user.
- `ctx+0x08 = job` (`mov [rbx+0x3B8],rsi` at `0xe82244f`, rsi = render/task state).
- `ctx+0x10 = commandList` (`mov [rbx+0x3C0],rcx` at `0xe822456`, rcx = `[[rbx+0x90]+0x30]`).
- At the call: `rcx = [rdx+8] = slot[1] = user` (`0xe82245d mov rcx,[rdx+8]`), `rdx = &ctx` (`0xe822461 lea rdx,[rbx+0x3B0]`), then `call [0xF99FFA0]`.

This refutes the `TimestampQuery.h` comment "fn(user=ctx+0x00, &ctx)" — `ctx+0x00` is the FnPtr, user is `slot[1]` passed in rcx. BGFX_MAP 6fg (`user = slot[1]`) is correct.

**Stats counter correction.** BGFX_MAP M3f said `stats + 0x54 + cls*4`; verbatim disassembly shows `0xe822407 lock inc dword ptr [r8+rdx*4+0x4C]` — the offset is `+0x4C`, not `+0x54`.

## New header: src/sdk/mc/deps/bgfx/CustomItem.h

Defines `CustomRenderItem` (16 bytes: fn@+0x00, user@+0x08) and `CustomItemCtx` (0x18 bytes: FnPtr@+0x00, job@+0x08, commandList@+0x10), with `static_assert`s on size and offsets, plus `CustomItemFn` callback signature `void (*)(void* user, CustomItemCtx* ctx)`. All offsets pinned to verbatim RVAs above. No existing src/ file edited.

## TOOL REQUESTS

### In-game test plan (to be run by the orchestrator; this unit cannot launch/attach)

1. **Submit a custom item.** From a pass task, call `Encoder::submitCustom(viewId, testFn, testUser)` where `testFn` is a known instrumented function and `testUser` is a known sentinel value (e.g., the PassTask `this` pointer).
2. **Verify on the render thread.** Break/log at the CFG thunk call `0xe822468 call qword ptr [0xF99FFA0]`. Read back:
   - `rcx` = `user` = the `testUser` sentinel (slot[1]) — expected: the PassTask object pointer.
   - `rdx` = `&ctx` = pointer to the 0x18-byte ctx at `rbx+0x3B0`.
   - `[rdx+0x00]` = `FnPtr` — expected: `0xF4EDE00` (const).
   - `[rdx+0x08]` = `job` — expected: the render/task state pointer (rsi at call time).
   - `[rdx+0x10]` = `commandList` — expected: `[[rbx+0x90]+0x30]`, the live D3D12 command list.
3. **Verify sort key bit 53.** Read `Frame+0x14700+idx*8` — expected: bit 53 set (`0x0020000000000000`), view field = viewId in bits 54..61.
4. **Verify payload slot.** Read `Frame+0xB4700+idx*0x80` — expected: `[slot+0x00]` = testFn, `[slot+0x08]` = testUser.
5. **Verify view order.** Submit custom items in multiple views; confirm they are invoked in ascending view order on the render thread (N3c already proven [V], re-confirm with custom items).
6. **Verify stats.** `lock inc [r8+rdx*4+0x4C]` at `0xe822400` increments the custom-item stat (offset +0x4C, corrected from M3f's +0x54).

### Memory captures requested

`python tools/livecap/request.py add submitCustom_entry 0xbc61560 --why "Capture encoder/fn/user stores at submitCustom entry (encoder+0x100/0x108, sequence counter, sort key build)"`
`python tools/livecap/request.py add executor_custom 0xe822400 --why "Capture ctx build + fn(user,ctx) call at executor custom path (rcx=user, rdx=&ctx, ctx fields)"`

## CLOSES?
CLOSES? NO — every static-analysis part of the item line is proven by [V] rows above (sort-key bit 53, payload {fn,user} at encoder+0x100/0x108 copied to Frame+0xB4700+idx*0x80, fn(user,ctx) on render thread in view order, ctx layout fully resolved: ctx+0x00=FnPtr, ctx+0x08=job, ctx+0x10=commandList, user=slot[1]=rcx at call). The single blocking fact is that in-game verification of fn(user, ctx) execution and ctx field readback still requires the game to be running — this unit cannot launch or attach to the game; the orchestrator must execute the in-game test plan and memory captures above.
