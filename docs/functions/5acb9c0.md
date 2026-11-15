# Dossier: 0x5acb9c0 - BlitFlipbook element emplace/copy helper (1.26.62.01)

Static analysis only. Target exe: `C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe`. Tags `[V]` verified from disassembly/rdis, `[I]` inferred, `[?]` unknown.

## Identity / role [V/I]
- Function: `sub_5acb9c0` (`0x5acb9c0..0x5acbe1f`, `.pdata` extent; `rdis sum` reports 37 blocks, 6 calls incl. tail jump).
- Copies/emplaces a **0x40-byte BlitFlipbook element** into a vector-like container (fast path when capacity available; slow path allocates/grows and relocates elements). [V copy sizes/offsets, I container type as vector of elements]

Evidence:
- Fast path (`@0x5acb9e0..0x5acba5a`): when `*(a0+0x8) != *(a0+0x10)` writes full 0x40 element from `a1` to destination `*(a0+0x8)` and then `add [a0+8], 0x40`.
- Slow path allocates/grows via allocator vcall(s) on global allocator object `*(&data_1233e1a8)` slot 1 and helpers (`sub_9bc830`, tail to `sub_5af0720`, throw helper `sub_75740`) and copies elements similarly [V calls/structure, I exact vector helper identities].
- Field-wise copies observed in both paths: qword `+0x00`, 16-byte `movups` `+0x08` region then SharedRef fixup, qwords/dwords/floats/bytes at `+0x18,+0x20,+0x24,+0x28,+0x2C,+0x30,+0x34,+0x3C`.

## Signature [I/V-ish]
```cpp
// [I] inferred from usage: a0 = element container/storage, a1 = source element (0x40 bytes)
// rdis returns rax as *u8(a1+0x3C) on one fast path [V], likely incidental to register state.
void emplaceOrPushBlitFlipbookElement(/*vector<Element>*/ void* elements, const Element* src);
```

## Element layout (0x40 bytes) [V]
From `rdis sum 0x5acb9c0` access trace/copies:
- `+0x00` qword: copied from `*(a1)` to destination `+0x00`. [V]
- `+0x08`..`+0x17`: copied as 16-byte block (`movups`) from source region and then `+0x08`/`+0x10` written explicitly as qwords from `a1+0x08/a1+0x10`. [V]
  - `+0x10` (control block pointer) participates in refcount increment: if `*(a1+0x10) != 0` then `inc dword [*(a1+0x10)+8]` (strong refcount) [V].
- `+0x18` qword: copied from `a1+0x18`. [V] (consumer uses as blend XY qword / `movsd [r14+0x18]`)
- `+0x20` dword: copied from `a1+0x20`. [V] (consumer uses as blend Z float / `movss [r14+0x20]`)
- `+0x24` float: copied (`movss`). [V] (consumer reads 16 bytes at `+0x24` via `movups` [V in consumer])
- `+0x28` float: copied. [V]
- `+0x2C` float: copied. [V]
- `+0x30` float: copied. [V]
- `+0x34` qword: copied (unaligned 8-byte copy). [V] **not observed read in Effect case 1 loop** `0x666b704..0x666c846` [V absence].
- `+0x3C` byte: copied (`movzx`/store). [V] **not observed read in Effect case 1 loop** `0x666b704..0x666c846` [V absence].
- Stride/size: destination/end advanced by `0x40` (`add [a0+8], 0x40`). [V]

This matches the `RenderBlitFlipbookDescription::Element` currently defined in `src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h` (size 0x40) [V layout agreement].

## Notes / semantics [I/?]
- `+0x08/+0x10` behave as a shared/control-block pair (strong refcount bump on control block at `ctrl+8`) consistent with `SharedRef`/shared_ptr storage conventions used elsewhere. [I]
- `+0x34/+0x3C` are part of the stored element but their consumer meaning in BlitFlipbook is unknown from this path; may be padding/flags/unused-by-this-extractor. [?]

## Verification
- [V] `rdis sum 0x5acb9c0` (copy sites, refcount increment, 0x40 advance).
- [V] Cross-check with consumer loop reads in `docs/functions/666aca0_blitflipbook.md` (reads inside `0x666b704..0x666c846` cover `+0x00,+0x08(addr),+0x18,+0x20,+0x24`; no `+0x28..+0x3C` reads seen).
- [V] Current header `Descriptions.h` element static_asserts align with copied offsets/sizes.

## Open
- Exact C++ container API/type for `a0` and precise role/name of every element field (`+0x00`, `+0x28..+0x30`, `+0x34`, `+0x3C`) remain partially inferred/unknown. [?]
