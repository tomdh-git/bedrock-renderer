// LIFT 0x675b350 size 0xfb 1.26.62.01 sub_675b350
#include "client/features/render/native/helpers/sub_675b350.h"
#include "client/features/render/native/Lift.h"

#include <cstddef>
#include <cstdint>
#include <emmintrin.h>
#include <intrin.h>

static_assert(offsetof(native::helpers::sub_675b350_self, self2) == 0x8, "675b350 self+0x8 self2 field");
static_assert(offsetof(native::helpers::sub_675b350_self, count) == 0x10, "675b350 self+0x10 count field");
static_assert(offsetof(native::helpers::sub_675b350_self, start) == 0x18, "675b350 self+0x18 start field");
static_assert(offsetof(native::helpers::sub_675b350_self, end) == 0x20, "675b350 self+0x20 end field");
static_assert(offsetof(native::helpers::sub_675b350_chunk, buf) == 0xe8, "675b350 chunk+0xe8 buf field");
static_assert(offsetof(native::helpers::sub_675b350_chunk, limit) == 0xf8, "675b350 chunk+0xf8 limit field");
static_assert(offsetof(native::helpers::sub_675b350_chunk, flag) == 0x100, "675b350 chunk+0x100 flag field");
static_assert(offsetof(native::helpers::sub_675b350_r14, buf) == 0x0, "675b350 r14+0x0 buf field");
static_assert(offsetof(native::helpers::sub_675b350_r14, limit) == 0x10, "675b350 r14+0x10 limit field");
static_assert(offsetof(native::helpers::sub_675b350_rsp, f20) == 0x20, "675b350 rsp+0x20 f20 field");
static_assert(offsetof(native::helpers::sub_675b350_rsp, f30) == 0x30, "675b350 rsp+0x30 f30 field");

namespace native {
// sub_e935700 (0xe935700, lift set, already lifted in helpers/sub_e935700.cpp):
// tail jump to sub_392960; argument forwarded in RCX, result in RAX.
void* sub_e935700(void* a0);
} // namespace native

namespace native::helpers {

namespace {

std::uint8_t* image_base() {
    return reinterpret_cast<std::uint8_t*>(RewriteRegistry::imageBase());
}
inline void* slot_f9a8c78() {
    // Data slot 0xF9A8C78: fail-handler function pointer, read at call time,
    // exactly as `call qword ptr [0xF9A8C78]` does.
    return *reinterpret_cast<void** volatile*>(image_base() + 0xF9A8C78);
}

} // namespace

void* sub_675b350(void* self) {
    // 0x675b35e  mov rsi,rcx            ; rsi = self (a0) for the whole function
    // 0x675b361  mov rcx,[rcx+8]        ; self2 = self->self2
    // 0x675b365  test rcx,rcx
    // 0x675b368  je 0x675B422           ; if self2 == 0: block 15 (ret)
    void* const self2 = *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(self) + 0x8);
    std::uint8_t* const start = *reinterpret_cast<std::uint8_t**>(
        reinterpret_cast<std::uint8_t*>(self) + 0x18);
    std::uint8_t* const end = *reinterpret_cast<std::uint8_t**>(
        reinterpret_cast<std::uint8_t*>(self) + 0x20);
    std::uint8_t* rdi = start;
    void** r14 = nullptr;
    void* rcx = nullptr;
    std::uintptr_t rax = 0;
    std::uintptr_t rdx = 0;
    __m128i xmm6 = _mm_setzero_si128();

    if (self2 == nullptr) goto L_0x675b422;
    if (start == end) goto L_0x675b3e6;
    goto L_0x675b39d;

    // 0x675b391..0x675b39d: block 4 (advance chunk by 0x118)
L_0x675b391:
    // 0x675b391  add rdi,0x118
    // 0x675b398  cmp rdi,rbx
    // 0x675b39b  je short 0x675B3E2     ; if rdi == end: block 10
    rdi += 0x118;
    if (rdi == end) goto L_0x675b3e2;
    goto L_0x675b39d;

    // 0x675b39d..0x675b3a6: block 5 (check chunk flag)
L_0x675b39d:
    // 0x675b39d  cmp byte ptr [rdi+0x100],1
    // 0x675b3a4  jne short 0x675B391    ; if flag != 1: block 4
    if (*reinterpret_cast<std::uint8_t*>(rdi + 0x100) != 1) goto L_0x675b391;
    goto L_0x675b3a6;

    // 0x675b3a6..0x675b3b5: block 6 (buf = [rdi+0xe8])
L_0x675b3a6:
    // 0x675b3a6  lea r14,[rdi+0xE8]
    // 0x675b3ad  mov rcx,[r14]          ; rcx = buf = *r14
    // 0x675b3b0  test rcx,rcx
    // 0x675b3b3  je short 0x675B391     ; if buf == 0: block 4
    r14 = reinterpret_cast<void**>(rdi + 0xE8);
    rcx = *r14;
    if (rcx == nullptr) goto L_0x675b391;
    goto L_0x675b3b5;

