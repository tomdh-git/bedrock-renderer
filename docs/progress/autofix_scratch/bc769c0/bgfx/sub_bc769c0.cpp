// LIFT 0xbc769c0 size 0x22c 1.26.62.01 bgfx shutdown

#include "client/features/render/native/bgfx/sub_bc769c0.h"

#include <cstddef>
#include <cstdint>

#include "client/features/render/native/RewriteRegistry.h"
#include "client/features/render/native/Lift.h"

namespace native::bgfx {

static_assert(offsetof(Bc769c0State, ptr) == 0x08, "bc769c0: state layout asserted in the lifted body");

namespace {

// g = renderer object pointer read from data_12adf800:

//   0xbc769de  mov rcx,[0x12ADF800]   0xbc76a40  mov rcx,[0x12ADF800]

//   0xbc76b3c  mov rcx,[0x12ADF800]   0xbc76baf  mov rcx,[0x12ADF800]

static uint64_t* rendererObject() {
    return reinterpret_cast<uint64_t*>(
        *reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0x12ADF800));
}

// Each original indirect call is:

//   mov rax,[rcx]      ; rax = *g          (vtable pointer)

//   mov rax,[rax+8]    ; rax = g->vtable[1] (call target)

//   mov r10,[0xF99FFA0]; r10 = CFG thunk sub_eea6040 (vendor boundary via data slot 0xF99FFA0)

//   call r10           ; thunk: jmp rax  =>  tail call g->vtable[1] with rcx = g, rdx/r8/r9 as set up

// The thunk forwards every register and jumps to rax, so the net effect of each call site is an

// indirect call through g->vtable[1] with this = g, in the same order as the original.

//   0xbc76a14  mov rax,[r8]      0xbc76a17  mov rax,[rax+8]     0xbc76a1b  mov r10,[0xF99FFA0]     0xbc76a3c  call r10

//   0xbc76a6b  mov rax,[rcx]     0xbc76a6e  mov rax,[rax+8]     0xbc76a72  mov r10,[0xF99FFA0]     0xbc76a95  call r10

//   0xbc76b48  mov rax,[rcx]     0xbc76b4b  mov rax,[rax+8]     0xbc76b4f  mov r10,[0xF99FFA0]     0xbc76b6d  call r10

//   0xbc76bbb  mov rax,[rcx]     0xbc76bbe  mov rax,[rax+8]     0xbc76bc2  mov r10,[0xF99FFA0]     0xbc76be0  call r10

using Vtable1Fn = uintptr_t (*)(uint64_t* g /*rcx = this*/, uint64_t a2 /*rdx*/,
                                uint64_t size /*r8*/, uint64_t a4 /*r9*/);
static Vtable1Fn vtable1(uint64_t* g) {
    return reinterpret_cast<Vtable1Fn>(reinterpret_cast<uint64_t*>(*g)[1]);  // rax = [rax+8] = g->vtable[1]

}

// 16-byte zero store: movups [dst],xmm0 (0xbc76b80/0xbc76b84/0xbc76b88/0xbc76b8c).

static void zero16(uint64_t* dst) {
    *dst = 0;
    *(dst + 1) = 0;
}

} // namespace


