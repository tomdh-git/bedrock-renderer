// LIFT 0x5e2270 size 0x118 1.26.62.01 sub_5e2270
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_5e2270.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_5e2270, "sub_5e2270", 0x5e2270, sub_5e2270, nullptr);

// Verbatim call instructions from the disassembly of [0x5e2270, 0x5e2388) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x5e22c3  call 0xE935700
0x5e2314  call 0xE935700
0x5e233d  call qword ptr [0xF99FFA0]
0x5e2381  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0x5e2270, 0x5e2388) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

void sub_5e2270(void* a0) {
    auto* const self = reinterpret_cast<sub_5e2270_rcx*>(a0);   // 0x5e2275 mov rsi,rcx
    std::uint64_t capacity = 0;
    void* buffer = nullptr;
    void* allocBase = nullptr;
    std::uintptr_t bias = 0;
    void* object = nullptr;
    void* queried = nullptr;

    // 0x5e2270..0x5e228c: basic block 0
    // 0x5e2270  push rsi
    // 0x5e2271  sub rsp,0x30
    // 0x5e2275  mov rsi,rcx
    // 0x5e2278  lea rax,[0xF086408]
    // 0x5e227f  mov [rcx],rax
    // 0x5e2282  mov rax,[rcx+0x58]
    // 0x5e2286  cmp rax,8
    // 0x5e228a  jb short 0x5E22C8
    self->vfptr = reinterpret_cast<void*>(
        RewriteRegistry::imageBase() + sub_5e2270Layout::kVtableRva);   // 0x5e2278 lea rax,[0xF086408] ; 0x5e227f mov [rcx],rax
    capacity = self->capacity40;                                        // 0x5e2282 mov rax,[rcx+0x58]
    if (capacity >= 8) {                                                // 0x5e2286 cmp rax,8 ; 0x5e228a jb short 0x5E22C8
        // 0x5e228c..0x5e22a1: basic block 1
        // 0x5e228c  mov rcx,[rsi+0x40]
        // 0x5e2290  lea rdx,[rax*2+2]
        // 0x5e2298  cmp rdx,0x1000
        // 0x5e229f  jb short 0x5E22C3
        buffer = self->buffer40;                                        // 0x5e228c mov rcx,[rsi+0x40]
        if (capacity * 2 + 2 < 0x1000) {                                // 0x5e2290 lea rdx,[rax*2+2] ; 0x5e2298 cmp rdx,0x1000 ; 0x5e229f jb short 0x5E22C3
            // 0x5e22c3..0x5e22c8: basic block 4
            // 0x5e22c3  call 0xE935700
            native::sub_e935700(buffer);                                // 0x5e22c3 call 0xE935700 (RDX = capacity*2+2 is dead inside the callee)
        } else {
            // 0x5e22a1..0x5e22b6: basic block 2
            // 0x5e22a1  mov r8,[rcx-8]
            // 0x5e22a5  add rcx,0xFFFFFFFFFFFFFFF8
            // 0x5e22a9  sub rcx,r8
            // 0x5e22ac  cmp rcx,0x20
            // 0x5e22b0  jae 0x5E236E
            allocBase = *reinterpret_cast<void**>(static_cast<char*>(buffer) - 8);  // 0x5e22a1 mov r8,[rcx-8]
            bias = reinterpret_cast<std::uintptr_t>(buffer) - 8 -
                   reinterpret_cast<std::uintptr_t>(allocBase);                     // 0x5e22a5 add rcx,-8 ; 0x5e22a9 sub rcx,r8
            if (bias >= 0x20) {                                         // 0x5e22ac cmp rcx,0x20 ; 0x5e22b0 jae 0x5E236E
                goto L_0x5e236e;
            }
            // 0x5e22b6..0x5e22c3: basic block 3
            // 0x5e22b6  add rax,rax
            // 0x5e22b9  add rax,0x29
            // 0x5e22bd  mov rdx,rax
            // 0x5e22c0  mov rcx,r8
            // 0x5e22c3  call 0xE935700
            native::sub_e935700(allocBase);                             // 0x5e22c3 call 0xE935700 (RDX = capacity*2+0x29 is dead inside the callee)
        }
    }

    // 0x5e22c8..0x5e22e8: basic block 5
    // 0x5e22c8  mov qword ptr [rsi+0x50],0
    // 0x5e22d0  mov qword ptr [rsi+0x58],7
    // 0x5e22d8  mov word ptr [rsi+0x40],0
    // 0x5e22de  mov rax,[rsi+0x38]
    // 0x5e22e2  cmp rax,0x10
    // 0x5e22e6  jb short 0x5E2319
    self->size40 = 0;                                                   // 0x5e22c8 mov qword ptr [rsi+0x50],0
    self->capacity40 = 7;                                               // 0x5e22d0 mov qword ptr [rsi+0x58],7
    *reinterpret_cast<std::uint16_t*>(reinterpret_cast<char*>(self) + 0x40) = 0;  // 0x5e22d8 mov word ptr [rsi+0x40],0
    capacity = self->capacity20;                                        // 0x5e22de mov rax,[rsi+0x38]
    if (capacity >= 0x10) {                                             // 0x5e22e2 cmp rax,0x10 ; 0x5e22e6 jb short 0x5E2319
        // 0x5e22e8..0x5e22f9: basic block 6
        // 0x5e22e8  mov rcx,[rsi+0x20]
        // 0x5e22ec  lea rdx,[rax+1]
        // 0x5e22f0  cmp rdx,0x1000
        // 0x5e22f7  jb short 0x5E2314
        buffer = self->buffer20;                                        // 0x5e22e8 mov rcx,[rsi+0x20]
        if (capacity + 1 < 0x1000) {                                    // 0x5e22ec lea rdx,[rax+1] ; 0x5e22f0 cmp rdx,0x1000 ; 0x5e22f7 jb short 0x5E2314
            // 0x5e2314..0x5e2319: basic block 9
            // 0x5e2314  call 0xE935700
            native::sub_e935700(buffer);                                // 0x5e2314 call 0xE935700 (RDX = capacity+1 is dead inside the callee)
        } else {
            // 0x5e22f9..0x5e230a: basic block 7
            // 0x5e22f9  mov r8,[rcx-8]
            // 0x5e22fd  add rcx,0xFFFFFFFFFFFFFFF8
            // 0x5e2301  sub rcx,r8
            // 0x5e2304  cmp rcx,0x20
            // 0x5e2308  jae short 0x5E236E
            allocBase = *reinterpret_cast<void**>(static_cast<char*>(buffer) - 8);  // 0x5e22f9 mov r8,[rcx-8]
            bias = reinterpret_cast<std::uintptr_t>(buffer) - 8 -
                   reinterpret_cast<std::uintptr_t>(allocBase);                     // 0x5e22fd add rcx,-8 ; 0x5e2301 sub rcx,r8
            if (bias >= 0x20) {                                         // 0x5e2304 cmp rcx,0x20 ; 0x5e2308 jae short 0x5E236E
                goto L_0x5e236e;
            }
            // 0x5e230a..0x5e2314: basic block 8
            // 0x5e230a  add rax,0x28
            // 0x5e230e  mov rdx,rax
            // 0x5e2311  mov rcx,r8
            // 0x5e2314  call 0xE935700
            native::sub_e935700(allocBase);                             // 0x5e2314 call 0xE935700 (RDX = capacity+0x28 is dead inside the callee)
        }
    }

    // 0x5e2319..0x5e2336: basic block 10
    // 0x5e2319  mov qword ptr [rsi+0x30],0
    // 0x5e2321  mov qword ptr [rsi+0x38],0xF
    // 0x5e2329  mov byte ptr [rsi+0x20],0
    // 0x5e232d  mov rcx,[rsi+0x18]
    // 0x5e2331  test rcx,rcx
    // 0x5e2334  je short 0x5E2368
    self->size20 = 0;                                                   // 0x5e2319 mov qword ptr [rsi+0x30],0
    self->capacity20 = 0xF;                                             // 0x5e2321 mov qword ptr [rsi+0x38],0xF
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<char*>(self) + 0x20) = 0;  // 0x5e2329 mov byte ptr [rsi+0x20],0
    object = self->object;                                              // 0x5e232d mov rcx,[rsi+0x18]
    if (object != nullptr) {                                            // 0x5e2331 test rcx,rcx ; 0x5e2334 je short 0x5E2368
        // 0x5e2336..0x5e2348: basic block 11
        // 0x5e2336  mov rax,[rcx]
        // 0x5e2339  mov rax,[rax+0x10]
        // 0x5e233d  call qword ptr [0xF99FFA0]
        // 0x5e2343  test rax,rax
        // 0x5e2346  je short 0x5E2368
        auto* const vtbl = *reinterpret_cast<sub_5e2270_rax**>(object);  // 0x5e2336 mov rax,[rcx] ; 0x5e2339 mov rax,[rax+0x10]
        queried = native::boundary::g_eea6040_thunk(object, vtbl->slot2); // 0x5e233d call qword ptr [0xF99FFA0]
        if (queried != nullptr) {                                       // 0x5e2343 test rax,rax ; 0x5e2346 je short 0x5E2368
            // 0x5e2348..0x5e2368: basic block 12
            // 0x5e2348  mov rcx,[rax]
            // 0x5e234b  mov r8,[rcx]
            // 0x5e234e  mov r9,[0xF99FFA0]
            // 0x5e2355  mov rcx,rax
            // 0x5e2358  mov edx,1
            // 0x5e235d  mov rax,r8
            // 0x5e2360  add rsp,0x30
            // 0x5e2364  pop rsi
            // 0x5e2365  jmp r9
            auto* const queriedVtbl = *reinterpret_cast<sub_5e2270_rax**>(queried);  // 0x5e2348 mov rcx,[rax] ; 0x5e234b mov r8,[rcx]
            using release_fn = void (*)(void*, int);
            reinterpret_cast<release_fn>(queriedVtbl->slot0)(queried, 1);        // 0x5e2355..0x5e2365: vtable[0](queried, 1), tail-jumped via the 0xF99FFA0 thunk
            return;                                                     // 0x5e2360 add rsp,0x30 ; 0x5e2364 pop rsi (tail call does not return here)
        }
    }

    // 0x5e2368..0x5e236e: basic block 13
    // 0x5e2368  add rsp,0x30
    // 0x5e236c  pop rsi
    // 0x5e236d  ret
    return;

L_0x5e236e:
    // 0x5e236e..0x5e2388: basic block 14
    // 0x5e236e  mov qword ptr [rsp+0x20],0
    // 0x5e2377  xor ecx,ecx
    // 0x5e2379  xor edx,edx
    // 0x5e237b  xor r8d,r8d
    // 0x5e237e  xor r9d,r9d
    // 0x5e2381  call qword ptr [0xF9A8C78]
    // 0x5e2387  int3
    using failfast_fn = void (__cdecl*)(void*, void*, void*, void*, void*);
    failfast_fn const failfast = reinterpret_cast<failfast_fn>(
        *reinterpret_cast<std::uintptr_t*>(
            RewriteRegistry::imageBase() + sub_5e2270Layout::kFailfastSlotRva));
    failfast(nullptr, nullptr, nullptr, nullptr, nullptr);   // 0x5e236e..0x5e2381: arg4 = 0 in [rsp+0x20], RCX/RDX/R8/R9 = 0
    __assume(0);                                            // 0x5e2387 int3: trap only if the failfast callee returns
}

} // namespace native::helpers
