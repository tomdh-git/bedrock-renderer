# sub_eec6de0 — IAT tail-jump thunk to memmove (0xeec6de0, size 0x6, 1.26.62.01)

## Source
- Unit: docs/progress/oc_U-EX7.eec6de0.md
- Function: `docs/data/native_functions.tsv` row `0xeec6de0	0x6	0	7	root	D0		added 0xeec6de0` [V]
- Size: 0x6 bytes [V: rdis dis 0xeec6de0 shows exactly one instruction at 0xeec6de0 followed by int3 padding]
- Native boundary: `docs/data/native_boundary.tsv` line 523 `0xeec6de0	lift	auto-unresolved->lift` [V]
- Callees in lift set: none [V: docs/data/native_functions.tsv, callees_in_set empty]

## Signature / ABI
- x64 Microsoft ABI, __cdecl. One return register RAX.
- RCX = dst (void*), RDX = src (const void*), R8 = size (std::uint64_t), return RAX = memmove result (void*).
- The function is a tail-forwarder: no register shuffling, no prologue/epilogue, control passes straight to the target in the data slot.

## Register / argument map
| Arg | Register | Type | Meaning |
| dst | RCX | void* | destination buffer |
| src | RDX | const void* | source buffer |
| size | R8 | std::uint64_t | byte count to copy |
| return | RAX | void* | memmove's return (dst) |

## Disassembly (rdis dis 0xeec6de0 1)
```
0xeec6de0  jmp qword ptr [0xF9A8AA0]     ; [data_f9a8aa0]
```

## Phases (instruction-complete)
// 0xeec6de0..0xeec6de6: jmp qword ptr [0xF9A8AA0] — indirect tail jump through IAT data slot 0xF9A8AA0 (.rdata), which holds VCRUNTIME140.dll!memmove [V: tools/sigs/peimports.py `0F9A8AA0  VCRUNTIME140.dll!memmove`]. Forwards dst (RCX), src (RDX), size (R8) unchanged to memmove; memmove's return (RAX) becomes this function's return. Reads no memory, writes none; the copy semantics belong to memmove. This is the only instruction in [0xeec6de0, 0xeec6de6).

## Struct fields touched
None — the instruction has no [reg+off] memory operand; the only memory read is the indirect jump target through data slot 0xF9A8AA0, not a struct field.

## Callees
- VCRUNTIME140!memmove via data slot 0xF9A8AA0 [V: peimports.py]. Class crt (boundary). No `call` instruction exists in the function — it is a tail-jump thunk (`jmp qword ptr [0xF9A8AA0]`), so there is no call to quote [V: rdis dis 0xeec6de0].
- callees_in_set: none [V: docs/data/native_functions.tsv].

## Reversed source (complete)
// 0xeec6de0..0xeec6de6: jmp qword ptr [0xF9A8AA0] ; tail call to memmove via IAT slot 0xF9A8AA0
void* sub_eec6de0(void* dst, const void* src, std::uint64_t size) {
    return ::memmove(dst, src, size);   // 0xeec6de0  jmp qword ptr [0xF9A8AA0]
}

Verbatim instruction of the function (matches rdis dis 0xeec6de0):
0xeec6de0  jmp qword ptr [0xF9A8AA0]

## Ownership / threading
memmove is a pure byte copy with no synchronization, no allocation, no GPU effects; thread-safety is the caller's concern, identical to the original thunk. No locks held or taken.

## Version anchors
- Build 1.26.62.01, Minecraft.Windows.exe, RVAs relative to image base [V: docs/OPENCODE_BRIEF.md].
- Slot 0xF9A8AA0 resolved via tools/sigs/peimports.py -> VCRUNTIME140.dll!memmove [V].

## Verification
- Coverage: the single instruction 0xeec6de0 is inside the cited range `0xeec6de0..0xeec6de6` and quoted verbatim.
- No `call` instruction, so no call quote is required; the verbatim `jmp` quote passes verify_oc.
- Layout constants asserted in `src/client/features/render/native/helpers/sub_eec6de0.h` (sub_eec6de0Layout static_asserts).
- Registry entry `LIFT_FN(eec6de0, "sub_eec6de0", 0xEEC6DE0, native::sub_eec6de0, nullptr)` in `sub_eec6de0.cpp`.

## OPEN questions
none
