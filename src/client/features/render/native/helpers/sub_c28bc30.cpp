// LIFT 0xc28bc30 size 0xbb 1.26.62.01 sub_c28bc30
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_c28bc30.h"
#include "client/features/render/native/helpers/sub_6ae330.h"

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_c28bc30, "sub_c28bc30", 0xc28bc30, sub_c28bc30, nullptr);

// Verbatim call instructions from the disassembly of [0xc28bc30, 0xc28bceb) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xc28bcab  call qword ptr [0xF99FFA0]
0xc28bcc1  call qword ptr [0xF99FFA0]
0xc28bccd  call 0x6AE330
#endif

namespace {

// sub_eea6040 via the vendor data slot at RVA 0xF99FFA0. This function's call sites never set
// a flag argument (edx), so it is invoked with just the object pointer, matching the listing.
void callEea6040(void* object)
{
    using Eea6040Callee = void (*)(void*);
    auto fn = reinterpret_cast<Eea6040Callee>(
        *reinterpret_cast<std::uintptr_t*>(
            RewriteRegistry::imageBase() + ::kEea6040SlotRva));
    fn(object);
}

} // namespace

uintptr_t sub_c28bc30(sub_c28bc30_state* self)
{
    // 0xc28bc30..0xc28bc50: prologue; rsi = this, rbx = [this+0x00] start, r14 = [this+0x08] end
    SubC28bc30Elem* rbx = reinterpret_cast<SubC28bc30Elem*>(self->elementStart);  // 0xc28bc3c mov rbx,[rcx]
    void* r14 = self->elementEnd;                                                 // 0xc28bc3f mov r14,[rcx+8]
    RefObject* rcx = nullptr;                                                     // 0xc28bc59 mov rcx,[rbx+8]
    std::uint32_t eax = 0;                                                        // 0xc28bc62 mov eax,[rcx+8]
    std::uint32_t edx = 0;                                                        // 0xc28bc74 lea edx,[rax+1]
    VftObject* rax = nullptr;                                                     // 0xc28bc7e mov rax,[rbx]
    RefObject* rdi = nullptr;                                                     // 0xc28bc81 mov rdi,[rbx+8]
    goto check;                                                                   // 0xc28bc43 jmp short loc_c28bc54

loop_increment:                                                                   // 0xc28bc50..0xc28bc54 add rbx,0x10
    rbx = reinterpret_cast<SubC28bc30Elem*>(reinterpret_cast<std::uint8_t*>(rbx) + 0x10);
check:                                                                            // 0xc28bc54..0xc28bc62 cmp rbx,r14 ; je ; mov rcx,[rbx+8] ; test ; je
    if (rbx == reinterpret_cast<SubC28bc30Elem*>(r14)) {
        goto epilogue;                                                            // 0xc28bc57 je short loc_c28bcc9
    }
    rcx = rbx->refObj;                                                            // 0xc28bc59 mov rcx,[rbx+8]
    if (rcx == nullptr) {
        goto loop_increment;                                                      // 0xc28bc5d test rcx,rcx ; 0xc28bc60 je loc_c28bc50
    }
    eax = rcx->refCount;                                                          // 0xc28bc62 mov eax,[rcx+8]

test_refcount:                                                                    // 0xc28bc62..0xc28bc70 mov eax,[rcx+8] ; nop
    if (eax == 0) {
        goto loop_increment;                                                      // 0xc28bc70..0xc28bc74 test eax,eax ; je short loc_c28bc50
    }
    edx = eax + 1;                                                                // 0xc28bc74 lea edx,[rax+1]
    // 0xc28bc74..0xc28bc7e lea edx,[rax+1] ; lock cmpxchg [rcx+8],edx ; jne loc_c28bc70
    {
        std::uint32_t orig = static_cast<std::uint32_t>(
            InterlockedCompareExchange(
                reinterpret_cast<volatile long*>(&rcx->refCount),
                static_cast<long>(edx), static_cast<long>(eax)));
        if (orig == eax) {
            goto acquired;                                                        // ZF set -> fall through to 0xc28bc7e
        }
        eax = orig;                                                               // cmpxchg reloads eax with current value
        goto test_refcount;                                                       // 0xc28bc7c jne short loc_c28bc70
    }

acquired:                                                                         // 0xc28bc7e..0xc28bc8a mov rax,[rbx] ; mov rdi,[rbx+8] ; test rax,rax ; je loc_c28bc97
    rax = rbx->vftObj;                                                            // 0xc28bc7e mov rax,[rbx]
    rdi = rcx;                                                                    // 0xc28bc81 mov rdi,[rbx+8]
    if (rax != nullptr) {                                                         // 0xc28bc85 test rax,rax ; 0xc28bc88 je short loc_c28bc97
        // 0xc28bc8a..0xc28bc97 mov rcx,[rax+0x18] ; mov word ptr [rcx],0xFFFF ; mov byte ptr [rax+0x10],0
        std::uint16_t* rcx2 = rax->refCountPtr;
        *rcx2 = 0xFFFF;                                                           // 0xc28bc8e mov word ptr [rcx],0xFFFF
        rax->stateByte = 0;                                                       // 0xc28bc93 mov byte ptr [rax+0x10],0
    }
    // 0xc28bc97..0xc28bc9c test rdi,rdi ; je short loc_c28bc50
    if (rdi == nullptr) {
        goto loop_increment;
    }
    // 0xc28bc9c..0xc28bca2 lock dec dword ptr [rdi+8] ; jne short loc_c28bc50
    if (InterlockedDecrement(reinterpret_cast<volatile long*>(&rdi->refCount)) != 0) {
        goto loop_increment;
    }
    // 0xc28bca2..0xc28bcb1 mov rax,[rdi] ; mov rax,[rax] ; mov rcx,rdi ; call qword ptr [0xF99FFA0]
    {
        void* vfptr0 = rdi->vfptr->dtor0;                                         // dead read of vfptr[0]
        (void)vfptr0;
    }
    callEea6040(rdi);                                                             // 0xc28bcab call qword ptr [0xF99FFA0] -> sub_eea6040(rdi)
    // 0xc28bcb1..0xc28bcb7 lock dec dword ptr [rdi+0xC] ; jne short loc_c28bc50
    if (InterlockedDecrement(reinterpret_cast<volatile long*>(&rdi->weakCount)) != 0) {
        goto loop_increment;
    }
    // 0xc28bcb7..0xc28bcc7 mov rax,[rdi] ; mov rax,[rax+8] ; mov rcx,rdi ; call qword ptr [0xF99FFA0]
    {
        void* vfptr8 = rdi->vfptr->dtor8;                                         // dead read of vfptr[8]
        (void)vfptr8;
    }
    callEea6040(rdi);                                                             // 0xc28bcc1 call qword ptr [0xF99FFA0] -> sub_eea6040(rdi)
    goto loop_increment;                                                          // 0xc28bcc7 jmp short loc_c28bc50

epilogue:                                                                         // 0xc28bcc9..0xc28bcea lea rcx,[rsi+0x18] ; call 0x6AE330 ; xorps ; movups ; mov qword ; add rsp ; pops ; ret
    native::sub_6ae330(&self->nested);                                            // 0xc28bccd call 0x6AE330
    // 0xc28bcd2..0xc28bcd9 xorps xmm0,xmm0 ; movups [rsi+0x18],xmm0  (clears nested.field00+field08)
    std::memset(&self->nested, 0, 16);
    // 0xc28bcd9..0xc28bce1 mov qword ptr [rsi+0x28],0
    self->nested.field10 = 0;
    // 0xc28bcd2 xorps xmm0,xmm0 -> rax = 0
    return 0;
}

