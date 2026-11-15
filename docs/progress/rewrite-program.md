# rewrite-program progress (agent "rewrite-program")

## NEXT
All coordinator-requested units are written (uncompiled). Remaining: (1) after the lead's batch build, fix compile errors in src/client/features/render/rewrite/; (2) in-game runs with the DLL (every OPEN below has its procedure); (3) Q3d wiring (needs the caller of 0x67B6300) and Q1d GPU timestamps.
Resume facts: all code in `src/client/features/render/rewrite/`; modes via env `BS_REWRITE`, probe via `BS_PROBE_FRAMES=N`; apply the registration notes below.
Half done: none.

## Files created so far (the lead must build once)
src/client/features/render/rewrite/: RewriteRegistry.h, RewriteRegistry.cpp, RewriteVerify.h, RewriteFunctions.h, RewriteOwnership.h, RewriteProbe.h, RewriteProbe.cpp, RewriteDescriptions.h, RewriteDescriptions.cpp, RewriteDiscard.cpp, RewriteLightCache.cpp, RewriteMath.cpp, RewriteUniform.cpp, RewriteResourceCache.cpp, RewriteFrameSort.cpp, RewriteEncoder.cpp
(no existing source file edited). Unity build: file-local names are prefixed rw/sRw/kRw; no namespaces.
Probe registration (lead, before hooks are enabled): `FrameBuilderHook::addEndFrameListener(&RewriteProbe::onEndFrame);` and in FrameFilterHook ffSlot / ffSlotSky / ffSlot340 call `RewriteProbe::noteInsert(RewriteGroup::Item / Sky / Ui, description)` (the probe installs its own detours on the Editor 0x358, Effect 0x360, Light 0x380 insert slots on the first end-frame).
Optional registration (lead): `TaskDispatchHook::addListener(&RewriteProbe::notePassList);` before hooks are enabled, to give the probe the pass list.

## Registration notes (not applied; I may not edit other files)
1. After `Detour::enableAll();` in `HookManager::init` (src/client/features/hooks/HookManager.cpp) add `RewriteRegistry::init();` (include "client/features/render/rewrite/RewriteRegistry.h"). Without it nothing runs.
2. Encoder::submit (0xBC60740) is ALREADY hooked: `HOOK(RenderMark, submit, ...)` in RenderMarkHook.cpp uses the same Sigs.json function; MinHook refuses a second detour on one address. So the entry "Encoder::submit" is `hosted`: in RenderMarkHook.cpp replace `ORIG(RenderMark_submit)(encoder, view, program, query, depth, flags);` by `RewriteEncoder::dispatch(ORIG(RenderMark_submit), encoder, view, program, query, depth, flags);` (include RewriteFunctions.h). With mode off dispatch just calls the original.
3. Sigs.json entries to add (names are Class::method, I may not edit Sigs.json). Patterns from tools/sigs/mksig.py on 62.01:
   - `Math::mat4Multiply` (rva 0xAA6580): `48 81 EC B8 00 00 00 44 0F 29 BC 24 ?? ?? ?? ?? 44 0F 29 B4 24 ?? ?? ?? ?? 44 0F 29 AC 24 ?? ?? ?? ?? 44 0F 29 64 24 70 44 0F 29 5C 24 60 44 0F 29 54 24 50 44 0F 29 4C 24 40 44 0F 29 44 24 30 0F 29 7C 24 20 0F 29 74 24 10 48 89 C8 41 0F 10` (unique, from xref.py sig)
   - `UniformBlock::setVec4Array` (0x5679DB0): `41 57 41 56 56 57 55 53 48 83 EC 28 48 89 CE 44 0F B7 32 4C 8B 79 30 41 C1 E6 04 43 0F B7 4C 37 08 48 39 4E 20 0F 86 ?? ?? ?? ?? 4C 89 C7 4D 8B 00 4D 85 C0 0F 84 ?? ?? ?? ?? 48 89 D3 48 03 4E 28 48 8B 57 08 49 C1 E0 04`
   - `Encoder::ensureBind` (0xBC7A7C0): `55 41 57 41 56 56 57 53 48 81 EC C8 00 00 00 48 8D AC 24 ?? ?? ?? ?? 48 C7 45 40 FE FF FF FF 3B`
   - `ResourceCache::get` (0x675E440): NO unique pattern: an identical-bodied twin sits at 0x567C8B0 (a 400-byte wildcarded prefix matches both). Needs a `kind: call` sig anchored on a unique caller (e.g. the call in 0x66EA3D0) or a mask on a byte after the differing rip operands. The registry's `knownRva` check (target must equal imageBase+0xBC...) catches a wrong twin.
   - existing and reused: `Encoder::frameSort` (Frame::sort 0xBC61E20), `Encoder::reset` (0xBC60D10), `FrameGraph::taskDispatch`.
   - Entry names used by the code: "Math::mat4Multiply", "UniformBlock::setVec4Array", "Encoder::frameSort" (entry name "Frame::sort"), "Encoder::submit", "Encoder::reset", "Encoder::ensureBind".

