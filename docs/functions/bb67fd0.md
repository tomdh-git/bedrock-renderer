# sub_bb67fd0 0xbb67fd0 size 0xef

## Identity
- RVA: 0xbb67fd0, size 0xef bytes ([0xbb67fd0, 0xbb680bf)), depth 0, milestone 7, region helpers.
- Root: added 0xbb67fd0. Callees in lift set: (none). Callees outside set: 0x1197a0.
- Lifted at: src/client/features/render/native/helpers/sub_bb67fd0.cpp (+ .h).

## Signature (x64 Microsoft ABI) [resolved]
SubBb67fd0State* sub_bb67fd0(SubBb67fd0State* self, SubBb67fd0SrcRange* src,
                             SubBb67fd0Block* a2, SubBb67fd0Block* a3);
- RCX = self (state object), RDX = src range, R8 = block a2, R9 = block a3.
- Return RAX = self (the state object pointer).

## Register / argument map [resolved]
- RCX (self) is spilled to [rbp-8] at 0xbb68009 and reloaded as rcx at every loop head
  (0xbb68020/0xbb68056/0xbb6808a) and for the return at 0xbb680ae (`mov rax,[rbp-8]`).
- R9 -> RSI at 0xbb67fe9 (block a3); R8 -> RDI at 0xbb67fec (block a2).
- The prologue zeroes self->buffer (+0x00), self->cur (+0x08) via `movups [rcx],xmm0`
  at 0xbb67ff2 and self->end (+0x10) at 0xbb67ff5.
- R14/R15 = src range [rdx+0x20, rdx+0x28) (0xbb67ffd/0xbb68001); iterated in 16-byte steps.
- RBX = address of the 16-byte scratch chunk at [rbp-0x20] (0xbb68005).

## Phases (instruction-complete, [0xbb67fd0, 0xbb680bf))

0xbb67fd0..0xbb6800f: prologue and initialization.
  Pushes rbp/r15/r14/rsi/rdi/rbx; sub rsp,0x48; lea rbp,[rsp+0x40];
  mov [rbp],-2 (dead frame slot, never read); mov rsi,r9; mov rdi,r8;
  movups [rcx],xmm0 (self->buffer/self->cur = 0); mov [rcx+0x10],0 (self->end = 0);
  mov r14,[rdx+0x20]; mov r15,[rdx+0x28]; lea rbx,[rbp-0x20]; mov [rbp-8],rcx;
  jmp to the loop head at 0xbb68024.

0xbb6800f..0xbb68010: nop fallthrough (no statement).

Loop head 0xbb68024..0xbb68029: cmp r14,r15; je -> 0xbb68046 (loop exit).

0xbb68029..0xbb6803b: for each src chunk: movups xmm0,[r14]; movaps [rbp-0x20],xmm0
  (scratch = chunk); mov rdx,[rcx+8] (cur); cmp rdx,[rcx+0x10] (end).
  0xbb68039: jne -> 0xbb68010 (inline copy path); fallthrough -> flush path.

0xbb68010..0xbb6801c: inline copy path: movups xmm0,[r14] (chunk reloaded);
  movups [rdx],xmm0 (*cur = chunk); add [rcx+8],0x10 (cur += 0x10); then
  0xbb6801c: add r14,0x10; 0xbb68020: mov rcx,[rbp-8]; back to loop head.

0xbb6803b..0xbb68046: flush path: mov r8,rbx; call 0x1197A0
  (RCX=self, RDX=cur, R8=scratch, R9=a3); then jmp -> 0xbb6801c.

0xbb68046..0xbb6804f: cmp byte ptr [rdi+0x140],0; je -> 0xbb6807a.
  When a2->flag != 0: add rdi,0x130 (chunk at a2+0x130); cur/end test;
  inline copy of [rdi] (*cur += 0x10) or call 0x1197A0(self, cur, a2+0x130, a3)
  at 0xbb68074.

0xbb6807a..0xbb680ae: cmp byte ptr [rsi+0x140],1; jne -> 0xbb680ae.
  When a3->flag == 1: add rsi,0x130 (chunk at a3+0x130); cur/end test;
  inline copy of [rsi] (*cur += 0x10) or call 0x1197A0(self, cur, a3+0x130, a3)
  at 0xbb680a8.

