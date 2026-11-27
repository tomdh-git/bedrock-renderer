// LIFT 0xe903360 size 0xa9 1.26.62.01 BgfxFrameBuilder slot 11
#include "client/features/render/native/dragon/sub_e903360.h"

#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc6af50.h"

#include <cstdint>

// Verbatim call quotes from the disassembly of [0xe903360, 0xe903409). [V]
#if 0
0xe90337d  call 0xBC6AF50
0xe903403  call 0xE951550
#endif

namespace native::dragon {

static_assert(kMaxResults * sizeof(std::uint32_t) == 0x2C,
              "sub_e903360: result buffer at rsp+0x2C is 11 u32 (rsp+0x2C..rsp+0x58)");

bool sub_e903360(std::uint8_t a1, std::uint32_t* /*a2*/) {
    // 0xe903360..0xe903376: prologue + stack cookie store
    //   push rbx; sub rsp,0x60; mov ebx,ecx           (bl = a1)
    //   mov rax,[0x1230A0C0]; xor rax,rsp; mov [rsp+0x58],rax
    const std::uintptr_t cookie_global =
        *reinterpret_cast<const std::uintptr_t*>(
            RewriteRegistry::imageBase() + kDataCookie);
    std::uintptr_t cookie_slot =
        cookie_global ^ reinterpret_cast<std::uintptr_t>(&cookie_slot);

    // 0xe903376..0xe90337d: call argument setup
    //   lea rdx,[rsp+0x2C]    (callee a2 = local buffer rsp+0x2C..rsp+0x58)
    //   mov cl,0xB            (callee a1 = 11, NOT the incoming a1)
    // The incoming a2 is overwritten by lea and never read. [V]
    std::uint32_t buffer[kMaxResults];   // rsp+0x2C; sub_bc6af50 writes buffer[0..sil], sil <= kMaxResults

    // 0xe90337d  call 0xBC6AF50
    //   sub_bc6af50(11, buffer); writes buffer[0..kMaxResults) (up to 11 u32) [V]
    native::bgfx::sub_bc6af50(static_cast<std::uint8_t>(kMaxResults), buffer);

    // 0xe903382..0xe903398: selection value edx
    //   dec bl; xor edx,edx; cmp bl,0xA; ja short 0xe903398   (edx stays 0 when a1-1 > 10)
    //   movzx eax,bl; lea rcx,[0xF440E10]; mov edx,[rcx+rax*4] (edx = kTable[a1-1]) [V]
    const std::uint8_t bl = static_cast<std::uint8_t>(a1 - 1);
    const std::uint32_t* const kTable =
        reinterpret_cast<const std::uint32_t*>(
            RewriteRegistry::imageBase() + kTableRva);
    std::uint32_t edx = 0;
    if (bl <= kMaxIndex) {
        edx = kTable[bl];
    }

    // 0xe903398..0xe9033da: scan buffer[0..kMaxResults) for edx
    //   xmm0=buffer[0..3], xmm1=buffer[4..7], broadcast edx; pcmpeqd x2, packssdw,
    //   pmovmskb -> any of the first 8 dwords equals edx; scalar compares of
    //   buffer[8] (al), buffer[9] (cl), buffer[10] (dl); or-combined into al. [V]
    // Reads every dword of the buffer, including entries sub_bc6af50 did not
    // write - identical stack-slot reads as the original (buffer[10] is never
    // written by sub_bc6af50 and is read as stack garbage here too).
    bool found = false;
    for (std::size_t idx = 0; idx < kMaxResults; ++idx) {
        found = found | (buffer[idx] == edx);
    }

    // 0xe9033da..0xe9033ee: stack cookie verify
    //   mov r9,[rsp+0x58]; xor r9,rsp; mov r10,[0x1230A0C0]; cmp r10,r9;
    //   jne short 0xe9033fb   (mismatch -> failure path) [V]
    if ((cookie_slot ^ reinterpret_cast<std::uintptr_t>(&cookie_slot)) != cookie_global) {
        // 0xe9033fb..0xe903409: cookie failure (noreturn)
        //   mov rcx,[rsp+0x58]; xor rcx,rsp; call 0xE951550; int3   [V]
        native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");
        sub_e951550(cookie_slot ^ reinterpret_cast<std::uintptr_t>(&cookie_slot));
        __assume(false);   // original executes int3 here (noreturn)
    }

    // 0xe9033ee..0xe9033fb: or al,cl; or al,dl; or al,r8b; add rsp,0x60;
    // pop rbx; ret   [V]
    return static_cast<bool>(found);
}

LIFT_FN(sub_e903360, "BgfxFrameBuilder slot 11", 0xe903360, sub_e903360, nullptr);

} // namespace native::dragon
