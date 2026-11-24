// LIFT 0xbcb3cf0 size 0x2119 1.26.62.01 sub_bcb3cf0_chunk1
// Chunk 1 of 2: 0xbcb3cf0..0xbcb54d0
// Frame-graph builder (VV)

#pragma once

#include <cstdint>
#include <cstddef>

// Forward declarations for lifted callees in this chunk
namespace native {
    // sub_e869ff0 - std::string constructor/assignment helper
    void sub_e869ff0(void* dst, const void* src);

    // sub_568ad40 - string/view handling
    void sub_568ad40(void* dst, const void* src);

    // sub_eea6040 - allocator (via data slot 0xF99FFA0)
    void* sub_eea6040(void* this_ptr, void* rdx, uint32_t size);

    // sub_76a8a0 - boundary (stl)
    void sub_76a8a0(void* rcx, void* rdx);

    // sub_eec6ec0 - memcpy-like
    void sub_eec6ec0(void* rcx, void* rdx, uint64_t r8);

    // sub_130ee0 - lifted
    void sub_130ee0(void* rcx, void* rdx, void* r8, void* r9);

    // sub_5693a80 - lifted
    void sub_5693a80(void* rcx, void* rdx);

    // sub_568c420 - lifted
    void sub_568c420(void* rcx, void* rdx);

    // sub_9d6d0 - boundary (stl)
    void sub_9d6d0(void* rcx, void* rdx, void* r8);

    // sub_eec6de0 - memcpy-like
    void sub_eec6de0(void* rcx, void* rdx, void* r8);

    // sub_e935700 - boundary (lift, auto-unresolved)
    void sub_e935700(void* rcx, void* rdx);

    // sub_9bc830 - boundary (alloc)
    void* sub_9bc830(uint64_t size);

    // sub_78ed0 - boundary (crt)
    void sub_78ed0(void);

    // sub_75720 - boundary (stl)
    void sub_75720(void);

    // sub_75740 - boundary (crt)
    void sub_75740(void);
}

// Layout constants for stack frame (rbp-relative)
static constexpr std::ptrdiff_t kFrameSize = 0x988;
static constexpr std::ptrdiff_t kRbpOffset = 0x80;  // rbp = rsp + 0x80 after prologue

// Saved registers at rbp+
static constexpr std::ptrdiff_t kSavedR9   = 0x8E0;  // a3
static constexpr std::ptrdiff_t kSavedXmm6 = 0x8F0;  // xmm6
static constexpr std::ptrdiff_t kCookie    = 0x8E8;  // 0xFFFFFFFFFFFFFFFE

// Stack arguments (above frame)
static constexpr std::ptrdiff_t kArgA4 = 0x970;  // a4 -> r13
static constexpr std::ptrdiff_t kArgA5 = 0x978;  // a5 -> r15

