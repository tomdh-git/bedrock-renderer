## NEXT
DONE

# UNIT U-EL2o — L2o upload tracking lists; pending part = copy path (slot 55) + slot 56

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred from instruction/string, [?] = unknown. Nothing invented.
Meaning column is '-' where no instruction or string shows a meaning.

Checklist line L2o (docs/RENDER_CHECKLIST.md line 252):
"Upload tracking lists (0x48/0x18 entries @+0x1A000/+0x1A018) + destroy path slot 57 (6ba); slot 55 init (6bb); copy path + slot 56 pending"
Already done (oc_U-B7c.md, ticked): entry layouts @ctx+0x1A000/+0x1A018, slot 55 init, slot 57 destroy/erase/retire.
This unit covers ONLY:
(A) copy path — slot 55 per-call upload path loc_e81684b..e816d22 of 0xe8165a0
(B) slot 56 in full — 0xe817070 (size 0x5e2)

Every verbatim line below is copied from the input listings (two spaces after the address). Sizes come from the instruction.
Input data read fully (not re-generated): docs/progress/oc_U-B7c_s55.txt, s56.txt, s57.txt (+stores, +descscan), docs/progress/pre/0xe8165a0.md.

## (A) Copy path — slot 55 per-call upload path (loc_e81684b..e816d22 inside 0xe8165a0)

Caller-spill arguments read from the caller's stack frame (no instruction shows their argument semantics):

| stack [rsp+0x1A0] | 2 B | R e81684b; R e816c07; R e816cb0 | handle lo (feeds side34+0x00 and side34+0x2C) | [V] |
 0xe81684b  movzx r10d,word ptr [rsp+0x1A0]
 0xe816c07  movzx eax,word ptr [rsp+0x1A0]
 0xe816cb0  movzx eax,word ptr [rsp+0x1A0]
| stack [rsp+0x4C] | 2 B | R e81683e; R e816b84 | handle hi | [V] |
 0xe81683e  movzx r8d,word ptr [rsp+0x4C]
 0xe816b84  movzx eax,word ptr [rsp+0x4E]
| stack [rsp+0x198] | 2 B | R e816854 | -> side34+0x1C | [V] |
 0xe816854  movzx r13d,word ptr [rsp+0x198]
| stack [rsp+0x188] | 4 B | R e81685d | -> side34+0x14 | [V] |
 0xe81685d  mov r15d,[rsp+0x188]
| stack [rsp+0x180] | 2 B | R e816865; R e816b95 | table select (cmp r11w,0xFFFF) and side34+0x06 | [V] |
 0xe816865  movzx r11d,word ptr [rsp+0x180]
 0xe816b95  movzx eax,word ptr [rsp+0x180]
| stack [rsp+0x170] | 4 B | R e81686e | byte count; shrink shr edx,2 / cmp 0x3FFF | [V] |
 0xe81686e  mov ebx,[rsp+0x170]
| stack [rsp+0x190] | 4 B | R e816925 | dst displacement added to record base ([rcx+0x58]) -> e48+0x70 block; /edi -> side34+0x18 | [V] |
 0xe816925  mov r9d,[rsp+0x190]
| stack [rsp+0x178] | 4 B | R e816936 | record displacement; [rax+0x9B21D0]+rcx -> e48+0x78 block; magic-div -> side34+0x0C/+0x10 | [V] |
 0xe816936  mov ecx,[rsp+0x178]
| stack [rsp+0x8C] | 4 B | W e81690f; R e816c15 | flags = (handle & 0x3D) | 2; bit2 gates list-A entry append | [V] |
 0xe81690f  mov [rsp+0x8C],edx
 0xe816c15  test byte ptr [rsp+0x8C],2
| stack [rsp+0x98] | 2 B | W e8168f4; R e816c49 | handle; lands at e48+0x38 (block copy) and list-A entry+0x04 | [V] |
 0xe8168f4  mov [rsp+0x98],r14w
 0xe816c49  movzx eax,word ptr [rsp+0x98]

