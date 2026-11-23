## NEXT
DONE

UNIT U-EM1d — M1d: Dossiers for every FrameBuilder clone and visitor handler (L4/L5) and every extractor (chunk, batch actor, item-in-hand, skinned, nametag, particle, sky)

WHAT CHANGED (paths; read-only static on Minecraft.Windows.exe 1.26.62.01, no game launch, no build)

- docs/functions/6b84e60.md  NEW — D1 dossier: insert<RenderSkinnedMeshDescription> general skinned clone (0x6b84e60; size 0x1bf0, 1616 instructions, frame 0x3d8, 8 pushes [V dossier/xref]; callers 0x6b80870/0x6b80f00/0x6e8dff0 [V]); gate `byte [rcx+0]==1` [V]; description reads +0x108/+0x110/+0x118 [V]; Mesh::hasDrawableData 0x4def080 x4 [V]; texture resolve 0x4dfb570 x5 [V]; records 0x6b86e80/0x6b87e00/0x4e00090 [V]; mesh insert via 0x4def480 (Item tag 2) [V]; errors "Quad/Tri/Mesh material doesn't exist" [V strings]; ends via vtable slot 111 _insert(Item) [V indirect [obj+0x378] slot 111 x1; call site not decoded [?]].
- docs/functions/4e39f20.md  NEW — D1 dossier: second skinned clone (0x4e39f20; size 0x9af, 504 instructions, frame 0x508, 10 saved xmm [V dossier]; caller 0x575efc0 player renderer [V]); [r12+0xC0] 0x60-stride render-object array [V `0x4e3a0f6` + BGFX_MAP 6ec]; mat4 build per entry (movups/mulps/addps [V]); ctor 0x668d350 [V `0x4e3a43e`]; slot-111 insert [V `0x4e3a4be`/`0x4e3a4cb`]; writes desc+0x08 on every exit [V]; jt 0xf217508/0xf217518 shared-release tails [V].
Both generated with tools/sigs/dossier.py, analyst sections filled in, every claim tagged [V]/[I]/[?].

[V] PROOF TABLE (one row per distinct offset; instr lines copied verbatim from rdis dis output)

| offset | size | site address | verbatim `0xRVA  instr` | meaning | tag |
| description +0x00 | 1 | [rcx]+0x0 | `0x6b84e86  cmp byte ptr [rcx],1` | general clone gate: returns unless description byte 0 == 1 | [V] |
| description +0x108 | 8 | [rsi]+0x108 | `0x6b84ebf  mov rdx,[rsi+0x108]` | shared mesh pointer read from description | [V] |
| description +0x110 | 8 | [rdx]+0x110 | `0x6b84ea4  mov rax,[rdx+0x110]` | shared_ptr control block (refcount slot) read | [V] |
| description +0x118 | 8 | [rsi]+0x118 | `0x6b84ed4  mov rcx,[rsi+0x118]` | third shared_ptr word read | [V] |
| object array base | 8 | [r12]+0xC0 | `0x4e3a0f6  add rsi,[r12+0xC0]` | 0x60-stride render-object array base, scaled by `0x4e3a0f2  shl rsi,5` | [V] |
| builder vtable +0x378 | 8 | [rax]+0x378 | `0x4e3a4be  mov rax,[rax+0x378]` | slot 111 (_insert(Item)) entry loaded for the virtual insert call | [V] |
| description +0x08 | 1 | [rsi]+0x08 | `0x4e3a7ad  mov byte ptr [rsi+8],0` | second clone writes output slot/flag byte to desc+0x08 | [V] |

M1d DOSsiER COVERAGE NOW ON DISK
- extractors (all seven named): chunk 0x66ea3d0.md [V]; batch actor 0x66d9af0.md + 66d9af0_builders.md [V]; item-in-hand 0x6698e30.md (D1+, phases A-C decoded, tail ranges OPEN [?]); skinned = Item tag 7 inline handler item_tag7_skinned.md (entry decoded [V], shared tail OPEN [?]); nametag = Item tag 1 inline handler 6646f5b.md [V] + producer 11276b0.md [V]; particle 0x67417f0.md [V]; sky = clouds 0x67375a0.md [V] + weather 0x6745440.md [V] + sky visitor 0x66560f0.md [V].
- visitors: item visitor 0x6646980.md (11 tags [V]); all six group wrappers + 52 cases group_visitors.md [V]; case handler files 6646a10/6646a89/6646bc6/6646c8d/6646d5f/6646f5b/66471de [V] + forwarders item_forwarders_6647320.md [V].
- clones: 21 thin via insert_thin_clones.md [V]; fat nametag 1127330.md, PlayerVision 53e62b0.md, Shadow 53e6c30.md, Crack 539fff0.md, Clouds 668e940.md, MeshFallback 4def480.md, sky/stars 5369b30.md, volfog 53e3aa0.md, Flame 594c5c0.md/594fbe0.md, skinned 6b84e60.md + 4e39f20.md (this unit) [V].
- constructors: nametag 668b6e0.md, MeshFallback 668b850.md, SkinnedMesh 668d350.md, BlockSelectionOverlay 668d990.md, Sky 668c910.md [V].
- shared helpers: 0x4def080/0x4dfb570/0x5aba5c0/0x5679db0/0x675e440 dossiers [V].

STILL OPEN (this unit's single blocker)

- Item tag 7 (SkinnedMesh) shared handler tail 0x6647ff1..0x6649200 interleaves cases 2/3/9; the variant copy + registry emplace after 0x6648d13 are not instruction-complete (item_tag7_skinned.md Status). Until decoded, the skinned extractor has no [V]-proof and M1d cannot close.

CLOSES? NO — the skinned-mesh extraction path (Item group tag 7, visitor entry 0x6646dc2, docs/functions/item_tag7_skinned.md) is not instruction-complete: shared tail 0x6647ff1..0x6649200 interleaves cases 2/3/9 and its variant copy + registry emplace are undecoded, so the skinned extractor is not [V]-proven. Skinned clone dossiers 0x6b84e60 and 0x4e39f20 are now on disk (D1).

TOOL REQUESTS: none (existing tools/sigs/dossier.py, rdis dis, xref only; all read-only static).
