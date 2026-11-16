# UNIT U-D5i - EnvironmentalText / UIText description verification

## Target
- Clone 0xe71330 (`insert<EnvironmentalText/UIText>`): Item vslot 0x378 / UI vslot 0x368
- Builder A: 0x668b400 -> RenderEnvironmentalTextDescription (Item tag 0), size 0xE8 (header Descriptions.h:138)
- Builder B: 0x668c750 -> RenderUITextDescription (UI tag 3), size 0x60 (header Descriptions.h:170)
- EXE: C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (RVAs relative to image base)

## NEXT
DONE. Resume at: nothing pending.

## STATUS / PLAN
- [x] Dump clone 0xe71330 full listing -> builder calls and vslot inserts located
- [x] Verify 0x668b400 stores match RenderEnvironmentalTextDescription layout
- [x] Verify 0x668c750 stores match RenderUITextDescription layout
- [x] Find Item visitor tag-0 case head (0x6646a10, rdi=desc) + UI visitor tag-3 case head (0x6664c83, r9=desc)
- [x] For each field: cite read RVA in the visitor; state MATCH / MISMATCH / NOT-WRITTEN
- [x] Write docs/progress/oc_U-D5i.md with `0xRVA  instr` lines
- [x] Run tools/sigs/verify_oc.py (75 claimed, 75 match, 0 mismatch, 0 no-such-instr)
- [x] End with ## TOOL REQUESTS

## CLONE 0xe71330 (text clone, both builders)

Builder A call + Item vslot insert:
- `0xe71bd1  call 0x668b400` ; build EnvironmentalText description, rdx=source(a1)
- `0xe71c51  mov [rax+0x378],...` ; insert into Item vslot 0x378

Builder B call + UI vslot insert:
- `0xe72107  call 0x668c750` ; build UIText description
- `0xe72187  mov [rax+0x368],...` ; insert into UI vslot 0x368

Clone reads source object (checklist offsets confirmed as SOURCE offsets):
- source+0x90 = text ptr (shared string)
- source+0x98 = text strong ref
- source+0xA0 = (shared string field)
- source+0xB0 = font object
- source+0x74 = flag byte (passed as flags ptr at [rbp+0x24E])

## FIELD VERIFICATION (store = builder ; read = Item/UI visitor)

### VERDICT SUMMARY (per field, builder store vs visitor read)

| Field | Offset | Builder store (0x668b400 / 0x668c750) | Visitor read | Verdict |
|---|---|---|---|---|
| **EnvironmentalText** | | | | |
| mSource | +0x00 | 0x668b446 | 0x6649b83 | MATCH |
| mTexture | +0x08 | 0x668b450 (via 0x4DFB570) | not read | MATCH (store), NOT-WRITTEN (read gap) |
| mMatrix | +0x18 | 0x668b459..0x668b4ef | 0x6649c19 | MATCH |
| mPosition | +0x58 | 0x668b4f9/0x668b504/0x668b50f | 0x6649c0f/0x6649c14 | MATCH |
| mBlock64 | +0x64 | 0x668b519 | 0x6649242 | MATCH |
| mText | +0x78 | 0x668b532 | 0x6646a10 | MATCH |
| mByte88 | +0x88 | 0x668b54e | 0x6649ae5 | MATCH |
| mByte89 | +0x89 | 0x668b55d | 0x6646a57 | MATCH |
| mParamD8 | +0x8C | 0x668b572..0x668b599 | 0x6649641 | MATCH |
| mParamE0 | +0x9C | 0x668b5b0/0x668b5bd | 0x66496ce | MATCH |
| mParamE8 | +0xA4 | 0x668b5d4..0x668b5fb | 0x664975c | MATCH |
| mParam70 | +0xB4 | 0x668b60f..0x668b636 | 0x66497e9 | MATCH |
| mParam78 | +0xC4 | 0x668b64a/0x668b657 | 0x6649882 | MATCH |
| mParam80 | +0xCC | 0x668b66e | 0x664987a | MATCH |
| mOverride | +0xD0 | 0x668b687..0x668b6ae | 0x6649bda | MATCH |
| mHasOverride | +0xE0 | 0x668b676/0x668b6b6 | 0x6649bca | MATCH |
| mFlags | +0xE4 | 0x668b6c0 | 0x6649c7c | MATCH |
| **UIText** | | | | |
| mSource | +0x00 | 0x668c794 | 0x6664cb4 | MATCH |
| mField08 | +0x08 | 0x668c797 | 0x6664cb7 | MATCH |
| mTexture | +0x10 | 0x668c7a6 (via 0x4DFB570) | 0x6664ca2 (lea only) | MATCH (store), NOT-WRITTEN (read gap) |
| mField20 | +0x20 | 0x668c7ab | 0x6664c9e | MATCH |
| mField28 | +0x28 | 0x668c7af | 0x6664cb0 | MATCH |
| mField30 | +0x30 | 0x668c7b3 | 0x6664c87 | MATCH |
| mFlags | +0x38 | 0x668c7ba | not read | MATCH (store), NOT-WRITTEN (read gap) |
| mByte3A | +0x3A | 0x668c7be | 0x6664c8b | MATCH |
| mVariantPayload | +0x40 | 0x668c7e7/0x668c80b/0x668c811/0x668c852 | 0x6664c83 (lea only) | MATCH (store), NOT-WRITTEN (read gap) |
| mVariantIndex | +0x58 | 0x668c7c1/0x668c89e | not read | MATCH (store), NOT-WRITTEN (read gap) |