// Local slots (rbp-relative, positive = above rbp, negative = below)
static constexpr std::ptrdiff_t kLocal_A1_Copy     = -0x50;  // 16 bytes from a1 (xmm)
static constexpr std::ptrdiff_t kLocal_A1_Copy_Q   = -0x40;  // qword from a1+0x10
static constexpr std::ptrdiff_t kLocal_TmpStr1     = -0x38;  // rdi points here
static constexpr std::ptrdiff_t kLocal_Slot40      = 0x40;
static constexpr std::ptrdiff_t kLocal_Slot7D0     = 0x7D0;
static constexpr std::ptrdiff_t kLocal_Slot7D8     = 0x7D8;
static constexpr std::ptrdiff_t kLocal_Slot7E0     = 0x7E0;
static constexpr std::ptrdiff_t kLocal_Slot7E8     = 0x7E8;
static constexpr std::ptrdiff_t kLocal_Slot7F0     = 0x7F0;
static constexpr std::ptrdiff_t kLocal_Slot7F8     = 0x7F8;
static constexpr std::ptrdiff_t kLocal_Slot800     = 0x800;
static constexpr std::ptrdiff_t kLocal_Slot808     = 0x808;
static constexpr std::ptrdiff_t kLocal_Slot810     = 0x810;
static constexpr std::ptrdiff_t kLocal_Slot818     = 0x818;
static constexpr std::ptrdiff_t kLocal_Slot820     = 0x820;
static constexpr std::ptrdiff_t kLocal_Slot828     = 0x828;
static constexpr std::ptrdiff_t kLocal_Slot830     = 0x830;
static constexpr std::ptrdiff_t kLocal_Slot838     = 0x838;
static constexpr std::ptrdiff_t kLocal_Slot840     = 0x840;
static constexpr std::ptrdiff_t kLocal_Slot848     = 0x848;
static constexpr std::ptrdiff_t kLocal_Slot850     = 0x850;
static constexpr std::ptrdiff_t kLocal_Slot858     = 0x858;
static constexpr std::ptrdiff_t kLocal_Slot860     = 0x860;
static constexpr std::ptrdiff_t kLocal_Slot868     = 0x868;
static constexpr std::ptrdiff_t kLocal_Slot878     = 0x878;
static constexpr std::ptrdiff_t kLocal_Slot880     = 0x880;
static constexpr std::ptrdiff_t kLocal_Slot888     = 0x888;
static constexpr std::ptrdiff_t kLocal_Slot890     = 0x890;
static constexpr std::ptrdiff_t kLocal_Slot898     = 0x898;
static constexpr std::ptrdiff_t kLocal_Slot8A0     = 0x8A0;
static constexpr std::ptrdiff_t kLocal_Slot8A8     = 0x8A8;
static constexpr std::ptrdiff_t kLocal_Slot8B0     = 0x8B0;
static constexpr std::ptrdiff_t kLocal_Slot8B8     = 0x8B8;
static constexpr std::ptrdiff_t kLocal_Slot8C0     = 0x8C0;
static constexpr std::ptrdiff_t kLocal_Slot8C8     = 0x8C8;
static constexpr std::ptrdiff_t kLocal_Slot8D0     = 0x8D0;
static constexpr std::ptrdiff_t kLocal_Slot8D8     = 0x8D8;
static constexpr std::ptrdiff_t kLocal_Slot8E0     = 0x8E0;  // overlaps saved r9
static constexpr std::ptrdiff_t kLocal_Slot8E8     = 0x8E8;  // overlaps cookie
static constexpr std::ptrdiff_t kLocal_Slot8F0     = 0x8F0;  // overlaps xmm6

