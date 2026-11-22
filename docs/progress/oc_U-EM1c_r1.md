## NEXT
DONE field map for 0xbc660a0 store instructions verified; resource-table drain blocks not directly present in function body

# M1c Dossiers (D2) — 0xbc660a0 bgfx::Context::shutdown sequence: drain-block store field map

## Scope

Verified every non-stack store instruction in `0xbc660a0..0xbc66a4b` (size 0x9ab, D2 per census). The function emits pre/post-cmd opcodes (0x01, 0x1F, 0x1E, 0x1A), pushes handles into frame queues, releases specific handles, drains the handle array at `this+0x1EBF2BC`, cleans up view/encoder aux state, and destroys two element arrays via `sub_ebdbc90`. The task's "6 drain blocks" for resource tables (index `0x93A178/0x78`, vertex `0x9B2178/0x80`, framebuffer `ctx+0xC97698/0x68`, shader `0xAAA178/0xB8`, program `0xB62178/0xF8`, texture `0xBDE178/0xB8`, uniform/vertex layouts `ctx+0xC96198`) are NOT directly referenced in this function body — confirmed by searching the full listing: none of those offsets appear. They must be triggered indirectly via emitted post-commands or implemented in callees (`0xbc65800`, `0xbc732e0`, `0xbc79ed0`, `0xbc769c0`, vcall targets via `data_12ADF800`).

## Field map: distinct store offsets in 0xbc660a0

| offset | size | site | instr | meaning |
|---|---|---|---|---|
| 0x1EBF19E | 1 | 0xbc660c4 | `0xbc660c4  and byte ptr [rcx+0x1EBF19E],0xFB` | clear bit 2 in Context shutdown/state flags [V] |
| 0xDC5818 | 4 | 0xbc660f6 | `0xbc660f6  inc dword ptr [rsi+0xDC5818]` | pre-cmd buffer cursor increment after emitting opcode 0x01 [V] |
| 0xE05820 | 4 | 0xbc66148, 0xbc66164, 0xbc66204, 0xbc66220, 0xbc6631d, 0xbc6633a, 0xbc663e4, 0xbc66401, 0xbc664fb, 0xbc66518, 0xbc665c3, 0xbc665df, 0xbc6667f, 0xbc6669b, 0xbc66738 | `0xbc66148  mov [rbx+0xE05820],eax`; `0xbc66164  add dword ptr [rbx+0xE05820],2`; `0xbc66204  mov [rbx+0xE05820],eax`; `0xbc66220  add dword ptr [rbx+0xE05820],2`; `0xbc6631d  mov [r14+0xE05820],eax`; `0xbc6633a  add dword ptr [r14+0xE05820],2`; `0xbc663e4  mov [r14+0xE05820],eax`; `0xbc66401  add dword ptr [r14+0xE05820],2`; `0xbc664fb  mov [r14+0xE05820],eax`; `0xbc66518  add dword ptr [r14+0xE05820],2`; `0xbc665c3  mov [rbx+0xE05820],eax`; `0xbc665df  add dword ptr [rbx+0xE05820],2`; `0xbc6667f  mov [rbx+0xE05820],eax`; `0xbc6669b  add dword ptr [rbx+0xE05820],2`; `0xbc66738  inc dword ptr [rsi+0xE05820]` | post-cmd buffer cursor: set to aligned-even value then +2 after each opcode+payload append; +1 after opcode 0x1A [V] |
| 0xE478AC | 2 | 0xbc6617d, 0xbc66354, 0xbc66532, 0xbc665f8 | `0xbc6617d  mov [rax+rdx*2+0xE478AC],cx`; `0xbc66354  mov [rax+rdx*2+0xE478AC],cx`; `0xbc66532  mov [rax+rdx*2+0xE478AC],cx`; `0xbc665f8  mov [rax+rdx*2+0xE478AC],cx` | push u16 handle into frame handle queue at `frame + count*2 + 0xE478AC` (opcode 0x1F path) [V] |
| 0xE498AC | 2 | 0xbc66185, 0xbc6635c, 0xbc6653a, 0xbc66600 | `0xbc66185  inc word ptr [rax+0xE498AC]`; `0xbc6635c  inc word ptr [rax+0xE498AC]`; `0xbc6653a  inc word ptr [rax+0xE498AC]`; `0xbc66600  inc word ptr [rax+0xE498AC]` | increment u16 handle queue count at `frame+0xE498AC` after each 0x1F push [V] |
| 0xE45828 | 2 | 0xbc66239, 0xbc6641b, 0xbc666b4 | `0xbc66239  mov [rax+rdx*2+0xE45828],cx`; `0xbc6641b  mov [rax+rdx*2+0xE45828],cx`; `0xbc666b4  mov [rax+rdx*2+0xE45828],cx` | push u16 handle into frame handle queue at `frame + count*2 + 0xE45828` (opcode 0x1E path) [V] |
| 0xE47828 | 2 | 0xbc66241, 0xbc66423, 0xbc666bc | `0xbc66241  inc word ptr [rax+0xE47828]`; `0xbc66423  inc word ptr [rax+0xE47828]`; `0xbc666bc  inc word ptr [rax+0xE47828]` | increment u16 handle queue count at `frame+0xE47828` after each 0x1E push [V] |
| 0x1EBF2BC | 2 | 0xbc664a3 | `0xbc664a3  mov word ptr [r15+rsi*2+0x1EBF2BC],0xFFFF` | bulk drain: store 0xFFFF sentinel back into handle slot after `sub_bc732e0` destroy, in loop over `this+0x1EBF2BC` indexed by `rsi*2` [V] |
| 0x13D20 | 8 | 0xbc66816 | `0xbc66816  mov qword ptr [r15+0x13D20],0` | null out Context view/encoder container pointer after handle free-list teardown [V] |
| 0x6F8 | 8 | 0xbc66798 | `0xbc66798  mov [rdi+0x6F8],rax` | store QPC/timestamp result from `sub_ebdb740` into view/encoder object at +0x6F8 [V] |
| 0x680 | 8 | 0xbc66840 | `0xbc66840  mov qword ptr [rdi+0x680],0` | clear per-view chain head pointer at `view+0x680` during aux-structure drain [V] |
| 0x4 | 4 | 0xbc6678c | `0xbc6678c  mov dword ptr [rsi+4],0` | reset per-view uniform buffer write cursor to 0 after appending u32 value 1 [V] |

