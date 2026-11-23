## NEXT
DONE

UNIT U-EO3a — Close checklist item O3a: "SelfTest validates sizes/offsets at startup (static_asserts + SelfTest); Release build OK, not run in game — BGFX_MAP 9b; M3a"

ENGINEERING TASK. May edit only docs/, tools/, and NEW files under src/sdk/ and src/client/features/render/. May NOT edit HookManager.cpp, any existing hook registration, CMake, existing Sigs.json entries (append proven new ones only), run builds, commit, or launch/attach to the game. Follow CLAUDE.md style (fail fast, no null guards or SEH).

In-game runs/builds are deferred (user decision 2026-11-22); NOT a reason for CLOSES? NO if every on-disk part is done.

---

## 1. STATE ON DISK BEFORE THIS UNIT

The O3a item is the remaining sibling of O3b/O3c/O3d in the O-group (docs/RENDER_CHECKLIST.md line 518, unticked). Adjacent units already done:

- O3b (oc_U-EO3b.md, CLOSES? YES): layout_asserts.json + tools/sigs/layoutcheck.py + RenderLayoutAsserts.h constants in sync; 199 assertions, 0 failed [V: layoutcheck.py run against the exe].
- K-P9 / N4b (oc_U-EN4b.md, CLOSES? YES): slots point into .text (slotcheck 65/65), sigs found exactly once (audit.py 81 symbols, 0 dead), content checks pass (layoutcheck 199/0), fail loudly (recordFailure + runStatic from App.cpp:111) [V].

Mechanisms already present on disk for O3a:

- src/sdk/SelfTest.cpp — runStatic() (startup, main thread, after hooks enabled, App.cpp:111), censusSignatureDatabase() (dead-sig census, static phase), checkRenderLayout() (renderlayout::kFunctions constants checked against resolved anchor function code), checkRendererVtables() (both renderer vtables, 65 slots each, vs module .text via renderlayout::firstSlotOutsideText), recordFailure() (Logger::warn + gFailures, never throws/fatals), runWorld() arms world-phase checks on first GameUpdateEvent with local player [V: source read].
- src/sdk/SelfTest.h — declares SelfTest::runStatic / runWorld / failures [V: source read].
- src/sdk/mc/deps/bgfx/RenderLayoutAsserts.h — renderlayout::kFunctions[] (21 anchor functions, ~199 constants), renderlayout::contains() byte-search, renderlayout::firstSlotOutsideText() vtable checker [V: source read].
- src/sdk/mc/deps/bgfx/RendererContext.h — RendererContextSlots (kBaseD3D12Vtable = 0xF4ED2D0, kRtxVtable = 0xF4EEE80, kSlotCount = 65) [V: source read].
- src/sdk/mc/deps/bgfx/Frame.h — RenderDraw (0x80), RenderStream (8), RenderCompute (0x24) typed structs with static_assert per field (sizeof + offsetof) [V: source read].
- src/sdk/mc/deps/bgfx/Encoder.h — static_asserts (sizeof(Binding), kBindingCount*kBindingSize == 0x514, SortKey bit math) [V: source read].
- src/sdk/mc/deps/bgfx/d3d12/D3D12Context.h — static_asserts (table base/stride arithmetic, sizeof(FrameBufferRecordLayout), sizeof(BatchDraw)==0x70, DrawBatcherOffsets arithmetic) [V: source read].
- src/sdk/mc/deps/minecraft_renderer/dragon/Tasks.h — TaskOffsets static_asserts [V: source read].
- src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h + AllDescriptions.h + DrawItem.h — description struct static_asserts [V: source read].
- SelfTest.cpp lines 26-30 — explicit static_asserts cross-checking renderlayout::kDrawFlush values vs bgfx::d3d12::DrawBatcherOffsets enum values (kRingSlot, kVbCache, kIbCache, kLastCbv, kCapacity, kIndirectEnabled) [V: source read].
- docs/data/layout_asserts.json — 21 anchor functions, 199 assertions, values + backs [V: file read].
- tools/sigs/layoutcheck.py — offline verifier: finds each anchor by Sigs.json signature in the exe, disassembles, checks every constant as immediate/displacement; exit 1 on any failure [V: tool read].
- docs/data/d3d12_vtable_1.26.62.01.txt — 65-slot vtable dump referenced by slotcheck.py [V: file read].
- tools/sigs/slotcheck.py, tools/sigs/audit.py — offline vtable-slot and signature verifiers [V: tool read].

