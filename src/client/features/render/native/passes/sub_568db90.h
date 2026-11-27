#pragma once

#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_568db90: Scene/HUD view-setup task element cleanup (size 0x80, 1.26.62.01).
// Processes one 0x20-byte view element from a pass-task array:
//   rcx = switch index (element->index + 1), rdx = unused, r8 = element (ViewElem*).
// Layout (all offsets [V] from disassembly of [0x568db90, 0x568dc10)):
//
//   struct ViewElem {
//       void* ptr;       // +0x00 buffer start        [read: 0x568dba5 mov rcx,[r8]]
//       std::uint8_t pad0[0x08]; // +0x08 unused
//       void* end;       // +0x10 buffer end          [read: 0x568dbad mov rdx,[r8+0x10]]
//       std::uint8_t index; // +0x18 switch index byte [read by caller: 0x568dac0 movsx rcx,byte ptr [rdi+0x18]]
//       std::uint8_t pad1[0x07]; // +0x19-0x1F unused
//   };                         sizeof 0x20 [V: caller steps by 0x20, 0x568dad3 add rdi,0x20]
//
// Calls out of lifted code [V]:
//   0x568dbdd  call 0xE935700   class lift (native_boundary.tsv line 505): forward-declared below, called directly
//   0x568dc09  call qword ptr [0xF9A8C78]  dead fail path through data slot [0xF9A8C78] (rcx=rdx=r8=r9=0, noreturn + int3)
namespace native {

struct ViewElem {
    void* ptr;           // +0x00
    std::uint8_t pad0[0x08];  // +0x08
    void* end;           // +0x10
    std::uint8_t index;  // +0x18
    std::uint8_t pad1[0x07];  // +0x19
};
static_assert(offsetof(ViewElem, ptr) == 0x00, "568db90: ViewElem::ptr at +0x00");
static_assert(offsetof(ViewElem, end) == 0x10, "568db90: ViewElem::end at +0x10");
static_assert(offsetof(ViewElem, index) == 0x18, "568db90: ViewElem::index at +0x18");
static_assert(sizeof(ViewElem) == 0x20, "568db90: ViewElem size 0x20");

// 0x568dbdd / 0x568dbda path: call 0xE935700 (rcx = buffer base or user ptr, rdx = size or size+0x27).
// Class lift per docs/data/native_boundary.tsv line 505: forward-declared here and called directly,
// not through a Boundary wrapper.
void sub_e935700(void* ptr, std::uint64_t size);

// void sub_568db90(std::uint8_t index /*rcx*/, void* /*rdx unused*/, ViewElem* elem /*r8*/);
// Return: void (rax = sub_e935700's result, ignored by caller [V: 0x568dace caller does not use rax]).
void sub_568db90(std::uint8_t index, void* /*unused*/, ViewElem* elem);

} // namespace native
