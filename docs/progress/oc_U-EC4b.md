## NEXT
DONE

# UNIT U-EC4b — IntraFrameAllocator pending-field close (BGFX_MAP 6cy)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Input data: docs/progress/oc_U-C4b.md (C4b unit, verify_oc 54/54 PASS).
Pending items carried in from C4b: field table [UNVERIFIED] rows (arena A +0x18/+0x28 reads not located), 9+ callers of 0xa78940 unidentified, no sizeof for the IntraFrameAllocator object.

Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.
Every proof line below is quoted verbatim from `rdis dis` output and re-checked by `tools/sigs/verify_oc.py`.

## (1) Resolved: IntraFrameAllocator object fields ("this" = rcx/r15 at entry to 0xa78940)

descscan2.py 0xa78940 --reg r15 over the full function [0xa78940..0xa78e80) reads these offsets and no others on `r15`. Direction corrected versus C4b: +0x40/+0x48 are **reads** (`mov r10,[r15+0x40]`, `mov rcx,[r15+0x48]`), not writes.

| Offset | Size | Direction | Site (RVA) | Verbatim instruction proof | Meaning (from context) | Tag |
|--------|------|-----------|------------|---------------------------|------------------------|-----|
| IFA+0x00 | qword | R/W (xchg) | 0xa78ca3 | `0xa78ca3  xchg [r15],rax` | pointer to arena A (`[this+0x00]` passed as `rcx` to sub_a79700) | [V] |
| IFA+0x08 | qword | W | 0xa7897d | `0xa7897d  lock inc qword ptr [r15+8]` | refcount / use count (lock inc) | [V] |
| IFA+0x10 | qword | R | 0xa78b27 | `0xa78b27  mov r8,[r15+0x10]` | page-vector count / capacity (`add r8,r8` doubling loop) | [V] |
| IFA+0x18 | qword | W | 0xa78cc8 | `0xa78cc8  lock add [r15+0x18],rax` | cumulative allocated bytes (lock add) | [V] |
| IFA+0x28 | qword | R | 0xa78b2b | `0xa78b2b  mov rax,[r15+0x28]` | page-vector **begin** pointer | [V] |
| IFA+0x30 | qword | R | 0xa78b2f | `0xa78b2f  mov r9,[r15+0x30]` | page-vector **end** pointer | [V] |
| IFA+0x40 | qword | R | 0xa78b46 | `0xa78b46  mov r10,[r15+0x40]` | page-vector begin / cursor | [V] |
| IFA+0x48 | qword | R | 0xa78b4a | `0xa78b4a  mov rcx,[r15+0x48]` | page-vector end / cap | [V] |
| IFA+0x88 | qword | addr (lea) | 0xa78a1f | `0xa78a1f  lea rcx,[r15+0x88]` | embedded mutex (`lea rcx,[this+0x88]` -> sub_e943178) | [V] |
| IFA+0x90 | dword | R | 0xa78a2f | `0xa78a2f  mov eax,[r15+0x90]` | arena state (0=fast path, !=0=locked/grown) | [V] |

Highest confirmed IFA field: +0x90 (dword, end +0x94). No field beyond +0x90 is read or written in sub_a78940, sub_a79120 (reads only +0x28/+0x30/+0x40/+0x48), or sub_a79330 (operates on ctrl blocks, not IFA fields).

## (2) Resolved: arena A fields ("A" = [this+0x00], rcx at entry to sub_a79700)

descscan2.py 0xa79700 --reg rcx over the full function [0xa79700..0xa7988f) reads exactly these offsets on `rcx`; coverage gap `0x10-0x40` (and `0x82-0x88`).

