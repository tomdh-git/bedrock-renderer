# U-FONT: UI font glyph atlas sidecar parsing progress

## NEXT (resume here)
Step 1: enumerate callers of 0x4fb3870 and 0x4fbe0c0 via `python tools/sigs/xref.py callers 4fb3870` and `python tools/sigs/xref.py callers 4fbe0c0`, then disassemble both seed functions (`python tools/sigs/disrange.py 4fb3870 <hi>` / `4fbe0c0 <hi>`) to find where each calls into .info reading. Then follow callers down to the .info contents reader (JSON/string parsing or fixed-record reads) and the struct that holds per-glyph advance/size/uv. Target output file: docs/progress/oc_U-FONT.md only; no other file edits.

## Ground rules (from OPENCODE_BRIEF.md)
- Static analysis only. Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe 1.26.62.01; RVAs relative to image base.
- Every claim tagged: [V] saw in disassembly (cite RVA), [I] inferred, [?] unknown. Never invent sizes/offsets/names.
- Write results immediately after each step; keep NEXT block at top.

## Known from docs/functions/ui_font_text_leads.md
- 0x4fb3870 builds name + "_ttf" + ".png" and ".info" sidecar path (refs "_ttf", ".png", ".info") [leads]. 0x4fbe0c0 same for "_ttfmsdf".
- Callers of 0x4fb3870/0x4fbe0c0 claimed: 0x4fb2900, 0x4fbbea0, 0x4fbbf20, 0x4fbcab0, 0x4fc3930, 0x4fc3db0, 0x4fe0e10 [V per leads; re-verify].
- GlyphTexture bound at 0x674dca3, GlyphHeight at 0x674e06a, "UI/Text" at 0x674a59e/0x674d880 inside 0x674a3a0 (UIText extractor) [leads].
- cohtml separate (L14b).

## Done
- Callers of 0x4fb3870 [V xref callers]: 0x4fb2900 (off 0xce8), 0x4fbbea0 (0x4d), 0x4fbbf20 (0x1a0), 0x4fbcab0 (0x20e), 0x4fe0bc0 (0xf6)
- Callers of 0x4fbe0c0 [V xref callers]: 0x4fc3930 (0x192), 0x4fc3db0 (0x1f6), 0x4fe0e10 (0xda)
  (leads listed 0x4fe0e10 for the first too; xref says 0x4fe0bc0 — re-verify by disassembly)

## In progress
- Disassemble seed functions 0x4fb3870 and 0x4fbe0c0 to find the .info reader call they make
  - 0x4fb3870 disassembled 4fb3870..~4fb47f8 [V]. Key observations:
    - 4fb3e3c: `mov dword ptr [r8 + rcx], 0x6674745f` writes "_ttf" + null (LE bytes 5F 74 74 66 = "_ttf")
    - 4fb3c41: `lea rdi, [rip + 0xd90d8c0]` then call 0xe943178 — string target unresolved (RIP-relative, points to another section)
    - 4fb3cee: vtable call [rip + 0xa9ec2ac] with rdx=&rbp+0x1fd8 buffer — likely file read [I]
    - 4fb3f18: call 0x4a8360 — path concat helper [I]
    - Function continues past 4fb47f8 (truncated at 4fb47f8: `je 0x4fb8d6d`)
  - 0x4fbe0c0 disrange FAILED — output started at 0xa60cf15 (wrong address range, tool issue). Retry with rdis or smaller range.

## Next steps
- Resolve rip-relative string targets (0xd90d8c0 from 4fb3c41, 0xa6061b5 from 4fb3e1b, 0xa5fec3e from 4fb3ef9)
- Use `python tools/sigs/xref.py str ".info" / ".png" / "_ttf" / "_ttfmsdf"` to find string xrefs
- Disassemble callers: 0x4fb2900, 0x4fbbea0, 0x4fbbf20, 0x4fbcab0, 0x4fe0bc0, 0x4fc3930, 0x4fc3db0, 0x4fe0e10
- Find the .info contents reader and the per-glyph struct

## Open
- .info file reader function RVA unknown
- per-glyph struct (advance/size/uv) unknown
- text measure/draw consumer unknown
