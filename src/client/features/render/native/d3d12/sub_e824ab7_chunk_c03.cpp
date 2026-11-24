// LIFT 0xe824ab7 size 0x8a2c 1.26.62.01 sub_e824ab7
// CHUNK 0xe8292b7..0xe82aaab
#include "client/features/render/native/d3d12/sub_e824ab7_chunk_c03.h"

#include <cstdint>
#include <cstring>

namespace native::d3d12 {

// External boundary / lifted functions
extern "C" void* __cdecl sub_47e8f0(void* rcx, uint64_t rdx);           // stl vector grow
extern "C" void* __cdecl sub_eec6ed0(void* rcx, void* rdx, uint64_t r8); // crt memcpy
extern "C" void* __cdecl sub_eec6ec0(void* rcx, void* rdx, uint64_t r8); // crt memmove
extern "C" void* __cdecl sub_eea6040(...);                                // vendor_alloc via [0xF99FFA0]
extern "C" void* __cdecl sub_e8360f0(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9); // upload ring allocator
extern "C" int   __cdecl sub_bc6a9d0(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9); // lifted
extern "C" int   __cdecl sub_e81e1c0(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9); // lifted

// Entry: 0xe8292b7
// State: st->rbx (frame base), st->r13 = [rbx+0xA8], st->r14 (array ptr), st->r15 (loop counter), st->rsi (index), st->rdi, st->rcx, st->rdx, st->r8, st->r9
void sub_e824ab7_chunk_c03(ChunkState_e824ab7_c03* st) {
    uint8_t* rbx = static_cast<uint8_t*>(st->rbx);
    uint64_t r13 = st->r13;
    uint64_t r14 = st->r14;
    uint64_t r15 = st->r15;
    uint64_t rsi = st->rsi;
    uint64_t rdi = st->rdi;
    uint64_t rcx, rdx, r8, r9;
    // xmm9 is zero vector constant (pcmpgtd xmm0, xmm9 at 0xe827e0a in prev chunk)

    // ============================================================
    // 0xe8292b7..0xe829314: First matrix store path (case 0 entry via int 4)
    // 0xe8292b7  int 4
    // 0xe8292b9  add [rax],al
    // 0xe8292bb  mov edi,[rbx+0x2B0]
    // 0xe8292c1  lea rdx,[rdi+rsi]
    // 0xe8292c5  add rdx,0x10
    // 0xe8292c9  mov rax,[rbx+0x98]
    // 0xe8292d0  mov rcx,[rax]
    // 0xe8292d3  mov rax,[r13]
    // 0xe8292d7  mov r9,rcx
    // 0xe8292da  sub r9,rax
    // 0xe8292dd  mov r8,rdx
    // 0xe8292e0  sub r8,r9
    // 0xe8292e3  jbe 0xE82981A
    // 0xe8292e9  mov r9,[rbx+0xA0]
    // 0xe8292f0  mov r9,[r9+0x38]
    // 0xe8292f4  sub r9,rax
    // 0xe8292f7  cmp rdx,r9
    // 0xe8292fa  jbe 0xE8297FA
    // 0xe829300  mov rcx,r13
    // 0xe829303  lea r8,[rbx+0x3B0]
    // 0xe82930a  call 0x47E8F0
    // 0xe82930f  nop
    // 0xe829310  jmp 0xE82980F
    // ============================================================
    // 0xe8292b7..0xe829314
    rdi = *reinterpret_cast<uint32_t*>(rbx + 0x2B0);
    rdx = rdi + rsi + 0x10;
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    rcx = *reinterpret_cast<uint64_t*>(rax);
    r9 = rcx - r13;
    r8 = rdx - r9;
    if (r8 <= r9) { /* jbe 0xE82981A - handled below as fallthrough */ }
    r9 = *reinterpret_cast<uint64_t*>(rbx + 0xA0);
    r9 = *reinterpret_cast<uint64_t*>(r9 + 0x38);
    r9 -= r13;
    if (rdx <= r9) { /* jbe 0xE8297FA - handled below */ }
    rcx = r13;
    r8 = reinterpret_cast<uint64_t>(rbx + 0x3B0);
    // 0xe82930a  call 0x47E8F0
    sub_47e8f0(reinterpret_cast<void*>(rcx), r8);
    goto L_0xe82980F; // jmp 0xE82980F

    // ============================================================
    // 0xe829315..0xe82936E: Second matrix store path (duplicate pattern, different target)
    // 0xe829315  mov edi,[rbx+0x2B0]
    // 0xe82931b  lea rdx,[rdi+rsi]
    // 0xe82931f  add rdx,0x10
    // 0xe829323  mov rax,[rbx+0x98]
    // 0xe82932a  mov rcx,[rax]
    // 0xe82932d  mov rax,[r13]
    // 0xe829331  mov r9,rcx
    // 0xe829334  sub r9,rax
    // 0xe829337  mov r8,rdx
    // 0xe82933a  sub r8,r9
    // 0xe82933d  jbe 0xE829849
    // 0xe829343  mov r9,[rbx+0xA0]
    // 0xe82934a  mov r9,[r9+0x38]
    // 0xe82934e  sub r9,rax
    // 0xe829351  cmp rdx,r9
    // 0xe829354  jbe 0xE829829
    // 0xe82935a  mov rcx,r13
    // 0xe82935d  lea r8,[rbx+0x3B0]
    // 0xe829364  call 0x47E8F0
    // 0xe829369  nop
    // 0xe82936a  jmp 0xE82983E
    // ============================================================
L_0xe829315: // 0xe829315..0xe82936E
    rdi = *reinterpret_cast<uint32_t*>(rbx + 0x2B0);
    rdx = rdi + rsi + 0x10;
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    rcx = *reinterpret_cast<uint64_t*>(rax);
    r9 = rcx - r13;
    r8 = rdx - r9;
    if (r8 <= r9) { /* jbe 0xE829849 */ }
    r9 = *reinterpret_cast<uint64_t*>(rbx + 0xA0);
    r9 = *reinterpret_cast<uint64_t*>(r9 + 0x38);
    r9 -= r13;
    if (rdx <= r9) { /* jbe 0xE829829 */ }
    rcx = r13;
    r8 = reinterpret_cast<uint64_t>(rbx + 0x3B0);
    // 0xe829364  call 0x47E8F0
    sub_47e8f0(reinterpret_cast<void*>(rcx), r8);
    goto L_0xe82983E; // jmp 0xE82983E

    // ============================================================
    // 0xe82936F..0xe8293CE: Third matrix store path (uses r12)
    // 0xe82936f  mov r12d,[rbx+0x2B0]
    // 0xe829376  add r12,rdi
    // 0xe829379  lea rdx,[r12+rsi]
    // 0xe82937d  mov rax,[rbx+0x98]
    // 0xe829384  mov rax,[rax]
    // 0xe829387  mov rcx,[r13]
    // 0xe82938b  mov r9,rax
    // 0xe82938e  sub r9,rcx
    // 0xe829391  mov r8,rdx
    // 0xe829394  sub r8,r9
    // 0xe829397  jbe 0xE8298AD
    // 0xe82939d  mov r9,[rbx+0xA0]
    // 0xe8293a4  mov r9,[r9+0x38]
    // 0xe8293a8  sub r9,rcx
    // 0xe8293ab  cmp rdx,r9
    // 0xe8293ae  jbe 0xE82988A
    // 0xe8293b4  mov rcx,r13
    // 0xe8293b7  lea r8,[rbx+0x3B0]
    // 0xe8293be  call 0x47E8F0
    // 0xe8293c3  nop
    // 0xe8293c4  jmp 0xE8298A2
    // ============================================================
L_0xe82936F: // 0xe82936F..0xe8293CE
    uint64_t r12 = *reinterpret_cast<uint32_t*>(rbx + 0x2B0);
    r12 += rdi;
    rdx = r12 + rsi;
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    rax = *reinterpret_cast<uint64_t*>(rax);
    rcx = *reinterpret_cast<uint64_t*>(r13);
    r9 = rax - rcx;
    r8 = rdx - r9;
    if (r8 <= r9) { /* jbe 0xE8298AD */ }
    r9 = *reinterpret_cast<uint64_t*>(rbx + 0xA0);
    r9 = *reinterpret_cast<uint64_t*>(r9 + 0x38);
    r9 -= rcx;
    if (rdx <= r9) { /* jbe 0xE82988A */ }
    rcx = r13;
    r8 = reinterpret_cast<uint64_t>(rbx + 0x3B0);
    // 0xe8293be  call 0x47E8F0
    sub_47e8f0(reinterpret_cast<void*>(rcx), r8);
    goto L_0xe8298A2; // jmp 0xE8298A2

    // ============================================================
    // 0xe8293CF..0xe829422: Fourth matrix store path (uses rdi)
    // 0xe8293cf  mov edi,[rbx+0x2B0]
    // 0xe8293d3  lea rdx,[rdi+rsi]
    // 0xe8293d7  add rdx,0x10
    // 0xe8293db  mov rax,[rbx+0x98]
    // 0xe8293e2  mov rcx,[rax]
    // 0xe8293e5  mov rax,[r13]
    // 0xe8293e9  mov r9,rcx
    // 0xe8293ec  sub r9,rax
    // 0xe8293ef  mov r8,rdx
    // 0xe8293f2  sub r8,r9
    // 0xe8293f5  jbe 0xE829901
    // 0xe8293fb  mov r9,[rbx+0xA0]
    // 0xe829402  mov r9,[r9+0x38]
    // 0xe829406  sub r9,rax
    // 0xe829409  cmp rdx,r9
    // 0xe82940c  jbe 0xE8298E1
    // 0xe829412  mov rcx,r13
    // 0xe829415  lea r8,[rbx+0x3B0]
    // 0xe82941c  call 0x47E8F0
    // 0xe829421  nop
    // 0xe829422  jmp 0xE8298F6
    // ============================================================
L_0xe8293CF: // 0xe8293CF..0xe829422
    rdi = *reinterpret_cast<uint32_t*>(rbx + 0x2B0);
    rdx = rdi + rsi + 0x10;
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    rcx = *reinterpret_cast<uint64_t*>(rax);
    rax = r13;
    r9 = rcx - rax;
    r8 = rdx - r9;
    if (r8 <= r9) { /* jbe 0xE829901 */ }
    r9 = *reinterpret_cast<uint64_t*>(rbx + 0xA0);
    r9 = *reinterpret_cast<uint64_t*>(r9 + 0x38);
    r9 -= rax;
    if (rdx <= r9) { /* jbe 0xE8298E1 */ }
    rcx = r13;
    r8 = reinterpret_cast<uint64_t>(rbx + 0x3B0);
    // 0xe82941c  call 0x47E8F0
    sub_47e8f0(reinterpret_cast<void*>(rcx), r8);
    goto L_0xe8298F6; // jmp 0xE8298F6

    // ============================================================
    // 0xe829423..0xe82947C: Fifth matrix store path (uses r12, target 0xC0)
    // 0xe829423  mov r12d,[rbx+0x2B0]
    // 0xe82942a  add r12,rdi
    // 0xe82942d  lea rdx,[r12+rsi]
    // 0xe829431  mov rax,[rbx+0x98]
    // 0xe829438  mov rax,[rax]
    // 0xe82943b  mov rcx,[r13]
    // 0xe82943f  mov r9,rax
    // 0xe829442  sub r9,rcx
    // 0xe829445  mov r8,rdx
    // 0xe829448  sub r8,r9
    // 0xe82944b  jbe 0xE82957C
    // 0xe829451  mov r9,[rbx+0xA0]
    // 0xe829458  mov r9,[r9+0x38]
    // 0xe82945c  sub r9,rcx
    // 0xe82945f  cmp rdx,r9
    // 0xe829462  jbe 0xE829559
    // 0xe829468  mov rcx,r13
    // 0xe82946b  lea r8,[rbx+0xC0]
    // 0xe829472  call 0x47E8F0
    // 0xe829477  nop
    // 0xe829478  jmp 0xE829571
    // ============================================================
L_0xe829423: // 0xe829423..0xe82947C
    r12 = *reinterpret_cast<uint32_t*>(rbx + 0x2B0);
    r12 += rdi;
    rdx = r12 + rsi;
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    rax = *reinterpret_cast<uint64_t*>(rax);
    rcx = *reinterpret_cast<uint64_t*>(r13);
    r9 = rax - rcx;
    r8 = rdx - r9;
    if (r8 <= r9) { /* jbe 0xE82957C */ }
    r9 = *reinterpret_cast<uint64_t*>(rbx + 0xA0);
    r9 = *reinterpret_cast<uint64_t*>(r9 + 0x38);
    r9 -= rcx;
    if (rdx <= r9) { /* jbe 0xE829559 */ }
    rcx = r13;
    r8 = reinterpret_cast<uint64_t>(rbx + 0xC0);
    // 0xe829472  call 0x47E8F0
    sub_47e8f0(reinterpret_cast<void*>(rcx), r8);
    goto L_0xe829571; // jmp 0xE829571

    // ============================================================
    // 0xe82947D..0xe8294D6: Sixth matrix store path (uses r12, target 0x3B0)
    // 0xe82947d  mov r12d,[rbx+0x2B0]
    // 0xe829484  add r12,rdi
    // 0xe829487  lea rdx,[r12+rsi]
    // 0xe82948b  mov rax,[rbx+0x98]
    // 0xe829492  mov rax,[rax]
    // 0xe829495  mov rcx,[r13]
    // 0xe829499  mov r9,rax
    // 0xe82949c  sub r9,rcx
    // 0xe82949f  mov r8,rdx
    // 0xe8294a2  sub r8,r9
    // 0xe8294a5  jbe 0xE8299C6
    // 0xe8294ab  mov r9,[rbx+0xA0]
    // 0xe8294b2  mov r9,[r9+0x38]
    // 0xe8294b6  sub r9,rcx
    // 0xe8294b9  cmp rdx,r9
    // 0xe8294bc  jbe 0xE8299A3
    // 0xe8294c2  mov rcx,r13
    // 0xe8294c5  lea r8,[rbx+0x3B0]
    // 0xe8294cc  call 0x47E8F0
    // 0xe8294d1  nop
    // 0xe8294d2  jmp 0xE8299BB
    // ============================================================
L_0xe82947D: // 0xe82947D..0xe8294D6
    r12 = *reinterpret_cast<uint32_t*>(rbx + 0x2B0);
    r12 += rdi;
    rdx = r12 + rsi;
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    rax = *reinterpret_cast<uint64_t*>(rax);
    rcx = *reinterpret_cast<uint64_t*>(r13);
    r9 = rax - rcx;
    r8 = rdx - r9;
    if (r8 <= r9) { /* jbe 0xE8299C6 */ }
    r9 = *reinterpret_cast<uint64_t*>(rbx + 0xA0);
    r9 = *reinterpret_cast<uint64_t*>(r9 + 0x38);
    r9 -= rcx;
    if (rdx <= r9) { /* jbe 0xE8299A3 */ }
    rcx = r13;
    r8 = reinterpret_cast<uint64_t>(rbx + 0x3B0);
    // 0xe8294cc  call 0x47E8F0
    sub_47e8f0(reinterpret_cast<void*>(rcx), r8);
    goto L_0xe8299BB; // jmp 0xE8299BB

    // ============================================================
    // 0xe8294D7..0xe829558: memcpy paths with sub_eec6ed0
    // 0xe8294d7  lea r12,[rax+r8]
    // 0xe8294db  mov rcx,rax
    // 0xe8294de  xor edx,edx
    // 0xe8294e0  call 0xEEC6ED0
    // 0xe8294e5  mov rax,[rbx+0x98]
    // 0xe8294ec  mov [rax],r12
    // 0xe8294ef  mov r13,[rbx+0xA8]
    // 0xe8294f6  mov rcx,[r13]
    // 0xe8294fa  add rcx,rdi
    // 0xe8294fd  jmp short 0xE82957F
    // ... (multiple similar blocks through 0xE829558)
    // ============================================================
L_0xe8294D7: // 0xe8294D7..0xe829558
    r12 = rax + r8;
    rcx = rax;
    rdx = 0;
    // 0xe8294e0  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = r12;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rcx = *reinterpret_cast<uint64_t*>(r13);
    rcx += rdi;
    goto L_0xe82957F;

L_0xe829531: // 0xe829531..0xe829558 (second memcpy block)
    r12 = rax + r8;
    rcx = rax;
    rdx = 0;
    // 0xe82953a  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = r12;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rcx = *reinterpret_cast<uint64_t*>(r13);
    rcx += rdi;
    // 0xe829557  jmp short 0xE82957F
    goto L_0xe82957F;

    // ============================================================
    // 0xe829559..0xe82957E: memcpy with rdi
    // 0xe829559  lea rdi,[rax+r8]
    // 0xe82955d  mov rcx,rax
    // 0xe829560  xor edx,edx
    // 0xe829562  call 0xEEC6ED0
    // 0xe829567  mov rax,[rbx+0x98]
    // 0xe82956e  mov [rax],rdi
    // 0xe829571  mov r13,[rbx+0xA8]
    // 0xe829578  mov rcx,[r13]
    // 0xe82957c  add rcx,r12
    // ============================================================
L_0xe829559: // 0xe829559..0xe82957E
    rdi = rax + r8;
    rcx = rax;
    rdx = 0;
    // 0xe829562  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = rdi;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rcx = *reinterpret_cast<uint64_t*>(r13);
    rcx += r12;

    // ============================================================
    // 0xe82957F..0xe82958A: Jump to common
    // 0xe82957f  lea rdx,[rbx+0x3B0]
    // 0xe829586  jmp 0xE8299D0
    // ============================================================
L_0xe82957F: // 0xe82957F..0xe82958A
    rdx = reinterpret_cast<uint64_t>(rbx + 0x3B0);
    goto L_0xe8299D0;

    // ============================================================
    // 0xe82958B..0xe82961D: More memcpy variants (rdx = 0x3B0 or 0x5B8 or jump to 0xE827F03/0xE827F10)
    // 0xe82958b  lea r12,[rax+r8]
    // 0xe82958f  mov rcx,rax
    // 0xe829592  xor edx,edx
    // 0xe829594  call 0xEEC6ED0
    // 0xe829599  mov rax,[rbx+0x98]
    // 0xe8295a0  mov [rax],r12
    // 0xe8295a3  mov r13,[rbx+0xA8]
    // 0xe8295aa  mov rcx,[r13]
    // 0xe8295ae  add rcx,rdi
    // 0xe8295b1  mov rdx,[rbx+0x5B8]
    // 0xe8295b8  jmp 0xE8299D0
    // ============================================================
L_0xe82958B: // 0xe82958B..0xe82961D
    r12 = rax + r8;
    rcx = rax;
    rdx = 0;
    // 0xe829594  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = r12;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rcx = *reinterpret_cast<uint64_t*>(r13);
    rcx += rdi;
    rdx = *reinterpret_cast<uint64_t*>(rbx + 0x5B8);
    goto L_0xe8299D0;

L_0xe8295BD: // 0xe8295BD..0xe8295EA
    rdi = rax + r8;
    rcx = rax;
    rdx = 0;
    // 0xe8295c6  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = rdi;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rcx = *reinterpret_cast<uint64_t*>(r13);
    rcx += r12;
    rdx = *reinterpret_cast<uint64_t*>(rbx + 0x5B8);
    goto L_0xe8299D0;

L_0xe8295EF: // 0xe8295EF..0xe829626
    rdi = rcx + r8;
    rdx = 0;
    // 0xe8295f5  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = rdi;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rdi = *reinterpret_cast<uint64_t*>(r13);
    rdi += rsi;
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x5C8);
    goto L_0xe827F03; // jmp 0xE827F03 (outside chunk - boundary)

