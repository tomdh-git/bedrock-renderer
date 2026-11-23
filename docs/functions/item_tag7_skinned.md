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
Classification DONE [V]: tag 7 = cracks_overlay_tile_entity.skinning (CracksBlockEntity material) inline handler. The shared tail sub_6648d13 [0x6648d13..0x664ad13) (variant copy + registry emplace) is now instruction-completely decoded block by block with [V] proof rows in docs/progress/oc_U-EM1d.md (delegate check OK; verify_oc mismatch=0), summarized below.

## sub_6648d13 shared variant-copy / registry-emplace (M1d) [V]

### Bounds [V]
`rdis fn 0x6648d13` -> `sub_6648d13  [0x6648d13..0x664ad13)  size 0x2000  2 xrefs in` — a region inside Item visitor `sub_6646980` ([0x6646980..0x664fda5)), reached from tag-7 entry 0x6646dc2 (jump table 0xF2BF2D0) and from alternate entry 0x6649dc9. One `rdis dis 0x6648d13 3000` window covers it entirely; last decoded instruction at 0x664ad09, 4 bytes 0x664ad0f..0x664ad12 undecoded, region end 0x664ad13 per rdis. Full 1587-row [V] table: docs/progress/oc_U-EM1d.md section "Full instruction table".

### Role
Shared variant-copy + registry-emplace tail for the skinned path (interleaved with cases 2/3/9 tails): copies the description variant payload into a registry component block (header [rbp+0x5A0] = {u16 count/size, u16 flag=1, data ptr [rbp+0x5A8]}, data from [rbp+0x5A0+0x10}), emplaces it into the entt registry, builds the draw-state block ([rbp+0x224..0x398]), resolves materials/pass-name FNV hashes, handles shared_ptr acquire/release, and copies the transform packet.

### Entry state [I from disassembly]
rdi = description pointer; rbp = frame base (locals rbp+0x10..0x900); rbp+0x778 = variant index byte (0..3; >3 exits to 0x664b8c3); rbp+0x740/0x750/0x760 = saved 16-byte vector state; r14 = destination pointer; rbx/rsi = description-related pointers per block.

### Jump tables [V] (int32-relative, target = table + disp, read from .rdata)
- 0xF2BF34C at 0x6648d7e on byte [rbp+0x778]: idx0->0x664b8bd, idx1->0x6648d8e, idx2->0x66495c4, idx3->0x66495d7
- 0xF2BF37C at 0x6649593: idx0->0x664cdeb, idx1->0x66495b1, idx2->0x664c2f5, idx3->0x664c307
- 0xF2BF38C at 0x6649d8d: idx0->0x664bf56, idx1->0x6649daf, idx2->0x664bf49, idx3->0x664bf7d
- 0xF2BF32C at 0x664a8bc: idx0->0x664e33e, idx1->0x664a8dd, idx2->0x664c91e, idx3->0x664c93d
- 0xF2BF31C at 0x664ab35: idx0->0x664e39e, idx1->0x664ab5a, idx2->0x664c92e, idx3->0x664c95f
- 0xF2BF36C at 0x664a5e7: idx0->0x664c36d, idx1->0x664a606, idx2->0x664a616, idx3->0x664a628

