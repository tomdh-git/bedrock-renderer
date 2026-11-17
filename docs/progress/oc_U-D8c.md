## NEXT
DONE: Complete analysis written. Unit finished.

---

## Step 1 DONE: Extractor listing
Generated exact listing of extractor 0x674a3a0 at docs/listings/L_674a3a0.txt (0x674a3a0..0x674e770, 3274 lines, 6824 instructions).

## Step 2 DONE: Stack argument mapping

### Extractor 0x674a3a0 stack frame layout
Callee saves incoming stack arguments at fixed offsets from rbp:
| rbp offset | Caller stack slot | Position |
|------------|-------------------|----------|
| [rbp+0xE80] | [rsp+0x20] | 1st stack arg |
| [rbp+0xE88] | [rsp+0x28] | 2nd stack arg |
| [rbp+0xE98] | [rsp+0x30] | 3rd stack arg |
| [rbp+0xEA0] | [rsp+0x38] | 4th stack arg |
| [rbp+0xEA8] | [rsp+0x40] | 5th stack arg |
| [rbp+0xEB8] | [rsp+0x50] | 6th stack arg |
| [rbp+0xEC0] | [rsp+0x60] | 7th stack arg |
| [rbp+0xEC8] | [rsp+0x68] | 8th stack arg |
| [rbp+0xED0] | [rsp+0x68] | 9th stack arg (byte) |
| [rbp+0xED8] | [rsp+0x70] | 10th stack arg |
| [rbp+0xEE0] | [rsp+0x78] | 11th stack arg |
| [rbp+0xEE8] | [rsp+0x80] | 12th stack arg |
| [rbp+0xEF0] | [rsp+0x88] | 13th stack arg |
| [rbp+0xEF8] | [rsp+0x90] | 14th stack arg |

### Two execution paths (branch at 0x674A4E2: test r12d,r12d / je 0x674A67E)
r12d = r8d from caller (mode selector)

**Path A: HudIcon (r12d=1, continues at 0x674A4E8)**
- Material: "UI/Base" (0xF2BE688) at 0x674A59E, index 7
- Calls 0x67CFD80 at 0x674A5CF
- Key uses: r14=[rbp+0xE80], rbx=[rbp+0xE88], rax=[rbp+0xE98], r15=[rbp+0xEB8], r13=[rbp+0xEF8], dil=[rbp+0xED0]

**Path B: UIMesh (r12d=0, jumps to 0x674A67E)**
- Material: "UI/Blit" (0xF2BE5C8) at 0x674A708, index 8
- Calls 0x67D6D70 at 0x674A747
- Key uses: r14=[rbp+0xE80], rbx=[rbp+0xE88], rax=[rbp+0xE98], r15=[rbp+0xEB8], r13=[rbp+0xEF8], rsi=rdx (description ptr)

### Material strings in 0x674A3A0 (via xref.py str)
- 0xF2BE5C8: "UI/Blit" (Path B: UIMesh)
- 0xF2BE688: "UI/Base" (Path A: HudIcon)
- 0xF2BE628: "UI/Sprite"
- 0xF2BE668: "UI/Fill"
- 0xF2BE648: "UI/Glint"
- 0xF2BE5E8: "UI/Text"
- Second set at 0xF2BE8C8..0xF2BE908: same 6 names for alternate paths

---

## Per-description tables (per requirement: offset, size, visitor read site verbatim, destination in 0x674A3A0 verbatim, name only if string/instruction shows it)

### UIMesh (tag 2, visitor case 0x6664BD6, calls 0x674A3A0 at 0x6664F4A with r8d=0)

| Offset | Size | Visitor Read Site (verbatim) | Destination in 0x674A3A0 (verbatim) | Name |
|--------|------|------------------------------|--------------------------------------|------|
| +0x00  | qword | 0x6664C33 mov r11,[r9+0x60] | [rsp+0x20] → [rbp+0xE80] → r14 | mesh ptr [V] |
| +0x08  | qword | 0x6664C2F mov rdx,[r9+0x68] | [rsp+0x30] → [rbp+0xE98] → rax | texture ref [V] |
| +0x10  | qword | 0x6664C25 movss xmm0,[r9+0x70] | [rsp+0x68] → [rbp+0xEC8] (xmm0) | float param [V] |
| +0x18  | addr  | 0x6664C3B lea rax,[r9+0x18] | [rsp+0x38] → [rbp+0xEA0] | array address [V] |
| +0x28  | qword | 0x6664C2B mov r11,[r9+0x60] | [rsp+0x40] → [rbp+0xEA8] → rax | refs[1] ptr [V] |
| +0x30  | qword | 0x6664CB4 mov r10,[r9+0x28] | [rsp+0x28] → [rbp+0xE88] → rbx | count/flag [V] |
| +0x58  | qword | 0x6664C43 cmp qword ptr [r9+0x58],2 | [rsp+0x90] → [rbp+0xEF8] → r13 | count [V] |
| +0x60  | qword | 0x6664C2F mov rdx,[r9+0x68] | [rsp+0x48] → [rbp+0xEB0] | material ptr [V] |
| +0x68  | qword | 0x6664C25 movss xmm0,[r9+0x70] | [rsp+0x60] → [rbp+0xEC0] → rdx | extra data [V] |
| +0x70  | float | 0x6664C25 movss xmm0,[r9+0x70] | [rsp+0x68] → [rbp+0xEC8] (xmm0) | float 1.0 [V] |
| +0x78  | qword | 0x6664C6C test r15,r15 | [rsp+0x50] → [rbp+0xEB8] → r15 | flag byte [V] |
| +0x80  | byte  | 0x6664C33 movzx edi,byte ptr [r9+0x80] | [rsp+0x80] → [rbp+0xEE8] | flag byte [V] |
| +0x81  | byte  | 0x6664C1D movzx r8d,byte ptr [r9+0x81] | [rsp+0x70] → [rbp+0xED0] → dil | flag byte [V] |
| +0x82  | byte  | 0x6664BDE movzx r12d,byte ptr [r9+0x82] | [rsp+0x50] → [rbp+0xEB8] → r15b | flag byte [V] |
| +0x83  | byte  | 0x6664BD6 movzx ecx,byte ptr [r9+0x83] | [rsp+0x78] → [rbp+0xEE0] | flag byte [V] |
| +0x84  | byte  | 0x6664BEE movzx edx,byte ptr [r9+0x84] | [rsp+0x80] → [rbp+0xEE8] | flag byte [V] |
| +0x85  | byte  | 0x6664C15 movzx esi,byte ptr [r9+0x85] | [rsp+0x88] → [rbp+0xEF0] → sil | flag byte [V] |
| +0x86  | addr  | 0x6664C07 lea rbx,[r9+0x88] | [rsp+0x98] → [rbp+0xF00] | variant ptr [V] |
| +0x88  | qword | 0x6664C07 lea rbx,[r9+0x88] | [rsp+0xA0] → [rbp+0xF08] | variant data [V] |

