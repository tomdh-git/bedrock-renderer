## NEXT
DONE

Bloom down / bloom up registration sites (hash-static, NOT executed bodies — per r4 the executed body is ScreenDraw 0xbc04dc0).
Each row = offset | size | R/W/C | verbatim `0xRVA  instr` | meaning | tag.

| offset | size | R/W/C | instr | meaning | tag |
| 0xbc99739 | 8 | R | `0xbc99739  mov rdx,0x34E743CD5E04564D` | FNV-1 hash constant loaded for bloom-down pass registration | [V] |
| 0xbc99743 | call | C | `0xbc99743  call 0x76AD00` | hash-static registration call | [V] |
| 0xbc99749 | lea | R | `0xbc99749  lea rcx,[0xBC9AC80]` | body function 0xBC9AC80 passed to registration | [V] |
| 0xbc99750 | call | C | `0xbc99750  call 0xE935740` | register pass body | [V] |
| 0xbc99794 | 8 | R | `0xbc99794  mov rdx,0x714FFC3B4FD51617` | FNV-1 hash constant loaded for bloom-down pass registration | [V] |
| 0xbc9979e | call | C | `0xbc9979e  call 0x76AD00` | hash-static registration call | [V] |
| 0xbc997a4 | lea | R | `0xbc997a4  lea rcx,[0xBC9AD10]` | body function 0xBC9AD10 passed to registration | [V] |
| 0xbc997ab | call | C | `0xbc997ab  call 0xE935740` | register pass body | [V] |
| 0xbc9978d | lea | R | `0xbc9978d  lea r8,[0xF5D9717]` | string "ThresholdedDownSample" (bloom down pass name) | [V] |
| 0xbc997eb | lea | R | `0xbc997eb  lea rax,[0xF59A75E]` | string "Bloom" (bloom category) | [V] |
| 0xbc99850 | lea | R | `0xbc99850  lea rdx,[0xF5C6EC9]` | string "BlurPyramidTexture" | [V] |
| 0xbc998c2 | lea | R | `0xbc998c2  lea rdx,[0xF5E7C75]` | string "AverageLuminance" | [V] |
| 0xbc9bbd4 | 8 | R | `0xbc9bbd4  mov rdx,0xF91FF9E312C7E556` | FNV-1 hash constant loaded for bloom-up pass registration | [V] |
| 0xbc9bbde | call | C | `0xbc9bbde  call 0x76AD00` | hash-static registration call | [V] |
| 0xbc9bbe4 | lea | R | `0xbc9bbe4  lea rcx,[0xBC9C850]` | body function 0xBC9C850 passed to registration | [V] |
| 0xbc9bbeb | call | C | `0xbc9bbeb  call 0xE935740` | register pass body | [V] |
| 0xbc9bbf0 | lea | R | `0xbc9bbf0  lea rcx,[0x12AE1E88]` | pass slot address | [V] |
| 0xbc9bbf7 | call | C | `0xbc9bbf7  call 0xE938D70` | register pass slot | [V] |
| 0xbc9bc21 | lea | R | `0xbc9bc21  lea r8,[0xF5ED9E9]` | string "BloomBlend" (bloom-up pass name) | [V] |
| 0xbc9bc28 | 8 | R | `0xbc9bc28  mov rdx,0x7ADA5C0EF1420F87` | FNV-1 hash constant loaded for BloomBlend registration | [V] |
| 0xbc9bc32 | call | C | `0xbc9bc32  call 0x76AD00` | hash-static registration call | [V] |
| 0xbc9bc38 | lea | R | `0xbc9bc38  lea rcx,[0xBC9C8E0]` | body function 0xBC9C8E0 passed to registration | [V] |
| 0xbc9bc3f | call | C | `0xbc9bc3f  call 0xE935740` | register pass body | [V] |
| 0xbc9bc44 | lea | R | `0xbc9bc44  lea rcx,[0x12AE1EC0]` | pass slot address | [V] |
| 0xbc9bc4b | call | C | `0xbc9bc4b  call 0xE938D70` | register pass slot | [V] |
| 0xbc9bc78 | lea | R | `0xbc9bc78  lea rax,[0xF59A75E]` | string "Bloom" (bloom category/group name) | [V] |
| 0xbc9bc91 | lea | R | `0xbc9bc91  lea rcx,[0x12AE1EC8]` | bloom pass-group slot address | [V] |
| 0xbc9bca6 | call | C | `0xbc9bca6  call 0x5668AC0` | pass-group registration call | [V] |
| 0xbc9bcd6 | lea | R | `0xbc9bcd6  lea rdx,[0xF5AD73F]` | string "HDRi" (bloom-up named param block) | [V] |
| 0xbc9bce7 | call | C | `0xbc9bce7  call 0x79580` | named-param block registration call | [V] |
| 0xbc9bd48 | lea | R | `0xbc9bd48  lea rdx,[0xF5C6EC9]` | string "BlurPyramidTexture" (bloom-up named param block) | [V] |
| 0xbc9bd59 | call | C | `0xbc9bd59  call 0x79580` | named-param block registration call | [V] |
| 0xbc9bdba | lea | R | `0xbc9bdba  lea rdx,[0xF550D5E]` | string "BloomParams" (bloom-up named param block) | [V] |
| 0xbc9bdcb | call | C | `0xbc9bdcb  call 0x79580` | named-param block registration call | [V] |
| 0xbc9be2c | lea | R | `0xbc9be2c  lea rdx,[0xF5DE7ED]` | string "ViewportScale" (bloom-up named param block) | [V] |
| 0xbc9be3d | call | C | `0xbc9be3d  call 0x79580` | named-param block registration call | [V] |
| 0xbc9be9e | lea | R | `0xbc9be9e  lea rdx,[0xF7E41CA]` | string "Color0" (bloom-up named param block) | [V] |
| 0xbc9beaf | call | C | `0xbc9beaf  call 0x79580` | named-param block registration call | [V] |

