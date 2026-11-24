// LIFT 0xbc5fce0 size 0x41d 1.26.62.01 sub_bc5fce0
#include "client/features/render/native/bgfx/sub_bc5fce0.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstring>
#include <intrin.h>

namespace native {

namespace {

// 0xE951550: stack-cookie failure (__report_gsfailure style), noreturn;
// crt row in docs/data/native_boundary.tsv [V].
// Called at 0xbc600f7 with rcx = cookieStored ^ rsp when the cookie check fails.
native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");

// 0xEBCE390: called at 0xbc5fffc as (rcx=r15, rdx=&block, r8d=0x70) => a 0x70-byte block copy.
// 0xEBCE390 -> jmp 0xEEC6EC0 -> jmp qword ptr [0xF9A8A98]; the real target is
// only known at runtime. Not classified in the CALLEES set or
// docs/data/native_boundary.tsv; recorded as unresolved in the unit result file.
// Declared with the observed argument layout so the call site can be expressed.
extern "C" void sub_ebce390(void* dst, const void* src, std::uint32_t count);

// Calls through 0xF99FFA0 at 0xbc5fdaf and 0xbc5fe0f: the cell holds sub_eea6040,
// which is `jmp rax` with rax = vfptr[0x198] / vfptr[0x1A0] loaded just before.
// => virtual calls through vtable slots 0x198 / 0x1A0; targets are not statically
// known; neither callee is classified in the CALLEES set or
// native_boundary.tsv; recorded as unresolved in the unit result file.
// Expressed as direct vtable-slot invocations, which is exactly what the
// jmp-rax thunk chain does.

std::uint32_t sub_bc5fce0_footprint(void* /*a1*/, void* /*a2*/, void* /*a3*/) {
    // Writes go through runtime-derived pointers (*(a2+0x10) -> vertex base,
    // *(*(a2+8)) -> destination) with extents derived from the input counts;
    // no static footprint can be declared [V].
    return {};
}

} // namespace

extern "C" void sub_bc5fce0(void* a1, void* a2, void* a3) {
    // 0xbc5fce0..0xbc5fd61
    // Prologue: push r15,r14,r13,r12,rsi,rdi,rbp,rbx; sub rsp,0x158; save xmm14..xmm7;
    // spill args (rsi = r8 = a3, [rsp+0x28] = rdx = a2, [rsp+0x38] = rcx = a1);
    // stack cookie: [rsp+0xB8] = [0x1230A0C0] ^ rsp.
    std::uintptr_t cookieSlot = 0;
    std::uintptr_t cookieStored =
        *reinterpret_cast<std::uintptr_t*>(kGblCookie) ^ reinterpret_cast<std::uintptr_t>(&cookieSlot);
    (void)cookieStored;

    // 0xbc5fd62..0xbc5fd9a
    // cmp byte ptr [a3+0x10], 0 ; flag selects the xmm6/xmm7/xmm8 constant set.
    const std::uint8_t flag =
        *reinterpret_cast<const std::uint8_t*>(reinterpret_cast<const char*>(a3) + 0x10u);
    float xmm6 = 0.0f;
    float xmm7 = *reinterpret_cast<const float*>(0xEF3F000u);
    float xmm8 = 0.0f;
    if (flag == 0) {
        // 0xbc5fd83..0xbc5fd9b: xmm6 = xmm7 (C0); xmm7 = [0xEEC8060] (C2); xmm8 = [0xF085AA8] (C1).
        xmm6 = xmm7;
        xmm7 = *reinterpret_cast<const float*>(0xEEC8060u);
        xmm8 = *reinterpret_cast<const float*>(0xF085AA8u);
    } else {
        // 0xbc5fd76..0xbc5fd9b: xmm6 stays 0; xmm7 stays C0; xmm8 = [0xEFC13A4] (C3).
        xmm8 = *reinterpret_cast<const float*>(0xEFC13A4u);
    }

    // 0xbc5fd9b..0xbc5fdaf
    // mov rcx = a1; rax = [a1] (vfptr); rax = vfptr[0x198] (dead read, same reads); rdx = a2.
    void** vf1 = *reinterpret_cast<void***>(a1);
    const std::uintptr_t slot198 = vf1[kVslotCall1 / 8];
    (void)slot198;
    // 0xbc5fdaf  call qword ptr [0xF99FFA0]   ; cell -> sub_eea6040 (`jmp rax`) => vfptr[0x198](a1, a2)
    // `0xbc5fdaf  call qword ptr [0xF99FFA0]`
    ((void (*)(void*, void*))slot198)(a1, a2);

    // 0xbc5fdb5..0xbc5fdbc
    // rc = u16[a3+0xE]; if rc == 0 -> epilogue.
    const std::uint16_t rc =
        *reinterpret_cast<const std::uint16_t*>(reinterpret_cast<const char*>(a3) + 0x0Eu);
    if (rc == 0) goto L_epilogue;

    // 0xbc5fdc2..0xbc5fde9
    const float xmm9 = *reinterpret_cast<const float*>(0xEFC13A4u);
    const float xmm10 = *reinterpret_cast<const float*>(0xF2CC750u);
    const float xmm11 = *reinterpret_cast<const float*>(0xF441400u);
    const std::uint16_t k12[4] = *reinterpret_cast<const std::uint16_t(*)[4]>(0xF441410u);
    const std::uint32_t* const T = reinterpret_cast<const std::uint32_t*>(0xF441880u);

    // 0xbc5fde9..0xbc5fdf0
    std::uint32_t ebx = 0;   // row
    std::uint32_t edi = 0;   // col
    std::uint32_t ebp = 0;   // element counter (+6 per element)
    std::uint32_t r14d = 0;  // vertex counter (+4 per element)
    std::uint32_t slot34 = 0;  // [rsp+0x34] = ebx + 1 (written per processed element)
    std::uint32_t cc = 0;    // column count, reloaded per row
    std::uint32_t r8d_at_entry = 0;  // r8d value on entry to the final call
    const std::uint16_t* const data = reinterpret_cast<const std::uint16_t*>(a3);
    const std::uint8_t* const vtxBase =
        reinterpret_cast<std::uint8_t*>(*reinterpret_cast<std::uintptr_t*>(
            reinterpret_cast<const char*>(a2) + 0x10u));          // *(a2+0x10)
    const std::uint8_t* const sinkBase =
        reinterpret_cast<std::uint8_t*>(*reinterpret_cast<std::uintptr_t*>(
            *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<const char*>(a2) + 0x8u))); // *(*(a2+8))
    std::uint8_t* r12 = const_cast<std::uint8_t*>(vtxBase);
    std::uint8_t* r15 = const_cast<std::uint8_t*>(sinkBase);

