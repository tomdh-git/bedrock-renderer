// LIFT 0xe8141e0 size 0xd8 1.26.62.01 sub_e8141e0
#include "sub_e8141e0.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>

namespace native { namespace d3d12 {

// Layout assertions (the authoritative copies live in sub_e8141e0.h).
static_assert(kSlotStride == 0xB8, "slot stride 0xB8");
static_assert(kSlotArrayOff == 0xAAA178, "slot array offset 0xAAA178");
static_assert(sizeof(SlotEntry) == 0xB8, "SlotEntry 0xB8 bytes");
static_assert(offsetof(SlotEntry, p8) == 0x08, "p8 at +0x08");

// Boundary thunk note (same mechanism as sub_e809f40):
//   call qword ptr [0xF99FFA0]  ->  sub_eea6040, a "jmp rax" thunk.
// sub_eea6040 is classified vendor/boundary in docs/data/native_boundary.tsv.
// The caller first loads the real target into rax:
//   - site 0xe814232 / 0xe81429a : rax = (*(rcx))->[+8]  with rcx = *[0x12ADF800]
//   - site 0xe814267            : rax = [rsi+0x10]      with rcx = [rsi]
// The thunk transfers control to that rax with the current registers, so we call
// the loaded target directly with the same register arguments.

extern "C" void sub_e8141e0(void* a0, unsigned short a1) {
    using boundary_fn = void (*)(void* rcx, void* rdx, void* r8, void* r9, void* s5, int s6);
    const std::uintptr_t base = RewriteRegistry::imageBase();
    char* ctx = static_cast<char*>(a0);

    // 0xe8141e0..0xe814206 : prologue, compute entry address, load its release pointer
    std::size_t idx = static_cast<unsigned short>(a1);                 // 0xe8141e6 movzx eax,dx
    char* entry = ctx + idx * kSlotStride + kSlotArrayOff;             // 0xe8141e0..0xe8141f4 lea/add
    void* release = *reinterpret_cast<void**>(entry + 0x08);           // 0xe8141fb mov rdx,[rcx+rax+0xAAA180]

    if (release != nullptr) {                                          // 0xe814203 test rdx,rdx ; 0xe814206 je 0xE814240
        // 0xe814208..0xe814232 : g = *[0x12ADF800]; call g->vtbl[1](g, release, 0,0,0,0)
        void* g = *reinterpret_cast<void**>(base + 0x12ADF800);        // 0xe814208 mov rcx,[0x12ADF800]
        if (g != nullptr) {                                            // 0xe81420f test rcx,rcx ; 0xe814212 je 0xE814238
            void* target = *reinterpret_cast<void**>(g);               // 0xe814214 mov rax,[rcx]
            target = *reinterpret_cast<void**>(reinterpret_cast<char*>(target) + 0x8); // 0xe814217 mov rax,[rax+8]
            // 0xe81421b..0xe81422f : [rsp+0x28]=0, [rsp+0x20]=0, r8d=0, r9d=0
            reinterpret_cast<boundary_fn>(target)(g, release, nullptr, nullptr, nullptr, 0); // 0xe814232 call qword ptr [0xF99FFA0]
        }
        *reinterpret_cast<void**>(entry + 0x08) = nullptr;             // 0xe814238 mov qword ptr [rdi+8],0
    }

    // 0xe814240..0xe814261 : clear flag byte, load p0, test its layout
    *reinterpret_cast<std::uint8_t*>(entry + 0xB0) = 0;               // 0xe814240 mov byte ptr [rdi+0xB0],0
    void* rsi = *reinterpret_cast<void**>(entry);                     // 0xe814247 mov rsi,[rdi]
    if (rsi != nullptr) {                                            // 0xe81424a test rsi,rsi ; 0xe81424d je 0xE8142B1
        void* rcx = *reinterpret_cast<void**>(rsi);                   // 0xe81424f mov rcx,[rsi]
        void* sentinel = reinterpret_cast<char*>(rsi) + 0x10;         // 0xe814252 lea rax,[rsi+0x10]
        if (rcx != sentinel) {                                       // 0xe814256 cmp rcx,rax ; 0xe814259 je 0xE81426D
            void* p = *reinterpret_cast<void**>(reinterpret_cast<char*>(rsi) + 0x10); // 0xe81425b mov rax,[rax]
            if (p != nullptr) {                                      // 0xe81425e test rax,rax ; 0xe814261 je 0xE81426D
                // 0xe814263..0xe814267 : call [rsi+0x10](rcx=[rsi], rdx=[rsi+0x18], 0,0,0,0)
                void* rdx = *reinterpret_cast<void**>(reinterpret_cast<char*>(rsi) + 0x18); // 0xe814263 mov rdx,[rsi+0x18]
                reinterpret_cast<boundary_fn>(p)(rcx, rdx, nullptr, nullptr, nullptr, 0);   // 0xe814267 call qword ptr [0xF99FFA0]
            }
        }
        // 0xe81426d..0xe81429a : g = *[0x12ADF800]; call g->vtbl[1](g, rsi, 0,0,0,0)
        void* g = *reinterpret_cast<void**>(base + 0x12ADF800);      // 0xe81426d mov rcx,[0x12ADF800]
        if (g != nullptr) {                                         // 0xe814274 test rcx,rcx ; 0xe814277 je 0xE8142A0
            void* target = *reinterpret_cast<void**>(g);            // 0xe814279 mov rax,[rcx]
            target = *reinterpret_cast<void**>(reinterpret_cast<char*>(target) + 0x8); // 0xe81427c mov rax,[rax+8]
            // 0xe814280..0xe814297 : [rsp+0x28]=0, [rsp+0x20]=0, rdx=rsi, r8d=0, r9d=0
            reinterpret_cast<boundary_fn>(target)(g, rsi, nullptr, nullptr, nullptr, 0); // 0xe81429a call qword ptr [0xF99FFA0]
        }
        // 0xe8142a0..0xe8142a7 : clear p0 and the 0xA8 dword
        *reinterpret_cast<void**>(entry) = nullptr;                 // 0xe8142a0 mov qword ptr [rdi],0
        *reinterpret_cast<std::uint32_t*>(entry + 0xA8) = 0;        // 0xe8142a7 mov dword ptr [rdi+0xA8],0
    }

    // 0xe8142b1..0xe8142b7 : epilogue (add rsp,0x38 ; pop rdi ; pop rsi ; ret)
}

} }

