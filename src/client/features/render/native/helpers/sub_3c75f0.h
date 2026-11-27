#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/native/Lift.h"

// sub_3c75f0 (0x3c75f0, size 0xb2, 1.26.62.01).
//
//   0x3c75f0  push rbp                                      
//   0x3c75f1  push rsi                                      
//   0x3c75f2  push rdi                                      
//   0x3c75f3  push rbx                                      
//   0x3c75f4  sub rsp,0x38                                  
//   0x3c75f8  lea rbp,[rsp+0x30]                            
//   0x3c75fd  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE        
//   0x3c7605  mov rdi,rdx                                   
//   0x3c7608  mov rsi,rcx                                   
//   0x3c760b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
//   0x3c7612  mov rax,[rcx]                                 
//   0x3c7615  mov rax,[rax+0x10]                            
//   0x3c7619  mov dl,7                                      
//   0x3c761b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
//   0x3c7621  mov [rbp-1],al                                
//   0x3c7624  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
//   0x3c762b  mov rax,[rcx]                                 
//   0x3c762e  mov rax,[rax+8]                               
//   0x3c7632  mov rdx,rdi                                   
//   0x3c7635  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
//   0x3c763b  nop                                           
//   0x3c763c  mov rbx,rax                                   
//   0x3c763f  test rdi,rdi                                  
//   0x3c7642  je short 0x3C7649                             ; -> loc_3c7649
//   0x3c7644  test rbx,rbx                                  
//   0x3c7647  je short 0x3C7697                             ; -> loc_3c7697
//   0x3c7649  test rdi,rdi                                  
//   0x3c764c  je short 0x3C7660                             ; -> loc_3c7660
//   0x3c764e  test rbx,rbx                                  
//   0x3c7651  je short 0x3C7660                             ; -> loc_3c7660
//   0x3c7653  mov rcx,rbx                                   
//   0x3c7656  xor edx,edx                                   
//   0x3c7658  mov r8,rdi                                    
//   0x3c765b  call 0xEEC6ED0                                ; -> sub_eec6ed0
//   0x3c7660  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
//   0x3c7667  mov rax,[rcx]                                 
//   0x3c766a  mov rax,[rax+0x10]                            
//   0x3c766e  movzx edx,byte ptr [rbp-1]                    
//   0x3c7672  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
//   0x3c7678  nop                                           
//   0x3c7679  lea rax,[0x3C7B10]                            ; [sub_3c7b10]
//   0x3c7680  mov [rsi],rax                                 ; W out+0x0
//   0x3c7683  mov [rsi+8],rbx                               ; W out+0x8
//   0x3c7687  mov [rsi+0x10],rdi                            ; W out+0x10
//   0x3c768b  mov rax,rsi                                   
//   0x3c768e  add rsp,0x38                                  
//   0x3c7692  pop rbx                                       
//   0x3c7693  pop rdi                                       
//   0x3c7694  pop rsi                                       
//   0x3c7695  pop rbp                                       
//   0x3c7696  ret                                           
//   0x3c7697  mov rcx,rdi                                   
//   0x3c769a  call 0x9BC830                                 ; -> sub_9bc830
//   0x3c769f  nop                                           
//   0x3c76a0  jmp short 0x3C7660                            ; -> loc_3c7660
//
// Effect: RCX = out (3-pointer object), RDX = param, return RAX = out.
//   Reads: qword at RVA 0x1233E1B0 ([data_1233e1b0], global A), *A and [vfptrA+0x10];
//          qword at RVA 0x1233E1A8 ([data_1233e1a8], global B), *B and [vfptrB+0x8];
//          own stack byte slot [rbp-1] (flag).
//   Writes: out+0x0 (8 bytes: 0x00000000003C7B10), out+0x8 (8 bytes: rbx), out+0x10 (8 bytes: param).
//   Calls (all boundary, docs/data/native_boundary.tsv): sub_eea6040 (vendor thunk via data slot 0xF99FFA0) x3
//   at 0x3c761b/0x3c7635/0x3c7672; sub_eec6ed0 (crt IAT thunk) at 0x3c765b; sub_9bc830 (alloc) at 0x3c769a,
//   whose return value is discarded (RAX clobbered before any use). 0 callees in the lift set.
//   Every branch is lifted: param==0 and rbx==0 both reach the common tail at 0x3c7660; no instruction skipped.
//
// x64 Microsoft ABI: RCX = out, RDX = param, RAX = out.

// Out object written by the function: three pointer fields at out+0x0/0x8/0x10.
struct sub_3c75f0Out {
    void* field00;   // +0x00: written 0x00000000003C7B10 (lea rax,[0x3C7B10] at 0x3c7679)
    void* field08;   // +0x08: rbx = sub_eea6040(globalB, param) result, or nullptr after the 0x3c769a path
    void* field10;   // +0x10: param (2nd argument, arrives in RDX)
};

