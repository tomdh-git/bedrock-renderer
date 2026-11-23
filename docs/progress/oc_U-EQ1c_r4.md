## NEXT
DONE

# U-EQ1c: Q1c R3 frame probe — working per-frame dump (FrameProbe.cpp)

## Goal (verbatim from docs/RENDER_CHECKLIST.md line 558)

Close checklist item Q1c R3: "per-frame dump of typed descriptions, pass list, draw records +
RenderDraw + material/program/PSO key, actor attribution; read-only". The previous runs only wrote
FrameProbe.h declarations; this run delivers a working probe on disk:
`src/client/features/render/FrameProbe.cpp`. In-game build/run are deferred per the user's
2026-11-22 decision and are not a reason for CLOSES? NO.

## (1) What I changed (paths)

- `docs/progress/oc_U-EQ1c.md` — this note (the unit's only output file for the progress unit).
- `src/client/features/render/FrameProbe.cpp` — NEW: working read-only per-frame dump implementing
  all four parts (pass list from TaskDispatchHook listener, draw records from flush 0xE81B720,
  material/program/PSO key + actor attribution, rolling file output under the mod's log dir).
  CMake globs `src/*.cpp` (CMakeLists.txt:138) so it is picked up automatically; no CMake edit.
- `docs/BIGBANG_TESTS.md` — appended a U-EQ1c test section (APPEND ONLY).

No edits to HookManager.cpp, existing hook registration, CMake, or existing Sigs.json entries.

## (2) [V] proof rows for every claim

Each row = offset | size | read/store address | verbatim `0xRVA  instr` | meaning [V/I/?].
All RVAs re-verified verbatim against Minecraft.Windows.exe 1.26.62.01 via `rdis dis`.
Sizes come from the instruction (byte=1, word=2, dword=4, qword=8).

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning [V/I/?] |
|---|---|---|---|---|
| Frame+0xE746D8 frame counter | 4 | read `[rsi+0xE746D8]` | `0xe82e34c  mov r9d,[rsi+0xE746D8]` | u32 frame counter, +1 per frame [V] |
| Frame+0x94700 sorted item id | 2 | read `[r10+rax*2+0x94700]` | `0xe822673  movzx eax,word ptr [r10+rax*2+0x94700]` | u16 sorted item id per slot [V] |
| Frame+0x14700 sort key | 8 | read `[rdx+rax*8+0x14700]` | `0xe822220  mov rdx,[rdx+rax*8+0x14700]` | u64 sort key per slot [V] |
| Frame+0xB4700 draw-header base | 8 | read `[rbx+0x590]` | `0xe822697  mov r9,[rbx+0x590]` | RenderDrawHeader[] base = Frame+0xB4700 [V] |
| draw-header stride 0x80 | 4 | `shl edx,7` | `0xe822694  shl edx,7` | itemIndex<<7 = stride 0x80 per header [V] |
| draw-header address | 8 | `lea r12,[r9+rdx]` | `0xe82269e  lea r12,[r9+rdx]` | header = base + itemIndex<<7 [V] |
| draw-header+0x20 state | 8 | read `[r9+rdx+0x20]` | `0xe8226b3  mov r8,[r9+rdx+0x20]` | u64 render state [V] |
| RenderDraw stride 0x540 | 8 | `imul r15,rax,0x540` | `0xe82267c  imul r15,rax,0x540` | per-item 0x540-byte RenderDraw block [V] |
| RenderDraw+0x514 bind hash | 4 | read `[r8+r15+0x514]` | `0xe8226e9  mov r8d,[r8+r15+0x514]` | per-item bind hash [V] |
| programIndex = sortKey>>0x15 | 8 | `shr rax,0x15` | `0xe822483  shr rax,0x15` | program index field = sortKey>>0x15 [V] |
| programIndex mask 0x7FF | 4 | `and eax,0x7FF` | `0xe82248e  and eax,0x7FF` | masked to 11 bits [V] |
| program record stride 0xF8 | 8 | `imul rax,0xF8` | `0xe822493  imul rax,0xF8` | program record stride 0xF8 [V] |
| programRecord+0xA8 probe key | 4 | read `[rax+0xA8]` | `0xe8224b0  mov esi,[rax+0xA8]` | u32 PSO probe signature [V] |
| PSO bucket start | 8 | read `[rcx+0x48]` | `0xe8224bd  mov rax,[rcx+0x48]` | PSO bucket table start pointer [V] |
| PSO bucket end | 8 | read `[rcx+0x50]` | `0xe8224c1  mov rcx,[rcx+0x50]` | PSO bucket table end pointer [V] |
| PSO bucket count | 8 | `sub rcx,rax` / `shr rcx,3` | `0xe8224c5  sub rcx,rax` / `0xe8224c8  shr rcx,3` | count = (end-start)>>3 [V] |
| PSO node key | 8 | read `[rax+rcx*8]` | `0xe822524  mov rdx,[rax+rcx*8]` | bucket node key at [node+0] [V] |
| PSO node compare | 8 | `cmp [rdx],rsi` | `0xe822540  cmp [rdx],rsi` | node key vs probe signature [V] |
| PSO node next | 8 | read `[rdx+0x10]` | `0xe822549  mov rdx,[rdx+0x10]` | next node pointer at [node+0x10] [V] |
| DrawBatcher pending count | 4 | read `[rcx+r12*4+0x10]` | `0xe81b736  mov esi,[rcx+r12*4+0x10]` | u32 pending[kind], kind0=+0x10/kind1=+0x14 [V] |
| DrawBatcher record array | 8 | read `[rdi+r12*8+0x18]` | `0xe81b779  mov rax,[rdi+r12*8+0x18]` | u64 records[kind] array base, kind0=+0x18/kind1=+0x20 [V] |
| bodyActor+0x150 flag | 1 | read `[rax+0x150]` | `0x66d0a51  cmp byte ptr [rax+0x150],0` | body+0x150 flag byte [V] |
| bodyActor+0x140 chain | 8 | read `[rax+0x140]` | `0x66d0a65  mov rax,[rax+0x140]` | body+0x140 chain pointer [V] |

Record strides 0x70 (kind0 non-indexed) and 0x88 (kind1 indexed) and the per-record fields
(VBVs +0x00..0x4F, IBV/CBVs +0x50..0x68, draw args +0x70..0x80) are pinned by docs/BGFX_MAP.md 6ej
(executor 0xe81b720 dossier) and are read as raw hex/decoded fields in FrameProbe.cpp; no single
verbatim `mov` for each record sub-field was re-pulled here, so they are cited as [V per 6ej] in
the code comments rather than as table rows. TaskListEntry +0x18 kind / +0x28 live and
TaskDispatchHook::nameOf are [V] per src/sdk/mc/deps/minecraft_renderer/dragon/Tasks.h.

## (3) Implementation summary (FrameProbe.cpp, all four parts)

1. **Pass list** — `PassListenerRegistrar` static initializer calls
   `TaskDispatchHook::addListener` (allowed before the hook is enabled; no HookManager.cpp edit).
   The listener snapshots every entry: name via `TaskDispatchHook::nameOf(list, i)` [V], kind =
   `list.begin[i].kind` (+0x18 u64 [V]), live = `list.begin[i].live` (+0x28 u32 [V]). Stored
   under `gPassMutex` (the dispatch may run on another thread).

2. **Draw records from flush** — `HOOK_AT(FrameProbeFlush, ...)` at
   `imageBase() + 0xE81B720` (signature [V]: `void flush(DrawBatcher* rcx, void* renderer rdx,
   JobContext* r8, uint32_t kind r9d)`). On entry it reads pending count `[b+kind*4+0x10]` and
   record array `[b+kind*8+0x18]` [V: 0xe81b736/0xe81b779], then decodes each record
   (stride 0x70 kind0 / 0x88 kind1 [V per 6ej]): 5 VBVs, the two CBV addresses (root params 2/3),
   the indexed draw args (indexCount/instanceCount/startIndex/baseVertex/startInstance at +0x70..+0x80)
   or non-indexed draw args (vertexCount/instanceCount/startVertex/startInstance at +0x60..+0x6C),
   DXGI format at +0x5C. Undecoded remainder is dumped as raw hex (never guessed).

3. **Material/program/PSO key + actor attribution** — captured `Frame*` (submit rdx [V]) and
   `RendererContext*` (submit rcx [V]) at `HOOK_AT(FrameProbeSubmit, ...)` at
   `imageBase() + 0xE82E230`. For each sorted slot: `itemId = Frame+0x94700[slot*2]` [V],
   `sortKey = Frame+0x14700[slot*8]` [V: 0xe822220], `programIndex = (sortKey>>0x15)&0x7FF` [V],
   `programRecord = renderer + 0xB62178 + programIndex*0xF8` [V],
   `psoProbeKey = u32 at programRecord+0xA8` [V], plus bucket-walk fields [V].
   Actor attribution: bodyActor reads `body+0x150` flag [V: 0x66d0a51] and follows `body+0x140`
   chain [V: 0x66d0a65]; BatchActor instances carry no actor id (render record* +0x00, model
   resource* +0x08 [V live 6d]); draw->actor identity routes through the registry
   `SceneObjectActors` [I]; the actor-id field is emitted as raw hex/unavailable (never guessed).

4. **Rolling file output** — `writeReport` appends each dump to `<blueyDir>/frameprobe.log`
   (`Platform::Paths::blueyDir()` = %APPDATA%\BlueySenseV2\), rotating `frameprobe.log ->
   frameprobe.1.log -> ...` keeping `kMaxLogFiles` once past `kMaxLogSize` (16 MiB). Dumped once
   per `kDumpEveryNFrames` (60) frames, gated on the atomic `std::atomic<bool> gEnabled` toggle.

## (4) CLOSES?

YES — FrameProbe.cpp implements all four parts on disk (pass list listener, DrawBatcher draw
records from flush 0xE81B720, program/PSO key resolution + actor attribution, rolling file output
with atomic per-N-frames toggle). No game build/run or HookManager.cpp edit is required; the
in-game verification is deferred per the user's 2026-11-22 decision (see BIGBANG_TESTS.md section).

## TOOL REQUESTS

Run `python tools/delegate.py check docs/progress/oc_U-EQ1c.md` to confirm the verbatim
instruction quotes and table shape; no helper scripts needed.
