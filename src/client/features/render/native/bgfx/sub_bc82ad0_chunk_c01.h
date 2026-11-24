#pragma once
// LIFT 0xbc82ad0 chunk c01
// Chunk state for sub_bc82ad0 range 0xbc842c9..0xbc85abd
// Mirrors the rbp-frame locals live across this chunk boundary.

#include <cstdint>
#include <cstddef>

// Forward declarations for lifted callees in this chunk
namespace native {
    void sub_5679db0(void* ctx, void* a2, void* a3);           // 0x5679db0
    void sub_bc8a240(void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8); // 0xbc8a240
    void sub_e86b370(void* ctx, void* a2, void* a3);           // 0xe86b370
    void sub_bc88560(void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8); // 0xbc88560
    void sub_7d7890(void* a1, void* a2);                        // 0x7d7890
    void sub_9b250(void* a1);                                   // 0x9b250
    void sub_e935740(void* a1);                                 // 0xe935740
}

// Boundary callees (via native::boundary)
namespace native::boundary {
    void sub_e935700(void* a1, void* a2, void* a3);            // 0xe935700 (lift-set, forward declared)
    void sub_eea6040(void* a1);                                 // 0xeea6040 via [0xF99FFA0] (vendor thunk)
    void sub_73150(void* a1);                                   // 0x73150 (stl)
    void sub_79580(void* a1, void* a2);                         // 0x79580 (stl)
    void sub_9bc830(uint32_t size);                             // 0x9bc830 (alloc)
    void sub_76ad00(void* a1, void* a2, uint64_t a3);           // 0x76ad00 (stl)
    void sub_e938cb0(void* a1);                                 // 0xe938cb0 (os)
    void sub_e938d70(void* a1);                                 // 0xe938d70 (os)
    void sub_f9a8c78();                                         // 0xf9a8c78 (crt - invalid parameter handler)
}

// Frame layout constants (rbp-relative offsets from the function prologue)
// rbp = rsp + 0x80 after prologue; frame size 0x938
// Offsets are from rbp. Verified against disassembly.

// Saved XMM registers
static constexpr ptrdiff_t kOffXmm6   = 0x810;
static constexpr ptrdiff_t kOffXmm7   = 0x820;
static constexpr ptrdiff_t kOffXmm8   = 0x830;
static constexpr ptrdiff_t kOffXmm9   = 0x840;
static constexpr ptrdiff_t kOffXmm10  = 0x850;
static constexpr ptrdiff_t kOffXmm11  = 0x860;
static constexpr ptrdiff_t kOffXmm12  = 0x870;
static constexpr ptrdiff_t kOffXmm13  = 0x880;
static constexpr ptrdiff_t kOffXmm14  = 0x890;
static constexpr ptrdiff_t kOffXmm15  = 0x8A0;

// Argument spill slots
static constexpr ptrdiff_t kOffArg1   = 0x670;  // rcx at entry
static constexpr ptrdiff_t kOffArg2   = 0x760;  // rdx at entry
static constexpr ptrdiff_t kOffArg3   = 0x768;  // r8 at entry
static constexpr ptrdiff_t kOffArg4   = 0x0;    // r9 -> r14 (passed in register)

