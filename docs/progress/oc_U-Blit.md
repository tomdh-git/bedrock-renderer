# U-Blit — BlitFlipbookTexture producer / clone / element / builder / vecview

Static dossier of the five listed functions. All input data comes from docs/data/listings/effect_blit_{producer_5aca680_5acb3a8, element_5acb9c0_5acbe20, clone_5acbe20_5acbf5a, elementbuilder_6bf7260_6bf7460, vecview_5acbfe0_5acc030}.txt (verbatim `0xRVA  instr` lines). Tags: [V] = seen in listing, [I] = inferred from instruction context, [?] = unknown.

## NEXT
DONE

## FUNCTION 5ACBFE0 — vecview (element-vector view copy)
Signature guess [I]: `void* copy_view(vecview* dst /*rcx*/, element_vector* src /*rdx/rdi... here rdx*/)` — copies {count, data} out of a 64-byte-element vector into a caller's view struct; returns dst.

### 0x5acbfe0..0x5acc01c: Reads src vector header: data ptr [rdx] and end ptr [rdx+8]; count = (end-data)>>6 (64-byte elements, `sar r9,6` [V]); stores count into [rcx] and data ptr into [rcx+8]; guards against an invalid span (rdx == 0xFFFFFFFFFFFFFFC0, i.e. data = end+0x40) and against data != 0 while end == 0 — on violation calls 0x78ED0 (fail-fast/invalid-parameter helper [I]); returns rcx in rax.
0x5acbfe0  sub rsp,0x28
0x5acbfe4  mov r8,[rdx]
0x5acbfe7  mov rax,[rdx+8]
0x5acbfeb  mov rdx,rax
0x5acbfee  sub rdx,r8
0x5acbff1  mov r9,rdx
0x5acbff4  sar r9,6
0x5acbff8  mov [rcx],r9
0x5acbffb  cmp rdx,0xFFFFFFFFFFFFFFC0
0x5acbfff  je short 0x5ACC01D
0x5acc001  mov [rcx+8],r8
0x5acc005  test r8,r8
0x5acc008  setne dl
0x5acc00b  test rax,rax
0x5acc00e  sete al
0x5acc011  or al,dl
0x5acc013  je short 0x5ACC01D
0x5acc015  mov rax,rcx
0x5acc018  add rsp,0x28
0x5acc01c  ret

### 0x5acc01d..0x5acc02f: Fail path: call 0x78ED0 (does not return [I]), followed by int3 padding to the next function boundary.
0x5acc01d  call 0x78ED0
0x5acc022  int3
0x5acc023  int3
0x5acc024  int3
0x5acc025  int3
0x5acc026  int3
0x5acc027  int3
0x5acc028  int3
0x5acc029  int3
0x5acc02a  int3
0x5acc02b  int3
0x5acc02c  int3
0x5acc02d  int3
0x5acc02e  int3
0x5acc02f  int3

#### Combined [reg+off] field table (all five functions; one annotated row per distinct offset; all sites verbatim)

