// LIFT 0xe8764f0 size 0x105 1.26.62.01 BgfxFrameBuilder slot 16
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/BgfxFrameBuilder_slot16.h"

#include <cstdint>
#include <cstddef>

namespace native {

static_assert(sizeof(void*) == 8, "e8764f0: x64 target");

namespace {

// 0x47E8F0: STL vector grow helper (stl boundary, docs/data/native_boundary.tsv row 0x47e8f0).
// Call site 0xe87656c: rcx=out, rdx=length, r8=&scratch, r9=totalCapacity. Return unused.
native::Boundary<void, void*, std::uint32_t, void*, std::size_t> sub_47e8f0("sub_47e8f0");

// 0xEEC6ED0: CRT memory import thunk (crt boundary, jmp qword ptr [IAT]).
// Call site 0xe876579: rcx=end, rdx=0, r8=newEnd-end.
native::Boundary<void, void*, void*, std::size_t> sub_eec6ed0("sub_eec6ed0");

// 0xE951550: __security_check_cookie (crt boundary).
// Call site 0xe8765ef: rcx=cookieSlot ^ rsp.
native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");

// Indirect calls at 0xe876517 and 0xe87658d: `call qword ptr [0xF9A7480]`.
// The cell at RVA 0xF9A7480 holds the std::basic_istream::read vtable slot pointer.
// Per the indirect-call hard rule: read the pointer from the slot at call time,
// call as a function pointer with the same arguments.

} // namespace

extern "C" bool BgfxFrameBuilder_slot16(void* stream, void* out) {
    // 0xe8764f0..0xe87650c
    // push rsi; push rdi; push rbx; sub rsp,0x50
    // mov rdi,rdx; mov rsi,rcx
    // mov rax,[0x1230A0C0]; xor rax,rsp; mov [rsp+0x48],rax
    const std::uintptr_t cookieStored = *reinterpret_cast<const std::uintptr_t*>(kGblCookie);
    std::uintptr_t cookieSlot = 0;
    cookieSlot = cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot); // [rsp+0x48]

    char* const o = static_cast<char*>(out);
    void* const s = stream;

    bool success = false;

    // 0xe87650c..0xe87651d
    // lea rdx,[rsp+0x2C]; mov r8d,4; call qword ptr [0xF9A7480]   (quoted below)
    std::uint32_t lengthBuf = 0;
    using ReadFn = void* (*)(void*, void*, std::uint32_t);
    void* readResult = (*reinterpret_cast<ReadFn*>(0x140000000 + kIstreamReadSlot))(s, &lengthBuf, 4);

    // 0xe87651d..0xe876524
    // mov rax,[rax+8]; test rax,rax
    std::int64_t gcount = *reinterpret_cast<const std::int64_t*>(reinterpret_cast<std::uintptr_t>(readResult) + 8);
    if (gcount < 0) {
        // 0xe8765c2..0xe8765e2 (exception path; falls through to cookie_check like the original)
        std::uintptr_t exceptionObjAddr = reinterpret_cast<std::uintptr_t>(0x140000000 + kExceptObj);
        std::uintptr_t typeInfoAddr = reinterpret_cast<std::uintptr_t>(0x140000000 + kExceptTypeInfo);
        sub_eec6d80(reinterpret_cast<void**>(&exceptionObjAddr), reinterpret_cast<const void*>(typeInfoAddr));
        goto cookie_check;
    }

    // 0xe87652a..0xe876530
    // cmp rax,4; jne short 0xE876552
    if (gcount != 4) {
        // 0xe876552..0xe876556
        // xor eax,eax; jmp short 0xE8765A6
        goto cookie_check;
    }

