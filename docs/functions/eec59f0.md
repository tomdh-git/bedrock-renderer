# sub_eec59f0 (0xeec59f0, size 0x6) - Minecraft Bedrock 1.26.62.1

Source: rdis dis 0xeec59f0 (one instruction, then int3 padding); PE import table of
C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe.
Lifted source: src/client/features/render/native/helpers/sub_eec59f0.cpp
(header: sub_eec59f0.h, registry entry LIFT_FN(eec59f0, ...) in the same file).

## Signature
extern "C" void sub_eec59f0(struct _Mtx* mtx);   // x64 Microsoft ABI: RCX = mtx, void return

## Register/argument map
- RCX (argument 1): struct _Mtx* mtx — pointer to the MSVCP140 C11 mutex; forwarded unchanged
  to the jump target. Observed at call sites, e.g.
  0x7e9d1  mov rcx,rbx
  0x7e9d4  call 0xeec59f0   ; -> sub_eec59f0
  and
  0x7ef00  lea ecx,[0x128CBD78]
  0x7ef06  call 0xeec59f0   ; -> sub_eec59f0
- RAX: none (void return). The tail jump never returns to the caller; control passes straight
  to the target, whose RET returns to sub_eec59f0's caller.
- No other registers are read or written by the function.

## Disassembly and phases
[0xeec59f0, 0xeec59f6) — one instruction:
  0xeec59f0  jmp qword ptr [0xF9A75A8]    ; [data_f9a75a8]
Loads the 8-byte function pointer from IAT slot RVA 0xF9A75A8 (.rdata) and tail-jumps to it.
Slot contents on disk: import-by-name RVA 0xF9AB92C (hint 1413) whose entry is
'MSVCP140.dll!_Mtx_lock' (slot index 160 of the MSVCP140.dll import block). At runtime the
loader fills the slot with _Mtx_lock's address, so the jmp dispatches to
void _Mtx_lock(struct _Mtx*) with the RCX argument forwarded.

## Reversed source (complete)
// 0xeec59f0..0xeec59f6
void sub_eec59f0(struct _Mtx* mtx) { return ::_Mtx_lock(mtx); }

The C++ tail-call forwards the single pointer argument and returns void, identical to the
original's tail jump through data slot 0xF9A75A8.

Verbatim instruction of the function:
#if 0
0xeec59f0  jmp qword ptr [0xF9A75A8]
#endif

## Struct fields touched
None. The function reads only the IAT slot (an absolute address, not a struct field) and
writes nothing. No layout offsets are used; the header asserts the x64 ABI contract instead.

## Callees
None in the lift set (0 direct callees). The instruction is a tail jump through data slot
0xF9A75A8 to MSVCP140!_Mtx_lock, resolved by the loader at runtime; _Mtx_lock is an MSVCP140
import, not a lift-set function and not a boundary wrapper. The lifted body calls it through
its declared import signature (same pattern as the sibling unit sub_eec59e0 -> std::_Xbad_function_call
through data slot 0xF9A7310).

## Version anchors
- Function size 0x6 per docs/data/native_functions.tsv (row 0xeec59f0, depth 0, milestone D0).
- RVAs, slot contents, import name and hint from the PE of Minecraft.Windows.exe 1.26.62.01.

## Ownership / threading
_Mtx_lock acquires the given C11 mutex; the threading contract of the caller is unchanged by
the tail jump. No thread synchronization of our own.

## OPEN questions
None.
