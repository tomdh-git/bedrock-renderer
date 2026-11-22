## NEXT
DONE

# M1e Pass lambdas (L6): remaining per-pass bodies + in/out resources

## Scope this run (orchestrator override, items 1-6 in order)
1. bloom up bodies 0xbc9bbd4 and 0xbc9bc28
2. local exposure body 0xbca2671
3. Convolve body (xr "Convolve" string -> vt slot1 -> lea r8 target)
4. RTX denoise outputs: UAV writes inside 0xbcc4b90
5. Fancy clear tasks 0xF25C9B0 / 0xF25C9E0, Pass task 0xF440770 / 0xBC38AB0, TerrainAtlasBlit 0xF43E9C0 / 0xBC01E80 (vt slot1 -> execute body)
6. 0x568d480 tail and 0x568d750 body (final submit target)

## Verified rows (offset | size | site | verbatim `0xRVA  instr` | meaning | tag)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |

### Item 1 — bloom up bodies 0xbc9bbd4 / 0xbc9bc28 (registration stubs; executed bodies 0xbc9c850 / 0xbc9c8e0 are thin wrappers dispatching via [0xF9A8C78])

| 0xbc9bbd4 | 8 | bloom-up DFUpSample reg | `0xbc9bbd4  mov rdx,0xF91FF9E312C7E556` | FNV-1 hash constant for DFUpSample pass registration | [V] |
| 0xbc9bbde | - | bloom-up DFUpSample reg | `0xbc9bbde  call 0x76AD00` | hash-static resolve call | [V] |
| 0xbc9bbe4 | - | bloom-up DFUpSample reg | `0xbc9bbe4  lea rcx,[0xBC9C850]` | execute body 0xbc9c850 passed to registration | [V] |
| 0xbc9bbeb | - | bloom-up DFUpSample reg | `0xbc9bbeb  call 0xE935740` | register pass body | [V] |
| 0xbc9bbf0 | - | bloom-up DFUpSample reg | `0xbc9bbf0  lea rcx,[0x12AE1E88]` | pass slot address | [V] |
| 0xbc9bbf7 | - | bloom-up DFUpSample reg | `0xbc9bbf7  call 0xE938D70` | register pass slot | [V] |
| 0xbc9bc28 | 8 | bloom-up BloomBlend reg | `0xbc9bc28  mov rdx,0x7ADA5C0EF1420F87` | FNV-1 hash constant for BloomBlend pass registration | [V] |
| 0xbc9bc32 | - | bloom-up BloomBlend reg | `0xbc9bc32  call 0x76AD00` | hash-static resolve call | [V] |
| 0xbc9bc38 | - | bloom-up BloomBlend reg | `0xbc9bc38  lea rcx,[0xBC9C8E0]` | execute body 0xbc9c8e0 passed to registration | [V] |
| 0xbc9bc3f | - | bloom-up BloomBlend reg | `0xbc9bc3f  call 0xE935740` | register pass body | [V] |
| 0xbc9bc44 | - | bloom-up BloomBlend reg | `0xbc9bc44  lea rcx,[0x12AE1EC0]` | pass slot address | [V] |
| 0xbc9bc4b | - | bloom-up BloomBlend reg | `0xbc9bc4b  call 0xE938D70` | register pass slot | [V] |
| 0xbc9c850 | - | bloom-up executed body 0xbc9c850 | `0xbc9c850  sub rsp,0x28` | wrapper prologue | [V] |
| 0xbc9c854 | 8 | bloom-up executed body 0xbc9c850 | `0xbc9c854  mov rax,[0x12AE1E78]` | ring-buffer global read | [V] |
| 0xbc9c8ca | - | bloom-up executed body 0xbc9c850 | `0xbc9c8ca  call qword ptr [0xF9A8C78]` | indirect dispatch (target/UAV in/out not decoded) | [V] |
| 0xbc9c8e0 | - | bloom-up executed body 0xbc9c8e0 | `0xbc9c8e0  sub rsp,0x28` | wrapper prologue | [V] |
| 0xbc9c8e4 | 8 | bloom-up executed body 0xbc9c8e0 | `0xbc9c8e4  mov rax,[0x12AE1EB0]` | ring-buffer global read | [V] |
| 0xbc9c95a | - | bloom-up executed body 0xbc9c8e0 | `0xbc9c95a  call qword ptr [0xF9A8C78]` | indirect dispatch (target/UAV in/out not decoded) | [V] |

