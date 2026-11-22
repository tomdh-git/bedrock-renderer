## NEXT
DONE

# Unit U-EL4w: close L4w gamecomponents fields — EditorHighlightConfiguration desc+0x08 (pending, blocked)

Exe 1.26.62.01, RVAs image-relative, static analysis only. Tags: [V] instruction seen in a listing, [I] inference, [?] unknown. Image base 0x140000000.

## Proven — carried over (do NOT redo)

- Part A GameplayMetadata (Light group, tag 2): fully [V] per oc_U-ED9c.md Part A. No pending rows.
- Part B ServerGraphicsOverrideParameters (Light group, tag 5): visitor-read +0x260/+0x268 [V]; block copies [V]; block Value type [?] non-blocking per ED9c.
- Part C EditorHighlightConfiguration (Effect group, tag 8, clone 0x4c8a5b0, thin): clone passes desc ptr + tag 8 to group insert only, no desc-field stores [V].
- Producer `rbx = rcx` arg = description base (`0x4c88974 mov rbx,rcx`); init flag checked at entry (`0x4c88977 cmp byte ptr [rcx+0x38],0` — desc object persists across producer calls).

Visitor confirmed (re-read this session): Effect visitor entry `0x666aca0 mov rbx,rcx / 0x666acf1 mov r15,[r8]` sets r15 = [r8] = description base (r8 = per-type node {desc_ptr+0, tag+8}); case 8 at `0x666b316 mov rbx,r15`. The visitor COPIES the whole description into the pass vector: `0x666b586 mov rax,[rbx]` / `0x666b589 mov [r15],rax` (desc+0x00 vptr), `0x666b58c mov rax,[rbx+8]` / `0x666b590 mov [r15+8],rax` (desc+0x08), then `0x666b5c0 add qword ptr [rsi+0x80],0x58` advances the pass cursor by 0x58. So desc+0x08 is a live refcounted-object-pointer field that is READ+addrefed+copied — but only READ by the visitor/producer path.

## Answer table — EditorHighlightConfiguration description-base fields (eh = desc base, offsets relative to rbx)

| Offset | Size | Site | Verbatim `0xRVA  instr` proof line(s) | Meaning | Tag |
|--------|------|------|---------------------------------------|---------|-----|
| eh+0x08 | 8 | R `0x666b3be`, `0x666b58c` | `0x666b3be  mov rax,[rbx+8]` ; `0x666b3c2  test rax,rax` ; `0x666b3cb  lock inc dword ptr [rax+8]` | refcounted-object pointer loaded from desc+0x08, null-checked, addrefed by visitor; again read at `0x666b58c  mov rax,[rbx+8]` and stored into pass-vector entry at `0x666b590  mov [r15+8],rax` (copy of desc `0x666b586 mov rax,[rbx]` / `0x666b589 mov [r15],rax`) | **no producer store to +0x08 exists** | [V] |
| eh+0x38 | 1 | St `0x4c8898e` | `0x4c8898e  mov byte ptr [rbx+0x38],1` | producer init flag | [V] |
| eh+0x40 | 8 | St `0x4c89163` | `0x4c89163  mov [rbx+0x40],rax` | producer qword store into description base | [V] |
| eh+0x48 | 8 | St `0x4c88d0b` | `0x4c88d0b  inc qword ptr [rbx+0x48]` | producer qword increment into description base | [V] |
| eh+0x60 | 16 | St `0x4c88a7b` | `0x4c88a7b  movups [rbx+0x60],xmm0` | producer xmmword store into description base | [V] |
| eh+0x70 | 16 | St `0x4c88ac3` | `0x4c88ac3  movups [rbx+0x70],xmm0` | producer xmmword store into description base | [V] |

descscan2 `--start 0x4c88900 --end 0x4c89881 --reg rbx` [V]: rbx accesses at +0x018,+0x038,+0x040,+0x048,+0x060,+0x068,+0x070,+0x078; GAPS include `0x0-0x38` (+0x00..+0x37 untouched). Combined with the complete store enumeration above: **NO `[rbx+0x08]` store anywhere in the producer**, and no `[rbx+0x00]` vptr store either (vptr is not written by the producer).

## Vtable lead (orchestrator hint) — re-verified this session

`rdis vt 0xf20aa50` (full slot map): slot 0 = sub_4c88900 (producer, size 0xf81); slot 1 = sub_768f0 (ret); slot 2 = sub_4c9d010 (size 0x4000, adjustor `add rcx,0xFFFFFFF0` -> 0x4ca48d0); slot 6 = sub_4c8d340 (0x8b); slot 7 = sub_8d09d0 (`mov rax,[rcx]`); slots 3-5, 8-10 = ret filler `sub_768f0`; slot 11 = non-code. Vtable slot0 at `0xf20aa50` = `0089c84401000000` = VA `0x144C88900` = imagebase+0x4C88900 ✓; vtable VA `0x144F20AA50`. So the producer IS reached — by virtual call slot 0 on an object whose vtable = 0xf20aa50; object `this` = desc base = rbx. But no code stores vptr 0xf20aa50 into any object.