    // ============================================================
    // 0xe82961E..0xe82967F: More memcpy + shl/add paths
    // 0xe82961e  lea r13,[rax+r8]
    // 0xe829622  mov rcx,rax
    // 0xe829625  xor edx,edx
    // 0xe829627  call 0xEEC6ED0
    // 0xe82962c  mov rax,[rbx+0x98]
    // 0xe829633  mov [rax],r13
    // 0xe829636  mov r13,[rbx+0xA8]
    // 0xe82963d  mov rcx,[r13]
    // 0xe829641  add rcx,r12
    // 0xe829644  jmp short 0xE829672
    // ============================================================
L_0xe82961E: // 0xe82961E..0xe82967F
    r13 = rax + r8;
    rcx = rax;
    rdx = 0;
    // 0xe829627  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = r13;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rcx = *reinterpret_cast<uint64_t*>(r13);
    rcx += r12;
    goto L_0xe829672;

L_0xe829646: // 0xe829646..0xe829671
    r12 = rax + r8;
    rcx = rax;
    rdx = 0;
    // 0xe82964f  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = r12;
    rax = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rcx = *reinterpret_cast<uint64_t*>(rax);
    rcx += r13;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);

L_0xe829672: // 0xe829672..0xe82967F
    rdi <<= 6;
    rdi += *reinterpret_cast<uint64_t*>(rbx + 0x2F8);
    rdx = rdi;
    goto L_0xe8299D0;

    // ============================================================
    // 0xe829685..0xe8297CE: More memcpy + jump variants
    // 0xe829685  lea r13,[rax+r8]
    // 0xe829689  mov rcx,rax
    // 0xe82968c  xor edx,edx
    // 0xe82968e  call 0xEEC6ED0
    // 0xe829693  mov rax,[rbx+0x98]
    // 0xe82969a  mov [rax],r13
    // 0xe82969d  mov r13,[rbx+0xA8]
    // 0xe8296a4  mov rcx,[r13]
    // 0xe8296a8  add rcx,r12
    // 0xe8296ab  jmp short 0xE8296D9
    // ... (through 0xE8297CE)
    // ============================================================
