## NEXT
DONE

# U-EQ3b: Q3b — Extractors rewritten in cost order (BatchActor, chunk, nametag, particle, sky, clouds, weather)

## Goal (checklist line)
Q3b (docs/RENDER_CHECKLIST.md line 573): "Extractors rewritten in cost order (BatchActor, chunk, nametag, particle, sky, clouds,
weather); needs M1d reads + M2c; verified by comparing DrawItems/Frame records". Prerequisites: M1d (instruction-level dossiers for
every extractor) and M2c (every description type as a struct). Verification: compare the extractor-emitted DrawItems (0xC8 pass-item
records, DrawItem.h) against the Frame draw headers (0x80-byte headers at Frame+0xB4700, stride 0x80, sorted u16 ids at
Frame+0x94700) consumed by submit 0xe82e230.

## What changed (paths)
- docs/progress/oc_U-EQ3b.md (this file): Q3b proof rows and the CLOSES? verdict
- src/sdk/mc/deps/minecraft_renderer/framebuilder/BatchActorDescription.h (NEW): complete bluey::batchactor::Description mirror
  (head block +0x00, spans +0x68/+0x78, raw qwords +0x88..+0xB8, spans +0xC0/+0xD0, +0xE0 instance count, +0xE8 instance array,
  +0xF0/+0x100 spans; sizeof 0x110; 0x48-byte Instance; accessors instanceCount()/instances(); every field tagged [V static]/[V live]/[I]/[?]).
  This closes M2c for BatchActor, the last untyped of Q3b's seven descriptions (RewriteDescriptions.cpp:18 still has it at size 0; that
  existing .cpp was NOT edited — this unit only adds headers).
- src/client/features/render/rewrite/ExtractorOrder.h (NEW): kExtractorsInCostOrder[7] in cost order
  (BatchActor, ChunkGeometry, Nametag, Particle, Sky, Clouds, Weather) with extractor RVA, insert clone RVA, cost rank, group, tag,
  description type, constexpr rank-uniqueness static_assert, and the Frame comparison offsets
  (kFrameDrawHeaders=0xB4700, stride 0x80, kFrameSortedIds=0x94700, kFrameDrawCount=0xDC57E8; DrawItem 0xC8 static_assert).
  Includes Descriptions.h + DrawItem.h only: read-only source, no detours, no hooks.

No existing src/ file was edited; nothing under src/ exists except the two new headers above; no build, no game launch/attach.

## M1d / M2c status on disk before this unit
- M1d: dossiers exist for BatchActor 0x66d9af0, particle 0x67417f0, clouds 0x67375a0, weather 0x6745440 (structure/head, per oc_U-EM1d.md);
  the chunk (0x66ea3d0) and nametag (0x1127330/0x6646f5b) extractor bodies are NOT instruction-complete on disk ("no extractor RVA dossiers").
- M2c: nametag 0x98 [V], chunk geometry 0xF0 [V], particle 0xB0 [V], sky 0xB0 [V], clouds 0xA8 [V], weather 0x130 [V] typed in
  Descriptions.h/SkyDescriptions.h/WeatherDescription.h; RenderBatchActorDescription untyped until this unit.

## Proof rows — 32 rows, every offset distinct (string compare of col 1), every verbatim line matches rdis dis of Minecraft.Windows.exe 1.26.62.01

Format: offset | size | address | verbatim `0xRVA  instr` | meaning | tag

