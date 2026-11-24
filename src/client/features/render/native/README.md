# native: the game's render path as our own source

Every function of the render path (bgfx, D3D12 backend, RenderDragon, FrameBuilder, pass bodies) lifted from the exe into C++ that does exactly what the original does, then run as our own code ("Native mode"). Plan: `docs/RENDER_DONE_STATE.md`. Rules and the definition of done per function: `docs/RENDER_NATIVE_SPEC.md`. Work list: `docs/RENDER_CHECKLIST.md` (native checklist).

Layout: `bgfx/`, `d3d12/`, `dragon/`, `framebuilder/`, `passes/`, `helpers/`; framework `Lift.h` / `Boundary.h` (X0d). One `<Class>_<method>.cpp` per function whose first line is `// LIFT 0x<rva> size 0x<size> 1.26.62.01 <name>`, plus its `.h` with layout constants and `static_assert`s. Check with `python tools/sigs/liftcheck.py <rva>`.

This directory is linked into the professional repo (`tomdh-git/bedrock-renderer`) by `tools/mirror_sync.ps1`.
