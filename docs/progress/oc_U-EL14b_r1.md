## NEXT
DONE

# Unit U-EL14b: L14b Ore UI / cohtml backend upload/draw

## Scope

Checklist item L14b: "Ore UI / cohtml: glue fn 0x52d26a0 + ui_textured_premultiplied_alpha (6cf); backend upload/draw pending".
- Glue fn 0x52d26a0 + ui_textured_premultiplied_alpha: already closed (I5b, oc_U-I5b.md).
- This unit covers ONLY the pending part: **backend upload/draw**.
- Source listings (already computed by orchestrator, read in full):
  - docs/listings/L_a01bdd0.txt — 0xA01BDD0 (sub_a01bdd0), Cohtml texture upload, zero-inits an ~0x410-byte upload record at rcx.
  - docs/listings/L_1f383f0.txt — 0x1F383F0 (sub_1f383f0), Draw command encoding, stores into rcx-based command buffer.

## Backend upload/draw offset table

One row per distinct offset, all sites listed (merged across both listings). Size column leads with the movups/movaps size (16) where any such instruction touches the offset, to satisfy verify_oc size cross-check.

| Offset | Size | Sites (RVA) | Verbatim `0xRVA  instr` lines | Meaning |
|--------|------|-------------|-------------------------------|---------|
| 0x00 | 16 | 0xa01bdf5, 0x1f38423, 0x1f385b7, 0x1f38880 | `0xa01bdf5  movups [rcx],xmm0`; `0x1f38423  mov [rcx],dl`; `0x1f385b7  mov [rcx],dl`; `0x1f38880  mov [rcx],dl` | Zero-init (16B) then tag-byte writes (1B each, 3 sites) |
| 0x08 | 8 | 0x1f3842f | `0x1f3842f  mov [rcx+8],rax` | Pointer from r9, source null-out at 0x1f38428 |
| 0x10 | 16 | 0xa01bdf1, 0x1f3843d | `0xa01bdf1  movups [rcx+0x10],xmm0`; `0x1f3843d  mov [rcx+0x10],rax` | Zero-init then pointer from r8, source null-out at 0x1f38436 |
| 0x18 | 8 | 0x1f3844b | `0x1f3844b  mov [rcx+0x18],rax` | Pointer from r10, source null-out at 0x1f38444 |
| 0x20 | 16 | 0xa01bded, 0x1f3844f | `0xa01bded  movups [rcx+0x20],xmm0`; `0x1f3844f  movups [rcx+0x20],xmm0` | Zero-init (upload record) / zero-init (draw cmd, xmm0 from [rbp+0xF8]) |
| 0x30 | 16 | 0xa01bde9, 0x1f38456, 0x1f38472 | `0xa01bde9  movups [rcx+0x30],xmm0`; `0x1f38456  movups [rcx+0x30],xmm0`; `0x1f38472  mov [rcx+0x30],rdx` | Zero-init x2 then object pointer from [r11] |
| 0x38 | 8 | 0x1f38476 | `0x1f38476  mov [rcx+0x38],rax` | Refcounted ptr from [r11+8], inc'd at 0x1f38463 |
| 0x40 | 1 | 0xa01bdf8, 0x1f3847e | `0xa01bdf8  mov byte ptr [rcx+0x40],0`; `0x1f3847e  mov [rcx+0x40],rax` | Zero byte flag then pointer from [r11+0x10] |
| 0x48 | 16 | 0xa01bf74, 0x1f384b1, 0x1f384e5 | `0xa01bf74  movups [rcx+0x48],xmm0`; `0x1f384b1  movups [rcx+0x48],xmm0`; `0x1f384e5  mov [rcx+0x48],rdx` | Zero-init x2 then pointer from [r8] |
| 0x50 | 8 | 0x1f384ed | `0x1f384ed  mov [rcx+0x50],rdx` | Pointer from [r8+8], inc'd at 0x1f384be |
| 0x58 | 16 | 0xa01bf70, 0x1f384f5 | `0xa01bf70  movups [rcx+0x58],xmm0`; `0x1f384f5  mov [rcx+0x58],rdx` | Zero-init then pointer from [r8+0x10] |
| 0x60 | 2 | 0x1f384f9 | `0x1f384f9  mov word ptr [rcx+0x60],0` | Zero word |
| 0x62 | 1 | 0x1f384ff | `0x1f384ff  mov [rcx+0x62],al` | Byte flag from [rbp+0x118] |
| 0x63 | 1 | 0x1f38502 | `0x1f38502  mov byte ptr [rcx+0x63],0` | Zero byte |
| 0x68 | 16 | 0xa01bf6c, 0x1f38524 | `0xa01bf6c  movups [rcx+0x68],xmm0`; `0x1f38524  movups [rcx+0x68],xmm0` | Zero-init x2 |
| 0x78 | 16 | 0xa01bf68, 0x1f38528 | `0xa01bf68  movups [rcx+0x78],xmm0`; `0x1f38528  mov byte ptr [rcx+0x78],0` | Zero-init then zero byte |
| 0x80 | 16 | 0x1f3852c | `0x1f3852c  movups [rcx+0x80],xmm0` | Zero-init |
| 0x88 | 16 | 0xa01bf61 | `0xa01bf61  movups [rcx+0x88],xmm0` | Zero-init upload record field |
| 0x90 | 16 | 0x1f38533 | `0x1f38533  movups [rcx+0x90],xmm0` | Zero-init |
| 0x98 | 16 | 0xa01bf5a | `0xa01bf5a  movups [rcx+0x98],xmm0` | Zero-init upload record field |
| 0xA0 | 8 | 0x1f3853a | `0x1f3853a  mov qword ptr [rcx+0xA0],0` | Zero qword |
| 0xA8 | 16 | 0xa01bf53 | `0xa01bf53  movups [rcx+0xA8],xmm0` | Zero-init upload record field |
| 0xB8 | 16 | 0xa01bf4c | `0xa01bf4c  movups [rcx+0xB8],xmm0` | Zero-init upload record field |
| 0xC8 | 16 | 0xa01bf45 | `0xa01bf45  movups [rcx+0xC8],xmm0` | Zero-init upload record field |
| 0xD8 | 16 | 0xa01bf3e | `0xa01bf3e  movups [rcx+0xD8],xmm0` | Zero-init upload record field |
| 0xF0 | 1 | 0xa01bdfc | `0xa01bdfc  mov byte ptr [rcx+0xF0],0` | Zero byte flag |
| 0x100 | 1 | 0xa01be03 | `0xa01be03  mov byte ptr [rcx+0x100],0` | Zero byte flag |
| 0x110 | 1 | 0xa01be0a | `0xa01be0a  mov byte ptr [rcx+0x110],0` | Zero byte flag |
| 0x120 | 1 | 0xa01be11 | `0xa01be11  mov byte ptr [rcx+0x120],0` | Zero byte flag |
| 0x130 | 1 | 0xa01be18 | `0xa01be18  mov byte ptr [rcx+0x130],0` | Zero byte flag |
| 0x140 | 1 | 0xa01be1f | `0xa01be1f  mov byte ptr [rcx+0x140],0` | Zero byte flag |
| 0x150 | 1 | 0xa01be26 | `0xa01be26  mov byte ptr [rcx+0x150],0` | Zero byte flag |
| 0x160 | 1 | 0xa01be2d | `0xa01be2d  mov byte ptr [rcx+0x160],0` | Zero byte flag |
| 0x170 | 1 | 0xa01be34 | `0xa01be34  mov byte ptr [rcx+0x170],0` | Zero byte flag |
| 0x180 | 1 | 0xa01be3b | `0xa01be3b  mov byte ptr [rcx+0x180],0` | Zero byte flag |
| 0x190 | 1 | 0xa01be42 | `0xa01be42  mov byte ptr [rcx+0x190],0` | Zero byte flag |
| 0x1A0 | 1 | 0xa01be49 | `0xa01be49  mov byte ptr [rcx+0x1A0],0` | Zero byte flag |
| 0x1B0 | 1 | 0xa01be50 | `0xa01be50  mov byte ptr [rcx+0x1B0],0` | Zero byte flag |
| 0x1C0 | 1 | 0xa01be57 | `0xa01be57  mov byte ptr [rcx+0x1C0],0` | Zero byte flag |
| 0x1D0 | 1 | 0xa01be5e | `0xa01be5e  mov byte ptr [rcx+0x1D0],0` | Zero byte flag |
| 0x1E0 | 1 | 0xa01be65 | `0xa01be65  mov byte ptr [rcx+0x1E0],0` | Zero byte flag |
| 0x1F0 | 1 | 0xa01be6c | `0xa01be6c  mov byte ptr [rcx+0x1F0],0` | Zero byte flag |
| 0x200 | 1 | 0xa01be73 | `0xa01be73  mov byte ptr [rcx+0x200],0` | Zero byte flag |
| 0x210 | 1 | 0xa01be7a | `0xa01be7a  mov byte ptr [rcx+0x210],0` | Zero byte flag |
| 0x220 | 1 | 0xa01be81 | `0xa01be81  mov byte ptr [rcx+0x220],0` | Zero byte flag |
| 0x230 | 1 | 0xa01be88 | `0xa01be88  mov byte ptr [rcx+0x230],0` | Zero byte flag |
| 0x240 | 1 | 0xa01be8f | `0xa01be8f  mov byte ptr [rcx+0x240],0` | Zero byte flag |
| 0x250 | 1 | 0xa01be96 | `0xa01be96  mov byte ptr [rcx+0x250],0` | Zero byte flag |
| 0x260 | 1 | 0xa01be9d | `0xa01be9d  mov byte ptr [rcx+0x260],0` | Zero byte flag |
| 0x270 | 1 | 0xa01bea4 | `0xa01bea4  mov byte ptr [rcx+0x270],0` | Zero byte flag |
| 0x280 | 1 | 0xa01beab | `0xa01beab  mov byte ptr [rcx+0x280],0` | Zero byte flag |
| 0x290 | 1 | 0xa01beb2 | `0xa01beb2  mov byte ptr [rcx+0x290],0` | Zero byte flag |
| 0x2A0 | 1 | 0xa01beb9 | `0xa01beb9  mov byte ptr [rcx+0x2A0],0` | Zero byte flag |
| 0x2B0 | 1 | 0xa01bec0 | `0xa01bec0  mov byte ptr [rcx+0x2B0],0` | Zero byte flag |
| 0x2C0 | 1 | 0xa01bec7 | `0xa01bec7  mov byte ptr [rcx+0x2C0],0` | Zero byte flag |
| 0x2D0 | 1 | 0xa01bece | `0xa01bece  mov byte ptr [rcx+0x2D0],0` | Zero byte flag |
| 0x2E0 | 1 | 0xa01bed5 | `0xa01bed5  mov byte ptr [rcx+0x2E0],0` | Zero byte flag |
| 0x2F0 | 1 | 0xa01bedc | `0xa01bedc  mov byte ptr [rcx+0x2F0],0` | Zero byte flag |
| 0x300 | 1 | 0xa01bee3 | `0xa01bee3  mov byte ptr [rcx+0x300],0` | Zero byte flag |
| 0x310 | 1 | 0xa01beea | `0xa01beea  mov byte ptr [rcx+0x310],0` | Zero byte flag |
| 0x320 | 1 | 0xa01bef1 | `0xa01bef1  mov byte ptr [rcx+0x320],0` | Zero byte flag |
| 0x330 | 1 | 0xa01bef8 | `0xa01bef8  mov byte ptr [rcx+0x330],0` | Zero byte flag |
| 0x340 | 1 | 0xa01beff | `0xa01beff  mov byte ptr [rcx+0x340],0` | Zero byte flag |
| 0x350 | 1 | 0xa01bf06 | `0xa01bf06  mov byte ptr [rcx+0x350],0` | Zero byte flag |
| 0x360 | 1 | 0xa01bf0d | `0xa01bf0d  mov byte ptr [rcx+0x360],0` | Zero byte flag |
| 0x368 | 16 | 0xa01bf37 | `0xa01bf37  movups [rcx+0x368],xmm0` | Zero-init upload record field |
| 0x378 | 16 | 0xa01bf30 | `0xa01bf30  movups [rcx+0x378],xmm0` | Zero-init upload record field |
| 0x388 | 16 | 0xa01bf29 | `0xa01bf29  movups [rcx+0x388],xmm0` | Zero-init upload record field |
| 0x398 | 16 | 0xa01bf22 | `0xa01bf22  movups [rcx+0x398],xmm0` | Zero-init upload record field |
| 0x3A8 | 16 | 0xa01bf1b | `0xa01bf1b  movups [rcx+0x3A8],xmm0` | Zero-init upload record field |
| 0x3B8 | 16 | 0xa01bf14 | `0xa01bf14  movups [rcx+0x3B8],xmm0` | Zero-init upload record field |
| 0x3D0 | 16 | 0xa01bf9f | `0xa01bf9f  movups [rcx+0x3D0],xmm0` | Zero-init callback slot |
| 0x3E0 | 16 | 0xa01bf98 | `0xa01bf98  movups [rcx+0x3E0],xmm0` | Zero-init callback slot |
| 0x3F0 | 16 | 0xa01bf91 | `0xa01bf91  movups [rcx+0x3F0],xmm0` | Zero-init callback slot |
| 0x400 | 8 | 0xa01bfaa | `0xa01bfaa  mov qword ptr [rcx+0x400],0` | Zero-init userdata pointer |

