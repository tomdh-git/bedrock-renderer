## NEXT
DONE

# Unit U-EG6: G6 Material swap hook — detour prologue at 0x675e440 + shipped-binary detour fact

## Scope

Checklist item G6 (docs/RENDER_CHECKLIST.md:167): "Material swap hook: control point = pass-name resolver 0x675e440 + item-visitor hash switches (6cj); not implemented".
Research is complete [V] (oc_U-EG6 r1-r3, oc_U-EL7h r1-r8; docs/progress/hints/G6.txt): tag-7 FNV-1 BST at 0x6646dc2 (consts 0x6646dde/0x6646df1/0x6646e00/0x6647449/0x6647458), resolver call 0x6646eab with this = frameCtx+0x68 (0x6646e5c), resolver 0x675e440 = ResourceCache::get (mutex cache+0x98, FNV-1 basis 0xCBF29CE484222325). Do NOT re-derive.
This unit does ONLY the pending part: (1) the exact detour prologue bytes/size at 0x675e440 — instructions up to a safe 5/14-byte boundary — and (2) the SHIPPED-binary fact whether a detour exists. If the detour is already coded in src, quote the source lines. BGFX_MAP.md sections read: 6cj (tag-7 hash switch), 6gs (0x675e440 = ResourceCache::get), plus docs/functions/675e440.md (dossier). Source read: src/client/features/render/rewrite/RewriteMaterialSwap.cpp/h, RewriteResourceCache.cpp, RewriteRegistry.h.

## Evidence table (offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?])

| 0x675e440 | 1 | - | `0x675e440  push rbp` | entry byte of ResourceCache::get in Minecraft.Windows.exe 1.26.62.01; original prologue, no jmp/ff-25 trampoline at the entry — the no-detour proof | [V]
| 0x675e441 | 2 | - | `0x675e441  push r15` | callee-saved register save (prologue) | [V]
| 0x675e443 | 2 | - | `0x675e443  push r14` | callee-saved register save (prologue); cumulative 5 bytes -> 5-byte boundary reached here | [V]
| 0x675e445 | 2 | - | `0x675e445  push r12` | callee-saved register save (prologue) | [V]
| 0x675e447 | 1 | - | `0x675e447  push rsi` | callee-saved register save (prologue) | [V]
| 0x675e448 | 1 | - | `0x675e448  push rdi` | callee-saved register save (prologue) | [V]
| 0x675e449 | 1 | - | `0x675e449  push rbx` | callee-saved register save (prologue) | [V]
| 0x675e44a | 7 | - | `0x675e44a  sub rsp,0x1F0` | 0x1F0 stack frame allocated (dossier: stack frame 0x1f0); cumulative 17 bytes -> 14-byte boundary reached inside this instruction; whole-instruction boundary keeps it | [V]

## Detour prologue budget (from the rows above)

Cumulative bytes from 0x675e440: push rbp 1 (cum 1), push r15 2 (cum 3), push r14 2 (cum 5), push r12 2 (cum 7), push rsi 1 (cum 8), push rdi 1 (cum 9), push rbx 1 (cum 10), sub rsp,0x1F0 7 (cum 17). A 5-byte in-place jump already fits at 0x675e440..0x675e445 (whole instructions through push r14); a 14-byte in-place jump fits once sub rsp,0x1F0 is included. Safe detour boundary: preserve 0x675e440..0x675e44a inclusive (8 whole instructions, 17 bytes >= 14); the trampoline copies them and resumes at 0x675e451 (`lea rbp,[rsp+0x80]`); the detour jump is placed at 0x675e440. No instruction past 0x675e44a is part of the preserved prologue.

## Shipped-binary detour fact

NO detour exists in Minecraft.Windows.exe 1.26.62.01 at 0x675e440: the entry is the original prologue above (all register saves and `sub rsp,0x1F0` frame setup; no `jmp` near jump and no `ff 25` absolute trampoline at the entry). [V] — re-disassembled with `rdis.exe dis 0x675e440 40` on the exe; every row above matches verbatim. The hook is source-only and is installed at runtime by RewriteRegistry (init reads BS_REWRITE; nothing enabled by default, RewriteRegistry.h:6-7).

