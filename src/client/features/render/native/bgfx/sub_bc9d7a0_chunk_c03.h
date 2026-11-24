#pragma once
// LIFT 0xbc9d7a0 size 0x67db 1.26.62.01 VV frame-graph builder
// CHUNK 0xbca1080..0xbca2785 (TSV chunk-003, checklist part 4/5)
// Chunk state documented in docs/functions/bc9d7a0.md section 'Chunk state'.
#include <cstdint>

namespace native::bgfx {

// Forward declarations for callees in the lift set (exact ABI from their own dossiers).
extern "C" void sub_568ad40(void* ctx, void* item, void* key, void* val);
extern "C" void sub_568c420(void* ctx, void* item);
extern "C" void sub_5693a80(void* ctx, void* item);
extern "C" void sub_56b8630(void* ctx, void* item);
extern "C" void sub_56c9740(void* ctx);
extern "C" void sub_5679db0(void* ctx, void* key, void* val);
extern "C" void sub_6760450(void* a0, void* a1);
extern "C" void sub_bc039a0(void* a0, void* a1, void* a2, void* a3);
extern "C" void sub_bc03cd0(void* a0);
extern "C" void sub_bc04620(void* a0, void* a1);
extern "C" void sub_bc04bb0(void* a0, void* a1, void* a2);
extern "C" void sub_bc054a0(void* a0, void* a1);
extern "C" void sub_e869ff0(void* a0, void* a1);
extern "C" void sub_e86b370(void* a0, void* a1);
extern "C" void sub_e935700(void* ptr, std::size_t size);
extern "C" void sub_eec6de0(void* dst, const void* src, std::size_t n);
extern "C" void sub_eec6ec0(void* dst, const void* src, std::size_t n);

// Data slots (read at call time, exactly as the instruction does).
extern void* data_1233e1a8;   // 0x1233E1A8 allocator object pointer ([slot]->obj, obj+8 = alloc fn)
extern void* data_f9a8c78;    // 0xF9A8C78 abort/error handler function pointer
extern std::uint64_t data_12ae20e8;
extern std::uint64_t data_12ae20a8;
extern std::uint64_t data_12ae20f8;
extern std::uint64_t data_12ae20d8;
extern std::uint64_t data_12ae2138;
extern std::uint64_t data_12ae2128;
extern std::uint64_t data_12ae2118;
extern std::uint64_t data_12ae2108;
extern std::uint64_t data_12ae20c8;
extern std::uint64_t data_12ae2078;
extern std::uint64_t data_12ae2060;
extern std::uint64_t data_12ae2070;
extern std::uint64_t data_12ae2018;
extern std::uint64_t data_128c1a58;
extern std::uint64_t data_12ae1f60;
extern std::uint64_t data_12ae1f30;
extern std::uint64_t data_12ae1f98;
extern std::uint64_t data_12ae1f68;
extern std::uint64_t data_12ae1fd0;
extern std::uint64_t data_12ae1fa0;
extern std::uint64_t data_12ae2008;
extern std::uint64_t data_12ae1fd8;
extern std::uint64_t data_12ae2040;
extern std::uint64_t data_12ae2010;
extern std::uint64_t data_12ae2050;
extern std::uint64_t data_12ae22a8;
extern std::uint64_t data_12ae22a0;
extern std::uint64_t data_12ae2048;
extern std::uint32_t data_eec8060;   // float constant 0xEEC8060
extern std::uint64_t data_eec8068;   // double constant 0xEEC8068
extern std::uint64_t data_f51b04c;   // "LocalExposureApply" string
extern std::uint64_t data_f5f026c;   // "BilateralGrid" string
extern std::uint64_t data_f524d6e;   // "FilteredBilateralGridOutput" string
extern std::uint64_t data_f44b6d0;   // jump table base (4 entries)
extern std::uint64_t data_f44b650;   // vtable/function pointer constant
extern std::uint64_t data_f0b8810;   // float constant vector
extern std::uint64_t data_f221610;   // vtable/function pointer constant
extern std::uint64_t data_f44b620;   // vtable/function pointer constant
extern std::uint64_t data_f0e2d80;   // vtable/function pointer constant
extern std::uint64_t data_f44b600;   // vtable/function pointer constant

struct ChunkState_bc9d7a0_c03 {
    std::uint64_t rax;
    std::uint64_t rcx;
    std::uint64_t rdx;
    std::uint64_t r8;
    std::uint64_t r9;
    std::uint64_t r10;
    std::uint64_t r11;
    void* rbx;
    void* rsi;
    void* rdi;
    void* r12;
    void* r13;
    void* r14;
    void* r15;
    void* rbp;
    // Frame is 0x12A8 (sub rsp) + 0x40 pushes; rbp = rsp+0x80, so [rbp+0x12D8+]
    // is reachable. Sized to cover the max offset used in this chunk (0x1300).
    std::uint8_t stack[0x1400];
};

void sub_bc9d7a0_chunk03(ChunkState_bc9d7a0_c03& s);

} // namespace native::bgfx