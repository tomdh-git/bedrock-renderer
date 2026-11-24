## NEXT
DONE — U-EX1.bc6f800 lifted: sub_0xbc6f800 (bgfx destroy-handle enqueue, cmd 0x1D), size 0xbb, ABI void sub_bc6f800(Context* ctx /*rcx*/, std::uint16_t handle /*dx*/). Source + header written under src/client/features/render/native/bgfx/, dossier docs/functions/bc6f800.md updated (Reversed source + Calls sections). liftcheck printed LIFTCHECK OK 0xbc6f800; no unresolved calls.

## FILES
- docs/progress/oc_U-EX1.bc6f800.md (created, this result file)
- src/client/features/render/native/bgfx/sub_bc6f800.cpp (created; first line // LIFT 0xbc6f800 size 0xbb 1.26.62.01 sub_bc6f800; LIFT_FN registry entry)
- src/client/features/render/native/bgfx/sub_bc6f800.h (created; layout constants + static_asserts for Context+0x1C0/0x1CFD0C8, Frame+0xE05820/0xE05828/0xE478AC/0xE498AC; forward declarations native::sub_ebdbf10/sub_ebce390/sub_ebdbf20)
- docs/functions/bc6f800.md (changed; Reversed source (complete) and Calls sections rewritten, callees now class lift, no unresolved calls)

## LIFTCHECK
LIFTCHECK OK 0xbc6f800

## UNRESOLVED CALL
none — all four calls (0xbc6f828 sub_ebdbf10 lock, 0xbc6f870/0xbc6f89c sub_ebce390 cmdPost append, 0xbc6f8ad sub_ebdbf20 unlock) target lift-classified callees registered in docs/data/native_boundary.tsv, forward-declared as native::sub_<rva> with signatures from the call sites and called directly.

CLOSES? YES
