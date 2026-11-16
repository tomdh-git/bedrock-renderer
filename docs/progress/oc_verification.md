# opencode unit verification (Claude)
## U-E4-A2 (body A 0x66ed987..0x66ef28d) — ACCEPTED (spot-check)
Checked against exe with rdis dis: 0x66edc2f (movzx [rbp+0x1630]), 0x66edd1c (movups [rsi+0x1CC]), 0x66edd87 (dec eax), 0x66eddd6 (vcall flag setup), 0x66ede89 (mov [rbp+0x1130],0x2005009), 0x66eded7/0x66edede (cmp r12,[r15+0x778]; je 0x66edf24), 0x66edf24/0x66edf35 (lea r15+0x768; call 0x6760710), 0x66edfb0..0x66edfe9 (call 0x6760e60; ~[r15+0x2d0]+[r15+0x2d8] -> [rbp+0x11bc]), 0x66ee026 (shr eax,5), 0x66ee06f (call 0xeec6ec0): all match. No mismatches. Semantic [I] claims not accepted as facts. Not yet folded into dossier/checklist (E4 item stays open: bodies B-D and builders pending).

## U-GF (Gameface 0x66ade80, 0x66af0c0..0x66afe7a) — ACCEPTED WITH CORRECTION
Automated: tools/sigs/verify_oc.py compares every `0xRVA  instr` line to rdis dis. 291/293 instruction lines match exactly.
Mismatch: the file lists the 0x66af780..0x66af799 zeroing as five stores (+0x50,+0x40,+0x30 at 0x66af780/85/8a, then +0x20 at 0x66af794, +0x10 at 0x66af799); real is stores at 0x66af785 +0x40, 0x66af78a +0x30, 0x66af78f +0x20, 0x66af794 +0x10, 0x66af799 +0x00 (the +0x20 store at 0x66af78f was dropped and the two after it shifted). Net effect: [rax+0x00..0x5f] zeroed; the comment "zero rbp+0x220/0x230" labels are off by one slot. Use the exe, not the file, for this range.
Open per the file's own NEXT: Viewport write not located in 0x66af0c0..0x66af263 (only Data_VS/Data_PS via 0x5679db0 there).

## U-E4-C (body C 0x66f2820..0x66f4f5a) — ACCEPTED as walkthrough (not instruction-complete)
Seven 300-instruction steps cover the whole range, content is bullet-level with RVAs, not per-instruction phases (no `0xRVA instr` lines, so verify_oc.py has nothing to compare). Spot checks vs exe: 0x66f2c61 (lea rdi,[rbp+0x1444]), 0x66f2ce7 (lea r13,[rbp+0x1210]), 0x66f2d0e (cmp rsi,[rbp+0x16A0]), 0x66f2dba (lea rcx,[rbp+0xE10]) all match. Key claim kept as [V]-pending: bodies B/C share body A's skeleton; difference = [rbp+0x1658] holds K&~1 (B, C) instead of &desc+0x78 (A), and the kind-class compute has no f16cf recheck. Checklist E4 stays open (instruction-complete requirement).

## U-E4-B (body B 0x66ef308..0x66f2817) — PROVISIONAL (walkthrough, low RVA density)
File claims "instruction-complete" but cites only ~42 distinct RVAs in 230 lines and has no `0xRVA instr` lines to auto-check; treated like U-E4-C: usable as a description of differences vs body A (K&~1 in [rbp+0x1658]; no f16cf recheck in kind-class compute), not as instruction-complete. Not folded into the dossier as [V] beyond those two diffs, which match body C independently.

## U-PASS (consumer of pass-object pools) — PARTIAL / NEGATIVE RESULT, consumer NOT found
Claims spot-checked: 0x833e30 reads [rsi+0x8A0] at 0x83657d (match, rdis fld); 0xc1cb60 callers are sub_c0a050 and sub_842a010 (rdis callers), NOT sub_36bc250/3722fe0 (those call sub_c21db0, per file; unchecked). Useful leads only: sub_c21db0 copies and sub_833e30 destroys a struct with the pass-object pools (same element type?); getter 0x5aba5c0 callers (95) are all pushers. Follow-up U-PASS2 delegated to trace owner container/consumer. E2 blocker remains open.

## U-NT (nametag producer 0x11276b0, 4 ranges) — ACCEPTED
verify_oc.py: 400/400 quoted instruction lines match the exe, 0 mismatches. Interpretations are [I] until folded by the merge agent; ranges 0x11278c5..0x1127b06, 0x1127c35..0x1127d23, 0x11283d3..0x11285f4, 0x112888e..0x1128a40 are covered.

## U-E4-D (body D 0x66f4fcb..0x66f6e36, K==10 terrain_blend) — PROVISIONAL (walkthrough)
Same format as B/C (bullet walkthrough, no checkable instruction lines). With B, C, D all walkthrough-grade, extractor 0x66ea3d0 bodies A..D are now covered end to end: A instruction-complete (accepted), B/C/D differences-vs-A only. E4 stays open until the builders (0x67762e0/0x670b6e0/0x6722cb0) and mask/pool tables are done.

## U-IH (ItemInHand extractor 0x6698e30 ranges) — ACCEPTED for covered part
verify_oc.py (now accepts lines with or without `0x`): 503/503 instruction lines match. File's own NEXT shows the unit is incomplete: callees 0x67d14e0 (after 0x67d16e2) and 0x673cc80 (after 0x673cdfd) not finished -> continuation delegated.

