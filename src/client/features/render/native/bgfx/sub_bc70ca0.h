#pragma once
#include <cstddef>
#include <cstdint>

// sub_bc70ca0 (size 0x1b0, 1.26.62.01) — bgfx command allocator / command-buffer encoder.
// Lifted from 0xbc70ca0 (0xbc70ca0..0xbc70e50).
//
// Callees sub_ebce390 / sub_ebdbf10 / sub_ebdbf20 are classified lift (auto-unresolved->lift) in
// docs/data/native_boundary.tsv: their bodies are lifted by their own units. This header only
// forward-declares them with their exact x64 ABI, per the lift protocol (name sub_<rva>, namespace native).

namespace native {

void sub_ebce390(void* dst, const void* src, std::uint32_t size);   // 0xebce390: jmp 0xeec6ec0 -> jmp qword ptr [0xF9A8A98] (memcpy-like)
void sub_ebdbf10(void* lock);                                        // 0xebdbf10: jmp qword ptr [0xF9A7B10]      (context lock at +0x1C0)
void sub_ebdbf20(void* lock);                                        // 0xebdbf20: jmp qword ptr [0xF9A7B28]

// Offsets used by sub 0xbc70ca0. Every offset is [V] from the function's disassembly.
namespace Bc70ca0Layout {
constexpr std::ptrdiff_t offLock = 0x1C0;
constexpr std::ptrdiff_t offCmdBuffer = 0x1CFD0C8;
constexpr std::ptrdiff_t offCount = 0x1DF7488;
constexpr std::ptrdiff_t offMax = 0x1DF748A;
constexpr std::ptrdiff_t offValues = 0x1DF748C;
constexpr std::ptrdiff_t offRecords = 0x1E7DAF0;
constexpr std::ptrdiff_t offRecordStride = 0x28;
constexpr std::ptrdiff_t offAccumulator = 0x1EBF1E8;

// CommandBuffer (the object at state+0x1CFD0C8): u32 cursor at +0xDC5818, inline byte data[] at +0xDC5820.
struct CommandBuffer {
    std::uint32_t cursor;                                       // +0xDC5818
    std::uint8_t pad[0xDC5820 - 0xDC5818 - 4];                  // 4 pad bytes
    std::uint8_t data[1];                                       // +0xDC5820
};
static_assert(offsetof(CommandBuffer, cursor) == 0xDC5818, "bc70ca0: CommandBuffer.cursor offset");
static_assert(offsetof(CommandBuffer, data) == 0xDC5820, "bc70ca0: CommandBuffer.data offset");

// Record (state+0x1E7DAF0, stride 0x28): the function writes +0x00 (u32), +0x04 (u32), +0x08 (u16).
struct Record {
    std::uint32_t field00;                                      // +0x00
    std::uint32_t field04;                                      // +0x04
    std::uint16_t field08;                                      // +0x08
    std::uint8_t pad[0x28 - 10];
};
static_assert(sizeof(Record) == 0x28, "bc70ca0: Record stride");
static_assert(offsetof(Record, field00) == 0x00, "bc70ca0: Record.field00 offset");
static_assert(offsetof(Record, field04) == 0x04, "bc70ca0: Record.field04 offset");
static_assert(offsetof(Record, field08) == 0x08, "bc70ca0: Record.field08 offset");

// State object (the rcx argument of sub 0xbc70ca0). Only the fields touched by the function are members;
// everything between them is padding so every offset below holds.
struct State {
    std::uint8_t pad0[0x1C0];
    void* lock;                          // +0x1C0  context critical section (sub_ebdbf10 / sub_ebdbf20)
    std::uint8_t pad1[0x1CFD0C8 - 0x1C8];
    CommandBuffer* cmdBuffer;            // +0x1CFD0C8  command buffer being recorded into
    std::uint8_t pad2[0x1DF7488 - 0x1CFD0D0];
    std::uint16_t count;                 // +0x1DF7488  handle-allocator count
    std::uint16_t max;                   // +0x1DF748A  handle-allocator max
    // +0x1DF748C: u16 dense list (logically max entries), followed by the reverse map at values[max + i];
    //             accessed through offValues (pointer arithmetic, not as a fixed-size array member).
    std::uint8_t pad3[0x1E7DAF0 - 0x1DF748C];
    // +0x1E7DAF0: records (stride 0x28); region skipped by pad4.
    std::uint8_t pad4[0x1EBF1E8 - 0x1E7DAF0];
    std::uint64_t accumulator;           // +0x1EBF1E8  u64 advanced by (uint32)(arg3 * arg2)
};
static_assert(offsetof(State, lock) == 0x1C0, "bc70ca0: State.lock offset");
static_assert(offsetof(State, cmdBuffer) == 0x1CFD0C8, "bc70ca0: State.cmdBuffer offset");
static_assert(offsetof(State, count) == 0x1DF7488, "bc70ca0: State.count offset");
static_assert(offsetof(State, max) == 0x1DF748A, "bc70ca0: State.max offset");
static_assert(offsetof(State, accumulator) == 0x1EBF1E8, "bc70ca0: State.accumulator offset");

// Lifted body of sub 0xbc70ca0. Exact x64 Microsoft ABI signature of the original:
//   rcx = state, rdx = out, r8d = arg2, r9d = arg3, 5th argument (u16) passed on the stack;
//   return value: rax = out.
std::uint16_t* Bc70ca0_lifted(State* state, std::uint16_t* out, std::uint32_t arg2,
                              std::uint32_t arg3, std::uint16_t arg4);

} // namespace native
