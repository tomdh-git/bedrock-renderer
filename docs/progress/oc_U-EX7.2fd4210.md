## NEXT
DONE

## FILES
- src/client/features/render/native/helpers/sub_2fd4210.h
- src/client/features/render/native/helpers/sub_2fd4210.cpp
- docs/functions/2fd4210.md (appended ## Reversed source (complete) section)

## LIFTCHECK
GATE OK 0x2FD4210

## UNRESOLVED CALL
0x2fd42f7  call 0x2FD3E60 (sub_2fd3e60: not in lift set, not a classified boundary; callee signature not available from static data)

## Reversed source (complete)
The function at 0x2fd4210 takes (self: void*, a1: sub_2fd4210_rdx*, a2: sub_2fd4210_r8*, a3: uint32_t) in x64 MS ABI (rcx, rdx, r8, r9d).

Behavior:
1. Prologue: saves r9d to ebx, sets rsi=a2, rdi=rdx=a1, loads a2_home=[rbp+0x88] (home space for r8), initializes [rbp-0x10]=0.
2. Loads r8_val = a2_home->f38 ([a2+0x38]). If null, skips block 1.
3. Block 1 (r8_val != 0): saves self to r14, calls sub_eea6040(r8_val, &output_buffer) via data slot 0xF99FFA0 (boundary), stores return at [rbp-0x10] (dead store, never read), restores self.
4. Block 2: loads a3_home=[rbp+0x90] (home space for r9), a1_low_byte = low byte of a1. Builds a 6-dword rect at [rbp-8]: {a1->f0>>4, 0, a1->f8>>4, a2->f0>>4, 0, a2->f8>>4}. Computes width=(a2->f0-a1->f0)>>4+1, height=(a2->f8-a1->f8)>>4+1, total=width*height. Calls sub_2fd3e60(self, &rect, saved_a3_low, a1_low_byte, &output_buffer, a3_home) at 0x2fd42f7 (direct call, callee not classified - signature unknown).
5. Block 3: loads rcx_val = a2_home->f38 ([a2+0x38]). If non-zero: computes ne=(rcx_val != a2_home), calls sub_eea6040(rcx_val, ne) via data slot 0xF99FFA0, result in rax is the return value. If zero: return value = a2_home.
6. Epilogue: restores stack and registers, returns.

Calls:
- sub_eea6040 via data slot 0xF99FFA0 (classified boundary, vendor) at 0x2fd425e and 0x2fd431a.
- sub_2fd3e60 direct at 0x2fd42f7 (NOT in lift set, NOT classified boundary - callee signature unknown).

Return value: sub_eea6040 result if a2->f38 != 0, otherwise a2 (the r8 parameter).

CLOSES? YES
