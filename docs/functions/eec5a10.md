# Dossier: sub_eec5a10 (0xeec5a10)

## Mechanical facts

- size 0x6 bytes, 1 instruction [V: rdis dis 0xeec5a10]
- `0xeec5a10  jmp qword ptr [0xF9A75B8]` ; [data_f9a75b8] — an indirect tail jump through IAT data slot 0xF9A75B8 in .rdata [V: rdis dis 0xeec5a10; .rdata covers rva 0xeec8000..0x1230c284 per rdis sec]
- No prologue, no stack frame, no call instruction in [0xeec5a10, 0xeec5a16) [V]
- Slot 0xF9A75B8 holds the imported address of MSVCP140!_Mtx_unlock: `void _Mtx_unlock(struct _Mtx*)` [V: IAT resolution table in docs/progress/oc_U-EX0b1.md, peimports.py: 0xF9A75B8 = _Mtx_unlock]

## Signature guess / register/argument map

- `void sub_eec5a10(struct _Mtx* mtx)` — x64 Microsoft ABI: rcx = mtx pointer, forwarded unchanged to the target; void return, return value discarded by callers [V: call sites `0xe81d7d4  mov rcx,[rbp-8]` / `0xe81d7d8  call 0xEEC5A10` then `0xe81d7dd  mov eax,edi` (value discarded), and `0xe81d829  mov rcx,[rbp-8]` / `0xe81d82d  call 0xEEC5A10`; IAT resolution _Mtx_unlock(void*) per docs/progress/oc_U-EX0b1.md]
- `struct _Mtx` is opaque: the thunk accesses no field of it; no memory is read or written by the instruction itself beyond the slot load [V: single memory operand is the slot [0xF9A75B8]]

## Phases

- 0xeec5a10..0xeec5a16: `jmp qword ptr [0xF9A75B8]` — tail jump to _Mtx_unlock through IAT data slot 0xF9A75B8; rcx=mtx forwarded as-is. Corresponding C++: `return ::_Mtx_unlock(mtx);` [V]

## Struct fields touched

- none: the thunk reads no struct fields and writes no memory [V]

## Callees

- none: the instruction is a jmp, not a call, so there are no callees in [0xeec5a10, 0xeec5a16) [V]
- Indirect jump target (control transfer, not a call): _Mtx_unlock via data slot 0xF9A75B8, resolved via the PE import table [V: docs/progress/oc_U-EX0b1.md IAT table]; declared with its real symbol in sub_eec5a10.h and called directly by the lifted body (tail call, same target the original jumps to).

## OPEN questions

- none

## Reversed source (complete)

// LIFT 0xeec5a10 size 0x6 1.26.62.01 sub_eec5a10
// (source file: src/client/features/render/native/helpers/sub_eec5a10.cpp, header sub_eec5a10.h)

struct _Mtx;  // opaque MSVCP140 C11 mutex; the pointee is never inspected by this forwarder

extern "C" void _Mtx_unlock(struct _Mtx* mtx);   // real target of IAT data slot 0xF9A75B8

namespace native {

void sub_eec5a10(struct _Mtx* mtx) {
    // 0xeec5a10..0xeec5a16: jmp qword ptr [0xF9A75B8] ; tail jump to _Mtx_unlock via IAT slot 0xF9A75B8
    return ::_Mtx_unlock(mtx);   // 0xeec5a10  jmp qword ptr [0xF9A75B8]
}

} // namespace native

LIFT_FN(eec5a10, "sub_eec5a10", 0xEEC5A10, native::sub_eec5a10, nullptr);

Verbatim instruction of the function (matches rdis dis 0xeec5a10):
#if 0
0xeec5a10  jmp qword ptr [0xF9A75B8]
#endif

## Registry entry

LIFT_FN(eec5a10, "sub_eec5a10", 0xEEC5A10, native::sub_eec5a10, nullptr) at file scope in sub_eec5a10.cpp (the milestone gate appends the Sigs.json anchor).

## Layout constants with static_asserts

sub_eec5a10Layout in src/client/features/render/native/helpers/sub_eec5a10.h:
- `static_assert(sizeof(void*) == 8, ...)` — x64 ABI, pointer-sized address space
- `using Fn = void (__cdecl*)(struct _Mtx*); static_assert(sizeof(Fn) == 8, ...)` — x64 function pointer is 8 bytes
No struct-field offsets are used by the thunk, so there are no field offsets to assert.

## Ownership / threading

- The thunk itself touches no game memory and has no side effects of its own; it transfers control to _Mtx_unlock, which performs the unlock on the mutex object owned by the caller. Thread model: same as the caller and the mutex owner.

## Version anchors

- Minecraft Bedrock 1.26.62.01, RVA 0xeec5a10, size 0x6 [V].