| offset | size | direction | verbatim line(s) | meaning |
|---|---|---|---|---|
| --- | --- | - | --- | --- |
| 0x0 | 8/4/8 | RW | `0x5acbfe4  mov r8,[rdx]`, `0x5acbff8  mov [rcx],r9`, `0x5acbefa  mov [rbp],rax`, `0x5acba6e  sub r12,[rcx]`, `0x5acbba7  mov rax,[rcx]`, `0x5acb9e3  mov [r15],rax`, `0x5acbb33  mov [rdx+r12],r8`, `0x5acbc4a  mov [rdx+r8],r9`, `0x5acbdca  mov [rdx+r8],r9`, `0x6bf7300  mov r9,[rbx]`, `0x6bf733e  mov rcx,[rax]`, `0x6bf7366  mov rax,[rax]`, `0x6bf73ad  mov [rsi],r12`, `0x6bf7381  mov rax,[r15]`, `0x6bf7397  mov rax,[r15]`, `0x6bf7421  mov rax,[rdi]`, `0x6bf7436  mov rax,[rdi]`, `0x5acaef4  mov dword ptr [rax],0x3F800000`, `0x5acaf4a  mov dword ptr [rax],0x3F800000`, `0x5acaf9c  mov dword ptr [rax],0x3F800000`, `0x5aca9ee  mov rcx,[rax]`, `0x5acaa05  mov r13,[rax]`, `0x5acacea  mov rax,[r15]`, `0x5acaced  mov rax,[rax]`, `0x5acad8f  mov rax,[rax]`, `0x5acadef  mov rdx,[rax]`, `0x5acae69  mov rax,[rcx]`, `0x5acb02f  mov rax,[rcx]`, `0x5acb0b6  mov rax,[rcx]`, `0x5acb145  mov rax,[rcx]`, `0x5acb20f  mov rdx,[rax]`, `0x5aca6eb  mov qword ptr [rbp],0` | src vector begin/data pointer | string buffer zero-init (rsi=rbp-8) [I] |
| 0x8 | 16/16/8/4/8 | RW | `0x5acbfe7  mov rax,[rdx+8]`, `0x5acc001  mov [rcx+8],r8`, `0x5acbefe  mov qword ptr [rbp+8],0x15`, `0x5acbe75  mov qword ptr [rbp+0x38],0`, `0x5acb9e9  movups [r15+8],xmm0`, `0x5acbb3a  movups [rdx+r12+8],xmm0`, `0x5acbc4e  movups [rdx+r8+8],xmm0`, `0x5acbdce  movups [rdx+r8+8],xmm0`, `0x5acba56  add qword ptr [rcx+8],0x40`, `0x5acb9d2  mov r15,[rcx+8]`, `0x5acb9fb  mov rax,[rbx+8]`, `0x5acbbaa  mov r8,[rcx+8]`, `0x5acbc6c  mov r8,[rcx+8]`, `0x5acbbd8  mov r11,[r10+8]`, `0x5acbd58  mov r11,[r10+8]`, `0x5acbc94  mov r11,[r10+8]`, `0x5acbb4e  mov r8,[rbx+8]`, `0x5acb9ff  mov [r15+8],rax`, `0x5acbb52  mov [rax+8],r8`, `0x5acbbdc  mov [r9+8],r11`, `0x5acbd5c  mov [r9+8],r11`, `0x5acb9f7  lock inc dword ptr [rax+8]`, `0x5acbb49  lock inc dword ptr [r8+8]`, `0x5acbc62  lock inc dword ptr [r9+8]`, `0x5acbd2c  lock inc dword ptr [r10+8]`, `0x5acbde2  lock inc dword ptr [r9+8]`, `0x6bf734a  mov rcx,[rax+8]`, `0x6bf7357  mov rcx,[rax+8]`, `0x6bf739a  mov rax,[rax+8]`, `0x6bf7439  mov rax,[rax+8]`, `0x6bf7353  lock inc dword ptr [rcx+8]`, `0x6bf737a  lock dec dword ptr [r15+8]`, `0x6bf741b  lock dec dword ptr [rdi+8]`, `0x5aca746  lock inc dword ptr [rcx+8]`, `0x5aca827  lock dec dword ptr [rdi+8]`, `0x5aca86a  lock dec dword ptr [rdi+8]`, `0x5acac5a  lock dec dword ptr [r15+8]`, `0x5acacaa  lock dec dword ptr [r15+8]`, `0x5acace3  lock dec dword ptr [r15+8]`, `0x5acad1c  lock dec dword ptr [r15+8]`, `0x5aca9bb  mov r15,[rax+8]`, `0x5acae6c  mov rax,[rax+8]`, `0x5acb032  mov rax,[rax+8]`, `0x5acb0b9  mov rcx,[rcx+8]`, `0x5acb148  mov rcx,[rcx+8]`, `0x5acaf8a  mov rdx,[rax+8]`, `0x5acb036  mov [rbp+8],rcx` | src vector end pointer | object ptr saved for the later 0x5ACBE20 call [I] |
| 0x4 | 4/16 | RW | `0x5acbe5a  cmp eax,[rcx+4]`, `0x5acaefe  movupd [rax+4],xmm0`, `0x5acaf50  movupd [rax+4],xmm0`, `0x5acafa2  movupd [rax+4],xmm0` | TLS state object counter vs global init counter [I] |
| -0x10 | 16/4/1 | RW | `0x5acbf0d  movaps [rbp-0x10],xmm0`, `0x6bf7275  movaps [rbp-0x10],xmm6`, `0x6bf7449  movaps xmm6,[rbp-0x10]`, `0x5acbcd8  movss [rax+r9-0x10],xmm1`, `0x5aca6e3  mov byte ptr [rbp-0x10],0`, `0x5aca703  mov [rbp-0x10],al`, `0x5aca8ec  cmp byte ptr [rbp-0x10],1` | exception record: 16 bytes from 0xF0BCBF8 [I] | element float field @0x2C [I] | bool from 0x39A7D40 (gates the 0x77A2500 log call) |
| -0x18 | 4/1/8/8 | RW | `0x5acbe7d  mov byte ptr [rbp-0x18],0`, `0x6bf7279  mov qword ptr [rbp-0x18],0xFFFFFFFFFFFFFFFE`, `0x5acbcbe  movss [rax+r9-0x18],xmm1`, `0x5aca6df  mov [rbp-0x18],rcx`, `0x5aca8f2  mov r8,[rbp-0x18]` | SEH/GS cookie = -2 [I] | element float field @0x24 [I] | descriptor ptr (0x129CFAF0, +0x60 used as name) |
| 0x10 | 8/2/8/16 | RW | `0x5acbe90  mov [rbp+0x10],rdi`, `0x6bf7346  movzx ecx,word ptr [rcx+0x10]`, `0x5acb9d6  cmp r15,[rcx+0x10]`, `0x5acb9ee  mov rax,[rbx+0x10]`, `0x5acba03  mov rax,[rbx+0x10]`, `0x5acbb40  mov r8,[rbx+0x10]`, `0x5acbb56  mov r8,[rbx+0x10]`, `0x5acbc9d  mov r11,[r10+0x10]`, `0x5acbd60  mov r11,[r10+0x10]`, `0x5acbbe0  mov r11,[r10+0x10]`, `0x5acba07  mov [r15+0x10],rax`, `0x5acbb5a  mov [rax+0x10],r8`, `0x5acbbe4  mov [r9+0x10],r11`, `0x5acbd64  mov [r9+0x10],r11`, `0x5acbc54  mov r9,[rax+r8+0x10]`, `0x5acbdd4  mov r9,[rax+r8+0x10]`, `0x5acbd1e  mov r10,[r15+r9+0x10]`, `0x5acaf8e  mov rax,[rax+0x10]`, `0x5acae2b  mov r8,[rbx+0x10]`, `0x5acaffb  mov rcx,[rbx+0x10]`, `0x5acb049  movapd [rbp+0x10],xmm0` | saves arg2 for the virtual call [I] | vector capacity ([rcx+0x10]) / element ptr field @0x10 (shared object, refcount-inc'd) | element ptr field @0x10 | element ptr field @0x10 (refcount-inc'd next) | ring-3 capacity/mask [I] | ctx object pointer (arg to 0x10EFEF0 / 0x5ACB650) | zero-init the element vector holder [I] |
| 0x18 | 4/4/1/8/16 | RW | `0x5acbe94  mov byte ptr [rbp+0x18],1`, `0x6bf73ec  movss [rsi+0x18],xmm0`, `0x5acba0b  mov rax,[rbx+0x18]`, `0x5acbb5e  mov r8,[rbx+0x18]`, `0x5acbbe8  mov r11,[r10+0x18]`, `0x5acbd68  mov r11,[r10+0x18]`, `0x5acbca6  mov r11,[r10+0x18]`, `0x5acba0f  mov [r15+0x18],rax`, `0x5acbb62  mov [rax+0x18],r8`, `0x5acbbec  mov [r9+0x18],r11`, `0x5acbd6c  mov [r9+0x18],r11`, `0x5acaf0a  movupd [rax+0x18],xmm0`, `0x5acaf0a  movupd [rax+0x18],xmm0`, `0x5acaf5c  movupd [rax+0x18],xmm0`, `0x5acafae  movupd [rax+0x18],xmm0`, `0x5acaebd  mov rax,[rbx+0x18]`, `0x5acaf22  mov rax,[rbx+0x18]`, `0x5acaf74  mov rax,[rbx+0x18]`, `0x5acaf80  mov rdx,[rax+0x18]` | element float @0x18 (r13d / count) | element ptr field @0x18 | - (producer ring entry; see producer table) | white-fill entry zeros @0x18 [I] | ring objects list base / ring-3 begin [I] |
| 0x20 | 4/4/8/8 | RW | `0x5acbe69  mov [rbp+0x20],rcx`, `0x5acbeb6  mov r8,[rbp+0x20]`, `0x5acbf1d  mov dword ptr [rsp+0x20],0`, `0x6bf73f6  movss [rsi+0x20],xmm6`, `0x5acba13  mov eax,[rbx+0x20]`, `0x5acbb66  mov r8d,[rbx+0x20]`, `0x5acbbf0  mov r11d,[r10+0x20]`, `0x5acbd70  mov r11d,[r10+0x20]`, `0x5acbcaf  mov r11d,[r10+0x20]`, `0x5acba16  mov [r15+0x20],eax`, `0x5acbb6a  mov [rax+0x20],r8d`, `0x5acbbf4  mov [r9+0x20],r11d`, `0x5acbd74  mov [r9+0x20],r11d`, `0x5acaf7c  mov rcx,[rax+0x20]`, `0x5acb2df  mov dword ptr [rsp+0x20],0`, `0x5acac06  mov qword ptr [rsp+0x20],0`, `0x5acb04e  mov qword ptr [rbp+0x20],0` | global singleton ptr 0x129CFC30 [V] | element dword field @0x20 | ring-3 bookkeeping [I] | stack arg to 0x2FE330 / 0x541F8F0 | element vector holder zero-init [I] |
| 0x28 | 4/1/8/8 | RW | `0x5acbe6d  mov byte ptr [rbp+0x28],0`, `0x5acbe8d  mov [rbp+0x28],al`, `0x5acbeb0  cmp byte ptr [rbp+0x28],1`, `0x5acbf18  mov [rsp+0x28],rax`, `0x5acba25  movss xmm0,[rbx+0x28]`, `0x5acbb78  movss xmm0,[rbx+0x28]`, `0x5acbc04  movss xmm1,[r10+0x28]`, `0x5acbd84  movss xmm1,[r10+0x28]`, `0x5acbcc5  movss xmm1,[r10+0x28]`, `0x5acba2a  movss [r15+0x28],xmm0`, `0x5acbb7d  movss [rax+0x28],xmm0`, `0x5acbc0a  movss [r9+0x28],xmm1`, `0x5acbd8a  movss [r9+0x28],xmm1`, `0x5acaf0f  mov dword ptr [rax+0x28],0x3F800000`, `0x5acaf61  mov dword ptr [rax+0x28],0x3F800000`, `0x5acafb3  mov dword ptr [rax+0x28],0x3F800000`, `0x5acae92  mov qword ptr [rdi+0x28],1`, `0x5acb2da  mov [rsp+0x28],rax`, `0x5acac01  mov byte ptr [rsp+0x28],0` | bool flag [I] | element float field @0x28 | white-fill entry float @0x28 [I] | texture blit slot field (object holder) [I] | stack arg (0xF276250 / byte 0) |
| 0x40 | 8/16 | W | `0x5acbe33  mov qword ptr [rbp+0x40],0xFFFFFFFFFFFFFFFE`, `0x5acb25a  movupd [rbp+0x40],xmm0` | SEH/GS cookie = -2 [I] | copied view {count,ptr} stash [I] |
| 0x360 | 8 | R | `0x5acbe9b  mov rax,[rax+0x360]` | vtable slot +0x360 of [rsi] (called next) [I] |
| 0xC | 4 | W | `0x6bf7390  lock dec dword ptr [r15+0xC]`, `0x6bf7430  lock dec dword ptr [rdi+0xC]`, `0x5aca83c  lock dec dword ptr [rdi+0xC]`, `0x5aca87f  lock dec dword ptr [rdi+0xC]`, `0x5acac70  lock dec dword ptr [r15+0xC]`, `0x5acacc0  lock dec dword ptr [r15+0xC]`, `0x5acacf9  lock dec dword ptr [r15+0xC]`, `0x5acad32  lock dec dword ptr [r15+0xC]` | second refcount-- [I] |
| 0x1C | 4 | W | `0x6bf73f1  movss [rsi+0x1C],xmm2` | element float @0x1C |
| 0x24 | 16/4/1 | RW | `0x6bf7402  movups [rsi+0x24],xmm0`, `0x5acba1a  movss xmm0,[rbx+0x24]`, `0x5acbb6e  movss xmm0,[rbx+0x24]`, `0x5acbbf8  movss xmm1,[r10+0x24]`, `0x5acbd78  movss xmm1,[r10+0x24]`, `0x5acbcb8  movss xmm1,[r10+0x24]`, `0x5acba1f  movss [r15+0x24],xmm0`, `0x5acbb73  movss [rax+0x24],xmm0`, `0x5acbbfe  movss [r9+0x24],xmm1`, `0x5acbd7e  movss [r9+0x24],xmm1`, `0x5aca706  mov byte ptr [rdi+0x24],0`, `0x5acb288  mov byte ptr [rdi+0x24],1` | element bytes @0x24 = [r9 arg] [I] | element float field @0x24 | texture dirty/processed flag [I] |
| 0x34 | 8 | RW | `0x6bf740a  mov [rsi+0x34],rax`, `0x5acba46  mov rax,[rbx+0x34]`, `0x5acbb96  mov r8,[rbx+0x34]`, `0x5acbc28  mov r11,[r10+0x34]`, `0x5acbda8  mov r11,[r10+0x34]`, `0x5acbcec  mov r11,[r10+0x34]`, `0x5acba4a  mov [r15+0x34],rax`, `0x5acbb9a  mov [rax+0x34],r8`, `0x5acbc2c  mov [r9+0x34],r11`, `0x5acbdac  mov [r9+0x34],r11` | element qword @0x34 = [r9 arg]+0x10 [I] | element qword field @0x34 |
| 0x3C | 1/4 | RW | `0x6bf740e  mov byte ptr [rsi+0x3C],0`, `0x5acba4e  movzx eax,byte ptr [rbx+0x3C]`, `0x5acbb9e  movzx r8d,byte ptr [rbx+0x3C]`, `0x5acbc30  movzx r11d,byte ptr [r10+0x3C]`, `0x5acbdb0  movzx r11d,byte ptr [r10+0x3C]`, `0x5acbcf5  movzx r11d,byte ptr [r10+0x3C]`, `0x5acba52  mov [r15+0x3C],al`, `0x5acbba3  mov [rax+0x3C],r8b`, `0x5acbc35  mov [r9+0x3C],r11b`, `0x5acbdb5  mov [r9+0x3C],r11b`, `0x5acbcfa  mov [rax+r9],r11b`, `0x5acaf1b  mov dword ptr [rax+0x3C],0x3F800000`, `0x5acaf6d  mov dword ptr [rax+0x3C],0x3F800000`, `0x5acafbf  mov dword ptr [rax+0x3C],0x3F800000` | element byte @0x3C = 0 | element byte field @0x3C | white-fill entry float @0x3C [I] |
| 0x74 | 4 | R | `0x6bf7297  mov eax,[r8+0x74]` | mode/count selector, clamped < 4 [I] |
| 0x120 | 4 | R | `0x6bf72b9  mulss xmm6,[r8+rax*4+0x120]` | indexed float table entry [I] |
| 0x80 | 8 | RW | `0x6bf7322  mov rcx,[rbx+0x80]`, `0x5aca9cf  mov [rbp+0x80],rax`, `0x5acb021  mov [rbp+0x80],rax`, `0x5acb217  mov rax,[rbp+0x80]` | descriptor object ptr of source | saved third pointer of the source object; later its byte is asserted [I] | object ptr at +0x80 of builder obj; null -> default 0x129C1210 [I] |
| 0xB0 | 16/-/8 | RW | (only `lea r12,[rbx+0xB0]` / `mov [rsi],r12`), `0x5acaaec  mov [rbp+0xB0],rax`, `0x5acaafa  mov [rbp+0xB5],rax`, `0x5acac36  movaps xmm0,[rbp+0xB0]`, `0x5acac40  movaps [rbp+0xB0],xmm6`, `0x5acaff3  movupd [rbp+0xB0],xmm0`, `0x5acb2cb  movapd [rbp+0xB0],xmm0` | sub-object address, stored by pointer [V] | std::string buffer init (13-char literal) [I] | string move-out / float pair / exception record [I] |
| 0x348 | 4 | R | `0x6bf72c3  addss xmm6,[rbx+0x348]` | float addend of the uv computation [I] |
| 0x34C | 4 | RW | `0x6bf72e2  mov eax,[rbx+0x34C]`, `0x6bf72e8  mov [rbp-0x38],rax`, `0x6bf73cb  cvtsi2ss xmm1,dword ptr [rbp-0x38]` | count value, also cached on the frame |
| 0x350 | 4 | R | `0x6bf72ef  mov r8d,[rbx+0x350]` | divisor for the row idiv [I] |
| 0x354 | 4 | R | `0x6bf72a2  cvtsi2ss xmm0,dword ptr [rbx+0x354]` | divisor of the constant [I] |
| 0x364 | 1 | R | `0x6bf73a7  mov bl,[rbx+0x364]` | bool: selects the @0x1C formula [I] |
| 0x365 | 1 | R | `0x6bf728e  cmp byte ptr [rcx+0x365],0` | bool: skip the uv recompute branch [I] |
| -0x28 | 8 | RW | `0x6bf736d  mov r15,[rbp-0x28]`, `0x6bf7371  mov [rbp-0x28],rcx`, `0x6bf7412  mov rdi,[rbp-0x28]`, `0x5acb22e  lea rbx,[rbp-0x28]` | old refcounted object slot | (address taken; object released via 0x7E6D0) [I] |
| -0x30 | 16/8 | W | `0x6bf733a  movaps [rbp-0x30],xmm0`, `0x6bf7369  mov [rbp-0x30],rax`, `0x5acab0c  mov qword ptr [rbp-0x30],0xD` | new refcounted object slot (arg to 0x4DFB570) | string-view length 0xD [I] |
| -0x38 | 4/8 | W | `0x6bf72e8  mov [rbp-0x38],rax`, `0x5acab08  mov [rbp-0x38],rax` | cached [rbx+0x34C] | string-view data ptr [I] |
| -0x40 | 8 | RW | `0x6bf7281  mov [rbp-0x40],r9`, `0x6bf73fb  mov rax,[rbp-0x40]` | saved r9 argument (source of the 16-byte copy) |
| 0x2C | 4/16 | RW | `0x5acba30  movss xmm0,[rbx+0x2C]`, `0x5acbb82  movss xmm0,[rbx+0x2C]`, `0x5acbc10  movss xmm1,[r10+0x2C]`, `0x5acbd90  movss xmm1,[r10+0x2C]`, `0x5acbcd2  movss xmm1,[r10+0x2C]`, `0x5acba35  movss [r15+0x2C],xmm0`, `0x5acbb87  movss [rax+0x2C],xmm0`, `0x5acbc16  movss [r9+0x2C],xmm1`, `0x5acbd96  movss [r9+0x2C],xmm1`, `0x5acaf16  movupd [rax+0x2C],xmm0`, `0x5acaf68  movupd [rax+0x2C],xmm0`, `0x5acafba  movupd [rax+0x2C],xmm0` | element float field @0x2C | white-fill entry zeros @0x2C [I] |
| 0x30 | 4/8 | RW | `0x5acba3b  movss xmm0,[rbx+0x30]`, `0x5acbb8c  movss xmm0,[rbx+0x30]`, `0x5acbc1c  movss xmm1,[r10+0x30]`, `0x5acbd9c  movss xmm1,[r10+0x30]`, `0x5acbcdf  movss xmm1,[r10+0x30]`, `0x5acba40  movss [r15+0x30],xmm0`, `0x5acbb91  movss [rax+0x30],xmm0`, `0x5acbc22  movss [r9+0x30],xmm1`, `0x5acbda2  movss [r9+0x30],xmm1`, `0x5aca9cb  mov rax,[rax+0x30]`, `0x5acafd7  movsd xmm1,[rdi+0x30]`, `0x5acae9a  mov [rdi+0x30],rax` | element float field @0x30 | third pointer of the [rbx+0xC8] source object | object +0x10 stored / read back as float pair for the abs math [I] |
| -0x3C | 8 | W | `0x5acbd13  mov [rax+r9-0x3C],r10` | element qword field @0 (shifted destination) [I] | element qword field @0 (shifted second-loop destination) [I] |
| -0x34 | 16/8 | W | `0x5acbc98  mov [rax+r9-0x34],r11`, `0x5acbd18  movups [rax+r9-0x34],xmm0` | element ptr field @8 [I] | zero the ptr field @8 [I] |
| -0x2C | 8 | W | `0x5acbca1  mov [rax+r9-0x2C],r11` | element ptr field @0x10 [I] |
| -0x24 | 8 | W | `0x5acbcaa  mov [rax+r9-0x24],r11` | element ptr field @0x18 [I] |
| -0x1C | 4 | W | `0x5acbcb3  mov [rax+r9-0x1C],r11d` | element dword field @0x20 [I] |
| -0x14 | 4 | W | `0x5acbccb  movss [rax+r9-0x14],xmm1` | element float field @0x28 [I] |
| -0xC | 4 | W | `0x5acbce5  movss [rax+r9-0xC],xmm1` | element float field @0x30 [I] |
| -0x8 | 8 | W | `0x5acbcf0  mov [rax+r9-8],r11` | element qword field @0x34 [I] |
| 0x14 | 4 | W | `0x5acaf03  mov dword ptr [rax+0x14],0x3F800000`, `0x5acaf55  mov dword ptr [rax+0x14],0x3F800000`, `0x5acafa7  mov dword ptr [rax+0x14],0x3F800000` | white-fill entry float @0x14 [I] |
| 0x38 | 1/8 | RW | `0x5acaf78  mov byte ptr [rax+0x38],1`, `0x5acad53  mov rcx,[rbp+0x38]`, `0x5acadae  mov rcx,[rbp+0x38]` | ring-3 reset flag [I] | string heap buffer |
| 0x44 | 1 | R | `0x5acaab3  cmp byte ptr [r14+0x44],0xFF` | "no special value" check (0xFF = none) [I] |
| 0x48 | 8 | R | `0x5acaf38  mov rdx,[rax+0x48]` | ring-2 buffer [I] |
| 0x50 | 8 | R | `0x5acaf3c  mov rax,[rax+0x50]`, `0x5acad49  mov rax,[rbp+0x50]`, `0x5acada0  mov rax,[rbp+0x50]` | ring-2 capacity/mask [I] | string capacity (>=0x10 → heap) |
| 0x58 | 8 | R | `0x5acab87  mov rax,[rax+0x58]`, `0x5acabeb  mov rax,[rax+0x58]`, `0x5acaf2e  mov rdx,[rax+0x58]` | map-node value ptr / ring-2 begin [I] |
| 0x60 | 8 | R | `0x5acaf2a  mov rcx,[rax+0x60]` | ring-2 bookkeeping [I] |
| 0x68 | 1 | RW | `0x5acaa9f  cmp byte ptr [r14+0x68],1`, `0x5acae1b  cmp byte ptr [r15+0x68],1`, `0x5aca6f3  mov byte ptr [rbp+0x68],0` | validity flag == 1 check [I] | flag cleared before 0x39A7D40 [I] |
| 0x70 | 8 | R | `0x5aca80e  cmp qword ptr [rbp+0x70],0`, `0x5acab6d  add r15,[rbp+0x70]`, `0x5acabd5  add r15,[rbp+0x70]`, `0x5acabf9  mov rcx,[rbp+0x70]` | out-param of virtual +0x338: an object with a map at +0x1A8 [I] |
| 0x78 | 8 | R | `0x5aca81e  mov rdi,[rbp+0x78]` | object to release on cleanup [I] |
| 0x85 | 1 | W | `0x5acae9e  mov byte ptr [rdi+0x85],1` | texture field set when a default object was used [I] |
| 0x88 | 8 | RW | `0x5aca75a  mov qword ptr [rbp+0x88],0`, `0x5aca79a  mov [rbp+0x88],r14`, `0x5aca8e0  mov rcx,[rbp+0x88]`, `0x5acb2b1  mov [rbp+0x88],rax` | source view first pointer (0x128C4FD0 / exception record string [I]) |
| 0x90 | 1/8 | RW | `0x5aca765  mov byte ptr [rbp+0x90],0`, `0x5aca7a1  mov byte ptr [rbp+0x90],1`, `0x5aca8d7  cmp byte ptr [rbp+0x90],1`, `0x5acb2b8  mov qword ptr [rbp+0x90],0x19` | source view bool flag (release via 0x3B2020) | exception record length 0x19 [I] |
| 0x98 | 16/8 | RW | `0x5aca770  movupd [rbp+0x98],xmm0`, `0x5aca85d  movupd [rbp+0x98],xmm0`, `0x5aca874  movupd [rbp+0x98],xmm6`, `0x5aca7a8  mov [rbp+0x98],rax`, `0x5acae49  mov rax,[rbp+0x98]`, `0x5acb010  mov rax,[rbp+0x98]` | source view second pointer / zeroed | source view second pointer (checked byte==1) |
| 0xA0 | 8 | RW | `0x5aca7af  mov [rbp+0xA0],rcx`, `0x5aca856  mov rdi,[rbp+0xA0]`, `0x5aca895  mov rdi,[rbp+0xA0]` | source view third pointer (released twice on cleanup) |
| 0xA8 | 8 | RW | `0x5aca778  mov qword ptr [rbp+0xA8],0`, `0x5aca7b6  mov [rbp+0xA8],rdx`, `0x5aca89c  mov qword ptr [rbp+0xA8],0`, `0x5acae62  mov rcx,[rbp+0xA8]`, `0x5acb028  mov rcx,[rbp+0xA8]` | source view fourth pointer (object with virtual [+8]) |
| 0xB5 | 8 | W | `0x5acaafa  mov [rbp+0xB5],rax` | overlapping tail of the string buffer [I] |
| 0xB8 | 8 | RW | `0x5acaac4  mov qword ptr [rbp+0xB8],0`, `0x5acad10  mov r15,[rbp+0xB8]`, `0x5aca986  mov rax,[rbx+0xB8]`, `0x5acb08c  mov rax,[rbx+0xB8]`, `0x5acb110  mov rax,[rbx+0xB8]` | string field (zeroed) | object release on cleanup | asserted nonnull object (DEADC0DE checks) |
| 0xC0 | 16/8 | RW | `0x5acaacf  mov qword ptr [rbp+0xC0],0xD`, `0x5acafd0  mov [rbp+0xC0],rax`, `0x5acac87  movapd xmm0,[rbp+0xC0]`, `0x5acac8f  movaps [rbp+0xC0],xmm6` | string size 0xD / two 1.0f doubles [I] | 16-byte move to [rdi+0x180] [I] |
| 0xC8 | 8 | RW | `0x5acaada  mov qword ptr [rbp+0xC8],0xF`, `0x5acab22  mov rax,[rbp+0xC8]`, `0x5acacd7  mov r15,[rbp+0xC8]`, `0x5aca9ad  mov rax,[rbx+0xC8]`, `0x5acb0a8  mov rax,[rbx+0xC8]`, `0x5acb137  mov rax,[rbx+0xC8]` | string capacity (0xF) / object release | source list object (its +0xE8 is the begin/end pair) |
| 0xD8 | 8 | W | `0x5aca6a2  mov qword ptr [rbp+0xD8],0xFFFFFFFFFFFFFFFE` | SEH/GS cookie = -2 [I] |
| 0xE0 | 16 | RW | `0x5aca69b  movaps [rbp+0xE0],xmm6`, `0x5aca90a  movaps xmm6,[rbp+0xE0]` | xmm6 save/restore |
| 0xE8 | 8 | R | `0x5aca9b4  mov rax,[rax+0xE8]`, `0x5acb0af  mov rcx,[rax+0xE8]`, `0x5acb13e  mov rcx,[rax+0xE8]` | begin/end pair of the source object's item list [I] |
| 0x160 | 1 | R | `0x5aca979  cmp byte ptr [rdi+0x160],0` | mode flag: 0 → alternate fill path [I] |
| 0x168 | 8 | R | `0x5aca7bd  mov rcx,[rdi+0x168]`, `0x5aca7d9  mov rcx,[rdi+0x168]`, `0x5aca7f6  mov rcx,[rdi+0x168]`, `0x5aca9d6  mov rcx,[rdi+0x168]` | interface object for the virtual calls [+0x338]/[+0x538]/[+0x198] |
| 0x170 | 16/8 | RW | `0x5aca925  mov rax,[rdi+0x170]`, `0x5acaa67  mov rax,[rdi+0x170]`, `0x5acae7f  mov rax,[rdi+0x170]`, `0x5acade8  lea rax,[rdi+0x170]`, `0x5acb208  lea rax,[rdi+0x170]`, `0x5acac26  lea rax,[rdi+0x170]`, `0x5acac4e  movups [rdi+0x170],xmm0` | current source pointer (null → rebuild / default) | store the resolved string/object into rdi+0x170 |
| 0x178 | 8 | R | `0x5acac47  mov r15,[rdi+0x178]` | old object at +0x170's neighbor, released after swap [I] |
| 0x180 | 16 | W | `0x5acac9d  movupd [rdi+0x180],xmm0` | 16-byte move from [rbp+0xC0] |
| 0x188 | 8 | R | `0x5acac96  mov r15,[rdi+0x188]` | old object, released after the +0x180 swap [I] |
| 0x190 | 8 | RW | `0x5acaa0f  cmp qword ptr [rdi+0x190],0`, `0x5acaa4a  cmp rcx,[rdi+0x190]`, `0x5acaa60  mov [rdi+0x190],rcx` | previous-source cache compared/stored [I] |
| 0x198 | 8 | RW | `0x5acaa08  mov r12,[rdi+0x198]`, `0x5acaa25  mov [rdi+0x198],r13` | previous-source object cache [I] |
| 0x1A0 | 1 | RW | `0x5acaa1b  or r14b,[rdi+0x1A0]`, `0x5acaa2c  setne [rdi+0x1A0]` | pending-change byte flag [I] |
| 0x278 | 8 | R | `0x5aca9f1  mov rdx,[rcx+0x278]` | vtable slot +0x278 of the +0x538 result (called next) [I] |
| 0x338 | 8 | R | `0x5aca7c7  mov rax,[rax+0x338]` | vtable slot +0x338 [I] |
| 0x538 | 8 | R | `0x5aca7e3  mov rax,[rax+0x538]`, `0x5aca9e0  mov rax,[rax+0x538]` | vtable slot +0x538 [I] |
| -0x48 | 16 | R | `0x5acb255  movupd xmm0,[rbp-0x48]` | copied element-vector view [I] |
## FUNCTION 5ACBE20 — clone (notify/clone wrapper)
Signature guess [I]: `void clone(void* src /*rcx in rsi*/, void* dst /*rdx in rdi*/)` — wraps a global singleton access (0x129CFC30) with one-time init and a virtual clone call plus a name-registration call 0x77A2500.

