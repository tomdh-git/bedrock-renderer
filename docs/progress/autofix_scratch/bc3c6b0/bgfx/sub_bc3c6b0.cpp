// LIFT 0xbc3c6b0 size 0xcb 1.26.62.01 BgfxFrameBuilder slot 0

#include "client/features/render/native/bgfx/sub_bc3c6b0.h"

#include <cstdint>
#include "client/features/render/native/Lift.h"
// Forward declarations (autofix)
struct sub_392960;
struct sub_bc3c6b0;


namespace native::bgfx {

namespace {

// External call: sub_e935700 is a thunk (`jmp sub_392960` @0xe935700). Neither

// sub_e935700 nor sub_392960 appears in docs/data/native_functions.tsv or

// docs/data/native_boundary.tsv. Declared with its native symbol only.

// Argument types mirror the registers the original passes (all 64-bit values).

extern "C" void sub_e935700(uint64_t a0, uint64_t a1, void* a2, void* a3);

// Error path: calls the function pointer at data address 0xF9A8C78 with

// zeroed arguments, then executes int3. Target is an absolute data address,

// not in any lift or boundary table.

extern "C" void bc3c6b0_error_indirect(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);

} // namespace


void sub_bc3c6b0(unsigned __int64 mode, unsigned __int64 /*unused*/,
                 BgfxFrameBuilderSlot0* fb, void* a3) {
    // 0xbc3c6b0  push rsi

    // 0xbc3c6b1  push rdi

    // 0xbc3c6b2  sub rsp,0x28

    // 0xbc3c6b6  cmp rcx,1

    // 0xbc3c6ba  jne 0xBC3C75A

    if (mode != kBc3c6b0ModeRequired) {
        return;   // 0xbc3c75a  add rsp,0x28   0xbc3c75e  pop rdi   0xbc3c75f  pop rsi   0xbc3c760  ret

    }

    // 0xbc3c6c0  mov rsi,r8

    BgfxFrameBuilderSlot0* self = fb;

    // 0xbc3c6c3  mov rcx,[r8+0x60]

    // 0xbc3c6c7  test rcx,rcx

    // 0xbc3c6ca  je short 0xBC3C70B

    if (self->field_0x60 != nullptr) {
        // 0xbc3c6cc  mov rdx,[rsi+0x70]

        // 0xbc3c6d0  sub rdx,rcx

        // 0xbc3c6d3  cmp rdx,0x1000

        uint64_t slot_size =
            reinterpret_cast<uintptr_t>(self->field_0x70) -
            reinterpret_cast<uintptr_t>(self->field_0x60);
        uint64_t arg0, arg1;
        if (slot_size >= kBc3c6b0SlotSizeLarge) {
            // 0xbc3c6dc  mov rax,[rcx-8]

            // 0xbc3c6e0  add rcx,0xFFFFFFFFFFFFFFF8

            // 0xbc3c6e4  sub rcx,rax

            // 0xbc3c6e7  cmp rcx,0x20

            // 0xbc3c6eb  jae short 0xBC3C761

            uint64_t chunk = *reinterpret_cast<const uint64_t*>(
                reinterpret_cast<const uint8_t*>(self->field_0x60) - 8);
            uint64_t guard = (reinterpret_cast<uintptr_t>(self->field_0x60) - 8) - chunk;
            if (guard >= kBc3c6b0GuardGap) {
                goto bc3c6b0_error;
            }
            arg1 = slot_size + kBc3c6b0Size1Bias;
            arg0 = chunk;
        } else {
            arg0 = reinterpret_cast<uint64_t>(self->field_0x60);
            arg1 = slot_size;
        }
        // 0xbc3c6f4  lea rdi,[rsi+0x60]

        // 0xbc3c6f8  call 0xE935700

        sub_e935700(arg0, arg1, self, a3);
        // 0xbc3c6fd  xorps xmm0,xmm0

        // 0xbc3c700  movups [rdi],xmm0   ; zero 16 bytes at &field_0x60

        // 0xbc3c703  mov qword ptr [rdi+0x10],0

        self->field_0x60 = nullptr;
        self->field_0x70 = nullptr;
    }

    // 0xbc3c70b  mov rax,[rsi+0x50]

    // 0xbc3c70f  cmp rax,0x10

    // 0xbc3c713  jb short 0xBC3C746

    if (self->field_0x50 >= kBc3c6b0Slot2Small) {
        // 0xbc3c715  mov rcx,[rsi+0x38]

        void* slot_ptr = self->field_0x38;
        // 0xbc3c719  lea rdx,[rax+1]

        uint64_t size_plus1 = self->field_0x50 + 1;
        uint64_t arg0, arg1, arg2;
        if (size_plus1 >= kBc3c6b0SlotSizeLarge) {
            // 0xbc3c726  mov r8,[rcx-8]

            // 0xbc3c72a  add rcx,0xFFFFFFFFFFFFFFF8

            // 0xbc3c72e  sub rcx,r8

            // 0xbc3c731  cmp rcx,0x20

            // 0xbc3c735  jae short 0xBC3C761

            uint64_t chunk = *reinterpret_cast<const uint64_t*>(
                reinterpret_cast<const uint8_t*>(slot_ptr) - 8);
            uint64_t guard = (reinterpret_cast<uintptr_t>(slot_ptr) - 8) - chunk;
            if (guard >= kBc3c6b0GuardGap) {
                goto bc3c6b0_error;
            }
            arg1 = self->field_0x50 + kBc3c6b0Size2Bias;
            arg0 = chunk;
            arg2 = chunk;
        } else {
            arg0 = reinterpret_cast<uint64_t>(slot_ptr);
            arg1 = size_plus1;
            arg2 = reinterpret_cast<uint64_t>(self);
        }
        // 0xbc3c741  call 0xE935700

        sub_e935700(arg0, arg1, reinterpret_cast<void*>(arg2), a3);
    }

    // 0xbc3c746  mov qword ptr [rsi+0x48],0

    self->field_0x48 = 0;
    // 0xbc3c74e  mov qword ptr [rsi+0x50],0xF

    self->field_0x50 = kBc3c6b0ResetSize;
    // 0xbc3c756  mov byte ptr [rsi+0x38],0

    *reinterpret_cast<uint8_t*>(&self->field_0x38) = 0;
    return;

bc3c6b0_error:
    // 0xbc3c761  mov qword ptr [rsp+0x20],0

    // 0xbc3c76a  xor ecx,ecx

    // 0xbc3c76c  xor edx,edx

    // 0xbc3c76e  xor r8d,r8d

    // 0xbc3c771  xor r9d,r9d

    // 0xbc3c774  call qword ptr [0xF9A8C78]

    // 0xbc3c77a  int3

    uintptr_t* fn_ptr = reinterpret_cast<uintptr_t*>(
        RewriteRegistry::imageBase() + 0xF9A8C78);
    using IndirectFn = void (*)(uint64_t, uint64_t, uint64_t, uint64_t);
    IndirectFn indirect = reinterpret_cast<IndirectFn>(*fn_ptr);
    indirect(0, 0, 0, 0);
    __assume(false);   // original executes int3 here (noreturn)

}

} // namespace native::bgfx


LIFT_FN(sub_bc3c6b0, "native::sub_bc3c6b0", 0xbc3c6b0, sub_bc3c6b0, nullptr);
