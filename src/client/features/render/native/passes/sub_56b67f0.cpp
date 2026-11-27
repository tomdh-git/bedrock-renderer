// LIFT 0x56b67f0 size 0xc8 1.26.62.01 sub_56b67f0
#include "sub_56b67f0.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

namespace native {

// sub_56b67f0 (0x56b67f0, size 0xc8, 1.26.62.01).
//
// Full instruction-by-instruction reversal:
//   0x56b67f0..0x56b67f5  push rsi; sub rsp,0x20
//   0x56b67f5             mov rsi,rcx
//   ... (processes 6 refcounted objects at +0xD0, +0xB0, +0x90, +0x70, +0x50, +0x30)
//   0x56b68af             jmp rdx (tail call for last slot)
//   0x56b68b2..0x56b68b7  add rsp,0x20; pop rsi; ret
//
// Reads: this+0xD0, this+0xB0, this+0x90, this+0x70, this+0x50, this+0x30 (ptr),
//   *ptr+0x0 (vfptr), *ptr+0x8 (vfptr[1] deallocator), *ptr+0xC (count0xC)
// Writes: *ptr+0xC (lock dec)
// Calls: 5x call + 1x tail call via data slot 0xF99FFA0 (sub_eea6040, boundary/vendor)
// Return: void

// 0x56b67f0..0x56b68b8
void sub_56b67f0(void* a0)
{
    static_assert(sizeof(void*) == 8, "sub_56b67f0: x64 pointers and arguments are 8 bytes");
    using DeallocFn = void (*)(void*);
    void* const thisObj = a0;  // RCX = this

    // 0x56b67f0..0x56b67f5  prologue: push rsi; sub rsp,0x20
    // 0x56b67f5             mov rsi,rcx
    void* rsi = thisObj;   // 0x56b67f5  mov rsi,rcx

    // Slot at +0xD0 (processed first)
    // 0x56b67f8  mov rcx,[rcx+0xD0]
    // 0x56b67ff  test rcx,rcx
    // 0x56b6802  je short 0x56B6817
    void* rcx = *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(thisObj) + kThisOffset0xD0);  // 0x56b67f8  mov rcx,[rcx+0xD0]
    if (rcx != nullptr) {                                                // 0x56b67ff  test rcx,rcx
                                                                          // 0x56b6802  je short 0x56B6817
        // 0x56b6804  lock dec dword ptr [rcx+0xC]
        // 0x56b6808  jne short 0x56B6817
        if (_InterlockedDecrement(
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(rcx) + kRefcountedOffsetCount0xC)) == 0) {  // 0x56b6804  lock dec dword ptr [rcx+0xC]
                                                                                                  // 0x56b6808  jne short 0x56B6817
            // 0x56b680a  mov rax,[rcx]
            // 0x56b680d  mov rax,[rax+8]
            // 0x56b6811  call qword ptr [0xF99FFA0]
            void** const vfptr = *reinterpret_cast<void***>(rcx);  // 0x56b680a  mov rax,[rcx]
                                                                    // 0x56b680d  mov rax,[rax+8]
            DeallocFn dealloc = reinterpret_cast<DeallocFn>(vfptr[1]);  // vfptr[1] at +0x8
            dealloc(rcx);  // 0x56b6811  call qword ptr [0xF99FFA0]
        }
    }

    // loc_56b6817: Slot at +0xB0
    // 0x56b6817  mov rcx,[rsi+0xB0]
    // 0x56b681e  test rcx,rcx
    // 0x56b6821  je short 0x56B6836
    rcx = *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(rsi) + kThisOffset0xB0);  // 0x56b6817  mov rcx,[rsi+0xB0]
    if (rcx != nullptr) {                                             // 0x56b681e  test rcx,rcx
                                                                         // 0x56b6821  je short 0x56B6836
        // 0x56b6823  lock dec dword ptr [rcx+0xC]
        // 0x56b6827  jne short 0x56B6836
        if (_InterlockedDecrement(
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(rcx) + kRefcountedOffsetCount0xC)) == 0) {  // 0x56b6823  lock dec dword ptr [rcx+0xC]
                                                                                                  // 0x56b6827  jne short 0x56B6836
            // 0x56b6829  mov rax,[rcx]
            // 0x56b682c  mov rax,[rax+8]
            // 0x56b6830  call qword ptr [0xF99FFA0]
            void** const vfptr = *reinterpret_cast<void***>(rcx);  // 0x56b6829  mov rax,[rcx]
                                                                    // 0x56b682c  mov rax,[rax+8]
            DeallocFn dealloc = reinterpret_cast<DeallocFn>(vfptr[1]);
            dealloc(rcx);  // 0x56b6830  call qword ptr [0xF99FFA0]
        }
    }

    // loc_56b6836: Slot at +0x90
    // 0x56b6836  mov rcx,[rsi+0x90]
    // 0x56b683d  test rcx,rcx
    // 0x56b6840  je short 0x56B6855
    rcx = *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(rsi) + kThisOffset0x90);  // 0x56b6836  mov rcx,[rsi+0x90]
    if (rcx != nullptr) {                                             // 0x56b683d  test rcx,rcx
                                                                         // 0x56b6840  je short 0x56B6855
        // 0x56b6842  lock dec dword ptr [rcx+0xC]
        // 0x56b6846  jne short 0x56B6855
        if (_InterlockedDecrement(
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(rcx) + kRefcountedOffsetCount0xC)) == 0) {  // 0x56b6842  lock dec dword ptr [rcx+0xC]
                                                                                                  // 0x56b6846  jne short 0x56B6855
            // 0x56b6848  mov rax,[rcx]
            // 0x56b684b  mov rax,[rax+8]
            // 0x56b684f  call qword ptr [0xF99FFA0]
            void** const vfptr = *reinterpret_cast<void***>(rcx);  // 0x56b6848  mov rax,[rcx]
                                                                    // 0x56b684b  mov rax,[rax+8]
            DeallocFn dealloc = reinterpret_cast<DeallocFn>(vfptr[1]);
            dealloc(rcx);  // 0x56b684f  call qword ptr [0xF99FFA0]
        }
    }

    // loc_56b6855: Slot at +0x70
    // 0x56b6855  mov rcx,[rsi+0x70]
    // 0x56b6859  test rcx,rcx
    // 0x56b685c  je short 0x56B6871
    rcx = *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(rsi) + kThisOffset0x70);  // 0x56b6855  mov rcx,[rsi+0x70]
    if (rcx != nullptr) {                                             // 0x56b6859  test rcx,rcx
                                                                         // 0x56b685c  je short 0x56B6871
        // 0x56b685e  lock dec dword ptr [rcx+0xC]
        // 0x56b6862  jne short 0x56B6871
        if (_InterlockedDecrement(
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(rcx) + kRefcountedOffsetCount0xC)) == 0) {  // 0x56b685e  lock dec dword ptr [rcx+0xC]
                                                                                                  // 0x56b6862  jne short 0x56B6871
            // 0x56b6864  mov rax,[rcx]
            // 0x56b6867  mov rax,[rax+8]
            // 0x56b686b  call qword ptr [0xF99FFA0]
            void** const vfptr = *reinterpret_cast<void***>(rcx);  // 0x56b6864  mov rax,[rcx]
                                                                    // 0x56b6867  mov rax,[rax+8]
            DeallocFn dealloc = reinterpret_cast<DeallocFn>(vfptr[1]);
            dealloc(rcx);  // 0x56b686b  call qword ptr [0xF99FFA0]
        }
    }

    // loc_56b6871: Slot at +0x50
    // 0x56b6871  mov rcx,[rsi+0x50]
    // 0x56b6875  test rcx,rcx
    // 0x56b6878  je short 0x56B688D
    rcx = *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(rsi) + kThisOffset0x50);  // 0x56b6871  mov rcx,[rsi+0x50]
    if (rcx != nullptr) {                                             // 0x56b6875  test rcx,rcx
                                                                         // 0x56b6878  je short 0x56B688D
        // 0x56b687a  lock dec dword ptr [rcx+0xC]
        // 0x56b687e  jne short 0x56B688D
        if (_InterlockedDecrement(
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(rcx) + kRefcountedOffsetCount0xC)) == 0) {  // 0x56b687a  lock dec dword ptr [rcx+0xC]
                                                                                                  // 0x56b687e  jne short 0x56B688D
            // 0x56b6880  mov rax,[rcx]
            // 0x56b6883  mov rax,[rax+8]
            // 0x56b6887  call qword ptr [0xF99FFA0]
            void** const vfptr = *reinterpret_cast<void***>(rcx);  // 0x56b6880  mov rax,[rcx]
                                                                    // 0x56b6883  mov rax,[rax+8]
            DeallocFn dealloc = reinterpret_cast<DeallocFn>(vfptr[1]);
            dealloc(rcx);  // 0x56b6887  call qword ptr [0xF99FFA0]
        }
    }

    // loc_56b688d: Slot at +0x30 (last, uses tail call)
    // 0x56b688d  mov rcx,[rsi+0x30]
    // 0x56b6891  test rcx,rcx
    // 0x56b6894  je short 0x56B68B2
    rcx = *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(rsi) + kThisOffset0x30);  // 0x56b688d  mov rcx,[rsi+0x30]
    if (rcx != nullptr) {                                             // 0x56b6891  test rcx,rcx
                                                                         // 0x56b6894  je short 0x56B68B2
        // 0x56b6896  lock dec dword ptr [rcx+0xC]
        // 0x56b689a  jne short 0x56B68B2
        if (_InterlockedDecrement(
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(rcx) + kRefcountedOffsetCount0xC)) == 0) {  // 0x56b6896  lock dec dword ptr [rcx+0xC]
                                                                                                  // 0x56b689a  jne short 0x56B68B2
            // 0x56b689c  mov rax,[rcx]
            // 0x56b689f  mov rax,[rax+8]
            // 0x56b68a3  mov rdx,[0xF99FFA0]
            // 0x56b68aa  add rsp,0x20
            // 0x56b68ae  pop rsi
            // 0x56b68af  jmp rdx
            void** const vfptr = *reinterpret_cast<void***>(rcx);  // 0x56b689c  mov rax,[rcx]
                                                                    // 0x56b689f  mov rax,[rax+8]
            void* const target = *reinterpret_cast<void**>(0xF99FFA0);  // 0x56b68a3  mov rdx,[0xF99FFA0]
            // Tail call: clean up stack frame and jump
            // add rsp,0x20; pop rsi; jmp rdx
            reinterpret_cast<DeallocFn>(target)(rcx);  // 0x56b68af  jmp rdx (tail call)
            return;
        }
    }

    // loc_56b68b2: epilogue
    // 0x56b68b2  add rsp,0x20
    // 0x56b68b6  pop rsi
    // 0x56b68b7  ret
    return;
}

} // namespace native

