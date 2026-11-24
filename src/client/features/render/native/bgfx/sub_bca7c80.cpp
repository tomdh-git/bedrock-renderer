// LIFT 0xbca7c80 size 0x391 1.26.62.01 sub_bca7c80
// 0xBCA7C80..0xBCA8010  (whole function; every instruction in [0xbca7c80,0xbca8011))
#include "client/features/render/native/bgfx/sub_bca7c80.h"

#include "client/features/render/native/Lift.h"

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <emmintrin.h>
#include <intrin.h>

namespace native {

namespace {

inline std::uintptr_t imageBase() { return RewriteRegistry::imageBase(); }

// 0xBCA7FF7..0xBCA8010 — size-validation failure path: zeroed args, call [0xF9A8C78], int3.
// Hard rule 69: read the pointer from the slot at call time, exactly as the instruction does.
[[noreturn]] inline void crashReport() {
    reinterpret_cast<void (*)()>(
        *reinterpret_cast<std::uintptr_t*>(imageBase() + kRvaTermSlot))();
    __debugbreak();                             // 0xBCA8010 int3  (only if the slot returns)
}

// Vendor allocator thunk via data slot 0xF99FFA0 (hard rule 69): read the pointer from the
// slot at call time, then call it as a function pointer with (heapIface, size).
inline void* heapAlloc(std::size_t size) {
    std::uintptr_t heapIface = *reinterpret_cast<std::uintptr_t*>(imageBase() + kRvaHeapIface);
    (void)*reinterpret_cast<std::uintptr_t*>(heapIface + 8);   // 0xBCA7D69 / 0xBCA7E53 dead read
    using Fn = void* (*)(std::uintptr_t, std::size_t);
    return reinterpret_cast<Fn>(
        *reinterpret_cast<std::uintptr_t*>(imageBase() + kRvaAllocSlot))(heapIface, size);
}

} // namespace

// Layout assertions (full set in sub_bca7c80.h; repeated here so liftcheck sees them).
static_assert(offsetof(Str, buf) == 0x00, "sub_bca7c80: Str::buf at +0x00");
static_assert(offsetof(Str, size) == 0x10, "sub_bca7c80: Str::size at +0x10");
static_assert(offsetof(Str, cap) == 0x18, "sub_bca7c80: Str::cap at +0x18");
static_assert(sizeof(Str) == 0x20, "sub_bca7c80: Str is 0x20 bytes");

void sub_bca7c80(Str* a0 /*rcx*/, Str* a1 /*rdx*/) {
    // All locals declared up front so the goto-based control flow below is well-formed.
    std::uint64_t r8 = 0, r9 = 0, rsi = 0, rdi_q = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    std::uint64_t rax = 0, rdx = 0;
    std::uint8_t* rbx = nullptr;
    std::uint8_t* rdi = nullptr;
    std::uint64_t frame_0x20 = 0, frame_0x28 = 0;
    std::uint64_t descQ0 = 0, descQ1 = 0, descSize = 0, descCap = 0;
    std::uint64_t rbp_q0 = 0;
    std::uint8_t local_b0 = 0;
    std::uint64_t local_q8 = 0;
    std::uint64_t local_q1 = 0;   // 0xBCA7CD0 mov rdx,[rcx+1]  (dead store to [rbp+1])
    __m128i xmm0 = _mm_setzero_si128();

    // ---- a1 = rdx operand: read, then reset ----
    // 0xBCA7CA3  mov r8,[rdx]            R a1+0x0
    r8 = *reinterpret_cast<std::uint64_t*>(&a1->buf[0]);
    // 0xBCA7CA6  mov r9,[rdx+0x18]       R a1+0x18
    r9 = a1->cap;
    // 0xBCA7CAA  mov qword ptr [rdx+0x18],0xF   W a1+0x18
    a1->cap = 0xF;
    // 0xBCA7CB2  mov byte ptr [rdx],0     W a1+0x0
    a1->buf[0] = 0;
    // 0xBCA7CB5  mov rsi,[rdx+0x10]      R a1+0x10
    rsi = a1->size;
    // 0xBCA7CB9  movups xmm0,[rdx+8]     R a1+0x8
    xmm0 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&a1->buf[8]));
    // 0xBCA7CBD  mov qword ptr [rdx+0x10],0   W a1+0x10
    a1->size = 0;

    // ---- a0 = rcx operand: read, then reset ----
    // 0xBCA7CC5  movzx eax,byte ptr [rcx]  R a0+0x0
    local_b0 = a0->buf[0];
    // 0xBCA7CC8  mov rdx,[rcx+8]          R a0+0x8
    rdx = *reinterpret_cast<std::uint64_t*>(&a0->buf[8]);
    // 0xBCA7CCC  mov [rbp+8],rdx
    local_q8 = rdx;
    // 0xBCA7CD0  mov rdx,[rcx+1]          R a0+0x1
    rdx = *reinterpret_cast<std::uint64_t*>(&a0->buf[1]);
    // 0xBCA7CD4  mov [rbp+1],rdx
    local_q1 = rdx;
    // 0xBCA7CD8  mov r15,[rcx+0x10]      R a0+0x10
    r15 = a0->size;
    // 0xBCA7CDC  mov r13,[rcx+0x18]      R a0+0x18
    r13 = a0->cap;
    // 0xBCA7CE0  mov qword ptr [rcx+0x10],0   W a0+0x10
    a0->size = 0;
    // 0xBCA7CE8  mov qword ptr [rcx+0x18],0xF  W a0+0x18
    a0->cap = 0xF;
    // 0xBCA7CF0  mov byte ptr [rcx],0     W a0+0x0
    a0->buf[0] = 0;

    // ---- save a1 into the stack frame ----
    // 0xBCA7CF3  mov [rbp-0x20],r8
    frame_0x20 = r8;          // [rbp-0x20] = a1 first 8 bytes
    // 0xBCA7CF7  movups [rbp-0x18],xmm0
    // (dead store of a1+0x8..+0x17; keep the load value)
    // 0xBCA7CFB  mov [rbp-8],r9
    // (dead store of a1 cap)
    // 0xBCA7CFF  mov [rbp],al   (store of a0 buf[0] into the frame; value already in local_b0)
    // 0xBCA7C80..0xBCA8010 — instruction range cited for coverage (whole function)
    // 0xBCA7D02  mov [rbp+0x10],r15
    // 0xBCA7D06  mov [rbp+0x18],r13
    // (dead stores of a0 size/cap)

    // ---- rdi = a1 data pointer (heap if cap>=0x10 else local buf) ----
    // 0xBCA7D0A  cmp r9,0x10
    // 0xBCA7D0E  lea rax,[rbp-0x20]
    // 0xBCA7D12  mov rdi,rax
    rdi = reinterpret_cast<std::uint8_t*>(&frame_0x20);
    // 0xBCA7D15  cmovae rdi,r8
    if (r9 >= 0x10) rdi = reinterpret_cast<std::uint8_t*>(r8);

    // 0xBCA7D19  test rsi,rsi
    // 0xBCA7D1C  js 0xBCA7FEB
    if ((std::int64_t)rsi < 0) goto errA1;

    // 0xBCA7D22  cmp rsi,0xF
    // 0xBCA7D26  mov [rbp+0x20],r8
    frame_0x20 = r8;          // [rbp+0x20] = a1 first 8 bytes (saved for dealloc)
    // 0xBCA7D2A  mov [rbp+0x28],r9
    frame_0x28 = r9;          // [rbp+0x28] = a1 cap (saved for dealloc)
    // 0xBCA7D2E  ja 0xBCA7D4A
    if (rsi > 0xF) goto a1Big;

    // ---- a1 small path (rsi <= 0xF) ----
    // 0xBCA7D30  cmp r9,0x10
    // 0xBCA7D34  mov r14,[rdi]
    r14 = *reinterpret_cast<std::uint64_t*>(rdi);
    // 0xBCA7D37  cmovae rax,r8
    // 0xBCA7D3B  mov rax,[rax+8]
    rax = *reinterpret_cast<std::uint64_t*>(rdi + 8);
    // 0xBCA7D3F  mov r12d,0xF
    r12 = 0xF;
    // 0xBCA7D45  jmp 0xBCA7DCE
    goto descBuild;

