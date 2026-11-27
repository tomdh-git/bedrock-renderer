# sub_ebcf430 (0xebcf430, size 0x2a, 1.26.62.01)

## Identity

- RVA 0xebcf430, size 0x2a bytes, range [0xebcf430, 0xebcf45a), depth 0, milestone 7, region root, status D0.
- Name: sub_ebcf430 (no exported symbol; docs/data/native_boundary.tsv row classifies it as `lift`, referenced from oc_U-EX0b2.md).
- Calls inside the range: none (0 callees in set, 0 calls at all).
- Successors of the range, both outside [0xebcf430, 0xebcf45a): fall-through 0xebcf45a and jump target 0xebcf49c of `0xebcf458  je short 0xEBCF49C`. Both are remaining ranges of sub_ebcf430, not separate callees; no return instruction sits inside this unit (the epilogue `0xebcf4ca  ... 0xebcf4df  ret` lies outside the unit).

## Signature (x64 Microsoft ABI) [V from the disassembly; argument types are an educated guess]

- RCX = a1: pointer/handle argument, tested for null (`0xebcf455  test rcx,rcx`), copied to RDI (`0xebcf44b  mov rdi,rcx`)
- RDX = a2: int32 argument; not read inside this range (consumed just past it, `0xebcf45f  movsxd rbx,edx`) [I]
- R8 = a3: pointer argument, copied to RBP (`0xebcf448  mov rbp,r8`) [I]
- R9 = a4: pointer argument, copied to RSI (`0xebcf445  mov rsi,r9`) [I]
- Return: int32 in EAX; the return path (`0xebcf493/0xebcf4c6  cmovs eax,r14d`, `0xebcf4df  ret`) lies outside this unit [I]

## Register/argument map

| Register | Argument | Use inside [0xebcf430, 0xebcf45a) |
| RCX | a1 | `0xebcf44b  mov rdi,rcx`; `0xebcf455  test rcx,rcx` |
| RDX | a2 | not read inside the range |
| R8 | a3 | `0xebcf448  mov rbp,r8` |
| R9 | a4 | `0xebcf445  mov rsi,r9` |
| RBP | - | incoming value stored (`0xebcf430  mov [rsp+0x10],rbp`), then clobbered |
| RSI | - | incoming value stored (`0xebcf435  mov [rsp+0x18],rsi`), then clobbered |
| RDI | - | incoming value stored (`0xebcf43a  mov [rsp+0x20],rdi`), then clobbered |
| R14 | - | incoming value pushed (`0xebcf43f  push r14`), then set to -1 (`0xebcf44e  mov r14,0xFFFFFFFFFFFFFFFF`) |
| RSP | - | `0xebcf441  sub rsp,0x40` (total frame change -0x48 including the push) |

## Phases

- 0xebcf430..0xebcf441: spill incoming RBP, RSI, RDI to [rsp+0x10], [rsp+0x18], [rsp+0x20] (entry-RSP-relative), then push R14.
- 0xebcf441..0xebcf445: `sub rsp,0x40`.
- 0xebcf445..0xebcf44e: reassign RSI = R9, RBP = R8, RDI = RCX.
- 0xebcf44e..0xebcf455: R14 = 0xFFFFFFFFFFFFFFFF.
- 0xebcf455..0xebcf45a: `test rcx,rcx`; `je short 0xEBCF49C` when RCX == 0.

## C-like statements

```
// 0xebcf430..0xebcf435
frame.rbp_save = saved_rbp;                     // [entry RSP+0x10] <- incoming RBP
// 0xebcf435..0xebcf43a
frame.rsi_save = saved_rsi;                     // [entry RSP+0x18] <- incoming RSI
// 0xebcf43a..0xebcf43f
frame.rdi_save = saved_rdi;                     // [entry RSP+0x20] <- incoming RDI
// 0xebcf43f..0xebcf441
frame.r14_save = saved_r14;                     // [entry RSP-8] <- incoming R14 (push r14)
// 0xebcf441..0xebcf445
rsp -= 0x40;                                    // frame base = post-sub RSP
// 0xebcf445..0xebcf448
rsi = a4;                                       // mov rsi,r9
// 0xebcf448..0xebcf44b
rbp = a3;                                       // mov rbp,r8
// 0xebcf44b..0xebcf44e
rdi = a1;                                       // mov rdi,rcx
// 0xebcf44e..0xebcf455
r14 = 0xFFFFFFFFFFFFFFFF;                       // mov r14,-1
// 0xebcf455..0xebcf45a
if (a1 == nullptr) { /* successor 0xebcf49c */ } else { /* successor 0xebcf45a */ }
                                                // test rcx,rcx ; je short 0xEBCF49C
```

