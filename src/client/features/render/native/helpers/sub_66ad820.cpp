// LIFT 0x66ad820 size 0x126 1.26.62.01 sub_66ad820
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_66ad820.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

// Layout assertions for the lifted state: every field of sub_66ad820_state and
// sub_66ad820_refcounted that the function reads or writes has an offsetof static_assert
// (also repeated in sub_66ad820.h); the sizeof bounds pin the observed footprint.
static_assert(offsetof(sub_66ad820_state, mBlock08) == 0x08, "sub_66ad820 layout: mBlock08 at +0x08");
static_assert(offsetof(sub_66ad820_state, mBlock10) == 0x10, "sub_66ad820 layout: mBlock10 at +0x10");
static_assert(offsetof(sub_66ad820_state, mBlock18) == 0x18, "sub_66ad820 layout: mBlock18 at +0x18");
static_assert(offsetof(sub_66ad820_state, mBlock28) == 0x28, "sub_66ad820 layout: mBlock28 at +0x28");
static_assert(offsetof(sub_66ad820_state, mBlock38) == 0x38, "sub_66ad820 layout: mBlock38 at +0x38");
static_assert(offsetof(sub_66ad820_state, mBlock48) == 0x48, "sub_66ad820 layout: mBlock48 at +0x48");
static_assert(offsetof(sub_66ad820_state, mBlock50) == 0x50, "sub_66ad820 layout: mBlock50 at +0x50");
static_assert(offsetof(sub_66ad820_state, mBlock58) == 0x58, "sub_66ad820 layout: mBlock58 at +0x58");
static_assert(sizeof(sub_66ad820_state) >= 0x60, "sub_66ad820 layout: sizeof lower bound");
static_assert(offsetof(sub_66ad820_refcounted, vptr) == 0x00, "sub_66ad820 layout: refcounted vptr at +0x00");
static_assert(offsetof(sub_66ad820_refcounted, strong) == 0x08, "sub_66ad820 layout: refcounted strong at +0x08");
static_assert(offsetof(sub_66ad820_refcounted, weak) == 0x0C, "sub_66ad820 layout: refcounted weak at +0x0C");
static_assert(sizeof(sub_66ad820_refcounted) == 0x10, "sub_66ad820 layout: refcounted sizeof");

