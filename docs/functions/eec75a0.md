# sub_eec75a0 (0xeec75a0) — lift dossier

Function: sub_eec75a0, RVA 0xeec75a0, size 0x6, version 1.26.62.01, depth 0, milestone 7, region root.
Callees in lift set: none.
Source: src/client/features/render/native/helpers/sub_eec75a0.cpp (+ header sub_eec75a0.h).

## Signature

x64 Microsoft ABI. The function is a tail-forwarder thunk: one indirect jump through data
slot 0xF9A8E60 whose runtime target is floorf. Argument: float in XMM0. Return: float in
XMM0. Control never returns to the caller of the thunk (tail jump).

    float sub_eec75a0(float value);   // 0xeec75a0  jmp qword ptr [0xF9A8E60]

## Register / argument map

- XMM0 = `value` (float), forwarded unchanged to floorf
- XMM0 = return value (float) from floorf, returned to the thunk's caller
- No memory is read or written by the thunk itself; the only memory read is the 8-byte
  load from data slot 0xF9A8E60 performed by the `jmp qword ptr [0xF9A8E60]` instruction
  [V: rdis dis 0xeec75a0].

## Data slot resolution

Slot 0xF9A8E60 (.rdata) contains qword RVA 0xF9B0820, an import-by-name entry: hint 0xBF,
name "floorf" (float floorf(float)) of the MSVC CRT [V: PE import table read,
slot RVA 0xF9A8E60 -> import-by-name RVA 0xF9B0820 -> name floorf]. At runtime the loader
fills the slot with floorf's address, so the instruction is a tail call to floorf.

## Reversed source (complete)

// 0xeec75a0..0xeec75a6
float sub_eec75a0(float value) {
    // 0xeec75a0..0xeec75a6: jmp qword ptr [0xF9A8E60] ; tail call to floorf via data slot 0xF9A8E60 (value=XMM0, return=XMM0)
    return std::floorf(value);   // 0xeec75a0  jmp qword ptr [0xF9A8E60]
}

The single instruction `0xeec75a0  jmp qword ptr [0xF9A8E60]` is covered by the cited
range `0xeec75a0..0xeec75a6` and is quoted verbatim above. There are no `call`
instructions in the function (the transfer is a `jmp`), so there are no call quotes.

## Struct fields touched

none (the thunk touches no struct fields; layout constants are in sub_eec75a0.h with
static_asserts: sizeof(void*)==8, function-pointer size 8).

## Callees

- floorf (float floorf(float), MSVC CRT) — reached through data slot 0xF9A8E60,
  tail-forwarded, not a `call` instruction; declared via <cmath> and called as
  std::floorf(value) in the lifted body [V: slot->import-by-name->floorf resolution above].

## Ownership / threading

Pure forwarder, no side effects of its own; thread-safe as floorf is. No allocator, no
lifetime, no locks.

## Version anchors

- Version 1.26.62.01; slot RVA 0xF9A8E60, import-by-name RVA 0xF9B0820, name floorf.
- Function size 0x6 bytes (0xeec75a0..0xeec75a6); bytes at 0xeec75a6 onward are int3
  padding and not part of the function.
