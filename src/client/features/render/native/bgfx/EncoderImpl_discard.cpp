// LIFT 0xbc60d10 size 0x1fc 1.26.62.01 bgfx::EncoderImpl::discard
#include "client/features/render/native/bgfx/EncoderImpl_discard.h"
#include "client/features/render/native/Lift.h"

#include <cstring>
#include <cstdint>

namespace native {

// Layout assertions: every struct offset read or written by the function is a
// named constant tied to the real struct layout.
static_assert(offsetof(EncoderImpl, m_field40) == 0x40, "EncoderImpl::m_field40 must be at +0x40");
static_assert(offsetof(EncoderImpl, m_field60) == 0x60, "EncoderImpl::m_field60 must be at +0x60");
static_assert(offsetof(EncoderImpl, m_field68) == 0x68, "EncoderImpl::m_field68 must be at +0x68");
static_assert(offsetof(EncoderImpl, m_field70) == 0x70, "EncoderImpl::m_field70 must be at +0x70");
static_assert(offsetof(EncoderImpl, m_field80) == 0x80, "EncoderImpl::m_field80 must be at +0x80");
static_assert(offsetof(EncoderImpl, m_field90) == 0x90, "EncoderImpl::m_field90 must be at +0x90");
static_assert(offsetof(EncoderImpl, m_field98) == 0x98, "EncoderImpl::m_field98 must be at +0x98");
static_assert(offsetof(EncoderImpl, m_fieldA0) == 0xA0, "EncoderImpl::m_fieldA0 must be at +0xA0");
static_assert(offsetof(EncoderImpl, m_fieldA2) == 0xA2, "EncoderImpl::m_fieldA2 must be at +0xA2");
static_assert(offsetof(EncoderImpl, m_fieldA3) == 0xA3, "EncoderImpl::m_fieldA3 must be at +0xA3");
static_assert(offsetof(EncoderImpl, m_fieldA8) == 0xA8, "EncoderImpl::m_fieldA8 must be at +0xA8");
static_assert(offsetof(EncoderImpl, m_fieldAC) == 0xAC, "EncoderImpl::m_fieldAC must be at +0xAC");
static_assert(offsetof(EncoderImpl, m_fieldB4) == 0xB4, "EncoderImpl::m_fieldB4 must be at +0xB4");
static_assert(offsetof(EncoderImpl, m_fieldC0) == 0xC0, "EncoderImpl::m_fieldC0 must be at +0xC0");
static_assert(offsetof(EncoderImpl, m_fieldC8) == 0xC8, "EncoderImpl::m_fieldC8 must be at +0xC8");
static_assert(offsetof(EncoderImpl, m_fieldCC) == 0xCC, "EncoderImpl::m_fieldCC must be at +0xCC");
static_assert(offsetof(EncoderImpl, m_fieldD0) == 0xD0, "EncoderImpl::m_fieldD0 must be at +0xD0");
static_assert(offsetof(EncoderImpl, m_fieldD8) == 0xD8, "EncoderImpl::m_fieldD8 must be at +0xD8");
static_assert(offsetof(EncoderImpl, m_fieldDC) == 0xDC, "EncoderImpl::m_fieldDC must be at +0xDC");
static_assert(offsetof(EncoderImpl, m_fieldE0) == 0xE0, "EncoderImpl::m_fieldE0 must be at +0xE0");
static_assert(offsetof(EncoderImpl, m_fieldE2) == 0xE2, "EncoderImpl::m_fieldE2 must be at +0xE2");
static_assert(offsetof(EncoderImpl, m_fieldE3) == 0xE3, "EncoderImpl::m_fieldE3 must be at +0xE3");
static_assert(offsetof(EncoderImpl, m_sideTable) == 0x680, "EncoderImpl::m_sideTable must be at +0x680");
static_assert(offsetof(EncoderImpl, m_bindDirty) == 0x688, "EncoderImpl::m_bindDirty must be at +0x688");
static_assert(offsetof(EncoderImpl, m_discard) == 0x6AD, "EncoderImpl::m_discard must be at +0x6AD");

static_assert(offsetof(SideTable, m_entry) == 0x00, "SideTable::m_entry must be at +0x00");
static_assert(offsetof(SideTable, m_count) == 0x410, "SideTable::m_count must be at +0x410");
static_assert(sizeof(SideTable) == 0x414, "SideTable must be 0x414 bytes (65 entries plus the count)");

static_assert(offsetof(Binding, m_f00) == 0x00, "Binding::m_f00 must be at +0x00");
static_assert(offsetof(Binding, m_f0a) == 0x0A, "Binding::m_f0a must be at +0x0A");
static_assert(offsetof(Binding, m_f0c) == 0x0C, "Binding::m_f0c must be at +0x0C");
static_assert(offsetof(Binding, m_f13) == 0x13, "Binding::m_f13 must be at +0x13");
static_assert(offsetof(Binding, m_f14) == 0x14, "Binding::m_f14 must be at +0x14");
static_assert(offsetof(Binding, m_f1c) == 0x1C, "Binding::m_f1c must be at +0x1C");
static_assert(offsetof(Binding, m_f1e) == 0x1E, "Binding::m_f1e must be at +0x1E");
static_assert(offsetof(Binding, m_f27) == 0x27, "Binding::m_f27 must be at +0x27");
static_assert(sizeof(Binding) == 0x28, "Binding must be 0x28 bytes");

// [0x12ADF800] holds the process-wide allocator interface pointer.
inline void** globalAllocatorPtr() {
    return reinterpret_cast<void**>(RewriteRegistry::imageBase() + 0x12ADF800);
}

// The allocator's free is reached through an indirection gadget: [0xF99FFA0]
// holds the address of 0xeea6040, which is `jmp rax`; rax is loaded from the
// allocator object's vtable slot 1 ([rcx], then [rax+8]) just before the call,
// so the call is a virtual interface call, not a static callee.
using AllocatorFree = void (*)(void* allocator, void* ptr);

// rodata constant copied to encoder +0x80 (16 bytes at [0xF08EF70]: 00 00 00 00
// ff ff ff ff 00 00 00 00 ff ff ff ff).
static constexpr std::uint8_t kDrawDefaults16[16] = {
    0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
};

// 0xbc60d10..0xbc60e10
// Prologue (push r14/rsi/rdi/rbx, sub rsp,0x48, save xmm6) is implicit; the
// epilogue (restore xmm6, add rsp,0x48, pop, ret) is the function return.
extern "C" void EncoderImpl_discard(EncoderImpl* encoder) {
    // 0xbc60d21  mov byte ptr [rcx+0x6AD],0
    encoder->m_discard = 0;
    // 0xbc60d28  mov rax,0x10000500000001F / 0xbc60d32  mov [rcx+0x60],rax
    encoder->m_field60 = 0x01000050000001FULL;
    // 0xbc60d36  mov qword ptr [rcx+0x68],0
    encoder->m_field68 = 0;
    // 0xbc60d3e  xorps xmm0,xmm0 / 0xbc60d41  movaps [rcx+0x70],xmm0
    std::memset(encoder->m_field70, 0, 16);
    // 0xbc60d45  movaps xmm0,[0xF08EF70] / 0xbc60d4c  movaps [rcx+0x80],xmm0
    std::memcpy(encoder->m_field80, kDrawDefaults16, 16);
    // 0xbc60d53  mov rax,0x100000000 / 0xbc60d5d  mov [rcx+0x90],rax
    encoder->m_field90 = 0x100000000ULL;
    // 0xbc60d64  mov rax,0x1FFFF00000000 / 0xbc60d6e  mov [rcx+0x98],rax
    encoder->m_field98 = 0x0001FFFF00000000ULL;
    // 0xbc60d75  mov byte ptr [rcx+0xA2],0
    encoder->m_fieldA2 = 0;
    // 0xbc60d7c  mov word ptr [rcx+0xA0],0xFFFF
    encoder->m_fieldA0 = 0xFFFF;
    // 0xbc60d85  mov word ptr [rcx+0xA3],0xFF00
    encoder->m_fieldA3 = 0xFF00;
    // 0xbc60d8e  mov rax,0xFFFFFFFF00000000 / 0xbc60d98  mov [rcx+0x40],rax
    encoder->m_field40 = 0xFFFFFFFF00000000ULL;
    // 0xbc60d9c  mov qword ptr [rcx+0xB4],0xFFFFFFFFFFFFFFFF
    encoder->m_fieldB4 = 0xFFFFFFFFFFFFFFFFULL;
    // 0xbc60da7  mov dword ptr [rcx+0xA8],0x7FFFFFFF
    encoder->m_fieldA8 = 0x7FFFFFFF;
    // 0xbc60db1  mov qword ptr [rcx+0xAC],0
    encoder->m_fieldAC = 0;
    // 0xbc60dbc  mov qword ptr [rcx+0xC0],0
    encoder->m_fieldC0 = 0;
    // 0xbc60dc7  mov dword ptr [rcx+0xC8],0
    encoder->m_fieldC8 = 0;
    // 0xbc60dd1  mov qword ptr [rcx+0xD0],0
    encoder->m_fieldD0 = 0;
    // 0xbc60ddc  mov dword ptr [rcx+0xD8],0
    encoder->m_fieldD8 = 0;
    // 0xbc60de6  mov word ptr [rcx+0xE0],0
    encoder->m_fieldE0 = 0;
    // 0xbc60def  mov byte ptr [rcx+0xE2],0xFF
    encoder->m_fieldE2 = 0xFF;
    // 0xbc60df6  mov word ptr [rcx+0xCC],0xFFFF
    encoder->m_fieldCC = 0xFFFF;
    // 0xbc60dff  mov dword ptr [rcx+0xDC],0xFFFF0000
    encoder->m_fieldDC = 0xFFFF0000;
    // 0xbc60e09  mov byte ptr [rcx+0xE3],0
    encoder->m_fieldE3 = 0;

    // 0xbc60e10..0xbc60e65
    // rax runs 0x167, 0x18F, ..., 0x667 (33 values, stride 0x28); binding i is at
    // encoder + 0x140 + i*0x28. The je at 0xbc60e42 skips the second half of the
    // body on the last iteration (rax == 0x667).
    for (std::uint32_t i = 0;; ++i) {
        std::uint32_t rax = 0x167u + i * 0x28u;
        Binding* b = reinterpret_cast<Binding*>(
            reinterpret_cast<std::uint8_t*>(encoder) + kBindingBase + i * kBindingStride);
        // 0xbc60e20  mov word ptr [rsi+rax-0x1D],0xFFFF
        b->m_f13 = 0xFFFF;
        // 0xbc60e27  mov byte ptr [rsi+rax-0x14],0
        b->m_f0a = 0;
        // 0xbc60e2c  mov dword ptr [rsi+rax-0x27],0
        b->m_f00 = 0;
        // 0xbc60e34  mov dword ptr [rsi+rax-0x1B],0xFFFFFFFF
        b->m_f0c = 0xFFFFFFFFu;
        // 0xbc60e3c  cmp rax,0x667 / 0xbc60e42  je short 0xBC60E65
        if (rax == 0x667u) break;
        // 0xbc60e44  mov word ptr [rsi+rax-9],0xFFFF
        b->m_f1e = 0xFFFF;
        // 0xbc60e4b  mov byte ptr [rsi+rax],0
        b->m_f27 = 0;
        // 0xbc60e4f  mov dword ptr [rsi+rax-0x13],0
        b->m_f14 = 0;
        // 0xbc60e57  mov dword ptr [rsi+rax-7],0xFFFFFFFF
        b->m_f1c = 0xFFFFFFFFu;
    }

    // 0xbc60e65..0xbc60eec
    SideTable* table = encoder->m_sideTable;        // 0xbc60e65  mov rdi,[rsi+0x680]
    if (table != nullptr) {                         // 0xbc60e6c  test rdi,rdi / 0xbc60e6f  je 0xBC60EF6
        void* alloc = *globalAllocatorPtr();        // 0xbc60e75  mov rcx,[0x12ADF800]
        if (alloc != nullptr) {                     // 0xbc60e7c  test rcx,rcx / 0xbc60e7f  je short 0xBC60EDC
            for (std::uint32_t i = 0; i < kSideTableEntryCount; ++i) {
                SideTableEntry* entry = table->m_entry + i;
                if (alloc != nullptr) {             // 0xbc60ed3  test rcx,rcx / 0xbc60ed6  jne short 0xBC60E90
                    void* ptr = entry->m_ptr;       // 0xbc60e90  mov rdx,[r14]
                    void** vt = *reinterpret_cast<void**>(alloc);   // 0xbc60e93  mov rax,[rcx]
                    AllocatorFree freeFn =
                        reinterpret_cast<AllocatorFree>(vt[1]);     // 0xbc60e96  mov rax,[rax+8] (vtable slot 1 = free)
                    // 0xbc60eb1  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040 = `jmp rax`
                    freeFn(alloc, ptr);
                    alloc = *globalAllocatorPtr();  // 0xbc60eb7  mov rcx,[0x12ADF800]
                }
                // 0xbc60ebe  movups [r14],xmm6  (xmm6 = 0): zero the whole 16-byte entry
                entry->m_ptr = nullptr;
                entry->m_reserved = 0;
            }
        } else {
            // 0xbc60edc  mov r8d,0x410 / 0xbc60ee2  mov rcx,rdi / 0xbc60ee5  xor edx,edx
            // 0xbc60ee7  call 0xEEC6ED0   (import thunk jmp [0xF9A8AA8]: memset(table, 0, 0x410))
            std::memset(table, 0, kSideTableBytes);
        }
        // 0xbc60eec..0xbc60f0c  covers mov [rdi+0x410],0, m_bindDirty = 1, and the
        // epilogue (restore xmm6, add rsp,0x48, pop, ret) which is the return.
        table->m_count = 0;
    }
    // 0xbc60ef6  mov byte ptr [rsi+0x688],1
    encoder->m_bindDirty = 1;
}

static native::Footprint encoderImplDiscardFootprint(EncoderImpl* encoder) {
    native::Footprint fp;
    fp.push_back({encoder, 0x689});                 // all encoder bytes written by the function (+0x00..+0x688)
    if (encoder != nullptr && encoder->m_sideTable != nullptr)
        fp.push_back({encoder->m_sideTable, 0x414}); // side table entries (+0x00..+0x40F) and count (+0x410)
    return fp;
}

LIFT_FN(EncoderImpl_discard, "bgfx::Encoder::reset", 0xBC60D10, EncoderImpl_discard,
        &encoderImplDiscardFootprint);

} // namespace native
