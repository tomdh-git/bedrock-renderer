## NEXT
DONE

# U-EG4a — G4a "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Scope of this unit = ONLY the pending part of the checklist line: **texture/atlas management** — the RendererContextD3D12 texture-management slot chain (create/update/read/resize/override/getInternal/destroy + blit/blitSetup), the shared texture-record-table lookup, and atlas registration/consumer. The sampler flag decode + sampler cache half is already closed on disk (docs/functions/e820500.md; 0xe820500 instruction-complete; BGFX_MAP section 6ax) and is NOT redone here.

All `0xRVA  instr` lines are verbatim from rdis disassembly of C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (image-relative RVAs). Sizes come from the instruction that accesses the field (qword 8, dword 4, word 2, byte 1). Meaning is written only where an instruction or string shows it, else '-'. Tags: [V] = seen in disassembly/string, [I] = inferred from instruction context, [?] = unknown/not proven.

## Texture-management chain — RendererContextD3D12 backend slots (all entries [V]; slot names [I slot N per 6k/6aj])

| name | rva or offset | size | verbatim `0xRVA  instr` proof | meaning | tag |
| slot 26 createTexture entry | 0xe8143c0 | - | `0xe8143c0  push rbp` | function entry; slot 26 = createTexture per vtable map (6k/6aj) | [V size/I name] |
| slot 28 updateTexture entry | 0xe814a70 | - | `0xe814a70  push r15` | slot 28 = updateTexture per vtable map (6k/6aj) | [V size/I name] |
| slot 30 readTexture entry | 0xe8150f0 | - | `0xe8150f0  push r15` | slot 30 = readTexture per vtable map (6k) | [V size/I name] |
| slot 31 resizeTexture entry | 0xe815840 | - | `0xe815840  push rbp` | slot 31 = resizeTexture per vtable map (6k) | [V size/I name] |
| slot 32 overrideInternal entry | 0xe815c30 | - | `0xe815c30  push r14` | slot 32 = overrideInternal per vtable map (6k) | [V size/I name] |
| slot 33 getInternal entry | 0xe815d70 | - | `0xe815d70  push rsi` | slot 33 = getInternal per vtable map (6k) | [V size/I name] |
| slot 34 destroyTexture entry | 0xe815ea0 | - | `0xe815ea0  push rsi` | slot 34 = destroyTexture per vtable map (6k) | [V size/I name] |
| slot 51 blit entry | 0xe818bc0 | - | `0xe818bc0  push r15` | slot 51 = blit per vtable map (6k) | [V size/I name] |
| slot 52 blitSetup entry | 0xe819750 | - | `0xe819750  push r15` | slot 52 = blitSetup per vtable map (6k) | [V size/I name] |

## Table A — shared texture-record lookup (used by every slot above)

| name | rva or offset | size | verbatim `0xRVA  instr` proof | meaning | tag |
| texture record table base | this+0xBDE178 | 8 | `0xe814a8c  lea rbx,[rcx+0xBDE178]` | inline table of 4096 records, stride 0xB8, ends 0xC5A178; sites: update 0xe814a8c, create 0xe8143f3, destroy 0xe815eaa, resize 0xe815876, getInternal 0xe815d81 | [V] meaning [I 6z] |
| record stride | 0xB8 | 4 | `0xe814ac3  imul r9,r15,0xB8` | sites: 0xe814ac3, update 0xe814c1b, destroy 0xe815ede, resize 0xe8158ad, override 0xe815c7c; byte size = dword immediate | [V] |
| overflow-page guard flag | this+0xC96190 | 1 | `0xe814aab  cmp byte ptr [r14+0xC96190],0` | sites: 0xe814aab, update 0xe814bfa, destroy 0xe815ec7, resize 0xe815895, create 0xe814410; guard enabled for handles >= 0x1000 | [V] meaning [I 6z] |
| page-list anchor for detached handles (>=0x1000) | this+0xC96178 | 8 | `0xe814ae7  mov rax,[r14+0xC96178]` | sites: 0xe814ae7, update 0xe814c36, destroy 0xe815f01, resize 0xe8158d1, override 0xe815ca0; +0xB8000 per page: 0xe814b37, 0xe814c87 | chained page-array anchor | [V] |
| bounds check before lookup | call 0xE83ABB0 | - | `0xe814a9d  call 0xE83ABB0` | sites: 0xe814a9d, update 0xe814bec, destroy 0xe815eba, resize 0xe815887, override 0xe815c57, create 0xe814403 | record-table bounds/guard check | [V] |
| guard-violation report | 0xBC5F110 + string 0xF7F68E3 | - | `0xe814ab5  lea rdx,[0xF7F68E3]`<br>`0xe814abe  call 0xBC5F110` | string: "FAILED: accessing a guarded paged heap backed array out of b..." | [V] |

