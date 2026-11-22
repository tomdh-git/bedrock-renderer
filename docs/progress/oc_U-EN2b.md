## NEXT
DONE

UNIT U-EN2b — Close checklist item N2b "Slot 50 submit stats/timers; slot 26 CreateTexture, slot 22 CreateShader, slot 24 CreateProgram, slots 14/16/17 vertex/index buffer, slot 35 CreateFrameBuffer, slots 36-38 uniform, slot 30 readTexture accounted for — BGFX_MAP 10; 6f; K-P5" (docs/RENDER_CHECKLIST.md line 489, still [ ]). Output file: docs/progress/oc_U-EN2b.md only.

Source of record: docs/BGFX_MAP.md section 6k (slot table), section 6f (vtables), sections 6aj/6et/6au/6z, docs/RENDER_CHECKLIST.md line 489. Exe: Minecraft.Windows.exe 1.26.62.01, image-base RVAs.

Status carried in from prior units (already CLOSES? YES, [V] rows exist elsewhere):
- Slot 50 submit stats/timers = 0xe82e230 (0x4d91 bytes): CLOSES? YES in oc_U-EL17c.md (40 rows, verify_oc 40/40).
- Slot 26 CreateTexture = 0xe8143c0 (size 0x2e1): CLOSES? in oc_U-B7a.md (45/45 verify_oc; open [UNVERIFIED] items non-blocking).
- Slot 24 CreateProgram = 0xe8142c0 (size 0xd6): CLOSES? in oc_U-B9b.md.

Pending/not decoded in this unit (fresh [V] rows below):
- Slot 22 CreateShader = 0xe8137b0 (B9b covers 23/24/25 only; 22 not yet disassembled in any unit)
- Slot 14 CreateVertexBuffer = 0xe812be0, slot 16 CreateDynamicIndexBuffer = 0xe812ea0, slot 17 UpdateDynamicIndexBuffer = 0xe813110
- Slot 35 = 0xe8146f0 (6k labels createFrameBuffer; corrected 6z/6es table says slot 35 is a Mojang texture-extra, framebuffer creates are slots 36/37 — contradiction resolved below)
- Slots 36-38 = 0xe815fc0..0xe816580 (6k: destroyFrameBuffer/createUniform/destroyUniform; corrected table: 36/37 createFrameBuffer variants, 38 destroyFrameBuffer — contradiction resolved below)
- Slot 30 readTexture = 0xe8150f0

Tags: [V] = seen verbatim in disassembly (cite RVA), [I] = inferred, [?] = unknown. No guesses as fact. [UNVERIFIED: 0xaddr question] where a single tool call doesn't settle it.

