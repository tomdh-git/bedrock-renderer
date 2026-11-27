#pragma once
#include <cstddef>
#include <cstdint>
#include <atomic>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_bc04270 (0xbc04270, size 0x95, 1.26.62.01, "pass encode D").
//
//   0xbc04270  push rsi                                   ; prologue
//   0xbc04271  push rdi
//   0xbc04272  sub rsp,0x28
//   0xbc04276  mov rsi,rcx                                ; a0 = rcx
//   0xbc04279  mov rax,[rdx]                              ; R a1+0x0
//   0xbc0427c  mov [rcx+0x3A8],rax                        ; W a0+0x3A8 = a1+0x0
//   0xbc04283  mov rax,[rdx+0x10]                         ; R a1+0x10 (RefCounted*)
//   0xbc04287  test rax,rax
//   0xbc0428a  je short 0xBC04296                         ; skip addref when a1+0x10 == 0
//   0xbc0428c  lock inc dword ptr [rax+8]                 ; W (a1+0x10)+0x8  addref
//   0xbc04290  mov rax,[rdx+0x10]                         ; R a1+0x10 (reload)
//   0xbc04294  jmp short 0xBC04298
//   0xbc04296  xor eax,eax                                ; a1+0x10 == 0 -> rax = 0
//   0xbc04298  mov rcx,[rdx+8]                            ; R a1+0x8 (task-node*)
//   0xbc0429c  mov [rsi+0x3B0],rcx                        ; W a0+0x3B0 = a1+0x8
//   0xbc042a3  mov rdi,[rsi+0x3B8]                        ; R a0+0x3B8 (old RefCounted*)
//   0xbc042aa  mov [rsi+0x3B8],rax                        ; W a0+0x3B8 = a1+0x10 (or 0)
//   0xbc042b1  test rdi,rdi
//   0xbc042b4  je short 0xBC042E1                         ; skip release when old == 0
//   0xbc042b6  lock dec dword ptr [rdi+8]                 ; W old+0x8  strong release
//   0xbc042ba  jne short 0xBC042E1                        ; strong != 0 -> done
//   0xbc042bc  mov rax,[rdi]                              ; R old+0x0 (vtable)
//   0xbc042bf  mov rax,[rax]                              ; R vtable+0x0 (destructor slot), into rax
//   0xbc042c2  mov rcx,rdi
//   0xbc042c5  call qword ptr [0xF99FFA0]                 ; [data_f99ffa0] = sub_eea6040, class vendor boundary thunk: `jmp rax` -> old_dtor(old)
//   0xbc042cb  lock dec dword ptr [rdi+0xC]               ; W old+0xC  weak release
//   0xbc042cf  jne short 0xBC042E1                        ; weak != 0 -> done
//   0xbc042d1  mov rax,[rdi]                              ; R old+0x0 (vtable)
//   0xbc042d4  mov rax,[rax+8]                            ; R vtable+8 (deleter slot)
//   0xbc042d8  mov rcx,rdi
//   0xbc042db  call qword ptr [0xF99FFA0]                 ; -> old_deleter(old)
//   0xbc042e1  mov rax,[rsi+0x3B0]                        ; R a0+0x3B0 (== a1+0x8)
//   0xbc042e8  mov rcx,[rax+0x10]                         ; R (a1+0x8)+0x10 -> RCX
//   0xbc042ec  movzx edx,word ptr [rax+8]                 ; R (a1+0x8)+8 -> RDX (zero-extended u16)
//   0xbc042f0  lea r8,[0xBC04530]                         ; R8 = sub_bc04530 ("pass task render-thread body (class D)")
//   0xbc042f7  mov r9,rsi                                 ; R9 = a0
//   0xbc042fa  add rsp,0x28
//   0xbc042fe  pop rdi
//   0xbc042ff  pop rsi
//   0xbc04300  jmp 0xBC61560                              ; tail call sub_bc61560(RCX, RDX, R8, R9)
//
// Same reads, same writes (value and order), same calls in the same order, same return.
// No null guard or SEH (the original has none; none added here). [V] every instruction
// line above, from the exe disassembly of [0xbc04270, 0xbc04305).
//
// a0 (RCX) - pass destination item (PassDst):
//   +0x3A8 u64         W  copied from a1+0x0                                    [V]
//   +0x3B0 void*       W  copied from a1+0x8                                     [V]
//   +0x3B8 RefCounted* RW  old value released (strong+weak), then a1+0x10 stored [V]
// a1 (RDX) - pass source item (PassSrc):
//   +0x0 u64           R  -> a0+0x3A8                                           [V]
//   +0x8 void*         R  -> a0+0x3B0 (task-node object)                        [V]
//   +0x10 RefCounted*  R  addref'd if non-zero, stored to a0+0x3B8              [V]
// The task-node object at a1+0x8 is read at +0x8 (u16 -> RDX) and +0x10 (ptr ->
// RCX) for the tail call. No game struct type is identifiable from the
// disassembly; the layouts below mirror exactly the fields used and nothing more.
// Every offset is [V] from 0xbc04270..0xbc04305.

static constexpr std::size_t kPassDstField0x3A8 = 0x3A8;
static constexpr std::size_t kPassDstField0x3B0 = 0x3B0;
static constexpr std::size_t kPassDstField0x3B8 = 0x3B8;
static constexpr std::size_t kPassDstSize = 0x3C0;

static constexpr std::size_t kPassSrcField0x0 = 0x0;
static constexpr std::size_t kPassSrcField0x8 = 0x8;
static constexpr std::size_t kPassSrcField0x10 = 0x10;
static constexpr std::size_t kPassSrcSize = 0x18;

