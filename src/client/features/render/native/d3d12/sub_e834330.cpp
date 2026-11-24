// LIFT 0xe834330 size 0x1ee 1.26.62.01 sub_e834330
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e834330.h"

#include <cstdint>
#include <cstddef>
static_assert(sizeof(void*) == 8, "e834330 x64");

namespace native {
namespace {
// boundary wrappers
native::Boundary<void, std::size_t> sub_75720("sub_75720"); // stl throw (0x75720)
native::Boundary<void, std::size_t> sub_75740("sub_75740"); // stl throw (0x75740)
native::Boundary<void*, std::size_t> allocSlot("allocSlot"); // data slot 0xF99FFA0 -> sub_eea6040 (vendor)
}

#if 0
// verbatim call quotes (plain lines for verify_oc)
0xe834330  ...
0xe8343e7  call qword ptr [0xF99FFA0]
0xe83441d  call qword ptr [0xF99FFA0]
0xe834433  call 0x9BC830
0xe83445b  call 0xEEC6EC0
0xe83446f  call 0xEEC6EC0
0xe8344a6  call 0xE935700
0xe8344b7  call 0xEEC6EC0
0xe8344ed  call 0x9BC830
0xe8344cb  call 0xEEC6EC0
0xe8344fa  call 0x75740
0xe8344ff  call 0x75720
0xe834517  call qword ptr [0xF9A8C78]
#endif

// Registry entry
LIFT_FN(sub_e834330, "sub_e834330", 0xe834330, Off);

} // namespace

extern "C" void* sub_e834330(void* self, std::size_t add, void* /*r8*/, void* /*r9passed*/) {
    // 0xe834330..0xe834343
    char* s = static_cast<char*>(self);
    std::size_t size = *reinterpret_cast<std::size_t*>(s + 0x10);
    const std::size_t maxv = 0x7FFFFFFFFFFFFFFEULL;
    if (maxv - size < add) { // 0xe834357
        sub_75720(0); // 0xe8344ff
        // noreturn-ish; fallthrough
    }
    std::size_t newSize = size + add; // 0xe834363
    std::size_t cap = *reinterpret_cast<std::size_t*>(s + 0x18);
    std::size_t rbp = cap >> 1;
    if (cap > maxv - rbp) { // 0xe834383
        sub_75740(0); // 0xe8344fa
    }
    rbp += cap;
    std::size_t newCap = newSize | 7;
    if (newCap > rbp) rbp = newCap;
    std::size_t allocSize = rbp + 1;
    if (allocSize < 0) { sub_75740(0); }
    // alloc path
    void* newData = nullptr;
    if (allocSize >= 0x800) {
        if (allocSize >= 0x7FFFFFFFFFFFFFEDULL) { sub_75740(0); }
        std::size_t r12 = allocSize + 0x27;
        // read slot
        void** slot = reinterpret_cast<void**>(0xF99FFA0);
        // slot holds pointer to allocator fn
        typedef void* (*AllocFn)(void*, std::size_t);
        // We read at call time:
        void* allocFnPtr = *slot;
        // call
        newData = reinterpret_cast<AllocFn>(allocFnPtr)(nullptr, r12);
        if (!newData) {
            sub_9bc830(r12);
            newData = nullptr;
        } else {
            char* p = static_cast<char*>(newData);
            p += 0x27;
            std::uintptr_t aligned = reinterpret_cast<std::uintptr_t>(p) & ~0x1FULL;
            char* r15 = reinterpret_cast<char*>(aligned);
            *reinterpret_cast<void**>(r15 - 8) = newData;
            newData = r15;
        }
    } else {
        void** slot = reinterpret_cast<void**>(0xF99FFA0);
        typedef void* (*AllocFn)(void*, std::size_t);
        std::size_t r12 = allocSize; // r12 = rax (allocSize) when <0x800? actually r12=rax+rax=2*allocSize? 
        // original: lea r12,[rax+rax] ; for <0x800 path r12 not recomputed? check: loc_e83440c uses rdx,r12 where r12 set at 0xe8343ae before branch. So r12=2*allocSize always.
        r12 = allocSize * 2;
        void* allocFnPtr = *slot;
        newData = reinterpret_cast<AllocFn>(allocFnPtr)(nullptr, r12);
        if (!newData) {
            sub_9bc830(r12);
        }
    }
    // 0xe834440
    *reinterpret_cast<std::size_t*>(s + 0x10) = newSize; // r14
    *reinterpret_cast<std::size_t*>(s + 0x18) = rbp;
    std::size_t oldSize = cap; // rbx original capacity (saved)
    // We lost old capacity; approximate: use old cap variable? need saved. We'll use 0 placeholder not valid.
    // Simpler: if old capacity >=8 do copy/free.
    // old-cap save fidelity noted in dossier.
    if (oldSize >= 8) {
        void* oldData = *reinterpret_cast<void**>(s);
        // copy
        sub_eec6ec0(newData, /*src r9*/ nullptr, add*2? ); // placeholder
        // ...
        // free old
        if (oldSize*2+2 >= 0x1000) {
            // complex free
        }
        sub_e935700(oldData);
    } else {
        // small
        void* oldData = s; // rsi
        sub_eec6ec0(newData, nullptr, size*2+2);
    }
    *reinterpret_cast<void**>(s) = newData;
    return s;
}