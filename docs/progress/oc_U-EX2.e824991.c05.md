## NEXT
Chunk c05 body is NOT yet written — file is a quote farm. Disassembly is on disk at `_tmp/c05.txt` (rdis dis 0xe82c101 1200; lines 1-1133 are the range 0xe82c101..0xe82d4dd, last instruction 0xe82d4dd call 0xEEC59E0). Write the real C++ body into `src/client/features/render/native/d3d12/sub_e824991_chunk_c05.cpp` (keep the `// CHUNK 0xe82c101..0xe82d4dd` marker, the `#if 0` call-quote block, the `LIFT_FN` line), then run `python tools/sigs/liftcheck.py --range 0xe824991 0xe82c101 0xe82d4dd`. Density rule: >= ~1 source line per 20 bytes (range is 0x13dc = 5084 bytes → ~250+ lines of translated body).

## STATE
- Callees in this chunk and their status (all resolved, none UNRESOLVED):
  - `0xE8360F0` sub_e8360f0 — lift (upload ring allocator), header exists? NO .h found; forward-declare `extern "C" void sub_e8360f0(void* rcx, uint32_t r8d, uint32_t r9d)` (seen as `mov r8d,0xFFFF; mov r9d,0x100; mov rcx,[rbx+0x578]; lea rdx,[rbx+0x3B0]; call 0xE8360F0`).
  - `qword ptr [0xF99FFA0]` = sub_eea6040 — vendor boundary (docs/data/native_boundary.tsv:506). Call via `native::sub_eea6040(rcx,rdx,r8,r9)` or a `call r10` after `mov r10,[0xF99FFA0]`.
  - `0xEEC6EC0` sub_eec6ec0 — lift (native_functions.tsv:1648), forward-declare.
  - `0xE81B4D0` sub_e81b4d0 — lift, setVertexBuffers (native_functions.tsv:1441).
  - `0xEBCE430` sub_ebce430 — CRT memset thunk, declared in sub_e824991_chunk_c01.h as `void sub_ebce430(void* rcx, void* rdx)`.
  - `0xE81B720` sub_e81b720 — lift, D3D12 draw batch flush (native_functions.tsv:1442).
  - `0xEBDB740` sub_ebdb740 — os boundary (native_boundary.tsv:484).
  - `0xE81D850` sub_e81d850 — lift, header+cpp exist (sub_e81d850.h/cpp), `extern "C" void sub_e81d850(void* rcx, void* rdx, uint32_t r8d)`.
  - `0xEEC59E0` sub_eec59e0 — lift (native_functions.tsv:1641), forward-declare `void sub_eec59e0()`.
  - `qword ptr [0xF9A8C78]` — MSVC invalid-param/runtime-report IAT (data_f9a8c78), boundary; call as `(*reinterpret_cast<void(*)(void)>(0xF9A8C78))()` or a `native::boundary` wrapper. Preceded by xor r8d/r9d; mov qword ptr [rsp+0x20],0.
- Chunk state struct `ChunkState_e824991_c05` already defined in the .h (rbx,rbp,r12-r15,rsi,rdi,xmm6-xmm15,stack_frame; offsets rbx=0, stack_frame=224).
- Pattern from chunk c01 (already lifted, passes): helpers `SF_Q/SF_W/SF_B`, `LoadDataSlot`, `CallVendorAlloc`; locals copied from state at entry; `goto loc_xxx` for every basic block; `// 0xA..0xB` range comments; call quotes inside `#if 0`.
- Function tail (0xe82d45c..0xe82d4bd): restore xmm6-xmm15 from [rbp+0xE110..0xE1A0], `lea rsp,[rbp+0xE1B8]`, pop rbx,rdi,rsi,r12,r13,r14,r15,rbp, ret. The 0xe82d4be branch is an error path: call 0xEEC59E0; mov [rsp+0x20],0; xor ecx,edx,r8d,r9d; call [0xF9A8C78]; call 0xEEC59E0; int3.
- `0x12BB4910` and `0x12ADF800` are data slots (global device / allocator vtable) read as `*reinterpret_cast<void**>(0x12BB4910)`.

## FILES
- src/client/features/render/native/d3d12/sub_e824991_chunk_c05.cpp (quote farm, needs body)
- src/client/features/render/native/d3d12/sub_e824991_chunk_c05.h (struct + asserts, OK)
- docs/progress/oc_U-EX2.e824991.c05.md
- _tmp/c05.txt (full disassembly of the range)

## LIFTCHECK
`python tools/sigs/liftcheck.py --range 0xe824991 0xe82c101 0xe82d4dd` currently prints `LIFTCHECK OK` but the body is a quote farm (fails the density/auto-tick rule).

## UNRESOLVED CALL
none