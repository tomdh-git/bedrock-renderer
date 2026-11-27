## NEXT
DONE. Unit complete; liftcheck printed LIFTCHECK OK 0x8e56b0. No further work.

## FILES
- src/client/features/render/native/helpers/sub_8e56b0.cpp (created; first line: // LIFT 0x8e56b0 size 0x78 1.26.62.01 sub_8e56b0)
- src/client/features/render/native/helpers/sub_8e56b0.h (created; layout constants + static_asserts + signature + boundary::g_eea6040_thunk extern + sub_e935700 forward decl)
- docs/functions/8e56b0.md (created; dossier with Reversed source section, struct fields, verbatim call log)
- docs/progress/oc_U-EX7.8e56b0.md (this result file, updated)

## LIFTCHECK
LIFTCHECK OK 0x8e56b0

## UNRESOLVED CALL
none

## Summary
sub_8e56b0 (0x8e56b0, 0x78 bytes, depth 0, D0, 0 callees in set) lifted to C++ with the exact x64 ABI `void sub_8e56b0(void* node)` (node in RCX; void return since rax is never meaningfully set).
Callees, all resolved:
- 0x8e56d8  call 0xE935700 -> sub_e935700 (lift set, native::sub_e935700)
- 0x8e56ea  call 0x8E56B0 -> self-recursion (native symbol)
- 0x8e570a / 0x8e5720  call qword ptr [0xF99FFA0] -> sub_eea6040 (boundary/vendor via data slot 0xF99FFA0; native::boundary::g_eea6040_thunk; 1-byte `jmp rax` thunk at 0xeea6040, RAX = vfptr[0]/vfptr[1] destructor/delete, RCX = obj)
No stubs, no skipped branches, no null guards/SEH beyond the original, no [?]/[I]/TODO/UNVERIFIED. Every instruction in [0x8e56b0, 0x8e5728) cited or quoted verbatim; every call quoted verbatim and verify_oc clean.

CLOSES? YES
