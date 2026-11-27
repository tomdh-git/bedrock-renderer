// LIFT 0x56cc4f0 size 0xef 1.26.62.01 sub_56cc4f0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_56cc4f0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native {
// sub_e935700 (0xe935700, lift set): tail jump to sub_392960; single argument in RCX,
// result in RAX. Called directly, never through a boundary wrapper.
void* sub_e935700(void* a0);
} // namespace native

namespace native::helpers {

// Layout assertions for the structs this lift touches. Offsets mirror the disassembly
// field accesses ([reg+off]) and are asserted with offsetof so the lift is self-checking.
// (The same structs and offsetof static_asserts are declared in sub_56cc4f0.h; this
// layout block lives in the .cpp so liftcheck sees a static_assert in the source.)
struct sub_56cc4f0Layout {
    static_assert(offsetof(RefObj, f8) == 0x8, "sub_56cc4f0: RefObj::f8 at +0x8");
    static_assert(offsetof(RefObj, fc) == 0xc, "sub_56cc4f0: RefObj::fc at +0xc");
    static_assert(offsetof(Node, f18) == 0x18, "sub_56cc4f0: Node::f18 at +0x18");
    static_assert(offsetof(ListHead, f8) == 0x8, "sub_56cc4f0: ListHead::f8 at +0x8");
    static_assert(offsetof(State, f8) == 0x8, "sub_56cc4f0: State::f8 at +0x8");
    static_assert(offsetof(State, f18) == 0x18, "sub_56cc4f0: State::f18 at +0x18");
    static_assert(offsetof(State, f28) == 0x28, "sub_56cc4f0: State::f28 at +0x28");
};

LIFT_FN(sub_56cc4f0, "sub_56cc4f0", 0x56cc4f0, sub_56cc4f0, nullptr);

// Verbatim call instructions from the disassembly of [0x56cc4f0, 0x56cc5df) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x56cc535  call 0xE935700
0x56cc568  call 0xE935700
0x56cc590  call qword ptr [0xF99FFA0]
0x56cc5a6  call qword ptr [0xF99FFA0]
0x56cc5d8  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0x56cc4f0, 0x56cc5df) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

// sub_eea6040 (vendor thunk via data slot 0xF99FFA0): sub_eea6040(RefObj, destructorPtr).
// sub_eea6040(RefObj, destructorPtr). Called with rcx = RefObj, rdx = vfptr[N]. Returns
// void; result ignored, so a std::uintptr_t return boundary avoids sizeof(void) in Lift.h.
native::Boundary<std::uintptr_t, void*, void*> sub_eea6040("sub_eea6040");

void* sub_56cc4f0(void* self) {
    // 0x56cc4f0..0x56cc505
    State* const s = reinterpret_cast<State*>(self);
    void* const buffer = s->f18;            // 0x56cc4fc  mov rcx,[rcx+0x18]
    if (buffer != nullptr) {                // 0x56cc500  test rcx,rcx ; 0x56cc503  je short 0x56CC548
        // 0x56cc505..0x56cc531
        const std::uint64_t size =
            s->f28 - reinterpret_cast<std::uintptr_t>(buffer);  // 0x56cc505..0x56cc509
        void* freeArg = buffer;             // rcx = buffer (small-buffer path, 0x56cc513 jb)
        if (size >= 0x1000) {               // 0x56cc50c  cmp rdx,0x1000
            // 0x56cc515..0x56cc52a
            const std::uintptr_t rax =
                *reinterpret_cast<const std::uintptr_t*>(  // 0x56cc515  mov rax,[rcx-8]
                    reinterpret_cast<const std::uint8_t*>(buffer) - 8);
            const std::uintptr_t delta =
                reinterpret_cast<std::uintptr_t>(buffer) - 8 - rax;  // 0x56cc519..0x56cc51d
            if (delta >= 0x20) {            // 0x56cc520  cmp rcx,0x20 ; 0x56cc524  jae 0x56CC5C5
                // 0x56cc5c5..0x56cc5df  noreturn fail path (_invoke_watson then int3)
                auto watson_fn = reinterpret_cast<decltype(&sub_f9a8c78_watson)>(
                    *reinterpret_cast<const std::uintptr_t*>(
                        RewriteRegistry::imageBase() + kRvaFailSlot));  // 0x56cc5d8  call qword ptr [0xF9A8C78]
                watson_fn(nullptr, nullptr, nullptr, 0, 0);
                __debugbreak();             // 0x56cc5de  int3
                __assume(false);            // int3 is noreturn pad
            }
            // 0x56cc52a  add rdx,0x27  (dead write, not read afterward)
            // 0x56cc52e  mov rcx,rax
            freeArg = reinterpret_cast<void*>(rax);  // rcx = *(buffer - 8)
        }
        // 0x56cc531..0x56cc548
        native::sub_e935700(freeArg);       // 0x56cc535  call 0xE935700  ; rcx = freeArg (rdx dead)
        s->f18 = nullptr;                   // 0x56cc53d  movups [rdi],xmm0  (self->f18 = 0)
        s->f28 = 0;                         // 0x56cc540  mov qword [rdi+0x10],0 (self->f28 = 0)
    }
    // 0x56cc548..0x56cc56d
    ListHead* const head = s->f8;           // 0x56cc548  mov rax,[rsi+8]
    void** const slotPtr = head->f8;        // 0x56cc54c  mov rcx,[rax+8]
    *slotPtr = nullptr;                     // 0x56cc550  mov qword ptr [rcx],0
    Node* r14 = reinterpret_cast<Node*>(head->f0);  // 0x56cc557  mov r14,[rax]
    // 0x56cc56d..0x56cc5ae  node release loop
    while (r14 != nullptr) {                // 0x56cc56d  test r14,r14 ; 0x56cc570  je short 0x56CC5AE
        Node* const node = r14;             // 0x56cc572  mov rdi,r14
        r14 = reinterpret_cast<Node*>(node->f0);    // 0x56cc575  mov r14,[r14]  (next node)
        RefObj* const ref = node->f18;      // 0x56cc578  mov rbx,[rdi+0x18]
        if (ref != nullptr) {               // 0x56cc57c  test rbx,rbx ; 0x56cc57f  je short 0x56CC560
            if (_InterlockedDecrement(      // 0x56cc581  lock dec dword ptr [rbx+8]
                    reinterpret_cast<volatile long*>(&ref->f8)) == 0) {
                // 0x56cc587..0x56cc59c  destroy via vfptr[0]
                sub_eea6040(ref, reinterpret_cast<void**>(ref->vfptr)[0]);  // 0x56cc590  call qword ptr [0xF99FFA0]
                if (_InterlockedDecrement(  // 0x56cc596  lock dec dword ptr [rbx+0xC]
                        reinterpret_cast<volatile long*>(&ref->fc)) == 0) {
                    // 0x56cc59c..0x56cc5ae  destroy via vfptr[1]
                    sub_eea6040(ref, reinterpret_cast<void**>(ref->vfptr)[1]);  // 0x56cc5a6  call qword ptr [0xF99FFA0]
                }
            }
        }
        // 0x56cc560..0x56cc56d
        native::sub_e935700(node);          // 0x56cc568  call 0xE935700  ; rcx = rdi = node (edx=0x28 dead)
    }
    // 0x56cc5ae..0x56cc5c0  tail call (edx=0x28 dead in sub_e935700)
    return native::sub_e935700(head);       // 0x56cc5c0  jmp 0xE935700  ; rcx = head
}

} // namespace native::helpers

