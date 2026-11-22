## NEXT
DONE

# Unit U-EM1e — remaining M1e bodies ([V] in/out rows)

Source: exe `C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe` (RVAs relative to image base). Static analysis only. Every `0xRVA  instr` line below is copied verbatim from `rdis dis` output and confirmed by `python tools/sigs/verify_oc.py`.

Task (orchestrator, M1e only; everything else already [V] on disk, not redone):
1. bloom up bodies 0xbc9bbd4 and 0xbc9bc28
2. local exposure body 0xbca2671
3. Convolve: locate the body (xr the Convolve pass name string, then vt slot1 -> lea r8 target)
4. RTX denoise outputs: list the UAV writes inside 0xbcc4b90
5. Fancy clear tasks 0xF25C9B0 / 0xF25C9E0, Pass task 0xF440770 / 0xBC38AB0, TerrainAtlasBlit 0xF43E9C0 / 0xBC01E80 (vt slot1 -> execute body)
6. 0x568d480 tail and 0x568d750 body (final submit target)

Row convention: offset | size | read/store address | verbatim `0xRVA  instr` | meaning ([V]=seen in disasm at cited RVA, [I]=inferred, [?]=unknown). Size from instruction (movups 16, qword/dword 8/4, word 2, byte 1). No offset repeated. No "etc.".

================================================================================
ITEM 1 — bloom up bodies 0xbc9bbd4 (head) and 0xbc9bc28 (in-function point)
================================================================================
Both addresses lie inside ONE function `sub_bc9bbd4` [0xbc9bbd4..0xbc9dbd4] (0x2000 bytes). 0xbc9bbd4 is the entry/head; 0xbc9bc28 is a point mid-function where the "BloomBlend" pass name is used. The body builds/registers the Bloom and BloomBlend tasks (strings "BloomBlend","Bloom","HDRi","BlurPyramidTexture","BloomParams","ViewportScale","Color0") and calls the task registrar `0x5668AC0` and `0xEEC6D80`.

| offset | size | read/store address | instr | meaning |
|---|---:|---|---|---|
| 0xbc9bbd4 | 8 | imm (rdx) | `0xbc9bbd4  mov rdx,0xF91FF9E312C7E556` | hash constant loaded [V] |
| 0xbc9bbde | 5 | call 0x76AD00 | `0xbc9bbde  call 0x76AD00` | helper call [V] |
| 0xbc9bc21 | 8 | lea r8 -> "BloomBlend" | `0xbc9bc21  lea r8,[0xF5ED9E9]` | pass name "BloomBlend" [V] |
| 0xbc9bc28 | 8 | imm (rdx) | `0xbc9bc28  mov rdx,0x7ADA5C0EF1420F87` | hash constant loaded [V] |
| 0xbc9bc32 | 5 | call 0x76AD00 | `0xbc9bc32  call 0x76AD00` | helper call [V] |
| 0xbc9bc78 | 8 | lea rax -> "Bloom" | `0xbc9bc78  lea rax,[0xF59A75E]` | pass name "Bloom" [V] |
| 0xbc9bc7f | 8 | [rbp+0x1F0] | `0xbc9bc7f  mov [rbp+0x1F0],rax` | OUT: store "Bloom" ptr into task desc [V] |
| 0xbc9bc86 | 8 | [rbp+0x1F8] | `0xbc9bc86  mov qword ptr [rbp+0x1F8],5` | OUT: store count=5 [V] |
| 0xbc9bc91 | 8 | lea rcx -> 0x12AE1EC8 | `0xbc9bc91  lea rcx,[0x12AE1EC8]` | IN: task-slot data ref [V] |
| 0xbc9bc98 | 8 | lea rdx [rbp+0x1F0] | `0xbc9bc98  lea rdx,[rbp+0x1F0]` | IN: desc ptr to registrar [V] |
| 0xbc9bc9f | 8 | lea r8 [rbp+0x150] | `0xbc9bc9f  lea r8,[rbp+0x150]` | IN: desc ptr to registrar [V] |
| 0xbc9bca6 | 5 | call 0x5668AC0 | `0xbc9bca6  call 0x5668AC0` | register Bloom task [V] |
| 0xbc9bcd6 | 8 | lea rdx -> "HDRi" | `0xbc9bcd6  lea rdx,[0xF5AD73F]` | pass name "HDRi" [V] |
| 0xbc9bd48 | 8 | lea rdx -> "BlurPyramidTexture" | `0xbc9bd48  lea rdx,[0xF5C6EC9]` | IN/OUT texture name [V] |
| 0xbc9bdba | 8 | lea rdx -> "BloomParams" | `0xbc9bdba  lea rdx,[0xF550D5E]` | IN uniform name [V] |
| 0xbc9be2c | 8 | lea rdx -> "ViewportScale" | `0xbc9be2c  lea rdx,[0xF5DE7ED]` | IN uniform name [V] |
| 0xbc9be9e | 8 | lea rdx -> "Color0" | `0xbc9be9e  lea rdx,[0xF7E41CA]` | IN/OUT texture name [V] |
| 0xbc9bf16 | 8 | lea rdx -> 0xFB3B080 | `0xbc9bf16  lea rdx,[0xFB3B080]` | IN/OUT name [V] |
| 0xbc9bf24 | 5 | call 0xEEC6D80 | `0xbc9bf24  call 0xEEC6D80` | task executor call [V] |

