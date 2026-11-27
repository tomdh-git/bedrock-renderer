# Dossier: sub_aaa6e0 (0xaaa6e0, size 0xd7, 1.26.62.01)

## Mechanical facts

- size 0xd7 bytes (215), depth 0, milestone 7, region root, D0
- callers: 6 (0xa8cee0, 0x539b7c0, 0x539e420, 0x53d4160, 0x6adf430, 0x6e78d90) [V: docs/progress/pack/aaa6e0.md]
- callees (direct, per rdis listing): sub_e935700 x3 (0xaaa717, 0xaaa739, tail jmp 0xaaa798); sub_a89240 x1 (0xaaa72c); indirect `call qword ptr [0xF9A8C78]` x1 (0xaaa7b0) [V]
- callees in lift set: 0 (per data file `callees_in_set` empty); callees outside set: 0xa89240 [V: data file]

### Argument use

- rcx (a0): this/pointer; read at +0x0 (P=[a0]), then P+0x8 cleared, P+0x0 -> rdi; [rsi]=[a0+0x0] used as RCX for tail call at 0xaaa782 [V]

### Direct callees

- sub_e935700 (lift-set, completed lift at src/client/features/render/native/helpers/sub_e935700.{h,cpp}, signature `void* sub_e935700(void* a0)`): called at 0xaaa717 (RCX=rcx value from loop), 0xaaa739 (RCX=rdi), tail jmp at 0xaaa798 (RCX=[a0], EDX=0x190 set but sub_e935700 only forwards RCX) [V]
- sub_a89240 (OUTSIDE both tables — only referenced as `callees_outside_set: 0xa89240` in data file and `0xa89240 3 ?` in native_boundary_candidates.tsv, unclassified): called at 0xaaa72c with RCX=rdi+0x18; return value discarded [V] => UNRESOLVED CALL blocker
- `call qword ptr [0xF9A8C78]` (indirect data slot, noreturn terminate path at 0xaaa7b0): not a blocker per rule 68 (document slot RVA); target not in either table [V]

### Struct fields touched

| Object base | Offset | Size | Direction | Meaning | Tag |
|---|---|---|---|---|---|
| a0 (=rsi) | +0x0 | 8 | R | P = [a0] (pointer) | [V] |
| P=[a0] | +0x8 | 8 | R/W | [P+8] = 0 | [V] |
| P=[a0] | +0x0 | 8 | R | rdi = [P] | [V] |
| rdi | +0x178 | 8 | R/W | read at 0xaaa749; written 0 at 0xaaa71c/0xaaa720 via r14=rdi+0x178 | [V] |
| rdi | +0x180 | 8 | W | [rdi+0x180] = 0 | [V] |
| rdi | +0x18 | 8 | R | passed to sub_a89240 | [V] |
| rdi | +0x188 | 8 | R | [rdi+0x188] (end pointer) | [V] |
| [rcx-8] | — | 8 | R | [rcx-8] where rcx=[rdi+0x178] | [V] |

Offsets are byte offsets into pointer-chained objects (a0 -> P=[a0] -> rdi=[P]); no single game struct is defined by this function.

## Analyst sections

### Purpose

`sub_aaa6e0` is a buffer/append helper operating on a pointer-chained object (a0 -> P=[a0] -> rdi=[P]). It clears [P+8], then if rdi=[P] is non-NULL enters a loop over [rdi+0x178] with remaining-size [rdi+0x188]-[rdi+0x178]: while remaining < 0x1000 it calls sub_e935700 to zero [rdi+0x178]..[rdi+0x180], calls sub_a89240(rdi+0x18), then sub_e935700(rdi), and advances rdi=[rdi] (the [rdi] chain); if rdi becomes NULL it tail-calls sub_e935700([a0]). When remaining >= 0x1000 it performs a bounds check ([rcx-8], rcx-8, compare >= 0x20) and on failure calls terminate via data slot 0xF9A8C78 (noreturn). Every returning path ends in a tail call to sub_e935700, returning void* in RAX. [V: every instruction in [0xaaa6e0, 0xaaa7b7) is accounted for in the reversed source below].

### Signature (real argument list and calling convention)

```cpp
void* sub_aaa6e0(void* a0 /*RCX*/);
```
[V]. Single argument in RCX, result in RAX (tail call to sub_e935700). No stack arguments read. No SEH, no null guards beyond the original's own test/jz tests.

### Reversed source (complete)

See `src/client/features/render/native/helpers/sub_aaa6e0.cpp` for the complete C++ reversal. Every instruction in [0xaaa6e0, 0xaaa7b7) is covered by a cited range `// 0xA..0xB` adjacent to the corresponding C++ statement, and every `call` instruction is quoted verbatim in the `#if 0 ... #endif` block of that file.

### Ownership / threading

No allocation; reads/writes only the pointer-chained object graph reachable from a0. Calls sub_e935700 (lift) and sub_a89240 (unresolved). The terminate path calls data slot 0xF9A8C78 (noreturn). Single-threaded within its use; no synchronization in this body. [V].

### Version anchors

- Game version: 1.26.62.01
- RVA: 0xaaa6e0, size 0xd7
- Verified by: rdis dis 0xaaa6e0 (exact listing captured in docs/progress/pack/aaa6e0.md)

## Calls

| RVA | Instruction | Target | Class | Tag |
|---|---|---|---|---|
| 0xaaa717 | `call 0xE935700` | sub_e935700 | lift (completed) | [V] |
| 0xaaa72c | `call 0xA89240` | sub_a89240 | outside both tables | [V] UNRESOLVED CALL |
| 0xaaa739 | `call 0xE935700` | sub_e935700 | lift (completed) | [V] |
| 0xaaa798 | `jmp 0xE935700` | sub_e935700 (tail) | lift (completed) | [V] |
| 0xaaa7b0 | `call qword ptr [0xF9A8C78]` | data slot 0xF9A8C78 | indirect data slot (noreturn) | [V] |

## Verification

- Static: `python tools/sigs/liftcheck.py 0xaaa6e0` must print `LIFTCHECK OK 0xaaa6e0`. Blocked: sub_a89240 is outside both tables (see CLOSES? below).
- The struct layout constants are asserted via `static_assert` in `sub_aaa6e0.h` (ABI contract; no single game struct defined).
- The `LIFT_FN` registry entry is in `sub_aaa6e0.cpp`.
