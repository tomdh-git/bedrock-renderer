// LIFT 0xae500 size 0x10a 1.26.62.01 sub_ae500
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_ae500.h"

#include <cstddef>
#include <cstdint>

namespace native::helpers {

LIFT_FN(sub_ae500, "sub_ae500", 0xae500, sub_ae500, nullptr);

// Verbatim call instructions from the disassembly of [0xae500, 0xae60a) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xae59c  call 0xAE610
0xae5a9  call 0xAE770
0xae5d6  call 0xAE770
0xae5fd  call 0xAE610
#endif

// Layout assertions repeated here so the layout check finds them in this unit.
static_assert(offsetof(sub_ae500_node, link) == 0x8, "sub_ae500 node+0x8 link field");
static_assert(offsetof(sub_ae500_node, seqEnd) == 0x20, "sub_ae500 node+0x20 seqEnd field");
static_assert(offsetof(sub_ae500_node, seqStart) == 0x28, "sub_ae500 node+0x28 seqStart field");
static_assert(offsetof(sub_ae500_node, mode48) == 0x48, "sub_ae500 node+0x48 mode48 field");
static_assert(offsetof(sub_ae500_head, node) == 0x0, "sub_ae500 head+0x0 node field");

// sub_ae500(head, context):
//   The first walk starts at *head and follows node->link at +0x08 (raw value; a
//   nonzero raw link encodes the next node as raw - 8). For every node it computes
//   delta = max(0, node->seqEnd - node->seqStart) with the exe's unsigned wrap test,
//   counts the nodes whose delta is nonzero and remembers the node with the largest
//   delta (the earlier node wins a tie). The walk ends at the list end or after three
//   nonzero-delta nodes were seen.
//   No nonzero delta -> return false. Otherwise the remembered node is passed to
//   sub_ae610 when node->mode48 == 1 and to sub_ae770 otherwise; a true result returns
//   true at once. After that the head is re-read and every other node of the list gets
//   the same call in list order, skipping the remembered node; the first true result
//   returns true. Running off the list returns false.
//   The body takes no locks; the two callees own any synchronisation.

bool sub_ae500(sub_ae500_head* head, void* context) {
    // 0xae500..0xae519: basic block 0, prologue and head load
    // 0xae500  push r15
    // 0xae502  push r14
    // 0xae504  push r12
    // 0xae506  push rsi
    // 0xae507  push rdi
    // 0xae508  push rbx
    // 0xae509  sub rsp,0x28
    // 0xae50d  mov rax,[rcx]
    sub_ae500_node* node = head->node;
    // 0xae510  test rax,rax
    // 0xae513  je 0xAE5BE
    if (node == nullptr) {
        // 0xae5be  xor eax,eax
        return false;   // loc_ae5be
    }

    // 0xae519..0xae530: basic block 1, walk state initialisation
    // 0xae519  mov rsi,rdx
    void* const ctx = context;
    // 0xae51c  xor edx,edx
    // 0xae51e  mov r8,0x8000000000000000
    const std::uint64_t kHalf = 0x8000000000000000ull;
    // 0xae528  xor r9d,r9d
    std::uint64_t bestDelta = 0;
    // 0xae52b  xor edi,edi
    sub_ae500_node* bestNode = nullptr;
    // 0xae52d  xor r10d,r10d
    std::uint64_t hotCount = 0;

    for (;;) {
        // 0xae530..0xae582: basic block 2, examine one node
        // 0xae530  mov r11,r10
        // 0xae533  mov rbx,rdi
        // 0xae536  mov r14,r9
        const std::uint64_t prevCount = hotCount;
        sub_ae500_node* const prevBestNode = bestNode;
        const std::uint64_t prevBestDelta = bestDelta;
        // 0xae539  mov r15,[rax+0x20]
        const std::uint64_t end = node->seqEnd;
        // 0xae53d  mov r10,[rax+0x28]
        const std::uint64_t start = node->seqStart;
        // 0xae541  mov r12,r10
        // 0xae544  sub r12,r15
        const std::uint64_t reverse = start - end;
        // 0xae547  sub r15,r10
        std::uint64_t delta = end - start;
        // 0xae54a  cmp r12,r8
        // 0xae54d  cmovbe r15,rdx
        if (reverse <= kHalf) {
            delta = 0;
        }
        // 0xae551  cmp r15,r9
        // 0xae554  cmova r9,r15
        // 0xae558  cmova rdi,rax
        if (delta > bestDelta) {
            bestDelta = delta;
            bestNode = node;
        }
        // 0xae55c  xor r10d,r10d
        // 0xae55f  test r15,r15
        // 0xae562  setne r10b
        // 0xae566  cmove rdi,rbx
        // 0xae56a  cmove r9,r14
        if (delta == 0) {
            bestNode = prevBestNode;
            bestDelta = prevBestDelta;
        }
        // 0xae56e  add r10,r11
        hotCount = prevCount + (delta != 0 ? 1u : 0u);
        // 0xae571  mov r11,[rax+8]
        const std::uint64_t link = node->link;
        // 0xae575  lea rax,[r11-8]
        // 0xae579  test r11,r11
        // 0xae57c  cmove rax,r11
        sub_ae500_node* const next =
            link != 0 ? reinterpret_cast<sub_ae500_node*>(link - 8) : nullptr;
        // 0xae580  je short 0xAE588
        if (link == 0) {
            break;   // loc_ae588
        }

        // 0xae582..0xae588: basic block 3, walk continuation test
        // 0xae582  cmp r10,3
        // 0xae586  jb short 0xAE530
        if (hotCount >= 3u) {
            break;   // loc_ae588
        }
        node = next;
    }

    // 0xae588..0xae58d: basic block 4, nothing counted
    // 0xae588  test r10,r10
    // 0xae58b  je short 0xAE5BE
    if (hotCount == 0) {
        // 0xae5be  xor eax,eax
        return false;   // loc_ae5be
    }

    // 0xae58d..0xae596: basic block 5, dispatch on the remembered node
    // 0xae58d  mov rbx,rcx
    // 0xae590  cmp byte ptr [rdi+0x48],1
    // 0xae594  jne short 0xAE5A3
    bool hit;
    if (bestNode->mode48 == 1) {
        // 0xae596..0xae5a3: basic block 6
        // 0xae596  mov rcx,rdi
        // 0xae599  mov rdx,rsi
        // 0xae59c  call 0xAE610
        // 0xae5a1  jmp short 0xAE5AE
        hit = sub_ae610(bestNode, ctx);
    } else {
        // 0xae5a3..0xae5ae: basic block 7
        // 0xae5a3  mov rcx,rdi
        // 0xae5a6  mov rdx,rsi
        // 0xae5a9  call 0xAE770
        hit = sub_ae770(bestNode, ctx);
    }

    // 0xae5ae..0xae5b6: basic block 8, result of the remembered-node call
    // 0xae5ae  mov ecx,eax
    // 0xae5b0  mov al,1
    // 0xae5b2  test cl,cl
    // 0xae5b4  jne short 0xAE5C0
    if (hit) {
        return true;   // loc_ae5c0
    }

    // 0xae5b6..0xae5be: basic block 9, re-read the head
    // 0xae5b6  mov rbx,[rbx]
    // 0xae5b9  test rbx,rbx
    // 0xae5bc  jne short 0xAE5EC
    node = head->node;
    if (node == nullptr) {
        // 0xae5be  xor eax,eax
        return false;   // loc_ae5be
    }

    // 0xae5c0..0xae5ce: basic block 11, epilogue shared by every return above
    // 0xae5c0  add rsp,0x28
    // 0xae5c4  pop rbx
    // 0xae5c5  pop rdi
    // 0xae5c6  pop rsi
    // 0xae5c7  pop r12
    // 0xae5c9  pop r14
    // 0xae5cb  pop r15
    // 0xae5cd  ret

    // 0xae5ce..0xae5d0: basic block 12, two-byte alignment padding
    // 0xae5ce  xchg ax,ax
    // Not executed; control reaches the second walk at 0xae5ec.

    for (;;) {
        // 0xae5ec..0xae5f1: basic block 15, skip the remembered node
        // 0xae5ec  cmp rbx,rdi
        // 0xae5ef  je short 0xAE5DF
        if (node != bestNode) {
            // 0xae5f1..0xae5f7: basic block 16, dispatch on this node
            // 0xae5f1  cmp byte ptr [rbx+0x48],1
            // 0xae5f5  jne short 0xAE5D0
            if (node->mode48 == 1) {
                // 0xae5f7..0xae606: basic block 17
                // 0xae5f7  mov rcx,rbx
                // 0xae5fa  mov rdx,rsi
                // 0xae5fd  call 0xAE610
                // 0xae602  test al,al
                // 0xae604  je short 0xAE5DF
                if (sub_ae610(node, ctx)) {
                    // 0xae606..0xae60a: basic block 18
                    // 0xae606  mov al,1
                    // 0xae608  jmp short 0xAE5C0
                    return true;   // loc_ae5c0
                }
            } else {
                // 0xae5d0..0xae5df: basic block 13
                // 0xae5d0  mov rcx,rbx
                // 0xae5d3  mov rdx,rsi
                // 0xae5d6  call 0xAE770
                // 0xae5db  test al,al
                // 0xae5dd  jne short 0xAE606
                if (sub_ae770(node, ctx)) {
                    // 0xae606..0xae60a: basic block 18
                    // 0xae606  mov al,1
                    // 0xae608  jmp short 0xAE5C0
                    return true;   // loc_ae5c0
                }
            }
        }

        // 0xae5df..0xae5ec: basic block 14, advance to the encoded next node
        // 0xae5df  mov rax,[rbx+8]
        // 0xae5e3  lea rbx,[rax-8]
        // 0xae5e7  test rax,rax
        // 0xae5ea  je short 0xAE5BE
        const std::uint64_t link = node->link;
        node = link != 0 ? reinterpret_cast<sub_ae500_node*>(link - 8) : nullptr;
        if (link == 0) {
            // 0xae5be  xor eax,eax
            return false;   // loc_ae5be
        }
    }
}

} // namespace native::helpers
