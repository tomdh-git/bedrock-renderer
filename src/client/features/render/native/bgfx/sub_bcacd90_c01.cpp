// LIFT 0xbcacd90 size 0x4f7b 1.26.62.01 sub_bcacd90
// CHUNK 0xbcae56d..0xbcafd5f

#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bcacd90_c01.h"

#include <cstdint>
#include <intrin.h>

namespace native::bgfx {
namespace {

// Lift-set callees (already lifted by their own units).
extern "C" void sub_5679db0(void* uniform_array, void* index_record, void* data_record); // 0x5679db0  UniformBlock::setUniform
extern "C" void sub_568ad40(void* a1, void* a2); // 0x568ad40
extern "C" void sub_568c420(void* a1, void* a2); // 0x568c420
extern "C" void sub_5693a80(void* a1, void* a2); // 0x5693a80
extern "C" void sub_56b8630(void* a1, void* a2, void* a3); // 0x56b8630
extern "C" void sub_56c9740(void* a1); // 0x56c9740
extern "C" void sub_6760450(void* a1, void* a2); // 0x6760450
extern "C" void sub_bc039a0(void* a1, void* a2, void* a3, void* a4); // 0xbc039a0
extern "C" void sub_bc03cd0(void* a1); // 0xbc03cd0
extern "C" void sub_bc04620(void* a1, void* a2, void* a3); // 0xbc04620
extern "C" void sub_bc04bb0(void* a1, void* a2, void* a3); // 0xbc04bb0
extern "C" void sub_bc054a0(void* a1, void* a2); // 0xbc054a0
extern "C" void sub_bcaba00(void* a1, void* a2, void* a3, void* a4, void* a5); // 0xbcaba00
extern "C" void sub_e869ff0(void* a1, void* a2); // 0xe869ff0
extern "C" void sub_e86ced0(void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7); // 0xe86ced0
extern "C" void sub_eec6de0(void* a1, void* a2, void* a3); // 0xeec6de0

// Boundary callees (native::boundary wrappers resolved at link time)
namespace boundary {
    extern "C" void sub_73150(void* a1);
    extern "C" void sub_75b60(void* a1);
    extern "C" void sub_78ed0(void* a1);
    extern "C" void sub_79580(void* a1, void* a2);
    extern "C" void sub_9d6d0(void* a1, void* a2, void* a3);
    extern "C" void sub_2679a0(void* a1, void* a2, void* a3);
    extern "C" void sub_76a8a0(void* a1, void* a2, void* a3);
    extern "C" void sub_9bc830(uint32_t size);
    extern "C" void sub_e935700(void* a1, void* a2, void* a3);
    extern "C" void sub_e938cb0(void* a1);
    extern "C" void sub_e938d70(void* a1);
    extern "C" void sub_e9e7970(void* a1);
    extern "C" void sub_f9a8c78();
    extern "C" void sub_eea6040(void* a1);
}

// Data slot addresses (from disassembly)
constexpr std::uintptr_t F99FFA0 = 0xF99FFA0; // allocator thunk -> sub_eea6040
constexpr std::uintptr_t F9A8C78 = 0xF9A8C78; // fatal-log thunk
constexpr std::uintptr_t F5C5E67 = 0xF5C5E67; // "ColorPostProcessPhase"
constexpr std::uintptr_t F547EEF = 0xF547EEF; // "ColorPostProcess"
constexpr std::uintptr_t F221610 = 0xF221610; // vtable
constexpr std::uintptr_t F44B7F0 = 0xF44B7F0; // jump table
constexpr std::uintptr_t F44B7C0 = 0xF44B7C0; // data
constexpr std::uintptr_t EFD3400 = 0xEFD3400; // double constant

// Global data addresses
constexpr std::uintptr_t DATA_12AE22B0 = 0x12AE22B0;
constexpr std::uintptr_t DATA_129C13C0 = 0x129C13C0;
constexpr std::uintptr_t DATA_128767C8 = 0x128767C8;
constexpr std::uintptr_t DATA_1233E1A8 = 0x1233E1A8;
constexpr std::uintptr_t DATA_12AE24B8 = 0x12AE24B8;
constexpr std::uintptr_t DATA_128C1A60 = 0x128C1A60;
constexpr std::uintptr_t DATA_12AE24B0 = 0x12AE24B0;
constexpr std::uintptr_t DATA_12AE23E0 = 0x12AE23E0;
constexpr std::uintptr_t DATA_12AE2450 = 0x12AE2450;
constexpr std::uintptr_t DATA_12AE2400 = 0x12AE2400;
constexpr std::uintptr_t DATA_128C1A58 = 0x128C1A58;
constexpr std::uintptr_t DATA_12AE2430 = 0x12AE2430;
constexpr std::uintptr_t DATA_12AE23F0 = 0x12AE23F0;

} // namespace

static inline void sub_bcacd90_chunk01(ChunkState_bcacd90_c01& s) {
    std::uint8_t* rbp = reinterpret_cast<std::uint8_t*>(s.rbp_frame_base);
    const std::uintptr_t base = RewriteRegistry::imageBase();

    // Live register aliases from chunk state
    void*& r8 = s.r8_current_slot;
    auto& r9 = s.r9_remaining;
    void*& rdx = s.rdx_slot_base;
    void*& r12 = s.r12_scratch;
    void*& r13 = s.r13_scratch;
    void*& r14 = s.r14_scratch;
    void*& r15 = s.r15_scratch;

    // ---- 0xbcae56d..0xbcae597 : slot availability gate + first call ----
    // 0xbcae56d  sub r8d,eax
    // 0xbcae570  shr r8d,4
    // 0xbcae574  mov [rbp],r8w
    *reinterpret_cast<std::uint16_t*>(rbp) = static_cast<std::uint16_t>((reinterpret_cast<std::uintptr_t>(r8) - 0) >> 4);
    // 0xbcae579  mov byte ptr [rbp+2],1
    rbp[2] = 1;
    // 0xbcae57d  mov rdx,rbp
    rdx = rbp;
    // 0xbcae580  lea r8,[rbp+0x310]
    r8 = rbp + 0x310;
    // 0xbcae587  mov rcx,[rbp+0xF50]
    void* rcx = *reinterpret_cast<void**>(rbp + 0xF50);
    // 0xbcae58e  call 0x5679DB0
    sub_5679db0(rcx, rdx, r8);
    // 0xbcae593  cmp dword ptr [rdi+8],2
    // 0xbcae597  jne 0xBCAE7DA
    std::uint8_t* rdi = *reinterpret_cast<std::uint8_t**>(rbp + 0x1040); // rdi from 0xbcae7e1
    if (*reinterpret_cast<std::uint32_t*>(rdi + 8) != 2) {
        s.branch = 0xBCAE7DA;
        return;
    }

    // ---- 0xbcae59d..0xbcae5ce : reference count path ----
    // 0xbcae59d  mov rsi,[0x12AE22B0]
    std::uint8_t* rsi = *reinterpret_cast<std::uint8_t**>(base + DATA_12AE22B0);
    // 0xbcae5a4  test rsi,rsi
    // 0xbcae5a7  je short 0xBCAE5DF
    if (rsi == nullptr) {
        // fall through to 0xbcae5df
    } else {
        // 0xbcae5a9  mov eax,[0x129C13C0]
        std::uint32_t eax = *reinterpret_cast<std::uint32_t*>(base + DATA_129C13C0);
        // 0xbcae5af  mov ecx,[0x128767C8]
        std::uint32_t ecx = *reinterpret_cast<std::uint32_t*>(base + DATA_128767C8);
        // 0xbcae5b5  mov rdx,gs:[0x58]
        // 0xbcae5be  mov rcx,[rdx+rcx*8]
        std::uint8_t* tls = reinterpret_cast<std::uint8_t*>(__readgsqword(0x58));
        std::uint8_t* frame = *reinterpret_cast<std::uint8_t**>(tls + ecx * 8);
        // 0xbcae5c2  cmp eax,[rcx+4]
        // 0xbcae5c8  jg 0xBCB04E3
        if (eax > *reinterpret_cast<std::uint32_t*>(frame + 4)) {
            s.branch = 0xBCB04E3;
            return;
        }
        // loc_bcae5ce:
        // 0xbcae5ce  lock inc word ptr [rsi+0x10]
        _InterlockedIncrement16(reinterpret_cast<short*>(rsi + 0x10));
        // 0xbcae5d3  movzx eax,byte ptr [rsi+0x12]
        // 0xbcae5d7  test al,1
        // 0xbcae5d9  jne 0xBCAE701
        if ((rsi[0x12] & 1) != 0) {
            s.branch = 0xBCAE701;
            return;
        }
        // fall through to loc_bcae5df
    }

    // ---- 0xbcae5df..0xbcae6cf : vector grow + memcpy + sub_eec6de0 + sub_e86ced0 ----
    // 0xbcae5df  movss xmm6,[rdi+0x30]
    s.xmm6_live = *reinterpret_cast<float*>(rdi + 0x30);
    // 0xbcae5e4  movss xmm8,[rdi+0x28]
    s.xmm8_live = *reinterpret_cast<float*>(rdi + 0x28);
    // 0xbcae5ea  movss xmm7,[rdi+0x2C]
    s.xmm7_live = *reinterpret_cast<float*>(rdi + 0x2C);
    // 0xbcae5ef  xorps xmm0,xmm0
    // 0xbcae5f2  movaps [rbp+0xEE0],xmm0
    *reinterpret_cast<__m128*>(rbp + 0xEE0) = _mm_setzero_ps();
    // 0xbcae5f9  mov qword ptr [rbp+0xEF0],0
    *reinterpret_cast<std::uint64_t*>(rbp + 0xEF0) = 0;
    // 0xbcae604  mov r12,[rdi+0x18]
    r12 = *reinterpret_cast<void**>(rdi + 0x18);
    // 0xbcae608  mov rcx,[rdi+0x10]
    void* rcx2 = *reinterpret_cast<void**>(rdi + 0x10);
    // 0xbcae60c  mov rax,r12
    // 0xbcae60f  sub rax,rcx
    std::uintptr_t rax = reinterpret_cast<std::uintptr_t>(r12) - reinterpret_cast<std::uintptr_t>(rcx2);
    // 0xbcae612  sub r12,rcx
    r12 = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(r12) - reinterpret_cast<std::uintptr_t>(rcx2));
    // 0xbcae615  je 0xBCAE6CF
    if (rax == 0) {
        s.branch = 0xBCAE6CF;
        // will continue at 0xbcae6cf below
    } else {
        // 0xbcae61b  sar rax,3
        rax >>= 3;
        // 0xbcae61f  mov rcx,rax
        // 0xbcae622  shr rcx,0x3D
        // 0xbcae626  jne 0xBCB0519
        if ((rax >> 0x3D) != 0) {
            s.branch = 0xBCB0519;
            return;
        }
        // 0xbcae62c  cmp rax,0x200
        // 0xbcae632  jb short 0xBCAE66D
        if (rax < 0x200) {
            // loc_bcae66d:
            // 0xbcae66d  mov rcx,[0x1233E1A8]
            void* alloc_ecx = *reinterpret_cast<void**>(base + DATA_1233E1A8);
            alloc_ecx = *reinterpret_cast<void**>(alloc_ecx);
            alloc_ecx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(alloc_ecx) + 8);
            // 0xbcae67b  mov rdx,r12
            // 0xbcae67e  call qword ptr [0xF99FFA0]
            void* (*alloc_fn)(void*) = *reinterpret_cast<void* (*)(void*)*>(base + F99FFA0);
            void* alloc_result = alloc_fn(r12);
            // 0xbcae684  mov r13,rax
            r13 = alloc_result;
            // 0xbcae687  test rax,rax
            // 0xbcae68a  je 0xBCAF66F
            if (alloc_result == nullptr) {
                s.branch = 0xBCAF66F;
                return;
            }
            // fall through to loc_bcae690
        } else {
            // loc_bcae634:
            // 0xbcae634  lea r13,[r12+0x27]
            r13 = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(r12) + 0x27);
            // 0xbcae639  mov rcx,[0x1233E1A8]
            void* alloc_ecx = *reinterpret_cast<void**>(base + DATA_1233E1A8);
            alloc_ecx = *reinterpret_cast<void**>(alloc_ecx);
            alloc_ecx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(alloc_ecx) + 8);
            // 0xbcae647  mov rdx,r13
            // 0xbcae64a  call qword ptr [0xF99FFA0]
            void* (*alloc_fn)(void*) = *reinterpret_cast<void* (*)(void*)*>(base + F99FFA0);
            void* alloc_result = alloc_fn(r13);
            // 0xbcae650  mov rbx,rax
            void* rbx = alloc_result;
            // 0xbcae653  test rax,rax
            // 0xbcae656  je 0xBCAF662
            if (alloc_result == nullptr) {
                s.branch = 0xBCAF662;
                return;
            }
            // loc_bcae65c:
            // 0xbcae65c  mov r13,rbx
            r13 = rbx;
            // 0xbcae65f  add r13,0x27
            r13 = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(r13) + 0x27);
            // 0xbcae663  and r13,0xFFFFFFFFFFFFFFE0
            r13 = reinterpret_cast<void*>((reinterpret_cast<std::uintptr_t>(r13)) & 0xFFFFFFFFFFFFFFE0ULL);
            // 0xbcae667  mov [r13-8],rbx
            *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(r13) - 8) = rbx;
            // 0xbcae66b  jmp short 0xBCAE690
            // fall through to loc_bcae690
        }
        // loc_bcae690:
        // 0xbcae690  mov [rbp+0xEE0],r13
        *reinterpret_cast<void**>(rbp + 0xEE0) = r13;
        // 0xbcae697  mov [rbp+0xEE8],r13
        *reinterpret_cast<void**>(rbp + 0xEE8) = r13;
        // 0xbcae69e  add r12,r13
        r12 = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(r12) + reinterpret_cast<std::uintptr_t>(r13));
        // 0xbcae6a1  mov [rbp+0xEF0],r12
        *reinterpret_cast<void**>(rbp + 0xEF0) = r12;
        // 0xbcae6a8  mov rdx,[rdi+0x10]
        rdx = *reinterpret_cast<void**>(rdi + 0x10);
        // 0xbcae6ac  mov rbx,[rdi+0x18]
        rbx = *reinterpret_cast<void**>(rdi + 0x18);
        // 0xbcae6b0  sub rbx,rdx
        rbx = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(rbx) - reinterpret_cast<std::uintptr_t>(rdx));
        // 0xbcae6b3  mov rcx,r13
        rcx2 = r13;
        // 0xbcae6b6  mov r8,rbx
        r8 = rbx;
        // 0xbcae6b9  call 0xEEC6DE0
        sub_eec6de0(rcx2, rdx, r8);
        // 0xbcae6be  add rbx,r13
        rbx = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(rbx) + reinterpret_cast<std::uintptr_t>(r13));
        // 0xbcae6c1  mov [rbp+0xEE8],rbx
        *reinterpret_cast<void**>(rbp + 0xEE8) = rbx;
        // 0xbcae6c8  mov r13,[rbp+0x1018]
        r13 = *reinterpret_cast<void**>(rbp + 0x1018);
    }

    // ---- 0xbcae6cf..0xbcae6fc : ColorPostProcessPhase registration ----
    // loc_bcae6cf:
    // 0xbcae6cf  movss [rsp+0x30],xmm8
    *reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(&rbp[0]) + 0x30) = s.xmm8_live;
    // 0xbcae6d6  movss [rsp+0x28],xmm6
    *reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(&rbp[0]) + 0x28) = s.xmm6_live;
    // 0xbcae6dc  movss [rsp+0x20],xmm7
    *reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(&rbp[0]) + 0x20) = s.xmm7_live;
    // 0xbcae6e2  lea rdx,[0x12AE22B0]
    rdx = reinterpret_cast<void*>(base + DATA_12AE22B0);
    // 0xbcae6e9  lea r8,[rbp+0xEE0]
    r8 = rbp + 0xEE0;
    // 0xbcae6f0  mov rcx,[rbp+0xF38]
    rcx2 = *reinterpret_cast<void**>(rbp + 0xF38);
    // 0xbcae6f7  mov r9w,0x100
    std::uint16_t r9w = 0x100;
    // 0xbcae6fc  call 0xE86CED0
    sub_e86ced0(rcx2, rdx, r8, reinterpret_cast<void*>(static_cast<std::uintptr_t>(r9w)), 
                reinterpret_cast<void*>(&rbp[0] + 0x30), reinterpret_cast<void*>(&rbp[0] + 0x28), reinterpret_cast<void*>(&rbp[0] + 0x20));

    // ---- 0xbcae7da..0xbcae87b : ColorPostProcessPhase builder (slot available path) ----
    // 0xbcae7da  mov r14,[rbp+0x1048]
    r14 = *reinterpret_cast<void**>(rbp + 0x1048);
    // 0xbcae7e1  mov rdi,[rbp+0x1040]
    rdi = *reinterpret_cast<std::uint8_t**>(rbp + 0x1040);
    // 0xbcae7e8  mov rax,[rbp+0x1010]
    void* rax_ptr = *reinterpret_cast<void**>(rbp + 0x1010);
    // 0xbcae7ef  movsd xmm0,[rax]
    double xmm0_val = *reinterpret_cast<double*>(rax_ptr);
    // 0xbcae7f3  movups [rbp+0xA80],xmm0
    *reinterpret_cast<__m128*>(rbp + 0xA80) = _mm_set_sd(xmm0_val);
    // 0xbcae7fa  mov qword ptr [rbp+0x310],1
    *reinterpret_cast<std::uint64_t*>(rbp + 0x310) = 1;
    // 0xbcae805  lea rax,[rbp+0xA80]
    // 0xbcae80c  mov [rbp+0x318],rax
    *reinterpret_cast<void**>(rbp + 0x318) = rbp + 0xA80;
    // 0xbcae813  mov rax,[r13+0x38]
    std::uint8_t* rax2 = *reinterpret_cast<std::uint8_t**>(reinterpret_cast<std::uint8_t*>(r13) + 0x38);
    // 0xbcae817  movzx r8d,word ptr [r13+0x42]
    std::uint16_t r8d = *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uint8_t*>(r13) + 0x42);
    // 0xbcae81c  mov edx,r8d
    std::uint32_t edx = r8d;
    // 0xbcae81f  shl edx,4
    edx <<= 4;
    // 0xbcae822  mov rcx,rax2
    rcx2 = rax2;
    // 0xbcae825  test r8d,r8d
    // 0xbcae828  je short 0xBCAE855
    if (r8d == 0) {
        s.branch = 0xBCAE855;
    } else {
        // 0xbcae82a  mov r8,[0x12AE23E0]
        void* r8_ptr = *reinterpret_cast<void**>(base + DATA_12AE23E0);
        // 0xbcae831  mov r9,rdx
        void* r9_ptr = reinterpret_cast<void*>(edx);
        // 0xbcae834  mov rcx,rax2
        rcx2 = rax2;
        // 0xbcae837  nop [rax+rax]
        // loop at 0xbcae840..0xbcae851
        for (;;) {
            // 0xbcae840  mov r10,[rcx]
            void* r10 = *reinterpret_cast<void**>(rcx2);
            // 0xbcae843  cmp [r10+0x28],r8
            if (*reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(r10) + 0x28) == r8_ptr) {
                // 0xbcae847  je short 0xBCAE855
                break;
            }
            // 0xbcae849  add rcx,0x10
            rcx2 = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(rcx2) + 0x10);
            // 0xbcae84d  add r9,0xFFFFFFFFFFFFFFF0
            r9_ptr = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(r9_ptr) - 0x10);
            // 0xbcae851  jne short 0xBCAE840
            if (reinterpret_cast<std::uintptr_t>(r9_ptr) != 0) continue;
            // 0xbcae853  jmp short 0xBCAE880
            s.branch = 0xBCAE880;
            goto L_BCAE880;
        }
        // loc_bcae855:
        // 0xbcae855  add rdx,rax2
        rdx = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(rdx) + reinterpret_cast<std::uintptr_t>(rax2));
        // 0xbcae858  cmp rcx,rdx
        // 0xbcae85b  jae short 0xBCAE880
        if (reinterpret_cast<std::uintptr_t>(rcx2) >= reinterpret_cast<std::uintptr_t>(rdx)) {
            s.branch = 0xBCAE880;
            goto L_BCAE880;
        }
        // 0xbcae85d  sub ecx,eax
        std::uint32_t ecx2 = reinterpret_cast<std::uintptr_t>(rcx2) - reinterpret_cast<std::uintptr_t>(rax2);
        // 0xbcae85f  shr ecx,4
        ecx2 >>= 4;
        // 0xbcae862  mov [rbp],cx
        *reinterpret_cast<std::uint16_t*>(rbp) = static_cast<std::uint16_t>(ecx2);
        // 0xbcae866  mov byte ptr [rbp+2],1
        rbp[2] = 1;
        // 0xbcae86a  mov rdx,rbp
        rdx = rbp;
        // 0xbcae86d  lea r8,[rbp+0x310]
        r8 = rbp + 0x310;
        // 0xbcae874  mov rcx,[rbp+0xF50]
        rcx2 = *reinterpret_cast<void**>(rbp + 0xF50);
        // 0xbcae87b  call 0x5679DB0
        sub_5679db0(rcx2, rdx, r8);
    }

