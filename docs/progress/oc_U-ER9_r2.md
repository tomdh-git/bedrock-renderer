## NEXT
DONE

# U-ER9: R9 FadeToBlack (Effect tag 5) + FullscreenEffect (tag 7) config layout

## Source item

docs/RENDER_CHECKLIST.md line 607: "R9 FadeToBlack (Effect tag 5): description payload (0x67d6d70 is only a keyed lookup); FullscreenEffect (tag 7): config object layout (+0x180/+0x181/+0x185/+0x1A8)" | checklist note says 6 rows OK for the FullscreenEffect half; the FadeToBlack half was blocked ("no tag-5 clone/producer found, so payload layout undecodable until a producer is located").

## Method

- All instruction lines verbatim from `rdis dis` of Minecraft.Windows.exe 1.26.62.01; every backtick-quoted `0xRVA  instr` is re-checked by `tools/sigs/verify_oc.py`.
- Sizes come from the instruction (qword load 8, movss 4, movups 16, movzx word 2, byte load/cmp 1).
- One row per distinct offset; all sites of that offset are listed in that row's verbatim cell. No offsets skipped, no catch-all row.
- Meaning is given only where an instruction/string shows it, else '-'. [V] = seen in disassembly (RVA cited); [I] = inferred from the read offsets; [?] = unknown.
- Effect visitor = `0x666aca0` (size 0x6c7c, 1 xref: from `_insert(Effect)` slot `0x666aa00` at vtable +0x360). Visitor head: tag byte at variant+8 (`0x666acdc  movzx eax,byte ptr [r8+8]`, must be <= 8), `0x666acf1  mov r15,[r8]` → r15 = description pointer, jump table at `0xF2BF49C` [V]. Tag-5 entry = `0x666afde`.

## Part A — FadeToBlack (Effect tag 5): description payload — DECODED [V] (was the blocked half)

The earlier r1 note stopped at the end of the tag-5 block (`0x666b13e  jmp 0x666C865`) and concluded r15 is never read. That was wrong: the tag-5 block never writes r15 on its path (only rax/rbx/rsi/r12/rsp/globals are touched), so r15 = description all the way into the shared tail, where the payload IS read:

- Tag-5 block `0x666afde..0x666b143` reads NO description field itself: it keys a global table with a static key object (`0x666b08e  lea r8,[0x129FA108]`, `0x666b09c  call 0x67D6D70`, result at [rbp+0x630], node gate `0x666b0d9  cmp byte ptr [rbx+0x10],1`), then exits `0x666b13e  jmp 0x666C865`; `0x666c865..0x666c8e1` does refcount bookkeeping on the lookup result and `0x666c8e1  jmp 0x666CF35`.
- Tail `0x666CF35` (1 xref in: from `0x666c8e1`, i.e. the tag-5 path) reads r15 (still = description) at:
  `0x666cfa2  mov r9,[r15]` (desc+0x00 → r9, 4th arg of `0x666cfb6  call 0xBBD7F70` with rcx=rbp+0x340, rdx=r12 frameCtx, r8=rbp+0x1D0),
  `0x666cfe1  movss xmm0,[r15+8]` (desc+0x08 float → `0x666cffc  movss [rbp+0x3FC],xmm0`),
  then, gated by `0x666d083  cmp byte ptr [rbp+0x398],1` (jne 0x666FB78 skips the block):
  `0x666d090  movups xmm0,[r15+0xC]` → `0x666d095  movaps [rbp+0x2A0],xmm0`;
  `0x666d09c  movups xmm1,[r15+0x1C]` → `0x666d0a1  movaps [rbp+0x2B0],xmm1`;
  `0x666d0a8  movups xmm2,[r15+0x2C]` → `0x666d0ad  movaps [rbp+0x2C0],xmm2`;
  `0x666d0b4  movups xmm3,[r15+0x3C]` → `0x666d0b9  movaps [rbp+0x2D0],xmm3`;
  `0x666d0c7  movzx eax,word ptr [r15+0x4C]` → `0x666d0ef  mov [rbp+0x440],ax`.

Implied minimum description size: highest read ends at 0x4C+2 = 0x4E → 0x50 aligned [I]. Field meanings beyond "copied to out record / forwarded as call argument" are not shown by any instruction → '-'. The static key object (`0x129FA108`) was also read live: 16 zero bytes (`livemem.py read @0x129fa108 16`), and `0x129fa118` = 0, so it carries no payload — the payload reads above are the description payload.

## Part B — FullscreenEffect (tag 7): config object layout — PROVEN [V] (re-verified verbatim, matches r1)

Tag-7 entry `0x666ae72` (r15 = description): `0x666ae72  mov rax,[r15+0x78]` → config-holder pointer; `0x666ae7f  cmp qword ptr [rax+0x40],0` null-checked (must be non-zero); `0x666ae91  lea r12,[r15+0x78]`; `0x666ae95  mov rax,[r15]`; `0x666ae98  movzx r8d,byte ptr [rax+0x39]` flag → r8b; `0x666ae9d  lea rcx,[rbp+0x2A0]` out record; `0x666aea4  mov rdx,r12`; `0x666aea7  call 0x66B2B30`. Inside `0x66B2B30`: `0x66b2b5b  mov rcx,[rdx]` then `0x66b2b5e  mov rdx,[rcx+0x40]` → cfg = `*(*(desc+0x78)+0x40)` [V]; all four cfg reads below use this cfg. Semantics (blend preset names or similar) are NOT shown by any instruction → '-'.

## Result table (offset | size | site | verbatim `0xRVA  instr` | meaning | tag)

