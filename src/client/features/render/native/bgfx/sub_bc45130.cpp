// LIFT 0xbc45130 size 0x161 1.26.62.01 sub_bc45130
#include "client/features/render/native/bgfx/sub_bc45130.h"

#include <cstdlib>
#include <cstring>

// Verbatim call instructions from the disassembly of [0xbc45130, 0xbc45291)
// (two spaces after each address, exactly as printed by rdis):
// `0xbc451ec  call qword ptr [0xF99FFA0]`   ; [data_f99ffa0] = sub_eea6040, imported CRT allocator ("malloc")
// `0xbc45214  call qword ptr [0xF99FFA0]`   ; [data_f99ffa0] = sub_eea6040, imported CRT allocator ("malloc")
// `0xbc4523f  call 0xEEC6EC0`               ; -> sub_eec6ec0, memcpy
// `0xbc45271  call 0x9BC830`                ; -> sub_9bc830, noreturn heap-failure handler
// `0xbc4527c  call 0x9BC830`                ; -> sub_9bc830, noreturn heap-failure handler
// `0xbc4528a  call 0x75720`                 ; -> sub_75720, noreturn invalid-parameter handler
// UNRESOLVED CALL = none. (0x75720 and 0x9BC830 are listed in docs/data/native_boundary.tsv (stl / alloc);
// sub_eea6040 via IAT slot [0xF99FFA0] and sub_eec6ec0 are CRT/library intrinsics, per the sub_bc44b40 precedent.)

extern "C" __declspec(noreturn) void invalid_parameter(void* object);   // 0x75720: invalid-parameter-like handler, noreturn
extern "C" __declspec(noreturn) void heap_failure(void* object);        // 0x9BC830: allocator out-of-memory handler, noreturn

