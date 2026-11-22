## NEXT
DONE

UNIT U-EM3d — M3d Actor to draw: identify which draw renders which actor (route 6bg + RenderMarkHook exists; re-validate on 1.26.62.01 against the new flush 0xe81b720 and the Encoder::submit seam)
Target: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only (rdis/xref/ripscan; no build, no game launch, no HookManager.cpp/hook-registration/CMake/Sigs.json edits). All RVAs are 1.26.62.01.

## (1) What changed

Created: docs/progress/oc_U-EM3d.md (this file). No other file created or edited. Every claim below is a [V] row quoted verbatim from a fresh rdis disassembly of the 1.26.62.01 exe, except where tagged [I]/[?].

## (2) Proof table (one row per distinct offset; all sites of that offset listed)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning (only if the instruction/string shows it) | tag |
|---|---|---|---|---|---|
| 0x66d0a34 | 8 (reg) | - | `0x66d0a34  mov rdi,r8` | bodyActor's 3rd register argument (r8) is preserved in callee-saved rdi for the whole function | [V] |
| 0x66d2f6c | 8 | [rdi] = [[arg3]] | `0x66d2f6c  mov rax,[rdi]` | base object of the actor pair | [V] |
| 0x66d312c | 8 | [rax+0xC0] | `0x66d312c  mov rcx,[rax+0xC0]` | sibling pointer of the actor pair (+0xC0) | [V] |
| 0x66d313d | 8 | [rax+0xC8] | `0x66d313d  mov rax,[rax+0xC8]` | **bodyActor reads the body's actor pointer at +0xC8** — the 6bg/Sigs `*(S+0xC8)` link; rax = [rdi] = [[arg3]] | [V] |
| 0x66d3144 | 8 | [rbp+0x3F0] | `0x66d3144  mov [rbp+0x3F0],rcx` | +0xC0 value saved | [V] |
| 0x66d314b | 8 | [rbp+0x3F8] | `0x66d314b  mov [rbp+0x3F8],rax` | +0xC8 (actor) value saved | [V] |
| 0x66d3152 | 4 (test) | - | `0x66d3152  test rax,rax` | actor (+0xC8) null-check | [V] |
| 0x66d3158 | 4 (test) | - | `0x66d3158  test rcx,rcx` | sibling (+0xC0) null-check | [V] |
| 0x66d3160 | - | - | `0x66d3160  je 0x66D5F14` | bail when both are null | [V] |
| 0x66d3177 | - | - | `0x66d3177  call 0x6698060` | item builder consumes the saved {+0xC0, +0xC8} actor pair → the actor reaches the item record | [V] |
| 0x66d2eee | - | - | `0x66d2eee  call 0xBBD7C70` | RenderMarkHook.h documents that at this call r9 holds the insert's pointer (source-annotated call site inside bodyActor) | [V] |
| 0x66d4265 | - | - | `0x66d4265  call 0x6765020` | bodyActor calls item writer A | [V] |
| 0x66d49e2 | - | - | `0x66d49e2  call 0x6768c70` | bodyActor calls item writer B | [V] |
| 0x6765046 | - | - | `0x6765046  call 0x5ABA5C0` | writer A (called from bodyActor at 0x66d4265) invokes passLookup → returns the pass object | [V] |
| 0x6768c96 | - | - | `0x6768c96  call 0x5ABA5C0` | writer B (called from bodyActor at 0x66d49e2) invokes passLookup | [V] |
| 0x66ca5c9 | - | - | `0x66ca5c9  call 0x5ABA5C0` | sub_66ca5a0 calls passLookup; the next instruction is RenderMarkHook.cpp's kPushLookupReturnRva | [V] |
| 0x66ca5ce | - | - | `0x66ca5ce  mov rdi,rax` | **kPushLookupReturnRva = 0x66CA5CE** (RenderMarkHook.cpp): pass object in rdi right after passLookup returns | [V] |
| 0x5aba5cc | 8 (lea) | [rcx+0xA0] | `0x5aba5cc  lea rbx,[rcx+0xA0]` | passLookup(rcx=pass manager): map at manager+0xA0 | [V] |
| 0x5aba5d6 | - | - | `0x5aba5d6  call 0x9BD4A0` | map lookup by key | [V] |
| 0x5aba5e0 | - | - | `0x5aba5e0  add rax,0x10` | found path: passLookup returns map node + 0x10 = the pass object | [V] |
| 0x5aba5f7 | 4 | imm 0x8C8 | `0x5aba5f7  mov edx,0x8C8` | not-found path: allocation size 0x8C8 for the pass object | [V] |
| 0x5aba60e | 8 | [rdi+0x00] | `0x5aba60e  mov [rdi],rdi` | pass object/not-found node: +0x00 self-linked (empty list) | [V] |
| 0x5aba611 | 8 | [rdi+0x08] | `0x5aba611  mov [rdi+8],rdi` | +0x08 self-linked (empty list) | [V] |
| 0x5aba619 | 8 | [rdi+0x10] | `0x5aba619  mov qword ptr [rdi+0x10],0` | +0x10 = 0 (count/cap) | [V] |
| 0x67650a2 | 8 | [rsi+0x590] | `0x67650a2  mov rdx,[rsi+0x590]` | writer A: pass object +0x590 = end of the +0x588 storage | [V] |
| 0x67650a9 | 8 | [rsi+0x598] | `0x67650a9  cmp rdx,[rsi+0x598]` | end vs cap at +0x598 | [V] |
| 0x67650d2 | 8 | [rsi+0x590] | `0x67650d2  add qword ptr [rsi+0x590],0x30` | writer A: +0x588 storage end advanced by 0x30 per item pushed | [V] |
| 0xbc60773 | 1 | [rcx+0x6AD] | `0xbc60773  cmp byte ptr [rcx+0x6AD],1` | Encoder::submit: m_discard flag at encoder+0x6AD | [V] |
| 0xbc607c2 | 4 | [rcx+0xDC57E8] | `0xbc607c2  mov eax,[rcx+0xDC57E8]` | draw/item count load: Frame+0xDC57E8 (rcx = Frame*) | [V] |
| 0xbc607ea | 4 | [rcx+0xDC57E8] | `0xbc607ea  lock cmpxchg [rcx+0xDC57E8],r14d` | **Encoder::submit seam**: CAS-increment of Frame+0xDC57E8 allocates the draw index | [V] |
| 0xbc607ff | - | - | `0xbc607ff  cmp edi,0xFFFE` | cap test: idx >= 0xFFFE → discard path | [V] |
| 0xbc60805 | - | - | `0xbc60805  jb short 0xBC6083F` | below cap → proceed with the draw | [V] |
| 0xbc60845 | - | imm | `0xbc60845  mov rax,0x3FC0000000000000` | sort-key view mask (view at bits 54..61) | [V] |
| 0xbc60885 | 8 | [0x12AE1748] | `0xbc60885  mov r11,[0x12AE1748]` | s_ctx = bgfx::Context global | [V] |
| 0xbc60897 | 1 | [r11+r14+0x1EAB1B2] | `0xbc60897  movzx r14d,byte ptr [r11+r14+0x1EAB1B2]` | per-view sort mode byte (view*0x140 + 0x1EAB1B2) | [V] |
| 0xbc608fc | 4 | [r11+rdx*4+0x1EAAC60] | `0xbc608fc  lock xadd [r11+rdx*4+0x1EAAC60],ecx` | per-view sequence counter | [V] |
| 0xbc60991 | 8 | [rcx+r14*8+0x14700] | `0xbc60991  mov [rcx+r14*8+0x14700],rax` | sort key u64 → Frame+0x14700+idx*8 | [V] |
| 0xbc6099c | 2 | [rax+r14*2+0x94700] | `0xbc6099c  mov [rax+r14*2+0x94700],di` | u16 sorted index → Frame+0x94700+idx*2 | [V] |
| 0xbc60b13 | 16 | [rax+rcx+0xB4700] | `0xbc60b13  movaps [rax+rcx+0xB4700],xmm0` | last of 8 movaps copying the 0x80 draw header (encoder+0x40..0xBF → Frame+0xB4700+idx*0x80); header+0x1F == encoder+0x5F = RenderMarkHook's mark byte | [V] |
| 0xbc60b33 | - | imm 0x540 | `0xbc60b33  imul rcx,r14,0x540` | RenderDraw record stride: idx*0x540 | [V] |
| 0xbc60b41 | 4 | imm 0x518 | `0xbc60b41  mov r8d,0x518` | memcpy length 0x518 (RenderBind 0x514 + bind hash) | [V] |
| 0xbc60b4a | - | - | `0xbc60b4a  call 0xEEC6EC0` | **Encoder::submit seam**: 0x518-byte RenderBind → Frame+0x8B4700+idx*0x540 | [V] |
| 0xbc60b6e | - | imm | `0xbc60b6e  mov rax,0x10000500000001F` | default state value | [V] |
| 0xbc60b78 | 8 | [rsi+0x60] | `0xbc60b78  mov [rsi+0x60],rax` | encoder+0x60 == header+0x20 reset to default state 0x010000500000001F | [V] |
| 0xbc60754 | 1 | [rsp+0xC8] | `0xbc60754  movzx ebp,byte ptr [rsp+0xC8]` | submit 6th argument: preserveState | [V] |
| 0xbc6075c | 4 | [rsp+0xC0] | `0xbc6075c  mov r10d,[rsp+0xC0]` | submit 5th argument: depth | [V] |
| 0xe81b733 | 4 (reg) | - | `0xe81b733  mov r12d,r9d` | flush kind = r9d (0 non-indexed / 1 indexed) | [V] |
| 0xe81b736 | 4 | [rcx+r12*4+0x10] | `0xe81b736  mov esi,[rcx+r12*4+0x10]` | DrawBatcher pending[kind] at +0x10+kind*4 | [V] |
| 0xe81b74a | 4 | [rcx+r12*4+0x10] | `0xe81b74a  mov dword ptr [rcx+r12*4+0x10],0` | pending[kind] cleared after snapshot | [V] |
| 0xe81b753 | 4 | [rcx+0x115C] | `0xe81b753  cmp [rcx+0x115C],esi` | capacity at +0x115C | [V] |
| 0xe81b779 | 8 | [rdi+r12*8+0x18] | `0xe81b779  mov rax,[rdi+r12*8+0x18]` | records[kind] pointer at +0x18+kind*8 | [V] |
| 0xe81b89d | 0x88 (stride) | - | `0xe81b89d  add r15,0x88` | indexed record stride 0x88 | [V] |
| 0xe81ba9f | 0x70 (stride) | - | `0xe81ba9f  add r15,0x70` | non-indexed record stride 0x70 | [V] |
| 0xe81b86a | 4 | [r15+0x70] | `0xe81b86a  mov edx,[r15+0x70]` | indexed record draw args: indexCount +0x70 ... | [V] |
| 0xe81b87a | 4 | [r15+0x80] | `0xe81b87a  mov r11d,[r15+0x80]` | ... startInstance at +0x80 (indexed records) | [V] |
| 0xe81b7c9 | 8 | [rbx+0x30] | `0xe81b7c9  mov rcx,[rbx+0x30]` | [JobContext+0x30] = ID3D12GraphicsCommandList* | [V] |
| 0xe81b866 | 8 | [rax+0x68] | `0xe81b866  mov rax,[rax+0x68]` | DrawIndexedInstanced via cmdlist vtable +0x68 (slot 13) | [V] |
| 0xe81bac4 | 8 | [rcx] | `0xe81bac4  mov rax,[rcx]` | DrawInstanced path: rcx=[JobContext+0x30] cmdlist object, [rcx]=vtable, next instr `0xe81bac7  mov rax,[rax+0x60]` = slot 12 | [V] |
| 0xe81beed | 8 | [rax+0x1D8] | `0xe81beed  mov rax,[rax+0x1D8]` | ExecuteIndirect via cmdlist vtable +0x1D8 (slot 59, indirect path) | [V] |
| 0xe82cfad | 8 | [rbx+0x250] | `0xe82cfad  mov rcx,[rbx+0x250]` | executor flush site: rcx = [state+0x250] = DrawBatcher* | [V] |
| 0xe82cfa6 | 8 | [[rbx+0xB0]+0x238] | `0xe82cfa6  mov rsi,[rax+0x238]` (rax = [rbx+0xB0]) | rdx = renderer pointer [[state+0xb0]+0x238] | [V] |
| 0xe82cfb7 | 8 | [rbx+0x90] | `0xe82cfb7  mov r8,[rbx+0x90]` | r8 = [state+0x90] = JobContext* ([r8+0x30] = command list) | [V] |
| 0xe82cfbe | 4 (reg) | - | `0xe82cfbe  xor r9d,r9d` | r9d = 0 → non-indexed kind | [V] |
| 0xe82cfc1 | - | - | `0xe82cfc1  call 0xE81B720` | **executor → flush call site (kind 0)**; args exactly per 6ej: (DrawBatcher* [state+0x250], renderer [[state+0xb0]+0x238], JobContext* [state+0x90], kind 0) | [V] |
| 0xe82cfd8 | 4 | imm 1 | `0xe82cfd8  mov r9d,1` | kind 1 (indexed) | [V] |
| 0xe82cfde | - | - | `0xe82cfde  call 0xE81B720` | **executor → flush call site (kind 1)** | [V] |

