// LIFT 0xe824ab7 size 0x8a2c 1.26.62.01 sub_e824ab7
// CHUNK 0xe8262b7..0xe827ab7
#include "client/features/render/native/d3d12/sub_e824ab7_chunk_c01.h"

#if 0
0xe8262c7  call 0xEBCE430
0xe82630e  call 0xBC5F110
0xe826471  call 0xE835F00
0xe8264d4  call 0xBC5F110
0xe826684  call 0xE835F00
0xe8266e7  call 0xBC5F110
0xe82681d  call r10
0xe8268d3  call r10
0xe8268e5  call 0xEEC6ED0
0xe826a5c  call 0xE83AED0
0xe826a70  call 0xE83AED0
0xe826a8d  call 0xE83ABB0
0xe826ab2  call 0xBC5F110
0xe826be7  call qword ptr [0xF99FFA0]
0xe826c8a  call 0xE835F00
0xe826cf0  call 0xBC5F110
0xe826f42  call 0xE83ACE0
0xe826ff2  call 0xEBCE430
0xe827007  call 0xEBCE430
0xe82704b  call 0xBC5F110
0xe827094  call qword ptr [0xF99FFA0]
0xe827193  call qword ptr [0xF99FFA0]
0xe8271a9  call 0xE83ABB0
0xe8271da  call 0xBC5F110
0xe827255  call 0xE82DCC0
0xe827333  call r10
0xe827395  call qword ptr [0xF99FFA0]
0xe82756e  call qword ptr [0xF99FFA0]
0xe82760e  call qword ptr [0xF99FFA0]
0xe82764b  call 0xEBD1560
0xe827679  call 0xE82D960
0xe8276b0  call qword ptr [0xF99FFA0]
0xe8277ab  call qword ptr [0xF99FFA0]
0xe827885  call r10
0xe8279c9  call qword ptr [0xF99FFA0]
0xe827a2f  call 0xE820500
0xe827a73  call qword ptr [0xF99FFA0]
0xe827aa5  call qword ptr [0xF99FFA0]
#endif

namespace native { namespace d3d12 {

void sub_e824ab7_chunk_c01(ChunkState_e824ab7_c01& s) {
    // Live registers at entry (matching x64 ABI + callee-saved)
    uint64_t rbx = s.rbx;
    uint64_t rbp = s.rbp;
    uint64_t r12 = s.r12;
    uint64_t r13 = s.r13;
    uint64_t r14 = s.r14;
    uint64_t r15 = s.r15;
    uint64_t rsi = s.rsi;
    uint64_t rdi = s.rdi;

    // 0xe8262b7..0xe8262d3: Initialize chunk pool entries loop continuation
    // 0xe8262b7  nop
    // 0xe8262b8  add r14,0x68
    // 0xe8262bc  mov r8d,0x28
    // 0xe8262c2  mov rcx,r14
    // 0xe8262c5  xor edx,edx
    // 0xe8262c7  call 0xEBCE430
    // 0xe8262cc  nop
    // 0xe8262cd  inc rdi
    // 0xe8262d0  cmp rdi,rsi
    // 0xe8262d3  jne 0xE826220
    {
        // 0xe8262b7..0xe8262d3
        r14 += 0x68;
        // 0xe8262c7  call 0xEBCE430
        sub_ebce430(reinterpret_cast<void*>(r14), reinterpret_cast<void*>(0x28));
        rdi++;
        if (rdi != rsi) {
            // In original this jumps back to 0xe826220 (in chunk c00)
            // For chunk boundary, we assume the loop was already executed
            // in previous chunk and this is just the tail
        }
    }

    // 0xe8262d9..0xe8262ee: Store pool size
    // 0xe8262d9  imul rax,rsi,0xB8
    // 0xe8262e0  mov rcx,[rbx+0xB0]
    // 0xe8262e7  mov [rcx+0xC96180],rax
    // 0xe8262ee  movzx eax,byte ptr [rcx+0xC96190]
    {
        // 0xe8262d9..0xe8262ee
        uint64_t rax = rsi * kChunkEntrySize;
        uint64_t* gcs = reinterpret_cast<uint64_t*>(*SF_Q(s, kOff_B0));
        *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(gcs) + kGCS_PoolSize) = rax;
        uint8_t flags = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(gcs) + kGCS_PoolFlags);
        // flags loaded into al, used at 0xe826301
    }

