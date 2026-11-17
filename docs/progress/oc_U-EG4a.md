## NEXT
DONE

# U-EG4a — G4a "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Scope of this unit = the part marked pending on the checklist line: the **texture/atlas management** half.
The **sampler flag decode + sampler cache** half is already closed on disk and was not redone:
docs/functions/e820500.md (0xe820500 instruction-complete: HashMurmur2A key, open hash map heap+0x60, u16 free ring
heap+8, CreateSampler vtable +0xB0, D3D12_SAMPLER_DESC with tables; CONTRADICTS 6ax on bit 28) and
src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h (static_asserts). BGFX_MAP 6ax keeps the early wording; the branch that
covers texture/atlas management per BGFX_MAP L8 is 6z/6z-2/6hz/6hx/BX (slot thread). This unit re-derived the
texture-management slot bodies from the exe (rdis 1.26.62.01) so the management chain is table-driven below.
All `0xRVA  instr` lines are verbatim from rdis disassembly of
C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (image-relative RVAs).

## Slots of the texture-management chain (base RendererContextD3D12)

| name | rva | size | proof | tag |
|---|---|---|---|---|
| slot 26 createTexture | 0xe8143c0..0xe8146a1 | 0x2e1 | `0xe8143c0  push rbp` | [V size/I name slot 26 per 6k] |
| slot 28 updateTexture | 0xe814a70..0xe8150e3 | 0x674 | `0xe814a70  push r15` | [V size/I name slot 28 per 6k] |
| slot 30 readTexture | 0xe8150f0..0xe815587 | 0x498 | `0xe8150f0  push r15` | [V size/I name] |
| slot 31 resizeTexture | 0xe815840..0xe815bee | 0x3ae | `0xe815840  push rbp` | [V size/I name] |
| slot 32 overrideInternal | 0xe815c30..0xe815d6c | 0x13c | `0xe815c30  push r14` | [V size/I name] |
| slot 33 getInternal | 0xe815d70..0xe815e9b | 0x12b | `0xe815d70  push rsi` | [V size/I name] |
| slot 34 destroyTexture | 0xe815ea0..0xe815fbf | 0x11f | `0xe815ea0  push rsi` | [V size/I name] |
| slot 51 blit | 0xe818bc0..0xe819746 | 0xb87 | `0xe818bc0  push r15` | [V size/I name] |
| slot 52 blitSetup | 0xe819750..0xe819b48 | 0x3f9 | `0xe819750  push r15` | [V size/I name] |

Names "[I slot N per 6k]" because the slot index comes from the BGFX_MAP vtable map, not the code.

## Table A — record lookup (shared by every texture slot)

| name | offset | size | proof (sites) | tag |
|---|---|---|---|---|
| texture record table base | this+0xBDE178 | 8 | `0xe814a8c  lea rbx,[rcx+0xBDE178]` (sites: 0xe814a8c upd, 0xe8143f3 create, 0xe815eaa destroy, 0xe815876 resize, 0xe815d81 getInternal) | [V] meaning: inline 4096-record table, stride 0xB8, ends 0xC5A178 [I 6z] |
| record stride | 0xB8 | 4 | `0xe814ac3  imul r9,r15,0xB8` (sites: 0xe814ac3, 0xe814c1b upd, 0xe815ede destroy, 0xe8158ad resize, 0xe815c7c override) | [V] byte size = the immediate is a dword imm |
| overflow-page guard flag | this+0xC96190 | 1 | `0xe814aab  cmp byte ptr [r14+0xC96190],0` (sites: 0xe814aab, 0xe814bfa upd, 0xe815ec7 destroy, 0xe815895 resize, 0xe814410 create) | [V] meaning: bit = guard enabled for handles >= 0x1000 [I 6z] |
| page-list anchor for detached handles (>=0x1000 pointer slot) | this+0xC96178 | 8 | `0xe814ae7  mov rax,[r14+0xC96178]` (sites: 0xe814ae7, 0xe814c36 upd, 0xe815f01 destroy, 0xe8158d1 resize, 0xe815ca0 override; +0xB8000 per page: 0xe814b37/0xe814c87) | [V] |
| address bounds check before lookup | call 0xE83ABB0 | - | `0xe814a9d  call 0xE83ABB0` (sites: 0xe814a9d, 0xe814bec upd2, 0xe815eba destroy, 0xe815887 resize, 0xe815c57 override, 0xe814403 create) | [V] |
| guard-violation report | 0xBC5F110, string 0xF7F68E3 | - | `0xe814ab5  lea rdx,[0xF7F68E3]` then `0xe814abe  call 0xBC5F110` (string shows meaning: "FAILED: accessing a guarded paged heap backed array out of b...") | [V] |

## Table B — createTexture (slot 26): the head of the management chain