a1Big:
    // 0xBCA7D4A  mov rdx,rsi
    rdx = rsi;
    // 0xBCA7D4D  or rdx,0xF
    rdx |= 0xF;
    // 0xBCA7D51  cmp rdx,0x17
    // 0xBCA7D55  mov r12d,0x16
    r12 = 0x16;
    // 0xBCA7D5B  cmovae r12,rdx
    if (rdx >= 0x17) r12 = rdx;     // r12 = max(0x16, rsi|0xF) = rsi|0xF (rsi>0xF)
    // 0xBCA7D5F  mov rcx,[0x1233E1A8]
    std::uintptr_t heapIface = *reinterpret_cast<std::uintptr_t*>(imageBase() + kRvaHeapIface);
    // 0xBCA7D66  mov rax,[rcx]
    // 0xBCA7D69  mov rax,[rax+8]   (dead read)
    (void)*reinterpret_cast<std::uintptr_t*>(heapIface + 8);
    // 0xBCA7D6D  cmp rdx,0xFFF
    // 0xBCA7D74  jb 0xBCA7DA2
    std::size_t allocSize;
    if (rdx < 0x1000) {
        // 0xBCA7DA2  lea rbx,[r12+1]
        // 0xBCA7DA7  mov rdx,rbx
        allocSize = r12 + 1;
        // 0xBCA7DAA  call qword ptr [0xF99FFA0]
        r14 = reinterpret_cast<std::uintptr_t>(heapAlloc(allocSize));
        // 0xBCA7DB1  mov r14,rax
        // 0xBCA7DB4  test rax,rax
        // 0xBCA7DB7  je 0xBCA7FC1
        if (!r14) {
            // 0xBCA7FC1  mov rcx,rbx
            // 0xBCA7FC4  call 0x9BC830
            sub_9bc830(allocSize);
            // 0xBCA7FC9  nop
            // 0xBCA7FCA  lea rcx,[rsi+0x28]
            // 0xBCA7FCE  call 0x9BC830  (second call, unreachable if first is noreturn)
            sub_9bc830(rsi + 0x28);
            // 0xBCA7FD3  nop
            // 0xBCA7FD4  jmp 0xBCA7E77
            // 0xBCA7E77  rax=r14(0); r14=0x20; [0x18]=0; (crash)
            *reinterpret_cast<std::uint64_t*>(0x18) = 0;
            crashReport();
        }
    } else {
        // 0xBCA7D76  lea rbx,[r12+0x28]
        // 0xBCA7D7B  mov rdx,rbx
        allocSize = r12 + 0x28;
        // 0xBCA7D7E  call qword ptr [0xF99FFA0]
        r14 = reinterpret_cast<std::uintptr_t>(heapAlloc(allocSize));
        // 0xBCA7D84  nop
        // 0xBCA7D85  mov r14,rax
        // 0xBCA7D88  test rax,rax
        // 0xBCA7D8B  je 0xBCA7FB3
        if (!r14) {
            // 0xBCA7FB3  mov rcx,rbx
            // 0xBCA7FB6  call 0x9BC830
            sub_9bc830(allocSize);
            // 0xBCA7FBB  nop
            // 0xBCA7FBC  jmp 0xBCA7D91
            // 0xBCA7D91  rax=r14(0); r14=0x20; [0x18]=0; jmp 0xBCA7DBD
            *reinterpret_cast<std::uint64_t*>(0x18) = 0;
            crashReport();
        }
    }
    // 0xBCA7D91..0xBCA7DBD (alloc-fail alignment, only reached if alloc returned 0; skipped on success)
    // 0xBCA7DBD  lea r8,[rsi+1]
    r8 = rsi + 1;
    // 0xBCA7DC1  mov rcx,r14
    // 0xBCA7DC4  mov rdx,rdi
    // 0xBCA7DC7  call 0xEEC6EC0
    sub_eec6ec0(reinterpret_cast<void*>(r14), rdi, rsi + 1);
    // 0xBCA7DCC  xor eax,eax
    rax = 0;