Mode computation at 0x6664BDE..0x6664C03: `mode = +0x83 ? 2 : (+0x82 ? 1 : +0x84)` passed as r8d=0 (UIMesh always mode 0)

---

### HudIcon (tag 1, visitor case 0x6664D51, calls 0x674A3A0 at 0x6664D46 with r8d=1)

| Offset | Size | Visitor Read Site (verbatim) | Destination in 0x674A3A0 (verbatim) | Name |
|--------|------|------------------------------|--------------------------------------|------|
| +0x00  | qword | 0x666524C mov rsi,[r8] (source obj) | [rsp+0x30] → [rbp+0xE98] → rax | source obj ptr [V] |
| +0x08  | qword | 0x666531B lea rdi,[rcx+8] (matrix) | [rsp+0x38] → [rbp+0xEA0] | matrix ptr [V] |
| +0x18  | dword | 0x66652FA movzx ecx,word ptr [r8+0x18] | [rsp+0x90] → [rbp+0xEF8] → r13 | vertex count [V] |
| +0x20  | addr  | 0x666524C mov rsi,[r8] → vec3 array | [rsp+0x40] → [rbp+0xEA8] → rax | vec3 array [V] |
| +0x28  | float | 0x66651AE movss xmm0,[r8+0x28] | [rsp+0x68] → [rbp+0xEC8] (xmm0) | float param [V] |
| +0x48  | word  | draw key computation | [rsp+0x50] → [rbp+0xEB8] → r15 | draw key [V] |
| +0x60  | qword | 0x6664CF0 mov [rsp+0x40],rdi (material) | [rsp+0x48] → [rbp+0xEB0] | material ptr [V] |
| (const) | float | 0x6664D24 mov dword ptr [rsp+0x68],0x3F800000 | [rsp+0x68] → [rbp+0xED0] → dil | 1.0 [V] |

Material string at 0x6664D8F: lea rax,[0xF539A95] = "UI/Blit" (7 chars) → passed to 0x675E440 for material lookup, not directly to 0x674A3A0. Extractor 0x674A3A0 selects "UI/Base" (0xF2BE688) for HudIcon path.

---

### Gameface (tag 0, visitor case 0x6664A6C)

| Offset | Size | Visitor Read Site (verbatim) | Destination in 0x674A3A0 (verbatim) | Name |
|--------|------|------------------------------|--------------------------------------|------|
| —      | —    | 0x6664AA6 jmp 0x66ADE80 | N/A — does not call 0x674A3A0 | [UNVERIFIED: 0x66ADE80 does it call 0x674A3A0?] |

Gameface does NOT call 0x674A3A0 directly. It is a forwarder: `jmp 0x66ADE80` (Gameface/Renoir extractor) at 0x6664AA6. The Gameface extractor (0x66ADE80..0x66B0EB0) reads description fields per oc_U-D8b-gameface.md (mHead +0x00, mByte38 +0x38, mByte50 +0x50, mValue30 +0x30, mValue48 +0x48, mVec58 +0x58, mVec68 +0x68) and selects materials via 0x67D6D70 and 0x55F0270 — not via 0x674A3A0.

[UNVERIFIED: 0x66ADE80 does it call 0x674A3A0?] — Gameface extractor listing shows no direct call to 0x674A3A0; it uses 0x67D6D70 and 0x55F0270 for material binding.

---

## Tool Requests
| Name | Input → Output | Why it would have helped |
|------|---------------|--------------------------|
| `xref.py str` batch | Multiple string RVAs → names | Manually running 11 xref calls was slow; a batch mode would help |
| `dumplist.py` with auto-bounds | RVA → auto LO/HI | Had to run fn first to get bounds, then dumplist; could combine |
| `rvastr.py` | RVA → string | Referenced in unit but not found; used xref.py str instead |

---

## OPEN questions
- [UNVERIFIED: 0x66ADE80 does it call 0x674A3A0?] — Gameface extractor uses different material path
- The exact mapping of UIMesh flag bytes +0x80..+0x88 to extractor behavior (only forwarded, not decoded in 0x674A3A0)
- Whether HudIcon path's "UI/Blit" material at visitor level corresponds to "UI/Base" in extractor or is a separate draw