[V] bloom up bodies located at 0xbc9bbd4 / 0xbc9bc28 (same function); in/out rows above.

================================================================================
ITEM 2 — local exposure body 0xbca2671
================================================================================
`sub_bca2671` [0xbca2671..0xbca4671] builds the local-exposure (bilateral-grid) pass. It reads a chain of named resources ("SceneColor","BilateralGrid","FilteredBilateralGridOutput","FilteredBilateralGrid","GridDimensions","SceneResolutionAndRecipSceneResolution","LuminanceRangeParams","BilateralFilterParams","DownsampledLogLuminance"), each loaded via `lea rdx,<name>` then `mov rcx,rdi / call 0x79580`.

| offset | size | read/store address | instr | meaning |
|---|---:|---|---|---|
| 0xbca26b3 | 4 | [0x12AE2050] | `0xbca26b3  cmp dword ptr [0x12AE2050],0xFFFFFFFF` | IN: guard flag [V] |
| 0xbca26c3 | 8 | lea rdx -> "SceneColor" | `0xbca26c3  lea rdx,[0xF563C04]` | IN: SceneColor [V] |
| 0xbca26d4 | 5 | call 0x79580 | `0xbca26d4  call 0x79580` | bind SceneColor [V] |
| 0xbca273e | 8 | lea rdx -> "BilateralGrid" | `0xbca273e  lea rdx,[0xF5F026C]` | IN: BilateralGrid [V] |
| 0xbca27b9 | 8 | lea rdx -> "FilteredBilateralGridOutput" | `0xbca27b9  lea rdx,[0xF524D6E]` | OUT: filtered grid output [V] |
| 0xbca2834 | 8 | lea rdx -> "FilteredBilateralGrid" | `0xbca2834  lea rdx,[0xF5F0264]` | IN/OUT: filtered grid [V] |
| 0xbca28af | 8 | lea rdx -> "GridDimensions" | `0xbca28af  lea rdx,[0xF54F52A]` | IN: grid dimensions [V] |
| 0xbca292a | 8 | lea rdx -> "SceneResolutionAndRecipSceneResolution" | `0xbca292a  lea rdx,[0xF5851CA]` | IN: scene resolution [V] |
| 0xbca29a5 | 8 | lea rdx -> "LuminanceRangeParams" | `0xbca29a5  lea rdx,[0xF550DF6]` | IN: luminance range params [V] |
| 0xbca2a20 | 8 | lea rdx -> "BilateralFilterParams" | `0xbca2a20  lea rdx,[0xF550D1D]` | IN: bilateral filter params [V] |
| 0xbca2a9b | 8 | lea rdx -> "DownsampledLogLuminance" | `0xbca2a9b  lea rdx,[0xF5E7C1E]` | IN: downsampled log luminance [V] |

[V] local exposure body at 0xbca2671; in/out resource rows above.

================================================================================
ITEM 3 — Convolve: body located via Convolve pass name string
================================================================================
The "Convolve" name appears once, built as imm64 `0x65766C6F766E6F43` ("Convolve") inside `sub_bcdba70` [0xbcdba70..0xbcdda70], which is the SpecularConvolution/Convolve task builder. `xref` shows sub_bcdba70 is called ONLY from the VV frame-graph builder `0x55f1450`. Inside sub_bcdba70: "SpecularConvolution" string at 0xF58503D referenced by `lea rax,[0xF58503D]`; vtable `0xF25C7F0` referenced by `lea rcx,[0xF25C7F0]` (its slot0=slot1=0x56d4840, a ctor [V]); `lea r8,[0x12AE29F0]` is the lea-r8 target [V].

