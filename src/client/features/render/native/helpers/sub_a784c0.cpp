// LIFT 0xa784c0 size 0x10f 1.26.62.01 sub_a784c0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_a784c0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

// Layout assertions for every field read or written (mirrored from the header so
// liftcheck sees them in the compiled source too).
static_assert(offsetof(native::helpers::sub_a784c0_rcx, factory) == 0x38, "sub_0xa784c0 rcx+0x38 field");
static_assert(offsetof(native::helpers::sub_a784c0_rcx, listHead) == 0x40, "sub_0xa784c0 rcx+0x40 field");
static_assert(offsetof(native::helpers::sub_a784c0_rcx, listTail) == 0x48, "sub_0xa784c0 rcx+0x48 field");
static_assert(offsetof(native::helpers::sub_a784c0_rcx, mutex) == 0x50, "sub_0xa784c0 rcx+0x50 field");
static_assert(offsetof(native::helpers::sub_a784c0_rcx, count) == 0x9c, "sub_0xa784c0 rcx+0x9c field");
static_assert(offsetof(native::helpers::sub_a784c0_rcx, tlsSlot) == 0xa0, "sub_0xa784c0 rcx+0xa0 field");
static_assert(sizeof(native::helpers::sub_a784c0_rcx) >= 0xa1, "sub_0xa784c0 rcx sizeof lower bound");
static_assert(offsetof(native::helpers::sub_a784c0_rax, next) == 0x0, "sub_0xa784c0 rax+0x0 field");
static_assert(offsetof(native::helpers::sub_a784c0_rax, prev) == 0x8, "sub_0xa784c0 rax+0x8 field");
static_assert(offsetof(native::helpers::sub_a784c0_rax, value) == 0x10, "sub_0xa784c0 rax+0x10 field");
static_assert(sizeof(native::helpers::sub_a784c0_rax) == 0x28, "sub_0xa784c0 node allocation size");
static_assert(offsetof(native::helpers::sub_a784c0_rbx, f0) == 0x0, "sub_0xa784c0 rbx+0x0 field");
static_assert(sizeof(native::helpers::sub_a784c0_rbx) >= 0x8, "sub_0xa784c0 rbx sizeof lower bound");
static_assert(offsetof(native::helpers::sub_a784c0_rsp, f20) == 0x20, "sub_0xa784c0 rsp+0x20 field");
static_assert(sizeof(native::helpers::sub_a784c0_rsp) >= 0x28, "sub_0xa784c0 rsp sizeof lower bound");

