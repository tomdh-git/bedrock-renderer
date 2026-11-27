// LIFT 0xbce15d0 size 0x91 1.26.62.01 sub_bce15d0
#include "sub_bce15d0.h"

#include <cstdint>
#include <intrin.h>

#include "client/features/render/native/Lift.h"

namespace native {

namespace {

// Jump table referenced by 0xbce160b  lea r8,[0xF44C2F0] ([data_f44c2f0] at image RVA
// 0xF44C2F0, .rdata): VA = imageBase + 0xF44C2F0 [V: rdis sec/dis 0xbce15d0].
inline std::int32_t* bce15d0_table() {
    return reinterpret_cast<std::int32_t*>(RewriteRegistry::imageBase() + 0xF44C2F0ull);
}

// Each table entry is targetVA - tableVA (0xbce1616  add rdx,r8 re-adds the base; then
// 0xbce1619  jmp rdx jumps to it). Image base cancels, so the entry values are RVA
// differences between the jump target and 0xF44C2F0:
constexpr std::int32_t kOff161b = -58109141; // 0xbce161b - 0xF44C2F0  (target: 0xbce161b)
constexpr std::int32_t kOff1640 = -58109104; // 0xbce1640 - 0xF44C2F0  (target: loc_bce1640)
constexpr std::int32_t kOff1647 = -58109097; // 0xbce1647 - 0xF44C2F0  (target: crash call chain)
constexpr std::int32_t kOff164c = -58109092; // 0xbce164c - 0xF44C2F0
constexpr std::int32_t kOff1651 = -58109087; // 0xbce1651 - 0xF44C2F0
constexpr std::int32_t kOff1656 = -58109082; // 0xbce1656 - 0xF44C2F0
constexpr std::int32_t kOff165b = -58109077; // 0xbce165b - 0xF44C2F0

} // namespace

// Boundary callee: sub_b432e0 (0xb432e0, boundary class crt, docs/data/native_boundary.tsv row 173).
// Its body (0xb432e0  sub rsp,0x28; call sub_1166e0; 0xb432e9  int3) reads none of its register
// arguments and never returns, so the values the jump chain delivers in RCX/RDX/R8/R9
// (q2, jump target, table base, incoming 4th argument) are immaterial; they are forwarded
// exactly as observed at each call site. [V: rdis fn 0xb432e0; rdis dis 0xbce15d0]
native::Boundary<std::uintptr_t, void*, void*, void*, void*> sub_b432e0("sub_b432e0");

// sub_bce15d0 (0xbce15d0, size 0x91, 1.26.62.01).
int sub_bce15d0(void* /*rcx: unused by this function*/, void* a1, void* a2, void* a3)
{
    // 0xbce15d0..0xbce15da   sub rsp,0x28 / mov rax,[rdx] / test rax,rax / je short 0xBCE1640
    void* const p1 = *reinterpret_cast<void**>(a1);                    // 0xbce15d4  mov rax,[rdx]
    if (p1 == nullptr) {                                               // 0xbce15d7  test rax,rax ; 0xbce15da  je short 0xBCE1640
        return 0;                                                      // 0xbce1640  xor eax,eax ; 0xbce1642  add rsp,0x28 ; 0xbce1646  ret
    }
    // 0xbce15dc..0xbce15e3   mov rax,[rax+0x18] / test rax,rax / je short 0xBCE1640
    Bce15d0_P* const pObj1 = reinterpret_cast<Bce15d0_P*>(p1);
    Bce15d0_Q* const q1 = pObj1->q;                                    // 0xbce15dc  mov rax,[rax+0x18]
    if (q1 == nullptr) {                                               // 0xbce15e0  test rax,rax ; 0xbce15e3  je short 0xBCE1640
        return 0;
    }
    // 0xbce15e5..0xbce15eb   mov rcx,[r8] / test rcx,rcx / je short 0xBCE1640
    void* const p2 = *reinterpret_cast<void**>(a2);                    // 0xbce15e5  mov rcx,[r8]
    if (p2 == nullptr) {                                               // 0xbce15e8  test rcx,rcx ; 0xbce15eb  je short 0xBCE1640
        return 0;
    }
    // 0xbce15ed..0xbce15f4   mov rcx,[rcx+0x18] / test rcx,rcx / je short 0xBCE1640
    Bce15d0_P* const pObj2 = reinterpret_cast<Bce15d0_P*>(p2);
    Bce15d0_Q* const q2 = pObj2->q;                                    // 0xbce15ed  mov rcx,[rcx+0x18]
    if (q2 == nullptr) {                                               // 0xbce15f1  test rcx,rcx ; 0xbce15f4  je short 0xBCE1640
        return 0;
    }
    // 0xbce15f6..0xbce1619   movsx rdx,byte ptr [rax+2] / movsx r8,byte ptr [rcx+2]
    //   lea rdx,[rdx+rdx*2] / add rdx,r8 / add rdx,4 / lea r8,[0xF44C2F0]
    //   movsxd rdx,[r8+rdx*4] / add rdx,r8 / jmp rdx
    std::int8_t const v1 = *reinterpret_cast<const std::int8_t*>(      // 0xbce15f6  movsx rdx,byte ptr [rax+2]
        reinterpret_cast<const std::uint8_t*>(q1) + 2);
    std::int8_t const v2 = *reinterpret_cast<const std::int8_t*>(      // 0xbce15fb  movsx r8,byte ptr [rcx+2]
        reinterpret_cast<const std::uint8_t*>(q2) + 2);
    std::int64_t const idx = static_cast<std::int64_t>(v1) * 3 +       // 0xbce1600  lea rdx,[rdx+rdx*2] ; 0xbce1604  add rdx,r8
                             static_cast<std::int64_t>(v2) + 4;        // 0xbce1607  add rdx,4
    std::int32_t* const table = bce15d0_table();                       // 0xbce160b  lea r8,[0xF44C2F0]
    std::int32_t const off = table[idx];                               // 0xbce1612  movsxd rdx,[r8+rdx*4]
    // tableVA + off is the jump target: 0xbce1616  add rdx,r8 ; 0xbce1619  jmp rdx
    switch (off) {                                                     // 0xbce1619  jmp rdx (target = tableVA + off)
    case kOff161b: {                                                   // target 0xbce161b
        // 0xbce161b  movzx ecx,word ptr [rcx]   ; R *(*(a2+0x0)+0x18)+0x0   (rcx still holds q2)
        // 0xbce161e  movzx eax,word ptr [rax]   ; R *(*(a1+0x0)+0x18)+0x0   (rax still holds q1)
        std::uint16_t const w1 = q1->id0x0;                            // 0xbce161e
        std::uint16_t const w2 = q2->id0x0;                            // 0xbce161b
        // 0xbce1621  cmp ax,cx ; 0xbce1624  sete dl
        // 0xbce1627  cmp ax,0xFFFF ; 0xbce162b  setne r8b
        // 0xbce162f  cmp cx,0xFFFF ; 0xbce1633  setne al
        // 0xbce1636  and al,r8b ; 0xbce1639  and al,dl
        //            ; al = (w1 == w2) && (w1 != 0xFFFF) && (w2 != 0xFFFF)
        int const result = (w1 == w2 && w1 != 0xFFFF && w2 != 0xFFFF) ? 1 : 0;
        // 0xbce163b  add rsp,0x28 ; 0xbce163f  ret
        // eax keeps w1's high byte (0xbce161e  movzx eax,word ptr [rax]) with al overwritten:
        return (w1 & 0xFF00) | result;                                 // 0xbce163f  ret
    }
    case kOff1640:                                                     // target loc_bce1640
        // 0xbce1640  xor eax,eax ; 0xbce1642  add rsp,0x28 ; 0xbce1646  ret
        return 0;                                                      // 0xbce1640  xor eax,eax ; ret
    case kOff1647:                                                     // 0xbce1647  call 0xB432E0
        sub_b432e0(q2, reinterpret_cast<void*>(reinterpret_cast<std::int8_t*>(table) + off), table, a3);
        [[fallthrough]];
    case kOff164c:                                                     // 0xbce164c  call 0xB432E0 (falls through from 0xbce1647)
        sub_b432e0(q2, reinterpret_cast<void*>(reinterpret_cast<std::int8_t*>(table) + off), table, a3);
        [[fallthrough]];
    case kOff1651:                                                     // 0xbce1651  call 0xB432E0
        sub_b432e0(q2, reinterpret_cast<void*>(reinterpret_cast<std::int8_t*>(table) + off), table, a3);
        [[fallthrough]];
    case kOff1656:                                                     // 0xbce1656  call 0xB432E0
        sub_b432e0(q2, reinterpret_cast<void*>(reinterpret_cast<std::int8_t*>(table) + off), table, a3);
        [[fallthrough]];
    case kOff165b:                                                     // 0xbce165b  call 0xB432E0
        sub_b432e0(q2, reinterpret_cast<void*>(reinterpret_cast<std::int8_t*>(table) + off), table, a3);
        [[fallthrough]];
    default:                                                           // 0xbce1660  int3 (target outside [0xbce15d0, 0xbce1661))
        __debugbreak();                                                // 0xbce1660  int3
        __assume(0);                                                   // end of function: int3 never returns
    }
    return 0;                                                          // unreachable
}

// Verbatim log of every call instruction in [0xbce15d0, 0xbce1661) (rdis dis output,
// two spaces after the address):
#if 0
0xbce1647  call 0xB432E0
0xbce164c  call 0xB432E0
0xbce1651  call 0xB432E0
0xbce1656  call 0xB432E0
0xbce165b  call 0xB432E0
#endif
// Calls out of lifted code: sub_b432e0 (0xb432e0, boundary class crt,
// docs/data/native_boundary.tsv row 173), only on the crash path reached through the jump
// table at image RVA 0xF44C2F0. The callee reads none of its arguments and never returns.
// UNRESOLVED CALL = none: every call target is listed in docs/data/native_boundary.tsv.

// Layout assertions (full set in sub_bce15d0.h; repeated here so liftcheck sees them).
static_assert(offsetof(native::Bce15d0_Q, id0x0) == 0x00, "sub_bce15d0: Q.id0x0 at +0x00");
static_assert(offsetof(native::Bce15d0_Q, type0x2) == 0x02, "sub_bce15d0: Q.type0x2 at +0x02");
static_assert(offsetof(native::Bce15d0_P, q) == 0x18, "sub_bce15d0: P.q at +0x18");
static_assert(offsetof(native::Bce15d0_Object, p) == 0x00, "sub_bce15d0: Object.p at +0x00");

LIFT_FN(bce15d0, "sub_bce15d0", 0xbce15d0, sub_bce15d0, nullptr);

} // namespace native
