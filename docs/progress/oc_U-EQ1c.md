## NEXT
DONE

# U-EQ1c: Q1c R3 frame probe — working per-frame dump (FrameProbe.cpp)

Goal (from the unit): a working read-only per-frame probe on disk implementing the four parts of Q1c R3:
(1) pass list from a TaskDispatchHook listener (name via TaskDispatchHook::nameOf, kind, live flag) registered from a static initializer in FrameProbe.cpp (no HookManager.cpp edit; TaskDispatchHook::addListener is allowed before the hook is enabled),
(2) draw records from the DrawBatcher at flush 0xe81b720 (counts [b+0x10]/[b+0x14], record arrays [b+0x18]/[b+0x20], strides 0x70 non-indexed / 0x88 indexed) with record fields decoded,
(3) material/program/PSO key and actor attribution from headers/structs on disk — only offsets proven [V] are decoded by name, everything else is dumped as raw hex, never guessed,
(4) output to a rolling file under the mod's log dir once per N frames, toggle via an atomic flag.
CLAUDE.md style: fail fast, no null guards, no SEH. Each field cites its [V] source in a comment. No game launch/attach, no build, no commit; CMake globs src/*.cpp so the new file is picked up automatically.

## (1) What I changed (paths)

- `docs/progress/oc_U-EQ1c.md` — this note (the unit's only output file for the progress unit).
- `src/client/features/render/FrameProbe.cpp` — NEW: working read-only per-frame dump implementing all four parts (pass list from TaskDispatchHook listener, draw records from flush 0xE81B720, material/program/PSO key + actor attribution, rolling file output under the mod's log dir). CMake globs `src/*.cpp` (CMakeLists.txt:138) so it is picked up automatically; no CMake edit.
- `docs/BIGBANG_TESTS.md` — appended a U-EQ1c test section (APPEND ONLY).

No edits to HookManager.cpp, any existing hook registration, CMake, or existing Sigs.json entries.

## (2) [V] proof rows for every claim

Each row = offset | size | read/store address | verbatim `0xRVA  instr` | meaning [V/I/?]. All RVAs re-verified verbatim against Minecraft.Windows.exe 1.26.62.01 via `rdis dis`. Sizes come from the instruction (byte=1, word=2, dword=4, qword=8).

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning [V/I/?] |
|---|---|---|---|---|
| Frame+0xE746D8 frame counter | 4 | read `[rsi+0xE746D8]` | `0xe82e34c  mov r9d,[rsi+0xE746D8]` | u32 frame counter, +1 per frame [V] |
| RendererContext+0x19F88 renderer state | 4 | read `[rcx+0x19F88]` | `0xe82e273  cmp dword ptr [rcx+0x19F88],5` | renderer state int; <5 skips submit body [V] |
| RendererContext+0x410 | 8 | lea `[rdi+0x410]` | `0xe82e33e  lea rcx,[rdi+0x410]` | bgfx::Context sub-object base +0x410 [V] |
| RendererContext+0x19F58 | 8 | read `[rdi+0x19F58]` | `0xe82e353  mov rdx,[rdi+0x19F58]` | resource-tables pointer [V] |
| RendererContext+0xB62178 | 8 | `add rbx,0xB62178` | `0xe81e8e5  add rbx,0xB62178` | program record table base [V] |
| program record stride | 8 | `imul rax,0xF8` | `0xe822493  imul rax,0xF8` | stride 0xF8 per program record [V] |
| program object signature | 4 | read `[rax+0xA8]` | `0xe8224b0  mov esi,[rax+0xA8]` | u32 PSO-cache probe signature [V] |
| PSO key mask | 8 | `mov rsi,0x707007FFFFFF0FF` | `0xe81e8ec  mov rsi,0x707007FFFFFF0FF` | state mask applied to build the PSO key [V] |
| PSO key apply | 8 | `and rsi,r13` | `0xe81e8f6  and rsi,r13` | key = state & mask [V] |
| sort key -> program index | 8 | `shr rax,0x15` | `0xe822483  shr rax,0x15` | program index field of the sort key [V] |
| program index mask | 4 | `and eax,0x7FF` | `0xe82248e  and eax,0x7FF` | masked to 11 bits [V] |
| sort key -> view/depth tag | 8 | `shr r11,0x25` | `0xe822656  shr r11,0x25` | view/depth-type tag field [V] |
| sort key view tag mask | 4 | `and r11d,0x7FF` | `0xe82265a  and r11d,0x7FF` | view/depth tag masked to 11 bits [V] |
| draw-header base | 8 | read `[rbx+0x590]` | `0xe822697  mov r9,[rbx+0x590]` | local+0x590 = Frame+0xB4700 draw-header array base [V] |
| draw-header stride | 4 | `shl edx,7` | `0xe822694  shl edx,7` | itemIndex<<7 = stride 0x80 per header [V] |
| draw-header address | 8 | `lea r12,[r9+rdx]` | `0xe82269e  lea r12,[r9+rdx]` | header = base + itemIndex<<7 [V] |
| sorted draw items | 2 | read `[r10+rax*2+0x94700]` | `0xe822673  movzx eax,word ptr [r10+rax*2+0x94700]` | u16 sorted item id list at Frame+0x94700 [V] |
| RenderDraw per-item stride | 8 | `imul r15,rax,0x540` | `0xe82267c  imul r15,rax,0x540` | per-item 0x540-byte block stride [V] |
| RenderDraw bind hash | 4 | read `[r8+r15+0x514]` | `0xe8226e9  mov r8d,[r8+r15+0x514]` | per-item block +0x514 u32 bind hash [V] |
| draw-header state word | 8 | read `[r9+rdx+0x20]` | `0xe8226b3  mov r8,[r9+rdx+0x20]` | header+0x20 u64 render state [V] |
| state bit-62 test | 8 | `shr r8,0x3E` | `0xe8226bf  shr r8,0x3E` | header state bit 62 tested [V] |
| draw-header scissor | 2 | read `[r12+0x60]` | `0xe822737  movzx edx,word ptr [r12+0x60]` | header+0x60 u16 scissor rect index [V] |
| draw-header occlusionQuery | 2 | read `[r9+rdx+0x7A]` | `0xe8226c7  movzx edx,word ptr [r9+rdx+0x7A]` | header+0x7A u16 occlusion-query handle [V] |
| DrawBatcher pending[kind] | 4 | read `[rcx+r12*4+0x10]` | `0xe81b736  mov esi,[rcx+r12*4+0x10]` | per-kind pending count at batcher+0x10+kind*4 [V] |
| DrawBatcher pending clear | 4 | write `[rcx+r12*4+0x10]` | `0xe81b74a  mov dword ptr [rcx+r12*4+0x10],0` | count zeroed once consumed [V] |
| DrawBatcher records[kind] | 8 | read `[rdi+r12*8+0x18]` | `0xe81b779  mov rax,[rdi+r12*8+0x18]` / `0xe81b79e  mov r15,[rdi+r12*8+0x18]` | record array base at batcher+0x18+kind*8 [V] |
| rec non-indexed vsConstantsGpuVa | 8 | read `[r15+0x50]` | `0xe81bb19  mov r8,[r15+0x50]` | 0x70 record +0x50 root CBV #2 [V] |
| rec non-indexed fsConstantsGpuVa | 8 | read `[r15+0x58]` | `0xe81ba24  mov r8,[r15+0x58]` | 0x70 record +0x58 root CBV #3 [V] |
| rec non-indexed vertexCount | 4 | read `[r15+0x60]` | `0xe81ba78  mov edx,[r15+0x60]` | 0x70 record +0x60 vertex count [V] |
| rec non-indexed instanceCount | 4 | read `[r15+0x64]` | `0xe81ba7c  mov r8d,[r15+0x64]` | 0x70 record +0x64 instance count [V] |
| rec non-indexed startVertex | 4 | read `[r15+0x68]` | `0xe81ba80  mov r9d,[r15+0x68]` | 0x70 record +0x68 start vertex [V] |
| rec non-indexed startInstance | 4 | read `[r15+0x6C]` | `0xe81ba84  mov r10d,[r15+0x6C]` | 0x70 record +0x6C start instance [V] |
| rec indexed cbv0 write | 8 | write `[rdx+rax+0x60]` | `0xe82cb3d  mov [rdx+rax+0x60],r8` | 0x88 record +0x60 CBV #2 [V] |
| rec indexed cbv1 write | 8 | write `[rdx+rax+0x68]` | `0xe82cb49  mov [rdx+rax+0x68],r8` | 0x88 record +0x68 CBV #3 [V] |
| rec indexed indexCount | 4 | write `[rdi+0x70]` | `0xe82cd11  mov [rdi+0x70],esi` | 0x88 record +0x70 index count [V] |
| rec indexed instanceCount | 4 | write `[rdi+0x74]` | `0xe82cd1e  mov [rdi+0x74],eax` | 0x88 record +0x74 instance count [V] |
| rec indexed startIndex | 4 | write `[rdi+0x78]` | `0xe82cd24  mov [rdi+0x78],eax` | 0x88 record +0x78 start index [V] |
| rec indexed baseVertex/startInstance | 8 | write `[rdi+0x7C]` | `0xe82cd27  mov qword ptr [rdi+0x7C],0` | 0x88 record +0x7C/+0x80 zero [V] |
| rec indexed ibvBufferLocation | 8 | write `[rdx+rax+0x50]` | `0xe82cb52  mov [rdx+rax+0x50],r8` | 0x88 record +0x50 IBV location [V] |
| rec indexed ibvSizeInBytes | 4 | write `[rdx+rax+0x58]` | `0xe82cb5a  mov [rdx+rax+0x58],ecx` | 0x88 record +0x58 IBV size [V] |
| rec indexed ibvFormat select | 4 | `cmp dword ptr [r12+0x48],2` / `mov ecx,0x2A` / `mov r8d,0x39` / `cmove ecx,r8d` | `0xe82cb5e  cmp dword ptr [r12+0x48],2` / `0xe82cb64  mov ecx,0x2A` / `0xe82cb69  mov r8d,0x39` / `0xe82cb6f  cmove ecx,r8d` / `0xe82cb73  mov [rdx+rax+0x5C],ecx` | 0x88 record +0x5C IBV format: 0x39 R16_UINT when header indexStride+0x48 == 2 else 0x2A R32_UINT [V] |
| Item visitor tag | 1 | read `[r8+8]` | `0x66469eb  movzx eax,byte ptr [r8+8]` | variant tag byte at desc+8 [V] |
| Item visitor jump-table base | 8 | `lea rcx,[0xF2BF2D0]` | `0x6646a00  lea rcx,[0xF2BF2D0]` | relative int32 jump table base 0xF2BF2D0 [V] |
| Item visitor jt index load | 8 | read `[rcx+rax*4]` | `0x6646a07  movsxd rax,[rcx+rax*4]` | i32 table entry indexed by tag [V] |
| Item visitor jt jump | 8 | `jmp rax` | `0x6646a0e  jmp rax` | indirect jump to tag handler [V] |
| BatchActor instance count | 8 | read `[r8+0xE0]` | `0x66d9b79  mov rax,[r8+0xE0]` | description+0xE0 u64 instance count [V] |
| bodyActor actor flag | 1 | read `[rax+0x150]` | `0x66d0a51  cmp byte ptr [rax+0x150],0` | bodyActor reads body+0x150 flag byte [V] |
| bodyActor actor chain | 8 | read `[rax+0x140]` | `0x66d0a65  mov rax,[rax+0x140]` | bodyActor follows body+0x140 chain pointer [V] |

Typed descriptions: the Item visitor (0x6646980) dispatches on tag at desc+8 through the int32 table at 0xF2BF2D0 to 11 tag blocks (0..10) [V rows above]; tag 10 forwards to the BatchActor extractor (0x66d9af0). Description field reads documented in BGFX_MAP 6m/6w are [V] at the entry level; per-frame description values live on the caller's stack and are NOT read by this probe (read-only static; live capture deferred).

Pass list: VV builder pass names are inline 8-byte ASCII immediates beside FNV-1 64 hash immediates [V per BGFX_MAP 6p: 0x55f387f `mov rax,0x4320776F64616853` "Shadow C", 0x55ff9a9 `mov rax,0x680E1340911894F3` = FNV-1("GeometryPrepass")]. The listener dumps the live task list (name/kind/live per entry) rather than statically listed names.

Actor attribution: BatchActor instances carry no actor id (instance = {render record*, model resource*, key at resource+0x40} [V live 6d]); the draw header/flush record carry none either. Attribution routes through bodyActor(0x66D0A00) body+0x150 flag + body+0x140 chain [V rows above] pushing one 0xC8 item record per actor [I 6bg], then registry SceneObjectActors [I]. This is printed as a labeled note in every dump, never guessed per-draw.

DrawBatcher kinds and record strides: kind 0 = non-indexed (DrawRecordNonIndexed, stride 0x70) -> DrawInstanced; kind 1 = indexed (DrawRecordIndexed, stride 0x88) -> DrawIndexedInstanced [V per 6ej and DrawRecord.h static_asserts]. Record fields decoded verbatim per DrawRecord.h (rows above); the fields the exe never decodes by name (header +0x00..0x1F stream block, +0x28..0x3F stencil/rgba/uniforms/startMatrix, +0x4C numVertices, +0x5E numMatrices, +0x68..0x73 depth bias block, +0x7C..0x7F padding) are dumped as raw hex blocks.

## (3) CLOSES?
YES

FrameProbe.cpp implements all four parts on disk (pass-list listener via static initializer, DrawBatcher draw-record dump at flush 0xe81b720 with verbatim-decoded fields, program/PSO key resolution and actor attribution using only [V]-proven offsets with raw hex elsewhere, rolling log-file output once per N frames behind an atomic toggle). Per the user's 2026-11-22 deferred-testing decision, builds and in-game runs are not a reason for CLOSES? NO; every on-disk part is done and no RVA, offset, or meaning is unknown. The deferred in-game half (DLL built with FrameProbe.cpp linked in, BS_FRAMEPROBE=1, one populated-world run, inspect frameprobe.log) is specified in docs/BIGBANG_TESTS.md.

## TOOL REQUESTS

Run `python tools/delegate.py check docs/progress/oc_U-EQ1c.md` to confirm the verbatim instruction quotes and table shape (already exit 0); no helper scripts needed.
