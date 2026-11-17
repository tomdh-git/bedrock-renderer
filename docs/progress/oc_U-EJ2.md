## NEXT
DONE

# Unit U-EJ2 - J2 startup self-check: content checks proven against 1.26.62.01

Goal (docs/RENDER_CHECKLIST.md line 199):
`J2 Startup self-check: 9 unique sigs added to Sigs.json (6dj); content checks (mask immediate, offset refs) to code in SelfTest, not built (P1) - infra; sigs re-checked per patch`

Scope of this unit: only the part of that line that is still pending, the content checks (mask immediate, field displacement refs, task stride) that SelfTest must assert, and whether each one is provable against the binary. The "9 unique sigs" half is already recorded as done; it is listed below only as the anchor set.

## Anchor set already present (not re-proven by this unit)

Read from `src/sdk/Sigs.json` (deps.bgfx, all priority "low" except taskDispatch "high"), each entry carries the 62.01 RVA in its comment:
- Encoder::submit 0xBC60740 (line 120)
- Encoder::reset 0xBC60D10 (line 121)
- Encoder::frameSort 0xBC61E20 (line 122)
- FrameGraph::endFrame 0xC270460 (line 128)
- FrameGraph::generate 0xC273420 (line 129)
- FrameGraph::taskDispatch 0xE9002E0 (line 130)
- FrameGraph::viewSetupTask 0x568CD90 (line 131)
- D3D12Context::drawExecutor 0xE821120 (line 134)
- D3D12Context::psoBuilder 0xE81E860 (line 135)

## Verbatim proof lines

Each line below was copied from `rdis dis` on Minecraft.Windows.exe 1.26.62.01 and is checked by `tools/sigs/verify_oc.py`.

0xE81E8EC  mov rsi,0x707007FFFFFF0FF
0xE81E8F6  and rsi,r13
0xE81E8F9  mov r14,0xFFFFFF00FFFFFF00
0xBC607BF  mov rcx,[rsi]
0xBC607C2  mov eax,[rcx+0xDC57E8]
0xBC607EA  lock cmpxchg [rcx+0xDC57E8],r14d
0xBC60991  mov [rcx+r14*8+0x14700],rax
0xBC6099C  mov [rax+r14*2+0x94700],di
0xBC60B13  movaps [rax+rcx+0xB4700],xmm0
0xE900366  mov r12,[rcx]
0xE900373  sar rax,7
0xE9003B6  sar rax,7
0xE900412  sub r12,0xFFFFFFFFFFFFFF80
0xE90052C  mov rax,[r12+0x70]
0xE90056B  mov rax,[r12+0x78]

## Answer table (one row per distinct constant or field the content checks name)