### 0x5acbe20..0x5acbec8: Prologue (4 pushes, frame 0xC8, rbp=rsp+0x80, SEH cookie [rbp+0x40]=-2); rdi=rdx (arg2), rsi=rcx (arg1). Reads TLS state: index at [0x128767C8] into gs:[0x58] array, then compares global dword [0x129CFD68] (init counter) with [rcx+4]; if counter is greater (init not done [I]) jumps to the one-time-init slow path at 0x5ACBEDA. Otherwise stores 0x129CFC30 into [rbp+0x20], byte flag [rbp+0x28]=0, zeroes [rbp+0x38] and [rbp-0x18], calls 0x39A7D40(rcx=rsi, rdx=&[rbp+0x30], r8=&[rbp-0x50]) storing the bool result in [rbp+0x28]; saves rdi in [rbp+0x10], byte [rbp+0x18]=1; makes the virtual call at slot +0x360 of [rsi]'s vtable with rdx=&[rbp+0x10]; if byte [rbp+0x28]==1, calls 0x77A2500(rcx=0x1244FD00, rdx=&[rbp+0x30], r8=[rbp+0x20]+0x60) — register/annotate the produced object with a descriptor and name string [I].
0x5acbe20  push rbp
0x5acbe21  push rsi
0x5acbe22  push rdi
0x5acbe23  push rbx
0x5acbe24  sub rsp,0xC8
0x5acbe2b  lea rbp,[rsp+0x80]
0x5acbe33  mov qword ptr [rbp+0x40],0xFFFFFFFFFFFFFFFE
0x5acbe3b  mov rdi,rdx
0x5acbe3e  mov rsi,rcx
0x5acbe41  mov eax,[0x129CFD68]
0x5acbe47  mov ecx,[0x128767C8]
0x5acbe4d  mov rdx,gs:[0x58]
0x5acbe56  mov rcx,[rdx+rcx*8]
0x5acbe5a  cmp eax,[rcx+4]
0x5acbe60  jg short 0x5ACBEDA
0x5acbe62  lea rcx,[0x129CFC30]
0x5acbe69  mov [rbp+0x20],rcx
0x5acbe6d  mov byte ptr [rbp+0x28],0
0x5acbe71  lea rbx,[rbp+0x30]
0x5acbe75  mov qword ptr [rbp+0x38],0
0x5acbe7d  mov byte ptr [rbp-0x18],0
0x5acbe81  lea r8,[rbp-0x50]
0x5acbe85  mov rdx,rbx
0x5acbe88  call 0x39A7D40
0x5acbe8d  mov [rbp+0x28],al
0x5acbe90  mov [rbp+0x10],rdi
0x5acbe94  mov byte ptr [rbp+0x18],1
0x5acbe98  mov rax,[rsi]
0x5acbe9b  mov rax,[rax+0x360]
0x5acbea2  lea rdx,[rbp+0x10]
0x5acbea6  mov rcx,rsi
0x5acbea9  call qword ptr [0xF99FFA0]
0x5acbeaf  nop
0x5acbeb0  cmp byte ptr [rbp+0x28],1
0x5acbeb4  jne short 0x5ACBECE
0x5acbeb6  mov r8,[rbp+0x20]
0x5acbeba  add r8,0x60
0x5acbebe  lea rcx,[0x1244FD00]
0x5acbec5  mov rdx,rbx
0x5acbec8  call 0x77A2500

### 0x5acbecd..0x5acbf59: Epilogue (ret). Then the slow path 0x5ACBEDA: thread-safe one-time init of the global counter at [0x129CFD68] via helpers 0xE938CB0 / 0xE938D70; if the counter is still 0xFFFFFFFF, builds an exception record — string ptr 0xF52E07A with qword length 0x15 at [rbp..rbp+8], 16 bytes copied from 0xF0BCBF8 into [rbp-0x10] — and calls 0x2FE330(rcx=0x129CFC30, rdx=&[rbp-0x10], r8b=1, r9=rbp, [rsp+0x20]=0xF276918, [rsp+0x28]=0) to throw/report [I]; then registers 0x5AF27C0 through 0xE935740 (atexit-style callback [I]), re-inits via 0xE938D70, and jumps back to 0x5ACBE62. Ends with alignment nop.
0x5acbecd  nop
0x5acbece  add rsp,0xC8
0x5acbed5  pop rbx
0x5acbed6  pop rdi
0x5acbed7  pop rsi
0x5acbed8  pop rbp
0x5acbed9  ret
0x5acbeda  lea rcx,[0x129CFD68]
0x5acbee1  call 0xE938CB0
0x5acbee6  cmp dword ptr [0x129CFD68],0xFFFFFFFF
0x5acbeed  jne 0x5ACBE62
0x5acbef3  lea rax,[0xF52E07A]
0x5acbefa  mov [rbp],rax
0x5acbefe  mov qword ptr [rbp+8],0x15
0x5acbf06  movups xmm0,[0xF0BCBF8]
0x5acbf0d  movaps [rbp-0x10],xmm0
0x5acbf11  lea rax,[0xF276918]
0x5acbf18  mov [rsp+0x28],rax
0x5acbf1d  mov dword ptr [rsp+0x20],0
0x5acbf25  lea rcx,[0x129CFC30]
0x5acbf2c  lea rdx,[rbp-0x10]
0x5acbf30  mov r9,rbp
0x5acbf33  mov r8b,1
0x5acbf36  call 0x2FE330
0x5acbf3b  nop
0x5acbf3c  lea rcx,[0x5AF27C0]
0x5acbf43  call 0xE935740
0x5acbf48  lea rcx,[0x129CFD68]
0x5acbf4f  call 0xE938D70
0x5acbf54  jmp 0x5ACBE62
0x5acbf59  nop [rax]


## FUNCTION 5ACB9C0 — element push_back (vector<element64> insert with growth)
Signature guess [I]: `void* push_back(element_vector* vec /*rcx*/, element64* src /*rdx in rbx*/)` — appends a copy of a 0x40-byte element to a vector of 64-byte elements (begin=[rcx], end=[rcx+8], cap=[rcx+0x10]); tail-call 0x5AF0720 when the vector must grow.

### 0x5acb9c0..0x5acba52: Fast path: if end ([rcx+8]) != cap ([rcx+0x10]), copy the 0x40-byte element from rbx into r15 (old end) field by field: [rbx]→[r15] (qword), zero xmm0 over [r15+8] (16 bytes, clears the copied-pointer field), refcount-inc the object at [rbx+0x10] (`lock inc dword [rax+8]`), then copy +8, +0x10, +0x18 (qwords), +0x20 (dword), +0x24..+0x30 (floats via movss), +0x34 (qword), +0x3C (byte); bump end += 0x40.
0x5acb9c0  push r15
0x5acb9c2  push r14
0x5acb9c4  push r13
0x5acb9c6  push r12
0x5acb9c8  push rsi
0x5acb9c9  push rdi
0x5acb9ca  push rbx
0x5acb9cb  sub rsp,0x20
0x5acb9cf  mov rbx,rdx
0x5acb9d2  mov r15,[rcx+8]
0x5acb9d6  cmp r15,[rcx+0x10]
0x5acb9da  je 0x5ACBA6B
0x5acb9e0  mov rax,[rbx]
0x5acb9e3  mov [r15],rax
0x5acb9e6  xorps xmm0,xmm0
0x5acb9e9  movups [r15+8],xmm0
0x5acb9ee  mov rax,[rbx+0x10]
0x5acb9f2  test rax,rax
0x5acb9f5  je short 0x5ACB9FB
0x5acb9f7  lock inc dword ptr [rax+8]
0x5acb9fb  mov rax,[rbx+8]
0x5acb9ff  mov [r15+8],rax
0x5acba03  mov rax,[rbx+0x10]
0x5acba07  mov [r15+0x10],rax
0x5acba0b  mov rax,[rbx+0x18]
0x5acba0f  mov [r15+0x18],rax
0x5acba13  mov eax,[rbx+0x20]
0x5acba16  mov [r15+0x20],eax
0x5acba1a  movss xmm0,[rbx+0x24]
0x5acba1f  movss [r15+0x24],xmm0
0x5acba25  movss xmm0,[rbx+0x28]
0x5acba2a  movss [r15+0x28],xmm0
0x5acba30  movss xmm0,[rbx+0x2C]
0x5acba35  movss [r15+0x2C],xmm0
0x5acba3b  movss xmm0,[rbx+0x30]
0x5acba40  movss [r15+0x30],xmm0
0x5acba46  mov rax,[rbx+0x34]
0x5acba4a  mov [r15+0x34],rax
0x5acba4e  movzx eax,byte ptr [rbx+0x3C]
0x5acba52  mov [r15+0x3C],al

### 0x5acba56..0x5acbad7: Epilogue of the fast path. Then growth path 0x5ACBA6B: r12 = end-begin = used bytes; rax = used>>6 (old element count); new capacity rdi = rax + max(rax>>1, ...) with the standard growth clamp against 0x3FFFFFFFFFFFFFF (overflow → `shr rax,0x3A`, nonzero jumps to 0x5ACBE19 → call 0x75740 = throw length_error/abort [I], then int3); if new capacity 0 skip alloc (0x5ACBB2A). Else r14 = rdi<<6 (byte size); if rdi >= 0x40, allocate via operator new ([0x1233E1A8] → [+8] with rdx=r14) then align the result up to 32 bytes (rax+0x27 & ~0x1F) keeping the raw pointer at [rdx-8] [I]; else plain alloc of r14 bytes; rcx = old vector ptr (r13=rcx saved).
0x5acba56  add qword ptr [rcx+8],0x40
0x5acba5b  add rsp,0x20
0x5acba5f  pop rbx
0x5acba60  pop rdi
0x5acba61  pop rsi
0x5acba62  pop r12
0x5acba64  pop r13
0x5acba66  pop r14
0x5acba68  pop r15
0x5acba6a  ret
0x5acba6b  mov r12,r15
0x5acba6e  sub r12,[rcx]
0x5acba71  mov rax,r12
0x5acba74  sar rax,6
0x5acba78  lea rsi,[rax+1]
0x5acba7c  mov rdi,rax
0x5acba7f  shr rdi,1
0x5acba82  mov rdx,0x3FFFFFFFFFFFFFF
0x5acba8c  mov r8,rdx
0x5acba8f  sub r8,rdi
0x5acba92  add rdi,rax
0x5acba95  cmp rdi,rsi
0x5acba98  cmovbe rdi,rsi
0x5acba9c  cmp rax,r8
0x5acba9f  cmova rdi,rdx
0x5acbaa3  mov rax,rdi
0x5acbaa6  shr rax,0x3A
0x5acbaaa  jne 0x5ACBE19
0x5acbab0  test rdi,rdi
0x5acbab3  je short 0x5ACBB2A
0x5acbab5  mov r13,rcx
0x5acbab8  mov r14,rdi
0x5acbabb  shl r14,6
0x5acbabf  cmp rdi,0x40
0x5acbac3  jb short 0x5ACBAFD
0x5acbac5  or r14,0x27
0x5acbac9  mov rcx,[0x1233E1A8]
0x5acbad0  mov rax,[rcx]
0x5acbad3  mov rax,[rax+8]
0x5acbad7  mov rdx,r14

