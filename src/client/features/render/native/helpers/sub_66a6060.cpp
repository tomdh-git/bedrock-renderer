// LIFT 0x66a6060 size 0x122 1.26.62.01 sub_66a6060
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_66a6060.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

// Callees: all three are `os` boundary functions in docs/data/native_boundary.tsv,
// called through native::boundary wrappers. Callee signatures are not derivable
// from the listing; the wrappers follow the convention used by the other lifts
// of these same callees (e.g. sub_6622590).
namespace native::boundary {
    void sub_e938cb0(std::uintptr_t a0, std::uintptr_t a1, std::uintptr_t a2, std::uintptr_t a3);
    void sub_e935740(std::uintptr_t a0, std::uintptr_t a1, std::uintptr_t a2, std::uintptr_t a3);
    void sub_e938d70(std::uintptr_t a0, std::uintptr_t a1, std::uintptr_t a2, std::uintptr_t a3);
}

// Read-only absolute data globals (image addresses as listed in the disassembly).
static std::uint32_t& g_seq1() { return *reinterpret_cast<std::uint32_t*>(0x0129441ACULL); }  // data_129441ac
static std::uint32_t& g_tlsIndex() { return *reinterpret_cast<std::uint32_t*>(0x0128767C8ULL); }  // data_128767c8
static std::uint32_t& g_seq2() { return *reinterpret_cast<std::uint32_t*>(0x0129441B0ULL); }  // data_129441b0

// Verbatim call instructions from the disassembly of [0x66a6060, 0x66a6182) (rdis `fn` output).
// Preprocessor-excluded below so the skeleton stays valid C++.
// All calls go through native::boundary wrappers (os boundary).
#if 0
0x66a60d2  call 0xE938CB0
0x66a60e6  call 0xE935740
0x66a60ee  call 0xE938D70
0x66a6154  call 0xE938CB0
0x66a616c  call 0xE935740
0x66a6178  call 0xE938D70
#endif

// Layout assertions repeated in the source file (offsets/widths proven from the listing).
static_assert(offsetof(native::helpers::sub_66a6060_rcx, begin) == 0x28, "sub_66a6060 rcx+0x28 field");
static_assert(offsetof(native::helpers::sub_66a6060_rcx, end) == 0x30, "sub_66a6060 rcx+0x30 field");
static_assert(offsetof(native::helpers::sub_66a6060_rcx, tail) == 0x40, "sub_66a6060 rcx+0x40 field");
static_assert(sizeof(native::helpers::sub_66a6060_rcx) >= 0x48, "sub_66a6060 rcx sizeof lower bound");
static_assert(offsetof(native::helpers::sub_66a6060_entry, flag0x10) == 0x10, "sub_66a6060 entry+0x10 field");
static_assert(sizeof(native::helpers::sub_66a6060_entry) >= 0x11, "sub_66a6060 entry sizeof lower bound");

