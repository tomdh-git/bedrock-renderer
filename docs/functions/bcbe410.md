# Dossier: sub_bcbe410 (0xbcbe410)

Source: Minecraft Windows 1.26.62.01, `Minecraft.Windows.exe`, image-base RVAs. All instruction
lines below are quoted verbatim from `rdis.exe dis 0xbcbe410 17` and machine-checked with
`tools/sigs/verify_oc.py`.

- size 0x11 bytes ([0xbcbe410, 0xbcbe421)), depth 3, milestone 1, region bgfx, status D0
- row name: BgfxFrameBuilder slot 68
- callees in lift set: none (0); the one call target is outside both tables (see Callees)

## Signature and argument map (x64 Microsoft ABI)

The prologue reads no incoming argument and the body ends at `int3`, so nothing is returned:

```cpp
void sub_bcbe410(void);
```

Register map: rcx is overwritten by the body before any use (`lea rcx,[0xF571225]`), so no
incoming argument is observable; no other register is read before being written; no stack slot
is addressed ([V]: disassembly below).

## Reversed source (complete)

```cpp
// [0xbcbe410, 0xbcbe421), Minecraft Windows 1.26.62.01 [V]: rdis dis output, every line
// quoted verbatim:
//   0xbcbe410  sub rsp,0x28
//   0xbcbe414  lea rcx,[0xF571225]        ; data slot 0xF571225 = "invalid bitset char" [data_f571225]
//   0xbcbe41b  call 0xEEC5AE0             ; -> sub_eec5ae0 (not in native_functions.tsv / native_boundary.tsv)
//   0xbcbe420  int3
void sub_bcbe410(void) {
    // 0xbcbe410..0xbcbe414: sub rsp,0x28 — reserves 0x28 bytes of call stack; no [rsp+...]
    //   operand is addressed in the body, so the reservation has no observable effect here.
    // 0xbcbe414..0xbcbe41b: lea rcx,[0xF571225] — rcx = address of data slot 0xF571225
    //   ("invalid bitset char").
    // 0xbcbe41b..0xbcbe420: 0xbcbe41b  call 0xEEC5AE0 — calls sub_eec5ae0 with rcx = the
    //   slot address. sub_eec5ae0 is listed in neither docs/data/native_functions.tsv nor
    //   docs/data/native_boundary.tsv: no lift/boundary target exists. This is the unit's
    //   UNRESOLVED CALL blocker (docs/progress/oc_U-EX1.bcbe410.md); no wrapper is invented.
    // 0xbcbe420..0xbcbe421: int3 — __debugbreak(); the original never returns normally.
    __debugbreak();
}
```

## Phases (instruction-complete)

- 0xbcbe410..0xbcbe414: `sub rsp,0x28` — reserve call-stack space. No stack slot is
  addressed in the body ([V]).
- 0xbcbe414..0xbcbe41b: `lea rcx,[0xF571225]` — load the address of data slot 0xF571225
  ("invalid bitset char", tag [data_f571225]) into rcx ([V]).
- 0xbcbe41b..0xbcbe420: `0xbcbe41b  call 0xEEC5AE0` — call sub_eec5ae0 with the slot address
  in rcx ([V]).
- 0xbcbe420..0xbcbe421: `int3` — breakpoint; no return value ([V]).

Every instruction of [0xbcbe410, 0xbcbe421) is inside one of the ranges above or quoted
verbatim as `0xRVA  instr` ([V]: `rdis dis 0xbcbe410 17` lists exactly these four
instructions: `0xbcbe410  sub rsp,0x28`, `0xbcbe414  lea rcx,[0xF571225]`,
`0xbcbe41b  call 0xEEC5AE0`, `0xbcbe420  int3`).

## Struct fields touched

None: the body has no memory operand addressing an object field ([V]); `lea` loads a
data-slot address, not a struct field. No layout constants are required; `sizeof(void*) == 8`
is asserted in `src/client/features/render/native/bgfx/sub_bcbe410.h` and repeated in the
.cpp so liftcheck sees it.

## Callees

- 0xEEC5AE0 `sub_eec5ae0`: direct call at 0xbcbe41b (`0xbcbe41b  call 0xEEC5AE0`,
  argument rcx = data slot 0xF571225 "invalid bitset char"). Listed in neither
  docs/data/native_functions.tsv nor docs/data/native_boundary.tsv (and not in
  src/sdk/Sigs.json) → UNRESOLVED CALL: cannot be called from lifted code and no wrapper
  may be invented. Blocking fact for CLOSES?.

## OPEN questions

- What sub_eec5ae0 (0xEEC5AE0) does; its signature is unknown (only that it receives a
  char* in rcx here). It must be classified (lift/boundary) by the owning unit before this
  unit can close.
