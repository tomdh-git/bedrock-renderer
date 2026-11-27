// LIFT 0x341070 size 0x12d 1.26.62.01 sub_341070
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_341070.h"

#include <cstdint>
#include <cstddef>

namespace native::helpers {

LIFT_FN(sub_341070, "sub_341070", 0x341070, sub_341070, nullptr);

// Verbatim call instructions from the disassembly of [0x341070, 0x34119d).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
// All three are indirect calls through data slots (IAT entries); the callee
// signatures are not derivable from the static listing, so each is declared as
// a boundary function pointer whose argument registers match the live state at
// the call site (return value unused by the caller).
#if 0
0x3410a9  call qword ptr [0xF9A70E8]
0x3410d5  call qword ptr [0xF9A70B8]
0x34116a  call qword ptr [0xF9A7440]
#endif

// Game-image data addressed by absolute-immediate operands inside the function.
// The values are stored as pointer fields into the object at the same RVAs the
// original reads them from.
static constexpr std::uintptr_t kData_EFFC3C0 = 0xEFFC3C0ULL; // 0x341097  lea rax,[0xEFFC3C0]
static constexpr std::uintptr_t kData_EFCA660 = 0xEFCA660ULL; // 0x3410af  lea rax,[0xEFCA660]
static constexpr std::uintptr_t kData_EFFC3D0 = 0xEFFC3D0ULL; // 0x3410fc  lea rsi,[0xEFFC3D0]
static constexpr std::uintptr_t kData_EFFC448 = 0xEFFC448ULL; // 0x3410e0  lea rdi,[0xEFFC448]
static constexpr std::uintptr_t kData_EFCA670 = 0xEFCA670ULL; // 0x341131  lea rcx,[0xEFCA670]

// Data-slot (IAT) addresses called indirectly through [addr].
static constexpr std::uintptr_t kSlot_0xF9A70E8 = 0xF9A70E8ULL; // 0x3410a9
static constexpr std::uintptr_t kSlot_0xF9A70B8 = 0xF9A70B8ULL; // 0x3410d5
static constexpr std::uintptr_t kSlot_0xF9A7440 = 0xF9A7440ULL; // 0x34116a

// off_of() reproduces the repeated  mov rax,[rdx+0x78]; movsxd rax,[rax+4]
// sequence: f78 = *(void**)(s + 0x78), off = sign-extend(*(int32*)(f78 + 4)).
static std::intptr_t off_of(const std::uint8_t* s) {
    void* f78 = *reinterpret_cast<void**>(const_cast<std::uint8_t*>(s) + 0x78);
    return static_cast<std::intptr_t>(
        *reinterpret_cast<const std::int32_t*>(
            reinterpret_cast<const std::uint8_t*>(f78) + 4));
}

// Indexed address = s + 0x78 + off, used for the +0x78/+0x74 stores.
static void* indexed_addr(std::uint8_t* s, std::intptr_t off) {
    return reinterpret_cast<void*>(
        s + 0x78 + static_cast<std::size_t>(off) + 0x78);
}

// Layout assertion mirroring the header structs (r dx view of the object).
static_assert(offsetof(sub_341070_rdx, f78) == 0x78, "sub_341070 layout: rdx f78 at +0x78");
static_assert(offsetof(sub_341070_rdx, f80) == 0x80, "sub_341070 layout: rdx f80 at +0x80");

uintptr_t sub_341070(void* self, void* a2, void* a3, std::uint32_t a4) {
    // x64 Microsoft ABI: RCX = self (a1), RDX = a2, R8 = a3, R9D = a4.
    // Return value: RAX = self at ret (the context pointer is returned).
    std::uint8_t* const s = reinterpret_cast<std::uint8_t*>(self);

    // 0x34108e  mov [rbp-0xC],r9d    (a4 saved to a stack slot; the slot is never
    // read back, so it has no observable effect and is not reproduced.)
    // 0x341092  test r9d,r9d
    // 0x341095  je short 0x3410CE    ; if a4 == 0 goto block 2
    if (a4 != 0) {
        // 0x341097..0x3410ce: basic block 1
        //   lea rax,[0xEFFC3C0]
        //   mov [rbx+0x78],rax
        *reinterpret_cast<void**>(s + 0x78) = reinterpret_cast<void*>(kData_EFFC3C0);
        //   lea rcx,[rbx+0x90]
        //   call qword ptr [0xF9A70E8]   RCX=&s[0x90], RDX=a2, R8=a3, R9D=a4
        {
            using fn_t = void (*)(void*, void*, void*, std::uint32_t);
            auto fn = reinterpret_cast<fn_t>(
                *reinterpret_cast<void**>(kSlot_0xF9A70E8));
            fn(reinterpret_cast<void*>(s + 0x90), a2, a3, a4);
        }
        //   lea rax,[0xEFCA660]
        //   mov [rbx+0x90],rax
        *reinterpret_cast<void**>(s + 0x90) = reinterpret_cast<void*>(kData_EFCA660);
        //   xorps xmm0,xmm0
        //   movups [rbx+0xD8],xmm0       (16-byte zero store)
        *reinterpret_cast<std::uint64_t*>(s + 0xD8) = 0;
        *reinterpret_cast<std::uint64_t*>(s + 0xE0) = 0;
        //   mov byte ptr [rbx+0xE8],0
        s[0xE8] = 0;
    }

    // 0x3410ce..0x34119d: basic block 2
    //   mov rcx,rbx
    //   mov [rbp-8],rbx                (saved self)
    //   call qword ptr [0xF9A70B8]     RCX=self, RDX=a2, R8=a3, R9D=a4
    {
        using fn_t = void (*)(void*, void*, void*, std::uint32_t);
        auto fn = reinterpret_cast<fn_t>(
            *reinterpret_cast<void**>(kSlot_0xF9A70B8));
        fn(self, a2, a3, a4);
    }
    //   mov rdx,[rbp-8]                (rdx = self)
    //   mov [rdx+0x68],rdi
    *reinterpret_cast<void**>(s + 0x68) = a2;
    //   mov [rdx+0x70],rsi
    *reinterpret_cast<void**>(s + 0x70) = a3;
    //   mov rax,[rdx+0x18]
    //   mov [rax],rdi                  (*(void**)(s + 0x18)) = a2
    *reinterpret_cast<void**>(
        *reinterpret_cast<void**>(s + 0x18)) = a2;
    //   mov rax,[rdx+0x38]
    //   mov [rax],rdi                  (*(void**)(s + 0x38)) = a2
    *reinterpret_cast<void**>(
        *reinterpret_cast<void**>(s + 0x38)) = a2;
    //   mov rax,[rdx+0x50]
    //   mov [rax],esi                  (*(std::uint32_t*)(*(void**)(s + 0x50))) = (uint32_t)a3
    *reinterpret_cast<std::uint32_t*>(
        *reinterpret_cast<void**>(s + 0x50)) =
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(a3));
    //   lea rsi,[0xEFFC3D0]
    //   mov [rdx],rsi                  (s + 0x00) = kData_EFFC3D0
    *reinterpret_cast<void**>(s + 0x00) =
        reinterpret_cast<void*>(kData_EFFC3D0);

