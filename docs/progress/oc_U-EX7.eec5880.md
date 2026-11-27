## NEXT
DONE — unit X7.eec5880 (sub_eec5880, 0xeec5880, size 0x6) lifted: LIFTCHECK OK 0xeec5880, CLOSES? YES.

## GOAL
LIFT sub_eec5880 (0xeec5880, size 0x6, depth 0, D0, root region, 0 callees in set) — unit X7.eec5880. Contract: docs/RENDER_NATIVE_SPEC.md. Result file: docs/progress/oc_U-EX7.eec5880.md.

## STATE
- Disassembly [V: rdis dis 0xeec5880]: `0xeec5880  jmp qword ptr [0xF9A7918] ; [data_f9a7918]` then 5 int3 padding; function [0xeec5880, 0xeec5886). No prologue/frame/call; single 8-byte slot read (rdis sum: access base &data_f9a7918 size 8 ip 0xeec5880).
- Slot 0xF9A7918 (.rdata, file off 0xf9a6318) u64 = 0x0F9AC050 = import-by-name RVA hint 14, name 'K32GetProcessMemoryInfo' (kernel32) [V: PE bytes read directly from the exe file]. Loader resolves the slot at runtime; this function is a tail-jump thunk to K32GetProcessMemoryInfo.
- 3 call sites, all `call 0xEEC5880`, return value (RAX) discarded at each [V: rdis dis of the 3 callers]:
  - 0x7eee8: 0x7eed2 call [0xF9A6FD8]; 0x7eed8 lea rdx,[rbp+0x80]; 0x7eedf mov rcx,rax; 0x7eee2 mov r8d,0x50; 0x7eee8 call 0xEEC5880
  - 0x83168: 0x83155 call [0xF9A6FD8]; 0x8315b lea rdx,[rbp-0x20]; 0x8315f mov rcx,rax; 0x83162 mov r8d,0x50; 0x83168 call 0xEEC5880
  - 0xed35e3a: 0xed35e26 call [0xF9A6FD8]; 0xed35e32 lea rdx,[rsp+0x20]; 0xed35e37 mov rcx,rax; 0xed35e3a call 0xEEC5880
- Convention at every site: RCX = handle/ptr (result of `call qword ptr [0xF9A6FD8]`), RDX = &stack buffer (0x50 bytes), R8D = 0x50, R9 untouched.
- Lift (exact x64 ABI signature, tail-call forward): `int sub_eec5880(void* hProcess, void* ppsmemCounters, unsigned int cb) { return K32GetProcessMemoryInfo(hProcess, ppsmemCounters, cb); }`. K32GetProcessMemoryInfo declared extern "C" with the real Win32 signature (BOOL=int, HANDLE=void*, PPROCESS_MEMORY_COUNTERS=void*, DWORD=unsigned int) in comments; no windows.h include.
- No struct fields touched; no layout offsets beyond x64 ABI asserts (sizeof(void*)==8, sizeof(Fn)==8 in the header).

## FILES
- docs/progress/oc_U-EX7.eec5880.md (this result file; finalized)
- docs/functions/eec5880.md (dossier: mechanical facts, slot resolution, signature/argument map, phases, struct fields touched, callees, ownership/threading, version anchors, 'Reversed source (complete)' with verbatim call quotes)
- src/client/features/render/native/helpers/sub_eec5880.h (sub_eec5880Layout static_asserts, extern "C" K32GetProcessMemoryInfo decl, native::sub_eec5880 signature)
- src/client/features/render/native/helpers/sub_eec5880.cpp (first line `// LIFT 0xeec5880 size 0x6 1.26.62.01 sub_eec5880`, cited body, #if 0 verbatim quote block, `LIFT_FN(eec5880, "sub_eec5880", 0xEEC5880, native::sub_eec5880, nullptr);`)

## LIFTCHECK
`python tools/sigs/liftcheck.py 0xeec5880` -> `LIFTCHECK OK 0xeec5880` (exit 0). Quoted verbatim from the command output; no failures printed, nothing to fix.

## UNRESOLVED CALL
none — the only call target (via import slot 0xF9A7918 -> K32GetProcessMemoryInfo) is a kernel32 import called through a real Win32 signature declaration; no callee outside the lift set/boundary remains unresolved.

CLOSES? YES
