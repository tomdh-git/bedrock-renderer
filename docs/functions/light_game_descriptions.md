# Light/Game/Sky-environment descriptions: producers and pass records for D9a (LightAmbient, LightDirectional, LightPoint), D9c (GameplayMetadata, ServerGraphicsOverrideParameters, EditorHighlightConfiguration), D6c (Clouds, Weather, Atmosphere)

Checklist items D9a (L4u), D9c (L4w), D6c (L4p). Exe 1.26.62.01, RVAs image-relative, static analysis only. Tags: [V] instruction seen in a listing AND re-run with rdis, [I] inference, [?] unknown.
Method: docs/functions/66560f0_sky_cases.md, 6640d80_light_visitor.md (visitor side), this file adds the CLONE/PRODUCER side and the exact pass-vector records. Every instruction block below is copied
from the listings docs/data/listings/lightgame_*.txt (plus light_visitor_6640d80_6645400.txt, light_clone_53599d0_535ce80.txt) and re-checked with `python tools/sigs/verify_oc.py docs/functions/light_game_descriptions.md`.
Typed headers: src/sdk/mc/deps/minecraft_renderer/framebuilder/LightGameDescriptions.h (producer stores + pass records, static_assert offsets, syntax-checked with `cl /std:c++20 /Zs`); read views stay in Descriptions.h, SkyDescriptions.h, LightDescriptions.h.

Listings written for this task (all `dumplist.py` exact): lightgame_clone_53e2c00_53e3743.txt (Atmosphere + LightAmbient clone), lightgame_clone_5370960_5370a99.txt (LightDirectional thin clone), lightgame_dirlight_producer_536aeb0_536b1d0.txt and
lightgame_dirlight_producer2_536c1a0_536c2f0.txt (the two Directional call sites in 0x5369b30), lightgame_point_ctor_668ade0_668b057.txt, lightgame_clouds_clone_53e88a0_53e960c.txt, lightgame_clouds_ctor_668e940_668eb03.txt,
lightgame_weather_clone_5ad5800_5ad5939.txt, lightgame_weather_ctor_668dd20_668e0f6.txt, lightgame_gameplaymeta_clone_53e5910_53e6114.txt, lightgame_serveroverride_producer_6c2e820_6c2f87e.txt, lightgame_serveroverride_copy_67b6300.txt,
lightgame_serveroverride_setcopy_67b7810.txt, lightgame_serveroverride_ctor_a1c40_a1dc1.txt, lightgame_edhighlight_clone_4c8a5b0_4c8a6e9.txt, lightgame_edhighlight_producer_4c88900_4c89881.txt.

## 0. Corrections to earlier docs found on the way [V]
1. LightAmbient: Descriptions.h/progress said the pass element is "qword, float, float, u16" with the u16 = desc +0x14. WRONG: the u16 of the element (+0x10) is the constant 0 (`mov word ptr [rbp+0xBF4],0`, stored 0x6640e24); desc +0x14 goes to a SEPARATE u16 vector (pass+0x8A0). Section 2.1.
2. The pass vector of GameplayMetadata starts at pass+0x498 (the case compares +0x4A0 with +0x4A8: end and cap), not +0x4A0 as in 6640d80/descriptions.md; ServerGraphicsOverrideParameters starts at +0x258 (end +0x260). Sections 3.1, 3.2.
3. ServerGraphicsOverrideParameters is NOT "44 x unordered_set<u16>": 16 of the 44 containers are unordered_map<u16, 3 floats> (k 21..35 and 39), one (k 17) is unordered_map<u16, u32>. Section 3.2.
4. EditorHighlightConfiguration: the visitor-side view "mBlock10[16] + mValue50" decomposes into u32 +0x10 (= 1), vec3 +0x14, f32 +0x20, vec3 +0x24, f32 +0x30, vec4 +0x34, vec4 +0x44, f32 +0x54 (= 1.0f); the pass vector begins at pass+0x78 (end +0x80, cap +0x88). Section 3.3.
5. BGFX_MAP 6ee still lists LightDirectional as tag 1 (right) and "GameplayMetadata ... Light tag 3" (wrong: tag 2, see 6640d80 section 1 and the srcloc below) and ServerGraphicsOverrideParameters clone as "?": it is Light tag 5, producer 0x6c2e820.

## 1. Which function inserts which type (profiler-zone source-location records) [V]
Each insert call site is bracketed by a zone whose record is loaded with `lea rax,[0xF2...]`; the record's second qword points at the __FUNCSIG__ string (read from the exe with tools/sigs/xref.py: `FrameBuilder::insert [TDescription = ...]`):
| Record | Type | Loaded at | Insert call | Tag store | Group slot |
|---|---|---|---|---|---|
| 0xF248E50 | RenderAtmosphereDescription | 0x53e366b (clone 0x53e2c00) | 0x53e32ac | variant {&desc, 0} at 0x53e328a/0x53e3291 | Sky 0x370 (0x53e329b) |
| 0xF248E70 | LightAmbientDescription | 0x53e36f7 (clone 0x53e2c00) | 0x53e352c | 0x53e3503/0x53e3511 (tag 0) | Light 0x380 (0x53e351b) |
| 0xF248F70 | LightDirectionalDescription | 0x5370a51 (thin clone 0x5370960) | 0x53709db slot | 0x53709d4 (tag 1) | Light 0x380 |
| 0xF248DA0 | LightPointDescription | cold stub of 0x53599d0 | 0x535a9ce | 0x535a9b7 (tag 3) | Light 0x380 (0x535a9c1) |
| 0xF248ED0 | gamecomponents::GameplayMetadata | 0x53e60c4 (clone 0x53e5910) | 0x53e5fca | 0x53e5fb4 (tag 2) | Light 0x380 (0x53e5fbf) |
| 0xF2D30F0 | gamecomponents::ServerGraphicsOverrideParameters | 0x6c2f82f (producer 0x6c2e820) | 0x6c2f6f7 | 0x6c2f6dc (tag 5) | Light 0x380 (0x6c2f6e6) |
| 0xF20B440 | gamecomponents::EditorHighlightConfiguration | 0x4c8a6a1 (thin clone 0x4c8a5b0) | 0x4c8a62b slot | 0x4c8a624 (tag 8) | Effect 0x360 |
| 0xF248FB0 | RenderCloudsDescription | 0x53e91ec (clone 0x53e88a0) | 0x53e9174 | 0x53e915d (tag 1) | Sky 0x370 (0x53e9167) |
| 0xF276938 | RenderWeatherDescription | 0x5ad58f1 (thin clone 0x5ad5800) | 0x5ad587b slot | 0x5ad5874 (tag 9) | Sky 0x370 |
Tag bytes and slots (exact instructions):
```
0x53709d0  mov [rbp+0x10],rdi
0x53709d4  mov byte ptr [rbp+0x18],1
0x53709d8  mov rax,[rsi]
0x53709db  mov rax,[rax+0x380]
0x5ad5870  mov [rbp+0x10],rdi
0x5ad5874  mov byte ptr [rbp+0x18],9
0x5ad5878  mov rax,[rsi]
0x5ad587b  mov rax,[rax+0x370]
0x4c8a620  mov [rbp+0x10],rdi
0x4c8a624  mov byte ptr [rbp+0x18],8
0x4c8a628  mov rax,[rsi]
0x4c8a62b  mov rax,[rax+0x360]
```
```
0x53e5fb0  mov [rbp-0x20],r15
0x53e5fb4  mov byte ptr [rbp-0x18],2
0x53e5fb8  mov rcx,[rbp-0x28]
0x53e5fbc  mov rax,[rcx]
0x53e5fbf  mov rax,[rax+0x380]
0x6c2f6d1  lea rax,[rbp-0x50]
0x6c2f6d5  mov [rbp+0xB18],rax
0x6c2f6dc  mov byte ptr [rbp+0xB20],5
0x6c2f6e3  mov rax,[rdi]
0x6c2f6e6  mov rax,[rax+0x380]
0x53e915d  mov byte ptr [rbp+0xC8],1
0x53e9164  mov rax,[r14]
0x53e9167  mov rax,[rax+0x370]
```

## 2. D9a Light descriptions