Local exposure / local-exposure pass registration site (hash-static, NOT an executed body — per r4 the executed body is ScreenDraw 0xbc04dc0).
Each row = offset | size | R/W/C | verbatim `0xRVA  instr` | meaning | tag.

| offset | size | R/W/C | instr | meaning | tag |
| 0xbca2671 | 8 | R | `0xbca2671  mov rdx,0x15C5632A1EBCD723` | FNV-1 hash constant loaded for local-exposure pass registration | [V] |
| 0xbca267b | call | C | `0xbca267b  call 0x76AD00` | hash-static registration call | [V] |
| 0xbca2681 | lea | R | `0xbca2681  lea rcx,[0xBCA7BE0]` | body function 0xBCA7BE0 passed to registration | [V] |
| 0xbca2688 | call | C | `0xbca2688  call 0xE935740` | register pass body | [V] |
| 0xbca268d | lea | R | `0xbca268d  lea rcx,[0x12AE2040]` | pass slot address | [V] |
| 0xbca2694 | call | C | `0xbca2694  call 0xE938D70` | register pass slot | [V] |
| 0xbca26c3 | lea | R | `0xbca26c3  lea rdx,[0xF563C04]` | string "SceneColor" (local-exposure named param block) | [V] |
| 0xbca26d4 | call | C | `0xbca26d4  call 0x79580` | named-param block registration call | [V] |
| 0xbca273e | lea | R | `0xbca273e  lea rdx,[0xF5F026C]` | string "BilateralGrid" (local-exposure named param block) | [V] |
| 0xbca274f | call | C | `0xbca274f  call 0x79580` | named-param block registration call | [V] |
| 0xbca27b9 | lea | R | `0xbca27b9  lea rdx,[0xF524D6E]` | string "FilteredBilateralGridOutput" (local-exposure named param block) | [V] |
| 0xbca27ca | call | C | `0xbca27ca  call 0x79580` | named-param block registration call | [V] |

