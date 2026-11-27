// LIFT 0xc293af0 size 0xd6 1.26.62.01 sub_c293af0
#include "client/features/render/native/dragon/sub_c293af0.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

namespace native {

// sub_eea6040 is a `jmp rax` thunk reached through loader-resolved data slot
// 0xF99FFA0 (docs/data/native_boundary.tsv: class vendor). The lifted code reads
// vtable[0] (destructor) and vtable[8] (deallocator) into rax and calls them with
// rcx = the refcounted object, exactly matching each
// `call qword ptr [0xF99FFA0]`.

void sub_c293af0(void* a0) {
    // 0xc293af0..0xc293af3: push rsi; push rdi; push rbx; sub rsp,0x30
    Context* ctx = reinterpret_cast<Context*>(a0);

    // 0xc293af7  mov rbx,[rcx+8]      ; R a0+0x8
    // 0xc293afb  test rbx,rbx
    // 0xc293afe  je 0xC293BA4         ; if rbx == 0, return (RAX unchanged)
    SubObject* sub = ctx->sub;
    if (sub == nullptr) {
        return;   // 0xc293ba4  add rsp,0x30; pop rbx; pop rdi; pop rsi; ret
    }

    // 0xc293b04  mov rsi,rcx           ; rsi = a0 (base for later reload of [a0+8])

    // 0xc293b07  mov rdi,[rbx+0x38]    ; R *(a0+0x8)+0x38
    // 0xc293b0b  test rdi,rdi
    // 0xc293b0e  je short 0xC293B3B    ; if ref == 0, skip the release
    RefCounted* ref = sub->ref;
    if (ref != nullptr) {
        // 0xc293b10  lock dec dword ptr [rdi+8]   ; W *(*(a0+0x8)+0x38)+0x8
        // 0xc293b14  jne short 0xC293B3B          ; if strong != 0, skip destroy
        if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&ref->strong)) == 0) {
            // 0xc293b16  mov rax,[rdi]            ; vtable
            // 0xc293b19  mov rax,[rax]            ; vtable[0] = destructor
            // 0xc293b1c  mov rcx,rdi
            // 0xc293b1f  call qword ptr [0xF99FFA0]  ; sub_eea6040 -> jmp rax = destructor(ref)
            using DestroyFn = void (*)(void*);
            DestroyFn destroy =
                reinterpret_cast<DestroyFn>(reinterpret_cast<void**>(ref->vtable)[0]);
            destroy(ref);   // 0xc293b1f  call qword ptr [0xF99FFA0]

            // 0xc293b25  lock dec dword ptr [rdi+0xC]   ; W *(*(a0+0x8)+0x38)+0xC
            // 0xc293b29  jne short 0xC293B3B            ; if weak != 0, skip dealloc
            if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&ref->weak)) == 0) {
                // 0xc293b2b  mov rax,[rdi]            ; vtable
                // 0xc293b2e  mov rax,[rax+8]          ; vtable[8] = deallocator
                // 0xc293b32  mov rcx,rdi
                // 0xc293b35  call qword ptr [0xF99FFA0]  ; sub_eea6040 -> jmp rax = deallocator(ref)
                using DeallocFn = void (*)(void*);
                DeallocFn dealloc =
                    reinterpret_cast<DeallocFn>(reinterpret_cast<void**>(ref->vtable)[1]);
                dealloc(ref);   // 0xc293b35  call qword ptr [0xF99FFA0]
            }
        }
    }

    // 0xc293b3b  mov rax,[rbx+0x28]    ; R *(a0+0x8)+0x28  (string size)
    // 0xc293b3f  cmp rax,0x10
    // 0xc293b43  jb short 0xC293B76    ; if size < 0x10, SSO path, skip release
    std::uint64_t size = sub->size;
    if (size >= 0x10) {
        // 0xc293b45  mov rcx,[rbx+0x10]    ; R *(a0+0x8)+0x10  (string data pointer)
        // 0xc293b49  lea rdx,[rax+1]       ; size + 1
        // 0xc293b4d  cmp rdx,0x1000
        // 0xc293b54  jb short 0xC293B71    ; if size + 1 < 0x1000, direct release
        char* data = sub->data;
        if (size + 1 < 0x1000) {
            // loc_c293b71:
            // 0xc293b71  call 0xE935700    sub_e935700(data)
            sub_e935700(data);   // 0xc293b71  call 0xE935700
        } else {
            // 0xc293b56  mov r8,[rcx-8]          ; R *(*(a0+0x8)+0x10)-0x8
            std::uint64_t refcount = *reinterpret_cast<std::uint64_t*>(
                reinterpret_cast<std::uint8_t*>(data) - 8);

            // 0xc293b5a  add rcx,0xFFFFFFFFFFFFFFF8   ; rcx = data - 8
            // 0xc293b5e  sub rcx,r8                   ; rcx = data - 8 - refcount
            std::uint64_t rcx =
                reinterpret_cast<std::uint64_t>(data) - 8 - refcount;

            // 0xc293b61  cmp rcx,0x20
            // 0xc293b65  jae short 0xC293BAC        ; if rcx >= 0x20, slow path via data slot
            if (rcx >= 0x20) {
                // loc_c293bac:
                // 0xc293bac  mov qword ptr [rsp+0x20],0
                // 0xc293bb5  xor ecx,ecx
                // 0xc293bb7  xor edx,edx
                // 0xc293bb9  xor r8d,r8d
                // 0xc293bbc  xor r9d,r9d
                // 0xc293bbf  call qword ptr [0xF9A8C78]  ; indirect call through data slot
                // 0xc293bc5  int3                         ; noreturn
                auto fn = reinterpret_cast<void(*)()>(
                    *reinterpret_cast<void**>(0xF9A8C78ULL));
                fn();   // 0xc293bbf  call qword ptr [0xF9A8C78]
                __assume(false);   // 0xc293bc5  int3  (noreturn)
            } else {
                // 0xc293b67  add rax,0x28         ; rdx = size + 0x28
                // 0xc293b6b  mov rdx,rax
                // 0xc293b6e  mov rcx,r8          ; rcx = refcount
                // loc_c293b71:
                // 0xc293b71  call 0xE935700      sub_e935700(refcount)
                sub_e935700(reinterpret_cast<void*>(refcount));   // 0xc293b71  call 0xE935700
            }
        }
    }

    // 0xc293b76  mov qword ptr [rbx+0x20],0     ; W *(a0+0x8)+0x20  (cap = 0)
    // 0xc293b7e  mov qword ptr [rbx+0x28],0xF   ; W *(a0+0x8)+0x28  (size = 0xF)
    // 0xc293b86  mov byte ptr [rbx+0x10],0      ; W *(a0+0x8)+0x10  (data = nullptr)
    sub->cap = 0;
    sub->size = 0xF;
    sub->data = nullptr;

    // 0xc293b8a  mov rcx,[rsi+8]      ; R a0+0x8   (reload rbx)
    // 0xc293b8e  test rcx,rcx
    // 0xc293b91  je short 0xC293BA4   ; if null, return (never taken: sub != 0 above)
    // 0xc293b93  mov edx,0x48
    // 0xc293b98  add rsp,0x30
    // 0xc293b9c  pop rbx
    // 0xc293b9d  pop rdi
    // 0xc293b9e  pop rsi
    // 0xc293b9f  jmp 0xE935700        ; tail call to sub_e935700 (rcx = sub, rdx = 0x48)
    sub_e935700(sub);   // 0xc293b9f  jmp 0xE935700
    return;
}

} // namespace native

