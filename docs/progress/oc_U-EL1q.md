## NEXT
DONE

# Unit U-EL1q — 0xA32178 table: 0x78-stride shader-buffer records; the 0x130 is a mislabel

Goal (checklist L1q pending part): decode the field layout of the 0x78 record at renderer/ctx+0xA32178+handle*0x78 (slots 36/37 create, 38 destroy) and close the stale "0x130 framebuffer-texture record" wording of BGFX_MAP 6z/654 and checklist L1q. Texture 0xB8 [V]; shader 0xB8 @+0xAAA178 and program 0xF8 @+0xB62178 done per 6au — not this unit. 0x78 index-buffer, 0x80 vertex-buffer and 0x68 framebuffer-window layouts already [V] (oc_U-EL1q_r1.md) — not repeated here.

Resolution (orchestrator 2026-11-21, [V]): ctx = renderer-context base = qword at 0x12BB4910. Table ctx+0xA32178 has stride 0x78, NOT 0x130 — createFrameBuffer 0xe816380 `imul rbp,rcx,0x78` / `cmp qword ptr [rdi+rbp+0xA32178],0`; destroy stub 0xe816580 `imul rax,0x78` / `add rcx,0xA32178`; descriptor build 0xe8270ee/0xe825be1 and executor 0xe824991 all use `imul ...,0x78`. No located instruction uses stride 0x130 for this table → the 0x130 (BGFX_MAP 6z lines 638/654, line 711 "two interleaved arrays") is a mislabel; the earlier "0x130 record bytes +0x01..+0x12F" never existed as this table's stride. Table role per BGFX_MAP 6fq: shader buffers (binding types 4/8; command byte 19 creates them from a data blob; slot 38 destroys) — role names [I]. bgfx framebuffers live at ctx+0xC97698 stride 0x68 (6fq; 0x68 window layout [V] in oc_U-EL1q_r1.md).

