// LIFT 0xbc7dc90 size 0x13e 1.26.62.01 sub_bc7dc90
#include "client/features/render/native/bgfx/sub_bc7dc90.h"
#include "client/features/render/native/Lift.h"

#include <cstddef>
#include <cstdint>
#include <intrin.h>

// Layout assertions (definitions live in sub_bc7dc90.h; repeated here so liftcheck
// sees them in the source file).
static_assert(offsetof(native::bgfx::BuilderState, buf1) == 0x00, "BuilderState::buf1 must be at +0x00");
static_assert(offsetof(native::bgfx::BuilderState, size1) == 0x10, "BuilderState::size1 must be at +0x10");
static_assert(offsetof(native::bgfx::BuilderState, cap1) == 0x18, "BuilderState::cap1 must be at +0x18");
static_assert(offsetof(native::bgfx::BuilderState, strongRef) == 0x28, "BuilderState::strongRef must be at +0x28");
static_assert(offsetof(native::bgfx::BuilderState, weakRef) == 0xB8, "BuilderState::weakRef must be at +0xB8");
static_assert(offsetof(native::bgfx::BuilderState, buf2) == 0xC8, "BuilderState::buf2 must be at +0xC8");
static_assert(offsetof(native::bgfx::BuilderState, size2) == 0xD8, "BuilderState::size2 must be at +0xD8");
static_assert(offsetof(native::bgfx::BuilderState, cap2) == 0xE0, "BuilderState::cap2 must be at +0xE0");
static_assert(sizeof(native::bgfx::BuilderState) == 0xE8, "BuilderState must be 0xE8 bytes");

// Verbatim call instructions from the disassembly of [0xbc7dc90, 0xbc7ddce) (rdis dis output).
// 0xbc7dcd9  call 0xE935700                -> sub_e935700 (`lift` in docs/data/native_boundary.tsv;
//                                        forward-declared as native::sub_e935700 and called by native symbol)
// 0xbc7dd1b  call qword ptr [0xF99FFA0]   -> [data_f99ffa0] = sub_eea6040, a `jmp rax` thunk
// 0xbc7dd44  call qword ptr [0xF99FFA0]   (vendor boundary per docs/data/native_boundary.tsv;
//                                        net effect: virtual call through the vtable entry loaded into rax)
// 0xbc7dd5a  call qword ptr [0xF99FFA0]
// 0xbc7dd95  call 0xE935700
// 0xbc7ddc7  call qword ptr [0xF9A8C78]   -> data slot 0xF9A8C78 (VA 0x14F9A8C78 = image base
//                                        0x140000000 + RVA 0xF9A8C78); target not statically known,
//                                        read from the slot at call time with all arguments zero
// No call target lies outside the lift set and the boundary table. UNRESOLVED CALL = none.

namespace {

// The cell at 0xF99FFA0 holds sub_eea6040, a 2-byte `jmp rax` thunk [V]. Each
// `call qword ptr [0xF99FFA0]` therefore tails into the vtable entry the original
// already loaded into rax: net effect vt[slot](obj) with rcx = obj.
inline void vtableCallSlot0(void* obj) {  // vtable[0]  (0xbc7dd44)
    void** vt = *reinterpret_cast<void***>(obj);
    reinterpret_cast<void (*)(void*)>(vt[0])(obj);
}
inline void vtableCallSlot1(void* obj) {  // vtable[8]  (0xbc7dd5a)
    void** vt = *reinterpret_cast<void***>(obj);
    reinterpret_cast<void (*)(void*)>(vt[1])(obj);
}
inline void vtableCallSlot4(void* obj) {  // vtable[0x20] (0xbc7dd1b)
    void** vt = *reinterpret_cast<void***>(obj);
    reinterpret_cast<void (*)(void*)>(vt[4])(obj);
}

// Cold path of both small-string frees: the original zeros the five arguments
// ([rsp+0x20] = 0; ecx = edx = r8d = r9d = 0) and calls the data slot 0xF9A8C78;
// int3 follows the call, so the handler never returns in the original's flow.
inline void invalidParameterColdPath() {
    using Watson = void(__cdecl*)(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, std::uintptr_t);
    reinterpret_cast<Watson>(*reinterpret_cast<std::uintptr_t*>(0x14F9A8C78ULL))(nullptr, nullptr, nullptr, 0, 0);
    // 0xbc7ddcd  int3
    __debugbreak();
}

} // namespace