### 2.1 LightAmbient (Light tag 0)
Visitor case 0x6640de8 (jump table 0xF2BF2B0 entry 0, 0x6640de8 [V], see 6640d80 section 1): reads qword +0x00, float +0x08, float +0x10, u16 +0x14 (+0x0C is not read):
```
0x6640df1  movzx r12d,word ptr [rsi+0x14]
0x6640df6  movss xmm6,[rsi+8]
0x6640dfb  movsd xmm7,[rsi]
0x6640dff  movss xmm0,[rsi+0x10]
0x6640e04  mov [rbp+0xBE0],r12w
0x6640e0c  movsd [rbp+0xBE4],xmm7
0x6640e14  movss [rbp+0xBEC],xmm6
0x6640e1c  movss [rbp+0xBF0],xmm0
0x6640e24  mov word ptr [rbp+0xBF4],0
0x6640e2d  call 0x5ABA5C0
```
Pass effects (rsi = pass): element 0x14 appended to the summary vector pass+0x7F8/+0x800/+0x808 (in-place 0x6640e84..0x6640eb4, grow path through 0x67D5CE0 at 0x6641aa5):
```
0x6640e84  mov rdx,[rsi+0x800]
0x6640e8b  cmp rdx,[rsi+0x808]
0x6640e92  je 0x6641A97
0x6640e98  lea rax,[rbp+0xBF0]
0x6640e9f  movlps [rdx],xmm7
0x6640ea2  movss [rdx+8],xmm6
0x6640ea7  mov ecx,[rax]
0x6640ea9  mov [rdx+0xC],ecx
0x6640eac  movzx eax,word ptr [rax+4]
0x6640eb0  mov [rdx+0x10],ax
0x6640eb4  add qword ptr [rsi+0x800],0x14
0x6640ebc  jmp 0x6641AAB
```
The element is {qword desc+0x00, f32 desc+0x08, dword desc+0x10 (copied from local [rbp+0xBF0]), u16 0 (local [rbp+0xBF4])}: `lea rax,[rbp+0xBF0]; mov ecx,[rax]; mov [rdx+0xC],ecx; movzx eax,word ptr [rax+4]; mov [rdx+0x10],ax`.
Then (0x6641ac7..0x6641b20): the record word [rbp-0x50] = 0x80, the index word [rbp-0x32] = (end - begin)/0x14 - 1 (`shr eax,2; imul eax,0xFFFFCCCD` = /5), and ONE byte is appended to the byte vector pass+0x7C8/+0x7D0/+0x7D8 (no store of a value, `inc rbx; mov [rsi+0x7D0],rbx`):
```
0x6641ac7  mov qword ptr [rbp-0x50],0x80
0x6641acf  mov eax,[rsi+0x800]
0x6641ad5  sub eax,[rsi+0x7F8]
0x6641adb  shr eax,2
0x6641ade  imul eax,0xFFFFCCCD
0x6641ae4  dec eax
0x6641ae6  mov [rbp-0x32],ax
0x6641b02  mov rbx,[rsi+0x7D0]
0x6641b09  cmp rbx,[rsi+0x7D8]
0x6641b10  je 0x6641C4C
0x6641b16  inc rbx
0x6641b19  mov [rsi+0x7D0],rbx
0x6641b20  jmp 0x66432FF
```
Finally (0x6643314..0x66433ab) the record index [rbp-0x2E] = byte-vector index, the u16 `r12w` = desc +0x14 is appended to the u16 vector pass+0x8A0/+0x8A8/+0x8B0, the record is overwritten to 0x281 with the u16 index in [rbp-0x40], and the 0xC8 record goes to the stream pass+0x08 (0x66433cb..0x66433e7):
```
0x6643314  mov eax,[rsi+0x7C8]
0x664331a  not eax
0x664331c  add eax,[rsi+0x7D0]
0x6643322  mov [rbp-0x2E],ax
0x6643342  mov rdx,[rsi+0x8A8]
0x6643349  cmp rdx,[rsi+0x8B0]
0x6643350  je short 0x6643360
0x6643352  mov [rdx],r12w
0x6643356  add qword ptr [rsi+0x8A8],2
0x6643393  mov qword ptr [rbp-0x50],0x281
0x664339b  mov eax,[rsi+0x8A8]
0x66433a1  sub eax,[rsi+0x8A0]
0x66433a7  shr eax,1
0x66433a9  dec eax
0x66433ab  mov [rbp-0x40],ax
0x66433cb  mov rax,[rsi+8]
0x66433cf  cmp rax,[rsi+0x10]
0x66433d3  je short 0x66433F1
0x66433d5  lea rdx,[rbp-0x50]
0x66433d9  mov r8d,0xC8
0x66433df  mov rcx,rax
0x66433e2  call 0xEEC6EC0
0x66433e7  add qword ptr [rsi+8],0xC8
```
Producer: fat clone 0x53e2c00 (size 0xb43; its only caller is 0x5376a00). It builds the ambient colour from the Atmosphere description it just inserted (xmm8 = Atmosphere +0xA4 qword (0x53e32d7), xmm7 = +0xAC (0x53e32dd), xmm6 = +0xB0 (0x53e32e2)), queries vslot 0x218 (result 1 required) and vslot 0x270 (twice) of the global builder to scale (mode == 1: x [obj+0x70], x [obj+0x74]) and stores:
```
0x53e3421  movss xmm0,[r14+0x70]
0x53e3427  movaps xmm1,xmm0
0x53e342a  shufps xmm1,xmm0,0
0x53e342e  mulps xmm8,xmm1
0x53e3432  mulss xmm7,xmm0
0x53e3436  mulss xmm0,[r14+0x74]
0x53e343c  mulss xmm0,xmm6
0x53e3440  jmp short 0x53E3445
0x53e3445  mov rcx,[rbp+0x1B8]
0x53e344c  mov rax,[rbp+0x180]
0x53e3453  test rax,rax
0x53e3456  je short 0x53E3468
0x53e3458  cmp byte ptr [rax],0
0x53e345b  jne short 0x53E3468
0x53e345d  mov dword ptr [0],0xDEADC0DE
0x53e3468  mov rbx,[rbp+0x190]
0x53e346f  movzx eax,byte ptr [rcx+0x74]
0x53e3473  movlps [rbp+0x118],xmm8
0x53e347b  movss [rbp+0x120],xmm7
0x53e3483  movss [rbp+0x124],xmm6
0x53e348b  movss [rbp+0x128],xmm0
0x53e3493  mov [rbp+0x12C],ax
0x53e3503  lea rax,[rbp+0x118]
0x53e350a  mov [rbp+0x130],rax
0x53e3511  mov byte ptr [rbp+0x138],0
0x53e3518  mov rax,[rbx]
0x53e351b  mov rax,[rax+0x380]
0x53e3522  lea rdx,[rbp+0x130]
0x53e3529  mov rcx,rbx
0x53e352c  call qword ptr [0xF99FFA0]
```
=> LightAmbientDescription = {+0x00 vec2 (Atmosphere +0xA4), +0x08 f32 (+0xAC), +0x0C f32 (+0xB0, WRITTEN BUT NEVER READ by the visitor), +0x10 f32 (xmm0 = +0xB0 or the scaled value), +0x14 u16 = byte [[rbp+0x1B8]+0x74]}, extent 0x16, size 0x18 [V: the variant local starts at [rbp+0x130]]. Tag 0, Light slot 0x380 [V]. Typed: LightAmbientProducer in LightGameDescriptions.h.

### 2.2 LightDirectional (Light tag 1)
Visitor case 0x66415b0: first instruction `cmp dword ptr [rdi+0x70],1; jne 0x66447A0` (frame ctx +0x70 must be 1). Reads vec4 +0x00 (movups 0x66415cc), byte +0x10, qword +0x14, dword +0x1C, u16 +0x20:
```
0x66415b0  cmp dword ptr [rdi+0x70],1
0x66415b4  jne 0x66447A0
0x66415ba  movss xmm0,[rsi+0x1C]
0x66415bf  movzx eax,word ptr [rsi+0x20]
0x66415c3  movzx ecx,byte ptr [rsi+0x10]
0x66415c7  movsd xmm1,[rsi+0x14]
0x66415cc  movups xmm2,[rsi]
```
It builds a light record in locals (u16 desc+0x20 at [rbp+0xBE0], dword 2 at [rbp+0xBE4], vec4 desc+0x00 at [rbp+0xBEC], byte 1 at [rbp+0xBFC], byte desc+0x10 at [rbp+0xBFD], 0x48-byte element at [rbp+0xC00] = {1.0f, 0 x16 B, [0xEEC8060]=1.0 qword, 0, qword desc+0x14, f32 desc+0x1C, 0 x16 B, 1.0f, byte 0}):
```
0x6641624  mov [rbp+0xBE0],ax
0x664162b  mov dword ptr [rbp+0xBE4],2
0x6641635  movups [rbp+0xBEC],xmm2
0x664163c  mov byte ptr [rbp+0xBFC],1
0x6641643  mov [rbp+0xBFD],cl
0x6641649  mov dword ptr [rbp+0xC00],0x3F800000
0x6641653  movups [rbp+0xC04],xmm6
0x664165a  movlps [rbp+0xC14],xmm3
0x6641661  mov dword ptr [rbp+0xC1C],0
0x664166b  movsd [rbp+0xC20],xmm1
0x6641673  movss [rbp+0xC28],xmm0
0x664167b  movups [rbp+0xC2C],xmm6
0x6641682  mov dword ptr [rbp+0xC3C],0x3F800000
0x664168c  mov byte ptr [rbp+0xC40],0
```
and pushes into FOUR pass vectors:
1. 0x48-byte light records at pass+0x648/+0x650 (`lea rdx,[rbp+0xC00]; lea rcx,[rsi+0x648]; call 0x675FB30`, index = (end-begin)/0x48 - 1 via `imul eax,0xFFFF8E39` into [rbp-0xE], record qword [rbp-0x50] = 0x2000000):
```
0x66416f1  lea rdx,[rbp+0xC00]
0x66416f8  lea rcx,[rsi+0x648]
0x66416ff  call 0x675FB30
0x6641721  mov qword ptr [rbp-0x50],0x2000000
0x6641729  mov eax,[rsi+0x650]
0x664172f  sub eax,[rsi+0x648]
0x6641735  shr eax,3
0x6641738  imul eax,0xFFFF8E39
0x664173e  dec eax
0x6641740  mov [rbp-0xE],ax
```
2. the 0x14 summary vector pass+0x7F8 (shared with Ambient and Point): {qword desc+0x00, f32 desc+0x08, dword desc+0x0C, byte 1, byte desc+0x10} (in-place 0x6641761..0x66417a2, grow via 0x67D5CE0 at 0x66427b6), index word [rbp-0x32]:
```
0x6641761  mov rdx,[rsi+0x800]
0x6641768  cmp rdx,[rsi+0x808]
0x664176f  je 0x66427A8
0x6641775  lea rax,[rbp+0xBF8]
0x664177c  movsd xmm0,[rbp+0xBEC]
0x6641784  movsd [rdx],xmm0
0x6641788  movss xmm0,[rbp+0xBF4]
0x6641790  movss [rdx+8],xmm0
0x6641795  mov ecx,[rax]
0x6641797  mov [rdx+0xC],ecx
0x664179a  movzx eax,word ptr [rax+4]
0x664179e  mov [rdx+0x10],ax
0x66417a2  add qword ptr [rsi+0x800],0x14
0x66427d8  mov eax,[rsi+0x800]
0x66427de  sub eax,[rsi+0x7F8]
0x66427e4  shr eax,2
0x66427e7  imul eax,0xFFFFCCCD
0x66427ed  dec eax
0x66427ef  mov [rbp-0x32],ax
```
3. one byte into pass+0x7E0/+0x7E8/+0x7F0 (0x664280c..0x6642826, record index [rbp-0x30] stored 0x66448d7) and the record qword becomes 0x2000180 (0x66448c1);
4. the dword 2 (`mov eax,[rbp+0xBE4]; mov [rdi],eax`) into the dword vector pass+0x6F0/+0x6F8/+0x700 (index [rbp-0x1C], 0x6644905..0x6644ae0), then the u16 desc+0x20 into pass+0x8A0 (0x6644b11..0x6644b36), record qword 0x2040181 with u16 index [rbp-0x40], appended to the stream:
```
0x66448c1  mov qword ptr [rbp-0x50],0x2000180
0x66448c9  mov eax,[rsi+0x7E0]
0x66448cf  not eax
0x66448d1  add eax,[rsi+0x7E8]
0x66448d7  mov [rbp-0x30],ax
0x6644905  mov eax,[rbp+0xBE4]
0x664490b  mov [rdi],eax
0x664490d  add qword ptr [rsi+0x6F8],4
0x6644acf  mov eax,[rsi+0x6F8]
0x6644ad5  sub eax,[rsi+0x6F0]
0x6644adb  shr eax,2
0x6644ade  dec eax
0x6644ae0  mov [rbp-0x1C],ax
0x6644b11  movzx eax,word ptr [rbp+0xBE0]
0x6644b18  mov [rdx],ax
0x6644b1b  add qword ptr [rsi+0x8A8],2
0x6644b58  mov qword ptr [rbp-0x50],0x2040181
0x6644b60  mov eax,[rsi+0x8A8]
0x6644b66  sub eax,[rsi+0x8A0]
0x6644b6c  shr eax,1
0x6644b6e  dec eax
0x6644b70  mov [rbp-0x40],ax
```
Producer: the sky/light producer 0x5369b30 (size 0x4b9c, 4033 listed instructions) calls the thin clone 0x5370960 twice (the clone is 0x139 bytes: stores {desc, 1} at [rbp+0x10]/[rbp+0x18] and calls vslot 0x380). Site 1 (0x536b1a1) builds the description from the helper 0x6752A20 output and the first keyframe of a vector returned by an interface call (0x536a8e0..0x536a92f: xmm14 = [e+0], xmm13 = [e+8], xmm6 = [e+0x10], xmm7 = [e+0x14], xmm8 = [e+0x1C], xmm9..12 = [e+0x2C..0x5C]):
```
0x536a8e0  lea rdx,[rbp+0xF0]
0x536a8e7  mov rcx,r14
0x536a8ea  call qword ptr [0xF99FFA0]
0x536a8f0  nop
0x536a8f1  mov rcx,[rbp+0xF0]
0x536a8f8  cmp [rbp+0xF8],rcx
0x536a8ff  je 0x536E574
0x536a905  movsd xmm14,[rcx]
0x536a90a  movss xmm13,[rcx+8]
0x536a910  movss xmm6,[rcx+0x10]
0x536a915  movq xmm7,[rcx+0x14]
0x536a91a  movss xmm8,[rcx+0x1C]
0x536a920  movups xmm9,[rcx+0x2C]
```
```
0x536b0bf  lea rcx,[rbp+0x248]
0x536b0c6  lea rdx,[rbp+0x290]
0x536b0cd  lea r8,[rbp+0xF0]
0x536b0d4  call 0x6752A20
0x536b0d9  nop
0x536b0da  movss xmm6,[rbp+0x284]
0x536b0e2  movsd xmm14,[rbp+0x274]
0x536b154  mov rax,[rbp+0x2E0]
0x536b15b  movzx eax,byte ptr [rax+0x74]
0x536b15f  movlps [rbp+0xF0],xmm14
0x536b167  movss [rbp+0xF8],xmm13
0x536b170  movss [rbp+0xFC],xmm6
0x536b178  mov byte ptr [rbp+0x100],0
0x536b17f  movq [rbp+0x104],xmm7
0x536b187  movss [rbp+0x10C],xmm8
0x536b190  mov [rbp+0x110],ax
0x536b197  lea rdx,[rbp+0xF0]
0x536b19e  mov rcx,rbx
0x536b1a1  call 0x5370960
```
Site 2 (0x536c2cc) is the second light (moon): vec2 xmm13 / f32 xmm8 / f32 xmm6 are blends of the two keyframes (0x536c1c0..0x536c241), `sete [rbp+0x100]` = ([rbp+0x288]==0), +0x14 qword and +0x1C f32 come straight from [r15+0x14]/[r15+0x1C]:
```
0x536c269  cmp dword ptr [rbp+0x288],0
0x536c270  mov rcx,[rbp+0xD0]
0x536c277  movss xmm0,[r15+0x1C]
0x536c27d  mov rax,[rbp+0x2E0]
0x536c284  movzx eax,byte ptr [rax+0x74]
0x536c288  movlps [rbp+0xF0],xmm13
0x536c290  movss [rbp+0xF8],xmm8
0x536c299  movss [rbp+0xFC],xmm6
0x536c2a1  sete [rbp+0x100]
0x536c2a8  movq xmm1,[r15+0x14]
0x536c2ae  movq [rbp+0x104],xmm1
0x536c2b6  movss [rbp+0x10C],xmm0
0x536c2be  mov [rbp+0x110],ax
0x536c2c5  lea rdx,[rbp+0xF0]
0x536c2cc  call 0x5370960
```
=> LightDirectionalDescription size 0x24 (extent 0x22, align 4) [V both sites]; byte +0x10 is 0 for the first light and the "is-first-keyframe" flag for the second [I]. Typed: LightDirectionalProducer.

