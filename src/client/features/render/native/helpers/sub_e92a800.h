#pragma once
#include <cstdint>
#include <cstddef>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"
#include "client/features/render/native/helpers/sub_eec5a00.h"
#include <thread>

// sub_e92a800 (0xe92a800, size 0xbf, 1.26.62.01).
// Locks the _Mtx at a0+0x30, walks the 8-byte-element array [a0+0x178, a0+0x180),
// and for each element whose +0xD8 qword is zero calls sub_e92a350(element, arg2, a0+0x128).
// Returns 1 if the loop broke early (sub_e92a350 returned non-zero), 0 if it ran to completion.
//
// Field offsets observed in the disassembly of 0xe92a800:
//   a0+0x30   _Mtx_t         (locked via ::_Mtx_lock, unlocked via ::_Mtx_unlock)
//   a0+0x7C   int32 state    (compared to 0x7FFFFFFF, set to 0x7FFFFFFE on error)
//   a0+0x128  void*          (passed as r8 / 3rd arg to sub_e92a350)
//   a0+0x178  void**         (array base pointer)
//   a0+0x180  void*          (array end pointer)
//   elem+0xD8 int64 flag     (compared to 0; call sub_e92a350 only when zero)
//
// Callees:
//   ::_Mtx_lock / ::_Mtx_unlock (MSVCP140 CRT, declared in <thread>): called via the
//     addresses that sub_eec59f0 (slot 0xF9A75A8) and sub_eec5a10 (slot 0xF9A75B8)
//     forward to. We call the CRT functions directly so we can inspect the _Thrd_result
//     return of _Mtx_lock. We do NOT include sub_eec59f0.h / sub_eec5a10.h here because
//     those redeclare _Mtx_lock / _Mtx_unlock with extern "C" and 'struct _Mtx*',
//     which conflicts with the CRT's own _Mtx_lock(_Mtx_t) / _Mtx_unlock(_Mtx_t).
//   sub_eec5a00 (lift/set): void std::_Throw_Cpp_error(int) — declared in sub_eec5a00.h.
//   sub_e92a350: UNRESOLVED — not in native_functions.tsv or native_boundary.tsv
//     (only in native_boundary_candidates.tsv with class '?'). Forward-declared below so the
//     lifted body compiles; the call site is documented in the result file as UNRESOLVED CALL.
//
// No shared headers or Sigs.json are edited; all layout constants are asserted here.

// sub_e92a350 — UNRESOLVED callee (not in either native table).
// Called at 0xe92a87f with rcx=array element, rdx=arg2, r8=[a0+0x128]; return in eax.
int sub_e92a350(void* element, void* arg2, void* ptr128);

struct sub_e92a800Layout {
    static constexpr std::size_t kMutexOffset = 0x30;      // a0+0x30: _Mtx
    static constexpr std::size_t kStateOffset = 0x7C;      // a0+0x7C: int32 state
    static constexpr std::size_t kCalleeArgOffset = 0x128; // a0+0x128: void* arg to sub_e92a350
    static constexpr std::size_t kArrayBaseOffset = 0x178; // a0+0x178: void** array base
    static constexpr std::size_t kArrayEndOffset = 0x180;  // a0+0x180: void* array end
    static constexpr std::size_t kElementD8Offset = 0xD8;  // elem+0xD8: int64 flag
    static_assert(kMutexOffset == 0x30, "sub_e92a800: mutex at a0+0x30");
    static_assert(kStateOffset == 0x7C, "sub_e92a800: state dword at a0+0x7C");
    static_assert(kCalleeArgOffset == 0x128, "sub_e92a800: callee arg pointer at a0+0x128");
    static_assert(kArrayBaseOffset == 0x178, "sub_e92a800: array base at a0+0x178");
    static_assert(kArrayEndOffset == 0x180, "sub_e92a800: array end at a0+0x180");
    static_assert(kElementD8Offset == 0xD8, "sub_e92a800: element flag at +0xD8");
    static_assert(sizeof(void*) == 8, "sub_e92a800: x64 ABI, pointer-sized address space");
};

namespace native {

// Signature of sub_e92a800: x64 Microsoft ABI, arg1 (RCX) = context pointer a0,
// arg2 (RDX) = forwarded to sub_e92a350, return int (0 or 1) in EAX.
int sub_e92a800(void* a0, void* arg2);

} // namespace native
