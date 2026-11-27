// LIFT 0xc27ebd0 size 0x8b 1.26.62.01 Frame renderer lambda
#include "client/features/render/native/dragon/sub_c27ebd0.h"

#include "client/features/render/native/Lift.h"

#include <atomic>
#include <cstddef>
#include <cstdint>

// Layout assertions (duplicated from header for liftcheck)
static_assert(offsetof(native::RefCountBase, vtable) == 0x00, "c27ebd0: RefCountBase::vtable at +0x00");
static_assert(offsetof(native::RefCountBase, strong) == 0x08, "c27ebd0: RefCountBase::strong at +0x08");
static_assert(offsetof(native::RefCountBase, weak) == 0x0C, "c27ebd0: RefCountBase::weak at +0x0C");
static_assert(sizeof(native::RefCountBase) == 0x10, "c27ebd0: RefCountBase size 0x10");
static_assert(offsetof(native::FrameRendererNode, next) == 0x00, "c27ebd0: FrameRendererNode::next at +0x00");
static_assert(offsetof(native::FrameRendererNode, recursiveArg) == 0x10, "c27ebd0: FrameRendererNode::recursiveArg at +0x10");
static_assert(offsetof(native::FrameRendererNode, flag) == 0x19, "c27ebd0: FrameRendererNode::flag at +0x19");
static_assert(offsetof(native::FrameRendererNode, refCountedObject) == 0x48, "c27ebd0: FrameRendererNode::refCountedObject at +0x48");
static_assert(offsetof(native::FrameRendererNode, type) == 0x50, "c27ebd0: FrameRendererNode::type at +0x50");

namespace native {

// Forward declaration for the vendor thunk at data slot 0xF99FFA0 -> sub_eea6040.
// Called with rcx = RefCountBase*; the thunk is a `jmp rax` forwarder where RAX
// holds the vtable entry (vtable[0] = destructor, vtable[8] = deallocator).
// Return value ignored.
void sub_eea6040(RefCountBase* obj);

// Recursive self-call.
void sub_c27ebd0(FrameRendererNode* node);

void sub_c27ebd0(FrameRendererNode* node) {
    // 0xc27ebd0..0xc27ebdb: push rsi; push rdi; push rbx; sub rsp,0x20
    // 0xc27ebd7  cmp byte ptr [rcx+0x19],0
    // 0xc27ebdb  je short 0xC27EBE5
    if (node->flag != 0) {
        // 0xc27ebdd..0xc27ebe5: add rsp,0x20; pop rbx; pop rdi; pop rsi; ret
        return;
    }

    // 0xc27ebe5  mov rsi,rcx
    // 0xc27ebe8  jmp short 0xC27EC03
    // 0xc27ebea  nop [rax+rax]
    FrameRendererNode* current = node;

    while (true) {
        // 0xc27ec03  mov rdi,rsi
        FrameRendererNode* prev = current;

        // 0xc27ec06  mov rcx,[rsi+0x10]
        // 0xc27ec0a  call 0xC27EBD0
        // Recursive call with recursiveArg
        sub_c27ebd0(static_cast<FrameRendererNode*>(prev->recursiveArg));

        // 0xc27ec0f  mov rsi,[rsi]
        // Move to next node
        current = prev->next;

        // 0xc27ec12  movzx eax,byte ptr [rdi+0x50]
        // 0xc27ec16  cmp eax,1
        // 0xc27ec19  jg short 0xC27EC20
        // 0xc27ec1b  test eax,eax
        // 0xc27ec1d  jmp short 0xC27EC25
        // 0xc27ec1f  nop
        std::uint8_t type = prev->type;
        bool doRefcount = (type <= 1) || (type == 2);
        // type 0 or 1 or 2: do refcount handling
        // type >= 3: skip refcount handling, go straight to sub_e935700

        if (doRefcount) {
            // 0xc27ec25  mov rbx,[rdi+0x48]
            // 0xc27ec29  test rbx,rbx
            // 0xc27ec2c  je short 0xC27EBF0
            RefCountBase* obj = prev->refCountedObject;
            if (obj != nullptr) {
                // 0xc27ec2e  lock dec dword ptr [rbx+8]
                // 0xc27ec32  jne short 0xC27EBF0
                std::atomic<std::int32_t>* strongAtomic =
                    reinterpret_cast<std::atomic<std::int32_t>*>(&obj->strong);
                if (strongAtomic->fetch_sub(1, std::memory_order_acq_rel) == 1) {
                    // 0xc27ec34  mov rax,[rbx]
                    // 0xc27ec37  mov rax,[rax]
                    // 0xc27ec3a  mov rcx,rbx
                    // 0xc27ec3d  call qword ptr [0xF99FFA0]
                    // Call destructor via vtable[0] through vendor thunk
                    sub_eea6040(obj);
                }

                // 0xc27ec43  lock dec dword ptr [rbx+c]
                // 0xc27ec47  jne short 0xC27EBF0
                std::atomic<std::int32_t>* weakAtomic =
                    reinterpret_cast<std::atomic<std::int32_t>*>(&obj->weak);
                if (weakAtomic->fetch_sub(1, std::memory_order_acq_rel) == 1) {
                    // 0xc27ec49  mov rax,[rbx]
                    // 0xc27ec4c  mov rax,[rax+8]
                    // 0xc27ec50  mov rcx,rbx
                    // 0xc27ec53  call qword ptr [0xF99FFA0]
                    // Call deallocator via vtable[8] through vendor thunk
                    sub_eea6040(obj);
                }
            }
        }

        // 0xc27ebf0  mov edx,0x58
        // 0xc27ebf5  mov rcx,rdi
        // 0xc27ebf8  call 0xE935700
        sub_e935700(prev, 0x58u);

        // 0xc27ebfd  cmp byte ptr [rsi+0x19],0
        // 0xc27ec01  jne short 0xC27EBDD
        if (current->flag != 0) {
            // 0xc27ebdd..0xc27ebe5: add rsp,0x20; pop rbx; pop rdi; pop rsi; ret
            return;
        }

        // 0xc27ec03: loop back
    }
}

// Registry entry: ID=c27ebd0, NAME="sub_c27ebd0", RVA=0xC27EBD0
LIFT_FN(c27ebd0, "sub_c27ebd0", 0xC27EBD0, sub_c27ebd0, nullptr);

} // namespace native

