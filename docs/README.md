# bedrock-renderer

Reference repository containing renderer reversal documentation and Minecraft bedrock SDK headers.

## docs/
Renderer reversal documentation for BlueySenseV2. Includes:
- `RENDER_*.md` — reversal plan, catalog, checklist, and callgraph docs
- `functions/` — per-function reversal notes
- `data/` — TSV/TXT/JSON dumps of render hashes, vtables, layouts, and inventory data
- `progress/` — per-subsystem progress tracking

## src/sdk/mc/
Minecraft bedrock SDK header files (mc/ subdirectory only). Extracted from BlueySenseV2/src/sdk/mc/.

## tools/sdkgen/
Python SDK generation scripts: check_offsets.py, gen_component_table.py, gen_types.py, layout.py

## Root-level files
- `Sigs.json` — signature definitions
- `OffsetProvider.h` — offset provider header
- `Layout.h` — layout header

## Notes
This is a reference repository. It is not a standalone buildable project.