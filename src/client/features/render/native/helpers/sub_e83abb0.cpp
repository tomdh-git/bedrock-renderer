// LIFT 0xe83abb0 size 0x12f 1.26.62.01 sub_e83abb0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_e83abb0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

// sub_ebce430 (0xEBCE430) is not in the lift set and not a boundary function.
// Both call sites pass (dest, fill = 0, count = 0x28), i.e. a 0x28-byte zero
// fill, so it is reproduced here as plain stores. No call to a function outside
// the lift set is introduced.
static inline void ebce430_zero_fill(void* dest, std::uint64_t count) {
    std::uint8_t* p = static_cast<std::uint8_t*>(dest);
    for (std::uint64_t i = 0; i < count; ++i) {
        *p++ = 0;
    }
}

// sub_e83ace0(self, size) grows the paged backing store. Its return value is not
// consumed by this function; self->fb8008 is reloaded after the call.
uintptr_t sub_e83ace0(void* self, std::uint64_t size);

// Reproduces: rax = n; mul 0x1642C8590B21642D; result = high64(rax*magic) >> 1.
static inline std::uint64_t magic_div(std::uint64_t n) {
    std::uint64_t high = 0;
    (void)_umul128(n, 0x1642C8590B21642DULL, &high);
    return high >> 1;
}

LIFT_FN(sub_e83abb0, "sub_e83abb0", 0xe83abb0, sub_e83abb0, nullptr);

