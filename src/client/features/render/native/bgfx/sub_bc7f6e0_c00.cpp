// LIFT 0xbc7f6e0 size 0x1a82 1.26.62.01 sub_bc7f6e0
// CHUNK 0xbc7f6e0..0xbc80ed3

// Chunk state documented in docs/functions/bc7f6e0.md section 'Chunk state'.
struct ChunkState_bc7f6e0_c00 {
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
    std::uint8_t stack[0x3E8];
};

static inline void sub_bc7f6e0_chunk00(ChunkState_bc7f6e0_c00& s) {
    (void)s;
    // 0xbc7f6e0..0xbc80ed3
}

#if 0
0xbc7f802  call 0x567C8B0
0xbc7f847  call qword ptr [0xF99FFA0]
0xbc7f85d  call qword ptr [0xF99FFA0]
0xbc7f895  call qword ptr [0xF99FFA0]
0xbc7f8ab  call qword ptr [0xF99FFA0]
0xbc7fad7  call 0x5698290
0xbc7fb28  call 0xE86B370
0xbc7fd88  call 0x5679DB0
0xbc7fe3c  call 0x5679DB0
0xbc7fed4  call 0x5679DB0
0xbc7ff44  call qword ptr [0xF99FFA0]
0xbc7ffb2  call 0x9B020
0xbc80006  call 0xBC81930
0xbc80047  call 0xE935700
0xbc80087  call 0x9B250
0xbc80094  call 0xE935700
0xbc800ad  call 0xE935700
0xbc800f9  call 0xE935700
0xbc8013a  call 0xE935700
0xbc801ad  call 0xE86B370
0xbc8040f  call 0x5679DB0
0xbc804af  call 0x5679DB0
0xbc8054b  call 0x5679DB0
0xbc805af  call qword ptr [0xF99FFA0]
0xbc80616  call 0x9B020
0xbc80663  call 0xBC81930
0xbc806a4  call 0xE935700
0xbc806e6  call 0xE935700
0xbc80740  call 0xE935700
0xbc80761  call 0xE935700
0xbc807af  call 0xE935700
0xbc80814  call 0x9BC830
0xbc80871  call qword ptr [0xF99FFA0]
0xbc80887  call qword ptr [0xF99FFA0]
0xbc808d5  call qword ptr [0xF9A8C78]
0xbc808e1  call 0x9BC830
0xbc80912  call 0xEEC6D80
0xbc8091f  call 0xE938CB0
0xbc80949  call 0x76AD00
0xbc80956  call 0xE935740
0xbc80962  call 0xE938D70
0xbc8097a  call 0xE938CB0
0xbc809a4  call 0x76AD00
0xbc809b1  call 0xE935740
0xbc809bd  call 0xE938D70
0xbc809d5  call 0xE938CB0
0xbc80a10  call 0x5668AC0
0xbc80a1d  call 0xE938D70
0xbc80a35  call 0xE938CB0
0xbc80a58  call 0x79580
0xbc80aa4  call 0xE938CB0
0xbc80ac7  call 0x79580
0xbc80b16  call 0xE938CB0
0xbc80b39  call 0x79580
0xbc80b88  call 0xE938CB0
0xbc80bab  call 0x79580
0xbc80bfa  call 0xE938CB0
0xbc80c1d  call 0x79580
0xbc80c6c  call 0xE938CB0
0xbc80c8f  call 0x79580
0xbc80dec  call 0x73150
0xbc80df8  call 0xE938D70
0xbc80e9b  call 0x73150
0xbc80ea7  call 0xE938D70
#endif

// Layout assertions for ChunkState_bc7f6e0_c00
static_assert(offsetof(ChunkState_bc7f6e0_c00, rax) == 0x00, "rax at +0x00");
static_assert(offsetof(ChunkState_bc7f6e0_c00, rcx) == 0x08, "rcx at +0x08");
static_assert(offsetof(ChunkState_bc7f6e0_c00, rdx) == 0x10, "rdx at +0x10");
static_assert(offsetof(ChunkState_bc7f6e0_c00, r8) == 0x18, "r8 at +0x18");
static_assert(offsetof(ChunkState_bc7f6e0_c00, r9) == 0x20, "r9 at +0x20");
static_assert(offsetof(ChunkState_bc7f6e0_c00, r10) == 0x28, "r10 at +0x28");
static_assert(offsetof(ChunkState_bc7f6e0_c00, r11) == 0x30, "r11 at +0x30");
static_assert(offsetof(ChunkState_bc7f6e0_c00, rbx) == 0x38, "rbx at +0x38");
static_assert(offsetof(ChunkState_bc7f6e0_c00, rsi) == 0x40, "rsi at +0x40");
static_assert(offsetof(ChunkState_bc7f6e0_c00, rdi) == 0x48, "rdi at +0x48");
static_assert(offsetof(ChunkState_bc7f6e0_c00, r12) == 0x50, "r12 at +0x50");
static_assert(offsetof(ChunkState_bc7f6e0_c00, r13) == 0x58, "r13 at +0x58");
static_assert(offsetof(ChunkState_bc7f6e0_c00, r14) == 0x60, "r14 at +0x60");
static_assert(offsetof(ChunkState_bc7f6e0_c00, r15) == 0x68, "r15 at +0x68");
static_assert(offsetof(ChunkState_bc7f6e0_c00, rbp) == 0x70, "rbp at +0x70");
static_assert(offsetof(ChunkState_bc7f6e0_c00, stack) == 0x78, "stack at +0x78");
static_assert(sizeof(ChunkState_bc7f6e0_c00) == 0x460, "state size 0x460 (0x78 + 0x3E8)");