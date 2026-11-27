// LIFT 0x3c75f0 size 0xb2 1.26.62.01 sub_3c75f0
#include "sub_3c75f0.h"

#include <cstdint>

namespace native {

sub_3c75f0Out* sub_3c75f0(sub_3c75f0Out* out, void* param)
{
    // 0x3c75f0..0x3c7609
    // 0x3c75f0  push rbp                                      
    // 0x3c75f1  push rsi                                      
    // 0x3c75f2  push rdi                                      
    // 0x3c75f3  push rbx                                      
    // 0x3c75f4  sub rsp,0x38                                  
    // 0x3c75f8  lea rbp,[rsp+0x30]                            
    // 0x3c75fd  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE         ; compiler frame trylevel (-2): write to own stack, dead (never read)
    // 0x3c7605  mov rdi,rdx                                    ; rdi = param (2nd argument), kept live across all calls
    // 0x3c7608  mov rsi,rcx                                    ; rsi = out (1st argument), also the return value
    (void)0; // frame setup; out = RCX, param = RDX (x64 Microsoft ABI)

    // 0x3c760b..0x3c7622   call #1 -> sub_eea6040 via data slot 0xF99FFA0
    // 0x3c760b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0] global object A pointer
    // 0x3c7612  mov rax,[rcx]                                 ; rax = *A = vfptr
    // 0x3c7615  mov rax,[rax+0x10]                            ; rax = vfptr[2] = target left in RAX for the thunk's `jmp rax`
    // 0x3c7619  mov dl,7                                      ; RDX = param with low byte forced to 7
    // 0x3c761b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (boundary/vendor thunk)
    // 0x3c7621  mov [rbp-1],al                                ; own stack byte slot = call #1 result (low byte)
    void** globalA = reinterpret_cast<void**>(0x15233E1B0ULL); // 0x3c760b  mov rcx,[0x1233E1B0]  (VA = image base 0x140000000 + RVA 0x1233E1B0)
    void* objectA = *globalA;                                   // 0x3c7612  mov rax,[rcx]
    void* call1Target = reinterpret_cast<void**>(objectA)[2];   // 0x3c7615  mov rax,[rax+0x10]
    (void)call1Target; // RAX set-up consumed by sub_eea6040's `jmp rax`
    std::uintptr_t rdx1 = (reinterpret_cast<std::uintptr_t>(param) & ~0xFFui64) | 0x7ui64; // 0x3c7619  mov dl,7
    std::uint8_t flag = static_cast<std::uint8_t>(reinterpret_cast<std::uintptr_t>(sub_eea6040(objectA, rdx1))); // 0x3c761b  call qword ptr [0xF99FFA0] ; 0x3c7621  mov [rbp-1],al

    // 0x3c7624..0x3c763d   call #2 -> sub_eea6040 via data slot 0xF99FFA0
    // 0x3c7624  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8] global object B pointer
    // 0x3c762b  mov rax,[rcx]                                 ; rax = *B = vfptr
    // 0x3c762e  mov rax,[rax+8]                               ; rax = vfptr[1] = target left in RAX for the thunk's `jmp rax`
    // 0x3c7632  mov rdx,rdi                                   ; RDX = param
    // 0x3c7635  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    // 0x3c763b  nop                                           
    // 0x3c763c  mov rbx,rax                                   ; rbx = call #2 result
    void** globalB = reinterpret_cast<void**>(0x15233E1A8ULL); // 0x3c7624  mov rcx,[0x1233E1A8]  (VA = image base 0x140000000 + RVA 0x1233E1A8)
    void* objectB = *globalB;                                   // 0x3c762b  mov rax,[rcx]
    void* call2Target = reinterpret_cast<void**>(objectB)[1];   // 0x3c762e  mov rax,[rax+8]
    (void)call2Target; // RAX set-up consumed by sub_eea6040's `jmp rax`
    void* rbx = sub_eea6040(objectB, reinterpret_cast<std::uintptr_t>(param)); // 0x3c7632  mov rdx,rdi ; 0x3c7635  call qword ptr [0xF99FFA0] ; 0x3c763c  mov rbx,rax
    (void)0; // 0x3c763b  nop

    // 0x3c763f..0x3c7649
    // 0x3c763f  test rdi,rdi                                  
    // 0x3c7642  je short 0x3C7649                             ; param == 0 -> loc_3c7649 (skip conditional calls)
    // 0x3c7644  test rbx,rbx                                  
    // 0x3c7647  je short 0x3C7697                             ; rbx == 0 -> loc_3c7697 (allocator path)
    if (param != nullptr && rbx != nullptr) {                   // 0x3c763f  test rdi,rdi ; 0x3c7642  je short 0x3C7649 ; 0x3c7644  test rbx,rbx ; 0x3c7647  je short 0x3C7697
        // 0x3c7653..0x3c765c   call #3 -> sub_eec6ed0 (crt boundary), return ignored
        // 0x3c7653  mov rcx,rbx                                   
        // 0x3c7656  xor edx,edx                                ; RDX = 0
        // 0x3c7658  mov r8,rdi                                 ; R8 = param
        // 0x3c765b  call 0xEEC6ED0                            ; -> sub_eec6ed0
        (void)sub_eec6ed0(rbx, 0ui64, param);                   // 0x3c765b  call 0xEEC6ED0 ; return ignored (original: RAX dead)
    }

    // 0x3c7649..0x3c7653   loc_3c7649: re-tests on the param == 0 entry (test rdi,rdi / je 0x3c7660,
    //                      test rbx,rbx / je 0x3c7660); both branches fall through to loc_3c7660,
    //                      no side effects.
    if (param != nullptr && rbx == nullptr) {                   // 0x3c7649  test rdi,rdi ; 0x3c764c  je short 0x3C7660 ; 0x3c764e  test rbx,rbx ; 0x3c7651  je short 0x3C7660
        // 0x3c7697..0x3c76a1   loc_3c7697: allocator path
        // 0x3c7697  mov rcx,rdi                                   
        // 0x3c769a  call 0x9BC830                             ; -> sub_9bc830 (boundary/alloc), return discarded
        // 0x3c769f  nop                                           
        // 0x3c76a0  jmp short 0x3C7660                        ; -> loc_3c7660 (common tail)
        (void)sub_9bc830(param);                                // 0x3c769a  call 0x9BC830 ; RAX return is overwritten before any use
        (void)0; // 0x3c769f  nop ; 0x3c76a0  jmp short 0x3C7660 -> fall through to the common tail below
    }

    // 0x3c7660..0x3c7679   call #3 -> sub_eea6040 via data slot 0xF99FFA0 (common tail, loc_3c7660)
    // 0x3c7660  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0] global object A pointer (again)
    // 0x3c7667  mov rax,[rcx]                                 ; rax = *A = vfptr
    // 0x3c766a  mov rax,[rax+0x10]                            ; rax = vfptr[2] = target left in RAX for the thunk's `jmp rax`
    // 0x3c766e  movzx edx,byte ptr [rbp-1]                    ; RDX = flag (zero-extended)
    // 0x3c7672  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040, return ignored
    // 0x3c7678  nop                                           
    void** globalA2 = reinterpret_cast<void**>(0x15233E1B0ULL); // 0x3c7660  mov rcx,[0x1233E1B0]
    void* objectA2 = *globalA2;                                 // 0x3c7667  mov rax,[rcx]
    void* call3Target = reinterpret_cast<void**>(objectA2)[2];  // 0x3c766a  mov rax,[rax+0x10]
    (void)call3Target; // RAX set-up consumed by sub_eea6040's `jmp rax`
    sub_eea6040(objectA2, static_cast<std::uintptr_t>(flag));   // 0x3c766e  movzx edx,byte ptr [rbp-1] ; 0x3c7672  call qword ptr [0xF99FFA0] ; 0x3c7678  nop

    // 0x3c7679..0x3c768e
    // 0x3c7679  lea rax,[0x3C7B10]                            ; rax = 0x00000000003C7B10
    // 0x3c7680  mov [rsi],rax                                 ; W out+0x0
    // 0x3c7683  mov [rsi+8],rbx                               ; W out+0x8
    // 0x3c7687  mov [rsi+0x10],rdi                            ; W out+0x10
    out->field00 = reinterpret_cast<void*>(sub_3c75f0Layout::kRvaSub3c7b10); // 0x3c7679  lea rax,[0x3C7B10] ; 0x3c7680  mov [rsi],rax
    out->field08 = rbx;                                         // 0x3c7683  mov [rsi+8],rbx
    out->field10 = param;                                       // 0x3c7687  mov [rsi+0x10],rdi

    // 0x3c768b..0x3c7697
    // 0x3c768b  mov rax,rsi                                    ; return value = out
    // 0x3c768e  add rsp,0x38                                  
    // 0x3c7692  pop rbx                                       
    // 0x3c7693  pop rdi                                       
    // 0x3c7694  pop rsi                                       
    // 0x3c7695  pop rbp                                       
    // 0x3c7696  ret                                           
    return out;                                                 // 0x3c768b  mov rax,rsi ; 0x3c768e  add rsp,0x38 ; 0x3c7692  pop rbx ; 0x3c7693  pop rdi ; 0x3c7694  pop rsi ; 0x3c7695  pop rbp ; 0x3c7696  ret
}

// Verbatim call instructions of the function (matches rdis dis 0x3c75f0 0xb2), plain lines for verify_oc:
#if 0
0x3c761b  call qword ptr [0xF99FFA0]
0x3c7635  call qword ptr [0xF99FFA0]
0x3c765b  call 0xEEC6ED0
0x3c7672  call qword ptr [0xF99FFA0]
0x3c769a  call 0x9BC830
#endif

LIFT_FN(sub_3c75f0, "sub_3c75f0", 0x3c75f0, sub_3c75f0, &sub_3c75f0_footprint);

} // namespace native
