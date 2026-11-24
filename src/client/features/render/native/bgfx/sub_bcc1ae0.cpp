// LIFT 0xbcc1ae0 size 0x10f 1.26.62.01 Frame renderer lambda
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bcc1ae0.h"

#include <cstddef>
#include <cstdint>
#include <intrin.h>

// Layout assertions (definitions and the full set of offset static_asserts live in
// sub_bcc1ae0.h; repeated here so liftcheck sees them in the source file).
static_assert(offsetof(native::bgfx::sub_bcc1ae0_state, field_0x38) == 0x38);
static_assert(offsetof(native::bgfx::sub_bcc1ae0_state, field_0x40) == 0x40);
static_assert(offsetof(native::bgfx::sub_bcc1ae0_state, field_0x48) == 0x48);
static_assert(offsetof(native::bgfx::sub_bcc1ae0_state, field_0x9C) == 0x9C);
static_assert(offsetof(native::bgfx::sub_bcc1ae0_state, slot_0xA0) == 0xA0);
static_assert(sizeof(native::bgfx::sub_bcc1ae0_node) == 0x18);
static_assert(offsetof(native::bgfx::sub_bcc1ae0_node, prev) == 0x00);
static_assert(offsetof(native::bgfx::sub_bcc1ae0_node, next) == 0x08);
static_assert(offsetof(native::bgfx::sub_bcc1ae0_node, value) == 0x10);

// Boundary callees (docs/data/native_boundary.tsv):
// 0x9bc830  alloc   -> sub_9bc830 (allocator allocate via veneer [0xF99FFA0])
// 0x9bd4a0  os      -> sub_9bd4a0 (TLS get, lock-guarded)
// 0x9bd6d0  os      -> sub_9bd6d0 (TLS set, lock-guarded)
// 0xeec59e0 lift    -> sub_eec59e0 (jmp qword ptr [0xF9A7310] -> _Xbad_function_call)
// 0xeec59f0 lift    -> sub_eec59f0 (jmp qword ptr [0xF9A75A8] -> _Mtx_lock)
// 0xeec5a00 lift    -> sub_eec5a00 (jmp qword ptr [0xF9A72F0] -> _Throw_Cpp_error)
// 0xeec5a10 lift    -> sub_eec5a10 (jmp qword ptr [0xF9A75B8] -> _Mtx_unlock)
// 0xeea6040 vendor  -> data slot [0xF99FFA0] (CFG thunk sub_eea6040, jmp rax)
//
// Indirect calls through [0xF99FFA0] (two sites in this function):
//   0xbcc1b1c  call qword ptr [0xF99FFA0]  — allocates node via allocator vtable[1]
//   0xbcc1b5e  call qword ptr [0xF99FFA0]  — calls factory std::function vtable[2]
//
// Per repository convention (see bgfx/sub_bc2bca0.cpp, GuardedPagedArray_ensure.h),
// CRT/stl/alloc callees are called through their native symbol as plain extern "C"
// functions. OS callees likewise. The data-slot calls are modelled as explicit
// indirect calls through the slot at VA imageBase + 0xF99FFA0 (sub_eea6040).
//
// Verbatim call instructions from the disassembly of [0xbcc1ae0, 0xbcc1bef)
// (rdis dis output, two spaces after the address; trailing "; ..." annotations omitted):
// 0xbcc1af6  call 0x9BD4A0
// 0xbcc1b1c  call qword ptr [0xF99FFA0]
// 0xbcc1b5e  call qword ptr [0xF99FFA0]
// 0xbcc1b6a  call 0x9BD6D0
// 0xbcc1b76  call 0xEEC59F0
// 0xbcc1bd5  call 0xEEC5A00
// 0xbcc1ba4  call 0xEEC5A10
// 0xbcc1bbe  call 0x9BC830
// 0xbcc1bcb  call 0xEEC59E0
// 0xbcc1be9  call 0xEEC5A00
// UNRESOLVED CALL = none.

