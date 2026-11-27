// LIFT 0x67602c0 size 0xea 1.26.62.01 sub_67602c0
#include "sub_67602c0.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

// sub_e935700 (lift set): argument forwarded in RCX, result in RAX.
// Forward-declared here (native::sub_e935700) rather than including sub_e935700.h, which
// contains a static_assert(sizeof(...)) over its own not-yet-complete type.
namespace native {
void* sub_e935700(void* a0);
}

namespace native::helpers {

// sub_67602c0 (0x67602c0, size 0xea, 1.26.62.01).
//
// Full reversal of [0x67602c0, 0x67603aa):
//   0x67602c0..0x67602d6   prologue; handle = self+8; null handle -> ret (rax undefined)
//   0x67602dc..0x6760340   walk block array [self+0x18, self+0x20) in 0x48 steps:
//                         for each block with flag byte +0x40 == 1 and begin != 0:
//                           size = block+0x10 - block+0x00
//                           if size < 0x1000: arg = block+0x00
//                           else: validate heap block at block+0x00 - 8; corrupt -> noreturn fail
//                                   arg = block size header
//                           call sub_e935700(arg); clear block +0x00..+0x10 (16 bytes)
//   0x6760341..0x676037e   total = self+0x10 * 72; if total < 0x1000: arg = handle
//                         else: validate heap block at handle - 8; corrupt -> noreturn fail
//                                   arg = block size header
//                         tail jmp sub_e935700(arg); return its result
//   0x6760383..0x676038f   null-handle epilogue; ret (rax undefined)
//   0x6760390..0x67603aa   noreturn fail path: call qword ptr [0xF9A8C78](0,0,0,0); int3
//
// x64 Microsoft ABI: RCX = this, return in RAX. No null guards and no SEH: none exist in
// the original; none are added.

void* sub_67602c0(sub_67602c0_state* self)
{
    // 0x67602c0  push rsi
    // 0x67602c1  push rdi
    // 0x67602c2  push rbx
    // 0x67602c3  sub rsp,0x40
    // 0x67602c7  movaps [rsp+0x30],xmm6
    // 0x67602cc  mov rsi,rcx                 ; rsi = self (this)
    // 0x67602cf  mov rcx,[rsi+8]             ; rcx = handle
    void* const handle =
        *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(self) +
                                  sub_67602c0_state::kOffHandle);  // 0x67602cf  mov rcx,[rsi+8]

    // 0x67602d3  test rcx,rcx
    // 0x67602d6  je short 0x6760383         ; null handle -> epilogue + ret (rax undefined)
    if (handle == nullptr) {                // 0x67602d3  test rcx,rcx ; 0x67602d6  je short 0x6760383
        // 0x6760383..0x676038f   epilogue; ret  (return value undefined in the original)
        return nullptr;                     // 0x676038f  ret  (rax undefined on this path)
    }

    // 0x67602dc  mov rdi,[rsi+0x18]         ; rdi = begin
    // 0x67602e0  mov rbx,[rsi+0x20]         ; rbx = end
    sub_67602c0_block* const begin =
        reinterpret_cast<sub_67602c0_block*>(reinterpret_cast<std::uint8_t*>(self) +
                                             sub_67602c0_state::kOffBegin);  // 0x67602dc  mov rdi,[rsi+0x18]
    sub_67602c0_block* const end =
        reinterpret_cast<sub_67602c0_block*>(reinterpret_cast<std::uint8_t*>(self) +
                                             sub_67602c0_state::kOffEnd);    // 0x67602e0  mov rbx,[rsi+0x20]

