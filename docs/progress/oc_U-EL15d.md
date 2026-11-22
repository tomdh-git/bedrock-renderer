## NEXT
DONE

# U-EL15d: DLSS wrapper vtable slots 60 (optimal-settings) / 64 (evaluate) — RTX RendererContext

## Scope (pending part only)

L15d: DLSS wrapper vtable slots 60/64 — map sections 6bc, 6al.
- Slot 60 = `0xe83ec70`, size 0x55e [V] (rdis vt 0xF4EEE80; BGFX_MAP.md 6f/6k).
- Slot 64 = `0xe8403d0`, size 0xAA5B [V] (rdis vt 0xF4EEE80; BGFX_MAP.md 6f).
- Everything in the item line is proven [V] EXCEPT the slot-64 `rdx+0x30` field access listed by the precomputed dossier `docs/functions/e8403d0.md` argument-use (`rdx: +0x30(rqx2)`), plus the unread middle of `0xe8403d0` (~0xe840c80..0xe84a200). This note covers ONLY that pending part.

## Input read (3 pieces, appended after each piece)

1. Head `0xe8403d0..0xe840c80`: 439 instructions (`python tools/sigs/dumplist.py 0xe8403d0 0xe840c80`). No rdx-based access.
2. Middle `0xe840c80..0xe84a200`: 7686 instructions (`python tools/sigs/dumplist.py 0xe840c80 0xe84a200`). No `[rdx+0x30]`.
3. Tail `0xe84a200..0xe84ae8b` (function end per size 0xAA5B): 659 instructions (`python tools/sigs/dumplist.py 0xe84a200 0xe84ae8b`). No `[rdx+0x30]`.

Full function `0xe8403d0..0xe84ae8b` (0xAA5B) contiguously read. `0xe84af28`/`0xe84b008` seen in an older partial dump lie past `0xe84ae8b`, outside the function.

## Slot-64 rdx field-access table — all rdx+offset accesses with offset < 0x100 in the full function, plus the queried offset 0x30

| offset | size | read/store address | `0xRVA  instr` proof | sites | meaning | tag |
|--------|------|--------------------|----------------------|-------|---------|-----|
| 0x0 | 4/8 | [rdx] | `0xe841e6f  mov rdx,[rdx]` | 0xe841e6f (8), 0xe847bb9 (4), 0xe847bf7 (4), 0xe84a2e7 (8, `mov rdi,[rdx]`) | rdx = object pointer, dereferenced | [V] |
| 0x10 | 8 | [rdx+0x10] | `0xe846570  mov rdx,[rdx+0x10]` | 0xe846570 | pointer chain: rdx := [rdx+0x10] | [V] |
| 0x50 | 4 | [rdx+0x50] | `0xe846955  mov eax,[rdx+0x50]` | 0xe846955 | dword read | [V] |
| 0x80 | 8 (lea) | [rdx+0x80] | `0xe84ae48  lea rbp,[rdx+0x80]` | 0xe84ae48 | sub-object base address; lea computes a 64-bit address, no memory read | [V] |
| 0x30 | ? | - | - | none | NOT FOUND: no `[rdx+0x30]` instruction anywhere in head+middle+tail of `0xe8403d0` (entire 0xAA5B function). Dossier `docs/functions/e8403d0.md` lists `rdx: +0x30(rqx2)` but no matching instruction exists in the disassembly. Other rdx displacements in the function are 0x238, 0x2000 and the 0x415xxxx/0x4165xxxx family (plus mixed-base [r10+rdx+0xC], [rsi+rdx+0x415E890], [rcx+rdx+0xC]); none is 0x30. | [?] |

## CLOSES?

CLOSES?: NO — blocking fact: the slot-64 `[rdx+0x30]` field access listed in `docs/functions/e8403d0.md` (`rdx: +0x30(rqx2)`) is not present anywhere in the complete disassembly of `0xe8403d0` (head `0xe8403d0..0xe840c80` + middle `0xe840c80..0xe84a200` + tail `0xe84a200..0xe84ae8b` = entire 0xAA5B function); every rdx-based access in the function is at 0x0, 0x10, 0x50, 0x80, 0x238, 0x2000 or the 0x415xxxx/0x4165xxxx family, never 0x30, so this part stays [?] and cannot be closed [V].

## TOOL REQUESTS

None — all data gathered with existing tools (python tools/sigs/dumplist.py, rdis vt).
