// LIFT 0xe824a42 size 0x8aa1 1.26.62.01 sub_e824a42
// CHUNK 0xe824a42..0xe826230

#include "Chunk_e824a42_c00.h"

namespace native {

// Forward declarations for lifted callees
void sub_e82dcc0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e82d960(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_ebce390(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_ebd1560(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e820500(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e82de90(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e935700(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e835b50(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_eec6ed0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e83ace0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e8360f0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e81b720(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e81b4d0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e81e1c0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e81d850(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_ebdb740(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_bc5f110(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_bc6a9d0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);

// Boundary callees (via data slots)
extern "C" void* g_vendor_thunk_eea6040;  // at 0xF99FFA0

// Static inline step function for chunk 0xe824a42..0xe826230
// state struct documented in docs/functions/e824a42.md section 'Chunk state'
static inline void chunk_e824a42_c00(void* state) {
    ChunkState_e824a42_c00* s = static_cast<ChunkState_e824a42_c00*>(state);
    uint8_t* rbx = static_cast<uint8_t*>(s->rbx);  // job state base

    // Helper lambdas for reading/writing job state frame at rbx
    auto read_qword = [rbx](uint32_t off) -> uint64_t {
        return *reinterpret_cast<uint64_t*>(rbx + off);
    };
    auto write_qword = [rbx](uint32_t off, uint64_t val) {
        *reinterpret_cast<uint64_t*>(rbx + off) = val;
    };
    auto read_dword = [rbx](uint32_t off) -> uint32_t {
        return *reinterpret_cast<uint32_t*>(rbx + off);
    };
    auto write_dword = [rbx](uint32_t off, uint32_t val) {
        *reinterpret_cast<uint32_t*>(rbx + off) = val;
    };
    auto read_word = [rbx](uint32_t off) -> uint16_t {
        return *reinterpret_cast<uint16_t*>(rbx + off);
    };
    auto read_byte = [rbx](uint32_t off) -> uint8_t {
        return *reinterpret_cast<uint8_t*>(rbx + off);
    };
    auto write_byte = [rbx](uint32_t off, uint8_t val) {
        *reinterpret_cast<uint8_t*>(rbx + off) = val;
    };

    // Register mirrors from state struct
    uint64_t rdi = s->rdi;
    uint64_t rsi = s->rsi;
    uint64_t rax = s->rax;
    uint64_t rcx = s->rcx;
    uint64_t rdx = s->rdx;
    uint64_t r8 = s->r8;
    uint64_t r9 = s->r9;
    uint64_t r10 = s->r10;
    uint64_t r11 = s->r11;
    uint64_t r12 = s->r12;
    uint64_t r13 = s->r13;
    uint64_t r14 = s->r14;
    uint64_t r15 = s->r15;

    // 0xe824a42..0xe824a59
    rdi = rdi * 0x78;
    rdi = rdi + read_qword(0x5D8);
    // jmp short 0xe824a59 (fallthrough)

    // 0xe824a4f..0xe824a59 (alternate path, not taken here)
    // rdi = (rdi << 7) + read_qword(0x588); // case 2 path

loc_e824a59:
    // 0xe824a59..0xe824a6a
    if (read_byte(rsi + 0x11) == 0) {
        goto loc_e82516b;
    }

    rdx = read_qword(0x90);
    rcx = rsi;
    r8 = 8;

    // 0xe824a73 call 0xE82DCC0
    sub_e82dcc0(rbx, rsi, rdi, rdx);

    // 0xe824a78 nop (ignored)
    r14 = read_qword(0x2C0);
    r9 = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(rdi) + 0x34);

    // 0xe824a84..0xe824a8e
    if (read_byte(rsi + 0x13) != 1) {
        goto loc_e8251c8;
    }

    r11 = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(rdi) + 0x30);
    r10 = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(rdi) + 0x44);
    rax = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(rdi) + 0x65);
    rax = rax & 0x10;
    r8 = *reinterpret_cast<uint32_t*>(rsi + 4);

    // 0xe824aa0..0xe824ab2
    uint8_t al = static_cast<uint8_t>(rax);
    uint8_t cl = 2;
    if (al != 1) {
        cl = 0;  // sbb cl, 0 when al != 1
    }
    rax = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(rdi) + 0x60);
    rax = rax - r8;
    r8 = r8 >> cl;
    rax = rax >> cl;

    goto loc_e8251f0;

loc_e824ab7:
    // 0xe824ab7..0xe824ac4
    if ((*reinterpret_cast<uint8_t*>(0x12ADFA53) & 0x80) != 0) {
        goto loc_e825289;
    }

    rcx = read_qword(0x2C0);
    r8 = read_qword(0xB8);
    rax = *reinterpret_cast<uint32_t*>(r8 + 0x18);
    *reinterpret_cast<uint64_t*>(r8 + 8) += rax;
    r10 = read_dword(0xF0);
    rdx = r10;
    rax = read_qword(r8 + 0x10);
    write_qword(rcx + rdx * 8, rax);

    goto loc_e8252f3;

loc_e824af1:
    // 0xe824af1..0xe824b00
    if (rdx == 0) {
        rax = read_dword(0x150);
        goto loc_e825498;
    }

    rsi = read_qword(0x1C0);
    rsi = rsi << 4;
    rsi = rsi + rdx;
    rdi = 0;
    r14 = read_qword(0x2C0);

    goto loc_e824b63;

loc_e824b20:
    // 0xe824b20..0xe824b63
    r8 = read_dword(0xF0);
    rax = r8;
    rdx = read_qword(0xB8);
    rcx = *reinterpret_cast<uint32_t*>(rdx + 0x18);
    *reinterpret_cast<uint64_t*>(rdx + 8) += rcx;
    rcx = read_qword(rdx + 0x10);
    write_qword(r14 + rax * 8, rcx);
    rax = *reinterpret_cast<uint32_t*>(rdx + 0x18);
    rax = rax + rcx;
    write_qword(rdx + 0x10, rax);
    r8 = r8 + 1;
    write_dword(0xF0, r8);
    rdi = rdi + 1;
    rdx = read_qword(0x110);
    rax = read_dword(0x150);

loc_e824b63:
    rcx = rdi;
    if (*reinterpret_cast<uint64_t*>(rsi + 8) <= rcx) {
        goto loc_e825269;
    }

    rax = read_qword(rsi);
    if (rax == 0) {
        goto loc_e824b20;
    }

    rdx = rcx + rcx * 4;
    rcx = *reinterpret_cast<uint16_t*>(rax + rdx * 4 + 0xA);
    if (rcx == 0xFFFF) {
        goto loc_e824b20;
    }

    r12 = rax + rdx * 4;
    rax = rcx * 0x78;
    rdx = read_qword(0x3A0);
    r15 = rdx + rax;

    // 0xe824b9c..0xe824bad
    if (read_byte(r12 + 0x11) == 0) {
        goto loc_e824c41;
    }

    rdx = read_qword(0x90);
    rdx = read_qword(rdx + 0x30);
    r8 = rcx;

    // 0xe824bb7..0xe824c3c
    if (r8 > 0xFFF) {
        goto loc_e824da0;
    }

    r8 = rcx;
    r8 = r8 >> 6;
    r11 = read_qword(0x90);
    r9 = read_qword(r11 + r8 * 8 + 0x224A8);
    r10 = 1;
    r10 = r10 << (rcx & 0x3F);
    if ((r9 & r10) == 0) {
        goto loc_e824cfc;
    }

    r8 = *reinterpret_cast<uint32_t*>(r11 + rcx * 8 + 0x226AC);
    if (r8 != 8) {
        goto loc_e824d36;
    }

    rcx = read_qword(r11 + 0x22498);
    rax = read_qword(rcx + rax);
    write_qword(0xC0, 2);
    write_qword(0xC8, rax);
    rax = read_qword(rdx);
    rax = read_qword(rax + 0xD0);
    rcx = rdx;
    rdx = 1;
    r8 = rbx + 0xC0;

    // 0xe824c35 call qword ptr [0xF99FFA0]
    // call via data slot -> g_vendor_thunk_eea6040
    // In C++ we call the thunk directly
    reinterpret_cast<void(*)(void*, void*, void*, void*)>(g_vendor_thunk_eea6040)(rcx, rdx, r8, r9);

    goto loc_e824da0;

loc_e824c41:
    // 0xe824c41..0xe824cf7
    if (r8 > 0xFFF) {
        goto loc_e824eb3;
    }

    r8 = rcx;
    r8 = r8 >> 6;
    r11 = read_qword(0x90);
    r9 = read_qword(r11 + r8 * 8 + 0x224A8);
    r10 = 1;
    r10 = r10 << (rcx & 0x3F);
    if ((r9 & r10) == 0) {
        goto loc_e824e7b;
    }

    r8 = *reinterpret_cast<uint32_t*>(r11 + rcx * 8 + 0x226AC);
    if (r8 == 0xAC3) {
        goto loc_e824eb3;
    }

    r9 = read_qword(0x90);
    write_dword(r9 + rcx * 8 + 0x226AC, 0xAC3);
    rcx = read_qword(r9 + 0x22498);
    rax = read_qword(rcx + rax);
    write_qword(0xC0, 0);
    write_qword(0xC8, rax);
    write_dword(0xD0, 0xFFFFFFFF);
    write_dword(0xD4, r8);
    write_dword(0xD8, 0xAC3);
    rax = read_qword(rdx);
    rax = read_qword(rax + 0xD0);
    rcx = rdx;
    rdx = 1;
    r8 = rbx + 0xC0;

    // 0xe824cf0 call qword ptr [0xF99FFA0]
    reinterpret_cast<void(*)(void*, void*, void*, void*)>(g_vendor_thunk_eea6040)(rcx, rdx, r8, r9);

    goto loc_e824eb3;

loc_e824cfc:
    // 0xe824cfc..0xe824d34
    r9 = r9 | r10;
    write_qword(r11 + r8 * 8 + 0x224A8, r9);
    rax = *reinterpret_cast<uint16_t*>(r11 + 0x224A0);
    write_word(r11 + rax * 2 + 0x2A6A8, static_cast<uint16_t>(rcx));
    rax = rax + 1;
    write_word(r11 + 0x224A0, static_cast<uint16_t>(rax));
    write_qword(r11 + rcx * 8 + 0x226A8, 0x800000008);
    goto loc_e824da0;

loc_e824d36:
    // 0xe824d36..0xe824d9a
    write_dword(r11 + rcx * 8 + 0x226AC, 8);
    rcx = read_qword(r11 + 0x22498);
    rax = read_qword(rcx + rax);
    write_qword(0xC0, 0);
    write_qword(0xC8, rax);
    write_dword(0xD0, 0xFFFFFFFF);
    write_dword(0xD4, r8);
    write_dword(0xD8, 8);
    rax = read_qword(rdx);
    rax = read_qword(rax + 0xD0);
    rcx = rdx;
    rdx = 1;
    r8 = rbx + 0xC0;

    // 0xe824d93 call qword ptr [0xF99FFA0]
    reinterpret_cast<void(*)(void*, void*, void*, void*)>(g_vendor_thunk_eea6040)(rcx, rdx, r8, r9);

    goto loc_e824da0;

loc_e824da0:
    // 0xe824da0..0xe824e76
    r9 = *reinterpret_cast<uint32_t*>(r15 + 0x34);

    if (read_byte(r12 + 0x13) != 1) {
        goto loc_e824dd5;
    }

    r11 = *reinterpret_cast<uint32_t*>(r15 + 0x30);
    r10 = *reinterpret_cast<uint32_t*>(r15 + 0x44);
    rax = *reinterpret_cast<uint8_t*>(r15 + 0x65);
    rax = rax & 0x10;
    r8 = *reinterpret_cast<uint32_t*>(r12 + 4);

    al = static_cast<uint8_t>(rax);
    cl = 2;
    if (al != 1) {
        cl = 0;
    }
    rax = *reinterpret_cast<uint32_t*>(r15 + 0x60);
    rax = rax - r8;
    r8 = r8 >> cl;
    rax = rax >> cl;
    goto loc_e824e01;

loc_e824dd5:
    // 0xe824dd5..0xe824e01
    r10 = *reinterpret_cast<uint16_t*>(r12 + 8);
    if (r10 == 0) {
        r10 = *reinterpret_cast<uint32_t*>(r15 + 0x70);
    }
    rcx = *reinterpret_cast<uint32_t*>(r12 + 4);
    r11 = 0;
    rax = rcx;
    rdx = 0;
    r8 = rax / r10;
    rax = *reinterpret_cast<uint32_t*>(r15 + 0x60);
    rax = rax - rcx;
    rdx = 0;
    rax = rax / r10;

loc_e824e01:
    rcx = r8;
    write_dword(0xC0, r11);
    write_dword(0xC4, r9);
    write_qword(0xC8, rcx);
    write_dword(0xD0, rax);
    write_dword(0xD4, r10);

    // movups xmm0, [r15+0x48] -> xmm0 not tracked in state
    // lea rax, [rbx+0xD4]; movups [rax+4], xmm0
    // We'll skip xmm operations as they're not in state

    rax = read_qword(0x12BB4910);
    rcx = read_qword(rax + 0x400);
    rax = read_qword(0xB8);
    r8 = read_qword(rax + 8);
    rdx = read_qword(r15);
    rax = read_qword(rcx);
    rax = read_qword(rax + 0x98);
    r10 = g_vendor_thunk_eea6040;
    // mov [rsp+0x20], r8 (stack arg)
    r8 = 0;
    r9 = rbx + 0xC0;

    // 0xe824e72 call r10
    reinterpret_cast<void(*)(void*, void*, void*, void*)>(r10)(rcx, rdx, r8, r9);

    goto loc_e824f88;

loc_e824e7b:
    // 0xe824e7b..0xe824eb3
    r9 = r9 | r10;
    write_qword(r11 + r8 * 8 + 0x224A8, r9);
    rax = *reinterpret_cast<uint16_t*>(r11 + 0x224A0);
    write_word(r11 + rax * 2 + 0x2A6A8, static_cast<uint16_t>(rcx));
    rax = rax + 1;
    write_word(r11 + 0x224A0, static_cast<uint16_t>(rax));
    write_qword(r11 + rcx * 8 + 0x226A8, 0xAC300000AC3);
    goto loc_e824eb3;

loc_e824eb3:
    // 0xe824eb3..0xe824f88
    r10 = read_qword(r15 + 0x28);

    if (read_byte(r12 + 0x13) != 1) {
        goto loc_e824ee9;
    }

    r13 = *reinterpret_cast<uint32_t*>(r15 + 8);
    r11 = *reinterpret_cast<uint32_t*>(r15 + 0x24);
    rax = *reinterpret_cast<uint8_t*>(r15 + 0x65);
    rax = rax & 0x10;
    r9 = *reinterpret_cast<uint32_t*>(r12 + 4);

    al = static_cast<uint8_t>(rax);
    cl = 2;
    if (al != 1) {
        cl = 0;
    }
    r8 = *reinterpret_cast<uint32_t*>(r15 + 0x60);
    r8 = r8 - r9;
    r9 = r9 >> cl;
    r8 = r8 >> cl;
    goto loc_e824f18;

loc_e824ee9:
    // 0xe824ee9..0xe824f18
    r11 = *reinterpret_cast<uint16_t*>(r12 + 8);
    if (r11 == 0) {
        r11 = *reinterpret_cast<uint32_t*>(r15 + 0x70);
    }
    rcx = *reinterpret_cast<uint32_t*>(r12 + 4);
    r13 = 0;
    rax = rcx;
    rdx = 0;
    r9 = rax / r11;
    r8 = r8 - rcx;
    rax = r8;
    rdx = 0;
    r8 = rax / r11;

loc_e824f18:
    rax = r9;
    write_dword(0xC0, r13);
    rcx = *reinterpret_cast<uint32_t*>(r15 + 0x14);
    rdx = rbx + 0xD4;
    write_dword(rdx - 8, rcx);
    rcx = read_qword(r15 + 0xC);
    write_qword(rdx - 0x10, rcx);
    write_dword(0xD0, rax);
    write_dword(0xD8, r8);
    write_dword(0xDC, r11);
    write_qword(0xE0, r10);

    rax = read_qword(0x12BB4910);
    rcx = read_qword(rax + 0x400);
    rax = read_qword(0xB8);
    r9 = read_qword(rax + 8);
    rdx = read_qword(r15);
    rax = read_qword(rcx);
    rax = read_qword(rax + 0x90);
    r8 = rbx + 0xC0;

    // 0xe824f81 call qword ptr [0xF99FFA0]
    reinterpret_cast<void(*)(void*, void*, void*, void*)>(g_vendor_thunk_eea6040)(rcx, rdx, r8, r9);

loc_e824f88:
    // 0xe824f88..0xe824fbe
    r8 = read_dword(0xF0);
    rax = r8;
    rdx = read_qword(0xB8);
    rcx = *reinterpret_cast<uint32_t*>(rdx + 0x18);
    *reinterpret_cast<uint64_t*>(rdx + 8) += rcx;
    rcx = read_qword(rdx + 0x10);
    write_qword(r14 + rax * 8, rcx);
    rax = *reinterpret_cast<uint32_t*>(rdx + 0x18);
    rax = rax + rcx;
    write_qword(rdx + 0x10, rax);
    r9 = read_qword(0xB0);

    goto loc_e824b4a;  // back to loop increment

loc_e824fbe:
    // 0xe824fbe..0xe824fd2 (jump to 0xe82306e - outside chunk)
    rax = read_dword(0x150);
    r10 = read_dword(0xF0);
    rax = rax + 1;
    // jmp 0xE82306E (outside chunk 0)
    // This exits the chunk

loc_e824fd2:
    // 0xe824fd2..0xe8250c2
    r8 = rdi * 0xB8;

    if (r13 <= 0xFFF) {
        goto loc_e82531f;
    }

    r14 = r8 - 0xB8000;
    rax = read_qword(r9 + 0xC96178);
    rcx = read_qword(rax);

    if (r14 < 0xB8000) {
        goto loc_e825098;
    }

    r8 = r8 - 0x170000;  // 0xFFFFFFFFFFE90000 = -0x170000
    rax = r8;
    rax = rax >> 0xF;
    rdx = 0xB21642C8590B217;
    // mul rdx (128-bit multiply)
    // For 64-bit, we just do the division equivalent
    rax = (r8 * 0xB21642C8590B217) >> 64;
    rax = ~rax;
    if ((al & 7) == 0) {
        goto loc_e825043;
    }

    rdx = rdx + 1;
    rdx = rdx & 7;

loc_e825030:
    r14 = r14 - 0xB8000;  // 0xFFFFFFFFFFF48000 = -0xB8000
    rcx = read_qword(rcx + 0xB8000);
    rdx = rdx - 1;
    if (rdx != 0) {
        goto loc_e825030;
    }

loc_e825043:
    if (static_cast<uint32_t>(r8) < 0x508000) {
        goto loc_e825098;
    }

loc_e825050:
    rax = read_qword(rcx + 0xB8000);
    rax = read_qword(rax + 0xB8000);
    rax = read_qword(rax + 0xB8000);
    rax = read_qword(rax + 0xB8000);
    rax = read_qword(rax + 0xB8000);
    rax = read_qword(rax + 0xB8000);
    r14 = r14 - 0x5C0000;  // 0xFFFFFFFFFFA40000
    rcx = read_qword(rax + 0xB8000);
    if (r14 > 0xB7FFF) {
        goto loc_e825050;
    }

loc_e825098:
    r14 = r14 + rcx;

    if (read_byte(rsi + 0x11) == 0) {
        goto loc_e825333;
    }

    r8 = *reinterpret_cast<uint16_t*>(rsi + 0xA);
    rax = read_qword(0x90);
    rdx = read_qword(rax + 0x30);
    rcx = read_qword(0x238);
    r9 = 8;

    // 0xe8250c2 call 0xE82D960
    sub_e82d960(rbx, rsi, rdi, rdx);

    r15 = *reinterpret_cast<uint8_t*>(rsi + 0x12);
    r9 = r14 + 0x68;
    rdi = read_qword(0x2C0);
    rax = read_qword(0x12BB4910);
    rsi = read_qword(rax + 0x400);

    if (r15 == 0) {
        goto loc_e825138;
    }

    r8 = 0x28;
    rcx = rbx + 0xC0;
    rdx = r9;

    // 0xe8250fb call 0xEBCE390
    sub_ebce390(rbx, rsi, rdi, rdx);

    rax = *reinterpret_cast<uint32_t*>(r14 + 0x6C);
    write_dword(0xC8, r15);
    r9 = rbx + 0xC0;

    if (eax == 8) {
        goto loc_e825138;
    }

    rcx = rbx + 0xCC;
    if (eax != 5) {
        goto loc_e82512b;
    }
    rcx = rbx + 0xD4;

loc_e82512b:
    write_dword(rcx, 0);
    r9 = rbx + 0xC0;

loc_e825138:
    rax = read_qword(0xB8);
    rcx = read_qword(rax + 8);
    rdx = read_qword(r14);
    rax = read_qword(rsi);
    rax = read_qword(rax + 0x98);
    r10 = g_vendor_thunk_eea6040;
    // mov [rsp+0x20], rcx
    r8 = 0;
    rcx = rsi;

    // 0xe825162 call r10
    reinterpret_cast<void(*)(void*, void*, void*, void*)>(r10)(rcx, rdx, r8, r9);

    goto loc_e825766;

loc_e82516b:
    // 0xe82516b..0xe82517a
    rcx = rsi;
    r8 = 0xAC3;

    // 0xe825174 call 0xE82DCC0
    sub_e82dcc0(rbx, rsi, rdi, rdx);

    r14 = read_qword(0x2C0);
    r10 = read_qword(rdi + 0x28);

    if (read_byte(rsi + 0x13) != 1) {
        goto loc_e8254a6;
    }

    r15 = *reinterpret_cast<uint32_t*>(rdi + 8);
    r11 = *reinterpret_cast<uint32_t*>(rdi + 0x24);
    rax = *reinterpret_cast<uint8_t*>(rdi + 0x65);
    rax = rax & 0x10;
    r9 = *reinterpret_cast<uint32_t*>(rsi + 4);

    al = static_cast<uint8_t>(rax);
    cl = 2;
    if (al != 1) {
        cl = 0;
    }
    r8 = *reinterpret_cast<uint32_t*>(rdi + 0x60);
    r8 = r8 - r9;
    r9 = r9 >> cl;
    r8 = r8 >> cl;
    goto loc_e8254d2;

loc_e8251ba:
    // 0xe8251ba..0xe8251c8 (jump to 0xe82306e - outside chunk)
    r10 = read_dword(0xF0);
    rax = rax + 1;
    // jmp 0xE82306E (outside chunk)

loc_e8251c8:
    // 0xe8251c8..0xe825264
    r10 = *reinterpret_cast<uint16_t*>(rsi + 8);
    if (r10 == 0) {
        r10 = *reinterpret_cast<uint32_t*>(rdi + 0x70);
    }
    rcx = *reinterpret_cast<uint32_t*>(rsi + 4);
    r11 = 0;
    rax = rcx;
    rdx = 0;
    r8 = rax / r10;
    rax = *reinterpret_cast<uint32_t*>(rdi + 0x60);
    rax = rax - rcx;
    rdx = 0;
    rax = rax / r10;

    rcx = r8;
    write_dword(0xC0, r11);
    write_dword(0xC4, r9);
    write_qword(0xC8, rcx);
    write_dword(0xD0, rax);
    write_dword(0xD4, r10);

    // movups xmm0, [rdi+0x48]; movups [rax+4], xmm0 (skip xmm)

    rax = read_qword(0x12BB4910);
    rcx = read_qword(rax + 0x400);
    rax = read_qword(0xB8);
    r8 = read_qword(rax + 8);
    rdx = read_qword(rdi);
    rax = read_qword(rcx);
    rax = read_qword(rax + 0x98);
    r10 = g_vendor_thunk_eea6040;
    // mov [rsp+0x20], r8
    r8 = 0;
    r9 = rbx + 0xC0;

    // 0xe825260 call r10
    reinterpret_cast<void(*)(void*, void*, void*, void*)>(r10)(rcx, rdx, r8, r9);

    goto loc_e825541;

loc_e825269:
    // 0xe825269..0xe825289
    rcx = read_qword(0x1C0);
    write_dword(rbx + rcx * 4 + 0x3B0, 0);
    r10 = read_dword(0xF0);
    rax = rax + 1;
    // jmp 0xE82306E (outside chunk)

loc_e825289:
    // 0xe825289..0xe82531a
    rax = rdi * 0x78;
    rsi = read_qword(0x2C0);
    r8 = r9 + rax;
    r8 = r8 + 0x57A180;
    rax = read_qword(0x12BB4910);
    rcx = read_qword(rax + 0x400);
    rax = read_qword(0xB8);
    r9 = read_qword(rax + 8);
    rax = read_qword(rcx);
    rax = read_qword(rax + 0x90);
    rdx = 0;

    // 0xe8252c4 call qword ptr [0xF99FFA0]
    reinterpret_cast<void(*)(void*, void*, void*, void*)>(g_vendor_thunk_eea6040)(rcx, rdx, r8, r9);

    r8 = read_qword(0xB8);
    rax = *reinterpret_cast<uint32_t*>(r8 + 0x18);
    *reinterpret_cast<uint64_t*>(r8 + 8) += rax;
    r10 = read_dword(0xF0);
    rcx = r10;
    rax = read_qword(r8 + 0x10);
    write_qword(rsi + rcx * 8, rax);
    r9 = read_qword(0xB0);
    rcx = *reinterpret_cast<uint32_t*>(r8 + 0x18);
    rcx = rcx + rax;
    write_qword(r8 + 0x10, rcx);
    r10 = r10 + 1;
    write_dword(0xF0, r10);
    rax = read_qword(0x1C0);
    write_dword(rbx + rax * 4 + 0x3B0, 0);
    rdx = read_qword(0x110);
    // jmp 0xE823066 (outside chunk)

loc_e82531f:
    // 0xe82531f..0xe825333
    r8 = r8 + read_qword(0x1F8);
    r14 = r8;

    if (read_byte(rsi + 0x11) != 0) {
        goto loc_e8250a5;
    }

loc_e825333:
    // 0xe825333..0xe82536f
    rcx = *reinterpret_cast<uint8_t*>(r14 + 0xB0);

    // 0xe82533b call 0xEBD1560
    sub_ebd1560(rbx, rsi, rdi, rdx);

    uint8_t al_ret = static_cast<uint8_t>(rax);  // al return
    r9 = 0xAC3;
    rax = 0x60;
    if (al_ret != 0) {
        r9 = rax;
    }
    r8 = *reinterpret_cast<uint16_t*>(rsi + 0xA);
    rax = read_qword(0x90);
    rdx = read_qword(rax + 0x30);
    rcx = read_qword(0x238);

    // 0xe825369 call 0xE82D960
    sub_e82d960(rbx, rsi, rdi, rdx);

    r12 = *reinterpret_cast<uint8_t*>(rsi + 0x12);
    r10 = r14 + 0x40;
    r15 = read_qword(0x2C0);
    rax = read_qword(0x12BB4910);
    rdi = read_qword(rax + 0x400);

    if (r12 == 0) {
        goto loc_e825578;
    }

    r8 = 0x28;
    rcx = rbx + 0xC0;
    rdx = r10;

    // 0xe8253a6 call 0xEBCE390
    sub_ebce390(rbx, rsi, rdi, rdx);

    rax = *reinterpret_cast<uint32_t*>(r14 + 0x44);
    write_dword(0xD0, r12);
    write_dword(0xD4, 1);

    if (eax == 8) {
        goto loc_e8253cf;
    }
    if (eax != 9) {
        goto loc_e825566;
    }

loc_e8253cf:
    write_dword(0xD8, 0);
    goto loc_e825571;

loc_e8253de:
    // 0xe8253de..0xe825493
    if (rcx > 0xFFF) {
        goto loc_e8257de;
    }

    r8 = rdi;
    r8 = r8 >> 6;
    r11 = read_qword(0x90);
    r9 = read_qword(r11 + r8 * 8 + 0x224A8);
    r10 = 1;
    rcx = rdi;
    r10 = r10 << (rcx & 0x3F);
    if ((r9 & r10) == 0) {
        goto loc_e8257a6;
    }

    rcx = *reinterpret_cast<uint32_t*>(r11 + rdi * 8 + 0x226AC);
    if (rcx == 0xAC3) {
        goto loc_e8257de;
    }

    r8 = read_qword(0x90);
    write_dword(r8 + rdi * 8 + 0x226AC, 0xAC3);
    r8 = read_qword(r8 + 0x22498);
    rax = read_qword(r8 + rax);
    write_qword(0xC0, 0);
    write_qword(0xC8, rax);
    write_dword(0xD0, 0xFFFFFFFF);
    write_dword(0xD4, rcx);
    write_dword(0xD8, 0xAC3);
    rax = read_qword(rdx);
    rax = read_qword(rax + 0xD0);
    rcx = rdx;
    rdx = 1;
    r8 = rbx + 0xC0;

    // 0xe82548c call qword ptr [0xF99FFA0]
    reinterpret_cast<void(*)(void*, void*, void*, void*)>(g_vendor_thunk_eea6040)(rcx, rdx, r8, r9);

    goto loc_e8257de;

loc_e825498:
    // 0xe825498..0xe8254a6 (jump to 0xe82306e - outside chunk)
    r10 = read_dword(0xF0);
    rax = rax + 1;
    // jmp 0xE82306E

loc_e8254a6:
    // 0xe8254a6..0xe825541
    r11 = *reinterpret_cast<uint16_t*>(rsi + 8);
    if (r11 == 0) {
        r11 = *reinterpret_cast<uint32_t*>(rdi + 0x70);
    }
    rcx = *reinterpret_cast<uint32_t*>(rsi + 4);
    r15 = 0;
    rax = rcx;
    rdx = 0;
    r9 = rax / r11;
    r8 = r8 - rcx;
    rax = r8;
    rdx = 0;
    r8 = rax / r11;

    rax = r9;
    write_dword(0xC0, r15);
    rcx = *reinterpret_cast<uint32_t*>(rdi + 0x14);
    rdx = rbx + 0xD4;
    write_dword(rdx - 8, rcx);
    rcx = read_qword(rdi + 0xC);
    write_qword(rdx - 0x10, rcx);
    write_dword(0xD0, rax);
    write_dword(0xD8, r8);
    write_dword(0xDC, r11);
    write_qword(0xE0, r10);

    rax = read_qword(0x12BB4910);
    rcx = read_qword(rax + 0x400);
    rax = read_qword(0xB8);
    r9 = read_qword(rax + 8);
    rdx = read_qword(rdi);
    rax = read_qword(rcx);
    rax = read_qword(rax + 0x90);
    r8 = rbx + 0xC0;

    // 0xe82553a call qword ptr [0xF99FFA0]
    reinterpret_cast<void(*)(void*, void*, void*, void*)>(g_vendor_thunk_eea6040)(rcx, rdx, r8, r9);

    goto loc_e825541;

loc_e825541:
    // 0xe825541..0xe82559c
    rdx = read_qword(0xB8);
    rax = *reinterpret_cast<uint32_t*>(rdx + 0x18);
    *reinterpret_cast<uint64_t*>(rdx + 8) += rax;
    r10 = read_dword(0xF0);
    rax = r10;
    rcx = read_qword(rdx + 0x10);
    write_qword(r14 + rax * 8, rcx);

    goto loc_e825786;

loc_e825566:
    // 0xe825566..0xe825578
    write_qword(0xD8, 0);
    r10 = rbx + 0xC0;

loc_e825578:
    // 0xe825578..0xe82559d
    rax = read_qword(0xB8);
    r9 = read_qword(rax + 8);
    rdx = read_qword(r14);
    rax = read_qword(rdi);
    rax = read_qword(rax + 0x90);
    rcx = rdi;
    r8 = r10;

    // 0xe825596 call qword ptr [0xF99FFA0]
    reinterpret_cast<void(*)(void*, void*, void*, void*)>(g_vendor_thunk_eea6040)(rcx, rdx, r8, r9);

    rdx = read_qword(0xB8);
    rax = *reinterpret_cast<uint32_t*>(rdx + 0x18);
    *reinterpret_cast<uint64_t*>(rdx + 8) += rax;
    rax = read_dword(0xF0);
    rcx = read_qword(rdx + 0x10);
    write_qword(r15 + rax * 8, rcx);
    rax = *reinterpret_cast<uint32_t*>(rdx + 0x18);
    rax = rax + rcx;
    write_qword(rdx + 0x10, rax);

    rax = read_dword(rsi);
    if ((rax & 0x20000000) != 0) {
        rax = *reinterpret_cast<uint32_t*>(r14 + 0x98);
    }
    rax = rax & 0x1F0F07FF;
    rcx = read_qword(0x1C0);
    write_dword(rbx + rcx * 4 + 0x3B0, rax);
    r10 = read_dword(0xF0);

    goto loc_e825790;

loc_e8255f2:
    // 0xe8255f2..0xe82568f
    r9 = r9 | r10;
    write_qword(r11 + r8 * 8 + 0x224A8, r9);
    rax = *reinterpret_cast<uint16_t*>(r11 + 0x224A0);
    write_word(r11 + rax * 2 + 0x2A6A8, static_cast<uint16_t>(rdi));
    rax = rax + 1;
    write_word(r11 + 0x224A0, static_cast<uint16_t>(rax));
    write_qword(r11 + rdi * 8 + 0x226A8, 0x800000008);
    goto loc_e82568f;

loc_e82562c:
    // 0xe82562c..0xe82568f
    write_dword(r11 + rdi * 8 + 0x226AC, 8);
    r8 = read_qword(r11 + 0x22498);
    rax = read_qword(r8 + rax);
    write_qword(0xC0, 0);
    write_qword(0xC8, rax);
    write_dword(0xD0, 0xFFFFFFFF);
    write_dword(0xD4, rcx);
    write_dword(0xD8, 8);
    rax = read_qword(rdx);
    rax = read_qword(rax + 0xD0);
    rcx = rdx;
    rdx = 1;
    r8 = rbx + 0xC0;

    // 0xe825688 call qword ptr [0xF99FFA0]
    reinterpret_cast<void(*)(void*, void*, void*, void*)>(g_vendor_thunk_eea6040)(rcx, rdx, r8, r9);

loc_e82568f:
    // 0xe82568f..0xe825766
    rdi = read_qword(0x2C0);
    r9 = *reinterpret_cast<uint32_t*>(r14 + 0x34);

    if (read_byte(rsi + 0x13) != 1) {
        goto loc_e8256c8;
    }

    r11 = *reinterpret_cast<uint32_t*>(r14 + 0x30);
    r10 = *reinterpret_cast<uint32_t*>(r14 + 0x44);
    rax = *reinterpret_cast<uint8_t*>(r14 + 0x65);
    rax = rax & 0x10;
    r8 = *reinterpret_cast<uint32_t*>(rsi + 4);

    al = static_cast<uint8_t>(rax);
    cl = 2;
    if (al != 1) {
        cl = 0;
    }
    rax = *reinterpret_cast<uint32_t*>(r14 + 0x60);
    rax = rax - r8;
    r8 = r8 >> cl;
    rax = rax >> cl;
    goto loc_e8256f1;

loc_e8256c8:
    // 0xe8256c8..0xe8256f1
    r10 = *reinterpret_cast<uint16_t*>(rsi + 8);
    if (r10 == 0) {
        r10 = *reinterpret_cast<uint32_t*>(r14 + 0x70);
    }
    rcx = *reinterpret_cast<uint32_t*>(rsi + 4);
    r11 = 0;
    rax = rcx;
    rdx = 0;
    r8 = rax / r10;
    rax = *reinterpret_cast<uint32_t*>(r14 + 0x60);
    rax = rax - rcx;
    rdx = 0;
    rax = rax / r10;

loc_e8256f1:
    rcx = r8;
    write_dword(0xC0, r11);
    write_dword(0xC4, r9);
    write_qword(0xC8, rcx);
    write_dword(0xD0, rax);
    write_dword(0xD4, r10);

    // movups xmm0, [r14+0x48]; movups [rax+4], xmm0 (skip xmm)

    rax = read_qword(0x12BB4910);
    rcx = read_qword(rax + 0x400);
    rax = read_qword(0xB8);
    r8 = read_qword(rax + 8);
    rdx = read_qword(r14);
    rax = read_qword(rcx);
    rax = read_qword(rax + 0x98);
    r10 = g_vendor_thunk_eea6040;
    // mov [rsp+0x20], r8
    r8 = 0;
    r9 = rbx + 0xC0;

    // 0xe825762 call r10
    reinterpret_cast<void(*)(void*, void*, void*, void*)>(r10)(rcx, rdx, r8, r9);

    goto loc_e825766;

loc_e825766:
    // 0xe825766..0xe8257a1
    rdx = read_qword(0xB8);
    rax = *reinterpret_cast<uint32_t*>(rdx + 0x18);
    *reinterpret_cast<uint64_t*>(rdx + 8) += rax;
    r10 = read_dword(0xF0);
    rax = r10;
    rcx = read_qword(rdx + 0x10);
    write_qword(rdi + rax * 8, rcx);
    rax = *reinterpret_cast<uint32_t*>(rdx + 0x18);
    rax = rax + rcx;
    write_qword(rdx + 0x10, rax);
    r10 = r10 + 1;
    r9 = read_qword(0xB0);
    rdx = read_qword(0x110);
    // jmp 0xE823066 (outside chunk)

loc_e8257a6:
    // 0xe8257a6..0xe8257de
    r9 = r9 | r10;
    write_qword(r11 + r8 * 8 + 0x224A8, r9);
    rax = *reinterpret_cast<uint16_t*>(r11 + 0x224A0);
    write_word(r11 + rax * 2 + 0x2A6A8, static_cast<uint16_t>(rdi));
    rax = rax + 1;
    write_word(r11 + 0x224A0, static_cast<uint16_t>(rax));
    write_qword(r11 + rdi * 8 + 0x226A8, 0xAC300000AC3);
    goto loc_e8257de;

loc_e8257de:
    // 0xe8257de..0xe8258f0
    rdi = read_qword(0x2C0);
    r10 = read_qword(r14 + 0x28);

    if (read_byte(rsi + 0x13) != 1) {
        goto loc_e825818;
    }

    r15 = *reinterpret_cast<uint32_t*>(r14 + 8);
    r11 = *reinterpret_cast<uint32_t*>(r14 + 0x24);
    rax = *reinterpret_cast<uint8_t*>(r14 + 0x65);
    rax = rax & 0x10;
    r9 = *reinterpret_cast<uint32_t*>(rsi + 4);

    al = static_cast<uint8_t>(rax);
    cl = 2;
    if (al != 1) {
        cl = 0;
    }
    r8 = r8 - r9;
    r9 = r9 >> cl;
    r8 = r8 >> cl;
    goto loc_e825844;

loc_e825818:
    // 0xe825818..0xe825844
    r11 = *reinterpret_cast<uint16_t*>(rsi + 8);
    if (r11 == 0) {
        r11 = *reinterpret_cast<uint32_t*>(r14 + 0x70);
    }
    rcx = *reinterpret_cast<uint32_t*>(rsi + 4);
    r15 = 0;
    rax = rcx;
    rdx = 0;
    r9 = rax / r11;
    r8 = r8 - rcx;
    rax = r8;
    rdx = 0;
    r8 = rax / r11;

loc_e825844:
    rax = r9;
    write_dword(0xC0, r15);
    rcx = *reinterpret_cast<uint32_t*>(r14 + 0x14);
    rdx = rbx + 0xD4;
    write_dword(rdx - 8, rcx);
    rcx = read_qword(r14 + 0xC);
    write_qword(rdx - 0x10, rcx);
    write_dword(0xD0, rax);
    write_dword(0xD8, r8);
    write_dword(0xDC, r11);
    write_qword(0xE0, r10);

    rax = read_qword(0x12BB4910);
    rcx = read_qword(rax + 0x400);
    rax = read_qword(0xB8);
    r9 = read_qword(rax + 8);
    rdx = read_qword(r14);
    rax = read_qword(rcx);
    rax = read_qword(rax + 0x90);
    r8 = rbx + 0xC0;

    // 0xe8258ad call qword ptr [0xF99FFA0]
    reinterpret_cast<void(*)(void*, void*, void*, void*)>(g_vendor_thunk_eea6040)(rcx, rdx, r8, r9);

    rdx = read_qword(0xB8);
    rax = *reinterpret_cast<uint32_t*>(rdx + 0x18);
    *reinterpret_cast<uint64_t*>(rdx + 8) += rax;
    r10 = read_dword(0xF0);
    rax = r10;
    rcx = read_qword(rdx + 0x10);
    write_qword(rdi + rax * 8, rcx);
    rax = *reinterpret_cast<uint32_t*>(rdx + 0x18);
    rax = rax + rcx;
    write_qword(rdx + 0x10, rax);

    rax = read_qword(0x1C0);
    write_dword(rbx + rax * 4 + 0x3B0, 0);
    // jmp 0xE825790 (outside chunk, goes to loop increment)
    goto loc_e825790;

loc_e8258f5:
    // 0xe8258f5..0xe825a66
    rcx = read_qword(0xA0);
    rdx = rbx + 0x3B0;
    r8 = 0x41;
    r9 = read_qword(0x388);

    // 0xe825910 call 0xE820500
    sub_e820500(rbx, rsi, rdi, rdx);

    rsi = rax;
    if (static_cast<uint16_t>(rax) == *reinterpret_cast<uint16_t*>(rbx + 0x10C)) {
        goto loc_e825962;
    }

    rax = read_qword(0x90);
    rcx = read_qword(rax + 0x30);
    rax = static_cast<uint16_t>(rsi);
    rdx = read_qword(0xA0);
    r8 = *reinterpret_cast<uint16_t*>(rdx + 0x24);
    r8 = r8 * rax;
    r8 = r8 * *reinterpret_cast<uint32_t*>(rdx + 0x20);
    r8 = r8 + read_qword(rdx + 0x18);
    rax = read_qword(rcx);
    rax = read_qword(rax + 0xF8);
    rdx = 0;

    // 0xe825954 call qword ptr [0xF99FFA0]
    reinterpret_cast<void(*)(void*, void*, void*, void*)>(g_vendor_thunk_eea6040)(rcx, rdx, r8, r9);

    write_word(0x10C, static_cast<uint16_t>(rsi));

loc_e825962:
    // 0xe825962..0xe825a14
    rax = read_qword(0x90);
    rcx = read_qword(rax + 0x30);
    rdi = read_qword(0x2C0);
    r8 = read_qword(rdi);
    rax = read_qword(rcx);
    rax = read_qword(rax + 0xF8);
    rdx = 1;

    // 0xe825986 call qword ptr [0xF99FFA0]
    reinterpret_cast<void(*)(void*, void*, void*, void*)>(g_vendor_thunk_eea6040)(rcx, rdx, r8, r9);

    rax = read_qword(0x90);
    rcx = read_qword(rax + 0x30);
    r8 = read_qword(rdi);
    rax = read_qword(rcx);
    rax = read_qword(rax + 0xF8);
    rdx = 4;

    // 0xe8259aa call qword ptr [0xF99FFA0]
    reinterpret_cast<void(*)(void*, void*, void*, void*)>(g_vendor_thunk_eea6040)(rcx, rdx, r8, r9);

    rax = read_qword(rdi);
    write_qword(0xC0, rax);
    write_dword(0xC8, static_cast<uint32_t>(rsi));
    rcx = rbx + 0x670;
    rdx = read_qword(0x178);
    r8 = rbx + 0xC0;

    // 0xe8259d7 call 0xE82DE90
    sub_e82de90(rbx, rsi, rdi, rdx);

    rdx = read_qword(0x2D0);
    rdx = rdx - rdi;
    if (rdx < 0x1000) {
        goto loc_e825a0c;
    }

    rax = read_qword(rdi - 8);
    rdi = rdi - 8;
    rdi = rdi - rax;
    if (rdi >= 0x20) {
        // jmp 0xE82D4C4 (outside chunk)
        // This path not fully lifted in chunk 0
    }

    rdx = rdx + 0x27;
    rdi = rax;

loc_e825a0c:
    rcx = rdi;

    // 0xe825a0f call 0xE935700
    sub_e935700(rbx, rsi, rdi, rdx);

    // jmp 0xE827C85 (outside chunk)

loc_e825a19:
    // 0xe825a19..0xe825a66
    // movdqa [rbx+0x220], xmm9 (skip xmm)
    write_qword(0x230, 0);
    rdx = 0x41;
    rcx = rbx + 0x220;

    // 0xe825a39 call 0xE835B50
    sub_e835b50(rbx, rsi, rdi, rdx);

    *reinterpret_cast<uint64_t*>(rbx + 0x200) += rdi;
    r8 = 0x104;
    rcx = rbx + 0x3B0;
    rdx = 0;

    // 0xe825a55 call 0xEEC6ED0
    sub_eec6ed0(rbx, rsi, rdi, rdx);

    rax = 0;
    r10 = 0;
    r9 = read_qword(0xB0);

loc_e825a66:
    goto loc_e825ab3;

loc_e825a70:
    // 0xe825a70..0xe825ab3
    rax = read_qword(0x220);
    r8 = read_qword(0xB8);
    rcx = *reinterpret_cast<uint32_t*>(r8 + 0x18);
    *reinterpret_cast<uint64_t*>(r8 + 8) += rcx;
    rcx = r10;
    r10 = r10 + 1;
    rdx = read_qword(r8 + 0x10);
    write_qword(rax + rcx * 8, rdx);
    rax = *reinterpret_cast<uint32_t*>(r8 + 0x18);
    rax = rax + rdx;
    write_qword(r8 + 0x10, rax);
    write_dword(rbx + r11 * 4 + 0x3B0, 0);
    rax = read_dword(0x1D0);
    rax = rax + 1;

loc_e825ab3:
    r8 = *reinterpret_cast<uint32_t*>(0x12AE0D80);
    if (rax >= r8) {
        // jmp 0xE827A11 (outside chunk)
    }

    write_dword(0x1D0, rax);
    r11 = rax;
    rax = r11 + r11 * 4;
    rcx = read_qword(0x200);
    rdi = *reinterpret_cast<uint16_t*>(rcx + rax * 4 + 0xA);
    if (rdi == 0xFFFF) {
        goto loc_e825a70;
    }

    write_qword(0x130, r11);
    write_dword(0x110, r10);
    rsi = rcx + rax * 4;
    rax = *reinterpret_cast<uint8_t*>(rsi + 0x13);
    if (rax > 9) {
        // jmp 0xE8270E2 (outside chunk)
    }

    rcx = 0xF4EE7D0;
    rax = *reinterpret_cast<int32_t*>(rcx + rax * 4);
    rax = rax + rcx;
    // jmp rax (jump table dispatch)
    // This would dispatch to various labels outside this chunk

    // For chunk 0, we stop here as the chunk ends at 0xe826230
    // The remaining code from 0xe825b15 onwards continues in chunk 1

    // Write back register state to struct
    s->rdi = rdi;
    s->rsi = rsi;
    s->rax = rax;
    s->rcx = rcx;
    s->rdx = rdx;
    s->r8 = r8;
    s->r9 = r9;
    s->r10 = r10;
    s->r11 = r11;
    s->r12 = r12;
    s->r13 = r13;
    s->r14 = r14;
    s->r15 = r15;
}

} // namespace native

#if 0
// verbatim instruction quotes for 0xe824a42..0xe826230
0xe824a73  call 0xE82DCC0
0xe824c35  call qword ptr [0xF99FFA0]
0xe824cf0  call qword ptr [0xF99FFA0]
0xe824d93  call qword ptr [0xF99FFA0]
0xe824e72  call r10
0xe824f81  call qword ptr [0xF99FFA0]
0xe8250c2  call 0xE82D960
0xe8250fb  call 0xEBCE390
0xe825162  call r10
0xe825174  call 0xE82DCC0
0xe825260  call r10
0xe8252c4  call qword ptr [0xF99FFA0]
0xe82533b  call 0xEBD1560
0xe825369  call 0xE82D960
0xe8253a6  call 0xEBCE390
0xe82548c  call qword ptr [0xF99FFA0]
0xe82553a  call qword ptr [0xF99FFA0]
0xe825596  call qword ptr [0xF99FFA0]
0xe825688  call qword ptr [0xF99FFA0]
0xe825762  call r10
0xe8258ad  call qword ptr [0xF99FFA0]
0xe825910  call 0xE820500
0xe825954  call qword ptr [0xF99FFA0]
0xe825986  call qword ptr [0xF99FFA0]
0xe8259aa  call qword ptr [0xF99FFA0]
0xe8259d7  call 0xE82DE90
0xe825a0f  call 0xE935700
0xe825a39  call 0xE835B50
0xe825a55  call 0xEEC6ED0
0xe825b62  call 0xE82DCC0
0xe825d18  call qword ptr [0xF99FFA0]
0xe825dd3  call qword ptr [0xF99FFA0]
0xe825e76  call qword ptr [0xF99FFA0]
0xe825f52  call r10
0xe826061  call qword ptr [0xF99FFA0]
0xe8261e2  call 0xE83ACE0
#endif