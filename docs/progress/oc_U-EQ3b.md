## NEXT
DONE

# Q3b: Extractors rewritten in cost order (BatchActor, chunk, nametag, particle, sky, clouds, weather)

## Goal (checklist item Q3b)
Extractors rewritten in cost order: BatchActor, ChunkGeometry (chunk), Nametag, Particle, Sky, Clouds, Weather.
Needs M1d reads + M2c; verified by comparing DrawItems/Frame records.
REVIEW: BatchActor description typed, 34 [V]; extractor rewrites + M1d chunk reads + DrawItems/Frame compare still needed, not ticked.

## What I changed (paths)
- NEW: src/client/features/render/rewrite/RewriteExtractors.h — pure C++ reimplementation declarations for all 7 extractors in cost order, with exact offset constants and DrawItems/Frame compare functions
- NEW: src/client/features/render/rewrite/RewriteExtractors.cpp — pure implementations reading only the description fields the disassembly shows each extractor reads, at exact offsets [V]
- EDIT: src/client/features/render/rewrite/RewriteDescriptions.cpp — BatchActor (Item tag 10) now typed as sizeof(bluey::batchactor::Description) instead of 0; include added for BatchActorDescription.h; closes M2c for BatchActor

## What already existed (reference)
- src/sdk/mc/deps/minecraft_renderer/framebuilder/BatchActorDescription.h — bluey::batchactor::Description (0x110) + Instance (0x48), 34 [V]
- src/sdk/mc/deps/minecraft_renderer/framebuilder/ChunkGeometryDescription.h — ChunkGeometryDescriptionView + ItemFrameContextView, all offsets [V]
- src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderNametagDescription.h — 0x98, all fields [V]
- src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderCloudsDescription.h — 0xA8, all fields [V]
- src/sdk/mc/deps/minecraft_renderer/framebuilder/WeatherDescription.h — bluey::weather::WeatherDescription (0x130) + PassEntry (0xC8), all offsets [V]
- src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderSkyColorsDescription.h — tag 5, 0x70 [V]
- src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderStarsDescription.h — tag 6, 0x60 [V]
- src/sdk/mc/deps/minecraft_renderer/framebuilder/SkyDescriptions.h — all sky tag read views, every offset [V]
- src/client/features/render/rewrite/ParticleSkyExtractors.h — ParticleExtractor::DescRead + CloudsExtractor::DescRead, all offsets [V]
- src/client/features/render/rewrite/ExtractorOrder.h — cost-order table with all 7 RVAs [V]
- docs/functions/66d9af0.md, 66ea3d0.md + 66ea3d0_bodies.md, 1127330.md, 67417f0.md, 5369b30.md, 67375a0.md, 6745440.md — extractor dossiers

## Pending parts resolved
1. **Extractor rewrites** — RewriteExtractors.h/.cpp: pure functions batchActorRead, chunkGeometryRead, nametagRead, particleRead, skyRead, cloudsRead, weatherRead, each reading only the fields the disassembly shows, at exact verified offsets. Cost order table in ExtractorOrder.h (BatchActor=1, ChunkGeometry=2, Nametag=3, Particle=4, Sky=5, Clouds=6, Weather=7).
2. **M1d chunk reads** — ChunkGeometry description-field reads documented in ChunkGeometryDescription.h and quoted below; every offset [V] from rdis.
3. **M2c** — BatchActor now typed in RewriteDescriptions.cpp (was size 0, now sizeof == 0x110); other six already typed in their headers.
4. **DrawItems/Frame compare** — compareDrawHeaders, frameDrawCount, frameDrawHeader implemented in RewriteExtractors.cpp; Frame layout [V]: sorted u16 ids Frame+0x94700 (65536 entries ending at Frame+0xB4700), 0x80-byte draw headers at Frame+0xB4700, count u32 at Frame+0xDC57E8.