## Answer table: N2b slot accounting

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | tag |
|---|---|---|---|---|
| Slot 22 CreateShader | 0xe8137b0 | 0xa22 | `e8137d4  mov esi,[r8+8]` | [V] |
| Shader mem->size field | a2+0x8 | 4 | `e8137d4  mov esi,[r8+8]` | [V] |
| Shader mem->data field | a2+0x0 | 8 | `e8137d8  mov rdi,[r8]` | [V] |
| Shader record handle*stride | handle*0xB8 | 8 | `e813895  imul rbx,r15,0xB8` | [V] |
| Shader record base | this+0xAAA178 | 8 | `e81390b  lea r12,[rax+rbx]` / `e81390f  add r12,0xAAA178` | [V] |
| Shader record stride | 0xB8 | - | `e813895  imul rbx,r15,0xB8` | [V] |
| Shader record+0xAC type/format u16 | +0xAC | 2 | `e813990  movzx eax,word ptr [rsp+0x4E]` / `e813995  mov [r12+0xAC],ax` | [V] |
| Shader record+0xB0 entry count u8 | +0xB0 | 1 | `e813987  mov byte ptr [r12+0xB0],0` / `e813d43  mov [r12+0xB0],al` | [V] |
| Shader entry array+0x00 u32 | +0x10 | 4 | `e813d1a  mov [r12+r8*8+0x10],ecx` | [V] |
| Shader entry array+0x04 u16 | +0x14 | 2 | `e813d2d  mov [r12+r8*8+0x14],cx` | [V] |
| Shader entry array+0x06 byte | +0x16 | 1 | `e813d37  mov [r12+r8*8+0x16],al` | [V] |
| Shader record+0x00 owned pointer | +0x00 | 8 | `e813f9b  mov [r12],r14` | [V] |
| Shader record+0x08 code/uniform pointer | +0x08 | 8 | `e813dcb  mov [rax+8],r12` | [V] |
| Shader record+0xA8 signature u32 | +0xA8 | 4 | `e814163  mov [rbp+0xA8],ecx` | [V] |
| "MemoryReader: read truncated." string | 0xF80CD25 | - | `e813839  lea rbx,[0xF80CD25]` | [V] |
| "Unknown shader format %x." string | 0xF7EB1DA | - | `e81387d  lea rdx,[0xF7EB1DA]` | [V] |
| Slot 14 CreateVertexBuffer | 0xe812be0 | 0x257 | `e812c0d  movzx esi,dx` | [V] |
| VB handle | dx (u16) | 2 | `e812c0d  movzx esi,dx` | [V] |
| VB handle*stride | handle*0x80 | 4 | `e812c12  shl eax,7` | [V] |
| VB record base | this+0x9B2178 | 8 | `e812c15  lea r12,[rcx+rax]` / `e812c19  add r12,0x9B2178` | [V] |
| VB record stride | 0x80 | - | `e812c12  shl eax,7` | [V] |
| VB record+0x78 handle u16 | +0x78 | 2 | `e812c89  mov [r12+0x78],ax` | [V] |
| Tracker+0xA220 flags qword | +0xA220 | 8 | `e812d09  mov [rdx+rax*8+0xA220],r9` | [V] |
| Tracker+0x12420 handle u16 | +0x12420 | 2 | `e812d1d  mov [rdx+rcx*2+0x12420],r9w` | [V] |
| Tracker+0xA218 count u16 | +0xA218 | 2 | `e812d28  mov [rdx+0xA218],cx` | [V] |
| Tracker+0xA420 size dword | +0xA420 | 4 | `e812d2f  mov [rdx+rsi*8+0xA420],r14d` | [V] |
| Tracker+0xA424 size dword | +0xA424 | 4 | `e812d37  mov [rdx+rsi*8+0xA424],r14d` | [V] |
| Resource table+0xA258 slot | +0xA258 | 8 | `e812d46  mov rcx,[rdx+rax*8+0xA258]` | [V] |
| Slot 16 CreateDynamicIndexBuffer | 0xe812ea0 | 0x22f | `e812ed5  imul rax,rsi,0x78` | [V] |
| IB16 handle | dx (u16) | 2 | `e812ed2  movzx esi,dx` | [V] |
| IB16 handle*stride | handle*0x78 | 4 | `e812ed5  imul rax,rsi,0x78` | [V] |
| IB16 record base | this+0x93A178 | 8 | `e812edd  add rax,rcx` / `e812ee0  add rax,0x93A178` | [V] |
| IB16 record stride | 0x78 | - | `e812ed5  imul rax,rsi,0x78` | [V] |
| IB16 stride stack slot | [rsp+0x28] | 2 | `e812f0c  mov [rsp+0x28],r15w` | [V] |
| IB16 type dword (1=index) | [rsp+0x30] | 4 | `e812f23  mov dword ptr [rsp+0x30],1` | [V] |
| Tracker16+0x10 flags qword | +0x10 | 8 | `e812fc1  mov [rdx+rax*8+0x10],r9` | [V] |
| Tracker16+0x8210 handle u16 | +0x8210 | 2 | `e812fca  mov [rdx+rcx*2+0x8210],di` | [V] |
| Tracker16+8 count u16 | +8 | 2 | `e812fd4  mov [rdx+8],cx` | [V] |
| Tracker16+0x210 size dword | +0x210 | 4 | `e812fd8  mov [rdx+rsi*8+0x210],r14d` | [V] |
| Tracker16+0x214 size dword | +0x214 | 4 | `e812fe0  mov [rdx+rsi*8+0x214],r14d` | [V] |
| Resource16 table+0x48 slot | +0x48 | 8 | `e812fef  mov rcx,[rdx+rax*8+0x48]` | [V] |
| Slot 17 UpdateDynamicIndexBuffer | 0xe813110 | 0x1f7 | `e813126  imul rbp,rcx,0x78` | [V] |
| IB17 handle*stride | handle*0x78 | 4 | `e813126  imul rbp,rcx,0x78` | [V] |
| IB17 record exists check | this+0x93A178+idx | 8 | `e81312a  cmp qword ptr [rdi+rbp+0x93A178],0` | [V] |
| Resource17+0x24C state dword | +0x24C | 4 | `e81318d  mov dword ptr [rax+rcx*8+0x24C],0x400` | [V] |
| Resource17+0x248 state qword | +0x248 | 8 | `e813206  mov rdx,0x40000000400` / `e813210  mov [rax+rcx*8+0x248],rdx` | [V] |
| IB17 upload call | 0xEEC6EC0 | - | `e8132be  call 0xEEC6EC0` | [V] |
| IB17 record data pointer | +0x00 | 8 | `e8132c3  mov rdx,[rdi]` | [V] |
| Slot 30 readTexture | 0xe8150f0 | 0x498 | `e81511e  lea r14,[rcx+0xBDE178]` | [V] |
| Texture30 table base | this+0xBDE178 | 8 | `e81511e  lea r14,[rcx+0xBDE178]` | [V] |
| Texture30 handle | dx (u16) | 2 | `e815125  movzx r15d,dx` | [V] |
| Texture30 handle*stride | handle*0xB8 | 4 | `e81515d  imul r8,r15,0xB8` | [V] |
| Texture30 record base | page+offset | 8 | `e815228  add r14,rcx` | [V] |
| Resource state tracker base | this+0x19F58 | 8 | `e815230  mov rcx,[rsi+0x19F58]` | [V] |
| Tracker+0x30 command list | +0x30 | 8 | `e815237  mov rdx,[rcx+0x30]` | [V] |
| Tracker block base | +0x14458 | 8 | `e81523b  add rcx,0x14458` | [V] |
| Resource state transition | 0xE82D960 | - | `e81524b  call 0xE82D960` | [V] |
| Texture30 record+0x00 resource ptr | +0x00 | 8 | `e815250  mov rcx,[r14]` | [V] |
| Texture desc copy | 0x45EB90 | - | `e815260  call 0x45EB90` | [V] |
| Texture format byte | bl | 1 | `e815295  movzx r8d,bl` | [V] |
| Device vtable+0x130 method | +0x130 | 8 | `e81529c  mov rax,[rax+0x130]` | [V] |
| Slot 35 texture-extra (NOT CreateFrameBuffer) | 0xe8146f0 | 0x372 | `e81470e  lea rdi,[rcx+0xBDE178]` | [V] |
| Slot 35 works on TEXTURE table | this+0xBDE178 | - | `e81470e  lea rdi,[rcx+0xBDE178]` | [V] |
| Texture35 record+0x98 flags dword | +0x98 | 4 | `e814820  mov dword ptr [rdi+0x98],0` / `e8148de  or [rdi+0x98],edx` | [V] |
| Texture35 record+0xAF format byte | +0xAF | 1 | `e8148d2  mov [rdi+0xAF],al` | [V] |
| Texture35 record+0xB0 format byte | +0xB0 | 1 | `e8148d8  mov [rdi+0xB0],al` | [V] |
| Texture35 record+0x9C width dword | +0x9C | 4 | `e8148f0  mov [rdi+0x9C],eax` | [V] |
| Texture35 record+0xA0 height dword | +0xA0 | 4 | `e8148fa  mov [rdi+0xA0],eax` | [V] |
| Texture35 record+0xA8 depth dword | +0xA8 | 4 | `e814905  mov [rdi+0xA8],eax` | [V] |
| Texture35 record+0xA4 layers dword | +0xA4 | 4 | `e81490b  mov [rdi+0xA4],eax` | [V] |
| Texture35 record+0xB1 mip byte | +0xB1 | 1 | `e814916  mov [rdi+0xB1],al` | [V] |
| Texture35 record+0xAE type byte | +0xAE | 1 | `e81491c  mov byte ptr [rdi+0xAE],0` | [V] |
| SRV desc memset | 0xEBCE430 | - | `e81492f  call 0xEBCE430` | [V] |
| SRV desc Shader4ComponentMapping | +0x48 | 4 | `e814934  mov dword ptr [rdi+0x48],0x1688` | [V] |
| SRV desc format | +0x68 | 4 | `e81493f  mov [rdi+0x68],eax` | [V] |
| SRV desc ViewDimension | +0x40 | 4 | `e814963  mov [rdi+0x40],eax` | [V] |
| UAV desc+0x60 qword | +0x60 | 8 | `e814987  mov qword ptr [rdi+0x60],0` | [V] |
| UAV desc+0x78 dword | +0x78 | 4 | `e81498f  mov [rdi+0x78],ecx` | [V] |
| UAV desc+0x7C dword | +0x7C | 4 | `e814992  mov dword ptr [rdi+0x7C],0` | [V] |
| UAV desc+0x44 dword | +0x44 | 4 | `e8149a9  mov [rdi+0x44],ecx` | [V] |
| UAV desc+0x50 dword | +0x50 | 4 | `e8149ac  mov dword ptr [rdi+0x50],0` | [V] |
| UAV desc+0x54 dword | +0x54 | 4 | `e8149b3  mov [rdi+0x54],eax` | [V] |
| UAV desc+0x58 dword | +0x58 | 4 | `e8149b6  mov dword ptr [rdi+0x58],0` | [V] |
| UAV desc+0x5C dword | +0x5C | 4 | `e8149bd  movd [rdi+0x5C],xmm0` | [V] |
| UAV desc+0x6C dword | +0x6C | 4 | `e8149c2  mov [rdi+0x6C],ecx` | [V] |
| UAV desc+0x70 qword | +0x70 | 8 | `e8149c5  mov qword ptr [rdi+0x70],0` | [V] |
| this35+0x10 sentinel qword | +0x10 | 8 | `e8149d9  mov qword ptr [rbx+0x10],0xFFFFFFFFFFFFFFFF` | [V] |
| this35+0x18 dword | +0x18 | 4 | `e8149e1  mov dword ptr [rbx+0x18],0` | [V] |
| this35+0x1E byte | +0x1E | 1 | `e8149e8  mov byte ptr [rbx+0x1E],6` | [V] |
| this35+0x1F byte | +0x1F | 1 | `e8149ec  mov [rbx+0x1F],dl` | [V] |
| this35+0x20 byte | +0x20 | 1 | `e8149ef  mov [rbx+0x20],al` | [V] |
| this35+0x22 word | +0x22 | 2 | `e8149f2  mov [rbx+0x22],cx` | [V] |
| this35+0x24 word | +0x24 | 2 | `e8149f6  mov word ptr [rbx+0x24],0x100` | [V] |
| this35+0x26 byte | +0x26 | 1 | `e8149fc  mov byte ptr [rbx+0x26],1` | [V] |
| Texture state registration | 0xE80F290 | - | `e814a00  mov rcx,rdi` / `e814a03  call 0xE80F290` | [V] |
| Texture35 record+0x9B created flag | +0x9B | 1 | `e814a08  or byte ptr [rdi+0x9B],0x40` | [V] |
| Texture35 record+0x00 resource ptr | +0x00 | 8 | `e814a0f  mov [rdi],rsi` | [V] |
| Texture35 record+0x08 desc block 1 | +0x08 | 16 | `e814a21  movups [rdi+8],xmm0` | [V] |
| Texture35 record+0x18 desc block 2 | +0x18 | 16 | `e814a25  movups [rdi+0x18],xmm1` | [V] |
| Texture35 record+0x28 desc block 3 | +0x28 | 16 | `e814a29  movups [rdi+0x28],xmm2` | [V] |
| Texture35 record+0x38 qword | +0x38 | 8 | `e814a32  mov [rdi+0x38],rax` | [V] |
| Slot 36 createFrameBuffer | 0xe815fc0 | 0x337 | `e8160f6  imul rdi,rsi,0x78` | [V] |
| FB36 handle*stride | handle*0x78 | 4 | `e8160f6  imul rdi,rsi,0x78` | [V] |
| FB36 record base | this+0xA32178 | 8 | `e8160fa  lea rcx,[rbx+rdi]` / `e8160fe  add rcx,0xA32178` | [V] |
| FB36 record stride | 0x78 | - | `e8160f6  imul rdi,rsi,0x78` | [V] |
| FB36 desc block 1 load | [rbp-8] | 16 | `e816105  movups xmm0,[rbp-8]` | [V] |
| FB36 desc block 2 load | [rbp+8] | 16 | `e816109  movups xmm1,[rbp+8]` | [V] |
| FB36 common create helper | 0xE812740 | - | `e816151  call 0xE812740` | [V] |
| Slot 37 createFrameBuffer-replace | 0xe816380 | 0x1f8 | `e816396  imul rbp,rcx,0x78` | [V] |
| FB37 handle*stride | handle*0x78 | 4 | `e816396  imul rbp,rcx,0x78` | [V] |
| FB37 record exists check | this+0xA32178+idx | 8 | `e81639a  cmp qword ptr [rdi+rbp+0xA32178],0` | [V] |
| FB37 no-record early return | loc_e816567 | - | `e8163a3  je 0xE816567` | [V] |
| FB37 create resource call | 0xE8360F0 | - | `e8164bb  call 0xE8360F0` | [V] |
| FB37 upload data call | 0xEEC6EC0 | - | `e81652f  call 0xEEC6EC0` | [V] |
| Slot 38 destroyFrameBuffer | 0xe816580 | 6 | `e816580  movzx eax,dx` | [V] |
| FB38 handle | dx (u16) | 2 | `e816580  movzx eax,dx` | [V] |
| FB38 handle*stride | handle*0x78 | 4 | `e816583  imul rax,0x78` | [V] |
| FB38 record address | this+0xA32178+idx | 8 | `e816587  add rcx,rax` / `e81658a  add rcx,0xA32178` | [V] |
| FB38 destroy tail-jump | 0xE80EF60 | - | `e816591  jmp 0xE80EF60` | [V] |
| Slot 50 submit stats/timers | 0xe82e230 | 0x4d91 | see oc_U-EL17c.md (40 rows, verify_oc 40/40) | [V] |
| Slot 26 CreateTexture | 0xe8143c0 | 0x2e1 | see oc_U-B7a.md (45 rows, verify_oc 45/45) | [V] |
| Slot 24 CreateProgram | 0xe8142c0 | 0xd6 | see oc_U-B9b.md | [V] |