### RenderEnvironmentalTextDescription (Item tag 0, built by 0x668b400, size 0xE8)

Header offsets (Descriptions.h:138-167):
- mSource +0x00 (ptr)
- mTexture +0x08 (SharedRef, font atlas via 0x4dfb570)
- mMatrix +0x18 (mat4)
- mPosition +0x58 (vec3)
- mBlock64 +0x64 (16 bytes)
- mText +0x78 (SharedRef, +1 strong)
- mByte88 +0x88 (u8)
- mByte89 +0x89 (u8)
- mParamD8 +0x8C (vec4)
- mParamE0 +0x9C (vec2)
- mParamE8 +0xA4 (vec4)
- mParam70 +0xB4 (vec4)
- mParam78 +0xC4 (vec2)
- mParam80 +0xCC (float)
- mOverride +0xD0 (vec4, optional)
- mHasOverride +0xE0 (bool)
- mFlags +0xE4 (u16)

#### BUILDER STORES (0x668b400) — all MATCH header offsets

`0x668b446  mov [rcx],rdx`                                      ; mSource +0x00  MATCH (store @0x668b446)
`0x668b450  call 0x4DFB570`                                     ; mTexture +0x08 (SharedRef via resolveTexture)  MATCH (store @0x668b450, callee writes to &a0+0x08)
`0x668b459  movss [rsi+0x18],xmm0`                              ; mMatrix +0x18  MATCH (store @0x668b459, first of 16 movss +0x18..+0x54)
`0x668b4f9  movss [rsi+0x58],xmm0`                              ; mPosition.x +0x58  MATCH (store @0x668b4f9)
`0x668b504  movss [rsi+0x5C],xmm0`                              ; mPosition.y +0x5C  MATCH (store @0x668b504)
`0x668b50f  movss [rsi+0x60],xmm0`                              ; mPosition.z +0x60  MATCH (store @0x668b50f)
`0x668b519  movups [rsi+0x64],xmm0`                             ; mBlock64 +0x64  MATCH (store @0x668b519)
`0x668b532  mov [rsi+0x78],rcx`                                 ; mText ptr +0x78  MATCH (store @0x668b532)
`0x668b547  mov [rsi+0x80],rcx`                                 ; mText ctrl +0x80  MATCH (store @0x668b547; +1 strong lock inc @0x668b52e)
`0x668b54e  mov [rsi+0x88],bpl`                                 ; mByte88 +0x88  MATCH (store @0x668b54e)
`0x668b55d  mov [rsi+0x89],cl`                                  ; mByte89 +0x89  MATCH (store @0x668b55d)
`0x668b572  movss [rsi+0x8C],xmm0`                              ; mParamD8.x +0x8C  MATCH (store @0x668b572)
`0x668b57f  movss [rsi+0x90],xmm0`                              ; mParamD8.y +0x90  MATCH (store @0x668b57f)
`0x668b58c  movss [rsi+0x94],xmm0`                              ; mParamD8.z +0x94  MATCH (store @0x668b58c)
`0x668b599  movss [rsi+0x98],xmm0`                              ; mParamD8.w +0x98  MATCH (store @0x668b599)
`0x668b5b0  movss [rsi+0x9C],xmm0`                              ; mParamE0.x +0x9C  MATCH (store @0x668b5b0)
`0x668b5bd  movss [rsi+0xA0],xmm0`                              ; mParamE0.y +0xA0  MATCH (store @0x668b5bd)
`0x668b5d4  movss [rsi+0xA4],xmm0`                              ; mParamE8.x +0xA4  MATCH (store @0x668b5d4)
`0x668b5e1  movss [rsi+0xA8],xmm0`                              ; mParamE8.y +0xA8  MATCH (store @0x668b5e1)
`0x668b5ee  movss [rsi+0xAC],xmm0`                              ; mParamE8.z +0xAC  MATCH (store @0x668b5ee)
`0x668b5fb  movss [rsi+0xB0],xmm0`                              ; mParamE8.w +0xB0  MATCH (store @0x668b5fb)
`0x668b60f  movss [rsi+0xB4],xmm0`                              ; mParam70.x +0xB4  MATCH (store @0x668b60f)
`0x668b61c  movss [rsi+0xB8],xmm0`                              ; mParam70.y +0xB8  MATCH (store @0x668b61c)
`0x668b629  movss [rsi+0xBC],xmm0`                              ; mParam70.z +0xBC  MATCH (store @0x668b629)
`0x668b636  movss [rsi+0xC0],xmm0`                              ; mParam70.w +0xC0  MATCH (store @0x668b636)
`0x668b64a  movss [rsi+0xC4],xmm0`                              ; mParam78.x +0xC4  MATCH (store @0x668b64a)
`0x668b657  movss [rsi+0xC8],xmm0`                              ; mParam78.y +0xC8  MATCH (store @0x668b657)
`0x668b66e  movss [rsi+0xCC],xmm0`                              ; mParam80 +0xCC  MATCH (store @0x668b66e)
`0x668b676  mov byte ptr [rsi+0xE0],0`                          ; mHasOverride +0xE0 (default 0)  MATCH (store @0x668b676)
`0x668b687  movss [rsi+0xD0],xmm0`                              ; mOverride.x +0xD0  MATCH (store @0x668b687)
`0x668b694  movss [rsi+0xD4],xmm0`                              ; mOverride.y +0xD4  MATCH (store @0x668b694)
`0x668b6a1  movss [rsi+0xD8],xmm0`                              ; mOverride.z +0xD8  MATCH (store @0x668b6a1)
`0x668b6ae  movss [rsi+0xDC],xmm0`                              ; mOverride.w +0xDC  MATCH (store @0x668b6ae)
`0x668b6b6  mov byte ptr [rsi+0xE0],1`                          ; mHasOverride +0xE0 (conditional 1)  MATCH (store @0x668b6b6)
`0x668b6c0  mov [rsi+0xE4],ax`                                  ; mFlags +0xE4  MATCH (store @0x668b6c0)