uintptr_t sub_e83abb0(void* self, std::uint64_t size) {
    std::uint64_t rax = 0, rbx = 0, rsi = 0, rdi = 0, r14 = 0;
    auto* a0 = static_cast<sub_e83abb0_rcx*>(self);

    // 0xe83abb0..0xe83abc8: basic block 0
    // 0xe83abb0  push r14
    // 0xe83abb2  push rsi
    // 0xe83abb3  push rdi
    // 0xe83abb4  push rbx
    // 0xe83abb5  sub rsp,0x28
    // 0xe83abb9  mov rsi,rdx
    // 0xe83abbc  mov rdi,rcx
    // 0xe83abbf  cmp rdx,0x1000
    // 0xe83abc6  jb short 0xE83ABD1   ; -> if size <u 0x1000 goto L_0xe83abd1
    // 0xe83abc8                   ; -> if size >=u 0x1000 goto L_0xe83abc8
    rdi = reinterpret_cast<std::uint64_t>(self);
    rsi = size;
    if (rsi < 0x1000ULL) goto L_0xe83abd1;
    goto L_0xe83abc8;

    // 0xe83abc8..0xe83abd1: basic block 1
    // 0xe83abc8  cmp byte ptr [rdi+0xB8018],0
    // 0xe83abcf  jne short 0xE83AC31   ; -> if a0->fb8018 != 0 goto L_0xe83ac31
    //                           ; -> if a0->fb8018 == 0 goto L_0xe83abd1
L_0xe83abc8:
    if (a0->fb8018 != 0) goto L_0xe83ac31;
    goto L_0xe83abd1;

    // 0xe83abd1..0xe83abf1: basic block 2
    // 0xe83abd1  mov rax,[rdi+0xB8008]
    // 0xe83abd8  shr rax,3
    // 0xe83abdc  mov rbx,0x1642C8590B21642D
    // 0xe83abe6  mul rbx
    // 0xe83abe9  shr rdx,1
    // 0xe83abec  cmp rsi,rdx
    // 0xe83abef  jb short 0xE83AC31   ; -> if size <u threshold goto L_0xe83ac31
    //                          ; -> if size >=u threshold goto L_0xe83abf1
L_0xe83abd1:
    rax = reinterpret_cast<std::uint64_t>(a0->fb8008);
    rax >>= 3;
    rbx = magic_div(rax);
    if (rsi < rbx) goto L_0xe83ac31;
    goto L_0xe83abf1;

    // 0xe83abf1..0xe83ac23: basic block 3
    // 0xe83abf1  and rsi,0xFFFFFFFFFFFFF000
    // 0xe83abf8  add rsi,0x1000
    // 0xe83abff  mov rcx,rdi
    // 0xe83ac02  mov rdx,rsi
    // 0xe83ac05  call 0xE83ACE0   ; sub_e83ace0(self, size)
    // 0xe83ac0a  mov rax,[rdi+0xB8008]
    // 0xe83ac11  shr rax,3
    // 0xe83ac15  mul rbx          ; rbx still holds the magic constant (callee-saved)
    // 0xe83ac18  mov rbx,rdx
    // 0xe83ac1b  shr rbx,1
    // 0xe83ac1e  cmp rbx,rsi
    // 0xe83ac21  jb short 0xE83AC8C ; -> if threshold <u aligned_size goto L_0xe83ac8c
    //                          ; -> if threshold >=u aligned_size goto L_0xe83ac23
L_0xe83abf1:
    rsi &= 0xFFFFFFFFFFFFF000ULL;
    rsi += 0x1000ULL;
    sub_e83ace0(self, rsi);
    rax = reinterpret_cast<std::uint64_t>(a0->fb8008);
    rax >>= 3;
    rbx = magic_div(rax);
    if (rbx < rsi) goto L_0xe83ac8c;
    goto L_0xe83ac23;

    // 0xe83ac23..0xe83ac31: basic block 4
    // 0xe83ac23  imul rax,rsi,0xB8
    // 0xe83ac2a  mov [rdi+0xB8008],rax   ; a0->fb8008 = aligned_size * 0xB8
L_0xe83ac23:
    rax = rsi * 0xB8ULL;
    a0->fb8008 = reinterpret_cast<void*>(rax);
    goto L_0xe83ac31;

    // 0xe83ac31..0xe83ac3b: basic block 5 (return epilogue)
L_0xe83ac31:
    return rax;

    // 0xe83ac40..0xe83ac43: basic block 7
    // 0xe83ac40  add r14,rdi
L_0xe83ac40:
    r14 += rdi;
    goto L_0xe83ac43;

    // 0xe83ac43..0xe83ac8c: basic block 8
    // 0xe83ac43  mov qword ptr [r14],0
    // 0xe83ac4a  mov qword ptr [r14+0x90],0
    // 0xe83ac55  mov word ptr [r14+0xB1],0
    // 0xe83ac5f  lea rcx,[r14+0x40]
    // 0xe83ac63  mov r8d,0x28
    // 0xe83ac69  xor edx,edx
    // 0xe83ac6b  call 0xEBCE430   ; zero-fill [r14+0x40, 0x28)
    // 0xe83ac70  add r14,0x68
    // 0xe83ac74  mov r8d,0x28
    // 0xe83ac7a  mov rcx,r14
    // 0xe83ac7d  xor edx,edx
    // 0xe83ac7f  call 0xEBCE430   ; zero-fill [r14, 0x28)
    // 0xe83ac84  inc rbx
    // 0xe83ac87  cmp rbx,rsi
    // 0xe83ac8a  je short 0xE83AC23 ; -> if rbx == aligned_size goto L_0xe83ac23
    //                          ; -> if rbx != aligned_size goto L_0xe83ac8c
L_0xe83ac43:
    *reinterpret_cast<std::uint64_t*>(r14) = 0;
    *reinterpret_cast<std::uint64_t*>(r14 + 0x90) = 0;
    *reinterpret_cast<std::uint16_t*>(r14 + 0xB1) = 0;
    ebce430_zero_fill(reinterpret_cast<void*>(r14 + 0x40), 0x28ULL);
    r14 += 0x68ULL;
    ebce430_zero_fill(reinterpret_cast<void*>(r14), 0x28ULL);
    rbx += 1ULL;
    if (rbx == rsi) goto L_0xe83ac23;
    goto L_0xe83ac8c;

    // 0xe83ac8c..0xe83ac9c: basic block 9
    // 0xe83ac8c  imul r14,rbx,0xB8
    // 0xe83ac93  cmp rbx,0xFFF
    // 0xe83ac9a  jbe short 0xE83AC40   ; -> if rbx <=u 0xFFF goto L_0xe83ac40
    //                         ; -> if rbx >u 0xFFF goto L_0xe83ac9c
L_0xe83ac8c:
    r14 = rbx * 0xB8ULL;
    if (rbx <= 0xFFFULL) goto L_0xe83ac40;
    goto L_0xe83ac9c;

    // 0xe83ac9c..0xe83acb6: basic block 10 (block 11 is the nop at 0xe83acb6)
    // 0xe83ac9c  add r14,0xFFFFFFFFFFF48000   ; r14 -= 0xB8000
    // 0xe83aca3  mov rax,[rdi+0xB8000]
    // 0xe83acaa  mov rax,[rax]
    // 0xe83acad  cmp r14,0xB8000
    // 0xe83acb4  jb short 0xE83ACD7   ; -> if r14 <u 0xB8000 goto L_0xe83acd7
    //                          ; -> if r14 >=u 0xB8000 goto L_0xe83acc0
L_0xe83ac9c:
    r14 += 0xFFFFFFFFFFF48000ULL;
    rax = reinterpret_cast<std::uint64_t>(
        reinterpret_cast<sub_e83abb0_rax*>(a0->fb8000)->f0);
    if (r14 < 0xB8000ULL) goto L_0xe83acd7;
    goto L_0xe83acc0;

    // 0xe83acc0..0xe83acd7: basic block 12
    // 0xe83acc0  add r14,0xFFFFFFFFFFF48000   ; r14 -= 0xB8000
    // 0xe83acc7  mov rax,[rax+0xB8000]
    // 0xe83acce  cmp r14,0xB7FFF
    // 0xe83acd5  ja short 0xE83ACC0   ; -> if r14 >u 0xB7FFF goto L_0xe83acc0
    //                          ; -> if r14 <=u 0xB7FFF goto L_0xe83acd7
L_0xe83acc0:
    r14 += 0xFFFFFFFFFFF48000ULL;
    rax = reinterpret_cast<sub_e83abb0_rax*>(rax)->fb8000;
    if (r14 > 0xB7FFFULL) goto L_0xe83acc0;
    goto L_0xe83acd7;

    // 0xe83acd7..0xe83acdf: basic block 13
    // 0xe83acd7  add r14,rax
    // 0xe83acda  jmp 0xE83AC43        ; -> goto L_0xe83ac43
L_0xe83acd7:
    r14 += rax;
    goto L_0xe83ac43;
}