namespace native::bgfx {

// x64 Microsoft ABI: rcx = a0 (BuilderState*), returns void.
//
// Clears both small strings, releases the +0xB8 single-owner object
// (vtable[4] destroy) and the +0x28 RefCounted (strong-- then vtable[0] destroy;
// weak-- then vtable[8] dealloc). Every branch of the original is lifted,
// including the invalid-parameter cold path. No null guards or SEH beyond the
// explicit tests in the original.
extern "C" void sub_bc7dc90(BuilderState* a0) {
    // 0xbc7dc90..0xbc7dca0
    std::uint64_t cap2 = a0->cap2;              // 0xbc7dc99  mov rax,[rcx+0xE0]
    // 0xbc7dca0  cmp rax,0x10 / 0xbc7dca4  jb short 0xBC7DCDE
    if (cap2 >= 0x10) {
        // 0xbc7dca6..0xbc7dcba
        void* buf2 = a0->buf2;                  // 0xbc7dca6  mov rcx,[rsi+0xC8]
        // 0xbc7dcad  lea rdx,[rax+1] / 0xbc7dcb1  cmp rdx,0x1000 / 0xbc7dcb8  jb short 0xBC7DCD9
        if (cap2 + 1 >= 0x1000) {               // slow path: free through the heap header pointer
            // 0xbc7dcba  mov r8,[rcx-8] / 0xbc7dcbe  add rcx,0xFFFFFFFFFFFFFFF8 / 0xbc7dcc2  sub rcx,r8
            std::uint64_t hdr2 = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint8_t*>(buf2) - 8);
            std::uint64_t delta2 = reinterpret_cast<std::uintptr_t>(buf2) - 8 - hdr2;
            // 0xbc7dcc5  cmp rcx,0x20 / 0xbc7dcc9  jae 0xBC7DDB4
            if (delta2 >= 0x20) {               // cold path: invalid parameter, all arguments zero
                // 0xbc7ddb4..0xbc7ddc7
                invalidParameterColdPath();
                return;                         // not reached in the original (trap)
            }
            // 0xbc7dccf  add rax,0x28 / 0xbc7dcd3  mov rdx,rax / 0xbc7dcd6  mov rcx,r8 /
            // 0xbc7dcd9  call 0xE935700   (rcx = hdr2, rdx = cap2 + 0x28)
            ::native::sub_e935700(hdr2, cap2 + 0x28);
        } else {
            // 0xbc7dcd9  call 0xE935700   (fast path: rcx = buf2, rdx = cap2 + 1)
            ::native::sub_e935700(buf2, cap2 + 1);
        }
    }
    // 0xbc7dcde  mov qword ptr [rsi+0xD8],0
    a0->size2 = 0;
    // 0xbc7dce9  mov qword ptr [rsi+0xE0],0xF
    a0->cap2 = 0xF;
    // 0xbc7dcf4  mov byte ptr [rsi+0xC8],0  (cleared with the SSO reset below)
    a0->buf2 = nullptr;

    // 0xbc7dcfb  mov rcx,[rsi+0xB8] / 0xbc7dd02  test rcx,rcx / 0xbc7dd05  je short 0xBC7DD2C
    if (void* r = a0->weakRef) {
        // 0xbc7dd07  lea rax,[rsi+0x80] / 0xbc7dd0e  cmp rcx,rax / 0xbc7dd11  setne dl
        //              dl = (r != &a0+0x80); result is never read: no observable effect
        // 0xbc7dd14  mov rax,[rcx] / 0xbc7dd17  mov rax,[rax+0x20] /
        // 0xbc7dd1b  call qword ptr [0xF99FFA0]  -> vtable[4](r) through the jmp-rax trampoline
        vtableCallSlot4(r);
        // 0xbc7dd21  mov qword ptr [rsi+0xB8],0
        a0->weakRef = nullptr;
    }

