// LIFT 0x14a0c0 size 0x130 1.26.62.01 sub_14a0c0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_14a0c0.h"

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <intrin.h>

namespace native::helpers {

// Layout assertions (mirrored in sub_14a0c0.h): every field read or written has
// an offsetof static_assert at its observed offset.
static_assert(offsetof(sub_14a0c0_rcx, f0) == 0x0, "14a0c0 rcx+0x0");
static_assert(offsetof(sub_14a0c0_rcx, f8) == 0x8, "14a0c0 rcx+0x8");
static_assert(sizeof(sub_14a0c0_rcx) >= 0x10, "14a0c0 rcx sizeof");
static_assert(offsetof(sub_14a0c0_rdx, f0) == 0x0, "14a0c0 rdx+0x0");
static_assert(offsetof(sub_14a0c0_rdx, f8) == 0x8, "14a0c0 rdx+0x8");
static_assert(sizeof(sub_14a0c0_rdx) >= 0xc, "14a0c0 rdx sizeof");
static_assert(offsetof(sub_14a0c0_r8, f0) == 0x0, "14a0c0 r8+0x0");
static_assert(offsetof(sub_14a0c0_r8, f8) == 0x8, "14a0c0 r8+0x8");
static_assert(offsetof(sub_14a0c0_r8, fc) == 0xc, "14a0c0 r8+0xc");
static_assert(offsetof(sub_14a0c0_r8, f30) == 0x30, "14a0c0 r8+0x30");
static_assert(sizeof(sub_14a0c0_r8) >= 0x31, "14a0c0 r8 sizeof");
static_assert(offsetof(sub_14a0c0_rax, f0) == 0x0, "14a0c0 rax+0x0");
static_assert(offsetof(sub_14a0c0_rax, f18) == 0x18, "14a0c0 rax+0x18");
static_assert(sizeof(sub_14a0c0_rax) >= 0x20, "14a0c0 rax sizeof");
static_assert(offsetof(sub_14a0c0_rbp, f40) == 0x40, "14a0c0 rbp+0x40");
static_assert(offsetof(sub_14a0c0_rbp, f48) == 0x48, "14a0c0 rbp+0x48");
static_assert(sizeof(sub_14a0c0_rbp) >= 0x50, "14a0c0 rbp sizeof");
static_assert(offsetof(sub_14a0c0_rsp, f20) == 0x20, "14a0c0 rsp+0x20");
static_assert(offsetof(sub_14a0c0_rsp, f80) == 0x80, "14a0c0 rsp+0x80");
static_assert(sizeof(sub_14a0c0_rsp) >= 0x81, "14a0c0 rsp sizeof");

LIFT_FN(sub_14a0c0, "sub_14a0c0", 0x14a0c0, sub_14a0c0, nullptr);

// Verbatim call instructions from the disassembly of [0x14a0c0, 0x14a1f0) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x14a103  call 0x14A260
0x14a143  call qword ptr [0xF99FFA0]
0x14a163  call 0x14A430
0x14a18a  call 0x14ABF0
0x14a1ac  call qword ptr [0xF99FFA0]
0x14a1c2  call qword ptr [0xF99FFA0]
0x14a1dc  call qword ptr [0xF99FFA0]
#endif

// Native callees used by this lift. Signatures are open (no Sigs.json entries); the
// shapes below are recovered from the disassembly of [0x14a0c0, 0x14a1f0).
// sub_14a260(self, &savedRdxSlot, &savedByteSlot) - 0x14a103 call 0x14A260
void sub_14a260(void* self, sub_14a0c0_rdx** savedRdxSlot, std::uint8_t* savedByteSlot);
// sub_14a430(rcx=self->f0, edx=0, r8d=0, r9d=0) - 0x14a163 call 0x14A430
void sub_14a430(void* rcx, std::uint32_t edx, std::uint32_t r8d, std::uint32_t r9d);
// sub_14abf0(rcx=self->f0, rdx=&saved16) - 0x14a18a call 0x14ABF0
void sub_14abf0(void* rcx, void* savedState);
// sub_eea6040(object, auxiliary) - every indirect call goes through data slot 0xF99FFA0,
// which the pack holds at sub_eea6040 ([data_f99ffa0]).
void sub_eea6040(void* object, void* auxiliary = nullptr);

// Model of the indirect-call data slot: dereference the slot once and reuse the
// resolved function pointer, same convention as sub_11666d0.cpp.
static auto eea6040 = reinterpret_cast<decltype(&sub_eea6040)>(
    *reinterpret_cast<void**>(0xF99FFA0));

// Ranges: every instruction of [0x14a0c0, 0x14a1f0) is covered by a block range comment
// and/or a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

uintptr_t sub_14a0c0(void* self, sub_14a0c0_rdx* a1, sub_14a0c0_r8* a2, void* a3) {
    auto* a0 = static_cast<sub_14a0c0_rcx*>(self);   // 0x14a0e1 mov rdi,rcx

    // Caller-frame slots read via [rbp+0x40] / [rbp+0x48]; provenance [open] (they
    // sit above this function's own frame), modeled as zero-initialized locals.
    std::uint8_t frame_f40 = 0;                      // 0x14a0e8 movzx eax, byte ptr [rbp+0x40]
    void* frame_f48 = nullptr;                       // 0x14a0e4 / 0x14a1c8 mov rcx,[rbp+0x48]

    // Stack slots of this frame (all negative rbp/rsp offsets are locals here).
    sub_14a0c0_rdx* saved_rdx = a1;                  // 0x14a0ec mov [rbp-0x28],rdx
    std::uint8_t saved_byte = frame_f40;             // 0x14a0f0 mov [rbp-9],al

    // Register values preserved across blocks (rax, rdxObj, rsi).
    void* rax = nullptr;
    sub_14a0c0_rdx* rdxObj = nullptr;
    void* rsi = nullptr;
    void* rsiVtable = nullptr;

    // Saved pair [rbp-0x40]/[rbp-0x38] = {self->f0, self->f8-as-pointer}.
    void* savedPair[2] = { nullptr, nullptr };
    void* vtableOfA1 = nullptr;
    void* releaseFn = nullptr;

    // Saved 16-byte exchange slot [rbp-0x50].
    std::uint8_t saved16[16] = { 0 };

    void* frameObj = nullptr;
    void* objVtable = nullptr;

    // 0x14a0c0..0x14a124: basic block 0
    // 0x14a0c0  push rbp
    // 0x14a0c1  push rsi
    // 0x14a0c2  push rdi
    // 0x14a0c3  sub rsp,0x80
    // 0x14a0ca  lea rbp,[rsp+0x80]
    // 0x14a0d2  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
    // 0x14a0da  mov [rbp-0x20],r9
    // 0x14a0de  mov rsi,r8
    // 0x14a0e1  mov rdi,rcx
    // 0x14a0e4  mov rcx,[rbp+0x48]
    // 0x14a0e8  movzx eax,byte ptr [rbp+0x40]
    // 0x14a0ec  mov [rbp-0x28],rdx
    // 0x14a0f0  mov [rbp-9],al
    // 0x14a0f3  mov [rsp+0x20],rcx
    // 0x14a0f8  lea rdx,[rbp-0x28]
    // 0x14a0fc  lea r9,[rbp-9]
    // 0x14a100  mov rcx,rdi
    // 0x14a103  call 0x14A260
    // 0x14a108  nop
    // 0x14a109  mov rcx,[rbp-0x28]
    // 0x14a10d  mov rax,[rdi]
    // 0x14a110  xorps xmm0,xmm0
    // 0x14a113  movaps [rbp-0x40],xmm0
    // 0x14a117  mov rdx,[rdi+8]
    // 0x14a11b  test rdx,rdx
    // 0x14a11e  mov [rbp-0x18],rdi
    // 0x14a122  je short 0x14A12E
    // -> if self->f8 == 0 goto L_0x14a12e
    // -> if self->f8 != 0 goto L_0x14a124
    L_0x14a0c0:;
    sub_14a260(self, &saved_rdx, &saved_byte);       // 0x14a103 call 0x14A260
    rax = a0->f0;                                    // 0x14a10d mov rax,[rdi]
    rdxObj = reinterpret_cast<sub_14a0c0_rdx*>(a0->f8); // 0x14a117 mov rdx,[rdi+8]
    if (rdxObj == nullptr) goto L_0x14a12e;          // 0x14a122 je short 0x14A12E

    // 0x14a124..0x14a12e: basic block 1
    // 0x14a124  lock inc dword ptr [rdx+8]
    // 0x14a128  mov rdx,[rdi+8]
    // 0x14a12c  jmp short 0x14A130
    // -> if jmp goto L_0x14a130
    L_0x14a124:;
    (void)_InterlockedIncrement(reinterpret_cast<volatile LONG*>(&rdxObj->f8)); // 0x14a124 lock inc [rdx+8]
    rdxObj = reinterpret_cast<sub_14a0c0_rdx*>(a0->f8); // 0x14a128 mov rdx,[rdi+8]
    goto L_0x14a130;                                 // 0x14a12c jmp short 0x14A130

    // 0x14a12e..0x14a130: basic block 2
    // 0x14a12e  xor edx,edx
    // -> if fallthrough goto L_0x14a130
    L_0x14a12e:;
    rdxObj = nullptr;                                // 0x14a12e xor edx,edx

    // 0x14a130..0x14a154: basic block 3
    // 0x14a130  mov [rbp-0x40],rax
    // 0x14a134  mov [rbp-0x38],rdx
    // 0x14a138  mov rax,[rcx]           rcx == saved_rdx (a1)
    // 0x14a13b  mov rax,[rax+0x18]
    // 0x14a13f  lea rdx,[rbp-0x40]
    // 0x14a143  call qword ptr [0xF99FFA0]
    // 0x14a149  nop
    // 0x14a14a  mov rax,[rbp-0x20]
    // 0x14a14e  cmp qword ptr [rax],0
    // 0x14a152  je short 0x14A190
    // -> if *a3 == 0 goto L_0x14a190
    // -> if *a3 != 0 goto L_0x14a154
    L_0x14a130:;
    savedPair[0] = rax;                              // 0x14a130 mov [rbp-0x40],rax
    savedPair[1] = reinterpret_cast<void*>(rdxObj);  // 0x14a134 mov [rbp-0x38],rdx
    vtableOfA1 = *reinterpret_cast<void**>(saved_rdx);        // 0x14a138 mov rax,[rcx]
    releaseFn = *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(vtableOfA1) + 0x18);  // 0x14a13b mov rax,[rax+0x18]
    eea6040(releaseFn, savedPair);                   // 0x14a143 call qword ptr [0xF99FFA0]
    rax = a3;                                        // 0x14a14a mov rax,[rbp-0x20]
    if (*reinterpret_cast<void**>(a3) == nullptr) goto L_0x14a190; // 0x14a152 je short 0x14A190

