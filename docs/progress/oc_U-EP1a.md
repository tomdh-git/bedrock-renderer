## NEXT
DONE

UNIT U-EP1a — P1a Seam map (BGFX_MAP 8a). Checklist wording: "P1a Seam map written: choose between submit takeover (0xe82e230), per-draw veto at executor flush 0xe821120, and custom item (submitCustom, key bit 53); document used and unused seams — BGFX_MAP 8a".

Source base: Minecraft Bedrock 1.26.62.01, RVAs relative to image base. Static analysis only (game closed; exe treated as data). Every `0xRVA  instr` line below is copied verbatim from rdis output of the exe and re-checked with tools/sigs/verify_oc.py via tools/delegate.py check. Tags: [V] = seen in disassembly (RVA cited), [I] = inferred, [?] = open/not proven.

## What changed (paths)

- Created: docs/progress/oc_U-EP1a.md — the only file this unit touches.
- No source, hook registration, CMake, or Sigs.json changes. This unit is a seam map (decision note), not code. No build, no commit, no game launch/attach. Nothing in this unit requires the game or a build; all proof is static.

## Seam map — BGFX_MAP 8a replacement seams (P1a)

Answer / choice: for a per-draw veto (read or modify a draw record before the GPU), the proven seam is the executor's batched flush 0xe81b720 inside draw executor 0xe821120 — every draw record is materialized at Frame+0x8B4700+idx*0x540 in the executor loop and the flush is called from that loop. For adding our own render-thread D3D12 work, the native seam is Encoder::submitCustom (key bit 53) at 0xbc61560, invoked as fn(user,&ctx) from executor path 0xe822400 — mechanism proven [V], untested in game [?]. For whole-frame replacement, the seam is submit takeover at 0xe82e230, entered only through the RTX override 0xe83d440 — heavier, no replacement written yet.

| name | rva or offset | size | proof `0xRVA  instr` | tag |
| submit takeover: RendererContextD3D12::submit fn entry (base vtable slot 50) | 0xe82e230 | 0x4d91 | `0xe82e273  cmp dword ptr [rcx+0x19F88],5` (queue-state guard, jl aborts submit); `0xe82e34c  mov r9d,[rsi+0xE746D8]` (frame counter); `0xe82e353  mov rdx,[rdi+0x19F58]` (resource tables) | [V] |
| submit takeover: entry control — submit has exactly one xref, from the RTX override | 0xe83d440 | 0x381 | `0xe83d4d6  call 0xE82E230` (wrapper calls base submit); `0xe83d4b5  movups xmm0,[rdx+0xE746E0]` (16-byte frame-params copy into RTX state) | [V] |
| vtable proof: base RendererContextD3D12 vtable 0xF4ED2D0 slot 50 (+0x190) = submit | 0xF4ED2D0 | - | rdis vt output: `50 +0x190 sub_e82e230 size 0x4d91` | [V] |
| vtable proof: live RTX vtable 0xF4EEE80 slot 50 (+0x190) = override wrapper 0xe83d440 (live object uses this vtable) | 0xF4EEE80 | - | rdis vt output: `50 +0x190 sub_e83d440 size 0x381` | [V] |
| per-draw veto seam: draw executor entry (per-draw consumer; executor does not itself issue D3D12 draw calls — draws emit via the DrawBatcher flush) | 0xe821120 | 0xc3c3 | `0xe821120  push rbp` (fn entry; 1 xref, from wrapper 0xe83c390) | [V] |
| per-draw veto seam: executor item-loop head — sort key load and class/bit-53 decode | 0xe8221f5 | - | `0xe822220  mov rdx,[rdx+rax*8+0x14700]` (key = Frame sortKeys[pos]); `0xe82222b  mov r8,0x30000000000000` (class mask bits 52-53); `0xe822238  mov r8,0x20000000000000` (bit-53 mask); `0xe822267  jne 0xE822400` (bit-53-only branches to custom path) | [V] |
| per-draw veto seam: draw record materialization in executor loop (Frame+0x8B4700, stride 0x540 per render item) | 0xe8222c0 | - | `0xe8222c7  lock inc dword ptr [rdx+0x4C]` (per-item draw stat); `0xe8222d2  movzx r8d,word ptr [rdx+rax*2+0x94700]` (sorted slot id); `0xe8222e2  imul rsi,r8,0x540` (0x540-byte RenderDraw record at Frame+0x8B4700+idx*0x540) | [V] |
| per-draw veto seam: batched DrawBatcher flush — all normal draws pass here; hook point for read/modify before GPU | 0xe81b720 | 0x803 | `0xe81b720  push r15` (flush entry, 7 xrefs); `0xe822e4e  call 0xE81B720`; `0xe822e6b  call 0xE81B720` (executor call sites) | [V] |
| executor invocation: render-thread job wrapper calls executor per job slice (4 jobs per submit observed) | 0xe83c390 | - | `0xe83c430  call 0xE821120` (wrapper calls executor) | [V] |
| custom item seam: Encoder::submitCustom(viewId, fn, user) — allocates draw index by CAS (cap 0xFFFE), stores fn/user payload, sets sort key bit 53 | 0xbc61560 | 0x372 | `0xbc615ea  lock cmpxchg [rcx+0xDC57E8],r11d` + `0xbc615ff  cmp edi,0xFFFE` (draw-index CAS at frame+0xDC57E8, cap 0xFFFE); `0xbc61645  mov [rsi+0x100],r8` / `0xbc6164c  mov [rsi+0x108],r9` (fn/user payload stored); `0xbc61673  lock xadd [rax+rcx*4+0x1EAAC60],edx` (per-view sequence counter); `0xbc61697  mov rcx,0x20000000000000` / `0xbc616a1  or rcx,rax` (key bit 53 = 0x20000000000000 set); `0xbc616aa  mov [rax+r15*8+0x14700],rcx` (sort key at Frame+0x14700+idx*8); `0xbc616b5  mov [rax+r15*2+0x94700],di` (slot id at Frame+0x94700+idx*2); `0xbc6174d  movaps xmm0,[r14]` / `0xbc61751  movaps [rax+rcx+0xB4700],xmm0` (16-byte {fn,user} copied to Frame+0xB4700+idx*0x80 header slot) | [V] |
| custom item seam: executor bit-53 path invokes fn(user,&ctx) on the render thread in view order | 0xe822400 | - | `0xe822407  lock inc dword ptr [r8+rdx*4+0x4C]` (custom-item stat); `0xe822426  mov rax,[r8+rdx]` (fn = slot[0]); `0xe82245d  mov rcx,[rdx+8]` (user = slot[8]); `0xe822468  call qword ptr [0xF99FFA0]` (fn(user,&ctx) via CFG dispatch thunk) | [V] |

