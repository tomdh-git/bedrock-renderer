#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/native/Lift.h"

// sub_5aba5c0 = ThreadLocalObject<T>::get (0x5aba5c0, size 0x10f, 1.26.62.01).
//
// Thread-local get-or-create. Returns the current thread's cached value node, or
// allocates a node, constructs the value with the factory, publishes it to TLS and
// appends the node to the owner's circular list.
//
// this (ThreadLocalObject<T>) field offsets touched [V: rdis dis 0x5aba5c0]:
//   +0x38 factory           pointer to std::function-like factory object (void* at +0x38)
//   +0x40 embedded list head node: +0x0 head.next, +0x8 head.prev
//   +0x50 _Mtx mutex        passed to _Mtx_lock / _Mtx_unlock
//   +0x9C u32 init flag     0x7FFFFFFF sentinel
//   +0xA0 u32 TLS slot index
//
// Node layout (0x8C8 bytes) [V: 0x5aba60e..0x5aba621, 0x5aba5e0]:
//   +0x00 prev (void*)
//   +0x08 next (void*)
//   +0x10 T value (0x8B8 bytes)  -> 0x10 + 0x8B8 == 0x8C8
//
// Calls:
//   sub_9bd4a0  (boundary/os)   tlsGet(&self->tlsSlot)             -> node*
//   sub_eea6040 (boundary/vendor, indirect-call thunk via slot 0xF99FFA0)
//                              heap->alloc(0x8C8)                   -> node*
//                              factory->invoke(factory, &valueSlot) -> void
//   sub_9bd6d0  (boundary/os)   tlsSet(&self->tlsSlot, node)       -> void
//   sub_eec59f0 (lift set)      _Mtx_lock(&self->mutex)            -> int (0 success)
//   sub_eec5a10 (lift set)      _Mtx_unlock(&self->mutex)          -> void
//   sub_eec5a00 (lift set)      _Throw_Cpp_error(int)              -> noreturn
//   sub_eec59e0 (lift set)      _Xbad_function_call(void)          -> noreturn
//   0x5aba5fc / 0x5aba63e are indirect calls through data slot 0xF99FFA0 (sub_eea6040)
//
// x64 Microsoft ABI: this in RCX, return RAX = &node->value (void*).

struct sub_5aba5c0Layout {
    static_assert(sizeof(void*) == 8, "sub_5aba5c0: x64 ABI, pointer-sized address space");
    // this (ThreadLocalObject<T>) field offsets
    static constexpr std::size_t kFactoryOffset = 0x38;       // void* factory at +0x38
    static constexpr std::size_t kListHeadOffset = 0x40;      // embedded list head node at +0x40
    static constexpr std::size_t kListPrevOffset = 0x48;      // head.prev (last node) at +0x48
    static constexpr std::size_t kMutexOffset = 0x50;         // _Mtx mutex at +0x50
    static constexpr std::size_t kInitFlagOffset = 0x9C;      // u32 init flag at +0x9C
    static constexpr std::size_t kTLSSlotOffset = 0xA0;       // u32 TLS slot index at +0xA0
    static_assert(kFactoryOffset == 0x38, "sub_5aba5c0: factory at +0x38");
    static_assert(kListHeadOffset == 0x40, "sub_5aba5c0: list head at +0x40");
    static_assert(kListPrevOffset == 0x48, "sub_5aba5c0: list prev at +0x48");
    static_assert(kMutexOffset == 0x50, "sub_5aba5c0: mutex at +0x50");
    static_assert(kInitFlagOffset == 0x9C, "sub_5aba5c0: init flag at +0x9C");
    static_assert(kTLSSlotOffset == 0xA0, "sub_5aba5c0: TLS slot at +0xA0");
    // Node layout
    static constexpr std::size_t kNodeSize = 0x8C8;           // total node size
    static constexpr std::size_t kNodeValueOffset = 0x10;     // T value at +0x10
    static constexpr std::size_t kValueSize = 0x8B8;          // value size
    static constexpr std::size_t kAllocSize = 0x8C8;          // alloc size
    static_assert(kNodeValueOffset + kValueSize == kNodeSize, "sub_5aba5c0: value + size == node size");
    static_assert(kNodeSize == kAllocSize, "sub_5aba5c0: node size == alloc size");
    // Global data RVA read for the heap pointer
    static constexpr std::uintptr_t kRvaHeapPtr = 0x1233E1A8; // [data_1233e1a8] heap object pointer
    // Indirect-call thunk data slot
    static constexpr std::uintptr_t kSlotF99ffa0 = 0xF99FFA0; // data slot holding sub_eea6040
};

namespace native {

// Opaque MSVCP140 C11 mutex; the pointee is never inspected by this forwarder.
struct _Mtx;

// Lift-set callees (already lifted), called through their native symbols.
int sub_eec59f0(struct _Mtx* mtx);            // 0xEEC59F0, _Mtx_lock forwarder (0 = success)
void sub_eec5a10(struct _Mtx* mtx);           // 0xEEC5A10, _Mtx_unlock forwarder
[[noreturn]] void sub_eec5a00(int errorCode); // 0xEEC5A00, _Throw_Cpp_error forwarder
[[noreturn]] void sub_eec59e0(void);          // 0xEEC59E0, _Xbad_function_call forwarder

// Boundary callees (declared at global scope, referenced unqualified from native::).
// sub_9bd4a0 (os): tlsGet(&tlsSlot) -> node*
native::Boundary<void*, void*> sub_9bd4a0("sub_9bd4a0");
// sub_9bd6d0 (os): tlsSet(&tlsSlot, node) -> void (return discarded)
native::Boundary<void*, void*, void*> sub_9bd6d0("sub_9bd6d0");
// sub_9bc830 (alloc): allocator OOM handler(size) -> void (return discarded)
native::Boundary<void*, void*> sub_9bc830("sub_9bc830");
// sub_eea6040 (vendor): indirect-call thunk via data slot 0xF99FFA0(self, arg) -> void*
native::Boundary<void*, void*, std::uintptr_t> sub_eea6040("sub_eea6040");

} // namespace native

// sub_5aba5c0 (0x5aba5c0, 0x10f bytes, 1.26.62.01): this in RCX, returns RAX = &node->value.
void* ThreadLocalObject_get(void* self);
