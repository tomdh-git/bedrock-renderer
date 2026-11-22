## NEXT
DONE

UNIT U-EL10c — Close checklist item L10c: viewport and render-resolution selection, dynamic resolution pending.
Output file: docs/progress/oc_U-EL10c.md (only file for this unit).
Must run `python tools/delegate.py check docs/progress/oc_U-EL10c.md` (exit 0), then set line after "## NEXT" to DONE.

GOAL (verbatim from checklist): L10c viewport and render-resolution selection, dynamic resolution pending | prior unit oc_U-Eratio.md (9 rows OK): NO; ctx+0x1F0 store 0x67c791f and TAAU read 0xbc8d34e proven, but source(r13)+0x1F0 writer and link to upscaling_percentage/targetResolution not found (endFrame 0x66232b0 has no direct callers).

ORCHESTRATOR HINT (2026-11-22 r3, treated as verified): writer of source(r13)+0x1F0 still not found statically. endFrame 0x66232b0 has no direct callers: it is called through a vtable/function pointer, so a store scan from the struct-copy 0x67C73D0 backwards needs the vtable owner. Angles tried per hint: (1) rdis vt/vslot for the object whose slot holds 0x66232b0; (2) scan BgfxFrameBuilder's other methods for a float/int store at +0x1F0; (3) settings readers of upscaling_percentage by string xref, follow the stored field.

INPUT DATA: docs/progress/oc_U-Eratio.md (prior unit, 9 rows OK, CLOSES? NO). Its proven [V] core is re-quoted below; this unit re-verified it and ran the exhaustive store scans the hint requires.

------------------------------------------------------------
VERIFIED [V] findings this unit (disassembly of Minecraft.Windows.exe 1.26.62.01, image base, RVAs):

1) Vtable owner of the slot holding 0x66232b0 — `rdis vt 0xf2bdeb0` printed:
   18 +0x090  sub_66232b0  size 0xb3d0  push rbp
   So endFrame 0x66232b0 is BgfxFrameBuilder vtable slot 18 (+0x90); vtable owner = BgfxFrameBuilder [V].

2) endFrame copy loop re-read (0x662da00–0x662e263):
   `0x662db9f  mov r15,[rax+0x70]`            ; r15 = ctx dst base = rdx_arg+0x70 (rax = [rbp+0x1998] = rdx arg)
   `0x6626237  mov r12,[rbx+0x18]`
   `0x6626273  mov r14,[r12+0x1320]`          ; r14 = source end
   `0x662627b  mov r13,[r12+0x1328]`          ; r13 = source-array base = [[rbx+0x18]+0x1328]
   Loop 0x662de92–0x662def4: per element (stride 0x2B0) call 0x67C73D0(dst=rcx=r15+k*0x2B0, src=rdx=r13+k*0x2B0), then tail stores [r13+0x290],[r13+0x298],[r13+0x2A0]; cmp r13,rdi exits when source exhausted.
   So ctx+0x1F0 = element[0]+0x1F0 copied from source-array element[0]+0x1F0. The source-array CONTENTS (incl. +0x1F0 ratio) are written upstream of endFrame — endFrame only propagates them.

3) ctx+0x1F0 writer (re-confirmed in this unit's full-exe scan): `0x67c791f  movss [rdx+0x1F0],xmm0` inside struct-copy 0x67C73D0; xmm0 = [rsi+0x1F0] = source(r13)+0x1F0; rdx = ctx [V]. TAAU read `0xbc8d34e  movups xmm0,[r13+0x1F0]` confirms ctx+0x1F0 = render/display ratio [V].

------------------------------------------------------------
NEGATIVE SCANS [V] (exhaustive, whole .exe, per hint):

4) `fld 0x1F0 --w` (12315 accesses, complete list) — every write to [reg+0x1F0] in the exe:
   - struct-field copies only (propagate values computed elsewhere, none computes a ratio): `0x566d052  movss [rdx+0x1F0],xmm0` from [rsi+0x1F0]; `0x5679980  movss [rax+0x1F0],xmm0` from [rsi+0x1F0]; `0x67c791f  movss [rdx+0x1F0],xmm0` from [rsi+0x1F0]; `0x6843e5d  movss [rsi+0x1F0],xmm0` from [rax+0xC] (sub_6806910 is a texture-variant lookup, unrelated); `0x660a21a  mov [r13+0x1F0],rax` (qword copy [r13+0x1E8]->[r13+0x1F0], object init).
   - zeroing: mov [reg+0x1F0],0 / movaps [reg+0x1F0],xmm6=0 / mov byte [reg+0x1F0],0 and similar stores.
   - stack: [rbp+0x1F0] / [rsp+0x1F0] stores only.
   - unrelated: `0xbc59468  movss [r15+0x1F0],xmm0` (light clustering sub_bc57460).
   NO instruction computes the render/display ratio (or anything from upscaling_percentage/targetResolution) into [reg+0x1F0].

