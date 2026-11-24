// LIFT 0xe80bee0 size 0xa5 1.26.62.01 RendererContextD3D12 base slot 58
#include "sub_e80bee0.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>

namespace native { namespace d3d12 {

static_assert(kTableBase == 0x10000, "table base");
static_assert(kCountOff == 0x12000, "count offset");
static_assert(kReadyOff == 0x12018, "ready offset");

// Boundary callee (docs/data/native_boundary.tsv: 0xebcf4e0 vendor, sub_ebcf4e0).
native::Boundary<void, void*, std::int32_t, void*, std::int32_t> sub_ebcf4e0("sub_ebcf4e0");

extern "C" void sub_e80bee0(void* a0, void* a1) {
    // a0 = rcx = this (RendererContextD3D12*), a1 = rdx = object pointer stored into every entry
    char* rsi = static_cast<char*>(a0); // mov rsi,rcx  (a0)
    void*  rdiObj = a1;                 // mov rdi,rdx ; value written into every table entry

    // 0xe80bee0..0xe80bee9: prologue saves r15,r14,r12,rsi,rdi,rbx and reserves 0x38 stack
    // 0xe80beed..0xe80bef5: movaps save xmm6; rdi=rdx; rsi=rcx
    // 0xe80bef8..0xe80bf16: r12 = a0 + 0x10000 (table base)
    char* r12 = rsi + kTableBase;
    *reinterpret_cast<std::uint64_t*>(rsi + kCountOff) = 0; // 0xe80beff  W a0+0x12000
    std::uint64_t ebx = 0;                                  // 0xe80bf0a  xor ebx,ebx
    std::uint64_t xmm6 = 0;                                 // 0xe80bf0c  xorps xmm6,xmm6
    void* r14 = reinterpret_cast<void*>(RewriteRegistry::imageBase() + 0xF842BBA); // 0xe80bf0f  lea r14,[0xF842BBA]
    char* r15 = rsi;                                        // 0xe80bf16  mov r15,rcx

    // 0xe80bf19: nop [rax]  (alignment padding before the loop head)
    // 0xe80bf20..0xe80bf69: 256-iteration fill loop
    for (;;) {
        std::uint64_t idx = *reinterpret_cast<std::uint64_t*>(rsi + kCountOff); // 0xe80bf20  mov rax,[rsi+0x12000]
        std::uint64_t off = idx << 5;                                            // 0xe80bf27  shl rax,5
        // 0xe80bf2b: store object pointer at entry+0
        *reinterpret_cast<void**>(r12 + off) = rdiObj;
        // 0xe80bf2f: 16 zero bytes at entry+8 (movups xmm6)
        struct Zero16 { std::uint64_t lo, hi; } z{0, 0};
        *reinterpret_cast<Zero16*>(r12 + off + kEntryZero) = z;
        // 0xe80bf35: entry+0x18 = 0xFFFFFFFF
        *reinterpret_cast<std::uint32_t*>(r12 + off + kEntryTag) = 0xFFFFFFFFu;
        // 0xe80bf3e: ++count
        *reinterpret_cast<std::uint64_t*>(rsi + kCountOff) = idx + 1;
        // 0xe80bf45..0xe80bf50: call sub_ebcf4e0(r15, 7, r14, ebx)
        sub_ebcf4e0(reinterpret_cast<void*>(r15), 7, r14, static_cast<std::int32_t>(ebx)); // 0xe80bf53  call
        // 0xe80bf58..0xe80bf69: ++rbx; r15 += 0x100; loop while rbx != 0x100
        ++ebx;             // 0xe80bf58  inc rbx
        r15 += kPerStride; // 0xe80bf5b  add r15,0x100
        if (ebx == kEntryCount) break; // 0xe80bf62  cmp rbx,0x100 ; 0xe80bf69  jne
    }

    // 0xe80bf6b..0xe80bf84: ready flag = 1; restore xmm6/stack; pop; ret
    *reinterpret_cast<std::uint8_t*>(rsi + kReadyOff) = 1;
    (void)xmm6;
}

#if 0
0xe80bee0  push r15
0xe80bee2  push r14
0xe80bee4  push r12
0xe80bee6  push rsi
0xe80bee7  push rdi
0xe80bee8  push rbx
0xe80bee9  sub rsp,0x38
0xe80beed  movaps [rsp+0x20],xmm6
0xe80bef2  mov rdi,rdx
0xe80bef5  mov rsi,rcx
0xe80bef8  lea r12,[rcx+0x10000]
0xe80beff  mov qword ptr [rcx+0x12000],0
0xe80bf0a  xor ebx,ebx
0xe80bf0c  xorps xmm6,xmm6
0xe80bf0f  lea r14,[0xF842BBA]
0xe80bf16  mov r15,rcx
0xe80bf19  nop [rax]
0xe80bf20  mov rax,[rsi+0x12000]
0xe80bf27  shl rax,5
0xe80bf2b  mov [r12+rax],rdi
0xe80bf2f  movups [r12+rax+8],xmm6
0xe80bf35  mov dword ptr [r12+rax+0x18],0xFFFFFFFF
0xe80bf3e  inc qword ptr [rsi+0x12000]
0xe80bf45  mov rcx,r15
0xe80bf48  mov edx,7
0xe80bf4d  mov r8,r14
0xe80bf50  mov r9d,ebx
0xe80bf53  call 0xEBCF4E0
0xe80bf58  inc rbx
0xe80bf5b  add r15,0x100
0xe80bf62  cmp rbx,0x100
0xe80bf69  jne short 0xE80BF20
0xe80bf6b  mov byte ptr [rsi+0x12018],1
0xe80bf72  movaps xmm6,[rsp+0x20]
0xe80bf77  add rsp,0x38
0xe80bf7b  pop rbx
0xe80bf7c  pop rdi
0xe80bf7d  pop rsi
0xe80bf7e  pop r12
0xe80bf80  pop r14
0xe80bf82  pop r15
0xe80bf84  ret
#endif

// Registry entry
LIFT_FN(sub_e80bee0, "RendererContextD3D12 base slot 58", 0xe80bee0, sub_e80bee0, nullptr);

} } // namespace