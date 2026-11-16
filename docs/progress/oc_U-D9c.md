# Unit U-D9c: field layouts of GameplayMetadata, ServerGraphicsOverrideParameters, EditorHighlightConfiguration

Checklist D9c. Exe 1.26.62.01, RVAs image-relative, static analysis only. Tags: [V] instruction seen in a listing, [I] inference, [?] unknown.
Listings (docs/data/listings/): lightgame_gameplaymeta_clone_53e5910_53e6114.txt, lightgame_serveroverride_ctor_a1c40_a1dc1.txt,
lightgame_serveroverride_producer_6c2e820_6c2f87e.txt, lightgame_serveroverride_copy_67b6300.txt, lightgame_serveroverride_setcopy_67b7810.txt,
lightgame_edhighlight_clone_4c8a5b0_4c8a6e9.txt, lightgame_edhighlight_producer_4c88900_4c89881.txt, lightgame_clone_5370960_5370a99.txt,
lightgame_clone_53e2c00_53e3743.txt. Existing knowledge: docs/functions/6640d80_light_visitor.md, src/sdk/mc/deps/minecraft_renderer/framebuilder/LightDescriptions.h, EffectDescriptions.h.

## GameplayMetadata (Light group, tag 2, clone 0x53e5910 fat 0x804 bytes)

**Clone:** 0x53e5910..0x53e6114 (465 lines). Builds description on stack at [rbp+0x40] (zeroed 0x40..0xB4), passes variant at [rbp-0x50] to insert.
**Visitor:** Light group case 2 at 0x6640f1b..0x66410a0 (reg rsi).

Visitor reads (descscan2.py --visitor light --case 2) [V]:
```
+0x000 xmmword  movups @6640f8c
+0x010 xmmword  movups @6640f8f
+0x020 xmmword  movups @6640f93
+0x02a xmmword  movups @6640f97
+0x03c dword    movss  @6640fb2
+0x040 dword    movss  @6640fbe
+0x044 dword    movss  @6640fca
+0x048 dword    movss  @6640fd6
+0x04c dword    movss  @6640fe2
+0x050 dword    movss  @6640fee
+0x054 dword    movss  @6640ffa
+0x058 dword    movss  @6641006
+0x05c dword    movss  @6641012
+0x060 dword    movss  @664101e
+0x064 dword    movss  @664102a
+0x068 dword    movss  @6641036
+0x06c dword    movss  @6641042
+0x070 dword    movss  @664104e
+0x074 dword    movss  @664105a
+0x078 dword    movss  @6641066
+0x07c dword    movss  @6641072
+0x080 dword    movss  @664107e
```
Read bytes: 0x0-0x3a, 0x3c-0x84. Gaps: 0x3a-0x3c.

Producer stores to stack buffer at [rbp+0x40] (listing lightgame_gameplaymeta_clone_53e5910_53e6114.txt) [V]:
```
0x53e5b31  mov [rbp+0x60],eax              ; +0x20 dword
0x53e5b38  movss [rbp+0x7C],xmm0           ; +0x3C float
0x53e5b42  movss [rbp+0x80],xmm0           ; +0x40 float
0x53e5b4f  movss [rbp+0x84],xmm0           ; +0x44 float
0x53e5b5b  mov [rbp+0x78],al               ; +0x38 byte
0x53e5bab  mov [rbp+0x76],al               ; +0x36 byte
0x53e5be0  mov [rbp+0x74],ax               ; +0x34 word
0x53e5c1e  mov [rbp+0x64],eax              ; +0x24 dword
0x53e5c44  mov [rbp+0x68],eax              ; +0x28 dword
0x53e5c4c  mov [rbp+0x79],al               ; +0x39 byte
0x53e5c97  movss [rbp+0x48],xmm0           ; +0x08 float
0x53e5d2f  movss [rbp+0x54],xmm0           ; +0x14 float
0x53e5d40  movss [rbp+0x58],xmm0           ; +0x18 float
0x53e5d93  movss [rbp+0x88],xmm0           ; +0x48 float
0x53e5da2  movups [rbp+0x8C],xmm4          ; +0x4C xmmword (16 bytes)
0x53e5da9  movss [rbp+0x9C],xmm2           ; +0x5C float
0x53e5dc6  movsd [rbp+0xA0],xmm1           ; +0x60 double (8 bytes)
0x53e5dce  movss [rbp+0xA8],xmm0           ; +0x68 float
```

