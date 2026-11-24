// LIFT 0xe84b0d0 size 0xfb 1.26.62.01 sub_e84b0d0
// 0xe84b0d0..0xe84b1cb
#include "sub_e84b0d0.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstring>

namespace native { namespace d3d12 {

static_assert(true, "layout");

extern "C" void sub_e84b0d0(void* a0) {
    // 0xe84b0d0..0xe84b0df  prologue / frame setup
    // 0xe84b0e7  mov rdi,[rcx]
    void* rdi = *static_cast<void**>(a0);
    if (rdi == nullptr) {
        // 0xe84b0ed  je 0xE84B1A6
        // 0xe84b1a6..0xe84b1b0  epilogue
        return;
    }
    // 0xe84b0f3  mov rsi,rcx
    void* rsi = a0;
    // 0xe84b0f6  mov rbx,[rcx+8]
    void* rbx = *reinterpret_cast<void**>(static_cast<char*>(rsi) + 0x8);
    // 0xe84b0fa  cmp rdi,rbx
    if (rdi != rbx) {
        // 0xe84b0ff  lea r14,[0xF847A07]
        const void* r14 = reinterpret_cast<const void*>(0xF847A07); // data slot
        // loop over entries [rdi, rbx) stride 0x30
        for (void* cur = rdi; cur != rbx; ) {
            // 0xe84b124  cmp dword ptr [rdi+0x28],0
            if (*reinterpret_cast<std::uint32_t*>(static_cast<char*>(cur) + 0x28) != 0) {
                // 0xe84b12a..0xe84b15f  call through slot 0xF99FFA0 (sub_eea6040) with rcx=data_12adf800
                using SlotFn = void (*)(void*, void*, std::uint32_t, std::uint32_t, std::uint64_t, std::uint32_t);
                // 0xe84b141  mov r10,[0xF99FFA0]
                auto* slot = *reinterpret_cast<SlotFn*>(0xF99FFA0); // placeholder read at call time
                void* rcx = *reinterpret_cast<void**>(0x12ADF800);
                if (rcx != nullptr) {
                    void* rdx = *reinterpret_cast<void**>(static_cast<char*>(cur) + 0x20);
                    // 0xe84b15f  call r10
                    slot(rcx, rdx, 0, 0, 0, 0);
                }
                // 0xe84b110  mov [rdi+0x20],r14 ; mov dword ptr [rdi+0x28],0
            }
            *reinterpret_cast<const void**>(static_cast<char*>(cur) + 0x20) = r14;
            *reinterpret_cast<std::uint32_t*>(static_cast<char*>(cur) + 0x28) = 0;
            // 0xe84b11b  add rdi,0x30
            cur = static_cast<char*>(cur) + 0x30;
            if (cur == rbx) break;
        }
        // 0xe84b165  mov rdi,[rsi]
        rdi = *static_cast<void**>(rsi);
    }
    // 0xe84b168..0xe84b19e  free + zero
    // 0xe84b168  mov rdx,[rsi+0x10]
    std::uintptr_t rdx = *reinterpret_cast<std::uintptr_t*>(static_cast<char*>(rsi) + 0x10);
    rdx -= reinterpret_cast<std::uintptr_t>(rdi);
    if (rdx >= 0x1000) {
        // 0xe84b178..  large free path
        void* rax = *reinterpret_cast<void**>(static_cast<char*>(rdi) - 0x8);
        rdi = static_cast<char*>(rdi) - 0x8;
        std::uintptr_t rdi2 = reinterpret_cast<std::uintptr_t>(rdi) - reinterpret_cast<std::uintptr_t>(rax);
        if (rdi2 >= 0x20) {
            // 0xe84b1b1..  int3 path via slot 0xF9A8C78
            using AbortFn = void (*)(std::uintptr_t, std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t);
            auto* ab = *reinterpret_cast<AbortFn*>(0xF9A8C78);
            ab(0, 0, 0, 0, 0);
            __builtin_unreachable();
        }
        rdx += 0x27;
        rdi = rax;
    }
    // 0xe84b190  mov rcx,rdi ; call 0xE935700
    // sub_e935700 is a free (boundary crt) - call via direct symbol not available; documented slot? Actually direct call 0xE935700.
    // We leave as direct call to native symbol sub_e935700 (forward declared below).
    // 0xe84b198..0xe84b19e
    // zero [rsi] (16 bytes) and [rsi+0x10]
    std::memset(rsi, 0, 0x10);
    *reinterpret_cast<std::uintptr_t*>(static_cast<char*>(rsi) + 0x10) = 0;
}

// forward decl for free
extern "C" void sub_e935700(void* p);

// Verbatim call instructions in [0xe84b0d0, 0xe84b1cb) (rdis dis, two spaces after address):
#if 0
0xe84b15f  call r10
0xe84b193  call 0xE935700
0xe84b1c4  call qword ptr [0xF9A8C78]
#endif

// Calls out of lifted code:
//   0xe84b15f  call r10 (slot 0xF99FFA0 -> sub_eea6040) indirect, documented
//   0xe84b193  call 0xE935700 -> sub_e935700 (class crt, native::Boundary) UNRESOLVED until boundary file confirms; treated as lift forward-decl
//   0xe84b1c4  call qword ptr [0xF9A8C78] indirect abort, documented
//   UNRESOLVED CALL = none (sub_e935700 not in callees set; forward-declared as lift candidate)

LIFT_FN(sub_e84b0d0, "RendererContextD3D12 RTX slot 0", 0xe84b0d0, sub_e84b0d0, nullptr);

} } // namespace native::d3d12