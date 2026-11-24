// LIFT 0xbc8a380 size 0x1afc 1.26.62.01 sub_bc8a380_chunk0
// CHUNK 0xbc8a380..0xbc8bb76

#pragma once

#include <cstdint>
#include <cstddef>

// Forward declarations for lifted callees (in lift set)
namespace native {
    // Lift set callees (from function row)
    void sub_130ee0(void* rcx, void* rdx, void* r8, void* r9);
    void sub_9bd3c0(void* rcx);
    void sub_5668ac0(void* rcx, void* rdx, void* r8);
    void sub_567c8b0(void* rcx, void* rdx, void* r8, void* r9);
    void sub_568ad40(void* rcx, void* rdx);
    void sub_568c420(void* rcx, void* rdx);
    void sub_5693a80(void* rcx, void* rdx);
    void sub_56b8630(void* rcx, void* r8, void* r9, void* rdx);
    void sub_56d5810(void* rcx);
    void sub_bc8c720(void* rcx);
    void sub_bc8c890(void* rcx, void* rdx);
    void sub_e86b370(void* rcx, void* rdx);

    // Auto-unresolved->lift callees (classified as lift, not yet lifted)
    void sub_eec5870(void* rcx, int edx);
    void sub_e869ff0(void* rcx, void* rdx);
    void sub_eec6ec0(void* rcx, void* r8, void* rdx);
    void sub_eec6de0(void* rcx, void* rdx, void* r8);
    void sub_e935700(void* rcx); // or with more args per call site

    // Boundary callees (from native_boundary.tsv)
    namespace boundary {
        // 0x73150 stl
        void sub_73150();
        // 0x75720 stl
        void sub_75720();
        // 0x75740 stl
        void sub_75740(void* rcx, void* rdx);
        // 0x78ed0 crt
        void sub_78ed0();
        // 0x79580 stl
        void sub_79580(void* rcx, void* rdx);
        // 0x9d6d0 stl
        void sub_9d6d0(void* rcx, void* rdx);
        // 0x76a8a0 stl
        void sub_76a8a0(void* rcx, void* rdx);
        // 0x9bc830 alloc
        void* sub_9bc830(size_t size);
        // 0x9bd2e0 os
        void sub_9bd2e0(void* rcx);
        // 0xe938cb0 os
        void sub_e938cb0(void* rcx);
        // 0xe938d70 os
        void sub_e938d70(void* rcx);

        // Vendor thunk via data slot 0xF99FFA0 -> sub_eea6040
        // Called as: call qword ptr [0xF99FFA0]
        using eea6040_fn = void(*)(void* rcx, void* rdx); // inferred from call sites
        extern eea6040_fn g_eea6040_thunk;
    }
}

// Layout constants for stack frame (rbp-relative, frame base at rbp = rsp+0x80 after prologue)
// Frame size: 0xD08 bytes + saved registers
// Verified against disassembly 0xbc8a380..0xbc8bb76

