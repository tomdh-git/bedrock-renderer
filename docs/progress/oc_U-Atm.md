## NEXT
DONE — instruction-complete: 4 phases covering all 139 instructions of 0x6656d4b..0x665708f, 87-row [reg+off] field table, `delegate.py check` exit 0.
# U-Atm — sky_atmosphere fragment 0x6656D4B..0x6657090 (instruction-complete dossier)

Input data: docs/data/listings/sky_atmosphere_6656d4b_6657090.txt (139 instructions, 0x6656d4b..0x665708f).
Status: fragments of a larger function (no prologue/epilogue in range; branch targets 0x6657237 / 0x66573C3 / 0x66573C5 lie outside the listing).

Context [I]: rsi is a frame context and rdi a sky description object — the same shape is documented in docs/BGFX_MAP.md:2032 ("all sky cases push into the pass object `0x5ABA5C0(0x9D0 + [frameCtx+0x10])`"); here rsi is only read at +0x10/+0x548/+0x550. Call targets: 0x5ABA5C0 = RenderMark::passLookup [I BGFX_MAP.md:828]; [0xF99FFA0] = CFG thunk cell [I BGFX_MAP.md:176]; 0xEEC6EC0 = copy/append helper (appears as the copy half of append/grow pairs in BGFX_MAP.md:2041) [I]. Function name "sky atmosphere" comes from the input filename [I].

## Phases (139 instructions, each listed verbatim; indentation added)

### Phase 1: 0x6656d4b..0x6656e53 — snapshot of desc fields into rbp locals (Part 1)
rax is zeroed; the qword `[rdi+0xD8]` is saved with it at 0x210/0x218 (a pointer + zeroed partner, refcount-incremented later when non-null); floats/doubles 0xE8/0xEC/0x100/0x104 and the blocks at 0x10C (16B), 0x11C (8B), 0x124 (4B), 0x128 (16B) are copied into locals 0x220..0x250; dword +4, qword +8 and floats +C/+10 are copied, and local 0x26C receives max(const float at [0xEEC8060], [rdi+0x10]-[rdi+0xC]) [V]; the 16-byte blocks desc+0x14/0x24/0x34/0x44 land at locals 0x270/0x280/0x290/0x2A0.

    0x6656d4b  xor eax,eax
    0x6656d4d  mov rcx,[rdi+0xD8]
    0x6656d54  mov [rbp+0x210],rcx
    0x6656d5b  mov [rbp+0x218],rax
    0x6656d62  movsd xmm6,[rdi+0xE8]
    0x6656d6a  movss xmm12,[rdi+0xEC]
    0x6656d73  movss [rbp+0x220],xmm6
    0x6656d7b  movss [rbp+0x224],xmm12
    0x6656d84  movsd xmm9,[rdi+0x100]
    0x6656d8d  movss [rbp+0x228],xmm9
    0x6656d96  movsd xmm7,[rdi+0x104]
    0x6656d9e  movsd [rbp+0x22C],xmm7
    0x6656da6  lea rcx,[rbp+0x234]
    0x6656dad  movups xmm1,[rdi+0x10C]
    0x6656db4  movups [rbp+0x234],xmm1
    0x6656dbb  movsd xmm8,[rdi+0x11C]
    0x6656dc4  movsd [rbp+0x244],xmm8
    0x6656dcd  movss xmm10,[rdi+0x124]
    0x6656dd6  movss [rbp+0x24C],xmm10
    0x6656ddf  lea rdx,[rbp+0x250]
    0x6656de6  movups xmm1,[rdi+0x128]
    0x6656ded  movaps [rbp+0x250],xmm1
    0x6656df4  mov r8d,[rdi+4]
    0x6656df8  mov [rbp+0x260],r8d
    0x6656dff  movss xmm1,[rdi+0xC]
    0x6656e04  movsd xmm2,[rdi+8]
    0x6656e09  movsd [rbp+0x264],xmm2
    0x6656e11  movss xmm2,[rdi+0x10]
    0x6656e16  subss xmm2,xmm1
    0x6656e1a  movss xmm1,[0xEEC8060]
    0x6656e22  maxss xmm1,xmm2
    0x6656e26  movss [rbp+0x26C],xmm1
    0x6656e2e  movups xmm1,[rdi+0x14]
    0x6656e32  movaps [rbp+0x270],xmm1
    0x6656e39  movups xmm1,[rdi+0x24]
    0x6656e3d  movaps [rbp+0x280],xmm1
    0x6656e44  movups xmm1,[rdi+0x34]
    0x6656e48  movaps [rbp+0x290],xmm1
    0x6656e4f  movups xmm1,[rdi+0x44]
    0x6656e53  movaps [rbp+0x2A0],xmm1