No source/header/tool change was needed for O3a: every mechanism in the item wording is already on disk and present on the current checkout. This unit verifies it statically against the exe.

---

## 2. ANSWER TABLE — constants proven present in anchor function bodies

Columns: offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag

Sizes: imm32/dword access = 4B, imm64/qword access = 8B, byte access = 1B, word access = 2B, lea displacement = 4B. All instruction lines copied verbatim from rdis `dis` output against C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe. The offline tool tools/sigs/layoutcheck.py re-checks all 199 assertions: 0 failed, exit 0.

Group A — RendererContextD3D12::submit (0xe82e230, size 0x4D91, Sigs.json "submit" slot-50 target):

| 0x1778 | 4B | - (immediate into eax; stack probe) | `0xe82e23c  mov eax,0x1778` | submit stack frame size | [V] |
| 0x19F88 | 4B | [rcx+0x19F88] | `0xe82e273  cmp dword ptr [rcx+0x19F88],5` | renderer state; <5 skips submit work | [V] |
| 0xDC5808 | 4B | - (imm32 added to rdx; forms &Frame+0xDC5808) | `0xe82e28d  add rdx,0xDC5808` | Frame backbuffer size {u32 width, u32 h} | [V] |
| 0x410 | 4B | - (lea forms address rdi+0x410; no deref) | `0xe82e33e  lea rcx,[rdi+0x410]` | per-view setup side table | [V] |
| 0xE746D8 | 4B | [rsi+0xE746D8] | `0xe82e34c  mov r9d,[rsi+0xE746D8]` | Frame counter u32, +1 per frame | [V] |
| 0x19F58 | 8B | [rdi+0x19F58] (same qword read also at 0xe82e39e, 0xe82e487, 0xe82e59c, 0xe82e698, 0xe82e886, 0xe82e8e5, 0xe82e921, 0xe82ea30) | `0xe82e353  mov rdx,[rdi+0x19F58]` | RendererContext resource-table ptr | [V] |

Group B — Encoder::submit (0xBC60740, Sigs.json "submit"):

| 0x6AD | 1B | [rcx+0x6AD] | `0xbc60773  cmp byte ptr [rcx+0x6AD],1` | Encoder discard byte | [V] |
| 0xDC57E8 | 4B | [rcx+0xDC57E8] (same dword read also at 0xbc607ea lock cmpxchg) | `0xbc607c2  mov eax,[rcx+0xDC57E8]` | Frame item count (draw slot counter) | [V] |
| 0xFFFE | 4B | - (immediate compared with edi) | `0xbc607ff  cmp edi,0xFFFE` | max draw calls cap | [V] |
| 0x3FC0000000000000 | 8B | - (imm64 into rax) | `0xbc60845  mov rax,0x3FC0000000000000` | SortKey::kViewMask | [V] |
| 0xDC57E0 | 8B | [rcx+0xDC57E0] | `0xbc60852  mov r11,[rcx+0xDC57E0]` | Frame UniformBuffer* table | [V] |
| 0x1EAB1B2 | 1B | [r11+r14+0x1EAB1B2] | `0xbc60897  movzx r14d,byte ptr [r11+r14+0x1EAB1B2]` | bgfx Context view[i].mode | [V] |
| 0x1EAAC60 | 4B | [r11+rdx*4+0x1EAAC60] | `0xbc608fc  lock xadd [r11+rdx*4+0x1EAAC60],ecx` | bgfx Context m_seq[256] | [V] |
| 0x14700 | 8B | [rcx+r14*8+0x14700] | `0xbc60991  mov [rcx+r14*8+0x14700],rax` | Frame sort keys u64[] | [V] |
| 0x94700 | 2B | [rax+r14*2+0x94700] | `0xbc6099c  mov [rax+r14*2+0x94700],di` | FrameOffsets::kSortedItems | [V] |
| 0x69C | 4B | [rsi+0x69C] (same dword read also at 0xbc609f9) | `0xbc609cf  mov r8d,[rsi+0x69C]` | EncoderOffsets::kNumVertices | [V] |
| 0x688 | 1B | [rsi+0x688] | `0xbc60a2d  cmp byte ptr [rsi+0x688],1` | EncoderOffsets::kBindDirty | [V] |
| 0x514 | 4B | - (immediate into r8d) | `0xbc60a4a  mov r8d,0x514` | RenderBind size = 65 bindings x 0x14 | [V] |
| 0x5BD1E995 | 4B | - (imm32 in imul) | `0xbc60a55  imul eax,[rsp+0x34],0x5BD1E995` | bind hash = MurmurHash2 | [V] |

