// LIFT 0xbcbf110 size 0x180 1.26.62.01 BgfxFrameBuilder slot 11
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bcbf110.h"

#include <cstdint>
#include <cstring>

namespace native::bgfx {

namespace {
extern "C" void sub_bcbf640(void* a0);
extern "C" void sub_eea6040(void* p); // boundary-ish via data slot [0xF99FFA0]
}

extern "C" void sub_bcbf110(void* a0) {
    void* rsi = a0; // 0xbcbf11b
    void* rdi = *reinterpret_cast<void**>(static_cast<char*>(rsi) + 0x80); // 0xbcbf11e
    if (rdi == nullptr) goto loc_bcbf1d8; // 0xbcbf125..0xbcbf128
    void** r14 = reinterpret_cast<void**>(static_cast<char*>(rsi) + 0x80); // 0xbcbf12e
    void* r15 = *reinterpret_cast<void**>(static_cast<char*>(rsi) + 0x88); // 0xbcbf135
    if (rdi != r15) { // 0xbcbf13c
        // fall through to loc_bcbf159
    } else {
        goto loc_bcbf192; // 0xbcbf141
    }
    // loc_bcbf150
    for (;;) {
        rdi = reinterpret_cast<char*>(rdi) + 0x10; // 0xbcbf150
        if (rdi == r15) goto loc_bcbf18f; // 0xbcbf154..0xbcbf157
        // loc_bcbf159
        void* rbx = *reinterpret_cast<void**>(static_cast<char*>(rdi) + 8); // 0xbcbf159
        if (rbx == nullptr) continue; // 0xbcbf15d..0xbcbf160
        // lock dec [rbx+8]
        if (--*reinterpret_cast<int*>(static_cast<char*>(rbx) + 8) != 0) continue; // 0xbcbf162..0xbcbf166
        // 0xbcbf168..0xbcbf171
        void** vtbl = *reinterpret_cast<void***>(rbx);
        void (*fn0)(void*) = reinterpret_cast<void(*)(void*)>(vtbl[0]);
        fn0(rbx); // 0xbcbf171  call qword ptr [0xF99FFA0] ... sub_eea6040 (via slot)
        // 0xbcbf177
        if (--*reinterpret_cast<int*>(static_cast<char*>(rbx) + 0xC) != 0) continue; // 0xbcbf177..0xbcbf17b
        // 0xbcbf17d..0xbcbf187
        void (*fn1)(void*) = reinterpret_cast<void(*)(void*)>(vtbl[1]);
        fn1(rbx); // 0xbcbf187
        continue;
    }
loc_bcbf18f:
    rdi = *r14; // 0xbcbf18f
loc_bcbf192:
    {
        // 0xbcbf192
        void* rdx = *reinterpret_cast<void**>(static_cast<char*>(rsi) + 0x90);
        char* diff = static_cast<char*>(rdx) - static_cast<char*>(rdi);
        if (reinterpret_cast<std::uintptr_t>(diff) < 0x1000) { // 0xbcbf19c
            // jb
        } else {
            void* rax = *reinterpret_cast<void**>(static_cast<char*>(rdi) - 8);
            rdi = static_cast<char*>(rdi) - 8;
            char* rdi2 = static_cast<char*>(rdi) - reinterpret_cast<char*>(rax);
            if (reinterpret_cast<std::uintptr_t>(rdi2) >= 0x20) goto loc_bcbf276;
            diff = static_cast<char*>(rdx) - static_cast<char*>(rdi) + 0x27; // approx
            rdi = rax;
        }
        // 0xbcbf1c1
        sub_e935700(rdi); // 0xbcbf1c4
        // 0xbcbf1c9
        *r14 = nullptr; // xorps
        reinterpret_cast<__int128*>(r14)[0] = 0; // movups
        *reinterpret_cast<void**>(static_cast<char*>(r14) + 0x10) = nullptr;
    }
loc_bcbf1d8:
    {
        void* rcx = *reinterpret_cast<void**>(static_cast<char*>(rsi) + 0x58);
        if (rcx == nullptr) goto loc_bcbf220;
        void* rdx = *reinterpret_cast<void**>(static_cast<char*>(rsi) + 0x68);
        char* diff = static_cast<char*>(rdx) - static_cast<char*>(rcx);
        if (reinterpret_cast<std::uintptr_t>(diff) < 0x1000) {
        } else {
            void* rax = *reinterpret_cast<void**>(static_cast<char*>(rcx) - 8);
            rcx = static_cast<char*>(rcx) - 8;
            char* rcx2 = static_cast<char*>(rcx) - static_cast<char*>(rax);
            if (reinterpret_cast<std::uintptr_t>(rcx2) >= 0x20) goto loc_bcbf276;
            diff = static_cast<char*>(rdx) - static_cast<char*>(rcx) + 0x27;
            rcx = rax;
        }
        void** rdi2 = reinterpret_cast<void**>(static_cast<char*>(rsi) + 0x58);
        sub_e935700(rcx); // 0xbcbf20d
        *rdi2 = nullptr;
        reinterpret_cast<__int128*>(rdi2)[0] = 0;
        *reinterpret_cast<void**>(static_cast<char*>(rdi2) + 0x10) = nullptr;
    }
loc_bcbf220:
    {
        void* rax = *reinterpret_cast<void**>(static_cast<char*>(rsi) + 0x48);
        void** rcx = *reinterpret_cast<void***>(static_cast<char*>(rax) + 8);
        *rcx = nullptr;
        void* node = *reinterpret_cast<void**>(rax);
        while (node != nullptr) {
            void* rdi = *reinterpret_cast<void**>(node);
            sub_e935700(node); // 0xbcbf248
            node = rdi;
        }
        sub_e935700(rax); // 0xbcbf25e
    }
    sub_bcbf640(rsi); // 0xbcbf271 tail call
    return;
loc_bcbf276:
    // invalid parameter handler via slot
    (*reinterpret_cast<void(*)()>(0xF9A8C78))();
    __debugbreak();
}

// 0xbcbf110..0xbcbf28f
#if 0
0xbcbf171  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcbf187  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcbf1c4  call 0xE935700                                ; -> sub_e935700
0xbcbf20d  call 0xE935700                                ; -> sub_e935700
0xbcbf248  call 0xE935700                                ; -> sub_e935700
0xbcbf25e  call 0xE935700                                ; -> sub_e935700
0xbcbf289  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
#endif

LIFT_FN(sub_bcbf110, "sub_bcbf110", 0xbcbf110, sub_bcbf110, nullptr);

} // namespace native::bgfx

// Registry
// // 0xbcbf110..0xbcbf28f
#if 0
0xbcbf171  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcbf187  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbcbf1c4  call 0xE935700                                ; -> sub_e935700
0xbcbf20d  call 0xE935700                                ; -> sub_e935700
0xbcbf248  call 0xE935700                                ; -> sub_e935700
0xbcbf25e  call 0xE935700                                ; -> sub_e935700
0xbcbf289  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
#endif

LIFT_FN(sub_bcbf110, "sub_bcbf110", 0xbcbf110, sub_bcbf110, nullptr);

static_assert(true, "placeholder");