### Phase 2: 0x6656e5a..0x6656f5f — snapshot Part 2, then the 0x378 record header is built
The block-copy from desc continues: 16-byte blocks desc+0x54/0x64/0x74/0x84 land at locals 0x2B0..0x2E0, qword +0x94 and float +0x9C at 0x2F0/0x2F8, byte +0xA0 at 0x2FC, qwords +0xF0/+0xF8 at 0x300/0x308; the r9w argument value is parked at 0x340 (and again at 0x1C8 below); three 16-byte locals 0x1E0/0x1F0/0x200 (prepared before the fragment) are moved into the new record at 0x348/0x358/0x368 and xmm0 zero is stored at 0x378; rax is still 0 from 0x6656d4b, so `test rax,rax` falls through the branch to `xor r14d,r14d` (the skipped path would atomically increment the dword at [rax+8] and load r14 from 0x218); finally rdi/r14 are reloaded from 0x210/0x218 into the record header at 0x378/0x380 and the floats xmm6/xmm12/xmm9/xmm7 are stored at 0x388/0x38C/0x390/0x394.

    0x6656e5a  movups xmm1,[rdi+0x54]
    0x6656e5e  movaps [rbp+0x2B0],xmm1
    0x6656e65  movups xmm1,[rdi+0x64]
    0x6656e69  movaps [rbp+0x2C0],xmm1
    0x6656e70  movups xmm1,[rdi+0x74]
    0x6656e74  movaps [rbp+0x2D0],xmm1
    0x6656e7b  movups xmm1,[rdi+0x84]
    0x6656e82  movaps [rbp+0x2E0],xmm1
    0x6656e89  movsd xmm1,[rdi+0x94]
    0x6656e91  movsd [rbp+0x2F0],xmm1
    0x6656e99  movss xmm1,[rdi+0x9C]
    0x6656ea1  movss [rbp+0x2F8],xmm1
    0x6656ea9  movzx r8d,byte ptr [rdi+0xA0]
    0x6656eb1  mov [rbp+0x2FC],r8b
    0x6656eb8  movsd xmm11,[rdi+0xF0]
    0x6656ec1  movsd [rbp+0x300],xmm11
    0x6656eca  movsd xmm1,[rdi+0xF8]
    0x6656ed2  movsd [rbp+0x308],xmm1
    0x6656eda  mov [rbp+0x340],r9w
    0x6656ee2  movaps xmm1,[rbp+0x1E0]
    0x6656ee9  movaps xmm2,[rbp+0x1F0]
    0x6656ef0  movaps xmm3,[rbp+0x200]
    0x6656ef7  movups [rbp+0x348],xmm1
    0x6656efe  movups [rbp+0x358],xmm2
    0x6656f05  movups [rbp+0x368],xmm3
    0x6656f0c  movups [rbp+0x378],xmm0
    0x6656f13  test rax,rax
    0x6656f16  mov [rbp+0x1C8],r9w
    0x6656f1e  je short 0x6656F2D
    0x6656f20  lock inc dword ptr [rax+8]
    0x6656f24  mov r14,[rbp+0x218]
    0x6656f2b  jmp short 0x6656F30
    0x6656f2d  xor r14d,r14d
    0x6656f30  mov rdi,[rbp+0x210]
    0x6656f37  mov [rbp+0x378],rdi
    0x6656f3e  mov [rbp+0x380],r14
    0x6656f45  movss [rbp+0x388],xmm6
    0x6656f4d  movss [rbp+0x38C],xmm12
    0x6656f56  movss [rbp+0x390],xmm9
    0x6656f5f  movlps [rbp+0x394],xmm7
