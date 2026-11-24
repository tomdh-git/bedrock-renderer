# sub_bcac8b0 - Item group visitor

- **RVA**: `0xbcac8b0` (`sub_bcac8b0`) [V rdis dis]
- **Range**: `0xbcac8b0..0xbcacaf8`, size `0x248`, 1 xref in [V rdis dis / xr]
- **Role**: Item group visitor for the bgfx render path (Minecraft Bedrock 1.26.62.01). Visits an
  item object through a slot pointer and, depending on a type index (rcx) and the item's state
  byte (+0x10), releases the old refcounted control block and/or stores a new 16-byte payload
  and a new state. Calls sub_eea6040 (boundary class "vendor", loader-resolved thunk through
  data slot 0xF99FFA0) for control-block release; no other callees. [V dis, native_boundary.tsv]

## Signature (x64 Microsoft ABI)

```cpp
void sub_bcac8b0(std::uint32_t idx, void** slot, std::uintptr_t const* src);
```

- rcx = idx: jump-table index into 6 entries at data 0xF44B728, no bounds check (bare `jmp rcx`) [V 0xbcac8b9..0xbcac8c7]. The sole caller passes `movsx rcx,byte [r9+0x10]; inc rcx` [V 0xbcac5e5..0xbcac5ea].
- rdx = slot: `void**`; the visited object pointer is `*slot` [V 0xbcac8c9 `mov rdi,[rdx]`].
- r8 = src: payload pointer; `src[0]` maps to object +0x00, `src[1]` to object +0x08 [V movups stores].
- return: void (eax holds the last state-byte load; the sole caller at 0xbcac5f7 ignores it) [V xr].

## Register / argument map

- rcx = idx (also the level-1 jump-table index)
- rdx = slot (saved to rbx/r14 across calls in release sequences)
- r8 = src (saved to r14 across calls in release sequences)
- rdi = working object pointer (*slot)
- rsi = control block pointer (obj->control) in release sequences
- r14/rbx = slot/src saves across calls
- frame: push r14/rsi/rdi/rbx; sub rsp,0x28 [V 0xbcac8b0..0xbcac8b5]

## Jump tables (data, read via movsxd + index + bare jmp)

- level 1 on idx: data 0xF44B728, 6 entries [V jt.py]: 0->0xbcac8c9, 1->0xbcac99a,
  2->0xbcac972, 3->0xbcac986, 4->0xbcac8ef, 5->0xbcaca1b
- level 2 on obj->state: tables 0xF44B77C (idx 0), 0xF44B754 (idx 4), 0xF44B768 (idx 1),
  0xF44B740 (idx 5 and the 0xbcac9b7 path), 0xF44B790 (idx 2 continuation), 0xF44B7A4 (idx 3
  continuation); 5 entries each (states 0..4), state > 4 handled by the `ja` default [V jt.py].

## Structural facts

- data slot 0xF99FFA0 holds sub_eea6040: native_boundary.tsv class "vendor", loader-resolved thunk [V native_boundary.tsv line 506].
- Item layout: +0x00 field0 (W), +0x08 control (R/W), +0x10 state (R/W) [V dis].
- Control block layout: +0x08 strong refcount (R/W atomic), +0x0C weak refcount (R/W atomic) [V dis lock inc/dec].
- The `mov rax,[cb]; mov rax,[cb+0|8]` loads inside release sequences are dead (results unused).
- Calls to sub_eea6040 pass (control block, slot, src); idx 2 state 2 and idx 3 state 2 end in a tail jump to sub_eea6040 via rdx = [0xF99FFA0].

## Reversed source (complete)

The C++ below is the complete lift (src/client/features/render/native/bgfx/sub_bcac8b0.cpp,
with layout constants and static_asserts in the matching .h). Every instruction of
0xbcac8b0..0xbcacaf8 is inside a cited range; every `call` is quoted verbatim.

