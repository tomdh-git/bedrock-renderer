// LIFT 0x66e5eb0 size 0xae 1.26.62.01 sub_66e5eb0
#include "client/features/render/native/framebuilder/sub_66e5eb0.h"
#include "client/features/render/native/Lift.h"

#include <cstring>
#include <cstdint>
#include <intrin.h>

namespace native {

// sub_eea6040 (0xEEA6040, class vendor, docs/data/native_boundary.tsv line 506) is reached through
// data slot 0xF99FFA0: the original does `call qword ptr [0xF99FFA0]` (0x66e5f0e) with RCX = the
// allocator object (*0x1233E1A8) and EDX = 0x20, and RAX = allocated record or NULL. Lifted code reads
// the pointer from the slot at call time (exactly what the instruction does) and calls the function
// pointer with the same arguments; slot RVA 0xF99FFA0 documented above.
using Eea6040Fn = void* (*)(void*, std::uint32_t);

// sub_9bc830 (0x9BC830, class alloc, docs/data/native_boundary.tsv line 149): allocator out-of-memory
// handler reached on a NULL allocation result, called with RCX = 0x20. It does not return (the process
// is terminated); the instructions after the call in the exe (nop / jmp short 0x66E5F1D) are unreachable
// dead code. Its return is discarded by the original (jmp short 0x66E5F1D right after), so it is modeled
// as returning std::uint64_t and the result is ignored. Wrapped through the Sigs.json-resolved boundary
// wrapper (Boundary<void,...> cannot be called under MSVC: Lift.h:65 static_asserts sizeof(R) which is
// ill-formed for void).
Boundary<std::uint64_t, std::uint64_t> sub_9bc830("sub_9bc830");

// Footprint: the function writes only the caller-provided out object (a0+0x0..0x3F, 0x40 bytes). The
// allocated record is returned through a0+0x20 and is not part of the input footprint; boundary call
// effects are recorded/replayed by the tape mechanism.
static Footprint sub_66e5eb0Footprint(void* a0) {
    return { { a0, 0x40 } };
}

void* sub_66e5eb0(void* a0) {
    Out* out = reinterpret_cast<Out*>(a0);

    // 0x66e5eb0  push rbp
    // 0x66e5eb1  push rsi
    // 0x66e5eb2  sub rsp,0x38
    // 0x66e5eb6  lea rbp,[rsp+0x30]
    // (prologue; nothing observable yet)

    // 0x66e5ebb  mov qword ptr [rcx+8],0                ; W a0+0x8 = 0
    // 0x66e5ec3  mov qword ptr [rcx+0x10],9             ; W a0+0x10 = 9
    // 0x66e5ed3  mov qword ptr [rcx+0x18],0xF           ; W a0+0x18 = 0xF
    out->field10 = kOutField10Value;
    out->field18 = kOutField18Value;

    // 0x66e5edb  mov rax,0x7365546168706C41             ; "AlphaTes" little-endian
    // 0x66e5ee5  mov [rcx],rax                          ; W a0+0x0..0x7 = "AlphaTes"
    // 0x66e5ee8  mov byte ptr [rcx+8],0x74              ; W a0+0x8 = 't'  ("AlphaTest")
    std::memcpy(out->name, kAlphaTest, 7);
    out->name[7] = kAlphaTest[7];

    // 0x66e5eec  xorps xmm0,xmm0
    // 0x66e5eef  movups [rcx+0x20],xmm0                 ; W a0+0x20..0x2F = 0
    std::memset(reinterpret_cast<std::uint8_t*>(out) + kOutOffsetRecord, 0, 16);

    // 0x66e5ef3  mov [rbp-8],rcx                        ; save a0
    // 0x66e5ef7  movups [rcx+0x30],xmm0                 ; W a0+0x30..0x3F = 0
    std::memset(reinterpret_cast<std::uint8_t*>(out) + kOutOffsetField30, 0, 16);

    // 0x66e5efb  mov rcx,[0x1233E1A8]                   ; R data_1233e1a8 (allocator object)
    // 0x66e5f02  mov rax,[rcx]                          ; R *allocator
    // 0x66e5f05  mov rax,[rax+8]                        ; R *allocator+8 (dead: value never used)
    void* allocator = *reinterpret_cast<void**>(reinterpret_cast<void*>(kGlobalAllocator));
    std::uint64_t deadRead = *reinterpret_cast<std::uint64_t*>(
        reinterpret_cast<std::uint8_t*>(allocator) + 8);
    (void)deadRead;

    // 0x66e5f09  mov edx,0x20
    // 0x66e5f0e  call qword ptr [0xF99FFA0]             ; [data_f99ffa0] = sub_eea6040; RAX = record or NULL
    Eea6040Fn allocFn = reinterpret_cast<Eea6040Fn>(
        *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<void*>(kSlotEea6040)));
    void* record = allocFn(allocator, static_cast<std::uint32_t>(kAllocSize));

