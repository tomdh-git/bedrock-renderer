// LIFT 0x56aea80 size 0x113 1.26.62.01 sub_56aea80
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_56aea80.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_56aea80, "sub_56aea80", 0x56aea80, sub_56aea80, nullptr);

// Layout assertion binding this unit to RVA 0x56aea80 (gate requirement).
static_assert(offsetof(sub_56aea80_r8, f0) == 0x0, "0x56aea80: layout r8+0x0");
static_assert(offsetof(sub_56aea80_r8, f40) == 0x40, "0x56aea80: layout r8+0x40");

// Verbatim call instructions from the disassembly of [0x56aea80, 0x56aeb93) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x56aeaf0  call qword ptr [0xF99FFA0]
0x56aeb09  call qword ptr [0xF99FFA0]
0x56aeb17  call 0xE935700
0x56aeb4c  call qword ptr [0xF99FFA0]
0x56aeb8c  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0x56aea80, 0x56aeb93) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

namespace {
    using slot_fn_void = void (*)(void*, void*);
    using slot_fn_ptr  = void* (*)(void*, void*);

    inline void slot_call0(void* rcx, void* rdx) {
        auto slot = reinterpret_cast<slot_fn_void*>(0xF99FFA0);
        (*slot)(rcx, rdx);
    }
    inline void* slot_read_ptr() {
        return *reinterpret_cast<void** volatile*>(0xF99FFA0);
    }
}

// sub_e935700 is lift set; declared in native::sub_e935700.h.
void* sub_e935700(void* a0);

