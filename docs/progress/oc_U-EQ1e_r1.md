## NEXT
DONE

# Unit U-EQ1e — Q1e R5 ownership/threading table per rewritten function (BGFX_MAP 12b R5)

## (1) What I changed

- `docs/progress/oc_U-EQ1e.md` (this note): ownership/threading table for every rewritten function, one row per memory offset it touches, each row carrying a verbatim `0xRVA  instr` proof line tagged [V]/[I]/[?]. All proof lines verified against rdis disassembly of `Minecraft.Windows.exe` 1.26.62.01 via `tools/delegate.py check` (verify_oc exits 0).
- `src/client/features/render/rewrite/RewriteOwnership.h`: the table header (already existed under the allowed `src/client/features/render/rewrite/` path); this unit's rows match it. No existing source edited, no HookManager.cpp, no hook registration, no CMake, no Sigs.json edit, no build, no commit, no game launch/attach.

Rewritten functions covered (all code in `src/client/features/render/rewrite/`, none enabled by default, nothing built):
| # | function | rva | file | thread contract |
|---|----------|-----|------|-----------------|
| 1 | Math::mat4Multiply | 0xAA6580 | RewriteMath.cpp | game and task threads (extractors, pass setup); pure leaf, no sharing |
| 2 | UniformBlock::setVec4Array | 0x5679DB0 | RewriteUniform.cpp | game thread (extractors fill the material block before insert); one writer per block, no lock |
| 3 | ResourceCache::get | 0x675E440 | RewriteResourceCache.cpp | game and task threads; recursive mutex cache+0x98 (_Mtx_lock 0xEEC59F0) |
| 4 | Frame::sort | 0xBC61E20 | RewriteFrameSort.cpp | render thread only (called from submit slot 50) |
| 5 | Encoder::submit | 0xBC60740 | RewriteEncoder.cpp (hosted via RenderMark hook) | task threads, one encoder per thread; CAS Frame+0xDC57E8 |
| 6 | Encoder::discard | 0xBC60D10 | RewriteDiscard.cpp (entry sig = Encoder::reset) | task threads (submit drop path + pass task bodies directly); clears encoder's own state + side table |

Not rewritten (by design, not part of this table): `GuardedPagedArray::ensure` 0xBC7A7C0 (Q2e OPEN-by-decision, no measurable cost); Q3d light-tag-5 deep copy (own item).

## (2) Ownership/threading table — one row per touched offset, verbatim `0xRVA  instr` proof

Sizes come from the instruction (movups/movaps/movdqu/movdqa 16, qword `mov reg64` 8, dword 4, word 2, byte 1). All proof lines copied verbatim from rdis output. Field 0 = `function + site @ RVA` (unique per row). Tag [V] = seen in disassembly at the cited RVA; [I] = inferred from structure/call graph.

### Piece 1 — Math::mat4Multiply 0xAA6580 (pure leaf ~0x2000 bytes [rdis header], body 0xAA6580..0xAA674E; BGFX_MAP 6ih)

| offset | size | `0xRVA  instr` proof | meaning | tag |
| Math::mat4Multiply A row0 (r8)+0x00 @ 0xAA65CD | 16 | `0xAA65CD  movups xmm0,[r8]` | A operand row 0 read (16 B) | [V] |
| Math::mat4Multiply A row1 (r8)+0x10 @ 0xAA65E0 | 16 | `0xAA65E0  movups xmm12,[r8+0x10]` | A operand row 1 read (16 B) | [V] |
| Math::mat4Multiply A row2 (r8)+0x20 @ 0xAA65F4 | 16 | `0xAA65F4  movups xmm4,[r8+0x20]` | A operand row 2 read (16 B) | [V] |
| Math::mat4Multiply A row3 (r8)+0x30 @ 0xAA6608 | 16 | `0xAA6608  movups xmm1,[r8+0x30]` | A operand row 3 read (16 B) | [V] |
| Math::mat4Multiply B row0 (rdx)+0x00 @ 0xAA660D | 16 | `0xAA660D  movups xmm2,[rdx]` | B operand row 0 read (16 B) | [V] |
| Math::mat4Multiply B row1 (rdx)+0x10 @ 0xAA6610 | 16 | `0xAA6610  movups xmm11,[rdx+0x10]` | B operand row 1 read (16 B) | [V] |
| Math::mat4Multiply B row2 (rdx)+0x20 @ 0xAA661A | 16 | `0xAA661A  movups xmm3,[rdx+0x20]` | B operand row 2 read (16 B) | [V] |
| Math::mat4Multiply B row3 (rdx)+0x30 @ 0xAA6632 | 16 | `0xAA6632  movups xmm11,[rdx+0x30]` | B operand row 3 read (16 B) | [V] |
| Math::mat4Multiply out row0 (rcx)+0x00 @ 0xAA6663 | 16 | `0xAA6663  movups [rcx],xmm0` | out row 0 written (16 B); out may alias an input | [V] |
| Math::mat4Multiply out row1 (rcx)+0x10 @ 0xAA669A | 16 | `0xAA669A  movups [rcx+0x10],xmm12` | out row 1 written (16 B) | [V] |
| Math::mat4Multiply out row2 (rcx)+0x20 @ 0xAA66C5 | 16 | `0xAA66C5  movups [rcx+0x20],xmm4` | out row 2 written (16 B) | [V] |
| Math::mat4Multiply out row3 (rcx)+0x30 @ 0xAA66F7 | 16 | `0xAA66F7  movups [rcx+0x30],xmm1` | out row 3 written (16 B) | [V] |