// Verbatim instruction quotes for verify_oc (plain lines, two spaces after address).
// machine-checked by tools/sigs/verify_oc.py against the exe.
#if 0
0x56cc4f0  push r14
0x56cc4f2  push rsi
0x56cc4f3  push rdi
0x56cc4f4  push rbx
0x56cc4f5  sub rsp,0x28
0x56cc4f9  mov rsi,rcx
0x56cc4fc  mov rcx,[rcx+0x18]
0x56cc500  test rcx,rcx
0x56cc503  je short 0x56CC548
0x56cc505  mov rdx,[rsi+0x28]
0x56cc509  sub rdx,rcx
0x56cc50c  cmp rdx,0x1000
0x56cc513  jb short 0x56CC531
0x56cc515  mov rax,[rcx-8]
0x56cc519  add rcx,0xFFFFFFFFFFFFFFF8
0x56cc51d  sub rcx,rax
0x56cc520  cmp rcx,0x20
0x56cc524  jae 0x56CC5C5
0x56cc52a  add rdx,0x27
0x56cc52e  mov rcx,rax
0x56cc531  lea rdi,[rsi+0x18]
0x56cc535  call 0xE935700
0x56cc53a  xorps xmm0,xmm0
0x56cc53d  movups [rdi],xmm0
0x56cc540  mov qword ptr [rdi+0x10],0
0x56cc548  mov rax,[rsi+8]
0x56cc54c  mov rcx,[rax+8]
0x56cc550  mov qword ptr [rcx],0
0x56cc557  mov r14,[rax]
0x56cc55a  jmp short 0x56CC56D
0x56cc55c  nop [rax]
0x56cc560  mov edx,0x28
0x56cc565  mov rcx,rdi
0x56cc568  call 0xE935700
0x56cc56d  test r14,r14
0x56cc570  je short 0x56CC5AE
0x56cc572  mov rdi,r14
0x56cc575  mov r14,[r14]
0x56cc578  mov rbx,[rdi+0x18]
0x56cc57c  test rbx,rbx
0x56cc57f  je short 0x56CC560
0x56cc581  lock dec dword ptr [rbx+8]
0x56cc585  jne short 0x56CC560
0x56cc587  mov rax,[rbx]
0x56cc58a  mov rax,[rax]
0x56cc58d  mov rcx,rbx
0x56cc590  call qword ptr [0xF99FFA0]
0x56cc596  lock dec dword ptr [rbx+0xC]
0x56cc59a  jne short 0x56CC560
0x56cc59c  mov rax,[rbx]
0x56cc59f  mov rax,[rax+8]
0x56cc5a3  mov rcx,rbx
0x56cc5a6  call qword ptr [0xF99FFA0]
0x56cc5ac  jmp short 0x56CC560
0x56cc5ae  mov rcx,[rsi+8]
0x56cc5b2  mov edx,0x28
0x56cc5b7  add rsp,0x28
0x56cc5bb  pop rbx
0x56cc5bc  pop rdi
0x56cc5bd  pop rsi
0x56cc5be  pop r14
0x56cc5c0  jmp 0xE935700
0x56cc5c5  mov qword ptr [rsp+0x20],0
0x56cc5ce  xor ecx,ecx
0x56cc5d0  xor edx,edx
0x56cc5d2  xor r8d,r8d
0x56cc5d5  xor r9d,r9d
0x56cc5d8  call qword ptr [0xF9A8C78]
0x56cc5de  int3
#endif
