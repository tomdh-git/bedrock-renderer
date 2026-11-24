// LIFT 0xbc60100 size 0x631 1.26.62.01 sub_bc60100
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc60100.h"

#include <cstddef>
#include <cstdint>
#include <intrin.h>

// Reversed from the disassembly of [0xbc60100, 0xbc60731), Minecraft Windows 1.26.62.01
// (rdis dis output). Every block carries the instruction range it implements as
// // 0xA..0xB beside it; every call is quoted verbatim in the verbatim log below.
//
// Layout ([V] from this body): the stack descriptors built at [rsp+0x28]/[rsp+0x30] and
// [rsp+0x38]/[rsp+0x40] are native::StrDesc { const char* ptr; uint32_t len; } values,
// passed by pointer to sub_ebce570. sub_ebce5e0(s, maxlen) returns the bounded length of s
// (0 if s is null); sub_ebce570(desc0, desc1, maxlen) returns 0 iff the two descriptors'
// strings are equal.
//
// Boundaries and lift-set callees:
//   sub_ebce5e0 x16 and sub_ebce570 x15 are lift-set callees
//   (docs/data/native_boundary.tsv, class lift), declared in sub_bc60100.h and called as
//   plain C++. sub_e951550 x1 is a boundary callee
//   (docs/data/native_boundary.tsv line 467, class crt): the /GS cookie-failure path.
//
// Verbatim log of every call instruction in [0xbc60100, 0xbc60731) (rdis dis output,
// copied verbatim, two spaces after the address):
#if 0
0xbc60169  call 0xEBCE5E0
0xbc60190  call 0xEBCE5E0
0xbc601ae  call 0xEBCE570
0xbc601ee  call 0xEBCE5E0
0xbc6021d  call 0xEBCE570
0xbc60246  call 0xEBCE5E0
0xbc60275  call 0xEBCE570
0xbc6029e  call 0xEBCE5E0
0xbc602cd  call 0xEBCE570
0xbc602f6  call 0xEBCE5E0
0xbc60325  call 0xEBCE570
0xbc6034e  call 0xEBCE5E0
0xbc6037d  call 0xEBCE570
0xbc603a6  call 0xEBCE5E0
0xbc603d5  call 0xEBCE570
0xbc603fe  call 0xEBCE5E0
0xbc6042d  call 0xEBCE570
0xbc60456  call 0xEBCE5E0
0xbc60485  call 0xEBCE570
0xbc604ae  call 0xEBCE5E0
0xbc604dd  call 0xEBCE570
0xbc60506  call 0xEBCE5E0
0xbc60535  call 0xEBCE570
0xbc6055e  call 0xEBCE5E0
0xbc6058d  call 0xEBCE570
0xbc605b6  call 0xEBCE5E0
0xbc605e5  call 0xEBCE570
0xbc6060e  call 0xEBCE5E0
0xbc6063d  call 0xEBCE570
0xbc60666  call 0xEBCE5E0
0xbc60695  call 0xEBCE570
0xbc6072b  call 0xE951550
#endif
// UNRESOLVED CALL = none: every target above is lift-set (sub_ebce5e0/sub_ebce570) or
// boundary (sub_e951550, class crt).

extern "C" void sub_e951550(uintptr_t cookie);   // boundary crt; cookie-failure path terminates

// Layout assertions (full set in sub_bc60100.h; repeated here so liftcheck sees them).
static_assert(offsetof(native::StrDesc, ptr) == 0x00, "sub_0xbc60100: descriptor ptr at +0x00");
static_assert(offsetof(native::StrDesc, len) == 0x08, "sub_0xbc60100: descriptor len at +0x08");
static_assert(sizeof(native::StrDesc) == 0x10, "sub_0xbc60100: descriptor size 0x10");

