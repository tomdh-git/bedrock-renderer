// LIFT 0xe879c60 size 0x24b 1.26.62.01 sub_e879c60
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e879c60.h"

#include <cstdint>

namespace native {
namespace d3d12 {

// sub_e879c60 - hash-set key lookup (read-only, returns bool in al/eax)
// 0xe879c60..0xe879eab  size 0x24b
// rcx = a0 (container: +0x10 sentinel, +0x20 bucket base, +0x38 count)
// rdx = a1 (pointer to pointer; [a1+0x8] -> key object K)
// Returns: true (1) on sentinel / key match, false (0) otherwise.
// Reads only; writes nothing. Calls sub_eec6eb0 (data compare) twice.
//
// Each block carries the instruction range it implements as `// 0xA..0xB`.
// ------------------------------------------------------------------

extern "C" bool sub_e879c60(void* a0_container, void* a1_keyPtr) {
    // Registers (x64 Microsoft ABI): rcx=a0, rdx=a1, r8..r15 scratch.
    uintptr_t rax = 0, rbx = 0, rcx = 0, rdx = 0, rdi = 0, r8 = 0, r9 = 0;
    uintptr_t r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uintptr_t rsp30 = 0, rsp28 = 0, rsp20 = 0;   // stack slots [rsp+0x30],[rsp+0x28],[rsp+0x20]
    bool al = false;

    Container* a0 = reinterpret_cast<Container*>(a0_container);
    uintptr_t Kptr = 0;

    // 0xe879c60..0xe879c87 : prologue; load key object K = *(a1+0x8); al=1; sentinel pre-test
    // push r15; push r14; push r13; push r12; push rsi; push rdi; push rbp; push rbx; sub rsp,0x38
    // 0xe879c70  mov rdx,[rdx+8]                               ; R a1+0x8
    // 0xe879c74  mov r15,[rdx]                                 ; R *(a1+0x8)+0x0
    // 0xe879c77  mov al,1
    // 0xe879c79  mov [rsp+0x30],rdx
    // 0xe879c7e  cmp r15,rdx
    // 0xe879c81  je 0xE879E9A
    rdx = reinterpret_cast<uintptr_t>(a1_keyPtr);
    rdx = *reinterpret_cast<uintptr_t*>(rdx + 8);     // 0xe879c70  rdx = *(a1+0x8)
    r15 = *reinterpret_cast<uintptr_t*>(rdx);          // 0xe879c74  r15 = *rdx  (= K)
    al = true;                                          // 0xe879c77
    rsp30 = rdx;                                        // 0xe879c79  [rsp+0x30] = rdx
    Kptr = rdx;
    if (r15 == Kptr) goto L_e879e9a;                    // 0xe879c7e-0xe879c81

    // 0xe879c87..0xe879cc0 : count/sentinel/bucket-base; bucket index = (count<<4) & mask
    // 0xe879c87  mov r13,0x100000001B3
    // 0xe879c91  mov rax,[rcx+0x38]                          ; R a0+0x38
    // 0xe879c95  mov rsi,[rcx+0x10]                          ; R a0+0x10
    // 0xe879c99  mov r12,[rcx+0x20]                          ; R a0+0x20
    // 0xe879c9d  mov [rsp+0x28],rax
    // 0xe879ca2  shl rax,4
    // 0xe879ca6  mov rcx,0xBF29CE4842223250
    // 0xe879cb0  and rcx,rax
    // 0xe879cb3  mov [rsp+0x20],rcx
    // 0xe879cb8  jmp short 0xE879CCE
    r13 = 0x100000001B3ULL;                             // 0xe879c87  FNV prime
    rax = a0->count;                                    // 0xe879c91
    rsp28 = rax;
    rsi = a0->sentinel;                                 // 0xe879c95
    r12 = a0->bucketBase;                               // 0xe879c99
    rax = rax << 4;                                     // 0xe879ca2
    rcx = kBucketMask;                                  // 0xe879ca6
    rcx = rcx & rax;                                    // 0xe879cb0
    rsp20 = rcx;                                        // 0xe879cb3  [rsp+0x20] = bucketIdx
    goto L_e879cce;                                     // 0xe879cb8

    // 0xe879cc0..0xe879cc9 : chain/sentinel reload (target of backward jumps)
    // 0xe879cc0  mov r15,[r15]                                 ; R *(r15)+0x0
    // 0xe879cc3  cmp r15,[rsp+0x30]
    // 0xe879cc8  je 0xE879E98
L_e879cc0:
    r15 = *reinterpret_cast<uintptr_t*>(r15);            // 0xe879cc0
    if (r15 == rsp30) goto L_e879e98;                    // 0xe879cc3-0xe879cc8

    // 0xe879cce..0xe879ce5 : select key data pointer (heap vs SSO at +0x10)
    // 0xe879cce  cmp qword ptr [r15+0x28],0x10               ; R K+0x28 cap
    // 0xe879cd3  jb short 0xE879CE0
    // 0xe879cd5  mov rdi,[r15+0x10]                          ; R K+0x10 data
    // 0xe879cd9  jmp short 0xE879CE4
    // 0xe879ce0  lea rdi,[r15+0x10]
L_e879cce:
    {
        KeyObj* kobj = reinterpret_cast<KeyObj*>(r15);
        if (kobj->cap >= 0x10) {                          // 0xe879cce-0xe879cd3
            rdi = kobj->data;                             // 0xe879cd5
        } else {
            rdi = r15 + 0x10;                             // 0xe879ce0 L_e879ce0
        }
    }
    // 0xe879ce4..0xe879cf7 : key size; fast path if size>=4
    // 0xe879ce4  mov rbx,[r15+0x20]                          ; R K+0x20 size
    // 0xe879ce8  test rbx,rbx
    // 0xe879ceb  je short 0xE879D10
    // 0xe879ced  mov eax,ebx
    // 0xe879cef  and eax,3
    // 0xe879cf2  cmp rbx,4
    // 0xe879cf6  jae short 0xE879D70
    rbx = *reinterpret_cast<uintptr_t*>(r15 + 0x20);      // 0xe879ce4
    if (rbx == 0) goto L_e879d10;                         // 0xe879ce8-0xe879ceb
    {
        uint32_t eax = static_cast<uint32_t>(rbx);        // 0xe879ced
        eax &= 3u;                                        // 0xe879cef
        if (rbx >= 4) goto L_e879d70;                     // 0xe879cf2-0xe879cf6
    }

    // 0xe879cf8..0xe879d05 : small-size hash setup (size<4), jump to byte loop
    // 0xe879cf8  xor ecx,ecx
    // 0xe879cfa  mov rdx,0xCBF29CE484222325
    // 0xe879d04  jmp 0xE879DCF
    {
        rcx = 0;                                          // 0xe879cf8
        rdx = kFnvBasis;                                  // 0xe879cfa
        goto L_e879dcf;                                   // 0xe879d04
    }

    // 0xe879d10..0xe879d30 : size==0 path -> walk bucket chain at [rsp+0x20]
    // 0xe879d10  mov rax,[rsp+0x20]                          ; R bucketIdx
    // 0xe879d15  mov rbp,[r12+rax+8]                         ; R bucket[+8]
    // 0xe879d1a  cmp rbp,rsi
    // 0xe879d1d  je short 0xE879CC0
    // 0xe879d1f  cmp qword ptr [rbp+0x20],0                  ; R node+0x20 size
    // 0xe879d24  je short 0xE879D40
    // 0xe879d26  mov rax,[rsp+0x20]
    // 0xe879d2b  mov rax,[r12+rax]                           ; R bucket[+0]
L_e879d10:
    rax = rsp20;                                          // 0xe879d10
    rbp = *reinterpret_cast<uintptr_t*>(r12 + rax + 8);   // 0xe879d15
    if (rbp == rsi) goto L_e879cc0;                       // 0xe879d1a-0xe879d1d
    {
        HashNode* node = reinterpret_cast<HashNode*>(rbp);
        if (node->size == 0) goto L_e879d40;              // 0xe879d1f-0xe879d24
    }
    rax = rsp20;                                          // 0xe879d26
    rax = *reinterpret_cast<uintptr_t*>(r12 + rax);       // 0xe879d2b
    goto L_e879d30;

    // 0xe879d30..0xe879d40 : chain walk on bucket[+0]
    // 0xe879d30  cmp rbp,rax
    // 0xe879d33  je short 0xE879CC0
    // 0xe879d35  mov rbp,[rbp+8]                            ; R node+0x8 next
    // 0xe879d39  cmp qword ptr [rbp+0x20],0                 ; R node+0x20 size
    // 0xe879d3e  jne short 0xE879D30
L_e879d30:
    if (rbp == rax) goto L_e879cc0;                       // 0xe879d30-0xe879d33
    {
        HashNode* node = reinterpret_cast<HashNode*>(rbp);
        rbp = node->next;                                 // 0xe879d35
        if (node->size != 0) goto L_e879d30;              // 0xe879d39-0xe879d3e
    }
    goto L_e879d40;

    // 0xe879d70..0xe879dc9 : 4-byte unrolled FNV-1a loop (size>=4)
    // 0xe879d70  mov r8,rbx
    // 0xe879d73  and r8,0xFFFFFFFFFFFFFFFC
    // 0xe879d77  xor ecx,ecx
    // 0xe879d79  mov rdx,0xCBF29CE484222325
    // 0xe879d90  movzx r9d,byte ptr [rdi+rcx]
    // 0xe879d95  xor r9,rdx
    // 0xe879d98  imul r9,r13
    // 0xe879d9c  movzx edx,byte ptr [rdi+rcx+1]
    // 0xe879da1  xor rdx,r9
    // 0xe879da4  imul rdx,r13
    // 0xe879da8  movzx r9d,byte ptr [rdi+rcx+2]
    // 0xe879dae  xor r9,rdx
    // 0xe879db1  imul r9,r13
    // 0xe879db5  movzx edx,byte ptr [rdi+rcx+3]
    // 0xe879dba  xor rdx,r9
    // 0xe879dbd  imul rdx,r13
    // 0xe879dc1  add rcx,4
    // 0xe879dc5  cmp r8,rcx
    // 0xe879dc8  jne short 0xE879D90
L_e879d70:
    r8 = rbx;                                             // 0xe879d70
    r8 &= 0xFFFFFFFFFFFFFFFCULL;                          // 0xe879d73  dword-aligned count
    rcx = 0;                                              // 0xe879d77  index
    rdx = kFnvBasis;                                      // 0xe879d79  hash = basis
L_e879d90:
    {
        uint8_t* p = reinterpret_cast<uint8_t*>(rdi);
        uint64_t h = rdx;
        uint64_t t = static_cast<uint64_t>(p[rcx + 0]);   // 0xe879d90
        t ^= h; t *= r13;                                  // 0xe879d95-0xe879d98
        h = t;
        t = static_cast<uint64_t>(p[rcx + 1]);             // 0xe879d9c
        t ^= h; h = t * r13;                               // 0xe879da1-0xe879da4
        t = static_cast<uint64_t>(p[rcx + 2]);             // 0xe879da8
        t ^= h; t *= r13;                                  // 0xe879dae-0xe879db1
        h = t;
        t = static_cast<uint64_t>(p[rcx + 3]);             // 0xe879db5
        t ^= h; h = t * r13;                               // 0xe879dba-0xe879dbd
        h = t;
        rdx = h;
    }
    rcx += 4;                                             // 0xe879dc1
    if (r8 != rcx) goto L_e879d90;                        // 0xe879dc5-0xe879dc8

    // 0xe879dca..0xe879dce : rax test -> jump to finalize if rax==0
    // 0xe879dca  test rax,rax
    // 0xe879dcd  je short 0xE879DF7
    if (rax == 0) goto L_e879df7;                         // 0xe879dca-0xe879dcd

    // 0xe879dcf..0xe879df6 : remainder byte loop entry
    // 0xe879dcf  add rcx,rdi
    // 0xe879dd2  mov r9,rdx
    // 0xe879dd5  xor r8d,r8d
    // 0xe879de0  movzx edx,byte ptr [rcx+r8]
    // 0xe879de5  xor rdx,r9
    // 0xe879de8  imul rdx,r13
    // 0xe879dec  inc r8
    // 0xe879def  mov r9,rdx
    // 0xe879df2  cmp rax,r8
    // 0xe879df5  jne short 0xE879DE0
L_e879dcf:
    rcx = rcx + rdi;                                      // 0xe879dcf  rcx = data ptr + index
    r9 = rdx;                                             // 0xe879dd2  r9 = running hash
    r8 = 0;                                               // 0xe879dd5  byte index
L_e879de0:
    {
        uint8_t* p = reinterpret_cast<uint8_t*>(rcx);
        uint64_t d = static_cast<uint64_t>(p[r8]);        // 0xe879de0
        d ^= r9; d *= r13;                                // 0xe879de5-0xe879de8
        r8 += 1;                                          // 0xe879dec
        r9 = d;                                           // 0xe879def
        if (rax != r8) goto L_e879de0;                    // 0xe879df2-0xe879df5
    }
    rdx = r9;

    // 0xe879df7..0xe879e1b : finalize hash -> bucket index = (hash & count) << 4
    // 0xe879df7  and rdx,[rsp+0x28]                        ; R count
    // 0xe879dfc  shl rdx,4
    // 0xe879e00  mov rbp,[r12+rdx+8]                       ; R bucket[+8]
    // 0xe879e05  cmp rbp,rsi
    // 0xe879e08  je 0xE879CC0
    // 0xe879e0e  mov r14,[r12+rdx]                         ; R bucket[+0]
    // 0xe879e12  cmp rbx,[rbp+0x20]                        ; R node+0x20 size
    // 0xe879e16  jne short 0xE879E57
    // 0xe879e18  jmp short 0xE879E2A
L_e879df7:
    rdx = rdx & rsp28;                                    // 0xe879df7
    rdx = rdx << 4;                                       // 0xe879dfc
    rbp = *reinterpret_cast<uintptr_t*>(r12 + rdx + 8);   // 0xe879e00
    if (rbp == rsi) goto L_e879cc0;                       // 0xe879e05-0xe879e08
    r14 = *reinterpret_cast<uintptr_t*>(r12 + rdx);       // 0xe879e0e
    {
        HashNode* node = reinterpret_cast<HashNode*>(rbp);
        if (rbx != node->size) goto L_e879e57;            // 0xe879e12-0xe879e16
    }
    goto L_e879e2a;                                       // 0xe879e18

    // 0xe879e20..0xe879e29 : walk to next node
    // 0xe879e20  mov rbp,[rbp+8]                            ; R node+0x8 next
    // 0xe879e24  cmp rbx,[rbp+0x20]                        ; R node+0x20 size
    // 0xe879e28  jne short 0xE879E57
L_e879e20:
    rbp = *reinterpret_cast<uintptr_t*>(rbp + 8);         // 0xe879e20
    {
        HashNode* node = reinterpret_cast<HashNode*>(rbp);
        if (rbx != node->size) goto L_e879e57;            // 0xe879e24-0xe879e28
    }
    goto L_e879e2a;                                       // fall through (matches original fallthrough)

    // 0xe879e2a..0xe879e52 : node size matches -> compare key data (1st call)
    // 0xe879e2a  cmp qword ptr [rbp+0x28],0x10              ; R node+0x28 cap
    // 0xe879e2f  jb short 0xE879E40
    // 0xe879e31  mov rdx,[rbp+0x10]                         ; R node+0x10 data
    // 0xe879e35  jmp short 0xE879E44
    // 0xe879e40  lea rdx,[rbp+0x10]
    // 0xe879e44  mov rcx,rdi                                 ; key data
    // 0xe879e47  mov r8,rbx                                  ; key size
    // 0xe879e4a  call 0xEEC6EB0                              ; sub_eec6eb0(keyData, nodeData, keySize)
    // 0xe879e4f  test eax,eax
    // 0xe879e51  je 0xE879D40
L_e879e2a:
    {
        HashNode* node = reinterpret_cast<HashNode*>(rbp);
        if (node->cap >= 0x10) {                          // 0xe879e2a-0xe879e2f
            rdx = node->data;                             // 0xe879e31
        } else {
            rdx = rbp + 0x10;                             // 0xe879e40 L_e879e40
        }
    }
    rcx = rdi;                                            // 0xe879e44
    r8 = rbx;                                             // 0xe879e47
    // 0xe879e4a  call 0xEEC6EB0
    {
        int cmpRes = sub_eec6eb0(reinterpret_cast<void*>(rcx),
                                 reinterpret_cast<void*>(rdx),
                                 static_cast<std::size_t>(r8));
        if (cmpRes == 0) goto L_e879d40;                  // 0xe879e4f-0xe879e51  equal -> d40
    }
    goto L_e879e57;

    // 0xe879e57..0xe879e5d : size mismatch / data mismatch -> advance chain
    // 0xe879e57  cmp rbp,r14
    // 0xe879e5a  jne short 0xE879E20
    // 0xe879e5c  jmp 0xE879CC0
L_e879e57:
    if (rbp != r14) goto L_e879e20;                       // 0xe879e57-0xe879e5a
    goto L_e879cc0;                                       // 0xe879e5c

    // 0xe879d40..0xe879e8f : 1st-data match -> compare 2nd data
    // 0xe879d40  cmp rbp,rsi
    // 0xe879d43  je 0xE879CC0
    // 0xe879d49  cmp qword ptr [r15+0x48],0x10              ; obj+0x48 cap2
    // 0xe879d4e  jb 0xE879E61
    // 0xe879d54  mov rdx,[r15+0x30]                         ; obj+0x30 data2 heap
    // 0xe879d58  cmp qword ptr [rbp+0x48],0x10              ; node+0x48 cap2
    // 0xe879d5d  jae 0xE879E70
    // 0xe879d63  lea rcx,[rbp+0x30]                         ; node+0x30 data2 inline
    // 0xe879d67  jmp 0xE879E74
    // 0xe879e61  lea rdx,[r15+0x30]                         ; obj+0x30 data2 inline
    // 0xe879e65  cmp qword ptr [rbp+0x48],0x10
    // 0xe879e6a  jb 0xE879D63
    // 0xe879e70  mov rcx,[rbp+0x30]                         ; node+0x30 data2
    // 0xe879e74  mov r8,[r15+0x40]                          ; obj+0x40 len2
    // 0xe879e78  cmp [rbp+0x40],r8                          ; node+0x40 len2
    // 0xe879e7c  jne short 0xE879E94
    // 0xe879e7e  test r8,r8
    // 0xe879e81  je 0xE879CC0
    // 0xe879e87  call 0xEEC6EB0                             ; sub_eec6eb0(nodeData2, objData2, len2)
    // 0xe879e8c  test eax,eax
    // 0xe879e8e  je 0xE879CC0
L_e879d40:
    if (rbp == rsi) goto L_e879cc0;                       // 0xe879d40-0xe879d43
    {
        KeyObj* kobj = reinterpret_cast<KeyObj*>(r15);
        HashNode* node = reinterpret_cast<HashNode*>(rbp);
        if (kobj->cap2 < 0x10) {                          // 0xe879d49-0xe879d4e
            rdx = r15 + 0x30;                             // 0xe879e61 (inline obj data2)
            if (node->cap2 < 0x10) {                      // 0xe879e65-0xe879e6a
                rcx = rbp + 0x30;                         // 0xe879d63 (inline node data2)
                goto L_e879e74;
            } else {
                rcx = node->data2;                        // 0xe879e70 (heap node data2)
                goto L_e879e74;
            }
        } else {
            rdx = kobj->data2;                            // 0xe879d54 (heap obj data2)
            if (node->cap2 >= 0x10) {                     // 0xe879d58-0xe879d5d
                rcx = node->data2;                        // 0xe879e70 (heap node data2)
                goto L_e879e74;
            } else {
                rcx = rbp + 0x30;                         // 0xe879d63 (inline node data2)
                goto L_e879e74;
            }
        }
    }
L_e879e74:
    r8 = *reinterpret_cast<uintptr_t*>(r15 + 0x40);       // 0xe879e74  obj len2
    {
        HashNode* node = reinterpret_cast<HashNode*>(rbp);
        if (node->len2 != r8) goto L_e879e94;             // 0xe879e78-0xe879e7c
    }
    if (r8 == 0) goto L_e879cc0;                          // 0xe879e7e-0xe879e81
    // 0xe879e87  call 0xEEC6EB0  ; rcx=nodeData2, rdx=objData2, r8=len2
    {
        int cmpRes = sub_eec6eb0(reinterpret_cast<void*>(rcx),
                                 reinterpret_cast<void*>(rdx),
                                 static_cast<std::size_t>(r8));
        if (cmpRes == 0) goto L_e879cc0;                  // 0xe879e8c-0xe879e8e  equal -> back
    }
    goto L_e879e94;

    // 0xe879e94..0xe879e97 : no match -> return 0
    // 0xe879e94  xor eax,eax
    // 0xe879e96  jmp short 0xE879E9A
L_e879e94:
    rax = 0;                                              // 0xe879e94
    al = false;
    goto L_e879e9a;

    // 0xe879e98..0xe879e99 : sentinel hit -> return 1
    // 0xe879e98  mov al,1
L_e879e98:
    al = true;                                            // 0xe879e98

    // 0xe879e9a..0xe879eab : epilogue
    // 0xe879e9a  add rsp,0x38
    // pop rbx; pop rbp; pop rdi; pop rsi; pop r12; pop r13; pop r14; pop r15; ret
L_e879e9a:
    return al;                                            // 0xe879e9a..0xe879eaa
}

// LIFT_FN registry entry
LIFT_FN(sub_e879c60, "sub_e879c60", 0xE879C60, sub_e879c60, nullptr);

} // namespace d3d12
} // namespace native

#if 0
// Verbatim call quotes for liftcheck (verify_oc parses plain lines)
0xe879e4a  call 0xEEC6EB0
0xe879e87  call 0xEEC6EB0
#endif
