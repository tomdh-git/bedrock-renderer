// LIFT 0x66a17c0 size 0x51 1.26.62.01 sub_66a17c0
#include "client/features/render/native/framebuilder/sub_66a17c0.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>

namespace native {

// sub_66a17c0 (0x66a17c0, size 0x51, 1.26.62.01, "Item group visitor").
//
// Given a source pair [a1+0x0, a1+0x8) of 16-byte items, writes to *a0:
//   a0+0x0 = 0xAAAAAAAAAAAAAAAB * (((a1+0x8) - (a1+0x0)) >> 4)   ; scaled item count
//   a0+0x8 = a1+0x0                                              ; source start
// and returns a0. On either of two sentinel/failure conditions
//   (a1+0x8 - a1+0x0 == 0xFFFFFFFFFFFFFFD0) or (a1+0x0 == 0 && a1+0x8 != 0)
// it calls sub_78ed0 (class crt boundary, noreturn) with RCX = a0 and never
// returns (the original breaks into int3 at 0x66a1810).
//
// Same reads, same writes (value and order), same call, same return. No null
// guard or SEH (the original has none; none added here). [V] every instruction
// line below, from the exe disassembly of [0x66a17c0, 0x66a1811).

// Boundary callee, class crt (docs/data/native_boundary.tsv line 11).
// 0x78ed0 itself: `sub rsp,0x28 / call qword ptr [0xF9A8CF0]` then int3
// padding; noreturn, never reaches a ret [V]. Called with RCX = a0 exactly as
// the original has it at the call site (rcx is untouched between entry and the
// call) [V]. Same wrapper precedent as sub_66a1820 (0x66a1850 call 0x78ED0
// with rcx = a0).
native::Boundary<void, std::uintptr_t> sub_78ed0("sub_78ed0");

// 0x66a17c0..0x66a17c7: sub rsp,0x28 / mov r8,[rdx] / mov rax,[rdx+8]
uint64_t* sub_66a17c0(uint64_t* a0, uint64_t* a1) {
    const std::uint64_t start = a1[0];                   // 0x66a17c4 mov r8,[rdx]      ; R a1+0x0 (start)
    const std::uint64_t end   = a1[1];                   // 0x66a17c7 mov rax,[rdx+8]   ; R a1+0x8 (end)
    // 0x66a17cb..0x66a17e2: mov rdx,rax / sub rdx,r8 / mov r9,rdx / sar r9,4 / mov r10,magic / imul r10,r9
    const std::uint64_t diff  = end - start;             // 0x66a17cb..0x66a17d1   ; diff = end - start
    const std::int64_t  r9    = (std::int64_t)diff >> 4; // 0x66a17d4 sar r9,4     ; arithmetic shift = diff/16
    const std::uint64_t scaled= 0xAAAAAAAAAAAAAAABULL * (std::uint64_t)r9; // 0x66a17d8 mov r10,magic / 0x66a17e2 imul r10,r9
    // 0x66a17e6 mov [rcx],r10 ; W a0+0x0
    a0[0] = scaled;                                      // 0x66a17e6 mov [rcx],r10   ; W a0+0x0 = scaled
    // 0x66a17e9..0x66a17ed: cmp rdx,0xFFFFFFFFFFFFFFD0 / je short 0x66a180b (taken -> fail)
    if (diff != 0xFFFFFFFFFFFFFFD0ULL) {                 // 0x66a17e9 cmp rdx,... / 0x66a17ed je -> fail
        // 0x66a17ef mov [rcx+8],r8 ; W a0+0x8
        a0[1] = start;                                   // 0x66a17ef mov [rcx+8],r8  ; W a0+0x8 = start
        // 0x66a17f3..0x66a1801: test r8,r8 / setne dl / test rax,rax / sete al / or al,dl / je short 0x66a180b
        // fail when al==0, i.e. start==0 && end!=0; otherwise fall through to return a0
        if (!(start == 0 && end != 0)) return a0;        // 0x66a17f3..0x66a1801 test/setne/sete/or/je ; 0x66a1803 mov rax,rcx -> return a0
    }
// 0x66a180b..0x66a1811: call 0x78ED0 / int3 (unreachable)
fail:
    // 0x66a180b  call 0x78ED0   ; sub_78ed0 (crt boundary, noreturn); RCX = a0
    sub_78ed0(reinterpret_cast<std::uintptr_t>(a0));     // 0x66a180b  call 0x78ED0
    // 0x66a1810  int3           ; unreachable: sub_78ed0 never returns (thunk ends in int3 padding)
    return a0;                                           // unreachable: the original breaks into int3 at 0x66a1810
}

// Verbatim instructions of the function (matches `rdis dis 0x66a17c0 0x51` from the exe,
// machine-checked with tools/sigs/verify_oc.py):
#if 0
0x66a17c0  sub rsp,0x28
0x66a17c4  mov r8,[rdx]
0x66a17c7  mov rax,[rdx+8]
0x66a17cb  mov rdx,rax
0x66a17ce  sub rdx,r8
0x66a17d1  mov r9,rdx
0x66a17d4  sar r9,4
0x66a17d8  mov r10,0xAAAAAAAAAAAAAAAB
0x66a17e2  imul r10,r9
0x66a17e6  mov [rcx],r10
0x66a17e9  cmp rdx,0xFFFFFFFFFFFFFFD0
0x66a17ed  je short 0x66A180B
0x66a17ef  mov [rcx+8],r8
0x66a17f3  test r8,r8
0x66a17f6  setne dl
0x66a17f9  test rax,rax
0x66a17fc  sete al
0x66a17ff  or al,dl
0x66a1801  je short 0x66a180B
0x66a1803  mov rax,rcx
0x66a1806  add rsp,0x28
0x66a180a  ret
0x66a180b  call 0x78ED0
0x66a1810  int3
#endif

static native::Footprint sub_66a17c0Footprint(uint64_t* a0, uint64_t* /*a1*/) {
    return {{a0, 0x10}}; // every byte the function writes: a0+0x0 (always) and a0+0x8 (success path) [V]
}

LIFT_FN(sub_66a17c0, "sub_66a17c0", 0x66a17c0, sub_66a17c0, sub_66a17c0Footprint);

} // namespace native
