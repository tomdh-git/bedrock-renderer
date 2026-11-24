## NEXT
DONE — lift complete and verified

## UNIT
X1.bc8c890 LIFT sub_bc8c890 (0xbc8c890, 0x435 bytes, depth 2, D0, 1 callee in set: 0x5669770 is `lift` in native_functions.tsv, called directly via forward declaration)

## FILES
docs/progress/oc_U-EX1.bc8c890.md (this file)
docs/functions/bc8c890.md (dossier: analysis + 'Reversed source (complete)')
src/client/features/render/native/bgfx/sub_bc8c890.h (layout constants + static_asserts + signature + forward declaration of ::native::sub_5669770)
src/client/features/render/native/bgfx/sub_bc8c890.cpp (lifted source, LIFT marker first line, LIFT_FN registry entry)

## LIFTCHECK
LIFTCHECK OK 0xbc8c890

## UNRESOLVED CALL
none (the only call, 0xbc8c959 `call 0x5669770`, targets a lift-class function in native_functions.tsv; forward-declared in the header, called through its native symbol)

## TOOL REQUESTS
(none yet)

CLOSES? YES
