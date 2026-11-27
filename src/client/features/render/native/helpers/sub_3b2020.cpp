// LIFT 0x3b2020 size 0xac 1.26.62.01 sub_3b2020

#include "sub_3b2020.h"

#include <intrin.h> // _InterlockedExchangeAdd64, _InterlockedAnd64

namespace native {

// Forward declarations for external callees (not in native_functions.tsv or native_boundary.tsv)
// These are called as raw function pointers per the original code.
// 0xE943170: called at 0x3b2056 with RCX = self
// 0xE943194: called at 0x3b206d with RCX = self
// 0xEEC5B90: called at 0x3b2092 with RCX = &self->field_0x18
using ExternalCallee1_t = void(*)(sub_3b2020_state* self);
using ExternalCallee2_t = void(*)(sub_3b2020_state* self);
using ExternalCallee3_t = void(*)(void* field_0x18);

void sub_3b2020(sub_3b2020_state* self) {
    // 0x3b2020..0x3b2053: prologue, atomic refcount decrement, early exit check
    // 0x3b2020  push rbp
    // 0x3b2021  push rsi
    // 0x3b2022  push rdi
    // 0x3b2023  sub rsp,0x30
    // 0x3b2027  lea rbp,[rsp+0x30]
    // 0x3b202c  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
    // 0x3b2034  mov rsi,rcx
    // 0x3b2037  mov rax,0xFFFFFFFFFFFFFFFF
    // 0x3b203e  lock xadd [rcx+0x60],rax
    // 0x3b2044  mov rcx,0x8000000000000001
    // 0x3b204e  cmp rax,rcx
    // 0x3b2051  jne short 0x3B20A6
    int64_t oldRefs = _InterlockedExchangeAdd64(reinterpret_cast<volatile int64_t*>(&self->field_0x60), -1);
    if (oldRefs != 0x8000000000000001LL) {
        // 0x3b20a6  add rsp,0x30
        // 0x3b20aa  pop rdi
        // 0x3b20ab  pop rsi
        // 0x3b20ac  pop rbp
        // 0x3b20ad  ret
        return;
    }

    // 0x3b2053..0x3b205b: call 0xE943170 (external)
    // 0x3b2053  mov rcx,rsi
    // 0x3b2056  call 0xE943170
    reinterpret_cast<ExternalCallee1_t>(0xE943170)(self);

    // 0x3b205b..0x3b206d: atomic AND to clear destroying bit
    // 0x3b205b  mov rax,0x7FFFFFFFFFFFFFFF
    // 0x3b2065  lock and [rsi+0x60],rax
    _InterlockedAnd64(reinterpret_cast<volatile int64_t*>(&self->field_0x60), 0x7FFFFFFFFFFFFFFFLL);

    // 0x3b206d..0x3b2072: call 0xE943194 (external)
    // 0x3b206d  mov rcx,rsi
    // 0x3b2072  call 0xE943194
    reinterpret_cast<ExternalCallee2_t>(0xE943194)(self);

    // 0x3b2072..0x3b207e: lock mutex
    // 0x3b2072  mov rdi,[rsi+8]
    // 0x3b2076  mov rcx,rdi
    // 0x3b2079  call 0xEEC59F0
    // 0x3b207e  test eax,eax
    // 0x3b2080  jne short 0x3B20AE
    struct _Mtx* mtx = self->field_0x08;
    if (sub_eec59f0(mtx) != 0) {
        // 0x3b20ae  mov ecx,5
        // 0x3b20b3  call 0xEEC5A00
        // 0x3b20b8  nop
        // 0x3b20b9  mov dword ptr [rdi+0x4C],0x7FFFFFFE
        // 0x3b20c0  mov ecx,6
        // 0x3b20c5  call 0xEEC5A00
        // 0x3b20ca  nop
        // 0x3b20cb  int3
        sub_eec5a00(5);
        // dead code in practice (sub_eec5a00 never returns), but lifted for completeness:
        mtx->field_0x4C = 0x7FFFFFFFu; // actually self->field_0x4C via rdi
        sub_eec5a00(6);
        __debugbreak();
    }

    // 0x3b2082..0x3b208b: check sentinel state
    // 0x3b2082  cmp dword ptr [rdi+0x4C],0x7FFFFFFF
    // 0x3b2089  je short 0x3B20B9
    if (mtx->field_0x4C == 0x7FFFFFFFu) { // actually self->field_0x4C
        // 0x3b20b9  mov dword ptr [rdi+0x4C],0x7FFFFFFE
        // 0x3b20c0  mov ecx,6
        // 0x3b20c5  call 0xEEC5A00
        // 0x3b20ca  nop
        // 0x3b20cb  int3
        mtx->field_0x4C = 0x7FFFFFFEu;
        sub_eec5a00(6);
        __debugbreak();
    }

    // 0x3b208b..0x3b2097: call 0xEEC5B90 (external) with &self->field_0x18
    // 0x3b208b  add rsi,0x18
    // 0x3b208f  mov rcx,rsi
    // 0x3b2092  call 0xEEC5B90
    // 0x3b2097  mov rcx,rdi
    reinterpret_cast<ExternalCallee3_t>(0xEEC5B90)(self->field_0x18);

    // 0x3b2097..0x3b20a1: tail call to unlock mutex
    // 0x3b2097  mov rcx,rdi
    // 0x3b209a  add rsp,0x30
    // 0x3b209e  pop rdi
    // 0x3b209f  pop rsi
    // 0x3b20a0  pop rbp
    // 0x3b20a1  jmp 0xEEC5A10
    return sub_eec5a10(mtx);
}

// Verbatim instruction quotes for liftcheck verification
#if 0
0x3b2056  call 0xE943170
0x3b206d  call 0xE943194
0x3b2079  call 0xEEC59F0
0x3b2092  call 0xEEC5B90
0x3b20b3  call 0xEEC5A00
0x3b20c5  call 0xEEC5A00
0x3b20a1  jmp 0xEEC5A10
#endif

// Registry entry
// Note: LIFT_FN macro is defined in the project's lift framework
// LIFT_FN(sub_3b2020, "sub_3b2020", 0x3B2020, native::sub_3b2020, nullptr);

} // namespace native