    // 0x675b3b5..0x675b3c8: block 7 (limit = [rdi+0xf8], check size)
L_0x675b3b5:
    // 0x675b3b5  mov rdx,[rdi+0xF8]     ; rdx = limit
    // 0x675b3bc  sub rdx,rcx            ; rdx = limit - buf
    // 0x675b3bf  cmp rdx,0x1000
    // 0x675b3c6  jb short 0x675B380     ; if rdx <u 0x1000: block 3
    rdx = *reinterpret_cast<std::uintptr_t*>(rdi + 0xF8);
    rdx -= reinterpret_cast<std::uintptr_t>(rcx);
    if (rdx < 0x1000u) goto L_0x675b380;
    goto L_0x675b3c8;

    // 0x675b380..0x675b391: block 3 (sub_e935700(buf), zero buf[0..16) and buf[0x10..0x18))
L_0x675b380:
    // 0x675b380  call 0xE935700         ; sub_e935700(rcx) ; result ignored
    // 0x675b385  movups [r14],xmm6      ; *r14 = xmm6  (16 zero bytes -> buf = 0)
    // 0x675b389  mov qword ptr [r14+0x10],0  ; r14[1] = 0  (-> buf+0x10 = 0)
    native::sub_e935700(rcx);
    _mm_storeu_si128(reinterpret_cast<__m128i*>(r14), xmm6);
    r14[1] = nullptr;
    goto L_0x675b391;

    // 0x675b3c8..0x675b3d9: block 8 (metadata probe on buf)
L_0x675b3c8:
    // 0x675b3c8  mov rax,[rcx-8]
    // 0x675b3cc  add rcx,0xFFFFFFFFFFFFFFF8   ; rcx -= 8
    // 0x675b3d0  sub rcx,rax                  ; rcx = (rcx-8) - rax
    // 0x675b3d3  cmp rcx,0x20
    // 0x675b3d7  jae short 0x675B431          ; if probe >=u 0x20: block 16 (fail, noreturn)
    rax = *reinterpret_cast<std::uintptr_t*>(
        reinterpret_cast<std::uint8_t*>(rcx) - 8);
    rcx = reinterpret_cast<void*>(
        reinterpret_cast<std::uintptr_t>(rcx) - 8 - rax);
    if (reinterpret_cast<std::uintptr_t>(rcx) >= 0x20u) goto L_0x675b431;
    goto L_0x675b3d9;

    // 0x675b3d9..0x675b3e2: block 9 (then block 3)
L_0x675b3d9:
    // 0x675b3d9  add rdx,0x27             ; rdx += 0x27
    // 0x675b3dd  mov rcx,rax              ; rcx = rax
    // 0x675b3e0  jmp short 0x675B380      ; block 3
    rdx += 0x27;
    rcx = reinterpret_cast<void*>(rax);
    goto L_0x675b380;

    // 0x675b3e2..0x675b3e6: block 10 (reload self2)
L_0x675b3e2:
    // 0x675b3e2  mov rcx,[rsi+8]          ; rcx = self2
    rcx = self2;
    goto L_0x675b3e6;

    // 0x675b3e6..0x675b3f7: block 11 (count * 0x118 vs 0x1000)
L_0x675b3e6:
    // 0x675b3e6  imul rdx,[rsi+0x10],0x118   ; rdx = count * 0x118
    // 0x675b3ee  cmp rdx,0x1000
    // 0x675b3f5  jb short 0x675B40F          ; if rdx <u 0x1000: block 14 (tail call)
    rdx = *reinterpret_cast<std::uint64_t*>(
        reinterpret_cast<std::uint8_t*>(self) + 0x10);
    rdx *= 0x118;
    if (rdx < 0x1000u) goto L_0x675b40f;
    goto L_0x675b3f7;

    // 0x675b3f7..0x675b408: block 12 (metadata probe on self2)
L_0x675b3f7:
    // 0x675b3f7  mov rax,[rcx-8]          ; rax = self2[-8]  (rcx == self2 here)
    // 0x675b3fb  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x675b3ff  sub rcx,rax              ; rcx = (rcx-8) - rax
    // 0x675b402  cmp rcx,0x20
    // 0x675b406  jae short 0x675B422      ; if probe >=u 0x20: block 15 (ret)
    rax = *reinterpret_cast<std::uintptr_t*>(
        reinterpret_cast<std::uint8_t*>(rcx) - 8);
    rcx = reinterpret_cast<void*>(
        reinterpret_cast<std::uintptr_t>(rcx) - 8 - rax);
    if (reinterpret_cast<std::uintptr_t>(rcx) >= 0x20u) goto L_0x675b422;
    goto L_0x675b408;

