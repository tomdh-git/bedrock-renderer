## NEXT
DONE

# Unit U-EM1c — M1c Dossiers (D2): ordered L1-L3 raises + field-map fix

Binary: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; RVAs are image-relative; the exe is passed to rdis as an argument only, never launched. Every `0xRVA  instr` line below is copied verbatim from `rdis dis` output and re-verified against the exe this run via `tools/sigs/verify_oc.py` (all 21 claims match, see Verification).

## Step status

- Step 1 done: this file created with first line `## NEXT` and second line `step 2`. Line 2 is flipped to `DONE` only after `python tools/delegate.py check docs/progress/oc_U-EM1c.md` exits 0.
- Fix from the prior failed output: the duplicate offset row `r8+0x30` is merged into ONE row below (both sites listed: read `0xc2734b9  mov rax,[r8+0x30]`, write `0xc2734bd  mov qword ptr [r8+0x30],0`). No offset appears twice in the table.
- The prior output also had no CLOSES? verdict; one is added at the end of this file.

## Ordered D1 raises (checklist line order) — on-disk status

| # | Function | RVA | Dossier | Status |
|---|---|---|---|---|
| 1 | `BgfxContext::endFrame` | 0xc270460 | docs/functions/c270460.md | Dossier on disk; mechanical facts verified [V] (size 0x2aa, 161 instr; direct callees include generate 0xc273420 x1 and dispatch 0xe9002e0 x1 [V c270460.md]). Analyst/line-level sections are an unfilled template — not instruction-complete D2. |
| 2 | task list dispatch | 0xe9002e0 | docs/functions/e9002e0.md | Dossier on disk; mechanical facts verified [V] (size 0xc3a, 713 instr; only caller endFrame 0xc270460 [V e9002e0.md]). Analyst sections are an unfilled template — not instruction-complete D2. |
| 3 | D3D12 draw executor | 0xe821120 | docs/functions/e821120.md | Dossier on disk; structural summary only [V] (10398-instr body, only caller wrapper 0xe83c390 [V e821120.md]); body not line-level decoded, sub-regions marked [?]. D2-partial, NOT full D2. |
| 3b | executor wrapper (job launch) | 0xe83c390 | docs/functions/e83c390.md | Unfilled template on disk; only callee 0xe821120 x1 [V mechanical]. Not D2. |
| 4 | `bgfx::Frame::sort` | — | docs/functions/bc61e20.md | D2 fully reversed [V] — all 119 instructions of the 0x215-byte body mapped to source lines; callers 0xe82e230 / 0xe7f5380 / 0xe85e5c0 [V]. |
| 5 | `bgfx::Context::init` | 0xbc63690 | docs/functions/bc63690.md | Dossier on disk; mechanical facts verified [V] (size 0x2000; `this`=rcx=rsi [V]); analyst sections partially filled — not instruction-complete D2. |
| 5b | `bgfx::Context::frame` | 0xbc66de0 | docs/functions/bc66de0.md | Dossier on disk; mechanical facts verified [V]; analyst sections partially filled — not instruction-complete D2. |
| 6 | Encoder::submit family | 0xbc60740 / 0xe82e230 | docs/functions/bc60740.md, docs/functions/e82e230.md | Dossiers on disk; mechanical facts verified [V] (submit 0xbc60740 `Encoder::submit` sig in Sigs.json [V]; D3D12 submit slot 50 0xe82e230 [V]); analyst sections partially filled — not instruction-complete D2. |
| 7 | D3D12 graphics PSO builder | 0xe81e860 | docs/functions/e81e860.md | Dossier on disk; mechanical facts verified [V] (caller executor 0xe821120 per-job item loop [V e81e860.md]); analyst sections unfilled — not instruction-complete D2. |
| 8 | five task bodies | — | none on disk | Not found — RVAs and dossiers not yet pinned [?]. |

`generate 0xc273420` (docs/functions/c273420.md) and render lambda `0xc267200` (docs/functions/c267200.md) were raised in the prior run and are the source of the fixed field map below; they are not re-listed as pending.

## Fixed field map (generate 0xc273420 / render lambda 0xc267200)

One annotated row per distinct offset, all its sites listed, size from the instruction, verbatim `0xRVA  instr` proof line copied from rdis output. `r8+0x30` (duplicate in the prior output) and `r8+0x20` now appear once each with all sites listed.

