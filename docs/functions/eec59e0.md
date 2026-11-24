# Dossier: sub_eec59e0 (0xeec59e0)

## Mechanical facts

- size 0x6 bytes, 1 instruction [V: rdis dis 0xeec59e0]
- `0xeec59e0  jmp qword ptr [0xF9A7310]` ; [data_f9a7310] — an indirect tail jump through data slot 0xF9A7310 [V]
- No prologue, no stack frame, no register reads, no memory writes, no call instruction in [0xeec59e0, 0xeec59e6) [V]
- Slot 0xF9A7310 (.rdata, file off 0xf9a5d10) contains import-by-name RVA 0xF9AA638; the entry at 0xF9AA638 is hint 652, name '?_Xbad_function_call@std@@YAXXZ' = std::_Xbad_function_call(void) of the MSVC CRT [V: PE import table read, slot RVA 0xF9A7310 -> RVA 0xF9AA638]

## Signature guess / register/argument map

- `void sub_eec59e0(void)` — x64 Microsoft ABI: no register argument is read (the instruction reads only the data slot), no return value is produced by the function itself; control never returns to the caller because the target throws std::bad_function_call or terminates [V for the instruction; I for never-returns, from CRT semantics of _Xbad_function_call]

## Phases

- 0xeec59e0..0xeec59e6: `jmp qword ptr [0xF9A7310]` — tail jump to std::_Xbad_function_call through data slot 0xF9A7310. Corresponding C++: `return std::_Xbad_function_call();` [V]

## Struct fields touched

- none: the function reads no memory and writes no memory [V]

## Callees

- none: the instruction is a jmp, not a call, so there are no callees in [0xeec59e0, 0xeec59e6) [V]
- Indirect jump target (control transfer, not a call): std::_Xbad_function_call via data slot 0xF9A7310, resolved from the PE import table; declared with its real symbol in sub_eec59e0.h and called directly by the lifted body (tail call, same target the original jumps to).

## OPEN questions

- none

## Reversed source (complete)

// LIFT 0xeec59e0 size 0x6 1.26.62.01 sub_eec59e0
// (source file: src/client/features/render/native/helpers/sub_eec59e0.cpp, header sub_eec59e0.h)

void sub_eec59e0(void) {
    // 0xeec59e0..0xeec59e6: jmp qword ptr [0xF9A7310] ; tail jump to std::_Xbad_function_call via data slot 0xF9A7310
    return std::_Xbad_function_call();   // 0xeec59e0  jmp qword ptr [0xF9A7310]
}

Verbatim instruction of the function (matches rdis dis 0xeec59e0):
#if 0
0xeec59e0  jmp qword ptr [0xF9A7310]
#endif

Registry entry (in sub_eec59e0.cpp):
LIFT_FN(eec59e0, "sub_eec59e0", 0xEEC59E0, sub_eec59e0, nullptr);

Layout constants with static_asserts (in sub_eec59e0.h): sub_eec59e0Layout asserts sizeof(void*) == 8 and sizeof(void(__cdecl*)(void)) == 8; no struct fields are touched so there are no layout offsets to assert.

## Ownership / threading

- The function touches no game memory and has no side effects of its own; it transfers control to the CRT. Thread model: same as the caller [I].

## Version anchors

- Minecraft Bedrock 1.26.62.01, RVA 0xeec59e0, size 0x6 [V].
