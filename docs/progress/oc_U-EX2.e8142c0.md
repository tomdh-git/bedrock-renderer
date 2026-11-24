## NEXT
DONE. U-EX2.e8142c0 lifted. No further steps.

## DONE
LIFT 0xe8142c0 (size 0xd6, 214 bytes) "createProgram (shader pointers, merged predefined uniforms)"
fully reversed and lifted. Body [0xe8142c0, 0xe814396), ret at 0xe814395. 49/49 instructions
cited; both `call 0xEBCE390` sites quoted verbatim; verify_oc 0 mismatch.

Checklist line: X2.e8142c0 LIFT createProgram (shader pointers, merged predefined uniforms),
fully reversed (0xe8142c0, 0xd6 bytes, depth 0, D2, 0 callees in set).

Summary of what the function does [V]:
- this=RendererContextD3D12* (rcx); a1=edx (uint16 program index, stride 0xF8), a2=r8w
  (uint16 shader-A index, stride 0xB8), a3=r9d (uint16 shader-B index; 0xFFFF = none).
- program[a1] record (this+0xB62178 + a1*0xF8): +0x00 = &shader[a2] (this+0xAAA178+a2*0xB8);
  +0x10 = bulk copy of shader[a2] data (this+0xAAA188+a2*0xB8), length shader[a2].count*8
  (count = byte at this+0xAAA228+a2*0xB8); +0xF0 = that count byte.
- if a3 != 0xFFFF: +0x08 = &shader[a3]; +0x10+cntA*8 = bulk copy of shader[a3] data
  (appended after shader A's blob); +0xF0 (byte) += shader[a3].count (8-bit).
- Two bulk copies call sub_ebce390(dst,src,size).

## FILES
- docs/progress/oc_U-EX2.e8142c0.md (this result file; created)
- src/client/features/render/native/d3d12/sub_e8142c0.cpp (new)
- src/client/features/render/native/d3d12/sub_e8142c0.h (new)
- docs/functions/e8142c0.md (new dossier)

## LIFTCHECK
```
$ python tools/sigs/liftcheck.py 0xe8142c0
LIFTCHECK OK 0xe8142c0
```
(verify_oc on the two artifacts: docs/functions/e8142c0.md claimed=9 match=9 mismatch=0
no-such-instr=0; sub_e8142c0.cpp claimed=49 match=49 mismatch=0 no-such-instr=0.)

## UNRESOLVED CALL
none. The only callee is 0xEBCE390 (sub_ebce390), called at 0xe81431e and 0xe814376.
sub_0xEBCE390 = `jmp 0xEEC6EC0`; sub_0xEEC6EC0 = `jmp qword ptr [0xF9A8A98]` (import thunk),
used as (rcx=dst, rdx=src, r8=size) memcpy-style. It is classified `lift` in
docs/data/native_boundary.tsv (line 509) and docs/data/native_functions.tsv (line 1622, root D0),
so it is forward-declared as native::sub_ebce390 and called through its native symbol; its own
unit lifts it and it links at the milestone gate. (Note: the unit's input data listed 0 callees
in set, but the disassembly shows the two sub_ebce390 calls; per the hard rule a lift-classified
callee is not a blocker.)

CLOSES? YES