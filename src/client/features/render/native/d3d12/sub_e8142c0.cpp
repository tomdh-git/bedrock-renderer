// LIFT 0xe8142c0 size 0xd6 1.26.62.01 createProgram (shader pointers, merged predefined uniforms)
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e8142c0.h"

#include <cstddef>
#include <cstdint>

static_assert(sizeof(void*) == 8, "ptr");

// Verbatim disassembly of [0xe8142c0, 0xe814396) (Minecraft Windows 1.26.62.01).
#if 0
0xe8142c0  push r15
0xe8142c2  push r14
0xe8142c4  push rsi
0xe8142c5  push rdi
0xe8142c6  push rbx
0xe8142c7  sub rsp,0x20
0xe8142cb  mov edi,r9d
0xe8142ce  mov rsi,rcx
0xe8142d1  movzx eax,dx
0xe8142d4  imul r14,rax,0xF8
0xe8142db  movzx eax,r8w
0xe8142df  imul r15,rax,0xB8
0xe8142e6  lea rax,[rcx+r15]
0xe8142ea  add rax,0xAAA178
0xe8142f0  mov [rcx+r14+0xB62178],rax
0xe8142f8  movzx r8d,byte ptr [rcx+r15+0xAAA228]
0xe814301  shl r8d,3
0xe814305  lea rdx,[rcx+r15]
0xe814309  add rdx,0xAAA188
0xe814310  lea rbx,[rcx+r14]
0xe814314  add rbx,0xB62188
0xe81431b  mov rcx,rbx
0xe81431e  call 0xEBCE390
0xe814323  movzx eax,byte ptr [rsi+r15+0xAAA228]
0xe81432c  mov [rsi+r14+0xB62268],al
0xe814334  cmp di,0xFFFF
0xe814338  je short 0xE81438A
0xe81433a  add r14,rsi
0xe81433d  add r14,0xB62178
0xe814344  add rsi,0xAAA178
0xe81434b  movzx ecx,di
0xe81434e  imul rdi,rcx,0xB8
0xe814355  lea rcx,[rsi+rdi]
0xe814359  mov [r14+8],rcx
0xe81435d  movzx r8d,byte ptr [rsi+rdi+0xB0]
0xe814366  shl r8d,3
0xe81436a  lea rdx,[rsi+rdi]
0xe81436e  add rdx,0x10
0xe814372  lea rcx,[rbx+rax*8]
0xe814376  call 0xEBCE390
0xe81437b  movzx eax,byte ptr [rsi+rdi+0xB0]
0xe814383  add [r14+0xF0],al
0xe81438a  add rsp,0x20
0xe81438e  pop rbx
0xe81438f  pop rdi
0xe814390  pop rsi
0xe814391  pop r14
0xe814393  pop r15
0xe814395  ret
#endif

