// LIFT 0xe7e150 size 0x10d 1.26.62.01 sub_e7e150
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_e7e150.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

// 0x88bb50 is the single direct callee of 0xe7e150 (0xe7e1b9). It is outside the lift
// set; x64 ABI shape taken from the call site: pointer in rcx, pointer in rax, the rax
// result is null-tested at 0xe7e1bf.
void* sub_88bb50(void* value);

// Layout constants of the state views used below (complete set in sub_e7e150.h).
static_assert(offsetof(sub_e7e150_rcx, fallbackValue) == 0x5c, "sub_0xe7e150 rcx+0x5c field");
static_assert(offsetof(sub_e7e150_rcx, provider) == 0x98, "sub_0xe7e150 rcx+0x98 field");
static_assert(offsetof(sub_e7e150_rcx, enabled) == 0xcb0, "sub_0xe7e150 rcx+0xcb0 field");
static_assert(offsetof(sub_e7e150_rax, value) == 0x18, "sub_0xe7e150 rax+0x18 field");
static_assert(offsetof(sub_e7e150_Handle, f10) == 0x10, "sub_0xe7e150 handle+0x10 field");

LIFT_FN(sub_e7e150, "sub_e7e150", 0xe7e150, sub_e7e150, nullptr);

// Verbatim call instructions from the disassembly of [0xe7e150, 0xe7e25d) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xe7e18e  call qword ptr [0xF99FFA0]
0xe7e1af  call qword ptr [0xF99FFA0]
0xe7e1b9  call 0x88BB50
0xe7e1ec  call qword ptr [0xF99FFA0]
0xe7e202  call qword ptr [0xF99FFA0]
0xe7e228  call qword ptr [0xF99FFA0]
0xe7e23e  call qword ptr [0xF99FFA0]
#endif

