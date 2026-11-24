// LIFT 0xbc8eb90 size 0x5ba7 1.26.62.01 VV frame-graph builder
// CHUNK 0xbc93379..0xbc94737

#include "sub_bc8eb90_chunk3.h"

namespace native {

// verbatim call quotes (machine-checked)
#if 0
0xbc93393  call 0x9D6D0
0xbc933b6  call 0xEEC6DE0
0xbc93421  call 0xE935700
0xbc93463  call qword ptr [0xF99FFA0]
0xbc934b4  call 0xE935700
0xbc93516  call 0xE935700
0xbc9355b  call 0xE935700
0xbc935a0  call 0xE935700
0xbc935be  call qword ptr [0xF99FFA0]
0xbc935fe  call 0xE935700
0xbc93643  call 0xE935700
0xbc93688  call 0xE935700
0xbc936cd  call 0xE935700
0xbc936eb  call qword ptr [0xF99FFA0]
0xbc93700  call qword ptr [0xF99FFA0]
0xbc9372d  call 0x9BC830
0xbc9373d  call 0x9BC830
0xbc9374d  call 0x9BC830
0xbc9375d  call 0x9BC830
0xbc9376d  call 0x9BC830
0xbc9377d  call 0x9BC830
0xbc9378d  call 0x9BC830
0xbc937ae  call 0x9BC830
0xbc937c0  call 0x9BC830
0xbc937d0  call 0x9BC830
0xbc937ee  call 0x9BC830
0xbc93800  call 0x9BC830
0xbc93810  call 0x9BC830
0xbc9382e  call 0x9BC830
0xbc93840  call 0x9BC830
0xbc93850  call 0x9BC830
0xbc9386e  call 0x9BC830
0xbc93880  call 0x9BC830
0xbc93890  call 0x9BC830
0xbc9389e  call 0x9BC830
0xbc938ac  call 0x9BC830
0xbc938bc  call 0x9BC830
0xbc938ca  call 0x9BC830
0xbc938da  call 0x9BC830
0xbc938e8  call 0x9BC830
0xbc938fa  call 0x9BC830
0xbc9390a  call 0x9BC830
0xbc9391b  call 0x9BC830
0xbc9392b  call 0x9BC830
0xbc93939  call 0x9BC830
0xbc93949  call 0x9BC830
0xbc93957  call 0x9BC830
0xbc93967  call 0x9BC830
0xbc93975  call 0x9BC830
0xbc93993  call qword ptr [0xF9A8C78]
0xbc939a0  call 0xE938CB0
0xbc939c0  call 0x79580
0xbc939d1  call 0x79580
0xbc939e2  call 0xBC95DB0
0xbc939ec  call 0x73150
0xbc939f8  call 0x73150
0xbc93a04  call 0xE935740
0xbc93a10  call 0xE938D70
0xbc93a28  call 0xE938CB0
0xbc93a63  call 0x5668AC0
0xbc93a70  call 0xE938D70
0xbc93a88  call 0xE938CB0
0xbc93aab  call 0x79580
0xbc93afa  call 0xE938CB0
0xbc93b1d  call 0x79580
0xbc93b6c  call 0xE938CB0
0xbc93b8f  call 0x79580
0xbc93bde  call 0xE938CB0
0xbc93c01  call 0x79580
0xbc93c50  call 0xE938CB0
0xbc93c73  call 0x79580
0xbc93cc2  call 0xE938CB0
0xbc93ce5  call 0x79580
0xbc93d34  call 0xE938CB0
0xbc93d57  call 0x79580
0xbc93da6  call 0xE938CB0
0xbc93dc9  call 0x79580
0xbc93e18  call 0xE938CB0
0xbc93e3b  call 0x79580
0xbc93e8a  call 0xE938CB0
0xbc93ead  call 0x79580
0xbc93f07  call 0x75720
0xbc93f14  call 0x75720
0xbc93f21  call 0x75720
0xbc93f2e  call 0x75720
0xbc93f3f  call 0x75740
0xbc93f53  call 0x75740
0xbc93f64  call 0x75740
0xbc93f78  call 0x75740
0xbc940a6  call 0x73150
0xbc940b2  call 0xE938D70
0xbc9415c  call 0x73150
0xbc94168  call 0xE938D70
0xbc94212  call 0x73150
0xbc9421e  call 0xE938D70
0xbc942c8  call 0x73150
0xbc942d4  call 0xE938D70
0xbc9437e  call 0x73150
0xbc9438a  call 0xE938D70
0xbc94434  call 0x73150
0xbc94440  call 0xE938D70
0xbc944ea  call 0x73150
0xbc944f6  call 0xE938D70
0xbc945a0  call 0x73150
0xbc945ac  call 0xE938D70
0xbc94656  call 0x73150
0xbc94662  call 0xE938D70
0xbc946fa  call 0x73150
0xbc94706  call 0xE938D70
0xbc9471e  call 0x75740
0xbc94724  call 0x75740
0xbc9472a  call 0x75740
0xbc94730  call 0x75740
#endif

// Helper to get the free function pointer from data slot 0xF99FFA0 (sub_eea6040)
static inline FreeFn get_free_fn(ChunkState_bc8eb90_c03& st) {
    (void)st;
    return *reinterpret_cast<FreeFn*>(0xF99FFA0);
}

// Helper to get the alloc function pointer from data slot 0xF9A8C78
static inline auto get_abort_fn(ChunkState_bc8eb90_c03& st) {
    (void)st;
    return *reinterpret_cast<void(*)(uint64_t, uint64_t, uint64_t, uint64_t)*>(0xF9A8C78);
}

static inline void chunk_bc8eb90_c03(ChunkState_bc8eb90_c03* st) {
    // 0xbc93379..0xbc933bf
    // String/vector cleanup for rsi (arg1) - part of frame-graph builder cleanup
    // lea rbx, [rsi+0x10]
    uint64_t rbx = st->slot<uint64_t>(0x10);  // rsi+0x10
    // mov rax, [rsi+0x28]
    uint64_t rax = st->slot<uint64_t>(0x28);  // rsi+0x28
    // cmp rdi, rax
    // jbe short 0xBC9339B
    if (st->rdi <= rax) {
        // loc_bc9339b:
        // cmp rax, 0x10
        // jb short 0xBC933A5
        if (rax >= 0x10) {
            // mov rbx, [rsi+0x10]
            rbx = st->slot<uint64_t>(0x10);
        }
        // loc_bc933a5:
        // mov [rsi+0x20], rdi
        st->slot<uint64_t>(0x20) = st->rdi;
        // mov rcx, rbx
        // mov rdx, [rbp+0x318]
        // mov r8, rdi
        // call 0xEEC6DE0
        sub_eec6de0(reinterpret_cast<void*>(rbx), reinterpret_cast<void*>(st->slot<uint64_t>(0x318)), st->rdi);
        // mov byte ptr [rbx+rdi], 0
        *reinterpret_cast<uint8_t*>(rbx + st->rdi) = 0;
    } else {
        // mov rcx, rbx
        // mov rdx, rdi
        // mov r9, [rbp+0x318]
        // call 0x9D6D0
        sub_9d6d0(reinterpret_cast<void*>(rbx), reinterpret_cast<void*>(st->rdi), reinterpret_cast<void*>(st->rdi), st->slot<uint64_t>(0x318));
        // nop
        // jmp short 0xBC933BF
    }

    // loc_bc933bf:
    // mov rax, [rbp+0x178]
    // mov [rsi+8], rax
    st->slot<uint64_t>(0x8) = st->slot<uint64_t>(0x178);
    // mov qword ptr [rsi+0x30], 0
    st->slot<uint64_t>(0x30) = 0;
    // mov rax, [rbp+0x400]
    // mov qword ptr [rax+0x58], 0
    st->slot<uint64_t>(st->slot<uint64_t>(0x400) + 0x58) = 0;

    // 0xbc933e1..0xbc93426
    // Cleanup std::string at [rbp+0x180] (size at [rbp+0x198], ptr at [rbp+0x180])
    // mov rax, [rbp+0x198]
    rax = st->slot<uint64_t>(0x198);
    // cmp rax, 0x10
    // jb short 0xBC93426
    if (rax >= 0x10) {
        // mov rcx, [rbp+0x180]
        uint64_t rcx = st->slot<uint64_t>(0x180);
        // lea rdx, [rax+1]
        uint64_t rdx = rax + 1;
        // cmp rdx, 0x1000
        // jb short 0xBC93421
        if (rdx < 0x1000) {
            // loc_bc93421:
            // call 0xE935700
            sub_e935700(reinterpret_cast<void*>(rcx), rdx);
        } else {
            // mov r8, [rcx-8]
            uint64_t r8 = *reinterpret_cast<uint64_t*>(rcx - 8);
            // add rcx, -8
            rcx -= 8;
            // sub rcx, r8
            rcx -= r8;
            // cmp rcx, 0x20
            // jae 0xBC93980
            if (rcx >= 0x20) {
                // loc_bc93980: abort path
                goto abort_path;
            }
            // add rax, 0x28
            rax += 0x28;
            // mov rdx, rax
            rdx = rax;
            // mov rcx, r8
            rcx = r8;
            // call 0xE935700
            sub_e935700(reinterpret_cast<void*>(rcx), rdx);
        }
    }

    // loc_bc93426:
    // mov qword ptr [rbp+0x190], 0
    st->slot<uint64_t>(0x190) = 0;
    // mov qword ptr [rbp+0x198], 0xF
    st->slot<uint64_t>(0x198) = 0xF;
    // mov byte ptr [rbp+0x180], 0
    st->slot<uint8_t>(0x180) = 0;

    // 0xbc93443..0xbc93474
    // Cleanup std::string at [rbp+0x170] (if not SSO)
    // mov rcx, [rbp+0x170]
    rcx = st->slot<uint64_t>(0x170);
    // test rcx, rcx
    // je short 0xBC93474
    if (rcx != 0) {
        // lea rax, [rbp+0x138]
        uint64_t rax_ss = st->rbp + 0x138;
        // cmp rcx, rax
        // setne dl
        uint8_t dl = (rcx != rax_ss) ? 1 : 0;
        // mov rax, [rcx]
        // mov rax, [rax+0x20]
        // call qword ptr [0xF99FFA0]
        if (dl) {
            get_free_fn(*st)(reinterpret_cast<void*>(rcx));
        }
        // mov qword ptr [rbp+0x170], 0
        st->slot<uint64_t>(0x170) = 0;
    }

    // loc_bc93474:
    // 0xbc93474..0xbc934b9
    // Cleanup std::string at [rbp+0x110] (size at [rbp+0x128], ptr at [rbp+0x110])
    rax = st->slot<uint64_t>(0x128);
    if (rax >= 0x10) {
        rcx = st->slot<uint64_t>(0x110);
        rdx = rax + 1;
        if (rdx < 0x1000) {
            sub_e935700(reinterpret_cast<void*>(rcx), rdx);
        } else {
            r8 = *reinterpret_cast<uint64_t*>(rcx - 8);
            rcx -= 8;
            rcx -= r8;
            if (rcx >= 0x20) goto abort_path;
            rax += 0x28;
            rdx = rax;
            rcx = r8;
            sub_e935700(reinterpret_cast<void*>(rcx), rdx);
        }
    }

    // loc_bc934b9:
    // mov qword ptr [rbp+0x120], 0
    st->slot<uint64_t>(0x120) = 0;
    // mov qword ptr [rbp+0x128], 0xF
    st->slot<uint64_t>(0x128) = 0xF;
    // mov byte ptr [rbp+0x110], 0
    st->slot<uint8_t>(0x110) = 0;

    // 0xbc934d6..0xbc9351b
    // Cleanup std::string at [rbp+0x258] (size at [rbp+0x270], ptr at [rbp+0x258])
    rax = st->slot<uint64_t>(0x270);
    if (rax >= 0x10) {
        rcx = st->slot<uint64_t>(0x258);
        rdx = rax + 1;
        if (rdx < 0x1000) {
            sub_e935700(reinterpret_cast<void*>(rcx), rdx);
        } else {
            r8 = *reinterpret_cast<uint64_t*>(rcx - 8);
            rcx -= 8;
            rcx -= r8;
            if (rcx >= 0x20) goto abort_path;
            rax += 0x28;
            rdx = rax;
            rcx = r8;
            sub_e935700(reinterpret_cast<void*>(rcx), rdx);
        }
    }

    // loc_bc9351b:
    // 0xbc9351b..0xbc93560
    // Cleanup std::string at [rbp+0x358] (size at [rbp+0x370], ptr at [rbp+0x358])
    rax = st->slot<uint64_t>(0x370);
    if (rax >= 0x10) {
        rcx = st->slot<uint64_t>(0x358);
        rdx = rax + 1;
        if (rdx < 0x1000) {
            sub_e935700(reinterpret_cast<void*>(rcx), rdx);
        } else {
            r8 = *reinterpret_cast<uint64_t*>(rcx - 8);
            rcx -= 8;
            rcx -= r8;
            if (rcx >= 0x20) goto abort_path;
            rax += 0x28;
            rdx = rax;
            rcx = r8;
            sub_e935700(reinterpret_cast<void*>(rcx), rdx);
        }
    }

    // loc_bc93560:
    // 0xbc93560..0xbc935a5
    // Cleanup std::string at [rbp+0x328] (size at [rbp+0x340], ptr at [rbp+0x328])
    rax = st->slot<uint64_t>(0x340);
    if (rax >= 0x10) {
        rcx = st->slot<uint64_t>(0x328);
        rdx = rax + 1;
        if (rdx < 0x1000) {
            sub_e935700(reinterpret_cast<void*>(rcx), rdx);
        } else {
            r8 = *reinterpret_cast<uint64_t*>(rcx - 8);
            rcx -= 8;
            rcx -= r8;
            if (rcx >= 0x20) goto abort_path;
            rax += 0x28;
            rdx = rax;
            rcx = r8;
            sub_e935700(reinterpret_cast<void*>(rcx), rdx);
        }
    }

    // loc_bc935a5:
    // 0xbc935a5..0xbc935c4
    // Cleanup object at [rbp+0xB0] (refcounted, destroy if not r15)
    rcx = st->slot<uint64_t>(0xB0);
    if (rcx != 0) {
        // cmp rcx, r15
        // setne dl
        dl = (rcx != st->r15) ? 1 : 0;
        if (dl) {
            // mov rax, [rcx]
            // mov rax, [rax+0x20]
            // call qword ptr [0xF99FFA0]
            get_free_fn(*st)(reinterpret_cast<void*>(rcx));
        }
    }

    // loc_bc935c4:
    // 0xbc935c4..0xbc93603
    // Cleanup std::string at [rbp+0x50] (size at [rbp+0x68], ptr at [rbp+0x50])
    rax = st->slot<uint64_t>(0x68);
    if (rax >= 0x10) {
        rcx = st->slot<uint64_t>(0x50);
        rdx = rax + 1;
        if (rdx < 0x1000) {
            sub_e935700(reinterpret_cast<void*>(rcx), rdx);
        } else {
            r8 = *reinterpret_cast<uint64_t*>(rcx - 8);
            rcx -= 8;
            rcx -= r8;
            if (rcx >= 0x20) goto abort_path;
            rax += 0x28;
            rdx = rax;
            rcx = r8;
            sub_e935700(reinterpret_cast<void*>(rcx), rdx);
        }
    }

    // loc_bc93603:
    // 0xbc93603..0xbc93648
    // Cleanup std::string at [rbp+0x390] (size at [rbp+0x3A8], ptr at [rbp+0x390])
    rax = st->slot<uint64_t>(0x3A8);
    if (rax >= 0x10) {
        rcx = st->slot<uint64_t>(0x390);
        rdx = rax + 1;
        if (rdx < 0x1000) {
            sub_e935700(reinterpret_cast<void*>(rcx), rdx);
        } else {
            r8 = *reinterpret_cast<uint64_t*>(rcx - 8);
            rcx -= 8;
            rcx -= r8;
            if (rcx >= 0x20) goto abort_path;
            rax += 0x28;
            rdx = rax;
            rcx = r8;
            sub_e935700(reinterpret_cast<void*>(rcx), rdx);
        }
    }

    // loc_bc93648:
    // 0xbc93648..0xbc9368d
    // Cleanup std::string at [rbp+0x2E8] (size at [rbp+0x300], ptr at [rbp+0x2E8])
    rax = st->slot<uint64_t>(0x300);
    if (rax >= 0x10) {
        rcx = st->slot<uint64_t>(0x2E8);
        rdx = rax + 1;
        if (rdx < 0x1000) {
            sub_e935700(reinterpret_cast<void*>(rcx), rdx);
        } else {
            r8 = *reinterpret_cast<uint64_t*>(rcx - 8);
            rcx -= 8;
            rcx -= r8;
            if (rcx >= 0x20) goto abort_path;
            rax += 0x28;
            rdx = rax;
            rcx = r8;
            sub_e935700(reinterpret_cast<void*>(rcx), rdx);
        }
    }

    // loc_bc9368d:
    // 0xbc9368d..0xbc936d2
    // Cleanup std::string at [rbp+0x3D0] (size at [rbp+0x3E8], ptr at [rbp+0x3D0])
    rax = st->slot<uint64_t>(0x3E8);
    if (rax >= 0x10) {
        rcx = st->slot<uint64_t>(0x3D0);
        rdx = rax + 1;
        if (rdx < 0x1000) {
            sub_e935700(reinterpret_cast<void*>(rcx), rdx);
        } else {
            r8 = *reinterpret_cast<uint64_t*>(rcx - 8);
            rcx -= 8;
            rcx -= r8;
            if (rcx >= 0x20) goto abort_path;
            rax += 0x28;
            rdx = rax;
            rcx = r8;
            sub_e935700(reinterpret_cast<void*>(rcx), rdx);
        }
    }

    // loc_bc936d2:
    // 0xbc936d2..0xbc93706
    // Refcount decrement on r14 object, conditional free
    // mov rax, [rbp+0x30]
    rax = st->slot<uint64_t>(0x30);
    // lock dec dword ptr [rax]
    uint32_t* refcount = reinterpret_cast<uint32_t*>(rax);
    uint32_t new_count = _InterlockedDecrement(refcount);
    if (new_count != 0) {
        goto loc_bc93706;
    }
    // mov rsi, r14
    // add rsi, 0xC
    uint64_t rsi = st->r14 + 0xC;
    // mov rax, [r14]
    // mov rax, [rax]
    // mov rcx, r14
    // call qword ptr [0xF99FFA0]
    get_free_fn(*st)(reinterpret_cast<void*>(st->r14));
    // lock dec dword ptr [rsi]
    uint32_t* refcount2 = reinterpret_cast<uint32_t*>(rsi);
    uint32_t new_count2 = _InterlockedDecrement(refcount2);
    if (new_count2 != 0) {
        goto loc_bc93706;
    }
    // mov rax, [r14]
    // mov rax, [rax+8]
    // mov rcx, r14
    // call qword ptr [0xF99FFA0]
    get_free_fn(*st)(reinterpret_cast<void*>(st->r14));

    loc_bc93706:
    // 0xbc93706..0xbc93727
    // Epilogue: restore xmm6/xmm7, rsp, pops, ret
    st->xmm6 = *reinterpret_cast<__m128i*>(st->rbp + 0x410);
    st->xmm7 = *reinterpret_cast<__m128i*>(st->rbp + 0x420);
    // add rsp, 0x4B8; pop rbx; pop rdi; pop rsi; pop r12; pop r13; pop r14; pop r15; pop rbp; ret
    // Note: The actual stack unwinding is handled by the caller/trampoline
    return;

abort_path:
    // 0xbc93980..0xbc93a21
    // Abort path: native boundary calls
    // mov qword ptr [rsp+0x20], 0
    // xor ecx, ecx; xor edx, edx; xor r8d, r8d; xor r9d, r9d
    // call qword ptr [0xF9A8C78]
    get_abort_fn(*st)(0, 0, 0, 0);
    // lea rcx, [0x12AE1CC0]
    // call 0xE938CB0
    sub_e938cb0(reinterpret_cast<void*>(0x12AE1CC0));
    // cmp dword ptr [0x12AE1CC0], 0xFFFFFFFF
    // jne 0xBC8EBFC
    if (*reinterpret_cast<uint32_t*>(0x12AE1CC0) != 0xFFFFFFFF) {
        // Jump to sub_bc8ebfc - not in this chunk
        return;
    }
    // lea rdx, [0xF5BD4D0] "Native"
    // lea rcx, [rbp+0x110]
    // call 0x79580
    sub_79580(reinterpret_cast<void*>(st->rbp + 0x110), reinterpret_cast<void*>(0xF5BD4D0));
    // nop
    // lea rdx, [0xF7D20C6] "LimitedAt128"
    // lea rcx, [rbp+0x50]
    // call 0x79580
    sub_79580(reinterpret_cast<void*>(st->rbp + 0x50), reinterpret_cast<void*>(0xF7D20C6));
    // nop
    // lea rcx, [rbp+0x50]
    // lea rdx, [rbp+0x110]
    // call 0xBC95DB0
    sub_bc95db0(reinterpret_cast<void*>(st->rbp + 0x50), reinterpret_cast<void*>(st->rbp + 0x110));
    // nop
    // lea rcx, [rbp+0x50]
    // call 0x73150
    sub_73150(reinterpret_cast<void*>(st->rbp + 0x50));
    // lea rcx, [rbp+0x110]
    // call 0x73150
    sub_73150(reinterpret_cast<void*>(st->rbp + 0x110));
    // lea rcx, [0xBC961D0]
    // call 0xE935740
    sub_e935740(reinterpret_cast<void*>(0xBC961D0));
    // lea rcx, [0x12AE1CC0]
    // call 0xE938D70
    sub_e938d70(reinterpret_cast<void*>(0x12AE1CC0));
    // mov r12, [rbp+0x400]
    // jmp 0xBC8EBFC
    st->r12 = st->slot<uint64_t>(0x400);
    return; // Jump to sub_bc8ebfc - not in this chunk
}

} // namespace native

LIFT_FN(sub_bc8eb90, chunk_bc8eb90_c03);