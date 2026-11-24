# Dossier: sub_bc70ca0 (0xbc70ca0)

## Mechanical facts

- size 0x1b0 bytes (0xbc70ca0..0xbc70e50), 93 instructions, 6 pushes (rbp, r15, r14, rsi, rdi, rbx), stack frame 0x48, frame pointer rbp = rsp + 0x40, security cookie at [rbp] [V: disassembly].
- 5 xrefs in (rdis header); one caller is sub_bc70ea0 (0xbc70ef5 `call 0xBC70CA0`) [V].
- Argument map (x64 Microsoft ABI): rcx = state object pointer, rdx = out (uint16_t*), r8d = arg2, r9d = arg3, 5th argument is a uint16_t passed on the stack ([rbp+0x60] = entry_rsp+0x28, the first stack argument slot), return value rax = out [V: register usage and final `mov rax,rsi`].
- Stack slots used: [rbp-0xC] saved arg3 (r9d), [rbp-4] popped value (u16), [rbp-8] product (u32), [rbp-1] tag byte 0x0F, [rbp-0x18] saved r15 (= state + 0x1C0) [V].
- Direct callees: 0xEBDBF10 sub_ebdbf10 (x1), 0xEBCE390 sub_ebce390 (x5), 0xEBDBF20 sub_ebdbf20 (x1). All three are classified lift (auto-unresolved->lift) in docs/data/native_boundary.tsv; this unit forward-declares them as native::sub_ebce390 / native::sub_ebdbf10 / native::sub_ebdbf20 and calls them directly [V: native_boundary.tsv lines 509-511].
- No indirect calls, no vtable reads, no strings, no loops [V: full body below].
- Fields touched (all [V] from the body): state+0x1C0 lock (passed to sub_ebdbf10/sub_ebdbf20), state+0x1CFD0C8 CommandBuffer* (read), state+0x1DF7488 u16 count (R/W), state+0x1DF748A u16 max (R), state+0x1DF748C u16 dense list (read at index count; written at index max+val, i.e. the reverse map following the dense list), state+0x1E7DAF0 Record[] stride 0x28 (fields +0x00 u32 = arg3, +0x04 u32 = arg2, +0x08 u16 = 1 at index val), state+0x1EBF1E8 u64 accumulator (+= (uint32)(arg3*arg2)); CommandBuffer+0xDC5818 u32 cursor (R/W), CommandBuffer+0xDC5820 inline data[] (W: tag, u16, u32, u32, u16 with the original's alignment steps) [V].

## Purpose

sub_bc70ca0 pops one entry from a u16 handle allocator embedded in the state object (count/max at +0x1DF7488/+0x1DF748A, dense list at +0x1DF748C with a reverse map at values[max+i]), stores a 3-field record indexed by the popped value, advances a u64 accumulator by (uint32)(arg3*arg2), and emits a 5-field command packet (tag 0x0F, u16 value, u32 arg3, u32 product, u16 5th argument) into the command buffer at state+0x1CFD0C8 (+0xDC5818 cursor, +0xDC5820 data), all under the context critical section at state+0x1C0 (sub_ebdbf10/sub_ebdbf20). Returns the out pointer (*out = value or 0xFFFF when the allocator is exhausted or the value is 0xFFFF). Role is [I] (BGFX_MAP section 6ai suggests "create (view/frame-buffer related)"); the mechanics above are [V].

## Signature (real argument list and calling convention)

```cpp
std::uint16_t* sub_bc70ca0(State* state /*rcx*/, std::uint16_t* out /*rdx*/,
                           std::uint32_t arg2 /*r8d*/, std::uint32_t arg3 /*r9d*/,
                           std::uint16_t arg4 /*5th argument, stack*/);
```

## Reversed source (complete)

```cpp
// LIFT 0xbc70ca0 size 0x1b0 1.26.62.01 sub_bc70ca0
#include "sub_bc70ca0.h"

namespace native {

std::uint16_t* Bc70ca0_lifted(State* state /*rcx*/, std::uint16_t* out /*rdx*/,
                              std::uint32_t arg2 /*r8d*/, std::uint32_t arg3 /*r9d*/,
                              std::uint16_t arg4 /*5th argument, passed on the stack*/) {
    // 0xbc70ca0..0xbc70cd3 : prologue (pushes, frame, cookie), argument stash and lock address
    //   state = rcx, out = rdx, arg2 = r8d, arg3 = r9d, arg4 = 5th stack argument;
    //   r15 = state + 0x1C0 = &state->lock

    // 0xbc70cd3
    sub_ebdbf10(static_cast<void*>(&state->lock));   // 0xbc70cd3  call 0xEBDBF10

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
    sub_ebce390(buf->data + c0, &tag, 1);                       // 0xbc70d7a  call 0xEBCE390  (rcx=buf->data+c0, rdx=&tag, r8d=1)
    buf->cursor = (c0 & 0xFFFFFFFEu) + 2u;                      // 0xbc70d87  mov ecx,[rbx+0xDC5818] ; and ecx,0xFFFFFFFE ; add ecx,2 ; 0xbc70d93  mov [rbx+0xDC5818],ecx
    sub_ebce390(buf->data + buf->cursor, &local, 2);            // 0xbc70da6  call 0xEBCE390  (rcx=buf->data+cursor, rdx=&local, r8d=2)
    buf->cursor = (buf->cursor + 5u) & 0xFFFFFFFCu;             // 0xbc70dac  mov ecx,[rbx+0xDC5818] ; add ecx,5 ; and ecx,0xFFFFFFFC ; 0xbc70db8  mov [rbx+0xDC5818],ecx
    sub_ebce390(buf->data + buf->cursor, &arg3, 4);             // 0xbc70dcb  call 0xEBCE390  (rcx=buf->data+cursor, rdx=[rbp-0xC]=arg3, r8d=4)
    buf->cursor = (buf->cursor + 7u) & 0xFFFFFFFCu;             // 0xbc70dd1  mov ecx,[rbx+0xDC5818] ; add ecx,7 ; and ecx,0xFFFFFFFC ; 0xbc70ddd  mov [rbx+0xDC5818],ecx
    sub_ebce390(buf->data + buf->cursor, &product, 4);          // 0xbc70df0  call 0xEBCE390  (rcx=buf->data+cursor, rdx=[rbp-8]=product, r8d=4)
    std::uint32_t c4 = (buf->cursor + 5u) & 0xFFFFFFFEu;        // 0xbc70df6  mov eax,[rbx+0xDC5818] ; add eax,5 ; and eax,0xFFFFFFFE ; 0xbc70e02  mov [rbx+0xDC5818],eax
    sub_ebce390(buf->data + c4, &arg4, 2);                      // 0xbc70e18  call 0xEBCE390  (rcx=buf->data+c4 [add rdi,rax], rdx=[rbp+0x60]=arg4, r8d=2)
    buf->cursor = c4 + 2u;                                      // 0xbc70e1e  add dword ptr [rbx+0xDC5818],2

    // 0xbc70e25..0xbc70e30 : *out = value
    *out = local;                                               // 0xbc70e25  movzx eax,word ptr [rbp-4] ; 0xbc70e29  mov [rsi],ax
    goto done;

fail:
    // 0xbc70e32 : failure path (*out = 0xFFFF)
    *out = 0xFFFF;                                              // 0xbc70e32  mov word ptr [rsi],0xFFFF

done:
    // 0xbc70e37..0xbc70e4f : release the lock and return the out pointer
    sub_ebdbf20(static_cast<void*>(&state->lock));   // 0xbc70e3a  call 0xEBDBF20
    return out;                                                 // 0xbc70e40  mov rax,rsi ; 0xbc70e43..0xbc70e4f  epilogue, ret
}

} // namespace native
```

## Structs touched (offsets confirmed [V] from this body)

- `native::Bc70ca0Layout::State` (src/client/features/render/native/bgfx/sub_bc70ca0.h): lock +0x1C0, cmdBuffer +0x1CFD0C8, count +0x1DF7488, max +0x1DF748A, values (dense list + reverse map) at +0x1DF748C, records at +0x1E7DAF0 (stride 0x28), accumulator +0x1EBF1E8. Each offset carries a static_assert in the header.
- `native::Bc70ca0Layout::CommandBuffer`: cursor +0xDC5818, data +0xDC5820 (static_asserted).
- `native::Bc70ca0Layout::Record`: stride 0x28, fields +0x00/+0x04/+0x08 (static_asserted).

## Callees

| address | name | class | source |
|---|---|---|---|
| 0xEBDBF10 | native::sub_ebdbf10 | lift (forward-declared here; body lifted by its own unit) | native_boundary.tsv line 510 |
| 0xEBCE390 | native::sub_ebce390 | lift (forward-declared here; body lifted by its own unit) | native_boundary.tsv line 509 |
| 0xEBDBF20 | native::sub_ebdbf20 | lift (forward-declared here; body lifted by its own unit) | native_boundary.tsv line 511 |

No call is outside the lift set: there are no UNRESOLVED CALLs.

## Ownership / threading

The whole body runs under the context critical section at state+0x1C0: sub_ebdbf10 is called at entry (0xbc70cd3) and sub_ebdbf20 on every exit path, including both failure branches [V]. The command buffer at state+0x1CFD0C8 is the API-thread command/lock state (ctx+0x1CFD0C8 per BGFX_MAP.md 603) [V/I]. No other synchronization; fail-fast (no null guards, no SEH: none exist in the original) [V].

## Version anchors

- Target: Minecraft Windows 1.26.62.01, image-base RVAs.
- Source marker: `// LIFT 0xbc70ca0 size 0x1b0 1.26.62.01 sub_bc70ca0` (src/client/features/render/native/bgfx/sub_bc70ca0.cpp line 1).
- Registry: LIFT_FN(bc70ca0, "sub_bc70ca0", 0xBC70CA0, Bc70ca0_lifted, nullptr) in the same .cpp.