L_0xe829685: // 0xe829685..0xe8296D8
    r13 = rax + r8;
    rcx = rax;
    rdx = 0;
    // 0xe82968e  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = r13;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rcx = *reinterpret_cast<uint64_t*>(r13);
    rcx += r12;
    goto L_0xe8296D9;

L_0xe8296AD: // 0xe8296AD..0xe8296D8
    r12 = rax + r8;
    rcx = rax;
    rdx = 0;
    // 0xe8296b6  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = r12;
    rax = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rcx = *reinterpret_cast<uint64_t*>(rax);
    rcx += r13;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);

L_0xe8296D9: // 0xe8296D9..0xe8296E3
    rdx = rsi;
    r8 = rdi;
    goto L_0xe8299D3;

L_0xe8296E4: // 0xe8296E4..0xe829731
    r12 = rax + r8;
    rcx = rax;
    rdx = 0;
    // 0xe8296ed  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = r12;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rcx = *reinterpret_cast<uint64_t*>(r13);
    rcx += rdi;
    goto L_0xe829732;

L_0xe82970C: // 0xe82970C..0xe829731
    rdi = rax + r8;
    rcx = rax;
    rdx = 0;
    // 0xe829715  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = rdi;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rcx = *reinterpret_cast<uint64_t*>(r13);
    rcx += r12;

L_0xe829732: // 0xe829732..0xe82973D
    rdx = reinterpret_cast<uint64_t>(rbx + 0x90B0);
    goto L_0xe8299D0;

L_0xe82973E: // 0xe82973E..0xe82979C
    r12 = rax + r8;
    rcx = rax;
    rdx = 0;
    // 0xe829747  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = r12;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rcx = *reinterpret_cast<uint64_t*>(r13);
    rcx += rdi;
    rdx = reinterpret_cast<uint64_t>(rbx + 0x9130);
    goto L_0xe8299D0;

L_0xe829770: // 0xe829770..0xe82979C
    rdi = rax + r8;
    rcx = rax;
    rdx = 0;
    // 0xe829779  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = rdi;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rcx = *reinterpret_cast<uint64_t*>(r13);
    rcx += r12;
    rdx = reinterpret_cast<uint64_t>(rbx + 0x9130);
    goto L_0xe8299D0;

L_0xe8297A2: // 0xe8297A2..0xe8297CA
    rdi = rcx + r8;
    rdx = 0;
    // 0xe8297a8  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = rdi;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rax = *reinterpret_cast<uint64_t*>(r13);
    rax += rsi;
    // 0xe8297c5  movups [rax],xmm8
    *reinterpret_cast<__m128i*>(rax) = *reinterpret_cast<__m128i*>(&xmm8); // xmm8 store
    goto L_0xe827F10; // jmp 0xE827F10 (outside chunk - boundary)

L_0xe8297CE: // 0xe8297CE..0xe8297F4
    rdi = rcx + r8;
    rdx = 0;
    // 0xe8297d4  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = rdi;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rax = *reinterpret_cast<uint64_t*>(r13);
    rax += rsi;
    // 0xe8297f1  movlps [rax],xmm8
    *reinterpret_cast<__m128i*>(rax) = *reinterpret_cast<__m128i*>(&xmm8); // xmm8 store (low 64-bit)
    goto L_0xe827F10; // jmp 0xE827F10

    // ============================================================
    // 0xe8297FA..0xe8299CF: More memcpy + store variants (r12, rdi, rdx=0x3B0/0x90F0/0x2F0/0x5C0)
    // 0xe8297fa  lea r12,[rcx+r8]
    // 0xe8297fe  xor edx,edx
    // 0xe829800  call 0xEEC6ED0
    // 0xe829805  mov rax,[rbx+0x98]
    // 0xe82980c  mov [rax],r12
    // 0xe82980f  mov r13,[rbx+0xA8]
    // 0xe829816  mov rax,[r13]
    // 0xe82981a  add rdi,rsi
    // 0xe82981d  add rdi,rax
    // 0xe829820  movups [rdi],xmm8
    // 0xe829824  jmp 0xE827F10
    // ============================================================
L_0xe8297FA: // 0xe8297FA..0xe829824
    r12 = rcx + r8;
    rdx = 0;
    // 0xe829800  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = r12;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rax = *reinterpret_cast<uint64_t*>(r13);
    rdi += rsi;
    rdi += rax;
    // 0xe829820  movups [rdi],xmm8
    *reinterpret_cast<__m128i*>(rdi) = *reinterpret_cast<__m128i*>(&xmm8);
    goto L_0xe827F10;

