## NEXT
DONE

# U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Item line (RENDER_CHECKLIST.md L-section, line 338): "- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending". The line has two halves: (1) sampler flag decode + sampler cache (6ax), already closed [V]; (2) texture/atlas management, the part marked pending — this unit covers half 2.

Half 1 — sampler flag decode + sampler cache (6ax), already closed [V] (cited, not re-derived):
- docs/functions/e820500.md decodes 0xe820500 instruction-complete: key = bgfx HashMurmur2A (seed 0) over min(count,16) u32 flag words, finalised inline at 0xe820564..0xe8205bf (constants 0x5bd1e995, shifts 24/13/15); open hash map at heap+0x60 (bucket vector begin/end +0x68/+0x70; node+0x00 = key u32, node+0x08 = u16 slot, node+0x10 = next); insert via 0xe805e50 with re-hash 0xe806410 when needed; u16 free ring at heap+8 (head +0, count +2, ring +4; 0xFFFF = exhausted); per sampler the D3D12_SAMPLER_DESC is filled on the stack and ID3D12Device::CreateSampler (device [ctx+0x400], vtable +0xB0) creates into CPU handle heap+0x10 + ((u16 heap[+0x24] * slot + i) * u32 heap[+0x20]) (+0x20 descriptor increment, +0x24 descriptors per group); return value = heap slot group index (bx), 0xFFFF when the free list is exhausted.
- Field decode [V]: AddressU/V/W = {1,2,3,4}[flags&3 / (flags>>2)&3 / (flags>>4)&3]; min filter (flags>>6)&3, mag filter (flags>>8)&3, mip filter bit 10; comparison = table[(flags>>16)&0xF] or 1; MaxAnisotropy = [ctx+0x19FD8] (read once at 0xe8206ab into D3D12_SAMPLER_DESC+0x14); MaxLOD = flags&0x10000000 ? 3.0 : FLT_MAX; border colour copied from the r9 table indexed by (flags>>24)&0xF, gated on a BORDER address mode.
- src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts for this decode. 0xe820500 is called twice from the draw executor: from blit 0xe818bc0 and from executor 0xe821120 (6ao).
- Correction vs 6ax: bit 28 (0x10000000) selects MaxLOD 3.0 vs FLT_MAX — it is NOT the border-colour selector; the border colour comes from the r9 table (bits 24..27) gated by BORDER address mode.

Half 2 — texture/atlas management (the part marked pending in the item line). Instruction-proven here is the D3D12 backend texture-management chain over the guarded texture record table (this+0xBDE178, stride 0xB8): slots 26 createTexture (0xe8143c0), 28 updateTexture (0xe814a70), 30 readTexture (0xe8150f0), 31 resizeTexture (0xe815840), 32 overrideInternal (0xe815c30), 33 getInternal (0xe815d70), 34 destroyTexture (0xe815ea0), the shared destructor tail 0xe80f290, blit slot 51 (0xe818bc0) and blitSetup slot 52 (0xe819750); 0xe820500 (sampler cache) is consumed from those paths.
Rules: every row = one distinct offset; all its read/store sites are listed; every `0xRVA  instr` line is verbatim from rdis disassembly of the 1.26.62.01 exe; tag [V] = instruction seen at the cited RVA (verified), [I] = inferred meaning, '-' = no instruction/string shows a meaning. Extended interpretations (guard-bit meaning, table roles, state-tag meaning) are [I] notes below the tables, not row claims.

Not proven in this unit (blocking fact, see CLOSES?): the Minecraft-side texture/atlas management — ClientTexture/BedrockTexture/TexturePtr pack->GPU caller chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00, last decoded call 0x54227af into undecoded callee 0x18718D0) and the terrain/item atlas stitchers plus mip/compression builders — tracked by open items L8a/L8b (oc_U-EL8a.md, oc_U-EL8b.md; agent notes only, [I], not proof).

## Table 1 — texture record table (shared by every texture slot; this = RendererContextD3D12)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| texture record table base | this+0xBDE178 | 8 | R: `0xe814a8c  lea rbx,[rcx+0xBDE178]` | record table base computed from context | [V] |
| record stride | 0xB8 | 4 | `0xe814ac3  imul r9,r15,0xB8` | 0xB8 stride immediate used in index math | [V] |
| overflow-page guard flag | this+0xC96190 | 1 | R: `0xe814aab  cmp byte ptr [r14+0xC96190],0` | guard byte compared against 0 | [V] |
| page-list anchor for detached handles | this+0xC96178 | 8 | R: `0xe814ae7  mov rax,[r14+0xC96178]` | page-list pointer loaded | [V] |
| address bounds check | call 0xE83ABB0 | - | `0xe814a9d  call 0xE83ABB0` | - | [V] |
| guard-violation report | 0xBC5F110, string 0xF7F68E3 | - | W: `0xe814ab5  lea rdx,[0xF7F68E3]` / `0xe814abe  call 0xBC5F110` | string pointer prepared for the report call | [V] |