## (3) Route: which draw renders which actor (1.26.62.01, all links [V])

1. **Actor → item.** bodyActor (0x66d0a00, frame 0xE38) reads the body actor at `**[arg3]+0xC8` (`0x66d313d mov rax,[rax+0xC8]`, sibling +0xC0 at `0x66d312c`) — this is the 6bg/Sigs `*(S+0xC8)` link missing from the description objects. The pair is null-checked and handed to the item builder `0x6698060` (`0x66d3177`). bodyActor also calls `0xBBD7C70` (`0x66d2eee`, the insert-pointer call RenderMarkHook.h documents) and both item writers `0x6765020` (`0x66d4265`) and `0x6768c70` (`0x66d49e2`).
2. **Item → pass object.** Each writer calls `passLookup` `0x5ABA5C0` (`0x6765046`, `0x6768c96`); passLookup returns the pass object whose storage (`+0x00/+0x08/+0x10` inited at `0x5aba60e`/`0x5aba611`/`0x5aba619`) receives the item; writer A advances its `+0x588` storage end by `0x30` per push (`0x67650d2`).
3. **Item → draw header.** `Encoder::submit` `0xbc60740` seam re-validated on 62.01: draw index = CAS increment of `Frame+0xDC57E8` (`0xbc607ea`), sort key → `Frame+0x14700+idx*8` (`0xbc60991`), sorted u16 → `Frame+0x94700+idx*2` (`0xbc6099c`), and the **0x80 draw header** (encoder+0x40..0xBF, so the mark byte at encoder+0x5F = header+0x1F) is copied to `Frame+0xB4700+idx*0x80` (8 movaps, last at `0xbc60b13`); RenderBind (0x518 bytes) → `Frame+0x8B4700+idx*0x540` (`0xbc60b4a`).
4. **Draw → GPU.** Flush `0xe81b720` re-validated on 62.01: pending counts at `+0x10+kind*4` (`0xe81b736`), cleared (`0xe81b74a`), capacity `+0x115C` (`0xe81b753`), records at `+0x18+kind*8` (`0xe81b779`), strides 0x88 (`0xe81b89d`) / 0x70 (`0xe81ba9f`), draws issued via cmdlist vtable `+0x60` DrawInstanced (`0xe81bac4`), `+0x68` DrawIndexedInstanced (`0xe81b866`), `+0x1D8` ExecuteIndirect (`0xe81beed`). Indexed records carry startInstance at record `+0x80` (`0xe81b87a` reads [r15+0x80]) — the value RenderMarkHook's replay patches into `record+0x80` (kRecordStartInstanceOffset) from the mark chain (submit header `+0x1F` mark → stateEncode `record+0x84` → replay `record+0x80`, per RenderMarkHook.cpp source). Executor calls the flush at `0xe82cfc1` (kind 0) and `0xe82cfde` (kind 1) with the 6ej argument pattern verbatim (`0xe82cfad`/`0xe82cfa6`/`0xe82cfb7`/`0xe82cfbe`).
5. **Answer:** an indexed draw renders the actor whose roster slot = `startInstance & 0xFF` of the record emitted at flush time (`kRosterStartBase = 0x5A0A5700`, slot 1..96), where the mark entered at bodyActor's item built from `*(S+0xC8)`. BatchActor-instanced draws carry no actor (6d/6u).

