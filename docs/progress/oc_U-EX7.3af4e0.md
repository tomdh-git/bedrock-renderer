## NEXT
DONE

## UNIT
U-EX7.3af4e0: lift sub_3af4e0 (0x3af4e0, 0x83 bytes, depth 0, D0, 0 callees in set)

## STATE
Complete. All instructions disassembled and verified with rdis.
- sub_3b23c0 is classified as `lift` in native_boundary.tsv line 528. Forward-declared via sub_3b23c0.h, called directly per hard rule #66. Not a blocker.
- sub_3b23c0: lea rax,[0x128CC490]; ret (size 0x8). Returns &data_128CC490, no args.
- Indirect call via slot 0xF9A8B30: read function pointer from slot, call per indirect-call rule (hard rule #69). Not a blocker.
- __report_gsfailure (0xe951550) is boundary crt (native_boundary.tsv line 467).
- Stack cookie: XOR with stack proxy (address of local), check passes unless corrupted. __report_gsfailure receives cookie ^ rsp_proxy = __security_cookie.
- No null guards, no SEH, no stubs, no skipped branches. Cookie mismatch path fully lifted.

## FILES
src/client/features/render/native/helpers/sub_3af4e0.h (rewritten: layout constants, static_asserts, sub_3b23c0.h include, __report_gsfailure boundary decl, slot_f9a8b30_t, signature)
src/client/features/render/native/helpers/sub_3af4e0.cpp (rewritten: LIFT marker, verbatim quotes in #if 0 block, full lifted implementation with range citations, LIFT_FN registry entry)
docs/functions/3af4e0.md (rewritten: removed UNRESOLVED CALL, updated callee classification sub_3b23c0=lift, complete Reversed source section, no OPEN questions)
docs/progress/oc_U-EX7.3af4e0.md (this progress file)

## LIFTCHECK
LIFTCHECK OK 0x3af4e0

## UNRESOLVED CALL
none

CLOSES? YES
