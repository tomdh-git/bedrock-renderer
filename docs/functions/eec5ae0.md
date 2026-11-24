# Dossier: sub_eec5ae0 (0xeec5ae0)

## Mechanical facts

- size 0x6 bytes (docs/data/native_functions.tsv), 1 instruction, 0 pushes, no stack frame
- address range: 0xeec5ae0..0xeec5ae6
- callers: 39 call sites in 32 functions [V: rdis xr 0xeec5ae0]; every site is `lea rcx,[<string constant>]; call 0xEEC5AE0`, return value unused
- Direct callees: none
- Indirect calls: none — the instruction is an indirect tail jump through data slot 0xF9A7318, not a call
- Strings referenced by the instruction: none
- Constants: 0xF9A7318 (data slot RVA, .rdata)

### Instruction listing (rdis dis 0xeec5ae0, verbatim)

```
  eec5ae0  jmp qword ptr [0xF9A7318]                     ; [data_f9a7318]
```
(0xeec5ae6 begins `int3` padding after the function end; function size is 0x6 per docs/data/native_functions.tsv.)

## Analyst sections (every claim tagged [V]/[I]/[?])

### Purpose

sub_eec5ae0 is a tail-forwarder thunk: it jumps through data slot 0xF9A7318 (.rdata) which the PE import table maps to MSVCP140.dll `?_Xinvalid_argument@std@@YAXPEBD@Z` = `std::_Xinvalid_argument(const char*)` [V: tools/sigs/peimports.py on Minecraft.Windows.exe 1.26.62.01: `0F9A7318  MSVCP140.dll !?_Xinvalid_argument@std@@YAXPEBD@Z`]. At runtime the loader fills the slot with the imported function's address, so the jmp dispatches to std::_Xinvalid_argument. All 39 call sites pass the error message in RCX [V: rdis xr 0xeec5ae0]; e.g. `0x275314  lea rcx,[0xF535F41]` ("invalid stoi argument") then `0x27531b  call 0xEEC5AE0` [V]. This is the std::stoi invalid_argument path: _Xinvalid_argument throws std::invalid_argument and never returns [I: MSVC CRT throw-helper contract].

### Signature (real argument list and calling convention)

```cpp
void sub_eec5ae0(const char* message);   // message in RCX (x64 Microsoft ABI first register argument), void return [V: call sites set only RCX before the call]
```
Control never returns to the caller [I: _Xinvalid_argument throws].

### Reversed source (complete)

```cpp
// 0xeec5ae0..0xeec5ae6
//   0xeec5ae0  jmp qword ptr [0xF9A7318]     ; [data_f9a7318]
// tail jump to *slot 0xF9A7318 = MSVCP140!std::_Xinvalid_argument(const char*)
return std::_Xinvalid_argument(message);   // 0xeec5ae0  jmp qword ptr [0xF9A7318]
```

### Struct fields touched

none — the instruction reads only the argument register RCX and the data slot; it writes no memory and touches no struct fields [V].

### Direct callees

none [V].

### Data-slot target (callee through slot)

- slot 0xF9A7318 (.rdata) -> MSVCP140.dll `?_Xinvalid_argument@std@@YAXPEBD@Z`, `void _Xinvalid_argument(const char*)` [V: peimports.py]. Lifted as a direct call to std::_Xinvalid_argument per the indirect-call/data-slot rule: same argument (RCX), tail-call effect, slot RVA documented.

### Ownership / threading

Stateless: reads no game memory, writes no game memory, allocates nothing. Safe to call from any thread once the import slot is loaded [I].

### Version anchors

- exe: Minecraft.Windows.exe 1.26.62.01 (RVAs relative to image base) [V: docs/RENDER_NATIVE_SPEC.md, rdis section output]
- function: 0xeec5ae0, size 0x6, depth 0, milestone 7, region root, status D0 [V: docs/data/native_functions.tsv, docs/progress/_d_U-EX7.eec5ae0.txt]

### Verification

- Source: src/client/features/render/native/helpers/sub_eec5ae0.cpp + sub_eec5ae0.h
- `python tools/sigs/liftcheck.py 0xeec5ae0` -> result quoted under ## LIFTCHECK in docs/progress/oc_U-EX7.eec5ae0.md
