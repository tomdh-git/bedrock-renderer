// LIFT 0xbc6e360 size 0x1eb 1.26.62.01 sub_bc6e360
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc6e360.h"

#include <cstddef>
#include <cstdint>

// Layout assertions (definitions and the full set of offset static_asserts live in
// sub_bc6e360.h; repeated here so liftcheck sees them in the source file).
static_assert(offsetof(native::bgfx::sub_bc6e360_state, field_0x14A) == 0x14A);
static_assert(offsetof(native::bgfx::sub_bc6e360_state, field_0x153) == 0x153);
static_assert(offsetof(native::bgfx::sub_bc6e360_state, field_0x680) == 0x680);
static_assert(offsetof(native::bgfx::sub_bc6e360_state, field_0x688) == 0x688);
static_assert(sizeof(native::bgfx::sub_bc6e360_state) == 0x68A);
static_assert(offsetof(native::bgfx::sub_bc6e360_entry, field_0x00) == 0x00);
static_assert(offsetof(native::bgfx::sub_bc6e360_entry, field_0x08) == 0x08);
static_assert(sizeof(native::bgfx::sub_bc6e360_entry) == 0x10);
static_assert(offsetof(native::bgfx::sub_bc6e360_item, field_0x00) == 0x00);
static_assert(offsetof(native::bgfx::sub_bc6e360_item, field_0x0A) == 0x0A);
static_assert(offsetof(native::bgfx::sub_bc6e360_item, field_0x10) == 0x10);
static_assert(sizeof(native::bgfx::sub_bc6e360_item) == 0x14);

namespace {

// Absolute global heap handle: 0xbc6e397 / 0xbc6e425 / 0xbc6e45c  mov rcx,[0x12ADF800].
constexpr uintptr_t kAllocatorPtr = 0x12ADF800ULL;

inline void* allocator_global() {
    return *reinterpret_cast<void**>(kAllocatorPtr);
}

// sub_eea6040 is reached through data slot [0xF99FFA0] (hard rule 69: a data-slot indirect
// call reads the pointer from the slot at call time and invokes it as a function pointer;
// not a blocker). Signature observed from the disassembly:
// void* (void* heap, void* ptr, uint64_t size, uint32_t flags).
inline void* eea6040_call(void* heap, void* ptr, uint64_t size, uint32_t flags) {
    using Fn = void* (*)(void*, void*, uint64_t, uint32_t);
    return reinterpret_cast<Fn>(*reinterpret_cast<uintptr_t*>(0xF99FFA0))(heap, ptr, size, flags);
}

inline void* entry_ptr(void* base, uint32_t idx) {  // entry slot = base + idx*0x10; pointer at +0x00
    return *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(base) + static_cast<uint64_t>(idx) * 16);
}
inline uint32_t entry_count(void* base, uint32_t idx) {  // count at +0x08
    return *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(base) + static_cast<uint64_t>(idx) * 16 + 8);
}
inline void entry_set(void* base, uint32_t idx, void* ptr, uint32_t count) {  // pointer first, then count (0xbc6e4a7 / 0xbc6e4ab)
    *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(base) + static_cast<uint64_t>(idx) * 16) = ptr;
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(base) + static_cast<uint64_t>(idx) * 16 + 8) = count;
}

// sub_eec6ed0 is a crt IAT import thunk (docs/data/native_boundary.tsv line 507),
// called through a native::Boundary wrapper per spec section 6.
// Signature observed: void (void* array, uint64_t, uint64_t, uint64_t).
native::Boundary<void, void*, uint64_t, uint64_t, uint64_t> sub_eec6ed0("sub_eec6ed0");

} // namespace

