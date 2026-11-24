## NEXT
DONE

## DONE
- Disassembly of 0xe874e20..0xe874e9b obtained via `tools/rdis/target/release/rdis.exe ... dis 0xe874e20 200` (fn reports size 0x7b, 5 xrefs in; caller sub_e870870 at offsets 0x244e/0x2466/0x2506/0x252b/0x2550).
- Data file: docs/progress/_d_U-EX2.e874e20.txt — row `0xe874e20 0x7b 6 2 d3d12 D0 BgfxFrameBuilder slot 16`, callees_in_set empty, callees_outside_set = 0xe951550.
- `0xe951550` is in docs/data/native_boundary.tsv classified `crt` (oc_U-EX0b1.md) — treat as boundary, not UNRESOLVED. Signature `void sub_e951550(std::uintptr_t)` used per sibling dossiers (e817790, e817b0f0, e81b3b0).
- `0xeec6d80` (called at 0xe874e88) is in native_boundary.tsv classified `lift` (auto-unresolved->lift) — forward-declare `native::sub_eec6d80`, call through it.
- `call qword ptr [0xF9A7480]` at 0xe874e39: slot 0xF9A7480 is a global indirect-call slot (55 xrefs across 16 functions, ripscan). Per the indirect-call hard rule this is NOT a blocker: read the pointer from the slot at call time and call it as a function pointer; document the slot RVA. [UNVERIFIED: 0xe874e39 — exact ABI of the indirect target; assumed __vectorcall/thiscall with r8d=size arg like the direct calls].
- Global 0x1230A0C0 = stack cookie (confirmed by sibling dossiers e817790, e818050, bc5f110).
- Function semantics: `bool sub_e874e20(void* obj /*rcx*/, void* dst /*rdx*/)` with hardcoded r8d=1. It is the same primitive as sibling slot-16 functions (e870630/e8707f0/e874d80/e874ea0): /GS cookie setup, indirect call to a length-checked byte copy (slot 0xF9A7480 with r8d=len), check the returned status (rax+8): negative -> zero-init 16 bytes at [rsp+0x30] and call sub_eec6d80 (0xF08E738 file, 0xFB3B080 data — an exception/trace record); else compare status to `len` and sete al (return 1 if equal, 0 otherwise); then /GS cookie check; on mismatch call sub_e951550 then int3. Callers pass rcx=rsi (the BgfxFrameBuilder object) and rdx=&local byte.

## FILES
- docs/progress/oc_U-EX2.e874e20.md (this file)
- docs/functions/e874e20.md
- src/client/features/render/native/d3d12/sub_e874e20.cpp
- src/client/features/render/native/d3d12/sub_e874e20.h

## LIFTCHECK
LIFTCHECK OK 0xe874e20

## UNRESOLVED CALL
none (0xe951550 boundary crt; 0xeec6d80 lift forward-declared; 0xF9A7480 indirect slot read-at-call-time per hard rule)

## TOOL REQUESTS
- `python tools/sigs/slotscan.py <rva>`: dump the 8-byte value at a data RVA and classify (function vs data) — I did this by hand with a python one-liner reading the file.

CLOSES? YES