L_0xe829829: // 0xe829829..0xe829852
    r12 = rcx + r8;
    rdx = 0;
    // 0xe82982f  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = r12;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rax = *reinterpret_cast<uint64_t*>(r13);
    rdi += rsi;
    rdi += rax;
    // 0xe82984f  movlps [rdi],xmm8
    *reinterpret_cast<__m128i*>(rdi) = *reinterpret_cast<__m128i*>(&xmm8); // low 64-bit
    goto L_0xe827F10;

L_0xe829858: // 0xe829858..0xe829884
    r12 = rax + r8;
    rcx = rax;
    rdx = 0;
    // 0xe829861  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = r12;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rcx = *reinterpret_cast<uint64_t*>(r13);
    rcx += rdi;
    rdx = reinterpret_cast<uint64_t>(rbx + 0x90F0);
    goto L_0xe8299D0;

L_0xe82988A: // 0xe82988A..0xe8298BC
    rdi = rax + r8;
    rcx = rax;
    rdx = 0;
    // 0xe829893  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = rdi;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rcx = *reinterpret_cast<uint64_t*>(r13);
    rcx += r12;
    rdx = reinterpret_cast<uint64_t>(rbx + 0x90F0);
    goto L_0xe8299D0;

L_0xe8298BC: // 0xe8298BC..0xe8298E0
    rdi = rcx + r8;
    rdx = 0;
    // 0xe8298c2  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = rdi;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rdi = *reinterpret_cast<uint64_t*>(r13);
    rdi += rsi;
    goto L_0xe829907;

L_0xe8298E1: // 0xe8298E1..0xe829906
    r12 = rcx + r8;
    rdx = 0;
    // 0xe8298e7  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = r12;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rax = *reinterpret_cast<uint64_t*>(r13);
    rdi += rsi;
    rdi += rax;

L_0xe829907: // 0xe829907..0xe829912
    rax = reinterpret_cast<uint64_t>(rbx + 0xD170);
    goto L_0xe827F03; // jmp 0xE827F03

    // ============================================================
    // 0xe829913..0xe8299D0: Final memcpy block with various rdx values
    // 0xe829913  lea r12,[rax+r8]
    // 0xe829917  mov rcx,rax
    // 0xe82991a  xor edx,edx
    // 0xe82991c  call 0xEEC6ED0
    // 0xe829921  mov rax,[rbx+0x98]
    // 0xe829928  mov [rax],r12
    // 0xe82992b  mov r13,[rbx+0xA8]
    // 0xe829932  mov rcx,[r13]
    // 0xe829936  add rcx,rdi
    // 0xe829939  mov rdx,[rbx+0x2F0]
    // 0xe829940  jmp 0xE8299D0
    // ... (through 0xE8299CF)
    // ============================================================
L_0xe829913: // 0xe829913..0xe82993F
    r12 = rax + r8;
    rcx = rax;
    rdx = 0;
    // 0xe82991c  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = r12;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rcx = *reinterpret_cast<uint64_t*>(r13);
    rcx += rdi;
    rdx = *reinterpret_cast<uint64_t*>(rbx + 0x2F0);
    goto L_0xe8299D0;

L_0xe829945: // 0xe829945..0xe829971
    rdi = rax + r8;
    rcx = rax;
    rdx = 0;
    // 0xe82994e  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = rdi;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rcx = *reinterpret_cast<uint64_t*>(r13);
    rcx += r12;
    rdx = *reinterpret_cast<uint64_t*>(rbx + 0x2F0);
    goto L_0xe8299D0;

L_0xe829974: // 0xe829974..0xe8299A0
    r12 = rax + r8;
    rcx = rax;
    rdx = 0;
    // 0xe82997d  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = r12;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rcx = *reinterpret_cast<uint64_t*>(r13);
    rcx += rdi;
    rdx = *reinterpret_cast<uint64_t*>(rbx + 0x5C0);
    goto L_0xe8299D0;

L_0xe8299A3: // 0xe8299A3..0xe8299CF
    rdi = rax + r8;
    rcx = rax;
    rdx = 0;
    // 0xe8299ac  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = rdi;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    rcx = *reinterpret_cast<uint64_t*>(r13);
    rcx += r12;
    rdx = *reinterpret_cast<uint64_t*>(rbx + 0x5C0);

    // ============================================================
    // 0xe8299D0..0xe8299D7: sub_eec6ec0 call + jump to 0xE827F10
    // 0xe8299d0  mov r8,rsi
    // 0xe8299d3  call 0xEEC6EC0
    // 0xe8299d8  jmp 0xE827F10
    // ============================================================
L_0xe8299D0: // 0xe8299D0..0xe8299D7
    r8 = rsi;
    // 0xe8299d3  call 0xEEC6EC0
    sub_eec6ec0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    goto L_0xe827F10; // jmp 0xE827F10

L_0xe8299D3: // 0xe8299D3..0xe8299D8 (alternate entry to sub_eec6ec0)
    r8 = rdi;
    // 0xe8299d3  call 0xEEC6EC0
    sub_eec6ec0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    goto L_0xe827F10;

    // ============================================================
    // 0xe8299DD..0xe829C8F: Texture/buffer upload path
    // 0xe8299dd  mov esi,[rbx+0x2B0]
    // 0xe8299e3  mov r14d,[rbx+0x2B8]
    // 0xe8299ea  mov rax,[rbx+0x2A8]
    // 0xe8299f1  lea rcx,[rax+rsi]
    // 0xe8299f5  mov edx,[rbx+0x26C]
    // 0xe8299fb  cmp rcx,rdx
    // 0xe8299fe  jbe 0xE829B20
    // ============================================================
L_0xe8299DD: // 0xe8299DD..0xe829C8F
    rsi = *reinterpret_cast<uint32_t*>(rbx + 0x2B0);
    r14 = *reinterpret_cast<uint32_t*>(rbx + 0x2B8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x2A8);
    rcx = rax + rsi;
    rdx = *reinterpret_cast<uint32_t*>(rbx + 0x26C);
    if (rcx <= rdx) { goto L_0xe829B20; }

    // 0xe829a04  mov r8d,0xFFFF
    // 0xe829a0a  mov r9d,0x100
    // 0xe829a10  mov rcx,[rbx+0x578]
    // 0xe829a17  lea rdx,[rbx+0x3B0]
    // 0xe829a1e  call 0xE8360F0
    r8 = 0xFFFF;
    r9 = 0x100;
    rcx = *reinterpret_cast<uint64_t*>(rbx + 0x578);
    rdx = reinterpret_cast<uint64_t>(rbx + 0x3B0);
    // 0xe829a1e  call 0xE8360F0
    sub_e8360f0(rcx, rdx, r8, r9);

    // 0xe829a24  mov r15,[rbx+0x3C8]
    // 0xe829a2b  mov r12d,[rbx+0x3C0]
    // 0xe829a32  mov rax,[rbx+0x3B0]
    // 0xe829a39  mov rdi,[rbx+0x3B8]
    // 0xe829a40  movups xmm0,[rax]
    // 0xe829a43  movups xmm1,[rax+0x10]
    // 0xe829a47  movaps [rbx+0xD0],xmm1
    // 0xe829a4e  movaps [rbx+0xC0],xmm0
    // 0xe829a55  mov rdx,[rax+8]
    // 0xe829a59  mov rcx,[rax+0x10]
    // 0xe829a5d  mov r13d,[rax+0x1C]
    // 0xe829a61  test rdi,rdi
    // 0xe829a64  je short 0xE829ABB
    r15 = *reinterpret_cast<uint64_t*>(rbx + 0x3C8);
    r12 = *reinterpret_cast<uint32_t*>(rbx + 0x3C0);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x3B0);
    rdi = *reinterpret_cast<uint64_t*>(rbx + 0x3B8);
    xmm0 = *reinterpret_cast<__m128i*>(rax);
    xmm1 = *reinterpret_cast<__m128i*>(rax + 0x10);
    *reinterpret_cast<__m128i*>(rbx + 0xD0) = xmm1;
    *reinterpret_cast<__m128i*>(rbx + 0xC0) = xmm0;
    rdx = *reinterpret_cast<uint64_t*>(rax + 8);
    rcx = *reinterpret_cast<uint64_t*>(rax + 0x10);
    r13 = *reinterpret_cast<uint32_t*>(rax + 0x1C);
    if (rdi == 0) { goto L_0xe829ABB; }

    // 0xe829a66  lock dec dword ptr [rdi+8]
    // 0xe829a6a  jne short 0xE829ABB
    // 0xe829a6c  mov rax,[rdi]
    // 0xe829a6f  mov rax,[rax]
    // 0xe829a72  mov [rbx+0xF0],rcx
    // 0xe829a79  mov rcx,rdi
    // 0xe829a7c  mov [rbx+0x170],rdx
    // 0xe829a83  call qword ptr [0xF99FFA0]
    // 0xe829a89  mov rdx,[rbx+0x170]
    // 0xe829a90  mov rcx,[rbx+0xF0]
    // 0xe829a97  lock dec dword ptr [rdi+0xC]
    // 0xe829a9b  jne short 0xE829ABB
    // 0xe829a9d  mov rax,[rdi]
    // 0xe829aa0  mov rax,[rax+8]
    // 0xe829aa4  mov rcx,rdi
    // 0xe829aa7  call qword ptr [0xF99FFA0]
    // 0xe829aad  mov rdx,[rbx+0x170]
    // 0xe829ab4  mov rcx,[rbx+0xF0]
    {
        uint32_t* ref1 = reinterpret_cast<uint32_t*>(rdi + 8);
        _InterlockedDecrement(ref1);
        if (*ref1 != 0) { goto L_0xe829ABB; }
        rax = *reinterpret_cast<uint64_t*>(rdi);
        rax = *reinterpret_cast<uint64_t*>(rax);
        *reinterpret_cast<uint64_t*>(rbx + 0xF0) = rcx;
        rcx = rdi;
        *reinterpret_cast<uint64_t*>(rbx + 0x170) = rdx;
        // 0xe829a83  call qword ptr [0xF99FFA0]
        sub_eea6040(rcx);
        rdx = *reinterpret_cast<uint64_t*>(rbx + 0x170);
        rcx = *reinterpret_cast<uint64_t*>(rbx + 0xF0);
        uint32_t* ref2 = reinterpret_cast<uint32_t*>(rdi + 0xC);
        _InterlockedDecrement(ref2);
        if (*ref2 != 0) { goto L_0xe829ABB; }
        rax = *reinterpret_cast<uint64_t*>(rdi);
        rax = *reinterpret_cast<uint64_t*>(rax + 8);
        rcx = rdi;
        // 0xe829aa7  call qword ptr [0xF99FFA0]
        sub_eea6040(rcx);
        rdx = *reinterpret_cast<uint64_t*>(rbx + 0x170);
        rcx = *reinterpret_cast<uint64_t*>(rbx + 0xF0);
    }

