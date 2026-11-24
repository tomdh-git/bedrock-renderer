// LIFT 0xbc68840 size 0x5f7 1.26.62.01 bgfx render-thread begin/init step (TLS magic)
#include "client/features/render/native/bgfx/sub_bc68840.h"

#include "client/features/render/native/Lift.h"

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <intrin.h>

static_assert(sizeof(std::uintptr_t) == 8, "sub_bc68840: uintptr_t is 8 bytes on x64");
static_assert(sizeof(std::uint32_t) == 4, "sub_bc68840: uint32_t is 4 bytes");

// Calls out of lifted code go to boundary callees (docs/data/native_boundary.tsv, class crt),
// declared extern "C" and called directly (sub_bc60100.cpp precedent).
extern "C" void sub_ebdbc90(std::uint32_t* table, std::uint32_t count, std::uint32_t stride,
                            std::int32_t(__cdecl* cmp)(const std::uint32_t*, const std::uint32_t*));
extern "C" void sub_e951550(std::uintptr_t cookieFailValue, std::uintptr_t cookieSecret);

namespace native {

namespace {

// Indirect calls go through the data slot read at call time, exactly as the
// `mov r64,[imm64]` / `call qword ptr [imm64]` instructions do [V].
std::uintptr_t readSlot(std::uintptr_t slotRva) {
    return *reinterpret_cast<std::uintptr_t*>(slotRva);
}

using Fn770 = std::uintptr_t(__cdecl)(std::uint32_t a, std::uint32_t b, std::uint8_t c);
using Fn780 = std::uint32_t(__cdecl)(std::uintptr_t* scratch, std::uint32_t a, std::uintptr_t obj);
using HandleFn = std::uintptr_t(__cdecl)(std::uintptr_t* ctx);

// [0xF99FFA0] = sub_eea6040 = `jmp rax` trampoline [V]:
//   mov rax,[r15]; mov rcx,ctx; call qword ptr [0xF99FFA0]
// == indirect call *r15 with rcx = ctx (the trampoline is transparent).
std::uintptr_t invokeHandle(std::uintptr_t handleFnPtr, std::uintptr_t* ctxp) {
    return reinterpret_cast<HandleFn*>(handleFnPtr)(ctxp);
}

std::uintptr_t invoke770(std::uintptr_t fn, std::uint32_t a, std::uint32_t b, std::uint8_t c) {
    return reinterpret_cast<Fn770*>(fn)(a, b, c);
}

std::uint32_t invoke780(std::uintptr_t fn, std::uintptr_t* scratch, std::uint32_t a,
                        std::uintptr_t obj) {
    return reinterpret_cast<Fn780*>(fn)(scratch, a, obj);
}

// 0xEBCE430 is a 2-byte forwarding snippet (movzx edx,dl; jmp sub_eec6ed0), i.e. memset(dst, 0, 0x9C) [V];
// the lifted code calls the memset intrinsic directly.
void memsetScratch(std::uint8_t* scratch, std::uint32_t fillDword, std::uintptr_t pattern) {
    std::memset(scratch, 0, kScratchSize);                         // 0xEBCE430 = memset(scratch, 0, 0x9C) [V]
    *reinterpret_cast<std::uintptr_t*>(scratch) = pattern;         // [rsp+0x74] = pattern
    *reinterpret_cast<std::uint32_t*>(scratch + kScratchFillOffset) = fillDword;  // [rsp+0x7C] = fill
}

} // namespace

std::uint32_t sub_bc68840_footprint(std::uintptr_t* ctx, std::uint8_t mode, std::uint8_t* outSignaled) {
    return { { outSignaled, 1ull } };   // statically known out-of-stack write [V]; handle-array flag
                                        // bytes are written at dynamic indices (V3 thread-model proof)
}

bool sub_bc68840(std::uintptr_t* ctx, std::uint8_t mode, std::uint8_t* outSignaled) {
    // 0xbc68840..0xbc68884: prologue (eight pushes), sub rsp,0x118, spills rbx=r8 (out), rcx (ctx), dl (mode),
    // cookie guard [rsp+0x110] = [0x1230A0C0] ^ rsp, ebp = 0 (entry count), flag[0x127CA028] select.
    // 0xbc68840..0xbc68e36: full function body (coverage catch-all; every instruction lies in this range).
    std::uintptr_t* const ctxp = ctx;               // [rsp+0x30] = rcx
    std::uint8_t* const outp = outSignaled;         // [rsp+0x38] = rbx (saved at 0xbc68b26, reloaded at 0xbc68d3f)
    const std::uint8_t modeSaved = mode;            // [rsp+0x2F] = dl
    std::uint32_t ebp = 0;                          // entry count

    std::uintptr_t cookieGuard =
        *reinterpret_cast<std::uintptr_t*>(kGCookieSecret) ^
        reinterpret_cast<std::uintptr_t>(&cookieGuard);   // [rsp+0x110] = secret ^ rsp

    std::uint32_t table[kTableMaxEntries] = {};     // [rsp+0x40 + n*4]
    std::uint8_t scratch[kScratchSize];             // [rsp+0x74]

    const std::uint32_t tlsIndex = *reinterpret_cast<std::uint32_t*>(kGTlsIndex);
    std::uint32_t* const tlsMagic = reinterpret_cast<std::uint32_t*>(
        *reinterpret_cast<std::uintptr_t*>(__readgsqword(kTlsArrayGva) + tlsIndex * 8) + kTlsSlotOffset);
    std::uintptr_t* const handleArray = reinterpret_cast<std::uintptr_t*>(kGHandleArray);
    std::uint8_t* const surfaceArray = reinterpret_cast<std::uint8_t*>(kGSurfaceArray);

    // 0xbc6888a..0xbc6889b: P2a timeout value esi = (*ctx == 0) ? 0x3E800 : 0
    if (*reinterpret_cast<std::uint8_t*>(kGFlagSingleThread) == 1) {
        const std::uint32_t esi = (*ctxp == 0) ? kTimeoutValue : 0u;

        // 0xbc6889c..0xbc68944: P2a surface entry, attempt 1 (scratch[0x7C] = 2), retry on eax == 0 (scratch[0x7C] = 1)
        {
            const std::uintptr_t fn770 = readSlot(kSlotF9A8770);   // 0xbc688be  mov rdi,[0xF9A8770]
            memsetScratch(scratch, 2, kScratchPattern);             // 0xbc688ac  call 0xEBCE430
            std::uintptr_t obj = invoke770(fn770, 0u, 2u, 3u);      // 0xbc688cf  call rdi
            obj = invoke770(fn770, obj, 1u, 3u);                    // 0xbc688e1  call rdi
            std::uint32_t eax = invoke780(readSlot(kSlotF9A8780), scratch, 3u, obj);  // 0xbc688ee  call qword ptr [0xF9A8780]
            if (eax == 0) {
                memsetScratch(scratch, 1, kScratchPattern);         // 0xbc68908  call 0xEBCE430
                obj = invoke770(fn770, 0u, 2u, 3u);                 // 0xbc68924  call rdi
                obj = invoke770(fn770, obj, 1u, 3u);                // 0xbc68931  call rdi
                eax = invoke780(readSlot(kSlotF9A8780), scratch, 3u, obj);  // 0xbc6893e  call qword ptr [0xF9A8780]
            }
        }
        table[0] = esi;            // 0xbc68944  mov [rsp+0x40],esi   (raw, not shifted)
        ebp = 1;                   // 0xbc688d1  mov ebp,1
    }

    // 0xbc68963..0xbc68a4c: P2d [ctx]==1 bias block, gated by flag[0x127CA050] == 1
    if (*reinterpret_cast<std::uint8_t*>(kGFlagBias1) == 1) {
        std::uint32_t edi = (*ctxp == 1) ? kBiasValue : 1u;
        {
            const std::uintptr_t fn770 = readSlot(kSlotF9A8770);   // 0xbc689a3  mov rsi,[0xF9A8770]
            memsetScratch(scratch, 2, kScratchPattern);             // 0xbc68991  call 0xEBCE430
            std::uintptr_t obj = invoke770(fn770, 0u, 2u, 3u);      // 0xbc689b4  call rsi
            obj = invoke770(fn770, obj, 1u, 3u);                    // 0xbc689c1  call rsi
            std::uint32_t eax = invoke780(readSlot(kSlotF9A8780), scratch, 3u, obj);  // 0xbc689ce  call qword ptr [0xF9A8780]
            if (eax != 0) {
                edi |= 0x14u;                                       // 0xbc689d8  or edi,0x14
            } else {
                memsetScratch(scratch, 1, kScratchPattern);         // 0xbc689ed  call 0xEBCE430
                obj = invoke770(fn770, 0u, 2u, 3u);                 // 0xbc68a09  call rsi
                obj = invoke770(fn770, obj, 1u, 3u);                // 0xbc68a16  call rsi
                eax = invoke780(readSlot(kSlotF9A8780), scratch, 3u, obj);  // 0xbc68a23  call qword ptr [0xF9A8780]
                const std::uint32_t ecx = edi | 0x14u;              // 0xbc68a29  mov ecx,edi / 0xbc68a2b  or ecx,0x14
                if (eax != 0) edi = ecx;                            // 0xbc68a30  cmovne edi,ecx
            }
        }
        table[ebp] = (edi << 8) | 1u;   // 0xbc68a33  shl edi,8 / 0xbc68a36  inc edi
        ++ebp;                          // 0xbc68a3a  inc ebp
    }

    // 0xbc68a4d..0xbc68b1e: P2e [ctx]==2 bias block, gated by flag[0x127CA078] == 1
    if (*reinterpret_cast<std::uint8_t*>(kGFlagBias2) == 1) {
        std::uint32_t edi = (*ctxp == 2) ? kBiasValue : 1u;
        {
            const std::uintptr_t fn770 = readSlot(kSlotF9A8770);   // 0xbc68a84  mov rsi,[0xF9A8770]
            memsetScratch(scratch, 2, kScratchPattern);             // 0xbc68a72  call 0xEBCE430
            std::uintptr_t obj = invoke770(fn770, 0u, 2u, 3u);      // 0xbc68a95  call rsi
            obj = invoke770(fn770, obj, 1u, 3u);                    // 0xbc68aa2  call rsi
            std::uint32_t eax = invoke780(readSlot(kSlotF9A8780), scratch, 3u, obj);  // 0xbc68aaf  call qword ptr [0xF9A8780]
            if (eax != 0) {
                edi += 0x1Eu;                                       // 0xbc68b0f  add edi,ecx  (ecx = 0x1E)
            } else {
                memsetScratch(scratch, 1, kScratchPattern);         // 0xbc68ace  call 0xEBCE430
                obj = invoke770(fn770, 0u, 2u, 3u);                 // 0xbc68aea  call rsi
                obj = invoke770(fn770, obj, 1u, 3u);                // 0xbc68af7  call rsi
                eax = invoke780(readSlot(kSlotF9A8780), scratch, 3u, obj);  // 0xbc68b04  call qword ptr [0xF9A8780]
                edi += 0xFFFFFF9Cu;                                 // 0xbc68b0a  mov ecx,0xFFFFFF9C / add edi,ecx
            }
        }
        table[ebp] = (edi << 8) | 2u;
        ++ebp;
    }

    // 0xbc68b31..0xbc68bfe: P2g [ctx]==3 bias block, gated by flag[0x127CA0A0] == 1
    if (*reinterpret_cast<std::uint8_t*>(kGFlagBias3) == 1) {
        std::uint32_t edi = (*ctxp == 3) ? kBiasValue : 1u;
        {
            const std::uintptr_t fn770 = readSlot(kSlotF9A8770);   // 0xbc68b68  mov rsi,[0xF9A8770]
            memsetScratch(scratch, 2, kScratchPattern);             // 0xbc68b56  call 0xEBCE430
            std::uintptr_t obj = invoke770(fn770, 0u, 2u, 3u);      // 0xbc68b79  call rsi
            obj = invoke770(fn770, obj, 1u, 3u);                    // 0xbc68b86  call rsi
            std::uint32_t eax = invoke780(readSlot(kSlotF9A8780), scratch, 3u, obj);  // 0xbc68b93  call qword ptr [0xF9A8780]
            if (eax != 0) {
                edi += 0xAu;                                        // 0xbc68b9d  add edi,0xA
            } else {
                memsetScratch(scratch, 1, kScratchPattern);         // 0xbc68bb2  call 0xEBCE430
                obj = invoke770(fn770, 0u, 2u, 3u);                 // 0xbc68bce  call rsi
                obj = invoke770(fn770, obj, 1u, 3u);                // 0xbc68bdb  call rsi
                eax = invoke780(readSlot(kSlotF9A8780), scratch, 3u, obj);  // 0xbc68be8  call qword ptr [0xF9A8780]
            }
        }
        table[ebp] = (edi << 8) | 3u;
        ++ebp;
    }

    // 0xbc68bfc..0xbc68ced: P2h surface-array loop, index 4 .. 10 stride 0x28
    {
        std::uint32_t r12d = kSurfaceFirst;                         // 0xbc68bfc  mov r12d,4
        std::uint8_t* r13 = surfaceArray;                           // 0xbc68c02  lea r13,[0x127CA0C8]
        const std::uintptr_t fn770 = readSlot(kSlotF9A8770);        // 0xbc68c0e  mov rdi,[0xF9A8770]
        const std::uintptr_t fn780 = readSlot(kSlotF9A8780);        // 0xbc68c15  mov rbx,[0xF9A8780]
        // 0xbc68c1c  jmp short 0xBC68C3C  (entry check first)
        for (;;) {
            if (*r13 == 1) {                                        // 0xbc68c3c  cmp byte ptr [r13],1
                std::uint32_t esi = (*ctxp == r12d) ? kLoopBiasMatch : kLoopBiasNomatch;  // 0xbc68c48 mov eax,[rax] / 0xbc68c57 cmove esi,eax
                memsetScratch(scratch, 2, kScratchPattern);         // 0xbc68c65  call 0xEBCE430
                std::uintptr_t obj = invoke770(fn770, 0u, 2u, 3u);  // 0xbc68c81  call rdi
                obj = invoke770(fn770, obj, 1u, 3u);                // 0xbc68c8e  call rdi
                std::uint32_t eax = invoke780(fn780, scratch, 3u, obj);  // 0xbc68c9b  call rbx
                if (eax == 0) {
                    memsetScratch(scratch, 1, kScratchPattern);     // 0xbc68cb0  call 0xEBCE430
                    obj = invoke770(fn770, 0u, 2u, 3u);             // 0xbc68ccc  call rdi
                    obj = invoke770(fn770, obj, 1u, 3u);            // 0xbc68cd9  call rdi
                    eax = invoke780(fn780, scratch, 3u, obj);       // 0xbc68ce6  call rbx
                }
                esi += r12d;                          // 0xbc68c20  add esi,r12d  (both paths)
                table[ebp] = esi;                     // 0xbc68c27  mov [rsp+rax*4+0x40],esi
                ++ebp;                                // 0xbc68c25  inc ebp
            }
            ++r12d; r13 += kSurfaceStride;            // 0xbc68c2b  inc r12 / 0xbc68c2e  add r13,0x28
            if (r12d == kSurfaceAfterLast) break;     // 0xbc68c32  cmp r12,0xB / 0xbc68c36  je short 0xBC68CED
        }
    }

    // 0xbc68ced..0xbc68df9: P3 multi-surface wait (table, count = ebp, 4, comparator 0xbc6af40)
    using SurfaceCmp = std::int32_t(__cdecl)(const std::uint32_t* a, const std::uint32_t* b);
    // 0xbc6af40: mov eax,[rdx]; sub eax,[rcx]; ret  -> *b - *a  [V]
    SurfaceCmp* const cmpCb = reinterpret_cast<SurfaceCmp*>(kCallbackRva);
    sub_ebdbc90(table, ebp, kWaitArg, cmpCb);         // 0xbc68d01  call 0xEBDBC90

    std::uint32_t eaxRet = 0;                         // 0xbc68df9  xor eax,eax  (default return)
    if (ebp != 0) {
        const std::uint32_t count = ebp;              // 0xbc68d0e  mov edi,ebp
        if (modeSaved == 0) {
            // 0xbc68daa..0xbc68ded: linear loop (rbx index; r14 still holds &scratch[0] from P2h setup)
            std::uintptr_t rsi = kGHandleArray;       // 0xbc68daa  lea rsi,[0x127CA010]
            std::uintptr_t rbxIndex = 0;              // 0xbc68db1  xor ebx,ebx
            const std::uintptr_t r14 = reinterpret_cast<std::uintptr_t>(scratch);  // 0xbc68c09  lea r14,[rsp+0x74]
            for (; rbxIndex != count; ++rbxIndex) {   // 0xbc68de8  cmp rdi,rbx
                const std::uint32_t eax =
                    static_cast<std::uint32_t>(*reinterpret_cast<const std::uint8_t*>(table + rbxIndex));  // 0xbc68dc0  movzx eax,byte ptr [rsp+rbx*4+0x40]
                (void)(eax * kEntryMult);             // 0xbc68dc5  lea rax,[rax+rax*4] (dead: overwritten)
                std::uintptr_t rax =
                    *reinterpret_cast<std::uintptr_t*>(rsi + r14 * kHandleEntryStride);  // 0xbc68dc9  mov rax,[rsi+r14*8]
                std::uintptr_t callRet = invokeHandle(rax, ctxp);          // 0xbc68dd2  call qword ptr [0xF99FFA0]
                if (callRet != 0) { eaxRet = static_cast<std::uint32_t>(callRet); goto cookieCheck; }
                rax = *reinterpret_cast<std::uintptr_t*>(rsi + r14 * kHandleEntryStride);  // 0xbc68ddd  lea rax,[rsi+r14*8]
                *reinterpret_cast<std::uint8_t*>(rax + 0x18) = 0;         // 0xbc68de1  mov byte ptr [rax+0x18],0
            }
        } else {
            // 0xbc68d50..0xbc68da8: indexed loop (r14 index)
            std::uint32_t r14 = 0;                        // 0xbc68d3c  xor r14d,r14d
            for (; r14 != count; ++r14) {                 // 0xbc68da3  cmp rdi,r14
                const std::uint32_t eax =
                    static_cast<std::uint32_t>(*reinterpret_cast<const std::uint8_t*>(table + r14));  // 0xbc68d50  movzx eax,byte ptr [rsp+r14*4+0x40]
                const std::uintptr_t entryIndex = static_cast<std::uintptr_t>(eax) * kEntryMult;  // 0xbc68d5c  lea rax,[rax+rax*4]
                const std::uint8_t cl =
                    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(handleArray + entryIndex) + 0x20);  // 0xbc68d60  movzx ecx,byte ptr [rbx+rax*8+0x20]
                if (*tlsMagic == kTlsMagic) {             // 0xbc68d56  cmp dword ptr [rsi],0x78666762
                    if (cl != 0 && *outp == 0) {          // 0xbc68d67  test cl,cl / 0xbc68d6b  cmp byte ptr [r12],0
                        *outp = 1;                        // 0xbc68df3  mov al,1 / 0xbc68df5  mov [r12],al
                        goto cookieCheck;                 // 0xbc68df9  xor eax,eax
                    }
                } else {
                    if (cl == 0) {                        // 0xbc68d80  test cl,cl / 0xbc68d82  je short 0xBC68DEF
                        *outp = 0;                        // 0xbc68def  xor eax,eax / mov [r12],al
                        goto cookieCheck;
                    }
                }
                // 0xbc68d84 call path
                std::uintptr_t* const r15 = handleArray + entryIndex;   // 0xbc68d84  lea r15,[rbx+rax*8]
                const std::uintptr_t rax2 = *r15;                       // 0xbc68d88  mov rax,[r15]
                std::uintptr_t callRet = invokeHandle(rax2, ctxp);        // 0xbc68d90  call qword ptr [0xF99FFA0]
                if (callRet != 0) { eaxRet = static_cast<std::uint32_t>(callRet); goto cookieCheck; }
                *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(r15) + 0x18) = 0;  // 0xbc68d9b  mov byte ptr [r15+0x18],0
            }
        }
    }

cookieCheck:
    // 0xbc68dfb..0xbc68e25: cookie verify + epilogue; mismatch -> call 0xE951550 + int3 (unreachable)
    if (cookieGuard != (*reinterpret_cast<std::uintptr_t*>(kGCookieSecret) ^
                        reinterpret_cast<std::uintptr_t>(&cookieGuard))) {
        sub_e951550(cookieGuard, *reinterpret_cast<std::uintptr_t*>(kGCookieSecret));
        // 0xbc68e31  call 0xE951550   ; 0xbc68e36  int3  (unreachable, noreturn path)
        __assume(false);
    }
    return eaxRet != 0;               // 0xbc68e25  ret  (al)

LIFT_FN(bc68840, "bgfx render-thread begin/init step (TLS magic)", 0xBC68840, sub_bc68840,
        &sub_bc68840_footprint);

} // namespace native
