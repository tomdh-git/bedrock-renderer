// LIFT 0x9c590 size 0xb4 1.26.62.01 sub_9c590
#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/native/helpers/sub_9c590.h"

namespace native {

// sub_9c590 (0x9c590, size 0xb4, 1.26.62.01).
//
// Recursive release of a node tree. Each node is 0x40 bytes:
//   +0x28 child list begin pointer (R/W)
//   +0x30 child list end   pointer (R/W)
//   +0x38 allocation limit pointer (R/W)
// Children are packed back-to-back with stride 0x40, so each child is itself
// such a node and is released recursively (0x9C5C6 call 0x9C590). After all
// children are released the node's own block is handed to sub_e935700
// (0x9C602 call 0xE935700; that function is a tail jump to sub_392960 and
// reads RCX only), the three slot fields (+0x28/+0x30/+0x38) are cleared
// (0x9C60A movups [rdi],xmm0; 0x9C60D mov [rdi+0x10],0), and the function
// tails to sub_9c650 with RCX = node + 0x10 (0x9C625 jmp 0x9C650).
//
// The block at 0x9C62A (heap-corruption check failure) reads the function
// pointer stored in data slot RVA 0xF9A8C78 (VA = imageBase() + 0xF9A8C78;
// see 0x9C63D call qword ptr [0xF9A8C78] / [data_f9a8c78]), calls it with
// RCX=RDX=R8=R9=0 and 5th stack argument 0, and ends in int3 (noreturn).
//
// RCX (a1, "slot") is dead on entry: it is written before every read
// (0x9C5C0 mov rcx,rdi / 0x9C5FF mov rcx,rbx / 0x9C619 mov rcx,rsi) and never
// read, so the observable behavior is a function of RDX (the node) only.
//
// Verbatim instruction lines of the function (match rdis dis 0x9c590):
#if 0
0x9C590  push r14
0x9C592  push rsi
0x9C593  push rdi
0x9C594  push rbx
0x9C595  sub rsp,0x28
0x9C599  mov rsi,rdx
0x9C59C  mov rbx,[rdx+0x28]
0x9C5A0  test rbx,rbx
0x9C5A3  je short 0x9C615
0x9C5A5  lea rdi,[rsi+0x28]
0x9C5A9  mov r14,[rsi+0x30]
0x9C5AD  cmp rbx,r14
0x9C5B0  je short 0x9C5D7
0x9C5B2  nop [rax+rax]
0x9C5C0  mov rcx,rdi
0x9C5C3  mov rdx,rbx
0x9C5C6  call 0x9C590
0x9C5CB  add rbx,0x40
0x9C5CF  cmp rbx,r14
0x9C5D2  jne short 0x9C5C0
0x9C5D4  mov rbx,[rdi]
0x9C5D7  mov rdx,[rsi+0x38]
0x9C5DB  sub rdx,rbx
0x9C5DE  cmp rdx,0x1000
0x9C5E5  jb short 0x9C5FF
0x9C5E7  mov rax,[rbx-8]
0x9C5EB  add rbx,0xFFFFFFFFFFFFFFF8
0x9C5EF  sub rbx,rax
0x9C5F2  cmp rbx,0x20
0x9C5F6  jae short 0x9C62A
0x9C5F8  or rdx,0x27
0x9C5FC  mov rbx,rax
0x9C5FF  mov rcx,rbx
0x9C602  call 0xE935700
0x9C607  xorps xmm0,xmm0
0x9C60A  movups [rdi],xmm0
0x9C60D  mov qword ptr [rdi+0x10],0
0x9C615  add rsi,0x10
0x9C619  mov rcx,rsi
0x9C61c  add rsp,0x28
0x9C620  pop rbx
0x9C621  pop rdi
0x9C622  pop rsi
0x9C623  pop r14
0x9C625  jmp 0x9C650
0x9C62A  mov qword ptr [rsp+0x20],0
0x9C633  xor ecx,ecx
0x9C635  xor edx,edx
0x9C637  xor r8d,r8d
0x9C63A  xor r9d,r9d
0x9C63D  call qword ptr [0xF9A8C78]
0x9C643  int3
#endif

void* sub_9c590(void* slot /* rcx: dead slot pointer, never read */, void* node /* rdx */) {
    (void)slot;
    Node* n = reinterpret_cast<Node*>(node);

    // 0x9C590..0x9C595: push r14; push rsi; push rdi; push rbx; sub rsp,0x28
    // (callee-saved registers and stack frame; no observable effect)

    // 0x9C599  mov rsi,rdx   /   0x9C59C  mov rbx,[rdx+0x28]
    void* rbx = n->child_begin;

    // 0x9C5A0  test rbx,rbx   /   0x9C5A3  je short 0x9C615
    if (rbx == nullptr) {
        // 0x9C615..0x9C625: add rsi,0x10; mov rcx,rsi; add rsp,0x28; pop rbx,rdi,rsi,r14; jmp 0x9C650
        return sub_9c650(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(node) + 0x10));
    }

