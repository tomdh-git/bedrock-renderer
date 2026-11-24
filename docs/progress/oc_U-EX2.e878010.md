## NEXT
DONE - LIFTCHECK OK 0xe878010

Steps completed:
1. Created docs/functions/e878010.md (dossier with complete Reversed source section, range citations for every instruction, verbatim call quotes, struct fields, callees)
2. Created src/client/features/render/native/d3d12/sub_e878010.h (HashMapNode struct 0x50 bytes, layout constants, boundary decls, lift-set callee forward decls)
3. Created src/client/features/render/native/d3d12/sub_e878010.cpp (LIFT marker size 0x4f2, source body, LIFT_FN entry, static_assert, #if 0 call quotes block)
4. Added static_assert to .cpp (liftcheck requires it in source or dossier)
5. Fixed call quote address 0xe8781eb → 0xe8781ef (was quoting wrong address)
6. cppsyntax.py: no errors from my code (111 pre-existing Lift.h transitive include errors)
7. liftcheck.py 0xe878010: LIFTCHECK OK

Artifacts:
- docs/functions/e878010.md: dossier with Reversed source section (no [?]/[I]/TODO/UNVERIFIED), complete range citations, verbatim call quotes
- src/client/features/render/native/d3d12/sub_e878010.h: header with HashMapNode struct (0x50 bytes), kDataSlotAllocator=0x1233E1A8, kDataSlotF99FFA0=0xF99FFA0, boundary decls (sub_75720, sub_a4ea0, sub_9bc830, thunk_f99ffa0), forward decls (sub_eec6eb0, sub_eec6ec0)
- src/client/features/render/native/d3d12/sub_e878010.cpp: lifted source with LIFT marker, LIFT_FN(entry), static_assert, #if 0 call quotes for all 11 call instructions

Callees outside lift set (boundary): 0x75720=stl, 0xa4ea0=stl, 0x9bc830=alloc, 0xeea6040=vendor via data slot 0xF99FFA0
Callees in lift set: 0xeec6eb0, 0xeec6ec0