## 6 drain blocks — status

The task's named resource-table drain targets (index/vertex/framebuffer/shader/program/texture/uniform/vertex-layout tables at bases `0x93A178`, `0x9B2178`, `ctx+0xC97698`, `0xAAA178`, `0xB62178`, `0xBDE178`, `ctx+0xC96198` with strides `0x78/0x80/0x68/0xB8/0xF8/0xB8`) do not appear as direct memory operands in `0xbc660a0`. The function's actual drain activity is: (a) command emission of opcodes 0x1F/0x1E/0x1A/0x21/0x22 into pre/post-cmd buffers, (b) handle queue pushes and releases, (c) bulk handle-array drain at `this+0x1EBF2BC`, (d) view/encoder aux cleanup at `this+0x13D18` + per-view stride `0x700`, (e) two array destructions via `sub_ebdbc90` at `this+0x1DE1310` and `this+0x1DDD2D0`. Mapping these to specific resource-table drains requires render-thread command-consumer tracing (callee `0xbc65800` frame/swap path, or `sub_ebce390` command-buffer append semantics). [UNVERIFIED: 0xbc660a0 which emitted post-command opcode triggers which resource-table drain on the render side]

CLOSES? NO — the 6 resource-table drain blocks of 0xbc660a0 (index/vertex/framebuffer/shader/program/texture) are not directly observable in this function body; they require render-thread command-consumer tracing beyond static disassembly of 0xbc660a0. Other pending items (6cs header fields slots 39-45, generate per-pass loop, L4/L5 dossiers endFrame 0x66232b0/extractors) are separate.

## TOOL REQUESTS

None — used rdis dis 0xbc660a0 800 and existing docs/functions/0xbc660a0.md dossier.