namespace native::d3d12 {

// 0xe8142c0..0xe814395  (prolog pushes r15/r14/rsi/rdi/rbx, sub rsp,0x20 and the
// epilog add rsp,0x20 / pop r15/r14/rsi/rdi/rbx / ret are emitted by the compiler.)
void sub_e8142c0(void* a0, unsigned short a1, unsigned short a2, unsigned int a3) {
    // 0xe8142cb..0xe8142df
    const unsigned int di = a3;                                   // 0xe8142cb  mov edi,r9d
    char* const rsi = static_cast<char*>(a0);                     // 0xe8142ce  mov rsi,rcx
    const std::size_t r14 = static_cast<std::size_t>(a1) * kProgramStride; // 0xe8142d1..0xe8142d4
    const std::size_t r15 = static_cast<std::size_t>(a2) * kShaderStride;  // 0xe8142db..0xe8142df

    // 0xe8142e6..0xe8142f0  program[a1].field0x00 = shader[a2]
    void* const shaderA = rsi + r15 + kShaderArrayOff;            // 0xe8142e6  lea rax,[rcx+r15]; 0xe8142ea  add rax,0xAAA178
    *reinterpret_cast<void**>(rsi + r14 + kProgramArrayOff) = shaderA; // 0xe8142f0  mov [rcx+r14+0xB62178],rax

    // 0xe8142f8..0xe81431e  copy shader[a2] data into program[a1] data (+0x10), length count*8
    unsigned int lenA = *reinterpret_cast<unsigned char*>(rsi + r15 + kShaderCountOff); // 0xe8142f8  movzx r8d,byte ptr [rcx+r15+0xAAA228]
    lenA <<= 3;                                                   // 0xe814301  shl r8d,3
    void* const srcA = rsi + r15 + kShaderDataOff;                // 0xe814305  lea rdx,[rcx+r15]; 0xe814309  add rdx,0xAAA188
    char* const dstA = rsi + r14 + kProgramDataOff;               // 0xe814310  lea rbx,[rcx+r14]; 0xe814314  add rbx,0xB62188
    native::sub_ebce390(dstA, srcA, lenA);                        // 0xe81431b  mov rcx,rbx ; 0xe81431e  call 0xEBCE390

    // 0xe814323..0xe81432c  program[a1].count (+0xF0) = shader[a2].count byte
    const unsigned int cntA = *reinterpret_cast<unsigned char*>(rsi + r15 + kShaderCountOff); // 0xe814323  movzx eax,byte ptr [rsi+r15+0xAAA228]
    *reinterpret_cast<unsigned char*>(rsi + r14 + kProgramCountOff) = static_cast<unsigned char>(cntA); // 0xe81432c  mov [rsi+r14+0xB62268],al

    // 0xe814334..0xe814338  if (a3 == 0xFFFF) skip the second shader
    if (static_cast<unsigned short>(di) != kNoShader) {           // 0xe814334  cmp di,0xFFFF ; 0xe814338  je short 0xE81438A
        // 0xe81433a..0xe81434e  r14 = program[a1] record base; rsi = shader table; rdi = a3*0xB8
        char* const rec = rsi + r14 + kProgramArrayOff;           // 0xe81433a  add r14,rsi ; 0xe81433d  add r14,0xB62178
        char* const sh = rsi + kShaderArrayOff;                   // 0xe814344  add rsi,0xAAA178
        const std::size_t rdi = static_cast<std::size_t>(static_cast<unsigned short>(di)) * kShaderStride; // 0xe81434b  movzx ecx,di ; 0xe81434e  imul rdi,rcx,0xB8

        // 0xe814355..0xe814359  program[a1].field0x08 = shader[a3]
        void* const shaderB = sh + rdi;                           // 0xe814355  lea rcx,[rsi+rdi]
        *reinterpret_cast<void**>(rec + kProgShaderBPtr) = shaderB; // 0xe814359  mov [r14+8],rcx

        // 0xe81435d..0xe814376  copy shader[a3] data to program[a1] data + cntA*8, length count*8
        unsigned int lenB = *reinterpret_cast<unsigned char*>(sh + rdi + kShaderFieldCnt); // 0xe81435d  movzx r8d,byte ptr [rsi+rdi+0xB0]
        lenB <<= 3;                                               // 0xe814366  shl r8d,3
        void* const srcB = sh + rdi + kShaderFieldData;           // 0xe81436a  lea rdx,[rsi+rdi] ; 0xe81436e  add rdx,0x10
        void* const dstB = dstA + cntA * 8;                       // 0xe814372  lea rcx,[rbx+rax*8]
        native::sub_ebce390(dstB, srcB, lenB);                    // 0xe814376  call 0xEBCE390

        // 0xe81437b..0xe814383  program[a1].count (+0xF0) += shader[a3].count byte (8-bit add)
        const unsigned int cntB = *reinterpret_cast<unsigned char*>(sh + rdi + kShaderFieldCnt); // 0xe81437b  movzx eax,byte ptr [rsi+rdi+0xB0]
        unsigned char* const cntSlot = reinterpret_cast<unsigned char*>(rec + kProgCountField); // 0xe814383  add [r14+0xF0],al
        *cntSlot = static_cast<unsigned char>(*cntSlot + static_cast<unsigned char>(cntB));
    }
    // 0xe81438a..0xe814395  epilog (compiler)
}

} // namespace native::d3d12

// Registry entry: NAME = Sigs.json symbol (sig anchors are appended at the milestone gate).
LIFT_FN(sub_e8142c0, "sub_e8142c0", 0xe8142c0, native::d3d12::sub_e8142c0, nullptr);