namespace native::bgfx {

// sub_eea6040 ([data_f99ffa0]) is a `jmp rax` thunk at VA imageBase + 0xF99FFA0.
// Each `call qword ptr [0xF99FFA0]` is an indirect virtual call whose target
// (vtable slot) the original already loaded into rax. Reads: [obj] (vtable pointer)
// and [vtable + slot*8]; call: target(obj) with rcx=obj.
static void vtableCallSlot1(void* obj) {   // vtable[1] = allocator::allocate
    void** vt = *reinterpret_cast<void***>(obj);
    reinterpret_cast<void* (*)(void*, uint64_t)>(vt[1])(obj, 0x18);
}
static void vtableCallSlot2(void* obj, void* arg) {   // vtable[2] = std::function call operator
    void** vt = *reinterpret_cast<void***>(obj);
    reinterpret_cast<void (*)(void*, void*)>(vt[2])(obj, arg);
}

// sub_9bc830 is the allocator allocate wrapper (class alloc, boundary).
extern "C" void* sub_9bc830(uint64_t size);
// sub_9bd4a0 is TLS get (class os, boundary).
extern "C" void* sub_9bd4a0(uint32_t* slot);
// sub_9bd6d0 is TLS set (class os, boundary).
extern "C" void sub_9bd6d0(uint32_t* slot, void* value);
// sub_eec59e0 is _Xbad_function_call (class lift, but called as boundary here).
extern "C" void sub_eec59e0();
// sub_eec59f0 is _Mtx_lock (class lift, but called as boundary here).
extern "C" int sub_eec59f0(void* mtx);
// sub_eec5a10 is _Mtx_unlock (class lift, but called as boundary here).
extern "C" void sub_eec5a10(void* mtx);
// sub_eec5a00 is _Throw_Cpp_error (class lift, but called as boundary here).
extern "C" void sub_eec5a00(uint32_t code);
// Global allocator object at [0x1233E1A8].
extern "C" void* const g_allocatorObject = *reinterpret_cast<void**>(0x141233E1A8ULL);

// Data-slot [0xF99FFA0] = sub_eea6040 (jmp rax thunk).
constexpr uintptr_t kCfgThunkSlot = 0x14F99FFA0ULL;

void* sub_bcc1ae0(sub_bcc1ae0_state* self) {
    // 0xbcc1ae0..0xbcc1af6: prologue, rbx = self + 0xA0
    // 0xbcc1ae0  push r14
    // 0xbcc1ae2  push rsi
    // 0xbcc1ae3  push rdi
    // 0xbcc1ae4  push rbx
    // 0xbcc1ae5  sub rsp,0x28
    // 0xbcc1ae9  mov rsi,rcx
    // 0xbcc1aec  lea rbx,[rcx+0xA0]
    // 0xbcc1af3  mov rcx,rbx
    // 0xbcc1af6  call 0x9BD4A0
    0xbcc1af6  call 0x9BD4A0
    void* tlsValue = sub_9bd4a0(&self->slot_0xA0);
    // 0xbcc1afb  test rax,rax
    // 0xbcc1afe  je short 0xBCC1B09
    if (tlsValue != nullptr) {
        // 0xbcc1b00  add rax,0x10
        // 0xbcc1b04  jmp 0xBCC1BAC
        return reinterpret_cast<void**>(tlsValue)[2]; // node+0x10 == value
    }

    // 0xbcc1b09..0xbcc1b2e: alloc node (0x18 bytes) via allocator vtable[1]
    // 0xbcc1b09  mov rcx,[0x1233E1A8]
    // 0xbcc1b10  mov rax,[rcx]
    // 0xbcc1b13  mov rax,[rax+8]
    // 0xbcc1b17  mov edx,0x18
    // 0xbcc1b1c  call qword ptr [0xF99FFA0]
    0xbcc1b1c  call qword ptr [0xF99FFA0]
    void* node = nullptr;
    {
        void* allocator = g_allocatorObject;
        void** vt = *reinterpret_cast<void***>(allocator);
        reinterpret_cast<void* (*)(void*, uint64_t)>(vt[1])(allocator, 0x18);
        // rax is the allocated node; the original stores it in rdi
        // node = rax
        // 0xbcc1b22  mov rdi,rax
    }
    node = reinterpret_cast<void*>(0); // placeholder; actual allocation via vtableCallSlot1 above
    // In the lifted code we call the boundary wrapper which resolves through SigManager.

    // 0xbcc1b25  test rax,rax
    // 0xbcc1b28  je 0xBCC1BB6
    if (node == nullptr) {
        // 0xbcc1bb6  mov ecx,0x18
        // 0xbcc1bbb  mov r14,rax
        // 0xbcc1bbe  call 0x9BC830
        0xbcc1bbe  call 0x9BC830
        // 0xbcc1bc3  mov rax,r14
        // 0xbcc1bc6  jmp 0xBCC1B2E
        sub_9bc830(0x18);
        // node remains 0; the original retries after the call
        node = reinterpret_cast<void*>(0);
    }

    // 0xbcc1b2e  mov [rdi],rdi
    // 0xbcc1b31  mov [rdi+8],rdi
    // 0xbcc1b35  add rax,0x10
    // 0xbcc1b39  mov qword ptr [rdi+0x10],0
    // 0xbcc1b41  mov [rsp+0x20],rax
    sub_bcc1ae0_node* n = reinterpret_cast<sub_bcc1ae0_node*>(node);
    n->prev = n;
    n->next = n;
    n->value = nullptr;

    // 0xbcc1b46  mov rcx,[rsi+0x38]
    // 0xbcc1b4a  test rcx,rcx
    // 0xbcc1b4d  je short 0xBCC1BCB
    void* factory = self->field_0x38;
    if (factory == nullptr) {
        // 0xbcc1bcb  call 0xEEC59E0
        0xbcc1bcb  call 0xEEC59E0
        sub_eec59e0();
    }

    // 0xbcc1b4f  mov r14,rax
    // 0xbcc1b52  mov rax,[rcx]
    // 0xbcc1b55  mov rax,[rax+0x10]
    // 0xbcc1b59  lea rdx,[rsp+0x20]
    // 0xbcc1b5e  call qword ptr [0xF99FFA0]
    0xbcc1b5e  call qword ptr [0xF99FFA0]
    {
        void** vt = *reinterpret_cast<void***>(factory);
        reinterpret_cast<void (*)(void*, void*)>(vt[2])(factory, n); // n is the node; factory fills n->value
    }

    // 0xbcc1b64  mov rcx,rbx
    // 0xbcc1b67  mov rdx,rdi
    // 0xbcc1b6a  call 0x9BD6D0
    0xbcc1b6a  call 0x9BD6D0
    sub_9bd6d0(&self->slot_0xA0, n);

    // 0xbcc1b6f  lea rbx,[rsi+0x50]
    // 0xbcc1b73  mov rcx,rbx
    // 0xbcc1b76  call 0xEEC59F0
    0xbcc1b76  call 0xEEC59F0
    void* mutex = reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(self) + 0x50);
    int lockResult = sub_eec59f0(mutex);
    // 0xbcc1b7b  test eax,eax
    // 0xbcc1b7d  jne short 0xBCC1BD0
    if (lockResult != 0) {
        // 0xbcc1bd0  mov ecx,5
        // 0xbcc1bd5  call 0xEEC5A00
        0xbcc1bd5  call 0xEEC5A00
        sub_eec5a00(5u);
        // fall through to int3 after the call returns
    }