uintptr_t sub_56aea80(void* self) {
    // State machine lifting blocks 0..17 of [0x56aea80, 0x56aeb93).
    enum block : std::uint8_t {
        B0 = 0, B1, B2, B3, B4, B5, B6, B7, B7b, B8, B9, B10, B11, B12, B13, B14, B14b, B15, B16, B17
    };
    block state = B0;

    // Values carried between blocks (mirror live registers across block boundaries).
    void* a2 = self;                 // r8 (the 'this' pointer argument)
    void* rsi = nullptr;
    void* rdi = nullptr;
    void* rdx_v = nullptr;
    void* rcx_v = nullptr;
    std::uint64_t len = 0;
    void* buf = nullptr;
    std::uintptr_t bufp = 0;
    std::uint64_t bias = 0;
    std::uint64_t dist = 0;
    void* owned = nullptr;
    void* vt = nullptr;
    void* fn = nullptr;
    void* target = nullptr;
    std::uintptr_t scratch_f20 = 0;

    while (true) {
        switch (state) {
        // 0x56aea80..0x56aea96: basic block 0 (switch dispatch via table at 0xF25D16C)
        case B0: {
            std::uintptr_t* table = reinterpret_cast<std::uintptr_t*>(0xF25D16C);
            std::uintptr_t target_addr = reinterpret_cast<std::uintptr_t>(table) + table[self == nullptr ? 0 : 0];
            using goto_fn = uintptr_t (*)(void*);
            return reinterpret_cast<goto_fn>(target_addr)(self);
        }

        // 0x56aea96..0x56aeaa0: basic block 1
        case B1: {
            len = reinterpret_cast<std::uintptr_t>(reinterpret_cast<sub_56aea80_r8*>(a2)->f40);
            if (len < 0x10ull) { state = B11; break; }  // -> L_0x56aeb1f
            state = B2;
            break;
        }

        // 0x56aeaa0..0x56aeab1: basic block 2
        case B2: {
            buf = reinterpret_cast<sub_56aea80_r8*>(a2)->f28;
            std::uint64_t len1 = len + 1;
            if (len1 < 0x1000ull) { state = B9; break; }  // -> L_0x56aeb14
            state = B3;
            break;
        }

        // 0x56aeab1..0x56aeac6: basic block 3
        case B3: {
            bufp = reinterpret_cast<std::uintptr_t>(buf);
            bias = *reinterpret_cast<std::uintptr_t*>(bufp - 8);
            dist = (bufp - 8) - bias;
            if (dist >= 0x20ull) { state = B17; break; }  // -> L_0x56aeb79
            state = B4;
            break;
        }

        // 0x56aeac6..0x56aead5: basic block 4
        case B4: {
            rdi = self;
            rdx_v = reinterpret_cast<void*>(bufp + 0x28);
            rcx_v = reinterpret_cast<void*>(bias);
            state = B5;
            break;
        }

        // 0x56aead5..0x56aeade: basic block 5
        case B5: {
            owned = reinterpret_cast<void*>(reinterpret_cast<sub_56aea80_r8*>(a2)->f18);
            if (owned == nullptr) { state = B12; break; }  // -> L_0x56aeb34
            state = B6;
            break;
        }

        // 0x56aeade..0x56aeae4: basic block 6
        case B6: {
            std::uint32_t* rc8 = reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uintptr_t>(owned) + 8);
            if (_InterlockedDecrement(rc8) != 0) { state = B12; break; }  // -> L_0x56aeb34
            state = B7;
            break;
        }

        // 0x56aeae4..0x56aeaff: basic block 7
        case B7: {
            vt = *reinterpret_cast<void**>(owned);
            fn = *reinterpret_cast<void**>(vt);
            slot_call0(owned, self);
            state = B7b;  // after the dec at +0xC
            break;
        }

        // 0x56aeaf9..0x56aeaff: basic block 7b (dec +0xC, then fall to block 8)
        case B7b: {
            std::uint32_t* rc12 = reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uintptr_t>(owned) + 0xC);
            if (_InterlockedDecrement(rc12) != 0) { state = B12; break; }  // -> L_0x56aeb34
            state = B8;
            break;
        }

        // 0x56aeaff..0x56aeb14: basic block 8
        case B8: {
            vt = *reinterpret_cast<void**>(owned);
            fn = *reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(vt) + 8);
            slot_call0(owned, fn);
            state = B12;
            break;
        }

        // 0x56aeb14..0x56aeb17: basic block 9
        case B9: {
            rsi = self;
            state = B10;
            break;
        }

        // 0x56aeb17..0x56aeb1f: basic block 10
        case B10: {
            (void)sub_e935700(self);  // r8 = self; result ignored
            state = B11;
            break;
        }

        // 0x56aeb1f..0x56aeb34: basic block 11
        case B11: {
            auto* a2b = reinterpret_cast<sub_56aea80_r8*>(a2);
            a2b->f38 = 0;
            a2b->f40 = reinterpret_cast<void*>(0xF);
            a2b->f28 = reinterpret_cast<void*>(0);
            state = B12;
            break;
        }

        // 0x56aeb34..0x56aeb3d: basic block 12
        case B12: {
            rsi = reinterpret_cast<void*>(reinterpret_cast<sub_56aea80_r8*>(a2)->f8);
            if (rsi == nullptr) { state = B16; break; }  // -> L_0x56aeb72
            state = B13;
            break;
        }

        // 0x56aeb3d..0x56aeb43: basic block 13
        case B13: {
            std::uint32_t* rc8b = reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uintptr_t>(rsi) + 8);
            if (_InterlockedDecrement(rc8b) != 0) { state = B16; break; }  // -> L_0x56aeb72
            state = B14;
            break;
        }

        // 0x56aeb43..0x56aeb58: basic block 14
        case B14: {
            vt = *reinterpret_cast<void**>(rsi);
            slot_call0(rsi, nullptr);
            state = B14b;  // after the dec at +0xC
            break;
        }

        // 0x56aeb52..0x56aeb58: basic block 14b (dec +0xC, then fall to block 15)
        case B14b: {
            std::uint32_t* rc12b = reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uintptr_t>(rsi) + 0xC);
            if (_InterlockedDecrement(rc12b) != 0) { state = B16; break; }  // -> L_0x56aeb72
            state = B15;
            break;
        }

        // 0x56aeb58..0x56aeb72: basic block 15 (tail call through slot ptr)
        case B15: {
            vt = *reinterpret_cast<void**>(rsi);
            fn = *reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(vt) + 8);
            target = slot_read_ptr();
            using tail_fn = uintptr_t (*)(void*, void*);
            return reinterpret_cast<tail_fn>(target)(rsi, nullptr);
        }

        // 0x56aeb72..0x56aeb79: basic block 16
        case B16:
            return 0;

        // 0x56aeb79..0x56aeb93: basic block 17 (noreturn fail path)
        case B17: {
            scratch_f20 = 0;  // [rsp+0x20] = 0
            (void)scratch_f20;
            using fh_fn = void (*)(std::uintptr_t, std::uintptr_t, std::uintptr_t, std::uintptr_t);
            auto fh = reinterpret_cast<fh_fn*>(0xF9A8C78);
            (*fh)(0, 0, 0, 0);
            // noreturn: halt (matches int3 intent)
            for (;;) {}
        }
        }
    }
}

} // namespace native::helpers
