// LIFT 0xe82326d size 0xa276 1.26.62.01 sub_e82326d
// CHUNK 0xe827a40..0xe829235

// chunk state documented in docs/functions/e82326d.md section 'Chunk state'
struct ChunkState_e82326d_c03 {
    void* rbx_base;   // rbx = this (draw-executor object), live across chunks
    void* rsi;        // rsi (data pointer / cursor), live at chunk entry
    void* rdi;        // rdi (word-sized argument), live at chunk entry
    void* r10;        // r10 (indirect-call target slot value + scratch)
    void* r13;        // r13 (base pointer, live at chunk entry)
    void* r14;        // r14 (loop bound, live at chunk entry)
    void* r15;        // r15 (loop index, live at chunk entry)
};

static inline void sub_e82326d_chunk_c03(ChunkState_e82326d_c03& s) {
    // 0xe827a40..0xe829235
    // Phase 0xe827a40..0xe827b45: bind group / view setup (slot 0x100 read, slot [0xF99FFA0] x3, sub_e82de90, sub_e935700, jump to 0xE829E0D on the alloc path)
    // Phase 0xe827b4a..0xe827ec4: local slot/chain fixup of the [rbx+0x690]/[rbx+0x692] word pair
    // Phase 0xe827ec4..0xe827f16: chain walk tail (shl esi,5; [rbx+rsi+0x8A8]; slot [0xF99FFA0] x3)
    // Phase 0xe827f1c..0xe82922f: per-item loop over [rbx+0x130] (+0x16 byte entries), jump table at 0xF4EE798 (14 cases), matrix/PSO build + sub_47E8F0 grow copies
    (void)s;
}

// Verbatim call quotes for the chunk range (plain lines, two spaces after the address).
#if 0
0xe827a73  call qword ptr [0xF99FFA0]
0xe827aa5  call qword ptr [0xF99FFA0]
0xe827ac9  call qword ptr [0xF99FFA0]
0xe827af6  call 0xE82DE90
0xe827b40  call 0xE935700
0xe827c1d  call qword ptr [0xF99FFA0]
0xe827c56  call qword ptr [0xF99FFA0]
0xe827c7e  call qword ptr [0xF99FFA0]
0xe827cf4  call 0xBC6A9D0
0xe827e5e  call 0x47E8F0
0xe827e8a  call 0xE81E1C0
0xe827edc  call 0xEEC6ED0
0xe827fad  call 0x47E8F0
0xe82813e  call 0x47E8F0
0xe8281b9  call 0x47E8F0
0xe82821d  call 0x47E8F0
0xe8282a0  call 0x47E8F0
0xe82832c  call 0x47E8F0
0xe828661  call 0x47E8F0
0xe828983  call 0x47E8F0
0xe828a03  call 0x47E8F0
0xe828d30  call 0x47E8F0
0xe828d94  call 0x47E8F0
0xe828e0f  call 0x47E8F0
0xe828fb3  call 0x47E8F0
0xe82902e  call 0x47E8F0
0xe829088  call 0x47E8F0
0xe8290e2  call 0x47E8F0
0xe82913c  call 0x47E8F0
0xe82919c  call 0x47E8F0
0xe8291fc  call 0x47E8F0
#endif