| name | offset | size | proof (sites) | tag |
|---|---|---|---|---|
| args: (this, handle u16, Memory* r8, flags r9d) | regs | 4/2/8/4 | `0xe8143e3  mov [rbp+0x28],r9d` (flags), `0xe8143ef  mov [rbp+0x2E],dx` (handle), `0xe8143e7  mov r14,r8` (Memory) | [V] |
| image-container magic/chunk parse on the Memory block | 0xEBD2160 | - | `0xe81452c  call 0xEBD2160` (result test: `0xe814532  test al,al`) | [V] meaning [I: same parser as 6et command-14 TEX chunk] |
| create body call | 0xE81BF30 | - | `0xe81455b  call 0xE81BF30` | [V] role [I 6hz] |
| create args: (record r12=base+idx*0xB8, out [rbp+0x18], parsed chunk [rbp-0x40]; stack: Memory, flags, skip) | stack | 8/4/1 | `0xe814548  mov [rsp+0x20],r14` (Memory), `0xe814541  mov eax,[rbp+0x28]` + `0xe814544  mov [rsp+0x28],eax` (flags), `0xe814536  movzx eax,byte ptr [rbp+0xA0]` + `0xe81453d  mov [rsp+0x30],al` (skip byte) | [V] mapping [I] |
| created handle/id output copy into both halves of the notification entry | [rbp+0x20] | 4 | `0xe8145be  mov r14d,[rbp+0x20]`, `0xe814601  shl rcx,0x20`, `0xe814605  or rcx,r14` | [?] field meaning (out struct of 0xE81BF30) |
| create-notification table base | ctx+0x3C549F8 | 8 | `0xe8145cc  mov r12,[rdi+0x3C549F8]` | [V] meaning [I: per-handle pending list header] |
| per-handle notification get-or-create | ctx+0x14420 / +0x14428 | 8 | `0xe8145d3  lea r15,[r12+0x14420]`, `0xe8145db  add r12,0x14428`, `0xe8145e8  call 0xE83AED0` | [V] |
| entry store qword = {id,id<<32} | entry+0x00 | 8 | `0xe814612  mov [rax],rcx` | [V] |
| entry "seen" flag byte | entry+0x08 | 1 | `0xe81460e  mov byte ptr [rax+8],1` (pre-existing-entry path: `0xe81464d  call 0xE83B0E0`) | [V] meaning [?] |
| temp name string alloc/free (size idx*2+2) | - | - | `0xe81458e  lea rdx,[r15*2+2]`, `0xe8145b9  call 0xE935700` | [V] purpose [?] |
| post-create state write | cmdlist+0x14458 / +0x30 | 8 | `0xe814652  mov rcx,[rdi+0x19F58]`, `0xe814659  mov rdx,[rcx+0x30]`, `0xe814664  add rcx,0x14458` | [V] shape = same state-tracker call as update (Table C row 1) [I] |

## Table C — updateTexture (slot 28): upload/ring chain