// Layout assertions for every field read or written by the lift.
static_assert(offsetof(sub_e83abb0_rcx, fb8000) == 0xb8000,
              "sub_0xe83abb0 rcx+0xb8000 field");
static_assert(offsetof(sub_e83abb0_rcx, fb8008) == 0xb8008,
              "sub_0xe83abb0 rcx+0xb8008 field");
static_assert(offsetof(sub_e83abb0_rcx, fb8018) == 0xb8018,
              "sub_0xe83abb0 rcx+0xb8018 field");
static_assert(sizeof(sub_e83abb0_rcx) >= 0xb8019,
              "sub_0xe83abb0 rcx sizeof lower bound");

static_assert(offsetof(sub_e83abb0_r14, f0) == 0x0,
              "sub_0xe83abb0 r14+0x0 field");
static_assert(offsetof(sub_e83abb0_r14, f40) == 0x40,
              "sub_0xe83abb0 r14+0x40 field");
static_assert(offsetof(sub_e83abb0_r14, f90) == 0x90,
              "sub_0xe83abb0 r14+0x90 field");
static_assert(offsetof(sub_e83abb0_r14, fb1) == 0xb1,
              "sub_0xe83abb0 r14+0xb1 field");
static_assert(sizeof(sub_e83abb0_r14) >= 0xb3,
              "sub_0xe83abb0 r14 sizeof lower bound");

static_assert(offsetof(sub_e83abb0_rax, f0) == 0x0,
              "sub_0xe83abb0 rax+0x0 field");
static_assert(offsetof(sub_e83abb0_rax, fb8000) == 0xb8000,
              "sub_0xe83abb0 rax+0xb8000 field");
static_assert(sizeof(sub_e83abb0_rax) >= 0xb8008,
              "sub_0xe83abb0 rax sizeof lower bound");

} // namespace native::helpers
