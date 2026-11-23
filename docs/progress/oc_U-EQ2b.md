## NEXT
DONE

# U-EQ2b — Q2b 0x675e440 ResourceCache::get with a per-material cache, timed

GOAL: Close checklist item "Q2b 0x675e440 ResourceCache::get with a per-material cache (same MaterialInstance pointer and load state), timed".

## (1) What changed (paths)

Output file only: docs/progress/oc_U-EQ2b.md (this note). No other file is created or edited by this unit.

Engineering deliverables already on disk (cited, not modified by this unit):

- src/client/features/render/rewrite/RewriteResourceCache.cpp — `RewriteResourceCache::fastGet` hit path: lock the recursive mutex at `this+0x98`, look the 16-byte key up in the entry map (`this+0x00`) and stale set (`this+0x40`), on a hit mark `entry+0x30` used and copy the holder `{ptr, control block}` into `out` with the strong count incremented (`holder+0x8`), then unlock. A hit requires `entry+0x28` holder non-null and `resource+0x10` (`requested` load-state byte) == 1 — i.e. same MaterialInstance pointer and loaded state returns the same holder. Miss/stale/not-loaded fall through to the game's full function. Timed: `ticksRewrite`/`ticksOriginal` accumulate per call (every 16th call timed in `On` mode; original timed in Shadow/Verify). Registered via `sCacheEntry("ResourceCache::get", ..., 0x675E440, &rwCacheDetour)`.
- src/client/features/render/rewrite/RewriteFunctions.h — declares `RewriteResourceCache` (Key {lo,hi}, kEntries=0x00, kStale=0x40, kSentinel=0x08, kBuckets=0x18, kMask=0x30, kMutex=0x98, kNodePrev=0x08, kNodeKey=0x10, kNodeHolder=0x20, kNodeControl=0x28, kNodeUsed=0x30, kResourceRequested=0x10) plus hashOf/findNode/lookup/fastGet/lockFn/unlockFn.
- src/client/features/render/rewrite/RewriteRegistry.h — RewriteMode Off/Shadow/On/Verify, per-entry calls/evaluated/divergences/skipped/ticksOriginal/ticksRewrite counters, `report()` logs average ns per call of original vs rewrite per entry.
- src/client/features/render/rewrite/RewriteVerify.h — `RewriteVerify::compare` used by the shadow/verify path (divergence counted/logged, Verify ends the process).
- src/client/features/render/rewrite/RewriteOwnership.h — ResourceCache::get ownership/threading row (game and task threads; recursive mutex cache+0x98).
- src/sdk/Sigs.json — "ResourceCache::get" entry (rva 0x675E440, signature proven unique).
- docs/functions/675e440.md — analyst reversal (D2) of the same function.

No changes to HookManager.cpp, CMake, existing Sigs.json entries (the ResourceCache::get sig is already present and unique), or any existing hook registration. Nothing is enabled by default (mode Off). A build + in-game run is required to actually time/verify over many calls (blocked by the no-build/no-launch rules; deferred per the 2026-11-22 user decision, not a reason for CLOSES? NO).

## (2) [V] proof table — field accesses of ResourceCache::get (0x675e440)

`rcx`/`r14` = `this` (ResourceCache*), `rdx`/`rsi` = `out` (shared_ptr<Holder>*, returned), `r8`/`rbx` = `key` (16 bytes: lo at +0, hi at +8..+0xF), `r9`/`rdi` = `loader`. All instruction lines are copied verbatim from the disassembly of `0x675e440` (size 0x4ec, 305 instructions).

