## NEXT
DONE

UNIT U-EO3b — Close checklist item O3b: layout_asserts.json + tools/sigs/layoutcheck.py and RenderLayoutAsserts.h constants; every newly reversed function adds constants to both lists — BGFX_MAP 9a; M4c.
Output file: docs/progress/oc_U-EO3b.md (no other file).

1. STATE ON DISK BEFORE THIS UNIT
- docs/data/layout_asserts.json: 21 anchor functions, 199 assertions; `python tools/sigs/layoutcheck.py` -> 199 assertions, 0 failed [V: tool run against the exe, all functions found by sig].
- src/sdk/mc/deps/bgfx/RenderLayoutAsserts.h: kFunctions[] holds 20 functions. The 21st, RendererContextD3D12::submit, IS in layout_asserts.json (8 asserts, rva 0xe82e230, size 0x4d91, all ok) but was NOT in RenderLayoutAsserts.h -> the "constants in both lists" rule was violated for this function.
- docs/functions/e82e230.md: D2-partial dossier for RendererContextD3D12::submit (size 0x4d91, 4017 instructions; rcx+0x19f58 and rcx+0x19f88 dereferenced; Frame offsets 0xDC57F0..0xDC5808 and 0xE746D8 used) [V: dossier on disk].

This unit's pending part: "every newly reversed function adds constants to both lists". RendererContextD3D12::submit is the newly reversed function whose constants lived in only one list.

2. CHANGE MADE (one path)
src/sdk/mc/deps/bgfx/RenderLayoutAsserts.h
- Added kRendererContextD3D12Submit[] with the same 8 constants as layout_asserts.json.
- Added BS_RENDER_LAYOUT_FN("RendererContextD3D12::submit", 0x4D91, kRendererContextD3D12Submit) to kFunctions[].
SelfTest.cpp already #includes this header and iterates kFunctions[], contains()-checking every constant against the anchor function's code (lines 14, 156-169) [V: file read], so the entry is wired into startup validation; the client build itself was not run (constraint: no builds).

docs/data/layout_asserts.json and tools/sigs/layoutcheck.py: no change needed — the manifest already contains all 8 values and layoutcheck passes 199/0 [V: re-run after the .h edit].

3. EVIDENCE TABLE (offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag)
All instruction lines copied verbatim from rdis `dis 0xe82e230` (0xe82e230..0xe83102a; listing held at C:\Users\Atomi\AppData\Local\Temp\opencode\submit_dis.txt) and re-checked against the exe. Sizes: dword/dword-immediate=4, qword read=8.

| 0x1778 | 4B | - (immediate into eax; no memory access) | `0xe82e23c  mov eax,0x1778` | submit stack frame size (stack probe) | [V]
| 0x19F88 | 4B | [rcx+0x19F88] | `0xe82e273  cmp dword ptr [rcx+0x19F88],5` | renderer state; <5 skips submit work | [V]
| 0xDC5808 | 4B | - (imm32 added to rdx; forms &Frame+0xDC5808 {width,height}, no deref of it in this instr) | `0xe82e28d  add rdx,0xDC5808` | Frame backbuffer size {u32 width, u32 h} | [V]
| 0xE746D8 | 4B | [rsi+0xE746D8] | `0xe82e34c  mov r9d,[rsi+0xE746D8]` | Frame counter u32, +1 per frame | [V]
| 0x19F58 | 8B | [rdi+0x19F58] (same [reg+0x19F58] qword read also at 0xe82e39e, 0xe82e487, 0xe82e59c, 0xe82e698, 0xe82e886) | `0xe82e353  mov rdx,[rdi+0x19F58]` | RendererContext resource-table ptr | [V]
| 0x410 | 4B | - (lea forms address rdi+0x410; no memory access) | `0xe82e33e  lea rcx,[rdi+0x410]` | per-view setup side table | [V]
| 0xDC57E8 | 8B | [rax+0xDC57E8] | `0xe8306af  movsxd rcx,[rax+0xDC57E8]` | Frame item count (draw slot counter, cap 0xFFFE) | [V]
| 0x14700 | 8B | [rax+0x14700] (address also formed by lea r8,[rax+0x14700] at 0xe8306bf; no deref there) | `0xe8306c6  mov rdx,[rax+0x14700]` | Frame sort keys u64[] | [V]

4. LISTS NOW IN SYNC
- layout_asserts.json: RendererContextD3D12::submit = {0x1778, 0x19F88, 0xDC5808, 0xE746D8, 0x19F58, 0xDC57E8, 0x14700, 0x410} — present before this unit, all 8 verified by layoutcheck [V].
- RenderLayoutAsserts.h: same 8 values + scan-window size 0x4D91 — added by this unit [V: file edit].
- tools/sigs/layoutcheck.py: unchanged, reads the manifest; re-run -> 199 assertions, 0 failed [V].
- JSON <-> .h constant parity: verified symbol-by-symbol; the only delta was RendererContextD3D12::submit, now closed [V: diff of the two files].

CLOSES? YES — every pending part of O3b/M4c is now on disk and proven by [V] rows: layout_asserts.json and RenderLayoutAsserts.h contain identical constants for every anchor function (the sole gap, RendererContextD3D12::submit, is in both), tools/sigs/layoutcheck.py exits 0 (199 assertions, 0 failed), and each of the 8 constants is backed by a verbatim `0xRVA  instr` proof line from the exe disassembly. Remaining outside this unit's scope: the client build and the in-game SelfTest run (M5; not run here per constraints).