Field table (offset from description start, size, meaning, tag) [V for visitor reads, I for producer correlation]:
| Offset | Size | Type | Meaning (visitor) | Producer store [V] | Tag |
|--------|------|------|-------------------|---------------------|-----|
| +0x000 | 16   | float[4] / mat4 row0 | Unknown (xmmword read) | [UNVERIFIED: 0x53e5910 no store to +0x000] | ? |
| +0x010 | 16   | float[4] / mat4 row1 | Unknown (xmmword read) | [UNVERIFIED: 0x53e5910 no store to +0x010] | ? |
| +0x020 | 16   | float[4] / mat4 row2 | Unknown (xmmword read) | 0x53e5b31 dword at +0x20 (partial) | ? |
| +0x02A | 16   | float[4] | Unknown (xmmword read at unaligned offset) | [UNVERIFIED: 0x53e5910 no store to +0x02A] | ? |
| +0x034 | 2    | uint16 | Unknown | 0x53e5be0 word at +0x34 | ? |
| +0x036 | 1    | uint8 | Unknown | 0x53e5bab byte at +0x36 | ? |
| +0x038 | 1    | uint8 | Unknown | 0x53e5b5b byte at +0x38 | ? |
| +0x03C | 4    | float | Unknown (dword read) | 0x53e5b38 float at +0x3C | ? |
| +0x040 | 4    | float | Unknown (dword read) | 0x53e5b42 float at +0x40 | ? |
| +0x044 | 4    | float | Unknown (dword read) | 0x53e5b4f float at +0x44 | ? |
| +0x048 | 4    | float | Unknown (dword read) | 0x53e5c97 float at +0x08 [I: desc+0x48 = buf+0x08] | ? |
| +0x04C | 16   | float[4] | Unknown (xmmword read at +0x4C via +0x8C store) | 0x53e5da2 xmmword at +0x4C | ? |
| +0x05C | 4    | float | Unknown (dword read at +0x5C) | 0x53e5da9 float at +0x5C | ? |
| +0x060 | 8    | double | Unknown (dword read at +0x60, but producer stores double) | 0x53e5dc6 double at +0x60 | ? |
| +0x064 | 4    | float/dword | Unknown (dword read) | 0x53e5c1e dword at +0x24 [I: desc+0x64 = buf+0x24] | ? |
| +0x068 | 4    | float/dword | Unknown (dword read) | 0x53e5c44 dword at +0x28 [I: desc+0x68 = buf+0x28] | ? |
| +0x06C | 4    | float | Unknown (dword read) | [UNVERIFIED] | ? |
| +0x070 | 4    | float | Unknown (dword read) | [UNVERIFIED] | ? |
| +0x074 | 4    | float | Unknown (dword read) | [UNVERIFIED] | ? |
| +0x078 | 4    | float | Unknown (dword read) | [UNVERIFIED] | ? |
| +0x07C | 4    | float | Unknown (dword read) | [UNVERIFIED] | ? |
| +0x080 | 4    | float | Unknown (dword read) | [UNVERIFIED] | ? |

**Size:** 0x84 (132) bytes minimum (last visitor read at +0x080 + 4). Tag byte: 2 (Light group). Clone kind: fat.

---

## ServerGraphicsOverrideParameters (Light group, tag 5, clone 0x6c2e820 fat 0x105e bytes)

**Clone:** 0x6c2e820..0x6c2f87e. Builds description in rdi (FrameBuilder 'this' +0x80 onwards), uses helper sub_6c29ea0 / sub_6c2a130 / sub_6c2a290 for repeated blocks.
**Visitor:** Light group case 5 at 0x66417af..0x664187d (reg rsi).

Visitor reads (descscan2.py --visitor light --case 5) [V]:
```
+0x260 qword  mov @6641846 (x2)
+0x268 qword  cmp @664184d
```
Read bytes: 0x260-0x270. Gaps: 0x0-0x260.