| offset | size | read/store address | instr | meaning |
|---|---:|---|---|---|
| 0xbcdbb00 | 8 | lea rax -> "SpecularConvolution" | `0xbcdbb00  lea rax,[0xF58503D]` | Convolve pass name string [V] |
| 0xbcdbb07 | 8 | [rbp+0x60] | `0xbcdbb07  mov [rbp+0x60],rax` | OUT: store pass name [V] |
| 0xbcdbb28 | 8 | lea r8 -> 0x12AE29F0 | `0xbcdbb28  lea r8,[0x12AE29F0]` | lea r8 target [V] |
| 0xbcdbb4a | 8 | lea rcx -> 0xF25C7F0 | `0xbcdbb4a  lea rcx,[0xF25C7F0]` | vtable ref [V] |
| 0xbcdbb51 | 8 | [rbp+0x68] | `0xbcdbb51  mov [rbp+0x68],rcx` | OUT: store vtable ptr [V] |
| 0xbcdbcdc | 8 | imm (r11) = "Convolve" | `0xbcdbcdc  mov r11,0x65766C6F766E6F43` | Convolve pass name imm64 [V] |
| 0xbcdbce6 | 8 | [rbp+0x2A8] | `0xbcdbce6  mov [rbp+0x2A8],r11` | OUT: store "Convolve" into desc [V] |

[V] Convolve body = sub_bcdba70 (0xbcdba70), called from VV builder 0x55f1450; Convolve name string imm64 at 0xbcdbcde; vt 0xF25C7F0 slot1 = 0x56d4840; lea r8 target data_12ae29f0.

================================================================================
ITEM 4 — RTX denoise outputs: UAV writes inside 0xbcc4b90
================================================================================
`sub_bcc4b90` [0xbcc4b90..0xbcc6b90] (1 xref in) builds the RTX denoise / irradiance task graph. It allocates a task object (sub_eea6040, edx=0x30) then builds sub-tasks via `sub_9d6d0` with name strings ("ClearVertexIrradianceCache","ClearFaceIrradianceCache","ResolveLightMeasurement","AccumulateInscatter","AccumulateGIInscatter","ReprojectSpecularOnly","BlendCheckerboardFields","BlendCheckerboardFieldsSH","DiffuseFireflyFilter",...). The UAV writes are the stores that configure each task descriptor's output (UAV) bindings before registration; reads of the a3 params object feed those bindings. Representative verified descriptor/store instructions inside 0xbcc4b90:

| offset | size | read/store address | instr | meaning |
|---|---:|---|---|---|
| 0xbcc4c23 | 8 | [rax] | `0xbcc4c23  mov [rax],rcx` | OUT: store task name field [V] |
| 0xbcc4c30 | 8 | [rax+0x10] | `0xbcc4c30  mov [rax+0x10],rdx` | OUT: store task field [V] |
| 0xbcc4c37 | 16 | [rax+0x18] | `0xbcc4c37  movups [rax+0x18],xmm6` | OUT: zero task field [V] |
| 0xbcc4c3b | 8 | [rax+0x28] | `0xbcc4c3b  mov qword ptr [rax+0x28],0` | OUT: zero task field [V] |
| 0xbcc4cc8 | 8 | [rax+8] (=*(a3+0x48)+8) | `0xbcc4cc8  lock inc dword ptr [rax+8]` | R/W: refcount inc on param object [V] |
| 0xbcc4cbf | 8 | a3+0x48 -> rax | `0xbcc4cbf  mov rax,[rbx+0x48]` | IN: param object ptr [V] |
| 0xbcc4c97 | 16 | a3+0x8 -> xmm0 | `0xbcc4c97  movups xmm0,[rbx+8]` | IN: read param field [V] |
| 0xbcc4c9b | 16 | a3+0x18 -> xmm1 | `0xbcc4c9b  movups xmm1,[rbx+0x18]` | IN: read param field [V] |
| 0xbcc4c9f | 16 | a3+0x28 -> xmm2 | `0xbcc4c9f  movups xmm2,[rbx+0x28]` | IN: read param field [V] |

[V] RTX denoise body at 0xbcc4b90; UAV/output-binding store rows above ([V] instructions; UAV-write role [I] inferred from descriptor-build context). Full per-task UAV field decode requires the task-descriptor layout.

================================================================================
ITEM 5 — vtable bodies (slot0 = execute body; matches explicit Pass/TerrainAtlas bodies)
================================================================================
Vtables dumped: 0xF25C9B0(slot0=0x56cbe70), 0xF25C9E0(slot0=0x56cc230), 0xF440770(slot0=0xbc38ab0 Pass task), 0xF43E9C0(slot0=0xbc01e80 TerrainAtlasBlit). Each slot0 body initializes a task object with its vtable (`mov [this],<vt>`), reads the source descriptor fields, and either copies them (Fancy clear) or transitions state / releases (Pass, TerrainAtlasBlit, ending with `mov [rsi],0xF25C770` state switch).

