## NEXT
DONE

## FILES
- docs/functions/bcb3cf0.md (extended)
- src/client/features/render/native/bgfx/sub_bcb3cf0_chunk2.cpp
- src/client/features/render/native/bgfx/sub_bcb3cf0_chunk2.h

## LIFTCHECK
Chunk 0xbcb54d0..0xbcb5e09 (size 0x939 bytes). First instruction: 0xbcb54d0  movups [rax+rdx],xmm0. Last instruction: 0xbcb5e08  int3. All instruction ranges in chunk cited with // 0xA..0xB comments. Every call in range quoted verbatim in #if 0 block. Coverage: 100% of instructions in [0xbcb54d0, 0xbcb5e09) belong to cited ranges. Calls: 34 calls total, all classified (lift/boundary/unresolved). No stubs, no skipped branches, no [?]/[I]/TODO/UNVERIFIED in code. Layout constants with static_asserts in header. LIFT_FN registry entry via kSub_bcb3cf0_Chunk2_Entry.

## UNRESOLVED CALL
0xEEC6DE0 at 0xbcb5601 and 0xbcb5a01 (direct call, not in lift set or boundary.tsv)
0xF9A8C78 at 0xbcb5ddd (indirect call via data slot, not in boundary.tsv)

CLOSES? NO UNRESOLVED CALL: 0xEEC6DE0 (direct) and 0xF9A8C78 (data slot) are neither in lift set nor boundary.tsv