// Additional locals used in chunk 1 (0xbcb3cf0..0xbcb54d0)
static constexpr std::ptrdiff_t kLocal_Slot1D0     = 0x1D0;
static constexpr std::ptrdiff_t kLocal_Slot1E0     = 0x1E0;
static constexpr std::ptrdiff_t kLocal_Slot1F0     = 0x1F0;
static constexpr std::ptrdiff_t kLocal_Slot200     = 0x200;
static constexpr std::ptrdiff_t kLocal_Slot208     = 0x208;
static constexpr std::ptrdiff_t kLocal_Slot280     = 0x280;
static constexpr std::ptrdiff_t kLocal_Slot288     = 0x288;
static constexpr std::ptrdiff_t kLocal_Slot290     = 0x290;
static constexpr std::ptrdiff_t kLocal_Slot2A0     = 0x2A0;
static constexpr std::ptrdiff_t kLocal_Slot2B0     = 0x2B0;
static constexpr std::ptrdiff_t kLocal_Slot2C0     = 0x2C0;
static constexpr std::ptrdiff_t kLocal_Slot2D0     = 0x2D0;
static constexpr std::ptrdiff_t kLocal_Slot2E0     = 0x2E0;
static constexpr std::ptrdiff_t kLocal_Slot2F0     = 0x2F0;
static constexpr std::ptrdiff_t kLocal_Slot300     = 0x300;
static constexpr std::ptrdiff_t kLocal_Slot310     = 0x310;
static constexpr std::ptrdiff_t kLocal_Slot320     = 0x320;
static constexpr std::ptrdiff_t kLocal_Slot324     = 0x324;
static constexpr std::ptrdiff_t kLocal_Slot334     = 0x334;
static constexpr std::ptrdiff_t kLocal_Slot344     = 0x344;
static constexpr std::ptrdiff_t kLocal_Slot354     = 0x354;
static constexpr std::ptrdiff_t kLocal_Slot364     = 0x364;
static constexpr std::ptrdiff_t kLocal_Slot374     = 0x374;
static constexpr std::ptrdiff_t kLocal_Slot384     = 0x384;
static constexpr std::ptrdiff_t kLocal_Slot394     = 0x394;
static constexpr std::ptrdiff_t kLocal_Slot3A4     = 0x3A4;
static constexpr std::ptrdiff_t kLocal_Slot3B4     = 0x3B4;
static constexpr std::ptrdiff_t kLocal_Slot3C4     = 0x3C4;
static constexpr std::ptrdiff_t kLocal_Slot3C8     = 0x3C8;
static constexpr std::ptrdiff_t kLocal_Slot3CC     = 0x3CC;
static constexpr std::ptrdiff_t kLocal_Slot3DC     = 0x3DC;
static constexpr std::ptrdiff_t kLocal_Slot3EC     = 0x3EC;
static constexpr std::ptrdiff_t kLocal_Slot3FB     = 0x3FB;
static constexpr std::ptrdiff_t kLocal_Slot410     = 0x410;
static constexpr std::ptrdiff_t kLocal_Slot448     = 0x448;
static constexpr std::ptrdiff_t kLocal_Slot450     = 0x450;
static constexpr std::ptrdiff_t kLocal_Slot460     = 0x460;
static constexpr std::ptrdiff_t kLocal_Slot468     = 0x468;
static constexpr std::ptrdiff_t kLocal_Slot470     = 0x470;
static constexpr std::ptrdiff_t kLocal_Slot480     = 0x480;
static constexpr std::ptrdiff_t kLocal_Slot488     = 0x488;
static constexpr std::ptrdiff_t kLocal_Slot500     = 0x500;
static constexpr std::ptrdiff_t kLocal_Slot508     = 0x508;
static constexpr std::ptrdiff_t kLocal_Slot510     = 0x510;
static constexpr std::ptrdiff_t kLocal_Slot520     = 0x520;
static constexpr std::ptrdiff_t kLocal_Slot530     = 0x530;
static constexpr std::ptrdiff_t kLocal_Slot540     = 0x540;
static constexpr std::ptrdiff_t kLocal_Slot550     = 0x550;
static constexpr std::ptrdiff_t kLocal_Slot560     = 0x560;
static constexpr std::ptrdiff_t kLocal_Slot570     = 0x570;
static constexpr std::ptrdiff_t kLocal_Slot580     = 0x580;
static constexpr std::ptrdiff_t kLocal_Slot590     = 0x590;
static constexpr std::ptrdiff_t kLocal_Slot5A0     = 0x5A0;
static constexpr std::ptrdiff_t kLocal_Slot5A4     = 0x5A4;
static constexpr std::ptrdiff_t kLocal_Slot5B4     = 0x5B4;
static constexpr std::ptrdiff_t kLocal_Slot5C4     = 0x5C4;
static constexpr std::ptrdiff_t kLocal_Slot5D4     = 0x5D4;
static constexpr std::ptrdiff_t kLocal_Slot5E4     = 0x5E4;
static constexpr std::ptrdiff_t kLocal_Slot5F4     = 0x5F4;
static constexpr std::ptrdiff_t kLocal_Slot604     = 0x604;
static constexpr std::ptrdiff_t kLocal_Slot614     = 0x614;
static constexpr std::ptrdiff_t kLocal_Slot624     = 0x624;
static constexpr std::ptrdiff_t kLocal_Slot634     = 0x634;
static constexpr std::ptrdiff_t kLocal_Slot644     = 0x644;
static constexpr std::ptrdiff_t kLocal_Slot648     = 0x648;
static constexpr std::ptrdiff_t kLocal_Slot64C     = 0x64C;
static constexpr std::ptrdiff_t kLocal_Slot65C     = 0x65C;
static constexpr std::ptrdiff_t kLocal_Slot66C     = 0x66C;
static constexpr std::ptrdiff_t kLocal_Slot67B     = 0x67B;
static constexpr std::ptrdiff_t kLocal_Slot690     = 0x690;
static constexpr std::ptrdiff_t kLocal_Slot6C8     = 0x6C8;
static constexpr std::ptrdiff_t kLocal_Slot6D0     = 0x6D0;
static constexpr std::ptrdiff_t kLocal_Slot6D8     = 0x6D8;
static constexpr std::ptrdiff_t kLocal_Slot6E8     = 0x6E8;
static constexpr std::ptrdiff_t kLocal_Slot6F0     = 0x6F0;
static constexpr std::ptrdiff_t kLocal_Slot6F8     = 0x6F8;
static constexpr std::ptrdiff_t kLocal_Slot700     = 0x700;
static constexpr std::ptrdiff_t kLocal_Slot710     = 0x710;
static constexpr std::ptrdiff_t kLocal_Slot720     = 0x720;
static constexpr std::ptrdiff_t kLocal_Slot728     = 0x728;
static constexpr std::ptrdiff_t kLocal_Slot738     = 0x738;
static constexpr std::ptrdiff_t kLocal_Slot740     = 0x740;
static constexpr std::ptrdiff_t kLocal_Slot748     = 0x748;
static constexpr std::ptrdiff_t kLocal_Slot750     = 0x750;
static constexpr std::ptrdiff_t kLocal_Slot758     = 0x758;
static constexpr std::ptrdiff_t kLocal_Slot759     = 0x759;
static constexpr std::ptrdiff_t kLocal_Slot760     = 0x760;
static constexpr std::ptrdiff_t kLocal_Slot768     = 0x768;
static constexpr std::ptrdiff_t kLocal_Slot770     = 0x770;
static constexpr std::ptrdiff_t kLocal_Slot778     = 0x778.
static constexpr std::ptrdiff_t kLocal_Slot780     = 0x780;
static constexpr std::ptrdiff_t kLocal_Slot788     = 0x788;
static constexpr std::ptrdiff_t kLocal_Slot790     = 0x790.
static constexpr std::ptrdiff_t kLocal_Slot798     = 0x798.
static constexpr std::ptrdiff_t kLocal_Slot7A2     = 0x7A2.
static constexpr std::ptrdiff_t kLocal_Slot7A8     = 0x7A8.
static constexpr std::ptrdiff_t kLocal_Slot7B0     = 0x7B0.
static constexpr std::ptrdiff_t kLocal_Slot7B8     = 0x7B8.
static constexpr std::ptrdiff_t kLocal_Slot7C0     = 0x7C0.
static constexpr std::ptrdiff_t kLocal_Slot7CA     = 0x7CA.