Executed body for bloom down, bloom up and local exposure (and all bloom/local-exposure passes): shared ScreenDraw body 0xbc04dc0 — vtable slot 2 of ScreenDraw std::function vtable 0xF440710 tail-jumps to 0xbc04dc0 (rdis vt; BGFX_MAP 1730/1734).
[V] ScreenDraw std::function vtable 0xF440710 (rdis vt 0xF440710): slot 0 _Copy = sub_bc380c0 (`mov rax,rdx`), slot 1 _Move = sub_bc380c0, slot 2 _Do_call = sub_bc380d0 (`0xbc380d0  add rcx,8` / `0xbc380d4  jmp 0xBC04DC0`) = tail-jump to ScreenDraw body 0xbc04dc0; slot 3 _Target_type = sub_bc380e0. BGFX_MAP 1730/1734: fullscreen post passes (ColorPostProcess builder 0xbbbcb20 -> declareScreenPass 0xbbbd3d0 -> buildScreenPass 0xbc37320 -> registerPass 0xbc37ca0) run the shared ScreenDraw body.
IN: r8 = pass record (name std::string at +0x268, rect +0x168, size +0x16C); rbx = rdx = a1, view id = u16 at [rbx+8]+8; s_ctx = [0x12AE1748].  [V: `0xbc04dee  mov rsi,r8`; `0xbc04df1  mov rbx,rdx`; `0xbc04dff  movzx eax,word ptr [rax+8]`; `0xbc04e03  mov rcx,[0x12AE1748]`; `0xbc04e11  movq xmm0,[r8+0x168]`; `0xbc04e22  movd xmm1,[r8+0x16C]`]
OUT (verbatim from disassembly 0xbc04dc0, shared by both bloom passes — rect, 4 mat4, 16-byte vec, sort byte written into s_ctx->views[viewId*0x140]):
| offset | size | R/W/C | instr | meaning | tag |
| 0xbc04dee | 8 | R | `0xbc04dee  mov rsi,r8` | pass record (a2) -> rsi | [V] |
| 0xbc04df1 | 8 | R | `0xbc04df1  mov rbx,rdx` | a1 -> rbx | [V] |
| 0xbc04dfb | 8 | R | `0xbc04dfb  mov rax,[rbx+8]` | a1+8 | [V] |
| 0xbc04dff | 2 | R | `0xbc04dff  movzx eax,word ptr [rax+8]` | view id u16 at *(a1+8)+8 | [V] |
| 0xbc04e03 | 8 | R | `0xbc04e03  mov rcx,[0x12AE1748]` | s_ctx base | [V] |
| 0xbc04e0a | 4 | R | `0xbc04e0a  shl eax,6` | view*64 | [V] |
| 0xbc04e0d | 4 | R | `0xbc04e0d  lea rdi,[rax+rax*4]` | view index = view*0x140 | [V] |
| 0xbc04e11 | 8 | R | `0xbc04e11  movq xmm0,[r8+0x168]` | pass rect from record +0x168 | [V] |
| 0xbc04e22 | 4 | R | `0xbc04e22  movd xmm1,[r8+0x16C]` | pass size from record +0x16C | [V] |
| 0xbc04e2b | 16 | W | `0xbc04e2b  movd [rcx+rdi+0x1EAB090],xmm0` | WRITE rect to ViewRecord ctx+0x1EAB090+view*0x140 | [V] |
| 0xbc04e40 | 4 | W | `0xbc04e40  movd [rcx+rdi+0x1EAB094],xmm1` | WRITE size to ViewRecord ctx+0x1EAB094+view*0x140 | [V] |
| 0xbc04e76 | call | C | `0xbc04e76  call 0xEBCE390` | WRITE mat4 to ctx+0x1EAB0A0+view*0x140 | [V] |
| 0xbc04e8f | call | C | `0xbc04e8f  call 0xEBCE390` | WRITE mat4 to ctx+0x1EAB0E0+view*0x140 | [V] |
| 0xbc04ea8 | call | C | `0xbc04ea8  call 0xEBCE390` | WRITE mat4 to ctx+0x1EAB120+view*0x140 | [V] |
| 0xbc04ec1 | call | C | `0xbc04ec1  call 0xEBCE390` | WRITE mat4 to ctx+0x1EAB160+view*0x140 | [V] |
| 0xbc04ede | call | C | `0xbc04ede  call 0xEBCE390` | WRITE 16 bytes to ctx+0x1EAB1A0+view*0x140 | [V] |
| 0xbc04ee3 | 1 | R | `0xbc04ee3  movzx eax,byte ptr [rsi+0x178]` | pass sort mode from record +0x178 | [V] |
| 0xbc04ef1 | 1 | W | `0xbc04ef1  mov [rcx+rdi+0x1EAB1B2],al` | WRITE sort mode byte to ctx+0x1EAB1B2+view*0x140 | [V] |

Tail 0x568d480 / body 0x568d750 — command-packet build + submit tail (rdis dis 0x568d480 and 0x568d750). sub_568d480 iterates a record list (a0=[rcx] head, [rcx+8] end, 0x18 stride), looks each element up in a keyed table (index = word at element+0x8+0x2C; table base at element+0x10+0x738; stride 0x58; element base = a0+0x0+idx*0x18), and on a match calls body sub_568d750 to build a command packet at rsp+0x90, then calls sub_bcc2b00/sub_bcc2eb00 validation and sub_bcc38e0 (submit, 6hr). sub_568d750 (a0=rcx/rsi=pass record, a1=rdx/rdi=table record) conditionally copies fields from &table[index] into rsp+0x38..rsp+0x8E gated by flag bytes at a0+0xC/0x11/0x18/0x1F/0x24/0x3C/0x4C/0x60, then calls sub_bcc1910 (encode) to write the packet.

