// LIFT 0xe806810 size 0x11c 1.26.62.01 sub_e806810
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e806810.h"

#include <cstdint>
#include <cstddef>
#include <cstring>

static_assert(sizeof(void*) == 8, "e806810 x64");

namespace native {
namespace {
// Registry entry (mirrors the sibling lift sub_e834330 in the same folder).
LIFT_FN(sub_e806810, "sub_e806810", 0xe806810, Off);
} // namespace

extern "C" void* sub_e806810(void* out, const std::uint16_t* u16Ptr) {
    // 0xe806810..0xe806818: push rbp,r15,r14,rsi,rdi,rbx; sub rsp,0x48; lea rbp,[rsp+0x40]
    std::uint8_t frame[0x48];
    void* const rbp = reinterpret_cast<void*>(reinterpret_cast<char*>(frame) + 0x40);

    // 0xe80681c  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
    *reinterpret_cast<std::uint64_t*>(rbp) = 0xFFFFFFFFFFFFFFFEULL;

    // 0xe806829  mov rsi,rcx        (rcx = out argument)
    // 0xe80682c  movzx edx,word ptr [rdx]   (rdx = pointer to the u16 value)
    const std::uint32_t u16val = static_cast<std::uint32_t>(
        *reinterpret_cast<const std::uint16_t*>(u16Ptr));

    // tmp string object at rbp-0x20: [tmp+0x00] data ptr, [tmp+0x10] size, [tmp+0x18] capacity
    void* const tmp = reinterpret_cast<void*>(reinterpret_cast<char*>(rbp) - 0x20);
    std::size_t* const tmpSize = reinterpret_cast<std::size_t*>(reinterpret_cast<char*>(rbp) - 0x10);
    std::size_t* const tmpCap = reinterpret_cast<std::size_t*>(reinterpret_cast<char*>(rbp) - 0x08);

    // 0xe80682f  lea rdi,[rbp-0x20]
    // 0xe806833  mov rcx,rdi
    // 0xe806836  call 0xE834520        ; -> sub_e834520
    sub_e834520(tmp, u16val);   // builds UTF-16 decimal string into tmp; return value ignored

    // 0xe80683b  mov rax,[rbp-0x10]
    // 0xe80683f  mov rcx,[rbp-8]
    const std::size_t size = *tmpSize;
    const std::size_t cap = *tmpCap;

    // 0xe806843  mov rdx,rcx
    // 0xe806846  sub rdx,rax
    // 0xe806849  cmp rdx,5
    // 0xe80684d  jae short 0xE806870   (enough spare room -> inline prefix insertion)
    if (cap - size >= 5) {
        // loc_e806870:
        // 0xe806870  lea rdx,[rax+5]
        // 0xe806874  mov [rbp-0x10],rdx
        *tmpSize = size + 5;

        // 0xe806878  cmp rcx,8
        // 0xe80687c  mov rdx,[rbp-0x20]
        const void* data = *reinterpret_cast<void**>(tmp);

        // 0xe806880  mov rbx,rdi        (rdi still = rbp-0x20 = &tmp)
        // 0xe806883  cmovae rbx,rdx     (if cap>=8 unsigned: data pointer, else &tmp = SSO)
        void* rbx = tmp;
        if (cap >= 8) rbx = data;

        // 0xe806887  lea r8,[0xF848D00]
        // 0xe80688e  cmp rbx,r8
        // 0xe806891  setae r8b
        const bool r8b = (reinterpret_cast<std::uintptr_t>(rbx) >= kSlotF848D00);

        // 0xe806895  lea r14,[0xF848CF6]   "LVbo: "
        const void* litLvbo = reinterpret_cast<const void*>(kData_LVbo);

        // 0xe80689c  lea r9,[rbx+rax*2]
        // 0xe8068a0  cmp r9,r14
        // 0xe8068a3  setb r9b
        const bool r9b = (reinterpret_cast<std::uintptr_t>(
                              reinterpret_cast<const char*>(rbx) + size * 2)
                          < reinterpret_cast<std::uintptr_t>(litLvbo));

        // 0xe8068a7  or r9b,r8b
        // 0xe8068aa  mov r15d,5
        // 0xe8068b0  jne short 0xE8068C2
        std::size_t r15 = 5;
        if (!(r9b || r8b)) {
            // 0xe8068b2  mov r15,rbx
            // 0xe8068b5  sub r15,r14
            r15 = reinterpret_cast<std::uintptr_t>(rbx)
                - reinterpret_cast<std::uintptr_t>(litLvbo);
            // 0xe8068b8  jbe short 0xE8068BF
            if (reinterpret_cast<std::uintptr_t>(rbx)
                <= reinterpret_cast<std::uintptr_t>(litLvbo)) {
                // 0xe8068bf  xor r15d,r15d
                r15 = 0;
            } else {
                // 0xe8068ba  sar r15,1
                r15 = r15 / 2;
            }
        }

        // loc_e8068c2:
        // 0xe8068c2  cmp rcx,8
        // 0xe8068c6  cmovae rdi,rdx
        // 0xe8068ca  add rdi,0xA
        void* rdi = (cap >= 8) ? data : tmp;
        void* destShift = reinterpret_cast<char*>(rdi) + 10;

        // 0xe8068ce  lea r8,[rax*2+2]
        const std::size_t count = size * 2 + 2;

        // 0xe8068d6  mov rcx,rdi
        // 0xe8068d9  mov rdx,rbx
        // 0xe8068dc  call 0xEEC6DE0        ; -> sub_eec6de0
        sub_eec6de0(destShift, rbx, count);

        // 0xe8068e1  lea rdi,[r15+r15]
        const std::size_t prefixLen = r15 * 2;

        // 0xe8068e5  mov rcx,rbx
        // 0xe8068e8  mov rdx,r14
        // 0xe8068eb  mov r8,rdi
        // 0xe8068ee  call 0xEEC6EC0        ; -> sub_eec6ec0
        sub_eec6ec0(rbx, litLvbo, prefixLen);

        // 0xe8068f3  lea rdx,[r14+r15*2]
        // 0xe8068f7  add rdx,0xA
        const void* src2 = reinterpret_cast<const char*>(litLvbo) + r15 * 2 + 10;
        // 0xe8068fb  lea rcx,[rbx+r15*2]
        void* dest2 = reinterpret_cast<char*>(rbx) + r15 * 2;
        // 0xe8068ff  mov r8d,0xA
        // 0xe806905  sub r8,rdi
        const std::size_t count2 = 10 - prefixLen;
        // 0xe806908  call 0xEEC6EC0        ; -> sub_eec6ec0
        sub_eec6ec0(dest2, src2, count2);
    } else {
        // 0xe80684f  lea r8,[0xF848CF6]   "LVbo: "
        // 0xe806856  lea rcx,[rbp-0x20]
        // 0xe80685a  mov edx,5
        // 0xe80685f  mov r9d,5
        // 0xe806865  call 0xE834330        ; -> sub_e834330
        sub_e834330(tmp, 5, reinterpret_cast<void*>(kData_LVbo),
                    reinterpret_cast<void*>(5));
        // 0xe80686a  nop
        // 0xe80686b  jmp 0xE80690D
        goto output;
    }

output:
    // loc_e80690d:
    // 0xe80690d  movups xmm0,[rbp-0x20]
    // 0xe806911  movups xmm1,[rbp-0x10]
    // 0xe806915  movups [rsi+0x10],xmm1
    // 0xe806919  movups [rsi],xmm0
    std::memcpy(out, tmp, 32);

    // 0xe80691c  mov rax,rsi
    return out;
}

// Verbatim call quotes (plain lines for verify_oc)
#if 0
0xe806836  call 0xE834520
0xe806865  call 0xE834330
0xe8068dc  call 0xEEC6DE0
0xe8068ee  call 0xEEC6EC0
0xe806908  call 0xEEC6EC0
#endif

} // namespace native
