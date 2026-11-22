## NEXT
step 2

# oc U-EF1b — VV pending pass resource rows (F1b remaining 6 passes)

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only.
Input data read in full: docs/progress/oc_U-F1b.md, docs/progress/oc_U-F1b2.md (50 ordered pass-declaration call sites), docs/progress/oc_U-EF1b_r3.md (in/out resource offsets analysis).
Orchestrator pending list (do NOT redo the 6 passes already with [V] rows):
  - ClearGBuffer/ScenePrepass
  - ClearStencil/WaterSurfaceStencil
  - TransparentDegamma (resolve vtable xmm7=[0xF546BAA] by dumping the 16 bytes there and the code that loads it)
  - WaitOnUpscalingOutput
  - FullScreenOverlayObjects
  - FullScreenOverlayTransparent
Order per ORCHESTRATOR 2026-11-22: FullScreenOverlayObjects, FullScreenOverlayTransparent, WaitOnUpscalingOutput, ClearStencil/WaterSurfaceStencil, ClearGBuffer/ScenePrepass, TransparentDegamma.

Method per pass: name-string xref -> helper call (e.g. 0x567C8B0, 0x56A8BB0, 0xBB66E20, 0x5669AE0) -> dis helper to first `lea rax,[rip+vtable]` / `mov [rcx],rax` (vtable stored into new pass object) -> `vt` that RVA: slot1 -> lea r8 -> execute body -> list resources read/written as [V] rows. Write each finished pass's rows immediately.
