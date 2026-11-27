// LIFT 0xc28a920 size 0xeb 1.26.62.01 sub_c28a920
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_c28a920.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

// sub_e935700 is lift set (0xe935700, tail-call forwarder to sub_392960).
// Forward-declared here rather than including sub_e935700.h. Signature matches
// sub_e935700.h exactly: void* sub_e935700(void* a0).
namespace native {
void* sub_e935700(void* a0);
}

// Fail handler through data slot [0xF9A8C78] (brief rule 69). Noreturn:
// 0xc28aa04 call qword ptr [0xF9A8C78]; 0xc28aa0a int3 (trap if it returns).
[[noreturn]] void sub_c28a920Fail() {
    using fail_fn = void (*)(void*, void*, void*, void*, void*);
    fail_fn const fail = reinterpret_cast<fail_fn>(
        *reinterpret_cast<std::uintptr_t*>(
            RewriteRegistry::imageBase() + sub_c28a920Layout::kFailSlotRva));
    fail(nullptr, nullptr, nullptr, nullptr, nullptr);   // 0xc28aa04 call qword ptr [0xF9A8C78]
    __debugbreak();                                      // 0xc28aa0a int3
    __assume(0);
}

uintptr_t sub_c28a920(sub_c28a920_state* self) {
    // 0xc28a920..0xc28a944: prologue and entry test
    //   0xc28a920  push r14
    //   0xc28a922  push rsi
    //   0xc28a923  push rdi
    //   0xc28a924  push rbx
    //   0xc28a925  sub rsp,0x28
    //   0xc28a929  mov rdi,[rcx]        ; rdi = self->begin
    //   0xc28a92c  test rdi,rdi
    //   0xc28a92f  je 0xC28A9E7         ; null self -> epilogue (ret, RAX indeterminate)
    //   0xc28a935  mov rsi,rcx          ; rsi = self
    //   0xc28a938  mov r14,[rcx+8]      ; r14 = self->end
    //   0xc28a93c  cmp rdi,r14
    //   0xc28a93f  jne short 0xC28A96B  ; non-empty array -> loop body
    //   0xc28a941  jmp short 0xC28A9A9  ; empty array -> tail
    //   0xc28a943  nop [rax+rax]
    std::uint8_t* rdi = reinterpret_cast<std::uint8_t*>(self->begin);  // 0xc28a929 mov rdi,[rcx]
    if (rdi == nullptr) {                       // 0xc28a92c test rdi,rdi ; 0xc28a92f je c28a9e7
        return 0;                               // 0xc28a9e7..0xc28a9f0 epilogue; RAX indeterminate
    }
    std::uint8_t* const rsi = reinterpret_cast<std::uint8_t*>(self);   // 0xc28a935 mov rsi,rcx
    std::uint8_t* r14 = reinterpret_cast<std::uint8_t*>(self->end);    // 0xc28a938 mov r14,[rcx+8]

    // Loop body (entry condition 0xc28a93c cmp rdi,r14 / 0xc28a93f jne c28a96b;
    // increment/bound test 0xc28a962 add rdi,8 / 0xc28a966 cmp rdi,r14 /
    // 0xc28a969 je short c28a9a6).
    while (rdi != r14) {
        // 0xc28a96b..0xc28a97c: fetch entry and null-test it
        //   0xc28a96b  mov rbx,[rdi]        ; rbx = entry object
        //   0xc28a96e  test rbx,rbx
        //   0xc28a971  je short 0xC28A962   ; null entry -> skip to next
        //   0xc28a973  mov rcx,[rbx+0x28]   ; rcx = entry->buffer
        //   0xc28a977  test rcx,rcx
        //   0xc28a97a  je short 0xC28A955   ; null buffer -> release entry only
        sub_c28a920_entry* const rbx =
            reinterpret_cast<sub_c28a920_entry*>(*reinterpret_cast<void**>(rdi));  // 0xc28a96b mov rbx,[rdi]
        if (rbx != nullptr) {                 // 0xc28a96e test rbx,rbx ; (je c28a962)
            std::uint8_t* const rcx = reinterpret_cast<std::uint8_t*>(rbx->buffer);  // 0xc28a973 mov rcx,[rbx+0x28]
            if (rcx == nullptr) {             // 0xc28a977 test rcx,rcx ; 0xc28a97a je c28a955
                // 0xc28a955  mov edx,0x40   (dead: sub_e935700->sub_392960 overwrites RDX)
                //   0xc28a95d  call 0xE935700   ; native::sub_e935700(rbx)
                native::sub_e935700(rbx);     // 0xc28a95d call 0xE935700
            } else {
                // 0xc28a97c..0xc28a9a5: buffer bounds and heap-bias check
                //   0xc28a97c  mov rdx,[rbx+0x38]   ; rdx = entry->bufferEnd
                //   0xc28a980  sub rdx,rcx          ; size = bufferEnd - buffer
                //   0xc28a983  cmp rdx,0x1000
                //   0xc28a98a  jb short 0xC28A950   ; small buffer -> free buffer
                //   0xc28a98c  mov rax,[rcx-8]      ; heap size header
                //   0xc28a990  add rcx,0xFFFFFFFFFFFFFFF8  ; rcx -= 8
                //   0xc28a994  sub rcx,rax          ; bias = (buffer - 8) - header
                //   0xc28a997  cmp rcx,0x20
                //   0xc28a99b  jae short 0xC28A9F1  ; bias >= 0x20 -> fail handler
                //   0xc28a99d  add rdx,0x27         ; dead
                //   0xc28a9a1  mov rcx,rax          ; rcx = header value
                //   0xc28a9a4  jmp short 0xC28A950  ; free header value
                std::uint8_t* const rdx = reinterpret_cast<std::uint8_t*>(rbx->bufferEnd);  // 0xc28a97c mov rdx,[rbx+0x38]
                std::uintptr_t const size =
                    reinterpret_cast<std::uintptr_t>(rdx) - reinterpret_cast<std::uintptr_t>(rcx);  // 0xc28a980 sub
                if (size < 0x1000) {          // 0xc28a983 cmp rdx,0x1000 ; 0xc28a98a jb c28a950
                    // 0xc28a950  call 0xE935700   ; native::sub_e935700(buffer)
                    native::sub_e935700(reinterpret_cast<void*>(rcx));  // 0xc28a950 call 0xE935700
                } else {
                    std::uintptr_t const rax =
                        *reinterpret_cast<std::uintptr_t*>(rcx - 8);  // 0xc28a98c mov rax,[rcx-8]
                    std::uintptr_t const bias =
                        reinterpret_cast<std::uintptr_t>(rcx) - 8 - rax;  // 0xc28a990 add rcx,-8 ; 0xc28a994 sub
                    if (bias >= 0x20) {       // 0xc28a997 cmp rcx,0x20 ; 0xc28a99b jae c28a9f1
                        sub_c28a920Fail();    // 0xc28a9f1 fail handler (noreturn)
                    }
                    // 0xc28a99d add rdx,0x27 (dead) ; 0xc28a9a1 mov rcx,rax
                    // 0xc28a950  call 0xE935700   ; native::sub_e935700(header value)
                    native::sub_e935700(reinterpret_cast<void*>(rax));  // 0xc28a950 call 0xE935700
                }
                // fall-through from 0xc28a950:
                //   0xc28a955  mov edx,0x40   (dead)
                //   0xc28a95d  call 0xE935700   ; native::sub_e935700(rbx)
                native::sub_e935700(rbx);     // 0xc28a95d call 0xE935700
            }
        }
        // 0xc28a962  add rdi,8
        rdi += 8;
        // 0xc28a966  cmp rdi,r14 ; 0xc28a969  je short c28a9a6  (loop condition re-checked by while)
    }
    // rdi == r14: array exhausted -> tail

    // 0xc28a9a6..0xc28a9cf: tail entry and total-size check
    //   0xc28a9a6  mov rdi,[rsi]        ; rdi = self->begin (re-read)
    //   0xc28a9a9  mov rdx,[rsi+0x10]   ; rdx = self->limit
    //   0xc28a9ad  sub rdx,rdi          ; size = limit - begin
    //   0xc28a9b0  cmp rdx,0x1000
    //   0xc28a9b7  jb short 0xC28A9D1   ; small total -> final free directly
    //   0xc28a9b9  mov rax,[rdi-8]      ; heap header at begin-8
    //   0xc28a9bd  add rdi,0xFFFFFFFFFFFFFFF8  ; rdi -= 8
    //   0xc28a9c1  sub rdi,rax          ; bias = (begin - 8) - header
    //   0xc28a9c4  cmp rdi,0x20
    //   0xc28a9c8  jae short 0xC28A9F1  ; bias >= 0x20 -> fail handler
    //   0xc28a9ca  add rdx,0x27         ; dead
    //   0xc28a9ce  mov rdi,rax          ; rdi = header value
    rdi = reinterpret_cast<std::uint8_t*>(self->begin);  // 0xc28a9a6 mov rdi,[rsi]
    std::uintptr_t const totalSize =
        reinterpret_cast<std::uintptr_t>(self->limit) - reinterpret_cast<std::uintptr_t>(rdi);  // 0xc28a9a9/0xc28a9ad
    if (!(totalSize < 0x1000)) {             // 0xc28a9b0 cmp ; 0xc28a9b7 jb c28a9d1
        std::uintptr_t const rax =
            *reinterpret_cast<std::uintptr_t*>(rdi - 8);  // 0xc28a9b9 mov rax,[rdi-8]
        std::uintptr_t const bias =
            reinterpret_cast<std::uintptr_t>(rdi) - 8 - rax;  // 0xc28a9bd/0xc28a9c1
        if (bias >= 0x20) {                  // 0xc28a9c4 cmp rdi,0x20 ; 0xc28a9c8 jae c28a9f1
            sub_c28a920Fail();               // 0xc28a9f1 fail handler (noreturn)
        }
        // 0xc28a9ca add rdx,0x27 (dead) ; 0xc28a9ce mov rdi,rax
        rdi = reinterpret_cast<std::uint8_t*>(rax);
    }
    // 0xc28a9d1..0xc28a9f0: final free, zero state, epilogue
    //   0xc28a9d1  mov rcx,rdi
    //   0xc28a9d4  call 0xE935700           ; native::sub_e935700(rdi)  -> return value
    //   0xc28a9d9  xorps xmm0,xmm0
    //   0xc28a9dc  movups [rsi],xmm0        ; self->begin = 0 ; self->end = 0
    //   0xc28a9df  mov qword ptr [rsi+0x10],0  ; self->limit = 0
    //   0xc28a9e7  add rsp,0x28
    //   0xc28a9eb  pop rbx
    //   0xc28a9ec  pop rdi
    //   0xc28a9ed  pop rsi
    //   0xc28a9ee  pop r14
    //   0xc28a9f0  ret
    uintptr_t const ret =
        (uintptr_t)native::sub_e935700(reinterpret_cast<void*>(rdi));  // 0xc28a9d4 call 0xE935700
    self->begin = nullptr;                   // 0xc28a9dc movups [rsi],xmm0 (writes begin+end)
    self->end = nullptr;
    self->limit = nullptr;                   // 0xc28a9df mov qword ptr [rsi+0x10],0
    return ret;                              // 0xc28a9e7..0xc28a9f0 epilogue
}

} // namespace native::helpers

static_assert(sizeof(void*) == 8,
              "sub_c28a920: x64 pointer-sized arguments (Microsoft x64 ABI)");

LIFT_FN(sub_c28a920, "sub_c28a920", 0xc28a920, ::native::helpers::sub_c28a920, nullptr);

#if 0
// Verbatim call instructions of [0xc28a920, 0xc28aa0b) (rdis dis 0xc28a920 0xeb),
// machine-checked by tools/sigs/verify_oc.py against the exe.
0xc28a950  call 0xE935700
0xc28a95d  call 0xE935700
0xc28a9d4  call 0xE935700
0xc28aa04  call qword ptr [0xF9A8C78]
#endif