## U-UI5 (UI extractor 0x674a3a0 from 0x674b4d9) — ACCEPTED for covered part (0x674b4d9..~0x674d2cd)
verify_oc.py: 693/696 match; 3 trivial (two `nop` omitted before a jmp at 0x674bccc/0x674bdb0 with correct jmp target; one typo in operand `[rbp[d28]` at 0x674c7d8). Unit stopped before the cold tails (0x674d2cd.., FNV loop 0x674dd58, blocks 0x674e3c0..0x674e707); the file's NEXT lists them and one open [?]: predecessor of 0x674bb0c. Continuation delegated.

## U-PASS2 — ACCEPTED (negative result, internally consistent, key claims re-checked above via rdis callers)
Rules out sub_c21db0 / sub_833e30 / sub_c1cb60 as pass-object consumers: they handle ~0xD30-stride / 0x2010-byte objects (caller sub_842a010 is vex-behaviour AI code); `imm 0x8B8/0x8C8` add-loops (0x2210ac, 0x289d1e, 0x8801224, 0xc06d1dc, 0xc07209c) do not read the pool offsets. The five displacements were coincidences with another struct. E2 blocker (who drains pass+0x648/0x750/0x768/0x780/0x8a0) stays OPEN; next idea: the pass object is probably consumed through a different base (vector element accessors / 0x5aba6d0 / memcpy 0xeec6ec0 of 0xc8 records) -> trace readers of the 0xC8-byte records, not of pass fields.

## U-E4-F1 (builder 0x67762e0, first 800 instr: 0x67762e0..0x677736d) — ACCEPTED
verify_oc.py: 778/778 quoted instruction lines match the exe, 0 mismatches. (The NEXT block in the file is stale; coverage ends at 0x677736d.) Next: F2 from 0x677736e.

## U-ED (editor extractor callees 0x66a6060, 0x66a6190, 0x66a6470, 0x66a65b0, 0x67d3850, 0x67d2f80) — ACCEPTED
verify_oc.py: 1018/1018 quoted instruction lines match the exe. All six functions transcribed end to end with bounds (0x66a6060..0x66a6182, 0x66a6190..0x66a63af, 0x66a6470..0x66a65b0, 0x66a65b0..0x66a66f0, 0x67d3850..0x67d3d20, 0x67d2f80..0x67d34ea). 0x67d3850/0x67d2f80 are pass-builders (9 sub-buffer entries + queue append), 0x66a6470/0x66a65b0 mirror record cleanups. Interpretations [I]. Open per file: struct layouts of the pass-buffer sub-entries. No dedicated checklist line for these callees (feeds M1d / R11 Editor tags); stays open until the editor extractor 0x66a1860 itself is closed.

## Gameface Viewport write — RESOLVED by Claude (static, rdis xr 0x5679db0)
The 0x5679db0 uniform writer is called three times in sub_66ade80: 0x66af049 (Viewport), 0x66af18d (Data_VS), 0x66af25d (Data_PS) [V]. The Viewport block is 0x66aefab..0x66af04f, i.e. just BEFORE the range given to U-GF: statics data_129f8f10 (name hash) / data_129f8f18 (init counter, TLS guard at 0x66aef86..0x66aefa5, cold init 0x66b0134), 1 vec4 {size=1 element, data = [rbp+0x2F0] copied to [rbp+0x320]} (0x66aefab..0x66aefcb), slot lookup in table [rbp+0x90] stride 0x10 with count word [rbp+0x9A] (0x66aefd2..0x66af029), then 0x5679db0(&rbp+0x60, {slot idx u16 [rbp+0x4C0], flag byte [rbp+0x4C2]=1}, &rbp+0x208) at 0x66af049. Data_VS/Data_PS use the identical sequence with data_129f8f20/28 and 0x80-byte blocks [r15+0x50]/[r15+0x60]. Source of the Viewport vec4 [rbp+0x2F0]: not traced yet.
Viewport vec4 source [V]: 0x66ae227 `movups xmm0,[rsi+0x58]` -> `movaps [rbp+0x2F0],xmm0` (rsi = third argument r8 of sub_66ade80, set at 0x66adec4 `mov rsi,r8`); [rsi+0x68] is copied to the next local right after (0x66ae232). Initialised to zero at 0x66adeff..0x66adf0d. Consumed at 0x66aefab (Viewport uniform) and 0x66af717 (pass-entry words). So the Viewport uniform = the 16 bytes at description(+0x58) of the Gameface description argument. Gameface Viewport item: closed at instruction level (statics data_129f8f10/18).

## U-PASS3 (readers of the 0xC8-byte DrawItem records) — ACCEPTED, E2 PARTIALLY RESOLVED
verify_oc.py (now clusters claims; was timing out on scattered RVAs): 54/54 quoted instruction lines match. Callers re-checked with rdis: sub_bbdad00 <- sub_67c9970 (1 site); sub_bbbfc50 <- sub_55f1450, sub_bbc9db0, sub_bbd25f0, sub_bbe2d50. Findings (instruction-level [V], roles [I]): three real consumers of 0xC8 DrawItem records: (1) sub_bbdad00: two stride loops 0xbbdb190 / 0xbbdb3a0 (`add reg,0xC8`), reads mask +0x00, u16 +0x10, u16 +0x2A -> pool +0x750 stride 0x88 with material compare at +0x78; (2) sub_bbbfc50 (NothingTask body 0xbc38c20 family): loops 0xbbbfeb0 / 0xbbc00ff, reads +0x28/+0x3C/+0x10/+0x2A, emits {index, DrawItem*, ..} entries and submits via 0xbcc38e0; (3) sub_562bb00: reads +0x28/+0x2A/+0x2C/+0x50/+0x52 of one record, calls sub_bcd77b0 / sub_bcdba70 (submit path). So the E2 "who drains" answer is: the record stream is consumed in the 0xbb.. VV task bodies and 0x562bb00 (not in the pass object itself). Still open: pool vector drain semantics (what it does with pools +0x648/+0x768/+0x780/+0x8a0), tag meanings, P+0x50/+0x51 consumer.