## New angles tried this session — ALL FAILED (do NOT redo)

1. `rdis vt 0xf20aa50` — full slot map obtained above; only slot 0/2/6/7 are real code, all others ret fillers; no constructor pointer anywhere in the vtable.
2. Disassembled `0x4c88000..0x4c88700` (code immediately before producer): composite sibling ctor storing vptrs 0xF20A9D0/+0x0, 0xF20AA60/+0x10, 0xF20AAB0/+0x18, sub-object vptrs 0xF146F20/0xF20B420 — never 0xF20AA50; dead slot-0 invoker thunk at `0x4c888d0` (`mov rax,[rcx]; mov rax,[rax]; mov edx,1; call [0xF99FFA0]`) with 0 xrefs.
3. Disassembled `0x4c89881` (immediately after producer) and `0x4c8a6e9` (immediately after clone): helper thunks only, no creator/ctor adjacent.
4. `docs/data/functions.tsv`: only `0x4c8a5b0 insert<EditorHighlight> thin clone (Effect tag 8)` is named in this neighborhood — no `RenderEditorHighlightDescription` constructor exists in the table (all other description ctors are listed: nametag 0x668b6e0, clouds 0x668e940, skinnedmesh 0x668d350 and others).
5. Visitor dispatch prologue `dis 0x666aca0` — confirms r8 = per-type node, r15 = [r8] = desc base; case entries tail-jump to extractors; nothing creates the description.
6. `rdis str "EditorHighlight"` / `"[ClearColorDepth][EditorHighlightScene]"` — refs only inside mega-function chunk sub_bb84ee0+... rendergraph pass-name iteration (`0xbbb7f54` area compares pass names), no description creation/allocation.
7. `rdis xr 0xf51e471` ("Volume-Highlight-Overlay" string data): 1 xref — the producer itself (`0x4c889ee movups xmm0,[0xF51E471]`).
8. `sub_331df0` callers enumerated (30 functions via `rdis callers 0x331df0`): producer's site inits desc+0x18; no other site identified as the desc+0x08 writer — and in any case vptr 0xF20AA50 is never materialized statically, so no ctor can store it.
9. vptr materialization: `rdis imm 0xF20AA50`/`0x144F20AA50` → 0; `lea` for 0xF20AA50 → 0; `rdis ptr`/data-scan for 0x144F20AA50 and RVA form → 0 (every file-backed section scanned, r4); `rdis xr 0xf20aa50` → 0; `rdis classes`/RTTI → stripped [V]. vptr exists only at runtime (copied from a prototype instance).
10. `livemem status`: game running (pid 18956, base 0x7ff699000000, version OK) [V], but NO EditorHighlightConfiguration instance address is known — no tag-8 live capture data (effect_visitor.txt has tags 1-4 only), and range-scanning memory is forbidden by the brief, so there is no seed address for `livemem read/chain`; `livemem vt` cannot take a vtable address (returned "vtable None").

## CLOSES?

NO — single blocking fact: EditorHighlightConfiguration (Effect tag 8) visitor reads desc+0x08 at `0x666b3be  mov rax,[rbx+8]` [V] (refcounted-object pointer; addref `0x666b3cb  lock inc dword ptr [rax+8]`; null-check `0x666b3c2  test rax,rax`; value copied into the pass-vector entry at `0x666b590  mov [r15+8],rax` [V]), but NO producer store into the description base exists at +0x08 (complete `[rbx+off]` store enumeration [V]: only +0x38 byte, +0x40 qword, +0x48 qword-inc, +0x60 xmmword, +0x70 xmmword; descscan2 gap 0x0-0x38 [V]); clone writes no description memory [V]. desc+0x08 is set before the producer by the constructor of the runtime object with vtable 0xf20aa50 — that constructor is not statically locatable: vptr 0x144F20AA50 is never materialized in the image (imm/lea/data-scan/xr all 0 [V]), RTTI stripped [V], no ctor for this class in functions.tsv or adjacent to producer/clone [V], all sibling/nearby factories construct other vptrs [V], thousands of slot-0 `call qword ptr [0xF99FFA0]` dispatcher sites cannot be filtered to this vtable [V], and no live instance address/seed exists for a livemem read (range-scan forbidden) [V].

Part A (GameplayMetadata) fully [V]; Part B (ServerGraphicsOverrideParameters) fully [V] except block Value type [?] (non-blocking per ED9c). The only unproven field is eh+0x08's writer.

## TOOL REQUESTS

1. live instance anchor for vtable 0xF20AA50 | input: none static available | output: live address of an object whose vptr = 0x144F20AA50, then read desc+0x08 and trace its writer | why: vptr never exists statically; the desc+0x08 writer can only be found from a live instance address, which no current capture provides. Requires orchestrator-added live-capture target or a seed address.
