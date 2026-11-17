## NEXT
DONE

# U-ER3 — R3 BlitFlipbook (Effect tag 1): description +0x00..+0x0F / +0x20..+0x9F, element +0x34..+0x3F unread; true size

Goal: close checklist item R3 (docs/RENDER_CHECKLIST.md section R): "R3 BlitFlipbook (Effect tag 1): description +0x00..+0x0F, +0x20..+0x9F, element +0x34..+0x3F unread; true size".
Scope: only the pending parts of that item line. Effect group vslot 0x360, tag 1 = BlitFlipbook; thin insert clone 0x5acbe20 (passes {desc_ptr, tag=1}, reads no desc field [V]); producer 0x5aca680 builds the stack description; Effect visitor 0x666aca0 tag-1 case 0x666aec2 consumes it.

Input data (read fully; no tools re-run to regenerate):
- docs/progress/oc_U-Blit.md — producer 0x5aca680, insert clone 0x5acbe20, element push_back 0x5acb9c0, element builder 0x6bf7260, vecview 0x5acbfe0; verbatim 0xRVA  instr lines from docs/data/listings/effect_blit_*.txt.
- docs/data/listings/effect_visitor_666aca0_667191c.txt — Effect visitor 0x666aca0, verbatim (tag-1 case entry 0x666aec2, shared tail, element loop 0x666b704..0x666c846).
- docs/functions/666aca0_blitflipbook.md — tag-1 case/tail dossier.
- docs/data/live_desc_sky_light_effect_1.26.62.01.txt — live effect-1 description capture (line 2).
- docs/BGFX_MAP.md R3/D7c/L4s/M2c; docs/RENDER_CHECKLIST.md R3.

<!-- TABLE -->

## Answer table

Columns: offset | size | read/store address | verbatim `0xRVA  instr` line | meaning [V/I/?]. Every quoted line is copied verbatim from the input data (all from rdis listings of the exe) and is checked by verify_oc. Sizes come from the instruction (movups 16, movsd 8, movss 4, qword 8, byte 1); rows without a sized memory operand in the quoted line carry the structural size.