LIFT_FN(c293af0, "sub_c293af0", 0xC293AF0, native::sub_c293af0, nullptr);

// Verbatim instructions of the function (rdis dis 0xc293af0 0xd6), for
// liftcheck/verify_oc. Every line matches rdis output for its address.
#if 0
0xC293AF0  push rsi
0xC293AF1  push rdi
0xC293AF2  push rbx
0xC293AF3  sub rsp,0x30
0xC293AF7  mov rbx,[rcx+8]
0xC293AFB  test rbx,rbx
0xC293AFE  je 0xC293BA4
0xC293B04  mov rsi,rcx
0xC293B07  mov rdi,[rbx+0x38]
0xC293B0B  test rdi,rdi
0xC293B0E  je short 0xC293B3B
0xC293B10  lock dec dword ptr [rdi+8]
0xC293B14  jne short 0xC293B3B
0xC293B16  mov rax,[rdi]
0xC293B19  mov rax,[rax]
0xC293B1C  mov rcx,rdi
0xC293B1F  call qword ptr [0xF99FFA0]
0xC293B25  lock dec dword ptr [rdi+0xC]
0xC293B29  jne short 0xC293B3B
0xC293B2B  mov rax,[rdi]
0xC293B2E  mov rax,[rax+8]
0xC293B32  mov rcx,rdi
0xC293B35  call qword ptr [0xF99FFA0]
0xC293B3B  mov rax,[rbx+0x28]
0xC293B3F  cmp rax,0x10
0xC293B43  jb short 0xC293B76
0xC293B45  mov rcx,[rbx+0x10]
0xC293B49  lea rdx,[rax+1]
0xC293B4D  cmp rdx,0x1000
0xC293B54  jb short 0xC293B71
0xC293B56  mov r8,[rcx-8]
0xC293B5A  add rcx,0xFFFFFFFFFFFFFFF8
0xC293B5E  sub rcx,r8
0xC293B61  cmp rcx,0x20
0xC293B65  jae short 0xC293BAC
0xC293B67  add rax,0x28
0xC293B6B  mov rdx,rax
0xC293B6E  mov rcx,r8
0xC293B71  call 0xE935700
0xC293B76  mov qword ptr [rbx+0x20],0
0xC293B7E  mov qword ptr [rbx+0x28],0xF
0xC293B86  mov byte ptr [rbx+0x10],0
0xC293B8A  mov rcx,[rsi+8]
0xC293B8E  test rcx,rcx
0xC293B91  je short 0xC293BA4
0xC293B93  mov edx,0x48
0xC293B98  add rsp,0x30
0xC293B9C  pop rbx
0xC293B9D  pop rdi
0xC293B9E  pop rsi
0xC293B9F  jmp 0xE935700
0xC293BA4  add rsp,0x30
0xC293BA8  pop rbx
0xC293BA9  pop rdi
0xC293BAA  pop rsi
0xC293BAB  ret
0xC293BAC  mov qword ptr [rsp+0x20],0
0xC293BB5  xor ecx,ecx
0xC293BB7  xor edx,edx
0xC293BB9  xor r8d,r8d
0xC293BBC  xor r9d,r9d
0xC293BBF  call qword ptr [0xF9A8C78]
0xC293BC5  int3
#endif