Body 0x568d750 IN (reads):
| offset | size | R/W/C | instr | meaning | tag |
| 0x568d77a | 1 | R | `0x568d77a  cmp byte ptr [rcx+0x80],1` | a0+0x80 flag byte == 1 gate | [V] |
| 0x568d78b | 8 | R | `0x568d78b  mov rax,[rdi+0x10]` | a1+0x10 | [V] |
| 0x568d78f | 8 | R | `0x568d78f  mov rcx,[rax+8]` | *(a1+0x10)+0x8 | [V] |
| 0x568d793 | 8 | R | `0x568d793  mov rax,[rax+0x10]` | *(a1+0x10)+0x10 | [V] |
| 0x568d797 | 2 | R | `0x568d797  movzx ecx,word ptr [rcx+0x2C]` | *(*(a1+0x10)+0x8)+0x2C → table index word | [V] |
| 0x568d79b | 8 | R | `0x568d79b  mov rax,[rax+0x738]` | *(*(a1+0x10)+0x10)+0x738 → table base | [V] |
| 0x568d7aa | 1 | R | `0x568d7aa  cmp byte ptr [rsi+0xC],0` | a0+0xC flag (select table entry vs a0+8 fallback) | [V] |
| 0x568d7b2 | 4 | R | `0x568d7b2  mov edx,[r8]` | table entry +0x0 | [V] |
| 0x568d7b9 | lea | R | `0x568d7b9  lea rdx,[rsi+0x10]` | a0+0x10 fallback addr | [V] |
| 0x568d7cd | 1 | R | `0x568d7cd  movzx edx,byte ptr [r8]` | table entry +0x4 (or a0+0x10) | [V] |
| 0x568d7d5 | lea | R | `0x568d7d5  lea rdx,[rsi+0x14]` | a0+0x14 fallback addr | [V] |
| 0x568d7e9 | 4 | R | `0x568d7e9  mov edx,[r8]` | table entry +0x8 (or a0+0x14) | [V] |
| 0x568d7f0 | lea | R | `0x568d7f0  lea rdx,[rsi+0x1C]` | a0+0x1C fallback addr | [V] |
| 0x568d804 | 2 | R | `0x568d804  movzx edx,word ptr [r8]` | table entry +0xC (or a0+0x1C) | [V] |
| 0x568d80d | 1 | R | `0x568d80d  movzx edx,byte ptr [r8+2]` | table entry +0xE | [V] |
| 0x568d816 | lea | R | `0x568d816  lea rdx,[rsi+0x20]` | a0+0x20 fallback addr | [V] |
| 0x568d82a | 4 | R | `0x568d82a  mov edx,[r8]` | table entry +0x10 (or a0+0x20) | [V] |
| 0x568d831 | lea | R | `0x568d831  lea rdx,[rsi+0x28]` | a0+0x28 fallback addr | [V] |
| 0x568d845 | 1 | R | `0x568d845  movzx edx,byte ptr [r8]` | table entry +0x14 (or a0+0x28) | [V] |
| 0x568d84d | 16 | R | `0x568d84d  movups xmm0,[r8+4]` | table entry +0x18 (16 B) (or a0+0x2C) | [V] |
| 0x568d857 | lea | R | `0x568d857  lea rdx,[rsi+0x40]` | a0+0x40 fallback addr | [V] |
| 0x568d86b | 4 | R | `0x568d86b  mov edx,[r8+8]` | table entry +0x30 (or a0+0x48) | [V] |
| 0x568d873 | 8 | R | `0x568d873  mov rdx,[r8]` | table entry +0x28 (or a0+0x40) | [V] |
| 0x568d87b | lea | R | `0x568d87b  lea rdx,[rsi+0x50]` | a0+0x50 fallback addr | [V] |
| 0x568d88f | 16 | R | `0x568d88f  movups xmm0,[r8]` | table entry +0x34 (16 B) (or a0+0x50) | [V] |
| 0x568d898 | lea | R | `0x568d898  lea rdx,[rsi+0x64]` | a0+0x64 fallback addr | [V] |
| 0x568d8ac | 16 | R | `0x568d8ac  movups xmm0,[r8]` | table entry +0x44 (16 B) (or a0+0x64) | [V] |
| 0x568d8b5 | lea | R | `0x568d8b5  lea rdx,[rsi+0x78]` | a0+0x78 fallback addr | [V] |
| 0x568d8c9 | 1 | R | `0x568d8c9  movzx edx,byte ptr [r8]` | table entry +0x54 (or a0+0x78) | [V] |
| 0x568d8d4 | lea | R | `0x568d8d4  lea rdx,[rsi+0x7A]` | a0+0x7A fallback addr | [V] |
| 0x568d8e8 | 1 | R | `0x568d8e8  movzx edx,byte ptr [r8]` | table entry +0x55 (or a0+0x7A) | [V] |
| 0x568d8f3 | lea | R | `0x568d8f3  lea rdx,[rsi+0x7C]` | a0+0x7C fallback addr | [V] |
| 0x568d906 | 1 | R | `0x568d906  movzx eax,byte ptr [rax]` | table entry +0x56 (or a0+0x7C) | [V] |
| 0x568d945 | call | C | `0x568d945  call 0xBCC1910` | encode command packet (sub_bcc1910) at rsp+0x90 from rsp+0x38 | [V] |

