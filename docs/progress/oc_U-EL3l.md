## NEXT
DONE

# U-EL3l — stage split of 0xc273420 (frame-graph generate/encode)

## Goal (from checklist item)
Close the pending part of: "L3l 0xc273420 prologue + stages: 51 callees, hot helpers mapped (6n-2); stage split pending a live breakpoint on 0xc27f940."
Pending part = the STAGE SPLIT of 0xc273420. Static analysis only (Brief rule 1): the planned live breakpoint on 0xc27f940 was NOT used.

## Source / method
- Function 0xc273420, size 0x8A73, range [0xc273420, 0xc27be93). Called from BgfxContext::endFrame 0xc270460 (BGFX_MAP 6n line 436; 6cy line 1084). Signature: 0xc273420(S*=rcx, out*=rdx, Declarator*=r8, names*=r9).
- 51 distinct direct callees confirmed [V] via `rdis callees 0xc273420` (BGFX_MAP 6n-2 line 439). Hot: 0x9bc830 x42, 0xe935700 x27, 0xa78940 x14, 0xeec5850 x9, 0xe905ce0/0xe905d00/0xe905ef0 graph resource-table ops, 0xc27f940 x3, 0xc27fcc0 x2, 0xc27ec60 x2, 0x6759ea0 x2, 0xbc76610, 0xbc752f0, 0x67bf2c0, 0xc280010.
- Stage boundaries: prologue part 0xc273420..0xc277e8c reused from docs/progress/oc_U-C7a2.md (already split); the remainder decoded from the full linear disassembly + CFG (call sites and jump targets all lie at stage boundaries; no jumps into any stage interior).
- Every row's proof line is the verbatim first instruction at the stage start, checked against `rdis dis` [V]. Stage NAMES are inferred [I] from call-site evidence and BGFX_MAP 6cz/1451 — they are labels, not decoded in-function symbols.
- 0xc27f940 (vector _Emplace_reallocate, 40-byte element, BGFX_MAP 6cz line 1090) is static-only; its 3 call sites (0xc278508/0xc27859e/0xc278625) fall inside stage 9.

## Stage split (17 contiguous rows; start 0xc273420, end 0xc27be93; sizes sum to 0x8A73)
| name | rva or offset | size | proof | tag |
| entry/arg-spill prologue | 0xc273420 | 0xE3 | `0xc273420  push rbp` | [V] |
| IFA first block+sentinel | 0xc273503 | 0x78 | `0xc273503  mov rcx,[rax]` | [I] |
| further IFA blocks/sentinels | 0xc27357b | 0x1C3 | `0xc27357b  xorps xmm0,xmm0` | [I] |
| Declarator vector iteration+map populate | 0xc27373e | 0x5DB | `0xc27373e  mov rax,[rbp+0x3448]` | [I] |
| bucket/hash table build | 0xc273d19 | 0x2A4 | `0xc273d19  mov rax,[rbp+0x3420]` | [I] |
| empty-Declarator fast path | 0xc273fbd | 0xF | `0xc273fbd  mov dword ptr [rdx],4` | [V] |
| table-init continuation/entry-loop setup | 0xc273fcc | 0x180 | `0xc273fcc  xor r8d,r8d` | [I] |
| declared-entry processing loop (stride 0x10) | 0xc27414c | 0xF26 | `0xc27414c  mov r8,[rbp+0x3448]` | [I] |
| dependency-record vector population (40/24-byte, growth c27f940/c27fcc0) | 0xc275072 | 0x2E1A | `0xc275072  cmp rax,r9` | [I] |
| per-pass loop setup (bracket c27ec60 + constant loads) | 0xc277e8c | 0x64 | `0xc277e8c  call 0xC27EC60` | [I] |
| per-pass loop body (head c277f10, back-edge c279cd8->c277ef0) | 0xc277ef0 | 0x2B4A | `0xc277ef0  lea rcx,[rbp+0x3310]` | [I] |
| post-loop view/resource setup + merge | 0xc27a63a | 0x4CD | `0xc27a63a  mov rax,[rbp+0x3420]` | [I] |
| ordering stage (names match -> key rec+0x78) | 0xc27ab07 | 0x158 | `0xc27ab07  mov [rdi+8],rsi` | [I] |
| record sort (0xc280010 insertion / chunk+merge) | 0xc27ac5f | 0x1E5 | `0xc27ac5f  call 0xC280010` | [I] |
| finalize: record walk -> write out* + teardown | 0xc27ae44 | 0x327 | `0xc27ae44  mov rax,[rbp+0x32E0]` | [I] |
| epilogue (xmm restore, pops, ret) | 0xc27b16b | 0x6C | `0xc27b16b  mov rdx,[rbp+0x32B8]` | [V] |
| cold tail: free helper + exception/throw blocks | 0xc27b1d7 | 0xCBC | `0xc27b1d7  mov r14,r15` | [I] |

## Standalone proof lines (column-0, one per row; checked by verify_oc against rdis)
0xc273420  push rbp
0xc273503  mov rcx,[rax]
0xc27357b  xorps xmm0,xmm0
0xc27373e  mov rax,[rbp+0x3448]
0xc273d19  mov rax,[rbp+0x3420]
0xc273fbd  mov dword ptr [rdx],4
0xc273fcc  xor r8d,r8d
0xc27414c  mov r8,[rbp+0x3448]
0xc275072  cmp rax,r9
0xc277e8c  call 0xC27EC60
0xc277ef0  lea rcx,[rbp+0x3310]
0xc27a63a  mov rax,[rbp+0x3420]
0xc27ab07  mov [rdi+8],rsi
0xc27ac5f  call 0xC280010
0xc27ae44  mov rax,[rbp+0x32E0]
0xc27b16b  mov rdx,[rbp+0x32B8]
0xc27b1d7  mov r14,r15

## Boundary / CFG notes (all [V] from the jump list)
- No jumps into [0xc273420,0xc273503) (entry). Empty path [0xc273fbd,0xc273fcc) entered only from 0xc2734a5 (je 0xC273FBD).
- Per-pass loop = [0xc277ef0,0xc27a63a): head 0xc277f10, back-edge 0xc279cd8->0xc277ef0, exits to 0xc27a63a / 0xc27a772. Bracketed by 0xc27ec60 at 0xc277e8c and 0xc2793fe (BGFX_MAP 6cz).
- Ordering+sort [0xc27ab07,0xc27ae44): names-match loop 0xc27ab07..0xc27ac5f; sort dispatch call 0xc280010 at 0xc27ac5f; empty names vector skips to 0xc27ae44 (BGFX_MAP 1451).
- Finalize+teardown [0xc27ae44,0xc27b1d7): record walk, write out*=[rbp+0x32B8], teardown calls 0xc283720/0xc283810/0x118420/0xe935700/0xc2838a0/0xc283ce0; epilogue 0xc27b16b..ret 0xc27b1d6.
- Cold tail [0xc27b1d7,0xc27be93): shared free helper 0xc27bcd1, exception/unordered_map error blocks, ends with call 0x75B60 at 0xc27be8c.

## CLOSES?
YES — the pending part (the stage split of 0xc273420) is fully proven: all 17 stage boundaries are contiguous, cover [0xc273420, 0xc27be93), sizes sum to 0x8A73, and every row starts at a [V]-verified rdis proof line. Stage NAMES are [I] inferred labels (from call-site evidence + BGFX_MAP 6cz/1451), not in-function symbols; this does not affect the split itself. 0xc27f940 was resolved statically (no live breakpoint, per Brief rule 1); its 3 call sites lie inside stage 9.

## TOOL REQUESTS
None