namespace native::helpers {

uintptr_t sub_66a6060(void* self) {
    // 0x66a6060..0x66a607e (block 0): prologue, then load cursor/end cursors and set flag = 1.
    sub_66a6060_rcx* const a0 = static_cast<sub_66a6060_rcx*>(self);             // rcx = self
    std::uint8_t* cursor = reinterpret_cast<std::uint8_t*>(a0->begin);           // 0x66a606f  mov r14,[rcx+0x28]
    std::uint8_t* const end = reinterpret_cast<std::uint8_t*>(a0->end);          // 0x66a6073  mov r15,[rcx+0x30]
    std::uint8_t flag = 1;                                                       // 0x66a6077  mov bl,1
    std::uint32_t* const seq1 = &g_seq1();                                       // 0x66a607e  lea rsi,[0x129441AC]
    void* const osCtx1 = reinterpret_cast<void*>(0x001F59570ULL);                // 0x66a6085  lea rdi,[0x1F59570]
    std::uint32_t* const seq2 = &g_seq2();                                       // 0x66a6147  lea rax,[0x129441B0]
    void* const osCtx2 = reinterpret_cast<void*>(0x001F5D7A0ULL);                // 0x66a6165  lea rcx,[0x1F5D7A0]
    sub_66a6060_entry* curEntry = nullptr;
    void* tail = nullptr;
    // Scratch registers (declared here so no goto crosses an initialization).
    std::uint32_t eax = 0;
    std::uint32_t tlsIdx = 0;
    std::uintptr_t teb = 0;
    std::uintptr_t tlsSlot = 0;
    std::uint32_t eax2 = 0;
    std::uint32_t tlsIdx2 = 0;
    std::uintptr_t teb2 = 0;
    std::uintptr_t tlsSlot2 = 0;
    std::uintptr_t rax = 0;
    std::uint8_t al = 0;
    if (cursor == end) goto L_0x66a60f8;                                         // 0x66a6079  cmp r14,r15 ; 0x66a607c  je short 0x66A60F8
    goto L_0x66a60a3;                                                            // 0x66a608c  jmp short 0x66A60A3

L_0x66a607e:;                                                                    // 0x66a607e..0x66a608e (block 1): lea rsi/rdi — state set up above
L_0x66a608e:;                                                                    // 0x66a608e..0x66a6090 (block 2): xchg ax,ax — padding, no state change

L_0x66a6090:                                                                     // 0x66a6090..0x66a609a (block 3): flag &= current entry's flag byte bit 0
    // 0x66a6090  test bl,bl
    // 0x66a6092  setne bl
    // 0x66a6095  and bl,[r12+0x10]
    flag = static_cast<std::uint8_t>((flag != 0 ? 1u : 0u) & (curEntry->flag0x10 & 1u));
    goto L_0x66a609a;

L_0x66a609a:                                                                     // 0x66a609a..0x66a60a3 (block 4): advance cursor by 0x10
    // 0x66a609a  add r14,0x10
    cursor += 0x10;
    // 0x66a609e  cmp r14,r15
    // 0x66a60a1  je short 0x66A60F8
    if (cursor == end) goto L_0x66a60f8;

L_0x66a60a3:                                                                     // 0x66a60a3..0x66a60ab (block 5): load current entry
    // 0x66a60a3  mov r12,[r14]
    // 0x66a60a6  test r12,r12
    // 0x66a60a9  je short 0x66A609A
    curEntry = reinterpret_cast<sub_66a6060_entry*>(*reinterpret_cast<void**>(cursor));
    if (curEntry == nullptr) goto L_0x66a609a;

L_0x66a60ab:                                                                     // 0x66a60ab..0x66a60cc (block 6): sequence vs TLS slot +4; jle skips the scope
    // 0x66a60ab  mov eax,[0x129441AC]
    eax = *seq1;
    // 0x66a60b1  mov edx,[0x128767C8]
    tlsIdx = *reinterpret_cast<std::uint32_t*>(0x0128767C8ULL);
    // 0x66a60b7  mov r8,gs:[0x58]
    teb = __readgsqword(0x58);
    // 0x66a60c0  mov rdx,[r8+rdx*8]
    tlsSlot = *reinterpret_cast<std::uintptr_t*>(teb + tlsIdx * 8);
    // 0x66a60c4  cmp eax,[rdx+4]
    // 0x66a60ca  jle short 0x66A6090
    if (static_cast<std::int32_t>(eax) <= static_cast<std::int32_t>(*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(tlsSlot) + 4))) goto L_0x66a6090;

L_0x66a60cc:                                                                     // 0x66a60cc..0x66a60e3 (block 7): enter scope; failure if sequence became -1
    // 0x66a60cc  mov r13,rcx
    // 0x66a60cf  mov rcx,rsi
    // 0x66a60d2  call 0xE938CB0
    // 0x66a60d7  mov rcx,r13
    native::boundary::sub_e938cb0(reinterpret_cast<std::uintptr_t>(seq1), 0, 0, 0);
    // 0x66a60da  cmp dword ptr [0x129441AC],0xFFFFFFFF
    // 0x66a60e1  jne short 0x66A6090
    if (*seq1 != 0xFFFFFFFFu) goto L_0x66a6090;

L_0x66a60e3:                                                                     // 0x66a60e3..0x66a60f8 (block 8): failure sequence, then block 3
    // 0x66a60e3  mov rcx,rdi
    // 0x66a60e6  call 0xE935740
    native::boundary::sub_e935740(reinterpret_cast<std::uintptr_t>(osCtx1), 0, 0, 0);
    // 0x66a60eb  mov rcx,rsi
    // 0x66a60ee  call 0xE938D70
    native::boundary::sub_e938d70(reinterpret_cast<std::uintptr_t>(seq1), 0, 0, 0);
    // 0x66a60f3  mov rcx,r13
    // 0x66a60f6  jmp short 0x66A6090
    goto L_0x66a6090;

L_0x66a60f8:                                                                     // 0x66a60f8..0x66a6101 (block 9): tail entry pointer
    // 0x66a60f8  mov rsi,[rcx+0x40]
    // 0x66a60fc  test rsi,rsi
    // 0x66a60ff  je short 0x66A612A
    tail = reinterpret_cast<void*>(a0->tail);
    if (tail == nullptr) goto L_0x66a612a;

L_0x66a6101:                                                                     // 0x66a6101..0x66a6122 (block 10): second sequence vs TLS; jg enters increment path
    // 0x66a6101  mov eax,[0x129441B0]
    eax2 = *reinterpret_cast<std::uint32_t*>(0x0129441B0ULL);
    // 0x66a6107  mov edx,[0x128767C8]
    tlsIdx2 = *reinterpret_cast<std::uint32_t*>(0x0128767C8ULL);
    // 0x66a610d  mov r8,gs:[0x58]
    teb2 = __readgsqword(0x58);
    // 0x66a6116  mov rdx,[r8+rdx*8]
    tlsSlot2 = *reinterpret_cast<std::uintptr_t*>(teb2 + tlsIdx2 * 8);
    // 0x66a611a  cmp eax,[rdx+4]
    // 0x66a6120  jg short 0x66A6147
    if (static_cast<std::int32_t>(eax2) > static_cast<std::int32_t>(*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(tlsSlot2) + 4))) goto L_0x66a6147;
    goto L_0x66a6122;

