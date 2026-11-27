#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_66a1820 (0x66a1820, size 0x36, 1.26.62.01, "Item group visitor").
//
//   0x66a1820  sub rsp,0x28                                  ; prologue / 0x28 byte home stack
//   0x66a1824  mov rax,[rdx]                                 ; R a1+0x0
//   0x66a1827  cmp rax,0xFFFFFFFFFFFFFFFF
//   0x66a182b  je short 0x66A1850                            ; fail: a1+0x0 == -1, nothing written
//   0x66a182d  mov rdx,[rdx+8]                               ; R a1+0x8
//   0x66a1831  mov [rcx],rax                                 ; W a0+0x0 = a1+0x0
//   0x66a1834  mov [rcx+8],rdx                               ; W a0+0x8 = a1+0x8
//   0x66a1838  test rdx,rdx
//   0x66a183b  setne dl                                      ; dl = (a1+0x8 != 0)
//   0x66a183e  test rax,rax
//   0x66a1841  sete al                                       ; al = (a1+0x0 == 0)
//   0x66a1844  or al,dl                                      ; al = (a1+0x0 == 0) || (a1+0x8 != 0)
//   0x66a1846  je short 0x66a1850                            ; fail: a1+0x0 != 0 && a1+0x8 == 0
//   0x66a1848  mov rax,rcx                                   ; return a0
//   0x66a184b  add rsp,0x28
//   0x66a184f  ret
//   0x66a1850  call 0x78ED0                                  ; sub_78ed0, class crt boundary
//   0x66a1855  int3                                          ; unreachable
//
// x64 Microsoft ABI: RCX = a0 (out pair), RDX = a1 (source pair), RAX = return value (a0 on
// the success path). Reads a1+0x0 and a1+0x8, writes a0+0x0 and a0+0x8 in the same order;
// on either failure path calls sub_78ed0 (class crt, docs/data/native_boundary.tsv) with
// RCX = a0 (rcx is untouched between entry and either call site) [V]. sub_78ed0 is noreturn
// (`sub rsp,0x28 / call qword ptr [0xF9A8CF0]` then int3 padding at 0x78ed0 [V]), so the
// int3 at 0x66a1855 is never reached. No null guard or SEH exists in the original (none
// added here).
//
// The function touches two unnamed 8-byte fields of a 16-byte pair object, at +0x0 and +0x8.
// No game struct type is identifiable from the disassembly; the layout below mirrors exactly
// those two fields and nothing more. Every offset is [V] from 0x66a1820..0x66a1856.

static constexpr std::size_t kPairOffset0 = 0x0;
static constexpr std::size_t kPairOffset8 = 0x8;
static constexpr std::size_t kPairSize = 0x10;

struct PairU64 {
    std::uint64_t first;  // +0x0: read from a1+0x0, written to a0+0x0 [V]
    std::uint64_t second; // +0x8: read from a1+0x8, written to a0+0x8 [V]
};

static_assert(offsetof(PairU64, first) == kPairOffset0,
              "sub_66a1820: pair+0x0 is read from a1+0x0 and written to a0+0x0");
static_assert(offsetof(PairU64, second) == kPairOffset8,
              "sub_66a1820: pair+0x8 is read from a1+0x8 and written to a0+0x8");
static_assert(sizeof(PairU64) == kPairSize,
              "sub_66a1820: pair object is 16 bytes");

namespace native {

// Exact x64 Microsoft ABI mirror of the original: RCX = a0, RDX = a1, RAX = return value.
uint64_t* sub_66a1820(uint64_t* a0, uint64_t* a1);

} // namespace native