    // 0xe876530..0xe876549
    // mov edx,[rsp+0x2C]; mov rax,[rdi]; mov rcx,[rdi+8]
    // mov r9,rcx; sub r9,rax; mov r8,rdx; sub r8,r9
    std::uint32_t length = lengthBuf;                       // [rsp+0x2C]
    std::uint8_t* begin = *reinterpret_cast<std::uint8_t**>(o + kOutBegin);
    std::uint8_t* end   = *reinterpret_cast<std::uint8_t**>(o + kOutEnd);
    std::size_t available = static_cast<std::size_t>(end - begin);
    if (static_cast<std::size_t>(length) >= available) {    // jae short 0xE876556
        // 0xe876556..0xe876558
        // jbe short 0xE876582   (taken iff length == available)
        if (static_cast<std::size_t>(length) == available) {
            goto second_read;
        }
        // 0xe876558..0xe876564
        // mov r9,[rdi+0x10]; sub r9,rax; cmp r9,rdx; jae short 0xE876573
        std::uint8_t* capacity = *reinterpret_cast<std::uint8_t**>(o + kOutCapacity);
        std::size_t totalCapacity = static_cast<std::size_t>(capacity - begin);
        if (totalCapacity >= static_cast<std::size_t>(length)) { // jae short 0xE876573
            // 0xe876573..0xe876579
            // lea rbx,[rcx+r8]; xor edx,edx
            std::uint8_t* newEnd = end + (static_cast<std::size_t>(length) - available);
            sub_eec6ed0(end, nullptr, static_cast<std::size_t>(newEnd - end)); // quoted below
            *reinterpret_cast<std::uint8_t**>(o + kOutEnd) = newEnd;
            goto second_read;
        }
        // 0xe876564..0xe876571
        // lea r8,[rsp+0x30]; mov rcx,rdi; call 0x47E8F0   (quoted below); jmp short 0xE876582
        std::uintptr_t scratchSlot = 0;
        sub_47e8f0(o, length, reinterpret_cast<void*>(&scratchSlot), totalCapacity);
        goto second_read;
    }
    // 0xe876549..0xe876552
    // add rax,rdx; mov [rdi+8],rax; jmp short 0xE876582
    *reinterpret_cast<std::uint8_t**>(o + kOutEnd) = begin + static_cast<std::size_t>(length);
    goto second_read;

second_read:
    // 0xe876582..0xe87658d
    // mov rdx,[rdi]; mov r8d,[rsp+0x2C]; mov rcx,rsi
    begin = *reinterpret_cast<std::uint8_t**>(o + kOutBegin);
    readResult = (*reinterpret_cast<ReadFn*>(0x140000000 + kIstreamReadSlot))(s, begin, length);

    // 0xe876593..0xe87659a
    // mov rax,[rax+8]; test rax,rax
    gcount = *reinterpret_cast<const std::int64_t*>(reinterpret_cast<std::uintptr_t>(readResult) + 8);
    if (gcount < 0) {
        // 0xe8765c2..0xe8765e2 (exception path)
        std::uintptr_t exceptionObjAddr = reinterpret_cast<std::uintptr_t>(0x140000000 + kExceptObj);
        std::uintptr_t typeInfoAddr = reinterpret_cast<std::uintptr_t>(0x140000000 + kExceptTypeInfo);
        sub_eec6d80(reinterpret_cast<void**>(&exceptionObjAddr), reinterpret_cast<const void*>(typeInfoAddr));
        goto cookie_check;
    }
    // 0xe87659c..0xe8765a3
    // mov ecx,[rsp+0x2C]; cmp rax,rcx; sete al
    success = (gcount == static_cast<std::int64_t>(length));

cookie_check:
    // 0xe8765a6..0xe8765c1
    // mov rcx,[rsp+0x48]; xor rcx,rsp; mov rdx,[0x1230A0C0]; cmp rdx,rcx; jne short 0xE8765E7
    // add rsp,0x50; pop rbx; pop rdi; pop rsi; ret
    std::uintptr_t check = cookieSlot ^ reinterpret_cast<std::uintptr_t>(&cookieSlot);
    if (check != cookieStored) {
        // 0xe8765e7..0xe8765f5
        // mov rcx,[rsp+0x48]; xor rcx,rsp; call 0xE951550   (quoted below); int3
        sub_e951550(check);
    }
    return success;
}

// LIFT_FN registry entry (per RENDER_NATIVE_SPEC.md section 1.4)
LIFT_FN(e8764f0, "BgfxFrameBuilder slot 16", 0xE8764F0, BgfxFrameBuilder_slot16, nullptr);

} // namespace native

#if 0
// Verbatim call quotes for liftcheck (verify_oc parses plain lines)
0xe876517  call qword ptr [0xF9A7480]
0xe87656c  call 0x47E8F0
0xe876579  call 0xEEC6ED0
0xe87658d  call qword ptr [0xF9A7480]
0xe8765e2  call 0xEEC6D80
0xe8765ef  call 0xE951550
#endif
