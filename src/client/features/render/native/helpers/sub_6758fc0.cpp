// LIFT 0x6758fc0 size 0xff 1.26.62.01 sub_6758fc0
#include "client/features/render/native/helpers/sub_6758fc0.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_6758fc0, "sub_6758fc0", 0x6758fc0, sub_6758fc0, nullptr);

// sub_e935700 is lift set; forward-declared here rather than including sub_e935700.h
// (that header's own layout static_assert block is rejected by MSVC in this TU).
// Signature matches sub_e935700.h exactly: void* sub_e935700(void* a0); argument in RCX,
// result in RAX. sub_e935700 is itself a tail jump to sub_392960, which reads only RCX.
namespace native {
void* sub_e935700(void* a0);
}

// sub_6758fc0 == BgfxFrameBuilder::endFrame (1.26.62.01), [0x6758fc0, 0x67590bf).
//
//   self (RCX) -> this object:
//     +0x08 heap   void*  heap block pointer (*(self+0x8))
//     +0x10 count  u64   number of entries (each entry is 0x140 bytes)
//     +0x18 first  void*  first entry (cursor, advanced by 0x140 per iteration)
//     +0x20 last   void*  end sentinel
//   entry (RDI):
//     +0xE8 block   void*   heap block owned by this entry
//     +0xF8 block_end void* end of the block's committed range
//     +0x100 flag   u8    entry is processed iff flag == 1
//   handle (R14 = RDI + 0xE8):
//     +0x00 block   void*   same as entry+0xE8
//     +0x08 pad0x08 void*   zeroed together with block by the 16-byte movups store
//     +0x10 limit   u64   same as entry+0xF8, zeroed after the entry is processed
//
// Walk entries [first, last) step 0x140. For each entry with flag == 1:
//   block = *(entry+0xE8);  if (block != 0) {
//       remaining = *(entry+0xF8) - block;
//       if (remaining <u 0x1000)          sub_e935700(block);
//       else {
//           hdr = *(block - 8);           // heap header size stored 8 bytes before block
//           bias = block - 8 - hdr;
//           if (bias >=u 0x20) fail_path();  // call [0xF9A8C78](0,0,0,0); int3
//           sub_e935700(hdr);                 // remaining += 0x27 is dead:
//                                              // sub_e935700->sub_392960 overwrites RDX
//                                              // before any read, never observable
//       }
//   }
//   *(R14+0x00) = 0; *(R14+0x08) = 0; *(R14+0x10) = 0;   // movups [r14], xmm6==0 ; [r14+0x10]=0
//
// Finish:
//   heap = *(self+0x8); total = count * 0x140;
//   if (total <u 0x1000) return sub_e935700(heap);       // tail call at 0x6759091
//   hdr = *(heap - 8); bias = heap - 8 - hdr;
//   if (bias >=u 0x20) fail_path();
//   return sub_e935700(hdr);                             // tail call at 0x6759091; or rdx,0x27 is dead
//
// Early exit (0x6759096, *(self+0x8) == 0): ret; RAX is never written by this function,
// so its value is whatever the caller left in RAX at entry and is not specified here;
// the lift returns nullptr on this path.
//
// Calls [decided]:
//   0x6758ff0  call 0xE935700        -> native::sub_e935700 (lift set, called directly)
//   0x6759091  jmp   0xE935700        -> tail call native::sub_e935700 (result returned in RAX)
//   0x67590b8  call qword ptr [0xF9A8C78]  -> data-slot target, four zero x64 arguments,
//                                             int3 trap if it returns (slot read at call time)

