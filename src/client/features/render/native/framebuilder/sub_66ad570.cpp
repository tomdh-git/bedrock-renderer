// LIFT 0x66ad570 size 0xc5 1.26.62.01 BgfxFrameBuilder::endFrame
#include "sub_66ad570.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

namespace native {

// sub_66ad570 (0x66ad570, size 0xc5, 1.26.62.01) = BgfxFrameBuilder::endFrame.
//
// Releases six refcounted members of this (offsets 0xB0, 0x90, 0x70, 0x50, 0x30, 0x10,
// released in that order). For each member: obj = [this+off]; if obj != null then
// lock-dec count0xC (+0xC); when it reaches zero, call the object's vfptr[1] deallocator.
// The disassembly reaches that deallocator through loader-resolved data slot 0xF99FFA0
// (= sub_eea6040, vendor boundary). The last member (+0x10) is tail-called.
// Returns void.

void sub_66ad570(void* a0)
{
    static_assert(sizeof(void*) == 8, "sub_66ad570: x64 pointers and arguments are 8 bytes");
    void* const thisObj = a0;  // 0x66ad575  mov rsi,rcx  (RCX = this)

    // 0x66ad570..0x66ad578  prologue: push rsi; sub rsp,0x20; mov rsi,rcx
    void* const rsi = thisObj;  // 0x66ad575  mov rsi,rcx

    // ---- member +0xB0 (released first) ----
    // 0x66ad578..0x66ad597
    void* const objB0 =
        *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rsi) + kObjOffset0xB0);  // 0x66ad578  mov rcx,[rsi+0xB0]
    if (objB0 != nullptr) {                                                                // 0x66ad57f  test rcx,rcx
                                                                                             // 0x66ad582  je short 0x66AD597
        // 0x66ad584  lock dec dword ptr [rcx+0xC]
        // 0x66ad588  jne short 0x66AD597
        if (_InterlockedDecrement(
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(objB0) + kReleasedOffsetCount0xC)) == 0) {  // 0x66ad584  lock dec dword ptr [rcx+0xC]
                                                                                                  // 0x66ad588  jne short 0x66AD597
            // 0x66ad58a  mov rax,[rcx]
            // 0x66ad58d  mov rax,[rax+8]        (vfptr[8] = deallocator)
            // 0x66ad591  call qword ptr [0xF99FFA0]  ; sub_eea6040 (vendor boundary)
            void** const vfptrB0 = *reinterpret_cast<void***>(objB0);  // 0x66ad58a  mov rax,[rcx]
                                                                            // 0x66ad58d  mov rax,[rax+8]
            void (*const deallocB0)(void*) =
                reinterpret_cast<void (*)(void*)>(vfptrB0[1]);  // vfptr[8]
            deallocB0(objB0);   // 0x66ad591  call qword ptr [0xF99FFA0]
        }
    } // loc_66ad597:

    // ---- member +0x90 ----
    // 0x66ad597..0x66ad5b6
    void* const obj90 =
        *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rsi) + kObjOffset0x90);  // 0x66ad597  mov rcx,[rsi+0x90]
    if (obj90 != nullptr) {                                                                // 0x66ad59e  test rcx,rcx
                                                                                             // 0x66ad5a1  je short 0x66AD5B6
        // 0x66ad5a3  lock dec dword ptr [rcx+0xC]
        // 0x66ad5a7  jne short 0x66AD5B6
        if (_InterlockedDecrement(
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(obj90) + kReleasedOffsetCount0xC)) == 0) {  // 0x66ad5a3  lock dec dword ptr [rcx+0xC]
                                                                                                  // 0x66ad5a7  jne short 0x66AD5B6
            // 0x66ad5a9  mov rax,[rcx]
            // 0x66ad5ac  mov rax,[rax+8]        (vfptr[8] = deallocator)
            // 0x66ad5b0  call qword ptr [0xF99FFA0]  ; sub_eea6040 (vendor boundary)
            void** const vfptr90 = *reinterpret_cast<void***>(obj90);  // 0x66ad5a9  mov rax,[rcx]
                                                                            // 0x66ad5ac  mov rax,[rax+8]
            void (*const dealloc90)(void*) =
                reinterpret_cast<void (*)(void*)>(vfptr90[1]);  // vfptr[8]
            dealloc90(obj90);   // 0x66ad5b0  call qword ptr [0xF99FFA0]
        }
    } // loc_66ad5b6:

    // ---- member +0x70 ----
    // 0x66ad5b6..0x66ad5d2
    void* const obj70 =
        *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rsi) + kObjOffset0x70);  // 0x66ad5b6  mov rcx,[rsi+0x70]
    if (obj70 != nullptr) {                                                                // 0x66ad5bd  test rcx,rcx
                                                                                             // 0x66ad5c0  je short 0x66AD5D2
        // 0x66ad5c2  lock dec dword ptr [rcx+0xC]
        // 0x66ad5c6  jne short 0x66AD5D2
        if (_InterlockedDecrement(
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(obj70) + kReleasedOffsetCount0xC)) == 0) {  // 0x66ad5c2  lock dec dword ptr [rcx+0xC]
                                                                                                  // 0x66ad5c6  jne short 0x66AD5D2
            // 0x66ad5c8  mov rax,[rcx]
            // 0x66ad5cb  mov rax,[rax+8]        (vfptr[8] = deallocator)
            // 0x66ad5cc  call qword ptr [0xF99FFA0]  ; sub_eea6040 (vendor boundary)
            void** const vfptr70 = *reinterpret_cast<void***>(obj70);  // 0x66ad5c8  mov rax,[rcx]
                                                                            // 0x66ad5cb  mov rax,[rax+8]
            void (*const dealloc70)(void*) =
                reinterpret_cast<void (*)(void*)>(vfptr70[1]);  // vfptr[8]
            dealloc70(obj70);   // 0x66ad5cc  call qword ptr [0xF99FFA0]
        }
    } // loc_66ad5d2:

    // ---- member +0x50 ----
    // 0x66ad5d2..0x66ad5ee
    void* const obj50 =
        *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rsi) + kObjOffset0x50);  // 0x66ad5d2  mov rcx,[rsi+0x50]
    if (obj50 != nullptr) {                                                                // 0x66ad5d9  test rcx,rcx
                                                                                             // 0x66ad5dc  je short 0x66AD5EE
        // 0x66ad5de  lock dec dword ptr [rcx+0xC]
        // 0x66ad5e2  jne short 0x66AD5EE
        if (_InterlockedDecrement(
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(obj50) + kReleasedOffsetCount0xC)) == 0) {  // 0x66ad5de  lock dec dword ptr [rcx+0xC]
                                                                                                  // 0x66ad5e2  jne short 0x66AD5EE
            // 0x66ad5e4  mov rax,[rcx]
            // 0x66ad5e7  mov rax,[rax+8]        (vfptr[8] = deallocator)
            // 0x66ad5eb  call qword ptr [0xF99FFA0]  ; sub_eea6040 (vendor boundary)
            void** const vfptr50 = *reinterpret_cast<void***>(obj50);  // 0x66ad5e4  mov rax,[rcx]
                                                                            // 0x66ad5e7  mov rax,[rax+8]
            void (*const dealloc50)(void*) =
                reinterpret_cast<void (*)(void*)>(vfptr50[1]);  // vfptr[8]
            dealloc50(obj50);   // 0x66ad5e8  call qword ptr [0xF99FFA0]
        }
    } // loc_66ad5ee:

    // ---- member +0x30 ----
    // 0x66ad5ee..0x66ad60a
    void* const obj30 =
        *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rsi) + kObjOffset0x30);  // 0x66ad5ee  mov rcx,[rsi+0x30]
    if (obj30 != nullptr) {                                                                // 0x66ad5f5  test rcx,rcx
                                                                                             // 0x66ad5f8  je short 0x66AD60A
        // 0x66ad5fa  lock dec dword ptr [rcx+0xC]
        // 0x66ad5fe  jne short 0x66AD60A
        if (_InterlockedDecrement(
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(obj30) + kReleasedOffsetCount0xC)) == 0) {  // 0x66ad5fa  lock dec dword ptr [rcx+0xC]
                                                                                                  // 0x66ad5fe  jne short 0x66AD60A
            // 0x66ad600  mov rax,[rcx]
            // 0x66ad603  mov rax,[rax+8]        (vfptr[8] = deallocator)
            // 0x66ad607  call qword ptr [0xF99FFA0]  ; sub_eea6040 (vendor boundary)
            void** const vfptr30 = *reinterpret_cast<void***>(obj30);  // 0x66ad600  mov rax,[rcx]
                                                                            // 0x66ad603  mov rax,[rax+8]
            void (*const dealloc30)(void*) =
                reinterpret_cast<void (*)(void*)>(vfptr30[1]);  // vfptr[8]
            dealloc30(obj30);   // 0x66ad607  call qword ptr [0xF99FFA0]
        }
    } // loc_66ad60a:

    // ---- member +0x10 (last): tail-called path ----
    // 0x66ad60a..0x66ad62f
    void* const obj10 =
        *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rsi) + kObjOffset0x10);  // 0x66ad60a  mov rcx,[rsi+0x10]
    if (obj10 != nullptr) {                                                                // 0x66ad60e  test rcx,rcx
                                                                                             // 0x66ad611  je short 0x66AD62F
        // 0x66ad613  lock dec dword ptr [rcx+0xC]
        // 0x66ad617  jne short 0x66AD62F
        if (_InterlockedDecrement(
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(obj10) + kReleasedOffsetCount0xC)) == 0) {  // 0x66ad613  lock dec dword ptr [rcx+0xC]
                                                                                                  // 0x66ad617  jne short 0x66AD62F
            // 0x66ad619  mov rax,[rcx]
            // 0x66ad61c  mov rax,[rax+8]        (vfptr[8] = deallocator)
            // 0x66ad620  mov rdx,[0xF99FFA0]
            // 0x66ad62c  jmp rdx                  ; tail call sub_eea6040 -> return
            void** const vfptr10 = *reinterpret_cast<void***>(obj10);  // 0x66ad619  mov rax,[rcx]
                                                                            // 0x66ad61c  mov rax,[rax+8]
            void (*const dealloc10)(void*) =
                reinterpret_cast<void (*)(void*)>(vfptr10[1]);  // vfptr[8]
            dealloc10(obj10);   // tail call 0x66ad62c  jmp rdx
            return;             // tail call: does not fall through to epilogue
        }
    } // loc_66ad62f:

    // 0x66ad62f..0x66ad635  epilogue: add rsp,0x20; pop rsi; ret
    return;
}

// Verbatim copies of every `call` instruction in 0x66ad570..0x66ad635,
// kept as a reference (the deallocator target is sub_eea6040 via data slot
// 0xF99FFA0, vendor boundary; not called through native::Boundary here).
#if 0
0x66ad591  call qword ptr [0xF99FFA0]
0x66ad5b0  call qword ptr [0xF99FFA0]
0x66ad5cc  call qword ptr [0xF99FFA0]
0x66ad5e8  call qword ptr [0xF99FFA0]
0x66ad604  call qword ptr [0xF99FFA0]
#endif

LIFT_FN(sub_66ad570, "sub_66ad570", 0x66AD570, ::native::sub_66ad570, nullptr);

} // namespace native
