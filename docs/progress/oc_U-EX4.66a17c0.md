## NEXT DONE

## UNIT
U-EX4.66a17c0 — LIFT sub_66a17c0 (0x66a17c0, 0x51 bytes, depth 1, D0, framebuilder, "Item group visitor")

## SUMMARY
Lifted sub_66a17c0 to C++ mirroring the exe exactly. Reads a1+0x0 (start) and a1+0x8 (end); computes diff=end-start; writes a0+0x0 = 0xAAAAAAAAAAAAAAAB * ((diff>>4) arithmetic) (low 64); if diff != -48 writes a0+0x8 = start; returns a0 unless (start==0 && end!=0). On either failure path (diff==-48, or start==0 && end!=0) calls sub_78ed0 (class crt boundary, noreturn) with RCX=a0, then int3 (unreachable). Same reads, writes, call order, return. No null guard or SEH (original has none).

## DISASSEMBLY (rdis fn 0x66a17c0, verbatim)
  66a17c0  sub rsp,0x28
  66a17c4  mov r8,[rdx]
  66a17c7  mov rax,[rdx+8]
  66a17cb  mov rdx,rax
  66a17ce  sub rdx,r8
  66a17d1  mov r9,rdx
  66a17d4  sar r9,4
  66a17d8  mov r10,0xAAAAAAAAAAAAAAAB
  66a17e2  imul r10,r9
  66a17e6  mov [rcx],r10
  66a17e9  cmp rdx,0xFFFFFFFFFFFFFFD0
  66a17ed  je short 0x66A180B
  66a17ef  mov [rcx+8],r8
  66a17f3  test r8,r8
  66a17f6  setne dl
  66a17f9  test rax,rax
  66a17fc  sete al
  66a17ff  or al,dl
  66a1801  je short 0x66a180B
  66a1803  mov rax,rcx
  66a1806  add rsp,0x28
  66a180a  ret
  66a180b  call 0x78ED0
  66a1810  int3

## FILES
- docs/progress/oc_U-EX4.66a17c0.md (this result file, written)
- docs/functions/66a17c0.md (created: dossier with Reversed source (complete))
- src/client/features/render/native/framebuilder/sub_66a17c0.h (created: layout constants, static_asserts, PairU64, signature)
- src/client/features/render/native/framebuilder/sub_66a17c0.cpp (created: LIFT marker first line, body, verbatim #if0 block, Footprint, LIFT_FN)

## CALLEE AUDIT
- 0x78ed0 = class crt boundary (docs/data/native_boundary.tsv line 11), called via `native::Boundary<void, std::uintptr_t> sub_78ed0("sub_78ed0")`; noreturn; not a blocker.
- No other calls. No unresolved calls.

## CPPSYNTAX
`python tools/cppsyntax.py src/client/features/render/native/framebuilder/sub_66a17c0.cpp` — 0 errors in sub_66a17c0.cpp. (112 cascade errors are pre-existing missing-<atomic>/<vector> issues in shared framework headers Detour.h/Profiler.h under standalone /Zs; shared headers must not be edited per rules, and no error references the lifted file.)

## LIFTCHECK
LIFTCHECK OK 0x66a17c0

## UNRESOLVED CALL
none

CLOSES? YES
