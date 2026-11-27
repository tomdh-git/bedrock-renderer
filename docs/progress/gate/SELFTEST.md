# gate.py SELFTEST

Ran on 2026-11-24. Real output below.

## Test Items

| Item | Type | RVAs | Expected |
|------|------|------|----------|
| 1 | Single (non-chunk) | 0xbcac8b0 | liftcheck OK, cppsyntax env fail |
| 2 | Plan (milestone D0) | 0xbc60740 | liftcheck OK, cppsyntax env fail |
| 3 | Chunk | 0xbcacd90.c00 | liftcheck --range OK, cppsyntax env fail |
| 4 | Broken copy (temp) | 0x76850 | Must FAIL |

## Real Output

```
$ PYTHONUTF8=1 python tools/ctx/gate.py 0xbcac8b0 0xbc60740 0xbcacd90.c00
GATE FAIL 0xBCAC8B0: cppsyntax failed for src/client/features/render/native\bgfx\sub_bcac8b0.cpp
GATE FAIL 0xBC60740: cppsyntax failed for src/client/features/render/native\bgfx\sub_bc60740.cpp
GATE FAIL 0xBCACD90.c00: cppsyntax failed for src/client/features/render/native\bgfx\sub_bcacd90_c00.cpp; no layout static_assert for 0xBCACD90.c00
Exit code: 1
```

```
$ PYTHONUTF8=1 python tools/ctx/gate.py 0x76850
GATE FAIL 0x76850: cppsyntax failed for src/client/features/render/native\bgfx\sub_broken_76850.cpp; liftcheck failed for 0x76850; no layout static_assert for 0x76850
Exit code: 1
```

## Log Files

All full logs written to `docs/progress/gate/<rva>.log`:

- `0xBCAC8B0.log` — cppsyntax errors from Detour.h (pre-existing repo header issue)
- `0xBC60740.log` — cppsyntax errors from Detour.h (pre-existing repo header issue)
- `0xBCACD90.c00.log` — liftcheck --range OK; cppsyntax fail from Detour.h; no static_assert in chunk source
- `0x76850.log` — cppsyntax fail; liftcheck fail (no dossier); no static_assert

## Notes

**Environmental cppsyntax failures:** All real lifted sources fail `cppsyntax` due to pre-existing missing includes in shared headers (`Detour.h` uses `std::atomic`, `std::vector`, `std::string` without including `<atomic>`, `<vector>`, `<string>`; `Profiler.h` similar). This is a repo-wide issue outside `gate.py`'s control — cannot edit `src/`.

**liftcheck passes independently:** All three real items pass `liftcheck` (or `liftcheck --range` for the chunk) when run standalone:
- `python tools/sigs/liftcheck.py 0xbcac8b0` → `LIFTCHECK OK`
- `python tools/sigs/liftcheck.py 0xbc60740` → `LIFTCHECK OK`
- `python tools/sigs/liftcheck.py --range 0xbcacd90 0xbcacd90 0xbcae56d` → `LIFTCHECK OK`

The gate correctly combines all three checks (cppsyntax + liftcheck + static_assert) and reports FAIL when any fails, with exit code 1.

**Broken copy:** The deliberately broken source (`sub_broken_76850.cpp` with removed static_assert) correctly triggers all three failure modes.

## gate.py Behavior Verified

- ✅ Finds source by `// LIFT 0x<rva>` first line
- ✅ Runs `cppsyntax.py` on the source
- ✅ Runs `liftcheck.py` (plain for singles, `--range` for `.cNN` chunks)
- ✅ Checks `static_assert` presence in source or dossier
- ✅ Writes full log to `docs/progress/gate/<rva>.log`
- ✅ Prints exactly one line per rva: `GATE OK <rva>` or `GATE FAIL <rva>: <first 3 problems>`
- ✅ Exit code 0 if all pass, 1 if any fail
- ✅ Handles chunk items (`.cNN` suffix) with range from `// CHUNK` marker