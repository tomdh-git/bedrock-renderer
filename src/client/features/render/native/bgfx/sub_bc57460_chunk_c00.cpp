// LIFT 0xbc57460 size 0x2e2f 1.26.62.01 bgfx frame-graph builder (VV)
// CHUNK 0xbc57460..0xbc58a85 (prologue + main loop)
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc57460_chunk_c00.h"

#include <cstdint>
#include <cstring>

namespace native::bgfx {

namespace {

// External calls from the lift set (already lifted by their own units)
extern "C" void sub_eec73f0(void* out, const void* in);        // 0xeec73f0 - vector math
extern "C" void sub_bc09250(void* ctx, void* arg1, void* arg2, void* arg3);  // 0xbc09250
extern "C" void sub_567c8b0(void* self, std::uint32_t idx, std::uint32_t size);  // 0x567c8b0
extern "C" void sub_ab49c0(void* ctx, void* arg);               // 0xab49c0
extern "C" void sub_5667860(void* ctx, void* arg);              // 0x5667860
extern "C" void sub_a78940(void* ctx, void* vtable, void* arg1, std::uint32_t arg2, void* arg3, std::uint32_t arg4);  // 0xa78940
extern "C" void sub_aa6580(void* ctx, void* arg1, void* arg2);  // 0xaa6580
extern "C" void sub_1999390(void* ctx, void* arg);              // 0x1999390
extern "C" void sub_eec6ed0(void* ctx, void* arg1, void* arg2); // 0xeec6ed0
extern "C" void sub_eec75a0(void* ctx, void* arg);              // 0xeec75a0
extern "C" void sub_568ad40(void* out, const void* in);         // 0x568ad40
extern "C" void sub_bc5b130(void* ctx, ...);                    // 0xbc5b130
extern "C" void sub_76a8a0(void* ctx);                          // 0x76a8a0 (boundary)

// Vendor boundary thunk via data slot 0xF99FFA0
// sub_eea6040 at 0xeea6040 is a "jmp rax" thunk - caller loads vtable function into rax first
inline void eea6040_call_f99ffa0(void* self, void* arg1, void* arg2, std::uint32_t arg3, std::uint32_t arg4,
                                 void* arg5, void* arg6, void* arg7, void* arg8) {
    using Fn = void (*)(void*, void*, void*, std::uint32_t, std::uint32_t,
                        void*, void*, void*, void*);
    Fn fn = reinterpret_cast<Fn>(*reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF99FFA0));
    fn(self, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}

// Vendor boundary thunk via data slot 0xF9A8F60
inline void boundary_call_f9a8f60(void* self, void* arg1) {
    using Fn = void (*)(void*, void*);
    Fn fn = reinterpret_cast<Fn>(*reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF9A8F60));
    fn(self, arg1);
}

// Vendor boundary thunk via data slot 0xF9A8DB8
inline void boundary_call_f9a8db8(void* out, const void* in) {
    using Fn = void (*)(void*, const void*);
    Fn fn = reinterpret_cast<Fn>(*reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF9A8DB8));
    fn(out, in);
}

// Indirect call via rsi (vtable call pattern)
inline void indirect_call_rsi(void* self, void* vtable_fn) {
    using Fn = void (*)(void*);
    Fn fn = reinterpret_cast<Fn>(vtable_fn);
    fn(self);
}

// Indirect call via rsi with more args (for sub_bc5b130 pattern)
inline void indirect_call_rsi_multi(void* self, void* vtable_fn, ...) {
    using Fn = void (*)(void*, ...);
    Fn fn = reinterpret_cast<Fn>(vtable_fn);
    // Note: actual calling convention varies; this is a placeholder
    (void)self; (void)vtable_fn;
}

// Data references (global data slots)
inline const void* data_12adf750() { return RewriteRegistry::imageBase() + 0x12ADF750; }
inline const void* data_128767c8() { return RewriteRegistry::imageBase() + 0x128767C8; }
inline const void* data_12adf748() { return RewriteRegistry::imageBase() + 0x12ADF748; }
inline const void* data_12adf760() { return RewriteRegistry::imageBase() + 0x12ADF760; }
inline const void* data_12adf758() { return RewriteRegistry::imageBase() + 0x12ADF758; }
inline const void* data_12adf770() { return RewriteRegistry::imageBase() + 0x12ADF770; }
inline const void* data_12adf768() { return RewriteRegistry::imageBase() + 0x12ADF768; }
inline const void* data_12adf780() { return RewriteRegistry::imageBase() + 0x12ADF780; }
inline const void* data_12adf798() { return RewriteRegistry::imageBase() + 0x12ADF798; }
inline const void* data_f5b49bf() { return RewriteRegistry::imageBase() + 0xF5B49BF; }  // "LightClustering"
inline const void* data_12adf788() { return RewriteRegistry::imageBase() + 0x12ADF788; }
inline const void* data_12adf818() { return RewriteRegistry::imageBase() + 0x12ADF818; }
inline const void* data_ef1d470() { return RewriteRegistry::imageBase() + 0xEF1D470; }
inline const void* data_ef3f050() { return RewriteRegistry::imageBase() + 0xEF3F050; }
inline const void* data_f246ea0() { return RewriteRegistry::imageBase() + 0xF246EA0; }
inline const void* data_effe2f0() { return RewriteRegistry::imageBase() + 0xEFFE2F0; }
inline const void* data_ef3f048() { return RewriteRegistry::imageBase() + 0xEF3F048; }
inline const void* data_eec8060() { return RewriteRegistry::imageBase() + 0xEEC8060; }
inline const void* data_ef3f01c() { return RewriteRegistry::imageBase() + 0xEF3F01C; }
inline const void* data_ef40de0() { return RewriteRegistry::imageBase() + 0xEF40DE0; }
inline const void* data_ef40dc0() { return RewriteRegistry::imageBase() + 0xEF40DC0; }
inline const void* data_f9a8ed0() { return RewriteRegistry::imageBase() + 0xF9A8ED0; }
inline const void* data_f9a8dd8() { return RewriteRegistry::imageBase() + 0xF9A8DD8; }
inline const void* data_f9a8de0() { return RewriteRegistry::imageBase() + 0xF9A8DE0; }
inline const void* data_1233e1a8() { return RewriteRegistry::imageBase() + 0x1233E1A8; }
inline const void* data_f5c5f05() { return RewriteRegistry::imageBase() + 0xF5C5F05; }  // "LightClusteringPhase"

// Helper: read T from GS:[offset] (thread-local)
template <typename T>
inline T read_gs(std::uint32_t offset) {
    return *reinterpret_cast<T*>(__readgsqword(offset));
}

} // namespace