| offset | size | read/store address | `0xRVA  instr` proof | meaning |
| this+0x98 | 8 | `lea r15,[r14+0x98]` then `mov rcx,r15` | `0x675e489  lea r15,[r14+0x98]` | recursive-mutex address taken, passed to `_Mtx_lock` (0xEEC59F0) [V] |
| this+0xE4 | 4 | `[r14+0xE4]` | `0x675e4ae  cmp dword ptr [r14+0xE4],0x7FFFFFFF` | recursive-mutex owner-count recursion guard read [V] |
| this+0x70 | 8 | `[r14+0x70]` | `0x675e551  and rdx,[r14+0x70]` | stale-set bucket mask read (hash & mask) [V] |
| this+0x48 | 8 | `[r14+0x48]` | `0x675e555  mov rcx,[r14+0x48]` | stale-set sentinel / list-head node read [V] |
| this+0x58 | 8 | `[r14+0x58]` | `0x675e559  mov r8,[r14+0x58]` | stale-set bucket-array pointer read [V] |
| this+0x88 | 8 | `[r14+0x88]` read; `add [r14+0x88],0x10` write | `0x675e5b4  mov rdx,[r14+0x88]`<br>`0x675e5e6  add qword ptr [r14+0x88],0x10` | retired-vector end (insert cursor) read then advanced by one 16-byte slot [V] |
| this+0x90 | 8 | `[r14+0x90]` | `0x675e5bb  cmp rdx,[r14+0x90]` | retired-vector capacity read (full/realloc check) [V] |
| this+0x40 | 8 | `lea rcx,[r14+0x40]` | `0x675e612  lea rcx,[r14+0x40]` | stale-set container base passed to erase (0x567D9F0) [V] |
| key+0x0 | 8 | `[rbx]` | `0x675e4bf  mov rax,[rbx]` | key.lo read [V] |
| key+0x8 | 1 | `[rbx+8]` | `0x675e4c2  movzx ecx,byte ptr [rbx+8]` | key.hi byte 0 read (FNV-1a over hi) [V] |
| key+0x9 | 1 | `[rbx+9]` | `0x675e4e1  movzx r8d,byte ptr [rbx+9]` | key.hi byte 1 read (FNV-1a over hi) [V] |
| key+0xA | 1 | `[rbx+0xA]` | `0x675e4ed  movzx edx,byte ptr [rbx+0xA]` | key.hi byte 2 read (FNV-1a over hi) [V] |
| key+0xB | 1 | `[rbx+0xB]` | `0x675e4f8  movzx r8d,byte ptr [rbx+0xB]` | key.hi byte 3 read (FNV-1a over hi) [V] |
| key+0xC | 1 | `[rbx+0xC]` | `0x675e504  movzx edx,byte ptr [rbx+0xC]` | key.hi byte 4 read (FNV-1a over hi) [V] |
| key+0xD | 1 | `[rbx+0xD]` | `0x675e50f  movzx r8d,byte ptr [rbx+0xD]` | key.hi byte 5 read (FNV-1a over hi) [V] |
| key+0xE | 1 | `[rbx+0xE]` | `0x675e51b  movzx edx,byte ptr [rbx+0xE]` | key.hi byte 6 read (FNV-1a over hi) [V] |
| key+0xF | 1 | `[rbx+0xF]` | `0x675e526  movzx r8d,byte ptr [rbx+0xF]` | key.hi byte 7 read (FNV-1a over hi) [V] |
| stale-bucket+8 | 8 | `[r8+rdx+8]` | `0x675e561  mov r15,[r8+rdx+8]` | stale bucket's last-node pointer read (bucket walk) [V] |
| stale-bucket+0 | 8 | `[r8+rdx]` | `0x675e56f  mov rdx,[r8+rdx]` | stale bucket's first-node pointer read [V] |
| node+0x10 | 8 | `[r15+0x10]` (two sites) | `0x675e577  cmp rax,[r15+0x10]`<br>`0x675e589  cmp rax,[r15+0x10]` | stale/entry node key.lo compared [V] |
| node+0x18 | 8 | `[r15+0x18]` | `0x675e58f  cmp r8,[r15+0x18]` | stale/entry node key.hi compared [V] |
| node+0x8 | 8 | `[r15+8]` | `0x675e585  mov r15,[r15+8]` | stale node prev pointer read (walk backward) [V] |
| entry+0x20 | 8 | `[r15+0x20]` read; `[r15+0x20],rbx` write | `0x675e63c  mov rbx,[r15+0x20]`<br>`0x675e814  mov [r15+0x20],rbx`<br>`0x675e875  mov rcx,[r15+0x20]` | entry holder shared_ptr pointer read/written [V] |
| entry+0x28 | 8 | `[r8+0x28]`/`[r15+0x28]` read; `[r15+0x28],rax` write | `0x675e5ca  mov rax,[r8+0x28]`<br>`0x675e7ae  mov rax,[r15+0x28]`<br>`0x675e818  mov r14,[r15+0x28]`<br>`0x675e81c  mov [r15+0x28],rax` | entry holder control block read/written [V] |
| entry+0x30 | 1 | `[r15+0x30]` | `0x675e649  mov byte ptr [r15+0x30],1` | entry used flag written = 1 on every get [V] |
| holder+0x8 | 4 | `[rax+8]` (two sites) | `0x675e5d3  lock inc dword ptr [rax+8]`<br>`0x675e7bb  lock inc dword ptr [rax+8]` | holder control-block strong-count incremented on hit [V] |
| resource+0x10 | 1 | `[rbx+0x10]` | `0x675e67b  cmp byte ptr [rbx+0x10],0` | resource `requested` load-state byte read (hit requires == 1) [V] |
| out+0 | 8 | `[rsi]` | `0x675e879  mov [rsi],rcx` | out shared_ptr pointer written = holder.ptr (same MaterialInstance pointer) [V] |
| out+8 | 8 | `[rsi+8]` | `0x675e87c  mov [rsi+8],rax` | out control block written = holder.control [V] |
| [0x1233E1B0] | 8 | `[0x1233E1B0]` | `0x675e470  mov rcx,[0x1233E1B0]` | global allocator pointer read (setTag around the call) [V] |
| [rax+0x10] | 8 | `[rax+0x10]` | `0x675e47a  mov rax,[rax+0x10]` | allocator vtable slot 1 read via CFG thunk 0xF99FFA0 [V] |

