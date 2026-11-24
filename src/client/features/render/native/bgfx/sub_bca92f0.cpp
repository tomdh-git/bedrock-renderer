// LIFT 0xbca92f0 size 0x13b 1.26.62.01 sub_bca92f0
#include "client/features/render/native/bgfx/sub_bca92f0.h"
#include "client/features/render/native/Lift.h"

#include <atomic>
#include <cstdint>
#include <intrin.h>

namespace native::bgfx {

namespace {

// Calls out of lifted code go through native::Boundary wrappers (spec section 6):
//   0xbca9378 / 0xbca93a1 / 0xbca93b7  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
//                                      vendor thunk via data slot 0xF99FFA0 (boundary, class vendor)
//   0xbca9424                         call qword ptr [0xF9A8C78]   ; [data_f9a8c78] import-slot fail handler
native::Boundary<void, void*, unsigned char> sub_eea6040("sub_eea6040");

} // namespace

static native::Footprint sub_bca92f0Footprint(Builder* self) {
    return {{reinterpret_cast<void*>(self), 0xB8ull}}; // writes cover [self, self+0xB8) [V]
}

extern "C" void sub_bca92f0(Builder* self) {
    Builder* const this_ = self;                      // 0xbca92f6  mov rsi,rcx
    unsigned char flag = 0u;                          // rdx scratch: setne dl at 0xbca936e

    // 0xbca92f0..0xbca9306
    //   0xbca92f0  push rsi
    //   0xbca92f1  push rdi
    //   0xbca92f2  sub rsp,0x28
    //   0xbca92f6  mov rsi,rcx
    //   0xbca92f9  mov rax,[rcx+0xB0]
    //   0xbca9300  cmp rax,0x10
    //   0xbca9304  jb short 0xBCA933E
    if (this_->cap_b < 0x10ull) {                     // 0xbca9300  cmp rax,0x10 / 0xbca9304  jb short 0xBCA933E
        goto done_a;                                  // cap_b < 0x10: buffer B is small, nothing to release
    }

    // 0xbca9306..0xbca9339  (buffer B release)
    //   0xbca9306  mov rcx,[rsi+0x98]
    //   0xbca930d  lea rdx,[rax+1]
    //   0xbca9311  cmp rdx,0x1000
    //   0xbca9318  jb short 0xBCA9339
    void* buf_b = this_->buf_b;                       // 0xbca9306  mov rcx,[rsi+0x98]
    if (this_->cap_b + 1ull < 0x1000ull) {            // 0xbca930d  lea rdx,[rax+1] / 0xbca9311  cmp rdx,0x1000 / 0xbca9318  jb short 0xBCA9339
        // 0xbca9339  call 0xE935700   ; -> sub_e935700  (rcx = buf_b, rdx = cap_b + 1 [dead inside sub_e935700])
        sub_e935700(buf_b);                           // 0xbca9339  call 0xE935700
    } else {
        // 0xbca931a  mov r8,[rcx-8]
        // 0xbca931e  add rcx,0xFFFFFFFFFFFFFFF8
        // 0xbca9322  sub rcx,r8
        // 0xbca9325  cmp rcx,0x20
        // 0xbca9329  jae 0xBCA9411
        const std::uintptr_t r8 =
            *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<char*>(buf_b) - 8); // 0xbca931a  mov r8,[rcx-8]
        if (static_cast<std::uintptr_t>(
                reinterpret_cast<char*>(buf_b) - 8 - reinterpret_cast<char*>(r8)) >= 0x20ull) { // 0xbca931e..0xbca9329  block-base guard
            goto fail;                                // 0xbca9329  jae 0xBCA9411
        }
        // 0xbca932f  add rax,0x28   (dead size, rdx is dead inside sub_e935700)
        // 0xbca9333  mov rdx,rax
        // 0xbca9336  mov rcx,r8
        // 0xbca9339  call 0xE935700   ; -> sub_e935700  (rcx = [buf_b-8], rdx = cap_b + 0x28 [dead inside sub_e935700])
        sub_e935700(reinterpret_cast<void*>(r8));     // 0xbca9339  call 0xE935700
    }

    // 0xbca933e..0xbca935b  (reset buffer B fields)
    //   0xbca933e  mov qword ptr [rsi+0xA8],0
    //   0xbca9349  mov qword ptr [rsi+0xB0],0xF
    //   0xbca9354  mov byte ptr [rsi+0x98],0
    this_->size_b = 0ull;                             // 0xbca933e  mov qword ptr [rsi+0xA8],0
    this_->cap_b = 0xFull;                            // 0xbca9349  mov qword ptr [rsi+0xB0],0xF
    *reinterpret_cast<std::uint8_t*>(&this_->buf_b) = 0u; // 0xbca9354  mov byte ptr [rsi+0x98],0

