## NEXT
DONE

# U-EL3m: L3m per-pass loop body fields 0xc277e8c..0xc2793fe (6cz)

Scope: checklist item "L3m per-pass loop located (0xc277e8c..0xc2793fe), dependency records = 24/40-byte vectors (6cz); body fields pending".
Not pending here (already located): the loop itself, bracketed by the two sub_c27ec60 call sites at 0xc277e8c and 0xc2793fe (C7b, oc_U-C7b.md, verify_oc 1139/1139; BGFX_MAP 6cz), and the dependency-record vectors: 40-byte at rbp+0x3330 begin / +0x3338 end / +0x3340 cap (stride 0x28, growth via sub_c27f940 at 0xc278508/0xc27859e/0xc278625), 24-byte at rbp+0x3348 begin / +0x3350 end / +0x3358 cap (stride 0x20, growth via sub_c27fcc0 at 0xc27881d/0xc278882).
Pending part done here: every field store in the per-pass loop body — the 0x80-byte per-pass record at r14=[rbp+0x32E8] (normal path, Phase 26 0xc278e7c..0xc278f7d) and at r15+r13 (empty path, Phase 33 0xc279245..0xc279308), plus the per-pass stack slots written in the body. All RVAs and instructions copied verbatim from docs/progress/pre/0xc277e8c.full.md (full listing, read in full). Sizes: movups/movaps/movdqu/movdqa = 16, qword/mov r64 = 8.

## Body field table (offset | size | name | meaning | tag | store address; proof lines listed under each row)

| offset | size | name | meaning | tag | store address |
| +0x00 | 8 | rec+0x00 (= entry+0x28) | qword from [rcx+0x28], rcx=[rbp+0x3460] (current entry); record head +0x00..+0x0F is zeroed by a 16-byte store before this field write; +0x00 = task object pointer per BGFX_MAP 6cx/6dc [I] | [V] | W [r14+0x00] normal path (r14=[rbp+0x32E8]); W [r15+r13+0x00] empty path |
  0xc278ec5  mov [r14],rax
  0xc279250  mov [r15+r13],rax
| +0x08 | 8 | rec+0x08 (= entry+0x30) | qword from [rcx+0x30], rcx=[rbp+0x3460] (current entry); +0x08 = shared_ptr control block per BGFX_MAP 6cx/6dc [I] | [V] | W [r14+0x08] normal path; W [r15+r13+0x08] empty path |
  0xc278ecc  mov [r14+8],rax
  0xc279258  mov [r15+r13+8],rax
| +0x10 | 16 | rec+0x10 | 16 bytes from xmm0, where xmm0 = [rbp+0x3310] (saved per-pass accumulator) | [V] | W [r14+0x10] normal path; W [r15+r13+0x10] empty path |
  0xc278ee7  movups [r14+0x10],xmm0
  0xc279275  movups [r15+r13+0x10],xmm0
| +0x1C | 16 | rec+0x1C | 16 bytes from xmm0, where xmm0 = [rbp+0x331C] | [V] | W [r14+0x1C] normal path; W [r15+r13+0x1C] empty path |
  0xc278edb  movups [r14+0x1C],xmm0
  0xc279268  movups [r15+r13+0x1C],xmm0
| +0x30 | 16 | rec+0x30 | 16-byte snapshot of [rbp+0x3330] (40-byte dependency-vector begin); vector zeroed right after | [V] | W [r14+0x30] normal path; W [r15+r13+0x30] empty path |
  0xc278f0d  movups [r14+0x30],xmm0
  0xc27929c  movups [r15+r13+0x30],xmm0
| +0x40 | 8 | rec+0x40 | qword snapshot of [rbp+0x3340] (40-byte dependency-vector cap); [rbp+0x3340] zeroed right after | [V] | W [r14+0x40] normal path; W [r15+r13+0x40] empty path |
  0xc278f12  mov [r14+0x40],rax
  0xc2792a2  mov [r15+r13+0x40],rax
| +0x48 | 16 | rec+0x48 | 16-byte snapshot of [rbp+0x3348] (24-byte dependency-vector begin); vector zeroed right after | [V] | W [r14+0x48] normal path; W [r15+r13+0x48] empty path |
  0xc278f37  movups [r14+0x48],xmm0
  0xc2792c8  movups [r15+r13+0x48],xmm0
| +0x58 | 8 | rec+0x58 | qword snapshot of [rbp+0x3358] (24-byte dependency-vector end); [rbp+0x3358] zeroed right after | [V] | W [r14+0x58] normal path; W [r15+r13+0x58] empty path |
  0xc278f3c  mov [r14+0x58],rax
  0xc2792ce  mov [r15+r13+0x58],rax
