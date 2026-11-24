// LIFT 0xe87b920 size 0x1e0 1.26.62.01 sub_e87b920
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e87b920.h"

#include <cstddef>
#include <cstdint>

static_assert(sizeof(void*) == 8, "ptr");

// Verbatim disassembly of [0xe87b920, 0xe87bb00) (Minecraft Windows 1.26.62.01).
// Every `call` target is sub_eec6eb0 (class lift, forward-declared in the header).
#if 0
0xe87b920  push r15
0xe87b922  push r14
0xe87b924  push r12
0xe87b926  push rsi
0xe87b927  push rdi
0xe87b928  push rbx
0xe87b929  sub rsp,0x28
0xe87b92d  mov rsi,r8
0xe87b930  mov rdi,rdx
0xe87b933  mov rbx,[rdx+0x10]
0xe87b937  cmp qword ptr [rdx+0x18],0x10
0xe87b93c  jb short 0xE87B941
0xe87b93e  mov rdi,[rdi]
0xe87b941  mov rax,0xCBF29CE484222325
0xe87b94b  test rbx,rbx
0xe87b94e  je 0xE87B9E7
0xe87b954  mov rdx,0x100000001B3
0xe87b95e  mov r8d,ebx
0xe87b961  and r8d,3
0xe87b965  cmp rbx,4
0xe87b969  jae short 0xE87B970
0xe87b96b  xor r9d,r9d
0xe87b96e  jmp short 0xE87B9C1
0xe87b970  mov r10,rbx
0xe87b973  and r10,0xFFFFFFFFFFFFFFFC
0xe87b977  xor r9d,r9d
0xe87b97a  nop [rax+rax]
0xe87b980  movzx r11d,byte ptr [rdi+r9]
0xe87b985  xor r11,rax
0xe87b988  imul r11,rdx
0xe87b98c  movzx eax,byte ptr [rdi+r9+1]
0xe87b992  xor rax,r11
0xe87b995  imul rax,rdx
0xe87b999  movzx r11d,byte ptr [rdi+r9+2]
0xe87b99f  xor r11,rax
0xe87b9a2  imul r11,rdx
0xe87b9a6  movzx eax,byte ptr [rdi+r9+3]
0xe87b9ac  xor rax,r11
0xe87b9af  imul rax,rdx
0xe87b9b3  add r9,4
0xe87b9b7  cmp r10,r9
0xe87b9ba  jne short 0xE87B980
0xe87b9bc  test r8,r8
0xe87b9bf  je short 0xE87B9E7
0xe87b9c1  add r9,rdi
0xe87b9c4  xor r10d,r10d
0xe87b9c7  mov r11,rax
0xe87b9ca  nop [rax+rax]
0xe87b9d0  movzx eax,byte ptr [r9+r10]
0xe87b9d5  xor rax,r11
0xe87b9d8  imul rax,rdx
0xe87b9dc  inc r10
0xe87b9df  mov r11,rax
0xe87b9e2  cmp r8,r10
0xe87b9e5  jne short 0xE87B9D0
0xe87b9e7  and rax,[rcx+0x30]
0xe87b9eb  mov r14,[rcx+8]
0xe87b9ef  mov rcx,[rcx+0x18]
0xe87b9f3  shl rax,4
0xe87b9f7  mov r15,[rcx+rax+8]
0xe87b9fc  cmp r15,r14
0xe87b9ff  je 0xE87BA9A
0xe87ba05  mov r12,[rcx+rax]
0xe87ba09  test rbx,rbx
0xe87ba0c  je short 0xE87BA69
0xe87ba0e  xchg ax,ax
0xe87ba10  cmp rbx,[r15+0x20]
0xe87ba14  jne short 0xE87BA43
0xe87ba16  cmp qword ptr [r15+0x28],0x10
0xe87ba1b  jb short 0xE87BA30
0xe87ba1d  mov rdx,[r15+0x10]
0xe87ba21  jmp short 0xE87BA34
0xe87ba23  nop [rax+rax]
0xe87ba30  lea rdx,[r15+0x10]
0xe87ba34  mov rcx,rdi
0xe87ba37  mov r8,rbx
0xe87ba3a  call 0xEEC6EB0
0xe87ba3f  test eax,eax
0xe87ba41  je short 0xE87BA70
0xe87ba43  cmp r15,r12
0xe87ba46  je short 0xE87BA9A
0xe87ba48  mov r15,[r15+8]
0xe87ba4c  cmp rbx,[r15+0x20]
0xe87ba50  je short 0xE87BA16
0xe87ba52  jmp short 0xE87BA43
0xe87ba54  nop [rax+rax]
0xe87ba60  cmp r15,r12
0xe87ba63  je short 0xE87BA9A
0xe87ba65  mov r15,[r15+8]
0xe87ba69  cmp qword ptr [r15+0x20],0
0xe87ba6e  jne short 0xE87BA60
0xe87ba70  cmp r15,r14
0xe87ba73  je short 0xE87BA9A
0xe87ba75  mov r14,[r15+0x30]
0xe87ba79  mov rbx,[r15+0x38]
0xe87ba7d  mov rax,rbx
0xe87ba80  cmp r14,rbx
0xe87ba83  je short 0xE87BAF8
0xe87ba85  mov rdi,[rsi+0x10]
0xe87ba89  cmp qword ptr [rsi+0x18],0x10
0xe87ba8e  jb short 0xE87BA93
0xe87ba90  mov rsi,[rsi]
0xe87ba93  test rdi,rdi
0xe87ba96  jne short 0xE87BAC8
0xe87ba98  jmp short 0xE87BAE9
0xe87ba9a  xor eax,eax
0xe87ba9c  add rsp,0x28
0xe87baa0  pop rbx
0xe87baa1  pop rdi
0xe87baa2  pop rsi
0xe87baa3  pop r12
0xe87baa5  pop r14
0xe87baa7  pop r15
0xe87baa9  ret
0xe87baaa  nop [rax+rax]
0xe87bab0  mov rdx,rsi
0xe87bab3  mov r8,rdi
0xe87bab6  call 0xEEC6EB0
0xe87babb  test eax,eax
0xe87babd  je short 0xE87BAF0
0xe87babf  add r14,0x20
0xe87bac3  cmp r14,rbx
0xe87bac6  je short 0xE87BAF5
0xe87bac8  cmp [r14+0x10],rdi
0xe87bacc  jne short 0xE87BABF
0xe87bace  cmp qword ptr [r14+0x18],0x10
0xe87bad3  mov rcx,r14
0xe87bad6  jb short 0xE87BAB0
0xe87bad8  mov rcx,[r14]
0xe87badb  jmp short 0xE87BAB0
0xe87badd  nop [rax]
0xe87bae0  add r14,0x20
0xe87bae4  cmp r14,rbx
0xe87bae7  je short 0xE87BAF5
0xe87bae9  cmp qword ptr [r14+0x10],0
0xe87baee  jne short 0xE87BAE0
0xe87baf0  mov rax,r14
0xe87baf3  jmp short 0xE87BAF8
0xe87baf5  mov rax,rbx
0xe87baf8  cmp rax,rbx
0xe87bafb  setne al
0xe87bafe  jmp short 0xE87BA9C
#endif