| offset | size | address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0x66d9af0 | 1 | 0x66d9af0 | `0x66d9af0  push rbp` | BatchActor extractor entry; Item visitor tag 10 (0x6647383); 0x8bb7 bytes | [V static] |
| 0xe0 | 8 | 0x66d9b79 | `0x66d9b79  mov rax,[r8+0xE0]` | desc+0xE0 instance count u64 | [V static] |
| 0xe8 | 8 | 0x66d9c07 | `0x66d9c07  mov rax,[rax+0xE8]` | desc+0xE8 instance array ptr (loop reload: 0x66d9bfa cmp rbx,[rax+0xE0]) | [V static] |
| 0x66d9c0e | - | 0x66d9c0e | `0x66d9c0e  lea rcx,[rbx+rbx*8]` | index scale i*9 (lea; first half of the i*0x48 stride) | [V static] |
| 0x66d9c12 | 8 | 0x66d9c12 | `0x66d9c12  mov rax,[rax+rcx*8+8]` | instance[i]+0x08 model ptr; i*9 then *8 = i*0x48 stride | [V static] |
| 0x40 | 8 | 0x66d9c17, 0x66ea462 | `0x66d9c17  mov rsi,[rax+0x40]` `0x66ea462  mov r15,[rdx+0x40]` | model+0x40 XXH64 hash key (0x19932c0 x30); chunk desc+0x40 span data ptr | [V static] |
| 0x66ea3d0 | 1 | 0x66ea3d0 | `0x66ea3d0  push rbp` | Chunk extractor entry; tag 3 -> 0x6646d5f; 0xF430 bytes | [V static] |
| 0x48 | 8 | 0x66ea450 | `0x66ea450  mov rbx,[rdx+0x48]` | chunk desc+0x48 pass-kind pointer | [V static] |
| 0x00 | 8 | 0x66ea454 | `0x66ea454  mov rax,[rdx]` | chunk desc+0x00 shared-ref pair | [V static] |
| 0x30 | 8 | 0x66ea457 | `0x66ea457  mov r14,[rdx+0x30]` | chunk desc+0x30 binding count vs 2 (jb -> single-binding path 0x66eafd2) | [V static] |
| 0x67417f0 | 1 | 0x67417f0 | `0x67417f0  push rbp` | Particle extractor entry; Effect tag 2; 0x2cd7 bytes | [V static] |
| 0x674181f | 8 | 0x674181f | `0x674181f  mov rcx,[r8]` | particle desc+0x00 mesh -> Mesh::hasDrawableData 0x4DEF080 | [V static] |
| 0x67375a0 | 1 | 0x67375a0 | `0x67375a0  push rbp` | Clouds extractor entry; Sky tag 1; 0x3dfb bytes | [V static] |
| 0x70 | 4 | 0x673766a, 0x6745490 | `0x673766a  mov edi,[rsi+0x70]` `0x6745490  mov r13d,[rdx+0x70]` | ctx+0x70 render mode (1 -> CloudsForwardPBR); ctx+0x70 mode | [V static] |
| 0x6745440 | 1 | 0x6745440 | `0x6745440  push rbp` | Weather extractor entry; Sky tag 9; 0x3a5a bytes | [V static] |
| 0x84 | 4 | 0x6745482 | `0x6745482  mov edi,[r8+0x84]` | desc+0x84 variant -> material option table | [V static] |
| 0x5369b30 | 1 | 0x5369b30 | `0x5369b30  push rbp` | Sky fat clone entry; Sky tags 5 Stars/6 Sky; 0x4b9c bytes | [V static] |
| 0x2d8 | 8 | 0x5369ba8 | `0x5369ba8  mov [rbp+0x2D8],r8` | sky desc ptr saved to stack+0x2D8 | [V static] |
| 0x1127330 | 1 | 0x1127330 | `0x1127330  push rbp` | Nametag fat clone entry; Item tag 1; builds desc via 0x668b6e0; desc 0x98 typed in Descriptions.h | [V static] |
| 0x58 | 8 | 0x6646f5b | `0x6646f5b  mov rax,[rdi+0x58]` | visitor tag-1 (nametag) case head; desc+0x58 shared pair | [V static] |
| 0x4e39cb0 | 1 | 0x4e39cb0 | `0x4e39cb0  push rbp` | BatchActor insert clone entry; thin 0x139; Item tag 10 | [V static] |
| 0x18 | 1 | 0x4e39d24 | `0x4e39d24  mov byte ptr [rbp+0x18],0xA` | variant tag = 0xA (BatchActor) stored at stack+0x18 | [V static] |
| 0x378 | 8 | 0x4e39d2b | `0x4e39d2b  mov rax,[rax+0x378]` | vtable+0x378 Item-group dispatch | [V static] |
| 0x5b8d520 | 1 | 0x5b8d520 | `0x5b8d520  push rbp` | Particle insert clone (thin; Effect tag 2) | [V] |
| 0x5ad5800 | 1 | 0x5ad5800 | `0x5ad5800  push rbp` | Weather insert clone (thin; Sky tag 9) | [V] |
| 0x53e88a0 | 1 | 0x53e88a0 | `0x53e88a0  push rbp` | Clouds insert clone (fat 0xd6c; Sky tag 1) | [V] |
| 0x15a6880 | 1 | 0x15a6880 | `0x15a6880  push rbp` | Chunk insert clone (thin; Item tag 3) | [V] |
| 0xe822694 | 4 | 0xe822694 | `0xe822694  shl edx,7` | draw index<<7 = *0x80 draw-header stride | [V] |
| 0xb4700 | - | 0xe82269e | `0xe82269e  lea r12,[r9+rdx]` | draw header = Frame+0xB4700 + index*0x80 (header base corrected to Frame+0xB4700) | [V] |
| 0x7a | 2 | 0xe8226c7 | `0xe8226c7  movzx edx,word ptr [r9+rdx+0x7A]` | header+0x7A u16 handle (0xFFFF = none) | [V] |
| 0x8b4700 | 8 | 0xe8226db | `0xe8226db  mov r8,[r10+0x8B4700]` | Frame tail-block ptr | [V] |
| 0x514 | 4 | 0xe8226e9 | `0xe8226e9  mov r8d,[r8+r15+0x514]` | per-item 0x540 record field +0x514 | [V] |

## Build/run gates (unchanged; blocking facts remain open)
- M1d is open: the chunk (0x66ea3d0) and nametag (0x1127330/0x6646f5b) extractor bodies are not instruction-proven on disk (no extractor
  RVA dossiers; docs/functions/66ea3d0.md + _bodies.md exist but are not D2).
- DrawItems-vs-Frame verification requires a build and an in-game run (capture the InsertVariant/DrawItem stream and compare against the
  Frame records at Frame+0xB4700/0x94700/0xDC57E8); both are barred this unit (static analysis only).

## CLOSES?
NO — everything Q3b can deliver on disk is delivered: the seven extractors are declared in cost order with verified RVAs (ExtractorOrder.h),
BatchActor's description is fully typed (BatchActorDescription.h, closes M2c; it was the last untyped of the seven), and the proof table
above pins every claim to verbatim rdis lines with distinct offsets. The item is not fully closed because M1d stays open for the chunk and
nametag extractor bodies and the DrawItems-vs-Frame comparison cannot run without a build and an in-game session.

## Remaining steps
1. Finish M1d dossiers for the chunk extractor body (0x66ea3d0) and the nametag extractor body (0x1127330 / 0x6646f5b) on disk.
2. Build + run the game; capture DrawItems vs Frame records at Frame+0xB4700 / 0x94700 / 0xDC57E8 and compare; flip CLOSES? to YES with
   the capture commands/results cited.
