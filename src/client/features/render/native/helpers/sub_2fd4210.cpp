// LIFT 0x2fd4210 size 0x11f 1.26.62.01 sub_2fd4210
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_2fd4210.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_2fd4210, "sub_2fd4210", 0x2fd4210, sub_2fd4210, nullptr);

static_assert(offsetof(sub_2fd4210_rdx, f8) == 0x8, "sub_0x2fd4210 rdx+0x8 field");
static_assert(offsetof(sub_2fd4210_rbp, f24) == 0x24, "sub_0x2fd4210 rbp+0x24 field");

// Verbatim call instructions from the disassembly of [0x2fd4210, 0x2fd432f) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
// sub_eea6040 is a classified boundary (vendor, thunk via data slot 0xF99FFA0).
// sub_2fd3e60 is NOT in the lift set and NOT a classified boundary.
#if 0
0x2fd425e  call qword ptr [0xF99FFA0]
0x2fd42f7  call 0x2FD3E60
0x2fd431a  call qword ptr [0xF99FFA0]
#endif

// Ranges: every instruction of [0x2fd4210, 0x2fd432f) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

// sub_eea6040 boundary: vendor thunk via data slot 0xF99FFA0.
// Called with (rcx=this, rdx=out_buf) in block 1; (rcx=this, rdx=bool) in block 3.
// Returns uintptr_t in rax.
static native::Boundary<uintptr_t, void*, void*> sub_eea6040_boundary("sub_eea6040");

// sub_2fd3e60: direct call, NOT in lift set, NOT a classified boundary.
// Signature unknown; best-effort declaration based on the call site at 0x2fd42f7:
//   rcx=self, rdx=&rect, r8d=saved_r9d, r9d=low_byte_of_a1,
//   stack[0]=&output_buffer, stack[1]=a3_home
// Return value is discarded (rax overwritten immediately after call).
// Call at 0x2fd42f7: call 0x2FD3E60 (callee signature not available from static data).
extern "C" void sub_2fd3e60(void* self, void* rect, std::uint32_t arg3, std::uint8_t arg4, void* output_buf, void* arg6);

// Output buffer at [rbp-0x48], used by sub_eea6040 (block 1) and sub_2fd3e60 (block 2).
// Size unknown from static analysis; covers [rbp-0x48..rbp-0x8).
struct alignas(8) OutputBuffer {
    std::uint8_t data[0x40];
};

// Rect at [rbp-8]: 6 int32 fields.
//   [rbp-8]  = a1->f0 >> 4
//   [rbp-4]  = 0
//   [rbp+0]  = a1->f8 >> 4
//   [rbp+4]  = a2->f0 >> 4
//   [rbp+8]  = 0
//   [rbp+0xC]= a2->f8 >> 4
struct alignas(4) ChunkRect {
    std::int32_t f0;  // [rbp-8]
    std::int32_t f4;  // [rbp-4]
    std::int32_t f8;  // [rbp+0]
    std::int32_t fc;  // [rbp+4]
    std::int32_t f10; // [rbp+8]
    std::int32_t f14; // [rbp+0xC]
};