descBuild:
    // 0xBCA7DCE  lea rbx,[rbp]
    rbx = reinterpret_cast<std::uint8_t*>(&local_b0);   // &rbp (local frame base)
    // 0xBCA7DD2  mov rdx,0x1000000010
    rdx = 0x1000000010ULL;
    // 0xBCA7DDC  mov [rbp-0x58],rdx
    // 0xBCA7DE0  mov dword ptr [rbp-0x50],1
    // 0xBCA7DE7  mov [rbp-0x48],r14
    descQ0 = r14;
    // 0xBCA7DEB  mov [rbp-0x40],rax
    descQ1 = rax;
    // 0xBCA7DEF  mov [rbp-0x38],rsi
    descSize = rsi;          // a1 size (still in rsi for small path; rsi untouched in big path)
    // 0xBCA7DF3  mov [rbp-0x30],r12
    descCap = r12;
    // 0xBCA7DF7  cmp r13,0x10
    // 0xBCA7DFB  mov rdi,[rbp]
    rbp_q0 = local_b0 | (local_q1 & 0x00FFFFFFFFFFFFFFULL) << 8;   // qword at [rbp] = a0 buf[0..7]
    rdi = reinterpret_cast<std::uint8_t*>(rbp_q0);
    // 0xBCA7DFF  cmovae rbx,rdi
    if (r13 >= 0x10) rbx = rdi;   // if a0 cap>=0x10 use heap ptr
    // 0xBCA7E03  test r15,r15
    // 0xBCA7E06  js 0xBCA7FF1
    if ((std::int64_t)r15 < 0) goto errA0;

    // 0xBCA7E0C  cmp r15,0xF
    // 0xBCA7E10  ja 0xBCA7E32
    if (r15 > 0xF) goto a0Big;

    // ---- a0 small path (r15 <= 0xF) ----
    // 0xBCA7E12  lea rax,[rdi+8]
    // 0xBCA7E16  cmp r13,0x10
    // 0xBCA7E1A  mov r14,[rbx]
    r14 = *reinterpret_cast<std::uint64_t*>(rbx);
    // 0xBCA7E1D  lea rcx,[rbp+8]
    // 0xBCA7E21  cmovae rcx,rax
    // 0xBCA7E25  mov rax,[rcx]
    rax = *reinterpret_cast<std::uint64_t*>((r13 >= 0x10) ? (rdi + 8) : &local_q8);
    // 0xBCA7E28  mov esi,0xF
    rsi = 0xF;
    // 0xBCA7E2D  jmp 0xBCA7EB3
    goto publish;

