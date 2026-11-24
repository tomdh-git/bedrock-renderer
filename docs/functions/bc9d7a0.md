# bc9d7a0 — VV frame-graph builder (chunk c00)

## Chunk state

`ChunkState_bc9d7a0_c00` (defined in `src/client/features/render/native/bgfx/sub_bc9d7a0_chunk_c00.cpp`):
- `rax`, `rcx`, `rdx`, `r8`, `r9`, `r10`, `r11` (uint64_t)
- `rbx`, `rsi`, `rdi`, `r12`, `r13`, `r14`, `r15`, `rbp` (void*)
- `stack[0x1098]` (uint8_t)

## Reversed source (complete)

```cpp
// 0xbc9d7a0..0xbc9e11a
// (entry chunk; prologue spills regs, 23 global-guard checks, first switch dispatch, BilateralGrid/LocalExposure node build, grid allocation, shared_ptr acquire, ClearBilateralGrid node construction, first alloc 0xC0)
```

## Reversed source (chunk c02)

```cpp
// 0xbc9f890..0xbca1080
// (frame graph builder continued: second pass setup, string handling, object allocation via vendor thunks, vector growth, frame graph node linking, refcount management, grid dimension computation, multiple 5679DB0 searches, final parameter block setup, call to BC9C990, cleanup)
```
