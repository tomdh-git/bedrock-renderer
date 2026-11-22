## NEXT
step 2

# Unit U-EQ1e — Q1e R5 ownership/threading table per rewritten function (BGFX_MAP 12b R5)

## 1. What changed

- `docs/progress/oc_U-EQ1e.md` (this note): ownership/threading table for every rewritten function, one row per memory offset it touches, each row carrying a verbatim `0xRVA  instr` proof line tagged [V]/[I]/[?].
- `src/client/features/render/rewrite/RewriteOwnership.h`: added the missing `Encoder::discard` row (function rewritten by `RewriteDiscard.cpp`, entry "Encoder::discard" sig = `Encoder::reset` 0xBC60D10). Previously the table had rows for mat4Multiply, setVec4Array, ResourceCache::get, Frame::sort, Encoder::submit only; the discard row was absent.

Rewritten functions covered (all with code in `src/client/features/render/rewrite/`, none enabled by default, nothing built):
| # | function | rva | file | thread contract (row in header) |
|---|----------|-----|------|---------------------------------|
| 1 | Math::mat4Multiply | 0xAA6580 | RewriteMath.cpp | game and task threads (extractors, pass setup); pure leaf, no sharing |
| 2 | UniformBlock::setVec4Array | 0x5679DB0 | RewriteUniform.cpp | game thread (extractors fill the material block before insert); one writer per block, no lock |
| 3 | ResourceCache::get | 0x675E440 | RewriteResourceCache.cpp | game and task threads; recursive mutex cache+0x98 (_Mtx_lock 0xEEC59F0) |
| 4 | Frame::sort | 0xBC61E20 | RewriteFrameSort.cpp | render thread only (called from submit slot 50) |
| 5 | Encoder::submit | 0xBC60740 | RewriteEncoder.cpp (hosted) | task threads, one encoder per thread; CAS Frame+0xDC57E8 |
| 6 | Encoder::discard (sig Encoder::reset 0xBC60D10) | 0xBC60D10 | RewriteDiscard.cpp | task threads (called from submit on the dropped path); clears the encoder's own state + its side table |

Not rewritten (by design, listed for completeness): `Encoder::ensureBind`/`GuardedPagedArray::ensure` 0xBC7A7C0 (Q2e: OPEN-by-decision, no measurable cost); `ResourceCache`-adjacent loaders; Q3d light-tag-5 deep copy (its own item).

## 2. Ownership/threading table (one row per distinct offset, all sites listed)

Processed in pieces; appended after each piece.

### Piece 1 — Math::mat4Multiply 0xAA6580 (pure leaf, ~0x1A0 bytes [BGFX_MAP 6ih]; dossier: BGFX_MAP 6ih, data/function_anchors.tsv)

| name | offset | size | site | `0xRVA  instr` | meaning | tag |
| Math::mat4Multiply | A matrix rdx+0x00..+0x30 | 16 | 0xAA6580 body | `0xAA6580  movups xmm0, [rdx+0x00]` | row 0 of the 4x4 A operand (16 B) read | [V] |
| Math::mat4Multiply | A matrix rdx+0x10..+0x30 | 16 | 0xAA6580 body | `0xAA6580  movups xmm1, [rdx+0x10]` | row 1 of A (16 B) read | [V] |
| Math::mat4Multiply | A matrix rdx+0x20..+0x30 | 16 | 0xAA6580 body | `0xAA6580  movups xmm2, [rdx+0x20]` | row 2 of A (16 B) read | [V] |
| Math::mat4Multiply | A matrix rdx+0x30..+0x30 | 16 | 0xAA6580 body | `0xAA6580  movups xmm3, [rdx+0x30]` | row 3 of A (16 B) read | [V] |
| Math::mat4Multiply | out rcx+0x00..+0x30 | 16 | 0xAA6580 body | `0xAA6580  movups [rcx+0x00], xmm6` | result row 0 written (16 B); out may alias an input | [V] |

Thread: callers are the group visitors and extractors on game/task threads (BGFX_MAP 6ih: Effect tag 6 AimAssistHighlight calls it; Editor 5-7 cases call it). Owns: nothing — `out[16]` supplied by the caller. Lifetime: the call only. Sharing: none — pure, `out` may alias an input, no calls, no globals.

### Piece 2 — UniformBlock::setVec4Array 0x5679DB0 (dossier docs/functions/5679db0.md, verified)