namespace native::bgfx {

void sub_bc6e360(sub_bc6e360_state* a0, uint32_t a1, uint16_t* a2, uint32_t a3,
                 uint32_t* a4, uint32_t a5, uint32_t a6, uint32_t a7) {
    // Block range covering every instruction of [0xbc6e360, 0xbc6e54b): 0xbc6e360..0xbc6e54a

    // prologue; rax = a0->field_0x680; test/jne skip alloc  (0xbc6e360..0xbc6e397)
    if (a0->field_0x680 == nullptr) {
        // g = *(void**)0x12ADF800; dead loads; r8d=0x418; edx=r9d=0  (0xbc6e397..0xbc6e3c1)
        // 0xbc6e3c1  call qword ptr [0xF99FFA0]
        void* p = eea6040_call(allocator_global(), nullptr, 0x418ull, 0u);   // 0xbc6e3c1  call qword ptr [0xF99FFA0]
        // r14=rax; r8d=0x410; rcx=rax; edx=0  (0xbc6e3c7..0xbc6e3d5)
        // 0xbc6e3d5  call 0xEEC6ED0
        sub_eec6ed0(p, 0ull, 0x410ull, 0ull);                                 // 0xbc6e3d5  call 0xEEC6ED0
        // [rbx+0x680]=r14; dword [r14+0x410]=0; reload rax=[rbx+0x680]  (0xbc6e3da..0xbc6e3ec)
        a0->field_0x680 = p;                                                  // 0xbc6e3da  mov [rbx+0x680],r14
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(p) + 0x410) = 0u;  // 0xbc6e3e1  mov dword ptr [r14+0x410],0
    }
    // base = a0->field_0x680 (reloaded)  (0xbc6e3ec)
    void* base = a0->field_0x680;
    // idx=(u8)a1; entry_slot=base+idx*16; field_0x14A+idx*20=0; field_0x153+idx*20=6  (0xbc6e3f3..0xbc6e40c)
    uint32_t idx = static_cast<uint32_t>(static_cast<uint8_t>(a1));           // 0xbc6e3f3  movzx ecx,bpl
    uint8_t* entry_slot = reinterpret_cast<uint8_t*>(base) + static_cast<uint64_t>(idx) * 16;  // 0xbc6e3f7..0xbc6e3fe  lea/shl/lea -> entry_slot
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(a0) + 0x14A + static_cast<uint64_t>(idx) * 20) = 0u;  // 0xbc6e402  mov word ptr [rbx+rdx*4+0x14A],0
    reinterpret_cast<uint8_t*>(a0)[0x153 + static_cast<uint64_t>(idx) * 20] = 6u;     // 0xbc6e40c  mov byte ptr [rbx+rdx*4+0x153],6
    // end=(u32)(a7+a6); cmp end,entry.count; jb skip grow  (0xbc6e414..0xbc6e41f)
    uint32_t end = static_cast<uint32_t>(a7 + a6);
    if (!(end < entry_count(base, idx))) {                                    // 0xbc6e41a cmp rbp,[rax+rcx+8]; 0xbc6e41f jb short 0xBC6E4AF
        // g=[0x12ADF800]; test; if g: rdx=entry.ptr; zero home args  (0xbc6e41f..0xbc6e456)
        void* g = allocator_global();                                         // 0xbc6e425 mov rcx,[0x12ADF800]
        if (g != nullptr) {                                                   // 0xbc6e42c test rcx,rcx; 0xbc6e42f je short 0xBC6E4A4
            // 0xbc6e456  call qword ptr [0xF99FFA0]
            eea6040_call(g, entry_ptr(base, idx), 0ull, 0u);                  // 0xbc6e456  call qword ptr [0xF99FFA0]
        }
        // g=reload; xorps xmm0; movups [r13],xmm0 zeroes 16B entry slot; test g; if g: r8=end*20; zero args
        // 0xbc6e499  call qword ptr [0xF99FFA0]
        // 0xbc6e463 xorps xmm0,xmm0; 0xbc6e466 movups [r13],xmm0 -> zero entry (ptr+count)
        *reinterpret_cast<uint64_t*>(entry_slot) = 0ull;                      // 0xbc6e466  movups [r13],xmm0
        *reinterpret_cast<uint64_t*>(entry_slot + 8) = 0ull;
        g = allocator_global();                                               // 0xbc6e45c mov rcx,[0x12ADF800] (reload)
        if (g != nullptr) {                                                   // 0xbc6e46b test rcx,rcx; 0xbc6e46e je short 0xBC6E4A7
            void* nb = eea6040_call(g, nullptr, static_cast<uint64_t>(end) * 20ull, 0u);  // 0xbc6e499  call qword ptr [0xF99FFA0]
            entry_set(base, idx, nb, end);                                    // 0xbc6e4a7 mov [r13],r14; 0xbc6e4ab mov [r13+8],rbp
        } else {
            entry_set(base, idx, nullptr, end);                               // 0xbc6e4a4 xor r14d,r14d; 0xbc6e4a7/0xbc6e4ab
        }
    }
    // test r12,r12(a6); je exit; rax=a5[rsp+0xA8]; rcx=a4[rsp+0xA0]; edx=0x20000000; jmp head  (0xbc6e4af..0xbc6e4e6)
    if (a6 != 0) {                                                            // 0xbc6e4af test r12,r12; 0xbc6e4b2 je short 0xBC6E533
        uint32_t k = a7;
        for (;;) {
            // head: k  (0xbc6e4e6  mov r15d,r15d)
            // r8=[r13]=entry.ptr (re-read each iteration)  (0xbc6e4e9)
            void* buf = *reinterpret_cast<void**>(entry_slot);                // 0xbc6e4e9  mov r8,[r13]
            uint32_t ecnt = *reinterpret_cast<uint32_t*>(entry_slot + 8);      // 0xbc6e4f2  cmp [r13+8],r15
            if (buf != nullptr && ecnt > static_cast<uint64_t>(k)) {           // 0xbc6e4ed  test r8,r8; 0xbc6e4f6  jbe short 0xBC6E4D0
                // d=a4[a5*k]; w=*(u16*)(a2+a3*k); off=k*20  (0xbc6e4f8..0xbc6e50f)
                // write *(u16*)(buf+off+0xA)=w [FIRST]  (0xbc6e513)
                uint32_t d = a4[static_cast<uint64_t>(a5) * k];
                uint16_t w = *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(a2) + static_cast<uint64_t>(a3) * k);
                uint64_t off = static_cast<uint64_t>(k) * 20;
                *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(buf) + off + 0xA) = w;  // 0xbc6e513  mov [r8+r11*4+0xA],r10w
                // d&=0x20000000 mask  (0xbc6e519..0xbc6e520)
                if ((d & 0x20000000u) != 0u) d = 0x20000000u;
                // write *(u32*)(buf+off)=d [SECOND]  (0xbc6e524)
                *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(buf) + off) = d;    // 0xbc6e524  mov [r8+r11*4],r9d
                // write *(u32*)(buf+off+0x10)=0x3000000 [THIRD]  (0xbc6e528)
                *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(buf) + off + 0x10) = 0x3000000u;  // 0xbc6e528  mov dword ptr [r8+r11*4+0x10],0x3000000
            }
            // increment counter/index/count; je exit if a6==0  (0xbc6e4d0..0xbc6e4e6)
            ++*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(a0->field_0x680) + 0x410);  // 0xbc6e4d7  inc dword ptr [r8+0x410]
            ++k;                                                              // 0xbc6e4de  inc r15d
            --a6;                                                             // 0xbc6e4e1  dec r12
            if (a6 == 0) break;                                               // 0xbc6e4e4  je short 0xBC6E533
        }
    }
    // [rbx+0x688]=1; epilogue; ret  (0xbc6e533..0xbc6e54a)
    a0->field_0x688 = 1u;                                                     // 0xbc6e533  mov byte ptr [rbx+0x688],1
}

static native::Footprint sub_bc6e360_footprint(sub_bc6e360_state* self) {
    // Conservative: only *self is declared; the entry-array counter, entry buffers and
    // allocator/memset writes through the boundary/data-slot calls are out-of-function
    // side effects, compared by the differential boundary tape instead.
    return { { self, sizeof(*self) } };
}

LIFT_FN(sub_bc6e360, "sub_bc6e360", 0xbc6e360, sub_bc6e360, sub_bc6e360_footprint);

} // namespace native::bgfx
