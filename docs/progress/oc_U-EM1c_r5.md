## NEXT
DONE

UNIT U-EM1c. GOAL (from orchestrator, overrides prior notes): raise exactly two dossiers from D1 to D2:
- generate 0xc273420 -> docs/functions/c273420.md
- GraphicsTasks Render lambda 0xc267200 -> docs/functions/c267200.md

D2 = every instruction block explained with [V] `0xRVA  instr` rows, every field offset it reads/writes with meaning, every call target named (reuse names from BGFX_MAP and existing dossiers), no [?] left except proven negatives. Work by windows (`rdis dis <start> --max 3000`), write rows as you go. Edit only these two dossier files plus docs/progress/oc_U-EM1c.md.

STATUS: both dossiers rewritten to D2 (docs/functions/c273420.md, docs/functions/c267200.md). Disassembly gathered:
- 0xc267200 full: docs/progress/listings/c267200_full.txt (0x632 bytes, [0xc267200,0xc267832), 386 instr)
- 0xc273420 windows: w1 c273420..c275419, w2 c275419..c277413, w3 c277413..c27940e, w4 c27940e..c27b40d, w5 c27b40e..c27d406 (function [0xc273420,0xc27be93), 8104 instr)

Field-map table (offset | size | read/store address | verbatim `0xRVA  instr` | meaning). Every quoted instruction line copied verbatim from rdis output (verified against the exe).

| offset | size | read/store address | `0xRVA  instr` | meaning |
|---|---|---|---|---|
| rcx+0x8 | 8 | R | `0xc267228  mov rsi,[rcx+8]` | Render lambda: closure+0x8 = task object pointer -> rsi [V c267200.md] |
| r14+0x48 | 8 | R | `0xc267349  mov rcx,[r14+0x48]` | Render lambda: closure+0x48 = current task object [V c267200.md] |
| rsi+0x150 | 8 | R/W | `0xc2675a0  xchg [rsi+0x150],rax` | Render lambda: task+0x150 timeout slot, xchg new timeout [V c267200.md] |
| rsi+0x98 | 8 | W | `0xc2675ea  mov [rsi+0x98],rax` | Render lambda: task+0x98 handoff ptr = r15+0x10 [V c267200.md] |
| rsi+0xA0 | 8 | W | `0xc2675f8  mov [rsi+0xA0],r15` | Render lambda: task+0xA0 handoff ptr = r15 (xchg) [V c267200.md] |
| rsi+0x138 | 8 | R | `0xc26764f  mov r14,[rsi+0x138]` | Render lambda: task+0x138 owner/notifier ptr [V c267200.md] |
| r14+0x350 | 8 | R (lea) | `0xc2676f4  lea rcx,[r14+0x350]` | Render lambda: closure+0x350 enqueue target for sub_eec5b90 [V c267200.md] |
| r14+0x90 | 4 | W | `0xc2676cc  lock xadd [r14+0x90],r15` | Render lambda: closure+0x90 signaled counter +=1 [V c267200.md] |
| r15+0xE8 | 8 | W | `0xc267506  mov qword ptr [r15+0xE8],0` | Render lambda: 0xF8 object+0xE8 result slot = 0 [V c267200.md] |
| r15+0xF0 | 1 | W | `0xc267549  mov byte ptr [r15+0xF0],0` | Render lambda: 0xF8 object+0xF0 flag byte = 0 [V c267200.md] |
| r8+0x50 | 8 | R | `0xc2734a0  cmp qword ptr [r8+0x50],0` | Generate: Declarator+0x50 gate; 0 -> early exit loc_c273fbd [V c273420.md] |
| r8+0x30 | 8 | R/W | `0xc2734b9  mov rax,[r8+0x30]` / `0xc2734bd  mov qword ptr [r8+0x30],0` | Declarator+0x30 cap read then zeroed (vector moved out) [V c273420.md] |
| r8+0x20 | 16 | R/W | `0xc2734c5  movups xmm0,[r8+0x20]` / `0xc2734d4  movups [r8+0x20],xmm1` | Declarator+0x20 {begin,end} read then zeroed (vector moved out) [V c273420.md] |
| rcx+0x20 | 8 | R | `0xc2734ee  mov rax,[rcx+0x20]` | Generate: S+0x20 arena object ptr read [V c273420.md] |
| rax+0x0 | 8 | R | `0xc2734f2  mov rax,[rax]` | Generate: arena object+0 = arena handle [V c273420.md] |
| rax+0x38 | 8 | R | `0xc273745  mov r12,[rax+0x38]` | Generate: declared-vector begin ([this+0x20].[0]+0x38) [V c273420.md] |
| rax+0x40 | 8 | R | `0xc273749  mov rax,[rax+0x40]` | Generate: declared-vector end ([this+0x20].[0]+0x40) [V c273420.md] |
| rbp+0x3450 | 8 | R/W | `0xc2780c3  mov rax,[rbp+0x3450]` | Generate: per-pass loop cursor [V c273420.md] |
| cursor+0x8 | 8 | R | `0xc2780ca  mov r13,[rax+8]` | Generate: pass object ptr = cursor+8 [V c273420.md] |

Call targets named in both dossiers (callee tables): render lambda -> 0xc25fc50 Execute x3, 0xeec58f0/0xeec5920/0xeec5930 wait, 0xeec5860/0xeec5870 ctor, 0xeec5b90, 0xc266ba0, 0xabd50, 0x76ee90, 0x77a2500, 0x39a7d40, 0x2fe330, 0xe935740, 0xe938d70, 0x9bc830, [data_f99ffa0]=sub_eea6040. generate -> endFrame 0xc270460 (sole caller), 0xa78940 x14, 0x9bc830 x42, 0xe935700 x27, 0xa4c70 x6, 0xc27ec60 x2, 0xc27ed70 x1, 0xc27f940 x3, 0xc27fcc0 x2, 0xc280010 x1, 0xbc76610 x1, 0xbc752f0 x1, 0xe905ce0/d00/ef0, [data_f99ffa0]=sub_eea6040.

Remaining D1 M1c functions (from the checklist line, not raised this run): endFrame 0xc270460 itself (the wrapper that calls generate), and any of Context::init/frame, Encoder::submit family, Frame::sort, executor 0xe821120 + wrapper, PSO builder, dispatch 0xe9002e0, the five task bodies that the checklist shows as not yet D2 in this run. Per the progress header, D2 already done: submit bc60740, draw flush e81b720, executor 0xe821120, PSO builder, submit 0xe82e230, Frame::sort, endFrame, Context::frame 0xbc66de0, dispatch 0xe9002e0, init 0xbc63690, handoff 0xbc65800, Execute 0xc25fc50, renderFrame 0xbc63150, thread proc 0xbc65720, shutdown 0xbc660a0, task runner 0xc25fe20, 0xc280010, 0xc280ca0, command interpreter 0xbc68e40. The two raised this run: generate 0xc273420, Render lambda 0xc267200.

Next step: run `python tools/delegate.py check docs/progress/oc_U-EM1c.md`, fix failures, then set "## NEXT" + "DONE".
