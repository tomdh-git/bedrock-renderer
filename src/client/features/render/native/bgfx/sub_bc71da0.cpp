// LIFT 0xbc71da0 size 0x167 1.26.62.01 sub_bc71da0
#include "sub_bc71da0.h"
#include "client/features/render/native/Lift.h"

namespace native {

// Lifted body of sub 0xbc71da0 ("Frame renderer lambda", destroy-texture command record),
// size 0x167 (0xbc71da0..0xbc71f07), 1.26.62.01. Same reads, same writes (value and order),
// same calls in the same order, same return (rax = rdx = out) as the exe function. Each
// block carries the instruction range it implements; every call is quoted verbatim beside
// the call site.
//
// Stream record appended to ctx->stream->data[] at ctx->stream->writePos:
//   u8 0xB; writePos = (writePos & ~1u) + 2u; u16 handle;
//   writePos = (writePos + 5u) & ~3u; u32 a3;
//   writePos = (writePos + 0xBu) & ~7u; u64 spill ([rbp+0x50]); writePos += 8u

static native::Footprint sub_bc71da0Footprint(Ctx* /*ctx*/, std::uint16_t* out,
                                              std::uint32_t /*a2*/, std::uint32_t /*a3*/) {
    native::Footprint fp;
    fp.push_back({out, sizeof(std::uint16_t)});
    // The command-stream region written through sub_ebce390 depends on the stream cursor
    // and on the uninstrumented sub_ebce390 target; it cannot be declared statically and is
    // not covered by this footprint.
    return fp;
}

extern "C" std::uint16_t* sub_bc71da0(Ctx* ctx, std::uint16_t* out, std::uint32_t a2,
                                      std::uint32_t a3) {
    // 0xbc71da0..0xbc71dc3: prologue and argument spill
    //   0xbc71da0  push rbp
    //   0xbc71da1  push r14
    //   0xbc71da3  push rsi
    //   0xbc71da4  push rdi
    //   0xbc71da5  push rbx
    //   0xbc71da6  sub rsp,0x40
    //   0xbc71daa  lea rbp,[rsp+0x40]
    //   0xbc71daf  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
    //   0xbc71db7  mov ebx,r8d            ; bx = low16(a2) = handle
    //   0xbc71dba  mov rsi,rdx            ; out
    //   0xbc71dbd  mov rdi,rcx            ; ctx
    //   0xbc71dc0  mov [rbp-0x10],r9d     ; saved a3
    std::uint16_t h = static_cast<std::uint16_t>(a2);   // bx = low16(a2) = handle
    void* lock = &ctx->lockField;                       // ctx + 0x1C0 (lea, no load)
    std::uint32_t savedA3 = a3;                         // [rbp-0x10]
    // [rbp+0x50] (= entry_rsp + 0x10, inside the caller's frame area): 8 bytes the
    // original copies verbatim into the stream; not defined by this function.
    std::uint64_t spill;

    // 0xbc71de1..0xbc71e8a: emitRecord (entered from 0xbc71ddd and from 0xbc71ee7)
    //   0xbc71de1  mov [rbp-0x18],r14
    //   0xbc71de5  mov rbx,[rdi+0x1CFD0C8]               ; s = ctx->stream
    //   0xbc71dec  mov byte ptr [rbp-0xB],0xB
    //   0xbc71df0  mov eax,[rbx+0xDC5818]                ; pos = s->writePos
    //   0xbc71df6  lea rcx,[rbx+rax]
    //   0xbc71dfa  add rcx,0xDC5820
    //   0xbc71e01  lea rdx,[rbp-0xB]
    //   0xbc71e05  mov r8d,1
    //   0xbc71e0b  call 0xEBCE390                        ; memcpy(s->data + pos, &mark, 1)
    //   0xbc71e10  nop
    //   0xbc71e11  lea rdi,[rbx+0xDC5820]
    //   0xbc71e18  mov ecx,[rbx+0xDC5818]                ; cursor reloaded
    //   0xbc71e1e  and ecx,0xFFFFFFFE
    //   0xbc71e21  add ecx,2
    //   0xbc71e24  mov [rbx+0xDC5818],ecx                ; s->writePos = pos
    //   0xbc71e2a  add rcx,rdi
    //   0xbc71e2d  lea rdx,[rbp-0xA]
    //   0xbc71e31  mov r8d,2
    //   0xbc71e37  call 0xEBCE390                        ; memcpy(s->data + pos, &chain, 2)
    //   0xbc71e3c  nop
    //   0xbc71e3d  mov ecx,[rbx+0xDC5818]                ; cursor reloaded
    //   0xbc71e43  add ecx,5
    //   0xbc71e46  and ecx,0xFFFFFFFC
    //   0xbc71e49  mov [rbx+0xDC5818],ecx                ; s->writePos = pos
    //   0xbc71e4f  add rcx,rdi
    //   0xbc71e52  lea rdx,[rbp-0x10]
    //   0xbc71e56  mov r8d,4
    //   0xbc71e5c  call 0xEBCE390                        ; memcpy(s->data + pos, &savedA3, 4)
    //   0xbc71e61  nop
    //   0xbc71e62  mov eax,[rbx+0xDC5818]                ; cursor reloaded
    //   0xbc71e68  add eax,0xB
    //   0xbc71e6b  and eax,0xFFFFFFF8
    //   0xbc71e6e  mov [rbx+0xDC5818],eax                ; s->writePos = pos
    //   0xbc71e74  add rdi,rax
    //   0xbc71e77  lea rdx,[rbp+0x50]
    //   0xbc71e7b  mov r8d,8
    //   0xbc71e81  mov rcx,rdi
    //   0xbc71e84  call 0xEBCE390                        ; memcpy(s->data + pos, &spill, 8)
    //   0xbc71e89  nop
    //   0xbc71e8a  add dword ptr [rbx+0xDC5818],8        ; s->writePos += 8
    auto emitRecord = [&](std::uint16_t chain) {
        CommandStream* s = ctx->stream;
        std::uint32_t pos = s->writePos;
        std::uint8_t mark = 0xB;
        sub_ebce390(s->data + pos, &mark, 1u);            // 0xbc71e0b  call 0xEBCE390   [`0xbc71e0b  call 0xEBCE390`]
        pos = (s->writePos & 0xFFFFFFFEu) + 2u;
        s->writePos = pos;
        sub_ebce390(s->data + pos, &chain, 2u);           // 0xbc71e37  call 0xEBCE390   [`0xbc71e37  call 0xEBCE390`]
        pos = (s->writePos + 5u) & 0xFFFFFFFCu;
        s->writePos = pos;
        sub_ebce390(s->data + pos, &savedA3, 4u);         // 0xbc71e5c  call 0xEBCE390   [`0xbc71e5c  call 0xEBCE390`]
        pos = (s->writePos + 0xBu) & 0xFFFFFFF8u;
        s->writePos = pos;
        sub_ebce390(s->data + pos, &spill, 8u);           // 0xbc71e84  call 0xEBCE390   [`0xbc71e84  call 0xEBCE390`]
        pos += 8u;
        s->writePos = pos;
    };

    // 0xbc71dc4..0xbc71dce: lock = ctx + 0x1C0; call sub_ebdbf10(lock, out, a2, a3)
    //   0xbc71dc4  lea r14,[rcx+0x1C0]
    //   0xbc71dcb  mov rcx,r14
    //   0xbc71dce  call 0xEBDBF10
    sub_ebdbf10(lock, out, a2, a3);                       // 0xbc71dce  call 0xEBDBF10   [`0xbc71dce  call 0xEBDBF10`]
    // return value unused ([V] the bx tested after the call is low16(a2), computed before it)

    if (h == 0xFFFF) {
        // 0xbc71dd3  cmp bx,0xFFFF ; 0xbc71dd7  je 0xBC71E9B
        // 0xbc71e9b..0xbc71ee7: handle-table indirection for the null handle
        //   0xbc71e9b  movzx ecx,word ptr [rdi+0x1DFC298]
        //   0xbc71ea2  movzx edx,word ptr [rdi+0x1DFC29A]
        //   0xbc71ea9  mov ax,0xFFFF
        //   0xbc71ead  cmp cx,dx
        //   0xbc71eb0  jae short 0xBC71EED
        std::uint16_t chain = 0xFFFF;
        std::uint16_t cx = ctx->handleIndex;
        std::uint16_t dx = ctx->handleMax;
        if (cx < dx) {
            // 0xbc71eb2..0xbc71edb
            //   0xbc71eb2  movzx r8d,cx
            //   0xbc71eb6  lea r9d,[rcx+1]
            //   0xbc71eba  mov [rdi+0x1DFC298],r9w
            //   0xbc71ec2  movzx r8d,word ptr [rdi+r8*2+0x1DFC29C]
            //   0xbc71ecb  lea rdx,[rdi+rdx*2]
            //   0xbc71ecf  add rdx,0x1DFC29C
            //   0xbc71ed6  mov [rdx+r8*2],cx
            //   0xbc71edb  mov [rbp-0xA],r8w
            ctx->handleIndex = static_cast<std::uint16_t>(cx + 1);
            std::uint16_t nxt = ctx->handleSlots[cx];
            ctx->handleSlots[static_cast<std::size_t>(dx) + nxt] = cx;
            chain = nxt;
            // 0xbc71ee0  cmp r8d,0xFFFF ; 0xbc71ee7  jne 0xBC71DE1
            if (nxt != 0xFFFF) {
                emitRecord(chain);
            }
        }
        // 0xbc71eed..0xbc71ef8: store result, call sub_ebdbf20
        //   0xbc71eed  mov [rsi],ax
        //   0xbc71ef0  mov rcx,r14
        //   0xbc71ef3  call 0xEBDBF20
        *out = chain;
        sub_ebdbf20(lock);                                // 0xbc71ef3  call 0xEBDBF20   [`0xbc71ef3  call 0xEBDBF20`]
        // 0xbc71ef9..0xbc71f06
        //   0xbc71ef9  mov rax,rsi
        //   0xbc71efc  add rsp,0x40
        //   0xbc71f00  pop rbx
        //   0xbc71f01  pop rdi
        //   0xbc71f02  pop rsi
        //   0xbc71f03  pop r14
        //   0xbc71f05  pop rbp
        //   0xbc71f06  ret
        return out;
    }

    // 0xbc71ddd  mov [rbp-0xA],bx ; 0xbc71de1..0xbc71e8a (emitRecord via lambda above)
    emitRecord(h);
    // 0xbc71e91..0xbc71e99
    //   0xbc71e91  movzx eax,word ptr [rbp-0xA]
    //   0xbc71e95  mov r14,[rbp-0x18]
    //   0xbc71e99  jmp short 0xBC71EED
    *out = h;
    // 0xbc71ef0..0xbc71f06
    //   0xbc71ef0  mov rcx,r14
    //   0xbc71ef3  call 0xEBDBF20
    //   0xbc71ef8  nop
    //   0xbc71ef9  mov rax,rsi
    //   0xbc71efc  add rsp,0x40
    //   0xbc71f00  pop rbx
    //   0xbc71f01  pop rdi
    //   0xbc71f02  pop rsi
    //   0xbc71f03  pop r14
    //   0xbc71f05  pop rbp
    //   0xbc71f06  ret
    sub_ebdbf20(lock);                                    // 0xbc71ef3  call 0xEBDBF20   [`0xbc71ef3  call 0xEBDBF20`]
    return out;
}

static_assert(offsetof(Ctx, lockField) == 0x1C0, "sub_bc71da0: Ctx+0x1C0 lockField");
static_assert(offsetof(Ctx, stream) == 0x1CFD0C8, "sub_bc71da0: Ctx+0x1CFD0C8 stream");
static_assert(offsetof(Ctx, handleIndex) == 0x1DFC298, "sub_bc71da0: Ctx+0x1DFC298 handleIndex");
static_assert(offsetof(Ctx, handleMax) == 0x1DFC29A, "sub_bc71da0: Ctx+0x1DFC29A handleMax");
static_assert(offsetof(Ctx, handleSlots) == 0x1DFC29C, "sub_bc71da0: Ctx+0x1DFC29C handleSlots");
static_assert(offsetof(CommandStream, writePos) == 0xDC5818, "sub_bc71da0: CommandStream+0xDC5818 writePos");
static_assert(offsetof(CommandStream, data) == 0xDC5820, "sub_bc71da0: CommandStream+0xDC5820 data");

LIFT_FN(sub_bc71da0, "native::sub_bc71da0", 0xbc71da0, sub_bc71da0, sub_bc71da0Footprint);

} // namespace native
