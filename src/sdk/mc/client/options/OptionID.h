#pragma once
// OptionID is `enum class OptionID : int {};` — no numerics baked in
// (contrast FeatureOptionID.h 0-65).
// ids are runtime registration indices passed as small-int key to
// IOptionsReader::get (vtable idx 1): `mov r8d,key; call [get]`.
// live-grounded 1.26.51 gdk 6764: gfx_gamma string 0x163EA0D98 holder 0x163EA0D10
// key 0x32 (50) at 0x7FF610D978DF (`mov r8d,32; call [7FF61EEDBAA8]`);
// gfx_hidehand string 0x163E96FF8 holder 0x163E96F70 key 0x1A6 (422) at
// 0x7FF610D96854 (`mov r8d,1a6; call [same get]`). holder base = string - 0x88,
// both holders open with the same option vtable. small sequential ints, not
// fnv-1a (hash of name would be 32-bit large). only these two are grounded;
// do not invent further numbers — ground each new key live first.
enum class OptionID : int {
    Perspective = 3, // Options::getPerspective: `mov r8d,3` before the same get call (0 first person, 1 back, 2 front)
    Gamma = 50,
    HideHand = 422,
};