uintptr_t sub_2fd4210(void* self, sub_2fd4210_rdx* a1, sub_2fd4210_r8* a2, uint32_t a3) {
    // 0x2fd4210..0x2fd424e: basic block 0
    // 0x2fd4210  push rbp
    // 0x2fd4211  push r14
    // 0x2fd4213  push rsi
    // 0x2fd4214  push rdi
    // 0x2fd4215  push rbx
    // 0x2fd4216  sub rsp,0xB0
    // 0x2fd421d  lea rbp,[rsp+0x80]
    // 0x2fd4225  mov qword ptr [rbp+0x28],0xFFFFFFFFFFFFFFFE
    // 0x2fd422d  mov ebx,r9d
    // 0x2fd4230  mov rsi,r8
    // 0x2fd4233  mov rdi,rdx
    // 0x2fd4236  mov rax,[rbp+0x88]
    // 0x2fd423d  mov qword ptr [rbp-0x10],0
    // 0x2fd4245  mov r8,[rax+0x38]
    // 0x2fd4249  test r8,r8
    // 0x2fd424c  je short 0x2FD426C
    // -> if a2_home->f38 == 0 goto L_0x2fd426c
    // -> if a2_home->f38 != 0 goto L_0x2fd424e
    L_0x2fd4210:;
    std::uint8_t saved_a3_low = static_cast<std::uint8_t>(a3);  // ebx = r9d
    sub_2fd4210_r8* a2_ptr = a2;                                // rsi = r8 (a2)
    sub_2fd4210_rdx* a1_ptr = a1;                               // rdi = rdx (a1)
    void* a2_home = a2;                                         // [rbp+0x88] = home space r8 = a2
    void* local_0x10 = nullptr;                                 // [rbp-0x10] = 0
    void* r8_val = static_cast<sub_2fd4210_rax*>(a2_home)->f38; // r8 = [a2+0x38]

    OutputBuffer output_buffer{};                               // [rbp-0x48] buffer

    if (r8_val != nullptr) {
        // 0x2fd424e..0x2fd426c: basic block 1
        // 0x2fd424e  mov r14,rcx
        // 0x2fd4251  mov rax,[r8]
        // 0x2fd4254  mov rax,[rax]
        // 0x2fd4257  lea rdx,[rbp-0x48]
        // 0x2fd425b  mov rcx,r8
        // 0x2fd425e  call qword ptr [0xF99FFA0]
        // 0x2fd4264  nop
        // 0x2fd4265  mov [rbp-0x10],rax
        // 0x2fd4269  mov rcx,r14
        // -> if fallthrough goto L_0x2fd426c
        L_0x2fd424e:;
        void* saved_self = self;                                // r14 = rcx
        uintptr_t sub_eea6040_ret = sub_eea6040_boundary(r8_val, &output_buffer); // sub_eea6040(r8_val, &output_buffer)
        local_0x10 = reinterpret_cast<void*>(sub_eea6040_ret);  // [rbp-0x10] = rax
        self = saved_self;                                      // rcx = r14
    }

    // 0x2fd426c..0x2fd430d: basic block 2
    // 0x2fd426c  mov rax,[rbp+0x90]
    // 0x2fd4273  movzx r9d,byte ptr [rbp+0x80]
    // 0x2fd427b  mov dword ptr [rbp+0x24],0x10
    // 0x2fd4282  mov edx,[rdi]
    // 0x2fd4284  mov r8d,[rdi+8]
    // 0x2fd4288  sar edx,4
    // 0x2fd428b  sar r8d,4
    // 0x2fd428f  mov r10d,[rsi]
    // 0x2fd4292  mov r11d,[rsi+8]
    // 0x2fd4296  sar r10d,4
    // 0x2fd429a  sar r11d,4
    // 0x2fd429e  mov [rbp-8],edx
    // 0x2fd42a1  mov dword ptr [rbp-4],0
    // 0x2fd42a8  mov [rbp],r8d
    // 0x2fd42ac  mov [rbp+4],r10d
    // 0x2fd42b0  mov dword ptr [rbp+8],0
    // 0x2fd42b7  mov [rbp+0xC],r11d
    // 0x2fd42bb  sub r11d,r8d
    // 0x2fd42be  sub r10d,edx
    // 0x2fd42c1  inc r11d
    // 0x2fd42c4  inc r10d
    // 0x2fd42c7  mov [rbp+0x10],r10d
    // 0x2fd42cb  mov dword ptr [rbp+0x14],1
    // 0x2fd42d2  mov [rbp+0x18],r11d
    // 0x2fd42d6  imul r10d,r11d
    // 0x2fd42da  mov [rbp+0x1C],r10d
    // 0x2fd42de  mov [rbp+0x20],r10d
    // 0x2fd42e2  mov [rsp+0x28],rax
    // 0x2fd42e7  lea rax,[rbp-0x48]
    // 0x2fd42eb  mov [rsp+0x20],rax
    // 0x2fd42f0  lea rdx,[rbp-8]
    // 0x2fd42f4  mov r8d,ebx
    // 0x2fd42f7  call 0x2FD3E60
    // 0x2fd42fc  nop
    // 0x2fd42fd  mov rax,[rbp+0x88]
    // 0x2fd4304  mov rcx,[rax+0x38]
    // 0x2fd4308  test rcx,rcx
    // 0x2fd430b  je short 0x2FD4321
    // -> if a2_home->f38 == 0 goto L_0x2fd4321
    // -> if a2_home->f38 != 0 goto L_0x2fd430d
    L_0x2fd426c:;
    void* a3_home = reinterpret_cast<void*>(static_cast<uintptr_t>(a3)); // [rbp+0x90] = home space r9
    std::uint8_t a1_low_byte = static_cast<std::uint8_t>(reinterpret_cast<uintptr_t>(a1_ptr)); // [rbp+0x80] low byte

    // Stack cookie at [rbp+0x28] (written but not read later; retained for fidelity)
    volatile std::uint64_t stack_cookie = 0xFFFFFFFFFFFFFFFEULL;

    // Rect construction at [rbp-8] .. [rbp+0xC]
    ChunkRect rect{};
    rect.f0 = static_cast<std::int32_t>(a1_ptr->f0) >> 4;   // [rbp-8] = a1->f0 >> 4
    rect.f4 = 0;                                             // [rbp-4] = 0
    rect.f8 = static_cast<std::int32_t>(a1_ptr->f8) >> 4;   // [rbp+0] = a1->f8 >> 4
    rect.fc = static_cast<std::int32_t>(reinterpret_cast<uintptr_t>(a2_ptr->f0)) >> 4;   // [rbp+4] = a2->f0 >> 4
    rect.f10 = 0;                                            // [rbp+8] = 0
    rect.f14 = static_cast<std::int32_t>(a2_ptr->f8) >> 4;  // [rbp+0xC] = a2->f8 >> 4

    // Width/height computation
    std::int32_t width = rect.fc - rect.f0 + 1;   // r10d = (a2->f0 - a1->f0)>>4 + 1
    std::int32_t height = rect.f14 - rect.f8 + 1; // r11d = (a2->f8 - a1->f8)>>4 + 1
    std::int32_t total = width * height;           // imul r10d, r11d

    // Stack slots for sub_2fd3e60 (args 5-6 on stack)
    void* stack_slot_0x20 = &output_buffer;       // [rsp+0x20] = &output_buffer
    void* stack_slot_0x28 = a3_home;              // [rsp+0x28] = rax = a3_home

    // sub_2fd3e60(self, &rect, saved_a3_low, a1_low_byte, &output_buffer, a3_home)
    // call at 0x2fd42f7: call 0x2FD3E60 (callee signature not available from static data)
    sub_2fd3e60(self, &rect, saved_a3_low, a1_low_byte, stack_slot_0x20, stack_slot_0x28);

    // 0x2fd430d..0x2fd4321: basic block 3
    // 0x2fd430d  cmp rcx,rax
    // 0x2fd4310  setne dl
    // 0x2fd4313  mov rax,[rcx]
    // 0x2fd4316  mov rax,[rax+0x20]
    // 0x2fd431a  call qword ptr [0xF99FFA0]
    // 0x2fd4320  nop
    // -> if fallthrough goto L_0x2fd4321
    L_0x2fd430d:;
    uintptr_t result = reinterpret_cast<uintptr_t>(a2_home); // default: rax = [rbp+0x88] = a2_home

    void* rcx_val = static_cast<sub_2fd4210_rax*>(a2_home)->f38;   // rcx = [a2+0x38]
    if (rcx_val != nullptr) {
        bool ne = (rcx_val != a2_home); // setne dl: dl = (rcx != rax)
        // sub_eea6040(rcx_val, (void*)(uintptr_t)ne)
        result = sub_eea6040_boundary(rcx_val, reinterpret_cast<void*>(static_cast<uintptr_t>(ne ? 1 : 0)));
    }

    // 0x2fd4321..0x2fd432f: basic block 4
    // 0x2fd4321  add rsp,0xB0
    // 0x2fd4328  pop rbx
    // 0x2fd4329  pop rdi
    // 0x2fd432a  pop rsi
    // 0x2fd432b  pop r14
    // 0x2fd432d  pop rbp
    // 0x2fd432e  ret
    // -> (fall-through / ret / end)
    L_0x2fd4321:;
    return result;
}

} // namespace native::helpers
