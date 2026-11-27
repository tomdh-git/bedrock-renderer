#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"
#include "client/features/render/native/Lift.h"

// sub_e943170 (0xe943170, size 0x7, 1.26.62.01): indirect tail jump through the
// loader-resolved data slot 0xF9A7AF0 (`jmp qword ptr [0xF9A7AF0]`; = AcquireSRWLockExclusive
// per peimports.py [V]).
// Layout constants: the function reads no struct fields and writes no memory of its
// own, so there are no struct offsets to assert; only the x64 ABI contract is
// asserted below [V: rdis dis for 0xe943170; one 8-byte read at &data_f9a7af0].
struct sub_e943170Layout {
    static_assert(sizeof(void*) == 8, "sub_e943170: x64 ABI, pointer-sized argument in RCX and result in RAX");
};

namespace native {

// sub_e943170: tail jump through data slot 0xF9A7AF0. The single argument arrives
// in RCX (a caller-supplied SRWLOCK pointer) and the result leaves in RAX exactly as
// the slot target leaves it (return unused by callers).
void sub_e943170(void* lock);

} // namespace native