## Corrections found (CONTRADICTS)
- CONTRADICTS docs/functions/675e440.md: callee 0xEEC5A00 is `_Throw_C_error` (called with 5 and 6 on the lock error paths), the unlock at 0x675E887 is 0xEEC5A10, lock is 0xEEC59F0 [V disassembly].
- CONTRADICTS checklist Q2c wording: Frame::sort is 0xBC61E20 (radix 0xBC62040/0xBC62BC0); 0xC280010/0xC280CA0 are the frame-graph generator's insertion/stable sort over 0x80-byte task records, a different sort [V per c280010.md].
- bc60740.md "[?] 16 default bytes": rodata 0xF08EF70 = `00000000 FFFFFFFF 00000000 FFFFFFFF` [V, read from the exe]. The loop at 0xBC60815 is the function epilogue, not a loop [V].
- 0x19932C0 is standard XXH64 seed 0 (constants P1..P5, the 0xDEF35B010F796CA9 immediate = P1*P2 folded) [V constants, I full equivalence]; my port reproduces the published vectors (empty EF46DB3751D8E999, "a" D24EC4F1A98C6E5B, "abc" 44BC2CF5AD770999) in a Python mirror [V].

## Entries

### Q1a - DONE-pending-build (code written, not compiled)
RewriteRegistry.h/.cpp: entry {name, sig, knownRva, detour, hosted}, modes off/shadow/on/verify (atomic), install = version gate (GameVersion Ok) + SigManager::get + knownRva check on build 62 + late Detour via HookTable::add + enable, setMode, BS_REWRITE parser (fatal on unknown name/mode), per-entry counters, report(). [V design vs Detour.h/Hook.h; compile unchecked]. Open until built: nothing else. Version gate is per entry, runtime toggle = setMode.