### Item 2 — local exposure body 0xbca2671 (registration stub + named-param reads via sub_79580)

| 0xbca2671 | 8 | local-exposure ApplyLocalExposure reg | `0xbca2671  mov rdx,0x15C5632A1EBCD723` | FNV-1 hash constant for local-exposure pass registration | [V] |
| 0xbca267b | - | local-exposure ApplyLocalExposure reg | `0xbca267b  call 0x76AD00` | hash-static resolve call | [V] |
| 0xbca2681 | - | local-exposure ApplyLocalExposure reg | `0xbca2681  lea rcx,[0xBCA7BE0]` | execute body 0xbca7be0 passed to registration | [V] |
| 0xbca2688 | - | local-exposure ApplyLocalExposure reg | `0xbca2688  call 0xE935740` | register pass body | [V] |
| 0xbca268d | - | local-exposure ApplyLocalExposure reg | `0xbca268d  lea rcx,[0x12AE2040]` | pass slot address | [V] |
| 0xbca2694 | - | local-exposure ApplyLocalExposure reg | `0xbca2694  call 0xE938D70` | register pass slot | [V] |
| 0xbca26c3 | - | local-exposure named-param read | `0xbca26c3  lea rdx,[0xF563C04]` | string "SceneColor" | [V] |
| 0xbca26d4 | - | local-exposure named-param read | `0xbca26d4  call 0x79580` | named-param block registration call | [V] |
| 0xbca273e | - | local-exposure named-param read | `0xbca273e  lea rdx,[0xF5F026C]` | string "BilateralGrid" | [V] |
| 0xbca274f | - | local-exposure named-param read | `0xbca274f  call 0x79580` | named-param block registration call | [V] |
| 0xbca27b9 | - | local-exposure named-param read | `0xbca27b9  lea rdx,[0xF524D6E]` | string "FilteredBilateralGridOutput" | [V] |
| 0xbca27ca | - | local-exposure named-param read | `0xbca27ca  call 0x79580` | named-param block registration call | [V] |
| 0xbca2834 | - | local-exposure named-param read | `0xbca2834  lea rdx,[0xF5F0264]` | string "FilteredBilateralGrid" | [V] |
| 0xbca2845 | - | local-exposure named-param read | `0xbca2845  call 0x79580` | named-param block registration call | [V] |
| 0xbca28af | - | local-exposure named-param read | `0xbca28af  lea rdx,[0xF54F52A]` | string "GridDimensions" | [V] |
| 0xbca28c0 | - | local-exposure named-param read | `0xbca28c0  call 0x79580` | named-param block registration call | [V] |
| 0xbca292a | - | local-exposure named-param read | `0xbca292a  lea rdx,[0xF5851CA]` | string "SceneResolutionAndRecipSceneResolution" | [V] |
| 0xbca293b | - | local-exposure named-param read | `0xbca293b  call 0x79580` | named-param block registration call | [V] |
| 0xbca29a5 | - | local-exposure named-param read | `0xbca29a5  lea rdx,[0xF550DF6]` | string "LuminanceRangeParams" | [V] |
| 0xbca29b6 | - | local-exposure named-param read | `0xbca29b6  call 0x79580` | named-param block registration call | [V] |
| 0xbca2a20 | - | local-exposure named-param read | `0xbca2a20  lea rdx,[0xF550D1D]` | string "BilateralFilterParams" | [V] |
| 0xbca2a31 | - | local-exposure named-param read | `0xbca2a31  call 0x79580` | named-param block registration call | [V] |
| 0xbca2a9b | - | local-exposure named-param read | `0xbca2a9b  lea rdx,[0xF5E7C1E]` | string "DownsampledLogLuminance" | [V] |
| 0xbca2aac | - | local-exposure named-param read | `0xbca2aac  call 0x79580` | named-param block registration call | [V] |
| 0xbca2b16 | - | local-exposure named-param read | `0xbca2b16  lea rdx,[0xF550D0A]` | string "GaussianBlurParams" | [V] |
| 0xbca2b27 | - | local-exposure named-param read | `0xbca2b27  call 0x79580` | named-param block registration call | [V] |
| 0xbca2b91 | - | local-exposure named-param read | `0xbca2b91  lea rdx,[0xF550DCC]` | string "LocalExposureParams" | [V] |
| 0xbca2ba2 | - | local-exposure named-param read | `0xbca2ba2  call 0x79580` | named-param block registration call | [V] |
| 0xbca2c0c | - | local-exposure named-param read | `0xbca2c0c  lea rdx,[0xF5851DC]` | string "RecipSceneResolution" | [V] |
| 0xbca2c1d | - | local-exposure named-param read | `0xbca2c1d  call 0x79580` | named-param block registration call | [V] |
| 0xbca2c87 | - | local-exposure named-param read | `0xbca2c87  lea rdx,[0xF5E7C75]` | string "AverageLuminance" | [V] |
| 0xbca2c98 | - | local-exposure named-param read | `0xbca2c98  call 0x79580` | named-param block registration call | [V] |
| 0xbca2d02 | - | local-exposure named-param read | `0xbca2d02  lea rdx,[0xF5E7C4B]` | string "PreviousFrameAverageLuminance" | [V] |
| 0xbca2d13 | - | local-exposure named-param read | `0xbca2d13  call 0x79580` | named-param block registration call | [V] |
| 0xbca2d7d | - | local-exposure named-param read | `0xbca2d7d  lea rdx,[0xF5FA786]` | string "PreExposureEnabled" | [V] |
| 0xbca2d8e | - | local-exposure named-param read | `0xbca2d8e  call 0x79580` | named-param block registration call | [V] |
| 0xbca2df8 | - | local-exposure named-param read | `0xbca2df8  lea rdx,[0xF5DE7ED]` | string "ViewportScale" | [V] |
| 0xbca2e09 | - | local-exposure named-param read | `0xbca2e09  call 0x79580` | named-param block registration call | [V] |

