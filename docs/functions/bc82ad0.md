# sub_bc82ad0

- RVA: 0xbc82ad0, size 0x3a0f, end 0xbc864df
- name: VV frame-graph builder (per orchestrator row)
- frame: sub rsp,0x938; rbp = rsp+0x80; saved xmm6-xmm15 at [rbp+0x810..0x8a0]; saved gprs rbp,r15,r14,r13,r12,rsi,rdi,rbx
- args: rcx -> [rbp+0x670]; rdx -> [rbp+0x760]; r8 -> [rbp+0x768]; r9 -> r14
- locals: various [rbp+...] slots
- chunking: see docs/data/native_chunks/bc82ad0.tsv (4 chunks, <=0x1800, BB boundaries)

## Chunk plan
Chunk boundaries are basic-block starts from rdis cfg; no gaps/overlaps; covers [0xbc82ad0,0xbc864df).

## OPEN QUESTIONS
- full analysis pending; no source written in this PLAN item.

## Chunk c03 (0xbc864bb..0xbc864df) Reversed source (complete)

### Chunk state
Struct `ChunkState_bc82ad0_c03` (defined in `src/client/features/render/native/bgfx/sub_bc82ad0_chunk_c03.h`):
- `rbp`: frame base pointer
- `rdx`: value in RDX register at chunk entry (to be stored at data_12ae1ac0)
- `rbx`, `rsi`, `rdi`, `r12`, `r13`, `r14`, `r15`: callee-saved GPRs (preserved for tail jump)
- xmm6-xmm15 accessed via rbp+0x810..0x8A0

### Instruction-by-instruction lift

// 0xbc864bb..0xbc864c2
*reinterpret_cast<uint64_t*>(0x12AE1AC0) = s.rdx;
// 0xbc864bb  mov [0x12AE1AC0],rdx                          ; [data_12ae1ac0]
// Stores current RDX register value to global data_12ae1ac0

// 0xbc864c2..0xbc864ce
native::boundary::sub_73150(rbp + 0x770);
// 0xbc864c2  lea rcx,[rbp+0x770]
// 0xbc864c9  call 0x73150                                  ; -> sub_73150
// Calls boundary function sub_73150 (stl) with pointer to local at [rbp+0x770]

// 0xbc864ce..0xbc864da
native::boundary::sub_e938d70(reinterpret_cast<void*>(0x12AE1AC8));
// 0xbc864ce  lea rcx,[0x12AE1AC8]
// 0xbc864d5  call 0xE938D70                                ; -> sub_e938d70
// Calls boundary function sub_e938d70 (os) with address of global data_12ae1ac8

// 0xbc864da..0xbc864df
native::sub_bc83aee(s.rbp);
// 0xbc864da  jmp 0xBC83AEE                                 ; -> sub_bc83aee
// 0xbc864df  nop
// Tail jump to lifted function sub_bc83aee (chunk c00, RVA 0xbc83aee), passing frame pointer

### Callees in this chunk
| RVA | Symbol | Class | Via |
|-----|--------|-------|-----|
| 0x73150 | sub_73150 | boundary (stl) | native::boundary::sub_73150 |
| 0xe938d70 | sub_e938d70 | boundary (os) | native::boundary::sub_e938d70 |
| 0xbc83aee | sub_bc83aee | lift (same function, chunk c00) | native::sub_bc83aee |

### Data references
| RVA | Description |
|-----|-------------|
| 0x12AE1AC0 | data_12ae1ac0 (qword) |
| 0x12AE1AC8 | data_12ae1ac8 (qword) |

### Frame locals accessed
| Offset | Size | Use |
|--------|------|-----|
| 0x770 | 8 | local buffer/string pointer - passed to sub_73150 |

### Verbatim call quotes (for liftcheck)
0xbc864c9  call 0x73150
0xbc864d5  call 0xE938D70