// Key locals used in chunk c01 (0xbc842c9..0xbc85abd)
static constexpr ptrdiff_t kOff740    = 0x740;  // word + byte flag
static constexpr ptrdiff_t kOff770    = 0x770;  // string/buffer ptr
static constexpr ptrdiff_t kOff778    = 0x778;  // word
static constexpr ptrdiff_t kOff77C    = 0x77C;  // dword
static constexpr ptrdiff_t kOff780    = 0x780;  // byte
static constexpr ptrdiff_t kOff788    = 0x788;  // qword
static constexpr ptrdiff_t kOff792    = 0x792;  // byte
static constexpr ptrdiff_t kOff7B0    = 0x7B0;  // qword (string data / pointer)
static constexpr ptrdiff_t kOff7B8    = 0x7B8;  // qword (size/capacity)
static constexpr ptrdiff_t kOff7C0    = 0x7C0;  // qword
static constexpr ptrdiff_t kOff7C8    = 0x7C8;  // qword
static constexpr ptrdiff_t kOff7E0    = 0x7E0;  // xmm/float data
static constexpr ptrdiff_t kOff7F0    = 0x7F0;  // xmm/qword
static constexpr ptrdiff_t kOff7F8    = 0x7F8;  // qword
static constexpr ptrdiff_t kOff6A0    = 0x6A0;  // qword
static constexpr ptrdiff_t kOff6A8    = 0x6A8;  // qword (r13)
static constexpr ptrdiff_t kOff6B0    = 0x6B0;  // qword (pointer)
static constexpr ptrdiff_t kOff6B8    = 0x6B8;  // qword (rsi base)
static constexpr ptrdiff_t kOff6E8    = 0x6E8;  // qword (array base)
static constexpr ptrdiff_t kOff6F2    = 0x6F2;  // word (count)
static constexpr ptrdiff_t kOff801    = 0x801;  // byte
static constexpr ptrdiff_t kOff802    = 0x802;  // word
static constexpr ptrdiff_t kOff804    = 0x804;  // byte flag
static constexpr ptrdiff_t kOff940    = 0x940;  // qword
static constexpr ptrdiff_t kOff928    = 0x928;  // qword
static constexpr ptrdiff_t kOff978    = 0x978;  // qword
static constexpr ptrdiff_t kOff690    = 0x690;  // qword
static constexpr ptrdiff_t kOff698    = 0x698;  // qword
static constexpr ptrdiff_t kOff730    = 0x730;  // qword
static constexpr ptrdiff_t kOff73C    = 0x73C;  // dword (float)
static constexpr ptrdiff_t kOff640    = 0x640;  // dword
static constexpr ptrdiff_t kOff638    = 0x638;  // qword
static constexpr ptrdiff_t kOff628    = 0x628;  // qword
static constexpr ptrdiff_t kOff67F    = 0x67F;  // byte/word
static constexpr ptrdiff_t kOff68F    = 0x68F;  // byte
static constexpr ptrdiff_t kOff2F0    = 0x2F0;  // xmm
static constexpr ptrdiff_t kOff310    = 0x310;  // xmm
static constexpr ptrdiff_t kOff430    = 0x430;  // xmm
static constexpr ptrdiff_t kOff440    = 0x440;  // xmm
static constexpr ptrdiff_t kOff450    = 0x450;  // xmm
static constexpr ptrdiff_t kOff460    = 0x460;  // xmm
static constexpr ptrdiff_t kOff470    = 0x470;  // xmm
static constexpr ptrdiff_t kOff650    = 0x650;  // xmm
static constexpr ptrdiff_t kOff160    = 0x160;  // xmm (xmm14)
static constexpr ptrdiff_t kOff170    = 0x170;  // xmm (xmm15)
static constexpr ptrdiff_t kOff180    = 0x180;  // xmm (xmm6)
static constexpr ptrdiff_t kOff190    = 0x190;  // xmm (xmm7)
static constexpr ptrdiff_t kOff1A0    = 0x1A0;  // xmm (xmm8)
static constexpr ptrdiff_t kOff1B0    = 0x1B0;  // xmm (xmm9)
static constexpr ptrdiff_t kOff1C0    = 0x1C0;  // xmm (xmm10)
static constexpr ptrdiff_t kOff1D0    = 0x1D0;  // xmm (xmm11)
static constexpr ptrdiff_t kOff1E0    = 0x1E0;  // qword
static constexpr ptrdiff_t kOff1E8    = 0x1E8;  // word
static constexpr ptrdiff_t kOff1EA    = 0x1EA;  // word
static constexpr ptrdiff_t kOff1EC    = 0x1EC;  // word
static constexpr ptrdiff_t kOff1EE    = 0x1EE;  // word
static constexpr ptrdiff_t kOff1F0    = 0x1F0;  // dword
static constexpr ptrdiff_t kOff1F4    = 0x1F4;  // xmm
static constexpr ptrdiff_t kOff204    = 0x204;  // xmm
static constexpr ptrdiff_t kOff214    = 0x214;  // xmm
static constexpr ptrdiff_t kOff224    = 0x224;  // xmm
static constexpr ptrdiff_t kOff234    = 0x234;  // xmm
static constexpr ptrdiff_t kOff244    = 0x244;  // xmm
static constexpr ptrdiff_t kOff254    = 0x254;  // xmm (xmm12)
static constexpr ptrdiff_t kOff264    = 0x264;  // xmm (xmm13)
static constexpr ptrdiff_t kOff274    = 0x274;  // xmm
static constexpr ptrdiff_t kOff284    = 0x284;  // dword
static constexpr ptrdiff_t kOff288    = 0x288;  // byte
static constexpr ptrdiff_t kOff28C    = 0x28C;  // dword
static constexpr ptrdiff_t kOff290    = 0x290;  // word
static constexpr ptrdiff_t kOff292    = 0x292;  // byte
static constexpr ptrdiff_t kOff294    = 0x294;  // dword
static constexpr ptrdiff_t kOff298    = 0x298;  // byte
static constexpr ptrdiff_t kOff29C    = 0x29C;  // xmm
static constexpr ptrdiff_t kOff2AC    = 0x2AC;  // qword
static constexpr ptrdiff_t kOff2B4    = 0x2B4;  // dword
static constexpr ptrdiff_t kOff2B8    = 0x2B8;  // byte
static constexpr ptrdiff_t kOff2BC    = 0x2BC;  // qword
static constexpr ptrdiff_t kOff2C4    = 0x2C4;  // dword
static constexpr ptrdiff_t kOff2C8    = 0x2C8;  // byte
static constexpr ptrdiff_t kOff2C9    = 0x2C9;  // xmm (16 bytes)
static constexpr ptrdiff_t kOff2D9    = 0x2D9;  // byte
static constexpr ptrdiff_t kOff2DA    = 0x2DA;  // byte
static constexpr ptrdiff_t kOff2DC    = 0x2DC;  // byte
static constexpr ptrdiff_t kOff388    = 0x388;  // qword
static constexpr ptrdiff_t kOff3D8    = 0x3D8;  // qword
static constexpr ptrdiff_t kOff3B8    = 0x3B8;  // qword
static constexpr ptrdiff_t kOff3C0    = 0x3C0;  // qword
static constexpr ptrdiff_t kOff3C8    = 0x3C8;  // qword
static constexpr ptrdiff_t kOff3D0    = 0x3D0;  // qword
static constexpr ptrdiff_t kOff648    = 0x648;  // qword
static constexpr ptrdiff_t kOff6B0_2  = 0x6B0;  // string buffer (reused)
static constexpr ptrdiff_t kOff6B7    = 0x6B7;  // qword
static constexpr ptrdiff_t kOff6BF    = 0x6BF;  // byte
static constexpr ptrdiff_t kOff6E0    = 0x6E0;  // qword
static constexpr ptrdiff_t kOff6D3    = 0x6D3;  // qword
static constexpr ptrdiff_t kOff6D8    = 0x6D8;  // qword
static constexpr ptrdiff_t kOff6D0    = 0x6D0;  // word
static constexpr ptrdiff_t kOff6D2    = 0x6D2;  // byte
static constexpr ptrdiff_t kOff770_2  = 0x770;  // string buffer (reused)
static constexpr ptrdiff_t kOff777    = 0x777;  // qword
static constexpr ptrdiff_t kOff77F    = 0x77F;  // byte
static constexpr ptrdiff_t kOff790    = 0x790;  // xmm/word
static constexpr ptrdiff_t kOff7A0    = 0x7A0;  // qword
static constexpr ptrdiff_t kOff7A8    = 0x7A8;  // qword
static constexpr ptrdiff_t kOff807    = 0x807;  // byte
static constexpr ptrdiff_t kOff4A0    = 0x4A0;  // 16-byte buffer (repeatedly used)
static constexpr ptrdiff_t kOff4B0    = 0x4B0;  // qword
static constexpr ptrdiff_t kOff4B8    = 0x4B8;  // qword
static constexpr ptrdiff_t kOff6C0    = 0x6C0;  // qword
static constexpr ptrdiff_t kOff6C8    = 0x6C8;  // qword
static constexpr ptrdiff_t kOff780_2  = 0x780;  // qword (reused)
static constexpr ptrdiff_t kOff788_2  = 0x788;  // qword (reused)
static constexpr ptrdiff_t kOff980    = 0x980;  // qword
static constexpr ptrdiff_t kOff970    = 0x970;  // qword
static constexpr ptrdiff_t kOff798    = 0x798;  // byte