### Phase 3: 0x6656f66..0x6657036 — record body copy, pass lookup, zeroed local buffer, CFG-thunk call
The 16 bytes at [rcx] (rcx = rbp+0x234 from the lea in phase 1) are stored at 0x39C and xmm8/xmm10 complete the header at 0x3AC/0x3B4; r13 = rbp+0x3B8 and `call 0xEEC6EC0` runs with rcx=r13, rdx=rbp+0x250 (set at 0x6656ddf and untouched since) and r8d=0xAD, copying/constructing the 0xAD-byte image rbp+0x250..0x2FC into rbp+0x3B8 [V shape, I helper]; the qwords from xmm11 (desc+0xF0) and [rbp+0x308] (desc+0xF8 image) are appended at 0x468/0x470; `ecx=0x9D0; add rcx,[rsi+0x10]; call 0x5ABA5C0` is the documented `passLookup(0x9D0 + [frameCtx+0x10])` [I BGFX_MAP.md:2032] and the returned pass object becomes the new rsi; twelve 16-byte zero stores clear the local buffer rbp+0x58..0x117; rcx = global [0x1233E1B0], its vtable slot [rax+0x10] is fetched and `call qword ptr [0xF99FFA0]` (the CFG thunk [I BGFX_MAP.md:176]) runs with dl=0x4A, result eax saved to ebx [? purpose]; rax is pointed at the record (lea rax,[rbp+0x348]) and r15 = [rsi+0x548] is compared against [rsi+0x550].

    0x6656f66  movups xmm0,[rcx]
    0x6656f69  movups [rbp+0x39C],xmm0
    0x6656f70  movlps [rbp+0x3AC],xmm8
    0x6656f78  movss [rbp+0x3B4],xmm10
    0x6656f81  lea r13,[rbp+0x3B8]
    0x6656f88  mov r8d,0xAD
    0x6656f8e  mov rcx,r13
    0x6656f91  call 0xEEC6EC0
    0x6656f96  movlps [rbp+0x468],xmm11
    0x6656f9e  mov rax,[rbp+0x308]
    0x6656fa5  mov r12,rax
    0x6656fa8  mov [rbp+0x470],rax
    0x6656faf  mov ecx,0x9D0
    0x6656fb4  add rcx,[rsi+0x10]
    0x6656fb8  call 0x5ABA5C0
    0x6656fbd  nop
    0x6656fbe  mov rsi,rax
    0x6656fc1  xorps xmm0,xmm0
    0x6656fc4  movups [rbp+0x108],xmm0
    0x6656fcb  movups [rbp+0xF8],xmm0
    0x6656fd2  movups [rbp+0xE8],xmm0
    0x6656fd9  movups [rbp+0xD8],xmm0
    0x6656fe0  movups [rbp+0xC8],xmm0
    0x6656fe7  movups [rbp+0xB8],xmm0
    0x6656fee  movups [rbp+0xA8],xmm0
    0x6656ff5  movups [rbp+0x98],xmm0
    0x6656ffc  movups [rbp+0x88],xmm0
    0x6657003  movups [rbp+0x78],xmm0
    0x6657007  movups [rbp+0x68],xmm0
    0x665700b  movups [rbp+0x58],xmm0
    0x665700f  mov rcx,[0x1233E1B0]
    0x6657016  mov rax,[rcx]
    0x6657019  mov rax,[rax+0x10]
    0x665701d  mov dl,0x4A
    0x665701f  call qword ptr [0xF99FFA0]
    0x6657025  nop
    0x6657026  mov ebx,eax
    0x6657028  lea rax,[rbp+0x348]
    0x665702f  mov r15,[rsi+0x548]
    0x6657036  cmp r15,[rsi+0x550]