## Table 2 — createTexture (slot 26, 0xe8143c0..0xe8146a1, size 0x2e1): head of the management chain

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| createTexture entry | 0xe8143c0 | - | `0xe8143c0  push rbp` | slot-26 entry (name/slot from vtable map 6k, [I]) | [V] |
| args: (this, handle u16, Memory* r8, flags r9d) | regs | 4/2/8/4 | W: `0xe8143e3  mov [rbp+0x28],r9d` / W: `0xe8143ef  mov [rbp+0x2E],dx` / `0xe8143e7  mov r14,r8` | flags/handle/Memory spilled to stack frame | [V] |
| container chunk parse | 0xEBD2160 | - | `0xe81452c  call 0xEBD2160` / `0xe814532  test al,al` | bimg-style image container parse, result tested | [V] |
| create body call | 0xE81BF30 | - | `0xe81455b  call 0xE81BF30` | TextureD3D12::create body (role [I 6hz]) | [V] |
| create-notification table base | ctx+0x3C549F8 | 8 | R: `0xe8145cc  mov r12,[rdi+0x3C549F8]` | per-handle pending-notification list header [I] | [V] |
| notification get-or-create | ctx+0x14420 / +0x14428 | 8 | `0xe8145d3  lea r15,[r12+0x14420]` / `0xe8145db  add r12,0x14428` / `0xe8145e8  call 0xE83AED0` | get-or-create the per-handle notification entry | [V] |
| entry id store {id,id<<32} | entry+0x00 | 8 | W: `0xe814612  mov [rax],rcx` | qword {id, id<<32} stored into the entry | [V] |
| entry "seen" flag byte | entry+0x08 | 1 | W: `0xe81460e  mov byte ptr [rax+8],1` | seen flag set on existing-entry path (pre-existing path calls 0xE83B0E0 at 0xe81464d) | [V] |
| temp name string alloc | - | - | `0xe81458e  cmp rdx,0x1000` / `0xe8145b9  call 0xE935700` | allocation of the temp name (size idx*2+2 [I]); purpose [?] | [V] |
| post-create state write | cmdlist+0x14458 / +0x30 | 8 | R: `0xe814652  mov rcx,[rdi+0x19F58]` / R: `0xe814659  mov rdx,[rcx+0x30]` / `0xe81465d  add rcx,0x14458` | command-list state slot addressed; same state-tracker call as Table 3 row 16 [I] | [V] |

