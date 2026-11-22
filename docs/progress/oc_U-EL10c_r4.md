## NEXT
DONE

UNIT U-EL10c — L10c viewport and render-resolution selection, dynamic resolution pending.
Output file: docs/progress/oc_U-EL10c.md (only file for this unit).
GOAL (verbatim from checklist item L10c / oc_U-Eratio.md): close the pending part left by oc_U-Eratio.md (9 rows OK): NO; ctx+0x1F0 store 0x67c791f and TAAU read 0xbc8d34e proven, but source(r13)+0x1F0 writer and link to upscaling_percentage/targetResolution not found (endFrame 0x66232b0 has no direct callers).
DO ONLY the pending part: (a) who writes source(r13)+0x1F0 (the value endFrame's struct-copy 0x67C73D0 copies into ctx+0x1F0 at 0x662def4), (b) link that value to upscaling_percentage/targetResolution.

METHOD: read all precomputed input data in full (oc_U-Eratio.md, oc_U-EL10c_r1.md, oc_U-EL10c_r2.md, oc_U-EL10c_r3.md, docs/functions/66232b0.md dossier, BGFX_MAP.md L10 row, section 3 = vtable slot 18 is endFrame, section 6ev = endFrame stage map). Re-verified verbatim from rdis listings: docs/data/listings/_tmp_67c73d0.txt (struct-copy 0x67C73D0), docs/data/listings/_tmp_66232b0/b/c/d.txt (endFrame 0x66232b0-0x66287c5), fresh rdis dis of endFrame regions 0x6628a00-0x662e07e, and sub_566cb20. Grepped every endFrame dump for "1F0" to enumerate all +0x1F0 sites.

TABLE (name | offset | size | address | verbatim `0xRVA  instr` proof | meaning [tag])
Sizes per rule: movups 16, movss 4, call 5, add 8. One row per distinct offset, all its sites listed.

| +0x1F0 | 4 | source [rsi+0x1F0] read by struct-copy; passLookup descriptor [rsi+0x1F0] read + element [rdx+0x1F0] written by sub_566cb20; element [rsi+0x1F0] zero-init; ctx [rdx+0x1F0] written by struct-copy; TAAU [r13+0x1F0] read | `0x67c7917  movss xmm0,[rsi+0x1F0]` | `566d04a  movss xmm0,[rsi+0x1F0]` | `566d052  movss [rdx+0x1F0],xmm0` | `0x6628fb0  movups [rsi+0x1F0],xmm6` | `0x67c791f  movss [rdx+0x1F0],xmm0` | `0xbc8d34e  movups xmm0,[r13+0x1F0]` | [V] +0x1F0 is the render/display ratio float. It is READ from the source element (rsi=r13=source base) and WRITTEN to ctx (rdx=r15=ctx) by pure field-by-field struct-copy 0x67C73D0 — no computation. Inside endFrame it is only COPIED: passLookup descriptor+0x1F0 -> element+0x1F0 via sub_566cb20 (called from endFrame at `0x662abef call 0x566CB20`, setup `0x662abec mov rcx,rdi`, rsi still = passLookup descriptor from `0x662ab48 mov rsi,rax`) or zeroed (`0x6628fb0 movups [rsi+0x1F0],xmm6` in an init streak). NEVER computed from upscaling_percentage/targetResolution; no writer ties source+0x1F0 to either option value. TAAU body 0xbc8cfd0 consumes it at `0xbc8d34e movups xmm0,[r13+0x1F0]` for RenderResolution = ratio * dims (0xbc8d34e..0xbc8d374). |

| call site | 5 | endFrame invokes struct-copy here (0x67C73D0 is called 3x in endFrame; this is the r13=source-base invocation) | `0x662def4  call 0x67C73D0` | [V] endFrame copy site #1. Setup: `0x662def1 mov rdx,r13` (rdx = source base = r13), `0x662deea lea rcx,[rbx-0x2B0]` (rcx = ctx dst = r15). Loop exit `0x662de92 cmp r13,rdi` / `je sub_662d0bf`. |

| loop stride | 8 | source-base walk in endFrame copy loop | `0x662ded3  add r13,0x2B0` | [V] r13 (source base) steps by 0x2B0 per element until r13 == rdi (`0x662dee1 cmp r13,rdi`). Source elements are 0x2B0 bytes. r13's initial source-base value is NOT assigned to any upscaling computation inside endFrame (checked all dumped regions). |

| Options ctor | 16 | Options ctor 0x5b0c1b0 property-registration loads | `0x5b3e799  movups xmm0,[0xF5E13CC]` | `0x5b3ead0  movups xmm0,[0xF5850DE]` | [V] Options ctor 0x5b0c1b0 registers upscaling_percentage and options.targetResolution via sub_9C4220/sub_5BC0530 only; it computes NO ratio and no instruction ties either option value to source+0x1F0. Default upscaling_percentage = 0x32 = 50. |

| option strings | - | string addresses (no code refs) | (no instruction; xref refs = []) | [V] strings upscaling_percentage (0xf5e13cc) and options.targetResolution (0xf5850de) exist but have no direct code references — registered through the options table only. |

| endFrame entry | - | endFrame 0x66232b0 | (no instruction; xref.py callers = empty) | [I] endFrame 0x66232b0 (0xb3d0 bytes) has no direct callers; entered only through an indirect BgfxFrameBuilder vtable slot-18 (+0x90) call. Vtable 0xf2bdeb0 references are constructor stores only (ripscan 0xf2bdeb0 -> 0x660d9d3 in func 0x660d940, 0x67eca03 in func 0x67ec9e0); no endFrame `call [..+0x90]` call site exists in .text. The caller that builds/fills the source array (and its descriptor's +0x1F0) is not statically reachable. |

| element builder | - | passLookup descriptor cursor inside endFrame | `0x662abd1  mov rdi,[rsi+0x50]` | `0x662abd5  cmp rdi,[rsi+0x58]` | `0x662ad17  add qword ptr [rsi+0x50],0x2B0` | [V] endFrame appends 0x2B0-byte source elements from the passLookup(0x5aba5c0) descriptor (rsi; [rsi+0x50] = insertion cursor, [rsi+0x58] = limit, advanced by 0x2B0 per element). It writes refcount fields +0x250..+0x2A0 only — there is NO +0x1F0 write anywhere in the builder. |

| zero-init | 16 | element [rsi+0x1F0] | `0x6628fb0  movups [rsi+0x1F0],xmm6` | [V] Element +0x1F0 is written with xmm6 inside a field-init streak ([rsi+0x19C]..[rsi+0x1D7] also xmm6) — zero-initialization, not the ratio value. |

FINDINGS (all tagged):
1. Inside endFrame the ratio at +0x1F0 is only PROPAGATED, never selected or computed: sub_566cb20 copies descriptor+0x1F0 into the new element (`566d04a movss xmm0,[rsi+0x1F0]` / `566d052 movss [rdx+0x1F0],xmm0`), then struct-copy 0x67C73D0 copies element+0x1F0 into ctx+0x1F0 (`0x67c791f movss [rdx+0x1F0],xmm0`), and TAAU consumes ctx+0x1F0 (`0xbc8d34e movups xmm0,[r13+0x1F0]`).
2. The ratio's ORIGIN — the passLookup descriptor's +0x1F0, i.e. the render-resolution/dynamic-resolution selection from upscaling_percentage/targetResolution — is written by endFrame's CALLER. endFrame 0x66232b0 has no direct callers (indirect vtable slot 18; xref.py empty), so that writer and the option link are statically unreachable.
3. Already proven and re-verified verbatim: ctx+0x1F0 store `0x67c791f movss [rdx+0x1F0],xmm0`; TAAU read `0xbc8d34e movups xmm0,[r13+0x1F0]`; struct-copy called from endFrame at `0x662def4 call 0x67C73D0`.

CLOSES?: NO
Single blocking fact: the writer of source(r13)+0x1F0's ratio value and its link to upscaling_percentage/targetResolution were not located. Inside endFrame the ratio is only copied (passLookup descriptor +0x1F0 -> element +0x1F0 via sub_566cb20 at 566d04a/566d052, called at `0x662abef call 0x566CB20`; then element +0x1F0 -> ctx +0x1F0 via 0x67c73d0 at `0x67c791f movss [rdx+0x1F0],xmm0`); no [reg+0x1F0] ratio store exists anywhere in endFrame [0x66232b0,0x662e680); endFrame 0x66232b0 has no direct callers (indirect BgfxFrameBuilder vtable slot-18 call), so the descriptor's +0x1F0 writer — the render-resolution/dynamic-resolution selection from upscaling_percentage/targetResolution — is statically unreachable; and no instruction ties source+0x1F0 to either option value (both strings xref refs=[], Options ctor 0x5b0c1b0 computes no ratio). Until that writer/link is proven by a [V] row, the item cannot close.

TOOL REQUESTS: none.