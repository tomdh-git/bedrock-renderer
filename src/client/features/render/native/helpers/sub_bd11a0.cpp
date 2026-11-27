// LIFT 0xbd11a0 size 0x133 1.26.62.01 sub_bd11a0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_bd11a0.h"

#include <cstdint>
#include <cstddef>

namespace native::helpers {

// Layout static_asserts for the dereferenced state structs (offsets match the
// disassembly evidence; see sub_bd11a0.h for the field declarations).
static_assert(offsetof(sub_bd11a0_rcx, f10) == 0x10, "rcx+0x10");
static_assert(offsetof(sub_bd11a0_rcx, f18) == 0x18, "rcx+0x18");
static_assert(offsetof(sub_bd11a0_r8, f48) == 0x48, "r8+0x48");
static_assert(offsetof(sub_bd11a0_r8, f50) == 0x50, "r8+0x50");
static_assert(offsetof(sub_bd11a0_r8, f68) == 0x68, "r8+0x68");
static_assert(offsetof(sub_bd11a0_r8, f70) == 0x70, "r8+0x70");
static_assert(offsetof(sub_bd11a0_r10, f0) == 0x0, "r10+0x0");

LIFT_FN(sub_bd11a0, "sub_bd11a0", 0xbd11a0, sub_bd11a0, nullptr);

// Verbatim call instructions from the disassembly of [0xbd11a0, 0xbd12d3) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xbd12cd  call 0x78ED0
#endif

// External references used by the lifted function.
// sub_78ed0 is the boundary=crt callee reached on every validation-failure path
// (the exe follows it with int3, i.e. it does not return normally).
// data_129726B0 is the absolute-data global compared at 0xbd12b7 / 0xbd13b7.
extern void sub_78ed0();
extern std::uint32_t data_129726B0;

// Ranges: every instruction of [0xbd11a0, 0xbd12d3) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

uintptr_t sub_bd11a0(void* self, std::uint32_t edx) {
    // 0xbd11a0..0xbd11d0: basic block 0
    // 0xbd11a0  sub rsp,0x28
    // 0xbd11a4  mov r8,[rcx+0x10]
    // 0xbd11a8  mov eax,[rcx+0x18]
    // 0xbd11ab  mov rcx,[r8+0x48]
    // 0xbd11af  mov r9,[r8+0x50]
    // 0xbd11b3  sub r9,rcx
    // 0xbd11b6  shr r9,3
    // 0xbd11ba  dec r9d
    // 0xbd11bd  and r9d,0xE6A1B550
    // 0xbd11c4  lea r10,[rcx+r9*8]
    // 0xbd11c8  mov rcx,[r8+0x68]
    // 0xbd11cc  nop [rax]     (alignment NOP, no architectural effect)
    // -> if fallthrough goto L_0xbd11d0
    sub_bd11a0_rcx* a0 = reinterpret_cast<sub_bd11a0_rcx*>(self);
    sub_bd11a0_r8* r8obj = reinterpret_cast<sub_bd11a0_r8*>(a0->f10);          // 0xbd11a4
    std::uint32_t eax = a0->f18;                                                // 0xbd11a8
    sub_bd11a0_rcx* rcx = reinterpret_cast<sub_bd11a0_rcx*>(r8obj->f48);       // 0xbd11ab
    std::uint64_t r9 = r8obj->f50;                                              // 0xbd11af
    r9 = (r9 - reinterpret_cast<std::uintptr_t>(rcx)) >> 3;                     // 0xbd11b3, 0xbd11b6
    r9 = static_cast<std::uint64_t>(static_cast<std::uint32_t>(r9) - 1u);       // 0xbd11ba
    r9 = static_cast<std::uint64_t>(static_cast<std::uint32_t>(r9) & 0xE6A1B550u); // 0xbd11bd
    sub_bd11a0_r10* r10 = reinterpret_cast<sub_bd11a0_r10*>(
        reinterpret_cast<std::uint8_t*>(rcx) + r9 * 8);                         // 0xbd11c4
    std::uint8_t* second_base = reinterpret_cast<std::uint8_t*>(r8obj->f68);    // 0xbd11c8
    std::uint64_t r9_shl = 0;                                                   // 0xbd11dd (assigned in block 2)
    // 0xbd11cc nop [rax] - no effect

    // 0xbd11d0..0xbd11dd: basic block 1
    // 0xbd11d0  mov r9,[r10]
    // 0xbd11d3  cmp r9,0xFFFFFFFFFFFFFFFF
    // 0xbd11d7  je 0xBD12CD
    // -> if r9 == -1 goto L_0xbd12cd
    // -> if r9 != -1 goto L_0xbd11dd
    L_0xbd11d0:;
    std::uint64_t r9_val = r10->f0;                                             // 0xbd11d0
    if (r9_val == 0xFFFFFFFFFFFFFFFFull) goto L_0xbd12cd;                      // 0xbd11d3-0xbd11d7

    // 0xbd11dd..0xbd11f0: basic block 2
    // 0xbd11dd  shl r9,5
    // 0xbd11e1  lea r10,[rcx+r9]
    // 0xbd11e5  cmp dword ptr [rcx+r9+8],0xE6A1B550
    // 0xbd11ee  jne short 0xBD11D0
    // -> if [second_base+r9+8] != 0xE6A1B550 goto L_0xbd11d0
    // -> if [second_base+r9+8] == 0xE6A1B550 goto L_0xbd11f0
    r9_shl = r9_val << 5;                                                       // 0xbd11dd
    r10 = reinterpret_cast<sub_bd11a0_r10*>(second_base + r9_shl);              // 0xbd11e1
    if (*reinterpret_cast<std::uint32_t*>(second_base + r9_shl + 8) != 0xE6A1B550u) // 0xbd11e5
        goto L_0xbd11d0;                                                        // 0xbd11ee

    // 0xbd11f0..0xbd11fd: basic block 3
    // 0xbd11f0  add rcx,r9
    // 0xbd11f3  cmp [r8+0x70],rcx
    // 0xbd11f7  je 0xBD12CD
    // -> if [r8+0x70] == second_base+r9_shl goto L_0xbd12cd
    // -> if [r8+0x70] != second_base+r9_shl goto L_0xbd11fd
    {
        std::uint8_t* rcx_ptr = second_base + r9_shl;                           // 0xbd11f0 (rcx = second_base + r9)
        if (*reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint8_t*>(r8obj) + 0x70) ==
            reinterpret_cast<std::uint64_t>(rcx_ptr)) goto L_0xbd12cd;         // 0xbd11f3-0xbd11f7

        // 0xbd11fd..0xbd120a: basic block 4
        // 0xbd11fd  mov rcx,[rcx+0x10]
        // 0xbd1201  test rcx,rcx
        // 0xbd1204  je 0xBD12CD
        // -> if [rcx_ptr+0x10] == 0 goto L_0xbd12cd
        // -> if [rcx_ptr+0x10] != 0 goto L_0xbd120a
        rcx = reinterpret_cast<sub_bd11a0_rcx*>(*reinterpret_cast<void**>(
            rcx_ptr + 0x10));                                                   // 0xbd11fd
        if (!rcx) goto L_0xbd12cd;                                              // 0xbd1201-0xbd1204

        // 0xbd120a..0xbd1233: basic block 5
        // 0xbd120a  mov r8d,eax
        // 0xbd120d  and r8d,0x3FFFF
        // 0xbd1214  mov r9d,r8d
        // 0xbd1217  shr r9d,0xB
        // 0xbd121b  mov r10,[rcx+8]
        // 0xbd121f  mov r11,[rcx+0x10]
        // 0xbd1223  sub r11,r10
        // 0xbd1226  sar r11,3
        // 0xbd122a  cmp r9,r11
        // 0xbd122d  jae 0xBD12CD
        // -> if r9d >= count goto L_0xbd12cd
        // -> if r9d < count goto L_0xbd1233
        L_0xbd120a:;
        std::uint32_t r8d = eax & 0x3FFFFu;                                     // 0xbd120a-0xbd120d
        std::uint32_t r9d = r8d >> 0xBu;                                        // 0xbd1214-0xbd1217
        void* r10b = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rcx) + 8);   // 0xbd121b
        void* r11v = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rcx) + 0x10); // 0xbd121f
        std::int64_t count = (reinterpret_cast<std::intptr_t>(r11v) - reinterpret_cast<std::intptr_t>(r10b)) >> 3; // 0xbd1223-0xbd1226
        if (r9d >= static_cast<std::uint32_t>(count)) goto L_0xbd12cd;          // 0xbd122a-0xbd122d

        // 0xbd1233..0xbd1240: basic block 6
        // 0xbd1233  mov r9,[r10+r9*8]
        // 0xbd1237  test r9,r9
        // 0xbd123a  je 0xBD12CD
        // -> if [r10b+r9d*8] == 0 goto L_0xbd12cd
        // -> if [r10b+r9d*8] != 0 goto L_0xbd1240
        L_0xbd1233:;
        std::uint64_t r9v = *reinterpret_cast<std::uint64_t*>(
            reinterpret_cast<std::uint8_t*>(r10b) + r9d * 8);                   // 0xbd1233
        if (!r9v) goto L_0xbd12cd;                                              // 0xbd1237-0xbd123a

        // 0xbd1240..0xbd125a: basic block 7
        // 0xbd1240  and r8d,0x7FF
        // 0xbd1247  and eax,0xFFFC0000
        // 0xbd124c  mov r8d,[r9+r8*4]
        // 0xbd1250  xor eax,r8d
        // 0xbd1253  cmp eax,0x3FFFE
        // 0xbd1258  ja short 0xBD12CD
        // -> if eax >u 0x3FFFE goto L_0xbd12cd
        // -> if eax <=u 0x3FFFE goto L_0xbd125a
        L_0xbd1240:;
        std::uint32_t r8d2 = r8d & 0x7FFu;                                      // 0xbd1240
        std::uint32_t eax2 = eax & 0xFFFC0000u;                                 // 0xbd1247
        std::uint32_t r8d3 = *reinterpret_cast<std::uint32_t*>(
            reinterpret_cast<std::uint8_t*>(r9v) + r8d2 * 4);                   // 0xbd124c
        std::uint32_t eax3 = eax2 ^ r8d3;                                       // 0xbd1250
        if (eax3 > 0x3FFFEu) goto L_0xbd12cd;                                   // 0xbd1253-0xbd1258

        // 0xbd125a..0xbd1273: basic block 8
        // 0xbd125a  mov rax,[rcx+0x50]
        // 0xbd125e  mov ecx,r8d
        // 0xbd1261  shr ecx,4
        // 0xbd1264  and ecx,0x3FF8
        // 0xbd126a  mov rcx,[rax+rcx]
        // 0xbd126e  test rcx,rcx
        // 0xbd1271  je short 0xBD12CD
        // -> if [rax+ecx] == 0 goto L_0xbd12cd
        // -> if [rax+ecx] != 0 goto L_0xbd1273
        L_0xbd125a:;
        void* rax = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rcx) + 0x50); // 0xbd125a
        std::uint32_t ecx3 = (r8d3 >> 4) & 0x3FF8u;                             // 0xbd125e-0xbd1264
        void* rcx4 = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rax) + ecx3); // 0xbd126a
        if (!rcx4) goto L_0xbd12cd;                                             // 0xbd126e-0xbd1271

        // 0xbd1273..0xbd12a7: basic block 9
        // 0xbd1273  and r8d,0x3FFFF
        // 0xbd127a  and r8d,0x7F
        // 0xbd127e  lea r8,[r8+r8*2]
        // 0xbd1282  mov rax,[rcx+r8*8]
        // 0xbd1286  mov rcx,[rcx+r8*8+8]
        // 0xbd128b  sub rcx,rax
        // 0xbd128e  sar rcx,3
        // 0xbd1292  mov r8,0xCF3CF3CF3CF3CF3D
        // 0xbd129c  imul r8,rcx
        // 0xbd12a0  mov ecx,edx
        // 0xbd12a2  cmp r8,rcx
        // 0xbd12a5  jbe short 0xBD12C6
        // -> if r8 <=u edx goto L_0xbd12c6
        // -> if r8 >u edx goto L_0xbd12a7
        L_0xbd1273:;
        std::uint32_t r8d4 = (r8d3 & 0x3FFFFu) & 0x7Fu;                         // 0xbd1273-0xbd127a
        std::uint64_t r8idx = static_cast<std::uint64_t>(r8d4) * 3u;            // 0xbd127e
        std::uint64_t rax2 = *reinterpret_cast<std::uint64_t*>(
            reinterpret_cast<std::uint8_t*>(rcx4) + r8idx * 8);                 // 0xbd1282
        std::uint64_t rcx5 = *reinterpret_cast<std::uint64_t*>(
            reinterpret_cast<std::uint8_t*>(rcx4) + r8idx * 8 + 8);             // 0xbd1286
        std::int64_t rcx6 = (static_cast<std::int64_t>(rcx5) - static_cast<std::int64_t>(rax2)) >> 3; // 0xbd128b-0xbd128e
        std::uint64_t r8big = 0xCF3CF3CF3CF3CF3Dull * static_cast<std::uint64_t>(rcx6); // 0xbd1292-0xbd129c
        // 0xbd12a0 mov ecx,edx
        if (r8big <= static_cast<std::uint64_t>(edx)) goto L_0xbd12c6;          // 0xbd12a2-0xbd12a5

        // 0xbd12a7..0xbd12c6: basic block 10
        // 0xbd12a7  imul rcx,0xA8
        // 0xbd12ae  lea rdx,[rax+rcx]
        // 0xbd12b2  mov ecx,[rax+rcx]
        // 0xbd12b5  xor eax,eax
        // 0xbd12b7  cmp ecx,[0x129726B0]
        // 0xbd12bd  cmovne rax,rdx
        // 0xbd12c1  add rsp,0x28
        // 0xbd12c5  ret
        L_0xbd12a7:;
        rcx6 = rcx6 * 0xA8;                                                     // 0xbd12a7
        std::uint8_t* rdx_ptr = reinterpret_cast<std::uint8_t*>(rax2) + static_cast<std::uint64_t>(rcx6); // 0xbd12ae
        std::uint32_t ecx4 = *reinterpret_cast<std::uint32_t*>(rdx_ptr);        // 0xbd12b2
        std::uintptr_t ret = 0;                                                 // 0xbd12b5
        if (ecx4 != data_129726B0) ret = reinterpret_cast<std::uintptr_t>(rdx_ptr); // 0xbd12b7-0xbd12bd cmovne
        return ret;                                                             // 0xbd12c1-0xbd12c5
    }

L_0xbd12c6:;                                                                    // basic block 11
    // 0xbd12c6  xor eax,eax
    // 0xbd12c8  add rsp,0x28
    // 0xbd12cc  ret
    return 0;

L_0xbd12cd:;                                                                    // basic block 12
    // 0xbd12cd  call 0x78ED0
    // 0xbd12d2  int3 (unreachable)
    sub_78ed0();
    return 0;                                                                   // unreachable; int3 follows in the exe
}

} // namespace native::helpers
