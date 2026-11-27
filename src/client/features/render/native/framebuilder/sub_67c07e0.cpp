// LIFT 0x67c07e0 size 0xed 1.26.62.01 sub_67c07e0
#include "client/features/render/native/framebuilder/sub_67c07e0.h"
#include "client/features/render/native/Lift.h"

#include <cstring>
#include <cstdint>
#include <intrin.h>

namespace native {

// Data addresses (VA == RVA at the preferred image base, 1.26.62.01) [V disassembly]
static constexpr std::uintptr_t kGlobalAllocator   = 0x1233E1A8; // uint64_t* : allocator object (read at 0x67c0836)
static constexpr std::uintptr_t kSlotEea6040       = 0x000F99FFA0; // data slot holding sub_eea6040 (read at 0x67c0849 / 0x67c08a8)
static constexpr std::uintptr_t kRodataPtr         = 0x00F2BE950; // pointer written to record+0x0 (read at 0x67c086d via lea)

// sub_eea6040 (0xEEA6040, class vendor, docs/data/native_boundary.tsv line 506) is reached through
// data slot 0xF99FFA0: the original does `call qword ptr [0xF99FFA0]` and RAX = allocated record or NULL.
// Lifted code reads the pointer from the slot at call time (exactly what the instruction does) and calls
// the function pointer with the same arguments; slot RVA 0xF99FFA0 documented above.
using Eea6040Fn = void* (*)(void*, std::uint32_t);

// sub_9bc830 (0x9BC830, class alloc, docs/data/native_boundary.tsv line 149): allocator out-of-memory
// handler reached on a NULL allocation result, called with RCX = 0x30. It does not return (the process
// is terminated); the instructions after the call in the exe (nop / jmp 0x67c0858) are unreachable dead
// code. Its return is discarded by the original. Wrapped through the Sigs.json-resolved boundary wrapper
// (Boundary<void,...> cannot be called under MSVC: Lift.h:65 static_asserts sizeof(R) which is ill-formed
// for void).
Boundary<std::uint64_t, std::uint64_t> sub_9bc830("sub_9bc830");

// Allocation size (EDX at 0x67c0844; ECX for sub_9bc830 at 0x67c08c0) [V]
static constexpr std::uint32_t kAllocSize = 0x30;

// Constant written to record+0x8 (0x67c0869) [V]
static constexpr std::uint64_t kRecordField8 = 0x100000001ull;

// Footprint: the function writes the out object a0+0x0..0xF (field0 and field8) and zeroes a2+0x0..0xF.
// Boundary call effects are recorded/replayed by the tape mechanism.
static Footprint sub_67c07e0Footprint(Slot17Out* a0, void* a1, Slot17RefCounted* a2) {
    return { { a0, 0x10 }, { a2, 0x10 } };
}

void* sub_67c07e0(Slot17Out* a0, void* a1, Slot17RefCounted* a2) {
    // 0x67c07e0..0x67c07ea prologue (push rbp, r15, r14, r12, rsi, rdi, rbx; sub rsp,0x70;
    // lea rbp,[rsp+0x70]) — no observable effect.
    // 0x67c07f3 mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE  ; dead stack store
    // 0x67c07fb  mov rdi,rdx   ; a1 -> rdi
    // 0x67c07fe  mov rsi,rcx   ; a0 -> rsi
    Slot17Out* out = a0;           // rsi
    void* a1_copy = a1;            // rdi
    Slot17RefCounted* a2_obj = a2; // r8

    // 0x67c0801  xorps xmm0,xmm0
    // 0x67c0804  movups [rcx],xmm0   ; W a0+0x0 = 0 (16 bytes)
    std::memset(out, 0, 16);        // 0x67c0801..0x67c0804

    // 0x67c0807  mov r14,[r8]        ; R a2+0x0
    // 0x67c080a  mov [rbp-0x30],r14  ; dead stack store
    // 0x67c080e  mov r15,[r8+8]      ; R a2+0x8
    // 0x67c0812  mov [rbp-0x28],r15  ; dead stack store
    void* f0 = a2_obj->field0;      // 0x67c0807
    void* f8 = a2_obj->field8;      // 0x67c080e
    // 0x67c0816  movups [r8],xmm0    ; W a2+0x0 = 0 (16 bytes) [zeroes a2+0x8 too]
    std::memset(a2_obj, 0, 16);     // 0x67c0816
    // 0x67c081a  mov [rbp-0x10],r8   ; save a2
    // 0x67c081e  mov r12,[r8+0x10]   ; R a2+0x10
    // 0x67c0822  mov [rbp-0x20],r12  ; dead stack store
    void* f10 = a2_obj->field10;    // 0x67c081e
    // 0x67c0826  mov [rbp-0x48],rdx  ; dead stack store (a1)
    // 0x67c082a  lea rax,[rbp-0x30]  ; dead
    // 0x67c082e  mov [rbp-0x40],rax  ; dead
    // 0x67c0832  mov byte ptr [rbp-0x38],1  ; dead

    // 0x67c0836  mov rcx,[0x1233E1A8]        ; R data_1233e1a8 (allocator object)
    // 0x67c083d  mov rax,[rcx]               ; R *allocator
    // 0x67c0840  mov rax,[rax+8]             ; R vtable[1] (dead read)
    // 0x67c0844  mov edx,0x30
    // 0x67c0849  call qword ptr [0xF99FFA0]  ; [data_f99ffa0] = sub_eea6040; RAX = record or NULL
    void* allocator = *reinterpret_cast<void**>(reinterpret_cast<void*>(kGlobalAllocator));
    std::uint64_t deadRead1 = *reinterpret_cast<std::uint64_t*>(
        reinterpret_cast<std::uint8_t*>(allocator) + 8);
    (void)deadRead1;
    Eea6040Fn allocFn = reinterpret_cast<Eea6040Fn>(
        *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<void*>(kSlotEea6040)));
    Slot17Record* record = reinterpret_cast<Slot17Record*>(
        allocFn(allocator, static_cast<std::uint32_t>(kAllocSize)));

