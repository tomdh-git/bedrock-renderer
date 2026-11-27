# sub_aa3c0 (0xaa3c0) — lift dossier

Minecraft Windows 1.26.62.01, function [0xaa3c0, 0xaa3c8), size 0x8 bytes, depth 0, milestone 7, region root, status D0. Unit U-EX7.aa3c0 (checklist line: `X7.aa3c0 LIFT sub_aa3c0 (0xaa3c0, 0x8 bytes, depth 0, D0, 0 callees in set)`).

## Signature / ABI

`extern "C" void* sub_aa3c0(void)` — x64 Microsoft ABI: no arguments (RCX, RDX, R8, R9 are not read), return value in RAX [V: `rdis dis 0xaa3c0 8` and `rdis sum 0xaa3c0` — the function reads no argument registers and returns `&data_128c1588` in RAX].

## Register / argument map

No argument registers are read; RAX holds the result on the only path [V]. No stack slots, no shadow-space use beyond the plain `ret` [V: `rdis sum 0xaa3c0`, stack_slots empty].

## Phases (instruction-complete, [0xaa3c0, 0xaa3c8))

- `0xaa3c0..0xaa3c8`: `lea rax,[0x128C1588]            ; [data_128c1588]` then `ret`. The function computes the address of the game global `data_128c1588` (RVA 0x128C1588) and returns it in RAX. No memory is read or written, no register other than RAX is touched, there are no calls [V: `rdis sum 0xaa3c0` — calls: empty, accesses: empty; `rdis dis 0xaa3c0 8` lists exactly the two instructions below].

## Reversed source (complete)

// 0xaa3c0..0xaa3c8
0xaa3c0  lea rax,[0x128C1588]
0xaa3c7  ret

extern "C" void* sub_aa3c0(void) {
// 0xaa3c0..0xaa3c8
    return reinterpret_cast<void*>(&data_128c1588);
    // 0xaa3c0  lea rax,[0x128C1588]
    // 0xaa3c7  ret
}

## Struct fields touched

None [V]: `rdis sum 0xaa3c0` reports no field accesses; the function only forms an address.

## Callees

None [V]: `rdis sum 0xaa3c0` reports no calls; `[0xaa3c0, 0xaa3c8)` contains no `call` instruction. No boundary, lift-set, or intrinsic callees.

## OPEN questions

- The pointee type of `data_128c1588` is not determined by this function alone: exactly one `.text` reference to 0x128C1588 exists, the `lea` at 0xaa3c3 itself [V: `rdis ripscan 0x128c1588` returned only `aa3c3 (func aa250)`]. Callers of `sub_aa3c0` determine the pointee type [I].