### Q1b - DONE-pending-build
RewriteVerify.h: compare() = first differing byte, hex window of both, Shadow counts/logs 16, Verify `Logger::fatal` (fail fast, no fallback). Method: pure plans / private copies are computed from pre-call inputs, the original runs on the live object, results compared; the rewrite never writes game memory in Shadow/Verify. Skips (counted in entry.skipped, named in each function's comment): uniform call the game itself terminates; Encoder::submit with a side table / discarded / empty draw / a slot raced by a sibling form.

### Q2f mat4 0xAA6580 - DONE-pending-build (verify run in game OPEN)
RewriteMath.cpp. Re-read all 0x1C6 bytes: row i = ((b_i0*A0 + b_i1*A1) + b_i2*A2) + b_i3*A3 with mulps/addps in that order, all loads before the first store (aliasing safe), returns rcx [V]. Verify compares 16 floats bitwise.

### Q2a 0x5679DB0 - DONE-pending-build (OPEN: live verify run)
RewriteUniform.cpp. Re-read every instruction: slot table is a pointer at block+0x30 (not inline), entry u16 offset +8, dirty +0xC, size +0x20, data ptr +0x28, hash +0x70; failure path = 0x78ED0 + int3 [V]. Hash = combine(h, fnv1a(slot lo, hi)); combine(h, fnv1a(8 LE bytes of xxh64(value, count*16, 0))) [V]. Verify compares data range, dirty byte, hash.

### Q2c Frame::sort - DONE-pending-build (OPEN: live verify/timing)
RewriteFrameSort.cpp. bx::radixSort 0xBC62040 read: 11-bit digits, six passes (shifts 0..55 all present), sorted-input early exit with copy-back => stable ascending sort by full key [V]. Rewrite: one histogram scan for all six digits, uniform-digit passes skipped. Blit keys: view remap in top byte then std::sort (identical keys indistinguishable) [V]. Not compared: ctx scratch arrays (written by the original only) [I].

### Q2d Encoder::submit - DONE-pending-build (OPEN: live verify run)
RewriteEncoder.cpp is the full plan: key per view mode 1/2/3/default, vertex-count minimum, occlusion bit, murmur2a bind hash, header/bind copy, clear, and now the side-table tail: commitSideTable (0xBC60F10) and the 0x41-entry clear loop through the game allocator (interface global read from the rip-relative load at submit+0x535, checked; slot 1 = realloc(self, ptr, size, align, file, line), size 0 frees; no allocator = memset 0x410; count at +0x410 = 0) [V disassembly 0xBC60773..0xBC60CFD]. Verify compares destination table, source-table cleared state, sort key/value, header, bind, encoder-after. Skips (counted): discarded/empty draws and slots raced by a sibling form. Hosted entry (registration note 2). Live verify OPEN: BS_REWRITE=Encoder::submit=verify in a world with ranged binds.

### Q2e discard / bind grow - discard DONE-pending-build, bind grow OPEN-by-design
RewriteDiscard.cpp, entry "Encoder::discard" (sig Encoder::reset, 0xBC60D10): rewrite = clearDrawState + the +0xC0 block + m_discard=0 + side-table clear + bindDirty=1 (docs/functions/bc60d10.md, instruction-complete [V]). Verify runs the rewrite on a 0x6B0-byte private copy of the thread-owned encoder and compares with the live encoder after the original; calls with a side table are skipped (original frees through the game allocator). Live verify OPEN.
GuardedPagedArray::ensure 0xBC7A7C0: NOT rewritten. Its work is a platform commit + memset on growth (taken a handful of times per run, fast path is one compare); a rewrite buys nothing and needs the platform interface calls. Reversal in bc7a7c0.md is complete; DONE for the checklist wording "side-table copy" (ported in Q2d); "bind grow": OPEN-by-decision, blocker = no measurable cost [I].

### Q3d Light tag 5 deep copy - OPEN (hash half DONE-pending-build)
RewriteLightCache.cpp: RewriteLightOverride::hashSet/hashDescription, order-independent content hash of the 44 unordered_set<u16> (layout per descriptions.md R7: sentinel +0x08, count +0x10, node key +0x10; fails fast if the chain length != count). Design: hook the converter 0x67B6300 caller, hash the source description, and when equal to last frame's, reuse last frame's converted vector instead of the 0x67B7810 deep copy (allocates 0x18-byte nodes per element). Blocker: the consumer of the converted copy must not mutate it (not established) and the caller of 0x67B6300 is not located; both need the dossier read plus an in-game poll that the hash is stable across frames (acceptance: hash unchanged for 300 frames standing still, changed on an override change; verify mode compares converted output bytes).

### Q2b ResourceCache::get 0x675E440 - DONE-pending-build (OPEN: unique sig, live verify)
RewriteResourceCache.cpp: hit path = lock (game's _Mtx_lock, address read from the E8 at fn+0x53, checked) -> stale set miss -> entry hit with holder->resource->requested != 0 -> used=1, use count++, out={holder, control} -> unlock (fn+0x447). Layout from the dossier; bucket walk re-read at 0x675E4BF..0x675E595 (hash = lo ^ (fnv1a(hi bytes) + 0x9E3779B9 + (lo<<6) + (lo>>2)), bucket = hash & mask, 16-byte buckets {first,last}, walk from last via prev) [V]. Anything that is not a hit calls the original. Blocker: no unique sig (twin 0x567C8B0), see registration note 3.

### Q1c frame probe - DONE-pending-build (OPEN: field-level pretty printing, in-game run)
RewriteProbe.h/.cpp, read-only. Per frame: counter, item/blit/per-view/actor-marked counts; per sorted slot (first 64): id, view, key, program decoded from the key, variant key, PSO key, handles, RenderMark byte. Pass list via TaskDispatchHook listener. Typed descriptions (new): RewriteDescriptions.h/.cpp table of {group, tag, name, size} using sizeof() of the descriptions agent's mce::framebuilder structs (reused, not copied); noteInsert/onEndFrame record per insert (group, tag, name, size, FNV, first 0x20 bytes) and captureFrame prints them. Untyped entries print 0x40 bytes. OPEN: per-field printing (needs the descriptions agent's remaining OPEN field names) and the in-game run: BS_PROBE_FRAMES=3, compare counts with a CE poll of [F+0xDC57E8].

### Q1d profiler - OPEN (GPU half)
CPU half DONE-pending-build: RewriteTimed feeds per-entry atomics and the existing Profiler row ("rewrite", name); report() logs ns per call original vs rewrite. GPU half needs a custom item (Encoder::submitCustom 0xBC61560, key bit 53) whose fn(user, ctx) runs on the render thread in view order and issues timestamp queries on ctx's command list; ctx layout (0x18 bytes) is inferred [?]. Test: with the DLL injected, submit one custom item in a spare view whose fn increments an atomic and logs ctx[0..2] and the thread id; confirm render thread, once per frame, in view order; then add the D3D12 timestamp query heap.

### Q1e ownership table - DONE-pending-build
RewriteOwnership.h: one row per rewritten function (thread, owned memory, lifetime, sharing). Sources: dossiers + BGFX_MAP lines 751/753/1492 (render thread waits ctx+0x80, runs cmdPre, slot 50 submit, cmdPost, posts ctx+0x100). Frame::sort is called inside submit so it is render-thread [V call graph]; Encoder::submit runs on task threads, one encoder each, CAS on Frame+0xDC57E8 [V bc60740.md].

### N1a - OPEN
Seam: D3D12 submit 0xE82E230 = slot 50 of base vtable 0xF4ED2D0; live object is the RTX subclass (vtable 0xF4EEE80), override 0xE83D440 wraps it [V D3D12Rvas, RendererContext.h kSubmit=50]. Records: header = Frame + 0xB4700 + (id<<7), id = u16 at Frame+0x94700 [V Frame.h]; bind records at base[Frame+0x8B4700] stride 0x540. Chosen route: not a submit takeover but a post-hook in Frame::sort (registry entry, runs inside submit on the render thread, Frame stable) that edits keys/slots. Acceptance: a post-hook swapping two same-view slots visibly changes draw order, 10 min no crash. Needs the DLL.

### N1b - OPEN
Per-draw veto: do NOT zero numIndices (0xFFFFFFFF means whole buffer). Safe veto = remove the slot from the sorted list in the Frame::sort post-hook (shift ids, decrement Frame+0xDC57E8) [I: executor 0xE822673 reads list and count]. Acceptance: veto all draws of view V -> that view disappears, no device lost, probe count drops by the vetoed number. Needs the DLL.

### N1c - OPEN
submitCustom 0xBC61560, key bit 53 (SortKey::kCustomBit); payload 16 bytes at encoder+0x100 [V Encoder.h]. ctx first field unknown [?]. Procedure = Q1d test; log ctx bytes and which are pointers.

### N1d - OPEN
PSO builder: the checklist says 0xE81DC60 but 62.01 is 0xE81E860 (Sigs.json psoBuilder, D3D12Rvas::kPsoBuilder) -- CONTRADICTS the checklist/BGFX_MAP 8c text (60.05 value). Key mask 0x0707007FFFFFF0FF [V]. Replacement draws keep using the executor so the builder is reused unchanged; a rebuilt key is only needed if the executor is replaced (Q4). Acceptance (DLL): counter hook on 0xE81E860 vs distinct (state&mask, variant key, framebuffer, layout) from the probe.

### N1e - OPEN
Per-view setup 0xE818490 (3 calls inside submit, 6t): no Q2 rewrite changes the call order inside submit (they sit at Frame::sort and in the encoders). Acceptance (DLL): shadow mode 5 min, unchanged frame time, no asserts.

### N1f - OPEN
Disk cache 0xE8FEB10 not touched by Q2. Rule for later: a replacement that changes blobs changes the key or deletes the blob. Needs the cache key RE (not done).

### N2a - OPEN
Slot 6 Present, 60 reset (0xE81A610, RTX 0xE83EC70), 59 shutdown, 7 TDR (0xE8102B0 [I]). No rewrite runs there. Eject: registry detours are ordinary Detours in Detour::all, removed by disableAll; the hosted entry has no detour. Acceptance (DLL): resize/fullscreen toggle with all entries in verify, no fatal. TDR stays [?] (forcing a GPU hang in the user's session is not allowed). Note D3D12Context.h kInit = slot 58, shutdown 59: consistent.

### N2b - OPEN
Create/destroy slots run on the render thread through the command interpreter 0xBC68E40 (cmdPre/cmdPost around submit, BGFX_MAP 1492). Q2 touches none: accounted for by the ownership table. Real acceptance is Q4c (counter hooks vs the resource tables).

### N3a - OPEN (static [V], live [?])
Model per RewriteOwnership.h. Acceptance (DLL): log GetCurrentThreadId in the Frame::sort detour and in dispatch(): expect exactly 1 thread for sort and several for submit.

### N3b - OPEN
Double buffer spacing 0xE749C0 [V live 6ij]. Semaphores ctx+0x80 / ctx+0x100 [V static BGFX_MAP 751]; their object layout is unread. Rewrites do not touch them. Procedure (read-only CE): read the qwords at ctx+0x80 and ctx+0x100, then the first 0x20 bytes of each object twice 100 ms apart (bounded), note which counter moves.

### N3c - OPEN
Custom items on the render thread in view order: [V static per the audit]; live = Q1d test.

### N4a - OPEN
Six Sigs.json entries to add (list above), knownRva stored in each RewriteEntry and checked on 1.26.62. Note: the game uses FNV-1a (xor, then multiply) at 0x5679DB0 and 0x675E440, not FNV-1: the checklist wording is loose [V `xor rcx,r15; imul rcx,rbx`].

### N4b - OPEN
RewriteRegistry::install already fails loudly: version Ok, sig resolved, knownRva equal. Missing: content-check rows (lead owns layout_asserts.json and RenderLayoutAsserts.h). Proposed rows: 0x5679DB0 {0x9E3779B9, 0xCBF29CE484222325, 0x100000001B3}; Frame::sort and Encoder::submit rows already exist.

### O1a - DONE (design)
Modules in the client DLL, no new DLL, no exports: folder src/client/features/render/rewrite/, self-registering entries (RewriteReg, same idea as HookReg), one init call (registration note 1).

### O1b - OPEN
Eject removes registry detours with all others; hosted dispatch vanishes with RenderMarkHook's detour. Acceptance (DLL): inject, set entries to verify, eject: clean unload, no "DRAIN TIMED OUT".

### O2a - OPEN
New files include Frame.h, Encoder.h, D3D12Context.h, BgfxContext.h, Tasks.h; compile status unknown until the lead builds (no /Zs allowed).

### O2b - DONE (static)
D3D12Context.h re-read: tables match the brief's live anchors (index 0x93A178/0x78, vertex 0x9B2178/0x80, shaders 0xAAA178/0xB8, programs 0xB62178/0xF8, textures 0xBDE178/0xB8, layouts 0xC96198/0x54, framebuffers 0xC97698/0x68), static_asserts on geometry present [V]. The probe uses kRendererGlobal and kPrograms.

### O3a - OPEN
SelfTest world phase needs a run with the DLL; nothing added by me.

### O3b - OPEN
Coverage of constants my code relies on: Encoder::submit rows exist for 0xDC57E8/0x14700/0x94700/0xB4700/0x8B4700/0x540/0x518/0x5BD1E995/0x6AD/0xFFFE/0xDC57E0/0x1EAB1B2/0x1EAAC60/0x680/0x688/0x69C/0x654/0x514; not covered (small values): 0x68C,0x690,0x694,0x698,0x6AC,0xA3,0xBA. My files static_assert the SDK side. Lead edits both lists.

### O3c - OPEN
Port check of the new sigs: generated against 62.01 only. Procedure: add them to Sigs.json, then run tools/sigs/where.py with BS_EXE on 50.04/51.01/60.05 and record found/unique/rva. Static, lead can run it.

### O3d - DONE
Static tools only, no debugger, no game write; Cheat Engine was not used.

### O4a - OPEN
Behavior text without RVAs, to paste into docs/BEHAVIOR_NOTES.md: mat4Multiply "4x4 multiply, out row i = sum_j B[i][j] * A.row[j], summed left to right, all loads before stores"; setVec4Array "memcpy a vec4 array into the block at the slot's offset, mark the slot dirty, fold the slot index (FNV-1a) and the XXH64 of the value (its 8 bytes FNV-1a'd) into the block's running hash with hash_combine"; ResourceCache::get "recursive-locked keyed get-or-load; stale keys force a reload and retire the old holder; used flag set on every get". Helpers 0x567D280/0x567CF50/0x567D9F0 still unread.

### P1a - DONE (seam map)
Used: Frame::sort (order control + probe), Encoder::submit (hosted), uniform writer, ResourceCache, mat4. Documented, unused: submit takeover 0xE82E230/0xE83D440 (N1a), executor/flush veto (N1b), custom item (N1c), PSO builder 0xE81E860 (N1d), TaskDispatch pass control (P1b). Reason: edits at Frame::sort happen on the render thread with a stable Frame and need no executor job-model knowledge (Q4a open).

### P1b / P2c - OPEN
TaskDispatchHook.cpp read: drop() parks the entry behind the new end (one shared_ptr leaked per drop per frame), swap() exchanges 0x80-byte entries; never built or run. Acceptance (DLL): listener drops pass X for 60 s: no crash, pass absent from the probe's pass list, no device lost; then swap two independent passes.

### P1c / P2a - OPEN
RenderMarkHook (passLookup, bodyActor, submit, stateEncode, replay) read; conflict found and handled (RenderMark::submit == Encoder::submit, hosted entry). The probe prints the mark byte per slot: enable chams for one player, BS_PROBE_FRAMES=3, expect marked slots = that player's body draws (~5). Needs the DLL.

### P1d / P2b - OPEN
FrameFilterHook drops by kind: compare seen[]/dropped[] with probe per-view counts over 3 frames. Needs the DLL.

### P3a - OPEN
Sigs.json already has Encoder{submit,reset,frameSort,...}, FrameGraph{endFrame,generate,taskDispatch,viewSetupTask}, D3D12Context{drawExecutor,psoBuilder,drawFlush,setVertexBuffers}; content checks in RenderLayoutAsserts.h (O3b); needs a SelfTest run.

### P3b / P3c / P3d - OPEN
P3c: reading every record is done by the probe; modifying needs the N1b test. P3d needs the P1b test. P3b depends on Q6a (not started).

### R14 rewrite parts
M3c = P1b, M3d = P1c, M3e = N1b + probe, M3f = N1c/Q1d. M4a: six new Sigs (N4a). M4d = O3c. M3a/M3b/M4b/M4c untouched by me beyond the notes above.