Body 0x568d750 OUT (writes to stack command packet):
| offset | size | R/W/C | instr | meaning | tag |
| 0x568d7b5 | 4 | W | `0x568d7b5  mov [rsp+0x38],edx` | packet +0x0 = table entry +0x0 | [V] |
| 0x568d7d1 | 1 | W | `0x568d7d1  mov [rsp+0x3C],dl` | packet +0x4 = table entry +0x4 | [V] |
| 0x568d7ec | 4 | W | `0x568d7ec  mov [rsp+0x40],edx` | packet +0x8 = table entry +0x8 | [V] |
| 0x568d808 | 2 | W | `0x568d808  mov [rsp+0x44],dx` | packet +0xC = table entry +0xC | [V] |
| 0x568d812 | 1 | W | `0x568d812  mov [rsp+0x46],dl` | packet +0xE = table entry +0xE | [V] |
| 0x568d82d | 4 | W | `0x568d82d  mov [rsp+0x48],edx` | packet +0x10 = table entry +0x10 | [V] |
| 0x568d849 | 1 | W | `0x568d849  mov [rsp+0x4C],dl` | packet +0x14 = table entry +0x14 | [V] |
| 0x568d852 | 16 | W | `0x568d852  movups [rsp+0x50],xmm0` | packet +0x18 = table entry +0x18 (16 B) | [V] |
| 0x568d86f | 4 | W | `0x568d86f  mov [rsp+0x68],edx` | packet +0x30 = table entry +0x30 | [V] |
| 0x568d876 | 8 | W | `0x568d876  mov [rsp+0x60],rdx` | packet +0x28 = table entry +0x28 | [V] |
| 0x568d893 | 16 | W | `0x568d893  movups [rsp+0x6C],xmm0` | packet +0x34 = table entry +0x34 (16 B) | [V] |
| 0x568d8b0 | 16 | W | `0x568d8b0  movups [rsp+0x7C],xmm0` | packet +0x44 = table entry +0x44 (16 B) | [V] |
| 0x568d8cd | 1 | W | `0x568d8cd  mov [rsp+0x8C],dl` | packet +0x54 = table entry +0x54 | [V] |
| 0x568d8ec | 1 | W | `0x568d8ec  mov [rsp+0x8D],dl` | packet +0x55 = table entry +0x55 | [V] |
| 0x568d909 | 1 | W | `0x568d909  mov [rsp+0x8E],al` | packet +0x56 = table entry +0x56 | [V] |

