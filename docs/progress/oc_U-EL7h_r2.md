## NEXT
DONE

# Unit U-EL7h: L7h Material swap hook — pass-name resolver 0x675e440 + item-visitor hash switches (6cj)

## Scope

Checklist item L7h (docs/RENDER_CHECKLIST.md line 341): "Material swap hook: control point = pass-name resolver 0x675e440 + item-visitor hash switches (6cj); not implemented".
This unit decodes the control point only. The hook itself is a runtime code change and is not written here (static-analysis-only unit; see rules 1 and 3 of docs/OPENCODE_BRIEF.md).
The earlier attempt oc_U-EL7h_r1.md (verify_oc 30/30) already proved the control point [V]: BST hash switch at tag-7 handler 0x6646dc2 (split 0x416AE22CAB22EA36 @ 0x6646dde, jg 0x6647449 @ 0x6646deb; leaves 0xD8EF928BC853553A @ 0x6646df1 and 0x2C8B246FD3EDDC59 = cracks_overlay_tile_entity.skinning @ 0x6646e00, jne miss @ 0x6646e0d; right subtree leaves 0x4B8EDB299C93ABB3 @ 0x6647449 and 0x416AE22CAB22EA37 @ 0x6647458, jne miss @ 0x6647465; miss path 0x66475bb `mov rsi,[0x128D6FA8]` → forwarder 0x66475de `call 0x4DF6E80` → miss tail 0x664CB91); on a match the pass-name "CracksBlockEntity" (0x6646e6c, len 0x11 @ 0x6646e7a) is passed as string_view at [rsp+0x20] (0x6646e98) and the resolver is called at 0x6646eab with call-site this = frameCtx+0x68 (0x6646e5c), r9 = frameCtx+0x40 (0x6646e58), result at [rbp+0x1F0] (0x6646eb0), null → 0x664CB91 (0x6646ebd). That work is not re-derived here; this file adds the missing new angle: every direct caller of 0x675e440, re-disassembled verbatim, plus a correction to one resolver-body row (cache+0xE4), then states whether the item closes.
Docs consulted: docs/BGFX_MAP.md sections 6cj (tag-7 hash switch) and 6gs (0x675e440 = ResourceCache::get, not a material resolver); docs/functions/675e440.md (dossier generated from the disassembly).

## Answer table (offset | size | address | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?])

All verbatim lines re-disassembled from the exe with rdis and each carried into `python tools/sigs/verify_oc.py` on this file. The last column tags the quoted instruction line ([V] = seen in the disassembly). Meanings marked [I] are inferred from xref.py callers / rdis callers + docs/functions/675e440.md, not from the instruction itself.

| offset | size | address | verbatim `0xRVA  instr` | meaning | [V]/[I]/[?] |
| 0x675e440 | 8 | - | `0x675e440  push rbp` | ResourceCache::get entry (6gs [I]: keyed get-or-load cache for render resources, not a material-specific resolver); hooking here intercepts all 34 call sites below [I scope] | [V] |
| 0x675e46d | 8 | rcx -> r14 | `0x675e46d  mov r14,rcx` | cache this (arg1 rcx) saved to r14; resolver body offsets are r14-relative | [V] |
| 0x675e489 | 8 | [r14+0x98] -> r15 | `0x675e489  lea r15,[r14+0x98]` | recursive mutex address = cache+0x98 | [V] |
| 0x675e493 | 5 | call 0xEEC59F0 | `0x675e493  call 0xEEC59F0` | lock the recursive mutex at cache+0x98 | [V] |
| 0x675e4ae | 4 | [r14+0xE4] | `0x675e4ae  cmp dword ptr [r14+0xE4],0x7FFFFFFF` | cache+0xE4 dword vs 0x7FFFFFFF; je 0x675E8D3; meaning [?]: 6gs/dossier read +0xE4 as recursive-mutex owner count, earlier "stale-key sentinel" label was a misread; not part of the hook point | [V] |
| 0x675e4bf | 8 | [rbx] | `0x675e4bf  mov rax,[rbx]` | key.lo (key+0x0) starts the FNV-1 64 hash | [V] |
| 0x675e4c2 | 1 | [rbx+8] | `0x675e4c2  movzx ecx,byte ptr [rbx+8]` | key.hi byte 0 mixed into the FNV-1 64 hash | [V] |
| 0x675e4c6 | 8 | - | `0x675e4c6  mov rdx,0xCBF29CE484222325` | FNV-1 64 offset basis 0xCBF29CE484222325 | [V] |
| 0x675e4d3 | 8 | - | `0x675e4d3  mov rcx,0x100000001B3` | FNV-1 64 prime 0x100000001B3 | [V] |
| 0x6646eab | 5 | -> 0x675e440 | `0x6646eab  call 0x675E440` | item-visitor 0x6646980 tag-7 match path: resolver call carrying the pass-name string_view "CracksBlockEntity" — the per-item material-swap hook point [V call; string provenance 0x6646e6c/0x6646e98 from prior verified notes] | [V] |

