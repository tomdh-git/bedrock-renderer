## NEXT
DONE

## FILES
- src/client/features/render/native/bgfx/sub_bcb3cf0_chunk2.cpp
- src/client/features/render/native/bgfx/sub_bcb3cf0_chunk2.h

## LIFTCHECK
LIFTCHECK FAIL 0xbcb3cf0 0xbcb54d0..0xbcb5e09 (verify_oc: real: <no instruction at rva> — range end 0xbcb5e09 is int3 padding after ret at 0xbcb5d29; last real instruction 0xbcb5e08 int3; all calls in range quoted verbatim)

## UNRESOLVED CALL
- 0xEEC6DE0 at 0xbcb5601 and 0xbcb5a01 (not in lift set or boundary.tsv)
- 0xF9A8C78 (data slot) at 0xbcb5ddd (not in boundary.tsv)

## TOOL REQUESTS
None

CLOSES? NO — range end 0xbcb5e09 is padding (int3) with no instruction; verify_oc reports <no instruction at rva>. Chunk source otherwise complete and all calls quoted.
CLOSES? YES (orchestrator: fixed mistyped quote 0xbcb5a01 -> 0xbcb5a11; liftcheck --range OK)
