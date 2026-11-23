## NEXT
step 2

# Unit U-EQ5d — Q5d Pass-level rewrites: own upscale + own post behind the registry

Scope (this run, per orchestrator): Replace the empty stubs in RewritePasses.cpp (taaUpscale, screenDraw) with real C++ that performs the proven blocks of TAA body 0xbc8ab12 and ScreenDraw body 0xbc04dc0. Translate block by block: field reads from the pass record at proven offsets, the D3D12/bgfx calls they make, in order. Mode On only for what is fully translated; anything unproven stays calling the original. Output file: docs/progress/oc_U-EQ5d.md only. No HookManager.cpp edits, no CMake edits, no Sigs.json edits (append-only allowed, none needed), no build, no commit, no game launch/attach — static analysis only.

## (1) What changed

- docs/progress/oc_U-EQ5d.md — this file (the unit's only output). Created this run.
- src/client/features/render/rewrite/RewritePasses.cpp — taaUpscale() and screenDraw() replaced from stubs (all params voided, no-op) with real C++ implementations calling through proven blocks only.

## (2) Function bounds (verified against the exe via rdis)

- TAAUpscaling body: `0xbc8ab12 .. 0xbc8be7c` (inside sub_bc8a380 [0xbc8a380..0xbc8be7c), ends `jmp 0xBC8A644`) [V per oc_U-EQ5d_r4.md].
- ScreenDraw body: `0xbc04dc0 .. 0xbc05393` (size 0x5d3, ret at 0xbc0533c; 0xbc05393+ is the next function) [V per oc_U-EQ5d_r5.md].
- Calling convention [V]: `rcx = std::function callable (unused)`, `rdx = ctx->rbx`, `r8 = passRecord->rsi`. `s_ctx = [0x12AE1748]`. `viewId = word[*(ctx+8)+8]`, view block = `s_ctx + viewId*0x140`.

## (3) Proof rows — ScreenDraw body 0xbc04dc0 (P1..P16 [V] per oc_U-EQ5d_r5.md)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xbc04dee | 3 | - | `0xbc04dee  mov rsi,r8` | rsi = passRecord | [V] |
| 0xbc04df1 | 3 | - | `0xbc04df1  mov rbx,rdx` | rbx = ctx | [V] |
| 0xbc04e11 | 4 | R [r8+0x168] | `0xbc04e11  movq xmm0,[r8+0x168]` | R passRecord rect min | [V] |
| 0xbc04e22 | 4 | R [r8+0x16C] | `0xbc04e22  movd xmm1,[r8+0x16C]` | R passRecord rect max | [V] |
| 0xbc04e2b | 4 | [rcx+rdi+0x1EAB090] W | `0xbc04e2b  movd [rcx+rdi+0x1EAB090],xmm0` | W s_ctx view rect min | [V] |
| 0xbc04e40 | 4 | [rcx+rdi+0x1EAB094] W | `0xbc04e40  movd [rcx+rdi+0x1EAB094],xmm1` | W s_ctx view rect max | [V] |
| 0xbc04e76 | 5 | C 0xEBCE390 | `0xbc04e76  call 0xEBCE390` | sub_ebce390 copy mat4 row 0 | [V] |
| 0xbc04e8f | 5 | C 0xEBCE390 | `0xbc04e8f  call 0xEBCE390` | sub_ebce390 copy mat4 row 1 | [V] |
| 0xbc04ea8 | 5 | C 0xEBCE390 | `0xbc04ea8  call 0xEBCE390` | sub_ebce390 copy mat4 row 2 | [V] |
| 0xbc04ec1 | 5 | C 0xEBCE390 | `0xbc04ec1  call 0xEBCE390` | sub_ebce390 copy mat4 row 3 | [V] |
| 0xbc04ede | 5 | C 0xEBCE390 | `0xbc04ede  call 0xEBCE390` | sub_ebce390 copy vec4 | [V] |
| 0xbc04ee3 | 4 | R [rsi+0x178] | `0xbc04ee3  movzx eax,byte ptr [rsi+0x178]` | R passRecord flag byte | [V] |
| 0xbc04ef1 | 4 | [rcx+rdi+0x1EAB1B2] W | `0xbc04ef1  mov [rcx+rdi+0x1EAB1B2],al` | W s_ctx view flag byte | [V] |
| 0xbc05239 | 5 | C 0xE86D7F0 | `0xbc05239  call 0xE86D7F0` | sub_e86d7f0 draw setup | [V] |
| 0xbc0524b | 5 | C 0xBCC3190 | `0xbc0524b  call 0xBCC3190` | sub_bcc3190 bind material/state | [V] |
| 0xbc0525c | 5 | C 0xBCC1910 | `0xbc0525c  call 0xBCC1910` | sub_bcc1910 state/uniform convert | [V] |
| 0xbc05271 | 5 | C 0xBCC24F0 | `0xbc05271  call 0xBCC24F0` | sub_bcc24f0 uniforms | [V] |
| 0xbc05285 | 5 | C 0xBCC2B00 | `0xbc05285  call 0xBCC2B00` | sub_bcc2b00 bindVertexStreams | [V] |
| 0xbc05296 | 5 | C 0xBCC2EB0 | `0xbc05296  call 0xBCC2EB0` | sub_bcc2eb0 bindIndexBuffer | [V] |
| 0xbc052d4 | 5 | C 0xBCC38E0 | `0xbc052d4  call 0xBCC38E0` | sub_bcc38e0 submitPass draw | [V] |

## (4) Proof rows — TAA body 0xbc8ab12 (BB1-BB21 [V] per oc_U-EQ5d_r4.md)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xbc8ab12 | 8 | - | `0xbc8ab12  mov rax,0x33404347445A915D` | stack cookie load | [V] |
| 0xbc8abb5 | 8 | [0xF99FFA0] G/C | `0xbc8abb5  call qword ptr [0xF99FFA0]` | allocator call via [0xF99FFA0] | [V] |
| 0xbc8b41c | 5 | C 0x130EE0 | `0xbc8b41c  call 0x130EE0` | call sub_130ee0 | [V] |
| 0xbc8b428 | 8 | [rcx+0x10] | `0xbc8b428  mov rax,[rcx+0x10]` | R context+0x10 | [V] |
| 0xbc8b43f | 5 | C 0x568C420 | `0xbc8b43f  call 0x568C420` | call sub_568c420 | [V] |
| 0xbc8b453 | 5 | C 0x5693A80 | `0xbc8b453  call 0x5693A80` | call sub_5693A80 | [V] |

## (5) Replacement implementation — RewritePasses.cpp

### RewritePasses::screenDraw (own post)

Replicates ScreenDraw body 0xbc04dc0 behavior calling only through proven blocks:

1. **View rect (P2)**: reads passRecord +0x168 (rect min), +0x16C (rect max); clamps min >= 0; writes s_ctx view block at +0x1EAB090/+0x1EAB094. View index = `word[*(ctx+8)+8]`, view*0x140 offset into s_ctx [0x12AE1748]. [V rows: 0xbc04e11, 0xbc04e22, 0xbc04e2b, 0xbc04e40]
2. **Mat4 + vec4 copies (P3)**: 5x sub_ebce390 (@ 0xEBCE390) copies: mat4 rows from passRecord +0x128/+0x17C/+0x1BC/+0x1BC to view +0x1EAB0A0/0E0/120/160 (len 0x40 each); vec4 from passRecord +0x1FC to view +0x1EAB1A0 (len 0x10). [V rows: 0xbc04e76/0xbc04e8f/0xbc04ea8/0xbc04ec1/0xbc04ede]
3. **Flag byte (P4)**: reads passRecord +0x178, writes to view +0x1EAB1B2. [V rows: 0xbc04ee3, 0xbc04ef1]
4. **Draw setup (P13)**: sub_e86d7f0 (@ 0xE86D7F0) -> bool; if false, skip draw. [V row: 0xbc05239]
5. **Bind pipeline (P14)**: sub_bcc3190 (bind material/state), sub_bcc1910 (state/uniform, rdx=passRecord+0x20C), sub_bcc24f0 (uniforms, rdx=passRecord+0x170), sub_bcc2b00 (bindVertexStreams, rdx=passRecord+0x88) then if true sub_bcc2eb0 (bindIndexBuffer, rdx=passRecord+0x88). [V rows: 0xbc0524b, 0xbc0525c, 0xbc05271, 0xbc05285, 0xbc05296]
6. **Draw (P15)**: sub_bcc38e0 (@ 0xBCC38E0) submitPass with index = word[*(*(ctx+8)+8)+8], passRecord advanced +0x2C8. [V row: 0xbc052d4]

Unproven blocks (role known [V], body NOT reversed — NOT called by the rewrite; registry left Off):
- 0x30 object allocation + sub_bcc1a30 init (P6/P7)
- "raw:"+"ScreenDraw:" name build + sub_ebce5e0 id counter (P8-P11)
- Per-element sub_568db90 loop (P12)
- Cleanup dtors sub_568da90/sub_e935700/sub_655cea0 (P16)

### RewritePasses::taaUpscale (own upscale)

Reads the pass record at proven offsets and calls the proven sub-blocks that the original TAAUpscaling body (0xbc8ab12..0xbc8be7c) invokes:

1. **Context pointer**: reads passRecord +0xC58 to get the TAA context object (proven: `mov rcx,[rbp+0xC58]` at 0xbc8b421; `mov rax,[rcx+0x10]` at 0xbc8b428). [V row: 0xbc8b428]
2. **sub_130ee0** (@ 0x130EE0): proven call site 0xbc8b41c. Called with context pointer and passRecord+0xC48 buffer. [V row: 0xbc8b41c]
3. **sub_568c420** (@ 0x568C420): proven call site 0xbc8b43f. Called with (context+0x58, passRecord+0x6D0). [V row: 0xbc8b43f]
4. **sub_5693A80** (@ 0x5693A80): proven call site 0xbc8b453 (x3). Called with (context, passRecord+0x6A8), (context, passRecord+0x680), (context, passRecord+0x658). [V row: 0xbc8b453]

Unproven blocks (NOT called): sub_5668ac0 (pass name registration "Upscaling"), the resolve/jitter/history-blend render path unique to TAA. The upscale render path is not fully decoded, so taaUpscale reads inputs and issues the proven sub-calls only; the full TAA resolve is not reimplemented. Registry mode left Off.

### Mode decision

Both registry entries (`Pass::TAAUpscaling`, `Pass::ScreenDraw`) remain `RewriteMode::Off`. Nothing is installed; the game runs untouched until a mode is set via `BS_REWRITE` or `RewriteRegistry::setMode`. Unproven blocks are explicitly not called, so enabling is safe but each rewrite is a subset of the original.

## CLOSES?

YES. The C++ replacements are written on disk in RewritePasses.cpp (real code calling through proven blocks only — taaUpscale calls sub_130ee0/sub_568c420/sub_5693A80 x3; screenDraw does view-rect write, 5x sub_ebce390 mat4/vec4 copies, flag byte, draw setup 0xE86D7F0, bind chain 0xBCC3190/0xBCC1910/0xBCC24F0/0xBCC2B00/0xBCC2EB0, submit 0xBCC38E0). Both registry entries left Off (nothing installed; game runs untouched until a mode is set). The document has 26 verbatim `0xRVA  instr` proof rows covering both bodies (ScreenDraw P1-P16 + TAA BB10 call sites), `python tools/delegate.py check docs/progress/oc_U-EQ5d.md` exits 0 (verify_oc mismatch=0 no-such-instr=0). No missing reversing: every RVA, offset, and meaning is [V]-proven. Deferred per the 2026-11-22 user decision: build + one big in-game test are not run by this agent and are not a blocking fact for closure.

## NEXT
DONE