### Block map (reads / writes / calls / field offsets) [V per instruction]
| block | range | exits | reads / writes / calls / field offsets |
|---|---|---|---|
| G1 | 0x6648d13..0x6648d8c | table 0xF2BF34C | write [rbp+0x6c8]=al (variant tag), [rbp+0x6d0]=si; read [rbp+0x740/0x750/0x760]; write [rbp+0x748]=0, [rbp+0x6d8], [rbp+0x750]=0, [rbp+0x6e8], [rbp+0x6f8]=[rbp+0x760]; r14=&rbp+0x700; [rbp+0x710]=0xFF |
| G2 | 0x6648d8e..0x6648d9c | 0x664b8bd | read [rbp+0x768] -> write [rbp+0x700] |
| G3 | 0x6648da1..0x6648ddc | 0x664ebd7 | write [r14+8]=0; read [rdi+0x10]->[r14+0x10]; call 0x66e75f0; call 0x539dd40 -> rax |
| G4 | 0x6648de1..0x6648e5f | loc_6648e5f | shared_ptr chain [rbp+0x220]->[rax+0x18]->[rax]->[rbp+0x10]; call 0xe86b370 emplace; release [rbp+0x228] via [0xF99FFA0]=sub_eea6040 |
| G5 | 0x6648e5f..0x6648eaf | loc_6648eaf | count=(([r15+0x60]-[r15+0x58])>>2)*0xAAAAAAAB; call 0xbbd7c70 (0x250-byte copy); call 0x4dedd00 (rcx=[rdi+0xB0]) |
| G6-G7 | 0x6648eaf..0x6648ee1 | loc_6648ee1/0x664cb91 | eax=[rdi+0xb8]; r12d=[r15+0x1d0] if [r15+0x1d4]; eax/3 rounded to even -> r12d |
| G8 | 0x6648ee1..0x66490ec | 0x664cb91/fallthrough | telemetry [0x129F9CD8/0x129F9CE8]; default block init: 0x3F800000 (1.0f) to [rbp+0x220..0x40C] stride 0x14; movsd 1.0 ([0xEFD3400]) to [rbp+0x25c/0x29c/0x2dc/0x31c/0x35c/0x39c] |
| G9 | 0x66490ec..0x664914f | 0x664ed47/fallthrough | shared_ptr [rdi+0xc0]/[0xc8] empty test; call 0x6698060 copy; [rbp+0x5a0]=8, [rbp+0x5a8]=&rbp+0x220 |
| G10 | 0x664914f..0x6649191 | 0x664ae22/0x664ae25/0x664ae68 | table scan #1: stride 0x10, entry+0x28 vs [0x129F8310] |
| G11 | 0x6649191..0x664921d | loc_664921d | shared_ptr reload; call 0xe86b370 emplace #2; release [rbp+0x228] |
| G12-G14 | 0x664921d..0x6649321 | 0x6649641/loc_6649321 | telemetry [0x129F9340]; read [rdi+0x64]->[rbp+0x220]; table scan #2 vs [0x129F9338]; index->[rbp+0x7c0]; call 0x5679db0; shared_ptr reload+emplace; release |
| G15 | 0x6649321..0x66493db | loc_66493db | telemetry [0x129F9220]; read [rdi+0x68]->[rbp+0x220]; table scan #3 vs [0x129F9218]; [rbp+0x740]=cx,[rbp+0x742]=1; call 0x5679db0 |
| G16-G17 | 0x66493db..0x66495fe | 0x664d484/table 0xF2BF37C | call 0xbbd7f70 emplace; byte [rbp+0x144]&=0xF7; draw-state block: [rdi+0x50/0x8/0x18/0x28/0x38/0x48/0x80/0x84] -> [rbp+0x1a0..0x228]; call 0xe869ff0 transform copy; [rbp+0x358..0x388] stores; byte [rbp+0x3a0]=0xFF |
| G18-G21 | 0x66495b1..0x6649641 | table exits/loc_6649641 | table idx1: [rbp+0x390]=[rbp+0x768]; idx2: movups [rbp+0x768]->[r14]; idx3: shared_ptr acquire [rbp+0x770]; scan #2 index -> call 0x5679db0 |
| G22-G24 | 0x6649641..0x6649915 | loc_6649915 | scans #3..#7 vs [0x129F8320/0x129F8328/0x129F8330/0x129F8348/0x129F8350] on [rdi+0x8c/0x9c/0xa4/0xb4], ss [rdi+0xcc]+sd [rdi+0xc4]; each index->[rbp+0x7c0],[rbp+0x7c2]=1; call 0x5679db0 |
| G25 | 0x6649915..0x6649963 | loc_6649963 | [rdi+0x78]->rax, [rax+0x40]->rcx; flags from bytes [rcx+0x1ac/0x1ad/0x1ae/0x1af] -> al (1|4|16|0x40), cx=0x500 |
| G26 | 0x6649963..0x6649a10 | loc_6649a10 | rdx=[rbp+0x58]; stride-0x30 scan vs [0x129F8318] (entry+0x28); index*0xFFFFAAAB -> [rbp+0x5a0]; component header [rbp+0x220..0x22c]; call 0xbcaba00 component emplace |
| G27-G28 | 0x6649a10..0x6649b83 | 0x664c2a1/fallthrough | telemetry [0x129F9350]; read [rbx+0x3e0]->[rbp+0x220]; scan #8 vs [0x129F9348]; call 0x5679db0; [rdi+0x88]?1.0f([0xEEC8060]):0 broadcast; scan #9 vs [0x129F9358]; call 0x5679db0; call 0xbbd7f70 emplace |
| G29-G30 | 0x6649b83..0x6649d20 | 0x664c2a1/0x664f714/fallthrough | byte [rdi+0x39]->r8d; call 0x66b2b30 emplace; [rbp+0x744]=0xF; [rdi+0xe0]?[rbp+0x754]=1,movups [rdi+0xd0]->[rbp+0x758]; [rbp+0x768]=0xFFFFFFE0; ss/sd [rdi+0x58/0x5c/0x18/0x1c/0x20/0x30/0x40/0x50]->[rbp+0x5a0..0x5d8]; call 0xe869ff0 |
| G31-G32 | 0x6649d20..0x6649dbd | 0x664bf56/table 0xF2BF38C | [rbp+0x350..0x398] draw-state tail; byte [rbp+0x398]=0xFF; word [rdi+0xe4]->[rbp+0x238]; movups block [rbp+0x740..]->[rbp+0x224..0x2c8]; table idx1: [rbp+0x388]=[rbp+0x7e8] |
| G33-G35 | 0x6649dc2..0x6649f65 | 0x664abf5/0x664f047/fallthrough | alternate entry: r15+=8,r12+=r15; call 0xe93bf00 ends-with "fullscreen_cube_overlay" (0xF51E3D7, 0x17); size checks [rbp+0x238]; call 0x66b2b30 emplace; FNV hash compare rsi vs 3 constants; allocator [0x1233E1A8]=0x15233de18 via [0xF99FFA0] (align-32 alloc, back-ptr at [r12-8]) |
| G36-G37 | 0x6649f65..0x664a0e4 | loc_664a086/0x664a09f | [rbp+0x140]=buffer; call 0xeec6ec0 memcpy; null-terminate; rsi vs 9 FNV constants -> [rbp+0x598]; shader "shaders/uv_selection_overlay.vertex" (0xF51FE2B) via 0xeec6eb0; FNV 0x8E31F9DB7CE887B7/0x72BE7BFDEE2D2411 compare; draw flags r9d from [rbp+0x8a0]+0x70 |
| G38 | 0x664a0e4..0x664a27c | 0x664eb99/loc_664a268/loc_664a27c | call 0xbbd46c0 emplace; if [rbp+0x628]==1 -> 0x664eb99; [rdi+0xdc]==1: [rbp+0x7bc]=[rdi+0x188],[rbp+0x7b8]=[rdi+0x18c]; r14=[rbp+0x8a0]+0x48; alloc 0x30; write "eCapture"/"UIStruct"; [rbp+0x220..0x250]={7bc,7b8,0x1C,r15,0,0x20,0x2f}; call 0x5ab9970 texture create; free path 0xe935700; [rbp+0x87f]=r15b |
| G39-G41 | 0x664a27c..0x664a69b | loc_664a31b/0x664a375/0x664a381/0x664a549/0x664eb5b/loc_664a69b | ss [rdi+0x134] broadcast; table scan vs [0x129F8388]; call 0x5679db0; bl|=r13b; [rbp-0x1c]=ebx; if bl==1: telemetry [0x129F9370], [rbp+0x898] chain [0x430]/[0x440] -> rbx=0xC0+[rax+0x18], shared_ptr acquire, call 0xbcac390 (name [0x129F9368]), release, telemetry [0x129F9380], scan vs [0x129F9378], call 0x5679db0; call 0xbbd7f70 emplace; [rbp+0x818]!=1 -> 0x664eb5b; [rdi+0x164]==1? [rbp+0x754]=1, [rdi+0x154]->[rbp+0x758]; memset 0x358 via 0xeec6ed0; table 0xF2BF36C on [rbp+0x7f8] |
| G42-G43 | 0x664a69b..0x664a8ea | table 0xF2BF32C exits | call 0x66a0f60 mesh binding; if byte [rdi+0x20]==1 (skinned): sd [r12]->[rbp+0x7c0], ss [r12+8]->[rbp+0x7c8], xmm [r12+0xc/0x1c/0x2c], ss [r12+0x3c]->[rbp+0x7fc]; draw-state [rbp+0x224..0x27a] incl. 0x101 kind, 0xFFFFFFE0, (-5.0f,-5.0f) [0xF07C974] at [rbp+0x250]; call 0xe869ff0; [rbp+0x308..0x390] fill |
| G44 | 0x664a8ed..0x664ab6a | table 0xF2BF31C exits | non-skinned draw block: ss [r12+0x30/0x34/0x38], sd [r12]->[rbp+0x7c0]; [rbp+0x7f0/0x7f4/0x7f8] from [r12+0x30/0x34/0x38]; same draw-state writes; call 0xe869ff0; [rbp+0x310..0x398] fill |
| G45-G47 | 0x664ab6a..0x664ad0f | 0x664ad64/0x664ad4f/end | copy loops stride 0x20 into [rbp+rcx+0x5a0] (count [rbp+0x620]) and [rax+r8] (count [rbp+0x6a8]); ss [rdx]->[rbp+0x6b0]; rcx mask loop with 0xFFFFFFFFFFFFFFF; tail copy: `movups xmm1,[rbp+0x5a0]`, `movups [rbp+r8+0x10],xmm1` at 0x664ad05/0x664ad09; 4 undecoded bytes 0x664ad0f..0x664ad12 |

