#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Lift callee of sub_0xe8142c0. sub_0xEBCE390 is `jmp 0xEEC6EC0`; sub_0xEEC6EC0 is
// `jmp qword ptr [0xF9A8A98]` (an import thunk). Called at both sites of 0xe8142c0 as
// (rcx=dst, rdx=src, r8=size): a memcpy-style bulk copy. It is classified `lift` in
// docs/data/native_boundary.tsv (line 509) and docs/data/native_functions.tsv (line 1622,
// root D0); it is forward-declared here and called through its native symbol, and is lifted
// by its own unit. ABI matches the observed register use at the call sites.
void sub_ebce390(void* dst, const void* src, std::uint32_t size);

} // namespace native

namespace native::d3d12 {

// LIFT 0xe8142c0 size 0xd6 1.26.62.01 createProgram (shader pointers, merged predefined uniforms)
//
// this = RendererContextD3D12* (rcx). Indexes are 16-bit (rdx, r8w, r9w).
// Two tables live inside `this`:
//   shader table:  base this+0xAAA178, stride 0xB8  (arg2 and arg3 index it)
//   program table: base this+0xB62178, stride 0xF8  (arg1 indexes it)
// A program record (0xF8 bytes at this+0xB62178 + a1*0xF8) gets:
//   +0x00 : pointer to shader[a2]          (this+0xAAA178 + a2*0xB8)
//   +0x08 : pointer to shader[a3]          (this+0xAAA178 + a3*0xB8), only when a3 != 0xFFFF
//   +0x10 : merged uniform blob = shader[a2] data ++ shader[a3] data (bulk copies)
//   +0xF0 : byte count = shader[a2].count + shader[a3].count (mod 256)
// where shader[i].data is at this+0xAAA188 + i*0xB8, and shader[i].count is the byte at
// this+0xAAA228 + i*0xB8; each bulk copy length is count*8.
constexpr std::size_t kShaderStride    = 0xB8;
constexpr std::size_t kProgramStride   = 0xF8;
constexpr std::size_t kShaderArrayOff  = 0xAAA178; // shader table base, relative to this
constexpr std::size_t kShaderDataOff   = 0xAAA188; // shader[i] data field (= base + 0x10)
constexpr std::size_t kShaderCountOff  = 0xAAA228; // shader[i] count byte (= base + 0xB0)
constexpr std::size_t kProgramArrayOff = 0xB62178; // program table base, relative to this
constexpr std::size_t kProgramDataOff  = 0xB62188; // program record +0x10 (= base + 0x10)
constexpr std::size_t kProgramCountOff = 0xB62268; // program record +0xF0 (= base + 0xF0)
constexpr std::size_t kProgShaderAPtr  = 0x00;     // program record field: shader[a2] ptr
constexpr std::size_t kProgShaderBPtr  = 0x08;     // program record field: shader[a3] ptr
constexpr std::size_t kProgDataField   = 0x10;     // program record field: merged blob
constexpr std::size_t kProgCountField  = 0xF0;     // program record field: count byte
constexpr std::size_t kShaderFieldData = 0x10;     // shader record data field
constexpr std::size_t kShaderFieldCnt  = 0xB0;     // shader record count-byte field
constexpr unsigned short kNoShader     = 0xFFFF;   // arg3 sentinel: skip second shader

static_assert(kShaderDataOff  == kShaderArrayOff + kShaderFieldData, "shader data off");
static_assert(kShaderCountOff == kShaderArrayOff + kShaderFieldCnt,  "shader count off");
static_assert(kProgramDataOff  == kProgramArrayOff + kProgDataField, "program data off");
static_assert(kProgramCountOff == kProgramArrayOff + kProgCountField, "program count off");

// sub_0xe8142c0: register a program record from two shader records, merging their
// predefined uniform blobs. rcx=this, edx=a1 (program index), r8w=a2 (shader A index),
// r9w=a3 (shader B index; 0xFFFF = none). Returns void.
void sub_e8142c0(void* a0, unsigned short a1, unsigned short a2, unsigned int a3);

} // namespace native::d3d12