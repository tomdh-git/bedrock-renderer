#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_66a17c0 (0x66a17c0, size 0x51, 1.26.62.01, "Item group visitor").
//
//   0x66a17c0  sub rsp,0x28                                  ; prologue / 0x28 byte home stack
//   0x66a17c4  mov r8,[rdx]                                 ; R a1+0x0  (start)
//   0x66a17c7  mov rax,[rdx+8]                              ; R a1+0x8  (end)
//   0x66a17cb  mov rdx,rax                                  
//   0x66a17ce  sub rdx,r8                                   ; rdx = end - start (diff)
//   0x66a17d1  mov r9,rdx                                   
//   0x66a17d4  sar r9,4                                     ; r9 = diff / 16 (arithmetic)
//   0x66a17d8  mov r10,0xAAAAAAAAAAAAAAAB                   
//   0x66a17e2  imul r10,r9                                  ; r10 = magic * r9 (low 64)
//   0x66a17e6  mov [rcx],r10                                ; W a0+0x0 = scaled
//   0x66a17e9  cmp rdx,0xFFFFFFFFFFFFFFD0                   
//   0x66a17ed  je short 0x66A180B                            ; fail: diff == -48
//   0x66a17ef  mov [rcx+8],r8                               ; W a0+0x8 = start
//   0x66a17f3  test r8,r8                                   ; setne dl = (start != 0)
//   0x66a17f6  setne dl                                     
//   0x66a17f9  test rax,rax                                 ; sete al = (end == 0)
//   0x66a17fc  sete al                                      
//   0x66a17ff  or al,dl                                     ; al = (end==0) || (start!=0)
//   0x66a1801  je short 0x66a180B                            ; fail: start==0 && end!=0
//   0x66a1803  mov rax,rcx                                  ; return a0
//   0x66a1806  add rsp,0x28                                 
//   0x66a180a  ret                                         
//   0x66a180b  call 0x78ED0                                 ; sub_78ed0, class crt boundary
//   0x66a1810  int3                                          ; unreachable
//
// x64 Microsoft ABI: RCX = a0 (out pair), RDX = a1 (source pair), RAX = return
// value (a0 on the success path). Reads a1+0x0 and a1+0x8, writes a0+0x0 then
// a0+0x8 in the same order; on either failure path calls sub_78ed0 (class crt,
// docs/data/native_boundary.tsv line 11) with RCX = a0 (rcx is untouched
// between entry and either call site) [V]. sub_78ed0 is noreturn
// (`sub rsp,0x28 / call qword ptr [0xF9A8CF0]` then int3 padding at 0x78ed0
// [V]), so the int3 at 0x66a1810 is unreachable. No null guard or SEH exists
// in the original (none added here).
//
// The function touches two unnamed 8-byte fields of a 16-byte pair object, at
// +0x0 and +0x8, on both the source (a1) and the destination (a0). No game
// struct type is identifiable from the disassembly; the layout below mirrors
// exactly those two fields and nothing more. Every offset is [V] from
// 0x66a17c0..0x66a1811.

static constexpr std::size_t kPairOffset0 = 0x0;
static constexpr std::size_t kPairOffset8 = 0x8;
static constexpr std::size_t kPairSize = 0x10;

struct PairU64 {
    std::uint64_t first;  // +0x0: a1+0x0 read (start); a0+0x0 written (scaled count)
    std::uint64_t second; // +0x8: a1+0x8 read (end);   a0+0x8 written (start)
};

static_assert(offsetof(PairU64, first) == kPairOffset0,
              "sub_66a17c0: pair+0x0 is read from a1+0x0 and a0+0x0 is written");
static_assert(offsetof(PairU64, second) == kPairOffset8,
              "sub_66a17c0: pair+0x8 is read from a1+0x8 and a0+0x8 is written");
static_assert(sizeof(PairU64) == kPairSize,
              "sub_66a17c0: pair object is 16 bytes");

namespace native {

// Exact x64 Microsoft ABI mirror of the original: RCX = a0, RDX = a1, RAX = return value.
uint64_t* sub_66a17c0(uint64_t* a0, uint64_t* a1);

} // namespace native