### Key proof rows [V] (verbatim from rdis dis; full table in oc_U-EM1d.md)
```
0x6648d13  mov [rbp+0x6C8],al
0x6648d7e  lea rcx,[0xF2BF34C]
0x6648d8c  jmp rdx
0x6648da9  movups xmm0,[rdi+0x10]
0x6648dca  call 0x66E75F0
0x6648dd0  lea rcx,[rbp+0x220]
0x6648dd7  call 0x539DD40
0x6648e0c  mov r8,[rbx]
0x6648e0f  mov rdx,[rax+0x170]
0x6648e19  call 0xE86B370
0x6648e72  imul eax,0xAAAAAAAB
0x6648f34  mov dword ptr [rbp+0x220],0x3F800000
0x66490ec  mov rax,[rdi+0xC0]
0x6649137  call 0x6698060
0x6649a0a  call 0xBCABA00
0x6649bbd  call 0x66B2B30
0x6649d1a  call 0xE869FF0
0x664a200  call 0x5AB9970
0x664a6cb  call 0x66A0F60
0x664ad05  movups xmm1,[r14]
0x664ad09  movups [rbp+r8+0x10],xmm1
```

### Callees / fields touched [V]
Callees: 0x66e75f0, 0x539dd40, 0xe86b370, 0xbbd7c70, 0x4dedd00, 0xe869ff0, 0x5679db0, 0xbbd7f70, 0x66b2b30, 0xbcac390, 0xeec6ec0/eb0/ed0, 0x5ab9970, 0xbbd46c0, 0x66a0f60, 0xe93bf00, 0xe935700, shared_ptr dtor/alloc via [0xF99FFA0]=sub_eea6040.
Stack fields: [rbp+0x10] result ptr, [rbp+0x5a0/0x5a8] component header, [rbp+0x740..0x900] variant state, [rbp+0x220..0x40c] default block, [rbp+0x224..0x398] draw-state block.
Description fields (rdi): +0x10, +0x38, +0x48, +0x50, +0x58, +0x5c, +0x64, +0x68, +0x78, +0x80, +0x84, +0x88, +0x94, +0xa0, +0xb0, +0xb8, +0xc0, +0xc8, +0xcc, +0xd0, +0xe0, +0xe4, +0x108, +0x134, +0x164, +0x188, +0x18c, +0x1a0, +0x1d0, +0x1d4, +0x1ad..0x1af, +0x3b8.

