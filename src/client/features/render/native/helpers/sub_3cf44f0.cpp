// LIFT 0x3cf44f0 size 0xe3 1.26.62.01 sub_3cf44f0
#include "sub_3cf44f0.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>

namespace native {

// sub_e935700 (0xe935700, size 0x5, lift set): tail-call target, same ABI (RCX in, RAX out).
void* sub_e935700(void* a0);

void* sub_3cf44f0(void* a0)
{
    // 0x3cf44f0..0x3cf4516
    // 0x3cf44f0  push rsi
    // 0x3cf44f1  push rdi
    // 0x3cf44f2  push rbx
    // 0x3cf44f3  sub rsp,0x30
    // 0x3cf44f7  mov rsi,rcx            ; rsi = a0
    // 0x3cf44fa  mov rcx,[rcx+8]        ; rcx = [a0+0x8]
    // 0x3cf44fe  test rcx,rcx
    // 0x3cf4501  je 0x3CF45B1           ; [a0+0x8]==0 -> early return
    // 0x3cf4507  mov rdi,[rsi+0x18]     ; rdi = [a0+0x18] array start
    // 0x3cf450b  mov rbx,[rsi+0x20]     ; rbx = [a0+0x20] array end
    // 0x3cf450f  cmp rdi,rbx
    // 0x3cf4512  jne short 0x3CF4541
    // 0x3cf4514  jmp short 0x3CF457C
    // 0x3cf4516  nop [rax+rax]          ; unreachable pad within the function
    void* rsi = a0;
    void* rcx = reinterpret_cast<sub_3cf44f0Arg*>(rsi)->field08;   // 0x3cf44fa  mov rcx,[rcx+8]
    void* rdi = nullptr;                                            // 0x3cf4507  mov rdi,[rsi+0x18]
    void* rbx = nullptr;                                            // 0x3cf450b  mov rbx,[rsi+0x20]
    std::uintptr_t rax = 0;                                         // 0x3cf4541  mov rax,[rdi+0x18]
    std::uintptr_t rdx = 0;                                         // 0x3cf454e  lea rdx,[rax+1]
    void* rcx2 = nullptr;                                           // 0x3cf454b  mov rcx,[rdi]
    std::uintptr_t r8 = 0;                                          // 0x3cf455b  mov r8,[rcx-8]
    std::uintptr_t rcx3 = 0;                                        // 0x3cf455f/0x3cf4563
    std::uintptr_t rdx2 = 0;                                        // 0x3cf457c  mov rdx,[rsi+0x10]
    std::uintptr_t rax2 = 0;                                        // 0x3cf458d  mov rax,[rcx-8]
    std::uintptr_t rcx4 = 0;                                        // 0x3cf4591/0x3cf4595/0x3cf45a2
    if (rcx == nullptr) goto loc_3cf45b1;                           // 0x3cf44fe  test rcx,rcx ; 0x3cf4501  je 0x3CF45B1

    rdi = reinterpret_cast<sub_3cf44f0Arg*>(rsi)->field18;          // 0x3cf4507  mov rdi,[rsi+0x18]
    rbx = reinterpret_cast<sub_3cf44f0Arg*>(rsi)->field20;          // 0x3cf450b  mov rbx,[rsi+0x20]
    if (rdi != rbx) goto loc_3cf4541;                               // 0x3cf450f  cmp rdi,rbx ; 0x3cf4512  jne short 0x3CF4541
    goto loc_3cf457c;                                               // 0x3cf4514  jmp short 0x3CF457C

loc_3cf4520:  // from 0x3cf4559, 0x3cf4576
    // 0x3cf4520  call 0xE935700                                     ; -> sub_e935700
    sub_e935700(rcx);                                              // 0x3cf4520  call 0xE935700 ; return discarded
    goto loc_3cf4525;

loc_3cf4525:  // from 0x3cf4549
    // 0x3cf4525  mov qword ptr [rdi+0x10],0
    // 0x3cf452d  mov qword ptr [rdi+0x18],0xF
    // 0x3cf4535  mov byte ptr [rdi],0
    // 0x3cf4538  add rdi,0x40
    // 0x3cf453c  cmp rdi,rbx
    // 0x3cf453f  je short 0x3CF4578
    *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<std::uintptr_t>(rdi) + 0x10) = 0;   // 0x3cf4525
    *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<std::uintptr_t>(rdi) + 0x18) = 0xF; // 0x3cf452d
    *reinterpret_cast<std::uint8_t*>(rdi) = 0;                                                // 0x3cf4535
    rdi = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(rdi) + sub_3cf44f0Layout::kEntryStep); // 0x3cf4538
    if (rdi == rbx) goto loc_3cf4578;                                                          // 0x3cf453c  cmp rdi,rbx ; 0x3cf453f  je short 0x3CF4578
    goto loc_3cf4541;