0xbb680ae..0xbb680bf: mov rax,[rbp-8]; epilogue (pop rbx/rdi/rsi/r14/r15/rbp; ret).
  Return value: self.

## Struct fields touched [resolved]

| base | offset | size | R/W | meaning | instruction |
|------|--------|------|-----|---------|-------------|
| self (+0x00) | 0x00 | 8 | W | state->buffer (buffer base; zeroed, never read) | 0xbb67ff2 movups [rcx] |
| self (+0x08) | 0x08 | 8 | R/W | state->cur (write cursor) | 0xbb68017/0xbb68031/0xbb6805a/0xbb6806a/0xbb6808e/0xbb6809e |
| self (+0x10) | 0x10 | 8 | R/W | state->end (write limit) | 0xbb67ff5 W; 0xbb68035/0xbb6805e/0xbb68092 R |
| src (+0x20) | 0x20 | 8 | R | src->begin (range begin) | 0xbb67ffd |
| src (+0x28) | 0x28 | 8 | R | src->end (range end) | 0xbb68001 |
| block a2 (+0x130) | 0x130 | 16 | R | a2->data (16-byte chunk) | 0xbb68064 (via rdi+0x130) |
| block a2 (+0x140) | 0x140 | 1 | R | a2->flag (!= 0 enables the a2 copy) | 0xbb68046 |
| block a3 (+0x130) | 0x130 | 16 | R | a3->data (16-byte chunk) | 0xbb68098 (via rsi+0x130) |
| block a3 (+0x140) | 0x140 | 1 | R | a3->flag (== 1 enables the a3 copy) | 0xbb6807a |

## Callees [resolved]

- 0xbb6803e / 0xbb68074 / 0xbb680a8: `call 0x1197A0` (sub_1197a0).
  sub_1197a0 is a boundary candidate (docs/data/native_boundary_candidates.tsv),
  not in the lift set; no statically recorded signature. Forward-declared as
  `extern "C" void sub_1197a0(SubBb67fd0State*, std::uint8_t*, const std::uint8_t*, SubBb67fd0Block*)`
  in sub_bb67fd0.h. The call convention used is x64 Microsoft ABI; RCX = self,
  RDX = state->cur, R8 = 16-byte chunk pointer, R9 = argument 3 (a3). RAX is never
  read after the call, so the return type is declared void.
  Argument/role mapping per call site:
  - 0xbb6803e: R8 = &scratch chunk ([rbp-0x20]).
  - 0xbb68074: R8 = a2 + 0x130.
  - 0xbb680a8: R8 = a3 + 0x130.

## DECISIONS [resolved]

- Signature: `SubBb67fd0State* sub_bb67fd0(SubBb67fd0State* self, SubBb67fd0SrcRange* src,
  SubBb67fd0Block* a2, SubBb67fd0Block* a3)` returning self. RCX=self is confirmed by
  the spill/reload pattern ([rbp-8] stored at 0xbb68009, reloaded at 0xbb68020/0xbb68056/
  0xbb6808a, returned in RAX at 0xbb680ae).
- self layout: +0x00 buffer (zeroed only), +0x08 cur, +0x10 end (void* pointers).
  cur is advanced by 0x10 after each 16-byte write; end is the flush threshold.
- src layout: +0x20 begin, +0x28 end; elements are 16-byte chunks (add r14,0x10).
- block layout (a2/a3): +0x130 data[16] chunk, +0x140 flag byte.
  a2 path enables when flag != 0; a3 path enables when flag == 1.
- scratch chunk: 16 bytes at [rbp-0x20], always written before the cur/end test
  (0xbb6802d), consumed by sub_1197a0 on the flush path.
- Return value: self (RAX = [rbp-8] at 0xbb680ae); no other exit paths.
- sub_1197a0 signature is not statically recorded; declared extern "C" with the
  argument roles observed at the three call sites. Its semantics (flush/grow of the
  state stream) are not observable from this listing.

## Verbatim instruction quotes (all calls in the function)