5) `fld 0x1E8 --w` — 16-byte stores at +0x1E8 (which cover +0x1F0..+0x1F3): none computes a ratio (stack/graphics math only).

6) BgfxFrameBuilder's other vtable methods (from vt 0xf2bdeb0): +0x1F0 writes found only at `0x661241d  movdqu [rsi+0x1F0],xmm6` (xmm6=0) and `0x6612974  mov qword ptr [rdx+0x1F0],0` in slot 11 sub_66117f0 (zeroing), and `0x6620615  mov [rbp+0x1F0],rsi` (stack) in slot 17 sub_661f200 (startFrame). NO float/int store at +0x1F0 computing the ratio [V].

7) Settings angle: strings upscaling_percentage (0xf5e13cc/0xf5e1458) and options.targetResolution (0xf5850de) have NO direct code refs (xref.py str = []); they are only loaded by absolute address in Options ctor 0x5b0c1b0 for registration via sub_9C4220/sub_5BC0530 (default upscaling_percentage = 0x32 = 50). No settings reader writes a computed ratio to +0x1F0 (per scan 4 above).

------------------------------------------------------------
EVIDENCE TABLE (offset | size | site | instr | meaning):

| offset    | size     | site                              | instr                                              | meaning                                               |
| 0x5b3e799 | 16 (movups)|Options ctor 0x5b0c1b0            | `0x5b3e799  movups xmm0,[0xF5E13CC]`                | [V] registers upscaling_percentage (no ratio computed) |
| 0x5b3ead0 | 16 (movups)|Options ctor 0x5b0c1b0            | `0x5b3ead0  movups xmm0,[0xF5850DE]`                | [V] registers options.targetResolution (no ratio computed) |
| 0x662627b | 8        | endFrame 0x66232b0 (gap 0x6626100)  | `0x662627b  mov r13,[r12+0x1328]`                  | [V] source-array base r13 = [r12+0x1328] = [[rbx+0x18]+0x1328] |
| 0x662deea | 8        | endFrame call setup                 | `0x662deea  lea rcx,[rbx-0x2B0]`                   | [V] rcx = ctx dst base (struct-copy arg 1)            |
| 0x662def1 | 8        | endFrame call setup                 | `0x662def1  mov rdx,r13`                           | [V] rdx = source-array base r13 (struct-copy arg 2)   |
| 0x662def4 | 5        | endFrame call site                  | `0x662def4  call 0x67C73D0`                        | [V] endFrame invokes struct-copy per source element   |
| 0x67c78c4 | 4 (movss)| struct-copy 0x67C73D0               | `0x67c78c4  movss [rdx+0x1DC],xmm0`                | [V] sibling field write ctx+0x1DC                     |
| 0x67c78d4 | 4 (movss)| struct-copy 0x67C73D0               | `0x67c78d4  movss [rdx+0x1E0],xmm0`                | [V] sibling field write ctx+0x1E0                     |
| 0x67c791f | 4 (movss)| struct-copy 0x67C73D0               | `0x67c791f  movss [rdx+0x1F0],xmm0`                | [V] writer store: writes ctx+0x1F0 (the ratio), value = source(r13)+0x1F0 |
| 0xbc8d34e | 16 (movups)|TAAU body 0xbc8cfd0                 | `0xbc8d34e  movups xmm0,[r13+0x1F0]`               | [V] confirms ctx+0x1F0 is read as render/display ratio|

------------------------------------------------------------
CLOSES? — NO

Single blocking fact:
The writer of source(r13)+0x1F0 — i.e. who computes the render/display ratio that endFrame's struct-copy (0x67c791f) propagates into ctx+0x1F0 — was not found statically, and neither was its link to upscaling_percentage/targetResolution:
- source(r13) = [[rbx+0x18]+0x1328] is loaded inside endFrame at `0x662627b  mov r13,[r12+0x1328]`; the array's contents are written upstream of endFrame and that writer was not located.
- endFrame 0x66232b0 has no direct callers: it is BgfxFrameBuilder vtable slot 18 (vt 0xf2bdeb0+0x90 -> 0x66232b0 [V]), invoked only indirectly, so the caller chain to the array builder cannot be followed statically.
- Exhaustive write scans `fld 0x1F0 --w` (12315 accesses, complete) and `fld 0x1E8 --w` show every [reg+0x1F0] write in the exe is a struct-field copy, zeroing, or stack store — none computes the ratio from upscaling settings. The settings strings (0xf5e13cc/0xf5e1458/0xf5850de) have no code refs (registration only in Options ctor 0x5b0c1b0).

Until the source(r13)+0x1F0 writer and its link to upscaling_percentage/targetResolution are found, CLOSES? cannot be YES.

------------------------------------------------------------
TOOL REQUESTS: None — rdis.exe vt/dis/fld scans and xref.py provided all evidence; no new scripts written.
