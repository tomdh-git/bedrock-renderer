// LIFT 0x4e69270 size 0xea 1.26.62.01 sub_4e69270
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_4e69270.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

static_assert(sizeof(void*) == 8, "sub_4e69270: x64 ABI, pointer-sized address space");

namespace native::helpers {

LIFT_FN(sub_4e69270, "sub_4e69270", 0x4e69270, sub_4e69270, nullptr);

// Verbatim call instructions from the disassembly of [0x4e69270, 0x4e6935a) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x4e692b5  call qword ptr [0xF99FFA0]
0x4e692cb  call qword ptr [0xF99FFA0]
0x4e692fb  call qword ptr [0xF99FFA0]
0x4e69309  call 0xE935700
0x4e69329  call qword ptr [0xF99FFA0]
0x4e6933f  call qword ptr [0xF99FFA0]
#endif

uintptr_t sub_4e69270(sub_4e69270_state* self) {
    // 0x4e69270..0x4e69298
    //   4e69270  push rsi; 4e69271  push rdi; 4e69272  sub rsp,0x28   (prologue)
    //   4e69276  mov rsi,rcx              ; self = RCX ('this')
    //   4e69279  movzx eax,byte ptr [rcx+0x1B0]   ; sel = self->caseSelector0x1b0
    //   4e69280  cmp rax,3
    //   4e69284  ja 0x4E6930E             ; sel > 3 -> skip dispatch (end_cleanup only)
    //   4e6928a  lea rcx,[0xF217574]      ; jump table base [data_f217574]
    //   4e69291  movsxd rax,[rcx+rax*4]   ; rax = table[sel]; table contents [V: rdis jt 0xF217574 4]:
    //                                      ;   0 -> 0x4e6930e (end_cleanup)
    //                                      ;   1 -> 0x4e692d3 (release_link)
    //                                      ;   2 -> 0x4e6929a (release_ref0x1a8)
    //                                      ;   3 -> 0x4e6929a (release_ref0x1a8)
    //   4e69295  add rax,rcx
    //   4e69298  jmp rax                  ; indirect branch through the table entry
    uint8_t sel = self->caseSelector0x1b0;
    if (sel <= 3) {                      // 4e69280  cmp rax,3 ; 4e69284  ja 0x4E6930E
        if (sel == 1) {                  // table[1] -> 0x4e692d3 release_link
            // 0x4e692d3..0x4e69309
            //   4e692d3  mov rcx,[rsi+0x198]      ; rcx = self->link0x198  (a)
            //   4e692da  test rcx,rcx
            //   4e692dd  je short 0x4E6930E       ; if a == 0, skip to end_cleanup
            //   4e692df  mov rdx,[rcx+8]          ; rdx = a->child0x08 (b)
            //   4e692e3  test rdx,rdx
            //   4e692e6  je short 0x4E69304       ; if b == 0, skip the release (fall to sub_e935700)
            //   4e692e8  lock dec dword ptr [rdx+0xC]   ; --b->weak
            //   4e692ec  jne short 0x4E69304      ; if weak != 0, skip the dealloc
            //   4e692ee  mov rax,[rdx]            ; b->vtable
            //   4e692f1  mov rax,[rax+8]          ; b->vtable[8] (deallocator)
            //   4e692f5  mov rdi,rcx              ; rdi = a
            //   4e692f8  mov rcx,rdx              ; rcx = b
            //   4e692fb  call qword ptr [0xF99FFA0]   ; b->vtable[1](b) via vendor thunk sub_eea6040
            //   4e69301  mov rcx,rdi              ; rcx = a
            //   4e69304  mov edx,0x20             ; dead: sub_e935700/sub_392960 overwrite RDX with RCX
            //   4e69309  call 0xE935700           ; sub_e935700(a); RAX ignored
            Link0x198* a = self->link0x198;
            if (a != nullptr) {
                RefCounted* b = a->child0x08;
                if (b != nullptr) {
                    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&b->weak)) == 0) {
                        void** vtable = reinterpret_cast<void**>(b->vtable);
                        using DeallocFn = void (*)(void*);
                        DeallocFn dealloc = reinterpret_cast<DeallocFn>(vtable[1]);
                        dealloc(b);                                 // 0x4e692fb call qword ptr [0xF99FFA0]
                    }
                }
                native::sub_e935700(a);   // 0x4e69309 call 0xE935700 ; RAX ignored
            }
        } else if (sel == 2 || sel == 3) { // table[2]/table[3] -> 0x4e6929a release_ref0x1a8
            // 0x4e6929a..0x4e692d1
            //   4e6929a  mov rdi,[rsi+0x1A8]      ; rdi = self->ref0x1a8
            //   4e692a1  test rdi,rdi
            //   4e692a4  je short 0x4E6930E       ; if rdi == 0, skip to end_cleanup
            //   4e692a6  lock dec dword ptr [rdi+8]      ; --rdi->strong
            //   4e692aa  jne short 0x4E6930E      ; if strong != 0, skip to end_cleanup
            //   4e692ac  mov rax,[rdi]            ; rdi->vtable
            //   4e692af  mov rax,[rax]            ; vtable[0] (destructor)
            //   4e692b2  mov rcx,rdi
            //   4e692b5  call qword ptr [0xF99FFA0]   ; vtable[0](rdi) via vendor thunk sub_eea6040
            //   4e692bb  lock dec dword ptr [rdi+0xC]   ; --rdi->weak
            //   4e692bf  jne short 0x4E6930E      ; if weak != 0, skip to end_cleanup
            //   4e692c1  mov rax,[rdi]            ; rdi->vtable (re-read)
            //   4e692c4  mov rax,[rax+8]          ; vtable[8] (deallocator)
            //   4e692c8  mov rcx,rdi
            //   4e692cb  call qword ptr [0xF99FFA0]   ; vtable[1](rdi) via vendor thunk sub_eea6040
            //   4e692d1  jmp short 0x4E6930E      ; to end_cleanup
            RefCounted* rdi = self->ref0x1a8;
            if (rdi != nullptr) {
                if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rdi->strong)) == 0) {
                    void** vtable = reinterpret_cast<void**>(rdi->vtable);
                    using DestroyFn = void (*)(void*);
                    DestroyFn destroy = reinterpret_cast<DestroyFn>(vtable[0]);
                    destroy(rdi);                                 // 0x4e692b5 call qword ptr [0xF99FFA0]
                    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rdi->weak)) == 0) {
                        vtable = reinterpret_cast<void**>(rdi->vtable);
                        using DeallocFn = void (*)(void*);
                        DeallocFn dealloc = reinterpret_cast<DeallocFn>(vtable[1]);
                        dealloc(rdi);                             // 0x4e692cb call qword ptr [0xF99FFA0]
                    }
                }
            }
        }
        // sel == 0: table[0] -> 0x4e6930e end_cleanup (no release, fall through)
        // sel == 1/2/3: release done above, fall through to end_cleanup
    }
    // sel > 3: dispatch skipped, fall straight to end_cleanup

    // 0x4e6930e..0x4e69345   end_cleanup
    //   4e6930e  mov rdi,[rsi+0x148]      ; rdi = self->ref0x148
    //   4e69315  test rdi,rdi
    //   4e69318  je short 0x4E69345       ; if rdi == 0, skip to tail call
    //   4e6931a  lock dec dword ptr [rdi+8]      ; --rdi->strong
    //   4e6931e  jne short 0x4E69345      ; if strong != 0, skip to tail call
    //   4e69320  mov rax,[rdi]            ; rdi->vtable
    //   4e69323  mov rax,[rax]            ; vtable[0] (destructor)
    //   4e69326  mov rcx,rdi
    //   4e69329  call qword ptr [0xF99FFA0]   ; vtable[0](rdi) via vendor thunk sub_eea6040
    //   4e6932f  lock dec dword ptr [rdi+0xC]   ; --rdi->weak
    //   4e69333  jne short 0x4E69345      ; if weak != 0, skip to tail call
    //   4e69335  mov rax,[rdi]            ; rdi->vtable (re-read)
    //   4e69338  mov rax,[rax+8]          ; vtable[8] (deallocator)
    //   4e6933c  mov rcx,rdi
    //   4e6933f  call qword ptr [0xF99FFA0]   ; vtable[1](rdi) via vendor thunk sub_eea6040
    RefCounted* rdi = self->ref0x148;
    if (rdi != nullptr) {
        if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rdi->strong)) == 0) {
            void** vtable = reinterpret_cast<void**>(rdi->vtable);
            using DestroyFn = void (*)(void*);
            DestroyFn destroy = reinterpret_cast<DestroyFn>(vtable[0]);
            destroy(rdi);                                 // 0x4e69329 call qword ptr [0xF99FFA0]
            if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rdi->weak)) == 0) {
                vtable = reinterpret_cast<void**>(rdi->vtable);
                using DeallocFn = void (*)(void*);
                DeallocFn dealloc = reinterpret_cast<DeallocFn>(vtable[1]);
                dealloc(rdi);                             // 0x4e6933f call qword ptr [0xF99FFA0]
            }
        }
    }
    // 0x4e69345..0x4e6935a
    //   4e69345  add rsi,0xE0
    //   4e6934c  mov rcx,rsi              ; rcx = self + 0xE0
    //   4e6934f  add rsp,0x28; 4e69353  pop rdi; 4e69354  pop rsi   (epilogue)
    //   4e69355  jmp 0x4E3B020            ; tail call; RAX result returned as-is
    return sub_4e3b020(reinterpret_cast<sub_4e69270_state*>(
        reinterpret_cast<std::uint8_t*>(self) + 0xE0));
}

} // namespace native::helpers
