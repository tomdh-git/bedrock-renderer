## NEXT
DONE - sub_ebce650 (0xebce650, 0x6b bytes) lifted; liftcheck printed LIFTCHECK OK; no further steps.

## UNIT
U-EX7.ebce650 CLOSED: lift sub_ebce650 (0xebce650, 0x6b bytes, depth 0, D0). Leaf apart from one call to sub_ebce390 (class `lift`, called directly via forward declaration; not a blocker).

## FILES
src/client/features/render/native/helpers/sub_ebce650.h   (new: SrcDesc layout {char* ptr @0x00, int32_t maxlen @0x08} + static_asserts, signature, forward declaration of native::sub_ebce390)
src/client/features/render/native/helpers/sub_ebce650.cpp (new: // LIFT 0xebce650 size 0x6b 1.26.62.01 sub_ebce650, lifted body with // 0xA..0xB range citations, verbatim #if 0 quote block, LIFT_FN(sub_ebce650,"sub_ebce650",0xEBCE650,sub_ebce650_lifted,nullptr))
docs/functions/ebce650.md                                 (new: signature, register map, Reversed source (complete), struct fields touched, callees, open questions none, version anchors)

## DISASSEMBLY [V]
rdis dis 0xebce650 0x6b; function = [0xebce650, 0xebce6bb), ret at ebce6ba, int3 padding from ebce6bb.
Instructions ebce650..ebce6ba (36 instructions); only call: ebce6a0 `call 0xEBCE390` (target sub_ebce390, lift set).
Semantics lifted: bound=min(maxlen,srcdesc->maxlen); len = src==0 ? 0 : strnlen_s(src,bound); count=min(dstSize-1,len) (signed); sub_ebce390(dst,src,count); dst[count]=0; return count.

## LIFTED SOURCE
.cpp first line: // LIFT 0xebce650 size 0x6b 1.26.62.01 sub_ebce650
Every instruction inside a cited // 0xA..0xB range; the call quoted verbatim as `0xebce6a0  call 0xEBCE390` (plain line in #if 0 block, verify_oc-parsable).
No [?]/[I]/TODO/UNVERIFIED/stub text; no null guards/SEH; no changed behavior.

## DOSSIER
docs/functions/ebce650.md: signature, register/argument map, Reversed source (complete) with per-phase ranges and C-like statements, struct fields touched (SrcDesc +0x00 R, +0x08 R), callees (sub_ebce390 = lift, direct call), open questions: none, version anchors.

## LIFTCHECK
`python tools/sigs/liftcheck.py 0xebce650` printed exactly:

LIFTCHECK OK 0xebce650

Supplementary: verify_oc on the .cpp and the dossier: claimed=36 match=36 mismatch=0 no-such-instr=0 (both files).
cppsyntax.py: identical result to the reference unit sub_ebce390.cpp (5 pre-existing macro-lookup diagnostics under isolated /Zs, same as the existing lift; builds are forbidden by the brief, liftcheck does not run cppsyntax).

## UNRESOLVED CALL
none (the only call, 0xebce6a0 call 0xEBCE390, targets sub_ebce390 which is class `lift` in docs/data/native_functions.tsv and docs/data/native_boundary.tsv)

CLOSES? YES
