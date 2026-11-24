## NEXT
DONE

## FILES
docs/progress/oc_U-EX1.bc76380.md (this result file, rewritten)
docs/functions/bc76380.md (extended: signature, callee table, Reversed source (complete) replaced)
src/client/features/render/native/bgfx/sub_bc76380.cpp (new: lifted body, first line `// LIFT 0xbc76380 size 0x107 1.26.62.01 D3D12 submit RTX override`)
src/client/features/render/native/bgfx/sub_bc76380.h (new: layout constants and static_asserts, signature, LIFT_FN registration in the .cpp)

## LIFTCHECK
LIFTCHECK OK 0xbc76380

## UNRESOLVED CALL
0xbc76448  call qword ptr [0xF9A90C8] (rcx = &rsp+0x34 dest buffer): reads the qword at data_f9a90c8; the stored raw value is RVA 0xF9B0AE2, which is UTF-16 string data ("Pati"), not code, so the call target is not statically resolvable to a lifted function or a boundary wrapper. Not in the lift set (0 callees in set), docs/data/native_boundary.tsv does not exist. Documented honestly per the LIFT brief; no wrapper invented. The lifted code reads the slot at runtime via RewriteRegistry::imageBase() + 0xF9A90C8 and calls it, exactly as the original does (same read, same call, same return use).

## Verification notes
- All 78 instructions of [0xbc76380, 0xbc76487) are cited by `// 0xA..0xB` ranges or quoted verbatim in the dossier and the .cpp; verify_oc on the dossier: claimed=78 match=78 mismatch=0 no-such-instr=0.
- Every original call is quoted verbatim: 0xbc763c5  call 0xEBCE5E0, 0xbc763de  call 0xEBCE760, 0xbc76411  call 0xEBCE5E0, 0xbc76440  call 0xEBCE650, 0xbc76448  call qword ptr [0xF9A90C8], 0xbc76481  call 0xE951550.
- sub_ebce5e0 (strlen-like) -> std::strlen; sub_ebce650 (bounded copy) -> std::memcpy; sub_ebce760 (bounded find-char) lifted inline as find_char_bounded (same reads, same order, no writes); sub_e951550 declared noreturn.
- Exact x64 ABI signature: uint32_t sub_bc76380(uint64_t* slot /*rcx*/, uint32_t ch /*rdx*/, uint32_t flags /*r8d*/, uint32_t /*r9 unused*/); return in eax/edi; stack cookie stash/verify replicated (__security_cookie read at data_1230a0c0, twice).

CLOSES? YES