### 0x5acbada..0x5acbb6a: Allocator call (`call qword ptr [0xF99FFA0]` with rcx=allocator, rdx=r14); on null result 0x9BC830 (throw bad_alloc [I]); aligned branch stores the raw block at [rdx-8]. Then rax = rdx+r12 (destination = new buffer + used bytes) and the new element from rbx is written at the end slot: [rbx]→[rdx+r12] (qword), zero over [rdx+r12+8] (16 bytes), refcount-inc [rbx+0x10], then copies +8, +0x10, +0x18 (qwords), +0x20 (dword), +0x24..+0x30 (floats), +0x34 (qword), +0x3C (byte) into [rax+...].
0x5acbada  call qword ptr [0xF99FFA0]
0x5acbae0  test rax,rax
0x5acbae3  je 0x5ACBE06
0x5acbae9  mov rdx,rax
0x5acbaec  add rdx,0x27
0x5acbaf0  and rdx,0xFFFFFFFFFFFFFFE0
0x5acbaf4  mov [rdx-8],rax
0x5acbaf8  mov rcx,r13
0x5acbafb  jmp short 0x5ACBB2C
0x5acbafd  mov rcx,[0x1233E1A8]
0x5acbb04  mov rax,[rcx]
0x5acbb07  mov rax,[rax+8]
0x5acbb0b  mov rdx,r14
0x5acbb0e  call qword ptr [0xF99FFA0]
0x5acbb14  mov rdx,rax
0x5acbb17  test rax,rax
0x5acbb1a  mov rcx,r13
0x5acbb1d  jne short 0x5ACBB2C
0x5acbb1f  mov rcx,r14
0x5acbb22  call 0x9BC830
0x5acbb27  mov rcx,r13
0x5acbb2a  xor edx,edx
0x5acbb2c  lea rax,[rdx+r12]
0x5acbb30  mov r8,[rbx]
0x5acbb33  mov [rdx+r12],r8
0x5acbb37  xorps xmm0,xmm0
0x5acbb3a  movups [rdx+r12+8],xmm0
0x5acbb40  mov r8,[rbx+0x10]
0x5acbb44  test r8,r8
0x5acbb47  je short 0x5ACBB4E
0x5acbb49  lock inc dword ptr [r8+8]
0x5acbb4e  mov r8,[rbx+8]
0x5acbb52  mov [rax+8],r8
0x5acbb56  mov r8,[rbx+0x10]
0x5acbb5a  mov [rax+0x10],r8
0x5acbb5e  mov r8,[rbx+0x18]
0x5acbb62  mov [rax+0x18],r8
0x5acbb66  mov r8d,[rbx+0x20]
0x5acbb6a  mov [rax+0x20],r8d

### 0x5acbb6e..0x5acbc28: Finish copying the new element ([rbx+0x24..0x34, +0x3C] → [rax+...]); then the "elements before/at the copy point" loop 0x5ACBBC0..0x5ACBC44: moves old-buffer elements from [rax+r8] to [rdx+r8] with stride 0x40 (r8 += 0x40, r10 += 0x40) until r10 == r15 (old end): qword [r10+X]→[r9+X] at +8, +0x10, +0x18, +0x18→(copy), dword +0x20, floats +0x24..+0x30, qword +0x34, byte +0x3C; refcount-inc each copied pointer at [r9+0x10] (`lock inc dword [r9+8]`).
0x5acbb6e  movss xmm0,[rbx+0x24]
0x5acbb73  movss [rax+0x24],xmm0
0x5acbb78  movss xmm0,[rbx+0x28]
0x5acbb7d  movss [rax+0x28],xmm0
0x5acbb82  movss xmm0,[rbx+0x2C]
0x5acbb87  movss [rax+0x2C],xmm0
0x5acbb8c  movss xmm0,[rbx+0x30]
0x5acbb91  movss [rax+0x30],xmm0
0x5acbb96  mov r8,[rbx+0x34]
0x5acbb9a  mov [rax+0x34],r8
0x5acbb9e  movzx r8d,byte ptr [rbx+0x3C]
0x5acbba3  mov [rax+0x3C],r8b
0x5acbba7  mov rax,[rcx]
0x5acbbaa  mov r8,[rcx+8]
0x5acbbae  cmp r15,r8
0x5acbbb1  je 0x5ACBD36
0x5acbbb7  cmp rax,r15
0x5acbbba  je 0x5ACBC70
0x5acbbc0  xor r8d,r8d
0x5acbbc3  xorps xmm0,xmm0
0x5acbbc6  jmp 0x5ACBC46
0x5acbbcb  nop [rax+rax]
0x5acbbd0  lea r9,[rdx+r8]
0x5acbbd4  lea r10,[rax+r8]
0x5acbbd8  mov r11,[r10+8]
0x5acbbdc  mov [r9+8],r11
0x5acbbe0  mov r11,[r10+0x10]
0x5acbbe4  mov [r9+0x10],r11
0x5acbbe8  mov r11,[r10+0x18]
0x5acbbec  mov [r9+0x18],r11
0x5acbbf0  mov r11d,[r10+0x20]
0x5acbbf4  mov [r9+0x20],r11d
0x5acbbf8  movss xmm1,[r10+0x24]
0x5acbbfe  movss [r9+0x24],xmm1
0x5acbc04  movss xmm1,[r10+0x28]
0x5acbc0a  movss [r9+0x28],xmm1
0x5acbc10  movss xmm1,[r10+0x2C]
0x5acbc16  movss [r9+0x2C],xmm1
0x5acbc1c  movss xmm1,[r10+0x30]
0x5acbc22  movss [r9+0x30],xmm1
0x5acbc28  mov r11,[r10+0x34]
0x5acbc2c  mov [r9+0x34],r11
0x5acbc30  movzx r11d,byte ptr [r10+0x3C]
0x5acbc35  mov [r9+0x3C],r11b
0x5acbc39  add r8,0x40
0x5acbc3d  add r10,0x40
0x5acbc41  cmp r10,r15
0x5acbc44  je short 0x5ACBC6C
0x5acbc46  mov r9,[rax+r8]
0x5acbc4a  mov [rdx+r8],r9
0x5acbc4e  movups [rdx+r8+8],xmm0
0x5acbc54  mov r9,[rax+r8+0x10]
0x5acbc59  test r9,r9
0x5acbc5c  je 0x5ACBBD0
0x5acbc62  lock inc dword ptr [r9+8]
0x5acbc67  jmp 0x5ACBBD0
0x5acbc6c  mov r8,[rcx+8]

### 0x5acbc6c..0x5acbcfa: Second move loop 0x5ACBC70..0x5ACBD09 (r8 reloaded from [rcx+8]; guard: if r15==r8 → 0x5ACBDEC): copies old elements that sit after the insertion point — source [r15+r9] (old buffer at old end + r9), destination [rax+r9-0x3C] where rax = r12+rdx+0x7C, so dest = newbuf + r12 + 0x40 + r9 (the slot after the new element) [I]; same field layout with shifted displacements (-0x3C qword, -0x34 16B zero via movups, -0x2C/-0x24 qwords, -0x1C dword, -0x18/-0x14/-0x10/-0xC floats, -8 qword, 0 byte); refcount-inc the source pointer at [r10+8] (`lock inc dword [r10+8]`); loop until r10 == r8.
0x5acbc70  cmp r15,r8
0x5acbc73  je 0x5ACBDEC
0x5acbc79  lea rax,[r12+rdx]
0x5acbc7d  add rax,0x7C
0x5acbc81  xor r9d,r9d
0x5acbc84  xorps xmm0,xmm0
0x5acbc87  jmp 0x5ACBD0F
0x5acbc8c  nop [rax]
0x5acbc90  lea r10,[r15+r9]
0x5acbc94  mov r11,[r10+8]
0x5acbc98  mov [rax+r9-0x34],r11
0x5acbc9d  mov r11,[r10+0x10]
0x5acbca1  mov [rax+r9-0x2C],r11
0x5acbca6  mov r11,[r10+0x18]
0x5acbcaa  mov [rax+r9-0x24],r11
0x5acbcaf  mov r11d,[r10+0x20]
0x5acbcb3  mov [rax+r9-0x1C],r11d
0x5acbcb8  movss xmm1,[r10+0x24]
0x5acbcbe  movss [rax+r9-0x18],xmm1
0x5acbcc5  movss xmm1,[r10+0x28]
0x5acbccb  movss [rax+r9-0x14],xmm1
0x5acbcd2  movss xmm1,[r10+0x2C]
0x5acbcd8  movss [rax+r9-0x10],xmm1
0x5acbcdf  movss xmm1,[r10+0x30]
0x5acbce5  movss [rax+r9-0xC],xmm1
0x5acbcec  mov r11,[r10+0x34]
0x5acbcf0  mov [rax+r9-8],r11
0x5acbcf5  movzx r11d,byte ptr [r10+0x3C]
0x5acbcfa  mov [rax+r9],r11b

### 0x5acbcfe..0x5acbd9c: (the `0x5acbcfa  mov [rax+r9],r11b` line is listed at the end of the previous phase) Loop body continued: stride update (r9 += 0x40, r10 += 0x40, loop while r10 != r8) and the copy prologue 0x5ACBD0F..0x5ACBD31 ([r15+r9]→[rax+r9-0x3C] qword, zero movups over [rax+r9-0x34], refcount-inc [r15+r9+0x10]); then the third move loop 0x5ACBD36..0x5ACBDC4 (reached when old begin == rax, i.e. all old elements move [I]): copies [rax+r8]→[rdx+r8] with the same field layout (+8 qword, +0x10, +0x18 qwords, +0x20 dword, +0x24..+0x30 floats, +0x34 qword, +0x3C byte) and refcount-inc at [r9+0x10].
0x5acbcfe  add r9,0x40
0x5acbd02  add r10,0x40
0x5acbd06  cmp r10,r8
0x5acbd09  je 0x5ACBDEC
0x5acbd0f  mov r10,[r15+r9]
0x5acbd13  mov [rax+r9-0x3C],r10
0x5acbd18  movups [rax+r9-0x34],xmm0
0x5acbd1e  mov r10,[r15+r9+0x10]
0x5acbd23  test r10,r10
0x5acbd26  je 0x5ACBC90
0x5acbd2c  lock inc dword ptr [r10+8]
0x5acbd31  jmp 0x5ACBC90
0x5acbd36  cmp rax,r15
0x5acbd39  je 0x5ACBDEC
0x5acbd3f  xor r8d,r8d
0x5acbd42  xorps xmm0,xmm0
0x5acbd45  jmp short 0x5ACBDC6
0x5acbd47  nop [rax+rax]
0x5acbd50  lea r9,[rdx+r8]
0x5acbd54  lea r10,[rax+r8]
0x5acbd58  mov r11,[r10+8]
0x5acbd5c  mov [r9+8],r11
0x5acbd60  mov r11,[r10+0x10]
0x5acbd64  mov [r9+0x10],r11
0x5acbd68  mov r11,[r10+0x18]
0x5acbd6c  mov [r9+0x18],r11
0x5acbd70  mov r11d,[r10+0x20]
0x5acbd74  mov [r9+0x20],r11d
0x5acbd78  movss xmm1,[r10+0x24]
0x5acbd7e  movss [r9+0x24],xmm1
0x5acbd84  movss xmm1,[r10+0x28]
0x5acbd8a  movss [r9+0x28],xmm1
0x5acbd90  movss xmm1,[r10+0x2C]
0x5acbd96  movss [r9+0x2C],xmm1
0x5acbd9c  movss xmm1,[r10+0x30]

### 0x5acbda2..0x5acbe1f: Finish the third move loop (floats +0x30, qword +0x34, byte +0x3C, stride, refcount-inc); then 0x5ACBDEC: r8=rsi (new capacity), r9=rdi (new capacity alt) and tail-call 0x5AF0720 — frees the old buffer and publishes the new begin/end/cap into the vector header [I]; register epilogue pops precede the jmp. Then 0x5ACBE06 (alloc returned null after alignment): 0x9BC830(rcx=r14) and jmp back to 0x5ACBAE9. Then 0x5ACBE19 (capacity overflow): call 0x75740 (throw/abort [I]) + int3 padding.
0x5acbda2  movss [r9+0x30],xmm1
0x5acbda8  mov r11,[r10+0x34]
0x5acbdac  mov [r9+0x34],r11
0x5acbdb0  movzx r11d,byte ptr [r10+0x3C]
0x5acbdb5  mov [r9+0x3C],r11b
0x5acbdb9  add r8,0x40
0x5acbdbd  add r10,0x40
0x5acbdc1  cmp r10,r15
0x5acbdc4  je short 0x5ACBDEC
0x5acbdc6  mov r9,[rax+r8]
0x5acbdca  mov [rdx+r8],r9
0x5acbdce  movups [rdx+r8+8],xmm0
0x5acbdd4  mov r9,[rax+r8+0x10]
0x5acbdd9  test r9,r9
0x5acbddc  je 0x5ACBD50
0x5acbde2  lock inc dword ptr [r9+8]
0x5acbde7  jmp 0x5ACBD50
0x5acbdec  mov r8,rsi
0x5acbdef  mov r9,rdi
0x5acbdf2  add rsp,0x20
0x5acbdf6  pop rbx
0x5acbdf7  pop rdi
0x5acbdf8  pop rsi
0x5acbdf9  pop r12
0x5acbdfb  pop r13
0x5acbdfd  pop r14
0x5acbdff  pop r15
0x5acbe01  jmp 0x5AF0720
0x5acbe06  mov rcx,r14
0x5acbe09  mov r14,rax
0x5acbe0c  call 0x9BC830
0x5acbe11  mov rax,r14
0x5acbe14  jmp 0x5ACBAE9
0x5acbe19  call 0x75740
0x5acbe1e  int3
0x5acbe1f  int3




## FUNCTION 6BF7260 — element builder (builds one 0x40-byte flipbook element)
Signature guess [I]: `element64* build(void* src /*rcx in rbx*/, element64* out /*rdx in rsi*/, void* params /*r8*/, void* extra /*r9, saved to [rbp-0x40]*/)` — computes row/uv values from the source object's fields and fills a 0x40-byte element (same layout as the element above: out+0 = pointer, out+8 = object via 0x4DFB570, floats +0x18/+0x1C/+0x20, 16 bytes +0x24, qword +0x34, byte +0x3C).

### 0x6bf7260..0x6bf72f6: Prologue (8 pushes, frame 0x68, rbp=rsp+0x60, saves xmm6, SEH cookie [rbp-0x18]=-2); saves r9 to [rbp-0x40], rsi=rdx (output element), rbx=rcx (source), xmm6=0. If byte [rbx+0x365] == 0: reads dword [r8+0x74] and clamps it to 0..3 (cmp al,4 / cmovb), xmm0 = (float)[rbx+0x354]; xmm6 = dword constant at 0xEEC8060 divided by xmm0, multiplied by the indexed float [r8+rax*4+0x120], plus [rbx+0x348] — a per-row speed/uv-scale computation [I]; then floor of xmm6 into r14d via the cvttss2si + cvttps2dq/cvtdq2ps compare-subtract idiom. Loads [rbx+0x34C] into [rbp-0x38], ecx = that-1, r8d = [rbx+0x350] (count), eax = r14d (kept for the next phase).
0x6bf7260  push rbp
0x6bf7261  push r15
0x6bf7263  push r14
0x6bf7265  push r13
0x6bf7267  push r12
0x6bf7269  push rsi
0x6bf726a  push rdi
0x6bf726b  push rbx
0x6bf726c  sub rsp,0x68
0x6bf7270  lea rbp,[rsp+0x60]
0x6bf7275  movaps [rbp-0x10],xmm6
0x6bf7279  mov qword ptr [rbp-0x18],0xFFFFFFFFFFFFFFFE
0x6bf7281  mov [rbp-0x40],r9
0x6bf7285  mov rsi,rdx
0x6bf7288  mov rbx,rcx
0x6bf728b  xorps xmm6,xmm6
0x6bf728e  cmp byte ptr [rcx+0x365],0
0x6bf7295  jne short 0x6BF72CB
0x6bf7297  mov eax,[r8+0x74]
0x6bf729b  xor ecx,ecx
0x6bf729d  cmp al,4
0x6bf729f  cmovb ecx,eax
0x6bf72a2  cvtsi2ss xmm0,dword ptr [rbx+0x354]
0x6bf72aa  movzx eax,cl
0x6bf72ad  movss xmm6,[0xEEC8060]
0x6bf72b5  divss xmm6,xmm0
0x6bf72b9  mulss xmm6,[r8+rax*4+0x120]
0x6bf72c3  addss xmm6,[rbx+0x348]
0x6bf72cb  cvttss2si r14d,xmm6
0x6bf72d0  cvttps2dq xmm0,xmm6
0x6bf72d4  cvtdq2ps xmm0,xmm0
0x6bf72d7  xor eax,eax
0x6bf72d9  ucomiss xmm0,xmm6
0x6bf72dc  seta al
0x6bf72df  sub r14d,eax
0x6bf72e2  mov eax,[rbx+0x34C]
0x6bf72e8  mov [rbp-0x38],rax
0x6bf72ec  lea ecx,[rax-1]
0x6bf72ef  mov r8d,[rbx+0x350]
0x6bf72f6  mov eax,r14d