void sub_bc769c0(Bc769c0State* self) {
    // 0xbc769c0..0xbc769fa: prologue, field loads and walk guards

    //   0xbc769c0  push rbp

    //   0xbc769c1  push rsi

    //   0xbc769c2  push rdi

    //   0xbc769c3  sub rsp,0x40

    //   0xbc769c7  lea rbp,[rsp+0x40]

    //   0xbc769cc  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE   ; stack sentinel at rsp+0x38, never read back

    //   0xbc769d4  mov rsi,rcx

    //   0xbc769d7  mov rdx,[rcx+8]       ; f8 = self->ptr (+0x08)

    //   0xbc769db  mov r8,[rdx]          ; *f8 = node->field00 (+0x00 of the node)

    //   0xbc769de  mov rcx,[0x12ADF800]  ; g

    //   0xbc769e5  test r8,r8            ; *f8 == 0 -> skip walk

    //   0xbc769e8  je short 0xBC76A50

    //   0xbc769ea  test rcx,rcx          ; g == 0 -> skip walk

    //   0xbc769ed  je short 0xBC76A50

    volatile uint64_t stackSentinel = 0xFFFFFFFFFFFFFFFEui64;
    (void)stackSentinel;
    uint64_t f8 = self->ptr;
    Bc769c0Node* node = reinterpret_cast<Bc769c0Node*>(f8);   // *f8 is dereferenced at 0xbc769db even when f8 == 0 (fail fast, no guard)

    uint64_t nodeField00 = *reinterpret_cast<uint64_t*>(node);
    uint64_t* g = rendererObject();
    if (nodeField00 != 0 && g != nullptr) {
        // 0xbc769ef..0xbc76a4a: walk the +0x8-linked list at *f8, calling g->vtable[1](g, 0, 0, 0)

        //   0xbc769ef  mov rax,r8

        //   0xbc769f2  mov r8,rcx

        //   0xbc769f5  mov rdx,rax

        //   0xbc769f8  jmp short 0xBC76A0B

        //   0xbc76a0b  mov rdi,[rdx+8]        ; next = node->next (+0x8)

        //   0xbc76a0f  test r8,r8             ; g != 0 (loop invariant)

        //   0xbc76a12  je short 0xBC76A00     ; 0xbc76a00  xor r8d,r8d  (unreachable: g != 0)

        //   0xbc76a14  mov rax,[r8]           ; rax = *g (vtable pointer)

        //   0xbc76a17  mov rax,[rax+8]        ; rax = g->vtable[1] (call target)

        //   0xbc76a1b  mov r10,[0xF99FFA0]    ; CFG thunk sub_eea6040

        //   0xbc76a22  mov dword ptr [rsp+0x28],0

        //   0xbc76a2a  mov qword ptr [rsp+0x20],0

        //   0xbc76a33  mov rcx,r8             ; rcx = g

        //   0xbc76a36  xor r8d,r8d            ; rdx = 0

        //   0xbc76a39  xor r9d,r9d            ; r8 = 0, r9 = 0

        //   0xbc76a3c  call r10               ; g->vtable[1](g, 0, 0, 0)

        //   0xbc76a3f  nop

        //   0xbc76a40  mov rcx,[0x12ADF800]   ; g = rendererObject() (every iteration)

        //   0xbc76a47  mov r8,rcx

        //   0xbc76a4a  jmp short 0xBC76A03    ; 0xbc76a03  mov rdx,rdi; test rdi,rdi; je -> exit walk

        for (;;) {
            Bc769c0Node* next = node->next;   // 0xbc76a0b  mov rdi,[rdx+8]

            if (g != nullptr) {               // 0xbc76a0f  test r8,r8  (always true here)

                (void)(*g);                   // 0xbc76a14  mov rax,[r8]

                Vtable1Fn fn = vtable1(g);    // 0xbc76a17  mov rax,[rax+8]

                fn(g, 0ui64, 0ui64, 0ui64);   // 0xbc76a1b..0xbc76a3c  call r10 -> jmp rax

            }
            node = next;                      // 0xbc76a03  mov rdx,rdi (= next)

            if (next == nullptr) break;       // 0xbc76a06  test rdi,rdi; 0xbc76a09  je short 0xBC76A4C

            g = rendererObject();             // 0xbc76a40  mov rcx,[0x12ADF800]

        }
    }

    // 0xbc76a4c..0xbc76a65: reload f8 = self->ptr; self->end = f8; compare f8 + 0x48 vs self->limit

    //   0xbc76a4c  mov rdx,[rsi+8]

    //   0xbc76a50  mov [rsi+0x10],rdx   ; self->end = f8

    //   0xbc76a54  lea rax,[rdx+0x48]

    //   0xbc76a58  cmp rax,[rsi+0x18]   ; f8 + 0x48 <= self->limit ?

    //   0xbc76a5c  jbe 0xBC76B06

    //   0xbc76a62  test rcx,rcx         ; g == 0 -> rdi = 0

    //   0xbc76a65  je 0xBC76B0B

    self->end = self->ptr;
    uint64_t* rdi;
    if (reinterpret_cast<uintptr_t>(self->ptr) + kBc769c0BlockSize <=
        reinterpret_cast<uintptr_t>(self->limit)) {
        // 0xbc76b06  mov rdi,rdx        ; reuse the existing block

        // 0xbc76b09  jmp short 0xBC76B7D

        rdi = reinterpret_cast<uint64_t*>(self->ptr);
    } else {
        // 0xbc76b0b  xor edi,edi        ; rdi = 0 when g == 0 (taken at 0xbc76a65)

        if (g == nullptr) {
            rdi = nullptr;
        } else {
            // 0xbc76a6b  mov rax,[rcx]        ; vtable probe (result not used as the target)

            // 0xbc76a6e  mov rax,[rax+8]

            // 0xbc76a72  mov r10,[0xF99FFA0]  ; CFG thunk sub_eea6040

            // 0xbc76a79  mov dword ptr [rsp+0x28],0

            // 0xbc76a81  mov qword ptr [rsp+0x20],0

            // 0xbc76a8a  mov r8d,0x48         ; size argument

            // 0xbc76a90  xor edx,edx          ; rdx = 0

            // 0xbc76a92  xor r9d,r9d          ; r9 = 0

            // 0xbc76a95  call r10             ; g->vtable[1](g, 0, 0x48, 0) -> rdi = rax

            // 0xbc76a98  nop

            // 0xbc76a99  mov rdi,rax

            (void)(*g);                       // 0xbc76a6b  mov rax,[rcx]

            (void)reinterpret_cast<uint64_t*>(*g)[1];  // 0xbc76a6e  mov rax,[rax+8]

            rdi = vtable1(g)(g, 0ui64, kBc769c0BlockSize, 0ui64);
        }
    }

    // 0xbc76a9c..0xbc76aa7: cur = self->ptr (reloaded); if cur == self->end skip the copy

    //   0xbc76a9c  mov rdx,[rsi+8]      ; cur = self->ptr (the callee may have moved it)

    //   0xbc76aa0  mov rax,[rsi+0x10]   ; rax = self->end (= f8)

    //   0xbc76aa4  cmp rdx,rax

    //   0xbc76aa7  je short 0xBC76B0D

    uint64_t* cur = self->ptr;
    if (cur != self->end) {
        // 0xbc76aa9..0xbc76b33: copy [cur, self->end) 8 bytes at a time into [rdi, ...)

        //   0xbc76aa9  mov r9,rax            ; r9 = self->end

        //   0xbc76aac  sub r9,rdx            ; r9 = self->end - cur

        //   0xbc76aaf  add r9,0xFFFFFFFFFFFFFFF8   ; r9 -= 8

        //   0xbc76ab3  cmp r9,0x38           ; r9 < 0x38 -> simple loop

        //   0xbc76ab7  jb short 0xBC76B14

        //   0xbc76ab9  mov rcx,rdi

        //   0xbc76abc  sub rcx,rdx           ; rcx = rdi - cur

        //   0xbc76abf  cmp rcx,0x20          ; rdi - cur < 0x20 -> simple loop

        //   0xbc76ac3  jb short 0xBC76B14

        //   0xbc76b14  mov rcx,rdi           ; simple loop: *d++ = *s++ until s == self->end

        //   0xbc76b17  mov r8,rdx

        //   0xbc76b1a  nop [rax+rax]

        //   0xbc76b20  mov rdx,[r8]

        //   0xbc76b23  mov [rcx],rdx

        //   0xbc76b26  add r8,8

        //   0xbc76b2a  add rcx,8

        //   0xbc76b2e  cmp r8,rax

        //   0xbc76b31  jne short 0xBC76B20

        //   0xbc76ac5  shr r9,3              ; SIMD path: r10 = round4(((r9 >> 3) + 1))

        //   0xbc76ac9  inc r9

        //   0xbc76acc  mov r10,r9

        //   0xbc76acf  and r10,0xFFFFFFFFFFFFFFFC

        //   0xbc76ad3  lea rcx,[rdi+r10*8]

        //   0xbc76ad7  lea r8,[rdx+r10*8]

        //   0xbc76adb  xor r11d,r11d

        //   0xbc76ade  xchg ax,ax

        //   0xbc76ae0  movups xmm0,[rdx+r11*8]

        //   0xbc76ae5  movups xmm1,[rdx+r11*8+0x10]

        //   0xbc76aeb  movups [rdi+r11*8],xmm0

        //   0xbc76af0  movups [rdi+r11*8+0x10],xmm1

        //   0xbc76af6  add r11,4

        //   0xbc76afa  cmp r10,r11

        //   0xbc76afd  jne short 0xBC76AE0

        //   0xbc76aff  cmp r9,r10

        //   0xbc76b02  jne short 0xBC76B20   ; remainder qword loop

        //   0xbc76b04  jmp short 0xBC76B33

        uintptr_t r9 =
            reinterpret_cast<uintptr_t>(self->end) - reinterpret_cast<uintptr_t>(cur) - 8ui64;
        if (r9 >= 0x38ui64 &&
            reinterpret_cast<uintptr_t>(rdi) - reinterpret_cast<uintptr_t>(cur) >= 0x20ui64) {
            uintptr_t r10 = ((r9 >> 3) + 1ui64) & ~0x3ui64;
            for (uintptr_t r11 = 0; r11 != r10; r11 += 4ui64) {
                uintptr_t s = reinterpret_cast<uintptr_t>(cur) + r11 * 8ui64;
                uint64_t lo = *reinterpret_cast<const uint64_t*>(s);                              // 0xbc76ae0  movups xmm0,[rdx+r11*8]

                uint64_t hi = *reinterpret_cast<const uint64_t*>(s + 0x10ui64);                     // 0xbc76ae5  movups xmm1,[rdx+r11*8+0x10]

                *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(rdi) + r11 * 8ui64) = lo;   // 0xbc76aeb  movups [rdi+r11*8],xmm0

                *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(rdi) + r11 * 8ui64 +
                                              0x10ui64) = hi;                                        // 0xbc76af0  movups [rdi+r11*8+0x10],xmm1

            }
            if (r9 != r10) {
                uintptr_t s = reinterpret_cast<uintptr_t>(cur) + r10 * 8ui64;
                uintptr_t d = reinterpret_cast<uintptr_t>(rdi) + r10 * 8ui64;
                while (s != reinterpret_cast<uintptr_t>(self->end)) {                             // 0xbc76b20..0xbc76b31

                    *reinterpret_cast<uint64_t*>(d) = *reinterpret_cast<const uint64_t*>(s);
                    s += 8ui64;
                    d += 8ui64;
                }
            }
        } else {
            uintptr_t s = reinterpret_cast<uintptr_t>(cur);
            uintptr_t d = reinterpret_cast<uintptr_t>(rdi);
            while (s != reinterpret_cast<uintptr_t>(self->end)) {                                 // 0xbc76b14..0xbc76b31

                *reinterpret_cast<uint64_t*>(d) = *reinterpret_cast<const uint64_t*>(s);
                s += 8ui64;
                d += 8ui64;
            }
        }
    }

    // 0xbc76b33..0xbc76b70: cur = self->ptr (reloaded); if cur != 0 and g != 0: probe + call

    //   0xbc76b33  mov rdx,[rsi+8]

    //   0xbc76b37  test rdx,rdx

    //   0xbc76b3a  je short 0xBC76B71

    //   0xbc76b3c  mov rcx,[0x12ADF800]

    //   0xbc76b43  test rcx,rcx

    //   0xbc76b46  je short 0xBC76B71

    //   0xbc76b48  mov rax,[rcx]

    //   0xbc76b4b  mov rax,[rax+8]

    //   0xbc76b4f  mov r10,[0xF99FFA0]

    //   0xbc76b56  mov dword ptr [rsp+0x28],0

    //   0xbc76b5e  mov qword ptr [rsp+0x20],0

    //   0xbc76b67  xor r8d,r8d

    //   0xbc76b6a  xor r9d,r9d

    //   0xbc76b6d  call r10            ; g->vtable[1](g, 0, 0, 0)

    //   0xbc76b70  nop

    cur = self->ptr;
    if (cur != nullptr) {
        g = rendererObject();
        if (g != nullptr) {
            (void)(*g);                                    // 0xbc76b48  mov rax,[rcx]

            (void)reinterpret_cast<uint64_t*>(*g)[1];      // 0xbc76b4b  mov rax,[rax+8]

            vtable1(g)(g, 0ui64, 0ui64, 0ui64);            // 0xbc76b4f..0xbc76b6d  call r10 -> jmp rax

        }
    }

    // 0xbc76b71..0xbc76ba3: reset self around the block

    //   0xbc76b71  mov [rsi+8],rdi          ; self->ptr = rdi

    //   0xbc76b75  lea rax,[rdi+0x48]

    //   0xbc76b79  mov [rsi+0x18],rax       ; self->limit = rdi + 0x48

    //   0xbc76b7d  xorps xmm0,xmm0

    //   0xbc76b80  movups [rdi+0x30],xmm0   ; zero [rdi, rdi+0x48): 16-byte stores at +0x00/+0x10/+0x20/+0x30

    //   0xbc76b84  movups [rdi+0x20],xmm0

    //   0xbc76b88  movups [rdi+0x10],xmm0

    //   0xbc76b8c  movups [rdi],xmm0

    //   0xbc76b8f  mov qword ptr [rdi+0x40],0

    //   0xbc76b97  mov rdx,[rsi+8]          ; rdx = self->ptr (= rdi)

    //   0xbc76b9b  lea rax,[rdx+0x48]

    //   0xbc76b9f  mov [rsi+0x10],rax       ; self->end = self->ptr + 0x48

    //   0xbc76ba3  mov qword ptr [rsi],0    ; self->count = 0

    self->ptr = rdi;
    self->limit = reinterpret_cast<uint64_t>(
        reinterpret_cast<uint8_t*>(rdi) + kBc769c0BlockSize);  // writes through rdi == 0 fail fast, like the original

    zero16(rdi);
    zero16(reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(rdi) + 0x10ui64));
    zero16(reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(rdi) + 0x20ui64));
    zero16(reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(rdi) + 0x30ui64));
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(rdi) + 0x40ui64) = 0;
    self->end = reinterpret_cast<uint64_t>(self->ptr) + kBc769c0BlockSize;
    self->count = 0;

    // 0xbc76baa..0xbc76be0: if self->ptr != 0 and g != 0: probe + call g->vtable[1](g, 0, 0, 0)

    //   0xbc76baa  test rdx,rdx       ; rdx = self->ptr

    //   0xbc76bad  je short 0xBC76BE4

    //   0xbc76baf  mov rcx,[0x12ADF800]

    //   0xbc76bb6  test rcx,rcx

    //   0xbc76bb9  je short 0xBC76BE4

    //   0xbc76bbb  mov rax,[rcx]

    //   0xbc76bbe  mov rax,[rax+8]

    //   0xbc76bc2  mov r10,[0xF99FFA0]

    //   0xbc76bc9  mov dword ptr [rsp+0x28],0

    //   0xbc76bd1  mov qword ptr [rsp+0x20],0

    //   0xbc76bda  xor r8d,r8d

    //   0xbc76bdd  xor r9d,r9d

    //   0xbc76be0  call r10           ; g->vtable[1](g, 0, 0, 0) -> jmp rax

    //   0xbc76be3  nop

    // 0xbc76be4..0xbc76beb: epilogue

    //   0xbc76be4  add rsp,0x40

    //   0xbc76be8  pop rdi

    //   0xbc76be9  pop rsi

    //   0xbc76bea  pop rbp

    //   0xbc76beb  ret

    if (self->ptr != nullptr) {
        g = rendererObject();
        if (g != nullptr) {
            (void)(*g);
            (void)reinterpret_cast<uint64_t*>(*g)[1];
            vtable1(g)(g, 0ui64, 0ui64, 0ui64);
        }
    }
}

LIFT_FN(sub_bc769c0, "bgfx shutdown", 0xbc769c0, sub_bc769c0, nullptr);

} // namespace native::bgfx

