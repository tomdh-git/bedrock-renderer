## NEXT
DONE

## ClientInstance loadResources 0x186e6a0 — instruction slice 0x186fae3..0x186fffc (chunk 5 of 6)

Every one of the 250 listed instructions belongs to exactly one phase below (each phase <= 40 instructions; phases are contiguous in listing order, no gaps, no skipped instructions). Verbatim `0xRVA  instr` lines are copied from docs/progress/_part_Lr5.txt (verified against the exe via rdis).

Phase 1, 0x186fae3..0x186fb99 (instructions 1-36 of 250): loads the allocator function pointer ([0x1233E1A8] -> [rax] -> [rax+8]) and calls it through [0xF99FFA0] with edx=8, jumping to 0x1870291 when the result is NULL. Saves the handle at [rbp+0x5B0] and base+8 at [rbp+0x5C0] and [rbp+0x5B8], writes qword tag 0x600000007 at [rdi], builds descriptor {ptr 0xF568A78 at [rbp+0x150], len 0xC at [rbp+0x158]}, spills rsi to [rsp+0x20], calls 0x1870DE0(rcx=[rbp+0x628], rdx=&desc, r8=&slot[rbp+0x5D0], r9d=0x18), releases the old slot value ([rbp+0x5D0] -> 0x2FE440 -> 0xE935700 size 0x138), then zeroes the slot ([rbp+0x5D0] 16 bytes via movaps, [rbp+0x5E0] = 0).
0x186fae3  mov rax,[rax+8]
0x186fae7  mov edx,8
0x186faec  call qword ptr [0xF99FFA0]
0x186faf2  nop
0x186faf3  mov rdi,rax
0x186faf6  test rax,rax
0x186faf9  je 0x1870291
0x186faff  mov [rbp+0x5B0],rdi
0x186fb06  mov rax,rdi
0x186fb09  add rax,8
0x186fb0d  mov [rbp+0x5C0],rax
0x186fb14  mov rcx,0x600000007
0x186fb1e  mov [rdi],rcx
0x186fb21  mov [rbp+0x5B8],rax
0x186fb28  mov qword ptr [rbp+0x5D0],0
0x186fb33  lea rax,[0xF568A78]
0x186fb3a  mov [rbp+0x150],rax
0x186fb41  mov qword ptr [rbp+0x158],0xC
0x186fb4c  mov [rsp+0x20],rsi
0x186fb51  lea rdx,[rbp+0x150]
0x186fb58  lea rsi,[rbp+0x5D0]
0x186fb5f  mov rcx,[rbp+0x628]
0x186fb66  mov r8,rsi
0x186fb69  mov r9d,0x18
0x186fb6f  call 0x1870DE0
0x186fb74  nop
0x186fb75  mov rdi,[rbp+0x5D0]
0x186fb7c  test rdi,rdi
0x186fb7f  je short 0x186FB96
0x186fb81  mov rcx,rdi
0x186fb84  call 0x2FE440
0x186fb89  mov edx,0x138
0x186fb8e  mov rcx,rdi
0x186fb91  call 0xE935700
0x186fb96  xorps xmm0,xmm0
0x186fb99  movaps [rbp+0x5D0],xmm0

