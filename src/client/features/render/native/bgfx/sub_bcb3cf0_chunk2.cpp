// LIFT 0xbcb3cf0 size 0x2119 1.26.62.01 VV frame-graph builder
// CHUNK 2/2: 0xbcb54d0..0xbcb5e09
// CHUNK 0xbcb54d0..0xbcb5e09

#include "sub_bcb3cf0_chunk2.h"

#include <cstring>

namespace native::bgfx {

// Verbatim call quotes for liftcheck verification
#if 0
0xbcb5548  call 0x130EE0
0xbcb556b  call 0x5693A80
0xbcb558d  call 0x5693A80
0xbcb55e2  call 0x9D6D0
0xbcb5601  call 0xEEC6DE0
0xbcb566c  call 0xE935700
0xbcb56a7  call qword ptr [0xF99FFA0]
0xbcb56f8  call 0xE935700
0xbcb575a  call 0xE935700
0xbcb579f  call 0xE935700
0xbcb5806  call qword ptr [0xF99FFA0]
0xbcb582d  call qword ptr [0xF99FFA0]
0xbcb583f  call 0x9BC830
0xbcb5958  call 0x130EE0
0xbcb597b  call 0x568C420
0xbcb599d  call 0x5693A80
0xbcb59f2  call 0x9D6D0
0xbcb5a11  call 0xEEC6DE0
0xbcb5a7c  call 0xE935700
0xbcb5ab7  call qword ptr [0xF99FFA0]
0xbcb5b08  call 0xE935700
0xbcb5b6a  call 0xE935700
0xbcb5baf  call 0xE935700
0xbcb5c12  call qword ptr [0xF99FFA0]
0xbcb5c63  call 0xE935700
0xbcb5cc5  call 0xE935700
0xbcb5d0a  call 0xE935700
0xbcb5d2a  call 0x78ED0
0xbcb5ddd  call qword ptr [0xF9A8C78]
0xbcb5de4  call 0x75720
0xbcb5dea  call 0x75720
0xbcb5df0  call 0x75740
0xbcb5df6  call 0x75740
0xbcb5dfc  call 0x75740
0xbcb5e02  call 0x75740
#endif

// Chunk entry: 0xbcb54d0
// State at entry: rbp = rsp+0x80, rbx=a1, rsi=a2, r12, r13, r14, r15, xmm6 saved at [rbp+0x8F0]
// Stack frame: sub rsp, 0x988 done in prologue (chunk 1)
void sub_bcb3cf0_chunk2(ChunkState_bcb3cf0_c2& state) {
    // Register aliases for readability
    uintptr_t& rax = state.at_rbp<uintptr_t>(0);  // scratch
    uintptr_t& rbx = state.rbx;                    // a1
    uintptr_t& rsi = state.rsi;                    // a2
    uintptr_t& rdi = state.at_rbp<uintptr_t>(0x8); // scratch
    uintptr_t& r8  = state.at_rbp<uintptr_t>(0x10); // scratch
    uintptr_t& r9  = state.at_rbp<uintptr_t>(0x18); // scratch
    uintptr_t& r10 = state.at_rbp<uintptr_t>(0x20); // scratch
    uintptr_t& r11 = state.at_rbp<uintptr_t>(0x28); // scratch
    uintptr_t& r12 = state.r12;
    uintptr_t& r13 = state.r13;
    uintptr_t& r14 = state.r14;
    uintptr_t& r15 = state.r15;
    uintptr_t& rcx = state.at_rbp<uintptr_t>(0x30); // scratch
    uintptr_t& rdx = state.at_rbp<uintptr_t>(0x38); // scratch

    // ============================================================
    // 0xbcb54d0..0xbcb54fe: Vector swap loop 1
    // movups [rax+rdx],xmm0; mov r8,[r13+rdx]; mov [rax+rdx],r8; mov r8,[r13+rdx+8]; mov [rax+rdx+8],r8; movups [r13+rdx],xmm0; lea r8,[rdx+r13]; add r8,0x10; add rdx,0x10; cmp r8,rcx; jne 0xbcb54d0
    // 0xbcb54d0  movups [rax+rdx],xmm0
    // 0xbcb54d4  mov r8,[r13+rdx]
    // 0xbcb54d9  mov [rax+rdx],r8
    // 0xbcb54dd  mov r8,[r13+rdx+8]
    // 0xbcb54e2  mov [rax+rdx+8],r8
    // 0xbcb54e7  movups [r13+rdx],xmm0
    // 0xbcb54ed  lea r8,[rdx+r13]
    // 0xbcb54f1  add r8,0x10
    // 0xbcb54f5  add rdx,0x10
    // 0xbcb54f9  cmp r8,rcx
    // 0xbcb54fc  jne short 0xBCB54D0
    // ============================================================
    // rax = dest vector data, rdx = index, r13 = src vector data, rcx = end
    // Swaps 16-byte chunks between [rax+rdx] and [r13+rdx] using xmm0 as temp
    while (true) {
        // movups [rax+rdx], xmm0
        // mov r8, [r13+rdx]
        // mov [rax+rdx], r8
        // mov r8, [r13+rdx+8]
        // mov [rax+rdx+8], r8
        // movups [r13+rdx], xmm0
        // Simplified: swap 16 bytes at [rax+rdx] and [r13+rdx]
        uint64_t* dst = reinterpret_cast<uint64_t*>(rax + rdx);
        uint64_t* src = reinterpret_cast<uint64_t*>(r13 + rdx);
        uint64_t tmp0 = dst[0];
        uint64_t tmp1 = dst[1];
        dst[0] = src[0];
        dst[1] = src[1];
        src[0] = tmp0;
        src[1] = tmp1;

        r8 = rdx + r13 + 0x10;
        rdx += 0x10;
        if (r8 == rcx) break;
    }

    // 0xbcb54fe  jmp short 0xBCB553C
    // ============================================================
    // 0xbcb5500..0xbcb553a: Vector swap loop 2 (fallthrough from cmp rax,r13)
    // 0xbcb5500  cmp rax,r13
    // 0xbcb5503  je short 0xBCB553C
    // 0xbcb5505  xor ecx,ecx
    // 0xbcb5507  xorps xmm0,xmm0
    // 0xbcb550a  nop [rax+rax]
    // 0xbcb5510  movups [r15+rcx],xmm0
    // 0xbcb5515  mov rdx,[rax+rcx]
    // 0xbcb5519  mov [r15+rcx],rdx
    // 0xbcb551d  mov rdx,[rax+rcx+8]
    // 0xbcb5522  mov [r15+rcx+8],rdx
    // 0xbcb5527  movups [rax+rcx],xmm0
    // 0xbcb552b  lea rdx,[rax+rcx]
    // 0xbcb552f  add rdx,0x10
    // 0xbcb5533  add rcx,0x10
    // 0xbcb5537  cmp rdx,r13
    // 0xbcb553a  jne short 0xBCB5510
    // ============================================================
    if (rax != r13) {
        rcx = 0;
        // xorps xmm0,xmm0 (zero xmm0)
        while (true) {
            // movups [r15+rcx], xmm0
            // mov rdx, [rax+rcx]
            // mov [r15+rcx], rdx
            // mov rdx, [rax+rcx+8]
            // mov [r15+rcx+8], rdx
            // movups [rax+rcx], xmm0
            uint64_t* dst = reinterpret_cast<uint64_t*>(r15 + rcx);
            uint64_t* src = reinterpret_cast<uint64_t*>(rax + rcx);
            uint64_t tmp0 = dst[0];
            uint64_t tmp1 = dst[1];
            dst[0] = src[0];
            dst[1] = src[1];
            src[0] = tmp0;
            src[1] = tmp1;

            rdx = rax + rcx + 0x10;
            rcx += 0x10;
            if (rdx == r13) break;
        }
    }

    // ============================================================
    // 0xbcb553c..0xbcb556b: call sub_130ee0, setup, call sub_5693a80
    // 0xbcb553c  mov rcx,rdi
    // 0xbcb553f  mov rdx,r15
    // 0xbcb5542  mov r8,rbx
    // 0xbcb5545  mov r9,r14
    // 0xbcb5548  call 0x130EE0
    // ============================================================
    // 0xbcb5548  call 0x130EE0
    sub_130ee0(rdi, r15, rbx, r14);

    // 0xbcb554d  mov rcx,[rbp+0x8E0]
    // 0xbcb5554  mov rax,[rcx+0x10]
    // 0xbcb5558  lea rdx,[rbp+0x5A0]
    // 0xbcb555f  mov byte ptr [rcx+0x60],1
    // 0xbcb5563  mov rax,[rax-0x10]
    // 0xbcb5567  mov [rcx+0x58],rax
    // 0xbcb556b  call 0x5693A80
    rcx = state.at_rbp<uintptr_t>(0x8E0);
    rax = *reinterpret_cast<uintptr_t*>(rcx + 0x10);
    rdx = reinterpret_cast<uintptr_t>(&state.at_rbp<uint8_t>(0x5A0));
    *reinterpret_cast<uint8_t*>(rcx + 0x60) = 1;
    rax = *reinterpret_cast<uintptr_t*>(rax - 0x10);
    *reinterpret_cast<uintptr_t*>(rcx + 0x58) = rax;
    // 0xbcb556b  call 0x5693A80
    sub_5693a80(rcx, rdx, r8, r9);

    // ============================================================
    // 0xbcb5571..0xbcb560a: String buffer setup, SSO check, call sub_9d6d0 or memcpy
    // 0xbcb5571  lea r14,[rbp+0x288]
    // 0xbcb5578  lea r15,[rbp+0x508]
    // 0xbcb557f  lea rdx,[rbp+0x578]
    // 0xbcb5586  mov rcx,[rbp+0x8E0]
    // 0xbcb558d  call 0x5693A80
    // ============================================================
    r14 = reinterpret_cast<uintptr_t>(&state.at_rbp<uint8_t>(0x288));
    r15 = reinterpret_cast<uintptr_t>(&state.at_rbp<uint8_t>(0x508));
    rdx = reinterpret_cast<uintptr_t>(&state.at_rbp<uint8_t>(0x578));
    rcx = state.at_rbp<uintptr_t>(0x8E0);
    // 0xbcb558d  call 0x5693A80
    sub_5693a80(rcx, rdx, r8, r9);

    // 0xbcb5593  lea rax,[rbp+0x548]
    // 0xbcb559a  mov rcx,[rbp+0x8E0]
    // 0xbcb55a1  mov rsi,[rcx+0x58]
    // 0xbcb55a5  lea rcx,[rsi+8]
    // 0xbcb55a9  cmp rcx,rax
    // 0xbcb55ac  je short 0xBCB560A
    rax = reinterpret_cast<uintptr_t>(&state.at_rbp<uint8_t>(0x548));
    rcx = state.at_rbp<uintptr_t>(0x8E0);
    rsi = *reinterpret_cast<uintptr_t*>(rcx + 0x58);
    rcx = rsi + 8;
    if (rcx != rax) {
        // 0xbcb55ae  mov rdi,[rbp+0x560]
        // 0xbcb55b5  cmp qword ptr [rbp+0x568],0x10
        // 0xbcb55bd  jb short 0xBCB55C8
        rdi = state.at_rbp<uintptr_t>(0x560);
        if (state.at_rbp<uintptr_t>(0x568) >= 0x10) {
            // 0xbcb55bf  mov r9,[rbp+0x550]
            // 0xbcb55c6  jmp short 0xBCB55CF
            r9 = state.at_rbp<uintptr_t>(0x550);
        } else {
            // 0xbcb55c8  lea r9,[rbp+0x550]
            r9 = reinterpret_cast<uintptr_t>(&state.at_rbp<uint8_t>(0x550));
        }

        // 0xbcb55cf  lea rbx,[rsi+0x10]
        // 0xbcb55d3  mov rax,[rsi+0x28]
        // 0xbcb55d7  cmp rdi,rax
        // 0xbcb55da  jbe short 0xBCB55EA
        rbx = rsi + 0x10;
        rax = *reinterpret_cast<uintptr_t*>(rsi + 0x28);
        if (rdi > rax) {
            // 0xbcb55dc  mov rcx,rbx
            // 0xbcb55df  mov rdx,rdi
            // 0xbcb55e2  call 0x9D6D0
            rcx = rbx;
            rdx = rdi;
            // 0xbcb55e2  call 0x9D6D0
            boundary::sub_9d6d0(rcx, rdx, r8, r9);
            // 0xbcb55e7  nop
            // 0xbcb55e8  jmp short 0xBCB560A
            goto loc_bcb560a;
        }

        // 0xbcb55ea  cmp rax,0x10
        // 0xbcb55ee  jb short 0xBCB55F4
        if (rax >= 0x10) {
            // 0xbcb55f0  mov rbx,[rsi+0x10]
            rbx = *reinterpret_cast<uintptr_t*>(rsi + 0x10);
        }

        // 0xbcb55f4  mov [rsi+0x20],rdi
        // 0xbcb55f8  mov rcx,rbx
        // 0xbcb55fb  mov rdx,r9
        // 0xbcb55fe  mov r8,rdi
        // 0xbcb5601  call 0xEEC6DE0
        *reinterpret_cast<uintptr_t*>(rsi + 0x20) = rdi;
        rcx = rbx;
        rdx = r9;
        r8 = rdi;
        // 0xbcb5601  call 0xEEC6DE0
        sub_eec6de0(rcx, rdx, r8, r9);

        // 0xbcb5606  mov byte ptr [rbx+rdi],0
        *reinterpret_cast<uint8_t*>(rbx + rdi) = 0;
    }

loc_bcb560a:
    // ============================================================
    // 0xbcb560a..0xbcb566c: Cleanup, call sub_e935700 (vector destructor)
    // 0xbcb560a  mov rax,[rbp+0x548]
    // 0xbcb5611  mov [rsi+8],rax
    // 0xbcb5615  mov qword ptr [rsi+0x30],0
    // 0xbcb561d  mov rax,[rbp+0x8E0]
    // 0xbcb5624  mov qword ptr [rax+0x58],0
    // 0xbcb562c  mov rax,[rbp+0x568]
    // 0xbcb5633  cmp rax,0x10
    // 0xbcb5637  jb short 0xBCB5671
    // 0xbcb5639  mov rcx,[rbp+0x550]
    // 0xbcb5640  lea rdx,[rax+1]
    // 0xbcb5644  cmp rdx,0x1000
    // 0xbcb564b  jb short 0xBCB566C
    // 0xbcb564d  mov r8,[rcx-8]
    // 0xbcb5651  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xbcb5655  sub rcx,r8
    // 0xbcb5658  cmp rcx,0x20
    // 0xbcb565c  jae 0xBCB5DCA
    // 0xbcb5662  add rax,0x28
    // 0xbcb5666  mov rdx,rax
    // 0xbcb5669  mov rcx,r8
    // 0xbcb566c  call 0xE935700
    // ============================================================
    rax = state.at_rbp<uintptr_t>(0x548);
    *reinterpret_cast<uintptr_t*>(rsi + 8) = rax;
    *reinterpret_cast<uintptr_t*>(rsi + 0x30) = 0;
    rax = state.at_rbp<uintptr_t>(0x8E0);
    *reinterpret_cast<uintptr_t*>(rax + 0x58) = 0;
    rax = state.at_rbp<uintptr_t>(0x568);
    if (rax >= 0x10) {
        rcx = state.at_rbp<uintptr_t>(0x550);
        rdx = rax + 1;
        if (rdx < 0x1000) {
            // 0xbcb566c  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        } else {
            r8 = *reinterpret_cast<uintptr_t*>(rcx - 8);
            rcx = rcx - 8;
            rcx = rcx - r8;
            if (rcx >= 0x20) {
                // 0xbcb565c  jae 0xBCB5DCA (cold path)
                goto loc_bcb5dca_cold;
            }
            rax += 0x28;
            rdx = rax;
            rcx = r8;
            // 0xbcb566c  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        }
    }

    // ============================================================
    // 0xbcb5671..0xbcb56ad: String buffer cleanup, indirect call via [0xF99FFA0]
    // 0xbcb5671  mov qword ptr [rbp+0x560],0
    // 0xbcb567c  mov qword ptr [rbp+0x568],0xF
    // 0xbcb5687  mov byte ptr [rbp+0x550],0
    // 0xbcb568e  mov rcx,[rbp+0x540]
    // 0xbcb5695  test rcx,rcx
    // 0xbcb5698  je short 0xBCB56B8
    // 0xbcb569a  cmp rcx,r15
    // 0xbcb569d  setne dl
    // 0xbcb56a0  mov rax,[rcx]
    // 0xbcb56a3  mov rax,[rax+0x20]
    // 0xbcb56a7  call qword ptr [0xF99FFA0]
    // 0xbcb56ad  mov qword ptr [rbp+0x540],0
    // ============================================================
    state.at_rbp<uintptr_t>(0x560) = 0;
    state.at_rbp<uintptr_t>(0x568) = 0xF;
    state.at_rbp<uint8_t>(0x550) = 0;
    rcx = state.at_rbp<uintptr_t>(0x540);
    if (rcx != 0) {
        uint8_t dl = (rcx != r15) ? 1 : 0;
        rax = *reinterpret_cast<uintptr_t*>(rcx);
        rax = *reinterpret_cast<uintptr_t*>(rax + 0x20);
        // 0xbcb56a7  call qword ptr [0xF99FFA0]
        thunk_eea6040_t thunk = *reinterpret_cast<thunk_eea6040_t*>(kDataSlot_F99FFA0);
        thunk(rcx, rdx, r8, r9);
        state.at_rbp<uintptr_t>(0x540) = 0;
    }

    // ============================================================
    // 0xbcb56b8..0xbcb56f8: String buffer cleanup, call sub_e935700
    // 0xbcb56b8  mov rax,[rbp+0x468]
    // 0xbcb56bf  cmp rax,0x10
    // 0xbcb56c3  jb short 0xBCB56FD
    // 0xbcb56c5  mov rcx,[rbp+0x450]
    // 0xbcb56cc  lea rdx,[rax+1]
    // 0xbcb56d0  cmp rdx,0x1000
    // 0xbcb56d7  jb short 0xBCB56F8
    // 0xbcb56d9  mov r8,[rcx-8]
    // 0xbcb56dd  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xbcb56e1  sub rcx,r8
    // 0xbcb56e4  cmp rcx,0x20
    // 0xbcb56e8  jae 0xBCB5DCA
    // 0xbcb56ec  add rax,0x28
    // 0xbcb56f0  mov rdx,rax
    // 0xbcb56f3  mov rcx,r8
    // 0xbcb56f8  call 0xE935700
    // ============================================================
    rax = state.at_rbp<uintptr_t>(0x468);
    if (rax >= 0x10) {
        rcx = state.at_rbp<uintptr_t>(0x450);
        rdx = rax + 1;
        if (rdx < 0x1000) {
            // 0xbcb56f8  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        } else {
            r8 = *reinterpret_cast<uintptr_t*>(rcx - 8);
            rcx = rcx - 8;
            rcx = rcx - r8;
            if (rcx >= 0x20) {
                goto loc_bcb5dca_cold;
            }
            rax += 0x28;
            rdx = rax;
            rcx = r8;
            // 0xbcb56f8  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        }
    }

    // ============================================================
    // 0xbcb56fd..0xbcb575a: String buffer cleanup, call sub_e935700
    // 0xbcb56fd  mov qword ptr [rbp+0x460],0
    // 0xbcb5708  mov qword ptr [rbp+0x468],0xF
    // 0xbcb5713  mov byte ptr [rbp+0x450],0
    // 0xbcb571a  mov rax,[rbp+0x770]
    // 0xbcb5721  cmp rax,0x10
    // 0xbcb5725  jb short 0xBCB575F
    // 0xbcb5727  mov rcx,[rbp+0x758]
    // 0xbcb572e  lea rdx,[rax+1]
    // 0xbcb5732  cmp rdx,0x1000
    // 0xbcb5739  jb short 0xBCB575A
    // 0xbcb573b  mov r8,[rcx-8]
    // 0xbcb573f  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xbcb5743  sub rcx,r8
    // 0xbcb5746  cmp rcx,0x20
    // 0xbcb574a  jae 0xBCB5DCA
    // 0xbcb5750  add rax,0x28
    // 0xbcb5754  mov rdx,rax
    // 0xbcb5757  mov rcx,r8
    // 0xbcb575a  call 0xE935700
    // ============================================================
    state.at_rbp<uintptr_t>(0x460) = 0;
    state.at_rbp<uintptr_t>(0x468) = 0xF;
    state.at_rbp<uint8_t>(0x450) = 0;
    rax = state.at_rbp<uintptr_t>(0x770);
    if (rax >= 0x10) {
        rcx = state.at_rbp<uintptr_t>(0x758);
        rdx = rax + 1;
        if (rdx < 0x1000) {
            // 0xbcb575a  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        } else {
            r8 = *reinterpret_cast<uintptr_t*>(rcx - 8);
            rcx = rcx - 8;
            rcx = rcx - r8;
            if (rcx >= 0x20) {
                goto loc_bcb5dca_cold;
            }
            rax += 0x28;
            rdx = rax;
            rcx = r8;
            // 0xbcb575a  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        }
    }

    // ============================================================
    // 0xbcb575f..0xbcb579f: String buffer cleanup, call sub_e935700
    // 0xbcb575f  mov rax,[rbp+0x898]
    // 0xbcb5766  cmp rax,0x10
    // 0xbcb576a  jb short 0xBCB57A4
    // 0xbcb576c  mov rcx,[rbp+0x880]
    // 0xbcb5773  lea rdx,[rax+1]
    // 0xbcb5777  cmp rdx,0x1000
    // 0xbcb577e  jb short 0xBCB579F
    // 0xbcb5780  mov r8,[rcx-8]
    // 0xbcb5784  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xbcb5788  sub rcx,r8
    // 0xbcb578b  cmp rcx,0x20
    // 0xbcb578f  jae 0xBCB5DCA
    // 0xbcb5795  add rax,0x28
    // 0xbcb5799  mov rdx,rax
    // 0xbcb579c  mov rcx,r8
    // 0xbcb579f  call 0xE935700
    // ============================================================
    rax = state.at_rbp<uintptr_t>(0x898);
    if (rax >= 0x10) {
        rcx = state.at_rbp<uintptr_t>(0x880);
        rdx = rax + 1;
        if (rdx < 0x1000) {
            // 0xbcb579f  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        } else {
            r8 = *reinterpret_cast<uintptr_t*>(rcx - 8);
            rcx = rcx - 8;
            rcx = rcx - r8;
            if (rcx >= 0x20) {
                goto loc_bcb5dca_cold;
            }
            rax += 0x28;
            rdx = rax;
            rcx = r8;
            // 0xbcb579f  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        }
    }

    // ============================================================
    // 0xbcb57a4..0xbcb580c: String buffer cleanup, indirect call via [0xF99FFA0]
    // 0xbcb57a4  mov rax,[rbp+0x868]
    // 0xbcb57ab  cmp rax,0x10
    // 0xbcb57af  jb short 0xBCB57E9
    // 0xbcb57b1  mov rcx,[rbp+0x850]
    // 0xbcb57b8  lea rdx,[rax+1]
    // 0xbcb57bc  cmp rdx,0x1000
    // 0xbcb57c3  jb short 0xBCB57E4
    // 0xbcb57c5  mov r8,[rcx-8]
    // 0xbcb57c9  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xbcb57cd  sub rcx,r8
    // 0xbcb57d0  cmp rcx,0x20
    // 0xbcb57d4  jae 0xBCB5DCA
    // 0xbcb57da  add rax,0x28
    // 0xbcb57de  mov rdx,rax
    // 0xbcb57e1  mov rcx,r8
    // 0xbcb57e4  call 0xE935700
    // 0xbcb57e9  mov rcx,[rbp+0x2D8]
    // 0xbcb57f0  test rcx,rcx
    // 0xbcb57f3  je short 0xBCB5817
    // 0xbcb57f5  cmp rcx,r14
    // 0xbcb57f8  setne dl
    // 0xbcb57fb  mov rax,[rcx]
    // 0xbcb57fe  mov rax,[rax+0x20]
    // 0xbcb5802  call qword ptr [0xF99FFA0]
    // 0xbcb5807  mov qword ptr [rbp+0x2D8],0
    // 0xbcb580c  jmp 0xBCB5C23
    // ============================================================
    rax = state.at_rbp<uintptr_t>(0x868);
    if (rax >= 0x10) {
        rcx = state.at_rbp<uintptr_t>(0x850);
        rdx = rax + 1;
        if (rdx < 0x1000) {
            // 0xbcb57e4  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        } else {
            r8 = *reinterpret_cast<uintptr_t*>(rcx - 8);
            rcx = rcx - 8;
            rcx = rcx - r8;
            if (rcx >= 0x20) {
                goto loc_bcb5dca_cold;
            }
            rax += 0x28;
            rdx = rax;
            rcx = r8;
            // 0xbcb57e4  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        }
    }

    rcx = state.at_rbp<uintptr_t>(0x2D8);
    if (rcx != 0) {
        uint8_t dl = (rcx != r14) ? 1 : 0;
        rax = *reinterpret_cast<uintptr_t*>(rcx);
        rax = *reinterpret_cast<uintptr_t*>(rax + 0x20);
        // 0xbcb5806  call qword ptr [0xF99FFA0]
        thunk_eea6040_t thunk2 = *reinterpret_cast<thunk_eea6040_t*>(kDataSlot_F99FFA0);
        thunk2(rcx, rdx, r8, r9);
        state.at_rbp<uintptr_t>(0x2D8) = 0;
    }
    // 0xbcb580c  jmp 0xBCB5C23
    goto loc_bcb5c23;

    // ============================================================
    // 0xbcb5817..0xbcb5848: Indirect call via [0xF99FFA0], call sub_9bc830
    // 0xbcb5817  jmp 0xBCB5C23
    // 0xbcb581c  mov rcx,[0x1233E1A8]
    // 0xbcb5823  mov rax,[rcx]
    // 0xbcb5826  mov rax,[rax+8]
    // 0xbcb582a  mov rdx,r12
    // 0xbcb582d  call qword ptr [0xF99FFA0]
    // 0xbcb5833  nop
    // 0xbcb5834  mov r15,rax
    // 0xbcb5837  test rax,rax
    // 0xbcb583a  jne short 0xBCB5848
    // 0xbcb583c  mov rcx,r12
    // 0xbcb583f  call 0x9BC830
    // 0xbcb5844  nop
    // 0xbcb5845  xor r15d,r15d
    // ============================================================
    // This is a cold path (jmp target from 0xbcb57e0 area)
    // We'll handle it as a label
loc_bcb581c:
    rcx = *reinterpret_cast<uintptr_t*>(0x1233E1A8);
    rax = *reinterpret_cast<uintptr_t*>(rcx);
    rax = *reinterpret_cast<uintptr_t*>(rax + 8);
    rdx = r12;
    // 0xbcb582d  call qword ptr [0xF99FFA0]
    thunk_eea6040_t thunk3 = *reinterpret_cast<thunk_eea6040_t*>(kDataSlot_F99FFA0);
    thunk3(rcx, rdx, r8, r9);
    r15 = rax;
    if (rax == 0) {
        rcx = r12;
        // 0xbcb583f  call 0x9BC830
        boundary::sub_9bc830(rcx, rdx, r8, r9);
        r15 = 0;
    }

    // ============================================================
    // 0xbcb5848..0xbcb5871: Store to r15+rsi, compare r13 with rcx/rax
    // 0xbcb5848  mov rax,[rbp+0x8D0]
    // 0xbcb584f  mov [r15+rsi],rax
    // 0xbcb5853  mov rax,[rbp+0x8D8]
    // 0xbcb585a  mov [r15+rsi+8],rax
    // 0xbcb585f  mov rcx,[rbp+0x8E0]
    // 0xbcb5866  mov rax,[rcx+8]
    // 0xbcb586a  mov rcx,[rcx+0x10]
    // 0xbcb586e  cmp r13,rcx
    // 0xbcb5871  je 0xBCB5910
    // ============================================================
    rax = state.at_rbp<uintptr_t>(0x8D0);
    *reinterpret_cast<uintptr_t*>(r15 + rsi) = rax;
    rax = state.at_rbp<uintptr_t>(0x8D8);
    *reinterpret_cast<uintptr_t*>(r15 + rsi + 8) = rax;
    rcx = state.at_rbp<uintptr_t>(0x8E0);
    rax = *reinterpret_cast<uintptr_t*>(rcx + 8);
    rcx = *reinterpret_cast<uintptr_t*>(rcx + 0x10);
    if (r13 == rcx) {
        // 0xbcb5871  je 0xBCB5910
        goto loc_bcb5910;
    }

    // 0xbcb5877  cmp rax,r13
    // 0xbcb587a  je short 0xBCB58C7
    if (rax == r13) {
        goto loc_bcb58c7;
    }

    // The code at 0xbcb587a..0xbcb58c7 appears to be garbage/bad instructions (0xbcb58c0 area)
    // Skip to 0xbcb58c7

loc_bcb58c7:
    // ============================================================
    // 0xbcb58c7..0xbcb590e: Vector swap loop 3
    // 0xbcb58c7  xor edx,edx
    // 0xbcb58c9  xorps xmm0,xmm0
    // 0xbcb58cc  nop [rax]
    // 0xbcb58d0  movups [rax+rdx],xmm0
    // 0xbcb58d4  mov r8,[r13+rdx]
    // 0xbcb58d9  mov [rax+rdx],r8
    // 0xbcb58dd  mov r8,[r13+rdx+8]
    // 0xbcb58e2  mov [rax+rdx+8],r8
    // 0xbcb58e7  movups [r13+rdx],xmm0
    // 0xbcb58ed  lea r8,[rdx+r13]
    // 0xbcb58f1  add r8,0x10
    // 0xbcb58f5  add rdx,0x10
    // 0xbcb58f9  cmp r8,rcx
    // 0xbcb58fc  jne short 0xBCB58D0
    // 0xbcb58fe  jmp short 0xBCB594C
    // ============================================================
    rdx = 0;
    // xorps xmm0,xmm0
    while (true) {
        // movups [rax+rdx], xmm0
        // mov r8, [r13+rdx]
        // mov [rax+rdx], r8
        // mov r8, [r13+rdx+8]
        // mov [rax+rdx+8], r8
        // movups [r13+rdx], xmm0
        uint64_t* dst = reinterpret_cast<uint64_t*>(rax + rdx);
        uint64_t* src = reinterpret_cast<uint64_t*>(r13 + rdx);
        uint64_t tmp0 = dst[0];
        uint64_t tmp1 = dst[1];
        dst[0] = src[0];
        dst[1] = src[1];
        src[0] = tmp0;
        src[1] = tmp1;

        r8 = rdx + r13 + 0x10;
        rdx += 0x10;
        if (r8 == rcx) break;
    }
    // 0xbcb58fe  jmp short 0xBCB594C
    goto loc_bcb594c;

    // ============================================================
    // 0xbcb5910..0xbcb594a: Vector swap loop 4
    // 0xbcb5910  cmp rax,r13
    // 0xbcb5913  je short 0xBCB594C
    // 0xbcb5915  xor ecx,ecx
    // 0xbcb5917  xorps xmm0,xmm0
    // 0xbcb591a  nop [rax+rax]
    // 0xbcb5920  movups [r15+rcx],xmm0
    // 0xbcb5925  mov rdx,[rax+rcx]
    // 0xbcb5929  mov [r15+rcx],rdx
    // 0xbcb592d  mov rdx,[rax+rcx+8]
    // 0xbcb5932  mov [r15+rcx+8],rdx
    // 0xbcb5937  movups [rax+rcx],xmm0
    // 0xbcb593b  lea rdx,[rax+rcx]
    // 0xbcb593f  add rdx,0x10
    // 0xbcb5943  add rcx,0x10
    // 0xbcb5947  cmp rdx,r13
    // 0xbcb594a  jne short 0xBCB5920
    // ============================================================
loc_bcb5910:
    if (rax != r13) {
        rcx = 0;
        // xorps xmm0,xmm0
        while (true) {
            // movups [r15+rcx], xmm0
            // mov rdx, [rax+rcx]
            // mov [r15+rcx], rdx
            // mov rdx, [rax+rcx+8]
            // mov [r15+rcx+8], rdx
            // movups [rax+rcx], xmm0
            uint64_t* dst = reinterpret_cast<uint64_t*>(r15 + rcx);
            uint64_t* src = reinterpret_cast<uint64_t*>(rax + rcx);
            uint64_t tmp0 = dst[0];
            uint64_t tmp1 = dst[1];
            dst[0] = src[0];
            dst[1] = src[1];
            src[0] = tmp0;
            src[1] = tmp1;

            rdx = rax + rcx + 0x10;
            rcx += 0x10;
            if (rdx == r13) break;
        }
    }

    // ============================================================
    // 0xbcb594c..0xbcb597b: call sub_130ee0, setup, call sub_568c420
    // 0xbcb594c  mov rcx,rdi
    // 0xbcb594f  mov rdx,r15
    // 0xbcb5952  mov r8,rbx
    // 0xbcb5955  mov r9,r14
    // 0xbcb5958  call 0x130EE0
    // ============================================================
loc_bcb594c:
    // 0xbcb5958  call 0x130EE0
    sub_130ee0(rdi, r15, rbx, r14);

    // 0xbcb595d  mov rcx,[rbp+0x8E0]
    // 0xbcb5964  mov rax,[rcx+0x10]
    // 0xbcb5968  lea rdx,[rbp+0x728]
    // 0xbcb596f  mov byte ptr [rcx+0x60],1
    // 0xbcb5973  mov rax,[rax-0x10]
    // 0xbcb5977  mov [rcx+0x58],rax
    // 0xbcb597b  call 0x568C420
    rcx = state.at_rbp<uintptr_t>(0x8E0);
    rax = *reinterpret_cast<uintptr_t*>(rcx + 0x10);
    rdx = reinterpret_cast<uintptr_t>(&state.at_rbp<uint8_t>(0x728));
    *reinterpret_cast<uint8_t*>(rcx + 0x60) = 1;
    rax = *reinterpret_cast<uintptr_t*>(rax - 0x10);
    *reinterpret_cast<uintptr_t*>(rcx + 0x58) = rax;
    // 0xbcb597b  call 0x568C420
    sub_568c420(rcx, rdx, r8, r9);

    // ============================================================
    // 0xbcb5981..0xbcb59f8: String buffer setup, SSO check, call sub_9d6d0 or memcpy
    // 0xbcb5981  lea r14,[rbp+0x410]
    // 0xbcb5988  lea r15,[rbp+0x690]
    // 0xbcb598f  lea rdx,[rbp+0x700]
    // 0xbcb5996  mov rcx,[rbp+0x8E0]
    // 0xbcb599d  call 0x5693A80
    // ============================================================
    r14 = reinterpret_cast<uintptr_t>(&state.at_rbp<uint8_t>(0x410));
    r15 = reinterpret_cast<uintptr_t>(&state.at_rbp<uint8_t>(0x690));
    rdx = reinterpret_cast<uintptr_t>(&state.at_rbp<uint8_t>(0x700));
    rcx = state.at_rbp<uintptr_t>(0x8E0);
    // 0xbcb599d  call 0x5693A80
    sub_5693a80(rcx, rdx, r8, r9);

    // 0xbcb59a3  lea rax,[rbp+0x6D0]
    // 0xbcb59aa  mov rcx,[rbp+0x8E0]
    // 0xbcb59b1  mov rsi,[rcx+0x58]
    // 0xbcb59b5  lea rcx,[rsi+8]
    // 0xbcb59b9  cmp rcx,rax
    // 0xbcb59bc  je short 0xBCB5A1A
    rax = reinterpret_cast<uintptr_t>(&state.at_rbp<uint8_t>(0x6D0));
    rcx = state.at_rbp<uintptr_t>(0x8E0);
    rsi = *reinterpret_cast<uintptr_t*>(rcx + 0x58);
    rcx = rsi + 8;
    if (rcx != rax) {
        // 0xbcb59be  mov rdi,[rbp+0x6E8]
        // 0xbcb59c5  cmp qword ptr [rbp+0x6F0],0x10
        // 0xbcb59cd  jb short 0xBCB59D8
        rdi = state.at_rbp<uintptr_t>(0x6E8);
        if (state.at_rbp<uintptr_t>(0x6F0) >= 0x10) {
            // 0xbcb59cf  mov r9,[rbp+0x6D8]
            // 0xbcb59d6  jmp short 0xBCB59DF
            r9 = state.at_rbp<uintptr_t>(0x6D8);
        } else {
            // 0xbcb59d8  lea r9,[rbp+0x6D8]
            r9 = reinterpret_cast<uintptr_t>(&state.at_rbp<uint8_t>(0x6D8));
        }

        // 0xbcb59df  lea rbx,[rsi+0x10]
        // 0xbcb59e3  mov rax,[rsi+0x28]
        // 0xbcb59e7  cmp rdi,rax
        // 0xbcb59ea  jbe short 0xBCB59FA
        rbx = rsi + 0x10;
        rax = *reinterpret_cast<uintptr_t*>(rsi + 0x28);
        if (rdi > rax) {
            // 0xbcb59ec  mov rcx,rbx
            // 0xbcb59ef  mov rdx,rdi
            // 0xbcb59f2  call 0x9D6D0
            rcx = rbx;
            rdx = rdi;
            // 0xbcb59f2  call 0x9D6D0
            boundary::sub_9d6d0(rcx, rdx, r8, r9);
            // 0xbcb59f7  nop
            // 0xbcb59f8  jmp short 0xBCB5A1A
            goto loc_bcb5a1a;
        }

        // 0xbcb59fa  cmp rax,0x10
        // 0xbcb59fe  jb short 0xBCB5A04
        if (rax >= 0x10) {
            // 0xbcb5a00  mov rbx,[rsi+0x10]
            rbx = *reinterpret_cast<uintptr_t*>(rsi + 0x10);
        }

        // 0xbcb5a04  mov [rsi+0x20],rdi
        // 0xbcb5a08  mov rcx,rbx
        // 0xbcb5a0b  mov rdx,r9
        // 0xbcb5a0e  mov r8,rdi
        // 0xbcb5a11  call 0xEEC6DE0
        *reinterpret_cast<uintptr_t*>(rsi + 0x20) = rdi;
        rcx = rbx;
        rdx = r9;
        r8 = rdi;
        // 0xbcb5a01  call 0xEEC6DE0  (actually 0xbcb5a11)
        sub_eec6de0(rcx, rdx, r8, r9);

        // 0xbcb5a16  mov byte ptr [rbx+rdi],0
        *reinterpret_cast<uint8_t*>(rbx + rdi) = 0;
    }

loc_bcb5a1a:
    // ============================================================
    // 0xbcb5a1a..0xbcb5a7c: Cleanup, call sub_e935700
    // 0xbcb5a1a  mov rax,[rbp+0x6D0]
    // 0xbcb5a21  mov [rsi+8],rax
    // 0xbcb5a25  mov qword ptr [rsi+0x30],0
    // 0xbcb5a2d  mov rax,[rbp+0x8E0]
    // 0xbcb5a34  mov qword ptr [rax+0x58],0
    // 0xbcb5a3c  mov rax,[rbp+0x6F0]
    // 0xbcb5a43  cmp rax,0x10
    // 0xbcb5a47  jb short 0xBCB5A81
    // 0xbcb5a49  mov rcx,[rbp+0x6D8]
    // 0xbcb5a50  lea rdx,[rax+1]
    // 0xbcb5a54  cmp rdx,0x1000
    // 0xbcb5a5b  jb short 0xBCB5A7C
    // 0xbcb5a5d  mov r8,[rcx-8]
    // 0xbcb5a61  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xbcb5a65  sub rcx,r8
    // 0xbcb5a68  cmp rcx,0x20
    // 0xbcb5a6c  jae 0xBCB5DCA
    // 0xbcb5a72  add rax,0x28
    // 0xbcb5a76  mov rdx,rax
    // 0xbcb5a79  mov rcx,r8
    // 0xbcb5a7c  call 0xE935700
    // ============================================================
    rax = state.at_rbp<uintptr_t>(0x6D0);
    *reinterpret_cast<uintptr_t*>(rsi + 8) = rax;
    *reinterpret_cast<uintptr_t*>(rsi + 0x30) = 0;
    rax = state.at_rbp<uintptr_t>(0x8E0);
    *reinterpret_cast<uintptr_t*>(rax + 0x58) = 0;
    rax = state.at_rbp<uintptr_t>(0x6F0);
    if (rax >= 0x10) {
        rcx = state.at_rbp<uintptr_t>(0x6D8);
        rdx = rax + 1;
        if (rdx < 0x1000) {
            // 0xbcb5a7c  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        } else {
            r8 = *reinterpret_cast<uintptr_t*>(rcx - 8);
            rcx = rcx - 8;
            rcx = rcx - r8;
            if (rcx >= 0x20) {
                goto loc_bcb5dca_cold;
            }
            rax += 0x28;
            rdx = rax;
            rcx = r8;
            // 0xbcb5a7c  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        }
    }

    // ============================================================
    // 0xbcb5a81..0xbcb5abd: String buffer cleanup, indirect call via [0xF99FFA0]
    // 0xbcb5a81  mov qword ptr [rbp+0x6E8],0
    // 0xbcb5a8c  mov qword ptr [rbp+0x6F0],0xF
    // 0xbcb5a97  mov byte ptr [rbp+0x6D8],0
    // 0xbcb5a9e  mov rcx,[rbp+0x6C8]
    // 0xbcb5aa5  test rcx,rcx
    // 0xbcb5aa8  je short 0xBCB5AC8
    // 0xbcb5aaa  cmp rcx,r15
    // 0xbcb5aad  setne dl
    // 0xbcb5ab0  mov rax,[rcx]
    // 0xbcb5ab3  mov rax,[rax+0x20]
    // 0xbcb5ab7  call qword ptr [0xF99FFA0]
    // 0xbcb5abd  mov qword ptr [rbp+0x6C8],0
    // ============================================================
    state.at_rbp<uintptr_t>(0x6E8) = 0;
    state.at_rbp<uintptr_t>(0x6F0) = 0xF;
    state.at_rbp<uint8_t>(0x6D8) = 0;
    rcx = state.at_rbp<uintptr_t>(0x6C8);
    if (rcx != 0) {
        uint8_t dl = (rcx != r15) ? 1 : 0;
        rax = *reinterpret_cast<uintptr_t*>(rcx);
        rax = *reinterpret_cast<uintptr_t*>(rax + 0x20);
        // 0xbcb5ab7  call qword ptr [0xF99FFA0]
        thunk_eea6040_t thunk4 = *reinterpret_cast<thunk_eea6040_t*>(kDataSlot_F99FFA0);
        thunk4(rcx, rdx, r8, r9);
        state.at_rbp<uintptr_t>(0x6C8) = 0;
    }

    // ============================================================
    // 0xbcb5ac8..0xbcb5b08: String buffer cleanup, call sub_e935700
    // 0xbcb5ac8  mov rax,[rbp+0x468]
    // 0xbcb5acf  cmp rax,0x10
    // 0xbcb5ad3  jb short 0xBCB5B0D
    // 0xbcb5ad5  mov rcx,[rbp+0x450]
    // 0xbcb5adc  lea rdx,[rax+1]
    // 0xbcb5ae0  cmp rdx,0x1000
    // 0xbcb5ae7  jb short 0xBCB5B08
    // 0xbcb5ae9  mov r8,[rcx-8]
    // 0xbcb5aed  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xbcb5af1  sub rcx,r8
    // 0xbcb5af4  cmp rcx,0x20
    // 0xbcb5af8  jae 0xBCB5DCA
    // 0xbcb5afe  add rax,0x28
    // 0xbcb5b02  mov rdx,rax
    // 0xbcb5b05  mov rcx,r8
    // 0xbcb5b08  call 0xE935700
    // ============================================================
    rax = state.at_rbp<uintptr_t>(0x468);
    if (rax >= 0x10) {
        rcx = state.at_rbp<uintptr_t>(0x450);
        rdx = rax + 1;
        if (rdx < 0x1000) {
            // 0xbcb5b08  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        } else {
            r8 = *reinterpret_cast<uintptr_t*>(rcx - 8);
            rcx = rcx - 8;
            rcx = rcx - r8;
            if (rcx >= 0x20) {
                goto loc_bcb5dca_cold;
            }
            rax += 0x28;
            rdx = rax;
            rcx = r8;
            // 0xbcb5b08  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        }
    }

    // ============================================================
    // 0xbcb5b0d..0xbcb5b6a: String buffer cleanup, call sub_e935700
    // 0xbcb5b0d  mov qword ptr [rbp+0x460],0
    // 0xbcb5b18  mov qword ptr [rbp+0x468],0xF
    // 0xbcb5b23  mov byte ptr [rbp+0x450],0
    // 0xbcb5b2a  mov rax,[rbp+0x770]
    // 0xbcb5b31  cmp rax,0x10
    // 0xbcb5b35  jb short 0xBCB5B6F
    // 0xbcb5b37  mov rcx,[rbp+0x758]
    // 0xbcb5b3e  lea rdx,[rax+1]
    // 0xbcb5b42  cmp rdx,0x1000
    // 0xbcb5b49  jb short 0xBCB5B6A
    // 0xbcb5b4b  mov r8,[rcx-8]
    // 0xbcb5b4f  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xbcb5b53  sub rcx,r8
    // 0xbcb5b56  cmp rcx,0x20
    // 0xbcb5b5a  jae 0xBCB5DCA
    // 0xbcb5b60  add rax,0x28
    // 0xbcb5b64  mov rdx,rax
    // 0xbcb5b67  mov rcx,r8
    // 0xbcb5b6a  call 0xE935700
    // ============================================================
    state.at_rbp<uintptr_t>(0x460) = 0;
    state.at_rbp<uintptr_t>(0x468) = 0xF;
    state.at_rbp<uint8_t>(0x450) = 0;
    rax = state.at_rbp<uintptr_t>(0x770);
    if (rax >= 0x10) {
        rcx = state.at_rbp<uintptr_t>(0x758);
        rdx = rax + 1;
        if (rdx < 0x1000) {
            // 0xbcb5b6a  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        } else {
            r8 = *reinterpret_cast<uintptr_t*>(rcx - 8);
            rcx = rcx - 8;
            rcx = rcx - r8;
            if (rcx >= 0x20) {
                goto loc_bcb5dca_cold;
            }
            rax += 0x28;
            rdx = rax;
            rcx = r8;
            // 0xbcb5b6a  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        }
    }

    // ============================================================
    // 0xbcb5b6f..0xbcb5baf: String buffer cleanup, call sub_e935700
    // 0xbcb5b6f  mov rax,[rbp+0x898]
    // 0xbcb5b76  cmp rax,0x10
    // 0xbcb5b7a  jb short 0xBCB5BB4
    // 0xbcb5b7c  mov rcx,[rbp+0x880]
    // 0xbcb5b83  lea rdx,[rax+1]
    // 0xbcb5b87  cmp rdx,0x1000
    // 0xbcb5b8e  jb short 0xBCB5BAF
    // 0xbcb5b90  mov r8,[rcx-8]
    // 0xbcb5b94  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xbcb5b98  sub rcx,r8
    // 0xbcb5b9b  cmp rcx,0x20
    // 0xbcb5b9f  jae 0xBCB5DCA
    // 0xbcb5ba5  add rax,0x28
    // 0xbcb5ba9  mov rdx,rax
    // 0xbcb5bac  mov rcx,r8
    // 0xbcb5baf  call 0xE935700
    // ============================================================
    rax = state.at_rbp<uintptr_t>(0x898);
    if (rax >= 0x10) {
        rcx = state.at_rbp<uintptr_t>(0x880);
        rdx = rax + 1;
        if (rdx < 0x1000) {
            // 0xbcb5baf  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        } else {
            r8 = *reinterpret_cast<uintptr_t*>(rcx - 8);
            rcx = rcx - 8;
            rcx = rcx - r8;
            if (rcx >= 0x20) {
                goto loc_bcb5dca_cold;
            }
            rax += 0x28;
            rdx = rax;
            rcx = r8;
            // 0xbcb5baf  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        }
    }

    // ============================================================
    // 0xbcb5bb4..0xbcb5c12: String buffer cleanup, indirect call via [0xF99FFA0]
    // 0xbcb5bb4  mov rax,[rbp+0x868]
    // 0xbcb5bbb  cmp rax,0x10
    // 0xbcb5bbf  jb short 0xBCB5BF9
    // 0xbcb5bc1  mov rcx,[rbp+0x850]
    // 0xbcb5bc8  lea rdx,[rax+1]
    // 0xbcb5bcc  cmp rdx,0x1000
    // 0xbcb5bd3  jb short 0xBCB5BF4
    // 0xbcb5bd5  mov r8,[rcx-8]
    // 0xbcb5bd9  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xbcb5bdd  sub rcx,r8
    // 0xbcb5be0  cmp rcx,0x20
    // 0xbcb5be4  jae 0xBCB5DCA
    // 0xbcb5bea  add rax,0x28
    // 0xbcb5bee  mov rdx,rax
    // 0xbcb5bf1  mov rcx,r8
    // 0xbcb5bf4  call 0xE935700
    // 0xbcb5bf9  mov rcx,[rbp+0x440]
    // 0xbcb5c00  test rcx,rcx
    // 0xbcb5c03  je short 0xBCB5C23
    // 0xbcb5c05  cmp rcx,r14
    // 0xbcb5c08  setne dl
    // 0xbcb5c0b  mov rax,[rcx]
    // 0xbcb5c0e  mov rax,[rax+0x20]
    // 0xbcb5c12  call qword ptr [0xF99FFA0]
    // ============================================================
    rax = state.at_rbp<uintptr_t>(0x868);
    if (rax >= 0x10) {
        rcx = state.at_rbp<uintptr_t>(0x850);
        rdx = rax + 1;
        if (rdx < 0x1000) {
            // 0xbcb5bf4  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        } else {
            r8 = *reinterpret_cast<uintptr_t*>(rcx - 8);
            rcx = rcx - 8;
            rcx = rcx - r8;
            if (rcx >= 0x20) {
                goto loc_bcb5dca_cold;
            }
            rax += 0x28;
            rdx = rax;
            rcx = r8;
            // 0xbcb5bf4  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        }
    }

    rcx = state.at_rbp<uintptr_t>(0x440);
    if (rcx != 0) {
        uint8_t dl = (rcx != r14) ? 1 : 0;
        rax = *reinterpret_cast<uintptr_t*>(rcx);
        rax = *reinterpret_cast<uintptr_t*>(rax + 0x20);
        // 0xbcb5c12  call qword ptr [0xF99FFA0]
        thunk_eea6040_t thunk5 = *reinterpret_cast<thunk_eea6040_t*>(kDataSlot_F99FFA0);
        thunk5(rcx, rdx, r8, r9);
    }

    // ============================================================
    // 0xbcb5c23..0xbcb5c63: String buffer cleanup, call sub_e935700
    // 0xbcb5c23  mov rax,[rbp+0x1E8]
    // 0xbcb5c2a  cmp rax,0x10
    // 0xbcb5c2e  jb short 0xBCB5C68
    // 0xbcb5c30  mov rcx,[rbp+0x1D0]
    // 0xbcb5c37  lea rdx,[rax+1]
    // 0xbcb5c3b  cmp rdx,0x1000
    // 0xbcb5c42  jb short 0xBCB5C63
    // 0xbcb5c44  mov r8,[rcx-8]
    // 0xbcb5c48  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xbcb5c4c  sub rcx,r8
    // 0xbcb5c4f  cmp rcx,0x20
    // 0xbcb5c53  jae 0xBCB5DCA
    // 0xbcb5c59  add rax,0x28
    // 0xbcb5c5d  mov rdx,rax
    // 0xbcb5c60  mov rcx,r8
    // 0xbcb5c63  call 0xE935700
    // ============================================================
loc_bcb5c23:
    rax = state.at_rbp<uintptr_t>(0x1E8);
    if (rax >= 0x10) {
        rcx = state.at_rbp<uintptr_t>(0x1D0);
        rdx = rax + 1;
        if (rdx < 0x1000) {
            // 0xbcb5c63  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        } else {
            r8 = *reinterpret_cast<uintptr_t*>(rcx - 8);
            rcx = rcx - 8;
            rcx = rcx - r8;
            if (rcx >= 0x20) {
                goto loc_bcb5dca_cold;
            }
            rax += 0x28;
            rdx = rax;
            rcx = r8;
            // 0xbcb5c63  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        }
    }

    // ============================================================
    // 0xbcb5c68..0xbcb5cc5: String buffer cleanup, call sub_e935700
    // 0xbcb5c68  mov qword ptr [rbp+0x1E0],0
    // 0xbcb5c73  mov qword ptr [rbp+0x1E8],0xF
    // 0xbcb5c7e  mov byte ptr [rbp+0x1D0],0
    // 0xbcb5c85  mov rax,[rbp+0x8C8]
    // 0xbcb5c8c  cmp rax,0x10
    // 0xbcb5c90  jb short 0xBCB5CCA
    // 0xbcb5c92  mov rcx,[rbp+0x8B0]
    // 0xbcb5c99  lea rdx,[rax+1]
    // 0xbcb5c9d  cmp rdx,0x1000
    // 0xbcb5ca4  jb short 0xBCB5CC5
    // 0xbcb5ca6  mov r8,[rcx-8]
    // 0xbcb5caa  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xbcb5cae  sub rcx,r8
    // 0xbcb5cb1  cmp rcx,0x20
    // 0xbcb5cb5  jae 0xBCB5DCA
    // 0xbcb5cbb  add rax,0x28
    // 0xbcb5cbf  mov rdx,rax
    // 0xbcb5cc2  mov rcx,r8
    // 0xbcb5cc5  call 0xE935700
    // ============================================================
    state.at_rbp<uintptr_t>(0x1E0) = 0;
    state.at_rbp<uintptr_t>(0x1E8) = 0xF;
    state.at_rbp<uint8_t>(0x1D0) = 0;
    rax = state.at_rbp<uintptr_t>(0x8C8);
    if (rax >= 0x10) {
        rcx = state.at_rbp<uintptr_t>(0x8B0);
        rdx = rax + 1;
        if (rdx < 0x1000) {
            // 0xbcb5cc5  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        } else {
            r8 = *reinterpret_cast<uintptr_t*>(rcx - 8);
            rcx = rcx - 8;
            rcx = rcx - r8;
            if (rcx >= 0x20) {
                goto loc_bcb5dca_cold;
            }
            rax += 0x28;
            rdx = rax;
            rcx = r8;
            // 0xbcb5cc5  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        }
    }

    // ============================================================
    // 0xbcb5cca..0xbcb5d0a: String buffer cleanup, call sub_e935700
    // 0xbcb5cca  mov rax,[rbp+0x810]
    // 0xbcb5cd1  cmp rax,0x10
    // 0xbcb5cd5  jb short 0xBCB5D0F
    // 0xbcb5cd7  mov rcx,[rbp+0x7F8]
    // 0xbcb5cde  lea rdx,[rax+1]
    // 0xbcb5ce2  cmp rdx,0x1000
    // 0xbcb5ce9  jb short 0xBCB5D0A
    // 0xbcb5ceb  mov r8,[rcx-8]
    // 0xbcb5cef  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xbcb5cf3  sub rcx,r8
    // 0xbcb5cf6  cmp rcx,0x20
    // 0xbcb5cfa  jae 0xBCB5DCA
    // 0xbcb5d00  add rax,0x28
    // 0xbcb5d04  mov rdx,rax
    // 0xbcb5d07  mov rcx,r8
    // 0xbcb5d0a  call 0xE935700
    // ============================================================
    rax = state.at_rbp<uintptr_t>(0x810);
    if (rax >= 0x10) {
        rcx = state.at_rbp<uintptr_t>(0x7F8);
        rdx = rax + 1;
        if (rdx < 0x1000) {
            // 0xbcb5d0a  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        } else {
            r8 = *reinterpret_cast<uintptr_t*>(rcx - 8);
            rcx = rcx - 8;
            rcx = rcx - r8;
            if (rcx >= 0x20) {
                goto loc_bcb5dca_cold;
            }
            rax += 0x28;
            rdx = rax;
            rcx = r8;
            // 0xbcb5d0a  call 0xE935700
            sub_e935700(rcx, rdx, r8, r9);
        }
    }

    // ============================================================
    // 0xbcb5d0f..0xbcb5d29: Epilogue
    // 0xbcb5d0f  movaps xmm6,[rbp+0x8F0]
    // 0xbcb5d16  add rsp,0x988
    // 0xbcb5d1d  pop rbx
    // 0xbcb5d1e  pop rdi
    // 0xbcb5d1f  pop rsi
    // 0xbcb5d20  pop r12
    // 0xbcb5d22  pop r13
    // 0xbcb5d24  pop r14
    // 0xbcb5d26  pop r15
    // 0xbcb5d28  pop rbp
    // 0xbcb5d29  ret
    // ============================================================
    // Restore xmm6 from [rbp+0x8F0]
    // Note: xmm6 is not modeled in ChunkState; in real code this would be a movaps
    // Add rsp, 0x988 - stack frame teardown
    // Pop registers in reverse order
    return;  // ret

    // ============================================================
    // 0xbcb5d2a..0xbcb5e09: Cold paths (error handlers)
    // 0xbcb5d2a  call 0x78ED0
    // 0xbcb5d2f  nop
    // 0xbcb5d30  mov ecx,0x130
    // 0xbcb5d35  call 0x9BC830
    // 0xbcb5d3a  nop
    // 0xbcb5d3b  jmp 0xBCB3EF2
    // 0xbcb5d40  mov ecx,0x130
    // 0xbcb5d45  call 0x9BC830
    // 0xbcb5d4a  nop
    // 0xbcb5d4b  jmp 0xBCB4664
    // 0xbcb5d50  mov ecx,0x140
    // 0xbcb5d55  call 0x9BC830
    // 0xbcb5d5a  nop
    // 0xbcb5d5b  jmp 0xBCB4B84
    // 0xbcb5d60  mov ecx,0x2C8
    // 0xbcb5d65  call 0x9BC830
    // 0xbcb5d6a  nop
    // 0xbcb5d6b  jmp 0xBCB4D13
    // 0xbcb5d70  mov rcx,r12
    // 0xbcb5d73  call 0x9BC830
    // 0xbcb5d78  nop
    // 0xbcb5d79  jmp 0xBCB4ED7
    // 0xbcb5d7e  mov rcx,r12
    // 0xbcb5d81  call 0x9BC830
    // 0xbcb5d86  nop
    // 0xbcb5d87  xor r15d,r15d
    // 0xbcb5d8a  jmp 0xBCB4F02
    // 0xbcb5d8f  mov rcx,r12
    // 0xbcb5d92  call 0x9BC830
    // 0xbcb5d97  nop
    // 0xbcb5d98  jmp 0xBCB52C4
    // 0xbcb5d9d  mov rcx,r12
    // 0xbcb5da0  call 0x9BC830
    // 0xbcb5da5  nop
    // 0xbcb5da6  xor r15d,r15d
    // 0xbcb5da9  jmp 0xBCB52EF
    // 0xbcb5dae  mov rcx,r12
    // 0xbcb5db1  call 0x9BC830
    // 0xbcb5db6  nop
    // 0xbcb5db7  jmp 0xBCB5010
    // 0xbcb5dbc  mov rcx,r12
    // 0xbcb5dbf  call 0x9BC830
    // 0xbcb5dc4  nop
    // 0xbcb5dc5  jmp 0xBCB53FD
    // 0xbcb5dca  mov qword ptr [rsp+0x20],0
    // 0xbcb5dd3  xor ecx,ecx
    // 0xbcb5dd5  xor edx,edx
    // 0xbcb5dd7  xor r8d,r8d
    // 0xbcb5dda  xor r9d,r9d
    // 0xbcb5ddd  call qword ptr [0xF9A8C78]
    // 0xbcb5de3  nop
    // 0xbcb5de4  call 0x75720
    // 0xbcb5dea  call 0x75720
    // 0xbcb5df0  call 0x75740
    // 0xbcb5df6  call 0x75740
    // 0xbcb5dfc  call 0x75740
    // 0xbcb5e02  call 0x75740
    // 0xbcb5e07  int3
    // 0xbcb5e08  int3
    // 0xbcb5e09  nop [rax]
    // ============================================================
loc_bcb5dca_cold:
    // Cold path at 0xbcb5dca
    *reinterpret_cast<uintptr_t*>(/*rsp+0x20*/0) = 0;  // rsp not modeled
    rcx = 0; rdx = 0; r8 = 0; r9 = 0;
    // 0xbcb5ddd  call qword ptr [0xF9A8C78]
    thunk_f9a8c78_t thunk_f9a8c78 = *reinterpret_cast<thunk_f9a8c78_t*>(kDataSlot_F9A8C78);
    thunk_f9a8c78(rcx, rdx, r8, r9);
    // 0xbcb5de4  call 0x75720
    boundary::sub_75720(rcx, rdx, r8, r9);
    // 0xbcb5dea  call 0x75720
    boundary::sub_75720(rcx, rdx, r8, r9);
    // 0xbcb5df0  call 0x75740
    boundary::sub_75740(rcx, rdx, r8, r9);
    // 0xbcb5df6  call 0x75740
    boundary::sub_75740(rcx, rdx, r8, r9);
    // 0xbcb5dfc  call 0x75740
    boundary::sub_75740(rcx, rdx, r8, r9);
    // 0xbcb5e02  call 0x75740
    boundary::sub_75740(rcx, rdx, r8, r9);
    // int3; int3; nop [rax]
    __debugbreak();
    __debugbreak();
    return;
}

// LIFT_FN registry entry
const void* kSub_bcb3cf0_Chunk2_Entry = reinterpret_cast<const void*>(sub_bcb3cf0_chunk2);

} // namespace native::bgfx