    goto L_check_row;

L_setup_row:   // 0xbc5fe2c..0xbc5fe47
    // mov rdx = a2; rax = [a2+8]; rdx = [a2+0x10]; r12 = [rdx] = vtxBase;
    // r15 = [rax] = sinkBase; eax = cc = u16[a3+0xC]; ebp = 0; r14d = 0.
    r12 = vtxBase;
    r15 = sinkBase;
    cc = *reinterpret_cast<const std::uint16_t*>(reinterpret_cast<const char*>(a3) + 0x0Cu);
    ebp = 0;
    r14d = 0;
    goto L_check_col;

L_check_row:   // 0xbc5fe25..0xbc5fe2b
    // movzx eax = rc; cmp ebx, eax; jae -> L_final_call with ebp = 0.
    if (ebx >= rc) {
        ebp = 0;                                          // 0xbc5fdf3  xor ebp, ebp
        r8d_at_entry = ebx;                               // 0xbc5fdf0  mov r8d, ebx
        goto L_final_call;
    }
    goto L_setup_row;

L_check_col:   // 0xbc5fe5e..0xbc5fe6a
    // movzx edx = cc; cmp edi, edx; cmovae edi, r13d (r13d == 0 here); cmp; jae -> row transition.
    if (edi >= cc) edi = 0;                               // 0xbc5fe63  cmovae edi, r13d
    if (edi >= cc) goto L_row_transition;
    goto L_body;

L_body:   // 0xbc5fe6b..0xbc5ffc3 (element body up to the block-copy call)
    // lea r8d = [rbx+1]; [rsp+0x34] = r8d; rcx = data; ... r13 = data + 2*(cc*ebx + edi) + 1.
    slot34 = ebx + 1;                                     // 0xbc5fe80  mov [rsp+0x34], r8d
    const std::uint16_t v = data[cc * ebx + edi];         // [r13] = hi, [r13-1] = lo, little-endian u16
    const std::uint8_t lo = static_cast<std::uint8_t>(v);
    const std::uint8_t hi = static_cast<std::uint8_t>(v >> 8);
    if (v == 0) goto L_next_col;                          // 0xbc5feb0  je 0xBC60035
    if (hi == 0x20 && lo < 0x10) goto L_next_col;         // 0xbc5feb9..0xbc5fec7

