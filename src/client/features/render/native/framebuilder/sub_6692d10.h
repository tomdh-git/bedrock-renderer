#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_6692d10 (0x6692d10, size 0x79, 1.26.62.01, "group insert effect").
//
// Layout of the 16-byte slot the function copies into (a0 = RCX, also the return value)
// and the 16-byte source slot it copies from (a1 = RDX). Both have the same layout:
//   +0x00 void* ptr
//   +0x08 void* object   (ref-counted object; +0x8 of the object is refcount1)
// Observed in the disassembly of [0x6692d10, 0x6692d89):
//   0x6692d1c  movups [rcx],xmm0         ; W slot+0x0 (16 bytes zeroed)
//   0x6692d1f  mov rcx,[rdx+8]           ; R source+0x8  (incoming object)
//   0x6692d28  lock inc dword ptr [rcx+8]; W object+0x8 (refcount1)
//   0x6692d2c  mov rsi,[rax+8]           ; R slot+0x8    (old object, always 0)
//   0x6692d30  movups xmm0,[rdx]         ; R source+0x0 (16 bytes)
//   0x6692d33  movups [rax],xmm0         ; W slot+0x0 (16 bytes copied)
//   0x6692d74  mov rcx,[rdx]             ; R source+0x0  (null-object branch)
//   0x6692d77  mov [rax],rcx             ; W slot+0x0
//   0x6692d7a  mov qword ptr [rax+8],0   ; W slot+0x8 = 0
struct EffectSlot {
    void* ptr;     // +0x00
    void* object;  // +0x08
};

// Layout of the ref-counted object pointed at by EffectSlot::object. Offsets
// referenced by the (dead) release block — oldObj is always 0 because the slot
// is zeroed at 0x6692d1c before being read at 0x6692d2c, so vtable[0] (0x6692d50)
// and vtable[1] (0x6692d69) are never invoked:
//   0x6692d41  mov rcx,[rsi]        ; R oldObj+0x0  (vtable)
//   0x6692d44  mov rdx,[rcx]        ; R vtable+0x0  (vtable[0])
//   0x6692d59  lock dec dword ptr [rsi+0xC]; W oldObj+0xC (refcount2)
//   0x6692d5f  mov rax,[rsi]        ; R oldObj+0x0  (vtable)
//   0x6692d62  mov rax,[rax+8]      ; R vtable+0x8  (vtable[1])
struct RefCountedObject {
    void** vtable;           // +0x00
    std::uint32_t refcount1; // +0x08  interlocked incremented/decremented
    std::uint32_t refcount2; // +0x0C  interlocked decremented
    // vtable[0] invoked via call at 0x6692d50, vtable[1] via call at 0x6692d69,
    // both through loader-resolved data slot 0xF99FFA0 (sub_eea6040, a `jmp rax`
    // thunk, docs/data/native_boundary.tsv class vendor). rcx = oldObj on entry.
};

static_assert(offsetof(EffectSlot, ptr) == 0x00,
              "sub_6692d10: EffectSlot::ptr at +0x00 (W, 0x6692d1c/0x6692d33/0x6692d77)");
static_assert(offsetof(EffectSlot, object) == 0x08,
              "sub_6692d10: EffectSlot::object at +0x08 (R/W, 0x6692d1f/0x6692d2c/0x6692d33/0x6692d7a)");
static_assert(offsetof(RefCountedObject, vtable) == 0x00,
              "sub_6692d10: RefCountedObject::vtable at +0x00 (R, 0x6692d41/0x6692d5f)");
static_assert(offsetof(RefCountedObject, refcount1) == 0x08,
              "sub_6692d10: RefCountedObject::refcount1 at +0x08 (RW, 0x6692d28/0x6692d3b)");
static_assert(offsetof(RefCountedObject, refcount2) == 0x0C,
              "sub_6692d10: RefCountedObject::refcount2 at +0x0C (RW, 0x6692d59)");
static_assert(sizeof(void*) == 8, "sub_6692d10: x64 ABI, pointer-sized address space");

// Exact x64 Microsoft ABI mirror of the original function.
// RCX = a0 (EffectSlot*, destination, also returned in RAX), RDX = a1 (const EffectSlot*, source).
void* sub_6692d10(EffectSlot* a0, const EffectSlot* a1);

} // namespace native
