# OffsetProvider port to 1.26.62.01: what is proven and what is open

Target: `C:\Users\Atomi\AppData\Roaming\levilauncher.exe\versions\1.26.62.01\Minecraft.Windows.exe` - 323,823,440 bytes, TimeDateStamp 6AEA437E (2026-11-03T20:26:38Z), the game reports itself as 1.26.62.1.

**Verdict: a pure code-relocation patch.** Every OffsetProvider value was re-proven unchanged - zero value edits. Update-day audit: 48/48 sigs LIVE, 0 dead (BobHurt runs on its second pattern; its first pattern died in 1.26.60 already). `tools/sigs/sigs.py`: ok. `tools/check.py`: 68 violations, all pre-existing in the 1.26.60 tree (layers=4, length=63, namespaces=1 - no regressions; a 69th pre-existing includes violation was auto-fixed by check.py's include hoist during the build, which moved Fly.h's `#include <memory>` into Pch.h). LeviLamina is still not updated to 1.26.62, so `src/sdk/GeneratedCheck.cpp` was NOT regenerated - everything below comes from pure reversing of the 1.26.60.05 and 1.26.62.01 exes.

## Method (same as the 1.26.60 port; the scripts are now committed)

1. No RTTI for game classes: a vtable start is the `lea reg,[rip+X]` target (constructors store it) that lies on a run of `.text` pointers in `.rdata`, anchored by sig'd functions that sit in the vtable (`grabMouse`/`releaseMouse` -> ClientInstance, `MultiPlayerLevel::_subTick` -> Level, `getHideHand` -> Options, the slot-76 `mov rax,[rcx+0x228]` getter -> MinecraftGame, ...).
2. Slots aligned old -> new with `tools/sigs/valign.py` (NEW in this update): it dumps up to N slots from each vtable, disassembles each target's first ~64 instructions in both binaries and aligns the two sequences with difflib.SequenceMatcher over displacement-normalized shape signatures ((mnemonic, operand kinds), every displacement/immediate zeroed). Verdict per aligned pair: SAME / SHIFTED / CHANGED. Tiny getters (<= 4 instructions containing a non-rip memory displacement, e.g. `mov rax,[rcx+0x1e0]`) additionally diff their raw displacements - a moved struct member shows up as a moved-member row with both instruction texts.
   `python tools/sigs/valign.py --old-exe <exe> --new-exe <exe> --old-vt <rva hex> --new-vt <rva hex> --count N [--json [path]]`
3. The .pdata trap: tiny leaf getters have no unwind info, so they have no .pdata entry - the function end must be found by disassembling to the next known start and stopping at the first ret. valign.py handles this in its `disasm` (window capped, stop at ret); without it, tiny-getter windows bleed into the following function and the alignment drowns in false CHANGED rows.
4. Larger functions were compared as dis-pairs (instruction-mnemonic shape, similarity ratio) with `tools/sigs/xref.py dis/callers/vt`; every proof below is such a pair with identical instruction counts unless stated otherwise.

## Tools

- `tools/sigs/xref.py` (existing): read-only str/dis/callers/strs/tree/sig/vt/ptr queries over the exe (`BS_EXE` selects the binary).
- `tools/sigs/valign.py` (new, committed with this update): vtable alignment + member-displacement diff as above; `--json [path]` writes the machine-readable report (per-slot rows plus same/shifted/changed/moved/old-only/new-only counts).
- Update-day dashboard: `python tools/update_day.py` folds the exe identity, `audit.py` (sig liveness), `sigs.py` and `check.py` into one read-only report.

## Regional RVA deltas

Code moved in blocks; everything inside a block moved by the same amount:

| Delta | Functions |
|---|---|
| +0xC00 | the ClientInstance group |
| +0x7C0 | the Options group |
| +0x370 | ItemInHand, camera, projection, BobHurt, applyOnExit, bindingA |
| +0x1D0 | setupAndRender |
| -0x20 | the MinecraftGame `_update` cluster |
| -0x140 | getGamertag, simulateJump, composeFullStack, setStack |
| +0x10 | getNameTag, canSee, getFeetAttachPos |

Vtable starts moved with their region, +0xFE0..+0x1000.

## Vtable starts (1.26.60.05 -> 1.26.62.01)

| Vtable | old | new |
|---|---|---|
| ClientInstance | 0xF2B9330 | 0xF2BA330 |
| Level | 0xF2CE790 | 0xF2CF790 |
| Options (+ secondary) | 0xF2760B0 (0xF276F30) | 0xF2770B0 (0xF277F30) |
| UserImpl (+ secondary) | 0xF0C0860 (0xEFCBB70) | 0xF0C1840 (0xEFCCB70) |
| Actor base (174 slots) | 0xF28DD00 | 0xF28ED00 |
| Mob-class (246) | 0xEFF7DD0 | 0xEFF8DD0 |
| len-252 | 0xF0C4820 | 0xF0C5800 |
| Player-class (293) | 0xF0C5050 | 0xF0C6030 |
| len-451 | 0xF164D70 | 0xF165D60 |
| MinecraftGame | 0xF091B70 | 0xF092B50 |
| BlockSource | 0xF188A20 | 0xF189A10 |
| GameMode | 0xF1A8E90 | 0xF1A9E80 |
| FrameBuilder | 0xF2BCE70 | 0xF2BDE70 |
| controller sub-vtables | 0xF22F9D0 / 0xF22FCF0 | 0xF2309D0 / 0xF230CF0 |