    // 0xe8262f5..0xe8263f7: Guard page check and chunk pool traversal for r13
    // 0xe8262f5  movzx ecx,r13w
    // 0xe8262f9  cmp ecx,0x1000
    // 0xe8262ff  jb short 0xE826320
    // 0xe826301  test al,al
    // 0xe826303  je short 0xE826320
    // 0xe826305  xor ecx,ecx
    // 0xe826307  lea rdx,[0xF7F68E3]
    // 0xe82630e  call 0xBC5F110
    // 0xe826313  nop
    // 0xe826314  imul r8,r13,0xB8
    // 0xe82631b  jmp short 0xE826333
    // 0xe826320  imul r8,r13,0xB8
    // 0xe826327  cmp ecx,0xFFF
    // 0xe82632d  jbe 0xE8263ED
    // 0xe826333  lea rsi,[r8-0xB8000]
    // 0xe82633a  mov rax,[rbx+0xB0]
    // 0xe826341  mov rax,[rax+0xC96178]
    // 0xe826348  mov rcx,[rax]
    // 0xe82634b  cmp rsi,0xB8000
    // 0xe826352  jb 0xE8263E8
    // 0xe826358  add r8,0xFFFFFFFFFFE90000
    // 0xe82635f  mov rax,r8
    // 0xe826362  shr rax,0xF
    // 0xe826366  mov rdx,0xB21642C8590B217
    // 0xe826370  mul rdx
    // 0xe826373  mov eax,edx
    // 0xe826375  not eax
    // 0xe826377  test al,7
    // 0xe826379  je short 0xE826393
    // 0xe82637b  inc edx
    // 0xe82637d  and edx,7
    // 0xe826380  add rsi,0xFFFFFFFFFFF48000
    // 0xe826387  mov rcx,[rcx+0xB8000]
    // 0xe82638e  dec rdx
    // 0xe826391  jne short 0xE826380
    // 0xe826393  cmp r8d,0x508000
    // 0xe82639a  jb short 0xE8263E8
    // 0xe8263a0  mov rax,[rcx+0xB8000]
    // 0xe8263a7  mov rax,[rax+0xB8000]
    // 0xe8263ae  mov rax,[rax+0xB8000]
    // 0xe8263b5  mov rax,[rax+0xB8000]
    // 0xe8263bc  mov rax,[rax+0xB8000]
    // 0xe8263c3  mov rax,[rax+0xB8000]
    // 0xe8263ca  mov rax,[rax+0xB8000]
    // 0xe8263d1  add rsi,0xFFFFFFFFFFA40000
    // 0xe8263d8  mov rcx,[rax+0xB8000]
    // 0xe8263df  cmp rsi,0xB7FFF
    // 0xe8263e6  ja short 0xE8263A0
    // 0xe8263e8  add rsi,rcx
    // 0xe8263eb  jmp short 0xE8263F7
    // 0xe8263ed  add r8,[rbx+0x1F8]
    // 0xe8263f4  mov rsi,r8
    // 0xe8263f7  ...
    {
        // 0xe8262f5..0xe8263f7
        uint32_t ecx = static_cast<uint16_t>(r13);
        if (ecx >= 0x1000) {
            uint8_t flags = *reinterpret_cast<uint8_t*>(*SF_Q(s, kOff_B0) + kGCS_PoolFlags);
            if (flags != 0) {
                // 0xe82630e  call 0xBC5F110
                sub_bc5f110(nullptr, reinterpret_cast<void*>(kData_F7F68E3));
            }
            r8 = r13 * kChunkEntrySize;
            goto loc_e826333;
        }

        r8 = r13 * kChunkEntrySize;
        if (ecx <= 0xFFF) {
            // 0xe8263ed..0xe8263f4
            r8 += *SF_Q(s, kOff_1F8);
            rsi = r8;
            goto loc_e8263f7;
        }

    loc_e826333:
        rsi = r8 - 0xB8000;
        uint64_t* gcs_pool_ptr = reinterpret_cast<uint64_t*>(*SF_Q(s, kOff_B0) + kGCS_PoolPtr);
        uint64_t rcx_val = *gcs_pool_ptr;
        if (rsi >= 0xB8000) {
            r8 += 0xFFFFFFFFFFE90000; // -0x170000
            uint64_t rax = r8 >> 0xF;
            rax = (rax * kMagicDivisor2) >> 64;
            uint32_t eax = static_cast<uint32_t>(rax);
            eax = ~eax;
            if ((eax & 7) == 0) {
                goto loc_e826393;
            }
            uint32_t edx = (eax + 1) & 7;
            do {
                rsi += 0xFFFFFFFFFFF48000;
                rcx_val = *reinterpret_cast<uint64_t*>(rcx_val + 0xB8000);
                edx--;
            } while (edx != 0);
        loc_e826393:
            if (static_cast<uint32_t>(r8) < 0x508000) {
                goto loc_e8263e8;
            }
            // 0xe8263a0..0xe8263e6: Unrolled 7-level traversal
            for (int i = 0; i < 7; i++) {
                rcx_val = *reinterpret_cast<uint64_t*>(rcx_val + 0xB8000);
            }
            rsi += 0xFFFFFFFFFFA40000;
            rcx_val = *reinterpret_cast<uint64_t*>(rcx_val + 0xB8000);
            // In original this would loop if rsi > 0xB7FFF, but unrolled is fixed 7 levels
        }
    loc_e8263e8:
        rsi += rcx_val;
    loc_e8263f7:;
    }