## Table 3 — updateTexture (slot 28, 0xe814a70..0xe8150e3): upload/ring chain

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| updateTexture entry | 0xe814a70 | - | `0xe814a70  push r15` | slot-28 entry | [V] |
| state-tracker call state 0x400 | r9d | 4 | `0xe814bd8  mov r8d,r15d` / `0xe814bdb  mov r9d,0x400` / `0xe814be1  call 0xE82D960` | state transition with state value 0x400 [I] | [V] |
| record current-state read | record+0x44 | 4 | R: `0xe814cfe  mov eax,[rbx+0x44]` / `0xe814ea9  cmp dword ptr [rbx+0x44],8` | per-handle state/flags word; kind check vs 8 | [V] |
| resource pointer | record+0x00 | 8 | R: `0xe814bac  cmp qword ptr [rcx],0` / R: `0xe814d34  mov rcx,[rbx]` | ID3D12Resource* loaded from record | [V] |
| record block byte (actual format) | record+0xB0 | 1 | R: `0xe814d10  movzx ecx,byte ptr [rbx+0xB0]` | format byte read for footprint math | [V] |
| record numMips byte | record+0xB1 | 1 | R: `0xe814d05  movzx eax,byte ptr [rbx+0xB1]` | mip count byte read | [V] |
| copy size math | word at [chunk+4] | 2 | `0xe814d1f  movzx eax,word ptr [r13+4]` / `0xe814d24  imul edi,eax` / `0xe814d27  shr edi,3` | copy size = block word * format bits >> 3 [I] | [V] |
| device for footprint query | [ctx+0x400] via 0x12BB4910 | 8 | R: `0xe814d9d  mov rax,[0x12BB4910]` / R: `0xe814da4  mov rcx,[rax+0x400]` / R: `0xe814dab  mov rax,[rcx]` / R: `0xe814dae  mov rax,[rax+0x130]` | device fetched; vtable +0x130 = GetCopyableFootprints [I] | [V] |
| device global | 0x12BB4910 | 8 | R: `0xe814d9d  mov rax,[0x12BB4910]` | live renderer-context base pointer [I] | [V] |
| ring placement call | record+0x08 desc ptr | 4 | `0xe814e17  add r15,8` / `0xe814e0f  mov r8d,[rsp+0x88]` / `0xe814e1b  lea rdx,[rsp+0x98]` / `0xe814e23  mov r9d,0x200` / `0xe814e2c  call 0xE8360F0` | upload-ring placement; 0x200 = ring usage tag [I] | [V] |
| mapped-range descriptor | ring+0x10 / +0x1C | 8/4 | R: `0xe814e38  mov rax,[rsp+0x98]` / R: `0xe814e48  mov rcx,[rax+0x10]` / R: `0xe814e4f  cmp dword ptr [rax+0x1C],2` | used-end + kind dword of the mapped range | [V] |
| shared_ptr temp release | [r14+8] / [r14+0xC] | 4 | W: `0xe814e64  lock dec dword ptr [r14+8]` / W: `0xe814e7a  lock dec dword ptr [r14+0xC]` | double refcount release of the temp | [V] |

## Table 4 — readTexture (slot 30, 0xe8150f0..0xe815587): readback chain

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| readTexture entry | 0xe8150f0 | - | `0xe8150f0  push r15` | slot-30 entry | [V] |
| state-tracker call state 0x800 | r9d | 4 | `0xe815242  mov r8d,ebp` / `0xe815245  mov r9d,0x800` / `0xe81524b  call 0xE82D960` | state transition with state value 0x800 [I] | [V] |
| staging-view parse reuse | 0x45EB90 | - | R: `0xe815250  mov rcx,[r14]` / `0xe815260  call 0x45EB90` | staging view parsed, record pointer tested non-null first | [V] |
| readback label string | 0xF84849C | - | `0xe815314  lea r8,[0xF84849C]` | string "LReadTextureReadback" loaded as the readback label | [V] |
| readback width | record+0x9C | 4 | R: `0xe81534e  mov rax,[r14+0x9C]` / R: `0xe815453  mov r12d,[r14+0x9C]` / `0xe81545c  shr r12d,cl` | width read, shifted by mip level | [V] |
| readback height | record+0xA0 | 4 | R: `0xe81545f  mov ebp,[r14+0xA0]` / `0xe81546e  shr ebp,cl` | height read, shifted by mip level | [V] |
| format byte for row pitch | record+0xB0 | 1 | R: `0xe815476  movzx ecx,byte ptr [r14+0xB0]` / `0xe81547e  call 0xEBD1570` / `0xe815487  imul r14d,r12d` / `0xe81548b  shr r14d,3` | format -> bits/block -> bytes per row of the mip | [V] |
| staging Map via vtable | staging+vt+0x40 | 8 | R: `0xe8154b1  mov rax,[r15]` / R: `0xe8154b4  mov rax,[rax+0x40]` / `0xe8154c7  call qword ptr [0xF99FFA0]` | Map fetched through the staging object's vtable | [V] |
| per-row copy out | 0xEBCE390 | - | `0xe8154e6  call 0xEBCE390` / `0xe8154ff  dec ebp` / `0xe8154eb  mov edx,[rsp+0x128]` / `0xe8154f7  mov [rsp+0x78],rdx` | per-row copy loop; next-row stride reloaded per iteration | [V] |
| renderer idle wait | this+0xCC9268 | 8 | R: `0xe815430  lea r12,[rsi+0xCC9268]` / `0xe81543f  call 0xE80ECB0` / `0xe815447  call 0xE81AC80` / W: `0xe81544c  mov [rsi+0x19F58],rax` | queue wait, next command list opened, stored at ctx+0x19F58 | [V] |
| staging view Release | staging+vt+0x10 | 8 | R: `0xe81553e  mov rax,[r15]` / R: `0xe815541  mov rax,[rax+0x10]` / `0xe815545  mov rcx,r15` / `0xe815548  call qword ptr [0xF99FFA0]` | staging view released via vtable +0x10 | [V] |