### 2.3 LightPoint (Light tag 3)
Visitor case 0x66410a0 reads float +0x00, qword +0x08, float +0x10, qword +0x14, float +0x1C, byte +0x20, qword +0x28, u16 +0x30, SIX {weak_ptr pair, vec4} slices at +0x38 + 0x20*k (the case does `lock inc dword ptr [rdx+0xC]` = WEAK count) and qword +0xF8, float +0x100:
```
0x66410a0  movsd xmm0,[rsi+0x14]
0x66410a5  movsd xmm3,[rsi+0xF8]
0x66410de  movzx eax,word ptr [rsi+0x30]
0x66410e2  mov rcx,[rsi+0x28]
0x66410e6  mov [rbp+0xB10],rcx
0x66410ed  movups [rbp+0xB18],xmm4
0x66410f4  mov rdx,[rsi+0x40]
0x66410f8  test rdx,rdx
0x66410fb  je short 0x6641113
0x66410fd  mov r8,[rsi+0x38]
0x6641101  mov [rbp+0xB18],r8
0x6641108  mov [rbp+0xB20],rdx
0x664110f  lock inc dword ptr [rdx+0xC]
0x6641113  mulss xmm2,xmm0
0x6641117  movups xmm5,[rsi+0x48]
0x664111b  movups [rbp+0xB28],xmm5
0x6641122  movups [rbp+0xB38],xmm4
0x6641129  mov rdx,[rsi+0x60]
0x664112d  test rdx,rdx
0x6641130  je short 0x6641148
0x6641132  mov r8,[rsi+0x58]
0x6641136  mov [rbp+0xB38],r8
0x664113d  mov [rbp+0xB40],rdx
0x6641144  lock inc dword ptr [rdx+0xC]
0x6641148  addps xmm1,xmm3
0x664125f  lock inc dword ptr [r8+0xC]
0x6641264  movups xmm3,[rbp+0xBB8]
0x664126b  movups xmm4,[rsi+0xE8]
0x6641272  movups [rbp+0xBC8],xmm4
0x6641279  movss xmm4,[rsi+0x10]
0x664127e  movss xmm5,[rsi]
0x6641282  movzx r8d,byte ptr [rsi+0x20]
```
It pushes: a 0x48 light record from locals [rbp+0x98..] (`lea rdx,[rbp+0x98]; lea rcx,[rsi+0x648]; call 0x675FB30` -> same vector as Directional), a summary element into pass+0x7F8 {f32 desc+8, f32 desc+0xC, f32 desc+0x10, dword desc+0x00, u16 = byte desc+0x20}, a 0xC8 SHADOW-CUBE element into pass+0x7B0/+0x7B8/+0x7C0 and the u16 desc+0x30 into pass+0x8A0:
```
0x6641453  lea rdx,[rbp+0x98]
0x664145a  lea rcx,[rsi+0x648]
0x6641461  call 0x675FB30
0x66414dd  lea rax,[rbp+0x8C]
0x66414e4  movss xmm0,[rbp+0x80]
0x66414ec  movss [rdx],xmm0
0x66414f0  movss xmm0,[rbp+0x84]
0x66414f8  movss [rdx+4],xmm0
0x66414fd  movss xmm0,[rbp+0x88]
0x6641505  movss [rdx+8],xmm0
0x664150a  mov ecx,[rax]
0x664150c  mov [rdx+0xC],ecx
0x664150f  movzx eax,word ptr [rax+4]
0x6641513  mov [rdx+0x10],ax
0x6641517  add qword ptr [rsi+0x800],0x14
```
Shadow-cube element (stride 0xC8, built by moving the staging copy [rbp-0x48..]: qword desc+0x28 then six {ptr, ctrl, vec4}):
```
0x6641ef8  mov rax,[rbp-0x48]
0x6641efc  mov [r12],rax
0x6641f00  xorps xmm0,xmm0
0x6641f03  movups [r12+8],xmm0
0x6641f09  mov rax,[rbp-0x40]
0x6641f0d  mov [r12+8],rax
0x6641f12  mov rax,[rbp-0x38]
0x6641f16  mov [r12+0x10],rax
0x6642016  add qword ptr [rsi+0x7B8],0xC8
0x6644674  mov eax,[rsi+0x7B8]
0x664467a  sub eax,[rsi+0x7B0]
0x6644680  shr eax,3
0x6644683  imul eax,0x5C29
0x6644689  dec eax
0x664468b  mov [rbp+0xC04],ax
```
```
0x66446af  mov rdx,[rsi+0x8A8]
0x66446b6  cmp rdx,[rsi+0x8B0]
0x66446bd  je short 0x66446D0
0x66446bf  movzx eax,word ptr [rbp-0x50]
0x66446c3  mov [rdx],ax
0x66446c6  add qword ptr [rsi+0x8A8],2
0x6644700  mov qword ptr [rbp+0xBE0],0x2000481
0x664470b  mov eax,[rsi+0x8A8]
0x6644711  sub eax,[rsi+0x8A0]
0x6644717  shr eax,1
0x6644719  dec eax
0x664471b  mov [rbp+0xBF0],ax
```
Records: [rbp+0xBE0] = 0x2000000 (0x6641483) with the 0x48-vector index at +0x42 (0x66414a5), the summary index at [rbp+0xBFE], the shadow-cube index at [rbp+0xC04], the final qword 0x2000481 with the u16 index [rbp+0xBF0].
Producer: the Light clone 0x53599d0 loops over the light list `rsi = [rbp+0x2D0] .. [rbp+0x2D8]` with stride 0xF0 (`add rsi,0xF0`), copies the config fields and the six weak_ptr slices into locals and calls the constructor 0x668ADE0:
```
0x535a760  add rsi,0xF0
0x535a767  cmp rsi,r12
0x535a76a  je 0x535AB4B
0x535a8d0  mov rax,[rbp+0x350]
0x535a8d7  mov rcx,[rax+0x418]
0x535a8de  mov rax,[rcx]
0x535a8e1  mov rax,[rax+0x970]
0x535a8e8  call qword ptr [0xF99FFA0]
0x535a8ee  nop
0x535a8ef  movzx r8d,al
0x535a8f3  movzx eax,byte ptr [rsi+4]
0x535a8f7  mov [rbp+0x84],al
0x535a8fd  mov eax,[rsi]
0x535a8ff  mov [rbp+0x80],eax
0x535a905  movups xmm0,[rsi+8]
0x535a909  movups [rbp+0x88],xmm0
0x535a910  movsd xmm0,[rsi+0x18]
0x535a915  movsd [rbp+0x98],xmm0
0x535a91d  movups xmm0,[rsi+0x20]
0x535a921  lea rax,[rbp+0xA0]
0x535a928  movups [rax],xmm0
0x535a92b  lea rax,[rbp+0xB0]
0x535a932  mov [rsp+0x20],rax
0x535a937  lea rcx,[rbp+0xC0]
0x535a93e  lea rdx,[rbp+0x80]
0x535a945  lea r9,[rbp-0x40]
0x535a949  call 0x668ADE0
```
Argument/field map [V]: config e+0 dword -> desc +0x00, e+4 byte -> +0x04, e+8..e+0x1F -> +0x08..+0x1F (six floats), e+0x20 vec4 -> +0x20, r8b = byte from the vcall [[[rbp+0x350]+0x418]+0x970] (0x535a8e8) -> u16 +0x30, slices e+0x30/e+0x38 + vec4 e+0x40 (k = 0), e+0x50.. (k = 1) ... e+0xD0.. (k = 5) (stride 0x20) -> desc +0x38 + 0x20k, three floats {qword [[rbp+0x350]+0x480]+0x101C, f32 +0x1024} -> +0xF8/+0xFC/+0x100. The constructor stores (all instructions):
```
0x668adec  movzx eax,byte ptr [rdx+4]
0x668adf0  mov [rcx+4],al
0x668adf3  mov eax,[rdx]
0x668adf5  mov [rcx],eax
0x668adf7  movss xmm0,[rdx+8]
0x668adfc  movss [rcx+8],xmm0
0x668ae01  movss xmm0,[rdx+0xC]
0x668ae06  movss [rcx+0xC],xmm0
0x668ae0b  movss xmm0,[rdx+0x10]
0x668ae10  movss [rcx+0x10],xmm0
0x668ae15  movss xmm0,[rdx+0x14]
0x668ae1a  movss [rcx+0x14],xmm0
0x668ae1f  movss xmm0,[rdx+0x18]
0x668ae24  movss [rcx+0x18],xmm0
0x668ae29  movss xmm0,[rdx+0x1C]
0x668ae2e  movss [rcx+0x1C],xmm0
0x668ae33  movups xmm0,[rdx+0x20]
0x668ae37  movups [rcx+0x20],xmm0
0x668ae3b  mov [rcx+0x30],r8w
0x668ae47  cmp qword ptr [r9+8],0
0x668ae4c  je short 0x668AE61
0x668ae4e  mov rax,[rdi]
0x668ae51  mov [rsi+0x38],rax
0x668ae55  mov rax,[rdi+8]
0x668ae59  mov [rsi+0x40],rax
0x668ae5d  lock inc dword ptr [rax+0xC]
0x668ae61  movups xmm1,[rdi+0x10]
0x668ae65  movups [rsi+0x48],xmm1
0x668af79  movss xmm0,[rax]
0x668af7d  movss [rsi+0xF8],xmm0
0x668af85  movss xmm0,[rax+4]
0x668af8a  movss [rsi+0xFC],xmm0
0x668af92  movss xmm0,[rax+8]
0x668af97  movss [rsi+0x100],xmm0
```
End 0x104 -> size 0x108 (pointers, align 8) [V]. Typed: LightPointProducer, LightPointShadowCubeElement, LightSummaryElement.

