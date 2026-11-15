# Item visitor 0x6646980 case 7 ("SkinnedMesh") - what it is on 1.26.62.01 [V disassembly]

There is NO dedicated skinned-mesh extractor function. Tag 7 is handled inline by the Item visitor 0x6646980, entry 0x6646dc2 (jump table 0xf2bf2d0). The handler is the block-entity CRACK OVERLAY draw (the "skinning" variant of the cracks overlay), not general actor skinning (players/mobs go through BatchActor 0x66d9af0 / bodyActor 0x66d0a00).

## Entry (0x6646dc2..0x6646e13) [V]
```
desc = rdi (variant payload pointer); passKeyPtr = desc[+0x140] ? &desc[+0x140]->[+0x10] : &g_defaultKey   // rax/rcx/rdx cmov
h = *passKeyPtr;                                  // 64-bit FNV-1 pass-name hash stored in the description
if (h > 0x416ae22cab22ea36) { if (h == 0x4b8edb299c93abb3 || h == 0x416ae22cab22ea37) goto 0x664746b; else goto 0x66475bb; }
else if (h == 0xd8ef928bc853553a || h == 0x2c8b246fd3eddc59) goto 0x6646e13 (the handler below);
else goto 0x66475bb;                               // 0x416ae22cab22ea36 falls here (jg not taken, then neither equality) -> generic tail
```
0x2c8b246fd3eddc59 = FNV-1 of "cracks_overlay_tile_entity.skinning" (docs/data/render_hashes.txt, rdata strings 0x5387bcc / 0x6646e00 [V]). The other constants (0xd8ef928bc853553a, 0x416ae22cab22ea36/37, 0x4b8edb299c93abb3) are pass hashes not present in render_hashes.txt [?].

## Handler (0x6646e13..) [V up to the material lookup; remainder is a scattered CFG]
- r13 = rbx; xmm6 = *(u64*)[[g_global+0x120]+0x40] (a 2-float value of a global settings object; used later) (0x6646e16..0x6646e28).
- Material lookup: name "CracksBlockEntity" (len 0x11, string at rva 0xf515e74), `0x675e440(out=rbp+0x1f0 (shared_ptr), cache=r? (r9=[[rbp+0x8a0]+0x40] , rcx=[[rbp+0x8a0]+0x68]), r8=&g_resourceKey, {name,0x11} (rbp+0x5a0), extra=&rbp+0x220 zero)` = ResourceCache::get (6gs). Result invalid (`[ptr+0x10] != 1` or null) -> 0x664cb91 (skip). Otherwise the shared_ptr is taken (strong++), `mat = *(*(ptr)+0x18)` etc.
- Then the shared tail 0x6647ff1: `rbx = [[rbp+0x8a0]]` (builder), copies the resolved shared_ptr into rbp+0x220 (0x6648017..0x6648079), `r14` material variant, `0x66a0f60(out=rbp+0x740, builder, [rbx+0x3b8], &rbp+0x130 (pair [r14+0x1b0],[r14+0x1b8]), r12d, 0, 0)` builds the mesh binding (same helper the ItemInHand extractor uses), then fills a draw-state block at rbp+0x5a4..0x6c8 (kind byte 7 at +0x5a8, 1 at +0x5ac, 0x101 at +0x5b0, 2 at +0x5b2, 8 markers at +0x5d8/+0x5e8, 0xFF at +0x5fa/+0x6c8), copies a transform packet via 0xe869ff0, and a 4-way variant (tag byte rbp+0x180: 0 -> 64 bytes (mat4) from rbp+0x140.., 2 -> 8 bytes, else error 0x6648d19) into rbp+0x688.., then continues into the shared registry emplace (0x567cf50 / 0x567d9f0 / 0x567d280 / 0x58f330 on builder-side maps) at 0x6648d.. (same tail as tags 2/3/9 per 6gh/6gi).
The CFG after this point is interleaved with cases 2, 3 and 9 (shared blocks 0x6647fe7, 0x6648d13..0x6649191), so it is not a linear function body.

## Producers / descriptions
- constructor 0x668d350 (SkinnedMesh description, fully reversed in 6gc), clones 0x4e39f20 and the inlined insert in 0x6b84e60 (6ci) - the description carries the skinning mesh + the pass-key pointer at +0x140 that this entry switches on.

## Status
Classification DONE [V]: tag 7 = cracks_overlay_tile_entity.skinning (CracksBlockEntity material) inline handler. Instruction-complete decode of the handler blocks is OPEN: the shared tail 0x6647ff1..0x6649200 interleaves several cases and needs a CFG pass (resume at 0x6648d13 for the variant copy and the registry emplace).
