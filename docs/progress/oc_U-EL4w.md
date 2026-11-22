## NEXT
DONE

# Unit U-EL4w: close L4w gamecomponents fields — EditorHighlightConfiguration desc+0x08 (pending, blocked)

Exe 1.26.62.01, RVAs image-relative, static analysis only. Tags: [V] instruction seen in a listing, [I] inference, [?] unknown. Image base 0x140000000.

## Proven — carried over (do NOT redo)

- Part A GameplayMetadata (Light group, tag 2): fully [V] per oc_U-ED9c.md Part A. No pending rows.
- Part B ServerGraphicsOverrideParameters (Light group, tag 5): visitor-read +0x260/+0x268 [V]; block copies [V]; block Value type [?] non-blocking per ED9c.
- Part C EditorHighlightConfiguration (Effect group, tag 8, clone 0x4c8a5b0, thin): clone passes desc ptr + tag 8 to group insert only, no desc-field stores [V].
- Producer `rbx = rcx` arg = description base (`0x4c88974 mov rbx,rcx`); init flag checked at entry (`0x4c88977 cmp byte ptr [rcx+0x38],0` — desc object persists across producer calls).
- Vtable: `rdis ptr 0x4c88900` -> one .rdata ptr at `0xf20aa50` = slot 0 of vtable `0xf20aa50` (slot 2 = sub_4c9d010 size 0x4000, slot 6 = sub_4c8d340). Vtable slot0 at `0xf20aa50` = `0089c84401000000` = VA `0x144C88900` = imagebase+0x4C88900 ✓; vtable VA `0x140000000 + 0xF20AA50 = 0x14F20AA50`. Producer reached ONLY by virtual call slot 0 on object whose vtable = 0xf20aa50; object `this` = desc base = rbx.
- `rdis xr 0x4c88900` -> 0 direct callers [V]; producer address not referenced as imm32/imm64/ripscan anywhere (0 hits [V]) — called indirectly only.
- `rdis xr 0xf20aa50` -> 0 xrefs [V]; `rdis classes`/RTTI -> stripped, no class name [V]. BGFX_MAP 6ee names the type `gamecomponents::EditorHighlightConfiguration`, clone 0x4c8a5b0 thin Effect tag 8 [V doc]; 6ih: description exactly 0x58 bytes — +0x00 qword (vptr), +0x08 shared_ptr control block (`lock inc [ctrl+8]`), +0x10..+0x4F four 16-byte rows, +0x50 qword; pass entry stride 0x58 [V doc].

## Answer table — EditorHighlightConfiguration description-base fields (eh = desc base, offsets relative to rbx)

| Offset | Size | Site | Verbatim `0xRVA  instr` proof line(s) | Meaning | Tag |
|--------|------|------|---------------------------------------|---------|-----|
| eh+0x08 | 8 | R `0x666b3be`, `0x666b58c` | `0x666b3be  mov rax,[rbx+8]` ; `0x666b3c2  test rax,rax` ; `0x666b3cb  lock inc dword ptr [rax+8]` | refcounted-object pointer (shared_ptr control block) loaded from desc+0x08, null-checked, addrefed by visitor [V per 6ih]; again read at `0x666b58c  mov rax,[rbx+8]` and stored into pass-vector entry at `0x666b590  mov [r15+8],rax` (verbatim desc copy `0x666b586 mov rax,[rbx]` / `0x666b589 mov [r15],rax`, entry stride `0x666b5c0 add qword ptr [rsi+0x80],0x58`) | **no producer or clone store to +0x08 exists** | [V] |
| eh+0x38 | 1 | St `0x4c8898e` | `0x4c8898e  mov byte ptr [rbx+0x38],1` | producer init flag | [V] |
| eh+0x40 | 8 | St `0x4c89163` | `0x4c89163  mov [rbx+0x40],rax` | producer qword store into description base (result of shared_ptr addref via `0x4c8914e lea rcx,[r12+8]` / `0x4c89153 mov rax,[r12+8]` / `0x4c89158 mov rax,[rax+8]` / `0x4c8915c call qword ptr [0xF99FFA0]`) | [V] |
| eh+0x48 | 8 | St `0x4c88d0b` | `0x4c88d0b  inc qword ptr [rbx+0x48]` | producer qword increment into description base | [V] |
| eh+0x60 | 16 | St `0x4c88a7b` | `0x4c88a7b  movups [rbx+0x60],xmm0` | producer xmmword store into description base | [V] |
| eh+0x70 | 16 | St `0x4c88ac3` | `0x4c88ac3  movups [rbx+0x70],xmm0` | producer xmmword store into description base | [V] |

