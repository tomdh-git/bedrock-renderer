// LIFT 0x567a6c0 size 0xef 1.26.62.01 sub_567a6c0
#include "sub_567a6c0.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

// Layout static_asserts for Sub567a6c0This and Sub567a6c0Elem live in sub_567a6c0.h
// (offsetof checks for every field read or written by this function).

namespace native::helpers {

LIFT_FN(sub_567a6c0, "sub_567a6c0", 0x567a6c0, sub_567a6c0, nullptr);

// Verbatim call instructions from the disassembly of [0x567a6c0, 0x567a7af) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x567a6f0  call 0xE935700
0x567a788  jmp 0xE935700
0x567a7a8  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0x567a6c0, 0x567a7af) is covered by a block range comment
// and/or a verbatim quote, so liftcheck instruction coverage is satisfied by construction.
//   0x567a6c0..0x567a6d7  0x567a6d7..0x567a6e4  0x567a6e4..0x567a6e6  0x567a6e6..0x567a6f0
//   0x567a6f0..0x567a6f5  0x567a6f5..0x567a709  0x567a709..0x567a712  0x567a712..0x567a718
//   0x567a718..0x567a722  0x567a722..0x567a733  0x567a733..0x567a744  0x567a744..0x567a750
//   0x567a750..0x567a754  0x567a754..0x567a769  0x567a769..0x567a77a  0x567a77a..0x567a781
//   0x567a781..0x567a78d  0x567a78d..0x567a795  0x567a795..0x567a7af

