#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Callee sub_eec6d80 (docs/data/native_boundary.tsv: class lift).
// Forward-declared here; ABI as used by sub_e8707f0: (rcx=exceptionObj, rdx=typeInfo).
extern "C" void sub_eec6d80(void* rcx, const void* rdx);

// Callee sub_e951550 (docs/data/native_boundary.tsv: class crt, __report_gsfailure).
// Forward-declared here; called on /GS cookie mismatch.
extern "C" void sub_e951550(std::uintptr_t);

namespace d3d12 {

// Layout constants for 0xe8707f0 (u32 stream reader, called by Material::parseBody 0xe870870).
// Reads 4 bytes from an istream via its vtable read() virtual function.
// On success (exactly 4 bytes read) returns true; on short read returns false;
// on read failure (gcount() < 0) throws a C++ exception via sub_eec6d80.

constexpr std::uintptr_t kCookieRva       = 0x1230A0C0; // mov rax,[0x1230A0C0]    ; __security_cookie
constexpr std::uintptr_t kReadSlotRva     = 0xF9A7480;  // call qword ptr [0xF9A7480] ; istream::read vtable slot
constexpr std::uintptr_t kExceptionObjRva = 0xF08E738;  // lea rax,[0xF08E738]     ; exception object for throw
constexpr std::uintptr_t kTypeInfoRva     = 0xFB3B080;  // lea rdx,[0xFB3B080]     ; type_info for throw
constexpr std::uint32_t  kReadSize        = 4;          // mov r8d,4               ; bytes to read

// Stack layout (sub rsp,0x48):
//   [rsp+0x00..0x30)  : buffer for read (16+ bytes, used by istream::read)
//   [rsp+0x30..0x40)  : exception object setup (xmm0 zeroed)
//   [rsp+0x40]        : saved cookie (cookie ^ rsp)
constexpr std::size_t kStackSize        = 0x48;
constexpr std::size_t kCookieSlotOff    = 0x40;
constexpr std::size_t kReadBufferOff    = 0x00;
constexpr std::size_t kExceptionSetupOff= 0x30;

static_assert(kStackSize == 0x48, "stack size");
static_assert(kCookieSlotOff == 0x40, "cookie slot offset");
static_assert(kReadBufferOff == 0x00, "read buffer offset");
static_assert(kExceptionSetupOff == 0x30, "exception setup offset");

// The lifted function: exact x64 Microsoft ABI.
// rcx = std::istream* stream
// rdx = uint32_t* out
// returns bool (in al)
extern "C" bool sub_e8707f0(void* stream, std::uint32_t* out);

} } // namespace native::d3d12

#define LIFT_FN_E8707F0 0xe8707f0