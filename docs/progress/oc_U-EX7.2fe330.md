## NEXT
DONE

## FILES
src/client/features/render/native/helpers/sub_2fe330.h
src/client/features/render/native/helpers/sub_2fe330.cpp
docs/functions/2fe330.md (appended ## Reversed source section)

## LIFTCHECK
GATE OK 0x2FE330

## UNRESOLVED CALL
none

## Reversed source summary
sub_2fe330 is a single basic block (0x2fe330..0x2fe43b) that initializes a destination state block a0. It calls sub_39a7ad0(&stack_copy_of_a1_f0, 0) and stores the returned pointer at a0+0x0, then fills a0 from a3 (vtable ptr/qword), a4 (5th arg), a5 (6th arg r14), and constants, zeroing most remaining fields. Returns a0 (original rcx). sub_39a7ad0 signature is evidence-based (ptr to 16-byte buffer, uint32 flag -> pointer); its true signature is not derivable from static data.

CLOSES? YES
