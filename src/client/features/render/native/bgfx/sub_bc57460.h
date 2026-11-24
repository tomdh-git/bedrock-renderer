#pragma once
#include <cstdint>

namespace native::bgfx {

// Forward declaration for the chunk c00 state
struct Sub_bc57460_ChunkC00State;

// Main entry point - frame graph builder (VV)
// Signature: void sub_bc57460(void* ctx, void* rdx, void* r8, void* r9, void* a4, void* a5, void* a6, void* a7)
// x64 MSVC ABI: this/ctx in rcx, args in rdx/r8/r9 + 4 stack args
// Chunked into 3 parts: c00 (0xbc57460..0xbc58a85), c01 (0xbc58a85..0xbc5a261), c02 (0xbc5a261..0xbc5a28f)
extern "C" void sub_bc57460(void* ctx, void* rdx, void* r8, void* r9, void* a4, void* a5, void* a6, void* a7);

// Chunk c00 step function (prologue + main loop)
void sub_bc57460_chunk_c00_step(Sub_bc57460_ChunkC00State* state);

} // namespace native::bgfx