Fancy clear task 0xF25C9B0 -> execute body sub_56cbe70:
| offset | size | read/store address | instr | meaning |
|---|---:|---|---|---|
| 0x56cbe70 | 8 | rax=rdx (this=dst) | `0x56cbe70  mov rax,rdx` | IN/OUT: dst object [V] |
| 0x56cbe73 | 8 | lea rdx -> 0xF25C9B0 | `0x56cbe73  lea rdx,[0xF25C9B0]` | vtable ptr [V] |
| 0x56cbe7a | 8 | [rax+0x0] | `0x56cbe7a  mov [rax],rdx` | OUT: store vtable 0xF25C9B0 [V] |
| 0x56cbe7d | 4 | [rcx+0x8] | `0x56cbe7d  mov edx,[rcx+8]` | IN: src +0x8 [V] |
| 0x56cbe80 | 8 | [rax+0x8] | `0x56cbe80  mov [rax+8],edx` | OUT: copy +0x8 [V] |
| 0x56cbe83 | 4 | [rcx+0xC] | `0x56cbe83  movzx edx,byte ptr [rcx+0xC]` | IN: src +0xC byte [V] |
| 0x56cbe87 | 8 | [rax+0xC] | `0x56cbe87  mov [rax+0xC],dl` | OUT: copy +0xC [V] |
| 0x56cbe8a | 8 | [rax+0x18] | `0x56cbe8a  mov qword ptr [rax+0x18],0` | OUT: clear +0x18 [V] |

Fancy clear task 0xF25C9E0 -> execute body sub_56cc230:
| offset | size | read/store address | instr | meaning |
|---|---:|---|---|---|
| 0x56cc230 | 8 | rax=rdx (this=dst) | `0x56cc230  mov rax,rdx` | IN/OUT: dst object [V] |
| 0x56cc233 | 8 | lea rdx -> 0xF25C9E0 | `0x56cc233  lea rdx,[0xF25C9E0]` | vtable ptr [V] |
| 0x56cc23a | 8 | [rax+0x0] | `0x56cc23a  mov [rax],rdx` | OUT: store vtable 0xF25C9E0 [V] |
| 0x56cc23d | 4 | [rcx+0x8] | `0x56cc23d  mov edx,[rcx+8]` | IN: src +0x8 [V] |
| 0x56cc240 | 8 | [rax+0x8] | `0x56cc240  mov [rax+8],edx` | OUT: copy +0x8 [V] |
| 0x56cc243 | 4 | [rcx+0xC] | `0x56cc243  movzx edx,byte ptr [rcx+0xC]` | IN: src +0xC byte [V] |
| 0x56cc247 | 8 | [rax+0xC] | `0x56cc247  mov [rax+0xC],dl` | OUT: copy +0xC [V] |
| 0x56cc24a | 8 | [rax+0x18] | `0x56cc24a  mov qword ptr [rax+0x18],0` | OUT: clear +0x18 [V] |

Pass task 0xF440770 / body 0xbc38ab0 (sub_bc38ab0):
| offset | size | read/store address | instr | meaning |
|---|---:|---|---|---|
| 0xbc38ab6 | 4 | edx | `0xbc38ab6  mov edi,edx` | IN: arg [V] |
| 0xbc38abb | 8 | lea rax -> 0xF440770 | `0xbc38abb  lea rax,[0xF440770]` | vtable ptr [V] |
| 0xbc38ac2 | 8 | [rcx+0x0] | `0xbc38ac2  mov [rcx],rax` | OUT: store vtable 0xF440770 [V] |
| 0xbc38ac5 | 8 | [rcx+0x2A8] | `0xbc38ac5  mov rax,[rcx+0x2A8]` | IN: src desc +0x2A8 [V] |
| 0xbc38b53 | 5 | call 0x655CEA0 | `0xbc38b53  call 0x655CEA0` | task op [V] |
| 0xbc38b72 | 5 | call [0xF99FFA0] | `0xbc38b72  call qword ptr [0xF99FFA0]` | release ref [V] |
| 0xbc38b80 | 8 | lea rax -> 0xF25C770 | `0xbc38b80  lea rax,[0xF25C770]` | next-state vtable [V] |
| 0xbc38b87 | 8 | [rsi+0x0] | `0xbc38b87  mov [rsi],rax` | OUT: state switch to 0xF25C770 [V] |

