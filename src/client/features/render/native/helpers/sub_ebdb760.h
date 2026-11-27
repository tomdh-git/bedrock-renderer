#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_ebdb760 (0xebdb760, size 0x19, 1.26.62.01): a leaf wrapper that calls the
// loader-resolved function in data slot 0xF9A7CA0 with RCX = &buf (a stack qword
// buffer the callee fills), then returns the qword the callee wrote there (RAX =
// buf). The callee's own return value is discarded.
//
//   0xebdb760  sub rsp,0x28
//   0xebdb764  lea rcx,[rsp+0x30]
//   0xebdb769  call qword ptr [0xF9A7CA0]   ; [data_f9a7ca0]
//   0xebdb76f  mov rax,[rsp+0x30]
//   0xebdb774  add rsp,0x28
//   0xebdb778  ret
//
// The callee's runtime address is the 8-byte value stored at imageBase + 0xF9A7CA0
// (a loader-resolved import/data slot, read at call time -- same pattern as
// sub_ebdbf10 through slot 0xF9A7B10). The function reads no struct field and
// writes no memory outside its own stack frame, so there are no struct layout
// offsets to assert; only the x64 ABI contract below [V: rdis dis 0xebdb760 0x19].
struct SubEbdb760Layout {
    static_assert(sizeof(void*) == 8, "sub_ebdb760: x64 ABI, 8-byte return value in RAX");
    static_assert(sizeof(uint64_t) == 8, "sub_ebdb760: returned value is 64 bits");
    static_assert(sizeof(SubEbdb760Layout) > 0, "sub_ebdb760: layout constant block");
};

namespace native {

// Signature of sub_ebdb760 itself: x64 Microsoft ABI, no register arguments on entry
// (RCX is overwritten by the lea before it is read), return value in RAX
// [V: rdis dis 0xebdb760 0x19].
extern "C" uint64_t sub_ebdb760(void);

// Signature of the data-slot callee reached through slot 0xF9A7CA0: receives RCX =
// pointer to a qword buffer it fills; its 64-bit return value (RAX) is discarded by
// the wrapper [V: 0xebdb769  call qword ptr [0xF9A7CA0]; 0xebdb76f  mov rax,[rsp+0x30]].
using Ebdb760Callee = uint64_t (*)(uint64_t* out);

} // namespace native