### Phase 4: 0x665703d..0x665708f — push the 0x40-byte record into the pass list; fragment tail
If r15 equals [rsi+0x550] the push is skipped and control leaves to 0x6657237 (end/capacity compare [I]; grow path beyond the fragment); otherwise the 0x40-byte record at rax (=rbp+0x348) is copied into the slot at r15 with three 16-byte movups (+0x20/+0x10/+0x00) and [r15+0x30] is zeroed (a 0x40-byte slot); on the r14!=0 path the dword [r14+8] is atomically incremented (shared-ptr refcount [I BGFX_MAP.md:2032]) else control jumps to 0x66573C3; then rdi/rax are reloaded from the record header (0x378/0x380) and `jmp 0x66573C5` (pointer-pair handoff [I]); at 0x6657088, a block reached only from outside the fragment, r12d is cleared and r14=[rdi+8] is parked at [rbp+0x1E8] — last instruction before the 0x6657090 cut.

    0x665703d  je 0x6657237
    0x6657043  movups xmm0,[rax]
    0x6657046  movups xmm1,[rax+0x10]
    0x665704a  mov rcx,rax
    0x665704d  movups xmm2,[rax+0x20]
    0x6657051  movups [r15+0x20],xmm2
    0x6657056  movups [r15+0x10],xmm1
    0x665705b  movups [r15],xmm0
    0x665705f  xorps xmm0,xmm0
    0x6657062  movups [r15+0x30],xmm0
    0x6657067  test r14,r14
    0x665706a  je 0x66573C3
    0x6657070  lock inc dword ptr [r14+8]
    0x6657075  mov rdi,[rbp+0x378]
    0x665707c  mov rax,[rbp+0x380]
    0x6657083  jmp 0x66573C5
    0x6657088  xor r12d,r12d
    0x665708b  mov r14,[rdi+8]
    0x665708f  mov [rbp+0x1E8],r14
## Field table — every [reg+off] site (one row per numeric offset; sites verbatim, ';'-separated)

Sizes are per instruction (16B movups/movaps, 8B movsd/qword, 4B movss/dword, 2B word, 1B byte). Where a numeric offset is used on several base registers, all its sites share one row. Non-[reg+off] operands ([0xEEC8060], [0x1233E1B0], [0xF99FFA0]) are absolute/rip-relative constants, not fields, and are described under "Other operands" below.