### 0x6bf72f9..0x6bf737f: r14d (floored row) % [rbx+0x350] (idiv, remainder in edx) indexes the dword table [rbx] (r9=[rbx]) → r13d; clamped up to ecx ([rbx+0x34C]-1) via cmovl. Same for r14d+1 → edi, clamped. Object pointer: rcx=[rbx+0x80]; rax = rcx if nonnull else the default global 0x129C1210 (cmovne). Zero-initializes a 16-byte refcounted-ptr slot [rbp-0x30] (movaps xmm0=0); rcx=[rax] (object ptr, reads word [rcx+0x10] into ecx if nonnull); rcx=[rax+8] (refcount object: lock inc [rcx+8] then reload, else ecx=0); r12 = &[rbx+0xB0]; stores [rax] into [rbp-0x30]; r15 = old [rbp-0x28]; [rbp-0x28] = rcx; releases the old object r15 with the double release pattern (lock dec [r15+8] → virtual dtor [0xF99FFA0], lock dec [r15+0xC] → virtual dtor via [rax+8] of the vtable).
0x6bf72f9  cdq
0x6bf72fa  idiv r8d
0x6bf72fd  movsxd rax,edx
0x6bf7300  mov r9,[rbx]
0x6bf7303  mov r13d,[r9+rax*4]
0x6bf7307  cmp ecx,r13d
0x6bf730a  cmovl r13d,ecx
0x6bf730e  lea eax,[r14+1]
0x6bf7312  cdq
0x6bf7313  idiv r8d
0x6bf7316  movsxd rax,edx
0x6bf7319  mov edi,[r9+rax*4]
0x6bf731d  cmp ecx,edi
0x6bf731f  cmovl edi,ecx
0x6bf7322  mov rcx,[rbx+0x80]
0x6bf7329  test rcx,rcx
0x6bf732c  lea rax,[0x129C1210]
0x6bf7333  cmovne rax,rcx
0x6bf7337  xorps xmm0,xmm0
0x6bf733a  movaps [rbp-0x30],xmm0
0x6bf733e  mov rcx,[rax]
0x6bf7341  test rcx,rcx
0x6bf7344  je short 0x6BF734A
0x6bf7346  movzx ecx,word ptr [rcx+0x10]
0x6bf734a  mov rcx,[rax+8]
0x6bf734e  test rcx,rcx
0x6bf7351  je short 0x6BF735D
0x6bf7353  lock inc dword ptr [rcx+8]
0x6bf7357  mov rcx,[rax+8]
0x6bf735b  jmp short 0x6BF735F
0x6bf735d  xor ecx,ecx
0x6bf735f  lea r12,[rbx+0xB0]
0x6bf7366  mov rax,[rax]
0x6bf7369  mov [rbp-0x30],rax
0x6bf736d  mov r15,[rbp-0x28]
0x6bf7371  mov [rbp-0x28],rcx
0x6bf7375  test r15,r15
0x6bf7378  je short 0x6BF73A7
0x6bf737a  lock dec dword ptr [r15+8]
0x6bf737f  jne short 0x6BF73A7

### 0x6bf7381..0x6bf740e: Second half of the double release of r15 (virtual dtor via [rax+8] after lock dec [r15+0xC]). Then fills the output element: bl = byte [rbx+0x364]; [rsi] = r12 (&[rbx+0xB0], element field @0); call 0x4DFB570(rcx=rsi+8, rdx=&[rbp-0x30]) — assigns the refcounted object into element+8 [I]; float math: xmm2=(float)r14d (row), xmm0=(float)r13d, xmm1=(float)[rbp-0x38]; xmm6 -= xmm2; xmm0 /= xmm1; if bl==0 then xmm2=xmm0 else xmm2=(float)edi / xmm1; stores [rsi+0x18]=xmm0, [rsi+0x1C]=xmm2, [rsi+0x20]=xmm6; copies 16 bytes from [rbp-0x40] (the saved r9 argument) over [rsi+0x24] and its qword [rax+0x10] into [rsi+0x34]; byte [rsi+0x3C]=0.
0x6bf7381  mov rax,[r15]
0x6bf7384  mov rax,[rax]
0x6bf7387  mov rcx,r15
0x6bf738a  call qword ptr [0xF99FFA0]
0x6bf7390  lock dec dword ptr [r15+0xC]
0x6bf7395  jne short 0x6BF73A7
0x6bf7397  mov rax,[r15]
0x6bf739a  mov rax,[rax+8]
0x6bf739e  mov rcx,r15
0x6bf73a1  call qword ptr [0xF99FFA0]
0x6bf73a7  mov bl,[rbx+0x364]
0x6bf73ad  mov [rsi],r12
0x6bf73b0  lea rcx,[rsi+8]
0x6bf73b4  lea rdx,[rbp-0x30]
0x6bf73b8  call 0x4DFB570
0x6bf73bd  nop
0x6bf73be  cvtsi2ss xmm2,r14d
0x6bf73c3  xorps xmm0,xmm0
0x6bf73c6  cvtsi2ss xmm0,r13d
0x6bf73cb  cvtsi2ss xmm1,dword ptr [rbp-0x38]
0x6bf73d0  subss xmm6,xmm2
0x6bf73d4  divss xmm0,xmm1
0x6bf73d8  test bl,bl
0x6bf73da  jne short 0x6BF73E1
0x6bf73dc  movaps xmm2,xmm0
0x6bf73df  jmp short 0x6BF73EC
0x6bf73e1  xorps xmm2,xmm2
0x6bf73e4  cvtsi2ss xmm2,edi
0x6bf73e8  divss xmm2,xmm1
0x6bf73ec  movss [rsi+0x18],xmm0
0x6bf73f1  movss [rsi+0x1C],xmm2
0x6bf73f6  movss [rsi+0x20],xmm6
0x6bf73fb  mov rax,[rbp-0x40]
0x6bf73ff  movups xmm0,[rax]
0x6bf7402  movups [rsi+0x24],xmm0
0x6bf7406  mov rax,[rax+0x10]
0x6bf740a  mov [rsi+0x34],rax
0x6bf740e  mov byte ptr [rsi+0x3C],0

### 0x6bf7412..0x6bf745e: Loads [rbp-0x28] into rdi and releases it (the object refcount taken in phase 2) with the same double release pattern (lock dec [rdi+8] → virtual dtor, lock dec [rdi+0xC] → virtual dtor via [rax+8]); returns rax=rsi (the built element); restores xmm6 from [rbp-0x10] and epilogue; trailing xchg padding.
0x6bf7412  mov rdi,[rbp-0x28]
0x6bf7416  test rdi,rdi
0x6bf7419  je short 0x6BF7446
0x6bf741b  lock dec dword ptr [rdi+8]
0x6bf741f  jne short 0x6BF7446
0x6bf7421  mov rax,[rdi]
0x6bf7424  mov rax,[rax]
0x6bf7427  mov rcx,rdi
0x6bf742a  call qword ptr [0xF99FFA0]
0x6bf7430  lock dec dword ptr [rdi+0xC]
0x6bf7434  jne short 0x6BF7446
0x6bf7436  mov rax,[rdi]
0x6bf7439  mov rax,[rax+8]
0x6bf743d  mov rcx,rdi
0x6bf7440  call qword ptr [0xF99FFA0]
0x6bf7446  mov rax,rsi
0x6bf7449  movaps xmm6,[rbp-0x10]
0x6bf744d  add rsp,0x68
0x6bf7451  pop rbx
0x6bf7452  pop rdi
0x6bf7453  pop rsi
0x6bf7454  pop r12
0x6bf7456  pop r13
0x6bf7458  pop r14
0x6bf745a  pop r15
0x6bf745c  pop rbp
0x6bf745d  ret
0x6bf745e  xchg ax,ax


## FUNCTION 5ACA680 — producer (BlitFlipbookTexture produce/update; 0x5aca680..0x5acb3a7)
Signature guess [I]: `void produce(void* tex /*rcx in rdi*/, void* ctx /*rdx in rbx*/)` — checks/refreshes the flipbook texture: one-time init guard, pulls source objects, resets three 0x40-byte ring entries, rebuilds the element vector via 0x6BF7260 + 0x5ACB9C0, then packages it via 0x5ACBFE0 + 0x5ACBE20 into the texture's blit slot.

### 0x5aca680..0x5aca733: Prologue (8 pushes + xmm6 save at [rbp+0xE0], frame 0x178, rbp=rsp+0x80, SEH cookie [rbp+0xD8]=-2); rbx=rdx (ctx), rdi=rcx (texture). One-time-init guard on global dword [0x129CFC28] vs TLS state counter ([0x128767C8] index into gs:[0x58] array; counter > state → slow path 0x5ACB291). Then: [rbp-0x18]=0x129CFAF0 (a global descriptor), byte flag [rbp-0x10]=0, zero qword [rbp] (string buffer at rsi=rbp-8), byte [rbp+0x68]=0; call 0x39A7D40(rcx=TLS state, rdx=rsi, r8=&[rbp+0x30]) → bool into [rbp-0x10]; byte [rdi+0x24]=0 (dirty flag clear [I]); r14=0x128C4FD0; call 0xE943178(r14); lock inc qword [0x128C5030]; call 0xE94319C(r14); read [0x128C5038]; if nonnull and byte [rax]==1 → rcx=[0x128C5040], skip to 0x5ACA791.
0x5aca680  push rbp
0x5aca681  push r15
0x5aca683  push r14
0x5aca685  push r13
0x5aca687  push r12
0x5aca689  push rsi
0x5aca68a  push rdi
0x5aca68b  push rbx
0x5aca68c  sub rsp,0x178
0x5aca693  lea rbp,[rsp+0x80]
0x5aca69b  movaps [rbp+0xE0],xmm6
0x5aca6a2  mov qword ptr [rbp+0xD8],0xFFFFFFFFFFFFFFFE
0x5aca6ad  mov rbx,rdx
0x5aca6b0  mov rdi,rcx
0x5aca6b3  mov eax,[0x129CFC28]
0x5aca6b9  mov ecx,[0x128767C8]
0x5aca6bf  mov rdx,gs:[0x58]
0x5aca6c8  mov rcx,[rdx+rcx*8]
0x5aca6cc  cmp eax,[rcx+4]
0x5aca6d2  jg 0x5ACB291
0x5aca6d8  lea rcx,[0x129CFAF0]
0x5aca6df  mov [rbp-0x18],rcx
0x5aca6e3  mov byte ptr [rbp-0x10],0
0x5aca6e7  lea rsi,[rbp-8]
0x5aca6eb  mov qword ptr [rbp],0
0x5aca6f3  mov byte ptr [rbp+0x68],0
0x5aca6f7  lea r8,[rbp+0x30]
0x5aca6fb  mov rdx,rsi
0x5aca6fe  call 0x39A7D40
0x5aca703  mov [rbp-0x10],al
0x5aca706  mov byte ptr [rdi+0x24],0
0x5aca70a  lea r14,[0x128C4FD0]
0x5aca711  mov rcx,r14
0x5aca714  call 0xE943178
0x5aca719  lock inc qword ptr [0x128C5030]
0x5aca721  mov rcx,r14
0x5aca724  call 0xE94319C
0x5aca729  mov rax,[0x128C5038]
0x5aca730  test rax,rax
0x5aca733  je short 0x5ACA75A

### 0x5aca735..0x5aca800: Guard continues: byte [rax]==1 test, rcx=[0x128C5040], null test → 0x5ACA791; lock inc [rcx+8] (refcount++ [I]) and reload both pointers. Path 0x5ACA75A (cache miss): zero-initializes the stack "source view" at [rbp+0x88..0xB0] (qword [rbp+0x88]=0, byte [rbp+0x90]=0, movupd zero → [rbp+0x98], qword [rbp+0xA8]=0) and calls 0x3B2020(0x128C4FD0) to create it [I]. Path 0x5ACA791 (cache hit): fills the same struct: [rbp+0x88]=r14 (0x128C4FD0), byte [rbp+0x90]=1, [rbp+0x98]=rax, [rbp+0xA0]=rcx, [rbp+0xA8]=rdx=[0x128C5048] — a three-pointer cached source view [I]. Then three virtual calls through [rdi+0x168]'s object vtable: [+0x338](rdx=&[rbp+0x70]) producing a value checked at [rbp+0x70]; [+0x538]() returning a pointer; and, if nonnull, [+0x198]().
0x5aca735  cmp byte ptr [rax],1
0x5aca738  jne short 0x5ACA75A
0x5aca73a  mov rcx,[0x128C5040]
0x5aca741  test rcx,rcx
0x5aca744  je short 0x5ACA791
0x5aca746  lock inc dword ptr [rcx+8]
0x5aca74a  mov rax,[0x128C5038]
0x5aca751  mov rcx,[0x128C5040]
0x5aca758  jmp short 0x5ACA793
0x5aca75a  mov qword ptr [rbp+0x88],0
0x5aca765  mov byte ptr [rbp+0x90],0
0x5aca76c  xorpd xmm0,xmm0
0x5aca770  movupd [rbp+0x98],xmm0
0x5aca778  mov qword ptr [rbp+0xA8],0
0x5aca783  lea rcx,[0x128C4FD0]
0x5aca78a  call 0x3B2020
0x5aca78f  jmp short 0x5ACA7BD
0x5aca791  xor ecx,ecx
0x5aca793  mov rdx,[0x128C5048]
0x5aca79a  mov [rbp+0x88],r14
0x5aca7a1  mov byte ptr [rbp+0x90],1
0x5aca7a8  mov [rbp+0x98],rax
0x5aca7af  mov [rbp+0xA0],rcx
0x5aca7b6  mov [rbp+0xA8],rdx
0x5aca7bd  mov rcx,[rdi+0x168]
0x5aca7c4  mov rax,[rcx]
0x5aca7c7  mov rax,[rax+0x338]
0x5aca7ce  lea rdx,[rbp+0x70]
0x5aca7d2  call qword ptr [0xF99FFA0]
0x5aca7d8  nop
0x5aca7d9  mov rcx,[rdi+0x168]
0x5aca7e0  mov rax,[rcx]
0x5aca7e3  mov rax,[rax+0x538]
0x5aca7ea  call qword ptr [0xF99FFA0]
0x5aca7f0  nop
0x5aca7f1  test rax,rax
0x5aca7f4  je short 0x5ACA81E
0x5aca7f6  mov rcx,[rdi+0x168]
0x5aca7fd  mov rax,[rcx]
0x5aca800  mov rax,[rax+0x198]

