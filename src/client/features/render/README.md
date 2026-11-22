# Render subsystem

`Renderer` is the swapchain-facing facade. `RendererContext` in `Renderer.cpp` keeps device, swapchain, frame-list, resize, and recovery state together so frame construction and teardown share one ownership boundary.

- `backend/` owns D3D12 overlay submission and buffer state.
- `context/` owns ImGui setup and teardown.
- `draw/` contains reusable drawing and image helpers.
- `chams/`, `lce/`, and `packcolor/` own specialized renderers and color integration.
- `post/` owns full-screen effects; `tracker/` observes the game's render commands.
- `underui/` owns the frame plan, captured GPU state, and passes inserted around the game's scene.

Keep passes declarative where possible and have `Renderer` own frame timing, device generation, and lifecycle transitions. Capability/readiness changes should be visible through the health panel.