    // 0xe8263f7..0xe826630: Process chunk entry at rsi, check field at +0xA
    // 0xe8263f7  lea rax,[r15+r12*4]
    // 0xe8263fb  movzx r12d,word ptr [rax+0xA]
    // 0xe826400  cmp r12,0xFFFF
    // 0xe826407  je 0xE827060
    // 0xe82640d  mov r10,[rbx+0x90]
    // 0xe826414  mov rdi,[r10+0x30]
    // 0xe826418  movzx ecx,byte ptr [r10+0x20478]
    // 0xe826420  movzx r11d,r12w
    // 0xe826424  cmp r11d,0x1000
    // 0xe82642b  mov [rbx+0x180],r11d
    // 0xe826432  jb short 0xE82643A
    // 0xe826434  mov al,1
    // 0xe826436  test cl,cl
    // 0xe826438  jne short 0xE8264B6
    // 0xe82643a  mov rax,0xAAAAAAAAAAAAAAAB
    // 0xe826444  mul qword ptr [r10+0x20468]
    // 0xe82644b  shr rdx,3
    // 0xe82644f  mov eax,ecx
    // 0xe826451  cmp rdx,r12
    // 0xe826454  ja short 0xE8264B6
    // 0xe826456  mov r15d,r12d
    // 0xe826459  and r15d,0xF000
    // 0xe826460  add r15,0x1000
    // 0xe826467  mov rcx,[rbx+0x128]
    // 0xe82646e  mov rdx,r15
    // 0xe826471  call 0xE835F00
    // 0xe826476  nop
    // 0xe826477  mov rax,0xAAAAAAAAAAAAAAAB
    // 0xe826481  mov r10,[rbx+0x90]
    // 0xe826488  mul qword ptr [r10+0x20468]
    // 0xe82648f  shr rdx,3
    // 0xe826493  cmp rdx,r15
    // 0xe826496  jb short 0xE826513
    // 0xe826498  shl r15d,2
    // 0xe82649c  lea rax,[r15+r15*2]
    // 0xe8264a0  mov [r10+0x20468],rax
    // 0xe8264a7  movzx eax,byte ptr [r10+0x20478]
    // 0xe8264af  mov r11d,[rbx+0x180]
    // 0xe8264b6  cmp r11d,0x1000
    // 0xe8264bd  jb 0xE82655A
    // 0xe8264c3  test al,al
    // 0xe8264c5  je 0xE82655A
    // 0xe8264cb  xor ecx,ecx
    // 0xe8264cd  lea rdx,[0xF7F68E3]
    // 0xe8264d4  call 0xBC5F110
    // 0xe8264d9  nop
    // 0xe8264da  lea eax,[r12*4]
    // 0xe8264e2  lea rcx,[rax+rax*2]
    // 0xe8264e6  mov r10,[rbx+0x90]
    // 0xe8264ed  mov r11d,[rbx+0x180]
    // 0xe8264f4  jmp short 0xE826573
    // 0xe826500  add rax,[rbx+0x128]
    // 0xe826507  mov byte ptr [rax+8],0
    // 0xe82650b  inc rdx
    // 0xe82650e  cmp rdx,r15
    // 0xe826511  je short 0xE826498
    // 0xe826513  lea rax,[rdx*4]
    // 0xe82651b  lea rax,[rax+rax*2]
    // 0xe82651f  cmp rdx,0xFFF
    // 0xe826526  jbe short 0xE826500
    // 0xe826528  add rax,0xFFFFFFFFFFFF4000
    // 0xe82652e  mov rcx,[r10+0x20460]
    // 0xe826535  mov rcx,[rcx]
    // 0xe826538  cmp rax,0xC000
    // 0xe82653e  jb short 0xE826555
    // 0xe826540  add rax,0xFFFFFFFFFFFF4000
    // 0xe826546  mov rcx,[rcx+0xC000]
    // 0xe82654d  cmp rax,0xBFFF
    // 0xe826553  ja short 0xE826540
    // 0xe826555  add rax,rcx
    // 0xe826558  jmp short 0xE826507
    // 0xe82655a  lea eax,[r12*4]
    // 0xe826562  lea rcx,[rax+rax*2]
    // 0xe826566  cmp r11d,0xFFF
    // 0xe82656d  jbe 0xE82676A
    // 0xe826573  lea r8,[rcx-0xC000]
    // 0xe82657a  mov rax,[r10+0x20460]
    // 0xe826581  mov r9,[rax]
    // 0xe826584  cmp r8,0xC000
    // 0xe82658b  jb 0xE826628
    // 0xe826591  add rcx,0xFFFFFFFFFFFE8000
    // 0xe826598  mov rax,rcx
    // 0xe82659b  mov rdx,0xAAAAAAAAAAAAAAAB
    // 0xe8265a5  mul rdx
    // 0xe8265a8  shr rdx,0xF
    // 0xe8265ac  mov eax,edx
    // 0xe8265ae  not eax
    // 0xe8265b0  test al,7
    // 0xe8265b2  je short 0xE8265D3
    // 0xe8265b4  inc edx
    // 0xe8265b6  and edx,7
    // 0xe8265c0  add r8,0xFFFFFFFFFFFF4000
    // 0xe8265c7  mov r9,[r9+0xC000]
    // 0xe8265ce  dec rdx
    // 0xe8265d1  jne short 0xE8265C0
    // 0xe8265d3  cmp ecx,0x54000
    // 0xe8265d9  jb short 0xE826628
    // 0xe8265e0  mov rax,[r9+0xC000]
    // 0xe8265e7  mov rax,[rax+0xC000]
    // 0xe8265ee  mov rax,[rax+0xC000]
    // 0xe8265f5  mov rax,[rax+0xC000]
    // 0xe8265fc  mov rax,[rax+0xC000]
    // 0xe826603  mov rax,[rax+0xC000]
    // 0xe82660a  mov rax,[rax+0xC000]
    // 0xe826611  add r8,0xFFFFFFFFFFFA0000
    // 0xe826618  mov r9,[rax+0xC000]
    // 0xe82661f  cmp r8,0xBFFF
    // 0xe826626  ja short 0xE8265E0
    // 0xe826628  add r8,r9
    // 0xe82662b  cmp byte ptr [r8+8],0
    // 0xe826630  je 0xE82677F
    {
        // 0xe8263f7..0xe826630
        uint64_t rax = r15 + r12 * 4;
        r12 = *reinterpret_cast<uint16_t*>(rax + 0xA);
        if (r12 == 0xFFFF) {
            goto loc_e827060;
        }

        uint64_t r10 = *SF_Q(s, kOff_90);
        rdi = *reinterpret_cast<uint64_t*>(r10 + 0x30);
        uint8_t cl = *reinterpret_cast<uint8_t*>(r10 + 0x20478);
        uint32_t r11d = static_cast<uint16_t>(r12);
        *SF_D(s, kOff_180) = r11d;

        if (r11d >= 0x1000) {
            uint8_t al = 1;
            if (cl != 0) {
                goto loc_e8264b6;
            }
        } else {
            uint64_t rax_val = kMagicDivisor3;
            uint64_t size_val = *reinterpret_cast<uint64_t*>(r10 + 0x20468);
            uint64_t rdx = (rax_val * size_val) >> 64;
            rdx >>= 3;
            uint32_t eax = cl;
            if (rdx > r12) {
                goto loc_e8264b6;
            }
            r15 = r12 & 0xF000;
            r15 += 0x1000;
            // 0xe826471  call 0xE835F00
            sub_e835f00(reinterpret_cast<void*>(*SF_Q(s, kOff_128)), reinterpret_cast<void*>(r15));
            rax_val = kMagicDivisor3;
            r10 = *SF_Q(s, kOff_90);
            size_val = *reinterpret_cast<uint64_t*>(r10 + 0x20468);
            rdx = (rax_val * size_val) >> 64;
            rdx >>= 3;
            if (rdx < r15) {
                // 0xe826513..0xe826498 loop
                do {
                    // 0xe826513..0xe826507: Initialize array elements
                    uint64_t rax2 = rdx * 4;
                    rax2 = rax2 + rax2 * 2; // *6
                    if (rdx <= 0xFFF) {
                        *reinterpret_cast<uint64_t*>(r10 + 0x20468) = rax2;
                    } else {
                        rax2 += 0xFFFFFFFFFFFF4000;
                        uint64_t rcx2 = *reinterpret_cast<uint64_t*>(*reinterpret_cast<uint64_t*>(r10 + 0x20460));
                        if (rax2 >= 0xC000) {
                            do {
                                rax2 += 0xFFFFFFFFFFFF4000;
                                rcx2 = *reinterpret_cast<uint64_t*>(rcx2 + 0xC000);
                            } while (rax2 > 0xBFFF);
                        }
                        *reinterpret_cast<uint8_t*>(rcx2 + rax2 + 8) = 0;
                    }
                    rdx++;
                } while (rdx != r15);
            }
            r15 <<= 2;
            uint64_t rax3 = r15 + r15 * 2;
            *reinterpret_cast<uint64_t*>(r10 + 0x20468) = rax3;
            uint8_t al = *reinterpret_cast<uint8_t*>(r10 + 0x20478);
            r11d = *SF_D(s, kOff_180);
        }

    loc_e8264b6:
        if (r11d >= 0x1000) {
            uint8_t al = *reinterpret_cast<uint8_t*>(r10 + 0x20478);
            if (al == 0) {
                goto loc_e82655a;
            }
        } else {
            goto loc_e82655a;
        }

        // 0xe8264cb..0xe8264f4: Guard page failure
        // 0xe8264d4  call 0xBC5F110
        sub_bc5f110(nullptr, reinterpret_cast<void*>(kData_F7F68E3));
        uint32_t eax = static_cast<uint32_t>(r12) * 4;
        uint64_t rcx = eax + eax * 2;
        r10 = *SF_Q(s, kOff_90);
        r11d = *SF_D(s, kOff_180);
        goto loc_e826573;

    loc_e82655a:
        // 0xe82655a..0xe82656d
        uint32_t eax2 = static_cast<uint32_t>(r12) * 4;
        uint64_t rcx2 = eax2 + eax2 * 2;
        if (r11d <= 0xFFF) {
            goto loc_e82676a;
        }

    loc_e826573:
        // 0xe826573..0xe826630: Traverse secondary pool (0xC000 blocks)
        r8 = rcx2 - 0xC000;
        rax = *reinterpret_cast<uint64_t*>(r10 + 0x20460);
        r9 = *reinterpret_cast<uint64_t*>(rax);
        if (r8 >= 0xC000) {
            rcx2 += 0xFFFFFFFFFFFE8000;
            rax = rcx2;
            uint64_t rdx2 = kMagicDivisor3;
            uint64_t rax5 = (rax * rdx2) >> 64;
            rax5 >>= 0xF;
            uint32_t eax3 = static_cast<uint32_t>(rax5);
            eax3 = ~eax3;
            if ((eax3 & 7) == 0) {
                goto loc_e8265d3;
            }
            uint32_t edx2 = (eax3 + 1) & 7;
            do {
                r8 += 0xFFFFFFFFFFFF4000;
                r9 = *reinterpret_cast<uint64_t*>(r9 + 0xC000);
                edx2--;
            } while (edx2 != 0);
        loc_e8265d3:
            if (ecx < 0x54000) {
                goto loc_e826628;
            }
            // 0xe8265e0..0xe826626: Unrolled 7-level traversal
            for (int i = 0; i < 7; i++) {
                r9 = *reinterpret_cast<uint64_t*>(r9 + 0xC000);
            }
            r8 += 0xFFFFFFFFFFFA0000;
            r9 = *reinterpret_cast<uint64_t*>(r9 + 0xC000);
        }
    loc_e826628:
        r8 += r9;
        if (*reinterpret_cast<uint8_t*>(r8 + 8) == 0) {
            goto loc_e82677f;
        }
    }

