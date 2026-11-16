# UNIT U-E1d — Item visitor forwarders (tags 6/8/10)

Status: IN PROGRESS

## NEXT
Resume here: read docs/BGFX_MAP.md sections 6w/6ed + src/sdk/mc/deps/minecraft_renderer/framebuilder/ItemVisitorTags.h for clone tag-store struct names; then run `python tools/sigs/dumplist.py 0x6646980 0x664ef20 docs/data/listings/item_visitor_6646980_664ef20.txt`; then `python tools/sigs/casewalk.py <listing> 0x6647320 rcx rdx r8 r9` for tag 6, same for 0x66473e6 (tag 8) and 0x6647383 (tag 10); then xref "GlowInkSign" for tag 8.