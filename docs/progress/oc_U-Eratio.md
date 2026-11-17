## NEXT
DONE

UNIT U-Eratio — find the code that WRITES the render/display ratio at ctx+0x1F0.
Output file: docs/progress/oc_U-Eratio.md (only file for this unit).
Must run `python tools/delegate.py check docs/progress/oc_U-Eratio.md` (exit 0), then set line after "## NEXT" to DONE.

GOAL (verbatim from brief): render/display ratio at ctx+0x1F0, read by TAAU body 0xbc8cfd0 at 0xbc8d34e..0xbc8d374; copied field-by-field by endFrame 0x66232b0 at 0x662def4 via 0x67C73D0, which also copies +0x1DC/+0x1E0.

Known anchors (from brief, re-confirmed [V] where cited):
- strings upscaling_percentage (0xf5e13cc / 0xf5e1458) and options.targetResolution (0xf5850de): no direct code refs (registered through a table).
- upscaling_mode/options.upscalingMode reached in Options ctor 0x5b0c1b0 (0x5b3e950/0x5b3e95c) and preset parser 0x11493a0 (0x115050e).

------------------------------------------------------------
VERIFIED [V] findings (disassembly of Minecraft.Windows.exe 1.26.62.01, image base, RVAs relative)

A) ctx+0x1F0 IS the render/display ratio — TAAU body read (r13 = ctx):
  0xbc8d34e  movups xmm0,[r13+0x1F0]          ; read ctx+0x1F0 (the ratio)
  0xbc8d356  movq   xmm1,[r13+0x1E0]          ; read ctx+0x1E0
  0xbc8d36d  mulps  xmm0,xmm1                 ; ratio * (+0x1E0 value)
  (range 0xbc8d34e..0xbc8d374 confirms ratio semantics)

B) Writer store to ctx+0x1F0 (the code that WRITES the ratio):
  0x67c791f  movss [rdx+0x1F0],xmm0           ; [V] writes ctx+0x1F0
  Located inside struct-copy 0x67C73D0.
  Call site: endFrame 0x66232b0 calls 0x67C73D0 at
    0x662def4  call 0x67C73D0
  Call setup proves rdx = ctx = r15:
    0x662deea  lea rcx,[rbx-0x2B0]            ; rcx = r15 = ctx (dst base)
    0x662def1  mov  rdx,r13                   ; rdx = r13 = source array base (src)
  Inside 0x67C73D0: mov rsi,rdx (src=r13); mov rdi,rcx (dst=r15=ctx); [rbp-0x20]=rdi=ctx base;
  later rdx=[rbp-0x20]=ctx, so `movss [rdx+0x1F0]` writes ctx+0x1F0.
  The stored value xmm0 = [rsi+0x1F0] = source(r13)+0x1F0, i.e. the SOURCE array element's +0x1F0 is the ratio copied into ctx+0x1F0.

C) Same struct-copy also writes the sibling offsets (matches brief +0x1DC/+0x1E0):
  0x67c78c4  movss [rdx+0x1DC],xmm0           ; [V] writes ctx+0x1DC
  0x67c78d4  movss [rdx+0x1E0],xmm0           ; [V] writes ctx+0x1E0

D) Source array (r13): elements are 0x2B0 bytes; endFrame copy loop (0x662de80..0x662def4) copies source[i]->ctx[i], advancing both by 0x2B0 until r13==rdi (source end). r15 = [rax+0x70] where rax=[rbp+0x1998] (ctx base, seen at 0x662db99).

E) Options ctor 0x5b0c1b0 only REGISTERS upscaling properties — computes NO ratio:
  0x5b3e799  movups xmm0,[0xF5E13CC]          ; [V] loads string content "upscaling_percentage"
  registers: options.upscalingPercentage (0xF5E1458 @0x5b3e807), upscaling_mode (0xF5E4372 @0x5b3e950),
  options.upscalingMode (0xF5E4CBB @0x5b3e95c), target_resolution (0xF585051 @0x5b3ea6d),
  options.targetResolution (0xF5850DE @0x5b3ead0). Default upscaling_percentage = 0x32 (50) @0x5b3e835.
  Registration via sub_9C4220 / sub_5BC0530. No ratio computation in the ctor.