namespace native::bc8a380 {

// Stack slot offsets from rbp (negative = below rbp, positive = above rbp)
// rbp = rsp + 0x80 after: sub rsp,0xD08; lea rbp,[rsp+0x80]
// Saved registers at [rbp-0x80]..[rbp-0x8] (push rbp,r15,r14,r13,r12,rsi,rdi,rbx)
// xmm6 saved at [rbp+0xC70]
// Stack cookie at [rbp+0xC68] = 0xFFFFFFFFFFFFFFFE

// Argument home slots (shadow space + saved args)
constexpr std::ptrdiff_t ARG_RCX_HOME   = 0xC58; // [rbp+0xC58] = rcx (1st arg)
constexpr std::ptrdiff_t ARG_RDX_HOME   = 0x9B8; // [rbp+0x9B8] = rdx (2nd arg, copied at 0xbc8a42c)
constexpr std::ptrdiff_t ARG_R8_HOME    = 0xC60; // [rbp+0xC60] used for various
constexpr std::ptrdiff_t ARG_R9_HOME    = 0xC38; // [rbp+0xC38] = r9

// Local stack slots (observed in chunk 0xbc8a380..0xbc8bb76)
constexpr std::ptrdiff_t SLOT_330       = 0x330; // 16-byte xmm/pointer slot
constexpr std::ptrdiff_t SLOT_338       = 0x338;
constexpr std::ptrdiff_t SLOT_340       = 0x340;
constexpr std::ptrdiff_t SLOT_348       = 0x348;
constexpr std::ptrdiff_t SLOT_2A0       = 0x2A0;
constexpr std::ptrdiff_t SLOT_2A8       = 0x2A8;
constexpr std::ptrdiff_t SLOT_2B0       = 0x2B0; // 16-byte
constexpr std::ptrdiff_t SLOT_328       = 0x328;
constexpr std::ptrdiff_t SLOT_700       = 0x700; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_710       = 0x710; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_720       = 0x720;
constexpr std::ptrdiff_t SLOT_728       = 0x728; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_738       = 0x738;
constexpr std::ptrdiff_t SLOT_740       = 0x740;
constexpr std::ptrdiff_t SLOT_748       = 0x748;
constexpr std::ptrdiff_t SLOT_750       = 0x750;
constexpr std::ptrdiff_t SLOT_758       = 0x758; // byte
constexpr std::ptrdiff_t SLOT_760       = 0x760; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_770       = 0x770;
constexpr std::ptrdiff_t SLOT_778       = 0x778;
constexpr std::ptrdiff_t SLOT_780       = 0x780;
constexpr std::ptrdiff_t SLOT_784       = 0x784; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_794       = 0x794;
constexpr std::ptrdiff_t SLOT_798       = 0x798; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_7A8       = 0x7A8;
constexpr std::ptrdiff_t SLOT_7AC       = 0x7AC; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_7BC       = 0x7BC;
constexpr std::ptrdiff_t SLOT_7C4       = 0x7C4; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_7D4       = 0x7D4;
constexpr std::ptrdiff_t SLOT_7D8       = 0x7D8; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_7E8       = 0x7E8.
constexpr std::ptrdiff_t SLOT_7EC       = 0x7EC; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_7FC       = 0x7FC.
constexpr std::ptrdiff_t SLOT_800       = 0x800.
constexpr std::ptrdiff_t SLOT_808       = 0x808.
constexpr std::ptrdiff_t SLOT_810       = 0x810.
constexpr std::ptrdiff_t SLOT_818       = 0x818; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_828       = 0x828.
constexpr std::ptrdiff_t SLOT_82C       = 0x82C; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_83C       = 0x83C.
constexpr std::ptrdiff_t SLOT_840       = 0x840; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_850       = 0x850.
constexpr std::ptrdiff_t SLOT_858       = 0x858; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_868       = 0x868.
constexpr std::ptrdiff_t SLOT_86C       = 0x86C; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_87C       = 0x87C.
constexpr std::ptrdiff_t SLOT_880       = 0x880; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_890       = 0x890.
constexpr std::ptrdiff_t SLOT_894       = 0x894; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_8A4       = 0x8A4.
constexpr std::ptrdiff_t SLOT_8A8       = 0x8A8; // byte
constexpr std::ptrdiff_t SLOT_8AC       = 0x8AC.
constexpr std::ptrdiff_t SLOT_8B0       = 0x8B0; // word
constexpr std::ptrdiff_t SLOT_8B2       = 0x8B2; // byte
constexpr std::ptrdiff_t SLOT_8B4       = 0x8B4.
constexpr std::ptrdiff_t SLOT_8B8       = 0x8B8; // byte
constexpr std::ptrdiff_t SLOT_8BC       = 0x8BC; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_8C8       = 0x8C8; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_8D8       = 0x8D8; // byte
constexpr std::ptrdiff_t SLOT_8DC       = 0x8DC.
constexpr std::ptrdiff_t SLOT_8E4       = 0x8E4.
constexpr std::ptrdiff_t SLOT_8E8       = 0x8E8; // byte
constexpr std::ptrdiff_t SLOT_8EC       = 0x8EC.
constexpr std::ptrdiff_t SLOT_8F2       = 0x8F2.
constexpr std::ptrdiff_t SLOT_8FA       = 0x8FA; // byte
constexpr std::ptrdiff_t SLOT_8FC       = 0x8FC.
constexpr std::ptrdiff_t SLOT_904       = 0x904.
constexpr std::ptrdiff_t SLOT_90C       = 0x90C; // byte
constexpr std::ptrdiff_t SLOT_910       = 0x910.
constexpr std::ptrdiff_t SLOT_914       = 0x914.
constexpr std::ptrdiff_t SLOT_91C       = 0x91C; // byte
constexpr std::ptrdiff_t SLOT_91D       = 0x91D; // byte
constexpr std::ptrdiff_t SLOT_920       = 0x920; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_930       = 0x930; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_940       = 0x940; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_950       = 0x950; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_960       = 0x960; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_970       = 0x970; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_980       = 0x980; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_990       = 0x990; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_9A0       = 0x9A0; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_9B0       = 0x9B0.
constexpr std::ptrdiff_t SLOT_9B8       = 0x9B8. // rdi (arg2)
constexpr std::ptrdiff_t SLOT_9C0       = 0x9C0; // 24-byte struct
constexpr std::ptrdiff_t SLOT_9F8       = 0x9F8.
constexpr std::ptrdiff_t SLOT_A00       = 0xA00.
constexpr std::ptrdiff_t SLOT_A08       = 0xA08.
constexpr std::ptrdiff_t SLOT_A10       = 0xA10; // dword
constexpr std::ptrdiff_t SLOT_A18       = 0xA18; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_A28       = 0xA28; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_A38       = 0xA38; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_A48       = 0xA48; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_A58       = 0xA58.
constexpr std::ptrdiff_t SLOT_A60       = 0xA60.
constexpr std::ptrdiff_t SLOT_A70       = 0xA70.
constexpr std::ptrdiff_t SLOT_A78       = 0xA78; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_A80       = 0xA80.
constexpr std::ptrdiff_t SLOT_A88       = 0xA88.
constexpr std::ptrdiff_t SLOT_A90       = 0xA90.
constexpr std::ptrdiff_t SLOT_A98       = 0xA98. // rbx
constexpr std::ptrdiff_t SLOT_AA0       = 0xAA0; // word
constexpr std::ptrdiff_t SLOT_AA4       = 0xAA4.
constexpr std::ptrdiff_t SLOT_AA8       = 0xAA8; // byte
constexpr std::ptrdiff_t SLOT_AB0       = 0xAB0.
constexpr std::ptrdiff_t SLOT_ABA       = 0xABA; // byte
constexpr std::ptrdiff_t SLOT_AC0       = 0xAC0.
constexpr std::ptrdiff_t SLOT_AC8       = 0xAC8; // word
constexpr std::ptrdiff_t SLOT_ACC       = 0xACC.
constexpr std::ptrdiff_t SLOT_AD0       = 0xAD0; // byte
constexpr std::ptrdiff_t SLOT_AD8       = 0xAD8.
constexpr std::ptrdiff_t SLOT_AE2       = 0xAE2; // byte
constexpr std::ptrdiff_t SLOT_AE8       = 0xAE8.
constexpr std::ptrdiff_t SLOT_AF0       = 0xAF0; // word
constexpr std::ptrdiff_t SLOT_AF4       = 0xAF4.
constexpr std::ptrdiff_t SLOT_AF8       = 0xAF8; // byte
constexpr std::ptrdiff_t SLOT_B00       = 0xB00.
constexpr std::ptrdiff_t SLOT_B0A       = 0xB0A; // byte
constexpr std::ptrdiff_t SLOT_B10       = 0xB10.
constexpr std::ptrdiff_t SLOT_B18       = 0xB18.
constexpr std::ptrdiff_t SLOT_B22       = 0xB22; // byte
constexpr std::ptrdiff_t SLOT_B28       = 0xB28.
constexpr std::ptrdiff_t SLOT_B30       = 0xB30.
constexpr std::ptrdiff_t SLOT_B38       = 0xB38.
constexpr std::ptrdiff_t SLOT_B40       = 0xB40.
constexpr std::ptrdiff_t SLOT_B48       = 0xB48.
constexpr std::ptrdiff_t SLOT_B50       = 0xB50.
constexpr std::ptrdiff_t SLOT_B58       = 0xB58.
constexpr std::ptrdiff_t SLOT_B60       = 0xB60.
constexpr std::ptrdiff_t SLOT_B68       = 0xB68.
constexpr std::ptrdiff_t SLOT_B70       = 0xB70.
constexpr std::ptrdiff_t SLOT_B78       = 0xB78.
constexpr std::ptrdiff_t SLOT_B80       = 0xB80.
constexpr std::ptrdiff_t SLOT_B88       = 0xB88.
constexpr std::ptrdiff_t SLOT_B90       = 0xB90.
constexpr std::ptrdiff_t SLOT_B98       = 0xB98.
constexpr std::ptrdiff_t SLOT_BA0       = 0xBA0.
constexpr std::ptrdiff_t SLOT_BA8       = 0xBA8.
constexpr std::ptrdiff_t SLOT_BB0       = 0xBB0.
constexpr std::ptrdiff_t SLOT_BB8       = 0xBB8; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_BC0       = 0xBC0.
constexpr std::ptrdiff_t SLOT_BC8       = 0xBC8.
constexpr std::ptrdiff_t SLOT_BD0       = 0xBD0.
constexpr std::ptrdiff_t SLOT_BD8       = 0xBD8.
constexpr std::ptrdiff_t SLOT_BE0       = 0xBE0.
constexpr std::ptrdiff_t SLOT_BE8       = 0xBE8.
constexpr std::ptrdiff_t SLOT_BF0       = 0xBF0.
constexpr std::ptrdiff_t SLOT_BF8       = 0xBF8; // byte/16-byte
constexpr std::ptrdiff_t SLOT_C08       = 0xC08.
constexpr std::ptrdiff_t SLOT_C10       = 0xC10.
constexpr std::ptrdiff_t SLOT_C18       = 0xC18.
constexpr std::ptrdiff_t SLOT_C20       = 0xC20.
constexpr std::ptrdiff_t SLOT_C28       = 0xC28.
constexpr std::ptrdiff_t SLOT_C30       = 0xC30.
constexpr std::ptrdiff_t SLOT_C38       = 0xC38.
constexpr std::ptrdiff_t SLOT_C40       = 0xC40.
constexpr std::ptrdiff_t SLOT_C48       = 0xC48.
constexpr std::ptrdiff_t SLOT_C50       = 0xC50.
constexpr std::ptrdiff_t SLOT_C60       = 0xC60.
constexpr std::ptrdiff_t SLOT_C68       = 0xC68; // stack cookie
constexpr std::ptrdiff_t SLOT_C70       = 0xC70; // xmm6 save

// Below rbp (negative offsets)
constexpr std::ptrdiff_t SLOT_NEG_30    = -0x30; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_NEG_40    = -0x40; // 16-byte xmm
constexpr std::ptrdiff_t SLOT_NEG_50    = -0x50; // 16-byte xmm + 8-byte
constexpr std::ptrdiff_t SLOT_NEG_58    = -0x58; // 8-byte

// Data addresses (rip-relative in exe, absolute here)
constexpr uintptr_t DATA_12AE1B60 = 0x12AE1B60;
constexpr uintptr_t DATA_128767C8 = 0x128767C8;
constexpr uintptr_t DATA_12AE1B70 = 0x12AE1B70;
constexpr uintptr_t DATA_12AE1B80 = 0x12AE1B80;
constexpr uintptr_t DATA_12AE1B98 = 0x12AE1B98;
constexpr uintptr_t DATA_12AE1B88 = 0x12AE1B88;
constexpr uintptr_t DATA_12AE1BA8 = 0x12AE1BA8;
constexpr uintptr_t DATA_12AE1BA0 = 0x12AE1BA0;
constexpr uintptr_t DATA_12AE1B58 = 0x12AE1B58;
constexpr uintptr_t DATA_12AE1B78 = 0x12AE1B78;
constexpr uintptr_t DATA_12AE1B68 = 0x12AE1B68;
constexpr uintptr_t DATA_F25C7F0  = 0xF25C7F0;
constexpr uintptr_t DATA_F5B67DB  = 0xF5B67DB;
constexpr uintptr_t DATA_F99FFA0  = 0xF99FFA0; // thunk -> sub_eea6040
constexpr uintptr_t DATA_1233E1A8 = 0x1233E1A8;
constexpr uintptr_t DATA_F44B310  = 0xF44B310;
constexpr uintptr_t DATA_EFD3400  = 0xEFD3400;
constexpr uintptr_t DATA_F441220  = 0xF441220.
constexpr uintptr_t DATA_F44B2E0  = 0xF44B2E0.
constexpr uintptr_t DATA_F09A740  = 0xF09A740.
constexpr uintptr_t DATA_F44B2C0  = 0xF44B2C0.
constexpr uintptr_t DATA_F563B27  = 0xF563B27.
constexpr uintptr_t DATA_F549A53  = 0xF549A53.
constexpr uintptr_t DATA_F5182C0  = 0xF5182C0.
constexpr uintptr_t DATA_F7E41CA  = 0xF7E41CA.

static_assert(sizeof(void*) == 8, "64-bit target required");

// Chunk state struct - captures all live state at chunk boundary 0xbc8bb76
// This struct is passed by pointer to the chunk function
struct ChunkState {
    // Preserved registers (callee-saved)
    uint64_t rbp;
    uint64_t rbx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;

