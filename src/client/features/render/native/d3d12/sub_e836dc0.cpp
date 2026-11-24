// LIFT 0xe836dc0 size 0x131 1.26.62.01 sub_e836dc0

#include "sub_e836dc0.h"

#include <cstring>
#include <cstddef>

static_assert(sizeof(void*) == 8, "abi");

namespace native { namespace d3d12 {

extern "C" void* sub_e836dc0(void* a0_, void* a1_) {
    auto* a0 = reinterpret_cast<unsigned char*>(a0_);
    auto* a1 = reinterpret_cast<unsigned char*>(a1_);

    // 0xe836dc0..0xe836de3
    // xorps xmm0,xmm0; movups [rcx],xmm0
    std::memset(a0, 0, 0x10);
    void* p = *reinterpret_cast<void**>(a1 + 8);
    if (p) {
        // lock inc dword ptr [rax+8]
        ++*reinterpret_cast<volatile int*>(static_cast<unsigned char*>(p) + 8);
    }

    // 0xe836de7..0xe836e37
    // mov rax,[rdx]; mov [rcx],rax
    *reinterpret_cast<void**>(a0) = *reinterpret_cast<void**>(a1);
    // mov rax,[rdx+8]; mov [rcx+8],rax
    *reinterpret_cast<void**>(a0 + 8) = *reinterpret_cast<void**>(a1 + 8);
    void* saved = a1;
    (void)saved;
    void* base = *reinterpret_cast<void**>(a1);
    uint64_t val = *reinterpret_cast<uint32_t*>(static_cast<unsigned char*>(base) + 0x18);
    *reinterpret_cast<uint64_t*>(a0 + 0x10) = val;
    // movups zeros at +0x18, +0x28
    std::memset(a0 + 0x18, 0, 0x20);
    // mov qword ptr [rcx+0x38],0
    *reinterpret_cast<uint64_t*>(a0 + 0x38) = 0;
    // alloc via data slot
    using Fn = void*(*)(void*, uint32_t);
    void* allocCtx = *reinterpret_cast<void**>(0x1233E1A8ULL);
    void* fnptr = *reinterpret_cast<void**>(*reinterpret_cast<void**>(allocCtx) + 8); // [rax+8]
    // call qword ptr [0xF99FFA0] with edx=0x10
    void* rsi = reinterpret_cast<Fn>(fnptr)(allocCtx, 0x10);
    if (!rsi) {
        // 0xe836ee1..0xe836eec
        // call 0x9BC830
        using AllocFn = void*(*)(uint32_t);
        rsi = reinterpret_cast<AllocFn>(0x9BC830)(0x10);
    }

    // 0xe836e3d..0xe836ed0
    void* rdi = a0;
    void** node = reinterpret_cast<void**>(rsi);
    node[1] = nullptr;
    *reinterpret_cast<void**>(rdi + 0x18) = rsi;
    *reinterpret_cast<void**>(rsi) = rdi + 0x18;
    std::memset(rdi + 0x40, 0, 0x10);
    void* v = *reinterpret_cast<void**>(rdi + 0x10);
    *reinterpret_cast<void**>(rdi + 0x50) = v;
    *reinterpret_cast<uint64_t*>(rdi + 0x58) = 0;
    *reinterpret_cast<void**>(rdi + 0x60) = v;
    *reinterpret_cast<uint64_t*>(rdi + 0x68) = 0;
    *reinterpret_cast<void**>(rdi + 0x70) = v;
    *reinterpret_cast<uint64_t*>(rdi + 0x78) = 0;
    *reinterpret_cast<uint16_t*>(rdi + 0x80) = 0;
    *reinterpret_cast<uint64_t*>(rdi + 0x88) = 0;
    *reinterpret_cast<unsigned char*>(rdi + 0x98) = 0;

    // release old shared ptr in a1
    void* old = *reinterpret_cast<void**>(a1 + 8);
    if (old) {
        // lock dec dword ptr [rsi+8]
        if (--*reinterpret_cast<volatile int*>(static_cast<unsigned char*>(old) + 8) == 0) {
            // call destructor via data slot
            void* vtbl = *reinterpret_cast<void**>(old);
            using DtorFn = void(*)(void*);
            reinterpret_cast<DtorFn>(*reinterpret_cast<void**>(vtbl))(old);
        }
        // lock dec dword ptr [rsi+0xC]
        if (--*reinterpret_cast<volatile int*>(static_cast<unsigned char*>(old) + 0xC) == 0) {
            void* vtbl = *reinterpret_cast<void**>(old);
            using DtorFn2 = void(*)(void*);
            reinterpret_cast<DtorFn2>(*reinterpret_cast<void**>(vtbl + 8))(old);
        }
    }

    // 0xe836ed6..0xe836ee0
    return rdi;
}

} } // namespace

// Registry entry
// LIFT_FN(sub_e836dc0, 0xe836dc0, native::d3d12::sub_e836dc0)

#if 0
// verbatim instruction quotes
0xe836e2a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe836eba  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe836ed0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe836ee6  call 0x9BC830                                 ; -> sub_9bc830
#endif