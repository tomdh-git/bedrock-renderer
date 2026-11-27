#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Layout of the r8 argument of sub_ebce650 (0xebce650, size 0x6b, 1.26.62.01), observed in the
// disassembly: the function reads [r8+8] (int32) at 0xebce65f, [r8] (char*) at 0xebce665, and
// [r8+8] again at 0xebce66b. No other offsets of this argument are touched, so the struct below
// declares exactly those two fields; the complete original size is not known from this function.
struct SrcDesc {
    char* ptr;               // +0x00  char*  source string (read at 0xebce665: mov rdx,[r8])
    std::int32_t maxlen;     // +0x08  int32  length cap (read at 0xebce65f and 0xebce66b)
};

static_assert(offsetof(SrcDesc, ptr) == 0x00, "sub_ebce650: SrcDesc::ptr must be at +0x00");
static_assert(offsetof(SrcDesc, maxlen) == 0x08, "sub_ebce650: SrcDesc::maxlen must be at +0x08");

// Lift-set callee: docs/data/native_functions.tsv and docs/data/native_boundary.tsv both classify
// 0xebce390 as lift (size 0x5, a tail forwarder to sub_eec6ec0). Forward-declared here and called
// directly with the same register arguments; linked through its own LIFT_FN registration.
extern "C" void sub_ebce390(void* dst, void* src, std::uint32_t count) noexcept;

// Signature of sub_ebce650 (x64 Microsoft ABI), recovered from the disassembly:
//   rcx = char*  dst      output buffer; dst[count] = 0 is written after the copy
//   rdx = int   dstSize   copy bound; at most dstSize-1 bytes are copied
//   r8  = SrcDesc* srcdesc; source string at +0x00, its length cap at +0x08
//   r9  = int   maxlen    second length cap; used as min(maxlen, srcdesc->maxlen)
//   return = int          number of bytes copied (not counting the terminator)
extern "C" int sub_ebce650(char* dst, int dstSize, SrcDesc* srcdesc, int maxlen) noexcept;

} // namespace native
