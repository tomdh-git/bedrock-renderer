// LIFT 0xbc962c0 size 0x12f 1.26.62.01 sub_bc962c0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc962c0.h"

#include <cstdint>
#include <intrin.h>

// Layout assertions (definitions in sub_bc962c0.h; repeated here so liftcheck sees them
// in the source file).
static_assert(offsetof(native::bgfx::sub_bc962c0_state, field_0x00) == 0x00);
static_assert(offsetof(native::bgfx::sub_bc962c0_state, field_0x10) == 0x10);
static_assert(offsetof(native::bgfx::sub_bc962c0_state, field_0x18) == 0x18);
static_assert(offsetof(native::bgfx::sub_bc962c0_state, field_0x28) == 0x28);
static_assert(offsetof(native::bgfx::sub_bc962c0_state, field_0x68) == 0x68);
static_assert(offsetof(native::bgfx::sub_bc962c0_state, field_0x78) == 0x78);
static_assert(offsetof(native::bgfx::sub_bc962c0_state, field_0x88) == 0x88);
static_assert(offsetof(native::bgfx::sub_bc962c0_state, field_0x90) == 0x90);
static_assert(sizeof(native::bgfx::sub_bc962c0_state) == 0x98);

// Verbatim call instructions from the disassembly of [0xbc962c0, 0xbc963ef) (rdis dis output):
// 0xbc96306  call 0xE935700              ; -> sub_e935700 (lift-set callee, `jmp sub_392960`)  [path: capacity+1 < 0x1000]
// 0xbc96306  call 0xE935700              ; -> sub_e935700  [path: header-size argument]
// 0xbc9633f  call qword ptr [0xF99FFA0]  ; [data_f99ffa0] = sub_eea6040, jmp-rax thunk -> vtable[4](objC)
// 0xbc96365  call qword ptr [0xF99FFA0]  ; [data_f99ffa0] = sub_eea6040 -> vtable[0](objB)
// 0xbc9637b  call qword ptr [0xF99FFA0]  ; [data_f99ffa0] = sub_eea6040 -> vtable[1](objB)
// 0xbc963e8  call qword ptr [0xF9A8C78]  ; [data_f9a8c78] -> _invoke_watson(nullptr,nullptr,nullptr,0,0) (noreturn)
// UNRESOLVED CALL = none: sub_e935700 is a lift-set callee (forward-declared above, native symbol),
// and the two indirect calls go through documented data slots read at call time ([0xF99FFA0],
// [0xF9A8C78]) per the indirect-call rule; no callee is outside the lift set / boundary.

namespace native::bgfx {

// sub_eea6040 ([data_f99ffa0], VA 0x14F99FFA0) is a `jmp rax` thunk, so each
// `call qword ptr [0xF99FFA0]` above is an indirect virtual call: the original loads
// vtable[slot] into rax and the thunk tails to it, with rcx = obj.
// Reads: obj+0x00 (vtable pointer), then vtable+slot*8; call target(obj).
static void vtableCallSlot0(void* obj) {
    void** vt = *reinterpret_cast<void***>(obj);
    reinterpret_cast<void (*)(void*)>(vt[0])(obj);
}
static void vtableCallSlot1(void* obj) {
    void** vt = *reinterpret_cast<void***>(obj);
    reinterpret_cast<void (*)(void*)>(vt[1])(obj);
}
static void vtableCallSlot4(void* obj) {
    void** vt = *reinterpret_cast<void***>(obj);
    reinterpret_cast<void (*)(void*)>(vt[4])(obj);
}

// Strong/weak release matching:
//   0xbc96356  lock dec dword ptr [rdi+8]      ; jne short 0xBC96381  (strong != 0 -> skip everything)
//   0xbc9635c..0xbc96365                      ; vtable[0](obj)  (destructor, strong hit 0)
//   0xbc9636b  lock dec dword ptr [rdi+0xC]    ; jne short 0xBC96381  (weak != 0 -> skip dealloc)
//   0xbc96371..0xbc9637b                      ; vtable[1](obj)  (deallocator, weak hit 0)
static void releaseRefObj(RefObj* obj) {
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&obj->strong)) == 0) {
        vtableCallSlot0(obj);                  // 0xbc9635c  mov rax,[rdi]
        // 0xbc9635f  mov rax,[rax]
        // 0xbc96362  mov rcx,rdi
        // 0xbc96365  call qword ptr [0xF99FFA0]
        if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&obj->weak)) == 0) {
            vtableCallSlot1(obj);              // 0xbc96371  mov rax,[rdi]
            // 0xbc96374  mov rax,[rax+8]
            // 0xbc96378  mov rcx,rdi
            // 0xbc9637b  call qword ptr [0xF99FFA0]
        }
    }
}