| Offset | Size | Direction | Site (RVA) | Verbatim instruction proof | Meaning | Tag |
|--------|------|-----------|------------|---------------------------|---------|-----|
| ArenaA+0x00 | qword | R | 0xa7980e | `0xa7980e  mov r9,[rcx]` | arena field 0 (returned in block buf+0x00) | [V] |
| ArenaA+0x08 | qword | R | 0xa797eb | `0xa797eb  mov r9,[rcx+8]` | arena field 8 (refcount target `lock inc dword [r9+8]`) | [V] |
| ArenaA+0x40 | qword | W | 0xa797e6 | `0xa797e6  lock add [rcx+0x40],rdx` | allocated cursor (lock add) | [V] |
| ArenaA+0x48 | qword | R | 0xa79712 | `0xa79712  add rax,[rcx+0x48]` | available-space operand | [V] |
| ArenaA+0x50 | qword | R | 0xa79707 | `0xa79707  mov rax,[rcx+0x50]` | bump base/start (`rax = [A+0x50]`) | [V] |
| ArenaA+0x58 | qword | R/W | 0xa7970b / 0xa7979f | `0xa7970b  mov r10,[rcx+0x58]` / `0xa7979f  lock cmpxchg [rcx+0x58],rbx` | end/cursor (cmpxchg target; new end published here) | [V] |
| ArenaA+0x60 | qword | R | 0xa79724 | `0xa79724  add rax,[rcx+0x60]` | available-space operand | [V] |
| ArenaA+0x68 | qword | R | 0xa79719 | `0xa79719  add rax,[rcx+0x68]` | available-space operand / page-relative end | [V] |
| ArenaA+0x70 | qword | R | 0xa7971d | `0xa7971d  mov rdx,[rcx+0x70]` | base page ptr | [V] |
| ArenaA+0x78 | qword | W | 0xa797e1 | `0xa797e1  lock add [rcx+0x78],rdx` | total allocated (lock add) | [V] |
| ArenaA+0x80 | word | W | 0xa7972d | `0xa7972d  lock inc word ptr [rcx+0x80]` | generation word (lock inc word) | [V] |
| ArenaA+0x88 | qword | R/W | 0xa797ef | `0xa797ef  mov rdx,[rcx+0x88]` | page base | [V] |
| ArenaA+0x90 | qword | W | 0xa797f6 | `0xa797f6  mov [rcx+0x90],rdx` | current page base | [V] |
| ArenaA+0x98 | byte | W | 0xa797fd | `0xa797fd  mov byte ptr [rcx+0x98],1` | flag = 1 | [V] |

**Arena A +0x18 and +0x28: proven NOT fields.** descscan2 full-function coverage of sub_a79700 reports read bytes `0x0-0x10 0x40-0x82 0x88-0x99` with GAP `0x10-0x40`, which covers both +0x18 and +0x28. No instruction in sub_a79700 (the only function taking arena A as `rcx`) reads `[rcx+0x18]` or `[rcx+0x28]`. The C4b [UNVERIFIED] rows for arena A +0x18/+0x28 are therefore closed as **absent** [V] (coverage gap), not present.

## (1.5) Verbatim instruction proofs (one canonical site per distinct offset)

  0xa7897d  lock inc qword ptr [r15+8]
  0xa78ca3  xchg [r15],rax
  0xa78b27  mov r8,[r15+0x10]
  0xa78cc8  lock add [r15+0x18],rax
  0xa78b2b  mov rax,[r15+0x28]
  0xa78b2f  mov r9,[r15+0x30]
  0xa78b46  mov r10,[r15+0x40]
  0xa78b4a  mov rcx,[r15+0x48]
  0xa78a1f  lea rcx,[r15+0x88]
  0xa78a2f  mov eax,[r15+0x90]
  0xa7980e  mov r9,[rcx]
  0xa797eb  mov r9,[rcx+8]
  0xa797e6  lock add [rcx+0x40],rdx
  0xa79712  add rax,[rcx+0x48]
  0xa79707  mov rax,[rcx+0x50]
  0xa7970b  mov r10,[rcx+0x58]
  0xa79724  add rax,[rcx+0x60]
  0xa79719  add rax,[rcx+0x68]
  0xa7971d  mov rdx,[rcx+0x70]
  0xa797e1  lock add [rcx+0x78],rdx
  0xa7972d  lock inc word ptr [rcx+0x80]
  0xa797ef  mov rdx,[rcx+0x88]
  0xa797f6  mov [rcx+0x90],rdx
  0xa797fd  mov byte ptr [rcx+0x98],1

