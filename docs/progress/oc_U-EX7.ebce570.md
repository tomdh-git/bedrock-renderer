## NEXT
DONE
## FILES
- docs/progress/oc_U-EX7.ebce570.md (this result file)
- docs/functions/ebce570.md (dossier: Reversed source (complete))
- src/client/features/render/native/helpers/sub_ebce570.h (layout constants, static_asserts, signature)
- src/client/features/render/native/helpers/sub_ebce570.cpp (LIFT marker, body, LIFT_FN registry)
## SUMMARY
LIFT sub_ebce570 (0xebce570, 0x5c bytes, depth 0, D0, 0 callees in set). Bounded strncmp-like compare over two { char* ptr @+0x0; int32_t size @+0x8 } objects (rcx=a0, rdx=a1) with int32 count bound (r8d); bound = min(a0->size,a1->size,count) signed; byte loop returns (signed char)*a0-(signed char)*a1 on first difference or null termination, 0 when bound exhausted with equal size-mins. Zero callees, zero calls, no writes, no null guards (fail fast). Verified argument setup at callers 0xbc601a2/0xbc6021d/etc. (rcx/rdx/r8d matches). cppsyntax OK; liftcheck OK.
## LIFTCHECK
LIFTCHECK OK 0xebce570
## UNRESOLVED CALL
none
CLOSES? YES
