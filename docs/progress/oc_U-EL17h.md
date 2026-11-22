## NEXT
DONE — both hint angles exhausted; no source(r13)+0x1F0 writer statically provable; CLOSES=NO

# Unit U-EL17h — L17h graphics options plumbing (OptionSync)

GOAL: close checklist item "L17h graphics options plumbing (OptionSync) pending" — prove the writer of source(r13)+0x1F0 (the value copied into ctx+0x1F0 by struct-copy 0x67C73D0 at endFrame 0x66232b0) and its link to upscaling_percentage / targetResolution.

Prior [V] facts carried in (oc_U-Eratio.md, oc_U-EL17h_r1/r2): writer store `0x67c791f movss [rdx+0x1F0],xmm0` writes ctx+0x1F0 (rdx=ctx=r15); TAAU read `0xbc8d34e movups xmm0,[r13+0x1F0]` consumes ctx+0x1F0 as render/display ratio; endFrame calls struct-copy 0x67C73D0 at `0x662def4 call 0x67C73D0` per 0x2B0 element (setup `0x662def1 mov rdx,r13` / `0x662deea lea rcx,[rbx-0x2B0]`); r13=[rsi+0x48] source base (0x662d085), rdi=[rsi+0x50] end (0x662d089); `0x67c7917 movss xmm0,[rsi+0x1F0]` reads source+0x1F0 inside the copy (a READ); 0x67C73D0's only caller is endFrame (3 sites); endFrame has no direct callers (xref callers 0x66232b0 = []).

Investigation performed this unit (all verbatim lines re-verified against the exe with rdis dis immediately before writing):
- Angle 1 (orchestrator hint): rdis vt 0xf2bdeb0 confirms slot 18 (+0x90) = sub_66232b0 endFrame size 0xb3d0 — BgfxFrameBuilder vtable. All other 31 slots dumped (full listings for 0x67ec9e0, 0x6619c10, 0x6619e60, 0x661f200, 0x66117f0, 0x6610a70-0x6611260, 0x66182d0, 0x661a400-0x661f180, 0x6622aa0, 0x6639450-0x663a390, 0x6619c20, 0x661a2f0, plus trivial slots by inspection). The only [obj+0x1F0] stores in the whole class are two zero-initialization stores inside slot 11 (0x66117f0): no computed render/display-ratio write anywhere.
- Angle 2: xref str "upscaling_percentage" (0xf5e1458) → refs=[]; xref str "options.targetResolution" (0xf5850de) → refs=[] — both table-registered (Options ctor 0x5b0c1b0: `0x5b3e799 movups xmm0,[0xF5E13CC]` default 0x32=50, `0x5b3ead0 movups xmm0,[0xF5850DE]`), no instruction ties either option to source(r13)+0x1F0.

## Answer table

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| source(r13)+0x1F0 read inside struct-copy 0x67C73D0 | 0x67c7917 | 4 | [rsi+0x1F0] | `0x67c7917  movss xmm0,[rsi+0x1F0]` | source element (rsi==r13)+0x1F0 read per 0x2B0 element — this is a READ, not the writer of source+0x1F0 | [V] |
| ctx+0x1F0 write inside struct-copy 0x67C73D0 | 0x67c791f | 4 | [rdx+0x1F0] | `0x67c791f  movss [rdx+0x1F0],xmm0` | ctx+0x1F0 written from source+0x1F0 (rdx=ctx=r15) | [V] |
| TAAU ratio consume, body 0xbc8cfd0 | 0xbc8d34e | 16 | [r13+0x1F0] | `0xbc8d34e  movups xmm0,[r13+0x1F0]` | ctx+0x1F0 consumed as render/display ratio (RenderResolution = ratio * dims) | [V] |
| endFrame copy-loop call site | 0x662def4 | 5 | - | `0x662def4  call 0x67C73D0` | endFrame 0x66232b0 calls struct-copy per element; 0x67C73D0's only caller is endFrame (sites 0x662ba52, 0x662cd25, 0x662def4) | [V] |
| endFrame = vtable slot 18, no direct callers | vtable 0xf2bdeb0 slot 18 (+0x90) | - | - | - | `18 +0x090 sub_66232b0 size 0xb3d0` (rdis vt 0xf2bdeb0); xref.py callers 0x66232b0 = [] — indirect/vtable call, caller not statically reachable | [V] |
| vtable-class slot 11 (0x66117f0): [rsi+0x1F0] store | 0x661241d | 16 | [rsi+0x1F0] | `0x661241d  movdqu [rsi+0x1F0],xmm6` | only object +0x1F0 store found scanning every other method of the class — whole-object zero-initialization, not the source ratio writer | [V] |
| vtable-class slot 11 (0x66117f0): [rdx+0x1F0] store | 0x6612974 | 8 | [rdx+0x1F0] | `0x6612974  mov qword ptr [rdx+0x1F0],0` | zero-store during object init, not a computed render/display ratio | [V] |
| string "upscaling_percentage" | 0xf5e1458 | - | - | - | xref str → refs=[]; option registered through a table, no direct code refs | [V] |
| string "options.targetResolution" | 0xf5850de | - | - | - | xref str → refs=[]; option registered through a table, no direct code refs | [V] |

## CLOSES?

NO

Single blocking fact: source(r13)+0x1F0 is only ever READ (`0x67c7917 movss xmm0,[rsi+0x1F0]`) and copied into ctx+0x1F0 (`0x67c791f movss [rdx+0x1F0],xmm0`) inside endFrame; the source array is a caller-built argument of endFrame (base [rsi+0x48] at `0x662d085 mov r13,[rsi+0x48]`, end [rsi+0x50] at `0x662d089 cmp rdi,[rsi+0x50]`), so its filler — the writer of source(r13)+0x1F0 — is endFrame's INDIRECT caller (vtable slot 18 of 0xf2bdeb0, xref callers = []), which is not statically reachable. Full-method scan of the vtable class found no computed [obj+0x1F0] store (only zero-stores `0x661241d movdqu [rsi+0x1F0],xmm6` and `0x6612974 mov qword ptr [rdx+0x1F0],0`), and xref str shows upscaling_percentage (0xf5e1458) and options.targetResolution (0xf5850de) both refs=[] with no instruction tying either option to source+0x1F0. Closing YES requires a live capture of endFrame's indirect caller or an orchestrator-provided caller RVA.

## TOOL REQUESTS

None — used rdis vt/dis, python tools/sigs/xref.py str, python tools/sigs/dumplist.py; no helper script written.
