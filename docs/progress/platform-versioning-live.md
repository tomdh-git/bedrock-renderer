# Progress: platform-versioning-live

## NEXT
Unit 2: K-P4/K-P6/K-P7/K-P9/L18 review (SelfTest.cpp, Sigs.json counts, OffsetProvider). R12 done, R13 open (Editor visitor consts).
Then: K-P7/K-P9/L18b (SelfTest review), M4a-d, live polls L10/L17 (obj=[base+0x12BB4910], ctx=[base+0x12AE1748]).

## Entries (newest last)

### R12 - DONE
- tools/sigs/descscan.py edited: `--stop-at-write` ends the read scan at the first overwrite of the description register (or any call when that register is volatile); per-visitor register map `VISITOR_REG` (Effect 0x666aca0 r15, Sky 0x66560f0 rdi, UI 0x6664a00 r9, Light 0x6640d80 rsi, Item 0x6646980 rdi) used when --reg/--start are absent: the scan then starts after the visitor's own `mov reg,[r8]/[rdx]` load. [V] ran on all five visitors (e.g. Sky: reads +0x00..+0x128 until rdi is reloaded at 0x6656f30).
- Limit [I]: inside one visitor the same register holds different descriptions per case, so offsets of a whole-visitor run mix cases; use --start/--end per case (group_visitors.md) for per-description reads.

### R13 - OPEN (Editor visitor 0x66742f0 has an anchor but no constants: Editor tags 0-7 payloads are untyped, R11)
- Sigs.json: appended deps.bgfx.FrameBuilder.{visitEditor,visitEffect,visitUI,visitSky,visitItem,visitLight} (prologue sigs from mksig, unique in 62.01 [V]; they include the frame-size dword so a stack-size change breaks them: then re-find via the zone strings "FrameBuilder - Insert <group>" -> wrapper -> single non-profiler callee). Wrapper-route sigs are NOT unique (the six wrappers are one template; only Sky is), documented.
- New tool tools/sigs/wrappersig.py (wrapper -> '@N' call-target signature; works for Sky only). Also found: capstone reports disp_size 2 for rip-relative operands behind a 66 prefix, so tools/sigs/mksig.py leaves 2 disp bytes unwildcarded there (not fixed in mksig, not mine; wrappersig fixed).
- layout_asserts.json + RenderLayoutAsserts.h (kVisitSky/Light/Item/Effect/UI + kFunctions): Sky 0x548,0x138,0x128,0x11C,0x10C; Light 0x800,0x648,0x4A0,0x1D0,0x84; Item 0x140,0xC8,0xE8,0xC0; Effect 0xF8,0xA0,0xB0; UI 0x90. `python tools/sigs/layoutcheck.py` -> 186 assertions, 0 failed.
- Caveat [I]: a constant is "present in the visitor body" (raw immediate/displacement), not proof of which case uses it; backs text states the meaning.