## 3. D9c gamecomponents

### 3.1 GameplayMetadata (Light tag 2)
Producer clone 0x53e5910 (fat, size 0x804, single caller 0x5376a00). It skips the build (jumps to the cleanup 0x53e5ff6) when vslot 0x1C8, 0x4B0 or 0x4B8 of the object [rcx+8] returns true (0x53e594f..0x53e5999 sets bl), when the builder's vslot 8 is false (0x53e5aa3..0x53e5abd) or when `[rdi+0x978]` (the region object) is null (0x53e5ac3..0x53e5acd). The 0x84-byte description is built INLINE at [rbp+0x40] (zero-init, constants, then field stores):
```
0x53e5ad3  xorps xmm0,xmm0
0x53e5ad6  movups [rbp+0x6A],xmm0
0x53e5ada  movaps [rbp+0x60],xmm0
0x53e5ade  movaps [rbp+0x50],xmm0
0x53e5ae2  movaps [rbp+0x40],xmm0
0x53e5ae6  movsd xmm1,[0xF0FD5A0]
0x53e5aee  movsd [rbp+0x7C],xmm1
0x53e5af3  mov dword ptr [rbp+0x84],0x7F7FFFFF
0x53e5afd  movups [rbp+0x88],xmm0
0x53e5b04  movups [rbp+0x98],xmm0
0x53e5b0b  movups [rbp+0xA8],xmm0
0x53e5b12  movups [rbp+0xB4],xmm0
0x53e5b19  mov rcx,[rdi+0x970]
0x53e5b34  movss xmm0,[rsi]
0x53e5b38  movss [rbp+0x7C],xmm0
0x53e5b3d  movss xmm0,[rsi+4]
0x53e5b42  movss [rbp+0x80],xmm0
0x53e5b4a  movss xmm0,[rsi+8]
0x53e5b4f  movss [rbp+0x84],xmm0
0x53e5b57  movzx eax,byte ptr [rsi+0x7D]
0x53e5b5b  mov [rbp+0x78],al
```
Further stores (each is a field of the description; the source is quoted): +0x20 = vcall [[rdi+0x970]+0x420] (0x53e5b31), +0x76/+0x77 from vslot 0x18 of [rdi+0x988] (0x53e5b9d..0x53e5bcb), +0x74 = vslot 0xC8 result (0x53e5be0), +0x24 = |hash| (0x53e5bfe..0x53e5c1e), +0x28 (0x53e5c44), +0x79 (0x53e5c4c), +0x2C = hash & 7 (0x53e5c8c), +0x08 (0x53e5c97), +0x14 (0x53e5d2f), +0x18 (0x53e5d40), then the unit vector and light direction fields:
```
0x53e5c8f  movss xmm0,[rdi+0x5D8]
0x53e5c97  movss [rbp+0x48],xmm0
0x53e5d2f  movss [rbp+0x54],xmm0
0x53e5d34  mov rax,[r13+0xA8]
0x53e5d3b  movss xmm0,[rax+4]
0x53e5d40  movss [rbp+0x58],xmm0
0x53e5d45  movss xmm0,[rdi+0x850]
0x53e5d4d  movaps xmm1,xmm0
0x53e5d50  mulss xmm1,xmm0
0x53e5d54  movss xmm2,[rsi+0xB0]
0x53e5d5c  movsd xmm3,[rdi+0x854]
0x53e5d64  movaps xmm4,xmm3
0x53e5d67  mulps xmm4,xmm3
0x53e5d6a  addss xmm1,xmm4
0x53e5d6e  shufps xmm4,xmm4,0x55
0x53e5d72  addss xmm4,xmm1
0x53e5d76  xorps xmm1,xmm1
0x53e5d79  sqrtss xmm1,xmm4
0x53e5d7d  movss xmm4,[0xEEC8060]
0x53e5d85  divss xmm4,xmm1
0x53e5d89  mulss xmm0,xmm4
0x53e5d8d  unpcklps xmm4,xmm4
0x53e5d90  mulps xmm4,xmm3
0x53e5d93  movss [rbp+0x88],xmm0
0x53e5d9b  movhps xmm4,[rsi+0xA8]
0x53e5da2  movups [rbp+0x8C],xmm4
0x53e5da9  movss [rbp+0x9C],xmm2
0x53e5db1  mov rax,[r13+0x20]
0x53e5db5  mov rax,[rax+0x70]
0x53e5db9  mov rax,[rax+0x40]
0x53e5dbd  movss xmm0,[rax+8]
0x53e5dc2  movsd xmm1,[rax]
0x53e5dc6  movsd [rbp+0xA0],xmm1
0x53e5dce  movss [rbp+0xA8],xmm0
```
The flags +0x30 (bits 0..6 from seven floats at [[rdi+0x950]+0x2BC0 + 4k] > 0):
```
0x53e5dee  mov rcx,[rdi+0x950]
0x53e5df5  mov eax,[rbp+0x70]
0x53e5df8  movss xmm1,[rcx+0x2BC0]
0x53e5e00  xorps xmm0,xmm0
0x53e5e03  ucomiss xmm1,xmm0
0x53e5e06  jbe short 0x53E5E0E
0x53e5e08  or eax,1
0x53e5e0b  mov [rbp+0x70],eax
0x53e5e6d  movss xmm0,[rcx+0x2BD8]
0x53e5e75  xorps xmm1,xmm1
0x53e5e78  ucomiss xmm0,xmm1
0x53e5e7b  jbe short 0x53E5E83
0x53e5e7d  or eax,0x40
0x53e5e80  mov [rbp+0x70],eax
0x53e5e83  movss xmm0,[rsi]
```
The world query 0x32D10F0 (block position floor of [rsi..+8], rdx = &[rbp+0x106]) gives two bytes that become the floats +0x0C and +0x00; 0x32DC5A0 gives the u16 at +0x1C ([+0x168] of its result):
```
0x53e5ebe  lea rdx,[rbp+0x106]
0x53e5ec5  lea r8,[rbp-0x20]
0x53e5ec9  mov rcx,rbx
0x53e5ecc  call 0x32D10F0
0x53e5ed1  nop
0x53e5ed2  movzx eax,byte ptr [rbp+0x106]
0x53e5ed9  xorps xmm0,xmm0
0x53e5edc  cvtsi2ss xmm0,eax
0x53e5ee0  movss [rbp+0x4C],xmm0
0x53e5ee5  movzx eax,byte ptr [rbp+0x107]
0x53e5eec  xorps xmm0,xmm0
0x53e5eef  cvtsi2ss xmm0,eax
0x53e5ef3  movss [rbp+0x40],xmm0
0x53e5f33  lea rdx,[rbp-0x20]
0x53e5f37  mov rcx,rbx
0x53e5f3a  call 0x32DC5A0
0x53e5f3f  nop
0x53e5f40  movzx eax,word ptr [rax+0x168]
0x53e5f47  mov [rbp+0x5C],eax
```
Insert: variant {&[rbp+0x40], 2} (0x53e5fb0/0x53e5fb4), Light vslot 0x380 (0x53e5fbf..0x53e5fca). A virtual call at 0x53e5de7 (`[[r14]+8](r14, &desc)`) runs after the inline stores and may write more fields [?]. Size 0x84 [V: visitor copies exactly 0x84 bytes, 0x664109b..; producer stores end at +0x83].
Visitor case 0x6640f1b (tag 2) copies +0x00..+0x39 as four 16-byte rows (0x00, 0x10, 0x20, 0x2A overlapping) and dwords +0x3C..+0x80 each into the vector begin pass+0x498 / end +0x4A0 / cap +0x4A8 (stride 0x84), record qword 0x80000000000, index word [rbp+0x16]:
```
0x6640f78  mov r12,[rdi+0x4A0]
0x6640f7f  cmp r12,[rdi+0x4A8]
0x6640f86  je 0x66419D3
0x6640f8c  movups xmm0,[rsi]
0x6640f8c  movups xmm0,[rsi]
0x6640f8f  movups xmm1,[rsi+0x10]
0x6640f93  movups xmm2,[rsi+0x20]
0x6640f97  movups xmm3,[rsi+0x2A]
0x6640f9b  movups [r12+0x2A],xmm3
0x6640fa1  movups [r12+0x20],xmm2
0x6640fa7  movups [r12+0x10],xmm1
0x6640fad  movups [r12],xmm0
0x6640fb2  movss xmm0,[rsi+0x3C]
0x6641090  add qword ptr [rdi+0x4A0],0x84
0x664318a  mov rax,0x80000000000
0x6643194  mov [rbp-0x50],rax
0x6643198  mov eax,[rdi+0x4A0]
0x664319e  sub eax,[rdi+0x498]
0x66431a4  shr eax,2
0x66431a7  imul eax,0xFFFF83E1
0x66431ad  dec eax
0x66431af  mov [rbp+0x16],ax
```
Field meanings: the world-light queries (+0x00/+0x0C bytes from 0x32D10F0 = block light / sky light of the camera block [I]), the dimension/biome id (+0x1C) and the seven feature flags (+0x30) are visible, but the consumer (lighting pass) is not located, so names stay [I]/[?]. Typed: GameplayMetadataProducer.

