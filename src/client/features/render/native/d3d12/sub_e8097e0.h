#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Callee sub_eec6ec0 (docs/data/native_boundary.tsv: class lift). Forward-declared here,
// lifted by its own unit; ABI as used by sub_e8097e0: (rcx=dst, rdx=src, r8d=byteCount).
extern "C" void sub_eec6ec0(void* rcx, const void* rdx, std::int32_t r8d);

namespace d3d12 {

// Layout constants for 0xe8097e0 (RendererContextD3D12 base slot 58).
// sub_e8097e0 template-initialises a 7-entry table at RVA 0x1285DBE0 (stride 0x18)
// from a constant template at RVA 0xF4EDE20 (0xA8 = 7*0x18 bytes) via sub_eec6ec0,
// then overwrites entries 0,1,2,3,5,6 (entry 4 at +0x60 is NOT touched) with a value
// fetched through this->vtable[0xD0] when the entry's first dword is != 4.

constexpr std::uintptr_t kTableRva      = 0x1285DBE0; // lea rcx,[0x1285DBE0]      ; table base (arg0 of sub_eec6ec0)
constexpr std::uintptr_t kTemplateRva   = 0x00F4EDE20; // lea rdx,[0xF4EDE20]      ; template source (arg1)
constexpr std::uint32_t  kTableBytes    = 0xA8;        // mov r8d,0xA8            ; 7 * 0x18
constexpr std::size_t    kEntryCount    = 7;           // kTableBytes / kEntryStride
constexpr std::size_t    kEntryStride   = 0x18;        // consecutive base+0x18 accesses
constexpr std::size_t    kEntryDataOff  = 0x00;        // movups/movaps [base],xmm0 ; 16-byte block
constexpr std::size_t    kEntryDataLen  = 0x10;        // 16 bytes
constexpr std::size_t    kEntryValueOff = 0x10;        // mov [base+0x10],eax      ; dword tag

// Per-entry byte offsets from kTableRva (kEntryStride * index).
constexpr std::size_t kEntry0Off = 0x00; // 0x1285DBE0  (block A, unconditional)
constexpr std::size_t kEntry1Off = 0x18; // 0x1285DBF8  (block B, guarded)
constexpr std::size_t kEntry2Off = 0x30; // 0x1285DC10  (block C, guarded)
constexpr std::size_t kEntry3Off = 0x48; // 0x1285DC28  (block D, guarded)
// 0x1285DC40 (kEntryStride*4 = 0x60) is intentionally NOT written by the original.
constexpr std::size_t kEntry5Off = 0x78; // 0x1285DC58  (block E, guarded)
constexpr std::size_t kEntry6Off = 0x90; // 0x1285DC70  (block F, guarded)

constexpr std::uint32_t  kGuardValue    = 4;          // cmp r9d,4 ; je skip     ; skip re-fetch
constexpr std::uintptr_t kCookieRva     = 0x1230A0C0; // mov rax,[0x1230A0C0]    ; __security_cookie
constexpr std::size_t    kThunkSlotOff  = 0xD0;       // mov rax,[rax+0xD0]     ; vtable slot used by sub_4687b0 thunk
constexpr std::size_t    kFetchSize     = 0x14;       // [rsp+0x24..0x38)       ; 16-byte block + dword

static_assert(kTableBytes == 0xA8, "table bytes");
static_assert(kEntryStride == 0x18, "entry stride");
static_assert(kEntryDataOff == 0x00, "entry data offset");
static_assert(kEntryDataLen == 0x10, "entry data length");
static_assert(kEntryValueOff == 0x10, "entry value offset");
static_assert(kEntryCount * kEntryStride == kTableBytes, "7 entries of 0x18 == 0xA8");
static_assert(kEntry0Off == 0x00 && kEntry1Off == 0x18 && kEntry2Off == 0x30 && kEntry3Off == 0x48, "entry offsets 0..3");
static_assert(kEntry5Off == 0x78 && kEntry6Off == 0x90, "entry offsets 5,6");
static_assert(kGuardValue == 4, "guard value");
static_assert(kThunkSlotOff == 0xD0, "vtable slot offset");
static_assert(kFetchSize == 0x14, "fetch buffer size");

// The lifted function: exact x64 Microsoft ABI (rcx = this).
extern "C" void sub_e8097e0(void* a0);

} } // namespace native::d3d12

#define LIFT_FN_E8097E0 0xe8097e0