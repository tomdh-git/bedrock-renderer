// LIFT 0x87440 size 0xcf 1.26.62.01 sub_87440
#include <cstddef>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/native/helpers/sub_87440.h"

namespace native {

static_assert(offsetof(ReleaseContext, child_begin) == 0x28, "sub_87440: child_begin offset");
static_assert(offsetof(ReleaseContext, child_end) == 0x30, "sub_87440: child_end offset");
static_assert(offsetof(ReleaseContext, limit) == 0x38, "sub_87440: limit offset");
static_assert(offsetof(ReleaseContext, flag) == 0x40, "sub_87440: flag offset");

// sub_87440 (0x87440, size 0xcf, 1.26.62.01).
//
// Release a node tree rooted at the release context a0 (RCX).
//   +0x28 child_begin, +0x30 child_end, +0x38 limit (all void*);
//   +0x40 flag byte: non-zero => already released, return immediately.
// Children are 0x40-byte nodes, released recursively via sub_9c590.
// After all children are released the context block is handed to
// sub_e935700 (argument = block size when remaining >= 0x1000,
// otherwise child_begin), the three slot fields are cleared, and the
// function tails to sub_9c650(a0 + 0x10).
//
// Heap-corruption check failure (block_start >= 0x20): calls the function
// pointer in data slot RVA 0xF9A8C78 with five zero arguments; that block
// ends in int3 (noreturn).
//
// Verbatim instruction lines of the function (match rdis dis 0x87440):
#if 0
0x87440  push r14
0x87442  push rsi
0x87443  push rdi
0x87444  push rbx
0x87445  sub rsp,0x28
0x87449  cmp byte ptr [rcx+0x40],0
0x8744d  je short 0x87459
0x8744f  add rsp,0x28
0x87453  pop rbx
0x87454  pop rdi
0x87455  pop rsi
0x87456  pop r14
0x87458  ret
0x87459  mov rdi,[rcx+0x28]
0x8745d  test rdi,rdi
0x87460  je 0x874E3
0x87466  lea rsi,[rcx+0x28]
0x8746a  mov rbx,[rcx+0x30]
0x8746e  cmp rdi,rbx
0x87471  je short 0x8749A
0x87473  mov r14,rcx
0x87476  nop [rax+rax]
0x87480  mov rcx,rsi
0x87483  mov rdx,rdi
0x87486  call 0x9C590
0x8748b  add rdi,0x40
0x8748f  cmp rdi,rbx
0x87492  jne short 0x87480
0x87494  mov rdi,[rsi]
0x87497  mov rcx,r14
0x8749a  mov rdx,[rcx+0x38]
0x8749e  sub rdx,rdi
0x874a1  cmp rdx,0x1000
0x874a8  jb short 0x874C7
0x874aa  mov rax,[rdi-8]
0x874ae  add rdi,0xFFFFFFFFFFFFFFF8
0x874b2  sub rdi,rax
0x874b5  cmp rdi,0x20
0x874b9  jae short 0x874F5
0x874bb  mov rbx,rcx
0x874be  or rdx,0x27
0x874c2  mov rdi,rax
0x874c5  jmp short 0x874CA
0x874c7  mov rbx,rcx
0x874ca  mov rcx,rdi
0x874cd  call 0xE935700
0x874d2  xorps xmm0,xmm0
0x874d5  movups [rsi],xmm0
0x874d8  mov qword ptr [rsi+0x10],0
0x874e0  mov rcx,rbx
0x874e3  add rcx,0x10
0x874e7  add rsp,0x28
0x874eb  pop rbx
0x874ec  pop rdi
0x874ed  pop rsi
0x874ee  pop r14
0x874f0  jmp 0x9C650
0x874f5  mov qword ptr [rsp+0x20],0
0x874fe  xor ecx,ecx
0x87500  xor edx,edx
0x87502  xor r8d,r8d
0x87505  xor r9d,r9d
0x87508  call qword ptr [0xF9A8C78]
0x8750e  int3
#endif

void* sub_87440(void* a0 /* rcx */) {
    auto* ctx = reinterpret_cast<ReleaseContext*>(a0);

    // 0x87440..0x87445: push r14; push rsi; push rdi; push rbx; sub rsp,0x28
    // (callee-saved registers and stack frame; no observable effect)

    // 0x87449  cmp byte ptr [rcx+0x40],0   /   0x8744d  je short 0x87459
    if (ctx->flag != 0) {
        // 0x8744f..0x87458: add rsp,0x28; pop rbx,rdi,rsi,r14; ret
        // RAX is not written by the function in this path (indeterminate).
        return nullptr;
    }

    // 0x87459  mov rdi,[rcx+0x28]
    void* child_begin = ctx->child_begin;

    // 0x8745d  test rdi,rdi   /   0x87460  je 0x874E3
    if (child_begin == nullptr) {
        // 0x874e3..0x874f0: add rcx,0x10; epilogue; jmp 0x9C650
        return sub_9c650(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(a0) + 0x10));
    }

