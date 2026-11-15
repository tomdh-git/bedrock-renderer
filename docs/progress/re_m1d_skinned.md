# Progress: re_m1d_skinned (M1d unit 4: skinned clone 0x6b84e60)

## NEXT

Next unit: disassemble `0x6b84e60` with rdis (`tools\rdis\target\release\rdis.exe "<exe>" -c "dis 0x6b84e60; path 0x6b84e60; sum 0x6b84e60"`), read the emitted dump, map constructor prologue / bone-joint data read / skinning-matrix build / vertex-transform loop / output buffer layout / shared_ptr bookkeeping, then write `docs/functions/0x6b84e60.md` + additive SDK header edits + `docs/data/layout_asserts.json` entries, and finish `docs/progress/re_m1d_skinned.md` with the proposed BGFX_MAP entry text.

Exe: `C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe`.
rdis: `tools\rdis\target\release\rdis.exe "<exe>" -c "cmd; cmd"` (loads exe once per process; batch commands).
python: `PYTHONUTF8=1 python tools/sigs/xref.py <cmd>`.

## Log

- 2026-11-15: session start. Read docs/AGENT_BRIEF.md, tools/README.md, docs/progress/re_m1d_clones.md, docs/BGFX_MAP.md sections 6cv/6ec/6gc/6gg/6gh, and src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h. Task = M1d unit (4): the last fat clone, skinned clone 0x6b84e60. Prior state from 6ec/6gc: description struct `RenderSkinnedMeshDescription` (0x1D0, constructor 0x668d350 fully reversed) is typed in Descriptions.h; the clone 0x6b84e60 itself is NOT decoded (fields +0x10/+0x18/+0x20/+0x30/+0x38/+0x60/+0x74-76/+0x108-118 listed, meanings pending). Callers: 0x6b80870, 0x6b80f00, 0x6e8dff0. Related: geometry builders 0x6b84200 ("Skinned Mesh", 0x3f8) and 0x6b84680 (IBs "Skinned Mesh Quads"/"Skinned Mesh Tris", 0x71c). Second producer 0x4e39f20 (not this unit). Item tag 7, vslot 0x378.