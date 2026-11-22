## NEXT
DONE

# oc U-EF1b — F1b VV pass order from builder 0x55f1450 (6ar): in/out resources per pass

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only.
Input data read in full: docs/progress/oc_U-F1b.md (preflight), docs/progress/oc_U-F1b2.md (50 ordered pass-declaration call sites, argument setup per site).
Map sections consulted: docs/BGFX_MAP.md 6ar (builder pass declaration order by inline name immediates), 6eo (in 1.26.62.01 pass order = pure declaration order; the names-vector ordering stage is inert).
Pending part of the checklist item line: "in/out resources per pass still pending". Nothing known yet separates each pass's input resources from its output resources.

## Question
Does any instruction in builder 0x55f1450..0x563f594 or in the 9 pass-declaration callees (sub_5667860 x4, sub_5684660 x1, sub_5689800 x18, sub_5693680 x7, sub_5694510 x2, sub_5695960 x1, sub_5696540 x1, sub_5697650 x1, sub_5698290 x15) tag a descriptor/config field as input vs output resource?

## Table — 28-byte pass descriptor field accesses (all sites per distinct offset)
Row format: offset | size | read/store address (all sites) | verbatim `0xRVA  instr` | meaning [V]/[I]/[?]
Descriptor location: built by the builder at [rbp+0x2C00..0x2C1B] (28 bytes) and passed as a single pointer argument (e.g. r8 = lea [rbp+0x2C00] -> sub_5698290 at 0x55f1fb9..0x55f1fca).

| offset | size | read/store address (all sites) | `0xRVA  instr` | meaning |
|---|---|---|---|---|
| 0x00 | 2 | W [rbp+0x2C00] @ 0x55f1f68 (builder); R [rbx+0x0] @ 0x56982dc, W [rdi+8] @ 0x56982e3 (sub_5698290); R [rdx+0x0] @ 0x5667887, W [rcx+0x0] @ 0x566788a (sub_5667860) | `0x55f1f68  mov [rbp+0x2C00],ax` | Builder writes descriptor field +0x00 (u16 from [rbp+0x27A0]); sub_5698290 bulk-reads descriptor bytes 0x00..0x0F via movups and copies to a new 0x28-byte object at +8; sub_5667860 bulk-copies the same 16 bytes field-to-field. No instruction labels +0x00 as input or output resource [V] |
| 0x02 | 2 | W [rbp+0x2C02] @ 0x55f1f76 (builder) | `0x55f1f76  mov [rbp+0x2C02],ax` | u16 descriptor field +0x02 from [rbp+0x27A2]; not labeled input or output [V] |
| 0x04 | 4 | W [rbp+0x2C04] @ 0x55f1f83 and @ 0x55f1fa5 (builder) | `0x55f1fa5  mov dword ptr [rbp+0x2C04],0x2D` | dword +0x04 written from [rbp+0x27A4] (0x55f1f83) then overwritten with constant 0x2D (45) (0x55f1fa5); opaque [V] |
| 0x08 | 8 | W [rbp+0x2C08] @ 0x55f1f90 (builder) | `0x55f1f90  mov [rbp+0x2C08],rax` | qword descriptor field +0x08 from [rbp+0x27A8]; opaque [V] |
| 0x0C | 16 | R [rbx+0xC] @ 0x56982df, W [rdi+0x14] @ 0x56982e7 (sub_5698290) | `0x56982df  movups xmm1,[rbx+0xC]` | movups (16B) reads descriptor bytes 0x0C..0x1B and writes them to the new object at +0x14; with the +0x00 movups chunk this is the full 28-byte opaque copy; no field split into input/output [V] |
| 0x10 | 8 | W [rbp+0x2C10] @ 0x55f1f9e (builder); R [rdx+0x10] @ 0x566787f (sub_5667860); R [rsi+0x10] @ 0x56936f2 (sub_5693680); R [rdx+0x10] @ 0x56846a2 (sub_5684660) | `0x55f1f9e  mov [rbp+0x2C10],rax` | qword +0x10 written by builder from [rbp+0x27B0]; read as config field by 3 callees; opaque [V] |
| 0x18 | 4 | W [rbp+0x2C18] @ 0x55f1faf (builder); R [rdx+0x18] @ 0x566788d (sub_5667860); R [rdx+0x18] @ 0x56846a6 (sub_5684660); R [rsi+0x18] @ 0x56936f6 (sub_5693680, qword bound cmp) | `0x55f1faf  mov dword ptr [rbp+0x2C18],0` | dword +0x18 = 0 (last descriptor byte; descriptor spans 0x00..0x1B = 28 bytes); callees read it as dword/qword; opaque [V] |

## Findings (all from the quoted rows unless tagged [I])

1. Descriptor build (builder, rows at 0x00/0x02/0x04/0x08/0x10/0x18): the 28-byte descriptor is built field by field from [rbp+0x27A0..0x27B0] (u16, u16, dword=0x2D, qword, qword, dword=0) and passed as one pointer argument. No field is labeled input or output resource; no string names an input or output at a declaration call site. [V]
2. sub_5698290 (15 call sites) copies the 28-byte descriptor opaquely: `movups xmm0,[rbx]` (0x56982dc, bytes 0x00..0x0F) then `movups xmm1,[rbx+0xC]` (0x56982df, bytes 0x0C..0x1B), written to `[rdi+8]`/`[rdi+0x14]` of a 0x28-byte allocation, then the object is linked into a context list (`[rsi+0x28]` chain, `[rsi+0x38/0x40/0x48/0x50]` list management). No field test on the descriptor anywhere in the function. [V]
3. sub_5667860 (4 call sites) copies a larger source record field-by-field (`mov rax,[rdx+0x10]` 0x566787f, `movups xmm0,[rdx]` 0x5667887, `movss` floats [rdx+0x18..+0x6C]) into [rcx+...]. Flag reads `cmp byte ptr [rdx+0x100],1` (0x5667b02) and `cmp byte ptr [rsi+0x168],1` (0x5667d91/0x5667e79/0x5667edf/0x5667f4f) are on larger structs, not descriptor fields, and no instruction or string defines them as input vs output. [V reads, [I] meaning]
4. sub_5689800 (18 call sites) takes start/end/count range args (rcx/rdx/r8), no descriptor at all. [V]
5. sub_5693680/sub_5684660/sub_5694510/5695960/5696540/5697650 read config fields individually (`mov rax,[rsi+0x10]` 0x56936f2, `mov r14,[rdx+0x10]` 0x56846a2, `lea rax,[rdx+0x28]` 0x56846b1, list iteration on [r8+0x40] range) including flag compare `cmp byte ptr [rsi+0x3C0],1` (0x5693773) — bulk handling, no direction flag on any descriptor field. [V]
6. "FbIn"/"FbOut" strings occur in-range but ripscan over .text found ZERO builder references to them (only external functions 0x5de4b20, 0x5542770, 0x5430840). No pass uses them as in/out names. [V]

## CLOSES?
NO — blocking fact: no instruction in 0x55f1450 or any of the 9 pass-declaration callees tags any descriptor/config field as input vs output resource; the 28-byte pass descriptor is copied opaquely (movups 16-byte chunks at +0x00/+0x0C), so per-pass input/output resources cannot be separated statically.

## TOOL REQUESTS
- None