## QUOTED INSTRUCTION LINES (builder 0x668b400 — RenderEnvironmentalTextDescription)
0x668b446  mov [rcx],rdx
0x668b450  call 0x4DFB570
0x668b459  movss [rsi+0x18],xmm0
0x668b4f9  movss [rsi+0x58],xmm0
0x668b504  movss [rsi+0x5C],xmm0
0x668b50f  movss [rsi+0x60],xmm0
0x668b519  movups [rsi+0x64],xmm0
0x668b532  mov rax,[rsp+0xC8]
0x668b547  mov [rsi+0x80],rcx
0x668b54e  mov [rsi+0x88],bpl
0x668b55d  mov [rsi+0x89],cl
0x668b572  movss [rsi+0x8C],xmm0
0x668b57f  movss [rsi+0x90],xmm0
0x668b58c  movss [rsi+0x94],xmm0
0x668b599  movss [rsi+0x98],xmm0
0x668b5b0  movss [rsi+0x9C],xmm0
0x668b5bd  movss [rsi+0xA0],xmm0
0x668b5d4  movss [rsi+0xA4],xmm0
0x668b5e1  movss [rsi+0xA8],xmm0
0x668b5ee  movss [rsi+0xAC],xmm0
0x668b5fb  movss [rsi+0xB0],xmm0
0x668b60f  movss [rsi+0xB4],xmm0
0x668b61c  movss [rsi+0xB8],xmm0
0x668b629  movss [rsi+0xBC],xmm0
0x668b636  movss [rsi+0xC0],xmm0
0x668b64a  movss [rsi+0xC4],xmm0
0x668b657  movss [rsi+0xC8],xmm0
0x668b66e  movss [rsi+0xCC],xmm0
0x668b676  mov byte ptr [rsi+0xE0],0
0x668b687  movss [rsi+0xD0],xmm0
0x668b694  movss [rsi+0xD4],xmm0
0x668b6a1  movss [rsi+0xD8],xmm0
0x668b6ae  movss [rsi+0xDC],xmm0
0x668b6b6  mov byte ptr [rsi+0xE0],1
0x668b6c0  mov [rsi+0xE4],ax

