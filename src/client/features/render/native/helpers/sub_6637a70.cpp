// LIFT 0x6637a70 size 0xf6 1.26.62.01 sub_6637a70
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_6637a70.h"

#include <cstdint>
#include <cstddef>
#include <cstring>

namespace native::helpers {

// Layout assertions (full set in sub_6637a70.h; duplicates here for liftcheck visibility).
static_assert(offsetof(SelfOut, object_ptr) == 0x0, "sub_6637a70: self+0x0");
static_assert(offsetof(SelfOut, base_ptr) == 0x8, "sub_6637a70: self+0x8");
static_assert(offsetof(AllocObject, f0x00) == 0x00, "sub_6637a70: obj+0x00");
static_assert(offsetof(AllocObject, f0x78) == 0x78, "sub_6637a70: obj+0x78");
static_assert(sizeof(AllocObject) == 0xA0, "sub_6637a70: object size 0xA0");

LIFT_FN(sub_6637a70, "sub_6637a70", 0x6637a70, sub_6637a70, nullptr);

// Verbatim call instructions from the disassembly of [0x6637a70, 0x6637b66) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x6637a8c  call qword ptr [0xF99FFA0]
0x6637b59  call 0x9BC830
#endif

uintptr_t sub_6637a70(void* self) {
    // 0x6637a70..0x6637a9b: prologue + vendor alloc attempt
    // 0x6637a70  push rsi
    // 0x6637a71  push rdi
    // 0x6637a72  sub rsp,0x28
    // 0x6637a76  mov rsi,rcx
    SelfOut* out = reinterpret_cast<SelfOut*>(self);

    // 0x6637a79  mov rcx,[0x1233E1A8]
    // 0x6637a80  mov rax,[rcx]
    // 0x6637a83  mov rax,[rax+8]
    void* global = *reinterpret_cast<void**>(0x1233E1A8ULL);
    void* a0 = *reinterpret_cast<void**>(global);
    void* a1 = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(a0) + 8);
    (void)a0;
    (void)a1;

    // 0x6637a87  mov edx,0xB0
    // 0x6637a8c  call qword ptr [0xF99FFA0]  ; vendor alloc thunk (global, 0xB0)
    auto allocFn = reinterpret_cast<void* (*)(void*, std::uint64_t)>(
        *reinterpret_cast<const std::uintptr_t*>(0xF99FFA0ULL));
    void* alloc = allocFn(global, 0xB0);

    // 0x6637a92  test rax,rax
    // 0x6637a95  je 0x6637B51                 ; if alloc == 0 goto fallback
    if (alloc == nullptr) {
        // 0x6637b51..0x6637b66: fallback alloc via sub_9bc830
        // 0x6637b51  mov ecx,0xB0
        // 0x6637b56  mov rdi,rax              ; rax == 0 here
        // 0x6637b59  call 0x9BC830            ; boundary alloc
        // 0x6637b5e  mov rax,rdi
        // 0x6637b61  jmp 0x6637A9B            ; fall through to init
        native::Boundary<void*, std::uint64_t> sub_9bc830("sub_9bc830");
        alloc = sub_9bc830(0xB0);
    }

    // 0x6637a9b..0x6637b51: initialize the allocated object
    // 0x6637a9b  mov rcx,0x100000001
    // 0x6637aa5  mov [rax+8],rcx
    auto* hdr = reinterpret_cast<AllocHeader*>(alloc);
    hdr->tag = 0x100000001ULL;

    // 0x6637aa9  lea rcx,[0xF121010]
    // 0x6637ab0  mov [rax],rcx
    hdr->vtable = *reinterpret_cast<void**>(0xF121010ULL);

    // 0x6637ab3  mov rcx,rax
    // 0x6637ab6  add rcx,0x10                 ; rcx = object pointer (alloc+0x10)
    auto* obj = reinterpret_cast<AllocObject*>(reinterpret_cast<std::uint8_t*>(alloc) + 0x10);

    // 0x6637aba  xorps xmm0,xmm0
    // 0x6637abd..0x6637ae3  movups clears of [rax+0x20..0xaf]
    // (memset below covers all object fields that the original clears to zero)
    std::memset(obj, 0, sizeof(AllocObject));

    // 0x6637aea  movaps xmm1,[0xF2BDD80]
    // 0x6637af1  movups [rax+0x10],xmm1
    {
        const double* d80 = reinterpret_cast<const double*>(0xF2BDD80ULL);
        obj->f0x00 = d80[0];
        obj->f0x08 = d80[1];
    }

    // 0x6637af5  mov dword ptr [rax+0x24],0x42055555
    {
        const std::uint32_t imm24 = 0x42055555u;
        std::memcpy(&obj->f0x14, &imm24, sizeof(obj->f0x14));
    }

    // 0x6637afc  movaps xmm1,[0xF2BDD90]
    // 0x6637b03  movups [rax+0x28],xmm1
    {
        const double* d90 = reinterpret_cast<const double*>(0xF2BDD90ULL);
        obj->f0x18 = d90[0];
        obj->f0x20 = d90[1];
    }

    // 0x6637b07  mov byte ptr [rax+0x38],1
    obj->f0x28 = 1;

    // 0x6637b0b  mov rdx,0x3FB999999999999A   ; double 0.1
    // 0x6637b15  mov [rax+0x40],rdx
    obj->f0x30 = 0.1;

    // 0x6637b19  mov [rax+0x58],rdx
    obj->f0x48 = 0.1;

    // 0x6637b1d  mov [rax+0x70],rdx
    obj->f0x60 = 0.1;

    // 0x6637b21  mov rdx,0x4040AAAAA0000000
    // 0x6637b2b  mov [rax+0x88],rdx
    {
        const std::uint64_t imm88 = 0x4040AAAAA0000000ULL;
        std::memcpy(&obj->f0x78, &imm88, sizeof(obj->f0x78));
    }

    // 0x6637b32  movups [rax+0x99],xmm0     (already zeroed by memset)
    // 0x6637b39  movups [rax+0x90],xmm0     (already zeroed by memset)

    // 0x6637b40  mov [rsi],rcx              ; self[0] = object_ptr
    out->object_ptr = obj;

    // 0x6637b43  mov [rsi+8],rax            ; self[8] = base_ptr
    out->base_ptr = alloc;

    // 0x6637b47  mov rax,rsi
    // 0x6637b4a  add rsp,0x28
    // 0x6637b4e  pop rdi
    // 0x6637b4f  pop rsi
    // 0x6637b50  ret
    return reinterpret_cast<uintptr_t>(self);
}

} // namespace native::helpers
