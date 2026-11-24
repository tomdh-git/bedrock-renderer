// LIFT 0xbc5f7b0 size 0x11e 1.26.62.01 D3D12 submit RTX override
#include "client/features/render/native/bgfx/sub_bc5f7b0.h"

#include "client/features/render/native/Lift.h"

#include <cstddef>
#include <cstdint>
#include <intrin.h>
#include <vector>

static_assert(offsetof(Pair, ptr) == 0x00, "bc5f7b0: Pair::ptr layout");
static_assert(offsetof(Pair, len) == 0x08, "bc5f7b0: Pair::len layout");
static_assert(sizeof(Pair) == 0x10, "bc5f7b0: Pair size");

namespace native {

namespace {

// Calls out of lifted code go through native::Boundary wrappers (spec section 6):
// the original code runs and its calls are recorded/compared in Shadow/Verify
// mode. Symbols resolve through Sigs.json (SigManager::get); sig anchors for
// these boundary targets are added at the milestone gate (units do not edit
// src/sdk/Sigs.json).
//
// 0xEBCE5E0: bounded strlen (disassembly [0xebce5e0,0xebce600]): ptr == 0 -> 0;
// otherwise scan [ptr, ptr+maxlen) for NUL and return the bytes scanned.
// Called as (0xF59FECD, 0x7FFFFFFF) at 0xbc5f80b and (savedPtr, 0x7FFFFFFF)
// at 0xbc5f832.
// 0xEBCE570: bounded comparison of two {ptr,len} pairs (rcx=&pairB, rdx=&pairA,
// r8d=2): returns 0 when equal over min(lenB,lenA,2) bytes, nonzero byte
// difference otherwise. Called at 0xbc5f854.
// 0xE951550: stack-cookie failure, noreturn; crt row in
// docs/data/native_boundary.tsv (line 467, X0b5) [V]. Called at 0xbc5f8c8,
// followed by int3 (unreachable).
native::Boundary<std::uint32_t, const char*, std::uint32_t> sub_ebce5e0("sub_ebce5e0");
native::Boundary<std::int32_t, const Pair*, const Pair*, std::uint32_t> sub_ebce570("sub_ebce570");
native::Boundary<void> sub_e951550("sub_e951550");

std::uint32_t sub_bc5f7b0_footprint(std::uintptr_t* a0, std::uint32_t /*arg*/) {
    return { { reinterpret_cast<void*>(a0), 8ull } }; // the function writes *a0 (+0x0, 8 bytes) [V]
}

} // namespace

std::uint32_t sub_bc5f7b0(std::uintptr_t* a0, std::uint32_t arg) {
    // 0xbc5f7b0..0xbc5f7ba
    // 0xbc5f7b0  push r15
    // 0xbc5f7b2  push r14
    // 0xbc5f7b4  push r12
    // 0xbc5f7b6  push rsi
    // 0xbc5f7b7  push rdi
    // 0xbc5f7b8  push rbp
    // 0xbc5f7b9  push rbx
    // 0xbc5f7ba  sub rsp,0x50
    // 0xbc5f7be  mov ebx,edx
    std::uint32_t ebx = arg;                               // 0xbc5f7be

    // 0xbc5f7c0..0xbc5f7ca
    // 0xbc5f7c0  mov rax,[0x1230A0C0]
    // 0xbc5f7c7  xor rax,rsp
    // 0xbc5f7ca  mov [rsp+0x48],rax
    std::uintptr_t cookieSlot = 0;                         // address stands in for the rsp-relative slot
    const std::uintptr_t cookieStored =
        *reinterpret_cast<std::uintptr_t*>(0x1230A0C0) ^ reinterpret_cast<std::uintptr_t>(&cookieSlot);  // 0xbc5f7c0..0xbc5f7ca

    // 0xbc5f7cf..0xbc5f7df
    // 0xbc5f7cf  mov r15,[rcx]
    // 0xbc5f7d2  lea rdi,[r15+1]
    // 0xbc5f7d6  mov [rsp+0x40],rdi
    // 0xbc5f7db  cmp byte ptr [r15],0x5B
    // 0xbc5f7df  jne 0xBC5F89B
    const std::uintptr_t r15 = *a0;                        // 0xbc5f7cf
    std::uintptr_t savedPtr = r15 + 1;                     // 0xbc5f7d2..0xbc5f7d6
    std::uintptr_t* const slot = &savedPtr;                // &[rsp+0x40]

    if (*reinterpret_cast<const unsigned char*>(r15) == 0x5B) {  // 0xbc5f7db / 0xbc5f7df
        // 0xbc5f7e5  mov rsi,rcx        rsi = a0 (result sink)
        // 0xbc5f7e8  lea r12,[0xF847A07]
        // 0xbc5f7ef  mov [rsp+0x30],r12
        // 0xbc5f7f4  mov dword ptr [rsp+0x38],0
        Pair pairA{0xF847A07, 0};                          // 0xbc5f7e5..0xbc5f7f4

        // `0xbc5f7fc  lea r14,[0xF59FECD]`
        // `0xbc5f803  mov rcx,r14`
        // `0xbc5f806  mov edx,0x7FFFFFFF`
        // `0xbc5f80b  call 0xEBCE5E0`
        const std::uint32_t lenA =
            sub_ebce5e0(reinterpret_cast<const char*>(0xF59FECD), 0x7FFFFFFFu);
        // `0xbc5f810  test eax,eax`
        // `0xbc5f812  je short 0xBC5F81D`
        if (lenA != 0) {                                   // 0xbc5f810..0xbc5f812
            // `0xbc5f814  mov [rsp+0x38],eax`
            // `0xbc5f818  mov [rsp+0x30],r14`
            pairA.ptr = 0xF59FECD;                         // 0xbc5f818
            pairA.len = lenA;                              // 0xbc5f814
        }

        // 0xbc5f81d  mov [rsp+0x20],r12
        // 0xbc5f822  mov dword ptr [rsp+0x28],0
        Pair pairB{0xF847A07, 0};                          // 0xbc5f81d..0xbc5f822

        // `0xbc5f82a  mov rcx,rdi`
        // `0xbc5f82d  mov edx,0x7FFFFFFF`
        // `0xbc5f832  call 0xEBCE5E0`
        const std::uint32_t lenB =
            sub_ebce5e0(reinterpret_cast<const char*>(savedPtr), 0x7FFFFFFFu);
        // `0xbc5f837  test eax,eax`
        // `0xbc5f839  je short 0xBC5F844`
        if (lenB != 0) {                                   // 0xbc5f837..0xbc5f839
            // `0xbc5f83b  mov [rsp+0x28],eax`
            // `0xbc5f83f  mov [rsp+0x20],rdi`
            pairB.ptr = savedPtr;                          // 0xbc5f83f
            pairB.len = lenB;                              // 0xbc5f83b
        }

        // `0xbc5f844  lea rcx,[rsp+0x20]`
        // `0xbc5f849  lea rdx,[rsp+0x30]`
        // `0xbc5f84e  mov r8d,2`
        // `0xbc5f854  call 0xEBCE570`
        const std::int32_t cmp =
            sub_ebce570(&pairB, &pairA, 2u);
        // `0xbc5f859  test eax,eax`
        // `0xbc5f85b  je short 0xBC5F894`
        if (cmp == 0) {                                    // 0xbc5f859..0xbc5f85b
            // 0xbc5f894  add r15,3
            // 0xbc5f898  mov [rsi],r15
            *a0 = r15 + 3;                                 // 0xbc5f894..0xbc5f898
        } else {
            // `0xbc5f85d  mov r8d,ebx`
            // `0xbc5f860  and r8b,0xF`
            // `0xbc5f864  lea rdi,[rsp+0x40]`
            // `0xbc5f869  mov rcx,rdi`
            // `0xbc5f86c  mov dl,0x3B`
            // `0xbc5f86e  call 0xBC76380`
            const std::uint32_t depth1 = (arg & 0xFFFFFF00u) | (arg & 0x0Fu);
            const std::uint32_t eax1 =
                Bc76380_lifted(slot, 0x3BULL, depth1, 0u);
            // `0xbc5f873  mov ebp,eax`
            const std::uint32_t ebp = eax1;                // 0xbc5f873

            // `0xbc5f875  shr bl,4`
            // `0xbc5f878  mov rcx,rdi`
            // `0xbc5f87b  mov dl,0x6D`
            // `0xbc5f87d  mov r8d,ebx`
            // `0xbc5f880  call 0xBC76380`
            const std::uint32_t depth2 = (arg & 0xFFFFFF00u) | ((arg >> 4) & 0x0Fu);
            const std::uint32_t eax2 =
                Bc76380_lifted(slot, 0x6DULL, depth2, 0u);

            // `0xbc5f885  mov ebx,eax`
            // `0xbc5f887  shl bl,4`
            // `0xbc5f88a  or bl,bpl`
            ebx = (eax2 & 0xFFFFFF00u) |
                static_cast<std::uint32_t>(static_cast<std::uint8_t>(
                    (eax2 & 0x0Fu) << 4 | static_cast<std::uint8_t>(eax1 & 0xFFu)));

            // `0xbc5f88d  mov r15,[rsp+0x40]`
            // `0xbc5f892  jmp short 0xBC5F898`
            // `0xbc5f898  mov [rsi],r15`
            *a0 = *slot;                                   // 0xbc5f88d..0xbc5f898
        }
    } else {
        // 0xbc5f894  add r15,3
        // 0xbc5f898  mov [rsi],r15
        *a0 = r15 + 3;                                     // 0xbc5f894..0xbc5f898
    }

    // 0xbc5f89b..0xbc5f8ad
    // 0xbc5f89b  mov rax,[rsp+0x48]
    // 0xbc5f8a0  xor rax,rsp
    // 0xbc5f8a3  mov rcx,[0x1230A0C0]
    // 0xbc5f8aa  cmp rcx,rax
    // 0xbc5f8ad  jne short 0xBC5F8C0
    if (*reinterpret_cast<std::uintptr_t*>(0x1230A0C0) !=
        (cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot))) {  // 0xbc5f89b..0xbc5f8ad
        // `0xbc5f8c0  mov rcx,[rsp+0x48]`
        // `0xbc5f8c5  xor rcx,rsp`
        // `0xbc5f8c8  call 0xE951550`
        // `0xbc5f8cd  int3`
        sub_e951550();                                     // 0xbc5f8c0..0xbc5f8c8  call 0xE951550
        __assume(false);                                   // 0xbc5f8cd  int3
    }

    // 0xbc5f8af  mov eax,ebx
    // 0xbc5f8b1..0xbc5f8bf  add rsp,0x50; pop rbx,rbp,rdi,rsi,r12,r14,r15; ret
    return ebx;                                            // 0xbc5f8af..0xbc5f8bf
}

LIFT_FN(bc5f7b0, "D3D12 submit RTX override", 0xBC5F7B0, sub_bc5f7b0, sub_bc5f7b0_footprint);

} // namespace native
