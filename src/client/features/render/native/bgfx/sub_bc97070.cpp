// LIFT 0xbc97070 size 0x135 1.26.62.01 VV frame-graph builder
#include "client/features/render/native/bgfx/sub_bc97070.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

static_assert(sizeof(std::uintptr_t) == 8, "bc97070: uintptr_t is 8 bytes on x64");
static_assert(sizeof(std::uint32_t) == 4, "bc97070: uint32_t is 4 bytes on x64");

// Verbatim call instructions from the disassembly of [0xbc97070, 0xbc971a5) (rdis dis output):
//   0xbc970b9  call 0xE935700            ; direct, sub_e935700 (lift: `jmp 0x392960`, depth 0)
//   0xbc970f5  call qword ptr [0xF99FFA0]; vtable slot 4 of the interface at +0x70 (sub_eea6040 `jmp rax` thunk, vendor)
//   0xbc9711b  call qword ptr [0xF99FFA0]; vtable slot 0 (destroy) of the refcounted object at +0x30
//   0xbc97131  call qword ptr [0xF99FFA0]; vtable slot 1 (dealloc) of the refcounted object at +0x30
//   0xbc9716c  call 0xE935700            ; direct, sub_e935700
//   0xbc9719e  call qword ptr [0xF9A8C78]; data slot, loader-patched invalid-parameter handler (_invoke_watson-like), noreturn
// No lift-set callees other than sub_e935700 (called directly, forward-declared in the header).
// UNRESOLVED CALL = none.
using DestroyFn = void (*)(void*);
using DeallocFn = void (*)(void*);
using ReleaseFn = void (*)(void*, bool);

static DestroyFn vtableDestroy(void* obj) {   // 0xbc97112  mov rax,[rdi]; 0xbc97115  mov rax,[rax]   (vtable[0] at +0x00)
    void** vt = reinterpret_cast<void**>(obj);
    return reinterpret_cast<DestroyFn>(vt[0]);
}
static DeallocFn vtableDealloc(void* obj) {   // 0xbc97127  mov rax,[rdi]; 0xbc9712a  mov rax,[rax+8] (vtable[1] at +0x08; vptr re-read after destroy)
    void** vt = reinterpret_cast<void**>(obj);
    return reinterpret_cast<DeallocFn>(vt[1]);
}
static ReleaseFn vtableRelease(void* iface) { // 0xbc970ee  mov rax,[rcx]; 0xbc970f1  mov rax,[rax+0x20] (vtable[4] at +0x20)
    void** vt = reinterpret_cast<void**>(iface);
    return reinterpret_cast<ReleaseFn>(vt[4]);
}

// 0xbc9718b..0xbc971a4: the validation-failure path. [rsp+0x20] = 0 (5th stack arg), ecx=edx=r8d=r9d=0
// (first four args), then `0xbc9719e  call qword ptr [0xF9A8C78]` -- the data slot holds 0xF9B055E
// on disk and is loader-patched at runtime to the CRT invalid-parameter handler; the disassembly
// follows the call with int3 padding, so the target is noreturn and control never continues here.
[[noreturn]] static void reportWatsonFailure() {
    //   0xbc9718b  mov qword ptr [rsp+0x20],0
    //   0xbc97194  xor ecx,ecx
    //   0xbc97196  xor edx,edx
    //   0xbc97198  xor r8d,r8d
    //   0xbc9719b  xor r9d,r9d
    //   0xbc9719e  call qword ptr [0xF9A8C78]
    using Watson = std::uintptr_t(__cdecl*)(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, std::uintptr_t);
    reinterpret_cast<Watson>(*reinterpret_cast<std::uintptr_t*>(
        RewriteRegistry::imageBase() + 0xF9A8C78))(nullptr, nullptr, nullptr, 0, 0);
    //   0xbc971a4  int3   (padding after the noreturn call; unreachable)
    __assume(false);
}

