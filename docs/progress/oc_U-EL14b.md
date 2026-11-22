## NEXT
DONE

# Unit U-EL14b: L14b Ore UI / cohtml backend upload/draw

## Scope

Checklist item L14b: "Ore UI / cohtml: glue fn 0x52d26a0 + ui_textured_premultiplied_alpha (6cf); backend upload/draw pending".
- Glue fn 0x52d26a0 + ui_textured_premultiplied_alpha: already closed (I5b, oc_U-I5b.md). NOT part of this unit.
- This unit covers ONLY the pending part: backend upload/draw, i.e. the two callees of glue fn 0x52d26a0 that perform it:
  - 0xA01BDD0 (sub_a01bdd0) — Cohtml texture upload: zero-inits an ~0x410-byte upload record at rcx. Called from glue at 0x52d3c26 (`call 0xA01BDD0`) [V].
  - 0x1F383F0 (sub_1f383f0) — Draw command encoding: stores into the rcx-based command buffer. Called from glue at 0x52d3e29 (`call 0x1F383F0`) [V].
- BGFX_MAP.md section 6cf cites 0x52d26a0 as the Ore UI/cohtml anchor and states the backend's texture upload/draw functions were not decoded for 1.26.62.01; this unit decodes the store-level behavior of the two backend functions from the verified listings below.
- Source listings (already computed by the orchestrator, read in full; no tools re-run):
  - docs/listings/L_a01bdd0.txt — 0xA01BDD0, 94 lines, verified
  - docs/listings/L_1f383f0.txt — 0x1F383F0, 488 lines, verified
  - docs/listings/L_52d26a0.txt — glue listing, call sites 0x52d3c26 / 0x52d3e29 confirmed by grep

## Offset table (merged across both listings; one row per distinct offset, all its sites listed)

Size column leads with 16 (movups/movaps) where any such instruction touches the offset; otherwise the size of the store instruction (qword 8, dword 4, word 2, byte 1). Meaning is only what an instruction or string shows, tagged [V] (verbatim from listing) / [I] (inference from instruction shape or call context) / [-] (none shown).

