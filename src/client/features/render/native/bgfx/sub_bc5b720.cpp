// LIFT 0xbc5b720 size 0x136 1.26.62.01 VV frame-graph builder
#include "client/features/render/native/bgfx/sub_bc5b720.h"

#include "client/features/render/native/Lift.h"

#include <cstddef>
#include <cstdint>
#include <intrin.h>
#include <vector>

static_assert(sizeof(std::uintptr_t) == 8, "bc5b720: uintptr_t is 8 bytes on x64");
static_assert(sizeof(std::uint32_t) == 4, "bc5b720: uint32_t is 4 bytes on x64");

namespace native {

namespace {

std::uintptr_t ctx_load(std::uintptr_t base, std::uint32_t off) {
    return *reinterpret_cast<std::uintptr_t*>(base + off);
}
void ctx_store(std::uintptr_t base, std::uint32_t off, std::uint32_t size, std::uintptr_t value) {
    if (size == 8) *reinterpret_cast<std::uintptr_t*>(base + off) = value;
    else if (size == 1) *reinterpret_cast<std::uint8_t*>(base + off) = static_cast<std::uint8_t>(value);
}
std::uint8_t ctx_load8(std::uintptr_t base, std::uint32_t off) { return *reinterpret_cast<std::uint8_t*>(base + off); }

// Calls out of lifted code go through native::Boundary wrappers (spec section 6):
// the original code runs and its calls are recorded/compared in Shadow/Verify mode.
//
// 0xe935700: direct callee reached at 0xbc5b7a1 and 0xbc5b81d [V].
// 0xeea6040: indirect callee via the data pointer at 0xf99ffa0, reached at 0xbc5b749, 0xbc5b7cc, 0xbc5b7e2 [V].
// 0xf9a8c78: indirect callee via the data pointer at 0xf9a8c78, reached at 0xbc5b84f [V].

native::Boundary<void> sub_e935700("sub_e935700");
native::Boundary<void> sub_eea6040("sub_eea6040");
native::Boundary<void> sub_f9a8c78("sub_f9a8c78");

} // namespace

std::uint32_t sub_bc5b720_footprint(std::uintptr_t* ctx) {
    return { { { reinterpret_cast<void*>(ctx), 0x210ull } } }; // the function writes through the context pointer [V]
}

std::uint32_t sub_bc5b720(std::uintptr_t* ctx) {
    // prologue
    0xbc5b720  push rsi
    0xbc5b721  push rdi
    0xbc5b722  sub rsp,0x28
    0xbc5b726  mov rsi,rcx
    const std::uintptr_t ctxp = reinterpret_cast<std::uintptr_t>(ctx); // context base

    0xbc5b729  mov rcx,[rcx+0x208]
    0xbc5b730  test rcx,rcx
    0xbc5b733  je short 0xBC5B75A
    const std::uintptr_t pending = ctx_load(ctxp, 0x208);
    if (pending != 0) { // 0xbc5b733  je short 0xBC5B75A
        0xbc5b735  lea rax,[rsi+0x1D0]
        0xbc5b73c  cmp rcx,rax
        0xbc5b73f  setne dl
        0xbc5b742  mov rax,[rcx]
        0xbc5b745  mov rax,[rax+0x20]
        0xbc5b749  call qword ptr [0xF99FFA0]
        sub_eea6040(pending);
        0xbc5b74f  mov qword ptr [rsi+0x208],0
        ctx_store(ctxp, 0x208, 8, 0);
    }

    0xbc5b75a  cmp byte ptr [rsi+0x1B8],1
    0xbc5b761  jne short 0xBC5B7B4
    if (ctx_load8(ctxp, 0x1b8) == 1) { // 0xbc5b761  jne short 0xBC5B7B4
        0xbc5b763  lea rdi,[rsi+0x1A0]
        0xbc5b76a  mov rcx,[rdi]
        0xbc5b76d  test rcx,rcx
        0xbc5b770  je short 0xBC5B7B4
        const std::uintptr_t container = ctx_load(ctxp, 0x1a0);
        if (container != 0) { // 0xbc5b770  je short 0xBC5B7B4
            0xbc5b772  mov rdx,[rsi+0x1B0]
            0xbc5b779  sub rdx,rcx
            0xbc5b77c  cmp rdx,0x1000
            0xbc5b783  jb short 0xBC5B7A1
            0xbc5b785  mov rax,[rcx-8]
            0xbc5b789  add rcx,0xFFFFFFFFFFFFFFF8
            0xbc5b78d  sub rcx,rax
            0xbc5b790  cmp rcx,0x20
            0xbc5b794  jae bc5b83c
            0xbc5b79a  add rdx,0x27
            0xbc5b79e  mov rcx,rax
            const std::uintptr_t diff = ctx_load(ctxp, 0x1b0) - container;
            if (diff < 0x1000) { // 0xbc5b783  jb short 0xBC5B7A1
                0xbc5b7a1  call 0xE935700
                sub_e935700();
                0xbc5b7a6  xorps xmm0,xmm0
                0xbc5b7a9  movups [rdi],xmm0
                0xbc5b7ac  mov qword ptr [rdi+0x10],0
                ctx_store(ctxp, 0x1a0, 8, 0);
                ctx_store(ctxp, 0x1b0, 8, 0);
            } else { // 0xbc5b794  jae short 0xBC5B83C
                0xbc5b83c  mov qword ptr [rsp+0x20],0
                0xbc5b845  xor ecx,ecx
                0xbc5b847  xor edx,edx
                0xbc5b849  xor r8d,r8d
                0xbc5b84c  xor r9d,r9d
                0xbc5b84f  call qword ptr [0xF9A8C78]
                sub_f9a8c78();
                return 0;
            }
        }
    }

    0xbc5b7b4  mov rdi,[rsi+0x60]
    0xbc5b7b8  test rdi,rdi
    0xbc5b7bb  je short 0xBC5B7E8
    0xbc5b7bd  lock dec dword ptr [rdi+8]
    0xbc5b7c1  jne short 0xBC5B7E8
    0xbc5b7c3  mov rax,[rdi]
    0xbc5b7c6  mov rax,[rax]
    0xbc5b7c9  mov rcx,rdi
    0xbc5b7cc  call qword ptr [0xF99FFA0]
    0xbc5b7d2  lock dec dword ptr [rdi+0xC]
    0xbc5b7d6  jne short 0xBC5B7E8
    0xbc5b7d8  mov rax,[rdi]
    0xbc5b7db  mov rax,[rax+8]
    0xbc5b7df  mov rcx,rdi
    0xbc5b7e2  call qword ptr [0xF99FFA0]
    0xbc5b7e8  mov rax,[rsi+0x18]
    0xbc5b7ec  cmp rax,0x10
    0xbc5b7f0  jb short 0xBC5B822
    0xbc5b7f2  mov rcx,[rsi]
    0xbc5b7f5  lea rdx,[rax+1]
    0xbc5b7f9  cmp rdx,0x1000
    0xbc5b800  jb short 0xBC5B81D
    0xbc5b802  mov r8,[rcx-8]
    0xbc5b806  add rcx,0xFFFFFFFFFFFFFFF8
    0xbc5b80a  sub rcx,r8
    0xbc5b80d  cmp rcx,0x20
    0xbc5b811  jae short 0xBC5B83C
    0xbc5b813  add rax,0x28
    0xbc5b817  mov rdx,rax
    0xbc5b81a  mov rcx,r8
    0xbc5b81d  call 0xE935700
    0xbc5b822  mov qword ptr [rsi+0x10],0
    0xbc5b82a  mov qword ptr [rsi+0x18],0xF
    0xbc5b832  mov byte ptr [rsi],0
    0xbc5b835  add rsp,0x28
    0xbc5b839  pop rdi
    0xbc5b83a  pop rsi
    0xbc5b83b  ret
    0xbc5b83c  mov qword ptr [rsp+0x20],0
    0xbc5b845  xor ecx,ecx
    0xbc5b847  xor edx,edx
    0xbc5b849  xor r8d,r8d
    0xbc5b84c  xor r9d,r9d
    0xbc5b84f  call qword ptr [0xF9A8C78]
    0xbc5b855  int3

    ctx_store(ctxp, 0x10, 8, 0);
    ctx_store(ctxp, 0x18, 8, 0xF);
    ctx_store(ctxp, 0x0, 1, 0);
    return 0;
}

LIFT_FN(bc5b720, "VV frame-graph builder", 0xBC5B720, sub_bc5b720, sub_bc5b720_footprint);

} // namespace native