Context fields read/written by the copy path:

| ctx +0x50 | 4 B | R e816b69 | -> side34+0x20 | [V] |
 0xe816b69  mov ecx,[rsi+0x50]
| ctx +0x238 | 8 B | R e816688 | device object (lazy-init path) | [V] |
 0xe816688  mov r8,[rsi+0x238]
| ctx +0x408 | 8 B | R e8169f6 | cmd-list wrapper object; vtable +0x1F8 called at e816a00 | [V] |
 0xe8169f6  mov rcx,[rsi+0x408]
| ctx +0x57A100 | 8 B | R e8165b9/e8165c0/e8166d0; W/R e8167a3/e8167a6/e816844 | lazy-init flag / upload-ring base pointer | [V] |
 0xe8165b9  lea r12,[rcx+0x57A100]
 0xe8165c0  cmp qword ptr [rcx+0x57A100],0
 0xe8166d0  mov rax,[rsi+0x57A100]
 0xe816844  lea r12,[rsi+0x57A100]
| ctx +0x57A178 (slot 55) | 8 B | R e816a53 | 0x78-record table base | [V] |
 0xe816a53  add rbx,0x57A178
| ctx +0x93A178 | 8 B | R e81688b | vertex/index 0x78-record table; chosen over side table via cmove when handle==0xFFFF | [V] |
 0xe81688b  lea rcx,[rsi+rdx+0x93A178]
| ctx +0x19F58 (slot 55) | 8 B | R e8165da | cmd-list wrapper object | [V] |
 0xe8165da  mov rbx,[rsi+0x19F58]
| ctx +0x1A000 | 8 B | R e816e52/e816e79/e816e8e; W e816eca | e48-list begin; realloc path stores new begin | [V] |
 0xe816e52  mov rdx,[rsi+0x1A000]
 0xe816e79  mov rdx,[rsi+0x1A000]
 0xe816e8e  mov rcx,[rsi+0x1A000]
 0xe816eca  mov [rsi+0x1A000],r14
| ctx +0x1A008 | 8 B | R e816cd4/e816e42; W e816d1a/e816ee0 | e48-list end; push += 0x48; realloc store | [V] |
 0xe816cd4  mov rdi,[rsi+0x1A008]
 0xe816d1a  add qword ptr [rsi+0x1A008],0x48
 0xe816ee0  mov [rsi+0x1A008],rax
| ctx +0x1A010 | 8 B | R e816cdb; W e816eef | e48-list cap | [V] |
 0xe816cdb  cmp rdi,[rsi+0x1A010]
 0xe816eef  mov [rsi+0x1A010],rax
| ctx +0x1A018 | 8 B | R e816cc0 | passed to grower sub_1195A0 when list-A full | [V] |
 0xe816cc0  lea rcx,[rsi+0x1A018]
| ctx +0x1A020 | 8 B | R e816c64; W e816c8d | list-A (0x18-entry ring) end; push += 0x18 | [V] |
 0xe816c64  mov rdx,[rsi+0x1A020]
 0xe816c8d  add qword ptr [rsi+0x1A020],0x18
| ctx +0x1A028 | 8 B | R e816c6b | list-A cap | [V] |
 0xe816c6b  cmp rdx,[rsi+0x1A028]

Per-handle side34 record at ctx+0x3DA100 + handle*0x34 (r12 = rsi + rdi*0x34 + 0x3DA100; rdi = handle lo):

| side34 +0x00 | 2 B | W e816b7f | handle lo | [V] |
 0xe816b7f  mov [r12],ax
| side34 +0x02 | 2 B | W e816b89 | handle hi | [V] |
 0xe816b89  mov [r12+2],ax
| side34 +0x04 | 2 B | W e816b8f | - | [V] |
 0xe816b8f  mov [r12+4],bp
| side34 +0x06 | 2 B | W e816b9d | - | [V] |
 0xe816b9d  mov [r12+6],ax
