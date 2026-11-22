## NEXT
DONE

# U-EL15d: DLSS wrapper vtable slots 60 (optimal-settings) / 64 (evaluate) — RTX RendererContext

Source exes: Minecraft.Windows.exe 1.26.62.01. RTX RendererContext vtable base `0xF4EEE80` (overrides base `0xF4ED2D0`); slot N is at vtable + N*8. Map sections cited: 6bc, 6al.

## Vtable confirmation [V]

`rdis vt 0xF4EEE80 65` output:

```
 60 +0x1e0  sub_e83ec70          size 0x55e  push r15
 64 +0x200  sub_e8403d0          size 0xaa5b  push rbp
```

Slot 60 → RVA `0xe83ec70`, size 0x55e [V]. Slot 64 → RVA `0xe8403d0`, size 0xAA5B [V]. Confirmed against map sections 6bc/6al.

---

## Slot 60 — 0xe83ec70, size 0x55e — DLSS optimal-settings / reset override

Field accesses through `rcx=this` (set to `rsi` at entry: `e83ec80  mov rsi,rcx`). All verbatim instruction lines below are copied from `rdis dis 0xe83ec70 800`.

    e83f0be  mov rax,[rsi+0x19F58]
    e83ed30  mov eax,[rsi+0x19F78]
    e83edf0  mov r15d,[rsi+0x19F78]
    e83ef06  movsd xmm1,[rsi+0x19F78]
    e83f079  lea rax,[rsi+0x19F78]
    e83f0a6  mov r15d,[rsi+0x19F78]
    e83ed3a  mov eax,[rsi+0x19F7C]
    e83edf7  mov ebp,[rsi+0x19F7C]
    e83f0ad  mov eax,[rsi+0x19F7C]
    e83ed45  mov r15d,[rsi+0x19F80]
    e83ede0  mov r14,[rsi+0x3C56410]
    e83f0b7  mov r14,[rsi+0x3C56410]
    e83ecd0  cmp byte ptr [rsi+0x3C56418],0
    e83edd3  cmp byte ptr [rsi+0x3C56418],1
    e83eeb7  mov byte ptr [rsi+0x3C56418],0
    e83ec92  mov ecx,[rcx+0x3C5641C]
    e83ecc8  mov [rsi+0x3C5641C],eax
    e83ed5f  mov eax,[rsi+0x3C56420]
    e83edaf  mov r12d,[rsi+0x3C56420]
    e83edc1  mov [rsi+0x3C56420],eax
    e83f06e  mov ebp,[rsi+0x3C56420]
    e83eea6  mov dword ptr [rsi+0x3C56424],0
    e83f066  movss [rsi+0x3C56424],xmm0
    e83ecea  movss xmm1,[rsi+0x3C56428]
    e83ed01  movss [rsi+0x3C56428],xmm0
    e83ec98  mov eax,[rsi+0x3C5642C]
    e83ed65  cmp eax,[rsi+0x3C56430]
    e83edb6  mov eax,[rsi+0x3C56430]
    e83ecf2  movss xmm0,[rsi+0x3C56438]
    e83ee99  mov [rsi+0x3C5643C],r15d
    e83eef1  mov rax,[rsi+0x3C5643C]
    e83ef50  movq [rsi+0x3C5643C],xmm0
    e83f04d  mov [rsi+0x3C5643C],r13d
    e83f093  mov r13d,[rsi+0x3C5643C]
    e83eea0  mov [rsi+0x3C56440],ebp
    e83f059  mov [rsi+0x3C56440],r12d
    e83f09a  mov r12d,[rsi+0x3C56440]
    e83eee5  mov eax,[rsi+0x3C56444]
    e83eef8  mov [rsi+0x3C56448],rax
    e83eeeb  mov [rsi+0x3C56450],eax
    e83eeff  movups xmm0,[rsi+0x3C56454]
    e83ecbb  mov [rsi+0x3C56458],cl
    e83ecd9  mov byte ptr [rsi+0x3C56458],0
    e83ed09  mov eax,[rsi+0x3C56458]
    e83ed6d  cmp byte ptr [rsi+0x3C56458],0
    e83ed82  cmp byte ptr [rsi+0x3C56458],1
    e83eeb0  mov byte ptr [rsi+0x3C56458],0
    e83eec7  cmp byte ptr [rsi+0x3C56458],0
    e83f1ae  cmp byte ptr [rsi+0x3C56458],0
    e83ecc1  mov [rsi+0x3C56459],r8b
    e83ece3  setne [rsi+0x3C56459]
    e83eedc  cmp byte ptr [rsi+0x3C56459],1
    e83ed16  cmp qword ptr [rsi+0x3C56460],0
    e83ed29  lea rdi,[rsi+0x3C56460]
    e83f1a0  cmp qword ptr [rsi+0x3C56460],0
    e83f206  cmp byte ptr [rcx+0x3C5646C],1
    e83f216  mov rax,[rcx+0x3C964B8]
    e83f28f  sub rcx,[rsi+0x3C964B8]
    e83f21d  cmp rax,[rcx+0x3C964C0]
    e83f288  mov rcx,[rsi+0x3C964C0]
    e83f258  mov eax,[rsi+0x50]
    e83f25b  mov [rsi+0x415E620],eax
    e83f261  mov eax,[rsi+0x415E614]
    e83f271  mov [rsi+0x415E614],edx
    e83f26b  div dword ptr [rsi+0x415E60C]
    e83f446  lea rdx,[rsi+0x9B2178]
    e83f454  lea rax,[rsi+0xC96198]
    e83f4bb  mov ecx,[rsi+0xC]
    e83f6f5  movzx edi,word ptr [rsi+8]
    e83f8ea  movzx r14d,word ptr [rsi+8]