float sub_e7e150(void* selfRaw) {
    auto* const self = static_cast<sub_e7e150_rcx*>(selfRaw);
    float value;

    // 0xe7e150..0xe7e179: basic block 0 - frame, enabled check
    // 0xe7e150  push rbp
    // 0xe7e151  push rsi
    // 0xe7e152  push rdi
    // 0xe7e153  push rbx
    // 0xe7e154  sub rsp,0x58
    // 0xe7e158  lea rbp,[rsp+0x50]
    // 0xe7e15d  movaps [rbp-0x10],xmm6
    // 0xe7e161  mov qword ptr [rbp-0x18],0xFFFFFFFFFFFFFFFE
    // 0xe7e169  mov rsi,rcx
    // 0xe7e16c  cmp byte ptr [rcx+0xCB0],1
    // 0xe7e173  jne 0xE7E248
    if (self->enabled != 1) {
        value = self->fallbackValue;                // 0xe7e248  movss xmm6,[rsi+0x5C]
        return value;                               // 0xe7e24d  movaps xmm0,xmm6
    }

    // 0xe7e179..0xe7e19f: basic block 1 - ask the provider for a handle
    // 0xe7e179  mov rcx,[rsi+0x98]
    // 0xe7e180  mov rax,[rcx]
    // 0xe7e183  mov rax,[rax+0x108]
    // 0xe7e18a  lea rdx,[rbp-0x30]
    // 0xe7e18e  call qword ptr [0xF99FFA0]
    // 0xe7e194  mov rax,[rbp-0x30]
    // 0xe7e198  mov bl,1
    // 0xe7e19a  test rax,rax
    // 0xe7e19d  je short 0xE7E1CD
    auto* const provider = static_cast<sub_e7e150_rcx*>(self->provider);
    using FillFn = void (*)(void*, sub_e7e150_Handle*);
    sub_e7e150_Handle handle;
    reinterpret_cast<FillFn>(static_cast<void**>(provider->vtable)[0x108 / 8])(provider, &handle);
    void* const handleObject = handle.f0;
    bool useFallback = true;

    // 0xe7e19f..0xe7e1a4: basic block 2
    // 0xe7e19f  cmp byte ptr [rax],1
    // 0xe7e1a2  jne short 0xE7E1CD
    if (handleObject != nullptr && *static_cast<std::uint8_t*>(handleObject) == 1) {
        // 0xe7e1a4..0xe7e1c4: basic block 3
        // 0xe7e1a4  mov rcx,[rbp-0x20]
        // 0xe7e1a8  mov rax,[rcx]
        // 0xe7e1ab  mov rax,[rax+8]
        // 0xe7e1af  call qword ptr [0xF99FFA0]
        // 0xe7e1b5  nop
        // 0xe7e1b6  mov rcx,rax
        // 0xe7e1b9  call 0x88BB50
        // 0xe7e1be  nop
        // 0xe7e1bf  test rax,rax
        // 0xe7e1c2  je short 0xE7E1CD
        auto* const inner = static_cast<sub_e7e150_rcx*>(handle.f10);
        using GetFn = void* (*)(void*);
        void* const got = reinterpret_cast<GetFn>(static_cast<void**>(inner->vtable)[1])(inner);
        auto* const found = static_cast<sub_e7e150_rax*>(sub_88bb50(got));

        // 0xe7e1c4..0xe7e1cd: basic block 4
        // 0xe7e1c4  movss xmm6,[rax+0x18]
        // 0xe7e1c9  xor ebx,ebx
        // 0xe7e1cb  jmp short 0xE7E1CD
        if (found != nullptr) {
            value = found->value;
            useFallback = false;
        }
    }

    // 0xe7e1cd..0xe7e1dd: basic block 5 - release slot 0 of the handle
    // 0xe7e1cd  xorps xmm0,xmm0
    // 0xe7e1d0  mov rdi,[rbp-0x28]
    // 0xe7e1d4  movups [rbp-0x30],xmm0
    // 0xe7e1d8  test rdi,rdi
    // 0xe7e1db  je short 0xE7E244
    auto* ctl = static_cast<sub_e7e150_rdi*>(handle.f8);
    handle.f0 = nullptr;
    handle.f8 = nullptr;
    if (ctl != nullptr) {
        // 0xe7e1dd..0xe7e1e3: basic block 6
        // 0xe7e1dd  lock dec dword ptr [rdi+8]
        // 0xe7e1e1  jne short 0xE7E208
        if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&ctl->strongCount)) == 0) {
            // 0xe7e1e3..0xe7e1f8: basic block 7
            // 0xe7e1e3  mov rax,[rdi]
            // 0xe7e1e6  mov rax,[rax]
            // 0xe7e1e9  mov rcx,rdi
            // 0xe7e1ec  call qword ptr [0xF99FFA0]
            // 0xe7e1f2  lock dec dword ptr [rdi+0xC]
            // 0xe7e1f6  jne short 0xE7E208
            void** const ctlVtable = static_cast<void**>(ctl->vtable);
            reinterpret_cast<void (*)(void*)>(ctlVtable[0])(ctl);
            if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&ctl->weakCount)) == 0) {
                // 0xe7e1f8..0xe7e208: basic block 8
                // 0xe7e1f8  mov rax,[rdi]
                // 0xe7e1fb  mov rax,[rax+8]
                // 0xe7e1ff  mov rcx,rdi
                // 0xe7e202  call qword ptr [0xF99FFA0]
                void** const ctlVtableFree = static_cast<void**>(ctl->vtable);
                reinterpret_cast<void (*)(void*)>(ctlVtableFree[1])(ctl);
            }
        }
    }

    // 0xe7e208..0xe7e219: basic block 9 - second handle slot; [rbp-0x28] was cleared above
    // 0xe7e208  mov rdi,[rbp-0x28]
    // 0xe7e20c  mov qword ptr [rbp-0x20],0
    // 0xe7e214  test rdi,rdi
    // 0xe7e217  je short 0xE7E244
    auto* ctl2 = static_cast<sub_e7e150_rdi*>(handle.f8);
    handle.f10 = nullptr;
    if (ctl2 != nullptr) {
        // 0xe7e219..0xe7e21f: basic block 10
        // 0xe7e219  lock dec dword ptr [rdi+8]
        // 0xe7e21d  jne short 0xE7E244
        if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&ctl2->strongCount)) == 0) {
            // 0xe7e21f..0xe7e234: basic block 11
            // 0xe7e21f  mov rax,[rdi]
            // 0xe7e222  mov rax,[rax]
            // 0xe7e225  mov rcx,rdi
            // 0xe7e228  call qword ptr [0xF99FFA0]
            // 0xe7e22e  lock dec dword ptr [rdi+0xC]
            // 0xe7e232  jne short 0xE7E244
            void** const ctl2Vtable = static_cast<void**>(ctl2->vtable);
            reinterpret_cast<void (*)(void*)>(ctl2Vtable[0])(ctl2);
            if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&ctl2->weakCount)) == 0) {
                // 0xe7e234..0xe7e244: basic block 12
                // 0xe7e234  mov rax,[rdi]
                // 0xe7e237  mov rax,[rax+8]
                // 0xe7e23b  mov rcx,rdi
                // 0xe7e23e  call qword ptr [0xF99FFA0]
                void** const ctl2VtableFree = static_cast<void**>(ctl2->vtable);
                reinterpret_cast<void (*)(void*)>(ctl2VtableFree[1])(ctl2);
            }
        }
    }

    // 0xe7e244..0xe7e248: basic block 13
    // 0xe7e244  test bl,bl
    // 0xe7e246  je short 0xE7E24D
    if (useFallback) {
        // 0xe7e248..0xe7e24d: basic block 14
        // 0xe7e248  movss xmm6,[rsi+0x5C]
        value = self->fallbackValue;
    }

    // 0xe7e24d..0xe7e25d: basic block 15
    // 0xe7e24d  movaps xmm0,xmm6
    // 0xe7e250  movaps xmm6,[rbp-0x10]
    // 0xe7e254  add rsp,0x58
    // 0xe7e258  pop rbx
    // 0xe7e259  pop rdi
    // 0xe7e25a  pop rsi
    // 0xe7e25b  pop rbp
    // 0xe7e25c  ret
    return value;
}

} // namespace native::helpers