| side34 +0x08 | 4 B | W e816baa | byte count from [rsp+0x170] | [V] |
 0xe816baa  mov [r12+8],eax
| side34 +0x0C | 4 B | W e816bba | - | [V] |
 0xe816bba  mov [r12+0xC],eax
| side34 +0x10 | 4 B | W e816bd3 | - | [V] |
 0xe816bd3  mov [r12+0x10],eax
| side34 +0x14 | 4 B | W e816bd8 | - | [V] |
 0xe816bd8  mov [r12+0x14],r15d
| side34 +0x18 | 4 B | W e816be8 | - | [V] |
 0xe816be8  mov [r12+0x18],eax
| side34 +0x1C | 2 B | W e816bed | - | [V] |
 0xe816bed  mov [r12+0x1C],r13w
| side34 +0x20 | 4 B | W e816b6c | [rsi+0x50] | [V] |
 0xe816b6c  mov [r12+0x20],ecx
| side34 +0x24 | 4 B | W e816bfc | - | [V] |
 0xe816bfc  mov [r12+0x24],ecx
| side34 +0x28 | 4 B | W e816b71 | sentinel 0xFFFFFFFF (immediate) | [V] |
 0xe816b71  mov dword ptr [r12+0x28],0xFFFFFFFF
| side34 +0x2C | 2 B | W e816c0f | handle lo | [V] |
 0xe816c0f  mov [r12+0x2C],ax
| side34 +0x2E | 4 B | W e816bf3 | sentinel 0xFFFFFFFF (immediate) | [V] |
 0xe816bf3  mov dword ptr [r12+0x2E],0xFFFFFFFF
| side34 +0x32 | 1 B | W e816c01 | flag bit0 set | [V] |
 0xe816c01  or byte ptr [r12+0x32],1

Per-handle 0x78 record at ctx+0x57A178 + handle*0x78 (rbx = rsi + rdi*0x78 + 0x57A178; merged with slot 56 which rewrites the same fields):

| rec78 +0x00 | 8 B | W e816ac5; W e817581 | copied-buffer pointer (sub_e815590 result) | [V] |
 0xe816ac5  mov [rbx],rax
 0xe817581  mov [rsi],rax
| rec78 +0x08 | 8 B | W e816ae5; W e817599 | imm 0xB00000000 | [V] |
 0xe816ae5  mov [rbx+8],r8
 0xe817599  mov [rsi+8],r8
| rec78 +0x10 | 4 B | W e816ae9; W e81759d | imm 0x1688 | [V] |
 0xe816ae9  mov dword ptr [rbx+0x10],0x1688
 0xe81759d  mov dword ptr [rsi+0x10],0x1688
| rec78 +0x18 | 8 B | W e816af0; W e8175a4 | - | [V] |
 0xe816af0  mov [rbx+0x18],rdx
 0xe8175a4  mov [rsi+0x18],rdx
| rec78 +0x58 | 8 B | W e816ad0; W e817588 | [rbp-0x38] (sub_e815590 output dword) | [V] |
 0xe816ad0  mov [rbx+0x58],rdx
 0xe817588  mov [rsi+0x58],rdx
| rec78 +0x60 | 4 B | W e816a68; W e817523 | imm 0x2000000 | [V] |
 0xe816a68  mov [rbx+0x60],eax
 0xe817523  mov dword ptr [rsi+0x60],0x2000000
| rec78 +0x64 | 2 B | W e816a6b; W e81752a | imm 0x200 | [V] |
 0xe816a6b  mov word ptr [rbx+0x64],0x200
 0xe81752a  mov word ptr [rsi+0x64],0x200
| rec78 +0x66 | 1 B | W e816a71; W e817530 | imm 1 | [V] |
 0xe816a71  mov byte ptr [rbx+0x66],1
 0xe817530  mov byte ptr [rsi+0x66],1
