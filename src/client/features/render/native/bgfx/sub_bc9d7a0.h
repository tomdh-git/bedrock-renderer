#pragma once
// LIFT 0xbc9d7a0 size 0x67db 1.26.62.01 VV frame-graph builder
// chunk 1/5 state (entry chunk 0xbc9d7a0..0xbc9e11a) documented in docs/functions/bc9d7a0.md 'Chunk state'
struct Bc9d7a0ChunkState1 {
    uint64_t rax, rcx, rdx, r8, r9, r10, r11;
    void* rbx;
    void* rsi;
    void* rdi;
    void* r12;
    void* r13;
    void* r14;
    void* r15;
    void* rbp;
    uint8_t stack[0x1098];
};

// chunk 2/5 state (0xbc9e11a..0xbc9f890) live-in from chunk 1 live-out at 0xbc9e11a
struct Bc9d7a0ChunkState2 {
    // Live-in registers from chunk 1 at 0xbc9e11a
    void* r12;        // [rbp+0x1298] equivalent
    void* r13;        // [rbp+0xA18] equivalent
    void* rax;        // [rbp+0x3A0] equivalent
    void* rcx;        // [rbp+0x90] equivalent
    void* rdi;        // additional live-in
    // Stack slots live-in from chunk 1
    // [rbp+0x90], [rbp+0x3A0], [rbp+0xA18], [rbp+0x1298] are already captured in registers above
    // The full stack frame is available via the parent function's stack
    uint8_t stack[0x1098];  // Full stack frame for slot access
};

// chunk 3/5 state (0xbc9f890..0xbca1080) live-in from chunk 2 live-out at 0xbc9f890
struct Bc9d7a0ChunkState3 {
    void* r13;
    void* rax;
    void* rcx;
    void* rdx;
    uint8_t stack[0x1098];
};

// chunk 4/5 state documented in docs/functions/bc9d7a0.md 'Chunk state'
struct Bc9d7a0ChunkState4 {};
static inline void bc9d7a0_chunk_4(Bc9d7a0ChunkState4& s) {}

// Chunk entry points
static inline void bc9d7a0_chunk_1(Bc9d7a0ChunkState1& s);
static inline void bc9d7a0_chunk_2(Bc9d7a0ChunkState2& s);
static inline void bc9d7a0_chunk_3(Bc9d7a0ChunkState3& s);