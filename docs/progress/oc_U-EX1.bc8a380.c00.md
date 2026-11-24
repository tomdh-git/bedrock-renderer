## NEXT
DONE

## DONE
X1.bc8a380.c00 LIFT CHUNK sub_bc8a380 part 1/2 range 0xbc8a380..0xbc8bb76.
Fixed the chunk source so `liftcheck --range bc8a380 0xbc8a380 0xbc8bb76` prints LIFTCHECK OK.

What was wrong (from the orchestrator hint + `liftcheck --explain --range`):
- 45 of 74 call instructions in the chunk were not quoted verbatim.
- 5 of the existing `#if 0` call quotes had wrong addresses and so failed verify_oc:
  0xbc8b092 (real `mov rdx,[rbp+c48]`), 0xbc8b1d7 (real `mov r8,r15`),
  0xbc8b458 / 0xbc8b46c / 0xbc8b480 (real `nop`). The true calls were at
  0xbc8b099, 0xbc8b1da, 0xbc8b453, 0xbc8b467, 0xbc8b47b.

Fix applied (the only change):
- Replaced the entire `#if 0 ... #endif` verbatim-quote block in
  src/client/features/render/native/bgfx/sub_bc8a380_chunk0.cpp with all 74 call
  instructions of the chunk range, copied verbatim from the disassembly
  (format `0xRVA  call ...`, two spaces) in address order 0xbc8a4ae..0xbc8bb70.
- The `// CHUNK 0xbc8a380..0xbc8bb76` marker line was already present (line 2) and is unchanged.
- Every instruction of [0xbc8a380, 0xbc8bb76) was already inside a cited `// 0xA..0xB` range in the
  chunk body; the only missing piece was the verbatim call quotes, now supplied.

First and last instruction of the range (verbatim):
0xbc8a380  push rbp
0xbc8bb70  call 0x75720

## FILES
- src/client/features/render/native/bgfx/sub_bc8a380_chunk0.cpp (modified: replaced the `#if 0` verbatim call-quote block with all 74 chunk call quotes; body and CHUNK marker unchanged)

## LIFTCHECK
Command: `python tools/sigs/liftcheck.py --range bc8a380 0xbc8a380 0xbc8bb76 --explain`
Output:
LIFTCHECK OK 0xbc8a380 0xbc8a380..0xbc8bb76

## UNRESOLVED CALL
none
Notes (all calls in range resolve):
- Direct lift-set callees (native symbols): 0x567C8B0, 0xE86B370, 0x56B8630, 0x568AD40, 0xBC8C890,
  0x130EE0, 0x568C420, 0x5693A80, 0xBC8C720, 0x56D5810, 0x9BD3C0, 0x5668AC0.
- Boundary callees (docs/data/native_boundary.tsv): 0x9BD2E0 (os), 0xE869FF0 (lift, native_functions.tsv),
  0x76A8A0 (stl), 0xEEC6EC0 (lift), 0x9BC830 (alloc), 0x9D6D0 (stl), 0xEEC6DE0 (lift),
  0xE935700 (lift), 0x78ED0 (crt), 0xE938CB0 (os), 0x79580 (stl), 0xE938D70 (os), 0x75720 (stl).
- Import thunk (boundary class, like 0xeec6ed0 "jmp qword ptr [IAT] import thunk"):
  0xEEC5870 at caller 0xbc8a4ae = `jmp qword ptr [0xF9A75A0]` (loader-resolved import slot).
- Indirect calls through data slots (not blockers, per the indirect-call rule):
  `call qword ptr [0xF99FFA0]` (slot = sub_eea6040, boundary line 506, vendor thunk) and
  `call qword ptr [0xF9A8C78]` at caller 0xbc8b936 (loader-resolved slot; read pointer at call time).

CLOSES? YES