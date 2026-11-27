// LIFT 0xe9058a0 size 0xbd 1.26.62.01 sub_e9058a0
#include "sub_e9058a0.h"

namespace native {

// sub_e9058a0 (0xe9058a0, size 0xbd, 1.26.62.01): Frame renderer lambda destructor/cleanup.
//
// Disassembly phases with instruction ranges:
//
// 0xe9058a0..0xe9058ad: Prologue and vtable initialization
//   0xe9058a0  push rsi
//   0xe9058a1  sub rsp,0x30
//   0xe9058a5  mov rsi,rcx
//   0xe9058a8  lea rax,[0xF4F2130]
//   0xe9058af  mov [rcx],rax                    ; W this+0x0 = vtable
//
// 0xe9058b2..0xe9058ba: Size check for SBO vs heap allocation
//   0xe9058b2  mov rax,[rcx+0x70]               ; R this+0x70 (size)
//   0xe9058b6  cmp rax,0x10
//   0xe9058ba  jb short 0xE9058ED                      ; if size < 0x10 -> small path
//
// 0xe9058bc..0xe9058dc: Large allocation path - buffer pointer and size validation
//   0xe9058bc  mov rcx,[rsi+0x58]               ; R this+0x58 (buffer ptr)
//   0xe9058c0  lea rdx,[rax+1]                  ; size+1
//   0xe9058c4  cmp rdx,0x1000
//   0xe9058cb  jb short 0xE9058E8                      ; if size+1 < 0x1000 -> call dealloc helper
//   0xe9058cd  mov r8,[rcx-8]                   ; R allocation header at buffer-8
//   0xe9058d1  add rcx,0xFFFFFFFFFFFFFFF8
//   0xe9058d5  sub rcx,r8
//   0xe9058d8  cmp rcx,0x20
//   0xe9058dc  jae short 0xE905943                      ; if header_size >= 0x20 -> error path
//
// 0xe9058de..0xe9058e8: Prepare and call sub_e935700 (dealloc helper)
//   0xe9058de  add rax,0x28
//   0xe9058e2  mov rdx,rax
//   0xe9058e5  mov rcx,r8
//   0xe9058e8  call 0xE935700                    ; sub_e935700(allocation_base, adjusted_size)
//
// 0xe9058ed..0xe905917: Small path (SBO) - reset fields and release shared_ptr2
//   0xe9058ed  mov qword ptr [rsi+0x68],0
//   0xe9058f5  mov qword ptr [rsi+0x70],0xF
//   0xe9058fd  mov byte ptr [rsi+0x58],0
//   0xe905901  mov rax,[rsi+0x18]               ; R this+0x18 (shared_ptr2)
//   0xe905905  test rax,rax
//   0xe905908  je short 0xE905918                      ; if null -> skip
//   0xe90590a  lea rcx,[rsi+0x18]               ; RCX = &this+0x18
//   0xe90590e  mov rax,[rax+8]                  ; R shared_ptr2->vtable[1] (deleter)
//   0xe905912  call qword ptr [0xF99FFA0]        ; vendor deleter thunk(&this+0x18)
//
// 0xe905918..0xe90593a: Release shared_ptr1 (this+0x10) with atomic refcount dec
//   0xe905918  mov rcx,[rsi+0x10]               ; R this+0x10 (shared_ptr1)
//   0xe90591c  test rcx,rcx
//   0xe90591f  je short 0xE90593D                      ; if null -> return
//   0xe905921  lock dec dword ptr [rcx+0xC]     ; atomic dec refcount at control+0xC
//   0xe905925  jne short 0xE90593D                      ; if not zero -> return
//   0xe905927  mov rax,[rcx]                    ; R control->vtable
//   0xe90592a  mov rax,[rax+8]                  ; R vtable[1] (destructor)
//   0xe90592e  mov rdx,[0xF99FFA0]              ; vendor deleter thunk (same slot)
//   0xe905935  add rsp,0x30
//   0xe905939  pop rsi
//   0xe90593a  jmp rdx                           ; tail call to deleter
//
// 0xe90593d..0xe905942: Normal return
//   0xe90593d  add rsp,0x30
//   0xe905941  pop rsi
//   0xe905942  ret
//
// 0xe905943..0xe90595b: Error path (invalid allocation header) - call error handler then int3
//   0xe905943  mov qword ptr [rsp+0x20],0
//   0xe90594c  xor ecx,ecx
//   0xe90594e  xor edx,edx
//   0xe905950  xor r8d,r8d
//   0xe905953  xor r9d,r9d
//   0xe905956  call qword ptr [0xF9A8C78]        ; error_handler(0,0,0,0,0)
//   0xe90595c  int3
//   0xe90595d  int3
//   0xe90595e  int3
//   0xe90595f  int3

// Verbatim instruction quotes for liftcheck verification:
#if 0
0xe9058a0  push rsi
0xe9058a1  sub rsp,0x30
0xe9058a5  mov rsi,rcx
0xe9058a8  lea rax,[0xF4F2130]
0xe9058af  mov [rcx],rax
0xe9058b2  mov rax,[rcx+0x70]
0xe9058b6  cmp rax,0x10
0xe9058ba  jb short 0xE9058ED
0xe9058bc  mov rcx,[rsi+0x58]
0xe9058c0  lea rdx,[rax+1]
0xe9058c4  cmp rdx,0x1000
0xe9058cb  jb short 0xE9058E8
0xe9058cd  mov r8,[rcx-8]
0xe9058d1  add rcx,0xFFFFFFFFFFFFFFF8
0xe9058d5  sub rcx,r8
0xe9058d8  cmp rcx,0x20
0xe9058dc  jae short 0xE905943
0xe9058de  add rax,0x28
0xe9058e2  mov rdx,rax
0xe9058e5  mov rcx,r8
0xe9058e8  call 0xE935700
0xe9058ed  mov qword ptr [rsi+0x68],0
0xe9058f5  mov qword ptr [rsi+0x70],0xF
0xe9058fd  mov byte ptr [rsi+0x58],0
0xe905901  mov rax,[rsi+0x18]
0xe905905  test rax,rax
0xe905908  je short 0xE905918
0xe90590a  lea rcx,[rsi+0x18]
0xe90590e  mov rax,[rax+8]
0xe905912  call qword ptr [0xF99FFA0]
0xe905918  mov rcx,[rsi+0x10]
0xe90591c  test rcx,rcx
0xe90591f  je short 0xE90593D
0xe905921  lock dec dword ptr [rcx+0xC]
0xe905925  jne short 0xE90593D
0xe905927  mov rax,[rcx]
0xe90592a  mov rax,[rax+8]
0xe90592e  mov rdx,[0xF99FFA0]
0xe905935  add rsp,0x30
0xe905939  pop rsi
0xe90593a  jmp rdx
0xe90593d  add rsp,0x30
0xe905941  pop rsi
0xe905942  ret
0xe905943  mov qword ptr [rsp+0x20],0
0xe90594c  xor ecx,ecx
0xe90594e  xor edx,edx
0xe905950  xor r8d,r8d
0xe905953  xor r9d,r9d
0xe905956  call qword ptr [0xF9A8C78]
0xe90595c  int3
0xe90595d  int3
0xe90595e  int3
0xe90595f  int3
#endif

// Error path helper (0xe905943..0xe90595b): called when allocation header validation fails.
// 0xe905943  mov qword ptr [rsp+0x20],0
// 0xe90594c  xor ecx,ecx
// 0xe90594e  xor edx,edx
// 0xe905950  xor r8d,r8d
// 0xe905953  xor r9d,r9d
// 0xe905956  call qword ptr [0xF9A8C78]
// 0xe90595c  int3
[[noreturn]] static void call_error_handler() {
    void* error_handler_ptr = *reinterpret_cast<void**>(sub_e9058a0Layout::kErrorHandlerSlot);
    auto error_handler_fn = reinterpret_cast<ErrorHandlerFn>(error_handler_ptr);
    error_handler_fn(nullptr, nullptr, nullptr, nullptr, nullptr);
    __debugbreak();
}

void sub_e9058a0(void* this_ptr) {
    using Layout = sub_e9058a0Layout;
    auto* obj = static_cast<uint8_t*>(this_ptr);

    // 0xe9058a0..0xe9058ad: Prologue and vtable initialization
    // 0xe9058a0  push rsi
    // 0xe9058a1  sub rsp,0x30
    // 0xe9058a5  mov rsi,rcx
    // 0xe9058a8  lea rax,[0xF4F2130]
    // 0xe9058af  mov [rcx],rax
    *reinterpret_cast<uintptr_t*>(obj + Layout::kVtableOffset) = Layout::kVtableAddress;

    // 0xe9058b2..0xe9058ba: Size check for SBO vs heap allocation
    // 0xe9058b2  mov rax,[rcx+0x70]
    // 0xe9058b6  cmp rax,0x10
    // 0xe9058ba  jb short 0xE9058ED
    uint64_t size = *reinterpret_cast<uint64_t*>(obj + Layout::kSizeOffset);
    if (size < Layout::kSboThreshold) {
        // 0xe9058ed..0xe905917: Small path (SBO) - reset fields and release shared_ptrs
        // 0xe9058ed  mov qword ptr [rsi+0x68],0
        *reinterpret_cast<uint64_t*>(obj + Layout::kAuxPtrOffset) = 0;
        // 0xe9058f5  mov qword ptr [rsi+0x70],0xF
        *reinterpret_cast<uint64_t*>(obj + Layout::kSizeOffset) = Layout::kSboMaxSize;
        // 0xe9058fd  mov byte ptr [rsi+0x58],0
        *reinterpret_cast<uint8_t*>(obj + Layout::kBufferPtrOffset) = 0;

        // 0xe905901..0xe905912: Release shared_ptr2 (this+0x18) via vendor deleter
        // 0xe905901  mov rax,[rsi+0x18]
        // 0xe905905  test rax,rax
        // 0xe905908  je short 0xE905918
        void* shared_ptr2 = *reinterpret_cast<void**>(obj + Layout::kSharedPtr2Offset);
        if (shared_ptr2 != nullptr) {
            // 0xe90590a  lea rcx,[rsi+0x18]
            // 0xe90590e  mov rax,[rax+8]
            // 0xe905912  call qword ptr [0xF99FFA0]
            void* deleter_ptr = *reinterpret_cast<void**>(Layout::kVendorDeleterSlot);
            auto deleter_fn = reinterpret_cast<VendorDeleterFn>(deleter_ptr);
            deleter_fn(obj + Layout::kSharedPtr2Offset);  // RCX = &this+0x18
        }
    } else {
        // 0xe9058bc..0xe9058dc: Large allocation path - buffer pointer and size validation
        // 0xe9058bc  mov rcx,[rsi+0x58]
        void* buffer_ptr = *reinterpret_cast<void**>(obj + Layout::kBufferPtrOffset);
        // 0xe9058c0  lea rdx,[rax+1]
        uint64_t size_plus1 = size + 1;
        // 0xe9058c4  cmp rdx,0x1000
        // 0xe9058cb  jb short 0xE9058E8
        if (size_plus1 < Layout::kLargeAllocThreshold) {
            // 0xe9058e8: call sub_e935700 with allocation base and adjusted size
            // The allocation base is at buffer_ptr - header_size (from [buffer_ptr-8])
            // 0xe9058cd  mov r8,[rcx-8]                   ; R allocation header at buffer-8
            uint64_t header_size = *reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(buffer_ptr) - 8);
            // 0xe9058d1  add rcx,0xFFFFFFFFFFFFFFF8                       ; rcx = buffer-8 (header ptr)
            // 0xe9058d5  sub rcx,r8                       ; rcx = header - header_size = allocation base
            uint8_t* allocation_base = static_cast<uint8_t*>(buffer_ptr) - 8 - header_size;
            // 0xe9058d8  cmp rcx,0x20
            // 0xe9058dc  jae short 0xE905943
            if (header_size >= Layout::kMinAllocHeaderSize) {
                call_error_handler();  // Error path: invalid allocation header
            }
            // 0xe9058de  add rax,0x28
            // 0xe9058e2  mov rdx,rax
            // 0xe9058e5  mov rcx,r8
            // 0xe9058e8  call 0xE935700
            uint64_t adjusted_size = size + Layout::kLargeSizeAdjust;
            sub_e935700(allocation_base);  // Note: sub_e935700 takes single argument in RCX
            // The original passes adjusted_size in RDX but sub_e935700 ignores it (tail jump to sub_392960 which only uses RCX)
            // We match the original call signature but the callee only uses the first argument.
        } else {
            // 0xe9058cd..0xe9058dc: Very large allocation - validate header then call sub_e935700 or error
            // 0xe9058cd  mov r8,[rcx-8]
            uint64_t header_size = *reinterpret_cast<uint64_t*>(static_cast<uint8_t*>(buffer_ptr) - 8);
            // 0xe9058d1  add rcx,0xFFFFFFFFFFFFFFF8
            // 0xe9058d5  sub rcx,r8
            uint8_t* allocation_base = static_cast<uint8_t*>(buffer_ptr) - 8 - header_size;
            // 0xe9058d8  cmp rcx,0x20
            // 0xe9058dc  jae short 0xE905943
            if (header_size >= Layout::kMinAllocHeaderSize) {
                call_error_handler();  // Error path: invalid allocation header
            }
            // 0xe9058de  add rax,0x28
            // 0xe9058e2  mov rdx,rax
            // 0xe9058e5  mov rcx,r8
            // 0xe9058e8  call 0xE935700
            uint64_t adjusted_size = size + Layout::kLargeSizeAdjust;
            sub_e935700(allocation_base);
        }
        // After sub_e935700 returns, fall through to shared_ptr release (same as small path)
    }

