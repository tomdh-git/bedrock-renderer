#pragma once
// LIFT 0xe878550 size 0x225 1.26.62.01 BgfxFrameBuilder_slot16

#include <cstddef>
#include <cstdint>

namespace native {
namespace d3d12 {

// Global data slots used by this function [V from disassembly]
static constexpr std::uintptr_t kDataSlotAllocator = 0x1233E1A8; // mov rcx,[0x1233E1A8] - allocator object
static constexpr std::uintptr_t kDataSlotF99FFA0   = 0xF99FFA0;   // call qword ptr [0xF99FFA0] - vendor thunk (sub_eea6040)

// Node structure layout (0x50 bytes) [V from disassembly of 0xe878550]
struct FrameBuilderNode {
    void* leftChild;      // 0x00 - set to left child recursive result (initially builder->field0)
    void* userParam;      // 0x08 - set to rbx (3rd function arg)
    void* rightChild;     // 0x10 - set to right child recursive result (initially builder->field0)
    uint16_t flags;       // 0x18 - byte from inputNode+0x18
    uint8_t pad1A[6];     // 0x1A..0x1F padding
    void* strData;        // 0x20 - inline buffer (this+0x20) or heap pointer
    uint64_t pad28;       // 0x28
    uint64_t strLen;      // 0x30 - string length (r14)
    uint64_t strCap;      // 0x38 - string capacity (r12)
    void* field40;        // 0x40 - from inputNode+0x40
    uint32_t field48;     // 0x48 - from inputNode+0x48 (32-bit read/write)
    uint8_t pad4C[4];     // 0x4C..0x4F padding
};

// Layout constants (offsets verified from disassembly [V])
static constexpr std::size_t kOffLeftChild  = 0x00;
static constexpr std::size_t kOffUserParam  = 0x08;
static constexpr std::size_t kOffRightChild = 0x10;
static constexpr std::size_t kOffFlags      = 0x18;
static constexpr std::size_t kOffStrData    = 0x20;
static constexpr std::size_t kOffStrLen     = 0x30;
static constexpr std::size_t kOffStrCap     = 0x38;
static constexpr std::size_t kOffField40    = 0x40;
static constexpr std::size_t kOffField48    = 0x48;

static_assert(kOffField48 + 4 == 0x50, "FrameBuilderNode field48 ends at struct end");

// Forward declaration of lifted callee [V from native_boundary.tsv: class=lift]
extern "C" void sub_eec6ec0(void* dst, const void* src, size_t count); // 0xeec6ec0

// Boundary callees [V from native_boundary.tsv]
namespace boundary {
    // Vendor: data slot 0xF99FFA0 -> sub_eea6040 (allocator thunk)
    // Called with: rcx = allocator object, rdx = size; returns allocated pointer in rax
    void* thunk_f99ffa0(void* allocator, size_t size);

    // Alloc boundary: sub_9bc830 (class alloc) - noreturn on failure
    // Called with: rcx = size
    __declspec(noreturn) void sub_9bc830(size_t size);

    // STL boundary: sub_75720 (class stl) - noreturn on invalid parameter
    __declspec(noreturn) void sub_75720();
} // namespace boundary

// Function signature: x64 Microsoft ABI
// rcx = builder (a0), rdx = inputNode (a1), r8 = userParam (a2)
// Returns: pointer to new FrameBuilderNode in rax
extern "C" FrameBuilderNode* sub_e878550(void* builder, void* inputNode, void* userParam);

// LIFT_FN registry entry: registered via LIFT_FN macro in the .cpp file

} // namespace d3d12
} // namespace native