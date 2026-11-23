## NEXT
DONE

# UNIT U-EL14c: Text/font SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas

## Live state this run

`python tools/sigs/livemem.py status` -> "game not running (no Minecraft.Windows.exe process)" [V]. The game is NOT running, so livemem is unavailable this run (per brief rule #30: write the request in the progress file and stop the live angle).

docs/data/live/_status.txt: `l14c_glyph_draw` hits=0 samples=0; `l14c_record_builder` hits=0 samples=0 [V] — the two orchestrator captures (0x674a3a0, 0x6664760) ran in a loaded world and got 0 hits; not retried per orchestrator 2026-11-22 22:35.

`0x5679db0` (UniformBlock::setUniform / setVec4Array) is too hot: it is called on every uniform write, so an 8-sample capture filtered to the GlyphTexture slot-hash name bytes cannot isolate the GlyphTexture write. Per the orchestrator fallback: state that and answer NO. No capture was queued.

## Offset table (one row per distinct offset; all sites listed; verbatim instr lines verified against the exe with rdis)
| Offset | Size | Read/store address | Verbatim `0xRVA  instr` proof line | Meaning ([V]/[I]/[?]) |
|---|---|---|---|---|
| 0x5679dbf | 2 | [rdx] = a1+0x0 | `0x5679dbf  movzx r14d,word ptr [rdx]` | sub_5679DB0 reads the slot index u16 from the {index,flag} parameter [V] |
| 0x5679df9 | 5 | call 0xEEC6EC0 | `0x5679df9  call 0xEEC6EC0` | memcpy(dst=slot, src=namePtr, 16): writes the 16-byte TEXTURE NAME into the hash-selected slot, NOT a bgfx handle [V] |
| 0x5679dfe | 1 | [r15+r14+0xC] | `0x5679dfe  mov byte ptr [r15+r14+0xC],1` | sub_5679DB0 sets entry[index].valid/bound flag = 1 [V] |
| 0x674aa09 | 16 | [rax] = *[[rbp+0xEB8]] | `0x674aa09  movups xmm0,[rax]` | 16-byte TEXTURE NAME loaded from caller-provided arg8 pointer (the GlyphTexture bind value) [V] |
| 0x674aa91 | 5 | call 0x5679DB0 | `0x674aa91  call 0x5679DB0` | draw-time GlyphTexture bind: writer copies the 16-byte name into the hash-selected slot [V] |

## Answer

SDF glyph uniforms + FONT_TYPE permutation (6ce) are already proven (U-I5c/U-EL14c verify 7/7) and are not redone.

GlyphTexture is bound BY NAME (16-byte texture name), not as a bgfx handle. At draw time sub_674a3a0 hashes "GlyphTexture" (`0x674dca3  lea rdx,[0xF5C6DD7]` -> `0x674dcb4  call 0x79580`), stores the hash at `0x674dd81  mov [0x129FA178],rcx`, walks the 16-byte-entry uniform slot array at [rbp+0xBA0] matching [record+0x28] name hash against that hash, selects the slot (live: index 0x000A = 10), then sub_5679DB0 memcpy's 16 bytes from namePtr into the slot (`0x5679df9  call 0xEEC6EC0`) and sets the valid flag (`0x5679dfe  mov byte ptr [r15+r14+0xC],1`). The 16-byte name is loaded from caller-provided arg8 (`0x674aa09  movups xmm0,[rax]`).

## CLOSES?

NO — single blocking fact (missing REVERSING): the glyph atlas texture creation/update site RVA is unknown. No direct createTexture/updateTexture call exists anywhere in .text; texture creation is vtable-indirect render-thread work (RendererContext slots 26/28, texture table this+0xbde178 stride 0xB8 per BGFX_MAP.md 6z/6aj), so the named atlas bound as GlyphTexture is not located statically. The writer of the 16-byte atlas NAME into the UIText record (arg8 to sub_674a3a0; indirect dispatch slot 0xf2be218; sub_6664760 has 0 static xrefs) is likewise not statically locatable. Live capture is unavailable this run: the game is not running (livemem status) and 0x5679db0 is too hot (every uniform write), so the atlas NAME cannot be dumped live. Closing requires a live trace when the game is running (bgfx createTexture/updateTexture break, or a capture at 0x5679db0 once the game is live).

## TOOL REQUESTS

None this run. A capture at 0x5679db0 was considered and rejected as too hot (UniformBlock::setUniform/setVec4Array fires on every uniform write; 8 name-filtered samples cannot isolate GlyphTexture), and the game is not running so livemem is unavailable. Per the orchestrator fallback: state it and answer NO. Re-request a live trace at 0x5679db0 (or bgfx createTexture slots 26/28) once the game is running.
