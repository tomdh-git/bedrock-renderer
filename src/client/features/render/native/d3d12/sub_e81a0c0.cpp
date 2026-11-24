// LIFT 0xe81a0c0 size 0x54a 1.26.62.01 sub_e81a0c0
#include "sub_e81a0c0.h"

#include "client/features/render/native/Lift.h"

#include <cstring>

static_assert(sizeof(void*) == 8, "ptr");

namespace {

// Global allocator interface pointer: data slot [0x12ADF800] (VA = imageBase 0x140000000 + 0x12ADF800).
constexpr uintptr_t kGAllocSlot = 0x1412ADF800ULL;
// CFG dispatch thunk: [0xF99FFA0] = sub_eea6040 (`jmp rax`), loader-resolved
// (docs/data/native_boundary.tsv, class vendor). Each `call qword ptr [0xF99FFA0]` in the
// original tail-jumps to the rax preloaded immediately before the call, so the net effect is
// an indirect call through that preloaded vtable entry (here g->vtable[1]).

// g->vtable[1](g, ptr, size, 0, 0, 0): the game's unified allocator.
//   ptr == 0, size > 0  -> allocate(size), result = new block
//   size == 0           -> free(ptr)
// Reached in the original as  mov rax,[rcx]; mov rax,[rax+8]; call qword ptr [0xF99FFA0].
inline void* Alloc(void* g, void* ptr, uint64_t size) {
    void** vt = *reinterpret_cast<void***>(g);
    auto fn = reinterpret_cast<void* (__fastcall*)(void*, void*, uint64_t, uint64_t, uint64_t, uint64_t)>(vt[1]);
    return fn(g, ptr, size, 0, 0, 0);
}

// Walk the intrusive singly-linked list whose head is `head` (next link at node+0x10) and free
// every node through the allocator, reloading the allocator pointer after each free.
//   vecA pass: 0xe81a120..0xe81a16b   vecB pass: 0xe81a300..0xe81a347
inline void FreeList(uint64_t& g, void* head) {
    void* cur = head;
    while (cur) {
        void* nxt = *reinterpret_cast<void**>(reinterpret_cast<char*>(cur) + 0x10);
        if (g) {
            Alloc(reinterpret_cast<void*>(g), cur, 0);          // free(cur)
            g = *reinterpret_cast<uint64_t*>(kGAllocSlot);      // reload allocator
        }
        cur = nxt;
    }
}

// Reset a {first,last,end} buffer triple to a freshly zeroed 0x48-byte (9-slot) region:
//   *last = *first;
//   if (first + 0x48 <= *end) buf = first;                 // capacity already sufficient
//   else { buf = g ? Alloc(g,0,0x48) : 0;                   // allocate 0x48
//          copy [first, *last) -> buf (empty: *last == first here);
//          if (*first) { g = reload; if (g) Alloc(g,*first,0); }   // free old buffer
//          *first = buf; *end = buf + 0x48; }
//   memset(buf, 0, 0x48);
//   *last = *first + 0x48;
//   vecA: 0xe81a174..0xe81a2de   vecB: 0xe81a34b..0xe81a4ae
inline void ResetBuf(void** pFirst, void** pLast, void** pEnd, uint64_t& g) {
    void* first = *pFirst;
    *pLast = first;                                          // clear: last = first
    void* buf;
    if (reinterpret_cast<uintptr_t>(reinterpret_cast<char*>(first) + 0x48) <=
        reinterpret_cast<uintptr_t>(*pEnd)) {
        buf = first;                                         // capacity sufficient, reuse buffer
    } else {
        buf = g ? Alloc(reinterpret_cast<void*>(g), nullptr, 0x48) : nullptr;   // allocate 0x48
        // inlined std::vector copy of 8-byte elements [first, *pLast) -> buf; dead because *pLast==first.
        void* last = *pLast;
        if (first != last) {
            std::memmove(buf, first, reinterpret_cast<char*>(last) - reinterpret_cast<char*>(first));
        }
        void* old = first;
        g = *reinterpret_cast<uint64_t*>(kGAllocSlot);       // reload allocator
        if (old) {
            if (g) Alloc(reinterpret_cast<void*>(g), old, 0); // free old buffer
        }
        *pFirst = buf;
        *pEnd = reinterpret_cast<char*>(buf) + 0x48;
    }
    std::memset(buf, 0, 0x48);                               // zero the 9 slots
    *pLast = reinterpret_cast<char*>(*pFirst) + 0x48;        // last = first + 0x48
}

} // namespace