    // Repeated field: off = sign-extend(*(int32*)(*(void**)(s + 0x78) + 4)).
    const std::intptr_t off = off_of(s);
    //   mov rax,[rdx+0x78]
    //   movsxd rax,[rax+4]
    //   lea rdi,[0xEFFC448]
    //   mov [rdx+rax+0x78],rdi         (s + 0x78 + off + 0x78) = kData_EFFC448
    *reinterpret_cast<void**>(indexed_addr(s, off)) =
        reinterpret_cast<void*>(kData_EFFC448);
    //   mov rax,[rdx+0x78]
    //   movsxd rax,[rax+4]
    //   lea ecx,[rax-0x18]
    //   mov [rdx+rax+0x74],ecx         (s + 0x78 + off + 0x74) = (uint32_t)(off - 0x18)
    *reinterpret_cast<std::uint32_t*>(
        reinterpret_cast<std::uint8_t*>(indexed_addr(s, off)) - 4) =
        static_cast<std::uint32_t>(static_cast<std::int32_t>(off - 0x18));
    //   mov rax,[rdx+0x78]
    //   movsxd rax,[rax+4]
    //   lea rcx,[0xEFCA670]
    //   mov [rdx+rax+0x78],rcx         (s + 0x78 + off + 0x78) = kData_EFCA670
    *reinterpret_cast<void**>(indexed_addr(s, off)) =
        reinterpret_cast<void*>(kData_EFCA670);
    //   mov rax,[rdx+0x78]
    //   movsxd rax,[rax+4]
    //   lea ecx,[rax-0x18]
    //   mov [rdx+rax+0x74],ecx         (s + 0x78 + off + 0x74) = (uint32_t)(off - 0x18)
    *reinterpret_cast<std::uint32_t*>(
        reinterpret_cast<std::uint8_t*>(indexed_addr(s, off)) - 4) =
        static_cast<std::uint32_t>(static_cast<std::int32_t>(off - 0x18));
    //   mov qword ptr [rdx+0x80],0
    *reinterpret_cast<std::uint64_t*>(s + 0x80) = 0;
    //   mov rax,[rdx+0x78]
    //   movsxd rax,[rax+4]
    //   lea rcx,[rdx+rax]
    //   add rcx,0x78                   (rcx = s + 0x78 + off)
    //   xor r8d,r8d
    //   call qword ptr [0xF9A7440]     RCX=indexed, RDX=self, R8=0, R9D=a4
    {
        using fn_t = void (*)(void*, void*, std::uintptr_t, std::uint32_t);
        auto fn = reinterpret_cast<fn_t>(
            *reinterpret_cast<void**>(kSlot_0xF9A7440));
        fn(indexed_addr(s, off), self, 0, a4);
    }
    //   nop
    //   mov rax,[rbp-8]                (rax = self)
    //   mov [rax],rsi                  (s + 0x00) = kData_EFFC3D0  (rewritten, same value)
    *reinterpret_cast<void**>(s + 0x00) =
        reinterpret_cast<void*>(kData_EFFC3D0);
    //   mov rcx,[rax+0x78]
    //   movsxd rcx,[rcx+4]             (rcx = off, recomputed)
    //   mov [rax+rcx+0x78],rdi         (s + 0x78 + off + 0x78) = kData_EFFC448
    *reinterpret_cast<void**>(indexed_addr(s, off)) =
        reinterpret_cast<void*>(kData_EFFC448);
    //   mov rcx,[rax+0x78]
    //   movsxd rdx,[rcx+4]             (rdx = off, recomputed)
    //   lea ecx,[rdx-0x18]
    //   mov [rax+rdx+0x74],ecx         (s + 0x78 + off + 0x74) = (uint32_t)(off - 0x18)
    *reinterpret_cast<std::uint32_t*>(
        reinterpret_cast<std::uint8_t*>(indexed_addr(s, off)) - 4) =
        static_cast<std::uint32_t>(static_cast<std::int32_t>(off - 0x18));
    //   add rsp,0x38 / pop rbx / pop rdi / pop rsi / pop rbp / ret
    //   RAX = self at return
    return reinterpret_cast<uintptr_t>(self);
}

} // namespace native::helpers
