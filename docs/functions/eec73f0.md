# sub_eec73f0 (0xeec73f0) — lift dossier

Function: sub_eec73f0, RVA 0xeec73f0, size 0x6, version 1.26.62.01, depth 0, milestone D0, region root.
Callees in lift set: none.
Source: src/client/features/render/native/helpers/sub_eec73f0.cpp (+ header sub_eec73f0.h).

## Signature

x64 Microsoft ABI. The function is a tail-forwarder thunk: one indirect jump through data
slot 0xF9A8E08 whose runtime target is ceilf. Argument: float in XMM0. Return: float in
XMM0. Control never returns to the caller of the thunk (tail jump).

    float sub_eec73f0(float value);   // 0xeec73f0  jmp qword ptr [0xF9A8E08]

## Register / argument map

- XMM0 = `value` (float), forwarded unchanged to ceilf
- XMM0 = return value (float) from ceilf, returned to the thunk's caller
- No memory is read or written by the thunk itself; the only memory read is the 8-byte
  load from data slot 0xF9A8E08 performed by the `jmp qword ptr [0xF9A8E08]` instruction
  [V: rdis dis 0xeec73f0; sum: accesses base &data_f9a8e08 size 8 read].

## Data slot resolution

Slot 0xF9A8E08 (.rdata) contains qword RVA 0xF9B07CC, an import-by-name entry: hint 0x7d,
name "ceilf" (float ceilf(float)) of the MSVC CRT [V: PE import table read,
slot RVA 0xF9A8E08 -> import-by-name RVA 0xF9B07CC -> name ceilf]. At runtime the loader
fills the slot with ceilf's address, so the instruction is a tail call to ceilf.

## Reversed source (complete)

// 0xeec73f0..0xeec73f6
float sub_eec73f0(float value) {
    // 0xeec73f0..0xeec73f6: jmp qword ptr [0xF9A8E08] ; tail call to ceilf via data slot 0xF9A8E08 (value=XMM0, return=XMM0)
    return std::ceilf(value);   // 0xeec73f0  jmp qword ptr [0xF9A8E08]
}

The single instruction `0xeec73f0  jmp qword ptr [0xF9A8E08]` is covered by the cited
range `0xeec73f0..0xeec73f6` and is quoted verbatim above. There are no `call`
instructions in the function (the transfer is a `jmp`), so there are no call quotes.

## Struct fields touched

none (the thunk touches no struct fields; layout constants are in sub_eec73f0.h with
static_asserts: sizeof(void*)==8, function-pointer size 8).

## Callees

- ceilf (float ceilf(float), MSVC CRT) — reached through data slot 0xF9A8E08,
  tail-forwarded, not a `call` instruction; declared via <cmath> and called as
  std::ceilf(value) in the lifted body [V: slot->import-by-name->ceilf resolution above].

## Ownership / threading

Pure forwarder, no side effects of its own; thread-safe as ceilf is. No allocator, no
lifetime, no locks.

## Version anchors

- Version 1.26.62.01; slot RVA 0xF9A8E08, import-by-name RVA 0xF9B07CC, name ceilf.
- Function size 0x6 bytes (0xeec73f0..0xeec73f6); bytes at 0xeec73f6 onward are int3
  padding and not part of the function.
