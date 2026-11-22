## NEXT
DONE

# U-EM3b — M3b Control flow: one frame from game logic to D3D12 submit

GOAL (checklist item M3b): trace one frame from game logic to D3D12 submit, every function on the path with a D2 dossier; the pipeline diagram in BGFX_MAP section 0 becomes a call-graph table with arguments at each hop.

Scope (this unit, pending parts only): A5 0x67c9c20 D1->D2, A7 0xc273420 D1->D2, B3 0xbc68840 D1->D2, resolve the two [?] links (task system -> A5; B5a submit -> executor wrapper 0xe83c390). M1d groups are separate units (docs/progress/PRIORITY.md) and are not touched here. A9 pass bodies are D0/D1 and remain out of this unit.

## 1. What changed (paths)

- docs/progress/oc_U-EM3b.md — this note (unit output file; no other file written for this unit)
- docs/functions/67c9c20.md — A5 "Frame renderer - Frame": full 0x966-byte body phased P1-P11, signature recovered, endFrame call + args verified [V], status D2
- docs/functions/c273420.md — A7 frame-graph generate/encode: signature, return shape, per-pass loop bounds 0xc277e8c..0xc2793fe, ordering stage 0xc27ab07..0xc27ac5f decoded; rest of 0x8A73-byte body left [I]/[?], status D2
- docs/functions/bc68840.md — B3 render-thread begin/init step: phased decode P1-P5, TLS magic 0x78666762 [V], callees 0xebce430/0xebdbc90/0xe951550, status D2
- docs/data/functions.tsv — status D1->D2 for 0xc273420 (line 31), 0x67c9c20 (line 38), 0xbc68840 (line 75)
- docs/FRAME_CALLGRAPH.md — rows A5/A7/B3 marked D2 with dossier refs; two [?] links resolved with verdicts below

## 2. Pending parts and verdicts

- A5 0x67c9c20 D1 -> D2: complete. Zero direct callers [V]; invoked through vtable slot 0 of .rdata vtable 0xf2beb90 [V]; dispatch mechanism (which task object/kind) [I]. Call to A6 at 0x67ca3cd with args rcx=*(this+0x20) bgfxCtx, rdx=[rsi+8]+[rsi+0x10]+0x268 DFR, r8=&rbp+0x38 Declarator, r9=&rbp+0xB0 allocator; names vector empty [V 6ep]. Dossier docs/functions/67c9c20.md.
- A7 0xc273420 D1 -> D2: complete for the decoded surface (signature [V addendum], ordering stage [V]); innermost dependency sub-steps remain callee-delegated [I]. Dossier docs/functions/c273420.md.
- B3 0xbc68840 D1 -> D2: complete, body 0xbc68840..ret 0xbc68e25 phased P1-P5; TLS render-thread identity cmp vs 0x78666762 "bgfx" magic [V]. Dossier docs/functions/bc68840.md.
- [?] link 1 (task system -> A5): RESOLVED. `rdis callers 0x67c9c20` -> zero direct callers [V]. .rdata vtable at 0xf2beb90 has sub_67c9c20 at slot +0x000 (push rbp, size 0x966) [V]; invoked via that vtable slot 0 by the task system. Dispatch mechanism [I] (task object/kind not recovered).
- [?] link 2 (B5a submit -> executor wrapper 0xe83c390): RESOLVED (negative). Submit body 0xe82e230 (0x4D91 bytes) contains no reference to 0xe83c390. At 0xe83159f submit does `lea r9,[0xE83C390]` (captures wrapper address) then `0xe8315ad  call qword ptr [0xF99FFA0]` — an indirect dispatch through the CFG thunk, rcx=obj via [0x12adf808], rdx=task object [rbp+0x1590], r9=&wrapper [V]. `rdis callers 0xe83c390` -> zero direct callers [V]; wrapper's sole callee is 0xe821120 [V]. Verdict: the executor runs as a dispatched job from submit, NOT as submit's direct callee.

## 3. Proof table: verbatim call-hop instructions (one row per offset; all sites listed)