    // 0x87466  lea rsi,[rcx+0x28]
    void** child_begin_slot = &ctx->child_begin;
    // 0x8746a  mov rbx,[rcx+0x30]
    void* child_end = ctx->child_end;

    // 0x8746e  cmp rdi,rbx   /   0x87471  je short 0x8749A
    if (child_begin != child_end) {
        // 0x87473  mov r14,rcx
        void* ctx_saved = a0;

        // 0x87476  nop [rax+rax]   (padding, no effect)
        // 0x87480..0x87492: loop releasing children
        do {
            // 0x87480  mov rcx,rsi   /   0x87483  mov rdx,rdi   /   0x87486  call 0x9C590
            sub_9c590(reinterpret_cast<void*>(child_begin_slot), child_begin);
            // 0x8748b  add rdi,0x40   /   0x8748f  cmp rdi,rbx   /   0x87492  jne short 0x87480
            child_begin = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(child_begin) + 0x40);
        } while (child_begin != child_end);

        // 0x87494  mov rdi,[rsi]
        child_begin = ctx->child_begin;
        // 0x87497  mov rcx,r14   (ctx_saved = a0, unchanged)
        (void)ctx_saved;
    }

    // 0x8749a  mov rdx,[rcx+0x38]   /   0x8749e  sub rdx,rdi
    uintptr_t remaining = reinterpret_cast<uintptr_t>(ctx->limit) - reinterpret_cast<uintptr_t>(child_begin);

    // 0x874a1  cmp rdx,0x1000   /   0x874a8  jb short 0x874C7
    void* free_arg = child_begin;

    if (remaining >= 0x1000) {
        // 0x874aa  mov rax,[rdi-8]
        uintptr_t block_size = *reinterpret_cast<uintptr_t*>(
            reinterpret_cast<uintptr_t>(child_begin) - 8);
        // 0x874ae  add rdi,0xFFFFFFFFFFFFFFF8   /   0x874b2  sub rdi,rax
        uintptr_t block_start = (reinterpret_cast<uintptr_t>(child_begin) - 8) - block_size;
        // 0x874b5  cmp rdi,0x20   /   0x874b9  jae short 0x874F5
        if (block_start >= 0x20) {
            // 0x874f5  mov qword ptr [rsp+0x20],0;
            // 0x874fe..0x87505  xor ecx,edx,r8d,r9d (all zero);
            // 0x87508  call qword ptr [0xF9A8C78]   ; [data_f9a8c78], five zero arguments
            // 0x8750e  int3   ; block terminator (noreturn)
            using FailFn = void (*)(void*, void*, void*, void*, void*);
            FailFn fail = reinterpret_cast<FailFn>(
                *reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF9A8C78));
            fail(nullptr, nullptr, nullptr, nullptr, nullptr);
            __assume(false);
        }
        // 0x874bb  mov rbx,rcx   (rbx = a0, already set)
        // 0x874be  or rdx,0x27   (dead)
        // 0x874c2  mov rdi,rax
        free_arg = reinterpret_cast<void*>(block_size);
    }
    // 0x874c7  mov rbx,rcx   (rbx = a0, already set in both branches)

    // 0x874ca  mov rcx,rdi   /   0x874cd  call 0xE935700
    sub_e935700(free_arg);

    // 0x874d2  xorps xmm0,xmm0   /   0x874d5  movups [rsi],xmm0   ; clear child_begin, child_end
    // 0x874d8  mov qword ptr [rsi+0x10],0   ; clear limit
    ctx->child_begin = nullptr;
    ctx->child_end = nullptr;
    ctx->limit = nullptr;

    // 0x874e0  mov rcx,rbx   (rcx = a0)
    // 0x874e3  add rcx,0x10   /   epilogue   /   0x874f0  jmp 0x9C650
    return sub_9c650(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(a0) + 0x10));
}

LIFT_FN(sub_87440, "sub_87440", 0x87440, sub_87440, nullptr);

} // namespace native