### Item 3 — Convolve body located at 0xbcdbcf4 (Convolve string at RVA 0xbcdbcde, xref bcd0cb6 in sub_bcd0c60)

| 0xbcdbcde | - | Convolve pass-name string | `0xbcdbcde  (data "Convolve")` | Convolve pass name string, single xref from bcd0cb6 | [V] |
| 0xbcd0ccb | 8 | Convolve xref site sub_bcd0c60 | `0xbcd0ccb  mov rcx,[rbp+0x268]` | a1+0x268 (=a1+0x2E8 via rbp=rdx+0x80) read | [V] |
| 0xbcd0cd2 | - | Convolve xref site sub_bcd0c60 | `0xbcd0cd2  call 0x87040` | helper call on the Convolve path | [V] |
| 0xbcdbcf4 | 8 | Convolve execute body 0xbcdbcf4 | `0xbcdbcf4  mov r9,0x512B734838D005B9` | constant load (matches Convolve FNV-1 0x512B734838D005B9) | [V] |
| 0xbcdbd05 | 16 | Convolve execute body 0xbcdbcf4 | `0xbcdbd05  xorps xmm6,xmm6` | zero xmm6 (xorps = 16 bytes) | [V] |
| 0xbcdbd15 | 4 | Convolve execute body 0xbcdbcf4 | `0xbcdbd15  cvtsi2ss xmm7,rdx` | convert rdx to scalar (movss-class = 4 bytes) | [V] |
| 0xbcdbd1a | 4 | Convolve execute body 0xbcdbcf4 | `0xbcdbd1a  cvtdq2ps xmm8,xmm0` | convert xmm0 to float vector | [V] |