// Data addresses referenced in this chunk
static constexpr uintptr_t kData12AE1AD0  = 0x12AE1AD0;
static constexpr uintptr_t kData12AE1A20  = 0x12AE1A20;
static constexpr uintptr_t kData128C1A58  = 0x128C1A58;
static constexpr uintptr_t kData12AE1A30  = 0x12AE1A30;
static constexpr uintptr_t kDataEFD3400   = 0xEFD3400;
static constexpr uintptr_t kData12AE19F0  = 0x12AE19F0;
static constexpr uintptr_t kData12AE19D0  = 0x12AE19D0;
static constexpr uintptr_t kDataF563D37   = 0xF563D37;   // "SSRGetReflectedColor"
static constexpr uintptr_t kData1233E1A8  = 0x1233E1A8;
static constexpr uintptr_t kDataF99FFA0   = 0xF99FFA0;   // -> sub_eea6040
static constexpr uintptr_t kDataF54E7B3   = 0xF54E7B3;   // "ScreenSpaceReflections"
static constexpr uintptr_t kDataF5B111F   = 0xF5B111F;   // "SSRRayMarch"
static constexpr uintptr_t kData12AE18D8  = 0x12AE18D8;
static constexpr uintptr_t kData12AE18A8  = 0x12AE18A8;
static constexpr uintptr_t kDataF7CE38A   = 0xF7CE38A;   // "SSRRayMarchHZB"
static constexpr uintptr_t kData12AE1910  = 0x12AE1910;
static constexpr uintptr_t kData12AE18E0  = 0x12AE18E0;
static constexpr uintptr_t kDataF54C98F   = 0xF54C98F;   // "SSRFillGaps"
static constexpr uintptr_t kData12AE1948  = 0x12AE1948.
static constexpr uintptr_t kData12AE1918  = 0x12AE1918.
static constexpr uintptr_t kData1DF55AD7E2C2C59F = 0x1DF55AD7E2C2C59F;
static constexpr uintptr_t kData12AE1980  = 0x12AE1980.
static constexpr uintptr_t kData12AE1950  = 0x12AE1950.
static constexpr uintptr_t kDataF563D37_2 = 0xF563D37;   // "SSRGetReflectedColor"
static constexpr uintptr_t kDataCF01D3F07DAC7C8 = 0xCF01D3F07DAC7C8;
static constexpr uintptr_t kData12AE1998  = 0x12AE1998.
static constexpr uintptr_t kData12AE1988  = 0x12AE1988.
static constexpr uintptr_t kDataF550D9E   = 0xF550D9E;   // "SSRRayMarchingParams"
static constexpr uintptr_t kData12AE19A8  = 0x12AE19A8.
static constexpr uintptr_t kDataF547C22   = 0xF547C22;   // "SSRFadingParamsAndThickness"
static constexpr uintptr_t kData12AE19B8  = 0x12AE19B8.
static constexpr uintptr_t kDataF550DB3   = 0xF550DB3;   // "SSRRoughnessCutoffParams"
static constexpr uintptr_t kData12AE19C8  = 0x12AE19C8.
static constexpr uintptr_t kDataF550D40   = 0xF550D40;   // "SSRTemporalAccumulationParams"
static constexpr uintptr_t kData12AE19D8  = 0x12AE19D8.
static constexpr uintptr_t kDataF544CBC   = 0xF544CBC;   // "UnitPlaneExtents"
static constexpr uintptr_t kData12AE19E8  = 0x12AE19E8.
static constexpr uintptr_t kData12AE19F8  = 0x12AE19F8.
static constexpr uintptr_t kDataF5BBFAF   = 0xF5BBFAF;   // "ScreenSize"
static constexpr uintptr_t kData12AE1A08  = 0x12AE1A08.
static constexpr uintptr_t kDataF60CFD8   = 0xF60CFD8;   // "CameraData"
static constexpr uintptr_t kData12AE1A18  = 0x12AE1A18.
static constexpr uintptr_t kDataF5DE7ED   = 0xF5DE7ED;   // "ViewportScale"
static constexpr uintptr_t kData12AE1A28  = 0x12AE1A28.
static constexpr uintptr_t kDataF5C6B69   = 0xF5C6B69;   // "InputTexture"
static constexpr uintptr_t kData12AE1A38  = 0x12AE1A38.
static constexpr uintptr_t kDataF5639F3   = 0xF5639F3;   // "RasterColor"
static constexpr uintptr_t kData12AE1A48  = 0x12AE1A48.
static constexpr uintptr_t kDataF5ADE08   = 0xF5ADE08;   // "GbufferDepth"
static constexpr uintptr_t kData12AE1A58  = 0x12AE1A58.
static constexpr uintptr_t kDataF5A62A0   = 0xF5A62A0;   // "GbufferNormal"
static constexpr uintptr_t kData12AE1A68  = 0x12AE1A68.
static constexpr uintptr_t kDataF547D3A   = 0xF547D3A;   // "GbufferRoughness"
static constexpr uintptr_t kData12AE1A78  = 0x12AE1A78.
static constexpr uintptr_t kDataF56EC49   = 0xF56EC49;   // "PreviousReflectionBuffer"
static constexpr uintptr_t kData12AE1A88  = 0x12AE1A88.
static constexpr uintptr_t kDataF7E41CA   = 0xF7E41CA;   // "Color0"
static constexpr uintptr_t kData12AE1A98  = 0x12AE1A98.
static constexpr uintptr_t kDataF56ECF5   = 0xF56ECF5;   // "HiZBuffer"
static constexpr uintptr_t kData12AE1AA8  = 0x12AE1AA8.
static constexpr uintptr_t kDataF54F41B   = 0xF54F41B;   // "HiZViewportDimensionsAndBufferDimensions"
static constexpr uintptr_t kData12AE1AB8  = 0x12AE1AB8.
static constexpr uintptr_t kDataF530C94   = 0xF530C94;   // "HiZMipCount"
static constexpr uintptr_t kData12AE1AC8  = 0x12AE1AC8.
static constexpr uintptr_t kDataF53C810   = 0xF53C810;   // "ScreenSpaceRayOffset"
static constexpr uintptr_t kData12AE1B50  = 0x12AE1B50.
static constexpr uintptr_t kDataF5BAC48   = 0xF5BAC48.
static constexpr uintptr_t kDataF5BAC4A   = 0xF5BAC4A.
static constexpr uintptr_t kData12AE1B10  = 0x12AE1B10.
static constexpr uintptr_t kDataBC89F80   = 0xBC89F80.
static constexpr uintptr_t kData12AE19A0  = 0x12AE19A0.
static constexpr uintptr_t kData12AE19B0  = 0x12AE19B0.
static constexpr uintptr_t kData12AE19C0  = 0x12AE19C0.
static constexpr uintptr_t kData12AE19E0  = 0x12AE19E0.
static constexpr uintptr_t kDataF9A8C78   = 0xF9A8C78.
static constexpr uintptr_t kData6465646E65747845 = 0x6465646E65747845; // "Extended"
static constexpr uintptr_t kData6C6C694670614764 = 0x6C6C694670614764; // "FillGap"

// Chunk state struct - contains the frame pointer (rbp) and any live register values
// At chunk boundary 0xbc842c9, the live state includes:
// - rbp (frame base)
// - r14 (4th argument)
// - rbx, rsi, rdi, r12, r13, r15 (callee-saved)
// - xmm6-xmm15 (saved at rbp+0x810..0x8A0)
// All frame locals are accessed via rbp, so we pass rbp as the frame pointer.
struct ChunkState_bc82ad0_c01 {
    uint8_t* rbp;           // Frame base pointer (rbp value)
    uint64_t r14;           // 4th argument (r9 at entry)
    uint64_t rbx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t r12;
    uint64_t r13;
    uint64_t r15;
    // xmm6-xmm15 are accessed via rbp offsets, no need to store separately
};

// Layout assertions
static_assert(sizeof(ChunkState_bc82ad0_c01) == 8 * 7, "ChunkState_bc82ad0_c01 size");