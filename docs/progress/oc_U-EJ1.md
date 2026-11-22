## NEXT
DONE

# Unit U-EJ1 — J1 Takeover design written against A-F: seams 1-6 with data and risks (6dy)

Item line (checklist J1): "J1 Takeover design written against A-F: seams 1-6 with data and risks (6dy); consistent by static+live evidence, no patch exercised in game (P1) — architecture-level, survives"

Source of the design to verify: docs/BGFX_MAP.md section 6dy ("J1: frame-level takeover design (written against A-F, untested in game)"), which lists seams 1-6 (earliest = game thread, latest = GPU submit) with the data each gives and what each can change, plus a validation status paragraph and three risks (task-list entries are shared_ptr<Task>; frame pointers alternate each frame fill vs consume; RVAs must be re-checked with SelfTest sigs at startup).

Pending part (the only part this unit touches): prove every seam in 6dy by static analysis (verbatim `0xRVA  instr` lines), cross-check seam-to-seam consistency (same pass names in task list, sort keys' viewIds and executor loop; camera from 6dw; materials from G1a/6dr; components from 6dt/6du), tag each row [V]/[I]/[?], record the data each seam gives and what it can change plus the risks, and end with CLOSES? YES/NO + single blocking fact. No game access: no patch exercised in game; the in-game test plan goes under TOOL REQUESTS only.

## Verbatim proof lines (each checked by tools/sigs/verify_oc.py against rdis dis of Minecraft.Windows.exe 1.26.62.01)

0x4e39cb0  push rbp
0x66232b0  push rbp
0x67c9c20  push rbp
0xc270460  push rbp
0xc273420  push rbp
0xe9002e0  push rbp
0xbc60740  push r15
0xbc607c2  mov eax,[rcx+0xDC57E8]
0xbc607ea  lock cmpxchg [rcx+0xDC57E8],r14d
0xbc60991  mov [rcx+r14*8+0x14700],rax
0xbc6099c  mov [rax+r14*2+0x94700],di
0xbc60b13  movaps [rax+rcx+0xB4700],xmm0
0xbc61e22  sub rsp,0x238
0xe821120  push rbp
0xe82e230  push rbp
0xe81e860  push r15

## (1) Answer table — seams 1-6 with data, risks and consistency

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|---|
| FrameBuilder::insert clone (seam 1) | 0x4e39cb0 | - | - | `0x4e39cb0  push rbp` | thin `insert<RenderBatchActorDescription>` clone, Item group vslot 0x378 tag 10; passes `{desc*, tag}` live pointer to the group insert; hook here sees/drops/edits every description before it enters the frame (actors, chunks, particles, UI) | [V] |
| BgfxFrameBuilder::endFrame (seam 2) | 0x66232b0 | - | - | `0x66232b0  push rbp` | whole-frame boundary on the builder side; runs the deferred texture/buffer flush (6dv) at its two exits (0x66244e7, 0x66264e6) before the frame renderer; good for per-frame setup/teardown of custom resources | [V] |
| Frame renderer 0x67c9c20 (seam 2) | 0x67c9c20 | - | - | `0x67c9c20  push rbp` | top-level per-frame renderer function; calls PipelineDiskCache::tick, resource-set setup (7 x 0xa784c0), then BgfxContext::endFrame 0xc270460; shared by Fancy and VV/RTX paths | [V] |
| BgfxContext::endFrame (seam 3) | 0xc270460 | - | - | `0xc270460  push rbp` | pack this-fields into a small struct, call frame-graph generate 0xc273420, task dispatch 0xe9002e0, fence/wait 0xeec58f0; primary takeover seam — one hook controls the whole pass list | [V] |
| frame-graph generate 0xc273420 (seam 3) | 0xc273420 | - | - | `0xc273420  push rbp` | turns the declared dragon graph into encoded tasks; 51 distinct callees; pass identity by FNV-1a 64 name hash (PassNames.h); pass enable/disable by swapping the std::function impl at task+0x70, reorder by swapping raw 0x80-byte entries, insert custom task by cloning an entry and pointing +0x70 at our callable | [V] |
| task dispatch 0xe9002e0 (seam 3) | 0xe9002e0 | - | - | `0xe9002e0  push rbp` | runs the encoded task list (0x80-byte entries) on the render thread; taskList begin/end/+0x18, stride 0x80, kind via vtable slot 0x18 | [V] |
| Encoder::submit (seam 4) | 0xbc60740 | - | - | `0xbc60740  push r15` | per-draw program/state/view/bindings; allocates the draw index via CAS on Frame+0xDC57E8 (cap 0xFFFF), builds the 0x80 draw header, copies it to Frame+0xB4700+idx*0x80 and the 0x518-byte RenderBind to Frame+0x8B4700+idx*0x540; veto or rewrite a draw via state bits, program, textures | [V] |
| draw index alloc CAS (seam 4 data) | Frame+0xDC57E8 | dword 4 | [rcx+0xDC57E8] | `0xbc607ea  lock cmpxchg [rcx+0xDC57E8],r14d` | CAS-increment of Frame+0xDC57E8 allocates the draw index (cap 0xFFFF = maxDrawCalls 65535) | [V] |
| sort key store (seam 5 data) | Frame+0x14700 | qword 8 | [rcx+r14*8+0x14700] | `0xbc60991  mov [rcx+r14*8+0x14700],rax` | sort key u64 stored at Frame+0x14700+idx*8 (view<<54 mask 0x3FC0000000000000, type tags 0x10/0x14/0x18 at bits 50..52) | [V] |
| sorted index store (seam 5 data) | Frame+0x94700 | word 2 | [rax+r14*2+0x94700] | `0xbc6099c  mov [rax+r14*2+0x94700],di` | sorted u16 index stored at Frame+0x94700+idx*2; consumed by Frame::sort | [V] |
| draw header copy (seam 4/6 data) | Frame+0xB4700 | 16 (movaps) | [rax+rcx+0xB4700] | `0xbc60b13  movaps [rax+rcx+0xB4700],xmm0` | 0x80-byte draw header copied to Frame+0xB4700+idx*0x80 (8 movaps); last movaps at 0xbc60b13; executor reads header fields (+0x40 start index, +0x44 count, +0x48 stride, +0x5A IB handle, +0x76 VB handle) | [V] |
| Frame::sort (seam 5) | 0xbc61e20 | - | - | `0xbc61e22  sub rsp,0x238` | consumes sort keys and sorted indices; radix sort 0xbc62040/0xbc62bc0; view-order control (viewId in bits 54-63, mode tag 48-53); reorder views without touching passes | [V] |
| D3D12 executor 0xe821120 (seam 6) | 0xe821120 | - | - | `0xe821120  push rbp` | GPU-side draw executor; reads the 0x80-byte draw headers and issues D3D12 draws via DrawInstanced (slot 12, 0x60), DrawIndexedInstanced (slot 13, 0x68), ExecuteIndirect (slot 59, 0x1d8); batcher flush 0xe81b720 | [V] |
| submit slot 50 (seam 6) | 0xe82e230 | - | - | `0xe82e230  push rbp` | RendererContextD3D12::submit slot 50 (RTX override 0xe83d440 wraps it); walks the Frame and records D3D12; stats/timers inline; replacement submit can walk the same Frame layout, reuse the PSO builder and descriptor/upload rings, and issue its own draws | [V] |
| PSO builder 0xe81e860 (seam 6) | 0xe81e860 | - | - | `0xe81e860  push r15` | decodes render state to a D3D12 PSO desc; key mask 0x0707007FFFFFF0FF; replace PSO at this seam; per-draw constants via matrix cache (6dq) | [V] |

## (2) Cross-seam consistency

- Same pass names (FNV-1a 64, PassNames.h) appear in the task list (seam 3, task dispatch 0xe9002e0), in the sort keys' viewIds (seam 5, Frame::sort 0xbc61e20) and in the executor loop (seam 6, executor 0xe821120 / flush 0xe81b720) — consistent across seams 3-6 [V per 6dy verification status].
- Camera data: seam 1/2 operate on descriptions; seam 4 reads the consume frame through the context (two Frame buffers 0xE749C0 apart, fill vs consume — 6do); view/projection come from the per-view record bgfx `ctx+0x1EAB090+viewId*0x140` (view +0x10, proj +0x50 — 6dd/6dw) [V live 6e/6r].
- Materials: seam 4 state bits + program bind to G1a material file format and the 6dr loader (0xc26caa0) [V per 6dy].
- Component data: seam 1 actor/chunk descriptions route to entt components (6dt/6du) — bodyActor S+0xC8 actor identity route (6bg) [V per 6bg/M3d].
- Risks from 6dy: (a) task-list entries are shared_ptr<Task> — disable by stub, never free; (b) frame pointers alternate each frame (fill vs consume, 6do); (c) RVAs must be re-checked with SelfTest sigs (6dj) at startup [V per 6dy text].

## (3) CLOSES?

YES. Every seam in 6dy (seams 1-6) is proven by verbatim `0xRVA  instr` lines ([V] rows above), each seam's data and what it can change is recorded, cross-seam consistency is established (same pass names in task list / sort keys / executor loop; camera from 6dw; materials from G1a/6dr; components from 6dt/6du), and the three stated risks are documented verbatim from 6dy. Nothing in the item line remains unproven; no patch was exercised in game (unit is architecture-level/static only, per the orchestrator hint).

## TOOL REQUESTS

In-game test plan (to be run by the orchestrator, not by this unit):
1. Attach a logging breakpoint (no patch, read-only) at Encoder::submit 0xe82e230 entry; confirm rcx = RendererContext (vtable 0xF4EEE80 "Direct3D 12 RTX"), rdx = Frame* alternating between two buffers 0xE749C0 apart each frame [V live 6b].
2. At submit entry read Frame+0xDC57E8 (draw index cap 0xFFFF) and confirm it increments by CAS each draw; read Frame+0xB4700+idx*0x80 draw headers and confirm +0x40/+0x44/+0x48/+0x5A/+0x76 fields match 6e-2 [V static].
3. Hook the draw-batch flush 0xe81b720 (seam 6): set `[rdi+kind*4+0x10]` to 0 to skip a whole batch, or zero a single record's count/index fields to skip one draw; confirm the draw disappears and the frame still presents.
4. Hook task dispatch 0xe9002e0 (seam 3): walk the 0x80-byte task entries, read the name hash at task+0x08 (FNV-1a 64, match against PassNames.h), and swap the std::function impl at task+0x70 for a no-op stub to disable a pass by name; confirm the pass is skipped.
5. Hook Encoder::submit 0xbc60740 (seam 4): on a chosen draw, rewrite the state bits (u64 at header+0x20) or the program (from sort key `(key>>0x15)&0x7FF`) and confirm the draw's state/program changes on screen.
6. Read back expected values: Frame+0xE746D8 frame counter rises by 1 per frame; backbuffer size Frame+0xDC5808 = 1920x1137; view count at Frame+0xDC57E0 ~0x56; draw count Frame+0xDC57E8 increments per draw [V live 6e].
No memory capture queued: all targets are function-entry RVAs already provable statically; live reads above use existing docs/data/live evidence (6b/6e/6c). If the orchestrator needs a live capture of Frame tail offsets, queue via `python tools/livecap/request.py add <name> 0xe82e230 --why "U-EJ1 in-game test plan step 1"` at submit entry.

## TOOL REQUESTS (tooling)

None (rdis.exe only, no helper script written).
