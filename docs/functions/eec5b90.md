# sub_eec5b90 (0xeec5b90, size 0x6) - Minecraft Bedrock 1.26.62.01

Source: rdis dis 0xeec5b90 (one instruction, then int3 padding); PE import table of
C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe.
Lifted source: src/client/features/render/native/helpers/sub_eec5b90.cpp
(header: sub_eec5b90.h, registry entry LIFT_FN(eec5b90, ...) in the same file).

## Signature
_Thrd_result sub_eec5b90(_Cnd_t cond);   // x64 Microsoft ABI: RCX = cond (_Cnd_t is the
// CRT condition-variable pointer type _Cnd_internal_imp_t*), _Thrd_result return

## Register/argument map
- RCX (argument 1): _Cnd_t cond — the MSVCP140 C11 condition variable (_Cnd_t is already a
  pointer type, _Cnd_internal_imp_t*); forwarded unchanged to the jump target. Observed at
  call sites, e.g.
  0x3b208f  mov rcx,rsi
  0x3b2092  call 0xeec5b90   ; -> sub_eec5b90   (RCX = rsi, a pointer)
- RAX/EAX: _Thrd_result return value of _Cnd_broadcast, passed straight through because the
  original is a tail jump (jmp, not call); control never returns to this function's own
  epilogue.
- No other registers are read or written by the function.
- _Cnd_t and _Cnd_broadcast are already declared by the MSVC CRT headers
  (_Cnd_t = _Cnd_internal_imp_t*; _Thrd_result _Cnd_broadcast(_Cnd_t) noexcept); neither is
  redeclared in the lift header.

## Disassembly and phases
[0xeec5b90, 0xeec5b96) — one instruction:
  0xeec5b90  jmp qword ptr [0xF9A7560]    ; [data_f9a7560]
Loads the 8-byte function pointer from IAT slot RVA 0xF9A7560 (.rdata) and tail-jumps to it.
Slot contents on disk: peptr reads slot 0xF9A7560 as 0xF9AB854 (import-by-name entry), and
peimports lists 0F9A7560 MSVCP140.dll!_Cnd_broadcast. At runtime the loader fills the slot
with _Cnd_broadcast's address, so the jmp dispatches to
int _Cnd_broadcast(struct _Cnd_t*) with the RCX argument forwarded and the int result passed
straight through to this function's caller.

## Reversed source (complete)
// 0xeec5b90..0xeec5b96
int sub_eec5b90(struct _Cnd_t* cond) { return _Cnd_broadcast(cond); }

The C++ tail-call forwards the single pointer argument and returns the int result, identical
to the original's tail jump through data slot 0xF9A7560.

Verbatim instruction of the function:
#if 0
0xeec5b90  jmp qword ptr [0xF9A7560]
#endif

## Struct fields touched
None. The function reads only the IAT slot (an absolute address, not a struct field) and
writes nothing. No layout offsets are used; the header asserts the x64 ABI contract instead.

## Callees
None in the lift set (0 direct callees). The instruction is a tail jump through data slot
0xF9A7560 to MSVCP140!_Cnd_broadcast, resolved by the loader at runtime; _Cnd_broadcast is an
MSVCP140 import, not a lift-set function and not a boundary wrapper. The lifted body calls it
through its declared import signature (same pattern as sibling units sub_eec59e0 ->
std::_Xbad_function_call through data slot 0xF9A7310, sub_eec59f0 -> MSVCP140!_Mtx_lock
through data slot 0xF9A75A8, sub_eec5a00 -> std::_Throw_Cpp_error through data slot 0xF9A72F0).

## Version anchors
- Function size 0x6 per docs/progress/_d_U-EX7.eec5b90.txt (row 0xeec5b90, depth 0, milestone D0, 0 callees).
- RVAs, slot contents, import name from the PE of Minecraft.Windows.exe 1.26.62.01.

## Ownership / threading
_Cnd_broadcast wakes all threads waiting on the given C11 condition variable; the threading
contract of the caller is unchanged by the tail jump. No thread synchronization of our own.

## OPEN questions
None.