struct sub_3c75f0Layout {
    static_assert(sizeof(void*) == 8, "sub_3c75f0: x64 ABI, pointer-sized address space");
    static_assert(sizeof(sub_3c75f0Out) == 0x18, "sub_3c75f0: out object is exactly 3 pointers");
    static_assert(offsetof(sub_3c75f0Out, field00) == 0x0, "sub_3c75f0: out field00 at +0x0");
    static_assert(offsetof(sub_3c75f0Out, field08) == 0x8, "sub_3c75f0: out field08 at +0x8");
    static_assert(offsetof(sub_3c75f0Out, field10) == 0x10, "sub_3c75f0: out field10 at +0x10");
    static constexpr std::uintptr_t kImageBase = 0x140000000ULL;   // [V: PE optional header ImageBase]
    static constexpr std::uintptr_t kRvaData1233e1b0 = 0x1233E1B0; // [data_1233e1b0] global A pointer (RVA)
    static constexpr std::uintptr_t kRvaData1233e1a8 = 0x1233E1A8; // [data_1233e1a8] global B pointer (RVA)
    static constexpr std::uintptr_t kRvaSlotF99ffa0 = 0xF99FFA0;   // data slot holding sub_eea6040 (RVA)
    static constexpr std::uintptr_t kRvaSub3c7b10 = 0x3C7B10;      // value stored to out+0x0 (lea target, RVA)
    static constexpr std::uintptr_t kVfptrAField2Offset = 0x10;    // [vfptr+0x10] = thunk target for calls #1/#3
    static constexpr std::uintptr_t kVfptrBField1Offset = 0x8;     // [vfptr+0x8] = thunk target for call #2
    static_assert(kImageBase + kRvaData1233e1b0 == 0x15233E1B0ULL, "sub_3c75f0: data_1233e1b0 VA 0x15233E1B0");
    static_assert(kImageBase + kRvaData1233e1a8 == 0x15233E1A8ULL, "sub_3c75f0: data_1233e1a8 VA 0x15233E1A8");
    static_assert(kImageBase + kRvaSlotF99ffa0 == 0x14F99FFA0ULL, "sub_3c75f0: slot 0xF99FFA0 VA 0x14F99FFA0");
    static_assert(kRvaSub3c7b10 == 0x3C7B10, "sub_3c75f0: stored function value 0x3C7B10");
    static_assert(kVfptrAField2Offset == 0x10, "sub_3c75f0: vfptr[2] offset 0x10");
    static_assert(kVfptrBField1Offset == 0x8, "sub_3c75f0: vfptr[1] offset 0x8");
};

namespace native {

// sub_eea6040 (0xeea6040, boundary/vendor): loader-resolved thunk via data slot 0xF99FFA0 (body `jmp rax`).
// Called with RCX = self pointer, RDX = 64-bit argument; the real target is the value the caller leaves in RAX
// ([vfptr+0x10] for calls #1/#3, [vfptr+0x8] for call #2). Return: callee's RAX (byte at call #1, pointer at #2,
// ignored at #3).
native::Boundary<void*, void*, std::uintptr_t> sub_eea6040("sub_eea6040");
// sub_eec6ed0 (0xeec6ed0, boundary/crt): IAT import thunk (CRT/memory). Called (rbx, 0, param); return ignored.
// Declared with a void* return because Lift.h's Boundary static_assert (sizeof(R) <= 8) cannot be instantiated
// for R = void; the return value is discarded like the original's RAX.
native::Boundary<void*, void*, std::uintptr_t, void*> sub_eec6ed0("sub_eec6ed0");
// sub_9bc830 (0x9bc830, boundary/alloc): allocator. Called (param); return value discarded by this function.
// Declared with a void* return for the same Lift.h reason; the return value is discarded like the original's RAX.
native::Boundary<void*, void*> sub_9bc830("sub_9bc830");

// Footprint: exactly the 0x18-byte out object this function writes (3 qword stores, same order as the exe).
static native::Footprint sub_3c75f0_footprint(sub_3c75f0Out* out, void* param) {
    (void)param;
    return native::Footprint{{out, 0x18}};
}

// sub_3c75f0 (0x3c75f0, 0xb2 bytes, 1.26.62.01): RCX = out, RDX = param, returns RAX = out.
// Reversed source: see sub_3c75f0.cpp (instruction-by-instruction; every call quoted verbatim).
sub_3c75f0Out* sub_3c75f0(sub_3c75f0Out* out, void* param);

} // namespace native
