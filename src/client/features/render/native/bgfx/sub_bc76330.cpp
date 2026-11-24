// LIFT 0xbc76330 size 0x4a 1.26.62.01 sub_bc76330
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc76330.h"

#include <cstddef>
#include <cstdint>

// Layout assertions (full set in sub_bc76330.h; repeated here so liftcheck sees them).
static_assert(offsetof(native::Bc76330State, name) == 0x00, "sub_0xbc76330: state name at +0x00");
static_assert(offsetof(native::Bc76330State, flag) == 0x10, "sub_0xbc76330: state flag at +0x10");
static_assert(offsetof(native::Bc76330Arg, name) == 0x00, "sub_0xbc76330: arg name at +0x00");

// Reversed from the disassembly of [0xbc76330, 0xbc7637a), Minecraft Windows 1.26.62.01
// (rdis dis output). Every block carries the instruction range it implements as
// // 0xA..0xB beside it; the single call is quoted verbatim below.
//
// Layout ([V] from this body): Bc76330State { const char* name @+0x00; uint32_t
// nameLen @+0x08; uint32_t reserved0x0c @+0x0c; uint32_t flag @+0x10 };
// Bc76330Arg { const char* name @+0x00; uint32_t maxLen @+0x08 }.
//
// Calls out of lifted code:
//   sub_ebce5e0 (class lift, docs/data/native_boundary.tsv line 504) is declared in
//   sub_bc76330.h and called as plain C++; it is lifted by its own unit.
//   No boundary calls, no indirect calls.
//
// Verbatim log of every call instruction in [0xbc76330, 0xbc7637a) (rdis dis output,
// copied verbatim, two spaces after the address):
#if 0
0xbc76369  call 0xEBCE5E0
#endif
// The only call target above is lift-set (sub_ebce5e0).

namespace native::bgfx {

int sub_bc76330(Bc76330State* state, std::uint32_t seed, const Bc76330Arg* arg) {
    // 0xbc76330..0xbc76342: prologue, init guard, shared epilogue
    //   0xbc76330  push rsi
    //   0xbc76331  push rdi
    //   0xbc76332  sub rsp,0x28
    //   0xbc76336  cmp dword ptr [rcx+0x10],0
    //   0xbc7633a  je short 0xBC76343
    //   0xbc7633c  add rsp,0x28
    //   0xbc76340  pop rdi
    //   0xbc76341  pop rsi
    //   0xbc76342  ret
    if (state->flag != 0) {
        return 0;   // 0xbc7633a not taken -> 0xbc7633c..0xbc76342 epilogue; the
                    // original does not write eax on this path (undefined)
    }

    // 0xbc76343..0xbc76378: init body
    //   0xbc76343  mov [rcx+0x10],edx
    //   0xbc76346  mov edx,[r8+8]
    //   0xbc7634a  mov rsi,[r8]
    //   0xbc7634d  lea rax,[0xF847A07]
    //   0xbc76354  mov [rcx],rax
    //   0xbc76357  mov dword ptr [rcx+8],0
    //   0xbc7635e  test rsi,rsi
    //   0xbc76361  je short 0xBC7633C
    //   0xbc76363  mov rdi,rcx
    //   0xbc76366  mov rcx,rsi
    //   0xbc76369  call 0xEBCE5E0
    //   0xbc7636e  test eax,eax
    //   0xbc76370  je short 0xBC7633C
    //   0xbc76372  mov [rdi+8],eax
    //   0xbc76375  mov [rdi],rsi
    //   0xbc76378  jmp short 0xBC7633C
    state->flag = seed;                                  // 0xbc76343  mov [rcx+0x10],edx
    const std::uint32_t maxLen = arg->maxLen;            // 0xbc76346  mov edx,[r8+8]
    const char* const s = arg->name;                     // 0xbc7634a  mov rsi,[r8]
    state->name = reinterpret_cast<const char*>(0x14F847A07ULL); // 0xbc7634d lea rax,[0xF847A07]
                                                            // 0xbc76354  mov [rcx],rax
    state->nameLen = 0;                                  // 0xbc76357  mov dword ptr [rcx+8],0
    if (s == 0) {
        return 0;   // 0xbc76361 je taken -> 0xbc7633c epilogue; eax undefined
    }
    const int r = static_cast<int>(sub_ebce5e0(s, maxLen));   // 0xbc76369  call 0xEBCE5E0
    if (r == 0) {
        return 0;   // 0xbc76370 je taken -> 0xbc7633c epilogue; eax == 0 here
    }
    state->nameLen = static_cast<std::uint32_t>(r);   // 0xbc76372  mov [rdi+8],eax
    state->name = s;                                  // 0xbc76375  mov [rdi],rsi
    return r;   // 0xbc76378 jmp -> 0xbc7633c epilogue; eax == r
}

LIFT_FN(sub_bc76330, "sub_bc76330", 0xbc76330, sub_bc76330, nullptr);

} // namespace native::bgfx
