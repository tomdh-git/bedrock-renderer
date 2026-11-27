#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_56cc4f0 (0x56cc4f0, size 0xef, 1.26.62.01): frame-graph buffer/node releaser.
//
//   0x56cc4f0  mov rsi,rcx                       ; rsi = self (State)
//   0x56cc4fc  mov rcx,[rcx+0x18]                ; rcx = self->f18 (heap buffer)
//   0x56cc500  test rcx,rcx
//   0x56cc503  je short 0x56CC548                ; buffer == 0 -> skip buffer free
//   0x56cc505  mov rdx,[rsi+0x28]                ; rdx = self->f28 (buffer end)
//   0x56cc509  sub rdx,rcx                       ; rdx = buffer size = f28 - f18
//   0x56cc50c  cmp rdx,0x1000
//   0x56cc513  jb short 0x56CC531                ; size < 0x1000 -> small buffer path
//   0x56cc515  mov rax,[rcx-8]                   ; rax = *(buffer - 8) (heap header)
//   0x56cc519  add rcx,0xFFFFFFFFFFFFFFF8        ; rcx = buffer - 8
//   0x56cc51d  sub rcx,rax                       ; rcx = (buffer - 8) - *(buffer - 8)
//   0x56cc520  cmp rcx,0x20
//   0x56cc524  jae 0x56CC5C5                     ; heap corrupt -> _invoke_watson (noreturn)
//   0x56cc52a  add rdx,0x27                      ; dead write (not read afterward)
//   0x56cc52e  mov rcx,rax                       ; rcx = *(buffer - 8)
//   0x56cc531  lea rdi,[rsi+0x18]                ; rdi = &self->f18
//   0x56cc535  call 0xE935700                    ; sub_e935700(freeArg); rdx is dead in sub_e935700
//   0x56cc53a  xorps xmm0,xmm0
//   0x56cc53d  movups [rdi],xmm0                 ; self->f18 = 0 (16 bytes)
//   0x56cc540  mov qword ptr [rdi+0x10],0        ; self->f28 = 0
//   0x56cc548  mov rax,[rsi+8]                   ; rax = self->f8 (list head)
//   0x56cc54c  mov rcx,[rax+8]                   ; rcx = head->f8 (pointer to pointer slot)
//   0x56cc550  mov qword ptr [rcx],0             ; *head->f8 = 0
//   0x56cc557  mov r14,[rax]                     ; r14 = head->f0 (first node)
//   0x56cc55a  jmp short 0x56CC56D
//   0x56cc56d  test r14,r14                      ; node loop
//   0x56cc570  je short 0x56CC5AE                ; no more nodes -> tail call
//   0x56cc572  mov rdi,r14                       ; rdi = node
//   0x56cc575  mov r14,[r14]                     ; r14 = node->f0 (next node)
//   0x56cc578  mov rbx,[rdi+0x18]                ; rbx = node->f18 (RefObj)
//   0x56cc57c  test rbx,rbx
//   0x56cc57f  je short 0x56CC560                ; no RefObj -> skip destroy
//   0x56cc581  lock dec dword ptr [rbx+8]        ; RefObj->f8-- (refcount)
//   0x56cc585  jne short 0x56CC560               ; refcount != 0 -> skip destroy
//   0x56cc587  mov rax,[rbx]                     ; rax = RefObj->vfptr
//   0x56cc58a  mov rax,[rax]                     ; rax = vfptr[0] (destructor 0)
//   0x56cc58d  mov rcx,rbx
//   0x56cc590  call qword ptr [0xF99FFA0]        ; sub_eea6040(RefObj, vfptr[0])
//   0x56cc596  lock dec dword ptr [rbx+0xC]      ; RefObj->fc-- (refcount2)
//   0x56cc59a  jne short 0x56CC560               ; refcount2 != 0 -> skip destroy
//   0x56cc59c  mov rax,[rbx]                     ; rax = RefObj->vfptr
//   0x56cc59f  mov rax,[rax+8]                   ; rax = vfptr[1] (destructor 1)
//   0x56cc5a3  mov rcx,rbx
//   0x56cc5a6  call qword ptr [0xF99FFA0]        ; sub_eea6040(RefObj, vfptr[1])
//   0x56cc5ac  jmp short 0x56CC560
//   0x56cc560  mov edx,0x28                      ; dead in sub_e935700
//   0x56cc565  mov rcx,rdi
//   0x56cc568  call 0xE935700                    ; sub_e935700(node)
//   0x56cc5ae  mov rcx,[rsi+8]                   ; rcx = self->f8 (list head)
//   0x56cc5b2  mov edx,0x28                      ; dead in sub_e935700
//   0x56cc5b7  add rsp,0x28                      ; epilogue
//   0x56cc5c0  jmp 0xE935700                     ; return sub_e935700(head) (tail call)
//
// Corrupt-heap path (0x56cc5c5..0x56cc5df):
//   0x56cc5c5  mov qword ptr [rsp+0x20],0        ; watson reserved arg = 0
//   0x56cc5ce..0x56cc5d5  xor ecx,edx,r8d,r9d    ; all args null/zero
//   0x56cc5d8  call qword ptr [0xF9A8C78]        ; _invoke_watson(nullptr,nullptr,nullptr,0,0)
//   0x56cc5de  int3                              ; noreturn pad
//
// x64 Microsoft ABI: RCX = self, return in RAX = sub_e935700 result (void*,
// forwarded by the tail call). No null guards and no SEH exist in the original.

