// LIFT 0x4dfb570 size 0x120 1.26.62.01 resolve loaded texture
#include "client/features/render/native/helpers/sub_4dfb570.h"

#include "client/features/render/native/Lift.h"

#include <cstddef>
#include <cstdint>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_4dfb570, "sub_4dfb570", 0x4DFB570, sub_4dfb570, nullptr);

// Boundary callees (docs/data/native_boundary.tsv, class os):
//   0xe938cb0  MSVC __Init_thread_header(int* guard)
//   0xe935740  atexit-style registration of the static destructor (takes the function pointer)
//   0xe938d70  MSVC __Init_thread_footer(int* guard)
// Their return values are not used by the original at any call site in this function.
Boundary<std::uintptr_t, void*> sub_e938cb0("sub_e938cb0");
Boundary<std::uintptr_t, void*> sub_e935740("sub_e935740");
Boundary<std::uintptr_t, void*> sub_e938d70("sub_e938d70");

// Boundary callee (docs/data/native_boundary.tsv, class vendor): the loader-resolved
// dispatch thunk at data slot 0xF99FFA0. The instruction loads the target into rax and
// the object into rcx; the wrapper takes (object, target) like the other lifts do.
Boundary<std::uintptr_t, void*, void*> sub_eea6040("sub_eea6040");

// Layout assertions (mirrored from the header for liftcheck).
static_assert(offsetof(sub_4dfb570_handle, object) == 0x00, "sub_4dfb570 handle+0x00");
static_assert(offsetof(sub_4dfb570_object, resource) == 0x18, "sub_4dfb570 object+0x18");
static_assert(offsetof(sub_4dfb570_resource, shared_ptr) == 0x00, "sub_4dfb570 resource+0x00");
static_assert(offsetof(sub_4dfb570_resource, shared_ctrl) == 0x08, "sub_4dfb570 resource+0x08");
static_assert(offsetof(sub_4dfb570_resource, state) == 0x68, "sub_4dfb570 resource+0x68");
static_assert(offsetof(sub_4dfb570_texture, use) == 0x10, "sub_4dfb570 texture+0x10");
static_assert(offsetof(sub_4dfb570_texture, flags) == 0x12, "sub_4dfb570 texture+0x12");
static_assert(offsetof(sub_4dfb570_control, vtable) == 0x00, "sub_4dfb570 control+0x00");
static_assert(offsetof(sub_4dfb570_control, uses) == 0x08, "sub_4dfb570 control+0x08");
static_assert(offsetof(sub_4dfb570_control, weaks) == 0x0C, "sub_4dfb570 control+0x0C");
static_assert(offsetof(sub_4dfb570_out, ptr) == 0x00, "sub_4dfb570 out+0x00");
static_assert(offsetof(sub_4dfb570_out, ctrl) == 0x08, "sub_4dfb570 out+0x08");
static_assert(sizeof(sub_4dfb570_out) == 0x10, "sub_4dfb570 out size");

// Verbatim call instructions of [0x4dfb570, 0x4dfb690) (rdis `dis` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x4dfb62a  call qword ptr [0xF99FFA0]
0x4dfb646  call qword ptr [0xF99FFA0]
0x4dfb65b  call 0xE938CB0
0x4dfb677  call 0xE935740
0x4dfb683  call 0xE938D70
#endif

