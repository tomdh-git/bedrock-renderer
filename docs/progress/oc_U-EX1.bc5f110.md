## NEXT
DONE

## FILES
created: src/client/features/render/native/bgfx/sub_bc5f110.h
created: src/client/features/render/native/bgfx/sub_bc5f110.cpp
rewritten: docs/functions/bc5f110.md
created: docs/progress/oc_U-EX1.bc5f110.md

## LIFTCHECK
LIFTCHECK OK 0xbc5f110

## UNRESOLVED CALL
none: every call target is either lifted (0xebcf430 = native::sub_ebcf430) or listed in docs/data/native_boundary.tsv (0xe9e7970 __chkstk, 0xebce470, 0xe951550 __security_check_cookie) or a loader-resolved data slot read at call time ([0xF99FFA0], [0xF9A8CB0]).

## Summary
Lifted sub_bc5f110 (0xbc5f110, size 0x121), the variadic log helper / "RendererContextD3D12 base slot 59". The function's de facto x64 ABI is 4 register args (int32 level, const char* fmt, varg1 in R8, varg2 in R9); it does not use va_start but spills R8/R9 into a contiguous 2-slot block at RBP+0x1FD0/0x1FD8 and passes &[rbp+0x1FD0] as the va_list pointer to sub_ebcf430. Declared with 4 explicit parameters (identical register assignment, stack varargs beyond R9 ignored like the original) so LIFT_FN/Thunk can take its address. Calls: sub_e9e7970 (__chkstk, boundary crt) x2, sub_ebcf430 (lift set) x2, call qword ptr [0xF99FFA0] (loader-resolved CFG dispatch of logger vtable slot 1), sub_ebce470 (boundary crt, null-logger path), call qword ptr [0xF9A8CB0] (loader-resolved terminate pointer), sub_e951550 (__security_check_cookie, boundary crt). Stack cookie [0x1230A0C0] ^ RBP validated at prologue and epilogue; __security_check_cookie + int3 on failure. Layout constants and static_asserts in sub_bc5f110.h and re-asserted in the .cpp. LIFT_FN(sub_bc5f110, "sub_bc5f110", 0xbc5f110, sub_bc5f110, nullptr) registered.

CLOSES? YES
