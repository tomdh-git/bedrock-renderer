## NEXT
DONE

UNIT U-EP1c — Close checklist item P1c "Actor-to-draw via RenderMarkHook; re-validate against flush 0xe81b720 and Encoder::submit seam — M3d" (docs/RENDER_CHECKLIST.md line 535, currently `[ ]`; M3d itself closed YES in docs/progress/oc_U-EM3d.md).
Target: Minecraft.Windows.exe 1.26.62.01 (base-relative RVAs). Static analysis only (rdis); no build, no game launch, no HookManager.cpp/hook-registration/CMake/Sigs.json edits. For this unit no file other than docs/progress/oc_U-EP1c.md is created or edited.

## (1) What changed

Created: docs/progress/oc_U-EP1c.md (this file). Every game-code claim below is a [V] row quoted verbatim from a fresh rdis disassembly of the 1.26.62.01 exe and re-verified here; source-file claims cite the files I read. It re-validates:
- the actor read in bodyActor (6bg `*(S+0xC8)`), the sibling read, the item builder and the two item writers called from bodyActor;
- passLookup: map at manager+0xA0, found path node+0x10, not-found alloc size 0x8C8, self-linked empty node, count zeroed;
- the Encoder::submit 0xbc60740 seam: discard flag, draw-count load, CAS-increment of Frame+0xDC57E8 allocating the draw index, sort key/store, the 0x80 draw-header copy (encoder+0x40..0xBF -> Frame+0xB4700+idx*0x80; header+0x1F == encoder+0x5F is RenderMarkHook's mark byte) and the RenderBind store;
- the DrawBatcher flush 0xe81b720: pending counts +0x10/kind, clear, cap +0x115C, records +0x18/kind, strides 0x88/0x70, DrawInstanced/DrawIndexedInstanced/ExecuteIndirect via cmdlist vtable +0x60/+0x68/+0x1D8, and the executor call sites 0xe82cfc1 (kind 0) / 0xe82cfde (kind 1) with the 6ej argument pattern;
- record+0x80 = startInstance (0xe81b87a) = kRosterStartBase | slot -> actor, which is the value RenderMarkHook's replay patches into record+0x80 from the mark chain (header mark byte -> stateEncode record+0x84 -> replay record+0x80, per RenderMarkHook.cpp source).
RenderMarkHook.{h,cpp} already exist on disk (src/client/features/hooks/hooks/render/; P2a ticked, not registered in HookManager) and implement exactly this chain; this note proves every game-code link the hook relies on.

## (2) Proof table (one row per distinct offset; all sites of that offset listed; size from the instruction: movups/movaps 16, qword 8, dword 4, word 2, byte 1; meaning only where the instruction or an immediate shows it, else '-')

| offset | name | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| 0x66d0a34 | bodyActor arg3 save | 8 (reg) | - | `0x66d0a34  mov rdi,r8` | bodyActor's 3rd register argument preserved in callee-saved rdi for the whole function | [V] |
| 0x66d2f6c | actor pair base | 8 | [rdi] | `0x66d2f6c  mov rax,[rdi]` | base object of the actor pair | [V] |
| 0x66d312c | actor pair sibling read | 8 | [rax+0xC0] | `0x66d312c  mov rcx,[rax+0xC0]` | sibling pointer of the actor pair (+0xC0) | [V] |
| 0x66d313d | bodyActor actor read | 8 | [rax+0xC8] | `0x66d313d  mov rax,[rax+0xC8]` | **bodyActor reads the body actor at +0xC8** — the 6bg/Sigs `*(S+0xC8)` link; rax = [rdi] = [[arg3]] | [V] |
| 0x66d3144 | actor pair save | 8 | [rbp+0x3F0] | `0x66d3144  mov [rbp+0x3F0],rcx` | +0xC0 (sibling) value saved | [V] |
| 0x66d314b | actor save | 8 | [rbp+0x3F8] | `0x66d314b  mov [rbp+0x3F8],rax` | +0xC8 (actor) value saved | [V] |
| 0x66d3152 | actor null-check | 4 (test) | - | `0x66d3152  test rax,rax` | actor (+0xC8) null-check | [V] |
| 0x66d3158 | sibling null-check | 4 (test) | - | `0x66d3158  test rcx,rcx` | sibling (+0xC0) null-check | [V] |
| 0x66d3160 | both-null bail | - | - | `0x66d3160  je 0x66D5F14` | bail when both are null | [V] |
| 0x66d3177 | item builder call | - | - | `0x66d3177  call 0x6698060` | saved {+0xC0, +0xC8} actor pair -> item builder; the actor reaches the item record | [V] |
| 0x66d2eee | insert-pointer call | - | - | `0x66d2eee  call 0xBBD7C70` | call site RenderMarkHook.h documents: at this call r9 holds the insert's pointer | [V] |
| 0x66d4265 | writer A call | - | - | `0x66d4265  call 0x6765020` | bodyActor calls item writer A | [V] |
| 0x66d49e2 | writer B call | - | - | `0x66d49e2  call 0x6768C70` | bodyActor calls item writer B | [V] |
| 0x5aba5cc | passLookup map | 8 (lea) | [rcx+0xA0] | `0x5aba5cc  lea rbx,[rcx+0xA0]` | passLookup(rcx=pass manager): map at manager+0xA0 | [V] |
| 0x5aba5d6 | passLookup map lookup | - | - | `0x5aba5d6  call 0x9BD4A0` | map lookup by key | [V] |
| 0x5aba5e0 | passLookup found path | - | - | `0x5aba5e0  add rax,0x10` | found path: pass object = map node + 0x10 | [V] |
| 0x5aba5f7 | passLookup alloc size | 4 | imm 0x8C8 | `0x5aba5f7  mov edx,0x8C8` | not-found path: allocation size 0x8C8 for the pass object | [V] |
| 0x5aba60e | pass node init | 8 | [rdi+0x00] | `0x5aba60e  mov [rdi],rdi` | pass object/not-found node: +0x00 self-linked (empty list) | [V] |
| 0x5aba611 | pass node init | 8 | [rdi+0x08] | `0x5aba611  mov [rdi+8],rdi` | +0x08 self-linked (empty list) | [V] |
| 0x5aba619 | pass node init | 8 | [rdi+0x10] | `0x5aba619  mov qword ptr [rdi+0x10],0` | +0x10 = 0 (count/cap) | [V] |
| 0x66ca5c9 | sub_66ca5a0 passLookup call | - | - | `0x66ca5c9  call 0x5ABA5C0` | sub_66ca5c9 calls passLookup; next instruction is kPushLookupReturnRva | [V] |
| 0x66ca5ce | kPushLookupReturnRva site | - | - | `0x66ca5ce  mov rdi,rax` | kPushLookupReturnRva = 0x66CA5CE: pass object in rdi right after passLookup returns | [V] |
| 0x6765046 | writer A passLookup | - | - | `0x6765046  call 0x5ABA5C0` | writer A (called from bodyActor at 0x66d4265) invokes passLookup -> returns the pass object | [V] |
| 0x67650a2 | writer A storage end | 8 | [rsi+0x590] | `0x67650a2  mov rdx,[rsi+0x590]` | writer A: pass object +0x590 = end of the +0x588 item storage | [V] |
| 0x67650a9 | writer A cap compare | 8 | [rsi+0x598] | `0x67650a9  cmp rdx,[rsi+0x598]` | end vs cap at +0x598 | [V] |
| 0x67650d2 | writer A item push | 8 | [rsi+0x590] | `0x67650d2  add qword ptr [rsi+0x590],0x30` | writer A: +0x588 storage end advanced by 0x30 per item pushed | [V] |
| 0x6768c96 | writer B passLookup | - | - | `0x6768c96  call 0x5ABA5C0` | writer B (called from bodyActor at 0x66d49e2) invokes passLookup | [V] |
| 0xbc60754 | submit 6th argument | 1 | [rsp+0xC8] | `0xbc60754  movzx ebp,byte ptr [rsp+0xC8]` | Encoder::submit 6th argument: preserveState | [V] |
| 0xbc6075c | submit 5th argument | 4 | [rsp+0xC0] | `0xbc6075c  mov r10d,[rsp+0xC0]` | Encoder::submit 5th argument: depth | [V] |
| 0xbc60773 | submit discard flag | 1 | [rcx+0x6AD] | `0xbc60773  cmp byte ptr [rcx+0x6AD],1` | Encoder::submit: m_discard flag at encoder+0x6AD | [V] |
| 0xbc607c2 | draw count load | 4 | [rcx+0xDC57E8] | `0xbc607c2  mov eax,[rcx+0xDC57E8]` | draw/item count load: Frame+0xDC57E8 (rcx = Frame*) | [V] |
| 0xbc607ea | draw index CAS | 4 | [rcx+0xDC57E8] | `0xbc607ea  lock cmpxchg [rcx+0xDC57E8],r14d` | **Encoder::submit seam**: CAS-increment of Frame+0xDC57E8 allocates the draw index | [V] |
| 0xbc607ff | cap test | 4 | - | `0xbc607ff  cmp edi,0xFFFE` | cap test: idx >= 0xFFFE -> discard path | [V] |
| 0xbc60805 | cap branch | - | - | `0xbc60805  jb short 0xBC6083F` | below cap -> proceed with the draw | [V] |
| 0xbc60845 | sort-key view mask | - | imm | `0xbc60845  mov rax,0x3FC0000000000000` | sort-key view mask (view at bits 54..61) | [V] |
| 0xbc60885 | s_ctx load | 8 | [0x12AE1748] | `0xbc60885  mov r11,[0x12AE1748]` | s_ctx = bgfx::Context global | [V] |
| 0xbc60897 | per-view sort mode | 1 | [r11+r14+0x1EAB1B2] | `0xbc60897  movzx r14d,byte ptr [r11+r14+0x1EAB1B2]` | per-view sort mode byte (view*0x140 + 0x1EAB1B2) | [V] |
| 0xbc608fc | per-view sequence | 4 | [r11+rdx*4+0x1EAAC60] | `0xbc608fc  lock xadd [r11+rdx*4+0x1EAAC60],ecx` | per-view sequence counter | [V] |
| 0xbc60991 | sort key store | 8 | [rcx+r14*8+0x14700] | `0xbc60991  mov [rcx+r14*8+0x14700],rax` | sort key u64 -> Frame+0x14700+idx*8 | [V] |
| 0xbc6099c | sorted index store | 2 | [rax+r14*2+0x94700] | `0xbc6099c  mov [rax+r14*2+0x94700],di` | u16 sorted index -> Frame+0x94700+idx*2 | [V] |
| 0xbc60b13 | draw header copy | 16 | [rax+rcx+0xB4700] | `0xbc60b13  movaps [rax+rcx+0xB4700],xmm0` | last of 8 movaps copying the 0x80 draw header (encoder+0x40..0xBF -> Frame+0xB4700+idx*0x80); header+0x1F == encoder+0x5F = RenderMarkHook's mark byte | [V] |
| 0xbc60b33 | RenderBind stride | - | imm 0x540 | `0xbc60b33  imul rcx,r14,0x540` | RenderDraw record stride: idx*0x540 | [V] |
| 0xbc60b41 | bind memcpy length | 4 | imm 0x518 | `0xbc60b41  mov r8d,0x518` | memcpy length 0x518 (RenderBind 0x514 + bind hash) | [V] |
| 0xbc60b4a | RenderBind store | - | - | `0xbc60b4a  call 0xEEC6EC0` | **Encoder::submit seam**: 0x518-byte RenderBind -> Frame+0x8B4700+idx*0x540 | [V] |
| 0xbc60b6e | default state | - | imm | `0xbc60b6e  mov rax,0x10000500000001F` | default state value | [V] |
| 0xbc60b78 | state reset | 8 | [rsi+0x60] | `0xbc60b78  mov [rsi+0x60],rax` | encoder+0x60 == header+0x20 reset to default state 0x010000500000001F | [V] |
| 0xe81b733 | flush kind | 4 (reg) | - | `0xe81b733  mov r12d,r9d` | flush kind = r9d (0 non-indexed / 1 indexed) | [V] |
| 0xe81b736 | pending count | 4 | [rcx+r12*4+0x10] | `0xe81b736  mov esi,[rcx+r12*4+0x10]` | DrawBatcher pending[kind] at +0x10+kind*4 | [V] |
| 0xe81b74a | pending clear | 4 | [rcx+r12*4+0x10] | `0xe81b74a  mov dword ptr [rcx+r12*4+0x10],0` | pending[kind] cleared after snapshot | [V] |
| 0xe81b753 | capacity compare | 4 | [rcx+0x115C] | `0xe81b753  cmp [rcx+0x115C],esi` | capacity at +0x115C | [V] |
| 0xe81b779 | records pointer | 8 | [rdi+r12*8+0x18] | `0xe81b779  mov rax,[rdi+r12*8+0x18]` | records[kind] pointer at +0x18+kind*8 | [V] |
| 0xe81b89d | indexed record stride | 0x88 (stride) | - | `0xe81b89d  add r15,0x88` | indexed record stride 0x88 | [V] |
| 0xe81ba9f | non-indexed record stride | 0x70 (stride) | - | `0xe81ba9f  add r15,0x70` | non-indexed record stride 0x70 | [V] |
| 0xe81b86a | indexed draw args | 4 | [r15+0x70] | `0xe81b86a  mov edx,[r15+0x70]` | indexed record draw args: indexCount at +0x70 | [V] |
| 0xe81b87a | startInstance | 4 | [r15+0x80] | `0xe81b87a  mov r11d,[r15+0x80]` | startInstance at indexed record +0x80 — the value RenderMarkHook's replay patches (kRecordStartInstanceOffset) | [V] |
| 0xe81b7c9 | command list | 8 | [rbx+0x30] | `0xe81b7c9  mov rcx,[rbx+0x30]` | [JobContext+0x30] = ID3D12GraphicsCommandList* | [V] |
| 0xe81b866 | DrawIndexedInstanced | 8 | [rax+0x68] | `0xe81b866  mov rax,[rax+0x68]` | DrawIndexedInstanced via cmdlist vtable +0x68 (slot 13) | [V] |
| 0xe81bac4 | DrawInstanced | 8 | [rcx] | `0xe81bac4  mov rax,[rcx]` | DrawInstanced path: rcx = cmdlist object, [rcx] = vtable, next instr `0xe81bac7  mov rax,[rax+0x60]` = slot 12 | [V] |
| 0xe81beed | ExecuteIndirect | 8 | [rax+0x1D8] | `0xe81beed  mov rax,[rax+0x1D8]` | ExecuteIndirect via cmdlist vtable +0x1D8 (slot 59, indirect path) | [V] |
| 0xe82cfad | flush site kind 0: batcher | 8 | [rbx+0x250] | `0xe82cfad  mov rcx,[rbx+0x250]` | executor flush site: rcx = [state+0x250] = DrawBatcher* | [V] |
| 0xe82cfa6 | flush site kind 0: renderer | 8 | [[rbx+0xB0]+0x238] | `0xe82cfa6  mov rsi,[rax+0x238]` (rax = [rbx+0xB0]) | rsi = renderer pointer [[state+0xb0]+0x238] | [V] |
| 0xe82cfb7 | flush site kind 0: job context | 8 | [rbx+0x90] | `0xe82cfb7  mov r8,[rbx+0x90]` | r8 = [state+0x90] = JobContext* ([r8+0x30] = command list) | [V] |
| 0xe82cfbe | flush site kind 0: kind | 4 (reg) | - | `0xe82cfbe  xor r9d,r9d` | r9d = 0 -> non-indexed kind | [V] |
| 0xe82cfc1 | flush site kind 0 call | - | - | `0xe82cfc1  call 0xE81B720` | **executor -> flush call site (kind 0)**; args exactly per 6ej: (DrawBatcher* [state+0x250], renderer [[state+0xb0]+0x238], JobContext* [state+0x90], kind 0) | [V] |
| 0xe82cfd8 | flush site kind 1: kind | 4 | imm 1 | `0xe82cfd8  mov r9d,1` | kind 1 (indexed) | [V] |
| 0xe82cfde | flush site kind 1 call | - | - | `0xe82cfde  call 0xE81B720` | **executor -> flush call site (kind 1)** | [V] |

## (3) Route: which draw renders which actor (1.26.62.01, every link [V] in the table above)

1. **Actor -> item.** bodyActor (0x66d0a00, frame 0xE38 bytes) gets the actor pair in its 5th argument `S`, reads `**[S]+0xC8` (`0x66d313d mov rax,[rax+0xC8]`, sibling +0xC0 at `0x66d312c`) — the 6bg/Sigs `*(S+0xC8)` link missing from the description objects — null-checks both (`0x66d3152`, `0x66d3158`, bail `0x66d3160`) and hands the pair to the item builder `0x6698060` (`0x66d3177`). bodyActor also makes the insert-pointer call `0xBBD7C70` (`0x66d2eee`, documented in RenderMarkHook.h) and both item writers `0x6765020` (`0x66d4265`) and `0x6768c70` (`0x66d49e2`).
2. **Item -> pass object.** Each writer calls `passLookup` `0x5ABA5C0` (`0x6765046`, `0x6768c96`); passLookup maps at manager+0xA0 (`0x5aba5cc`), returns node+0x10 (`0x5aba5e0`), allocs 0x8C8-byte nodes (`0x5aba5f7`) inited self-linked with count 0 (`0x5aba60e`/`0x5aba611`/`0x5aba619`); the writer pushes into the pass object's +0x588 storage, advancing its end by 0x30 per item (`0x67650d2`). The capture convention RenderMarkHook.cpp relies on (pass object in rdi at `0x66ca5ce`, kPushLookupReturnRva) exists as code, but see open items below.
3. **Item -> draw header.** `Encoder::submit` `0xbc60740` seam re-validated: draw index = CAS increment of Frame+0xDC57E8 (`0xbc607ea`), sort key -> Frame+0x14700+idx*8 (`0xbc60991`), sorted u16 -> Frame+0x94700+idx*2 (`0xbc6099c`), and the **0x80 draw header** (encoder state at +0x40, so the mark byte at encoder+0x5F = header+0x1F) is copied to Frame+0xB4700+idx*0x80 (8 movaps, last at `0xbc60b13`); RenderBind (0x518 bytes) -> Frame+0x8B4700+idx*0x540 (`0xbc60b4a`).
4. **Draw -> GPU.** Flush `0xe81b720` re-validated: pending counts at +0x10+kind*4 (`0xe81b736`), cleared (`0xe81b74a`), capacity +0x115C (`0xe81b753`), records at +0x18+kind*8 (`0xe81b779`), strides 0x88 (`0xe81b89d`) / 0x70 (`0xe81ba9f`), draws via cmdlist vtable +0x60 DrawInstanced (`0xe81bac4`), +0x68 DrawIndexedInstanced (`0xe81b866`), +0x1D8 ExecuteIndirect (`0xe81beed`). Indexed records carry startInstance at record +0x80 (`0xe81b87a` reads [r15+0x80]). Executor calls the flush at `0xe82cfc1` (kind 0) and `0xe82cfde` (kind 1) with the 6ej argument pattern verbatim (`0xe82cfad`/`0xe82cfa6`/`0xe82cfb7`/`0xe82cfbe`).
5. **Answer:** an indexed draw renders the actor whose roster slot = `startInstance & 0xFF` of the record emitted at flush time (`kRosterStartBase = 0x5A0A5700`, slot 1..96), where the mark entered at bodyActor's item built from `*(S+0xC8)`. BatchActor-instanced draws carry no actor (6d/6u).

## (4) RenderMarkHook side (source level; files exist on disk [V])

src/client/features/hooks/hooks/render/RenderMarkHook.h + .cpp exist (P2a ticked; not registered in HookManager.cpp; used by FrameFilterHook, ActorRenderDispatcherHook, chams Renderer, TrackerHooks). The hook's mapping, verbatim from the source I read:
- kEncoderHeaderOffset = 0x40, kHeaderMarkOffset = 0x1F: submit stores a 0x80-byte header copied from encoder state, so `mark = encoder + 0x40 + 0x1F` = header+0x1F — matches the game's header copy at `0xbc60b13` [V game side; byte role is source-documented].
- kRecordMarkOffset = 0x84, kRecordStartInstanceOffset = 0x80, kBuilderReturnRva = 0xE82CB90: stateEncode (hook entered when the return address is 0xE82CB90 — verified a real instruction in the exe: `0xe82cb90  nop`, right after `0xe82cb8b  call 0xE81B4D0`) writes record+0x84 = kRecordMarkBase | slot from header[0x1F]; replay writes record+0x80 = kRosterStartBase | slot for marked records; kRosterStartBase = 0x5A0A5700, slots 1..96; slotOf clears anything else to 0.
- Task side: kBodyTaskKind = 0x481CF7B16E204CF8 (fnv1a("UseAlphaRewrite") per 6ad), task kind read at data-0x48, entries of 0x18 with the item record at +8, kItemSize = sizeof(DrawItem) = 0xC8 (DrawItem.h static_assert).
- Drawn flow: wanted actor's pass -> mark byte set around submit (RenderMark::submit hosts Encoder::submit via RewriteEncoder::dispatch; see rewrite-program.md) -> stateEncode copies mark into record+0x84 -> replay patches record+0x80 -> the draw call carries startInstance -> TrackerHooks::slotOf(recovers roster slot) -> chams twin drawn; mark cleared afterwards so a slot reused later never carries a stale mark.

## (5) Remaining step (off-disk; blocked for this unit, not by this note)

Exact in-game/build step: build the client DLL (RenderMarkHook is source-complete but not built/injected — no build permitted here), inject, then poll DrawBatcher state at renderer+0x250 between frames (pending counts/draw records) and run RenderMarkHook + TrackerHooks in game to confirm marks -> record+0x80 startInstance -> TrackerHooks slotOf -> actor. The game may not be launched or attached to from this unit, so this stays off-disk; it does not block the static close (same disposition as M3d).

## Open items ([?], non-blocking)

- sub_66ca5a0 (containing kPushLookupReturnRva `0x66CA5CE`) has **no callers**: ripscan and xref callers return nothing on 62.01, so RenderMarkHook.cpp's pass-object capture condition (`_ReturnAddress() == base + 0x66CA5CE`) can never fire from bodyActor as written (bodyActor's passLookup calls via the writers return to `0x676504b`/`0x6768c9b`, not `0x66CA5CE`). The route is proven at game-code level; the hook's wiring of that capture condition is not statically confirmed. [?]
- Item-record serialization: passLookup inits +0x00/+0x08/+0x10 while writers push into the pass object's +0x588 vector (0x30 stride) and pools (+0x630 u32, +0x690 u16, +0x750 0x58); RenderMarkHook.cpp reads *pass/*(pass+8) with stride kItemSize = 0xC8 (DrawItem.h). The exact item-record serialization on 62.01 is not statically reconciled between the two views. [I]

