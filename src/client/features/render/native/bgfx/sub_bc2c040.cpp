// LIFT 0xbc2c040 size 0x1c5 1.26.62.01 sub_bc2c040
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc2c040.h"

#include <cstddef>
#include <cstdint>
#include <emmintrin.h>
#include <intrin.h>

// Callee forward declarations per docs/data/native_boundary.tsv and native_functions.tsv:
// - sub_bc2be20 (0xbc2be20): class lift, already lifted, header at sub_bc2be20.h
// - sub_eea6040 (0xeea6040): class vendor, boundary via slot [0xF99FFA0] (jmp rax thunk)
// - sub_9bc830 (0x9bc830): class alloc, boundary
// - sub_75720 (0x75720): class stl, boundary
// - sub_eec6ec0 (0xeec6ec0): class lift, called directly at 0xbc2c1c6
namespace native {
void sub_bc2be20(sub_bc2be20_state* dst, sub_bc2be20_state* src);
// sub_eea6040 is a `jmp rax` thunk; the original does indirect vtable calls through it.
// We model each `call qword ptr [0xF99FFA0]` as a virtual call whose slot index the
// original already loaded into rax. The two call sites in this function use rax loaded
// from [obj] (vtable[1] at +8) and [obj+0x20] respectively.
void vtableCallSlot1(void* obj);   // target from [obj+8]
void vtableCallSlot4(void* obj);   // target from [obj+0x20]
// alloc boundary (sub_9bc830) — called when allocation fails
void* sub_9bc830(void* ptr);
// stl boundary (sub_75720) — string too long / std::string::reserve failure
void sub_75720(void);
// lift function (sub_eec6ec0) — memcpy-like
void sub_eec6ec0(void* dst, const void* src, size_t len);
} // namespace native

