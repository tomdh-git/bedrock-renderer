# Progress: U-PASS (consumer of thread-local pass-object pool vectors)

## NEXT
Step 1: enumerate every caller of 0x5aba5c0 via xref.py callers; verify the getter dossier (return type, TLS storage) against a fresh disrange of 0x5aba5c0.
Step 2: find function(s) that READ the pool vectors at pass offsets +0x648, +0x750, +0x768, +0x780, +0x8a0.
Step 3: decode type/vtable of object returned by 0x5aba5c0 via factory at PassQueueRegistry+0x38, vtbl[2]=0x9BD6D0.

## Unit task (from brief)
- Decode 0x5aba5c0 fully: return type, how the object is stored per thread.
- Find function(s) that READ the pool vectors at pass offsets +0x648, +0x750, +0x768, +0x780, +0x8a0 (pushers known: 0x6760e60, 0x675f3b0, 0x675fb30, 0x6760710, 0x6760a80, 0x5aba6d0; pools are the draw-item pools of DrawItem.h/DrawItemProto in BatchActorBuilders.h).
- Say what the consumer does with each 1-byte pool tag and with P+0x50/P+0x51 of DrawItemProto (mPassRecord: mat4 +0x00, translation +0x30, byte +0x50, byte +0x51).
- If consumer not found: list every function ruled out and why.
- Output: docs/progress/oc_U-PASS.md only. NEXT block at top, append after every step.

## Known context (from dossiers, [V]/[I] as tagged there)
- 0x5aba5c0 dossier exists (docs/functions/5aba5c0.md): ThreadLocalObject<T>::get; rcx = F->renderer + 0x9D0 (PassQueueRegistry); TLS u32 slot index at +0xA0; factory std::function at +0x38; instance list at +0x40/+0x48 guarded by mutex +0x50; first call per thread allocates 0x8C8 node (payload 0x8B8 at node+0x10), builds via factory vtbl[2], tlsSet, list_push_back; returns &n->payload (Q). Callers: 0x5ab8e20, 0x66232b0 endFrame, 0x6640d80 light visitor, 0x6646980 item visitor, 0x66560f0 sky visitor, 0x6664a00 UI visitor, 0x666aca0 effect visitor, 0x66742f0 editor visitor, 0x66a6830/0x66a9d50/0x66ade80 gameface extractor, 0x66bb7b0.
- DrawItem.h: 0xC8 DrawItem record {mValidMask +0x00, mKindA +0x04, mU16PoolA(+0x8A0) +0x10, mPool780 +0x28, mPool768 +0x2A, mPool750 +0x2C, mU16PoolB(+0x690) +0x3C, mPool660 +0x40, mPool648 +0x42, mU32Pool(+0x630) +0x44, mPoolA(+0x588) +0x52, mPoolB(+0x108) +0xB2}. Pools: +0x00 items, +0x108 shared(0x38B), +0x588 smallvec(0x30), +0x630 u32, +0x648 transform(0x48), +0x660 bounds(0x2C), +0x690 u16, +0x750 state(0x58), +0x768 shader(0x88), +0x780 geometry(0x58), +0x8A0 u16.
- BatchActorBuilders.h: DrawItemProto P+0x50/P+0x51 are bytes of mPassRecord (P = [rbp+0x718]: mat4 +0x00, translation +0x30, byte +0x50, byte +0x51). Byte pools (1-byte tags): +0x1f8->item+0x9E, +0x300->+0x88, +0x3f0->+0x74, +0x570->+0x54, +0x6d8->+0x36, +0x858->+0x16, +0x888->+0x12.
- vv_lambda_bodies.md: 0xbc38c20 NothingTask item-list body reads entries {u64, DrawItem*, pass-object*} at [r+0x68,r+0x70); state pool +0x750 stride 0x88 (+0x78 for material compare); record +0x2A index into pool +0x750; u32 pool +0x618 indexed by record +0x44; submits via 0xbcc38e0. Tagged as the DrawItem consumer [V structure, I per-item semantics].
- Pushers of record: 0x67e8020/0x67e8900/0x67e5f00 (particle/clouds ID-PUSH), 0x6765020 & 0x6768c70 (RenderMark::bodyActor 0x66d0a00), plus 10 BatchActor variant builders (0x66bf290 family).

## Type/vtable of pass object (PARTIAL)
- Getter 0x5aba5c0 fully disassembled [V]: ThreadLocalObject<T>::get. rcx=F->renderer+0x9D0 (PassQueueRegistry). TLS slot at +0xA0. Alloc 0x8C8 node via sub_eea6040 ([0xF99FFA0]), node+0x10=payload(0x8B8). Factory std::function at registry+0x38 called via vtbl[2] (0x9BD6D0 = sub_9bd6d0). List push at registry+0x40/+0x48 guarded by mutex +0x50. Returns &n->payload. 95 calling functions.
- sub_9bd6d0 (vtbl[2] factory): calls sub_9bd570(rdi=factory_this). sub_9bd570 manages a callback registration array at [tls_base+0xCC0]/[tls_base+0xCC8] (8-byte elements), stores callback at [returned_slot] = 2nd arg. Returns slot pointer.
- Exact type name/vtable of the 0x8B8-byte payload object NOT yet determined from static analysis.

