# bedrock-renderer

Reference repository containing renderer reversal documentation and Minecraft Bedrock renderer SDK headers (target: **1.26.62.01**, RenderDragon / bgfx / D3D12).

## Repository Overview

### `docs/`
Complete renderer reversal documentation:
- `RENDER_CATALOG.md` — Map of all renderer components, subsystems, and descriptors
- `BGFX_MAP.md` — Deep architectural breakdown of bgfx, RenderDragon framebuilder, pass names, and D3D12 mapping
- `FRAME_CALLGRAPH.md` — Complete frame execution order and callgraph
- `RENDER_CHECKLIST.md` — Reversal progress checklist
- `functions/` — Instruction-complete per-function reversal notes and struct field tables
- `data/` — TSV, TXT, and JSON dumps of render hashes, vtables, layouts, and component tables

### `src/sdk/mc/`
Renderer-focused Minecraft Bedrock SDK headers:
- `deps/bgfx/` — BGFX context, frame structures, view, encoders, uniforms, caps, and D3D12 context/tables
- `deps/minecraft_renderer/` — RenderDragon framebuilder, dragon scheduler, pass names, mesh data, and draw item descriptors
- `client/renderer/` — Tessellator, actor renderers, level projection, and shader managers
- `deps/minecraft_camera/` & `deps/vanilla_camera/` — Camera controllers and matrices
- `deps/core/math/` & `deps/core_graphics/` — Shared math (Vec, Matrix, Color) and graphics primitives
- `deps/ecs/` & `deps/vanilla_components/` — Renderable entity components and entt storage

### Root Files
- `Sigs.json` — Verified renderer memory signatures for 1.26.62.01
- `OffsetProvider.h` — Proven game offsets and vtable indices
- `Layout.h` — Win64 layout macros, callVirtual wrappers, and property helpers

---

## Versioning & Tagging System

Releases follow a target-prefixed semantic versioning convention:

```
<minecraft_version>-v<semver>
```

- **Current Stage (Alpha):** `1.26.62-v0.1.0-alpha`, `1.26.62-v0.1.1-alpha`
- **Milestone Releases:** `1.26.62-v1.0.0`
- **Incremental updates for same Minecraft version:** `1.26.62-v1.1.0`
- **Major breaking SDK redesign for same Minecraft version:** `1.26.62-v2.0.0`
- **Future game version updates:** `1.26.70-v0.1.0-alpha`

## CI & Automated Releases

GitHub Actions automatically packages and releases:
- **Rolling Pre-release (`latest-1.26.62`)**: Updated on every push to `main` with the latest headers, signatures, and reversal docs.
- **Tagged Releases**: Published on any version tag with a packaged `bedrock-renderer-sdk-*.zip` attached.