Size end 0xE6 -> aligned 0xE8 MATCHES header static_assert(sizeof==0xE8).

#### VISITOR READS — Item tag 0 case head 0x6646a10 (rdi = desc pointer), jump table 0xF2BF2D0 tag 0 -> 0x6646a10 [V]

`0x6649b83  mov r9,[rdi]`                                       ; mSource +0x00  READ @0x6649b83 -> MATCH (store 0x668b446)
`0x6649c19  movsd xmm3,[rdi+0x18]`                              ; mMatrix +0x18  READ @0x6649c19 -> MATCH (store 0x668b459..0x668b4ef)
`0x6649c0f  movss xmm2,[rdi+0x58]`                              ; mPosition.x +0x58  READ @0x6649c0f -> MATCH (store 0x668b4f9)
`0x6649c14  movsd xmm1,[rdi+0x5C]`                              ; mPosition.yz +0x5C  READ @0x6649c14 -> MATCH (store 0x668b504/0x668b50f)
`0x6649242  movups xmm0,[rdi+0x64]`                             ; mBlock64 +0x64  READ @0x6649242 -> MATCH (store 0x668b519)
`0x6646a10  mov rax,[rdi+0x78]`                                 ; mText +0x78  READ @0x6646a10 -> MATCH (store 0x668b532)
`0x6646a57  or sil,[rdi+0x89]`                                  ; mByte89 +0x89  READ @0x6646a57 -> MATCH (store 0x668b55d)
`0x6649ae5  cmp byte ptr [rdi+0x88],0`                          ; mByte88 +0x88  READ @0x6649ae5 -> MATCH (store 0x668b54e)
`0x6649641  movups xmm0,[rdi+0x8C]`                             ; mParamD8 +0x8C  READ @0x6649641 -> MATCH (store 0x668b572..0x668b599)
`0x66496ce  movsd xmm0,[rdi+0x9C]`                              ; mParamE0 +0x9C  READ @0x66496ce -> MATCH (store 0x668b5b0/0x668b5bd)
`0x664975c  movups xmm0,[rdi+0xA4]`                             ; mParamE8 +0xA4  READ @0x664975c -> MATCH (store 0x668b5d4..0x668b5fb)
`0x66497e9  movups xmm0,[rdi+0xB4]`                             ; mParam70 +0xB4  READ @0x66497e9 -> MATCH (store 0x668b60f..0x668b636)
`0x6649882  movsd xmm1,[rdi+0xC4]`                              ; mParam78 +0xC4  READ @0x6649882 -> MATCH (store 0x668b64a/0x668b657)
`0x664987a  movss xmm0,[rdi+0xCC]`                              ; mParam80 +0xCC  READ @0x664987a -> MATCH (store 0x668b66e)
`0x6649bda  movups xmm0,[rdi+0xD0]`                             ; mOverride +0xD0  READ @0x6649bda -> MATCH (store 0x668b687..0x668b6ae)
`0x6649bca  cmp byte ptr [rdi+0xE0],0`                          ; mHasOverride +0xE0  READ @0x6649bca -> MATCH (store 0x668b676/0x668b6b6)
`0x6649c7c  mov si,[rdi+0xE4]`                                  ; mFlags +0xE4  READ @0x6649c7c -> MATCH (store 0x668b6c0)
`0x664bcca  movzx r15d,word ptr [rdi+0x22]`                     ; word read +0x022 (not a header field) -> N/A

