#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

namespace native {

// Layout of std::vector<uint16_t> as used by the exe (MSVC STL: three pointers).
// [V] offsets from [0xbc6a9d0, 0xbc6abd0): [r10+0x00] first/_Myfirst read,
// [r10+0x08] last/_Mylast read and written, [r10+0x10] end/_Myend read.
struct Uniform16Vector {
    uint16_t* first;       // +0x00
    uint16_t* last;        // +0x08
    uint16_t* end_storage; // +0x10
};
static_assert(offsetof(Uniform16Vector, first) == 0x00, "rendererUpdateUniforms: vector first at +0x00");
static_assert(offsetof(Uniform16Vector, last) == 0x08, "rendererUpdateUniforms: vector last at +0x08");
static_assert(offsetof(Uniform16Vector, end_storage) == 0x10, "rendererUpdateUniforms: vector end_storage at +0x10");
static_assert(sizeof(Uniform16Vector) == 0x18, "rendererUpdateUniforms: vector size 0x18");

// Uniform buffer: { uint32_t size; uint32_t pos; } followed by uint8_t data[] at +0x08.
// [V] from [0xbc6a9d0]: rbx = ub + 0x08 is the data base (0xbc6aa0f add rbx,8); every
// uniform read is ub->data + pos, so data is at +0x08 and sizeof(UniformBuffer) == 0x08.
struct UniformBuffer {
    uint32_t size; // +0x00
    uint32_t pos;  // +0x04
};
static_assert(offsetof(UniformBuffer, size) == 0x00, "rendererUpdateUniforms: UniformBuffer size at +0x00");
static_assert(offsetof(UniformBuffer, pos) == 0x04, "rendererUpdateUniforms: UniformBuffer pos at +0x04");
static_assert(sizeof(UniformBuffer) == 0x08, "rendererUpdateUniforms: UniformBuffer data at +0x08");
static constexpr size_t kUniformBufferDataOffset = 0x08;
static_assert(kUniformBufferDataOffset == 0x08, "rendererUpdateUniforms: UniformBuffer::data at +0x08");

// Renderer interface (RendererContextI): vfptr at +0x00, virtual slots at +0x08 + index*8.
// [V] slots from [0xbc6a9d0]: [rax+0x170] slot 46 = updateUniform, [rax+0x178] slot 47 = setMarker.
struct RendererContextI {
    virtual void rendererVtblSlot00() = 0;
    virtual void rendererVtblSlot01() = 0;
    virtual void rendererVtblSlot02() = 0;
    virtual void rendererVtblSlot03() = 0;
    virtual void rendererVtblSlot04() = 0;
    virtual void rendererVtblSlot05() = 0;
    virtual void rendererVtblSlot06() = 0;
    virtual void rendererVtblSlot07() = 0;
    virtual void rendererVtblSlot08() = 0;
    virtual void rendererVtblSlot09() = 0;
    virtual void rendererVtblSlot10() = 0;
    virtual void rendererVtblSlot11() = 0;
    virtual void rendererVtblSlot12() = 0;
    virtual void rendererVtblSlot13() = 0;
    virtual void rendererVtblSlot14() = 0;
    virtual void rendererVtblSlot15() = 0;
    virtual void rendererVtblSlot16() = 0;
    virtual void rendererVtblSlot17() = 0;
    virtual void rendererVtblSlot18() = 0;
    virtual void rendererVtblSlot19() = 0;
    virtual void rendererVtblSlot20() = 0;
    virtual void rendererVtblSlot21() = 0;
    virtual void rendererVtblSlot22() = 0;
    virtual void rendererVtblSlot23() = 0;
    virtual void rendererVtblSlot24() = 0;
    virtual void rendererVtblSlot25() = 0;
    virtual void rendererVtblSlot26() = 0;
    virtual void rendererVtblSlot27() = 0;
    virtual void rendererVtblSlot28() = 0;
    virtual void rendererVtblSlot29() = 0;
    virtual void rendererVtblSlot30() = 0;
    virtual void rendererVtblSlot31() = 0;
    virtual void rendererVtblSlot32() = 0;
    virtual void rendererVtblSlot33() = 0;
    virtual void rendererVtblSlot34() = 0;
    virtual void rendererVtblSlot35() = 0;
    virtual void rendererVtblSlot36() = 0;
    virtual void rendererVtblSlot37() = 0;
    virtual void rendererVtblSlot38() = 0;
    virtual void rendererVtblSlot39() = 0;
    virtual void rendererVtblSlot40() = 0;
    virtual void rendererVtblSlot41() = 0;
    virtual void rendererVtblSlot42() = 0;
    virtual void rendererVtblSlot43() = 0;
    virtual void rendererVtblSlot44() = 0;
    virtual void rendererVtblSlot45() = 0;
    virtual void updateUniform(void* ctx, uint16_t handle, const void* data, uint32_t size) = 0; // slot 46 at +0x170
    virtual void setMarker(void* ctx, const void* data, uint32_t size) = 0;                     // slot 47 at +0x178
};
static_assert(46 * 8 == 0x170, "rendererUpdateUniforms: updateUniform vtable slot at +0x170");
static_assert(47 * 8 == 0x178, "rendererUpdateUniforms: setMarker vtable slot at +0x178");

// Read-only uniform type size table at RVA 0xF441930: {4, 0, 16, 36, 64} [V: bytes read from the exe,
// docs/progress/_readtable.py; index = op >> 27, valid for op <= 0x27FFFFFF].
static constexpr uint32_t kUniformTypeSize[5] = { 4u, 0u, 16u, 36u, 64u };
static constexpr uint32_t kUniformTypeCount = 5u;
static constexpr uint32_t kMaxUniformOp = 0x27FFFFFFu;

// Boundary callee (class stl, docs/data/native_boundary.tsv line 129): std::vector<uint16_t>::insert
// growth path for touched->insert(position, handle). Called with (vec, position, &value); return
// iterator is unused by the caller. Arguments arrive in rcx/rdx/r8 like a vector::insert thiscall.
void sub_74c9c0(Uniform16Vector* vec, uint16_t* position, const uint16_t* value);

} // namespace native

namespace native::bgfx {

// bgfx rendererUpdateUniforms, Minecraft Windows 1.26.62.01.
// [0xbc6a9d0, 0xbc6abd0), size 0x200, depth 2, D2.
// Signature (x64 MSVC ABI, void return):
//   renderer = rcx (RendererContextI*), ub = rdx (UniformBuffer*),
//   begin = r8d (uint32_t), end = r9d (uint32_t),
//   touched = caller stack +0x20 (5th arg, std::vector<uint16_t>*, may be null),
//   ctx = caller stack +0x28 (6th arg, void*, per-job D3D12 context).
void rendererUpdateUniforms(RendererContextI* renderer, UniformBuffer* ub, uint32_t begin, uint32_t end,
                            std::vector<uint16_t>* touched, void* ctx);

} // namespace native::bgfx