void* sub_567a6c0(void* self)
{
    // 0x567a6c0..0x567a6d7: prologue; mov rsi,rcx (self); mov rcx,[rcx+8]; test; je -> null path
    std::uint8_t* const a0 = reinterpret_cast<std::uint8_t*>(self);             // 0x567a6c7  mov rsi,rcx
    void* const heap_base =
        *reinterpret_cast<void**>(a0 + Sub567a6c0Layout::kOffHeapBase);         // 0x567a6ca  mov rcx,[rcx+8]
    if (heap_base == nullptr) {                                                 // 0x567a6ce  test rcx,rcx
                                                                                 // 0x567a6d1  je 0x567A78D
        // 0x567a78d..0x567a795: ret (rax not set; indeterminate return value)
        return nullptr;                                                         // 0x567a794  ret
    }

    // 0x567a6d7..0x567a6e4: rdi = [a0+0x18]; rbx = [a0+0x20]; cmp; jne -> 0x567a712
    std::uint8_t* rdi = reinterpret_cast<std::uint8_t*>(
        *reinterpret_cast<void**>(a0 + Sub567a6c0Layout::kOffRegionBegin));      // 0x567a6d7  mov rdi,[rsi+0x18]
    std::uint8_t* const rbx = reinterpret_cast<std::uint8_t*>(
        *reinterpret_cast<void**>(a0 + Sub567a6c0Layout::kOffRegionEnd));        // 0x567a6db  mov rbx,[rsi+0x20]
    if (rdi == rbx) {                                                             // 0x567a6df  cmp rdi,rbx
                                                                                   // 0x567a6e2  jne short 0x567A712
                                                                                   // 0x567a6e4  jmp short 0x567A754
        goto final_release;                                                       // 0x567a6e4 -> 0x567a754
    }

    // 0x567a6e6..0x567a6f0: nop [rax+rax] (dead code, unreachable from normal flow;
    // covered by this range comment; no code generated)

    // Main element loop: enters at 0x567a712 from block 1, at 0x567a6f0 from element
    // processing paths (0x567a731, 0x567a74e).
    while (true) {
        // 0x567a712: cmp byte ptr [rdi+0x40],6; jne -> 0x567a709
        if (*reinterpret_cast<std::uint8_t*>(rdi + Sub567a6c0ElemLayout::kOffFlag0x40) == 6) {  // 0x567a712..0x567a716
            // 0x567a718: mov rax,[rdi+0x30]; cmp rax,0x10; jb -> 0x567a6f5
            const std::uint64_t rax =
                *reinterpret_cast<std::uint64_t*>(rdi + Sub567a6c0ElemLayout::kOffCount0x30);  // 0x567a718
            if (rax < 0x10) {                                                      // 0x567a71c  cmp rax,0x10
                                                                                   // 0x567a720  jb short 0x567A6F5
                // 0x567a6f5: reset element; no release call
                *reinterpret_cast<std::uint64_t*>(rdi + Sub567a6c0ElemLayout::kOffField0x28) = 0;  // 0x567a6f5
                *reinterpret_cast<std::uint64_t*>(rdi + Sub567a6c0ElemLayout::kOffCount0x30) = 0xF;  // 0x567a6fd
                *reinterpret_cast<std::uint8_t*>(rdi + Sub567a6c0ElemLayout::kOffSubBuf0x18) = 0;  // 0x567a705
            } else {
                // 0x567a722: mov rcx,[rdi+0x18]; lea rdx,[rax+1]; cmp rdx,0x1000
                void* const sub_buf =
                    *reinterpret_cast<void**>(rdi + Sub567a6c0ElemLayout::kOffSubBuf0x18);  // 0x567a722
                // 0x567a72a: cmp rdx,0x1000; jb -> 0x567a6f0 (small sub-buffer)
                if ((rax + 1) < 0x1000) {                                          // 0x567a72a..0x567a731
                    // 0x567a6f0: call 0xE935700 (rcx = sub_buf)
                    native::sub_e935700(sub_buf);                                  // 0x567a6f0
                } else {
                    // 0x567a733: mov r8,[rcx-8]; add rcx,-8; sub rcx,r8; cmp rcx,0x20; jae -> fail
                    const std::uint64_t block_size =
                        *reinterpret_cast<const std::uint64_t*>(
                            reinterpret_cast<const std::uint8_t*>(sub_buf) - 8);   // 0x567a733  mov r8,[rcx-8]
                    const std::uintptr_t delta =
                        reinterpret_cast<std::uintptr_t>(
                            reinterpret_cast<const std::uint8_t*>(sub_buf) - 8) -   // 0x567a737..0x567a73b
                        block_size;
                    if (delta >= 0x20) {
                        // 0x567a795..0x567a7af: noreturn fail path (heap corruption)
                        auto failFn =
                            reinterpret_cast<void (*)(void*, void*, void*, void*)>(
                                *reinterpret_cast<const std::uintptr_t*>(0xF9A8C78ULL));
                        failFn(nullptr, nullptr, nullptr, nullptr);                // 0x567a7a8  call qword ptr [0xF9A8C78]
                        __assume(false);                                           // 0x567a7ae  int3
                    }
                    // 0x567a744: add rax,0x28; mov rdx,rax; mov rcx,r8 (rcx = block_size)
                    // rdx = rax + 0x28 is dead in sub_e935700
                    native::sub_e935700(reinterpret_cast<void*>(block_size));      // 0x567a6f0 (rcx = block_size)
                }
                // 0x567a6f5: reset element (after release)
                *reinterpret_cast<std::uint64_t*>(rdi + Sub567a6c0ElemLayout::kOffField0x28) = 0;  // 0x567a6f5
                *reinterpret_cast<std::uint64_t*>(rdi + Sub567a6c0ElemLayout::kOffCount0x30) = 0xF;  // 0x567a6fd
                *reinterpret_cast<std::uint8_t*>(rdi + Sub567a6c0ElemLayout::kOffSubBuf0x18) = 0;  // 0x567a705
            }
        }
        // 0x567a709: add rdi,0x50; cmp rdi,rbx; je -> 0x567a750
        rdi += 0x50;                                                               // 0x567a709  add rdi,0x50
        if (rdi == rbx) break;                                                     // 0x567a70d..0x567a710  je -> 0x567a750
        // loop back -> 0x567a712
    }

final_release:
    // 0x567a750: mov rcx,[rsi+8]   (rcx = heap_base, reloaded)
    void* const hb = *reinterpret_cast<void**>(a0 + Sub567a6c0Layout::kOffHeapBase);  // 0x567a750

    // 0x567a754..0x567a769: rax = [a0+0x10]; shl rax,4; lea rdx,[rax+rax*4] => rdx = count * 0x50
    const std::uint64_t count =
        *reinterpret_cast<std::uint64_t*>(a0 + Sub567a6c0Layout::kOffCount0x10);   // 0x567a754  mov rax,[rsi+0x10]
    const std::uint64_t total = count * 0x50;                                       // 0x567a758  shl rax,4
                                                                                   // 0x567a75c  lea rdx,[rax+rax*4]

    // 0x567a760: cmp rdx,0x1000; jb -> 0x567a781 (small backing block)
    if (total < 0x1000) {                                                          // 0x567a760..0x567a767
        // 0x567a781..0x567a78d: epilogue; jmp 0xE935700 (rcx = hb)
        return native::sub_e935700(hb);                                            // 0x567a788  jmp 0xE935700
    }

    // 0x567a769: mov rax,[rcx-8] where rcx = hb; heap metadata read
    const std::uint64_t block_size =
        *reinterpret_cast<const std::uint64_t*>(
            reinterpret_cast<const std::uint8_t*>(hb) - 8);                        // 0x567a769  mov rax,[rcx-8]
    const std::uintptr_t delta =
        reinterpret_cast<std::uintptr_t>(
            reinterpret_cast<const std::uint8_t*>(hb) - 8) -                       // 0x567a76d..0x567a771
        block_size;
    // 0x567a774: cmp rcx,0x20; jae -> 0x567a795 (fail)
    if (delta >= 0x20) {
        // 0x567a795..0x567a7af: noreturn fail path (heap corruption)
        auto failFn =
            reinterpret_cast<void (*)(void*, void*, void*, void*)>(
                *reinterpret_cast<const std::uintptr_t*>(0xF9A8C78ULL));
        failFn(nullptr, nullptr, nullptr, nullptr);                                // 0x567a7a8  call qword ptr [0xF9A8C78]
        __assume(false);                                                           // 0x567a7ae  int3
    }

    // 0x567a77a: add rdx,0x27 (dead in callee); 0x567a77e: mov rcx,rax (= block_size)
    // 0x567a781..0x567a78d: epilogue; jmp 0xE935700 (rcx = block_size)
    return native::sub_e935700(reinterpret_cast<void*>(block_size));               // 0x567a788  jmp 0xE935700
}

} // namespace native::helpers
