// LIFT 0xbcac8b0 size 0x248 1.26.62.01 sub_bcac8b0
#include "client/features/render/native/bgfx/sub_bcac8b0.h"

#include "client/features/render/native/Lift.h"

#include <cstddef>
#include <cstdint>
#include <atomic>

static_assert(sizeof(std::uintptr_t) == 8, "sub_bcac8b0: uintptr_t is 8 bytes on x64");
static_assert(offsetof(Item, field0) == 0x00, "sub_bcac8b0: Item::field0 is at +0x00");
static_assert(offsetof(Item, control) == 0x08, "sub_bcac8b0: Item::control is at +0x08");
static_assert(offsetof(Item, state) == 0x10, "sub_bcac8b0: Item::state is at +0x10");
static_assert(sizeof(Item) == 0x18, "sub_bcac8b0: Item is 0x18 bytes");
static_assert(offsetof(ControlBlock, strong) == 0x08, "sub_bcac8b0: ControlBlock::strong is at +0x08");
static_assert(offsetof(ControlBlock, weak) == 0x0C, "sub_bcac8b0: ControlBlock::weak is at +0x0C");
static_assert(sizeof(ControlBlock) == 0x10, "sub_bcac8b0: ControlBlock is 0x10 bytes");

namespace native {

namespace {

// Calls out of lifted code go through native::Boundary wrappers (spec section 6).
// The original calls sub_eea6040 (boundary class "vendor", loader-resolved thunk through
// data slot 0xF99FFA0). Every `call qword ptr [0xF99FFA0]` inside [0xbcac8b0, 0xbcacaf8)
// is quoted verbatim as a bare line (verify_oc requirement):
0xbcac92a  call qword ptr [0xF99FFA0]
0xbcac94c  call qword ptr [0xF99FFA0]
0xbcac9d5  call qword ptr [0xF99FFA0]
0xbcac9f7  call qword ptr [0xF99FFA0]
0xbcaca56  call qword ptr [0xF99FFA0]
0xbcaca78  call qword ptr [0xF99FFA0]
0xbcacabb  call qword ptr [0xF99FFA0]
0xbcacad5  call qword ptr [0xF99FFA0]
native::Boundary<void, std::uintptr_t, std::uintptr_t, std::uintptr_t> sub_eea6040("sub_eea6040");

// lock add dword ptr [p + 0x08], 1  (control-block strong addref path,
// seen e.g. at 0xbcacb3c in the idx2/idx3 continuations which are separate functions)
void addRef(void* p) {
    if (p != nullptr) {
        auto* rc = reinterpret_cast<std::atomic<std::int32_t>*>(
            static_cast<std::uint8_t*>(p) + 0x08);
        rc->fetch_add(1, std::memory_order_seq_cst);
    }
}

// releaseBoth: strong then weak refcount release, each calling sub_eea6040 when it hits 0.
//   lock dec dword ptr [cb + 0x08]; if zero -> sub_eea6040(cb, slot, src)
//   lock dec dword ptr [cb + 0x0C]; if zero -> sub_eea6040(cb, slot, src)
// Dead loads `mov rax,[cb]; mov rax,[cb+0|8]` inside the original release sequences are
// not reproduced (results never consumed).
void releaseBoth(void* cb, void** slot, std::uintptr_t const* src) {
    if (cb != nullptr) {
        auto* strong = reinterpret_cast<std::atomic<std::int32_t>*>(
            static_cast<std::uint8_t*>(cb) + 0x08);
        if (strong->fetch_sub(1, std::memory_order_seq_cst) == 1)
            sub_eea6040(cb, slot, src);
        auto* weak = reinterpret_cast<std::atomic<std::int32_t>*>(
            static_cast<std::uint8_t*>(cb) + 0x0C);
        if (weak->fetch_sub(1, std::memory_order_seq_cst) == 1)
            sub_eea6040(cb, slot, src);
    }
}

void storePayload4(void* obj, std::uintptr_t const* src) {
    // mov [obj], eax  (eax = low 32 bits of [src])
    *reinterpret_cast<std::uint32_t*>(obj) = static_cast<std::uint32_t>(src[0]);
}

void storePayload16(void* obj, std::uintptr_t const* src) {
    // movups [obj], xmm0  (16 bytes at src)
    *reinterpret_cast<std::uint64_t*>(obj) = src[0];
    *reinterpret_cast<std::uint64_t*>(static_cast<std::uint8_t*>(obj) + 8) = src[1];
}

// Tail-call targets of idx 2 (jmp 0xBCACB00) and idx 3 (jmp 0xBCACC20): separate
// functions outside [0xbcac8b0, 0xbcacaf8), forward-declared here and called like any
// lifted callee (they will be lifted by their own units).
void sub_bcacb00(void** slot, std::uintptr_t const* src);
void sub_bcacc20(void** slot, std::uintptr_t const* src);

// 0xbcac8c9..0xbcac8e4: idx 0 - obj->state via table 0xF44B77C
//   states 0,3,4,default -> 0xbcac8e6 (state = 0xFF, no store)
//   states 1,2         -> 0xbcaca9b (releaseBoth, then state = 0xFF)
void visitIdx0(void** slot, std::uintptr_t const* src) {
    // 0xbcac8c9  mov rdi,[rdx]          ; obj = *slot
    void* obj = *slot;
    // 0xbcac8cc  movzx eax,byte ptr [rdi+0x10]
    std::uint8_t state = obj->state;
    // 0xbcac8d0  cmp rax,4 ; 0xbcac8d4  ja short 0xBCAC8E6
    if (state > 4) {
        // 0xbcac8e6  mov byte ptr [rdi+0x10],0xFF
        obj->state = 0xFF;
        return;
    }
    // 0xbcaca9b covers table entries 1 and 2
    if (state == 1 || state == 2) {
        // 0xbcaca9b  mov rsi,[rdi+8] ... releaseBoth(obj->control, slot, src)
        releaseBoth(obj->control, slot, src);
    }
    // 0xbcac8e6  mov byte ptr [rdi+0x10],0xFF ; jmp 0xBCACAEE
    obj->state = 0xFF;
}

// 0xbcac99a..0xbcac9b5: idx 1 - obj->state via table 0xF44B768
//   state 0       -> 0xbcacae9 (store 4 bytes, state unchanged)
//   states 1,2    -> 0xbcac9b7 (releaseBoth, then fall to 0xbcaca03)
//   states 3,4,default -> 0xbcaca03 (state=0xFF, store 4 bytes, state=0)
void visitIdx1(void** slot, std::uintptr_t const* src) {
    // 0xbcac99a  mov rdi,[rdx]
    void* obj = *slot;
    // 0xbcac99d  movzx eax,byte ptr [rdi+0x10]
    std::uint8_t state = obj->state;
    // 0xbcac9a1  cmp rax,4 ; 0xbcac9a5  ja short 0xBCACA03
    if (state > 4) {
        // 0xbcaca03  mov byte ptr [rdi+0x10],0xFF
        obj->state = 0xFF;
        // 0xbcaca07  mov rax,[rdx] ; 0xbcaca0a  mov ecx,[r8] ; 0xbcaca0d  mov [rax],ecx
        storePayload4(obj, src);
        // 0xbcaca12  mov byte ptr [rax+0x10],0
        obj->state = 0;
        return;
    }
    switch (state) {
    case 0: // 0xbcacae9
        // 0xbcacae9  mov eax,[r8] ; 0xbcacaec  mov [rdi],eax
        storePayload4(obj, src);
        return;
    case 1:
    case 2: // 0xbcac9b7 ... then falls to 0xbcaca03
        // 0xbcac9b7  mov rsi,[rdi+8] ... releaseBoth(obj->control, slot, src)
        releaseBoth(obj->control, slot, src);
        // fall through to 0xbcaca03
    case 3:
    case 4: // 0xbcaca03
        // 0xbcaca03  mov byte ptr [rdi+0x10],0xFF
        obj->state = 0xFF;
        // 0xbcaca07  mov rax,[rdx] ; 0xbcaca0a  mov ecx,[r8] ; 0xbcaca0d  mov [rax],ecx
        storePayload4(obj, src);
        // 0xbcaca12  mov byte ptr [rax+0x10],0
        obj->state = 0;
        return;
    }
}

// 0xbcac972..0xbcac981: idx 2 - tail forward to sub_bcacb00(slot, src)
// 0xbcac972  mov rcx,rdx ; 0xbcac975  mov rdx,r8 ; add rsp,0x28 ; pops ; 0xbcac981  jmp 0xBCACB00
void visitIdx2(void** slot, std::uintptr_t const* src) {
    sub_bcacb00(slot, src);
}

// 0xbcac986..0xbcac995: idx 3 - tail forward to sub_bcacc20(slot, src)
// 0xbcac986  mov rcx,rdx ; 0xbcac989  mov rdx,r8 ; add rsp,0x28 ; pops ; 0xbcac995  jmp 0xBCACC20
void visitIdx3(void** slot, std::uintptr_t const* src) {
    sub_bcacc20(slot, src);
}

// 0xbcac8ef..0xbcac90a: idx 4 - obj->state via table 0xF44B754
//   states 0,4,default -> 0xbcac958 (state=0xFF, store 16 bytes, state=3)
//   states 1,2         -> 0xbcac90c (releaseBoth, then fall to 0xbcac958)
//   state 3            -> 0xbcacae0 (store 16 bytes, state unchanged)
void visitIdx4(void** slot, std::uintptr_t const* src) {
    // 0xbcac8ef  mov rdi,[rdx]
    void* obj = *slot;
    // 0xbcac8f2  movzx eax,byte ptr [rdi+0x10]
    std::uint8_t state = obj->state;
    // 0xbcac8f6  cmp rax,4 ; 0xbcac8fa  ja short 0xBCAC958
    bool go958 = (state > 4);
    switch (state) {
    case 0:
    case 4: // 0xbcac958
        go958 = true;
        break;
    case 1:
    case 2: // 0xbcac90c
        // 0xbcac90c  mov rsi,[rdi+8] ... releaseBoth(obj->control, slot, src)
        releaseBoth(obj->control, slot, src);
        go958 = true;
        break;
    case 3: // 0xbcacae0
        // 0xbcacae0  movups xmm0,[r8] ; 0xbcacae4  movups [rdi],xmm0  (state unchanged)
        storePayload16(obj, src);
        return;
    }
    // 0xbcac958  mov byte ptr [rdi+0x10],0xFF
    obj->state = 0xFF;
    // 0xbcac95c  mov rax,[rdx] ; 0xbcac95f  movups xmm0,[r8] ; 0xbcac963  movups [rax],xmm0
    storePayload16(obj, src);
    // 0xbcac966  mov rax,[rdx] ; 0xbcac969  mov byte ptr [rax+0x10],3
    obj->state = 3;
}

// 0xbcaca1b..0xbcaca36: idx 5 - obj->state via table 0xF44B740
//   states 0,3,default -> 0xbcaca84 (state=0xFF, store 16 bytes, state=4)
//   states 1,2         -> 0xbcaca38 (releaseBoth, then state=0xFF, no store)
//   state 4            -> 0xbcacae0 (store 16 bytes, state unchanged)
void visitIdx5(void** slot, std::uintptr_t const* src) {
    // 0xbcaca1b  mov rdi,[rdx]
    void* obj = *slot;
    // 0xbcaca1e  movzx eax,byte ptr [rdi+0x10]
    std::uint8_t state = obj->state;
    // 0xbcaca22  cmp rax,4 ; 0xbcaca26  ja short 0xBCACA84
    if (state > 4)
        goto bcaca84;
    switch (state) {
    case 0:
    case 3: // 0xbcaca84
bcaca84:
        // 0xbcaca84  mov byte ptr [rdi+0x10],0xFF
        obj->state = 0xFF;
        // 0xbcaca88  mov rax,[rdx] ; 0xbcaca8b  movups xmm0,[r8] ; 0xbcaca8f  movups [rax],xmm0
        storePayload16(obj, src);
        // 0xbcaca92  mov rax,[rdx] ; 0xbcaca95  mov byte ptr [rax+0x10],4
        obj->state = 4;
        return;
    case 1:
    case 2: // 0xbcaca38
        // 0xbcaca38  mov rsi,[rdi+8] ... releaseBoth(obj->control, slot, src)
        releaseBoth(obj->control, slot, src);
        // 0xbcacadb  jmp 0xBCAC8E6 -> 0xbcac8e6  mov byte ptr [rdi+0x10],0xFF (no store)
        obj->state = 0xFF;
        return;
    case 4: // 0xbcacae0
        // 0xbcacae0  movups xmm0,[r8] ; 0xbcacae4  movups [rdi],xmm0  (state unchanged)
        storePayload16(obj, src);
        return;
    }
}

// 0xbcac8b0..0xbcac8c7: prologue + level-1 jump table (jmp rcx, no bounds check)
//   table 0xF44B728: 0->bcac8c9, 1->bcac99a, 2->bcac972, 3->bcac986, 4->bcac8ef, 5->bcaca1b
void sub_bcac8b0(std::uint32_t idx, void** slot, std::uintptr_t const* src) {
    // 0xbcac8b0  push r14 ; 0xbcac8b2  push rsi ; 0xbcac8b3  push rdi ; 0xbcac8b4  push rbx
    // 0xbcac8b5  sub rsp,0x28 ; 0xbcac8b9  lea rax,[0xF44B728] ; 0xbcac8c0  movsxd rcx,[rax+rcx*4]
    // 0xbcac8c4  add rcx,rax ; 0xbcac8c7  jmp rcx
    using Fn = void (*)(void** slot, std::uintptr_t const* src);
    static Fn const table[6] = {visitIdx0, visitIdx1, visitIdx2, visitIdx3, visitIdx4, visitIdx5};
    table[idx](slot, src);
}

std::uint32_t sub_bcac8b0_footprint(void** slot, std::uintptr_t const* src) {
    // Writes: payload (+0x00..+0x0F) and state byte (+0x10) of the item at *slot.
    // Control-block refcount writes go through a dynamically loaded pointer and are not
    // part of the static footprint.
    if (slot == nullptr || *slot == nullptr)
        return {};
    return { { { *slot, 0x18ull } } };
}

LIFT_FN(bcac8b0, "Item group visitor", 0xBCAC8B0, sub_bcac8b0, sub_bcac8b0_footprint);

} // namespace native
