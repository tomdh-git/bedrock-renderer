// LIFT 0x8e56b0 size 0x78 1.26.62.01 sub_8e56b0
#include "sub_8e56b0.h"

#include <cstdint>
#include <intrin.h>

namespace native {

// sub_8e56b0 (0x8e56b0, size 0x78, 1.26.62.01, "sub_8e56b0").
//
// Recursive child/sibling walk over a node list headed at argument 1 (RCX):
//   - entry: if *(u8*)(node + 0x19) != 0, return immediately
//     (0x8e56bb je short 0x8E56C5 -> epilogue).
//   - for each node: recurse into child (+0x10), then teardown the refcounted
//     object at +0x30 (lock dec +0x8; if it hit 0, call virtual destructor
//     vfptr[0] via the sub_eea6040 thunk; lock dec +0xC; if it hit 0, call
//     virtual delete vfptr[1] via the sub_eea6040 thunk), then release the
//     node via native::sub_e935700(node), then advance to next sibling (+0x00);
//     stop when *(u8*)(next + 0x19) != 0 (0x8e56e1 jne -> epilogue).
// Writes [V]: *(obj+0x8) and *(obj+0xC) (lock dec). No other game memory is
// written by this function itself; sub_e935700 releases the node (it invokes
// boundary sub_eea6040 via data slot 0xF99FFA0). rax is never meaningfully
// returned, so the return type is void [V].
// Callees [V]:
//   - sub_8e56b0 (self-recursion), 0x8e56ea  call 0x8E56B0
//   - sub_e935700 (lift set, native::sub_e935700), 0x8e56d8  call 0xE935700
//   - sub_eea6040 (boundary/vendor, thunk via data slot 0xF99FFA0),
//     0x8e570a  call qword ptr [0xF99FFA0] and 0x8e5720  call qword ptr [0xF99FFA0]
// No null guards or SEH beyond the original's own tests; no stubs.

void sub_8e56b0(void* nodeArg) {
    void* const node = nodeArg;              // RCX = node (argument 1)

    // 0x8e56b0..0x8e56c5  prologue, then entry flag check on node+0x19
    //   0x8e56b0  push rsi
    //   0x8e56b1  push rdi
    //   0x8e56b2  push rbx
    //   0x8e56b3  sub rsp,0x20
    //   0x8e56b7  cmp byte ptr [rcx+0x19],0        ; R node+0x19 (entry flag)
    //   0x8e56bb  je short 0x8E56C5                ; flag == 0 -> process
    //                                                    ; flag != 0 -> epilogue/return
    if (*(std::uint8_t*)(reinterpret_cast<char*>(node) + kNodeOffsetFlag) != 0)
        return;                                      // 0x8e56bb je not taken -> 0x8e56bd epilogue

    void* current = node;                            // 0x8e56c5  mov rsi,rcx

    for (;;) {                                       // 0x8e56e3  loc_8e56e3: loop head
        // 0x8e56e3..0x8e56ea  rdi = current; rcx = [current+0x10] = child; recurse
        //   0x8e56e3  mov rdi,rsi
        //   0x8e56e6  mov rcx,[rsi+0x10]           ; R current+0x10 (child)
        //   0x8e56ea  call 0x8E56B0                ; -> sub_8e56b0 (recursion)
        void* const child =
            *(void**)(reinterpret_cast<char*>(current) + kNodeOffsetChild);
        sub_8e56b0(child);                           // 0x8e56ea  call 0x8E56B0

        // 0x8e56ef..0x8e56f6  rsi = [current] = next; rbx = [current+0x30] = obj
        //   0x8e56ef  mov rsi,[rsi]                ; R current+0x00 (next)
        //   0x8e56f2  mov rbx,[rdi+0x30]           ; R current+0x30 (obj)
        //   0x8e56f6  test rbx,rbx
        //   0x8e56f9  je short 0x8E56D0            ; obj == 0 -> release current
        void* const next = *(void**)current;
        void* const obj =
            *(void**)(reinterpret_cast<char*>(current) + kNodeOffsetObj);

        // Refcounted-object teardown (entirely skipped when obj == null).
        if (obj != nullptr) {
            // 0x8e56fb  lock dec dword ptr [rbx+8]     ; W *(obj+0x8): refcount -1
            //   0x8e56ff  jne short 0x8E56D0           ; refcount != 0 -> release current
            if (_InterlockedDecrement(reinterpret_cast<volatile long*>(
                    reinterpret_cast<char*>(obj) + kObjOffsetRefcount)) == 0) {
                // refcount reached 0: virtual destructor vfptr[0](obj)
                // via sub_eea6040 thunk:
                //   0x8e5701  mov rax,[rbx]            ; R obj+0x00 (vfptr)
                //   0x8e5704  mov rax,[rax]            ; R vfptr[0] (destructor) -> RAX
                //   0x8e5707  mov rcx,rbx              ; RCX = obj
                //   0x8e570a  call qword ptr [0xF99FFA0]   ; -> sub_eea6040 (boundary/vendor)
                void** const vfptr = *(void***)obj;
                boundary::g_eea6040_thunk(obj, vfptr[0]);   // 0x8e570a  call qword ptr [0xF99FFA0]

                // 0x8e5710  lock dec dword ptr [rbx+0xC]   ; W *(obj+0xC): count0xC -1
                //   0x8e5714  jne short 0x8E56D0           ; count0xC != 0 -> release current
                if (_InterlockedDecrement(reinterpret_cast<volatile long*>(
                        reinterpret_cast<char*>(obj) + kObjOffsetCountC)) == 0) {
                    // count0xC reached 0: virtual delete vfptr[1](obj)
                    // via sub_eea6040 thunk:
                    //   0x8e5716  mov rax,[rbx]            ; R obj+0x00 (vfptr)
                    //   0x8e5719  mov rax,[rax+8]          ; R vfptr[1] (operator delete) -> RAX
                    //   0x8e571d  mov rcx,rbx              ; RCX = obj
                    //   0x8e5720  call qword ptr [0xF99FFA0]   ; -> sub_eea6040 (boundary/vendor)
                    boundary::g_eea6040_thunk(obj, vfptr[1]);   // 0x8e5720  call qword ptr [0xF99FFA0]
                }
            }
        }

        // 0x8e56d0..0x8e56d8  mov edx,0x38 (dead store); mov rcx,current;
        //   0x8e56d0  mov edx,0x38                       ; dead store
        //   0x8e56d5  mov rcx,rdi                        ; RCX = current node
        //   0x8e56d8  call 0xE935700                     ; -> sub_e935700 (lift set)
        sub_e935700(current);                          // 0x8e56d8  call 0xE935700

        // 0x8e56dd..0x8e56e1  check next+0x19; == 0 continues the loop,
        //   0x8e56dd  cmp byte ptr [rsi+0x19],0          ; R next+0x19
        //   0x8e56e1  jne short 0x8E56BD                 ; != 0 -> epilogue/return
        // == 0 falls through to loc_8e56e3 with current = next
        if (*(std::uint8_t*)(reinterpret_cast<char*>(next) + kNodeOffsetFlag) != 0)
            return;                                      // 0x8e56e1 jne taken -> 0x8e56bd epilogue
        current = next;                                  // -> 0x8e56e3 loop head
    }
    // unreachable: the loop only exits via the return above
}

} // namespace native