## Table 5 — resizeTexture (slot 31, 0xe815840..0xe815bee)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| resizeTexture args | regs | 2/4/4 | W: `0xe81586f  mov [rbp+0x8E],dx` / `0xe815869  mov ebx,r8d` / `0xe815866  mov edi,r9d` | handle (dx), width (r8d), height (r9d) spilled | [V] |
| new header block alloc | global allocator | 4 | `0xe8159b4  mov r8d,0x2C` / `0xe8159bf  call qword ptr [0xF99FFA0]` | 0x2C-byte header block allocated | [V] |
| refcount block init | [r14+8] = 0x1C | 4 | W: `0xe8159cd  mov dword ptr [r14+8],0x1C` | refcount-like dword initialised | [V] |
| new-record vtable trio | 0xF441980 / 0xF441990 / 0xF4419A0 | 8 | `0xe8159eb  lea rax,[0xF441980]` / `0xe8159f6  lea rax,[0xF441990]` / `0xe815a01  lea rax,[0xF4419A0]` | three vtable pointers installed in the new record | [V] |
| 'TEX\0' magic stamp | [rbp+0x88] | 4 | W: `0xe815a17  mov dword ptr [rbp+0x88],0x584554` | TEX chunk magic stamped (same as createTexture container) [I] | [V] |
| chunk stamp into block | 0xEBCE390 | - | `0xe815a3d  call 0xEBCE390` / `0xe815a34  mov r8d,4` | chunk data stamped into the block | [V] |
| requested-format byte read | record+0xAF | 1 | R: `0xe815a65  movzx ecx,byte ptr [rsi+0xAF]` / W: `0xe815a83  mov [rbp+0x70],ecx` | old record's requested format byte copied out | [V] |
| destroy old resource before re-create | 0xE80F290 | - | `0xe815ac9  call 0xE80F290` | old resource released via the shared destructor | [V] |
| flags copy for new create | record+0x98 | 4 | R: `0xe815ace  mov r12d,[rsi+0x98]` / W: `0xe815b0d  mov [rsp+0x28],r12d` | record flags copied into the new create args | [V] |
| re-create through body | 0xE81BF30 | - | `0xe815b2a  call 0xE81BF30` | same create body as Table 2 | [V] |
| temp block frees | 0xE935700 / Release | - | `0xe815b6d  call 0xE935700` / `0xe815b72  mov rcx,[r14]` / `0xe815b75  cmp rcx,r15` / `0xe815b86  call qword ptr [0xF99FFA0]` | temp freed, then the resource Released | [V] |

## Table 6 — overrideInternal / getInternal / destroyTexture (slots 32/33/34, 0xe815c30..0xe815fbf)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| override entry | 0xe815c30 | - | `0xe815c30  push r14` | slot-32 entry | [V] |
| override: swap record pointer | record+0x00 | 8 | R: `0xe815c39  mov rsi,r8` / W: `0xe815d5f  mov [rdi],rsi` | caller's external object swapped into the record | [V] |
| override: flag record "external" | record+0x9B | 1 | W: `0xe815d58  or byte ptr [rdi+0x9B],0x40` / `0xe815d9c  jb short 0xE815DBE` | bit 0x40 set = overridden/external record | [V] |
| override/getInternal: global side-flag | 0x12AE1750 | 1 | W: `0xe815c3f  mov byte ptr [0x12AE1750],1` / W: `0xe815d7a  mov byte ptr [0x12AE1750],1` | global flag set on both paths | [V] |
| getInternal entry | 0xe815d70 | - | `0xe815d70  push rsi` | slot-33 entry | [V] |
| getInternal: return [record] | record+0x00 | 8 | R: `0xe815e90  mov rax,[rsi]` | record pointer returned to caller | [V] |
| destroyTexture entry | 0xe815ea0 | - | `0xe815ea0  push rsi` | slot-34 entry | [V] |
| destroyTexture: release record's resource | record -> 0xE80F290 | - | `0xe815fb0  mov rcx,rsi` / `0xe815fba  jmp 0xE80F290` | tail-jumps into the shared destructor | [V] |