| rec78 +0x70 | 4 B | W e816a75; W e817534 | imm 1 | [V] |
 0xe816a75  mov dword ptr [rbx+0x70],1
 0xe817534  mov dword ptr [rsi+0x70],1

e48 tracking entry appended at ctx+0x1A008 (end):

| e48 +0x00 | 16 B | W e816d16 | 16-byte block copy from stack desc [rsp+0x50..0x5F] | [V] |
 0xe816d16  movdqu [rdi],xmm0
| e48 +0x10 | 16 B | W e816d11 | 16-byte block copy from stack desc [rsp+0x60..0x6F] | [V] |
 0xe816d11  movdqu [rdi+0x10],xmm1
| e48 +0x20 | 16 B | W e816d0d | 16-byte block copy from stack desc [rsp+0x70..0x7F] | [V] |
 0xe816d0d  movups [rdi+0x20],xmm2
| e48 +0x30 | 16 B | W e816d09 | 16-byte block copy from stack desc [rsp+0x80..0x8F]; carries handle at +0x38 ([rsp+0x88]) and flags at +0x3C ([rsp+0x8C]) | [V] |
 0xe816d09  movups [rdi+0x30],xmm3
| e48 +0x40 | 8 B | W e816cec | [rsp+0x90] copy-descriptor dword | [V] |
 0xe816cec  mov [rdi+0x40],rax

Stack descriptor block built for the cmd-list wrapper vtable +0x1F8 call (e816a17):

| stack [rsp+0x50] | 8 B | W e816920 | imm 0x200000000 | [V] |
 0xe816920  mov [rsp+0x50],r9
| stack [rsp+0x58] | 8 B | W e81699e | 0 | [V] |
 0xe81699e  mov qword ptr [rsp+0x58],0
| stack [rsp+0x60] | 4 B | W e816991 | DXGI format (0x39 R16 / 0x2A R32 via cmove on r13w==2) | [I] |
 0xe816991  mov [rsp+0x60],ecx
| stack [rsp+0x64] | 4 B | W e81697b | bitfield table lookup at [r8+rax], table base 0xF4ECF40 | [V] |
 0xe81697b  mov [rsp+0x64],eax
| stack [rsp+0x68] | 4 B | W e816995 | [rsp+0x188] | [V] |
 0xe816995  mov [rsp+0x68],r15d
| stack [rsp+0x6C] | 4 B | W e81699a | byte count [rsp+0x170] | [V] |
 0xe81699a  mov [rsp+0x6C],ebx
| stack [rsp+0x70] | 8 B | W e816931 | [rsp+0x190] + [rcx+0x58] (dst displacement + record base) | [V] |
 0xe816931  mov [rsp+0x70],r9
| stack [rsp+0x78] | 8 B | W e816947 | [rax+0x9B21D0] + [rsp+0x178] | [V] |
 0xe816947  mov [rsp+0x78],rax
| stack [rsp+0x80] | 8 B | W e816967 | - | [V] |
 0xe816967  mov [rsp+0x80],rbp
| stack [rsp+0xDC] | 4 B | W e8169cb | (handle & 0x3D) | [V] |
 0xe8169cb  mov [rsp+0xDC],edx
| stack [rsp+0x90] | 4 B | W e816a3e | [rsp+0xC8] or rbx (cmove on test r14b,0x20) | [V] |
 0xe816a3e  mov [rsp+0x90],eax
| stack [rsp+0xC0] | 16 B | W e8169d6 | zeroed | [V] |
 0xe8169d6  movdqa [rsp+0xC0],xmm0
| stack [rsp+0xD0] | 8 B | W e8169df | 0 | [V] |
 0xe8169df  mov qword ptr [rsp+0xD0],0
| stack [rsp+0xD8] | 4 B | W e8169a7 | 1 | [V] |
 0xe8169a7  mov dword ptr [rsp+0xD8],1
| stack [rsp+0xE0] | 8 B | W e8169bf | 1 | [V] |
 0xe8169bf  mov qword ptr [rsp+0xE0],1

