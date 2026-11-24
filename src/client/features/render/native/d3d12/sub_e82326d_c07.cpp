// LIFT 0xe82326d size 0xa276 1.26.62.01 sub_e82326d
// CHUNK 0xe82d4be..0xe82d4e3

// chunk state documented in docs/functions/e82326d.md section 'Chunk state'
struct ChunkState_e82326d_c07 {
    void* rbx_base;     // rbx = this (draw executor object), live across chunks (unused in this cold path)
};

// Forward declarations for lift-set callees
extern "C" void sub_eec59e0();

// Boundary: indirect call through data slot 0xF9A8C78
using data_slot_f9a8c78_fn = void(*)();
extern "C" void* data_slot_f9a8c78;  // resolves to data_f9a8c78 at runtime

static inline void sub_e82326d_chunk_c07(ChunkState_e82326d_c07& s) {
    // 0xe82d4be..0xe82d4e3: Cold path / debug trap sequence
    (void)s;

    // 0xe82d4be..0xe82d4c3
    // 0xe82d4be  call 0xEEC59E0
    sub_eec59e0();

    // 0xe82d4c3..0xe82d4c4
    // 0xe82d4c3  nop

    // 0xe82d4c4..0xe82d4cd
    // 0xe82d4c4  mov qword ptr [rsp+0x20],0
    // (stack slot write, no state tracking needed)

    // 0xe82d4cd..0xe82d4d7: Zero argument registers for indirect call
    // 0xe82d4cd  xor ecx,ecx
    // 0xe82d4cf  xor edx,edx
    // 0xe82d4d1  xor r8d,r8d
    // 0xe82d4d4  xor r9d,r9d

    // 0xe82d4d7..0xe82d4dd
    // 0xe82d4d7  call qword ptr [0xF9A8C78]
    reinterpret_cast<data_slot_f9a8c78_fn>(data_slot_f9a8c78)();

    // 0xe82d4dd..0xe82d4e2
    // 0xe82d4dd  call 0xEEC59E0
    sub_eec59e0();

    // 0xe82d4e2..0xe82d4e3
    // 0xe82d4e2  int3
    // 0xe82d4e3  nop [rax+rax]
    __debugbreak();
}

// Verbatim call quotes for the chunk range (plain lines, two spaces after the address).
#if 0
0xe82d4be  call 0xEEC59E0
0xe82d4d7  call qword ptr [0xF9A8C78]
0xe82d4dd  call 0xEEC59E0
#endif