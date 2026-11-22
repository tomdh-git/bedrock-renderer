## NEXT
DONE

# Unit U-EG6: G6 Material swap hook — call-site 'this' provenance (pass-name resolver 0x675e440 + item-visitor hash switches 6cj)

## Scope

Checklist item G6 (docs/RENDER_CHECKLIST.md:167): "Material swap hook: control point = pass-name resolver 0x675e440 + item-visitor hash switches (6cj); not implemented".

Per the 2026-11-21 progress line on that item, the pending part of THIS unit is the call-site 'this' provenance, still [I]: at `0x6646eab  call 0x675E440` inside the item visitor tag-7 handler (entry 0x6646dc2), prove [V] that rcx, the `this` argument of ResourceCache::get, equals frameCtx + 0x68, where frameCtx is the visitor's rdx argument saved at [rbp+0x8A0].

Already [V] and not re-derived here: tag-7 FNV-1 BST at 0x6646dc2 (consts 0x6646dde/0x6646df1/0x6646e00/0x6647449/0x6647458; BGFX_MAP.md 6cj) and resolver identity 0x675e440 = ResourceCache::get (recursive mutex at cache+0x98; BGFX_MAP.md 6gs/6bk, docs/functions/675e440.md). The hook implementation itself is oc_U-EL7h engineering scope (RewriteMaterialSwap.cpp/h + one detour on 0x675E440 in RewriteResourceCache.cpp; L7h ticked at RENDER_CHECKLIST.md:341); this static unit writes only docs/progress/oc_U-EG6.md (OPENCODE_BRIEF rule 3) and may not edit src/.

Input data: docs/listings/L_6646980.txt (rdis of item visitor 0x6646980, frame 0x9B8). Every `0xRVA  instr` line below is copied verbatim from that listing.

## Evidence table (offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?])

| 0x66469e4 | 8 | [rbp+0x8A0] <- rdx | `0x66469e4  mov [rbp+0x8A0],rdx` | visitor prologue: qword store of arg rdx to stack slot [rbp+0x8A0] before the tag dispatch (frameCtx kept at [rbp+0x8a0] per BGFX_MAP.md 6c/6ci) | [V]
| 0x6646e51 | 8 | [rbp+0x8A0] -> rax | `0x6646e51  mov rax,[rbp+0x8A0]` | tag-7 path: reload saved slot [rbp+0x8A0] into rax | [V]
| 0x6646e58 | 8 | [rax+0x40] -> r9 | `0x6646e58  mov r9,[rax+0x40]` | r9 = [rax+0x40], the resolver's loader argument (ctx+0x40 passed along per BGFX_MAP.md 6cj) | [V]
| 0x6646e5c | 8 | [rax+0x68] -> rcx | `0x6646e5c  mov rcx,[rax+0x68]` | rcx = [rax+0x68]; with rax = [rbp+0x8A0] this is frameCtx+0x68, the cache `this` (ctx+0x68 passed along per BGFX_MAP.md 6cj) | [V]
| 0x6646e60 | 16 | - | `0x6646e60  pxor xmm0,xmm0` | xmm0 zeroed; does not write rcx | [V]
| 0x6646e64 | 16 | [rbp+0x220] <- xmm0 | `0x6646e64  movdqa [rbp+0x220],xmm0` | defines span zeroed at [rbp+0x220]; does not write rcx | [V]
| 0x6646e6c | 8 | - | `0x6646e6c  lea rax,[0xF515E74]` | pass-name pointer 0xF515E74 computed into rax; does not write rcx | [V]
| 0x6646e73 | 8 | [rbp+0x5A0] <- rax | `0x6646e73  mov [rbp+0x5A0],rax` | pass-name pointer stored; does not write rcx | [V]
| 0x6646e7a | 8 | [rbp+0x5A8] <- imm 0x11 | `0x6646e7a  mov qword ptr [rbp+0x5A8],0x11` | pass-name size 0x11 stored; does not write rcx | [V]
| 0x6646e85 | 8 | - | `0x6646e85  lea rax,[rbp+0x220]` | defines pointer computed; does not write rcx | [V]
| 0x6646e8c | 8 | [rsp+0x28] <- rax | `0x6646e8c  mov [rsp+0x28],rax` | stack arg 6 = defines pointer; does not write rcx | [V]
| 0x6646e91 | 8 | - | `0x6646e91  lea rsi,[rbp+0x5A0]` | name-view address into rsi; does not write rcx | [V]
| 0x6646e98 | 8 | [rsp+0x20] <- rsi | `0x6646e98  mov [rsp+0x20],rsi` | stack arg 5 = name view {ptr,size}; does not write rcx | [V]
| 0x6646e9d | 8 | - | `0x6646e9d  lea r8,[0x129F9CB8]` | r8 = key pointer; does not write rcx | [V]
| 0x6646ea4 | 8 | - | `0x6646ea4  lea rdx,[rbp+0x1F0]` | rdx = out slot; does not write rcx | [V]
| 0x6646eab | 5 | imm 0x675E440 | `0x6646eab  call 0x675E440` | resolver call; rcx still holds frameCtx+0x68 from 0x6646e5c — no instruction 0x6646e60..0x6646ea4 rewrites rcx | [V]
| 0x675e440 | 1 | - | `0x675e440  push rbp` | ResourceCache::get entry in the shipped binary — original prologue, no detour/trampoline, so no material-swap hook is implemented in the exe at this control point | [V]

## Proven chain (every instruction above [V], copied verbatim from the listing and re-checked against the exe)

Visitor arg rdx (= frameCtx, signature (this rcx, frameCtx rdx, variant r8) per BGFX_MAP.md 6c/6ci — role name [I]) -> stored to [rbp+0x8A0] @ 0x66469e4 -> reloaded rax = [rbp+0x8A0] @ 0x6646e51 -> rcx = [rax+0x68] @ 0x6646e5c -> no instruction 0x6646e60..0x6646ea4 touches rcx (the 11 rows listed above cover every instruction in that gap) -> `0x6646eab  call 0x675E440` with `this` = frameCtx+0x68 in rcx. Provenance chain [V] for every instruction; role names frameCtx/this [I] from BGFX_MAP.md 6c/6cj.

## CLOSES?

NO — single blocking fact: the hook implementation itself is not proven by any `0xRVA  instr` row and is not present in the shipped binary (0x675e440 is the original `push rbp` entry, no detour — see the row above); it is oc_U-EL7h's engineering scope (RewriteMaterialSwap.cpp/h + RewriteResourceCache.cpp detour; L7h ticked at RENDER_CHECKLIST.md:341 with the in-game swap test still pending there). This unit's static part — the call-site 'this' provenance — is now [V].

## Verification

`python tools/delegate.py check docs/progress/oc_U-EG6.md` -> CHECK OK 17 rows (verify_oc: all quoted `0xRVA  instr` lines match rdis output of the exe; shape checks pass).

## TOOL REQUESTS

None — rdis.exe `dis` and tools/sigs/verify_oc.py (via delegate.py check) sufficed; no helper script written, no _tmp files left behind.
