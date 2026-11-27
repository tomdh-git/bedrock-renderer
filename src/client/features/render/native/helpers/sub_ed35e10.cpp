// LIFT 0xed35e10 size 0x49 1.26.62.01 sub_ed35e10
#include "sub_ed35e10.h"

namespace native {

// sub_ed35e10 (0xed35e10, size 0x49, 1.26.62.01): instruction-by-instruction reversal of
// [0xed35e10, 0xed35e59); see sub_ed35e10.h for the full verbatim listing and the layout
// constants. Calls, in order:
//   0xed35e26  call qword ptr [0xF9A6FD8]   import data slot, GetCurrentProcess() (rule 68: pointer read from the slot)
//   0xed35e3a  call 0xEEC5880               lift callee native::sub_eec5880 (K32GetProcessMemoryInfo thunk)
//   0xed35e4c  call 0xE951550               crt boundary native::sub_e951550 (stack-cookie check)
// No game memory outside the stack frame is written; the only game-data read is the cookie
// global [data_1230a0c0]. Fail fast: the cookie check terminates on mismatch, like the original.

// Verbatim instructions of [0xed35e10, 0xed35e59), copied from `rdis dis 0xed35e10 0x49`:
#if 0
0xed35e10  sub rsp,0x88
0xed35e17  mov rax,[0x1230A0C0]
0xed35e1e  xor rax,rsp
0xed35e21  mov [rsp+0x70],rax
0xed35e26  call qword ptr [0xF9A6FD8]
0xed35e2c  mov r8d,0x48
0xed35e32  lea rdx,[rsp+0x20]
0xed35e37  mov rcx,rax
0xed35e3a  call 0xEEC5880
0xed35e3f  mov rax,[rsp+0x30]
0xed35e44  mov rcx,[rsp+0x70]
0xed35e49  xor rcx,rsp
0xed35e4c  call 0xE951550
0xed35e51  add rsp,0x88
0xed35e58  ret
#endif

static_assert(sub_ed35e10Layout::kStackFrameSize == 0x88ull, "sub_ed35e10: frame size is 0x88 bytes");
static_assert(sub_ed35e10Layout::kStackBufferSize == 0x48ull, "sub_ed35e10: buffer size is 0x48 bytes");

std::uintptr_t sub_ed35e10(void)
{
    // 0xed35e10..0xed35e17  sub rsp,0x88   (0x88-byte stack frame; the compiler lays out our locals in it)
    std::uint8_t buffer[sub_ed35e10Layout::kStackBufferSize];   // PROCESS_MEMORY_COUNTERS buffer at rsp+0x20
    std::uintptr_t cookieSlot;                                  // cookie slot at rsp+0x70

    // 0xed35e17  mov rax,[0x1230A0C0]     ; [data_1230a0c0]
    // 0xed35e1e  xor rax,rsp
    // 0xed35e21  mov [rsp+0x70],rax
    cookieSlot = (*reinterpret_cast<std::uintptr_t*>(RewriteRegistry::imageBase() + sub_ed35e10Layout::kCookieGlobalRva)
        ^ reinterpret_cast<std::uintptr_t>(&cookieSlot));
    //     0xed35e17  mov rax,[0x1230A0C0]
    //     0xed35e1e  xor rax,rsp
    //     0xed35e21  mov [rsp+0x70],rax

    // 0xed35e26  call qword ptr [0xF9A6FD8]  ; [data_f9a6fd8] import data slot (rule 68)
    void* (*getCurrentProcess)(void) = reinterpret_cast<void* (*)(void)>(
        *reinterpret_cast<std::uintptr_t*>(RewriteRegistry::imageBase() + sub_ed35e10Layout::kGetCurrentProcessSlotRva));
    void* const hProcess = getCurrentProcess();
    //     0xed35e26  call qword ptr [0xF9A6FD8]

    // 0xed35e2c  mov r8d,0x48
    // 0xed35e32  lea rdx,[rsp+0x20]
    // 0xed35e37  mov rcx,rax
    // 0xed35e3a  call 0xEEC5880  ; -> sub_eec5880
    const std::uint32_t cb = sub_ed35e10Layout::kStackBufferSize;
    sub_eec5880(hProcess, buffer, cb);
    //     0xed35e2c  mov r8d,0x48   ; 0xed35e32  lea rdx,[rsp+0x20]   ; 0xed35e37  mov rcx,rax   ; 0xed35e3a  call 0xEEC5880

    // 0xed35e3f  mov rax,[rsp+0x30]     ; buffer+0x10
    const std::uintptr_t result = *reinterpret_cast<std::uintptr_t*>(buffer + sub_ed35e10Layout::kWorkingSetSizeOffset);
    //     0xed35e3f  mov rax,[rsp+0x30]

    // 0xed35e44  mov rcx,[rsp+0x70]
    // 0xed35e49  xor rcx,rsp
    // 0xed35e4c  call 0xE951550  ; -> sub_e951550 cookie check
    sub_e951550(cookieSlot ^ reinterpret_cast<std::uintptr_t>(&cookieSlot));
    //     0xed35e44  mov rcx,[rsp+0x70]   ; 0xed35e49  xor rcx,rsp   ; 0xed35e4c  call 0xE951550

    // 0xed35e51  add rsp,0x88
    // 0xed35e58  ret
    return result;
}

LIFT_FN(sub_ed35e10, "sub_ed35e10", 0xED35E10, sub_ed35e10, nullptr);

} // namespace native