    // 0x67602e4  cmp rdi,rbx
    // 0x67602e7  je short 0x6760345         ; empty array -> skip the walk
    bool corrupt = false;
    if (begin != end) {                     // 0x67602e4  cmp rdi,rbx ; 0x67602e7  je short 0x6760345
        // 0x67602e9  xorps xmm6,xmm6        ; cleared value for the stores below

        for (sub_67602c0_block* it = begin; it != end; ++it) {  // 0x6760300  add rdi,0x48 ; cmp rdi,rbx
            // 0x6760309  cmp byte ptr [rdi+0x40],1
            // 0x676030d  jne short 0x6760300   ; skip block when flag != 1
            if (it->flag == 1) {            // 0x6760309  cmp byte [rdi+0x40],1 ; 0x676030d  jne short 0x6760300
                // 0x676030f  mov rcx,[rdi]     ; rcx = block begin
                // 0x6760312  test rcx,rcx
                // 0x6760315  je short 0x6760300   ; skip block when begin == 0
                void* const blockBegin = it->begin;  // 0x676030f  mov rcx,[rdi]
                if (blockBegin != nullptr) {         // 0x6760312  test rcx,rcx ; 0x6760315  je short 0x6760300
                    // 0x6760317  mov rdx,[rdi+0x10]  ; rdx = block end
                    // 0x676031b  sub rdx,rcx         ; size = end - begin (unsigned, wraps)
                    // 0x676031e  cmp rdx,0x1000
                    const std::uintptr_t size =
                        reinterpret_cast<std::uintptr_t>(it->end) -
                        reinterpret_cast<std::uintptr_t>(blockBegin);  // 0x6760317..0x676031b

                    void* deallocArg = nullptr;
                    if (size < 0x1000) {                          // 0x676031e  cmp rdx,0x1000
                                                                    // 0x6760325  jb short 0x67602F0  ; rcx stays blockBegin
                        deallocArg = blockBegin;                  // 0x67602f0  call 0xE935700 ; rcx = blockBegin
                    } else {
                        // 0x6760327  mov rax,[rcx-8]              ; block size header
                        // 0x676032b  add rcx,0xFFFFFFFFFFFFFFF8   ; rcx = blockBegin - 8
                        // 0x676032f  sub rcx,rax                  ; delta = (blockBegin-8) - blockSize
                        // 0x6760332  cmp rcx,0x20
                        // 0x6760336  jae short 0x6760390          ; corrupt -> noreturn fail path
                        const std::uintptr_t blockSize =
                            *reinterpret_cast<const std::uintptr_t*>(
                                reinterpret_cast<std::uint8_t*>(blockBegin) - 8);  // 0x6760327  mov rax,[rcx-8]
                        const std::uintptr_t delta =
                            reinterpret_cast<std::uintptr_t>(
                                reinterpret_cast<std::uint8_t*>(blockBegin) - 8) -
                            blockSize;                             // 0x676032b..0x676032f
                        if (delta >= 0x20) {                     // 0x6760332  cmp rcx,0x20
                            corrupt = true;                      // 0x6760336  jae short 0x6760390
                            break;                               // break out of the block walk
                        }
                        // 0x6760338  or rdx,0x27           ; size | 0x27 (dead in sub_e935700)
                        // 0x676033c  mov rcx,rax           ; argument = blockSize
                        (void)(size | 0x27);                  // 0x6760338  or rdx,0x27
                        deallocArg = reinterpret_cast<void*>(blockSize);  // 0x676033c  mov rcx,rax
                    }

                    // 0x67602f0  call 0xE935700           ; rcx = deallocArg
                    native::sub_e935700(deallocArg);      // 0x67602f0  call 0xE935700 (lift set)
                    // 0x67602f5  movups [rdi],xmm6        ; block +0x00..+0x10 = 0
                    // 0x67602f8  mov qword [rdi+0x10],0   ; block +0x10 = 0
                    it->begin = nullptr;                  // 0x67602f5  movups [rdi],xmm6  (+0x00)
                    it->end = nullptr;                    // 0x67602f8  mov qword [rdi+0x10],0
                }
            }
        }
    }

    // 0x6760341  mov rcx,[rsi+8]            ; rcx = handle (again)
    // 0x6760345  mov rax,[rsi+0x10]         ; rax = count
    // 0x6760349  shl rax,3                  ; rax = count * 8
    // 0x676034d  lea rdx,[rax+rax*8]        ; rdx = count * 72
    // 0x6760351  cmp rdx,0x1000
    const std::uintptr_t total =
        static_cast<std::uintptr_t>(self->count) * 72ULL;   // 0x6760345..0x676034d

    void* finalArg = nullptr;
    if (!corrupt && total < 0x1000) {              // 0x6760351  cmp rdx,0x1000
                                                   // 0x6760358  jb short 0x6760372  ; arg = handle
        finalArg = handle;                         // 0x6760372  jmp 0xE935700  ; rcx = handle
    } else if (!corrupt) {
        // 0x676035a  mov rax,[rcx-8]              ; block size header at handle - 8
        // 0x676035e  add rcx,0xFFFFFFFFFFFFFFF8   ; rcx = handle - 8
        // 0x6760362  sub rcx,rax                  ; delta = (handle-8) - blockSize
        // 0x6760365  cmp rcx,0x20
        // 0x6760369  jae short 0x6760390          ; corrupt -> noreturn fail path
        const std::uintptr_t blockSize =
            *reinterpret_cast<const std::uintptr_t*>(
                reinterpret_cast<std::uint8_t*>(handle) - 8);  // 0x676035a  mov rax,[rcx-8]
        const std::uintptr_t delta =
            reinterpret_cast<std::uintptr_t>(
                reinterpret_cast<std::uint8_t*>(handle) - 8) -
            blockSize;                               // 0x676035e..0x6760362
        if (delta >= 0x20) {                       // 0x6760365  cmp rcx,0x20
            corrupt = true;                        // 0x6760369  jae short 0x6760390
        }
        // 0x676036b  add rdx,0x27           ; count*72 + 0x27 (dead in sub_e935700)
        // 0x676036f  mov rcx,rax            ; argument = blockSize
        (void)(total + 0x27);                    // 0x676036b  add rdx,0x27
        finalArg = reinterpret_cast<void*>(blockSize);  // 0x676036f  mov rcx,rax
    }