## Struct fields touched

None: no game-struct field is read or written inside [0xebcf430, 0xebcf45a). The function writes only its own stack frame slots (all dead within this range — the epilogue that restores them lies outside the unit):

| Slot (post-sub-RSP base) | Size | Direction | Instruction | Meaning |
| 0x40 | 8 | W | `0xebcf43f  push r14` | incoming R14 save |
| 0x58 | 8 | W | `0xebcf430  mov [rsp+0x10],rbp` | incoming RBP save |
| 0x60 | 8 | W | `0xebcf435  mov [rsp+0x18],rsi` | incoming RSI save |
| 0x68 | 8 | W | `0xebcf43a  mov [rsp+0x20],rdi` | incoming RDI save |

Layout constants with static_asserts: src/client/features/render/native/helpers/sub_ebcf430.h (struct SubEbcf430Frame).

## Callees

None: there are no `call` instructions inside [0xebcf430, 0xebcf45a).

## OPEN questions

- Exact types of a1/a3/a4 (pointer vs handle) are inferred from usage, not from a symbol.
- The two successors (0xebcf45a, 0xebcf49c) are the remaining ranges of sub_ebcf430; they are not part of this unit and are lifted elsewhere (if at all).

## Reversed source (complete)

```cpp
// LIFT 0xebcf430 size 0x2a 1.26.62.01 sub_ebcf430
#include "sub_ebcf430.h"
#include "client/features/render/native/Lift.h"

namespace native {

int32_t sub_ebcf430_lifted(void* a1 [[maybe_unused]], int32_t a2 [[maybe_unused]],
                           void* a3 [[maybe_unused]], void* a4 [[maybe_unused]]) {
    // 0xebcf430..0xebcf441
    std::uintptr_t saved_rbp;
    std::uintptr_t saved_rsi;
    std::uintptr_t saved_rdi;
    std::uintptr_t saved_r14;
    SubEbcf430Frame frame;
    // 0xebcf430  mov [rsp+0x10],rbp
    // 0xebcf435  mov [rsp+0x18],rsi
    // 0xebcf43a  mov [rsp+0x20],rdi
    // 0xebcf43f  push r14
    // 0xebcf441  sub rsp,0x40
    frame.rbp_save = saved_rbp;
    frame.rsi_save = saved_rsi;
    frame.rdi_save = saved_rdi;
    frame.r14_save = saved_r14;
    // 0xebcf445  mov rsi,r9
    // 0xebcf448  mov rbp,r8
    // 0xebcf44b  mov rdi,rcx
    // 0xebcf44e  mov r14,0xFFFFFFFFFFFFFFFF
    [[maybe_unused]] void* rdi = a1;
    [[maybe_unused]] void* rbp = a3;
    [[maybe_unused]] void* rsi = a4;
    [[maybe_unused]] std::uintptr_t r14 = 0xFFFFFFFFFFFFFFFFui64;
    // 0xebcf455  test rcx,rcx
    // 0xebcf458  je short 0xEBCF49C
    if (a1 == nullptr) {
        // successor at 0xebcf49c: control leaves this lift unit
    } else {
        // successor at 0xebcf45a: control leaves this lift unit
    }
    __assume(false);
}

} // namespace native

LIFT_FN(sub_ebcf430, "sub_ebcf430", 0xEBCF430, sub_ebcf430_lifted, nullptr);
```

## Verification

- Source: src/client/features/render/native/helpers/sub_ebcf430.cpp (first line is the LIFT marker for 0xebcf430, size 0x2a).
- All 11 instructions of [0xebcf430, 0xebcf45a) are covered by cited ranges and quoted verbatim in the #if 0 block of the source; there are no call instructions to quote.
- Gate: `python tools/sigs/liftcheck.py 0xebcf430` must print `LIFTCHECK OK 0xebcf430`.
