// LIFT 0xe903290 size 0xc3 1.26.62.01 BgfxFrameBuilder slot 11
#include "client/features/render/native/dragon/sub_e903290.h"

#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc6af50.h"

#include <cstdint>

// Verbatim call quotes from the disassembly of [0xe903290, 0xe903353). [V]
#if 0
0xe9032bc  call 0xBC6AF50
0xe90334d  call 0xE951550
#endif

namespace native::dragon {

static_assert(kMaxResults * sizeof(std::uint32_t) == 0x2C,
              "sub_e903290: result buffer at rsp+0x2C is 11 u32 (rsp+0x2C..rsp+0x58)");

std::uint8_t* sub_e903290(std::uint8_t* a1, std::uint32_t a2) {
    // 0xe903290..0xe9032ad: prologue + stack cookie store
    //   push rsi/rdi/rbx; sub rsp,0x60; mov edi,edx (a2); mov rsi,rcx (a1)
    //   mov rax,[0x1230A0C0]; xor rax,rsp; mov [rsp+0x58],rax; xor ebx,ebx (result=0)
    //   test edi,0x100; je short 0xe903323   (if (a2 & 0x100)==0 -> end, result stays 0)
    const std::uintptr_t cookie_global =
        *reinterpret_cast<const std::uintptr_t*>(
            RewriteRegistry::imageBase() + kDataCookie);
    std::uintptr_t cookie_slot =
        cookie_global ^ reinterpret_cast<std::uintptr_t>(&cookie_slot);
    std::uint8_t result = 0;

    if ((a2 & 0x100u) != 0u) {
        // 0xe9032b5..0xe9032bc: call argument setup
        //   lea rdx,[rsp+0x2C]    (callee a2 = local buffer rsp+0x2C..rsp+0x58)
        //   mov cl,0xB            (callee a1 = 11)
        std::uint32_t buffer[kMaxResults];   // rsp+0x2C; sub_bc6af50 writes buffer[0..sil], sil <= kMaxResults

        // 0xe9032bc  call 0xBC6AF50
        //   sub_bc6af50(11, buffer); writes buffer[0..kMaxResults) (up to 11 u32) [V]
        native::bgfx::sub_bc6af50(static_cast<std::uint8_t>(kMaxResults), buffer);

        // 0xe9032c1..0xe9032d2: selection value ebx
        //   lea eax,[rdi-1]      (eax = a2 - 1)
        //   cmp al,0xA; ja short 0xe9032d5   (ebx stays 0 when (a2-1) > 10)
        //   movzx eax,al; lea rcx,[0xF440E10]; mov ebx,[rcx+rax*4] (ebx = kTable[(a2-1)]) [V]
        const std::uint8_t idx = static_cast<std::uint8_t>(a2 - 1u);
        const std::uint32_t* const kTable =
            reinterpret_cast<const std::uint32_t*>(
                RewriteRegistry::imageBase() + kTableRva);
        std::uint32_t ebx = 0;
        if (idx <= kMaxIndex) {
            ebx = kTable[idx];
        }

        // 0xe9032d5..0xe90331e: scan buffer for ebx
        //   xmm0=buffer[0..3], xmm1=buffer[4..7], broadcast ebx; pcmpeqd,
        //   packssdw, pmovmskb -> any of first 8 dwords equals ebx;
        //   scalar compares of buffer[8] (cl), buffer[9] (al), buffer[10] (cmp);
        //   or-combined into result [V]
        bool found = false;
        for (std::size_t k = 0; k < kMaxResults; ++k) {
            found = found | (buffer[k] == ebx);
        }

        if (found) {
            // 0xe90331e  mov [rsi],dil   (a1[0] = a2 & 0xFF)
            // 0xe903321  mov bl,1         (result = 1)
            a1[0] = static_cast<std::uint8_t>(a2);
            result = 1;
        }
        // If not found: result stays 0, a1[0] is NOT written (matches original)
    }
    // If (a2 & 0x100) == 0: result stays 0, a1 is NOT written at all (matches original)

    // 0xe903323  mov [rsi+1],bl   (a1[1] = result)
    a1[1] = result;

    // 0xe903326..0xe90333a: stack cookie verify + return
    //   mov rax,[rsp+0x58]; xor rax,rsp; mov rcx,[0x1230A0C0]; cmp rcx,rax;
    //   jne short 0xe903345   (mismatch -> failure path) [V]
    if ((cookie_slot ^ reinterpret_cast<std::uintptr_t>(&cookie_slot)) != cookie_global) {
        // 0xe903345..0xe903352: cookie failure (noreturn)
        //   mov rcx,[rsp+0x58]; xor rcx,rsp; call 0xE951550; int3   [V]
        native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");
        sub_e951550(cookie_slot ^ reinterpret_cast<std::uintptr_t>(&cookie_slot));
        __assume(false);   // original executes int3 here (noreturn)
    }

    // 0xe90333a  mov rax,rsi   (return a1)
    return a1;
}

native::Footprint sub_e903290_footprint(std::uint8_t* a1, std::uint32_t /*a2*/) {
    // Writes 2 bytes at a1 (a1[0], a1[1]) when (a2 & 0x100) != 0 and match found,
    // otherwise only a1[1]. Stack buffer and cookie slot are frame-local.
    return { { { a1, 2 } } };
}

LIFT_FN(sub_e903290, "BgfxFrameBuilder slot 11", 0xe903290, sub_e903290,
        sub_e903290_footprint);

} // namespace native::dragon