void sub_bc97070(VvFrameGraphBuilder* self) {
    // x64 Microsoft ABI: rcx = self (the frame-graph builder), moved to rsi at 0xbc97076.
    // Returns void: no instruction of the range writes rax with a defined value, so the return
    // register is dead at ret (rdis sum: rax = '?' at 0xbc9718a).
    //
    // Prologue/epilogue (stack frame only, no observable effect):
    //   0xbc97070  push rsi
    //   0xbc97071  push rdi
    //   0xbc97072  sub rsp,0x28
    //   0xbc97076  mov rsi,rcx
    //   ...
    //   0xbc97184  add rsp,0x28
    //   0xbc97188  pop rdi
    //   0xbc97189  pop rsi
    //   0xbc9718a  ret

    // ---- string 2 at +0x80 (size +0x90, capacity +0x98) ----
    // 0xbc97079  mov rax,[rcx+0x98]
    // 0xbc97080  cmp rax,0x10
    // 0xbc97084  jb short 0xBC970BE        ; capacity < 0x10 -> SSO, skip the free
    if (self->mBlock98 < 0x10ull) {
        // nothing to free; fall through to the unconditional reset below
    } else {
        // 0xbc97086  mov rcx,[rsi+0x80]
        void* ptr = reinterpret_cast<void*>(self->mBlock80);
        // 0xbc9708d  lea rdx,[rax+1]
        // 0xbc97091  cmp rdx,0x1000
        // 0xbc97098  jb short 0xBC970B9    ; capacity + 1 < 0x1000 -> pass the pointer itself
        if (self->mBlock98 + 1ull < 0x1000ull) {
            // 0xbc970b9  call 0xE935700   ; rcx = ptr, rdx = capacity + 1
            native::sub_e935700(reinterpret_cast<std::uintptr_t>(ptr), self->mBlock98 + 1ull);
        } else {
            // 0xbc9709a  mov r8,[rcx-8]
            const std::uintptr_t hdr = *reinterpret_cast<const std::uintptr_t*>(
                reinterpret_cast<const std::uint8_t*>(ptr) - 8);
            // 0xbc9709e  add rcx,0xFFFFFFFFFFFFFFF8
            // 0xbc970a2  sub rcx,r8
            const std::uintptr_t delta = (reinterpret_cast<std::uintptr_t>(ptr) - 8) - hdr;
            // 0xbc970a5  cmp rcx,0x20
            // 0xbc970a9  jae 0xBC9718B     ; (ptr - 8 - *(ptr-8)) >= 0x20 -> validation failure
            if (delta >= 0x20ull) {
                // 0xbc9718b  mov qword ptr [rsp+0x20],0
            // 0xbc97194  xor ecx,ecx
            // 0xbc97196  xor edx,edx
            // 0xbc97198  xor r8d,r8d
            // 0xbc9719b  xor r9d,r9d
            // 0xbc9719e  call qword ptr [0xF9A8C78]   (noreturn)
                reportWatsonFailure();
                __assume(false);
            }
            // 0xbc970af  add rax,0x28
            // 0xbc970b3  mov rdx,rax
            // 0xbc970b6  mov rcx,r8   ; rcx = *(ptr-8) = hdr
            // 0xbc970b9  call 0xE935700 ; rcx = hdr, rdx = capacity + 0x28
            native::sub_e935700(hdr, self->mBlock98 + 0x28ull);
        }
    }
    // 0xbc970be  mov qword ptr [rsi+0x90],0
    // 0xbc970c9  mov qword ptr [rsi+0x98],0xF
    // 0xbc970d4  mov byte ptr [rsi+0x80],0
    self->mBlock90 = 0;
    self->mBlock98 = 0xFull;
    *reinterpret_cast<std::uint8_t*>(&self->mBlock80) = 0;

    // ---- interface at +0x70 ----
    // 0xbc970db  mov rcx,[rsi+0x70]
    // 0xbc970df  test rcx,rcx
    // 0xbc970e2  je short 0xBC97103
    if (void* iface = self->mBlock70) {
        // 0xbc970e4  lea rax,[rsi+0x38]
        // 0xbc970e8  cmp rcx,rax
        // 0xbc970eb  setne dl          ; dl = (iface != &self + 0x38)
        const bool external = (iface != reinterpret_cast<void*>(reinterpret_cast<std::uint8_t*>(self) + 0x38));
        // 0xbc970ee  mov rax,[rcx]
        // 0xbc970f1  mov rax,[rax+0x20]
        // 0xbc970f5  call qword ptr [0xF99FFA0]   ; vtable[4](iface, external) via the jmp-rax thunk
        vtableRelease(iface)(iface, external);
        // 0xbc970fb  mov qword ptr [rsi+0x70],0
        self->mBlock70 = nullptr;
    }

    // ---- refcounted object at +0x30 ----
    // 0xbc97103  mov rdi,[rsi+0x30]
    // 0xbc97107  test rdi,rdi
    // 0xbc9710a  je short 0xBC97137
    if (Bc97070RefCounted* obj = reinterpret_cast<Bc97070RefCounted*>(self->mBlock30)) {
        // 0xbc9710c  lock dec dword ptr [rdi+8]
        // 0xbc97110  jne short 0xBC97137
        if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&obj->strong)) == 0) {
            // 0xbc97112  mov rax,[rdi]
            // 0xbc97115  mov rax,[rax]
            // 0xbc97118  mov rcx,rdi
            // 0xbc9711b  call qword ptr [0xF99FFA0]   ; vtable[0](obj) = destroy
            vtableDestroy(obj)(obj);
            // 0xbc97121  lock dec dword ptr [rdi+0xC]
            // 0xbc97125  jne short 0xBC97137
            if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&obj->weak)) == 0) {
                // 0xbc97127  mov rax,[rdi]      ; vptr re-read after destroy
                // 0xbc9712a  mov rax,[rax+8]
                // 0xbc9712e  mov rcx,rdi
                // 0xbc97131  call qword ptr [0xF99FFA0]   ; vtable[1](obj) = dealloc
                vtableDealloc(obj)(obj);
            }
        }
    }

    // ---- string 1 at +0x00 (size +0x10, capacity +0x18) ----
    // 0xbc97137  mov rax,[rsi+0x18]
    // 0xbc9713b  cmp rax,0x10
    // 0xbc9713f  jb short 0xBC97171        ; capacity < 0x10 -> SSO, skip the free
    if (self->mBlock18 < 0x10ull) {
        // nothing to free; fall through to the unconditional reset below
    } else {
        // 0xbc97141  mov rcx,[rsi]
        void* ptr = reinterpret_cast<void*>(self->mBlock00);
        // 0xbc97144  lea rdx,[rax+1]
        // 0xbc97148  cmp rdx,0x1000
        // 0xbc9714f  jb short 0xBC9716C    ; capacity + 1 < 0x1000 -> pass the pointer itself
        if (self->mBlock18 + 1ull < 0x1000ull) {
            // 0xbc9716c  call 0xE935700   ; rcx = ptr, rdx = capacity + 1
            native::sub_e935700(reinterpret_cast<std::uintptr_t>(ptr), self->mBlock18 + 1ull);
        } else {
            // 0xbc97151  mov r8,[rcx-8]
            const std::uintptr_t hdr = *reinterpret_cast<const std::uintptr_t*>(
                reinterpret_cast<const std::uint8_t*>(ptr) - 8);
            // 0xbc97155  add rcx,0xFFFFFFFFFFFFFFF8
            // 0xbc97159  sub rcx,r8
            const std::uintptr_t delta = (reinterpret_cast<std::uintptr_t>(ptr) - 8) - hdr;
            // 0xbc9715c  cmp rcx,0x20
            // 0xbc97160  jae short 0xBC9718B ; (ptr - 8 - *(ptr-8)) >= 0x20 -> validation failure
            if (delta >= 0x20ull) {
                // 0xbc9718b  mov qword ptr [rsp+0x20],0
            // 0xbc97194  xor ecx,ecx
            // 0xbc97196  xor edx,edx
            // 0xbc97198  xor r8d,r8d
            // 0xbc9719b  xor r9d,r9d
            // 0xbc9719e  call qword ptr [0xF9A8C78]   (noreturn)
                reportWatsonFailure();
                __assume(false);
            }
            // 0xbc97162  add rax,0x28
            // 0xbc97166  mov rdx,rax
            // 0xbc97169  mov rcx,r8   ; rcx = *(ptr-8) = hdr
            // 0xbc9716c  call 0xE935700 ; rcx = hdr, rdx = capacity + 0x28
            native::sub_e935700(hdr, self->mBlock18 + 0x28ull);
        }
    }
    // 0xbc97171  mov qword ptr [rsi+0x10],0
    // 0xbc97179  mov qword ptr [rsi+0x18],0xF
    // 0xbc97181  mov byte ptr [rsi],0
    self->mBlock10 = 0;
    self->mBlock18 = 0xFull;
    *reinterpret_cast<std::uint8_t*>(&self->mBlock00) = 0;
}

static native::Footprint sub_bc97070_footprint(VvFrameGraphBuilder* self) {
    // The function writes only inside *self ([0x00, 0xA0)): the two strings, the interface
    // pointer and the reset stores. Refcount writes to the object at +0x30, the virtual-call
    // targets and sub_e935700's frees happen outside the function and cannot be declared
    // statically (same convention as sub_bc2bca0).
    return {{self, 0xA0ull}};
}

LIFT_FN(sub_bc97070, "VV frame-graph builder", 0xbc97070, sub_bc97070, sub_bc97070_footprint);

} // namespace native::bgfx