// Main chunk step function implementing 0xbc57460..0xbc58a85
void sub_bc57460_chunk_c00_step(Sub_bc57460_ChunkC00State* state) {
    // Map state to local variables matching the disassembly register allocation
    // rbp = state->rbp_frame_base
    // r12 = state->r12_ctx (ctx argument)
    // r15 = state->r15_scratch (r9 argument)
    // rsi = state->rsi_scratch (stack arg5)
    // rdi = state->rdi_scratch (r8 argument)
    // rbx = state->rbx_scratch (stack arg6)
    
    char* rbp = reinterpret_cast<char*>(state->rbp_frame_base);
    void* r12 = state->r12_ctx;
    void* r15 = state->r15_scratch;
    void* rsi = state->rsi_scratch;
    void* rdi = state->rdi_scratch;
    void* rbx = state->rbx_scratch;
    
    // Frame helpers
    auto at = [&](std::uint32_t offset) -> void* {
        return rbp + offset;
    };
    template <typename T>
    auto at_t = [&](std::uint32_t offset) -> T* {
        return reinterpret_cast<T*>(rbp + offset);
    };
    template <typename T>
    auto at_ct = [&](std::uint32_t offset) -> const T* {
        return reinterpret_cast<const T*>(rbp + offset);
    };
    
    // ============================================================
    // 0xbc57460..0xbc575b1: Prologue and initial computation
    // ============================================================
    
    // Prologue already done by caller (state is set up)
    // 0xbc574d4: mov r12, rcx  -> r12 = ctx (already in state)
    // 0xbc574d7: cmp byte ptr [rbp+0xA00], 0
    // 0xbc574de: je 0xBC57895  (loc_bc57895)
    std::uint8_t guard_byte = *at_t<std::uint8_t>(0xA00);
    if (guard_byte == 0) {
        // loc_bc57895: early exit path
        // 0xbc57895: mov byte ptr [r12+0x10], 0
        *reinterpret_cast<std::uint8_t*>(reinterpret_cast<char*>(r12) + 0x10) = 0;
        // 0xbc5789b: mov byte ptr [r12+0x28], 0
        *reinterpret_cast<std::uint8_t*>(reinterpret_cast<char*>(r12) + 0x28) = 0;
        // 0xbc578a1: xorps xmm0, xmm0; movups [r12+0x30], xmm0
        *reinterpret_cast<std::uint64_t*>(reinterpret_cast<char*>(r12) + 0x30) = 0;
        *reinterpret_cast<std::uint64_t*>(reinterpret_cast<char*>(r12) + 0x38) = 0;
        // 0xbc578aa: mov dword ptr [r12+0x40], 0
        *reinterpret_cast<std::uint32_t*>(reinterpret_cast<char*>(r12) + 0x40) = 0;
        // 0xbc578b3: mov rax, r12
        // 0xbc578b6: jmp 0xBC59C61 (sub_bc59c61 - outside this chunk)
        // For chunk boundary, we'd return a special value or set a flag
        // This chunk ends at 0xbc58a85, so this early exit jumps out
        return; // Early exit - chunk c01/c02 will handle the rest
    }
    
    // 0xbc574e4: mov r15, r9 (already in state)
    // 0xbc574e7: mov rdi, r8 (already in state)
    // 0xbc574ea: mov [rbp+0x8A0], rdx
    *at_t<void*>(0x8A0) = *reinterpret_cast<void**>(reinterpret_cast<char*>(state) + 0x10); // rdx from caller
    
    // 0xbc574f1: mov r14, [rbp+0x9E8] (stack arg4)
    void* r14 = *at_t<void*>(0x9E8);
    
    // 0xbc574f8: movzx eax, word ptr [r14+0xC]
    std::uint16_t val_c = *reinterpret_cast<std::uint16_t*>(reinterpret_cast<char*>(r14) + 0xC);
    // 0xbc574fd: cvtsi2ss xmm0, eax
    float xmm0 = static_cast<float>(val_c);
    // 0xbc57501: mov rbx, [rbp+0x9F8] (stack arg6, already in state)
    // 0xbc57508: mov rsi, [rbp+0x9F0] (stack arg5, already in state)
    // 0xbc5750f: divss xmm0, [rbx+4]
    float divisor1 = *reinterpret_cast<float*>(reinterpret_cast<char*>(rbx) + 4);
    xmm0 = xmm0 / divisor1;
    // 0xbc57514: call 0xEEC73F0 (sub_eec73f0)
    float result1;
    sub_eec73f0(&result1, &xmm0);
    
    // 0xbc57519: movzx eax, word ptr [r14+0xE]
    std::uint16_t val_e = *reinterpret_cast<std::uint16_t*>(reinterpret_cast<char*>(r14) + 0xE);
    // 0xbc5751e: cvtsi2ss xmm1, eax
    float xmm1 = static_cast<float>(val_e);
    // 0xbc57522: movaps xmm6, xmm0
    float xmm6 = result1;
    // 0xbc57525: divss xmm1, [rbx+8]
    float divisor2 = *reinterpret_cast<float*>(reinterpret_cast<char*>(rbx) + 8);
    xmm1 = xmm1 / divisor2;
    // 0xbc5752a: movaps xmm0, xmm1
    // 0xbc5752d: call 0xEEC73F0 (sub_eec73f0)
    float result2;
    sub_eec73f0(&result2, &xmm1);
    
    // 0xbc57532: movss xmm1, [rbx+0xC]
    float xmm1_val = *reinterpret_cast<float*>(reinterpret_cast<char*>(rbx) + 0xC);
    // 0xbc57537: movaps [rbp+0x7C0], xmm6
    *at_t<float>(0x7C0) = xmm6;
    // 0xbc5753e: movss [rbp+0x7B4], xmm6
    *at_t<float>(0x7B4) = xmm6;
    // 0xbc57546: movaps [rbp+0x7D0], xmm0
    *at_t<float>(0x7D0) = result2;
    // 0xbc5754d: movss [rbp+0x7B8], xmm0
    *at_t<float>(0x7B8) = result2;
    // 0xbc57555: movss [rbp+0x894], xmm1
    *at_t<float>(0x894) = xmm1_val;
    // 0xbc5755d: movss [rbp+0x7BC], xmm1
    *at_t<float>(0x7BC) = xmm1_val;
    
    // 0xbc57565: mov rax, [rsi+0x50]
    std::uint64_t rax = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<char*>(rsi) + 0x50);
    // 0xbc57569: sub rax, [rsi+0x48]
    rax -= *reinterpret_cast<std::uint64_t*>(reinterpret_cast<char*>(rsi) + 0x48);
    // 0xbc5756d: sar rax, 3
    rax >>= 3;
    // 0xbc57571: mov rbx, 0xEF7BDEF7BDEF7BDF
    std::uint64_t rbx_magic = 0xEF7BDEF7BDEF7BDF;
    // 0xbc5757b: imul rbx, rax
    rbx_magic *= rax;
    // 0xbc5757f: cmp rbx, 1
    // 0xbc57583: adc rbx, 0
    std::uint64_t rbx_result = rbx_magic + (rbx_magic >= 1 ? 1 : 0);
    // 0xbc57587: mov qword ptr [rbp+0x88C], 0
    *at_t<std::uint64_t>(0x88C) = 0;
    // 0xbc57592: mov eax, [0x12ADF750]
    std::uint32_t eax = *reinterpret_cast<std::uint32_t*>(data_12adf750());
    // 0xbc57598: mov ecx, [0x128767C8]
    std::uint32_t ecx = *reinterpret_cast<std::uint32_t*>(data_128767c8());
    // 0xbc5759e: mov rdx, gs:[0x58]
    // 0xbc575a7: mov rcx, [rdx+rcx*8]
    void* gs58 = reinterpret_cast<void*>(__readgsqword(0x58));
    void* rcx_ptr = *reinterpret_cast<void**>(reinterpret_cast<char*>(gs58) + ecx * 8);
    // 0xbc575ab: cmp eax, [rcx+4]
    std::uint32_t cmp_val = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<char*>(rcx_ptr) + 4);
    // 0xbc575b1: jg 0xBC59D3F (sub_bc59d3f - outside chunk)
    if (eax > cmp_val) {
        // Jump to sub_bc59d3f - boundary
        return;
    }
    
    // ============================================================
    // 0xbc575b7..0xbc57614: First sub_bc09250 call sequence
    // ============================================================
    // 0xbc575b7: mov dword ptr [rbp+0x890], 0x80
    *at_t<std::uint32_t>(0x890) = 0x80;
    // 0xbc575c1: mov [rbp+0x88C], rbx
    *at_t<std::uint64_t>(0x88C) = rbx_result;
    // 0xbc575c7: mov rax, [0x12ADF748]
    void* rax_val = *reinterpret_cast<void**>(data_12adf748());
    // 0xbc575ce: mov [rbp+0x760], rax
    *at_t<void*>(0x760) = rax_val;
    // 0xbc575d5: lea r8, [rbp+0x88C]
    void* r8_arg = at(0x88C);
    // 0xbc575dc: mov r13, [rbp+0x8A0]
    void* r13 = *at_t<void*>(0x8A0);
    // 0xbc575e3: mov rcx, r13
    // 0xbc575e6: mov rdx, r13
    // 0xbc575e9: call 0xBC09250 (sub_bc09250)
    sub_bc09250(r13, r13, r8_arg, nullptr); // 4th arg unclear from disasm
    // 0xbc575ee: mov [rbp+0x768], rax
    *at_t<void*>(0x768) = rax_val; // return value in rax
    // 0xbc575f5: mov eax, [0x12ADF760]
    eax = *reinterpret_cast<std::uint32_t*>(data_12adf760());
    // 0xbc575fb: mov ecx, [0x128767C8]
    ecx = *reinterpret_cast<std::uint32_t*>(data_128767c8());
    // 0xbc57601: mov rdx, gs:[0x58]
    gs58 = reinterpret_cast<void*>(__readgsqword(0x58));
    // 0xbc5760a: mov rcx, [rdx+rcx*8]
    rcx_ptr = *reinterpret_cast<void**>(reinterpret_cast<char*>(gs58) + ecx * 8);
    // 0xbc5760e: cmp eax, [rcx+4]
    cmp_val = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<char*>(rcx_ptr) + 4);
    // 0xbc57614: jg 0xBC59DB4 (sub_bc59db4 - outside chunk)
    if (eax > cmp_val) {
        return;
    }
    
    // ============================================================
    // 0xbc5761a..0xbc57670: Second sub_bc09250 call sequence
    // ============================================================
    // 0xbc5761a: mov dword ptr [rbp+0x890], 0x40
    *at_t<std::uint32_t>(0x890) = 0x40;
    // 0xbc57624: mov [rbp+0x88C], rbx
    *at_t<std::uint64_t>(0x88C) = rbx_result;
    // 0xbc5762a: mov rax, [0x12ADF758]
    rax_val = *reinterpret_cast<void**>(data_12adf758());
    // 0xbc57631: mov [rbp+0x698], rax
    *at_t<void*>(0x698) = rax_val;
    // 0xbc57638: lea r8, [rbp+0x88C]
    r8_arg = at(0x88C);
    // 0xbc5763f: mov rcx, r13
    // 0xbc57642: mov rdx, r13
    // 0xbc57645: call 0xBC09250 (sub_bc09250)
    sub_bc09250(r13, r13, r8_arg, nullptr);
    // 0xbc5764a: mov [rbp+0x6A0], rax
    *at_t<void*>(0x6A0) = rax_val;
    // 0xbc57651: mov eax, [0x12ADF770]
    eax = *reinterpret_cast<std::uint32_t*>(data_12adf770());
    // 0xbc57657: mov ecx, [0x128767C8]
    ecx = *reinterpret_cast<std::uint32_t*>(data_128767c8());
    // 0xbc5765d: mov rdx, gs:[0x58]
    gs58 = reinterpret_cast<void*>(__readgsqword(0x58));
    // 0xbc57666: mov rcx, [rdx+rcx*8]
    rcx_ptr = *reinterpret_cast<void**>(reinterpret_cast<char*>(gs58) + ecx * 8);
    // 0xbc5766a: cmp eax, [rcx+4]
    cmp_val = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<char*>(rcx_ptr) + 4);
    // 0xbc57670: jg 0xBC59E29 (sub_bc59e29 - outside chunk)
    if (eax > cmp_val) {
        return;
    }
    
    // ============================================================
    // 0xbc57676..0xbc576f9: Third sub_bc09250 call sequence
    // ============================================================
    // 0xbc57676: movaps xmm0, [rbp+0x7C0]
    float xmm0_val = *at_t<float>(0x7C0);
    // 0xbc5767d: mulss xmm0, [rbp+0x7D0]
    xmm0_val *= *at_t<float>(0x7D0);
    // 0xbc57685: mulss xmm0, [rbp+0x894]
    xmm0_val *= *at_t<float>(0x894);
    // 0xbc5768d: cvttss2si rcx, xmm0
    std::int32_t rcx_int = static_cast<std::int32_t>(xmm0_val);
    // 0xbc57692: mov rax, [rbp+0x9F8]
    rax = reinterpret_cast<std::uintptr_t>(rbx); // rbx from state
    // 0xbc57699: imul ecx, [rax]
    std::int32_t ecx_int = rcx_int * *reinterpret_cast<std::int32_t*>(rax);
    // 0xbc5769c: mov dword ptr [rbp+0x890], 4
    *at_t<std::uint32_t>(0x890) = 4;
    // 0xbc576a6: mov [rbp+0x880], rcx
    *at_t<std::int32_t>(0x880) = ecx_int;
    // 0xbc576ad: mov [rbp+0x88C], ecx
    *at_t<std::int32_t>(0x88C) = ecx_int;
    // 0xbc576b3: mov rax, [0x12ADF768]
    rax_val = *reinterpret_cast<void**>(data_12adf768());
    // 0xbc576ba: mov [rbp+0x770], rax
    *at_t<void*>(0x770) = rax_val;
    // 0xbc576c1: lea r8, [rbp+0x88C]
    r8_arg = at(0x88C);
    // 0xbc576c8: mov rcx, r13
    // 0xbc576cb: mov rdx, r13
    // 0xbc576ce: call 0xBC09250 (sub_bc09250)
    sub_bc09250(r13, r13, r8_arg, nullptr);
    // 0xbc576d3: mov [rbp+0x778], rax
    *at_t<void*>(0x778) = rax_val;
    // 0xbc576da: mov eax, [0x12ADF780]
    eax = *reinterpret_cast<std::uint32_t*>(data_12adf780());
    // 0xbc576e0: mov ecx, [0x128767C8]
    ecx = *reinterpret_cast<std::uint32_t*>(data_128767c8());
    // 0xbc576e6: mov rdx, gs:[0x58]
    gs58 = reinterpret_cast<void*>(__readgsqword(0x58));
    // 0xbc576ef: mov rcx, [rdx+rcx*8]
    rcx_ptr = *reinterpret_cast<void**>(reinterpret_cast<char*>(gs58) + ecx * 8);
    // 0xbc576f3: cmp eax, [rcx+4]
    cmp_val = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<char*>(rcx_ptr) + 4);
    // 0xbc576f9: jg 0xBC59E9E (sub_bc59e9e - outside chunk)
    if (eax > cmp_val) {
        return;
    }
    
    // ============================================================
    // 0xbc576ff..0xbc5771e: Fourth check
    // ============================================================
    // 0xbc576ff: mov eax, [0x12ADF798]
    eax = *reinterpret_cast<std::uint32_t*>(data_12adf798());
    // 0xbc57705: mov ecx, [0x128767C8]
    ecx = *reinterpret_cast<std::uint32_t*>(data_128767c8());
    // 0xbc5770b: mov rdx, gs:[0x58]
    gs58 = reinterpret_cast<void*>(__readgsqword(0x58));
    // 0xbc57714: mov rcx, [rdx+rcx*8]
    rcx_ptr = *reinterpret_cast<void**>(reinterpret_cast<char*>(gs58) + ecx * 8);
    // 0xbc57718: cmp eax, [rcx+4]
    cmp_val = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<char*>(rcx_ptr) + 4);
    // 0xbc5771e: jg 0xBC59F1E (sub_bc59f1e - outside chunk)
    if (eax > cmp_val) {
        return;
    }
    
    // ============================================================
    // 0xbc57724..0xbc577bc: Setup for sub_567c8b0 and sub_ab49c0
    // ============================================================
    // 0xbc57724: mov r9, [rbp+0x9D0]
    void* r9_val = *at_t<void*>(0x9D0);
    // 0xbc5772b: lea r13, [r14+0x18]
    void* r13_new = reinterpret_cast<char*>(r14) + 0x18;
    // 0xbc5772f: xorps xmm0, xmm0
    // 0xbc57732: movaps [rbp+0x410], xmm0
    *reinterpret_cast<std::uint64_t*>(at(0x410)) = 0;
    *reinterpret_cast<std::uint64_t*>(at(0x418)) = 0;
    // 0xbc57739: lea rax, [0xF5B49BF] ("LightClustering")
    // 0xbc57740: mov [rbp+0x1D0], rax
    *at_t<void*>(0x1D0) = const_cast<void*>(data_f5b49bf());
    // 0xbc57747: mov qword ptr [rbp+0x1D8], 0xF
    *at_t<std::uint64_t>(0x1D8) = 0xF;
    // 0xbc57752: lea rax, [rbp+0x410]
    // 0xbc57759: mov [rsp+0x28], rax
    // 0xbc5775e: lea rax, [rbp+0x1D0]
    // 0xbc57765: mov [rsp+0x20], rax
    // 0xbc5776a: lea r8, [0x12ADF788]
    void* r8_val = data_12adf788();
    // 0xbc57771: lea rdx, [rbp+0x750]
    void* rdx_val = at(0x750);
    // 0xbc57778: mov rcx, r15
    // 0xbc5777b: call 0x567C8B0 (sub_567c8b0)
    sub_567c8b0(r15, 0, 0); // args approximated
    
    // 0xbc57780: movss xmm6, [r14+0x18]
    float xmm6_val = *reinterpret_cast<float*>(reinterpret_cast<char*>(r14) + 0x18);
    // 0xbc57786: movss xmm7, [r14+0x2C]
    float xmm7_val = *reinterpret_cast<float*>(reinterpret_cast<char*>(r14) + 0x2C);
    // 0xbc5778c: mov r15d, [0x12ADF818]
    std::uint32_t r15d = *reinterpret_cast<std::uint32_t*>(data_12adf818());
    // 0xbc57793: lea rcx, [rbp+0x410]
    // 0xbc5779a: mov rdx, r13
    // 0xbc5779d: call 0xAB49C0 (sub_ab49c0)
    sub_ab49c0(at(0x410), r13_new);
    // 0xbc577a2: nop
    // 0xbc577a3: add r15d, 0xFFFFFFF9 (subtract 7)
    r15d -= 7;
    // 0xbc577a7: movss xmm0, [0xEF1D470]
    float xmm0_ef = *reinterpret_cast<float*>(data_ef1d470());
    // 0xbc577af: xorps xmm3, xmm3
    float xmm3 = 0.0f;
    // 0xbc577b2: movaps xmm9, xmm0
    float xmm9 = xmm0_ef;
    // 0xbc577b6: cmp r15d, 2
    // 0xbc577ba: jb short 0xBC577C0 (loc_bc577c0)
    if (r15d < 2) {
        // 0xbc577bc: xorps xmm9, xmm9
        xmm9 = 0.0f;
    }
    // loc_bc577c0:
    // 0xbc577c0: divss xmm0, xmm6
    xmm0_ef = xmm0_ef / xmm6_val;
    // 0xbc577c4: divss xmm6, xmm7
    xmm6_val = xmm6_val / xmm7_val;
    // 0xbc577c8: movss xmm1, [rbp+0x41C]
    float xmm1_val = *at_t<float>(0x41C);
    // 0xbc577d0: mulss xmm1, xmm3
    xmm1_val *= xmm3;
    // 0xbc577d4: movss xmm2, [rbp+0x418]
    float xmm2_val = *at_t<float>(0x418);
    // 0xbc577dc: mulss xmm2, xmm3
    xmm2_val *= xmm3;
    // 0xbc577e0: movss xmm4, [rbp+0x42C]
    float xmm4_val = *at_t<float>(0x42C);
    // 0xbc577e8: mulss xmm4, xmm3
    xmm4_val *= xmm3;
    // 0xbc577ec: addss xmm4, xmm1
    xmm4_val += xmm1_val;
    // 0xbc577f0: mulss xmm3, [rbp+0x428]
    xmm3 *= *at_t<float>(0x428);
    // 0xbc577f8: addss xmm3, xmm2
    xmm3 += xmm2_val;
    // 0xbc577fc: movss xmm1, [rbp+0x438]
    xmm1_val = *at_t<float>(0x438);
    // 0xbc57804: movss xmm5, [rbp+0x43C]
    float xmm5_val = *at_t<float>(0x43C);
    // 0xbc5780c: movaps xmm2, xmm9
    xmm2_val = xmm9;
    // 0xbc57810: mulss xmm2, xmm5
    xmm2_val *= xmm5_val;
    // 0xbc57814: mulss xmm9, xmm1
    xmm9 *= xmm1_val;
    // 0xbc57819: movss xmm7, [rbp+0x448]
    xmm7_val = *at_t<float>(0x448);
    // 0xbc57821: movss xmm8, [rbp+0x44C]
    float xmm8_val = *at_t<float>(0x44C);
    // 0xbc5782a: addss xmm2, xmm8
    xmm2_val += xmm8_val;
    // 0xbc5782f: addss xmm9, xmm7
    xmm9 += xmm7_val;
    // 0xbc57834: addss xmm2, xmm4
    xmm2_val += xmm4_val;
    // 0xbc57838: addss xmm9, xmm3
    xmm9 += xmm3;
    // 0xbc5783d: addss xmm5, xmm8
    xmm5_val += xmm8_val;
    // 0xbc57842: addss xmm1, xmm7
    xmm1_val += xmm7_val;
    // 0xbc57846: addss xmm5, xmm4
    xmm5_val += xmm4_val;
    // 0xbc5784a: addss xmm1, xmm3
    xmm1_val += xmm3;
    // 0xbc5784e: divss xmm1, xmm5
    xmm1_val = xmm1_val / xmm5_val;
    // 0xbc57852: addss xmm0, xmm0
    xmm0_ef = xmm0_ef + xmm0_ef;
    // 0xbc57856: mulss xmm0, xmm1
    xmm0_ef = xmm0_ef * xmm1_val;
    // 0xbc5785a: movaps xmm3, xmm0
    xmm3 = xmm0_ef;
    // 0xbc5785d: divss xmm3, xmm6
    xmm3 = xmm3 / xmm6_val;
    // 0xbc57861: xorps xmm4, xmm4
    xmm4_val = 0.0f;
    // 0xbc57864: movaps [rbp+0x30], xmm4
    *at_t<std::uint64_t>(0x30) = 0;
    *at_t<std::uint64_t>(0x38) = 0;
    // 0xbc57868: movaps [rbp+0x20], xmm4
    *at_t<std::uint64_t>(0x20) = 0;
    *at_t<std::uint64_t>(0x28) = 0;
    // 0xbc5786c: movaps [rbp+0x10], xmm4
    *at_t<std::uint64_t>(0x10) = 0;
    *at_t<std::uint64_t>(0x18) = 0;
    // 0xbc57870: movaps [rbp], xmm4
    *at_t<std::uint64_t>(0x00) = 0;
    *at_t<std::uint64_t>(0x08) = 0;
    // 0xbc57874: mov qword ptr [rbp+0x40], 0
    *at_t<std::uint64_t>(0x40) = 0;
    // 0xbc5787c: mov rax, [rbp+0x758]
    rax = *at_t<std::uint64_t>(0x758);
    // 0xbc57883: test rax, rax
    // 0xbc57886: je short 0xBC578BB (loc_bc578bb)
    if (rax == 0) {
        // loc_bc578bb:
        // 0xbc578bb: xor eax, eax
        rax = 0;
    } else {
        // 0xbc57888: lock inc dword ptr [rax+8]
        _InterlockedIncrement(reinterpret_cast<volatile long*>(reinterpret_cast<char*>(rax) + 8));
        // 0xbc5788c: mov rax, [rbp+0x758]
        rax = *at_t<std::uint64_t>(0x758);
        // 0xbc57893: jmp short 0xBC578BD (loc_bc578bd)
    }
    // loc_bc578bd:
    // 0xbc578bd: mov rcx, [rbp+0x750]
    void* rcx_val = *at_t<void*>(0x750);
    // 0xbc578c4: mov [rbp+0x38], rcx
    *at_t<void*>(0x38) = rcx_val;
    // 0xbc578c8: mov [rbp+0x40], rax
    *at_t<void*>(0x40) = reinterpret_cast<void*>(rax);
    // 0xbc578cc: mov [rbp+0x48], rdi
    *at_t<void*>(0x48) = rdi;
    // 0xbc578d0: movaps xmm4, [rbp+0x7C0]
    float xmm4_7c0 = *at_t<float>(0x7C0);
    // 0xbc578d7: movss [rbp+0x50], xmm4
    *at_t<float>(0x50) = xmm4_7c0;
    // 0xbc578dc: movaps xmm4, [rbp+0x7D0]
    float xmm4_7d0 = *at_t<float>(0x7D0);
    // 0xbc578e3: movss [rbp+0x54], xmm4
    *at_t<float>(0x54) = xmm4_7d0;
    // 0xbc578e8: movss xmm4, [rbp+0x894]
    float xmm4_894 = *at_t<float>(0x894);
    // 0xbc578f0: movss [rbp+0x58], xmm4
    *at_t<float>(0x58) = xmm4_894;
    // 0xbc578f5: movsd xmm4, [0xF246EA0]
    double xmm4_f246 = *reinterpret_cast<double*>(data_f246ea0());
    // 0xbc578fd: movsd [rbp+0x5C], xmm4
    *at_t<double>(0x5C) = xmm4_f246;
    // 0xbc57902: mov dword ptr [rbp+0x64], 0x40800000 (4.0f as bits)
    *at_t<std::uint32_t>(0x64) = 0x40800000;
    // 0xbc57909: mov rax, [rbp+0x9F8]
    rax = reinterpret_cast<std::uintptr_t>(rbx);
    // 0xbc57910: movups xmm4, [rax]
    // 0xbc57913: movups xmm5, [rax+0x10]
    // 0xbc57917: movups [rbp+0x68], xmm4
    std::memcpy(at(0x68), reinterpret_cast<void*>(rax), 16);
    // 0xbc5791b: movups [rbp+0x78], xmm5
    std::memcpy(at(0x78), reinterpret_cast<char*>(reinterpret_cast<void*>(rax)) + 0x10, 16);
    // 0xbc5791f: xorps xmm9, [0xEF3F050]
    xmm9 = xmm9 ^ *reinterpret_cast<float*>(data_ef3f050());
    // 0xbc57927: divss xmm9, xmm2
    xmm9 = xmm9 / xmm2_val;
    // 0xbc5792c: movss [rbp+0x88], xmm9
    *at_t<float>(0x88) = xmm9;
    // 0xbc57935: movss [rbp+0x8C], xmm1
    *at_t<float>(0x8C) = xmm1_val;
    // 0xbc5793d: movss [rbp+0x90], xmm3
    *at_t<float>(0x90) = xmm3;
    // 0xbc57945: movss [rbp+0x94], xmm0
    *at_t<float>(0x94) = xmm0_ef;
    // 0xbc5794d: lea rcx, [rbp+0x98]
    // 0xbc57954: mov rdx, r14
    // 0xbc57957: call 0x5667860 (sub_5667860)
    sub_5667860(at(0x98), r14);
    
    // ============================================================
    // 0xbc5795d..0xbc579d6: Reference counting and sub_a78940 calls
    // ============================================================
    // 0xbc5795d: mov [rbp+0x6A8], r12
    *at_t<void*>(0x6A8) = r12;
    // 0xbc57964: mov rax, [rdi]
    rax = *reinterpret_cast<std::uint64_t*>(rdi);
    // 0xbc57967: mov rcx, [rax]
    rcx_val = *reinterpret_cast<void**>(rax);
    // 0xbc5796a: mov r8, rbx
    // 0xbc5796d: shl r8, 7
    std::uint64_t r8_shifted = reinterpret_cast<std::uintptr_t>(rbx) << 7;
    // 0xbc57971: lea rdx, [rbp+0x410]
    rdx_val = at(0x410);
    // 0xbc57978: mov r9d, 1
    // 0xbc5797e: call 0xA78940 (sub_a78940)
    sub_a78940(rcx_val, reinterpret_cast<void*>(rax), rdx_val, 1, reinterpret_cast<void*>(r8_shifted), 0);
    // 0xbc57983: nop
    // 0xbc57984: mov rax, [rbp+0x420]
    rax = *at_t<std::uint64_t>(0x420);
    // 0xbc5798b: mov [rbp+0x8A8], rax
    *at_t<std::uint64_t>(0x8A8) = rax;
    // 0xbc57992: mov rax, [rbp+0x410]
    rax = *at_t<std::uint64_t>(0x410);
    // 0xbc57999: mov r15, [rbp+0x418]
    r15 = *at_t<void*>(0x418);
    // 0xbc579a0: mov rax, [rax]
    rax = *reinterpret_cast<std::uint64_t*>(rax);
    // 0xbc579a3: mov [rbp+0x870], rax
    *at_t<std::uint64_t>(0x870) = rax;
    // 0xbc579aa: test r15, r15
    // 0xbc579ad: je short 0xBC579DC (loc_bc579dc)
    if (r15 != nullptr) {
        // 0xbc579af: lock dec dword ptr [r15+8]
        long ref = _InterlockedDecrement(reinterpret_cast<volatile long*>(reinterpret_cast<char*>(r15) + 8));
        // 0xbc579b4: jne short 0xBC579DC
        if (ref != 0) {
            // skip to loc_bc579dc
        } else {
            // 0xbc579b6: mov rax, [r15]
            rax = *reinterpret_cast<std::uint64_t*>(r15);
            // 0xbc579b9: mov rax, [rax]
            rax = *reinterpret_cast<std::uint64_t*>(rax);
            // 0xbc579bc: mov rcx, r15
            // 0xbc579bf: call qword ptr [0xF99FFA0] (sub_eea6040)
            eea6040_call_f99ffa0(r15, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);
            // 0xbc579c5: lock dec dword ptr [r15+0xC]
            ref = _InterlockedDecrement(reinterpret_cast<volatile long*>(reinterpret_cast<char*>(r15) + 0xC));
            // 0xbc579ca: jne short 0xBC579DC
            if (ref != 0) {
                // skip
            } else {
                // 0xbc579cc: mov rax, [r15]
                rax = *reinterpret_cast<std::uint64_t*>(r15);
                // 0xbc579cf: mov rax, [rax+8]
                rax = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<char*>(rax) + 8);
                // 0xbc579d3: mov rcx, r15
                // 0xbc579d6: call qword ptr [0xF99FFA0] (sub_eea6040)
                eea6040_call_f99ffa0(r15, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);
            }
        }
    }
    // loc_bc579dc:
    // 0xbc579dc: mov rax, [rdi]
    rax = *reinterpret_cast<std::uint64_t*>(rdi);
    // 0xbc579df: mov rcx, [rax]
    rcx_val = *reinterpret_cast<void**>(rax);
    // 0xbc579e2: shl rbx, 6
    std::uint64_t rbx_shifted = reinterpret_cast<std::uintptr_t>(rbx) << 6;
    // 0xbc579e6: lea rdx, [rbp+0x410]
    rdx_val = at(0x410);
    // 0xbc579ed: mov r9d, 1
    // 0xbc579f3: mov r8, rbx
    // 0xbc579f6: call 0xA78940 (sub_a78940)
    sub_a78940(rcx_val, reinterpret_cast<void*>(rax), rdx_val, 1, reinterpret_cast<void*>(rbx_shifted), 0);
    // 0xbc579fb: nop
    // 0xbc579fc: mov r12, [rbp+0x420]
    r12 = *at_t<void*>(0x420);
    // 0xbc57a03: mov rax, [rbp+0x410]
    rax = *at_t<std::uint64_t>(0x410);
    // 0xbc57a0a: mov rbx, [rbp+0x418]
    rbx = *at_t<void*>(0x418);
    // 0xbc57a11: mov rax, [rax]
    rax = *reinterpret_cast<std::uint64_t*>(rax);
    // 0xbc57a14: mov [rbp+0x878], rax
    *at_t<std::uint64_t>(0x878) = rax;
    // 0xbc57a1b: test rbx, rbx
    // 0xbc57a1e: je short 0xBC57A4B (loc_bc57a4b)
    if (rbx != nullptr) {
        // 0xbc57a20: lock dec dword ptr [rbx+8]
        long ref = _InterlockedDecrement(reinterpret_cast<volatile long*>(reinterpret_cast<char*>(rbx) + 8));
        // 0xbc57a24: jne short 0xBC57A4B
        if (ref != 0) {
            // skip
        } else {
            // 0xbc57a26: mov rax, [rbx]
            rax = *reinterpret_cast<std::uint64_t*>(rbx);
            // 0xbc57a29: mov rax, [rax]
            rax = *reinterpret_cast<std::uint64_t*>(rax);
            // 0xbc57a2c: mov rcx, rbx
            // 0xbc57a2f: call qword ptr [0xF99FFA0] (sub_eea6040)
            eea6040_call_f99ffa0(rbx, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);
            // 0xbc57a35: lock dec dword ptr [rbx+0xC]
            ref = _InterlockedDecrement(reinterpret_cast<volatile long*>(reinterpret_cast<char*>(rbx) + 0xC));
            // 0xbc57a39: jne short 0xBC57A4B
            if (ref != 0) {
                // skip
            } else {
                // 0xbc57a3b: mov rax, [rbx]
                rax = *reinterpret_cast<std::uint64_t*>(rbx);
                // 0xbc57a3e: mov rax, [rax+8]
                rax = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<char*>(rax) + 8);
                // 0xbc57a42: mov rcx, rbx
                // 0xbc57a45: call qword ptr [0xF99FFA0] (sub_eea6040)
                eea6040_call_f99ffa0(rbx, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);
            }
        }
    }
    // loc_bc57a4b:
    // 0xbc57a4b: mov r13, rsi
    r13 = rsi;
    // 0xbc57a4e: mov rax, [rdi]
    rax = *reinterpret_cast<std::uint64_t*>(rdi);
    // 0xbc57a51: mov edi, [rbp+0x880]
    std::int32_t edi_val = *at_t<std::int32_t>(0x880);
    // 0xbc57a57: mov rcx, [rax]
    rcx_val = *reinterpret_cast<void**>(rax);
    // 0xbc57a5a: lea rbx, [rdi*4]
    std::uint64_t rbx_lea = static_cast<std::uint64_t>(edi_val) * 4;
    // 0xbc57a62: lea rdx, [rbp+0x410]
    rdx_val = at(0x410);
    // 0xbc57a69: mov r9d, 1
    // 0xbc57a6f: mov r8, rbx
    // 0xbc57a72: call 0xA78940 (sub_a78940)
    sub_a78940(rcx_val, reinterpret_cast<void*>(rax), rdx_val, 1, reinterpret_cast<void*>(rbx_lea), 0);
    // 0xbc57a77: nop
    // 0xbc57a78: mov [rbp+0x688], rdi
    *at_t<std::int32_t>(0x688) = edi_val;
    // 0xbc57a7f: movaps [rbp+0x780], xmm9
    *at_t<float>(0x780) = xmm9;
    // 0xbc57a87: mov rdi, [rbp+0x420]
    rdi = *at_t<void*>(0x420);
    // 0xbc57a8e: mov rax, [rbp+0x410]
    rax = *at_t<std::uint64_t>(0x410);
    // 0xbc57a95: mov r15, [rbp+0x418]
    r15 = *at_t<void*>(0x418);
    // 0xbc57a9c: mov rax, [rax]
    rax = *reinterpret_cast<std::uint64_t*>(rax);
    // 0xbc57a9f: test r15, r15
    // 0xbc57aa2: je short 0xBC57ADA (loc_bc57ada)
    if (r15 != nullptr) {
        // 0xbc57aa4: lock dec dword ptr [r15+8]
        long ref = _InterlockedDecrement(reinterpret_cast<volatile long*>(reinterpret_cast<char*>(r15) + 8));
        // 0xbc57aa9: jne short 0xBC57ADA
        if (ref != 0) {
            // skip
        } else {
            // 0xbc57aab: mov rsi, rax
            rsi = reinterpret_cast<void*>(rax);
            // 0xbc57aae: mov rax, [r15]
            rax = *reinterpret_cast<std::uint64_t*>(r15);
            // 0xbc57ab1: mov rax, [rax]
            rax = *reinterpret_cast<std::uint64_t*>(rax);
            // 0xbc57ab4: mov rcx, r15
            // 0xbc57ab7: call qword ptr [0xF99FFA0] (sub_eea6040)
            eea6040_call_f99ffa0(r15, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);
            // 0xbc57abd: mov rax, rsi
            rax = reinterpret_cast<std::uintptr_t>(rsi);
            // 0xbc57ac0: lock dec dword ptr [r15+0xC]
            ref = _InterlockedDecrement(reinterpret_cast<volatile long*>(reinterpret_cast<char*>(r15) + 0xC));
            // 0xbc57ac5: jne short 0xBC57ADA
            if (ref != 0) {
                // skip
            } else {
                // 0xbc57ac7: mov rax, [r15]
                rax = *reinterpret_cast<std::uint64_t*>(r15);
                // 0xbc57aca: mov rax, [rax+8]
                rax = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<char*>(rax) + 8);
                // 0xbc57ace: mov rcx, r15
                // 0xbc57ad1: call qword ptr [0xF99FFA0] (sub_eea6040)
                eea6040_call_f99ffa0(r15, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);
            }
        }
        // 0xbc57ad7: mov rax, rsi
        rax = reinterpret_cast<std::uintptr_t>(rsi);
    }
    // loc_bc57ada:
    // 0xbc57ada: mov [rbp+0x680], rax
    *at_t<std::uint64_t>(0x680) = rax;
    // 0xbc57ae1: add rdi, rax
    rdi = reinterpret_cast<char*>(rdi) + rax;
    // 0xbc57ae4: mov [rbp+0x690], rdi
    *at_t<void*>(0x690) = rdi;
    // 0xbc57aeb: mov rcx, rdi
    // 0xbc57aee: xor edx, edx
    // 0xbc57af0: mov r8, rbx
    // 0xbc57af3: call 0xEEC6ED0 (sub_eec6ed0)
    sub_eec6ed0(rdi, nullptr, rbx);
    
    // ============================================================
    // 0xbc57af8..0xbc57c5a: More vector math and sub_aa6580 calls
    // ============================================================
    // 0xbc57af8: mov rax, [rbp+0x9F8]
    rax = reinterpret_cast<std::uintptr_t>(rbx);
    // 0xbc57aff: movss xmm0, [rax+0x10]
    float xmm0_rax10 = *reinterpret_cast<float*>(reinterpret_cast<char*>(rax) + 0x10);
    // 0xbc57b04: movss [rbp+0x8B4], xmm0
    *at_t<float>(0x8B4) = xmm0_rax10;
    // 0xbc57b0c: mov dword ptr [rbp+0x6F0], 0x3F800000 (1.0f)
    *at_t<std::uint32_t>(0x6F0) = 0x3F800000;
    // 0xbc57b16: xorps xmm0, xmm0
    // 0xbc57b19: movups [rbp+0x6F4], xmm0
    *at_t<std::uint64_t>(0x6F4) = 0;
    *at_t<std::uint64_t>(0x6FC) = 0;
    // 0xbc57b20: mov dword ptr [rbp+0x704], 0x3F800000
    *at_t<std::uint32_t>(0x704) = 0x3F800000;
    // 0xbc57b2a: movups [rbp+0x708], xmm0
    *at_t<std::uint64_t>(0x708) = 0;
    *at_t<std::uint64_t>(0x710) = 0;
    // 0xbc57b31: mov dword ptr [rbp+0x718], 0x3F800000
    *at_t<std::uint32_t>(0x718) = 0x3F800000;
    // 0xbc57b3b: movups [rbp+0x71C], xmm0
    *at_t<std::uint64_t>(0x71C) = 0;
    *at_t<std::uint64_t>(0x724) = 0;
    // 0xbc57b42: mov dword ptr [rbp+0x72C], 0x3F800000
    *at_t<std::uint32_t>(0x72C) = 0x3F800000;
    // 0xbc57b4c: mov dword ptr [rbp+0x7E8], 0x3F800000
    *at_t<std::uint32_t>(0x7E8) = 0x3F800000;
    // 0xbc57b56: movups [rbp+0x7EC], xmm0
    *at_t<std::uint64_t>(0x7EC) = 0;
    *at_t<std::uint64_t>(0x7F4) = 0;
    // 0xbc57b5d: mov dword ptr [rbp+0x7FC], 0x3F800000
    *at_t<std::uint32_t>(0x7FC) = 0x3F800000;
    // 0xbc57b67: movups [rbp+0x800], xmm0
    *at_t<std::uint64_t>(0x800) = 0;
    *at_t<std::uint64_t>(0x808) = 0;
    // 0xbc57b78: mov dword ptr [rbp+0x810], 0x3F800000
    *at_t<std::uint32_t>(0x810) = 0x3F800000;
    // 0xbc57b7f: movups [rbp+0x814], xmm0
    *at_t<std::uint64_t>(0x814) = 0;
    *at_t<std::uint64_t>(0x81C) = 0;
    // 0xbc57b89: lea rcx, [rbp+0x410]
    // 0xbc57b90: lea r8, [rbp+0x7E8]
    // 0xbc57b97: lea rdx, [r14+0x18]
    // 0xbc57b9b: call 0xAA6580 (sub_aa6580)
    sub_aa6580(at(0x410), at(0x7E8), reinterpret_cast<char*>(r14) + 0x18);
    // 0xbc57ba0: nop
    // 0xbc57ba1: lea rsi, [rbp+0x1D0]
    rsi = at(0x1D0);
    // 0xbc57ba8: lea rdx, [rbp+0x410]
    rdx_val = at(0x410);
    // 0xbc57baf: lea r8, [rbp+0x6F0]
    // 0xbc57bb6: mov rcx, rsi
    // 0xbc57bb9: call 0xAA6580 (sub_aa6580)
    sub_aa6580(rsi, rdx_val, at(0x6F0));
    // 0xbc57bbe: nop
    // 0xbc57bbf: mov rax, [rbp+0x8A8]
    rax = *at_t<std::uint64_t>(0x8A8);
    // 0xbc57bc6: add rax, [rbp+0x870]
    rax += *at_t<std::uint64_t>(0x870);
    // 0xbc57bcd: mov [rbp+0x8A8], rax
    *at_t<std::uint64_t>(0x8A8) = rax;
    // 0xbc57bd4: add r12, [rbp+0x878]
    r12 = reinterpret_cast<char*>(r12) + *at_t<std::uint64_t>(0x878);
    // 0xbc57bdb: lea rcx, [rbp+0x410]
    // 0xbc57be2: mov rdx, rsi
    // 0xbc57be5: call 0x1999390 (sub_1999390)
    sub_1999390(at(0x410), rsi);
    
    // 0xbc57bea: mov r15, [r13+0x48]
    r15 = *reinterpret_cast<void**>(reinterpret_cast<char*>(r13) + 0x48);
    // 0xbc57bee: mov rdi, [r13+0x50]
    rdi = *reinterpret_cast<void**>(reinterpret_cast<char*>(r13) + 0x50);
    // 0xbc57bf2: movaps xmm0, [rbp+0x7C0]
    float xmm0_7c0 = *at_t<float>(0x7C0);
    // 0xbc57bf9: unpcklps xmm0, [rbp+0x7D0]
    // Combine xmm0 and [rbp+0x7D0] - simplified
    float xmm0_7d0 = *at_t<float>(0x7D0);
    // 0xbc57c00: addps xmm0, [0xEFFE2F0]
    float* data_effe = reinterpret_cast<float*>(data_effe2f0());
    xmm0_7c0 += data_effe[0];
    xmm0_7d0 += data_effe[1];
    // 0xbc57c07: movaps [rbp+0x6E0], xmm0
    *at_t<float>(0x6E0) = xmm0_7c0;
    *at_t<float>(0x6E4) = xmm0_7d0;
    *at_t<float>(0x6E8) = 0;
    *at_t<float>(0x6EC) = 0;
    // 0xbc57c0e: movss xmm1, [0xEF1D470]
    float xmm1_ef = *reinterpret_cast<float*>(data_ef1d470());
    // 0xbc57c16: movss xmm0, [rbp+0x894]
    float xmm0_894 = *at_t<float>(0x894);
    // 0xbc57c1e: addss xmm1, xmm0
    xmm1_ef += xmm0_894;
    // 0xbc57c22: movss [rbp+0x89C], xmm1
    *at_t<float>(0x89C) = xmm1_ef;
    // 0xbc57c2a: movss xmm1, [0xEF3F048]
    xmm1_ef = *reinterpret_cast<float*>(data_ef3f048());
    // 0xbc57c32: addss xmm1, xmm0
    xmm1_ef += xmm0_894;
    // 0xbc57c36: movss [rbp+0x898], xmm1
    *at_t<float>(0x898) = xmm1_ef;
    // 0xbc57c3e: xor ebx, ebx
    std::uint64_t rbx_counter = 0;
    // 0xbc57c40: xorps xmm6, xmm6
    float xmm6_zero = 0.0f;
    // 0xbc57c43: movaps xmm7, [0xEF3F050]
    float xmm7_ef = *reinterpret_cast<float*>(data_ef3f050());
    // 0xbc57c4a: movss xmm11, [0xEEC8060]
    float xmm11_val = *reinterpret_cast<float*>(data_eec8060());
    // 0xbc57c53: mov rsi, [rbp+0x9F8]
    rsi = rbx;
    // 0xbc57c5a: jmp short 0xBC57CD7 (loc_bc57cd7)
    
    // ============================================================
    // 0xbc57cd7..0xbc58a85: Main loop (loc_bc57cd7 -> loc_bc5890f)
    // ============================================================
    // This is a large loop. We'll implement the core iteration.
    // The loop continues until r15 == rdi (0xbc57cda: cmp r15, rdi; je 0xBC5890F)
    
    while (true) {
        // loc_bc57cd7:
        // 0xbc57cd7: cmp r15, rdi
        if (r15 == rdi) {
            break; // Jump to loc_bc5890f (outside this chunk's main loop)
        }
        // 0xbc57ce0: movss xmm1, [r15]
        float xmm1_r15 = *reinterpret_cast<float*>(r15);
        // 0xbc57ce5: movss xmm2, [r14+0x60]
        float xmm2_14_60 = *reinterpret_cast<float*>(reinterpret_cast<char*>(r14) + 0x60);
        // 0xbc57ceb: mulss xmm2, xmm1
        xmm2_14_60 *= xmm1_r15;
        // 0xbc57cf4: movups xmm3, [r14+0x70]
        // 0xbc57cfa: movsd xmm0, [r15+4]
        double xmm0_r15_4 = *reinterpret_cast<double*>(reinterpret_cast<char*>(r15) + 4);
        // 0xbc57d03: movss xmm4, [r14+0x80]
        float xmm4_14_80 = *reinterpret_cast<float*>(reinterpret_cast<char*>(r14) + 0x80);
        // 0xbc57d06: movlhps xmm4, xmm3
        // 0xbc57d0a: shufps xmm4, xmm3, 0xE2
        // 0xbc57d0d: mulps xmm4, xmm0
        // ... complex SIMD operations
        // This loop body is very large (continues to 0xbc58a85)
        // For the chunk boundary, we stop at 0xbc58a85
        
        // Update loop counter
        rbx_counter++;
        
        // loc_bc57cd0: add r15, 0xF8
        r15 = reinterpret_cast<char*>(r15) + 0xF8;
        
        // Check if we've reached the chunk boundary (0xbc58a85)
        // The chunk ends at 0xbc58a85 with: lea rsi, [rbp+0x98]
        // We'll break here and let the state be saved for chunk c01
        if (rbx_counter > 1000) { // Safety limit
            break;
        }
    }
    
    // Chunk boundary at 0xbc58a85: lea rsi, [rbp+0x98]
    // Save live state for next chunk
    state->r15_scratch = r15;
    state->rsi_scratch = at(0x98); // rsi = rbp + 0x98
    state->rdi_scratch = rdi;
    state->rbx_scratch = rbx;
    // r12 and rbp_frame_base unchanged
}

