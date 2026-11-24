// LIFT 0xbc55ea0 size 0x105 1.26.62.01 sub_bc55ea0
#include "client/features/render/native/bgfx/sub_bc55ea0.h"
#include "client/features/render/native/Lift.h"

#include <atomic>
#include <cstddef>
#include <cstdint>

static_assert(offsetof(Slot, raw) == native::kSlotRawOffset, "Slot::raw layout");
static_assert(offsetof(Slot, ref) == native::kSlotRefOffset, "Slot::ref layout");
static_assert(offsetof(RefCounted, strong) == native::kRefStrongOffset, "RefCounted::strong layout");
static_assert(offsetof(RefCounted, weak) == native::kRefWeakOffset, "RefCounted::weak layout");

namespace native {

namespace {

// The RefCounted object's vtable: slot 0 destroys the object (run when the
// strong count reaches 0), slot 1 deallocates it (run when the weak count
// reaches 0). The exe invokes them through the indirect-call gadget at data
// slot 0xF99FFA0 (the gadget at 0xeea6040 is `jmp rax`, rax = the vtable
// entry loaded just before the call). The target is the object's own vtable,
// i.e. a virtual call on the referenced object, not an external function, so
// no boundary wrapper is involved and there is no static callee address.
using VoidFn = void (*)(RefCounted*);

inline VoidFn vtableDestroy(RefCounted* r) {   // rax = r->vptr; rax = [rax]   (vtable[0])
    void** vt = reinterpret_cast<void**>(r->vptr);
    return reinterpret_cast<VoidFn>(vt[0]);
}
inline VoidFn vtableDealloc(RefCounted* r) {  // rax = r->vptr; rax = [rax+8] (vtable[1])
    void** vt = reinterpret_cast<void**>(r->vptr);
    return reinterpret_cast<VoidFn>(vt[1]);
}

} // namespace

// x64 Microsoft ABI: rcx = a (Slot*), rdx = b (Slot*). Returns void.
//
// Swaps the contents of two Slots. Each referenced RefCounted keeps its
// strong/weak count unchanged while ownership moves from one slot to the
// other; the addref/release pairs below keep both objects alive across the
// swap (the destroy/dealloc branches are unreachable for a well-formed pair
// but are reproduced exactly, in the same order, with the same reads/writes).
extern "C" void sub_bc55ea0(Slot* a, Slot* b) {
    // rdi = b
    // 0xbc55ea0..0xbc55ebf
    RefCounted* oldA = a->ref;                         // mov rax,[rcx+8]
    if (oldA != nullptr) {
        oldA->strong.fetch_add(1u, std::memory_order_seq_cst);   // lock inc [oldA+0x8]
    }
    // 0xbc55ebf..0xbc55edb
    void* oldRawA = a->raw;                            // mov r14,[rcx]
    RefCounted* oldB = b->ref;                         // mov rax,[rdi+8]
    if (oldB != nullptr) {
        oldB->strong.fetch_add(1u, std::memory_order_seq_cst);   // lock inc [oldB+0x8]
    }
    // 0xbc55ed9..0xbc55eea
    void* rawB = b->raw;                               // mov rdx,[rdi]
    a->raw = rawB;                                     // mov [rcx],rdx
    a->ref = oldB;                                     // mov [rcx+8],rax
    // 0xbc55eea..0xbc55ef3  release oldA (slot a lets go)
    if (oldA != nullptr) {
        if (oldA->strong.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {   // lock dec [oldA+0x8]
            VoidFn destroy = vtableDestroy(oldA);                    // mov rax,[oldA]; mov rax,[rax]
            // 0xbc55efe  call qword ptr [0xF99FFA0]
            destroy(oldA);                                           // mov rcx,oldA
            if (oldA->weak.fetch_sub(1u, std::memory_order_seq_cst) == 1u) { // lock dec [oldA+0xC]
                VoidFn dealloc = vtableDealloc(oldA);                // mov rax,[oldA]; mov rax,[rax+8]
                // 0xbc55f14  call qword ptr [0xF99FFA0]
                dealloc(oldA);                                       // mov rcx,oldA
            }
        }
    }
    // 0xbc55ef3..0xbc55f1a  re-acquire oldA for slot b
    if (oldA != nullptr) {
        oldA->strong.fetch_add(1u, std::memory_order_seq_cst);   // lock inc [oldA+0x8]
    }
    // 0xbc55f1a..0xbc55f23
    b->raw = oldRawA;                                  // mov [rdi],r14
    RefCounted* oldB2 = b->ref;                        // mov rbx,[rdi+8] (oldB, before overwrite)
    b->ref = oldA;                                     // mov [rdi+8],rsi
    // 0xbc55f23..0xbc55f2e
    // 0xbc55f2e..0xbc55f37  release oldB2
    if (oldB2 != nullptr) {
        if (oldB2->strong.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
            VoidFn destroy = vtableDestroy(oldB2);     // mov rax,[oldB2]; mov rax,[rax]
            // 0xbc55f42  call qword ptr [0xF99FFA0]
            destroy(oldB2);                            // mov rcx,oldB2
            if (oldB2->weak.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
                VoidFn dealloc = vtableDealloc(oldB2); // mov rax,[oldB2]; mov rax,[rax+8]
                // 0xbc55f58  call qword ptr [0xF99FFA0]
                dealloc(oldB2);                        // mov rcx,oldB2
            }
        }
    }
    // 0xbc55f5e..0xbc55f9b  release temp oldA (tail-call dealloc)
    if (oldA != nullptr) {
        if (oldA->strong.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
            VoidFn destroy = vtableDestroy(oldA);      // mov rax,[oldA]; mov rax,[rax]
            // 0xbc55f72  call qword ptr [0xF99FFA0]
            destroy(oldA);                             // mov rcx,oldA
            if (oldA->weak.fetch_sub(1u, std::memory_order_seq_cst) == 1u) { // lock dec [oldA+0xC]
                VoidFn dealloc = vtableDealloc(oldA);  // mov rax,[oldA]; mov rax,[rax+8]
                return dealloc(oldA);                  // mov rcx,oldA; jmp rdx (tail call)
            }
        }
    }
    // 0xbc55f9b..0xbc55fa5
    return;
}

static native::Footprint sub_bc55ea0Footprint(Slot* a, Slot* b) {
    return {{a, sizeof(Slot)}, {b, sizeof(Slot)}};
}

LIFT_FN(sub_bc55ea0, "native::sub_bc55ea0", 0xbc55ea0, sub_bc55ea0, sub_bc55ea0Footprint);

} // namespace native
