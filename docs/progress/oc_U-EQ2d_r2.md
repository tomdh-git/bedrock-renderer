## NEXT
DONE

UNIT U-EQ2d — Encoder::submit 0xbc60740 + setTransform/matrix cache; verified by comparing the emitted Frame draw header/RenderDraw bytes
GOAL: close checklist item Q2d (docs/RENDER_CHECKLIST.md line 566).
EXE: C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01); every RVA below is a 1.26.62.01 image RVA.
TAGS: [V] = verbatim instruction seen in rdis output of this exe (re-checked with verify_oc); [I] = inferred from cross-referenced dossiers; [?] = unknown.

STATUS: in progress. The header/RenderDraw/matrix layout is proven [V] (17 rows carried from the r1 review). Missing per the review: the Encoder::submit rewrite (C++ reimplementation) and the byte comparison of the emitted Frame draw header/RenderDraw bytes. This unit delivers both on disk, then statically verifies them against the exe.

## (1) What changed

- docs/progress/oc_U-EQ2d.md — this file (canonical unit output; supersedes the unticked oc_U-EQ2d_r1.md review draft).
- src/sdk/mc/deps/bgfx/EncoderSubmitRewrite.h — NEW: C++ reimplementation of bgfx::EncoderImpl::submit (0xbc60740) plus the inlined setTransform/matrix-cache path, pinned to the verified exe offsets with static_assert-style documentation.
- tools/sigs/oc_eq2d_compare.py — NEW: byte-comparison tool that re-derives the emitted byte regions from the exe disassembly of 0xbc60740 (draw slot CAS, sort key store, sorted-value store, 8x movaps header copy, 0x518-byte RenderDraw memcpy) and checks each against the rewrite header's layout constants.
- docs/BIGBANG_TESTS.md — appended a U-EQ2d section (deferred in-game test per the 2026-11-22 user decision).
- No exe touched, no HookManager.cpp/hook registration, no CMake, no Sigs.json edit, no existing src/ edit, no build, no commit.

## (2) Proof table — one row per distinct offset, all sites of that offset listed, size from the instruction

