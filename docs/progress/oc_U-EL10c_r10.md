## NEXT
DONE

UNIT U-EL10c: L10c viewport and render-resolution selection, dynamic resolution pending.
Output file: docs/progress/oc_U-EL10c.md (only file for this unit).
Must run `python tools/delegate.py check docs/progress/oc_U-EL10c.md` (exit 0); line after "## NEXT" set to DONE only on exit 0.

Inherited (oc_U-Eratio.md, 9 rows OK, CLOSES? NO): ctx+0x1F0 store 0x67c791f [V] and TAAU read 0xbc8d34e [V] proven; source(r13)+0x1F0 writer and link to upscaling_percentage/targetResolution not found; endFrame 0x66232b0 = BgfxFrameBuilder vtable slot 18, no direct callers (indirect).
r4 chain [V]: descriptor +0x1F0 -> element +0x1F0 (sub_566cb20 0x566d052) -> ctx +0x1F0 (sub_67c73d0 0x67c791f) -> TAAU read 0xbc8d34e.

New work for this unit (endFrame listing docs/data/listings/_tmp_fn_66232b0.txt, each line re-confirmed against rdis.exe output):
- endFrame reads render-width global [0xEEC8060]: 0x6624da7 movss xmm6,[0xEEC8060] and (loop) 0x6625077 movss xmm7,[0xEEC8060]
- 0x6625090 movaps xmm8,xmm7 ; 0x6625094 divss xmm8,[r15+0x14] : render/display ratio = [0xEEC8060] / [r15+0x14]; ratio spilled at [rsp+0x40] by 0x6625298 movss [rsp+0x40],xmm8
- 0x66252be call 0x6634DB0 : ratio propagated to sub_6634DB0 -> sub_566cb20 -> sub_67c73d0 -> ctx+0x1F0

------------------------------------------------------------
EVIDENCE TABLE (offset | size | site | instr | meaning)
| offset | size | site | instr | meaning |
| 0x6624da7 | 4 (movss) | endFrame 0x66232b0 | `0x6624da7  movss xmm6,[0xEEC8060]` | [V] endFrame reads render-width global [0xEEC8060] into xmm6 |
| 0x6625077 | 4 (movss) | endFrame 0x66232b0 | `0x6625077  movss xmm7,[0xEEC8060]` | [V] endFrame loop reads render-width global [0xEEC8060] into xmm7 |
| 0x6625094 | 4 (divss) | endFrame 0x66232b0 | `0x6625094  divss xmm8,[r15+0x14]` | [V] render/display ratio = [0xEEC8060] / [r15+0x14]; xmm8 = ratio passed on |
| 0x66252be | 5 (call) | endFrame 0x66232b0 | `0x66252be  call 0x6634DB0` | [V] ratio (spilled at [rsp+0x40] by 0x6625298) passed to sub_6634DB0 |
| 0x566d052 | 4 (movss) | sub_566cb20 | `0x566d052  movss [rdx+0x1F0],xmm0` | [V] sub_566cb20 stores descriptor/element +0x1F0 (ratio) |
| 0x67c791f | 4 (movss) | sub_67c73d0 | `0x67c791f  movss [rdx+0x1F0],xmm0` | [V] sub_67c73d0 stores ctx+0x1F0 (ratio), rdx=ctx [from oc_U-Eratio] |
| 0xbc8d34e | 16 (movups) | TAAU 0xbc8cfd0 | `0xbc8d34e  movups xmm0,[r13+0x1F0]` | [V] TAAU reads ctx+0x1F0 as render/display ratio [from oc_U-Eratio] |
| [0xEEC8060] | - | store not located | - | [?] store/write of render-width global [0xEEC8060]: not found statically; every repo reference is a read (0x6624da7, 0x6625077, ...); register-indirect write during window resize / upscaling_percentage change not located |

------------------------------------------------------------
CLOSES? NO
Single blocking fact: the store of render-width global [0xEEC8060] is not located statically (register-indirect, no rip-relative store; all repo references are reads). The writer function in the resize/init path (window resize or upscaling_percentage change) is still missing, so the link upscaling_percentage/targetResolution -> [0xEEC8060] -> ratio cannot be completed.

------------------------------------------------------------
TOOL REQUESTS:
CAPTURE REQUESTED el10c_eec8060_store — python tools/livecap/request.py add el10c_eec8060_store <rva of resize/init function that writes [0xEEC8060]> --size 0x100 --max 6 --why "U-EL10c L10c render-width global [0xEEC8060] store: who writes it (register-indirect, no rip-relative store) and how it links to upscaling_percentage/targetResolution; trigger = resize the game window or change upscaling_percentage in video options. Exact function-entry RVA not yet located statically; endFrame 0x66232b0 only READS [0xEEC8060] (0x6624da7/0x6625077), it does not write it."
