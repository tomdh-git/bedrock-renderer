// LIFT 0xe87bb00 size 0x1ac 1.26.62.01 BgfxFrameBuilder::endFrame
#include "client/features/render/native/d3d12/sub_e87bb00.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstdlib>

namespace native {

// Layout assertion for the struct used by this function [V]:
static_assert(kEndFrameLastOffset - kEndFrameFirstOffset == 0x08,
              "e87bb00: last follows first at +0x48");

extern "C" void sub_e87bb00(void* self)
{
    // 0xe87bb00..0xe87bb0b
    // push r15; push r14; push rsi; push rdi; push rbx; sub rsp,0x40
    // movaps [rsp+0x30],xmm6
    std::uint8_t* obj = static_cast<std::uint8_t*>(self);

    // All registers used by the lifted body (declared here so gotos can skip initialisation):
    void*  rdi = nullptr;   // entry cursor
    void*  rbx = nullptr;   // end sentinel
    void*  rax = nullptr;   // scratch / node pointer
    void*  rcx = nullptr;   // scratch / link addr
    void*  rdx = nullptr;   // scratch / allocator begin
    void*  rsi = nullptr;   // node cursor (unlink chain)
    void*  r8 = nullptr;    // scratch / fill cursor
    void*  r14 = nullptr;   // next node in unlink chain
    std::uint8_t* r15 = nullptr; // &rsi+0x20
    std::uintptr_t r9 = 0;  // allocator size
    std::uintptr_t r10 = 0; // rounded count
    std::uintptr_t r11 = 0; // fill index
    std::uintptr_t rdx_val = 0; // computed size delta
    std::uintptr_t blockSize = 0; // heap block size
    std::uintptr_t rcx_adj = 0;   // adjusted rcx
    void* rax2 = nullptr;   // heap block header
    std::uint64_t patternVal = 0; // broadcast fill pattern

    // 0xe87bb10..0xe87bb1b
    // mov rdi,[rcx+0x40]; mov rbx,[rcx+0x48]; cmp rdi,rbx
    rdi = *reinterpret_cast<void**>(obj + 0x40);
    rbx = *reinterpret_cast<void**>(obj + 0x48);

    // 0xe87bb18: cmp rdi,rbx
    if (rdi == rbx) {
        // 0xe87bb1b: je 0xE87BC81
        goto epilogue;
    }

    // 0xe87bb21..0xe87bb26
    // xorps xmm6,xmm6; jmp short 0xE87BB40; nop [rax+rax]
    // 0xe87bb24: jmp short 0xE87BB40
    goto loop_test;

loop_body:
    // 0xe87bb30..0xe87bb3a
    // add rdi,0x88; cmp rdi,rbx; je 0xE87BC81
    rdi = static_cast<std::uint8_t*>(rdi) + 0x88;

loop_test:
    // 0xe87bb37: cmp rdi,rbx
    if (rdi == rbx) {
        // 0xe87bb3a: je 0xE87BC81
        goto epilogue;
    }

    // 0xe87bb40..0xe87bb5c
    // cmp qword ptr [rdi+0x58],0; je short 0xE87BB30
    // mov rax,[rdi+0x50]; mov rcx,[rax+8]; mov qword ptr [rcx],0
    // mov rsi,[rax]; test rsi,rsi; jne short 0xE87BBCA
    if (*reinterpret_cast<std::uint64_t*>(static_cast<std::uint8_t*>(rdi) + 0x58) == 0) {
        // 0xe87bb45: je short 0xE87BB30
        goto loop_body;
    }

    // 0xe87bb47: mov rax,[rdi+0x50]
    rax = *reinterpret_cast<void**>(static_cast<std::uint8_t*>(rdi) + 0x50);
    // 0xe87bb4b: mov rcx,[rax+8]
    rcx = *reinterpret_cast<void**>(static_cast<std::uint8_t*>(rax) + 8);
    // 0xe87bb4f: mov qword ptr [rcx],0
    *reinterpret_cast<void**>(rcx) = nullptr;
    // 0xe87bb56: mov rsi,[rax]
    rsi = *reinterpret_cast<void**>(rax);

    // 0xe87bb59: test rsi,rsi
    if (rsi != nullptr) {
        // 0xe87bb5c: jne short 0xE87BBCA
        goto unlink_node;
    }

    // ----- single node path (rsi == 0) -----
    // 0xe87bb5e..0xe87bb7c
    // mov rax,[rdi+0x50]; mov [rax],rax; mov [rax+8],rax
    // mov qword ptr [rdi+0x58],0; mov rdx,[rdi+0x60]; mov rax,[rdi+0x68]
    // cmp rdx,rax; je short 0xE87BB30
single_node:
    // 0xe87bb5e: mov rax,[rdi+0x50]
    rax = *reinterpret_cast<void**>(static_cast<std::uint8_t*>(rdi) + 0x50);
    // 0xe87bb62: mov [rax],rax
    *reinterpret_cast<void**>(rax) = rax;
    // 0xe87bb65: mov [rax+8],rax
    *reinterpret_cast<void**>(static_cast<std::uint8_t*>(rax) + 8) = rax;
    // 0xe87bb69: mov qword ptr [rdi+0x58],0
    *reinterpret_cast<std::uint64_t*>(static_cast<std::uint8_t*>(rdi) + 0x58) = 0;
    // 0xe87bb71: mov rdx,[rdi+0x60]
    rdx = *reinterpret_cast<void**>(static_cast<std::uint8_t*>(rdi) + 0x60);
    // 0xe87bb75: mov rax,[rdi+0x68]
    rax = *reinterpret_cast<void**>(static_cast<std::uint8_t*>(rdi) + 0x68);
    // 0xe87bb79: cmp rdx,rax
    if (rdx == rax) {
        // 0xe87bb7c: je short 0xE87BB30
        goto loop_body;
    }
    // 0xe87bb7e..0xe87bb9e
    // mov rcx,[rdi+0x50]; mov r9,rax; sub r9,rdx; add r9,0xFFFFFFFFFFFFFFF8
    // cmp r9,0x18; jae 0xE87BC25; mov r8,rdx; jmp 0xE87BC70; nop [rax+rax]
    rcx = *reinterpret_cast<void**>(static_cast<std::uint8_t*>(rdi) + 0x50);
    // 0xe87bb82: mov r9,rax;  0xe87bb85: sub r9,rdx;  0xe87bb88: add r9,0xFFFFFFFFFFFFFFF8
    r9 = (std::uintptr_t)rax - (std::uintptr_t)rdx - 8;
    // 0xe87bb8c: cmp r9,0x18
    if (r9 >= 0x18) {
        // 0xe87bb90: jae 0xE87BC25
        goto shrink;
    }
    // 0xe87bb96: mov r8,rdx
    r8 = rdx;
    // 0xe87bb99: jmp 0xE87BC70
    goto fill_simple;

    // ----- unlink path (rsi != 0) -----
    // 0xe87bbca..0xe87bbd9
    // mov r14,[rsi]; mov rax,[rsi+0x38]; lea rcx,[rsi+0x38]
    // mov r8,[rax+8]; mov rdx,rcx; call 0x1F5EF50
unlink_node:
    // 0xe87bbca: mov r14,[rsi]
    r14 = *reinterpret_cast<void**>(rsi);
    // 0xe87bbcd: mov rax,[rsi+0x38]
    rax = *reinterpret_cast<void**>(static_cast<std::uint8_t*>(rsi) + 0x38);
    // 0xe87bbd1: lea rcx,[rsi+0x38]
    void* rcx_link = static_cast<std::uint8_t*>(rsi) + 0x38;
    // 0xe87bbd5: mov r8,[rax+8]
    r8 = *reinterpret_cast<void**>(static_cast<std::uint8_t*>(rax) + 8);
    // 0xe87bbd9: mov rdx,rcx
    void* rdx_unlink = rcx_link;
    // 0xe87bbdc: call 0x1F5EF50  (stl boundary)
    Boundary<void, void*, void*, void*>{"sub_1f5ef50"}(rcx_link, rdx_unlink, r8);
    // 0xe87bbe1..0xe87bbe5
    // mov rcx,[rsi+0x38]; mov edx,0x50
    rcx = *reinterpret_cast<void**>(static_cast<std::uint8_t*>(rsi) + 0x38);
    // 0xe87bbea: call 0xE935700  (lift)
    sub_e935700(rcx, 0x50);
    // 0xe87bbef..0xe87bc20
    // mov rcx,[rsi+0x20]; test rcx,rcx; je short 0xE87BBB5
    // mov rdx,[rsi+0x30]; sub rdx,rcx; cmp rdx,0x1000
    // jb short 0xE87BBA0; mov rax,[rcx-8]; add rcx,0xFFFFFFFFFFFFFFF8
    // sub rcx,rax; cmp rcx,0x20; jae short 0xE87BC92
    // add rdx,0x27; mov rcx,rax; jmp 0xE87BBA0
    rcx = *reinterpret_cast<void**>(static_cast<std::uint8_t*>(rsi) + 0x20);
    // 0xe87bbf3: test rcx,rcx
    if (rcx == nullptr) {
        // 0xe87bbf6: je short 0xE87BBB5
        goto free_48;
    }
    // 0xe87bbf8: mov rdx,[rsi+0x30]
    rdx = *reinterpret_cast<void**>(static_cast<std::uint8_t*>(rsi) + 0x30);
    // 0xe87bbfc: sub rdx,rcx
    rdx_val = (std::uintptr_t)rdx - (std::uintptr_t)rcx;
    // 0xe87bbff: cmp rdx,0x1000
    if (rdx_val < 0x1000) {
        // 0xe87bc06: jb short 0xE87BBA0
        goto bba0_small;
    }
    // 0xe87bc08: mov rax,[rcx-8]
    rax2 = *reinterpret_cast<void**>(static_cast<std::uint8_t*>(rcx) - 8);
    // 0xe87bc0c: add rcx,0xFFFFFFFFFFFFFFF8
    rcx_adj = (std::uintptr_t)rcx - 8;
    // 0xe87bc10: sub rcx,rax
    blockSize = rcx_adj - (std::uintptr_t)rax2;
    // 0xe87bc13: cmp rcx,0x20
    if (blockSize >= 0x20) {
        // 0xe87bc17: jae short 0xE87BC92
        goto error_path;
    }
    // 0xe87bc19: add rdx,0x27
    rdx_val += 0x27;
    // 0xe87bc1d: mov rcx,rax
    rcx_adj = (std::uintptr_t)rax2;
    // 0xe87bc20: jmp 0xE87BBA0
    goto bba0;

bba0_small:
    // edx = rdx_val, rcx = rcx (already set)
    goto bba0;

bba0:
    // 0xe87bba0..0xe87bbad
    // lea r15,[rsi+0x20]; call 0xE935700
    // movups [r15],xmm6; mov qword ptr [r15+0x10],0
    // 0xe87bba0: lea r15,[rsi+0x20]
    r15 = static_cast<std::uint8_t*>(rsi) + 0x20;
    // 0xe87bba4: call 0xE935700  (lift)
    sub_e935700(reinterpret_cast<void*>(rcx_adj), rdx_val);
    // 0xe87bba9: movups [r15],xmm6   (store 16 zero bytes)
    *reinterpret_cast<std::uint64_t*>(r15) = 0;
    *reinterpret_cast<std::uint64_t*>(r15 + 8) = 0;
    // 0xe87bbad: mov qword ptr [r15+0x10],0
    *reinterpret_cast<std::uint64_t*>(r15 + 0x10) = 0;

free_48:
    // 0xe87bbb5..0xe87bbc8
    // mov edx,0x48; mov rcx,rsi; call 0xE935700
    // mov rsi,r14; test r14,r14; je short 0xE87BB5E
    // 0xe87bbb5: mov edx,0x48; mov rcx,rsi
    // 0xe87bbbd: call 0xE935700  (lift)
    sub_e935700(rsi, 0x48);
    // 0xe87bbc2: mov rsi,r14
    rsi = r14;
    // 0xe87bbc5: test r14,r14
    if (rsi != nullptr) {
        // 0xe87bbc8: je short 0xE87BB5E  (not taken)
        goto unlink_node;
    }
    // 0xe87bbc8: je short 0xE87BB5E  (taken)
    goto single_node;

    // ----- shrink path -----
    // 0xe87bc25..0xe87bc6f
    // shr r9,3; inc r9; mov r10,r9; and r10,0xFFFFFFFFFFFFFFFC
    // lea r8,[rdx+r10*8]; movq xmm0,rcx; pshufd xmm0,xmm0,0x44
    // xor r11d,r11d; nop [rax+rax]
shrink:
    // 0xe87bc25: shr r9,3
    r9 >>= 3;
    // 0xe87bc29: inc r9
    r9 += 1;
    // 0xe87bc2c: mov r10,r9
    r10 = r9;
    // 0xe87bc2f: and r10,0xFFFFFFFFFFFFFFFC
    r10 &= 0xFFFFFFFFFFFFFFFCull;
    // 0xe87bc33: lea r8,[rdx+r10*8]
    r8 = static_cast<std::uint8_t*>(rdx) + r10 * 8;
    // 0xe87bc37: movq xmm0,rcx;  0xe87bc3c: pshufd xmm0,xmm0,0x44
    patternVal = static_cast<std::uint64_t>(reinterpret_cast<std::uintptr_t>(rcx));
    // 0xe87bc41: xor r11d,r11d
    r11 = 0;

fill_shrink_loop:
    // 0xe87bc50..0xe87bc64
    // movdqu [rdx+r11*8],xmm0; movdqu [rdx+r11*8+0x10],xmm0
    // add r11,4; cmp r10,r11; jne short 0xE87BC50
    *reinterpret_cast<std::uint64_t*>(static_cast<std::uint8_t*>(rdx) + r11 * 8) = patternVal;
    *reinterpret_cast<std::uint64_t*>(static_cast<std::uint8_t*>(rdx) + r11 * 8 + 0x10) = patternVal;
    // 0xe87bc5d: add r11,4
    r11 += 4;
    // 0xe87bc61: cmp r10,r11
    if (r10 != r11) {
        // 0xe87bc64: jne short 0xE87BC50
        goto fill_shrink_loop;
    }
    // 0xe87bc66: cmp r9,r10
    if (r9 == r10) {
        // 0xe87bc69: je 0xE87BB30
        goto loop_body;
    }
    // 0xe87bc6f: nop  (fallthrough to fill_simple)
    goto fill_simple;

fill_simple:
    // 0xe87bc70..0xe87bc7c
    // mov [r8],rcx; add r8,8; cmp r8,rax; jne short 0xE87BC70
    // 0xe87bc7c: jmp 0xE87BB30
    while (r8 != rax) {
        *reinterpret_cast<void**>(r8) = rcx;
        r8 = static_cast<std::uint8_t*>(r8) + 8;
    }
    goto loop_body;

    // ----- error path -----
    // 0xe87bc92..0xe87bcab
    // mov qword ptr [rsp+0x20],0; xor ecx,ecx; xor edx,edx; xor r8d,r8d; xor r9d,r9d
    // call qword ptr [0xF9A8C78]; int3
error_path:
    // 0xe87bca5: call qword ptr [0xF9A8C78]  (import slot, all-zero args)
    using fail_fn = void(__cdecl*)(std::uintptr_t, std::uintptr_t, std::uintptr_t, std::uintptr_t);
    reinterpret_cast<fail_fn>(*reinterpret_cast<void**>(kFailSlotAddr))(0, 0, 0, 0);
    // 0xe87bcab: int3  (noreturn; the original never continues past this point)
    __assume(false);

epilogue:
    // 0xe87bc81..0xe87bc91
    // movaps xmm6,[rsp+0x30]; add rsp,0x40; pop rbx/rdi/rsi/r14/r15; ret
    return;
}

// LIFT_FN registry entry (per RENDER_NATIVE_SPEC.md section 1.4)
LIFT_FN(e87bb00, "BgfxFrameBuilder::endFrame", 0xE87BB00, sub_e87bb00, nullptr);

// Verbatim call quotes for liftcheck (verify_oc parses plain lines)
#if 0
0xe87bbdc  call 0x1F5EF50
0xe87bbea  call 0xE935700
0xe87bba4  call 0xE935700
0xe87bbbd  call 0xE935700
0xe87bca5  call qword ptr [0xF9A8C78]
#endif

} // namespace native