| offset | size | direction | site addresses and verbatim lines | meaning |
|---|---|---|---|---|
| 0x0 | 16 | R, R, W | 0x6656f66  movups xmm0,[rcx] ; 0x6657043  movups xmm0,[rax] ; 0x665705b  movups [r15],xmm0 | [rcx] = rbp+0x234 (lea 0x6656da6), [rax] = rbp+0x348 (lea 0x6657028), [r15] = pass-list slot [V] |
| 0x4 | 4 | R | 0x6656df4  mov r8d,[rdi+4] | - |
| 0x8 | 8 (qword reads); 4 (dword atomic inc) | R, RW, RW, R | 0x6656e04  movsd xmm2,[rdi+8] ; 0x6656f20  lock inc dword ptr [rax+8] ; 0x6657070  lock inc dword ptr [r14+8] ; 0x665708b  mov r14,[rdi+8] | desc+8 saved at 0x264 [V]; the +8 dwords of the pointer/ctrl pairs at 0x210/0x380 are incremented after a null test = shared-ptr refcount [I BGFX_MAP.md:2032] |
| 0xC | 4 | R | 0x6656dff  movss xmm1,[rdi+0xC] | subtrahend of the 0x26C max calculation [V] |
| 0x10 | 4 (movss read); 8 (qword); 16 (movups copies) | R, R, R, R, W | 0x6656e11  movss xmm2,[rdi+0x10] ; 0x6656fb4  add rcx,[rsi+0x10] ; 0x6657019  mov rax,[rax+0x10] ; 0x6657046  movups xmm1,[rax+0x10] ; 0x6657056  movups [r15+0x10],xmm1 | minuend of the 0x26C calculation [V]; [rsi+0x10] = frameCtx+0x10 of the passLookup idiom [I BGFX_MAP.md:2032]; [rax+0x10] = vtable slot of the object at [0x1233E1B0] [V shape]; [r15+0x10] = part of the pushed record [V] |
| 0x14 | 16 | R, W | 0x6656e2e  movups xmm1,[rdi+0x14] ; 0x6656e32  movaps [rbp+0x270],xmm1 | - |
| 0x20 | 16 | R, W | 0x665704d  movups xmm2,[rax+0x20] ; 0x6657051  movups [r15+0x20],xmm2 | third 16B chunk of the pushed record [V] |
| 0x24 | 16 | R, W | 0x6656e39  movups xmm1,[rdi+0x24] ; 0x6656e3d  movaps [rbp+0x280],xmm1 | - |
| 0x30 | 16 | W | 0x6657062  movups [r15+0x30],xmm0 | zeroed tail of the pushed record [V] |
| 0x34 | 16 | R, W | 0x6656e44  movups xmm1,[rdi+0x34] ; 0x6656e48  movaps [rbp+0x290],xmm1 | - |
| 0x44 | 16 | R, W | 0x6656e4f  movups xmm1,[rdi+0x44] ; 0x6656e53  movaps [rbp+0x2A0],xmm1 | - |
| 0x54 | 16 | R, W | 0x6656e5a  movups xmm1,[rdi+0x54] ; 0x6656e5e  movaps [rbp+0x2B0],xmm1 | - |
| 0x58 | 16 | W | 0x665700b  movups [rbp+0x58],xmm0 | member of the 0xC0-byte zeroed local buffer rbp+0x58..0x117 [V] |
| 0x64 | 16 | R, W | 0x6656e65  movups xmm1,[rdi+0x64] ; 0x6656e69  movaps [rbp+0x2C0],xmm1 | - |
| 0x68 | 16 | W | 0x6657007  movups [rbp+0x68],xmm0 | member of the zeroed 0x58..0x117 buffer [V] |
| 0x74 | 16 | R, W | 0x6656e70  movups xmm1,[rdi+0x74] ; 0x6656e74  movaps [rbp+0x2D0],xmm1 | - |
| 0x78 | 16 | W | 0x6657003  movups [rbp+0x78],xmm0 | member of the zeroed 0x58..0x117 buffer [V] |
| 0x84 | 16 | R, W | 0x6656e7b  movups xmm1,[rdi+0x84] ; 0x6656e82  movaps [rbp+0x2E0],xmm1 | - |
| 0x88 | 16 | W | 0x6656ffc  movups [rbp+0x88],xmm0 | member of the zeroed 0x58..0x117 buffer [V] |
| 0x94 | 8 | R, W | 0x6656e89  movsd xmm1,[rdi+0x94] ; 0x6656e91  movsd [rbp+0x2F0],xmm1 | - |
| 0x98 | 16 | W | 0x6656ff5  movups [rbp+0x98],xmm0 | member of the zeroed 0x58..0x117 buffer [V] |
| 0x9C | 4 | R, W | 0x6656e99  movss xmm1,[rdi+0x9C] ; 0x6656ea1  movss [rbp+0x2F8],xmm1 | - |
| 0xA0 | 1 | R, W | 0x6656ea9  movzx r8d,byte ptr [rdi+0xA0] ; 0x6656eb1  mov [rbp+0x2FC],r8b | last byte of the 0xAD-byte 0x250 image [V] |
| 0xA8 | 16 | W | 0x6656fee  movups [rbp+0xA8],xmm0 | member of the zeroed 0x58..0x117 buffer [V] |
| 0xB8 | 16 | W | 0x6656fe7  movups [rbp+0xB8],xmm0 | member of the zeroed 0x58..0x117 buffer [V] |
| 0xC8 | 16 | W | 0x6656fe0  movups [rbp+0xC8],xmm0 | member of the zeroed 0x58..0x117 buffer [V] |
| 0xD8 | 16 (zeroing store) then 8 (qword read) | R, W | 0x6656d4d  mov rcx,[rdi+0xD8] ; 0x6656fd9  movups [rbp+0xD8],xmm0 | qword read is a pointer saved at 0x210 (null-checked, refcount-incremented class) [V] |
| 0xE8 | 8 (qword read) then 16 (zeroing store) | R, W | 0x6656d62  movsd xmm6,[rdi+0xE8] ; 0x6656fd2  movups [rbp+0xE8],xmm0 | double read; only its low 4B reaches 0x220 and 0x388 via movss [V] |
| 0xEC | 4 | R | 0x6656d6a  movss xmm12,[rdi+0xEC] | image stored at 0x224 and 0x38C [V] |
| 0xF0 | 8 | R, W | 0x6656eb8  movsd xmm11,[rdi+0xF0] ; 0x6656ec1  movsd [rbp+0x300],xmm11 | also written a second time into the record at 0x468 [V] |
| 0xF8 | 8 then 8 then 16 (zeroing store) | R, W, W | 0x6656eca  movsd xmm1,[rdi+0xF8] ; 0x6656ed2  movsd [rbp+0x308],xmm1 ; 0x6656fcb  movups [rbp+0xF8],xmm0 | qword image at 0x308 re-stored at 0x470 [V] |
| 0x100 | 8 | R | 0x6656d84  movsd xmm9,[rdi+0x100] | only the low 4B is stored, at 0x228 and 0x390 [V] |
| 0x104 | 8 | R | 0x6656d96  movsd xmm7,[rdi+0x104] | 8B image stored at 0x22C and 0x394 [V] |
| 0x108 | 16 | W | 0x6656fc4  movups [rbp+0x108],xmm0 | top member of the zeroed 0x58..0x117 buffer [V] |
| 0x10C | 16 | R, W | 0x6656dad  movups xmm1,[rdi+0x10C] ; 0x6656db4  movups [rbp+0x234],xmm1 | - |
| 0x11C | 8 | R | 0x6656dbb  movsd xmm8,[rdi+0x11C] | 8B image stored at 0x244 and 0x3AC [V] |
| 0x124 | 4 | R | 0x6656dcd  movss xmm10,[rdi+0x124] | image stored at 0x24C and 0x3B4 [V] |
| 0x128 | 16 | R, W | 0x6656de6  movups xmm1,[rdi+0x128] ; 0x6656ded  movaps [rbp+0x250],xmm1 | first 16B of the 0xAD-byte image copied to 0x3B8 [V] |
| 0x1C8 | 2 | W | 0x6656f16  mov [rbp+0x1C8],r9w | stores the r9w value current at fragment start (same value also parked at 0x340) [V] |
| 0x1E0 | 16 | R | 0x6656ee2  movaps xmm1,[rbp+0x1E0] | local written before the fragment; becomes the record's first 16B at 0x348 [V] |
| 0x1E8 | 8 | W | 0x665708f  mov [rbp+0x1E8],r14 | - |
| 0x1F0 | 16 | R | 0x6656ee9  movaps xmm2,[rbp+0x1F0] | becomes record +0x10 at 0x358 [V] |
| 0x200 | 16 | R | 0x6656ef0  movaps xmm3,[rbp+0x200] | becomes record +0x20 at 0x368 [V] |
| 0x210 | 8 | W, R | 0x6656d54  mov [rbp+0x210],rcx ; 0x6656f30  mov rdi,[rbp+0x210] | holds the qword read from [rdi+0xD8] (a refcounted-object pointer [I from the [ptr+8] lock incs]); reloaded into rdi for the record header [V] |
| 0x218 | 8 | W, R | 0x6656d5b  mov [rbp+0x218],rax ; 0x6656f24  mov r14,[rbp+0x218] | partner slot of 0x210, holds rax = 0 here; its reload feeds the refcount path [V] |
| 0x220 | 4 | W | 0x6656d73  movss [rbp+0x220],xmm6 | low 4B of the desc+0xE8 read [V] |
| 0x224 | 4 | W | 0x6656d7b  movss [rbp+0x224],xmm12 | image of desc+0xEC [V] |
| 0x228 | 4 | W | 0x6656d8d  movss [rbp+0x228],xmm9 | low 4B of the desc+0x100 read [V] |
| 0x22C | 8 | W | 0x6656d9e  movsd [rbp+0x22C],xmm7 | image of desc+0x104 [V] |
| 0x234 | 16 | W | 0x6656db4  movups [rbp+0x234],xmm1 | image of desc+0x10C; address taken at 0x6656da6 lea rcx,[rbp+0x234] and re-read via [rcx] at 0x6656f66 [V] |
| 0x244 | 8 | W | 0x6656dc4  movsd [rbp+0x244],xmm8 | image of desc+0x11C [V] |
| 0x24C | 4 | W | 0x6656dd6  movss [rbp+0x24C],xmm10 | image of desc+0x124 [V] |
| 0x250 | 16 | W | 0x6656ded  movaps [rbp+0x250],xmm1 | first 16B of the 0xAD-byte image; address taken at 0x6656ddf lea rdx,[rbp+0x250] as source of the 0xEEC6EC0 copy [V] |
| 0x260 | 4 | W | 0x6656df8  mov [rbp+0x260],r8d | image of desc+0x4 [V] |
| 0x264 | 8 | W | 0x6656e09  movsd [rbp+0x264],xmm2 | image of desc+0x8 [V] |
| 0x26C | 4 | W | 0x6656e26  movss [rbp+0x26C],xmm1 | max(const at [0xEEC8060], desc+0x10 minus desc+0xC) [V] |
| 0x270 | 16 | W | 0x6656e32  movaps [rbp+0x270],xmm1 | image of desc+0x14 [V] |
| 0x280 | 16 | W | 0x6656e3d  movaps [rbp+0x280],xmm1 | image of desc+0x24 [V] |
| 0x290 | 16 | W | 0x6656e48  movaps [rbp+0x290],xmm1 | image of desc+0x34 [V] |
| 0x2A0 | 16 | W | 0x6656e53  movaps [rbp+0x2A0],xmm1 | image of desc+0x44 [V] |
| 0x2B0 | 16 | W | 0x6656e5e  movaps [rbp+0x2B0],xmm1 | image of desc+0x54 [V] |
| 0x2C0 | 16 | W | 0x6656e69  movaps [rbp+0x2C0],xmm1 | image of desc+0x64 [V] |
| 0x2D0 | 16 | W | 0x6656e74  movaps [rbp+0x2D0],xmm1 | image of desc+0x74 [V] |
| 0x2E0 | 16 | W | 0x6656e82  movaps [rbp+0x2E0],xmm1 | image of desc+0x84 [V] |
| 0x2F0 | 8 | W | 0x6656e91  movsd [rbp+0x2F0],xmm1 | image of desc+0x94 [V] |
| 0x2F8 | 4 | W | 0x6656ea1  movss [rbp+0x2F8],xmm1 | image of desc+0x9C [V] |
| 0x2FC | 1 | W | 0x6656eb1  mov [rbp+0x2FC],r8b | final byte of the 0x250 image (desc+0xA0) [V] |
| 0x300 | 8 | W | 0x6656ec1  movsd [rbp+0x300],xmm11 | image of desc+0xF0 [V] |
| 0x308 | 8 (both sites) | W, R | 0x6656ed2  movsd [rbp+0x308],xmm1 ; 0x6656f9e  mov rax,[rbp+0x308] | image of desc+0xF8; re-stored into the record at 0x470 and kept in r12 [V] |
| 0x340 | 2 | W | 0x6656eda  mov [rbp+0x340],r9w | parks the incoming r9w [V] |
| 0x348 | 16 | W | 0x6656ef7  movups [rbp+0x348],xmm1 | record base (offset +0x00); address taken at 0x6657028 lea rax,[rbp+0x348], read via [rax] rows 0x0/0x10/0x20, pushed to [r15] [V] |
| 0x358 | 16 | W | 0x6656efe  movups [rbp+0x358],xmm2 | record +0x10 [V] |
| 0x368 | 16 | W | 0x6656f05  movups [rbp+0x368],xmm3 | record +0x20 [V] |
| 0x378 | 16 (zero fill) then 8, 8 | W, W, R | 0x6656f0c  movups [rbp+0x378],xmm0 ; 0x6656f37  mov [rbp+0x378],rdi ; 0x6657075  mov rdi,[rbp+0x378] | first zeroed, then holds the 0x210 pointer; reloaded into rdi before `jmp 0x66573C5` [V] |
| 0x380 | 8 | W, R | 0x6656f3e  mov [rbp+0x380],r14 ; 0x665707c  mov rax,[rbp+0x380] | refcount ctrl slot of the record pair (0 here), reloaded before `jmp 0x66573C5` [V] |
| 0x388 | 4 | W | 0x6656f45  movss [rbp+0x388],xmm6 | copy of desc+0xE8 low 4B into the record [V] |
| 0x38C | 4 | W | 0x6656f4d  movss [rbp+0x38C],xmm12 | copy of desc+0xEC into the record [V] |
| 0x390 | 4 | W | 0x6656f56  movss [rbp+0x390],xmm9 | copy of desc+0x100 low 4B into the record [V] |
| 0x394 | 8 (qword) | W | 0x6656f5f  movlps [rbp+0x394],xmm7 | 8B image of desc+0x104 into the record [V] |
| 0x39C | 16 | W | 0x6656f69  movups [rbp+0x39C],xmm0 | record +0x24: the 0x234 block (desc+0x10C image) [V] |
| 0x3AC | 8 (qword) | W | 0x6656f70  movlps [rbp+0x3AC],xmm8 | record +0x34: 8B of desc+0x11C [V] |
| 0x3B4 | 4 | W | 0x6656f78  movss [rbp+0x3B4],xmm10 | record +0x3C: desc+0x124 [V] |
| 0x3B8 | - (addr only) | addr | 0x6656f81  lea r13,[rbp+0x3B8] | destination of `call 0xEEC6EC0` (rcx=r13, rdx=rbp+0x250, r8d=0xAD): a 0xAD-byte copy lands at rbp+0x3B8..0x464 [V shape] |
| 0x468 | 8 (qword) | W | 0x6656f96  movlps [rbp+0x468],xmm11 | 8B of desc+0xF0 appended after the 0xAD copy [V] |
| 0x470 | 8 | W | 0x6656fa8  mov [rbp+0x470],rax | the 0x308 qword (desc+0xF8 image) appended after it [V] |
| 0x548 | 8 | R | 0x665702f  mov r15,[rsi+0x548] | r15 = end pointer of a list on the 0x5ABA5C0 pass object; the push target [I see row 0x0, BGFX_MAP.md:828] |
| 0x550 | 8 | R | 0x6657036  cmp r15,[rsi+0x550] | the other bound of that list; equal means no push and exit to 0x6657237 [I] |

