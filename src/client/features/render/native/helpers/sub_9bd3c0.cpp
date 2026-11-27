// LIFT 0x9bd3c0 size 0x82 1.26.62.01 sub_9bd3c0
#include "sub_9bd3c0.h"

static_assert(sizeof(void*) == 8, "sub_9bd3c0: x64 ABI, pointer-sized address space");

namespace native {

// sub_9bd3c0 (0x9bd3c0, size 0x82, 1.26.62.01).
// Guard function: checks g_128d8040 against TLS[g_128767c8]+4.
// If g_128d8040 <= TLS_limit: calls sub_9bd230(&g_128d7fc0, a0->field0) and returns its result.
// If g_128d8040 > TLS_limit: error sequence:
//   sub_e938cb0(&g_128d8040); if g_128d8040 != -1 retry normal;
//   sub_9bde00();
//   sub_e935740(&sub_9bdf00);
//   sub_e938d70(&g_128d8040);
//   retry normal.
// All paths return sub_9bd230's RAX.
//
// Instruction-by-instruction reversal with address ranges:

std::uintptr_t sub_9bd3c0(void* a0)
{
    // 0x9bd3c0..0x9bd3f5: prologue and guard check
    // 0x9bd3c0  push rbp
    // 0x9bd3c1  push rsi
    // 0x9bd3c2  sub rsp,0x28
    // 0x9bd3c6  lea rbp,[rsp+0x20]
    // 0x9bd3cb  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
    // 0x9bd3d3  mov rsi,rcx
    // 0x9bd3d6  mov eax,[0x128D8040]                          ; g_128d8040
    // 0x9bd3dc  mov ecx,[0x128767C8]                          ; g_128767c8 (TLS index)
    // 0x9bd3e2  mov rdx,gs:[0x58]                             ; TEB
    // 0x9bd3eb  mov rcx,[rdx+rcx*8]                           ; TLS slot[g_128767c8]
    // 0x9bd3ef  cmp eax,[rcx+4]                               ; compare g_128d8040 with TLS+4
    // 0x9bd3f5  jg short 0x9BD40D                             ; if greater -> error_path

    std::uint32_t field0 = 0;  // declared here to avoid C2362 (goto skips init); assigned in normal_path

    std::uint32_t g_128d8040_val = *reinterpret_cast<std::uint32_t*>(RewriteRegistry::imageBase() + sub_9bd3c0Layout::kG128D8040Rva);          // 0x9bd3d6  mov eax,[0x128D8040]
    std::uint32_t tls_index = *reinterpret_cast<std::uint32_t*>(RewriteRegistry::imageBase() + sub_9bd3c0Layout::kG128767C8Rva);               // 0x9bd3dc  mov ecx,[0x128767C8]
    void* tls_base = *reinterpret_cast<void**>(__readgsqword(0x58) + tls_index * 8);                                   // 0x9bd3e2..0x9bd3eb
    if (g_128d8040_val > *reinterpret_cast<std::uint32_t*>(reinterpret_cast<uintptr_t>(tls_base) + 4)) {              // 0x9bd3ef..0x9bd3f5
        goto error_path;
    }

normal_path:
    // 0x9bd3f7..0x9bd40c: normal path
    // 0x9bd3f7  mov edx,[rsi]                                 ; edx = a0->field0
    // 0x9bd3f9  lea rcx,[0x128D7FC0]                          ; rcx = &g_128d7fc0
    // 0x9bd400  call 0x9BD230                                 ; sub_9bd230(&g_128d7fc0, field0)
    // 0x9bd405  nop
    // 0x9bd406  add rsp,0x28
    // 0x9bd40a  pop rsi
    // 0x9bd40b  pop rbp
    // 0x9bd40c  ret

    field0 = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<uintptr_t>(a0) + sub_9bd3c0Layout::kArgField0Offset);  // 0x9bd3f7  mov edx,[rsi]
    return sub_9bd230(                                                                                                           // 0x9bd3f9..0x9bd400
        reinterpret_cast<void*>(RewriteRegistry::imageBase() + sub_9bd3c0Layout::kG128D7FC0Rva),
        field0
    );

error_path:
    // 0x9bd40d..0x9bd440: error path
    // 0x9bd40d  lea rcx,[0x128D8040]                          ; rcx = &g_128d8040
    // 0x9bd414  call 0xE938CB0                                ; sub_e938cb0(&g_128d8040)
    // 0x9bd419  cmp dword ptr [0x128D8040],0xFFFFFFFF         ; check g_128d8040
    // 0x9bd420  jne short 0x9BD3F7                            ; if != -1 -> normal_path
    // 0x9bd422  call 0x9BDE00                                 ; sub_9bde00()
    // 0x9bd427  nop
    // 0x9bd428  lea rcx,[0x9BDF00]                            ; rcx = &sub_9bdf00
    // 0x9bd42f  call 0xE935740                                ; sub_e935740(&sub_9bdf00)
    // 0x9bd434  lea rcx,[0x128D8040]                          ; rcx = &g_128d8040
    // 0x9bd43b  call 0xE938D70                                ; sub_e938d70(&g_128d8040)
    // 0x9bd440  jmp short 0x9BD3F7                            ; -> normal_path

    sub_e938cb0(                                                                                                               // 0x9bd40d..0x9bd414
        reinterpret_cast<void*>(RewriteRegistry::imageBase() + sub_9bd3c0Layout::kG128D8040Rva)
    );
    if (*reinterpret_cast<std::int32_t*>(RewriteRegistry::imageBase() + sub_9bd3c0Layout::kG128D8040Rva) != -1) {           // 0x9bd419..0x9bd420
        goto normal_path;
    }
    sub_9bde00();                                                                                                              // 0x9bd422  call 0x9BDE00
    sub_e935740(                                                                                                               // 0x9bd428..0x9bd42f
        reinterpret_cast<void*>(RewriteRegistry::imageBase() + sub_9bd3c0Layout::kSub9BDF00Rva)
    );
    sub_e938d70(                                                                                                               // 0x9bd434..0x9bd43b
        reinterpret_cast<void*>(RewriteRegistry::imageBase() + sub_9bd3c0Layout::kG128D8040Rva)
    );
    goto normal_path;                                                                                                          // 0x9bd440  jmp short 0x9BD3F7
}

// Verbatim call instruction quotes (match rdis dis 0x9bd3c0 0x82 exactly):
#if 0
0x9bd400  call 0x9BD230
0x9bd414  call 0xE938CB0
0x9bd422  call 0x9BDE00
0x9bd42f  call 0xE935740
0x9bd43b  call 0xE938D70
#endif

} // namespace native

// LIFT_FN registration inside namespace native (per sub_7e6d0.cpp pattern)
namespace native {
LIFT_FN(sub_9bd3c0, "sub_9bd3c0", 0x9BD3C0, native::sub_9bd3c0, nullptr);
}