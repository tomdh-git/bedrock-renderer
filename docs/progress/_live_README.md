# Live capture output (for agents: READ ONLY, never touch the game)

Produced by `tools/livecap/livecap.lua` (run by the Claude orchestrator through Cheat Engine: rotating hardware execute breakpoints, logging only, nothing written into the game). Game: Minecraft.Windows.exe 1.26.62.01, in a populated world. Check `_status.txt` first (RUNNING / DONE, hit counts and sample counts per target).

Files: one `<target>.txt` per target in `tools/livecap/targets.lua` (name, rva, kind).
- kind `visitor` (item/ui/editor/sky/light/effect visitors): line = `tag descptr hex`. `hex` is the description object memory (0x300 bytes, little-endian memory order, byte 0 first). Item tag 6 = ItemInHand, tag 3 = chunk, etc (see docs/data/item_visitor_tag_reads_1.26.62.01.txt and docs/functions/*visitor*.md). Distinct tags appear once or twice.
- kind `regs` (extractors, bodyActor, nametag, gameface): line = `REG=value hit=N hex` for REG in RCX,RDX,R8,R9: 0x200 bytes at the address held by that register at function entry. Which register is the description is in the function's dossier (docs/functions/<rva>.md); the other registers are context objects. Pointers inside dumps point into live memory; only the dumped bytes are available.

How to use in a unit: decode floats/ints per offset, compare with the struct headers under src/sdk/mc/deps/minecraft_renderer/framebuilder/*.h, and write findings (offset, size, type, evidence line) into your progress file. Mark `[V live]` and quote the file name + line number. Values that are constant across samples are constants/defaults; values that differ per sample are per-object data. Do not guess sizes beyond the dump. If a needed target or more samples are missing, write that in your progress file as a request for the orchestrator (targets are added in tools/livecap/targets.lua by the orchestrator).
Older one-off dumps: docs/data/live_chunk_desc_1.26.62.01.txt, live_desc_sky_light_effect_1.26.62.01.txt, live_desc_item_ui_editor_sky2_1.26.62.01.txt, live_item_payloads_1.26.62.01.txt.

CORRECTION 2026-11-15: the light visitor (0x6640d80) and editor visitor (0x66742f0) take their {desc,tag} argument in RDX, not R8; the earlier light line in docs/data/live_desc_sky_light_effect_1.26.62.01.txt is INVALID (wrong register). Use docs/data/live/light_visitor.txt / editor_visitor.txt (re-captured with arg=RDX).