## Table B — createTexture (slot 26): head of the management chain

| name | rva or offset | size | verbatim `0xRVA  instr` proof | meaning | tag |
| args: (this, handle u16, Memory* r8, flags r9d) | entry regs createTexture | 4/2/8/4 | `0xe8143e3  mov [rbp+0x28],r9d`<br>`0xe8143ef  mov [rbp+0x2E],dx`<br>`0xe8143e7  mov r14,r8` | flags/handle/Memory register map at entry | [V] |
| image-container chunk parse on Memory | call 0xEBD2160 | - | `0xe81452c  call 0xEBD2160`<br>`0xe814532  test al,al` | parse result tested | [V] meaning [I: bimg-style TEX chunk] |
| create body call | call 0xE81BF30 | - | `0xe81455b  call 0xE81BF30` | TextureD3D12 create body; sites: createTexture 0xe81455b, resizeTexture 0xe815b2a | [V] role [I 6hz/L8a] |
| create args on stack | stack createTexture | 8/4/1 | `0xe814548  mov [rsp+0x20],r14`<br>`0xe814541  mov eax,[rbp+0x28]`<br>`0xe814544  mov [rsp+0x28],eax`<br>`0xe814536  movzx eax,byte ptr [rbp+0xA0]`<br>`0xe81453d  mov [rsp+0x30],al` | record out [rbp+0x18], parsed chunk [rbp-0x40]; Memory/flags/skip byte | [V] mapping [I] |
| created handle/id copy into both halves | [rbp+0x20] | 4 | `0xe8145be  mov r14d,[rbp+0x20]`<br>`0xe814601  shl rcx,0x20`<br>`0xe814605  or rcx,r14` | out struct of 0xE81BF30 copied into both halves | [?] field meaning |
| create-notification table base | ctx+0x3C549F8 | 8 | `0xe8145cc  mov r12,[rdi+0x3C549F8]` | per-handle pending list header | [V] meaning [I] |
| notification get-or-create | ctx+0x14420 / +0x14428 | 8 | `0xe8145d3  lea r15,[r12+0x14420]`<br>`0xe8145db  add r12,0x14428`<br>`0xe8145e8  call 0xE83AED0` | paged-element get-or-create | [V] |
| entry store qword = {id,id<<32} | entry+0x00 | 8 | `0xe814612  mov [rax],rcx` | | [V] |
| entry "seen" flag byte | entry+0x08 | 1 | `0xe81460e  mov byte ptr [rax+8],1`<br>`0xe81464d  call 0xE83B0E0` (pre-existing-entry path) | seen flag | [V] meaning [?] |
| temp name string alloc size | string-alloc size no fixed address | - | `0xe814586  lea rdx,[r15*2+2]`<br>`0xe81458e  cmp rdx,0x1000`<br>`0xe814595  jb short 0xE8145B9`<br>`0xe8145b9  call 0xE935700` | name alloc size idx*2+2; cmp vs 0x1000 picks inline vs paged path | [V] purpose [?] |
| post-create state write | cmdlist+0x14458 / +0x30 createTexture | 8 | `0xe814652  mov rcx,[rdi+0x19F58]`<br>`0xe814659  mov rdx,[rcx+0x30]`<br>`0xe81465d  add rcx,0x14458`<br>`0xe814664  mov r8d,esi`<br>`0xe814667  mov r9d,r14d`<br>`0xe81466a  call 0xE82D960` | state-tracker call shared with updateTexture | [V] shape [I] |