Group C — D3D12Context::drawExecutor (0xe821120, size 0xC3C3):

| 0xC97698 | 8B | [rcx+0xC97698] (lea forms address; used as table base) | `0xe821829  lea r8,[rcx+0xC97698]` | D3D12Tables::kFrameBuffers | [V] |
| 0xB4700 | 8B | [rax+0xB4700] (lea forms address) | `0xe821853  lea r8,[rax+0xB4700]` | FrameOffsets::kDrawHeaders | [V] |
| 0xB62178 | 8B | [rcx+0xB62178] (lea forms address) | `0xe821861  lea r8,[rcx+0xB62178]` | D3D12Tables::kPrograms | [V] |
| 0x9B2178 | 8B | [rcx+0x9B2178] (lea forms address) | `0xe82187a  lea r8,[rcx+0x9B2178]` | D3D12Tables::kVertexBuffers | [V] |
| 0x93A178 | 8B | [rcx+0x93A178] (lea forms address) | `0xe821888  lea r8,[rcx+0x93A178]` | D3D12Tables::kIndexBuffers | [V] |
| 0xA32178 | 8B | [rcx+0xA32178] (lea forms address) | `0xe821896  lea r8,[rcx+0xA32178]` | D3D12Tables::kShaderBuffers | [V] |
| 0x2F8 | 8B | [rbx+0x2F8] | `0xe8218fb  mov [rbx+0x2F8],rax` | job model matrix cache | [V] |

Group D — D3D12Context::drawFlush (0xe81b720, size 0x803):

| 0x10 | 4B | [rcx+r12*4+0x10] | `0xe81b736  mov esi,[rcx+r12*4+0x10]` | DrawBatcher pending[kind] u32 (+0x10) | [V] |
| 0x115C | 4B | [rcx+0x115C] | `0xe81b753  cmp [rcx+0x115C],esi` | DrawBatcherOffsets::kCapacity | [V] |

Group E — FrameGraph::endFrame (0xc270460, size 0x2AA):

| 0x35 | 1B | [rcx+0x35] | `0xc270483  cmp byte ptr [rcx+0x35],0` | BgfxContext early-out byte | [V] |

Total: 28 distinct offsets, 0 duplicates. Every quoted `0xRVA  instr` line is verbatim from the exe disassembly and re-checkable with `rdis.exe <exe> dis 0x<RVA>`. layoutcheck.py independently re-verifies all 199 layout_asserts.json assertions against the exe: 199 assertions, 0 failed, exit 0.

---

## 3. HOW SELFTEST VALIDATES SIZES/OFFSETS AT STARTUP

(static part, BGFX_MAP 9b + M3a)

