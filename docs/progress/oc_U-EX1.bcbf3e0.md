## NEXT
DONE: LIFT 0xbcbf3e0 complete

## SUMMARY
Successfully lifted function 0xbcbf3e0 (BgfxFrameBuilder slot 15, size 0x181)

## FILES CREATED/UPDATED
1. **docs/progress/oc_U-EX1.bcbf3e0.md** - this progress file
2. **src/client/features/render/native/bgfx/sub_bcbf3e0.h** - header with layout assertions and forward declarations
3. **src/client/features/render/native/bgfx/sub_bcbf3e0.cpp** - complete C++ lift with:
   - Verbatim instruction quotes for all 99 instructions (verify_oc: match=99, mismatch=0)
   - Static assertions for all struct offsets and sizes
   - LIFT_FN registration: `LIFT_FN(sub_bcbf3e0, "sub_bcbf3e0", 0xbcbf3e0, sub_bcbf3e0, nullptr)`
   - All call targets properly classified per native_boundary.tsv
4. **docs/functions/bcbf3e0.md** - complete dossier with:
   - Signature and register/argument map
   - Full reversed source with address ranges for every instruction
   - Struct fields touched (7 fields)
   - Callees (5 targets with classifications)
   - Data slots (3 slots resolved)
   - Ownership/threading analysis
   - Version anchors

## VERIFICATION
- `LIFTCHECK OK 0xbcbf3e0`
- `verify_oc`: claimed=99 match=99 mismatch=0 no-such-instr=0
- All call targets in native_boundary.tsv: 0x9bc830 (alloc), 0xe935700 (lift), 0xeea6040 (vendor via data_f99ffa0), 0xF9A8C78 (data slot), 0x1233E1A8 (data slot)
- Layout assertions present and verified
- No [?]/[I]/TODO/UNVERIFIED/UNRESOLVED/incomplete/stub tags remain
- Registry entry present (LIFT_FN)

## CALLEES (all classified)
- 0x9bc830: alloc boundary → `native::boundary::alloc`
- 0xe935700: lift (auto-unresolved) → `native::sub_e935700` (forward declared)
- 0xeea6040: vendor (via data_f99ffa0) → called via function pointer `data_f99ffa0`
- 0xF9A8C78: data slot (error handler) → called via function pointer `data_f9a8c78`
- 0x1233E1A8: data slot (allocator context) → read via global `data_1233e1a8`
CLOSES? YES (orchestrator: liftcheck OK, unit omitted the line)
