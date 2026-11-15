# Dossier: BatchActor variant builders (0x66bf290 family) and helpers, 1.26.62.01 (static, extractors-core)

Struct header: src/sdk/mc/deps/minecraft_renderer/framebuilder/BatchActorBuilders.h. Tags [V]/[I]/[?]. Disassemble with `python tools/sigs/disrange.py <lo> <hi>`.

## Family structure [V]
Sizes: 0x66bf290 0x66c1920 0x66c3840 0x66c5760 = 0x12e6 B (1031 instr, identical code); 0x66cc7a0 0x66ce8d0 0x66c7680 0x66c98e0 = 0x13f2 B (1086 instr, identical); 0x66bb7b0 = 0x114f; 0x66bd430 = 0x11f0. Within each group a rip-normalised diff differs only in: (1) the variant-copy jump table (0xf2bfa20/50/60/70 for the 12e6 group; 0xf2bfac0/80/aa0/ad0 for 13f2), (2) the pass-object byte-pool offsets used, (3) the 64-bit valid-mask constants. One template instantiated per pool combination [I].

Signature [V]: `void build(FrameCtx* rcx /*rcx+0x10 + 0x9D0 -> pass object via 0x5aba5c0*/, const BuilderSpan* rdx, Obj** r8 /*caller [rbp+0x778]; *r8 has a vtable, slot 9 is called*/, vec3* r9 /*unused*/, DrawItemProto* stack5 (rbp+0x380), float stack6 (rbp+0x388))`.

Body [V structure]:
```
if (span->count == 0 || *r8 == 0) goto fallback;
0x6769ee0(&bindings /*vector of 0x20-byte entries, shared_ptr ctrl at +8*/, span->count, span->begin, distance);   // [?] meaning
(*r8)->vfunc9(&tmp);                                   // CFG call, result unused
if (bindings.empty()) goto fallback;
small1 = SmallVector<0x20,1>(); small2 = same; for e in bindings: 0x676a670(&small1,&small2,e);
sv78 = copy(small1) (0x6764990); svA8 = copy(sv78);
pass = 0x5aba5c0(frameCtx->+0x10 + 0x9D0);
item = DrawItem{};                                      // 0xC8 bytes zeroed (12 xmm stores)
pool780.push(proto->mGeometry) (0x675f3b0) ; item.+0x28 = size-1     // mask 0x1000
pool648.push(proto->mTransform) (0x675fb30); item.+0x42
pool660.push(proto->mBounds) (0x6762270)   ; item.+0x40              // absent in 0x66bb7b0
pool768.push(shader head + 0x78 block via 0xe869ff0, owned moved); item.+0x2A
pool750.push(proto->mState); item.+0x2C
pool8a0(u16).push(proto->mU16A); item.+0x10 ; pool690(u16).push(proto->mU16B); item.+0x3C
for each byte pool of this variant: pool.push_back(0); item.<field> = size-1; mask |= bit   // table below
pool588(0x30).push(svA8) (0x6764990 / grow 0x6765870); item.+0x52; mask |= 0x200000000
pass.items.push(item)   (memcpy 0xC8 via 0xeec6ec0, or grow 0x5aba6d0)
release svA8/sv78/small*/bindings (lock dec [ctrl+0xC] -> vcall[8])
return;
fallback: the same item without the 0x588 small-vector (no +0x52), pools pushed from the proto, same epilogue.
```
Per-variant tables [V from the store sequences]:

| builder | byte pools -> item offsets | final mask (path with 0x588) |
|---|---|---|
| 0x66bf290 | 0x300->+0x88, 0x3f0->+0x74, 0x888->+0x12, 0x6d8->+0x36 | 0x1004000203487003 |
| 0x66c1920 | 0x300, 0x570->+0x54, 0x888, 0x6d8 | 0x1000000603487003 |
| 0x66c3840 | 0x300, 0x3f0, 0x858->+0x16, 0x6d8 | 0x1004000203487009 |
| 0x66c5760 | 0x300, 0x570, 0x858, 0x6d8 | 0x1000000603487009 |
| 0x66cc7a0 | 0x1f8->+0x9e, 0x300, 0x3f0, 0x6d8, 0x858 | 0x1004000203487009 |
| 0x66ce8d0 | 0x1f8, 0x300, 0x570, 0x6d8, 0x858 | 0x1000000603487009 |
| 0x66c7680 | 0x1f8, 0x300, 0x3f0, 0x6d8, 0x888 | 0x1004000203487003 |
| 0x66c98e0 | 0x1f8, 0x300, 0x570, 0x6d8, 0x888 | 0x1000000603487003 |
| 0x66bb7b0 | 0x318->+0x86, 0x300, 0x888 (no 0x660, no 0x6d8) | 0x1800000202407003 |
| 0x66bd430 | 0x318, 0x300, 0x858 (has 0x660) | 0x1800000203407009 |

The 13f2 group's bindings path shows two push sequences (first with partial mask 0x1000000003407001-family, then the full mask, with 0x676a480 between) [V call order]; the exact item count per call for that group is not separately verified [?].

## Pairing in 0x66d9af0 [V]
Corrects docs/functions/66d9af0.md phase 5; the table with the P50/P51/F/edi/C conditions is in docs/progress/extractors-core.md (E2).

