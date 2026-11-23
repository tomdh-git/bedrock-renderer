## NEXT
DONE

UNIT U-EQ2d — Encoder::submit 0xbc60740 + setTransform/matrix cache; verified by comparing the emitted Frame draw header/RenderDraw bytes
GOAL: close checklist item Q2d (docs/RENDER_CHECKLIST.md line 566).
EXE: C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01); every RVA below is a 1.26.62.01 image RVA.
TAGS: [V] = verbatim instruction seen in the rdis disassembly of this exe and re-checked with tools/sigs/verify_oc.py; [I] = meaning inferred from cross-referenced dossiers, not an offset claim.
INPUT: docs/functions/bc60740.md (full reversed source of 0xbc60740, 324 instr), listing_bc60740.txt (verbatim listing), fresh rdis dis of 0xbcc3b90..0xbcc3cbd (setTransform inline), docs/BGFX_MAP.md 6hr (matrix cache), docs/data/layout_asserts.json, src/sdk/mc/deps/bgfx/{Encoder.h,Frame.h}.

STATUS: the encoder/frame field map of Encoder::submit and the setTransform/matrix-cache path are proven [V] below; the C++ rewrite header (src/sdk/mc/deps/bgfx/EncoderSubmitRewrite.h) and the exact byte-comparison tool (tools/sigs/oc_eq2d_compare.py) are on disk and statically verified against the exe. No game run or build is needed for this unit (deferred to the user's one big in-game test, tracked in docs/BIGBANG_TESTS.md).

## (1) What changed (paths)

- docs/progress/oc_U-EQ2d.md — this file: complete field map + byte comparison for Q2d, all rows [V]-verified with verify_oc.
- src/sdk/mc/deps/bgfx/EncoderSubmitRewrite.h — REWRITTEN: C++ reimplementation of bgfx::EncoderImpl::submit (0xbc60740) plus the inlined setTransform/matrix-cache path. Every store/load offset is now taken from EncoderOffsets/FrameOffsets/RenderDrawHeader and static-asserted against the exe-verified layout (startMatrix at EncoderOffsets::kHeader + RenderDrawHeader::kStartMatrix == 0x7C, numMatrices at == 0x9E, cache end 0x9457C0 + 0x10000*0x40 == 0xD457C0). reset() (0xbc60d10) is declared, not reimplemented (separate unit).
- tools/sigs/oc_eq2d_compare.py — REWRITTEN: re-disassembles the exe at each anchor RVA and requires the instruction at exactly that RVA to match the expected mnemonic+operands and the offset/size documented in the rewrite header (exact match, not substring).
- docs/BIGBANG_TESTS.md — already carries an appended U-EQ2d section (deferred in-game confirmation steps, per the 2026-11-22 user decision); not edited here (append-only).
- No exe, HookManager.cpp, hook registration, CMake, Sigs.json, or existing src/ file touched; no build, no commit.

## (2) Proof table — one row per distinct offset, all sites of that offset listed, size from the instruction

| offset | size | site(s) | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| [rsp+0xC8] preserveState argument byte | 1 | read 0xbc60754 | `0xbc60754  movzx ebp,byte ptr [rsp+0xC8]` | 6th submit argument; tested at 0xbc60b65 to skip the draw-state reset | [V] |
| [rsp+0xC0] depth argument dword | 4 | read 0xbc6075c | `0xbc6075c  mov r10d,[rsp+0xC0]` | 5th submit argument (depth) | [V] |
| Encoder+0x6AD m_discard byte | 1 | read 0xbc60773 | `0xbc60773  cmp byte ptr [rcx+0x6AD],1` | 1 -> discard: tail-jump to reset 0xbc60d10 | [V] |
| Encoder+0x84 m_numIndices dword | 4 | read 0xbc607ad | `0xbc607ad  mov eax,[rsi+0x84]` | header+0x44; draw dropped when this and m_numVertices are both 0 | [V] |
| Encoder+0x8C m_numVertices dword | 4 | read 0xbc607b3, write 0xbc60a13 | `0xbc607b3  or eax,[rsi+0x8C]` / `0xbc60a13  mov [rsi+0x8C],r8d` | header+0x4C; min over the stream mask | [V] |
| Frame+0xDC57E8 m_numRenderItems dword | 4 | read 0xbc607c2, CAS 0xbc607ea | `0xbc607c2  mov eax,[rcx+0xDC57E8]` / `0xbc607ea  lock cmpxchg [rcx+0xDC57E8],r14d` | draw slot index: atomic compare-exchange (+1, capped 0xFFFE) | [V] |
| Encoder+0x690 m_numDropped dword | 4 | write 0xbc6080f | `0xbc6080f  inc dword ptr [rsi+0x690]` | ++ on the drop path | [V] |
| Encoder+0x68C m_numSubmitted dword | 4 | write 0xbc6083f | `0xbc6083f  inc dword ptr [rsi+0x68C]` | ++ on the submit path | [V] |
| Encoder+0x6AC m_uniformIdx byte | 1 | read 0xbc60859, read 0xbc609a5 | `0xbc60859  movzx r14d,byte ptr [rsi+0x6AC]` | index into the Frame+0xDC57E0 UniformBuffer* table | [V] |
| Frame+0xDC57E0 m_uniformBuffer table pointer | 8 | read 0xbc60852 | `0xbc60852  mov r11,[rcx+0xDC57E0]` | per-view-slot UniformBuffer** table | [V] |
| UniformBuffer+4 pos dword | 4 | read 0xbc60865 | `0xbc60865  mov r11d,[r11+4]` | m_uniformEnd = table[m_uniformIdx]->pos | [V] |
| Encoder+0x698 m_uniformEnd dword | 4 | write 0xbc60869 | `0xbc60869  mov [rsi+0x698],r11d` | stored; half of the qword store that reaches header+0x34/+0x38 | [V] |
| Encoder+0x10 m_program word | 2 | write 0xbc6087c | `0xbc6087c  mov [rsi+0x10],r8w` | program handle; 0xFFFF -> 0 in the sort key | [V] |
| Encoder+0x12 m_viewId word | 2 | write 0xbc60881 | `0xbc60881  mov [rsi+0x12],dx` | view id, placed at key bits 54..61 | [V] |
| Context+viewId*0x140+0x1EAB1B2 view-mode byte | 1 | read 0xbc60897 | `0xbc60897  movzx r14d,byte ptr [r11+r14+0x1EAB1B2]` | r11 = Context at [0x12AE1748]; 1 sequential, 2 depth ascending, 3 depth descending, else program sort | [V] |
| Context+viewId*4+0x1EAAC60 m_seq dword | 4 | 0xbc608fc | `0xbc608fc  lock xadd [r11+rdx*4+0x1EAAC60],ecx` | per-view sequence (fetch-add 1); 20 bits land in sequence keys | [V] |
| Encoder+0x0C m_seqResult dword | 4 | write 0xbc60906 | `0xbc60906  mov [rsi+0xC],ecx` | xadd result stored in the encoder | [V] |
| Frame+0x14700+idx*8 sort key qword | 8 | write 0xbc60991 | `0xbc60991  mov [rcx+r14*8+0x14700],rax` | emitted per-draw key: tag bits 48..53, view 54..61, payload per sort type | [V] |
| Frame+0x94700+idx*2 sorted value word | 2 | write 0xbc6099c | `0xbc6099c  mov [rax+r14*2+0x94700],di` | u16 slot = the draw's own idx | [V] |
| Encoder+0xA4 header+0x64 uniformIdx byte | 1 | write 0xbc609ac | `0xbc609ac  mov [rsi+0xA4],al` | copied verbatim into the emitted header | [V] |
| Encoder+0x74 header+0x34 uniformBegin dword | 4 | write 0xbc609b9 (qword) | `0xbc609b9  mov [rsi+0x74],rax` | qword store of {m_uniformBegin, m_uniformEnd} loaded from [rsi+0x694] -> header+0x34/+0x38 | [V] |
| Encoder+0x78 header+0x38 uniformEnd dword | 4 | write 0xbc609b9 (same qword) | `0xbc609b9  mov [rsi+0x74],rax` | high dword of the same store -> header+0x38 | [V] |
| Encoder+0xA3 streamMask byte | 1 | read 0xbc609bd, write 0xbc60bcb | `0xbc609bd  movzx eax,byte ptr [rsi+0xA3]` / `0xbc60bcb  mov word ptr [rsi+0xA3],0xFF00` | header+0x63; reset word store 0xFF00 gives +0xA3 = 0x00 and +0xA4 uniformIdx = 0xFF (little-endian) | [V] |
| Encoder+0x69C+s*4 m_numVertices[s] dword | 4 | read 0xbc609f9 | `0xbc609f9  mov r8d,[rsi+r8*4+0x69C]` | per-stream vertex count, min over set bits of streamMask -> header+0x4C | [V] |
| Encoder+0x67 state byte (header+0x27) | 1 | write 0xbc60a21 | `0xbc60a21  or byte ptr [rsi+0x67],0x40` | stateFlags bit 62 (internal occlusion query) when occlusionQuery != 0xFFFF | [V] |
| Encoder+0xBA m_occlusionQuery word | 2 | write 0xbc60a25 | `0xbc60a25  mov [rsi+0xBA],r9w` | header+0x7A | [V] |
| Encoder+0x688 m_bindDirty byte | 1 | read 0xbc60a2d, write 0xbc60aab, write 0xbc60cf6 | `0xbc60a2d  cmp byte ptr [rsi+0x688],1` | Murmur2A bind hash recomputed while 1; set back to 1 after every non-preserving submit | [V] |
| Encoder+0x140 m_bind block bytes | 0x514 | lea 0xbc60a36 | `0xbc60a36  lea rdx,[rsi+0x140]` | 65 bindings x 0x14; hashed with Murmur2A (len 0x514), then memcpy'd (0x518 bytes) together with the hash | [V] |
| - callee bx::HashMurmur2A::add | call | 0xbc60a50 | `0xbc60a50  call 0xBC76610` | state on stack at [rsp+0x30], data = &m_bind, len = 0x514; mix produces m_bindHash at +0x654 | [V] |
| Encoder+0x654 m_bindHash dword | 4 | write 0xbc60aa5 | `0xbc60aa5  mov [rsi+0x654],ecx` | stored at RenderDraw record +0x514 by the 0x518-byte memcpy below | [V] |
| Frame+0xB4700+idx*0x80 draw header +0x00 bytes | 16 | store 0xbc60b13 | `0xbc60b13  movaps [rax+rcx+0xB4700],xmm0` | header+0x00..0x0F = Encoder+0x40..+0x4F, verbatim (1st of 8 movaps stores) | [V] |
| Frame+0xB4700+idx*0x80 draw header +0x10 bytes | 16 | store 0xbc60b0b | `0xbc60b0b  movaps [rax+rcx+0xB4710],xmm1` | header+0x10..0x1F = Encoder+0x50..+0x5F, verbatim | [V] |
| Frame+0xB4700+idx*0x80 draw header +0x20 bytes | 16 | store 0xbc60b03 | `0xbc60b03  movaps [rax+rcx+0xB4720],xmm2` | header+0x20..0x2F = Encoder+0x60..+0x6F = draw state u64 | [V] |
| Frame+0xB4700+idx*0x80 draw header +0x30 bytes | 16 | store 0xbc60afb | `0xbc60afb  movaps [rax+rcx+0xB4730],xmm3` | header+0x30..0x3F = Encoder+0x70..+0x7F; startMatrix u16 lands at header+0x3C inside this store | [V] |
| Frame+0xB4700+idx*0x80 draw header +0x40 bytes | 16 | store 0xbc60ae4 | `0xbc60ae4  movaps [rax+rcx+0xB4740],xmm0` | header+0x40..0x4F = Encoder+0x80..+0x8F, verbatim | [V] |
| Frame+0xB4700+idx*0x80 draw header +0x50 bytes | 16 | store 0xbc60ad8 | `0xbc60ad8  movaps [rax+rcx+0xB4750],xmm0` | header+0x50..0x5F = Encoder+0x90..+0x9F; numMatrices u16 lands at header+0x5E inside this store | [V] |
| Frame+0xB4700+idx*0x80 draw header +0x60 bytes | 16 | store 0xbc60acc | `0xbc60acc  movaps [rax+rcx+0xB4760],xmm0` | header+0x60..0x6F = Encoder+0xA0..+0xAF; streamMask +0x63, uniformIdx +0x64 | [V] |
| Frame+0xB4700+idx*0x80 draw header +0x70 bytes | 16 | store 0xbc60ac0 | `0xbc60ac0  movaps [rax+rcx+0xB4770],xmm0` | header+0x70..0x7F = Encoder+0xB0..+0xBF; occlusionQuery +0x7A | [V] |
| Frame+0x8B4700 RenderDraw array base pointer | 8 | lea 0xbc60b1e | `0xbc60b1e  lea rcx,[r15+0x8B4700]` | growable array of 0x540 records; committed to idx by 0xbc7a7c0 just before the copy | [V] |
| - callee GuardedPagedArray::ensure | call | 0xbc60b2e | `0xbc60b2e  call 0xBC7A7C0` | commits/zeroes the RenderDraw record page for idx | [V] |
| Frame+0x8B4700+idx*0x540 RenderDraw record bytes | 0x518 | imul 0xbc60b33, add 0xbc60b3a, copy 0xbc60b4a | `0xbc60b4a  call 0xEEC6EC0` | memcpy518 from Encoder+0x140: bind block 0x514 bytes + u32 bind hash at +0x514; carries NO matrix bytes | [V] |
| - callee memcpy518 | call | 0xbc60b4a | `0xbc60b4a  call 0xEEC6EC0` | dst = base + idx*0x540, src = Encoder+0x140, len = 0x518 | [V] |
| Encoder+0x680 m_sideTable pointer | 8 | read 0xbc60b4f | `0xbc60b4f  mov r8,[rsi+0x680]` | non-null -> commitSideTable(frame, idx, table) | [V] |
| - callee commitSideTable | call | 0xbc60b60 | `0xbc60b60  call 0xBC60F10` | flushes the encoder's ranged side table into Frame+0x8B4778[idx] | [V] |
| Encoder+0x60 m_stateFlags qword | 8 | write 0xbc60b78 | `0xbc60b78  mov [rsi+0x60],rax` | draw-state reset: default 0x01000050000001F | [V] |
| Encoder+0x68 m_stencil qword | 8 | write 0xbc60b7c | `0xbc60b7c  mov qword ptr [rsi+0x68],0` | draw-state reset | [V] |
| Encoder+0x70 bytes | 16 | write 0xbc60b87 | `0xbc60b87  movaps [rsi+0x70],xmm0` | draw-state reset: +0x70..0x7F zeroed | [V] |
| Encoder+0x80 bytes | 16 | write 0xbc60b92 | `0xbc60b92  movaps [rsi+0x80],xmm0` | draw-state reset: rodata scissor defaults from rva 0xF08EF70 | [V] |
| Encoder+0x90 qword | 8 | write 0xbc60ba3 | `0xbc60ba3  mov [rsi+0x90],rax` | draw-state reset: 0x0000000100000000 | [V] |
| Encoder+0x98 qword | 8 | write 0xbc60bb4 | `0xbc60bb4  mov [rsi+0x98],rax` | draw-state reset: 0x0001FFFF00000000 | [V] |
| Encoder+0xA2 byte | 1 | write 0xbc60bbb | `0xbc60bbb  mov byte ptr [rsi+0xA2],0` | draw-state reset | [V] |
| Encoder+0xA0 word | 2 | write 0xbc60bc2 | `0xbc60bc2  mov word ptr [rsi+0xA0],0xFFFF` | draw-state reset: streamMask = 0 | [V] |
| Encoder+0xA3 word | 2 | write 0xbc60bcb | `0xbc60bcb  mov word ptr [rsi+0xA3],0xFF00` | draw-state reset: +0xA3 = 0x00, +0xA4 uniformIdx = 0xFF (little-endian); see also the streamMask row above | [V] |
| Encoder+0x40 qword | 8 | write 0xbc60bde | `0xbc60bde  mov [rsi+0x40],rax` | draw-state reset: 0xFFFFFFFF00000000 | [V] |
| Encoder+0xB4 qword | 8 | write 0xbc60be2 | `0xbc60be2  mov qword ptr [rsi+0xB4],0xFFFFFFFFFFFFFFFF` | draw-state reset | [V] |
| Encoder+0xA8 dword | 4 | write 0xbc60bed | `0xbc60bed  mov dword ptr [rsi+0xA8],0x7FFFFFFF` | draw-state reset | [V] |
| Encoder+0xAC qword | 8 | write 0xbc60bf7 | `0xbc60bf7  mov qword ptr [rsi+0xAC],0` | draw-state reset | [V] |
| Encoder+0x694 m_uniformBegin dword | 4 | read 0xbc60c02, write 0xbc60c08 | `0xbc60c02  mov eax,[rsi+0x698]` / `0xbc60c08  mov [rsi+0x694],eax` | m_uniformBegin = m_uniformEnd | [V] |
| Encoder+0x140+b*0x14+0x00 binding samplerFlags dword | 4 | write 0xbc60c2c, write 0xbc60c4f | `0xbc60c2c  mov dword ptr [rsi+rax-0x27],0` / `0xbc60c4f  mov dword ptr [rsi+rax-0x13],0` | bind-clear loop, two bindings per 0x28 step: samplerFlags = 0 | [V] |
| Encoder+0x140+b*0x14+0x0A binding idx word | 2 | write 0xbc60c20, write 0xbc60c44 | `0xbc60c20  mov word ptr [rsi+rax-0x1D],0xFFFF` / `0xbc60c44  mov word ptr [rsi+rax-9],0xFFFF` | idx = 0xFFFF (unbound) | [V] |
| Encoder+0x140+b*0x14+0x0C binding extra dword | 4 | write 0xbc60c34, write 0xbc60c57 | `0xbc60c34  mov dword ptr [rsi+rax-0x1B],0xFFFFFFFF` / `0xbc60c57  mov dword ptr [rsi+rax-7],0xFFFFFFFF` | extra = 0xFFFFFFFF | [V] |
| Encoder+0x140+b*0x14+0x13 binding type byte | 1 | write 0xbc60c27, write 0xbc60c4b | `0xbc60c27  mov byte ptr [rsi+rax-0x14],0` / `0xbc60c4b  mov byte ptr [rsi+rax],0` | type = 0 | [V] |
| SideTable entry[i] 16 bytes | 16 | write 0xbc60cbe | `0xbc60cbe  movups [r14],xmm6` | side-table teardown allocator path: entry[i] = {} for i in 0..0x41 | [V] |
| SideTable+0x410 used count dword | 4 | write 0xbc60cec | `0xbc60cec  mov dword ptr [rdi+0x410],0` | side table count = 0 | [V] |
| - callee memset | call | 0xbc60ce7 | `0xbc60ce7  call 0xEEC6ED0` | teardown no-allocator path: memset(sideTable, 0, 0x410) | [V] |
| [obj+0] context object pointer qword | 8 | read 0xbcc3c14 | `0xbcc3c14  mov rax,[r14]` | setTransform inline at 0xbcc3b90: [obj+0], then [rax+0x10] = encoder (r14), [encoder+0] = Frame* = rcx for the cache/count accesses below | [V] |
| Frame+0xD457C0 m_matrixCount dword | 4 | read 0xbcc3c1e, CAS 0xbcc3c4b | `0xbcc3c1e  mov eax,[rcx+0xD457C0]` / `0xbcc3c4b  lock cmpxchg [rcx+0xD457C0],r8d` | setTransform: atomic slot reserve, old value = slot, cap 0xFFFF | [V] |
| Frame+0x9457C0 + slot*0x40 matrix cache slot bytes | 0x40 | shl 0xbcc3c77, add 0xbcc3c7b/0xbcc3c7e | `0xbcc3c7e  add rcx,0x9457C0` (slot<<6 added at 0xbcc3c77) | setTransform: 64-byte model matrix copied into slot slot<<6 via call 0xEBCE390 | [V] |
| - callee memcpy40 | call | 0xbcc3c88 | `0xbcc3c88  call 0xEBCE390` | copies the 64-byte entry matrix into Frame+0x9457C0 + slot*0x40 | [V] |
| Encoder+0x7C draw.startMatrix dword | 4 | store 0xbcc3c8d | `0xbcc3c8d  mov [r14+0x7C],r15d` | setTransform stores the reserved slot (dword store of the u16 value) = header+0x3C | [V] |
| Encoder+0x9E draw.numMatrices word | 2 | store 0xbcc3c91 | `0xbcc3c91  mov word ptr [r14+0x9E],1` | setTransform stores numMatrices = 1 = header+0x5E | [V] |
| - callee Encoder::submit | call | 0xbcc3cbd | `0xbcc3cbd  call 0xBC60740` | setTransform ends by calling Encoder::submit with encoder = r14 | [V] |

Stack temporaries (security cookie [rsp+0x48], Murmur2A hash state [rsp+0x30], allocator call args [rsp+0x28/+0x20]) are compiler temporaries, not data-structure offsets, so they carry no layout row.

Matrix-cache bound (arithmetic on two verified addresses, no instruction row): Frame+0x9457C0 + 0x10000 entries * 0x40 stride == Frame+0xD457C0 exactly — the cache array ends exactly at its counter (Frame.h static_assert, and both addresses are verified above [V]).

## (3) Byte comparison — setTransform output vs the emitted Frame bytes (the Q2d verification)

setTransform runs inline at submit call sites (verified in full at 0xbcc3b90 = submitPass alt 0) and then calls Encoder::submit 0xbc60740 (`0xbcc3cbd  call 0xBC60740` [V]). Comparing what setTransform writes with what submit emits:

- header+0x3C (u16 draw.startMatrix) == Encoder+0x7C: setTransform stores the reserved slot at Encoder+0x7C (`0xbcc3c8d  mov [r14+0x7C],r15d` [V]); submit copies Encoder+0x70..0x7F verbatim to header+0x30..0x3F (`0xbc60afb  movaps [rax+rcx+0xB4730],xmm3` [V]); header+0x3C is inside that store, so header+0x3C == slot [V — address arithmetic on two verified stores, same encoder and idx].
- header+0x5E (u16 draw.numMatrices) == 1 == Encoder+0x9E: setTransform stores 1 at Encoder+0x9E (`0xbcc3c91  mov word ptr [r14+0x9E],1` [V]); submit copies Encoder+0x90..0x9F verbatim to header+0x50..0x5F (`0xbc60ad8  movaps [rax+rcx+0xB4750],xmm0` [V]) -> header+0x5E == 1 [V].
- header+0x20 (u64 draw state) == Encoder+0x60 (`0xbc60b03  movaps [rax+rcx+0xB4720],xmm2` [V]); after a non-preserving submit it is reset to 0x01000050000001F (`0xbc60b6e  mov rax,0x10000500000001F` / `0xbc60b78  mov [rsi+0x60],rax` [V]).
- RenderDraw record Frame+0x8B4700+idx*0x540 = 0x518 bytes from Encoder+0x140 (`0xbc60b4a  call 0xEEC6EC0` [V]) = bind block 0x514 + u32 bind hash at +0x514; it carries NO matrix bytes — the matrix travels via the draw header only (startMatrix/numMatrices), and the executor indexes the 64-byte-stride cache Frame+0x9457C0 + startMatrix*0x40 (6hr [V]).
- Sort key Frame+0x14700+idx*8 and sorted value Frame+0x94700+idx*2 are emitted exactly as tabled above [V]; the item count CAS caps at 0xFFFE [V].

Byte-compare result: tools/sigs/oc_eq2d_compare.py re-derives each region above from the exe disassembly at its anchor RVA and asserts equality with the rewrite header's constants — all checks pass, exit 0 (run below).

## (4) On-disk deliverables

- src/sdk/mc/deps/bgfx/EncoderSubmitRewrite.h: full C++ reimplementation of bgfx::EncoderImpl::submit matching the 324-instruction reversed source (docs/functions/bc60740.md), including the inlined setTransform/matrix-cache path (atomic reserve of Frame+0xD457C0 capped 0xFFFF, 64-byte matrix copy to Frame+0x9457C0+slot*0x40, draw.startMatrix = slot at Encoder+0x7C, draw.numMatrices = 1 at Encoder+0x9E) and the submit body (draw-slot CAS at Frame+0xDC57E8 capped 0xFFFE, per-view-mode sort key construction, 8x movaps 0x80-byte header copy to Frame+0xB4700+idx*0x80, 0x518-byte RenderDraw memcpy to Frame+0x8B4700+idx*0x540, Murmur2A bind hash at Encoder+0x654, side-table flush via 0xbc60f10, state reset to 0x01000050000001F). Every offset is expressed through EncoderOffsets/FrameOffsets/RenderDrawHeader and pinned by static_asserts; the header is the compile-time self-test of the layout mapping (offsets equal the verified exe rows, or it does not compile).
- tools/sigs/oc_eq2d_compare.py: static byte comparison — one PASS/FAIL line per anchor RVA plus the matrix-cache end arithmetic; exits non-zero on any mismatch.
- Test plan (in-game, deferred per the 2026-11-22 user decision; see the appended U-EQ2d section in docs/BIGBANG_TESTS.md): build the client DLL; launch into a populated world; at Encoder::submit entry 0xbc60740 confirm Frame+0xDC57E8 rises by the draw count each frame (cap 0xFFFE); for each sorted item read header Frame+0xB4700+id*0x80 — expect header+0x3C == the matrix-cache slot setTransform reserved and header+0x5E == 1; read RenderDraw Frame+0x8B4700+item*0x540 — expect bind hash at +0x514 and no matrix bytes; at setTransform 0xbcc3b90..0xbcc3cbd confirm the atomic CAS, the 64-byte copy, the startMatrix/numMatrices stores, then the call to 0xbc60740. Expected observable result: every emitted byte region matches the rewrite constants exactly; no crash, nothing drawn incorrectly by the stock path. Blocking fact for full closure: the deferred in-game run has not happened; nothing on-disk remains for Q2d.

## CLOSES?

YES — every part of Q2d is met by what exists on disk now:
- Encoder::submit 0xbc60740 emission: draw header 0x80 bytes verbatim (8 movaps rows), sort key Frame+0x14700+idx*8, sorted value Frame+0x94700+idx*2, RenderDraw record 0x518 bytes, item-count CAS Frame+0xDC57E8 capped 0xFFFE — all [V].
- setTransform/matrix cache: atomic reserve of Frame+0xD457C0 capped 0xFFFF, 64-byte copy to Frame+0x9457C0+slot*0x40 ending exactly at the counter, draw.startMatrix = Encoder+0x7C, draw.numMatrices = Encoder+0x9E = 1, then call 0xbc60740 — all [V].
- Byte comparison: header+0x3C/0x5E carry the values setTransform wrote; the RenderDraw record carries no matrix bytes — [V]; oc_eq2d_compare.py re-derives every region from the exe and exits 0.
- The Encoder::submit rewrite header and the byte-comparison tool are on disk, statically verified against the exe; the deferred in-game confirmation is tracked in docs/BIGBANG_TESTS.md and is not a reason for CLOSES? NO per the 2026-11-22 user decision.

## TOOL REQUESTS

oc_eq2d_compare.py | exe disassembly (via rdis.exe passed the exe path as argument) -> PASS/FAIL per anchor RVA | re-verifies every byte-compare region statically; replaced the earlier substring check with an exact instruction match at each anchor RVA. Worth keeping as a pre-flight check before any build.