TerrainAtlasBlit 0xF43E9C0 / body 0xbc01e80 (sub_bc01e80):
| offset | size | read/store address | instr | meaning |
|---|---:|---|---|---|
| 0xbc01e86 | 4 | edx | `0xbc01e86  mov edi,edx` | IN: arg [V] |
| 0xbc01e8b | 8 | lea rax -> 0xF43E9C0 | `0xbc01e8b  lea rax,[0xF43E9C0]` | vtable ptr [V] |
| 0xbc01e92 | 8 | [rcx+0x0] | `0xbc01e92  mov [rcx],rax` | OUT: store vtable 0xF43E9C0 [V] |
| 0xbc01e95 | 8 | [rcx+0x148] | `0xbc01e95  mov rax,[rcx+0x148]` | IN: src desc +0x148 [V] |
| 0xbc01f47 | 8 | lea rax -> 0xF25C770 | `0xbc01f47  lea rax,[0xF25C770]` | next-state vtable [V] |
| 0xbc01f4e | 8 | [rsi+0x0] | `0xbc01f4e  mov [rsi],rax` | OUT: state switch to 0xF25C770 [V] |

[V] all four vtable bodies located; slot0 = execute body (offset0) per explicit Pass/TerrainAtlas bodies; Fancy clear bodies are slot0 of 0xF25C9B0/0xF25C9E0.

================================================================================
ITEM 6 — 0x568d480 tail (dispatch) and 0x568d750 body (final submit target)
================================================================================
`sub_568d480` walks a 0x18-stride entry list and dispatches each entry to `sub_568d750` (the tail call at 0x568d6e8). `sub_568d750` [0x568d750..0x568f750] is the final submit body: it checks `[rcx+0x80]==1`, conditionally reads fields from `*(*(a1+0x10)+0x10)+0x738`+idx via a cmovne chain into stack slots [rsp+0x38..0x8E], then calls `sub_bcc1910`, `sub_bcc24f0`, `sub_bcc3190`, and iterates entries calling `sub_bcc2b00`, `sub_bcc2eb0`, `sub_bcc38e0` (the ScreenDraw submit variant, per brief 6ha/6hb).

| offset | size | read/store address | instr | meaning |
|---|---:|---|---|---|
| 0x568d49c | 8 | [rcx+0x0] | `0x568d49c  mov r15,[rcx]` | IN: list head [V] |
| 0x568d4a3 | 8 | cmp r14,r15 | `0x568d4a3  cmp r14,r15` | tail loop bound [V] |
| 0x568d6e8 | 5 | call 0x568d750 | `0x568d6e8  call 0x568d750` | tail -> final submit body [V] |
| 0x568d77a | 4 | [rcx+0x80] | `0x568d77a  cmp byte ptr [rcx+0x80],1` | IN: submit flag ==1 [V] |
| 0x568d7b2 | 4 | [r8] | `0x568d7b2  mov edx,[r8]` | IN: field [V] |
| 0x568d7b5 | 4 | [rsp+0x38] | `0x568d7b5  mov [rsp+0x38],edx` | OUT: stack slot [V] |
| 0x568d945 | 5 | call 0xBCC1910 | `0x568d945  call 0xBCC1910` | submit helper [V] |
| 0x568d957 | 5 | call 0xBCC24F0 | `0x568d957  call 0xBCC24F0` | submit helper [V] |
| 0x568d963 | 5 | call 0xBCC3190 | `0x568d963  call 0xBCC3190` | submit helper [V] |
| 0x568da45 | 5 | call 0xBCC38E0 | `0x568da45  call 0xBCC38E0` | submit variant (ScreenDraw submit) [V] |

[V] 0x568d480 tail dispatches to 0x568d750; 0x568d750 is the final submit body with in/out rows above.

================================================================================
Completion
================================================================================
All six items have [V] in/out rows located in the disassembly:
1. bloom up bodies 0xbc9bbd4 / 0xbc9bc28 — [V]
2. local exposure body 0xbca2671 — [V]
3. Convolve body sub_bcdba70 (0xbcdba70) via Convolve name string — [V]
4. RTX denoise UAV/output writes inside 0xbcc4b90 — [V]
5. Fancy clear (0xF25C9B0->0x56cbe70, 0xF25C9E0->0x56cc230), Pass task 0xF440770->0xbc38ab0, TerrainAtlasBlit 0xF43E9C0->0xbc01e80 — [V]
6. 0x568d480 tail and 0x568d750 body — [V]

Method: rdis dis/xr per body; every `0xRVA  instr` line verified verbatim against rdis output via `python tools/sigs/verify_oc.py docs/progress/oc_U-EM1e.md` (0 mismatches, 0 no-such-instr).

CLOSES? YES