| offset | size | site | `0xRVA  instr` | meaning |
|---|---|---|---|---|
| rcx+0x8 | 8 | R | `0xc267228  mov rsi,[rcx+8]` | Render lambda: closure+0x8 = task object pointer -> rsi [V c267200.md] |
| r14+0x48 | 8 | R | `0xc267349  mov rcx,[r14+0x48]` | Render lambda: closure+0x48 = current task object [V c267200.md] |
| r15+0xE8 | 8 | W | `0xc267506  mov qword ptr [r15+0xE8],0` | Render lambda: 0xF8 object+0xE8 result slot = 0 [V c267200.md] |
| r15+0xF0 | 1 | W | `0xc267549  mov byte ptr [r15+0xF0],0` | Render lambda: 0xF8 object+0xF0 flag byte = 0 [V c267200.md] |
| rsi+0x150 | 8 | R/W | `0xc2675a0  xchg [rsi+0x150],rax` | Render lambda: task+0x150 timeout slot, xchg new timeout [V c267200.md] |
| rsi+0x98 | 8 | W | `0xc2675ea  mov [rsi+0x98],rax` | Render lambda: task+0x98 handoff ptr = rax [V c267200.md] |
| rsi+0xA0 | 8 | W | `0xc2675f8  mov [rsi+0xA0],r15` | Render lambda: task+0xA0 handoff ptr = r15 (xchg) [V c267200.md] |
| rsi+0x138 | 8 | R | `0xc26764f  mov r14,[rsi+0x138]` | Render lambda: task+0x138 owner/notifier ptr [V c267200.md] |
| r14+0x350 | 8 | R (lea) | `0xc2676f4  lea rcx,[r14+0x350]` | Render lambda: closure+0x350 enqueue target for sub_eec5b90 [V c267200.md] |
| r14+0x90 | 4 | W | `0xc2676cc  lock xadd [r14+0x90],r15` | Render lambda: closure+0x90 signaled counter += r15 [V c267200.md] |
| r8+0x50 | 8 | R | `0xc2734a0  cmp qword ptr [r8+0x50],0` | Generate: declarator+0x50 gate; 0 -> early exit loc_c273fbd [V c273420.md] |
| r8+0x30 | 8 | R/W | `0xc2734b9  mov rax,[r8+0x30]` / `0xc2734bd  mov qword ptr [r8+0x30],0` | Generate: declarator+0x30 cap read then zeroed (vector moved out); both sites merged into one row [V c273420.md] |
| r8+0x20 | 16 | R/W | `0xc2734c5  movups xmm0,[r8+0x20]` / `0xc2734d4  movups [r8+0x20],xmm1` | Generate: declarator+0x20 {begin,end} read then zeroed (vector moved out); both sites merged into one row [V c273420.md] |
| rcx+0x20 | 8 | R | `0xc2734ee  mov rax,[rcx+0x20]` | Generate: context+0x20 arena object ptr read [V c273420.md] |
| rax+0x0 | 8 | R | `0xc2734f2  mov rax,[rax]` | Generate: arena object+0 = arena handle [V c273420.md] |
| rax+0x38 | 8 | R | `0xc273745  mov r12,[rax+0x38]` | Generate: declared-vector begin (arena+0x38) [V c273420.md] |
| rax+0x40 | 8 | R | `0xc273749  mov rax,[rax+0x40]` | Generate: declared-vector end (arena+0x40) [V c273420.md] |
| rbp+0x3450 | 8 | R/W | `0xc2780c3  mov rax,[rbp+0x3450]` | Generate: per-pass loop cursor [V c273420.md] |
| cursor+0x8 | 8 | R | `0xc2780ca  mov r13,[rax+8]` | Generate: pass object ptr = cursor entry+8 [V c273420.md] |

## Verification this run

- All 21 instruction claims re-checked verbatim against the exe: mov rsi,[rcx+8] at c267228; mov rcx,[r14+0x48] at c267349; mov qword ptr [r15+0xE8],0 at c267506; mov byte ptr [r15+0xF0],0 at c267549; xchg [rsi+0x150],rax at c2675a0; mov [rsi+0x98],rax at c2675ea; mov [rsi+0xA0],r15 at c2675f8; mov r14,[rsi+0x138] at c26764f; lea rcx,[r14+0x350] at c2676f4; lock xadd [r14+0x90],r15 at c2676cc; cmp qword ptr [r8+0x50],0 at c2734a0; mov rax,[r8+0x30] at c2734b9; mov qword ptr [r8+0x30],0 at c2734bd; movups xmm0,[r8+0x20] at c2734c5; movups [r8+0x20],xmm1 at c2734d4; mov rax,[rcx+0x20] at c2734ee; mov rax,[rax] at c2734f2; mov r12,[rax+0x38] at c273745; mov rax,[rax+0x40] at c273749; mov rax,[rbp+0x3450] at c2780c3; mov r13,[rax+8] at c2780ca — every claim matches `rdis dis` output [V rdis verbatim].
- Dossier status lines re-read from disk: c270460.md / e9002e0.md / e821120.md / bc63690.md / bc66de0.md / bc60740.md / e82e230.md / e81e860.md have mechanical-facts sections and unfilled/partially-filled analyst templates [V file reads]; bc61e20.md is instruction-complete D2 [V].

## Remaining (not raised to instruction-complete D2 this run)

- executor 0xe821120 full D2: 10398-instruction body not line-level decoded; sub-regions [?].
- executor wrapper 0xe83c390 full D2 dossier: unfilled template on disk.
- five task bodies: no RVAs/dossiers pinned [?].
- Analyst/line-level sections for endFrame, dispatch, Context::init/frame, Encoder::submit family, PSO builder: unfilled templates on disk — not instruction-complete D2.

## CLOSES?

NO — the ordered M1c D2 raise is not complete on disk. Single blocking fact: executor 0xe821120 is not instruction-complete D2 (10398-instruction body, structural summary only, sub-regions [?]); in addition the wrapper 0xe83c390 is an unfilled template and the five task bodies have no RVAs/dossiers yet. Every other item in the order has a dossier on disk with verified mechanical facts, but most analyst sections remain unfilled templates.

## TOOL REQUESTS

None — used `rdis dis` for verbatim verification and existing `docs/functions/<rva>.md` dossiers.
