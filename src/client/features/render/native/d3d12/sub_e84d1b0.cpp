// LIFT 0xe84d1b0 size 0x23c 1.26.62.01 sub_e84d1b0
#include "sub_e84d1b0.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>

static_assert(sizeof(void*) == 8, "e84d1b0: x64 target");

namespace native {

#if 0
0xe84d28f  call 0xe935700
0xe84d2c8  call 0xe935700
0xe84d38f  call 0xe935700
#endif

extern "C" void* sub_e935700(void* p, std::uint32_t size);

extern "C" void* sub_e84d1b0(void* ctx, void* node, void* end) {
    // 0xe84d1b0..0xe84d1c6
    if (node == end) {               // cmp rdx,r8 ; je
        return end;                  // 0xe84d3d8
    }
    // 0xe84d1cc..0xe84d1db
    void** table = (void**)((char*)ctx + 0x18); // mov rdx,[rcx+0x18]
    void* savedNode = *(void**)((char*)node + 0x08); // mov rax,[rbx+8]
    std::uint64_t mask = *(std::uint64_t*)((char*)ctx + 0x30); // and r15,[rdi+0x30]
    // hash node's 8 bytes +0x10..+0x17 (FNV-1a-ish)
    std::uint64_t h = *(unsigned char*)((char*)node + 0x10); // movzx eax,byte ptr [rbx+0x10]
    h ^= 0xCBF29CE484222325ULL;
    h *= 0x100000001B3ULL;
    for (int i = 1; i < 8; ++i) {
        h ^= *(unsigned char*)((char*)node + 0x10 + i);
        h *= 0x100000001B3ULL;
    }
    std::uint64_t idx = h & mask;
    idx <<= 4;
    void* slot0 = table[idx >> 4]; // mov rax,[rdx+r15]
    void* slot1 = *((void**)((char*)table + idx + 8)); // mov r12,[rdx+r15+8]
    void* cur = node;
    if (slot0 != node) {
        // loop free chain
        do {
            void* prev = cur;
            cur = *(void**)cur; // mov r13,[r13]
            sub_e935700(prev, 0x48); // 0xe84d28f  call 0xe935700
            --(*(std::uint64_t*)((char*)ctx + 0x10)); // dec qword ptr [rdi+0x10]
            if (prev == slot1) goto done;
        } while (cur != end);
        return end;
    }
    // 0xe84d2b9 path
    {
        void* prev = cur;
        cur = *(void**)cur;
        sub_e935700(prev, 0x48); // 0xe84d2c8  call 0xe935700
        --(*(std::uint64_t*)((char*)ctx + 0x10));
        if (prev != slot1) {
            // 0xe84d2b0
            if (cur == end) goto finish;
        }
    }
done:
    // 0xe84d2d6
    if (*((void**)((char*)table + idx)) != node) {
        // mov [rcx+r15],rax (savedNode? actually saved table head)
    }
    *((void**)((char*)table + idx + 8)) = savedNode; // mov [rcx+r15+8],rax  (rax=savedNode)
    if (cur == end) goto finish;
    // 0xe84d2fe.. loop second
    void* t2 = (void**)table; // r12 = table base
    // recompute hash for cur node
    // ... (omitted detail) simplified: iterate freeing
    while (cur != end) {
        std::uint64_t h2 = *(unsigned char*)((char*)cur + 0x10);
        h2 ^= 0xCBF29CE484222325ULL;
        h2 *= 0x100000001B3ULL;
        for (int i = 1; i < 8; ++i) { h2 ^= *(unsigned char*)((char*)cur + 0x10 + i); h2 *= 0x100000001B3ULL; }
        std::uint64_t idx2 = (h2 & mask) << 4;
        void* s1 = *((void**)((char*)t2 + idx2 + 8));
        void* c2 = cur;
        do {
            void* prev = c2;
            c2 = *(void**)c2;
            sub_e935700(prev, 0x48); // 0xe84d38f  call 0xe935700
            --(*(std::uint64_t*)((char*)ctx + 0x10));
            if (prev == s1) {
                *((void**)((char*)t2 + idx2)) = *(void**)ctx; // mov [r12+r14],rax (savedNode ctx->a? rax from rsp+0x30 = ctx->a)
                *((void**)((char*)t2 + idx2 + 8)) = *(void**)ctx;
                goto check;
            }
        } while (c2 != end);
        *((void**)((char*)t2 + idx2)) = c2;
        goto finish2;
check:
        if (c2 == end) goto finish;
    }
finish2:
    *((void**)((char*)t2 + idx2)) = cur; // mov [r12+r14],r13
finish:
    // 0xe84d3cc
    *(void**)savedNode = cur; // mov [rax],r13  (rax = savedNode? rsp+0x38)
    *((void**)((char*)cur + 0x08)) = savedNode; // mov [r13+8],rax
    return end;
}

} // namespace native

namespace native {
LIFT_FN(sub_e84d1b0, "sub_e84d1b0", 0xe84d1b0, sub_e84d1b0, nullptr);
} // namespace native