# sub_e824fbe (range 0xe824fbe..0xe82d4e3)

Part of sub_e821120. Range size 0x8525. Chunked into 7 basic-block-aligned chunks (see docs/data/native_chunks/e824fbe.tsv).

## Function-wide facts
- Container function: sub_e821120 [0xe821120..0xe82d4e3), size 0xc3c3.
- Target range: [0xe824fbe, 0xe82d4e3), size 0x8525.
- Frame/saved regs/locals/arg map: not determined in this PLAN item.

## Chunk state
Chunk c02 state struct: ChunkState_e824fbe_c02 { rbx, rbp, rcx, rsi, rdi, rax, rdx } (see sub_e824fbe_chunk_c02.h). Live registers at chunk entry 0xe827fa3.
## Chunk state
Chunk c04 state struct: ChunkState_e824fbe_c04 { rbx, rbp, rcx, rsi, rdi, rax, rdx, r10, r13, r14 } (see sub_e824fbe_chunk_c04.h). Live registers at chunk entry 0xe82af92.

## Chunk state
Chunk c01 (0xe8267b7..0xe827fa3) live state passed as struct ChunkState_e824fbe_c01: rbx_base, r10_scratch, r13_scratch, r14_scratch (rbp-frame).

## Reversed source (complete)
Chunk 0xe824fbe..0xe8267b7 (part 1/7). See src/client/features/render/native/d3d12/sub_e824fbe.cpp. First instruction 0xe824fbe mov eax,[rbx+0x150]; last instruction 0xe8267b7 (within range).

## Chunk state
Chunk c05 (0xe82c765..0xe82d4c4) live state passed as struct ChunkState_e824fbe_c05: rbx, rbp, rcx, rsi, rdi, rax, rdx, r10 (rbp-frame).

## Chunk state
Chunk c06 (0xe82d4c4..0xe82d4e3) live state passed as struct ChunkState_e824fbe_c06: rbx, rbp, rcx, rsi, rdi, rax, rdx (rbp-frame).