## Used vs unused seams (BGFX_MAP 8a, items 1-5)

1. Submit takeover (0xe82e230): USED by the engine itself every frame — submit runs once per frame (entered only via RTX override 0xe83d440, unique xref [V], live vtable slot 50 [V]); UNUSED as a replacement seam — no submit replacement is written in this codebase. [V for mechanism, I for per-frame cadence per BGFX_MAP 6ac hit counts]
2. Per-draw veto/rewrite at executor flush (0xe81b720 within 0xe821120): USED by the engine every frame — executor calls the flush from its item loop (call sites 0xe822e4e/0xe822e6b [V]); the veto hook point is proven and hook-ready; an in-game test of a veto is still outstanding (M3e). [V]
3. Custom render item (submitCustom, key bit 53, 0xbc61560): seam EXISTS and is proven [V] (key bit 53 set, fn(user,&ctx) via CFG thunk [V]); UNUSED in observed scenes — executor path 0xe822400 is stat-counted but no observed frame queued custom items (bit 53 clear on all 1106 keys of an observed 1106-item frame [V live, BGFX_MAP 6io]); PassTask code queues `encoder->submitCustom(...)` per SDK source (Tasks.h:61) [I], untested in game [?]; custom-item ctx layout (0x18 bytes, first field) still partly inferred [?].
4. Pass control via TaskDispatch + dragon/Tasks.h: written, never built or run [I, BGFX_MAP 8a#4 / checklist P1b].
5. Whole-frame takeover (frame-level substitute for submit): no replacement written [?] — submit takeover seam (item 1) is the entry point for it.

## CLOSES?
YES — the P1a seam map is written on disk (docs/progress/oc_U-EP1a.md): all three candidate seams (submit takeover 0xe82e230; per-draw veto at executor flush 0xe821120 / flush 0xe81b720; custom item submitCustom key bit 53 at 0xbc61560) are proven with verbatim [V] instruction rows, vtable slot-50 ownership of submit is proven [V] for both base and live RTX vtables, and used vs unused status is documented for every BGFX_MAP 8a seam with [V]/[I]/[?] tags. Open items that are not part of this map's wording: custom-item 0x18-byte ctx layout ([?], M3f), in-game veto test ([], M3e), and writing an actual submit replacement ([], whole-frame takeover) — flagged, not blocking.

## DECISION (orchestrator, 2026-11-21, from the [V] rows above)
Primary seam: the per-draw veto/rewrite at the executor flush 0xe81b720 (hook point proven and hook-ready, runs every frame, actor-to-draw identification already solved by M3d via record+0x80 startInstance). Secondary, only when a whole-frame replacement is needed: the submit takeover at 0xe82e230 through the RTX override 0xe83d440 (slot 50), which owns every draw record at Frame+0xB4700 but needs the full contract of N1e/N2a (retire, reset slot 60, TDR slot 7). Reserve the custom item seam (submitCustom, key bit 53) for injecting extra draws (overlays, chams passes) once its 0x18-byte context layout is decoded (M3f); it is unused in observed scenes.