## Meaning notes

- Every store in 0xA01BDD0 is zero-initialization of the Cohtml texture upload record (~0x410 bytes). No instruction or string in the listing assigns a semantic name to any individual upload-record field; meanings shown are "Zero-init" / "Zero byte flag" / "Zero-init userdata pointer", which are what the instructions themselves show.
- Every store in 0x1F383F0 is into the Cohtml draw command buffer. The tag byte at +0x00 is rewritten by chain-walk hash lookups at 0x1f385b7 and 0x1f38880. Field meanings beyond pointer copies and zero-init are not shown by any instruction or string in the listing; marked by description of what the instruction does, not by any proven semantic name.

## CLOSES?

NO — every offset row is backed by verbatim `0xRVA  instr` lines copied from verified listings ([V] for the store operations themselves), but the semantic roles of the upload-record fields and draw-command fields (what Cohtml's backend calls them, what it consumes them as) are not proven by any instruction or string in either listing; they remain [I] inferences carried over from oc_U-I5f.md. The single blocking fact: no instruction or string in 0xA01BDD0 or 0x1F383F0 names or semantically tags any individual upload-record or draw-command field offset.

## Verification lines (standalone, for verify_oc.py)

    0xa01bdf5  movups [rcx],xmm0
    0x1f38423  mov [rcx],dl
    0x1f385b7  mov [rcx],dl
    0x1f38880  mov [rcx],dl
    0x1f3842f  mov [rcx+8],rax
    0xa01bdf1  movups [rcx+0x10],xmm0
    0x1f3843d  mov [rcx+0x10],rax
    0x1f3844b  mov [rcx+0x18],rax
    0xa01bded  movups [rcx+0x20],xmm0
    0x1f3844f  movups [rcx+0x20],xmm0
    0xa01bde9  movups [rcx+0x30],xmm0
    0x1f38456  movups [rcx+0x30],xmm0
    0x1f38472  mov [rcx+0x30],rdx
    0x1f38476  mov [rcx+0x38],rax
    0xa01bdf8  mov byte ptr [rcx+0x40],0
    0x1f3847e  mov [rcx+0x40],rax
    0xa01bf74  movups [rcx+0x48],xmm0
    0x1f384b1  movups [rcx+0x48],xmm0
    0x1f384e5  mov [rcx+0x48],rdx
    0x1f384ed  mov [rcx+0x50],rdx
    0xa01bf70  movups [rcx+0x58],xmm0
    0x1f384f5  mov [rcx+0x58],rdx
    0x1f384f9  mov word ptr [rcx+0x60],0
    0x1f384ff  mov [rcx+0x62],al
    0x1f38502  mov byte ptr [rcx+0x63],0
    0xa01bf6c  movups [rcx+0x68],xmm0
    0x1f38524  movups [rcx+0x68],xmm0
    0xa01bf68  movups [rcx+0x78],xmm0
    0x1f38528  mov byte ptr [rcx+0x78],0
    0x1f3852c  movups [rcx+0x80],xmm0
    0xa01bf61  movups [rcx+0x88],xmm0
    0x1f38533  movups [rcx+0x90],xmm0
    0xa01bf5a  movups [rcx+0x98],xmm0
    0x1f3853a  mov qword ptr [rcx+0xA0],0
    0xa01bf53  movups [rcx+0xA8],xmm0
    0xa01bf4c  movups [rcx+0xB8],xmm0
    0xa01bf45  movups [rcx+0xC8],xmm0
    0xa01bf3e  movups [rcx+0xD8],xmm0
    0xa01bdfc  mov byte ptr [rcx+0xF0],0
    0xa01be03  mov byte ptr [rcx+0x100],0
    0xa01be0a  mov byte ptr [rcx+0x110],0
    0xa01be11  mov byte ptr [rcx+0x120],0
    0xa01be18  mov byte ptr [rcx+0x130],0
    0xa01be1f  mov byte ptr [rcx+0x140],0
    0xa01be26  mov byte ptr [rcx+0x150],0
    0xa01be2d  mov byte ptr [rcx+0x160],0
    0xa01be34  mov byte ptr [rcx+0x170],0
    0xa01be3b  mov byte ptr [rcx+0x180],0
    0xa01be42  mov byte ptr [rcx+0x190],0
    0xa01be49  mov byte ptr [rcx+0x1A0],0
    0xa01be50  mov byte ptr [rcx+0x1B0],0
    0xa01be57  mov byte ptr [rcx+0x1C0],0
    0xa01be5e  mov byte ptr [rcx+0x1D0],0
    0xa01be65  mov byte ptr [rcx+0x1E0],0
    0xa01be6c  mov byte ptr [rcx+0x1F0],0
    0xa01be73  mov byte ptr [rcx+0x200],0
    0xa01be7a  mov byte ptr [rcx+0x210],0
    0xa01be81  mov byte ptr [rcx+0x220],0
    0xa01be88  mov byte ptr [rcx+0x230],0
    0xa01be8f  mov byte ptr [rcx+0x240],0
    0xa01be96  mov byte ptr [rcx+0x250],0
    0xa01be9d  mov byte ptr [rcx+0x260],0
    0xa01bea4  mov byte ptr [rcx+0x270],0
    0xa01beab  mov byte ptr [rcx+0x280],0
    0xa01beb2  mov byte ptr [rcx+0x290],0
    0xa01beb9  mov byte ptr [rcx+0x2A0],0
    0xa01bec0  mov byte ptr [rcx+0x2B0],0
    0xa01bec7  mov byte ptr [rcx+0x2C0],0
    0xa01bece  mov byte ptr [rcx+0x2D0],0
    0xa01bed5  mov byte ptr [rcx+0x2E0],0
    0xa01bedc  mov byte ptr [rcx+0x2F0],0
    0xa01bee3  mov byte ptr [rcx+0x300],0
    0xa01beea  mov byte ptr [rcx+0x310],0
    0xa01bef1  mov byte ptr [rcx+0x320],0
    0xa01bef8  mov byte ptr [rcx+0x330],0
    0xa01beff  mov byte ptr [rcx+0x340],0
    0xa01bf06  mov byte ptr [rcx+0x350],0
    0xa01bf0d  mov byte ptr [rcx+0x360],0
    0xa01bf37  movups [rcx+0x368],xmm0
    0xa01bf30  movups [rcx+0x378],xmm0
    0xa01bf29  movups [rcx+0x388],xmm0
    0xa01bf22  movups [rcx+0x398],xmm0
    0xa01bf1b  movups [rcx+0x3A8],xmm0
    0xa01bf14  movups [rcx+0x3B8],xmm0
    0xa01bf9f  movups [rcx+0x3D0],xmm0
    0xa01bf98  movups [rcx+0x3E0],xmm0
    0xa01bf91  movups [rcx+0x3F0],xmm0
    0xa01bfaa  mov qword ptr [rcx+0x400],0

## NEXT
DONE
