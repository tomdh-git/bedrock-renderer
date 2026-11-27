// LIFT 0xa14e0 size 0xd1 1.26.62.01 sub_a14e0
#include "sub_a14e0.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

namespace native {

// sub_a14e0 (0xa14e0, size 0xd1, 1.26.62.01).
//
// Full reversal of [0xa14e0, 0xa15b1):
//   0xa14e0..0xa14e5   prologue (push rsi; sub rsp,0x30; mov rsi,rcx) - no observable effect
//   0xa14e8..0xa1540   if (a0->f70 & 1): select rax = *(*(a0+0x40)) (idx = 0x58) or
//                      rax = *(*(a0+0x38)) (idx = 0x50), rdx = (int32_t)*(a0+idx)[0] + rax - *(*(a0+0x18)),
//                      then call sub_e935700 (rcx = *(*(a0+0x18)) when rdx < 0x1000, otherwise
//                      rcx = *(*(*(a0+0x18)) - 8) after a block-size check)
//   0xa1597..0xa15b1   block-size >= 0x20: call qword ptr [0xF9A8C78](0,0,0,0,0) through the data
//                      slot (read at call time) then int3 - noreturn
//   0xa1545..0xa1597   cleanup, always executed: *f18=0, *f38=0, *f50(dword)=0, *f20=0,
//                      *f40=0, *f58(dword)=0, f68 = 0, f70 &= 0xFE; ret with RAX = a0->f58
//
// x64 Microsoft ABI: RCX = a0, return in RAX. Every store below is in the same order as the
// original's stores. No null guards and no SEH: none exist in the original (fail fast).
//
// Verbatim instruction lines of the function (match rdis dis 0xa14e0 0xd1):
#if 0
0xa14e0  push rsi
0xa14e1  sub rsp,0x30
0xa14e5  mov rsi,rcx
0xa14e8  test byte ptr [rcx+0x70],1
0xa14ec  je short 0xA1545
0xa14ee  mov rax,[rsi+0x40]
0xa14f2  mov rax,[rax]
0xa14f5  mov ecx,0x58
0xa14fa  test rax,rax
0xa14fd  jne short 0xA150B
0xa14ff  mov rax,[rsi+0x38]
0xa1503  mov rax,[rax]
0xa1506  mov ecx,0x50
0xa150b  mov rcx,[rsi+rcx]
0xa150f  movsxd rdx,[rcx]
0xa1512  add rdx,rax
0xa1515  mov rax,[rsi+0x18]
0xa1519  mov rcx,[rax]
0xa151c  sub rdx,rcx
0xa151f  cmp rdx,0x1000
0xa1526  jb short 0xA1540
0xa1528  mov rax,[rcx-8]
0xa152c  add rcx,0xFFFFFFFFFFFFFFF8
0xa1530  sub rcx,rax
0xa1533  cmp rcx,0x20
0xa1537  jae short 0xA1597
0xa1539  add rdx,0x27
0xa153d  mov rcx,rax
0xa1540  call 0xE935700
0xa1545  mov rax,[rsi+0x18]
0xa1549  mov qword ptr [rax],0
0xa1550  mov rax,[rsi+0x38]
0xa1554  mov qword ptr [rax],0
0xa155b  mov rax,[rsi+0x50]
0xa155f  mov dword ptr [rax],0
0xa1565  mov rax,[rsi+0x20]
0xa1569  mov qword ptr [rax],0
0xa1570  mov rax,[rsi+0x40]
0xa1574  mov qword ptr [rax],0
0xa157b  mov rax,[rsi+0x58]
0xa157f  mov dword ptr [rax],0
0xa1585  mov qword ptr [rsi+0x68],0
0xa158d  and byte ptr [rsi+0x70],0xFE
0xa1591  add rsp,0x30
0xa1595  pop rsi
0xa1596  ret
0xa1597  mov qword ptr [rsp+0x20],0
0xa15a0  xor ecx,ecx
0xa15a2  xor edx,edx
0xa15a4  xor r8d,r8d
0xa15a7  xor r9d,r9d
0xa15aa  call qword ptr [0xF9A8C78]
0xa15b0  int3
#endif

void* sub_a14e0(void* a0)
{
    A14e0This* const n = reinterpret_cast<A14e0This*>(a0);

    // 0xa14e0..0xa14e5: push rsi; sub rsp,0x30; mov rsi,rcx (callee-saved register and stack
    // frame; no observable effect)

    // 0xa14e8..0xa14ec: test byte ptr [rcx+0x70],1 ; je short 0xA1545
    if ((n->f70 & 1u) != 0u) {   // 0xa14e8  test byte ptr [rcx+0x70],1 ; 0xa14ec  je short 0xA1545 (bit clear skips to cleanup)

        // 0xa14ee..0xa1506: rax = *(*(a0+0x40)) (idx = 0x58), else rax = *(*(a0+0x38)) (idx = 0x50)
        void* const p40 = n->f40;                            // 0xa14ee  mov rax,[rsi+0x40]
        void* rax = *reinterpret_cast<void**>(p40);          // 0xa14f2  mov rax,[rax]
        std::uintptr_t idx = 0x58;                           // 0xa14f5  mov ecx,0x58
        // 0xa14fa  test rax,rax ; 0xa14fd  jne short 0xA150B
        if (rax == nullptr) {
            rax = *reinterpret_cast<void**>(n->f38);         // 0xa14ff  mov rax,[rsi+0x38] ; 0xa1503  mov rax,[rax]
            idx = 0x50;                                      // 0xa1506  mov ecx,0x50
        }

        // 0xa150b..0xa1526: rdx = (int32_t)*(uint32_t*)(a0+idx) + rax - *(*(a0+0x18)); cmp rdx,0x1000
        void* const buf = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(a0) + idx);  // 0xa150b  mov rcx,[rsi+rcx]
        std::uint64_t rdx = static_cast<std::uint64_t>(static_cast<std::int64_t>(static_cast<std::int32_t>(  // 0xa150f  movsxd rdx,[rcx]
            *reinterpret_cast<std::uint32_t*>(buf))));
        rdx += reinterpret_cast<std::uintptr_t>(rax);        // 0xa1512  add rdx,rax
        void* const p18 = n->f18;                            // 0xa1515  mov rax,[rsi+0x18]
        void* const v18 = *reinterpret_cast<void**>(p18);    // 0xa1519  mov rcx,[rax]
        rdx -= reinterpret_cast<std::uintptr_t>(v18);        // 0xa151c  sub rdx,rcx
        // 0xa151f  cmp rdx,0x1000 ; 0xa1526  jb short 0xA1540
        if (rdx < 0x1000ull) {
            // 0xa1540  call 0xE935700   (rcx = v18 = *(*(a0+0x18)))
            native::sub_e935700(v18);
        } else {
            // 0xa1528..0xa153d: prefix = *(v18 - 8); block_start = (v18 - 8) - prefix; cmp rcx,0x20
            std::uintptr_t const prefix =
                *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<std::uint8_t*>(v18) - 8);  // 0xa1528  mov rax,[rcx-8]
            std::uintptr_t const block_start =   // 0xa152c  add rcx,0xFFFFFFFFFFFFFFF8 ; 0xa1530  sub rcx,rax
                reinterpret_cast<std::uintptr_t>(v18) - 8 - prefix;
            // 0xa1533  cmp rcx,0x20 ; 0xa1537  jae short 0xA1597
            if (block_start >= 0x20) {
                // 0xa1597..0xa15aa: mov qword ptr [rsp+0x20],0 ; xor ecx,edx,r8d,r9d (five zero arguments)
                // 0xa15aa  call qword ptr [0xF9A8C78]   ; [data_f9a8c78], slot pointer read at call time
                using FailFn = void (*)(void*, void*, void*, void*, void*);
                FailFn const failFn = reinterpret_cast<FailFn>(
                    *reinterpret_cast<std::uintptr_t*>(RewriteRegistry::imageBase() + kRvaFailSlot));
                failFn(nullptr, nullptr, nullptr, nullptr, nullptr);   // 0xa15aa  call qword ptr [0xF9A8C78]
                // 0xa15b0  int3   ; block terminator (noreturn)
                __debugbreak();
                __assume(false);
            }
            // 0xa1539..0xa1540: add rdx,0x27 (dead); mov rcx,rax ; call 0xE935700 (rcx = prefix)
            native::sub_e935700(reinterpret_cast<void*>(prefix));   // 0xa1540  call 0xE935700
        }
    }

    // 0xa1545..0xa1596: cleanup stores in original order, then ret (RAX = a0->f58)
    *reinterpret_cast<void**>(n->f18) = nullptr;      // 0xa1545  mov rax,[rsi+0x18] ; 0xa1549  mov qword ptr [rax],0
    *reinterpret_cast<void**>(n->f38) = nullptr;      // 0xa1550  mov rax,[rsi+0x38] ; 0xa1554  mov qword ptr [rax],0
    *reinterpret_cast<std::uint32_t*>(n->f50) = 0;    // 0xa155b  mov rax,[rsi+0x50] ; 0xa155f  mov dword ptr [rax],0
    *reinterpret_cast<void**>(n->f20) = nullptr;      // 0xa1565  mov rax,[rsi+0x20] ; 0xa1569  mov qword ptr [rax],0
    *reinterpret_cast<void**>(n->f40) = nullptr;      // 0xa1570  mov rax,[rsi+0x40] ; 0xa1574  mov qword ptr [rax],0
    void* const ret = n->f58;                         // 0xa157b  mov rax,[rsi+0x58]   (return value)
    *reinterpret_cast<std::uint32_t*>(ret) = 0;       // 0xa157f  mov dword ptr [rax],0
    n->f68 = nullptr;                                 // 0xa1585  mov qword ptr [rsi+0x68],0
    n->f70 = static_cast<std::uint8_t>(n->f70 & 0xFEu);  // 0xa158d  and byte ptr [rsi+0x70],0xFE
    // 0xa1591..0xa1596: add rsp,0x30 ; pop rsi ; ret
    return ret;
}

LIFT_FN(sub_a14e0, "sub_a14e0", 0xA14E0, sub_a14e0, nullptr);

} // namespace native
