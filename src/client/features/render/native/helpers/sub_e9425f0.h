#pragma once
#include <cstdint>

// sub_e9425f0 (0xe9425f0, size 0x13, 1.26.62.01): transparent allocator forwarder.
//
// The exe function body ([0xe9425f0, 0xe942603)):
//   0xe9425f0  sub rsp,0x28                       ; 16-byte align rsp before the call
//   0xe9425f4  call 0x392920                      ; boundary: sub_392920(rcx=size) -> rax
//   0xe9425f9  jmp short 0xE9425FD                ; skip unreachable block
//   0xe9425fb  xor eax,eax                        ; dead code (never executes)
//   0xe9425fd  add rsp,0x28
//   0xe942601  ret                               ; return rax unchanged
//   0xe942602  int3                              ; padding inside the declared size 0x13
//
// It addresses no stack argument and touches no memory: only rcx (64-bit allocation size in
// bytes) is forwarded and rax (allocated pointer) is returned. [V: rdis dis 0xe9425f0 0x13;
//  caller 0x6627c25 sets rcx = count<<4 at 0x6627c1e]
//
// No layout constants are needed (no struct fields are touched); the x64 ABI contract is
// asserted below.
struct sub_e9425f0Layout {
    static_assert(sizeof(void*) == 8, "sub_e9425f0: x64 ABI, pointer-sized address space");
    using Fn = void* (__cdecl*)(std::uint64_t);
    static_assert(sizeof(Fn) == 8, "sub_e9425f0: x64 function pointer is 8 bytes");
};

namespace native {

// Boundary callee: 0x392920, class=alloc [docs/data/native_boundary.tsv line 98].
// sub_392920(std::uint64_t size) -> void* ; rcx = size, rax = allocation result;
// on a null result with nonzero size it calls sub_9bc830 (noreturn OOM) through the
// allocator vtable slot reached via data slot 0xF99FFA0 (sub_eea6040) [V: rdis dis 0x392920].
namespace boundary {
    void* sub_392920(std::uint64_t size);
} // namespace boundary

// Signature of sub_e9425f0 itself: identical to sub_392920 (transparent forwarder,
// no register shuffling, no stack frame). [V]
void* sub_e9425f0(std::uint64_t size);

} // namespace native