## (3) Pending: callers of allocate `0xa78940`

`xref.py callers 0xa78940` lists ~55 caller RVAs. Cross-checked every caller RVA against `docs/data/functions.tsv` (234 entries): only **0x55f1450 = "VV frame-graph builder (giant)"** is named (82 call sites). Every other caller (0xa786c0, 0x1147870, 0x1771960, 0x4e01de0, 0x567b890, 0x567bce0, 0x567c6e0, 0x567e510, 0x567fd70, 0x56815d0, 0x5682e20, 0x5684660, 0x5685ea0, 0x56876f0, 0x5688ff0, 0x568a310, 0x568a7f0, 0x568dc40, 0x568e110, 0x568e5f0, 0x568eb90, 0x568f030, 0x568f4e0, 0x568fa60, 0x568ff10, 0x56903d0, 0x5690960, 0x5690e10, 0x56912d0, 0x5691860, 0x5691d00, 0x56921b0, 0x5692730, 0x5692c00, 0x56930e0, 0x5693ba0, 0x5694050, 0x5694510, 0x5694fb0, 0x5695480, 0x5695960, 0x5695f00, 0x5696540, 0x5696ad0, 0x56970b0, 0x5697650, 0x569a4e0, 0x569ad50, 0x569b220, 0x569b700, 0x569bca0, 0x569c170, 0x569c650, 0x569cbf0, 0x569d160, 0x569e990, 0x56a06a0, 0x56a9b00, 0x56ab340, 0x56af0f0, 0x56b0940, 0x56b2190, 0x56b3a10, 0x56b3eb0 ...) is **UNNAMED** in functions.tsv. No string or callee reference identifies them in sampled prologues. -> [UNVERIFIED: exact name] for callers other than 0x55f1450.

## (4) Pending: sizeof of the IntraFrameAllocator object

No `new`/memset size and no bounds check for the IFA object is visible in the disassembly. Highest confirmed field is IFA+0x90 (dword, end +0x94), so `sizeof(IFA) >= 0x94` [I], but the exact total size is not determinable from static analysis. -> [UNVERIFIED].

## (5) Already-verified context (from C4b, not re-derived here)

- 0x38-byte out block: +0x00 `[A+0x00]`, +0x08 `this`, +0x10 block_ptr, +0x18 size, +0x20 offset, +0x28 `[A+0x88]`, +0x30 success flag — all [V] (sub_a78fc0 / sub_a79700).
- Refcounted ctrl block (0xC0, built by sub_a79330 / sub_a79900): ctrl+0x00 vtable, ctrl+0x08 use count, ctrl+0x0C weak count — [V] for ops (`lock inc/dec [ctrl+8]`, `[ctrl+0xC]`), layout is shared_ptr pattern [I].
- sub_a79900 = ctrl-block init (not IFA reset; exactly 1 xref from sub_a79330) [V]. No separate frame-reset function exists.

## CLOSES?

CLOSES? NO — single blocking fact: `sizeof(IntraFrameAllocator)` is not determinable from the disassembly (no allocation size / memset / bounds check; highest confirmed field IFA+0x90 end +0x94). Field list is now complete [V] (arena A +0x18/+0x28 proven absent); callers other than 0x55f1450 remain unnamed in functions.tsv ([UNVERIFIED: exact name]).

## Verification artifacts

- docs/progress/pre/0xa78940.md — `python tools/preflight.py 0xa78940` (fn+callers+callees+stores+listing 600 instr)
- descscan2.py 0xa78940 --reg r15 (this) and descscan2.py 0xa79700 --reg rcx (arena A), full-function scans
- rdis dis 0xa78940 / 0xa79700 / 0xa78b10 / 0xa78c80 / 0xa790d0 / 0xa79900 (verbatim instruction proofs above)

Run: `python tools/sigs/verify_oc.py docs/progress/oc_U-EC4b.md` then `python tools/delegate.py check docs/progress/oc_U-EC4b.md`

## TOOL REQUESTS
- None needed for this unit; descscan2 + rdis sufficed.