## U-UI5 (UI extractor 0x674a3a0, whole function 0x674a3a0..0x674f006) — ACCEPTED
verify_oc.py: 1806/1811 quoted instruction lines match. The 5 misses are transcription noise: two omitted `nop` before a jmp (0x674bccc, 0x674bdb0; targets correct), operand typos at 0x674c7d8 (`rbp[d28]`) and 0x674e3cc (`[0.129fa2a0]`), and one line at 0x674dadc that sits mid-instruction (inside `lea rcx,[0x567DBA0]` at 0x674dada; cold static-guard area). Coverage claim (hot path ret 0x674ce4e, switch cases 0x674b559/0x674b71a/0x674b85d/0x674b9b2, kind>3 default 0x674e428, cold tails to 0x674f001, next function starts 0x674f006) is consistent with rdis. The open [?] predecessor of 0x674bb0c is resolved per the file's final NEXT (UNIT COMPLETE).

## U-E4-F2 (builder 0x67762e0, 0x677736e..0x6778c1a) — ACCEPTED
verify_oc.py: 796/797 (one wrong line: 0x67785b7 claimed `mov [rbp+838],al`, real `mov eax,[r13+8a8]`; treat that line as wrong). Covers ~700 instructions; builder continues from 0x6778c1a (F3).

## U-E4-G1 (builder 0x670b6e0) — PARTIAL, ACCEPTED for what it covers
verify_oc.py: 317/317 quoted lines match, but the file only covers 0x670beaa..0x670c5a6 (its phases 28..~42, "identical to F1 phase N" comparisons: same pattern, different slots/registers); the start 0x670b6e0..0x670bea9 and a NEXT block are missing (file was apparently rewritten by the re-delegated session). Follow-ups: U-E4-G0 (0x670b6e0..0x670beaa) and U-E4-G2 (from 0x670c5a6).

## U-PASS4A (sub_bbdad00 0xbbdad00..0xbbdcdc5, size 0x20c5) — PARTIAL, ACCEPTED for covered part
verify_oc.py: 430/431 (typo `mov rdx,ccccccccccccccd` at 0xbbdafe0, real 0xcccccccccccccccd). Coverage only 0xbbdad00..0xbbdb59a (phases 1-27, ~25% of the function); the file's NEXT is stale; the unit also wrote helper dumps docs/progress/u-pass4a-*.txt (raw rdis output, harmless). Seen so far [V from quoted lines]: list walk with magic-multiply count (/0x...cd = divide by 5?), pool object + sub_a78940 alloc, refcount releases, output slot write, record valid-mask filter, u16 pool-index lookup at +0x10, output-buffer flush, sub_eec6de0 copy, sub_5689800 final flush. Continuation from 0xbbdb59a delegated (U-PASS4A2).

## U-IH (ItemInHand extractor 0x6698e30: ranges 0x669c35f..0x669c8f9, 0x669be56..0x669bef8, 0x669c8f9..0x669c9e2, callees 0x67d14e0 (to its ret 0x67d253a) and 0x673cc80) — ACCEPTED
verify_oc.py: 1340/1340 quoted instruction lines match the exe, 0 mismatches. The unit's scope is complete; the checklist items D5e/L4i/M1d still need the dossier's other pending ranges (docs/functions/6698e30.md "Pending (OPEN)": 0x669b4b9..0x669cc4b is only read at control-flow level) before they can be ticked.

## U-E4-G0 (builder 0x670b6e0, 0x670b6e0..0x670bb20) — ACCEPTED, GAP REMAINS
verify_oc.py: 202/202 match (phases 1..15). The file's NEXT says "resume at 0x670beaa" but it only covers to 0x670bb20; gap 0x670bb20..0x670beaa remains (U-E4-G0b).