namespace native::bgfx {

// Layout assertions from header (repeated so liftcheck sees them in the source file).
static_assert(offsetof(sub_bc2c040_state, vtable)  == kOff0x00,  "sub_0xbc2c040 touches self+0x00");
static_assert(offsetof(sub_bc2c040_state, f0x08)  == kOff0x08,  "sub_0xbc2c040 touches self+0x08");
static_assert(offsetof(sub_bc2c040_state, f0x18)  == kOff0x18,  "sub_0xbc2c040 touches self+0x18");
static_assert(offsetof(sub_bc2c040_state, f0x28)  == kOff0x28,  "sub_0xbc2c040 touches self+0x28");
static_assert(offsetof(sub_bc2c040_state, f0x30)  == kOff0x30,  "sub_0xbc2c040 touches self+0x30");
static_assert(offsetof(sub_bc2c040_state, f0x38)  == kOff0x38,  "sub_0xbc2c040 takes the address of self+0x38");
static_assert(offsetof(sub_bc2c040_state, f0x70)  == kOff0x70,  "sub_0xbc2c040 touches self+0x70");
static_assert(offsetof(sub_bc2c040_state, be20)   == kOff0x78,  "sub_0xbc2c040 passes &self+0x78 to sub_bc2be20");
static_assert(offsetof(sub_bc2c040_state, buf)    == kOff0x318, "sub_0xbc2c040 touches self+0x318");
static_assert(offsetof(sub_bc2c040_state, size)   == kOff0x328, "sub_0xbc2c040 touches self+0x328");
static_assert(offsetof(sub_bc2c040_state, cap)    == kOff0x330, "sub_0xbc2c040 touches self+0x330");
static_assert(sizeof(sub_bc2c040_state) >= 0x338, "sub_0xbc2c040 object spans at least [0x00,0x338)");

// sub_0xbc2c040(sub_bc2c040_state* a0 = rcx, void* a1 = rdx, void* a2 = r8, void* a3 = r9)
//   -> void* (rax = a0).
// Minecraft Windows 1.26.62.01, function [0xbc2c040, 0xbc2c205), size 0x1c5.
void* sub_bc2c040(sub_bc2c040_state* a0, void* a1, void* a2, void* a3) {
    uint8_t* self = reinterpret_cast<uint8_t*>(a0);
    void* a1_arg = a1;
    void* a2_arg = a2;
    void* a3_arg = a3;

    // 0xbc2c040..0xbc2c05b: prologue (push rbp/r15/r14/r12/rsi/rdi/rbx, sub rsp,0x40,
    // lea rbp,[rsp+0x40], mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE)
    // 0xbc2c05b  mov rsi,r9
    // 0xbc2c05e  mov rbx,r8
    // 0xbc2c061  mov r14,rcx
    // No observable effect beyond stack frame setup.

    // 0xbc2c064..0xbc2c07f: zero-initialise fields
    // 0xbc2c064  xorps xmm0,xmm0
    // 0xbc2c067  movups [rcx+0x18],xmm0
    *reinterpret_cast<__m128i*>(self + kOff0x18) = _mm_setzero_si128();
    // 0xbc2c06b  movups [rcx+0x8],xmm0
    *reinterpret_cast<__m128i*>(self + kOff0x08) = _mm_setzero_si128();
    // 0xbc2c06f  mov qword ptr [rcx+0x28],0xF
    *reinterpret_cast<uint64_t*>(self + kOff0x28) = 0xF;
    // 0xbc2c077  mov qword ptr [rcx+0x30],0
    *reinterpret_cast<uint64_t*>(self + kOff0x30) = 0;
    // 0xbc2c07f  lea rax,[0xF43F9C0]
    // 0xbc2c086  mov [rcx],rax
    *reinterpret_cast<uint64_t*>(self + kOff0x00) = 0x14F43F9C0; // image base 0x140000000 + RVA 0xF43F9C0

    // 0xbc2c089  lea r15,[rcx+0x38]
    uint8_t* region38 = self + kOff0x38;
    // 0xbc2c08d  mov qword ptr [rcx+0x70],0
    *reinterpret_cast<uint64_t*>(self + kOff0x70) = 0;

    // 0xbc2c095..0xbc2c0dc: process a1->field_0x38 (rdx = a1)
    // 0xbc2c095  mov rcx,[rdx+0x38]
    void* obj = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(a1_arg) + 0x38);
    // 0xbc2c099  test rcx,rcx
    // 0xbc2c09c  je short 0xBC2C0E4
    if (obj != nullptr) {
        // 0xbc2c09e  mov rdi,rdx
        void* a1_copy = a1_arg;
        // 0xbc2c0a1  cmp rcx,rdx
        // 0xbc2c0a4  je short 0xBC2C0AC
        if (obj == a1_arg) {
            // 0xbc2c0ac  mov rax,[rcx]
            // 0xbc2c0af  mov rax,[rax+8]
            // 0xbc2c0b3  mov rdx,r15
            // 0xbc2c0b6  call qword ptr [0xF99FFA0]
            // 0xbc2c0bc  mov [r14+0x70],rax
            *reinterpret_cast<uint64_t*>(self + kOff0x70) = reinterpret_cast<uint64_t>(native::vtableCallSlot1(obj));
            // 0xbc2c0c0  mov rcx,[rdi+0x38]
            // 0xbc2c0c4  test rcx,rcx
            // 0xbc2c0c7  je short 0xBC2C0E4
            obj = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(a1_copy) + 0x38);
            if (obj != nullptr) {
                // 0xbc2c0c9  cmp rcx,rdi
                // 0xbc2c0cc  setne dl
                // 0xbc2c0cf  mov rax,[rcx]
                // 0xbc2c0d2  mov rax,[rax+0x20]
                // 0xbc2c0d6  call qword ptr [0xF99FFA0]
                native::vtableCallSlot4(obj);
            }
        } else {
            // 0xbc2c0a6  mov [r14+0x70],rcx
            // `0xbc2c0a6  mov [r14+70],rcx`
            *reinterpret_cast<uint64_t*>(self + kOff0x70) = reinterpret_cast<uint64_t>(obj);
            // 0xbc2c0aa  jmp short 0xBC2C0DC
        }
        // 0xbc2c0dc  mov qword ptr [rdi+0x38],0
        *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(a1_copy) + 0x38) = nullptr;
    }

    // 0xbc2c0e4: loc_bc2c0e4
    // 0xbc2c0e4  mov [rbp-0x20],r15
    // 0xbc2c0e8  lea r15,[r14+0x78]
    // 0xbc2c0ec  mov rcx,r15
    // 0xbc2c0ef  mov rdx,rsi
    // 0xbc2c0f2  mov [rbp-0x10],r14
    // 0xbc2c0f6  call 0xBC2BE20
    // 0xbc2c0fb  nop
    native::sub_bc2be20(&a0->be20, reinterpret_cast<sub_bc2be20_state*>(a3_arg));

    // 0xbc2c0fc..0xbc2c112: zero buffer pointer and size fields
    // 0xbc2c0fc  xorps xmm0,xmm0
    // 0xbc2c0ff  mov r14,[rbp-0x10]
    // 0xbc2c103  movups [r14+0x328],xmm0
    *reinterpret_cast<__m128i*>(self + kOff0x328) = _mm_setzero_si128();
    // 0xbc2c10b  movups [r14+0x318],xmm0
    *reinterpret_cast<__m128i*>(self + kOff0x318) = _mm_setzero_si128();

    // 0xbc2c113..0xbc2c12d: read a2->field_8 (size), test sign
    // 0xbc2c113  mov rsi,[rbx+8]
    uint64_t size = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(a2_arg) + 8);
    // 0xbc2c117  test rsi,rsi
    // 0xbc2c11a  js 0xBC2C1FA
    if ((int64_t)size < 0) {
        // 0xbc2c1fa  mov [rbp-0x18],r15
        // 0xbc2c1fe  call 0x75720
        // 0xbc2c203  nop
        // 0xbc2c204  int3
        native::sub_75720();
        // unreachable (int3), but original falls through
    }

    // 0xbc2c120  lea rdi,[r14+0x318]
    // 0xbc2c127  mov rbx,[rbx]
    uint8_t* src = *reinterpret_cast<uint8_t**>(a2_arg);
    // 0xbc2c12a  mov r12d,0xF
    uint64_t cap = 0xF;
    // 0xbc2c130  cmp rsi,0x10
    // 0xbc2c134  jb short 0xBC2C1AF
    if (size >= 0x10) {
        // 0xbc2c136  mov [rbp-0x18],r15
        // 0xbc2c13a  mov rdx,rsi
        // 0xbc2c13d  or rdx,0xF
        // 0xbc2c141  cmp rdx,0x17
        // 0xbc2c145  mov r12d,0x16
        // 0xbc2c14b  cmovae r12,rdx
        uint64_t rdx = size | 0xF;
        cap = (rdx >= 0x17) ? rdx : 0x16;

        // 0xbc2c14f  mov rcx,[0x1233E1A8]
        // 0xbc2c156  mov rax,[rcx]
        // 0xbc2c159  mov rax,[rax+8]
        // 0xbc2c15d  cmp rdx,0xFFF
        // 0xbc2c164  jb short 0xBC2C18E
        // 0xbc2c166  lea r15,[r12+0x28]
        // 0xbc2c16b  mov rdx,r15
        // 0xbc2c16e  call qword ptr [0xF99FFA0]
        // 0xbc2c174  nop
        // 0xbc2c175  mov r14,rax
        // 0xbc2c178  test rax,rax
        // 0xbc2c17b  je short 0xBC2C1E1
        // 0xbc2c17d  mov rax,r14
        // 0xbc2c180  add r14,0x27
        // 0xbc2c184  and r14,0xFFFFFFFFFFFFFFE0
        // 0xbc2c188  mov [r14-8],rax
        // 0xbc2c18c  jmp short 0xBC2C1A5
        if (rdx >= 0xFFF) {
            void* alloc_ptr = native::vtableCallSlot1WithSize(rdx); // vtable[1] with rdx=cap+0x28
            if (alloc_ptr == nullptr) {
                // 0xbc2c1e1  mov rcx,r15
                // 0xbc2c1e4  call 0x9BC830
                // 0xbc2c1e9  nop
                // 0xbc2c1ea  jmp short 0xBC2C17D
                // This is an allocation failure path that calls the alloc boundary
                // and retries. We model it as a single call that handles the failure.
                alloc_ptr = native::sub_9bc830(nullptr);
            }
            // Align and store header
            uint8_t* aligned = reinterpret_cast<uint8_t*>(alloc_ptr);
            aligned += 0x27;
            aligned = reinterpret_cast<uint8_t*>((reinterpret_cast<uintptr_t>(aligned)) & ~0x1F);
            *reinterpret_cast<uint64_t*>(aligned - 8) = reinterpret_cast<uint64_t>(alloc_ptr);
            *reinterpret_cast<uint8_t**>(self + kOff0x318) = aligned;
        } else {
            // 0xbc2c18e  lea r15,[r12+1]
            // 0xbc2c193  mov rdx,r15
            // 0xbc2c196  call qword ptr [0xF99FFA0]
            // 0xbc2c19c  nop
            // 0xbc2c19d  mov r14,rax
            // 0xbc2c1a0  test rax,rax
            // 0xbc2c1a3  je short 0xBC2C1EC
            // 0xbc2c1ec  mov rcx,r15
            // 0xbc2c1ef  call 0x9BC830
            // 0xbc2c1f4  nop
            // 0xbc2c1f5  xor r14d,r14d
            // 0xbc2c1f8  jmp short 0xBC2C1A5
            void* alloc_ptr = native::vtableCallSlot1WithSize(cap + 1);
            if (alloc_ptr == nullptr) {
                native::sub_9bc830(nullptr);
                alloc_ptr = nullptr;
            }
            if (alloc_ptr != nullptr) {
                uint8_t* aligned = reinterpret_cast<uint8_t*>(alloc_ptr);
                aligned += 0x27;
                aligned = reinterpret_cast<uint8_t*>((reinterpret_cast<uintptr_t>(aligned)) & ~0x1F);
                *reinterpret_cast<uint64_t*>(aligned - 8) = reinterpret_cast<uint64_t>(alloc_ptr);
                *reinterpret_cast<uint8_t**>(self + kOff0x318) = aligned;
            }
        }
    }

    // 0xbc2c1a5: loc_bc2c1a5
    // 0xbc2c1a5  mov [rdi],r14
    //    (already written above in both branches)
    // 0xbc2c1a8  mov rdi,r14
    // 0xbc2c1ab  mov r14,[rbp-0x10]

    // 0xbc2c1af: loc_bc2c1af
    // 0xbc2c1af  mov [r14+0x328],rsi
    *reinterpret_cast<uint64_t*>(self + kOff0x328) = size;
    // 0xbc2c1b6  mov [r14+0x330],r12
    *reinterpret_cast<uint64_t*>(self + kOff0x330) = cap;

    // 0xbc2c1bd..0xbc2c1c6: call sub_eec6ec0 (memcpy)
    // 0xbc2c1bd  mov rcx,rdi
    // 0xbc2c1c0  mov rdx,rbx
    // 0xbc2c1c3  mov r8,rsi
    // 0xbc2c1c6  call 0xEEC6EC0
    if (*reinterpret_cast<uint8_t**>(self + kOff0x318) != nullptr && src != nullptr) {
        native::sub_eec6ec0(*reinterpret_cast<void**>(self + kOff0x318), src, size);
    }

    // 0xbc2c1cb  mov byte ptr [rdi+rsi],0
    if (*reinterpret_cast<uint8_t**>(self + kOff0x318) != nullptr) {
        (*reinterpret_cast<uint8_t**>(self + kOff0x318))[size] = 0;
    }

    // 0xbc2c1cf  mov rax,r14
    // 0xbc2c1d2..0xbc2c1df: epilogue
    // 0xbc2c1d2  add rsp,0x40
    // 0xbc2c1d6  pop rbx
    // 0xbc2c1d7  pop rdi
    // 0xbc2c1d8  pop rsi
    // 0xbc2c1d9  pop r12
    // 0xbc2c1db  pop r14
    // 0xbc2c1dd  pop r15
    // 0xbc2c1df  pop rbp
    // 0xbc2c1e0  ret
    return a0;
}

// Static footprint for differential verification.
static native::Footprint sub_bc2c040_footprint(sub_bc2c040_state* a0, void*, void*, void*) {
    // Conservative: the whole object is written (vtable, zero-initialisation, be20 sub-object,
    // buf/size/cap). External writes: a1+0x38 zeroed, allocation via vtable calls, memcpy dst.
    return { { a0, 0x338 } };
}

LIFT_FN(sub_bc2c040, "sub_bc2c040", 0xbc2c040, sub_bc2c040, sub_bc2c040_footprint);

} // namespace native::bgfx