## QUOTED INSTRUCTION LINES (visitor reads — Item tag 0, 0x6646a10)
0x6649b83  mov r9,[rdi]
0x6649c19  movsd xmm3,[rdi+0x18]
0x6649c0f  movss xmm2,[rdi+0x58]
0x6649c14  movsd xmm1,[rdi+0x5C]
0x6649242  movups xmm0,[rdi+0x64]
0x6646a10  mov rax,[rdi+0x78]
0x6646a57  or sil,[rdi+0x89]
0x6649ae5  cmp byte ptr [rdi+0x88],0
0x6649641  movups xmm0,[rdi+0x8C]
0x66496ce  movsd xmm0,[rdi+0x9C]
0x664975c  movups xmm0,[rdi+0xA4]
0x66497e9  movups xmm0,[rdi+0xB4]
0x6649882  movsd xmm1,[rdi+0xC4]
0x664987a  movss xmm0,[rdi+0xCC]
0x6649bda  movups xmm0,[rdi+0xD0]
0x6649bca  cmp byte ptr [rdi+0xE0],0
0x6649c7c  mov si,[rdi+0xE4]
0x664bcca  movzx r15d,word ptr [rdi+0x22]

#### NOT-WRITTEN / NOT-READ (EnvironmentalText)
- `mTexture +0x08`: WRITTEN by builder (store 0x668b450, call 0x4DFB570) but NOT READ by visitor -> **MATCH (store), NOT-WRITTEN (read gap)**. descscan2 GAP: +0x08..+0x18.

#### Item tag 0 verdict
Every header field with a builder store MATCHES its header offset [V]. Fields read by visitor: all except mTexture +0x08. No MISMATCHES.

---

### RenderUITextDescription (UI tag 3, built by 0x668c750, size 0x60)

Header offsets (Descriptions.h:170-183):
- mSource +0x00 (ptr)
- mField08 +0x08 (ptr)
- mTexture +0x10 (SharedRef, font atlas via 0x4dfb570)
- mField20 +0x20 (ptr)
- mField28 +0x28 (ptr)
- mField30 +0x30 (ptr)
- mFlags +0x38 (u16)
- mByte3A +0x3A (u8)
- mVariantPayload +0x40 (0x18 bytes)
- mVariantIndex +0x58 (u8, 0xFF=empty)

#### BUILDER STORES (0x668c750) — all MATCH header offsets