    Bc5fce0Block block;
    block.f[0] = static_cast<float>(edi) * xmm9;          // 0xbc5feeb  movss [rsp+0x40], xmm0
    block.f[1] = static_cast<float>(ebx) * xmm8;          // 0xbc5fef6  movss [rsp+0x44], xmm13
    block.w[2] = 0;                                       // 0xbc5fefd
    block.w[3] = T[lo & 0xF];                             // 0xbc5fed9
    block.w[4] = T[lo >> 4];                              // 0xbc5fee7
    block.f[5] = static_cast<float>(hi) * xmm9 * xmm10 + xmm11;  // 0xbc5ff20
    block.f[6] = xmm6;                                    // 0xbc5ff26
    block.f[7] = static_cast<float>(edi + 1) * xmm9;      // 0xbc5ff3a
    block.f[8] = static_cast<float>(ebx) * xmm8;          // 0xbc5ff40
    block.w[9] = 0;                                       // 0xbc5ff47
    block.w[10] = T[lo & 0xF];                            // 0xbc5ff5a
    block.w[11] = T[lo >> 4];                             // 0xbc5ff5e
    block.f[12] = static_cast<float>((std::uint32_t)hi * 8u + 8u) * xmm10 + xmm11;  // 0xbc5ff6c
    block.f[13] = xmm6;                                   // 0xbc5ff72
    block.f[14] = static_cast<float>(edi + 1) * xmm9;     // 0xbc5ff78
    block.f[15] = static_cast<float>(ebx + 1) * xmm8;     // 0xbc5ff7e
    block.w[16] = 0;                                      // 0xbc5ff85
    block.w[17] = T[lo & 0xF];                            // 0xbc5ff90
    block.w[18] = T[lo >> 4];                             // 0xbc5ff97
    block.f[19] = static_cast<float>((std::uint32_t)hi * 8u + 8u) * xmm10 + xmm11;  // 0xbc5ff9e
    block.f[20] = xmm7;                                   // 0xbc5ffa7
    block.f[21] = static_cast<float>(edi) * xmm9;         // 0xbc5ffb0
    block.f[22] = static_cast<float>(ebx + 1) * xmm8;     // 0xbc5ffb9
    block.w[23] = 0;                                      // 0xbc5ffc3
    block.w[24] = T[lo & 0xF];                            // 0xbc5ffce
    block.w[25] = T[lo >> 4];                             // 0xbc5ffd5
    block.f[26] = static_cast<float>(hi) * xmm9 * xmm10 + xmm11;  // 0xbc5ffdc
    block.f[27] = xmm7;                                   // 0xbc5ffe5

    // 0xbc5ffee..0xbc5fffc: r8d = 0x70; rcx = r15; rdx = &block; call.
    // 0xbc5fffc  call 0xEBCE390   ; (r15, &block, 0x70) -> sub_ebce390 -> jmp [0xF9A8A98] (unclassified target)
    // `0xbc5fffc  call 0xEBCE390`
    sub_ebce390(r15, &block, kBlockSize);

