# Progress: extractors-core (E2/L5e BatchActor builders, E4/L5g chunk extractor, E7/L5k, H4/L9f)

## NEXT
E2 consumer search: callers of the pool pushes 0x6760e60/0x675f3b0/0x5aba5c0 give the full WRITER set (not consumers): 0x6646980 0x66560f0 0x6664a00 0x66742f0 0x66a6830 0x66a9d50 0x666aca0 0x66ade80 0x66cba10 0x67375a0 0x673d150 0x6745440 0x675eae0 0x6761970 plus the ten builders and 0x66ea3d0/0x670b6e0/0x6722cb0 (more variants to decode). fld 0x8a8 in 0x5a..0x68 only hits a vtable slot (0x5aaef09), not the consumer. Consumer must be found via the pass object type's vtable/destructor (0x5aba5c0 return type) -> its draw/submit method.
rdis note: `fld 0x858 --r` / `fld 0x8a0 --r` are too noisy (dozens of unrelated structs); the pass-object consumer needs a base filter, e.g. start from callers of 0x5aba5c0 readers or the pass-task vcall, not field displacement alone.
Body A advanced to 0x66ed973 (summary only, mask table [~]); resume 0x66ed987; was 0x66ed500 (resume there; then 0x66ed987); was: partially advanced to 0x66ed053 (66ea3d0.md 'Body A continued'); resume at 0x66ed053 (kind 9/5 path) and 0x66ed987; then B/C/D diff, 0x67762e0/0x670b6e0/0x6722cb0, E2 consumer of 0x1C0 stride, E7 0x50-byte layout record: all not started.
Resolvers ALL decoded (geometry_resolvers.md incl. 0xC2AA290 quad index buffer, 0xC29A1D0 stream-mask binder (lookup key semantics [?]), 0x66A0F60 and 0x678C4C0 source). Next: re-evaluate E2/E7 closure (remaining E2 blockers: byte-pool tag meaning, P+0x50/0x51), then body A from 0x66eca7c and B/C/D by template diff.
E4 body A decoded through RVA 0x66eca7c (docs/functions/66ea3d0.md 'Body A'); resume at 0x66eca7c: `python tools/sigs/disrange.py 66ea3d0 66f9800 > $TEMP/ec/chunk.asm` then read from 0x66eca7c (branches 0x66ecb30 / 0x66ecc9f / 0x66ecd2d), then bodies B (0x66ef308), C (0x66f2820), D (0x66f4fcb) by diff vs A (mnemonic similarity 0.6-0.83), then 0x67762e0/0x670b6e0/0x6722cb0, E7 0x678c4c0..0x678f640, H4.
Bindings collector 0x6769ee0/0x676a670/0x6764990 DONE (dossier appended). Now E4 chunk extractor 0x66ea3d0 inline body A (0x66ebf85..) etc. E2 written (docs/functions/66d9af0_builders.md + BatchActorBuilders.h) but OPEN. Next unit: E4 chunk extractor 0x66ea3d0 inline body A (0x66ebf85..), `python tools/sigs/disrange.py 66ea3d0 66f9800`; then 0x67762e0 / 0x670b6e0 / 0x6722cb0.
Scratch (regenerable): $TEMP/ec/{a..j}.asm = builders (a=66bf290 b=66c1920 c=66c3840 d=66ce8d0 e=66c5760 f=66cc7a0 g=66c7680 h=66c98e0 i=66bb7b0 j=66bd430), diffb.py = rip-normalising diff.
Then: E4 chunk extractor (0x66ea3d0 bodies A..D), E7, H4 (all still OPEN, see entries).

---

### E2 / L5e - IN PROGRESS (pairing CONFIRMED, builder family decoded; entry below is partial until the dossier is written)
Pairing, confirmed by following the jump targets in 0x66d9af0 (disasm 0x66e0f08..0x66e2217) [V]. CONTRADICTS docs/functions/66d9af0.md phase 5 table (that table labelled the second-level branches wrongly). P = material pass record [rbp+0x718], P50 = byte P+0x50, P51 = byte P+0x51, F = byte [rbp+0x7c8], edi = (instance count != 0), C = (bl | ((r13d>>12)&1)) (bl = running AND of two earlier flags):
| builder | call site | condition [V] |
|---|---|---|
| 0x66bf290 | 0x66e1406 | P50==1, F==0, edi!=0, P51==1 |
| 0x66c1920 | 0x66e1aea | P50==1, F==0, edi!=0, P51!=1 |
| 0x66c3840 | 0x66e1a38 | P50==1, F==0, edi==0, P51==1 |
| 0x66c5760 | 0x66e1c4e | P50==1, F==0, edi==0, P51!=1 |
| 0x66bb7b0 (+0x66a65b0) | 0x66e20cf | P50==2, F==0, edi!=0 (via variant-copy table 0xf2bfb30, case target 0x66e2022) |
| 0x66bd430 | 0x66e21b3 | P50==2, F==0, edi==0 (via table 0xf2bfb20, case target 0x66e2106) |
| 0x66c7680 | 0x66e1e65 | P50 not in {1,2}, C==1, P51==1 (after 0x67743c0) |
| 0x66c98e0 | 0x66e1f42 | P50 not in {1,2}, C==1, P51!=1 (after 0x67743c0) |
| 0x66cc7a0 | 0x66e1770 | P50 not in {1,2}, C!=1, F==0, P51==1 |
| 0x66ce8d0 | 0x66e1b9c | P50 not in {1,2}, C!=1, F==0, P51!=1 |
Case P50 not in {1,2}, C!=1, F!=0 (0x66e157d) calls 0x66cc400 / 0x66cba10 / 0x66cc660 directly (no builder). F!=0 with P50 in {1,2} skips to the loop tail 0x66e1f58 (no draw).
Common call shape of every builder [V]: build(rcx = per-frame ctx [rbp+0x7b0], rdx = &{u64 count (=(end-begin)/0x30 of builder+0x480/+0x488), const T* begin}, r8 = [rbp+0x778], r9 = &vec3 copy of P+0x30..0x3B, stack5 = &DrawItem prototype (built by 0x66c11b0 at rbp+0x4a0), stack6 = float distance*scale (xmm8)). Pre-calls per site: 0x66d9710(&ctx3c8,&rec110) then 0x66c11b0(&rec4a0,&rec110); post-call 0x66c17e0(&rec4a0) (destroy).