## Table C — updateTexture (slot 28): upload/ring chain

| name | rva or offset | size | verbatim `0xRVA  instr` proof | meaning | tag |
| state-tracker call state 0x400 | cmdlist+0x14458 updateTexture | 4 | `0xe814bd8  mov r8d,r15d`<br>`0xe814bdb  mov r9d,0x400`<br>`0xe814be1  call 0xE82D960` | state 0x400 = ready/current tag | [V] meaning [I] |
| record current-state read | record+0x44 | 4 | `0xe814cfe  mov eax,[rbx+0x44]`<br>`0xe814ea9  cmp dword ptr [rbx+0x44],8` | per-handle state/flags word; cmp 8 = kind check | [V] meaning [I] |
| resource pointer at record+0x00 | record+0x00 | 8 | `0xe814bac  cmp qword ptr [rcx],0`<br>`0xe814d34  mov rcx,[rbx]` | ID3D12Resource* at record+0; sites: update 0xe814bac/0xe814d34, overrideInternal 0xe815d5f, getInternal 0xe815e90 | [V] |
| format byte at record+0xB0 (+ row pitch in readTexture) | record+0xB0 | 1 | `0xe814d10  movzx ecx,byte ptr [rbx+0xB0]`<br>`0xe815476  movzx ecx,byte ptr [r14+0xB0]`<br>`0xe81547e  call 0xEBD1570`<br>`0xe815487  imul r14d,r12d`<br>`0xe81548b  shr r14d,3` | format byte; readTexture computes bytes-per-row of the mip from it (sites: update 0xe814d10, readTexture 0xe815476..0xe81548b) | [V] meaning [I 6hz] result [I] |
| numMips byte | record+0xB1 | 1 | `0xe814d05  movzx eax,byte ptr [rbx+0xB1]` | numMips | [V] meaning [I 6hz] |
| copy size = word([chunk+4]) * bits/block >> 3 | copy-size formula no fixed address | 2 | `0xe814d1f  movzx eax,word ptr [r13+4]`<br>`0xe814d24  imul edi,eax`<br>`0xe814d27  shr edi,3` | bytes = block count * bits/block >> 3 | [V] formula [I] |
| device global | 0x12BB4910 | 8 | `0xe814d9d  mov rax,[0x12BB4910]` | live RendererContext base pointer; sites: update 0xe814d9d, destroy-path 0xe80f2fc, readback-status 0xe815618 | [V] meaning [I] |
| device for footprint query | ctx(deref)+0x400 then vtable+0x130 | 8 | `0xe814da4  mov rcx,[rax+0x400]`<br>`0xe814dab  mov rax,[rcx]`<br>`0xe814dae  mov rax,[rax+0x130]` | device vtable +0x130 = GetCopyableFootprints | [V] meaning [I] |
| ring placement call | record+0x08 desc ptr + ring sizes | 4 | `0xe814e0f  mov r8d,[rsp+0x88]`<br>`0xe814e17  add r15,8`<br>`0xe814e1b  lea rdx,[rsp+0x98]`<br>`0xe814e23  mov r9d,0x200`<br>`0xe814e2c  call 0xE8360F0` | upload-ring usage tag 0x200 | [V] meaning [I] |
| mapped-range descriptor | rax(ring)+0x10 / +0x1C | 8/4 | `0xe814e38  mov rax,[rsp+0x98]`<br>`0xe814e48  mov rcx,[rax+0x10]`<br>`0xe814e4f  cmp dword ptr [rax+0x1C],2` | used end +0x10, kind +0x1C | [V] |
| shared_ptr temp release | [r14+8] / [r14+0xC] | 4 | `0xe814e64  lock dec dword ptr [r14+8]`<br>`0xe814e7a  lock dec dword ptr [r14+0xC]` | refcount drops | [V] |

## Table D — readTexture (slot 30): readback chain