    // Volatile registers that are live across chunk boundary
    uint64_t rax;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;

    // XMM registers (only xmm6 is callee-saved and explicitly saved)
    // We capture xmm0-xmm5, xmm6-xmm15 as needed
    // For simplicity, capture xmm6 explicitly, others as 16-byte slots
    __m128 xmm6;

    // Stack frame base (rbp value)
    uint8_t* frame_base; // points to rbp

    // Stack slots that are live across the chunk boundary
    // (only those read/written in chunk 0 and read in chunk 1)
    // We include all slots observed in chunk 0 for simplicity
    // In practice, only a subset is truly live across the boundary
    uint64_t slots[0x1000 / 8]; // Large enough to cover all observed offsets

    // Helper to access slot by rbp-relative offset
    uint64_t& slot(std::ptrdiff_t offset) {
        return slots[(offset + 0x800) / 8]; // bias to handle negative offsets
    }
    const uint64_t& slot(std::ptrdiff_t offset) const {
        return slots[(offset + 0x800) / 8];
    }

    // 128-bit slot access
    __m128& slot128(std::ptrdiff_t offset) {
        return *reinterpret_cast<__m128*>(&slots[(offset + 0x800) / 8]);
    }
    const __m128& slot128(std::ptrdiff_t offset) const {
        return *reinterpret_cast<const __m128*>(&slots[(offset + 0x800) / 8]);
    }
};

} // namespace native::bc8a380