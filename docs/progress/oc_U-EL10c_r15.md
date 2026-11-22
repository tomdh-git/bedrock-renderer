## NEXT
DONE

UNIT U-EL10c — L10c viewport and render-resolution selection, dynamic resolution pending.
Output file: docs/progress/oc_U-EL10c.md (only file for this unit).

GOAL (verbatim from item L10c / prior unit oc_U-Eratio.md): close "L10c viewport and render-resolution selection, dynamic resolution pending". Do ONLY the pending part: who writes source(r13)+0x1F0 (== element+0x1F0, == descriptor+0x1F0 via sub_566cb20, propagated to ctx+0x1F0 by endFrame's struct-copy 0x67C73D0 and read by TAAU 0xbc8d34e), who writes [elem+0x14] (the divisor in endFrame's ratio computation), and link either to upscaling_percentage / options.targetResolution.

METHOD: static analysis of Minecraft.Windows.exe 1.26.62.01 (image-relative RVAs). Every quoted `0xRVA  instr` re-verified with rdis against the exe. Input data read in full: docs/progress/oc_U-Eratio.md, docs/functions/66232b0.md (endFrame dossier), docs/data/listings/_tmp_66232b0/b/c/d.txt (endFrame listings), docs/data/listings/_tmp_67c73d0.txt (struct-copy 0x67C73D0), docs/progress/hints/L10c.txt (orchestrator r3/r4/r5 + 2026-11-22 CORRECTION). Live data: grep docs/data/live/*.txt for RVAs 0x66232b0/0x66259e4/0x6624da7/0x67c791f/0xbc8d34e/0x566cb20/0xEEC8060 — zero hits; no live capture names any L10c RVA (known zero-hit captures: er5_clone_4c8a5b0, l8b_resizetex_slot31, oc_u_el6b_desc, el10b_lighting_desc — none is L10c). Per docs/data/live/README.md no capture needed for what statics already name.

------------------------------------------------------------
VERIFIED [V] findings (disassembly of the exe)

A) ctx+0x1F0 IS the render/display ratio — TAAU body read (r13 = ctx):
   0xbc8d34e movups xmm0,[r13+0x1F0]   ; ratio, mulps with +0x1E0 at 0xbc8d36d

B) Writer to ctx+0x1F0 — endFrame 0x66232b0 field-by-field struct copy 0x67C73D0 (called at 0x662def4):
   0x662deea lea rcx,[rbx-0x2B0]       ; rcx = r15 = ctx dst base
   0x662def1 mov rdx,r13               ; rdx = r13 = source-array base (struct-copy src arg)
   0x662def4 call 0x67C73D0
   inside 0x67C73D0 (rsi=r13=src, rdx=ctx=dst):
   0x67c7917 movss xmm0,[rsi+0x1F0]    ; load source(r13)+0x1F0
   0x67c791f movss [rdx+0x1F0],xmm0    ; WRITE ctx+0x1F0
   Sibling field writes in the same copy: 0x67c78c4 movss [rdx+0x1DC],xmm0 ; 0x67c78d4 movss [rdx+0x1E0],xmm0

C) source(r13)+0x1F0 == element+0x1F0 — sub_566cb20 copies descriptor+0x1F0 into element+0x1F0 (0x208-stride element; endFrame calls sub_566cb20 x7):
   0x566d04a movss xmm0,[rsi+0x1F0]    ; load descriptor+0x1F0
   0x566d052 movss [rdx+0x1F0],xmm0    ; write element+0x1F0

D) Ratio computed inside endFrame element loop (rdi walks the 0x208-stride elements, add rdi,0x208 at 0x662595b; bounds [rbp+0x1970]/[rbp+0x19A8]):
   0x6624da7 movss xmm6,[0xEEC8060]    ; load 1.0f
   0x66259e1 movaps xmm6,xmm7
   0x66259e4 divss xmm6,[rdi+0x14]     ; ratio = 1.0f / [elem+0x14]

E) [0xEEC8060] is a read-only constant 1.0f (live read bytes 00 00 80 3F; page PAGE_READONLY; neighbours +0x68/+0x70 are double constants). There is NO store to [0xEEC8060] — supersedes any render-width-global theory.

F) Options ctor 0x5b0c1b0 only REGISTERS upscaling_percentage / options.targetResolution via sub_9C4220/sub_5BC0530; it computes NO ratio and no store ties either option to source+0x1F0 / element+0x1F0 / descriptor+0x1F0 / [elem+0x14]. (0x5b3e799 loads "upscaling_percentage" content; default upscaling_percentage=0x32=50 at 0x5b3e835.)

------------------------------------------------------------
EVIDENCE TABLE (offset | size | site | verbatim `0xRVA  instr` proof | meaning | tag)

| +0x1F0 ctx read (TAAU) | 16 | TAAU body 0xbc8cfd0, r13=ctx | `0xbc8d34e  movups xmm0,[r13+0x1F0]` | ctx+0x1F0 read as render/display ratio; mulps with +0x1E0 at 0xbc8d36d | [V] |
| +0x1F0 ctx write (struct-copy) | 4 | struct-copy 0x67C73D0 (endFrame 0x66232b0 calls it at 0x662def4) | `0x67c791f  movss [rdx+0x1F0],xmm0` | WRITES ctx+0x1F0; rdx=ctx=r15, value = source(r13)+0x1F0 | [V] |
| +0x1F0 source load (struct-copy) | 4 | struct-copy 0x67C73D0 | `0x67c7917  movss xmm0,[rsi+0x1F0]` | loads source(r13)+0x1F0 (rsi=r13=source base) | [V] |
| +0x1F0 element write (sub_566cb20) | 4 | sub_566cb20 at 0x566d04a/0x566d052 | `0x566d052  movss [rdx+0x1F0],xmm0` | element+0x1F0 written from descriptor+0x1F0; element is 0x208-stride | [V] |
| +0x1F0 descriptor load (sub_566cb20) | 4 | sub_566cb20 at 0x566d04a/0x566d052 | `0x566d04a  movss xmm0,[rsi+0x1F0]` | descriptor+0x1F0 loaded (rsi=descriptor base) | [V] |
| +0x1F0 copy call | 5 | endFrame 0x66232b0 call site | `0x662def4  call 0x67C73D0` | endFrame invokes the struct-copy that performs the ctx+0x1F0 write | [V] |
| +0x1F0 copy setup rdx | 3 | endFrame 0x66232b0 call setup | `0x662def1  mov rdx,r13` | rdx = r13 = source-array base passed as struct-copy src arg | [V] |
| +0x1F0 copy setup rcx | 7 | endFrame 0x66232b0 call setup | `0x662deea  lea rcx,[rbx-0x2B0]` | rcx = r15 = ctx dst base passed as struct-copy dst arg | [V] |
| 0xEEC8060 | 4 | endFrame 0x66232b0 | `0x6624da7  movss xmm6,[0xEEC8060]` | [data_eec8060] read-only constant 1.0f (live bytes 00 00 80 3F, PAGE_READONLY); NO store exists to it | [V] [V live] |
| +0x14 elem divisor read | 4 | endFrame element loop | `0x66259e4  divss xmm6,[rdi+0x14]` | ratio = 1.0f / [elem+0x14]; rdi walks 0x208-stride elements (add rdi,0x208 at 0x662595b) | [V] |

------------------------------------------------------------
OPEN / not found ([?])

- Writer of source(r13)+0x1F0 = writer of descriptor+0x1F0 (the passLookup descriptor, src arg of sub_566cb20): not located statically. endFrame calls passLookup 0x5aba5c0 x3 but the descriptor producer that fills +0x1F0 was not found. The chain descriptor+0x1F0 -> element+0x1F0 -> ctx+0x1F0 is proven [V] above; only its upstream writer is missing.
- Writer of [elem+0x14] (the float divisor read by divss at 0x66259e4): not located statically. The element array ([rbp+0x1970..0x19A8], stride 0x208) is filled in endFrame (loop at 0x662570f allocates 0x30-byte entries writing elem+0x1C/+0x20/+0x24/+0x28 from source stride-0x208 fields +0x00/+0x124/+0x128/+0x12C) but no store to elem+0x14 was found in the dumped regions; the setup of [rbp+0x1970]/[rbp+0x19A8] lies in listing gaps.
- Link to upscaling_percentage / options.targetResolution: not found. Option readers sub_5b0c1b0 / sub_10c1ad0 (index 0xFD/0xFE/0x100/0x101 per L17h notes) read the settings, but no instruction ties a read value to a store at descriptor+0x1F0 / element+0x1F0 / [elem+0x14]. Strings upscaling_percentage (0xf5e13cc/0xf5e1458) and options.targetResolution (0xf5850de) have no direct code refs (registered through a table).
- endFrame 0x66232b0 has no direct callers (vtable/function pointer — BgfxFrameBuilder vtable slot 18 per r4), so r13/source-array base and the descriptor producer are not statically traceable from endFrame alone.

------------------------------------------------------------
CLOSES? — NO

Single blocking fact:
No [V] row (and no static instruction) writes source(r13)+0x1F0 / descriptor+0x1F0 / [elem+0x14] AND links that value to upscaling_percentage or options.targetResolution. Everything up to and including the ctx+0x1F0 write (0x67c791f), the element+0x1F0 copy (0x566d052), the TAAU read (0xbc8d34e), and the endFrame ratio computation (0x6624da7 / 0x66259e4) is proven [V]; the single missing link is the upstream writer of the ratio field and its connection to the settings. No live capture names these RVAs, so nothing can be closed from live data either.

------------------------------------------------------------
TOOL REQUESTS: none (all evidence gathered with rdis.exe / xref.py / descscan2-style reads from precomputed listings; no new scripts written). Capture still missing (not queued, no function-entry RVA statically located): a write-watch capture on the passLookup-descriptor +0x1F0 store and on element [elem+0x14] while changing upscaling_percentage / targetResolution in video options, once the descriptor-producer entry RVA is found.