#if 0
0xe8141e0  push rsi
0xe8141e1  push rdi
0xe8141e2  sub rsp,0x38
0xe8141e6  movzx eax,dx
0xe8141e9  imul rax,0xB8
0xe8141f0  lea rdi,[rcx+rax]
0xe8141f4  add rdi,0xAAA178
0xe8141fb  mov rdx,[rcx+rax+0xAAA180]
0xe814203  test rdx,rdx
0xe814206  je short 0xE814240
0xe814208  mov rcx,[0x12ADF800]
0xe81420f  test rcx,rcx
0xe814212  je short 0xE814238
0xe814214  mov rax,[rcx]
0xe814217  mov rax,[rax+8]
0xe81421b  mov dword ptr [rsp+0x28],0
0xe814223  mov qword ptr [rsp+0x20],0
0xe81422c  xor r8d,r8d
0xe81422f  xor r9d,r9d
0xe814232  call qword ptr [0xF99FFA0]
0xe814238  mov qword ptr [rdi+8],0
0xe814240  mov byte ptr [rdi+0xB0],0
0xe814247  mov rsi,[rdi]
0xe81424a  test rsi,rsi
0xe81424d  je short 0xE8142B1
0xe81424f  mov rcx,[rsi]
0xe814252  lea rax,[rsi+0x10]
0xe814256  cmp rcx,rax
0xe814259  je short 0xE81426D
0xe81425b  mov rax,[rax]
0xe81425e  test rax,rax
0xe814261  je short 0xE81426D
0xe814263  mov rdx,[rsi+0x18]
0xe814267  call qword ptr [0xF99FFA0]
0xe81426d  mov rcx,[0x12ADF800]
0xe814274  test rcx,rcx
0xe814277  je short 0xE8142A0
0xe814279  mov rax,[rcx]
0xe81427c  mov rax,[rax+8]
0xe814280  mov dword ptr [rsp+0x28],0
0xe814288  mov qword ptr [rsp+0x20],0
0xe814291  mov rdx,rsi
0xe814294  xor r8d,r8d
0xe814297  xor r9d,r9d
0xe81429a  call qword ptr [0xF99FFA0]
0xe8142a0  mov qword ptr [rdi],0
0xe8142a7  mov dword ptr [rdi+0xA8],0
0xe8142b1  add rsp,0x38
0xe8142b5  pop rdi
0xe8142b6  pop rsi
0xe8142b7  ret
#endif

// Registry entry
LIFT_FN(sub_e8141e0, "RendererContextD3D12 base slot 23", 0xe8141e0, sub_e8141e0, nullptr);