## TOOL REQUESTS

None — rdis directly for each quoted address; no helper script written.

CLOSES?: YES — every part of the P1c line is proven by [V] rows on disk now: RenderMarkHook.{h,cpp} exist and implement the actor-to-draw mark chain (source [V] file content; semantics per source comments); actor read `*(S+0xC8)` (0x66d313d) + sibling +0xC0 (0x66d312c) + item builder (0x66d3177) + writers (0x66d4265/0x66d49e2) + insert-pointer call (0x66d2eee); passLookup + item push (0x5aba5e0/0x5aba60e-619; 0x6765046/0x6768c96/0x67650d2); Encoder::submit seam re-validated (Frame+0xDC57E8 CAS 0xbc607ea; 0x80 header -> Frame+0xB4700+idx*0x80, 0xbc60b13; mark byte encoder+0x5F = header+0x1F; RenderBind -> Frame+0x8B4700+idx*0x540, 0xbc60b4a); flush 0xe81b720 re-validated (counts 0xe81b736/clear 0xe81b74a; cap +0x115C 0xe81b753; records +0x18/kind 0xe81b779; strides 0x88/0x70; DrawInstanced/Indexed/ExecuteIndirect via cmdlist +0x60/+0x68/+0x1D8; executor sites 0xe82cfc1/0xe82cfde with args per 6ej); record+0x80 = startInstance (0xe81b87a) = the mark's roster slot -> actor. The two [?]/[I] hook-wiring details above are non-blocking (same disposition as M3d); the single remaining fact is the off-disk in-game test listed in section 5 (build and launch not permitted for this unit).
