// LIFT 0xe818aa0 size 0xcf 1.26.62.01 RendererContextD3D12 ring-buffer clear-by-value
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e818aa0.h"

#include <cstddef>
#include <cstdint>

static_assert(sizeof(void*) == 8, "ptr");

// Verbatim disassembly of [0xe818aa0, 0xe818b6f) (Minecraft Windows 1.26.62.01).
#if 0
0xe818aa0  push rsi
0xe818aa1  mov r8d,edx
0xe818aa4  mov r10d,[rcx+0x7EC8]
0xe818aab  mov edx,[rcx+0x7ECC]
0xe818ab1  mov eax,[rcx+0x7ED4]
0xe818ab7  mov r11d,edx
0xe818aba  sub r11d,eax
0xe818abd  mov esi,r11d
0xe818ac0  sar esi,0x1F
0xe818ac3  and esi,r10d
0xe818ac6  add r11d,esi
0xe818ac9  je 0xE818B6D
0xe818acf  add esi,edx
0xe818ad1  inc eax
0xe818ad3  xor r9d,r9d
0xe818ad6  cmp esi,eax
0xe818ad8  je short 0xE818B49
0xe818ada  mov esi,r11d
0xe818add  and esi,0xFFFFFFFE
0xe818ae0  xor r9d,r9d
0xe818ae3  jmp short 0xE818AF9
0xe818ae5  nop [rax+rax]
0xe818af0  add r9d,2
0xe818af4  cmp esi,r9d
0xe818af7  je short 0xE818B43
0xe818af9  mov eax,[rcx+0x7ED4]
0xe818aff  add eax,r9d
0xe818b02  xor edx,edx
0xe818b04  div r10d
0xe818b07  cmp [rcx+rdx*2+0x7CC0],r8w
0xe818b10  jne short 0xE818B1C
0xe818b12  mov word ptr [rcx+rdx*2+0x7CC0],0xFFFF
0xe818b1c  mov eax,[rcx+0x7ED4]
0xe818b22  add eax,r9d
0xe818b25  inc eax
0xe818b27  xor edx,edx
0xe818b29  div r10d
0xe818b2c  cmp [rcx+rdx*2+0x7CC0],r8w
0xe818b35  jne short 0xE818AF0
0xe818b37  mov word ptr [rcx+rdx*2+0x7CC0],0xFFFF
0xe818b41  jmp short 0xE818AF0
0xe818b43  test r11b,1
0xe818b47  je short 0xE818B6D
0xe818b49  add r9d,[rcx+0x7ED4]
0xe818b50  mov eax,r9d
0xe818b53  xor edx,edx
0xe818b55  div r10d
0xe818b58  cmp [rcx+rdx*2+0x7CC0],r8w
0xe818b61  jne short 0xE818B6D
0xe818b63  mov word ptr [rcx+rdx*2+0x7CC0],0xFFFF
0xe818b6d  pop rsi
0xe818b6e  ret
#endif

