## NEXT
DONE

# Unit U-EL4w: close L4w gamecomponents fields — EditorHighlightConfiguration desc+0x08 (pending, blocked)

Exe 1.26.62.01, RVAs image-relative, static analysis only. Tags: [V] instruction seen in a listing, [I] inference, [?] unknown. Image base 0x140000000.

## Proven — carried over (do NOT redo)

- Part A GameplayMetadata (Light group, tag 2): fully [V] per oc_U-ED9c.md Part A. No pending rows.
- Part B ServerGraphicsOverrideParameters (Light group, tag 5): visitor-read +0x260/+0x268 [V]; block copies [V]; block Value type [?] non-blocking per ED9c.
- Part C EditorHighlightConfiguration (Effect group, tag 8, clone 0x4c8a5b0, thin): clone passes desc ptr + tag 8 to group insert only, no desc-field stores [V].
- Producer `rbx = rcx` arg = description base (`0x4c88974 mov rbx,rcx`); init flag checked at entry (`0x4c88977 cmp byte ptr [rcx+0x38],0` — desc object persists across producer calls).

## Answer table — eh+0x08 (pending writer) vs proven producer stores into description base

| Offset | Size | Site | Verbatim `0xRVA  instr` proof | Meaning | Tag |
|--------|------|------|-------------------------------|---------|-----|
| eh+0x08 | 8 | R `0x666b3be` | `0x666b3be  mov rax,[rbx+8]` | refcounted-object pointer READ by visitor; addref `lock inc dword ptr [rax+8]` @`0x666b3cb`; null-checked @`0x666b3c2 test rax,rax`; visitor rbx = r15 = [r8] @`0x666b316 mov rbx,r15` / `0x666acf1 mov r15,[r8]`; **no producer store to +0x08 located** | [V] |
| eh+0x38 | 1 | St `0x4c8898e` | `0x4c8898e  mov byte ptr [rbx+0x38],1` | producer init flag | [V] |
| eh+0x40 | 8 | St `0x4c89163` | `0x4c89163  mov [rbx+0x40],rax` | producer qword store | [V] |
| eh+0x48 | 8 | St `0x4c88d0b` | `0x4c88d0b  inc qword ptr [rbx+0x48]` | producer qword increment | [V] |
| eh+0x60 | 16 | St `0x4c88a7b` | `0x4c88a7b  movups [rbx+0x60],xmm0` | producer xmmword store | [V] |
| eh+0x70 | 16 | St `0x4c88ac3` | `0x4c88ac3  movups [rbx+0x70],xmm0` | producer xmmword store | [V] |

descscan2 `--start 0x4c88900 --end 0x4c89881 --reg rbx` [V]: rbx accesses at +0x018,+0x038,+0x040,+0x048,+0x060,+0x068,+0x070,+0x078; GAPS include `0x0-0x38` (+0x00..+0x37 untouched). Confirms NO `[rbx+0x08]` store anywhere in the producer. Producer-internal virtual call `0x4c889a3 mov rax,[rsi]` / `0x4c889a6 mov rax,[rax+0x338]` / `0x4c889b7 call qword ptr [0xF99FFA0]` (slot 0x338 on rsi=r8, result [rbp+0x568]=r14, used for texture loading at desc+0x60/+0x70 region, NOT desc+0x08) [V]. Producer's clone call `0x4c89478 call 0x4C8A5B0` with `0x4c8946a mov rcx,[rbp+0x6C0]` (insert target) and `0x4c89471 lea rdx,[rbp+0x568]` — only xref to the clone [V]; clone inserts, writes no desc memory [V].

## Vtable lead (orchestrator hint) — re-verified this session

`rdis ptr 0x4c88900` -> one .rdata ptr at `0xf20aa50` = slot 0 of vtable `0xf20aa50` (slot 2 = sub_4c9d010 size 0x4000, slot 6 = sub_4c8d340). Producer reached ONLY by virtual call slot 0 on object whose vtable = 0xf20aa50; object `this` = desc base = rbx. Verified: vtable slot0 at `0xf20aa50` = `0089c84401000000` = VA `0x144C88900` = imagebase+0x4C88900 ✓; vtable VA = `0x144F20AA50`.

**New re-verification this session:** independent byte-scan of every file-backed PE section for qword == 0x144F20AA50 -> 0 hits; qword == 0x00F20AA50 (RVA form) -> 0 hits; qword == 0x144F20AA48 / 0x00F20AA48 (RTTI-adjacent) -> 0 hits. So vptr 0xf20aa50 NEVER exists statically in the image (not as imm64/imm32, not as lea target, not as stored data) — purely copied at runtime from another object instance (regress bottoms at engine init, no static anchor). RTTI stripped for game classes [V]; `rdis class`/`classes` -> no class name [V].

## NEW ANGLES TRIED THIS SESSION — ALL FAILED (do NOT redo)

