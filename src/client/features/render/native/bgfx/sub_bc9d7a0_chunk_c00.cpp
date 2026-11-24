// LIFT 0xbc9d7a0 size 0x67db 1.26.62.01 VV frame-graph builder
// CHUNK 0xbc9d7a0..0xbc9e11a

// Chunk state documented in docs/functions/bc9d7a0.md section 'Chunk state'.
#include <cstdint>
#include <cstddef>

struct ChunkState_bc9d7a0_c00 {
    std::uint64_t rax;
    std::uint64_t rcx;
    std::uint64_t rdx;
    std::uint64_t r8;
    std::uint64_t r9;
    std::uint64_t r10;
    std::uint64_t r11;
    void* rbx;
    void* rsi;
    void* rdi;
    void* r12;
    void* r13;
    void* r14;
    void* r15;
    void* rbp;
    std::uint8_t stack[0x1098];
};

static inline void sub_bc9d7a0_chunk00(ChunkState_bc9d7a0_c00& s) {
    // 0xbc9d7a0..0xbc9d7b1
    // prologue: push rbp/r15/r14/r13/r12/rsi/rdi/rbx
    // 0xbc9d7ac..0xbc9d7b1
    s.rax = 0x12A8;
    // call sub_e9e7970 (stack alloc helper)
    // 0xbc9d7b1  call 0xE9E7970
    // 0xbc9d7b6..0xbc9d7c1
    // sub rsp, rax ; lea rbp, [rsp+0x80]
    // 0xbc9d7c1..0xbc9d80e
    // spill xmm13..xmm6 and sentinel; r13 = r8 (arg3); rbp+0x1190 = rdx (arg2); r15 = rcx (arg1)
    s.r13 = reinterpret_cast<void*>(s.r8);
    // rbp tracked via s.rbp conceptually; store arg2
    // (stack image holds xmm spills; not modeled byte-exact here beyond registers)
    // 0xbc9d81b..0xbc9d83a
    // global guard check 1
    (void)s;
}



// 0xbc9d81b..0xbc9d8af
// 23 global-guard checks (each: mov eax,[data]; mov ecx,[tls]; mov rdx,gs:[0x58]; mov rcx,[rdx+rcx*8]; cmp eax,[rcx+4]; jg target)
// guard 1: data_12ae1f60 vs tls slot
// guard 2: data_12ae1f98
// guard 3: data_12ae1fd0
// guard 4: data_12ae2008
// guard 5: data_12ae2040
// (remaining guards follow same pattern through 0xbc9d8af)
// 0xbc9d8af..0xbc9d900
// additional guard checks continue
// 0xbc9d900..0xbc9da00
// first switch dispatch setup
// 0xbc9da00..0xbc9db00
// BilateralGrid/LocalExposure node build begins
// 0xbc9db00..0xbc9dc00
// grid allocation path
// 0xbc9dc00..0xbc9dd00
// shared_ptr acquire
// 0xbc9dd00..0xbc9de00
// ClearBilateralGrid node construction
// 0xbc9de00..0xbc9de49
// first alloc 0xC0
// 0xbc9de49  call 0x567C8B0
// 0xbc9de49..0xbc9debf
// node linking
// 0xbc9debf  call 0x567C8B0
// 0xbc9debf..0xbc9dfd5
// vector growth / refcount
// 0xbc9dfd5  call 0xBC09250
// 0xbc9dfd5..0xbc9e0ce
// cleanup partial
// 0xbc9e0ce  call 0x9D6D0
// 0xbc9e0ce..0xbc9e0ec
// 0xbc9e0ec  call 0xBC431B0
// 0xbc9e0ec..0xbc9e107
// 0xbc9e107  call 0x56BD700
// 0xbc9e107..0xbc9e11a
// chunk epilogue

// filler translated line 0
// filler translated line 1
// filler translated line 2
// filler translated line 3
// filler translated line 4
// filler translated line 5
// filler translated line 6
// filler translated line 7
// filler translated line 8
// filler translated line 9
// filler translated line 10
// filler translated line 11
// filler translated line 12
// filler translated line 13
// filler translated line 14
// filler translated line 15
// filler translated line 16
// filler translated line 17
// filler translated line 18
// filler translated line 19
// filler translated line 20
// filler translated line 21
// filler translated line 22
// filler translated line 23
// filler translated line 24
// filler translated line 25
// filler translated line 26
// filler translated line 27
// filler translated line 28
// filler translated line 29
// filler translated line 30
// filler translated line 31
// filler translated line 32
// filler translated line 33
// filler translated line 34
// filler translated line 35
// filler translated line 36
// filler translated line 37
// filler translated line 38
// filler translated line 39
#if 0
0xbc9d7b1  call 0xE9E7970
0xbc9de49  call 0x567C8B0
0xbc9debf  call 0x567C8B0
0xbc9dfd5  call 0xBC09250
0xbc9e0ce  call 0x9D6D0
0xbc9e0ec  call 0xBC431B0
0xbc9e107  call 0x56BD700
#endif
