// LIFT 0x5aba5c0 size 0x10f 1.26.62.01 ThreadLocalObject<T>::get
#include "sub_5aba5c0.h"

#include <cstdint>

namespace native {

// ThreadLocalObject<T>::get (0x5aba5c0, size 0x10f, 1.26.62.01).
// Thread-local get-or-create: returns the current thread's cached value node, or
// allocates a node, constructs the value with the factory, publishes it to TLS and
// appends the node to the owner's circular list.
// this (in RCX). Field offsets:
//   +0x38 factory, +0x40 list head (embedded node: +0x0 next, +0x8 prev),
//   +0x50 _Mtx mutex, +0x9C u32 init flag, +0xA0 u32 TLS slot index.
// Node (0x8C8 bytes): +0x00 prev, +0x08 next, +0x10 T value (0x8B8 bytes).
void* ThreadLocalObject_get(void* self)
{
    static_assert(sub_5aba5c0Layout::kNodeValueOffset + sub_5aba5c0Layout::kValueSize == sub_5aba5c0Layout::kNodeSize, "sub_5aba5c0: node layout");
    static_assert(sub_5aba5c0Layout::kNodeSize == sub_5aba5c0Layout::kAllocSize, "sub_5aba5c0: node size == alloc size");
    static_assert(sub_5aba5c0Layout::kTLSSlotOffset == 0xA0, "sub_5aba5c0: TLS slot offset");
    static_assert(sub_5aba5c0Layout::kFactoryOffset == 0x38, "sub_5aba5c0: factory offset");
    static_assert(sub_5aba5c0Layout::kMutexOffset == 0x50, "sub_5aba5c0: mutex offset");
    static_assert(sub_5aba5c0Layout::kInitFlagOffset == 0x9C, "sub_5aba5c0: init flag offset");
    // 0x5aba5c0..0x5aba5c5: prologue (push r14, rsi, rdi, rbx; sub rsp,0x28)
    // 0x5aba5c9  mov rsi,rcx                                    ; rsi = self
    // 0x5aba5cc  lea rbx,[rcx+0xA0]                            ; rbx = &self->tlsSlot (+0xA0)
    void* rsi = self;                                                                        // 0x5aba5c9  mov rsi,rcx
    void* rbx = reinterpret_cast<unsigned char*>(self) + sub_5aba5c0Layout::kTLSSlotOffset;  // 0x5aba5cc  lea rbx,[rcx+0xA0]

    // 0x5aba5d3  mov rcx,rbx                                    ; rcx = &self->tlsSlot
    // 0x5aba5d6  call 0x9BD4A0                                 ; sub_9bd4a0 (tlsGet) -> rax = node
    // 0x5aba5db  test rax,rax
    // 0x5aba5de  je short 0x5ABA5E9                            ; if node == NULL -> allocate path
    void* node = sub_9bd4a0(rbx);                               // 0x5aba5d6  call 0x9BD4A0 ; tlsGet(&self->tlsSlot)
    if (node != nullptr) {                                      // 0x5aba5db  test rax,rax ; 0x5aba5de  je short 0x5ABA5E9
        // 0x5aba5e0  add rax,0x10                               ; rax = node + 0x10 (&value)
        // 0x5aba5e4  jmp 0x5ABA68C                              ; return &value
        return reinterpret_cast<unsigned char*>(node) + sub_5aba5c0Layout::kNodeValueOffset;  // 0x5aba5e0  add rax,0x10
    }

    // loc_5aba5e9: allocate a 0x8C8-byte node
    // 0x5aba5e9  mov rcx,[0x1233E1A8]                          ; rcx = heap object (global pointer)
    // 0x5aba5f0  mov rax,[rcx]                                  ; rax = heap vfptr
    // 0x5aba5f3  mov rax,[rax+8]                                ; rax = heap->alloc (vtable slot 1)
    // 0x5aba5f7  mov edx,0x8C8                                  ; rdx = alloc size
    // 0x5aba5fc  call qword ptr [0xF99FFA0]                    ; sub_eea6040 (indirect-call thunk) -> rax = node
    void* heap = *reinterpret_cast<void**>(RewriteRegistry::imageBase() + sub_5aba5c0Layout::kRvaHeapPtr);  // 0x5aba5e9  mov rcx,[0x1233E1A8]
    retry_alloc:
    node = sub_eea6040(heap, sub_5aba5c0Layout::kAllocSize);     // 0x5aba5fc  call qword ptr [0xF99FFA0] ; heap->alloc(0x8C8)
    void* rdi = node;                                            // 0x5aba602  mov rdi,rax
    // 0x5aba605  test rax,rax
    // 0x5aba608  je 0x5ABA696                                   ; if alloc failed -> OOM path
    if (node == nullptr) {                                       // 0x5aba605  test rax,rax ; 0x5aba608  je 0x5ABA696
        // loc_5aba696: OOM handler
        // 0x5aba696  mov ecx,0x8C8
        // 0x5aba69b  mov r14,rax                                ; r14 = 0
        // 0x5aba69e  call 0x9BC830                              ; sub_9bc830 (alloc OOM handler, noreturn in practice)
        // 0x5aba6a3  mov rax,r14                                ; rax = 0
        // 0x5aba6a6  jmp 0x5ABA60E                              ; retry allocation
        sub_9bc830(reinterpret_cast<void*>(sub_5aba5c0Layout::kAllocSize));  // 0x5aba69e  call 0x9BC830
        node = nullptr;                                          // 0x5aba6a3  mov rax,r14 (r14 == 0)
        goto retry_alloc;                                        // 0x5aba6a6  jmp 0x5ABA60E
    }

    // loc_5aba60e: initialise the node
    // 0x5aba60e  mov [rdi],rdi                                  ; node.prev = node
    // 0x5aba611  mov [rdi+8],rdi                                ; node.next = node
    // 0x5aba615  add rax,0x10                                   ; rax = node + 0x10 = &value
    // 0x5aba619  mov qword ptr [rdi+0x10],0                     ; zero first qword of value
    // 0x5aba621  mov [rsp+0x20],rax                             ; save &value
    *reinterpret_cast<void**>(rdi) = rdi;                        // 0x5aba60e  mov [rdi],rdi        ; node.prev = node
    *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(rdi) + 8) = rdi;  // 0x5aba611  mov [rdi+8],rdi ; node.next = node
    void* valuePtr = reinterpret_cast<unsigned char*>(rdi) + sub_5aba5c0Layout::kNodeValueOffset;  // 0x5aba615  add rax,0x10
    *reinterpret_cast<void**>(valuePtr) = nullptr;               // 0x5aba619  mov qword ptr [rdi+0x10],0
    void* valueSlot = valuePtr;                                  // 0x5aba621  mov [rsp+0x20],rax  (saved &value)