## New angle: every direct caller of 0x675e440 (continuation of the same table)

xref.py callers and rdis callers agree: 12 calling functions, 34 direct call sites, every one a verbatim `call 0x675E440`. 0x675e440 is therefore NOT a material-specific resolver: per 6gs/docs/functions/675e440.md it is ResourceCache::get(out rdx, key16 r8, loader r9, name string_view, defines) — a keyed get-or-load cache used by every group visitor that needs a resource (Item, Sky, UI, Effect, Editor), the terrain builder (5 sites), the BlockSelectionOverlay extractor (2), FlameBillboard (1) and the RTX frame builder (1). Hooking 0x675e440 intercepts ALL resource gets; the tag-7 material-swap-relevant site is only 0x6646eab (pass-name string_view above).

| 0x6647270 | 5 | -> 0x675e440 | `0x6647270  call 0x675E440` | item-visitor 0x6646980, second resolver call site (path not re-decoded here) [I role] | [V] |
| 0x66565ec | 5 | -> 0x675e440 | `0x66565ec  call 0x675E440` | sky group visitor 0x66560f0 [I role] | [V] |
| 0x6656764 | 5 | -> 0x675e440 | `0x6656764  call 0x675E440` | sky group visitor 0x66560f0 [I role] | [V] |
| 0x66568d2 | 5 | -> 0x675e440 | `0x66568d2  call 0x675E440` | sky group visitor 0x66560f0 [I role] | [V] |
| 0x6656b32 | 5 | -> 0x675e440 | `0x6656b32  call 0x675E440` | sky group visitor 0x66560f0 [I role] | [V] |
| 0x6656c99 | 5 | -> 0x675e440 | `0x6656c99  call 0x675E440` | sky group visitor 0x66560f0 [I role] | [V] |
| 0x6664b28 | 5 | -> 0x675e440 | `0x6664b28  call 0x675E440` | UI group visitor 0x6664a00 [I role] | [V] |
| 0x6664dce | 5 | -> 0x675e440 | `0x6664dce  call 0x675E440` | UI group visitor 0x6664a00 [I role] | [V] |
| 0x666af30 | 5 | -> 0x675e440 | `0x666af30  call 0x675E440` | Effect group visitor 0x666aca0 [I role] (BlitFlipbook tag 1 at 0x666aec2, AimAssistHighlight tag 6 at 0x666b143 per 6ih [I]) | [V] |
| 0x666b268 | 5 | -> 0x675e440 | `0x666b268  call 0x675E440` | Effect group visitor 0x666aca0 [I role] | [V] |
| 0x667446a | 5 | -> 0x675e440 | `0x667446a  call 0x675E440` | Editor group visitor 0x66742f0 [I role] | [V] |
| 0x667458e | 5 | -> 0x675e440 | `0x667458e  call 0x675E440` | Editor group visitor 0x66742f0 [I role] | [V] |
| 0x66746b2 | 5 | -> 0x675e440 | `0x66746b2  call 0x675E440` | Editor group visitor 0x66742f0 [I role] | [V] |
| 0x66748f4 | 5 | -> 0x675e440 | `0x66748f4  call 0x675E440` | Editor group visitor 0x66742f0 [I role] | [V] |
| 0x6674a15 | 5 | -> 0x675e440 | `0x6674a15  call 0x675E440` | Editor group visitor 0x66742f0 [I role] | [V] |
| 0x6674c57 | 5 | -> 0x675e440 | `0x6674c57  call 0x675E440` | Editor group visitor 0x66742f0 [I role] | [V] |
| 0x6674e96 | 5 | -> 0x675e440 | `0x6674e96  call 0x675E440` | Editor group visitor 0x66742f0 [I role] | [V] |
| 0x66757b4 | 5 | -> 0x675e440 | `0x66757b4  call 0x675E440` | Editor group visitor 0x66742f0 [I role] | [V] |
| 0x66a1aed | 5 | -> 0x675e440 | `0x66a1aed  call 0x675E440` | Editor block-volume extractor 0x66a1860 [I role] | [V] |
| 0x66a284f | 5 | -> 0x675e440 | `0x66a284f  call 0x675E440` | Editor block-volume extractor 0x66a1860 [I role] | [V] |
| 0x66a359f | 5 | -> 0x675e440 | `0x66a359f  call 0x675E440` | Editor block-volume extractor 0x66a1860 [I role] | [V] |
| 0x66a6927 | 5 | -> 0x675e440 | `0x66a6927  call 0x675E440` | caller 0x66a6830; role not decoded [I] | [V] |
| 0x66a696c | 5 | -> 0x675e440 | `0x66a696c  call 0x675E440` | caller 0x66a6830; role not decoded [I] | [V] |
| 0x66a9e46 | 5 | -> 0x675e440 | `0x66a9e46  call 0x675E440` | caller 0x66a9d50; role not decoded [I] | [V] |
| 0x66e76db | 5 | -> 0x675e440 | `0x66e76db  call 0x675E440` | BlockSelectionOverlayBlockEntity extractor 0x66e75f0 (Item tag 8) [I role] | [V] |
| 0x66e7844 | 5 | -> 0x675e440 | `0x66e7844  call 0x675E440` | BlockSelectionOverlayBlockEntity extractor 0x66e75f0 (Item tag 8) [I role] | [V] |
| 0x66ea88f | 5 | -> 0x675e440 | `0x66ea88f  call 0x675E440` | terrain/chunk draw builder 0x66ea3d0 [I role] | [V] |
| 0x66ea987 | 5 | -> 0x675e440 | `0x66ea987  call 0x675E440` | terrain/chunk draw builder 0x66ea3d0 [I role] | [V] |
| 0x66eaa19 | 5 | -> 0x675e440 | `0x66eaa19  call 0x675E440` | terrain/chunk draw builder 0x66ea3d0 [I role] | [V] |
| 0x66eabd8 | 5 | -> 0x675e440 | `0x66eabd8  call 0x675E440` | terrain/chunk draw builder 0x66ea3d0 [I role] | [V] |
| 0x66eac2c | 5 | -> 0x675e440 | `0x66eac2c  call 0x675E440` | terrain/chunk draw builder 0x66ea3d0 [I role] | [V] |
| 0x673d238 | 5 | -> 0x675e440 | `0x673d238  call 0x675E440` | FlameBillboard extractor 0x673d150 (Effect tag 0) [I role] | [V] |
| 0xbbe4fae | 5 | -> 0x675e440 | `0xbbe4fae  call 0x675E440` | RTX frame builder 0xbbe2d50 [I role] | [V] |