### Slot 60 field-access table (one row per distinct offset, all sites merged)

| offset | size | read/store address | sites | meaning |
|--------|------|---------------------|-------|---------|
| 0x19F58 | 8 | [rsi+0x19F58] | 1 | - |
| 0x19F78 | 4/8 | [rsi+0x19F78] | 5 | - |
| 0x19F7C | 4 | [rsi+0x19F7C] | 3 | - |
| 0x19F80 | 4 | [rsi+0x19F80] | 1 | - |
| 0x3C56410 | 8 | [rsi+0x3C56410] | 2 | - |
| 0x3C56418 | 1 | [rsi+0x3C56418] | 3 | - |
| 0x3C5641C | 4 | [rcx+0x3C5641C] / [rsi+0x3C5641C] | 2 | - |
| 0x3C56420 | 4 | [rsi+0x3C56420] | 4 | - |
| 0x3C56424 | 4 | [rsi+0x3C56424] | 2 | - |
| 0x3C56428 | 4 | [rsi+0x3C56428] | 2 | - |
| 0x3C5642C | 4 | [rsi+0x3C5642C] | 1 | - |
| 0x3C56430 | 4 | [rsi+0x3C56430] | 2 | - |
| 0x3C56438 | 4 | [rsi+0x3C56438] | 1 | - |
| 0x3C5643C | 4/8 | [rsi+0x3C5643C] | 5 | - |
| 0x3C56440 | 4 | [rsi+0x3C56440] | 3 | - |
| 0x3C56444 | 4 | [rsi+0x3C56444] | 1 | - |
| 0x3C56448 | 8 | [rsi+0x3C56448] | 1 | - |
| 0x3C56450 | 4 | [rsi+0x3C56450] | 1 | - |
| 0x3C56454 | 16 | [rsi+0x3C56454] | 1 | - |
| 0x3C56458 | 1/4 | [rsi+0x3C56458] | 8 | - |
| 0x3C56459 | 1 | [rsi+0x3C56459] | 3 | - |
| 0x3C56460 | 8 | [rsi+0x3C56460] | 3 | - |
| 0x3C5646C | 1 | [rcx+0x3C5646C] (slot60: rcx=[rsi+0x19F58]; slot64: rcx=this) | 2 | - |
| 0x3C964B8 | 8 | [rcx+0x3C964B8] / [rsi+0x3C964B8] | 2 | - |
| 0x3C964C0 | 8 | [rcx+0x3C964C0] / [rsi+0x3C964C0] | 2 | - |
| 0x50 | 4 | [rsi+0x50] | 1 | - |
| 0x415E620 | 4 | [rsi+0x415E620] | 1 | - |
| 0x415E614 | 4 | [rsi+0x415E614] | 2 | - |
| 0x415E60C | 4 | [rsi+0x415E60C] | 1 | - |
| 0x9B2178 | lea | [rsi+0x9B2178] | 1 | - |
| 0xC96198 | lea | [rsi+0xC96198] | 1 | - |
| 0xC | 4 | [rsi+0xC] | 1 | - |
| 0x8 | 2/8 | [rsi+8] (slot60); [rcx+8] (slot64) | 3 | - |
| 0x0 | 8 | [rdx] (slot64) | 1 | - |
| 0x80 | lea | [rdx+0x80] (slot64) | 3 | - |
| 0x30 | ? | [rdx+0x30] (slot64, not found in listing) | 0 | [UNVERIFIED: 0xe8403d0 rdx+0x30 field access not seen in available listing] |