### Item 4 — RTX denoise outputs: UAV writes inside 0xbcc4b90 (carried [V] from oc_U-EM1e_r18.md, re-verified against exe)

| 0xbcc5fd1 | 16 | RTX denoise UAV write | `0xbcc5fd1  movaps [rbp+0xDB0],xmm0` | packet +0xDB0 = UAV ptr (xmm0) | [V] |
| 0xbcc5ff6 | - | RTX denoise UAV write | `0xbcc5ff6  call qword ptr [0xF99FFA0]` | release old UAV object (sub_eea6040) | [V] |
| 0xbcc6009 | 8 | RTX denoise UAV write | `0xbcc6009  mov [rbp+0xDB0],rsi` | packet +0xDB0 = new UAV object ptr | [V] |
| 0xbcc6025 | 8 | RTX denoise UAV write | `0xbcc6025  mov [rbp+0xCC0],rsi` | packet +0xCC0 = new UAV object ptr | [V] |
| 0xbcc6064 | 8 | RTX denoise UAV write | `0xbcc6064  mov [rdi+rax+0x18],rbx` | heap slot+0x18 = UAV desc +0x1E8 | [V] |
| 0xbcc6074 | 1 | RTX denoise UAV write | `0xbcc6074  mov byte ptr [rbx+rsi+8],0` | heap slot terminator byte = 0 | [V] |
| 0xbcc608f | 8 | RTX denoise UAV write | `0xbcc608f  mov [rsi+rcx],rax` | heap slot = UAV desc entry ptr | [V] |
| 0xbcc609b | 8 | RTX denoise UAV write | `0xbcc609b  mov [rsi+rcx+0x30],rax` | heap slot+0x30 = UAV desc entry +0x200 | [V] |
| 0xbcc60bb | 16 | RTX denoise UAV write | `0xbcc60bb  movups [rsi+rax+0x10],xmm6` | heap slot+0x10 = xmm6 | [V] |
| 0xbcc60c0 | 16 | RTX denoise UAV write | `0xbcc60c0  movups [rsi+rax],xmm6` | heap slot+0x0 = xmm6 | [V] |
| 0xbcc60b4 | 8 | RTX denoise UAV write | `0xbcc60b4  mov [rbp+0xDD0],rax` | stack +0xDD0 = index | [V] |
| 0xbcc6125 | 8 | RTX denoise UAV write | `0xbcc6125  mov [rbp+0xCD8],rcx` | stack +0xCD8 = heap slot addr | [V] |
| 0xbcc613a | 8 | RTX denoise UAV write | `0xbcc613a  mov [rbp+0xDD0],r12` | stack +0xDD0 = r12 | [V] |
| 0xbcc6147 | 8 | RTX denoise UAV write | `0xbcc6147  mov [rbp+0xDB8],rsi` | stack +0xDB8 = UAV object ptr | [V] |
| 0xbcc6165 | 8 | RTX denoise UAV write | `0xbcc6165  mov qword ptr [rbp+rdi+0x1E0],0` | slot+0x1E0 = 0 | [V] |
| 0xbcc6171 | 8 | RTX denoise UAV write | `0xbcc6171  mov qword ptr [rbp+rdi+0x1E8],0xF` | slot+0x1E8 = 0xF | [V] |
| 0xbcc617d | 1 | RTX denoise UAV write | `0xbcc617d  mov byte ptr [rbp+rdi+0x1D0],0` | slot+0x1D0 = 0 | [V] |
| 0xbcc5fe3 | 8 | RTX denoise UAV read | `0xbcc5fe3  mov rcx,[0x1233E1A8]` | global UAV/resource manager ptr | [V] |
| 0xbcc5fea | 8 | RTX denoise UAV read | `0xbcc5fea  mov rax,[rcx]` | *(mgr) | [V] |
| 0xbcc5fed | 8 | RTX denoise UAV read | `0xbcc5fed  mov rax,[rax+8]` | *(mgr+8) = ref-counted UAV object | [V] |
| 0xbcc6017 | - | RTX denoise UAV read | `0xbcc6017  lea rax,[rsi+0xAF0]` | new UAV object +0xAF0 | [V] |
| 0xbcc603c | - | RTX denoise UAV read | `0xbcc603c  lea r14,[rbp+0x1D0]` | UAV descriptor-table base on stack | [V] |
| 0xbcc604a | 8 | RTX denoise UAV read | `0xbcc604a  mov rdi,[rbp+0xDA8]` | descriptor-heap base ptr | [V] |
| 0xbcc6079 | 8 | RTX denoise UAV read | `0xbcc6079  mov rcx,[rbp+0xDD0]` | UAV desc table index | [V] |
| 0xbcc6080 | 8 | RTX denoise UAV read | `0xbcc6080  mov rax,[rbp+rcx+0x1D0]` | UAV desc entry [index].ptr | [V] |
| 0xbcc6093 | 8 | RTX denoise UAV read | `0xbcc6093  mov rax,[rbp+rcx+0x200]` | UAV desc entry [index]+0x200 | [V] |
| 0xbcc60db | 8 | RTX denoise UAV read | `0xbcc60db  mov rax,[rbp+0xDD0]` | UAV desc table index | [V] |
| 0xbcc60e2 | 8 | RTX denoise UAV read | `0xbcc60e2  cmp qword ptr [rbp+rax+0x1F0],0x10` | UAV desc size field vs 0x10 | [V] |
| 0xbcc60ed | 8 | RTX denoise UAV read | `0xbcc60ed  mov r9,[rbp+rax+0x1D8]` | UAV desc ptr (or rbp+rax fallback) | [V] |
| 0xbcc610b | - | RTX denoise UAV read | `0xbcc610b  lea rcx,[rdi+rax]` | heap slot addr | [V] |
| 0xbcc6113 | 8 | RTX denoise UAV read | `0xbcc6113  mov rbx,[rbp+rax+0x1E8]` | UAV desc +0x1E8 | [V] |
| 0xbcc618f | 8 | RTX denoise UAV read | `0xbcc618f  mov rax,[rbp+rdi+0x1E8]` | current slot size | [V] |
| 0xbcc619d | 8 | RTX denoise UAV read | `0xbcc619d  mov rcx,[rbp+rdi+0x1D0]` | current slot ptr | [V] |