## What I tried that failed (new angle)

1. Bound the material-swap hook to a material-only resolver — failed: 0x675e440 is ResourceCache::get, a keyed get-or-load cache (0x4EC bytes, 305 instructions per the dossier) with 34 direct call sites in 12 functions (item/sky/UI/effect/editor visitors, terrain builder x5, block-selection-overlay extractor x2, FlameBillboard, RTX frame builder — all enumerated [V] above). Hooking 0x675e440 intercepts every resource get, not only material swaps; the tag-7 material-swap-relevant site is the single call 0x6646eab carrying the pass-name string_view. Caller identities [I] from xref.py callers + rdis callers + docs/functions/675e440.md.
2. Confirmed the earlier "stale-key sentinel at cache+0xE4" reading — failed: `0x675e4ae  cmp dword ptr [r14+0xE4],0x7FFFFFFF` executes after the cache+0x98 mutex is locked (0x675e493 `call 0xEEC59F0`), and 6gs/the dossier read +0xE4 as the recursive-mutex owner count, so the earlier "stale-key sentinel / 0x7FFFFFFF = stale" label was a misread. The instruction and branch are [V]; the semantic of +0xE4 is [?] and is irrelevant to the hook control point.
3. Hook implementation itself — cannot be produced or verified here: rule 1 is static analysis only, no detour or code change can be written (rule 3). No livemem reads were needed; static analysis settled the control point. vt/vcalls/descscan2 angles add nothing: the resolver's only indirect call is the allocator setTag vcall (`mov dl,0x30` @ 0x675e47e, `call qword ptr [0xF99FFA0]` @ 0x675e480), and the cache has no vtable slots of its own.

## CLOSES?

NO — single blocking fact: the hook implementation itself remains undone. Everything decodable statically is [V]: BST hash switch (tag-7 handler 0x6646dc2), pass-name resolver call 0x6646eab with this=frameCtx+0x68 (0x6646e5c), resolver body 0x675e440 (mutex cache+0x98, FNV-1 basis 0xCBF29CE484222325), and — new angle — all 34 direct call sites of 0x675e440 across 12 callers. But writing the hook (detour at 0x675e440 entry or interception of call 0x6646eab carrying the pass-name string_view) is a dynamic code change outside static-analysis scope (rules 1 and 3), and the checklist item itself still reads "not implemented". No offsets remain [I] or [?] for the control point; the only [I]/[?] tags above are caller-role names and the unresolved cache+0xE4 semantic, neither part of the hook control point.