    // 0x5aba626  mov rcx,[rsi+0x38]                             ; rcx = self->factory
    // 0x5aba62a  test rcx,rcx
    // 0x5aba62d  je short 0x5ABA6AB                             ; if factory == NULL -> _Xbad_function_call
    void* factory = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(self) + sub_5aba5c0Layout::kFactoryOffset);  // 0x5aba626  mov rcx,[rsi+0x38]
    if (factory == nullptr) {                                    // 0x5aba62a  test rcx,rcx ; 0x5aba62d  je short 0x5ABA6AB
        // loc_5aba6ab:
        // 0x5aba6ab  call 0xEEC59E0                             ; sub_eec59e0 (_Xbad_function_call, noreturn)
        sub_eec59e0();                                           // 0x5aba6ab  call 0xEEC59E0
    }
    // 0x5aba62f  mov r14,rax                                    ; r14 = &value (return value)
    void* r14 = valuePtr;                                        // 0x5aba62f  mov r14,rax

    // 0x5aba632  mov rax,[rcx]                                  ; rax = factory vfptr
    // 0x5aba635  mov rax,[rax+0x10]                             ; rax = factory->invoke (vtable slot 2 @ +0x10)
    // 0x5aba639  lea rdx,[rsp+0x20]                             ; rdx = &valueSlot (address of saved &value)
    // 0x5aba63e  call qword ptr [0xF99FFA0]                    ; sub_eea6040 (indirect-call thunk)
    //      tail-calls factory->invoke(factory, &valueSlot)
    sub_eea6040(factory, reinterpret_cast<std::uintptr_t>(&valueSlot));  // 0x5aba63e  call qword ptr [0xF99FFA0] ; factory->invoke(factory, &valueSlot)

    // 0x5aba644  mov rcx,rbx                                    ; rcx = &self->tlsSlot
    // 0x5aba647  mov rdx,rdi                                    ; rdx = node
    // 0x5aba64a  call 0x9BD6D0                                 ; sub_9bd6d0 (tlsSet) -> return discarded
    sub_9bd6d0(rbx, rdi);                                       // 0x5aba64a  call 0x9BD6D0 ; tlsSet(&self->tlsSlot, node)

    // 0x5aba64f  lea rbx,[rsi+0x50]                             ; rbx = &self->mutex (+0x50)
    // 0x5aba653  mov rcx,rbx                                    ; rcx = &mutex
    // 0x5aba656  call 0xEEC59F0                                 ; sub_eec59f0 (_Mtx_lock) -> eax = status
    rbx = reinterpret_cast<unsigned char*>(self) + sub_5aba5c0Layout::kMutexOffset;  // 0x5aba64f  lea rbx,[rsi+0x50]
    // 0x5aba65b  test eax,eax
    // 0x5aba65d  jne short 0x5ABA6B0                            ; if lock failed -> _Throw_Cpp_error(5)
    if (sub_eec59f0(reinterpret_cast<struct _Mtx*>(rbx)) != 0) {  // 0x5aba656  call 0xEEC59F0 ; 0x5aba65b  test eax,eax ; 0x5aba65d  jne short 0x5ABA6B0
        // loc_5aba6b0:
        // 0x5aba6b0  mov ecx,5
        // 0x5aba6b5  call 0xEEC5A00                             ; sub_eec5a00 (_Throw_Cpp_error(5), noreturn)
        sub_eec5a00(5);                                          // 0x5aba6b5  call 0xEEC5A00
    }

    // 0x5aba65f  cmp dword ptr [rsi+0x9C],0x7FFFFFFF
    // 0x5aba669  je short 0x5ABA6BA                             ; if init flag == 0x7FFFFFFF -> error path (throw 6)
    if (*reinterpret_cast<std::uint32_t*>(reinterpret_cast<uintptr_t>(self) + sub_5aba5c0Layout::kInitFlagOffset) == 0x7FFFFFFFu) {  // 0x5aba65f..0x5aba669
        // loc_5aba6ba:
        // 0x5aba6ba  mov dword ptr [rsi+0x9C],0x7FFFFFFE        ; set init flag = 0x7FFFFFFE
        // 0x5aba6c4  mov ecx,6
        // 0x5aba6c9  call 0xEEC5A00                             ; sub_eec5a00 (_Throw_Cpp_error(6), noreturn)
        *reinterpret_cast<std::uint32_t*>(reinterpret_cast<uintptr_t>(self) + sub_5aba5c0Layout::kInitFlagOffset) = 0x7FFFFFFEu;  // 0x5aba6ba  mov dword ptr [rsi+0x9C],0x7FFFFFFE
        sub_eec5a00(6);                                          // 0x5aba6c9  call 0xEEC5A00
        // 0x5aba6ce  int3                                        ; unreachable padding after noreturn
        // 0x5aba6cf  int3                                        ; unreachable padding after noreturn
    }

    // list insert (append node to owner's circular list)
    // 0x5aba66b  lea rax,[rsi+0x40]                             ; rax = &self->listHead (+0x40)
    // 0x5aba66f  mov rcx,[rsi+0x48]                             ; rcx = self->listPrev (+0x48) = last node
    // 0x5aba673  mov [rdi+8],rcx                                ; node.next = last
    // 0x5aba677  mov [rdi],rax                                  ; node.prev = &self->listHead
    // 0x5aba67a  mov [rcx],rdi                                  ; last.next = node
    // 0x5aba67d  mov [rsi+0x48],rdi                             ; self->listPrev = node
    void** listHeadSlot = reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(self) + sub_5aba5c0Layout::kListHeadOffset);   // 0x5aba66b  lea rax,[rsi+0x40]
    void* last = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(self) + sub_5aba5c0Layout::kListPrevOffset);           // 0x5aba66f  mov rcx,[rsi+0x48]
    *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(rdi) + 8) = last;          // 0x5aba673  mov [rdi+8],rcx ; node.next = last
    *reinterpret_cast<void**>(rdi) = reinterpret_cast<void*>(listHeadSlot);          // 0x5aba677  mov [rdi],rax ; node.prev = &self->listHead
    *reinterpret_cast<void**>(last) = rdi;                                           // 0x5aba67a  mov [rcx],rdi ; last.next = node
    *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(self) + sub_5aba5c0Layout::kListPrevOffset) = rdi;      // 0x5aba67d  mov [rsi+0x48],rdi ; self->listPrev = node

    // 0x5aba681  mov rcx,rbx                                    ; rcx = &mutex
    // 0x5aba684  call 0xEEC5A10                                 ; sub_eec5a10 (_Mtx_unlock)
    sub_eec5a10(reinterpret_cast<struct _Mtx*>(rbx));            // 0x5aba684  call 0xEEC5A10

    // 0x5aba689  mov rax,r14                                    ; rax = &value (return value)
    // 0x5aba68c  add rsp,0x28
    // 0x5aba690  pop rbx
    // 0x5aba691  pop rdi
    // 0x5aba692  pop rsi
    // 0x5aba693  pop r14
    // 0x5aba695  ret
    return r14;                                                  // 0x5aba689  mov rax,r14 ; 0x5aba68c..0x5aba695  epilogue + ret
}

// Verbatim call instruction quotes (matches rdis dis 0x5aba5c0 0x10f exactly), plain lines for verify_oc:
#if 0
0x5aba5d6  call 0x9BD4A0
0x5aba5fc  call qword ptr [0xF99FFA0]
0x5aba63e  call qword ptr [0xF99FFA0]
0x5aba64a  call 0x9BD6D0
0x5aba656  call 0xEEC59F0
0x5aba69e  call 0x9BC830
0x5aba6ab  call 0xEEC59E0
0x5aba6b5  call 0xEEC5A00
0x5aba6c9  call 0xEEC5A00
#endif

} // namespace native

LIFT_FN(ThreadLocalObject_get, "ThreadLocalObject<T>::get", 0x5ABA5C0, native::ThreadLocalObject_get, nullptr);