Thread: callers are group visitors and extractors on game/task threads (BGFX_MAP 6ih: Effect tag 6 AimAssistHighlight calls it at 0x666B1EE; Editor 5-7 cases call it). Owns: nothing — `out[16]` supplied by the caller. Lifetime: the call only. Sharing: none — pure leaf, `out` may alias an input, no calls, no globals.

### Piece 2 — UniformBlock::setVec4Array 0x5679DB0 (dossier docs/functions/5679db0.md)

| offset | size | `0xRVA  instr` proof | meaning | tag |
| UniformBlock::setVec4Array slot table (block+0x30) @ 0x5679DC3 | 8 | `0x5679DC3  mov r15,[rcx+0x30]` | slot table pointer read | [V] |
| UniformBlock::setVec4Array slot offset (slot+0x08) @ 0x5679DCB | 2 | `0x5679DCB  movzx ecx,word ptr [r15+r14+8]` | slot offset (u16) read | [V] |
| UniformBlock::setVec4Array block size (block+0x20) @ 0x5679DD1 | 8 | `0x5679DD1  cmp [rsi+0x20],rcx` | block data size read (bounds check vs slot offset) | [V] |
| UniformBlock::setVec4Array block data ptr (block+0x28) @ 0x5679DED | 8 | `0x5679DED  add rcx,[rsi+0x28]` | block data pointer read + offset | [V] |
| UniformBlock::setVec4Array slot dirty (slot+0x0C) @ 0x5679DFE | 1 | `0x5679DFE  mov byte ptr [r15+r14+0xC],1` | slot dirty byte written | [V] |
| UniformBlock::setVec4Array running hash read (block+0x70) @ 0x5679E0D | 8 | `0x5679E0D  mov rdx,[rsi+0x70]` | running hash read | [V] |
| UniformBlock::setVec4Array running hash write (block+0x70) @ 0x5679E53 | 8 | `0x5679E53  mov [rsi+0x70],r8` | running hash written (folded slot FNV-1a) | [V] |
| UniformBlock::setVec4Array running hash write (block+0x70) @ 0x5679EFE | 8 | `0x5679EFE  mov [rsi+0x70],r8` | running hash written (folded XXH64 of value) | [V] |