### 3.2 ServerGraphicsOverrideParameters (Light tag 5)
Producer 0x6c2e820 (size 0x105e, the object it builds lives in locals; rcx = rdi = the server override config, r8 = rsi = the block registry, xmm1 = a float). The description is 44 local containers [rbp-0x50 + 0x40*k]. Container constructors: 0xA1C40 (empty hash container, args {0.0f}) for k 0..16, 18..20, 36..38, 40..43 and 0x433020 for k 21..35 and 39; k 17 (rbp+0x3F0) is initialised inline:
```
0x6c2e86f  lea rcx,[rbp-0x50]
0x6c2e873  lea rdx,[rbp+0xB18]
0x6c2e87a  call 0xA1C40
0x6c2ea56  mov dword ptr [rbp+0x3F0],0
0x6c2ea60  xorps xmm0,xmm0
0x6c2ea63  movups [rbp+0x3F8],xmm0
0x6c2ea6a  mov rcx,[0x1233E1A8]
0x6c2ea71  mov rax,[rcx]
0x6c2ea74  mov rax,[rax+8]
0x6c2ea78  mov edx,0x18
0x6c2ea7d  call qword ptr [0xF99FFA0]
0x6c2ea83  nop
0x6c2ea84  mov rbx,rax
0x6c2ea87  test rax,rax
0x6c2ea8a  je 0x6C2F7B6
0x6c2ea90  mov [rbx],rbx
0x6c2ea93  mov [rbx+8],rbx
0x6c2ea97  mov [rbp+0x3F8],rbx
0x6c2ea9e  xorps xmm0,xmm0
0x6c2eabe  mov qword ptr [rbp+0x428],8
0x6c2eac9  mov dword ptr [rbp+0x3F0],0x3F800000
```
The empty-container constructor 0xA1C40 stores the same shape (+0x00 1.0f, +0x08 list sentinel, +0x18 bucket vector of 0x80 bytes, +0x30 mask 7, +0x38 max index 8):
```
0xa1c5c  mov eax,[rdx]
0xa1c5e  mov [rcx],eax
0xa1c60  xorps xmm6,xmm6
0xa1c63  movups [rcx+8],xmm6
0xa1c8c  lea rax,[rsi+8]
0xa1c90  mov [rbp-0x28],rax
0xa1c94  mov [rdi],rdi
0xa1c97  mov [rdi+8],rdi
0xa1c9b  mov [rsi+8],rdi
0xa1c9f  lea rax,[rsi+0x18]
0xa1ca3  mov [rbp-0x20],rax
0xa1ca7  movups [rsi+0x18],xmm6
0xa1cab  mov qword ptr [rsi+0x28],0
0xa1cb3  mov qword ptr [rsi+0x30],7
0xa1cbb  mov qword ptr [rsi+0x38],8
0xa1cc3  mov dword ptr [rsi],0x3F800000
0xa1d26  mov [rsi+0x18],rbx
0xa1d2a  mov rax,rbx
0xa1d2d  sub rax,0xFFFFFFFFFFFFFF80
0xa1d31  mov [rsi+0x20],rax
0xa1d35  mov [rsi+0x28],rax
```
Fill: converter calls `rcx = rdi + 0x40*s` (source container s of the config object), `rdx = &local k` (destination), r8/r9 = the registry/float. Source index s = k+2 for k 0..16, 18..38 (the config has two extra leading containers), and 40 <- 48, 41 <- 0, 42 <- 50, 43 <- 51 (script over the listing). 0x6C29EA0 serves k 0..7, 40, 42, 43 (11 sites), 0x6C2A130 serves k 8..16, 18..20, 36..38, 41 (16 sites) and 0x6C2A290 serves k 21..35 (15 sites). k 39 (a 0x433020 map) is filled by a separate list loop through 0x6C40160 (0x6c2f3b8, 0x6c2f4d5) that is not decoded [?]. k 17 is filled in a loop over the list of source container 19 (`mov r15,[rdi+0x4C8]` = its list head at +0x08; nodes: byte +0x30, key object at +0x38 passed to 0x5D3F510, value u32 at +0x58): the key resolves through the registry lookup 0x5D3F510, the u16 id is read from [result+0x168] and hashed (FNV-1a over the two key bytes, offset basis 0xCBF29CE484222325, prime 0x100000001B3), then 0x6C3FEA0 inserts and `mov [rax+0x14],r13d` stores the value:
```
0x6c2eea4  lea rdx,[rbp-0x50]
0x6c2eea8  movaps xmm2,xmm6
0x6c2eeab  mov r9,rsi
0x6c2eeae  call 0x6C29EA0
0x6c2ef72  call 0x6C2A130
0x6c2ef77  nop
0x6c2ef78  lea rcx,[rdi+0x2C0]
0x6c2ef7f  lea rdx,[rbp+0x1F0]
0x6c2ef86  mov r8,rsi
0x6c2ef89  call 0x6C2A130
0x6c2f030  mov r15,[rdi+0x4C8]
0x6c2f037  mov r12,[r15]
0x6c2f03a  cmp r12,r15
0x6c2f03d  je 0x6C2F15A
0x6c2f043  lea rbx,[rbp+0xB18]
0x6c2f04a  lea r14,[rbp+0xAF0]
0x6c2f051  jmp short 0x6C2F090
0x6c2f053  nop [rax+rax]
0x6c2f060  mov r13d,[r12+0x58]
0x6c2f065  lea rcx,[rbp+0x3F0]
0x6c2f06c  mov rdx,rbx
0x6c2f06f  mov r8,r14
0x6c2f072  call 0x6C3FEA0
0x6c2f077  nop
0x6c2f078  mov rax,[rbp+0xB18]
0x6c2f07f  mov [rax+0x14],r13d
0x6c2f083  mov r12,[r12]
0x6c2f087  cmp r12,r15
0x6c2f08a  je 0x6C2F15A
0x6c2f090  lea rdx,[r12+0x38]
0x6c2f095  mov rcx,rsi
0x6c2f098  call 0x5D3F510
0x6c2f09d  nop
```
```
0x6c2f0a3  movzx eax,word ptr [rax+0x168]
0x6c2f0aa  mov [rbp+0xAF0],ax
0x6c2f0b9  movzx ecx,ax
0x6c2f0bc  movzx edx,cl
0x6c2f0bf  shr ecx,8
0x6c2f0c2  mov r8,0xBF29CE484222325
0x6c2f0cc  xor rdx,r8
0x6c2f0cf  mov r8,0x100000001B3
0x6c2f0d9  imul rdx,r8
0x6c2f0dd  xor rdx,rcx
0x6c2f0e0  imul rdx,r8
0x6c2f13d  mov r13d,[r12+0x58]
0x6c2f142  lea rcx,[rbp+0x3F0]
0x6c2f149  mov rdx,rbx
0x6c2f14c  mov r8,r14
0x6c2f14f  call 0x6C3FEA0
0x6c2f1b0  call 0x6C2A290
```
Final: the guard `[0x128C5038]`/`[0x128C5048]` (global builder) then the insert with the variant {&[rbp-0x50], 5} through vslot 0x380 (quoted in section 1) and `call 0x67B8030` (destroy the 44 locals, 0x6c2f5d0).
Visitor case 0x66417af: `0x67B6300(rcx = &[rbp-0x50], rdx = desc)` is the COPY constructor (listing lightgame_serveroverride_copy_67b6300.txt, 466 lines): 27 calls of 0x67B7810 (unordered_set<u16>: node 0x18 B = 2 pointers + u16 at +0x10, copied as a qword `mov rax,[r14+0x10]; mov [rdi+0x10],rax`, allocation `mov edx,0x18`), 16 calls of 0x67B7C10 (unordered_map<u16, 3 floats>: node 0x20 B, key u16 +0x10, floats +0x14/+0x18/+0x1C, allocation `mov edx,0x20`) and ONE inline copy (k 17, offsets +0x440..+0x47F: `lea rax,[rdx+0x448]`). Index sets, by script over the listing: 0x67B7810 handles k = 0..16, 18..20, 36..38, 40..43 (27), 0x67B7C10 handles k = 21..35 and 39 (16), k = 17 inline. This agrees with the producer's constructors (0xA1C40 vs 0x433020) [V cross-check]. The last container copy:
```
0x67b6b6a  lea rcx,[rdi+0xAC0]
0x67b6b71  add rsi,0xAC0
0x67b6b78  mov rdx,rsi
0x67b6b7b  call 0x67B7810
```
Then 0x67E90D0 MOVES the 0xB00-byte local into the pass vector (begin pass+0x258, end +0x260, cap +0x268, stride 0xB00: `shr eax,8; imul eax,0xFFFF8BA3` = /11), record qword [rbp+0xBE8] = 8, index word [rbp+0xC76]:
```
0x6641846  mov rbx,[rsi+0x260]
0x664184d  cmp rbx,[rsi+0x268]
0x6641854  mov [rbp+0xCBF],al
0x664185a  je 0x6641DBB
0x6641860  lea rdx,[rbp-0x50]
0x6641864  mov rcx,rbx
0x6641867  call 0x67E90D0
0x664186c  nop
0x664186d  add qword ptr [rsi+0x260],0xB00
0x6641878  jmp 0x6642AFC
0x6642b18  mov qword ptr [rbp+0xBE8],8
0x6642b23  mov eax,[rsi+0x260]
0x6642b29  sub eax,[rsi+0x258]
0x6642b2f  shr eax,8
0x6642b32  imul eax,0xFFFF8BA3
0x6642b38  dec eax
0x6642b3a  mov [rbp+0xC76],ax
```
Container members are MSVC std::_Hash: {+0x00 max_load_factor float, +0x08 list head, +0x10 size, +0x18/+0x20/+0x28 bucket vector begin/end/cap, +0x30 mask, +0x38 max idx}; what each of the 44 index slots means (block ids, item ids, ...) is not decoded [?]. Typed: ServerOverrideHashContainer / ServerGraphicsOverrideParametersDesc (size 0xB00 = 44 x 0x40).