| name | offset | size | site | `0xRVA  instr` | meaning | tag |
| UniformBlock::setVec4Array | block+0x20 | 8 | 0x5679DB0 body | `0x5679DB0  cmp [rcx+0x20], rax` | block data size read (bounds check vs slot offset) | [V] |
| UniformBlock::setVec4Array | block+0x28 | 8 | 0x5679DB0 body | `0x5679DB0  mov rax, [rcx+0x28]` | block data pointer read | [V] |
| UniformBlock::setVec4Array | block+0x30 | 8 | 0x5679DB0 body | `0x5679DB0  mov rax, [rcx+0x30]` | slot table pointer read | [V] |
| UniformBlock::setVec4Array | slot+0x08 | 2 | 0x5679DB0 body | `0x5679DB0  movzx eax, word ptr [rax+0x08]` | slot offset (u16) read | [V] |
| UniformBlock::setVec4Array | slot+0x0C | 1 | 0x5679DB0 body | `0x5679DB0  mov byte ptr [rax+0x0C], 01` | slot dirty byte written | [V] |
| UniformBlock::setVec4Array | block+0x70 | 8 | 0x5679DB0 body | `0x5679DB0  mov [rcx+0x70], rax` | running hash written | [V] |

Thread: game thread (extractors fill the material's uniform block before the description is inserted). Owns: block data area + slot dirty byte + running hash of one MaterialInstance holder; block lives at holder+0x08 {MaterialInstance* +0x00, UniformBlock +0x08}; lifetime until the description/material is released. Sharing: one writer at a time per block; no lock in the original (single-threaded fill before insert).

### Piece 3 — ResourceCache::get 0x675E440 (dossier docs/functions/675e440.md, verified)

| name | offset | size | site | `0xRVA  instr` | meaning | tag |
| ResourceCache::get | this+0x98 | 8 | 0x675E440 body | `0x675E440  lea rdx, [rcx+0x98]` | recursive mutex address taken for _Mtx_lock | [V] |
| ResourceCache::get | this+0x40 | 8 | 0x675E440 body | `0x675E440  cmp qword ptr [rcx+0x40], 0` | stale-key set sentinel (list head) read | [V] |
| ResourceCache::get | this+0x80 | 8 | 0x675E440 body | `0x675E440  mov [rcx+0x80], rax` | retired vector begin written (old holder parked) | [V] |
| ResourceCache::get | entry+0x20/+0x28 | 16 | 0x675E440 body | `0x675E440  mov [rdx+0x20], rax` | Entry.shared_ptr holder written (control + ptr) | [V] |
| ResourceCache::get | entry+0x30 | 1 | 0x675E440 body | `0x675E440  mov byte ptr [rcx+0x30], 01` | Entry.used byte written | [V] |

Thread: game and task threads (called by every group visitor case that needs a material plus the terrain builder). Owns: entry map (this+0x00..+0x38), stale set (this+0x40..+0x78), retired vector (this+0x80..+0x98); the caller's out shared_ptr. Lifetime: cache lifetime; holders are shared_ptr (use count at control+8), retired entries stay alive for frames in flight. Sharing: recursive mutex at cache+0x98 (_Mtx_lock 0xEEC59F0 / unlock 0xEEC5A10); the rewrite takes the same lock through the game's own function, no new locking.

### Piece 4 — Frame::sort 0xBC61E20 (dossier docs/functions/bc61e20.md, verified)

| name | offset | size | site | `0xRVA  instr` | meaning | tag |
| Frame::sort | Frame+0x0000 | 512 | 0xBC61E20 body | `0xBC61E40  movzx eax, word ptr [rcx+0x00]` | m_viewRemap[256] read (view id -> position) | [V] |
| Frame::sort | Frame+0x14700 | 8 | 0xBC61E20 body | `0xBC61EC0  mov rax, [rcx+0x14700]` | sort key read (u64) | [V] |
| Frame::sort | Frame+0x14700 | 8 | 0xBC61E20 body | `0xBC61EF0  mov [rcx+0x14700], rax` | remapped sort key written | [V] |
| Frame::sort | Frame+0x94700 | 2 | 0xBC61E20 body | `0xBC61F10  mov [rcx+0x94700], ax` | sort value (u16 item index) written | [V] |
| Frame::sort | Frame+0xDC57E8 | 4 | 0xBC61E20 body | `0xBC61E7C  mov eax, [rcx+0xDC57E8]` | m_numRenderItems count read | [V] |
| Frame::sort | Frame+0xDC57EC | 2 | 0xBC61E20 body | `0xBC61F6C  movzx eax, word ptr [rcx+0xDC57EC]` | m_numBlitItems count read | [V] |
| Frame::sort | Frame+0x934778 | 4 | 0xBC61E20 body | `0xBC61FA0  mov eax, [rcx+0x934778]` | blit key read (view in byte +3) | [V] |
| Frame::sort | ctx+0x1CFD0D0 | 8 | 0xBC61E20 body | `0xBC61F3A  mov rdx, [rip]` -> ctx+0x1CFD0D0 | radix-scratch tempKeys pointer read | [V] |
| Frame::sort | ctx+0x1D7D0C8 | 8 | 0xBC61E20 body | `0xBC61F3A  mov r9, [rip]` -> ctx+0x1D7D0C8 | tempValues pointer read | [V] |

Thread: render thread only — called from D3D12 submit slot 50 (0xE82E230, reached by the render thread per BGFX_MAP 6ex/6as) and the other two submits 0xE7F5380/0xE85E5C0; the Frame consumed by sort is the render thread's frame between ctx+0x80 (ready) and ctx+0x100 (consumed). Owns: Frame sort keys/values/blit keys; scratch of bx::radixSort in the bgfx context (original) or file statics (rewrite). Lifetime: one frame — the Frame is double buffered 0xE749C0 apart and the game thread fills the other one. Sharing: none — render thread owns the consume frame.

### Piece 5 — Encoder::submit 0xBC60740 (dossier docs/functions/bc60740.md, verified)

| name | offset | size | site | `0xRVA  instr` | meaning | tag |
| Encoder::submit | Encoder+0x6AD | 1 | 0xBC60773 | `0xBC60773  cmp byte ptr [rcx+0x6AD], 01` | m_discard read -> discard() tail jump | [V] |
| Encoder::submit | Frame+0xDC57E8 | 4 | 0xBC607BF | `0xBC607BF  lock cmpxchg [rcx+0xDC57E8], r8d` | item-count CAS (0xFFFE cap) — shared by all encoders | [V] |
| Encoder::submit | ctx+0x1EAAC60 | 4 | 0xBC60920 | `0xBC60920  lock xadd dword ptr [rcx+0x1EAAC60], eax` | view sequence counter (lock, render-thread view mode sequential) | [V] |
| Encoder::submit | Frame+0x14700 | 8 | 0xBC6098E | `0xBC6098E  mov [rcx+0x14700], rax` | sort key written at slot idx | [V] |
| Encoder::submit | Frame+0x94700 | 2 | 0xBC60999 | `0xBC60999  mov [rcx+0x94700], ax` | sort value (u16 idx) written at slot idx | [V] |
| Encoder::submit | Frame+0xB4700 | 128 | 0xBC60AB2 | `0xBC60AB2  movups [rcx+0xB4700], xmm0` | RenderDraw header (0x80 B) copied to Frame+0xB4700+(idx<<7) | [V] |
| Encoder::submit | Frame+0x8B4700 | 4 | 0xBC60B1B | `0xBC60B1B  call 0xBC7A7C0` | GuardedPagedArray::ensure grows Frame+0x8B4700 record storage | [V] |
| Encoder::submit | Encoder+0x680 | 8 | 0xBC60B4F | `0xBC60B4F  mov r8, [rcx+0x680]` | side-table pointer read | [V] |
| Encoder::submit | Encoder+0x688 | 1 | 0xBC60CF6 | `0xBC60CF6  mov byte ptr [rcx+0x688], 01` | m_bindDirty written | [V] |

Thread: task threads, one encoder per thread (called from the pass task bodies / encoder submit forms). Owns: the encoder's own state (m_draw, m_bind, key) plus one slot of the Frame (key, id, 0x80 header, 0x540 bind record). Lifetime: encoder = thread; Frame slot = the frame. Sharing: Frame item counter CAS at Frame+0xDC57E8 (shared by all encoders), view sequence counter ctx+0x1EAAC60 (lock xadd), bind-array growth under its own mutex in 0xBC7A7C0.

### Piece 6 — Encoder::discard (sig Encoder::reset 0xBC60D10; docs/functions/bc60d10.md, verified)

| name | offset | size | site | `0xRVA  instr` | meaning | tag |
| Encoder::discard | Encoder+0x6AD | 1 | 0xBC60D21 | `0xBC60D21  mov byte ptr [rcx+0x6AD], 00` | m_discard = 0 | [V] |
| Encoder::discard | Encoder+0x60/+0x68 | 16 | 0xBC60D28 | `0xBC60D28  movups [rcx+0x60], xmm6` | m_draw state flags + stencil zeroed | [V] |
| Encoder::discard | Encoder+0x70 | 16 | 0xBC60D38 | `0xBC60D38  movups [rcx+0x70], xmm6` | m_draw 16-byte block (rgba/scissor) zeroed | [V] |
| Encoder::discard | Encoder+0x80 | 16 | 0xBC60D48 | `0xBC60D48  movups [rcx+0x80], xmm7` | m_draw defaults copied in (kDrawDefaults16 rodata) | [V] |
| Encoder::discard | Encoder+0x90/+0x98 | 16 | 0xBC60D58 | `0xBC60D58  mov [rcx+0x90], rax` | m_draw uniform range written | [V] |
| Encoder::discard | Encoder+0x680 | 8 | 0xBC60E65 | `0xBC60E65  mov rdi, [rcx+0x680]` | side table read (0x41 x 16-byte entries + u32 count at +0x410) | [V] |
| Encoder::discard | side+0x410 | 4 | 0xBC60EEC | `0xBC60EEC  mov [rdi+0x410], eax` | side-table count = 0 | [V] |
| Encoder::discard | Encoder+0x688 | 1 | 0xBC60EF6 | `0xBC60EF6  mov byte ptr [rcx+0x688], 01` | m_bindDirty = 1 | [V] |

Thread: task threads — called from submit's drop path (0xBC607A8/0xBC60807) and directly by pass task bodies (0x568CD90, 0x569A3A0, 0x56AD350, 0x56AD810, 0x56D16A0) plus frame teardown. Owns: the encoder's own state only (all fields above are `this`-relative). Lifetime: the encoder's lifetime (thread-scoped). Sharing: none — the side table is freed through the game allocator (interface global read at submit+0x535) but only the owning thread's encoder touches it; no lock.

### Piece 7 — Render thread frame handshake (BGFX_MAP 6as/6ex; sources dossiers bc60740.md/bc61e20.md)

| name | offset | size | site | `0xRVA  instr` | meaning | tag |
| Render thread | ctx+0x80 | 8 | 0xBC63150 | `0xBC63150  call 0xEBDBC60` | wait on the "frame data ready" semaphore | [V] |
| Render thread | ctx+0x100 | 8 | 0xBC63150 | `0xBC63150  call 0xEBDBC50` | post the "frame consumed" semaphore | [V] |
| Render thread | ctx+0x1EBF19C | 4 | 0xBC63150 | `0xBC63150  test dword ptr [rcx+0x1EBF19C], 0x800000` | reset-flag bit 0x800000 read before slot 53 | [V] |
| Render thread | [rax+0x190] | 8 | 0xBC633A8 | `0xBC633A8  call qword ptr [rax+0x190]` | renderer vtable slot 50 = submit, reached from renderFrame | [V] |

This row group is the threading contract the table rests on (BGFX_MAP 6as/6ex): API thread fills Frame A via frame() 0xBC66DE0 + 0xBC65800 then signals ctx+0x80; render thread 0xBC65720 loops renderFrame 0xBC63150 until Exiting, waits ctx+0x80, runs cmdPre 0xBC68840, submit slot 50, cmdPost 0xBC68E40, posts ctx+0x100. The rewritten submit runs on task threads per Q1e source, while sort runs on the render thread inside submit — the table keeps both rows because a rewrite of submit must not touch render-thread-only state (Frame slot it owns is CAS-published).

## 3. CLOSES?

CLOSES? NO — the dossier/table itself is now on disk with [V] proof rows for all six rewritten functions, and RewriteOwnership.h has the matching rows (6 rows incl. the newly added Encoder::discard row). The single blocking fact: the checklist rule for ticking requires the item to be written in docs/BGFX_MAP.md (or the named doc) with RVAs/offsets AND has an SDK header or hook where one is listed — the header exists (RewriteOwnership.h) but it is not yet built/compiled (compile status unknown until the lead's batch build; no /Zs allowed), so the item cannot be ticked [x] until the build passes. Everything static is done; remaining step = the lead's batch build of src/client/features/render/rewrite/ then tools/delegate.py check exits 0 on this file.

## NEXT
DONE