| name | rva or offset | size | verbatim `0xRVA  instr` proof | meaning | tag |
| readback state call state 0x800 | state arg r9d=0x800 | 4 | `0xe815242  mov r8d,ebp`<br>`0xe815245  mov r9d,0x800`<br>`0xe81524b  call 0xE82D960` | state 0x800 = readback | [V] meaning [I] |
| staging-view parse reuse | call 0x45EB90 | - | `0xe815250  mov rcx,[r14]`<br>`0xe815260  call 0x45EB90` | staging-view helper; record [r14] tested non-null first | [V] |
| readback label string | string 0xF84849C | - | `0xe81530c  mov dword ptr [rsp+0x28],0x400`<br>`0xe815314  lea r8,[0xF84849C]`<br>`0xe81532c  call 0xE815590` | string "LReadTextureReadback"; staged read view to slot helper | [V] purpose [I] |
| readback width | record+0x9C | 4 | `0xe81534e  mov rax,[r14+0x9C]`<br>`0xe815453  mov r12d,[r14+0x9C]`<br>`0xe81545c  shr r12d,cl` | width, mip-shifted | [V] meaning [I] |
| readback height | record+0xA0 | 4 | `0xe81545f  mov ebp,[r14+0xA0]`<br>`0xe81546e  shr ebp,cl` | height, mip-shifted | [V] meaning [I] |
| staging Map via vtable | staging + vtable +0x40 | 8 | `0xe8154b1  mov rax,[r15]`<br>`0xe8154b4  mov rax,[rax+0x40]`<br>`0xe8154c7  call qword ptr [0xF99FFA0]` | Map (CFG-thunk vtable +0x40) | [V] |
| per-row copy / 4-byte chunk stamp | call 0xEBCE390 | - | `0xe8154e6  call 0xEBCE390`<br>`0xe8154ff  dec ebp`<br>`0xe8154eb  mov edx,[rsp+0x128]`<br>`0xe8154f7  mov [rsp+0x78],rdx` | per-row copy out (caller buffer rdi += stride row); sites: readTexture 0xe8154e6, resizeTexture 0xe815a3d with `0xe815a34  mov r8d,4` | [V] target [I] |
| idle wait + fresh command list | this+0xCC9268 | 8 | `0xe815430  lea r12,[rsi+0xCC9268]`<br>`0xe81543f  call 0xE80ECB0`<br>`0xe815447  call 0xE81AC80`<br>`0xe81544c  mov [rsi+0x19F58],rax` | wait idle, open next list into current-list slot | [V] |
| staging view Release | staging + vtable +0x10 | 8 | `0xe81553e  mov rax,[r15]`<br>`0xe815541  mov rax,[rax+0x10]`<br>`0xe815545  mov rcx,r15`<br>`0xe815548  call qword ptr [0xF99FFA0]` | Release (vtable +0x10) | [V] |

## Table E — resizeTexture (slot 31)

| name | rva or offset | size | verbatim `0xRVA  instr` proof | meaning | tag |
| args: (this, handle dx, w r8d, h r9d) | entry regs resizeTexture | 2/4/4 | `0xe81586f  mov [rbp+0x8E],dx`<br>`0xe815869  mov ebx,r8d`<br>`0xe815866  mov edi,r9d` | register map at entry | [V] |
| new header block allocation | global allocator | 4 | `0xe8159b4  mov r8d,0x2C`<br>`0xe8159bf  call qword ptr [0xF99FFA0]` | 0x2C-byte block | [V] |
| refcount block init | [r14+8] = 0x1C | 4 | `0xe8159cd  mov dword ptr [r14+8],0x1C` | meaning [?] | [V] meaning [?] |
| new-record vtable trio | 0xF441980 / 0xF441990 / 0xF4419A0 | 8 | `0xe8159eb  lea rax,[0xF441980]`<br>`0xe8159f6  lea rax,[0xF441990]`<br>`0xe815a01  lea rax,[0xF4419A0]` | identity [?] | [V] identity [?] |
| 'TEX\0' magic stamp | [rbp+0x88] | 4 | `0xe815a17  mov dword ptr [rbp+0x88],0x584554` | same chunk magic as createTexture | [V] meaning [I] |
| requested-format byte of old record | record+0xAF | 1 | `0xe815a65  movzx ecx,byte ptr [rsi+0xAF]`<br>`0xe815a83  mov [rbp+0x70],ecx` | requested format | [V] meaning [I] |
| flags copy for the new create | record+0x98 | 4 | `0xe815ace  mov r12d,[rsi+0x98]`<br>`0xe815b0d  mov [rsp+0x28],r12d` | flags | [V] meaning [I] |
| temp block frees | call 0xE935700 / Release | - | `0xe815b6d  call 0xE935700`<br>`0xe815b72  mov rcx,[r14]`<br>`0xe815b75  cmp rcx,r15`<br>`0xe815b86  call qword ptr [0xF99FFA0]` | temp allocator free (0xE935700, shared with createTexture temp name path) / object Release | [V] |

