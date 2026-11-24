// LIFT 0xbc66c50 size 0x11e 1.26.62.01 Frame renderer lambda
#include "client/features/render/native/bgfx/sub_bc66c50.h"

#include <cstdint>
#include <intrin.h>

namespace native::bgfx {

// External calls of the original, all verbatim from the disassembly:
//   0xbc66c9d  call 0xEBDBF10   ; import thunk forwarder: jmp qword ptr [0xF9A7B10]
//   0xbc66cff  call 0xEBDB740   ; boundary (docs/data/native_boundary.tsv: 0xebdb740 os)
//   0xbc66d50  call 0xEBDBF20   ; import thunk forwarder: jmp qword ptr [0xF9A7B28]
//   0xbc66d5d  call 0xEBDBF20   ; import thunk forwarder: jmp qword ptr [0xF9A7B28]
// The two thunks are tiny forwarders (single jmp through a loader-resolved slot);
// they are forward-declared in native (sub_bc66c50.h) and called directly, exactly
// like the original direct calls. The os call goes through a native::Boundary
// wrapper (spec section 6), resolving sub_ebdb740 from Sigs.json.
native::Boundary<void*, std::uint16_t, std::uint16_t, std::uint16_t>
    sub_ebdb740("sub_ebdb740");

// Arguments/return (x64 Microsoft ABI): self = rcx, return in rax.
//   fast path:   return [self+0x13D18]
//   main path:   return element base at [self+0x13D18] + pick * 0x700
//   early exits: return 0
void* sub_bc66c50(void* self) {
    // 0xbc66c50..0xbc66c65: prologue (push rbp/rsi/rdi/rbx, sub rsp,0x38,
    // lea rbp,[rsp+0x30], EH marker [rbp] = -2); self = rcx
    std::uint8_t* const s = reinterpret_cast<std::uint8_t*>(self);   // 0xbc66c65  mov rsi,rcx

    // 0xbc66c68..0xbc66c85: backend-tag fast path: gidx = [0x128767C8];
    // entry = ((uintptr_t*)__readgsqword(0x58))[gidx];
    // if (*(uint32_t*)(entry + 0x2D4C) == 0x78666762 ("bgfx")) -> fast path
    const std::uint32_t gidx = *reinterpret_cast<const std::uint32_t*>(kGlobalRva);   // 0xbc66c68  mov eax,[0x128767C8]
    const std::uintptr_t tls = __readgsqword(kTlsOff);                                // 0xbc66c6e  mov rcx,gs:[0x58]
    const std::uintptr_t entry = reinterpret_cast<const std::uintptr_t*>(tls)[gidx];  // 0xbc66c77  mov rax,[rcx+rax*8]
    if (*reinterpret_cast<const std::uint32_t*>(entry + 0x2D4C) == kTagBgfx) {        // 0xbc66c7b cmp dword ptr [rax+0x2D4C],0x78666762 ; 0xbc66c85 jne short 0xBC66C93
        return reinterpret_cast<void*>(                                               // 0xbc66c87 mov rax,[rsi+0x13D18]
            *reinterpret_cast<const std::uintptr_t*>(s + kSelfOff_0x13D18));          // 0xbc66c8e jmp 0xBC66D65 (epilogue/ret)
    }

    // 0xbc66c93..0xbc66c9d: &self[0x180] + thunk call 0xEBDBF10 (rcx = &self[0x180])
    void* const field0x180_addr = s + kSelfOff_0x180;                                 // 0xbc66c93 lea rbx,[rsi+0x180]
    native::sub_ebdbf10(field0x180_addr);                                             // 0xbc66c9a mov rcx,rbx ; 0xbc66c9d call 0xEBDBF10

    // 0xbc66ca2..0xbc66cc1: u16 header [self+0x13D20]: hdr[0]=count, hdr[1]=limit;
    // count >= limit -> early exit (0xBC66D5A); else hdr[0] = count + 1
    std::uint16_t* const hdr = reinterpret_cast<std::uint16_t*>(                     // 0xbc66ca2 mov rax,[rsi+0x13D20]
        *reinterpret_cast<const std::uintptr_t*>(s + kSelfOff_0x13D20));
    const std::uint16_t count = hdr[kHdrOffCount];                                   // 0xbc66ca9 movzx ecx,word ptr [rax]
    const std::uint16_t limit = hdr[kHdrOffLimit];                                   // 0xbc66cac movzx edx,word ptr [rax+2]
    if (count >= limit) {                                                            // 0xbc66cb0 cmp cx,dx ; 0xbc66cb3 jae short 0xBC66D5A
        native::sub_ebdbf20(field0x180_addr);                                        // 0xbc66d5a mov rcx,rbx ; 0xbc66d5d call 0xEBDBF20
        return nullptr;                                                              // 0xbc66d63 xor eax,eax ; epilogue/ret
    }
    hdr[kHdrOffCount] = static_cast<std::uint16_t>(count + 1u);                      // 0xbc66cb9 movzx r8d,cx ; 0xbc66cbd lea r9d,[rcx+1] ; 0xbc66cc1 mov [rax],r9w
    const std::uint16_t pick = hdr[2u + count];                                      // 0xbc66cc5 movzx edi,word ptr [rax+r8*2+4]
    hdr[2u + limit + pick] = count;                                                  // 0xbc66ccb lea rax,[rax+rdx*2] ; 0xbc66ccf add rax,4 ; 0xbc66cd3 mov [rax+rdi*2],cx
    if (pick == kPickSentinel) {                                                     // 0xbc66cd7 cmp edi,0xFFFF ; 0xbc66cdd je short 0xBC66D5A
        native::sub_ebdbf20(field0x180_addr);                                        // 0xbc66d5a mov rcx,rbx ; 0xbc66d5d call 0xEBDBF20
        return nullptr;                                                              // 0xbc66d63 xor eax,eax ; epilogue/ret
    }

    // 0xbc66cdf..0xbc66cfb: save &self[0x180]; elem = array + pick*0x700; elem[0] = self[0x1CFD0C8]
    const void* const saved_field0x180 = field0x180_addr;                            // 0xbc66cdf mov [rbp-8],rbx
    std::uint8_t* const array = reinterpret_cast<std::uint8_t*>(                    // 0xbc66ce3 mov rax,[rsi+0x13D18]
        *reinterpret_cast<const std::uintptr_t*>(s + kSelfOff_0x13D18));
    const std::uintptr_t stride = static_cast<std::uintptr_t>(pick) * kElemStride;   // 0xbc66cea imul rbx,rdi,0x700
    const std::uint64_t field_0x1CFD0C8 =                                            // 0xbc66cf1 mov rcx,[rsi+0x1CFD0C8]
        *reinterpret_cast<const std::uint64_t*>(s + kSelfOff_0x1CFD0C8);
    ElemLayout* const elem = reinterpret_cast<ElemLayout*>(array + stride);          // 0xbc66cf8 mov rsi,rax
    elem->field_0x0000 = field_0x1CFD0C8;                                            // 0xbc66cfb mov [rax+rbx],rcx

    // 0xbc66cff: boundary call (os): sub_ebdb740(self[0x1CFD0C8], limit, count, count+1)
    const void* const created = sub_ebdb740(                                         // 0xbc66cff call 0xEBDB740
        reinterpret_cast<void*>(field_0x1CFD0C8), limit, count,
        static_cast<std::uint16_t>(count + 1u));
    // 0xbc66d04 nop
    elem->field_0x6F0 = created;                                                     // 0xbc66d05 add rsi,rbx ; 0xbc66d08 mov [rsi+0x6F0],rax
    elem->field_0x6AC = static_cast<std::uint8_t>(pick);                             // 0xbc66d0f mov [rsi+0x6AC],dil
    elem->field_0x694 = 0;                                                           // 0xbc66d16 mov qword ptr [rsi+0x694],0

    // 0xbc66d21..0xbc66d33: vtable chain: elem[0] (== field_0x1CFD0C8) ->
    // [+0xDC57E0] -> [+ (pick & 0xFF) * 8] -> +4 = 0
    const std::uintptr_t vtable = elem->field_0x0000;                                // 0xbc66d21 mov rax,[rsi]
    const std::uintptr_t p = *reinterpret_cast<const std::uintptr_t*>(               // 0xbc66d24 mov rax,[rax+0xDC57E0]
        vtable + kVtblChainOff);
    const std::uintptr_t q = *reinterpret_cast<const std::uintptr_t*>(               // 0xbc66d2b movzx ecx,dil ; 0xbc66d2f mov rax,[rax+rcx*8]
        p + static_cast<std::uintptr_t>(static_cast<std::uint8_t>(pick)) * 8);
    *reinterpret_cast<std::uint32_t*>(q + 4) = 0;                                    // 0xbc66d33 mov dword ptr [rax+4],0

    // 0xbc66d3a..0xbc66d50: clear elem[0x68C]/elem[0x688]; thunk call 0xEBDBF20
    // (rcx = [rbp-8] == &self[0x180])
    elem->field_0x68C = 0;                                                           // 0xbc66d3a mov qword ptr [rsi+0x68C],0
    elem->field_0x688 = 0;                                                           // 0xbc66d45 mov byte ptr [rsi+0x688],0
    native::sub_ebdbf20(field0x180_addr);                                            // 0xbc66d4c mov rcx,[rbp-8] ; 0xbc66d50 call 0xEBDBF20
    return reinterpret_cast<void*>(elem);                                            // 0xbc66d55 mov rax,rsi ; 0xbc66d58 jmp 0xBC66D65 ; epilogue/ret
    // 0xbc66d65..0xbc66d6d: epilogue (add rsp,0x38; pop rbx/rdi/rsi/rbp; ret)
}

native::Footprint sub_bc66c50_footprint(void* self) {
    // Declared written region: self-relative [0, 0x1CFD0C8+8) covers the self fields
    // (hdr pointer, count/limit, self[0x1CFD0C8]). Element stores at
    // [self+0x13D18] + pick * 0x700 + {0x0000, 0x688, 0x68C, 0x694, 0x6AC, 0x6F0}
    // and the vtable-chain store at *[elem[0] + 0xDC57E0 + (pick&0xFF)*8 + 4] have
    // dynamic targets, so they are not statically boundable here (documented V2
    // footprint gap; whole-frame V3 covers them).
    return { { { self, kSelfFootprintSize } } };
}

LIFT_FN(sub_bc66c50, "Frame renderer lambda", 0xbc66c50, sub_bc66c50,
        sub_bc66c50_footprint);

} // namespace native::bgfx