### E2 / L5e - OPEN (blocking: bindings collector 0x6769ee0/0x676a670/0x6764990 and consumer-side identity of the byte-pool tags and P+0x50/+0x51)
Done [V]: pairing of all ten builders (table above); builder family = 4 templates differing only in byte-pool set / mask constants / copy table; helpers 0x66d9710, 0x66c11b0, 0x66c17e0 (=0x66bf150=0x66cc660=0x66a65b0) instruction-complete; 0x66a0f60 structure. Files: docs/functions/66d9af0_builders.md, src/sdk/mc/deps/minecraft_renderer/framebuilder/BatchActorBuilders.h (DrawItemProto 0x1C0, DrawItemProtoPacked 0x1B8, DrawProtoSources 0x38, mask-bit constants, static_asserts). Correction: DrawItem +0x00 is a u64 valid mask in these builders; items carry more indices at +0x12/+0x16/+0x36/+0x54/+0x74/+0x86/+0x88/+0x9e/+0x52. No layout_asserts.json entries (not Sigs-anchored; static_asserts are the guard).
### E7 / L5k - OPEN (ten builders characterised as draw-item writers; blocking: the bindings collector above and chunk draw-list builders 0x678c4c0..0x678f640)
### E4 / L5g - OPEN (unchanged: bodies A..D not decoded; not started this session)
### H4 / L9f - OPEN (not started)

### E2/E7 sub-unit: bindings collector - DONE (static, [V])
0x6769ee0 = distance + facing-side cull of 0x30-byte FaceBinding records into 0x20-byte BindingEntry (switch table 0xf2bfe94, 6 dirs +X -X +Y -Y +Z -Z); 0x676a670 = sorted-unique insert into a SmallVector<BindingEntry,1>; 0x6764990 = SmallVector move-assign. Source in docs/functions/66d9af0_builders.md (section "Bindings collector family"). E2 remaining blocker narrowed to: names/meaning of the eight 1-byte pool tags and of P+0x50/+0x51 (consumer side); 0xc2aa290/0xc2adac0/0xc2adfd0 resolvers of 0x66a0f60.

### E7 / L5k - OPEN (blocking: resolver family 0xC29A1D0 / 0xC2AA290 / 0xC2ADAC0 / 0xC2ADFD0 / 0xC2AE240 / 0x675D320 / 0x66B2730, shared with 0x66A0F60)
Done [V]: 0x678F640 instruction-complete (descriptor packer, ChunkDrawDescriptor 0x130); 0x678C4C0 structure and ChunkDrawListEntry (0x58) fields: docs/functions/678c4c0.md, header ChunkDrawList.h (static_asserts). Also found: inline body A per-entry transform = descMat(+0x78) x Translate(entry+0x3C,+0x3C+4,+0x44) x Scale(entry+0x48) and FogAlpha = entry+0x4C.
### E4 progress: body A decoded to 0x66eca7c; remaining skeleton of body A (call list with masks 0x4000000042807009 @0x66ed84f, 0x4000000042007009 @0x66ee007, 0x4000000002007009 @0x66eee63 = inline item emission as in 0xc8-item builders) not written line by line. Helpers seen in the bodies: 0x67a75d0, 0x678e1d0, 0x678e420, 0x678ef40, 0x678f260, 0x678f640, 0x678dce0, 0x67e23f0, 0x67e1660, 0x67e1840, 0x67e1990, 0x673cc80, 0x678d690, 0x1770a70.

### E7 / L5k - status update: resolvers decoded
0x678C4C0 and 0x66A0F60 now have source in docs/functions/geometry_resolvers.md (QuadIndexBuffer::ensure 0xC2AA290, addVertexStream 0xC2ADAC0, IndexRef::assign 0xC2ADFD0, tracker 0x675D320/0xC2AE240, 0x66B2730, bindVertexStreams 0xC29A1D0). Remaining for E7: 0xC29A1D0 key semantics [?] and the stream-layout record (0x50 bytes) meaning; E7 stays OPEN only on that, plus the unreached builder contents of 0x67762e0 family.