## Verification rows (each `0xRVA  instr` line verified against the exe by tools/sigs/verify_oc.py)

e8137d4  mov esi,[r8+8]
e8137d8  mov rdi,[r8]
e813895  imul rbx,r15,0xB8
e81390b  lea r12,[rax+rbx]
e81390f  add r12,0xAAA178
e813987  mov byte ptr [r12+0xB0],0
e813990  movzx eax,word ptr [rsp+0x4E]
e813995  mov [r12+0xAC],ax
e813d1a  mov [r12+r8*8+0x10],ecx
e813d2d  mov [r12+r8*8+0x14],cx
e813d37  mov [r12+r8*8+0x16],al
e813d43  mov [r12+0xB0],al
e813f9b  mov [r12],r14
e813dcb  mov [rax+8],r12
e814163  mov [rbp+0xA8],ecx
e813839  lea rbx,[0xF80CD25]
e81387d  lea rdx,[0xF7EB1DA]
e812c0d  movzx esi,dx
e812c12  shl eax,7
e812c15  lea r12,[rcx+rax]
e812c19  add r12,0x9B2178
e812c89  mov [r12+0x78],ax
e812d09  mov [rdx+rax*8+0xA220],r9
e812d1d  mov [rdx+rcx*2+0x12420],r9w
e812d28  mov [rdx+0xA218],cx
e812d2f  mov [rdx+rsi*8+0xA420],r14d
e812d37  mov [rdx+rsi*8+0xA424],r14d
e812d46  mov rcx,[rdx+rax*8+0xA258]
e812ed5  imul rax,rsi,0x78
e812ed2  movzx esi,dx
e812edd  add rax,rcx
e812ee0  add rax,0x93A178
e812f0c  mov [rsp+0x28],r15w
e812f23  mov dword ptr [rsp+0x30],1
e812fc1  mov [rdx+rax*8+0x10],r9
e812fca  mov [rdx+rcx*2+0x8210],di
e812fd4  mov [rdx+8],cx
e812fd8  mov [rdx+rsi*8+0x210],r14d
e812fe0  mov [rdx+rsi*8+0x214],r14d
e812fef  mov rcx,[rdx+rax*8+0x48]
e813126  imul rbp,rcx,0x78
e81312a  cmp qword ptr [rdi+rbp+0x93A178],0
e81318d  mov dword ptr [rax+rcx*8+0x24C],0x400
e813206  mov rdx,0x40000000400
e813210  mov [rax+rcx*8+0x248],rdx
e8132be  call 0xEEC6EC0
e8132c3  mov rdx,[rdi]
e81511e  lea r14,[rcx+0xBDE178]
e815125  movzx r15d,dx
e81515d  imul r8,r15,0xB8
e815228  add r14,rcx
e815230  mov rcx,[rsi+0x19F58]
e815237  mov rdx,[rcx+0x30]
e81523b  add rcx,0x14458
e81524b  call 0xE82D960
e815250  mov rcx,[r14]
e815260  call 0x45EB90
e815295  movzx r8d,bl
e81529c  mov rax,[rax+0x130]
e81470e  lea rdi,[rcx+0xBDE178]
e814820  mov dword ptr [rdi+0x98],0
e8148d2  mov [rdi+0xAF],al
e8148d8  mov [rdi+0xB0],al
e8148de  or [rdi+0x98],edx
e8148f0  mov [rdi+0x9C],eax
e8148fa  mov [rdi+0xA0],eax
e814905  mov [rdi+0xA8],eax
e81490b  mov [rdi+0xA4],eax
e814916  mov [rdi+0xB1],al
e81491c  mov byte ptr [rdi+0xAE],0
e81492f  call 0xEBCE430
e814934  mov dword ptr [rdi+0x48],0x1688
e81493f  mov [rdi+0x68],eax
e814963  mov [rdi+0x40],eax
e814987  mov qword ptr [rdi+0x60],0
e81498f  mov [rdi+0x78],ecx
e814992  mov dword ptr [rdi+0x7C],0
e8149a9  mov [rdi+0x44],ecx
e8149ac  mov dword ptr [rdi+0x50],0
e8149b3  mov [rdi+0x54],eax
e8149b6  mov dword ptr [rdi+0x58],0
e8149bd  movd [rdi+0x5C],xmm0
e8149c2  mov [rdi+0x6C],ecx
e8149c5  mov qword ptr [rdi+0x70],0
e8149d9  mov qword ptr [rbx+0x10],0xFFFFFFFFFFFFFFFF
e8149e1  mov dword ptr [rbx+0x18],0
e8149e8  mov byte ptr [rbx+0x1E],6
e8149ec  mov [rbx+0x1F],dl
e8149ef  mov [rbx+0x20],al
e8149f2  mov [rbx+0x22],cx
e8149f6  mov word ptr [rbx+0x24],0x100
e8149fc  mov byte ptr [rbx+0x26],1
e814a00  mov rcx,rdi
e814a03  call 0xE80F290
e814a08  or byte ptr [rdi+0x9B],0x40
e814a0f  mov [rdi],rsi
e814a21  movups [rdi+8],xmm0
e814a25  movups [rdi+0x18],xmm1
e814a29  movups [rdi+0x28],xmm2
e814a32  mov [rdi+0x38],rax
e8160f6  imul rdi,rsi,0x78
e8160fa  lea rcx,[rbx+rdi]
e8160fe  add rcx,0xA32178
e816105  movups xmm0,[rbp-8]
e816109  movups xmm1,[rbp+8]
e816151  call 0xE812740
e816396  imul rbp,rcx,0x78
e81639a  cmp qword ptr [rdi+rbp+0xA32178],0
e8163a3  je 0xE816567
e8164bb  call 0xE8360F0
e81652f  call 0xEEC6EC0
e816580  movzx eax,dx
e816583  imul rax,0x78
e816587  add rcx,rax
e81658a  add rcx,0xA32178
e816591  jmp 0xE80EF60

