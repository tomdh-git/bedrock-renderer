## NEXT
DONE

# U-EQ2a — Q2a 0x5679db0 uniform/component writer

GOAL: Close checklist item "Q2a 0x5679db0 uniform/component writer, shadow-verified over many calls, timed".

## (1) What changed (paths)
- Created: docs/progress/oc_U-EQ2a.md (this note; the [V] proof table and CLOSES? verdict for the unit).
- Engineering deliverable already on disk (cited, not modified by this unit):
  - src/client/features/render/rewrite/RewriteUniform.cpp — shadow/verify + timed rewrite of UniformBlock::setVec4Array at 0x5679DB0.
  - src/client/features/render/rewrite/RewriteVerify.h — compare() used by the shadow/verify path (compareValue + Logger::fatal on first divergence).
  - docs/functions/5679db0.md — dossier (analyst reversal of the same function).

## (2) [V] proof table — field accesses of UniformBlock::setVec4Array (0x5679db0)

Every offset/size/instr below is read verbatim from the disassembly of `0x5679db0` (size 0x165, 103 instructions). `rcx`=UniformBlock* block, `rdx`=const uint16_t* slot, `r8`=const Span<vec4>* value ({u64 count at +0, ptr data at +8}), `r9` unused.

| offset | size | read/store address | `0xRVA  instr` proof | meaning |
| rdx+0x0 | 2 | slot pointer arg | `0x5679dbf  movzx r14d,word ptr [rdx]` | slot index u16 read [V] |
| rcx+0x30 | 8 | block | `0x5679dc3  mov r15,[rcx+0x30]` | slot-table pointer read [V] |
| entry+0x8 | 2 | [r15+r14]+8 | `0x5679dcb  movzx ecx,word ptr [r15+r14+8]` | slot's uniform offset u16 read [V] |
| block+0x20 | 8 | rsi+0x20 | `0x5679dd1  cmp [rsi+0x20],rcx` | block data size read, bounds check vs offset [V] |
| rdi+0x0 | 8 | value span (r8 saved to rdi) | `0x5679dde  mov r8,[r8]` | vec4 count read (span+0) [V] |
| block+0x28 | 8 | rsi+0x28 | `0x5679ded  add rcx,[rsi+0x28]` | block data pointer read [V] |
| rdi+0x8 | 8 | value span | `0x5679df1  mov rdx,[rdi+8]` | vec4 data pointer read (span+8, memcpy src) [V] |
| entry+0xC | 1 | [r15+r14]+0xC | `0x5679dfe  mov byte ptr [r15+r14+0xC],1` | dirty flag write = 1 [V] |
| block+0x70 | 8 | rsi+0x70 | `0x5679e0d  mov rdx,[rsi+0x70]`<br>`0x5679e53  mov [rsi+0x70],r8`<br>`0x5679e99  mov rax,[rsi+0x70]`<br>`0x5679efe  mov [rsi+0x70],r8` | running hash read then written (two combine steps) [V] |

Direct calls (also [V] from the same listing):
- `0x5679df9  call 0xEEC6EC0` — memcpy(dest=rcx, src=rdx=data, n=r8=count<<4) [V]
- `0x5679e65  call 0x19932C0` — XXH64(data, bytes, seed=0) [V]
- Failure path (out of range or empty count): `0x5679f0f  call 0x78ED0` then `0x5679f14  int3` — the game ends the process [V].

Hash (running, block+0x70), both combine steps [V] from constants and instruction flow:
- combine(h, fnv1a64({slot lo, slot hi})): `0x5679e11  mov r15,0xCBF29CE484222325`, `0x5679e1e  mov rbx,0x100000001B3`, `0x5679e44  mov r14d,0x9E3779B9`; combine = h ^ (x + 0x9E3779B9 + (h<<6) + (h>>2)).
- combine(h, fnv1a64(xxh64 digest bytes little-endian)): `0x5679e65  call 0x19932C0`, then byte-split FNV-1a over the 8 digest bytes into the hash, stored at `0x5679efe  mov [rsi+0x70],r8`.

Struct layout touched [V]: UniformBlock +0x20 u64 data size, +0x28 u64 data pointer, +0x30 slot table (16-byte entries: +0x8 u16 offset, +0xC u8 dirty), +0x70 u64 running hash. Matches RewriteUniform.cpp constants kBlockSlots=0x30, kSlotOffset=0x8, kSlotDirty=0xC, kBlockSize=0x20, kBlockData=0x28, kBlockHash=0x70.

Shadow/verify + timed (code on disk, not yet [V] live):
- RewriteUniform::rwUniformCompare runs the original on the real block, computes expected data/dirty/hash from pre-call copies, compares all three after the call (RewriteVerify::compare), and counts e.evaluated per call — i.e. shadow-verified per call. Timed: RewriteTimed wraps e.ticksOriginal and e.ticksRewrite around the original and the rewrite respectively (RewriteUniform.cpp lines 58-64).
- "Over many calls" / the actual measured ns and divergence count require a live in-game run (build + BS_REWRITE=UniformBlock::setVec4Array=verify), which is blocked by the no-build/no-game rules.

## CLOSES?
NO — the writer's field accesses are fully [V]-proven above and the shadow/verify + timed code exists on disk, but the item's own wording ("shadow-verified over many calls, timed") is only met by a live in-game verify run (build the DLL, then BS_REWRITE=UniformBlock::setVec4Array=verify in a world). That run is blocked by the no-build/no-launch rules. Single blocking fact: live verify run not performed / not permitted under current constraints.