void sub_bc962c0(sub_bc962c0_state* self) {
    // 0xbc962c0..0xbc962c6: prologue
    //   0xbc962c0  push rsi
    //   0xbc962c1  push rdi
    //   0xbc962c2  sub rsp,0x28
    //   0xbc962c6  mov rsi,rcx                 ; self = rcx

    // 0xbc962c6..0xbc9630b: buffer B (data @+0x78, size @+0x88, capacity @+0x90):
    //   0xbc962c9  mov rax,[rcx+0x90]          ; capB
    //   0xbc962d0  cmp rax,0x10
    //   0xbc962d4  jb short 0xBC9630B          ; capB < 0x10 -> small buffer, nothing to free
    //   0xbc962d6  mov rcx,[rsi+0x78]          ; dataB pointer
    //   0xbc962da  lea rdx,[rax+1]             ; capB + 1
    //   0xbc962de  cmp rdx,0x1000
    //   0xbc962e5  jb short 0xBC96306          ; capB + 1 < 0x1000 -> small-free path
    //   0xbc962e7  mov r8,[rcx-8]              ; heap header size
    //   0xbc962eb  add rcx,0xFFFFFFFFFFFFFFF8  ; rcx = dataB - 8
    //   0xbc962ef  sub rcx,r8                  ; rcx = (dataB - 8) - headerSize
    //   0xbc962f2  cmp rcx,0x20
    //   0xbc962f6  jae 0xBC963D5               ; header inconsistent -> fail path (watson)
    //   0xbc962fc  add rax,0x28                ; capB + 0x28
    //   0xbc96300  mov rdx,rax
    //   0xbc96303  mov rcx,r8                  ; rcx = headerSize
    //   0xbc96306  call 0xE935700              ; both paths converge here
    uint64_t capB = self->field_0x90;                         // 0xbc962c9  mov rax,[rcx+0x90]
    if (capB < 0x10ULL) goto resetB;                          // 0xbc962d0  cmp rax,0x10 / 0xbc962d4  jb short 0xBC9630B
    void* dataB = self->field_0x78;                           // 0xbc962d6  mov rcx,[rsi+0x78]
    if (capB + 1ULL < 0x1000ULL) {                            // 0xbc962da  lea rdx,[rax+1] / 0xbc962de  cmp rdx,0x1000 / 0xbc962e5  jb short 0xBC96306
        (void)sub_e935700((uint64_t)dataB, capB + 1ULL);      // 0xbc96306  call 0xE935700  (rcx = dataB, rdx = capB + 1)
    } else {
        uint64_t hdrB = *reinterpret_cast<uint64_t*>(         // 0xbc962e7  mov r8,[rcx-8]
            reinterpret_cast<uint8_t*>(dataB) - 8);
        uint64_t delta = (reinterpret_cast<uintptr_t>(dataB) - 8) - hdrB;  // 0xbc962eb..0xbc962ef
        if (delta >= 0x20ULL) goto fail;                      // 0xbc962f2  cmp rcx,0x20 / 0xbc962f6  jae 0xBC963D5
        (void)sub_e935700(hdrB, capB + 0x28ULL);              // 0xbc96306  call 0xE935700  (rcx = hdrB, rdx = capB + 0x28)
    }

resetB:                                                     // 0xbc9630b
    //   0xbc9630b  mov qword ptr [rsi+0x88],0
    //   0xbc96316  mov qword ptr [rsi+0x90],0xF
    //   0xbc96321  mov byte ptr [rsi+0x78],0
    self->field_0x88 = 0;                                     // 0xbc9630b
    self->field_0x90 = 0xFULL;                                // 0xbc96316
    *reinterpret_cast<uint8_t*>(&self->field_0x78) = 0;       // 0xbc96321

    // 0xbc96325..0xbc9634d: object C (@+0x68): vtable[4] release via jmp-rax thunk, then clear pointer.
    //   0xbc96325  mov rcx,[rsi+0x68]
    //   0xbc96329  test rcx,rcx
    //   0xbc9632c  je short 0xBC9634D
    //   0xbc9632e  lea rax,[rsi+0x30]            ; &self+0x30 (dead comparator operand)
    //   0xbc96332  cmp rcx,rax
    //   0xbc96335  setne dl                      ; dl never read: no observable effect
    //   0xbc96338  mov rax,[rcx]                 ; objC vtable pointer
    //   0xbc9633b  mov rax,[rax+0x20]            ; vtable[4]
    //   0xbc9633f  call qword ptr [0xF99FFA0]    ; vtable[4](objC)
    //   0xbc96345  mov qword ptr [rsi+0x68],0
    RefObj* objC = self->field_0x68;              // 0xbc96325  mov rcx,[rsi+0x68]
    if (objC != nullptr) {                        // 0xbc96329  test rcx,rcx / 0xbc9632c  je short 0xBC9634D
        // 0xbc9632e  lea rax,[rsi+0x30] / 0xbc96332  cmp rcx,rax / 0xbc96335  setne dl — result never read.
        vtableCallSlot4(objC);                    // 0xbc96338  mov rax,[rcx] / 0xbc9633b  mov rax,[rax+0x20] / 0xbc9633f  call qword ptr [0xF99FFA0]
    }
    self->field_0x68 = nullptr;                   // 0xbc96345  mov qword ptr [rsi+0x68],0

    // 0xbc9634d..0xbc96381: object B (@+0x28): strong release, destructor vtable[0],
    // weak release, deallocator vtable[1]. (See releaseRefObj for the per-instruction quotes.)
    //   0xbc9634d  mov rdi,[rsi+0x28]
    //   0xbc96351  test rdi,rdi
    //   0xbc96354  je short 0xBC96381
    RefObj* objB = self->field_0x28;              // 0xbc9634d  mov rdi,[rsi+0x28]
    if (objB != nullptr) {                        // 0xbc96351  test rdi,rdi / 0xbc96354  je short 0xBC96381
        releaseRefObj(objB);                      // 0xbc96356..0xbc9637b
    }
    // NOTE: field_0x28 is NOT written back — the original leaves the dangling pointer.

    // 0xbc96381..0xbc963bb: buffer A (data @+0x00, size @+0x10, capacity @+0x18):
    //   0xbc96381  mov rax,[rsi+0x18]          ; capA
    //   0xbc96385  cmp rax,0x10
    //   0xbc96389  jb short 0xBC963BB          ; capA < 0x10 -> small buffer, nothing to free
    //   0xbc9638b  mov rcx,[rsi]               ; dataA pointer
    //   0xbc9638e  lea rdx,[rax+1]             ; capA + 1
    //   0xbc96392  cmp rdx,0x1000
    //   0xbc96399  jb short 0xBC963B6          ; capA + 1 < 0x1000 -> small-free path
    //   0xbc9639b  mov r8,[rcx-8]              ; heap header size
    //   0xbc9639f  add rcx,0xFFFFFFFFFFFFFFF8  ; rcx = dataA - 8
    //   0xbc963a3  sub rcx,r8                  ; rcx = (dataA - 8) - headerSize
    //   0xbc963a6  cmp rcx,0x20
    //   0xbc963aa  jae short 0xBC963D5         ; header inconsistent -> fail path (watson)
    //   0xbc963ac  add rax,0x28                ; capA + 0x28
    //   0xbc963b0  mov rdx,rax
    //   0xbc963b3  mov rcx,r8                  ; rcx = headerSize
    //   0xbc963b6  call 0xE935700              ; both paths converge here
    uint64_t capA = self->field_0x18;                         // 0xbc96381  mov rax,[rsi+0x18]
    if (capA < 0x10ULL) goto resetA;                          // 0xbc96385  cmp rax,0x10 / 0xbc96389  jb short 0xBC963BB
    void* dataA = self->field_0x00;                           // 0xbc9638b  mov rcx,[rsi]
    if (capA + 1ULL < 0x1000ULL) {                            // 0xbc9638e  lea rdx,[rax+1] / 0xbc96392  cmp rdx,0x1000 / 0xbc96399  jb short 0xBC963B6
        (void)sub_e935700((uint64_t)dataA, capA + 1ULL);      // 0xbc963b6  call 0xE935700  (rcx = dataA, rdx = capA + 1)
    } else {
        uint64_t hdrA = *reinterpret_cast<uint64_t*>(         // 0xbc9639b  mov r8,[rcx-8]
            reinterpret_cast<uint8_t*>(dataA) - 8);
        uint64_t delta = (reinterpret_cast<uintptr_t>(dataA) - 8) - hdrA;
        if (delta >= 0x20ULL) goto fail;                      // 0xbc963a6  cmp rcx,0x20 / 0xbc963aa  jae short 0xBC963D5
        (void)sub_e935700(hdrA, capA + 0x28ULL);              // 0xbc963b6  call 0xE935700  (rcx = hdrA, rdx = capA + 0x28)
    }

resetA:                                                     // 0xbc963bb
    //   0xbc963bb  mov qword ptr [rsi+0x10],0
    //   0xbc963c3  mov qword ptr [rsi+0x18],0xF
    //   0xbc963cb  mov byte ptr [rsi],0
    //   0xbc963ce  add rsp,0x28
    //   0xbc963d2  pop rdi
    //   0xbc963d3  pop rsi
    //   0xbc963d4  ret
    self->field_0x10 = 0;                                     // 0xbc963bb
    self->field_0x18 = 0xFULL;                                // 0xbc963c3
    *reinterpret_cast<uint8_t*>(&self->field_0x00) = 0;       // 0xbc963cb
    return;                                                   // 0xbc963ce..0xbc963d4

fail:                                                         // 0xbc963d5
    // 0xbc963d5..0xbc963ef: bounds-check failure path
    //   0xbc963d5  mov qword ptr [rsp+0x20],0   ; scratch stack store (not observable outside this function)
    //   0xbc963de  xor ecx,ecx
    //   0xbc963e0  xor edx,edx
    //   0xbc963e2  xor r8d,r8d
    //   0xbc963e5  xor r9d,r9d                 ; watson arguments all zero
    //   0xbc963e8  call qword ptr [0xF9A8C78]   ; [data_f9a8c78] -> _invoke_watson(nullptr,nullptr,nullptr,0,0)
    //   0xbc963ee  int3                        ; unreachable (_invoke_watson terminates)
    using Watson = uintptr_t(__cdecl*)(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t);
    (void)reinterpret_cast<Watson>(*reinterpret_cast<uintptr_t*>(0x14F9A8C78ULL))
        (nullptr, nullptr, nullptr, 0, 0);
    // 0xbc963ee  int3 — unreachable (_invoke_watson terminates the process).
    return;
    // 0xbc963ef  int3 — padding after the function end, outside [0xbc962c0, 0xbc963ef).
}

static native::Footprint sub_bc962c0_footprint(sub_bc962c0_state* self) {
    // Writes within *self: field_0x00 (byte), field_0x10, field_0x18, field_0x68,
    // field_0x78 (byte), field_0x88, field_0x90. Side effects on other objects
    // (refcounts via releaseRefObj, virtual calls through [0xF99FFA0], the global read
    // performed by sub_e935700) are out of function scope; the watson path does not return.
    return { { self, 0x98 } };
}

LIFT_FN(sub_bc962c0, "sub_bc962c0", 0xbc962c0, sub_bc962c0, sub_bc962c0_footprint);

} // namespace native::bgfx
