// LIFT 0xbc70ff0 size 0xf1 1.26.62.01 sub_bc70ff0
#include "client/features/render/native/bgfx/sub_bc70ff0.h"
#include "client/features/render/native/Lift.h"

#include <cstddef>
#include <cstdint>

namespace native {

// Layout assertions (canonical constants live in sub_bc70ff0.h; repeated here so the lift
// is self-checking per docs/RENDER_NATIVE_SPEC.md item 3).
static_assert(offsetof(RenderContext, cmdPost) == 0x1CFD0C8,
              "sub_bc70ff0: RenderContext::cmdPost must be at +0x1CFD0C8");
static_assert(offsetof(CmdPostState, postCursor) == 0xDC5818,
              "sub_bc70ff0: CmdPostState::postCursor must be at +0xDC5818");
static_assert(offsetof(CmdPostState, postData) == 0xDC5820,
              "sub_bc70ff0: CmdPostState::postData must be at +0xDC5820");

void sub_bc70ff0(RenderContext* ctx, std::uint16_t dx, std::uint32_t d32, std::uint64_t q64)
{
    // 0xbc70ff0..0xbc71023: prologue; spill args to locals; lock address = ctx + 0x1C0;
    //   sub_ebdbf10(lock)
    //   0xbc70ff0  push rbp        0xbc70ff1  push rsi        0xbc70ff2  push rdi
    //   0xbc70ff3  sub rsp,0x40    0xbc70ff7  lea rbp,[rsp+0x40]
    //   0xbc70ffc  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
    //               ; stack cookie, stored never read back (dead store, not reproduced)
    //   0xbc71004  mov rsi,rcx     0xbc71007  mov [rbp-0xC],dx    0xbc7100b  mov [rbp-0x20],r9
    //   0xbc7100f  mov [rbp-0x10],r8d  0xbc71013  add rcx,0x1C0   0xbc7101a  mov [rbp-0x18],rcx
    //   0xbc7101e  call 0xEBDBF10    ; sub_ebdbf10(lock)  [`0xbc7101e  call 0xEBDBF10`]
    void* lockPtr = reinterpret_cast<void*>(reinterpret_cast<std::uint8_t*>(ctx) + 0x1C0);
    sub_ebdbf10(lockPtr);                                         // 0xbc7101e  call 0xEBDBF10   ; lock

    // 0xbc71023..0xbc7104e: st = ctx->cmdPost (loaded after the lock call, as in the original);
    //   tag byte 0x13; append 1 byte at st->postData + st->postCursor
    //   0xbc71023  mov rdi,[rsi+0x1CFD0C8]   0xbc7102a  mov byte ptr [rbp-9],0x13
    //   0xbc7102e  mov eax,[rdi+0xDC5818]    0xbc71034  lea rcx,[rdi+rax]   0xbc71038  add rcx,0xDC5820
    //   0xbc7103f  lea rdx,[rbp-9]           0xbc71043  mov r8d,1           0xbc71049  call 0xEBCE390   [`0xbc71049  call 0xEBCE390`]
    CmdPostState* st = ctx->cmdPost;                               // 0xbc71023  mov rdi,[rsi+0x1CFD0C8]
    std::uint8_t tag = 0x13;                                       // 0xbc7102a  mov byte ptr [rbp-9],0x13
    std::uint32_t count = st->postCursor;                          // 0xbc7102e  mov eax,[rdi+0xDC5818]
    sub_ebce390(st->postData + count, &tag, 1u);                   // 0xbc71049  call 0xEBCE390   dst=postData+count, src=&tag, size=1   [`0xbc71049  call 0xEBCE390`]

    // 0xbc7104e..0xbc7107a: count = (count & ~1) + 2; store to cursor; append 2 bytes of dx
    //   0xbc7104e  nop                      0xbc7104f  lea rsi,[rdi+0xDC5820]
    //   0xbc71056  mov ecx,[rdi+0xDC5818]   0xbc7105c  and ecx,0xFFFFFFFE   0xbc7105f  add ecx,2
    //   0xbc71062  mov [rdi+0xDC5818],ecx   0xbc71068  add rcx,rsi          0xbc7106b  lea rdx,[rbp-0xC]
    //   0xbc7106f  mov r8d,2                0xbc71075  call 0xEBCE390       [`0xbc71075  call 0xEBCE390`]
    count = st->postCursor = (st->postCursor & ~1u) + 2u;          // 0xbc71056..0xbc71062  (reloaded from memory; same value as local count)
    sub_ebce390(st->postData + count, &dx, 2u);                    // 0xbc71075  call 0xEBCE390   dst=postData+count, src=&dx, size=2   [`0xbc71075  call 0xEBCE390`]

    // 0xbc7107a..0xbc7109f: count = (count + 5) & ~3; store to cursor; append 4 bytes of d32
    //   0xbc7107a  nop                      0xbc7107b  mov ecx,[rdi+0xDC5818]
    //   0xbc71081  add ecx,5                0xbc71084  and ecx,0xFFFFFFFC   0xbc71087  mov [rdi+0xDC5818],ecx
    //   0xbc7108d  add rcx,rsi              0xbc71090  lea rdx,[rbp-0x10]   0xbc71094  mov r8d,4
    //   0xbc7109a  call 0xEBCE390           [`0xbc7109a  call 0xEBCE390`]
    count = st->postCursor = (st->postCursor + 5u) & ~3u;          // 0xbc7107b..0xbc71087
    sub_ebce390(st->postData + count, &d32, 4u);                   // 0xbc7109a  call 0xEBCE390   dst=postData+count, src=&d32, size=4   [`0xbc7109a  call 0xEBCE390`]

    // 0xbc7109f..0xbc710c8: count = (count + 0xB) & ~7; store to cursor; append 8 bytes of q64;
    //   cursor += 8
    //   0xbc7109f  nop                      0xbc710a0  mov eax,[rdi+0xDC5818]
    //   0xbc710a6  add eax,0xB              0xbc710a9  and eax,0xFFFFFFF8   0xbc710ac  mov [rdi+0xDC5818],eax
    //   0xbc710b2  add rsi,rax              0xbc710b5  lea rdx,[rbp-0x20]   0xbc710b9  mov r8d,8
    //   0xbc710bf  mov rcx,rsi              0xbc710c2  call 0xEBCE390       [`0xbc710c2  call 0xEBCE390`]
    //   0xbc710c7  nop                      0xbc710c8  add dword ptr [rdi+0xDC5818],8
    count = st->postCursor = (st->postCursor + 0xBu) & ~7u;        // 0xbc710a0..0xbc710ac
    sub_ebce390(st->postData + count, &q64, 8u);                   // 0xbc710c2  call 0xEBCE390   dst=postData+count, src=&q64, size=8   [`0xbc710c2  call 0xEBCE390`]
    st->postCursor = count + 8u;                                   // 0xbc710c8  add dword ptr [rdi+0xDC5818],8

    // 0xbc710c8..0xbc710e1: sub_ebdbf20(lock); epilogue; ret (void)
    //   0xbc710cf  mov rcx,[rbp-0x18]   0xbc710d3  call 0xEBDBF20   ; sub_ebdbf20(lock)  [`0xbc710d3  call 0xEBDBF20`]
    //   0xbc710d8  nop                  0xbc710d9  add rsp,0x40     0xbc710dd  pop rdi
    //   0xbc710de  pop rsi              0xbc710df  pop rbp          0xbc710e0  ret
    sub_ebdbf20(lockPtr);                                          // 0xbc710d3  call 0xEBDBF20   ; unlock
}

static native::Footprint sub_bc70ff0Footprint(RenderContext* ctx, std::uint16_t, std::uint32_t, std::uint64_t)
{
    native::Footprint fp;
    if (ctx == nullptr) return fp;
    CmdPostState* st = ctx->cmdPost;
    if (st == nullptr) return fp;
    fp.push_back({reinterpret_cast<void*>(&st->postCursor), sizeof(st->postCursor)}); // written at 0xbc71062/0xbc71087/0xbc710ac/0xbc710c8
    std::uint32_t c0 = st->postCursor;
    std::uint32_t c1 = (c0 & ~1u) + 2u;
    std::uint32_t c2 = (c1 + 5u) & ~3u;
    std::uint32_t c3 = (c2 + 0xBu) & ~7u;
    std::uint32_t end = c3 + 8u;                                     // final cursor value after 0xbc710c8
    if (st->postData != nullptr && end > c0)
        fp.push_back({st->postData + c0, end - c0});                 // appended bytes at 0xbc71049/0xbc71075/0xbc7109a/0xbc710c2
    fp.push_back({reinterpret_cast<std::uint8_t*>(ctx) + 0x1C0, 0x29}); // lock subobject written by sub_ebdbf10/sub_ebdbf20 [V 0xebdbf30..0xebdbf97]
    return fp;
}

LIFT_FN(sub_bc70ff0, "native::sub_bc70ff0", 0xbc70ff0, sub_bc70ff0, sub_bc70ff0Footprint);

} // namespace native