F) No pointer table holds the string pointers (the strings ARE inline data, loaded by address):
  ptr 0xf5e13cc = 0 (no pointer-to-string refs).
  `movups xmm0,[0xF5E13CC]` appears at 0x51de12b (sub_51cd6c0) and 0x5b3e799 (sub_5b0c1b0) — loads string content, not a table entry.
  xref.py str refs to upscaling_percentage / targetResolution = [] (no direct code refs), consistent with "registered through a table".

------------------------------------------------------------
EVIDENCE TABLE (offset | size | site | instr | meaning)

| offset    | size     | site                  | instr                                              | meaning                                               |
| 0x67c791f | 4 (movss)| struct-copy 0x67C73D0 | `0x67c791f  movss [rdx+0x1F0],xmm0`                | [V] writer store: writes ctx+0x1F0 (the ratio), rdx=ctx=r15 |
| 0xbc8d34e | 16 (movups)|TAAU body 0xbc8cfd0  | `0xbc8d34e  movups xmm0,[r13+0x1F0]`               | [V] confirms ctx+0x1F0 is read as render/display ratio |
| 0x662def4 | 5 (call) | endFrame 0x66232b0   | `0x662def4  call 0x67C73D0`                        | [V] endFrame invokes the struct-copy at the ratio write site |
| 0x662def1 | 3 (mov)  | endFrame call setup  | `0x662def1  mov rdx,r13`                           | [V] rdx = source-array base r13 (arg to struct-copy) |
| 0x662deea | 7 (lea)  | endFrame call setup  | `0x662deea  lea rcx,[rbx-0x2B0]`                   | [V] rcx = r15 = ctx dst base (arg to struct-copy) |
| 0x67c78c4 | 4 (movss)| struct-copy 0x67C73D0 | `0x67c78c4  movss [rdx+0x1DC],xmm0`                | [V] sibling field write ctx+0x1DC |
| 0x67c78d4 | 4 (movss)| struct-copy 0x67C73D0 | `0x67c78d4  movss [rdx+0x1E0],xmm0`                | [V] sibling field write ctx+0x1E0 |
| 0x5b3e799 | 16 (movups)|Options ctor 0x5b0c1b0| `0x5b3e799  movups xmm0,[0xF5E13CC]`               | [V] registers upscaling_percentage (no ratio computed) |
| 0x5b3ead0 | 7 (lea)  |Options ctor 0x5b0c1b0| `0x5b3ead0  lea rdx,[0xF5850DE]`                   | [V] registers options.targetResolution (no ratio computed) |

------------------------------------------------------------
CLOSES? — NO

Single blocking fact:
The writer store IS quoted [V] (`0x67c791f movss [rdx+0x1F0],xmm0` writes ctx+0x1F0; ratio confirmed by TAAU read at `0xbc8d34e movups xmm0,[r13+0x1F0]`), but I could NOT statically link that written value to upscaling_percentage or targetResolution. The value written is source(r13)+0x1F0, and the writer of the SOURCE struct's +0x1F0 (i.e. who builds/populates the source array's ratio field from upscaling_percentage/targetResolution) was not located:
- r13 (source-array base) is callee-saved in endFrame: only `push r13`/`pop r13` (prologue/epilogue), never assigned in the dumped regions 0x66232b0–0x6626100 and 0x662da00–0x662de80; endFrame has no direct callers via `xref.py callers 0x66232b0` (indirect call), so r13's source-array base is not statically traceable to an upscaling source.
- Options ctor 0x5b0c1b0 only registers upscaling_percentage/targetResolution properties (default upscaling_percentage=0x32=50) via sub_9C4220/sub_5BC0530; it computes NO ratio and there is no instruction tying source+0x1F0 to either option value.

Until the source(r13)+0x1F0 writer and its link to upscaling_percentage/targetResolution are found, CLOSES? cannot be YES.

------------------------------------------------------------
TOOL REQUESTS: None (all evidence gathered with rdis.exe / xref.py / descscan2-style reads; no new scripts written).