    // 0x67c084f  nop
    // 0x67c0850  mov rbx,rax              ; rbx = record
    // 0x67c0853  test rax,rax
    // 0x67c0856  je short 0x67C08C0       ; -> loc_67c08c0 (alloc failure)
    if (record == nullptr) {
        // 0x67c08c0  mov ecx,0x30
        // 0x67c08c5  call 0x9BC830        ; -> sub_9bc830 (alloc boundary OOM handler, noreturn)
        // 0x67c08ca  nop                  ; unreachable
        // 0x67c08cb  jmp short 0x67C0858  ; unreachable
        std::uint64_t oomRet = sub_9bc830(0x30ull);
        (void)oomRet;
        __assume(false);   // sub_9bc830 does not return
    }

    // 0x67c0858  xorps xmm0,xmm0
    // 0x67c085b  movaps [rbp-0x30],xmm0   ; dead stack store
    // 0x67c085f  mov rax,0x100000001
    // 0x67c0869  mov [rbx+8],rax          ; W record+0x8 = 0x100000001
    record->field8 = kRecordField8;     // 0x67c085f..0x67c0869
    // 0x67c086d  lea rax,[0xF2BE950]      ; R rodata pointer
    // 0x67c0874  mov [rbx],rax            ; W record+0x0 = kRodataPtr
    record->field0 = reinterpret_cast<void*>(kRodataPtr);  // 0x67c086d..0x67c0874
    // 0x67c0877  mov [rbx+0x10],r14       ; W record+0x10 = a2+0x0 (f0)
    record->field10 = f0;               // 0x67c0877
    // 0x67c087b  mov [rbx+0x18],r15       ; W record+0x18 = a2+0x8 (f8)
    record->field18 = f8;               // 0x67c087b
    // 0x67c087f  mov [rbx+0x20],r12       ; W record+0x20 = a2+0x10 (f10)
    record->field20 = f10;              // 0x67c087f
    // 0x67c0883  mov [rbx+0x28],rdi       ; W record+0x28 = a1
    record->field28 = a1_copy;          // 0x67c0883
    // 0x67c0887  mov [rsi],rdi            ; W a0+0x0 = a1
    out->field0 = a1_copy;              // 0x67c0887
    // 0x67c088a  mov [rsi+8],rbx          ; W a0+0x8 = record
    out->field8 = record;               // 0x67c088a
    // 0x67c088e  mov rax,[rbp-0x10]       ; rax = a2
    // 0x67c0892  mov rcx,[rax+8]          ; rcx = a2+0x8 = 0 (zeroed at 0x67c0816)
    // 0x67c0896  test rcx,rcx
    // 0x67c0899  je short 0x67C08AE       ; always taken (zero) -> release block dead
    if (a2_obj->field8 != nullptr) {    // 0x67c088e..0x67c0899  ; always false: a2+0x8 was zeroed
        // 0x67c089b  lock dec dword ptr [rcx+0xC]
        // 0x67c089f  jne short 0x67C08AE  ; release block dead (never entered)
        if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&a2_obj->refcount)) == 0) {  // 0x67c089b..0x67c089f
            // 0x67c08a1  mov rax,[rcx]      ; R vtable pointer (dead read)
            // 0x67c08a4  mov rax,[rax+8]    ; R vtable[1] (dead read)
            // 0x67c08a8  call qword ptr [0xF99FFA0]  ; [data_f99ffa0] = sub_eea6040; return discarded
            void* obj = a2_obj->field8;          // = 0 here; unreachable
            std::uint64_t deadRead2 = *reinterpret_cast<std::uint64_t*>(obj);
            std::uint64_t deadRead3 = *reinterpret_cast<std::uint64_t*>(
                reinterpret_cast<std::uint8_t*>(obj) + 8);
            (void)deadRead2;
            (void)deadRead3;
            Eea6040Fn releaseFn = reinterpret_cast<Eea6040Fn>(
                *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<void*>(kSlotEea6040)));
            (void)releaseFn(obj, static_cast<std::uint32_t>(kAllocSize));
        }
    }
    // 0x67c08ae  mov rax,rsi              ; rax = a0
    // 0x67c08b1  add rsp,0x70
    // 0x67c08b5  pop rbx
    // 0x67c08b6  pop rdi
    // 0x67c08b7  pop rsi
    // 0x67c08b8  pop r12
    // 0x67c08ba  pop r14
    // 0x67c08bc  pop r15
    // 0x67c08be  pop rbp
    // 0x67c08bf  ret
    return a0;                          // 0x67c08ae..0x67c08bf
}