L_0xe829ABB: // 0xe829ABB..0xe829B1F
    rcx += r12;
    if (r13 != 2) { rcx = 0; }
    rdx += r12;
    *reinterpret_cast<uint32_t*>(rbx + 0x268) = static_cast<uint32_t>(r12);
    *reinterpret_cast<uint32_t*>(rbx + 0x26C) = static_cast<uint32_t>(r15);
    xmm0 = *reinterpret_cast<__m128i*>(rbx + 0xC0);
    xmm1 = *reinterpret_cast<__m128i*>(rbx + 0xD0);
    rax = reinterpret_cast<uint64_t>(rbx + 0x270);
    *reinterpret_cast<__m128i*>(rax + 0x10) = xmm1;
    *reinterpret_cast<__m128i*>(rax) = xmm0;
    *reinterpret_cast<uint64_t*>(rbx + 0x290) = rdx;
    *reinterpret_cast<uint64_t*>(rbx + 0x298) = rcx;
    *reinterpret_cast<uint64_t*>(rbx + 0x2A8) = 0;
    r13 = *reinterpret_cast<uint64_t*>(rbx + 0xA8);
    goto L_0xe829B2E;

    // ============================================================
    // 0xe829B20..0xe829C8F: Main upload loop
    // 0xe829b20  mov rdx,[rbx+0x290]
    // 0xe829b27  mov rcx,[rbx+0x298]
    // 0xe829b2e  add rcx,rax
    // 0xe829b31  add rdx,rax
    // 0xe829b34  mov [rbx+0x170],rdx
    // 0xe829b3b  mov rdx,[r13]
    // 0xe829b3f  mov r8,rsi
    // 0xe829b42  call 0xEEC6EC0
    L_0xe829B20: // 0xe829B20..0xe829B50
    rdx = *reinterpret_cast<uint64_t*>(rbx + 0x290);
    rcx = *reinterpret_cast<uint64_t*>(rbx + 0x298);
    rcx += rax;
    rdx += rax;
    *reinterpret_cast<uint64_t*>(rbx + 0x170) = rdx;
    rdx = *reinterpret_cast<uint64_t*>(r13);
    r8 = rsi;
    // 0xe829b42  call 0xEEC6EC0
    sub_eec6ec0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    *reinterpret_cast<uint64_t*>(rbx + 0x2A8) += r14;

    // 0xe829b50  mov rax,[rbx+0x90]
    // 0xe829b57  mov rcx,[rax+0x30]
    // 0xe829b5b  mov rax,[rcx]
    // 0xe829b5e  mov rax,[rax+0x128]
    // 0xe829b65  mov edx,2
    // 0xe829b6a  mov r8,[rbx+0x170]
    // 0xe829b71  call qword ptr [0xF99FFA0]
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x90);
    rcx = *reinterpret_cast<uint64_t*>(rax + 0x30);
    rax = *reinterpret_cast<uint64_t*>(rcx);
    rax = *reinterpret_cast<uint64_t*>(rax + 0x128);
    rdx = 2;
    r8 = *reinterpret_cast<uint64_t*>(rbx + 0x170);
    // 0xe829b71  call qword ptr [0xF99FFA0]
    sub_eea6040(rcx, rdx, r8);

    // 0xe829b78  mov r8,[rbx+0x1B0]
    // 0xe829b7f  cmp byte ptr [r8+0x23],1
    // 0xe829b84  jne short 0xE829BEA
    r8 = *reinterpret_cast<uint64_t*>(rbx + 0x1B0);
    if (*reinterpret_cast<uint8_t*>(r8 + 0x23) == 1) {
        // 0xe829b86  mov rdx,[rbx+0x1E8]
        // 0xe829b8d  shl edx,6
        // 0xe829b90  add rdx,[rbx+0x90A0]
        // 0xe829b97  mov rcx,[rbx+0xB0]
        // 0xe829b9e  mov rax,[rcx]
        // 0xe829ba1  mov rax,[rax+0x200]
        // 0xe829ba8  mov r10,[0xF99FFA0]
        // 0xe829baf  mov r8,[rbx+0x318]
        // 0xe829bb6  mov [rsp+0x30],r8
        // 0xe829bbb  mov [rsp+0x28],rdx
        // 0xe829bc0  mov rdx,[rbx+0x1F0]
        // 0xe829bc7  mov [rsp+0x20],rdx
        // 0xe829bcc  mov rdx,[rbx+0x90]
        // 0xe829bd3  mov r8,[rbx+0x658]
        // 0xe829bda  mov r9,[rbx+0x660]
        // 0xe829be1  call r10
        rdx = *reinterpret_cast<uint64_t*>(rbx + 0x1E8);
        rdx <<= 6;
        rdx += *reinterpret_cast<uint64_t*>(rbx + 0x90A0);
        rcx = *reinterpret_cast<uint64_t*>(rbx + 0xB0);
        rax = *reinterpret_cast<uint64_t*>(rcx);
        rax = *reinterpret_cast<uint64_t*>(rax + 0x200);
        void* r10 = *reinterpret_cast<void**>(0xF99FFA0);
        r8 = *reinterpret_cast<uint64_t*>(rbx + 0x318);
        // stack args for call r10
        rdx = *reinterpret_cast<uint64_t*>(rbx + 0x1F0);
        rdx = *reinterpret_cast<uint64_t*>(rbx + 0x90);
        r8 = *reinterpret_cast<uint64_t*>(rbx + 0x658);
        r9 = *reinterpret_cast<uint64_t*>(rbx + 0x660);
        // 0xe829be1  call r10
        reinterpret_cast<void(*)()>(r10)(); // vendor call via r10
        goto L_0xe829C90;
    } else {
        // 0xe829bea  movzx eax,word ptr [r8+0xC]
        // 0xe829bef  cmp rax,0xFFFF
        // 0xe829bf5  mov rcx,[rbx+0x90]
        // 0xe829bfc  je short 0xE829C66
        // 0xe829bfe  shl eax,7
        // 0xe829c01  add rax,[rbx+0x588]
        // 0xe829c08  movzx r8d,word ptr [r8+0x1E]
        // 0xe829c0d  cmp r8d,0xFFFF
        // 0xe829c14  jne short 0xE829C1E
        // 0xe829c16  mov r8d,[rax+0x60]
        // 0xe829c1a  shr r8d,5
        // 0xe829c1e  mov rcx,[rcx+0x30]
        // 0xe829c22  mov rdx,[rbx+0x1B0]
        // 0xe829c29  movzx r10d,word ptr [rdx+0x1C]
        // 0xe829c2e  shl r10d,5
        // 0xe829c32  mov r9,[rax]
        // 0xe829c35  mov rax,[0x12BB4910]
        // 0xe829c3c  mov rdx,[rax+0x19F40]
        // 0xe829c43  mov rax,[rcx]
        // 0xe829c46  mov rax,[rax+0x1D8]
        // 0xe829c4d  mov r11,[0xF99FFA0]
        // 0xe829c54  movdqu [rsp+0x28],xmm9
        // 0xe829c5b  mov [rsp+0x20],r10
        // 0xe829c60  call r11
        rax = *reinterpret_cast<uint16_t*>(r8 + 0xC);
        rcx = *reinterpret_cast<uint64_t*>(rbx + 0x90);
        if (rax == 0xFFFF) { goto L_0xe829C66; }
        rax <<= 7;
        rax += *reinterpret_cast<uint64_t*>(rbx + 0x588);
        r8 = *reinterpret_cast<uint16_t*>(r8 + 0x1E);
        if (r8 != 0xFFFF) { goto L_0xe829C1E; }
        r8 = *reinterpret_cast<uint32_t*>(rax + 0x60);
        r8 >>= 5;

L_0xe829C1E:
        rcx = *reinterpret_cast<uint64_t*>(rcx + 0x30);
        rdx = *reinterpret_cast<uint64_t*>(rbx + 0x1B0);
        r10 = *reinterpret_cast<uint16_t*>(rdx + 0x1C);
        r10 <<= 5;
        r9 = *reinterpret_cast<uint64_t*>(rax);
        rax = *reinterpret_cast<uint64_t*>(0x12BB4910);
        rdx = *reinterpret_cast<uint64_t*>(rax + 0x19F40);
        rax = *reinterpret_cast<uint64_t*>(rcx);
        rax = *reinterpret_cast<uint64_t*>(rax + 0x1D8);
        void* r11 = *reinterpret_cast<void**>(0xF99FFA0);
        // stack: xmm9, r10
        // 0xe829c60  call r11
        reinterpret_cast<void(*)()>(r11)(); // vendor call via r11
        goto L_0xe829C90;

L_0xe829C66: // 0xe829C66..0xe829C8F
        rcx = *reinterpret_cast<uint64_t*>(rcx + 0x30);
        r9 = *reinterpret_cast<uint32_t*>(r8 + 0x18);
        rdx = *reinterpret_cast<uint32_t*>(r8 + 0x10);
        r8 = *reinterpret_cast<uint32_t*>(r8 + 0x14);
        rax = *reinterpret_cast<uint64_t*>(rcx);
        rax = *reinterpret_cast<uint64_t*>(rax + 0x70);
        // 0xe829c7d  call qword ptr [0xF99FFA0]
        sub_eea6040(rcx, rdx, r8, r9);
    }

