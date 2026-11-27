// LIFT 0x673cef0 size 0xea 1.26.62.01 sub_673cef0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_673cef0.h"

#include <cstdint>
#include <cstddef>

namespace native::helpers {

// Layout assertions for liftcheck (mirror sub_673cef0Layout in the header): every struct
// field read or written by the function is asserted here by offsetof.
static_assert(offsetof(sub_673cef0_state, m_obj08) == 0x08, "sub_673cef0: m_obj08 at self+0x08");
static_assert(offsetof(sub_673cef0_state, m_obj30) == 0x30, "sub_673cef0: m_obj30 at self+0x30");
static_assert(offsetof(sub_673cef0_state, m_obj40) == 0x40, "sub_673cef0: m_obj40 at self+0x40");
static_assert(offsetof(sub_673cef0_state, m_obj50) == 0x50, "sub_673cef0: m_obj50 at self+0x50");
static_assert(sizeof(sub_673cef0_state) == 0x58, "sub_673cef0: state size");
static_assert(offsetof(sub_673cef0_refobj, m_vfptr) == 0x00, "sub_673cef0: m_vfptr at obj+0x00");
static_assert(offsetof(sub_673cef0_refobj, m_strong) == 0x08, "sub_673cef0: m_strong at obj+0x08");
static_assert(offsetof(sub_673cef0_refobj, m_weak) == 0x0C, "sub_673cef0: m_weak at obj+0x0C");
static_assert(sizeof(sub_673cef0_refobj) == 0x10, "sub_673cef0: refobj size");

LIFT_FN(sub_673cef0, "sub_673cef0", 0x673cef0, sub_673cef0, nullptr);

// Verbatim call instructions from the disassembly of [0x673cef0, 0x673cfda) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++. All seven are
// `call qword ptr [0xF99FFA0]` -> sub_eea6040 (vendor boundary thunk, jmp rax).
#if 0
0x673cf11  call qword ptr [0xF99FFA0]
0x673cf27  call qword ptr [0xF99FFA0]
0x673cf45  call qword ptr [0xF99FFA0]
0x673cf5b  call qword ptr [0xF99FFA0]
0x673cf79  call qword ptr [0xF99FFA0]
0x673cf8f  call qword ptr [0xF99FFA0]
0x673cfad  call qword ptr [0xF99FFA0]
#endif

// Release one vendor ref-counted object: strong-- at obj+0x8, destroy at vfptr[0] if 0,
// weak-- at obj+0xC, delete at vfptr[8] if 0. Reads/writes/calls in listing order.
//  0xA..0xB   lock dec [obj+8] / mov rax,[obj] / mov rax,[rax] / call [slot] /
//             lock dec [obj+0xC] / mov rax,[obj] / mov rax,[rax+8] / call [slot]
static void release_obj(sub_673cef0_refobj* obj)
{
    // 0x673cf02  lock dec dword ptr [obj+0x8]   ; strong-- (atomic write)
    std::uint32_t* strong = &obj->m_strong;
    if (--(*strong) == 0) {                  // 0x673cf06  jne skip (proceed iff strong == 0)
        // 0x673cf08  mov rax,[obj]      ; vfptr = obj->m_vfptr               (read obj+0x0)
        void** vfptr = obj->m_vfptr;
        // 0x673cf0b  mov rax,[rax]      ; destroy = vfptr[0]                 (read vfptr+0x0)
        void* destroy = vfptr[0];
        // 0x673cf0e  mov rcx,obj
        // 0x673cf11  call qword ptr [0xF99FFA0]   ; sub_eea6040(obj, destroy)
        sub_eea6040(obj, destroy);           // 0x673cf11 (destroy runs, then returns here)
        // 0x673cf17  lock dec dword ptr [obj+0xC] ; weak-- (atomic write)
        std::uint32_t* weak = &obj->m_weak;
        if (--(*weak) == 0) {                // 0x673cf1b  jne skip (proceed iff weak == 0)
            // 0x673cf1d  mov rax,[obj]      ; vfptr re-read                  (read obj+0x0)
            void** vfptr2 = obj->m_vfptr;
            // 0x673cf20  mov rax,[rax+8]    ; delete = vfptr[8]              (read vfptr+0x8)
            void* del = vfptr2[1];
            // 0x673cf24  mov rcx,obj
            // 0x673cf27  call qword ptr [0xF99FFA0]   ; sub_eea6040(obj, del)
            sub_eea6040(obj, del);           // 0x673cf27
        }
    }
}

void sub_673cef0(sub_673cef0_state* self)
{
    // 0x673cef0..0x673cf2d  release self->m_obj50
    {
        // 0x673cef0  push rsi
        // 0x673cef1  push rdi
        // 0x673cef2  sub rsp,0x28
        // 0x673cef6  mov rsi,rcx            ; self = rcx ('this')
        // 0x673cef9  mov rdi,[rcx+0x50]     ; obj = self->m_obj50
        sub_673cef0_refobj* obj = reinterpret_cast<sub_673cef0_refobj*>(self->m_obj50);   // 0x673cef9
        // 0x673cefd  test rdi,rdi
        // 0x673cf00  je short loc_673cf2d   ; null -> next field
        if (obj != nullptr) {                // 0x673cefd  test rdi,rdi ; 0x673cf00  je loc_673cf2d
            release_obj(obj);                // 0x673cf02..0x673cf27  (m_obj50 strong/weak release)
        }
        // loc_673cf2d:  (from 0x673cf00, 0x673cf06, 0x673cf1b)
    }

    // 0x673cf2d..0x673cf61  release self->m_obj40
    {
        // 0x673cf2d  mov rdi,[rsi+0x40]     ; obj = self->m_obj40
        sub_673cef0_refobj* obj = reinterpret_cast<sub_673cef0_refobj*>(self->m_obj40);   // 0x673cf2d
        // 0x673cf31  test rdi,rdi
        // 0x673cf34  je short loc_673cf61   ; null -> next field
        if (obj != nullptr) {                // 0x673cf31  test rdi,rdi ; 0x673cf34  je loc_673cf61
            release_obj(obj);                // 0x673cf36..0x673cf5b  (m_obj40 strong/weak release)
        }
        // loc_673cf61:  (from 0x673cf34, 0x673cf3a, 0x673cf4f)
    }

    // 0x673cf61..0x673cf95  release self->m_obj30
    {
        // 0x673cf61  mov rdi,[rsi+0x30]     ; obj = self->m_obj30
        sub_673cef0_refobj* obj = reinterpret_cast<sub_673cef0_refobj*>(self->m_obj30);   // 0x673cf61
        // 0x673cf65  test rdi,rdi
        // 0x673cf68  je short loc_673cf95   ; null -> next field
        if (obj != nullptr) {                // 0x673cf65  test rdi,rdi ; 0x673cf68  je loc_673cf95
            release_obj(obj);                // 0x673cf6a..0x673cf8f  (m_obj30 strong/weak release)
        }
        // loc_673cf95:  (from 0x673cf68, 0x673cf6e, 0x673cf83)
    }

    // 0x673cf95..0x673cfda  release self->m_obj08; the delete call is a tail call via the thunk
    {
        // 0x673cf95  mov rsi,[rsi+8]        ; obj = self->m_obj08 (rsi reused as the walk register)
        sub_673cef0_refobj* obj = reinterpret_cast<sub_673cef0_refobj*>(self->m_obj08);   // 0x673cf95
        // 0x673cf99  test rsi,rsi
        // 0x673cf9c  je short loc_673cfd3   ; null -> return
        if (obj != nullptr) {                // 0x673cf99  test rsi,rsi ; 0x673cf9c  je loc_673cfd3
            // 0x673cf9e  lock dec dword ptr [obj+0x8]   ; strong-- (atomic write)
            std::uint32_t* strong = &obj->m_strong;
            if (--(*strong) == 0) {          // 0x673cfa2  jne loc_673cfd3 (proceed iff strong == 0)
                // 0x673cfa4  mov rax,[obj]      ; vfptr = obj->m_vfptr       (read obj+0x0)
                void** vfptr = obj->m_vfptr;
                // 0x673cfa7  mov rax,[rax]      ; destroy = vfptr[0]         (read vfptr+0x0)
                void* destroy = vfptr[0];
                // 0x673cfad  call qword ptr [0xF99FFA0]   ; sub_eea6040(obj, destroy)
                sub_eea6040(obj, destroy);   // 0x673cfad
                // 0x673cfb3  lock dec dword ptr [obj+0xC] ; weak-- (atomic write)
                std::uint32_t* weak = &obj->m_weak;
                if (--(*weak) == 0) {        // 0x673cfb7  jne loc_673cfd3 (proceed iff weak == 0)
                    // 0x673cfb9  mov rax,[obj]      ; vfptr re-read           (read obj+0x0)
                    void** vfptr2 = obj->m_vfptr;
                    // 0x673cfbc  mov rax,[rax+8]    ; delete = vfptr[8]       (read vfptr+0x8)
                    void* del = vfptr2[1];
                    // 0x673cfc0  mov rdx,[0xF99FFA0]   ; rdx = sub_eea6040
                    // 0x673cfc7  mov rcx,obj
                    // 0x673cfca  add rsp,0x28
                    // 0x673cfce  pop rdi
                    // 0x673cfcf  pop rsi
                    // 0x673cfd0  jmp rdx            ; tail call sub_eea6040(obj, del) -> vfptr[8](obj)
                    sub_eea6040(obj, del);   // 0x673cfc0..0x673cfd0 tail call via thunk; never returns
                    // Unreachable: the thunk tail-jumps to vfptr[8]; control never resumes here.
                }
            }
        }
        // loc_673cfd3:
        // 0x673cfd3  add rsp,0x28
        // 0x673cfd7  pop rdi
        // 0x673cfd8  pop rsi
        // 0x673cfd9  ret
    }
}

} // namespace native::helpers
