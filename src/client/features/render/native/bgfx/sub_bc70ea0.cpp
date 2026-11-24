// LIFT 0xbc70ea0 size 0xf2 1.26.62.01 sub_bc70ea0
#include "sub_bc70ea0.h"

#include <cstdint>

static_assert(sizeof(void*) == 8, "x64");

namespace native {

std::uint16_t* sub_bc70ea0(void* ctx /*rcx*/, std::uint16_t* out /*rdx*/, void* info /*r8*/, std::uint32_t arg /*r9d*/, std::uint16_t arg4 /*5th stack*/) {
    // 0xbc70ea0..0xbc70ec5 : prologue, stash args
    // r14d = arg (r9d), rdi = info (r8), rsi = out (rdx), rbx = ctx (rcx), r15w = arg4 (stack)
    (void)arg4;

    // 0xbc70eca..0xbc70ed1 : rcx = ctx + 0x1C0 (lock); store to [rbp-0x10]
    void* lock = static_cast<char*>(ctx) + 0x1C0;

    // 0xbc70ed5  call 0xEBDBF10
    // `0xbc70ed5  call 0xEBDBF10`
    sub_ebdbf10(lock);

    // 0xbc70eda..0xbc70ef5 : divide info->count? eax = [info+8]; edx=0; div r14d
    std::uint32_t val = *reinterpret_cast<std::uint32_t*>(static_cast<char*>(info) + 8);
    val = val / arg; // 0xbc70edf  div r14d

    // 0xbc70ee2 : stack arg for sub_bc70ca0 arg4 = r15w
    // 0xbc70ee8..0xbc70ef5 : lea rdx,[rbp-2]; rcx=ctx; r8d=val; r9d=arg
    std::uint16_t local = 0;
    // 0xbc70ef5  call 0xBC70CA0
    // `0xbc70ef5  call 0xBC70CA0`
    sub_bc70ca0(reinterpret_cast<State_bc70ca0*>(ctx), &local, val, arg, arg4);

    // 0xbc70efa  nop
    // 0xbc70efb..0xbc70f03 : if (local == 0xFFFF) goto fail path
    if (local != 0xFFFF) {
        // 0xbc70f05..0xbc70f0e : rcx=ctx; r8d=0; r9=info
        // 0xbc70f0e  call 0xBC70FF0
        // `0xbc70f0e  call 0xBC70FF0`
        sub_bc70ff0(reinterpret_cast<RenderContext_bc70ff0*>(ctx), local, 0, reinterpret_cast<std::uint64_t>(info));
        // 0xbc70f13  nop
        // 0xbc70f14  movzx ebx,word ptr [rbp-2]
        arg4 = local; // ebx = local (unused beyond)
        (void)arg4;
    } else {
        // 0xbc70f1a..0xbc70f38 : cleanup info via slot
        void* p0 = *reinterpret_cast<void**>(info);
        void** p1slot = reinterpret_cast<void**>(static_cast<char*>(info) + 0x10);
        void* p1 = *p1slot;
        if (p0 != static_cast<char*>(info) + 0x10) {
            if (p1 != nullptr) {
                void* p2 = *reinterpret_cast<void**>(static_cast<char*>(info) + 0x18);
                auto fn = *reinterpret_cast<void(*)(void*, void*, std::uint32_t, std::uint32_t)*>(kSlotF99FFA0);
                // 0xbc70f32  call qword ptr [0xF99FFA0]
                // `0xbc70f32  call qword ptr [0xF99FFA0]`
                fn(p0, p2, 0, 0);
            }
        }
        // 0xbc70f39..0xbc70f74 : global ptr
        // read [0x12ADF800]
        void* g = *reinterpret_cast<void**>(0x12ADF800ULL);
        if (g != nullptr) {
            // 0xbc70f49..0xbc70f71
            auto vtbl = *reinterpret_cast<void**>(g);
            auto m = *reinterpret_cast<void(*)(void*, void*, std::uint32_t, std::uint32_t, std::uint64_t, std::uint64_t)>(static_cast<char*>(vtbl) + 8);
            std::uint64_t zero = 0;
            // 0xbc70f71  call r10
            // `0xbc70f71  call r10`
            m(g, info, 0, 0, 0, 0);
        }
        // 0xbc70f75 : *out (rsi) = 0xFFFF
        // ebx = 0xFFFF
    }

    // 0xbc70f75  mov [rsi],bx   (bx = local on success, 0xFFFF on fail)
    *out = local;

    // 0xbc70f78..0xbc70f81 : unlock
    // 0xbc70f78  mov rcx,[rbp-0x10]  (lock)
    // 0xbc70f7c  call 0xEBDBF20
    // `0xbc70f7c  call 0xEBDBF20`
    sub_ebdbf20(lock);

    // 0xbc70f82  mov rax,rsi
    return out;
}

LIFT_FN(bc70ea0, "sub_bc70ea0", 0xBC70EA0, sub_bc70ea0, nullptr);

} // namespace native