List-A 0x18-entry appended at ctx+0x1A020 (end) by the copy path:

| e18A +0x00 | 16 B | W e816c89 | 16-byte block from [rsp+0xA0..0xAF]: +0x00=0, +0x04=handle u16 ([rsp+0x98]), +0x08=[rsp+0xC0], +0x0C=0 | [V] |
 0xe816c89  movdqu [rdx],xmm0
| e18A +0x10 | 4 B | W e816c7c | [rsp+0xB0] = 0xFFFFFFFF | [V] |
 0xe816c7c  mov [rdx+0x10],rax

Copy-path calls (prose, not table rows): wrapper vtable +0x1F8 at e816a17 (copy-range submit); sub_e815590 at e816aaf (r8 = string "LBLAS" @0xF848B2A, r9d = 5; strings "LBLAS Quad Indices" @0xF847D90 and "LBLAS" @0xF848B2A are in this path); wrapper vtable +0xD0 at e816b63; grow sub_1195A0 at e816cc0; memmove sub_eec6de0 at e816e62/e816e89; free sub_e935700 at e816ec5; fail sub_75740 at e816f1d/e816f35.

## (B) Slot 56 in full (0xe817070, size 0x5e2)

Signature: (this = rcx = rbx, handle = edx = r12d, size = r8d = edi, userptr = r9 at [rbp+0x20]) [V e817097/e81709b/e81709e/e8170a1].

Stack slots:

| stack [rbp+0x38] | 8 B | W e81708f | sentinel -2 | [V] |
 0xe81708f  mov qword ptr [rbp+0x38],0xFFFFFFFFFFFFFFFE
| stack [rbp+0x20] | 8 B | W e817097 | userptr argument saved | [V] |
 0xe817097  mov [rbp+0x20],r9
| stack [rbp] | 2 B | W e8170b4 | handle saved | [V] |
 0xe8170b4  mov [rbp],dx
| stack [rbp+8] | 16 B | W e817158; W e81719c | copied-buffer pointer saved at [rbp+8]; r14 = &[rbp+8], so the movups zeroes [rbp+8..+0x17] (dead store) | [V] |
 0xe817158  mov [rbp+8],r13
 0xe81719c  movups [r14],xmm0
| stack [rbp+0x10] | 8 B | W e817167 | region end (buf + size*96) | [V] |
 0xe817167  mov [rbp+0x10],rsi
| stack [rbp+0x18] | 8 B | W e81716b; W e8171a0 | region end; then [rbp+0x18] zeroed (r14 = &[rbp+8]) | [V] |
 0xe81716b  mov [rbp+0x18],rsi
 0xe8171a0  mov qword ptr [r14+0x10],0
| stack [rbp+0x36] | 2 B | W e81721c | handle saved | [V] |
 0xe81721c  mov [rbp+0x36],r12w
| stack [rbp+0x28] | 8 B | W e817215 | new cap bytes | [V] |
 0xe817215  mov [rbp+0x28],rdx
| stack [rbp-0x10] | 8 B | W e8171f2 | new entry count | [V] |
 0xe8171f2  mov [rbp-0x10],r9
| stack [rsp+0x20] | 8 B | W e817554 | imm 0x2000000 | [V] |
 0xe817554  mov qword ptr [rsp+0x20],0x2000000
| stack [rsp+0x28] | 4 B | W e817548 | global dword [0x1285DC6C] | [V] |
 0xe817548  mov [rsp+0x28],eax
| stack [rsp+0x30] | 4 B | W e81754c | imm 4 | [V] |
 0xe81754c  mov dword ptr [rsp+0x30],4
| stack [rbp-0x30] | 8 B | W e8175d7 | 0 | [V] |
 0xe8175d7  mov qword ptr [rbp-0x30],0
| stack [rbp-0x28] | 8 B | W e8175df | sub_e815590 output buffer pointer | [V] |
 0xe8175df  mov [rbp-0x28],rax
