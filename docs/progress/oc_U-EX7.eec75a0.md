## NEXT
DONE

## UNIT
U-EX7.eec75a0 | function sub_eec75a0 at RVA 0xeec75a0, size 0x6, depth 0, milestone 7, region root, status D0, 0 callees in lift set.

## DISASSEMBLY
0xeec75a0  jmp qword ptr [0xF9A8E60]                     ; [data_f9a8e60]   (6 bytes, the entire function)
0xeec75a6+: int3 padding (not part of the function)

Slot 0xF9A8E60 (.rdata) contains qword RVA 0xF9B0820, an import-by-name entry: hint 0xBF,
name "floorf" (float floorf(float)) of the MSVC CRT [V: PE import table read,
slot RVA 0xF9A8E60 -> import-by-name RVA 0xF9B0820 -> name floorf]. At runtime the loader
fills the slot with floorf's address, so the instruction is a tail call to floorf.
Verified by reading the PE file directly (not from dossiers).

## FILES
- src/client/features/render/native/helpers/sub_eec75a0.cpp (new)
- src/client/features/render/native/helpers/sub_eec75a0.h (new)
- docs/functions/eec75a0.md (new dossier)

## LIFTCHECK
LIFTCHECK OK 0xeec75a0

## UNRESOLVED CALL
none (the only control transfer is a jmp through data slot 0xF9A8E60 to floorf, which is
a CRT function called directly as std::floorf from <cmath>; no call instruction exists in
the function)

CLOSES? YES
