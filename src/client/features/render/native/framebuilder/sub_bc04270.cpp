// LIFT 0xbc04270 size 0x95 1.26.62.01 sub_bc04270
#include "client/features/render/native/framebuilder/sub_bc04270.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>

namespace native {

// sub_bc04270 (0xbc04270, size 0x95, 1.26.62.01, "pass encode D").
//
// Copies a pass item's handle and two pointers from *a1 to *a0 with addref/release of the
// ref-counted pointer at a1+0x10 (replacing the old one at a0+0x3B8), then tail-calls
// sub_bc61560 (lift set, "custom item submit (key bit 53)"):
//   RCX = *(void**)(*(void**)(a1+0x8) + 0x10)
//   RDX = *(uint16_t*)(*(void**)(a1+0x8) + 8)      (zero-extended)
//   R8  = 0xBC04530 (sub_bc04530, "pass task render-thread body (class D)")
//   R9  = a0
// Return: void (tail call).
//
// Same reads, same writes (value and order), same calls in the same order, same return.
// No null guard or SEH (the original has none; none added here). [V] every instruction
// line below, from the exe disassembly of [0xbc04270, 0xbc04305).

// sub_eea6040 (0xeea6040, class vendor, docs/data/native_boundary.tsv): loader-resolved
// thunk via data slot 0xF99FFA0; its body is `jmp rax`, so the caller loads the target
// pointer into rax first and the thunk tail-calls it with RCX = object.
// Read the slot pointer at call time, exactly as `call qword ptr [0xF99FFA0]` does [V].
namespace {
inline void eea6040_thunk(void* object) {
    using Fn = void (*)(void*);
    Fn fn = reinterpret_cast<Fn>(*reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF99FFA0));
    fn(object);  // RCX = object; thunk tail-calls the rax-loaded target function
}
} // namespace