1. `rdis imm 0xF20AA48` -> 0 hits; `rdis imm 0x144F20AA48` -> 0 hits [V] (RTTI-adjacent address never materialized).
2. `rdis comp EditorHighlightConfiguration` -> FNV-1a hash 0x7C46743a, `"name_seen_in_image":false`, total 0 functions [V] — not an ECS component registered by name hash; `comp EditorHighlight` -> hash 0xBA9E61B8, also 0 [V].
3. `rdis fld 8 --w --max 60` -> 423,933 [reg+8] write accesses across .pdata [V] — unfilterable to the desc-base object; `rdis fld 0 --w --max 120` -> 1,085,807 [reg+0] accesses (mostly xmm stores) [V] — unfilterable.
4. Enumerated every `call qword ptr [0xF99FFA0]` virtual-dispatcher site in .text (thousands — every refcounted destructor is slot 0 via `mov rax,[obj]; mov rax,[rax]; mov rcx,obj; call [0xF99FFA0]`) — slot-0 call sites cannot be filtered to vtable 0xf20aa50 statically [V]. Dispatcher confirmed: `0x4c8a639 call qword ptr [0xF99FFA0]` ; `[data_f99ffa0] = sub_eea6040` (= `jmp rax`) [V].
5. Factory/constructor functions near the producer examined in full:
   - `sub_4c88570` (ctor, 1 xref in at `sub_1c8b100+0x5f` = `0x1c8b15f call 0x4C88570`): `0x4c885a1 lea rax,[0xF20A9D0]; mov [rcx],rax` (vptr 0xF20A9D0), `0x4c885ab lea rax,[0xF20AA60]; mov [rcx+0x10],rax`, `0x4c885b6 lea rax,[0xF20AAB0]; mov [rcx+0x18],rax`, +0x8=float 1.0, +0x38=0, sub-object vptr 0xF146F20 at +0x70 [V]. vptr != 0xF20AA50 -> sibling class.
   - `sub_4c886d0` (ctor, alloc 0x80): vptr 0xF20A9D0 @`0x4c8872a`, sub-object vptrs 0xF20AA60/+0x10, 0xF20AAB0/+0x18, 0xF20B420 (0x18-byte sub-object) [V]. Sibling class.
   - `sub_1c8b100` family (create-component factories): vptrs 0xF08BFB0 (0x90-obj), 0xEFFDBE0 (0x30-obj, sub-obj vptr 0xF20A8B0 @`0x1c8b20d`), 0xF0ED760 (0x80-obj), 0xF0FD970 (0x60-obj, "bindings" string path) [V]. NONE store vptr 0xF20AA50.
6. `rdis str "EditorHighlight"` -> refs at 0xf53accc inside generated mega-functions sub_bb84ee0+0x280d/+0x447e (0xbbb76ed/0xbbb935e), no constructor context [V].
7. Livemem: game running (pid 18956, base 0x7ff699000000, version OK) [V status], but NO tag-8 live capture data anywhere: effect_visitor.txt has tags 1-4 only (descptrs = static image RVAs 14B950/14A450/14A668/14A604), editor_visitor.txt empty, editor_extractor.txt empty, older live_desc_* dumps have no tag 8 [V]. livemem requires a concrete target address; range-scanning is forbidden by the brief, so the runtime instance (vptr 0x144F20AA50) cannot be located or its +0x08 read. [V live attempt not possible — no target.]

## CLOSES?

NO — blocking fact: EditorHighlightConfiguration (Effect tag 8) visitor reads desc+0x08 at `0x666b3be mov rax,[rbx+8]` [V] (refcounted-object pointer; addref `0x666b3cb lock inc dword ptr [rax+8]`; null-check `0x666b3c2 test rax,rax`), but NO producer store into the description base at +0x08 exists (complete rbx store enumeration [V]: only +0x38 byte, +0x40 qword, +0x48 qword inc, +0x60 xmmword, +0x70 xmmword). desc+0x08 is set before the producer by the constructor of the runtime-created vtable-0xf20aa50 object. That constructor is not statically locatable: vptr 0x144F20AA50 is never materialized in the image (qword scan 0 hits for VA and RVA forms of both 0xF20AA50 and 0xF20AA48 [V]; imm/lea 0 [V]), RTTI stripped [V], no ECS component hash [V], thousands of slot-0 virtual-dispatch sites unfilterable [V], no tag-8 live instance to target [V]. All sibling/nearby factories construct other vptrs [V]. GameplayMetadata fully [V]; ServerGraphicsOverrideParameters fully [V] (block Value type [?] non-blocking per ED9c).

## TOOL REQUESTS

1. **live instance anchor for vtable 0xF20AA50** | input: none static available | output: live address of an object whose vptr = 0x144F20AA50, then `livemem chain <addr> 8` to read desc+0x08 and identify the config object | why: vptr never exists statically; the constructor/write of desc+0x08 can only be found from a live instance address, which no current capture provides. Requires orchestrator-added livecap target or a seed address.

## NEXT

DONE