Tail 0x568d480 IN (reads):
| offset | size | R/W/C | instr | meaning | tag |
| 0x568d48d | 8 | R | `0x568d48d  mov rax,[0x1230A0C0]` | stack cookie | [V] |
| 0x568d49c | 8 | R | `0x568d49c  mov r15,[rcx]` | a0+0x0 = list head | [V] |
| 0x568d49f | 8 | R | `0x568d49f  mov r14,[rcx+8]` | a0+0x8 = list end | [V] |
| 0x568d4f9 | 8 | R | `0x568d4f9  mov rax,[r15+8]` | *(a0+0x0)+0x8+idx (element ptr A) | [V] |
| 0x568d502 | 8 | R | `0x568d502  mov rdx,[r15+0x10]` | *(a0+0x0)+0x10+idx (element ptr B) | [V] |
| 0x568d50b | 1 | R | `0x568d50b  test byte ptr [rax+1],0x40` | **(a0+0x0)+0x8+idx+1 flag | [V] |
| 0x568d524 | 4 | R | `0x568d524  mov edx,[rcx]` | match key dword | [V] |
| 0x568d526 | 8 | R | `0x568d526  mov r8,[rax+8]` | element+0x18+0x8 | [V] |
| 0x568d52a | 8 | R | `0x568d52a  mov r9,[rax+0x10]` | element+0x18+0x10 | [V] |
| 0x568d52e | 2 | R | `0x568d52e  movzx r10d,word ptr [r8+0x2C]` | element+0x18+0x8+0x2C → index word | [V] |
| 0x568d533 | 8 | R | `0x568d533  mov r8,[r9+0x738]` | element+0x18+0x10+0x738 → table base | [V] |
| 0x568d53e | 4 | R | `0x568d53e  cmp [r8+r9],edx` | table[index] vs match key | [V] |
| 0x568d54b | 1 | R | `0x568d54b  movzx r9d,byte ptr [r8+4]` | table entry +0x4 (compare field) | [V] |
| 0x568d55a | 4 | R | `0x568d55a  mov r9d,[r8+8]` | table entry +0x8 | [V] |
| 0x568d568 | 1 | R | `0x568d568  movzx r9d,byte ptr [r8+0xC]` | table entry +0xC | [V] |
| 0x568d577 | 1 | R | `0x568d577  movzx r9d,byte ptr [r8+0xD]` | table entry +0xD | [V] |
| 0x568d586 | 1 | R | `0x568d586  movzx r9d,byte ptr [r8+0xE]` | table entry +0xE | [V] |
| 0x568d595 | 4 | R | `0x568d595  mov r9d,[r8+0x10]` | table entry +0x10 | [V] |
| 0x568d5a3 | 1 | R | `0x568d5a3  movzx r9d,byte ptr [r8+0x14]` | table entry +0x14 | [V] |
| 0x568d5b2 | 4 | R | `0x568d5b2  movss xmm0,[r8+0x18]` | table entry +0x18 | [V] |
| 0x568d5c8 | 4 | R | `0x568d5c8  movss xmm0,[r8+0x1C]` | table entry +0x1C | [V] |
| 0x568d5de | 4 | R | `0x568d5de  movss xmm0,[r8+0x20]` | table entry +0x20 | [V] |
| 0x568d5f4 | 4 | R | `0x568d5f4  movss xmm0,[r8+0x24]` | table entry +0x24 | [V] |
| 0x568d60a | 4 | R | `0x568d60a  mov r9d,[r8+0x28]` | table entry +0x28 | [V] |
| 0x568d618 | 4 | R | `0x568d618  movss xmm0,[r8+0x2C]` | table entry +0x2C | [V] |
| 0x568d62e | 4 | R | `0x568d62e  movss xmm0,[r8+0x30]` | table entry +0x30 | [V] |
| 0x568d644 | 1 | R | `0x568d644  movzx r9d,byte ptr [r8+0x54]` | table entry +0x54 | [V] |
| 0x568d66e | 1 | R | `0x568d66e  movzx r9d,byte ptr [r8+0x34]` | table entry +0x34 | [V] |
| 0x568d679 | 4 | R | `0x568d679  mov r9d,[r8+0x38]` | table entry +0x38 | [V] |
| 0x568d683 | 4 | R | `0x568d683  mov r9d,[r8+0x3C]` | table entry +0x3C | [V] |
| 0x568d68d | 4 | R | `0x568d68d  mov r9d,[r8+0x40]` | table entry +0x40 | [V] |
| 0x568d697 | 1 | R | `0x568d697  movzx r9d,byte ptr [r8+0x44]` | table entry +0x44 | [V] |
| 0x568d6a2 | 4 | R | `0x568d6a2  mov r9d,[r8+0x48]` | table entry +0x48 | [V] |
| 0x568d6ac | 4 | R | `0x568d6ac  mov r9d,[r8+0x4C]` | table entry +0x4C | [V] |
| 0x568d6b6 | 4 | R | `0x568d6b6  mov r8d,[r8+0x50]` | table entry +0x50 | [V] |
| 0x568d6e8 | call | C | `0x568d6e8  call 0x568D750` | body: build command packet | [V] |
| 0x568d94a | 8 | R | `0x568d94a  mov rdx,[rsi]` | a0+0x0 | [V] |
| 0x568d94d | 8 | R | `0x568d94d  mov rcx,[rsi+0x88]` | a0+0x88 | [V] |
| 0x568d968 | 8 | R | `0x568d968  mov r15,[rdi]` | [rdi] list head | [V] |
| 0x568d96b | 8 | R | `0x568d96b  mov r14,[rdi+8]` | [rdi+8] list end | [V] |
| 0x568d9b9 | 8 | R | `0x568d9b9  mov r13,[r15-0x10]` | element-0x10 | [V] |
| 0x568d9c6 | 8 | R | `0x568d9c6  mov r12,[r15-8]` | element-8 | [V] |
| 0x568d9ca | 2 | R | `0x568d9ca  movzx eax,word ptr [r13+0x28]` | element-0x10+0x28 → index | [V] |
| 0x568d9d3 | 8 | R | `0x568d9d3  add rdi,[r12+0x768]` | rdi += element-8+0x768 → table base (rdi was 0 from xor prior path) | [V] |
| 0x568d9db | 8 | R | `0x568d9db  mov rbx,[rsi+0x88]` | a0+0x88 | [V] |
| 0x568da00 | 2 | R | `0x568da00  movzx eax,word ptr [r13+0x42]` | element-0x10+0x42 | [V] |
| 0x568da0d | add | R | `0x568da0d  add r9,[r12+0x630]` | element-8+0x630 → table2 base | [V] |
| 0x568da15 | 8 | R | `0x568da15  mov rax,[rsi+0x98]` | a0+0x98 | [V] |
| 0x568da1c | 8 | R | `0x568da1c  mov rax,[rax]` | *(a0+0x98) | [V] |
| 0x568da1f | 8 | R | `0x568da1f  mov rcx,[rsi+0x88]` | a0+0x88 | [V] |
| 0x568da26 | 8 | R | `0x568da26  mov rdx,[rsi+0x90]` | a0+0x90 | [V] |
| 0x568da2d | 2 | R | `0x568da2d  movzx r8d,word ptr [rdx+8]` | *(a0+0x90)+8 | [V] |
| 0x568da45 | call | C | `0x568da45  call 0xBCC38E0` | submit (sub_bcc38e0, 6hr submitPass inline path) | [V] |
| 0x568d9e8 | call | C | `0x568d9e8  call 0xBCC2B00` | validation (sub_bcc2b00) | [V] |
| 0x568d9f7 | call | C | `0x568d9f7  call 0xBCC2EB0` | validation (sub_bcc2eb0) | [V] |

