#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_bce15d0 (0xbce15d0, size 0x91, 1.26.62.01).
//
//   0xbce15d0  sub rsp,0x28
//   0xbce15d4  mov rax,[rdx]                                 ; R a1+0x0
//   0xbce15d7  test rax,rax
//   0xbce15da  je short 0xBCE1640                            ; -> loc_bce1640
//   0xbce15dc  mov rax,[rax+0x18]                            ; R *(a1+0x0)+0x18
//   0xbce15e0  test rax,rax
//   0xbce15e3  je short 0xBCE1640                            ; -> loc_bce1640
//   0xbce15e5  mov rcx,[r8]                                  ; R a2+0x0
//   0xbce15e8  test rcx,rcx
//   0xbce15eb  je short 0xBCE1640                            ; -> loc_bce1640
//   0xbce15ed  mov rcx,[rcx+0x18]                            ; R *(a2+0x0)+0x18
//   0xbce15f1  test rcx,rcx
//   0xbce15f4  je short 0xBCE1640                            ; -> loc_bce1640
//   0xbce15f6  movsx rdx,byte ptr [rax+2]                    ; R *(*(a1+0x0)+0x18)+0x2
//   0xbce15fb  movsx r8,byte ptr [rcx+2]                     ; R *(*(a2+0x0)+0x18)+0x2
//   0xbce1600  lea rdx,[rdx+rdx*2]
//   0xbce1604  add rdx,r8
//   0xbce1607  add rdx,4
//   0xbce160b  lea r8,[0xF44C2F0]                            ; [data_f44c2f0]
//   0xbce1612  movsxd rdx,[r8+rdx*4]
//   0xbce1616  add rdx,r8
//   0xbce1619  jmp rdx
//   0xbce161b  movzx ecx,word ptr [rcx]                      ; R *(*(a2+0x0)+0x18)+0x0
//   0xbce161e  movzx eax,word ptr [rax]                      ; R *(*(a1+0x0)+0x18)+0x0
//   0xbce1621  cmp ax,cx
//   0xbce1624  sete dl
//   0xbce1627  cmp ax,0xFFFF
//   0xbce162b  setne r8b
//   0xbce162f  cmp cx,0xFFFF
//   0xbce1633  setne al
//   0xbce1636  and al,r8b
//   0xbce1639  and al,dl
//   0xbce163b  add rsp,0x28
//   0xbce163f  ret
//
// loc_bce1640:
//   0xbce1640  xor eax,eax
//   0xbce1642  add rsp,0x28
//   0xbce1646  ret
//
//   0xbce1647  call 0xB432E0                                 ; -> sub_b432e0
//   0xbce164c  call 0xB432E0                                 ; -> sub_b432e0
//   0xbce1651  call 0xB432E0                                 ; -> sub_b432e0
//   0xbce1656  call 0xB432E0                                 ; -> sub_b432e0
//   0xbce165b  call 0xB432E0                                 ; -> sub_b432e0
//   0xbce1660  int3
//
// Reversed source (complete; see sub_bce15d0.cpp for the instruction-cited body):
//   p1 = *(void**)a1;             if (p1 == nullptr) return 0;
//   p2 = *(void**)a2;             if (p2 == nullptr) return 0;
//   q1 = *(void**)(p1 + 0x18);    if (q1 == nullptr) return 0;
//   q2 = *(void**)(p2 + 0x18);    if (q2 == nullptr) return 0;
//   idx = (int8_t)*(uint8_t*)(q1 + 2) * 3
//       + (int8_t)*(uint8_t*)(q2 + 2) + 4;
//   off = (int32_t*)(imageBase + 0xF44C2F0)[idx];           // jump table at image RVA 0xF44C2F0
//   switch (off) {  // indirect jump 0xbce1619  jmp rdx to tableVA + off
//     case -> 0xbce161b:
//         return (*(uint16_t*)q1 & 0xFF00)
//             | ((*(uint16_t*)q1 == *(uint16_t*)q2 && *(uint16_t*)q1 != 0xFFFF && *(uint16_t*)q2 != 0xFFFF) ? 1 : 0);
//     case -> 0xbce1640: return 0;
//     case -> 0xbce1647/0xbce164c/0xbce1651/0xbce1656/0xbce165b:
//         sub_b432e0(q2, tableVA + off, tableVA, a3); fall through to the next call; 0xbce1660  int3
//     default: 0xbce1660  int3 (target outside [0xbce15d0, 0xbce1661))
//   }
// Writes: none to game memory.
// Reads: [a1+0x0], [that+0x18], [q1+2], [q1+0]; [a2+0x0], [that+0x18], [q2+2], [q2+0];
//   jump table entry (int32) at image RVA 0xF44C2F0 + idx*4.
// Calls: sub_b432e0 (0xb432e0, boundary class crt) - only on the crash path; the callee reads
//   none of its register arguments and never returns (0xb432e0  sub rsp,0x28; call sub_1166e0; int3).
// 0 callees in the lift set.
// x64 Microsoft ABI: int sub_bce15d0(void* rcx /*unused*/, void* rdx=a1, void* r8=a2, void* r9=a3);
//   return value in EAX: high byte = (*(uint16_t*)q1 >> 8), low byte = comparison result.
//
// Layout constants and static asserts for the lifted body.

struct Bce15d0_Q {   // *q1 / *q2: [+0x00] uint16 (read at 0xbce161e / 0xbce161b), [+0x02] int8 (read at 0xbce15f6 / 0xbce15fb)
    std::uint16_t id0x0;   // +0x00
    std::int8_t  type0x2;  // +0x02
};

struct Bce15d0_P {   // *p1 / *p2: [+0x18] pointer to Q (read at 0xbce15dc / 0xbce15ed)
    std::uint8_t pad0x00[0x18];
    Bce15d0_Q* q;    // +0x18
};

struct Bce15d0_Object {   // *a1 / *a2: [+0x00] pointer to P (read at 0xbce15d4 / 0xbce15e5)
    Bce15d0_P* p;    // +0x00
};

struct Bce15d0Layout {
    static_assert(sizeof(void*) == 8, "sub_bce15d0: x64 ABI, pointer-sized address space");
    static_assert(offsetof(Bce15d0_Q, id0x0) == 0x00, "sub_bce15d0: Q.id0x0 at +0x00");
    static_assert(offsetof(Bce15d0_Q, type0x2) == 0x02, "sub_bce15d0: Q.type0x2 at +0x02");
    static_assert(sizeof(Bce15d0_Q) == 4, "sub_bce15d0: Q covers +0x02");
    static_assert(offsetof(Bce15d0_P, q) == 0x18, "sub_bce15d0: P.q at +0x18");
    static_assert(offsetof(Bce15d0_Object, p) == 0x00, "sub_bce15d0: Object.p at +0x00");
};

namespace native {

// sub_bce15d0 (0xbce15d0, 0x91 bytes, 1.26.62.01): reads two game objects and compares their
// Q->id0x0 values; returns 0 on any null pointer; on the crash path calls the boundary
// callee sub_b432e0 (0xb432e0, crt) and int3's. See the instruction-cited reversal in
// sub_bce15d0.cpp.
int sub_bce15d0(void* /*rcx: unused by this function*/, void* a1 /*rdx*/, void* a2 /*r8*/, void* a3 /*r9*/);

} // namespace native