// Data addresses (RIP-relative in exe, absolute here)
static constexpr uintptr_t kData_12AE24E8 = 0x12AE24E8;
static constexpr uintptr_t kData_12AE24F0 = 0x12AE24F0;
static constexpr uintptr_t kData_12AE24F8 = 0x12AE24F8;
static constexpr uintptr_t kData_12AE2500 = 0x12AE2500;
static constexpr uintptr_t kData_12AE2504 = 0x12AE2504;
static constexpr uintptr_t kData_12AE250C = 0x12AE250C;
static constexpr uintptr_t kData_12AE2510 = 0x12AE2510;
static constexpr uintptr_t kData_12AE2518 = 0x12AE2518;
static constexpr uintptr_t kData_1233E1A8 = 0x1233E1A8;
static constexpr uintptr_t kData_F99FFA0  = 0xF99FFA0;  // -> sub_eea6040
static constexpr uintptr_t kData_EFD3400  = 0xEFD3400;
static constexpr uintptr_t kData_F44BE30  = 0xF44BE30;
static constexpr uintptr_t kData_F44BE80  = 0xF44BE80.
static constexpr uintptr_t kData_F44BE10  = 0xF44BE10.
static constexpr uintptr_t kData_F44BE60  = 0xF44BE60.
static constexpr uintptr_t kData_F084570  = 0xF084570.
static constexpr uintptr_t kData_F0E1D60  = 0xF0E1D60.

static_assert(sizeof(void*) == 8, "x64 only");
static_assert(kFrameSize == 0x988, "frame size matches disassembly");

// Chunk state: all live values at chunk boundary 0xbcb54d0
// This struct is passed by pointer to the next chunk
struct ChunkState_bcb3cf0_1 {
    // Preserved registers
    uint64_t rbx;   // a1 (or r14 in else branch)
    uint64_t rsi;   // a2
    uint64_t rdi;   // varies
    uint64_t r12;   // from [r15+8] or [r13+8]
    uint64_t r13;   // from [a4+8] or r13 arg
    uint64_t r14;   // from data_12ae24e8 or rcx
    uint64_t r15;   // from data_12ae24e8 or stack arg a5
    // xmm6 saved at rbp+0x8F0
    // We don't save xmm6 in struct; it's in stack frame

    // Stack frame base (rbp)
    uint8_t* rbp;