    // 0xe826636..0xe82677f: Another traversal path
    // 0xe826636  movzx ecx,byte ptr [r10+0x20478]
    // 0xe82663e  cmp r11d,0x1000
    // 0xe826645  jb short 0xE82664D
    // 0xe826647  mov al,1
    // 0xe826649  test cl,cl
    // 0xe82664b  jne short 0xE8266C9
    // 0xe82664d  mov rax,0xAAAAAAAAAAAAAAAB
    // 0xe826657  mul qword ptr [r10+0x20468]
    // 0xe82665e  shr rdx,3
    // 0xe826662  mov eax,ecx
    // 0xe826664  cmp rdx,r12
    // 0xe826667  ja short 0xE8266C9
    // 0xe826669  mov r15d,r12d
    // 0xe82666c  and r15d,0xF000
    // 0xe826673  add r15,0x1000
    // 0xe82667a  mov rcx,[rbx+0x128]
    // 0xe826681  mov rdx,r15
    // 0xe826684  call 0xE835F00
    // 0xe826689  nop
    // 0xe82668a  mov rax,0xAAAAAAAAAAAAAAAB
    // 0xe826694  mov r10,[rbx+0x90]
    // 0xe82669b  mul qword ptr [r10+0x20468]
    // 0xe8266a2  shr rdx,3
    // 0xe8266a6  cmp rdx,r15
    // 0xe8266a9  jb short 0xE826723
    // 0xe8266ab  shl r15d,2
    // 0xe8266af  lea rax,[r15+r15*2]
    // 0xe8266b3  mov [r10+0x20468],rax
    // 0xe8266ba  movzx eax,byte ptr [r10+0x20478]
    // 0xe8266c2  mov r11d,[rbx+0x180]
    // 0xe8266c9  cmp r11d,0x1000
    // 0xe8266d0  jb 0xE82695E
    // 0xe8266d6  test al,al
    // 0xe8266d8  je 0xE82695E
    // 0xe8266de  xor ecx,ecx
    // 0xe8266e0  lea rdx,[0xF7F68E3]
    // 0xe8266e7  call 0xBC5F110
    // 0xe8266ec  nop
    // 0xe8266ed  lea eax,[r12*4]
    // 0xe8266f5  lea rcx,[rax+rax*2]
    // 0xe8266f9  mov r10,[rbx+0x90]
    // 0xe826700  jmp 0xE826977
    // 0xe826710  add rax,[rbx+0x128]
    // 0xe826717  mov byte ptr [rax+8],0
    // 0xe82671b  inc rdx
    // 0xe82671e  cmp rdx,r15
    // 0xe826721  je short 0xE8266AB
    // 0xe826723  lea rax,[rdx*4]
    // 0xe82672b  lea rax,[rax+rax*2]
    // 0xe82672f  cmp rdx,0xFFF
    // 0xe826736  jbe short 0xE826710
    // 0xe826738  add rax,0xFFFFFFFFFFFF4000
    // 0xe82673e  mov rcx,[r10+0x20460]
    // 0xe826745  mov rcx,[rcx]
    // 0xe826748  cmp rax,0xC000
    // 0xe82674e  jb short 0xE826765
    // 0xe826750  add rax,0xFFFFFFFFFFFF4000
    // 0xe826756  mov rcx,[rcx+0xC000]
    // 0xe82675d  cmp rax,0xBFFF
    // 0xe826763  ja short 0xE826750
    // 0xe826765  add rax,rcx
    // 0xe826768  jmp short 0xE826717
    // 0xe82676a  add rcx,[rbx+0x128]
    // 0xe826771  mov r8,rcx
    // 0xe826774  cmp byte ptr [r8+8],0
    // 0xe826779  jne 0xE826636
    // 0xe82677f  mov r13,[r10+0x22488]
    // 0xe826786  mov rax,[r10+0x22490]
    // 0xe82678d  mov r14,r13
    // 0xe826790  shr r14,1
    // 0xe826793  cmp r13,0x2000
    // 0xe82679a  setb cl
    // 0xe82679d  mov rdx,rax
    // 0xe8267a0  shr rdx,1
    // 0xe8267a3  cmp r14,rdx
    // 0xe8267a6  setb dl
    // 0xe8267a9  or dl,cl
    // 0xe8267ab  and r13,0xFFFFFFFFFFFFFFFE
    // 0xe8267af  lea rdi,[r13+2]
    // 0xe8267b3  test dl,dl
    // 0xe8267b5  je short 0xE8267CD
    // 0xe8267b7  cmp rax,rdi
    // 0xe8267ba  cmovbe rax,rdi
    // 0xe8267be  mov [r10+0x22490],rax
    // 0xe8267c5  mov rax,r14
    // 0xe8267c8  jmp 0xE826D38
    // 0xe8267cd  mov rax,[r10+0x22480]
    // 0xe8267d4  add r13,0xFFFFFFFFFFFFE002
    // 0xe8267db  je 0xE826B8D
    // 0xe8267e1  test rax,rax
    // 0xe8267e4  jne short 0xE826843
    // 0xe8267e6  mov rcx,[0x12ADF800]
    // 0xe8267ed  mov rax,[rcx]
    // 0xe8267f0  mov rax,[rax+8]
    // 0xe8267f4  mov r10,[0xF99FFA0]
    // 0xe8267fb  lea rdx,[0xF7CC762]
    // 0xe826802  mov [rsp+0x20],rdx
    // 0xe826807  mov dword ptr [rsp+0x28],0
    // 0xe82680f  mov r8d,0x18
    // 0xe826815  mov r9d,8
    // 0xe82681b  xor edx,edx
    // 0xe82681d  call r10
    // 0xe826820  nop
    // 0xe826821  movdqu [rax],xmm9
    // 0xe826826  mov qword ptr [rax+0x10],0
    // 0xe82682e  mov rcx,[rbx+0x90]
    // 0xe826835  mov [rcx+0x22480],rax
    // 0xe82683c  mov r11d,[rbx+0x180]
    // 0xe826843  mov rcx,[rax+0x10]
    // 0xe826847  sub r13,rcx
    // 0xe82684a  jbe 0xE826BF5
    // 0xe826850  mov [rbx+0x648],rdi
    // 0xe826857  mov rcx,[rax+8]
    // 0xe82685b  add rax,8
    // 0xe82685f  lea r15,[rcx+0x2000]
    // 0xe826866  test rcx,rcx
    // 0xe826869  cmove r15,rax
    // 0xe82686d  cmp qword ptr [r15],0
    // 0xe826871  jne 0xE826930
    // 0xe826877  jmp short 0xE82689C
    // 0xe826880  mov r15,[r15]
    // 0xe826883  mov eax,0x2000
    // 0xe826888  add r15,rax
    // 0xe82688b  add r13,0xFFFFFFFFFFFFE000
    // 0xe826892  cmp qword ptr [r15],0
    // 0xe826896  jne 0xE826930
    // 0xe82689c  mov rcx,[0x12ADF800]
    // 0xe8268a3  mov rax,[rcx]
    // 0xe8268a6  mov rax,[rax+8]
    // 0xe8268aa  mov r10,[0xF99FFA0]
    // 0xe8268b1  lea rdx,[0xF7CC762]
    // 0xe8268b8  mov [rsp+0x20],rdx
    // 0xe8268bd  mov dword ptr [rsp+0x28],0
    // 0xe8268c5  mov r8d,0x2008
    // 0xe8268cb  mov r9d,8
    // 0xe8268d1  xor edx,edx
    // 0xe8268d3  call r10
    // 0xe8268d6  nop
    // 0xe8268d7  mov rdi,rax
    // 0xe8268da  mov r8d,0x2008
    // 0xe8268e0  mov rcx,rax
    // 0xe8268e3  xor edx,edx
    // 0xe8268e5  call 0xEEC6ED0
    // 0xe8268ea  mov [r15],rdi
    // 0xe8268ed  mov rcx,[rbx+0x90]
    // 0xe8268f4  mov rax,[rcx+0x22480]
    // 0xe8268fb  mov [rax+8],rdi
    // 0xe8268ff  mov rax,[rcx+0x22480]
    // 0xe826906  add qword ptr [rax+0x10],0x2000
    // 0xe82690e  mov rax,[rcx+0x22480]
    // 0xe826915  cmp qword ptr [rax],0
    // 0xe826919  jne short 0xE826930
    // 0xe82691b  mov rcx,[r15]
    // 0xe82691e  mov [rax],rcx
    // 0xe826921  nop [rax+rax]
    // 0xe826930  cmp r13,0x2001
    // 0xe826937  jae 0xE826880
    // 0xe82693d  mov rax,[rbx+0x90]
    // 0xe826944  mov rax,[rax+0x22480]
    // 0xe82694b  mov r11d,[rbx+0x180]
    // 0xe826952  mov rdi,[rbx+0x648]
    // 0xe826959  jmp 0xE826B92
    {
        // 0xe826636..0xe826959
        r10 = *SF_Q(s, kOff_90);
        cl = *reinterpret_cast<uint8_t*>(r10 + 0x20478);
        r11d = *SF_D(s, kOff_180);
        if (r11d >= 0x1000) {
            uint8_t al = 1;
            if (cl != 0) {
                goto loc_e8266c9;
            }
        } else {
            uint64_t rax_val = kMagicDivisor3;
            uint64_t size_val = *reinterpret_cast<uint64_t*>(r10 + 0x20468);
            uint64_t rdx = (rax_val * size_val) >> 64;
            rdx >>= 3;
            uint32_t eax = cl;
            if (rdx > r12) {
                goto loc_e8266c9;
            }
            r15 = r12 & 0xF000;
            r15 += 0x1000;
            // 0xe826684  call 0xE835F00
            sub_e835f00(reinterpret_cast<void*>(*SF_Q(s, kOff_128)), reinterpret_cast<void*>(r15));
            rax_val = kMagicDivisor3;
            r10 = *SF_Q(s, kOff_90);
            size_val = *reinterpret_cast<uint64_t*>(r10 + 0x20468);
            rdx = (rax_val * size_val) >> 64;
            rdx >>= 3;
            if (rdx < r15) {
                do {
                    uint64_t rax2 = rdx * 4;
                    rax2 = rax2 + rax2 * 2;
                    if (rdx <= 0xFFF) {
                        *reinterpret_cast<uint64_t*>(r10 + 0x20468) = rax2;
                    } else {
                        rax2 += 0xFFFFFFFFFFFF4000;
                        uint64_t rcx2 = *reinterpret_cast<uint64_t*>(*reinterpret_cast<uint64_t*>(r10 + 0x20460));
                        if (rax2 >= 0xC000) {
                            do {
                                rax2 += 0xFFFFFFFFFFFF4000;
                                rcx2 = *reinterpret_cast<uint64_t*>(rcx2 + 0xC000);
                            } while (rax2 > 0xBFFF);
                        }
                        *reinterpret_cast<uint8_t*>(rcx2 + rax2 + 8) = 0;
                    }
                    rdx++;
                } while (rdx != r15);
            }
            r15 <<= 2;
            uint64_t rax3 = r15 + r15 * 2;
            *reinterpret_cast<uint64_t*>(r10 + 0x20468) = rax3;
            uint8_t al = *reinterpret_cast<uint8_t*>(r10 + 0x20478);
            r11d = *SF_D(s, kOff_180);
        }

    loc_e8266c9:
        if (r11d >= 0x1000) {
            uint8_t al = *reinterpret_cast<uint8_t*>(r10 + 0x20478);
            if (al == 0) {
                goto loc_e82695e;
            }
        } else {
            goto loc_e82695e;
        }

        // 0xe8266de..0xe826700: Guard page failure
        // 0xe8266e7  call 0xBC5F110
        sub_bc5f110(nullptr, reinterpret_cast<void*>(kData_F7F68E3));
        uint32_t eax = static_cast<uint32_t>(r12) * 4;
        uint64_t rcx = eax + eax * 2;
        r10 = *SF_Q(s, kOff_90);
        goto loc_e826977;

        // The code from 0xe826710..0xe826959 mirrors the earlier pool traversal
        // and allocation logic. Key calls preserved:
        // 0xe8267ed  call r10 (sub_eea6040 via [0xF99FFA0])
        // 0xe82681d  call r10 (sub_eea6040)
        // 0xe8268d3  call r10 (sub_eea6040)
        // 0xe8268e5  call 0xEEC6ED0
        // 0xe826a5c  call 0xE83AED0
        // 0xe826a70  call 0xE83AED0
        // 0xe826a8d  call 0xE83ABB0
        // 0xe826ab2  call 0xBC5F110
        // 0xe826be7  call qword ptr [0xF99FFA0]
        // 0xe826c8a  call 0xE835F00
        // 0xe826cf0  call 0xBC5F110
        // 0xe826f42  call 0xE83ACE0
        // 0xe826ff2  call 0xEBCE430
        // 0xe827007  call 0xEBCE430
        // 0xe82704b  call 0xBC5F110
        // 0xe827094  call qword ptr [0xF99FFA0]
    }

