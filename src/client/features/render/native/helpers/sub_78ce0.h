#pragma once
#include <cstddef>
#include <cstdint>

// sub_78ce0 (0x78ce0, size 0x98, 1.26.62.01): releases the refcounted object referenced at [a0+0x8]
// via the loader-resolved thunk in data slot 0xF99FFA0 (sub_eea6040, vendor boundary), then clears
// [a0+0x10]. Because the function first zeroes [a0+0x00..0x0F] with movups, the load of [a0+0x8]
// that selects the release path reads back zero, so the release block is unreachable at runtime;
// the observable effect is [a0+0x00..0x17] = 0 and a void return. Every instruction is lifted
// faithfully, including the dead release block.
//   0x78ce0  push rsi
//   0x78ce1  push rdi
//   0x78ce2  sub rsp,0x28
//   0x78ce6  mov rsi,rcx
//   0x78ce9  xorps xmm0,xmm0
//   0x78cec  movups [rcx],xmm0   ; W [a0+0x00..0x0F] = 0
//   0x78cf0  mov rdi,[rcx+8]     ; R objectA = [a0+0x8] (= 0)
//   0x78cf3  test rdi,rdi
//   0x78cf6  je short 0x78D69    ; objectA == 0 -> skip release
//   0x78cf8..0x78d22  block 1 (dead): lock dec [objectA+8]; if 0 call [0xF99FFA0](objectA);
//                            lock dec [objectA+0xC]; if 0 call [0xF99FFA0](objectA)
//   0x78d23..0x78d68  block 2 (dead): objectA = [a0+8]; [a0+0x10] = 0; lock dec [objectA+8];
//                            if 0 call [0xF99FFA0](objectA); lock dec [objectA+0xC];
//                            if 0 jmp [0xF99FFA0] (tail)
//   0x78d69  mov qword ptr [rsi+0x10],0   ; W [a0+0x10] = 0
//   0x78d71  add rsp,0x28
//   0x78d75  pop rdi
//   0x78d76  pop rsi
//   0x78d77  ret
// Calls: 0x78d07, 0x78d1d, 0x78d43 all `call qword ptr [0xF99FFA0]` (sub_eea6040, vendor boundary,
// loader-resolved thunk via data slot 0xF99FFA0), invoked through a function pointer read from the
// slot at call time (rule #69; not a blocker).
// x64 Microsoft ABI: RCX = a0 (this), return void.
// Reads: [a0+0x8] (objectA pointer), objectA fields (+0x0 vfptr, +0x8 strong, +0xC weak) in dead block,
// data slot 0xF99FFA0 (call target). Writes: [a0+0x00..0x0F] (movups), [a0+0x10] (qword 0),
// objectA refcounts in dead block.

struct Sub78ce0This {
    std::uint64_t field00;   // +0x00  zeroed by movups
    std::uint64_t field08;   // +0x08  objectA pointer (zeroed by movups)
    std::uint64_t field0x10; // +0x10  zeroed by qword store
};
static_assert(offsetof(Sub78ce0This, field00) == 0x00, "sub_78ce0: field00 at +0x00");
static_assert(offsetof(Sub78ce0This, field08) == 0x08, "sub_78ce0: objectA pointer at +0x08");
static_assert(offsetof(Sub78ce0This, field0x10) == 0x10, "sub_78ce0: clear field at +0x10");
static_assert(sizeof(Sub78ce0This) == 0x18, "sub_78ce0: this object size 0x18");

struct Sub78ce0Refcounted {
    std::uint64_t vfptr;      // +0x00
    std::uint32_t strongRef;  // +0x08  lock dec dword
    std::uint32_t weakRef;    // +0x0C  lock dec dword
};
static_assert(offsetof(Sub78ce0Refcounted, vfptr) == 0x00, "sub_78ce0: vfptr at +0x00");
static_assert(offsetof(Sub78ce0Refcounted, strongRef) == 0x08, "sub_78ce0: strong refcount at +0x08");
static_assert(offsetof(Sub78ce0Refcounted, weakRef) == 0x0C, "sub_78ce0: weak refcount at +0x0C");
static_assert(sizeof(Sub78ce0Refcounted) == 0x10, "sub_78ce0: refcounted object size 0x10");

static constexpr std::uintptr_t kReleaseSlotRva = 0xF99FFA0; // call qword ptr [0xF99FFA0] target
static_assert(kReleaseSlotRva == 0xF99FFA0, "sub_78ce0: release thunk slot at RVA 0xF99FFA0");

namespace native {

// Signature of sub_78ce0 itself: RCX = a0 (this), return void [V: rdis dis 0x78ce0 0x98].
void sub_78ce0(void* a0);

// Signature of the data-slot callee sub_eea6040 reached through slot 0xF99FFA0:
// receives RCX = objectA (this); return unused by sub_78ce0
// [V: 0x78d07/0x78d1d/0x78d43 call qword ptr [0xF99FFA0]].
using Eea6040Callee = void (*)(void* objectA);

} // namespace native