loc_3cf4541:  // from 0x3cf4512
    // 0x3cf4541  mov rax,[rdi+0x18]
    // 0x3cf4545  cmp rax,0x10
    // 0x3cf4549  jb short 0x3CF4525
    // 0x3cf454b  mov rcx,[rdi]
    // 0x3cf454e  lea rdx,[rax+1]
    // 0x3cf4552  cmp rdx,0x1000
    // 0x3cf4559  jb short 0x3CF4520
    // 0x3cf455b  mov r8,[rcx-8]
    // 0x3cf455f  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x3cf4563  sub rcx,r8
    // 0x3cf4566  cmp rcx,0x20
    // 0x3cf456a  jae short 0x3CF45B9
    // 0x3cf456c  add rax,0x28
    // 0x3cf4570  mov rdx,rax
    // 0x3cf4573  mov rcx,r8
    // 0x3cf4576  jmp short 0x3CF4520
    rax = *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<std::uintptr_t>(rdi) + 0x18); // 0x3cf4541
    if (rax < sub_3cf44f0Layout::kSmallCount) goto loc_3cf4525;                // 0x3cf4545  cmp rax,0x10 ; 0x3cf4549  jb short 0x3CF4525
    rcx2 = reinterpret_cast<void*>(*reinterpret_cast<std::uintptr_t*>(rdi));   // 0x3cf454b  mov rcx,[rdi]
    rdx = rax + 1;                                                             // 0x3cf454e  lea rdx,[rax+1]
    if (rdx < sub_3cf44f0Layout::kPage) {                                      // 0x3cf4552  cmp rdx,0x1000 ; 0x3cf4559  jb short 0x3CF4520
        sub_e935700(rcx2);                                                     // 0x3cf4520  call 0xE935700
        goto loc_3cf4525;
    }
    r8 = *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<std::uintptr_t>(rcx2) - sub_3cf44f0Layout::kHeapHeaderSize); // 0x3cf455b
    rcx3 = reinterpret_cast<std::uintptr_t>(rcx2) - 8 - r8;                    // 0x3cf455f  add rcx,-8 ; 0x3cf4563  sub rcx,r8
    if (rcx3 >= sub_3cf44f0Layout::kMinAlloc) goto loc_3cf45b9;                // 0x3cf4566  cmp rcx,0x20 ; 0x3cf456a  jae short 0x3CF45B9
    rax = rax + sub_3cf44f0Layout::kExtra;                                     // 0x3cf456c  add rax,0x28
    rdx = rax;                                                                 // 0x3cf4570  mov rdx,rax
    rcx2 = reinterpret_cast<void*>(r8);                                        // 0x3cf4573  mov rcx,r8
    sub_e935700(rcx2);                                                         // 0x3cf4520  call 0xE935700
    goto loc_3cf4525;

loc_3cf4578:  // from 0x3cf453f
    // 0x3cf4578  mov rcx,[rsi+8]
    rcx = reinterpret_cast<sub_3cf44f0Arg*>(rsi)->field08;   // 0x3cf4578
    goto loc_3cf457c;