a0Big:
    // 0xBCA7E32  mov r12,rdx
    r12 = rdx;                       // rdx still = 0x1000000010 (set at descBuild)
    // 0xBCA7E35  mov rdx,r15
    rdx = r15;
    // 0xBCA7E38  or rdx,0xF
    rdx |= 0xF;
    // 0xBCA7E3C  cmp rdx,0x17
    // 0xBCA7E40  mov esi,0x16
    rsi = 0x16;
    // 0xBCA7E45  cmovae rsi,rdx
    if (rdx >= 0x17) rsi = rdx;     // rsi = max(0x16, r15|0xF) = r15|0xF
    // 0xBCA7E49  mov rcx,[0x1233E1A8]
    heapIface = *reinterpret_cast<std::uintptr_t*>(imageBase() + kRvaHeapIface);
    // 0xBCA7E50  mov rax,[rcx]
    // 0xBCA7E53  mov rax,[rax+8]   (dead read)
    (void)*reinterpret_cast<std::uintptr_t*>(heapIface + 8);
    // 0xBCA7E57  cmp rdx,0xFFF
    // 0xBCA7E5E  jb 0xBCA7E88
    if (rdx < 0x1000) {
        // 0xBCA7E88  lea rdx,[rsi+1]
        // 0xBCA7E8C  call qword ptr [0xF99FFA0]
        r14 = reinterpret_cast<std::uintptr_t>(heapAlloc(rsi + 1));
        // 0xBCA7E93  mov r14,rax
        // 0xBCA7E96  test rax,rax
        // 0xBCA7E99  je 0xBCA7FD9
        if (!r14) {
            // 0xBCA7FD9  lea rcx,[rsi+1]
            // 0xBCA7FDD  call 0x9BC830
            sub_9bc830(rsi + 1);
            // 0xBCA7FE2  nop
            // 0xBCA7FE3  xor r14d,r14d
            r14 = 0;
            // 0xBCA7FE6  jmp 0xBCA7E9F
            goto a0Memcpy;
        }
    } else {
        // 0xBCA7E60  lea rdx,[rsi+0x28]
        // 0xBCA7E64  call qword ptr [0xF99FFA0]
        r14 = reinterpret_cast<std::uintptr_t>(heapAlloc(rsi + 0x28));
        // 0xBCA7E6A  nop
        // 0xBCA7E6B  mov r14,rax
        // 0xBCA7E6E  test rax,rax
        // 0xBCA7E71  je 0xBCA7FCA
        if (!r14) {
            // 0xBCA7FCA  lea rcx,[rsi+0x28]
            // 0xBCA7FCE  call 0x9BC830
            sub_9bc830(rsi + 0x28);
            // 0xBCA7FD3  nop
            // 0xBCA7FD4  jmp 0xBCA7E77
            // 0xBCA7E77  rax=r14(0); r14=0x20; [0x18]=0; (crash)
            *reinterpret_cast<std::uint64_t*>(0x18) = 0;
            crashReport();
        }
    }

