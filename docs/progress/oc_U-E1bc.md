# UNIT U-E1bc — Item visitor 0x6646980 tag table (tags 0,1,2,3,4,5,7,9)

## Target
Item-group visitor 0x6646980, jump table 0xF2BF2D0 (11 entries, decoded by tools/sigs/jt.py). Per-tag table for tags 0,1,2,3,4,5,7,9:
case head RVA, description register at the case, type, callee(s) reached first, inline vs tail-jump to extractor, one-line pointer to existing field-level reads.

## NEXT
Resume: run `python tools/sigs/jt.py 0xF2BF2D0`; run casewalk for tags 1 and 9; write the table; run verify_oc.py; append ## TOOL REQUESTS.

## STATUS
- [ ] jt.py decode
- [ ] tag 0 table row (done: oc_U-D5i.md)
- [ ] tag 1 casewalk
- [ ] tag 2 table row
- [ ] tag 3 table row (oc_U-D5i.md UI tag 3 — note: that is the UI visitor 0x6664a00, NOT the Item visitor; Item tag 3 is ChunkGeometry)
- [ ] tag 4 table row (oc_U-D5c.md)
- [ ] tag 5 table row (oc_U-D5d.md)
- [ ] tag 7 table row (oc_U-D5f.md)
- [ ] tag 9 casewalk
- [ ] verify_oc.py
- [ ] ## TOOL REQUESTS