### Slot 60 string references [V]

`xref.py str` confirms each string's data RVA and its reference site(s) inside `0xe83ec70`:

    e83ee17  lea rdx,[0xF5ABF1E]
    e83ee33  lea rdx,[0xF5AEED2]
    e83ee45  lea rdx,[0xF53B446]
    e83ee57  lea rdx,[0xF5BF37A]
    e83ee69  lea rdx,[0xF5BF6B2]
    e83eed0  lea r8,[0xF7C9076]
    e83ef58  lea r8,[0xF5ABF05]
    e83ef61  lea r8,[0xF5BAC38]
    e83efb8  lea rdx,[0xF53B227]
    e83efe4  lea rdx,[0xF5AEE80]
    e83eff8  lea rdx,[0xF53B3FA]
    e83f00c  lea rdx,[0xF5AEEA2]
    e83f020  lea rdx,[0xF53B41D]
    e83f034  lea rdx,[0xF547A61]
    e83f0ce  lea rdx,[0xF5A737E]
    e83f0e3  lea rdx,[0xF5A736B]
    e83f0f8  lea rdx,[0xF5AEED2]
    e83f10a  lea rdx,[0xF53B446]
    e83f11c  lea rdx,[0xF5AED1A]
    e83f12e  lea rdx,[0xF53B227]
    e83f142  lea rdx,[0xF5BF37A]
    e83f154  lea rdx,[0xF555238]
    e83f169  lea rdx,[0xF546A4D]

### Slot 64 field accesses

Accessible disassembly covers `0xe8403d0..~0xe840c80` (first 500 instructions) and `0xe84a200..~0xe84aa00` (800 instructions). Middle gap not covered.

    e840455  cmp byte ptr [rcx+0x3C5646C],0
    e84b0f6  mov rbx,[rcx+8]
    e84a2e7  mov rdi,[rdx]
    e84ae48  lea rbp,[rdx+0x80]
    e84af28  lea rbp,[rdx+0x80]
    e84b008  lea rbp,[rdx+0x80]

### Slot 64 string references [V]

Gate parameters (first chunk):

    e840615  lea rdx,[0xF56666A]
    e840659  lea rdx,[0xF563E51]
    e840677  lea rdx,[0xF562F31]
    e84069e  lea rdx,[0xF5DDC16]

