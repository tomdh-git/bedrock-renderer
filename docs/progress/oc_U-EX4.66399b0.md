## NEXT
DONE: unit U-EX4.66399b0 lifted and verified (see below).

## GOAL (done)
LIFT TASK U-EX4.66399b0: lift function 0x66399b0 (size 0x34, depth 0, D0, framebuilder, "BgfxFrameBuilder slot 91", 0 callees in set) to C++ per docs/RENDER_NATIVE_SPEC.md. Contract checked: docs/RENDER_NATIVE_SPEC.md; input data: docs/progress/_d_U-EX4.66399b0.txt.

## Summary of the lift

Function 0x66399b0 ([0x66399b0, 0x66399e4)), 15 instructions, no callees in the lift set, one call:
- 0x66399b8  mov rax,[rcx]        ; R self+0x0 (vtable pointer)
- 0x66399bb  mov rax,[rax+0x230]  ; R vtable+0x230 -> RAX (slot index 0x46 = 70)
- 0x66399c2  call qword ptr [0xF99FFA0]  ; -> sub_eea6040, boundary/vendor
  [V: docs/data/native_boundary.tsv row "0xeea6040 vendor thunk via data slot 0xF99FFA0
  (loader-resolved)"; rdis: [data_f99ffa0] = sub_eea6040]
  sub_eea6040 body [V]: 0xEEA6040  jmp rax — tail-calls RAX (= vtable+0x230 target) with
  RCX = self; result back in AL. Net effect = virtual call through vtable+0x230.
- 0x66399c8  mov ecx,eax   ; 0x66399ca  mov al,2   ; 0x66399cc  test cl,cl
  ; 0x66399ce  je short 0x66399DE -> return 2
- 0x66399d0  mov rax,[rsi+0x358]   ; R self+0x358 state pointer
  ; 0x66399d7  movzx eax,byte ptr [rax+0x7E6]  ; R state+0x7E6 -> AL
- 0x66399de  add rsp,0x20 ; 0x66399e2  pop rsi ; 0x66399e3  ret  ; return AL

Lifted as `uint8_t sub_66399b0(BgfxFrameBuilder* self)` (x64 Microsoft ABI, RCX = self,
return AL): if the trampoline call yields non-zero, return *(uint8_t*)(self->state0x358 +
0x7E6), else return 2. Same reads (vtable pointer, vtable+0x230, self+0x358, state+0x7E6),
same writes (none), same calls in the same order (one), same return. No null guard, no SEH,
no skipped branches — matching the original. Layout constants with static_asserts for every
used offset (0x358, 0x7E6) in sub_66399b0.h; LIFT_FN registry entry in sub_66399b0.cpp;
dossier at docs/functions/66399b0.md with 'Reversed source (complete)' and verbatim call
quote `0x66399c2  call qword ptr [0xF99FFA0]`.

## FILES
- docs/progress/oc_U-EX4.66399b0.md (this result file)
- docs/functions/66399b0.md (dossier: mechanical facts, signature, Reversed source (complete), struct fields, callees, verification)
- src/client/features/render/native/framebuilder/sub_66399b0.cpp (first line: `// LIFT 0x66399b0 size 0x34 1.26.62.01 BgfxFrameBuilder slot 91`, plus LIFT_FN entry)
- src/client/features/render/native/framebuilder/sub_66399b0.h (layout constants, static_asserts, ABI signature)

## LIFTCHECK
LIFTCHECK OK 0x66399b0

## UNRESOLVED CALL
none: the only call, 0x66399c2 `call qword ptr [0xF99FFA0]`, targets sub_eea6040, which is
listed in docs/data/native_boundary.tsv (class: vendor, thunk via data slot 0xF99FFA0,
loader-resolved). No callee is outside the lift set and the boundary table.

CLOSES? YES