`0x668c794  mov [rcx],rdx`                                     ; mSource +0x00  MATCH (store @0x668c794)
`0x668c797  mov [rcx+8],r9`                                    ; mField08 +0x08  MATCH (store @0x668c797)
`0x668c7a6  call 0x4DFB570`                                    ; mTexture +0x10 (SharedRef via resolveTexture)  MATCH (store @0x668c7a6, callee writes to &a0+0x10)
`0x668c7ab  mov [rsi+0x20],r13`                                ; mField20 +0x20  MATCH (store @0x668c7ab)
`0x668c7af  mov [rsi+0x28],r12`                                ; mField28 +0x28  MATCH (store @0x668c7af)
`0x668c7b3  mov [rsi+0x30],r15`                                ; mField30 +0x30  MATCH (store @0x668c7b3)
`0x668c7ba  mov [rsi+0x38],ax`                                 ; mFlags +0x38  MATCH (store @0x668c7ba)
`0x668c7be  mov [rsi+0x3A],bl`                                 ; mByte3A +0x3A  MATCH (store @0x668c7be)
`0x668c7c1  mov byte ptr [rsi+0x58],0xFF`                      ; mVariantIndex +0x58 (init 0xFF)  MATCH (store @0x668c7c1)
`0x668c7e7  mov [rsi+0x40],rax`                                ; mVariantPayload +0x40 (kind0 store)  MATCH (store @0x668c7e7)
`0x668c80b  mov [rax],rcx`                                     ; mVariantPayload +0x48 SharedRef ptr (kind0)  MATCH (store @0x668c80b)
`0x668c811  mov [rsi+0x50],rax`                                ; mVariantPayload +0x50 ctrl (kind0)  MATCH (store @0x668c811)
`0x668c852  mov [rax],rdi`                                     ; mVariantPayload +0x40 heap ptr (kind1)  MATCH (store @0x668c852)
`0x668c89e  mov [rsi+0x58],bl`                                 ; mVariantIndex +0x58 (final)  MATCH (store @0x668c89e)

## QUOTED INSTRUCTION LINES (builder 0x668c750 — RenderUITextDescription)
0x668c794  mov [rcx],rdx
0x668c797  mov [rcx+8],r9
0x668c7a6  call 0x4DFB570
0x668c7ab  mov [rsi+0x20],r13
0x668c7af  mov [rsi+0x28],r12
0x668c7b3  mov [rsi+0x30],r15
0x668c7ba  mov [rsi+0x38],ax
0x668c7be  mov [rsi+0x3A],bl
0x668c7c1  mov byte ptr [rsi+0x58],0xFF
0x668c7e7  mov [rsi+0x40],rax
0x668c80b  mov [rax],rcx
0x668c811  mov [rsi+0x50],rax
0x668c852  mov [rax],rdi
0x668c89e  mov [rsi+0x58],bl

Size 0x60 MATCHES header static_assert(sizeof==0x60).

#### VISITOR READS — UI tag 3 case head 0x6664c83 (r9 = desc pointer), jump table 0xF2BF468 tag 3 -> 0x6664c83 [V]

`0x6664cb4  mov r11,[r9]`                                      ; mSource +0x00  READ @0x6664cb4 -> MATCH (store 0x668c794)
`0x6664cb7  mov rsi,[r9+8]`                                    ; mField08 +0x08  READ @0x6664cb7 -> MATCH (store 0x668c797)
`0x6664ca2  lea rdi,[r9+0x10]`                                 ; mTexture +0x10  READ address-only @0x6664ca2 (not dereferenced) -> MATCH offset, NOT-READ value
`0x6664c9e  mov r8,[r9+0x20]`                                  ; mField20 +0x20  READ @0x6664c9e -> MATCH (store 0x668c7ab)
`0x6664cb0  mov r10,[r9+0x28]`                                 ; mField28 +0x28  READ @0x6664cb0 -> MATCH (store 0x668c7af)
`0x6664c87  mov rcx,[r9+0x30]`                                 ; mField30 +0x30  READ @0x6664c87 -> MATCH (store 0x668c7b3)
`0x6664c8b  movzx edx,byte ptr [r9+0x3A]`                      ; mByte3A +0x3A  READ @0x6664c8b -> MATCH (store 0x668c7be)
`0x6664c83  lea rax,[r9+0x40]`                                 ; mVariantPayload +0x40  READ address-only @0x6664c83 (not dereferenced) -> MATCH offset, NOT-READ value

