# TOOL-BUILD: tools/sigs index + mine agent scratch scripts

## NEXT
- [x] run `tools/rdis/target/release/rdis.exe <exe> help` to enumerate subcommands
- [x] write `tools/sigs/toolindex.py` (grouped index + cheat table)
- [x] run toolindex.py, verify cheat table entries against real tools
- [x] write `tools/mine_agent_scripts.py`
- [x] run mine_agent_scripts.py, capture summary
- [x] append to docs/OPENCODE_BRIEF.md
- [x] DONE

## PROOF — docs/TOOLS_INDEX.md (top)
```
# TOOLS_INDEX.md — Auto-generated from tools/sigs/ + rdis


## CHEAT TABLE — "I need to…" → use this

| I need to… | Tool | Example |
|------------|------|---------|
| Read pointer at an RVA | `peptr.py` | `python tools/sigs/peptr.py 0xF9A8C78` |
| Read bytes/string/u32 at an RVA | `pepeek.py` | `python tools/sigs/pepeek.py 0xf4ed700 u32 4` |
| List callers of a function | `rdis callers` | `rdis.exe <exe> callers 0xbc60740` |
| Clean rdis listing to UTF-8 | `oc_clean_listing.py` | `python tools/sigs/oc_clean_listing.py listing.txt out.txt` |
| Find strings containing text | `rdis str` | `rdis.exe <exe> str dragon` |
| Dump vtable slots | `vtdump.py` | `python tools/sigs/vtdump.py 0xF4ED2D0 8` |
| Why liftcheck fails | `liftcheck.py` | `python tools/sigs/liftcheck.py 0xbc60740` |
| Decode jump table | `jt.py` | `python tools/sigs/jt.py 0xf4ed700 4` |
| Cross-refs to an address | `rdis xr` | `rdis.exe <exe> xr 0xbc60740` |
| Verify quoted instructions | `verify_oc.py` | `python tools/sigs/verify_oc.py doc.md` |
| IAT import names | `peimports.py` | `python tools/sigs/peimports.py` |
| Read NUL-terminated string at RVA | `rvastr.py` | `python tools/sigs/rvastr.py 0xf16e9f0` |
| Disassemble a range | `rdis dis` | `rdis.exe <exe> dis 0xbc60740 40` |
| Control-flow walk from address | `rdis walk` | `rdis.exe <exe> walk 0xbc60740` |
| Find field accesses [reg+disp] | `rdis fld` | `rdis.exe <exe> fld 0x20 --base rcx --w` |
| Annote function with strings/vcalls | `rdis fn` | `rdis.exe <exe> fn 0xbc60740` |
| List callees of a function | `rdis callees` | `rdis.exe <exe> callees 0xbc60740` |
| Search immediate values | `rdis imm` | `rdis.exe <exe> imm 0x75DF36B7` |
| Find component users | `rdis comp` | `rdis.exe <exe> comp ActorRotationComponent` |
| Where pointers to address are stored | `rdis ptr` | `rdis.exe <exe> ptr 0xF9A8C78` |
| Signature matching | `rdis find` | `rdis.exe <exe> find 488B??488D` |
| Store analysis on listing | `stores.py` | `python tools/sigs/stores.py listing.txt` |
| Slot producer scan | `slotscan.py` | `python tools/sigs/slotscan.py 0x378` |
| Case walk from head | `casewalk.py` | `python tools/sigs/casewalk.py listing.txt 0xbc60740 rdi rsi` |
| Live memory decode | `livedec.py` | `python tools/sigs/livedec.py live.txt` |
| Coverage check | `cov_oc.py` | `python tools/sigs/cov_oc.py 0xbc60740 0xbc62740 doc.md` |
```

## PROOF — mine_agent_scripts.py summary
```
=== MINE SUMMARY ===
Scanned 99 scripts from C:/Users/Atomi/AppData/Local/Temp/opencode (since 720h ago)

Unknown                36 scripts
PE read                22 scripts
Listing parse          15 scripts
String search          11 scripts
Disassembly             5 scripts
Table gen               4 scripts
Liftcheck/verify        2 scripts
Vtable/slot             2 scripts
Xref/caller scan        2 scripts
```

Clusters with ≥3 scripts and no matching existing tool → GENERALIZE CANDIDATE:
- Unknown (36 scripts, all "no match") — candidate
- Listing parse (15 scripts, matches: verbatim.py, livedec.py, xref.py, peptr.py, pepeek.py, slotscan.py, showlines.py, oc_clean_listing.py) — has matches
- String search (11 scripts, matches: xref.py, verbatim.py, peptr.py, oc_clean_listing.py, pepeek.py) — has matches
- PE read (22 scripts, matches: peptr.py, pepeek.py, xref.py) — has matches
- Disassembly (5 scripts, matches: peptr.py, xref.py) — has matches
- Table gen (4 scripts, matches: peptr.py, pepeek.py) — has matches

## VERIFIED CHEAT TABLE ENTRIES (ran each once)
- peptr.py 0xF9A8C78 → `0xF9A8C78: section .rdata file_off=0xf9a7678 -> 0xf9b055e`
- pepeek.py 0xf4ed700 u32 4 → u32 table at image_base=0x10000EEA5E90 rva=0xF4ED700
- rdis callers 0xbc60740 → 6 callers listed
- oc_clean_listing.py → "clean lines: 12" on utf-8 listing
- rdis str dragon → 8 strings found (e.g., "minecraft:magma_aft:ender_dragon...")
- vtdump.py 0xF4ED2D0 8 → 8 slots with targets + strings
- liftcheck.py 0xbc60740 → LIFTCHECK FAIL with reasons
- jt.py 0xf4ed700 4 → jump table decoded (tag 0 -> 0xf4ed747)
- rdis xr 0xbc60740 → cross-refs found
- verify_oc.py on clean listing → "match=8 mismatch=0 no-such-instr=0"
- peimports.py → IAT imports listed
- rvastr.py 0xf16e9f0 → string at RVA