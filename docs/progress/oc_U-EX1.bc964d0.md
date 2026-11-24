## NEXT
DONE - unit complete, awaiting CLOSES confirmation.

## UNIT
rva=0xbc964d0 size=0x1e0 depth=2 milestone=1 region=bgfx status=D0 name="VV frame-graph builder"
Callees: 0x75720 (boundary stl), 0x9bc830 (boundary alloc), 0xeea6040 via call qword ptr [0xF99FFA0] (boundary vendor, jmp-rax thunk, data slot 0xF99FFA0), 0xeec6ec0 (boundary.tsv class lift, size 0x6, IAT thunk jmp [0xF9A8A98] == memcpy, called as native::sub_eec6ec0).
No UNRESOLVED CALLs.
Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances/1.26.62.01\Minecraft.Windows.exe (1.26.62.01)

## DONE
- Disassembled [0xbc964d0, 0xbc966b0) fully (size 0x1e0 per docs/progress/_d_U-EX1.bc964d0.txt; last byte int3 at 0xbc966af). Verified all callees against docs/data/native_boundary.tsv and docs/data/native_functions.tsv.
- Created src/client/features/render/native/bgfx/sub_bc964d0.h (layout structs sub_bc964d0_state / sub_bc964d0_source / sub_bc964d0_str with offset + sizeof static_asserts; native::sub_eec6ec0 forward declaration; exact x64 ABI signature sub_bc964d0(self rcx, a1 rdx, a2 r8, a3 r9) -> self rax).
- Created src/client/features/render/native/bgfx/sub_bc964d0.cpp (first line `// LIFT 0xbc964d0 size 0x1e0 1.26.62.01 sub_bc964d0`; full lifted body mirroring every instruction of [0xbc964d0, 0xbc966b0); every call quoted verbatim; extern "C" boundary symbols sub_75720/sub_9bc830; direct vtable-slot calls in place of the jmp-rax thunk sub_eea6040; LIFT_FN registry entry + footprint; static_asserts repeated in source).
- Created docs/functions/bc964d0.md (mechanical facts + 'Reversed source (complete)' section, free of [?]/[I]/TODO/UNVERIFIED; every call quoted verbatim).
- verify_oc.py on the dossier: claimed=43 match=43 mismatch=0 no-such-instr=0.
- python tools/sigs/liftcheck.py 0xbc964d0 -> LIFTCHECK OK 0xbc964d0.

## FILES
src/client/features/render/native/bgfx/sub_bc964d0.h (new)
src/client/features/render/native/bgfx/sub_bc964d0.cpp (new)
docs/functions/bc964d0.md (new)

## LIFTCHECK
LIFTCHECK OK 0xbc964d0

## UNRESOLVED CALL
none

## TOOL REQUESTS
None

CLOSES? YES
