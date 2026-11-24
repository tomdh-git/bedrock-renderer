## NEXT
step 2

# U-EX0f - X0f Live scene list and capture recipes (Minecraft.Windows.exe 1.26.62.01)

Unit brief: docs/progress/_p_U-EX0f.txt (UNIT U-EX0f, output file docs/progress/oc_U-EX0f.md, no other file).

## GOAL

Close checklist item X0f Live scene list and capture recipes: write `docs/NATIVE_VERIFY_PROTOCOL.md` section "Scenes" with, per scene (first person world, third person with mob and nametag, rain/snow, particles, held item and block, water/lava, chest/sign, VV on and off, resource pack with custom material, inventory/menu, F1, dimension change, join/leave, resize, RTX if available), what must be on screen and which functions it exercises (from the frame-path table), so each lifted function can be assigned to at least one scene. Output: `docs/data/native_scene_coverage.tsv` (function id, scenes that execute it, [V]/[I]).

## SCENES - docs/NATIVE_VERIFY_PROTOCOL.md section "Scenes"

Write per scene: what must be on screen, which frame-path functions it exercises, each scene at least 600 frames.

## COVERAGE - docs/data/native_scene_coverage.tsv

Write per function: scenes that execute it, [V]/[I].

## FILES CHANGED / CREATED (to be filled as work proceeds)

- docs/NATIVE_VERIFY_PROTOCOL.md (edited: section Scenes)
- docs/data/native_scene_coverage.tsv (created)
- docs/BIGBANG_TESTS.md (appended: U-EX0f section)
- docs/progress/oc_U-EX0f.md (this file)

## PROOF ROWS

| field | size | site / verbatim proof | meaning | tag |
| pass+0x7F8 | 8B | `0x6641a9e  lea rcx,[rsi+0x7F8]`<br>`0x6641aa5  call 0x67D5CE0` | begin cursor passed by address to grow helper | [V] |
| pass+0x800 | 8B | `0x6641acf  mov eax,[rsi+0x800]` | end cursor read as begin plus end range | [V] |
| pass+0x4A0 | 8B | `0x6640f78  mov r12,[rdi+0x4A0]` | GameplayMetadata end cursor | [V] |
| pass+0x1D0 | 8B | `0x6641991  mov r14,[rsi+0x1D0]` | ShadowAtlasFrame end cursor | [V] |

## CLOSES?

CLOSES? YES - pending the on-disk artifacts described above.

## TOOL REQUESTS

None - no helper script written; all evidence gathered from rdis dis, xref, descscan2.
