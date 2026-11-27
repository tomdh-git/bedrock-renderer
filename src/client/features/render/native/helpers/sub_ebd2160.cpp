// LIFT 0xebd2160 size 0x5c 1.26.62.01 sub_ebd2160
#include "sub_ebd2160.h"
#include "client/features/render/native/Lift.h"

namespace native {

// sub_ebd2160 (0xebd2160, size 0x5c, 1.26.62.01): single basic block 0xebd2160..0xebd21bc,
// no branches, no loops, one call.
//
//   0xebd2160  mov r11,rsp
//   0xebd2163  sub rsp,0x68
//   0xebd2167  mov eax,r8d                 ; rax = zero_extend(a3)  (feeds descriptor +0x30)
//   0xebd216a  lea r8,[0xF847A07]
//   0xebd2171  mov [r11-0x48],r8           ; desc+0x00 = 0x000000000F847A07
//   0xebd2175  xor r10d,r10d
//   0xebd2178  mov [r11-0x40],r10d         ; desc+0x08 = 0
//   0xebd217c  mov [r11-0x38],r10d         ; desc+0x0c = 0
//   0xebd2180  lea r8,[r11-0x48]           ; r8 = &desc+0x00
//   0xebd2184  test r9,r9
//   0xebd2187  cmovne r8,r9                ; r8 = (a4 != 0) ? a4 : &desc+0x00
//   0xebd218b  lea r9,[0xF449520]
//   0xebd2192  mov [r11-0x30],r9           ; desc+0x10 = 0x000000000F449520
//   0xebd2196  lea r9,[0xF449530]
//   0xebd219d  mov [r11-0x28],r9           ; desc+0x18 = 0x000000000F449530
//   0xebd21a1  mov [r11-0x20],rdx          ; desc+0x20 = arg2 (rdx)
//   0xebd21a5  mov [r11-0x18],r10          ; desc+0x28 = 0   (r10 == 0)
//   0xebd21a9  mov [r11-0x10],rax          ; desc+0x30 = zero_extend(a3)
//   0xebd21ad  lea rdx,[r11-0x30]          ; rdx = &desc+0x10
//   0xebd21b1  call 0xEBD1F80              ; -> sub_ebd1f80   (rcx=r8, rdx=&desc+0x10, r8=r8, r9=0xF449530)
//   0xebd21b6  nop
//   0xebd21b7  add rsp,0x68
//   0xebd21bb  ret                          ; return rax
//
// The frame is the 0x68 bytes below entry rsp; the descriptor lives at rsp+0x20 (r11-0x48).
// Arg a1 (rcx) is never read by the original.

// Verbatim instruction quotes from the exe (checked by tools/sigs/verify_oc.py):
#if 0
0xebd2160  mov r11,rsp
0xebd2163  sub rsp,0x68
0xebd2167  mov eax,r8d
0xebd216a  lea r8,[0xF847A07]
0xebd2171  mov [r11-0x48],r8
0xebd2175  xor r10d,r10d
0xebd2178  mov [r11-0x40],r10d
0xebd217c  mov [r11-0x38],r10d
0xebd2180  lea r8,[r11-0x48]
0xebd2184  test r9,r9
0xebd2187  cmovne r8,r9
0xebd218b  lea r9,[0xF449520]
0xebd2192  mov [r11-0x30],r9
0xebd2196  lea r9,[0xF449530]
0xebd219d  mov [r11-0x28],r9
0xebd21a1  mov [r11-0x20],rdx
0xebd21a5  mov [r11-0x18],r10
0xebd21a9  mov [r11-0x10],rax
0xebd21ad  lea rdx,[r11-0x30]
0xebd21b1  call 0xEBD1F80
0xebd21b6  nop
0xebd21b7  add rsp,0x68
0xebd21bb  ret
#endif

void* sub_ebd2160(void* a1 /*rcx: never read*/, void* a2 /*rdx*/, std::uint32_t a3 /*r8d*/, void* a4 /*r9*/)
{
    // 0xebd2160..0xebd2163
    static_assert(sizeof(void*) == 8, "sub_ebd2160: x64 ABI, pointer-sized address space");
    // 0xebd2160 mov r11,rsp ; 0xebd2163 sub rsp,0x68  (frame = 0x68 bytes below entry rsp)
    std::uint8_t frame[sub_ebd2160Layout::kDescOffsetFromRsp + sub_ebd2160Layout::kDescSize];
    std::uint8_t* stk = frame;                                   // rsp after sub rsp,0x68
    void* desc = reinterpret_cast<void*>(stk + sub_ebd2160Layout::kDescOffsetFromRsp);  // r11-0x48
    auto writePtr = [desc](std::uintptr_t off, void* val) {
        *reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(desc) + off) = val;
    };
    auto writeDword = [desc](std::uintptr_t off, std::uint32_t val) {
        *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uintptr_t>(desc) + off) = val;
    };

    // 0xebd2167 mov eax,r8d              ; rax = zero_extend(a3)  (feeds desc+0x30 below)
    // 0xebd216a lea r8,[0xF847A07]
    // 0xebd2171 mov [r11-0x48],r8
    writePtr(sub_ebd2160Layout::kF00_Addr0, reinterpret_cast<void*>(sub_ebd2160Layout::kImm0));  // 0xebd2171
    // 0xebd2175 xor r10d,r10d
    // 0xebd2178 mov [r11-0x40],r10d
    writeDword(sub_ebd2160Layout::kF08_Zero1, 0);                                            // 0xebd2178
    // 0xebd217c mov [r11-0x38],r10d
    writeDword(sub_ebd2160Layout::kF0c_Zero2, 0);                                            // 0xebd217c
    // 0xebd2180 lea r8,[r11-0x48] ; 0xebd2184 test r9,r9 ; 0xebd2187 cmovne r8,r9
    void* out = (a4 != nullptr) ? a4 : desc;                                                 // 0xebd2184..0xebd2187
    // 0xebd218b..0xebd219d
    writePtr(sub_ebd2160Layout::kF10_Addr1, reinterpret_cast<void*>(sub_ebd2160Layout::kImm1)); // 0xebd2192
    writePtr(sub_ebd2160Layout::kF18_Addr2, reinterpret_cast<void*>(sub_ebd2160Layout::kImm2)); // 0xebd219d
    // 0xebd21a1 mov [r11-0x20],rdx
    writePtr(sub_ebd2160Layout::kF20_Arg2, a2);                                              // 0xebd21a1
    // 0xebd21a5 mov [r11-0x18],r10  (r10 == 0)
    writePtr(sub_ebd2160Layout::kF28_Zero3, nullptr);                                        // 0xebd21a5
    // 0xebd21a9 mov [r11-0x10],rax  (rax = zero_extend(a3) from 0xebd2167)
    writePtr(sub_ebd2160Layout::kF30_Arg3,
             reinterpret_cast<void*>(static_cast<std::uintptr_t>(static_cast<std::uint32_t>(a3))));  // 0xebd21a9
    // 0xebd21ad..0xebd21bb
    void* arg_rdx = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(desc) + sub_ebd2160Layout::kF10_Addr1);  // 0xebd21ad
    // 0xebd21b1 call 0xEBD1F80   ; 0xebd21b6 nop ; 0xebd21b7 add rsp,0x68 ; 0xebd21bb ret
    return sub_ebd1f80(out, arg_rdx, out, reinterpret_cast<void*>(sub_ebd2160Layout::kImm2));   // rcx=out, rdx=&desc+0x10, r8=out, r9=0xF449530
}

LIFT_FN(sub_ebd2160, "sub_ebd2160", 0xEBD2160, sub_ebd2160, nullptr);

} // namespace native
