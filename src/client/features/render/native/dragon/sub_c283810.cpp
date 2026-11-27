// LIFT 0xc283810 size 0x8b 1.26.62.01 Frame renderer lambda
#include "client/features/render/native/dragon/sub_c283810.h"

#include "client/features/render/native/Lift.h"

#include <cstddef>
#include <cstdint>
#include <intrin.h>

// Layout assertions (duplicated from header for liftcheck)
static_assert(offsetof(native::RenderNode, nextSibling) == 0x00, "c283810: RenderNode::nextSibling at +0x00");
static_assert(offsetof(native::RenderNode, child) == 0x10, "c283810: RenderNode::child at +0x10");
static_assert(offsetof(native::RenderNode, renderFlag) == 0x19, "c283810: RenderNode::renderFlag at +0x19");
static_assert(offsetof(native::RenderNode, refCount) == 0x30, "c283810: RenderNode::refCount at +0x30");
static_assert(offsetof(native::RenderNode, type) == 0x38, "c283810: RenderNode::type at +0x38");
static_assert(offsetof(native::RefCountBase, vtable) == 0x00, "c283810: RefCountBase::vtable at +0x00");
static_assert(offsetof(native::RefCountBase, strong) == 0x08, "c283810: RefCountBase::strong at +0x08");
static_assert(offsetof(native::RefCountBase, weak) == 0x0C, "c283810: RefCountBase::weak at +0x0C");
static_assert(sizeof(void*) == 8, "c283810: x64 ABI, pointer-sized address space");

namespace native {

void sub_c283810(RenderNode* node) {
    // 0xc283810..0xc283823: push rsi; push rdi; sub rsp,0x28;
    //   cmp byte ptr [rcx+0x19],0 ; je short 0xC283823
    //   renderFlag != 0 -> return via epilogue at 0xc28381c.
    if (node->renderFlag != 0) {
        return;   // 0xc28381c  add rsp,0x28 ; pop rdi ; pop rsi ; ret
    }

    // 0xc283823..0xc283830: mov rsi,rcx ; jmp short 0xC283836
    RenderNode* cur = node;

    for (;;) {
        // 0xc283836..0xc28383d: mov rdi,rsi ; mov rcx,[rsi+0x10] ; call 0xC283810
        RenderNode* thisNode = cur;
        sub_c283810(thisNode->child);   // 0xc28383d  call 0xC283810  (rcx = child)

        // 0xc283842..0xc283860: mov rsi,[rsi] ; movzx eax,byte ptr [rdi+0x38] ; cmp eax,1 ; jg short 0xC283860
        cur = thisNode->nextSibling;     // 0xc283842  mov rsi,[rsi]
        std::uint8_t type = thisNode->type;   // 0xc283845  movzx eax,byte ptr [rdi+0x38]

        // 0xc283860..0xc283865: cmp eax,2 ; jne short 0xC283830
        //   type > 2: skip release, go to loop check
        //   type <= 2: fall through to release
        if (type <= 2) {
            // 0xc283865..0xc28386c: mov rdi,[rdi+0x30] ; test rdi,rdi ; je short 0xC283830
            RefCountBase* rc = thisNode->refCount;  // 0xc283865  mov rdi,[rdi+0x30]
            if (rc != 0) {
                // 0xc28386e..0xc283872: lock dec dword ptr [rdi+8] ; jne short 0xC283830
                if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rc->strong)) == 0) {
                    // 0xc283874..0xc28387d: mov rax,[rdi] ; mov rax,[rax] ; mov rcx,rdi
                    //   call qword ptr [0xF99FFA0] (sub_eea6040 -> vtable[0] = destructor)
                    sub_eea6040(rc);   // 0xc28387d  call qword ptr [0xF99FFA0]

                    // 0xc283883..0xc283887: lock dec dword ptr [rdi+0xC] ; jne short 0xC283830
                    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&rc->weak)) == 0) {
                        // 0xc283889..0xc283893: mov rax,[rdi] ; mov rax,[rax+8] ; mov rcx,rdi
                        //   call qword ptr [0xF99FFA0] (sub_eea6040 -> vtable[1] = deallocator)
                        sub_eea6040(rc);   // 0xc283893  call qword ptr [0xF99FFA0]
                    }
                }
            }
        }

        // 0xc283830..0xc283834: cmp byte ptr [rsi+0x19],0 ; jne short 0xC28381C
        if (cur->renderFlag != 0) {
            return;   // 0xc28381c  add rsp,0x28 ; pop rdi ; pop rsi ; ret
        }
        // fall through: 0xc283836 processes cur again
    }
}

LIFT_FN(c283810, "sub_c283810", 0xC283810, sub_c283810, nullptr);

} // namespace native

// Verbatim instructions of the function (rdis dis 0xc283810 0x8b), for
// liftcheck/verify_oc. Every line matches rdis output for its address.
#if 0
0xC283810  push rsi
0xC283811  push rdi
0xC283812  sub rsp,0x28
0xC283816  cmp byte ptr [rcx+0x19],0
0xC28381A  je short 0xC283823
0xC28381C  add rsp,0x28
0xC283820  pop rdi
0xC283821  pop rsi
0xC283822  ret
0xC283823  mov rsi,rcx
0xC283826  jmp short 0xC283836
0xC283828  nop [rax+rax]
0xC283830  cmp byte ptr [rsi+0x19],0
0xC283834  jne short 0xC28381C
0xC283836  mov rdi,rsi
0xC283839  mov rcx,[rsi+0x10]
0xC28383D  call 0xC283810
0xC283842  mov rsi,[rsi]
0xC283845  movzx eax,byte ptr [rdi+0x38]
0xC283849  cmp eax,1
0xC28384C  jg short 0xC283860
0xC28384E  test eax,eax
0xC283850  jmp short 0xC283865
0xC283852  nop [rax+rax]
0xC283860  cmp eax,2
0xC283863  jne short 0xC283830
0xC283865  mov rdi,[rdi+0x30]
0xC283869  test rdi,rdi
0xC28386C  je short 0xC283830
0xC28386E  lock dec dword ptr [rdi+8]
0xC283872  jne short 0xC283830
0xC283874  mov rax,[rdi]
0xC283877  mov rax,[rax]
0xC28387A  mov rcx,rdi
0xC28387D  call qword ptr [0xF99FFA0]
0xC283883  lock dec dword ptr [rdi+0xC]
0xC283887  jne short 0xC283830
0xC283889  mov rax,[rdi]
0xC28388C  mov rax,[rax+8]
0xC283890  mov rcx,rdi
0xC283893  call qword ptr [0xF99FFA0]
0xC283899  jmp short 0xC283830
#endif