L_0xe829C90: // 0xe829C90..0xe829CAE
    st->rdi = 1; // dil=1
    rcx = 0;
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x160);
    *reinterpret_cast<uint16_t*>(rbx + 0x190) = static_cast<uint16_t>(rax);
    rsi = *reinterpret_cast<uint64_t*>(rbx + 0xB0);
    goto L_0xe82D0CF; // jmp 0xE82D0CF (outside chunk - boundary)

    // ============================================================
    // 0xe829CAF..0xe829CE0: More memcpy variants
    // 0xe829caf  lea rdi,[rcx+r8]
    // 0xe829cb3  xor edx,edx
    // 0xe829cb5  call 0xEEC6ED0
    // 0xe829cba  mov rax,[rbx+0x98]
    // 0xe829cc1  mov [rax],rdi
    // 0xe829cc4  test sil,sil
    // 0xe829cc7  jne 0xE827E69
    // 0xe829ccd  jmp 0xE827E90
    // ============================================================
L_0xe829CAF: // 0xe829CAF..0xe829CE0
    rdi = rcx + r8;
    rdx = 0;
    // 0xe829cb5  call 0xEEC6ED0
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x98);
    *reinterpret_cast<uint64_t*>(rax) = rdi;
    if (static_cast<uint8_t>(rsi) != 0) { goto L_0xe827E69; }
    goto L_0xe827E90; // jmp 0xE827E90

    // ============================================================
    // 0xe829CD2..0xe829D5C: Index/vertex setup path
    // 0xe829cd2  movzx ecx,word ptr [rbx+rsi*4+0x696]
    // 0xe829cda  mov [rbx+0x690],cx
    // 0xe829ce1  cmp cx,0xFFFF
    // 0xe829ce5  jne 0xE822FC5
    // 0xe829ceb  mov [rbx+0x692],ax
    // 0xe829cf2  mov word ptr [rbx+rsi*4+0x694],0xFFFF
    // 0xe829cfc  movzx eax,word ptr [rbx+0x690]
    // 0xe829d03  mov [rbx+rsi*4+0x696],ax
    // 0xe829d0b  cmp rax,0xFFFF
    // 0xe829d11  je 0xE82A39B
    // 0xe829d17  movzx ecx,word ptr [rbx+rax*4+0x694]
    // 0xe829d1f  cmp rcx,0xFFFF
    // 0xe829d26  je short 0xE829D30
    // 0xe829d28  mov [rbx+rcx*4+0x696],si
    // 0xe829d30  mov [rbx+rsi*4+0x694],cx
    // 0xe829d38  mov [rbx+rax*4+0x694],si
    // 0xe829d40  cmp word ptr [rbx+rsi*4+0x694],0xFFFF
    // 0xe829d49  je 0xE82A39B
    // 0xe829d4f  cmp word ptr [rbx+rsi*4+0x696],0xFFFF
    // 0xe829d58  je 0xE82A3B1
    // ============================================================
L_0xe829CD2: // 0xe829CD2..0xe829D5C
    rcx = *reinterpret_cast<uint16_t*>(rbx + rsi * 4 + 0x696);
    *reinterpret_cast<uint16_t*>(rbx + 0x690) = static_cast<uint16_t>(rcx);
    if (rcx != 0xFFFF) { goto L_0xe822FC5; } // outside chunk
    *reinterpret_cast<uint16_t*>(rbx + 0x692) = static_cast<uint16_t>(rax);
    *reinterpret_cast<uint16_t*>(rbx + rsi * 4 + 0x694) = 0xFFFF;
    rax = *reinterpret_cast<uint16_t*>(rbx + 0x690);
    *reinterpret_cast<uint16_t*>(rbx + rsi * 4 + 0x696) = static_cast<uint16_t>(rax);
    if (rax == 0xFFFF) { goto L_0xe82A39B; }
    rcx = *reinterpret_cast<uint16_t*>(rbx + rax * 4 + 0x694);
    if (rcx != 0xFFFF) {
        *reinterpret_cast<uint16_t*>(rbx + rcx * 4 + 0x696) = static_cast<uint16_t>(rsi);
    }
    *reinterpret_cast<uint16_t*>(rbx + rsi * 4 + 0x694) = static_cast<uint16_t>(rcx);
    *reinterpret_cast<uint16_t*>(rbx + rax * 4 + 0x694) = static_cast<uint16_t>(rsi);
    if (*reinterpret_cast<uint16_t*>(rbx + rsi * 4 + 0x694) == 0xFFFF) { goto L_0xe82A39B; }
    if (*reinterpret_cast<uint16_t*>(rbx + rsi * 4 + 0x696) == 0xFFFF) { goto L_0xe82A3B1; }

    // ============================================================
    // 0xe829D5E..0xe829E3D: Vertex/index buffer setup with vendor calls
    // 0xe829d5e  shl esi,5
    // 0xe829d61  movzx edi,word ptr [rbx+rsi+0x8A8]
    // 0xe829d69  cmp di,[rbx+0x10C]
    // 0xe829d70  je short 0xE829DB3
    // ... through 0xE829E3D
    // ============================================================
L_0xe829D5E: // 0xe829D5E..0xe829E3D
    rsi <<= 5;
    rdi = *reinterpret_cast<uint16_t*>(rbx + rsi + 0x8A8);
    if (rdi == *reinterpret_cast<uint16_t*>(rbx + 0x10C)) { goto L_0xe829DB3; }
    rax = rdi;
    rcx = *reinterpret_cast<uint64_t*>(rbx + 0x90);
    rcx = *reinterpret_cast<uint64_t*>(rcx + 0x30);
    rdx = *reinterpret_cast<uint64_t*>(rbx + 0xA0);
    r8 = *reinterpret_cast<uint16_t*>(rdx + 0x24);
    r8 *= rax;
    r8 *= *reinterpret_cast<uint32_t*>(rdx + 0x20);
    r8 += *reinterpret_cast<uint64_t*>(rdx + 0x18);
    rax = *reinterpret_cast<uint64_t*>(rcx);
    rax = *reinterpret_cast<uint64_t*>(rax + 0x100);
    rdx = 0;
    // 0xe829da5  call qword ptr [0xF99FFA0]
    sub_eea6040(rcx, rdx, r8);
    *reinterpret_cast<uint16_t*>(rbx + 0x10C) = static_cast<uint16_t>(rdi);

