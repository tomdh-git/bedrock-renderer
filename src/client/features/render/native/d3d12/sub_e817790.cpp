// LIFT 0xe817790 size 0xe8 1.26.62.01 sub_e817790
#include "sub_e817790.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

// Layout constants live in sub_e817790.h; cross-check the target model here [V].
static_assert(sizeof(void*) == 8, "e817790: x64 target");
static_assert(sizeof(native::E817790Registry) == 0x520, "e817790: registry footprint");

namespace native {

namespace {

// 0xE951550: __security_check_cookie (crt boundary, noreturn on failure) [V].
// Called at 0xe817872 with rcx = cookieStored ^ frame when the /GS cookie check fails.
native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");

// Calls at 0xe817813 / 0xe817833 / 0xe81784a go through `call qword ptr [0xF99FFA0]`.
// The cell at 0xF99FFA0 holds sub_eea6040, whose single instruction is `jmp rax`; rax is
// loaded from a vtable slot just before each call (0xe81780c / 0xe817823 / 0xe817846).
// So each is a guarded virtual call; expressing it as the resolved vtable-slot invocation
// is exactly what the jmp-rax thunk chain does.

} // namespace

extern "C" void sub_e817790(void* self, std::uint16_t key, std::uint32_t value) {
    // 0xe817790..0xe8177a2: push rsi; sub rsp,0x30; mov rax,rcx; /GS cookie:
    //   rcx = [0x1230A0C0]; xor rcx,rsp; mov [rsp+0x28],rcx.
    std::uintptr_t cookieSlot = 0;
    const std::uintptr_t cookieStored =
        *reinterpret_cast<std::uintptr_t*>(kGblCookie) ^ reinterpret_cast<std::uintptr_t>(&cookieSlot);

    E817790Registry* reg = static_cast<E817790Registry*>(self); // rax = self throughout

    // 0xe8177a7..0xe8177ab: cmp dx,0x7F ; ja 0xE817850 -> handles above 0x7F skip the whole body.
    if (key <= 0x7F) {
        // 0xe8177b1..0xe8177e7: register key in the seen-bitmap; append to keyList if new.
        const unsigned      word = key >> 6;                       // 0xe8177b5 mov r10d,r9d ; 0xe8177b8 shr r10d,6
        const std::uint64_t bit  = std::uint64_t(1) << (key & 0x3F); // 0xe8177c1 mov esi,1 ; 0xe8177c8 shl rsi,cl
        const std::uint64_t bits = reg->present[word];             // 0xe8177bc mov r11,[rax+r10*8+0x10]
        if ((bits & bit) == 0) {                                   // 0xe8177cb bt r11,r9 ; 0xe8177cf jb 0xE8177EB
            reg->present[word] = bits | bit;                       // 0xe8177d1 or r11,rsi ; 0xe8177d4 mov [rax+r10*8+0x10],r11
            const unsigned count = reg->count;                     // 0xe8177d9 movzx ecx,word ptr [rax+8]
            reg->keyList[count]  = key;                            // 0xe8177dd mov [rax+rcx*2+0x420],dx
            reg->count = static_cast<std::uint16_t>(count + 1);    // 0xe8177e5 inc ecx ; 0xe8177e7 mov [rax+8],cx
        }

        // 0xe8177eb..0xe8177f0: store value into the per-key record (both dwords).
        reg->perKey[key].v0 = value;                               // 0xe8177eb mov [rax+r9*8+0x20],r8d
        reg->perKey[key].v1 = value;                               // 0xe8177f0 mov [rax+r9*8+0x24],r8d

        // 0xe8177f5..0xe817804: connection = self->slots[key].connection ; skip if null.
        char* const slots = static_cast<char*>(reg->slots);        // 0xe8177f5 mov rsi,[rax]
        const std::size_t recOff = static_cast<std::size_t>(key) * kSlotStride; // 0xe8177f8 imul rax,r9,0x68
        void* const connection = *reinterpret_cast<void**>(slots + recOff + 0x18); // 0xe8177fc mov rcx,[rsi+rax+0x18]
        if (connection != nullptr) {                               // 0xe817801 test rcx,rcx ; 0xe817804 je 0xE817850
            char* const record = slots + recOff;                  // 0xe817806 add rsi,rax

            // 0xe817809..0xe817813: r1 = connection->vtable[0x120](connection).
            void** const vtbl1 = *reinterpret_cast<void***>(connection); // 0xe817809 mov rax,[rcx]
            void* const target1 = vtbl1[kVslotNotify / 8];         // 0xe81780c mov rax,[rax+0x120]
            const std::uint8_t r1 =
                reinterpret_cast<std::uint8_t (*)(void*)>(target1)(connection); // 0xe817813 call qword ptr [0xF99FFA0]

            // 0xe817819..0xe817833: connection->vtable[0x48](connection, r1, &kData_f4ed2c0, &outLocal).
            void* const connection2 = *reinterpret_cast<void**>(record + 0x18); // 0xe817819 mov rcx,[rsi+0x18]
            void** const vtbl2 = *reinterpret_cast<void***>(connection2);     // 0xe817820 mov rax,[rcx]
            void* const target2 = vtbl2[kVslotClose / 8];          // 0xe817823 mov rax,[rax+0x48]
            void* outLocal = nullptr;                              // 0xe81782e lea r9,[rsp+0x20]
            reinterpret_cast<void (*)(void*, std::uint32_t, const void*, void**)>(target2)(
                connection2,                                       // rcx
                static_cast<std::uint32_t>(r1),                    // 0xe81781d movzx edx,al
                reinterpret_cast<const void*>(kData_f4ed2c0),      // 0xe817827 lea r8,[0xF4ED2C0]
                &outLocal);                                        // 0xe817833 call qword ptr [0xF99FFA0]

            // 0xe817839..0xe81784a: if (outLocal) outLocal->vtable[0x10](outLocal).
            if (outLocal != nullptr) {                             // 0xe81783e test rcx,rcx ; 0xe817841 je 0xE817850
                void** const vtbl3 = *reinterpret_cast<void***>(outLocal); // 0xe817843 mov rax,[rcx]
                void* const target3 = vtbl3[kVslotRelease / 8];    // 0xe817846 mov rax,[rax+0x10]
                reinterpret_cast<void (*)(void*)>(target3)(outLocal); // 0xe81784a call qword ptr [0xF99FFA0]
            }
        }
    }

    // 0xe817850..0xe817869: /GS epilogue. rax = cookieStored ^ frame; cmp with [0x1230A0C0]; jne -> failure.
    if (*reinterpret_cast<std::uintptr_t*>(kGblCookie) !=
        (cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot))) {
        // 0xe81786a..0xe817877: failure path (cookie mismatch).
        sub_e951550(cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot)); // 0xe817872 call 0xE951550
        __assume(false);                                           // 0xe817877 int3 (unreachable)
    }
    // 0xe817864 add rsp,0x30 ; 0xe817868 pop rsi ; 0xe817869 ret.
}

// Verbatim call instructions in [0xe817790, 0xe817878) (rdis dis output, two spaces after address):
#if 0
0xe817813  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe817833  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe81784a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe817872  call 0xE951550                                ; -> sub_e951550
#endif

LIFT_FN(e817790, "sub_e817790", 0xE817790, sub_e817790, nullptr);

} // namespace native