L_BCAE880:
    // ---- 0xbcae880..0xbcae8fa : setup for ColorPostProcess builder ----
    // 0xbcae880  mov qword ptr [rbp+0xA22],0
    *reinterpret_cast<std::uint64_t*>(rbp + 0xA22) = 0;
    // 0xbcae88b  mov qword ptr [rbp+0xA28],0
    *reinterpret_cast<std::uint64_t*>(rbp + 0xA28) = 0;
    // 0xbcae896  mov rax,[rbp+0xF30]
    void* rax3 = *reinterpret_cast<void**>(rbp + 0xF30);
    // 0xbcae89d  mov rsi,[rax]
    rsi = *reinterpret_cast<std::uint8_t**>(rax3);
    // 0xbcae8a0  mov r12,[0x12AE2450]
    r12 = *reinterpret_cast<void**>(base + DATA_12AE2450);
    // 0xbcae8a7  mov rbx,[0x12AE2400]
    rbx = *reinterpret_cast<void**>(base + DATA_12AE2400);
    // 0xbcae8ae  movzx r15d,word ptr [0x128C1A58]
    std::uint16_t r15d = *reinterpret_cast<std::uint16_t*>(base + DATA_128C1A58);
    // 0xbcae8b6  mov r14,[r14+0x18]
    r14 = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(r14) + 0x18);
    // 0xbcae8ba  mov rax,[0x12AE2430]
    rax3 = *reinterpret_cast<void**>(base + DATA_12AE2430);
    // 0xbcae8c1  mov [rbp+0xA78],rax3
    *reinterpret_cast<void**>(rbp + 0xA78) = rax3;
    // 0xbcae8c8  mov rax,[rdi+0x18]
    rax3 = *reinterpret_cast<void**>(rdi + 0x18);
    // 0xbcae8cc  mov [rbp+0xF38],rax3
    *reinterpret_cast<void**>(rbp + 0xF38) = rax3;
    // 0xbcae8d3  mov rax,[0x12AE23F0]
    rax3 = *reinterpret_cast<void**>(base + DATA_12AE23F0);
    // 0xbcae8da  mov [rbp+0xF30],rax3
    *reinterpret_cast<void**>(rbp + 0xF30) = rax3;
    // 0xbcae8e1  mov qword ptr [rbp+0xF18],0
    *reinterpret_cast<std::uint64_t*>(rbp + 0xF18) = 0;
    // 0xbcae8ec  mov rcx,[0x1233E1A8]
    void* rcx3 = *reinterpret_cast<void**>(base + DATA_1233E1A8);
    // 0xbcae8f3  mov rax,[rcx]
    rax3 = *reinterpret_cast<void**>(rcx3);
    // 0xbcae8f6  mov rax,[rax+8]
    rax3 = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rax3) + 8);
    // 0xbcae8fa  mov edx,0x20
    // 0xbcae8ff  call qword ptr [0xF99FFA0]
    void* (*alloc_fn2)(void*) = *reinterpret_cast<void* (*)(void*)*>(base + F99FFA0);
    void* alloc_result2 = alloc_fn2(reinterpret_cast<void*>(0x20));
    // 0xbcae905  test rax,rax
    // 0xbcae908  je 0xBCAF63D
    if (alloc_result2 == nullptr) {
        s.branch = 0xBCAF63D;
        return;
    }

    // ---- 0xbcae90e..0xbcaebd9 : ColorPostProcess builder body ----
    // loc_bcae90e:
    // 0xbcae90e  mov [rbp+0xF10],rax
    *reinterpret_cast<void**>(rbp + 0xF10) = alloc_result2;
    // 0xbcae915  mov qword ptr [rbp+0xF20],0x15
    *reinterpret_cast<std::uint64_t*>(rbp + 0xF20) = 0x15;
    // 0xbcae920  mov qword ptr [rbp+0xF28],0x1F
    *reinterpret_cast<std::uint64_t*>(rbp + 0xF28) = 0x1F;
    // 0xbcae92b  movups xmm0,[0xF5C5E67]
    __m128 str1 = *reinterpret_cast<__m128*>(base + F5C5E67); // "ColorPostProcessPhase"
    // 0xbcae932  movups [rax],xmm0
    *reinterpret_cast<__m128*>(alloc_result2) = str1;
    // 0xbcae935  mov rcx,0x6573616850737365
    // 0xbcae93f  mov [rax+0xD],rcx
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint8_t*>(alloc_result2) + 0xD) = 0x6573616850737365ULL;
    // 0xbcae943  mov byte ptr [rax+0x15],0
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(alloc_result2) + 0x15) = 0;
    // 0xbcae947  lea rcx,[rbp+0x9E8]
    rcx3 = rbp + 0x9E8;
    // 0xbcae94e  xorps xmm6,xmm6
    __m128 xmm6_val = _mm_setzero_ps();
    // 0xbcae951  movaps [rbp+0x9F0],xmm6
    *reinterpret_cast<__m128*>(rbp + 0x9F0) = xmm6_val;
    // 0xbcae958  movaps [rbp+0x9E0],xmm6
    *reinterpret_cast<__m128*>(rbp + 0x9E0) = xmm6_val;
    // 0xbcae95f  mov qword ptr [rbp+0xA00],0xF
    *reinterpret_cast<std::uint64_t*>(rbp + 0xA00) = 0xF;
    // 0xbcae96a  mov qword ptr [rbp+0xA08],0
    *reinterpret_cast<std::uint64_t*>(rbp + 0xA08) = 0;
    // 0xbcae975  lea r9,[0xF547EEF]
    void* r9_val = reinterpret_cast<void*>(base + F547EEF); // "ColorPostProcess"
    // 0xbcae97c  mov edx,0x10
    std::uint32_t edx2 = 0x10;
    // 0xbcae981  call 0x9D6D0
    boundary::sub_9d6d0(rcx3, reinterpret_cast<void*>(edx2), r9_val);
    // 0xbcae986  nop
    // 0xbcae987  mov rax,0x16D95E79CDB26A8F
    std::uint64_t rax4 = 0x16D95E79CDB26A8FULL;
    // 0xbcae991  mov [rbp+0x9E0],rax
    *reinterpret_cast<std::uint64_t*>(rbp + 0x9E0) = rax4;
    // 0xbcae998  mov dword ptr [rbp+0x948],0x3F800000
    *reinterpret_cast<std::uint32_t*>(rbp + 0x948) = 0x3F800000; // 1.0f
    // 0xbcae9a2  movups [rbp+0x94C],xmm6
    *reinterpret_cast<__m128*>(rbp + 0x94C) = xmm6_val;
    // 0xbcae9a9  mov dword ptr [rbp+0x95C],0x3F800000
    *reinterpret_cast<std::uint32_t*>(rbp + 0x95C) = 0x3F800000;
    // 0xbcae9b3  movups [rbp+0x960],xmm6
    *reinterpret_cast<__m128*>(rbp + 0x960) = xmm6_val;
    // 0xbcae9ba  mov dword ptr [rbp+0x970],0x3F800000
    *reinterpret_cast<std::uint32_t*>(rbp + 0x970) = 0x3F800000;
    // 0xbcae9c4  movups [rbp+0x974],xmm6
    *reinterpret_cast<__m128*>(rbp + 0x974) = xmm6_val;
    // 0xbcae9cb  mov dword ptr [rbp+0x984],0x3F800000
    *reinterpret_cast<std::uint32_t*>(rbp + 0x984) = 0x3F800000;
    // 0xbcae9d5  mov byte ptr [rbp+0x988],0
    rbp[0x988] = 0;
    // 0xbcae9dc  mov byte ptr [rbp-8],0xFF
    rbp[-8] = 0xFF;
    // 0xbcae9e0  lea rdi,[rbp-0x48]
    std::uint8_t* rdi2 = rbp - 0x48;
    // 0xbcae9e4  lea rdx,[rbp+0x948]
    rdx = rbp + 0x948;
    // 0xbcae9eb  mov rcx,rdi
    rcx3 = rdi2;
    // 0xbcae9f3  nop
    // ---- continuation translated below ----

    // ---- remainder of chunk (0xbcae9f4..0xbcafd5f) in progress ----

    // ---- 0xbcae9f4..0xbcaeb1d : ColorPostProcess builder (second pass) ----
    // 0xbcae9fc  mov rcx,[rcx+8]
    // 0xbcaea00  mov [rbp+0xA68],rcx
    // 0xbcaea07  mov rax,[rax+8]
    // 0xbcaea0b  mov [rbp+0xA70],rax
    // 0xbcaea12  movss xmm0,[r15+0x28]
    // 0xbcaea18  call 0xEEC7FF0  (sub_eec7ff0)
    // 0xbcaea1d  movaps xmm6,xmm0
    // 0xbcaea20  movss xmm0,[r15+0x38]
    // 0xbcaea26  cvtss2sd xmm0,xmm0
    // 0xbcaea2a  call 0xEEC8420  (sub_eec8420)
    // 0xbcaea2f  cmp byte ptr [r15],0
    // 0xbcaea33  movss xmm1,[0xEEC9060]
    // 0xbcaea3b  movaps xmm7,xmm1
    // 0xbcaea3e  jne short 0xBCAEA43
    // 0xbcaea40  xorps xmm7,xmm7
    // loc_bcaea43:
    // 0xbcaea43  cvtsd2ss xmm8,xmm0
    // 0xbcaea48  mov r14,[rbp+0x1018]
    // ... (full translation of this section continues; see chunk1_tail.txt)
    // Key: this section builds ColorPostProcessPhase entries via sub_5679ec0 (0x5679EC0)
    // and sub_eec7ff0/sub_eec8420 conversions.




    // ---- 0xbcae9f4..0xbcaeb1d : ColorPostProcess builder (second pass) ----
    // 0xbcae9fc  mov rcx,[rcx+8]
    // 0xbcaea00  mov [rbp+0xA68],rcx
    // 0xbcaea07  mov rax,[rax+8]
    // 0xbcaea0b  mov [rbp+0xA70],rax
    // 0xbcaea12  movss xmm0,[r15+0x28]
    // 0xbcaea18  call 0xEEC7FF0  (sub_eec7ff0)
    // 0xbcaea1d  movaps xmm6,xmm0
    // 0xbcaea20  movss xmm0,[r15+0x38]
    // 0xbcaea26  cvtss2sd xmm0,xmm0
    // 0xbcaea2a  call 0xEEC8420  (sub_eec8420)
    // 0xbcaea2f  cmp byte ptr [r15],0
    // 0xbcaea33  movss xmm1,[0xEEC9060]
    // 0xbcaea3b  movaps xmm7,xmm1
    // 0xbcaea3e  jne short 0xBCAEA43
    // 0xbcaea40  xorps xmm7,xmm7
    // loc_bcaea43:
    // 0xbcaea43  cvtsd2ss xmm8,xmm0
    // 0xbcaea48  mov r14,[rbp+0x1018]
    // 0xbcaea4f  cmp byte ptr [r15+0x34],0
    // 0xbcaea54  jne short 0xBCAEA59
    // 0xbcaea56  xorps xmm1,xmm1
    // loc_bcaea59:
    // 0xbcaea59  xorps xmm0,xmm0
    // 0xbcaea5c  cvtsi2ss xmm0,dword ptr [r15+8]
    // 0xbcaea62  mulss xmm8,[0xF35FC60]
    // 0xbcaea6b  lea rax,[r14+8]
    // 0xbcaea6f  mov [rbp+0xF50],rax
    // 0xbcaea76  movss [rbp+0xA80],xmm0
    // 0xbcaea7e  movss [rbp+0xA84],xmm6
    // 0xbcaea86  movss [rbp+0xA88],xmm1
    // 0xbcaea8e  mov dword ptr [rbp+0xA8C],0
    // 0xbcaea98  mov qword ptr [rbp+0x310],1
    // 0xbcaeaa3  lea rdi,[rbp+0xA80]
    // 0xbcaeaaa  mov [rbp+0x318],rdi
    // 0xbcaeab1  mov rax,[r14+0x38]
    // 0xbcaeab5  movzx r8d,word ptr [r14+0x42]
    // 0xbcaeaba  mov edx,r8d
    // 0xbcaeabd  shl edx,4
    // 0xbcaeac0  mov rcx,rax
    // 0xbcaeac3  test r8d,r8d
    // 0xbcaeac6  je short 0xBCAEAF5
    // 0xbcaeac8  mov r8,[0x12AE34D0]
    // 0xbcaeacf  mov r9,rdx
    // 0xbcaead2  mov rcx,rax
    // (loop at 0xbcaeae0..0xbcaeaf1)
    // 0xbcaeaf5  add rdx,rax
    // 0xbcaeaf8  cmp rcx,rdx
    // 0xbcaeafb  jae short 0xBCAEB1D
    // 0xbcaeafd  sub ecx,eax
    // 0xbcaeaff  shr ecx,4
    // 0xbcaeb02  mov [rbp],cx
    // 0xbcaeb06  mov byte ptr [rbp+2],1
    // 0xbcaeb0a  mov rdx,rbp
    // 0xbcaeb0d  lea r8,[rbp+0x310]
    // 0xbcaeb14  lea rcx,[r14+8]
    // 0xbcaeb18  call 0x5679EC0  (sub_5679ec0)
    // loc_bcaeb1d:
    // (continues with more ColorPostProcess entries...)



    // ---- 0xbcaeb1d..0xbcaee63 : ColorPostProcess builder entries 2-6 ----
    // 0xbcaeb1d  movzx ebx,byte ptr [rbp+0x1030]
    uint8_t bl = rbp[0x1030];
    // 0xbcaeb24  movss xmm0,[r15+0x30]
    float xmm0_val = *reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(r15) + 0x30);
    // 0xbcaeb2a  movss xmm9,[r15+0x3C]
    s.xmm9_live = *reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(r15) + 0x3C);
    // 0xbcaeb30  cvtss2sd xmm0,xmm0
    // 0xbcaeb34  call 0xEEC8420  (sub_eec8420)
    // 0xbcaeb39  movaps xmm6,xmm0
    // 0xbcaeb3c  movss xmm0,[r15+0x2C]
    // 0xbcaeb42  cvtss2sd xmm0,xmm0
    // 0xbcaeb46  call 0xEEC8420  (sub_eec8420)
    // 0xbcaeb4b  movlhps xmm0,xmm6
    // 0xbcaeb4e  cvtpd2ps xmm0,xmm0
    // 0xbcaeb52  mulps xmm0,[0xF153810]
    // 0xbcaeb59  movlps [rbp+0xA80],xmm0
    // 0xbcaeb60  movss [rbp+0xA88],xmm8
    // 0xbcaeb69  movss [rbp+0xA8C],xmm9
    // 0xbcaeb72  mov qword ptr [rbp+0x310],1
    // 0xbcaeb7d  mov [rbp+0x318],rdi
    // 0xbcaeb84  mov rsi,[r14+0x38]
    std::uint8_t* rsi2 = *reinterpret_cast<std::uint8_t**>(reinterpret_cast<std::uint8_t*>(r14) + 0x38);
    // 0xbcaeb88  movzx ecx,word ptr [r14+0x42]
    uint16_t ecx = *reinterpret_cast<uint16_t*>(reinterpret_cast<std::uint8_t*>(r14) + 0x42);
    // 0xbcaeb8d  mov eax,ecx
    uint32_t eax = ecx;
    // 0xbcaeb8f  shl eax,4
    eax <<= 4;
    // 0xbcaeb92  mov rdx,rsi2
    rdx = rsi2;
    // 0xbcaeb95  test ecx,ecx
    // 0xbcaeb97  je short 0xBCAEBC8
    if (ecx == 0) {
        s.branch = 0xBCAEBC8;
    } else {
        // 0xbcaeb99  mov r8,[0x12AE34E0]
        void* r8_ptr = *reinterpret_cast<void**>(base + 0x12AE34E0);
        // 0xbcaeba0  xor edx,edx
        // (loop at 0xbcaebb0..0xbcaebc1)
        // 0xbcaebc5  add rdx,rsi2
        // loc_bcaebc8:
        // 0xbcaebc8  lea r8,[rsi2+rax]
        // 0xbcaebcc  cmp rdx,r8
        // 0xbcaebcf  jae short 0xBCAEBFF
        // 0xbcaebd1  sub edx,esi
        // 0xbcaebd3  shr edx,4
        // 0xbcaebd6  mov [rbp],dx
        // 0xbcaebda  mov byte ptr [rbp+2],1
        // 0xbcaebde  mov rdx,rbp
        // 0xbcaebe1  lea r8,[rbp+0x310]
        // 0xbcaebe8  lea rcx,[r14+8]
        // 0xbcaebec  call 0x5679EC0  (sub_5679ec0)
        // loc_bcaebff:
        // 0xbcaebff  test bl,bl
        // 0xbcaec01  jne short 0xBCAEC08
        // 0xbcaec03  xorps xmm0,xmm0
        // 0xbcaec06  jmp short 0xBCAEC10
        // loc_bcaec08:
        // 0xbcaec08  movss xmm0,[0xEEC9060]
        // loc_bcaec10:
        // 0xbcaec10  movzx ebx,byte ptr [rbp+0x1060]
        bl = rbp[0x1060];
        // 0xbcaec17  xorps xmm1,xmm1
        // 0xbcaec1a  cvtsi2ss xmm1,dword ptr [r15+4]
        // 0xbcaec20  movss [rbp+0xA80],xmm1
        // 0xbcaec28  movss [rbp+0xA84],xmm7
        // 0xbcaec30  movss [rbp+0xA88],xmm0
        // 0xbcaec38  mov dword ptr [rbp+0xA8C],0
        // 0xbcaec42  mov qword ptr [rbp+0x310],1
        // 0xbcaec4d  mov [rbp+0x318],rdi
        // 0xbcaec54  mov rdx,rsi2
        // 0xbcaec57  test cx,cx
        // 0xbcaec5a  je short 0xBCAEC8C
        if (ecx == 0) {
            s.branch = 0xBCAEC8C;
        } else {
            // 0xbcaec5c  mov r8,[0x12AE3520]
            void* r8_ptr2 = *reinterpret_cast<void**>(base + 0x12AE3520);
            // 0xbcaec63  xor edx,edx
            // (loop at 0xbcaec70..0xbcaec81)
            // 0xbcaec89  add rdx,rsi2
            // loc_bcaec8c:
            // 0xbcaec8c  lea r8,[rsi2+rax]
            // 0xbcaec90  cmp rdx,r8
            // 0xbcaec93  jae short 0xBCAECC3
            // 0xbcaec95  sub edx,esi
            // 0xbcaec97  shr edx,4
            // 0xbcaec9a  mov [rbp],dx
            // 0xbcaec9e  mov byte ptr [rbp+2],1
            // 0xbcaeca2  mov rdx,rbp
            // 0xbcaeca5  lea r8,[rbp+0x310]
            // 0xbcaecac  lea rcx,[r14+8]
            // 0xbcaecb0  call 0x5679EC0  (sub_5679ec0)
            // loc_bcaecc3:
            // 0xbcaecc3  test bl,bl
            // 0xbcaecc5  jne short 0xBCAECCC
            // 0xbcaecc7  xorps xmm0,xmm0
            // 0xbcaecca  jmp short 0xBCAECD4
            // loc_bcaeccc:
            // 0xbcaeccc  movss xmm0,[0xEEC9060]
            // loc_bcaecd4:
            // 0xbcaecd4  shufps xmm0,xmm0,0
            // 0xbcaecd8  movaps [rbp+0xA80],xmm0
            // 0xbcaecdf  mov qword ptr [rbp+0x310],1
            // 0xbcaecea  mov [rbp+0x318],rdi
            // 0xbcaecf1  mov rdx,rsi2
            // 0xbcaecf4  test cx,cx
            // 0xbcaecf7  je short 0xBCAED28
            if (ecx == 0) {
                s.branch = 0xBCAED28;
            } else {
                // 0xbcaecf9  mov rcx,[0x12AE3530]
                // (loop at 0xbcaed10..0xbcaed21)
                // 0xbcaed25  add rdx,rsi2
                // loc_bcaed28:
                // 0xbcaed28  add rax,rsi2
                // 0xbcaed2b  cmp rdx,rax
                // 0xbcaed2e  jae short 0xBCAED54
                // 0xbcaed30  sub edx,esi
                // 0xbcaed32  shr edx,4
                // 0xbcaed35  mov [rbp],dx
                // 0xbcaed39  mov byte ptr [rbp+2],1
                // 0xbcaed3d  mov rdx,rbp
                // 0xbcaed40  lea r8,[rbp+0x310]
                // 0xbcaed47  lea rcx,[r14+8]
                // 0xbcaed4b  call 0x5679EC0  (sub_5679ec0)
                // loc_bcaed54:
                // 0xbcaed54  movss xmm1,[r15+0x40]
                // 0xbcaed5a  movss xmm0,[r15+0x44]
                // 0xbcaed60  mov rdi,[0xF9A9F98]
                // 0xbcaed67  call rdi  (indirect call via thunk)
                // 0xbcaed69  movaps xmm6,xmm0
                // 0xbcaed6c  movss xmm1,[r15+0x40]
                // 0xbcaed72  movss xmm0,[r15+0x4C]
                // 0xbcaed78  call rdi
                // 0xbcaed7a  movss xmm1,[r15+0x40]
                // 0xbcaed80  movss xmm2,[r15+0x48]
                // 0xbcaed86  movaps xmm3,xmm0
                // 0xbcaed89  mulss xmm3,xmm2
                // 0xbcaed8d  movaps xmm4,xmm6
                // 0xbcaed90  subss xmm4,xmm3
                // 0xbcaed94  mulss xmm6,xmm2
                // 0xbcaed98  subss xmm6,xmm3
                // 0xbcaed9c  divss xmm4,xmm6
                // 0xbcaeda0  movaps xmm2,xmm0
                // 0xbcaeda3  mulss xmm2,xmm4
                // 0xbcaedab  subss xmm0,xmm2
                // 0xbcaedb1  movss [rbp+0xA80],xmm1
                // 0xbcaedb9  movss [rbp+0xA84],xmm4
                // 0xbcaedc1  movss [rbp+0xA88],xmm0
                // 0xbcaedc9  movss [rbp+0xA8C],xmm2
                // 0xbcaedd1  mov qword ptr [rbp+0x310],1
                // 0xbcaeddc  lea rdi,[rbp+0xA80]
                // 0xbcaede3  mov [rbp+0x318],rdi
                // 0xbcaedea  movzx ecx,word ptr [r14+0x42]
                ecx = *reinterpret_cast<uint16_t*>(reinterpret_cast<std::uint8_t*>(r14) + 0x42);
                // 0xbcaedef  mov eax,ecx
                eax = ecx;
                // 0xbcaedf1  shl eax,4
                eax <<= 4;
                // 0xbcaedf4  mov rdx,rsi2
                rdx = rsi2;
                // 0xbcaedf7  test ecx,ecx
                // 0xbcaedf9  je short 0xBCAEE2C
                if (ecx == 0) {
                    s.branch = 0xBCAEE2C;
                } else {
                    // 0xbcaedfb  mov r8,[0x12AE3550]
                    void* r8_ptr3 = *reinterpret_cast<void**>(base + 0x12AE3550);
                    // 0xbcaee02  xor edx,edx
                    // (loop at 0xbcaee10..0xbcaee21)
                    // 0xbcaee29  add rdx,rsi2
                    // loc_bcaee2c:
                    // 0xbcaee2c  lea r8,[rsi2+rax]
                    // 0xbcaee30  cmp rdx,r8
                    // 0xbcaee33  jae short 0xBCAEE63
                    // 0xbcaee35  sub edx,esi
                    // 0xbcaee37  shr edx,4
                    // 0xbcaee3a  mov [rbp],dx
                    // 0xbcaee3e  mov byte ptr [rbp+2],1
                    // 0xbcaee42  mov rdx,rbp
                    // 0xbcaee45  lea r8,[rbp+0x310]
                    // 0xbcaee4c  lea rcx,[r14+8]
                    // 0xbcaee50  call 0x5679EC0  (sub_5679ec0)
    // ---- 0xbcaeb1d..0xbcaee63 : ColorPostProcess builder entries 2-6 ----
    // 0xbcaeb1d  movzx ebx,byte ptr [rbp+0x1030]
    uint8_t bl = rbp[0x1030];
    // 0xbcaeb24  movss xmm0,[r15+0x30]
    float xmm0_val = *reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(r15) + 0x30);
    // 0xbcaeb2a  movss xmm9,[r15+0x3C]
    s.xmm9_live = *reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(r15) + 0x3C);
    // ... (translation continues in comments; full translation below)
    // NOTE: remainder still needs full instruction-by-instruction translation.
    // Progress marker only; function not yet complete.
    s.branch = 0;
}

} // namespace