## Table G — shared resource destructor 0xE80F290 (destroy/shared tail)

| name | rva or offset | size | verbatim `0xRVA  instr` proof | meaning | tag |
| staging holder release | record-ish +0x90 | 8 | `0xe80f2be  cmp qword ptr [rsi+0x90],0`<br>`0xe80f2d3  mov rax,[rax+0x48]`<br>`0xe80f2e4  mov qword ptr [rsi+0x90],0` | wrapper holding the upload staging resource | [V] meaning [I] |
| external bit respected on destroy | [rsi+0x9B] bit 0x40 | 1 | `0xe80f2ef  test byte ptr [rsi+0x9B],0x40`<br>`0xe80f2f6  jne 0xE80F5BB` | external objects must not be destroyed here | [V] meaning [I] |
| destroyed resource queued on batcher vector | cmdlist+0x2CBE8 / +0x2CBF0 / +0x2CBE0 | 8 | `0xe80f34e  mov [rax],rdx`<br>`0xe80f351  add qword ptr [rbx+0x2CBE8],8`<br>`0xe80f385  shr rbp,1`<br>`0xe80f388  add rbp,r15`<br>`0xe80f38f  mov rdi,r12` | deferred-release list on the frame command list (1.5x growth) | [V] meaning [I] |
| allocator used for growth | 0x12ADF800 | 8 | `0xe80f3a0  mov rcx,[0x12ADF800]`<br>`0xe80f3d1  call qword ptr [0xF99FFA0]` | global allocator | [V] |
| destructor entry sites | call 0xE80F290 | - | `0xe815fba  jmp 0xE80F290` | destroyTexture tail-jump (0xe815fb0 `mov rcx,rsi`); resizeTexture destroys its old resource at 0xe815ac9 via the same destructor | [V] |

## Table F — overrideInternal (slot 32) / getInternal (slot 33)

| name | rva or offset | size | verbatim `0xRVA  instr` proof | meaning | tag |
| override: flag record "external" | record+0x9B | 1 | `0xe815d58  or byte ptr [rdi+0x9B],0x40`<br>`0xe815d9c  jb short 0xE815DBE` | bit 0x40 = overridden/external | [V] bit meaning [I] |
| override/getInternal: global side-flag | 0x12AE1750 | 1 | `0xe815c3f  mov byte ptr [0x12AE1750],1`<br>`0xe815d7a  mov byte ptr [0x12AE1750],1` | set by both override and getInternal | [V] meaning [?] |

## Table H — atlas blit (slot 51) + blitSetup (slot 52)