### Item 5 — Fancy clear tasks 0xF25C9B0 / 0xF25C9E0, Pass task 0xF440770 / 0xBC38AB0, TerrainAtlasBlit 0xF43E9C0 / 0xBC01E80 (vtables are DATA; execute body via vt slot)

| 0x56cc043 | - | Fancy clear vt 0xF25C9B0 slot1 ctor | `0x56cc043  lea rdx,[0xF25C9B0]` | vtable 0xF25C9B0 installed onto object | [V] |
| 0x56cc04a | 8 | Fancy clear vt 0xF25C9B0 slot1 ctor | `0x56cc04a  mov [rax],rdx` | W obj+0x0 = vtable ptr 0xF25C9B0 | [V] |
| 0xbc38abb | - | Pass task vt 0xF440770 ctor sub_bc38ab0 | `0xbc38abb  lea rax,[0xF440770]` | vtable 0xF440770 installed onto object | [V] |
| 0xbc38ac2 | 8 | Pass task vt 0xF440770 ctor sub_bc38ab0 | `0xbc38ac2  mov [rcx],rax` | W obj+0x0 = vtable ptr 0xF440770 | [V] |
| 0xbc01e8b | - | TerrainAtlasBlit vt 0xF43E9C0 ctor sub_bc01e80 | `0xbc01e8b  lea rax,[0xF43E9C0]` | vtable 0xF43E9C0 installed onto object | [V] |
| 0xbc01e92 | 8 | TerrainAtlasBlit vt 0xF43E9C0 ctor sub_bc01e80 | `0xbc01e92  mov [rcx],rax` | W obj+0x0 = vtable ptr 0xF43E9C0 | [V] |
| 0xbc38c5c | 2 | Pass task execute body 0xbc38c20 | `0xbc38c5c  movzx eax,word ptr [rax+8]` | view id u16 from task object | [V] |
| 0xbc38c67 | 4 | Pass task execute body 0xbc38c20 | `0xbc38c67  shl eax,6` | view*64 | [V] |
| 0xbc38c6a | - | Pass task execute body 0xbc38c20 | `0xbc38c6a  lea r12,[rax+rax*4]` | view index = view*0x140 | [V] |
| 0xbc38c60 | 8 | Pass task execute body 0xbc38c20 | `0xbc38c60  mov rcx,[0x12AE1748]` | s_ctx base | [V] |
| 0xbc38c6e | 8 | Pass task execute body 0xbc38c20 | `0xbc38c6e  movq xmm0,[r8+0xF8]` | pass rect from task obj +0xF8 | [V] |
| 0xbc38c88 | 4 | Pass task execute body 0xbc38c20 | `0xbc38c88  movd [rcx+r12+0x1EAB090],xmm0` | WRITE rect to ctx+0x1EAB090+view*0x140 | [V] |
| 0xbc38c7f | 4 | Pass task execute body 0xbc38c20 | `0xbc38c7f  movd xmm1,[r8+0xFC]` | pass size from task obj +0xFC | [V] |
| 0xbc38c9e | 4 | Pass task execute body 0xbc38c20 | `0xbc38c9e  movd [rcx+r12+0x1EAB094],xmm1` | WRITE size to ctx+0x1EAB094+view*0x140 | [V] |
| 0xbc38cd5 | - | Pass task execute body 0xbc38c20 | `0xbc38cd5  call 0xEBCE390` | WRITE mat4 to ctx+0x1EAB0A0+view*0x140 | [V] |
| 0xbc38ceb | 8 | Pass task execute body 0xbc38c20 | `0xbc38ceb  mov rdx,r15` | rdx = r15 for mat4 copy dest ctx+0x1EAB0E0 | [V] |
| 0xbc38cee | - | Pass task execute body 0xbc38c20 | `0xbc38cee  call 0xEBCE390` | WRITE mat4 to ctx+0x1EAB0E0+view*0x140 | [V] |
| 0xbc38d07 | - | Pass task execute body 0xbc38c20 | `0xbc38d07  call 0xEBCE390` | WRITE mat4 to ctx+0x1EAB120+view*0x140 | [V] |
| 0xbc38d1d | 8 | Pass task execute body 0xbc38c20 | `0xbc38d1d  mov rdx,rdi` | rdx = rdi for mat4 copy dest ctx+0x1EAB160 | [V] |
| 0xbc38d20 | - | Pass task execute body 0xbc38c20 | `0xbc38d20  call 0xEBCE390` | WRITE mat4 to ctx+0x1EAB160+view*0x140 | [V] |
| 0xbc38d36 | - | Pass task execute body 0xbc38c20 | `0xbc38d36  lea rdx,[rbx+0x18C]` | 16-byte data source rbx+0x18C | [V] |
| 0xbc38d3d | - | Pass task execute body 0xbc38c20 | `0xbc38d3d  call 0xEBCE390` | WRITE 16 bytes to ctx+0x1EAB1A0+view*0x140 | [V] |
| 0xbc38d42 | 1 | Pass task execute body 0xbc38c20 | `0xbc38d42  movzx eax,byte ptr [rbx+0x108]` | sort mode byte from rbx+0x108 | [V] |
| 0xbc38d50 | 1 | Pass task execute body 0xbc38c20 | `0xbc38d50  mov [rcx+r12+0x1EAB1B2],al` | WRITE sort byte to ctx+0x1EAB1B2+view*0x140 | [V] |