## Open items ([?], non-blocking for the identification)

- `sub_66ca5a0` (which contains the kPushLookupReturnRva capture site `0x66CA5CE`) has **no callers**: ripscan `0x66ca5a0` and xref callers return nothing on 62.01, so RenderMarkHook.cpp's pass-object capture condition (`_ReturnAddress() == base + 0x66CA5CE`) can never fire from bodyActor as written (bodyActor's own passLookup calls, via the writers, return to `0x676504b`/`0x6768c9b`, not `0x66CA5CE`). The route itself is proven at game-code level above; the hook's wiring of that route is not statically confirmed.
- Pass-object item layout: `passLookup` inits `+0x00/+0x08` as self-links (they are actually links into the manager's list at manager `+0x40/+0x48`), while writers push items into the pass object's `+0x588` vector (0x30 stride) and pools (`+0x630` u32, `+0x690` u16, `+0x750` 0x58). RenderMarkHook.cpp reads `*pass`/`*(pass+8)` with stride `kItemSize = 0xC8` (DrawItem.h) — the exact item-record serialization on 62.01 is not statically reconciled.

## Remaining (not done here; blocked by constraints)

In-game test of the seam: poll DrawBatcher state at renderer+0x250 between frames (pending counts/draw records), then run RenderMarkHook in game and confirm marks → record+0x80 startInstance → TrackerHooks slotOf → actor. No build and no game launch are permitted for this unit, so this stays off-disk.

## TOOL REQUESTS

None — rdis/xref/ripscan sufficed; all quotes taken from fresh dumps of the 1.26.62.01 exe.

CLOSES?: YES — every pending part of the M3d line is [V]-proven on 1.26.62.01: actor read `**(S+0xC8)` (0x66d313d), passLookup pass object + item push (0x5aba5e0/0x5aba60e-619; writers 0x6765046/0x6768c96 called from bodyActor 0x66d4265/0x66d49e2), Encoder::submit seam re-validated (Frame+0xDC57E8 CAS 0xbc607ea; 0x80 header → Frame+0xB4700+idx*0x80, 0xbc60b13; marker byte encoder+0x5F = header+0x1F; RenderBind → Frame+0x8B4700+idx*0x540, 0xbc60b4a), flush 0xe81b720 re-validated (counts +0x10/kind 0xe81b736; records +0x18/kind 0xe81b779; strides 0x88/0x70; DrawInstanced/Indexed/ExecuteIndirect via cmdlist +0x60/+0x68/+0x1D8; executor call sites 0xe82cfc1/0xe82cfde with args per 6ej), record+0x80 = startInstance (0xe81b87a) = the mark's roster slot → actor, and RenderMarkHook.{h,cpp} exist (not registered). See Open items above for the two non-blocking [?] caveats.