// Verbatim instructions of the function (rdis dis 0xc27ebd0 0x8b), for liftcheck
// verify_oc. Every line matches rdis output for its address.
#if 0
0xC27EBD0  push rsi
0xC27EBD1  push rdi
0xC27EBD2  push rbx
0xC27EBD3  sub rsp,0x20
0xC27EBD7  cmp byte ptr [rcx+0x19],0
0xC27EBDB  je short 0xC27EBE5
0xC27EBDD  add rsp,0x20
0xC27EBE1  pop rbx
0xC27EBE2  pop rdi
0xC27EBE3  pop rsi
0xC27EBE4  ret
0xC27EBE5  mov rsi,rcx
0xC27EBE8  jmp short 0xC27EC03
0xC27EBEA  nop [rax+rax]
0xC27EBF0  mov edx,0x58
0xC27EBF5  mov rcx,rdi
0xC27EBF8  call 0xE935700
0xC27EBFD  cmp byte ptr [rsi+0x19],0
0xC27EC01  jne short 0xC27EBDD
0xC27EC03  mov rdi,rsi
0xC27EC06  mov rcx,[rsi+0x10]
0xC27EC0A  call 0xC27EBD0
0xC27EC0F  mov rsi,[rsi]
0xC27EC12  movzx eax,byte ptr [rdi+0x50]
0xC27EC16  cmp eax,1
0xC27EC19  jg short 0xC27EC20
0xC27EC1B  test eax,eax
0xC27EC1D  jmp short 0xC27EC25
0xC27EC1F  nop
0xC27EC20  cmp eax,2
0xC27EC23  jne short 0xC27EBF0
0xC27EC25  mov rbx,[rdi+0x48]
0xC27EC29  test rbx,rbx
0xC27EC2C  je short 0xC27EBF0
0xC27EC2E  lock dec dword ptr [rbx+8]
0xC27EC32  jne short 0xC27EBF0
0xC27EC34  mov rax,[rbx]
0xC27EC37  mov rax,[rax]
0xC27EC3A  mov rcx,rbx
0xC27EC3D  call qword ptr [0xF99FFA0]
0xC27EC43  lock dec dword ptr [rbx+c]
0xC27EC47  jne short 0xC27EBF0
0xC27EC49  mov rax,[rbx]
0xC27EC4C  mov rax,[rax+8]
0xC27EC50  mov rcx,rbx
0xC27EC53  call qword ptr [0xF99FFA0]
0xC27EC59  jmp short 0xC27EBF0
#endif