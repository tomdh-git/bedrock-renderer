// LIFT 0x392960 size 0x35 1.26.62.01 sub_392960
#include "sub_392960.h"

static_assert(sizeof(void*) == 8, "sub_392960: x64 ABI, pointer-sized address space");

namespace native {

// sub_392960 (0x392960, size 0x35, 1.26.62.01).
//
//   0x392960  push rbp
//   0x392961  sub rsp,0x30
//   0x392965  lea rbp,[rsp+0x30]
//   0x39296a  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE   ; frame trylevel = -2 (dead store, never read)
//   0x392972  mov rdx,rcx                                ; copy of the argument (arrives in RCX)
//   0x392975  mov rcx,[0x1233E1A8]                       ; [data_1233e1a8] global object pointer at image RVA 0x1233E1A8
//   0x39297c  test rdx,rdx
//   0x39297f  je short 0x39298F                          ; skip the call when the argument is NULL
//   0x392981  mov rax,[rcx]                              ; rax = *globalObject (vfptr)
//   0x392984  mov rax,[rax+0x10]                         ; rax = vfptr[2] (the method the boundary thunk jumps to via RAX)
//   0x392988  call qword ptr [0xF99FFA0]                 ; [data_f99ffa0] = sub_eea6040, vendor boundary thunk (indirect jump through RAX)
//   0x39298e  nop
//   0x39298f  add rsp,0x30
//   0x392993  pop rbp
//   0x392994  ret
//
// Effect: if (argument != nullptr) sub_eea6040(g_globalObject, argument);
// i.e. the global object's vfptr[2] method is invoked with (this = global object,
// argument = the RCX argument) through the sub_eea6040 thunk; the return value is ignored.
// The two vtable loads at 0x392981/0x392984 produce the thunk's target register (RAX) and
// are otherwise unused by this function.
// Reads: the qword at image RVA 0x1233E1A8 [data_1233e1a8] (global object pointer), then
// the qword at [vfptr+0x10] (vfptr[2]). Writes: none to game memory (only its own stack
// frame). Calls: one, sub_eea6040, boundary class vendor
// (docs/data/native_boundary.tsv: "0xeea6040 vendor thunk via data slot 0xF99FFA0
// (loader-resolved)"). 0 callees in the lift set.
// x64 Microsoft ABI: argument in RCX, return value (incidental, in RAX) ignored.
//
// Verbatim instructions of the function (matches rdis dis 0x392960 0x35):
#if 0
0x392960  push rbp
0x392961  sub rsp,0x30
0x392965  lea rbp,[rsp+0x30]
0x39296a  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
0x392972  mov rdx,rcx
0x392975  mov rcx,[0x1233E1A8]
0x39297c  test rdx,rdx
0x39297f  je short 0x39298F
0x392981  mov rax,[rcx]
0x392984  mov rax,[rax+0x10]
0x392988  call qword ptr [0xF99FFA0]
0x39298e  nop
0x39298f  add rsp,0x30
0x392993  pop rbp
0x392994  ret
#endif

// Boundary callee: sub_eea6040, vendor class, reached through data slot 0xF99FFA0
// (docs/data/native_boundary.tsv). Called with rcx = global object, rdx = argument;
// the thunk tail-jumps to RAX (vfptr[2] of the global object). Return value ignored.
native::Boundary<void, void*, void*> sub_eea6040("sub_eea6040");

// [data_1233e1a8]: pointer to the global object, stored at image RVA 0x1233E1A8,
// i.e. VA 0x15233E1A8 = image base 0x140000000 [V: PE optional header ImageBase] +
// RVA 0x1233E1A8 [V: rdis data label data_1233e1a8].
static void** g_globalObject = reinterpret_cast<void**>(0x15233E1A8ULL);

void sub_392960(void* argument)
{
    // 0x392960..0x39296a   push rbp; sub rsp,0x30; lea rbp,[rsp+0x30]  (compiler frame setup)
    // 0x39296a..0x392972   [rbp-8] = 0xFFFFFFFFFFFFFFFE                (frame trylevel -2; dead store)
    // 0x392972..0x392975   mov rdx,rcx                                 (argument copy)
    void* thisPtr = argument;                                           // 0x392972  mov rdx,rcx

    // 0x392975..0x39297c   mov rcx,[0x1233E1A8]   ; [data_1233e1a8] global object pointer
    void** globalObject = g_globalObject;                               // 0x392975  mov rcx,[0x1233E1A8]

    // 0x39297c..0x39298f   test rdx,rdx ; je short 0x39298F            (skip the call when the argument is NULL)
    if (thisPtr != nullptr) {                                           // 0x39297c  test rdx,rdx ; 0x39297f  je short 0x39298F
        // 0x392981..0x392984   mov rax,[rcx]      ; rax = *globalObject (vfptr)
        // 0x392984..0x392988   mov rax,[rax+0x10] ; rax = vfptr[2] (boundary thunk target in RAX)
        void* thunkTarget = reinterpret_cast<void**>(*globalObject)[2]; // 0x392981  mov rax,[rcx] ; 0x392984  mov rax,[rax+0x10]
        (void)thunkTarget;

        // 0x392988..0x39298f   call qword ptr [0xF99FFA0] ; nop        (boundary call; return value ignored)
        sub_eea6040(globalObject, thisPtr);  // 0x392988  call qword ptr [0xF99FFA0]
    }

    // 0x39298f..0x392995   add rsp,0x30; pop rbp; ret                  (compiler epilogue)
}

LIFT_FN(sub_392960, "sub_392960", 0x392960, sub_392960, nullptr);

} // namespace native