L_0x66a6122:                                                                     // 0x66a6122..0x66a612a (block 11): flag &= tail entry's flag byte bit 0
    // 0x66a6122  test bl,bl
    // 0x66a6124  setne bl
    // 0x66a6127  and bl,[rsi+0x10]
    flag = static_cast<std::uint8_t>((flag != 0 ? 1u : 0u) & (reinterpret_cast<sub_66a6060_entry*>(tail)->flag0x10 & 1u));
    goto L_0x66a612a;

L_0x66a612a:                                                                     // 0x66a612a..0x66a6147 (block 12): result and epilogue
    // 0x66a612a  mov rax,[rcx+0x28]
    rax = reinterpret_cast<std::uintptr_t>(a0->begin);
    // 0x66a612e  cmp rax,[rcx+0x30]
    // 0x66a6132  setne al
    al = (rax != reinterpret_cast<std::uintptr_t>(a0->end)) ? 1u : 0u;
    // 0x66a6135  and al,bl
    al = static_cast<std::uint8_t>(al & flag);
    // 0x66a6137  add rsp,0x20 ; pops ; ret  (RAX = begin with AL replaced by the result)
    return (rax & ~0xFFULL) | static_cast<std::uintptr_t>(al);

L_0x66a6147:                                                                     // 0x66a6147..0x66a6165 (block 13): enter second scope; failure if -1
    // 0x66a6147  lea rax,[0x129441B0]
    // 0x66a614e  mov rdi,rcx
    // 0x66a6151  mov rcx,rax
    // 0x66a6154  call 0xE938CB0
    // 0x66a6159  mov rcx,rdi
    native::boundary::sub_e938cb0(reinterpret_cast<std::uintptr_t>(seq2), 0, 0, 0);
    // 0x66a615c  cmp dword ptr [0x129441B0],0xFFFFFFFF
    // 0x66a6163  jne short 0x66A6122
    if (*reinterpret_cast<std::uint32_t*>(0x0129441B0ULL) != 0xFFFFFFFFu) goto L_0x66a6122;

L_0x66a6165:                                                                     // 0x66a6165..0x66a6182 (block 14): failure sequence, then block 11
    // 0x66a6165  lea rcx,[0x1F5D7A0]
    // 0x66a616c  call 0xE935740
    native::boundary::sub_e935740(reinterpret_cast<std::uintptr_t>(osCtx2), 0, 0, 0);
    // 0x66a6171  lea rcx,[0x129441B0]
    // 0x66a6178  call 0xE938D70
    native::boundary::sub_e938d70(reinterpret_cast<std::uintptr_t>(seq2), 0, 0, 0);
    // 0x66a617d  mov rcx,rdi
    // 0x66a6180  jmp short 0x66A6122
    goto L_0x66a6122;
}

LIFT_FN(sub_66a6060, "sub_66a6060", 0x66a6060, sub_66a6060, nullptr);

} // namespace native::helpers
