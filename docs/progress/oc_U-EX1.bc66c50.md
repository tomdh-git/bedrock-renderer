## NEXT
DONE — unit complete.

## UNIT
U-EX1.bc66c50 — LIFT sub_0xbc66c50 "Frame renderer lambda", rva 0xbc66c50 size 0x11e bytes depth 2 milestone D0 region bgfx. 0 callees in lift set.

## SUMMARY
Lifted function 0xbc66c50 (65 instructions, extent [0xbc66c50, 0xbc66d6e)) to C++ with the exact x64 ABI signature `void* sub_bc66c50(void* self /*rcx*/)` returning rax. Same reads/writes/calls/return as the disassembly, every block cited with `// 0xA..0xB`, every `call` quoted verbatim. Verified with liftcheck: LIFTCHECK OK 0xbc66c50.

Calls (all handled, none unresolved):
- 0xbc66c9d  call 0xEBDBF10 — tiny forwarder `jmp qword ptr [0xF9A7B10]` outside both tables; forward-declared `extern "C" void native::sub_ebdbf10(void*)` (sub_bc66c50.h, namespace native, rule 66/69) and called directly with rcx = &self+0x180, return unused [V]
- 0xbc66cff  call 0xEBDB740 — boundary class os (native_boundary.tsv line 484); args rcx=self+0x1CFD0C8, rdx=limit u16, r8=count u16, r9=count+1 u16; return rax -> elem+0x6F0, via native::Boundary<void*,uint16_t,uint16_t,uint16_t>("sub_ebdb740") [V]
- 0xbc66d50, 0xbc66d5d  call 0xEBDBF20 — same forwarder as above, rcx = &self+0x180 [V]
Fast path: dword [gs-array[[0x128767C8]]+0x2D4C] == 0x78666762 ("bgfx") -> return [self+0x13D18] [V]
No stack cookie, no SEH, no loops, no jump tables [V]

## FILES
src/client/features/render/native/bgfx/sub_bc66c50.h       (layout constants, ElemLayout + static_asserts, signature, footprint decl, thunk forward-decls)
src/client/features/render/native/bgfx/sub_bc66c50.cpp     (lifted body, first line LIFT marker, Boundary wrapper, LIFT_FN registry entry)
docs/functions/bc66c50.md                                  (dossier with Reversed source (complete) + verbatim instruction listing)
docs/progress/oc_U-EX1.bc66c50.md                          (this file)

## LIFTCHECK
LIFTCHECK OK 0xbc66c50

## UNRESOLVED CALL
none

## TOOL REQUESTS
None

CLOSES? YES