## OPEN questions / contradictions resolved

**Contradiction: BGFX_MAP 6k vs 6z/6es on slots 35-38.**

6k (line 406-407) says: slot 35 = createFrameBuffer (0xe8146f0), slots 36-38 = destroyFrameBuffer/createUniform/destroyUniform (0xe815fc0..0xe816580).

6z/6es corrected table (line 1526-1527) says: slot 35 = texture-extra (Mojang, works on texture table ctx+0xBDE178, NOT createFrameBuffer); slots 36/37 = createFrameBuffer variants (framebuffer table ctx+0xA32178, stride 0x78); slot 38 = destroyFrameBuffer.

**Resolution [V]:** Disassembly confirms the 6z/6es reading:
- Slot 35 (0xe8146f0) works on the TEXTURE table (this+0xBDE178, stride 0xB8) — it sets record fields +0x98/+0x9C/+0xA0/+0xA4/+0xA8/+0xAF/+0xB0/+0xB1 (texture desc), builds SRV/UAV descriptors at +0x40/+0x60/+0x68, stores an externally-provided resource pointer at +0x00, and calls 0xE80F290 for state registration. It is a Mojang texture-extra (wrap/register an existing ID3D12Resource under a handle), NOT createFrameBuffer.
- Slot 36 (0xe815fc0) works on the FRAMEBUFFER table (this+0xA32178, stride 0x78) — computes &fb[handle], loads two 16-byte desc blocks, calls common helper 0xE812740. It is createFrameBuffer.
- Slot 37 (0xe816380) works on the FRAMEBUFFER table — checks if a record already exists (je early-return), then creates resources via 0xE8360F0 and uploads via 0xEEC6EC0. It is createFrameBuffer with replacement semantics.
- Slot 38 (0xe816580) computes &fb[handle] and tail-jumps to 0xE80EF60 (common release). It is destroyFrameBuffer.