void* sub_6758fc0(void* self) {
    // 0x6758fc0..0x6758fde: basic block 0
    // 0x6758fc0  push r14
    // 0x6758fc2  push rsi
    // 0x6758fc3  push rdi
    // 0x6758fc4  push rbx
    // 0x6758fc5  sub rsp,0x48
    // 0x6758fc9  movaps [rsp+0x30],xmm6
    // 0x6758fce  mov rsi,rcx
    // 0x6758fd1  mov rcx,[rcx+8]
    // 0x6758fd5  test rcx,rcx
    // 0x6758fd8  je short 0x6759096
    auto* const a0 = reinterpret_cast<sub_6758fc0_this*>(self);   // 0x6758fce mov rsi,rcx
    if (a0->heap == nullptr) {        // 0x6758fd1 mov rcx,[rcx+8] ; 0x6758fd5 test rcx,rcx ; 0x6758fd8 je short 0x6759096
        // 0x6759096..0x67590a5: basic block 15 (early exit)
        // 0x6759096  movaps xmm6,[rsp+0x30]
        // 0x675909b  add rsp,0x48
        // 0x675909f  pop rbx
        // 0x67590a0  pop rdi
        // 0x67590a1  pop rsi
        // 0x67590a2  pop r14
        // 0x67590a4  ret
        // 0x67590a4 ret -- RAX is unspecified by the original on this path
        return nullptr;               // 0x67590a4 ret
    }

    // 0x6758fde..0x6758feb: basic block 1
    // 0x6758fde  mov rdi,[rsi+0x18]
    // 0x6758fe2  mov rbx,[rsi+0x20]
    // 0x6758fe6  cmp rdi,rbx
    // 0x6758fe9  je short 0x6759056
    std::uint8_t* rdi = reinterpret_cast<std::uint8_t*>(a0->first);   // 0x6758fde mov rdi,[rsi+0x18]
    std::uint8_t* const last = reinterpret_cast<std::uint8_t*>(a0->last);  // 0x6758fe2 mov rbx,[rsi+0x20]

    // 0x6758feb..0x6758ff0: basic block 2
    // 0x6758feb  xorps xmm6,xmm6   (xmm6 == 0; restored at every exit, not observable)
    // 0x6758fee  jmp short 0x675900D

    // 0x67590a5..0x67590bf: basic block 16 (corruption/fail path)
    // 0x67590a5  mov qword ptr [rsp+0x20],0   (dead home-slot store, not observable outside this frame)
    // 0x67590ae  xor ecx,ecx
    // 0x67590b0  xor edx,edx
    // 0x67590b2  xor r8d,r8d
    // 0x67590b5  xor r9d,r9d                (four zero x64 arguments)
    // 0x67590b8  call qword ptr [0xF9A8C78]  -> data-slot target read at call time
    // 0x67590be  int3
    // 0x67590bf  int3
    auto fail_path = []() {
        using fail_fn = void(__cdecl*)(void*, void*, void*, void*);
        fail_fn const fail = reinterpret_cast<fail_fn>(
            *reinterpret_cast<uintptr_t*>(
                RewriteRegistry::imageBase() + sub_6758fc0Layout::kFailSlotRva));
        fail(nullptr, nullptr, nullptr, nullptr);   // 0x67590b8 call qword ptr [0xF9A8C78]
        __debugbreak();                             // 0x67590be int3
        __assume(0);                                // 0x67590bf int3: does not return
    };

    if (rdi != last) {                            // 0x6758fe6 cmp rdi,rbx ; 0x6758fe9 je short 0x6759056
        for (;;) {
            // 0x675900d..0x6759016: basic block 5
            // 0x675900d  cmp byte ptr [rdi+0x100],1
            // 0x6759014  jne short 0x6759001
            auto* const entry = reinterpret_cast<sub_6758fc0_entry*>(rdi);
            if (entry->flag == 1) {              // 0x675900d cmp byte ptr [rdi+0x100],1 ; 0x6759014 jne short 0x6759001
                // 0x6759016..0x6759025: basic block 6
                // 0x6759016  lea r14,[rdi+0xE8]
                // 0x675901d  mov rcx,[r14]
                // 0x6759020  test rcx,rcx
                // 0x6759023  je short 0x6759001
                auto* const h = reinterpret_cast<sub_6758fc0_handle*>(rdi + 0xE8);  // 0x6759016 lea r14,[rdi+0xE8]
                void* const block = h->block;   // 0x675901d mov rcx,[r14]
                if (block != nullptr) {         // 0x6759020 test rcx,rcx ; 0x6759023 je short 0x6759001

                    // 0x6759025..0x6759038: basic block 7
            // 0x6759025  mov rdx,[rdi+0xF8]
            // 0x675902c  sub rdx,rcx
            // 0x675902f  cmp rdx,0x1000
            // 0x6759036  jb short 0x6758ff0
            uintptr_t const remaining =
                reinterpret_cast<uintptr_t>(entry->block_end) -
                reinterpret_cast<uintptr_t>(block); // 0x6759025/0x675902c
            if (remaining < 0x1000ull) {            // 0x675902f cmp rdx,0x1000 ; 0x6759036 jb short 0x6758ff0
                // 0x6758ff0..0x6759001: basic block 3
                // 0x6758ff0  call 0xE935700
                // 0x6758ff5  movups [r14],xmm6
                // 0x6758ff9  mov qword ptr [r14+0x10],0
                native::sub_e935700(block);         // 0x6758ff0 call 0xE935700
            } else {
                // 0x6759038..0x6759049: basic blocks 8/9
                // 0x6759038  mov rax,[rcx-8]
                // 0x675903c  add rcx,0xFFFFFFFFFFFFFFF8
                // 0x6759040  sub rcx,rax
                // 0x6759043  cmp rcx,0x20
                // 0x6759047  jae short 0x67590A5
                // 0x6759049  add rdx,0x27   (dead: RDX is overwritten by sub_e935700->sub_392960
                //                   before any read, never observable)
                // 0x675904d  mov rcx,rax
                // 0x6759050  jmp short 0x6758FF0
                uintptr_t const hdr =
                    *reinterpret_cast<uintptr_t*>(
                        reinterpret_cast<std::uint8_t*>(block) - 8);  // 0x6759038 mov rax,[rcx-8]
                uintptr_t const bias =
                    reinterpret_cast<uintptr_t>(block) - 8 -
                    hdr;                 // 0x675903c/0x6759040
                if (bias >= 0x20ull) {                                // 0x6759043 cmp rcx,0x20 ; 0x6759047 jae short 0x67590A5
                    fail_path();                                      // 0x67590a5..0x67590bf
                    __assume(0);
                }
            }                                       // closes else (remaining >= 0x1000)
            // 0x6758ff5  movups [r14],xmm6     W r14+0x00..r14+0x0f (xmm6 == 0)
            // 0x6758ff9  mov qword ptr [r14+0x10],0  W r14+0x10..r14+0x17
            h->block = nullptr;                     // 0x6758ff5 low qword
            h->pad0x08 = nullptr;                   // 0x6758ff5 high qword
            h->limit = 0;                           // 0x6758ff9
        }                                           // closes if (block != nullptr)
    }                                               // closes if (entry->flag == 1)

    // 0x6759001..0x675900d: basic block 4
    // 0x6759001  add rdi,0x140
    // 0x6759008  cmp rdi,rbx
    // 0x675900b  je short 0x6759052
    rdi += 0x140;                                   // 0x6759001 add rdi,0x140
    if (rdi == last) break;                         // 0x6759008 cmp rdi,rbx ; 0x675900b je short 0x6759052
}                                                   // closes for (;;)
}                                                   // closes if (rdi != last)
    // 0x6759052..0x675906b: basic blocks 10/11
    // 0x6759052  mov rcx,[rsi+8]
    // 0x6759056  mov rax,[rsi+0x10]
    // 0x675905a  shl rax,6
    // 0x675905e  lea rdx,[rax+rax*4]        rdx = count * 0x140
    // 0x6759062  cmp rdx,0x1000
    // 0x6759069  jb short 0x6759083
    void* const heap = a0->heap;             // 0x6759052 mov rcx,[rsi+8]
    uintptr_t const total = static_cast<uintptr_t>(a0->count) * 0x140ull;
    if (total < 0x1000ull) {                 // 0x6759062 cmp rdx,0x1000 ; 0x6759069 jb short 0x6759083
        // 0x6759083..0x6759096: basic block 14
        // 0x6759083  movaps xmm6,[rsp+0x30]
        // 0x6759088  add rsp,0x48
        // 0x675908c  pop rbx
        // 0x675908d  pop rdi
        // 0x675908e  pop rsi
        // 0x675908f  pop r14
        // 0x6759091  jmp 0xE935700
        // 0x6759091 jmp 0xE935700 -> tail call native::sub_e935700(heap); result in RAX
        return native::sub_e935700(heap);    // 0x6759091
    }
    // 0x675906b..0x675907c: basic blocks 12/13
    // 0x675906b  mov rax,[rcx-8]
    // 0x675906f  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x6759073  sub rcx,rax
    // 0x6759076  cmp rcx,0x20
    // 0x675907a  jae short 0x67590A5
    // 0x675907c  or rdx,0x27   (dead: RDX is overwritten by sub_e935700->sub_392960
    //                   before any read, never observable)
    // 0x6759080  mov rcx,rax
    // 0x6759091  jmp 0xE935700   (basic block 14 tail call)
    uintptr_t const hdr =
        *reinterpret_cast<uintptr_t*>(
            reinterpret_cast<std::uint8_t*>(heap) - 8);  // 0x675906b mov rax,[rcx-8]
    uintptr_t const bias =
        reinterpret_cast<uintptr_t>(heap) - 8 -
        hdr;                // 0x675906f/0x6759073
    if (bias >= 0x20ull) {                               // 0x6759076 cmp rcx,0x20 ; 0x675907a jae short 0x67590A5
        fail_path();                                     // 0x67590a5..0x67590bf
        __assume(0);
    }
    // 0x6759091 jmp 0xE935700 -> tail call native::sub_e935700(*(heap - 8))
    return native::sub_e935700(reinterpret_cast<void*>(hdr));  // 0x6759091
}

#if 0
// Verbatim call instructions from the disassembly of [0x6758fc0, 0x67590bf) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
0x6758ff0  call 0xE935700
0x67590b8  call qword ptr [0xF9A8C78]
#endif

} // namespace native::helpers
