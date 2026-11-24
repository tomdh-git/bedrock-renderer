#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

// LIFT 0xe81e1c0 size 0x69c 1.26.62.01 commit(UniformBuffer) constant-buffer commit
//
// RendererContextD3D12::commit(UniformBuffer&) in Mojang's form: walks one shader's
// uniform command stream and copies each uniform's value into that shader's constant
// scratch buffer (a growable byte vector), returning whether anything was written.
// Called twice per draw from the executor (vertex stage, then fragment stage).

namespace native::d3d12 {

// UniformCursor as seen by the function: data base at +0x00, read cursor (u32) at +0x0C.
struct E81e1c0Cursor {
    void*   data;          // +0x00  base of the command stream buffer (read at 0xe81e213)
    std::uint8_t pad_0x08[4]; // +0x08
    std::uint32_t pos;     // +0x0C  read cursor, set to 4 on entry (0xe81e21f)
};
static_assert(offsetof(E81e1c0Cursor, data) == 0x00, "sub_e81e1c0: cursor data at +0x00");
static_assert(offsetof(E81e1c0Cursor, pos) == 0x0C, "sub_e81e1c0: cursor pos at +0x0C");

// UniformBuffer is the object pointed to by cursor->data; its command bytes start at +0x08.
// (modelled only through the cursor indirection; no separate struct needed.)

} // namespace native::d3d12

// Uniform type size table at RVA 0xF441930: {4, 0, 16, 36, 64} (int32, indexed by type) [V].
static constexpr std::int32_t kE81e1c0SizeTable[5] = { 4, 0, 16, 36, 64 };

// Jump table base RVA 0xF4EE720 (21 int32 entries) [V].
static constexpr std::uintptr_t kE81e1c0JumpTableRva = 0xF4EE720u;

// m_uniforms array base offset inside RendererContextD3D12 [V: 0xe81e4ba rcx+rax*8+0x1250].
static constexpr std::size_t kE81e1c0Uniforms = 0x1250;

// std::vector<uint8_t> layout: begin +0, end +8, cap +0x10 [V].
static constexpr std::size_t kVecBegin = 0x00;
static constexpr std::size_t kVecEnd   = 0x08;
static constexpr std::size_t kVecCap   = 0x10;

static_assert(sizeof(void*) == 8, "sub_e81e1c0: x64 target");
static_assert(kE81e1c0Uniforms == 0x1250, "sub_e81e1c0: uniforms offset");

// Exact x64 Microsoft ABI signature.
extern "C" bool sub_e81e1c0(void* ctx, native::d3d12::E81e1c0Cursor* cur,
                            std::vector<std::uint8_t>** dst,
                            const std::vector<std::uint16_t>* shaderUniforms,
                            bool fragment);