    // Key stack slots that are live across chunk boundary
    // (only those read/written in chunk 2)
    uint64_t slot_1D0[2];   // xmm at 0x1D0
    uint64_t slot_1E0[2];   // xmm at 0x1E0
    uint64_t slot_1F0;      // qword at 0x1F0
    uint64_t slot_200;      // qword at 0x200
    uint64_t slot_208;      // rbx saved at 0x208
    uint64_t slot_280;      // qword at 0x280
    uint64_t slot_2C0;      // qword at 0x2C0 (object ptr)
    uint64_t slot_448;      // qword at 0x448 (object ptr)
    uint64_t slot_500;      // qword at 0x500
    uint64_t slot_540;      // qword at 0x540
    uint64_t slot_548;      // qword at 0x548 (rsi)
    uint64_t slot_550[2];   // xmm at 0x550
    uint64_t slot_560[2];   // xmm at 0x560
    uint64_t slot_578[2];   // xmm at 0x578
    uint64_t slot_588[2];   // xmm at 0x588
    uint64_t slot_598;      // qword at 0x598
    uint64_t slot_5A0[2];   // xmm at 0x5A0
    uint64_t slot_5B0[2];   // xmm at 0x5B0
    uint64_t slot_5C0;      // qword at 0x5C0
    uint64_t slot_6C8;      // qword at 0x6C8 (object ptr)
    uint64_t slot_6D0;      // qword at 0x6D0
    uint64_t slot_6D8[2];   // xmm at 0x6D8
    uint64_t slot_6E8[2];   // xmm at 0x6E8
    uint64_t slot_700[2];   // xmm at 0x700
    uint64_t slot_710[2];   // xmm at 0x710
    uint64_t slot_720;      // qword at 0x720
    uint64_t slot_728[2];   // xmm at 0x728
    uint64_t slot_738;      // qword at 0x738
    uint64_t slot_750;      // qword at 0x750
    uint64_t slot_758;      // byte at 0x758
    uint64_t slot_759;      // byte at 0x759
    uint64_t slot_760;      // qword at 0x760
    uint64_t slot_768[2];   // xmm at 0x768
    uint64_t slot_778;      // qword at 0x778
    uint64_t slot_780;      // qword at 0x780 (r14)
    uint64_t slot_788;      // qword at 0x788
    uint64_t slot_790;      // dword at 0x790
    uint64_t slot_798;      // qword at 0x798 (r12)
    uint64_t slot_7A2;      // byte at 0x7A2
    uint64_t slot_7A8[2];   // xmm at 0x7A8
    uint64_t slot_7B8;      // qword at 0x7B8
    uint64_t slot_7C0;      // qword at 0x7C0 (r13)
    uint64_t slot_7CA;      // byte at 0x7CA
    uint64_t slot_7D0;      // qword at 0x7D0
    uint64_t slot_7D8;      // qword at 0x7D8
    uint64_t slot_7E0;      // qword at 0x7E0
    uint64_t slot_7E8;      // dword at 0x7E8
    uint64_t slot_7F0;      // qword at 0x7F0
    uint64_t slot_7F8;      // qword at 0x7F8
    uint64_t slot_800;      // qword at 0x800
    uint64_t slot_808;      // qword at 0x808
    uint64_t slot_810;      // qword at 0x810
    uint64_t slot_818;      // qword at 0x818
    uint64_t slot_820;      // qword at 0x820
    uint64_t slot_828;      // qword at 0x828
    uint64_t slot_830;      // dword at 0x830
    uint64_t slot_838;      // qword at 0x838
    uint64_t slot_840;      // dword at 0x840
    uint64_t slot_848;      // qword at 0x848
    uint64_t slot_850;      // qword at 0x850
    uint64_t slot_858;      // qword at 0x858
    uint64_t slot_860[2];   // xmm at 0x860
    uint64_t slot_878;      // qword at 0x878
    uint64_t slot_880;      // qword at 0x880
    uint64_t slot_888;      // qword at 0x888
    uint64_t slot_890;      // qword at 0x890
    uint64_t slot_898;      // qword at 0x898
    uint64_t slot_8A0;      // qword at 0x8A0
    uint64_t slot_8A8;      // qword at 0x8A8
    uint64_t slot_8B0[2];   // xmm at 0x8B0
    uint64_t slot_8C0[2];   // xmm at 0x8C0
    uint64_t slot_8D0;      // qword at 0x8D0
    uint64_t slot_8D8;      // qword at 0x8D8

    // Data pointers (read from globals)
    uint64_t data_12ae24e8;
    uint64_t data_12ae24f0;
    uint64_t data_12ae24f8;
    uint32_t data_12ae2500;
    uint64_t data_12ae2504;
    uint32_t data_12ae250c;
    uint64_t data_12ae2510;
    uint32_t data_12ae2518;
    uint64_t data_1233e1a8;
    uint64_t data_f99ffa0;  // allocator thunk
    double   data_efd3400;  // constant double
    uint64_t data_f44be30;
    uint64_t data_f44be80;
    uint64_t data_f44be10;
    uint64_t data_f44be60;
    uint64_t data_f084570;
    uint64_t data_f0e1d60;
};

// Entry point for chunk 1
// Signature matches original: rcx=a0, rdx=a1, r8=a2, r9=a3, [rsp+0x28]=a4, [rsp+0x30]=a5
// Returns void (original returns at 0xbcb5d29 after chunk 2)
extern "C" void sub_bcb3cf0_chunk1(
    void* a0, void* a1, void* a2, void* a3, void* a4, void* a5,
    ChunkState_bcb3cf0_1* state
);