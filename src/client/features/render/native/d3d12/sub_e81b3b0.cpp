// LIFT 0xe81b3b0 size 0x118 1.26.62.01 sub_e81b3b0
#include "sub_e81b3b0.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

// Layout constants live in sub_e81b3b0.h; cross-check the target model here [V].
static_assert(sizeof(void*) == 8, "e81b3b0: x64 target");
static_assert(sizeof(native::E81b3b0Context) == 0x38, "e81b3b0: context up to +0x38");
static_assert(sizeof(native::E81b3b0Element) == 0x88, "e81b3b0: element stride 0x88");

namespace native {

namespace {

// 0xE951550: __security_check_cookie (crt boundary, noreturn on failure) [V].
// Called at 0xe81b4c2 with rcx = cookieStored ^ frame when the /GS cookie check fails.
native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");

// Calls at 0xe81b3d8 / 0xe81b430 / 0xe81b47c go through `call qword ptr [0xF99FFA0]`.
// The cell at 0xF99FFA0 holds sub_eea6040, whose single instruction is `jmp rax`; rax is
// loaded from a vtable slot just before each call (0xe81b3d4 / 0xe81b429 / 0xe81b475).
// So each is a guarded virtual call; expressing it as the resolved vtable-slot invocation
// is exactly what the jmp-rax thunk chain does.

// 0xEEC59E0: _Xbad_function_call (class lift, but called as a boundary here). It is
// reached only from the per-element null check at 0xe81b420 / 0xe81b470 and never returns.
extern "C" void sub_eec59e0();

// UNRESOLVED CALL = none.

} // namespace

extern "C" bool sub_e81b3b0(void* self) {
    // 0xe81b3b0..0xe81b3c8: push r15/r14/rsi/rdi/rbx; sub rsp,0x30; mov rdi,rcx;
    //   /GS cookie: rax = [0x1230A0C0]; xor rax,rsp; mov [rsp+0x28],rax.
    std::uintptr_t cookieSlot = 0;
    const std::uintptr_t cookieStored =
        *reinterpret_cast<std::uintptr_t*>(kGblCookie) ^ reinterpret_cast<std::uintptr_t>(&cookieSlot);

    E81b3b0Context* ctx = static_cast<E81b3b0Context*>(self); // rdi = rcx throughout

    // 0xe81b3cd..0xe81b3e1: rcx = self->idSource (self+0x18); vt = *rcx;
    //   id = vt[0x40/8](rcx) via the jmp-rax thunk; self->id = id.
    void* const idSource = ctx->idSource;                          // 0xe81b3cd mov rcx,[rcx+0x18]
    void** const vt = *reinterpret_cast<void***>(idSource);        // 0xe81b3d1 mov rax,[rcx]
    void* const getIdTarget = vt[kVslotGetId / 8];                // 0xe81b3d4 mov rax,[rax+0x40]
    const std::uint64_t id =
        reinterpret_cast<std::uint64_t (*)(void*)>(getIdTarget)(idSource); // 0xe81b3d8 call qword ptr [0xF99FFA0]
    ctx->id = id;                                                  // 0xe81b3e1 mov [rdi+0x30],rax

    if (id != std::uint64_t(-1)) {
        // 0xe81b3e5..0xe81b3e9: cmp rax,-1 ; je loc_e81b444 (id == -1 -> the other loop).
        // 0xe81b3eb..0xe81b403: lea rax,[rsi-1]; cmp rax,[rdi+0x28]; jae (skip);
        //   r14 = begin (self+0x0); r15 = end (self+0x8); cmp r14,r15; je (skip).
        if ((id - 1) < ctx->count && ctx->begin != ctx->end) {
            // 0xe81b409: lea rbx,[rsp+0x20] (&local); 0xe81b40e: xchg ax,ax (nop).
            std::uint64_t local = 0;
            const E81b3b0Element* cur  = static_cast<const E81b3b0Element*>(ctx->begin); // r14 = begin
            const E81b3b0Element* last = static_cast<const E81b3b0Element*>(ctx->end);   // r15 = end

            // 0xe81b410..0xe81b442: LOOP A over [begin, end) stride 0x88.
            do {
                local = ctx->id;                                   // 0xe81b410 mov rax,[rdi+0x30] ; 0xe81b414 mov [rsp+0x20],rax
                void* const sub38 = cur->notify;                   // 0xe81b419 mov rcx,[r14+0x38]
                if (sub38 == nullptr) {                            // 0xe81b41d test rcx,rcx ; 0xe81b420 je 0xE81B4B5
                    sub_eec59e0();                                 // 0xe81b4b5 call 0xEEC59E0
                }
                void** const vt2 = *reinterpret_cast<void***>(sub38);      // 0xe81b426 mov rax,[rcx]
                void* const target = vt2[kVslotNotifyOne / 8];            // 0xe81b429 mov rax,[rax+0x10]
                reinterpret_cast<void (*)(void*, std::uint64_t*)>(target)( // 0xe81b42d mov rdx,rbx
                    sub38, &local);                                       // 0xe81b430 call qword ptr [0xF99FFA0]
                ++cur;                                             // 0xe81b436 add r14,0x88
            } while (cur != last);                                 // 0xe81b43d cmp r14,r15 ; 0xe81b440 jne ; 0xe81b442 jmp
        }
    } else {
        // 0xe81b444..0xe81b455: rbx = begin (self+0x0); r14 = end (self+0x8);
        //   cmp rbx,r14; je (skip); lea rdi,[rsp+0x20] (&local); nop.
        if (ctx->begin != ctx->end) {
            std::uint64_t local = 0;
            const E81b3b0Element* cur  = static_cast<const E81b3b0Element*>(ctx->begin); // rbx = begin
            const E81b3b0Element* last = static_cast<const E81b3b0Element*>(ctx->end);   // r14 = end

            // 0xe81b460..0xe81b48c: LOOP B over [begin, end) stride 0x88.
            do {
                local = std::uint64_t(-1);                         // 0xe81b460 mov qword ptr [rsp+0x20],0xFFFFFFFFFFFFFFFF
                void* const sub38 = cur->notify;                   // 0xe81b469 mov rcx,[rbx+0x38]
                if (sub38 == nullptr) {                            // 0xe81b46d test rcx,rcx ; 0xe81b470 je 0xE81B4B5
                    sub_eec59e0();                                 // 0xe81b4b5 call 0xEEC59E0
                }
                void** const vt2 = *reinterpret_cast<void***>(sub38);      // 0xe81b472 mov rax,[rcx]
                void* const target = vt2[kVslotNotifyOne / 8];            // 0xe81b475 mov rax,[rax+0x10]
                reinterpret_cast<void (*)(void*, std::uint64_t*)>(target)( // 0xe81b479 mov rdx,rdi
                    sub38, &local);                                       // 0xe81b47c call qword ptr [0xF99FFA0]
                ++cur;                                             // 0xe81b482 add rbx,0x88
            } while (cur != last);                                 // 0xe81b489 cmp rbx,r14 ; 0xe81b48c jne
        }
    }

    // 0xe81b48e..0xe81b492: cmp rsi,-1 ; setne al -> return (id != -1).
    const bool result = (id != std::uint64_t(-1));

    // 0xe81b495..0xe81b4a7: /GS epilogue. rcx = cookieStored ^ frame; cmp with [0x1230A0C0]; jne -> failure.
    if (*reinterpret_cast<std::uintptr_t*>(kGblCookie) !=
        (cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot))) {
        // 0xe81b4ba..0xe81b4c2: failure path (cookie mismatch).
        sub_e951550(cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot)); // 0xe81b4c2 call 0xE951550
        __assume(false);                                           // 0xe81b4c7 int3 (unreachable)
    }
    // 0xe81b4a9 add rsp,0x30 ; 0xe81b4ad pop rbx ; 0xe81b4ae pop rdi ; 0xe81b4af pop rsi ;
    //   0xe81b4b0 pop r14 ; 0xe81b4b2 pop r15 ; 0xe81b4b4 ret.
    return result;
}

static native::Footprint sub_e81b3b0_footprint(void* self) {
    return { { self, 0x38 } };
}

// Verbatim call instructions in [0xe81b3b0, 0xe81b4c8) (rdis dis output, two spaces after address):
#if 0
0xe81b3d8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe81b430  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe81b47c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe81b4b5  call 0xEEC59E0                                ; -> sub_eec59e0
0xe81b4c2  call 0xE951550                                ; -> sub_e951550
#endif

LIFT_FN(e81b3b0, "sub_e81b3b0", 0xE81B3B0, sub_e81b3b0, sub_e81b3b0_footprint);

} // namespace native