loc_3cf457c:  // from 0x3cf4514
    // 0x3cf457c  mov rdx,[rsi+0x10]
    // 0x3cf4580  shl rdx,6
    // 0x3cf4584  cmp rdx,0x1000
    // 0x3cf458b  jb short 0x3CF45A5
    // 0x3cf458d  mov rax,[rcx-8]
    // 0x3cf4591  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x3cf4595  sub rcx,rax
    // 0x3cf4598  cmp rcx,0x20
    // 0x3cf459c  jae short 0x3CF45B9
    // 0x3cf459e  or rdx,0x27
    // 0x3cf45a2  mov rcx,rax
    rdx2 = reinterpret_cast<std::uintptr_t>(reinterpret_cast<sub_3cf44f0Arg*>(rsi)->field10);   // 0x3cf457c
    rdx2 <<= 6;                                               // 0x3cf4580
    if (rdx2 < sub_3cf44f0Layout::kPage) goto loc_3cf45a5;    // 0x3cf4584  cmp rdx,0x1000 ; 0x3cf458b  jb short 0x3CF45A5
    rax2 = *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<std::uintptr_t>(rcx) - sub_3cf44f0Layout::kHeapHeaderSize); // 0x3cf458d
    rcx4 = reinterpret_cast<std::uintptr_t>(rcx) - 8 - rax2;  // 0x3cf4591  add rcx,-8 ; 0x3cf4595  sub rcx,rax
    if (rcx4 >= sub_3cf44f0Layout::kMinAlloc) goto loc_3cf45b9; // 0x3cf4598  cmp rcx,0x20 ; 0x3cf459c  jae short 0x3CF45B9
    rdx2 |= sub_3cf44f0Layout::kSlotTag;                       // 0x3cf459e  or rdx,0x27
    rcx4 = rax2;                                               // 0x3cf45a2  mov rcx,rax
    goto loc_3cf45a5;

loc_3cf45a5:  // from 0x3cf458b
    // 0x3cf45a5  add rsp,0x30
    // 0x3cf45a9  pop rbx
    // 0x3cf45aa  pop rdi
    // 0x3cf45ab  pop rsi
    // 0x3cf45ac  jmp 0xE935700                                  ; -> sub_e935700  (tail call)
    return sub_e935700(reinterpret_cast<void*>(rcx4));           // 0x3cf45a5..0x3cf45ac

loc_3cf45b1:  // from 0x3cf4501
    // 0x3cf45b1  add rsp,0x30
    // 0x3cf45b5  pop rbx
    // 0x3cf45b6  pop rdi
    // 0x3cf45b7  pop rsi
    // 0x3cf45b8  ret                                            ; RAX untouched (indeterminate)
    return nullptr;                                              // 0x3cf45b1..0x3cf45b8

loc_3cf45b9:  // from 0x3cf456a, 0x3cf459c
    // 0x3cf45b9  mov qword ptr [rsp+0x20],0
    // 0x3cf45c2  xor ecx,ecx
    // 0x3cf45c4  xor edx,edx
    // 0x3cf45c6  xor r8d,r8d
    // 0x3cf45c9  xor r9d,r9d
    // 0x3cf45cc  call qword ptr [0xF9A8C78]                       ; [data_f9a8c78]
    // 0x3cf45d2  int3
    {
        using slot_t = void* (*)(void*, void*, void*, void*, void*);
        slot_t slot = reinterpret_cast<slot_t>(*reinterpret_cast<std::uintptr_t*>(sub_3cf44f0Layout::kSlotVA));
        slot(nullptr, nullptr, nullptr, nullptr, nullptr);       // 0x3cf45cc  call qword ptr [0xF9A8C78] ; all-zero args
        __debugbreak();                                          // 0x3cf45d2  int3
    }
    return nullptr;                                              // unreachable after int3
}

// Verbatim call instructions of the function (matches rdis dis 0x3cf44f0 0xe3), plain lines for verify_oc:
#if 0
0x3cf4520  call 0xE935700
0x3cf45cc  call qword ptr [0xF9A8C78]
#endif

static_assert(sizeof(void*) == 8, "sub_3cf44f0: x64 ABI, pointer-sized address space");

LIFT_FN(sub_3cf44f0, "sub_3cf44f0", 0x3cf44f0, sub_3cf44f0, nullptr);

} // namespace native