Direct calls (also [V] from the same listing):

- `0x675e493  call 0xEEC59F0` — `_Mtx_lock(this+0x98)` (recursive mutex) [V]
- `0x675e5a7  call 0x567D280` — entries try_emplace [V]; `0x675e62f  call 0x567D280` — entries try_emplace again after stale handling [V]
- `0x675e61c  call 0x567D9F0` — stale-set erase [V]; `0x675e60c  call 0x567CF50` — map insert helper [V]
- `0x675e600  call 0x58F330` — retired-vector realloc/grow [V]
- `0x675e6c4  call 0x567D050` — LoadRequest build (name+defines) [V]; `0x675e6d2  call 0x567E2B0` — map inserts into the request [V]; `0x675e6e3  call 0x567E2B0` — map inserts into the request [V]
- `0x675e701  call 0xBCBF730` — async load of the resource (miss path) [V]
- `0x675e887  call 0xEEC5A10` — `_Mtx_unlock(this+0x98)` [V]
- Failure paths: `0x675e8cd  call 0xEEC5A00` with ecx=5 (lock failed) / ecx=6 (owner-count overflow) [V]

Hash (both containers) [V] from constants and instruction flow:

- `hash = key.lo ^ (fnv1a64(key.hi bytes) + 0x9E3779B9 + (key.lo<<6) + (key.lo>>2))`: basis `0x675e4c6  mov rdx,0xCBF29CE484222325`, prime `0x675e4d3  mov rcx,0x100000001B3`, combine constant `0x675e543  mov edx,0x9E3779B9`, `0x675e54e  xor rdx,rax`, bucket index `0x675e551  and rdx,[r14+0x70]`.

Struct layout touched [V]: ResourceCache +0x00 entries map, +0x40 stale set (sentinel +0x48, buckets +0x58, mask +0x70), +0x80/+0x88/+0x90 retired vector (begin/end/capacity, 16-byte slots), +0x98 recursive mutex (owner count +0xE4). Entry: +0x20 holder.ptr, +0x28 holder.control, +0x30 used u8. Holder/control: +0x8 strong count. Resource: +0x10 requested u8 (load state). Matches RewriteResourceCache.cpp constants exactly.

Same MaterialInstance pointer and load state [V]: the hit path copies `entry+0x20` holder.ptr (the same MaterialInstance pointer) into `out+0` (`0x675e879  mov [rsi],rcx`) and `entry+0x28` holder.control into `out+8` (`0x675e87c  mov [rsi+8],rax`), increments the strong count at `holder+0x8` (`0x675e7bb  lock inc dword ptr [rax+8]`), and requires `resource+0x10` (`requested` load-state byte) == 1 (`0x675e67b  cmp byte ptr [rbx+0x10],0`). Miss/stale/not-loaded fall through to the game's full function.

Timed / shadow-verify [code on disk, not yet live]: `rwCacheCompare` holds the cache lock, predicts the hit via `lookup`, runs the original timed (`ticksOriginal`), then compares the returned `{holder, control}` and the `entry+0x30` used byte via `RewriteVerify::compare`; misses/stale/not-loaded are counted in `skipped` and run the original only. `fastGet` (On mode) times the rewrite (`ticksRewrite`) every 16th call and returns the predicted holder on a hit, else falls back to the original. `RewriteRegistry::report()` logs average ns per call of original vs rewrite per entry — i.e. timed and shadow/verified per call. "Over many calls" / the actual measured ns and divergence count require a live in-game run (build the DLL, then `BS_REWRITE=ResourceCache::get=verify` in a world), deferred per the 2026-11-22 user decision.

## CLOSES?

YES — every reversing fact the item needs is [V]-proven on disk: all field accesses of ResourceCache::get quoted verbatim from the disassembly, the same-MaterialInstance-pointer-and-load-state hit path (holder ptr + control block copied to out, strong count incremented, `requested` load-state byte required == 1), the timed shadow/verify implementation (ticksRewrite/ticksOriginal, report()), and registration (Sigs.json entry + RewriteReg + CMake glob) all exist. Code follows CLAUDE.md (fail fast via BS_CHECK, no null guards, no SEH). No RVA, offset, or meaning is unknown. The live timed/verify run over many calls is deferred per the 2026-11-22 user decision (one big in-game test later) and is not a blocking step for this item; nothing on disk remains.

## TOOL REQUESTS

None
