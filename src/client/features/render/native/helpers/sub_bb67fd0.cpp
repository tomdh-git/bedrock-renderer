// LIFT 0xbb67fd0 size 0xef 1.26.62.01 sub_bb67fd0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_bb67fd0.h"

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_bb67fd0, "sub_bb67fd0", 0xbb67fd0, sub_bb67fd0, nullptr);

// Verbatim call instructions from the disassembly of [0xbb67fd0, 0xbb680bf)
// (rdis fn output). Plain lines, two spaces after the address.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xbb6803e  call 0x1197A0
0xbb68074  call 0x1197A0
0xbb680a8  call 0x1197A0
#endif

// Layout assertions for the state structs (definitions live in sub_bb67fd0.h;
// repeated here so liftcheck sees them in the source file).
static_assert(offsetof(SubBb67fd0State, buffer) == 0x0, "sub_bb67fd0 state+0x00 field");
static_assert(offsetof(SubBb67fd0State, cur) == 0x8, "sub_bb67fd0 state+0x08 field");
static_assert(offsetof(SubBb67fd0State, end) == 0x10, "sub_bb67fd0 state+0x10 field");
static_assert(sizeof(SubBb67fd0State) == 0x18, "sub_bb67fd0 state size");
static_assert(offsetof(SubBb67fd0SrcRange, begin) == 0x20, "sub_bb67fd0 src+0x20 field");
static_assert(offsetof(SubBb67fd0SrcRange, end) == 0x28, "sub_bb67fd0 src+0x28 field");
static_assert(sizeof(SubBb67fd0SrcRange) == 0x30, "sub_bb67fd0 src size");
static_assert(offsetof(SubBb67fd0Block, data) == 0x130, "sub_bb67fd0 block+0x130 field");
static_assert(offsetof(SubBb67fd0Block, flag) == 0x140, "sub_bb67fd0 block+0x140 field");
static_assert(sizeof(SubBb67fd0Block) == 0x141, "sub_bb67fd0 block size");

