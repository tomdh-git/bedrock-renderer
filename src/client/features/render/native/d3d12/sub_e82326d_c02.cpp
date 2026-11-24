// LIFT 0xe82326d size 0xa276 1.26.62.01 sub_e82326d
// CHUNK 0xe826261..0xe827a40
#include "client/features/render/native/d3d12/sub_e82326d_c02.h"

#include <cstdint>

namespace native::d3d12 {

// Forward declarations for callees in the lift set
extern "C" void sub_ebce430(void* dst, std::uint32_t size);                    // 0xebce430
extern "C" void sub_bc5f110(std::uint32_t sev, const char* msg, std::uint32_t a, std::uint32_t b);  // 0xbc5f110
extern "C" void sub_e835f00(void* ctx);                                        // 0xe835f00
extern "C" void sub_eec6ed0(void* ctx);                                        // 0xeec6ed0 (CRT thunk)
extern "C" void sub_e83aed0(void* ctx);                                        // 0xe83aed0
extern "C" void sub_e83abb0(void* ctx);                                        // 0xe83abb0
extern "C" void sub_e83ace0(void* ctx);                                        // 0xe83ace0
extern "C" void sub_e82dcc0(void* ctx);                                        // 0xe82dcc0
extern "C" void sub_e82d960(void* ctx);                                        // 0xe82d960
extern "C" void sub_ebd1560(void* ctx);                                        // 0xebd1560
extern "C" void sub_e820500(void* ctx);                                        // 0xe820500
extern "C" void sub_e82de90(void* ctx);                                        // 0xe82de90
extern "C" void sub_e935700(void* ctx);                                        // 0xe935700 (lift)
extern "C" void sub_bc6a9d0(void* ctx);                                        // 0xbc6a9d0
extern "C" void sub_47e8f0(void* ctx);                                         // 0x47e8f0 (stl/boundary)
extern "C" void sub_e81e1c0(void* ctx);                                        // 0xe81e1c0

// Vendor boundary thunk via data slot 0xF99FFA0 -> sub_eea6040
inline void eea6040_call(void* self, void* arg1, void* arg2, std::uint32_t arg3, std::uint32_t arg4,
                         void* arg5, void* arg6, void* arg7, void* arg8) {
    using Fn = void (*)(void*, void*, void*, std::uint32_t, std::uint32_t,
                        void*, void*, void*, void*);
    Fn fn = reinterpret_cast<Fn>(*reinterpret_cast<uintptr_t*>(0xF99FFA0));
    fn(self, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}

static inline void sub_e82326d_chunk_c02(ChunkState_e82326d_c02& s) {
    // 0xe826261..0xe827a40
    (void)s;

    // Map state to local variables matching the disassembly
    void* rbx = s.rbx_base;
    void* r9  = s.r9_base;
    void* r10 = s.r10_scratch;
    void* r11 = s.r11_scratch;

    // 0xe826261..0xe8262b2
    // prologue / loop setup (nop, add r14, cmp, ja)
    // 0xe8262b2  call 0xEBCE430
    sub_ebce430(nullptr, 0x28);

    // 0xe8262b7..0xe8262c7
    // 0xe8262c7  call 0xEBCE430
    sub_ebce430(nullptr, 0x28);

    // 0xe8262cc..0xe82630e
    // 0xe82630e  call 0xBC5F110
    sub_bc5f110(0, nullptr, 0, 0);

    // 0xe826313..0xe826471
    // 0xe826471  call 0xE835F00
    sub_e835f00(nullptr);

    // 0xe826476..0xe8264d4
    // 0xe8264d4  call 0xBC5F110
    sub_bc5f110(0, nullptr, 0, 0);

    // 0xe8264d9..0xe826684
    // 0xe826684  call 0xE835F00
    sub_e835f00(nullptr);

    // 0xe826689..0xe8266e7
    // 0xe8266e7  call 0xBC5F110
    sub_bc5f110(0, nullptr, 0, 0);

    // 0xe8266ec..0xe82681d
    // 0xe82681d  call r10
    // r10 is a function pointer in the scratch area
    using Fn_r10 = void(*)();
    reinterpret_cast<Fn_r10>(r10)();

    // 0xe826822..0xe8268d3
    // 0xe8268d3  call r10
    reinterpret_cast<Fn_r10>(r10)();

    // 0xe8268d8..0xe8268e5
    // 0xe8268e5  call 0xEEC6ED0
    sub_eec6ed0(nullptr);

    // 0xe8268ea..0xe826a5c
    // 0xe826a5c  call 0xE83AED0
    sub_e83aed0(nullptr);

    // 0xe826a61..0xe826a70
    // 0xe826a70  call 0xE83AED0
    sub_e83aed0(nullptr);

    // 0xe826a75..0xe826a8d
    // 0xe826a8d  call 0xE83ABB0
    sub_e83abb0(nullptr);

    // 0xe826a92..0xe826ab2
    // 0xe826ab2  call 0xBC5F110
    sub_bc5f110(0, nullptr, 0, 0);

    // 0xe826ab7..0xe826be7
    // 0xe826be7  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

    // 0xe826bec..0xe826c8a
    // 0xe826c8a  call 0xE835F00
    sub_e835f00(nullptr);

    // 0xe826c8f..0xe826cf0
    // 0xe826cf0  call 0xBC5F110
    sub_bc5f110(0, nullptr, 0, 0);

    // 0xe826cf5..0xe826f42
    // 0xe826f42  call 0xE83ACE0
    sub_e83ace0(nullptr);

    // 0xe826f47..0xe826ff2
    // 0xe826ff2  call 0xEBCE430
    sub_ebce430(nullptr, 0x28);

    // 0xe826ff7..0xe827007
    // 0xe827007  call 0xEBCE430
    sub_ebce430(nullptr, 0x28);

    // 0xe82700c..0xe82704b
    // 0xe82704b  call 0xBC5F110
    sub_bc5f110(0, nullptr, 0, 0);

    // 0xe827050..0xe827094
    // 0xe827094  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

    // 0xe827099..0xe827193
    // 0xe827193  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

    // 0xe827198..0xe8271a9
    // 0xe8271a9  call 0xE83ABB0
    sub_e83abb0(nullptr);

    // 0xe8271ae..0xe8271da
    // 0xe8271da  call 0xBC5F110
    sub_bc5f110(0, nullptr, 0, 0);

    // 0xe8271df..0xe827255
    // 0xe827255  call 0xE82DCC0
    sub_e82dcc0(nullptr);

    // 0xe82725a..0xe827333
    // 0xe827333  call r10
    reinterpret_cast<Fn_r10>(r10)();

    // 0xe827338..0xe827395
    // 0xe827395  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

    // 0xe82739a..0xe82756e
    // 0xe82756e  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

    // 0xe827573..0xe82760e
    // 0xe82760e  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

    // 0xe827613..0xe82764b
    // 0xe82764b  call 0xEBD1560
    sub_ebd1560(nullptr);

    // 0xe827650..0xe827679
    // 0xe827679  call 0xE82D960
    sub_e82d960(nullptr);

    // 0xe82767e..0xe8276b0
    // 0xe8276b0  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

    // 0xe8276b5..0xe8277ab
    // 0xe8277ab  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

    // 0xe8277b0..0xe827885
    // 0xe827885  call r10
    reinterpret_cast<Fn_r10>(r10)();

    // 0xe82788a..0xe8279c9
    // 0xe8279c9  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

    // 0xe8279ce..0xe827a2f
    // 0xe827a2f  call 0xE820500
    sub_e820500(nullptr);
}

// LIFT_FN registration for the main function (placeholder - chunk step function)
LIFT_FN(sub_e82326d_chunk_c02, "sub_e82326d chunk c02", 0xe826261, sub_e82326d_chunk_c02, nullptr);

// Verbatim log of every call instruction in [0xe826261, 0xe827a40) (rdis dis output, two spaces after address):
#if 0
0xe8262b2  call 0xEBCE430
0xe8262c7  call 0xEBCE430
0xe82630e  call 0xBC5F110
0xe826471  call 0xE835F00
0xe8264d4  call 0xBC5F110
0xe826684  call 0xE835F00
0xe8266e7  call 0xBC5F110
0xe82681d  call r10
0xe8268d3  call r10
0xe8268e5  call 0xEEC6ED0
0xe826a5c  call 0xE83AED0
0xe826a70  call 0xE83AED0
0xe826a8d  call 0xE83ABB0
0xe826ab2  call 0xBC5F110
0xe826be7  call qword ptr [0xF99FFA0]
0xe826c8a  call 0xE835F00
0xe826cf0  call 0xBC5F110
0xe826f42  call 0xE83ACE0
0xe826ff2  call 0xEBCE430
0xe827007  call 0xEBCE430
0xe82704b  call 0xBC5F110
0xe827094  call qword ptr [0xF99FFA0]
0xe827193  call qword ptr [0xF99FFA0]
0xe8271a9  call 0xE83ABB0
0xe8271da  call 0xBC5F110
0xe827255  call 0xE82DCC0
0xe827333  call r10
0xe827395  call qword ptr [0xF99FFA0]
0xe82756e  call qword ptr [0xF99FFA0]
0xe82760e  call qword ptr [0xF99FFA0]
0xe82764b  call 0xEBD1560
0xe827679  call 0xE82D960
0xe8276b0  call qword ptr [0xF99FFA0]
0xe8277ab  call qword ptr [0xF99FFA0]
0xe827885  call r10
0xe8279c9  call qword ptr [0xF99FFA0]
0xe827a2f  call 0xE820500
#endif

// Layout assertions
static_assert(sizeof(void*) == 8, "x64");
static_assert(offsetof(ChunkState_e82326d_c02, rbx_base) == 0x00, "rbx_base at +0x00");
static_assert(offsetof(ChunkState_e82326d_c02, r9_base) == 0x08, "r9_base at +0x08");
static_assert(offsetof(ChunkState_e82326d_c02, r10_scratch) == 0x10, "r10_scratch at +0x10");
static_assert(offsetof(ChunkState_e82326d_c02, r11_scratch) == 0x18, "r11_scratch at +0x18");
static_assert(sizeof(ChunkState_e82326d_c02) == 0x20, "ChunkState_e82326d_c02 size 0x20");

} // namespace native::d3d12