    // 0x66e5f15  mov rsi,rax                            ; record
    // 0x66e5f18  test rax,rax
    // 0x66e5f1b  je short 0x66E5F51                     ; -> loc_66e5f51 (allocation failure)
    if (record == nullptr) {
        // 0x66e5f51  mov ecx,0x20
        // 0x66e5f56  call 0x9BC830                      ; sub_9bc830(0x20), alloc boundary (noreturn OOM handler)
        // 0x66e5f5b  nop
        // 0x66e5f5c  jmp short 0x66E5F1D                ; unreachable: sub_9bc830 terminates the process
        std::uint64_t oomRet = sub_9bc830(static_cast<std::uint64_t>(kAllocSize));
        (void)oomRet;
        __assume(false);   // sub_9bc830 does not return
    }

    // 0x66e5f1d  mov rax,[rbp-8]                        ; a0
    // 0x66e5f21  mov [rax+0x20],rsi                     ; W a0+0x20 = record
    // 0x66e5f25  mov qword ptr [rax+0x30],0x14          ; W a0+0x30 = 0x14
    // 0x66e5f2d  mov qword ptr [rax+0x38],0x1F          ; W a0+0x38 = 0x1F
    out->record = record;
    out->field30 = kOutField30Value;
    out->field38 = kOutField38Value;

    // 0x66e5f35  movups xmm0,[0xF5F4D16]                ; R data_f5f4d16 16-byte id
    // 0x66e5f3c  movups [rsi],xmm0                      ; W record+0x0..0xF
    // 0x66e5f3f  mov dword ptr [rsi+0x10],0x64657361    ; W record+0x10 = 0x64657361 ("ased")
    // 0x66e5f46  mov byte ptr [rsi+0x14],0              ; W record+0x14 = 0
    std::memcpy(record, reinterpret_cast<const void*>(kRodataOnDiscardValueB), 16);
    *reinterpret_cast<std::uint32_t*>(
        reinterpret_cast<std::uint8_t*>(record) + kRecordOffsetTagDword) = kRecordTagDword;
    *reinterpret_cast<std::uint8_t*>(
        reinterpret_cast<std::uint8_t*>(record) + kRecordOffsetNull) = 0;

    // 0x66e5f4a  add rsp,0x38
    // 0x66e5f4e  pop rsi
    // 0x66e5f4f  pop rbp
    // 0x66e5f50  ret                                    ; return a0
    return a0;
}

// Verbatim instructions of the function (matches `rdis dis 0x66e5eb0 0xae` from the exe,
// machine-checked with tools/sigs/verify_oc.py):
#if 0
0x66e5eb0  push rbp
0x66e5eb1  push rsi
0x66e5eb2  sub rsp,0x38
0x66e5eb6  lea rbp,[rsp+0x30]
0x66e5ebb  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
0x66e5ec3  mov qword ptr [rcx+8],0
0x66e5ecb  mov qword ptr [rcx+0x10],9
0x66e5ed3  mov qword ptr [rcx+0x18],0xF
0x66e5edb  mov rax,0x7365546168706C41
0x66e5ee5  mov [rcx],rax
0x66e5ee8  mov byte ptr [rcx+8],0x74
0x66e5eec  xorps xmm0,xmm0
0x66e5eef  movups [rcx+0x20],xmm0
0x66e5ef3  mov [rbp-8],rcx
0x66e5ef7  movups [rcx+0x30],xmm0
0x66e5efb  mov rcx,[0x1233E1A8]
0x66e5f02  mov rax,[rcx]
0x66e5f05  mov rax,[rax+8]
0x66e5f09  mov edx,0x20
0x66e5f0e  call qword ptr [0xF99FFA0]
0x66e5f14  nop
0x66e5f15  mov rsi,rax
0x66e5f18  test rax,rax
0x66e5f1b  je short 0x66E5F51
0x66e5f1d  mov rax,[rbp-8]
0x66e5f21  mov [rax+0x20],rsi
0x66e5f25  mov qword ptr [rax+0x30],0x14
0x66e5f2d  mov qword ptr [rax+0x38],0x1F
0x66e5f35  movups xmm0,[0xF5F4D16]
0x66e5f3c  movups [rsi],xmm0
0x66e5f3f  mov dword ptr [rsi+0x10],0x64657361
0x66e5f46  mov byte ptr [rsi+0x14],0
0x66e5f4a  add rsp,0x38
0x66e5f4e  pop rsi
0x66e5f4f  pop rbp
0x66e5f50  ret
0x66e5f51  mov ecx,0x20
0x66e5f56  call 0x9BC830
0x66e5f5b  nop
0x66e5f5c  jmp short 0x66E5F1D
0x66e5f5e  xchg ax,ax
#endif

LIFT_FN(sub_66e5eb0, "sub_66e5eb0", 0x66e5eb0, sub_66e5eb0, &sub_66e5eb0Footprint);

} // namespace native