namespace native::helpers {

// Verbatim call instructions from the disassembly of [0x66ad820, 0x66ad946) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x66ad862  call 0xE935700
0x66ad88d  call qword ptr [0xF99FFA0]
0x66ad8a3  call qword ptr [0xF99FFA0]
0x66ad8c1  call qword ptr [0xF99FFA0]
0x66ad8d7  call qword ptr [0xF99FFA0]
0x66ad912  call 0xE935700
0x66ad93f  call qword ptr [0xF9A8C78]
#endif

// 0x66ad92c..0x66ad946: validation failure. 0x66ad92c mov qword ptr [rsp+0x20],0 (5th stack arg);
// xor ecx,ecx; xor edx,edx; xor r8d,r8d; xor r9d,r9d; 0x66ad93f call qword ptr [0xF9A8C78] -- the
// data slot is loader-patched at runtime; int3 padding follows (0x66ad945), so the target is
// noreturn and control never continues here.
[[noreturn]] static void reportValidationFailure() {
    //   0x66ad92c  mov qword ptr [rsp+0x20],0
    //   0x66ad935  xor ecx,ecx
    //   0x66ad937  xor edx,edx
    //   0x66ad939  xor r8d,r8d
    //   0x66ad93c  xor r9d,r9d
    //   0x66ad93f  call qword ptr [0xF9A8C78]
    using Watson = std::uintptr_t(__cdecl*)(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, std::uintptr_t);
    reinterpret_cast<Watson>(*reinterpret_cast<std::uintptr_t*>(
        RewriteRegistry::imageBase() + 0xF9A8C78))(nullptr, nullptr, nullptr, 0, 0);
    //   0x66ad945  int3   (unreachable)
    __assume(false);
}

// 0x66ad88d / 0x66ad8a3 / 0x66ad8d7 call qword ptr [0xF99FFA0]; [data_f99ffa0] = sub_eea6040.
// Read the slot at call time and tail-call it with RCX = obj, exactly like the exe.
static void callThunk0xF99FFA0(void* obj) {   // rcx = obj at 0x66ad88a/0x66ad8a0/0x66ad8d4
    auto thunk = reinterpret_cast<void (*)(void*)>(
        *reinterpret_cast<const std::uintptr_t*>(
            RewriteRegistry::imageBase() + 0xF99FFA0));
    thunk(obj);
}

// 0x66ad884 mov rax,[rdi]; 0x66ad887 mov rax,[rax]  (dead vtable reads before the slot-0 call)
static void deadVtableReadsSlot0(void* obj) {
    const std::uint64_t vptr = *reinterpret_cast<const std::uint64_t*>(obj);   // 0x66ad884 mov rax,[rdi]
    (void)vptr;
    (void)*reinterpret_cast<const std::uint64_t*>(vptr);                        // 0x66ad887 mov rax,[rax]
}

// 0x66ad899 mov rax,[rdi]; 0x66ad89c mov rax,[rax+8] (dead vtable reads before the slot-1 call)
static void deadVtableReadsSlot1(void* obj) {
    (void)*reinterpret_cast<const std::uint64_t*>(obj);                         // 0x66ad899 mov rax,[rdi]
    (void)*reinterpret_cast<const std::uint64_t*>(                              // 0x66ad89c mov rax,[rax+8]
        reinterpret_cast<const std::uint8_t*>(obj) + 8);
}

// Release a refcounted object (blocks 5-8 for mBlock38, blocks 9-12 for mBlock28).
// 0x66ad87e/0x66ad8b2 lock dec [obj+0x8]; if 0: dead reads, thunk call (slot 0),
//                   0x66ad893/0x66ad8c7 lock dec [obj+0xC]; if 0: dead reads, thunk call (slot 1).
static void releaseRefcounted(sub_66ad820_refcounted* obj) {
    // 0x66ad87e lock dec dword ptr [rdi+8]; 0x66ad882 jne -> skip
    if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&obj->strong)) == 0) {
        deadVtableReadsSlot0(obj);          // 0x66ad884 mov rax,[rdi]; 0x66ad887 mov rax,[rax]
        // 0x66ad88a mov rcx,rdi; 0x66ad88d call qword ptr [0xF99FFA0] (slot 0 = destroy)
        callThunk0xF99FFA0(obj);
        // 0x66ad893 lock dec dword ptr [rdi+0xC]; 0x66ad897 jne -> skip
        if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&obj->weak)) == 0) {
            deadVtableReadsSlot1(obj);      // 0x66ad899 mov rax,[rdi]; 0x66ad89c mov rax,[rax+8]
            // 0x66ad8a0 mov rcx,rdi; 0x66ad8a3 call qword ptr [0xF99FFA0] (slot 1 = dealloc)
            callThunk0xF99FFA0(obj);
        }
    }
}

// Release a heap buffer described by (ptr, end): size = end - ptr.
// 0x66ad832..0x66ad85e (mBlock48/mBlock58) and 0x66ad8e6..0x66ad90e (mBlock08/mBlock18).
// if size <u 0x1000: pass the pointer itself; otherwise validate the heap cookie at ptr-8:
// (ptr - 8) - *(ptr - 8) must be <u 0x20, else the validation-failure path (noreturn) is taken;
// pass *(ptr - 8) as the argument. sub_e935700 ignores RDX (sub_392960: 0x392972 mov rdx,rcx), so
// only RCX is observable at the call.
static void releaseBuffer(void* ptr, std::uintptr_t end) {   // rcx = ptr at entry of the call path
    const std::uintptr_t size = end - reinterpret_cast<std::uintptr_t>(ptr);
    void* arg = ptr;                                              // small buffer: rcx = ptr
    if (!(size < 0x1000ull)) {
        const std::uintptr_t hdr = *reinterpret_cast<const std::uintptr_t*>(                  // 0x66ad842/0x66ad8f6 mov rax,[rcx-8]
            reinterpret_cast<const std::uint8_t*>(ptr) - 8);
        const std::uintptr_t delta = (reinterpret_cast<std::uintptr_t>(ptr) - 8) - hdr;       // add rcx,-8; sub rcx,rax
        if (delta >= 0x20ull) {                                   // cmp rcx,0x20; jae -> validation failure
            // 0x66ad92c mov qword ptr [rsp+0x20],0; xor ecx,edx,r8d,r9d; call [0xF9A8C78] (noreturn)
            reportValidationFailure();
            __assume(false);
        }
        arg = reinterpret_cast<void*>(hdr);                       // add rdx,0x27; mov rcx,rax -> rcx = hdr
    }
    // 0x66ad862 / 0x66ad912 call 0xE935700 (rcx = arg; sub_392960 ignores RDX)
    native::sub_e935700(arg);
}

