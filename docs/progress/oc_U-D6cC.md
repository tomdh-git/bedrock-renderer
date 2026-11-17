## NEXT DONE
DONE (orchestrator-written from listing sky_atmosphere_6656d4b_6657090.txt; casewalk reachable=5, clone stores into r15+0x0/0x10/0x20/0x30)

# D6 Atmosphere description field map (case head 0x66580f0, description pointer rdi)

All lines below are verbatim from the listing.

## Loads from description (rdi) in the case head
    0x6656d4d  mov rcx,[rdi+0xD8]
    0x6656d62  movsd xmm6,[rdi+0xE8]
    0x6656d6a  movss xmm12,[rdi+0xEC]
    0x6656d84  movsd xmm9,[rdi+0x100]
    0x6656d96  movsd xmm7,[rdi+0x104]
    0x6656dad  movups xmm1,[rdi+0x10C]
    0x6656dbb  movsd xmm8,[rdi+0x11C]
    0x6656dcd  movss xmm10,[rdi+0x124]
    0x6656de6  movups xmm1,[rdi+0x128]
    0x6656df4  mov r8d,[rdi+4]
    0x6656dff  movss xmm1,[rdi+0xC]
    0x6656e04  movsd xmm2,[rdi+8]
    0x6656e11  movss xmm2,[rdi+0x10]
    0x6656e2e  movups xmm1,[rdi+0x14]
    0x6656e39  movups xmm1,[rdi+0x24]
    0x6656e44  movups xmm1,[rdi+0x34]
    0x6656e4f  movups xmm1,[rdi+0x44]
    0x6656e5a  movups xmm1,[rdi+0x54]
    0x6656e65  movups xmm1,[rdi+0x64]
    0x6656e70  movups xmm1,[rdi+0x74]
    0x6656e7b  movups xmm1,[rdi+0x84]
    0x6656e89  movsd xmm1,[rdi+0x94]
    0x6656e99  movss xmm1,[rdi+0x9C]
    0x6656ea9  movzx r8d,byte ptr [rdi+0xA0]
    0x6656eb8  movsd xmm11,[rdi+0xF0]
    0x6656eca  movsd xmm1,[rdi+0xF8]

## Clone stores into pass object (r15)
    0x665705b  movups [r15],xmm0
    0x6657056  movups [r15+0x10],xmm1
    0x6657051  movups [r15+0x20],xmm2
    0x6657062  movups [r15+0x30],xmm0

Case walk from 0x66580f0 (rdi): reachable=5; no [rdi+off] read reached → read site column is [UNVERIFIED: ...]

Description size lower bound: highest clone-store offset is [r15+0x30] (movups, 16 bytes) → ≥0x40 bytes

Field summary by offset: +0x4 qword, +0x8 qword, +0x10 qword, +0x14 xmm, +0x24 xmm, +0x34 xmm, +0x44 xmm, +0x54 xmm, +0x64 xmm, +0x74 xmm, +0x84 xmm, +0x94 sd, +0x9C ss, +0xA0 byte, +0xD8 qword, +0xE8 sd, +0xEC ss, +0xF0 sd, +0xF8 sd, +0x100 sd, +0x104 sd, +0x10C xmm, +0x11C sd, +0x124 ss, +0x128 xmm

Names: none shown by instructions or strings; not guessing.
