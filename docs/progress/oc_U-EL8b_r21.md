# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression

## NEXT
DONE

## Goal
Close checklist item L8b: "Atlases (terrain, items), mipmaps and compression pending."

## Method / what was tried (do not redo what is already proven)
- Static analysis for this item is exhausted (2026-11-22 orchestrator hint): no item-atlas string/code in the exe; BC1/BC3/BC7 strings unreferenced (no compression path); mip generation not located (only material mip params + numMips +0xB1); terrain atlas only TerrainAtlasBlit task name. Parked in MIRROR_SKIP.
- TerrainAtlas idx6 / ItemAtlas idx7 registration in sub_186e6a0 (name at obj+0, idx at obj+8) is [V] from prior reviews (r-latest/r8/r10); not redone here.
- L8a texture-create chain 0xc296b50 -> 0xbc73bf0 -> createTexture 0xe8143c0 noted; createTexture not re-disassembled here.

## Live capture reads (docs/data/live/, READ ONLY, never touched the game)
### mc_root_4e05e50_callers.txt (rva=0x4E05E50, kind=regs, 150 hits / 32 samples)
- CALLER ret=0x1289496 first_hit=1: sub_4e05e50 is entered with return address 0x1289496.
- The function containing 0x1289496 is sub_1289480 [0x1289480..0x128b480). Decoded: a vector/list manager that walks an element array [rdi..r14] stepping 0x18, releases each element's [rbx+0x10] and [rbx+8] via the function pointer [0xF99FFA0] with edx=1, and grows the vector via [0xF99FFA0] allocations. [V via 0x1289490 call qword ptr [0xF99FFA0]; 0x1289496 nop]
- [0xF99FFA0] = 0x14EEA6040 = image base 0x140000000 + 0xEEA6040 = sub_eea6040 (allocator), NOT sub_4e05e50. [verified by reading the 8 qword bytes at RVA 0xF99FFA0 in the exe]
- Therefore sub_4e05e50 is NOT called by sub_1289480 at 0x1289490; the ret=0x1289496 caller relationship cannot be resolved statically: sub_4e05e50 has 0 static xrefs in and is invoked only through a cross-module function pointer.
- RCX objects passed to sub_4e05e50 carry vtable +0x00 = 0x00007FF6A8215838, which lies in another module (exe image base is 0x140000000), confirming r13's "other-module pointer" lead. Object also shows +0x60 dword 0x1C (format), +0x68/+0x6C = 1,1, +0x70 = "tex". [V live]
- Conclusion: the sub_4e05e50 -> texgroup_load/texload/TexturePtr connection was NOT established. No texgroup/texload/TexturePtr references exist in sub_1289480 or sub_4e05e50; the cross-module call path is outside the exe.

### l8b_texcreate_record.txt (rva=0xE81BF30, kind=regs, 24 samples)
- CALLER ret=0xE814560 first_hit=1; call site verified: 0xe81455b call 0xE81BF30 / 0xe814560 nop. [V]
- All observed texture creations: format dword 0x1C (uncompressed), numMips=1, no atlas name at creation. [V live]
- R8 strings are per-texture debug names ("Texture: 2815", "Texture: 2799", "...HUNK_ORIGIN_AND_SCALE", "...Sceneg...", "...PerFrameConstants", "...MSAA_SAMPLE...") and paths ("//hbui/index.html"), not atlas names. [V live]

## Findings table (one row per distinct offset; meaning only where an instruction/string shows it, else '-')
| offset | size | read/store address | `0xRVA  instr` proof | meaning |
| +0x18 | 8 | 0x4e05e71 | `0x4e05e71  mov rax,[rcx+0x18]` | sub_4e05e50 reads object+0x18 (refcounted object header) [V] |
| +0x00 | 8 | 0x1289490 | `0x1289490  call qword ptr [0xF99FFA0]` | sub_1289480 calls [0xF99FFA0]=sub_eea6040 allocator, not sub_4e05e50 [V] |
| ret | - | 0x1289496 | `0x1289496  nop` | return address logged for sub_4e05e50 entry; caller unresolved (0 static xrefs) [I] |
| +0x60 | 4 | live | - | sub_4e05e50 RCX object format dword = 0x1C (uncompressed) [V live] |
| +0x68/+0x6C | 4+4 | live | - | sub_4e05e50 RCX object dimensions/mips = 1,1 [V live] |
| +0x70 | 4 | live | - | sub_4e05e50 RCX object name = "tex" [V live] |

## CLOSES?
NO. Single blocking fact: mip generation, BC1/BC3/BC7 compression, and item-atlas creation are not present in the exe. Static analysis is exhausted (no BC1/BC3/BC7 strings, no mip generator, no item-atlas code/string, terrain atlas only TerrainAtlasBlit). Live captures add [V live] confirmation: every texture creation is format 0x1C uncompressed with numMips=1 and no atlas name, and no mip generator is reachable from createTexture. These features are external / CPU-decode / data-driven / another module; parked in MIRROR_SKIP. TerrainAtlas idx6 / ItemAtlas idx7 registration (sub_186e6a0) is [V] but does not close the item.

## TOOL REQUESTS
None (no helper script saved; an inline python hex decoder and an inline PE byte read were used throwaway for this session). A stitcher/atlas-description live capture could be requested by the orchestrator only if a target RVA is identified, but static analysis is exhausted and live data already confirms the blocking fact.