| +0x60 | 16 | rec+0x60 | 16-byte snapshot of [rbp+0x3360] (0x20-stride dependency-vector begin); vector zeroed right after | [V] | W [r14+0x60] normal path; W [r15+r13+0x60] empty path |
  0xc278f61  movups [r14+0x60],xmm0
  0xc2792f4  movups [r15+r13+0x60],xmm0
| +0x70 | 8 | rec+0x70 | qword snapshot of [rbp+0x3370] (0x20-stride dependency-vector cap); [rbp+0x3370] zeroed right after | [V] | W [r14+0x70] normal path; W [r15+r13+0x70] empty path |
  0xc278f66  mov [r14+0x70],rax
  0xc2792fa  mov [r15+r13+0x70],rax
| +0x78 | 8 | rec+0x78 | immediate 0 written at record end | [V] | W [r14+0x78] normal path; W [r15+r13+0x78] empty path |
  0xc278f6a  mov qword ptr [r14+0x78],0
  0xc2792ff  mov qword ptr [r15+r13+0x78],0
| rbp-0x50 + pass*16 | 16 | per-pass accumulator slot | 16 bytes from xmm0 ([rbp+0x1FC0]) at slot index = pass count; pass count = [rbp+0x1FB0], rax = pass << 4 | [V] | W [rbp+rax-0x50] |
  0xc278e8e  movups [rbp+rax-0x50],xmm0
| +0x1FB0 | 8 | per-pass pass counter | read as the pass index (rax=[rbp+0x1FB0], shl rax,4) then incremented once per pass | [V] | R [rbp+0x1FB0] (index), W [rbp+0x1FB0] (increment) |
  0xc278e83  mov rax,[rbp+0x1FB0]
  0xc278e93  inc qword ptr [rbp+0x1FB0]
| +0x3310 | 16 | xmm save slot | zeroed at loop entry (movdqa xmm7) then reloaded with xmm0 every pass; feeds rec+0x10 | [V] | W [rbp+0x3310] |
  0xc27808b  movdqa [rbp+0x3310],xmm7
  0xc278e9a  movaps [rbp+0x3310],xmm0

## Notes

- Offsets +0x0C..+0x0F belong to the zeroed record head; +0x2C..+0x2F are never written by the body (no store, tag [-]); every other record offset +0x00..+0x78 is covered by a row above. The record is advanced by `sub r14,0xFFFFFFFFFFFFFF80` (= r14 += 0x80) at 0xc278f72 and the base pointer is reloaded at 0xc278ea1 (`mov r14,[rbp+0x32E8]`).
- After the record is filled, the dependency vectors are zeroed in place (movdqa/movdqu xmm7 on [rbp+0x3330]/[rbp+0x3348]/[rbp+0x3360]) and their end/cap slots are nulled; these are vector clearances, not record fields.
- The relocation loop at 0xc279320..0xc2793fb (Phase 34) copies finished 0x80-byte records from r12 to r15 at the same field offsets (+0x00, +0x08, +0x10, +0x1C, +0x30, +0x40, +0x48, +0x58, +0x60, +0x70, +0x78), zeroing each source record as it goes — no new field offsets, no new store semantics.
- Tag key: [V] = store/load seen verbatim in the listing; [I] = object-role inference from BGFX_MAP 6cx/6dc (task object / shared_ptr control block); [-] = not written.

## Verification

- All proof lines above are quoted verbatim from docs/progress/pre/0xc277e8c.full.md and verified by `python tools/sigs/verify_oc.py docs/progress/oc_U-EL3m.md` (mismatch=0, no-such-instr=0).
- Gate: `python tools/delegate.py check docs/progress/oc_U-EL3m.md` exits 0.

CLOSES? YES — the pending part ("body fields pending") is proven by [V] rows: all eleven record field offsets (+0x00, +0x08, +0x10, +0x1C, +0x30, +0x40, +0x48, +0x58, +0x60, +0x70, +0x78) with both body-path stores (normal path at r14, empty path at r15+r13), plus the three body stack stores (accumulator slot rbp-0x50+pass*16, pass counter +0x1FB0, xmm save slot +0x3310). Loop location and the 24/40-byte dependency-record vectors were already located (C7b/BGFX_MAP 6cz) and are not re-decoded here. No blocking fact.

## TOOL REQUESTS

1. verify_oc.py and delegate.py check (existing tools, used as the gate above); no new helper scripts written.