| stack [rbp-0x20] | 4 B | W e8175e3 | imm 0xFFFFFFFF | [V] |
 0xe8175e3  mov dword ptr [rbp-0x20],0xFFFFFFFF
| stack [rbp-0x1C] | 4 B | W e8175ea | sub_e815590 output dword | [V] |
 0xe8175ea  mov [rbp-0x1C],ecx
| stack [rbp-0x18] | 4 B | W e8175ed | imm 0xAC3 | [V] |
 0xe8175ed  mov dword ptr [rbp-0x18],0xAC3

Globals:

| gbl [0x1233E1A8] | 8 B | R e8170e3/e81712d/e81723c/e817273 | global allocator object (vtable +8 alloc path) | [V] |
 0xe8170e3  mov rcx,[0x1233E1A8]
| gbl [0x12BB4910] | 8 B | R e81753b | renderer global object | [V] |
 0xe81753b  mov rcx,[0x12BB4910]
| gbl [0x1285DC6C] | 4 B | R e817542 | global dword -> stack [rsp+0x28] | [V] |
 0xe817542  mov eax,[0x1285DC6C]

Context fields (list-B = the slot-56 0x18 ring):

| ctx +0x19FE0 | 8 B | R e8172cb/e8173e1; W e8174b2 | list-B begin; reset to new base on compact | [V] |
 0xe8172cb  mov r13,[rbx+0x19FE0]
 0xe8173e1  mov r13,[rbx+0x19FE0]
 0xe8174b2  mov [rbx+0x19FE0],r12
| ctx +0x19FE8 | 8 B | R e817185/e8172d2/e8173f1; W e8174c4 | list-B end; push += 0x20 at e8171b4; reset on compact | [V] |
 0xe817185  mov r15,[rbx+0x19FE8]
 0xe8172d2  mov rax,[rbx+0x19FE8]
 0xe8173f1  mov rsi,[rbx+0x19FE8]
 0xe8174c4  mov [rbx+0x19FE8],rax
| ctx +0x19FF0 | 8 B | R e81718c/e81747f; W e8174d2 | list-B cap; full-check grows the ring | [V] |
 0xe81718c  cmp r15,[rbx+0x19FF0]
 0xe81747f  mov rdx,[rbx+0x19FF0]
 0xe8174d2  mov [rbx+0x19FF0],rax
| ctx +0x57A178 (slot 56) | 8 B | R e8174e6/e817518 | 0x78-record table base; updated only when record was NULL | [V] |
 0xe8174e6  cmp qword ptr [rbx+rax+0x57A178],0
 0xe817518  lea rsi,[rbx+rax]
 0xe81751c  add rsi,0x57A178
| ctx +0x19F58 (slot 56) | 8 B | R e8175af | cmd-list wrapper object (rdx = renderer [0x12BB4910]); vtable +0xD0 called at e81760b | [V] |
 0xe8175af  mov rdx,[rdx+0x19F58]

Slot-56 0x18-entry (list-B ring, stride 0x20; fields +0x00/+0x08/+0x10/+0x18):

| e18B +0x00 | 2 B | R e8172f0/e8173a0/e817350; W e817195/e8172a5/e8172f6/e8173a6/e817355 | handle (u16); written on push, copied in both compaction loops | [V] |
 0xe817195  mov [r15],r12w
 0xe8172a5  mov [r12+r14],ax
 0xe8172f0  movzx ecx,word ptr [r13+rax]
 0xe8172f6  mov [r12+rax],cx
 0xe8173a0  movzx ecx,word ptr [r13+rax]
 0xe8173a6  mov [r12+rax],cx
 0xe817350  movzx r8d,word ptr [r15+rdx]
 0xe817355  mov [rcx+rdx-0x18],r8w