namespace native::bgfx {

int sub_bc60100(const char* name) {
    // 0xbc60100..0xbc60144: prologue, /GS cookie guard, and loop setup.
    //   0xbc6010f  mov rax,[0x1230A0C0]
    //   0xbc60116  xor rax,rsp
    //   0xbc60119  mov [rsp+0x48],rax
    //   0xbc6011e  lea r12,[0xF847A07]
    //   0xbc60125  test rcx,rcx
    //   0xbc60128  je short 0xBC601D2
    //   0xbc6012e  mov rdi,rcx
    //   0xbc60131  lea r13,[0xF4418C0]
    //   0xbc60138  xor esi,esi
    //   0xbc6013a  lea rbx,[rsp+0x28]
    //   0xbc6013f  lea r14,[rsp+0x38]
    //   0xbc60144  nop [rax+rax]
    uintptr_t cookie = *reinterpret_cast<uintptr_t*>(0x141230A0C0ULL);
    uintptr_t guardSlot = cookie ^ reinterpret_cast<uintptr_t>(&guardSlot);
    const char* const empty = reinterpret_cast<const char*>(0x14F847A07ULL);
    const char* const* table = reinterpret_cast<const char* const*>(0x14F4418C0ULL);

    if (name == 0) {
        // 0xbc601d2..0xbc606a5: null-name path. "" vs each literal; all fail -> 14.
        // One call pair per literal: strnlen(lit) then strcmp("", lit), in the same order
        // as the literal chain 0xbc601d2 .. 0xbc606a5.
        StrDesc desc0 = { empty, 0 };
        for (int k = 0; k < 0xE; ++k) {
            StrDesc desc1 = { empty, 0 };
            desc1.len = sub_ebce5e0(table[k], 0x7FFFFFFF);   // strnlen(table[k], 0x7FFFFFFF)
            if (desc1.len != 0)
                desc1.ptr = table[k];
            if (sub_ebce570(&desc0, &desc1, 0x7FFFFFFF) == 0)   // strcmp(desc0, desc1, 0x7FFFFFFF); je -> esi = k
                return k;   // never taken: every literal is non-empty, so "" never matches
        }
        // 0xbc6069a  cmp eax,1; 0xbc6069d  mov esi,0xE; 0xbc606a2  sbb esi,0  (eax != 0 -> 14)
        return 14;
    }

    int result = 0;
    int index = 0;
    // 0xbc60150..0xbc601cd: scan table[0..13] for the first entry equal to name.
    // One iteration: strnlen(table[index]), strnlen(name), strcmp(desc(name), desc(table[index])).
    //   0xbc60150  mov r15,[r13]; back-edge 0xbc601c6  jne short 0xBC60150
    for (;;) {
        const char* entry = table[index];   // 0xbc60150  mov r15,[r13]
        StrDesc desc1 = { empty, 0 };
        desc1.len = sub_ebce5e0(entry, 0x7FFFFFFF);   // strnlen(entry, 0x7FFFFFFF)
        if (desc1.len != 0)
            desc1.ptr = entry;
        StrDesc desc0 = { empty, 0 };
        desc0.len = sub_ebce5e0(name, 0x7FFFFFFF);   // strnlen(name, 0x7FFFFFFF)
        if (desc0.len != 0)
            desc0.ptr = name;
        if (sub_ebce570(&desc0, &desc1, 0x7FFFFFFF) == 0) {   // strcmp(...); je 0xBC606FD -> esi = index
            result = index;
            goto done;
        }
        //   0xbc601bb  inc rsi; 0xbc601c2  cmp rsi,0xE; 0xbc601c6  jne short 0xBC60150
        if (++index == 0xE) {   // 0xbc601c8  mov esi,0xE
            result = 14;
            goto done;
        }
    }

done:
    // 0xbc606a7..0xbc606f8: match blocks (esi = 0..13), fall through to the check.
    // 0xbc606fd..0xbc60730: /GS cookie verification and return.
    //   0xbc606fd  mov rax,[rsp+0x48]; 0xbc60702  xor rax,rsp
    //   0xbc60705  mov rcx,[0x1230A0C0]; 0xbc6070c  cmp rcx,rax; 0xbc6070f  jne short 0xBC60723
    if ((guardSlot ^ reinterpret_cast<uintptr_t>(&guardSlot)) != cookie) {
        //   0xbc60723  mov rcx,[rsp+0x48]; 0xbc60728  xor rcx,rsp; 0xbc6072b  call 0xE951550
        sub_e951550(cookie);
        //   0xbc60730  int3  (unreachable)
        __assume(false);
    }
    //   0xbc60711  mov eax,esi; 0xbc60713  add rsp,0x50; pop rbx/rdi/rsi/r12/r13/r14/r15; 0xbc60722  ret
    return result;
}

LIFT_FN(sub_bc60100, "sub_bc60100", 0xbc60100, sub_bc60100, nullptr);

} // namespace native::bgfx