    // 0xbca935b..0xbca937e  (obj_a release, if present and not the inline object)
    //   0xbca935b  mov rcx,[rsi+0x88]
    //   0xbca9362  test rcx,rcx
    //   0xbca9365  je short 0xBCA9389
    //   0xbca9367  lea rax,[rsi+0x50]
    //   0xbca936b  cmp rcx,rax
    //   0xbca936e  setne dl
    //   0xbca9371  mov rax,[rcx]                      (dead read: obj_a->vtable)
    //   0xbca9374  mov rax,[rax+0x20]                 (dead read: vtable[8])
    //   0xbca9378  call qword ptr [0xF99FFA0]         ; [data_f99ffa0] = sub_eea6040  (rcx = obj_a, rdx = flag)
    //   0xbca937e  mov qword ptr [rsi+0x88],0
    RefCounted* const obj_a = this_->obj_a;           // 0xbca935b  mov rcx,[rsi+0x88]
    if (obj_a != nullptr) {                           // 0xbca9362  test rcx,rcx / 0xbca9365  je short 0xBCA9389
        flag = static_cast<unsigned char>(
            obj_a != reinterpret_cast<RefCounted*>(&this_->inline_obj)); // 0xbca9367..0xbca936e  obj_a != &this+0x50 -> dl

        // dead reads of the vtable (results unused; call target is the IAT slot, not the vtable)
        const std::uintptr_t vt =
            *reinterpret_cast<std::uintptr_t volatile*>(obj_a);        // 0xbca9371  mov rax,[rcx]
        const std::uintptr_t vt_slot4 =
            *reinterpret_cast<std::uintptr_t volatile*>(vt + 0x20ull); // 0xbca9374  mov rax,[rax+0x20]
        (void)vt;
        (void)vt_slot4;

        // 0xbca9378  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040  (rcx = obj_a, rdx = flag)
        sub_eea6040(obj_a, flag);                     // 0xbca9378  call qword ptr [0xF99FFA0]

        // 0xbca937e  mov qword ptr [rsi+0x88],0
        this_->obj_a = nullptr;                       // 0xbca937e  mov qword ptr [rsi+0x88],0
    }

    // 0xbca9389..0xbca93bd  (shared release)
    //   0xbca9389  mov rdi,[rsi+0x28]
    //   0xbca938d  test rdi,rdi
    //   0xbca9390  je short 0xBCA93BD
    RefCounted* const shared = this_->shared;         // 0xbca9389  mov rdi,[rsi+0x28]
    if (shared != nullptr) {                          // 0xbca938d  test rdi,rdi / 0xbca9390  je short 0xBCA93BD
        // 0xbca9392  lock dec dword ptr [rdi+8]
        // 0xbca9396  jne short 0xBCA93BD
        std::atomic<std::uint32_t>* const strong =
            reinterpret_cast<std::atomic<std::uint32_t>*>(&shared->strong);
        if (strong->fetch_sub(1u, std::memory_order_seq_cst) == 1u) { // 0xbca9392  lock dec dword ptr [rdi+8] / 0xbca9396  jne short 0xBCA93BD
            // 0xbca9398  mov rax,[rdi]              (dead read: shared->vtable)
            // 0xbca939b  mov rax,[rax]              (dead read: vtable[0])
            const std::uintptr_t vt =
                *reinterpret_cast<std::uintptr_t volatile*>(shared);  // 0xbca9398  mov rax,[rdi]
            const std::uintptr_t dtor_slot =
                *reinterpret_cast<std::uintptr_t volatile*>(vt);      // 0xbca939b  mov rax,[rax]
            (void)vt;
            (void)dtor_slot;

            // 0xbca93a1  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040  (rcx = shared, rdx = flag)
            sub_eea6040(shared, flag);                // 0xbca93a1  call qword ptr [0xF99FFA0]

            // 0xbca93a7  lock dec dword ptr [rdi+0xC]
            // 0xbca93ab  jne short 0xBCA93BD
            std::atomic<std::uint32_t>* const weak =
                reinterpret_cast<std::atomic<std::uint32_t>*>(&shared->weak);
            if (weak->fetch_sub(1u, std::memory_order_seq_cst) == 1u) { // 0xbca93a7  lock dec dword ptr [rdi+0xC] / 0xbca93ab  jne short 0xBCA93BD
                // 0xbca93ad  mov rax,[rdi]          (dead read: shared->vtable)
                // 0xbca93b0  mov rax,[rax+8]        (dead read: vtable[1])
                const std::uintptr_t vt2 =
                    *reinterpret_cast<std::uintptr_t volatile*>(shared);  // 0xbca93ad  mov rax,[rdi]
                const std::uintptr_t dealloc_slot =
                    *reinterpret_cast<std::uintptr_t volatile*>(vt2 + 8ull); // 0xbca93b0  mov rax,[rax+8]
                (void)vt2;
                (void)dealloc_slot;

                // 0xbca93b7  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040  (rcx = shared, rdx = flag)
                sub_eea6040(shared, flag);            // 0xbca93b7  call qword ptr [0xF99FFA0]
            }
        }
    }

