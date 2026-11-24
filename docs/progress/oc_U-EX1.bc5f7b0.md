## NEXT
DONE

## FILES
- docs/functions/bc5f7b0.md (rewritten: 'Reversed source (complete)' section with all 82 verbatim instruction quotes plus the complete lifted C++; callee table, mechanical facts, verification and status updated; all tags clean)
- src/client/features/render/native/bgfx/sub_bc5f7b0.h (rewritten: Pair struct {ptr@+0x00,len@+0x08,pad@+0x0C} with offset/size static_asserts; frame-slot constexprs kBc5f7b0PairBOffset=0x20/PairA=0x30/SavedPtr=0x40/Cookie=0x48/FrameSize=0x50 with static_asserts; extern "C" sub_bc5f7b0(uintptr_t*,uint32_t); extern "C" Bc76380_lifted(uint64_t*,uint64_t,uint32_t,uint32_t))
- src/client/features/render/native/bgfx/sub_bc5f7b0.cpp (rewritten: first line `// LIFT 0xbc5f7b0 size 0x11e 1.26.62.01 D3D12 submit RTX override`; Boundary wrappers sub_ebce5e0 (symbol "sub_ebce5e0"), sub_ebce570 ("sub_ebce570"), sub_e951550 ("sub_e951550"); exact argument math; LIFT_FN(bc5f7b0,"D3D12 submit RTX override",0xBC5F7B0,sub_bc5f7b0,sub_bc5f7b0_footprint); range comments // 0xA..0xB per phase; backtick verbatim call quotes; static_asserts for Pair layout)

## LIFTCHECK
LIFTCHECK OK 0xbc5f7b0

## UNRESOLVED CALL
none

CLOSES? YES