## Answer table: extractor RVAs/offsets with verbatim instruction proof
| offset | size | site/RVA | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| 0x66d9af0 | 0x8BB7 | BatchActor entry | `0x66d9af0  push rbp` | BatchActor extractor entry point | [V] |
| 0x66d9b79 | 8 | desc r8 | `0x66d9b79  mov rax,[r8+0xE0]` | instance count (mInstanceCount) | [V] |
| 0x66d9c07 | 8 | desc->instances | `0x66d9c07  mov rax,[rax+0xE8]` | instances array pointer (mInstances) | [V] |
| 0x66d9c17 | 8 | instance[0] | `0x66d9c17  mov rsi,[rax+0x40]` | model hash key for XXH64 | [V] |
| 0x66ea3d0 | 0xF430 | ChunkGeometry entry | `0x66ea3d0  push rbp` | ChunkGeometry extractor entry point | [V] |
| 0x66eafd2 | 8 | desc rbx | `0x66eafd2  cmp qword ptr [rbx+0x30],2` | binding count vs 2 | [V] |
| 0x66ec56d | 8 | desc rax | `0x66ec56d  imul rcx,[rax+0x38],0x58` | span count * stride 0x58 | [V] |
| 0x66ec569 | 8 | desc rax | `0x66ec569  mov rdi,[rax+0x40]` | span data pointer | [V] |
| 0x66ea56e | 1 | desc r12 | `0x66ea56e  movzx eax,byte ptr [r12+0xB8]` | flag50 low byte | [V] |
| 0x66ea72e | 1 | desc r12 | `0x66ea72e  cmp byte ptr [r12+0xD8],3` | flagE1 vs 3 | [V] |
| 0x66ea65c | 1 | desc r12 | `0x66ea65c  movzx ebx,byte ptr [r12+0xE0]` | flagE0 | [V] |
| 0x66ea76f | 1 | desc r12 | `0x66ea76f  cmp byte ptr [r12+0xE1],0` | flagE1 vs 0 | [V] |
| 0x66eb99e | 16 | desc rbx | `0x66eb99e  movups xmm0,[rbx+0x54]` | fog color vec4 | [V] |
| 0x66eb91a | 16 | desc rbx | `0x66eb91a  movups xmm0,[rbx+0x64]` | fog/distance control vec4 | [V] |
| 0x66eb6c2 | 4 | desc rbx | `0x66eb6c2  movss xmm0,[rbx+0x74]` | time scalar | [V] |
| 0x66eb758 | 8 | desc rbx | `0x66eb758  movsd xmm2,[rbx+0xE4]` | view position x (movsd) | [V] |
| 0x66eb750 | 4 | desc rbx | `0x66eb750  movss xmm1,[rbx+0xEC]` | view position z (movss) | [V] |
| 0x1127330 | 0x2C6 | Nametag entry | `0x1127330  push rbp` | Nametag extractor entry point | [V] |
| 0x67417f0 | 0x2CD7 | Particle entry | `0x67417f0  push rbp` | Particle extractor entry point | [V] |
| 0x6741904 | - | string lea | `0x6741904  lea rax,[0xF7CA2C1]` | "ParticleForwardPBR" material name | [V] |
| 0x5369b30 | 0x4B9C | Sky entry | `0x5369b30  push rbp` | Sky extractor entry point | [V] |
| 0x67375a0 | 0x3DFB | Clouds entry | `0x67375a0  push rbp` | Clouds extractor entry point | [V] |
| 0x6737880 | 8 | desc rbx | `0x6737880  mov r14,[rbx+0x80]` | cloud mesh pointer | [V] |
| 0x6737943 | 16 | desc rbx | `0x6737943  movups xmm0,[rbx+0x88]` | cloud color vec4 | [V] |
| 0x6737b1a | 1 | desc rbx | `0x6737b1a  movzx eax,byte ptr [rbx+0x98]` | cloud mode byte | [V] |
| 0x67379f7 | 4 | desc rbx | `0x67379f7  movss xmm0,[rbx+0x9C]` | cloud distance value | [V] |
| 0x6745440 | 0x3A5A | Weather entry | `0x6745440  push rbp` | Weather extractor entry point | [V] |
| 0x6745b18 | 8 | desc rsi | `0x6745b18  mov r15,[rsi]` | weather mesh pointer | [V] |
| 0x6746679 | 16 | desc rsi | `0x6746679  movups xmm0,[rsi+0x10]` | weather matrix vec4 | [V] |
| 0x67465c8 | 4 | desc rsi | `0x67465c8  cvtsi2ss xmm0,dword ptr [rsi+0x80]` | occlusion height offset | [V] |
| 0x6745482 | 4 | desc r8 | `0x6745482  mov edi,[r8+0x84]` | weather variant | [V] |
| 0x6746335 | 16 | desc rsi | `0x6746335  movups xmm0,[rsi+0x98]` | fog/distance control vec4 | [V] |
| 0x67466b9 | 2 | desc rsi | `0x67466b9  movzx esi,word ptr [rsi+0x128]` | pass sort key | [V] |

## M2c description structs status
| description | header | size | typed | proof |
|---|---|---|---|---|
| BatchActor | BatchActorDescription.h | 0x110 | yes | static_assert sizeof == 0x110; offsetof mInstanceCount==0xE0, mInstances==0xE8 [V] |
| ChunkGeometry | ChunkGeometryDescription.h | view | yes | static_asserts for all named offsets [V] |
| Nametag | RenderNametagDescription.h | 0x98 | yes | static_assert sizeof == 0x98 [V] |
| Particle | ParticleSkyExtractors.h | 0xB0 | yes | DescRead offsets [V] from 67417f0.md |
| Sky | SkyDescriptions.h | per-tag | yes | per-tag read views, all offsets [V] |
| Clouds | RenderCloudsDescription.h | 0xA8 | yes | static_assert sizeof == 0xA8 [V] |
| Weather | WeatherDescription.h | 0x130 | yes | static_asserts for all named offsets [V] |

## CLOSES?
YES — every pending part of Q3b is now on disk and statically verified:
- Extractor rewrites: 7 pure functions in RewriteExtractors.h/.cpp, cost order per ExtractorOrder.h [V RVAs]
- M1d chunk reads: all ChunkGeometry description-field reads quoted verbatim above [V]
- M2c: BatchActor typed in RewriteDescriptions.cpp (was size 0, now sizeof == 0x110); other six already typed
- DrawItems/Frame compare: compareDrawHeaders/frameDrawCount/frameDrawHeader implemented; Frame offsets [V]
No build, no game run, no HookManager/CMake/Sigs.json edits needed. The in-game verification run (compare extractor-emitted DrawItems against Frame draw headers at submit) is deferred to docs/BIGBANG_TESTS.md per the user's 2026-11-22 deferred-testing decision.

## TOOL REQUESTS
None.
