#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_567bfe0 (0x567bfe0, size 0xbd, 1.26.62.01, "VV frame-graph builder").
//
// Full instruction-by-instruction reversal:
//   0x567bfe0  push rsi                                              ; prologue, callee-saved scratch
//   0x567bfe1  mov rax,r8                                            ; rax = dst (a2)
//   0x567bfe4  cmp rcx,rdx                                           ; src(a0) vs end(a1)
//   0x567bfe7  je 0x567C09B                                           ; if src == end, return
//   0x567bfed  add rcx,0x28                                          ; rcx = src + 0x28 (working cursor)
//   0x567bff1  lea r8,[0xF25CF78]                                    ; jump table base (data_f25cf78)
//   0x567bff8  xorps xmm0,xmm0                                       ; xmm0 = 0
//   0x567bffd  nop [rax]                                             ; padding (unreachable)
//   0x567bffb  jmp short 0x567C046                                   ; loop top
//   0x567c046  movups xmm1,[rcx-0x28]                                ; dst+0x00 = chunk+0x00 (16 B)
//   0x567c04a  movups [rax],xmm1
//   0x567c04d  mov byte ptr [rax+0x30],0xFF                          ; dst+0x30 = 0xFF (tentative)
//   0x567c051  movzx r9d,byte ptr [rcx+8]                            ; index = chunk+0x30
//   0x567c056  cmp r9,6
//   0x567c05a  ja short 0x567C020                                    ; index > 6: skip table path
//   0x567c05c  lea r10,[rax+0x10]                                    ; r10 = dst+0x10
//   0x567c060  lea r11,[rcx-0x18]                                    ; r11 = chunk+0x10
//   0x567c064  movsxd rsi,[r8+r9*4]                                  ; table entry (int32)
//   0x567c068  add rsi,r8                                            ; target = table + entry
//   0x567c06b  jmp rsi                                               ; tail jump to inline target
//     index 0..2 -> 0x567c000: dst+0x10=chunk+0x10(16B), dst+0x20=chunk+0x20(16B),
//                          zero chunk+0x18(8B), zero chunk+0x20(16B)
//     index 3    -> 0x567c06D: dst+0x10=chunk+0x10(16B), dst+0x20=chunk+0x20(16B)
//     index 4    -> 0x567c081: dst+0x10=chunk+0x10(2B)
//     index 5    -> 0x567c08B: dst+0x10=chunk+0x10(4B)
//     index 6    -> 0x567c093: dst+0x10=chunk+0x10(8B)
//   0x567c01c  mov [rax+0x30],r9b                                    ; dst+0x30 = index
//   0x567c020  lea r9,[rcx-0x28]                                     ; r9 = chunk
//   0x567c024  movzx r10d,byte ptr [r9+0x40]                         ; dst+0x40 = chunk+0x40 (1 B)
//   0x567c029  mov [rax+0x40],r10b
//   0x567c02d  mov r10,[r9+0x38]                                     ; dst+0x38 = chunk+0x38 (8 B)
//   0x567c031  mov [rax+0x38],r10
//   0x567c035  add rax,0x48                                          ; dst += 0x48
//   0x567c039  add rcx,0x48                                          ; chunk += 0x48
//   0x567c03d  add r9,0x48                                           ; r9 = next chunk
//   0x567c041  cmp r9,rdx
//   0x567c044  je short 0x567C09B                                    ; if next chunk == end, return
//   0x567c09b  pop rsi                                               ; epilogue
//   0x567c09c  ret
//
// x64 Microsoft ABI: RCX = src, RDX = end, R8 = dst. R9 (4th argument) is
// unused by this function [V]. Return: void.
//
// Layout of the 0x48-byte record processed per iteration (chunk = rcx-0x28) [V]:
//   dst+0x00 (16 B)  = chunk+0x00
//   dst+0x10         = chunk+0x10 (size depends on index byte at chunk+0x30)
//   dst+0x20         = chunk+0x20 (16 B, only when index <= 2)
//   chunk+0x18 (8 B) = 0           (only when index <= 2)
//   chunk+0x20 (16 B)= 0           (only when index <= 2)
//   dst+0x30 (1 B)   = index (0..6), else 0xFF
//   dst+0x38 (8 B)   = chunk+0x38
//   dst+0x40 (1 B)   = chunk+0x40
//   loop until (chunk + 0x48) == end
//
// Callees: none. The table at data_f25cf78 is an inline switch dispatch
// (all targets are within this function); there are no `call` instructions
// and no boundary calls [V].