    // 0x675b408..0x675b40f: block 13 (then block 14)
L_0x675b408:
    // 0x675b408  add rdx,0x27
    // 0x675b40c  mov rcx,rax
    rdx += 0x27;
    rcx = reinterpret_cast<void*>(rax);
    goto L_0x675b40f;

    // 0x675b40f..0x675b422: block 14 (tail call sub_e935700)
L_0x675b40f:
    // 0x675b41d  jmp 0xE935700            ; tail call sub_e935700(rcx)
    return native::sub_e935700(rcx);

    // 0x675b422..0x675b431: block 15 (ret)
L_0x675b422:
    // 0x675b430  ret                      ; return rax
    return reinterpret_cast<void*>(rax);

    // 0x675b431..0x675b44b: block 16 (noreturn fail handler)
L_0x675b431:
    // 0x675b431  mov qword ptr [rsp+0x20],0
    // 0x675b43a  xor ecx,ecx
    // 0x675b43c  xor edx,edx
    // 0x675b43e  xor r8d,r8d
    // 0x675b441  xor r9d,r9d
    // 0x675b444  call qword ptr [0xF9A8C78]   ; fail(0,0,0,0)
    // 0x675b44a  int3
    using FailFn = void (__cdecl*)(void*, void*, void*, void*);
    reinterpret_cast<FailFn>(slot_f9a8c78())(nullptr, nullptr, nullptr, nullptr);
    __assume(false);   // noreturn; original traps with int3
}

// Verbatim instruction quotes from the disassembly of [0x675b350, 0x675b44b)
// (rdis `dis` output), for verify_oc coverage.
#if 0
0x675b350  push r14
0x675b352  push rsi
0x675b353  push rdi
0x675b354  push rbx
0x675b355  sub rsp,0x48
0x675b359  movaps [rsp+0x30],xmm6
0x675b35e  mov rsi,rcx
0x675b361  mov rcx,[rcx+8]
0x675b365  test rcx,rcx
0x675b368  je 0x675B422
0x675b36e  mov rdi,[rsi+0x18]
0x675b372  mov rbx,[rsi+0x20]
0x675b376  cmp rdi,rbx
0x675b379  je short 0x675B3E6
0x675b37b  xorps xmm6,xmm6
0x675b37e  jmp short 0x675B39D
0x675b380  call 0xE935700
0x675b385  movups [r14],xmm6
0x675b389  mov qword ptr [r14+0x10],0
0x675b391  add rdi,0x118
0x675b398  cmp rdi,rbx
0x675b39b  je short 0x675B3E2
0x675b39d  cmp byte ptr [rdi+0x100],1
0x675b3a4  jne short 0x675B391
0x675b3a6  lea r14,[rdi+0xE8]
0x675b3ad  mov rcx,[r14]
0x675b3b0  test rcx,rcx
0x675b3b3  je short 0x675B391
0x675b3b5  mov rdx,[rdi+0xF8]
0x675b3bc  sub rdx,rcx
0x675b3bf  cmp rdx,0x1000
0x675b3c6  jb short 0x675B380
0x675b3c8  mov rax,[rcx-8]
0x675b3cc  add rcx,0xFFFFFFFFFFFFFFF8
0x675b3d0  sub rcx,rax
0x675b3d3  cmp rcx,0x20
0x675b3d7  jae short 0x675B431
0x675b3d9  add rdx,0x27
0x675b3dd  mov rcx,rax
0x675b3e0  jmp short 0x675B380
0x675b3e2  mov rcx,[rsi+8]
0x675b3e6  imul rdx,[rsi+0x10],0x118
0x675b3ee  cmp rdx,0x1000
0x675b3f5  jb short 0x675B40F
0x675b3f7  mov rax,[rcx-8]
0x675b3fb  add rcx,0xFFFFFFFFFFFFFFF8
0x675b3ff  sub rcx,rax
0x675b402  cmp rcx,0x20
0x675b406  jae short 0x675B431
0x675b408  add rdx,0x27
0x675b40c  mov rcx,rax
0x675b40f  movaps xmm6,[rsp+0x30]
0x675b414  add rsp,0x48
0x675b418  pop rbx
0x675b419  pop rdi
0x675b41a  pop rsi
0x675b41b  pop r14
0x675b41d  jmp 0xE935700
0x675b422  movaps xmm6,[rsp+0x30]
0x675b427  add rsp,0x48
0x675b42b  pop rbx
0x675b42c  pop rdi
0x675b42d  pop rsi
0x675b42e  pop r14
0x675b430  ret
0x675b431  mov qword ptr [rsp+0x20],0
0x675b43a  xor ecx,ecx
0x675b43c  xor edx,edx
0x675b43e  xor r8d,r8d
0x675b441  xor r9d,r9d
0x675b444  call qword ptr [0xF9A8C78]
0x675b44a  int3
#endif

LIFT_FN(sub_675b350, "sub_675b350", 0x675b350, sub_675b350, nullptr);

} // namespace native::helpers