### 0x5aca807..0x5aca89c: Calls the +0x198 virtual slot; then the completion guard `cmp qword ptr [rbp+0x70],0 / sete cl / or al,cl / je 0x5ACA925` — continue into the main body at 0x5ACA925 when both al (low byte of the virtual result [I]) and cl are zero; otherwise fall into the early-return cleanup at 0x5ACA81E: release the [rbp+0x78] object (double release pattern: lock dec [rdi+8] → virtual dtor, lock dec [rdi+0xC] → virtual dtor), zero 16 bytes into [rbp+0x98], release the [rbp+0xA0] object (double release), and zero qword [rbp+0xA8].
0x5aca807  call qword ptr [0xF99FFA0]
0x5aca80d  nop
0x5aca80e  cmp qword ptr [rbp+0x70],0
0x5aca813  sete cl
0x5aca816  or al,cl
0x5aca818  je 0x5ACA925
0x5aca81e  mov rdi,[rbp+0x78]
0x5aca822  test rdi,rdi
0x5aca825  je short 0x5ACA852
0x5aca827  lock dec dword ptr [rdi+8]
0x5aca82b  jne short 0x5ACA852
0x5aca82d  mov rax,[rdi]
0x5aca830  mov rax,[rax]
0x5aca833  mov rcx,rdi
0x5aca836  call qword ptr [0xF99FFA0]
0x5aca83c  lock dec dword ptr [rdi+0xC]
0x5aca840  jne short 0x5ACA852
0x5aca842  mov rax,[rdi]
0x5aca845  mov rax,[rax+8]
0x5aca849  mov rcx,rdi
0x5aca84c  call qword ptr [0xF99FFA0]
0x5aca852  xorpd xmm0,xmm0
0x5aca856  mov rdi,[rbp+0xA0]
0x5aca85d  movupd [rbp+0x98],xmm0
0x5aca865  test rdi,rdi
0x5aca868  je short 0x5ACA8D7
0x5aca86a  lock dec dword ptr [rdi+8]
0x5aca86e  jne short 0x5ACA895
0x5aca870  mov rax,[rdi]
0x5aca873  mov rax,[rax]
0x5aca876  mov rcx,rdi
0x5aca879  call qword ptr [0xF99FFA0]
0x5aca87f  lock dec dword ptr [rdi+0xC]
0x5aca883  jne short 0x5ACA895
0x5aca885  mov rax,[rdi]
0x5aca888  mov rax,[rax+8]
0x5aca88c  mov rcx,rdi
0x5aca88f  call qword ptr [0xF99FFA0]
0x5aca895  mov rdi,[rbp+0xA0]
0x5aca89c  mov qword ptr [rbp+0xA8],0

### 0x5aca8a7..0x5aca960: Second half of the [rbp+0xA0] release; zero qword [rbp+0xA8]; then: if byte [rbp+0x90]==1 call 0x3B2020(rcx=[rbp+0x88]) (release the created source view [I]); if byte [rbp-0x10]==1 call 0x77A2500(rcx=0x1244FD00, rdx=rsi, r8=[rbp-0x18]+0x60) (descriptor/name log [I]); restore xmm6 from [rbp+0xE0] and ret (pops rbx/rdi/rsi/r12/r13/r14/r15/rbp). Main body 0x5ACA925: rax=[rdi+0x170]; null → 0x5ACAAC4 (the "build list" path); r15=[rax]; null → 0x5ACA81E; one-time-init guard on global [0x128D8FC8] (TLS array via [0x128767C8]; counter > state → 0x5ACB322).
0x5aca8a7  test rdi,rdi
0x5aca8aa  je short 0x5ACA8D7
0x5aca8ac  lock dec dword ptr [rdi+8]
0x5aca8b0  jne short 0x5ACA8D7
0x5aca8b2  mov rax,[rdi]
0x5aca8b5  mov rax,[rax]
0x5aca8b8  mov rcx,rdi
0x5aca8bb  call qword ptr [0xF99FFA0]
0x5aca8c1  lock dec dword ptr [rdi+0xC]
0x5aca8c5  jne short 0x5ACA8D7
0x5aca8c7  mov rax,[rdi]
0x5aca8ca  mov rax,[rax+8]
0x5aca8ce  mov rcx,rdi
0x5aca8d1  call qword ptr [0xF99FFA0]
0x5aca8d7  cmp byte ptr [rbp+0x90],1
0x5aca8de  jne short 0x5ACA8EC
0x5aca8e0  mov rcx,[rbp+0x88]
0x5aca8e7  call 0x3B2020
0x5aca8ec  cmp byte ptr [rbp-0x10],1
0x5aca8f0  jne short 0x5ACA90A
0x5aca8f2  mov r8,[rbp-0x18]
0x5aca8f6  add r8,0x60
0x5aca8fa  lea rcx,[0x1244FD00]
0x5aca901  mov rdx,rsi
0x5aca904  call 0x77A2500
0x5aca909  nop
0x5aca90a  movaps xmm6,[rbp+0xE0]
0x5aca911  add rsp,0x178
0x5aca918  pop rbx
0x5aca919  pop rdi
0x5aca91a  pop rsi
0x5aca91b  pop r12
0x5aca91d  pop r13
0x5aca91f  pop r14
0x5aca921  pop r15
0x5aca923  pop rbp
0x5aca924  ret
0x5aca925  mov rax,[rdi+0x170]
0x5aca92c  test rax,rax
0x5aca92f  je 0x5ACAAC4
0x5aca935  mov r15,[rax]
0x5aca938  test r15,r15
0x5aca93b  je 0x5ACA81E
0x5aca941  mov eax,[0x128D8FC8]
0x5aca947  mov ecx,[0x128767C8]
0x5aca94d  mov rdx,gs:[0x58]
0x5aca956  mov rcx,[rdx+rcx*8]
0x5aca95a  cmp eax,[rcx+4]
0x5aca960  jg 0x5ACB322

### 0x5aca966..0x5aca9fe: Locks the r15 object (lock inc word [r15+0x10]); byte [r15+0x12] bit0 clear → 0x5ACA81E; byte [rdi+0x160]==0 → 0x5ACADE8 (alternate fill path). Else: rax=[rbx+0xB8] must be nonnull and its byte [rax] nonzero, else `mov dword ptr [0],0xDEADC0DE` (debug assert trap [V]); rax=[rbx+0xC8]; rax=[rax+0xE8]; r15=[rax+8] (end ptr), rcx=[rax] (begin ptr); r15-=rcx; zero → 0x5ACA81E (empty); rax=[rax+0x30] stored to [rbp+0x80]; virtual call [+0x538] via [rdi+0x168]; rcx=[rax]; rdx=[rcx+0x278]; rcx=rax; rax=rdx; call [0xF99FFA0] (virtual through the vtable slot).
0x5aca966  lock inc word ptr [r15+0x10]
0x5aca96c  movzx eax,byte ptr [r15+0x12]
0x5aca971  test al,1
0x5aca973  je 0x5ACA81E
0x5aca979  cmp byte ptr [rdi+0x160],0
0x5aca980  je 0x5ACADE8
0x5aca986  mov rax,[rbx+0xB8]
0x5aca98d  test rax,rax
0x5aca990  jne short 0x5ACA99D
0x5aca992  mov dword ptr [0],0xDEADC0DE
0x5aca99d  cmp byte ptr [rax],0
0x5aca9a0  jne short 0x5ACA9AD
0x5aca9a2  mov dword ptr [0],0xDEADC0DE
0x5aca9ad  mov rax,[rbx+0xC8]
0x5aca9b4  mov rax,[rax+0xE8]
0x5aca9bb  mov r15,[rax+8]
0x5aca9bf  mov rcx,[rax]
0x5aca9c2  sub r15,rcx
0x5aca9c5  je 0x5ACA81E
0x5aca9cb  mov rax,[rax+0x30]
0x5aca9cf  mov [rbp+0x80],rax
0x5aca9d6  mov rcx,[rdi+0x168]
0x5aca9dd  mov rax,[rcx]
0x5aca9e0  mov rax,[rax+0x538]
0x5aca9e7  call qword ptr [0xF99FFA0]
0x5aca9ed  nop
0x5aca9ee  mov rcx,[rax]
0x5aca9f1  mov rdx,[rcx+0x278]
0x5aca9f8  mov rcx,rax
0x5aca9fb  mov rax,rdx
0x5aca9fe  call qword ptr [0xF99FFA0]

### 0x5acaa04..0x5acaabe: Dirty-state logic: r13=[rax] (new source object), r12=[rdi+0x198] (previous value); sets r14b = ([rdi+0x190]!=0); or r14b,[rdi+0x1A0] (pending-change flag); cmp r13,r12; store [rdi+0x198]=r13; setne [rdi+0x1A0]; call 0x5ACA3E0 → al; rcx=[rbp+0x80]; if al==0 → 0x5ACAA60 (store and continue); else if r13==r12 (sete al) and rcx==[rdi+0x190] → 0x5ACB288 (skip work); else or r14b,al → zero → 0x5ACB288. Then [rdi+0x190]=rcx; rdx=[rdi+0x170] or default 0x129C1210 (lea+cmovne); call 0x4C74180(rcx=&[rbp+0x30], rdx) (produce/describe [I]); checks: [rbp+0x30] null / [rax+0x18] (r14) null / byte [r14+0x68]!=1 → 0x5ACAEAA; call 0x7E6D0 (dtor of the [rbp+0x30] temp [I]); byte [r14+0x44]==0xFF → skip to 0x5ACAEB3; else call 0x1166E0.
0x5acaa04  nop
0x5acaa05  mov r13,[rax]
0x5acaa08  mov r12,[rdi+0x198]
0x5acaa0f  cmp qword ptr [rdi+0x190],0
0x5acaa17  sets r14b
0x5acaa1b  or r14b,[rdi+0x1A0]
0x5acaa22  cmp r13,r12
0x5acaa25  mov [rdi+0x198],r13
0x5acaa2c  setne [rdi+0x1A0]
0x5acaa33  call 0x5ACA3E0
0x5acaa38  nop
0x5acaa39  test al,al
0x5acaa3b  mov rcx,[rbp+0x80]
0x5acaa42  je short 0x5ACAA60
0x5acaa44  cmp r13,r12
0x5acaa47  sete al
0x5acaa4a  cmp rcx,[rdi+0x190]
0x5acaa51  je 0x5ACB288
0x5acaa57  or r14b,al
0x5acaa5a  je 0x5ACB288
0x5acaa60  mov [rdi+0x190],rcx
0x5acaa67  mov rax,[rdi+0x170]
0x5acaa6e  test rax,rax
0x5acaa71  lea rdx,[0x129C1210]
0x5acaa78  cmovne rdx,rax
0x5acaa7c  lea rcx,[rbp+0x30]
0x5acaa80  call 0x4C74180
0x5acaa85  mov rax,[rbp+0x30]
0x5acaa89  test rax,rax
0x5acaa8c  je 0x5ACAEAA
0x5acaa92  mov r14,[rax+0x18]
0x5acaa96  test r14,r14
0x5acaa99  je 0x5ACAEAA
0x5acaa9f  cmp byte ptr [r14+0x68],1
0x5acaaa4  jne 0x5ACAEAA
0x5acaaaa  lea rcx,[rbp+0x30]
0x5acaaae  call 0x7E6D0
0x5acaab3  cmp byte ptr [r14+0x44],0xFF
0x5acaab8  jne 0x5ACAEB3
0x5acaabe  call 0x1166E0

### 0x5acaac3..0x5acab81: "Build list" path 0x5ACAAC4: constructs a 13-char std::string at [rbp+0xB0] — qword [rbp+0xB8]=0, [rbp+0xC0]=0xD (size), [rbp+0xC8]=0xF (capacity), qword from 0xF593358 → [rbp+0xB0], qword from 0xF59335D → [rbp+0xB5] (overlapping 8-byte stores of a 13-char literal [I]); [rbp-0x38]=&[rbp+0xB0], qword [rbp-0x30]=0xD; call 0x3946B0(rcx=&[rbp+0x30], rdx=&[rbp-0x38]). String free: rax=[rbp+0xC8]; if >=0x10 free [rbp+0xB0] via 0xE935700 with heap-block checks (header rcx-8, size compare 0x20 → invalid → 0x5ACB358). Then r15 = [rbp+0x70] + 0x1A8; call 0xAB6B80(rcx=r15, rdx=&[rbp+0x30]) (map lookup [I]); result == [r15] (map end) → 0x5ACADA0 (not-found path).
0x5acaac3  nop
0x5acaac4  mov qword ptr [rbp+0xB8],0
0x5acaacf  mov qword ptr [rbp+0xC0],0xD
0x5acaada  mov qword ptr [rbp+0xC8],0xF
0x5acaae5  mov rax,[0xF593358]
0x5acaaec  mov [rbp+0xB0],rax
0x5acaaf3  mov rax,[0xF59335D]
0x5acaafa  mov [rbp+0xB5],rax
0x5acab01  lea rax,[rbp+0xB0]
0x5acab08  mov [rbp-0x38],rax
0x5acab0c  mov qword ptr [rbp-0x30],0xD
0x5acab14  lea rcx,[rbp+0x30]
0x5acab18  lea rdx,[rbp-0x38]
0x5acab1c  call 0x3946B0
0x5acab21  nop
0x5acab22  mov rax,[rbp+0xC8]
0x5acab29  cmp rax,0x10
0x5acab2d  jb short 0x5ACAB67
0x5acab2f  mov rcx,[rbp+0xB0]
0x5acab36  lea rdx,[rax+1]
0x5acab3a  cmp rdx,0x1000
0x5acab41  jb short 0x5ACAB62
0x5acab43  mov r8,[rcx-8]
0x5acab47  add rcx,0xFFFFFFFFFFFFFFF8
0x5acab4b  sub rcx,r8
0x5acab4e  cmp rcx,0x20
0x5acab52  jae 0x5ACB358
0x5acab58  add rax,0x28
0x5acab5c  mov rdx,rax
0x5acab5f  mov rcx,r8
0x5acab62  call 0xE935700
0x5acab67  mov r15d,0x1A8
0x5acab6d  add r15,[rbp+0x70]
0x5acab71  lea rdx,[rbp+0x30]
0x5acab75  mov rcx,r15
0x5acab78  call 0xAB6B80
0x5acab7d  nop
0x5acab7e  cmp rax,[r15]
0x5acab81  je 0x5ACADA0

### 0x5acab87..0x5acac40: Lookup hit: r15=[rax]; null → 0x5ACADA0; TLS guard on [0x128D8FC8] (counter > state → 0x5ACB371); lock inc word [r15+0x10]; byte [r15+0x12] bit0 clear → 0x5ACADA0; recompute r15=[rbp+0x70]+0x1A8 and repeat the 0xAB6B80 lookup; if result != [r15] then rax=[rax+0x58] and byte [rax+0x50] must be nonzero (else 0x5ACADA0); call 0x541F8F0(rcx=[rbp+0x70]+0x18, rdx=&[rbp+0xB0] (string), r8=&[rbp+0x30], r9=0, [rsp+0x20]=0, byte [rsp+0x28]=0) — register/apply the entry [I]; then lea rax,[rdi+0x170] compared to r15 (=&[rbp+0xB0]): equal → 0x5ACACD7 (skip swap); else xmm0=16 bytes from [rbp+0xB0], zero xmm6 → [rbp+0xB0] (prepare to move the string [I]).
0x5acab87  mov rax,[rax+0x58]
0x5acab8b  mov r15,[rax]
0x5acab8e  test r15,r15
0x5acab91  je 0x5ACADA0
0x5acab97  mov eax,[0x128D8FC8]
0x5acab9d  mov ecx,[0x128767C8]
0x5acaba3  mov rdx,gs:[0x58]
0x5acabac  mov rcx,[rdx+rcx*8]
0x5acabb0  cmp eax,[rcx+4]
0x5acabb6  jg 0x5ACB371
0x5acabbc  lock inc word ptr [r15+0x10]
0x5acabc2  movzx eax,byte ptr [r15+0x12]
0x5acabc7  test al,1
0x5acabc9  je 0x5ACADA0
0x5acabcf  mov r15d,0x1A8
0x5acabd5  add r15,[rbp+0x70]
0x5acabd9  lea rdx,[rbp+0x30]
0x5acabdd  mov rcx,r15
0x5acabe0  call 0xAB6B80
0x5acabe5  nop
0x5acabe6  cmp rax,[r15]
0x5acabe9  je short 0x5ACABF9
0x5acabeb  mov rax,[rax+0x58]
0x5acabef  cmp byte ptr [rax+0x50],0
0x5acabf3  je 0x5ACADA0
0x5acabf9  mov rcx,[rbp+0x70]
0x5acabfd  add rcx,0x18
0x5acac01  mov byte ptr [rsp+0x28],0
0x5acac06  mov qword ptr [rsp+0x20],0
0x5acac0f  lea r15,[rbp+0xB0]
0x5acac16  lea r8,[rbp+0x30]
0x5acac1a  mov rdx,r15
0x5acac1d  xor r9d,r9d
0x5acac20  call 0x541F8F0
0x5acac25  nop
0x5acac26  lea rax,[rdi+0x170]
0x5acac2d  cmp rax,r15
0x5acac30  je 0x5ACACD7
0x5acac36  movaps xmm0,[rbp+0xB0]
0x5acac3d  xorps xmm6,xmm6
0x5acac40  movaps [rbp+0xB0],xmm6

