## NEXT
DONE: unit U-EX1.bc7a9d0 complete; `python tools/sigs/liftcheck.py 0xbc7a9d0` printed `LIFTCHECK OK 0xbc7a9d0`.

## Work done
- Read contract (docs/RENDER_NATIVE_SPEC.md), hard rules (docs/OPENCODE_BRIEF.md), input data (_d_U-EX1.bc7a9d0.txt).
- Verified callees against docs/data/native_boundary.tsv and docs/data/native_functions.tsv: 0xE9E7970 (crt, __chkstk-style probe) and 0xE951550 (crt, stack-cookie failure, noreturn) are boundary; 0xEBCE390 (lift, jmp 0xEEC6EC0 memcpy forwarder); 0xEBCE430 is a 5-byte forwarder (`movzx edx,dl; jmp 0xEEC6ED0` -> crt IAT memset thunk) outside both tables, handled per rule 69: its three fill-0 calls are replaced with the std::memset intrinsic they tail-call, documented in the .cpp and dossier; every call target is resolved.
- Disassembled 0xbc7a9d0 (size 0x5e3, extent 0xbc7a9d0..0xbc7afb3 per .pdata): 3-pass LSD radix sort over u32 keys with a parallel u32 array (digits key&0x7FF, (key>>9)&0x1FFC byte-offset bins, key>>22), pairwise histogram with sortedness fast paths (including the odd-n flag-overwrite quirk at 0xbc7aab9..0xbc7aac3), group-of-4 exclusive prefix scan, pairwise distribute with odd tail, tail memcpy(keys,workKeys,count*4) via sub_ebce390 and conditional parOut->parIn copy (movups 32-byte bulk vs u32 loops), /GS cookie via data_1230a0c0 with sub_e951550 on mismatch.
- Caller 0xbc6aeb0 passes count as 5th stack arg (call at 0xbc6aefd).
- Created src/client/features/render/native/bgfx/sub_bc7a9d0.h (Bc7a9d0Frame overlay, static_asserts, kGblCookie=0x1230A0C0, digit constants, forward declarations, footprint declaration).
- Created src/client/features/render/native/bgfx/sub_bc7a9d0.cpp (`// LIFT 0xbc7a9d0 size 0x5e3 1.26.62.01 sub_bc7a9d0`, full verbatim instruction quotes with // 0xA..0xB range cites, all 6 calls quoted verbatim, LIFT_FN + footprint, no [?]/[I]/TODO/UNVERIFIED/stub).
- Created docs/functions/bc7a9d0.md (dossier: signature, ABI map, phases, callees, 'Reversed source (complete)', no forbidden tokens).
- verify_oc on source+dossier: claimed=16 match=16 mismatch=0 no-such-instr=0.

## FILES
- docs/progress/oc_U-EX1.bc7a9d0.md (this result file; created)
- docs/functions/bc7a9d0.md (dossier; created)
- src/client/features/render/native/bgfx/sub_bc7a9d0.h (created)
- src/client/features/render/native/bgfx/sub_bc7a9d0.cpp (created)

## LIFTCHECK
LIFTCHECK OK 0xbc7a9d0

## UNRESOLVED CALL
none

CLOSES? YES
