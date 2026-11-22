## NEXT
DONE

# U-EM3b — M3b control-flow dossiers (one frame traced game logic -> D3D12 submit)

## (1) What changed (paths)
- docs/progress/oc_U-EM3b.md — this file (unit report)
- docs/functions/4e39cb0.md — NEW D2 dossier: representative insert clone (Item tag 0xA BatchActor), instruction-complete
- docs/functions/6646980.md — NEW D2 dossier: Item group visitor (dispatch D2; tag blocks [I]/[?])
- docs/functions/568cd90.md — NEW D2 dossier: Scene/HUD pass body (A9), instruction-complete

## (2) Basis (verified inputs, not re-derived)
- Function sizes [V from rdis fn]: 0x4e39cb0 [0x4e39cb0..0x4e39de9) size 0x139, 2 xrefs (0x6ebb510, 0x4e355a0); 0x568cd90 [0x568cd90..0x568d3a5) size 0x615, 0 xrefs (indirect); 0x6646980 [0x6646980..0x664fda5) size 0x9425, 1 xref, monolithic visitor, jump table 0xF2BF2D0 (rel i32), tag = byte [r8+8], cmp 0xA, ja error 0x664EF12.
- Jump targets [V from BGFX_MAP 6m]: 0 0x6646a10, 1 0x6646f5b, 2 0x6646c8d, 3 0x6646d5f, 4 0x6646a89, 5 0x66471de, 6 0x6647320, 7 0x6646dc2, 8 0x66473e6, 9 0x6646bc6, 10 0x6647383. All 11 targets confirmed present as block starts in docs/progress/6646980_list.txt.
- Prior D2 dossiers (already accepted): docs/functions/67c9c20.md (A5), c273420.md (A7), bc68840.md (B3); EM3b 9/9 per orchestrator hint.
- Still open per FRAME_CALLGRAPH.md: A1 insert clones (now D2 for representative clone 0x4e39cb0), A2 group visitors (dispatch D2 for 0x6646980; tag bodies [I]/[?]), A9 pass task body (now D2 for 0x568cd90).

## (3) Proof table (offset | size | site | instr | meaning)
Every instr cell is verbatim from the rdis listing (two spaces after the address). Size = memory operand size per instruction (qword/64-bit reg = 8, dword = 4, word = 2, byte = 1); no movups/movaps/movdqu/movdqa/movss/movsd rows so the size table is not exercised by any row.