### 0x5acac47..0x5acacea: String swap: r15=[rdi+0x178] (old object), movups [rdi+0x170],xmm0 (store the 16-byte string/object into rdi+0x170), release old r15 (double release); then 16-byte move [rbp+0xC0]→[rdi+0x180] (xmm0=movapd [rbp+0xC0], zero xmm6 → [rbp+0xC0]), release old [rdi+0x188] (double release); then 0x5ACACD7: r15=[rbp+0xC8], begin releasing it.
0x5acac47  mov r15,[rdi+0x178]
0x5acac4e  movups [rdi+0x170],xmm0
0x5acac55  test r15,r15
0x5acac58  je short 0x5ACAC87
0x5acac5a  lock dec dword ptr [r15+8]
0x5acac5f  jne short 0x5ACAC87
0x5acac61  mov rax,[r15]
0x5acac64  mov rax,[rax]
0x5acac67  mov rcx,r15
0x5acac6a  call qword ptr [0xF99FFA0]
0x5acac70  lock dec dword ptr [r15+0xC]
0x5acac75  jne short 0x5ACAC87
0x5acac77  mov rax,[r15]
0x5acac7a  mov rax,[rax+8]
0x5acac7e  mov rcx,r15
0x5acac81  call qword ptr [0xF99FFA0]
0x5acac87  movapd xmm0,[rbp+0xC0]
0x5acac8f  movaps [rbp+0xC0],xmm6
0x5acac96  mov r15,[rdi+0x188]
0x5acac9d  movupd [rdi+0x180],xmm0
0x5acaca5  test r15,r15
0x5acaca8  je short 0x5ACACD7
0x5acacaa  lock dec dword ptr [r15+8]
0x5acacaf  jne short 0x5ACACD7
0x5acacb1  mov rax,[r15]
0x5acacb4  mov rax,[rax]
0x5acacb7  mov rcx,r15
0x5acacba  call qword ptr [0xF99FFA0]
0x5acacc0  lock dec dword ptr [r15+0xC]
0x5acacc5  jne short 0x5ACACD7
0x5acacc7  mov rax,[r15]
0x5acacca  mov rax,[rax+8]
0x5acacce  mov rcx,r15
0x5acacd1  call qword ptr [0xF99FFA0]
0x5acacd7  mov r15,[rbp+0xC8]
0x5acacde  test r15,r15
0x5acace1  je short 0x5ACAD10
0x5acace3  lock dec dword ptr [r15+8]
0x5acace8  jne short 0x5ACAD10
0x5acacea  mov rax,[r15]

### 0x5acacf3..0x5acad83: Finish the [rbp+0xC8] release (double release), then release [rbp+0xB8] (double release); then the std::string destructor for the temp at [rbp+0x30]: if capacity [rbp+0x50] >= 0x10 free heap buffer [rbp+0x38] via 0xE935700 with the same heap-block checks (invalid → 0x5ACB358).
0x5acacf3  call qword ptr [0xF99FFA0]
0x5acacf9  lock dec dword ptr [r15+0xC]
0x5acacfe  jne short 0x5ACAD10
0x5acad00  mov rax,[r15]
0x5acad03  mov rax,[rax+8]
0x5acad07  mov rcx,r15
0x5acad0a  call qword ptr [0xF99FFA0]
0x5acad10  mov r15,[rbp+0xB8]
0x5acad17  test r15,r15
0x5acad1a  je short 0x5ACAD49
0x5acad1c  lock dec dword ptr [r15+8]
0x5acad21  jne short 0x5ACAD49
0x5acad23  mov rax,[r15]
0x5acad26  mov rax,[rax]
0x5acad29  mov rcx,r15
0x5acad2c  call qword ptr [0xF99FFA0]
0x5acad32  lock dec dword ptr [r15+0xC]
0x5acad37  jne short 0x5ACAD49
0x5acad39  mov rax,[r15]
0x5acad3c  mov rax,[rax+8]
0x5acad40  mov rcx,r15
0x5acad43  call qword ptr [0xF99FFA0]
0x5acad49  mov rax,[rbp+0x50]
0x5acad4d  cmp rax,0x10
0x5acad51  jb short 0x5ACAD88
0x5acad53  mov rcx,[rbp+0x38]
0x5acad57  lea rdx,[rax+1]
0x5acad5b  cmp rdx,0x1000
0x5acad62  jb short 0x5ACAD83
0x5acad64  mov r8,[rcx-8]
0x5acad68  add rcx,0xFFFFFFFFFFFFFFF8
0x5acad6c  sub rcx,r8
0x5acad6f  cmp rcx,0x20
0x5acad73  jae 0x5ACB358
0x5acad79  add rax,0x28
0x5acad7d  mov rdx,rax
0x5acad80  mov rcx,r8
0x5acad83  call 0xE935700

### 0x5acad88..0x5acae2b: After the string cleanup: rax=[rdi+0x170]; nonnull → jmp 0x5ACA935 (next object / loop), else jmp 0x5ACA81E (done). Then 0x5ACADA0 (map-miss path): string dtor for [rbp+0x30] (capacity [rbp+0x50] >= 0x10 → free [rbp+0x38] via 0xE935700 with heap checks, invalid → 0x5ACB358) then jmp 0x5ACA81E. Then 0x5ACADE8 (the byte [rdi+0x160]==0 path): rdx=[rdi+0x170] (via lea rax,[rdi+0x170]; mov rdx,[rax]) or default 0x129C1210 (lea r12 + cmove); call 0x4C74180(rcx=&[rbp+0x30], rdx); checks [rbp+0x30] nonnull / [rax+0x18] (r15) nonnull / byte [r15+0x68]==1 else 0x5ACAE40; call 0x7E6D0; r8=[rbx+0x10]; call 0x5ACB650(rcx=rdi, rdx=r15).
0x5acad88  lea rax,[rdi+0x170]
0x5acad8f  mov rax,[rax]
0x5acad92  test rax,rax
0x5acad95  jne 0x5ACA935
0x5acad9b  jmp 0x5ACA81E
0x5acada0  mov rax,[rbp+0x50]
0x5acada4  cmp rax,0x10
0x5acada8  jb 0x5ACA81E
0x5acadae  mov rcx,[rbp+0x38]
0x5acadb2  lea rdx,[rax+1]
0x5acadb6  cmp rdx,0x1000
0x5acadbd  jb short 0x5ACADDE
0x5acadbf  mov r8,[rcx-8]
0x5acadc3  add rcx,0xFFFFFFFFFFFFFFF8
0x5acadc7  sub rcx,r8
0x5acadca  cmp rcx,0x20
0x5acadce  jae 0x5ACB358
0x5acadd4  add rax,0x28
0x5acadd8  mov rdx,rax
0x5acaddb  mov rcx,r8
0x5acadde  call 0xE935700
0x5acade3  jmp 0x5ACA81E
0x5acade8  lea rax,[rdi+0x170]
0x5acadef  mov rdx,[rax]
0x5acadf2  test rdx,rdx
0x5acadf5  lea r12,[0x129C1210]
0x5acadfc  cmove rdx,r12
0x5acae00  lea rcx,[rbp+0x30]
0x5acae04  call 0x4C74180
0x5acae09  mov rax,[rbp+0x30]
0x5acae0d  test rax,rax
0x5acae10  je short 0x5ACAE40
0x5acae12  mov r15,[rax+0x18]
0x5acae16  test r15,r15
0x5acae19  je short 0x5ACAE40
0x5acae1b  cmp byte ptr [r15+0x68],1
0x5acae20  jne short 0x5ACAE40
0x5acae22  lea rcx,[rbp+0x30]
0x5acae26  call 0x7E6D0
0x5acae2b  mov r8,[rbx+0x10]

### 0x5acae2f..0x5acaee3: Finish 0x5ACB650 call; jmp 0x5ACA986. Then 0x5ACAE40 (no valid object found): call 0x7E6D0 on the [rbp+0x30] temp; [rbp+0x98] must be nonnull and its byte [rax]==1 (else 0x5ACA81E); rcx=[rbp+0xA8]; virtual call [rcx]→[+8] → al; zero → 0x5ACA81E; r12 = [rdi+0x170] or the default (cmovne); rax=[r12+0x10]; store qword [rdi+0x28]=1, [rdi+0x30]=rax, byte [rdi+0x85]=1; jmp 0x5ACA986. Then 0x5ACAEAA: call 0x7E6D0 on [rbp+0x30]. Then 0x5ACAEB3: call 0x10EFE60(rcx=rdi+0x28). Then ring-entry bookkeeping: rax=[rbx+0x18]; byte [rax+0xB8]=1; idx=([rax+0xA0]+[rax+0x98]-1) & ([rax+0x90]-1) with buffer rdx=[rax+0x88]; entry ptr rax=[rdx+rax*8].
0x5acae2f  mov rcx,rdi
0x5acae32  mov rdx,r15
0x5acae35  call 0x5ACB650
0x5acae3a  nop
0x5acae3b  jmp 0x5ACA986
0x5acae40  lea rcx,[rbp+0x30]
0x5acae44  call 0x7E6D0
0x5acae49  mov rax,[rbp+0x98]
0x5acae50  test rax,rax
0x5acae53  je 0x5ACA81E
0x5acae59  cmp byte ptr [rax],1
0x5acae5c  jne 0x5ACA81E
0x5acae62  mov rcx,[rbp+0xA8]
0x5acae69  mov rax,[rcx]
0x5acae6c  mov rax,[rax+8]
0x5acae70  call qword ptr [0xF99FFA0]
0x5acae76  nop
0x5acae77  test al,al
0x5acae79  je 0x5ACA81E
0x5acae7f  mov rax,[rdi+0x170]
0x5acae86  test rax,rax
0x5acae89  cmovne r12,rax
0x5acae8d  mov rax,[r12+0x10]
0x5acae92  mov qword ptr [rdi+0x28],1
0x5acae9a  mov [rdi+0x30],rax
0x5acae9e  mov byte ptr [rdi+0x85],1
0x5acaea5  jmp 0x5ACA986
0x5acaeaa  lea rcx,[rbp+0x30]
0x5acaeae  call 0x7E6D0
0x5acaeb3  lea rcx,[rdi+0x28]
0x5acaeb7  call 0x10EFE60
0x5acaebc  nop
0x5acaebd  mov rax,[rbx+0x18]
0x5acaec1  mov byte ptr [rax+0xB8],1
0x5acaec8  mov rcx,[rax+0xA0]
0x5acaecf  mov rdx,[rax+0x98]
0x5acaed6  add rcx,rdx
0x5acaed9  dec rcx
0x5acaedc  mov rdx,[rax+0x88]
0x5acaee3  mov rax,[rax+0x90]

### 0x5acaee4..0x5acaf98: White-fill of ring-1 entry (0x3F800000 = 1.0f plus zeroed 16-byte spans): dword [rax]=0x3F800000, movupd zero → [rax+4], dword [rax+0x14]=0x3F800000, movupd zero → [rax+0x18], dword [rax+0x28]=0x3F800000, movupd zero → [rax+0x2C], dword [rax+0x3C]=0x3F800000. Then ring-2: rax=[rbx+0x18]; byte [rax+0x78]=1; idx=([rax+0x60]+[rax+0x58]-1) & ([rax+0x50]-1), buffer rdx=[rax+0x48]; same white-fill of the entry. Then ring-3: byte [rax+0x38]=1; idx=([rax+0x20]+[rax+0x18]-1) & ([rax+0x10]-1), buffer rdx=[rax+8]; entry ptr rax=[rdx+rax*8].
0x5acaeea  dec rax
0x5acaeed  and rax,rcx
0x5acaef0  mov rax,[rdx+rax*8]
0x5acaef4  mov dword ptr [rax],0x3F800000
0x5acaefa  xorpd xmm0,xmm0
0x5acaefe  movupd [rax+4],xmm0
0x5acaf03  mov dword ptr [rax+0x14],0x3F800000
0x5acaf0a  movupd [rax+0x18],xmm0
0x5acaf0f  mov dword ptr [rax+0x28],0x3F800000
0x5acaf16  movupd [rax+0x2C],xmm0
0x5acaf1b  mov dword ptr [rax+0x3C],0x3F800000
0x5acaf22  mov rax,[rbx+0x18]
0x5acaf26  mov byte ptr [rax+0x78],1
0x5acaf2a  mov rcx,[rax+0x60]
0x5acaf2e  mov rdx,[rax+0x58]
0x5acaf32  add rcx,rdx
0x5acaf35  dec rcx
0x5acaf38  mov rdx,[rax+0x48]
0x5acaf3c  mov rax,[rax+0x50]
0x5acaf40  dec rax
0x5acaf43  and rax,rcx
0x5acaf46  mov rax,[rdx+rax*8]
0x5acaf4a  mov dword ptr [rax],0x3F800000
0x5acaf50  movupd [rax+4],xmm0
0x5acaf55  mov dword ptr [rax+0x14],0x3F800000
0x5acaf5c  movupd [rax+0x18],xmm0
0x5acaf61  mov dword ptr [rax+0x28],0x3F800000
0x5acaf68  movupd [rax+0x2C],xmm0
0x5acaf6d  mov dword ptr [rax+0x3C],0x3F800000
0x5acaf74  mov rax,[rbx+0x18]
0x5acaf78  mov byte ptr [rax+0x38],1
0x5acaf7c  mov rcx,[rax+0x20]
0x5acaf80  mov rdx,[rax+0x18]
0x5acaf84  add rcx,rdx
0x5acaf87  dec rcx
0x5acaf8a  mov rdx,[rax+8]
0x5acaf8e  mov rax,[rax+0x10]
0x5acaf92  dec rax
0x5acaf95  and rax,rcx
0x5acaf98  mov rax,[rdx+rax*8]