| name | rva or offset | size | verbatim `0xRVA  instr` proof | meaning | tag |
| slot 51 reads cmd list + stats words | this+0x19F58 / +0x19F60 / +0x19F90 / +0x19F94 | 8/4/4 | `0xe818be9  mov rsi,[rcx+0x19F58]`<br>`0xe818bf0  mov rax,[rcx+0x19F60]`<br>`0xe818bf7  mov r14,[rax]`<br>`0xe818bfa  mov edi,[rcx+0x19F90]`<br>`0xe818c00  mov ebx,[rcx+0x19F94]` | 0x19F90/0x19F94 feed the blit desc w/h | [V] meanings [I] |
| blit desc stamp {0,0,w,h} + double constant | [rsp+0xF8..0x110] | 8 | `0xe818c29  mov qword ptr [rsp+0xF8],0`<br>`0xe818c47  movsd xmm0,[0xEFD32F0]`<br>`0xe818c4f  movsd [rsp+0x108],xmm0` | two 8-byte stores | [V] constant meaning [?] |
| blit op code to batch builder | r8d blit op | 4 | `0xe818d1e  mov r8d,0x8F`<br>`0xe818d2d  call 0xE81E860` | op code 0x8F | [V] meaning [?] |
| lex table slot for blit mapper | cmdlist+0x24 / +0x20 | 8/2 | `0xe818cd2  lea rax,[rsi+0x24]`<br>`0xe818cd6  movzx ecx,word ptr [rsi+0x20]`<br>`0xe818cda  movzx edx,word ptr [r12+0x6C]` | {handler, handle} pair header | [V] meaning [I] |
| vertex-layout record pick | ctx+0xC96198 + idx*0x54 | 8 | `0xe818cb4  mov rax,[r12+8]`<br>`0xe818cb9  movzx eax,word ptr [rax+0x14]`<br>`0xe818cbd  imul rax,0x54`<br>`0xe818cc1  add rax,r15`<br>`0xe818cc4  add rax,0xC96198` | idx from blit-desc word +0x14 | [V] meaning [I: 6hx vertex-layout table] |
| program record pick | ctx+0xB62178 + idx*0xF8 word +0xAE | 2 | `0xe818dab  lea rbp,[r15+0xB62178]`<br>`0xe818e6d  movzx eax,word ptr [r12+0x6C]`<br>`0xe818e73  imul rcx,rax,0xF8`<br>`0xe818e7e  mov rcx,[rbp+rcx]`<br>`0xe818e8e  movzx r15d,word ptr [rcx+0xAE]`<br>`0xe818e9e  mov rax,[rax+8]`<br>`0xe818ea7  movzx ebx,word ptr [rax+0xAE]` | +0xAE inside the 6au program record | [V] +0xAE meaning [?] |
| blitSetup per-handle touched bitset | cmdlist+0x48 + idx*8 | 8 | `0xe8197a0  mov rdx,[rbx+rax*8+0x48]`<br>`0xe8197ae  bt rdx,rcx`<br>`0xe819822  or rdx,r8`<br>`0xe819825  mov [rbx+rax*8+0x48],rdx` | per-handle touched bitmap over record id | [V] meaning [I] |
| blitSetup per-handle state dword 0x400 | cmdlist+0x24C + idx*8 | 4 | `0xe8197b4  mov eax,[rbx+rcx*8+0x24C]`<br>`0xe8197bb  cmp eax,0x400`<br>`0xe8197ca  mov dword ptr [rbx+rcx*8+0x24C],0x400`<br>`0xe8197fb  mov dword ptr [rsp+0x58],0x400` | same ready tag as updateTexture state call | [V] 0x400 meaning [I] |
| blitSetup record fetch | [cmdlist+0x38] elem idx*0x78 | 8 | `0xe8197d5  mov r8,[rbx+0x38]`<br>`0xe8197d9  imul rcx,0x78`<br>`0xe8197dd  mov rcx,[r8+rcx]` | 0x78-stride buffer record table | [V] meaning [I] |
| barrier on that record | vtable +0xD0 | - | `0xe819803  mov rax,[rdx]`<br>`0xe819806  mov rax,[rax+0xD0]`<br>`0xe81980d  lea r8,[rsp+0x40]`<br>`0xe81981a  call qword ptr [0xF99FFA0]` | ResourceBarrier emission | [V] |
| blitSetup pending-handle append | cmdlist+0x40 / +0x8248+idx*2 / +0x248+idx*8 | 2/2/8 | `0xe81982a  movzx eax,word ptr [rbx+0x40]`<br>`0xe81982e  mov [rbx+rax*2+0x8248],cx`<br>`0xe819838  mov [rbx+0x40],ax`<br>`0xe81983c  mov rax,0x40000000400`<br>`0xe819846  mov [rbx+rcx*8+0x248],rax` | upload/barrier pending queue beside the 0x78 records | [V] meaning [I] |
| second record family (vertex side) | cmdlist+0xA248 / +0xA250 / +0xA258 / +0xA45C / +0x12458 | 8/2/8/4/2 | `0xe8198af  mov rax,[rax+0xA248]`<br>`0xe8198b6  shl ecx,7`<br>`0xe8198b9  mov rax,[rax+rcx]`<br>`0xe81990a  movzx edx,word ptr [rax+0xA250]`<br>`0xe819911  mov [rax+rdx*2+0x12458],cx`<br>`0xe819922  mov rdx,0x40000000400`<br>`0xe81992c  mov [rax+rcx*8+0xA458],rdx` | 0x80-stride dynamic vertex table (6ba base 0x9B2178) | [V] identity [I] |
| blitSetup type filter | type filter r8d no fixed address | 4 | `0xe819763  mov r15d,r8d`<br>`0xe819766  lea eax,[r15*4]`<br>`0xe81976e  cmp eax,6`<br>`0xe819771  jb 0xE819B35` | accepts type >= 2 only | [V] meaning [?] |

