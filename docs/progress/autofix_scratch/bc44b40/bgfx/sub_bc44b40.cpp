// LIFT 0xbc44b40 size 0x133 1.26.62.01 sub_bc44b40

#include "client/features/render/native/bgfx/sub_bc44b40.h"

#include <cstdlib>
#include <cstring>
#include "client/features/render/native/Lift.h"
#include <cstdint>
// Forward declarations (autofix)
struct sub_eec6ec0;


// Layout assertions used by this function (full set in sub_bc44b40.h).

static_assert(offsetof(native::bgfx::FbSlot41Dst, mSize) == 0x30,
              "sub_bc44b40 writes dst+0x30 as size");
static_assert(offsetof(native::bgfx::FbSlot41Dst, mCapacity) == 0x38,
              "sub_bc44b40 branches on/writes dst+0x38 as capacity");

// Verbatim call instructions from the disassembly of [0xbc44b40, 0xbc44c73).

// All external targets are CRT/library intrinsics (spec §5/6): the two IAT

// calls go to the imported allocator (sub_eea6040, "malloc"), 0xEEC6EC0 is

// memcpy, and 0x75720/0x9BC830 are noreturn CRT handlers

// (invalid_parameter / heap failure). None are game calls needing a wrapper.

// UNRESOLVED CALL = none.

// 0xbc44be5  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040

// 0xbc44c08  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040

// 0xbc44c2b  call 0xEEC6EC0               ; -> sub_eec6ec0

// 0xbc44c5b  call 0x9BC830                ; -> sub_9bc830

// 0xbc44c65  call 0x75720                 ; -> sub_75720

// 0xbc44c6d  call 0x9BC830                ; -> sub_9bc830


extern "C" __declspec(noreturn) void invalid_parameter(void* dst, uint8_t tag, const void* src, void* extra);
extern "C" __declspec(noreturn) void heap_failure(uint64_t alloc_size);