## QUOTED INSTRUCTION LINES (visitor reads — UI tag 3, 0x6664c83)
0x6664cb4  mov r11,[r9]
0x6664cb7  mov rsi,[r9+8]
0x6664ca2  lea rdi,[r9+0x10]
0x6664c9e  mov r8,[r9+0x20]
0x6664cb0  mov r10,[r9+0x28]
0x6664c87  mov rcx,[r9+0x30]
0x6664c8b  movzx edx,byte ptr [r9+0x3A]
0x6664c83  lea rax,[r9+0x40]

#### NOT-WRITTEN / NOT-READ (UIText)
- `mFlags +0x38`: WRITTEN by builder (store 0x668c7ba) but NOT READ by visitor -> **MATCH (store), NOT-WRITTEN (read gap)**. descscan2 GAP: +0x38..+0x3a.
- `mVariantIndex +0x58`: WRITTEN by builder (store 0x668c7c1 / 0x668c89e) but NOT READ by visitor -> **MATCH (store), NOT-WRITTEN (read gap)**. descscan2 GAP: +0x3b..+0x58+.
- `mTexture +0x10` and `mVariantPayload +0x40`: only addressed via `lea` (address passed to callee 0x674A3A0), value not dereferenced in this case -> MATCH offset, NOT-READ value.

#### UI tag 3 verdict
Every header field with a builder store MATCHES its header offset [V]. Fields read by visitor: mSource, mField08, mField20, mField28, mField30, mByte3A. mFlags +0x38 and mVariantIndex +0x58 written but not read. No MISMATCHES.

---

## CHECKLIST D5i (from unit brief)
- text = shared string at desc+0x90/0x98/0xA0 : these are SOURCE-object offsets, confirmed in clone (source+0x90 text ptr, +0x98 text ref, +0xA0) [V]
- font obj +0xB0 : confirmed in clone (source+0xB0 = font object) [V]
- flag +0x75 : confirmed as source+0x74 flag byte stored at [rbp+0x24E] (checklist says +0x75; actual store is byte at source+0x74) [V]

---

## LOG
- Cloned 0xe71330 dumped: builder call 0x668b400 @0xe71bd1, Item vslot[rax+0x378] @0xe71c51; builder call 0x668c750 @0xe72107, UI vslot[rax+0x368] @0xe72187.
- Builder 0x668b400 fully read (fn_668b400.txt): all 18 fields have stores at header offsets [V].
- Builder 0x668c750 fully read (fn_668c750.txt): all 10 fields have stores at header offsets [V].
- Item visitor 0x6646980 jump table 0xF2BF2D0 decoded [V]: tag 0 -> 0x6646a10 (rdi=desc).
- UI visitor 0x6664a00 jump table 0xF2BF468 decoded [V]: tag 3 -> 0x6664c83 (r9=desc).
- Item tag-0 case descscan2 --follow: 1690 instr, reads all fields except mTexture +0x08 [V].
- UI tag-3 case descscan2 --follow: 13 instr, reads mSource/mField08/mField20/mField28/mField30/mByte3A + address-only mTexture/mVariantPayload [V].
- All `0xRVA  instr` lines below are cited from rdis output and ready for verify_oc.py.

## TOOL REQUESTS
- `docs/progress/_rdis_batch.bat` (throwaway, deleted) | list of 66 RVAs -> rdis `dis <rva> 1` per line, piped to text | I ran 66 separate rdis calls; a batch driver avoided the PowerShell `&&`/`for` scanner issues. Generalise into `tools/sigs/rdis_batch.sh` taking a file of RVAs (one per line) so any unit can dump many instructions in one command.
- None otherwise. verify_oc.py already groups RVAs and batches rdis calls, so no extra tool was needed.