namespace native::bgfx {

FbSsoString* sub_bc45130(FbSsoString* dst, const FbSsoString* src) {
    // 0xbc45130..0xbc4513a — prologue: push rbp, r15, r14, r12, rsi, rdi, rbx; sub rsp, 0x30; lea rbp,[rsp+0x30]
    // 0xbc45143  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE (EH cookie slot, never read by this function)
    dst->mValid = 0;                                                               // 0xbc4514b  mov byte ptr [rcx+0x40],0
    if (src->mValid != 1u) {                                                       // 0xbc4514f  cmp byte ptr [rdx+0x40],1 / 0xbc45153  jne 0xBC4525C
        return dst;                                                                // 0xbc4525c..0xbc4526d epilogue: mov rax,rcx; add rsp,0x30; pop...; ret
    }
    dst->mField10 = src->mField10;                                               // 0xbc45159  mov rax,[rdx+0x10] / 0xbc4515d  mov [rcx+0x10],rax
    std::memcpy(&dst->mHeader, &src->mHeader, 16);                               // 0xbc45161  movups xmm0,[rdx] / 0xbc45164  movups [rcx],xmm0
    // 0xbc4516a  movups [rcx+0x18],xmm0 / 0xbc4516e  movups [rcx+0x28],xmm0 — zero dst+0x18..dst+0x37
    dst->mData = nullptr;
    dst->mSize = 0;
    dst->mCapacity = 0;
    uint64_t size = src->mSize;                                                  // 0xbc45172  mov rsi,[rdx+0x28]
    const uint8_t* srcData;
    if (src->mCapacity < 0x10) {                                                 // 0xbc45176  cmp qword ptr [rdx+0x30],0x10 / 0xbc4517b  jb short 0xBC45183
        srcData = reinterpret_cast<const uint8_t*>(&src->mData);                 // 0xbc45183  lea rdi,[rdx+0x18]
    } else {                                                                     // 0xbc4517d  mov rdi,[rdx+0x18] / 0xbc45181  jmp short 0xBC45187
        srcData = src->mData;
    }
    if (static_cast<int64_t>(size) < 0) {                                        // 0xbc45187  test rsi,rsi / 0xbc4518a  js 0xBC45286
        invalid_parameter(dst);                                                  // 0xbc4528a  call 0x75720 (noreturn; nop+int3 padding follows)
    }
    if (size > 0xF) {                                                            // 0xbc45190  cmp rsi,0xF / 0xbc45194  ja short 0xBC451B1 -> heap path
        // 0xbc451b1..0xbc451f2 — heap path: save dst/src, allocator setup, size class, malloc
        //   0xbc451b1  mov [rbp-0x10],rcx / 0xbc451b5  mov r15,rdx  (save dst and src)
        //   0xbc451cd  mov rcx,[0x1233E1A8] / 0xbc451d4  mov rax,[rcx] / 0xbc451d7  mov rax,[rax+8]
        //                        (allocator handle plus vtable-slot read; the loaded value is unused —
        //                        the call goes through IAT slot [0xF99FFA0] = sub_eea6040)
        //   0xbc451b8  mov rdx,rsi / 0xbc451bb  or rdx,0xF / 0xbc451bf  cmp rdx,0x17 / 0xbc451c3  mov r12d,0x16 / 0xbc451c9  cmovae r12,rdx
        const uint64_t rdx = size | 0xFULL;
        uint64_t capacity = 0x16ULL;
        if (rdx >= 0x17ULL) capacity = rdx;
        //   0xbc451db  cmp rdx,0xFFF / 0xbc451e2  jb short 0xBC4520C (small path: capacity + 1)
        //              else large path: capacity + 0x28
        const uint64_t allocSize = (rdx < 0xFFFULL) ? capacity + 1 : capacity + 0x28ULL;
        void* allocated = std::malloc(allocSize);                                // 0xbc451ec / 0xbc45214  call qword ptr [0xF99FFA0] (rcx = allocator handle, rdx = allocSize)
        if (allocated == nullptr) {                                              // 0xbc451f6  test rax,rax / 0xbc451f9 je 0xBC4526E / 0xbc4521e test / 0xbc45221 je 0xBC45279
            heap_failure(dst);                                                   // 0xbc45271 / 0xbc4527c  call 0x9BC830 (noreturn)
        }
        // 0xbc451fb..0xbc4520a — align block and store the base pointer cookie at aligned-8
        uintptr_t aligned = (reinterpret_cast<uintptr_t>(allocated) + 0x27ULL) & ~0x1FULL;
        *reinterpret_cast<void**>(aligned - 8) = allocated;                      // 0xbc45206  mov [rbx-8],rax
        // 0xbc45223..0xbc45247 — join: restore dst/src, store data pointer, size, capacity; size++
        dst->mData = reinterpret_cast<uint8_t*>(aligned);                        // 0xbc45227  mov [r14+0x18],rbx
        dst->mSize = size;                                                       // 0xbc4522b  mov [r14+0x28],rsi
        dst->mCapacity = capacity;                                               // 0xbc4522f  mov [r14+0x30],r12
        size++;                                                                  // 0xbc45233  inc rsi
        std::memcpy(dst->mData, srcData, size);                                  // 0xbc4523f  call 0xEEC6EC0 (rcx = dst->mData, rdx = srcData, r8 = size + 1)
        // 0xbc4524a..0xbc45258 — tail (shared with the SSO path)
    } else {
        // 0xbc45196..0xbc451ac — SSO path (size <= 0xF): size, capacity, 16-byte inline copy to dst+0x18
        dst->mSize = size;                                                       // 0xbc4519a  mov [rcx+0x28],rsi
        dst->mCapacity = 0xF;                                                    // 0xbc4519e  mov qword ptr [rcx+0x30],0xF
        std::memcpy(&dst->mData, srcData, 16);                                   // 0xbc451a6  movups xmm0,[rdi] / 0xbc451a9  movups [rax],xmm0
        // 0xbc451ac  jmp 0xBC4524A  (join at tail)
    }
    dst->mField3C = src->mField3C;                                               // 0xbc4524a  movzx eax,word ptr [rdx+0x3C] / 0xbc4524e  mov [rcx+0x3C],ax
    dst->mField38 = src->mField38;                                               // 0xbc45252  mov eax,[rdx+0x38] / 0xbc45255  mov [rcx+0x38],eax
    dst->mValid = 1u;                                                            // 0xbc45258  mov byte ptr [rcx+0x40],1
    // 0xbc4525c..0xbc4526d — epilogue: mov rax,rcx; add rsp,0x30; pop rbx,rdi,rsi,r12,r14,r15,rbp; ret
    return dst;
}

LIFT_FN(FbSsoStringCopy, "sub_bc45130", 0xbc45130, sub_bc45130, nullptr);

} // namespace native::bgfx
