// LIFT 0xbc79a60 size 0x46f 1.26.62.01 sub_bc79a60
#include "client/features/render/native/bgfx/sub_bc79a60.h"
#include "client/features/render/native/Lift.h"

#include <cstring>

namespace native {

namespace {
const char kSlabReallocFile[] = "NOFILE";   // slot [0xF7CC762] "NOFILE" [V]
}

// Calls out of the lifted function (same calls, same order, as the original):
//   0xbc79b09  call qword ptr [0xF99FFA0]   realloc(alloc, nullptr, 0x18, 8, "NOFILE", 0)   header block
//   0xbc79b90  call qword ptr [0xF99FFA0]   realloc(alloc, nullptr, 0x4008, 8, "NOFILE", 0)  chain block
//   0xbc79ba4  call 0xEEC6ED0               memset(newBlock, 0, 0x4008)
// The [0xF99FFA0] slot holds sub_eea6040, a `jmp rax` thunk (vendor, loader-resolved;
// docs/data/native_boundary.tsv line 506). rax holds allocator->vtable[1] = realloc, loaded
// just before each call (0xbc79ad9  mov rcx,[0x12ADF800]; 0xbc79ae0  mov rax,[rcx];
// 0xbc79ae3  mov rax,[rax+8]; identical at 0xbc79b60-0xbc79b6a). The lifted code reads vtable
// slot 1 at call time via slabRealloc(slabAllocator()) and invokes it directly with the same
// arguments — exactly what the thunk tail-calls [V; hard rule 69]. memset/memcpy are CRT
// intrinsics [V: 0xbc79ba4  call 0xEEC6ED0; boundary.tsv line 507 class crt].

extern "C" std::uint64_t sub_bc79a60(Slab* slab) {
    // 0xbc79a60..0xbc79a6c
    //   0xbc79a60  push r15
    //   0xbc79a62  push r14
    //   0xbc79a64  push r13
    //   0xbc79a66  push r12
    //   0xbc79a68  push rsi
    //   0xbc79a69  push rdi
    //   0xbc79a6a  push rbp
    //   0xbc79a6b  push rbx
    //   0xbc79a6c  sub rsp,0x38
    // Register map: rsi = slab for the whole body (0xbc79a70  mov rsi,rcx).

    // All temporaries are declared up front so the gotos mirroring the original labels
    // never jump over an initialization.
    std::uint64_t count = 0;          // r14d/ebx: a0+0x4018 (count)
    std::uint64_t cursor = 0;         // rcx: a0+0x4008 (cursor)
    std::uint64_t index = 0;          // r15: cursor >> 2
    std::uint64_t rdx = 0;            // rdx scratch (index + 1, later candidate limit)
    std::uint64_t r12 = 0;            // r12 scratch (bytes still needed)
    void* header = nullptr;           // rax: a0+0x4000 (header block pointer)
    std::uint64_t totalBytes = 0;     // rdx: [header+0x10]
    void** link = nullptr;            // r13: link field address
    void* tail = nullptr;             // rcx: [header+8]
    void* block = nullptr;            // block walk base
    void* newBlock = nullptr;         // rdi: freshly allocated block
    std::uint64_t addr = 0;           // rax: result slot address
    std::uint64_t walkOff = 0;        // rcx/r14d scratch (cursor - 0x8000 etc.)
    std::uint32_t hops = 0;           // r8d/r9d: hop count
    AllocatorI* alloc = nullptr;
    ReallocFn reallocFn = nullptr;
    std::uint64_t r8 = 0;             // r8d scratch
    std::uint64_t next = 0;           // eax: free-list next value / return candidate
    std::uint64_t addr2 = 0;          // second result address (d28 path)
    void* block2 = nullptr;           // second walk base
    std::uint32_t hops2 = 0;
    std::uint64_t nextCursor = 0;

    // 0xbc79a70  mov rsi,rcx                       (slab already in rsi via the ABI)
    // 0xbc79a73  movzx r14d,word ptr [rcx+0x4018]  R a0+0x4018   (slab->count)
    count = slab->count;
    // 0xbc79a7b  mov ebx,r14d
    // 0xbc79a7e  lea eax,[r14+1]
    // 0xbc79a82  mov [rcx+0x4018],ax               W a0+0x4018   (slab->count = count + 1)
    slab->count = static_cast<std::uint16_t>(count + 1u);
    // 0xbc79a89  mov rcx,[rcx+0x4008]              R a0+0x4008   (slab->cursor)
    cursor = slab->cursor;
    // 0xbc79a90  mov r15,rcx
    // 0xbc79a93  shr r15,2
    index = cursor >> 2;
    // 0xbc79a97  cmp r15,r14
    // 0xbc79a9a  ja 0xBC79D28
    if (index > count) goto loc_bc79d28;
    // 0xbc79aa0  lea rdx,[r15+1]
    rdx = index + 1;
    // 0xbc79aa4  cmp rcx,0x4000
    // 0xbc79aab  jb 0xBC79C20
    if (cursor < 0x4000ull) goto loc_bc79c20;
    // 0xbc79ab1  mov rax,[rsi+0x4010]              R a0+0x4010   (slab->limit)
    // 0xbc79ab8  shr rax,2
    // 0xbc79abc  cmp r15,rax
    // 0xbc79abf  jb 0xBC79C20
    if (index < (slab->limit >> 2)) goto loc_bc79c20;

    // 0xbc79ac5  lea r12,[rdx*4-0x4000]
    r12 = rdx * 4 - 0x4000ull;
    // 0xbc79acd  mov rax,[rsi+0x4000]              R a0+0x4000   (slab->blockHead)
    header = slab->blockHead;
    // 0xbc79ad4  test rax,rax
    // 0xbc79ad7  jne short 0xBC79B24
    if (header != nullptr) goto loc_bc79b24;
    // 0xbc79ad9  mov rcx,[0x12ADF800]              [data_12adf800]
    // 0xbc79ae0  mov rax,[rcx]
    // 0xbc79ae3  mov rax,[rax+8]
    alloc = slabAllocator();
    reallocFn = slabRealloc(alloc);
    // 0xbc79ae7  lea rdx,[0xF7CC762]              [data_f7cc762] "NOFILE"
    // 0xbc79aee  mov [rsp+0x20],rdx
    // 0xbc79af3  mov dword ptr [rsp+0x28],0
    // 0xbc79afb  mov r8d,0x18
    // 0xbc79b01  mov r9d,8
    // 0xbc79b07  xor edx,edx
    // 0xbc79b09  call qword ptr [0xF99FFA0]        [data_f99ffa0] = sub_eea6040  realloc(alloc, nullptr, 0x18, 8, "NOFILE", 0)
    block = reallocFn(alloc, nullptr, 0x18, 8, kSlabReallocFile, 0);
    // 0xbc79b0f  xorps xmm0,xmm0
    // 0xbc79b12  movups [rax],xmm0
    std::memset(block, 0, 16);
    // 0xbc79b15  mov qword ptr [rax+0x10],0
    *reinterpret_cast<std::uint64_t*>(static_cast<char*>(block) + 0x10) = 0;
    // 0xbc79b1d  mov [rsi+0x4000],rax              W a0+0x4000   (slab->blockHead = block)
    slab->blockHead = block;
    goto loc_bc79b24;

loc_bc79b24:
    // 0xbc79b24  mov rdx,[rax+0x10]                [rax = header]
    totalBytes = *reinterpret_cast<std::uint64_t*>(static_cast<char*>(header) + 0x10);
    // 0xbc79b28  sub r12,rdx
    r12 -= totalBytes;
    // 0xbc79b2b  jbe 0xBC79C0E
    if (r12 <= 0) goto loc_bc79c0e;
    // 0xbc79b31  mov rcx,[rax+8]
    tail = *reinterpret_cast<void**>(static_cast<char*>(header) + 8);
    // 0xbc79b35  add rax,8
    // 0xbc79b39  lea r13,[rcx+0x4000]
    // 0xbc79b40  test rcx,rcx
    // 0xbc79b43  cmove r13,rax                      if (tail == 0) link = header + 8 else link = tail + 0x4000
    link = tail != nullptr
        ? reinterpret_cast<void**>(static_cast<char*>(tail) + 0x4000)
        : reinterpret_cast<void**>(static_cast<char*>(header) + 8);
    // 0xbc79b47  mov ebp,0x4000
    // 0xbc79b4c  cmp qword ptr [r13],0
    // 0xbc79b51  jne 0xBC79BE0
    if (*link != nullptr) goto loc_bc79be0;
    // 0xbc79b57  nop [rax+rax]   (fall through)
    goto loc_bc79b60;

loc_bc79be0:
    // 0xbc79be0  cmp r12,0x4001
    // 0xbc79be7  jb short 0xBC79C03
    if (r12 < 0x4001ull) goto loc_bc79c03;
    // 0xbc79be9  mov r13,[r13]
    // 0xbc79bed  add r13,rbp
    link = reinterpret_cast<void**>(static_cast<char*>(*link) + 0x4000);
    // 0xbc79bf0  add r12,0xFFFFFFFFFFFFC000
    r12 -= 0x4000ull;
    // 0xbc79bf7  cmp qword ptr [r13],0
    // 0xbc79bfc  jne short 0xBC79BE0
    if (*link != nullptr) goto loc_bc79be0;
    // 0xbc79bfe  jmp 0xBC79B60
    goto loc_bc79b60;

loc_bc79b60:
    // 0xbc79b60  mov rcx,[0x12ADF800]
    alloc = slabAllocator();
    // 0xbc79b67  mov rax,[rcx]
    // 0xbc79b6a  mov rax,[rax+8]
    reallocFn = slabRealloc(alloc);
    // 0xbc79b6e  lea rdx,[0xF7CC762]              "NOFILE"
    // 0xbc79b75  mov [rsp+0x20],rdx
    // 0xbc79b7a  mov dword ptr [rsp+0x28],0
    // 0xbc79b82  mov r8d,0x4008
    // 0xbc79b88  mov r9d,8
    // 0xbc79b8e  xor edx,edx
    // 0xbc79b90  call qword ptr [0xF99FFA0]        realloc(alloc, nullptr, 0x4008, 8, "NOFILE", 0)
    newBlock = reallocFn(alloc, nullptr, 0x4008, 8, kSlabReallocFile, 0);
    // 0xbc79b96  mov rdi,rax
    // 0xbc79b99  mov r8d,0x4008
    // 0xbc79b9f  mov rcx,rax
    // 0xbc79ba2  xor edx,edx
    // 0xbc79ba4  call 0xEEC6ED0              memset(newBlock, 0, 0x4008)
    std::memset(newBlock, 0, 0x4008);
    // 0xbc79ba9  mov [r13],rdi
    *link = newBlock;
    // 0xbc79bad  mov rax,[rsi+0x4000]
    header = slab->blockHead;
    // 0xbc79bb4  mov [rax+8],rdi                   W *(a0+0x4000)+0x8   (header tail = newBlock)
    *reinterpret_cast<void**>(static_cast<char*>(header) + 8) = newBlock;
    // 0xbc79bb8  mov rax,[rsi+0x4000]
    header = slab->blockHead;
    // 0xbc79bbf  add qword ptr [rax+0x10],0x4000   W *(a0+0x4000)+0x10   (header totalBytes += 0x4000)
    *reinterpret_cast<std::uint64_t*>(static_cast<char*>(header) + 0x10) += 0x4000ull;
    // 0xbc79bc7  mov rax,[rsi+0x4000]
    header = slab->blockHead;
    // 0xbc79bce  cmp qword ptr [rax],0
    // 0xbc79bd2  jne short 0xBC79BE0
    if (*reinterpret_cast<void**>(header) != nullptr) goto loc_bc79be0;
    // 0xbc79bd4  mov rcx,[r13]
    // 0xbc79bd8  mov [rax],rcx                     W *(a0+0x4000)+0x0   (header head = *link = newBlock)
    *reinterpret_cast<void**>(header) = *link;
    // 0xbc79bdb  nop [rax+rax]   (fall through to 0xBC79BE0)
    goto loc_bc79be0;

loc_bc79c03:
    // 0xbc79c03  mov rax,[rsi+0x4000]
    header = slab->blockHead;
    // 0xbc79c0a  mov rdx,[rax+0x10]
    totalBytes = *reinterpret_cast<std::uint64_t*>(static_cast<char*>(header) + 0x10);

loc_bc79c0e:
    // 0xbc79c0e  shr rdx,2
    // 0xbc79c12  add rdx,0x1000
    totalBytes = (totalBytes >> 2) + 0x1000ull;
    // 0xbc79c19  mov rcx,[rsi+0x4008]
    cursor = slab->cursor;

loc_bc79c20:
    // 0xbc79c20  shl rdx,2
    totalBytes = totalBytes << 2;
    // 0xbc79c24  mov rax,[rsi+0x4010]
    // 0xbc79c2b  cmp rax,rdx
    // 0xbc79c2e  cmova rdx,rax                    if (limit > totalBytes) totalBytes = limit  (unsigned)
    if (slab->limit > totalBytes) totalBytes = slab->limit;
    // 0xbc79c32  mov [rsi+0x4010],rdx
    slab->limit = totalBytes;
    // 0xbc79c39  mov rax,rcx
    // 0xbc79c3c  and rax,0xFFFFFFFFFFFFFFFC
    addr = cursor & 0xFFFFFFFFFFFFFFFCull;
    // 0xbc79c40  cmp rcx,0x3FFF
    // 0xbc79c47  ja 0xBC79C51
    if (cursor > 0x3FFFull) goto loc_bc79c51;
    // 0xbc79c49  add rax,rsi
    addr = reinterpret_cast<std::uint64_t>(slab) + addr;
    // 0xbc79c4c  jmp 0xBC79D09
    goto loc_bc79d09;

loc_bc79c51:
    // 0xbc79c51  add rax,0xFFFFFFFFFFFFC000
    addr -= 0x4000ull;
    // 0xbc79c57  mov rdx,[rsi+0x4000]
    // 0xbc79c5e  mov rdx,[rdx]                    block = headBlock = [header+0]
    block = *reinterpret_cast<void**>(slab->blockHead);
    // 0xbc79c61  cmp rax,0x4000
    // 0xbc79c67  jb 0xBC79D06
    if (addr < 0x4000ull) goto loc_bc79d06;
    // 0xbc79c6d  add rcx,0xFFFFFFFFFFFF8000
    walkOff = cursor - 0x8000ull;
    // 0xbc79c74  mov r8d,ecx
    // 0xbc79c77  not r8d
    // 0xbc79c7a  test r8d,0x1C000
    // 0xbc79c81  je 0xBC79CB2
    if ((~static_cast<std::uint32_t>(walkOff) & 0x1C000ull) != 0) {
        // 0xbc79c83  mov r8d,ecx
        // 0xbc79c86  shr r8d,0xE
        // 0xbc79c8a  inc r8d
        // 0xbc79c8d  and r8d,7
        hops = (static_cast<std::uint32_t>(walkOff) >> 14) + 1;
        hops &= 7u;
        // 0xbc79c91  nop [rax+rax]
        // 0xbc79ca0  add rax,0xFFFFFFFFFFFFC000
        // 0xbc79ca6  mov rdx,[rdx+0x4000]
        // 0xbc79cad  dec r8
        // 0xbc79cb0  jne short 0xBC79CA0
        do {
            addr -= 0x4000ull;
            block = *reinterpret_cast<void**>(static_cast<char*>(block) + 0x4000);
            --hops;
        } while (hops != 0);
    }
    // 0xbc79cb2  cmp rcx,0x1C000
    // 0xbc79cb9  jb 0xBC79D06
    if (walkOff < 0x1C000ull) goto loc_bc79d06;
    // 0xbc79cbb  nop [rax+rax]   (fall through)
    goto loc_bc79cc0;

loc_bc79cc0:
    do {
        // 0xbc79cc0  mov rcx,[rdx+0x4000]
        // 0xbc79cc7  mov rcx,[rcx+0x4000]
        // 0xbc79cce  mov rcx,[rcx+0x4000]
        // 0xbc79cd5  mov rcx,[rcx+0x4000]
        // 0xbc79cdc  mov rcx,[rcx+0x4000]
        // 0xbc79ce3  mov rcx,[rcx+0x4000]
        // 0xbc79cea  mov rcx,[rdx+0x4000]
        block = *reinterpret_cast<void**>(static_cast<char*>(block) + 0x4000);
        block = *reinterpret_cast<void**>(static_cast<char*>(block) + 0x4000);
        block = *reinterpret_cast<void**>(static_cast<char*>(block) + 0x4000);
        block = *reinterpret_cast<void**>(static_cast<char*>(block) + 0x4000);
        block = *reinterpret_cast<void**>(static_cast<char*>(block) + 0x4000);
        block = *reinterpret_cast<void**>(static_cast<char*>(block) + 0x4000);
        block = *reinterpret_cast<void**>(static_cast<char*>(block) + 0x4000);
        block = *reinterpret_cast<void**>(static_cast<char*>(block) + 0x4000);
        // 0xbc79cf1  add rax,0xFFFFFFFFFFFE0000
        addr -= 0x20000ull;
        // 0xbc79cf7  mov rdx,[rcx+0x4000]
        block = *reinterpret_cast<void**>(static_cast<char*>(block) + 0x4000);
        // 0xbc79cfe  cmp rax,0x3FFF
        // 0xbc79d04  ja 0xBC79CC0
    } while (addr > 0x3FFFull);
    goto loc_bc79d06;

loc_bc79d06:
    // 0xbc79d06  add rax,rdx
    addr += reinterpret_cast<std::uint64_t>(block);

loc_bc79d09:
    // 0xbc79d09  mov [rax],r15w
    // 0xbc79d0d  mov [rax+2],r15w
    *reinterpret_cast<std::uint16_t*>(addr) = static_cast<std::uint16_t>(index);
    *reinterpret_cast<std::uint16_t*>(addr + 2) = static_cast<std::uint16_t>(index);
    // 0xbc79d12  mov rax,[rsi+0x4008]
    // 0xbc79d19  and rax,0xFFFFFFFFFFFFFFFC
    // 0xbc79d1d  add rax,4
    // 0xbc79d21  mov [rsi+0x4008],rax
    nextCursor = (cursor & 0xFFFFFFFFFFFFFFFCull) + 4;
    slab->cursor = nextCursor;
    return nextCursor;

loc_bc79d28:
    // 0xbc79d28  movzx eax,bx                     next = count (return candidate)
    // 0xbc79d2b  shl r14d,2
    next = count;
    r8 = count * 4;
    // 0xbc79d2f  cmp eax,0xFFF
    // 0xbc79d34  ja 0xBC79D41
    if (count > 0xFFF) goto loc_bc79d41;
    // 0xbc79d36  add r14,rsi
    // 0xbc79d39  mov rax,r14                      rax = slab + count*4
    addr = reinterpret_cast<std::uint64_t>(slab) + r8;
    // 0xbc79d3c  jmp 0xBC79DE9
    goto loc_bc79de9;

loc_bc79d41:
    // 0xbc79d41  lea rax,[r14-0x4000]             rax = count*4 - 0x4000
    addr = count * 4 - 0x4000ull;
    // 0xbc79d48  mov rcx,[rsi+0x4000]
    // 0xbc79d4f  mov rcx,[rcx]                    block2 = headBlock = [header+0]
    block2 = *reinterpret_cast<void**>(slab->blockHead);
    // 0xbc79d52  cmp rax,0x4000
    // 0xbc79d58  jb 0xBC79DE6
    if (addr < 0x4000ull) goto loc_bc79de6;
    // 0xbc79d5e  add r14,0xFFFFFFFFFFFF8000       walkOff = (uint32)(count*4 - 0x8000)
    walkOff = static_cast<std::uint64_t>(static_cast<std::uint32_t>(count * 4 - 0x8000ull));
    // 0xbc79d65  mov edx,r14d
    // 0xbc79d68  not edx
    // 0xbc79d6a  test edx,0x1C000
    // 0xbc79d70  je 0xBC79D92
    if ((~static_cast<std::uint32_t>(walkOff) & 0x1C000ull) != 0) {
        // 0xbc79d72  mov edx,r14d
        // 0xbc79d75  shr edx,0xE
        // 0xbc79d78  inc edx
        // 0xbc79d7a  and edx,7
        hops2 = (static_cast<std::uint32_t>(walkOff) >> 14) + 1;
        hops2 &= 7u;
        // 0xbc79d7d  nop [rax]
        // 0xbc79d80  add rax,0xFFFFFFFFFFFFC000
        // 0xbc79d86  mov rcx,[rcx+0x4000]
        // 0xbc79d8d  dec rdx
        // 0xbc79d90  jne short 0xBC79D80
        do {
            addr -= 0x4000ull;
            block2 = *reinterpret_cast<void**>(static_cast<char*>(block2) + 0x4000);
            --hops2;
        } while (hops2 != 0);
    }
    // 0xbc79d92  cmp r14d,0x1C000
    // 0xbc79d99  jb 0xBC79DE6
    if (walkOff < 0x1C000ull) goto loc_bc79de6;
    // 0xbc79d9b  nop [rax+rax]   (fall through)
    goto loc_bc79da0;

loc_bc79da0:
    do {
        // 0xbc79da0  mov rcx,[rcx+0x4000]  x8
        block2 = *reinterpret_cast<void**>(static_cast<char*>(block2) + 0x4000);
        block2 = *reinterpret_cast<void**>(static_cast<char*>(block2) + 0x4000);
        block2 = *reinterpret_cast<void**>(static_cast<char*>(block2) + 0x4000);
        block2 = *reinterpret_cast<void**>(static_cast<char*>(block2) + 0x4000);
        block2 = *reinterpret_cast<void**>(static_cast<char*>(block2) + 0x4000);
        block2 = *reinterpret_cast<void**>(static_cast<char*>(block2) + 0x4000);
        block2 = *reinterpret_cast<void**>(static_cast<char*>(block2) + 0x4000);
        block2 = *reinterpret_cast<void**>(static_cast<char*>(block2) + 0x4000);
        // 0xbc79dd1  add rax,0xFFFFFFFFFFFE0000
        addr -= 0x20000ull;
        // 0xbc79dd7  mov rcx,[rcx+0x4000]
        block2 = *reinterpret_cast<void**>(static_cast<char*>(block2) + 0x4000);
        // 0xbc79dde  cmp rax,0x3FFF
        // 0xbc79de4  ja 0xBC79DA0
    } while (addr > 0x3FFFull);

loc_bc79de6:
    // 0xbc79de6  add rax,rcx
    addr += reinterpret_cast<std::uint64_t>(block2);

loc_bc79de9:
    // 0xbc79de9  movzx eax,word ptr [rax+2]     next = u16 at [addr + 2]
    next = *reinterpret_cast<std::uint16_t*>(addr + 2);
    // 0xbc79ded  lea r8d,[rax*4]
    r8 = next * 4;
    // 0xbc79df5  cmp eax,0xFFF
    // 0xbc79dfa  ja 0xBC79E07
    if (next > 0xFFF) goto loc_bc79e07;
    // 0xbc79dfc  add rsi,r8                     rsi = slab + next*4
    // 0xbc79dff  mov rcx,rsi
    addr2 = reinterpret_cast<std::uint64_t>(slab) + r8;
    // 0xbc79e02  jmp 0xBC79EBB
    goto loc_bc79ebb;

loc_bc79e07:
    // 0xbc79e07  lea rcx,[r8-0x4000]
    walkOff = r8 - 0x4000ull;
    // 0xbc79e0e  mov rdx,[rsi+0x4000]
    // 0xbc79e15  mov rdx,[rdx]                  block2 = headBlock = [header+0]
    block2 = *reinterpret_cast<void**>(slab->blockHead);
    // 0xbc79e18  cmp rcx,0x4000
    // 0xbc79e1f  jb 0xBC79EB8
    if (walkOff < 0x4000ull) goto loc_bc79eb8;
    // 0xbc79e25  add r8,0xFFFFFFFFFFFF8000
    r8 -= 0x8000ull;
    // 0xbc79e2c  mov r9d,r8d
    // 0xbc79e2f  not r9d
    // 0xbc79e32  test r9d,0x1C000
    // 0xbc79e39  je 0xBC79E63
    if ((~static_cast<std::uint32_t>(r8) & 0x1C000ull) != 0) {
        // 0xbc79e3b  mov r9d,r8d
        // 0xbc79e3e  shr r9d,0xE
        // 0xbc79e42  inc r9d
        // 0xbc79e45  and r9d,7
        hops2 = (static_cast<std::uint32_t>(r8) >> 14) + 1;
        hops2 &= 7u;
        // 0xbc79e49  nop [rax]
        // 0xbc79e50  add rcx,0xFFFFFFFFFFFFC000
        // 0xbc79e57  mov rdx,[rdx+0x4000]
        // 0xbc79e5e  dec r9
        // 0xbc79e61  jne short 0xBC79E50
        do {
            walkOff -= 0x4000ull;
            block2 = *reinterpret_cast<void**>(static_cast<char*>(block2) + 0x4000);
            --hops2;
        } while (hops2 != 0);
    }
    // 0xbc79e63  cmp r8d,0x1C000
    // 0xbc79e6a  jb 0xBC79EB8
    if (r8 < 0x1C000ull) goto loc_bc79eb8;
    // 0xbc79e6c  nop [rax]   (fall through)
    goto loc_bc79e70;

loc_bc79e70:
    do {
        // 0xbc79e70  mov rdx,[rdx+0x4000]  x8
        block2 = *reinterpret_cast<void**>(static_cast<char*>(block2) + 0x4000);
        block2 = *reinterpret_cast<void**>(static_cast<char*>(block2) + 0x4000);
        block2 = *reinterpret_cast<void**>(static_cast<char*>(block2) + 0x4000);
        block2 = *reinterpret_cast<void**>(static_cast<char*>(block2) + 0x4000);
        block2 = *reinterpret_cast<void**>(static_cast<char*>(block2) + 0x4000);
        block2 = *reinterpret_cast<void**>(static_cast<char*>(block2) + 0x4000);
        block2 = *reinterpret_cast<void**>(static_cast<char*>(block2) + 0x4000);
        block2 = *reinterpret_cast<void**>(static_cast<char*>(block2) + 0x4000);
        // 0xbc79ea1  add rcx,0xFFFFFFFFFFFE0000
        walkOff -= 0x20000ull;
        // 0xbc79ea8  mov rdx,[rdx+0x4000]
        block2 = *reinterpret_cast<void**>(static_cast<char*>(block2) + 0x4000);
        // 0xbc79eaf  cmp rcx,0x3FFF
        // 0xbc79eb6  ja 0xBC79E70
    } while (walkOff > 0x3FFFull);
    goto loc_bc79eb8;

loc_bc79eb8:
    // 0xbc79eb8  add rcx,rdx
    addr2 = walkOff + reinterpret_cast<std::uint64_t>(block2);

loc_bc79ebb:
    // 0xbc79ebb  mov [rcx],bx                 *addr2 = (u16)count
    *reinterpret_cast<std::uint16_t*>(addr2) = static_cast<std::uint16_t>(count);
    // 0xbc79ebe  add rsp,0x38
    //   0xbc79ec2  pop rbx
    //   0xbc79ec3  pop rbp
    //   0xbc79ec4  pop rdi
    //   0xbc79ec5  pop rsi
    //   0xbc79ec6  pop r12
    //   0xbc79ec8  pop r13
    //   0xbc79eca  pop r14
    //   0xbc79ecc  pop r15
    //   0xbc79ece  ret
    return next;
}

native::Footprint sub_bc79a60Footprint(Slab* a) {
    native::Footprint fp;
    fp.push_back({a, sizeof(Slab)});
    // Block header/chain writes (blockHead field, header+0/8/0x10, block+0x4000 links,
    // block payload slots) target allocator-managed memory outside the Slab object; those
    // blocks are freshly zeroed by the allocator before use, so they carry no pre-state to
    // snapshot (same assumption as freshly allocated memcpy targets).
    return fp;
}

LIFT_FN(sub_bc79a60, "native::sub_bc79a60", 0xbc79a60, sub_bc79a60, sub_bc79a60Footprint);

} // namespace native
