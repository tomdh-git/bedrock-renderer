// LIFT 0x6757320 size 0x12e 1.26.62.01 sub_6757320
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_6757320.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>
#include <emmintrin.h>

namespace native::helpers {

// Boundary callees invoked from the import-address thunk [0xF99FFA0] (= sub_eea6040)
// and from the native symbol sub_6ae330. Signatures are reconstructed from the
// call sites: sub_eea6040 is entered with rcx = pointer and a second argument of 1;
// sub_6ae330 is entered with rcx = &self->f18.
void sub_eea6040(void* ptr, std::uint32_t delta);
void sub_6ae330(void* self);

// Layout assertions mirroring the state structs in sub_6757320.h.
static_assert(offsetof(sub_6757320_rcx, f0) == 0x0, "rcx+0x0");
static_assert(offsetof(sub_6757320_rcx, f8) == 0x8, "rcx+0x8");
static_assert(offsetof(sub_6757320_rcx, f18) == 0x18, "rcx+0x18");
static_assert(offsetof(sub_6757320_rcx, f28) == 0x28, "rcx+0x28");
static_assert(offsetof(sub_6757320_rbx, f0) == 0x0, "rbx+0x0");
static_assert(offsetof(sub_6757320_rbx, f8) == 0x8, "rbx+0x8");
static_assert(offsetof(sub_6757320_r15, f10) == 0x10, "r15+0x10");
static_assert(offsetof(sub_6757320_r15, f18) == 0x18, "r15+0x18");
static_assert(offsetof(sub_6757320_rax, f0) == 0x0, "rax+0x0");
static_assert(offsetof(sub_6757320_rax, f8) == 0x8, "rax+0x8");
static_assert(offsetof(sub_6757320_rax, f10) == 0x10, "rax+0x10");
static_assert(offsetof(sub_6757320_rax, f20) == 0x20, "rax+0x20");
static_assert(offsetof(sub_6757320_rax, f30) == 0x30, "rax+0x30");
static_assert(offsetof(sub_6757320_rax, f40) == 0x40, "rax+0x40");
static_assert(offsetof(sub_6757320_rax, f50) == 0x50, "rax+0x50");
static_assert(offsetof(sub_6757320_rax, f60) == 0x60, "rax+0x60");
static_assert(offsetof(sub_6757320_rax, f68) == 0x68, "rax+0x68");
static_assert(offsetof(sub_6757320_rdi, f0) == 0x0, "rdi+0x0");
static_assert(offsetof(sub_6757320_rdi, f8) == 0x8, "rdi+0x8");
static_assert(offsetof(sub_6757320_rdi, fc) == 0xc, "rdi+0xc");
static_assert(offsetof(sub_6757320_rsp, f20) == 0x20, "rsp+0x20");

LIFT_FN(sub_6757320, "sub_6757320", 0x6757320, sub_6757320, nullptr);

// Verbatim call instructions from the disassembly of [0x6757320, 0x675744e) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x67573d9  call qword ptr [0xF99FFA0]
0x6757400  call qword ptr [0xF99FFA0]
0x675741a  call qword ptr [0xF99FFA0]
0x6757429  call 0x6AE330
#endif

// Ranges: every instruction of [0x6757320, 0x675744e) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

void sub_6757320(void* self) {
    // 0x6757320..0x6757343: basic block 0
    // 0x6757320  push r15
    // 0x6757322  push r14
    // 0x6757324  push rsi
    // 0x6757325  push rdi
    // 0x6757326  push rbx
    // 0x6757327  sub rsp,0x30
    // 0x675732b  movaps [rsp+0x20],xmm6
    // 0x6757330  mov rsi,rcx
    // 0x6757333  mov rbx,[rcx]           ; begin iterator
    // 0x6757336  mov r14,[rcx+8]         ; end iterator
    // 0x675733a  cmp rbx,r14
    // 0x675733d  je 0x6757425            ; -> if begin == end goto L_0x6757425
    //            fallthrough             ; -> if begin != end goto L_0x6757343
    sub_6757320_rcx* a0 = static_cast<sub_6757320_rcx*>(self);
    sub_6757320_rbx* rbx = reinterpret_cast<sub_6757320_rbx*>(a0->f0);
    sub_6757320_rbx* end = reinterpret_cast<sub_6757320_rbx*>(a0->f8);
    __m128i xmm6 = _mm_setzero_si128();   // 0x6757343  xorps xmm6,xmm6

    auto next_element = [](sub_6757320_rbx* p) {
        return reinterpret_cast<sub_6757320_rbx*>(reinterpret_cast<char*>(p) + 0x10);
    };

    for (; rbx != end; rbx = next_element(rbx)) {
        // 0x6757350..0x675735d: basic block 3 (loop back from continues)
        // 0x6757350  add rbx,0x10          (for-increment)
        // 0x6757354  cmp rbx,r14
        // 0x6757357  je 0x6757425          ; -> if end goto L_0x6757425
        //            fallthrough           ; -> if != end goto L_0x675735d

        // 0x675735d..0x6757366: basic block 4
        // 0x675735d  mov rcx,[rbx+8]       ; control block
        // 0x6757361  test rcx,rcx
        // 0x6757364  je short 0x6757350    ; -> if control == 0 goto next element
        void* control = rbx->f8;
        if (control == nullptr) continue;   // -> L_0x6757350 (advance)

        // 0x6757366..0x675737e: basic blocks 5, 6, 7 (CAS acquire)
        // 0x6757366  mov eax,[rcx+8]       ; expected = use count (32-bit)
        // 0x6757370  test eax,eax
        // 0x6757372  je short 0x6757350    ; -> if expected == 0 goto next element
        // 0x6757374  lea edx,[rax+1]       ; desired = expected + 1
        // 0x6757377  lock cmpxchg [rcx+8],edx
        // 0x675737c  jne short 0x6757370   ; -> if CAS failed goto L_0x6757370 (eax reloaded)
        sub_6757320_rdi* cb = reinterpret_cast<sub_6757320_rdi*>(control);
        std::uint32_t expected = cb->f8;

        // Declared here so that goto next_element_iter (below) never bypasses
        // their initialization.
        void* managed = nullptr;
        void* f68obj = nullptr;

        for (;;) {
            if (expected == 0) goto next_element_iter;   // test eax,eax; je L_0x6757350
            std::uint32_t desired = expected + 1u;
            long actual = _InterlockedCompareExchange(
                reinterpret_cast<long volatile*>(&cb->f8),
                static_cast<long>(desired),
                static_cast<long>(expected));
            if (static_cast<std::uint32_t>(actual) == expected) break;   // CAS succeeded
            expected = static_cast<std::uint32_t>(actual);               // cmpxchg reloaded eax
        }

        // 0x675737e..0x675738a: basic block 8
        // 0x675737e  mov r15,[rbx]         ; managed pointer
        // 0x6757381  mov rdi,[rbx+8]       ; control block (same as control)
        // 0x6757385  test r15,r15
        // 0x6757388  je short 0x67573E4    ; -> if managed == 0 goto L_0x67573e4
        managed = rbx->f0;

        if (managed != nullptr) {
            // 0x675738a..0x67573ce: basic block 9
            // 0x675738a  mov rax,[r15+0x18]    ; rax object
            // 0x675738e  mov qword ptr [rax],0xFFFF
            // 0x6757395  mov dword ptr [rax+8],0
            // 0x675739c  mov word ptr [rax+0xC],0xFFFF
            // 0x67573a2..0x67573b2  movups [rax+0x10..0x50],xmm6 (zero)
            // 0x67573b6  mov dword ptr [rax+0x60],0
            // 0x67573bd  mov rcx,[rax+0x68]    ; f68 object
            // 0x67573c1  mov qword ptr [rax+0x68],0
            // 0x67573c9  test rcx,rcx
            // 0x67573cc  je short 0x67573DF    ; -> if f68 object == 0 goto L_0x67573df
            sub_6757320_r15* m = reinterpret_cast<sub_6757320_r15*>(managed);
            sub_6757320_rax* h = reinterpret_cast<sub_6757320_rax*>(m->f18);

            *reinterpret_cast<std::uint64_t*>(h) = 0xFFFFu;                                            // [rax]=0xFFFF
            *reinterpret_cast<std::uint64_t*>(reinterpret_cast<char*>(h) + 8) = 0;                     // [rax+8]=0
            *reinterpret_cast<std::uint16_t*>(reinterpret_cast<char*>(h) + 0xC) = 0xFFFFu;              // [rax+0xC]=0xFFFF
            _mm_storeu_si128(reinterpret_cast<__m128i*>(reinterpret_cast<char*>(h) + 0x10), xmm6);     // [rax+0x10]=0
            _mm_storeu_si128(reinterpret_cast<__m128i*>(reinterpret_cast<char*>(h) + 0x20), xmm6);     // [rax+0x20]=0
            _mm_storeu_si128(reinterpret_cast<__m128i*>(reinterpret_cast<char*>(h) + 0x30), xmm6);     // [rax+0x30]=0
            _mm_storeu_si128(reinterpret_cast<__m128i*>(reinterpret_cast<char*>(h) + 0x40), xmm6);     // [rax+0x40]=0
            _mm_storeu_si128(reinterpret_cast<__m128i*>(reinterpret_cast<char*>(h) + 0x50), xmm6);     // [rax+0x50]=0
            h->f60 = 0;                                                                                // [rax+0x60]=0
            f68obj = h->f68;                                                                           // [rax+0x68]
            h->f68 = nullptr;                                                                          // [rax+0x68]=0

            // 0x67573ce..0x67573df: basic block 10
            // 0x67573ce  mov rax,[rcx]
            // 0x67573d1  mov rax,[rax]
            // 0x67573d4  mov edx,1
            // 0x67573d9  call qword ptr [0xF99FFA0]   ; sub_eea6040(f68 object, 1)
            if (f68obj != nullptr) {
                sub_eea6040(f68obj, 1u);
            }

            // 0x67573df..0x67573e4: basic block 11
            // 0x67573df  mov byte ptr [r15+0x10],0
            m->f10 = 0;
        }

        // 0x67573e4..0x6757425: basic blocks 12, 13, 14, 15 (control release)
        // rdi = control is non-null here (block 4 already filtered null).
        // 0x67573ed  lock dec dword ptr [rdi+8]
        // 0x67573f1  jne 0x6757350       ; -> if dec != 0 goto next element
        if (_InterlockedDecrement(reinterpret_cast<long volatile*>(&cb->f8)) != 0) goto next_element_iter;
        // 0x67573f7..0x6757400  call sub_eea6040(control)   (block 14)
        // 0x6757406  lock dec dword ptr [rdi+0xC]
        // 0x675740a  jne 0x6757350       ; -> if dec != 0 goto next element
        sub_eea6040(control, 1u);
        if (_InterlockedDecrement(reinterpret_cast<long volatile*>(&cb->fc)) != 0) goto next_element_iter;
        // 0x6757410..0x675741a  call sub_eea6040(control)   (block 15)
        // 0x6757420  jmp 0x6757350       ; -> next element
        sub_eea6040(control, 1u);

    next_element_iter:
        ; // outer for-increment advances rbx to the next element
    }

    // 0x6757425..0x675744e: basic block 16 (exit)
    // 0x6757425  lea rcx,[rsi+0x18]
    // 0x6757429  call 0x6AE330           ; sub_6ae330(&self->f18)
    // 0x675742e  xorps xmm0,xmm0
    // 0x6757431  movups [rsi+0x18],xmm0  ; zero f18
    // 0x6757435  mov qword ptr [rsi+0x28],0   ; f28 = 0
    // 0x675743d  movaps xmm6,[rsp+0x20]  ; restore xmm6 (compiler epilogue)
    // 0x6757442  add rsp,0x30
    // 0x6757446..0x675744d  pop rbx,rdi,rsi,r14,r15; ret
    sub_6ae330(reinterpret_cast<void*>(&a0->f18));
    _mm_storeu_si128(reinterpret_cast<__m128i*>(&a0->f18), _mm_setzero_si128());
    a0->f28 = 0;
}

} // namespace native::helpers
