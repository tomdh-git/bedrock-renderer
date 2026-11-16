## NEXT
DONE — all U-D5c deliverables written below; resume only if verify_oc.py reports mismatches.

[V] casewalk reachable=1510 from 0x6646a89 with regs rsi,rdx (listing docs/progress/_d5c_fn.txt, 0x6646980..0x664fda5).
[V] producer 0x5369920 has exactly 1 caller: 0x53def00 (size 0x56a).

---

## CASEWALK rsi/rdx RESULT — ZERO description reads

casewalk from 0x6646a89 with regs rsi,rdx found reachable=1510 but ZERO reads of the description via rsi or rdx. The description pointer is **rdi**, not rsi/rdx:
- Dispatch (0x66469fa-0x6646a0e): `rdi=[r8]` is the description pointer; tag byte at `[r8+8]`; jump table 0xF2BF2D0; case 4 -> 0x6646a89. `rdi=[r8]` is never rewritten inside case 4.
- rsi/[rbp] = resolver output object (shared_ptr ctrl block + material object); [rdx] = security cookie / record-vector writes. None of these are the description.

All description reads in handler 0x6646a89 are **rdi-based** [V]:

| RVA | Instruction | Offset | Size | Field | Tag |
|-----|-------------|--------|------|-------|-----|
| 0x6647e73 | `mov r14,[rdi+0x40]` | +0x40 | qword | mce::Mesh* mMesh | [V] |
| 0x6647edc | `movups xmm0,[rdi]` | +0x00 | 16B | mTransform row 0 | [V] |
| 0x6647ee6 | `movups xmm0,[rdi+0x10]` | +0x10 | 16B | mTransform row 1 | [V] |
| 0x6647ef1 | `movups xmm0,[rdi+0x20]` | +0x20 | 16B | mTransform row 2 | [V] |
| 0x6647efc | `movdqu xmm0,[rdi+0x30]` | +0x30 | 16B | mTransform row 3 | [V] |
| 0x6647f10 | `movzx esi,word ptr [rdi+0x48]` | +0x48 | u16 | mValue48 | [V] |

Read view: mat4 at +0x00..+0x3F, mce::Mesh* at +0x40, u16 at +0x48. **Last read ends at 0x4A (0x48 + 2 bytes u16), so read VIEW SIZE = 0x4A.** Bytes +0x4A..+0x4F are alignment padding, unread by the handler.

Indirect mesh reads (via mce::Mesh* at [rdi+0x40], NOT description fields): [r14+0x60], [r14+0x58] (count calc), [r14+0x1D4] flag byte, [r14+0x1D0] count — these are mesh fields, not description fields.

Matches docs/BGFX_MAP.md section 6ig (tag-4 reads). Direct disassembly supersedes the map's "+0x30+0x38+0x40+0x48" shorthand.

---

## PRODUCER 0x53def00 — STORES INTO THE DESCRIPTION

0x53def00 is the sole caller of thin clone 0x5369920. At 0x53def44 `mov rdi,rcx` so rdi=arg1. The description pointer is `[rbp+0x2A8] = [0x128C5048]` (loaded at 0x53df095, saved at 0x53df0da). It is passed as rcx to thin clone 0x5369920 at 0x53df328, with rdx = lea [rbp+0x210] (pointer to stack image of the description). The thin clone copies the stack image into the actual description memory.

**stores.py found ZERO matches** — by design it excludes `[rbp+/rsp+]` stack stores (`mm.group(3) not in("rsp","rbp")` at tools/sigs/stores.py line 10). All description-building stores in 0x53def00 target the stack image at `rbp+0x210..0x258` (offset difference 0x210 from description fields):

| RVA | Instruction | Stack Off | Desc Off | Size | Field | Source | Tag |
|-----|-------------|-----------|----------|------|-------|--------|-----|
| 0x53df2e4 | `movaps [rbp+0x210],xmm0` | +0x210 | +0x00 | 16B | mTransform row 0 | [rcx] where rcx=[rbp+0x280] | [V] |
| 0x53df2ef | `movaps [rbp+0x220],xmm0` | +0x220 | +0x10 | 16B | mTransform row 1 | [rcx+0x10] | [V] |
| 0x53df2fa | `movaps [rbp+0x230],xmm0` | +0x230 | +0x20 | 16B | mTransform row 2 | [rcx+0x20] | [V] |
| 0x53df305 | `movaps [rbp+0x240],xmm0` | +0x240 | +0x30 | 16B | mTransform row 3 | [rcx+0x30] | [V] |
| 0x53df30c | `mov [rbp+0x250],r15` | +0x250 | +0x40 | qword | mce::Mesh* mMesh | r15 (mesh pointer from producer logic) | [V] |
| 0x53df313 | `mov [rbp+0x258],ax` | +0x258 | +0x48 | u16 | mValue48 | ax = (u16)byte at [rax+0x74], rax=[rbp+0x278] | [V] |

These 6 stores build the complete description on the stack, then 0x53df328 `call 0x5369920` copies it into the actual description at [0x128C5048]. No direct `[desc_ptr+off]` stores exist in 0x53def00 — the thin clone performs the final memory writes into the description struct.

Source of matrix data: rcx = [rbp+0x280] (object with mat4 at +0x00..+0x30). Source of mMesh: r15. Source of mValue48: byte at [rax+0x74] zero-extended to u16.

---

## FIELD TYPES

| Offset | Size | Type | Meaning |
|--------|------|------|---------|
| +0x00 | 64B | float mTransform[4][4] | 4x4 row-major matrix |
| +0x40 | 8B | mce::Mesh* mMesh | mesh pointer |
| +0x48 | 2B | uint16_t mValue48 | u16 value |
| +0x4A | 6B | padding | alignment to 0x50 |

`sizeof(RenderChunkOccludersDescription) == 0x50` (pointer-padded; matches existing src struct, not edited).

---

## docs/progress/oc_U-D5c_header.h

See separate file. Contains struct RenderChunkOccludersDescription with offsetof/sizeof static_asserts. Read view ends at 0x4A.

---

## Verification with tools/sigs/verify_oc.py

Instruction lines claimed in this file (format `0xRVA  instr`) for verify_oc.py:

0x6647e73  mov r14,[rdi+0x40]
0x6647edc  movups xmm0,[rdi]
0x6647ee6  movups xmm0,[rdi+0x10]
0x6647ef1  movups xmm0,[rdi+0x20]
0x6647efc  movdqu xmm0,[rdi+0x30]
0x6647f10  movzx esi,word ptr [rdi+0x48]
0x53df2e4  movaps [rbp+0x210],xmm0
0x53df2ef  movaps [rbp+0x220],xmm0
0x53df2fa  movaps [rbp+0x230],xmm0
0x53df305  movaps [rbp+0x240],xmm0
0x53df30c  mov [rbp+0x250],r15
0x53df313  mov [rbp+0x258],ax

---

## TOOL REQUESTS

stores.py | listing -> [reg+off] store lines | Excludes [rbp/rsp] stack stores by design, so it found zero description stores in 0x53def00; I had to write a custom scan3.py to enumerate stack-image stores. Would be useful if stores.py had a flag to include stack-offset stores (_d5c_scan3.py was a throwaway replacement).