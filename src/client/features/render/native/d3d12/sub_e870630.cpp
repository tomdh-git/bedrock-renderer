// LIFT 0xe870630 size 0x7b 1.26.62.01 BgfxFrameBuilder slot 16
#include "sub_e870630.h"
#include "Lift.h"
static_assert(sizeof(void*) == 8, "ptr");

#if 0
0xe870630  sub rsp,0x48
0xe870634  mov rax,[0x1230A0C0]
0xe87063b  xor rax,rsp
0xe87063e  mov [rsp+0x40],rax
0xe870643  mov r8d,8
0xe870649  call qword ptr [0xF9A7480]
0xe87064f  mov rax,[rax+8]
0xe870653  test rax,rax
0xe870656  js short 0xE870678
0xe870658  cmp rax,8
0xe87065c  sete al
0xe87065f  mov rcx,[rsp+0x40]
0xe870664  xor rcx,rsp
0xe870667  mov rdx,[0x1230A0C0]
0xe87066e  cmp rdx,rcx
0xe870671  jne short 0xE87069D
0xe870673  add rsp,0x48
0xe870677  ret
0xe870678  xorps xmm0,xmm0
0xe87067b  movups [rsp+0x30],xmm0
0xe870680  lea rax,[0xF08E738]
0xe870687  mov [rsp+0x28],rax
0xe87068c  lea rdx,[0xFB3B080]
0xe870693  lea rcx,[rsp+0x28]
0xe870698  call 0xEEC6D80
0xe87069d  mov rcx,[rsp+0x40]
0xe8706a2  xor rcx,rsp
0xe8706a5  call 0xE951550
0xe8706aa  int3
0xe8706ab  int3
#endif

extern "C" bool sub_e870630(void* rcx, const void* rdx) {
    (void)rcx; (void)rdx;
    // 0xe870630..0xe870642
    uintptr_t cookie = *reinterpret_cast<uintptr_t*>(0x1230A0C0);
    uintptr_t guard = cookie ^ reinterpret_cast<uintptr_t>(&guard);
    *reinterpret_cast<uintptr_t*>(reinterpret_cast<char*>(&guard) + 0) = guard; // [rsp+0x40]

    // 0xe870643..0xe870649
    void* (*indirect_fn)(uint32_t) = reinterpret_cast<void* (*)(uint32_t)>(*reinterpret_cast<uintptr_t*>(0xF9A7480));
    void* ret = indirect_fn(8u);

    // 0xe87064f..0xe87065c
    int64_t sz = *reinterpret_cast<int64_t*>(static_cast<char*>(ret) + 8);
    bool ok;
    // 0xe870656  js short 0xE870678
    if (sz < 0) {
        // 0xe870678..0xe870698
        struct { void* a; uint64_t b; } err;
        err.a = reinterpret_cast<void*>(0xF08E738);
        err.b = 0;
        sub_eec6d80(&err, reinterpret_cast<void*>(0xFB3B080)); // noreturn
        __builtin_unreachable();
    } else {
        // 0xe870658..0xe87065c
        ok = (sz == 8);
    }

    // 0xe87065f..0xe870671
    if (*reinterpret_cast<uintptr_t*>(0x1230A0C0) != (guard ^ reinterpret_cast<uintptr_t>(&guard)))
        boundary::sub_e951550(reinterpret_cast<void*>(&guard)); // __stack_chk_fail; noreturn

    // 0xe870673..0xe870677
    return ok;
}

// LIFT_FN registration for the main function
LIFT_FN(sub_e870630, "BgfxFrameBuilder slot 16 (sub_e870630)", 0xe870630, sub_e870630, nullptr);