## NEXT
DONE

## FILES
- docs/progress/oc_U-EX7.a14e0.md (this result file)
- docs/functions/a14e0.md (dossier: signature, Reversed source (complete) with verbatim call quotes, fields touched, callees, ownership, verification)
- src/client/features/render/native/helpers/sub_a14e0.h (A14e0This object mirror, static_asserts at 0x18/0x20/0x38/0x40/0x50/0x58/0x68/0x70 sizeof 0x78, kRvaFailSlot = 0xF9A8C78, sub_e935700 forward declaration, native::sub_a14e0 signature)
- src/client/features/render/native/helpers/sub_a14e0.cpp (lifted body, // LIFT 0xa14e0 size 0xd1 1.26.62.01 sub_a14e0 marker, verbatim #if 0 instruction quotes, range citations beside every block, LIFT_FN(sub_a14e0, "sub_a14e0", 0xA14E0, sub_a14e0, nullptr))
- docs/progress/gate/0xA14E0.log (gate log, produced by tools/ctx/gate.py)

## SUMMARY
LIFTED sub_a14e0 (0xa14e0, size 0xd1, depth 0, D0) for Minecraft Bedrock 1.26.62.01.
Behavior [V] from rdis dis 0xa14e0 0xd1:
- 0xa14e8 test byte [rcx+0x70],1; je 0xa1545 skips the body to the cleanup when bit 0 is clear.
- Body: rax = *(*(a0+0x40)) (idx 0x58) or rax = *(*(a0+0x38)) (idx 0x50); rdx = (int32_t)*(a0+idx) + rax - *(*(a0+0x18)); cmp rdx,0x1000.
- rdx < 0x1000: 0xa1540 call 0xE935700 with rcx = *(*(a0+0x18)). rdx >= 0x1000: prefix = *(*(*(a0+0x18))-8), block_start = (*(*(a0+0x18))-8) - prefix; block_start >= 0x20 takes the noreturn fail path (0xa1597..0xa15b0): call qword ptr [0xF9A8C78] with five zero args (slot read at call time per brief rule 68), then 0xa15b0 int3; otherwise 0xa1540 call 0xE935700 with rcx = prefix.
- Cleanup 0xa1545..0xa1596 always runs: qword 0 through *(a0+0x18), *(a0+0x38), *(a0+0x20), *(a0+0x40); dword 0 through *(a0+0x50) and *(a0+0x58); (a0+0x68) = 0; (a0+0x70) &= 0xFE; ret RAX = (a0+0x58).
- Calls: sub_e935700 is lift-classified (native_boundary.tsv line 505), called through its native symbol native::sub_e935700 (brief rule 66; header helpers/sub_e935700.h). Data slot 0xF9A8C78 is not a callee; read at call time (brief rule 68/69), not a blocker.
- No null guards, no SEH (none in the original - fail fast). Layout mirror with static_asserts in the header.

## LIFTCHECK
LIFTCHECK OK 0xa14e0

## UNRESOLVED CALL
none

CLOSES? YES