descscan2 `--start 0x4c88900 --end 0x4c89881 --reg rbx` [V]: rbx accesses at +0x018,+0x038,+0x040,+0x048,+0x060,+0x068,+0x070,+0x078; GAPS include `0x0-0x38` (+0x00..+0x37 untouched). Combined with the complete store enumeration above: **NO `[rbx+0x08]` store anywhere in the producer**, and no `[rbx+0x00]` vptr store either (vptr is not written by the producer). Clone 0x4c8a5b0 writes no description memory [V] (`0x4c8a620 mov [rbp+0x10],rdi`; `0x4c8a624 mov byte ptr [rbp+0x18],8`; `0x4c8a628 mov rax,[rsi]` / `0x4c8a62b mov rax,[rax+0x360]` / `0x4c8a639 call qword ptr [0xF99FFA0]` — group insert only).

Visitor register flow (re-confirmed): Effect case 8 head `0x666b316 mov rbx,r15` with `0x666acf1 mov r15,[r8]` at prologue (r8 = per-type node {desc_ptr+0, tag+8}); r15 clobbered to pass-vector cursor at `0x666b3a6 mov r15,[rsi+0x80]`; rbx clobbered at `0x666b3e0 mov rbx,rdi`. Only description-base read before clobbering is eh+0x08 at `0x666b3be` [V].

## Blocking fact (single open item) — PROVEN

eh+0x08 is READ by the visitor [V] (shared_ptr control-block pointer; addref `0x666b3cb lock inc dword ptr [rax+8]`; null-check `0x666b3c2 test rax,rax`; verbatim-copied into pass entry at `0x666b590 mov [r15+8],rax` [V]), but NO producer store into the description base exists at +0x08 (complete `[rbx+off]` store enumeration [V]: only +0x38 byte, +0x40 qword, +0x48 qword-inc, +0x60 xmmword, +0x70 xmmword; descscan2 gap 0x0-0x38 [V]); clone writes no description memory [V]. desc+0x08 (and the vptr at +0x00) are set before the producer by the constructor of the runtime object with vtable 0xf20aa50. That constructor is not statically locatable: vptr 0x14F20AA50 is never materialized in the image (all scanned forms 0 hits), RTTI stripped [V], no ctor for this class in functions.tsv or adjacent to producer/clone [V], all sibling/nearby factories construct other vptrs [V], thousands of slot-0 `call qword ptr [0xF99FFA0]` dispatcher sites cannot be filtered to this vtable [V], and no live instance address/seed exists for a livemem read (range-scan forbidden) [V].

## New angles tried THIS session — ALL FAILED (do NOT redo)

