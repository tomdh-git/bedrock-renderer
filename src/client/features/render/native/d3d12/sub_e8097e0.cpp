// LIFT 0xe8097e0 size 0x195 1.26.62.01 sub_e8097e0
#include "sub_e8097e0.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstring>

namespace native { namespace d3d12 {

namespace {

// sub_4687b0 is a 4-instruction vtable-dispatch thunk:
//   0x4687b0  mov rax,[rcx]        ; rax = *this (vtable)
//   0x4687b3  mov rax,[rax+0xD0]   ; rax = vtbl[0xD0/8]
//   0x4687ba  mov r10,[0xF99FFA0]  ; r10 = sub_eea6040 ("jmp rax")
//   0x4687c1  jmp r10              ; tail-call rax(this, rdx, r8, r9)
// Reproduced inline: a virtual call to vtable slot 0xD0 with (this, &buf, 1, 1).

struct FetchResult {
    std::uint8_t  bytes[0x10]; // [rsp+0x24..0x34) -> entry+0x00 (16-byte store)
    std::uint32_t value;       // [rsp+0x34..0x38) -> entry+0x10 (dword store)
};
static_assert(sizeof(FetchResult) == kFetchSize, "FetchResult size");

// sub_e951550 = __report_gsfailure (docs/data/native_boundary.tsv: class crt).
native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");

} // namespace

extern "C" void sub_e8097e0(void* a0) {
    unsigned char* rsi = static_cast<unsigned char*>(a0); // mov rsi,rcx
    const std::uintptr_t base = RewriteRegistry::imageBase();

    // 0xe8097e8..0xe8097f2  security cookie prologue
    const std::uintptr_t cookie = *reinterpret_cast<std::uintptr_t*>(base + kCookieRva);
    volatile std::uintptr_t cookieSlot = 0;                       // [rsp+0x38]
    const std::uintptr_t frame = reinterpret_cast<std::uintptr_t>(&cookieSlot);
    cookieSlot = cookie ^ frame;                                  // mov [rsp+0x38],rax

    // 0xe8097f7..0xe80980b  sub_eec6ec0(table, template, 0xA8)
    unsigned char* table = reinterpret_cast<unsigned char*>(base + kTableRva);
    native::sub_eec6ec0(table,
                        reinterpret_cast<const void*>(base + kTemplateRva),
                        static_cast<std::int32_t>(kTableBytes)); // 0xe80980b  call 0xEEC6EC0

    // Fetch one entry's value via this->vtable[0xD0](this,&buf,1,1), then store it.
    auto fetch = [&](unsigned char* entry) {
        FetchResult buf;
        void** vtbl = *reinterpret_cast<void***>(rsi);                       // mov rax,[rcx]
        using FetchFn = void (*)(void*, void*, int, int);
        reinterpret_cast<FetchFn>(vtbl[kThunkSlotOff / sizeof(void*)])(
            reinterpret_cast<void*>(rsi), &buf, 1, 1);                      // mov rax,[rax+0xD0]; jmp; 0x4687B0
        // store order matches the original: dword at +0x10 FIRST, then 16 bytes at +0x00
        *reinterpret_cast<std::uint32_t*>(entry + kEntryValueOff) = buf.value; // mov [base+0x10],eax
        std::memcpy(entry + kEntryDataOff, buf.bytes, kEntryDataLen);          // movups xmm0,[rsp+0x24]; movaps [base],xmm0
    };

    // 0xe809810..0xe80984a  block A: entry 0 (unconditional) + guard for entry 1
    fetch(table + kEntry0Off);
    if (*reinterpret_cast<std::uint32_t*>(table + kEntry1Off) != kGuardValue) fetch(table + kEntry1Off);
    // 0xe80984c..0xe809880  block B: entry 1 + guard for entry 2
    if (*reinterpret_cast<std::uint32_t*>(table + kEntry2Off) != kGuardValue) fetch(table + kEntry2Off);
    // 0xe809882..0xe8098b6  block C: entry 2 + guard for entry 3
    if (*reinterpret_cast<std::uint32_t*>(table + kEntry3Off) != kGuardValue) fetch(table + kEntry3Off);
    // 0xe8098b8..0xe8098ec  block D: entry 3 + guard for entry 5 (entry 4 at +0x60 is NOT touched)
    if (*reinterpret_cast<std::uint32_t*>(table + kEntry5Off) != kGuardValue) fetch(table + kEntry5Off);
    // 0xe8098ee..0xe809922  block E: entry 5 + guard for entry 6
    if (*reinterpret_cast<std::uint32_t*>(table + kEntry6Off) != kGuardValue) fetch(table + kEntry6Off);
    // 0xe809924..0xe809946  block F: entry 6

    // 0xe80994d..0xe809966  cookie check + normal return
    const std::uintptr_t check = static_cast<std::uintptr_t>(cookieSlot) ^ frame;
    if (check != cookie) {
        // 0xe809967..0xe809974  failure path (noreturn)
        sub_e951550(check);            // 0xe80996f  call 0xE951550
        __builtin_unreachable();       // 0xe809974  int3 (padding after the noreturn call)
    }
    // 0xe809961..0xe809966  add rsp,0x40 ; pop rsi ; ret
}

// Verbatim call instructions in [0xe8097e0, 0xe809975) (rdis dis, two spaces after address):
#if 0
0xe80980b  call 0xEEC6EC0
0xe809824  call 0x4687B0
0xe80985a  call 0x4687B0
0xe809890  call 0x4687B0
0xe8098c6  call 0x4687B0
0xe8098fc  call 0x4687B0
0xe809932  call 0x4687B0
0xe80996f  call 0xE951550
#endif

// Calls out of lifted code:
//   0xe80980b  call 0xEEC6EC0   -> sub_eec6ec0 (class lift, forward-declared, called directly)
//   0xe809824/0xe80985a/0xe809890/0xe8098c6/0xe8098fc/0xe809932  call 0x4687B0
//                                -> sub_4687b0 (vtable[0xD0] dispatch thunk; reproduced inline as a vtable call)
//   0xe80996f  call 0xE951550   -> sub_e951550 (class crt, native::Boundary)
//   UNRESOLVED CALL = none

// Registry entry
LIFT_FN(sub_e8097e0, "RendererContextD3D12 base slot 58", 0xe8097e0, sub_e8097e0, nullptr);

} } // namespace native::d3d12