    // 0xbc60001..0xbc6002e
    r15 += 0x70u;                                          // 0xbc60001
    *reinterpret_cast<std::uint16_t*>(r12) =
        static_cast<std::uint16_t>(r14d);                  // 0xbc60005  mov [r12], r14w
    {
        // 0xbc6000a..0xbc60014: movd xmm0, r14d; pshuflw xmm0, xmm0, 0; paddw xmm0, xmm12.
        std::uint16_t lanes[4];
        const std::uint16_t v14 = static_cast<std::uint16_t>(r14d);
        for (int idx = 0; idx < 4; ++idx)
            lanes[idx] = static_cast<std::uint16_t>(static_cast<std::uint32_t>(v14) + k12[idx]);  // paddw wrap
        // 0xbc60019  movq [r12+2], xmm0  (8 bytes)
        std::memcpy(r12 + 2, lanes, 8);
    }
    *reinterpret_cast<std::uint16_t*>(r12 + 0xAu) =
        static_cast<std::uint16_t>(r14d);                  // 0xbc60020  mov [r12+0xA], r14w
    r14d += 4u;                                            // 0xbc60026
    r12 += kVtxStride;                                     // 0xbc6002a
    ebp += 6u;                                             // 0xbc6002e

L_next_col:   // 0xbc60031..0xbc6003e
    // movzx eax = cc (reloaded); inc edi; cmp edi, cc; jae -> row transition.
    ++edi;                                                // 0xbc60035
    if (edi >= cc) goto L_row_transition;                 // 0xbc6003a  jae 0xBC6004E
    if (ebp < kElemCap) goto L_body;                      // 0xbc60042  jb 0xBC5FEA0
    goto L_row_transition;                                // fall through

L_row_transition:   // 0xbc6004e..0xbc60055
    // cmp ebp, 0x17FF; ja -> cap path.
    if (ebp > kRowDone) goto L_all_done;                  // 0xbc60054  ja 0xBC60067
    rc = *reinterpret_cast<const std::uint16_t*>(reinterpret_cast<const char*>(a3) + 0x0Eu);  // 0xbc60056
    // 0xbc6005a  xor r13d, r13d (edi reset at L_check_col via cmovae) [V]
    // 0xbc6005d  mov r8d, [rsp+0x34] (slot34) [V]
    goto L_row_advance;

L_row_advance:   // 0xbc60062 -> 0xBC5FE54
    // movzx edx = cc; inc ebx; cmp r8d(=slot34), edx; jae -> final call.
    ++ebx;                                                // 0xbc60057
    if (slot34 >= rc) {                                   // 0xbc60059..0xbc6005c  jae 0xBC5FDF5
        r8d_at_entry = slot34;
        goto L_final_call;
    }
    goto L_check_col;                                     // fall through: edi >= cc -> 0 at L_check_col

L_final_call:   // 0xbc5fdf5..0xbc5fe1f
    // mov rcx = a1; rax = [a1] (vfptr); rax = vfptr[0x1A0] (dead read, same reads);
    // rdx = a2; r8d = ebp.
    void** vf2 = *reinterpret_cast<void***>(a1);
    const std::uintptr_t slot1A0 = vf2[kVslotCall2 / 8];
    (void)slot1A0;
    // 0xbc5fe0f  call qword ptr [0xF99FFA0]   ; cell -> sub_eea6040 (`jmp rax`) => vfptr[0x1A0](a1, a2, ebp)
    // `0xbc5fe0f  call qword ptr [0xF99FFA0]`
    ((void (*)(void*, void*, std::uint32_t))slot1A0)(a1, a2, ebp);
    ebx = r8d_at_entry;                                   // 0xbc5fe19  mov ebx, r14d
    if (ebx >= rc) goto L_epilogue;                       // 0xbc5fe1c..0xbc5fe1f  jae 0xBC60072
    goto L_check_row;                                     // 0xbc5fe25..0xbc5fe2a

L_all_done:   // 0xbc60067..0xbc6006c
    // mov r8d, ebx; xor r13d, r13d; jmp final call.
    r8d_at_entry = ebx;                                   // 0xbc60067  mov r8d, ebx
    goto L_final_call;

L_epilogue:   // 0xbc60072..0xbc600eb
    // mov rax = [rsp+0xB8] (cookieStored); xor rax, rsp; rcx = [0x1230A0C0]; cmp; jne -> failure.
    if (*reinterpret_cast<std::uintptr_t*>(kGblCookie) !=
        (cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot))) {
        // failure path 0xbc600ec..0xbc600fc:
        //   `0xbc600ec  mov rcx,[rsp+0xB8]`
        //   `0xbc600f4  xor rcx,rsp`
        //   0xbc600f7  call 0xE951550   ; boundary crt, noreturn [V]
        //   `0xbc600f7  call 0xE951550`
        //   `0xbc600fc  int3`
        sub_e951550(cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot));
        __assume(false);                                  // `0xbc600fc  int3` (unreachable)
    }
    // 0xbc60089..0xbc600eb: restore xmm6..xmm14, add rsp,0x158, pop rbx..r15, ret.
}

// 0xbc600ec..0xbc600fc: failure path (cookie mismatch); not taken on the cookie-match path.

LIFT_FN(bc5fce0, "sub_bc5fce0", 0xBC5FCE0, sub_bc5fce0, sub_bc5fce0_footprint);

} // namespace native