sub_4dfb570_out* sub_4dfb570(sub_4dfb570_out* out, const sub_4dfb570_handle* h) {
    // 0x4dfb570..0x4dfb597: prologue, then handle -> object -> resource -> texture,
    // falling to the empty result on any null or on state != 2.
    // 0x4dfb570  push rsi / 0x4dfb571  push rdi / 0x4dfb572  push rbx / 0x4dfb573  sub rsp,0x20
    // 0x4dfb577  mov r8,rcx            (r8 = the hidden return slot)
    // 0x4dfb57a  mov rax,[rdx]         object = h->object
    sub_4dfb570_resource* resource = nullptr;
    sub_4dfb570_texture* texture = nullptr;
    void* ctrl = nullptr;
    void* old = nullptr;
    void* object = h->object;
    if (!object) goto empty;                                    // 0x4dfb580  je short 0x4DFB5F1
    // 0x4dfb582  mov rsi,[rax+0x18]    resource = object->resource
    resource = static_cast<sub_4dfb570_resource*>(static_cast<sub_4dfb570_object*>(object)->resource);
    if (!resource) goto empty;                                   // 0x4dfb589  je short 0x4DFB5F1
    if (resource->state != 2) goto empty;                        // 0x4dfb58b  cmp byte ptr [rsi+0x68],2
    // 0x4dfb591  mov rdi,[rsi]         texture = resource->shared_ptr
    texture = static_cast<sub_4dfb570_texture*>(resource->shared_ptr);
    if (!texture) goto empty;                                    // 0x4dfb597  je short 0x4DFB5F1

    // 0x4dfb599..0x4dfb5b8: MSVC thread-safe static guard for the object at 0x129C13C0.
    // 0x4dfb599  mov eax,[0x129C13C0]
    // 0x4dfb59f  mov ecx,[0x128767C8]
    // 0x4dfb5a5  mov rdx,gs:[0x58]
    // 0x4dfb5ae  mov rcx,[rdx+rcx*8]
    // 0x4dfb5b2  cmp eax,[rcx+4]
    // 0x4dfb5b8  jg 0x4DFB651
    {
        const std::int32_t guard = *reinterpret_cast<volatile std::int32_t*>(0x129C13C0);
        const std::int32_t tls_index = *reinterpret_cast<volatile std::int32_t*>(0x128767C8);
        std::uint8_t* tls = reinterpret_cast<std::uint8_t*>(__readgsqword(0x58));
        const std::int32_t epoch =
            *reinterpret_cast<std::int32_t*>(tls + static_cast<std::int64_t>(tls_index) * 8 + 4);
        if (guard > epoch) {
            // 0x4dfb651..0x4dfb68b: slow path, header / destructor registration / footer.
            // 0x4dfb651  lea rcx,[0x129C13C0]
            // 0x4dfb658  mov rbx,r8
            // 0x4dfb65b  call 0xE938CB0
            sub_e938cb0(reinterpret_cast<void*>(0x129C13C0));
            // 0x4dfb660  mov r8,rbx
            // 0x4dfb663  cmp dword ptr [0x129C13C0],0xFFFFFFFF
            // 0x4dfb66a  jne 0x4DFB5BE
            if (*reinterpret_cast<volatile std::int32_t*>(0x129C13C0) == -1) {
                // 0x4dfb670  lea rcx,[0x4E05030]
                // 0x4dfb677  call 0xE935740
                sub_e935740(reinterpret_cast<void*>(0x4E05030));
                // 0x4dfb67c  lea rcx,[0x129C13C0]
                // 0x4dfb683  call 0xE938D70
                sub_e938d70(reinterpret_cast<void*>(0x129C13C0));
            }
            // 0x4dfb688  mov r8,rbx / 0x4dfb68b  jmp 0x4DFB5BE
        }
    }

body:
    // 0x4dfb5be..0x4dfb5c9: touch the texture, bail out while it is not ready on the GPU.
    // 0x4dfb5be  lock inc word ptr [rdi+0x10]
    _InterlockedIncrement16(reinterpret_cast<volatile short*>(&texture->use));
    // 0x4dfb5c3  movzx eax,byte ptr [rdi+0x12]
    // 0x4dfb5c7  test al,1
    // 0x4dfb5c9  je short 0x4DFB5F1
    if ((texture->flags & 1) == 0) goto empty;

    // 0x4dfb5cb..0x4dfb5da: zero the return value, then re-read the shared pointer.
    // 0x4dfb5cb  xorps xmm0,xmm0 / 0x4dfb5ce  movups [r8],xmm0
    out->ptr = nullptr;
    out->ctrl = nullptr;
    // 0x4dfb5d2  mov rax,[rsi]
    // 0x4dfb5d5  test rax,rax
    // 0x4dfb5d8  je short 0x4DFB5DE
    // 0x4dfb5da  movzx eax,word ptr [rax+0x10]
    if (resource->shared_ptr)
        (void)*reinterpret_cast<volatile std::uint16_t*>(
            &static_cast<sub_4dfb570_texture*>(resource->shared_ptr)->use);

    // 0x4dfb5de..0x4dfb5ef: take a strong reference on the control block.
    // 0x4dfb5de  mov rax,[rsi+8]
    // 0x4dfb5e2  test rax,rax
    // 0x4dfb5e5  je short 0x4DFB603
    ctrl = resource->shared_ctrl;
    if (ctrl) {
        // 0x4dfb5e7  lock inc dword ptr [rax+8]
        _InterlockedIncrement(reinterpret_cast<volatile long*>(
            static_cast<std::uint8_t*>(ctrl) + offsetof(sub_4dfb570_control, uses)));
        // 0x4dfb5eb  mov rax,[rsi+8]
        ctrl = resource->shared_ctrl;
    } else {
        // 0x4dfb603  xor eax,eax
        ctrl = nullptr;
    }

    // 0x4dfb605..0x4dfb616: store the new pair, then release whatever the slot held.
    // 0x4dfb605  mov rcx,[rsi] / 0x4dfb608  mov [r8],rcx
    out->ptr = resource->shared_ptr;
    // 0x4dfb60b  mov rsi,[r8+8]
    old = out->ctrl;
    // 0x4dfb60f  mov [r8+8],rax
    out->ctrl = ctrl;
    // 0x4dfb613  test rsi,rsi / 0x4dfb616  je short 0x4DFB5F8
    if (!old) return out;

    // 0x4dfb618..0x4dfb637: drop the strong count; at zero destroy and maybe free.
    // 0x4dfb618  lock dec dword ptr [rsi+8]
    // 0x4dfb61c  jne short 0x4DFB5F8
    if (_InterlockedDecrement(reinterpret_cast<volatile long*>(
            static_cast<std::uint8_t*>(old) + offsetof(sub_4dfb570_control, uses))) == 0) {
        // 0x4dfb61e..0x4dfb62a: virtual destructor, vtable slot 0, through the dispatch slot.
        // 0x4dfb61e  mov rax,[rsi] / 0x4dfb621  mov rax,[rax]
        void** vtable = *static_cast<void***>(old);
        // 0x4dfb624  mov rcx,rsi / 0x4dfb627  mov rdi,r8
        // 0x4dfb62a  call qword ptr [0xF99FFA0]
        sub_eea6040(old, vtable[0]);
        // 0x4dfb630  mov r8,rdi
        // 0x4dfb633  lock dec dword ptr [rsi+0xC]
        // 0x4dfb637  jne short 0x4DFB5F8
        if (_InterlockedDecrement(reinterpret_cast<volatile long*>(
                static_cast<std::uint8_t*>(old) + offsetof(sub_4dfb570_control, weaks))) == 0) {
            // 0x4dfb639..0x4dfb646: virtual deallocation, vtable slot 1, same dispatch slot.
            // 0x4dfb639  mov rax,[rsi] / 0x4dfb63c  mov rax,[rax+8]
            void** vtable_weak = *static_cast<void***>(old);
            // 0x4dfb640  mov rcx,rsi / 0x4dfb643  mov rsi,r8
            // 0x4dfb646  call qword ptr [0xF99FFA0]
            sub_eea6040(old, vtable_weak[1]);
        }
    }
    // 0x4dfb64c  mov rax,rsi / 0x4dfb64f  jmp short 0x4DFB5FB
    return out;

empty:
    // 0x4dfb5f1..0x4dfb5f8: empty result (16 zero bytes), return the slot.
    // 0x4dfb5f1  xorps xmm0,xmm0 / 0x4dfb5f4  movups [r8],xmm0
    out->ptr = nullptr;
    out->ctrl = nullptr;
    // 0x4dfb5f8  mov rax,r8
    // 0x4dfb5fb..0x4dfb602: add rsp,0x20 / pop rbx / pop rdi / pop rsi / ret
    return out;
}

} // namespace native::helpers