### 0x5acaf9c..0x5acb05a: Ring-3 white-fill completion (dword [rax], [rax+4] zero, [rax+0x14], [rax+0x18] zero, [rax+0x28], [rax+0x2C] zero, [rax+0x3C]). Then float prep: rax=0x3F80000000000000 → [rbp+0xC0] (two 1.0f doubles [I]); xmm1=movsd [rdi+0x30], unpcklps xmm1,xmm0; xmm0=movapd [0xEFC6AF0]; orpd/subpd (abs trick [I]); cvtpd2ps xmm0,xmm1; movupd [rbp+0xB0]; call 0x10EFEF0(rcx=[rbx+0x10], rdx=&[rbp+0xB0]). Then r15 = r15>>3 (sar 3); [rbp+0x98] must be nonnull with byte [rax]==1 (else 0x5ACB06F); [rbp+0x80]=rax; rcx=[rbp+0xA8]; rax=[rcx]; rax=[rax+8]; [rbp+8]=rcx; virtual call → al; zero → 0x5ACB06F; else zero-init [rbp+0x10] (movapd) + qword [rbp+0x20]=0; lea rcx,[rbp+0x10]; rdx=r15.
0x5acaf9c  mov dword ptr [rax],0x3F800000
0x5acafa2  movupd [rax+4],xmm0
0x5acafa7  mov dword ptr [rax+0x14],0x3F800000
0x5acafae  movupd [rax+0x18],xmm0
0x5acafb3  mov dword ptr [rax+0x28],0x3F800000
0x5acafba  movupd [rax+0x2C],xmm0
0x5acafbf  mov dword ptr [rax+0x3C],0x3F800000
0x5acafc6  mov rax,0x3F80000000000000
0x5acafd0  mov [rbp+0xC0],rax
0x5acafd7  movsd xmm1,[rdi+0x30]
0x5acafdc  unpcklps xmm1,xmm0
0x5acafdf  movapd xmm0,[0xEFC6AF0]
0x5acafe7  orpd xmm1,xmm0
0x5acafeb  subpd xmm1,xmm0
0x5acafef  cvtpd2ps xmm0,xmm1
0x5acaff3  movupd [rbp+0xB0],xmm0
0x5acaffb  mov rcx,[rbx+0x10]
0x5acafff  lea rdx,[rbp+0xB0]
0x5acb006  call 0x10EFEF0
0x5acb00b  nop
0x5acb00c  sar r15,3
0x5acb010  mov rax,[rbp+0x98]
0x5acb017  test rax,rax
0x5acb01a  je short 0x5ACB06F
0x5acb01c  cmp byte ptr [rax],1
0x5acb01f  jne short 0x5ACB06F
0x5acb021  mov [rbp+0x80],rax
0x5acb028  mov rcx,[rbp+0xA8]
0x5acb02f  mov rax,[rcx]
0x5acb032  mov rax,[rax+8]
0x5acb036  mov [rbp+8],rcx
0x5acb03a  call qword ptr [0xF99FFA0]
0x5acb040  nop
0x5acb041  test al,al
0x5acb043  je short 0x5ACB06F
0x5acb045  xorpd xmm0,xmm0
0x5acb049  movapd [rbp+0x10],xmm0
0x5acb04e  mov qword ptr [rbp+0x20],0
0x5acb056  lea rcx,[rbp+0x10]
0x5acb05a  mov rdx,r15

### 0x5acb05d..0x5acb0f9: call 0x5ACB800(rcx=&[rbp+0x10], rdx=r15) (construct per-item context [I]); r12=0; rdx=&[rbp+0x30]; jmp 0x5ACB107. Then the alternate path 0x5ACB06F: r13=0, r12=&[rbp+0xB0]; loop 0x5ACB083 while r13<r15 (jae → 0x5ACB288): assert [rbx+0xB8] nonnull and byte [rax]!=0 (DEADC0DE traps); rax=[rbx+0xC8]; rcx=[rax+0xE8]; count=([rcx+8]-[rcx])>>3 (sar rcx,3); r13>=count → continue; rcx=[rax+r13*8]; null → continue; call 0x6BF6F10(rcx=that item, rdx=rbx, r8=rdi+0x170, r9=r12); inc r13 (loop).
0x5acb05d  call 0x5ACB800
0x5acb062  nop
0x5acb063  xor r12d,r12d
0x5acb066  lea rdx,[rbp+0x30]
0x5acb06a  jmp 0x5ACB107
0x5acb06f  xor r13d,r13d
0x5acb072  lea r12,[rbp+0xB0]
0x5acb079  jmp short 0x5ACB083
0x5acb07b  nop [rax+rax]
0x5acb080  inc r13
0x5acb083  cmp r13,r15
0x5acb086  jae 0x5ACB288
0x5acb08c  mov rax,[rbx+0xB8]
0x5acb093  test rax,rax
0x5acb096  je short 0x5ACB0E7
0x5acb098  cmp byte ptr [rax],0
0x5acb09b  jne short 0x5ACB0A8
0x5acb09d  mov dword ptr [0],0xDEADC0DE
0x5acb0a8  mov rax,[rbx+0xC8]
0x5acb0af  mov rcx,[rax+0xE8]
0x5acb0b6  mov rax,[rcx]
0x5acb0b9  mov rcx,[rcx+8]
0x5acb0bd  sub rcx,rax
0x5acb0c0  sar rcx,3
0x5acb0c4  cmp r13,rcx
0x5acb0c7  jae short 0x5ACB080
0x5acb0c9  mov rcx,[rax+r13*8]
0x5acb0cd  test rcx,rcx
0x5acb0d0  je short 0x5ACB080
0x5acb0d2  mov rdx,rbx
0x5acb0d5  lea r8,[rdi+0x170]
0x5acb0dc  mov r9,r12
0x5acb0df  call 0x6BF6F10
0x5acb0e4  nop
0x5acb0e5  jmp short 0x5ACB080
0x5acb0e7  mov dword ptr [0],0xDEADC0DE
0x5acb0f2  cmp byte ptr [rax],0
0x5acb0f5  je short 0x5ACB09D
0x5acb0f7  jmp short 0x5ACB0A8
0x5acb0f9  mov rcx,r14

### 0x5acb10a..0x5acb1a1: Loop body (while r12<r15, jae → 0x5ACB208): asserts on [rbx+0xB8] nonnull and byte [rax]!=0 (DEADC0DE); rax=[rbx+0xC8]; rcx=[rax+0xE8]; count=([rcx+8]-[rcx])>>3; r12>=count → continue; r13=[rax+r12*8]; null → continue; rax=[r13+0x80]; null → continue; r14=[rax]; null → continue; TLS guard on [0x128D8FC8] (counter > state → 0x5ACB1D1); lock inc word [r14+0x10]; byte [r14+0x12] bit0 clear → continue.
0x5acb10a  jae 0x5ACB208
0x5acb110  mov rax,[rbx+0xB8]
0x5acb117  test rax,rax
0x5acb11a  jne short 0x5ACB127
0x5acb11c  mov dword ptr [0],0xDEADC0DE
0x5acb127  cmp byte ptr [rax],0
0x5acb12a  jne short 0x5ACB137
0x5acb12c  mov dword ptr [0],0xDEADC0DE
0x5acb137  mov rax,[rbx+0xC8]
0x5acb13e  mov rcx,[rax+0xE8]
0x5acb145  mov rax,[rcx]
0x5acb148  mov rcx,[rcx+8]
0x5acb14c  sub rcx,rax
0x5acb14f  sar rcx,3
0x5acb153  cmp r12,rcx
0x5acb156  jae short 0x5ACB104
0x5acb158  mov r13,[rax+r12*8]
0x5acb15c  test r13,r13
0x5acb15f  je short 0x5ACB104
0x5acb161  mov rax,[r13+0x80]
0x5acb168  test rax,rax
0x5acb16b  je short 0x5ACB104
0x5acb16d  mov r14,[rax]
0x5acb170  test r14,r14
0x5acb173  je short 0x5ACB104
0x5acb175  mov eax,[0x128D8FC8]
0x5acb17b  mov ecx,[0x128767C8]
0x5acb181  mov r8,gs:[0x58]
0x5acb18a  mov rcx,[r8+rcx*8]
0x5acb18e  cmp eax,[rcx+4]
0x5acb194  jg short 0x5ACB1D1
0x5acb196  lock inc word ptr [r14+0x10]
0x5acb19c  movzx eax,byte ptr [r14+0x12]
0x5acb1a1  test al,1

### 0x5acb1a3..0x5acb24f: Bit0 set → build the element: rcx=r13, r14=rdx, r8=rbx, r9=&[rbp+0xB0]; call 0x6BF7260 (element builder; writes the 0x40-byte element at rdx=&[rbp+0x30] [I]); then call 0x5ACB9C0(rcx=&[rbp+0x10], rdx=r14) (push_back into the element vector [I]); jmp 0x5ACB0F9 (dtor loop head). Then 0x5ACB1D1: TLS one-time-init slow path for [0x128D8FC8] (0xE938CB0; if not 0xFFFFFFFF → 0x5ACB196; else register 0xA771D0 via 0xE935740, re-init 0xE938D70, → 0x5ACB196). Then 0x5ACB208 (loop exit): rdx=[rdi+0x170] (via lea rax,[rdi+0x170]); null → 0x5ACB27F; assert byte [rbp+0x80] != 0 (DEADC0DE); rbx=&[rbp-0x28]; call 0x4C74180(rcx=rbx, rdx); call 0x5ACBFE0(rcx=&[rbp-0x48], rdx=&[rbp+0x10]) (copy the element vector view [I]); call 0x4DFB570(rcx=&[rbp+0x30], rdx=rbx).
0x5acb1a3  je 0x5ACB104
0x5acb1a9  mov rcx,r13
0x5acb1ac  mov r14,rdx
0x5acb1af  mov r8,rbx
0x5acb1b2  lea r9,[rbp+0xB0]
0x5acb1b9  call 0x6BF7260
0x5acb1be  nop
0x5acb1bf  lea rcx,[rbp+0x10]
0x5acb1c3  mov rdx,r14
0x5acb1c6  call 0x5ACB9C0
0x5acb1cb  nop
0x5acb1cc  jmp 0x5ACB0F9
0x5acb1d1  lea rcx,[0x128D8FC8]
0x5acb1d8  call 0xE938CB0
0x5acb1dd  lea rdx,[rbp+0x30]
0x5acb1e1  cmp dword ptr [0x128D8FC8],0xFFFFFFFF
0x5acb1e8  jne short 0x5ACB196
0x5acb1ea  lea rcx,[0xA771D0]
0x5acb1f1  call 0xE935740
0x5acb1f6  lea rcx,[0x128D8FC8]
0x5acb1fd  call 0xE938D70
0x5acb202  lea rdx,[rbp+0x30]
0x5acb206  jmp short 0x5ACB196
0x5acb208  lea rax,[rdi+0x170]
0x5acb20f  mov rdx,[rax]
0x5acb212  test rdx,rdx
0x5acb215  je short 0x5ACB27F
0x5acb217  mov rax,[rbp+0x80]
0x5acb21e  cmp byte ptr [rax],0
0x5acb221  jne short 0x5ACB22E
0x5acb223  mov dword ptr [0],0xDEADC0DE
0x5acb22e  lea rbx,[rbp-0x28]
0x5acb232  mov rcx,rbx
0x5acb235  call 0x4C74180
0x5acb23a  lea rcx,[rbp-0x48]
0x5acb23e  lea rdx,[rbp+0x10]
0x5acb242  call 0x5ACBFE0
0x5acb247  nop
0x5acb248  lea rcx,[rbp+0x30]
0x5acb24c  mov rdx,rbx
0x5acb24f  call 0x4DFB570

### 0x5acb255..0x5acb329: movupd xmm0=[rbp-0x48] (the copied view) → [rbp+0x40]; rdx=&[rbp+0x30]; rcx=[rbp+8]; call 0x5ACBE20 (clone/notify [I]); call 0x7E6D0 on [rbp+0x30] and on [rbp-0x28] (dtors [I]). Then 0x5ACB27F: call 0x5ACC030(rcx=&[rbp+0x10]) (destroy the element vector [I]). Then 0x5ACB288: byte [rdi+0x24]=1; jmp 0x5ACA81E (cleanup & return). Then 0x5ACB291: one-time init for global [0x129CFC28] (0xE938CB0; if != 0xFFFFFFFF → 0x5ACA6D8; else exception record: [rbp+0x88]=0xF56F764, qword [rbp+0x90]=0x19, movupd 0xF2768B0 → [rbp+0xB0], call 0x2FE330(rcx=0x129CFAF0, rdx=&[rbp+0xB0], r8b=1, r9=&[rbp+0x88], [rsp+0x20]=0, [rsp+0x28]=0xF276250); register 0x5AF0710 via 0xE935740; 0xE938D70; jmp 0x5ACA6D8). Then 0x5ACB322: TLS init for [0x128D8FC8] → 0x5ACA966.
0x5acb255  movupd xmm0,[rbp-0x48]
0x5acb25a  movupd [rbp+0x40],xmm0
0x5acb25f  lea rdx,[rbp+0x30]
0x5acb263  mov rcx,[rbp+8]
0x5acb267  call 0x5ACBE20
0x5acb26c  nop
0x5acb26d  lea rcx,[rbp+0x30]
0x5acb271  call 0x7E6D0
0x5acb276  lea rcx,[rbp-0x28]
0x5acb27a  call 0x7E6D0
0x5acb27f  lea rcx,[rbp+0x10]
0x5acb283  call 0x5ACC030
0x5acb288  mov byte ptr [rdi+0x24],1
0x5acb28c  jmp 0x5ACA81E
0x5acb291  lea rcx,[0x129CFC28]
0x5acb298  call 0xE938CB0
0x5acb29d  cmp dword ptr [0x129CFC28],0xFFFFFFFF
0x5acb2a4  jne 0x5ACA6D8
0x5acb2aa  lea rax,[0xF56F764]
0x5acb2b1  mov [rbp+0x88],rax
0x5acb2b8  mov qword ptr [rbp+0x90],0x19
0x5acb2c3  movupd xmm0,[0xF2768B0]
0x5acb2cb  movapd [rbp+0xB0],xmm0
0x5acb2d3  lea rax,[0xF276250]
0x5acb2da  mov [rsp+0x28],rax
0x5acb2df  mov dword ptr [rsp+0x20],0
0x5acb2e7  lea rcx,[0x129CFAF0]
0x5acb2ee  lea rdx,[rbp+0xB0]
0x5acb2f5  lea r9,[rbp+0x88]
0x5acb2fc  mov r8b,1
0x5acb2ff  call 0x2FE330
0x5acb304  nop
0x5acb305  lea rcx,[0x5AF0710]
0x5acb30c  call 0xE935740
0x5acb311  lea rcx,[0x129CFC28]
0x5acb318  call 0xE938D70
0x5acb31d  jmp 0x5ACA6D8
0x5acb322  lea rcx,[0x128D8FC8]
0x5acb329  call 0xE938CB0

### 0x5acb33b..0x5acb3a7: 0x5ACB322 continuation: register 0xA771D0 via 0xE935740, re-init via 0xE938D70, jmp 0x5ACA966. Then 0x5ACB358: invalid-heap-arguments handler: qword [rsp+0x20]=0, zero rcx/rdx/r8/r9, call qword ptr [0xF9A8C78] (_invalid_parameter [I]). Then 0x5ACB371: TLS one-time-init slow path for [0x128D8FC8] (0xE938CB0; if != 0xFFFFFFFF → 0x5ACABBC; else register 0xA771D0 via 0xE935740, 0xE938D70, → 0x5ACABBC); trailing alignment nop.
0x5acb33b  lea rcx,[0xA771D0]
0x5acb342  call 0xE935740
0x5acb347  lea rcx,[0x128D8FC8]
0x5acb34e  call 0xE938D70
0x5acb353  jmp 0x5ACA966
0x5acb358  mov qword ptr [rsp+0x20],0
0x5acb361  xor ecx,ecx
0x5acb363  xor edx,edx
0x5acb365  xor r8d,r8d
0x5acb368  xor r9d,r9d
0x5acb36b  call qword ptr [0xF9A8C78]
0x5acb371  lea rcx,[0x128D8FC8]
0x5acb378  call 0xE938CB0
0x5acb37d  cmp dword ptr [0x128D8FC8],0xFFFFFFFF
0x5acb384  jne 0x5ACABBC
0x5acb38a  lea rcx,[0xA771D0]
0x5acb391  call 0xE935740
0x5acb396  lea rcx,[0x128D8FC8]
0x5acb39d  call 0xE938D70
0x5acb3a2  jmp 0x5ACABBC
0x5acb3a7  nop [rax+rax]

## TOOL REQUESTS



## TOOL REQUESTS
None

<!-- APPEND -->

## ADDENDUM (orchestrator): 8 producer instructions missing from the phases above, added verbatim from effect_blit_producer_5aca680_5acb3a8.txt
```
0x5acacf0  mov rcx,r15
0x5acb0fc  call 0x14C560
0x5acb101  mov rdx,r14
0x5acb104  inc r12
0x5acb107  cmp r12,r15
0x5acb254  nop
0x5acb32e  cmp dword ptr [0x128D8FC8],0xFFFFFFFF
0x5acb335  jne 0x5ACA966
```