namespace native::d3d12 {

bool sub_e87b920(Map* map, const Str* key, const Str* query)
{
    // 0xe87b920..0xe87b941  prologue + argument stash: key->length, key data pointer (SSO-resolved)
    const Map* m = map;
    const Str* keyStr = key;
    const Str* queryStr = query;

    uint64_t keyLen = keyStr->length;                              // 0xe87b933  mov rbx,[rdx+0x10]
    uintptr_t keyData;
    if (keyStr->size >= 0x10) {                                    // 0xe87b937  cmp qword ptr [rdx+0x18],0x10 ; jb short 0xE87B941
        keyData = keyStr->data;                                    // 0xe87b93e  mov rdi,[rdi]
    } else {
        keyData = reinterpret_cast<uintptr_t>(keyStr);             // SSO: object address (= &key->data)
    }

    // 0xe87b941..0xe87b9e7  FNV-1a hash of the key bytes (basis 0xCBF29CE484222325, prime 0x100000001B3)
    uint64_t hash = 0xCBF29CE484222325ULL;                         // 0xe87b941  mov rax,0xCBF29CE484222325
    if (keyLen != 0) {                                             // 0xe87b94b  test rbx,rbx ; je 0xE87B9E7
        const uint64_t prime = 0x100000001B3ULL;                   // 0xe87b954  mov rdx,0x100000001B3
        const uint8_t* kp = reinterpret_cast<const uint8_t*>(keyData);
        size_t i = 0;
        const size_t aligned = keyLen & ~3ULL;                     // 0xe87b973  and r10,0xFFFFFFFFFFFFFFFC
        if (keyLen >= 4) {                                         // 0xe87b965  cmp rbx,4 ; jae short 0xE87B970
            while (i < aligned) {                                  // 0xe87b970..0xe87b9ba  aligned 4-byte loop
                hash ^= static_cast<uint64_t>(*kp);                hash *= prime; ++kp;  // 0xe87b980..0xe87b988
                hash ^= static_cast<uint64_t>(*kp);                hash *= prime; ++kp;  // 0xe87b98c..0xe87b995
                hash ^= static_cast<uint64_t>(*kp);                hash *= prime; ++kp;  // 0xe87b999..0xe87b9a2
                hash ^= static_cast<uint64_t>(*kp);                hash *= prime; ++kp;  // 0xe87b9a6..0xe87b9af
                i += 4;                                            // 0xe87b9b3  add r9,4
            }                                                      // 0xe87b9b7  cmp r10,r9 ; jne short 0xE87B980
        }
        if ((keyLen & 3ULL) != 0) {                                // 0xe87b9bc  test r8,r8 ; jne short 0xE87B9C1 (via jmp at 0xe87b96e)
            while (i < keyLen) {                                   // 0xe87b9c1..0xe87b9e5  remainder loop
                hash ^= static_cast<uint64_t>(*kp);                hash *= prime; ++kp;  // 0xe87b9d0..0xe87b9d8
                ++i;                                               // 0xe87b9dc  inc r10
            }                                                      // 0xe87b9e2  cmp r8,r10 ; jne short 0xE87B9D0
        }
    }

    // 0xe87b9e7..0xe87ba05  bucket selection: index = hash & mask; head = bucketArray[index*2+1]
    hash &= m->mask;                                               // 0xe87b9e7  and rax,[rcx+0x30]
    const Node* sentinel = reinterpret_cast<const Node*>(m->sentinel);  // 0xe87b9eb  mov r14,[rcx+8]
    const uintptr_t* bucketArray = m->bucketArray;                 // 0xe87b9ef  mov rcx,[rcx+0x18]
    const size_t index = hash;                                     // 0xe87b9f3  shl rax,4
    const Node* head = reinterpret_cast<const Node*>(bucketArray[index * 2 + 1]);  // 0xe87b9f7  mov r15,[rcx+rax+8]
    if (head == sentinel) return false;                            // 0xe87b9fc  cmp r15,r14 ; je short 0xE87BA9A
    const Node* chainEnd = reinterpret_cast<const Node*>(bucketArray[index * 2]);  // 0xe87ba05  mov r12,[rcx+rax]

    const Node* node = head;

    // 0xe87ba09..0xe87ba6e  chain walk, key->length == 0 special case: find node with key length 0
    if (keyLen == 0) {                                             // 0xe87ba09  test rbx,rbx ; je short 0xE87BA69
        while (true) {
            if (node->keyLength != 0) {                            // 0xe87ba69  cmp qword ptr [r15+0x20],0 ; jne short 0xE87BA60
                if (node == chainEnd) return false;                // 0xe87ba60  cmp r15,r12 ; je short 0xE87BA9A
                node = node->next;                                 // 0xe87ba65  mov r15,[r15+8]
                continue;                                          // jmp short 0xE87BA69
            }
            break;                                                 // node->keyLength == 0 -> fall to 0xe87ba70
        }
    }

    // 0xe87ba10..0xe87ba52  chain walk, key->length != 0: compare length + memcmp
    while (true) {
        if (keyLen == node->keyLength) {                           // 0xe87ba10  cmp rbx,[r15+0x20] ; jne short 0xE87BA43
            uintptr_t nodeKeyData;
            if (node->keySize >= 0x10) {                           // 0xe87ba16  cmp qword ptr [r15+0x28],0x10 ; jb short 0xE87BA30
                nodeKeyData = node->keyData;                       // 0xe87ba1d  mov rdx,[r15+0x10]
            } else {
                nodeKeyData = reinterpret_cast<uintptr_t>(&node->keyData);  // 0xe87ba30  lea rdx,[r15+0x10]
            }
            // 0xe87ba34  mov rcx,rdi ; 0xe87ba37  mov r8,rbx ; 0xe87ba3a  call 0xEEC6EB0
            if (sub_eec6eb0(reinterpret_cast<const void*>(keyData),
                            reinterpret_cast<const void*>(nodeKeyData),
                            keyLen) == 0) {                        // 0xe87ba3f  test eax,eax ; je short 0xE87BA70
                goto found_node;
            }
        }
        // 0xe87ba43  cmp r15,r12 ; je short 0xE87BA9A
        if (node == chainEnd) return false;
        // 0xe87ba48  mov r15,[r15+8]
        node = node->next;
        // 0xe87ba4c  cmp rbx,[r15+0x20] ; je short 0xE87BA16 / jmp short 0xE87BA43
        // (loop re-checks the length of the new node)
    }

found_node:
    // 0xe87ba70  cmp r15,r14 ; je short 0xE87BA9A  (dead: node != sentinel; kept for fidelity)
    if (node == sentinel) return false;

    // 0xe87ba75..0xe87ba83  node's embedded vector [vecData, vecEnd); rax = vecEnd
    const Str* vecData = node->vecData;                            // 0xe87ba75  mov r14,[r15+0x30]
    const Str* vecEnd = node->vecEnd;                              // 0xe87ba79  mov rbx,[r15+0x38]
    uintptr_t rax = reinterpret_cast<uintptr_t>(vecEnd);           // 0xe87ba7d  mov rax,rbx
    if (vecData == vecEnd) return (rax != reinterpret_cast<uintptr_t>(vecEnd));  // 0xe87ba80  cmp r14,rbx ; je short 0xE87BAF8 -> setne al (false)

    // 0xe87ba85..0xe87ba98  query length + SSO data resolve; query->length == 0 edge
    uint64_t queryLen = queryStr->length;                          // 0xe87ba85  mov rdi,[rsi+0x10]
    uintptr_t queryData;
    if (queryStr->size >= 0x10) {                                  // 0xe87ba89  cmp qword ptr [rsi+0x18],0x10 ; jb short 0xE87BA93
        queryData = queryStr->data;                                // 0xe87ba90  mov rsi,[rsi]
    } else {
        queryData = reinterpret_cast<uintptr_t>(queryStr);         // SSO: object address
    }
    if (queryLen == 0) {                                           // 0xe87ba93  test rdi,rdi ; jne short 0xE87BAC8 / jmp short 0xE87BAE9
        // 0xe87bae9..0xe87bae7  seek first vector element with length == 0
        const Str* it = vecData;
        while (true) {
            if (it->length == 0) {                                 // 0xe87bae9  cmp qword ptr [r14+0x10],0 ; jne short 0xE87BAE0
                rax = reinterpret_cast<uintptr_t>(it);             // 0xe87baf0  mov rax,r14
                return rax != reinterpret_cast<uintptr_t>(vecEnd); // 0xe87baf8  cmp rax,rbx ; setne al
            }
            // 0xe87bae0  add r14,0x20 ; cmp r14,rbx ; je short 0xE87BAF5
            ++it;                                                  // stride 0x20 == sizeof(Str)
            if (it == vecEnd) return false;                        // rax = vecEnd -> setne al -> false
        }
    }

    // 0xe87bac8..0xe87babd  vector element compare: length + memcmp(elemData, queryData, queryLen)
    {
        const Str* it = vecData;
        while (true) {
            if (it->length == queryLen) {                          // 0xe87bac8  cmp [r14+0x10],rdi ; jne short 0xE87BABF
                uintptr_t elemData;
                if (it->size >= 0x10) {                            // 0xe87bace  cmp qword ptr [r14+0x18],0x10 ; jb short 0xE87BAB0
                    elemData = it->data;                           // 0xe87bad8  mov rcx,[r14]
                } else {
                    elemData = reinterpret_cast<uintptr_t>(it);    // 0xe87bad3  mov rcx,r14
                }
                // 0xe87bab0  mov rdx,rsi ; mov r8,rdi ; 0xe87bab6  call 0xEEC6EB0
                if (sub_eec6eb0(reinterpret_cast<const void*>(elemData),
                                reinterpret_cast<const void*>(queryData),
                                queryLen) == 0) {                  // 0xe87babb  test eax,eax ; je short 0xE87BAF0
                    rax = reinterpret_cast<uintptr_t>(it);
                    return rax != reinterpret_cast<uintptr_t>(vecEnd);  // 0xe87baf8  cmp rax,rbx ; setne al -> true
                }
            }
            // 0xe87babf  add r14,0x20 ; cmp r14,rbx ; je short 0xE87BAF5
            ++it;
            if (it == vecEnd) return false;                        // rax = vecEnd -> setne al -> false
        }
    }
}

} // namespace native::d3d12

LIFT_FN(sub_e87b920, "sub_e87b920", 0xE87B920, native::d3d12::sub_e87b920, nullptr);
