// LIFT 0xbcaa640 size 0x135 1.26.62.01 sub_bcaa640
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bcaa640.h"

#include <cstddef>
#include <cstdint>
#include <intrin.h>

// Layout assertions for every struct offset this function touches (defined in
// sub_bcaa640.h; repeated here so liftcheck finds them in the source file).
static_assert(offsetof(native::bgfx::sub_bcaa640_state, field_0x00) == 0x00, "sub_0xbcaa640: self+0x00");
static_assert(offsetof(native::bgfx::sub_bcaa640_state, field_0x10) == 0x10, "sub_0xbcaa640: self+0x10");
static_assert(offsetof(native::bgfx::sub_bcaa640_state, field_0x18) == 0x18, "sub_0xbcaa640: self+0x18");
static_assert(offsetof(native::bgfx::sub_bcaa640_state, field_0x28) == 0x28, "sub_0xbcaa640: self+0x28");
static_assert(offsetof(native::bgfx::sub_bcaa640_state, field_0x78) == 0x78, "sub_0xbcaa640: self+0x78");
static_assert(offsetof(native::bgfx::sub_bcaa640_state, field_0x88) == 0x88, "sub_0xbcaa640: self+0x88");
static_assert(offsetof(native::bgfx::sub_bcaa640_state, field_0x98) == 0x98, "sub_0xbcaa640: self+0x98");
static_assert(offsetof(native::bgfx::sub_bcaa640_state, field_0xA0) == 0xA0, "sub_0xbcaa640: self+0xA0");
static_assert(sizeof(native::bgfx::sub_bcaa640_state) == 0xA8, "sub_0xbcaa640 object size");

// Reversed from the disassembly of [0xbcaa640, 0xbcaa775), Minecraft Windows 1.26.62.01
// (rdis dis output, docs/progress/pre/bcaa640_dis.txt). Every block carries the
// instruction range it implements as // 0xA..0xB beside it; every call is quoted
// verbatim in the verbatim log below.
//
// Boundaries and lift-set callees:
//   sub_e935700 x2 is a lift-set callee (docs/data/native_boundary.tsv line 505,
//   class lift), declared in sub_bcaa640.h and called as plain C++.
//   [0xF99FFA0] (sub_eea6040, `jmp rax` vtable thunk, boundary.tsv line 506) is an
//   indirect virtual call whose target (vtable slot) the original already loaded into
//   rax; modelled as vtable slot calls through function pointers (same convention as
//   sub_bc8c720).
//   [0xF9A8C78] (_invoke_watson IAT slot, read at VA 0x14F9A8C78 at call time) is
//   modelled as a function-pointer call through the slot (boundary hard rule: indirect
//   call through a data slot).
// Verbatim call instructions from the disassembly of [0xbcaa640, 0xbcaa775)
// (rdis dis output, copied verbatim, two spaces after the address):
//   0xbcaa689  call 0xE935700
//   0xbcaa6c5  call qword ptr [0xF99FFA0]
//   0xbcaa6eb  call qword ptr [0xF99FFA0]
//   0xbcaa701  call qword ptr [0xF99FFA0]
//   0xbcaa73c  call 0xE935700
//   0xbcaa76e  call qword ptr [0xF9A8C78]
// UNRESOLVED CALL = none: every target above is either a lift-set callee (sub_e935700)
// or an indirect call through a documented data slot ([0xF99FFA0] vtable thunk,
// [0xF9A8C78] _invoke_watson IAT slot).