## U-E4-G0b (builder 0x670b6e0, gap 0x670bb20..0x670bea3) — ACCEPTED
verify_oc.py: 170/170 match. With G0 (0x670b6e0..0x670bb20) and G1 (0x670beaa..0x670c5a6) the builder 0x670b6e0 is now covered instruction-level from its entry to 0x670c5a6 (join 0x670bea3..0x670beaa is a single `jmp`-class boundary, no instruction skipped per the three files' phase boundaries). Remaining for 0x670b6e0: from 0x670c5a6 (U-E4-G2 running). Builder 0x6722cb0 not started.

## U-PASS4B (sub_562bb00 / sub_55f1450 context) — ACCEPTED with CORRECTION to U-PASS3 candidate 3
Checked with rdis: sub_55f1450 = [0x55f1450..0x563f594) size 0x4e144 (a ~320 KB function, 0 direct callers); 0x562bb00 is INTERIOR to it, not a function start (the file's first bytes at 0x562bb1b decode as garbage because it enters mid-function; real decoded code starts at 0x562bb27 `mov rdx,rcx` / 0x562bb2a `call 0x56BA620`). So "sub_562bb00" in U-PASS3 is a region inside sub_55f1450, not a separate consumer. Verified [V]: 0x55f16b0 `mov qword ptr [rbx],0` / `mov [rbx+8],r14` / `mov [rbx+0x10],r13` / `add rbx,0x18` writes 0x18-byte entries {0, DrawItem*, r13}; 0x55f16c3 `add r14,0xC8; cmp r14,rcx; je` is the record stride loop. Callees sub_bcd77b0 and sub_bcdba70 are render-graph pass bodies keyed by pass-name strings ("CubemapTransfer" f56e968 xref sub_bcd77b0+0x7e confirmed; "Core/Screen/Blit", "SpecularConvolution"), calling sub_567c8b0 (pass lookup by name), not bgfx submit calls. Record fields read in the region (+0x08 refcounted, +0x20 byte, +0x24, +0x28/+0x2A/+0x2C u16 pool indices, +0x30, +0x50 u16, +0x52 dword) are [V] per its table (not all individually re-checked). E2 progress: the consumer of the 0xC8 records is the giant sub_55f1450 stream (loop 0x55f16c3) which builds {0, DrawItem*, pass*} entries, later read by the 0xbbbfc50/0xbbdad00 task bodies. Pool/tag meaning still open.

## U-E4-G2 (builder 0x670b6e0, 0x670c5a6..0x670d6c6, 800 instr) — ACCEPTED (2 line errors)
verify_oc.py: 797/799; wrong line 0x670ca51 (claimed `movaps [rbp+420],xmm6`, real `[rbp+430]`), 0x670d574 operand formatting (`0718` vs `718`). Builder 0x670b6e0 now covered 0x670b6e0..0x670d6c6 at instruction level; resume point 0x670d6cc (G3).

## Builder template similarity (Claude, rdis `dis`, difflib on mnemonic sequences)
Instruction counts to function end: 0x670b6e0 = 5992 instr (end 0x6713c64), first 4500 of 0x67762e0 and 0x6722cb0 compared. Mnemonic-sequence ratio (first 4500 instr): 0x67762e0 vs 0x670b6e0 = 0.854, 0x67762e0 vs 0x6722cb0 = 0.853, 0x670b6e0 vs 0x6722cb0 = 0.768. The three builders therefore share one template (~85% identical mnemonic stream); the effort of the remaining units should concentrate on the differing regions (use `difflib` opcodes on the mnemonic streams) rather than re-transcribing every instruction. Sizes: 0x67762e0 = 0x7e86 bytes, 0x670b6e0 = 0x8584, 0x6722cb0 = 0x77b4.

## U-PASS4A2 (sub_bbdad00 0xbbdb59a..0xbbdcdc5 + caller sub_67c9970) — ACCEPTED with noise (1068/1079)
verify_oc.py: 1068 match; 11 misses are transcription noise (garbled 7-digit RVAs like 0xbbdbad / 0xbbdbba19, constant typos `ccccccccccccccd` for 0xcccccccccccccccd at 0xbbdb9af / 0xbbdafe0). Together with PASS4A (0xbbdad00..0xbbdb59a) the function sub_bbdad00 [0xbbdad00..0xbbdcdc5) is covered. Caller sub_67c9970 re-verified against rdis: `sub rsp,0x38; mov r8,[rcx+0x30]; mov rax,[rcx+0x10] (+ lock inc [rax+8] if non-null); mov rcx,[rdx+8]; add rdx,0x18; ...; lea rcx,[rsp+0x20]; call 0xBBDAD00` -> sub_bbdad00(rcx=&{[in+8],[in+0x10]}, rdx=in+0x18, r8=[in+0x30]). Pool +0x750/+0x78 compare: three sites 0xbbdb69c-6ae, 0xbbdc02c-3e, 0xbbdcabc-5e (u16 [rec+0x2A]*0x88 into pool table, compare field +0x78). Output: slot arrays of {0, count, slot_base} 0x18-byte entries copied via sub_eec6de0, pool allocator sub_a78940. Roles [I].

## U-E4-F3 (builder 0x67762e0, 0x6778c1a..0x677a4d0) — ACCEPTED
verify_oc.py: 1248/1248 match, 0 mismatches. Builder 0x67762e0 now covered 0x67762e0..0x677a4d0 (of end 0x677e166, ~65%); resume 0x677a4d4 (F4).

## U-PASS5 (2026-11-15)
verify_oc: claimed=178 match=178 mismatch=0. ACCEPTED (instruction quotes); semantic claims still [I] where tagged.

## U-SK2 pass 2
verify_oc: 349/351 match, 2 no-such-instr (0x6659815, 0x6659817: transcription garbage, drop). Cubemap case end NOT located; E1-E4 accepted, C1-C6 accepted except those two lines. Continue from 0x6659a75.

## U-SK1 pass 2
verify_oc: 1384/1414 match, 5 mismatch, 25 no-such-instr (join-3 tail 0x665bd31..0x665c272 corrupted; file self-reports corruption). Accept only matching lines; join-3 parts 4/5 must be redone. All Kilo keys capped at this time (ensurekey NO_WORKING_KEY); re-delegate after recovery.

## U-E4-F4 (partial)
verify_oc: 592/600 match, 8 no-such-instr (0x677a791..795, 0x677adfd..ae0f: garbled). Accepted except those 8 lines; 0x67762e0 covered to 0x677b05d. Failed by quota; resume at 0x677b05d (end 0x677e166) when keys recover.

## U-E4-H1 (partial)
verify_oc: 594/602 match, 8 mismatch. Accepted except mismatched lines; 0x6722cb0 covered to ~0x6723971. Failed by quota; resume at 0x6723971 when keys recover.

## U-E4-G3
verify_oc: 619/619 match. ACCEPTED. 0x670b6e0 covered to 0x670e94f; next unit G4 resumes at 0x670e955 (end 0x6713c64).

## U-SK2b
verify_oc: 152/152 match. Claims DONE (Cubemap exits via 0x665aee8 -> jmp 0x665d124) but only 152 quoted instructions cover 0x6659a75..0x665aee8 (~1300 instr): NOT instruction-complete. Lines accepted; case structure/exit [I]. Not ticked.

## U-SK1b (partial)
verify_oc: 694/694 match. ACCEPTED for what it covers (join-3 tail redo through 0x665c251). Open: 0x665c272.. residual, cold range 0x665cf64..0x665d7e5.

## U-E4-H2
verify_oc: 799/800 match, 1 mismatch (0x6724a43 is `mov rcx,[1233e1b0]`, not lea). ACCEPTED with that correction. 0x6722cb0 covered to 0x6724a4a; H3 resumes 0x6724a4d.

## U-E4-G4
verify_oc: 777/779 match; 2 mismatches are direct jmps mis-quoted as `jmp qword ptr` (0x670f221 -> 67139a0, 0x670f609 -> 6710c20). ACCEPTED with correction. 0x670b6e0 covered to 0x670f92b; G5 resumes there.

## U-E4-F5 (partial)
verify_oc: 507/519 match, 12 no-such-instr (garbled around 0x677b1e3..). Accepted except those; 0x67762e0 covered to 0x677bb27 minus garbled spots (redo ~0x677b1e0). F6 resumes 0x677bb27.
## U-E4-H3 (partial)
verify_oc: 279/280 match, 1 garbled (0x6724bf8). Covered to 0x6724fff; H4 resumes 0x6725004.

## U-E4-F6
verify_oc: 806/824 match, 18 no-such-instr (garbled spots incl. 0x677bdf0..; verify list). ACCEPTED except those; 0x67762e0 covered to 0x677ca98 (garbled 0x677b1e0 redone). F7 resumes 0x677ca98 + redo garbled spots; end 0x677e166.

## U-E4-G5
verify_oc: 800/800 match. ACCEPTED. 0x670b6e0 covered to 0x67108da; G6 resumes there (end 0x6713c64).

## U-E4-F7 (partial)
verify_oc: 176/181 match; 5 no-such-instr at 0x677c4d0.. are unaligned starts inside the garbled-area redo (those RVAs are mid-instruction; F6 lines there are invalid, not real code). Covered to 0x677cdb6; F8 resumes there (end 0x677e166).

## U-E4-G6
verify_oc: 800/800 match. ACCEPTED. 0x670b6e0 covered to 0x6711806; G7 resumes (end 0x6713c64).

## U-E4-F8 (partial)
verify_oc: 80/80. covered to 0x677cf26; F9 resumes.
## U-E4-H4
verify_oc: 725/732, 7 garbled lines. Covered 0x6725004..0x672604d. H5 resumes 0x672604d.

## U-SK1c (partial)
verify_oc: 1040/1040 match. ACCEPTED. Residual tail 0x665c276..0x665cf64 complete; cold range 0x665cf64..0x665d5d1 done; remaining 0x665d5d1..0x665d7e5.

## U-SK3
verify_oc: 1041/1073 match, 32 no-such-instr (garbled spots listed by verify; includes 0x6656b81, 0x6656d0a.., 0x6656f06, 0x6656fef, 0x665721c.., 0x6657387, 0x665746c, 0x66574f6). Accepted except those. SkyAmbientSamples 0x665708b..0x665803c phases 1-21; VolumetricFog 0x66569b1..0x6657da4 phases 22-46; tail 0x6657da4..0x6657e4a pending.

## U-E4-G7 (partial)
verify_oc: 200/200 match. ACCEPTED (0x6711806..~0x6711c03, 5 phases; NEXT block stale). G8 resumes at 0x6711c03.

## U-SK3b
verify_oc: 150/151 match, 1 mismatch (0x6657386 is `lea rdx,[rax+27]`, not edx). ACCEPTED with that fix. The 12 listed garbled SK3 spots are all redone; 20 further garbled SK3 lines not listed by verifier (it prints first 12 only): SK3 stays [~] until those are re-checked.

## U-SK1d
verify_oc: 53/53 match. ACCEPTED. Cold range 0x665cf64..0x665d7e5 complete (SK1c + SK1d).

## U-SK1e
verify_oc: 65/65 match. ACCEPTED. Gaps 0x665bc70..0x665bd31 and 0x665c240..0x665c2d0 filled. U-SK1 family (SK1, SK1b, SK1c, SK1d, SK1e) now covers sky Stars joins + cold range 0x665cf64..0x665d7e5 with the corrections listed above: eligible for merge.

## U-SK3c
verify_oc: 209/209 match; all 10 remaining SK3 garbled neighborhoods present. ACCEPTED. U-SK3 family (SK3+SK3b+SK3c) complete for SkyAmbientSamples 0x665708b and VolumetricFog 0x66569b1: eligible for merge.

## U-E4-H5
verify_oc: 812/820 match, 1 mismatch, 7 no-such-instr (the 0x6725c58..6b neighborhood, still garbled; 0x67258ec/0x67259cb redone). ACCEPTED except those. 0x6722cb0 covered to 0x6726f07; H6 resumes there.
Correction (Claude, rdis): real lines 0x6725c4b..0x6725c70: 6725c4b mov rcx,[0x1233E1B0]; 6725c52 mov rax,[rcx]; 6725c55 mov rax,[rax+0x10]; 6725c59 mov dl,0x4A; 6725c5b call qword ptr [0xF99FFA0]; 6725c61 nop; 6725c62 mov [rbp+0x818],al; 6725c68 mov rdx,[r14+0x68]; 6725c6c cmp rdx,[r14+0x70]; 6725c70 je 0x6725FEB. Builder 0x6722cb0 ends 0x672a464.

## U-E4-F9
verify_oc: 922/929 match, 7 garbled (0x677dcab, 0x677dcad, 0x677dece, 0x677e0d7 ...). Builder 0x67762e0 now reaches its end 0x677e166 across F1..F9. ACCEPTED except garbled spots; fixup unit F10 covers all garbled spots of F4/F5/F6/F7/F9.

## U-E4-G8
verify_oc: 1093/1093 match. ACCEPTED. Builder 0x670b6e0 reaches end 0x6713c64 (G0..G8). Gap check follows.

## U-SK2c
verify_oc: 915/916 match (1 junk line 0x665abf4). cov_oc: Cubemap case 0x6659615..0x665aee8 has 5 real instructions unquoted; supplied here from rdis by Claude:
0x6659e08 mov r8,[0x129F9FE0]; 0x6659e0f mov r9,rdx; 0x6659e12 mov rcx,rax; 0x665a9ec jmp short 0x665AA02; 0x665abf3 movups xmm2,[rbp+0x38B] (reads a0 +0x38B, written to [rdx+0x47]).
ACCEPTED: U-SK2 family (SK2, SK2b, SK2c) instruction-complete for Cubemap case; EndSky/LegacyCubemap 0x6656b2b..0x6656d4d done in SK2 E1-E4. Eligible for merge.

## U-E4-G9
verify_oc: 383/388 match, 1 mismatch + 4 junk at 0x670f3cd..0x670f3d4. cov_oc over G0..G9: 6718 real instructions, all but 2 quoted. Real lines supplied by Claude from rdis: 0x670f3cd lea rcx,[r12+0x630]; 0x670f3d5 lea r8,[rbp+0x5B8]; 0x670f3dc call 0x14DB710 (sub_14db710); 0x670f3e1 nop.
ACCEPTED: builder 0x670b6e0 (G0..G9) is instruction-complete with these corrections. Eligible for merge (E4 body-C/builder-G part).

## U-E4-F10
verify_oc: 377/386 match; 9 mismatches are cosmetic (near `je`/`jmp` quoted as `short`, e.g. 0x6778119 je 6778687). cov_oc over F1..F10: 6337 real instructions, 0 unquoted. ACCEPTED: builder 0x67762e0 (F1..F10) is instruction-complete. Eligible for merge.

## U-L8 (partial)
verify_oc: 728/731 (2 mismatch 0x67ceeeb is mov rsi,rdx; 1 junk). Contains raw first-160-instr dumps of 0x67ceb40/0x67ceed0/0x95ed00/0x4e198d0/0x4e1cbb0 and caller counts (4e198d0: 5, 4e1cbb0: 1; others 0 direct callers = virtual/indirect). Does NOT identify the image builder/PNG decoder: L8a/L8b remain open.

## U-BA1
verify_oc: 1355/1355 match. ACCEPTED. bodyActor 0x66d0a00 covered 0x66d0a00..0x66d23a1 (1355 instr; NEXT block stale). BA2 resumes 0x66d23a3 (function end ~0x66d7d8b).

## U-E4-H6 (partial)
verify_oc: 774/790 match, 16 junk lines. cov_oc H1..H6 over 0x6722cb0..0x672a464. Covered through ~0x6727ad8; gaps below that (0x6724b25, 0x67258eb, 0x67259c6, 0x6725c59..0x6725c6c, 0x6725ed3..0x6726047, 0x67263c1..0x6726486, 0x6726a82..0x6726aab, 0x6726cb1, 0x6726d60..6a, 0x6726e02..22, 0x6727308, 0x6727562, 0x672779c, 0x6727a23..3c, 0x6727e10) tracked in docs/progress/gaps_6722cb0.txt. H7 resumes 0x6727ad8.

## U-SK4
Format: inline backticked instructions (no per-line RVAs), so verify_oc cannot machine-check; Claude compared the whole range by eye against rdis dis 0x6656812 90: every instruction 0x6656812..0x665697e is present and in order (TLS guards, [rsi+0x70] cmove material select, call 0x675E440, loaded-flag [r14+0x10], refcount retain/release, jmp 0x6657562). ACCEPTED: Stars head 0x6656812..0x665697e instruction-complete; it reads no description fields (only frame ctx [rsi+0x40]/[rsi+0x68]/[rsi+0x70]).

## U-L8b
verify_oc: 263/264 match (1 mismatch 0x779ae0b is `movaps [rbp+0x790],xmm6`). ACCEPTED as research notes: image decoder = sub_777ed0 (multi-format stb-style loader: PNG sig 0x89 at 0x777f55 "bad png sig" 0x7784be, BMP 'B''M' checks, TGA via 0x1474780/0x1475480, IHDR via sub_781550); decode ctx r15: +0 width, +4 height, +8 components, +0xB8 consumed, +0xC0/+0xC8 cursor/end [V]/[I]. Callers 0x7647c0 / 0x764950 <- 0x19944b0, 0x1994f90, 0x167d050. "Failed to load the contents of file %s" at 0x779adf0. Texture-group/ClientTexture path (L8a) and atlas stitching (L8b) remain open.

## U-BA2 (partial)
verify_oc: 513/520 match (7 junk/mismatch at 0x66d2514, 275e, 2761, 28da, 2ca2, 2ca4, 2d3a). Covered 0x66d23a3..0x66d2d4f. cov_oc: tiny gaps at 0x66d2513, 0x66d275f, 0x66d2ca0, 0x66d2d3e; the rest 0x66d2d50..~0x66d7d8b open (BA3+). 

## U-SK6
Format: prose with inline instructions (not machine-verifiable). Claude generated the exact rdis listing docs/data/listings/sky_tag5_66574d8.txt (225 instr, 0x66574d8..0x66578db) via the new tools/sigs/dumplist.py; SK6's headline claims match it: preamble test r14,r14 / je 0x665AEE8, exit `jmp 0x665D154` at 0x66578db. Description field reads in this body: none (only frame ctx [rsi+0], locals, ctrl-block refcounts). ACCEPTED at structural level (use the listing as the instruction-complete source); undecoded branch targets 0x6658445, 0x665845A, 0x66585B4, 0x66585C9, 0x66587CF, 0x66587E4, 0x6657717 remain open.

## U-SK5b
verify_oc: 320/320 match; cov_oc: 283 real instructions 0x6658ffc..0x6659615 all quoted. ACCEPTED. Stars base draw instruction-complete.

## U-SK5b result use
Range 0x66580f0..0x6658ffc (806 instr) was never covered by any unit and holds the Stars/Celestial/other case bodies that read the description ([rdi+0x18/0x28/0x38/0x48/0x50/0x58...]). Claude generated the exact listing docs/data/listings/sky_66580f0_6658ffc.txt (dumplist.py) as the instruction-complete source; interpretation pending (sky merge #2).

## U-E4-H8
verify_oc: 165 claimed; 153 "mismatch" are only trailing inline // comments (instructions identical) so effectively 165/165. cov_oc H1..H8 over 0x6722cb0..0x6727ad8: all quoted except 1 instruction (0x6726cb1, listed below). ACCEPTED: builder 0x6722cb0 is instruction-complete up to 0x6727ad8; H7 continues to 0x672a464.
Supplied by Claude: 0x6726cb0 mov rcx,rdi (the single unquoted instruction 0x6726cb1 is the tail of this one).

## U-L8c
verify_oc: 49/49 quoted lines match (rest is inline-prose format). ACCEPTED as research notes: stb-style chain sub_777ed0 (decode) <- sub_764950 (returns RGBA32 buffer w*h*4, guard sub_764E50) / sub_7647c0 (16->8 bit conversion) <- sub_1994f90 (loads [a4,a4+a5) bytes, comp in {1,3,4}) / sub_19944b0 (stream-reader ctor). Texture-loader candidate in the caller tree: 0x6632fd0 (ref "look_up_tables.png" at 0x6633ebf, level 2 of 0x1994f90). L8a (pack -> TextureGroup/ClientTexture -> GPU) still open.

## Sky merge #2 (Claude agent)
D6a and D6b TICKED in RENDER_CHECKLIST.md. Spot check by Claude: tag-5 insertion verified at 0x536a2d8 `mov byte ptr [rbp+0x298],5` (producer inline in clone 0x536a2c8.. -> call [0xF99FFA0]). Open: D9b (Voxel/ShadowAtlas), I4b (pass strings), D6 Cubemap producer fields +0x60..+0xBF.

## D9b Light visitor (Claude agent, static)
docs/functions/6640d80_light_visitor.md: verify_oc.py 112/112 quoted lines match; 37/37 extra claims (insert call sites, tag byte stores 0x535a696/0x535a9b7/0x535ad34/0x535aeb9/0x53e5fb4, builder calls, engaged-byte stores, 0x67D5FF0/0x66AD820 reads) match rdis; __FUNCSIG__ strings of the four insert records and the 0x75740/0x75B60 throw strings read from the exe; jump table 0xF2BF2B0 parsed from the PE. D9b ticked.

## Light visitor merge (Claude agent)
D9b TICKED. Spot check: tag 4 (ShadowAtlasFrame) stored at 0x535a696 `mov byte ptr [rbp+0x278],4`; visitor 0x6640d80 prologue confirmed. Open: LightPoint (tag 3) fields, voxel builders 0x5AE5760/0x6B19E30 interiors, pass-vector consumers.

## U-L8d
verify_oc: 184/184 match. ACCEPTED as research notes. The 0x6632fd0 path is the RAY-TRACING lookup-texture loader ("look_up_tables.png", name "Ray Tracing Texture", registration into "RenderDragon Ray Tracing Textures" via 0x6622610), not the general resource-pack texture loader: sub_1994f90 -> pixels -> memcpy into a device-owned buffer ([device+0x288]+0x970..0x980) with deferred GPU creation. Callers of sub_6632fd0: 0x661a770, 0x66232b0. L8a/L8b/L8c remain open (general pack path unlocated).

## U-BA3 (partial)
verify_oc: 1052/1057 match (5 junk). cov_oc BA1..BA3: covered 0x66d0a00..0x66d42ad (tiny gaps 0x66d330f, 0x66d37a3, 0x66d3d7e); remaining 0x66d42ae..~0x66d69f6+ (BA4+). NEXT block stale.

## U-E4-H7 (partial)
cov_oc H7: covered 0x6727ad8..0x6728f54 with gaps 0x6727a44..0x6727ad3, 0x6727f8b..94, 0x67281a5, 0x6728242, 0x6728527, 0x67286b6, 0x67288e7..ee, 0x6728ce9, 0x6728db8, 0x6728e9b; remaining 0x6728f55..0x672a464: assigned U-E4-H9.
## Effects merge (Claude agent)
D7a/L4q ticked by agent (EffectDescriptions.h, docs/functions/effect_descriptions.md, BGFX_MAP 6ex; verify_oc 34/34). Claude REVERTED D7b/L4r tick: Shadow decoded only at field level, not instruction-complete. D7c/L4s open (FullscreenEffect tag-7 body 0x666b5cf.. ~3700 instr undecoded). Agent asked to finish both.

## UI/editor/enums merge (Claude agent)
D11/L4y and D12/L4z TICKED (FrameBuilder.h enums re-derived from tag stores; Nametag/MeshFallback asserts checked store by store; BatchActor head/spans decoded, kMinSize 0x100->0x110; agent reports cl /Zs syntax check of UiEditorDescriptions.h + FrameBuilder.h; 131 instruction claims re-run, 0 mismatches). D8/L4t (UIMesh/Gameface/HudIcon/UIImGui semantic fields) and D10/L4x (editor gizmo layouts, no proven struct size) left open. Claude verified the checklist file was not clobbered (ticks D6a/D6b/D9b/D7a and reverted D7b intact).

## FX1/FX2/FX3 (tag-7 body tables) 2026-11-15
- verify_tbl.py: FX1 ok=299 bad=824 (line numbers drift by 1 after ~line 536; RVAs/instrs correct but off-by-one lines; covers 475..825 only -> INCOMPLETE, needs redo 825..1700); FX2 ok=191 bad=32 (cosmetic/short jmps), covers 1710..2338 of 1700..2950 -> INCOMPLETE; FX3 ok=1230 bad=55 cosmetic, covers 2950..4252, no tag-7 end stated.
- Verdict: tables are field-read/branch tables only (not instruction-complete phases). D7c stays [ ].
- FX2 final: verify_tbl ok=289 bad=51 (shifted/cosmetic), selective rows (field reads/calls only), claims complete 1701..2950. Accepted as field-level only.
- H10 final: cov_oc 0x6722cb0..0x672a464 over H1-H10 real=6078, only gap 0x6726cb1 (mid-instruction, non-boundary; H8 states so). verify_oc no-such-instr=0, 965 mismatches are operand-format cosmetic (objdump-style vs rdis). ACCEPTED: builder 0x6722cb0 instruction-complete.
- FX1b: verify_tbl ok=396 bad=474 (row line numbers drift by 1; RVAs/instr real), covers 825..1700 field-level. FX4 in progress (4253..5252 so far).
- FX4 (4253..5403 ok=983 bad=159) + FX5 (5413..5869 ok=456 bad=1) accepted as line-complete tables; tag-7 hot path ends at listing line 4252 (jmp 0x6670032, [V] by sed); lines 4253..5869 are cold blocks branching back into body. D7c still [ ]: field meaning/layout synthesis not done and FX1/FX2 are selective.
- BA5 so far: 273 claimed, 3 junk at 0x66d4f8e..0x66d4f97 (phase 18 started mid-instruction), rest match.
- BA5 final: phases through 0x66d4f8d valid; from 0x66d4f8e all later phases JUNK (phase 18 started mid-instruction; 67 no-such-instr). Redo as BA6 from 0x66d4f8d.
- BA6 (0x66d4f8d..0x66d5904): 483 claimed, 483 match. ACCEPTED. BA7 continues.
- BA7 (0x66d5904..0x66d6558): 598 claimed, 598 match. ACCEPTED. BA8 continues.
- BA8 (0x66d6562..0x66d715a): 592 claimed, 592 match. ACCEPTED. BA9 continues to function end 0x66d7d8b.
- BA9 (0x66d715d..0x66d7d8b): 674 claimed, 674 match. BA1-BA9 + oc_U-BA_gapfill.md (28 boundary gaps filled from rdis): cov_oc real=5998 quoted=6082, residual 0x66d4a00..a05 is a mid-instruction artifact (true boundary 0x66d49ff->0x66d4a01). bodyActor 0x66d0a00 ACCEPTED instruction-complete.
- E4X units verified with tools/sigs/verbatim.py (exact line compare vs docs/data/listings/e4_{A,B,C,D}.txt): B1 700/700 ok; A1 772 quoted, 19 bad (agent retyped), 678/700 lines covered -> will gap-fill verbatim; B2 partial 553 ok 1 bad. Plan: per body, final gapfill file with missing listing lines.
- E4X bodies A-D: transcription units + verbatim gap-fill files oc_U-E4X-{A,B,C,D}_gapfill.md (listing copy); union.py shows 0 missing => bodies A-D instruction-complete (B3 retyped lines ignored, exact lines only). Interpretation pending synthesis.
- 2026-11-15 live: item tags 0,1,2,3,6,7,10 + ui 2,3 + sky 0,5,6,7 dumped (docs/data/live_desc_item_ui_editor_sky2_*.txt). Item tag 6 confirms ItemInHandDescription.h up to +0x17F; +0x180..+0x1FF still untyped.
