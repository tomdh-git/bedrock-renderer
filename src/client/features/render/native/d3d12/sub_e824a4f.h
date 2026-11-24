#pragma once
// LIFT 0xe824a4f size 0x8a94 1.26.62.01 sub_e824a4f

#include <cstdint>

namespace native {
namespace d3d12 {

// Stack frame layout constants (relative to rbx stack base)
struct FrameLayout_e824a4f {
    // Saved registers area (set up by parent sub_e821120 prologue)
    static constexpr uint32_t OFF_RBP_SAVE      = 0xE180; // rbp saved at [rbx+0xE180]
    static constexpr uint32_t OFF_XMM6_SAVE     = 0xE110;
    static constexpr uint32_t OFF_XMM7_SAVE     = 0xE120;
    static constexpr uint32_t OFF_XMM8_SAVE     = 0xE130;
    static constexpr uint32_t OFF_XMM9_SAVE     = 0xE140;
    static constexpr uint32_t OFF_XMM10_SAVE    = 0xE150;
    static constexpr uint32_t OFF_XMM11_SAVE    = 0xE160;
    static constexpr uint32_t OFF_XMM12_SAVE    = 0xE170;
    static constexpr uint32_t OFF_XMM13_SAVE    = 0xE180;
    static constexpr uint32_t OFF_XMM14_SAVE    = 0xE190;
    static constexpr uint32_t OFF_XMM15_SAVE    = 0xE1A0;

    // Argument home slots (stored by parent prologue)
    static constexpr uint32_t OFF_ARG_RCX       = 0x00A0; // this/obj0
    static constexpr uint32_t OFF_ARG_RDX       = 0x0168; // arg1 (also copied to r14)
    static constexpr uint32_t OFF_ARG_R8        = 0x03A8; // arg2
    static constexpr uint32_t OFF_ARG_R9        = 0x03A8; // arg3 (same slot as r8 in parent)

    // Draw list and vertex buffer state
    static constexpr uint32_t OFF_DRAW_LIST     = 0x01C0; // draw list pointer
    static constexpr uint32_t OFF_DRAW_IDX_LO   = 0x0110; // loop index low
    static constexpr uint32_t OFF_DRAW_IDX_HI   = 0x0150; // loop index high
    static constexpr uint32_t OFF_VB_BASE       = 0x0588; // vertex buffer base
    static constexpr uint32_t OFF_SLOT_BITMAP   = 0x224A8; // per-slot bitmap base (off [rbx+0x90])
    static constexpr uint32_t OFF_SLOT_STATUS   = 0x226AC; // per-slot status words
    static constexpr uint32_t OFF_SLOT_HEAD     = 0x224A0; // slot head index
    static constexpr uint32_t OFF_SLOT_HEAD_ALT = 0x2A6A8; // alt slot head index

    // Vertex buffer view build area
    static constexpr uint32_t OFF_VBV_START     = 0x00C0; // D3D12_VERTEX_BUFFER_VIEW buffer
    static constexpr uint32_t OFF_VBV_STRIDE    = 0x00D0; // stride
    static constexpr uint32_t OFF_VBV_COUNT     = 0x00D4; // count
    static constexpr uint32_t OFF_VBV_OFFSET    = 0x00D8; // offset

    // Scratch / working registers spilled to stack
    static constexpr uint32_t OFF_R10_SCRATCH   = 0x00F0;
    static constexpr uint32_t OFF_R12_IDX       = 0x02B0;
    static constexpr uint32_t OFF_R13_SIZE      = 0x02B4;
    static constexpr uint32_t OFF_R14_STRIDE    = 0x02BC;
    static constexpr uint32_t OFF_RDI_ELEM_IDX  = 0x010C;
    static constexpr uint32_t OFF_RSI_ELEM_CNT  = 0x0110;

    // Page table / guarded array
    static constexpr uint32_t OFF_PAGE_TABLE    = 0x00B0; // base of page table
    static constexpr uint32_t OFF_PAGE_TABLE_SZ = 0xC96178; // size field in page table
    static constexpr uint32_t OFF_GUARDED_BASE  = 0x0128; // guarded array base
    static constexpr uint32_t OFF_GUARDED_LIMIT = 0x20468; // guarded array limit
    static constexpr uint32_t OFF_GUARDED_FLAGS = 0x20478; // guarded array flags

    // Data slot 0xF99FFA0 (sub_eea6040) - vendor boundary
    static constexpr uint64_t DATA_SLOT_F99FFA0 = 0xF99FFA0;

    // Total stack frame size (parent allocates 0xE238 via sub_e9e7970)
    static constexpr uint32_t FRAME_SIZE        = 0xE238;
};

// Verify frame layout against known constants
static_assert(FrameLayout_e824a4f::FRAME_SIZE == 0xE238, "FrameLayout_e824a4f size mismatch");

// Complete live state passed through all chunks (rbx is stack base)
struct ChunkState_e824a4f {
    // Stack base (rbx) - set by parent prologue, constant throughout
    void* rbx = nullptr;

    // Preserved registers across chunks (x64 non-volatile + r10/r11 scratch)
    uint64_t r12 = 0; // index / size word
    uint64_t r13 = 0; // guarded-array size
    uint64_t r14 = 0; // byte offset into guarded array / arg1 copy
    uint64_t r15 = 0; // element stride accumulator
    uint64_t rdi = 0; // element index
    uint64_t rsi = 0; // element count / draw item pointer
    uint64_t r10 = 0; // scratch / object pointer
    uint64_t r11 = 0; // scratch

    // XMM6-XMM15 are preserved by parent prologue; not tracked in chunk state
};

// Forward declarations of lifted callees (native::sub_<rva>)
void sub_e82dcc0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e82d960(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_ebce390(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_ebd1560(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e820500(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e82de90(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e935700(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e835b50(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_eec6ed0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e83ace0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_ebce430(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_bc5f110(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e835f00(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e83aed0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e83abb0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e81e1c0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e81b4d0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e81b720(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e81d850(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_ebd15b0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_ebd18f0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_eec6ec0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_eec6de0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_eec6d80(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_bc6a9d0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_e8360f0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
void sub_ebdb740(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);

// Boundary callees (via native::boundary::<name>)
namespace boundary {
    // STL: sub_47e8f0
    void sub_47e8f0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
    // CRT import thunk: sub_eec6ed0 (jmp qword ptr [IAT])
    void sub_eec6ed0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
    // Vendor: data slot 0xF99FFA0 -> sub_eea6040
    void thunk_f99ffa0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
    // Vendor: sub_ebd21c0, sub_ebd3c60
    void sub_ebd21c0(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
    void sub_ebd3c60(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
    // OS: sub_ebdb740
    void sub_ebdb740(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx);
} // namespace boundary

// LIFT_FN registry entry for sub_e824a4f
// Signature: void sub_e824a4f(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
// Actual x64 ABI: rcx=this, rdx=arg1, r8=arg2, r9=arg3; rbx=stack base (non-volatile, preserved from parent)
using Fn_e824a4f = void(*)(void* rbx, uint64_t rsi, uint64_t rdi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);

constexpr Fn_e824a4f LIFT_FN_e824a4f = reinterpret_cast<Fn_e824a4f>(0xE824A4F);

// Main lifted function entry point
void sub_e824a4f(ChunkState_e824a4f& state, uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9);

} // namespace d3d12
} // namespace native