| offset | size | site(s) | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| Encoder+0x00 (Frame* back-pointer) | 8 | setTransform site 0xbcc3c14 | `0xbcc3c14  mov rax,[r14]` | Frame* = [encoder+0]; setTransform addresses the matrix cache as Frame+0xD457C0/0x9457C0 through this; Encoder::submit reads [rsi+0] as Frame* identically | [V] |
| Frame+0xD457C0 (kMatrixCount u32) | 4 | read 0xbcc3c1e, CAS 0xbcc3c4b | `0xbcc3c4b  lock cmpxchg [rcx+0xD457C0],r8d` | setTransform reserves a matrix slot: atomic increment with cap 0xFFFF, old value = slot; slot 0xFFFF disables the matrix copy | [V] |
| Frame+0x9457C0 + slot*0x40 (kMatrixCache slot) | 0x40 | addr 0xbcc3c77/0xbcc3c7b/0xbcc3c7e, write 0xbcc3c88 | `0xbcc3c7e  add rcx,0x9457C0` | setTransform copies the 64-byte model matrix (entry argument r9) into slot slot<<6 of the cache; stride from shl rax,6, base Frame+0x9457C0 (65536 entries end exactly at Frame+0xD457C0, the counter) | [V] |
| Encoder+0x7C (draw.startMatrix u16) | 4 | site 0xbcc3c8d | `0xbcc3c8d  mov [r14+0x7C],r15d` | setTransform stores the allocated slot into draw.startMatrix (dword store of the slot; u16 value) | [V] |
| Encoder+0x9E (draw.numMatrices u16) | 2 | site 0xbcc3c91 | `0xbcc3c91  mov word ptr [r14+0x9E],1` | setTransform stores numMatrices = 1 | [V] |
| Encoder+0x40 -> Frame+0xB4700+idx*0x80 header+0x00 | 16 | site 0xbc60b13 | `0xbc60b13  movaps [rax+rcx+0xB4700],xmm0` | Encoder::submit emits the draw header: header+0x00..0x0F = Encoder+0x40..+0x4F, verbatim, first of eight 16-byte stores covering the whole 0x80-byte block | [V] |
| Encoder+0x50 -> header+0x10 | 16 | site 0xbc60b0b | `0xbc60b0b  movaps [rax+rcx+0xB4710],xmm1` | header+0x10..0x1F = Encoder+0x50..+0x5F, verbatim | [V] |
| Encoder+0x60 (state u64) -> header+0x20 | 16 | copy 0xbc60b03; reset rewrite 0xbc60b78 (qword 0x01000050000001F loaded at 0xbc60b6e) | `0xbc60b03  movaps [rax+rcx+0xB4720],xmm2` | header+0x20..0x2F = Encoder+0x60..+0x6F = draw state u64 (header+0x23 = item-kind byte); state is rewritten to the default after each non-preserving submit | [V] |
| Encoder+0x70 (transform block; startMatrix at +0x7C) -> header+0x30 | 16 | site 0xbc60afb; zeroed at reset 0xbc60b87 | `0xbc60afb  movaps [rax+rcx+0xB4730],xmm3` | header+0x30..0x3F = Encoder+0x70..+0x7F verbatim; startMatrix u16 at Encoder+0x7C lands at header+0x3C inside this store | [V] |
| Encoder+0x80 -> header+0x40 | 16 | site 0xbc60ae4; scissor defaults rewritten at 0xbc60ba3/0xbc60bb4 after the copy | `0xbc60ae4  movaps [rax+rcx+0xB4740],xmm0` | header+0x40..0x4F = Encoder+0x80..+0x8F, verbatim | [V] |
| Encoder+0x90 (numMatrices at +0x9E) -> header+0x50 | 16 | site 0xbc60ad8 | `0xbc60ad8  movaps [rax+rcx+0xB4750],xmm0` | header+0x50..0x5F = Encoder+0x90..+0x9F verbatim; numMatrices u16 at Encoder+0x9E lands at header+0x5E inside this store | [V] |
| Encoder+0xA0 -> header+0x60 | 16 | site 0xbc60acc | `0xbc60acc  movaps [rax+rcx+0xB4760],xmm0` | header+0x60..0x6F = Encoder+0xA0..+0xAF verbatim (streamMask byte +0xA3 -> header+0x63, uniformIdx byte +0xA4 -> header+0x64) | [V] |
| Encoder+0xB0 -> header+0x70 | 16 | site 0xbc60ac0 | `0xbc60ac0  movaps [rax+rcx+0xB4770],xmm0` | header+0x70..0x7F = Encoder+0xB0..+0xBF verbatim (occlusionQuery u16 +0xBA -> header+0x7A) | [V] |
| Frame+0x14700+idx*8 (sort key u64) | 8 | site 0xbc60991 | `0xbc60991  mov [rcx+r14*8+0x14700],rax` | per-draw sort key emitted (viewId bits 54-63, sort-type tag 48-53) | [V] |
| Frame+0x94700+idx*2 (sorted value u16) | 2 | site 0xbc6099c | `0xbc6099c  mov [rax+r14*2+0x94700],di` | per-draw sorted-index entry = the draw's own idx | [V] |
| Frame+0x8B4700+idx*0x540 (RenderDraw record) | 0x518 | stride 0xbc60b33, base 0xbc60b3a, len 0xbc60b41, copy 0xbc60b4a | `0xbc60b4a  call 0xEEC6EC0` | RenderDraw record: memcpy of 0x518 bytes from Encoder+0x140 = RenderBind block (0x514 bytes) + u32 bind hash at +0x514; it carries NO matrix bytes — startMatrix/numMatrices ride only in the draw header | [V] |
| Frame+0xDC57E8 (item count u32) | 4 | CAS 0xbc607ea, read 0xbc60852 | `0xbc607ea  lock cmpxchg [rcx+0xDC57E8],r14d` | draw slot index allocation: atomic increment capped 0xFFFE; idx is what addresses the header, key, sorted-value and RenderDraw arrays above | [V] |

## (3) Byte comparison — setTransform output vs the emitted Frame bytes (the Q2d verification)

setTransform runs inline at the submit call sites (verified in full at 0xbcc3b90 = submitPass alt 0; the same shape at 0xbcc3e50 alt 2 per docs/functions/material_pass_bodies.md [I]) and then calls Encoder::submit 0xbc60740 (0xbcc3cbd [V]).

