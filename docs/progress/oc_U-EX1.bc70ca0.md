## NEXT
DONE

## FILES
- docs/progress/oc_U-EX1.bc70ca0.md (this result file, created)
- docs/functions/bc70ca0.md (dossier created: mechanical facts, signature, Reversed source (complete), structs, callees, ownership)
- src/client/features/render/native/bgfx/sub_bc70ca0.cpp (created: first line `// LIFT 0xbc70ca0 size 0x1b0 1.26.62.01 sub_bc70ca0`, lifted body, LIFT_FN registry entry)
- src/client/features/render/native/bgfx/sub_bc70ca0.h (created: layout constants, static_asserts, signature, forward declarations of lift-classified callees)

## LIFTCHECK
LIFTCHECK OK 0xbc70ca0

## UNRESOLVED CALL
none

## Summary
Unit U-EX1.bc70ca0: lifted sub_bc70ca0 (0xbc70ca0, size 0x1b0, depth 1, region bgfx/D0). Calls in the body: sub_ebdbf10 (lock state+0x1C0), sub_ebce390 x5 (command-packet copies into cmdBuffer->data at state+0x1CFD0C8, cursor +0xDC5818/data +0xDC5820), sub_ebdbf20 (unlock). All three callees are classified lift (auto-unresolved->lift) in docs/data/native_boundary.tsv and are forward-declared as native::sub_ebdbf10/native::sub_ebce390/native::sub_ebdbf20 in sub_bc70ca0.h; no call is outside the lift set, so there are no UNRESOLVED CALLs. Body pops one u16 handle from the allocator (count+0x1DF7488, max+0x1DF748A, dense+0x1DF748C with reverse map at values[max+val]), stores a 3-field stride-0x28 record at records[val] (fields +0x00=arg3/r9d, +0x04=arg2/r8d, +0x08=1), advances u64 accumulator at +0x1EBF1E8 by (uint32)(arg3*arg2), emits the packet tag 0x0F/u16/u32/u32/u16(5th stack argument) with the original's cursor alignment steps ((c0&~1)+2, +5&~3, +7&~3, +5&~1, +2), writes *out = val (0xFFFF on either failure branch), unlocks, returns out. Every instruction of [0xbc70ca0, 0xbc70e50) is inside a cited // 0xA..0xB range; every call is quoted verbatim (plain comment + backtick form) and matches rdis via verify_oc. liftcheck printed LIFTCHECK OK 0xbc70ca0 with zero failures.

CLOSES? YES
