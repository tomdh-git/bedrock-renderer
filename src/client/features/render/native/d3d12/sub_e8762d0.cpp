// LIFT 0xe8762d0 size 0x74 1.26.62.01 sub_e8762d0
#include "sub_e8762d0.h"
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/boundary.h"

#include <cstdint>

namespace native { namespace d3d12 {

extern "C" void* sub_e8762d0(void* a0) {
    // 0xe8762d0..0xe8762e2
    // prologue: push rbp; push rsi; sub rsp,0x38; lea rbp,[rsp+0x30]
    // 0xe8762e3..0xe8762f5
    // xorps xmm0,xmm0; movups [rcx+0x20],xmm0; movups [rcx+0x10],xmm0; mov [rbp-8],rcx; movups [rcx],xmm0
    for (int i = 0; i < 4; ++i) {
        *reinterpret_cast<std::uint64_t*>(static_cast<char*>(a0) + i * 8) = 0; // 0xe8762e6/0xe8762ea/0xe8762f2
    }

    // 0xe8762f5..0xe876308
    // rcx = [0x1233E1A8]; rax = [rcx]; rax = [rax+8]; edx = 0x50; call qword ptr [0xF99FFA0]  (data slot -> sub_eea6040)
    using FnSlot = void* (*)(void* rcx, std::uint32_t edx);
    std::uintptr_t rcxv = *reinterpret_cast<std::uintptr_t*>(0x1233E1A8);
    std::uintptr_t raxv = *reinterpret_cast<std::uintptr_t*>(rcxv);
    raxv = *reinterpret_cast<std::uintptr_t*>(raxv + 8);
    void* rsi = reinterpret_cast<FnSlot>(raxv)(reinterpret_cast<void*>(rcxv), 0x50); // 0xe876308 call qword ptr [0xF99FFA0]

    // 0xe87630e..0xe876315
    // nop; mov rsi,rax; test rax,rax; je 0xe876337
    if (rsi == nullptr) {
        // 0xe876337..0xe876342
        // mov ecx,0x50; call 0x9BC830; nop; jmp 0xe876317
        rsi = boundary::alloc(0x50); // 0xe87633c  call 0x9BC830
    }

    // 0xe876317..0xe876336
    // mov [rsi],rsi; mov [rsi+8],rsi; mov [rsi+0x10],rsi; mov word ptr [rsi+0x18],0x101; mov rax,[rbp-8]; mov [rax+0x20],rsi; epilogue
    *reinterpret_cast<void**>(rsi) = rsi;                       // 0xe876317
    *reinterpret_cast<void**>(static_cast<char*>(rsi) + 8) = rsi;  // 0xe87631a
    *reinterpret_cast<void**>(static_cast<char*>(rsi) + 0x10) = rsi; // 0xe87631e
    *reinterpret_cast<std::uint16_t*>(static_cast<char*>(rsi) + 0x18) = 0x0101; // 0xe876322
    *reinterpret_cast<void**>(static_cast<char*>(a0) + 0x20) = rsi; // 0xe87632c

    return a0; // 0xe876336 ret (rax = [rbp-8])
}

#if 0
0xe8762d0  push rbp
0xe8762d1  push rsi
0xe8762d2  sub rsp,0x38
0xe8762d6  lea rbp,[rsp+0x30]
0xe8762db  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
0xe8762e3  xorps xmm0,xmm0
0xe8762e6  movups [rcx+0x20],xmm0
0xe8762ea  movups [rcx+0x10],xmm0
0xe8762ee  mov [rbp-8],rcx
0xe8762f2  movups [rcx],xmm0
0xe8762f5  mov rcx,[0x1233E1A8]
0xe8762fc  mov rax,[rcx]
0xe8762ff  mov rax,[rax+8]
0xe876303  mov edx,0x50
0xe876308  call qword ptr [0xF99FFA0]
0xe87630e  nop
0xe87630f  mov rsi,rax
0xe876312  test rax,rax
0xe876315  je short 0xE876337
0xe876317  mov [rsi],rsi
0xe87631a  mov [rsi+8],rsi
0xe87631e  mov [rsi+0x10],rsi
0xe876322  mov word ptr [rsi+0x18],0x101
0xe876328  mov rax,[rbp-8]
0xe87632c  mov [rax+0x20],rsi
0xe876330  add rsp,0x38
0xe876334  pop rsi
0xe876335  pop rbp
0xe876336  ret
0xe876337  mov ecx,0x50
0xe87633c  call 0x9BC830
0xe876341  nop
0xe876342  jmp short 0xE876317
#endif

static_assert(kOff_0x00 == 0x00, "off 0x00");
static_assert(kOff_0x10 == 0x10, "off 0x10");
static_assert(kOff_0x20 == 0x20, "off 0x20");
// Registry entry
LIFT_FN(sub_e8762d0, "BgfxFrameBuilder slot 16", 0xe8762d0, sub_e8762d0, nullptr);

} } // namespace native::d3d12