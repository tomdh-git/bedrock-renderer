#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Layout constants and static assertions for lifted sub 0xbc68840
// (size 0x5f7, Minecraft Bedrock 1.26.62.01). Every address and offset below is
// verbatim from the disassembly of the function [V]; nothing is inferred.

static_assert(sizeof(std::uintptr_t) == 8, "sub_bc68840: uintptr_t is 8 bytes on x64");
static_assert(sizeof(std::uint32_t) == 4, "sub_bc68840: uint32_t is 4 bytes");

// Data addresses read by the function [V].
constexpr std::uintptr_t kGCookieSecret = 0x1230A0C0ULL;   // [data_1230a0c0] stack cookie secret
constexpr std::uintptr_t kGFlagSingleThread = 0x127CA028ULL;  // [data_127ca028] : 1 selects the P2a timeout entry
constexpr std::uintptr_t kGFlagBias1 = 0x127CA050ULL;       // [data_127ca050] : 1 selects the [ctx]==1 bias block
constexpr std::uintptr_t kGFlagBias2 = 0x127CA078ULL;       // [data_127ca078] : 1 selects the [ctx]==2 bias block
constexpr std::uintptr_t kGFlagBias3 = 0x127CA0A0ULL;       // [data_127ca0a0] : 1 selects the [ctx]==3 bias block
constexpr std::uintptr_t kGHandleArray = 0x127CA010ULL;     // [data_127ca010] handle array (entry stride 8)
constexpr std::uintptr_t kGSurfaceArray = 0x127CA0C8ULL;    // [data_127ca0c8] 0x28-stride surface array
constexpr std::uintptr_t kGTlsIndex = 0x128767C8ULL;        // [data_128767c8] TLS slot index
constexpr std::uintptr_t kSlotF9A8770 = 0xF9A8770ULL;       // [data_f9a8770]
constexpr std::uintptr_t kSlotF9A8780 = 0xF9A8780ULL;       // [data_f9a8780]
constexpr std::uintptr_t kSlotF99FFA0 = 0xF99FFA0ULL;       // [data_f99ffa0] = sub_eea6040, a `jmp rax` trampoline [V]
constexpr std::uintptr_t kCallbackRva = 0xBC6AF40ULL;       // [sub_bc6af40] comparator passed to sub_ebdbc90 in r9

// Constants used by the lifted code [V].
constexpr std::uint32_t kScratchSize = 0x9C;                        // scratch buffer [rsp+0x74..0x74+0x9C)
constexpr std::uintptr_t kScratchPattern = 0x60000009CULL;          // stored at [rsp+0x74] after the memset-like call
constexpr std::uint32_t kScratchFillOffset = 0x08;                  // [rsp+0x7C] = scratch + 8, filled with 2 or 1
constexpr std::uint32_t kTableMaxEntries = 11;                      // [rsp+0x40 + n*4], ebp <= 11
constexpr std::uint32_t kTlsMagic = 0x78666762UL;                   // "bgfx"
constexpr std::uintptr_t kTlsArrayGva = 0x58;                       // gs:[0x58] TLS array pointer
constexpr std::uintptr_t kTlsSlotOffset = 0x2D4C;                   // TLS slot + 0x2D4c holds the magic dword
constexpr std::uint32_t kEntryMult = 5;                             // table entry * 5 indexes the handle array
constexpr std::uint32_t kHandleEntryStride = 8;                     // handle array entry stride ([rbx + index*8])
constexpr std::uint32_t kSurfaceFirst = 4;                          // first surface-array index
constexpr std::uint32_t kSurfaceAfterLast = 0xB;                    // loop stops when index reaches 0xB
constexpr std::uint32_t kSurfaceStride = 0x28;                      // surface-array stride
constexpr std::uint32_t kWaitArg = 4;                               // r8d argument to sub_ebdbc90
constexpr std::uint32_t kTimeoutValue = 0x3E800UL;                  // esi when *ctx == 0
constexpr std::uint32_t kBiasValue = 0x3E9UL;                       // esi/edi base for bias blocks
constexpr std::uint32_t kLoopBiasMatch = 0x3E900UL;                 // loop entry when *ctx == surface index
constexpr std::uint32_t kLoopBiasNomatch = 0x100UL;                 // loop entry otherwise

// Handle entry layout ([rbx + index*8]): qword callable at +0x00, byte cleared at +0x18 after the call,
// flag byte at +0x20 read before the call [V].
struct HandleEntry {
    std::uintptr_t fn;              // +0x00
    std::uint8_t pad0x08[0x10];     // +0x08..0x17
    std::uint8_t cleared0x18;       // +0x18
    std::uint8_t flag0x20;          // +0x20
};
static_assert(offsetof(HandleEntry, fn) == 0x00, "sub_bc68840: handle callable at +0x00");
static_assert(offsetof(HandleEntry, cleared0x18) == 0x18, "sub_bc68840: handle cleared byte at +0x18");
static_assert(offsetof(HandleEntry, flag0x20) == 0x20, "sub_bc68840: handle flag byte at +0x20");
static_assert(sizeof(HandleEntry) == 0x21, "sub_bc68840: handle entry size 0x21");

// bool sub_bc68840(std::uintptr_t* ctx /*rcx*/, std::uint8_t mode /*dl*/, std::uint8_t* outSignaled /*r8*/) returns al
bool sub_bc68840(std::uintptr_t* ctx, std::uint8_t mode, std::uint8_t* outSignaled);
std::uint32_t sub_bc68840_footprint(std::uintptr_t* ctx, std::uint8_t mode, std::uint8_t* outSignaled);

} // namespace native