## Alignment results

valign.py over all vtables above: ClientInstance 340/340, Level 419/419, Options 140/140, UserImpl 60/60, MinecraftGame 120/120, BlockSource 40/40, GameMode 40/40 - **0 SHIFTED, 0 CHANGED, 0 inserted, 0 deleted anywhere**. Actor family: the 5 base vtables aligned 120/120 slots each; the 41 member vtables cluster 1:1 via slot 13. 176 tiny getters byte-identical; a full displacement sweep across the two largest Actor vtables (451 + 293 slot pairs) found 0 diffs. No OffsetProvider value changed.

## Re-proof evidence (the interesting ones)

| Entry | Proof (old -> new; dis-pairs ratio 1.0) |
|---|---|
| ResourcePackManager 0x130 / 0x138 / 0x58 / 0x179 / 0x17A (+ listeners 0xF8, mInitializing 0x178, mutex 0x180) | composeFullStack / setStack dis-pairs; identical loads at the aligned places |
| ScreenView 0x40 / 0x50 + the UIControl/VisualTree flags | setupAndRender (+0x1D0) reads [this+0x40]/[this+0x50] and makes the controller vtable calls (+0x10/+0x18) at the same aligned places |
| GeneralSettingsScreenController 0xD61 | applyOnExit keeps `cmp byte [rsi+0xD61],1` |
| Option_mValue 0x18 | getGamma body keeps `movss xmm0,[rax+0x18]` |
| MinecraftGame mPackManager 0x228 | vtable slot 76 tiny getter `mov rax,[rcx+0x228]` (getter 0x8bc9e0 -> 0x8bc9c0; vtable 0xF091B70 -> 0xF092B50) |
| MinecraftGame mMouseGrabbed 0x1F8 | slot 99 tiny getter + the same cmp in the `_update` cluster |
| MinecraftGame mClientMap 0x9D0 | slots 47/52 |
| LevelRendererPlayer mCameraPos 0x9C4 | camera fn 0x5340b70 -> 0x5340ee0 keeps `movss xmm2,[r8+0x9C4]` |
| LevelRendererPlayer mFovX / mProjection 0xF50 + mFovY 0xF64 | projection fn 0x53b3290 -> 0x53b3600 |
| LevelRenderer_mRendererPlayer 0x480 | chain fn 0x65b13d0 -> 0x65b1fd0: `mov rax,[rcx+0x1E0]; mov rax,[rax+0x480]; mov rax,[rax+0xA70]` |
| GameCore_mPlatform 0x8 / Platform_mGameHolder 0x118 / GameHolder_mMinecraftGame 0x48 | chain fn 0xae3a0 (unchanged): `mov rax,[rdi+8]; mov rcx,[rdi+0x118]; mov rcx,[rcx+0x48]` |
| bgfx mCommandQueue 0xCC9268 | `mov rdx,[rcx+0xCC9268]` at the sig site 0xe816dec -> 0xe8179ec |
| BlockSource getBlock (slot 2) | shape-identical |
| GameMode slots 1/2/3/4/15 | shape-identical |
| ScreenController vHandleEvent 3 | primary vtable NOT-REACHABLE (no RTTI); the slot is carried over and its use sites are shape-identical |
| Container / PlayerInventory [rcx+0xB8] | the forwarding-vtable pattern is unchanged; class attribution NOT-REACHABLE |

## BobHurt

Pattern 0 is dead in BOTH 1.26.60 and 1.26.62. Pattern 1 has exactly one match per exe: 0x53a0fb0 -> 0x53a1320 (+0x370, the ItemInHand/camera region), same function - 157/157 instructions, ratio 1.0 - and its single caller moved 0x4e0de00 -> 0x4e0df90. An earlier 0x856fee0 audit lead was NOT a pattern match (a dead lead). The sig itself is unchanged.

## FrameBuilder insert

The game-side insert offset is 0x370 in BOTH builds: the insert thunk sits at FrameBuilder vtable byte offset 0x370 (slot 110), slot 118 is the sig'd `_insert`, and slot 106 (the 1.26.51 insert slot at byte offset 0x350) is now a flag-reader. `kFfSlotOffset` stays 0x370 (`FrameFilterHook.h`); the hook's scan finds 2852 identical sites per exe.

## Not re-provable (values carried over)

All three blocked by the stripped RTTI; each is backed by relocation evidence and shape-identical access patterns:

- LevelRenderer vtable start - no RTTI and no anchor function; the mRendererPlayer chain (above) is the indirect evidence.
- ScreenController primary vtable start - NOT-REACHABLE; vHandleEvent slot 3 carried over.
- Container class attribution - the [rcx+0xB8] forwarding-vtable pattern is unchanged, but the class cannot be named; NOT-REACHABLE.

## The one runtime-visible address change

The GameCore::instance global moved 0x128BEF90 -> 0x128C0F90; its sig resolves it automatically on both builds. Everything else the mod touches follows the sigs and vtables.