1. `rdis imm 0x14F20AA50` -> 0 hit(s) [V] — correct VA form (imagebase+0xF20AA50; r4/r5 scanned the typo'd 0x144F20AA50) — vptr VA not materialized as imm64 anywhere.
2. `rdis imm 0x00F20AA50` -> 0 hit(s) [V] — vptr RVA form not materialized as small immediate anywhere.
3. `rdis ptr 0xF20AA50` -> 0 pointer(s) [V] — no data qword storing the vtable RVA form in .rdata/.data.
4. Full producer listing re-read (0x4c88900..0x4c89881): at `0x4c893cf lea rcx,[rbp+0x568]` / `0x4c893d6 mov rdx,r12` / `0x4c893d9 call 0x4DFB570` a LOCAL transient description at rbp+0x568 is built/copied from source struct [rbp+0x480], fields patched at [rbp+0x57C]..[rbp+0x598] (NOT rbx-relative), then `0x4c8946a mov rcx,[rbp+0x6C0]` (= global 0x128C5048) / `0x4c89471 lea rdx,[rbp+0x568]` / `0x4c89478 call 0x4C8A5B0` inserts the local copy into the Effect group. No [rbx+0x08] store anywhere; rbx never copied to another register used as a [reg+8] store base.
5. Clone listing re-read (0x4c8a5b0..0x4c8a6e9): thin clone only (desc ptr + tag 8 -> group insert via vtable slot 0x360); confirms no desc-field stores.
6. `livemem status`: game running, pid 18956, base 0x7ff699000000, version OK [V live]. `livemem ptr @0x128C5048 2` -> +0x0 = heap ptr 0x0000053106252800 [V live]; `livemem vt 0x0000053106252800 4` -> vtable image+0xF2BDEB0 (FrameBuilder class passed to the clone), NOT image+0xF20AA50 — not an EditorHighlightConfiguration instance [V live]. No seed address for an instance of our class; range-scanning memory is forbidden by the brief; a live value is evidence for one instance, not proof of the static writer — livemem cannot close the static writer of desc+0x08.

## Previously tried angles that FAILED (carried over, do NOT redo)

1. xref.py callers 0x4c88900 → 0 direct callers [V]; imm32/imm64/ripscan 0 hits [V] — indirect call only.
2. rdis xr 0x4c88900 → 0 xrefs [V]; rdis xr 0xf20aa50 → 0 xrefs [V].
3. rdis vt 0xf20aa50 [V] full slot map: slot 0 = sub_4c88900 (producer); slots 1/3/4/5/8/9/10 = ret filler sub_768f0; slot 2 = sub_4c9d010; slot 6 = sub_4c8d340; slot 7 = sub_8d09d0; slot 11 = non-code. No constructor pointer anywhere in the vtable.
4. rdis imm 0xF20AA50/0x144F20AA50/0x004F20AA50 -> 0; lea for 0xF20AA50 -> 0; rdis ptr/data-scan for 0x144F20AA50 and RVA form -> 0 [V] — vptr never materialized statically.
5. rdis comp EditorHighlightConfiguration -> FNV-1a 0x7C46743a, name_seen_in_image false, 0 functions [V]; comp EditorHighlight -> 0xBA9E61B8, 0 [V].
6. rdis fld 8 --w -> 423,933 [reg+8] writes [V] unfilterable; fld 0 --w -> 1,085,807 [V] unfilterable.
7. Thousands of `call qword ptr [0xF99FFA0]` virtual-dispatcher sites (dispatcher = sub_eea6040 = jmp rax; [data_f99ffa0] = sub_eea6040 [V]) — slot-0 sites cannot be filtered to vtable 0xf20aa50 statically [V]. `rdis str "EditorHighlight"` -> refs only inside rendergraph pass-name mega-function sub_bb84ee0 [V], no constructor context. `rdis str "Volume-Highlight-Overlay"` data 0xf51e471 -> 1 xref (producer itself 0x4c889ee) [V].
8. Factories near producer examined: sub_4c88570 (vptr 0xF20A9D0), sub_4c886d0 (vptr 0xF20A9D0), sub_1c8b100 family (vptrs 0xF08BFB0/0xEFFDBE0/0xF0ED760/0xF0FD970) [V] — none store vptr 0xF20AA50. sub_4c8d407 (vptr 0xF0ED760, +0x08 immediate) [V] — different class. sub_4c9d010 (slot 2) adjustor/iterator [V]; sub_4c8d340 (slot 6) accessor [V].
9. Code immediately before/after producer (0x4c88000..0x4c88900, 0x4c89881, 0x4c8a6e9): sibling ctors storing other vptrs, dead slot-0 invoker thunk 0x4c888d0 with 0 xrefs, helper thunks only [V].
10. docs/data/functions.tsv: only 0x4c8a5b0 insert<EditorHighlight> thin clone named in neighborhood — no RenderEditorHighlightDescription constructor in table [V].
11. Visitor dispatch prologue dis 0x666aca0 [V]: r8 = per-type node {desc_ptr+0, tag+8}, r15 = [r8] = desc base; nothing creates the description there.
12. sub_331df0 callers (30 functions) enumerated [V]: none inits desc+0x08; desc+0x08 writer unknown.

## CLOSES?

NO — single blocking fact: EditorHighlightConfiguration (Effect tag 8) visitor reads desc+0x08 at `0x666b3be mov rax,[rbx+8]` [V] (shared_ptr control-block pointer; addref `0x666b3cb lock inc dword ptr [rax+8]`; null-check `0x666b3c2 test rax,rax`; value copied into pass-vector entry at `0x666b590 mov [r15+8],rax` [V]), but NO producer store into the description base exists at +0x08 (complete `[rbx+off]` store enumeration [V]: only +0x38 byte, +0x40 qword, +0x48 qword-inc, +0x60 xmmword, +0x70 xmmword; descscan2 gap 0x0-0x38 [V]); clone writes no description memory [V]. desc+0x08 is set before the producer by the constructor of the runtime object with vtable 0xf20aa50 — that constructor is not statically locatable: vptr 0x14F20AA50 never materialized statically (imm/lea/ptr/data-scan all 0 [V]), RTTI stripped [V], no ctor for this class [V], slot-0 virtual caller not filterable [V], no live instance seed (range-scan forbidden; live value cannot prove the static writer) [V]. GameplayMetadata fully [V]; ServerGraphicsOverrideParameters fully [V] except block Value type [?] (non-blocking per ED9c). The only unproven field is eh+0x08's writer.

## TOOL REQUESTS

1. live instance seed for vtable 0xF20AA50 | input: none static available | output: live address of an object whose vptr = image+0xF20AA50 (e.g. a global/registry walk into the Effect pass descriptions), then `livemem chain <addr> 8` to read desc+0x08 live | why: vptr never exists statically; no constructor or slot-0 caller is statically locatable; a live seed is the only remaining evidence channel. Requires orchestrator-added live-capture target or a seed address.