Producer stores (listing lightgame_serveroverride_producer_6c2e820_6c2f87e.txt) [V]:
The description is built at rdi+0x80 (see `lea rcx,[rdi+0x80]` at 0x6c2ee9d). The helper sub_6c29ea0 copies 0x40-byte blocks from stack buffers (rbp-0x50, rbp-0x10, rbp+0x30, rbp+0x70, rbp+0xB0, rbp+0xF0, rbp+0x130, rbp+0x170, rbp+0x1B0, rbp+0x1F0, rbp+0x230, rbp+0x270, rbp+0x2B0, rbp+0x2F0, rbp+0x330, rbp+0x370, rbp+0x3B0) to rdi+0x80, rdi+0xC0, rdi+0x100, rdi+0x140, rdi+0x180, rdi+0x1C0, rdi+0x200, rdi+0x240, rdi+0x280, rdi+0x2C0, rdi+0x300, rdi+0x340, rdi+0x380, rdi+0x3C0, rdi+0x400, rdi+0x440, rdi+0x480, rdi+0x4C0.

Each block is 0x40 bytes (64 bytes). 18 blocks × 0x40 = 0x480 bytes from rdi+0x80 to rdi+0x500.

Additional stores:
```
0x6c2ea56  mov dword ptr [rbp+0x3F0],0          ; local
0x6c2ea60  xorps xmm0,xmm0
0x6c2ea63  movups [rbp+0x3F8],xmm0              ; local
0x6c2ea90  mov [rbx],rbx                        ; rbx = linked list head
0x6c2ea93  mov [rbx+8],rbx
0x6c2ea97  mov [rbp+0x3F8],rbx                  ; +0x3F8 = list head ptr
0x6c2eac9  mov dword ptr [rbp+0x3F0],0x3F800000 ; local float 1.0
0x6c2eb52  mov [r14],rbx                        ; first of 16 stores to r14+0..r14+0x78 (rbp+0x408..0x478)
0x6c2eb55  mov [r14+8],rbx
0x6c2eb59  mov [r14+0x10],rbx
0x6c2eb5d  mov [r14+0x18],rbx
0x6c2eb61  mov [r14+0x20],rbx
0x6c2eb65  mov [r14+0x28],rbx
0x6c2eb69  mov [r14+0x30],rbx
0x6c2eb6d  mov [r14+0x38],rbx
0x6c2eb71  mov [r14+0x40],rbx
0x6c2eb75  mov [r14+0x48],rbx
0x6c2eb79  mov [r14+0x50],rbx
0x6c2eb7d  mov [r14+0x58],rbx
0x6c2eb81  mov [r14+0x60],rbx
0x6c2eb85  mov [r14+0x68],rbx
0x6c2eb89  mov [r14+0x70],rbx
0x6c2eb8d  mov [r14+0x78],rbx
0x6c2f3be  mov rax,[rbp+0xB18]
0x6c2f3c5  movlps [rax+0x14],xmm8               ; +0x14 = vec2/float2
0x6c2f3ca  movss [rax+0x1C],xmm7                ; +0x1C = float
0x6c2f72c  movups [rax],xmm0                    ; rax = [rbp+0xB00], zero 16 bytes
```

The visitor only reads at +0x260 and +0x268 (two qwords). At rdi+0x80 + 0x260 = rdi+0x2E0. This falls in block 11 (rdi+0x280 + 0x40 = rdi+0x2C0, block 12 starts at rdi+0x2C0, so +0x260 is in block 11 at offset 0x260-0x240=0x20 within block).

Field table (offset from description start, size, meaning, tag) [V for visitor, I for producer]:
| Offset | Size | Type | Meaning (visitor) | Producer store [V] | Tag |
|--------|------|------|-------------------|---------------------|-----|
| +0x260 | 8    | uint64* / ptr | Unknown (qword read x2) | Block 11 (rdi+0x280) + 0x20 [I] | ? |
| +0x268 | 8    | uint64* / ptr | Unknown (qword cmp) | Block 11 (rdi+0x280) + 0x28 [I] | ? |

**Size:** At least 0x270 (624) bytes. Full description appears to be 0x500 bytes (rdi+0x80 to rdi+0x580) based on producer (18×0x40 blocks). Tag byte: 5 (Light group). Clone kind: fat.

[UNVERIFIED: 0x6c2e820 full field map of 18×0x40 blocks not decoded; visitor only reads 2 qwords at +0x260/+0x268]