NGX evaluate parameter-map keys (second chunk):

    e84a334  lea rdx,[0xF5AEE1C]
    e84a356  lea rdx,[0xF53B34C]
    e84a37f  lea rdx,[0xF5AC7E3]
    e84a3a1  lea rdx,[0xF563DF4]
    e84a3b3  lea rdx,[0xF524DB9]
    e84a3c5  lea rdx,[0xF5ADF13]
    e84a3d7  lea rdx,[0xF549A76]
    e84a3e9  lea rdx,[0xF7C81BB]
    e84a3fc  lea rdx,[0xF7C7A7A]
    e84a40f  lea rdx,[0xF547A61]
    e84a421  lea rdx,[0xF53CDAA]
    e84a443  lea rdx,[0xF7C8297]
    e84a468  lea rdx,[0xF7C7B56]
    e84a477  lea rdx,[0xF5A7300]
    e84a489  lea rdx,[0xF5C6E38]
    e84a49b  lea rdx,[0xF5A739F]
    e84a4ad  lea rdx,[0xF57F877]
    e84a4bf  lea rdx,[0xF547D94]
    e84a4d1  lea rdx,[0xF6068C6]
    e84a4e3  lea rdx,[0xF5710B9]
    e84a4f5  lea rdx,[0xF5EA31D]
    e84a507  lea rdx,[0xF5518E1]
    e84a519  lea rdx,[0xF603B49]
    e84a52b  lea rdx,[0xF603B71]
    e84a53d  lea rdx,[0xF7D22C4]
    e84a54f  lea rdx,[0xF7D160F]
    e84a561  lea rdx,[0xF7E5CB1]
    e84a573  lea rdx,[0xF7E3971]
    e84a585  lea rdx,[0xF7DD5DD]
    e84a597  lea rdx,[0xF7D91AE]
    e84a5a9  lea rdx,[0xF7D686E]
    e84a5bb  lea rdx,[0xF7D4D0B]
    e84a5cd  lea rdx,[0xF5CBB48]
    e84a5df  lea rdx,[0xF7CDE83]
    e84a5f1  lea rdx,[0xF5A735C]
    e84a603  lea rdx,[0xF5A7348]
    e84a615  lea rdx,[0xF55AE11]
    e84a627  lea rdx,[0xF5E9EA7]
    e84a639  lea rdx,[0xF606AD6]
    e84a64b  lea rdx,[0xF5E75B6]
    e84a65d  lea rdx,[0xF58ADE0]
    e84a66f  lea rdx,[0xF7C820D]
    e84a681  lea rdx,[0xF7C7ACC]
    e84a693  lea rdx,[0xF7C825A]
    e84a6a5  lea rdx,[0xF7C7B19]
    e84a6b7  lea rdx,[0xF7C827A]
    e84a6c9  lea rdx,[0xF7C7B39]
    e84a6db  lea rdx,[0xF7C81CB]
    e84a6ed  lea rdx,[0xF7C7A8A]
    e84a6ff  lea rdx,[0xF7C822D]
    e84a711  lea rdx,[0xF7C7AEC]
    e84a723  lea rdx,[0xF7C81F2]
    e84a735  lea rdx,[0xF7C7AB1]
    e84a747  lea rdx,[0xF5AEE5B]
    e84a759  lea rdx,[0xF53B3D4]
    e84a76b  lea rdx,[0xF5C919E]
    e84a77d  lea rdx,[0xF5DEB9F]
    e84a78f  lea rdx,[0xF553A8D]
    e84a7a1  lea rdx,[0xF553A70]

### Combined string-reference table (one row per distinct offset)

