# sub_bc8eb90

- RVA: 0xbc8eb90
- Size: 0x5ba7 (end 0xbc94737)
- Name: VV frame-graph builder

## Function-wide facts

- Prologue: push rbp, r15, r14, r13, r12, rsi, rdi, rbx; sub rsp, 0x4B8; lea rbp,[rsp+0x80]; saves xmm7 at [rbp+0x420], xmm6 at [rbp+0x410]; [rbp+0x408]=0xFFFFFFFFFFFFFFFE.
- Frame size (rsp decrement): 0x4B8.
- Saved registers: rbp, r15, r14, r13, r12, rsi, rdi, rbx, xmm6, xmm7.
- Argument map (x64 MSVC ABI): rcx -> r12 (arg0), rdx -> rsi (arg1), r8 -> rbx (arg2), r9 -> rdi (arg3).
- Local slots: [rbp+0x400] holds r12 (arg0).
- Jump table at 0xf44b4b0 (switch on eax in [0..9]).
- Chunk boundaries: docs/data/native_chunks/bc8eb90.tsv.

## Chunks

See docs/data/native_chunks/bc8eb90.tsv.