// Offset constants for the 0x48-byte record [V].
static constexpr std::size_t kRecField0x00 = 0x00;
static constexpr std::size_t kRecField0x10 = 0x10;
static constexpr std::size_t kRecField0x18 = 0x18;
static constexpr std::size_t kRecField0x20 = 0x20;
static constexpr std::size_t kRecField0x30 = 0x30;
static constexpr std::size_t kRecField0x38 = 0x38;
static constexpr std::size_t kRecField0x40 = 0x40;
static constexpr std::size_t kRecSize = 0x48;

// Source record layout (read per iteration, partly written when index <= 2).
struct sub_567bfe0_src {
    std::uint8_t field0x00[16];     // +0x00  16 bytes -> dst+0x00
    std::uint8_t field0x10[8];      // +0x10  8 bytes  (part of -> dst+0x10 region)
    std::uint8_t field0x18[8];      // +0x18  8 bytes  zeroed when index <= 2
    std::uint8_t field0x20[16];     // +0x20  16 bytes -> dst+0x20; zeroed when index <= 2
    std::uint8_t index0x30;         // +0x30  index byte (0..6)
    std::uint8_t pad0x31[7];
    std::uint8_t field0x38[8];      // +0x38  8 bytes -> dst+0x38
    std::uint8_t field0x40;         // +0x40  1 byte  -> dst+0x40
    std::uint8_t pad0x41[7];
};

// Destination record layout (written per iteration).
struct sub_567bfe0_dst {
    std::uint8_t field0x00[16];     // +0x00  16 bytes
    std::uint8_t field0x10[16];     // +0x10  up to 16 bytes
    std::uint8_t field0x20[16];     // +0x20  16 bytes
    std::uint8_t field0x30;         // +0x30  index byte or 0xFF
    std::uint8_t pad0x31[7];
    std::uint8_t field0x38[8];      // +0x38  8 bytes
    std::uint8_t field0x40;         // +0x40  1 byte
    std::uint8_t pad0x41[7];
};

struct sub_567bfe0Layout {
    static_assert(offsetof(sub_567bfe0_src, field0x00) == kRecField0x00,
                  "sub_567bfe0_src: field0x00 at +0x00");
    static_assert(offsetof(sub_567bfe0_src, field0x10) == kRecField0x10,
                  "sub_567bfe0_src: field0x10 at +0x10");
    static_assert(offsetof(sub_567bfe0_src, field0x18) == kRecField0x18,
                  "sub_567bfe0_src: field0x18 at +0x18");
    static_assert(offsetof(sub_567bfe0_src, field0x20) == kRecField0x20,
                  "sub_567bfe0_src: field0x20 at +0x20");
    static_assert(offsetof(sub_567bfe0_src, index0x30) == kRecField0x30,
                  "sub_567bfe0_src: index0x30 at +0x30");
    static_assert(offsetof(sub_567bfe0_src, field0x38) == kRecField0x38,
                  "sub_567bfe0_src: field0x38 at +0x38");
    static_assert(offsetof(sub_567bfe0_src, field0x40) == kRecField0x40,
                  "sub_567bfe0_src: field0x40 at +0x40");
    static_assert(offsetof(sub_567bfe0_dst, field0x00) == kRecField0x00,
                  "sub_567bfe0_dst: field0x00 at +0x00");
    static_assert(offsetof(sub_567bfe0_dst, field0x10) == kRecField0x10,
                  "sub_567bfe0_dst: field0x10 at +0x10");
    static_assert(offsetof(sub_567bfe0_dst, field0x20) == kRecField0x20,
                  "sub_567bfe0_dst: field0x20 at +0x20");
    static_assert(offsetof(sub_567bfe0_dst, field0x30) == kRecField0x30,
                  "sub_567bfe0_dst: field0x30 at +0x30");
    static_assert(offsetof(sub_567bfe0_dst, field0x38) == kRecField0x38,
                  "sub_567bfe0_dst: field0x38 at +0x38");
    static_assert(offsetof(sub_567bfe0_dst, field0x40) == kRecField0x40,
                  "sub_567bfe0_dst: field0x40 at +0x40");
    static_assert(sizeof(sub_567bfe0_src) == kRecSize,
                  "sub_567bfe0_src: size is 0x48");
    static_assert(sizeof(sub_567bfe0_dst) == kRecSize,
                  "sub_567bfe0_dst: size is 0x48");
    static_assert(sizeof(void*) == 8, "sub_567bfe0: x64 pointers are 8 bytes");
};

namespace native {

// sub_567bfe0(unsigned char* src, unsigned char* end, unsigned char* dst) -> void
void sub_567bfe0(unsigned char* src, unsigned char* end, unsigned char* dst);

} // namespace native