namespace native::bgfx {

FbSlot41Dst* sub_bc44b40(FbSlot41Dst* dst, uint8_t tag, const FbSlot41Src* src, void* extra) {
    // 0xbc44b40..0xbc44b4b — prologue: push r15, r14, r13, r12, rsi, rdi, rbx; sub rsp, 0x20      // 0xbc44b40..0xbc44b4b

    // 0xbc44b4f..0xbc44b55 — argument copies: rsi = r9, rbx = r8, rdi = rcx                        // 0xbc44b4f..0xbc44b55

    dst->mTag = tag;                                                                  // 0xbc44b58  mov [rcx],dl

    std::memcpy(&dst->mHeader, src, 16);                                              // 0xbc44b5a  movups xmm0,[r8] / 0xbc44b5e  movups [rcx+8],xmm0 / 0xbc44b62  mov rax,[r8+0x10] / 0xbc44b66  mov [rcx+0x18],rax  // 0xbc44b5a..0xbc44b66

    std::memset(&dst->mData, 0, 16);                                                  // 0xbc44b6d  movups [rcx+0x20],xmm0 / 0xbc44b71  movups [rcx+0x30],xmm0  // 0xbc44b6d..0xbc44b71

    const uint64_t size = src->mSize;                                                 // 0xbc44b75  mov r14,[r8+0x28]  // 0xbc44b75..0xbc44b75

    const uint8_t* srcData;
    if (src->mCapacity < 0x10) {                                                      // 0xbc44b79  cmp qword ptr [r8+0x30],0x10 / 0xbc44b7e  jb short 0xBC44B86  // 0xbc44b79..0xbc44b7e

        srcData = reinterpret_cast<const uint8_t*>(&src->mData);                      // 0xbc44b86  lea r15,[rbx+0x18]  // 0xbc44b86..0xbc44b86

    } else {                                                                          // 0xbc44b80  mov r15,[rbx+0x18] / 0xbc44b84  jmp short 0xBC44B8A  // 0xbc44b80..0xbc44b84

        srcData = src->mData;
    }
    if (static_cast<int64_t>(size) < 0) {                                             // 0xbc44b8a  test r14,r14 / 0xbc44b8d  js 0xBC44C65  // 0xbc44b8a..0xbc44b8d

        invalid_parameter(dst, tag, src, extra);                                      // 0xbc44c65  call 0x75720  // 0xbc44c65..0xbc44c65

    }
    if (size > 0xF) {                                                                 // 0xbc44b93  cmp r14,0xF / 0xbc44b97  ja short 0xBC44BB2  // 0xbc44b93..0xbc44b97

        // 0xbc44bb2..0xbc44bc3 — size class: rdx = size | 0xF; capacity = (rdx >= 0x17) ? rdx : 0x16   // 0xbc44bb2..0xbc44bc3

        const uint64_t rdx = size | 0xF;                                              // 0xbc44bb2  mov rdx,r14 / 0xbc44bb5  or rdx,0xF  // 0xbc44bb2..0xbc44bb5

        uint64_t capacity = 0x16;                                                     // 0xbc44bbd  mov r13d,0x16  // 0xbc44bbd..0xbc44bbd

        if (rdx >= 0x17) capacity = rdx;                                              // 0xbc44bb9  cmp rdx,0x17 / 0xbc44bc3  cmovae r13,rdx  // 0xbc44bb9..0xbc44bc3


        // 0xbc44bd5..0xbc44c08 — heap malloc (fast path, rdx < 0xFFF: capacity + 1)

        // via IAT call [0xF99FFA0]; NULL -> heap_failure.                            // 0xbc44bd5  cmp rdx,0xFFF / 0xbc44bdc  jb short 0xBC44C01 / 0xbc44be5  call qword ptr [0xF99FFA0] / 0xbc44beb  test rax,rax / 0xbc44bee  je short 0xBC44C55  // 0xbc44bd5..0xbc44bee

        void* allocated;
        if (rdx < 0xFFF) {
            allocated = std::malloc(capacity + 1);                                    // 0xbc44c01  lea r12,[r13+1] / 0xbc44c05  mov rdx,r12  // 0xbc44c01..0xbc44c05

            if (!allocated) heap_failure(capacity + 1);                               // 0xbc44c08  call qword ptr [0xF99FFA0] / 0xbc44c0e  mov rcx,rax / 0xbc44c11  test rax,rax / 0xbc44c14  je short 0xBC44C6A / 0xbc44c55  mov rcx,r12 / 0xbc44c58  mov r12,rax / 0xbc44c5b  call 0x9BC830  // 0xbc44c08..0xbc44c5b

        } else {
            allocated = std::malloc(capacity + 0x28);                                 // 0xbc44bde  lea r12,[r13+0x28] / 0xbc44be2  mov rdx,r12  // 0xbc44bde..0xbc44be2

            if (!allocated) heap_failure(capacity + 0x28);                            // 0xbc44be5  call qword ptr [0xF99FFA0] / 0xbc44beb  test rax,rax / 0xbc44bee  je short 0xBC44C55  // 0xbc44be5..0xbc44bee

            uint8_t* p = reinterpret_cast<uint8_t*>(allocated);
            uintptr_t aligned = (reinterpret_cast<uintptr_t>(p) + 0x27) & ~0x1FULL;
            *reinterpret_cast<uintptr_t*>(aligned - 8) = reinterpret_cast<uintptr_t>(p);  // 0xbc44bf0  mov rcx,rax / 0xbc44bf3  add rcx,0x27 / 0xbc44bf7  and rcx,0xFFFFFFFFFFFFFFE0 / 0xbc44bfb  mov [rcx-8],rax  // 0xbc44bf0..0xbc44bfb

            dst->mData = reinterpret_cast<void*>(aligned);                            // 0xbc44bff  jmp short 0xBC44C16 / 0xbc44c16  mov [rdi+0x20],rcx  // 0xbc44bff..0xbc44c16

        }
        dst->mSize = size;                                                            // 0xbc44c1a  mov [rdi+0x30],r14  // 0xbc44c1a..0xbc44c1a

        dst->mCapacity = capacity;                                                    // 0xbc44c1e  mov [rdi+0x38],r13  // 0xbc44c1e..0xbc44c1e


        // 0xbc44c22..0xbc44c2b — size++; memcpy(dst->mData, srcData, size + 1).       // 0xbc44c22  inc r14 / 0xbc44c25  mov rdx,r15 / 0xbc44c28  mov r8,r14 / 0xbc44c2b  call 0xEEC6EC0  // 0xbc44c22..0xbc44c2b

        std::memcpy(dst->mData, srcData, size + 1);
    } else {
        // 0xbc44b99..0xbc44bb0 — SSO destination: dst+0x30 = size, +0x38 = 0xF, copy

        // 16 bytes of inline data to dst+0x20.                                       // 0xbc44b99  lea rax,[rdi+0x20] / 0xbc44b9d  mov [rdi+0x30],r14 / 0xbc44ba1  mov qword ptr [rdi+0x38],0xF / 0xbc44ba9  movups xmm0,[r15] / 0xbc44bad  movups [rax],xmm0 / 0xbc44bb0  jmp short 0xBC44C30  // 0xbc44b99..0xbc44bb0

        dst->mSize = size;
        dst->mCapacity = 0xF;
        std::memcpy(&dst->mData, srcData, 16);
    }

    // 0xbc44c30..0xbc44c54 — tail: dst+0x44 = src+0x3C (u16), dst+0x40 = src+0x38

    // (u32), dst+0x48 = extra (4th argument), return dst.                           // 0xbc44c30  movzx eax,word ptr [rbx+0x3C] / 0xbc44c34  mov [rdi+0x44],ax / 0xbc44c38  mov eax,[rbx+0x38] / 0xbc44c3b  mov [rdi+0x40],eax / 0xbc44c3e  mov [rdi+0x48],rsi / 0xbc44c42  mov rax,rdi / ... / 0xbc44c54  ret  // 0xbc44c30..0xbc44c54

    dst->mField3C = src->mField3C;
    dst->mField38 = src->mField38;
    dst->mField48 = extra;
    return dst;
}

LIFT_FN(BgfxFrameBuilderSlot41_copy, "sub_bc44b40", 0xbc44b40, sub_bc44b40, nullptr);

} // namespace native::bgfx