| # | Hop (caller -> callee) | Offset | Size | Read/store address | Verbatim instruction | Meaning | Tag |
|---|---|---|---|---|---|---|---|
| 1 | A5 frame renderer -> A6 endFrame | 0x67CA3CD | 5 | imm 0xC270460 (direct call target) | `0x67CA3CD  call 0xC270460` | A5 calls A6 BgfxContext::endFrame(bgfxCtx=*(this+0x20), DFR=[rsi+8]+[rsi+0x10]+0x268, Declarator=&rbp+0x38, allocator=&rbp+0xB0); names vector empty [V] | [V] |
| 2 | A6 endFrame -> A7 frame-graph generate | 0xC270521 | 5 | imm 0xC273420 (direct call target) | `0xC270521  call 0xC273420` | A6 calls A7 0xc273420 with rcx=stack struct {rbx+0x38, rbx+0x40/+0x48 swapped pair, rbx+0x50} [V 6n] | [V] |
| 3 | A6 endFrame -> A8 task dispatch | 0xC270554 | 5 | imm 0xE9002E0 (direct call target) | `0xC270554  call 0xE9002E0` | A6 calls A8 0xe9002e0(taskList, rdx=stack struct {[rbx+0x20]+0x118, rbx+0x58, rbx+0x18}, r8=r15, r9=r12) [V 6n] | [V] |
| 4 | submit captures executor wrapper | 0xE83159F | 7 | imm 0xE83C390 | `0xE83159F  lea r9,[0xE83C390]` | submit (0xe82e230) loads wrapper address 0xe83c390 into r9; wrapper's sole callee is 0xe821120 [V]; no direct `call 0xe83c390` anywhere in submit [V] | [V] |
| 5 | submit indirect dispatch | 0xE8315AD | 6 | [0xF99FFA0] (indirect call target read here) | `0xE8315AD  call qword ptr [0xF99FFA0]` | submit dispatches through CFG thunk [0xF99FFA0] (rcx=obj via [0x12adf808], rdx=task object [rbp+0x1590], r9=&wrapper) — executor runs as dispatched job, not submit's direct callee [V] | [V] |
| 6 | B3 render-thread begin step | 0xBC68D01 | 5 | imm 0xEBDBC90 (direct call target) | `0xBC68D01  call 0xEBDBC90` | B3 multi-surface wait: rcx=wait table [rsp+0x40], edx=ebp(count), r8d=4, r9=callback 0xbc6af40; ebp==0 returns 0 [V] | [V] |
| 7 | B3 TLS identity check | 0xBC68D56 | 6 | [rsi] where rsi = gs:[0x58]+0x2D4C | `0xBC68D56  cmp dword ptr [rsi],0x78666762` | B3 compares TLS render-thread identity dword with magic "bgfx" = 0x78666762 [V] | [V] |
| 8 | B3 per-handle op | 0xBC68D90 | 6 | [0xF99FFA0] (indirect call target read here) | `0xBC68D90  call qword ptr [0xF99FFA0]` | B3 walks handle array [0x127ca010] (qword handle +0, flag byte +0x20, zero byte +0x18); per entry calls [0xF99FFA0] with rcx=handle ctx, clears byte [handle+0x18] when result==0; dl!=0 indexed loop / dl==0 linear loop [V] | [V] |
| 9 | B3 prologue | 0xBC6884C | 8 | rsp (stack frame below rsp-0x118) | `0xBC6884C  sub rsp,0x118` | B3 prologue: stack cookie [0x1230a0c0]^rsp stored at [rsp+0x110], then 0x118-byte frame; next function at 0xbc68e40 = B4 interpreter [V] | [V] |

## 4. CLOSES?

CLOSES? YES for U-EM3b's pending scope: A5/A7/B3 are now D2 with dossiers on disk (docs/functions/67c9c20.md, c273420.md, bc68840.md), every hop on the A5->A6->A7/A8 path has a verbatim [V] instruction line, both [?] links are resolved (link 1 via vtable slot 0 of .rdata 0xf2beb90, no direct call site [V], dispatch [I]; link 2 negative — submit uses `lea r9,[0xE83C390]` + `call qword ptr [0xF99FFA0]` indirect dispatch [V], wrapper's sole callee 0xe821120 [V], no direct caller of the wrapper [V]). The wider M3b item still needs M1d groups (separate units, PRIORITY.md) and A9 pass bodies (D0/D1); those are out of this unit's scope.

## TOOL REQUESTS

None — no helper scripts written; all evidence from existing rdis/xref tooling and precomputed listings.