void sub_66ad820(sub_66ad820_state* self) {
    // x64 Microsoft ABI: rcx = self, copied to rsi at 0x66ad826 (mov rsi,rcx).
    // Returns void: rax is written only by dead vtable reads (0x66ad884/0x66ad887/0x66ad899/
    // 0x66ad8cd) and by sub_e935700, whose result is never read, so rax is dead at ret
    // (0x66ad92b).
    //
    // Prologue/epilogue (stack frame only, no observable effect):
    //   0x66ad820  push rsi
    //   0x66ad821  push rdi
    //   0x66ad822  sub rsp,0x28
    //   0x66ad826  mov rsi,rcx
    //   ...
    //   0x66ad925  add rsp,0x28
    //   0x66ad929  pop rdi
    //   0x66ad92a  pop rsi
    //   0x66ad92b  ret

    // 0x66ad820..0x66ad875: blocks 0-4 -- release heap buffer mBlock48/mBlock58
    // 0x66ad829  mov rcx,[rcx+0x48]; 0x66ad82d test rcx,rcx; 0x66ad830 je short -> 0x66AD875
    if (self->mBlock48 != nullptr) {
        releaseBuffer(self->mBlock48, self->mBlock58);
        // 0x66ad85e lea rdi,[rsi+0x48]        rdi = &self->mBlock48
        // 0x66ad862 call 0xE935700            (inside releaseBuffer)
        // 0x66ad867 xorps xmm0,xmm0
        // 0x66ad86a movups [rdi],xmm0         mBlock48 = 0, mBlock50 = 0  (16-byte store)
        // 0x66ad86d mov qword ptr [rdi+0x10],0   mBlock58 = 0
        self->mBlock48 = nullptr;
        self->mBlock50 = 0;
        self->mBlock58 = 0;
    }
    // 0x66ad875..0x66ad8a9: blocks 5-8 -- release refcounted object mBlock38
    // 0x66ad875 mov rdi,[rsi+0x38]; 0x66ad879 test rdi,rdi; 0x66ad87c je short -> 0x66AD8A9
    if (self->mBlock38 != nullptr) {
        releaseRefcounted(reinterpret_cast<sub_66ad820_refcounted*>(self->mBlock38));
    }
    // 0x66ad8a9..0x66ad8dd: blocks 9-12 -- release refcounted object mBlock28
    // 0x66ad8a9 mov rdi,[rsi+0x28]; 0x66ad8ad test rdi,rdi; 0x66ad8b0 je short -> 0x66AD8DD
    if (self->mBlock28 != nullptr) {
        releaseRefcounted(reinterpret_cast<sub_66ad820_refcounted*>(self->mBlock28));
    }
    // 0x66ad8dd..0x66ad925: blocks 13-17 -- release heap buffer mBlock08/mBlock18
    // 0x66ad8dd mov rcx,[rsi+8]; 0x66ad8e1 test rcx,rcx; 0x66ad8e4 je short -> 0x66AD925
    if (self->mBlock08 != nullptr) {
        releaseBuffer(self->mBlock08, self->mBlock18);
        // 0x66ad90e add rsi,8                 rsi = &self->mBlock08
        // 0x66ad912 call 0xE935700            (inside releaseBuffer)
        // 0x66ad917 xorps xmm0,xmm0
        // 0x66ad91a movups [rsi],xmm0         mBlock08 = 0, mBlock10 = 0
        // 0x66ad91d mov qword ptr [rsi+0x10],0   mBlock18 = 0
        self->mBlock08 = nullptr;
        self->mBlock10 = 0;
        self->mBlock18 = 0;
    }
    // 0x66ad925..0x66ad92c: block 18 -- epilogue
    // 0x66ad925 add rsp,0x28; 0x66ad929 pop rdi; 0x66ad92a pop rsi; 0x66ad92b ret
}

LIFT_FN(sub_66ad820, "sub_66ad820", 0x66ad820, sub_66ad820, nullptr);

// Block 19 (0x66ad92c..0x66ad946) is the validation-failure path: it calls data slot
// [0xF9A8C78] (noreturn) and never reaches block 18; emitted by reportValidationFailure().

} // namespace native::helpers