---

## EditorHighlightConfiguration (Effect group, tag 8, clone 0x4c8a5b0 thin 0x139 bytes)

**Clone:** 0x4c8a5b0..0x4c8a6e9 (thin, 313 bytes). Passes description pointer (rdx) and tag 8 directly to insert via variant at [rbp-0x10]/[rbp+0x10].
**Visitor:** Effect group case 8 at 0x666b316..0x667191c (reg r15).

Visitor reads (descscan2.py --visitor effect --case 8) [V]:
```
+0x000 qword/xmmword  movups @666b3ba (x13)
+0x001 addr          lea    @666c2c3
+0x008 addr/dword/qword mov  @666b3be (x9)
+0x00c dword/xmmword  lock dec @666cdd8 (x2)
+0x010 addr/qword/xmmword movups @666b5a4 (x5)
+0x018 qword/xmmword  mov    @666b6d3 (x5)
+0x01c xmmword        movups @666d09c
+0x020 xmmword        movups @666b5a9 (x2)
+0x028 xmmword        movups @666f339 (x2)
+0x02c xmmword        movups @666d0a8
+0x030 xmmword        movups @666b5ae (x2)
+0x038 xmmword        movups @666f344 (x2)
+00x03c xmmword        movups @666d0b4
+0x040 qword/xmmword  movups @666b5b3 (x3)
+0x048 xmmword        movups @666f34f (x2)
+0x04c word           movzx  @666d0c7
+0x050 qword          mov    @666b5bc (x2)
+0x058 dword          movss  @667049a
+0x05c qword          movsd  @667049f
+0x064 xmmword        movups @666f2fe (x2)
+0x068 addr/qword     lea    @666d2d7 (x2)
+0x078 qword          mov    @666d4b1 (x4)
+0x080 word           mov    @666d610 (x2)
+0x084 dword          mov    @666c96f (x2)
+0x088 word           mov    @666f36e (x2)
+0x0c8 byte           cmp    @666d9c0
+0x0c9 byte           cmp    @6670513
```
Read bytes: 0x0-0x74, 0x78-0x82, 0x84-0x8a, 0xc8-0xca. Gaps: 0x74-0x78, 0x82-0x84, 0x8a-0xc8.

Producer stores (listing lightgame_edhighlight_producer_4c88900_4c89881.txt) [V]:
The producer builds the description at rbx (allocated object). Key stores:
```
0x4c8898e  mov byte ptr [rbx+0x38],1           ; +0x38 byte = 1
0x4c88a7b  movups [rbx+0x60],xmm0              ; +0x60 xmmword (zero)
0x4c88ac3  movups [rbx+0x70],xmm0              ; +0x70 xmmword (zero)
0x4c89163  mov [rbx+0x40],rax                  ; +0x40 ptr
0x4c893f6  mov [rcx+8],eax                     ; rcx = some sub-object +8 dword
0x4c89400  mov [rcx],rax                       ; rcx = sub-object +0 ptr
0x4c89412  mov [rcx+0x18],eax                  ; rcx +0x18 dword
0x4c8941c  mov [rcx+0x10],rax                  ; rcx +0x10 ptr
0x4c89430  movups [rcx+0x20],xmm0              ; rcx +0x20 xmmword
0x4c8948e  movups [rcx],xmm13                  ; rcx = another sub-object, xmmword
0x4c89492  mov byte ptr [rax+0x31],1           ; rax +0x31 byte
0x4c894e5  movlps [rax+0x20],xmm7              ; rax +0x20 vec2/float2
0x4c894e9  movss [rax+0x28],xmm6               ; rax +0x28 float
0x4c894fc  mov [rax+0x48],rcx                  ; rax +0x48 ptr
0x4c89507  movups [rax+0x38],xmm0              ; rax +0x38 xmmword
0x4c8960d  mov byte ptr [rax+0x38],1           ; rax +0x38 byte (overwrites?)
0x4c897d2  movups [rax],xmm0                   ; rax +0x0 xmmword
```