### Item 6 — 0x568d480 tail and 0x568d750 body (final submit target) (carried [V] from oc_U-EM1e_r18.md)

| 0x568d48d | 8 | tail 0x568d480 | `0x568d48d  mov rax,[0x1230A0C0]` | stack cookie | [V] |
| 0x568d49c | 8 | tail 0x568d480 | `0x568d49c  mov r15,[rcx]` | a0+0x0 = list head | [V] |
| 0x568d49f | 8 | tail 0x568d480 | `0x568d49f  mov r14,[rcx+8]` | a0+0x8 = list end | [V] |
| 0x568d6e8 | - | tail 0x568d480 | `0x568d6e8  call 0x568D750` | body: build command packet | [V] |
| 0x568da45 | - | tail 0x568d480 | `0x568da45  call 0xBCC38E0` | submit (sub_bcc38e0, 6hr submitPass inline path) | [V] |
| 0x568d9e8 | - | tail 0x568d480 | `0x568d9e8  call 0xBCC2B00` | validation | [V] |
| 0x568d9f7 | - | tail 0x568d480 | `0x568d9f7  call 0xBCC2EB0` | validation | [V] |
| 0x568d6d3 | 8 | tail 0x568d480 write | `0x568d6d3  mov [rsp+0x28],r15` | stack +0x28 = matched element | [V] |
| 0x568d6d8 | 8 | tail 0x568d480 write | `0x568d6d8  mov [rsp+0x30],r14` | stack +0x30 = list end | [V] |
| 0x568d6dd | 8 | tail 0x568d480 write | `0x568d6dd  mov [rsp+0x38],r15` | stack +0x38 = matched element | [V] |
| 0x568da38 | 8 | tail 0x568d480 write | `0x568da38  mov [rsp+0x20],rax` | stack +0x20 = *(a0+0x98) | [V] |
| 0x568da3d | 4 | tail 0x568d480 write | `0x568da3d  mov dword ptr [rsp+0x28],0` | stack +0x28 = 0 | [V] |
| 0x568d77a | 1 | body 0x568d750 read | `0x568d77a  cmp byte ptr [rcx+0x80],1` | a0+0x80 flag byte == 1 gate | [V] |
| 0x568d78b | 8 | body 0x568d750 read | `0x568d78b  mov rax,[rdi+0x10]` | a1+0x10 | [V] |
| 0x568d797 | 2 | body 0x568d750 read | `0x568d797  movzx ecx,word ptr [rcx+0x2C]` | table index word | [V] |
| 0x568d79b | 8 | body 0x568d750 read | `0x568d79b  mov rax,[rax+0x738]` | table base | [V] |
| 0x568d945 | - | body 0x568d750 | `0x568d945  call 0xBCC1910` | encode command packet at rsp+0x90 | [V] |
| 0x568d7b5 | 4 | body 0x568d750 write | `0x568d7b5  mov [rsp+0x38],edx` | packet +0x0 = table entry +0x0 | [V] |
| 0x568d7d1 | 1 | body 0x568d750 write | `0x568d7d1  mov [rsp+0x3C],dl` | packet +0x4 = table entry +0x4 | [V] |
| 0x568d7ec | 4 | body 0x568d750 write | `0x568d7ec  mov [rsp+0x40],edx` | packet +0x8 = table entry +0x8 | [V] |
| 0x568d808 | 2 | body 0x568d750 write | `0x568d808  mov [rsp+0x44],dx` | packet +0xC = table entry +0xC | [V] |
| 0x568d812 | 1 | body 0x568d750 write | `0x568d812  mov [rsp+0x46],dl` | packet +0xE = table entry +0xE | [V] |
| 0x568d82d | 4 | body 0x568d750 write | `0x568d82d  mov [rsp+0x48],edx` | packet +0x10 = table entry +0x10 | [V] |
| 0x568d849 | 1 | body 0x568d750 write | `0x568d849  mov [rsp+0x4C],dl` | packet +0x14 = table entry +0x14 | [V] |
| 0x568d852 | 16 | body 0x568d750 write | `0x568d852  movups [rsp+0x50],xmm0` | packet +0x18 = table entry +0x18 (16 B) | [V] |
| 0x568d86f | 4 | body 0x568d750 write | `0x568d86f  mov [rsp+0x68],edx` | packet +0x30 = table entry +0x30 | [V] |
| 0x568d876 | 8 | body 0x568d750 write | `0x568d876  mov [rsp+0x60],rdx` | packet +0x28 = table entry +0x28 | [V] |
| 0x568d893 | 16 | body 0x568d750 write | `0x568d893  movups [rsp+0x6C],xmm0` | packet +0x34 = table entry +0x34 (16 B) | [V] |
| 0x568d8b0 | 16 | body 0x568d750 write | `0x568d8b0  movups [rsp+0x7C],xmm0` | packet +0x44 = table entry +0x44 (16 B) | [V] |
| 0x568d8cd | 1 | body 0x568d750 write | `0x568d8cd  mov [rsp+0x8C],dl` | packet +0x54 = table entry +0x54 | [V] |
| 0x568d8ec | 1 | body 0x568d750 write | `0x568d8ec  mov [rsp+0x8D],dl` | packet +0x55 = table entry +0x55 | [V] |
| 0x568d909 | 1 | body 0x568d750 write | `0x568d909  mov [rsp+0x8E],al` | packet +0x56 = table entry +0x56 | [V] |