## Table 7 — resource destructor 0xe80f290 (destroy/shared tail)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| staging holder release | this+0x90 | 8 | R: `0xe80f2be  cmp qword ptr [rsi+0x90],0` / R: `0xe80f2d3  mov rax,[rax+0x48]` / W: `0xe80f2e4  mov qword ptr [rsi+0x90],0` | staging holder released and nulled | [V] |
| external bit respected on destroy | [rsi+0x9B] bit 0x40 | 1 | R: `0xe80f2ef  test byte ptr [rsi+0x9B],0x40` / `0xe80f2f6  jne 0xE80F5BB` | external records skip destruction here | [V] |
| deferred-release queue | cmdlist+0x2CBE8 / +0x2CBF0 / +0x2CBE0 | 8 | W: `0xe80f34e  mov [rax],rdx` / W: `0xe80f351  add qword ptr [rbx+0x2CBE8],8` / `0xe80f385  shr rbp,1` / `0xe80f388  add rbp,r15` | resource queued on the per-frame deferred-release list; 1.5x growth | [V] |
| allocator for growth | 0x12ADF800 | 8 | R: `0xe80f3a0  mov rcx,[0x12ADF800]` / `0xe80f3d1  call qword ptr [0xF99FFA0]` | global allocator used for queue growth | [V] |

## Table 8 — blit slot 51 (0xe818bc0..0xe819746) + blitSetup slot 52 (0xe819750..0xe819b48)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| blit entry | 0xe818bc0 | - | `0xe818bc0  push r15` | slot-51 entry | [V] |
| blit command list + stats words | this+0x19F58 / +0x19F60 / +0x19F90 / +0x19F94 | 8/4/4 | R: `0xe818be9  mov rsi,[rcx+0x19F58]` / R: `0xe818bf0  mov rax,[rcx+0x19F60]` / R: `0xe818bf7  mov r14,[rax]` / R: `0xe818bfa  mov edi,[rcx+0x19F90]` / R: `0xe818c00  mov ebx,[rcx+0x19F94]` | command-list wrapper + per-kind pending counters loaded | [V] |
| blit desc stamp {0,0,w,h} + double constant | [rsp+0xF8..0x108] | 8 | W: `0xe818c29  mov qword ptr [rsp+0xF8],0` / `0xe818c47  movsd xmm0,[0xEFD32F0]` / W: `0xe818c4f  movsd [rsp+0x108],xmm0` | desc zeroed; double constant from 0xEFD32F0 stored | [V] |
| blit op 0x8F to batch builder | r8d | 4 | `0xe818d1e  mov r8d,0x8F` / `0xe818d2d  call 0xE81E860` | blit op code 0x8F passed to the batch builder | [V] |
| blit lex table slot | cmdlist+0x24 / +0x20 | 8/2 | R: `0xe818cd2  lea rax,[rsi+0x24]` / R: `0xe818cd6  movzx ecx,word ptr [rsi+0x20]` / R: `0xe818cda  movzx edx,word ptr [r12+0x6C]` | lex entry {handler, handle} pair addressed | [V] |
| blit vertex-layout record pick | ctx+0xC96198 + idx*0x54 | 8 | R: `0xe818cb4  mov rax,[r12+8]` / R: `0xe818cb9  movzx eax,word ptr [rax+0x14]` / `0xe818cbd  imul rax,0x54` / `0xe818cc1  add rax,r15` / `0xe818cc4  add rax,0xC96198` | vertex-layout record selected via word+0x14 index, stride 0x54 | [V] |
| blit program record pick | ctx+0xB62178 + idx*0xF8, word +0xAE | 2 | R: `0xe818dab  lea rbp,[r15+0xB62178]` / R: `0xe818e6d  movzx eax,word ptr [r12+0x6C]` / `0xe818e73  imul rcx,rax,0xF8` / R: `0xe818e7e  mov rcx,[rbp+rcx]` / R: `0xe818e8e  movzx r15d,word ptr [rcx+0xAE]` / R: `0xe818e9e  mov rax,[rax+8]` / R: `0xe818ea7  movzx ebx,word ptr [rax+0xAE]` | program record (0xF8 stride) and its +0xAE word picked | [V] |
| blitSetup entry | 0xe819750 | - | `0xe819750  push r15` | slot-52 entry | [V] |
| blitSetup type filter (*4 < 6 rejected) | - | 4 | `0xe819763  mov r15d,r8d` / `0xe819766  lea eax,[r15*4]` / `0xe81976e  cmp eax,6` / `0xe819771  jb 0xE819B35` | types < 2 rejected | [V] |
| blitSetup touched bitset | cmdlist+0x48 + idx*8 | 8 | R: `0xe8197a0  mov rdx,[rbx+rax*8+0x48]` / R: `0xe8197ae  bt rdx,rcx` / `0xe819822  or rdx,r8` / W: `0xe819825  mov [rbx+rax*8+0x48],rdx` | per-handle touched-bit bitmap updated | [V] |
| blitSetup state dword 0x400 | cmdlist+0x24C + idx*8 | 4 | R: `0xe8197b4  mov eax,[rbx+rcx*8+0x24C]` / `0xe8197bb  cmp eax,0x400` / W: `0xe8197ca  mov dword ptr [rbx+rcx*8+0x24C],0x400` / W: `0xe8197fb  mov dword ptr [rsp+0x58],0x400` | per-handle state dword set to 0x400 (same ready tag as Table 3 row 2) [I] | [V] |
| blitSetup record fetch (0x78 stride) | [cmdlist+0x38] idx*0x78 | 8 | R: `0xe8197d5  mov r8,[rbx+0x38]` / `0xe8197d9  imul rcx,0x78` / R: `0xe8197dd  mov rcx,[r8+rcx]` | 0x78-stride buffer record fetched (0x93A178 family) | [V] |
| blitSetup barrier on that record | vtable +0xD0 | - | R: `0xe819806  mov rax,[rax+0xD0]` / `0xe81980d  lea r8,[rsp+0x40]` / `0xe81981a  call qword ptr [0xF99FFA0]` | ResourceBarrier emitted for the record | [V] |
| blitSetup pending-handle append | cmdlist+0x40 / +0x8248+idx*2 / +0x248+idx*8 | 2/2/8 | `0xe81982a  movzx eax,word ptr [rbx+0x40]` / W: `0xe81982e  mov [rbx+rax*2+0x8248],cx` / W: `0xe819838  mov [rbx+0x40],ax` / `0xe81983c  mov rax,0x40000000400` / W: `0xe819846  mov [rbx+rcx*8+0x248],rax` | pending handle appended; state word 0x40000000400 stored | [V] |
| blitSetup second record family (0x80 stride) | cmdlist+0xA248 / +0xA250 / +0xA258 / +0xA458 / +0x12458 | 8/2/8/4/2 | R: `0xe8198af  mov rax,[rax+0xA248]` / `0xe8198b6  shl ecx,7` / R: `0xe8198b9  mov rax,[rax+rcx]` / R: `0xe81990a  movzx edx,word ptr [rax+0xA250]` / W: `0xe819911  mov [rax+rdx*2+0x12458],cx` / `0xe819922  mov rdx,0x40000000400` / W: `0xe81992c  mov [rax+rcx*8+0xA458],rdx` | 0x80-stride dynamic vertex table (0x9B2178 family) | [V] |

