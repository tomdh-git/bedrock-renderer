// LIFT 0x670b260 size 0x98 1.26.62.01 sub_670b260
#include "client/features/render/native/framebuilder/sub_670b260.h"
#include "client/features/render/native/Lift.h"

#include <cstring>
#include <cstdint>
#include <intrin.h>

namespace native {

// sub_eea6040 (0xEEA6040, class vendor, docs/data/native_boundary.tsv line 506) is reached through
// data slot 0xF99FFA0: the original does `call qword ptr [0xF99FFA0]` (0x670b28b) with RCX = the
// allocator object (*0x1233E1A8) and EDX = 0x20, and RAX = allocated record or NULL. Lifted code reads
// the pointer from the slot at call time (exactly what the instruction does) and calls the function
// pointer with the same arguments; slot RVA 0xF99FFA0 documented above.
using Eea6040Fn = void* (*)(void*, std::uint32_t);

// sub_9bc830 (0x9BC830, class alloc, docs/data/native_boundary.tsv line 149): allocator out-of-memory
// handler reached on a NULL allocation result, called with RCX = 0x20. It does not return (the process
// is terminated); the instructions after the call in the exe (mov rax,rdi / jmp 0x670b296 / int3
// padding) are unreachable dead code. Its return is discarded by the original (mov rax,rdi right after),
// so it is modeled as returning std::uint64_t and the result is ignored. Wrapped through the
// Sigs.json-resolved boundary wrapper (Boundary<void,...> cannot be called under MSVC: Lift.h:65
// static_asserts sizeof(R) which is ill-formed for void).
Boundary<std::uint64_t, std::uint64_t> sub_9bc830("sub_9bc830");

// Footprint: the function writes only the caller-provided out object (a0+0x0..0x3F). The allocated
// record is returned through a0 and is not part of the input footprint; boundary call effects are
// recorded/replayed by the tape mechanism.
static Footprint sub_670b260Footprint(void* a0) {
    return { { a0, 0x40 } };
}

void* sub_670b260(void* a0) {
    // 0x670b260..0x670b275: prologue (push rsi, push rdi, sub rsp,0x38, save xmm6) and clear the
    // out object's first 32 bytes: a0+0x10..0x1F then a0+0x0..0xF.
    Out* out = reinterpret_cast<Out*>(a0);
    // 0x670b271  movups [rcx+0x10],xmm6   ; W a0+0x10..0x1F = 0
    // 0x670b275  movups [rcx],xmm6        ; W a0+0x0..0xF = 0
    out->field10 = 0;
    out->field18 = 0;
    out->zero0x08 = 0;
    out->buffer = nullptr;

    // 0x670b278  mov rcx,[0x1233E1A8]          ; R data_1233e1a8 (allocator object)
    // 0x670b27f  mov rax,[rcx]                  ; R *allocator
    // 0x670b282  mov rax,[rax+8]                ; R *allocator+8 (dead: value computed, never used)
    void* allocator = *reinterpret_cast<void**>(reinterpret_cast<void*>(kGlobalAllocator));
    std::uint64_t deadRead = *reinterpret_cast<std::uint64_t*>(
        reinterpret_cast<std::uint8_t*>(allocator) + 8);
    (void)deadRead;

    // 0x670b286  mov edx,0x20
    // 0x670b28b  call qword ptr [0xF99FFA0]     ; [data_f99ffa0] = sub_eea6040; RAX = record or NULL
    Eea6040Fn allocFn = reinterpret_cast<Eea6040Fn>(
        *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<void*>(kSlotEea6040)));
    void* record = allocFn(allocator, static_cast<std::uint32_t>(kAllocSize));

    // 0x670b291  test rax,rax
    // 0x670b294  je short 0x670B2E6
    if (record == nullptr) {
        // 0x670b2e6  mov ecx,0x20
        // 0x670b2eb  mov rdi,rax              ; rax == 0: the NULL allocation result
        // 0x670b2ee  call 0x9BC830             ; sub_9bc830(0x20), alloc boundary (noreturn OOM handler)
        // 0x670b2f3  mov rax,rdi               ; unreachable: sub_9bc830 terminates the process
        // 0x670b2f6  jmp short 0x670B296       ; unreachable
        // 0x670b2f8..0x670b300  int3 x8         ; padding past end of function (size 0x98)
        std::uint64_t oomRet = sub_9bc830(0x20ull);
        (void)oomRet;
        __assume(false);   // sub_9bc830 does not return
    }