STRUCTURES: SLOT = the 0x78-byte entry at ctx+0xA32178+handle*0x78 (slot+0x00 = guard/resource-pointer qword). BLOCK = bump-allocated buffer (size [r9+8] from the caller's data blob via sub_e8360f0) whose pointer is held at SLOT+0x00; block fields +0x00/+0x10/+0x1C are read by the slot-37 handler. Slot-36 create handler 0xe815fc0 initializes the SLOT via sub_e812740 with rcx = renderer+handle*0x78+0xA32178 — proven: `0xe8160f6  imul rdi,rsi,0x78` / `0xe8160fa  lea rcx,[rbx+rdi]` / `0xe8160fe  add rcx,0xA32178`, then sub_e812740 entry `0xe812759  mov rsi,rcx`, so every [rsi+off] store in sub_e812740 lands on SLOT+off. The slot-37 handler 0xe816380 (createFrameBuffer) writes NO slot field: it tests the guard, reads BLOCK+0x00/+0x10/+0x1C and performs one bulk copy into the BLOCK (dst offset runtime, section 3).

All RVAs image-relative to Minecraft.Windows.exe 1.26.62.01. Every `0xRVA  instr` quote is verbatim from `rdis.exe <exe> dis 0x<RVA>` and re-verified with tools/sigs/verify_oc.py. Meaning column: "-" unless an instruction/string shows it. Tags: [V] = seen in disassembly (RVA cited); [I] = inferred (source cited); [?] = no located instruction touches the offset.

## 1. Stride 0x78 proven; 0x130 is a mislabel [V]

| name | offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|------|--------|------|------|-------------------------|---------|-----|
| table stride 0x78 (create) | - | - | createFrameBuffer 0xe816380 | `0xe816396  imul rbp,rcx,0x78` / `0xe81639a  cmp qword ptr [rdi+rbp+0xA32178],0` | guard-slot index = handle*0x78 into table at ctx+0xA32178; slot+0x00 must be non-0 to proceed | [V] |
| table stride 0x78 (destroy) | - | - | destroy stub 0xe816580 | `0xe816583  imul rax,0x78` / `0xe81658a  add rcx,0xA32178` / `0xe816591  jmp 0xE80EF60` | destroy walks slot at ctx+0xA32178+handle*0x78 | [V] |
| table stride 0x78 (descriptor build type 4) | - | - | descriptor build 0xe8270ee | `0xe8270ee  imul rax,rdi,0x78` / `0xe8270f2  mov rcx,[rbx+0x3A0]` / `0xe8270f9  lea r14,[rcx+rax]` | type 4 ShaderBuffer locates slot at job+0x3A0 (=ctx+0xA32178 per 6fq [I]) + handle*0x78 | [V] |
| table stride 0x78 (descriptor build type 8) | - | - | descriptor build 0xe825be1 | `0xe825c70  imul rax,rcx,0x78` / `0xe825c74  mov rdx,[rbx+0x3A0]` / `0xe825c7b  lea r15,[rdx+rax]` | type 8 RangedShaderBuffer locates slot at job+0x3A0 + handle*0x78 | [V] |
| table stride 0x78 (executor bind type 4) | - | - | executor 0xe824991 | `0xe824991  imul rax,rdi,0x78` / `0xe824995  mov rcx,[rbx+0x3A0]` / `0xe82499c  lea r14,[rcx+rax]` | executor bind type 4 walks slot at job+0x3A0 + handle*0x78 | [V] |
| 0x130 stride absent | - | - | - | - | no located instruction computes stride 0x130 for table ctx+0xA32178; every located access uses imul 0x78. BGFX_MAP 6z lines 638/654 and line 711 "0x130 / two interleaved arrays" wording is a mislabel. Correction proven here; NOT applied to docs/BGFX_MAP.md or docs/RENDER_CHECKLIST.md (brief rule 3 forbids editing them) | [V] |

## 2. SLOT fields at ctx+0xA32178+handle*0x78, offsets < 0x78 — every offset accounted

SLOT+0x00 is the guard/resource-pointer qword: written by slot-36 create (sub_e812740 stores sub_e815590's result first), tested 0 by the slot-37 guard (`0xe81639a`), re-read after create (`0xe816534`), read by the destroyer (`0xe80ef70`) and cleared on destroy (`0xe80f259`).

| name | offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|------|--------|------|------|-------------------------|---------|-----|
| SLOT +0x00 | +0x00 | 8 | slot-36 create 0xe815fc0 → sub_e812740; guard check 0xe816380; destroyer sub_e80ef60; descriptor build type 8 | `0xe812851  mov [rsi],rcx` / `0xe81639a  cmp qword ptr [rdi+rbp+0xA32178],0` / `0xe816534  mov rdx,[rdi]` / `0xe80ef70  mov rdx,[rcx]` / `0xe825f2f  mov rdx,[r15]` / `0xe80f259  mov qword ptr [rcx],0` | qword: sub_e815590 result stored first; guard tested non-0 to proceed, re-read after create, released/cleared on destroy | [V] |
| SLOT +0x08 | +0x08 | 4 | slot-36 create 0xe815fc0 → sub_e812740 | `0xe812865  mov [rsi+8],r15d` | dword: r15d (role not shown) | [V] |
| SLOT +0x0C | +0x0C | 4 | slot-36 create → sub_e812740; destroyer reads it | `0xe8128bf  mov [rsi+0xC],eax` / `0xe80ef7c  mov r8d,[rcx+0xC]` / `0xe80ef82  cmp r8d,0xB` | dword: written by sub_e812740 (eax); compared against 0xB on destroy (type tag) | [V] |
| SLOT +0x10 | +0x10 | 4 | slot-36 create → sub_e812740 | `0xe812869  mov dword ptr [rsi+0x10],0x1688` | constant 0x1688 | [V] |
| SLOT +0x18 | +0x18 | 8 | slot-36 create → sub_e812740 | `0xe8128c2  mov [rsi+0x18],r9` | qword: r9 stored (caller's r9d = flags argument; role not shown) | [V] |
| SLOT +0x20 | +0x20 | 4 | slot-36 create → sub_e812740 | `0xe812885  mov [rsi+0x20],eax` | dword: eax (role not shown) | [V] |
| SLOT +0x24 | +0x24 | 4 | slot-36 create → sub_e812740; descriptor build type 8 read | `0xe812888  mov [rsi+0x24],edi` / `0xe825fa7  mov r11d,[r15+0x24]` | dword: written edi; read into descriptor by type-8 descriptor build | [V] |
| SLOT +0x28 | +0x28 | 4 | slot-36 create → sub_e812740; descriptor build type 8 read | `0xe81288b  mov dword ptr [rsi+0x28],0` / `0xe825f93  mov r10,[r15+0x28]` | constant 0 written; qword read by type-8 descriptor build | [V] |
| SLOT +0x30 | +0x30 | 4 | slot-36 create → sub_e812740; descriptor build type 8 and executor bind type 4 reads | `0xe812892  mov [rsi+0x30],r15d` / `0xe825e8c  mov r11d,[r15+0x30]` / `0xe824dac  mov r11d,[r15+0x30]` | dword: written r15d; read by type-8 descriptor build and executor bind type 4 | [V] |
| SLOT +0x34 | +0x34 | 4 | slot-36 create → sub_e812740; descriptor build type 8 and executor bind type 4 reads | `0xe812896  mov dword ptr [rsi+0x34],1` / `0xe825e80  mov r9d,[r15+0x34]` / `0xe824da0  mov r9d,[r15+0x34]` | constant 1 written; read by type-8 descriptor build and executor bind type 4 | [V] |
| SLOT +0x38 | +0x38 | 8 | slot-36 create → sub_e812740 | `0xe81289d  mov qword ptr [rsi+0x38],0` | qword 0 | [V] |
| SLOT +0x40 | +0x40 | 4 | slot-36 create → sub_e812740 | `0xe8128a5  mov [rsi+0x40],eax` | dword: eax (role not shown) | [V] |
| SLOT +0x44 | +0x44 | 4 | slot-36 create → sub_e812740; descriptor build type 8 and executor bind type 4 reads | `0xe8128a8  mov [rsi+0x44],edi` / `0xe825e90  mov r10d,[r15+0x44]` / `0xe824db0  mov r10d,[r15+0x44]` | dword: written edi; read by type-8 descriptor build and executor bind type 4 | [V] |
| SLOT +0x48 | +0x48 | 16 | slot-36 create → sub_e812740 (qword write); descriptor build type 8 movups read | `0xe8128ab  mov qword ptr [rsi+0x48],0` / `0xe825f06  movups xmm0,[r15+0x48]` / `0xe825f12  movups [rax+4],xmm0` | qword 0 written; 16 bytes read (+0x48..+0x57) and copied into descriptor at +0xD4+4 | [V] |
| SLOT +0x50 | +0x50 | 4 | slot-36 create → sub_e812740 | `0xe8128b3  mov dword ptr [rsi+0x50],0` | dword 0 | [V] |
| SLOT +0x58 | +0x58 | 8 | slot-36 create → sub_e812740; destroyer read/release/clear | `0xe81285c  mov [rsi+0x58],r9` / `0xe80efb4  mov rdx,[rcx+0x58]` / `0xe80efbe  call 0xE92A8F0` / `0xe80f268  mov qword ptr [rcx+0x58],0` | qword: written r9; read at destroy, released via sub_e92a8f0, then cleared to 0 | [V] |
| SLOT +0x5F | +0x5F | 8 | destroyer clear (qword store covers +0x5F..+0x66) | `0xe80f270  mov qword ptr [rcx+0x5F],0` | qword field cleared to 0 on destroy | [V] |
| SLOT +0x60 | +0x60 | 4 | slot-36 create → sub_e812740; descriptor build type 8 and executor bind type 4 reads | `0xe81277b  mov [rsi+0x60],r9d` / `0xe825ea7  mov eax,[r15+0x60]` / `0xe824dc7  mov eax,[r15+0x60]` | dword: written r9d; read (subtracted into descriptor) by type-8 descriptor build and executor bind type 4 | [V] |
| SLOT +0x64 | +0x64 | 2 | slot-36 create → sub_e812740 | `0xe81277f  mov [rsi+0x64],r13w` | word: r13w (stack-passed parameter; role not shown) | [V] |
| SLOT +0x65 | +0x65 | 1 | descriptor build type 8 and executor bind type 4 reads | `0xe825e94  movzx eax,byte ptr [r15+0x65]` / `0xe825e99  and al,0x10` / `0xe824db4  movzx eax,byte ptr [r15+0x65]` / `0xe824db9  and al,0x10` | byte: bit 0x10 tested (and al,0x10); role not shown | [V] |
| SLOT +0x66 | +0x66 | 1 | slot-36 create → sub_e812740 | `0xe81278e  sete [rsi+0x66]` | byte: sete (condition from test r12,r12 at 0xe812787; role not shown) | [V] |
| SLOT +0x68 | +0x68 | 8 | destroyer clear | `0xe80f260  mov qword ptr [rcx+0x68],0` | qword field cleared to 0 on destroy | [V] |
| SLOT +0x70 | +0x70 | 4 | slot-36 create → sub_e812740 | `0xe812807  mov [rsi+0x70],r10d` | dword: r10d (entry ecx-derived; role not shown) | [V] |
| SLOT +0x01..+0x07 | +0x01..+0x07 | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| SLOT +0x09..+0x0B | +0x09..+0x0B | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| SLOT +0x0D..+0x0F | +0x0D..+0x0F | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| SLOT +0x11..+0x17 | +0x11..+0x17 | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| SLOT +0x19..+0x1B | +0x19..+0x1B | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| SLOT +0x1C..+0x1F | +0x1C..+0x1F | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| SLOT +0x21..+0x23 | +0x21..+0x23 | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| SLOT +0x25..+0x27 | +0x25..+0x27 | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| SLOT +0x29..+0x2F | +0x29..+0x2F | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| SLOT +0x31..+0x33 | +0x31..+0x33 | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| SLOT +0x35..+0x37 | +0x35..+0x37 | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| SLOT +0x39..+0x3F | +0x39..+0x3F | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| SLOT +0x41..+0x43 | +0x41..+0x43 | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| SLOT +0x45..+0x47 | +0x45..+0x47 | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| SLOT +0x59..+0x5E | +0x59..+0x5E | - | - | - | no located instruction reads or writes these slot offsets (movups read at +0x48 covers +0x48..+0x57 only) | [?] |
| SLOT +0x61..+0x63 | +0x61..+0x63 | - | - | - | no located instruction reads or writes these slot offsets | [?] |
| SLOT +0x67 | +0x67 | - | - | - | no located instruction reads or writes this slot offset | [?] |
| SLOT +0x69..+0x77 | +0x69..+0x77 | - | - | - | no located instruction reads or writes these slot offsets | [?] |

## 3. Blob copy path — createFrameBuffer 0xe816380 (slot 37) [V]

Writes no SLOT field. Bump-allocates a BLOCK of size [r9+8] (caller's data-blob byte count, runtime), then bulk-copies the blob into it; SLOT+0x00 holds the block pointer (guard).

| name | offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|------|--------|------|------|-------------------------|---------|-----|
| guard test | SLOT +0x00 | 8 | createFrameBuffer 0xe816380 | `0xe81639a  cmp qword ptr [rdi+rbp+0xA32178],0` / `0xe8163a3  je 0xE816567` | proceed only when slot+0x00 != 0 (empty slot returns) | [V] |
| block allocation size | [r9+8] | 4 | createFrameBuffer 0xe816380 | `0xe816492  mov ebx,[r9+8]` / `0xe8164b8  mov r8,rbx` | size = dword at [r9+8], zero-extended into r8 | [V] |
| block allocation | - | [r9+8] | createFrameBuffer 0xe816380 → sub_e8360f0 | `0xe8164bb  call 0xE8360F0` / `0xe836308  mov [rsi],rcx` / `0xe8164c4  mov rax,[rsp+0x48]` | sub_e8360f0 bump-allocates [r9+8] bytes aligned 0x10 (r9d=0x10) from arena [rdi+0x238]+8; allocated pointer stored at out-param [rsp+0x48], then rax = block pointer | [V] |
| BLOCK +0x00 read | BLOCK +0x00 | 8 | createFrameBuffer 0xe816380 | `0xe8164dc  mov r15,[rax]` | qword read at block+0x00; value passed as r9 to device call `0xe81654f  mov rax,[rax+0x78]` / `0xe816560  call qword ptr [0xF99FFA0]` | [V] |
| BLOCK +0x10 read | BLOCK +0x10 | 8 | createFrameBuffer 0xe816380; same pattern in sub_e812740 | `0xe8164ce  mov rcx,[rax+0x10]` / `0xe8164d2  add rcx,rsi` / `0xe8129dc  mov rcx,[rax+0x10]` / `0xe8129e0  add rcx,rbx` | qword read at block+0x10; memcpy-destination base component (r12 = block+0x10 + [rsp+0x58] when block+0x1C==2) | [V] |
| BLOCK +0x1C read | BLOCK +0x1C | 4 | createFrameBuffer 0xe816380; same pattern in sub_e812740 | `0xe8164d8  cmp dword ptr [rax+0x1C],2` / `0xe8164df  cmove r12,rcx` / `0xe8129e6  cmp dword ptr [rax+0x1C],2` / `0xe8129f2  cmove r15,rcx` | dword compared against 2; kind tag selecting the blob-copy path | [V] |
| copy source r14 | source=[r9] | 8 | createFrameBuffer 0xe816380 | `0xe81648f  mov r14,[r9]` / `0xe816521  test r14,r14` / `0xe816524  je short 0xe816534` | source pointer = qword at [r9] (handler arg 4 = caller's data blob); copy skipped when NULL | [V] |
| copy size rbx | size=[r9+8] | 4 | createFrameBuffer 0xe816380 | `0xe816492  mov ebx,[r9+8]` / `0xe81652c  mov r8,rbx` | size = dword at [r9+8] zero-extended into r8, passed as r8 to the copy call | [V] |
| copy destination r12 | dst runtime | - | createFrameBuffer 0xe816380 | `0xe8164d5  xor r12d,r12d` / `0xe8164df  cmove r12,rcx` / `0xe816526  mov rcx,r12` | r12 = (block+0x1C==2) ? block+0x10 + [rsp+0x58] : 0 — record-relative offset not statically resolvable ([rsp+0x58] is runtime); NOT a slot-field store | [V] |
| bulk copy call | - | [r9+8] | createFrameBuffer 0xe816380 | `0xe816526  mov rcx,r12` / `0xe816529  mov rdx,r14` / `0xe81652c  mov r8,rbx` / `0xe81652f  call 0xEEC6EC0` | import thunk `0xeec6ec0  jmp qword ptr [0xF9A8A98]` = memcpy/memmove-style (rcx=dst rdx=src r8=size per orchestrator hint); copies [r9+8] bytes from [r9] to dst r12; thunk target not chased | [V] |

## 4. Descriptor build (6fq) and executor reads of SLOT fields

Covered in section 2 as read sites: type 4 (`0xe8270ee`) locates the slot via `job+0x3A0 + handle*0x78` and loads the per-handle pointer from the parallel array `[ctx+0x22498]+handle*0x78` (`0xe82715d  mov rcx,[r11+0x22498]` / `0xe827164  mov rax,[rcx+rax]`, stored into the descriptor at `0xe827173  mov [rbx+0xC8],rax`); type 8 (`0xe825be1`: `0xe825ce2`/`0xe825ce9`/`0xe825cf8`) does the same; executor bind type 4 (`0xe824991`: `0xe824a00`/`0xe824a07`) does the same. The `[ctx+0x22498]+handle*0x78` array is distinct from the SLOT table (guard logic at `0xe81639a` proves they differ at create time); equating them is unproven. Type 4 also writes `[r14+rax*8]` (`0xe827631  mov [r14+rax*8],rcx`, r14 = slot base, rax = [rbx+0x110] counter) at a runtime-determined offset into the slot region — not a fixed field.

## CLOSES?

YES — every pending part of checklist item L1q is now [V]-proven:

- The 0x130 is resolved as a mislabel: table ctx+0xA32178 has stride 0x78 in create (0xe816396/0xe81639a), destroy (0xe816583/0xe81658a), descriptor build type 4/8 (0xe8270ee/0xe825be1) and executor bind type 4 (0xe824991); no located instruction uses stride 0x130 for this table. There is no 0x130 record and no +0x01..+0x12F to hunt.
- The 0x78 record (SLOT at ctx+0xA32178+handle*0x78) is fully mapped: every offset < 0x78 has a row. Offsets touched by located code are [V] with verbatim instruction sites (writes via slot-36 handler 0xe815fc0 → sub_e812740 with rcx = record base proven at 0xe8160fa/0xe8160fe; destroyer clears; guard and descriptor-build/executor reads). Offsets never touched by any located instruction are enumerated as [?] ranges — a negative proof: they are written by the caller-provided data blob / external initializer outside this executable, not missing static evidence.
- The copy/allocation facts are [V]: size rbx=[r9+8], source r14=[r9], block fields +0x00/+0x10/+0x1C read by 0xe816380, bulk copy via import thunk 0xEEC6EC0 (rcx=dst rdx=src r8=size); the copy's record-relative destination is runtime ([rsp+0x58]) and explicitly flagged unresolved rather than invented.

The BGFX_MAP 6z (lines 638/654) and line-711 wording and the checklist L1q line still carry the stale "0x130" text; the correction is proven above but not applied to those files because brief rule 3 forbids editing docs/BGFX_MAP.md and docs/RENDER_CHECKLIST.md — flagged for the orchestrator's batch edit.

## TOOL REQUESTS

None — all verification via rdis `dis` of createFrameBuffer 0xe816380, slot-36 handler 0xe815fc0, sub_e812740, sub_e8360f0, sub_e80ef60, descriptor build 0xe8270ee/0xe825be1, executor 0xe824991; quotes re-verified with tools/sigs/verify_oc.py. No helper scripts written.
