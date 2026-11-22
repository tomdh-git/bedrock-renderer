## NEXT
DONE

# Unit U-EG6: G6 Material swap hook — call-site 'this' provenance (pass-name resolver 0x675e440 + item-visitor hash switches 6cj)

## Scope

Checklist item G6 (docs/RENDER_CHECKLIST.md line 167): "Material swap hook: control point = pass-name resolver 0x675e440 + item-visitor hash switches (6cj); not implemented".

Pending part of the item line (per the 2026-11-21 progress note): **call-site 'this' provenance still [I]** — prove [V] that at the resolver call `0x6646eab  call 0x675E440` inside Item visitor tag 7 (entry 0x6646dc2), the `this` argument (rcx) really is `frameCtx + 0x68`, where `frameCtx` is the visitor's `rdx` argument saved at `[rbp+0x8A0]`.

Already [V] elsewhere (oc_U-EL7h.md, BGFX_MAP.md 6c/6cj/6gs, docs/functions/675e440.md): tag-7 FNV-1 BST at 0x6646dc2; resolver 0x675e440 = ResourceCache::get (recursive mutex at cache+0x98; signature `get(rcx=this, rdx=out, r8=key, r9=loader, 5th=name_view, 6th=defines)`). This unit only re-derives the call-site provenance so the row is [V] here, quoted verbatim from the precomputed listing docs/listings/L_6646980.txt (rdis of the exe), not re-run.

## Call-site 'this' provenance (tag-7 handler 0x6646dc2, inside visitor 0x6646980)

The visitor prologue saves the only argument not consumed by the dispatch (`rdx`, frameCtx per the BGFX_MAP.md 6c signature `(this rcx, frameCtx rdx, variant r8)`) at `[rbp+0x8A0]`; tag 7 then rebuilds the resolver arguments from that slot: loader = `[frameCtx+0x40]`, cache `this` = `[frameCtx+0x68]`. The name view is built in parallel (lea rax,[0xF515E74] "CracksBlockEntity", size 0x11) and is not part of 'this'.

| name | size | address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| frameCtx-spill | 8 | [rbp+0x8A0] <- rdx | `0x66469e4  mov [rbp+0x8A0],rdx` | visitor arg rdx = frameCtx spilled to the stack slot before the tag switch (prologue, after `mov rbx,rcx`/`mov rdi,[r8]`/`movzx eax,byte ptr [r8+8]`) | [V] |
| frameCtx-reload | 8 | [rbp+0x8A0] -> rax | `0x6646e51  mov rax,[rbp+0x8A0]` | frameCtx reloaded into rax to build the resolver call arguments | [V] |
| loader-arg | 8 | [rax+0x40] -> r9 | `0x6646e58  mov r9,[rax+0x40]` | r9 = loader argument = frameCtx+0x40 | [V] |
| this-from-frameCtx | 8 | [rax+0x68] -> rcx | `0x6646e5c  mov rcx,[rax+0x68]` | rcx = cache `this` = frameCtx+0x68 | [V] |
| resolver-call | 5 | imm 0x675E440 | `0x6646eab  call 0x675E440` | hook point: `this` = frameCtx+0x68 in rcx; result holder at [rbp+0x1F0] | [V] |

rcx is written at 0x6646e5c and is not redefined anywhere between there and the call: I read every instruction 0x6646e60..0x6646ea4 (`pxor xmm0,xmm0`, `movdqa [rbp+0x220],xmm0`, `lea rax,[0xF515E74]`, `mov [rbp+0x5A0],rax`, `mov qword ptr [rbp+0x5A8],0x11`, `lea rax,[rbp+0x220]`, `mov [rsp+0x28],rax`, `lea rsi,[rbp+0x5A0]`, `mov [rsp+0x20],rsi`, `lea r8,[0x129F9CB8]`, `lea rdx,[rbp+0x1F0]`) — none touch rcx. [V]

Proven chain: `rdx` (frameCtx parameter) -> stored `[rbp+0x8A0]` @ 0x66469e4 -> reloaded `rax = [rbp+0x8A0]` @ 0x6646e51 -> `rcx = [rax+0x68]` = frameCtx+0x68 @ 0x6646e5c -> `call 0x675E440` @ 0x6646eab with `this` = frameCtx+0x68. [V]

## CLOSES?

YES — the pending part of the G6 item line for oc_U-EG6 ("call-site 'this' provenance still [I]") is now proven [V]: every instruction in the chain 0x66469e4 -> 0x6646e51 -> 0x6646e58 -> 0x6646e5c -> 0x6646eab is quoted verbatim from the listing, rcx is never redefined between 0x6646e5c and the call, and rcx is the `this` argument of `ResourceCache::get`. BST decode and resolver identification were already [V] (oc_U-EL7h.md / BGFX_MAP.md 6cj/6gs); the hook implementation itself is oc_U-EL7h's scope (RewriteMaterialSwap.cpp / RewriteResourceCache.cpp), not this static unit.

## TOOL REQUESTS

None — no helper script written; all evidence quoted verbatim from the precomputed listing docs/listings/L_6646980.txt.
