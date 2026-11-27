#pragma once

#include <cstddef>
#include <cstdint>

namespace native {

// Layout recovered from the disassembly of 0xbc7a9d0 (size 0x5e3,

// 0xbc7a9d0..0xbc7afb3, sub_bc7a9d0, 1.26.62.01; instruction offsets cited

// in sub_bc7a9d0.cpp). The structs are layout overlays only: no object of

// these types is instantiated here.

//

// Frame (frame base = rsp after the prologue; the 0x20 bytes below it are

// home space / callee-saved save area):

//   +0x0000 (rsp+0x20 absolute)  u32 counters[0x800]  radix counting bins,

//                                0x2000 bytes, cleared per pass

//   +0x2000                      u64 cookie            stack cookie = [0x1230A0C0] ^ rsp

// Probe size: 0x2028 (mov eax,0x2028; call sub_e9e7970; sub rsp,rax).

struct Bc7a9d0Frame {
    std::uint32_t counters[0x800];  // +0x0000 relative to frame base

    std::uint64_t  cookie;          // +0x2000 relative to frame base

};                                  // sizeof == 0x2008

static_assert(offsetof(Bc7a9d0Frame, counters) == 0x0000u, "sub_bc7a9d0: counters at frame base");
static_assert(offsetof(Bc7a9d0Frame, cookie) == 0x2000u, "sub_bc7a9d0: cookie at +0x2000");
static_assert(sizeof(Bc7a9d0Frame) == 0x2008u, "sub_bc7a9d0: frame size");

// Read-only data referenced by the function [V]:

static constexpr std::uintptr_t native::kGblCookie = 0x1230A0C0u;  // [data_1230a0c0] stack cookie secret


// Loop/frame constants [V]:

static constexpr std::uint32_t kCounterBins = 0x800u;   // 2048 u32 counting bins

static constexpr std::uint32_t kCounterBytes = 0x2000u; // memset size per pass (0x800 * 4)

static constexpr std::uint32_t kStackSize = 0x2028u;    // stack probe request size (mov eax,0x2028)


// Radix digits per pass [V] (three-pass LSD radix sort over u32 keys with a

// parallel u32 array; counting sort is stable per pass):

//   pass 1: key & 0x7FF                    keys + parIn  -> workKeys + parOut

//   pass 2: (key >> 9) & 0x1FFC            workKeys + parOut -> keys + parIn

//                                          (the listing addresses bins by byte offset;

//                                           the equivalent u32 bin is (key >> 9) & 0x7FF)

//   pass 3: key >> 22                      keys + parIn  -> workKeys + parOut

static constexpr std::uint32_t kDigitMaskA = 0x7FFu;
static constexpr std::uint32_t kDigitMaskB = 0x1FFCu;  // byte-offset form; u32 bin == (key >> 9) & 0x7FF


// x64 Microsoft ABI: rcx = keys, rdx = workKeys, r8 = parIn, r9 = parOut;

// the 5th (stack) argument is count. Return: void (none observed).

extern "C" void sub_bc7a9d0(std::uint32_t* keys, std::uint32_t* workKeys,
                            std::uint32_t* parIn, std::uint32_t* parOut,
                            std::uint32_t count);

// Calls out of 0xbc7a9d0, all verbatim from the listing:

//   0xbc7a9e1  call 0xE9E7970   -> sub_e9e7970   (boundary crt, __chkstk-style probe,

//                                                 eax = 0x2028, then sub rsp,rax)

//   0xbc7aa1b  call 0xEBCE430   -> sub_ebce430   (lift forwarder: 0xebce430 =

//                                                 "movzx edx,dl; jmp 0xEEC6ED0",

//                                                 target 0xEEC6ED0 = crt IAT memset thunk;

//                                                 all three calls pass fill 0, i.e.

//                                                 std::memset(counters, 0, 0x2000))

//   0xbc7abb8  call 0xEBCE430   (idem)

//   0xbc7ad50  call 0xEBCE430   (idem)

//   0xbc7aed0  call 0xEBCE390   -> sub_ebce390   (lift, 0xebce390 = jmp 0xEEC6EC0;

//                                                 memcpy(keys, workKeys, count*4))

//   0xbc7afad  call 0xE951550   -> sub_e951550  (boundary crt, stack-cookie failure,

//                                                 noreturn)

// sub_ebce430 is not in docs/data/native_functions.tsv or native_boundary.tsv; it is a

// 5-byte forwarder (docs/OPENCODE_BRIEF.md rule 69) whose target is a crt boundary,

// so the lifted code replaces the three calls with the std::memset intrinsic they

// tail-call (allowed library intrinsic, docs/RENDER_NATIVE_SPEC.md section 5).

extern "C" void sub_ebce390(void* dst, const void* src, std::uint64_t n);

// Footprint (V2 differential): every region the function writes, directly or via its

// calls. Stack locals are not snapshotted (same frame on both runs).

native::Footprint sub_bc7a9d0_footprint(std::uint32_t* keys, std::uint32_t* workKeys,
                                        std::uint32_t* parIn, std::uint32_t* parOut,
                                        std::uint32_t count);

} // namespace native