Phase 2, 0x186fba0..0x186fc63 (instructions 37-73 of 250): zeroes [rbp+0x5E0], allocates another 8-byte buffer via the same allocator chain (edx=8), stores handle at [rbp+0x5D0], base+8 at [rbp+0x5E0], extra base+8 copy at [rbp+0x5D8], writes qword tag rbx=0x700000006 at [rdi]. Clears slot [rbp+0x3A8], builds descriptor {ptr 0xF557386 at [rbp+0x160], len 0xF at [rbp+0x168]}, calls 0x1870DE0(rcx=[rbp+0x628], rdx=&desc, r8=&slot[rbp+0x3A8], r9d=0x19), releases previous [rbp+0x3A8] via 0x2FE440 + 0xE935700 (edx=0x138).
0x186fba0  mov qword ptr [rbp+0x5E0],0
0x186fbab  mov rcx,[0x1233E1A8]
0x186fbb2  mov rax,[rcx]
0x186fbb5  mov rax,[rax+8]
0x186fbb9  mov edx,8
0x186fbbe  call qword ptr [0xF99FFA0]
0x186fbc4  nop
0x186fbc5  mov rdi,rax
0x186fbc8  test rax,rax
0x186fbcb  je 0x18702A1
0x186fbd1  mov [rbp+0x5D0],rdi
0x186fbd8  mov rax,rdi
0x186fbdb  add rax,8
0x186fbdf  mov [rbp+0x5E0],rax
0x186fbe6  mov rbx,0x700000006
0x186fbf0  mov [rdi],rbx
0x186fbf3  mov [rbp+0x5D8],rax
0x186fbfa  mov qword ptr [rbp+0x3A8],0
0x186fc05  lea rax,[0xF557386]
0x186fc0c  mov [rbp+0x160],rax
0x186fc13  mov qword ptr [rbp+0x168],0xF
0x186fc1e  mov [rsp+0x20],rsi
0x186fc23  lea rdx,[rbp+0x160]
0x186fc2a  lea rsi,[rbp+0x3A8]
0x186fc31  mov rcx,[rbp+0x628]
0x186fc38  mov r8,rsi
0x186fc3b  mov r9d,0x19
0x186fc41  call 0x1870DE0
0x186fc46  nop
0x186fc47  mov rdi,[rbp+0x3A8]
0x186fc4e  test rdi,rdi
0x186fc51  je short 0x186FC68
0x186fc53  mov rcx,rdi
0x186fc56  call 0x2FE440
0x186fc5b  mov edx,0x138
0x186fc60  mov rcx,rdi
0x186fc63  call 0xE935700
Phase 3, 0x186fc68..0x186fd19 (instructions 74-108 of 250): allocates a 4-byte buffer (edx=4), stores handle at [rbp+0x3A8], rax+4 at [rbp+0x3B8] and [rbp+0x3B0], writes dword tag 6 at [rdi], clears [rbp+0x3C0]. Builds descriptor {ptr 0xF53B85C at [rbp+0x170], len 0xC at [rbp+0x178]}, calls 0x1870DE0(rcx=[rbp+0x628], rdx=&desc, r8=&slot[rbp+0x3C0], r9d=0x27), releases previous [rbp+0x3C0] via 0x2FE440 + 0xE935700.
0x186fc68  mov rcx,[0x1233E1A8]
0x186fc6f  mov rax,[rcx]
0x186fc72  mov rax,[rax+8]
0x186fc76  mov edx,4
0x186fc7b  call qword ptr [0xF99FFA0]
0x186fc81  nop
0x186fc82  mov rdi,rax
0x186fc85  test rax,rax
0x186fc88  je 0x18702B1
0x186fc8e  mov [rbp+0x3A8],rdi
0x186fc95  mov rax,rdi
0x186fc98  add rax,4
0x186fc9c  mov [rbp+0x3B8],rax
0x186fca3  mov dword ptr [rdi],6
0x186fca9  mov [rbp+0x3B0],rax
0x186fcb0  mov qword ptr [rbp+0x3C0],0
0x186fcbb  lea rax,[0xF53B85C]
0x186fcc2  mov [rbp+0x170],rax
0x186fcc9  mov qword ptr [rbp+0x178],0xC
0x186fcd4  mov [rsp+0x20],rsi
0x186fcd9  lea rdx,[rbp+0x170]
0x186fce0  lea rsi,[rbp+0x3C0]
0x186fce7  mov rcx,[rbp+0x628]
0x186fcee  mov r8,rsi
0x186fcf1  mov r9d,0x27
0x186fcf7  call 0x1870DE0
0x186fcfc  nop
0x186fcfd  mov rdi,[rbp+0x3C0]
0x186fd04  test rdi,rdi
0x186fd07  je short 0x186FD1E
0x186fd09  mov rcx,rdi
0x186fd0c  call 0x2FE440
0x186fd11  mov edx,0x138
0x186fd16  mov rcx,rdi
0x186fd19  call 0xE935700