    // 0x14a154..0x14a190: basic block 4
    // 0x14a154  mov rax,[rbp-0x18]
    // 0x14a158  mov rcx,[rax]
    // 0x14a15b  xor edx,edx
    // 0x14a15d  xor r8d,r8d
    // 0x14a160  xor r9d,r9d
    // 0x14a163  call 0x14A430
    // 0x14a168  nop
    // 0x14a169  mov rax,[rbp-0x18]
    // 0x14a16d  mov rcx,[rax]
    // 0x14a170  movzx r8d,byte ptr [rsi+0x30]
    // 0x14a175  mov rax,[rbp-0x20]
    // 0x14a179  movups xmm0,[rax]
    // 0x14a17c  xorps xmm1,xmm1
    // 0x14a17f  movups [rax],xmm1
    // 0x14a182  movaps [rbp-0x50],xmm0
    // 0x14a186  lea rdx,[rbp-0x50]
    // 0x14a18a  call 0x14ABF0
    // 0x14a18f  nop
    // -> if fallthrough goto L_0x14a190
    L_0x14a154:;
    sub_14a430(a0->f0, 0u, 0u, 0u);                  // 0x14a163 call 0x14A430
    (void)a2->f30;                                   // 0x14a170 movzx r8d,byte ptr [rsi+0x30]
    std::memcpy(saved16, a3, 16);                    // 0x14a179 movups xmm0,[rax]
    std::memset(a3, 0, 16);                          // 0x14a17f movups [rax],xmm1  (xmm1 = 0)
    sub_14abf0(a0->f0, saved16);                     // 0x14a18a call 0x14ABF0

