# Dossier: the 21 thin `FrameBuilder::insert<Description>` clones (1.26.62.01)

Fully reversed: all 21 are the same 0x139-byte function stamped out by the compiler; only the variant tag byte, the group slot and the RIP-relative displacements of the profiler statics differ. Found by searching the whole .text for the shared code shape (see "How to re-find" below), so the list is complete for this shape. Tags: [V] read, [I] inferred, [?] open.

## Reversed source (complete, one body for all 21)

```cpp
// rcx = BgfxFrameBuilder* (the IFrameBuilder implementation), rdx = const Description* (lives on the caller's stack)
void FrameBuilder::insert(const Description* desc) {
    ProfileScope scope;                                     // TLS-guarded profiler zone: 0x39a7d40 enter, 0x77a2500 leave,
                                                            // lazy registration 0xe938cb0 / 0x2fe330 / 0xe938d70 on first use (0x15-char name)
    struct { const Description* desc; uint8_t tag; } variant = { desc, kTag };    // rbp+0x10 / rbp+0x18
    this->vtbl[kGroupSlot / 8](this, &variant);             // _insert for the group: Editor 0x358, Effect 0x360, UI 0x368, Sky 0x370, Item 0x378, Light 0x380
}
```
Nothing in a thin clone reads the description: it is passed by pointer as the first member of a `{ptr, u8 tag}` variant (the std::variant-like argument the group visitors switch on). That is why ExtractionObserver (src/client/features/hooks/hooks/render/ExtractionObserver.h) reads the variant as `{desc* +0, tag u32 +8}`.

## All 21 clones

| clone rva | group | tag | description (name by the group's variant order, BGFX_MAP 6g) |
|---|---|---|---|
| 0x6c956b0 | Editor | 0 | editor variant 0 [?] |
| 0x4c85d70 | Editor | 1 | editor variant 1 [?] |
| 0x4c85f30 | Editor | 2 | editor variant 2 [?] |
| 0x4c860f0 | Editor | 3 | editor variant 3 [?] |
| 0x4c862b0 | Editor | 4 | editor variant 4 [?] |
| 0x5371160 | Editor | 5 | editor variant 5 [?] |
| 0x6c961e0 | Editor | 6 | editor variant 6 [?] |
| 0x5acbe20 | Effect | 1 | BlitFlipbook |
| 0x5b8d520 | Effect | 2 | Particle |
| 0x5370e80 | Effect | 6 | AimAssistHighlight |
| 0x4c8a5b0 | Effect | 8 | EditorHighlight |
| 0x4c96140 | UI | 2 | UIMesh |
| 0x660b720 | Sky | 2 | Cubemap |
| 0x53707a0 | Sky | 3 | EndSky |
| 0x5370b20 | Sky | 7 | CelestialBody |
| 0x5ad5800 | Sky | 9 | Weather |
| 0x15a6880 | Item | 3 | ChunkGeometry |
| 0x5369920 | Item | 4 | ChunkOccluders |
| 0x531b180 | Item | 6 | ItemInHand |
| 0x4e39cb0 | Item | 10 | BatchActor |
| 0x5370960 | Light | 1 | LightDirectional |

The names for Effect, UI, Sky, Item and Light come from the variant order of each group (LeviLamina-derived, the Item order was confirmed by its 11-entry jump table); they agree with every clone that earlier notes identified independently (ChunkGeometry 0x15a6880, ChunkOccluders 0x5369920, ItemInHand 0x531b180, BatchActor 0x4e39cb0, Cubemap 0x660b720, EndSky 0x53707a0, CelestialBody 0x5370b20, UIMesh 0x4c96140, Particle 0x5b8d520, LightDirectional 0x5370960). The Editor variants have no confirmed names [?].
The other description types use "fat" clones that build the description in the clone (Nametag 0x1127330, Crack 0x539fff0, SkinnedMesh 0x6b84e60 / 0x4e39f20, ...); those are separate dossiers.

## How to re-find (version-stable)

The shape is `mov [rbp+0x10], rdi; mov byte [rbp+0x18], TAG; mov rax, [rsi]; mov rax, [rax+SLOT]; lea rdx, [rbp+0x10]; mov rcx, rsi; call [rip+...]`, bytes:
`48 89 7D 10 C6 45 18 ?? 48 8B 06 48 8B 80 ?? ?? 00 00 48 8D 55 10 48 89 F1 FF 15`. On 1.26.62.01 it matches exactly 21 times, all inside 0x139-byte functions. The tag is the byte after `C6 45 18`, the group slot the u32 after `48 8B 80`.

## Verification

Static, instruction-complete for the shared body (read twice, at 0x531b180 and 0x5369920; the other 19 matched by the byte shape and have the same size). Earlier live work hooked several of these clones (6c, 6dx) and saw the predicted variant tags. Status D2 for all 21.