Field table (offset from description start, size, meaning, tag) [V for visitor, I for producer correlation]:
| Offset | Size | Type | Meaning (visitor) | Producer store [V] | Tag |
|--------|------|------|-------------------|---------------------|-----|
| +0x000 | 16   | float[4] / mat4 row | Unknown (xmmword read x13) | 0x4c897d2 xmmword at +0x0 [I: rax = desc] | ? |
| +0x008 | 4/8  | ptr/dword | Unknown (read x9) | 0x4c89400 ptr at subobj+0, 0x4c8941c ptr at subobj+0x10 [I] | ? |
| +0x00C | 4/16 | dword/xmmword | Unknown (lock dec x2) | [UNVERIFIED] | ? |
| +0x010 | 16   | float[4] | Unknown (xmmword read x5) | [UNVERIFIED] | ? |
| +0x018 | 8/16 | ptr/xmmword | Unknown (read x5) | [UNVERIFIED] | ? |
| +0x01C | 16   | float[4] | Unknown (xmmword read) | [UNVERIFIED] | ? |
| +0x020 | 16   | float[4] | Unknown (xmmword read x2) | 0x4c89430 xmmword at subobj+0x20, 0x4c894e5 movlps at rax+0x20 | ? |
| +0x028 | 16   | float[4] | Unknown (xmmword read x2) | 0x4c894e9 float at rax+0x28 | ? |
| +0x02C | 16   | float[4] | Unknown (xmmword read) | [UNVERIFIED] | ? |
| +0x030 | 16   | float[4] | Unknown (xmmword read x2) | [UNVERIFIED] | ? |
| +0x038 | 16   | float[4] | Unknown (xmmword read x2) | 0x4c8898e byte at +0x38, 0x4c89507 xmmword at rax+0x38, 0x4c8960d byte at rax+0x38 | ? |
| +0x03C | 16   | float[4] | Unknown (xmmword read) | [UNVERIFIED] | ? |
| +0x040 | 8/16 | ptr/xmmword | Unknown (read x3) | 0x4c89163 ptr at +0x40 | ? |
| +0x048 | 16   | float[4] | Unknown (xmmword read x2) | [UNVERIFIED] | ? |
| +0x04C | 2    | uint16 | Unknown (movzx) | [UNVERIFIED] | ? |
| +0x050 | 8    | ptr | Unknown (qword read x2) | [UNVERIFIED] | ? |
| +0x058 | 4    | float | Unknown (movss) | [UNVERIFIED] | ? |
| +0x05C | 8    | double/ptr | Unknown (movsd) | [UNVERIFIED] | ? |
| +0x060 | 16   | float[4] | Unknown (xmmword read x2) | 0x4c88a7b xmmword at +0x60 | ? |
| +0x068 | 8    | ptr | Unknown (lea/qword read x2) | [UNVERIFIED] | ? |
| +0x078 | 8    | ptr | Unknown (qword read x4) | [UNVERIFIED] | ? |
| +0x080 | 2    | uint16 | Unknown (mov) | [UNVERIFIED] | ? |
| +0x084 | 4    | dword | Unknown (mov) | [UNVERIFIED] | ? |
| +0x088 | 2    | uint16 | Unknown (mov) | [UNVERIFIED] | ? |
| +0x0C8 | 1    | uint8 | Unknown (cmp) | [UNVERIFIED] | ? |
| +0x0C9 | 1    | uint8 | Unknown (cmp) | [UNVERIFIED] | ? |

**Size:** At least 0xCA (202) bytes (last read at +0xC9). Tag byte: 8 (Effect group). Clone kind: thin.

[UNVERIFIED: 0x4c88900 producer uses multiple sub-objects (rcx, rax) with unclear ownership; mapping to visitor offsets is inferred]

---

## Summary

| Type | Group | Tag | Clone RVA | Clone Kind | Size (min) | Visitor Case |
|------|-------|-----|-----------|------------|------------|--------------|
| GameplayMetadata | Light | 2 | 0x53e5910 | fat | 0x84 | Light case 2 |
| ServerGraphicsOverrideParameters | Light | 5 | 0x6c2e820 | fat | 0x270+ | Light case 5 |
| EditorHighlightConfiguration | Effect | 8 | 0x4c8a5b0 | thin | 0xCA | Effect case 8 |

## TOOL REQUESTS

None

## NEXT

All three type tables written. Run verify_oc.py on this file.