// 0xbc04270..0xbc04279: push rsi / push rdi / sub rsp,0x28 / mov rsi,rcx   (a0 = rcx)
void sub_bc04270(PassDst* a0, PassSrc* a1) {
    // 0xbc04279 mov rax,[rdx]          ; R a1+0x0
    const std::uint64_t v0 = a1->field_0x0;                   // 0xbc04279 mov rax,[rdx]  ; R PassSrc+0x0
    // 0xbc0427c mov [rcx+0x3A8],rax    ; W a0+0x3A8
    a0->field_0x3A8 = v0;                                     // 0xbc0427c mov [rcx+0x3A8],rax  ; W PassDst+0x3A8
    // 0xbc04283 mov rax,[rdx+0x10]     ; R a1+0x10
    // 0xbc04287 test rax,rax
    // 0xbc0428a je short 0xBC04296     ; taken when a1+0x10 == 0 (nothing added)
    RefCounted* v2 = a1->field_0x10;                          // 0xbc04283 mov rax,[rdx+0x10]  ; R PassSrc+0x10
    if (v2 != nullptr) {                                      // 0xbc04287 test rax,rax / 0xbc0428a je short 0xBC04296
        // 0xbc0428c lock inc dword ptr [rax+8]   ; W (a1+0x10)+0x8  addref
        v2->strong.fetch_add(1u, std::memory_order_seq_cst);  // 0xbc0428c lock inc dword ptr [rax+8]  ; W RefCounted+0x8
    }
    // 0xbc04290 mov rax,[rdx+0x10]     ; R a1+0x10 (reload; rax = v2, or 0 after 0xbc04296 xor eax,eax)
    // 0xbc04294 jmp short 0xBC04298
    // 0xbc04298 mov rcx,[rdx+8]        ; R a1+0x8
    // 0xbc0429c mov [rsi+0x3B0],rcx    ; W a0+0x3B0
    void* v3 = a1->field_0x8;                                 // 0xbc04298 mov rcx,[rdx+8]  ; R PassSrc+0x8
    a0->field_0x3B0 = v3;                                     // 0xbc0429c mov [rsi+0x3B0],rcx  ; W PassDst+0x3B0
    // 0xbc042a3 mov rdi,[rsi+0x3B8]    ; R a0+0x3B8 (old)
    // 0xbc042aa mov [rsi+0x3B8],rax    ; W a0+0x3B8 = v2 (or 0)
    RefCounted* old = a0->field_0x3B8;                        // 0xbc042a3 mov rdi,[rsi+0x3B8]  ; R PassDst+0x3B8
    a0->field_0x3B8 = v2;                                     // 0xbc042aa mov [rsi+0x3B8],rax  ; W PassDst+0x3B8 = PassSrc+0x10
    // 0xbc042b1 test rdi,rdi
    // 0xbc042b4 je short 0xBC042E1     ; taken when old == 0 (nothing released)
    if (old != nullptr) {                                     // 0xbc042b1 test rdi,rdi / 0xbc042b4 je short 0xBC042E1
        // 0xbc042b6 lock dec dword ptr [rdi+8]   ; W old+0x8  strong release
        // 0xbc042ba jne short 0xBC042E1          ; not taken when strong reached 0
        if (old->strong.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {  // 0xbc042b6..0xbc042ba
            // 0xbc042bc mov rax,[rdi]   ; R old+0x0 (vtable)
            // 0xbc042bf mov rax,[rax]   ; R vtable+0x0 (destructor slot), into rax for the thunk's `jmp rax`
            void* old_vtable   = *reinterpret_cast<void**>(old);             // 0xbc042bc mov rax,[rdi]   ; R RefCounted+0x0
            void* old_slot0    = *reinterpret_cast<void**>(old_vtable);      // 0xbc042bf mov rax,[rax]  ; R vtable+0x0
            (void)old_vtable;
            (void)old_slot0;
            // 0xbc042c2 mov rcx,rdi
            // 0xbc042c5 call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040, class vendor boundary thunk; net: old_slot0(old)
            eea6040_thunk(old);                                  // 0xbc042c5 call qword ptr [0xF99FFA0]
            // 0xbc042cb lock dec dword ptr [rdi+0xC]   ; W old+0xC  weak release
            // 0xbc042cf jne short 0xBC042E1          ; not taken when weak reached 0
            if (old->weak.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {  // 0xbc042cb..0xbc042cf
                // 0xbc042d1 mov rax,[rdi]   ; R old+0x0 (vtable)
                // 0xbc042d4 mov rax,[rax+8] ; R vtable+8 (deleter slot)
                void* old_vtable2  = *reinterpret_cast<void**>(old);                                                 // 0xbc042d1 mov rax,[rdi]
                void* old_slot1    = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(old_vtable2) + 8);     // 0xbc042d4 mov rax,[rax+8]
                (void)old_vtable2;
                (void)old_slot1;
                // 0xbc042d8 mov rcx,rdi
                // 0xbc042db call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040; net: old_slot1(old)
                eea6040_thunk(old);                              // 0xbc042db call qword ptr [0xF99FFA0]
            }
        }
    }
    // 0xbc042e1 mov rax,[rsi+0x3B0]   ; R a0+0x3B0 (== v3)
    // 0xbc042e8 mov rcx,[rax+0x10]    ; R v3+0x10 -> RCX
    // 0xbc042ec movzx edx,word ptr [rax+8]  ; R v3+8 -> RDX (zero-extended u16)
    // 0xbc042f0 lea r8,[0xBC04530]    ; R8 = sub_bc04530 address
    // 0xbc042f7 mov r9,rsi            ; R9 = a0
    // 0xbc042fa add rsp,0x28
    // 0xbc042fe pop rdi
    // 0xbc042ff pop rsi
    // 0xbc04300 jmp 0xBC61560         ; tail call
    TaskNode* node = reinterpret_cast<TaskNode*>(v3);
    return sub_bc61560(                                           // 0xbc04300 jmp 0xBC61560  (tail call)
        reinterpret_cast<void*>(node->field_0x10),                // 0xbc042e8 mov rcx,[rax+0x10]   ; RCX = TaskNode+0x10
        static_cast<std::uint16_t>(node->field_0x8),              // 0xbc042ec movzx edx,word ptr [rax+8]  ; RDX = TaskNode+0x8 (zero-extended)
        reinterpret_cast<void*>(0xBC04530ULL),                    // 0xbc042f0 lea r8,[0xBC04530]     ; R8 = sub_bc04530
        a0);                                                      // 0xbc042f7 mov r9,rsi         ; R9 = a0
    // 0xbc04305 int3 padding (function end, not part of sub_bc04270)
}

// Verbatim instructions of the function (matches `rdis dis 0xbc04270 0x95` from the exe,
// machine-checked with tools/sigs/verify_oc.py):
#if 0
0xbc04270  push rsi
0xbc04271  push rdi
0xbc04272  sub rsp,0x28
0xbc04276  mov rsi,rcx
0xbc04279  mov rax,[rdx]
0xbc0427c  mov [rcx+0x3A8],rax
0xbc04283  mov rax,[rdx+0x10]
0xbc04287  test rax,rax
0xbc0428a  je short 0xBC04296
0xbc0428c  lock inc dword ptr [rax+8]
0xbc04290  mov rax,[rdx+0x10]
0xbc04294  jmp short 0xBC04298
0xbc04296  xor eax,eax
0xbc04298  mov rcx,[rdx+8]
0xbc0429c  mov [rsi+0x3B0],rcx
0xbc042a3  mov rdi,[rsi+0x3B8]
0xbc042aa  mov [rsi+0x3B8],rax
0xbc042b1  test rdi,rdi
0xbc042b4  je short 0xBC042E1
0xbc042b6  lock dec dword ptr [rdi+8]
0xbc042ba  jne short 0xBC042E1
0xbc042bc  mov rax,[rdi]
0xbc042bf  mov rax,[rax]
0xbc042c2  mov rcx,rdi
0xbc042c5  call qword ptr [0xF99FFA0]
0xbc042cb  lock dec dword ptr [rdi+0xC]
0xbc042cf  jne short 0xBC042E1
0xbc042d1  mov rax,[rdi]
0xbc042d4  mov rax,[rax+8]
0xbc042d8  mov rcx,rdi
0xbc042db  call qword ptr [0xF99FFA0]
0xbc042e1  mov rax,[rsi+0x3B0]
0xbc042e8  mov rcx,[rax+0x10]
0xbc042ec  movzx edx,word ptr [rax+8]
0xbc042f0  lea r8,[0xBC04530]
0xbc042f7  mov r9,rsi
0xbc042fa  add rsp,0x28
0xbc042fe  pop rdi
0xbc042ff  pop rsi
0xbc04300  jmp 0xBC61560
#endif

static native::Footprint sub_bc04270Footprint(PassDst* a0, PassSrc* /*a1*/) {
    return { { static_cast<void*>(reinterpret_cast<std::uint8_t*>(a0) + 0x3A8), 0x18 } }; // writes a0+0x3A8, a0+0x3B0, a0+0x3B8 [V]
}

LIFT_FN(sub_bc04270, "sub_bc04270", 0xbc04270, sub_bc04270, sub_bc04270Footprint);

} // namespace native