// Verbatim instructions of the function (matches `rdis dis 0x67c07e0 0xed` from the exe,
// machine-checked with tools/sigs/verify_oc.py):
//   0x67c07e0: push rbp / push r15 / push r14 / push r12 / push rsi / push rdi / push rbx
//   0x67c07ea: sub rsp,0x70 / lea rbp,[rsp+0x70]
//   0x67c07f3: mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
//   0x67c07fb: mov rdi,rdx             ; a1 -> rdi
//   0x67c07fe: mov rsi,rcx             ; a0 -> rsi
//   0x67c0801: xorps xmm0,xmm0
//   0x67c0804: movups [rcx],xmm0       ; W a0+0x0
//   0x67c0807: mov r14,[r8]            ; R a2+0x0
//   0x67c080a: mov [rbp-0x30],r14
//   0x67c080e: mov r15,[r8+8]          ; R a2+0x8
//   0x67c0812: mov [rbp-0x28],r15
//   0x67c0816: movups [r8],xmm0        ; W a2+0x0
//   0x67c081a: mov [rbp-0x10],r8
//   0x67c081e: mov r12,[r8+0x10]       ; R a2+0x10
//   0x67c0822: mov [rbp-0x20],r12
//   0x67c0826: mov [rbp-0x48],rdx
//   0x67c082a: lea rax,[rbp-0x30]
//   0x67c082e: mov [rbp-0x40],rax
//   0x67c0832: mov byte ptr [rbp-0x38],1
//   0x67c0836: mov rcx,[0x1233E1A8]
//   0x67c083d: mov rax,[rcx]
//   0x67c0840: mov rax,[rax+8]
//   0x67c0844: mov edx,0x30
//   0x67c0849: call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
//   0x67c084f: nop
//   0x67c0850: mov rbx,rax
//   0x67c0853: test rax,rax
//   0x67c0856: je short 0x67C08C0
//   0x67c0858: xorps xmm0,xmm0
//   0x67c085b: movaps [rbp-0x30],xmm0
//   0x67c085f: mov rax,0x100000001
//   0x67c0869: mov [rbx+8],rax
//   0x67c086d: lea rax,[0xF2BE950]
//   0x67c0874: mov [rbx],rax
//   0x67c0877: mov [rbx+0x10],r14
//   0x67c087b: mov [rbx+0x18],r15
//   0x67c087f: mov [rbx+0x20],r12
//   0x67c0883: mov [rbx+0x28],rdi
//   0x67c0887: mov [rsi],rdi             ; W a0+0x0
//   0x67c088a: mov [rsi+8],rbx           ; W a0+0x8
//   0x67c088e: mov rax,[rbp-0x10]
//   0x67c0892: mov rcx,[rax+8]
//   0x67c0896: test rcx,rcx
//   0x67c0899: je short 0x67C08AE
//   0x67c089b: lock dec dword ptr [rcx+0xC]
//   0x67c089f: jne short 0x67C08AE
//   0x67c08a1: mov rax,[rcx]
//   0x67c08a4: mov rax,[rax+8]
//   0x67c08a8: call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
//   0x67c08ae: mov rax,rsi
//   0x67c08b1: add rsp,0x70
//   0x67c08b5: pop rbx
//   0x67c08b6: pop rdi
//   0x67c08b7: pop rsi
//   0x67c08b8: pop r12
//   0x67c08ba: pop r14
//   0x67c08bc: pop r15
//   0x67c08be: pop rbp
//   0x67c08bf: ret
//   0x67c08c0: mov ecx,0x30
//   0x67c08c5: call 0x9BC830             ; -> sub_9bc830
//   0x67c08ca: nop
//   0x67c08cb: jmp short 0x67C0858
#if 0
0x67c07e0  push rbp
0x67c07e1  push r15
0x67c07e3  push r14
0x67c07e5  push r12
0x67c07e7  push rsi
0x67c07e8  push rdi
0x67c07e9  push rbx
0x67c07ea  sub rsp,0x70
0x67c07ee  lea rbp,[rsp+0x70]
0x67c07f3  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
0x67c07fb  mov rdi,rdx
0x67c07fe  mov rsi,rcx
0x67c0801  xorps xmm0,xmm0
0x67c0804  movups [rcx],xmm0
0x67c0807  mov r14,[r8]
0x67c080a  mov [rbp-0x30],r14
0x67c080e  mov r15,[r8+8]
0x67c0812  mov [rbp-0x28],r15
0x67c0816  movups [r8],xmm0
0x67c081a  mov [rbp-0x10],r8
0x67c081e  mov r12,[r8+0x10]
0x67c0822  mov [rbp-0x20],r12
0x67c0826  mov [rbp-0x48],rdx
0x67c082a  lea rax,[rbp-0x30]
0x67c082e  mov [rbp-0x40],rax
0x67c0832  mov byte ptr [rbp-0x38],1
0x67c0836  mov rcx,[0x1233E1A8]
0x67c083d  mov rax,[rcx]
0x67c0840  mov rax,[rax+8]
0x67c0844  mov edx,0x30
0x67c0849  call qword ptr [0xF99FFA0]
0x67c084f  nop
0x67c0850  mov rbx,rax
0x67c0853  test rax,rax
0x67c0856  je short 0x67C08C0
0x67c0858  xorps xmm0,xmm0
0x67c085b  movaps [rbp-0x30],xmm0
0x67c085f  mov rax,0x100000001
0x67c0869  mov [rbx+8],rax
0x67c086d  lea rax,[0xF2BE950]
0x67c0874  mov [rbx],rax
0x67c0877  mov [rbx+0x10],r14
0x67c087b  mov [rbx+0x18],r15
0x67c087f  mov [rbx+0x20],r12
0x67c0883  mov [rbx+0x28],rdi
0x67c0887  mov [rsi],rdi
0x67c088a  mov [rsi+8],rbx
0x67c088e  mov rax,[rbp-0x10]
0x67c0892  mov rcx,[rax+8]
0x67c0896  test rcx,rcx
0x67c0899  je short 0x67C08AE
0x67c089b  lock dec dword ptr [rcx+0xC]
0x67c089f  jne short 0x67C08AE
0x67c08a1  mov rax,[rcx]
0x67c08a4  mov rax,[rax+8]
0x67c08a8  call qword ptr [0xF99FFA0]
0x67c08ae  mov rax,rsi
0x67c08b1  add rsp,0x70
0x67c08b5  pop rbx
0x67c08b6  pop rdi
0x67c08b7  pop rsi
0x67c08b8  pop r12
0x67c08ba  pop r14
0x67c08bc  pop r15
0x67c08be  pop rbp
0x67c08bf  ret
0x67c08c0  mov ecx,0x30
0x67c08c5  call 0x9BC830
0x67c08ca  nop
0x67c08cb  jmp short 0x67C0858
#endif

LIFT_FN(sub_67c07e0, "sub_67c07e0", 0x67c07e0, sub_67c07e0, &sub_67c07e0Footprint);

} // namespace native
