# Progress: re_m1d_clones (M1d batch: 0x6698e30 body, 0x66d9af0 callee map, 0x6b84e60, 0x66ea3d0 census)

## NEXT

Next unit: (1) BatchActor extractor 0x66d9af0 full callee map via rdis (`tools\rdis\target\release\rdis.exe <exe> -c "callees 0x66d9af0"` batched), one-line meaning per callee, fold in with 66d9af0_builders.md findings; write into docs/functions/66d9af0.md (NOT BGFX_MAP.md). (2) ItemInHand 0x6698e30 remaining: D-tree leaves 0x669be56..0x669bef8 exact mapping, G packet copies 0x669c35f..0x669c8f9, F shared_ptr bookkeeping; disasm source: `python tools/sigs/disrange.py 6698e30 669edE4 > %TEMP%\ih.asm` (full function 0x5fb4 + static init blocks to 0x669ede4). (3) 0x66ea3d0 sub-extractor switch census. (4) 0x6b84e60 skinned clone start.

Exe: `C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe`.
rdis: `tools\rdis\target\release\rdis.exe <exe> -c "cmd; cmd"` (loads exe once per process; batch commands).

## Log

- 2026-11-15: session start. graphify CLI not installed (graphify-out/graph.json queried directly with python: graph covers project source, not exe RVAs). rdis binary present and working (help + command dispatch confirmed; HELP const is stale — v2 commands sum/cfg/gates/path/uses/... work but are not listed by `help` [tooling gap to report]).