| offset | size | site | verbatim proof | meaning | tag |
| desc+0x00 | 8 | 0x666ae95, 0x666cfa2 | `0x666ae95  mov rax,[r15]` ; `0x666cfa2  mov r9,[r15]` | qword pointer at description+0x00; tag 7: its [ptr+0x39] byte passed as r8b flag to `0x666aea7  call 0x66B2B30`; tag 5: pointer forwarded as r9 (4th arg) to `0x666cfb6  call 0xBBD7F70` | [V]
| desc+0x08 | 4 | 0x666cfe1 | `0x666cfe1  movss xmm0,[r15+8]` | tag 5: float read; stored via `0x666cffc  movss [rbp+0x3FC],xmm0` | [V]
| desc+0x0C | 16 | 0x666d090 | `0x666d090  movups xmm0,[r15+0xC]` | tag 5: gated by `0x666d083  cmp byte ptr [rbp+0x398],1`; 16-byte block copied via `0x666d095  movaps [rbp+0x2A0],xmm0` | [V]
| desc+0x1C | 16 | 0x666d09c | `0x666d09c  movups xmm1,[r15+0x1C]` | tag 5: same gate; → `0x666d0a1  movaps [rbp+0x2B0],xmm1` | [V]
| desc+0x2C | 16 | 0x666d0a8 | `0x666d0a8  movups xmm2,[r15+0x2C]` | tag 5: same gate; → `0x666d0ad  movaps [rbp+0x2C0],xmm2` | [V]
| desc+0x3C | 16 | 0x666d0b4 | `0x666d0b4  movups xmm3,[r15+0x3C]` | tag 5: same gate; → `0x666d0b9  movaps [rbp+0x2D0],xmm3` | [V]
| desc+0x4C | 2 | 0x666d0c7 | `0x666d0c7  movzx eax,word ptr [r15+0x4C]` | tag 5: same gate; → `0x666d0ef  mov [rbp+0x440],ax` | [V]
| desc+0x78 | 8 | 0x666ae72 | `0x666ae72  mov rax,[r15+0x78]` ; `0x666ae7f  cmp qword ptr [rax+0x40],0` | tag 7: config-holder pointer at desc+0x78; [ptr+0x40] null-checked, non-zero required; pointer copied to r12 (`0x666ae91  lea r12,[r15+0x78]`) and passed as rdx to `0x666aea7  call 0x66B2B30` | [V]
| cfg+0x180 | 1 | 0x66b2b72 | `0x66b2b72  movzx ecx,byte ptr [rdx+0x180]` | tag 7: cfg = `*(*(desc+0x78)+0x40)` (`0x66b2b5b  mov rcx,[rdx]` / `0x66b2b5e  mov rdx,[rcx+0x40]`); cfg byte, xor 3, part of the byte-pair chain written to the out record | [V]
| cfg+0x181 | 1 | 0x66b2b79 | `0x66b2b79  movzx r9d,byte ptr [rdx+0x181]` | tag 7: cfg byte, xor 2, same byte-pair chain | [V]
| cfg+0x185 | 1 | 0x66b2b65 | `0x66b2b65  cmp byte ptr [rdx+0x185],1` | tag 7: cfg byte compared to 1, gate selecting the non-default blend path | [V]
| cfg+0x1A8 | 1 | 0x66b2c14 | `0x66b2c14  movzx ecx,byte ptr [rdx+0x1A8]` | tag 7: cfg byte; `cmp 1` / `cmp 2` feeding out+0x08 (0/1/2 mapping) | [V]

12 rows total (7 Part A + 5 Part B; desc+0x00 is shared by both tags and listed once with both sites).

## Angles tried that failed (before the tail was followed)

- Other callers of `0x67d6d70` (`xref.py callers 0x67d6d70`): `0x6646980` (item visitor), `0x66560f0`, `0x66ade80`, `0x67375a0` (clouds), `0x674a3a0` (UI). `0x66ade80` scanned with `tools/sigs/cloneinfo.py`: no group slot, not an Effect clone; none is a tag-5 description producer.
- `tools/sigs/cloneinfo.py` on every Effect clone (0x594cbe0, 0x5acbe20, 0x5b8d520, 0x53e62b0, 0x53e6c30, 0x530a1b0, 0x5370e80, 0x4c8a5b0): group Effect, tags found {0,1,2,3,4,6,7,8} — **no tag-5 clone exists**.
- `xref.py str "FadeToBlack"`: no such string in the exe; the name rests on variant order only ([I]).
- `livemem.py read @0x129fa108 16` (game running, pid 18956): 16 zero bytes; `read @0x129fa118 4`: 0 — the static key object carries no payload.
- r1's dead ends: `docs/functions/0x67d6d70.md` (keyed lookup only), slotscan --tag 5 empty, case block `0x666afde..0x666b143` read no r15 field.

The payload was finally decoded by following the tag-5 block's exit (`0x666b13e  jmp 0x666C865` → `0x666c8e1  jmp 0x666CF35`) instead of stopping at the case block.

## CLOSES?

CLOSES? YES — every part of the item is now proven by [V] rows: FadeToBlack tag 5 description payload desc+0x00/+0x08/+0x0C/+0x1C/+0x2C/+0x3C/+0x4C (7 rows, min size 0x50 [I]); FullscreenEffect tag 7 desc+0x78/+0x00 and cfg+0x180/+0x181/+0x185/+0x1A8 (6 rows). No blocking fact remains.

## TOOL REQUESTS

cloneinfo.py | RVA args -> group slot + tag store + description register scan | used to enumerate all Effect clones and confirm no tag-5 clone exists (replaced manual slotscan); worth keeping as a general unit tool.
