// LIFT 0x2b96970 size 0x100 1.26.62.01 sub_2b96970
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_2b96970.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

// Layout assertions (mirrored from sub_2b96970.h; liftcheck scans the .cpp source).
static_assert(offsetof(sub_2b96970_rcx, data) == 0x0, "sub_0x2b96970 rcx+0x0 field");
static_assert(offsetof(sub_2b96970_rcx, next) == 0x8, "sub_0x2b96970 rcx+0x8 field");
static_assert(offsetof(sub_2b96970_rcx, handle) == 0x10, "sub_0x2b96970 rcx+0x10 field");
static_assert(offsetof(sub_2b96970_rcx, valid) == 0x18, "sub_0x2b96970 rcx+0x18 field");
static_assert(offsetof(sub_2b96970_rdx, array_obj) == 0x0, "sub_0x2b96970 rdx+0x0 field");
static_assert(offsetof(sub_2b96970_rdx, refcounted) == 0x8, "sub_0x2b96970 rdx+0x8 field");
static_assert(offsetof(sub_2b96970_rdx, handle) == 0x10, "sub_0x2b96970 rdx+0x10 field");
static_assert(offsetof(sub_2b96970_rax, base) == 0x110, "sub_0x2b96970 rax+0x110 field");
static_assert(offsetof(sub_2b96970_rax, end) == 0x118, "sub_0x2b96970 rax+0x118 field");
static_assert(offsetof(sub_2b96970_rax, limit) == 0x150, "sub_0x2b96970 rax+0x150 field");
static_assert(offsetof(sub_2b96970_rdi, vfptr) == 0x0, "sub_0x2b96970 rdi+0x0 field");
static_assert(offsetof(sub_2b96970_rdi, refcount) == 0x8, "sub_0x2b96970 rdi+0x8 field");
static_assert(offsetof(sub_2b96970_rdi, count0xC) == 0xc, "sub_0x2b96970 rdi+0xc field");

LIFT_FN(sub_2b96970, "sub_2b96970", 0x2b96970, sub_2b96970, nullptr);

// Boundary callee: sub_eea6040, vendor class, reached through data slot 0xF99FFA0.
// The thunk is `jmp rax`; RAX must hold the target function pointer on entry.
// Called with (rcx = object, rdx = vfptr entry); return value ignored.
// 0x2b96a4a  call qword ptr [0xF99FFA0]  ; sub_eea6040(refObj, vfptr[0])  -- destructor
// 0x2b96a60  call qword ptr [0xF99FFA0]  ; sub_eea6040(refObj, vfptr[1])  -- deallocator
native::Boundary<std::uintptr_t, void*, void*> sub_eea6040("sub_eea6040");

// Verbatim call instructions from the disassembly of [0x2b96970, 0x2b96a70) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x2b96a4a  call qword ptr [0xF99FFA0]
0x2b96a60  call qword ptr [0xF99FFA0]
#endif