// Verbatim log of every call instruction in [0xe81a0c0, 0xe81a60a) (rdis dis output, two
// spaces after the address; trailing "; ..." annotations omitted):
#if 0
0xe81a0eb  call qword ptr [0xF99FFA0]
0xe81a141  call qword ptr [0xF99FFA0]
0xe81a1b2  call qword ptr [0xF99FFA0]
0xe81a296  call qword ptr [0xF99FFA0]
0xe81a321  call qword ptr [0xF99FFA0]
0xe81a389  call qword ptr [0xF99FFA0]
0xe81a466  call qword ptr [0xF99FFA0]
0xe81a4e6  call qword ptr [0xF99FFA0]
0xe81a51d  call qword ptr [0xF99FFA0]
#endif
// UNRESOLVED CALL = none: every call target is sub_eea6040, a loader-resolved CFG thunk
// (`jmp rax`, data slot 0xF99FFA0) classified `vendor` in docs/data/native_boundary.tsv; the
// preloaded rax (this object's allocator vtable entry) is the effective callee.

extern "C" void sub_e81a0c0(void* rcx) {
    auto* self = reinterpret_cast<native::d3d12::S81a0c0*>(rcx);   // rsi = this

    // 0xe81a0c0..0xe81a0f8: push regs; rdx=this->vecA_first; walk list calling obj->vtable[2]
    //   on each node->[8] object; advance via node+0x10.
    //   0xe81a0cb  mov rdx,[rcx+0x48]
    //   0xe81a0cf  mov rdi,[rdx]
    //   0xe81a0d5  je 0xE81A16D   (head == 0)
    //   0xe81a0eb  call qword ptr [0xF99FFA0]   (obj->vtable[2], obj = node->[8])
    void* node = *reinterpret_cast<void**>(reinterpret_cast<char*>(&self->vecA_first));
    if (node) {
        do {
            uint64_t obj = *reinterpret_cast<uint64_t*>(reinterpret_cast<char*>(node) + 8);
            uint64_t vt  = *reinterpret_cast<uint64_t*>(obj);
            uint64_t fn  = *reinterpret_cast<uint64_t*>(vt + 0x10);          // vtable[2]
            reinterpret_cast<void (__fastcall*)(uint64_t)>(fn)(obj);
            node = *reinterpret_cast<void**>(reinterpret_cast<char*>(node) + 0x10);
        } while (node);
    }

    // 0xe81a0fa..0xe81a120: g = allocator; free every node of the same list; g reloaded per node.
    //   0xe81a0fa  mov rdx,[rsi+0x48]
    //   0xe81a0fe  mov r8,[rdx]
    //   0xe81a101  mov rcx,[0x12ADF800]
    //   0xe81a10b  je 0xE81A174   (head == 0)
    uint64_t g = *reinterpret_cast<uint64_t*>(kGAllocSlot);
    FreeList(g, *reinterpret_cast<void**>(reinterpret_cast<char*>(&self->vecA_first)));

    // 0xe81a174..0xe81a2de: reset vecA buffer (first/last/end at +0x48/+0x50/+0x58).
    //   0xe81a174  mov [rsi+0x50],rdx
    //   0xe81a180  jbe 0xE81A23A   (capacity sufficient)
    //   0xe81a1b2  call qword ptr [0xF99FFA0]   (allocate 0x48)
    //   0xe81a296  call qword ptr [0xF99FFA0]   (free old buffer)
    ResetBuf(&self->vecA_first, &self->vecA_last, &self->vecA_end, g);
    self->state40 = nullptr;                                 // 0xe81a2e2  mov qword ptr [rsi+0x40],0

    // 0xe81a2d6..0xe81a347: g = allocator; free every node of the vecB list (this+0x68).
    //   0xe81a2d6  mov rdx,[rsi+0x68]
    //   0xe81a2ea  mov r8,[rdx]
    //   0xe81a321  call qword ptr [0xF99FFA0]   (free node)
    FreeList(g, *reinterpret_cast<void**>(reinterpret_cast<char*>(&self->vecB_first)));

    // 0xe81a34b..0xe81a4ae: reset vecB buffer (first/last/end at +0x68/+0x70/+0x78).
    //   0xe81a34b  mov [rsi+0x70],rdx
    //   0xe81a357  jbe 0xE81A40A   (capacity sufficient)
    //   0xe81a389  call qword ptr [0xF99FFA0]   (allocate 0x48)
    //   0xe81a466  call qword ptr [0xF99FFA0]   (free old buffer)
    ResetBuf(&self->vecB_first, &self->vecB_last, &self->vecB_end, g);
    self->state60 = nullptr;                                 // 0xe81a4b2  mov qword ptr [rsi+0x60],0

    // 0xe81a4a2..0xe81a536: count = ((uint16_t*)old_p08)[1]; free old_p08; buf = malloc(count*4+4).
    //   0xe81a4a2  mov rdx,[rsi+8]
    //   0xe81a4ba  movzx ebp,word ptr [rdx+2]
    //   0xe81a4e6  call qword ptr [0xF99FFA0]   (free old index buffer this->p08)
    //   0xe81a51d  call qword ptr [0xF99FFA0]   (allocate count*4+4)
    void* oldP08 = self->p08;
    uint32_t count = *reinterpret_cast<uint16_t*>(reinterpret_cast<char*>(oldP08) + 2);
    void* buf = nullptr;
    if (g) {
        Alloc(reinterpret_cast<void*>(g), oldP08, 0);        // free old index buffer
        g = *reinterpret_cast<uint64_t*>(kGAllocSlot);       // reload allocator
        if (g) {
            buf = Alloc(reinterpret_cast<void*>(g), nullptr, static_cast<uint64_t>(count) * 4 + 4);
        }
    }
    // 0xe81a52a..0xe81a5fd: header [0]=0, [1]=count; identity map [2+i]=i for i in [0,count);
    // store this->p08 = buf.  The original fills the body with SIMD (movdqa from the five
    // .rdata constants 0xF441430=[0..7], 0xF08ED30=[8x8], 0xF441630=[16x8], 0xF441640=[0,1,2,3],
    // 0xF441650=[4,4,4,4]) plus a scalar tail; both produce the same identity sequence.
    //   0xe81a52a  mov [rdi+2],bp
    //   0xe81a52e  mov word ptr [rdi],0
    //   0xe81a536  je 0xE81A5FD   (count == 0)
    //   0xe81a551..0xe81a5e5  SIMD + 4-wide + scalar identity fill
    //   0xe81a5fd  mov [rsi+8],rdi
    *reinterpret_cast<uint16_t*>(reinterpret_cast<char*>(buf) + 0) = 0;
    *reinterpret_cast<uint16_t*>(reinterpret_cast<char*>(buf) + 2) = static_cast<uint16_t>(count);
    uint16_t* body = reinterpret_cast<uint16_t*>(reinterpret_cast<char*>(buf) + 4);
    uint32_t i = 0;
    for (uint16_t* p = body; i < count; ++p, ++i) {
        *p = static_cast<uint16_t>(i);
    }
    self->p08 = buf;
    // 0xe81a601..0xe81a609: add rsp,0x38; pop rbx/rbp/rdi/rsi; ret
}

namespace native::d3d12 {
LIFT_FN(sub_e81a0c0, "sub_e81a0c0", 0xe81a0c0, sub_e81a0c0, nullptr);
} // namespace native::d3d12