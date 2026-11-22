## NEXT
DONE

# Unit U-EL17h — L17h graphics options plumbing (OptionSync)
Output file: docs/progress/oc_U-EL17h.md (only file for this unit).
Must run `python tools/delegate.py check docs/progress/oc_U-EL17h.md` (exit 0), then set line after "## NEXT" to DONE.

GOAL (verbatim from docs/RENDER_CHECKLIST.md line L17h): close "graphics options plumbing (OptionSync) pending" — prove the writer of source(r13)+0x1F0 (the value copied into ctx+0x1F0 by struct-copy 0x67C73D0 at endFrame 0x66232b0) and its link to upscaling_percentage / targetResolution.

Prior unit oc_U-Eratio.md proven [V]: writer store `0x67c791f movss [rdx+0x1F0],xmm0` writes ctx+0x1F0; TAAU read `0xbc8d34e movups xmm0,[r13+0x1F0]`; struct-copy 0x67C73D0 called from endFrame at `0x662def4 call 0x67C73D0` (setup `0x662def1 mov rdx,r13` / `0x662deea lea rcx,[rbx-0x2B0]`); source elements are 0x2B0 bytes; options upscaling_percentage/targetResolution registered in Options ctor 0x5b0c1b0 with NO ratio computed; strings 0xf5e13cc/0xf5850de have no direct code refs (table-registered); live ratio 0.65 (1248x739 = 0.65 x backbuffer 1920x1137).

New work this unit: full endFrame dump [0x66232b0,0x662e680) via dumplist.py (docs/data/listings gap covered), all r13 writes, all 0x1F0 references, all 0x67C73D0 call sites.

## TABLE (name | offset | size | verbatim `0xRVA  instr` proof | [V]/[I]/[?] meaning)

| source(r13)+0x1F0 read inside struct-copy | 0x67c7917 | 4 (movss) | struct-copy 0x67C73D0 | `0x67c7917  movss xmm0,[rsi+0x1F0]` | [V] source+0x1F0 (rsi = source = r13) is READ here — a read, not a write; this instruction does NOT identify the writer of source+0x1F0 |
| ctx+0x1F0 write inside struct-copy | 0x67c791f | 4 (movss) | struct-copy 0x67C73D0 | `0x67c791f  movss [rdx+0x1F0],xmm0` | [V] writes ctx+0x1F0; rdx = ctx = r15 (proven by oc_U-Eratio.md) |
| endFrame copy-loop call site | 0x662def4 | 5 (call) | endFrame 0x66232b0 | `0x662def4  call 0x67C73D0` | [V] per-element copy source(r13)[0x2B0] -> ctx(r15); setup `0x662def1  mov rdx,r13` / `0x662deea  lea rcx,[rbx-0x2B0]` |
| copy-loop bounds check | 0x662de92 | 6 (cmp) | endFrame copy loop | `0x662de92  cmp r13,rdi` | [V] r13 = source cursor, rdi = source end (range [rsi+0x48]..[rsi+0x50]); stride 0x2B0 per element |
| source array base setup | 0x662d085 | 8 (mov) | endFrame pre-loop | `0x662d085  mov r13,[rsi+0x48]` | [V] r13 = source array base from an endFrame argument object (+0x48/+0x50 = begin/end; `0x662d089  cmp rdi,[rsi+0x50]`) |
| endFrame argument provenance | 0x662501a | 10 (mov) | endFrame | `0x662501a  mov [rbp+0x1970],rcx` | [V] [rbp+0x1970] = builder+0x28 (context ptr): `0x662500f  mov rax,[rbp+0x19D0]`; `0x6625016  lea rcx,[rax+0x28]`; the source array lives in endFrame's argument objects, filled by endFrame's CALLER |
| endFrame contains no source+0x1F0 object store | 0x6628fb0 | 16 (movups) | endFrame full dump [0x66232b0,0x662e680) | `0x6628fb0  movups [rsi+0x1F0],xmm6` | [I] the ONLY object +0x1F0 store in all of endFrame (full dump has exactly two 0x1F0 refs: this one and stack [rbp+0x1F0] at 0x6628943); it zeroes a 0x378-byte pass entry (vtable 0xF2BEAD0, size 0x378 at 0x6628e71), NOT the source ratio — endFrame never writes source+0x1F0 |
| TAAU ratio consume | 0xbc8d34e | 16 (movups) | TAAU body 0xbc8cfd0 | `0xbc8d34e  movups xmm0,[r13+0x1F0]` | [V] ctx+0x1F0 consumed as render/display ratio (proven by oc_U-Eratio.md; RenderResolution = ratio * dims at 0xbc8d34e..0xbc8d36d) |
| options registration, no ratio computed | 0x5b3e799 | 16 (movups) | Options ctor 0x5b0c1b0 | `0x5b3e799  movups xmm0,[0xF5E13CC]` | [V] upscaling_percentage registered (default 0x32=50 at 0x5b3e835); `0x5b3ead0  movups xmm0,[0xF5850DE]` registers options.targetResolution; no instruction ties either option to source+0x1F0 |