namespace native::bgfx {

using sub_bcaa640_state = ::native::bgfx::sub_bcaa640_state;

// [0xF99FFA0] (sub_eea6040) is a `jmp rax` thunk, so each
// `call qword ptr [0xF99FFA0]` above is an indirect virtual call whose target
// (vtable slot) the original already loaded into rax. Reads: [obj] (vtable pointer)
// and [vtable + slot*8]; call: target(obj) with rcx = obj.
static void vtableCallSlot4(void* obj) {
    void** vt = *reinterpret_cast<void***>(obj);
    reinterpret_cast<void (*)(void*)>(vt[4])(obj);
}
static void vtableCallSlot0(void* obj) {
    void** vt = *reinterpret_cast<void***>(obj);
    reinterpret_cast<void (*)(void*)>(vt[0])(obj);
}
static void vtableCallSlot1(void* obj) {
    void** vt = *reinterpret_cast<void***>(obj);
    reinterpret_cast<void (*)(void*)>(vt[1])(obj);
}

// sub_0xbcaa640(sub_bcaa640_state* self = rcx) -> void
void sub_bcaa640(sub_bcaa640_state* self) {
    using State = sub_bcaa640_state;

    // 0xbcaa640..0xbcaa656
    // 0xbcaa640  push rsi ; 0xbcaa641  push rdi ; 0xbcaa642  sub rsp,0x28 ;
    // 0xbcaa646  mov rsi,rcx ; 0xbcaa649  mov rax,[rcx+0xA0] ;
    // 0xbcaa650  cmp rax,0x10 ; 0xbcaa654  jb short 0xBCAA68E
    uint64_t capA = self->field_0xA0;                          // 0xbcaa649 mov rax,[rcx+0xA0]
    if (capA >= 0x10) {                                        // 0xbcaa650 cmp rax,0x10 ; 0xbcaa654 jb short 0xBCAA68E
        // 0xbcaa656..0xbcaa689
        // 0xbcaa656  mov rcx,[rsi+0x88] ; 0xbcaa65d  lea rdx,[rax+1] ;
        // 0xbcaa661  cmp rdx,0x1000 ; 0xbcaa668  jb short 0xBCAA689
        void* ptrA = self->field_0x88;                         // 0xbcaa656 mov rcx,[rsi+0x88]
        if (capA + 1 < 0x1000) {                               // 0xbcaa65d lea rdx,[rax+1]; 0xbcaa661 cmp rdx,0x1000; 0xbcaa668 jb short 0xBCAA689
            ::native::sub_e935700((uint64_t)ptrA, capA + 1);   // 0xbcaa689  call 0xE935700
        } else {
            // 0xbcaa66a  mov r8,[rcx-8] ; 0xbcaa66e  add rcx,0xFFFFFFFFFFFFFFF8 ;
            // 0xbcaa672  sub rcx,r8 ; 0xbcaa675  cmp rcx,0x20 ;
            // 0xbcaa679  jae 0xBCAA75B
            uint64_t hdr = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(ptrA) - 8);  // 0xbcaa66a mov r8,[rcx-8]
            uint64_t delta = (reinterpret_cast<uintptr_t>(ptrA) - 8) - hdr;                    // 0xbcaa66e add rcx,0xFFFFFFFFFFFFFFF8; 0xbcaa672 sub rcx,r8
            if (delta >= 0x20) {                               // 0xbcaa675 cmp rcx,0x20 ; 0xbcaa679 jae 0xBCAA75B
                // 0xbcaa75b..0xbcaa775: zero [rsp+0x20]/ecx/edx/r8d/r9d then
                // 0xbcaa76e  call qword ptr [0xF9A8C78] -> _invoke_watson (noreturn; int3 padding at 0xbcaa774)
                using Watson_t = void (__cdecl*)(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t);
                auto watson = reinterpret_cast<Watson_t>(*reinterpret_cast<uintptr_t*>(0x14F9A8C78));
                *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(self) + 0x20) = 0;
                watson(nullptr, nullptr, nullptr, 0, 0);
                __assume(false);
            }
            // 0xbcaa67f  add rax,0x28 ; 0xbcaa683  mov rdx,rax ;
            // 0xbcaa686  mov rcx,r8 ; 0xbcaa689  call 0xE935700
            ::native::sub_e935700(hdr, capA + 0x28);          // 0xbcaa689  call 0xE935700
        }
    }

    // 0xbcaa68e..0xbcaa6ab
    // 0xbcaa68e  mov qword ptr [rsi+0x98],0 ; 0xbcaa699  mov qword ptr [rsi+0xA0],0xF ;
    // 0xbcaa6a4  mov byte ptr [rsi+0x88],0
    self->field_0x98 = 0;                                     // 0xbcaa68e mov qword ptr [rsi+0x98],0
    self->field_0xA0 = 0xF;                                   // 0xbcaa699 mov qword ptr [rsi+0xA0],0xF
    *reinterpret_cast<uint8_t*>(&self->field_0x88) = 0;       // 0xbcaa6a4 mov byte ptr [rsi+0x88],0

    // 0xbcaa6ab..0xbcaa6cb
    // 0xbcaa6ab  mov rcx,[rsi+0x78] ; 0xbcaa6af  test rcx,rcx ;
    // 0xbcaa6b2  je short 0xBCAA6D3
    void* objB = self->field_0x78;                            // 0xbcaa6ab mov rcx,[rsi+0x78]
    if (objB != 0) {                                          // 0xbcaa6af test rcx,rcx ; 0xbcaa6b2 je short 0xBCAA6D3
        // 0xbcaa6b4  lea rax,[rsi+0x40] ; 0xbcaa6b8  cmp rcx,rax ;
        // 0xbcaa6bb  setne dl  (dl is dead: never read afterwards)
        // 0xbcaa6be  mov rax,[rcx] ; 0xbcaa6c1  mov rax,[rax+0x20] ;
        // 0xbcaa6c5  call qword ptr [0xF99FFA0]  -> sub_eea6040 jmp-rax thunk => vt[4](objB)
        void** vtB = *reinterpret_cast<void***>(objB);          // 0xbcaa6be mov rax,[rcx]
        vtableCallSlot4(objB);                                 // 0xbcaa6c1 mov rax,[rax+0x20]; 0xbcaa6c5 call qword ptr [0xF99FFA0]
    }
    self->field_0x78 = 0;                                     // 0xbcaa6cb mov qword ptr [rsi+0x78],0

    // 0xbcaa6d3..0xbcaa707
    // 0xbcaa6d3  mov rdi,[rsi+0x28] ; 0xbcaa6d7  test rdi,rdi ;
    // 0xbcaa6da  je short 0xBCAA707
    void* objA = self->field_0x28;                            // 0xbcaa6d3 mov rdi,[rsi+0x28]
    if (objA != 0) {                                          // 0xbcaa6d7 test rdi,rdi ; 0xbcaa6da je short 0xBCAA707
        // 0xbcaa6dc  lock dec dword ptr [rdi+8] ;
        // 0xbcaa6e0  jne short 0xBCAA707
        if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(reinterpret_cast<uint8_t*>(objA) + 8)) == 0) {  // 0xbcaa6dc lock dec [rdi+8]; 0xbcaa6e0 jne short 0xBCAA707
            // 0xbcaa6e2  mov rax,[rdi] ; 0xbcaa6e5  mov rax,[rax] ;
            // 0xbcaa6e8  mov rcx,rdi ;
            // 0xbcaa6eb  call qword ptr [0xF99FFA0]  -> vt[0](objA)
            void** vtA0 = *reinterpret_cast<void***>(objA);   // 0xbcaa6e2 mov rax,[rdi]
            reinterpret_cast<void (*)(void*)>(vtA0[0])(objA);  // 0xbcaa6e5 mov rax,[rax]; 0xbcaa6eb call qword ptr [0xF99FFA0]
            // 0xbcaa6f1  lock dec dword ptr [rdi+0xC] ;
            // 0xbcaa6f5  jne short 0xBCAA707
            if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(reinterpret_cast<uint8_t*>(objA) + 0xC)) == 0) {  // 0xbcaa6f1 lock dec [rdi+0xC]; 0xbcaa6f5 jne short 0xBCAA707
                // 0xbcaa6f7  mov rax,[rdi] ; 0xbcaa6fa  mov rax,[rax+8] ;
                // 0xbcaa6fe  mov rcx,rdi ;
                // 0xbcaa701  call qword ptr [0xF99FFA0]  -> vt[1](objA)
                void** vtA1 = *reinterpret_cast<void***>(objA);  // 0xbcaa6f7 mov rax,[rdi]
                reinterpret_cast<void (*)(void*)>(vtA1[1])(objA);  // 0xbcaa6fa mov rax,[rax+8]; 0xbcaa701 call qword ptr [0xF99FFA0]
            }
        }
    }

    // 0xbcaa707..0xbcaa75a
    // 0xbcaa707  mov rax,[rsi+0x18] ; 0xbcaa70b  cmp rax,0x10 ;
    // 0xbcaa70f  jb short 0xBCAA741
    uint64_t capB = self->field_0x18;                          // 0xbcaa707 mov rax,[rsi+0x18]
    if (capB >= 0x10) {                                        // 0xbcaa70b cmp rax,0x10 ; 0xbcaa70f jb short 0xBCAA741
        // 0xbcaa711  mov rcx,[rsi] ; 0xbcaa714  lea rdx,[rax+1] ;
        // 0xbcaa718  cmp rdx,0x1000 ; 0xbcaa71f  jb short 0xBCAA73C
        void* ptrB = self->field_0x00;                         // 0xbcaa711 mov rcx,[rsi]
        if (capB + 1 < 0x1000) {                               // 0xbcaa714 lea rdx,[rax+1]; 0xbcaa718 cmp rdx,0x1000; 0xbcaa71f jb short 0xBCAA73C
            ::native::sub_e935700((uint64_t)ptrB, capB + 1);   // 0xbcaa73c  call 0xE935700
        } else {
            // 0xbcaa721  mov r8,[rcx-8] ; 0xbcaa725  add rcx,0xFFFFFFFFFFFFFFF8 ;
            // 0xbcaa729  sub rcx,r8 ; 0xbcaa72c  cmp rcx,0x20 ;
            // 0xbcaa730  jae short 0xBCAA75B
            uint64_t hdrB = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(ptrB) - 8);  // 0xbcaa721 mov r8,[rcx-8]
            uint64_t deltaB = (reinterpret_cast<uintptr_t>(ptrB) - 8) - hdrB;                 // 0xbcaa725 add rcx,0xFFFFFFFFFFFFFFF8; 0xbcaa729 sub rcx,r8
            if (deltaB >= 0x20) {                          // 0xbcaa72c cmp rcx,0x20 ; 0xbcaa730 jae short 0xBCAA75B
                // 0xbcaa75b..0xbcaa775: zero [rsp+0x20]/ecx/edx/r8d/r9d then
                // 0xbcaa76e  call qword ptr [0xF9A8C78] -> _invoke_watson (noreturn; int3 padding at 0xbcaa774)
                using Watson_t = void (__cdecl*)(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t);
                auto watson = reinterpret_cast<Watson_t>(*reinterpret_cast<uintptr_t*>(0x14F9A8C78));
                *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(self) + 0x20) = 0;
                watson(nullptr, nullptr, nullptr, 0, 0);
                __assume(false);
            }
            // 0xbcaa732  add rax,0x28 ; 0xbcaa736  mov rdx,rax ;
            // 0xbcaa739  mov rcx,r8 ; 0xbcaa73c  call 0xE935700
            ::native::sub_e935700(hdrB, capB + 0x28);     // 0xbcaa73c  call 0xE935700
        }
    }

    // 0xbcaa741..0xbcaa75a
    // 0xbcaa741  mov qword ptr [rsi+0x10],0 ; 0xbcaa749  mov qword ptr [rsi+0x18],0xF ;
    // 0xbcaa751  mov byte ptr [rsi],0
    // 0xbcaa754  add rsp,0x28 ; 0xbcaa758  pop rdi ; 0xbcaa759  pop rsi ; 0xbcaa75a  ret
    self->field_0x10 = 0;                                 // 0xbcaa741 mov qword ptr [rsi+0x10],0
    self->field_0x18 = 0xF;                               // 0xbcaa749 mov qword ptr [rsi+0x18],0xF
    *reinterpret_cast<uint8_t*>(&self->field_0x00) = 0;   // 0xbcaa751 mov byte ptr [rsi],0
}

static native::Footprint sub_bcaa640_footprint(sub_bcaa640_state* self) {
    // Conservative: every byte written to *self. Refcount writes to other objects
    // (via the virtual calls above) are outside this footprint, same as the
    // original's out-of-function side effects; they cannot be declared statically.
    return { { self, 0xA8 } };
}

} // namespace native::bgfx

LIFT_FN(sub_bcaa640, "sub_bcaa640", 0xbcaa640, sub_bcaa640, sub_bcaa640_footprint);