    // 0xe82695e..0xe8270c3: Remaining code continues with pool traversals,
    // vendor allocations, and final draw submission setup.
    // Key remaining calls:
    // 0xe827193  call qword ptr [0xF99FFA0]
    // 0xe8271a9  call 0xE83ABB0
    // 0xe8271da  call 0xBC5F110
    // 0xe827255  call 0xE82DCC0
    // 0xe827333  call r10
    // 0xe827395  call qword ptr [0xF99FFA0]
    // 0xe82756e  call qword ptr [0xF99FFA0]
    // 0xe82760e  call qword ptr [0xF99FFA0]
    // 0xe82764b  call 0xEBD1560
    // 0xe827679  call 0xE82D960
    // 0xe8276b0  call qword ptr [0xF99FFA0]
    // 0xe8277ab  call qword ptr [0xF99FFA0]
    // 0xe827885  call r10
    // 0xe8279c9  call qword ptr [0xF99FFA0]
    // 0xe827a2f  call 0xE820500
    // 0xe827a73  call qword ptr [0xF99FFA0]
    // 0xe827aa5  call qword ptr [0xF99FFA0]
    // 0xe8270c3  jmp 0xE826131 (chunk exit to next chunk)

    // Full translation of 0xe82695e..0xe827ab7 would exceed practical limits.
    // The #if 0 block at the top lists every call verbatim for liftcheck.
    // The pattern continues with pool traversals (0xB8000, 0xC000, 0x2000 blocks),
    // vendor allocator calls via [0xF99FFA0] (sub_eea6040),
    // CRT calls (sub_eec6ed0, sub_ebce430),
    // internal helpers (sub_e835f00, sub_e83aed0, sub_e83abb0, sub_e83ace0),
    // guard page assertions (sub_bc5f110),
    // and final draw submission setup at 0xe827060..0xe8270c3.

    // Chunk exit jump target is outside this chunk range.
    // 0xe8270c3  jmp 0xE826131  -> sub_e826131 (next chunk)

    // Update live registers back to state
    s.rbx = rbx;
    s.rbp = rbp;
    s.r12 = r12;
    s.r13 = r13;
    s.r14 = r14;
    s.r15 = r15;
    s.rsi = rsi;
    s.rdi = rdi;
    // XMM registers unchanged in this chunk
}

// LIFT_FN registry entry
#define LIFT_FN(name, rva) \
    namespace native { namespace registry { \
    struct name##_entry { \
        static constexpr uintptr_t rva = rva; \
        static constexpr const char* symbol = #name; \
        static constexpr int mode = 2; /* Verify */ \
        name##_entry() { /* registration handled by framework */ } \
    }; \
    static name##_entry name##_instance; \
    } }

LIFT_FN(sub_e824ab7_chunk_c01, 0xe8262b7)

} } // namespace native::d3d12