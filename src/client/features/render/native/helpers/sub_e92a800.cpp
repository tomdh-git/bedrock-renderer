// LIFT 0xe92a800 size 0xbf 1.26.62.01 sub_e92a800
#include "sub_e92a800.h"

#include "client/features/render/native/Lift.h"

static_assert(sizeof(void*) == 8, "sub_e92a800: x64 ABI contract, pointer-sized address space");

namespace native {

// sub_e92a800 (0xe92a800, size 0xbf, 1.26.62.01).
//
// Locks the _Mtx at a0+0x30 via sub_eec59f0 (_Mtx_lock through data slot 0xF9A75A8),
// walks the 8-byte-element array [a0+0x178, a0+0x180), and for each element whose
// +0xD8 qword is zero calls sub_e92a350(element, arg2, [a0+0x128]). Breaks out of the
// loop if sub_e92a350 returns non-zero. Unlocks the mutex and returns 1 if the loop
// broke early, 0 if it ran to completion.
//
// sub_e92a350 is not classified in native_functions.tsv or native_boundary.tsv; the
// call site is documented in docs/progress/oc_U-EX7.e92a800.md under the callee-status section.
// No wrapper is invented for it.
//
// Verbatim instructions of the function (matches rdis dis 0xe92a800 0xbf):
#if 0
e92a800  push rbp
e92a801  push r14
e92a803  push rsi
e92a804  push rdi
e92a805  push rbx
e92a806  sub rsp,0x30
e92a80a  lea rbp,[rsp+0x30]
e92a80f  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
e92a817  mov rdi,rdx
e92a81a  mov rsi,rcx
e92a81d  lea rbx,[rcx+0x30]
e92a821  mov rcx,rbx
e92a824  call 0xEEC59F0
e92a829  test eax,eax
e92a82b  jne short 0xE92A8A3
e92a82d  mov [rbp-0x10],rbx
e92a831  cmp dword ptr [rsi+0x7C],0x7FFFFFFF
e92a838  je short 0xE92A8AD
e92a83a  xor ecx,ecx
e92a83c  jmp short 0xE92A84A
e92a83e  xchg ax,ax
e92a840  xor eax,eax
e92a842  lea rcx,[rbx+1]
e92a846  test al,al
e92a848  jne short 0xE92A887
e92a84a  mov rbx,rcx
e92a84d  mov rax,[rsi+0x178]
e92a854  mov r14,[rsi+0x180]
e92a85b  sub r14,rax
e92a85e  sar r14,3
e92a862  cmp rcx,r14
e92a865  jae short 0xE92A887
e92a867  mov rcx,[rax+rbx*8]
e92a86b  cmp qword ptr [rcx+0xD8],0
e92a873  jne short 0xE92A840
e92a875  mov r8,[rsi+0x128]
e92a87c  mov rdx,rdi
e92a87f  call 0xE92A350
e92a884  nop
e92a885  jmp short 0xE92A842
e92a887  cmp rbx,r14
e92a88a  setb bl
e92a88d  mov rcx,[rbp-0x10]
e92a891  call 0xEEC5A10
e92a896  mov eax,ebx
e92a898  add rsp,0x30
e92a89c  pop rbx
e92a89d  pop rdi
e92a89e  pop rsi
e92a89f  pop r14
e92a8a1  pop rbp
e92a8a2  ret
e92a8a3  mov ecx,5
e92a8a8  call 0xEEC5A00
e92a8ad  mov dword ptr [rsi+0x7C],0x7FFFFFFE
e92a8b4  mov ecx,6
e92a8b9  call 0xEEC5A00
e92a8be  int3
e92a8bf  nop
#endif

int sub_e92a800(void* a0, void* arg2)
{
    // 0xe92a800..0xe92a824: prologue (push rbp,r14,rsi,rdi,rbx; sub rsp,0x30; lea rbp;
    // mov [rbp-8],-2; mov rdi,rdx; mov rsi,rcx; lea rbx,[rcx+0x30]) then lock the mutex
    // at a0+0x30 via _Mtx_lock (sub_eec59f0 is an indirect tail jump through slot 0xF9A75A8
    // to this same target; we call ::_Mtx_lock directly so we can inspect its _Thrd_result
    // return). _Mtx_t is the MSVC CRT's opaque mutex handle type; a0+0x30 holds the address
    // of the embedded mutex, which we pass to ::_Mtx_lock / ::_Mtx_unlock directly.
    _Mtx_t mtx = reinterpret_cast<_Mtx_t>(
        reinterpret_cast<uint8_t*>(a0) + sub_e92a800Layout::kMutexOffset);
    _Thrd_result lockResult = ::_Mtx_lock(mtx);   // 0xe92a824  call 0xEEC59F0   ; sub_eec59f0 = _Mtx_lock via slot 0xF9A75A8

    // 0xe92a829  test eax,eax ; 0xe92a82b  jne short 0xE92A8A3  : lock failed -> throw error 5
    if (static_cast<int>(lockResult) != 0) {
        // loc_e92a8a3:  0xe92a8a3  mov ecx,5 ; 0xe92a8a8  call 0xEEC5A00   (std::_Throw_Cpp_error, never returns)
        native::sub_eec5a00(5);   // 0xe92a8a8  call 0xEEC5A00
        // Unreachable: _Throw_Cpp_error throws (mirrors the original which never continues past this call).
    }

    // 0xe92a82d  mov [rbp-0x10],rbx  : save the mutex pointer (not used again except at unlock)
    // 0xe92a831  cmp dword ptr [rsi+0x7C],0x7FFFFFFF ; 0xe92a838  je short 0xE92A8AD
    if (*reinterpret_cast<int32_t*>(
            reinterpret_cast<uint8_t*>(a0) + sub_e92a800Layout::kStateOffset) == 0x7FFFFFFF) {
        // loc_e92a8ad:  0xe92a8ad  mov dword ptr [rsi+0x7C],0x7FFFFFFE
        *reinterpret_cast<int32_t*>(
            reinterpret_cast<uint8_t*>(a0) + sub_e92a800Layout::kStateOffset) = 0x7FFFFFFE;
        //  0xe92a8b4  mov ecx,6 ; 0xe92a8b9  call 0xEEC5A00 ; 0xe92a8be  int3  (unreachable)
        native::sub_eec5a00(6);   // 0xe92a8b9  call 0xEEC5A00
        // Unreachable: _Throw_Cpp_error throws; the int3 after it in the original is a debug breakpoint only.
    }

    // 0xe92a83a  xor ecx,ecx ; 0xe92a83c  jmp short 0xE92A84A  : index = 0, enter loop
    size_t index = 0;
    size_t current = 0;
    size_t count = 0;   // declared outside the loop so it's visible after the loop exits

    for (;;) {
        // 0xe92a84a  mov rbx,rcx                         : current index
        current = index;
        // 0xe92a84d  mov rax,[rsi+0x178]  ;  0xe92a854  mov r14,[rsi+0x180]  : array base / end
        void** arrayBase = reinterpret_cast<void**>(
            *reinterpret_cast<uintptr_t*>(reinterpret_cast<uint8_t*>(a0) + sub_e92a800Layout::kArrayBaseOffset));
        void* arrayEnd = reinterpret_cast<void*>(
            *reinterpret_cast<uintptr_t*>(reinterpret_cast<uint8_t*>(a0) + sub_e92a800Layout::kArrayEndOffset));
        // 0xe92a85b  sub r14,rax ; 0xe92a85e  sar r14,3   : count = (end - base) / 8
        count = (reinterpret_cast<uint8_t*>(arrayEnd) - reinterpret_cast<uint8_t*>(arrayBase)) / 8;
        // 0xe92a862  cmp rcx,r14 ; 0xe92a865  jae short 0xE92A887  : index >= count -> exit
        if (current >= count) {
            break;   // 0xe92a865  jae short 0xE92A887
        }
        // 0xe92a867  mov rcx,[rax+rbx*8]  : element = array[index]
        void* element = arrayBase[current];
        // 0xe92a86b  cmp qword ptr [rcx+0xD8],0 ; 0xe92a873  jne short 0xE92A840  : element+0xD8 != 0 -> skip call
        if (*reinterpret_cast<int64_t*>(
                reinterpret_cast<uint8_t*>(element) + sub_e92a800Layout::kElementD8Offset) != 0) {
            // loc_e92a840: 0xe92a840  xor eax,eax  : al = 0 (no break)
            // 0xe92a842  lea rcx,[rbx+1] ; 0xe92a846  test al,al ; 0xe92a848  jne short 0xE92A887 (not taken)
            index = current + 1;   // 0xe92a842  lea rcx,[rbx+1]
            continue;              // al == 0 -> stay in loop
        }
        // 0xe92a875  mov r8,[rsi+0x128]  : ptr128 = a0+0x128
        // 0xe92a87c  mov rdx,rdi         : arg2
        // 0xe92a87f  call 0xE92A350      : sub_e92a350(element, arg2, ptr128)  ; callee not in either native table
        void* ptr128 = reinterpret_cast<void*>(
            *reinterpret_cast<uintptr_t*>(reinterpret_cast<uint8_t*>(a0) + sub_e92a800Layout::kCalleeArgOffset));
        int callResult = sub_e92a350(element, arg2, ptr128);   // 0xe92a87f  call 0xE92A350
        // 0xe92a884  nop
        // 0xe92a885  jmp short 0xE92A842 ; 0xe92a842  lea rcx,[rbx+1]
        index = current + 1;
        // 0xe92a846  test al,al ; 0xe92a848  jne short 0xE92A887  : sub_e92a350 returned non-zero -> break
        if ((callResult & 0xFF) != 0) {
            break;   // 0xe92a848  jne short 0xE92A887
        }
    }

    // loc_e92a887: 0xe92a887  cmp rbx,r14 ; 0xe92a88a  setb bl  : bl = (current < count)
    // 0xe92a88d  mov rcx,[rbp-0x10]  ;  0xe92a891  call 0xEEC5A10  : _Mtx_unlock(mtx) (sub_eec5a10 = _Mtx_unlock via slot 0xF9A75B8)
    ::_Mtx_unlock(mtx);   // 0xe92a891  call 0xEEC5A10   ; sub_eec5a10 = _Mtx_unlock via slot 0xF9A75B8
    // 0xe92a896  mov eax,ebx  : return = (current < count) ? 1 : 0
    // 0xe92a898..0xe92a8a2: add rsp,0x30; pop rbx,rdi,rsi,r14,rbp; ret
    return static_cast<int>(current < count);   // 0xe92a88a  setb bl ; 0xe92a896  mov eax,ebx
}

} // namespace native

LIFT_FN(sub_e92a800, "sub_e92a800", 0xE92A800, native::sub_e92a800, nullptr);