    // 0x9C5A5  lea rdi,[rsi+0x28]
    void** rdi = &n->child_begin;
    // 0x9C5A9  mov r14,[rsi+0x30]
    void* r14 = n->child_end;
    // 0x9C5AD  cmp rbx,r14   /   0x9C5B0  je short 0x9C5D7
    if (rbx != r14) {
        // 0x9C5B2  nop [rax+rax]
        do {
            // 0x9C5C0  mov rcx,rdi   /   0x9C5C3  mov rdx,rbx   /   0x9C5C6  call 0x9C590
            sub_9c590(reinterpret_cast<void*>(rdi), rbx);   // 0x9C5C6  call 0x9C590  (recursive)
            // 0x9C5CB  add rbx,0x40   /   0x9C5CF  cmp rbx,r14   /   0x9C5D2  jne short 0x9C5C0
            rbx = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(rbx) + 0x40);
        } while (rbx != r14);
    }
    // 0x9C5D4  mov rbx,[rdi]
    rbx = n->child_begin;

    // 0x9C5D7  mov rdx,[rsi+0x38]   /   0x9C5DB  sub rdx,rbx
    uintptr_t remaining = reinterpret_cast<uintptr_t>(n->limit) - reinterpret_cast<uintptr_t>(rbx);
    // 0x9C5DE  cmp rdx,0x1000   /   0x9C5E5  jb short 0x9C5FF
    void* free_ptr = rbx;
    uintptr_t free_rdx = remaining;   // RDX at the call site (dead for sub_e935700/sub_392960: RCX only)
    if (remaining >= 0x1000) {
        // 0x9C5E7  mov rax,[rbx-8]
        uintptr_t block_size = *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(rbx) - 8);
        // 0x9C5EB  add rbx,0xFFFFFFFFFFFFFFF8   /   0x9C5EF  sub rbx,rax
        uintptr_t block_start = (reinterpret_cast<uintptr_t>(rbx) - 8) - block_size;
        // 0x9C5F2  cmp rbx,0x20   /   0x9C5F6  jae short 0x9C62A
        if (block_start >= 0x20) {
            // 0x9C62A  mov qword ptr [rsp+0x20],0;
            // 0x9C633  xor ecx,ecx   /   0x9C635  xor edx,edx;
            // 0x9C637  xor r8d,r8d   /   0x9C63A  xor r9d,r9d;
            // 0x9C63D  call qword ptr [0xF9A8C78]   ; [data_f9a8c78], all arguments zero
            // 0x9C643  int3   ; block terminator (unreachable)
            using FailFn = void (*)(void*, void*, void*, void*, void*);
            FailFn fail = reinterpret_cast<FailFn>(
                *reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF9A8C78));
            fail(nullptr, nullptr, nullptr, nullptr, nullptr);   // the slot handler is noreturn
            // 0x9C643  int3   ; block terminator (unreachable)
            __assume(false);
        }
        // 0x9C5F8  or rdx,0x27   /   0x9C5FC  mov rbx,rax
        free_rdx = remaining | 0x27;
        free_ptr = reinterpret_cast<void*>(block_size);
    }
    // 0x9C5FF  mov rcx,rbx   /   0x9C602  call 0xE935700   ; RDX = free_rdx (dead for callee)
    (void)free_rdx;
    sub_e935700(free_ptr);

    // 0x9C607  xorps xmm0,xmm0   /   0x9C60A  movups [rdi],xmm0   ; +0x28 = 0, +0x30 = 0
    // 0x9C60D  mov qword ptr [rdi+0x10],0                      ; +0x38 = 0
    n->child_begin = nullptr;
    n->child_end = nullptr;
    n->limit = nullptr;

    // 0x9C615  add rsi,0x10   /   0x9C619  mov rcx,rsi   /   epilogue   /   0x9C625  jmp 0x9C650
    return sub_9c650(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(node) + 0x10));
}

LIFT_FN(sub_9c590, "sub_9c590", 0x9C590, sub_9c590, nullptr);

} // namespace native