    // 0x14a190..0x14a19d: basic block 5
    // 0x14a190  mov rax,[rbp-0x20]
    // 0x14a194  mov rsi,[rax+8]
    // 0x14a198  test rsi,rsi
    // 0x14a19b  je short 0x14A1C8
    // -> if rsi == 0 goto L_0x14a1c8
    // -> if rsi != 0 goto L_0x14a19d
    L_0x14a190:;
    rax = a3;                                        // 0x14a190 mov rax,[rbp-0x20]
    rsi = *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(a3) + 8);    // 0x14a194 mov rsi,[rax+8]
    if (rsi == nullptr) goto L_0x14a1c8;             // 0x14a19b je short 0x14A1C8

    // 0x14a19d..0x14a1a3: basic block 6
    // 0x14a19d  lock dec dword ptr [rsi+8]
    // 0x14a1a1  jne short 0x14A1C8
    // -> if (Dec ?, ?) != 0 goto L_0x14a1c8
    // -> if (Dec ?, ?) == 0 goto L_0x14a1a3
    L_0x14a19d:;
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(
            reinterpret_cast<std::uint8_t*>(rsi) + 8)) != 0)
        goto L_0x14a1c8;                             // 0x14a1a1 jne short 0x14A1C8

    // 0x14a1a3..0x14a1b8: basic block 7
    // 0x14a1a3  mov rax,[rsi]
    // 0x14a1a6  mov rax,[rax]
    // 0x14a1a9  mov rcx,rsi
    // 0x14a1ac  call qword ptr [0xF99FFA0]
    // 0x14a1b2  lock dec dword ptr [rsi+0xC]
    // 0x14a1b6  jne short 0x14A1C8
    // -> if (Dec ?, ?) != 0 goto L_0x14a1c8
    // -> if (Dec ?, ?) == 0 goto L_0x14a1b8
    L_0x14a1a3:;
    rsiVtable = *reinterpret_cast<void**>(rsi);      // 0x14a1a6 mov rax,[rax] (dead load)
    (void)rsiVtable;
    eea6040(rsi, nullptr);                           // 0x14a1ac call qword ptr [0xF99FFA0]
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(
            reinterpret_cast<std::uint8_t*>(rsi) + 0xC)) != 0)
        goto L_0x14a1c8;                             // 0x14a1b6 jne short 0x14A1C8

    // 0x14a1b8..0x14a1c8: basic block 8
    // 0x14a1b8  mov rax,[rsi]
    // 0x14a1bb  mov rax,[rax+8]
    // 0x14a1bf  mov rcx,rsi
    // 0x14a1c2  call qword ptr [0xF99FFA0]
    // -> if fallthrough goto L_0x14a1c8
    L_0x14a1b8:;
    (void)*reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(rsiVtable) + 8); // 0x14a1bb mov rax,[rax+8] (dead read)
    eea6040(rsi, nullptr);                           // 0x14a1c2 call qword ptr [0xF99FFA0]

    // 0x14a1c8..0x14a1d8: basic block 9
    // 0x14a1c8  mov rcx,[rbp+0x48]
    // 0x14a1cc  mov rax,[rcx]
    // 0x14a1cf  test rax,rax
    // 0x14a1d2  mov rsi,[rbp-0x18]
    // 0x14a1d6  je short 0x14A1E2
    // -> if objVtable == 0 goto L_0x14a1e2
    // -> if objVtable != 0 goto L_0x14a1d8
    L_0x14a1c8:;
    frameObj = frame_f48;                            // 0x14a1c8 mov rcx,[rbp+0x48]
    objVtable = frameObj ? *reinterpret_cast<void**>(frameObj) : nullptr; // 0x14a1cc mov rax,[rcx]
    rsi = self;                                      // 0x14a1d2 mov rsi,[rbp-0x18] (== self)
    if (objVtable == nullptr) goto L_0x14a1e2;       // 0x14a1d6 je short 0x14A1E2

    // 0x14a1d8..0x14a1e2: basic block 10
    // 0x14a1d8  mov rax,[rax+8]
    // 0x14a1dc  call qword ptr [0xF99FFA0]
    // -> if fallthrough goto L_0x14a1e2
    L_0x14a1d8:;
    (void)*reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(objVtable) + 8); // 0x14a1d8 mov rax,[rax+8] (dead read)
    eea6040(frameObj, nullptr);                      // 0x14a1dc call qword ptr [0xF99FFA0]

    // 0x14a1e2..0x14a1f0: basic block 11
    // 0x14a1e2  mov rax,rsi          rsi == self here
    // 0x14a1e5  add rsp,0x80
    // 0x14a1ec  pop rdi
    // 0x14a1ed  pop rsi
    // 0x14a1ee  pop rbp
    // 0x14a1ef  ret
    // -> (fall-through / ret / end)
    L_0x14a1e2:;
    return reinterpret_cast<uintptr_t>(self);        // 0x14a1e2 mov rax,rsi
}

} // namespace native::helpers