namespace native::helpers {

LIFT_FN(sub_a784c0, "sub_a784c0", 0xa784c0, sub_a784c0, nullptr);

// Verbatim call instructions from the disassembly of [0xa784c0, 0xa785cf) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xa784d6  call 0x9BD4A0
0xa784fc  call qword ptr [0xF99FFA0]
0xa7853e  call qword ptr [0xF99FFA0]
0xa7854a  call 0x9BD6D0
0xa78556  call 0xEEC59F0
0xa78584  call 0xEEC5A10
0xa7859e  call 0x9BC830
0xa785ab  call 0xEEC59E0
0xa785b5  call 0xEEC5A00
0xa785c9  call 0xEEC5A00
#endif

// Boundary / lifted callees called through their native symbol.
// 0x9bd4a0 TLS get (os), 0x9bd6d0 TLS set (os), 0x9bc830 allocator OOM (alloc),
// 0xeec59e0 std::_Xbad_function_call, 0xeec59f0 _Mtx_lock, 0xeec5a00 std::_Throw_Cpp_error,
// 0xeec5a10 _Mtx_unlock.
extern "C" void* sub_9bd4a0(void* slot);
extern "C" void  sub_9bd6d0(void* slot, void* value);
extern "C" void* sub_9bc830(std::uint32_t size);
extern "C" void  sub_eec59e0(void);
extern "C" int   sub_eec59f0(void* mtx);
extern "C" void  sub_eec5a00(int code);
extern "C" void  sub_eec5a10(void* mtx);

// [0x1233E1A8] is the process allocator object; [0xF99FFA0] is the control-flow-guard
// dispatch slot holding sub_eea6040 (`jmp rax`). The two indirect calls below load the
// allocator/factory vtable slot into the called function pointer, exactly the target the
// original places into RAX before `call qword ptr [0xF99FFA0]`.
constexpr std::uintptr_t kAllocatorSlot = 0x141233E1A8ULL;
constexpr std::uintptr_t kDispatchSlot  = 0x14F99FFA0ULL;

void* sub_a784c0(void* a0) {
    auto* const self = reinterpret_cast<sub_a784c0_rcx*>(a0);

    // 0xa784c0..0xa784e0: basic block 0 (TLS lookup)
    // 0xa784c0  push r14
    // 0xa784c2  push rsi
    // 0xa784c3  push rdi
    // 0xa784c4  push rbx
    // 0xa784c5  sub rsp,0x28
    // 0xa784c9  mov rsi,rcx
    // 0xa784cc  lea rbx,[rcx+0xA0]
    // 0xa784d3  mov rcx,rbx
    // 0xa784d6  call 0x9BD4A0
    // 0xa784db  test rax,rax
    // 0xa784de  je short 0xA784E9
    void* const tlsSlot = &self->tlsSlot;
    void* const tlsValue = sub_9bd4a0(tlsSlot);
    if (tlsValue != nullptr) {
        // 0xa784e0..0xa784e9: basic block 1 (cached node payload)
        // 0xa784e0  add rax,0x10
        // 0xa784e4  jmp 0xA7858C
        return static_cast<std::uint8_t*>(tlsValue) + 0x10;
    }

    // 0xa784e9..0xa7850e: basic block 2 (allocate the 0x28-byte node)
    // 0xa784e9  mov rcx,[0x1233E1A8]
    // 0xa784f0  mov rax,[rcx]
    // 0xa784f3  mov rax,[rax+8]
    // 0xa784f7  mov edx,0x28
    // 0xa784fc  call qword ptr [0xF99FFA0]
    // 0xa78502  mov rdi,rax
    // 0xa78505  test rax,rax
    // 0xa78508  je 0xA78596
    (void)kDispatchSlot;
    void* const allocator = *reinterpret_cast<void**>(reinterpret_cast<void*>(kAllocatorSlot));
    void** const allocVtbl = *reinterpret_cast<void***>(allocator);
    using AllocFn = void* (*)(void*, std::size_t);
    AllocFn const sub_eea6040_alloc = reinterpret_cast<AllocFn>(allocVtbl[1]);
    void* const nodeMem = sub_eea6040_alloc(allocator, 0x28);
    auto* node = reinterpret_cast<sub_a784c0_rax*>(nodeMem);
    if (nodeMem == nullptr) {
        // 0xa78596..0xa785ab: basic block 8 (allocator out-of-memory handler)
        // 0xa78596  mov ecx,0x28
        // 0xa7859b  mov r14,rax
        // 0xa7859e  call 0x9BC830
        // 0xa785a3  mov rax,r14
        // 0xa785a6  jmp 0xA7850E
        void* const savedRax = nodeMem;
        (void)sub_9bc830(0x28);
        node = reinterpret_cast<sub_a784c0_rax*>(savedRax);
    }

    // 0xa7850e..0xa7852f: basic block 3 (initialise links, payload slot and factory)
    // 0xa7850e  mov [rdi],rdi
    // 0xa78511  mov [rdi+8],rdi
    // 0xa78515  add rax,0x10
    // 0xa78519  mov qword ptr [rdi+0x10],0
    // 0xa78521  mov [rsp+0x20],rax
    // 0xa78526  mov rcx,[rsi+0x38]
    // 0xa7852a  test rcx,rcx
    // 0xa7852d  je short 0xA785AB
    node->next = node;
    node->prev = node;
    void* const payload = reinterpret_cast<std::uint8_t*>(node) + 0x10;
    *reinterpret_cast<void**>(node->value) = nullptr;
    void* stackPayload = payload;
    void* const factory = self->factory;

    // 0xa7852f..0xa7855f: basic block 4 (fill payload, install TLS node, lock)
    // 0xa7852f  mov r14,rax
    // 0xa78532  mov rax,[rcx]
    // 0xa78535  mov rax,[rax+0x10]
    // 0xa78539  lea rdx,[rsp+0x20]
    // 0xa7853e  call qword ptr [0xF99FFA0]
    // 0xa78544  mov rcx,rbx
    // 0xa78547  mov rdx,rdi
    // 0xa7854a  call 0x9BD6D0
    // 0xa7854f  lea rbx,[rsi+0x50]
    // 0xa78553  mov rcx,rbx
    // 0xa78556  call 0xEEC59F0
    // 0xa7855b  test eax,eax
    // 0xa7855d  jne short 0xA785B0
    void* const mutex = &self->mutex;
    bool throwDeadlock = false;
    if (factory == nullptr) {
        // 0xa785ab..0xa785b0: basic block 9 (no factory object; falls into block 10)
        // 0xa785ab  call 0xEEC59E0
        sub_eec59e0();
        throwDeadlock = true;
    } else {
        void** const factoryVtbl = *reinterpret_cast<void***>(factory);
        using FactoryFn = void (*)(void*, void**);
        FactoryFn const sub_eea6040_factory = reinterpret_cast<FactoryFn>(factoryVtbl[2]);
        sub_eea6040_factory(factory, &stackPayload);
        sub_9bd6d0(tlsSlot, node);
        int const lockResult = sub_eec59f0(mutex);
        if (lockResult != 0) throwDeadlock = true;
    }

    // 0xa785b0..0xa785ba: basic block 10 (deadlock error code 5)
    // 0xa785b0  mov ecx,5
    // 0xa785b5  call 0xEEC5A00
    if (throwDeadlock) sub_eec5a00(5);

    // 0xa7855f..0xa7856b: basic block 5 (list size guard)
    // 0xa7855f  cmp dword ptr [rsi+0x9C],0x7FFFFFFF
    // 0xa78569  je short 0xA785BA
    if (self->count == 0x7FFFFFFFu) {
        // 0xa785ba..0xa785cf: basic block 11 (size-limit error code 6)
        // 0xa785ba  mov dword ptr [rsi+0x9C],0x7FFFFFFE
        // 0xa785c4  mov ecx,6
        // 0xa785c9  call 0xEEC5A00
        // 0xa785ce  int3
        // 0xa785cf  int3
        self->count = 0x7FFFFFFEu;
        sub_eec5a00(6);
    }

    // 0xa7856b..0xa7858c: basic block 6 (link node at tail, unlock)
    // 0xa7856b  lea rax,[rsi+0x40]
    // 0xa7856f  mov rcx,[rsi+0x48]
    // 0xa78573  mov [rdi+8],rcx
    // 0xa78577  mov [rdi],rax
    // 0xa7857a  mov [rcx],rdi
    // 0xa7857d  mov [rsi+0x48],rdi
    // 0xa78581  mov rcx,rbx
    // 0xa78584  call 0xEEC5A10
    // 0xa78589  mov rax,r14
    void* const listHead = reinterpret_cast<std::uint8_t*>(self) + 0x40;
    void* const oldTail = self->listTail;
    node->prev = oldTail;
    node->next = listHead;
    reinterpret_cast<sub_a784c0_rax*>(oldTail)->next = node;
    self->listTail = node;
    sub_eec5a10(mutex);

    // 0xa7858c..0xa78596: basic block 7 (epilogue); RAX = R14 = node + 0x10
    // 0xa7858c  add rsp,0x28
    // 0xa78590  pop rbx
    // 0xa78591  pop rdi
    // 0xa78592  pop rsi
    // 0xa78593  pop r14
    // 0xa78595  ret
    return payload;
}

} // namespace native::helpers