    // 0xbc7dd2c  mov rdi,[rsi+0x28] / 0xbc7dd30  test rdi,rdi / 0xbc7dd33  je short 0xBC7DD60
    if (::native::RefCounted* r = a0->strongRef) {
        // 0xbc7dd35  lock dec dword ptr [rdi+8] / 0xbc7dd39  jne short 0xBC7DD60
        if (r->strong.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
            // 0xbc7dd3b  mov rax,[rdi] / 0xbc7dd3e  mov rax,[rax] (vtable[0]) /
            // 0xbc7dd44  call qword ptr [0xF99FFA0]  -> destroy(r)
            vtableCallSlot0(r);
            // 0xbc7dd4a..0xbc7dd4e
            // 0xbc7dd4e..0xbc7dd50
            if (r->weak.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
                // 0xbc7dd50  mov rax,[rdi] / 0xbc7dd53  mov rax,[rax+8] (vtable[8]) /
                // 0xbc7dd5a  call qword ptr [0xF99FFA0]  -> dealloc(r)
                vtableCallSlot1(r);
            }
        }
    }

    // 0xbc7dd60  mov rax,[rsi+0x18] / 0xbc7dd64  cmp rax,0x10 / 0xbc7dd68  jb short 0xBC7DD9A
    std::uint64_t cap1 = a0->cap1;
    if (cap1 >= 0x10) {
        // 0xbc7dd6a  mov rcx,[rsi] / 0xbc7dd6d  lea rdx,[rax+1] / 0xbc7dd71  cmp rdx,0x1000 /
        // 0xbc7dd78  jb short 0xBC7DD95
        void* buf1 = a0->buf1;
        if (cap1 + 1 >= 0x1000) {               // slow path: free through the heap header pointer
            // 0xbc7dd7a  mov r8,[rcx-8] / 0xbc7dd7e..0xbc7dd82
            std::uint64_t hdr1 = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint8_t*>(buf1) - 8);
            std::uint64_t delta1 = reinterpret_cast<std::uintptr_t>(buf1) - 8 - hdr1;
            // 0xbc7dd85  cmp rcx,0x20 / 0xbc7dd89  jae short 0xBC7DDB4
            if (delta1 >= 0x20) {               // cold path
                invalidParameterColdPath();
                return;
            }
            // 0xbc7dd95  call 0xE935700   (rcx = hdr1, rdx = cap1 + 0x28)
            ::native::sub_e935700(hdr1, cap1 + 0x28);
        } else {
            // 0xbc7dd95  call 0xE935700   (fast path: rcx = buf1, rdx = cap1 + 1)
            ::native::sub_e935700(buf1, cap1 + 1);
        }
    }
    // 0xbc7dd9a  mov qword ptr [rsi+0x10],0
    a0->size1 = 0;
    // 0xbc7dda2  mov qword ptr [rsi+0x18],0xF
    a0->cap1 = 0xF;
    // 0xbc7ddaa  mov byte ptr [rsi],0  (cleared with the SSO reset below)
    a0->buf1 = nullptr;
    // 0xbc7ddad  add rsp,0x28 / 0xbc7ddb1  pop rdi / 0xbc7ddb2  pop rsi / 0xbc7ddb3  ret
    return;
}

static native::Footprint sub_bc7dc90Footprint(BuilderState* a0) {
    // Conservative: every byte written to *a0 (0xE8 bytes). Writes through the virtual
    // calls (refcount control blocks and the destroyed object) and via sub_e935700
    // (the global object at VA 0x15233E1A8) are out-of-function side effects, not
    // declared statically -- same convention as sibling unit sub_bc2bca0.
    return {{a0, sizeof(BuilderState)}};
}

LIFT_FN(sub_bc7dc90, "native::sub_bc7dc90", 0xbc7dc90, sub_bc7dc90, sub_bc7dc90Footprint);

} // namespace native::bgfx
