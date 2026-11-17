## NEXT
DONE

# U-ER4 — R4 AimAssistHighlight (Effect tag 6): true size and the shared-tail +0x84 read

## Goal (checklist RENDER_CHECKLIST.md section R, line 602)
Close R4: "AimAssistHighlight (Effect tag 6): true size (min 0x68) and the +0x84 read of the shared tail".
Pending parts: (1) true size of RenderAimAssistHighlightDescription (known floor 0x68 from the mat4 at desc+0x28), (2) attribute the dword read at [r15+0x84] in the shared tail 0x666c8f0 (left "not attributed" in BGFX_MAP.md 6ih).

## Input data read (fully)
- docs/BGFX_MAP.md: 6w (Effect tag 6 = CameraAimAssistHighlight), 6g/6m (clone 0x5370e80, visitor field reads), 6ih (case 0x666b143, min 0x68, tail 0x666c8f0 reads dword [r15+0x84] "not attributed")
- docs/functions/0x5370e80.md (thin insert clone), docs/functions/0x668e160.md (default ctor), docs/functions/0x666aca0.md (Effect visitor, tag-6 case @ 0x666b143)
- docs/data/producer_fields.txt (AimAssistHighlight producer 0x53e77c0)
- docs/progress/pre/0x666AA00.md (preflight listing: tag-6 case body 0x666b143-0x666b311; shared tail block at 0x666c8f0)
- Fresh evidence: rdis dis 0x666c8f0, rdis dis 0x668e160, rdis dis 0x53e77c0, xref.py callers 0x5370e80 -> 0x53e77c0

## Register convention for the tag-6 case
Visitor entry (0x666aca0): r8 = {desc*, tag byte at +8}, r15 = [r8] = description pointer, al = tag [V per docs/functions/0x666aca0.md dossier]. In the tag-6 case body (0x666b143-0x666b311) r15 is only read ([r15+0xC], [r15+0x14], `lea r8,[r15+0x28]` mat4 arg to 0xaa6580) and never written. Every exit from the case that reaches the shared tail — 0x666b2d8 je, 0x666b2e2 jne, 0x666b2fb jne, 0x666b311 jmp — therefore enters 0x666c8f0 with r15 still equal to the AimAssistHighlight description [V]. r15 is callee-saved, so the calls (0xaa6580, 0x675e440, shared_ptr release via [0xF99FFA0]) preserve it [V].

## Field map — one row per distinct offset, all sites merged
| offset | size | site(s) | verbatim `0xRVA  instr` proof line(s) | meaning | tag |
| +0x0C | 8 | read 0x666b151 (visitor tag-6 case); write 0x53e7c40 (producer 0x53e77c0; desc base rbp-0x58, so rbp-0x4C = desc+0x0C) | `0x666b151  movsd xmm2,[r15+0xC]` ; `0x53e7c40  movsd [rbp-0x4C],xmm1` | vec2 (2x f32) read by the case | [V]
| +0x14 | 4 | read 0x666b182 (visitor tag-6 case); write 0x53e7c45 (producer 0x53e77c0) | `0x666b182  movss xmm2,[r15+0x14]` ; `0x53e7c45  movss [rbp-0x44],xmm0` | float read by the case | [V]
| +0x84 | 4 | write 0x668e1c3 (default ctor 0x668e160); read 0x666c96f (shared tail 0x666c8f0) | `0x668e1c3  mov dword ptr [rdi+0x84],0xFFFFFFFF` ; `0x666c96f  mov edi,[r15+0x84]` | ctor sentinel -1; shared-tail dword read — ATTRIBUTED: r15 = desc at every tag-6 exit into the tail | [V]
| +0x118 | 8 | write 0x53e77db (producer 0x53e77c0 prologue; [rbp-0x58+0x118] = [rbp+0xC0]) | `0x53e77db  mov qword ptr [rbp+0xC0],0xFFFFFFFFFFFFFFFE` | qword sentinel (-2); highest proven write of the object | [V]

## True size
Max proven offset accessed: +0x118 with an 8-byte qword store → size >= 0x120 bytes [V].
The producer's stack object is at rbp-0x58 (desc base; passed as rdx to clone 0x5370e80 at `0x53e7d45  lea rdx,[rbp-0x58]` then `call 0x5370E80` at 0x53e7d49 [V]) inside a `sub rsp,0x148` frame (rbp = rsp+0x80), i.e. desc at rsp+0x28 within rsp..rsp+0x148 → the object fills exactly rsp+0x28..rsp+0x148 = 0x120 bytes [I frame-fit; no write beyond +0x118 observed anywhere in producer 0x53e77c0; last store +0x118 per docs/data/producer_fields.txt [V]].
Conclusion: true size = 0x120 bytes (proven floor 0x120 [V], exact fit [I]). This contradicts the SDK header's sizeof 0x88 and the earlier "min 0x68 / true size unknown" notes (BGFX_MAP.md 6ih; docs/progress/re-descriptions.md "AimAssistHighlight 0x88 (CONTRADICTS 6ih)") — the header is stale for this build. Open remark: ctor 0xAA9B90 is called at desc+0x98 (0x53e7cfc) and was not traced into; nothing above 0x120 is provable from the producer alone [?].

## Shared tail +0x84 read — resolved [V]
The shared tail at 0x666c8f0 executes `0x666c96f  mov edi,[r15+0x84]` (a dword read), immediately after `0x666c968  mov [rbp+0x668],r15` saves the description pointer. On the tag-6 path r15 is still the description pointer when the case jumps into 0x666c8f0, so [r15+0x84] IS desc+0x84 of RenderAimAssistHighlightDescription. The prior "not attributed" state (BGFX_MAP.md 6ih) is closed. The ctor pre-initializes the same field to -1 (`0x668e1c3  mov dword ptr [rdi+0x84],0xFFFFFFFF`) [V].

## CLOSES?
CLOSES? YES — every pending part of R4 is proven by [V] rows: (1) true size 0x120 bytes ([V] floor from the +0x118 qword store; [I] exact frame fit; header 0x88 contradicted), (2) the shared-tail +0x84 read (`0x666c96f  mov edi,[r15+0x84]` at 0x666c8f0) is attributed to the AimAssistHighlight description via r15 liveness through all tag-6 exits into the tail [V]. Non-blocking open remark: ctor 0xAA9B90 at desc+0x98 not traced into; exact upper bound above 0x120 rests on frame bounds only [?].

## TOOL REQUESTS
None