0xbb6803e  call 0x1197A0
0xbb68074  call 0x1197A0
0xbb680a8  call 0x1197A0

## Reversed source (complete)

```cpp
// LIFT 0xbb67fd0 size 0xef 1.26.62.01 sub_bb67fd0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_bb67fd0.h"

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_bb67fd0, "sub_bb67fd0", 0xbb67fd0, sub_bb67fd0, nullptr);

#if 0
0xbb6803e  call 0x1197A0
0xbb68074  call 0x1197A0
0xbb680a8  call 0x1197A0
#endif

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

SubBb67fd0State* sub_bb67fd0(SubBb67fd0State* self, SubBb67fd0SrcRange* src,
                             SubBb67fd0Block* a2, SubBb67fd0Block* a3)
{
    SubBb67fd0State* const state = self;
    SubBb67fd0Block* const blkA2 = a2;
    SubBb67fd0Block* const blkA3 = a3;

    state->buffer = nullptr;  // 0xbb67ff2 movups [rcx] (+0x00)
    state->cur = nullptr;     // 0xbb67ff2 movups [rcx] (+0x08)
    state->end = nullptr;     // 0xbb67ff5 [rcx+0x10] = 0

    const std::uint8_t* const srcBegin =
        reinterpret_cast<const std::uint8_t*>(src->begin);
    const std::uint8_t* const srcEnd =
        reinterpret_cast<const std::uint8_t*>(src->end);

    std::uint8_t stackBuf[16];  // 0xbb68005 scratch chunk at [rbp-0x20]

    std::uint8_t* curSrc = const_cast<std::uint8_t*>(srcBegin);
    while (curSrc != srcEnd) {  // 0xbb68024 cmp r14,r15;  0xbb68027 je -> 0xbb68046

        std::memcpy(stackBuf, curSrc, 16);  // 0xbb68029/0xbb6802d chunk -> scratch

        std::uint8_t* cur = reinterpret_cast<std::uint8_t*>(state->cur);
        if (cur != reinterpret_cast<std::uint8_t*>(state->end)) {  // 0xbb68031/0xbb68035/0xbb68039
            std::memcpy(cur, curSrc, 16);  // 0xbb68010/0xbb68014 *cur = chunk
            state->cur = reinterpret_cast<void*>(cur + 16);          // 0xbb68017 cur += 0x10
        } else {  // 0xbb6803b/0xbb6803e flush path
            sub_1197a0(state, cur, stackBuf, blkA3);
        }

        curSrc += 16;  // 0xbb6801c r14 += 0x10;  0xbb68020 rcx = self
    }

    if (blkA2->flag != 0) {  // 0xbb68046/0xbb6804d
        const std::uint8_t* const ptr = blkA2->data;  // 0xbb6804f rdi += 0x130

        std::uint8_t* cur = reinterpret_cast<std::uint8_t*>(state->cur);
        if (cur != reinterpret_cast<std::uint8_t*>(state->end)) {  // 0xbb6805a/0xbb6805e/0xbb68062
            std::memcpy(cur, ptr, 16);  // 0xbb68064/0xbb68067
            state->cur = reinterpret_cast<void*>(cur + 16);          // 0xbb6806a
        } else {  // 0xbb68071/0xbb68074 flush path
            sub_1197a0(state, cur, ptr, blkA3);
        }
    }

    if (blkA3->flag == 1) {  // 0xbb6807a/0xbb68081
        const std::uint8_t* const ptr = blkA3->data;  // 0xbb68083 rsi += 0x130

        std::uint8_t* cur = reinterpret_cast<std::uint8_t*>(state->cur);
        if (cur != reinterpret_cast<std::uint8_t*>(state->end)) {  // 0xbb6808e/0xbb68092/0xbb68096
            std::memcpy(cur, ptr, 16);  // 0xbb68098/0xbb6809b
            state->cur = reinterpret_cast<void*>(cur + 16);          // 0xbb6809e
        } else {  // 0xbb680a5/0xbb680a8 flush path
            sub_1197a0(state, cur, ptr, blkA3);
        }
    }

    return state;  // 0xbb680ae rax = self; epilogue implicit
}

} // namespace native::helpers
```
