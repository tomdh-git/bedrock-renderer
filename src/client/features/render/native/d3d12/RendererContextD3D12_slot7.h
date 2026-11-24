#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// LIFT 0xe834c50 size 0x1d8 1.26.62.01 RendererContextD3D12 base slot 7
// Layout constants recovered from disassembly of sub_e834c50 [V].
// Every offset appears as an instruction [reg+off] in the listing.

// ---- Data slots (RIP-relative addresses) [V] ----
static constexpr std::uintptr_t kSlot_vftable_f086408      = 0xF086408;     // lea rax,[0xF086408]              0xe834c68
static constexpr std::uintptr_t kSlot_global_1233E1A8      = 0x1233E1A8;    // mov rcx,[0x1233E1A8]             0xe834cc7
static constexpr std::uintptr_t kSlot_f99ffa0              = 0xF99FFA0;     // call qword ptr [0xF99FFA0]       0xe834cda (sub_eea6040 = jmp rax thunk)
static constexpr std::uintptr_t kSlot_f9a70c0              = 0xF9A70C0;     // call qword ptr [0xF9A70C0]       0xe834cf6
static constexpr std::uintptr_t kSlot_f9a72b0              = 0xF9A72B0;     // call qword ptr [0xF9A72B0]       0xe834d1f
static constexpr std::uintptr_t kSlot_f9a70d8              = 0xF9A70D8;     // call qword ptr [0xF9A70D8]       0xe834d3e
static constexpr std::uintptr_t kSlot_f9a7120              = 0xF9A7120;     // call qword ptr [0xF9A7120]       0xe834d60
static constexpr std::uintptr_t kSlot_f9a7268              = 0xF9A7268;     // call qword ptr [0xF9A7268]       0xe834d6f
static constexpr std::uintptr_t kSlot_f9a7138              = 0xF9A7138;     // call qword ptr [0xF9A7138]       0xe834d88
static constexpr std::uintptr_t kSlot_f9a7400              = 0xF9A7400;     // mov rdi,[0xF9A7400]              0xe834d29
static constexpr std::uintptr_t kSlot_f9a7240              = 0xF9A7240;     // mov rax,[0xF9A7240]              0xe834d4a
static constexpr std::uintptr_t kData_f4eded0              = 0xF4EDED0;     // lea rax,[0xF4EDED0]              0xe834cfd
static constexpr std::uintptr_t kData_f81f125              = 0xF81F125;     // lea rdx,[0xF81F125]              0xe834d81

// ---- RendererContextD3D12 (rcx / ctx) field offsets [V] ----
static constexpr std::size_t kCtxVftable          = 0x00;  // mov [rcx],rax                0xe834c6f
static constexpr std::size_t kCtxField18          = 0x18;  // mov [rsi+0x18],rax           0xe834c7a
static constexpr std::size_t kCtxField20          = 0x20;  // lea rax,[rsi+0x20]           0xe834c7e (zeroed 16B)
static constexpr std::size_t kCtxField30          = 0x30;  // mov qword ptr [rsi+0x30],0   0xe834c8d
static constexpr std::size_t kCtxField38          = 0x38;  // mov qword ptr [rsi+0x38],0xF 0xe834c95
static constexpr std::size_t kCtxField40          = 0x40;  // lea rax,[rsi+0x40]           0xe834c9d (zeroed 16B)
static constexpr std::size_t kCtxField50          = 0x50;  // mov qword ptr [rsi+0x50],0   0xe834ca9
static constexpr std::size_t kCtxField58          = 0x58;  // mov qword ptr [rsi+0x58],7   0xe834cb1
static constexpr std::size_t kCtxField68          = 0x68;  // mov word ptr [rsi+0x68],0    0xe834cb9
static constexpr std::size_t kCtxField6A          = 0x6A;  // mov byte ptr [rsi+0x6A],0    0xe834cc3
static constexpr std::size_t kCtxField60          = 0x60;  // mov qword ptr [rax+0x60],0   0xe834d0f
static constexpr std::size_t kCtxField08          = 0x08;  // mov [rax+8],rbx              0xe834d17
static constexpr std::size_t kCtxField20_2        = 0x20;  // mov dword ptr [rsi+0x20],0   0xe834d76 (on rsi obj)
static constexpr std::size_t kCtxField28          = 0x28;  // lea rcx,[rsi+0x28]           0xe834d7d (on rsi obj)
static constexpr std::size_t kCtxField70          = 0x70;  // mov qword ptr [rdi+0x70],0   0xe834e04

static_assert(kCtxField08 < kCtxField18, "e834c50: field 0x08 before 0x18");
static_assert(kCtxField18 < kCtxField20, "e834c50: field 0x18 before 0x20");
static_assert(kCtxField20 + 16 == kCtxField30, "e834c50: 16-byte zero at 0x20");
static_assert(kCtxField30 + 8 == kCtxField38, "e834c50: field 0x30 then 0x38");
static_assert(kCtxField38 + 8 == kCtxField40, "e834c50: field 0x38 then 0x40");
static_assert(kCtxField40 + 16 == kCtxField50, "e834c50: 16-byte zero at 0x40");
static_assert(kCtxField50 + 8 == kCtxField58, "e834c50: field 0x50 then 0x58");
static_assert(kCtxField58 + 0x10 == kCtxField68, "e834c50: field 0x58 then 0x68");
static_assert(kCtxField68 + 2 == kCtxField6A, "e834c50: word at 0x68 then byte at 0x6A");
static_assert(kCtxField60 == 0x60, "e834c50: field 0x60 explicit");
static_assert(kCtxField70 == 0x70, "e834c50: field 0x70 explicit");

// ---- Global data at 0x1233E1A8 field offsets [V] ----
static constexpr std::size_t kGlobal1233E1A8_field0 = 0x00;  // mov rax,[rcx]                0xe834cce
static constexpr std::size_t kGlobal1233E1A8_field8 = 0x08;  // mov rax,[rax+8]              0xe834cd1

// ---- Object from slot 0xF9A7400 field offsets [V] ----
static constexpr std::size_t kRsiObject_field0 = 0x00;       // mov r8,[rdi]                 0xe834d30
static constexpr std::size_t kRsiObject_field8 = 0x08;       // cmp qword ptr [rdi],0        0xe834d44

// ---- Object from slot 0xF9A7240 field offsets [V] ----
static constexpr std::size_t kRaxObject_field0 = 0x00;       // movsxd rcx,[rax]             0xe834d51

// ---- s_renderD3D12-like object field offsets [V] ----
static constexpr std::size_t kRenderField18 = 0x18;          // mov rcx,[rax+0x18]           0xe834d1b, 0xe834d92

// ---- Signature and registry ----
extern "C" void* RendererContextD3D12_slot7(void* rcx);

// LIFT_FN registration (per RENDER_NATIVE_SPEC.md section 1.4)
inline constexpr struct {
    const char* name = "RendererContextD3D12_slot7";
    const char* sig_name = "sub_e834c50";
    std::uintptr_t known_rva = 0xe834c50;
    int mode = 0; // Off
} LIFT_FN_RendererContextD3D12_slot7;

} // namespace native