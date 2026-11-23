## NEXT
step 2

# Unit U-EQ5d — Q5d Pass-level rewrites (own upscale, own post) behind the registry

Checklist item Q5d (docs/RENDER_CHECKLIST.md line 586): "Pass-level rewrites (own upscale, own post) behind the registry (REVIEW: registry entries + stubs exist, 30 [V]; TAAUpscaling body 0xbc8ab12 and ScreenDraw body 0xbc04dc0 not reversed, no working replacement, not ticked)".

Pending part of this line: reverse the two pass bodies at instruction level so a working replacement exists on disk. Registry half (RewritePasses.h/.cpp, RewriteRegistry entries, Sigs.json sigs for PassTAAUpscaling @0xbc8ab12 and PassScreenDraw @0xbc04dc0) already exists; see src/client/features/render/rewrite/.

This file is my only output. Contents: reversal of 0xbc8ab12 and 0xbc04dc0 with verbatim [V] proof rows, the C++ replacement code on disk, and the CLOSES? line.
