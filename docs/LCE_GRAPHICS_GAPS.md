# LCE Graphics visual-match audit

This audit compares the currently implemented terrain replacement with the vendored 4J LCE reference. It is a gap list, not a claim of visual equivalence. The terrain signature reader now preserves component masks (including non-contiguous `.zw` inputs) when generating the replacement input declaration and maps shader reads through those masks. This addresses an interface correctness issue, but does not by itself enable new material hashes.

## Current coverage

`features/render/lce/LceTerrain.cpp` replaces selected terrain pixel shaders. Current 1.26.51.01 families include straight cutout, seasonal cutout, seasonal opaque, atlas-alpha output, and non-cutout tint-mask families. The implementation table uses runtime FNV-1a hashes (the pairs from the material map are DXBC header checksums, so the values differ). UV mapping is family-specific and verified from DXIL resource reads and input semantics: straight/seasonal cutout and atlas-alpha output use atlas `TEXCOORD1` plus lightmap `TEXCOORD0`; tint-mask and seasonal opaque use atlas `TEXCOORD0` plus lightmap `TEXCOORD1`. Seasonal variants sample t2 with `COLOR0.xy` and blend with `COLOR0.z`. The shader signature reader preserves component masks and the generated input signature remains linked to the game pipeline. `features/render/lce/Renderer.cpp` deliberately limits substitution to terrain. Actor/player shader substitution was removed to avoid affecting inventory and pause-menu model rendering. The replacement repeats each original pixel shader input signature so it can link with the game's pipeline. These variants still need live PSO and in-game validation.

The installed Minecraft 1.26.51.01 `RenderChunk.material.bin` contains 480 containers: 120 each of SM4, SM5, DXIL vertex, and DXIL pixel programs. Its DXIL programs form 60 unique hashes across vertex/pixel stages. An earlier expansion that rewrote signatures caused D3D12 PSO creation failures (`0x80070057`) and was rolled back. Current additions were selected after bytecode disassembly confirmed their signature and resource/alpha patterns.

The complete installed material map has 157 files and 5,136 unique shader hashes. In `RenderChunk`, tint-mask and season families are partially covered; the current simple families include cbuffer fog color at offset 0. The fade/dither pairs (`7bac81a1`, `752d1a1f`, `73daf84f`, `74c8f678` and related variants) read `DitherParams`, `FogColor`, and `ViewPositionAndTime` from `FragmentUniforms`, use additional interpolants, and perform extra math. They remain native until that behavior is reproduced. Also native are depth/cutout-only programs, fallback programs without material bindings, and other specialized variants.

`TextureShiftRenderChunk.material.bin` includes distinct atlas/material programs and other resource layouts; it requires a separate implementation from ordinary chunks. `RenderChunkForwardPBR.material.bin` has up to 23 reflected resource bindings per shader and is a separate PBR pipeline. `RenderChunkPrepass.material.bin` has depth/prepass-specific shader pairs. Neither should inherit the simple terrain shader.

## Gaps before a closer match

1. **Current-game terrain variants:** decode and implement the fade/dither families, TextureShift material mapping, translucent water/glass, and any other replacement-appropriate variants. Keep depth-only behavior native unless there is a measured benefit and a signature-safe implementation.
2. **Lighting:** the current approximation uses a fixed block-light multiplier and samples a day proxy. LCE `GameRenderer::updateLightTexture` also handles time-varying sky darkening, block-light flicker, lightning, End-specific channel handling, night vision, and gamma. LCE dimensions provide different ambient ramps, including the Nether ramp. These conditions need explicit game-state inputs or a captured game light table; they cannot be inferred exactly from one proxy texel.
3. **Fog:** the replacement's simplified distance/far-plane handling does not reproduce LCE `GameRenderer::setupFog` modes and environment-specific fog colors/ranges (including water, lava, cloud, and dimension cases).
4. **Biome and material tint:** LCE obtains grass, foliage, water, sky, and other colors from `ColourTable`/biome data. The current pass relies on Bedrock's supplied vertex colors and does not reproduce LCE color tables or biome tint rules.
5. **Texture sampling:** the crisp option forces base-level sampling broadly, which can improve distant terrain but look subtle up close when a texture pack or atlas already has sharp texels. LCE selectively enables mipmaps per tile and forces LOD 0 for cutout draws. Preserve resource-pack atlases and implement sampling behavior per material/tile policy rather than replacing user textures.
6. **Other render passes:** water surface/animation, clouds, weather, particles, sky bodies, held items, entities, and first-person effects each need separate comparison with the corresponding LCE renderer paths. Actor replacements remain intentionally excluded pending a safe, isolated design.
7. **Geometry and assets:** Bedrock RenderDragon vertex data, chunk meshing, and resource assets differ from the LCE renderer. Pixel-identical output may require matching mesh inputs and pass ordering as well as shaders; shaders alone cannot guarantee it.
8. **Validation coverage:** validate each supported pipeline in Overworld, Nether, End, water/lava, weather, resource packs, inventory/pause screens, and debug modes; capture comparable reference/game screenshots and record which material hashes actually bind.

## Reference locations

- `src/sdk/lce/reference/Minecraft.Client/GameRenderer.cpp`: `updateLightTexture`, `setupFog`, sky/cloud/entity rendering.
- `src/sdk/lce/reference/Minecraft.World/Dimension.cpp`: dimension light ramps and fog colors.
- `src/sdk/lce/reference/Minecraft.Client/LevelRenderer.cpp` and `TileRenderer.cpp`: pass ordering, cutout LOD and per-tile mipmap policy.
- `src/sdk/lce/reference/Minecraft.World/Biome.cpp` and `Minecraft.Client/Common/Colours/ColourTable.*`: biome and color-table behavior.
- `src/client/features/render/lce/`: active LCE replacement implementation.
- `tools/lce/map_material.py`: reproducible material map generation using the Windows SDK `dxc.exe`; the generated full 1.26.51.01 map is kept under ignored `build/` output.

## Safe implementation order

First verify that the rolled-back baseline creates PSOs and that debug views work. Then inspect each current material's bytecode signature and bindings; implement one variant at a time without changing the original vertex interface, and confirm successful PSO creation before enabling it by default. Add lighting/fog/color behavior as isolated shader changes with a comparison capture per case. Expand other render roles only behind explicit role classification and live checks that cover UI/inventory actors. Keep performance measurement separate from visual validation.

## Material map tool

The installed 1.26.51.01 directory contains 157 material files and 5,136 unique shader hashes. The generated full DXIL-disassembled map is `build/lce-material-map-1.26.51.json`; it is a build output and is not checked into the source tree. A smaller quick inventory and prior world subset may also exist in `build/`.

Run `python tools/lce/map_material.py --output build/lce-material-map.json --dxc <Windows-SDK-dxc.exe> <game>/data/renderer/materials` to inventory every material and disassemble DXIL. The report includes shader stages, input/output semantics and component masks, texture/sampler/cbuffer bindings, operation summaries, and adjacent VS-to-PS pairs where the binary order and DXC stage agree. Use material ownership and shader pair data as the source of truth before adding a replacement family.
