## NEXT
DONE

# U-ER9: R9 FadeToBlack (Effect tag 5) + FullscreenEffect (tag 7) config layout

## Source item (docs/RENDER_CHECKLIST.md line 607, `[ ]`)
R9 FadeToBlack (Effect tag 5): description payload (0x67d6d70 is only a keyed lookup); FullscreenEffect (tag 7): config object layout (+0x180/+0x181/+0x185/+0x1A8)

## Method
All instruction lines below were taken verbatim from `rdis dis` of Minecraft.Windows.exe 1.26.62.01 and every backtick-quoted `0xRVA  instr` segment is re-checked by `tools/sigs/verify_oc.py`. Sizes come from the instruction (movzx byte/cmp byte = 1; mov rax,[mem] = qword 8). Meaning is given only where the instruction/string shows it, else '-'. No input data pasted as-is; one row per distinct offset.

## Part A — FadeToBlack (Effect tag 5): description payload — NOT decodable (blocked)

The tag-5 case lives in `0x666aca0` (Effect visitor) at entry `0x666afde`. Its only description-related action is a call to `0x67d6d70`, which is a keyed find-or-insert over key bytes at key+0x08..+0x0F — it is NOT a description payload reader. At the callsite the key argument is a STATIC object, not description `r15`:

- `0x666b08e  lea r8,[0x129FA108]` — r8 = static key object, NOT description-derived bytes
- `0x666b095  lea rdx,[rbp+0x630]`
- `0x666b09c  call 0x67D6D70`

No description payload offset is read anywhere in the tag-5 case path (0x666afde → 0x67d6d70 call → result release → 0x666c865 tail), and no clone/producer exists for Effect tag 5 (D12: "names FadeToBlack ... rest on the variant order (no clone found)"; slotscan --tag 5 empty).

Evidence that 0x67d6d70 itself is only the keyed lookup is in docs/functions/0x67d6d70.md and BGFX_MAP.md 6ih: it hashes key+0x08..+0x0F (FNV-1 64), masks on [obj+0x70], walks buckets at [obj+0x58]/[obj+0x48], appends 0x10-byte records — the description's meaningful payload is not read by it [? meaning / no payload layout].

Blocking fact for Part A: no FadeToBlack description payload field is read anywhere in the visitor, and no tag-5 producer/clone exists, so no payload offset or size can be proven from static disassembly.

## Part B — FullscreenEffect (tag 7): config object layout at +0x180/+0x181/+0x185/+0x1A8 — decoded [V]

Tag-7 case entry `0x666ae72` (in `0x666aca0`, r15 = description). The description chain is:
- `0x666ae72  mov rax,[r15+0x78]` — desc+0x78 = pointer to config-holding object
- `0x666ae7f  cmp qword ptr [rax+0x40],0` — [desc+0x78]+0x40 must be non-zero (this is the config object)
- `0x666ae91  lea r12,[r15+0x78]`
- `0x666ae95  mov rax,[r15]` — desc+0x00 = qword pointer
- `0x666ae98  movzx r8d,byte ptr [rax+0x39]` — [desc+0x00]+0x39 byte → r8b flag arg
- `0x666ae9d  lea rcx,[rbp+0x2A0]` — out record at rbp+0x2A0
- `0x666aea4  mov rdx,r12` — rdx = &desc+0x78
- `0x666aea7  call 0x66B2B30`

Inside `0x66b2b30`, `rdx` becomes the config object: `0x66b2b5b  mov rcx,[rdx]` / `0x66b2b5e  mov rdx,[rcx+0x40]` → cfg = *(*(desc+0x78)+0x40). The requested config offsets are all single-byte reads:

| offset | size | site | verbatim proof | meaning | tag |
|---|---|---|---|---|---|
| desc+0x78 | 8 | 0x666ae72 | `0x666ae72  mov rax,[r15+0x78]`\n`0x666ae7f  cmp qword ptr [rax+0x40],0` | config-holder pointer at desc+0x78; [ptr+0x40] null-checked, non-zero required | [V] |
| desc+0x00 | 8 | 0x666ae95 | `0x666ae95  mov rax,[r15]`\n`0x666ae98  movzx r8d,byte ptr [rax+0x39]` | qword pointer at desc+0x00; [ptr+0x39] byte passed as r8b flag | [V] |
| cfg+0x185 | 1 | 0x66b2b65 | `0x66b2b65  cmp byte ptr [rdx+0x185],1` | byte compared to 1 — gate selecting the non-default blend path; semantics beyond the compare not shown | [V] |
| cfg+0x180 | 1 | 0x66b2b72 | `0x66b2b72  movzx ecx,byte ptr [rdx+0x180]` | byte read; xor 3, part of byte-pair chain written to out+0x00; semantics not shown | [V] |
| cfg+0x181 | 1 | 0x66b2b79 | `0x66b2b79  movzx r9d,byte ptr [rdx+0x181]` | byte read; xor 2, part of byte-pair chain written to out+0x00; semantics not shown | [V] |
| cfg+0x1A8 | 1 | 0x66b2c14 | `0x66b2c14  movzx ecx,byte ptr [rdx+0x1A8]` | byte read; cmp 1 / cmp 2 feeding out+0x08 (0/1/2 mapping); semantics not shown | [V] |

cfg derivation lines (context, not table offsets): `0x66b2b5b  mov rcx,[rdx]`, `0x66b2b5e  mov rdx,[rcx+0x40]` → cfg = `*(*(desc+0x78)+0x40)`; all four cfg reads above use this cfg [V]. Blend-mode/state semantic names for cfg+0x180/+0x181/+0x185/+0x1A8 are NOT shown by any instruction and stay '-' (earlier [I] blend-preset readings are not re-stated as fact).

## Part A remaining evidence (negative finding)
No table rows possible for Part A: no description offset is read by the tag-5 case, so there is no offset/size to annotate. The only verified instruction facts are the static-key call above; everything else (minimum size, defaults, producer) is open.

## CLOSES?
CLOSES? NO — FullscreenEffect cfg+0x180/+0x181/+0x185/+0x1A8 are proven [V] above (6 rows, all verbatim instructions verified), but the FadeToBlack (tag 5) description payload part is NOT closed: no payload offset/size exists to prove because the tag-5 case calls 0x67d6d70 with a static key object (0x666b08e `lea r8,[0x129FA108]`, not description r15) at 0x666b09c, reads no description payload offset, and no tag-5 clone/producer exists (D12: no clone found). Single blocking fact: the FadeToBlack description payload is never read by the visitor, so its layout cannot be decoded from static disassembly; a producer or payload read must be located first.

## TOOL REQUESTS
None.