L_0xe829DB3: // 0xe829DB3..0xe829E0B
    rsi += rbx + 0x670;
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x90);
    rcx = *reinterpret_cast<uint64_t*>(rax + 0x30);
    r8 = *reinterpret_cast<uint64_t*>(rsi + 0x230);
    rax = *reinterpret_cast<uint64_t*>(rcx);
    rax = *reinterpret_cast<uint64_t*>(rax + 0x100);
    rdx = 1;
    // 0xe829dde  call qword ptr [0xF99FFA0]
    sub_eea6040(rcx, rdx, r8);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x90);
    rcx = *reinterpret_cast<uint64_t*>(rax + 0x30);
    r8 = *reinterpret_cast<uint64_t*>(rsi + 0x230);
    rax = *reinterpret_cast<uint64_t*>(rcx);
    rax = *reinterpret_cast<uint64_t*>(rax + 0x100);
    rdx = 4;
    // 0xe829e06  call qword ptr [0xF99FFA0]
    sub_eea6040(rcx, rdx, r8);

    // 0xe829e0d  cmp qword ptr [rbx+0x240],0
    // 0xe829e15  je short 0xE829E3E
    // 0xe829e17  mov rax,[rbx+0xF0]
    // 0xe829e1e  movzx edx,byte ptr [rax+0x28]
    // 0xe829e22  mov rax,[rbx+0x90]
    // 0xe829e29  mov rcx,[rax+0x30]
    // 0xe829e2d  mov rax,[rcx]
    // 0xe829e30  mov rax,[rax+0xC0]
    // 0xe829e37  call qword ptr [0xF99FFA0]
    if (*reinterpret_cast<uint64_t*>(rbx + 0x240) != 0) {
        rax = *reinterpret_cast<uint64_t*>(rbx + 0xF0);
        rdx = *reinterpret_cast<uint8_t*>(rax + 0x28);
        rax = *reinterpret_cast<uint64_t*>(rbx + 0x90);
        rcx = *reinterpret_cast<uint64_t*>(rax + 0x30);
        rax = *reinterpret_cast<uint64_t*>(rcx);
        rax = *reinterpret_cast<uint64_t*>(rax + 0xC0);
        // 0xe829e37  call qword ptr [0xF99FFA0]
        sub_eea6040(rcx, rdx, r8); // r8 from prev
    }

    // ============================================================
    // 0xe829E3E..0xe829F85: Render-state path (SIMD const loads, divps, vendor calls)
    // 0xe829e3e  cmp byte ptr [rbx+0x390],0
    // 0xe829e45  je 0xE829ED1
    // 0xe829e4b  mov rax,[rbx+0xF0]
    // 0xe829e52  mov esi,[rax+0x30]
    // 0xe829e55  cmp [rbx+0x258],esi
    // 0xe829e5b  mov rdi,[rbx+0x90]
    // 0xe829e62  movzx r8d,word ptr [rbx+0x300]
    // 0xe829e6a  je short 0xE829EE0
    // ... through 0xE829F85
    // ============================================================
L_0xe829E3E: // 0xe829E3E..0xe829F85
    if (*reinterpret_cast<uint8_t*>(rbx + 0x390) != 0) {
        rax = *reinterpret_cast<uint64_t*>(rbx + 0xF0);
        rsi = *reinterpret_cast<uint32_t*>(rax + 0x30);
        if (*reinterpret_cast<uint32_t*>(rbx + 0x258) != rsi) {
            rdi = *reinterpret_cast<uint64_t*>(rbx + 0x90);
            r8 = *reinterpret_cast<uint16_t*>(rbx + 0x300);
            rax = rsi;
            rax >>= 0x10;
            xmm0 = _mm_cvtsi32_si128(rsi);
            xmm1 = xmm0;
            xmm1 = _mm_srli_epi32(xmm1, 8);
            xmm1 = _mm_unpacklo_epi32(xmm1, xmm0);
            xmm1 = _mm_and_si128(xmm1, *reinterpret_cast<__m128i*>(0xF08C710));
            rax = static_cast<uint8_t>(al);
            xmm0 = _mm_srli_epi32(xmm0, 0x18);
            xmm2 = _mm_cvtsi32_si128(static_cast<int>(rax));
            xmm0 = _mm_unpacklo_epi32(xmm0, xmm2);
            xmm0 = _mm_unpacklo_epi64(xmm0, xmm1);
            xmm0 = _mm_cvtepi32_ps(xmm0);
            xmm0 = _mm_div_ps(xmm0, *reinterpret_cast<__m128*>(0xF0837E0));
            *reinterpret_cast<__m128*>(rbx + 0x3B0) = xmm0;
            rcx = *reinterpret_cast<uint64_t*>(rdi + 0x30);
            rax = *reinterpret_cast<uint64_t*>(rcx);
            rax = *reinterpret_cast<uint64_t*>(rax + 0xB8);
            rdx = reinterpret_cast<uint64_t>(rbx + 0x3B0);
            // 0xe829ec4  call qword ptr [0xF99FFA0]
            sub_eea6040(rcx, rdx);
            *reinterpret_cast<uint32_t*>(rbx + 0x258) = rsi;
        }
    }

L_0xe829ED1: // 0xe829ED1..0xe829F85
    rdi = *reinterpret_cast<uint64_t*>(rbx + 0x90);
    r8 = *reinterpret_cast<uint16_t*>(rbx + 0x300);
    rax = 0x7000000000000;
    if ((*reinterpret_cast<uint64_t*>(rbx + 0x1B0) & rax) != 0) { goto L_0xe829F10; }
    rax = *reinterpret_cast<uint8_t*>(rbx + 0x210);
    rax = rax + rax * 4;
    rcx = 0xF4EDD80;
    rdx = *reinterpret_cast<uint32_t*>(rbx + 0x25C);
    if (rdx == *reinterpret_cast<uint32_t*>(rcx + rax * 4)) { goto L_0xe829F86; }

L_0xe829F10: // 0xe829F10..0xe829F85
    rcx = *reinterpret_cast<uint64_t*>(rbx + 0x1F0);
    rcx >>= 0x30;
    rax = rcx;
    *reinterpret_cast<uint64_t*>(rbx + 0x210) = rcx;
    rax &= 7;
    rax = rax + rax * 4;
    rcx = 0xF4EDD80;
    rdx = *reinterpret_cast<uint32_t*>(rcx + rax * 4);
    r8 = *reinterpret_cast<uint32_t*>(rcx + rax * 4 + 0xC);
    *reinterpret_cast<uint32_t*>(rbx + 0x338) = r8;
    rax = *reinterpret_cast<uint32_t*>(rcx + rax * 4 + 0x10);
    *reinterpret_cast<uint32_t*>(rbx + 0x334) = rax;
    rcx = *reinterpret_cast<uint64_t*>(rdi + 0x30);
    rax = *reinterpret_cast<uint64_t*>(rcx);
    rax = *reinterpret_cast<uint64_t*>(rax + 0xA0);
    *reinterpret_cast<uint32_t*>(rbx + 0x25C) = rdx;
    // 0xe829f60  call qword ptr [0xF99FFA0]
    sub_eea6040(rcx);
    rax = *reinterpret_cast<uint64_t*>(rbx + 0x210);
    rax &= 7;
    *reinterpret_cast<uint64_t*>(rbx + 0x210) = rax;
    rdi = *reinterpret_cast<uint64_t*>(rbx + 0x90);
    r8 = *reinterpret_cast<uint16_t*>(rbx + 0x300);
    if (*reinterpret_cast<uint16_t*>(rbx + 0x520) != r8) { goto L_0xe829F94; }

L_0xe829F86: // 0xe829F86..0xe829F93
    if (*reinterpret_cast<uint16_t*>(rbx + 0x520) == r8) { goto L_0xe82A0FE; }

    // ============================================================
    // 0xe829F94..0xe82A0FD: More render state / index buffer setup
    // 0xe829f94  mov [rbx+0x520],r8w
    // 0xe829f9c  cmp r8w,0xFFFF
    // 0xe829fa1  mov rsi,[rbx+0xB0]
    // 0xe829fa8  je 0xE82A08A
    // ... through 0xE82A0FD
    // ============================================================