## Source-coded detour (already coded there)

The detour is the single one on 0x675E440, owned by RewriteResourceCache.cpp (no second detour is registered on this RVA).
- RewriteResourceCache.cpp:89-91:
  `static void* rwCacheDetour(uint8_t* cache, uint64_t* out, const RewriteResourceCache::Key* key, void* loader, const void* name, const void* defines);`
  `static RewriteEntry sCacheEntry("ResourceCache::get", "ResourceCache::get", 0x675E440, reinterpret_cast<void*>(&rwCacheDetour));`
  `static const RewriteReg sCacheReg(sCacheEntry);`
- RewriteResourceCache.cpp:117-150 (`rwCacheDetour` body): Off mode forwards to `e.original<&rwCacheDetour>()` unchanged (line 122); On mode (lines 123-150) reads `MaterialSwap::swapEnabled()` (line 130), looks up the pass-name view (`MaterialSwap::lookup(namePtr, nameSize, repl, replSize)`, line 138) and, on a match, calls the original with the substituted view (`e.original<&rwCacheDetour>()(cache, out, key, loader, nameToUse, defines)`, line 150); otherwise the original runs unchanged with the original name argument.
- RewriteMaterialSwap.cpp:115-116: the MaterialSwap entry is hosted — `static RewriteEntry sSwapEntry("MaterialSwap", "ResourceCache::get", 0x675E440, nullptr, true /* hosted */);` — detour is nullptr, so install() skips Detour creation (RewriteRegistry.cpp:77-82): no second detour is ever created on 0x675E440 and MinHook's MH_ERROR_ALREADY_CREATED cannot occur.
Installation: RewriteRegistry::install resolves sig "ResourceCache::get" (Sigs.json:92, rva 0x675E440), fatals unless target == imageBase()+0x675E440 and knownRva matches (RewriteRegistry.cpp:75), creates the MinHook detour and enables it when the entry mode is not Off (BS_REWRITE="ResourceCache::get=on,MaterialSwap=on").

## CLOSES?

YES — every pending part of this unit's task (the G6 item's remaining static part) is proven by [V] rows:

1. Detour prologue bytes/size at 0x675e440: 8 instructions with verbatim [V] rows above (0x675e440 `push rbp` through 0x675e44a `sub rsp,0x1F0`), 17 cumulative bytes through 0x675e44a; safe whole-instruction boundary for a 5- or 14-byte in-place jump ends at 0x675e44a, resume at 0x675e451. [V]
2. Shipped-binary detour fact: NO detour — 0x675e440 is the original `push rbp` prologue in the shipped exe; no jmp/trampoline at the entry. [V]
3. Source-coded detour quoted above: RewriteResourceCache.cpp rwCacheDetour + sCacheEntry@0x675E440 performs the MaterialSwap pass-name substitution (lines 130/138/150); the MaterialSwap entry is hosted (detour nullptr, RewriteMaterialSwap.cpp:115-116) so exactly one detour exists on the RVA.

Item wording met: control point = pass-name resolver 0x675e440 + item-visitor hash switches (6cj), all [V] (prior units); hook implemented in source (L7h ticked [x] at RENDER_CHECKLIST.md:341 via oc_U-EL7h_r8, verify_oc 15/15, compiled Debug+Release). Caveats: no detour exists in the shipped binary (runtime install by RewriteRegistry only, gated by BS_REWRITE); the in-game swap test is pending (orchestrator live step, outside this static unit); G6's checkbox at RENDER_CHECKLIST.md:167 is reticked by the orchestrator, not by this unit (rule 3: do not edit RENDER_CHECKLIST.md or src/).

## Verification

`python tools/delegate.py check docs/progress/oc_U-EG6.md` -> exit 0 required before setting the line after "## NEXT" to DONE.

## TOOL REQUESTS

None — rdis.exe `dis` and reads of src/ and docs/ sufficed; no helper script written, no _tmp files left behind.
