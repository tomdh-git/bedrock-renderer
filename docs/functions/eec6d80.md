# Dossier: sub_eec6d80 (0xeec6d80)

## Mechanical facts

- size 0x6 bytes, 1 instruction [V: rdis dis 0xeec6d80]
- instruction: `0xeec6d80  jmp qword ptr [0xF9A8A18]  ; [data_f9a8a18]` [V]
- callees (direct): none [V: the body is a single indirect `jmp`, not a `call`]
- callers: resolved by rdis xref (many sites); one lifted in-tree caller is sub_e874d80 at `0xe874e02  call 0xEEC6D80` [V: src/client/features/render/native/d3d12/sub_e874d80.cpp]
- class: lift (docs/data/native_boundary.tsv: `0xeec6d80 lift`) [V]

### Argument use

- rcx = a0: exception object pointer, forwarded unchanged to _CxxThrowException [V: caller convention at 0xe874da2..0xe874e02; nothing in the function reads rcx itself]
- rdx = a1: throw-info pointer, forwarded unchanged to _CxxThrowException [V: same]
- r8 = a2, r9 = a3 and stack arguments: forwarded unchanged by the tail jump; read by no instruction in this function [V: single-instruction body]

### Direct callees

- none [V]

### Indirect calls

- `jmp qword ptr [0xF9A8A18]` at 0xeec6d80: data slot 0xF9A8A18 (.rdata) is the VCRUNTIME140.dll import slot of `_CxxThrowException` [V: tools/sigs/peimports.py prints `0F9A8A18 VCRUNTIME140.dll!_CxxThrowException`; slot qword 0x0000000F9B0090 points at the import-by-name entry "_CxxThrowException" read from the image]. The jmp is RIP-relative: next RIP 0xeec6d86 + disp 0xAE1C92 = 0xF9A8A18 [V: bytes FF 25 92 1C AE 00 at 0xeec6d80].

### Strings

- none

### Loops

- none

### Jump tables

- none

### Notable constants (>= 0x1000)

- 0xF9A8A18 x1: data slot address (RIP-relative target of the jmp) [V]
- 0xF9B0090 x1: qword stored at slot 0xF9A8A18 (RVA of the "_CxxThrowException" import-by-name entry) [V]

## Analyst sections

### Purpose

sub_eec6d80 is a tail-forwarding thunk for VCRUNTIME140!_CxxThrowException: the whole function is `jmp qword ptr [0xF9A8A18]`, an indirect jump through its import slot. At runtime the loader fills the slot with _CxxThrowException's address; RCX (exception object) and RDX (throw info) arrive from the caller and are forwarded unchanged. Nothing is read from or written to memory; control never returns to the caller because _CxxThrowException never returns [V: the single instruction; peimports.py; caller convention at 0xe874da2..0xe874e02].

### Signature

`void sub_eec6d80(void* a0, std::uintptr_t a1, std::uintptr_t a2, std::uintptr_t a3)` — x64 Microsoft ABI; equivalent to `_CxxThrowException(void* exceptionObject, const _s__ThrowInfo* throwInfo)` with extra caller arguments forwarded unread [V: tail-jump forwarding; _CxxThrowException reads RCX and RDX only].

### Reversed source (complete)

```cpp
// 0xeec6d80..0xeec6d86: jmp qword ptr [0xF9A8A18] ; tail call to _CxxThrowException via data slot 0xF9A8A18
return _CxxThrowException(a0, reinterpret_cast<const void*>(a1));   // 0xeec6d80  jmp qword ptr [0xF9A8A18]
```

Verbatim instruction of the function (matches rdis dis 0xeec6d80):

```
0xeec6d80  jmp qword ptr [0xF9A8A18]
```

### Struct fields touched

- none: the function reads no memory and writes none [V]

### Callee

- VCRUNTIME140.dll!_CxxThrowException(void* exceptionObject, const _s__ThrowInfo* throwInfo) — reached through data slot 0xF9A8A18, forward-declared and called directly; noreturn [V: peimports.py]

### Ownership / threading

- stateless: no memory touched [V]

### Open questions

- none
