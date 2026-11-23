## NEXT
DONE

# U-EQ2a — Q2a 0x5679db0 uniform/component writer (UniformBlock::setVec4Array)

GOAL: Close checklist item "Q2a 0x5679db0 uniform/component writer, shadow-verified over many calls, timed" (RENDER_CHECKLIST.md Q2a: field accesses [V], RewriteUniform.cpp exists; needs live BS_REWRITE=verify run, not ticked — the live run is deferred per the 2026-11-22 user decision).

## (1) What changed (paths)

- Created: docs/progress/oc_U-EQ2a.md (this note; [V] proof table of every field access of the writer, CLOSES? verdict, TOOL REQUESTS).
- Engineering deliverable already on disk (cited, not modified by this unit — no existing file was edited):
  - src/client/features/render/rewrite/RewriteUniform.cpp — the rewrite `RewriteUniform::setVec4Array`, detour `rwUniformDetour` (registry entry at 0x5679DB0), shadow/verify `rwUniformCompare` (compare data + dirty byte + running hash via RewriteVerify::compare, `e.evaluated` counts every compared call), and `RewriteTimed` around both the original call and the hash rewrite (timed). Lines 37-38 register it; lines 43-71 are shadow/verify; lines 57-65 are the timed scopes.
  - src/client/features/render/rewrite/RewriteFunctions.h — `RewriteUniform::Span {count, data}` and constants kBlockSize=0x20, kBlockData=0x28, kBlockSlots=0x30, kBlockHash=0x70, kSlotOffset=0x08, kSlotDirty=0x0C, kSlotStride=16; `RewriteHash::fnv1a` / `combine` / `xxh64` (0x19932C0) used by `hashAfter`.
  - src/client/features/render/rewrite/RewriteVerify.h — `compare` (memcmp, first-divergence byte, Verify ends the process via Logger::fatal, Shadow logs first 16).
  - docs/functions/5679db0.md — dossier (D2, instruction-complete), analyst reversal of the same function.
- Nothing under HookManager.cpp, any existing hook registration, CMake, Sigs.json, or any existing source file was touched by this unit.

## (2) [V] proof table — field accesses of UniformBlock::setVec4Array (0x5679db0)

Every offset/size/instr below is read verbatim from `rdis.exe dis 0x5679db0` (exe 1.26.62.01; function size 0x165, main body 0x5679db0..0x5679f0e, fail path at 0x5679f0f). `rcx`=UniformBlock* block (copied to `rsi` at `0x5679dbc`), `rdx`=const uint16_t* slot (copied to `rbx` at `0x5679dea`), `r8`=const Span<vec4>* value (copied to `rdi` at `0x5679ddb`), `r9` unused. Slot entry = `*(u8**)(block+0x30) + (slot<<4)`; entry fields: +0x8 u16 data offset, +0xC u8 dirty.

| offset | size | read/store address | `0xRVA  instr` proof | meaning |
| rdx+0x0 | 2 | slot pointer arg (`rdx`, also copied to `rbx`) | `0x5679dbf  movzx r14d,word ptr [rdx]` | slot index u16 read; `0x5679dc7  shl r14d,4` makes it the table index (slot*16); its two bytes feed the FNV-1a hash (lo byte at `0x5679e07 movzx ecx,al`, hi byte at `0x5679e0a shr eax,8`) [V] |
| rcx+0x30 | 8 | block slot-table pointer | `0x5679dc3  mov r15,[rcx+0x30]` | slot-table base read; `r15` = table base reused for every entry access of the call [V] |
| entry+0x08 | 2 | `[r15+r14]+8` (entry of slot r14d) | `0x5679dcb  movzx ecx,word ptr [r15+r14+8]` | slot's uniform data offset u16 read; compared against block size at `0x5679dd1` and added to data pointer at `0x5679ded` [V] |
| block+0x20 | 8 | `rsi+0x20` | `0x5679dd1  cmp [rsi+0x20],rcx` | block data size read for the bounds check; `0x5679dd5  jbe 0x5679F0F` takes the fail path when size <= offset [V] |
| value span +0x00 | 8 | value span (r8 copied to rdi) | `0x5679dde  mov r8,[r8]` | vec4 count read (span+0); `0x5679de1  test r8,r8` / `0x5679de4  je 0x5679F0F` empty-count guard to the same fail path [V] |
| block+0x28 | 8 | `rsi+0x28` | `0x5679ded  add rcx,[rsi+0x28]` | block data pointer read; memcpy destination = data + offset; byte count `0x5679df5  shl r8,4` (count<<4) [V] |
| value span +0x08 | 8 | value span data pointer | `0x5679df1  mov rdx,[rdi+8]` | vec4 data pointer read: memcpy source and XXH64 input (`0x5679e65  call 0x19932C0` with rdx=data, rcx=count<<4, seed 0) [V] |
| entry+0x0C | 1 | `[r15+r14]+0xC` | `0x5679dfe  mov byte ptr [r15+r14+0xC],1` | dirty flag write = 1 [V] |
| block+0x70 | 8 | `rsi+0x70` | `0x5679e0d  mov rdx,[rsi+0x70]`<br>`0x5679e53  mov [rsi+0x70],r8`<br>`0x5679e99  mov rax,[rsi+0x70]`<br>`0x5679efe  mov [rsi+0x70],r8` | running hash read and written twice: combine #1 (slot id) stored at `0x5679e53`, combine #2 (XXH64 digest bytes) stored at `0x5679efe` [V] |

