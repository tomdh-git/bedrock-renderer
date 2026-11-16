# U-D9a: Light-group description field layouts (Ambient / Directional / Point)

Status: IN PROGRESS. Appended after each listing. Static analysis only, exe 1.26.62.01.

## NEXT
Resume here:
1. Decode `docs/data/live/light_visitor.txt` + `docs/data/live_desc_sky_light_effect_1.26.62.01.txt` with python (little-endian, floats) to get concrete field values per tag.
2. Map Point ctor `docs/data/listings/lightgame_point_ctor_668ade0_668b057.txt` stores (done below, pending live cross-check).
3. Map Directional producer `lightgame_dirlight_producer_536aeb0_536b1d0.txt` and Ambient producer `lightgame_dirlight_producer2_536c1a0_536c2f0.txt` stores (done below, pending live cross-check).
4. Confirm which live tag/line matches each description type; identify the tag byte each producer inserts (`mov byte ptr [..],N` right before `call 0x5370960`).
5. Final per-type table: offset, size, type, meaning [V]/[I]/[?], tag byte, matching live tag/line.

Blocker: none yet.