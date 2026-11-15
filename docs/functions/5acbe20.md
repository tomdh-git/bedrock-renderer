# Dossier: 0x5acbe20 - Effect BlitFlipbook thin insert clone (1.26.62.01)

Static analysis only. Target exe: `C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe`. Tags `[V]` verified from disassembly/rdis, `[I]` inferred, `[?]` unknown.

## Identity / role [V]
- Function: `sub_5acbe20` (`0x5acbe20..0x5acbf59`, 0x139 bytes, `.pdata` extent).
- Thin `FrameBuilder::insert<RenderBlitFlipbookDescription>` clone for Effect group, **tag 1 (BlitFlipbook)**.
- Same body shape as the 21 thin clones documented in `docs/functions/insert_thin_clones.md` / `docs/data/frame_path_functions.tsv` (D2 root).

Evidence:
- `rdis sum 0x5acbe20`: TLS/profile scope setup (`sub_39a7d40`, guard/init paths), builds variant on stack as `{desc_ptr, tag}` and stores `tag = 0x1` at `0x5acbe94` (`&stk-0x118 <- 0x1`) with desc pointer at `&stk-0x120 <- a1` (`@0x5acbe90`).
- Dispatches through builder vtbl slot **+0x360 / index 108**: loads `*(a0)` then `(*(a0)+0x360)` and performs indirect call `vcall obj=a0 slot=108` with `(a0, &variant)` (`@0x5acbe98..0x5acbea9`).
- Matches group visitor mapping in `docs/functions/group_visitors.md`: slot 108 / offset 0x360 = Effect insert wrapper `0x666aa00` -> visitor `0x666aca0`, case tag 1 = BlitFlipbook (`0x666aec2`).

## Signature [V/I]
```cpp
// [V] call shape from rdis sum: (a0=rcx builder/framebuilder impl, a1=rdx description*)
void insertBlitFlipbook(/*BgfxFrameBuilder*/ void* builder, const RenderBlitFlipbookDescription* desc); // [I] typed name
```
- Does **not** read description contents [V]; only passes description pointer in `{ptr, u8 tag}` variant to group insert virtual.

## Description/layout consumed (by pointer only) [V]
- Description object passed as `a1` is the stack-built `RenderBlitFlipbookDescription` from producer `0x5aca680` (see `docs/functions/5aca680.md`).
- Verified description layout at 1.26.62.01: **0x20 bytes** `{ SharedRef mRef00 @+0x00; u64 mCount @+0x10; Element* mElements @+0x18; }` (size contradicts older 0xA0 claims; see progress report).
- Element stride 0x40, copied by `0x5acb9c0` (see `docs/functions/5acb9c0.md`) and consumed by Effect visitor case 1 / shared tail (see `docs/functions/666aca0_blitflipbook.md`).

## Control flow notes [V]
- Standard profiler scope enter/leave with TLS once-init pattern (globals `data_129cfd68`, TLS index `data_128767c8`).
- Calls include `sub_39a7d40`, `sub_77a2500` (profiler leave path), lazy registration/error helpers `sub_e938cb0`, `sub_2fe330`, `sub_e935740`, `sub_e938d70`.

## Verification
- [V] rdis `sum 0x5acbe20` (static).
- [V] Cross-check with `docs/functions/insert_thin_clones.md` row for `0x5acbe20` (Effect tag 1 BlitFlipbook).
- [V] Cross-check with `docs/functions/group_visitors.md` Effect slot/case mapping.

## Open
- None for this thin clone body; description semantics live in producer/consumer dossiers. [?] none.