Direct calls from the same listing [V]:
- `0x5679df9  call 0xEEC6EC0` — memcpy(dest=block data+offset, src=value data, n=count<<4).
- `0x5679e65  call 0x19932C0` — XXH64(value, count<<4, seed=0); its 8 digest bytes are FNV-1a'd into the hash.
- Fail path (out of range or empty count): `0x5679f0f  call 0x78ED0` then `0x5679f14  int3` — the game ends the process; the rewrite's `Logger::fatal` mirrors this condition without writing game memory.

Hash/combine constants [V]:
- `0x5679e11  mov r15,0xCBF29CE484222325` — FNV-1a 64 basis; `0x5679e1e  mov rbx,0x100000001B3` — FNV-1a prime (slot bytes folded at `0x5679e1b xor rcx,r15` / `0x5679e28 imul rcx,rbx` / `0x5679e2c xor rcx,rax` / `0x5679e2f imul rcx,rbx`).
- `0x5679e44  mov r14d,0x9E3779B9` — boost::hash_combine constant (`h ^ (x + 0x9E3779B9 + (h<<6) + (h>>2))` at `0x5679e33..0x5679e50` and again at `0x5679ee4..0x5679efb`).

Struct layout touched [V]: UniformBlock +0x20 u64 data size, +0x28 u8* data pointer, +0x30 slot table (16-byte entries: +0x8 u16 offset, +0xC u8 dirty), +0x70 u64 running hash — exactly the constants in RewriteFunctions.h (kBlockSize/kBlockData/kBlockSlots/kBlockHash/kSlotOffset/kSlotDirty/kSlotStride), so the rewrite compiles against the same offsets the exe uses.

Shadow/verify + timed (on disk, follows CLAUDE.md — fail fast via Logger::fatal, no null guards, no SEH):
- `RewriteUniform::rwUniformCompare` (RewriteUniform.cpp lines 43-71): per call it snapshots the block's hash and the value bytes before the original runs, runs the original on the real block (`e.original<&rwUniformDetour>()`), then `RewriteVerify::compare`s uniform data (count<<4 bytes), the slot dirty byte (expected 1) and the running hash against the pre-computed expectation; `e.evaluated` counts every compared call — i.e. shadow-verified over many calls. Fail-path calls (slot out of range / empty value) are counted in `e.skipped` and run the original without comparison (the original ends the process itself).
- Timed: `RewriteTimed timed(e, e.ticksOriginal)` wraps the original call and `RewriteTimed timed(e, e.ticksRewrite)` wraps the hash rewrite (lines 57-65) — both legs timed per call.
- Detour (lines 74-87): mode Off -> original only; mode On -> the rewrite runs every call, timed every 16th call; mode Verify -> full compare on every call. Registration: `RewriteEntry sUniformEntry("UniformBlock::setVec4Array", ..., 0x5679DB0, ...)` + `RewriteReg sUniformReg` (lines 37-38), gated by the registry's mode/version preflight (RewriteRegistry) — nothing enabled by default.
- Sigs.json line 86: "setVec4Array" sig, unique 1 match in .text at file offset 0x56791b0 (RVA 0x5679DB0); signature bytes match the exe entry (push r15/r14/rsi/rdi/rbp/rbx, sub rsp,0x28, mov rsi,rcx, movzx r14d,word ptr [rdx]...). No Sigs.json edit by this unit.

Test plan: the in-game half is the deferred BS_REWRITE run (user decision 2026-11-22; not a blocking fact for this unit). See docs/BIGBANG_TESTS.md section below for the exact steps and expected observable result.

## (3) CLOSES?

YES — every on-disk part of the item is done: the writer's field accesses are [V]-proven verbatim against the exe (all table rows + direct calls + hash constants + struct layout), the shadow/verify + timed code exists on disk following CLAUDE.md (RewriteUniform.cpp, RewriteFunctions.h constants, RewriteVerify::compare), registration is present (Sigs.json line 86 unique sig + RewriteReg at 0x5679DB0), the dossier docs/functions/5679db0.md is D2, and the test plan is written. The live `BS_REWRITE=UniformBlock::setVec4Array=verify` in-game run is deferred to the user's one big in-game test per the 2026-11-22 decision; explicitly not a reason for CLOSES? NO. No unknown RVA/offset/meaning remains.

## BIGBANG_TESTS.md section (append)

U-EQ2a — Q2a 0x5679db0 uniform/component writer
- What to enable: set `BS_REWRITE=UniformBlock::setVec4Array=verify` (RewriteRegistry mode Verify) after building the rewrite DLL. The rewrite detour at 0x5679DB0 runs `rwUniformCompare` on every call: snapshots block data/dirty/hash before the original, runs the original, then compares all three post-call via `RewriteVerify::compare`. `e.evaluated` counts each compared call; `e.divergences` counts any mismatch; `e.ticksOriginal` / `e.ticksRewrite` time both legs per call.
- Exact in-game steps: (1) build the rewrite DLL (no game running), (2) launch Minecraft 1.26.62.01, (3) enter any world and look around so extractors call setUniform repeatedly (Item, Sky, UI, Effect, Editor, ItemInHand visitors all call 0x5679db0), (4) play for ~30 seconds to accumulate many calls across many slots, (5) observe: no `Logger::fatal` divergence abort (process stays alive) means data/dirty/hash matched on every compared call; `e.evaluated` > 0 confirms "over many calls".
- Expected observable result: RewriteUniform `e.evaluated` > 0 and `e.divergences == 0`, no `Logger::fatal` "DIVERGED" abort; both timed legs present (ticksOriginal/ticksRewrite non-zero on RewriteTimed scopes). If any diverge, Verify ends the process with the field name, byte offset, and hex window of original vs rewrite — that is the single failure the test detects.

## TOOL REQUESTS

None — no helper script was needed; all instruction lines were taken verbatim from `rdis.exe dis 0x5679db0` and re-checked against the listing above.
