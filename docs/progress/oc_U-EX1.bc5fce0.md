## NEXT
DONE

UNIT U-EX1.bc5fce0: lift sub_0xbc5fce0 (0xbc5fce0, 0x41d bytes, depth 2, D0, 0 callees in set) — CLOSED.

Source of truth: docs/progress/_d_U-EX1.bc5fce0.txt — row: 0xbc5fce0 size 0x41d depth 2 milestone 1 region bgfx status D0 root "D3D12 submit RTX override" callees_in_set: (none) callees_outside_set: 0xe951550. Function range [0xbc5fce0, 0xbc600fd).

## FILES
- docs/progress/oc_U-EX1.bc5fce0.md (this result file; rewritten with final state)
- docs/functions/bc5fce0.md (dossier: signature, argument map, instruction-complete phases with verbatim instruction quotes, call classification, struct fields touched, 'Reversed source (complete)' section)
- src/client/features/render/native/bgfx/sub_bc5fce0.h (layout constants Bc5fce0Params/Bc5fce0Ctx/Bc5fce0Block offsets, data-address constants, vtable-slot constants 0x198/0x1A0, loop/frame constants, signature extern "C" void sub_bc5fce0(void*, void*, void*), static_asserts)
- src/client/features/render/native/bgfx/sub_bc5fce0.cpp (first line `// LIFT 0xbc5fce0 size 0x41d 1.26.62.01 sub_bc5fce0`, faithful instruction-faithful translation, LIFT_FN registration, LIFT marker size 0x41d)

## LIFTCHECK
`python tools/sigs/liftcheck.py 0xbc5fce0` printed:

LIFTCHECK OK 0xbc5fce0

(verify_oc on the source: claimed=7 match=7 mismatch=0 no-such-instr=0.)

## UNRESOLVED CALL
Three calls in 0xbc5fce0 have targets outside the CALLEES set (empty) and outside docs/data/native_boundary.tsv; they are documented here and expressed faithfully (no wrapper invented):

1. 0xbc5fdaf  `call qword ptr [0xF99FFA0]` (in sub_bc5fce0). Cell 0xF99FFA0 holds sub_eea6040; 0xEEA6040 disassembles as `jmp rax`, with rax = vfptr[0x198] loaded immediately before (0xbc5fda0..0xbc5fda3) => effectively the virtual call vfptr[0x198](a1, a2). Target not statically known. Expresses as direct vtable-slot invocation vf[0x198/8](a1, a2).
2. 0xbc5fe0f  `call qword ptr [0xF99FFA0]` (in sub_bc5fce0). Same cell/thunk => vfptr[0x1A0](a1, a2, ebp). Target not statically known. Expressed as vf[0x1A0/8](a1, a2, ebp).
3. 0xbc5fffc  `call 0xEBCE390` (in sub_bc5fce0) with (rcx=r15, rdx=&block, r8d=0x70) => 0x70-byte block copy. 0xEBCE390 -> jmp 0xEEC6EC0; 0xEEC6EC0 -> `jmp qword ptr [0xF9A8A98]`; real target only known at runtime. Declared extern "C" void sub_ebce390(void*, const void*, std::uint32_t) with the observed argument layout.

The fourth call, 0xbc600f7  `call 0xE951550`, targets sub_e951550 = boundary class crt (native_boundary.tsv line from oc_U-EX0b1.md) and is made through native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550").

## TOOL REQUESTS
None.

CLOSES? YES
