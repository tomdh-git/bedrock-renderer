#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Layout of the fields of BgfxFrameBuilder used by sub_c25f680
// (BgfxFrameBuilder::endFrame, 0xc25f680, size 0x77, 1.26.62.01), observed in
// the disassembly of [0xc25f680, 0xc25f6f7):
//   0xc25f686 / 0xc25f696  mov rax,[rcx+0x90]     (RefCountBase* object)
//   0xc25f6a1              mov rax,[rcx+0x88]     (pointer; its int32 pointee compared with 2)
// Only the fields used by this function are declared; nothing else about the
// class layout is assumed.
struct RefCountBase {
    void* vtable;            // +0x00  vtable pointer; [0] = destructor, [8] = deallocator
    std::int32_t strong;     // +0x08  interlocked strong reference count
    std::int32_t weak;       // +0x0C  interlocked weak reference count
};
struct BgfxFrameBuilder {
    std::uint8_t _pad_0x00[0x88];  // +0x00 unused by this function
    std::int32_t* field0x88;       // +0x88  pointer; *field0x88 compared against 2
    RefCountBase* field0x90;       // +0x90  ref-counted object (strong at +0x08, weak at +0x0C)
};
static_assert(offsetof(BgfxFrameBuilder, field0x88) == 0x88, "c25f680: BgfxFrameBuilder::field0x88 at +0x88");
static_assert(offsetof(BgfxFrameBuilder, field0x90) == 0x90, "c25f680: BgfxFrameBuilder::field0x90 at +0x90");
static_assert(offsetof(RefCountBase, vtable) == 0x00, "c25f680: RefCountBase::vtable at +0x00");
static_assert(offsetof(RefCountBase, strong) == 0x08, "c25f680: RefCountBase::strong at +0x08");
static_assert(offsetof(RefCountBase, weak) == 0x0C, "c25f680: RefCountBase::weak at +0x0C");
static_assert(sizeof(RefCountBase) == 0x10, "c25f680: RefCountBase size 0x10");

// Both `call qword ptr [0xF99FFA0]` sites (0xc25f6d2, 0xc25f6e8) go through the
// loader-resolved data slot 0xF99FFA0, which holds sub_eea6040
// (docs/data/native_boundary.tsv row 0xeea6040, class vendor, "thunk via data
// slot 0xF99FFA0 (loader-resolved)"). sub_eea6040 is a `jmp rax` forwarder, so
// the real target is the vtable entry preloaded into RAX: vtable[0] (object
// destructor) at 0xc25f6d2, vtable[8] (object deallocator) at 0xc25f6e8. RCX =
// object pointer on entry; return value ignored.

// Signature of sub_c25f680 itself: x64 Microsoft ABI, self in RCX, bool in AL.
bool sub_c25f680(BgfxFrameBuilder* self);

} // namespace native