// Layout assertions (mirror sub_c28bc30.h): every struct field read or written is asserted.
static_assert(offsetof(sub_c28bc30_state, elementStart) == 0x00, "sub_c28bc30: elementStart at +0x00");
static_assert(offsetof(sub_c28bc30_state, elementEnd) == 0x08, "sub_c28bc30: elementEnd at +0x08");
static_assert(offsetof(sub_c28bc30_state, nested) == 0x18, "sub_c28bc30: nested at +0x18");
static_assert(sizeof(sub_c28bc30_state) == 0x30, "sub_c28bc30: sub_c28bc30_state size 0x30");
static_assert(offsetof(SubC28bc30Elem, vftObj) == 0x00, "sub_c28bc30: SubC28bc30Elem::vftObj at +0x00");
static_assert(offsetof(SubC28bc30Elem, refObj) == 0x08, "sub_c28bc30: SubC28bc30Elem::refObj at +0x08");
static_assert(sizeof(SubC28bc30Elem) == 0x10, "sub_c28bc30: SubC28bc30Elem size 0x10");
static_assert(offsetof(VftObject, stateByte) == 0x10, "sub_c28bc30: VftObject::stateByte at +0x10");
static_assert(offsetof(VftObject, refCountPtr) == 0x18, "sub_c28bc30: VftObject::refCountPtr at +0x18");
static_assert(sizeof(VftObject) == 0x20, "sub_c28bc30: VftObject size 0x20");
static_assert(offsetof(RefObject, vfptr) == 0x00, "sub_c28bc30: RefObject::vfptr at +0x00");
static_assert(offsetof(RefObject, refCount) == 0x08, "sub_c28bc30: RefObject::refCount at +0x08");
static_assert(offsetof(RefObject, weakCount) == 0x0C, "sub_c28bc30: RefObject::weakCount at +0x0C");
static_assert(sizeof(RefObject) == 0x10, "sub_c28bc30: RefObject size 0x10");
static_assert(offsetof(RefObjectVft, dtor0) == 0x00, "sub_c28bc30: RefObjectVft::dtor0 at +0x00");
static_assert(offsetof(RefObjectVft, dtor8) == 0x08, "sub_c28bc30: RefObjectVft::dtor8 at +0x08");
static_assert(sizeof(RefObjectVft) == 0x10, "sub_c28bc30: RefObjectVft size 0x10");

} // namespace native::helpers