// Refcounted object owned by each node (rbx base).
struct RefObj {
    void* vfptr;             // +0x00  vtable; vfptr[0] and vfptr[1] are destructor thunks
    std::uint32_t f8;        // +0x08  refcount   (lock dec dword)
    std::uint32_t fc;        // +0x0c  refcount2  (lock dec dword)
};

// List node (r14/rdi base).
struct Node {
    void* f0;                // +0x00  next node
    std::uint8_t pad0x08[0x10];
    RefObj* f18;             // +0x18  owned RefObj
};

// List head (rax base, self->f8).
struct ListHead {
    void* f0;                // +0x00  first node
    void** f8;               // +0x08  pointer to a pointer slot nulled by this function
};

// Self object (rcx/rsi base).
struct State {
    std::uint8_t pad0x00[0x8];
    ListHead* f8;            // +0x08  list head
    std::uint8_t pad0x10[0x8];
    void* f18;               // +0x18  heap buffer
    std::uint8_t pad0x20[0x8];
    std::uint64_t f28;       // +0x28  buffer end
};

static_assert(offsetof(RefObj, vfptr) == 0x00, "sub_56cc4f0 RefObj vfptr at +0x00");
static_assert(offsetof(RefObj, f8) == 0x08, "sub_56cc4f0 RefObj f8 at +0x08");
static_assert(offsetof(RefObj, fc) == 0x0c, "sub_56cc4f0 RefObj fc at +0x0c");
static_assert(sizeof(RefObj) == 0x10, "sub_56cc4f0 RefObj size");

static_assert(offsetof(Node, f0) == 0x00, "sub_56cc4f0 Node f0 at +0x00");
static_assert(offsetof(Node, f18) == 0x18, "sub_56cc4f0 Node f18 at +0x18");
static_assert(sizeof(Node) == 0x20, "sub_56cc4f0 Node size");

static_assert(offsetof(ListHead, f0) == 0x00, "sub_56cc4f0 ListHead f0 at +0x00");
static_assert(offsetof(ListHead, f8) == 0x08, "sub_56cc4f0 ListHead f8 at +0x08");
static_assert(sizeof(ListHead) == 0x10, "sub_56cc4f0 ListHead size");

static_assert(offsetof(State, f8) == 0x08, "sub_56cc4f0 State f8 at +0x08");
static_assert(offsetof(State, f18) == 0x18, "sub_56cc4f0 State f18 at +0x18");
static_assert(offsetof(State, f28) == 0x28, "sub_56cc4f0 State f28 at +0x28");
static_assert(sizeof(State) == 0x30, "sub_56cc4f0 State size");

// Data-slot RVA (call qword ptr [slot]; pointer read at call time, hard rule 69).
static constexpr std::uintptr_t kRvaFailSlot = 0xF9A8C78;  // _invoke_watson (noreturn)

// _invoke_watson via IAT data slot 0xF9A8C78.
// Indirect call through data slot (hard rule 69): read the pointer at call time.
// __declspec(noreturn): never returns to the caller.
__declspec(noreturn) void sub_f9a8c78_watson(const wchar_t* expression,
                                             const wchar_t* function,
                                             const wchar_t* file,
                                             unsigned int line,
                                             unsigned int reserved);

namespace native::helpers {

// Lifted body of sub_56cc4f0 (0x56cc4f0, size 0xef, 1.26.62.01).
void* sub_56cc4f0(void* self);

} // namespace native::helpers