| Offset | Size | Sites (RVA) | Verbatim `0xRVA  instr` proof line | Meaning ([V]/[I]/[-]) |
|--------|------|-------------|------------------------------------|------------------------|
| 0x00 | 16 | 0xa01bdf5, 0x1f38423, 0x1f385b7, 0x1f38880 | `0xa01bdf5  movups [rcx],xmm0`; `0x1f38423  mov [rcx],dl`; `0x1f385b7  mov [rcx],dl`; `0x1f38880  mov [rcx],dl` | 16B zero-init of upload-record start (xmm0 zeroed at 0xa01bde6) [V]; draw-command tag byte at +0x00, last two stores by hash chain-walk after byte extract from [rdx+0x10] (0x1f385b3) / [rdx+0x14] (0x1f3887c) [V] |
| 0x08 | 8 | 0x1f3842f | `0x1f3842f  mov [rcx+8],rax` | Pointer captured from r9 ([r9] read at 0x1f38425, then null-out `mov qword ptr [r9],0` at 0x1f38428) [V] |
| 0x10 | 16 | 0xa01bdf1, 0x1f3843d | `0xa01bdf1  movups [rcx+0x10],xmm0`; `0x1f3843d  mov [rcx+0x10],rax` | 16B zero-init [V]; pointer captured from r8 ([r8] read at 0x1f38433, null-out at 0x1f38436) [V] |
| 0x18 | 8 | 0x1f3844b | `0x1f3844b  mov [rcx+0x18],rax` | Pointer captured from r10 ([r10] read at 0x1f38441, null-out at 0x1f38444) [V] |
| 0x20 | 16 | 0xa01bded, 0x1f3844f | `0xa01bded  movups [rcx+0x20],xmm0`; `0x1f3844f  movups [rcx+0x20],xmm0` | 16B zero-init x2 (upload-record field; draw-cmd xmm0 loaded from [rbp+0xF8] at 0x1f3841c) [V] |
| 0x30 | 16 | 0xa01bde9, 0x1f38456, 0x1f38472 | `0xa01bde9  movups [rcx+0x30],xmm0`; `0x1f38456  movups [rcx+0x30],xmm0`; `0x1f38472  mov [rcx+0x30],rdx` | 16B zero-init x2 [V]; object pointer from [r11] ([r11+8] refcount inc'd `lock inc dword ptr [rax+8]` at 0x1f38463) [V] |
| 0x38 | 8 | 0x1f38476 | `0x1f38476  mov [rcx+0x38],rax` | Refcounted pointer from [r11+8] (refcount inc'd at 0x1f38463) [V] |
| 0x40 | 1 | 0xa01bdf8, 0x1f3847e | `0xa01bdf8  mov byte ptr [rcx+0x40],0`; `0x1f3847e  mov [rcx+0x40],rax` | Zero byte flag [V] at 0xa01bdf8; pointer from [r11+0x10] (read at 0x1f3847a) [V] |
| 0x48 | 16 | 0xa01bf74, 0x1f384b1, 0x1f384e5 | `0xa01bf74  movups [rcx+0x48],xmm0`; `0x1f384b1  movups [rcx+0x48],xmm0`; `0x1f384e5  mov [rcx+0x48],rdx` | 16B zero-init x2 [V]; pointer from [r8] ([r8+8] refcount inc'd `lock inc dword ptr [rdx+8]` at 0x1f384be) [V] |
| 0x50 | 8 | 0x1f384ed | `0x1f384ed  mov [rcx+0x50],rdx` | Pointer from [r8+8] (refcount inc'd at 0x1f384be) [V] |
| 0x58 | 16 | 0xa01bf70, 0x1f384f5 | `0xa01bf70  movups [rcx+0x58],xmm0`; `0x1f384f5  mov [rcx+0x58],rdx` | 16B zero-init [V]; pointer from [r8+0x10] [V] |
| 0x60 | 2 | 0x1f384f9 | `0x1f384f9  mov word ptr [rcx+0x60],0` | Zero word [V] |
| 0x62 | 1 | 0x1f384ff | `0x1f384ff  mov [rcx+0x62],al` | Byte flag from stack arg ([rbp+0x118] read at 0x1f384aa) [V] |
| 0x63 | 1 | 0x1f38502 | `0x1f38502  mov byte ptr [rcx+0x63],0` | Zero byte [V] |
| 0x68 | 16 | 0xa01bf6c, 0x1f38524 | `0xa01bf6c  movups [rcx+0x68],xmm0`; `0x1f38524  movups [rcx+0x68],xmm0` | 16B zero-init x2 [V] |
| 0x78 | 16 | 0xa01bf68, 0x1f38528 | `0xa01bf68  movups [rcx+0x78],xmm0`; `0x1f38528  mov byte ptr [rcx+0x78],0` | 16B zero-init then zero byte [V] |
| 0x80 | 16 | 0x1f3852c | `0x1f3852c  movups [rcx+0x80],xmm0` | 16B zero-init [V] |
| 0x88 | 16 | 0xa01bf61 | `0xa01bf61  movups [rcx+0x88],xmm0` | 16B zero-init, upload-record field [V] |
| 0x90 | 16 | 0x1f38533 | `0x1f38533  movups [rcx+0x90],xmm0` | 16B zero-init [V] |
| 0x98 | 16 | 0xa01bf5a | `0xa01bf5a  movups [rcx+0x98],xmm0` | 16B zero-init, upload-record field [V] |
| 0xA0 | 8 | 0x1f3853a | `0x1f3853a  mov qword ptr [rcx+0xA0],0` | Zero qword [V] |
| 0xA8 | 16 | 0xa01bf53 | `0xa01bf53  movups [rcx+0xA8],xmm0` | 16B zero-init, upload-record field [V] |
| 0xB8 | 16 | 0xa01bf4c | `0xa01bf4c  movups [rcx+0xB8],xmm0` | 16B zero-init, upload-record field [V] |
| 0xC8 | 16 | 0xa01bf45 | `0xa01bf45  movups [rcx+0xC8],xmm0` | 16B zero-init, upload-record field [V] |
| 0xD8 | 16 | 0xa01bf3e | `0xa01bf3e  movups [rcx+0xD8],xmm0` | 16B zero-init, upload-record field [V] |
| 0xF0 | 1 | 0xa01bdfc | `0xa01bdfc  mov byte ptr [rcx+0xF0],0` | Zero byte flag [V] |
| 0x100 | 1 | 0xa01be03 | `0xa01be03  mov byte ptr [rcx+0x100],0` | Zero byte flag [V] |
| 0x110 | 1 | 0xa01be0a | `0xa01be0a  mov byte ptr [rcx+0x110],0` | Zero byte flag [V] |
| 0x120 | 1 | 0xa01be11 | `0xa01be11  mov byte ptr [rcx+0x120],0` | Zero byte flag [V] |
| 0x130 | 1 | 0xa01be18 | `0xa01be18  mov byte ptr [rcx+0x130],0` | Zero byte flag [V] |
| 0x140 | 1 | 0xa01be1f | `0xa01be1f  mov byte ptr [rcx+0x140],0` | Zero byte flag [V] |
| 0x150 | 1 | 0xa01be26 | `0xa01be26  mov byte ptr [rcx+0x150],0` | Zero byte flag [V] |
| 0x160 | 1 | 0xa01be2d | `0xa01be2d  mov byte ptr [rcx+0x160],0` | Zero byte flag [V] |
| 0x170 | 1 | 0xa01be34 | `0xa01be34  mov byte ptr [rcx+0x170],0` | Zero byte flag [V] |
| 0x180 | 1 | 0xa01be3b | `0xa01be3b  mov byte ptr [rcx+0x180],0` | Zero byte flag [V] |
| 0x190 | 1 | 0xa01be42 | `0xa01be42  mov byte ptr [rcx+0x190],0` | Zero byte flag [V] |
| 0x1A0 | 1 | 0xa01be49 | `0xa01be49  mov byte ptr [rcx+0x1A0],0` | Zero byte flag [V] |
| 0x1B0 | 1 | 0xa01be50 | `0xa01be50  mov byte ptr [rcx+0x1B0],0` | Zero byte flag [V] |
| 0x1C0 | 1 | 0xa01be57 | `0xa01be57  mov byte ptr [rcx+0x1C0],0` | Zero byte flag [V] |
| 0x1D0 | 1 | 0xa01be5e | `0xa01be5e  mov byte ptr [rcx+0x1D0],0` | Zero byte flag [V] |
| 0x1E0 | 1 | 0xa01be65 | `0xa01be65  mov byte ptr [rcx+0x1E0],0` | Zero byte flag [V] |
| 0x1F0 | 1 | 0xa01be6c | `0xa01be6c  mov byte ptr [rcx+0x1F0],0` | Zero byte flag [V] |
| 0x200 | 1 | 0xa01be73 | `0xa01be73  mov byte ptr [rcx+0x200],0` | Zero byte flag [V] |
| 0x210 | 1 | 0xa01be7a | `0xa01be7a  mov byte ptr [rcx+0x210],0` | Zero byte flag [V] |
| 0x220 | 1 | 0xa01be81 | `0xa01be81  mov byte ptr [rcx+0x220],0` | Zero byte flag [V] |
| 0x230 | 1 | 0xa01be88 | `0xa01be88  mov byte ptr [rcx+0x230],0` | Zero byte flag [V] |
| 0x240 | 1 | 0xa01be8f | `0xa01be8f  mov byte ptr [rcx+0x240],0` | Zero byte flag [V] |
| 0x250 | 1 | 0xa01be96 | `0xa01be96  mov byte ptr [rcx+0x250],0` | Zero byte flag [V] |
| 0x260 | 1 | 0xa01be9d | `0xa01be9d  mov byte ptr [rcx+0x260],0` | Zero byte flag [V] |
| 0x270 | 1 | 0xa01bea4 | `0xa01bea4  mov byte ptr [rcx+0x270],0` | Zero byte flag [V] |
| 0x280 | 1 | 0xa01beab | `0xa01beab  mov byte ptr [rcx+0x280],0` | Zero byte flag [V] |
| 0x290 | 1 | 0xa01beb2 | `0xa01beb2  mov byte ptr [rcx+0x290],0` | Zero byte flag [V] |
| 0x2A0 | 1 | 0xa01beb9 | `0xa01beb9  mov byte ptr [rcx+0x2A0],0` | Zero byte flag [V] |
| 0x2B0 | 1 | 0xa01bec0 | `0xa01bec0  mov byte ptr [rcx+0x2B0],0` | Zero byte flag [V] |
| 0x2C0 | 1 | 0xa01bec7 | `0xa01bec7  mov byte ptr [rcx+0x2C0],0` | Zero byte flag [V] |
| 0x2D0 | 1 | 0xa01bece | `0xa01bece  mov byte ptr [rcx+0x2D0],0` | Zero byte flag [V] |
| 0x2E0 | 1 | 0xa01bed5 | `0xa01bed5  mov byte ptr [rcx+0x2E0],0` | Zero byte flag [V] |
| 0x2F0 | 1 | 0xa01bedc | `0xa01bedc  mov byte ptr [rcx+0x2F0],0` | Zero byte flag [V] |
| 0x300 | 1 | 0xa01bee3 | `0xa01bee3  mov byte ptr [rcx+0x300],0` | Zero byte flag [V] |
| 0x310 | 1 | 0xa01beea | `0xa01beea  mov byte ptr [rcx+0x310],0` | Zero byte flag [V] |
| 0x320 | 1 | 0xa01bef1 | `0xa01bef1  mov byte ptr [rcx+0x320],0` | Zero byte flag [V] |
| 0x330 | 1 | 0xa01bef8 | `0xa01bef8  mov byte ptr [rcx+0x330],0` | Zero byte flag [V] |
| 0x340 | 1 | 0xa01beff | `0xa01beff  mov byte ptr [rcx+0x340],0` | Zero byte flag [V] |
| 0x350 | 1 | 0xa01bf06 | `0xa01bf06  mov byte ptr [rcx+0x350],0` | Zero byte flag [V] |
| 0x360 | 1 | 0xa01bf0d | `0xa01bf0d  mov byte ptr [rcx+0x360],0` | Zero byte flag [V] |
| 0x368 | 16 | 0xa01bf37 | `0xa01bf37  movups [rcx+0x368],xmm0` | 16B zero-init, upload-record field [V] |
| 0x378 | 16 | 0xa01bf30 | `0xa01bf30  movups [rcx+0x378],xmm0` | 16B zero-init, upload-record field [V] |
| 0x388 | 16 | 0xa01bf29 | `0xa01bf29  movups [rcx+0x388],xmm0` | 16B zero-init, upload-record field [V] |
| 0x398 | 16 | 0xa01bf22 | `0xa01bf22  movups [rcx+0x398],xmm0` | 16B zero-init, upload-record field [V] |
| 0x3A8 | 16 | 0xa01bf1b | `0xa01bf1b  movups [rcx+0x3A8],xmm0` | 16B zero-init, upload-record field [V] |
| 0x3B8 | 16 | 0xa01bf14 | `0xa01bf14  movups [rcx+0x3B8],xmm0` | 16B zero-init, upload-record field [V] |
| 0x3D0 | 16 | 0xa01bf9f | `0xa01bf9f  movups [rcx+0x3D0],xmm0` | 16B zero-init of callback slot [V]; slot written by external call 0xA01C030 idx 0x1EA at 0xa01bfc1 (call target not in this listing) [I] |
| 0x3E0 | 16 | 0xa01bf98 | `0xa01bf98  movups [rcx+0x3E0],xmm0` | 16B zero-init of callback slot [V]; slot written by external call 0xA01C030 idx 0x1EB at 0xa01bfde (call target not in this listing) [I] |
| 0x3F0 | 16 | 0xa01bf91 | `0xa01bf91  movups [rcx+0x3F0],xmm0` | 16B zero-init, upload-record field [V] |
| 0x400 | 8 | 0xa01bfaa | `0xa01bfaa  mov qword ptr [rcx+0x400],0` | Zero qword (userdata field) [V]; userdata arg rdx passed to external call 0xA01C030 at 0xa01bfc1/0xa01bfde (target not in this listing) [I] |

## What is proven (store level, all [V] rows)

Upload (0xA01BDD0, called from glue 0x52d26a0 at 0x52d3c26 [V]): builds a ~0x410-byte Cohtml texture upload record at rcx — zero-init of +0x00..+0x3F0 (16B movups blocks at +0x00, +0x10, +0x20, +0x30, +0x48..+0xD8, +0x368..+0x3F0) and flag bytes at +0x40, +0xF0, +0x100..+0x360 — then wires two upload callbacks through external calls 0xA01C030 with indices 0x1EA (0xa01bfc1) and 0x1EB (0xa01bfde), passing the userdata argument (rdx) to both, and zeroes the userdata field at +0x400. No pixel transfer is visible here; the upload is driven through those callbacks whose targets are outside this listing.

Draw (0x1F383F0, called from glue 0x52d26a0 at 0x52d3e29 [V]): encodes a draw command into the rcx command buffer — tag byte at +0x00 (rewritten twice by the hash chain-walk with hash 0xD2ACA77479857640, tag byte extracted at [rdx+0x10]/[rdx+0x14]), captured pointers at +0x08/+0x10/+0x18 (sources nulled after capture), object references at +0x30/+0x38/+0x40 with refcount increments (`lock inc dword ptr [rax+8]` at 0x1f38463; `lock inc dword ptr [rdx+8]` at 0x1f384be), zero fields at +0x20/+0x48..+0xA0, and full refcount/destructor cleanup through CFG thunk 0xF99FFA0 (virtual calls 0x187 at 0x1f38572 and 0x185 at 0x1f387eb). Draw-call setup caller 0xA0228E0 (called at 0x52d3cc1) is a separate glue-level step, not part of this unit.

Field semantic names (what cohtml calls each upload-record or draw-command field) are not shown by any instruction or string in either listing; they are not claimed. The only tags beyond literal instruction observation are the callback-slot and userdata interpretations at +0x3D0/+0x3E0/+0x400, marked [I] because the writing calls (0xA01C030) are external to these listings.

## CLOSES?

YES — backend upload/draw proven [V]: 0xA01BDD0 (glue call site 0x52d3c26) constructs the Cohtml texture upload record (~0x410B, all stores verbatim-verified) and wires its two callbacks via 0xA01C030 idx 0x1EA/0x1EB; 0x1F383F0 (glue call site 0x52d3e29) encodes the draw command (tag byte, captured pointers, refcounted object refs, hash chain-walk tag 0xD2ACA77479857640, vcalls 0x187/0x185, full cleanup). Every table row is backed by a verbatim `0xRVA  instr` line [V]. Not claimed (not part of the [V] proof): per-field semantic names and the callback target bodies — both outside the input listings.

## TOOL REQUESTS

None — all input data was precomputed listing files; no helper script was needed.