### 3.3 EditorHighlightConfiguration (Effect tag 8)
Thin clone 0x4c8a5b0 (size 0x139; tag 8, Effect vslot 0x360, srcloc 0xF20B440; section 1), the single caller is 0x4c88900 at 0x4c89478. The description is built in the local [rbp+0x568]:
```
0x4c89363  movups xmm0,[r12+0x74]
0x4c89369  movaps [rbp+0x470],xmm0
0x4c893b4  mov rdx,[r13]
0x4c893b8  test rdx,rdx
0x4c893bb  cmove rdx,r14
0x4c893bf  lea r12,[rbp+0x480]
0x4c893c6  mov rcx,r12
0x4c893c9  call 0x4C74180
0x4c893ce  nop
0x4c893cf  lea rcx,[rbp+0x568]
0x4c893d6  mov rdx,r12
0x4c893d9  call 0x4DFB570
0x4c893de  nop
0x4c893df  mov dword ptr [rbp+0x578],1
0x4c893e9  mov eax,[rbp+0x638]
0x4c893ef  lea rcx,[rbp+0x57C]
0x4c893f6  mov [rcx+8],eax
0x4c893f9  mov rax,[rbp+0x630]
0x4c89400  mov [rcx],rax
0x4c89403  movss [rbp+0x588],xmm14
0x4c8940c  mov eax,[rbp+0x648]
0x4c89412  mov [rcx+0x18],eax
0x4c89415  mov rax,[rbp+0x640]
0x4c8941c  mov [rcx+0x10],rax
0x4c89420  movss [rbp+0x598],xmm14
0x4c89429  movaps xmm0,[rbp+0x470]
0x4c89430  movups [rcx+0x20],xmm0
0x4c89434  movups [rbp+0x5AC],xmm12
0x4c8943c  mov dword ptr [rbp+0x5BC],0x3F800000
```
Sources: r12 = the highlight settings object taken from the shared-pointer vector `[rbp+0x618] .. [rbp+0x620]` (stride 0x10, element locked with `lock cmpxchg [rcx+8],edx`: 0x4c89102..0x4c89145): vec4 [r12+0x74], vec3 [r12+0x84..0x8F], f32 [r12+0x90]; the shared pair at +0x00 comes from 0x4DFB570 applied to the result of 0x4C74180(&[rbp+0x480], [r13] or r14) (a resource lookup keyed by name, `rdx = [r13]` or fallback r14 = the value returned by the interface call at 0x4c889b7). xmm12 is the constant [0xF20A380] = (0.12, 1.0, 1.0, 0.125) loaded at 0x4c890df.
Visitor case 0x666b316 (jump table 0xF2BF49C) copies the 0x58 bytes verbatim into the vector pass+0x78/+0x80/+0x88 (stride 0x58, `shr eax,3; imul eax,0xFFFF8BA3`), record index word [rbp+0x4AE]:
```
0x666b586  mov rax,[rbx]
0x666b589  mov [r15],rax
0x666b58c  mov rax,[rbx+8]
0x666b590  mov [r15+8],rax
0x666b594  movups xmm0,[rbx+0x10]
0x666b598  movups xmm1,[rbx+0x20]
0x666b59c  movups xmm2,[rbx+0x30]
0x666b5a0  movups xmm3,[rbx+0x40]
0x666b5a4  movups [r15+0x10],xmm0
0x666b5a9  movups [r15+0x20],xmm1
0x666b5ae  movups [r15+0x30],xmm2
0x666b5b3  movups [r15+0x40],xmm3
0x666b5b8  mov rax,[rbx+0x50]
0x666b5bc  mov [r15+0x50],rax
0x666b5c0  add qword ptr [rsi+0x80],0x58
```
```
0x666ce78  mov eax,[rsi+0x80]
0x666ce7e  sub eax,[rsi+0x78]
0x666ce81  shr eax,3
0x666ce84  imul eax,0xFFFF8BA3
0x666ce8a  dec eax
0x666ce8c  mov [rbp+0x4AE],ax
```
Size 0x58 [V both sides]. Typed: EditorHighlightConfigurationProducer.

## 4. D6c Clouds, Weather, Atmosphere: producer side (visitor reads are in 66560f0_sky_cases.md section 9, 67375a0.md, Descriptions.h, SkyDescriptions.h)