| name | offset | size | proof (sites) | tag |
|---|---|---|---|---|
| per-handle resource-state tracker call | cmdlist+0x14458, state arg r9d | 4 | `0xe814be1  call 0xE82D960` with `0xe814bd8  mov r8d,r15d` (handle) + `0xe814bdb  mov r9d,0x400` (state 0x400) | [V] 0x400 meaning [I: "ready/current" tag also used by blitSetup row B8] |
| record current-state read | record+0x44 | 4 | `0xe814cfe  mov eax,[rbx+0x44]` (sites: 0xe814cfe, `0xe814ea9  cmp dword ptr [rbx+0x44],8`) | [V] meaning [I: per-handle state/flags word, cmp 8 = kind check in 6hz record] |
| resource pointer ownership test | record+0x00 | 8 | `0xe814bac  cmp qword ptr [rcx],0` (null already?) and `0xe814d34  mov rcx,[rbx]` (the ID3D12Resource*) | [V] |
| block byte for size math | record+0xB0 | 1 | `0xe814d10  movzx ecx,byte ptr [rbx+0xB0]` | [V] meaning [I: 6hz +0xB0 actual format] |
| numMips byte | record+0xB1 | 1 | `0xe814d05  movzx eax,byte ptr [rbx+0xB1]` | [V] meaning [I: 6hz +0xB1 mips] |
| copy size = word([chunk+4]) * formatBits >> 3 | - | 2 | `0xe814d1f  movzx eax,word ptr [r13+4]`, `0xe814d24  imul edi,eax`, `0xe814d27  shr edi,3` | [V] formula [I: bits-per-block * blocks >> 3] |
| device fetch for footprint query | ctx(deref)+0x400 | 8 | `0xe814d9d  mov rax,[0x12BB4910]`, `0xe814da4  mov rcx,[rax+0x400]`, `0xe814dab  mov rax,[rcx]`, `0xe814dae  mov rax,[rax+0x130]` | [V] meaning [I: device vtable +0x130 = GetCopyableFootprints] |
| device global holding the RendererContext | 0x12BB4910 | 8 | `0xe814d9d  mov rax,[0x12BB4910]` (sites: 0xe814d9d upd, 0xe80f2fc destroy-path, 0xe815618 readback-status) | [V] meaning [I: live census base pointer] |
| ring placement call with row layout | record+0x08 desc ptr, sizes | 4 | `0xe814e17  add r15,8`, `0xe814e0f  mov r8d,[rsp+0x88]` (layout), `0xe814e1b  lea rdx,[rsp+0x98]` (mapped range), `0xe814e23  mov r9d,0x200` (ring size code), `0xe814e2c  call 0xE8360F0` | [V] 0x200 meaning [I: upload-ring usage tag of 6bb's ring] |
| mapped-range descriptor shape | rax(ring)+0x10, +0x1C | 8/4 | `0xe814e38  mov rax,[rsp+0x98]`, `0xe814e48  mov rcx,[rax+0x10]` (used end), `0xe814e4f  cmp dword ptr [rax+0x1C],2` (kind) | [V] |
| destroyed shared_ptr temp release | [r14+8]/[r14+0xC] | 4 | `0xe814e64  lock dec dword ptr [r14+8]`, `0xe814e7a  lock dec dword ptr [r14+0xC]` | [V] |

## Table D — readTexture (slot 30): readback chain

| name | offset | size | proof (sites) | tag |
|---|---|---|---|---|
| state-tracker call state 0x800 ("readback") | r9d | 4 | `0xe815242  mov r8d,ebp` (handle), `0xe815245  mov r9d,0x800`, `0xe81524b  call 0xE82D960` | [V] 0x800 meaning [I] |
| staging-view parse reuse | 0x45EB90 | - | `0xe815260  call 0x45EB90` (record [r14] tested non-null first: `0xe815250  mov rcx,[r14]`) | [V] |
| readback label string | 0xF84849C | - | `0xe815314  lea r8,[0xF84849C]` — string shows it: "LReadTextureReadback" — with `0xe81530c  mov dword ptr [rsp+0x28],0x400` and `0xe81532c  call 0xE815590` | [V] purpose [I: staged read "view" issued to slot helper 0xE815590] |
| readback width from record | record+0x9C | 4 | `0xe81534e  mov rax,[r14+0x9C]` (and `0xe815453  mov r12d,[r14+0x9C]` with mip shift `0xe81545c  shr r12d,cl`) | [V] meaning [I: 6hz +0x9C width] |
| readback height from record | record+0xA0 | 4 | `0xe81545f  mov ebp,[r14+0xA0]` (shifted by mip: `0xe81546e  shr ebp,cl`) | [V] meaning [I: 6hz +0xA0 height] |
| format byte for row pitch | record+0xB0 | 1 | `0xe815476  movzx ecx,byte ptr [r14+0xB0]` then `0xe81547e  call 0xEBD1570` (bits/block) `0xe815487  imul r14d,r12d`, `0xe81548b  shr r14d,3` | [V] result [I: bytes-per-row of the mip] |
| staging Map via vtable | r15(staging)+vt+0x40 | 8 | `0xe8154b4  mov rax,[rax+0x40]` inside `0xe8154b1  mov rax,[r15]` then `0xe8154c7  call qword ptr [0xF99FFA0]` | [V] |
| per-row copy out | 0xEBCE390 | - | `0xe8154e6  call 0xEBCE390` (loop head `0xe8154ff  dec ebp`; next-row offset read `0xe8154eb  mov edx,[rsp+0x128]`; `0xe8154f7  mov [rsp+0x78],rdx`) | [V] target [I: caller buffer rdi += stride row] |
| renderer idle wait + fresh list for readback | this+0xCC9268 | 8 | `0xe815430  lea r12,[rsi+0xCC9268]`, `0xe81543f  call 0xE80ECB0` (wait: 6av), `0xe815447  call 0xE81AC80`, `0xe81544c  mov [rsi+0x19F58],rax` | [V] |
| staging view Release | r15+vt+0x10 | 8 | `0xe81553e  mov rax,[r15]`, `0xe815541  mov rax,[rax+0x10]`, `0xe815545  mov rcx,r15`, `0xe815548  call qword ptr [0xF99FFA0]` | [V] |

## Table E — resizeTexture (slot 31)

| name | offset | size | proof (sites) | tag |
|---|---|---|---|---|
| args: (this, handle dx -> [rbp+0x8E], w r8d, h r9d) | regs | 2/4/4 | `0xe81586f  mov [rbp+0x8E],dx`, `0xe815869  mov ebx,r8d`, `0xe815866  mov edi,r9d` | [V] |
| allocation of the new header block (0x2C bytes) | 0xE928660-global allocator | 4 | `0xe8159b4  mov r8d,0x2C`, `0xe8159bf  call qword ptr [0xF99FFA0]` | [V] |
| refcount block init | [r14+8] = 0x1C | 4 | `0xe8159cd  mov dword ptr [r14+8],0x1C` | [V] meaning [?] |
| new-record vtable trio | 0xF441980/0xF441990/0xF4419A0 | 8 | `0xe8159eb  lea rax,[0xF441980]`, `0xe8159f6  lea rax,[0xF441990]`, `0xe815a01  lea rax,[0xF4419A0]` | [V] identity [?] |
| 'TEX\0' magic of the block | [rbp+0x88] | 4 | `0xe815a17  mov dword ptr [rbp+0x88],0x584554` | [V] meaning [I: same chunk magic as 6et command-14 createTexture] |
| requested-format byte read of the old record | record+0xAF | 1 | `0xe815a65  movzx ecx,byte ptr [rsi+0xAF]` then `0xe815a83  mov [rbp+0x70],ecx` | [V] meaning [I: 6hz +0xAF requested format] |
| chunk stamp into block | 0xEBCE390 | - | `0xe815a3d  call 0xEBCE390` (r8d=4: `0xe815a34  mov r8d,4`) | [V] |
| destroy of the old resource before re-create | 0xE80F290 | - | `0xe815ac9  call 0xE80F290` | [V] |
| flags copy from record for the new create | record+0x98 | 4 | `0xe815ace  mov r12d,[rsi+0x98]` (used later `0xe815b0d  mov [rsp+0x28],r12d`) | [V] meaning [I: 6hz +0x98 flags] |
| re-create through the same body | 0xE81BF30 | - | `0xe815b2a  call 0xE81BF30` | [V] |
| temp block frees | 0xE935700 / Release | - | `0xe815b6d  call 0xE935700`, `0xe815b86  call qword ptr [0xF99FFA0]` (pre: `0xe815b72  mov rcx,[r14]`, `0xe815b75  cmp rcx,r15`) | [V] |

## Table F — overrideInternal / getInternal / destroyTexture (slots 32/33/34)

| name | offset | size | proof (sites) | tag |
|---|---|---|---|---|
| override: swap record pointer | record+0x00 | 8 | `0xe815d5f  mov [rdi],rsi` (rsi = caller's external object: `0xe815c39  mov rsi,r8`) | [V] meaning [I: bgfx overrideInternal] |
| override: flag the record "external" | record+0x9B | 1 | `0xe815d58  or byte ptr [rdi+0x9B],0x40` ; `0xe815d9c  jb short 0xE815DBE` (destroy path) | [V] bit meaning [I: bit 0x40 = overriden/external (0xE80F290 rows below)] |
| override/getInternal: global side-flag set | 0x12AE1750 | 1 | `0xe815c3f  mov byte ptr [0x12AE1750],1` (sites: 0xe815c3f override, 0xe815d7a getInternal) | [V] meaning [?] |
| getInternal: return [record] | record+0x00 | 8 | `0xe815e90  mov rax,[rsi]` | [V] |
| destroyTexture: release the record's resource object | record + 0xE80F290 | - | `0xe815fb0  mov rcx,rsi`, `0xe815fba  jmp 0xE80F290` | [V] |

## Table G — the resource destructor 0xE80F290 (destroy/shared tail)

| name | offset | size | proof (sites) | tag |
|---|---|---|---|---|
| staging holder release | this(record-ish)+0x90 | 8 | `0xe80f2be  cmp qword ptr [rsi+0x90],0`, then `0xe80f2d3  mov rax,[rax+0x48]`, `0xe80f2e4  mov qword ptr [rsi+0x90],0` | [V] meaning [I: wrapper holding the upload staging resource] |
| record "external" bit respected on destroy | [rsi+0x9B] bit 0x40 | 1 | `0xe80f2ef  test byte ptr [rsi+0x9B],0x40`, `0xe80f2f6  jne 0xE80F5BB` (exit) | [V] meaning [I: external objects must not be destroyed here] |
| destroyed resource queued on the command-list wrapper batcher vector | cmdlist+0x2CBE8/0x2CBF0/0x2CBE0 | 8 | `0xe80f34e  mov [rax],rdx` (rdx = [rsi] resource), `0xe80f351  add qword ptr [rbx+0x2CBE8],8` (count +8/elem; capacity growth: `0xe80f385  shr rbp,1`, `0xe80f388  add rbp,r15` = 1.5x) | [V] meaning [I: deferred release list on the frame command list (0x19F58 wrapper)] |
| allocator used for growth | 0x12ADF800 | 8 | `0xe80f3a0  mov rcx,[0x12ADF800]`, `0xe80f3d1  call qword ptr [0xF99FFA0]` | [V] |

## Table H — atlas blit (slot 51) + blitSetup (slot 52)

| name | offset | size | proof (sites) | tag |
|---|---|---|---|---|
| slot 51 reads the current command list + stats words | this+0x19F58/0x19F60/0x19F90/0x19F94 | 8/4/4 | `0xe818be9  mov rsi,[rcx+0x19F58]`, `0xe818bf0  mov rax,[rcx+0x19F60]`, `0xe818bf7  mov r14,[rax]`, `0xe818bfa  mov edi,[rcx+0x19F90]`, `0xe818c00  mov ebx,[rcx+0x19F94]` | [V; meanings [I: 6ax lists 0x19F90/94 as blit scratch (w/h in the blit desc built at 0xe818c35/0xe818c3e)] |
| blit desc stamp {0,0,w,h} + double constant | [rsp+0xF8..0x110] | 8 | `0xe818c29  mov qword ptr [rsp+0xF8],0`, `0xe818c47  movsd xmm0,[0xEFD32F0]`, `0xe818c4f  movsd [rsp+0x108],xmm0` | [V] constant meaning [?] (two 8-byte stores) |
| blit op code 0x8F to the batch builder | r8d | 4 | `0xe818d1e  mov r8d,0x8F`, `0xe818d2d  call 0xE81E860` | [V] 0x8F meaning [?] |
| lex table slot for the blit mapper | cmdlist+0x24/+0x20 | 8/2 | `0xe818cd2  lea rax,[rsi+0x24]`, `0xe818cd6  movzx ecx,word ptr [rsi+0x20]`, `0xe818cda  movzx edx,word ptr [r12+0x6C]` | [V] meaning [I: blit entry {handler, handle} pair, 6cx-style task headers] |
| vertex layout record pick for the flat blit | ctx+0xC96198 + idx*0x54 | 8 | `0xe818cb4  mov rax,[r12+8]`, `0xe818cb9  movzx eax,word ptr [rax+0x14]`, `0xe818cbd  imul rax,0x54`, `0xe818cc1  add rax,r15`, `0xe818cc4  add rax,0xC96198` | [V] meaning [I: 6hx vertex-layout table, idx from blit-desc word +0x14] |
| program record pick (0xF8 stride) + slot count | ctx+0xB62178 + idx*0xF8, word +0xAE | 2 | `0xe818dab  lea rbp,[r15+0xB62178]`, `0xe818e6d  movzx eax,word ptr [r12+0x6C]`, `0xe818e73  imul rcx,rax,0xF8`, `0xe818e7e  mov rcx,[rbp+rcx]`, `0xe818e8e  movzx r15d,word ptr [rcx+0xAE]` (fsh: `0xe818e9e  mov rax,[rax+8]`, `0xe818ea7  movzx ebx,word ptr [rax+0xAE]`) | [V] +0xAE meaning [?] (inside the 6au program record; not the uniform-entry area semantics) |
| blitSetup per-handle touched bitset (buffers) | cmdlist+0x48 + idx*8 | 8 | `0xe8197a0  mov rdx,[rbx+rax*8+0x48]`, `0xe8197ae  bt rdx,rcx`, `0xe819822  or rdx,r8`, `0xe819825  mov [rbx+rax*8+0x48],rdx` | [V] meaning [I: per-handle "touched" bitmap over the record id] |
| blitSetup per-handle state dword 0x400 | cmdlist+0x24C + idx*8 | 4 | `0xe8197b4  mov eax,[rbx+rcx*8+0x24C]`, `0xe8197bb  cmp eax,0x400`, `0xe8197ca  mov dword ptr [rbx+rcx*8+0x24C],0x400`, `0xe8197fb  mov dword ptr [rsp+0x58],0x400` | [V] 0x400 meaning [I: same ready-tag as updateTexture row C1] |
| blitSetup record fetch (0x78 stride) | [cmdlist+0x38] elem idx*0x78 | 8 | `0xe8197d5  mov r8,[rbx+0x38]`, `0xe8197d9  imul rcx,0x78`, `0xe8197dd  mov rcx,[r8+rcx]` | [V] meaning [I: the 0x78-stride buffer-record table of 6ba (0x93A178 family)] |
| barrier on that record | vtable +0xD0 (ResourceBarrier) | - | `0xe819806  mov rax,[rax+0xD0]` (vtbl load + slot from `0xe819803  mov rax,[rdx]` family), args `0xe81980d  lea r8,[rsp+0x40]`, `0xe81981a  call qword ptr [0xF99FFA0]` | [V] |
| blitSetup pending-handle append (u16, counter, double-const state 0x40000000400) | cmdlist+0x40 / +0x8248+idx*2 / +0x248+idx*8 | 2/2/8 | `0xe81982a  movzx eax,word ptr [rbx+0x40]`, `0xe81982e  mov [rbx+rax*2+0x8248],cx`, `0xe819838  mov [rbx+0x40],ax`, `0xe81983c  mov rax,0x40000000400`, `0xe819846  mov [rbx+rcx*8+0x248],rax` | [V] meaning [I: upload/barrier pending queue beside the 0x78 records] |
| second record family (vertex side) same shape, 0x80 stride | cmdlist+0xA248 / +0xA250 / +0xA258 / +0xA45C / +0x12458 | 8/2/8/4/2 | `0xe8198af  mov rax,[rax+0xA248]`, `0xe8198b9  mov rax,[rax+rcx]` (idx<<7: `0xe8198b6  shl ecx,7`), `0xe81990a  movzx edx,word ptr [rax+0xA250]`, `0xe819911  mov [rax+rdx*2+0x12458],cx`, `0xe819922  mov rdx,0x40000000400`, `0xe81992c  mov [rax+rcx*8+0xA458],rdx` | [V] identity [I: 0x80-stride dynamic vertex table (6ba base 0x9B2178)] |
| blitSetup type filter (r8d type; *4 < 6 rejected) | - | 4 | `0xe819763  mov r15d,r8d`, `0xe819766  lea eax,[r15*4]`, `0xe81976e  cmp eax,6`, `0xe819771  jb 0xE819B35` | [V] meaning [? (accepts type >= 2 only)] |

## Notes

- Row meanings tagged [I] are the record-layout cross-reads against BGFX_MAP 6z/6ba/6hx/6hz (field offsets shown by the
  instruction); meanings kept '-' where no instruction or string in the disassembly shows them (the +0xAE words, the
  0x8F op, the 0xF441980-family vtables, the blit desc double constant, the 0x12AE1750 flag).
- Sampler half (the first half of the checklist line) is proven closed by: docs/functions/e820500.md (0xe820500
  instruction-complete, HashMurmur2A key over <=16 flag dwords, hash map heap+0x60, free ring heap+8, CreateSampler
  device vtable +0xB0 into heap+0x10 + (u16[+0x24]*slot+i)*u32[+0x20], D3D12_SAMPLER_DESC tables read from the exe)
  and its CONTRADICTS-6ax correction (border colour from the r9 table indexed by bits 24..27, bit 28 selects
  MaxLOD 3.0 vs FLT_MAX). I did not re-derive those here.
- Atlas management above the backend (the Minecraft-side packers that feed TerrainAtlasBlit / atlas metadata
  0x4e198d0/0x4e1cbb0 of oc_U-Atl4) is not part of what was decoded this session; still open (see CLOSES?).

## CLOSES?

NO — the pending part "texture/atlas management" is only proven at the D3D12 record-table level (Tables A-H above,
all [V]); the Minecraft-side atlas management (atlas packers/streamers that produce the terrain/item atlases and
their texture uploads) is not decoded by any instruction-complete unit, so the checklist line cannot be ticked.

## TOOL REQUESTS
- None (all work done with rdis.exe + grep already covered by the toolbox).

## Appendix — verify_oc proof lines (verbatim rdis output; the `0xRVA  instr` lines quoted in the tables above, one per address, for tools/sigs/verify_oc.py)

```
0xe80f2be  cmp qword ptr [rsi+0x90],0                    ; R a0+0x90   ; from _eg4a_dtor.txt
0xe80f2d3  mov rax,[rax+0x48]                            ; R *(*(a0+0x0)+0x0)+0x48   ; from _eg4a_dtor.txt
0xe80f2e4  mov qword ptr [rsi+0x90],0                    ; W a0+0x90   ; from _eg4a_dtor.txt
0xe80f2ef  test byte ptr [rsi+0x9B],0x40                 ; R a0+0x9B   ; from _eg4a_dtor.txt
0xe80f2f6  jne 0xE80F5BB                                 ; -> loc_e80f5bb   ; from _eg4a_dtor.txt
0xe80f34e  mov [rax],rdx   ; from _eg4a_dtor.txt
0xe80f351  add qword ptr [rbx+0x2CBE8],8   ; from _eg4a_dtor.txt
0xe80f385  shr rbp,1   ; from _eg4a_dtor.txt
0xe80f388  add rbp,r15   ; from _eg4a_dtor.txt
0xe80f38f  mov rdi,r12   ; from _eg4a_dtor.txt
0xe80f3a0  mov rcx,[0x12ADF800]                          ; [data_12adf800]   ; from _eg4a_dtor.txt
0xe80f3d1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040   ; from _eg4a_dtor.txt
0xe8143c0  push rbp   ; from _eg4a_create.txt
0xe8143e3  mov [rbp+0x28],r9d   ; from _eg4a_create.txt
0xe8143e7  mov r14,r8   ; from _eg4a_create.txt
0xe8143ef  mov [rbp+0x2E],dx   ; from _eg4a_create.txt
0xe814403  call 0xE83ABB0                                ; -> sub_e83abb0   ; from _eg4a_create.txt
0xe814410  cmp byte ptr [rdi+0xC96190],0                 ; R a0+0xC96190   ; from _eg4a_create.txt
0xe81452c  call 0xEBD2160                                ; -> sub_ebd2160   ; from _eg4a_create.txt
0xe814532  test al,al   ; from _eg4a_create.txt
0xe814536  movzx eax,byte ptr [rbp+0xA0]   ; from _eg4a_create.txt
0xe81453d  mov [rsp+0x30],al   ; from _eg4a_create.txt
0xe814541  mov eax,[rbp+0x28]   ; from _eg4a_create.txt
0xe814544  mov [rsp+0x28],eax   ; from _eg4a_create.txt
0xe814548  mov [rsp+0x20],r14   ; from _eg4a_create.txt
0xe81455b  call 0xE81BF30                                ; -> sub_e81bf30   ; from _eg4a_create.txt
0xe81458e  cmp rdx,0x1000   ; from _eg4a_create.txt
0xe8145b9  call 0xE935700                                ; -> sub_e935700   ; from _eg4a_create.txt
0xe8145be  mov r14d,[rbp+0x20]   ; from _eg4a_create.txt
0xe8145cc  mov r12,[rdi+0x3C549F8]   ; from _eg4a_create.txt
0xe8145d3  lea r15,[r12+0x14420]   ; from _eg4a_create.txt
0xe8145db  add r12,0x14428   ; from _eg4a_create.txt
0xe8145e8  call 0xE83AED0                                ; -> sub_e83aed0   ; from _eg4a_create.txt
0xe814601  shl rcx,0x20   ; from _eg4a_create.txt
0xe814605  or rcx,r14   ; from _eg4a_create.txt
0xe81460e  mov byte ptr [rax+8],1                        ; W ret@e83aed0+0x8   ; from _eg4a_create.txt
0xe814612  mov [rax],rcx                                 ; W ret@e83aed0+0x0   ; from _eg4a_create.txt
0xe81464d  call 0xE83B0E0                                ; -> sub_e83b0e0   ; from _eg4a_create.txt
0xe814652  mov rcx,[rdi+0x19F58]   ; from _eg4a_create.txt
0xe814659  mov rdx,[rcx+0x30]   ; from _eg4a_create.txt
0xe814664  mov r8d,esi   ; from _eg4a_create.txt
0xe814a70  push r15   ; from _eg4a_update.txt
0xe814a8c  lea rbx,[rcx+0xBDE178]                        ; R a0+0xBDE178   ; from _eg4a_update.txt
0xe814a9d  call 0xE83ABB0                                ; -> sub_e83abb0   ; from _eg4a_update.txt
0xe814aab  cmp byte ptr [r14+0xC96190],0                 ; R a0+0xC96190   ; from _eg4a_update.txt
0xe814ab5  lea rdx,[0xF7F68E3]                           ; [data_f7f68e3] "FAILED: accessing a guarded paged heap backed array out of b..."   ; from _eg4a_update.txt
0xe814abe  call 0xBC5F110                                ; -> sub_bc5f110   ; from _eg4a_update.txt
0xe814ac3  imul r9,r15,0xB8   ; from _eg4a_update.txt
0xe814ae7  mov rax,[r14+0xC96178]   ; from _eg4a_update.txt
0xe814bac  cmp qword ptr [rcx],0   ; from _eg4a_update.txt
0xe814bd8  mov r8d,r15d   ; from _eg4a_update.txt
0xe814bdb  mov r9d,0x400   ; from _eg4a_update.txt
0xe814be1  call 0xE82D960                                ; -> sub_e82d960   ; from _eg4a_update.txt
0xe814cfe  mov eax,[rbx+0x44]   ; from _eg4a_update.txt
0xe814d05  movzx eax,byte ptr [rbx+0xB1]   ; from _eg4a_update.txt
0xe814d10  movzx ecx,byte ptr [rbx+0xB0]   ; from _eg4a_update.txt
0xe814d1f  movzx eax,word ptr [r13+4]   ; from _eg4a_update.txt
0xe814d24  imul edi,eax   ; from _eg4a_update.txt
0xe814d27  shr edi,3   ; from _eg4a_update.txt
0xe814d34  mov rcx,[rbx]   ; from _eg4a_update.txt
0xe814d9d  mov rax,[0x12BB4910]                          ; [data_12bb4910]   ; from _eg4a_update.txt
0xe814da4  mov rcx,[rax+0x400]   ; from _eg4a_update.txt
0xe814dab  mov rax,[rcx]   ; from _eg4a_update.txt
0xe814dae  mov rax,[rax+0x130]   ; from _eg4a_update.txt
0xe814e0f  mov r8d,[rsp+0x88]   ; from _eg4a_update.txt
0xe814e17  add r15,8   ; from _eg4a_update.txt
0xe814e1b  lea rdx,[rsp+0x98]   ; from _eg4a_update.txt
0xe814e23  mov r9d,0x200   ; from _eg4a_update.txt
0xe814e2c  call 0xE8360F0                                ; -> sub_e8360f0   ; from _eg4a_update.txt
0xe814e38  mov rax,[rsp+0x98]   ; from _eg4a_update.txt
0xe814e48  mov rcx,[rax+0x10]   ; from _eg4a_update.txt
0xe814e4f  cmp dword ptr [rax+0x1C],2   ; from _eg4a_update.txt
0xe814e64  lock dec dword ptr [r14+8]   ; from _eg4a_update.txt
0xe814e7a  lock dec dword ptr [r14+0xC]   ; from _eg4a_update.txt
0xe814ea9  cmp dword ptr [rbx+0x44],8   ; from _eg4a_update.txt
0xe8150f0  push r15   ; from _eg4a_update.txt
0xe815242  mov r8d,ebp   ; from _eg4a_update.txt
0xe815245  mov r9d,0x800   ; from _eg4a_update.txt
0xe81524b  call 0xE82D960                                ; -> sub_e82d960   ; from _eg4a_update.txt
0xe815250  mov rcx,[r14]   ; from _eg4a_update.txt
0xe815260  call 0x45EB90                                 ; -> sub_45eb90   ; from _eg4a_update.txt
0xe81530c  mov dword ptr [rsp+0x28],0x400   ; from _eg4a_update.txt
0xe815314  lea r8,[0xF84849C]                            ; [data_f84849c] "LReadTextureReadback"   ; from _eg4a_update.txt
0xe81532c  call 0xE815590                                ; -> sub_e815590   ; from _eg4a_update.txt
0xe81534e  mov rax,[r14+0x9C]   ; from _eg4a_update.txt
0xe815430  lea r12,[rsi+0xCC9268]   ; from _eg4a_update.txt
0xe81543f  call 0xE80ECB0                                ; -> sub_e80ecb0   ; from _eg4a_update.txt
0xe815447  call 0xE81AC80                                ; -> sub_e81ac80   ; from _eg4a_update.txt
0xe81544c  mov [rsi+0x19F58],rax   ; from _eg4a_update.txt
0xe815453  mov r12d,[r14+0x9C]   ; from _eg4a_update.txt
0xe81545c  shr r12d,cl   ; from _eg4a_update.txt
0xe81545f  mov ebp,[r14+0xA0]   ; from _eg4a_update.txt
0xe81546e  shr ebp,cl   ; from _eg4a_update.txt
0xe815476  movzx ecx,byte ptr [r14+0xB0]   ; from _eg4a_update.txt
0xe81547e  call 0xEBD1570                                ; -> sub_ebd1570   ; from _eg4a_update.txt
0xe815487  imul r14d,r12d   ; from _eg4a_update.txt
0xe81548b  shr r14d,3   ; from _eg4a_update.txt
0xe8154b1  mov rax,[r15]   ; from _eg4a_update.txt
0xe8154b4  mov rax,[rax+0x40]   ; from _eg4a_update.txt
0xe8154c7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040   ; from _eg4a_update.txt
0xe8154e6  call 0xEBCE390                                ; -> sub_ebce390   ; from _eg4a_update.txt
0xe8154eb  mov edx,[rsp+0x128]   ; from _eg4a_update.txt
0xe8154f7  mov [rsp+0x78],rdx   ; from _eg4a_update.txt
0xe8154ff  dec ebp   ; from _eg4a_update.txt
0xe81553e  mov rax,[r15]   ; from _eg4a_update.txt
0xe815541  mov rax,[rax+0x10]   ; from _eg4a_update.txt
0xe815545  mov rcx,r15   ; from _eg4a_update.txt
0xe815548  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040   ; from _eg4a_update.txt
0xe815840  push rbp   ; from _eg4a_update.txt
0xe815866  mov edi,r9d   ; from _eg4a_update.txt
0xe815869  mov ebx,r8d   ; from _eg4a_update.txt
0xe81586f  mov [rbp+0x8E],dx   ; from _eg4a_update.txt
0xe8159b4  mov r8d,0x2C   ; from _eg4a_tail.txt
0xe8159bf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040   ; from _eg4a_tail.txt
0xe8159cd  mov dword ptr [r14+8],0x1C   ; from _eg4a_tail.txt
0xe8159eb  lea rax,[0xF441980]                           ; [data_f441980]   ; from _eg4a_tail.txt
0xe8159f6  lea rax,[0xF441990]                           ; [data_f441990]   ; from _eg4a_tail.txt
0xe815a01  lea rax,[0xF4419A0]                           ; [data_f4419a0]   ; from _eg4a_tail.txt
0xe815a17  mov dword ptr [rbp+0x88],0x584554   ; from _eg4a_tail.txt
0xe815a34  mov r8d,4   ; from _eg4a_tail.txt
0xe815a3d  call 0xEBCE390                                ; -> sub_ebce390   ; from _eg4a_tail.txt
0xe815a65  movzx ecx,byte ptr [rsi+0xAF]   ; from _eg4a_resize2.txt
0xe815a83  mov [rbp+0x70],ecx   ; from _eg4a_resize2.txt
0xe815ac9  call 0xE80F290                                ; -> sub_e80f290   ; from _eg4a_resize2.txt
0xe815ace  mov r12d,[rsi+0x98]   ; from _eg4a_resize2.txt
0xe815b0d  mov [rsp+0x28],r12d   ; from _eg4a_resize2.txt
0xe815b2a  call 0xE81BF30                                ; -> sub_e81bf30   ; from _eg4a_resize2.txt
0xe815b6d  call 0xE935700                                ; -> sub_e935700   ; from _eg4a_resize2.txt
0xe815b72  mov rcx,[r14]   ; from _eg4a_resize2.txt
0xe815b75  cmp rcx,r15   ; from _eg4a_resize2.txt
0xe815b86  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040   ; from _eg4a_resize2.txt
0xe815c30  push r14   ; from _eg4a_tail.txt
0xe815c39  mov rsi,r8   ; from _eg4a_tail.txt
0xe815c3f  mov byte ptr [0x12AE1750],1                   ; [data_12ae1750]   ; from _eg4a_tail.txt
0xe815d58  or byte ptr [rdi+0x9B],0x40   ; from _eg4a_tail.txt
0xe815d5f  mov [rdi],rsi   ; from _eg4a_tail.txt
0xe815d70  push rsi   ; from _eg4a_tail.txt
0xe815d7a  mov byte ptr [0x12AE1750],1                   ; [data_12ae1750]   ; from _eg4a_tail.txt
0xe815d9c  jb short 0xE815DBE                            ; -> loc_e815dbe   ; from _eg4a_tail.txt
0xe815e90  mov rax,[rsi]   ; from _eg4a_ovr.txt
0xe815ea0  push rsi   ; from _eg4a_ovr.txt
0xe815fb0  mov rcx,rsi   ; from _eg4a_ovr.txt
0xe815fba  jmp 0xE80F290                                 ; -> sub_e80f290   ; from _eg4a_ovr.txt
0xe818bc0  push r15   ; from _eg4a_blit.txt
0xe818be9  mov rsi,[rcx+0x19F58]                         ; R a0+0x19F58   ; from _eg4a_blit.txt
0xe818bf0  mov rax,[rcx+0x19F60]                         ; R a0+0x19F60   ; from _eg4a_blit.txt
0xe818bf7  mov r14,[rax]                                 ; R *(a0+0x19F60)+0x0   ; from _eg4a_blit.txt
0xe818bfa  mov edi,[rcx+0x19F90]                         ; R a0+0x19F90   ; from _eg4a_blit.txt
0xe818c00  mov ebx,[rcx+0x19F94]                         ; R a0+0x19F94   ; from _eg4a_blit.txt
0xe818c29  mov qword ptr [rsp+0xF8],0   ; from _eg4a_blit.txt
0xe818c47  movsd xmm0,[0xEFD32F0]                        ; [data_efd32f0]   ; from _eg4a_blit.txt
0xe818c4f  movsd [rsp+0x108],xmm0   ; from _eg4a_blit.txt
0xe818cb4  mov rax,[r12+8]                               ; R a1+0x8   ; from _eg4a_blit.txt
0xe818cb9  movzx eax,word ptr [rax+0x14]                 ; R *(a1+0x8)+0x14   ; from _eg4a_blit.txt
0xe818cbd  imul rax,0x54   ; from _eg4a_blit.txt
0xe818cc1  add rax,r15   ; from _eg4a_blit.txt
0xe818cc4  add rax,0xC96198   ; from _eg4a_blit.txt
0xe818cd2  lea rax,[rsi+0x24]                            ; R *(a0+0x19F58)+0x24   ; from _eg4a_blit.txt
0xe818cd6  movzx ecx,word ptr [rsi+0x20]                 ; R *(a0+0x19F58)+0x20   ; from _eg4a_blit.txt
0xe818cda  movzx edx,word ptr [r12+0x6C]                 ; R a1+0x6C   ; from _eg4a_blit.txt
0xe818d1e  mov r8d,0x8F   ; from _eg4a_blit.txt
0xe818d2d  call 0xE81E860                                ; -> sub_e81e860   ; from _eg4a_blit.txt
0xe818dab  lea rbp,[r15+0xB62178]                        ; R a0+0xB62178   ; from _eg4a_blit.txt
0xe818e6d  movzx eax,word ptr [r12+0x6C]                 ; R a1+0x6C   ; from _eg4a_blit.txt
0xe818e73  imul rcx,rax,0xF8   ; from _eg4a_blit.txt
0xe818e7e  mov rcx,[rbp+rcx]                             ; R a0+0xB62178+0x0+idx   ; from _eg4a_blit.txt
0xe818e8e  movzx r15d,word ptr [rcx+0xAE]                ; R *(a0+0xB62178+0x0+idx)+0xAE   ; from _eg4a_blit.txt
0xe818e9e  mov rax,[rax+8]   ; from _eg4a_blit.txt
0xe818ea7  movzx ebx,word ptr [rax+0xAE]   ; from _eg4a_blit.txt
0xe819750  push r15   ; from _eg4a_blitsetup.txt
0xe819763  mov r15d,r8d   ; from _eg4a_blitsetup.txt
0xe819766  lea eax,[r15*4]   ; from _eg4a_blitsetup.txt
0xe81976e  cmp eax,6   ; from _eg4a_blitsetup.txt
0xe819771  jb 0xE819B35                                  ; -> loc_e819b35   ; from _eg4a_blitsetup.txt
0xe8197a0  mov rdx,[rbx+rax*8+0x48]                      ; R *(a0+0x19F58)+0x48+idx   ; from _eg4a_blitsetup.txt
0xe8197ae  bt rdx,rcx   ; from _eg4a_blitsetup.txt
0xe8197b4  mov eax,[rbx+rcx*8+0x24C]                     ; R *(a0+0x19F58)+0x24C+idx   ; from _eg4a_blitsetup.txt
0xe8197bb  cmp eax,0x400   ; from _eg4a_blitsetup.txt
0xe8197ca  mov dword ptr [rbx+rcx*8+0x24C],0x400         ; W *(a0+0x19F58)+0x24C+idx   ; from _eg4a_blitsetup.txt
0xe8197d5  mov r8,[rbx+0x38]                             ; R *(a0+0x19F58)+0x38   ; from _eg4a_blitsetup.txt
0xe8197d9  imul rcx,0x78   ; from _eg4a_blitsetup.txt
0xe8197dd  mov rcx,[r8+rcx]                              ; R *(*(a0+0x19F58)+0x38)+0x0+idx   ; from _eg4a_blitsetup.txt
0xe8197fb  mov dword ptr [rsp+0x58],0x400   ; from _eg4a_blitsetup.txt
0xe819803  mov rax,[rdx]                                 ; R *(*(a0+0x19F58)+0x30)+0x0   ; from _eg4a_blitsetup.txt
0xe819806  mov rax,[rax+0xD0]                            ; R *(*(*(a0+0x19F58)+0x30)+0x0)+0xD0   ; from _eg4a_blitsetup.txt
0xe81980d  lea r8,[rsp+0x40]   ; from _eg4a_blitsetup.txt
0xe81981a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040   ; from _eg4a_blitsetup.txt
0xe819822  or rdx,r8   ; from _eg4a_blitsetup.txt
0xe819825  mov [rbx+rax*8+0x48],rdx   ; from _eg4a_blitsetup.txt
0xe81982a  movzx eax,word ptr [rbx+0x40]   ; from _eg4a_blitsetup.txt
0xe81982e  mov [rbx+rax*2+0x8248],cx   ; from _eg4a_blitsetup.txt
0xe819838  mov [rbx+0x40],ax   ; from _eg4a_blitsetup.txt
0xe81983c  mov rax,0x40000000400   ; from _eg4a_blitsetup.txt
0xe819846  mov [rbx+rcx*8+0x248],rax   ; from _eg4a_blitsetup.txt
0xe8198af  mov rax,[rax+0xA248]   ; from _eg4a_blitsetup.txt
0xe8198b6  shl ecx,7   ; from _eg4a_blitsetup.txt
0xe8198b9  mov rax,[rax+rcx]   ; from _eg4a_blitsetup.txt
0xe81990a  movzx edx,word ptr [rax+0xA250]   ; from _eg4a_blitsetup.txt
0xe819911  mov [rax+rdx*2+0x12458],cx   ; from _eg4a_blitsetup.txt
0xe819922  mov rdx,0x40000000400   ; from _eg4a_blitsetup.txt
0xe81992c  mov [rax+rcx*8+0xA458],rdx   ; from _eg4a_blitsetup.txt
```