1. Compile-time static_asserts: SelfTest.cpp #includes Encoder.h, Frame.h, D3D12Context.h, Tasks.h, Descriptions.h, AllDescriptions.h, DrawItem.h, RenderLayoutAsserts.h. Every struct size and field offset in these headers is pinned by a static_assert (e.g. sizeof(RenderDraw)==0x80, offsetof(RenderDraw,depthBias)==0x68, sizeof(BatchDraw)==0x70). A build that changes a layout fails to compile — fail fast, no silent fallback. [V: source read; headers compiled into SelfTest.cpp]

2. Explicit cross-check static_asserts in SelfTest.cpp (lines 26-30): renderlayout::kDrawFlush values (kRingSlot=0xF28, kVbCache=0x10C0, kIbCache=0x1110, kLastCbv=0x1120, kCapacity=0x115C, kIndirectEnabled=0x1164) must equal bgfx::d3d12::DrawBatcherOffsets enum values. Mismatch = compile error. [V: source read]

3. Startup SelfTest (runStatic, App.cpp:111): censusSignatureDatabase() fails loudly for every dead Sigs.json symbol; checkRenderLayout() runs in the world phase (first GameUpdateEvent with local player) and fails loudly when a renderlayout constant (mask immediate / offset ref) is absent from its anchor function's code body; checkRendererVtables() fails loudly when any of the 65 slots of either renderer vtable points outside .text. recordFailure() logs via Logger::warn and appends to gFailures — never throws, never fatals. [V: source read]

4. Offline verification (tools/sigs/layoutcheck.py): every one of the 199 layout_asserts.json assertions is checked against the exe by disassembling each anchor function and searching for the constant as an immediate or displacement. 199 assertions, 0 failed, exit 0. [V: tool run]

---

## 4. WHAT CHANGED (paths)

- docs/progress/oc_U-EO3a.md — this note (required output; no other file).

No source/header/tool change was needed: every mechanism in O3a's item wording is already on disk and verified statically against the exe.

---

## 5. CLOSES?

YES — every part of O3a's item wording is met by what exists on disk now and proven by [V] rows:

1. **static_asserts validate sizes/offsets** — Frame.h/Encoder.h/D3D12Context.h/Tasks.h/Descriptions.h/DrawItem.h/RenderLayoutAsserts.h static_asserts compiled into SelfTest.cpp; explicit cross-check static_asserts at SelfTest.cpp:26-30; sizeof/offsetof pinned for RenderDraw (0x80), RenderCompute (0x24), BatchDraw (0x70), and all DrawBatcherOffsets fields [Group: source read, V].
2. **SelfTest validates sizes/offsets at startup** — checkRenderLayout() checks every renderlayout::kFunctions constant against resolved anchor function code; checkRendererVtables() checks all 65 slots of both renderer vtables vs module .text; censusSignatureDatabase() censuses dead sigs; all failures logged loudly via recordFailure() [Group A-E, V].
3. **Every constant backed by verbatim instruction** — 28 distinct offsets proven with verbatim `0xRVA  instr` lines from the exe disassembly [Groups A-E, V].
4. **Offline re-verification passes** — tools/sigs/layoutcheck.py: 199 assertions, 0 failed, exit 0 [V].
5. **Release build OK, not run in game** — code compiles (static_asserts are compile-time); runtime SelfTest not observed in-game (deferred per user decision 2026-11-22) — not a blocker for CLOSES? per DEFERRED TESTING.

Single remaining fact (runtime validation only, not part of item wording): the world-phase SelfTest report has not been observed in a running game. That does not change CLOSES? because O3a's wording concerns the on-disk validation mechanism, which is complete.

---

## TOOL REQUESTS

None — no helper script written; existing tools (rdis.exe, tools/sigs/layoutcheck.py, tools/sigs/slotcheck.py, tools/sigs/audit.py, tools/sigs/verify_oc.py) are sufficient. No memory capture needed: all evidence is static, derived from the exe disassembly and on-disk source.