Thread: game thread (extractors fill the material's uniform block before the description is inserted; callers include all six group visitors per dossier). Owns: block data area + slot dirty byte + running hash of one MaterialInstance holder; block lives at holder+0x08 {MaterialInstance* +0x00, UniformBlock +0x08}; lifetime until the description/material is released. Sharing: one writer at a time per block; no lock in the original (single-threaded fill before insert).

### Piece 3 — ResourceCache::get 0x675E440 (dossier docs/functions/675e440.md)

| offset | size | `0xRVA  instr` proof | meaning | tag |
| ResourceCache::get mutex addr (this+0x98) @ 0x675E489 | 8 | `0x675E489  lea r15,[r14+0x98]` | recursive mutex address taken | [V] |
| ResourceCache::get mutex lock (this+0x98) @ 0x675E493 | - | `0x675E493  call 0xEEC59F0` | _Mtx_lock on cache+0x98 | [V] |
| ResourceCache::get mutex guard (this+0xE4) @ 0x675E4AE | 4 | `0x675E4AE  cmp dword ptr [r14+0xE4],0x7FFFFFFF` | mutex owner-count / invalid-state guard read | [V] |
| ResourceCache::get stale bucket head (this+0x48) @ 0x675E555 | 8 | `0x675E555  mov rcx,[r14+0x48]` | stale-key set bucket head read | [V] |
| ResourceCache::get retired end (this+0x88) @ 0x675E5E6 | 8 | `0x675E5E6  add qword ptr [r14+0x88],0x10` | retired vector end advanced (old holder parked) | [V] |
| ResourceCache::get shared_ptr ptr (entry+0x20) @ 0x675E5DB | 8 | `0x675E5DB  mov [rdx],rax` | Entry.shared_ptr pointer written | [V] |
| ResourceCache::get shared_ptr ctrl (entry+0x28) @ 0x675E5E2 | 8 | `0x675E5E2  mov [rdx+8],rax` | Entry.shared_ptr control block written | [V] |
| ResourceCache::get used byte (entry+0x30) @ 0x675E649 | 1 | `0x675E649  mov byte ptr [r15+0x30],1` | Entry.used byte written | [V] |

Thread: game and task threads (called by every group visitor case that needs a material plus the terrain builder per dossier callers). Owns: entry map (this+0x00..+0x38), stale set (this+0x40..+0x78), retired vector (this+0x80..+0x98); the caller's out shared_ptr. Lifetime: cache lifetime; holders are shared_ptr (use count at control+8), retired entries stay alive for frames in flight. Sharing: recursive mutex at cache+0x98 (_Mtx_lock 0xEEC59F0 / unlock 0xEEC5A10); the rewrite takes the same lock through the game's own function, no new locking.

### Piece 4 — Frame::sort 0xBC61E20 (dossier docs/functions/bc61e20.md)

| offset | size | `0xRVA  instr` proof | meaning | tag |
| Frame::sort viewRemap entry (Frame+0x0000) @ 0xBC61E40 | 2 | `0xBC61E40  movzx ecx,word ptr [rsi+rax*2]` | m_viewRemap entry read (view id -> position) | [V] |
| Frame::sort sort key read (Frame+0x14700) @ 0xBC61EB0 | 8 | `0xBC61EB0  mov r9,[rsi+rcx*8+0x14700]` | sort key read | [V] |
| Frame::sort sort key write (Frame+0x14700) @ 0xBC61EDB | 8 | `0xBC61EDB  mov [rsi+rcx*8+0x14700],r9` | remapped sort key written | [V] |
| Frame::sort blit key read (Frame+0x93477B) @ 0xBC61F90 | 1 | `0xBC61F90  movzx r8d,byte ptr [rsi+rcx*4+0x93477B]` | blit key top byte read | [V] |
| Frame::sort blit key write (Frame+0x93477B) @ 0xBC61F9F | 1 | `0xBC61F9F  mov [rsi+rcx*4+0x93477B],r8b` | remapped blit key byte written | [V] |
| Frame::sort item count (Frame+0xDC57E8) @ 0xBC61E7C | 4 | `0xBC61E7C  mov edx,[rsi+0xDC57E8]` | m_numRenderItems count read | [V] |
| Frame::sort blit count (Frame+0xDC57EC) @ 0xBC61F6C | 2 | `0xBC61F6C  movzx eax,word ptr [rsi+0xDC57EC]` | m_numBlitItems count read | [V] |
| Frame::sort s_ctx global (s_ctx+0x0000) @ 0xBC61F40 | 8 | `0xBC61F40  mov rdx,[0x12AE1748]` | s_ctx global pointer read | [V] |
| Frame::sort tempKeys ptr (s_ctx+0x1CFD0D0) @ 0xBC61F55 | 8 | `0xBC61F55  add rdx,0x1CFD0D0` | radix-scratch tempKeys pointer computed | [V] |
| Frame::sort tempValues ptr (s_ctx+0x1D7D0C8) @ 0xBC61F47 | 8 | `0xBC61F47  lea r9,[rdx+0x1D7D0C8]` | tempValues pointer computed | [V] |

Thread: render thread only — called from D3D12 submit slot 50 (0xE82E230, reached by the render thread per BGFX_MAP 6ex: renderFrame calls `[rax+0x190]` = slot 50 submit at 0xBC633A8) and the other two submits 0xE7F5380/0xE85E5C0; the Frame consumed is the render thread's frame between ctx+0x80 (ready) and ctx+0x100 (consumed). Owns: Frame sort keys/values/blit keys; scratch of bx::radixSort in the bgfx context (original) or file statics (rewrite). Lifetime: one frame — the Frame is double buffered 0xE749C0 apart and the game thread fills the other one. Sharing: none — render thread owns the consume frame.

### Piece 5 — Encoder::submit 0xBC60740 (dossier docs/functions/bc60740.md)

| offset | size | `0xRVA  instr` proof | meaning | tag |
| Encoder::submit m_discard (Encoder+0x6AD) @ 0xBC60773 | 1 | `0xBC60773  cmp byte ptr [rcx+0x6AD],1` | m_discard read -> discard() tail jump | [V] |
| Encoder::submit item CAS (Frame+0xDC57E8) @ 0xBC607EA | 4 | `0xBC607EA  lock cmpxchg [rcx+0xDC57E8],r14d` | item-count CAS (0xFFFE cap) — shared by all encoders | [V] |
| Encoder::submit view seq (s_ctx+0x1EAAC60) @ 0xBC608FC | 4 | `0xBC608FC  lock xadd [r11+rdx*4+0x1EAAC60],ecx` | view sequence counter (lock xadd) | [V] |
| Encoder::submit sort key write (Frame+0x14700) @ 0xBC60991 | 8 | `0xBC60991  mov [rcx+r14*8+0x14700],rax` | sort key written at slot idx | [V] |
| Encoder::submit sort value write (Frame+0x94700) @ 0xBC6099C | 2 | `0xBC6099C  mov [rax+r14*2+0x94700],di` | sort value (u16 idx) written at slot idx | [V] |
| Encoder::submit header copy (Frame+0xB4700) @ 0xBC60B13 | 16 | `0xBC60B13  movaps [rax+rcx+0xB4700],xmm0` | RenderDraw header row 0 written (16 B); the full 0x80-byte header is four movaps at 0xBC60AFB/0xBC60B03/0xBC60B0B/0xBC60B13 to Frame+0xB4700+(idx<<7) | [V] |
| Encoder::submit ensure grow (Frame+0x8B4700) @ 0xBC60B2E | - | `0xBC60B2E  call 0xBC7A7C0` | GuardedPagedArray::ensure grows Frame+0x8B4700 record storage | [V] |
| Encoder::submit side table (Encoder+0x680) @ 0xBC60B4F | 8 | `0xBC60B4F  mov r8,[rsi+0x680]` | side-table pointer read | [V] |
| Encoder::submit m_bindDirty (Encoder+0x688) @ 0xBC60CF6 | 1 | `0xBC60CF6  mov byte ptr [rsi+0x688],1` | m_bindDirty written | [V] |

Thread: task threads, one encoder per thread (called from pass task bodies / encoder submit forms per dossier callers). Owns: the encoder's own state (m_draw, m_bind, key) plus one slot of the Frame (key, id, 0x80 header, 0x540 bind record). Lifetime: encoder = thread; Frame slot = the frame. Sharing: Frame item counter CAS at Frame+0xDC57E8 (shared by all encoders), view sequence counter s_ctx+0x1EAAC60 (lock xadd), bind-array growth under its own mutex in 0xBC7A7C0.

### Piece 6 — Encoder::discard 0xBC60D10 (dossier docs/functions/bc60d10.md; entry sig Encoder::reset)

| offset | size | `0xRVA  instr` proof | meaning | tag |
| Encoder::discard m_discard (Encoder+0x6AD) @ 0xBC60D21 | 1 | `0xBC60D21  mov byte ptr [rcx+0x6AD],0` | m_discard = 0 | [V] |
| Encoder::discard state flags (Encoder+0x60) @ 0xBC60D32 | 8 | `0xBC60D32  mov [rcx+0x60],rax` | m_draw state flags written | [V] |
| Encoder::discard stencil (Encoder+0x68) @ 0xBC60D36 | 8 | `0xBC60D36  mov qword ptr [rcx+0x68],0` | m_draw stencil zeroed | [V] |
| Encoder::discard block 1 (Encoder+0x70) @ 0xBC60D41 | 16 | `0xBC60D41  movaps [rcx+0x70],xmm0` | m_draw 16-byte block zeroed | [V] |
| Encoder::discard block 2 (Encoder+0x80) @ 0xBC60D4C | 16 | `0xBC60D4C  movaps [rcx+0x80],xmm0` | m_draw defaults copied in (kDrawDefaults16 rodata 0xF08EF70) | [V] |
| Encoder::discard uniform begin (Encoder+0x90) @ 0xBC60D5D | 8 | `0xBC60D5D  mov [rcx+0x90],rax` | m_draw uniform range begin written | [V] |
| Encoder::discard uniform end (Encoder+0x98) @ 0xBC60D6E | 8 | `0xBC60D6E  mov [rcx+0x98],rax` | m_draw uniform range end written | [V] |
| Encoder::discard side table (Encoder+0x680) @ 0xBC60E65 | 8 | `0xBC60E65  mov rdi,[rsi+0x680]` | side table read (0x41 x 16-byte entries + u32 count at +0x410) | [V] |
| Encoder::discard side count (side+0x410) @ 0xBC60EEC | 4 | `0xBC60EEC  mov dword ptr [rdi+0x410],0` | side-table count = 0 | [V] |
| Encoder::discard m_bindDirty (Encoder+0x688) @ 0xBC60EF6 | 1 | `0xBC60EF6  mov byte ptr [rsi+0x688],1` | m_bindDirty = 1 | [V] |

Thread: task threads — called from submit's drop path (0xBC607A8/0xBC60807 tail jumps) and directly by pass task bodies (0x568CD90, 0x569A3A0, 0x56AD350, 0x56AD810, 0x56D16A0 per dossier callers) plus frame teardown. Owns: the encoder's own state only (all fields are `this`-relative). Lifetime: the encoder's lifetime (thread-scoped). Sharing: none — the side table is freed through the game allocator (interface global read) but only the owning thread's encoder touches it; no lock.

### Piece 7 — Render thread frame handshake (BGFX_MAP 6as/6ex; sources dossiers bc60740.md/bc61e20.md)

| offset | size | `0xRVA  instr` proof | meaning | tag |
| Render thread wait sem (ctx+0x80) @ 0xBC63226 | 8 | `0xBC63226  lea rcx,[rsi+0x80]` | "frame data ready" semaphore address (ctx+0x80) | [V] |
| Render thread wait sem call (ctx+0x80) @ 0xBC6322F | - | `0xBC6322F  call 0xEBDBC60` | wait on semaphore ctx+0x80 | [V] |
| Render thread post sem (ctx+0x100) @ 0xBC633DA | - | `0xBC633DA  call 0xEBDBC50` | post "frame consumed" semaphore ctx+0x100 | [V] |
| Render thread reset flag (ctx+0x1EBF19C) @ 0xBC631AD | 4 | `0xBC631AD  mov r14d,[rsi+0x1EBF19C]` | reset-flag bit 0x800000 read | [V] |
| Render thread slot 50 submit ([rax+0x190]) @ 0xBC633A8 | 8 | `0xBC633A8  mov rax,[rax+0x190]` | renderer vtable slot 50 = submit, reached from renderFrame | [V] |

This row group is the threading contract the table rests on (BGFX_MAP 6as/6ex): API thread fills Frame A via frame() 0xBC66DE0 + 0xBC65800 then signals ctx+0x80; render thread 0xBC65720 loops renderFrame 0xBC63150 until Exiting, waits ctx+0x80, runs cmdPre 0xBC68840, submit slot 50, cmdPost 0xBC68E40, posts ctx+0x100. The rewritten submit runs on task threads per Q1e source, while sort runs on the render thread inside submit — the table keeps both rows because a rewrite of submit must not touch render-thread-only state (Frame slot it owns is CAS-published).

## (3) CLOSES?

CLOSES? YES — every part of Q1e R5's wording is met on disk now: an ownership/threading table row per rewritten function (mat4Multiply, setVec4Array, ResourceCache::get, Frame::sort, Encoder::submit, Encoder::discard), each with thread/owned-memory/lifetime/sharing, and per-offset verbatim `0xRVA  instr` proof rows all tagged [V] (or [I] where meaning is structural), verified by `tools/delegate.py check` / verify_oc exiting 0. The matching table exists in `src/client/features/render/rewrite/RewriteOwnership.h`. The item cannot be ticked [x] in the checklist until the lead's batch build compiles the rewrite folder (no /Zs allowed, build not run by this unit), but that is a build-step, not a wording gap: the item's own wording ("ownership/threading table per rewritten function in its dossier") is fully satisfied by what exists on disk now.

## NEXT
DONE