Phase 4, 0x186fd1e..0x186fdd6 (instructions 109-144 of 250): allocates an 8-byte buffer, stores handle at [rbp+0x3C0], base+8 at [rbp+0x3D0] and [rbp+0x3C8], writes qword tag 0x600000005 at [rdi], clears [rbp+0x3D8]. Builds descriptor {ptr 0xF568A97 at [rbp+0x180], len 0xD at [rbp+0x188]}, calls 0x1870DE0(rcx=[rbp+0x628], rdx=&desc, r8=&slot[rbp+0x3D8], r9d=0x1A), releases previous [rbp+0x3D8] via 0x2FE440 + 0xE935700.
0x186fd1e  mov rcx,[0x1233E1A8]
0x186fd25  mov rax,[rcx]
0x186fd28  mov rax,[rax+8]
0x186fd2c  mov edx,8
0x186fd31  call qword ptr [0xF99FFA0]
0x186fd37  nop
0x186fd38  mov rdi,rax
0x186fd3b  test rax,rax
0x186fd3e  je 0x18702C1
0x186fd44  mov [rbp+0x3C0],rdi
0x186fd4b  mov rax,rdi
0x186fd4e  add rax,8
0x186fd52  mov [rbp+0x3D0],rax
0x186fd59  mov rcx,0x600000005
0x186fd63  mov [rdi],rcx
0x186fd66  mov [rbp+0x3C8],rax
0x186fd6d  mov qword ptr [rbp+0x3D8],0
0x186fd78  lea rax,[0xF568A97]
0x186fd7f  mov [rbp+0x180],rax
0x186fd86  mov qword ptr [rbp+0x188],0xD
0x186fd91  mov [rsp+0x20],rsi
0x186fd96  lea rdx,[rbp+0x180]
0x186fd9d  lea rsi,[rbp+0x3D8]
0x186fda4  mov rcx,[rbp+0x628]
0x186fdab  mov r8,rsi
0x186fdae  mov r9d,0x1A
0x186fdb4  call 0x1870DE0
0x186fdb9  nop
0x186fdba  mov rdi,[rbp+0x3D8]
0x186fdc1  test rdi,rdi
0x186fdc4  je short 0x186FDDB
0x186fdc6  mov rcx,rdi
0x186fdc9  call 0x2FE440
0x186fdce  mov edx,0x138
0x186fdd3  mov rcx,rdi
0x186fdd6  call 0xE935700
Phase 5, 0x186fddb..0x186fe89 (instructions 145-179 of 250): allocates an 8-byte buffer, stores handle at [rbp+0x3D8], base+8 at [rbp+0x3E8] and [rbp+0x3E0], writes qword tag rbx=0x700000006 at [rdi], clears [rbp+0x3F0]. Builds descriptor {ptr 0xF55A7C7 at [rbp+0x190], len 0x17 at [rbp+0x198]}, calls 0x1870DE0(rcx=[rbp+0x628], rdx=&desc, r8=&slot[rbp+0x3F0], r9d=0x1B), releases previous [rbp+0x3F0] via 0x2FE440 + 0xE935700.
0x186fddb  mov rcx,[0x1233E1A8]
0x186fde2  mov rax,[rcx]
0x186fde5  mov rax,[rax+8]
0x186fde9  mov edx,8
0x186fdee  call qword ptr [0xF99FFA0]
0x186fdf4  nop
0x186fdf5  mov rdi,rax
0x186fdf8  test rax,rax
0x186fdfb  je 0x18702D1
0x186fe01  mov [rbp+0x3D8],rdi
0x186fe08  mov rax,rdi
0x186fe0b  add rax,8
0x186fe0f  mov [rbp+0x3E8],rax
0x186fe16  mov [rdi],rbx
0x186fe19  mov [rbp+0x3E0],rax
0x186fe20  mov qword ptr [rbp+0x3F0],0
0x186fe2b  lea rax,[0xF55A7C7]
0x186fe32  mov [rbp+0x190],rax
0x186fe39  mov qword ptr [rbp+0x198],0x17
0x186fe44  mov [rsp+0x20],rsi
0x186fe49  lea rdx,[rbp+0x190]
0x186fe50  lea rsi,[rbp+0x3F0]
0x186fe57  mov rcx,[rbp+0x628]
0x186fe5e  mov r8,rsi
0x186fe61  mov r9d,0x1B
0x186fe67  call 0x1870DE0
0x186fe6c  nop
0x186fe6d  mov rdi,[rbp+0x3F0]
0x186fe74  test rdi,rdi
0x186fe77  je short 0x186FE8E
0x186fe79  mov rcx,rdi
0x186fe7c  call 0x2FE440
0x186fe81  mov edx,0x138
0x186fe86  mov rcx,rdi
0x186fe89  call 0xE935700

