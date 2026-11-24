#pragma once

#include <cstddef>
#include <cstdint>

namespace native {

// Layout recovered from the disassembly of 0xbc6aeb0 (size 0x86,
// 0xbc6aeb0..0xbc6af36, sub_bc6aeb0, 1.26.62.01).
//
// The argument rcx points at a struct whose first dword (+0x00) is a count.
// If count != 0 the function allocates two 0x400-byte stack buffers and calls
// sub_bc7a9d0(keys=rcx+4, workKeys=buf0, parIn=rcx+0x404, parOut=buf1, count).
// Returns (count != 0).
static constexpr std::uintptr_t kGblCookie = 0x1230A0C0u;  // [data_1230a0c0] stack cookie secret

extern "C" bool sub_bc6aeb0(void* p);

} // namespace native