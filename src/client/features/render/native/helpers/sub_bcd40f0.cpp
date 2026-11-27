// LIFT 0xbcd40f0 size 0xc3 1.26.62.01 sub_bcd40f0
#include "sub_bcd40f0.h"
#include "client/features/render/native/Lift.h"

namespace native {

// Verbatim instruction quotes for liftcheck verification (plain lines inside #if 0).
// Every instruction in [0xbcd40f0, 0xbcd41b3) is covered by the cited ranges below.
#if 0
0xbcd40f0  push rsi
0xbcd40f1  push rdi
0xbcd40f2  push rbx
0xbcd40f3  sub rsp,0x30
0xbcd40f7  mov rsi,rcx
0xbcd40fa  mov rax,[rcx]
0xbcd40fd  mov rcx,[rax+8]
0xbcd4101  mov qword ptr [rcx],0
0xbcd4108  mov rdi,[rax]
0xbcd410b  test rdi,rdi
0xbcd410e  jne short 0xBCD415E
0xbcd4110  mov rcx,[rsi]
0xbcd4113  mov edx,0x80
0xbcd4118  add rsp,0x30
0xbcd411c  pop rbx
0xbcd411d  pop rdi
0xbcd411e  pop rsi
0xbcd411f  jmp 0xE935700
0xbcd4130  call 0xE935700
0xbcd4135  mov qword ptr [rdi+0x20],0
0xbcd413d  mov qword ptr [rdi+0x28],0xF
0xbcd4145  mov byte ptr [rdi+0x10],0
0xbcd4149  mov edx,0x80
0xbcd414e  mov rcx,rdi
0xbcd4151  call 0xE935700
0xbcd4156  mov rdi,rbx
0xbcd4159  test rbx,rbx
0xbcd415c  je short 0xBCD4110
0xbcd415e  mov rbx,[rdi]
0xbcd4161  mov rax,[rdi+0x28]
0xbcd4165  cmp rax,0x10
0xbcd4169  jb short 0xBCD4135
0xbcd416b  mov rcx,[rdi+0x10]
0xbcd416f  lea rdx,[rax+1]
0xbcd4173  cmp rdx,0x1000
0xbcd417a  jb short 0xBCD4130
0xbcd417c  mov r8,[rcx-8]
0xbcd4180  add rcx,0xFFFFFFFFFFFFFFF8
0xbcd4184  sub rcx,r8
0xbcd4187  cmp rcx,0x20
0xbcd418b  jae short 0xBCD4199
0xbcd418d  add rax,0x28
0xbcd4191  mov rdx,rax
0xbcd4194  mov rcx,r8
0xbcd4197  jmp short 0xBCD4130
0xbcd4199  mov qword ptr [rsp+0x20],0
0xbcd41a2  xor ecx,ecx
0xbcd41a4  xor edx,edx
0xbcd41a6  xor r8d,r8d
0xbcd41a9  xor r9d,r9d
0xbcd41ac  call qword ptr [0xF9A8C78]
0xbcd41b2  int3
0xbcd41b3  int3
#endif

// sub_bcd40f0 (0xbcd40f0, size 0xc3, 1.26.62.01).
// String list destructor / cleanup.
//   rcx = thisPtr (StringListHead*).
// Iterates the linked list of nodes, cleaning each:
//   - SSO nodes (capacity < 0x10): zero size, set capacity=0xF, null-terminate inline buffer, call sub_e935700(node).
//   - Heap nodes (capacity >= 0x10): deallocate heap buffer via sub_e935700(data_ptr) or sub_e935700(alloc_header).
// After all nodes, tail-calls sub_e935700(head).
// On heap header corruption (header size >= 0x20), calls abort handler at data slot 0xF9A8C78 (noreturn).
void* sub_bcd40f0(void* thisPtr) noexcept {
    // 0xbcd40f0..0xbcd410e: prologue, load head and first node, zero head->field8.
    auto* head = reinterpret_cast<StringListHead*>(thisPtr);
    auto* headFirst = *reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(head) + StringListHead::kFirstOffset);  // 0xbcd40fa  mov rax,[rcx]
    auto* field8Ptr = *reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(headFirst) + StringListHead::kField8Offset);  // 0xbcd40fd  mov rcx,[rax+8]
    *reinterpret_cast<std::uint64_t*>(field8Ptr) = 0;  // 0xbcd4101  mov qword ptr [rcx],0
    auto* node = *reinterpret_cast<void**>(headFirst);  // 0xbcd4108  mov rdi,[rax]  (first node)
    if (node == nullptr) {  // 0xbcd410b  test rdi,rdi / 0xbcd410e  jne short 0xBCD415E
        // 0xbcd4110..0xbcd411f: empty list -> tail call sub_e935700(head, 0x80).
        // 0xbcd4110  mov rcx,[rsi]  (rcx = head)
        // 0xbcd4113  mov edx,0x80   (rdx = 0x80, ignored by callee)
        // 0xbcd4118..0xbcd411f  epilogue + jmp 0xE935700
        // 0xbcd411f  jmp 0xE935700
        return sub_e935700(head);  // RCX = head; RDX=0x80 is dead (callee overwrites it)
    }

    // 0xbcd411f..0xbcd4130: unreachable padding after tail call (nop [rax+rax] at 0xbcd4124).
    // 0xbcd415e..0xbcd41b3: non-empty list, iterate nodes.
    // Registers: rdi = current node, rbx = next node (loaded at top of loop).
    while (true) {
        // 0xbcd415e  mov rbx,[rdi]  (rbx = node->next)
        auto* nextNode = *reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(node) + StringListNode::kNextOffset);
        // 0xbcd4161  mov rax,[rdi+0x28]  (rax = node->capacity)
        std::uint64_t capacity = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uintptr_t>(node) + StringListNode::kCapacityOffset);

        if (capacity < StringListNode::kSsoCapacityThreshold) {  // 0xbcd4165  cmp rax,0x10 / 0xbcd4169  jb short 0xBCD4135
            // SSO node: 0xbcd4135..0xbcd4155
            // 0xbcd4135  mov qword ptr [rdi+0x20],0  (size = 0)
            *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uintptr_t>(node) + StringListNode::kSizeOffset) = 0;
            // 0xbcd413d  mov qword ptr [rdi+0x28],0xF  (capacity = 0xF)
            *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uintptr_t>(node) + StringListNode::kCapacityOffset) = StringListNode::kSsoCapacityValue;
            // 0xbcd4145  mov byte ptr [rdi+0x10],0  (null-terminate inline buffer)
            *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(node) + StringListNode::kDataOffset) = 0;
            // 0xbcd4149  mov edx,0x80 / 0xbcd414e  mov rcx,rdi / 0xbcd4151  call 0xE935700
            // 0xbcd4151  call 0xE935700
            sub_e935700(node);  // RCX = node; RDX=0x80 dead
        } else {
            // Heap node: 0xbcd416b..0xbcd4197
            // 0xbcd416b  mov rcx,[rdi+0x10]  (rcx = node->heapData)
            auto* heapData = *reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(node) + StringListNode::kDataOffset);
            // 0xbcd416f  lea rdx,[rax+1]  (rdx = capacity + 1)
            std::uint64_t capPlus1 = capacity + 1;
            if (capPlus1 < StringListNode::kLargeAllocThreshold) {  // 0xbcd4173  cmp rdx,0x1000 / 0xbcd417a  jb short 0xBCD4130
                // Small heap allocation: direct deallocate data pointer.
                // 0xbcd4130  call 0xE935700  (RCX = heapData from 0xbcd416b)
                // 0xbcd4130  call 0xE935700
                sub_e935700(heapData);
            } else {
                // Large allocation: 0xbcd417c..0xbcd4197
                // 0xbcd417c  mov r8,[rcx-8]  (r8 = alloc header at heapData - 8)
                auto* allocHeader = *reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(heapData) - 8);
                // 0xbcd4180  add rcx,0xFFFFFFFFFFFFFFF8  (rcx = heapData - 8)
                // 0xbcd4184  sub rcx,r8  (rcx = (heapData - 8) - allocHeader = allocation size)
                std::uintptr_t allocSize = (reinterpret_cast<std::uintptr_t>(heapData) - 8) - reinterpret_cast<std::uintptr_t>(allocHeader);
                if (allocSize >= StringListNode::kAllocHeaderMinSize) {  // 0xbcd4187  cmp rcx,0x20 / 0xbcd418b  jae short 0xBCD4199
                    // Corruption: header size >= 0x20 -> abort.
                    // 0xbcd4199..0xbcd41ac: call abort handler at [0xF9A8C78] with zero args.
                    // 0xbcd4199  mov qword ptr [rsp+0x20],0
                    // 0xbcd41a2  xor ecx,ecx
                    // 0xbcd41a4  xor edx,edx
                    // 0xbcd41a6  xor r8d,r8d
                    // 0xbcd41a9  xor r9d,r9d
                    // 0xbcd41ac  call qword ptr [0xF9A8C78]
                    auto abortHandler = *reinterpret_cast<AbortHandlerFn*>(0xF9A8C78ULL);
                    abortHandler(0, 0, 0, 0, 0);  // noreturn
                    __assume(false);
                }
                // 0xbcd418d  add rax,0x28  (rax = capacity + 0x28)
                // 0xbcd4191  mov rdx,rax  (rdx = capacity + 0x28)
                // 0xbcd4194  mov rcx,r8  (rcx = allocHeader)
                // 0xbcd4197  jmp short 0xBCD4130  -> call sub_e935700(allocHeader)
                // 0xbcd4130  call 0xE935700
                sub_e935700(allocHeader);
            }
        }

        // 0xbcd4156  mov rdi,rbx  (node = nextNode)
        // 0xbcd4159  test rbx,rbx / 0xbcd415c  je short 0xBCD4110
        node = nextNode;
        if (node == nullptr) {
            // End of list: tail call sub_e935700(head).
            // 0xbcd4110  mov rcx,[rsi]  (rcx = head)
            // 0xbcd4113  mov edx,0x80
            // 0xbcd4118..0xbcd411f  epilogue + jmp 0xE935700
            // 0xbcd411f  jmp 0xE935700
            return sub_e935700(head);
        }
        // Loop continues with next node.
    }
}

} // namespace native

LIFT_FN(sub_bcd40f0, "sub_bcd40f0", 0xBCD40F0, native::sub_bcd40f0, nullptr);