Phase 6, 0x186fe8e..0x186ff3f (instructions 180-214 of 250): allocates a 4-byte buffer (edx=4), stores handle at [rbp+0x3F0], rax+4 at [rbp+0x400] and [rbp+0x3F8], writes dword tag 1 at [rdi], clears [rbp+0x408]. Builds descriptor {ptr 0xF549EEB at [rbp+0x1A0], len 0xD at [rbp+0x1A8]}, calls 0x1870DE0(rcx=[rbp+0x628], rdx=&desc, r8=&slot[rbp+0x408], r9d=0x1C), releases previous [rbp+0x408] via 0x2FE440 + 0xE935700.
0x186fe8e  mov rcx,[0x1233E1A8]
0x186fe95  mov rax,[rcx]
0x186fe98  mov rax,[rax+8]
0x186fe9c  mov edx,4
0x186fea1  call qword ptr [0xF99FFA0]
0x186fea7  nop
0x186fea8  mov rdi,rax
0x186feab  test rax,rax
0x186feae  je 0x18702E1
0x186feb4  mov [rbp+0x3F0],rdi
0x186febb  mov rax,rdi
0x186febe  add rax,4
0x186fec2  mov [rbp+0x400],rax
0x186fec9  mov dword ptr [rdi],1
0x186fecf  mov [rbp+0x3F8],rax
0x186fed6  mov qword ptr [rbp+0x408],0
0x186fee1  lea rax,[0xF549EEB]
0x186fee8  mov [rbp+0x1A0],rax
0x186feef  mov qword ptr [rbp+0x1A8],0xD
0x186fefa  mov [rsp+0x20],rsi
0x186feff  lea rdx,[rbp+0x1A0]
0x186ff06  lea rsi,[rbp+0x408]
0x186ff0d  mov rcx,[rbp+0x628]
0x186ff14  mov r8,rsi
0x186ff17  mov r9d,0x1C
0x186ff1d  call 0x1870DE0
0x186ff22  nop
0x186ff23  mov rdi,[rbp+0x408]
0x186ff2a  test rdi,rdi
0x186ff2d  je short 0x186FF44
0x186ff2f  mov rcx,rdi
0x186ff32  call 0x2FE440
0x186ff37  mov edx,0x138
0x186ff3c  mov rcx,rdi
0x186ff3f  call 0xE935700
Phase 7, 0x186ff44..0x186fffc (instructions 215-250 of 250): allocates an 8-byte buffer, stores handle at [rbp+0x408], base+8 at [rbp+0x418] and [rbp+0x410], writes qword tag 0x1900000001 at [rdi], clears [rbp+0x420]. Builds descriptor {ptr 0xF54D038 at [rbp+0x1B0], len 7 at [rbp+0x1B8]}, calls 0x1870DE0(rcx=[rbp+0x628], rdx=&desc, r8=&slot[rbp+0x420], r9d=0xD), releases previous [rbp+0x420] via 0x2FE440 + 0xE935700; the slice ends at the release call 0xE935700 at 0x186fffc.
0x186ff44  mov rcx,[0x1233E1A8]
0x186ff4b  mov rax,[rcx]
0x186ff4e  mov rax,[rax+8]
0x186ff52  mov edx,8
0x186ff57  call qword ptr [0xF99FFA0]
0x186ff5d  nop
0x186ff5e  mov rdi,rax
0x186ff61  test rax,rax
0x186ff64  je 0x18702F1
0x186ff6a  mov [rbp+0x408],rdi
0x186ff71  mov rax,rdi
0x186ff74  add rax,8
0x186ff78  mov [rbp+0x418],rax
0x186ff7f  mov rcx,0x1900000001
0x186ff89  mov [rdi],rcx
0x186ff8c  mov [rbp+0x410],rax
0x186ff93  mov qword ptr [rbp+0x420],0
0x186ff9e  lea rax,[0xF54D038]
0x186ffa5  mov [rbp+0x1B0],rax
0x186ffac  mov qword ptr [rbp+0x1B8],7
0x186ffb7  mov [rsp+0x20],rsi
0x186ffbc  lea rdx,[rbp+0x1B0]
0x186ffc3  lea rsi,[rbp+0x420]
0x186ffca  mov rcx,[rbp+0x628]
0x186ffd1  mov r8,rsi
0x186ffd4  mov r9d,0xD
0x186ffda  call 0x1870DE0
0x186ffdf  nop
0x186ffe0  mov rdi,[rbp+0x420]
0x186ffe7  test rdi,rdi
0x186ffea  je short 0x1870001
0x186ffec  mov rcx,rdi
0x186ffef  call 0x2FE440
0x186fff4  mov edx,0x138
0x186fff9  mov rcx,rdi
0x186fffc  call 0xE935700