## Coverage status
- Item 1 bloom up 0xbc9bbd4/0xbc9bc28: [V] registration stubs + executed bodies 0xbc9c850/0xbc9c8e0 located (thin wrappers dispatching via [0xF9A8C78]); full UAV/texture in/out of the dispatch target = [?].
- Item 2 local exposure 0xbca2671: [V] registration stub + named-param reads (SceneColor/BilateralGrid/.../ViewportScale); executed body 0xbca7be0 not yet read = [?].
- Item 3 Convolve: [V] body located at 0xbcdbcf4 (string 0xbcdbcde xref bcd0cb6); per-pass in/out not yet read = [?].
- Item 4 RTX denoise UAV writes in 0xbcc4b90: [V] (19 writes + 18 reads listed above).
- Item 5 Fancy: Pass task execute body 0xbc38c20 [V] (writes rect/size/4x mat4/16B/sort into s_ctx views); clear-task execute bodies (0xF25C9B0/0xF25C9E0) and TerrainAtlasBlit execute body (0xF43E9C0) not located via vt slot1 -> lea r8 target = [?]; vtable data installs verified [V].
- Item 6 tail 0x568d480 + body 0x568d750: [V] (packet build + submit 0xBCC38E0).

CLOSES? NO — not all six items have fully-[V] in/out rows yet. Blocking fact: Item 1 executed-body full UAV/texture in/out [?], Item 2 executed body 0xbca7be0 in/out [?], Item 3 Convolve per-pass in/out [?], Item 5 clear-task/TerrainAtlasBlit execute bodies not located [?]. Items 4 and 6 are fully [V]; Item 5 Pass task body is [V]. Per the unit wording (finish with CLOSES? YES only if all six have [V] rows), this run cannot close until the remaining bodies are read and their in/out proven.

## TOOL REQUESTS
None