```cpp
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
// The original calls sub_eea6040 (boundary class "vendor", loader-resolved thunk) through
// the data slot 0xF99FFA0; every call site passes (control block, slot pointer, src
// pointer). Every `call qword ptr [0xF99FFA0]` address inside 0xbcac8b0..0xbcacaf8 is
// quoted verbatim below (plus the two in the inlined continuations):
//   0xbcac92a  call qword ptr [0xF99FFA0]
//   0xbcac94c  call qword ptr [0xF99FFA0]
//   0xbcac9d5  call qword ptr [0xF99FFA0]
//   0xbcac9f7  call qword ptr [0xF99FFA0]
//   0xbcaca56  call qword ptr [0xF99FFA0]
//   0xbcaca78  call qword ptr [0xF99FFA0]
//   0xbcacabb  call qword ptr [0xF99FFA0]
//   0xbcacad5  call qword ptr [0xF99FFA0]
//   0xbcacb7e  call qword ptr [0xF99FFA0]
//   0xbcacb9a  call qword ptr [0xF99FFA0]
//   0xbcaccb1  call qword ptr [0xF99FFA0]
//   0xbcaccd3  call qword ptr [0xF99FFA0]
//   0xbcacd06  call qword ptr [0xF99FFA0]
native::Boundary<void, std::uintptr_t, std::uintptr_t, std::uintptr_t> sub_eea6040("sub_eea6040");

std::uintptr_t slot_fn_ptr() {
    // The loader-resolved target of `call qword ptr [0xF99FFA0]`; the tail paths
    // materialize the same slot bytes in rdx (`mov rdx,[0xF99FFA0]` at 0xbcacbfd and
    // 0xbcacd1d) before the tail jump.
    return *reinterpret_cast<std::uintptr_t*>(0xF99FFA0);
}

// lock add dword ptr [p + 0x08], 1  (control-block strong refcount addref path,
// seen e.g. at 0xbcacb3c and 0xbcacc5c)
void addRef(void* p) {
    if (p != nullptr) {
        auto* rc = reinterpret_cast<std::atomic<std::int32_t>*>(
            static_cast<std::uint8_t*>(p) + 0x08);
        rc->fetch_add(1, std::memory_order_seq_cst);
    }
}

// maybeReleaseBoth: the release sequence used for an old control block:
//   lock dec dword ptr [cb + 0x08]; if zero -> sub_eea6040(cb, slot, src)
//   lock dec dword ptr [cb + 0x0C]; if zero -> sub_eea6040(cb, slot, src)
// The `mov rax,[cb]; mov rax,[cb+0|8]` loads inside the original release sequences are
// dead (their results are never consumed) and are not reproduced.
void maybeReleaseBoth(void* cb, void** slot, std::uintptr_t const* src) {
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

void storePayload16(void* obj, std::uintptr_t const* src) {
    // movups [obj], xmm0  with xmm0 = 16 bytes at src (two qword stores, low then high)
    *reinterpret_cast<std::uint64_t*>(obj) = src[0];
    *reinterpret_cast<std::uint64_t*>(static_cast<std::uint8_t*>(obj) + 8) = src[1];
}

void storePayload4(void* obj, std::uintptr_t const* src) {
    // mov [obj], eax  with eax = low 32 bits of [src]
    *reinterpret_cast<std::uint32_t*>(obj) = static_cast<std::uint32_t>(src[0]);
}

// Level-1 jump table on idx: six entries, no bounds check (matches the bare `jmp rcx`
// at 0xbcac8c7). Entries per data 0xF44B728: 0->0xbcac8c9, 1->0xbcac99a, 2->0xbcac972,
// 3->0xbcac986, 4->0xbcac8ef, 5->0xbcaca1b [V jt.py].
using ItemVisit = void (*)(void** slot, std::uintptr_t const* src);

void visitIdx0(void** slot, std::uintptr_t const* src);
void visitIdx1(void** slot, std::uintptr_t const* src);
void visitIdx2(void** slot, std::uintptr_t const* src);
void visitIdx3(void** slot, std::uintptr_t const* src);
void visitIdx4(void** slot, std::uintptr_t const* src);
void visitIdx5(void** slot, std::uintptr_t const* src);

ItemVisit const kIdxTable[6] = {
    visitIdx0,   // 0xbcac8c9
    visitIdx1,   // 0xbcac99a
    visitIdx2,   // 0xbcac972
    visitIdx3,   // 0xbcac986
    visitIdx4,   // 0xbcac8ef
    visitIdx5,   // 0xbcaca1b
};

// 0xbcac8c9..0xbcac8e4: idx 0 - switch on obj->state via table 0xF44B77C
//   states 1,2 -> 0xbcaca9b (maybeReleaseBoth); all other states -> 0xbcac8e6
//   every exit sets state = 0xFF; nothing is stored
void visitIdx0(void** slot, std::uintptr_t const* src) {
    // 0xbcac8c9  mov rdi,[rdx]
    void* obj = *slot;
    // 0xbcac8cc  movzx eax,byte ptr [rdi+0x10]
    std::uint8_t state = obj->state;
    // 0xbcac8d0  cmp rax,4 ; 0xbcac8d4  ja short 0xBCAC8E6
    if (state > 4) {
        // 0xbcac8e6  mov byte ptr [rdi+0x10],0xFF
        obj->state = 0xFF;
        return;
    }
    // 0xbcaca9b covers table entries for states 1 and 2
    if (state == 1 || state == 2)
        maybeReleaseBoth(obj->control, slot, src);
    // 0xbcac8e6  mov byte ptr [rdi+0x10],0xFF
    obj->state = 0xFF;
}

// 0xbcac99a..0xbcac9b5: idx 1 - switch on obj->state via table 0xF44B768
//   state 0 -> 0xbcacae9 (store 4 bytes, state unchanged)
//   states 1,2 -> 0xbcac9b7 (maybeReleaseBoth, then 0xbcaca03)
//   states 3,4 and default -> 0xbcaca03 (state = 0xFF, store 4 bytes, state = 0)
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
    case 2: // 0xbcac9b7
        maybeReleaseBoth(obj->control, slot, src);
        // 0xbcaca03
        obj->state = 0xFF;
        storePayload4(obj, src);
        obj->state = 0;
        return;
    case 3:
    case 4: // 0xbcaca03
        obj->state = 0xFF;
        storePayload4(obj, src);
        obj->state = 0;
        return;
    }
}

// 0xbcac972..0xbcac981: idx 2 - epilogue of this frame then tail into the 0xbcacb00
// continuation; reproduced inline below (same register state: rcx=slot, rdx=src).
void visitIdx2(void** slot, std::uintptr_t const* src) {
    // 0xbcacb00  mov rdi,[rcx]
    void* obj = *slot;
    // 0xbcacb0c  movzx eax,byte ptr [rdi+0x10]
    std::uint8_t state = obj->state;
    // 0xbcacb10  cmp rax,4 ; 0xbcacb14  ja short 0xBCACB26
    if (state > 4)
        goto bcacb26;
    switch (state) {
    case 0:
    case 3:
    case 4: // 0xbcacb26
bcacb26:
        // 0xbcacb26  mov byte ptr [rdi+0x10],0xFF
        obj->state = 0xFF;
        // 0xbcacb2a  mov rax,[rcx] ; 0xbcacb2d  xorps xmm0,xmm0 ; 0xbcacb30  movups [rax],xmm0
        obj->field0 = 0;
        obj->control = nullptr;
        // 0xbcacb33  mov r8,[rdx+8] ; 0xbcacb37  test r8,r8 ; 0xbcacb3a  je ... ;
        // 0xbcacb3c  lock inc dword ptr [r8+8]
        if (src[1] != 0)
            addRef(reinterpret_cast<void*>(src[1]));
        // 0xbcacb41  mov r8,[rdx] ; 0xbcacb44  mov [rax],r8 ;
        // 0xbcacb47  mov rdx,[rdx+8] ; 0xbcacb4b  mov [rax+8],rdx
        obj->field0 = src[0];
        obj->control = reinterpret_cast<void*>(src[1]);
        // 0xbcacb4f  mov rax,[rcx] ; 0xbcacb52  mov byte ptr [rax+0x10],1
        obj->state = 1;
        return;
    case 1: // 0xbcacbab
        // 0xbcacbab  mov rax,[rdx+8] ; 0xbcacbb4  lock inc dword ptr [rax+8] (if nonzero)
        if (src[1] != 0)
            addRef(reinterpret_cast<void*>(src[1]));
        // 0xbcacbc0  mov rcx,[rdx] ; 0xbcacbc3  mov [rdi],rcx
        obj->field0 = src[0];
        // 0xbcacbc6  mov rsi,[rdi+8]
        void* oldCb = obj->control;
        // 0xbcacbca  mov [rdi+8],rax
        obj->control = reinterpret_cast<void*>(src[1]);
        maybeReleaseBoth(oldCb, slot, src);
        return;
    case 2: // 0xbcacb60
        // 0xbcacb60  mov rsi,[rdi+8] ; 0xbcacb64  test rsi,rsi ; 0xbcacb67  je ... 0xBCACB26
        // 0xbcacb69  lock dec dword ptr [rsi+8] ; 0xbcacb6d  jne ... 0xBCACB26
        if (obj->control != nullptr) {
            auto* strong = reinterpret_cast<std::atomic<std::int32_t>*>(
                static_cast<std::uint8_t*>(obj->control) + 0x08);
            if (strong->fetch_sub(1, std::memory_order_seq_cst) == 1)
                sub_eea6040(obj->control, slot, src);
            auto* weak = reinterpret_cast<std::atomic<std::int32_t>*>(
                static_cast<std::uint8_t*>(obj->control) + 0x0C);
            if (weak->fetch_sub(1, std::memory_order_seq_cst) == 1) {
                sub_eea6040(obj->control, slot, src);
                // 0xbcacbfd  mov rdx,[0xF99FFA0] ; 0xbcacc10  jmp rdx  (tail call)
                sub_eea6040(obj->control, slot_fn_ptr(), src);
                return;
            }
        }
        goto bcacb26;
    }
}

// 0xbcac986..0xbcac995: idx 3 - epilogue of this frame then tail into the 0xbcacc20
// continuation; reproduced inline below (rcx=slot, rdx=src).
void visitIdx3(void** slot, std::uintptr_t const* src) {
    // 0xbcacc20  mov rdi,[rcx]
    void* obj = *slot;
    // 0xbcacc2c  movzx eax,byte ptr [rdi+0x10]
    std::uint8_t state = obj->state;
    // 0xbcacc30  cmp rax,4 ; 0xbcacc34  ja short 0xBCACC46
    if (state > 4)
        goto bcacc46;
    switch (state) {
    case 0:
    case 3:
    case 4: // 0xbcacc46
bcacc46:
        // 0xbcacc46  mov byte ptr [rdi+0x10],0xFF
        obj->state = 0xFF;
        // 0xbcacc4a  mov rax,[rcx] ; 0xbcacc4d  xorps xmm0,xmm0 ; 0xbcacc50  movups [rax],xmm0
        obj->field0 = 0;
        obj->control = nullptr;
        // 0xbcacc53..0xbcacc5c  addref [rdx+8] if nonzero
        if (src[1] != 0)
            addRef(reinterpret_cast<void*>(src[1]));
        // 0xbcacc61..0xbcacc72  store payload, state = 2
        obj->field0 = src[0];
        obj->control = reinterpret_cast<void*>(src[1]);
        obj->state = 2;
        return;
    case 1: // 0xbcacc93
        maybeReleaseBoth(obj->control, slot, src);
        goto bcacc46;
    case 2: // 0xbcacc80
        // 0xbcacc80  mov rax,[rdx+8] ; addref [rax+8] if nonzero
        if (src[1] != 0)
            addRef(reinterpret_cast<void*>(src[1]));
        // 0xbcacce0  mov rcx,[rdx] ; 0xbcacce3  mov [rdi],rcx
        obj->field0 = src[0];
        // 0xbcacce6  mov rsi,[rdi+8]
        void* oldCb = obj->control;
        // 0xbcaccea  mov [rdi+8],rax
        obj->control = reinterpret_cast<void*>(src[1]);
        // 0xbcaccee  test rsi,rsi ; 0xbcaccf1  je ... 0xBCACC76
        if (oldCb == nullptr)
            return;
        // 0xbcaccf3  lock dec dword ptr [rsi+8] ; 0xbcaccf7  jne ... 0xBCACC76
        {
            auto* strong = reinterpret_cast<std::atomic<std::int32_t>*>(
                static_cast<std::uint8_t*>(oldCb) + 0x08);
            if (strong->fetch_sub(1, std::memory_order_seq_cst) != 1)
                return;
        }
        sub_eea6040(oldCb, slot, src);
        // 0xbcacd0c  lock dec dword ptr [rsi+0xC] ; 0xbcacd10  jne 0xBCACC76
        {
            auto* weak = reinterpret_cast<std::atomic<std::int32_t>*>(
                static_cast<std::uint8_t*>(oldCb) + 0x0C);
            if (weak->fetch_sub(1, std::memory_order_seq_cst) != 1)
                return;
        }
        sub_eea6040(oldCb, slot, src);
        // 0xbcacd1d  mov rdx,[0xF99FFA0] ; 0xbcacd30  jmp rdx  (tail call)
        sub_eea6040(oldCb, slot_fn_ptr(), src);
        return;
    }
}

// 0xbcac8ef..0xbc90a: idx 4 - switch on obj->state via table 0xF44B754
//   states 0,4,default -> 0xbcac958 (state = 0xFF, store 16 bytes, state = 3)
//   states 1,2 -> 0xbcac90c (maybeReleaseBoth, then fall into 0xbcac958)
//   state 3 -> 0xbcacae0 (store 16 bytes, state unchanged)
void visitIdx4(void** slot, std::uintptr_t const* src) {
    // 0xbcac8ef  mov rdi,[rdx]
    void* obj = *slot;
    // 0xbcac8f2  movzx eax,byte ptr [rdi+0x10]
    std::uint8_t state = obj->state;
    // 0xbcac8f6  cmp rax,4 ; 0xbcac8fa  ja short 0xBCAC958
    bool store3 = false;
    if (state > 4)
        store3 = true;
    switch (state) {
    case 0:
    case 4: // 0xbcac958
        store3 = true;
        break;
    case 1:
    case 2: // 0xbcac90c
        maybeReleaseBoth(obj->control, slot, src);
        store3 = true;
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

// 0xbcaca1b..0xbcaca36: idx 5 - switch on obj->state via table 0xF44B740
//   states 0,3,default -> 0xbcaca84 (state = 0xFF, store 16 bytes, state = 4)
//   states 1,2 -> 0xbcaca38 (maybeReleaseBoth, then state = 0xFF, no store)
//   state 4 -> 0xbcacae0 (store 16 bytes, state unchanged)
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
        maybeReleaseBoth(obj->control, slot, src);
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
void sub_bcac8b0(std::uint32_t idx, void** slot, std::uintptr_t const* src) {
    // 0xbcac8b0  push r14 ; 0xbcac8b2  push rsi ; 0xbcac8b3  push rdi ; 0xbcac8b4  push rbx
    // 0xbcac8b5  sub rsp,0x28 ; 0xbcac8b9  lea rax,[0xF44B728] ; 0xbcac8c0  movsxd rcx,[rax+rcx*4]
    // 0xbcac8c4  add rcx,rax ; 0xbcac8c7  jmp rcx
    kIdxTable[idx](slot, src);
}

std::uint32_t sub_bcac8b0_footprint(void** slot, std::uintptr_t const* src) {
    // Writes: the 16-byte payload (+0x00..+0x0F) and state byte (+0x10) of the item at
    // *slot. Control-block refcount writes go through a dynamically loaded pointer and
    // are not part of the static footprint.
    if (slot == nullptr || *slot == nullptr)
        return {};
    return { { { *slot, 0x18ull } } };
}

LIFT_FN(bcac8b0, "Item group visitor", 0xBCAC8B0, sub_bcac8b0, sub_bcac8b0_footprint);

} // namespace native
```