## Drain function search — RULED OUT (no single function reads all 5 pools [0x648/0x750/0x768/0x780/0x8A0] with pass-object register base)

### RULED OUT: All getter callers (all are PUSHERS, write TO pools not read FROM)
- 0x66232b0 endFrame: pushes 0x250/0x2B0/0xF18-byte items to pools at +0x20/+0x50/+0x38 (3 getter calls)
- 0x6646980 item visitor (4 getter calls): pushes 0x18-byte items to [rsi+0x98]/[rsi+0xA0] vector
- 0x66ea3d0 (14 getter calls): writes u16 to [reg+0x8A8], advances by 2
- 0x66560f0, 0x6664a00, 0x666aca0, 0x66742f0, 0x670b6e0, 0x6722cb0, 0x6792d90, 0x67762e0: all in dispfun results for all 5 displacements but use [rbp+...] stack locals, not pass-object-relative

### RULED OUT: sub_c21db0 (0xc21db0..0xc23831) — STRUCTURE COPY, not drain
- source=rsi, dest=rdx. Copies [rsi+0x648] (single ptr), vector pair [rsi+0x748]/[rsi+0x750] (state pool), [rsi+0x780] (single ptr), [rsi+0x8A0] (single ptr).
- Calls sub_26e880 for each vector pair (16-byte elems, refcount inc).
- DOES NOT read [rsi+0x768] — confirmed via fld 0x768 scan.
- Called by: sub_c1cb60 (2x), sub_36bc250 (1x), sub_3722fe0 (1x) — none of these read pool offsets directly.

### RULED OUT: sub_833e30 (0x833e30..0x837899) — REFCOUNT DESTRUCTOR, not drain
- Reads [rsi+0x750], [rsi+0x768], [rsi+0x780], [rsi+0x8A0] but NOT [rsi+0x648] — confirmed via fld 0x648 scan.
- Does refcount decrements on sub-objects at offsets 0x1E00-0x2000 range.

### RULED OUT: sub_c1cb60 (0xc1cb60..0xc1ce49) — VECTOR REALLOCATION
- Grows vector: allocates new buffer, calls sub_c21db0 to copy items, calls sub_c12f20 to destroy old items, frees old memory.
- Does not read pool offsets directly.

### RULED OUT: sub_c12f20 (0xc12f20..0xc13cc3) — PER-ITEM DESTRUCTOR
- Only reads [rsi+0x780] out of the 5 target offsets (confirmed via fld scans).
- Resets vector fields (begin/end/capacity to 0/0xF), frees memory.

### RULED OUT: sub_26e880 (0x26e880..0x26e9cb) — GENERIC VECTOR COPY
- Args: rcx=dst_ptr_addr, rdx=count, r8=src_begin, r9=src_end. 16-byte elems, refcount inc.
- Called by sub_c21db0 for each vector pair. Not specific to pass object pools.

### RULED OUT: 0xbc38c20 (DrawItem consumer / NothingTask body)
- Tagged as DrawItem consumer in vv_lambda_bodies.md.
- Reads [pass_object+0x750] (state pool base, stride 0x88) and [pass_object+0x618] (u32 pool).
- Does NOT read all 5 target offsets: reads 0x618 not 0x648; does not read 0x768/0x780/0x8A0.
- Iterates entries {u64, DrawItem*, pass-object*} at [r+0x68,r+0x70).

## Closest matches (together cover all 5, but neither individually)
- sub_c21db0: reads 0x648, 0x750, 0x780, 0x8A0 — MISSING 0x768
- sub_833e30: reads 0x750, 0x768, 0x780, 0x8A0 — MISSING 0x648

## Verification log
- fld 0x648/0x750/0x768/0x780/0x8a0 --r: scanned all 5 offsets. Most hits are [rbp+0xXXX] stack locals.
- dispfun.py 0x648 0x750 0x768 0x780 0x8a0: lists functions accessing all 5 displacements, but mostly stack-relative.
- callers 0x5aba5c0: 95 calling functions, all checked are pushers.
- endFrame (0x66232b0) NOT in dispfun results — delegates, doesn't directly access pool offsets.
- sub_c1cb60/36bc250/3722fe0 (callers of sub_c21db0): none read pool offsets directly.
- sub_aaa7c0/c1cfb0/66a6830/670b6e0/6722cb0: none appear in fld results for any of the 5 offsets.