## NEXT
DONE

## UNIT
U-EX1.bc75c30 — LIFT sub_0xbc75c30 (0xbc75c30, 0x2a9 bytes, depth 2, D0, 0 callees in set), region bgfx, Minecraft Bedrock 1.26.62.01 — COMPLETE.

## STATE
Lift finished and verified. Disassembly of [0xbc75c30, 0xbc75ed9) taken verbatim from rdis; every instruction inside a cited `// 0xA..0xB` range; all 5 calls quoted verbatim as `0xRVA  call target` in backtick quotes beside the call sites; verify_oc: source 5/5 match, dossier 150/150 match, mismatch=0, no-such-instr=0. No [?]/[I]/TODO/UNVERIFIED/stub/incomplete anywhere in source or dossier.

Callees (all resolved, none are blockers):
- 0xEBDBF10 sub_ebdbf10 — lift (boundary.tsv, depth-7 root D0) — forward-declared in sub_bc75c30.h (namespace native), called directly [brief rule 66]
- 0xEBDBF20 sub_ebdbf20 — lift — same
- 0xEBCE390 sub_ebce390 — lift — same (memcpy-like, dst/src/n)
- call r10 at 0xbc75cdc — r10 = [0xF99FFA0] = sub_eea6040 (vendor boundary, "thunk via data slot 0xF99FFA0 (loader-resolved)") — called per rule 69 by reading the slot at call time as a function pointer (g, slot->ptr, 0, 0, 0, 0); slot RVA documented. No UNRESOLVED CALL.

Function: void sub_bc75c30(Ctx* ctx, std::uint16_t idx); takes ctx+0x1C0 lock (sub_ebdbf10), decrements slot refcount (ctx+0x1E1DABE+idx*0x18), early-return releases lock; on zero: appends idx to stream free list (P+0xE509DC / count P+0xE50DDC), handles slot pointer via global [0x12ADF800] or default [0xF847A07], open-addressing hash-delete of key idx (entries ctx+0x1E1D2A4, aux ctx+0x1E1C2A4, count ctx+0x1E1C2A0, hash ((v*0x5EBCA77)>>19)*0x1B1&0x3FF, cluster rehash/drop), appends stream record tag 0x25 + savedIdx u16 via sub_ebce390, releases lock (sub_ebdbf20), ret.

## FILES
- src/client/features/render/native/bgfx/sub_bc75c30.h (new: layout constants + static_asserts, callee forward declarations, signature)
- src/client/features/render/native/bgfx/sub_bc75c30.cpp (new: lifted body; first line `// LIFT 0xbc75c30 size 0x2a9 1.26.62.01 sub_bc75c30`; LIFT_FN registry entry)
- docs/functions/bc75c30.md (new: dossier with Reversed source (complete))
- docs/progress/oc_U-EX1.bc75c30.md (this file)

## LIFTCHECK
LIFTCHECK OK 0xbc75c30

## UNRESOLVED CALL
none

CLOSES? YES