    // 0xbca93bd..0xbca93f2  (buffer A release)
    //   0xbca93bd  mov rax,[rsi+0x18]
    //   0xbca93c1  cmp rax,0x10
    //   0xbca93c5  jb short 0xBCA93F7
    //   0xbca93c7  mov rcx,[rsi]
    //   0xbca93ca  lea rdx,[rax+1]
    //   0xbca93ce  cmp rdx,0x1000
    //   0xbca93d5  jb short 0xBCA93F2
    //   0xbca93d7  mov r8,[rcx-8]
    //   0xbca93db  add rcx,0xFFFFFFFFFFFFFFF8
    //   0xbca93df  sub rcx,r8
    //   0xbca93e2  cmp rcx,0x20
    //   0xbca93e6  jae short 0xBCA9411
    //   0xbca93e8  add rax,0x28   (dead size)
    //   0xbca93ec  mov rdx,rax
    //   0xbca93ef  mov rcx,r8
    if (this_->cap_a < 0x10ull) {                     // 0xbca93c1  cmp rax,0x10 / 0xbca93c5  jb short 0xBCA93F7
        goto done_a;
    }
    void* buf_a = this_->buf_a;                       // 0xbca93c7  mov rcx,[rsi]
    if (this_->cap_a + 1ull < 0x1000ull) {            // 0xbca93ca  lea rdx,[rax+1] / 0xbca93ce  cmp rdx,0x1000 / 0xbca93d5  jb short 0xBCA93F2
        // 0xbca93f2  call 0xE935700   ; -> sub_e935700  (rcx = buf_a, rdx = cap_a + 1 [dead inside sub_e935700])
        sub_e935700(buf_a);                           // 0xbca93f2  call 0xE935700
    } else {
        const std::uintptr_t r8 =
            *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<char*>(buf_a) - 8); // 0xbca93d7  mov r8,[rcx-8]
        if (static_cast<std::uintptr_t>(
                reinterpret_cast<char*>(buf_a) - 8 - reinterpret_cast<char*>(r8)) >= 0x20ull) { // 0xbca93db..0xbca93e6  block-base guard
            goto fail;                                // 0xbca93e6  jae short 0xBCA9411
        }
        // 0xbca93f2  call 0xE935700   ; -> sub_e935700  (rcx = [buf_a-8], rdx = cap_a + 0x28 [dead inside sub_e935700])
        sub_e935700(reinterpret_cast<void*>(r8));     // 0xbca93f2  call 0xE935700
    }

    // 0xbca93f7..0xbca9410  (reset buffer A fields + epilogue)
    //   0xbca93f7  mov qword ptr [rsi+0x10],0
    //   0xbca93ff  mov qword ptr [rsi+0x18],0xF
    //   0xbca9407  mov byte ptr [rsi],0
    //   0xbca940a  add rsp,0x28
    //   0xbca940e  pop rdi
    //   0xbca940f  pop rsi
    //   0xbca9410  ret
done_a:
    this_->size_a = 0ull;                             // 0xbca93f7  mov qword ptr [rsi+0x10],0
    this_->cap_a = 0xFull;                            // 0xbca93ff  mov qword ptr [rsi+0x18],0xF
    *reinterpret_cast<std::uint8_t*>(&this_->buf_a) = 0u; // 0xbca9407  mov byte ptr [rsi],0
    return;                                           // 0xbca940a..0xbca9410  epilogue + ret

    // 0xbca9411..0xbca942b   (heap-guard failure, noreturn)
    //   0xbca9411  mov qword ptr [rsp+0x20],0   (own stack slot; not observable)
    //   0xbca941a  xor ecx,ecx
    //   0xbca941c  xor edx,edx
    //   0xbca941e  xor r8d,r8d
    //   0xbca9421  xor r9d,r9d
    //   0xbca9424  call qword ptr [0xF9A8C78]   ; [data_f9a8c78]
    //   0xbca942a  int3
fail:
    {
        using FailFn = void (*)(std::uintptr_t, std::uintptr_t, std::uintptr_t, std::uintptr_t);
        reinterpret_cast<FailFn>(
            *reinterpret_cast<void**>(kFailSlotAddr))(0, 0, 0, 0); // 0xbca9424  call qword ptr [0xF9A8C78]
    }
    __debugbreak();                                   // 0xbca942a  int3
    __assume(false);                                  // noreturn: the original traps on the int3
}

static_assert(offsetof(Builder, cap_b) == 0xB0, "sub_bca92f0: Builder::cap_b at +0xB0");

LIFT_FN(sub_bca92f0, "sub_bca92f0", 0xBCA92F0, sub_bca92f0, sub_bca92f0Footprint);

} // namespace native::bgfx