### 4.1 Atmosphere (Sky tag 0, fat clone 0x53e2c00)
Prologue: the clone context is {+0x08 render state (rsi), +0x10 (r15), +0x18 settings (r13: +0x68, +0x7D, +0x84, +0x18..+0x57 colour blocks), +0x20 -> object r14}; a guard path tail-jumps to the sky producer 0x5369B30 (0x53e2d39 `jmp 0x5369B30`, taken when the global flag byte is 1 and byte [[rdi+0x18]+0x84] == 1, else it returns at 0x53e2d67).
The 0x138-byte description lives at [rbp-0x38 .. rbp+0x100) (extent verified: last store `movups [rbp+0xF0],xmm0` covers +0x128..+0x137). Defaults first, field overrides after:
```
0x53e2e76  mov eax,[rbp+0x1C4]
0x53e2e7c  mov word ptr [rbp-0x38],0
0x53e2e82  mov [rbp-0x34],eax
0x53e2e85  movsd xmm0,[0xF2470E0]
0x53e2e8d  movsd [rbp-0x30],xmm0
0x53e2e92  mov dword ptr [rbp-0x28],0x43FA0000
0x53e2e99  movups xmm0,[0xF0922E0]
0x53e2ea0  movups [rbp-0x24],xmm0
0x53e2ea4  movups [rbp-0x14],xmm0
0x53e2ea8  movups [rbp-4],xmm0
0x53e2eac  movups [rbp+0xC],xmm0
0x53e2eb0  movups [rbp+0x1C],xmm0
0x53e2eb4  movups [rbp+0x2C],xmm0
0x53e2eb8  movups [rbp+0x3C],xmm0
0x53e2ebc  xorps xmm0,xmm0
0x53e2ebf  movups [rbp+0x4C],xmm0
0x53e2ec3  mov qword ptr [rbp+0x5C],0
0x53e2ecb  mov dword ptr [rbp+0x64],0x3F800000
0x53e2f08  lea r12,[rbp+0x3C]
0x53e2f0c  movaps xmm0,[0xEF40DE0]
0x53e2f13  movups [rbp+0xB0],xmm0
0x53e2f1a  movaps xmm0,[0xF0922E0]
0x53e2f21  movups [rbp+0xC0],xmm0
0x53e2f28  mov dword ptr [rbp+0xD0],0
0x53e2f32  movups xmm0,[0xF0FFAA0]
0x53e2f39  movups [rbp+0xD4],xmm0
0x53e2f40  movsd xmm1,[0xEFD32F0]
0x53e2f48  movsd [rbp+0xE4],xmm1
0x53e2f50  mov dword ptr [rbp+0xEC],0
0x53e2f5a  movups [rbp+0xF0],xmm0
```
Overrides (offset = [rbp+disp+0x38]):
```
0x53e2f9a  mov rax,[rbp+0x1B8]
0x53e2fa1  movzx eax,byte ptr [rax+0x74]
0x53e2fa5  mov [rbp-0x38],ax
0x53e2fa9  movsd xmm0,[rsi+0x45C]
0x53e2fb1  movsd [rbp-0x30],xmm0
0x53e2fb6  movss xmm0,[rsi+0x464]
0x53e2fbe  movss [rbp-0x28],xmm0
0x53e2fc3  movups xmm0,[rsi+0x424]
0x53e2fca  movups [r12],xmm0
0x53e2fcf  movsd xmm0,[rsi+0x434]
0x53e2fd7  movsd xmm1,[rsi+0x5D4]
0x53e2fdf  shufps xmm0,xmm1,0x14
0x53e2fe3  addps xmm0,[0xF2470F0]
0x53e2fea  movups [rbp+0x4C],xmm0
0x53e3006  lea rcx,[rbp-0x24]
0x53e300a  mov rax,[rax+0x1E8]
0x53e3011  movss xmm0,[rax+0x4C]
0x53e3016  movss [rbp+0x5C],xmm0
0x53e301b  mov rdx,[rax+0x58]
0x53e301f  xorps xmm0,xmm0
0x53e3022  cmp byte ptr [rdx+0x100],1
0x53e3029  jne short 0x53E3041
0x53e302b  movss xmm1,[rax+0x34]
0x53e3030  movss xmm2,[rax+0x38]
0x53e3035  subss xmm2,xmm1
0x53e3039  mulss xmm0,xmm2
0x53e303d  addss xmm0,xmm1
0x53e3041  movss [rbp+0x60],xmm0
0x53e3046  movups xmm0,[rsi+0x478]
0x53e304d  movups [rcx],xmm0
0x53e3050  movups xmm0,[rsi+0x468]
0x53e3057  movups [rcx+0x10],xmm0
0x53e305b  movups xmm0,[rsi+0x498]
0x53e3062  movups [rcx+0x20],xmm0
0x53e3066  movups xmm0,[rsi+0x488]
0x53e306d  movups [rcx+0x30],xmm0
0x53e3071  movups xmm0,[rsi+0x4B8]
0x53e3078  movups [rcx+0x40],xmm0
0x53e307c  movups xmm0,[rsi+0x4A8]
0x53e3083  movups [rcx+0x50],xmm0
0x53e3087  movzx eax,byte ptr [rsi+0x96A]
0x53e308e  cmp byte ptr [rsi+0x96B],0
0x53e3095  mov ecx,1
0x53e309a  cmove ecx,eax
0x53e309d  mov [rbp+0x68],cl
0x53e30a0  movsd xmm0,[rsi+0x414]
0x53e30a8  movsd [rbp+0xB8],xmm0
0x53e30b0  mov rax,[r14]
0x53e30b3  mov rax,[rax]
0x53e30b6  lea r15,[rbp-0x38]
0x53e30ba  mov rcx,r14
0x53e30bd  mov rdx,r15
0x53e30c0  mov r8d,ebx
0x53e30c3  call qword ptr [0xF99FFA0]
0x53e30c9  nop
0x53e30ca  cmp byte ptr [rsi+0x96A],0
0x53e30d1  jne short 0x53E30D8
0x53e30d3  xorps xmm0,xmm0
0x53e30d6  jmp short 0x53E30E0
0x53e30d8  movss xmm0,[0xEEC8060]
0x53e30e0  movss [rbp+0x64],xmm0
0x53e30e5  cmp byte ptr [r13+0x68],1
0x53e30ea  jne short 0x53E310A
0x53e30ec  movsd xmm0,[0xF1A5F30]
0x53e30f4  movsd [rbp+0xB0],xmm0
0x53e30fc  movups xmm0,[r13+0x18]
0x53e3101  addps xmm0,xmm0
```
```
0x53e3101  addps xmm0,xmm0
0x53e3104  movups [rbp+0x6C],xmm0
0x53e3108  jmp short 0x53E3167
0x53e310a  cmp dword ptr [rbp+0x1C4],1
0x53e3111  jne short 0x53E3125
0x53e3113  movups xmm0,[r13+0x18]
0x53e3118  mulps xmm0,[0xF247100]
0x53e311f  movups [rbp+0x6C],xmm0
0x53e3123  jmp short 0x53E3167
0x53e3125  lea rax,[rbp+0x6C]
0x53e3129  movsd xmm0,[0xEFD3400]
0x53e3131  movsd [rbp+0xB0],xmm0
0x53e3139  cmp byte ptr [r13+0x7D],1
0x53e313e  jne short 0x53E314A
0x53e3140  movups xmm0,[r13+0x18]
0x53e3145  movups [rax],xmm0
0x53e3148  jmp short 0x53E3167
0x53e314a  movups xmm0,[r13+0x28]
0x53e314f  movups [rax],xmm0
0x53e3152  movups xmm0,[r13+0x38]
0x53e3157  movups [rbp+0x7C],xmm0
0x53e315b  movups xmm0,[r13+0x48]
0x53e3160  movups [rbp+0x8C],xmm0
0x53e3167  mov rbx,[rsi+0x978]
0x53e31f5  movlps [rbp+0xC0],xmm0
```
Then the insert: variant {&desc (r15 = lea [rbp-0x38]), tag 0} stored at [rbp+0x130]/[rbp+0x138], Sky slot 0x370:
```
0x53e328a  mov [rbp+0x130],r15
0x53e3291  mov byte ptr [rbp+0x138],0
0x53e3298  mov rax,[rbx]
0x53e329b  mov rax,[rax+0x370]
0x53e32a2  lea rdx,[rbp+0x130]
0x53e32a9  mov rcx,rbx
0x53e32ac  call qword ptr [0xF99FFA0]
```
Unknown: the virtual call at 0x53e30c3 (`[[r14]+0]` with rdx = &desc, r8d = byte [r13+0x84]) runs between the stores and may fill more of the description [?]. Typed: AtmosphereProducer (0x138, all stored offsets asserted).

### 4.2 Clouds (Sky tag 1, fat clone 0x53e88a0, size 0xd6c)
One description per cloud mesh piece. The clone iterates a square grid (r15d x r15d pieces; the check `(end-begin)/0x260 == grid*grid` at 0x53e8c32..0x53e8c50 uses the inverse of 19 = 0x260/0x20), piece r12 = begin of the vector at [cloud state+0x90] + index*0x260 (0x53e8ea8..0x53e8ec7), builds matrix A in [rbp+0x80..+0xBF] and matrix B in [rbp+0x100..+0x13F] from the camera/world matrix and the cloud offsets, optionally calls 0x1999140 (per-piece byte) and then the constructor 0x668E940:
```
0x53e9045  call 0x1999140
0x53e904a  nop
0x53e904b  mov r15d,eax
0x53e904e  mov rcx,r12
0x53e9051  call 0x4DEF080
0x53e9089  movzx eax,byte ptr [rcx+0x74]
0x53e908d  mov rcx,[rcx+0x20]
0x53e9091  mov rdx,[rbp+0x2A8]
0x53e9098  movzx edx,byte ptr [rdx+0xD4]
0x53e909f  mov [rsp+0x50],ax
0x53e90a4  mov [rsp+0x48],rcx
0x53e90a9  mov rax,[rbp+0x2A0]
0x53e90b0  mov [rsp+0x40],rax
0x53e90b5  mov rax,[rbp+0x298]
0x53e90bc  mov [rsp+0x38],al
0x53e90c0  mov [rsp+0x30],r15b
0x53e90c5  mov [rsp+0x28],dl
0x53e90c9  lea rax,[rbp+0x1E0]
0x53e90d0  mov [rsp+0x20],rax
0x53e90d5  lea rcx,[rbp-0x28]
0x53e90d9  lea rdx,[rbp+0x80]
0x53e90e0  lea r8,[rbp+0x100]
0x53e90e7  mov r9,r12
0x53e90ea  call 0x668E940
```
Constructor 0x668E940 (size 0x1c3, single caller 0x53e88a0) stores EVERY field of the 0xA8-byte description:
```
0x668e965  movss xmm0,[rdx]
0x668e969  movss [rax],xmm0
0x668e96d  movss xmm0,[rdx+4]
0x668e972  movss [rax+4],xmm0
0x668e9fe  movss [rax+0x3C],xmm0
0x668ea03  movss xmm0,[r8]
0x668ea08  movss [rax+0x40],xmm0
0x668eaad  movss [rax+0x7C],xmm0
0x668eab2  mov [rax+0x80],r9
0x668eab9  movups xmm0,[rdi]
0x668eabc  movups [rax+0x88],xmm0
0x668eac3  mov [rax+0x98],sil
0x668eaca  mov [rax+0x99],bl
0x668ead0  mov [rax+0x9A],r11b
0x668ead7  bt r10,0x20
0x668eadc  jb short 0x668EAF1
0x668eade  mov rdx,[rsp+0x68]
0x668eae3  mov rdx,[rdx+0x80]
0x668eaea  mov rdx,[rdx+0x40]
0x668eaee  mov r10d,[rdx]
0x668eaf1  mov [rax+0x9C],r10d
0x668eaf8  mov [rax+0xA0],cx
0x668eaff  pop rbx
0x668eb00  pop rdi
0x668eb01  pop rsi
0x668eb02  ret
```
=> matrices +0x00/+0x40 (16 floats each, from rdx and r8), mesh +0x80 = r9, vec4 +0x88 = the stack argument (cloud state +0xA8), bytes +0x98 (cloud state +0xD4), +0x99 (1 or the 0x1999140 result), +0x9A, u32 +0x9C (override when bit 0x20 of the optional word is set, else the default `[[[arg+0x80]+0x40]]`), u16 +0xA0 (byte [ctx+0x74]); +0x9B and +0xA2.. are never written; size 0xA8 [V: the dest local [rbp-0x28] ends where the next local [rbp+0x80] starts]. Insert: variant {&[rbp-0x28], 1}, Sky slot 0x370 (section 1). Typed: CloudsProducer (same offsets as Descriptions.h RenderCloudsDescription, asserted both ways).