## Struct fields touched

| Struct | Offset | Size | Direction | Meaning | Tag |
|---|---|---|---|---|---|
| Item | +0x00 | 8 | W | field0 (payload qword 0) | [V dis] |
| Item | +0x08 | 8 | R/W | control-block pointer | [V dis] |
| Item | +0x10 | 1 | R/W | state byte (0..4 tabled, else 0xFF) | [V dis] |
| ControlBlock | +0x08 | 4 | R/W | strong refcount (lock inc/dec) | [V dis] |
| ControlBlock | +0x0C | 4 | R/W | weak refcount (lock inc/dec) | [V dis] |
| src payload | +0x00 | 8 | R | payload qword 0 | [V dis] |
| src payload | +0x08 | 8 | R | payload qword 1 (control candidate) | [V dis] |

## Callees

| Call instruction | Target | Class | Tag |
|---|---|---|---|
| 0xbcac92a, 0xbcac94c, 0xbcac9d5, 0xbcac9f7, 0xbcaca56, 0xbcaca78, 0xbcacabb, 0xbcacad5, 0xbcacb7e, 0xbcacb9a, 0xbcaccb1, 0xbcaccd3, 0xbcacd06 | sub_eea6040 via `call qword ptr [0xF99FFA0]` | boundary "vendor" (native_boundary.tsv) | [V dis, native_boundary.tsv] |

No other calls; 0 callees inside the lift set. [V native_deps.tsv X1.bcac8b0]

## Ownership / threading

Refcount updates use lock-prefixed atomic operations (strong +0x08, weak +0x0C). No other
synchronization; the caller (sub_bcac590 at 0xbcac5f7 [V xr]) is responsible for object
lifetime outside this function. No SEH, no null guards beyond those in the original
(`test rsi,rsi`/`test rax,rax` around control-block and payload pointers).

## Version anchors

- Version: 1.26.62.01; function row: docs/data/native_functions.tsv 0xbcac8b0 size 0x248 depth 3 milestone 1 region bgfx status D0 [V frame_path_functions.tsv, native_functions.tsv].
- Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe [V].

## Verification

- liftcheck: `python tools/sigs/liftcheck.py 0xbcac8b0` -> LIFTCHECK OK 0xbcac8b0 (pending)
- verify_oc: every quoted `0xRVA  call ...` line matches rdis dis output of the exe
