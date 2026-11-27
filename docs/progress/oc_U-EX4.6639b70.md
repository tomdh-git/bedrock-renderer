## NEXT
DONE

## TASK
Lift 0x6639b70 (size 0x42, depth 0, region framebuilder, "BgfxFrameBuilder slot 86", 0 callees in set). CLOSES? YES — liftcheck prints LIFTCHECK OK.

## FACTS (from input data)
- EXE: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01), RVAs relative to image base.
- Function row: 0x6639b70 0x42 0 4 framebuilder D0 BgfxFrameBuilder slot 86, no callees in set.
- Allowed outputs: docs/progress/oc_U-EX4.6639b70.md, docs/functions/6639b70.md, src/client/features/render/native/framebuilder/ (new .cpp + .h only).

## FILES
Created or changed:
- docs/functions/6639b70.md (dossier with 'Reversed source (complete)')
- src/client/features/render/native/framebuilder/sub_6639b70.h (layout constants, static_asserts, signature, extern globals)
- src/client/features/render/native/framebuilder/sub_6639b70.cpp (LIFT marker, lifted body, #if 0 verbatim quotes, LIFT_FN registration)

## LIFTCHECK
LIFTCHECK OK 0x6639b70

## UNRESOLVED CALL
none (the only call is `0x6639b82  call qword ptr [0xF99FFA0]` to sub_eea6040, which is a vendor boundary function per docs/data/native_boundary.tsv; lifted via native::Boundary<uint8_t, void*>)

CLOSES? YES