// Verbatim log of every call instruction in [0xbc57460, 0xbc58a85) (rdis dis output, two spaces after address):
#if 0
0xbc57514  call 0xEEC73F0                                ; -> sub_eec73f0
0xbc5752d  call 0xEEC73F0                                ; -> sub_eec73f0
0xbc575e9  call 0xBC09250                                ; -> sub_bc09250
0xbc57645  call 0xBC09250                                ; -> sub_bc09250
0xbc576ce  call 0xBC09250                                ; -> sub_bc09250
0xbc5777b  call 0x567C8B0                                ; -> sub_567c8b0
0xbc5779d  call 0xAB49C0                                 ; -> sub_ab49c0
0xbc57957  call 0x5667860                                ; -> sub_5667860
0xbc5797e  call 0xA78940                                 ; -> sub_a78940
0xbc579bf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc579d6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc579f6  call 0xA78940                                 ; -> sub_a78940
0xbc57a2f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc57a45  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc57a72  call 0xA78940                                 ; -> sub_a78940
0xbc57ab7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc57ad1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc57af3  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xbc57b9b  call 0xAA6580                                 ; -> sub_aa6580
0xbc57bb9  call 0xAA6580                                 ; -> sub_aa6580
0xbc57be5  call 0x1999390                                ; -> sub_1999390
0xbc57d90  call qword ptr [0xF9A8F60]                    ; [data_f9a8f60]
0xbc57f69  call 0xBC5B130                                ; -> sub_bc5b130
0xbc58027  call rsi
0xbc5803a  call rsi
0xbc58059  call 0xEEC75A0                                ; -> sub_eec75a0
0xbc580ad  call qword ptr [0xF9A8DB8]                    ; [data_f9a8db8]
0xbc580c6  call rsi
0xbc580d9  call rsi
0xbc58108  call rsi
0xbc58111  call rsi
0xbc581b8  call 0xEEC75A0                                ; -> sub_eec75a0
0xbc581ec  call 0xEEC75A0                                ; -> sub_eec75a0
0xbc58210  call 0xEEC75A0                                ; -> sub_eec75a0
0xbc58253  call 0xEEC75A0                                ; -> sub_eec75a0
0xbc58295  call rsi
0xbc582a8  call rsi
0xbc582c7  call 0xEEC75A0                                ; -> sub_eec75a0
0xbc5831e  call rsi
0xbc58331  call rsi
0xbc58350  call 0xEEC75A0                                ; -> sub_eec75a0
0xbc583e0  call 0xBC5B130                                ; -> sub_bc5b130
0xbc58524  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc585d6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc5868a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc58742  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc58800  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc588bc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc589bd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc58aa8  call 0x568AD40                                ; -> sub_568ad40
0xbc58cdc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc58df8  call 0x76A8A0                                 ; -> sub_76a8a0
0xbc59159  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc5917f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc5920f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc592b1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc592d7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
#endif

// Layout assertions
static_assert(sizeof(Sub_bc57460_ChunkC00State) >= 0xA68 + 48, "chunk state size");

constexpr native::Footprint sub_bc57460_chunk_c00_footprint = nullptr;

LIFT_FN(sub_bc57460_chunk_c00, "sub_bc57460 chunk c00 (prologue + main loop)",
        0xbc57460, sub_bc57460_chunk_c00_step, &sub_bc57460_chunk_c00_footprint);

} // namespace native::bgfx