| e18B +0x08 | 16 B | W e8171a8/e8172bc/e817309/e81730f/e817315/e817369/e81736f/e817375/e8173c5/e817420 | alloc ptr qword at push; +0x08..+0x17 moved as a 16-byte block together with +0x10 in compaction; old entries zeroed on free/compact | [V] |
 0xe8171a8  mov [r15+8],r13
 0xe8172bc  mov [r12+r14+8],r13
 0xe817309  movups xmm1,[r13+rax+8]
 0xe81730f  movups [r13+rax+8],xmm0
 0xe817315  movups [r12+rax+8],xmm1
 0xe817369  movups xmm1,[r15+rdx+8]
 0xe81736f  movups [r15+rdx+8],xmm0
 0xe817375  movups [rcx+rdx-0x10],xmm1
 0xe8173c5  movups [r12+rax+8],xmm1
 0xe817420  movups [r14],xmm6
| e18B +0x10 | 8 B | W e8171ac/e8172c1 | region-end qword (= buf + size*96); also inside the +0x08 16-byte block moves | [V] |
 0xe8171ac  mov [r15+0x10],rsi
 0xe8172c1  mov [r12+r14+0x10],rsi
| e18B +0x18 | 8 B | W e8171b0/e8172c6/e81731b/e8173cb/e81737a; zeroed W e817300/e8173b0/e817360/e817424 | size dup / fence; zeroed when old entry freed or compacted | [V] |
 0xe8171b0  mov [r15+0x18],rsi
 0xe8172c6  mov [r12+r14+0x18],rsi
 0xe81731b  mov [r12+rax+0x18],rcx
 0xe8173cb  mov [r12+rax+0x18],rcx
 0xe81737a  mov [rcx+rdx],r8
 0xe817300  mov qword ptr [r13+rax+0x18],0
 0xe8173b0  mov qword ptr [r13+rax+0x18],0
 0xe817360  mov qword ptr [r15+rdx+0x18],0
 0xe817424  mov qword ptr [r14+0x10],0

rec78 +0x00/+0x08/+0x10/+0x18/+0x58/+0x60/+0x64/+0x66/+0x70 are also written by slot 56 (merged rows in section A above). The slot-56 write is gated on [rec78]==0 (e8174e6 test, je e817518).

Slot-56 calls (prose, not table rows): allocator [0xF99FFA0] x4 (e8170f4/e817138/e81724e/e817285); 0xEEC6ED0 at e817153 (memset-like, rdx = 0); 0xEEC6EC0 at e817180 (rcx = buf, rdx = userptr, r8 = size); 0x9BC830 free x4; sub_e815590 at e81756e (r8 = 0xF848B20, r9d = 5; out ptr [rbp-0x48]); wrapper vtable +0xD0 at e81760b (skipped when [rbp-0x40] == 0xAC3 or 0x400000); free sub_e935700 x3 (e81741b/e8174ad plus the [0xF9A8C78] callback at e817472); fail sub_75740 at e817645/e81764b.

CLOSES?
YES — every pending part of L2o is now proven by [V] rows: (A) copy path — caller-spill stack reads, ctx fields (+0x50/+0x238/+0x408/+0x57A100/+0x57A178/+0x93A178/+0x19F58/+0x1A000/+0x1A008/+0x1A010/+0x1A018/+0x1A020/+0x1A028), side34 record (+0x00..+0x32), rec78 record (+0x00/+0x08/+0x10/+0x18/+0x58/+0x60/+0x64/+0x66/+0x70), e48 entry (+0x00..+0x40), stack descriptor block ([rsp+0x50..0xE0]), list-A 0x18 append (+0x00/+0x10); (B) slot 56 — stack slots, globals, ctx list-B (+0x19FE0/+0x19FE8/+0x19FF0/+0x57A178/+0x19F58), e18B entry (+0x00/+0x08/+0x10/+0x18), rec78 rewrites, ring-pointer reset. No blocking fact. Field meanings not shown by any instruction are tagged '-', per the brief rules; this is not a blocker.

## TOOL REQUESTS
None