LIFT_FN(sub_56b67f0, "sub_56b67f0", 0x56B67F0, ::native::sub_56b67f0, nullptr);

// Verbatim instructions of [0x56b67f0, 0x56b68b8) (rdis dis 0x56b67f0 0xc8);
// machine-checked by tools/sigs/verify_oc.py against the exe.
#if 0
0x56b67f0  push rsi
0x56b67f1  sub rsp,0x20
0x56b67f5  mov rsi,rcx
0x56b67f8  mov rcx,[rcx+0xD0]
0x56b67ff  test rcx,rcx
0x56b6802  je short 0x56B6817
0x56b6804  lock dec dword ptr [rcx+0xC]
0x56b6808  jne short 0x56B6817
0x56b680a  mov rax,[rcx]
0x56b680d  mov rax,[rax+8]
0x56b6811  call qword ptr [0xF99FFA0]
0x56b6817  mov rcx,[rsi+0xB0]
0x56b681e  test rcx,rcx
0x56b6821  je short 0x56B6836
0x56b6823  lock dec dword ptr [rcx+0xC]
0x56b6827  jne short 0x56b6836
0x56b6829  mov rax,[rcx]
0x56b682c  mov rax,[rax+8]
0x56b6830  call qword ptr [0xF99FFA0]
0x56b6836  mov rcx,[rsi+0x90]
0x56b683d  test rcx,rcx
0x56b6840  je short 0x56b6855
0x56b6842  lock dec dword ptr [rcx+0xC]
0x56b6846  jne short 0x56b6855
0x56b6848  mov rax,[rcx]
0x56b684b  mov rax,[rax+8]
0x56b684f  call qword ptr [0xF99FFA0]
0x56b6855  mov rcx,[rsi+0x70]
0x56b6859  test rcx,rcx
0x56b685c  je short 0x56b6871
0x56b685e  lock dec dword ptr [rcx+0xC]
0x56b6862  jne short 0x56b6871
0x56b6864  mov rax,[rcx]
0x56b6867  mov rax,[rax+8]
0x56b686b  call qword ptr [0xF99FFA0]
0x56b6871  mov rcx,[rsi+0x50]
0x56b6875  test rcx,rcx
0x56b6878  je short 0x56b688d
0x56b687a  lock dec dword ptr [rcx+0xC]
0x56b687e  jne short 0x56b688d
0x56b6880  mov rax,[rcx]
0x56b6883  mov rax,[rax+8]
0x56b6887  call qword ptr [0xF99FFA0]
0x56b688d  mov rcx,[rsi+0x30]
0x56b6891  test rcx,rcx
0x56b6894  je short 0x56b68b2
0x56b6896  lock dec dword ptr [rcx+0xC]
0x56b689a  jne short 0x56b68b2
0x56b689c  mov rax,[rcx]
0x56b689f  mov rax,[rax+8]
0x56b68a3  mov rdx,[0xF99FFA0]
0x56b68aa  add rsp,0x20
0x56b68ae  pop rsi
0x56b68af  jmp rdx
0x56b68b2  add rsp,0x20
0x56b68b6  pop rsi
0x56b68b7  ret
#endif