| offset | size | site | instr | meaning |
|--------|------|------|-------|---------|
| 0x4e39cc3 | 8 | docs/progress/4e39cb0_fn.txt:8 | `0x4e39cc3  mov qword ptr [rbp+0x40],0xFFFFFFFFFFFFFFFE` | [V] EH/frame marker store [rbp+0x40] = -2 |
| 0x4e39ccb | 8 | docs/progress/4e39cb0_fn.txt:9 | `0x4e39ccb  mov rdi,rdx` | [V] desc argument copied to rdi |
| 0x4e39cce | 8 | docs/progress/4e39cb0_fn.txt:10 | `0x4e39cce  mov rsi,rcx` | [V] builder argument copied to rsi |
| 0x4e39cd1 | 4 | docs/progress/4e39cb0_fn.txt:11 | `0x4e39cd1  mov eax,[0x129C1E78]` | [V] TLS guard slot load |
| 0x4e39d20 | 8 | docs/progress/4e39cb0_fn.txt:29 | `0x4e39d20  mov [rbp+0x10],rdi` | [V] variant payload: desc ptr store |
| 0x4e39d24 | 1 | docs/progress/4e39cb0_fn.txt:30 | `0x4e39d24  mov byte ptr [rbp+0x18],0xA` | [V] variant payload: tag byte = 0xA (BatchActor) |
| 0x4e39d28 | 8 | docs/progress/4e39cb0_fn.txt:31 | `0x4e39d28  mov rax,[rsi]` | [V] builder object read |
| 0x4e39d2b | 8 | docs/progress/4e39cb0_fn.txt:32 | `0x4e39d2b  mov rax,[rax+0x378]` | [V] builder vtable load (slot 111) |
| 0x4e39d39 | 8 | docs/progress/4e39cb0_fn.txt:35 | `0x4e39d39  call qword ptr [0xF99FFA0]` | [V] _insert(Item) via CFG thunk |
| 0x568cdc8 | 8 | docs/progress/568cd90_fn.txt:17 | `0x568cdc8  mov rax,[rcx+8]` | [V] view object base read [a0+8] |
| 0x568cdcc | 2 | docs/progress/568cd90_fn.txt:18 | `0x568cdcc  movzx eax,word ptr [rax+8]` | [V] u16 view id read |
| 0x568cdee | 4 | docs/progress/568cd90_fn.txt:25 | `0x568cdee  movd xmm1,[rbx+0xFC]` | [V] clear/rect dword read [a1+0xFC] |
| 0x568cebe | 1 | docs/progress/568cd90_fn.txt:61 | `0x568cebe  movzx eax,byte ptr [rbx+0x108]` | [V] flag byte read [a1+0x108] |
| 0x568cecc | 1 | docs/progress/568cd90_fn.txt:63 | `0x568cecc  mov [rcx+r13+0x1EAB1B2],al` | [V] per-view flag store |
| 0x66469eb | 1 | docs/progress/6646980_list.txt:21 | `0x66469eb  movzx eax,byte ptr [r8+8]` | [V] variant tag byte read |
| 0x66469fd | 8 | docs/progress/6646980_list.txt:25 | `0x66469fd  mov rdi,[r8]` | [V] desc pointer read |
| 0x6646a1d | 8 | docs/progress/6646980_list.txt:33 | `0x6646a1d  cmp qword ptr [rax+0x40],0` | [V] tag0 inner-pointer null check |

Row count: 17 data rows (header excluded — contains the word offset). No duplicate offsets. No leading-whitespace disassembly lines anywhere in this file (raw = 0). No movups/movaps/movdqu/movdqa/movss/movsd rows.

## (4) CLOSES?
NO. Blocking fact: M3b requires every function on the traced game-logic -> D3D12-submit path to hold a D2 dossier. This unit closes three pending path functions (clone 0x4e39cb0 D2, visitor 0x6646980 dispatch D2, pass body 0x568cd90 D2) and A5/A7/B3 were already D2, but the visitor's per-tag bodies (0x6646a10..0x66473e6 blocks plus shared machinery 0x6647400..0x6648F33 and cold tail 0x664ec29..0x664fda0) are not decoded beyond dispatch ([I]/[?] documented in docs/functions/6646980.md), so not every function on the path is D2. Remaining per-tag coverage and the rest of the submit chain are M1d/M3b follow-up.

## (5) TOOL REQUESTS (not part of this unit's closure)
- Per-tag visitor body units for tags 0..10 (entries 0x6646a10, 0x6646f5b, 0x6646c8d, 0x6646d5f, 0x6646a89, 0x66471de, 0x6647320, 0x6646dc2, 0x66473e6, 0x6646bc6, 0x6647383) and shared region 0x6647400..0x6648F33.
- Dossiers for pass-body callees: sub_ebce390, sub_BCC1A30, sub_BC60D10, sub_C4BBA0, sub_568DB90, sub_E86D7F0, sub_568DA90, sub_655CEA0, sub_E935700, sub_568D480.
- EndFrame -> encoder -> D3D12 command list -> submit chain dossiers to complete the full M3b path.
- Sigs.json (src/sdk/Sigs.json): append proven new entries only for call sites 0x39A7D40, 0xEBCE390, 0xBCC1A30, 0xBC60D10, 0xC4BBA0, 0x568DB90, 0x568D480, 0xE86D7F0, [0xF99FFA0], [0xF9A8C78] (all verified via rdis dis; no existing entries modified).
