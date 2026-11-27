#pragma once
#include <cstdint>
#include <cstddef>

// sub_6685f60 (0x6685f60, size 0x25, 1.26.62.01): BgfxFrameBuilder slot 61.
// Body [0x6685f60, 0x6685f85):
//   0x6685f60  sub rsp,0x28
//   0x6685f64  test r8,r8             ; je short 0x6685F7F
//   0x6685f69  test rdx,rdx           ; je short 0x6685F7F
//   0x6685f6e  mov rax,[rcx+0x28]     ; read link out of the rcx argument object
//   0x6685f72  mov rcx,[rax+0x18]     ; tail-call this out of the linked object
//   0x6685f76  add rsp,0x28
//   0x6685f7a  jmp 0xC288650          ; tail call, target outside the lift set and native_boundary.tsv
//   0x6685f7f  call 0x78ED0           ; CRT boundary (class=crt), rcx=a0 rdx=a1 r8=a2, result unused
//   0x6685f84  int3
// No memory writes; two reads in the order above. [V: rdis dis 0x6685f60 0x25]
//
// No game struct types are known for this unit; only the two read offsets are asserted here.
namespace native {

struct sub_6685f60Layout {
    // Offset of the link pointer read from the rcx argument object: [rcx+0x28]  [V: 0x6685f6e mov rax,[rcx+0x28]]
    static constexpr std::size_t kObjLinkOff = 0x28;
    // Offset of the tail-call this pointer read from the linked object: [link+0x18]  [V: 0x6685f72 mov rcx,[rax+0x18]]
    static constexpr std::size_t kTailThisOff = 0x18;

    static_assert(kObjLinkOff == 0x28, "sub_6685f60: [rcx+0x28] link offset");
    static_assert(kTailThisOff == 0x18, "sub_6685f60: [link+0x18] tail-this offset");
    static_assert(sizeof(void*) == 8, "sub_6685f60: x64 ABI, pointer-sized address space");
};

// Signature of the original: x64 Microsoft ABI, rcx/rdx/r8 in registers. Return type and pointee types
// are not determined by the disassembly (rax is the tail-call pass-through / boundary result). [I]
std::uintptr_t sub_6685f60(void* a0, void* a1, void* a2);

} // namespace native
