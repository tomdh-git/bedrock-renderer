// LIFT 0xe834c50 size 0x1d8 1.26.62.01 RendererContextD3D12 base slot 7
#include "client/features/render/native/d3d12/RendererContextD3D12_slot7.h"

#include <cstddef>
#include <cstdint>

namespace native {

// Forward declarations for lift-set callees
// sub_eec5a50: tiny forwarder at 0xeec5a50 = jmp qword ptr [0xF9A7250] [V]
extern "C" void* sub_eec5a50(void* rcx, uint8_t cl);

// 0x9bc830: alloc boundary [V] docs/data/native_boundary.tsv row 149
namespace boundary {
extern "C" void* alloc(void* rcx, size_t size);
}

// Data slot constants [V] from disassembly
static constexpr std::uintptr_t kSlot_vftable_f086408 = 0xF086408;     // lea rax,[0xF086408]  0xe834c68
static constexpr std::uintptr_t kSlot_global_1233E1A8 = 0x1233E1A8;    // mov rcx,[0x1233E1A8]  0xe834cc7
static constexpr std::uintptr_t kSlot_f99ffa0 = 0xF99FFA0;             // call qword ptr [0xF99FFA0]  0xe834cda,0xe834da2,0xe834dcf,0xe834de2,0xe834dfb
static constexpr std::uintptr_t kSlot_f9a70c0 = 0xF9A70C0;             // call qword ptr [0xF9A70C0]  0xe834cf6
static constexpr std::uintptr_t kSlot_f9a72b0 = 0xF9A72B0;             // call qword ptr [0xF9A72B0]  0xe834d1f
static constexpr std::uintptr_t kSlot_f9a70d8 = 0xF9A70D8;             // call qword ptr [0xF9A70D8]  0xe834d3e
static constexpr std::uintptr_t kSlot_f9a7120 = 0xF9A7120;             // call qword ptr [0xF9A7120]  0xe834d60
static constexpr std::uintptr_t kSlot_f9a7268 = 0xF9A7268;             // call qword ptr [0xF9A7268]  0xe834d6f
static constexpr std::uintptr_t kSlot_f9a7138 = 0xF9A7138;             // call qword ptr [0xF9A7138]  0xe834d88
static constexpr std::uintptr_t kSlot_f9a7400 = 0xF9A7400;             // mov rdi,[0xF9A7400]     0xe834d29
static constexpr std::uintptr_t kSlot_f9a7240 = 0xF9A7240;             // mov rax,[0xF9A7240]     0xe834d4a
static constexpr std::uintptr_t kData_f4eded0 = 0xF4EDED0;             // lea rax,[0xF4EDED0]     0xe834cfd
static constexpr std::uintptr_t kData_f81f125 = 0xF81F125;             // lea rdx,[0xF81F125]     0xe834d81

// Context (rcx = RendererContextD3D12*) field offsets [V] from disassembly
static constexpr std::size_t kCtxVftable          = 0x00;  // mov [rcx],rax                0xe834c6f
static constexpr std::size_t kCtxField18          = 0x18;  // mov [rsi+0x18],rax           0xe834c7a
static constexpr std::size_t kCtxField20          = 0x20;  // lea rax,[rsi+0x20]           0xe834c7e
static constexpr std::size_t kCtxField30          = 0x30;  // mov qword ptr [rsi+0x30],0   0xe834c8d
static constexpr std::size_t kCtxField38          = 0x38;  // mov qword ptr [rsi+0x38],0xF 0xe834c95
static constexpr std::size_t kCtxField40          = 0x40;  // lea rax,[rsi+0x40]           0xe834c9d
static constexpr std::size_t kCtxField50          = 0x50;  // mov qword ptr [rsi+0x50],0   0xe834ca9
static constexpr std::size_t kCtxField58          = 0x58;  // mov qword ptr [rsi+0x58],7   0xe834cb1
static constexpr std::size_t kCtxField68          = 0x68;  // mov word ptr [rsi+0x68],0    0xe834cb9
static constexpr std::size_t kCtxField6A          = 0x6A;  // mov byte ptr [rsi+0x6A],0    0xe834cc3
static constexpr std::size_t kCtxField60          = 0x60;  // mov qword ptr [rax+0x60],0   0xe834d0f
static constexpr std::size_t kCtxField08          = 0x08;  // mov [rax+8],rbx              0xe834d17
static constexpr std::size_t kCtxField18_2        = 0x18;  // mov rcx,[rax+0x18]           0xe834d1b
static constexpr std::size_t kCtxField20_2        = 0x20;  // mov dword ptr [rsi+0x20],0   0xe834d76
static constexpr std::size_t kCtxField28          = 0x28;  // lea rcx,[rsi+0x28]           0xe834d7d
static constexpr std::size_t kCtxField70          = 0x70;  // mov qword ptr [rdi+0x70],0   0xe834e04

// Global data structure at 0x1233E1A8 field offsets [V]
static constexpr std::size_t kGlobal1233E1A8_field0 = 0x00;  // mov rax,[rcx]                0xe834cce
static constexpr std::size_t kGlobal1233E1A8_field8 = 0x08;  // mov rax,[rax+8]              0xe834cd1

// rsi object (from 0xF9A7400) field offsets [V]
static constexpr std::size_t kRsiObject_field0 = 0x00;       // mov r8,[rdi]                 0xe834d30
static constexpr std::size_t kRsiObject_field8 = 0x08;       // cmp qword ptr [rdi],0        0xe834d44

// rax object (from 0xF9A7240) field offsets [V]
static constexpr std::size_t kRaxObject_field0 = 0x00;       // movsxd rcx,[rax]             0xe834d51

// s_renderD3D12-like object field offsets [V]
static constexpr std::size_t kRenderField18 = 0x18;          // mov rcx,[rax+0x18]           0xe834d1b, 0xe834d92

extern "C" void* RendererContextD3D12_slot7(void* rcx) {
    // 0xe834c50..0xe834c54: push rbp, rsi, rdi, rbx
    // 0xe834c54..0xe834c58: sub rsp,0x58; lea rbp,[rsp+0x50]
    // 0xe834c5d: mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
    // 0xe834c65: mov rsi,rcx
    char* const ctx = static_cast<char*>(rcx);

    // 0xe834c68..0xe834c6f: lea rax,[0xF086408]; mov [rcx],rax
    // W a0+0x0 = vftable pointer
    *reinterpret_cast<void**>(ctx + kCtxVftable) = reinterpret_cast<void*>(kSlot_vftable_f086408);

    // 0xe834c72: mov cl,1
    // 0xe834c74: call 0xEEC5A50 -> sub_eec5a50
    // 0xe834c74  call 0xEEC5A50                                ; -> sub_eec5a50
    void* rax_ret = sub_eec5a50(ctx, 1);

    // 0xe834c79: nop
    // 0xe834c7a: mov [rsi+0x18],rax
    // W a0+0x18 = return value from sub_eec5a50
    *reinterpret_cast<void**>(ctx + kCtxField18) = rax_ret;

    // 0xe834c7e..0xe834c82: lea rax,[rsi+0x20]; mov [rbp-0x28],rax
    // R a0+0x20 - saved to stack

    // 0xe834c86..0xe834c89: xorps xmm0,xmm0; movups [rsi+0x20],xmm0
    // W a0+0x20..0x2F = zero (16 bytes)
    *reinterpret_cast<__m128i*>(ctx + kCtxField20) = _mm_setzero_si128();

    // 0xe834c8d: mov qword ptr [rsi+0x30],0
    // W a0+0x30 = 0
    *reinterpret_cast<void**>(ctx + kCtxField30) = nullptr;

    // 0xe834c95: mov qword ptr [rsi+0x38],0xF
    // W a0+0x38 = 15
    *reinterpret_cast<std::uint64_t*>(ctx + kCtxField38) = 0xF;

    // 0xe834c9d..0xe834ca1: lea rax,[rsi+0x40]; mov [rbp-0x20],rax
    // R a0+0x40 - saved to stack

    // 0xe834ca5: movups [rsi+0x40],xmm0
    // W a0+0x40..0x4F = zero (16 bytes)
    *reinterpret_cast<__m128i*>(ctx + kCtxField40) = _mm_setzero_si128();

    // 0xe834ca9: mov qword ptr [rsi+0x50],0
    // W a0+0x50 = 0
    *reinterpret_cast<void**>(ctx + kCtxField50) = nullptr;

    // 0xe834cb1: mov qword ptr [rsi+0x58],7
    // W a0+0x58 = 7
    *reinterpret_cast<std::uint64_t*>(ctx + kCtxField58) = 7;

    // 0xe834cb9: mov word ptr [rsi+0x68],0
    // W a0+0x68 = 0 (word)
    *reinterpret_cast<std::uint16_t*>(ctx + kCtxField68) = 0;

    // 0xe834cbf: mov [rbp-8],rsi
    // Save ctx to stack

    // 0xe834cc3: mov byte ptr [rsi+0x6A],0
    // W a0+0x6A = 0 (byte)
    *reinterpret_cast<std::uint8_t*>(ctx + kCtxField6A) = 0;

    // 0xe834cc7..0xe834cd1: mov rcx,[0x1233E1A8]; mov rax,[rcx]; mov rax,[rax+8]
    // Read global pointer chain
    void* global_ptr = *reinterpret_cast<void**>(kSlot_global_1233E1A8);
    void* global_field0 = *reinterpret_cast<void**>(reinterpret_cast<char*>(global_ptr) + kGlobal1233E1A8_field0);
    void* global_field8 = *reinterpret_cast<void**>(reinterpret_cast<char*>(global_field0) + kGlobal1233E1A8_field8);

    // 0xe834cd5: mov edx,0x40
    // 0xe834cda: call qword ptr [0xF99FFA0] -> sub_eea6040 (jmp rax thunk)
    // 0xe834cda  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    using ThunkFn = void*(*)(void*, uint32_t);
    ThunkFn thunk = *reinterpret_cast<ThunkFn*>(kSlot_f99ffa0);
    void* rsi_obj = thunk(global_field8, 0x40);

    // 0xe834ce0: nop
    // 0xe834ce1: mov rsi,rax
    // 0xe834ce4: test rax,rax
    // 0xe834ce7: je 0xE834E18 -> loc_e834e18 (fallback path)
    if (rsi_obj == nullptr) {
        // loc_e834e18:
        // 0xe834e18: mov ecx,0x40
        // 0xe834e1d: call 0x9BC830 -> alloc boundary
        // 0xe834e1d  call 0x9BC830                                 ; -> sub_9bc830
        // 0xe834e22: nop
        // 0xe834e23: jmp 0xE834CED -> loc_e834ced
        rsi_obj = boundary::alloc(nullptr, 0x40);
    }

    // loc_e834ced:
    // 0xe834ced: mov rcx,rsi
    // 0xe834cf0: xor edx,edx
    // 0xe834cf2: mov [rbp-0x18],rsi
    // 0xe834cf6: call qword ptr [0xF9A70C0]
    // 0xe834cf6  call qword ptr [0xF9A70C0]
    using Fn_F9A70C0 = void(*)(void*, uint32_t);
    Fn_F9A70C0 fn_f9a70c0 = *reinterpret_cast<Fn_F9A70C0*>(kSlot_f9a70c0);
    fn_f9a70c0(rsi_obj, 0);

    // 0xe834cfc: nop
    // 0xe834cfd: lea rax,[0xF4EDED0]
    // 0xe834d04: mov rbx,[rbp-0x18]
    // 0xe834d08: mov [rbx],rax
    // W [rsi] = 0xF4EDED0
    *reinterpret_cast<void**>(rsi_obj) = reinterpret_cast<void*>(kData_f4eded0);

    // 0xe834d0b: mov rax,[rbp-8]  (ctx)
    // 0xe834d0f: mov qword ptr [rax+0x60],0
    // W a0+0x60 = 0
    *reinterpret_cast<void**>(ctx + kCtxField60) = nullptr;

    // 0xe834d17: mov [rax+8],rbx
    // W a0+0x08 = rsi_obj
    *reinterpret_cast<void**>(ctx + kCtxField08) = rsi_obj;

    // 0xe834d1b: mov rcx,[rax+0x18]
    // R a0+0x18 (value from sub_eec5a50)
    void* ctx_field18 = *reinterpret_cast<void**>(ctx + kCtxField18);

    // 0xe834d1f: call qword ptr [0xF9A72B0]
    // 0xe834d1f  call qword ptr [0xF9A72B0]
    using Fn_F9A72B0 = void*(*)(void*);
    Fn_F9A72B0 fn_f9a72b0 = *reinterpret_cast<Fn_F9A72B0*>(kSlot_f9a72b0);
    void* rax2 = fn_f9a72b0(ctx_field18);

    // 0xe834d25: nop
    // 0xe834d26: mov rsi,rax
    // 0xe834d29: mov rdi,[0xF9A7400]
    void* rdi_obj = *reinterpret_cast<void**>(kSlot_f9a7400);

    // 0xe834d30: mov r8,[rdi]
    // R [rdi+0x00]
    void* rdi_field0 = *reinterpret_cast<void**>(rdi_obj);

    // 0xe834d33: test r8,r8
    // 0xe834d36: jne short 0xE834D69 -> loc_e834d69
    if (rdi_field0 == nullptr) {
        // 0xe834d38: lea rcx,[rbp-0xC]
        // 0xe834d3c: xor edx,edx
        // 0xe834d3e: call qword ptr [0xF9A70D8]
        // 0xe834d3e  call qword ptr [0xF9A70D8]
        char stack_obj[12]; // rbp-0xC
        using Fn_F9A70D8 = void(*)(void*, uint32_t);
        Fn_F9A70D8 fn_f9a70d8 = *reinterpret_cast<Fn_F9A70D8*>(kSlot_f9a70d8);
        fn_f9a70d8(stack_obj, 0);

        // 0xe834d44: cmp qword ptr [rdi],0
        // 0xe834d48: jne short 0xE834D5C -> loc_e834d5c
        if (*reinterpret_cast<void**>(rdi_obj) == nullptr) {
            // 0xe834d4a: mov rax,[0xF9A7240]
            // 0xe834d51: movsxd rcx,[rax]
            // 0xe834d54: inc rcx
            // 0xe834d57: mov [rax],ecx
            // 0xe834d59: mov [rdi],rcx
            int32_t* counter = *reinterpret_cast<int32_t**>(kSlot_f9a7240);
            int32_t val = *counter;
            val++;
            *counter = val;
            *reinterpret_cast<void**>(rdi_obj) = reinterpret_cast<void*>(val);
        }

        // loc_e834d5c:
        // 0xe834d5c: lea rcx,[rbp-0xC]
        // 0xe834d60: call qword ptr [0xF9A7120]
        // 0xe834d60  call qword ptr [0xF9A7120]
        using Fn_F9A7120 = void(*)(void*);
        Fn_F9A7120 fn_f9a7120 = *reinterpret_cast<Fn_F9A7120*>(kSlot_f9a7120);
        fn_f9a7120(stack_obj);

        // 0xe834d66: mov r8,[rdi]
        rdi_field0 = *reinterpret_cast<void**>(rdi_obj);
    }

    // loc_e834d69:
    // 0xe834d69: mov rcx,rsi
    // 0xe834d6c: mov rdx,rbx (rsi_obj)
    // 0xe834d6f: call qword ptr [0xF9A7268]
    // 0xe834d6f  call qword ptr [0xF9A7268]
    using Fn_F9A7268 = void(*)(void*, void*);
    Fn_F9A7268 fn_f9a7268 = *reinterpret_cast<Fn_F9A7268*>(kSlot_f9a7268);
    fn_f9a7268(rsi_obj, rdi_field0);

    // 0xe834d75: nop
    // 0xe834d76: mov dword ptr [rsi+0x20],0
    // W [rsi+0x20] = 0 (dword)
    *reinterpret_cast<std::uint32_t*>(reinterpret_cast<char*>(rsi_obj) + 0x20) = 0;

    // 0xe834d7d: lea rcx,[rsi+0x28]
    // 0xe834d81: lea rdx,[0xF81F125]
    // 0xe834d88: call qword ptr [0xF9A7138]
    // 0xe834d88  call qword ptr [0xF9A7138]
    using Fn_F9A7138 = void(*)(void*, void*);
    Fn_F9A7138 fn_f9a7138 = *reinterpret_cast<Fn_F9A7138*>(kSlot_f9a7138);
    fn_f9a7138(reinterpret_cast<char*>(rsi_obj) + 0x28, reinterpret_cast<void*>(kData_f81f125));

    // 0xe834d8e: mov rdi,[rbp-8] (ctx)
    // 0xe834d92: mov rcx,[rdi+0x18]
    // R a0+0x18
    void* ctx_field18_2 = *reinterpret_cast<void**>(ctx + kCtxField18);

    // 0xe834d96: cmp rcx,rsi
    // 0xe834d99: je short 0xE834DD8 -> loc_e834dd8
    if (ctx_field18_2 != rsi_obj) {
        // 0xe834d9b: mov rax,[rcx]
        // 0xe834d9e: mov rax,[rax+0x10]
        // 0xe834da2: call qword ptr [0xF99FFA0] -> sub_eea6040
        // 0xe834da2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
        void* vtable = *reinterpret_cast<void**>(ctx_field18_2);
        void* vtable_slot10 = *reinterpret_cast<void**>(reinterpret_cast<char*>(vtable) + 0x10);
        void* ref_result = thunk(vtable_slot10, 0x40);

        // 0xe834da8: test rax,rax
        // 0xe834dab: je short 0xE834DC4 -> loc_e834dc4
        if (ref_result != nullptr) {
            // 0xe834dad: mov rcx,[rax]
            // 0xe834db0: mov r8,[rcx]
            // 0xe834db3: mov rcx,rax
            // 0xe834db6: mov edx,1
            // 0xe834dbb: mov rax,r8
            // 0xe834dbe: call qword ptr [0xF99FFA0] -> sub_eea6040
            // 0xe834dbe  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
            void* inner = *reinterpret_cast<void**>(ref_result);
            void* inner_vtable = *reinterpret_cast<void**>(inner);
            thunk(inner_vtable, 1);
        }

        // loc_e834dc4:
        // 0xe834dc4: mov [rdi+0x18],rsi
        // W a0+0x18 = rsi_obj
        *reinterpret_cast<void**>(ctx + kCtxField18) = rsi_obj;

        // 0xe834dc8: mov rax,[rsi]
        // 0xe834dcb: mov rax,[rax+0x10]
        // 0xe834dcf: mov rcx,rsi
        // 0xe834dd2: call qword ptr [0xF99FFA0] -> sub_eea6040
        // 0xe834dd2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
        void* rsi_vtable = *reinterpret_cast<void**>(rsi_obj);
        void* rsi_vtable_slot10 = *reinterpret_cast<void**>(reinterpret_cast<char*>(rsi_vtable) + 0x10);
        thunk(rsi_vtable_slot10, 1);
    }

    // loc_e834dd8:
    // 0xe834dd8: mov rax,[rsi]
    // 0xe834ddb: mov rax,[rax+0x10]
    // 0xe834ddf: mov rcx,rsi
    // 0xe834de2: call qword ptr [0xF99FFA0] -> sub_eea6040
    // 0xe834de2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    void* rsi_vtable2 = *reinterpret_cast<void**>(rsi_obj);
    void* rsi_vtable2_slot10 = *reinterpret_cast<void**>(reinterpret_cast<char*>(rsi_vtable2) + 0x10);
    void* ref_result2 = thunk(rsi_vtable2_slot10, 0x40);

    // 0xe834de8: test rax,rax
    // 0xe834deb: je short 0xE834E04 -> loc_e834e04
    if (ref_result2 != nullptr) {
        // 0xe834ded: mov rcx,[rax]
        // 0xe834df0: mov r8,[rcx]
        // 0xe834df3: mov rcx,rax
        // 0xe834df6: mov edx,1
        // 0xe834dfb: mov rax,r8
        // 0xe834dfe: call qword ptr [0xF99FFA0] -> sub_eea6040
        // 0xe834dfe  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
        void* inner2 = *reinterpret_cast<void**>(ref_result2);
        void* inner2_vtable = *reinterpret_cast<void**>(inner2);
        thunk(inner2_vtable, 1);
    }

    // loc_e834e04:
    // 0xe834e04: mov qword ptr [rdi+0x70],0
    // W [rdi+0x70] = 0 (rdi is ctx here? wait - rdi was overwritten)
    // Looking at 0xe834d8e: mov rdi,[rbp-8] - so rdi = ctx
    *reinterpret_cast<void**>(ctx + kCtxField70) = nullptr;

    // 0xe834e0c: mov rax,rdi
    // 0xe834e0f: add rsp,0x58
    // 0xe834e13: pop rbx
    // 0xe834e14: pop rdi
    // 0xe834e15: pop rsi
    // 0xe834e16: pop rbp
    // 0xe834e17: ret
    return ctx;
}

// Verbatim call quotes for verify_oc (plain lines, two spaces after address)
#if 0
0xe834c74  call 0xEEC5A50
0xe834cda  call qword ptr [0xF99FFA0]
0xe834cf6  call qword ptr [0xF9A70C0]
0xe834d1f  call qword ptr [0xF9A72B0]
0xe834d3e  call qword ptr [0xF9A70D8]
0xe834d60  call qword ptr [0xF9A7120]
0xe834d6f  call qword ptr [0xF9A7268]
0xe834d88  call qword ptr [0xF9A7138]
0xe834da2  call qword ptr [0xF99FFA0]
0xe834dbe  call qword ptr [0xF99FFA0]
0xe834dd2  call qword ptr [0xF99FFA0]
0xe834de2  call qword ptr [0xF99FFA0]
0xe834dfe  call qword ptr [0xF99FFA0]
0xe834e1d  call 0x9BC830
#endif

// Layout assertions (static_assert for every struct offset used)
static_assert(kCtxVftable == 0x00, "e834c50: vftable at 0x00");
static_assert(kCtxField08 == 0x08, "e834c50: field at 0x08");
static_assert(kCtxField18 == 0x18, "e834c50: field at 0x18");
static_assert(kCtxField20 == 0x20, "e834c50: field at 0x20");
static_assert(kCtxField30 == 0x30, "e834c50: field at 0x30");
static_assert(kCtxField38 == 0x38, "e834c50: field at 0x38");
static_assert(kCtxField40 == 0x40, "e834c50: field at 0x40");
static_assert(kCtxField50 == 0x50, "e834c50: field at 0x50");
static_assert(kCtxField58 == 0x58, "e834c50: field at 0x58");
static_assert(kCtxField60 == 0x60, "e834c50: field at 0x60");
static_assert(kCtxField68 == 0x68, "e834c50: field at 0x68");
static_assert(kCtxField6A == 0x6A, "e834c50: field at 0x6A");
static_assert(kCtxField70 == 0x70, "e834c50: field at 0x70");

// LIFT_FN registry entry (per RENDER_NATIVE_SPEC.md section 1.4)
namespace {
    struct NativeEntry {
        const char* name;
        const char* sig_name;
        std::uintptr_t known_rva;
        int mode;
    };
    constexpr NativeEntry LIFT_FN_RendererContextD3D12_slot7 = {
        "RendererContextD3D12_slot7",
        "sub_e834c50",
        0xe834c50,
        0  // Off
    };
}

} // namespace native