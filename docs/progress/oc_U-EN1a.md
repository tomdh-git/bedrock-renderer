## NEXT
DONE

GOAL: Close checklist item N1a: "Submit takeover hook at 0xe82e230 (slot 50 stats/timers); replacement walks Frame+0xB4700 draw records (stride 0x80) — BGFX_MAP 8a, 10". All reversing done statically against Minecraft.Windows.exe 1.26.62.01; the build + in-game run are deferred per the 2026-11-22 user decision, so CLOSES? YES (no unknown RVA/offset/meaning remains).

VERIFIED (static, rdis on 1.26.62.01; every verbatim line copied from a listing and re-checked with verify_oc):
- submit entry 0xe82e230 = vtable slot 50 (+0x190 of base vtable 0xF4ED2D0), size 0x4d91 [V: d3d12_vtable data + `0xe82e230  push rbp`].
- RTX subclass vtable 0xF4EEE80 overrides slot 50 at 0xe83d440 and calls base 0xe82e230 at `0xe83d4d6  call 0xE82E230` [V], so detouring 0xe82e230 covers every submit entry path [8a].
- submit signature: rcx = RendererContext*, rdx = Frame*; rdx saved at `0xe82e26c  mov [rbp+0x16A8],rdx`, recovered `0xe82e345  mov rsi,[rbp+0x16A8]`, used as Frame* `0xe82e34c  mov r9d,[rsi+0xE746D8]` [V].
- renderer-state fast path: `0xe82e273  cmp dword ptr [rcx+0x19F88],5` / `0xe82e27a  jl 0xE832CEE` — state < 5 skips [V]; command-list wrapper null-check `0xe82e283  cmp qword ptr [rcx+0x2D8],0` [V].
- stats/timers inline: `0xe82e332  call 0xEBDB740` (QPC) [V]; frame begin 0xe81d660 at `0xe82e367  call 0xE81D660` [V].
- Frame contract [V in submit's body / executor consuming the same Frame]:
  - item count `0xe8306af  movsxd rcx,[rax+0xDC57E8]` (cap 0xFFFE per Frame.h)
  - sort keys `0xe8306bf  lea r8,[rax+0x14700]`, view field `0xe8306cd  shr rdx,0x36` (key>>54)
  - per-item u16 `0xe8306d4  movzx r10d,word ptr [rax+rdx*2]`
  - 0x80 stride scale `0xe82e67d  shl r14d,7` (inside submit)
  - draw-header base `0xe821853  lea r8,[rax+0xB4700]` / `0xe82185a  mov [rbx+0x590],r8` (executor, same Frame contract)
  - index×0x80 `0xe82241c  shl edx,7` / `0xe82241f  mov r8,[rbx+0x590]` / `0xe822426  mov rax,[r8+rdx]`
  - state byte `0xe8223cd  cmp byte ptr [r8+0x23],0` / `0xe8223d2  je 0xE822480` (header+0x20 u64 state, byte +0x23 tested)

| offset/rva | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| 0xe82e230 | 0x4d91 | entry (vtable 0xF4ED2D0 slot 50 +0x190) | `0xe82e230  push rbp` | RendererContextD3D12::submit entry; RTX override 0xe83d440 wraps base, calls base at `0xe83d4d6  call 0xE82E230` | [V] |
| [rbp+0x16A8] | 8 | Frame* arg (rdx) saved + recovered | `0xe82e26c  mov [rbp+0x16A8],rdx` ; `0xe82e345  mov rsi,[rbp+0x16A8]` | rdx = Frame* stored to stack local, then rsi = Frame* reloaded for Frame-field reads | [V] |
| 0x19F88 | 4 | RendererContext+0x19F88 u32 | `0xe82e273  cmp dword ptr [rcx+0x19F88],5` ; `0xe82e27a  jl 0xE832CEE` | renderer state skip: state < 5 skips submit work | [V] |
| 0x2D8 | 8 | RendererContext+0x2D8 qword | `0xe82e283  cmp qword ptr [rcx+0x2D8],0` | command-list wrapper null-check | [V] |
| Frame+0xDC5808 | 8 | Frame+0xDC5808 {u32 w, u32 h} | `0xe82e28d  add rdx,0xDC5808` | backbuffer size | [V] |
| call 0xEBDB740 | 8 | QPC timestamp call inside submit | `0xe82e332  call 0xEBDB740` | stats/timer read (QPC), stored [rbp+0x15D8] | [V] |
| Frame+0xE746D8 | 4 | Frame+0xE746D8 u32 | `0xe82e34c  mov r9d,[rsi+0xE746D8]` | frame counter, +1 per frame | [V] |
| RendererContext+0x19F58 | 8 | RendererContext+0x19F58 ptr | `0xe82e353  mov rdx,[rdi+0x19F58]` | resource-table ptr -> guarded paged heap arrays | [V] |
| Frame+0xDC57F0 | 4 | Frame+0xDC57F0 u32 | `0xe82e372  cmp dword ptr [rsi+0xDC57F0],0` | transient index-buffer size [I] | [I] |
| Frame+0xDC57F8 | 8 | Frame+0xDC57F8 ptr | `0xe82e37f  mov rsi,[rsi+0xDC57F8]` | transient index-buffer pointer [I] | [I] |
| Frame+0xDC57F4 | 4 | Frame+0xDC57F4 u32 | `0xe82e570  cmp dword ptr [rax+0xDC57F4],0` | transient vertex-buffer size [I] | [I] |
| Frame+0xDC5800 | 8 | Frame+0xDC5800 ptr | `0xe82e57d  mov rsi,[rax+0xDC5800]` | transient vertex-buffer pointer [I] | [I] |
| Frame+0xDC57E8 | 4 | Frame+0xDC57E8 u32 | `0xe8306af  movsxd rcx,[rax+0xDC57E8]` | draw/item count, CAS-allocated, cap 0xFFFE | [V] |
| Frame+0x14700 | 8 | Frame+0x14700 u64[] | `0xe8306bf  lea r8,[rax+0x14700]` | sort keys; view field = bits 54..61 | [V] |
| key>>54 | 8->1 | sort-key view field | `0xe8306cd  shr rdx,0x36` | viewId = key >> 54 | [V] |
| Frame+viewId*2 | 2 | Frame+0x94700 u16[] | `0xe8306d4  movzx r10d,word ptr [rax+rdx*2]` | per-item u16 sorted index | [V] |
| shl r14d,7 | 2->0x80 | stride scale inside submit | `0xe82e67d  shl r14d,7` | index*0x80 for draw-header walk | [V] |
| Frame+0xB4700 | 0x80 | Frame+0xB4700 RenderDrawHeader[] | `0xe821853  lea r8,[rax+0xB4700]` ; `0xe82185a  mov [rbx+0x590],r8` | draw-header base, stride 0x80 (executor consumes same Frame) | [V] |
| index*0x80 | 2->0x80 | Frame+0x94700 -> header | `0xe82241c  shl edx,7` ; `0xe82241f  mov r8,[rbx+0x590]` ; `0xe822426  mov rax,[r8+rdx]` | item loop indexes header base + (index<<7) | [V] |
| header+0x23 | 1 | header+0x20 u64 state (byte +0x23) | `0xe8223cd  cmp byte ptr [r8+0x23],0` ; `0xe8223d2  je 0xE822480` | executor tests state byte at header+0x23 | [V] |

Per-draw header fields from the section-0 example (program +0x38, startIdx +0x40, indexCnt +0x44, ibHandle +0x74, vbHandle +0x76, state +0x20, bind mask +0x63) are pinned by static_asserts in src/sdk/mc/deps/bgfx/Frame.h (RenderDraw, kSize=0x80) and match the executor-verified lines above; the remaining field meanings are [I] in BGFX_MAP 8a where no instruction shows them.

CHANGES ON DISK (this unit only; every path is docs/ or src/client/features/render/ or src/sdk/):
- NEW docs/progress/oc_U-EN1a.md — this note (the unit's output file).
- src/client/features/render/rewrite/RewriteSubmit.h — takeover seam header: kSubmitRva=0xe82e230, slot 50, size 0x4d91, Fn signature (rcx=RendererContext*, rdx=Frame*, r8/r9 helpers), Frame contract constants (FrameOffsets::kItemCount=0xDC57E8, kSortKeys=0x14700, kSortedItems=0x94700, kDrawHeaders=0xB4700 stride 0x80, kState=0x20, kStreamMask=0x63), DrawVetoPolicy::verdict prototype, takeover() declaration, registry entry declaration (mode Off by default).
- src/client/features/render/rewrite/RewriteSubmit.cpp — detour that walks Frame+0xB4700 headers stride 0x80 (Frame+0xDC57E8 count, Frame+0x94700 sorted u16 list), per-draw DrawVetoPolicy::verdict (state bit 62 => Veto -> zero header+0x63 streamMask so executor skips; Rewrite = record-only), QPC-timed walk with relaxed-atomic stats (sDrawsWalked/sDrawNs/sFrames/sDrawsVetoed/sDrawsRewritten), forwards to original via RewriteRegistry trampoline, fail fast (no null guards, no SEH), registered mode Off (nothing installs without a mode switch + build).
- src/sdk/Sigs.json — append-only: deps.bgfx.RendererContextD3D12.submit sig already present at line 159 (proven unique prologue, 0xe82e230). No existing entry touched.
- src/sdk/mc/deps/bgfx/Frame.h — already carries all Frame/draw-header offsets used above (kDrawHeaders=0xB4700, kItemCount=0xDC57E8, kSortKeys=0x14700, kSortedItems=0x94700, kState=0x20, kStreamMask=0x63, kSize=0x80, kFrameCounter=0xE746D8, kBackbufferSize=0xDC5808) with static_asserts; no edit needed by this unit.

CLOSES?: YES — every part of the item line is on disk and [V]-proven: submit hook target 0xe82e230 (slot 50, stats/timers inline), replacement walks Frame+0xB4700 draw records stride 0x80 (Frame+0xDC57E8 count, Frame+0x94700 sorted list, kSize=0x80, shl ...7 scale), BGFX_MAP 8a/10 seam documented, code follows CLAUDE.md (fail fast, no null guards/SEH), includes + Sigs.json registration present where editable, and the build + one in-game test are deferred per the 2026-11-22 user decision (not a reason for CLOSES? NO). No unknown RVA/offset/meaning remains.

A section for this item is appended to docs/BIGBANG_TESTS.md (item id, what to enable, exact in-game steps, expected observable result).

## TOOL REQUESTS
- rdis `imm 0xb4700` returned 0 hits although `lea r8,[rax+0xB4700]` exists at 0xe821853 (verified by `dis`): the `imm` command does not match lea displacements; I used `dis` listings instead. If `imm` is intended to cover lea displacements, fixing it would let later units scan constant footprints without dumping whole functions.
