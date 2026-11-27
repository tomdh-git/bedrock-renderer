#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_ebcf430 (0xebcf430, size 0x2a, 1.26.62.01): the first 0x2a bytes of the
// function ([0xebcf430, 0xebcf45a)), i.e. prologue, register reassignment and the
// branch on RCX. No game struct field is touched; the function only spills the
// incoming callee-saved registers to its own stack frame.
//
// Frame layout, with RSP after `sub rsp,0x40` as the frame base (the stores at
// 0xebcf430..0xebcf43a target [entry RSP+0x10..0x20] = [base+0x58..0x68], and the
// push at 0xebcf43f targets [entry RSP-8] = [base+0x40]):
//   base+0x40  r14 save    0xebcf43f  push r14
//   base+0x58  rbp save    0xebcf430  mov [rsp+0x10],rbp
//   base+0x60  rsi save    0xebcf435  mov [rsp+0x18],rsi
//   base+0x68  rdi save    0xebcf43a  mov [rsp+0x20],rdi
struct SubEbcf430Frame {
    std::uint8_t pad0[0x40];
    std::uintptr_t r14_save;   // offset 0x40
    std::uint8_t pad1[0x10];
    void* rbp_save;            // offset 0x58
    void* rsi_save;            // offset 0x60
    void* rdi_save;            // offset 0x68
};
static_assert(sizeof(SubEbcf430Frame) == 0x70, "sub_ebcf430: prologue frame is 0x70 bytes");
static_assert(offsetof(SubEbcf430Frame, r14_save) == 0x40, "sub_ebcf430: r14 save slot at [RSP+0x40]");
static_assert(offsetof(SubEbcf430Frame, rbp_save) == 0x58, "sub_ebcf430: rbp save slot at [RSP+0x58]");
static_assert(offsetof(SubEbcf430Frame, rsi_save) == 0x60, "sub_ebcf430: rsi save slot at [RSP+0x60]");
static_assert(offsetof(SubEbcf430Frame, rdi_save) == 0x68, "sub_ebcf430: rdi save slot at [RSP+0x68]");
static_assert(sizeof(void*) == 8, "sub_ebcf430: x64 ABI, 8-byte registers");
static_assert(sizeof(int32_t) == 4, "sub_ebcf430: 32-bit return value in EAX");

// Signature of sub_ebcf430 itself: x64 Microsoft ABI.
//   RCX = a1: pointer/handle argument, tested for null (0xebcf455  test rcx,rcx)
//   RDX = a2: int32 argument (consumed just past this range, at 0xebcf45f  movsxd rbx,edx)
//   R8  = a3: pointer argument, copied to RBP (0xebcf448  mov rbp,r8)
//   R9  = a4: pointer argument, copied to RSI (0xebcf445  mov rsi,r9)
//   Return: int32 in EAX; the return instruction (0xebcf4df  ret) lies outside
//   [0xebcf430, 0xebcf45a) and belongs to later ranges of sub_ebcf430.
extern "C" int32_t sub_ebcf430(void* a1, int32_t a2, void* a3, void* a4);

} // namespace native