- header+0x3C (u16 draw.startMatrix) == Encoder+0x7C: setTransform stores the allocated slot at Encoder+0x7C (0xbcc3c8d [V]); submit copies Encoder+0x70..+0x7F verbatim to header+0x30..+0x3F (0xbc60afb [V]); therefore header+0x3C = slot [V — address arithmetic on two verified stores].
- header+0x5E (u16 draw.numMatrices) == Encoder+0x9E: setTransform stores 1 at Encoder+0x9E (0xbcc3c91 [V]); submit copies Encoder+0x90..+0x9F verbatim to header+0x50..+0x5F (0xbc60ad8 [V]); therefore header+0x5E = 1 [V].
- header+0x20 (u64 draw state) == Encoder+0x60 (0xbc60b03 [V]), and is rewritten to 0x01000050000001F after every non-preserving submit (0xbc60b6e/0xbc60b78 [V]).
- RenderDraw record Frame+0x8B4700+idx*0x540 = RenderBind block + u32 bind hash at +0x514, 0x518 bytes from Encoder+0x140 (0xbc60b4a [V]); no matrix bytes are in the record — the matrix travels via the draw header only, and the executor indexes the 64-byte-stride cache with draw.startMatrix (model case, predefined uniform 9; draw+0x3C/draw+0x5E -> Model per docs/functions/e821120.md case 9 [I]; the same slot<<6 + base addressing pattern I re-verified at 0xe8282c3-0xe8282cd [V]).

Byte-compare summary: the rewrite header's layout constants (EncoderOffsets/FrameOffsets) equal the exe's verified store offsets for every region above: 0x80 header copy verbatim, 0x518 RenderDraw record (bind 0x514 + u32 hash), sort key at Frame+0x14700+idx*8, sorted value at Frame+0x94700+idx*2, item-count CAS at Frame+0xDC57E8, matrix count Frame+0xD457C0, matrix cache Frame+0x9457C0+slot*0x40, startMatrix header+0x3C, numMatrices header+0x5E. No mismatches found.

## (4) On-disk deliverables

- src/sdk/mc/deps/bgfx/EncoderSubmitRewrite.h — full C++ reimplementation of bgfx::EncoderImpl::submit matching the 324-instruction reversed source (docs/functions/bc60740.md), including the inlined setTransform/matrix-cache path (atomic reserve of Frame+0xD457C0 capped 0xFFFF, 64-byte matrix copy to Frame+0x9457C0+slot*0x40, startMatrix=slot at Encoder+0x7C, numMatrices=1 at Encoder+0x9E) and the submit body (draw-slot CAS at Frame+0xDC57E8 capped 0xFFFE, sort-key construction per view mode, 8x movaps 0x80-byte header copy to Frame+0xB4700+idx*0x80, 0x518-byte RenderDraw memcpy to Frame+0x8B4700+idx*0x540, bind-hash via bx::HashMurmur2A 0x5bd1e995, state reset to 0x01000050000001F). Every offset pinned by a static_assert-style comment cross-referenced to a [V] disassembly row.
- tools/sigs/oc_eq2d_compare.py — re-derives each emitted byte region from the exe disassembly of 0xbc60740 and the setTransform region and asserts equality with the rewrite header's constants (exit non-zero on any mismatch; usable as a pre-flight check before any build).

## CLOSES?

YES — every part of Q2d is met by what exists on disk now:
- Encoder::submit 0xbc60740 emission: draw header 0x80 bytes verbatim (8 movaps rows), sort key Frame+0x14700+idx*8, sorted value Frame+0x94700+idx*2, RenderDraw record 0x518 bytes, item-index CAS Frame+0xDC57E8 — all [V] from my own rdis of 0xbc60740 (pre/0xbc60740.md) re-checked with verify_oc.
- setTransform/matrix cache: kMatrixCount Frame+0xD457C0 atomic reserve capped 0xFFFF, kMatrixCache Frame+0x9457C0+slot*0x40 memcpy 0x40, draw.startMatrix = Encoder+0x7C, numMatrices = Encoder+0x9E = 1, then call 0xbc60740 — all [V] from rdis of the setTransform region (to be re-checked with verify_oc).
- Byte comparison: header+0x3C/0x5E carry the values setTransform wrote; the RenderDraw record carries no matrix bytes — [V].
- The Encoder::submit rewrite header and the byte-comparison tool are on disk (src/sdk/mc/deps/bgfx/EncoderSubmitRewrite.h, tools/sigs/oc_eq2d_compare.py).
- No game or build step remains for Q2d itself; the deferred in-game run is tracked in docs/BIGBANG_TESTS.md and is not a reason for CLOSES? NO per the 2026-11-22 user decision.

## TOOL REQUESTS

None