### 4.3 Weather (Sky tag 9, thin clone 0x5ad5800, producer 0x5ad3f70)
The clone is the 0x139-byte thin pass-through (section 1). The producer 0x5ad3f70 (size 0x13f7, 4 callers) builds the description in [rbp-0x28] with the constructor 0x668DD20 (call sites 0x5ad4d54 and 0x5ad4f3a) and inserts it at 0x5ad4d61 / 0x5ad4f47:
```
0x5ad4cf0  mov qword ptr [rbp+0x1D8],3
0x5ad4cfb  lea rcx,[rbp+0x220]
0x5ad4d02  mov [rbp+0x1E0],rcx
0x5ad4d09  mov ecx,[rdi+0x60]
0x5ad4d0c  mov r9,[r14+0x20]
0x5ad4d10  movzx r10d,byte ptr [r14+0x74]
0x5ad4d15  lea r11,[rbp+0x2C8]
0x5ad4d1c  mov [rsp+0x50],r11
0x5ad4d21  mov [rsp+0x48],r10w
0x5ad4d27  mov [rsp+0x40],r9
0x5ad4d2c  mov r9d,[rbp+0x300]
0x5ad4d33  mov [rsp+0x38],r9d
0x5ad4d38  mov [rsp+0x30],ecx
0x5ad4d3c  lea rcx,[rbp+0x1D8]
0x5ad4d43  mov [rsp+0x28],rcx
0x5ad4d48  mov [rsp+0x20],rax
0x5ad4d4d  lea rcx,[rbp-0x28]
0x5ad4d51  mov r9d,esi
0x5ad4d54  call 0x668DD20
0x5ad4d59  nop
0x5ad4d5a  mov rcx,r13
0x5ad4d5d  lea rdx,[rbp-0x28]
0x5ad4d61  call 0x5AD5800
```
Constructor 0x668DD20 (size 0x3d6) stores every field (count check: three texture refs need array count >= 3, else the throw stub `call 0x78ED0` at 0x668e0f0):
```
0x668dd3d  mov [rcx],rdx
0x668dd40  mov [rcx+8],r8d
0x668dd44  mov [rcx+0xC],r9d
0x668dd48  movss xmm0,[rax]
0x668dde7  cmp qword ptr [rdi],0
0x668ddeb  je 0x668E0F0
0x668ddf1  mov rsi,rcx
0x668ddf4  lea rbx,[rcx+0x50]
0x668ddf8  mov rdx,[rdi+8]
0x668ddfc  mov rcx,rbx
0x668ddff  call 0x4DFB570
0x668de04  cmp qword ptr [rdi],1
0x668de08  jbe 0x668E0F0
0x668de0e  mov [rbp-0x10],rbx
0x668de12  lea rbx,[rsi+0x60]
0x668de16  mov rdx,[rdi+8]
0x668de1a  add rdx,0x10
0x668de1e  mov rcx,rbx
0x668de21  call 0x4DFB570
0x668de26  nop
0x668de47  mov rdx,[rbp+0x80]
0x668de4e  movzx eax,word ptr [rbp+0x78]
0x668de52  mov rcx,[rbp+0x70]
0x668de56  mov r8d,[rbp+0x68]
0x668de5a  mov r9d,[rbp+0x60]
0x668de5e  mov [rsi+0x80],r9d
0x668de65  mov [rsi+0x84],r8d
0x668de6c  mov r8,[rcx+0x70]
0x668df40  movss xmm0,[rdx+0x10]
0x668df45  movss [rsi+0xB8],xmm0
0x668df4d  movss xmm0,[rdx+0x14]
0x668df52  movss [rsi+0xBC],xmm0
0x668df5a  movss xmm0,[rdx+0x18]
0x668df5f  movss [rsi+0xC0],xmm0
0x668df67  movss xmm0,[rdx+0x1C]
0x668df6c  movss [rsi+0xC4],xmm0
0x668df74  movss xmm0,[rdx]
0x668e09f  mov rcx,[rcx+0x1B0]
0x668e0a6  mov rcx,[rcx+0x40]
0x668e0aa  movss xmm0,[rcx]
0x668e0ae  movss [rsi+0x118],xmm0
0x668e0b6  movss xmm0,[rcx+4]
0x668e0bb  movss [rsi+0x11C],xmm0
0x668e0c3  movss xmm0,[rcx+8]
0x668e0c8  movss [rsi+0x120],xmm0
0x668e0d0  movss xmm0,[rcx+0xC]
0x668e0d5  movss [rsi+0x124],xmm0
0x668e0dd  mov [rsi+0x128],ax
0x668e0e4  mov rax,rsi
```
Field map: +0x00 mesh (rdx), +0x08 dword (6 * 2 * r12), +0x0C dword, +0x10 16 floats (arg5 pointer), +0x50/+0x60/+0x70 three shared texture refs from the arg6 array, +0x80/+0x84 dwords (args 7, 8), then ten vec4/vec2/float uniform blocks read through pointer chains `[[a9+off]+0x40]` (a9 = the weather parameter object: +0x70 -> +0x88 vec4, +0x78 -> +0x98 vec2, +0x80 -> +0xA0, +0x88 -> +0xA4, +0x190 -> +0xA8, +0x1B8 -> +0xD8, +0x1A8 -> +0xE8, +0x1C0 -> +0xF8, +0x198 -> +0x108, +0x1B0 -> +0x118) and the two direct vec4 +0xB8 ([a11+0x10]) / +0xC8 ([a11+0]), u16 +0x128 (byte [r14+0x74]); size 0x130 [V: last store ends +0x12A, align 8; existing Descriptions.h size agrees]. Typed: WeatherProducer (asserted equal to RenderWeatherDescription offsets +0x80, +0x88, +0x118, +0x128).

## 5. Pass-object vectors written by the Light cases (offsets inside the pass object returned by 0x5ABA5C0)
| Vector | begin / end / cap | element | written by |
|---|---|---|---|
| light records | +0x648 / +0x650 | 0x48 | Directional, Point (0x675FB30) |
| dwords | +0x6F0 / +0x6F8 / +0x700 | 4 | Directional (dword 2) |
| shadow cubes | +0x7B0 / +0x7B8 / +0x7C0 | 0xC8 | Point |
| byte | +0x7C8 / +0x7D0 / +0x7D8 | 1 | Ambient |
| byte | +0x7E0 / +0x7E8 / +0x7F0 | 1 | Directional |
| summary | +0x7F8 / +0x800 / +0x808 | 0x14 | Ambient, Directional, Point |
| u16 | +0x8A0 / +0x8A8 / +0x8B0 | 2 | Ambient (+0x14), Directional (+0x20), Point (+0x30) |
| GameplayMetadata | +0x498 / +0x4A0 / +0x4A8 | 0x84 | tag 2 |
| ServerOverride | +0x258 / +0x260 / +0x268 | 0xB00 | tag 5 |
| EditorHighlight | +0x78 / +0x80 / +0x88 | 0x58 | Effect tag 8 |
Every case then appends one 0xC8 DrawItem record to the stream pass+0x08/+0x10 (`mov r8d,0xC8; call 0xEEC6EC0; add qword ptr [rsi+8],0xC8`, full: `call 0x5ABA6D0`). The record's first qword carries a per-type mask/kind (Ambient 0x281, Directional 0x2040181, Point 0x2000481, GameplayMetadata 0x80000000000, ServerOverride 0x8 at +0x08) and u16 indices into the vectors above at fixed record offsets [V stores quoted above]; the consumers (lighting / environment passes) are not located (same E2 consumer blocker as the other groups).

## 6. Status per checklist item
- D9a Ambient / Directional / Point: visitor reads (6640d80 + this file), producers (clone 0x53e2c00 inline, 0x5369b30 two sites + thin clone 0x5370960, ctor 0x668ADE0 + loop in 0x53599d0), tag bytes, sizes (0x18, 0x24, 0x108), pass records and layout asserts are all covered by quoted listings. Meanings of the fields stay [I] (names unresolved because the lighting-pass consumer is not located).
- D9c GameplayMetadata / ServerGraphicsOverrideParameters / EditorHighlightConfiguration: covered the same way (sizes 0x84, 0xB00, 0x58). Open [?]: the virtual call at 0x53e5de7 may write more GameplayMetadata fields; the 0x6C29EA0/0x6C2A130/0x6C2A290 filler bodies (which registry ids go into which of the 44 containers) are not decoded.
- D6c Clouds / Weather / Atmosphere: clone/producer side covered (tag, group slot, size, constructor args, field sources). Open [?]: the Atmosphere virtual filler at 0x53e30c3; the Weather producer's local sources ([rbp+0x2A0], [rbp+0x2C8], [rbp+0x300]) and Clouds matrix construction arithmetic (0x53e8a57..0x53e8f9d) are summarised, not instruction-decoded.

## 7. Re-verification (rdis, 2026-11)
Result: `python tools/sigs/verify_oc.py docs/functions/light_game_descriptions.md` -> claimed=869 match=869 mismatch=0 no-such-instr=0 (every quoted instruction line re-disassembled). Independent checks, all passed (scripts read the PE with tools/sigs/xref.py and run `rdis fn`):
1. Nine __FUNCSIG__ strings of section 1 (records 0xF248E50, 0xF248E70, 0xF248F70, 0xF248DA0, 0xF248ED0, 0xF248FB0, 0xF2D30F0, 0xF20B440, 0xF276938): `FrameBuilder::insert [TDescription = ...]` names exactly the type claimed.
2. Light jump table 0xF2BF2B0 (8 entries, target = table + s32): 0 0x6640de8, 1 0x66415b0, 2 0x6640f1b, 3 0x66410a0, 4 0x6640ec1, 5 0x66417af, 6 0x664187d, 7 0x6641524 (all eight).
3. Effect jump table 0xF2BF49C (`lea rcx,[0xF2BF49C]; movsxd rax,[rcx+rax*4]; add rax,rcx; jmp rax` at 0x666acf4..0x666ad02): entry 8 = 0x666b316.
4. Function sizes (rdis fn): 0x53e2c00 0xb43, 0x53e88a0 0xd6c, 0x53e5910 0x804, 0x6c2e820 0x105e, 0x5ad3f70 0x13f7, 0x668e940 0x1c3, 0x668dd20 0x3d6, 0x668ade0 0x277, 0x67b6300 0x8bd, and the three thin clones 0x5370960 / 0x5ad5800 / 0x4c8a5b0 = 0x139.
5. Constants read from the PE: 0xF2470E0 = (0.1, 500.0), 0xF0922E0 = (0,0,0,1), 0xF20A380 = (0.12, 1, 1, 0.125), 0xEEC8060 = 1.0.
6. ServerGraphicsOverrideParameters container kinds by script over the copy-constructor listing: 0x67B7C10 handles k = 21..35 and 39 (16 sites); 0x67B7810 handles k = 0..16, 18..20, 36..38, 40..43 (27 sites); k 17 inline; the producer's constructor sites give the same split (0x433020 for 21..35, 39).
7. LightGameDescriptions.h syntax and every static_assert: `cl /std:c++20 /Zs` clean (no compile of the project).