void* sub_2b96970(void* a0, void* a1) {
    // 0x2b96970..0x2b9698a: basic block 0
    // 0x2b96970  push rsi
    // 0x2b96971  push rdi
    // 0x2b96972  sub rsp,0x28
    // 0x2b96976  mov rsi,rcx
    // 0x2b96979  mov byte ptr [rcx+0x18],0
    // 0x2b9697d  mov rcx,[rdx+8]
    // 0x2b96981  test rcx,rcx
    // 0x2b96984  je 0x2B96A66
    auto* const out = reinterpret_cast<sub_2b96970_rcx*>(a0);
    auto* const in = reinterpret_cast<sub_2b96970_rdx*>(a1);
    out->valid = 0;                                            // 0x2b96979  mov byte ptr [rcx+0x18],0
    void* const refObj = in->refcounted;                       // 0x2b9697d  mov rcx,[rdx+8]
    if (refObj == nullptr) return a0;                          // 0x2b96981  test rcx,rcx / 0x2b96984  je 0x2B96A66

    // 0x2b9698a..0x2b9699d: basic block 1
    // 0x2b9698a  mov eax,0x3FFFF
    // 0x2b9698f  and eax,[rdx+0x10]
    // 0x2b96992  cmp eax,0x3FFFF
    // 0x2b96997  je 0x2B96A66
    std::uint32_t const handleMasked = in->handle & 0x3FFFF;   // 0x2b9698a-0x2b9698f
    if (handleMasked == 0x3FFFF) return a0;                    // 0x2b96992  cmp eax,0x3FFFF / 0x2b96997  je

    // 0x2b9699d..0x2b969b4: basic blocks 2-4 (refcount acquire CAS loop)
    // 0x2b9699d  mov eax,[rcx+8]
    // 0x2b969a0  test eax,eax
    // 0x2b969a2  je 0x2B96A66
    // 0x2b969a8  lea r8d,[rax+1]
    // 0x2b969ac  lock cmpxchg [rcx+8],r8d
    // 0x2b969b2  jne short 0x2B969A0
    auto* const refObjTyped = reinterpret_cast<sub_2b96970_rdi*>(refObj);
    std::uint32_t refcount = refObjTyped->refcount;            // 0x2b9699d  mov eax,[rcx+8]
    while (true) {
        if (refcount == 0) return a0;                          // 0x2b969a0  test eax,eax / 0x2b969a2  je
        std::uint32_t const expected = refcount;               // 0x2b969a8  lea r8d,[rax+1]
        long const prev = _InterlockedCompareExchange(         // 0x2b969ac  lock cmpxchg [rcx+8],r8d
            reinterpret_cast<volatile long*>(&refObjTyped->refcount),
            static_cast<long>(expected + 1),
            static_cast<long>(expected));
        if (prev == static_cast<long>(expected)) break;        // 0x2b969b2  jne short 0x2B969A0 (not taken = success)
        refcount = static_cast<std::uint32_t>(prev);           // eax updated by cmpxchg, retry
    }

    // 0x2b969b4..0x2b969c0: basic block 5
    // 0x2b969b4  mov rax,[rdx]
    // 0x2b969b7  mov rdi,[rdx+8]
    // 0x2b969bb  test rax,rax
    // 0x2b969be  je short 0x2B96A36
    void* const arrayObj = in->array_obj;                      // 0x2b969b4  mov rax,[rdx]
    // rdi = refObj already (0x2b969b7  mov rdi,[rdx+8])

    // 0x2b969c0..0x2b96a32: basic blocks 6-10 (lookup; fill output on success)
    if (arrayObj != nullptr) {
        auto* const arrayObjTyped = reinterpret_cast<sub_2b96970_rax*>(arrayObj);
        std::uint32_t const ecx = in->handle;                  // 0x2b969c0  mov ecx,[rdx+0x10]
        std::uint32_t const idx = ecx & 0x3FFFF;               // 0x2b969c3  mov edx,ecx / 0x2b969c5  and edx,0x3FFFF
        std::uint32_t const outerIdx = idx >> 0xB;             // 0x2b969cb  mov r8d,edx / 0x2b969ce  shr r8d,0xB
        void* const arrayBase = arrayObjTyped->base;           // 0x2b969d2  mov r9,[rax+0x110]
        void* const arrayEnd = arrayObjTyped->end;             // 0x2b969d9  mov r10,[rax+0x118]
        std::uint64_t const count =                            // 0x2b969e0  sub r10,r9 / 0x2b969e3  sar r10,3
            static_cast<std::uint64_t>(
                reinterpret_cast<std::uint8_t*>(arrayEnd) -
                reinterpret_cast<std::uint8_t*>(arrayBase)) >> 3;
        if (static_cast<std::uint64_t>(outerIdx) < count) {    // 0x2b969e7  cmp r8,r10 / 0x2b969ea  jae (not taken)
            void* const entry = reinterpret_cast<void**>(arrayBase)[outerIdx];  // 0x2b969ec  mov r8,[r9+r8*8]
            if (entry != nullptr) {                            // 0x2b969f0  test r8,r8 / 0x2b969f3  je (not taken)
                std::uint32_t const innerIdx = idx & 0x7FF;    // 0x2b969f5  and edx,0x7FF
                std::uint32_t const genBits = ecx & 0xFFFC0000;  // 0x2b969fb  mov r9d,ecx / 0x2b969fe  and r9d,0xFFFC0000
                std::uint32_t const val =                      // 0x2b96a05  mov edx,[r8+rdx*4]
                    reinterpret_cast<std::uint32_t*>(entry)[innerIdx];
                std::uint32_t const tag = genBits ^ val;       // 0x2b96a09  xor r9d,edx
                if (tag <= 0x3FFFE) {                          // 0x2b96a0c  cmp r9d,0x3FFFE / 0x2b96a13  ja (not taken)
                    std::uint32_t const maskedVal = val & 0x3FFFF;  // 0x2b96a15  and edx,0x3FFFF
                    if (arrayObjTyped->limit > maskedVal) {    // 0x2b96a1b  cmp [rax+0x150],rdx / 0x2b96a22  jbe (not taken)
                        // 0x2b96a24..0x2b96a32: basic block 10 (success)
                        // 0x2b96a24  mov [rsi],rax
                        // 0x2b96a27  add rax,0x30
                        // 0x2b96a2b  mov [rsi+8],rax
                        // 0x2b96a2f  mov [rsi+0x10],ecx
                        // 0x2b96a32  mov byte ptr [rsi+0x18],1
                        out->data = arrayObj;                  // 0x2b96a24  mov [rsi],rax
                        out->next = reinterpret_cast<void*>(   // 0x2b96a27-0x2b96a2b
                            reinterpret_cast<std::uint8_t*>(arrayObj) + 0x30);
                        out->handle = ecx;                     // 0x2b96a2f  mov [rsi+0x10],ecx
                        out->valid = 1;                        // 0x2b96a32  mov byte ptr [rsi+0x18],1
                    }
                }
            }
        }
    }

    // 0x2b96a36..0x2b96a60: basic blocks 11-14 (release refObj)
    // 0x2b96a36  test rdi,rdi / 0x2b96a39  je short 0x2B96A66 — refObj is non-null here
    if (_InterlockedDecrement(                                 // 0x2b96a3b  lock dec dword ptr [rdi+8]
            reinterpret_cast<volatile long*>(&refObjTyped->refcount)) == 0) {  // 0x2b96a3f  jne short 0x2B96A66 (not taken)
        // 0x2b96a41  mov rax,[rdi] / 0x2b96a44  mov rax,[rax]
        void** const vfptr = *reinterpret_cast<void***>(refObj);
        sub_eea6040(refObj, vfptr[0]);                         // 0x2b96a47  mov rcx,rdi / 0x2b96a4a  call [0xF99FFA0]
        if (_InterlockedDecrement(                             // 0x2b96a50  lock dec dword ptr [rdi+0xC]
                reinterpret_cast<volatile long*>(&refObjTyped->count0xC)) == 0) {  // 0x2b96a54  jne short 0x2B96A66 (not taken)
            // 0x2b96a56  mov rax,[rdi] / 0x2b96a59  mov rax,[rax+8]
            sub_eea6040(refObj, vfptr[1]);                     // 0x2b96a5d  mov rcx,rdi / 0x2b96a60  call [0xF99FFA0]
        }
    }

    // 0x2b96a66..0x2b96a6f: basic block 15 (epilogue)
    // 0x2b96a66  mov rax,rsi / 0x2b96a69  add rsp,0x28 / pop rdi / pop rsi / ret
    return a0;                                                 // 0x2b96a66  mov rax,rsi / ret
}

} // namespace native::helpers
