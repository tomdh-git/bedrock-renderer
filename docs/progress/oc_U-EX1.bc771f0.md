## NEXT
DONE: sub_bc771f0 lifted (0xbc771f0, 0x157 bytes), liftcheck OK.

## UNIT
X1.bc771f0 LIFT sub_bc771f0 (0xbc771f0, 0x157 bytes, depth 3, D0, 0 callees in set)

## GOAL
Lift function 0xbc771f0 (bgfx handle-allocator release/refcount helper) into C++ that does exactly what the exe does: same reads, writes, calls, order, return, exact x64 ABI signature. Contract: docs/RENDER_NATIVE_SPEC.md. Rules: docs/OPENCODE_BRIEF.md.

## INPUT DATA (read, not regenerated)
- docs/functions/bc771f0.md: size 0x157 bytes ([0xbc771f0..0xbc77347)), 26 blocks (24 reached by dataflow), 2 xrefs in. Signature inferred: u16* release(Alloc* a /*rcx*/, u16* out? /*rdx*/, u16 handle /*r8w*/) -> rax=a1. No direct callees. count @ +4; u16[0x80] table @ +0x208; per-handle 2-byte refcount/state @ +0x308 + handle*2.
- docs/progress/_d_U-EX1.bc771f0.txt: function row confirms 0x157 bytes, depth 3, milestone 1, region bgfx, status D0; CALLEES IN THE LIFT SET empty.
- docs/data/native_boundary.tsv: 0xbc771f0 not listed as boundary.

## FILES
- src/client/features/render/native/bgfx/sub_bc771f0.h (new: layout constants + static_asserts + signature)
- src/client/features/render/native/bgfx/sub_bc771f0.cpp (new: lifted source, LIFT marker, LIFT_FN entry)
- docs/functions/bc771f0.md (extended: added 'Reversed source (complete)' section)

## DISASSEMBLY (read, verbatim from rdis.exe)
[0xbc771f0, 0xbc77347), 0 calls, no callees. Layout [V] from body: +0x04 u32 count; +0x08 u32 dense[128]; +0x208 u16 sparse[128] (handle or 0xFFFF); +0x308 u16 refcount[] indexed by handle*2. Algorithm: invalid handle (0xFFFF) -> *out=0xFFFF; else --refcount[handle], if !=0 -> *out=0xFFFF; else remove handle from sparse table and hash-probe compact dense/sparse; on success *out=handle, on not-found *out=handle. Every instruction address covered by cited ranges below.

## NEXT STEP
None - unit complete.

## LIFTCHECK
LIFTCHECK OK 0xbc771f0

## UNRESOLVED CALL
none

## CLOSES?
YES
