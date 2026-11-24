#pragma once
#include <cstdint>

namespace native {

// LIFT 0xe83b8c0 size 0x121 1.26.62.01 sub_e83b8c0
// layout constants (offsets into the object at rcx and output at rdx)
constexpr std::size_t kObjPtr0Off = 0x0;     // [rcx]     -> copied to [rdx]
constexpr std::size_t kObjField40Off = 0x40; // lock add
constexpr std::size_t kObjField48Off = 0x48;
constexpr std::size_t kObjField50Off = 0x50;
constexpr std::size_t kObjField58Off = 0x58;
constexpr std::size_t kObjField60Off = 0x60;
constexpr std::size_t kObjField68Off = 0x68;
constexpr std::size_t kObjField70Off = 0x70;
constexpr std::size_t kObjField78Off = 0x78; // lock add
constexpr std::size_t kObjField80Off = 0x80; // lock inc word
constexpr std::size_t kObjField88Off = 0x88;
constexpr std::size_t kObjField90Off = 0x90;
constexpr std::size_t kObjField98Off = 0x98;
constexpr std::size_t kObjField08Off = 0x8;
// output struct (rdx) offsets
constexpr std::size_t kOut00Off = 0x0;
constexpr std::size_t kOut08Off = 0x8;
constexpr std::size_t kOut10Off = 0x10;
constexpr std::size_t kOut18Off = 0x18;
constexpr std::size_t kOut20Off = 0x20;
constexpr std::size_t kOut28Off = 0x28;
constexpr std::size_t kOut30Off = 0x30;

static_assert(kObjField50Off == 0x50, "obj +0x50");
static_assert(kObjField58Off == 0x58, "obj +0x58");
static_assert(kObjField48Off == 0x48, "obj +0x48");
static_assert(kObjField68Off == 0x68, "obj +0x68");
static_assert(kObjField70Off == 0x70, "obj +0x70");
static_assert(kObjField60Off == 0x60, "obj +0x60");
static_assert(kObjField80Off == 0x80, "obj +0x80");
static_assert(kObjField78Off == 0x78, "obj +0x78");
static_assert(kObjField40Off == 0x40, "obj +0x40");
static_assert(kObjField08Off == 0x8, "obj +0x8");
static_assert(kObjField88Off == 0x88, "obj +0x88");
static_assert(kObjField90Off == 0x90, "obj +0x90");
static_assert(kObjField98Off == 0x98, "obj +0x98");
static_assert(kOut30Off == 0x30, "out +0x30");

extern "C" void* sub_e83b8c0(void* a0, void* a1, unsigned long long a2);

} // namespace native
