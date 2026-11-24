# Dossier: sub_eec5a00 (0xeec5a00)

## Mechanical facts

- size 0x6 bytes, 1 instruction [V: rdis dis 0xeec5a00]:
  `0xeec5a00  jmp qword ptr [0xF9A72F0]`          ; [data_f9a72f0]
- The function is an indirect tail jump through data slot 0xF9A72F0 (.rdata). It has no prologue/epilogue, contains no `call` instruction, reads no registers for its own logic, and writes no memory. The bytes at 0xeec5a06+ are int3 padding and are not part of the function [V: rdis dis 0xeec5a00 8].
- Slot 0xF9A72F0 holds the MSVCP140.dll import-by-name `?_Throw_Cpp_error@std@@YAXH@Z` = `std::_Throw_Cpp_error(int)` [V: python tools/sigs/peimports.py prints `0xF9A72F0 -> MSVCP140.dll !?_Throw_Cpp_error@std@@YAXH@Z`].
- callees: none — no `call` instruction in [0xeec5a00, 0xeec5a06). The tail-jump target is resolved through the data slot at runtime (see "Callees").

## Signature

`void sub_eec5a00(int errorCode)` — x64 Microsoft ABI; the error code arrives in RCX [V: call sites `mov ecx,5; call 0xEEC5A00` / `mov ecx,6; call 0xEEC5A00`, e.g. 0x7efca and 0x7efde; the import mangling encodes an int argument and void return]. Observed call sites ignore the return value; the original is a tail jump so eax is whatever the target leaves.

## Reversed source (complete)

The function body is one instruction:

`0xeec5a00  jmp qword ptr [0xF9A72F0]`

Lifted body (src/client/features/render/native/helpers/sub_eec5a00.cpp):

```cpp
// 0xeec5a00..0xeec5a06: jmp qword ptr [0xF9A72F0] ; tail call to std::_Throw_Cpp_error via data slot 0xF9A72F0
return std::_Throw_Cpp_error(errorCode);   // 0xeec5a00  jmp qword ptr [0xF9A72F0]
```

The `jmp` is a tail call through data slot 0xF9A72F0. The slot resolves [V] to MSVCP140.dll `std::_Throw_Cpp_error(int)`, so the lifted body calls that exact function with the same argument (RCX) and the same return behavior — identical reads (none observable in the function itself; the slot fetch is the jump target), identical writes (none), identical calls (none in the function itself), identical return.

## Structs touched

None: the function touches no struct fields, so no layout offsets are used. The x64 ABI contract is asserted in `sub_eec5a00.h` and `sub_eec5a00.cpp` (pointer and function-pointer size static_asserts).

## Callees

No callees: the body is one indirect tail jump through data slot 0xF9A72F0, not a `call`. The resolved target MSVCP140.dll `std::_Throw_Cpp_error(int)` [V: PE import table] is called directly by name from the lifted body, exactly as hard rule 69 sanctions for data-slot indirect calls (documenting the slot RVA 0xF9A72F0). No unresolved call.

## Version-stable anchors

- Function RVA 0xeec5a00, size 0x6, 1.26.62.01 [V: docs/data/native_functions.tsv line 1643; rdis dis].
- Data slot RVA 0xF9A72F0 -> MSVCP140.dll !?_Throw_Cpp_error@std@@YAXH@Z [V: peimports.py].

## Verification

Static [V]: disassembly read with `rdis dis 0xeec5a00` (8 instructions for padding context); import resolved with `python tools/sigs/peimports.py`; call-site argument passing observed at 0x7efca/0x7efde (`mov ecx,5/6; call 0xEEC5A00`) and 0xbc7a980/0xbc7a991 (`mov ecx,5/6; call 0xEEC5A00`).