static constexpr std::size_t kRefCountedVtable = 0x0;
static constexpr std::size_t kRefCountedStrong = 0x8;
static constexpr std::size_t kRefCountedWeak = 0xC;
static constexpr std::size_t kRefCountedSize = 0x10;

static constexpr std::size_t kTaskNodeField0x8 = 0x8;
static constexpr std::size_t kTaskNodeField0x10 = 0x10;
static constexpr std::size_t kTaskNodeSize = 0x18;

struct RefCounted {
    void* vtable;                          // +0x0: R vtable (slot 0 = destructor, slot 8 = deleter) [V]
    std::atomic<std::uint32_t> strong;     // +0x8: R/W lock inc (addref) / lock dec (release) [V]
    std::atomic<std::uint32_t> weak;       // +0xC: R/W lock dec (weak release) [V]
};                                         // size 0x10

struct PassDst {
    std::uint8_t pad_0x0[0x3A8];
    std::uint64_t field_0x3A8;             // +0x3A8: W a0+0x3A8 = a1+0x0 [V]
    void* field_0x3B0;                     // +0x3B0: W a0+0x3B0 = a1+0x8 [V]
    RefCounted* field_0x3B8;               // +0x3B8: RW old released / a1+0x10 stored [V]
};                                         // size 0x3C0

struct PassSrc {
    std::uint64_t field_0x0;               // +0x0: R a1+0x0 -> a0+0x3A8 [V]
    void* field_0x8;                       // +0x8: R a1+0x8 (task-node*) -> a0+0x3B0 [V]
    RefCounted* field_0x10;                // +0x10: R a1+0x10, addref'd -> a0+0x3B8 [V]
};                                         // size 0x18

struct TaskNode {
    std::uint8_t pad_0x0[0x8];
    std::uint16_t field_0x8;               // +0x8: R -> RDX (zero-extended) for sub_bc61560 [V]
    std::uint8_t pad_0xA[0x6];
    void* field_0x10;                      // +0x10: R -> RCX for sub_bc61560 [V]
};                                         // size 0x18

static_assert(offsetof(RefCounted, vtable) == kRefCountedVtable,
              "sub_bc04270: RefCounted+0x0 is the vtable pointer, read at 0xbc042bc and 0xbc042d1");
static_assert(offsetof(RefCounted, strong) == kRefCountedStrong,
              "sub_bc04270: RefCounted+0x8 is lock inc/dec'd at 0xbc0428c and 0xbc042b6");
static_assert(offsetof(RefCounted, weak) == kRefCountedWeak,
              "sub_bc04270: RefCounted+0xC is lock dec'd at 0xbc042cb");
static_assert(sizeof(RefCounted) == kRefCountedSize,
              "sub_bc04270: RefCounted size");
static_assert(offsetof(PassDst, field_0x3A8) == kPassDstField0x3A8,
              "sub_bc04270: PassDst+0x3A8 written at 0xbc0427c");
static_assert(offsetof(PassDst, field_0x3B0) == kPassDstField0x3B0,
              "sub_bc04270: PassDst+0x3B0 written at 0xbc0429c");
static_assert(offsetof(PassDst, field_0x3B8) == kPassDstField0x3B8,
              "sub_bc04270: PassDst+0x3B8 read/written at 0xbc042a3 and 0xbc042aa");
static_assert(sizeof(PassDst) == kPassDstSize,
              "sub_bc04270: PassDst size");
static_assert(offsetof(PassSrc, field_0x0) == kPassSrcField0x0,
              "sub_bc04270: PassSrc+0x0 read at 0xbc04279");
static_assert(offsetof(PassSrc, field_0x8) == kPassSrcField0x8,
              "sub_bc04270: PassSrc+0x8 read at 0xbc04298");
static_assert(offsetof(PassSrc, field_0x10) == kPassSrcField0x10,
              "sub_bc04270: PassSrc+0x10 read at 0xbc04283");
static_assert(sizeof(PassSrc) == kPassSrcSize,
              "sub_bc04270: PassSrc size");
static_assert(offsetof(TaskNode, field_0x8) == kTaskNodeField0x8,
              "sub_bc04270: TaskNode+0x8 read at 0xbc042ec");
static_assert(offsetof(TaskNode, field_0x10) == kTaskNodeField0x10,
              "sub_bc04270: TaskNode+0x10 read at 0xbc042e8");
static_assert(sizeof(TaskNode) == kTaskNodeSize,
              "sub_bc04270: TaskNode size");

namespace native {

// sub_bc61560 (0xbc61560, lift set, "custom item submit (key bit 53)") - lifted by its own
// unit (D2 dossier). Forward-declared here with the exact ABI seen at the tail call of
// sub_bc04270: RCX = *(void**)(TaskNode*)(a1+0x8) + 0x10, RDX = u16 at (a1+0x8)+8
// (zero-extended), R8 = 0xBC04530 (sub_bc04530), R9 = a0. Returns void: all its exit
// paths end in ret/jmp without a computed value [V].
void sub_bc61560(void* a0, std::uint16_t a1, void* a2, void* a3);

// Exact x64 Microsoft ABI mirror of the original: RCX = a0 (PassDst*), RDX = a1 (PassSrc*),
// return void via tail call to sub_bc61560 (0xbc04300 jmp 0xBC61560).
void sub_bc04270(PassDst* a0, PassSrc* a1);

} // namespace native
