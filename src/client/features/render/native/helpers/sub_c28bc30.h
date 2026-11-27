#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/native/helpers/sub_6ae330.h"

namespace native::helpers {

// Layout of the object passed to sub_c28bc30 in rcx (this), reverse-engineered from the
// disassembly of [0xc28bc30, 0xc28bceb), Minecraft Windows 1.26.62.01.
//
// The function walks a range of 0x10-byte elements [elementStart, elementEnd). Each element
// references a VftObject (+0x00) and a RefObject (+0x08). For each element it acquires the
// RefObject's refCount via lock cmpxchg (skipping when zero), mutates the VftObject, then
// releases the RefObject (lock dec refCount -> eea6040 via vfptr[0]; lock dec weakCount ->
// eea6040 via vfptr[8]). After the loop it releases a nested Sub6ae330This range at +0x18
// via sub_6ae330 and clears it.
//
// Field names and meanings are lift decisions. Offsets are [V] facts cited by instruction.

struct VftObject {
    // +0x00..0x0F unused by this function
    std::uint8_t pad00[0x10];         // +0x00
    std::uint8_t stateByte;           // +0x10  written 0   [0xc28bc93 mov byte ptr [rax+0x10],0]
    std::uint16_t* refCountPtr;       // +0x18  pointer to uint16 written 0xFFFF
                                      // [0xc28bc8a mov rcx,[rax+0x18]; 0xc28bc8e mov word ptr [rcx],0xFFFF]
};
static_assert(offsetof(VftObject, stateByte) == 0x10, "sub_c28bc30: VftObject::stateByte at +0x10");
static_assert(offsetof(VftObject, refCountPtr) == 0x18, "sub_c28bc30: VftObject::refCountPtr at +0x18");
static_assert(sizeof(VftObject) == 0x20, "sub_c28bc30: VftObject size 0x20");

struct RefObjectVft {
    void* dtor0;   // +0x00 vfptr[0]  (read, discarded) [0xc28bca5 mov rax,[rax]]
    void* dtor8;   // +0x08 vfptr[8]  (read, discarded) [0xc28bcba mov rax,[rax+8]]
};
static_assert(offsetof(RefObjectVft, dtor0) == 0x00, "sub_c28bc30: RefObjectVft::dtor0 at +0x00");
static_assert(offsetof(RefObjectVft, dtor8) == 0x08, "sub_c28bc30: RefObjectVft::dtor8 at +0x08");
static_assert(sizeof(RefObjectVft) == 0x10, "sub_c28bc30: RefObjectVft size 0x10");

struct RefObject {
    RefObjectVft* vfptr;      // +0x00  vfptr  [0xc28bca2 mov rax,[rdi] / 0xc28bcb7 mov rax,[rdi]]
    std::uint32_t refCount;   // +0x08  lock cmpxchg [0xc28bc77] / lock dec [0xc28bc9c]
    std::uint32_t weakCount;  // +0x0C  lock dec [0xc28bcb1]
};
static_assert(offsetof(RefObject, vfptr) == 0x00, "sub_c28bc30: RefObject::vfptr at +0x00");
static_assert(offsetof(RefObject, refCount) == 0x08, "sub_c28bc30: RefObject::refCount at +0x08");
static_assert(offsetof(RefObject, weakCount) == 0x0C, "sub_c28bc30: RefObject::weakCount at +0x0C");
static_assert(sizeof(RefObject) == 0x10, "sub_c28bc30: RefObject size 0x10");

struct SubC28bc30Elem {
    VftObject* vftObj;   // +0x00  [0xc28bc7e mov rax,[rbx]]
    RefObject* refObj;   // +0x08  [0xc28bc59 mov rcx,[rbx+8]; 0xc28bc81 mov rdi,[rbx+8]]
};
static_assert(offsetof(SubC28bc30Elem, vftObj) == 0x00, "sub_c28bc30: SubC28bc30Elem::vftObj at +0x00");
static_assert(offsetof(SubC28bc30Elem, refObj) == 0x08, "sub_c28bc30: SubC28bc30Elem::refObj at +0x08");
static_assert(sizeof(SubC28bc30Elem) == 0x10, "sub_c28bc30: SubC28bc30Elem size 0x10");

struct sub_c28bc30_state {
    void* elementStart;       // +0x00  start of element range  [0xc28bc3c mov rbx,[rcx]]
    void* elementEnd;         // +0x08  end of element range    [0xc28bc3f mov r14,[rcx+8]]
    std::uint8_t pad10[0x8];  // +0x10  unused gap
    Sub6ae330This nested;     // +0x18  nested range released by sub_6ae330
                              // [0xc28bcc9 lea rcx,[rsi+0x18]; 0xc28bccd call 0x6AE330]
                              // [0xc28bcd5 movups [rsi+0x18]; 0xc28bcd9 mov qword ptr [rsi+0x28],0]
};
static_assert(offsetof(sub_c28bc30_state, elementStart) == 0x00, "sub_c28bc30: elementStart at +0x00");
static_assert(offsetof(sub_c28bc30_state, elementEnd) == 0x08, "sub_c28bc30: elementEnd at +0x08");
static_assert(offsetof(sub_c28bc30_state, nested) == 0x18, "sub_c28bc30: nested at +0x18");
static_assert(sizeof(sub_c28bc30_state) == 0x30, "sub_c28bc30: sub_c28bc30_state size 0x30");

// Signature (x64 Microsoft ABI). The only exit zeroes rax [0xc28bcd2 xorps xmm0,xmm0],
// so the function returns 0.
uintptr_t sub_c28bc30(sub_c28bc30_state* self);

} // namespace native::helpers
