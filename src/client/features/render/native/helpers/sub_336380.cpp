// LIFT 0x336380 size 0x97 1.26.62.01 sub_336380
#include "sub_336380.h"

#include <cstdint>
#include <intrin.h>

namespace native {

// Layout assertions (definitions live in sub_336380.h; repeated here so liftcheck sees them
// in the source file).
static_assert(sub_336380Layout::kFrameSize == 0x48, "sub_336380: stack frame is 0x48 bytes");
static_assert(sub_336380Layout::kArg5Slot == 0x20, "sub_336380: 5th-arg slot at [rsp+0x20]");
static_assert(sub_336380Layout::kArg6Slot == 0x28, "sub_336380: 6th-arg slot at [rsp+0x28]");
static_assert(sub_336380Layout::kR14CopySlot == 0x38, "sub_336380: r14 copy slot at [rsp+0x38]");
static_assert(sub_336380Layout::kCookieSlot == 0x40, "sub_336380: cookie slot at [rsp+0x40]");
static_assert(sub_336380Layout::kSpilledA4Slot == 0x88, "sub_336380: spilled a4 slot at [rsp+0x88]");
static_assert(sub_336380Layout::kGblCookieRva == 0x1230A0C0, "sub_336380: stack cookie global at 0x1230A0C0");
static_assert(sub_336380Layout::kData128c1588Rva == 0x128C1588, "sub_336380: data_128c1588 at 0x128C1588");
static_assert(sub_336380Layout::kDispatchSlotRva == 0xF9A8B20, "sub_336380: indirect call slot at 0xF9A8B20");
static_assert(sub_336380Layout::kTagBit == 2, "sub_336380: tag bit is 2");
static_assert(sub_336380Layout::kNegativeResult == -1, "sub_336380: negative results become -1");

// Verbatim call instructions from the disassembly of [0x336380, 0x336417) (rdis dis output).
// Targets: 0xAA3C0 = sub_aa3c0 (`lea rax,[0x128C1588]; ret`, size 0x8 bytes): classified `lift`,
// forward-declared in sub_336380.h and called as sub_aa3c0(); data slot [0xF9A8B20] (indirect
// call, target read at call time); and 0xE951550 (crt boundary, called through its native symbol
// declared in sub_336380.h).
#if 0
0x3363b6  call 0xAA3C0
0x3363d9  call qword ptr [0xF9A8B20]
0x336411  call 0xE951550
#endif

std::int32_t sub_336380(void* a1, void* a2, void* a3, void* a4)
{
    // 0x336380..0x336389: push r14; push rsi; push rdi; push rbx; sub rsp,0x48
    //   Prologue - implicit in the C++ stack frame.

    // 0x336389..0x33639a: mov rsi,r8; mov rdi,rdx; mov rbx,rcx; mov [rsp+0x88],r9
    //   a3 -> rsi, a2 -> rdi, a1 -> rbx; a4 spilled to [rsp+0x88]. Address of the spilled slot:
    //   r14 = lea [rsp+0x88] (0x3363a9); [rsp+0x38] = r14 (0x3363b1, dead store, not read later).
    void** const r14 = &a4;              // 0x3363a9  lea r14,[rsp+0x88];  0x3363b1  mov [rsp+0x38],r14
    (void)r14;                           // [rsp+0x38] = r14 is a dead store

    // 0x33639a..0x3363a9: mov rax,[0x1230A0C0]; xor rax,rsp; mov [rsp+0x40],rax
    const std::uintptr_t cookieSlot =
        *reinterpret_cast<std::uintptr_t*>(native::imageBase() + sub_336380Layout::kGblCookieRva)
        ^ reinterpret_cast<std::uintptr_t>(&cookieSlot);

    // 0x3363b6  call 0xAA3C0  -> sub_aa3c0 (`lea rax,[0x128C1588]; ret`, size 0x8 bytes).
    //   sub_aa3c0 is classified `lift` (docs/data/native_functions.tsv line 15,
    //   docs/data/native_boundary.tsv line 529): forward-declared in sub_336380.h
    //   and called here per hard rule #66.
    const std::uintptr_t rax = sub_aa3c0();  // 0x3363b6 call 0xAA3C0 -> rax

    // 0x3363bb..0x3363c2: mov rcx,[rax]; or rcx,2
    const std::uintptr_t taggedPtr =
        (*reinterpret_cast<std::uintptr_t*>(rax)) | sub_336380Layout::kTagBit;

    // 0x3363c2..0x3363d9: mov [rsp+0x28],r14; mov qword ptr [rsp+0x20],0;
    //   mov rdx,rbx; mov r8,rdi; mov r9,rsi
    //   Indirect call arguments: RCX = taggedPtr, RDX = a1, R8 = a2, R9 = a3,
    //   5th stack arg = 0 ([rsp+0x20]), 6th stack arg = &a4 slot ([rsp+0x28] = r14).
    using DispatchFn = std::int32_t (__cdecl*)(
        std::uintptr_t tagged, void* a1, void* a2, void* a3, std::int32_t arg5, void** arg6Slot);
    // 0x3363d9  call qword ptr [0xF9A8B20]  - function pointer read from data slot at call time.
    const DispatchFn dispatch =
        *reinterpret_cast<DispatchFn*>(native::imageBase() + sub_336380Layout::kDispatchSlotRva);
    const std::int32_t raw = dispatch(taggedPtr, a1, a2, a3, 0, &a4);

    // 0x3363df..0x3363e8: mov ecx,eax; test eax,eax; mov eax,0xFFFFFFFF; cmovns eax,ecx
    //   Negative results become -1; non-negative results pass through unchanged.
    const std::int32_t ret = raw < 0 ? -1 : raw;

    // 0x3363eb..0x3363fd: mov rcx,[rsp+0x40]; xor rcx,rsp; mov rdx,[0x1230A0C0]; cmp rdx,rcx; jne 0x336409
    const std::uintptr_t decodedCookie = cookieSlot ^ reinterpret_cast<std::uintptr_t>(&cookieSlot);
    const std::uintptr_t globalCookie =
        *reinterpret_cast<std::uintptr_t*>(native::imageBase() + sub_336380Layout::kGblCookieRva);
    if (decodedCookie != globalCookie) {                          // 0x3363fd  jne short 0x336409
        // 0x336409..0x336411: mov rcx,[rsp+0x40]; xor rcx,rsp (decoded cookie, recomputed)
        // 0x336411  call 0xE951550  (crt boundary, noreturn on mismatch)
        sub_e951550(decodedCookie);
        // 0x336416  int3  - unreachable after the noreturn boundary call
        __assume(false);
    }

    // 0x3363ff..0x336409: add rsp,0x48; pop rbx; pop rdi; pop rsi; pop r14; ret  (rax = ret)
    return ret;
}

// Footprint: nullptr - the function itself writes only its own stack slots, but its callees
// (lift sub_aa3c0, indirect slot 0xF9A8B20, boundary 0xE951550) may write arbitrary memory,
// so no footprint can be declared statically (same convention as helpers/sub_76850).
LIFT_FN(sub_336380, "sub_336380", 0x336380, sub_336380, nullptr);

} // namespace native
