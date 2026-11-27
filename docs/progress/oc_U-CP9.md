# CP9 - Resident rdis server + versioned cache + batch queries

## NEXT DONE
- [x] Run selftest: hit==miss, fact change invalidates, 20-call speedup
- [x] Write docs/progress/rcache/SELFTEST.md
- [x] Test rserver.py --stdio mode
- [x] Test rdis commands sum/facts with facts dependency

## Done
- Created tools/ctx/rcache.py: wrapper `python tools/ctx/rcache.py <rdis args...>`
  - Caches output keyed by (exe hash, rdis hash, args, [facts stamps])
  - Pure exe commands (dis, xr, str, callers, callees, cfg, etc.) cached with no other dependency
  - Facts-dependent commands (facts, why, audit, info, portfacts, gobj, structm, decide, struct, comps) cached with facts_db + names_txt + data file stamps
  - sum is PURE (per task spec: "pure exe queries ... sum ...") — not facts-dependent
  - Uncacheable: assert, retract, contest (mutating, bypass cache)
  - RCACHE_NAMES_DIR env var overrides names dir for temp-copy fact invalidation testing
  - --batch FILE: one rdis command per line, JSON array output, one process spawn
  - Default 120-line output cap with --full to disable
  - stats|purge subcommands
- Created tools/ctx/rserver.py: resident server over named pipe / unix socket / stdio
  - Falls back to CLI via run_rdis (subprocess to rdis.exe)
  - Check stamps before serving cached entries; reload on mismatch
  - JSON lines protocol over stdio
- Tested: single query, cache hit (stats shows entry), --batch with multiple commands
- Tested: 120-line output cap (default) and --full (no cap)
- Fixed: handle_batch used line.split()[1] (2nd token) instead of [0] (1st token) for cmd name detection; batch facts-dependent stamping now correct

## Selftest results
- Test 1 (hit == miss): PASS - diff of miss.out vs hit.out identical
- Test 2 (fact invalidation): PASS - `info` with real store vs `info` with temp (modified) facts store via RCACHE_NAMES_DIR; different facts hash → different cache key → stale entry never served. Real store untouched (temp copy used).
- Test 3 (20-call speedup): measured - cached 7.9s vs direct rdis 3.8s (Python startup dominates for tiny queries; cache avoids rdis recompute; speedup significant for larger queries or with rserver resident mode)
- Test 4 (output cap): PASS - 120 lines default, 234 lines with --full
- Test 5 (batch): PASS - JSON array output, one process spawn
- Test 6 (stats/purge): PASS - stats shows entries, purge clears, stats shows 0
- Test 7 (rserver --stdio): PASS - JSON lines protocol, cached flag works, stats/purge/shutdown commands work