## Field map: every [reg+off] load/store in the slice (offset | size | read/store address | verbatim instr | meaning)

Sizes come from the instruction (qword = 8, dword = 4, movaps = 16). One row per distinct offset; all sites of that offset are listed. Meaning is "-" unless an instruction or string in the slice shows it.

| offset | size | site | instr | meaning |
| 0x0 | 8/8/8/4/8/8/4/8 | W 0x186fb1e ([rdi] qword tag 0x600000007); R 0x186fbb2 ([rcx] allocator global); W 0x186fbf0 ([rdi] qword tag rbx=0x700000006); W 0x186fca3 ([rdi] dword tag 6); W 0x186fd63 ([rdi] qword tag 0x600000005); W 0x186fe16 ([rdi] qword tag rbx=0x700000006); W 0x186fec9 ([rdi] dword tag 1); W 0x186ff89 ([rdi] qword tag 0x1900000001) | `0x186fb1e  mov [rdi],rcx` ; `0x186fbb2  mov rax,[rcx]` ; `0x186fbf0  mov [rdi],rbx` ; `0x186fca3  mov dword ptr [rdi],6` ; `0x186fd63  mov [rdi],rcx` ; `0x186fe16  mov [rdi],rbx` ; `0x186fec9  mov dword ptr [rdi],1` ; `0x186ff89  mov [rdi],rcx` | type-tag stores at buffer base [rdi]+0 (immediates visible at each store); allocator [rcx]/[rax+8] loads: - |
| 0x8 | 8/8 | R 0x186fae3 ([rax+8]); R 0x186fbb5 ([rax+8]) | `0x186fae3  mov rax,[rax+8]` ; `0x186fbb5  mov rax,[rax+8]` | allocator function-pointer load from [rax+8]: - |
| 0x20 | 8 | W 0x186fb4c ([rsp+0x20]); W 0x186fc1e ([rsp+0x20]); W 0x186fcd4 ([rsp+0x20]); W 0x186fd91 ([rsp+0x20]); W 0x186fe44 ([rsp+0x20]); W 0x186fefa ([rsp+0x20]); W 0x186ffb7 ([rsp+0x20]) | `0x186fb4c  mov [rsp+0x20],rsi` ; `0x186fc1e  mov [rsp+0x20],rsi` ; `0x186fcd4  mov [rsp+0x20],rsi` ; `0x186fd91  mov [rsp+0x20],rsi` ; `0x186fe44  mov [rsp+0x20],rsi` ; `0x186fefa  mov [rsp+0x20],rsi` ; `0x186ffb7  mov [rsp+0x20],rsi` | rsi spill slot reused before each 0x1870DE0 call: - |
| 0x150 | 8 | W 0x186fb3a | `0x186fb3a  mov [rbp+0x150],rax` | descriptor.ptr passed as rdx to 0x1870DE0 (id 0x18); pointer from lea rax,[0xF568A78] at 0x186fb33 |
| 0x158 | 8 | W 0x186fb41 | `0x186fb41  mov qword ptr [rbp+0x158],0xC` | descriptor.len = 0xC for id 0x18 |
| 0x160 | 8 | W 0x186fc0c | `0x186fc0c  mov [rbp+0x160],rax` | descriptor.ptr passed as rdx to 0x1870DE0 (id 0x19); pointer from lea rax,[0xF557386] at 0x186fc05 |
| 0x168 | 8 | W 0x186fc13 | `0x186fc13  mov qword ptr [rbp+0x168],0xF` | descriptor.len = 0xF for id 0x19 |
| 0x170 | 8 | W 0x186fcc2 | `0x186fcc2  mov [rbp+0x170],rax` | descriptor.ptr passed as rdx to 0x1870DE0 (id 0x27); pointer from lea rax,[0xF53B85C] at 0x186fcbb |
| 0x178 | 8 | W 0x186fcc9 | `0x186fcc9  mov qword ptr [rbp+0x178],0xC` | descriptor.len = 0xC for id 0x27 |
| 0x180 | 8 | W 0x186fd7f | `0x186fd7f  mov [rbp+0x180],rax` | descriptor.ptr passed as rdx to 0x1870DE0 (id 0x1A); pointer from lea rax,[0xF568A97] at 0x186fd78 |
| 0x188 | 8 | W 0x186fd86 | `0x186fd86  mov qword ptr [rbp+0x188],0xD` | descriptor.len = 0xD for id 0x1A |
| 0x190 | 8 | W 0x186fe32 | `0x186fe32  mov [rbp+0x190],rax` | descriptor.ptr passed as rdx to 0x1870DE0 (id 0x1B); pointer from lea rax,[0xF55A7C7] at 0x186fe2b |
| 0x198 | 8 | W 0x186fe39 | `0x186fe39  mov qword ptr [rbp+0x198],0x17` | descriptor.len = 0x17 for id 0x1B |
| 0x1A0 | 8 | W 0x186fee8 | `0x186fee8  mov [rbp+0x1A0],rax` | descriptor.ptr passed as rdx to 0x1870DE0 (id 0x1C); pointer from lea rax,[0xF549EEB] at 0x186fee1 |
| 0x1A8 | 8 | W 0x186feef | `0x186feef  mov qword ptr [rbp+0x1A8],0xD` | descriptor.len = 0xD for id 0x1C |
| 0x1B0 | 8 | W 0x186ffa5 | `0x186ffa5  mov [rbp+0x1B0],rax` | descriptor.ptr passed as rdx to 0x1870DE0 (id 0xD); pointer from lea rax,[0xF54D038] at 0x186ff9e |
| 0x1B8 | 8 | W 0x186ffac | `0x186ffac  mov qword ptr [rbp+0x1B8],7` | descriptor.len = 7 for id 0xD |
| 0x3A8 | 8/8/8 | W 0x186fbfa; R 0x186fc47; W 0x186fc8e | `0x186fbfa  mov qword ptr [rbp+0x3A8],0` ; `0x186fc47  mov rdi,[rbp+0x3A8]` ; `0x186fc8e  mov [rbp+0x3A8],rdi` | client slot for id 0x19: cleared, loaded for release, re-stored: - |
| 0x3B0 | 8 | W 0x186fca9 | `0x186fca9  mov [rbp+0x3B0],rax` | slot copy of base+4 (id 0x27 block): - |
| 0x3B8 | 8 | W 0x186fc9c | `0x186fc9c  mov [rbp+0x3B8],rax` | slot copy of base+4 (id 0x27 block): - |
| 0x3C0 | 8/8/8 | W 0x186fcb0; R 0x186fcfd; W 0x186fd44 | `0x186fcb0  mov qword ptr [rbp+0x3C0],0` ; `0x186fcfd  mov rdi,[rbp+0x3C0]` ; `0x186fd44  mov [rbp+0x3C0],rdi` | client slot for id 0x27: zeroed, loaded for release, re-stored: - |
| 0x3C8 | 8 | W 0x186fd66 | `0x186fd66  mov [rbp+0x3C8],rax` | slot copy of base+8 (id 0x1A block): - |
| 0x3D0 | 8 | W 0x186fd52 | `0x186fd52  mov [rbp+0x3D0],rax` | slot copy of base+8 (id 0x19 block): - |
| 0x3D8 | 8/8/8 | W 0x186fd6d; R 0x186fdba; W 0x186fe01 | `0x186fd6d  mov qword ptr [rbp+0x3D8],0` ; `0x186fdba  mov rdi,[rbp+0x3D8]` ; `0x186fe01  mov [rbp+0x3D8],rdi` | client slot for id 0x1A: zeroed, loaded for release, re-stored: - |
| 0x3E0 | 8 | W 0x186fe19 | `0x186fe19  mov [rbp+0x3E0],rax` | slot copy of base+8 (id 0x1B block): - |
| 0x3E8 | 8 | W 0x186fe0f | `0x186fe0f  mov [rbp+0x3E8],rax` | slot copy of base+8 (id 0x1B block): - |
| 0x3F0 | 8/8/8 | W 0x186fe20; R 0x186fe6d; W 0x186feb4 | `0x186fe20  mov qword ptr [rbp+0x3F0],0` ; `0x186fe6d  mov rdi,[rbp+0x3F0]` ; `0x186feb4  mov [rbp+0x3F0],rdi` | client slot for id 0x1B: zeroed, loaded for release, re-stored: - |
| 0x3F8 | 8 | W 0x186fecf | `0x186fecf  mov [rbp+0x3F8],rax` | slot copy of base+4 (id 0x1C block): - |
| 0x400 | 8 | W 0x186fec2 | `0x186fec2  mov [rbp+0x400],rax` | slot copy of base+4 (id 0x1C block): - |
| 0x408 | 8/8/8 | W 0x186fed6; R 0x186ff23; W 0x186ff6a | `0x186fed6  mov qword ptr [rbp+0x408],0` ; `0x186ff23  mov rdi,[rbp+0x408]` ; `0x186ff6a  mov [rbp+0x408],rdi` | client slot for id 0x1C: zeroed, loaded for release, re-stored: - |
| 0x410 | 8 | W 0x186ff8c | `0x186ff8c  mov [rbp+0x410],rax` | slot copy of base+8 (id 0xD block): - |
| 0x418 | 8 | W 0x186ff78 | `0x186ff78  mov [rbp+0x418],rax` | slot copy of base+8 (id 0xD block): - |
| 0x420 | 8/8 | W 0x186ff93; R 0x186ffe0 | `0x186ff93  mov qword ptr [rbp+0x420],0` ; `0x186ffe0  mov rdi,[rbp+0x420]` | client slot for id 0xD: zeroed, then loaded for release at end of slice: - |
| 0x5B0 | 8 | W 0x186faff | `0x186faff  mov [rbp+0x5B0],rdi` | saved resource handle from first allocator call (id 0x18 block): - |
| 0x5B8 | 8 | W 0x186fb21 | `0x186fb21  mov [rbp+0x5B8],rax` | copy of base+8 (id 0x18 block): - |
| 0x5C0 | 8 | W 0x186fb0d | `0x186fb0d  mov [rbp+0x5C0],rax` | copy of base+8 (id 0x18 block): - |
| 0x5D0 | 16/8/8/8 | W 0x186fb99 (movaps 16B); W 0x186fb28 (8); R 0x186fb75 (8); W 0x186fbd1 (8) | `0x186fb99  movaps [rbp+0x5D0],xmm0` ; `0x186fb28  mov qword ptr [rbp+0x5D0],0` ; `0x186fb75  mov rdi,[rbp+0x5D0]` ; `0x186fbd1  mov [rbp+0x5D0],rdi` | client slot for id 0x18: zeroed, reloaded before release, re-stored, then zeroed by movaps: - |
| 0x5D8 | 8 | W 0x186fbf3 | `0x186fbf3  mov [rbp+0x5D8],rax` | copy of base+8 (id 0x19 block): - |
| 0x5E0 | 8/8 | W 0x186fba0; W 0x186fbdf | `0x186fba0  mov qword ptr [rbp+0x5E0],0` ; `0x186fbdf  mov [rbp+0x5E0],rax` | slot copy of base+8 then zeroed (id 0x19 block): - |
| 0x628 | 8 | R 0x186fb5f; R 0x186fc31; R 0x186fce7; R 0x186fda4; R 0x186fe57; R 0x186ff0d; R 0x186ffca | `0x186fb5f  mov rcx,[rbp+0x628]` ; `0x186fc31  mov rcx,[rbp+0x628]` ; `0x186fce7  mov rcx,[rbp+0x628]` ; `0x186fda4  mov rcx,[rbp+0x628]` ; `0x186fe57  mov rcx,[rbp+0x628]` ; `0x186ff0d  mov rcx,[rbp+0x628]` ; `0x186ffca  mov rcx,[rbp+0x628]` | client-instance pointer ('this') passed as rcx to each 0x1870DE0 call: - |