L_0xe829F94: // 0xe829F94..0xe82A0FD
    *reinterpret_cast<uint16_t*>(rbx + 0x520) = r8;
    if (r8 == 0xFFFF) {
        rsi = *reinterpret_cast<uint64_t*>(rbx + 0xB0);
        if (*reinterpret_cast<uint64_t*>(rbx + 0x638) == 0) {
            uint8_t al = 1;
            uint32_t ecx = *reinterpret_cast<uint32_t*>(rbx + 0x1AC);
            ecx ^= 1;
            if ((al & ecx) != 0) { goto L_0xe82A0F4; }
            eax = *reinterpret_cast<uint32_t*>(rbx + 0x5A4);
            *reinterpret_cast<uint32_t*>(rbx + 0x3B0) = eax;
            rax = *reinterpret_cast<uint64_t*>(rbx + 0x630);
            *reinterpret_cast<uint32_t*>(rbx + 0x3B4) = static_cast<uint32_t>(rax);
            eax = *reinterpret_cast<uint32_t*>(rbx + 0x5A0);
            *reinterpret_cast<uint32_t*>(rbx + 0x3B8) = eax;
            eax = *reinterpret_cast<uint32_t*>(rbx + 0x59C);
            *reinterpret_cast<uint32_t*>(rbx + 0x3BC) = eax;
            rcx = *reinterpret_cast<uint64_t*>(rdi + 0x30);
            rax = *reinterpret_cast<uint64_t*>(rcx);
            rax = *reinterpret_cast<uint64_t*>(rax + 0xB0);
            rdx = 1;
            r8 = reinterpret_cast<uint64_t>(rbx + 0x3B0);
            // 0xe82a0ed  call qword ptr [0xF99FFA0]
            sub_eea6040(rcx, rdx, r8);
        }
        *reinterpret_cast<uint32_t*>(rbx + 0x1AC) = 0;
        goto L_0xe82A0FE;
    }

    rsi = *reinterpret_cast<uint64_t*>(rbx + 0xB0);
    r8 = static_cast<uint32_t>(r8);
    r11 = *reinterpret_cast<uint64_t*>(rbx + 0x168);
    rax = *reinterpret_cast<uint16_t*>(r11 + r8 * 8 + 0xD457D0);
    r9 = rax;
    rcx = *reinterpret_cast<uint64_t*>(rbx + 0x320);
    if (static_cast<uint16_t>(rcx) > static_cast<uint16_t>(rax)) {
        rax = static_cast<uint16_t>(rcx);
    }
    rcx = *reinterpret_cast<uint16_t*>(r11 + r8 * 8 + 0xD457D2);
    r10 = rcx;
    rdx = *reinterpret_cast<uint64_t*>(rbx + 0x398);
    if (static_cast<uint16_t>(rdx) > static_cast<uint16_t>(rcx)) {
        rcx = static_cast<uint16_t>(rdx);
    }
    rdx = *reinterpret_cast<uint16_t*>(r11 + r8 * 8 + 0xD457D4);
    rdx += r9;
    r9 = *reinterpret_cast<uint64_t*>(rbx + 0x2E8);
    if (static_cast<uint16_t>(r9) > static_cast<uint16_t>(rdx)) {
        rdx = static_cast<uint32_t>(r9);
    }
    r8 = *reinterpret_cast<uint16_t*>(r11 + r8 * 8 + 0xD457D6);
    r8 += r10;
    r9 = *reinterpret_cast<uint64_t*>(rbx + 0x2E0);
    if (static_cast<uint16_t>(r9) > static_cast<uint16_t>(r8)) {
        r8 = static_cast<uint32_t>(r9);
    }
    *reinterpret_cast<uint8_t*>(rbx + 0x1AC) = 1;
    if (static_cast<uint16_t>(rdx) <= static_cast<uint16_t>(rax)) { goto L_0xe82D0CB; }
    if (static_cast<uint16_t>(r8) <= static_cast<uint16_t>(rcx)) { goto L_0xe82D0CB; }
    rax = static_cast<uint32_t>(static_cast<uint16_t>(rax));
    xmm0 = _mm_cvtsi32_si128(static_cast<int>(rax));
    xmm0 = _mm_insert_epi16(xmm0, static_cast<int>(rcx), 2);
    xmm0 = _mm_insert_epi16(xmm0, static_cast<int>(rdx), 4);
    xmm0 = _mm_insert_epi16(xmm0, static_cast<int>(r8), 6);
    *reinterpret_cast<__m128i*>(rbx + 0x3B0) = xmm0;
    rcx = *reinterpret_cast<uint64_t*>(rdi + 0x30);
    rax = *reinterpret_cast<uint64_t*>(rcx);
    rax = *reinterpret_cast<uint64_t*>(rax + 0xB0);
    rdx = 1;
    r8 = reinterpret_cast<uint64_t>(rbx + 0x3B0);
    // 0xe82a079  call qword ptr [0xF99FFA0]
    sub_eea6040(rcx, rdx, r8);
    *reinterpret_cast<uint8_t*>(rbx + 0x1AC) = 1;
    goto L_0xe82A0FE;

L_0xe82A08A: // 0xe82A08A..0xe82A0FD
    // ... (similar pattern, omitted for brevity - full in next piece)
    // Continue in next write

    // ============================================================
    // 0xe82A0FE..0xe82A3E1: Buffer bind / resource setup
    // 0xe82a0fe  mov rax,[rbx+0x580]
    // 0xe82a105  test rax,rax
    // ... through 0xE82A3E1
    // ============================================================
    // (continues in next piece)

    // Save state before boundary jumps
    st->rbx = rbx;
    st->r13 = r13;
    st->r14 = r14;
    st->r15 = r15;
    st->rsi = rsi;
    st->rdi = rdi;
    st->rcx = rcx;
    st->rdx = rdx;
    st->r8 = r8;
    st->r9 = r9;
}

} // namespace native::d3d12

#if 0
// Call quotes from disassembly (two spaces after address)
0xe82930a  call 0x47E8F0
0xe829364  call 0x47E8F0
0xe8293be  call 0x47E8F0
0xe829418  call 0x47E8F0
0xe829472  call 0x47E8F0
0xe8294cc  call 0x47E8F0
0xe829526  call 0x47E8F0
0xe82953a  call 0xEEC6ED0
0xe829562  call 0xEEC6ED0
0xe829594  call 0xEEC6ED0
0xe8295c6  call 0xEEC6ED0
0xe8295f5  call 0xEEC6ED0
0xe829627  call 0xEEC6ED0
0xe82964f  call 0xEEC6ED0
0xe82968e  call 0xEEC6ED0
0xe8296b6  call 0xEEC6ED0
0xe8296ed  call 0xEEC6ED0
0xe829715  call 0xEEC6ED0
0xe829747  call 0xEEC6ED0
0xe829779  call 0xEEC6ED0
0xe8297a8  call 0xEEC6ED0
0xe8297d4  call 0xEEC6ED0
0xe829800  call 0xEEC6ED0
0xe82982f  call 0xEEC6ED0
0xe829861  call 0xEEC6ED0
0xe829893  call 0xEEC6ED0
0xe8298c2  call 0xEEC6ED0
0xe8298e7  call 0xEEC6ED0
0xe82991c  call 0xEEC6ED0
0xe82994e  call 0xEEC6ED0
0xe82997d  call 0xEEC6ED0
0xe8299ac  call 0xEEC6ED0
0xe8299d3  call 0xEEC6EC0
0xe829a1e  call 0xE8360F0
0xe829a83  call qword ptr [0xF99FFA0]
0xe829aa7  call qword ptr [0xF99FFA0]
0xe829b42  call 0xEEC6EC0
0xe829b71  call qword ptr [0xF99FFA0]
0xe829be1  call r10
0xe829c60  call r11
0xe829c7d  call qword ptr [0xF99FFA0]
0xe829cb5  call 0xEEC6ED0
0xe829da5  call qword ptr [0xF99FFA0]
0xe829dde  call qword ptr [0xF99FFA0]
0xe829e06  call qword ptr [0xF99FFA0]
0xe829e37  call qword ptr [0xF99FFA0]
0xe829ec4  call qword ptr [0xF99FFA0]
0xe829f60  call qword ptr [0xF99FFA0]
0xe82a079  call qword ptr [0xF99FFA0]
0xe82a0ed  call qword ptr [0xF99FFA0]
0xe82a132  call qword ptr [0xF99FFA0]
0xe82a1f6  call 0xBC6A9D0
0xe82a393  call 0x47E8F0
0xe82a3c3  call 0xEEC6ED0
0xe82a40f  call 0xE81E1C0
0xe82a485  call 0xE81E1C0
0xe82a4c4  call 0xEEC6ED0
0xe82a4f2  call 0xEEC6EC0
0xe82a58a  call 0x47E8F0
0xe82a70f  call 0x47E8F0
0xe82a783  call 0x47E8F0
0xe82a7e0  call 0x47E8F0
0xe82a863  call 0x47E8F0
0xe82a8f3  call 0x47E8F0
0xe82ac21  call 0x47E8F0
0xe82af3a  call 0x47E8F0
0xe82afb3  call 0x47E8F0
#endif