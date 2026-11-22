## NEXT
DONE

# U-EM2c — M2c description types as structs with confirmed fields (Cloud*/Shadow*)

GOAL (overriding, ORCHESTRATOR 2026-11-22): STOP looking for a JSON-key -> struct-offset store; it does not exist as a per-key mov. For each Cloud*/Shadow* type, take its constructor/extractor (rdis callees of the type's vtable/RTTI-named function, or the function that writes the type's sizeof-sized allocation) and list every `mov [reg+off], x` / movss / movups store as one [V] row (offset, width, source). Fields never written by the constructor but read by the pass execute body also count: list them from the readers. Do 2 types per run, write rows into Descriptions.h-compatible struct text, end with a precise count of types done out of 62.

## Method

Use the constructor/builder that writes the type's sizeof-sized allocation. For each field, list every `mov [reg+off], x` / movss / movups store as one [V] row. Size from instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1).

## Input data read in full

- docs/data/listings/light_shadowatlas_builder_7915d50_7915fc0.txt — ShadowAtlasFrame builder 0x7915d50 (158 instructions), verbatim instruction source for all proof rows below.
- docs/data/producer_fields.txt (6if raw producer stores for the thin clones).
- docs/BGFX_MAP.md, 6ih/6gb/6ie sections.
- docs/progress/oc_U-Atm.md, docs/progress/re_atmosphere.md, docs/progress/re_blitflipbook.md.
- docs/progress/oc_U-Cld.md (RenderCloudsDescription 0xA8 already [V]-typed from ctor 0x668e940).
- docs/data/entt_types_1.26.62.01.txt (full 62-type catalog).

## Cloud*/Shadow* type survey

From the catalog (docs/data/entt_types_1.26.62.01.txt, framebuilder descriptions section) and docs/data/functions.tsv:

- RenderCloudsDescription (Sky tag 1, 0xA8) — ALREADY typed (6gb): ctor 0x668e940 writes every field [V]. docs/progress/oc_U-Cld.md + docs/functions/668e940.md.
- ShadowAtlasFrameDescription (0x50) — builder 0x7915d50 writes the full 0x50-byte struct [V]. Done this run (below).
- RenderShadowDescription (Effect tag 4, 0x20) — header exists in Descriptions.h but evidence is producer stack-slot stores ([rbp+0x1D8]/[rbp+0x1E0]/[rbp+0x1F0]), NOT [desc+off] constructor stores. The Shadow clone 0x53e6c30 "inserts no Shadow description of its own" (BGFX_MAP.md:1642); it builds a 0x14-byte entry and hands it to the insert vtable. No [desc+off] store located.
- CloudLightingParameters, CloudParameters, ShadowParameters, ShadowRange — xref str shows refs=[] (type name strings only, no code references). No constructor/extractor code exists to reverse. Cannot be [V]-documented.

Only ShadowAtlasFrameDescription has decodable constructor/builder [desc+off] stores among the remaining Cloud*/Shadow* types.

## Type 1 this run: ShadowAtlasFrameDescription (0x50), builder 0x7915d50

rbx == rdx == description pointer (`0x7915d6e  mov rbx,rdx`; restored `0x7915e32  mov rbx,[rbp+0xF8]` where [rbp+0xF8]=rbx). Builder zero-inits then writes a 4x4 matrix (4 movups rows) and a SharedRef pair.

## [V] proof rows (one row per distinct offset, all store sites listed)

