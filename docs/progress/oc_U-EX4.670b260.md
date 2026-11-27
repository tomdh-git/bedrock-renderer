## NEXT
DONE: unit U-EX4.670b260 complete — sub_670b260 (0x670b260, 0x98 bytes, "terrain/chunk draw builder") lifted to C++; `python tools/sigs/liftcheck.py 0x670b260` printed `LIFTCHECK OK 0x670b260`; no unresolved calls; CLOSES? YES.

## FILES
- docs/progress/oc_U-EX4.670b260.md (this file, created)
- docs/functions/670b260.md (created: dossier with mechanical facts and 'Reversed source (complete)')
- src/client/features/render/native/framebuilder/sub_670b260.h (created: layout constants, static_asserts, Out/Record layouts, signature)
- src/client/features/render/native/framebuilder/sub_670b260.cpp (created: first line `// LIFT 0x670b260 size 0x98 1.26.62.01 sub_670b260`, lifted body, footprint, LIFT_FN registry entry, verbatim call quotes in #if 0 block)

## Summary
Function sub_670b260 [V from `rdis dis 0x670b260 0x98`, 36 instructions, 0x670b260..0x670b2f8]: x64 ABI `void* sub_670b260(void* a0)` (RCX = out object, RAX = a0). Clears a0+0x0..0x1F, loads the allocator object from data_1233e1a8 (dead read [allocator+8]), allocates 0x20 bytes via `call qword ptr [0xF99FFA0]` (slot data_f99ffa0 = sub_eea6040, vendor boundary, read through the slot at call time with RCX = allocator, EDX = 0x20). On NULL: `call 0x9BC830` (sub_9bc830, class alloc boundary, native_boundary.tsv row 149, OOM handler, noreturn) then the unreachable tail with a NULL record. Success path stores the record pointer and constants into a0 (+0x10 = 0x12, +0x18 = 0x1F, +0x20 u16 = 0x6E4F after a 16-byte zero, +0x30 = 2, +0x38 = 0xF) and fills the record ("RenderAsBillboards" from rodata [0xF55AF3F] +0x0..0xF, u16 0x7364 at +0x10, byte 0 at +0x12), returns a0. No null guard or SEH in the original (none added). Both calls target functions in docs/data/native_boundary.tsv; no callee outside the lift set and the boundary table.

## LIFTCHECK
LIFTCHECK OK 0x670b260

## UNRESOLVED CALL
none

CLOSES? YES
