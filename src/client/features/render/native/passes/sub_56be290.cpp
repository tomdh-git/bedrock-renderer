// LIFT 0x56be290 size 0xc6 1.26.62.01 sub_56be290
#include "sub_56be290.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

namespace native {

// sub_56be290 (0x56be290, size 0xc6, 1.26.62.01).
//
// Full reversal of [0x56be290, 0x56be356):
//   0x56be290..0x56be2e0   prologue, vtable install, conditional sub_e935700 call or noreturn fail path
//   0x56be2e0..0x56be2f9   reset: field0x80 = 0, field0x88 = 0xF, byte field0x70 = 0
//   0x56be2fa..0x56be30b   release releaseObj (&a0+0x18) through data slot 0xF99FFA0
//   0x56be311..0x56be33b   release refObj (a0+0x10): lock dec +0xC; tail jmp through slot 0xF99FFA0 on zero
//   0x56be336..0x56be33b   epilogue: add rsp,0x30; pop rsi; ret
//   0x56be33c..0x56be356   fail path: [0xF9A8C78](0,0,0,0); int3
//
// x64 Microsoft ABI: RCX = a0, return void. No null guards and no SEH: none exist in the original.

void sub_56be290(void* a0)
{
    // 0x56be290..0x56be298
    //   0x56be290  push rsi
    //   0x56be291  sub rsp,0x30
    //   0x56be295  mov rsi,rcx
    //   0x56be298  lea rax,[0xF25CB90]
    //   0x56be29f  mov [rcx],rax
    uint8_t* const thisObj = reinterpret_cast<uint8_t*>(a0);
    *reinterpret_cast<void**>(a0) = reinterpret_cast<void*>(0xF25CB90);  // 0x56be298  lea rax,[0xF25CB90]; 0x56be29f  mov [rcx],rax

    // 0x56be2a2..0x56be2d8
    //   0x56be2a2  mov rax,[rcx+0x88]
    //   0x56be2a9  cmp rax,0x10
    //   0x56be2ad  jb short 0x56BE2E0
    const std::uint64_t field0x88 =
        *reinterpret_cast<const std::uint64_t*>(thisObj + Sub56be290Layout::kOffField0x88);  // 0x56be2a2  mov rax,[rcx+0x88]
    if (field0x88 >= 0x10) {  // 0x56be2a9  cmp rax,0x10 ; 0x56be2ad  jb short 0x56BE2E0
        // 0x56be2af  mov rcx,[rsi+0x70]
        // 0x56be2b3  lea rdx,[rax+1]
        // 0x56be2b7  cmp rdx,0x1000
        // 0x56be2be  jb short 0x56BE2DB
        void* const data = *reinterpret_cast<void**>(thisObj + Sub56be290Layout::kOffData);   // 0x56be2af  mov rcx,[rsi+0x70]
        const std::uint64_t field0x88p1 = field0x88 + 1;                                      // 0x56be2b3  lea rdx,[rax+1]
        if (field0x88p1 < 0x1000) {                                                           // 0x56be2b7  cmp rdx,0x1000 ; 0x56be2be  jb short 0x56BE2DB
            // 0x56be2db  call 0xE935700   ; rcx = data (rdx = field0x88 + 1 is dead in sub_e935700)
            native::sub_e935700(data);                                                        // 0x56be2db  call 0xE935700
        } else {
            // 0x56be2c0  mov r8,[rcx-8]
            // 0x56be2c4  add rcx,0xFFFFFFFFFFFFFFF8
            // 0x56be2c8  sub rcx,r8
            // 0x56be2cb  cmp rcx,0x20
            // 0x56be2cf  jae short 0x56BE33C
            const std::uint64_t blockSize =
                *reinterpret_cast<const std::uint64_t*>(reinterpret_cast<uint8_t*>(data) - 8);  // 0x56be2c0  mov r8,[rcx-8]
            const std::uint64_t delta =
                reinterpret_cast<std::uintptr_t>(reinterpret_cast<uint8_t*>(data) - 8) - blockSize;  // 0x56be2c4..0x56be2c8
            if (delta >= 0x20) {  // 0x56be2cb  cmp rcx,0x20 ; 0x56be2cf  jae short 0x56BE33C
                // 0x56be33c..0x56be355   noreturn fail path
                //   0x56be33c  mov qword ptr [rsp+0x20],0
                //   0x56be345  xor ecx,ecx
                //   0x56be347  xor edx,edx
                //   0x56be349  xor r8d,r8d
                //   0x56be34c  xor r9d,r9d
                //   0x56be34f  call qword ptr [0xF9A8C78]   ; fail handler, 4 zero args
                //   0x56be355  int3
                auto failFn = reinterpret_cast<void (*)(void*, void*, void*, void*)>(
                    *reinterpret_cast<const std::uintptr_t*>(
                        RewriteRegistry::imageBase() + kRvaFailSlot));  // 0x56be34f  call qword ptr [0xF9A8C78] (slot read at call time)
                failFn(nullptr, nullptr, nullptr, nullptr);                                // 0x56be34f  call qword ptr [0xF9A8C78]
                __debugbreak();                                                          // 0x56be355  int3
                __assume(false);                                                         // int3 is noreturn pad
            } else {
                // 0x56be2d1  add rax,0x28
                // 0x56be2d5  mov rdx,rax
                // 0x56be2d8  mov rcx,r8
                // 0x56be2db  call 0xE935700   ; rcx = blockSize
                native::sub_e935700(reinterpret_cast<void*>(blockSize));  // 0x56be2db  call 0xE935700
            }
        }
    }

    // 0x56be2e0..0x56be2f9   reset to small state
    //   0x56be2e0  mov qword ptr [rsi+0x80],0
    //   0x56be2eb  mov qword ptr [rsi+0x88],0xF
    //   0x56be2f6  mov byte ptr [rsi+0x70],0
    *reinterpret_cast<std::uint64_t*>(thisObj + Sub56be290Layout::kOffField0x80) = 0;   // 0x56be2e0  mov qword ptr [rsi+0x80],0
    *reinterpret_cast<std::uint64_t*>(thisObj + Sub56be290Layout::kOffField0x88) = 0xF; // 0x56be2eb  mov qword ptr [rsi+0x88],0xF
    *reinterpret_cast<uint8_t*>(thisObj + Sub56be290Layout::kOffData) = 0;              // 0x56be2f6  mov byte ptr [rsi+0x70],0

    // 0x56be2fa..0x56be30b   release releaseObj (a0+0x18) through data slot 0xF99FFA0
    //   0x56be2fa  mov rax,[rsi+0x18]
    //   0x56be2fe  test rax,rax
    //   0x56be301  je short 0x56BE311
    //   0x56be303  lea rcx,[rsi+0x18]
    //   0x56be307  mov rax,[rax+8]        ; dead load
    //   0x56be30b  call qword ptr [0xF99FFA0]   ; sub_eea6040, boundary/vendor thunk via data slot
    void** const releaseObj = reinterpret_cast<void**>(thisObj + 0x18);
    if (*releaseObj != nullptr) {  // 0x56be2fe  test rax,rax ; 0x56be301  je short 0x56BE311
        (void)*reinterpret_cast<const std::uint64_t*>(
            reinterpret_cast<uint8_t*>(*releaseObj) + 8);  // 0x56be307  mov rax,[rax+8] (dead)
        // 0x56be303  lea rcx,[rsi+0x18]  -> rcx = releaseObj
        auto releaseFn18 = reinterpret_cast<void (*)(void**)>(
            *reinterpret_cast<const std::uintptr_t*>(
                RewriteRegistry::imageBase() + kRvaReleaseSlot));  // slot read at call time
        releaseFn18(releaseObj);  // 0x56be30b  call qword ptr [0xF99FFA0]  ; rcx = &a0+0x18
    }

    // 0x56be311..0x56be33b   release refObj (a0+0x10)
    //   0x56be311  mov rcx,[rsi+0x10]
    //   0x56be315  test rcx,rcx
    //   0x56be318  je short 0x56BE336
    //   0x56be31a  lock dec dword ptr [rcx+0xC]
    //   0x56be31e  jne short 0x56BE336
    void* const refObj = *reinterpret_cast<void**>(thisObj + 0x10);  // 0x56be311  mov rcx,[rsi+0x10]
    if (refObj != nullptr) {  // 0x56be315  test rcx,rcx ; 0x56be318  je short 0x56BE336
        if (_InterlockedDecrement(
                reinterpret_cast<volatile long*>(reinterpret_cast<uint8_t*>(refObj) + 0xC)) == 0) {  // 0x56be31a..0x56be31e
            //   0x56be320  mov rax,[rcx]
            //   0x56be323  mov rax,[rax+8]   ; dead load
            //   0x56be327  mov rdx,[0xF99FFA0]
            //   0x56be333  jmp rdx            ; tail jmp through data slot 0xF99FFA0: rcx = refObj, rdx = slot value
            (void)*reinterpret_cast<void**>(refObj);             // 0x56be320  mov rax,[rcx] (dead)
            (void)*reinterpret_cast<const std::uint64_t*>(  // 0x56be323  mov rax,[rax+8] (dead)
                reinterpret_cast<uint8_t*>(refObj) + 8);
            auto releaseFn10 = reinterpret_cast<void (*)(void*, void*)>(
                *reinterpret_cast<const std::uintptr_t*>(
                    RewriteRegistry::imageBase() + kRvaReleaseSlot));  // 0x56be327  mov rdx,[0xF99FFA0] (slot read at call time)
            releaseFn10(refObj, releaseFn10);  // 0x56be333  jmp rdx  ; rcx = refObj, rdx = slot value (tail call)
            __assume(false);                       // tail jump: control never returns to this frame
        }
    }

    // 0x56be336..0x56be33b   epilogue
    //   0x56be336  add rsp,0x30
    //   0x56be33a  pop rsi
    //   0x56be33b  ret
    return;
}

} // namespace native

