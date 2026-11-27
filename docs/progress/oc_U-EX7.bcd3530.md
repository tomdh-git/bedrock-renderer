## NEXT
DONE

## FILES
- src/client/features/render/native/helpers/sub_bcd3530.cpp
- src/client/features/render/native/helpers/sub_bcd3530.h
- docs/functions/bcd3530.md (appended `## Reversed source (complete)`)

## LIFTCHECK
GATE OK 0xBCD3530
LIFTCHECK OK 0xbcd3530
cppsyntax: src/client/features/render/native/helpers/sub_bcd3530.cpp: OK (syntax)

## DECISIONS
- RCX object read/written through RSI (0xbcd3537 mov rsi,rcx): self layout at
  +0x08/+0x10/+0x18 and +0x38/+0x40/+0x48 = two begin/end/capacity pointer triples;
  +0x28 = pointer to a list header (0x50-byte allocation) whose +0x00 is the node chain
  head and whose +0x08 is a pointer to a qword cleared at 0xbcd358e.
- Node chain: node +0x00 next, node +0x10 payload destroyed via boundary 0x9b250,
  node freed with size 0x50.
- 0xe935700 (lift-set callee) declared locally with the ABI from its own lifted header
  (`void* sub_e935700(void*)`, argument in RCX, result in RAX); it forwards RCX to
  0x392960 and overwrites RDX before any use (`0x392972 mov rdx,rcx`), so the size in
  RDX at the original call sites is dead and is not passed.
- 0xbcd3632 `call qword ptr [0xF9A8C78]`: data-slot indirect call with five zero
  arguments (ECX/EDX/R8D/R9D and the [rsp+0x20] stack slot), non-returning; emitted as
  a five-argument function-pointer call through the slot value, followed by no code
  (the int3 at 0xbcd3638 is unreachable).

## UNRESOLVED CALL
none

CLOSES? YES