## Atlas management — registration (proven [V]) and blit consumer (proven [V]); stitcher not found

| name | rva or offset | size | verbatim `0xRVA  instr` proof | meaning | tag |
| atlas name "TerrainAtlas" idx 6 | str data 0xF55CDD3 | - | `0x186f731  lea rax,[0xF55CDD3]` | name loaded inside sub_186e6a0; idx 6 via sub_1870de0 | [V] |
| atlas name "ItemAtlas" idx 7 | str data 0xF55CDE0 | - | `0x186f7fc  lea rax,[0xF55CDE0]` | name loaded inside sub_186e6a0; idx 7 via sub_1870de0 | [V] |
| registration index store | registered object +8 | 4 | `0x1870ecb  mov [rsi+8],eax` | index (6 TerrainAtlas / 7 ItemAtlas) stored at obj+8 inside sub_1870de0 | [V] |
| TerrainAtlasBlit task name | str data 0xF539A0B | - | `0xbb431ee  lea rdx,[0xF539A0B]` | task-16 name referenced inside 0xbb418d0; functor vtable 0xF43E9E0 | [V] |
| atlas blit body (consumer, not creator) | code 0xbc02090 | - | `0xbc020c4  mov rbx,rcx` | sub_bc02090 reads atlas fields +0x88/+0x8C/+0x48/+0xDC/+0x11C and byte +0x98, uploads via 0xEBCE390; reached via functor vtable 0xF43E9E0 slot 2; no static callers | [V] |
| atlas texture-creation stitcher | not located | - | - | xref to str "ItemAtlas" refs=[(0x186f7fc,0x186e6a0)] only; no createTexture/resizeTexture call tied to either atlas; static analysis exhausted per the L8 series | not located | [?] |

## CLOSES?

NO — every texture-management row above is proven [V] (slots 26/28/30/31/32/33/34/51/52 entries; shared record-table lookup Table A; create/update/read/resize/override/getInternal/destroy Tables B-G; blit/blitSetup Table H), and atlas registration ("TerrainAtlas" idx 6 str 0xF55CDD3, "ItemAtlas" idx 7 str 0xF55CDE0 via sub_186e6a0/sub_1870de0 storing obj+8) plus the TerrainAtlasBlit blit consumer (sub_bc02090 via functor vtable 0xF43E9E0 slot 2) are [V]-proven. But the pending part "texture/atlas management" is not fully proven: the atlas texture-creation stitcher — who builds the TerrainAtlas/ItemAtlas texture description and calls createTexture/resizeTexture with atlas parameters — is not located in the executable (xref to str "ItemAtlas" refs=[(0x186f7fc,0x186e6a0)] only; no createTexture/resizeTexture call tied to either atlas; static analysis exhausted). That stitcher is tracked by L8b/U-L8, so the checklist line cannot be ticked here. Single blocking fact: atlas texture-creation stitcher not located in the executable.

## TOOL REQUESTS

- None (all rows come from the precomputed rdis data; verify_oc.py confirms every quoted instruction line).
