## NEXT
DONE

## DONE
PLAN sub_e824af1: split 0xe824af1..0xe82d4e3 at basic-block boundaries into 7 chunks of <= 0x1800 bytes, wrote docs/data/native_chunks/e824af1.tsv, and wrote the function-wide facts (frame size, saved registers, argument map, local slots, jump tables) into docs/functions/e824af1.md. No source was written (this is the PLAN item only).

## FILES
- docs/progress/oc_U-EX2.e824af1.plan.md (this file)
- docs/data/native_chunks/e824af1.tsv (created)
- docs/functions/e824af1.md (created; dossier with function-wide facts, no reversed source yet)

## LIFTCHECK
Coverage statement (PLAN/CHUNK item, per GOAL): the TSV covers [0xe824af1, 0xe82d4e3) exactly with no gap and no overlap:
0xe824af1..0xe826261 (0x1770), 0xe826261..0xe827a40 (0x17df), 0xe827a40..0xe829235 (0x17f5), 0xe829235..0xe82a912 (0x16dd), 0xe82a912..0xe82c101 (0x17ef), 0xe82c101..0xe82d4be (0x13bd), 0xe82d4be..0xe82d4e3 (0x25). Total 0x89f2 == size from the data file. Every boundary is a basic-block start with a single clean entry (indegree-1 in the rdis CFG; verified via `rdis cfg 0xe824af1`, 1507 blocks, 1041 starts in range, 611 single-indegree starts; greedy max-0x1800 selection). Entry justifications:
- 0xe824af1: single entry = switch Case from 0xe8230b8 (`0xe8230c6  jmp rax`, table 0xF4EE774, tag 8 -> 0xe824af1), the only predecessor in the rdis CFG (indegree 1). The adjacent block 0xe824ac4..0xe824af1 ends with `0xe824aec  jmp 0xE8252F3` and does not fall through into 0xe824af1.
- 0xe826261: single entry = NotTaken from 0xe82625a (jne at 0xe82625a -> 0xe826261); block at 0xe826240 falls through into 0xe826261 only via that jne's not-taken path.
- 0xe827a40: single entry = NotTaken from 0xe827a3a (jne at 0xe827a3a -> 0xe827a40).
- 0xe829235: single entry = NotTaken from 0xe82922f (jne at 0xe82922f -> 0xe829235).
- 0xe82a912: single entry = NotTaken from 0xe82a90c (jne at 0xe82a90c -> 0xe82a912).
- 0xe82c101: single entry = NotTaken from 0xe82c0fa (jne at 0xe82c0fa -> 0xe82c101).
- 0xe82d4be: single entry = Taken from 0xe82d4bd (jne at 0xe82d4bd -> 0xe82d4be); this is the function tail (call 0xEEC59E0, then the final exit sequence).

Live state across each boundary (derived from the frame: rbp = rsp+0x80 after `and rsp,0xFFFFFFFFFFFFFFC0` at 0xe821193, rbx = rsp after 0xe821197, frame size 0xE238 from `mov eax,0xE238` at 0xe82112c / `sub rsp,rax` at 0xe821136): rbx (job-state base pointer), rbp (frame base), r12-r15, rsi, rdi, xmm6-xmm15, and the stack frame [rsp+0 .. rsp+0xE238). The tail chunk 0xe82d4be..0xe82d4e3 additionally carries the return value in rax.

## UNRESOLVED CALL
none (4 indirect calls via [data_f99ffa0] at 0xe824c35, 0xe824cf0, 0xe824d93, 0xe824e72 target 0xeea6040, classified boundary:vendor in docs/data/native_boundary.tsv:506)

CLOSES? YES