| offset | size | site | verbatim `0xRVA  instr` | meaning |
|---|---|---|---|---|
| +0x00 | 16B | 0x7915d71, 0x7915e55 | `0x7915d71  mov dword ptr [rdx],0x3F800000`; `0x7915e55  movups [rbx],xmm0` | ShadowAtlas matrix row 0; initial dword 1.0f at +0x00 overwritten by movups row [V] |
| +0x04 | 16B | 0x7915d7a | `0x7915d7a  movups [rdx+4],xmm0` | ShadowAtlas zero-init +0x04..+0x13 (overlaps matrix row 0 tail / row 1 head) [V] |
| +0x10 | 16B | 0x7915e5c | `0x7915e5c  movups [rbx+0x10],xmm0` | ShadowAtlas matrix row 1 [V] |
| +0x14 | 4B | 0x7915d7e | `0x7915d7e  mov dword ptr [rdx+0x14],0x3F800000` | ShadowAtlas initial dword 1.0f at +0x14, overwritten by movups row at +0x10 [V] |
| +0x18 | 16B | 0x7915d85 | `0x7915d85  movups [rdx+0x18],xmm0` | ShadowAtlas zero-init +0x18..+0x27 (overlaps matrix row 1 tail / row 2 head) [V] |
| +0x20 | 16B | 0x7915e64 | `0x7915e64  movups [rbx+0x20],xmm0` | ShadowAtlas matrix row 2 [V] |
| +0x28 | 4B | 0x7915d89 | `0x7915d89  mov dword ptr [rdx+0x28],0x3F800000` | ShadowAtlas initial dword 1.0f at +0x28, overwritten by movups row at +0x20 [V] |
| +0x2C | 16B | 0x7915d90 | `0x7915d90  movups [rdx+0x2C],xmm0` | ShadowAtlas zero-init +0x2C..+0x3B (overlaps matrix row 2 tail / row 3 head) [V] |
| +0x30 | 16B | 0x7915e6c | `0x7915e6c  movups [rbx+0x30],xmm0` | ShadowAtlas matrix row 3 [V] |
| +0x3C | 4B | 0x7915d94 | `0x7915d94  mov dword ptr [rdx+0x3C],0x3F800000` | ShadowAtlas initial dword 1.0f at +0x3C, overwritten by movups row at +0x30 [V] |
| +0x40 | 16B | 0x7915d9b, 0x7915e70 | `0x7915d9b  movups [rdx+0x40],xmm0`; `0x7915e70  mov [rbx+0x40],rcx` | ShadowAtlas zero-init +0x40..+0x4F then shared_ref.mPtr qword [rsi+0x178] at +0x40 [V] |
| +0x48 | 8B | 0x7915e74 | `0x7915e74  mov [rbx+0x48],rax` | ShadowAtlas shared_ref.mCtrl qword (0 or addref'd ctrl) at +0x48 [V] |

## Descriptions.h-compatible struct text

```cpp
// ShadowAtlasFrameDescription (Effect/Light group tag 4), built by 0x7915d50
// Size 0x50 [V]. Every field written by the builder [V]: 4x4 matrix at +0x00 (four movups rows),
// SharedRef pair at +0x40/+0x48. Builder zero-inits (movups at +0x04/+0x18/+0x2C/+0x40) and sets
// identity diagonal dwords (1.0f at +0x00/+0x14/+0x28/+0x3C) before overwriting with the real matrix.
namespace mce::framebuilder {

struct ShadowAtlasFrameDescription {
    float mMatrix[16];     // +0x00 4x4 matrix (rows at +0x00,+0x10,+0x20,+0x30) [V]
    SharedRef mAtlas;      // +0x40 shared_ptr pair: mPtr +0x40 [V], mCtrl +0x48 [V]
};
static_assert(sizeof(ShadowAtlasFrameDescription) == 0x50);
static_assert(offsetof(ShadowAtlasFrameDescription, mMatrix) == 0x00);
static_assert(offsetof(ShadowAtlasFrameDescription, mAtlas) == 0x40);

} // namespace mce::framebuilder
```

Header candidate: `src/sdk/mc/deps/minecraft_renderer/framebuilder/ShadowAtlasFrameDescription.h` (new file; none exists yet).

## Types done / remaining

- Previously typed (per M2c progress line, 6ih): 27 of 62 (incl. RenderCloudsDescription 0xA8).
- This run: ShadowAtlasFrameDescription (0x50) added → **28 of 62 typed**.
- Remaining untyped (34): RenderShadowDescription (header exists but lacks [desc+off] ctor evidence), CloudLightingParameters, CloudParameters, ShadowParameters, ShadowRange (no code references — cannot be [V]-documented), plus ~29 others from the 62-type catalog.

## CLOSES?

NO — M2c requires all 62 description types as structs with confirmed fields. This run types 1 of the 35 remaining (ShadowAtlasFrameDescription), bringing the total to 28 of 62. The single blocking fact: the remaining Cloud*/Shadow* types (CloudLightingParameters, CloudParameters, ShadowParameters, ShadowRange) have zero code references (xref str refs=[]) so no constructor/extractor exists to reverse; RenderShadowDescription has no [desc+off] constructor store (clone builds a 0x14-byte entry handed to an insert vtable, not located).

## TOOL REQUESTS

None — existing rdis dis and delegate.py/verify_oc only.