## VERBATIM PROOF LINES (each verified against the exe with rdis)
0x67c7917  movss xmm0,[rsi+0x1F0]
0x67c791f  movss [rdx+0x1F0],xmm0
0x662def4  call 0x67C73D0
0x662def1  mov rdx,r13
0x662deea  lea rcx,[rbx-0x2B0]
0x662de92  cmp r13,rdi
0x662d085  mov r13,[rsi+0x48]
0x662d089  cmp rdi,[rsi+0x50]
0x6625016  lea rcx,[rax+0x28]
0x662501a  mov [rbp+0x1970],rcx
0x6628fb0  movups [rsi+0x1F0],xmm6
0x6628943  movapd [rbp+0x1F0],xmm0
0xbc8d34e  movups xmm0,[r13+0x1F0]
0x5b3e799  movups xmm0,[0xF5E13CC]
0x5b3ead0  movups xmm0,[0xF5850DE]

## MECHANICS ESTABLISHED [V]
- endFrame(rcx=builder [rbp+0x19D0], rdx=frame-package [rbp+0x1998]). The copy loop at 0x662de80 walks source [r13, rdi) stride 0x2B0 into ctx [r15, ...); per element `call 0x67C73D0(rdx=r13=source element, rcx=r15=ctx)` at 0x662def4. r13 = [rsi+0x48] set at 0x662d085, end rdi = [rsi+0x50] (0x662d089); empty-range exit `je 0x662DE7D` lands on the same loop-entry block (`0x662de7d  mov [rbp+0x1800],r15` / `0x662de84  mov [rbp+0x1808],r15` / `0x662de8b  mov [rbp+0x1810],r14` / `0x662de92  cmp r13,rdi`).
- 0x67C73D0 copies field-by-field incl. +0x1D8/+0x1DC/+0x1E0/+0x1E4 (movss), +0x1E8 (word), +0x1EC/+0x1F0/+0x1F4/+0x1F8/+0x1FC/+0x200/+0x204/+0x208/+0x20C (movss), +0x210 (word), +0x212 (byte), +0x214..+0x234 (movss), +0x238 (word), +0x23A (byte), +0x23C/+0x242 (qword); endFrame then copies the shared_ptr fields +0x250..+0x2A0 inline with refcount inc.
- 0x67C73D0 is called 3x from endFrame: 0x662ba52, 0x662cd25, 0x662def4 (full-function dump). None of the three writes +0x1F0 of any source object.
- Full endFrame dump [0x66232b0,0x662e680) contains exactly two 0x1F0 references: stack `[rbp+0x1F0]` at 0x6628943 and the unrelated pass-entry zeroing at 0x6628fb0. NO `[reg+0x1F0]` object store → endFrame does not write source+0x1F0; it only reads it (0x67c7917) and copies it to ctx+0x1F0 (0x67c791f).
- [rbp+0x1970] = builder+0x28 (context pointer, [V] 0x662500f/0x6625016/0x662501a; context null-checked at 0x6623308; BGFX_MAP.md 6cx: [builder+0x28] = BgfxContext passed to 0xc270460). The source array ([rsi+0x48..[rsi+0x50)) belongs to endFrame's argument objects, i.e. it is built by endFrame's CALLER.
- endFrame has NO direct callers: `xref.py callers 0x66232b0` = []; dossier docs/functions/66232b0.md: "callers: none direct (vtable / std::function / CFG)"; BgfxFrameBuilder::endFrame = vtable slot 18 (BGFX_MAP.md platform-versioning-live.md). The caller is an indirect call, not statically traceable.

## ANSWER TO THE PENDING ITEMS
- source(r13)+0x1F0 writer: NOT located. endFrame consumes a caller-built source array (base = [rsi+0x48], end = [rsi+0x50]); it contains no store to source+0x1F0 anywhere (full-function dump verified). The writer is the filler of the frame-package argument, i.e. code upstream of endFrame — endFrame's indirect caller — which is not statically reachable.
- Link of source+0x1F0 to upscaling_percentage/targetResolution: NOT proven. Options are registered in Options ctor 0x5b0c1b0 (`0x5b3e799 movups xmm0,[0xF5E13CC]` upscaling_percentage, `0x5b3ead0 movups xmm0,[0xF5850DE]` targetResolution, default upscaling_percentage = 0x32 = 50); the strings have no direct code refs (table-registered); no instruction ties either option value to source(r13)+0x1F0. Live ratio 0.65 is consistent with ctx+0x1F0 at runtime but proves nothing about the writing code.

## CLOSES?
NO

Single blocking fact: source(r13)+0x1F0 is only ever READ (0x67c7917) and copied into ctx+0x1F0 (0x67c791f) inside endFrame; the source array is a caller-built argument of endFrame (base [rsi+0x48] at 0x662d085, end [rsi+0x50] at 0x662d089), a full dump of endFrame [0x66232b0,0x662e680) shows no [reg+0x1F0] object store, and endFrame has no direct callers (indirect call, vtable slot 18). The OptionSync writer of source(r13)+0x1F0 and its link to upscaling_percentage/targetResolution are therefore not statically provable; closing YES requires tracing endFrame's indirect caller (live capture or an orchestrator-provided caller RVA).

## TOOL REQUESTS: None