## Interpretations ([I] notes, not row claims)

- Guard byte this+0xC96190: bit = guard enabled for handles >= 0x1000; detached handles use the page list at this+0xC96178 (+0xB8000 per page) [I 6z].
- Record fields seen by the instructions: record+0x00 ID3D12Resource*, record+0x44 state/flags word, record+0x98 flags, record+0xAF requested format, record+0xB0 actual format byte, record+0xB1 numMips, record+0x9C width, record+0xA0 height [I field roles per 6z/6z-2].
- State value 0x400 passed to 0xe82d960 (updateTexture) and 0xe81b720-style flushes; 0x800 in readTexture; meaning of each state value not shown by the instructions [I].
- 0xe82d960 = the resource-state transition helper (6ae); 0xe8360f0 = upload-ring range registration [I].
- Slot names 26/28/30/31/32/33/34/51/52 come from the RendererContextD3D12 vtable map (6k); the code itself only shows the entry RVAs [I].

## CLOSES?

NO — every pending part is NOT proven: the sampler half (6ax) is [V] (e820500.md, SamplerFlags.h) and the D3D12 backend texture-management chain is [V] (Tables 1-8 above), but the Minecraft-side texture/atlas management — the ClientTexture/BedrockTexture/TexturePtr pack->GPU caller chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00, ending at undecoded callee 0x18718D0 at call 0x54227af) and the terrain/item atlas stitchers plus mip/compression builders — has no [V]-proven instruction row and is tracked by open items L8a/L8b (oc_U-EL8a.md, oc_U-EL8b.md), so the pending half of L7e cannot be closed by this unit.

## TOOL REQUESTS

- None (all instruction lines taken verbatim from rdis disassembly of the 1.26.62.01 exe; no helper scripts written, no temporary files left behind).

