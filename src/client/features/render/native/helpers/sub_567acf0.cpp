// LIFT 0x567acf0 size 0xe9 1.26.62.01 sub_567acf0
#include "client/features/render/native/helpers/sub_567acf0.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native {
    // Forward declaration: sub_e935700 (lift/set), void* sub_e935700(void*), tail jump to sub_392960.
    void* sub_e935700(void* a0);
}

namespace native::helpers {

// sub_567acf0 (0x567acf0, size 0xe9, 1.26.62.01).
//
// Releases every refcounted object held by the elements of self's buffer (tags 1 and 2 of
// the per-element type tag at element+0x18; jump table at data_f25cd68 maps tags 1,2 to the
// release path and tags 0,3,4 to skip), then frees the backing buffer via sub_e935700 and
// zeroes self->data_start, self->data_end and self->buffer_end.
//
// Element layout (0x28 bytes):
//   +0x08  ref_obj  void*   refcounted object pointer
//   +0x18  type_tag u8      type tag (0..4 valid; >4 skipped)
// Refcounted object:
//   +0x00  vfptr        void**
//   +0x08  refcount     int32 (lock dec)
//   +0x0C  count0xC     int32 (lock dec)
//   vfptr[0] = destructor, vfptr[1] = operator delete, both invoked through sub_eea6040.
//
// Buffer release (after the element loop): rdx = self->buffer_end - self->data_start.
//   if (rdx < 0x1000) -> sub_e935700(self->data_start)
//   else:
//     rax = *(self->data_start - 8); rdi = (self->data_start - 8) - rax;
//     if (rdi >= 0x20) -> noreturn fail path: call [0xF9A8C78](0,0,0,0); int3
//     rdx += 0x27; rdi = rax; -> sub_e935700(rax)
// Then: self->data_start = 0; self->data_end = 0; self->buffer_end = 0; return sub_e935700 result.
//
// Same reads, same writes, same calls in the same order, same return. Nothing else happens
// in [0x567acf0, 0x567add9).

uintptr_t sub_567acf0(sub_567acf0_state* self) {
    // 0x567acf0..0x567ad13:
    //   0x567acf0  push r15
    //   0x567acf2  push r14
    //   0x567acf4  push rsi
    //   0x567acf5  push rdi
    //   0x567acf6  push rbx
    //   0x567acf7  sub rsp,0x30
    //   0x567acfb  mov rdi,[rcx]           ; rdi = self->data_start
    //   0x567acfe  test rdi,rdi
    //   0x567ad01  je short 0x567ADB3      ; if null, goto end
    //   0x567ad07  mov rsi,rcx             ; rsi = self
    //   0x567ad0a  mov r14,[rcx+8]         ; r14 = self->data_end
    //   0x567ad0e  cmp rdi,r14
    //   0x567ad11  je short 0x567AD75      ; if start==end, goto buffer release
    void* const rdi0 = self->data_start;   // 0x567acfb  mov rdi,[rcx]
    if (rdi0 == nullptr) {                 // 0x567acfe  test rdi,rdi ; 0x567ad01  je short 0x567ADB3
        return 0;                          // 0x567adb3  ... ret (rax == data_start == nullptr)
    }
    void* r14 = self->data_end;            // 0x567ad0a  mov r14,[rcx+8]
    void* rdi = rdi0;                      // rdi = self->data_start

    // Element loop: process each element while rdi != r14.
    //   loc_567ad20:
    //   0x567ad20  add rdi,0x28           ; advance to next element
    //   0x567ad24  cmp rdi,r14
    //   0x567ad27  je short 0x567AD72     ; loop exit -> buffer release
    //   0x567ad13  lea r15,[0xF25CD68]    ; r15 = jump table base (data_f25cd68)
    //   0x567ad1a  jmp short 0x567AD29
    //   0x567ad1c  nop [rax]
    //   0x567ad29  movzx eax,byte ptr [rdi+0x18]  ; eax = element->type_tag
    //   0x567ad2d  cmp rax,4
    //   0x567ad31  ja short 0x567AD20             ; tag > 4: skip
    //   0x567ad33  movsxd rax,[r15+rax*4]         ; jump table[tag]
    //   0x567ad37  add rax,r15
    //   0x567ad3a  jmp rax                         ; indirect jump (tag 1,2 -> 0x567ad3c)
    while (rdi != r14) {                     // 0x567ad0e  cmp rdi,r14 ; 0x567ad11/0x567ad24/0x567ad27
        // 0x567ad29..0x567ad3c:
        std::uint8_t const tag =
            *reinterpret_cast<std::uint8_t*>(
                reinterpret_cast<std::uint8_t*>(rdi) + 0x18);  // 0x567ad29  movzx eax,byte ptr [rdi+0x18]
        if (tag <= 4) {                             // 0x567ad2d  cmp rax,4 ; 0x567ad31  ja short 0x567AD20
            // Jump table (data_f25cd68): tag 0->skip, 1->release, 2->release, 3->skip, 4->skip.
            if (tag == 1 || tag == 2) {             // 0x567ad33..0x567ad3a  jmp rax -> 0x567ad3c
                // 0x567ad3c..0x567ad45:
                //   0x567ad3c  mov rbx,[rdi+8]        ; rbx = element->ref_obj
                //   0x567ad40  test rbx,rbx
                //   0x567ad43  je short 0x567AD20     ; if null, skip
                void* rbx = *reinterpret_cast<void**>(
                    reinterpret_cast<std::uint8_t*>(rdi) + 0x08);  // 0x567ad3c  mov rbx,[rdi+8]
                if (rbx != nullptr) {               // 0x567ad40  test rbx,rbx ; 0x567ad43  je short 0x567AD20
                    // 0x567ad45..0x567ad4b:
                    //   0x567ad45  lock dec dword ptr [rbx+8]   ; refcount -1
                    //   0x567ad49  jne short 0x567AD20          ; if not zero, skip
                    if (_InterlockedDecrement(
                            reinterpret_cast<volatile long*>(
                                reinterpret_cast<std::uint8_t*>(rbx) + 0x08)) == 0) {  // 0x567ad45
                        // 0x567ad4b..0x567ad5a:
                        //   0x567ad4b  mov rax,[rbx]            ; rax = *rbx (vfptr)
                        //   0x567ad4e  mov rax,[rax]            ; rax = vfptr[0] (destructor)
                        //   0x567ad51  mov rcx,rbx              ; RCX = rbx
                        //   0x567ad54  call qword ptr [0xF99FFA0]  ; sub_eea6040(rbx, vfptr[0])
                        void** const vfptr = *reinterpret_cast<void***>(rbx);  // 0x567ad4b  mov rax,[rbx]
                        (void)*vfptr;                                        // 0x567ad4e  mov rax,[rax]  (target in RAX)
                        sub_eea6040(rbx, vfptr[0]);                        // 0x567ad51  mov rcx,rbx ; 0x567ad54  call
                        // 0x567ad5a..0x567ad60:
                        //   0x567ad5a  lock dec dword ptr [rbx+0xC]   ; count0xC -1
                        //   0x567ad5e  jne short 0x567AD20            ; if not zero, skip
                        if (_InterlockedDecrement(
                                reinterpret_cast<volatile long*>(
                                    reinterpret_cast<std::uint8_t*>(rbx) + 0x0C)) == 0) {  // 0x567ad5a
                            // 0x567ad60..0x567ad70:
                            //   0x567ad60  mov rax,[rbx]            ; rax = *rbx (vfptr)
                            //   0x567ad63  mov rax,[rax+8]          ; rax = vfptr[1] (operator delete)
                            //   0x567ad67  mov rcx,rbx              ; RCX = rbx
                            //   0x567ad6a  call qword ptr [0xF99FFA0]  ; sub_eea6040(rbx, vfptr[1])
                            //   0x567ad70  jmp short 0x567AD20        ; advance
                            sub_eea6040(rbx, vfptr[1]);  // 0x567ad60  mov rax,[rbx] ; 0x567ad63  mov rax,[rax+8]
                                                         // 0x567ad67  mov rcx,rbx ; 0x567ad6a  call ; 0x567ad70  jmp
                        }
                    }
                }
            }
        }
        // 0x567ad20  add rdi,0x28 ; loop back-edge
        rdi = reinterpret_cast<void*>(
            reinterpret_cast<std::uintptr_t>(rdi) + 0x28);  // 0x567ad20  add rdi,0x28
    }

    // loc_567ad72:
    //   0x567ad72  mov rdi,[rsi]     ; rdi = self->data_start (reload)
    rdi = self->data_start;      // 0x567ad72  mov rdi,[rsi]

    // 0x567ad75..0x567ad83:
    //   0x567ad75  mov rdx,[rsi+0x10]   ; rdx = self->buffer_end
    //   0x567ad79  sub rdx,rdi          ; rdx = buffer size
    //   0x567ad7c  cmp rdx,0x1000
    std::uintptr_t rdx =
        reinterpret_cast<std::uintptr_t>(self->buffer_end) -
        reinterpret_cast<std::uintptr_t>(rdi);  // 0x567ad75  mov rdx,[rsi+0x10] ; 0x567ad79  sub rdx,rdi
    if (rdx >= 0x1000) {                        // 0x567ad7c  cmp rdx,0x1000 ; 0x567ad83  jb short 0x567AD9D
        // 0x567ad85..0x567ad90:
        //   0x567ad85  mov rax,[rdi-8]          ; rax = heap chunk size
        //   0x567ad89  add rdi,0xFFFFFFFFFFFFFFF8   ; rdi -= 8
        //   0x567ad8d  sub rdi,rax              ; rdi -= rax
        std::uintptr_t const rax =
            *reinterpret_cast<std::uintptr_t*>(
                reinterpret_cast<std::uint8_t*>(rdi) - 8);  // 0x567ad85  mov rax,[rdi-8]
        std::uintptr_t const rdi2 =
            reinterpret_cast<std::uintptr_t>(rdi) - 8 - rax;  // 0x567ad89  add rdi,-8 ; 0x567ad8d  sub rdi,rax
        if (rdi2 >= 0x20) {                     // 0x567ad90  cmp rdi,0x20 ; 0x567ad94  jae short 0x567ADBF
            // loc_567adbf: slow path, noreturn
            //   0x567adbf  mov qword ptr [rsp+0x20],0   ; dead store
            //   0x567adc8..0x567adcf  xor ecx,edx,r8d,r9d   ; zero args
            //   0x567add2  call qword ptr [0xF9A8C78]     ; fail handler (noreturn)
            //   0x567add8  int3
            auto failFn = reinterpret_cast<void (*)(void*, void*, void*, void*)>(
                *reinterpret_cast<void** volatile*>(0xF9A8C78ULL));
            failFn(nullptr, nullptr, nullptr, nullptr);  // 0x567add2  call qword ptr [0xF9A8C78]
            __assume(false);                            // 0x567add8  int3  (noreturn)
        }
        // 0x567ad96..0x567ad9a:
        //   0x567ad96  add rdx,0x27          ; rdx += 0x27
        //   0x567ad9a  mov rdi,rax           ; rdi = rax (heap chunk size)
        rdx += 0x27;                            // 0x567ad96  add rdx,0x27
        rdi = reinterpret_cast<void*>(rax);   // 0x567ad9a  mov rdi,rax
    }

    // loc_567ad9d:
    //   0x567ad9d  mov rcx,rdi
    //   0x567ada0  call 0xE935700              ; sub_e935700(rdi)
    void* const result = sub_e935700(rdi);     // 0x567ada0  call 0xE935700

    // 0x567ada5..0x567adab:
    //   0x567ada5  xorps xmm0,xmm0
    //   0x567ada8  movups [rsi],xmm0            ; self->data_start = 0 ; self->data_end = 0  (16 bytes)
    //   0x567adab  mov qword ptr [rsi+0x10],0   ; self->buffer_end = 0
    self->data_start = nullptr;                // 0x567ada5..0x567ada8  movups [rsi],xmm0 (low qword)
    self->data_end = nullptr;                  // 0x567ada5..0x567ada8  movups [rsi],xmm0 (high qword)
    self->buffer_end = nullptr;                // 0x567adab  mov qword ptr [rsi+0x10],0

    // 0x567adb3..0x567adbe:
    //   0x567adb3  add rsp,0x30
    //   0x567adb7  pop rbx
    //   0x567adb8  pop rdi
    //   0x567adb9  pop rsi
    //   0x567adba  pop r14
    //   0x567adbc  pop r15
    //   0x567adbe  ret
    return reinterpret_cast<uintptr_t>(result);
}

} // namespace native::helpers

LIFT_FN(sub_567acf0, "sub_567acf0", 0x567acf0, native::helpers::sub_567acf0, nullptr);

// Verbatim instruction quotes from the disassembly of [0x567acf0, 0x567add9) (rdis `dis` output).
// Machine-checked by tools/sigs/verify_oc.py against the exe.
#if 0
0x567ad54  call qword ptr [0xF99FFA0]
0x567ad6a  call qword ptr [0xF99FFA0]
0x567ada0  call 0xE935700
0x567add2  call qword ptr [0xF9A8C78]
#endif
