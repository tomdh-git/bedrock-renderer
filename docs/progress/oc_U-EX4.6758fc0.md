## NEXT
DONE

## FILES
- src/client/features/render/native/helpers/sub_6758fc0.cpp (lifted body: block-by-block translation of [0x6758fc0, 0x67590bf), LIFT marker, LIFT_FN registry entry, verbatim call quotes in #if 0 block)
- src/client/features/render/native/helpers/sub_6758fc0.h (packed this/entry/handle/stack structs with offsetof static_asserts, sub_6758fc0Layout with kFailSlotRva assert, signature void* sub_6758fc0(void* self))
- docs/functions/6758fc0.md (dossier: Reversed source section, DECISIONS, verbatim call quotes, all markers resolved)

## LIFTCHECK
GATE OK 0x6758FC0
LIFTCHECK OK 0x6758fc0
cppsyntax: OK
liftcheck: LIFTCHECK OK 0x6758fc0 (mismatch=0)
static_assert: present (source + dossier)

## UNRESOLVED CALL
none

## NOTES
- Signature: void* sub_6758fc0(void* self); RCX=self; result in RAX via tail call jmp 0xE935700 at 0x6759091 to native::sub_e935700 (lift set, called directly via its symbol). Early-exit path (*(self+0x8)==0) returns nullptr (original leaves RAX unspecified).
- Data slot 0xF9A8C78: call qword ptr [0xF9A8C78] at 0x67590b8 modeled exactly — target read at call time via RewriteRegistry::imageBase() + kFailSlotRva, four zero x64 arguments, __debugbreak()/__assume(0) after (noreturn). Data-slot rule precedent; UNRESOLVED CALL = none.
- Dead stores documented as dead: [rsp+0x20]=0 home-slot store; add rdx,0x27 / or rdx,0x27 (RDX clobbered by sub_e935700->sub_392960 before any read); xmm6 save/restore (xmm6==0 at every store site).
- No stubs, no TODO/[?]/UNVERIFIED/UNRESOLVED/incomplete markers; plain factual comments only.

CLOSES? YES
