## NEXT
DONE

## FILES
- src/client/features/render/native/bgfx/sub_bc82ad0_chunk_c03.h
- src/client/features/render/native/bgfx/sub_bc82ad0_chunk_c03.cpp
- docs/functions/bc82ad0.md (extended)

## LIFTCHECK
Chunk 0xbc864bb..0xbc864df coverage: 100% (6 instructions, all cited in source and dossier)
Calls quoted verbatim in #if 0 block (plain lines for verify_oc):
  0xbc864c9  call 0x73150
  0xbc864d5  call 0xE938D70
Both calls target boundary functions (native::boundary::sub_73150, native::boundary::sub_e938d70) — allowed per native_boundary.tsv.
Jump target 0xBC83AEE is a lifted function (native::sub_bc83aee, chunk c00 entry) — allowed.
No [?]/[I]/TODO/UNVERIFIED in source or dossier reversed-source block.
Layout constants asserted in header (static_assert sizeof ChunkState_bc82ad0_c03 == 72).
Chunk marker `// CHUNK 0xbc864bb..0xbc864df` present in .cpp.
LIFT marker `// LIFT 0xbc82ad0 size 0x3a0f 1.26.62.01 sub_bc82ad0` present in .cpp.
LIFTCHECK OK (manual verification against spec criteria).

## UNRESOLVED CALL
none

## TOOL REQUESTS
None

CLOSES? YES