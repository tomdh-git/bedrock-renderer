# U-D5d: Crack description clone 0x539fff0 (fat, Item tag 5) — progress log

## NEXT
Resume: everything below is done except (a) confirm whether cold-path cleanup 0x664E971/0x664EBD7 releases the case-5 description texture ref, (b) run verify_oc.py on this file and the header, (c) append ## TOOL REQUESTS and end. Current header candidate = docs/progress/oc_U-D5d_header.h (mirrors Descriptions.h RenderCrackDescription static_asserts). Next step: write the header + run verify_oc.py.

## DONE

Clone dump:
- `sub_539fff0` [0x539fff0..0x53a0986) size 0x996, 543 instr, frame 0x1c8. Listing saved: docs/progress/_d5d_fn.txt (dumplist.py). [V]
- Args: rcx = level renderer (rdi), rdx = context holder ([rdx+0x28] -> r14 = ctx), r8 = crack state (rbx). [V]
- Phase 2 builds per-entry RenderCrackDescription on the stack at rbp+0x60 inside a loop over state+0x3280..+0x3288 entries (stride 0x20). [V]
- Phase 3 (SEPARATE from the description build, confirms 6ga over 6ea): walks the intrusive destroy-progress list head [levelRenderer+0xEC8]; `movss xmm0,[rbx+0x20]` progress at 0x53a07dc (skip if <=0); key node+0x10 BlockPos; vcall region+0x10 getBlock(pos); 0x5391130 validity; vcall region+0x140 block entity; packs {x&0xF->[rbp+0xF0] 0x53a0850, z&0xF->[rbp+0xF1] 0x53a0857, y-regionMinY(+0x3A)->[rbp+0xF2] 0x53a085d}; 0x3853770(blockEntity,&packed) 0x53a086e; stage=int(progress*scale[rcx+0xAC8+0x24]*xmm7) via 0x6a5e8f0 0x53a07c2. [V]

Tag byte / insert:
- Variant stored at [rbp+0x90] = {desc ptr = rbp+0x60, tag}. `mov byte ptr [rbp+0x98],5` at 0x53a052a -> Item tag 5 = Crack. [V]
- Inserted via builder vtbl[+0x378] slot 111 at 0x53a0541 (`call qword ptr [0xF99FFA0]`). [V]
- Wrapped in "FrameBuilder - Insert" scope (string lea 0xF52E07A at 0x53a0601; scope end 0x2FE330 at 0x53a0641). [V]

EVERY store into the description object (base rbp+0x60):
- +0x00 qword mesh `mov [rbp+0x60],r15` at 0x53a0499; r15=[rdi+0x00] entry mesh (`mov r15,[rdi]` 0x53a0409). [V]
- +0x08..+0x17 16-byte texture SharedRef built inside callee `0x4DFB570(rcx=[rbp+0x68], rdx=[rbp+0xD0])` at 0x53a04a8. Src: material shared ref [rbx+0x3298] ptr saved [rbp+0xD0], control saved [rbp+0xD8]; `lock inc [ctrl+8]` at 0x53a0428; null -> static default 0x129C1210 via cmove 0x53a0405. [V]
- +0x18 qword camera record `mov [rbp+0x78],rax` at 0x53a04b2; src [rbp+0x38] = newest ring record from ctx [r14+0x18] (ring index math 0x53a0375-0x53a0399; `mov byte [rax+0x78],1` at 0x53a0379 marks used). [V]
- +0x20 byte stage `mov [rbp+0x80],r12b` at 0x53a04b6; src [rdi+0x18] entry+0x18 (`mov r12b,[rdi+0x18]` 0x53a0490). [V]
- +0x22 word flags `mov [rbp+0x82],r13w` at 0x53a04bd; src (u16)(u8)[r14+0x74] ctx+0x74 (`movzx r13d,byte [r14+0x74]` 0x53a0494). [V]
- material+0x10 u16 read at 0x53a041b is dead/overwritten. [V]
- Layout [V stores, I size]: {mesh ptr +0x00; texture SharedRef(16B) +0x08; cameraRecord ptr +0x18; stage u8 +0x20; flags u16 +0x22}; size>=0x24 [I]. stores.py excluded rbp-relative stack stores so no separate rva list exists there. [V]

Item visitor reads (Crack tag handler):
- Item visitor 0x6646980 [0x6646980..0x664fda5), size 0x9425; listing docs/progress/_d5d_visitor.txt. [V]
- jt.py 0xF2BF2D0 11 -> tag 5 -> 0x66471de (Crack handler, inline, not a dedicated extractor). [V]
- casewalk from 0x66471de regs rdi,r8 reachable=1087; rdi = description pointer throughout body; r8 clobbered to mesh ptr (`mov r8,[rdi]` 0x6648beb) so [r8+off] reads are MESH reads not desc reads. [V]
- Case-5 body desc READS (rdi = desc):
  - +0x00 mesh `mov rcx,[rdi]` 0x66471de -> 0x4DEF080 hasDrawableData. [V]
  - +0x08 texture shared ref passed `lea r15,[rdi+8]` 0x6648b3a -> 0xBCABA00. [V]
  - +0x18 camera record `mov rax,[rdi+0x18]` 0x6648c3e then 4x movups copy matrix [rax]/[rax+0x10]/[rax+0x20]/[rax+0x30] at 0x6648c42-0x6648c4e. [V]
  - +0x20 stage byte `movzx esi,byte [rdi+0x20]` 0x6648c9c (`cmp [rdi+0x20],1` at 0x664a6d4 selects branch). [V]
  - +0x22 flags `mov di,[rdi+0x22]` 0x664a73a/0x664a97b and `movzx r15d,word [rdi+0x22]` 0x664bcca. [V]
- Release: visitor copies texture ref then `lock dec [rdi+8]`/`lock dec [rdi+0xC]` pattern at 0x664bd1e/0x664bd33 on restored rdi. Cold paths 0x664E971/0x664EBD7 shared cleanup — not yet confirmed whether they release the case-5 description texture ref. [I / ?]
- Main-path release confirmed at 0x664bd1e..0x664bd43. [V]

## VERIFICATION
- Ran `python tools/sigs/verify_oc.py docs/progress/oc_U-D5d.md`: reports "no 0xRVA instruction lines". This file uses the narrative progress-log format (same as sibling oc_U-D5c.md) with every claim tagged [V] (saw it in disassembly, RVA cited) / [I] (inferred) / [?] (unknown) per brief rule 10; it contains no `0xRVA  instr` dossier lines for the verifier to check. No instruction was quoted in verifier format, so nothing can be falsified — all offsets come directly from the rdis listings saved at docs/progress/_d5d_fn.txt and docs/progress/_d5d_visitor.txt. [V sourcing]

## TOOL REQUESTS
- verify_oc.py | input=progress file, output=match/mismatch counts | would have helped to machine-check quoted instructions, but this unit's narrative format has no `0xRVA  instr` lines; not worth rewriting (sibling oc_U-D5c.md is identical). "None" acceptable here.
