#pragma once
// LIFT 0xe878bc0 size 0xba 1.26.62.01 sub_e878bc0
// Layout constants for the lift of sub_e878bc0 [0xe878bc0, 0xe878c7a).
// Every offset below is verbatim from the disassembly; see docs/functions/e878bc0.md.

#include <cstddef>
#include <cstdint>

namespace native {
namespace d3d12 {

// [a0] (rcx) is an opaque object; the function only reads [a0 + 0x8], a sub-object pointer.
static constexpr std::size_t kOffA0Sub = 0x8;

// *rdi = [a0 + 0x8]. Used fields: [rdi + 0x20] (buf), [rdi + 0x30] (end),
// [rdi + 0x38] (container object).
struct alignas(8) SubObject {
    std::uint8_t pad_0x00[0x20];   // 0x00..0x1F not read by this function
    void* buf;                     // 0x20 - buffer pointer
    std::uint8_t pad_0x28[8];      // 0x28..0x2F not read by this function
    void* end;                     // 0x30 - one-past-end pointer
    void* container;               // 0x38 - container heap object
};
static_assert(offsetof(SubObject, buf) == 0x20, "SubObject.buf must be at offset 0x20");
static_assert(offsetof(SubObject, end) == 0x30, "SubObject.end must be at offset 0x30");
static_assert(offsetof(SubObject, container) == 0x38, "SubObject.container must be at offset 0x38");
static_assert(sizeof(SubObject) == 0x40, "SubObject accessed region must end at 0x40");

// *container = [sub + 0x38]. Used field: [container + 0x8], passed as r8 to the boundary call.
struct alignas(8) Container {
    std::uint8_t pad_0x00[8];      // 0x00..0x07 not read by this function
    void* field8;                  // 0x08
};
static_assert(offsetof(Container, field8) == 0x08, "Container.field8 must be at offset 0x08");
static_assert(sizeof(Container) == 0x10, "Container accessed region must end at 0x10");

// ---------------------------------------------------------------------------
// Callees of sub_e878bc0
// ---------------------------------------------------------------------------

// 0xe935700: class lift in docs/data/native_boundary.tsv (own lift unit, X7.e935700).
//   sub_e935700 is `jmp 0x392960`: a sized free through the allocator object at [0x1233E1A8]
//   (which itself calls the thunk at slot [0xF99FFA0] = sub_eea6040).
//   Observed call convention: rcx = pointer to free, rdx = size (accepted but unused by the
//   callee itself). Forward-declared with the exact x64 ABI signature; called as native::sub_e935700.
extern "C" void sub_e935700(void* ptr, unsigned __int64 size); // 0xe935700

namespace boundary {
    // 0x1f5ef50: class stl in docs/data/native_boundary.tsv.
    //   Container walk that frees its nodes via sub_e935700; return value unused by the caller.
    //   Observed call convention: rcx = container, rdx = container, r8 = [container + 0x8].
    void sub_1f5ef50(void* a1, void* a2, void* a3); // 0x1f5ef50 (stl)

    // call qword ptr [0xF9A8C78]: IAT slot of _invoke_watson (CRT fail-fast,
    // api-ms-win-crt-runtime-l1-1-0.dll). The exe zeroes all five arguments and the
    // call is noreturn (the block is padded with int3, 0xe878c79..0xe878c7f).
    // The slot is read at call time (VA = image base 0x140000000 + RVA 0xF9A8C78)
    // and invoked as a function pointer, per docs/OPENCODE_BRIEF.md indirect-slot rule.
    __declspec(noreturn) void sub_f9a8c78(const wchar_t* a1, const wchar_t* a2,
                                          const wchar_t* a3, unsigned int a4,
                                          uintptr_t a5); // via slot 0xF9A8C78
} // namespace boundary

// ---------------------------------------------------------------------------
// Function: sub_e878bc0
//   [0xe878bc0, 0xe878c7a), size 0xba. x64 Microsoft ABI: rcx = a0.
//   Returns void: rax is never defined on any straight return path; the tail path
//   forwards sub_e935700's result exactly like the original's tail jump.
//   Writes: [sub + 0x20, sub + 0x38) zeroed (buf/end fields of *rdi); sub itself
//   is released through sub_e935700(sub, 0x48) on every exit path.
//   Calls: boundary::sub_1f5ef50 (0x1f5ef50, stl), native::sub_e935700 (0xe935700,
//   lift callee, x2 direct + 1 tail), call [0xF9A8C78] (_invoke_watson, noreturn).
//   x64 Microsoft ABI: rcx = a0. C++ linkage is used (same x64 ABI) so the function
//   can be referenced by LIFT_FN; the linkage is not observable from the call sites.
void sub_e878bc0(void* a0);

} // namespace d3d12
} // namespace native