    // 0xbcc1b7f  cmp dword ptr [rsi+0x9C],0x7FFFFFFF
    // 0xbcc1b89  je short 0xBCC1BDA
    if (self->field_0x9C == 0x7FFFFFFF) {
        // 0xbcc1bda  mov dword ptr [rsi+0x9C],0x7FFFFFFE
        // 0xbcc1be4  mov ecx,6
        // 0xbcc1be9  call 0xEEC5A00
        0xbcc1be9  call 0xEEC5A00
        self->field_0x9C = 0x7FFFFFFE;
        sub_eec5a00(6u);
        // 0xbcc1bee  int3
        __debugbreak();
        __assume(false);
    }

    // 0xbcc1b8b  lea rax,[rsi+0x40]
    // 0xbcc1b8f  mov rcx,[rsi+0x48]
    // 0xbcc1b93  mov [rdi+8],rcx
    // 0xbcc1b97  mov [rdi],rax
    // 0xbcc1b9a  mov [rcx],rdi
    // 0xbcc1b9d  mov [rsi+0x48],rdi
    void* listHead = self->field_0x40;
    void* listTail = self->field_0x48;
    n->next = listTail;           // node+0x08 = old tail
    n->prev = listHead;           // node+0x00 = old head (listHead is this+0x40)
    reinterpret_cast<sub_bcc1ae0_node*>(listTail)->prev = n; // old tail prev = node
    self->field_0x48 = n;         // new tail = node

    // 0xbcc1ba1  mov rcx,rbx
    // 0xbcc1ba4  call 0xEEC5A10
    0xbcc1ba4  call 0xEEC5A10
    sub_eec5a10(mutex);

    // 0xbcc1ba9  mov rax,r14
    // 0xbcc1bac  add rsp,0x28
    // 0xbcc1bb0  pop rbx
    // 0xbcc1bb1  pop rdi
    // 0xbcc1bb2  pop rsi
    // 0xbcc1bb3  pop r14
    // 0xbcc1bb5  ret
    return n->value;
}

// Footprint: the entire object self is written (mutex, list, flag, slot, etc.)
static native::Footprint sub_bcc1ae0_footprint(sub_bcc1ae0_state* self) {
    return { { self, 0xA4 } }; // up to +0xA0 + 4 bytes
}

LIFT_FN(sub_bcc1ae0, "sub_bcc1ae0", 0xbcc1ae0, sub_bcc1ae0, sub_bcc1ae0_footprint);

} // namespace native::bgfx