| offset | size | read/store address | verbatim `0xRVA  instr` line | meaning [V/I/?] |
|---|---|---|---|---|
| desc +0x00..+0x0F | 16 | producer insert 0x5acb24f | `0x5acb24f  call 0x4DFB570` | desc+0x00..+0x0F = SharedRef {ptr,ctrl} built by the producer at insert (rcx=&desc+0x00, rdx=produced object); 16-byte write window per the 16-byte temp pattern used at 0x6bf7275/0x6bf733a [I]; NOT read by the consumer — desc reads are +0x10/+0x18 only (rows below). Insert clone 0x5acbe20 passes {desc_ptr, tag=1} and reads no desc field [V oc_U-Blit.md 0x5acbe20]. Live capture matches: +0x00 ptr, +0x08 ctrl [V live docs/data/live_desc_sky_light_effect_1.26.62.01.txt line 2]. |
| desc +0x10 | 8 | consumer tail 0x666b6cf | `0x666b6cf  mov rax,[r15+0x10]` | element count, read as the loop bound (0x666b6d7 `shl rax,6`, end = data + count<<6 stored at [rbp+0x660] by 0x666b6de; loop head `0x666b704 cmp r14,[rbp+0x660]`, exit `je 0x666c846`) [V]. Tag-1 case 0x666aec2 reaches this tail via 0x666B67C [V listing flow]. |
| desc +0x18 | 8 | consumer tail 0x666b6d3 | `0x666b6d3  mov r14,[r15+0x18]` | element array base, loop cursor r14 [V]. |
| desc +0x20..+0x9F | - | producer last store 0x5acb25a; consumer max read +0x18 | `0x5acb25a  movupd [rbp+0x40],xmm0` | Description object spans desc+0x00..+0x1F only: SharedRef@+0x00..+0x0F (row 1), then count+ptr stored as one 16-byte movupd covering desc+0x10..+0x1F (`0x5acb255 movupd xmm0,[rbp-0x48]` / `0x5acb25a movupd [rbp+0x40],xmm0`); nothing is stored or read at desc+0x20..+0x9F. TRUE SIZE = 0x20 (not the stale 0xA0 inference from over-wide producer stack windows) [V]; corroborated by Descriptions.h RenderBlitFlipbookDescription 0x20 and the live capture (+0x10 count=0x60, +0x18 elements ptr) [V live line 2]. |
| element +0x00 | 8 | consumer loop 0x666b942 | `0x666b942  mov rsi,[r14]` | element+0x00 mesh/object handle read by the consumer (second read `0x666b982 mov rsi,[r14]`) [V]. |
| element +0x08 | 8 | consumer loop 0x666b858 | `0x666b858  lea r8,[r14+8]` &element+0x08 (SharedRef subobject address) passed to the bind/setup helper (0xbcaba00) [V]. |
| element +0x18 | 8 | consumer loop 0x666b897 | `0x666b897  movsd xmm1,[r14+0x18]` | element+0x18 qword (blend XY) read by the consumer [V read; field meaning I]. |
| element +0x20 | 4 | consumer loop 0x666b891 | `0x666b891  movss xmm0,[r14+0x20]` | element+0x20 float (blend Z) read by the consumer [V read; field meaning I]. |
| element +0x24 | 16 | consumer loop 0x666ba25 | `0x666ba25  movups xmm0,[r14+0x24]` | element+0x24 16-byte block read by the consumer [V]. |
| element loop bounds | - | consumer 0x666b700 / 0x666b704 | `0x666b700  add r14,0x40` / `0x666b704  cmp r14,[rbp+0x660]` | element stride 0x40; end bound = desc+0x18 + (desc+0x10<<6) at [rbp+0x660]; exit to 0x666c846. An rdis scan of 0x666b704..0x666c846 for reads of [r14+0x28/0x2c/0x30/0x34/0x38/0x3c] found none [V tool evidence]. |
| element +0x34 | 8 | producer 0x5acba46; builder 0x6bf740a | `0x5acba46  mov rax,[rbx+0x34]` | element+0x34 qword: read as copy source by push_back (dest write `0x5acba4a mov [r15+0x34],rax`) and written by the builder as [saved r9+0x10] (`0x6bf740a mov [rsi+0x34],rax`); +0x35..+0x3B ride the same qword span; NOT read by the consumer loop (row above) [V]. |
| element +0x3C | 1 | producer 0x5acba52; builder 0x6bf740e | `0x5acba4e  movzx eax,byte ptr [rbx+0x3C]` | element+0x3C byte: read as copy source by push_back (dest write `0x5acba52 mov [r15+0x3C],al`); written 0 by the builder (`0x6bf740e mov byte ptr [rsi+0x3C],0`); NOT read by the consumer loop [V]. |
| element +0x3D..+0x3F | 3 | - | - | never accessed in the producer copy or the consumer loop; padding beyond the last defined element byte +0x3C [I]. |

Element size: 0x40 [V] — stride `add r14,0x40`; push_back/builder copy the full 0x40-byte element; last defined byte is +0x3C.

## CLOSES?

YES — every pending part of the R3 item line is resolved by [V] rows:
1. desc +0x00..+0x0F: producer-built SharedRef at insert (`0x5acb24f call 0x4DFB570`, [V]); not read by the consumer — the verified tag-1 path's desc read set is +0x10 (count, `0x666b6cf`) and +0x18 (elements ptr, `0x666b6d3`) only.
2. desc +0x20..+0x9F: beyond the description — true size is 0x20 (highest store covers desc+0x10..+0x1F via `0x5acb25a movupd [rbp+0x40],xmm0`, nothing stored/read at +0x20..+0x9F) [V], contradicting the stale 0xA0 claim; matches the live capture [V live line 2].
3. element +0x34..+0x3F: +0x34 qword and +0x3C byte are producer-copied (source reads `0x5acba46 mov rax,[rbx+0x34]` / `0x5acba52 movzx eax,byte ptr [rbx+0x3C]` and corresponding writes [V]); none of +0x34..+0x3F is read by the consumer loop — verified absence of [r14+0x28/2c/30/34/38/3c] in 0x666b704..0x666c846 [V]; +0x3D..+0x3F never accessed [I].
4. True size: description 0x20, element 0x40 [V].

Single blocking fact: none.

## TOOL REQUESTS

None

