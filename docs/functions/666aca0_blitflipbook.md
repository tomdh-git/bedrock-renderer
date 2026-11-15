# Dossier: 0x666aca0 Effect visitor - BlitFlipbook case (tag 1) / shared tail (1.26.62.01)

Static analysis only. Target exe: `C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe`. Tags `[V]` verified from disassembly, `[I]` inferred, `[?]` unknown.

## Identity / dispatch context [V]
- Visitor: `sub_666aca0` (Effect group, slot 108 wrapper `0x666aa00`, jump table `0xF2BF49C`, 9 cases). See `docs/functions/group_visitors.md`.
- On entry: `rax = *(u8*)(r8+8)` (tag), `r15 = [r8]` (description pointer), `r12 = rdx` (frame/pass context), `rbx = rcx` (builder/visitor receiver). Dispatch via jump table. [V]
- **Tag 1 (BlitFlipbook)** case entry: `0x666aec2`.

## Case 1 entry: material/resource resolution [V]
`0x666aec2..`:
- Reads frame context fields `r9 = [r12+0x40]`, `rcx = [r12+0x68]` and calls `sub_675e440` (`0x675e440`) with string/material key `"Flipbook"` (`lea rax,[0xF5A7830]`) to resolve material/object into local out slots (e.g. `[rbp+0x3E0]` / `[rbp+0x3F0]` patterns). [V]
- Uses resolved result `rsi = [*[rbp+0x3E0]]`; bails out to `0x666c846` if null or if `byte [rsi+0x10] != 1`. [V]
- Falls through to shared tail/loop setup around `0x666b67c` region for element processing (common tail used by multiple cases; BlitFlipbook reaches the element iteration described below). [V/I control-flow join]

## Description reads (BlitFlipbook path) [V]
In shared tail setup (e.g. `0x666b6cf` region): 
- `mov rax,[r15+0x10]`  -> element count/load basis
- `mov r14,[r15+0x18]`  -> element base pointer
- computes end = `r14 + (count << 6)` and stores to `[rbp+0x660]`
- loop: `0x666b704 cmp r14,[rbp+0x660]; je 0x666c846` (exit), `0x666b700 add r14,0x40` for step.

Thus description layout consumed is **0x20** `{ +0x00 SharedRef (not read in this tail slice except desc ptr context), +0x10 u64 count, +0x18 Element* data }` with 0x40-byte elements. [V]

## Element loop (0x666b704..0x666c846, stride 0x40, element ptr `r14`) [V]
Verified reads/uses inside loop range:
- `+0x00` qword: `0x666b942 mov rsi,[r14]` then uses `rsi` as mesh/object handle (e.g. inspects `[rsi+0x60]/[rsi+0x58]`, `[rsi+0x1D4]/[rsi+0x1D0]`, passes to `sub_bbd7c70` / `sub_4dedd00`). [V]
- `+0x08` (subobject/SharedRef ptr address): `0x666b858 lea r8,[r14+8]` passed to `sub_bcaba00` (`@0x666b88b`). [V]
- `+0x18` qword and `+0x20` dword/float: `0x666b897 movsd xmm1,[r14+0x18]`, `0x666b891 movss xmm0,[r14+0x20]` stored into locals for `VBlendControl`/related setup. [V]
- `+0x24` 16 bytes: `0x666ba25 movups xmm0,[r14+0x24]` (shuffled/stored for transform/state setup). [V]

Not observed in loop range `0x666b704..0x666c846` (searched disassembly): reads of `[r14+0x28]`, `[r14+0x2C]`, `[r14+0x30]`, `[r14+0x34]`, `[r14+0x38]`, `[r14+0x3C]`. [V absence within scanned range]

Loop control:
- Advance: `0x666b700 add r14,0x40` [V]
- End/bound: compare against `[rbp+0x660]` derived from desc count/data at `0x666b704..0x666b70b`, exit to `0x666c846` [V]

## Semantics [I/?]
- `+0x00`: mesh/render object handle pointer (used like mesh with vertex/index/instance-related fields queried later). [I]
- `+0x08`: texture/resource shared-ref subobject passed by address into bind/setup helper `sub_bcaba00`. [I]
- `+0x18/+0x20`: blend control values (XY qword + Z float), consistent with header naming `mBlendXY/mBlendZ`. [I]
- `+0x24`: 16-byte vector/packed float block consumed as state input (`movups` + `shufps`). [I]
- `+0x28..+0x30`, `+0x34`, `+0x3C`: present in element copies (see `0x5acb9c0`) but unused by this specific consumer path; meanings unknown. [?]

## Verification
- [V] `rdis dis 0x666aca0 ...` and targeted slices (`0x666aec2` case entry, `0x666b6f0+`, `0x666b830+`, `0x666ba00+`, loop end `0x666c846`).
- [V] `rdis dis 0x666b704 0x666c846` searched for `r14+0x28/2c/30/34/38/3c` (none found).
- [V] Cross-check with `docs/functions/group_visitors.md` (Effect tag 1 first callee `0x675e440`).
- [I] Attribution of any reads above +0x27 reported by broader-range tools outside `..0x666c846` to this element loop would be incorrect; range-bounded scan required.

## Open
- Full transcription/meaning of all helpers called in loop (`sub_bcaba00`, `sub_5679db0`, `sub_bbd7c70`, `sub_4dedd00`, etc.) and complete state written per element. [?]
- Producer-side meaning of unread element fields (`+0x28..+0x30`, `+0x34`, `+0x3C`) and description `+0x00` SharedRef target. [?]