| name | field / displacement | size | read/store address | verbatim `0xRVA  instr` proof line(s) | meaning | tag |
|---|---|---|---|---|---|---|
| PSO key mask, first state word | 0x0707007FFFFFF0FF | 8 (mov r64, imm64) | psoBuilder 0xE81E860 body at +0x8C; mask ANDed onto r13 (the first state word) by `and rsi,r13` at 0xE81E8F6, program table base added at 0xE81E8E5 (`add rbx,0xB62178`) | 0xE81E8EC  mov rsi,0x707007FFFFFF0FF ; 0xE81E8F6  and rsi,r13 | key-mask immediate of the D3D12 graphics PSO lookup; single occurrence in the 0x1C9A-byte body | [V] |
| PSO key mask, second state word | 0xFFFFFF00FFFFFF00 | 8 (mov r64, imm64) | psoBuilder +0x99; mask ANDed onto r9 (second state word) by `and r14,r9` at 0xE81E908 | 0xE81E8F9  mov r14,0xFFFFFF00FFFFFF00 | second state-word mask of the same PSO key, loaded next to the 0x0707 mask | [V] |
| Frame item counter | Frame+0xDC57E8 | 4 (dword read; dword CAS) | submit 0xBC60740: rcx = [rsi] = Frame* at +0x7F, read at +0x82, CAS at +0xAA (r14d) | 0xBC607C2  mov eax,[rcx+0xDC57E8] ; 0xBC607EA  lock cmpxchg [rcx+0xDC57E8],r14d | m_numRenderItems: read, then bumped by compare-exchange with the next index; the slot counter for the draw header written later in the body (allocation role [I], the field and the CAS are [V]) | [V] |
| Frame sort values | Frame+0x94700 | 2 (word store, index r14 scaled by 2) | submit 0xBC60740 at +0x25C; rax = [rsi] = Frame* | 0xBC6099C  mov [rax+r14*2+0x94700],di | m_sortValues entry for the draw, u16 array parallel to the sort keys | [V] |
| Frame sort keys (supporting) | Frame+0x14700 | 8 (qword store, index r14 scaled by 8) | submit 0xBC60740 at +0x251; rcx = Frame* | 0xBC60991  mov [rcx+r14*8+0x14700],rax | m_sortKeys entry written in the same block as the 0x94700 store, both indexed by r14 (the draw slot) | [V] |
| Frame render-item header array | Frame+0xB4700 | 16 (movaps store) | submit 0xBC60740 at +0x3D3; rax = Frame*, rcx = draw index << 7 | 0xBC60B13  movaps [rax+rcx+0xB4700],xmm0 | 16-byte chunk stored into the 0x80-byte RenderDraw header array at Frame+0xB4700+(idx<<7) | [V] |
| Task-list entry stride | 0x80 bytes per entry | 0x80 (two `sar rax,7` divides, one `sub r12,-0x80` advance) | taskDispatch 0xE9002E0: begin pointer loaded at 0xE900366, byte distance divided by 0x80 at 0xE900373 and 0xE9003B6, walk pointer advanced by +0x80 at 0xE900412, last two fields of the current entry read at 0xE90052C and 0xE90056B | 0xE900373  sar rax,7 ; 0xE9003B6  sar rax,7 ; 0xE900412  sub r12,0xFFFFFFFFFFFFFF80 ; 0xE90052C  mov rax,[r12+0x70] ; 0xE90056B  mov rax,[r12+0x78] | entry count = (end-begin)>>7; the loop advances one 0x80-byte entry per iteration, and the per-entry reads land at +0x70 and +0x78, both inside the 0x80-byte record | [V] |

## What the SelfTest content check covers today

- Encoder::submit anchor `Encoder::submit` with kEncoderSubmit in `src/sdk/mc/deps/bgfx/RenderLayoutAsserts.h` (lines 27-48) already lists 0xDC57E8, 0x14700, 0x94700, 0xB4700 (plus 0x8B4700, 0x540, 0x518 and the encoder-side constants), so the three displacement refs named in 6dj are coded. [V file]
- psoBuilder anchor `D3D12Context::psoBuilder` with kPsoBuilder lists 0x0707007FFFFFF0FF (line 150) and 0xFFFFFF00FFFFFF00 (line 151), so both mask immediates are coded. [V file]
- taskDispatch anchor `FrameGraph::taskDispatch` with kTaskDispatch (lines 97-100) lists only 0x298 and 0x2A0; `docs/data/layout_asserts.json` lists for the same symbol 0x88, 0x298, 0x2a0, 0x18. Neither list contains the 0x80 entry stride, so the dispatch stride check is still uncoded. [V file]
- Build state: `build/Release/BlueySenseV2.dll` (written 2026-11-16 19:57) contains the literal `render layout drift` once, so checkRenderLayout is compiled into that artifact; I did not verify which DLL the launcher instance loads, and a launched game is out of scope for this unit. [V file]

Possible encoding for the missing stride check, if wanted: the listing of 0xE9002E0 contains the imm32 0xFFFFFF80 exactly once (the `sub r12,0xFFFFFFFFFFFFFF80` at 0xE900412), and that value is above the 0x100 floor the byte-search assertions use, so `{0xFFFFFF80, "task entry stride 0x80"}` would be a non-spurious constant for kTaskDispatch. A bare 0x80 cannot be used: 0x00000080 occurs incidentally as a stack displacement (`[rbp+0x80]`, `[rsp+0x80]`) in the same body.

CLOSES? NO - the dispatch content check is still not coded: kTaskDispatch (and layout_asserts.json for FrameGraph::taskDispatch) asserts 0x88/0x298/0x2A0/0x18 but not the 0x80-byte task-entry stride, and that absent assertion is the single blocking fact. The mask immediate, the Frame+0xDC57E8 / 0xB4700 / 0x94700 displacement refs and the stride itself are all proven above with [V] rows, so only the SelfTest code for the stride remains.
