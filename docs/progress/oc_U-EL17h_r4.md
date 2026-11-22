## NEXT
DONE

# Unit U-EL17h — L17h graphics options plumbing (OptionSync)

GOAL: close checklist item "L17h graphics options plumbing (OptionSync) pending" — prove the writer of source(r13)+0x1F0 (copied into ctx+0x1F0 by struct-copy 0x67C73D0 at endFrame 0x66232b0) and its link to upscaling_percentage/targetResolution, now via the passLookup-descriptor angle: descriptor +0x1F0 -> element +0x1F0 (sub_566cb20 at 0x566d04a/0x566d052) -> ctx +0x1F0 (0x67c791f) proven [V] in r4; remaining = who stores the descriptor +0x1F0.

Carried [V] facts (oc_U-Eratio.md, oc_U-EL17h r1-r3, re-verified with rdis before writing):
- `0x67c791f movss [rdx+0x1F0],xmm0` writes ctx+0x1F0 inside struct-copy 0x67C73D0 (rdx=ctx=r15).
- `0xbc8d34e movups xmm0,[r13+0x1F0]` TAAU body 0xbc8cfd0 consumes ctx+0x1F0 as render/display ratio.
- `0x662def4 call 0x67C73D0` endFrame copy-loop per 0x2B0 element (rdx=r13=source, rcx=r15=ctx); r13=[rsi+0x48] base (0x662d085), rdi=[rsi+0x50] end (0x662d089).
- `0x67c7917 movss xmm0,[rsi+0x1F0]` source+0x1F0 READ inside the copy — a read, not the writer.
- endFrame = vtable slot 18 of 0xf2bdeb0 (`18 +0x090 sub_66232b0 size 0xb3d0`), no direct callers (xref callers 0x66232b0 = []).
- endFrame full dump [0x66232b0,0x662e680): no [reg+0x1F0] object store; only stack [rbp+0x1F0] at 0x6628943 and pass-entry zero-store at 0x661241d/0x6612974.
- Options ctor 0x5b0c1b0: `0x5b3e799 movups xmm0,[0xF5E13CC]` upscaling_percentage default 0x32=50; `0x5b3ead0 movups xmm0,[0xF5850DE]` options.targetResolution; strings xref → refs=[] (table-registered); no instruction ties either option to source(r13)+0x1F0.
- Live data grep: docs/data/live/*.txt has NO hit for 0x67c791f, 0x67C73D0, 0x566cb20, 0x566d04a, 0x566d052, 0xbc8d34e, 0x66232b0, or the strings "upscaling_percentage"/"targetResolution" (_status.txt DONE; zero-hit captures: er5_clone_4c8a5b0[_b], l8b_resizetex_slot31[_b], oc_u_el6b_desc, el10b_lighting_desc).
- Capture queued: el17h_endframe_caller 0x66232b0 (endFrame entry; size 0x100, max 6) — ret= caller return RVA to name endFrame's indirect caller; see TOOL REQUESTS.

## Answer table (name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag)

| passLookup returns pass descriptor | 0x662ab42 | 5 (call) | endFrame 0x66232b0 | `0x662ab42  call 0x5ABA5C0` | rax = passLookup result = pass descriptor (descriptor base for the +0x1F0 chain); `0x662ab48  mov rsi,rax` copies it to rsi | [V] |
| pass item cursor / limit | 0x662abd1 / 0x662abd5 | 8 / 6 | [rsi+0x50] / [rsi+0x58] | `0x662abd1  mov rdi,[rsi+0x50]` / `0x662abd5  cmp rdi,[rsi+0x58]` | pass item vector cursor [rsi+0x50] vs limit [rsi+0x58]; stride 0x2B0 per element | [V] |
| descriptor->element copy call | 0x662abec / 0x662abef | 8 / 5 | - | `0x662abec  mov rcx,rdi` / `0x662abef  call 0x566CB20` | sub_566cb20(desc=rsi=pass descriptor, element=rcx=rdi=pass item) copies descriptor fields into each pass item | [V] |
| descriptor+0x1F0 read inside sub_566cb20 | 0x566d04a | 4 (movss) | [rsi+0x1F0] | `566d04a  movss xmm0,[rsi+0x1F0]` | pass descriptor+0x1F0 read — pure field copy, NOT a write of the descriptor | [V] |
| element+0x1F0 write inside sub_566cb20 | 0x566d052 | 4 (movss) | [rdx+0x1F0] | `566d052  movss [rdx+0x1F0],xmm0` | element+0x1F0 = descriptor+0x1F0 (ratio propagated into the pass item) | [V] |
| pass cursor advance | 0x662ad17 | 8 (add) | [rsi+0x50] | `0x662ad17  add qword ptr [rsi+0x50],0x2B0` | pass item cursor advances by 0x2B0 per element | [V] |
| element+0x1F0 zero-init streak | 0x6628fb0 | 16 (movups) | [rsi+0x1F0] | `0x6628fb0  movups [rsi+0x1F0],xmm6` | element/object +0x1F0 zero-init inside init streak ([rsi+0xC4]..[rsi+0x358] also xmm6), not the ratio value | [V] |
| source-array base load | 0x662627b | 8 (mov) | [r12+0x1328] | `0x662627b  mov r13,[r12+0x1328]` | r13 = source-array base = [[rbx+0x18]+0x1328]; `0x6626237  mov r12,[rbx+0x18]`; rbx = frame-package arg ([rbp+0x1998]) | [V] |
| copy-loop bound check | 0x662de92 | 6 (cmp) | - | `0x662de92  cmp r13,rdi` | loop exit when source cursor r13 == end rdi; stride 0x2B0 | [V] |
| source-array step | 0x662ded3 | 8 (add) | - | `0x662ded3  add r13,0x2B0` | r13 steps by 0x2B0 per source element | [V] |
| struct-copy call site | 0x662def4 | 5 (call) | endFrame 0x66232b0 | `0x662def4  call 0x67C73D0` | per-element copy source(r13)[0x2B0] -> ctx; setup `0x662def1  mov rdx,r13` / `0x662deea  lea rcx,[rbx-0x2B0]` | [V] |
| source+0x1F0 read inside struct-copy | 0x67c7917 | 4 (movss) | [rsi+0x1F0] | `0x67c7917  movss xmm0,[rsi+0x1F0]` | source element+0x1F0 READ (rsi=source=r13) — a read, not the writer | [V] |
| ctx+0x1F0 write inside struct-copy | 0x67c791f | 4 (movss) | [rdx+0x1F0] | `0x67c791f  movss [rdx+0x1F0],xmm0` | WRITER of ctx+0x1F0; value = source(r13)+0x1F0; rdx=ctx=r15 | [V] |
| sibling field writes | 0x67c78bc / 0x67c78cc | 4 (movss) | [rsi+0x1DC] / [rsi+0x1E0] | `0x67c78bc  movss xmm0,[rsi+0x1DC]` / `0x67c78cc  movss xmm0,[rsi+0x1E0]` | +0x1DC/+0x1E0 copied the same field-by-field way (ratio siblings) | [V] |
| TAAU ratio consume | 0xbc8d34e | 16 (movups) | [r13+0x1F0] | `0xbc8d34e  movups xmm0,[r13+0x1F0]` | TAAU body 0xbc8cfd0 consumes ctx+0x1F0 as render/display ratio (RenderResolution = ratio * dims, 0xbc8d34e..0xbc8d374) | [V] |
| upscaling_percentage default load | 0x5b3e799 | 16 (movups) | [0xF5E13CC] | `0x5b3e799  movups xmm0,[0xF5E13CC]` | Options ctor 0x5b0c1b0 loads upscaling_percentage default (0x32=50) for registration only — NO ratio computed | [V] |
| options.targetResolution default load | 0x5b3ead0 | 16 (movups) | [0xF5850DE] | `0x5b3ead0  movups xmm0,[0xF5850DE]` | Options ctor 0x5b0c1b0 loads options.targetResolution default for registration only — NO ratio computed | [V] |
| string "upscaling_percentage" | 0xf5e1458 | - | - | (string address; xref refs = []) | string exists; xref.py str -> no code refs (table-registered via Options ctor) | [V] |
| string "options.targetResolution" | 0xf5850de | - | - | (string address; xref refs = []) | string exists; xref.py str -> no code refs (table-registered via Options ctor) | [V] |
| endFrame vtable slot | vtable 0xf2bdeb0 +0x90 | - | - | `18 +0x090 sub_66232b0 size 0xb3d0` (rdis vt 0xf2bdeb0) | endFrame = BgfxFrameBuilder vtable slot 18; passLookup = ThreadLocalObject per-thread block getter 0x5ABA5C0 (BGFX_MAP.md 6gq) [I] | [V]/[I] |
| endFrame direct callers | xref callers 0x66232b0 | - | - | (xref.py callers -> empty) | endFrame has NO direct callers; entered only through the indirect vtable slot-18 call; caller not statically reachable | [V] |
| exe-wide [reg+0x1F0] write scan | - | - | fld 0x1F0 --w, 12315 accesses, complete list (whole .exe) | - | every [reg+0x1F0] write in the exe is a struct-field copy (`0x566d052  movss [rdx+0x1F0],xmm0` from [rsi+0x1F0]; `0x67c791f  movss [rdx+0x1F0],xmm0`; `0x5679980`, `0x6843e5d` from [rax+0xC], `0x660a21a` qword init), zeroing, or stack store — NONE computes the render/display ratio from upscaling_percentage/targetResolution | [V] |

## Mechanics established ([V] unless marked)

1. endFrame(rcx=builder [rbp+0x19D0], rdx=frame-package [rbp+0x1998]) obtains its pass descriptor via `0x662ab42  call 0x5ABA5C0` (passLookup, ThreadLocalObject per-thread block, BGFX_MAP.md 6gq [I]) and `0x662ab48  mov rsi,rax`; it walks pass items [rsi+0x50]..[rsi+0x58] stride 0x2B0 (`0x662abd1  mov rdi,[rsi+0x50]` / `0x662abd5  cmp rdi,[rsi+0x58]` / `0x662ad17  add qword ptr [rsi+0x50],0x2B0`).
2. Per pass item it calls sub_566cb20 at `0x662abef  call 0x566CB20` (`0x662abec  mov rcx,rdi`), which field-copies the descriptor into the item including `566d04a  movss xmm0,[rsi+0x1F0]` / `566d052  movss [rdx+0x1F0],xmm0` — descriptor+0x1F0 -> item+0x1F0, a pure copy.
3. After the pass loop, endFrame builds the source array from [[rbx+0x18]+0x1328] (`0x662627b  mov r13,[r12+0x1328]`; `0x6626237  mov r12,[rbx+0x18]`) and its copy loop `0x662deea  lea rcx,[rbx-0x2B0]` / `0x662def1  mov rdx,r13` / `0x662def4  call 0x67C73D0` / `0x662ded3  add r13,0x2B0` / `0x662de92  cmp r13,rdi` copies each source element (incl. +0x1F0) into ctx.
4. Inside struct-copy 0x67C73D0, `0x67c7917  movss xmm0,[rsi+0x1F0]` reads source+0x1F0 and `0x67c791f  movss [rdx+0x1F0],xmm0` writes ctx+0x1F0 (rdx=ctx=r15); sibling fields +0x1DC/+0x1E0 copied identically.
5. TAAU body 0xbc8cfd0 consumes `0xbc8d34e  movups xmm0,[r13+0x1F0]` as render/display ratio — confirming ctx+0x1F0 = the ratio.
6. The whole chain is therefore: pass descriptor+0x1F0 -> source element+0x1F0 (sub_566cb20 copy) -> ctx+0x1F0 (struct-copy 0x67c791f) -> TAAU (0xbc8d34e). No step computes anything; every step is a field copy.
7. Options ctor 0x5b0c1b0 registers upscaling_percentage (`0x5b3e799  movups xmm0,[0xF5E13CC]`, default 0x32=50) and options.targetResolution (`0x5b3ead0  movups xmm0,[0xF5850DE]`) via sub_9C4220/sub_5BC0530 only — no ratio computed, no instruction ties either option to source(r13)+0x1F0.
8. Both option strings have xref refs = [] (table-registered). Exhaustive fld 0x1F0 --w (12315 accesses, whole exe): every [reg+0x1F0] write is a struct-field copy (0x566d052, 0x67c791f, 0x5679980, 0x6843e5d-from-[rax+0xC], 0x660a21a-qword-init), zeroing, or stack store — none computes the ratio.
9. endFrame = BgfxFrameBuilder vtable slot 18 (vt 0xf2bdeb0 +0x90, `18 +0x090 sub_66232b0 size 0xb3d0` [V]); xref.py callers 0x66232b0 = [] — no direct callers, indirect call only, so the code that builds/fills the pass descriptor's +0x1F0 (endFrame's caller) is not statically reachable.

## Answer to the pending items

- Chain descriptor+0x1F0 -> element+0x1F0 -> ctx+0x1F0 -> TAAU: PROVEN [V] (rows above; r4 chain confirmed verbatim).
- source(r13)+0x1F0 writer: NOT located — it is endFrame's caller that fills the pass descriptor / source array; endFrame itself only propagates +0x1F0 by copy (full endFrame dump [0x66232b0,0x662e680) contains no [reg+0x1F0] object store except zero-init `0x6628fb0  movups [rsi+0x1F0],xmm6` and stack [rbp+0x1F0]).
- Link of source+0x1F0 to upscaling_percentage/targetResolution: NOT proven — options are registration-only in Options ctor 0x5b0c1b0, strings have no code refs, and no [reg+0x1F0] write in the exe computes a ratio.

## CLOSES?

NO

Single blocking fact: the writer of the pass descriptor's +0x1F0 (i.e. of source(r13)+0x1F0, the value endFrame's struct-copy `0x67c791f  movss [rdx+0x1F0],xmm0` propagates into ctx+0x1F0) and its link to upscaling_percentage/targetResolution were not located. endFrame 0x66232b0 is BgfxFrameBuilder vtable slot 18 with no direct callers (xref.py callers = []), so its caller — which builds/fills the pass descriptor — is statically unreachable; an exe-wide [reg+0x1F0] write scan (fld 0x1F0 --w, 12315 accesses, complete) shows only copies/zeroing/stack stores, no ratio computation; both option strings have xref refs=[]. Closing YES requires identifying endFrame's indirect caller and tracing how it writes descriptor+0x1F0 from the upscaling settings.

## TOOL REQUESTS

CAPTURE REQUESTED el17h_endframe_caller — endFrame entry 0x66232b0 capture queued (size 0x100, max 6); pending on the orchestrator's live run. Expected: ret=caller return RVA names endFrame's indirect caller (the frame-graph builder that builds/fills the passLookup descriptor), RCX=builder and RDX=frame-package dumps show the argument objects; after it returns, statically scan that caller for a [reg+0x1F0] store and the upscaling_percentage/targetResolution link.