// Registry entry: name, Sigs.json symbol, knownRva, lifted function, footprint (nullptr: no footprint declared).
LIFT_FN(sub_56be290, "sub_56be290", 0x56be290, ::native::sub_56be290, nullptr);

// Verbatim instructions of [0x56be290, 0x56be356) (rdis dis 0x56be290 0xc6);
// machine-checked by tools/sigs/verify_oc.py against the exe.
#if 0
0x56be290  push rsi
0x56be291  sub rsp,0x30
0x56be295  mov rsi,rcx
0x56be298  lea rax,[0xF25CB90]
0x56be29f  mov [rcx],rax
0x56be2a2  mov rax,[rcx+0x88]
0x56be2a9  cmp rax,0x10
0x56be2ad  jb short 0x56BE2E0
0x56be2af  mov rcx,[rsi+0x70]
0x56be2b3  lea rdx,[rax+1]
0x56be2b7  cmp rdx,0x1000
0x56be2be  jb short 0x56BE2DB
0x56be2c0  mov r8,[rcx-8]
0x56be2c4  add rcx,0xFFFFFFFFFFFFFFF8
0x56be2c8  sub rcx,r8
0x56be2cb  cmp rcx,0x20
0x56be2cf  jae short 0x56BE33C
0x56be2d1  add rax,0x28
0x56be2d5  mov rdx,rax
0x56be2d8  mov rcx,r8
0x56be2db  call 0xE935700
0x56be2e0  mov qword ptr [rsi+0x80],0
0x56be2eb  mov qword ptr [rsi+0x88],0xF
0x56be2f6  mov byte ptr [rsi+0x70],0
0x56be2fa  mov rax,[rsi+0x18]
0x56be2fe  test rax,rax
0x56be301  je short 0x56BE311
0x56be303  lea rcx,[rsi+0x18]
0x56be307  mov rax,[rax+8]
0x56be30b  call qword ptr [0xF99FFA0]
0x56be311  mov rcx,[rsi+0x10]
0x56be315  test rcx,rcx
0x56be318  je short 0x56BE336
0x56be31a  lock dec dword ptr [rcx+0xC]
0x56be31e  jne short 0x56BE336
0x56be320  mov rax,[rcx]
0x56be323  mov rax,[rax+8]
0x56be327  mov rdx,[0xF99FFA0]
0x56be32e  add rsp,0x30
0x56be332  pop rsi
0x56be333  jmp rdx
0x56be336  add rsp,0x30
0x56be33a  pop rsi
0x56be33b  ret
0x56be33c  mov qword ptr [rsp+0x20],0
0x56be345  xor ecx,ecx
0x56be347  xor edx,edx
0x56be349  xor r8d,r8d
0x56be34c  xor r9d,r9d
0x56be34f  call qword ptr [0xF9A8C78]
0x56be355  int3
#endif