**Consequence:** The checklist item wording "slot 35 CreateFrameBuffer, slots 36-38 uniform" does NOT match the 1.26.62.01 exe. Slot 35 is a texture extra, and slots 36-38 are createFrameBuffer/createFrameBuffer-replace/destroyFrameBuffer — NOT uniform functions. CreateUniform/destroyUniform are NOT at slots 36-38 (per line 1527 they may be at 39/41 touching ctx+0xC97698, [I] not verified here). Every slot named in the item is nevertheless accounted for with [V] proof rows showing what it actually does.

**Already closed (reference only, not re-proven here):**
- Slot 50 submit stats/timers: oc_U-EL17c.md (40/40 verify_oc).
- Slot 26 CreateTexture: oc_U-B7a.md (45/45 verify_oc).
- Slot 24 CreateProgram: oc_U-B9b.md.

## CLOSES?
YES — every slot named in N2b is accounted for with [V] proof rows: slot 50 (submit stats/timers, oc_U-EL17c.md), slot 26 (CreateTexture, oc_U-B7a.md), slot 22 (CreateShader, 0xe8137b0), slot 24 (CreateProgram, oc_U-B9b.md), slots 14/16/17 (vertex/index buffer, 0xe812be0/0xe812ea0/0xe813110), slot 35 (texture-extra, NOT CreateFrameBuffer — 0xe8146f0 works on texture table), slots 36-38 (createFrameBuffer/createFrameBuffer-replace/destroyFrameBuffer, NOT uniform — 0xe815fc0/0xe816380/0xe816580 work on framebuffer table), slot 30 (readTexture, 0xe8150f0). The checklist item's slot names for 35/36-38 do not match the 1.26.62.01 exe (Mojang-shifted numbering per 6z/6es), but each slot is identified and proven. CreateUniform/destroyUniform actual slots not verified in this unit ([I] per line 1527: possibly 39/41).

## TOOL REQUESTS
None — all data from rdis fn/dis on the exe plus existing verified unit docs.