    // 0x670b296..0x670b2e6: shared success tail (entered at 0x670b296 on the success path; the failure
    // path never reaches here because sub_9bc830 does not return).
    // 0x670b296  mov [rsi],rax                ; W a0+0x0 = record (NULL only on the dead failure path)
    out->buffer = record;
    // 0x670b299  mov qword ptr [rsi+0x10],0x12   ; W a0+0x10
    out->field10 = kOutField10Value;
    // 0x670b2a1  mov qword ptr [rsi+0x18],0x1F   ; W a0+0x18
    out->field18 = kOutField18Value;
    // 0x670b2a9  movups xmm0,[0xF55AF3F]         ; R data_f55af3f "RenderAsBillboards" (16 bytes)
    // 0x670b2b0  movups [rax],xmm0               ; W record+0x0..0xF
    // 0x670b2b3  mov word ptr [rax+0x10],0x7364  ; W record+0x10 = 0x7364 ('d','s')
    // 0x670b2b9  mov byte ptr [rax+0x12],0       ; W record+0x12 = 0
    std::memcpy(record, reinterpret_cast<const void*>(kRodataRenderAsBillboards), 16);
    *reinterpret_cast<std::uint16_t*>(
        reinterpret_cast<std::uint8_t*>(record) + kRecordOffsetTag) = kRecordTag;
    *reinterpret_cast<std::uint8_t*>(
        reinterpret_cast<std::uint8_t*>(record) + kRecordOffsetNull) = 0;
    // 0x670b2bd  movups [rsi+0x20],xmm6          ; W a0+0x20..0x2F = 0
    std::memset(reinterpret_cast<std::uint8_t*>(out) + kOutOffsetField20, 0, 16);
    // 0x670b2c1  mov qword ptr [rsi+0x30],2      ; W a0+0x30 = 2
    out->field30 = kOutField30Value;
    // 0x670b2c9  mov qword ptr [rsi+0x38],0xF    ; W a0+0x38 = 0xF
    out->field38 = kOutField38Value;
    // 0x670b2d1  mov word ptr [rsi+0x20],0x6E4F  ; W a0+0x20 = 0x6E4F
    out->field20 = kOutField20Value;
    // 0x670b2d7  mov rax,rsi
    // 0x670b2da  movaps xmm6,[rsp+0x20]
    // 0x670b2df  add rsp,0x38
    // 0x670b2e3  pop rdi
    // 0x670b2e4  pop rsi
    // 0x670b2e5  ret
    return a0;
}

// Verbatim instructions of the function (matches `rdis dis 0x670b260 0x98` from the exe,
// machine-checked with tools/sigs/verify_oc.py):
#if 0
0x670b260  push rsi
0x670b261  push rdi
0x670b262  sub rsp,0x38
0x670b266  movaps [rsp+0x20],xmm6
0x670b26b  mov rsi,rcx
0x670b26e  xorps xmm6,xmm6
0x670b271  movups [rcx+0x10],xmm6
0x670b275  movups [rcx],xmm6
0x670b278  mov rcx,[0x1233E1A8]
0x670b27f  mov rax,[rcx]
0x670b282  mov rax,[rax+8]
0x670b286  mov edx,0x20
0x670b28b  call qword ptr [0xF99FFA0]
0x670b291  test rax,rax
0x670b294  je short 0x670B2E6
0x670b296  mov [rsi],rax
0x670b299  mov qword ptr [rsi+0x10],0x12
0x670b2a1  mov qword ptr [rsi+0x18],0x1F
0x670b2a9  movups xmm0,[0xF55AF3F]
0x670b2b0  movups [rax],xmm0
0x670b2b3  mov word ptr [rax+0x10],0x7364
0x670b2b9  mov byte ptr [rax+0x12],0
0x670b2bd  movups [rsi+0x20],xmm6
0x670b2c1  mov qword ptr [rsi+0x30],2
0x670b2c9  mov qword ptr [rsi+0x38],0xF
0x670b2d1  mov word ptr [rsi+0x20],0x6E4F
0x670b2d7  mov rax,rsi
0x670b2da  movaps xmm6,[rsp+0x20]
0x670b2df  add rsp,0x38
0x670b2e3  pop rdi
0x670b2e4  pop rsi
0x670b2e5  ret
0x670b2e6  mov ecx,0x20
0x670b2eb  mov rdi,rax
0x670b2ee  call 0x9BC830
0x670b2f3  mov rax,rdi
0x670b2f6  jmp short 0x670B296
#endif

LIFT_FN(sub_670b260, "sub_670b260", 0x670b260, sub_670b260, &sub_670b260Footprint);

} // namespace native