## Helpers [V]
- 0x66d9710(src = DrawProtoSources*, out = DrawItemProtoPacked*): pure copy exactly as laid out in the header (+0x02 u16 from *src[0x30]; +0x06 u16 from desc+0x1C; +0x08 state 0x58 from src[0x20]; +0x60 u64 and +0x68 0x78-block (0xe869ff0) from src[0x18], owned pointer src[0x18]+0x80 moved to +0xE0; +0xE8 box = R+0x1C..0x33, +0x100 index = (R+0x34 != 0xFF) ? 0 : 0xFF; +0x104 vec4 = R+0x38; +0x118 mat4 = P[0..0x40), +0x158 = 0; +0x160 geometry moved from *src[0]: 0x30 bytes plus variant at +0x188 copied by jump table 0xf2bfb10 (case 3 = shared_ptr, lock inc [ctrl+8])).
- 0x66c11b0(out = DrawItemProto*, in = Packed*): moves each member to its aligned offset (+2->+4, +6->+8, +8->+0xC, +0x60/+0x68->+0x68/+0x70, +0xE0->+0xE8, bounds +0xE8->+0xF0, transform +0x118->+0x120 with tag +0x158->+0x160 (variants 0 copy 0x40, 1 move vector, 2 copy pointer), geometry +0x160->+0x168 with variant +0x198->+0x1A0 via table 0xf2bfa30). Instruction-complete.
- 0x66c17e0 (= 0x66bf150 = 0x66cc660 = 0x66a65b0, identical 0x140-byte code): proto destructor: if geometry index kind (+0x1A0) == 3 release shared_ptr +0x198; release every 0x28-byte stream element in vector +0x170/+0x178 whose tag (+0x18) == 2 (shared_ptr at +8), clear it; if transform tag (+0x160) == 1 free the matrix vector at +0x120 and zero it.
- 0x66a0f60(out = DrawItemGeometry*, frameCtx, meshRef, matPair, u32 count, u32 start, u32 x): out[0] = **frameCtx, +0x38 = 0, +0x40 = start, +0x48 = count, +0x50 = frameCtx, streams zeroed; when matPair.ptr->+0x18 exists and its byte +0x28 == 2 it resolves the index buffer through 0xc2aa290 / 0xc2adac0 / 0xc2adfd0 (variant visit, kind 3 = shared) else returns the empty geometry. Partial: resolver callees 0xc2aa290, 0xc2adac0, 0xc2adfd0, 0xc2ae240, 0x675d320 not decoded [?].

## Open (blocking)
- 0x6769ee0 / 0x676a670 / 0x6764990 (bindings collector over the 0x30-byte span elements with the float distance); identity of the 1-byte pool element types (+0x12/+0x16/+0x36/+0x54/+0x74/+0x86/+0x88/+0x9e) and of P+0x50 / P+0x51 values: needs the consumer side (submit reading DrawItem +0x74 etc.) [?].

## Bindings collector family (instruction-complete, static)
Element type `FaceBinding` (0x30 bytes, from the span at builder state +0x480/+0x488): +0x00 shared_ptr {ptr, ctrl (refcount at ctrl+0xC)}, +0x10 16-byte payload (copied; contains the sort key at +0x10 u64, +0x18 u32, +0x1C u32 in the output entries), +0x20/+0x24/+0x28 float position x,y,z, +0x2C u8 radius, +0x2D u8 direction 0..5 [V all from 0x676a059..0x676a0e7].
Output entry `BindingEntry` (0x20): {shared_ptr ptr, ctrl; u64 key; u32 k1; u32 k2} (key triple = the 16 payload bytes) [V].
```
// 0x6769ee0(out: vector<BindingEntry>* (zeroed first), count, const FaceBinding* begin, const float view[3], float bias /*[rbp+0x70]*/)
out->reserve(count);                                  // overflow checks: count>>59 -> 0x75b60, count==0x7ffffffffffffff -> 0x75740
for (e = begin; e != begin + count; ++e) {            // stride 0x30 (lea r14*3, shl 4)
    dx = view[0]-e.x; dy = view[1]-e.y; dz = view[2]-e.z;
    r  = (float)e.radius + bias;
    if (dx*dx + dy*dy + dz*dz > r*r) continue;        // ja
    switch (e.dir) {                                  // jump table 0xf2bfe94, 6 entries [V]
      case 0: keep = dx + bias > 0; break;            // +X face
      case 1: keep = bias > dx;     break;            // -X
      case 2: keep = dy + bias > 0; break;            // +Y
      case 3: keep = bias > dy;     break;            // -Y
      case 4: keep = dz + bias > 0; break;            // +Z
      case 5: keep = bias > dz;     break;            // -Z
      default: continue;
    }
    if (!keep) continue;
    out->push_back({e.ptr, e.ctrl (lock inc ctrl+0xC), e.payload});   // grow 1.5x style via 0x1233e1a8 allocator vcall +8
}
```
Meaning [I]: distance plus facing-side cull of per-actor face/decal quads (axis-aligned plane list); the viewer must be within radius+bias and on the front side of the axis plane.
- 0x676a670(set: SmallVector<BindingEntry,1>* rcx {data +0, size u32 +8, cap u32 +0xC, inline slot +0x10}, out: {iterator, bool} rdx, entry r8): sorted-unique insert, lexicographic key (u64 at +0x10, u32 +0x18, u32 +0x1C), binary search 0x676a6e8..0x676a71f, if equal returns {it,false} and drops the shared_ptr ref; else shifts the tail up (moves, zeroing sources), writes the entry, size++; when size==cap grows by factor from float const rva 0xefd3360 with allocation through vcall +8 of 0x1233e1a8, size -1 throws (0xeec6e20/0xeec6d80) [V].
- 0x6764990(dst rcx, src rdx): SmallVector move-assignment (self check; if src is heap-allocated steals its buffer, else element-wise move with zeroing of sources and release of the old destination elements) [V skim of 0x6764990..0x6764b6x, tail not read; I for the heap-vs-inline split].
