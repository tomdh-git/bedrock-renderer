// LIFT 0xbc70ca0 size 0x1b0 1.26.62.01 sub_bc70ca0
#include "sub_bc70ca0.h"

#include <cstdint>

namespace native {

namespace {

// Lifted body of sub 0xbc70ca0 (bgfx command allocator / command-buffer encoder, size 0x1b0, 1.26.62.01).
//
// Control flow follows the original exactly:
//   prologue -> lock state+0x1C0 (sub_ebdbf10) -> handle-allocator pop (state+0x1DF7488 count,
//   +0x1DF748A max, +0x1DF748C dense list, reverse map at values[max + i]) -> store record at
//   records[val] (stride 0x28) -> accumulator at +0x1EBF1E8 += (uint32)(arg3 * arg2) -> emit the
//   command packet into cmdBuffer->data (cursor +0xDC5818, data +0xDC5820): tag byte 0x0F, u16 val,
//   u32 arg3, u32 product, u16 5th argument, with the original's alignment steps -> *out = val
//   (0xFFFF on either failure) -> unlock (sub_ebdbf20) -> return out.
// Both failure branches (count >= max at 0xbc70ce9, val == 0xFFFF at 0xbc70d1f) write *out = 0xFFFF,
// unlock and return out, exactly as the original.
//
// Argument/return map (x64 Microsoft ABI): rcx = state, rdx = out, r8d = arg2, r9d = arg3, the
// 5th argument (u16) is passed on the stack ([rbp+0x60] in the original frame), rax = out on return.

std::uint16_t* Bc70ca0_lifted(State* state /*rcx*/, std::uint16_t* out /*rdx*/,
                              std::uint32_t arg2 /*r8d*/, std::uint32_t arg3 /*r9d*/,
                              std::uint16_t arg4 /*5th argument, passed on the stack*/) {
    // 0xbc70ca0..0xbc70cd3 : prologue (pushes, frame, cookie), argument stash and lock address
    //   state = rcx, out = rdx, arg2 = r8d, arg3 = r9d, arg4 = 5th stack argument;
    //   r15 = state + 0x1C0 = &state->lock

    // 0xbc70cd3  call 0xEBDBF10
    // `0xbc70cd3  call 0xEBDBF10`
    sub_ebdbf10(static_cast<void*>(&state->lock));

    // 0xbc70cd8..0xbc70ce9 : allocator header read and bounds check
    std::uint16_t count = state->count;                         // 0xbc70cd8  movzx eax,word ptr [rbx+0x1DF7488]
    std::uint16_t max = state->max;                             // 0xbc70cdf  movzx ecx,word ptr [rbx+0x1DF748A]
    if (count >= max) goto fail;                                // 0xbc70ce6  cmp ax,cx ; 0xbc70ce9  jae 0xBC70E32

    // 0xbc70cef..0xbc70d1f : pop a handle, advance the count, set the reverse map
    state->count = static_cast<std::uint16_t>(count + 1);       // 0xbc70cf6  mov [rbx+0x1DF7488],r8w
    std::uint16_t* const values = reinterpret_cast<std::uint16_t*>(
        reinterpret_cast<std::uint8_t*>(state) + Bc70ca0Layout::offValues);
    std::uint16_t val = values[count];                          // 0xbc70cfe  movzx edx,word ptr [rbx+rdx*2+0x1DF748C]
    values[max + val] = count;                                  // 0xbc70d11  mov [rcx+rdx*2],ax
                                                                  //   (rcx = state + 0x1DF748C + 2*max, i.e. reverseMap[val])
    std::uint16_t local = val;                                  // 0xbc70d15  mov [rbp-4],dx
    if (val == 0xFFFF) goto fail;                               // 0xbc70d19  cmp edx,0xFFFF ; 0xbc70d1f  je 0xBC70E32

    // 0xbc70d25..0xbc70d4d : record store at records[val], then accumulator update
    Record* const records = reinterpret_cast<Record*>(
        reinterpret_cast<std::uint8_t*>(state) + Bc70ca0Layout::offRecords);
    records[val].field00 = arg3;                                // 0xbc70d2d  mov [rbx+rax*8+0x1E7DAF0],edi  (rax = val*5 = stride 0x28; edi = arg3)
    records[val].field04 = arg2;                                // 0xbc70d34  mov [rbx+rax*8+0x1E7DAF4],r14d (r14d = arg2)
    records[val].field08 = 1;                                   // 0xbc70d3c  mov word ptr [rbx+rax*8+0x1E7DAF8],1
    const std::uint32_t product = static_cast<std::uint32_t>(arg3 * arg2);   // 0xbc70d46  imul edi,r14d
    state->accumulator += static_cast<std::uint64_t>(product);  // 0xbc70d4d  add [rbx+0x1EBF1E8],rdi  (rdi = zero-extended product)

    // 0xbc70d54..0xbc70e1e : command packet into cmdBuffer->data (cursor +0xDC5818, data +0xDC5820)
    CommandBuffer* const buf = state->cmdBuffer;                // 0xbc70d54  mov rbx,[rbx+0x1CFD0C8]
    const std::uint8_t tag = 0x0F;                              // 0xbc70d5b  mov byte ptr [rbp-1],0xF
    std::uint32_t c0 = buf->cursor;                             // 0xbc70d5f  mov eax,[rbx+0xDC5818]
    // 0xbc70d7a  call 0xEBCE390
    // `0xbc70d7a  call 0xEBCE390`
    sub_ebce390(buf->data + c0, &tag, 1);
    buf->cursor = (c0 & 0xFFFFFFFEu) + 2u;                      // 0xbc70d87  mov ecx,[rbx+0xDC5818] ; and ecx,0xFFFFFFFE ; add ecx,2 ; 0xbc70d93  mov [rbx+0xDC5818],ecx
    // 0xbc70da6  call 0xEBCE390
    // `0xbc70da6  call 0xEBCE390`
    sub_ebce390(buf->data + buf->cursor, &local, 2);
    buf->cursor = (buf->cursor + 5u) & 0xFFFFFFFCu;             // 0xbc70dac  mov ecx,[rbx+0xDC5818] ; add ecx,5 ; and ecx,0xFFFFFFFC ; 0xbc70db8  mov [rbx+0xDC5818],ecx
    // 0xbc70dcb  call 0xEBCE390
    // `0xbc70dcb  call 0xEBCE390`
    sub_ebce390(buf->data + buf->cursor, &arg3, 4);
    buf->cursor = (buf->cursor + 7u) & 0xFFFFFFFCu;             // 0xbc70dd1  mov ecx,[rbx+0xDC5818] ; add ecx,7 ; and ecx,0xFFFFFFFC ; 0xbc70ddd  mov [rbx+0xDC5818],ecx
    // 0xbc70df0  call 0xEBCE390
    // `0xbc70df0  call 0xEBCE390`
    sub_ebce390(buf->data + buf->cursor, &product, 4);
    std::uint32_t c4 = (buf->cursor + 5u) & 0xFFFFFFFEu;        // 0xbc70df6  mov eax,[rbx+0xDC5818] ; add eax,5 ; and eax,0xFFFFFFFE ; 0xbc70e02  mov [rbx+0xDC5818],eax
    // 0xbc70e18  call 0xEBCE390
    // `0xbc70e18  call 0xEBCE390`
    sub_ebce390(buf->data + c4, &arg4, 2);
    buf->cursor = c4 + 2u;                                      // 0xbc70e1e  add dword ptr [rbx+0xDC5818],2

    // 0xbc70e25..0xbc70e30 : *out = value
    *out = local;                                               // 0xbc70e25  movzx eax,word ptr [rbp-4] ; 0xbc70e29  mov [rsi],ax
    goto done;

fail:
    // 0xbc70e32 : failure path (*out = 0xFFFF)
    // 0xbc70e32  mov word ptr [rsi],0xFFFF
    *out = 0xFFFF;

done:
    // 0xbc70e37..0xbc70e4f : release the lock and return the out pointer
    // 0xbc70e3a  call 0xEBDBF20
    // `0xbc70e3a  call 0xEBDBF20`
    sub_ebdbf20(static_cast<void*>(&state->lock));
    return out;                                                 // 0xbc70e40  mov rax,rsi ; 0xbc70e43..0xbc70e4f  epilogue, ret
}

} // namespace

LIFT_FN(bc70ca0, "sub_bc70ca0", 0xBC70CA0, Bc70ca0_lifted, nullptr);

} // namespace native
