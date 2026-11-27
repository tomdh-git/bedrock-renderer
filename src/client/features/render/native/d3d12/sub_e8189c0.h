#pragma once
#include <cstddef>
#include <cstdint>

namespace native::d3d12 {

// RendererContextD3D12 (1.26.62.01) - partial layout: this function only touches the per-index
// name region, the rest of the object is opaque.
//   +0x0000..+0x7EDD: opaque (not read or written by this function)
//   +0x7EDE..      : name slots, stride 0x100 per index; slot i holds the name written by vtable slot 45
struct RendererContextD3D12 {
    char pad_0x0000[0x7EDE];
    char name_slot[0x100];          // slot 0 at +0x7EDE; slot i at +0x7EDE + i*0x100
};
static_assert(offsetof(RendererContextD3D12, name_slot) == 0x7EDE,
    "sub_e8189c0: RendererContextD3D12::name_slot must be at +0x7EDE");
static_assert(sizeof(RendererContextD3D12) == 0x7FDE,
    "sub_e8189c0: partial RendererContextD3D12 size is +0x7FDE (+0x7EDE + 0x100 slot 0)");

// Layout constants observed in the disassembly of sub_e8189c0:
//   dest = ctx + index*0x100 + 0x7EDE, copy bound = 0xFA, length cap = 0x7FFFFFFF
constexpr std::uint32_t kNameSlotBaseOffset = 0x7EDE;
constexpr std::uint32_t kNameSlotStride = 0x100;
constexpr std::uint32_t kNameCopyBound = 0xFA;          // dstSize passed to sub_ebce650
constexpr std::uint32_t kNameLengthCap = 0x7FFFFFFF;    // maxlen passed to sub_ebce5e0 and sub_ebce650

// data_f847a07: default (empty) source string used when name is null (lea rax,[0xF847A07] at 0xe8189db).
extern char data_f847a07[];

// Lift-set callees (classified `lift` in docs/data/native_boundary.tsv, rows 504/474):
// forward-declared with their exact ABI signatures and called like any lifted function.
//   0xebce5e0: strnlen-like length: (const char* str, int maxlen) -> int length in eax
extern "C" int sub_ebce5e0(const char* str, int maxlen) noexcept;

// sub_ebce650: bounded string set: (char* dst, int dstSize, SrcDesc* srcdesc, int maxlen) -> int
// declared in src/client/features/render/native/helpers/sub_ebce650.h

// Signature of sub_e8189c0 (x64 Microsoft ABI, vtable slot 45):
//   rcx = RendererContextD3D12* ctx
//   rdx = uint16_t   index      (entry: edi = edx, then movzx eax, di)
//   r8  = const char*  name     (may be null)
//   return: void (no return value is produced)
void sub_e8189c0(RendererContextD3D12* ctx, std::uint16_t index, const char* name) noexcept;

} // namespace native::d3d12