Tail 0x568d480 OUT (writes):
| offset | size | R/W/C | instr | meaning | tag |
| 0x568d6d3 | 8 | W | `0x568d6d3  mov [rsp+0x28],r15` | stack +0x28 = matched element | [V] |
| 0x568d6d8 | 8 | W | `0x568d6d8  mov [rsp+0x30],r14` | stack +0x30 = list end | [V] |
| 0x568d6dd | 8 | W | `0x568d6dd  mov [rsp+0x38],r15` | stack +0x38 = matched element | [V] |
| 0x568da38 | 8 | W | `0x568da38  mov [rsp+0x20],rax` | stack +0x20 = *(a0+0x98) | [V] |
| 0x568da3d | 4 | W | `0x568da3d  mov dword ptr [rsp+0x28],0` | stack +0x28 = 0 | [V] |

RTX denoise body 0xbcc4b90 — UAV writes (rdis dis 0xbcc4b90, descriptor-heap bind loop region bcc5fd1..bcc619d). sub_bcc4b90 builds a command packet (rbp-relative fields) and binds RTX/UAV resources into a descriptor heap; this section covers the UAV-related reads/writes only.

IN (reads — UAV descriptor table at rbp+0x1D0.. and packet UAV fields):
| offset | size | R/W/C | instr | meaning | tag |
| 0xbcc5fe3 | 8 | R | `0xbcc5fe3  mov rcx,[0x1233E1A8]` | global UAV/resource manager ptr | [V] |
| 0xbcc5fea | 8 | R | `0xbcc5fea  mov rax,[rcx]` | *(mgr) | [V] |
| 0xbcc5fed | 8 | R | `0xbcc5fed  mov rax,[rax+8]` | *(mgr+8) = ref-counted UAV object | [V] |
| 0xbcc6017 | lea | R | `0xbcc6017  lea rax,[rsi+0xAF0]` | new UAV object +0xAF0 | [V] |
| 0xbcc603c | lea | R | `0xbcc603c  lea r14,[rbp+0x1D0]` | UAV descriptor-table base on stack | [V] |
| 0xbcc604a | 8 | R | `0xbcc604a  mov rdi,[rbp+0xDA8]` | descriptor-heap base ptr | [V] |
| 0xbcc6079 | 8 | R | `0xbcc6079  mov rcx,[rbp+0xDD0]` | UAV desc table index | [V] |
| 0xbcc6080 | 8 | R | `0xbcc6080  mov rax,[rbp+rcx+0x1D0]` | UAV desc entry [index].ptr | [V] |
| 0xbcc6093 | 8 | R | `0xbcc6093  mov rax,[rbp+rcx+0x200]` | UAV desc entry [index]+0x200 | [V] |
| 0xbcc60db | 8 | R | `0xbcc60db  mov rax,[rbp+0xDD0]` | UAV desc table index | [V] |
| 0xbcc60e2 | 8 | R | `0xbcc60e2  cmp qword ptr [rbp+rax+0x1F0],0x10` | UAV desc size field vs 0x10 | [V] |
| 0xbcc60ed | 8 | R | `0xbcc60ed  mov r9,[rbp+rax+0x1D8]` | UAV desc ptr (or rbp+rax fallback) | [V] |
| 0xbcc610b | lea | R | `0xbcc610b  lea rcx,[rdi+rax]` | heap slot addr | [V] |
| 0xbcc6113 | 8 | R | `0xbcc6113  mov rbx,[rbp+rax+0x1E8]` | UAV desc +0x1E8 | [V] |
| 0xbcc618f | 8 | R | `0xbcc618f  mov rax,[rbp+rdi+0x1E8]` | current slot size | [V] |
| 0xbcc619d | 8 | R | `0xbcc619d  mov rcx,[rbp+rdi+0x1D0]` | current slot ptr | [V] |