namespace native::d3d12 {

// Walk the uint16 ring buffer at this+0x7CC0 over the live range [head, tail) (mod cap),
// two slots per turn, and set to 0xFFFF every slot whose value equals `value`.
void sub_e818aa0(void* a0, unsigned short a1) {
    char* const self = static_cast<char*>(a0);

    // 0xe818aa0..0xe818aab  (push rsi is emitted by the compiler)
    const std::uint16_t value = a1;                                     // 0xe818aa1  mov r8d,edx
    const std::int32_t cap = *reinterpret_cast<std::int32_t*>(self + kRingCapacityOff); // 0xe818aa4  mov r10d,[rcx+0x7EC8]

    // 0xe818aab..0xe818ac9  count = tail - head, rounded up to a multiple of cap when negative
    std::int32_t tail = *reinterpret_cast<std::int32_t*>(self + kRingTailOff); // 0xe818aab  mov edx,[rcx+0x7ECC]
    const std::int32_t head = *reinterpret_cast<std::int32_t*>(self + kRingHeadOff); // 0xe818ab1  mov eax,[rcx+0x7ED4]
    std::int32_t count = tail - head;                                   // 0xe818ab7  mov r11d,edx ; 0xe818aba  sub r11d,eax
    const std::int32_t esi = ((count >> 31) & cap);                     // 0xe818abd..0xe818ac3  mov esi,r11d ; sar esi,0x1F ; and esi,r10d
    count += esi;                                                      // 0xe818ac6  add r11d,esi
    if (count == 0) {                                                  // 0xe818ac9  je 0xE818B6D
        return; // 0xe818b6d..0xe818b6e  pop rsi ; ret (compiler epilog)
    }

    // 0xe818acf..0xe818ad8  single-element case: tail-normalized == head+1
    const std::int32_t normTail = esi + tail;                          // 0xe818acf  add esi,edx
    const std::int32_t headPlus1 = head + 1;                           // 0xe818ad1  inc eax
    std::uint32_t i = 0;                                               // 0xe818ad3  xor r9d,r9d
    if (normTail == headPlus1) {                                       // 0xe818ad6  cmp esi,eax ; 0xe818ad8  je short 0xE818B49
        goto single;
    }

    // 0xe818ada..0xe818ae3  even count (pairs), enter the pair loop at its first slot
    const std::int32_t evenCount = count & static_cast<std::int32_t>(kRingModMask); // 0xe818ada  mov esi,r11d ; 0xe818add  and esi,0xFFFFFFFE
    i = 0;                                                             // 0xe818ae0  xor r9d,r9d
    // 0xe818ae3  jmp short 0xE818AF9  (0xe818ae5 nop [rax+rax] is alignment padding)

    for (;;) {
    pair_first:  // loc_e818af9
        // 0xe818af9..0xe818b12  slot[(head+i)%cap] = 0xFFFF if it equals value
        {
            const std::uint32_t idx = static_cast<std::uint32_t>(head) + i; // 0xe818af9  mov eax,[rcx+0x7ED4] ; 0xe818aff  add eax,r9d
            const std::uint32_t rdx = idx % static_cast<std::uint32_t>(cap); // 0xe818b02..0xe818b04  xor edx,edx ; div r10d
            std::uint16_t* const slot = reinterpret_cast<std::uint16_t*>(self + kRingSlotArrayOff + rdx * 2); // 0xe818b07  cmp [rcx+rdx*2+0x7CC0],r8w
            if (*slot == value) {                                      // 0xe818b10  jne short 0xE818B1C (taken when !=)
                *slot = kRingClearedVal;                              // 0xe818b12  mov word ptr [rcx+rdx*2+0x7CC0],0xFFFF
            }
        }

        // 0xe818b1c..0xe818b37  slot[(head+i+1)%cap] = 0xFFFF if it equals value
        {
            std::uint32_t idx = static_cast<std::uint32_t>(head) + i; // 0xe818b1c  mov eax,[rcx+0x7ED4] ; 0xe818b22  add eax,r9d
            idx += 1;                                                 // 0xe818b25  inc eax
            const std::uint32_t rdx = idx % static_cast<std::uint32_t>(cap); // 0xe818b27..0xe818b29  xor edx,edx ; div r10d
            std::uint16_t* const slot = reinterpret_cast<std::uint16_t*>(self + kRingSlotArrayOff + rdx * 2); // 0xe818b2c  cmp [rcx+rdx*2+0x7CC0],r8w
            if (*slot == value) {                                     // 0xe818b35  jne short 0xE818AF0 (taken when !=)
                *slot = kRingClearedVal;                             // 0xe818b37  mov word ptr [rcx+rdx*2+0x7CC0],0xFFFF
            }
            // 0xe818b41  jmp short 0xE818AF0
        }

    next_pair:  // loc_e818af0
        i += 2;                                                        // 0xe818af0  add r9d,2
        if (i == static_cast<std::uint32_t>(evenCount)) {             // 0xe818af4  cmp esi,r9d ; 0xe818af7  je short 0xE818B43
            goto odd_check;
        }
        goto pair_first;
    }

    odd_check:  // loc_e818b43
    if ((count & 1) == 0) {                                           // 0xe818b43  test r11b,1 ; 0xe818b47  je short 0xE818B6D
        return; // 0xe818b6d..0xe818b6e  pop rsi ; ret (compiler epilog)
    }

    single:  // loc_e818b49
    // 0xe818b49..0xe818b63  last leftover slot[(head+i)%cap] = 0xFFFF if it equals value
    {
        const std::uint32_t idx = static_cast<std::uint32_t>(head) + i; // 0xe818b49  add r9d,[rcx+0x7ED4] ; 0xe818b50  mov eax,r9d
        const std::uint32_t rdx = idx % static_cast<std::uint32_t>(cap); // 0xe818b53..0xe818b55  xor edx,edx ; div r10d
        std::uint16_t* const slot = reinterpret_cast<std::uint16_t*>(self + kRingSlotArrayOff + rdx * 2); // 0xe818b58  cmp [rcx+rdx*2+0x7CC0],r8w
        if (*slot == value) {                                         // 0xe818b61  jne short 0xE818B6D (taken when !=)
            *slot = kRingClearedVal;                                 // 0xe818b63  mov word ptr [rcx+rdx*2+0x7CC0],0xFFFF
        }
    }
    // 0xe818b6d..0xe818b6e  pop rsi ; ret (compiler epilog)
}

} // namespace native::d3d12

// Registry entry: NAME = Sigs.json symbol (sig anchors are appended at the milestone gate).
LIFT_FN(sub_e818aa0, "sub_e818aa0", 0xe818aa0, native::d3d12::sub_e818aa0, nullptr);