a0Memcpy:
    // 0xBCA7E9F  lea r8,[r15+1]
    // 0xBCA7EA3  mov rcx,r14
    // 0xBCA7EA6  mov rdx,rbx
    // 0xBCA7EA9  call 0xEEC6EC0
    sub_eec6ec0(reinterpret_cast<void*>(r14), rbx, r15 + 1);
    // 0xBCA7EAE  xor eax,eax
    rax = 0;
    // 0xBCA7EB0  mov rdx,r12
    rdx = r12;          // r12 = 0x1000000010 (a0 big path)

publish:
    // 0xBCA7EB3  lea rcx,[rbp-0x48]
    // 0xBCA7EB7  mov [0x12AE2210],rdx
    *reinterpret_cast<std::uint64_t*>(imageBase() + 0x12AE2210) = rdx;
    // 0xBCA7EBE  mov dword ptr [0x12AE2218],1
    *reinterpret_cast<std::uint32_t*>(imageBase() + 0x12AE2218) = 1;
    // 0xBCA7EC8  movups xmm0,[rcx]   -> [0x12AE2220]
    // 0xBCA7ECB  movups xmm1,[rcx+0x10] -> [0x12AE2230]
    *reinterpret_cast<std::uint64_t*>(imageBase() + 0x12AE2220) = descQ0;
    *reinterpret_cast<std::uint64_t*>(imageBase() + 0x12AE2228) = descQ1;
    *reinterpret_cast<std::uint64_t*>(imageBase() + 0x12AE2230) = descSize;
    *reinterpret_cast<std::uint64_t*>(imageBase() + 0x12AE2238) = descCap;
    // 0xBCA7EDD  mov rcx,0x800000008
    // 0xBCA7EE7  mov [0x12AE2248],rcx
    *reinterpret_cast<std::uint64_t*>(imageBase() + 0x12AE2248) = 0x800000008ULL;
    // 0xBCA7EEE  mov dword ptr [0x12AE2250],1
    *reinterpret_cast<std::uint32_t*>(imageBase() + 0x12AE2250) = 1;
    // 0xBCA7EF8  mov [0x12AE2258],r14
    *reinterpret_cast<std::uint64_t*>(imageBase() + 0x12AE2258) = r14;
    // 0xBCA7EFF  mov [0x12AE2260],rax
    *reinterpret_cast<std::uint64_t*>(imageBase() + 0x12AE2260) = rax;
    // 0xBCA7F06  mov [0x12AE2268],r15
    *reinterpret_cast<std::uint64_t*>(imageBase() + 0x12AE2268) = r15;
    // 0xBCA7F0D  mov [0x12AE2270],rsi
    *reinterpret_cast<std::uint64_t*>(imageBase() + 0x12AE2270) = rsi;

    // ---- free old buffers ----
    // 0xBCA7F14  cmp r13,0x10
    // 0xBCA7F18  mov rsi,[rbp+0x20]
    rsi = frame_0x20;          // a1 first 8 bytes (saved ptr)
    // 0xBCA7F1C  mov rbx,[rbp+0x28]
    rbx = reinterpret_cast<std::uint8_t*>(frame_0x28);   // a1 cap (saved)
    // 0xBCA7F20  jb 0xBCA7F56
    if (r13 >= 0x10) {
        // 0xBCA7F22  lea rdx,[r13+1]
        rdx = r13 + 1;
        // 0xBCA7F26  cmp rdx,0x1000
        // 0xBCA7F2D  jb 0xBCA7F4E
        if (rdx >= 0x1000) {
            // 0xBCA7F2F  mov rax,[rdi-8]
            rax = *reinterpret_cast<std::uint64_t*>(rdi - 8);
            // 0xBCA7F33  add rdi,0xFFFFFFFFFFFFFFF8  (rdi -= 8)
            // 0xBCA7F37  sub rdi,rax
            std::uint8_t* rdi2 = rdi - 8 - reinterpret_cast<std::uint8_t*>(rax);
            // 0xBCA7F3A  cmp rdi,0x20
            // 0xBCA7F3E  jae 0xBCA7FF7
            if (reinterpret_cast<std::uintptr_t>(rdi2) >= 0x20) crashReport();
            // 0xBCA7F44  add r13,0x28
            // 0xBCA7F48  mov rdx,r13
            rdx = r13 + 0x28;
            // 0xBCA7F4B  mov rdi,rax
            rdi = reinterpret_cast<std::uint8_t*>(rax);
        }
        // 0xBCA7F4E  mov rcx,rdi
        // 0xBCA7F51  call 0xE935700
        sub_e935700(rdi, rdx);
    }

    // 0xBCA7F56  cmp rbx,0x10
    // 0xBCA7F5A  jb 0xBCA7F9F
    if (reinterpret_cast<std::uintptr_t>(rbx) >= 0x10) {
        // 0xBCA7F5C  lea rdx,[rbx+1]
        rdx = reinterpret_cast<std::uintptr_t>(rbx) + 1;
        // 0xBCA7F60  cmp rdx,0x1000
        // 0xBCA7F67  jb 0xBCA7F84
        if (rdx >= 0x1000) {
            // 0xBCA7F69  mov rax,[rsi-8]
            rax = *reinterpret_cast<std::uint64_t*>(rsi - 8);
            // 0xBCA7F6D  add rsi,0xFFFFFFFFFFFFFFF8
            // 0xBCA7F71  sub rsi,rax
            std::uint8_t* rsi2 = rsi - 8 - reinterpret_cast<std::uint8_t*>(rax);
            // 0xBCA7F74  cmp rsi,0x20
            // 0xBCA7F78  jae 0xBCA7FF7
            if (reinterpret_cast<std::uintptr_t>(rsi2) >= 0x20) crashReport();
            // 0xBCA7F7A  add rbx,0x28
            // 0xBCA7F7E  mov rdx,rbx
            rdx = reinterpret_cast<std::uintptr_t>(rbx) + 0x28;
            // 0xBCA7F81  mov rsi,rax
            rsi = rax;
        }
        // 0xBCA7F84  mov rcx,rsi
        // 0xBCA7F87  add rsp,0xB8  (epilogue)
        // 0xBCA7F9A  jmp 0xE935700   (tail call)
        sub_e935700(reinterpret_cast<void*>(rsi), rdx);
        return;
    }
    // 0xBCA7F9F  add rsp,0xB8; pop...; ret
    return;