    // 0x6760372  movaps xmm6,[rsp+0x30]
    // 0x6760377  add rsp,0x40
    // 0x676037b  pop rbx
    // 0x676037c  pop rdi
    // 0x676037d  pop rsi
    if (corrupt) {                                 // 0x6760390  noreturn fail path
        // 0x6760390  mov qword ptr [rsp+0x20],0   ; dead stack store (never read)
        // 0x6760399  xor ecx,ecx
        // 0x676039b  xor edx,edx
        // 0x676039d  xor r8d,r8d
        // 0x67603a0  xor r9d,r9d
        // 0x67603a3  call qword ptr [0xF9A8C78]   ; fail handler via data slot, 4 zero args
        // 0x67603a9  int3                         ; noreturn pad
        auto failFn = reinterpret_cast<void (*)(void*, void*, void*, void*)>(
            *reinterpret_cast<const std::uintptr_t*>(kRvaFailSlot));  // slot read at call time
        failFn(nullptr, nullptr, nullptr, nullptr);    // 0x67603a3  call qword ptr [0xF9A8C78]
        __assume(false);                               // 0x67603a9  int3  (noreturn)
    }

    // 0x676037e  jmp 0xE935700              ; tail call sub_e935700(finalArg); return its result
    return native::sub_e935700(finalArg);    // 0x676037e  jmp 0xE935700
}

} // namespace native::helpers

// Registry entry: name, Sigs.json symbol, knownRva, lifted function, footprint (nullptr).
LIFT_FN(sub_67602c0, "sub_67602c0", 0x67602c0, ::native::helpers::sub_67602c0, nullptr);

// Verbatim instructions of [0x67602c0, 0x67603aa) (rdis dis 0x67602c0 0xea);
// machine-checked by tools/sigs/verify_oc.py against the exe.
#if 0
0x67602c0  push rsi
0x67602c1  push rdi
0x67602c2  push rbx
0x67602c3  sub rsp,0x40
0x67602c7  movaps [rsp+0x30],xmm6
0x67602cc  mov rsi,rcx
0x67602cf  mov rcx,[rcx+8]
0x67602d3  test rcx,rcx
0x67602d6  je short 0x6760383
0x67602dc  mov rdi,[rsi+0x18]
0x67602e0  mov rbx,[rsi+0x20]
0x67602e4  cmp rdi,rbx
0x67602e7  je short 0x6760345
0x67602e9  xorps xmm6,xmm6
0x67602ec  jmp short 0x6760309
0x67602f0  call 0xE935700
0x67602f5  movups [rdi],xmm6
0x67602f8  mov qword ptr [rdi+0x10],0
0x6760300  add rdi,0x48
0x6760304  cmp rdi,rbx
0x6760307  je short 0x6760341
0x6760309  cmp byte ptr [rdi+0x40],1
0x676030d  jne short 0x6760300
0x676030f  mov rcx,[rdi]
0x6760312  test rcx,rcx
0x6760315  je short 0x6760300
0x6760317  mov rdx,[rdi+0x10]
0x676031b  sub rdx,rcx
0x676031e  cmp rdx,0x1000
0x6760325  jb short 0x67602f0
0x6760327  mov rax,[rcx-8]
0x676032b  add rcx,0xFFFFFFFFFFFFFFF8
0x676032f  sub rcx,rax
0x6760332  cmp rcx,0x20
0x6760336  jae short 0x6760390
0x6760338  or rdx,0x27
0x676033c  mov rcx,rax
0x676033f  jmp short 0x67602f0
0x6760341  mov rcx,[rsi+8]
0x6760345  mov rax,[rsi+0x10]
0x6760349  shl rax,3
0x676034d  lea rdx,[rax+rax*8]
0x6760351  cmp rdx,0x1000
0x6760358  jb short 0x6760372
0x676035a  mov rax,[rcx-8]
0x676035e  add rcx,0xFFFFFFFFFFFFFFF8
0x6760362  sub rcx,rax
0x6760365  cmp rcx,0x20
0x6760369  jae short 0x6760390
0x676036b  add rdx,0x27
0x676036f  mov rcx,rax
0x6760372  movaps xmm6,[rsp+0x30]
0x6760377  add rsp,0x40
0x676037b  pop rbx
0x676037c  pop rdi
0x676037d  pop rsi
0x676037e  jmp 0xE935700
0x6760383  movaps xmm6,[rsp+0x30]
0x6760388  add rsp,0x40
0x676038c  pop rbx
0x676038d  pop rdi
0x676038e  pop rsi
0x676038f  ret
0x6760390  mov qword ptr [rsp+0x20],0
0x6760399  xor ecx,ecx
0x676039b  xor edx,edx
0x676039d  xor r8d,r8d
0x67603a0  xor r9d,r9d
0x67603a3  call qword ptr [0xF9A8C78]
0x67603a9  int3
#endif