LIFT_FN(sub_8e56b0, "sub_8e56b0", 0x8e56b0, ::native::sub_8e56b0, nullptr);

#if 0
// Verbatim instructions of [0x8e56b0, 0x8e5728) (rdis dis 0x8e56b0 0x78);
// machine-checked by tools/sigs/verify_oc.py against the exe.
0x8e56b0  push rsi
0x8e56b1  push rdi
0x8e56b2  push rbx
0x8e56b3  sub rsp,0x20
0x8e56b7  cmp byte ptr [rcx+0x19],0
0x8e56bb  je short 0x8E56C5
0x8e56bd  add rsp,0x20
0x8e56c1  pop rbx
0x8e56c2  pop rdi
0x8e56c3  pop rsi
0x8e56c4  ret
0x8e56c5  mov rsi,rcx
0x8e56c8  jmp short 0x8E56E3
0x8e56ca  nop [rax+rax]
0x8e56d0  mov edx,0x38
0x8e56d5  mov rcx,rdi
0x8e56d8  call 0xE935700
0x8e56dd  cmp byte ptr [rsi+0x19],0
0x8e56e1  jne short 0x8E56BD
0x8e56e3  mov rdi,rsi
0x8e56e6  mov rcx,[rsi+0x10]
0x8e56ea  call 0x8E56B0
0x8e56ef  mov rsi,[rsi]
0x8e56f2  mov rbx,[rdi+0x30]
0x8e56f6  test rbx,rbx
0x8e56f9  je short 0x8E56D0
0x8e56fb  lock dec dword ptr [rbx+8]
0x8e56ff  jne short 0x8E56D0
0x8e5701  mov rax,[rbx]
0x8e5704  mov rax,[rax]
0x8e5707  mov rcx,rbx
0x8e570a  call qword ptr [0xF99FFA0]
0x8e5710  lock dec dword ptr [rbx+0xC]
0x8e5714  jne short 0x8E56D0
0x8e5716  mov rax,[rbx]
0x8e5719  mov rax,[rax+8]
0x8e571d  mov rcx,rbx
0x8e5720  call qword ptr [0xF99FFA0]
0x8e5726  jmp short 0x8E56D0
#endif