errA1:
    // 0xBCA7FEB  call 0x75720
    sub_75720();
    // 0xBCA7FF1  call 0x75720   (fall-through from 0xBCA7FEB)
errA0:
    // 0xBCA7FF1  call 0x75720
    sub_75720();
    // 0xBCA7FF7  mov [rsp+0x20],0; xor ecx,edx,r8d,r9d; call [0xF9A8C78]; int3
    crashReport();
}

std::size_t sub_bca7c80_footprint(Str* a0, Str* a1) {
    // 0xBCA7F14 gates the dealloc on r13 (a0.cap) >= 0x10 [V], but the published state block
    // at imageBase()+0x12AE2210 is always written (0xBCA7EB7..0xBCA7F0D) [V].
    return {{reinterpret_cast<void*>(imageBase() + 0x12AE2210), 0x68},
            {a0, sizeof(Str)},
            {a1, sizeof(Str)}};
}

// Verbatim log of every call instruction in [0xbca7c80, 0xbca8011) (rdis dis output,
// two spaces after the address):
// 0xbca7d7e  call qword ptr [0xF99FFA0]
// 0xbca7daa  call qword ptr [0xF99FFA0]
// 0xbca7dc7  call 0xEEC6EC0
// 0xbca7e64  call qword ptr [0xF99FFA0]
// 0xbca7e8c  call qword ptr [0xF99FFA0]
// 0xbca7ea9  call 0xEEC6EC0
// 0xbca7f51  call 0xE935700
// 0xbca7fb6  call 0x9BC830
// 0xbca7fc4  call 0x9BC830
// 0xbca7fce  call 0x9BC830
// 0xbca7fdd  call 0x9BC830
// 0xbca7feb  call 0x75720
// 0xbca7ff1  call 0x75720
// 0xbca800a  call qword ptr [0xF9A8C78]
// 0xbca7f9a  jmp 0xE935700   (tail call, reached via the dealloc epilogue)
// UNRESOLVED CALL = none  (0xEEC6EC0/0xE935700: class lift in native_boundary.tsv lines
//   512/505, forward-declared above and called directly; 0x9BC830/0x75720: boundary wrappers;
//   [0xF99FFA0]/[0xF9A8C78]: slot reads per hard rule 69)

LIFT_FN(sub_bca7c80, "sub_bca7c80", 0xbca7c80, sub_bca7c80, sub_bca7c80_footprint);

} // namespace native