## Other operands (absolute/rip-relative, not [reg+off] fields)
- 0x6656e1a movss xmm1,[0xEEC8060]: float constant read; value not determined here [?].
- 0x665700f mov rcx,[0x1233E1B0]: global object pointer; its vtable slot at +0x10 is called through the CFG thunk cell 0x665701f call qword ptr [0xF99FFA0] with dl=0x4A [I BGFX_MAP.md:176]; result -> ebx [? purpose].

## Notes
- Branch targets 0x6657237, 0x66573C3, 0x66573C5 and the 0x6657088 entry edge lie outside the listing [V].
- The record built at rbp+0x348 spans 0x40 bytes and is pushed whole to [r15]; the record at rbp+0x378 spans at least through 0x478 (header 0x378..0x3B7, 0xAD-byte body 0x3B8..0x464, qwords 0x468/0x470) [V layout from the stores].
- open question: exact kind of the list at pass+0x548/+0x550 and the consumer at 0x66573C5 [?].

## OPEN questions
- Purpose of the CFG-thunk call with dl=0x4A and of its eax result saved to ebx [?].
- Value/role of the float constant at [0xEEC8060] [?].
- Writers of the pre-set locals rbp+0x1E0/0x1F0/0x200 (before the fragment) and of r9w [?].
- Identity check of 0xEEC6EC0 as memcpy-style copy vs construct-copy [I only].

## TOOL REQUESTS
None.