| offset | meaning | sites |
|--------|---------|-------|
| 0xF5ABF1E | "DLSSOptimalSettingsCallback" | 1 (slot60) |
| 0xF5AEED2 | "Width" | 2 (slot60) |
| 0xF53B446 | "Height" | 2 (slot60) |
| 0xF5BF37A | "PerfQualityValue" | 2 (slot60) |
| 0xF5BF6B2 | "RTXValue" | 1 (slot60) |
| 0xF7C9076 | "Upscaling Mode: DLSS" | 1 (slot60) |
| 0xF5ABF05 | "Upscaling Mode: Fallback" | 1 (slot60) |
| 0xF5BAC38 | "Upscaling Mode: Off" | 1 (slot60) |
| 0xF53B227 | "OutHeight" | 2 (slot60) |
| 0xF5AEE80 | "DLSS.Get.Dynamic.Max.Render.Width" | 1 (slot60) |
| 0xF53B3FA | "DLSS.Get.Dynamic.Max.Render.Height" | 1 (slot60) |
| 0xF5AEEA2 | "DLSS.Get.Dynamic.Min.Render.Width" | 1 (slot60) |
| 0xF53B41D | "DLSS.Get.Dynamic.Min.Render.Height" | 1 (slot60) |
| 0xF547A61 | "Sharpness" | 2 (slot60+slot64) |
| 0xF5A737E | "CreationNodeMask" | 1 (slot60) |
| 0xF5A736B | "VisibilityNodeMask" | 1 (slot60) |
| 0xF5AED1A | "OutWidth" | 1 (slot60) |
| 0xF555238 | "DLSS.Feature.Create.Flags" | 1 (slot60) |
| 0xF546A4D | "DLSS.Enable.Output.Subrects" | 1 (slot60) |
| 0xF56666A | "SuperSampling.NeedsUpdatedDriver" | 1 (slot64) |
| 0xF563E51 | "SuperSampling.MinDriverVersionMajor" | 1 (slot64) |
| 0xF562F31 | "SuperSampling.MinDriverVersionMinor" | 1 (slot64) |
| 0xF5DDC16 | "SuperSampling.Available" | 1 (slot64) |
| 0xF5AEE1C | "ResourceWidth" | 1 (slot64) |
| 0xF53B34C | "ResourceHeight" | 1 (slot64) |
| 0xF5AC7E3 | "DLSS.Checkerboard.Jitter.Hack" | 1 (slot64) |
| 0xF563DF4 | "Color" | 1 (slot64) |
| 0xF524DB9 | "Output" | 1 (slot64) |
| 0xF5ADF13 | "Depth" | 1 (slot64) |
| 0xF549A76 | "MotionVectors" | 1 (slot64) |
| 0xF7C81BB | "Jitter.Offset.X" | 1 (slot64) |
| 0xF7C7A7A | "Jitter.Offset.Y" | 1 (slot64) |
| 0xF53CDAA | "Reset" | 1 (slot64) |
| 0xF7C8297 | "MV.Scale.X" | 1 (slot64) |
| 0xF7C7B56 | "MV.Scale.Y" | 1 (slot64) |
| 0xF5A7300 | "TransparencyMask" | 1 (slot64) |
| 0xF5C6E38 | "ExposureTexture" | 1 (slot64) |
| 0xF5A739F | "DLSS.Input.Bias.Current.Color.Mask" | 1 (slot64) |
| 0xF57F877 | "GBuffer.Albedo" | 1 (slot64) |
| 0xF547D94 | "GBuffer.Roughness" | 1 (slot64) |
| 0xF6068C6 | "GBuffer.Metallic" | 1 (slot64) |
| 0xF5710B9 | "GBuffer.Specular" | 1 (slot64) |
| 0xF5EA31D | "GBuffer.Subsurface" | 1 (slot64) |
| 0xF5518E1 | "GBuffer.Normals" | 1 (slot64) |
| 0xF603B49 | "GBuffer.ShadingModelId" | 1 (slot64) |
| 0xF603B71 | "GBuffer.MaterialId" | 1 (slot64) |
| 0xF7D22C4 | "GBuffer.Attrib.8" | 1 (slot64) |
| 0xF7D160F | "GBuffer.Attrib.9" | 1 (slot64) |
| 0xF7E5CB1 | "GBuffer.Attrib.10" | 1 (slot64) |
| 0xF7E3971 | "GBuffer.Attrib.11" | 1 (slot64) |
| 0xF7DD5DD | "GBuffer.Attrib.12" | 1 (slot64) |
| 0xF7D91AE | "GBuffer.Attrib.13" | 1 (slot64) |
| 0xF7D686E | "GBuffer.Attrib.14" | 1 (slot64) |
| 0xF7D4D0B | "GBuffer.Attrib.15" | 1 (slot64) |
| 0xF5CBB48 | "TonemapperType" | 1 (slot64) |
| 0xF7CDE83 | "MotionVectors3D" | 1 (slot64) |
| 0xF5A735C | "IsParticleMask" | 1 (slot64) |
| 0xF5A7348 | "AnimatedTextureMask" | 1 (slot64) |
| 0xF55AE11 | "DepthHighRes" | 1 (slot64) |
| 0xF5E9EA7 | "Position.ViewSpace" | 1 (slot64) |
| 0xF606AD6 | "FrameTimeDeltaInMsec" | 1 (slot64) |
| 0xF5E75B6 | "RayTracingHitDistance" | 1 (slot64) |
| 0xF58ADE0 | "MotionVectorsReflection" | 1 (slot64) |
| 0xF7C820D | "DLSS.Input.Color.Subrect.Base.X" | 1 (slot64) |
| 0xF7C7ACC | "DLSS.Input.Color.Subrect.Base.Y" | 1 (slot64) |
| 0xF7C825A | "DLSS.Input.Depth.Subrect.Base.X" | 1 (slot64) |
| 0xF7C7B19 | "DLSS.Input.Depth.Subrect.Base.Y" | 1 (slot64) |
| 0xF7C827A | "DLSS.Input.MV.Subrect.Base.X" | 1 (slot64) |
| 0xF7C7B39 | "DLSS.Input.MV.Subrect.Base.Y" | 1 (slot64) |
| 0xF7C81CB | "DLSS.Input.Translucency.Subrect.Base.X" | 1 (slot64) |
| 0xF7C7A8A | "DLSS.Input.Translucency.Subrect.Base.Y" | 1 (slot64) |
| 0xF7C822D | "DLSS.Input.Bias.Current.Color.Subrect.Base.X" | 1 (slot64) |
| 0xF7C7AEC | "DLSS.Input.Bias.Current.Color.Subrect.Base.Y" | 1 (slot64) |
| 0xF7C81F2 | "DLSS.Output.Subrect.Base.X" | 1 (slot64) |
| 0xF7C7AB1 | "DLSS.Output.Subrect.Base.Y" | 1 (slot64) |
| 0xF5AEE5B | "DLSS.Render.Subrect.Dimensions.Width" | 1 (slot64) |
| 0xF53B3D4 | "DLSS.Render.Subrect.Dimensions.Height" | 1 (slot64) |
| 0xF5C919E | "DLSS.Pre.Exposure" | 1 (slot64) |
| 0xF5DEB9F | "DLSS.Exposure.Scale" | 1 (slot64) |
| 0xF553A8D | "DLSS.Indicator.Invert.X.Axis" | 1 (slot64) |
| 0xF553A70 | "DLSS.Indicator.Invert.Y.Axis" | 1 (slot64) |

---

## CLOSES?

NO — blocking fact: slot 64 field offset `rdx+0x30` (listed by the precomputed dossier `docs/functions/e8403d0.md` as `rdx: +0x30(rqx2)`) was not found as a verbatim `[rdx+0x30]` instruction in the accessible disassembly (`0xe8403d0..~0xe840c80` and `0xe84a200..~0xe84aa00`). The middle of the function (`~0xe840c80..0xe84a200`) was not disassembled, so this access is `[?]`. Every other pending part of the item line is proven by [V] rows.

## TOOL REQUESTS

None — all data gathered with existing tools (rdis dis, rdis vt, xref.py str).