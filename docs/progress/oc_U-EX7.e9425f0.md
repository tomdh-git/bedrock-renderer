## NEXT
DONE

## FILES
docs/progress/oc_U-EX7.e9425f0.md (this result file)
docs/functions/e9425f0.md (dossier: signature, register map, phases, Reversed source (complete), callees)
src/client/features/render/native/helpers/sub_e9425f0.h (layout constants/static_asserts, signature, boundary callee declaration)
src/client/features/render/native/helpers/sub_e9425f0.cpp (lifted body, LIFT_FN registry entry)

## Summary
Lifted sub_e9425f0 (0xe9425f0, size 0x13, 1.26.62.01, depth 0, D0). The exe body is a transparent allocator forwarder:
  0xe9425f0  sub rsp,0x28
  0xe9425f4  call 0x392920          ; -> sub_392920   (boundary: alloc)
  0xe9425f9  jmp short 0xE9425FD    ; -> loc_e9425fd
  0xe9425fb  xor eax,eax            ; dead code after the unconditional jmp
  0xe9425fd  add rsp,0x28
  0xe942601  ret
  0xe942602  int3                    ; padding inside declared size 0x13
It forwards rcx (64-bit allocation size in bytes) to boundary callee sub_392920 (class=alloc,
docs/data/native_boundary.tsv line 98) via native::boundary::sub_392920 and returns rax
unchanged; no memory is read or written, no struct fields touched, no stack argument addressed
(caller 0x6627c25 sets rcx = count<<4 at 0x6627c1e [V]). Dead code xor eax,eax and padding int3
are cited but not reproduced (unreachable). Verbatim call quote: 0xe9425f4  call 0x392920.

## LIFTCHECK
LIFTCHECK OK 0xe9425f0

## UNRESOLVED CALL
none

## TOOL REQUESTS
None

CLOSES? YES
