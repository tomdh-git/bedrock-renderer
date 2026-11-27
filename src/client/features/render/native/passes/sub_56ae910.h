#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_56ae910 (0x56ae910, size 0x79, 1.26.62.01): Item group visitor.
// Layout constants and static asserts for the lifted body.
//
// Operand object layout (rcx = a0) [V: rdis dis 0x56ae910]:
//   +0x00  void* vtable     (8-byte read at [rcx]; heap-block base reference)
//   +0x10  void* some_ptr   (8-byte read at [rcx+0x10], written to 0 at [rcx+0x10])
//   +0x40  uint8_t flag     (1-byte read at [rcx+0x40] == 1 check)
//   +0x00..+0x18            (24 bytes zeroed: movups 16B at +0x00, movq 8B at +0x10)
//
// Heap integrity check [V]:
//   reads [vtable-8] (qword heap header), computes vtable - 8 - header,
//   calls _invoke_watson via IAT slot 0xF9A8C78 if result >= 0x20 (noreturn).
//
struct Sub56ae910Layout {
    static constexpr std::size_t kOffVtable = 0x00;   // [rcx+0x00] 8-byte read (vtable)
    static constexpr std::size_t kOffSomePtr = 0x10;  // [rcx+0x10] 8-byte read/write
    static constexpr std::size_t kOffFlag = 0x40;     // [rcx+0x40] 1-byte read
    static constexpr std::size_t kZeroSize = 0x18;    // bytes zeroed at [rcx..rcx+0x18)
    static_assert(sizeof(void*) == 8, "sub_56ae910: x64 pointer-sized fields are 8 bytes");
};
static_assert(sizeof(Sub56ae910Layout) > 0, "sub_56ae910: layout constant block");

// Data-slot RVA (documented; call goes through the slot read at call time, hard rule 69).
static constexpr std::uintptr_t kRvaWatsonSlot = 0xF9A8C78;  // call qword ptr [0xF9A8C78]

namespace native {

// Lift-set callee sub_e935700 (0xe935700, size 0x5, docs/data/native_functions.tsv line 1620).
// Tail jump to sub_392960. Single argument in RCX, result in RAX.
// Forward-declared here and called directly (hard rule 66: lift callee, not boundary).
void* sub_e935700(void* a0);

// _invoke_watson via IAT data slot 0xF9A8C78.
// Indirect call through data slot (hard rule 69): read the pointer at call time.
// __declspec(noreturn): never returns to the caller.
// Arguments: (expression=nullptr, function=nullptr, file=nullptr, line=0, reserved=0).
__declspec(noreturn) void sub_f9a8c78_watson(const wchar_t* expression,
                                             const wchar_t* function,
                                             const wchar_t* file,
                                             unsigned int line,
                                             unsigned int reserved);

// Lifted body of sub_56ae910 (Item group visitor).
void* sub_56ae910(void* a0);

} // namespace native
