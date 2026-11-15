# Dossier: the six FrameBuilder group inserts and their visitors (1.26.62.01)

Static. Found from the BgfxFrameBuilder vtable (rva 0xF2BDEB0; endFrame at slot 18 = 0x66232b0 is the anchor), slots 107..112. Each slot is a 0x214..0x28E-byte wrapper that opens the profiler zone named by its string and calls one visitor; each visitor switches on the variant tag (`u8` at variant+8) through a jump table. Tags: [V] read, [I] inferred, [?] open.

## Reversed wrapper (one body, six copies)

```cpp
void BgfxFrameBuilder::insertGroup(const Variant* v) {        // slot 107..112
    ProfileScope scope("FrameBuilder - Insert <group>");      // string per group, TLS-guarded like the clones
    visitGroup(this, &this->frameCtx, v);                     // the group's visitor below (Sky's wrapper also calls 0x1166e0)
}
```

## Table

| slot | offset | wrapper | zone string | visitor | cases | jump table rva |
|---|---|---|---|---|---|---|
| 107 | 0x358 | 0x6674050 | "FrameBuilder - Insert editor" | 0x66742f0 | 8 | 0xF2BF520 |
| 108 | 0x360 | 0x666aa00 | "FrameBuilder - Insert effect" | 0x666aca0 | 9 | 0xF2BF49C |
| 109 | 0x368 | 0x6664760 | "FrameBuilder - Insert UI" | 0x6664a00 | 5 | 0xF2BF468 |
| 110 | 0x370 | 0x6655de0 | "FrameBuilder - Insert sky" | 0x66560f0 | 11 | 0xF2BF39C |
| 111 | 0x378 | 0x66466e0 | "FrameBuilder - Insert item" | 0x6646980 | 11 | 0xF2BF2D0 |
| 112 | 0x380 | 0x6640ae0 | "FrameBuilder - Insert light" | 0x6640d80 | 8 | 0xF2BF2B0 |

The case counts match the variant lists of 6g for Effect (9), UI (5), Sky (11) and Item (11); Light has 8 cases but 6g lists 7 names (one variant unnamed [?]); Editor has 8 [?names].

## Case entry points per tag

- Editor 0x66742f0: 0 0x6674388, 1 0x667499f, 2 0x6674518, 3 0x667463c, 4 0x66743f4, 5 0x6674ac3, 6 0x6674d02, 7 0x6674760
- Effect 0x666aca0 (FlameBillboard, BlitFlipbook, Particle, PlayerVision, Shadow, FadeToBlack, AimAssistHighlight, FullscreenEffect, EditorHighlight): 0x666ad04, 0x666aec2, 0x666ad88, 0x666adbf, 0x666ad3b, 0x666afde, 0x666b143, 0x666ae72, 0x666b316
- UI 0x6664a00 (Gameface, HudIcon, UIMesh, UIText, UIImGui): 0x6664a6c, 0x6664d51, 0x6664bd6, 0x6664c83, 0x6664aab
- Sky 0x66560f0 (Atmosphere, Clouds, Cubemap, EndSky, LegacyCubemap, Sky, Stars, CelestialBody, VolumetricFog, Weather, SkyAmbientSamples): 0x6656174, 0x6656697, 0x66562d5, 0x665649c, 0x66561cc, 0x66566ee, 0x6656812, 0x6656516, 0x66569b1, 0x665627e, 0x6656983
- Item 0x6646980: see docs/functions/6646980.md (tags 3, 6, 8, 10 tail-jump to dedicated extractors)
- Light 0x6640d80 (LightAmbient, LightDirectional, LightPoint, GameplayMetadata, ShadowAtlasFrame, ServerGraphicsOverride, VoxelVolume, +1): 0x6640de8, 0x66415b0, 0x6640f1b, 0x66410a0, 0x6640ec1, 0x66417af, 0x664187d, 0x6641524

The UIText case (UI tag 3 = 0x6664c83) and PlayerVision case (Effect tag 3 = 0x666adbf) consume the descriptions typed in Descriptions.h (6gd, 6fw); Sky tags 1, 5, 6 consume Clouds, Sky and Stars (6gb, 6gf).

## Version-stable re-find

Anchor on the zone strings ("FrameBuilder - Insert <group>"): each is referenced only by its wrapper; the wrapper's single non-profiler call is the visitor, and the visitor's `cmp eax, N-1` + `lea` is its jump table.

## Verification

