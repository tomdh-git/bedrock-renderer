## NEXT
DONE

# Unit U-EL4w: close L4w gamecomponents fields — EditorHighlightConfiguration desc+0x08 (pending, blocked)

Exe 1.26.62.01, RVAs image-relative, static analysis only. Tags: [V] instruction seen in a listing, [I] inference, [?] unknown.

## Proven (do NOT redo)

- Part A GameplayMetadata (Light group, tag 2): fully [V] per oc_U-ED9c.md Part A. No pending rows.
- Part B ServerGraphicsOverrideParameters (Light group, tag 5): visitor-read +0x260/+0x268 [V]; block copies [V]; block Value type [?] non-blocking per ED9c.
- Part C EditorHighlightConfiguration (Effect group, tag 8, clone 0x4c8a5b0, thin): clone passes desc ptr + tag 8 to group insert only, no desc-field stores [V].
- Producer `rbx = rcx` arg = description base (`0x4c88974 mov rbx,rcx`); init flag checked at entry (`0x4c88977 cmp byte ptr [rcx+0x38],0` — desc object persists across calls).

## Answer table — eh+0x08 (pending item) vs proven producer stores

| Offset | Size | Site | Verbatim `0xRVA  instr` proof | Meaning | Tag |
|--------|------|------|-------------------------------|---------|-----|
| eh+0x08 | 8 | R `0x666b3be` | `0x666b3be  mov rax,[rbx+8]` | refcounted-object pointer READ by visitor; addref `lock inc dword ptr [rax+8]` @`0x666b3cb`; null-checked @`0x666b3c2`; NO producer store to +0x08 | [V] |
| eh+0x38 | 1 | St `0x4c8898e` | `0x4c8898e  mov byte ptr [rbx+0x38],1` | producer init flag | [V] |
| eh+0x40 | 8 | St `0x4c89163` | `0x4c89163 mov [rbx+0x40],rax` | producer qword store | [V] |
| eh+0x48 | 8 | St `0x4c88d0b` | `0x4c88d0b inc qword ptr [rbx+0x48]` | producer qword increment | [V] |
| eh+0x60 | 16 | St `0x4c88a7b` | `0x4c88a7b movups [rbx+0x60],xmm0` | producer xmmword store | [V] |
| eh+0x70 | 16 | St `0x4c88ac3` | `0x4c88ac3 movups [rbx+0x70],xmm0` | producer xmmword store | [V] |

descscan2 `--start 0x4c88900 --end 0x4c89881 --reg rbx` [V]: rbx accesses at +0x018,+0x038,+0x040,+0x048,+0x060,+0x068,+0x070,+0x078; GAPS include `0x0-0x38` (+0x00..+0x37 untouched). Confirms NO `[rbx+0x08]` store anywhere in the producer.

## BLOCKING FACT (single open item) — PROVEN

eh+0x08 is READ by the visitor [V] but NO producer store into description base at +0x08 exists. Producer stores only +0x38/+0x40/+0x48/+0x60/+0x70 into rbx [V]. desc+0x08 is set before the producer by code not located in any input data.

## Angles tried that FAILED (do NOT redo)

1. xref.py callers 0x4c88900 → 0 direct callers [V]; producer address not referenced as imm32/imm64/ripscan anywhere (0 hits [V]) — called indirectly only.
2. rdis xr 0x4c88900 → 0 xrefs [V]; rdis xr 0x4c9d010 (vtable slot 2) → 0 xrefs [V].
3. rdis vt 0xf20aa50 [V]: slot 0 = sub_4c88900 (producer); reached ONLY by virtual call slot 0 on object with vtable 0xf20aa50.
4. rdis imm 0xf20aa50 → 0 hits [V] (imm does NOT catch RIP-relative `lea`; verified `imm 0xf20a9d0`=0 despite `lea rax,[0xF20A9D0]` @`0x4c885a1` [V]).
5. rdis ptr 0xf20aa50 → 0 pointers [V] (no static object stores vtable addr as data qword).
6. rdis classes / class 0xf20aa50 → RTTI stripped for game classes [V]; no class name obtainable.
7. `find 48 8D 05` → 476K raw-byte hits (too noisy, not instruction-aware) [V].
8. fld [rcx]+[rcx+8] intersection → 10,053 candidate constructors (too noisy) [V].
9. sub_4c88570 near producer → constructor but vptr is `0xF20A9D0` (`lea rax,[0xF20A9D0]` @`0x4c885a8`), NOT `0xF20AA50` → sibling class [V].
10. livemem: game running (pid 10808) [V status]; `livemem vt 0x14A604` → vtable 0x0, all zeros → live effect_visitor.txt descptrs are NOT absolute addresses [V]; no editor/tag-8 live capture data [V].

## CLOSES?

NO — blocking fact: EditorHighlightConfiguration (Effect tag 8) visitor reads desc+0x08 at `0x666b3be mov rax,[rbx+8]` [V] (refcounted-object pointer; addref `0x666b3cb lock inc dword ptr [rax+8]`; null-check `0x666b3c2 test rax,rax`), but NO producer store into description base at +0x08 exists (complete rbx store enumeration [V]: only +0x38/+0x40/+0x48/+0x60/+0x70). desc+0x08 is set before the producer by the class-X constructor / virtual slot-0 caller, which is NOT located in any input data and could not be found statically (no direct caller, no static vtable storage, RTTI stripped, no live tag-8 target). GameplayMetadata fully [V]; ServerGraphicsOverrideParameters fully [V] (block Value type [?] non-blocking per ED9c).

## TOOL REQUESTS

indirect-caller / vtable-slot resolver | input: producer RVA 0x4c88900 or vtable 0xf20aa50 | output: the virtual call site that invokes slot 0 (producer) on a class-X object, and/or the constructor that stores vptr 0xf20aa50 at [rcx+0] and desc+0x08 at [rcx+8] | why: producer address is not a literal anywhere in the exe, so its caller—and the writer of desc+0x08—cannot be found statically from current inputs; needs a vtable-slot caller resolver or a way to find `lea rax,[0xF20AA50]; mov [rcx],rax` (RIP-relative lea not caught by `imm`).