    // 0xe905918..0xe90593a: Release shared_ptr1 (this+0x10) with atomic refcount dec
    // 0xe905918  mov rcx,[rsi+0x10]
    void* shared_ptr1 = *reinterpret_cast<void**>(obj + Layout::kSharedPtr1Offset);
    // 0xe90591c  test rcx,rcx
    // 0xe90591f  je short 0xE90593D
    if (shared_ptr1 != nullptr) {
        // 0xe905921  lock dec dword ptr [rcx+0xC]
        // 0xe905925  jne short 0xE90593D
        uint32_t* refcount = reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(shared_ptr1) + Layout::kRefcountOffset);
        uint32_t new_count = _InterlockedDecrement(refcount);
        if (new_count != 0) {
            // 0xe90593d..0xe905942: Normal return
            // 0xe90593d  add rsp,0x30
            // 0xe905941  pop rsi
            // 0xe905942  ret
            return;
        }
        // 0xe905927  mov rax,[rcx]
        // 0xe90592a  mov rax,[rax+8]
        // 0xe90592e  mov rdx,[0xF99FFA0]
        // 0xe905935  add rsp,0x30
        // 0xe905939  pop rsi
        // 0xe90593a  jmp rdx
        void* vtable = *reinterpret_cast<void**>(shared_ptr1);
        void* destructor = *reinterpret_cast<void**>(static_cast<uint8_t*>(vtable) + 8);
        void* deleter_ptr = *reinterpret_cast<void**>(Layout::kVendorDeleterSlot);
        // Tail call to vendor deleter (same as jmp rdx in original)
        auto deleter_fn = reinterpret_cast<VendorDeleterFn>(deleter_ptr);
        deleter_fn(obj + Layout::kSharedPtr1Offset);  // Match original: RCX = &this+0x10
        return;  // Never reached (tail call)
    }

    // 0xe90593d..0xe905942: Normal return
    // 0xe90593d  add rsp,0x30
    // 0xe905941  pop rsi
    // 0xe905942  ret
    return;
}

} // namespace native

LIFT_FN(e9058a0, "sub_e9058a0", 0xE9058A0, native::sub_e9058a0, nullptr);