Static. Wrapper shape read for all six; visitor dispatch read for all six (table entries dumped). Case bodies other than Item's dedicated extractors are not transcribed [?]. Status D2 for the wrappers and dispatch.

## Two case bodies read (static, 62.01) [V]

**Effect tag 3, PlayerVision (0x666adbf):** queues, it does not draw.
```cpp
    const RenderPlayerVisionDescription& d = *v->desc;
    PassObject* pass = passLookup(frameCtx->ptr10 + 0x9D0);                 // 0x5aba5c0 (the pass/module lookup)
    (zero a 0xC0-byte local; allocator query with type id 0x4A)
    pass->playerVision.push_back(d);                                       // std::vector<0x14-byte element> at pass+0x330 (begin) / +0x338 (end) / +0x340 (cap)
                                                                           // element = { u8 +0x00, 16 bytes +0x04 } = the whole description
```
So the Effect visitor hands descriptions to the render pass that owns them; the pass consumes its vector when its frame-graph task runs.

**UI tag 3, UIText (0x6664c83):** draws immediately through the UI text renderer 0x674a3a0 ("UI/Text", "UI/Glint" materials), passing the description's fields one by one: `src = d+0x00`, `d+0x08`, `&d.texture (+0x10)`, `d+0x20`, `d+0x28`, `d+0x30`, `&d.flags (+0x38)`, `d.byte3A`, `&d.variant (+0x40)`, plus constants (1, a 16-byte default colour, 1.0f, zeros). Every offset used matches RenderUITextDescription in Descriptions.h, which independently confirms that struct.

## Correction: the visitor's second argument is the frame context, not the description

In every visitor `rdx` is the frame context and the description is `[r8]` (kept in `rdi`/`r15`). The Sky tag 5 case reads `frameCtx+0x40` and `+0x68` (the same frame-context fields the Item visitor reads), which is why its offsets did not match RenderSkyDescription.

## First real callee of every case (dedicated extractors are tail jumps) [V]

| group | per tag: first non-helper callee (`jmp` = tail jump to a dedicated extractor) |
|---|---|
| Editor | 0 jmp 0x66a1860 (EditorBlockVolumeWireframe), 1-4 material resolver 0x675e440, 5-7 0xaa6580 |
| Effect | 0 jmp 0x673d150 (FlameBillboard / ActorPrepass), 1 0x675e440 (BlitFlipbook), 2 jmp 0x67417f0 (Particle), 3 pass lookup 0x5aba5c0 (PlayerVision: queue, 6gi), 4 0x66a9d50 (Shadow), 5 0x67d6d70 (FadeToBlack), 6 0xaa6580 (AimAssistHighlight), 7 0x66b2b30 (FullscreenEffect: registry emplace), 8 0x5aba5c0 (EditorHighlight) |
| UI | 0 jmp 0x66ade80 (Gameface/Renoir), 1 0x675e440 (HudIcon), 2 inline (UIMesh), 3 the UI renderer 0x674a3a0 (UIText), 4 0x675e440 (UIImGui) |
| Sky | 0 inline (Atmosphere: reads desc +0x00 u16, +0xA4..+0xD3 three 16-byte blocks, +0xE0 pointer), 1 jmp 0x67375a0 (Clouds), 2 0x67d6d70, 3 inline, 4 inline, 5, 6, 7 0x675e440, 8 0x5aba5c0, **9 jmp 0x6745440 (Weather)**, 10 inline |
| Light | 0, 1, 2, 3, 6 pass lookup 0x5aba5c0 (queued like PlayerVision), 4 inline, 5 0x67b6300, 7 inline |

Scan method (6gn): every case is scanned only up to the next case's entry address (or the end of the visitor), so a case that falls through into a neighbour is reported as "inline". The first version of this table scanned a fixed 0x260 bytes and over-reported for UI 2, Sky 0, 3, 4, 10 and Light 3, 4, 7.

Names in parentheses follow each group's variant order and agree with the extractor strings where one exists (Clouds, Particle, Gameface, FlameBillboard, UI). Correction (6gm): the first version of this row said Sky tags 0, 4 and 9 all jump to 0x6745440. Only tag 9 does (its case is a bare tail jump at 0x665627e -> 0x66562d0); the scan for cases 0 and 4 ran past their own code into case 9's body. So the Sky variant order holds: tag 9 = Weather, handled by the "Weather"/"WeatherForwardPBR" renderer. Light cases are almost all queue operations: lights are collected per pass and consumed by the lighting passes.