OUT (writes — packet UAV fields + descriptor-heap UAV bindings; releases old UAV via refcount):
| offset | size | R/W/C | instr | meaning | tag |
| 0xbcc5fd1 | 16 | W | `0xbcc5fd1  movaps [rbp+0xDB0],xmm0` | packet +0xDB0 = UAV ptr (xmm0) | [V] |
| 0xbcc5ff6 | call | C | `0xbcc5ff6  call qword ptr [0xF99FFA0]` | release old UAV object (sub_eea6040 via vtable) | [V] |
| 0xbcc6009 | 8 | W | `0xbcc6009  mov [rbp+0xDB0],rsi` | packet +0xDB0 = new UAV object ptr | [V] |
| 0xbcc6025 | 8 | W | `0xbcc6025  mov [rbp+0xCC0],rsi` | packet +0xCC0 = new UAV object ptr | [V] |
| 0xbcc6064 | 8 | W | `0xbcc6064  mov [rdi+rax+0x18],rbx` | heap slot+0x18 = UAV desc +0x1E8 | [V] |
| 0xbcc6074 | 1 | W | `0xbcc6074  mov byte ptr [rbx+rsi+8],0` | heap slot terminator byte = 0 | [V] |
| 0xbcc608f | 8 | W | `0xbcc608f  mov [rsi+rcx],rax` | heap slot = UAV desc entry ptr | [V] |
| 0xbcc609b | 8 | W | `0xbcc609b  mov [rsi+rcx+0x30],rax` | heap slot+0x30 = UAV desc entry +0x200 | [V] |
| 0xbcc60bb | 16 | W | `0xbcc60bb  movups [rsi+rax+0x10],xmm6` | heap slot+0x10 = xmm6 | [V] |
| 0xbcc60c0 | 16 | W | `0xbcc60c0  movups [rsi+rax],xmm6` | heap slot+0x0 = xmm6 | [V] |
| 0xbcc60b4 | 8 | W | `0xbcc60b4  mov [rbp+0xDD0],rax` | stack +0xDD0 = index | [V] |
| 0xbcc6125 | 8 | W | `0xbcc6125  mov [rbp+0xCD8],rcx` | stack +0xCD8 = heap slot addr | [V] |
| 0xbcc613a | 8 | W | `0xbcc613a  mov [rbp+0xDD0],r12` | stack +0xDD0 = r12 | [V] |
| 0xbcc6147 | 8 | W | `0xbcc6147  mov [rbp+0xDB8],rsi` | stack +0xDB8 = UAV object ptr | [V] |
| 0xbcc6165 | 8 | W | `0xbcc6165  mov qword ptr [rbp+rdi+0x1E0],0` | slot+0x1E0 = 0 | [V] |
| 0xbcc6171 | 8 | W | `0xbcc6171  mov qword ptr [rbp+rdi+0x1E8],0xF` | slot+0x1E8 = 0xF | [V] |
| 0xbcc617d | 1 | W | `0xbcc617d  mov byte ptr [rbp+rdi+0x1D0],0` | slot+0x1D0 = 0 | [V] |

