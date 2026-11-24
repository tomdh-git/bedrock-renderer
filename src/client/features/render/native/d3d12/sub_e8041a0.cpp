// LIFT 0xe8041a0 size 0x21c 1.26.62.01 sub_e8041a0
#include "sub_e8041a0.h"
static_assert(sizeof(void*) == 8, "ptr");

#if 0
0xe8041d8  mov rdi,[rdx+0x10]
0xe8041dc  mov rcx,[0x12ADF800]
0xe80420d  call r10
0xe804239  mov rax,[rcx]
0xe80423c  mov rax,[rax+8]
0xe804240  mov r10,[0xF99FFA0]
0xe804263  call r10
0xe804318  mov rax,[rcx]
0xe80431b  mov rax,[rax+8]
0xe80431f  mov r10,[0xF99FFA0]
0xe80433d  call r10
0xe80438b  mov rax,[rcx]
0xe80438e  mov rax,[rax+8]
0xe804392  mov r10,[0xF99FFA0]
0xe8043b0  call r10
#endif

extern "C" void sub_e8041a0(void* a0) {
    // 0xe8041a0..0xe8041c1
    // push rbp; push rsi; push rdi; sub rsp,0x40; lea rbp,[rsp+0x40]
    void* rsi = a0;
    // 0xe8041b7..0xe8041c1
    void** p = (void**)((char*)rsi + 8);
    void* rdx = *p;
    void* rcx = rdx ? *(void**)rdx : nullptr;
    if (!rcx) goto loc_217;
    // loop
    for (;;) {
        void* rdi = *(void**)((char*)rdx + 0x10);
        void* data = *(void**)0x12ADF800;
        if (data) {
            void** vtbl = *(void***)data;
            auto fn = (void(*)(void*,void*,void*,void*,void*,int,void*))vtbl[1]; // [rax+8]
            // call r10 = data_f99ffa0 = sub_eea6040
            void* r10 = *(void**)0xF99FFA0;
            // emulate call via slot
            ((void(*)(void*,void*,void*,void*,void*,int,void*))r10)(data, nullptr, nullptr, nullptr, nullptr, 0, nullptr);
        }
        rdx = rdi;
        if (!rdi) break;
    }
loc_217:
    // 0xe804217..0xe804223
    *(void**)((char*)rsi + 0x10) = rdx;
    // ...
    (void)rcx;
}

// LIFT_FN registry entry placeholder
// native::registry::register_fn("sub_e8041a0", 0xe8041a0, &sub_e8041a0);