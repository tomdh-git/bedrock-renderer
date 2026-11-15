# Progress: small overlay descriptions (FadeToBlack / FullscreenEffect / AimAssistHighlight / EditorHighlight)

Agent: `re_small_overlays`. Target exe: `C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe`.
Scope: STATIC ANALYSIS ONLY. No debugger / patches / commits. Tags [V]/[I]/[?] on every claim.

Checklist items covered: RENDER_CHECKLIST **R4** (AimAssistHighlight), **R5** (EditorHighlight), **R9** (FadeToBlack + FullscreenEffect config).
Also BGFX_MAP 6ih partials for the four Effect tags (5/6/7/8).

## NEXT
- Unit 1 (in progress): EditorHighlight — find the consumer of pass+0x80 (the pass object returned by 0x5aba5c0 at ctx+0x9D0).
  Commands: `rdis "<exe>" 0x666b316 --calls`, then scan for readers of the queue vector.
- Unit 2: FadeToBlack — locate the real producer/clone of the tag-5 description (thin clone list in BGFX_MAP 6if: none for tag 5; it is a fat clone or inlined).
- Unit 3: FullscreenEffect config object — decode +0x180/+0x181/+0x185/+0x1A8 meanings via 0x66b2b30 callers / config loader.
- Unit 4: AimAssistHighlight — confirm 0x88 size and the shared-tail +0x84 read ownership (already contradicted by the constructor; verify the tail).
- Unit 5: D2-style analysis + dossier writes + BGFX_MAP entry text.

---

## Unit status log