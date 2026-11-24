// LIFT 0xe806560 size 0x15f 1.26.62.01 sub_e806560
#include "sub_e806560.h"
static_assert(sizeof(void*) == 8, "ptr");

#if 0
0xe8065e5  call qword ptr [0xF99FFA0]
0xe80660d  call qword ptr [0xF99FFA0]
0xe8066b9  call 0xE951550
#endif

extern "C" void* sub_e806560(void* a0, void* a1, int a2, void* a3, void* a4) {
    // 0xe806560..0xe806563
    // push rsi; push rdi; push rbx; sub rsp,0x50
    void* rsi = a0;
    void* rdi = a3;
    // 0xe806567..0xe80656d
    void* rcx_stack = a4; // [rsp+0x90]
    // 0xe806575..0xe80657f stack cookie
    (void)rcx_stack;
    // 0xe806584..0xe806592
    long long idx = (long long)a2;
    // data table at 0x1285DBE0, stride 24
    unsigned char* table = (unsigned char*)0x1285DBE0;
    void* rbx = (void*)(table + idx * 3 * 8);
    // 0xe806596
    void* out_slot = nullptr; // [rsp+0x40]
    // 0xe80659f
    int r9d = *(int*)(table + idx * 3 * 8 + 0x14);
    // 0xe8065a4..0xe8065ae
    int r8d = (a2 == 4) ? 8 : 0;
    // 0xe8065b2..0xe8065bc
    void** vtbl = *(void***)a1;
    void* fn = vtbl[0xD8 / 8]; // +0xD8
    // 0xe8065bc..0xe8065e5 setup stack args and call
    void* r10_slot = *(void**)0xF99FFA0;
    out_slot = nullptr;
    // call via slot
    int eax = ((int(*)(void*, void*, int, void*, int, void*, void*, void*, void**))r10_slot)(
        a1, rbx, r8d, rdi, r9d, rcx_stack, (void*)0xF4ED2C0, nullptr, &out_slot);
    // 0xe8065eb..0xe8065ed
    if (eax < 0) {
        // 0xe806615.. 
        void* rcxg = *(void**)0x12BB4910;
        if (*(int*)((char*)rcxg + 0x19F88) >= 5) {
            int edx = 4;
            int r8v = eax + 0x7785FFFB;
            if (r8v <= 0x1D) {
                int r9mask = 0x28000007;
                if ((r9mask >> (r8v & 31)) & 1) goto lbl_set;
            }
            r8v = eax + 0x7789F798;
            if (r8v <= 0xC) {
                int r9mask = 0x1101;
                if ((r9mask >> (r8v & 31)) & 1) goto lbl_set;
            }
            if (eax == 0x88760826) goto lbl_set;
            edx = 3;
        lbl_set:
            *(int*)((char*)rcxg + 0x19F88) = edx;
            *(int*)((char*)rcxg + 0x19F8C) = eax;
        }
        // 0xe806674..
        ((native::E806560_A0*)rsi)->p0 = nullptr;
        ((native::E806560_A0*)rsi)->i8 = 0;
        ((native::E806560_A0*)rsi)->p10 = nullptr;
        goto done;
    }
    // 0xe8065ef..0xe8065fa
    ((native::E806560_A0*)rsi)->p0 = out_slot;
    ((native::E806560_A0*)rsi)->i8 = *(int*)((char*)rbx + 0x14);
    // 0xe8065fd..0xe806600
    if (*(int*)rdi != 1) {
        // 0xe80668c
        eax = 0;
        goto store_p10;
    }
    // 0xe806606..0xe806613
    {
        void** vtbl2 = *(void***)out_slot;
        void* fn2 = vtbl2[0x58 / 8]; // +0x58
        void* r10_slot2 = *(void**)0xF99FFA0;
        (void)fn2;
        eax = ((int(*)(void*))r10_slot2)(out_slot);
    }
store_p10:
    ((native::E806560_A0*)rsi)->p10 = (void*)(size_t)eax;
done:
    // 0xe806692..0xe8066b0
    (void)fn;
    return rsi;
}

// LIFT_FN registry entry placeholder
// native::registry::register_fn("sub_e806560", 0xe806560, &sub_e806560);