// 0xbb67fd0..0xbb680bf - whole function, block by block:
//   0xbb67fd0..0xbb6800f: prologue (pushes, sub rsp,0x48, lea rbp,
//                          mov [rbp],-2 dead frame slot, mov rsi,r9, mov rdi,r8,
//                          state->buffer/cur/end = 0, src range load, scratch lea,
//                          self spill [rbp-8]) - implicit in the C++ frame.
//   0xbb6800f..0xbb68010: nop fallthrough (no statement).
//   0xbb68010..0xbb6801c: inline chunk copy: *cur = [r14]; cur += 0x10.
//   0xbb6801c..0xbb68024: r14 += 0x10; rcx = self.
//   0xbb68024..0xbb68029: loop head: while (r14 != r15).
//   0xbb68029..0xbb6803b: chunk -> scratch; cur = state->cur; if (cur != end) inline,
//                        else call sub_1197a0(state, cur, scratch, a3).
//   0xbb6803b..0xbb68046: call sub_1197a0(path; r8 = scratch).
//   0xbb68046..0xbb6804f: if (a2->flag != 0) { a2 += 0x130; ... }
//   0xbb6804f..0xbb68064: cur = state->cur; if (cur != end) inline, else call.
//   0xbb68064..0xbb68071: inline copy of a2+0x130 chunk; cur += 0x10.
//   0xbb68071..0xbb6807a: call sub_1197a0(state, cur, a2+0x130, a3).
//   0xbb6807a..0xbb68083: if (a3->flag == 1) { a3 += 0x130; ... }
//   0xbb68083..0xbb68098: cur = state->cur; if (cur != end) inline, else call.
//   0xbb68098..0xbb680a5: inline copy of a3+0x130 chunk; cur += 0x10.
//   0xbb680a5..0xbb680ae: call sub_1197a0(state, cur, a3+0x130, a3).
//   0xbb680ae..0xbb680bf: return self.
SubBb67fd0State* sub_bb67fd0(SubBb67fd0State* self, SubBb67fd0SrcRange* src,
                             SubBb67fd0Block* a2, SubBb67fd0Block* a3)
{
    // 0xbb67fd0..0xbb6800f: prologue/initialization (frame setup implicit)
    SubBb67fd0State* const state = self;
    SubBb67fd0Block* const blkA2 = a2;
    SubBb67fd0Block* const blkA3 = a3;

    // 0xbb67fef  xorps xmm0,xmm0
    // 0xbb67ff2  movups [rcx],xmm0   -> state->buffer = 0, state->cur = 0
    // 0xbb67ff5  mov qword ptr [rcx+0x10],0  -> state->end = 0
    state->buffer = nullptr;  // 0xbb67ff2 movups [rcx] (+0x00)
    state->cur = nullptr;     // 0xbb67ff2 movups [rcx] (+0x08)
    state->end = nullptr;     // 0xbb67ff5 [rcx+0x10] = 0

    // 0xbb67ffd  mov r14,[rdx+0x20];  0xbb68001  mov r15,[rdx+0x28]
    const std::uint8_t* const srcBegin =
        reinterpret_cast<const std::uint8_t*>(src->begin);
    const std::uint8_t* const srcEnd =
        reinterpret_cast<const std::uint8_t*>(src->end);

    // 0xbb68005  lea rbx,[rbp-0x20]   16-byte scratch chunk at [rbp-0x20]
    std::uint8_t stackBuf[16];

    // 0xbb68009  mov [rbp-8],rcx      (self spill; reloaded as rcx at each loop head)
    // 0xbb6800d  jmp short 0xBB68024  (enter at the loop head)
    std::uint8_t* curSrc = const_cast<std::uint8_t*>(srcBegin);
    while (curSrc != srcEnd) {  // 0xbb68024 cmp r14,r15;  0xbb68027 je -> 0xbb68046

        // 0xbb68029  movups xmm0,[r14];
        // 0xbb6802d  movaps [rbp-0x20],xmm0   (scratch = chunk, before the cur/end test)
        std::memcpy(stackBuf, curSrc, 16);

        // 0xbb68031  mov rdx,[rcx+8];
        // 0xbb68035  cmp rdx,[rcx+0x10];
        // 0xbb68039  jne -> 0xbb68010 (inline copy) /  0xbb6803b  mov r8,rbx
        //          0xbb6803e  call 0x1197A0  (RCX=self, RDX=cur, R8=scratch, R9=a3)
        std::uint8_t* cur = reinterpret_cast<std::uint8_t*>(state->cur);
        if (cur != reinterpret_cast<std::uint8_t*>(state->end)) {
            // 0xbb68010..0xbb6801c: inline copy path
            // 0xbb68010  movups xmm0,[r14]   (chunk reloaded from src)
            // 0xbb68014  movups [rdx],xmm0   (*cur = chunk)
            // 0xbb68017  add qword ptr [rcx+8],0x10   (state->cur += 0x10)
            std::memcpy(cur, curSrc, 16);
            state->cur = reinterpret_cast<void*>(cur + 16);
        } else {
            // 0xbb6803b..0xbb68046: flush path
            // 0xbb6803e  call 0x1197A0
            sub_1197a0(state, cur, stackBuf, blkA3);
        }

        // 0xbb6801c  add r14,0x10;  0xbb68020  mov rcx,[rbp-8]
        curSrc += 16;
    }

    // 0xbb68046  cmp byte ptr [rdi+0x140],0;  0xbb6804d  je -> 0xbb6807a
    if (blkA2->flag != 0) {  // 0xbb68046/0xbb6804d
        // 0xbb6804f  add rdi,0x130   chunk address is a2+0x130
        const std::uint8_t* const ptr = blkA2->data;

        // 0xbb68056  mov rcx,[rbp-8];
        // 0xbb6805a  mov rdx,[rcx+8];
        // 0xbb6805e  cmp rdx,[rcx+0x10];
        // 0xbb68062  je -> 0xbb68071 (call path) /  0xbb68064 inline copy
        std::uint8_t* cur = reinterpret_cast<std::uint8_t*>(state->cur);
        if (cur != reinterpret_cast<std::uint8_t*>(state->end)) {
            // 0xbb68064..0xbb68071: inline copy path
            // 0xbb68064  movups xmm0,[rdi];
            // 0xbb68067  movups [rdx],xmm0;
            // 0xbb6806a  add qword ptr [rcx+8],0x10
            std::memcpy(cur, ptr, 16);
            state->cur = reinterpret_cast<void*>(cur + 16);
        } else {
            // 0xbb68071..0xbb6807a: flush path
            // 0xbb68071  mov r8,rdi;
            // 0xbb68074  call 0x1197A0  (R9 = a3)
            sub_1197a0(state, cur, ptr, blkA3);
        }
    }

    // 0xbb6807a  cmp byte ptr [rsi+0x140],1;  0xbb68081  jne -> 0xbb680ae
    if (blkA3->flag == 1) {  // 0xbb6807a/0xbb68081
        // 0xbb68083  add rsi,0x130   chunk address is a3+0x130
        const std::uint8_t* const ptr = blkA3->data;

        // 0xbb6808a..0xbb68092: cur/end test as above
        std::uint8_t* cur = reinterpret_cast<std::uint8_t*>(state->cur);
        if (cur != reinterpret_cast<std::uint8_t*>(state->end)) {
            // 0xbb68098..0xbb680a5: inline copy path
            // 0xbb68098  movups xmm0,[rsi];
            // 0xbb6809b  movups [rdx],xmm0;
            // 0xbb6809e  add qword ptr [rcx+8],0x10
            std::memcpy(cur, ptr, 16);
            state->cur = reinterpret_cast<void*>(cur + 16);
        } else {
            // 0xbb680a5..0xbb680ae: flush path
            // 0xbb680a5  mov r8,rsi;
            // 0xbb680a8  call 0x1197A0  (R9 = a3)
            sub_1197a0(state, cur, ptr, blkA3);
        }
    }

    // 0xbb680ae  mov rax,[rbp-8]  -> return self
    return state;  // 0xbb680b2..0xbb680be epilogue (restore registers, ret) implicit
}

} // namespace native::helpers
