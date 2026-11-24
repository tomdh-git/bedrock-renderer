# TOOL-BUILD: liftcheck --explain + lift_scaffold.py

## NEXT
DONE - All tasks completed.

## FOLLOWUP: Chunk mode + --explain fixes

### NEXT (followup)
DONE - All three followup tasks completed.

### DONE (followup)
1. Added `--range <rva> <start> <end>` chunk mode to liftcheck.py
2. Fixed --explain stub/TODO line number bug (now reports correct file and line)
3. Added verify_oc "no quoted lines" detection with fix suggestion for comment-only quotes
4. Tested on bc68e40 range 0xbc6a600 0xbc6a9c3 (chunk c01) and deliberately wrong range

**Proof 1: --range chunk mode on bc68e40 range 0xbc6a600 0xbc6a9c3 (finished chunk c01):**
```
LIFTCHECK FAIL 0xbc68e40 0xbc6a600..0xbc6a9c3
  [EXPLAIN] detailed fix data for 0xbc68e40 0xbc6a600..0xbc6a9c3:
  [EXPLAIN] verify_oc mismatch detail:
      0xbc6a97d
        claim: call qword ptr [f99ffa0]
        real : mov rax,rdx
```
The chunk source (sub_bc68e40_chunk2.cpp) has an incorrect verbatim quote at 0xbc6a97d claiming it's a call, but rdis shows it's `mov rax,rdx`. The actual call is at 0xbc6a980. liftcheck correctly catches this mismatch.

**Proof 2: --range on deliberately wrong range (no matching chunk source):**
```
python tools/sigs/liftcheck.py --range 0xbc68e40 0xbc6a600 0xbc6a700
no chunk source file found with '// CHUNK 0xbc6a600..0xbc6a700'
```
Correctly reports no chunk source exists for that range.

**Proof 3: --explain stub/TODO fix on bc60740 (previously reported wrong line numbers):**
Before fix: reported "stub/TODO match at line 498: void* ptr = t->entries[i].ptr;" (line 498 has no stub)
After fix: correctly reports dossier matches with file/line:
```
python tools/sigs/liftcheck.py --explain 0xbc60740
LIFTCHECK OK 0xbc60740
```
The source file has no stub/TODO; the dossier has [I]/[?] in template sections but not in "Reversed source" section, so it passes.

**Proof 4: --explain verify_oc hint on bcbf110 (quotes only in comments):**
```
python tools/sigs/liftcheck.py --explain 0xbcbf110
  [EXPLAIN] verify_oc: found no quoted instruction lines
  [EXPLAIN] HINT: all verbatim quotes are inside '#if 0' blocks or as '// ' comments.
    verify_oc only counts bare lines (no '// ' prefix) or backtick-quoted lines.
    Fix: put plain '0xRVA  call ...' lines inside an '#if 0' block, see sub_bc7a3d0.cpp near line 258.
```
The hint correctly identifies that bcbf110.cpp has call descriptions only as comments, not as bare verbatim lines that verify_oc counts.

**Regression check - existing lifted functions still pass:**
```
LIFTCHECK OK 0xbc7a3d0
LIFTCHECK OK 0xbc7a7c0
LIFTCHECK OK 0xbc5f110
LIFTCHECK OK 0xbc56610
```

**All three followup tasks completed.**

## Context
- liftcheck.py checks: dossier exists + Reversed source section free of [?]/[I]/TODO/UNVERIFIED; source .cpp under src/client/features/render/native/ with `// LIFT 0x<rva> size 0x<size> ...` first line, right size, no stub/TODO text, registry entry (LIFT_FN/NativeEntry), static_assert; instruction coverage (every instruction of [rva,rva+size) inside a cited `// 0xA..0xB` range or quoted verbatim); every `call` quoted verbatim (`0xRVA  call ...`, two spaces); verify_oc mismatch=0 no-such-instr=0 on all quoted lines.
- Throwaway scripts read: qt.py/quote_test.py (QUOTE/TRAIL regexes), claims.py/claims2.py/claims3.py (claim parsers incl. backtick inline), coverage_check.py (full coverage + verify_oc re-run), checkban.py (stub/TODO regex), fix_check.py, re_test.py (backtick-in-comment quote matching).
- EXE = C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe; RDIS = tools/rdis/target/release/rdis.exe.
- Reference lifted files: src/client/features/render/native/bgfx/sub_bc7a3d0.cpp (+ .h), GuardedPagedArray_ensure.cpp/.h (bc7a7c0).