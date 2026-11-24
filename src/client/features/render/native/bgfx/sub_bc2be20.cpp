// LIFT 0xbc2be20 size 0x1ec 1.26.62.01 sub_bc2be20
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc2be20.h"

#include <cstdint>
#include <emmintrin.h>
#include <intrin.h>

namespace {
using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;

static inline u64 rd64(const u8* b, size_t o) { return *reinterpret_cast<const u64*>(b + o); }
static inline void wr64(u8* b, size_t o, u64 v) { *reinterpret_cast<u64*>(b + o) = v; }
static inline u32 rd32(const u8* b, size_t o) { return *reinterpret_cast<const u32*>(b + o); }
static inline void wr32(u8* b, size_t o, u32 v) { *reinterpret_cast<u32*>(b + o) = v; }
static inline u8 rd8(const u8* b, size_t o) { return b[o]; }
static inline void wr8(u8* b, size_t o, u8 v) { b[o] = v; }
static inline __m128i rd128(const u8* b, size_t o) { return _mm_loadu_si128(reinterpret_cast<const __m128i*>(b + o)); }
static inline void wr128(u8* b, size_t o, __m128i v) { _mm_storeu_si128(reinterpret_cast<__m128i*>(b + o), v); }
} // namespace

// Callee forward declarations: both targets are class `lift` in docs/data/native_boundary.tsv
// (not boundary), so they are called through their native symbols and linked at the milestone
// gate. The call instructions are quoted verbatim beside each call site below.
namespace native {
void sub_5669770(void* dst, const void* src);
void sub_e869ff0(void* dst, const void* src);
}

namespace native::bgfx {

// Layout assertions (definitions and the full set of offset static_asserts live in
// sub_bc2be20.h; repeated here so the source file is self-contained for liftcheck).
static_assert(offsetof(sub_bc2be20_state, field_0x00)  == 0x00,  "sub_0xbc2be20 touches self+0x00");
static_assert(offsetof(sub_bc2be20_state, field_0x08)  == 0x08,  "sub_0xbc2be20 touches self+0x08");
static_assert(offsetof(sub_bc2be20_state, field_0x10)  == 0x10,  "sub_0xbc2be20 touches self+0x10");
static_assert(offsetof(sub_bc2be20_state, field_0x18)  == 0x18,  "sub_0xbc2be20 touches self+0x18");
static_assert(offsetof(sub_bc2be20_state, field_0x28)  == 0x28,  "sub_0xbc2be20 touches self+0x28");
static_assert(offsetof(sub_bc2be20_state, field_0x30)  == 0x30,  "sub_0xbc2be20 touches self+0x30");
static_assert(offsetof(sub_bc2be20_state, field_0x38)  == 0x38,  "sub_0xbc2be20 touches self+0x38");
static_assert(offsetof(sub_bc2be20_state, field_0x40)  == 0x40,  "sub_0xbc2be20 touches self+0x40");
static_assert(offsetof(sub_bc2be20_state, field_0x48)  == 0x48,  "sub_0xbc2be20 touches self+0x48");
static_assert(offsetof(sub_bc2be20_state, field_0x58)  == 0x58,  "sub_0xbc2be20 touches self+0x58");
static_assert(offsetof(sub_bc2be20_state, field_0x60)  == 0x60,  "sub_0xbc2be20 touches self+0x60");
static_assert(offsetof(sub_bc2be20_state, field_0x68)  == 0x68,  "sub_0xbc2be20 touches self+0x68");
static_assert(offsetof(sub_bc2be20_state, field_0x70)  == 0x70,  "sub_0xbc2be20 touches self+0x70");
static_assert(offsetof(sub_bc2be20_state, field_0x78)  == 0x78,  "sub_0xbc2be20 touches self+0x78");
static_assert(offsetof(sub_bc2be20_state, field_0x88)  == 0x88,  "sub_0xbc2be20 touches self+0x88");
static_assert(offsetof(sub_bc2be20_state, field_0x90)  == 0x90,  "sub_0xbc2be20 touches self+0x90");
static_assert(offsetof(sub_bc2be20_state, field_0x98)  == 0x98,  "sub_0xbc2be20 passes &self+0x98 to sub_e869ff0");
static_assert(offsetof(sub_bc2be20_state, field_0x110) == 0x110, "sub_0xbc2be20 touches self+0x110");
static_assert(offsetof(sub_bc2be20_state, field_0x118) == 0x118, "sub_0xbc2be20 passes &self+0x118 to sub_5669770");
static_assert(offsetof(sub_bc2be20_state, field_0x23C) == 0x23C, "sub_0xbc2be20 touches self+0x23C");
static_assert(offsetof(sub_bc2be20_state, field_0x24C) == 0x24C, "sub_0xbc2be20 touches self+0x24C");
static_assert(offsetof(sub_bc2be20_state, field_0x250) == 0x250, "sub_0xbc2be20 touches self+0x250");
static_assert(offsetof(sub_bc2be20_state, field_0x254) == 0x254, "sub_0xbc2be20 touches self+0x254");
static_assert(offsetof(sub_bc2be20_state, field_0x258) == 0x258, "sub_0xbc2be20 touches self+0x258");
static_assert(offsetof(sub_bc2be20_state, field_0x25C) == 0x25C, "sub_0xbc2be20 touches self+0x25C");
static_assert(offsetof(sub_bc2be20_state, field_0x260) == 0x260, "sub_0xbc2be20 touches self+0x260");
static_assert(offsetof(sub_bc2be20_state, field_0x264) == 0x264, "sub_0xbc2be20 touches self+0x264");
static_assert(offsetof(sub_bc2be20_state, field_0x274) == 0x274, "sub_0xbc2be20 touches self+0x274");
static_assert(offsetof(sub_bc2be20_state, field_0x283) == 0x283, "sub_0xbc2be20 touches self+0x283");
static_assert(offsetof(sub_bc2be20_state, field_0x294) == 0x294, "sub_0xbc2be20 touches self+0x294");
static_assert(sizeof(sub_bc2be20_state) == 0x2A0, "sub_0xbc2be20 object size");

// sub_0xbc2be20(sub_bc2be20_state* dst = rcx, sub_bc2be20_state* src = rdx) -> sub_bc2be20_state* (rax = dst).
// Minecraft Windows 1.26.62.01, function [0xbc2be20, 0xbc2c00c), size 0x1ec.
// The source is also mutated: +0x8, +0x40, +0x48 are zeroed and +0x110 is moved to dst then cleared.
sub_bc2be20_state* sub_bc2be20(sub_bc2be20_state* dst, sub_bc2be20_state* src) {
    u8* d = reinterpret_cast<u8*>(dst);
    u8* s = reinterpret_cast<u8*>(src);

    // 0xbc2be20..0xbc2be3c: prologue (push rbp/rsi, sub rsp,0x38, frame setup, args saved in rsi/r10);
    // field_0x00 copy src->dst.                                    // 0xbc2be39  mov rax,[rdx]; 0xbc2be3c  mov [rcx],rax
    wr64(d, kOff0x00, rd64(s, kOff0x00));

    // 0xbc2be3f..0xbc2be52: xmm0 = 0; dst+0x8 zeroed then overwritten from src+0x8; dst+0x10 copy.
    // 0xbc2be3f  xorps xmm0,xmm0; 0xbc2be42  movups [rcx+8],xmm0
    wr128(d, kOff0x08, _mm_setzero_si128());
    // 0xbc2be46  mov rax,[rdx+8]; 0xbc2be4a  mov [rcx+8],rax
    wr64(d, kOff0x08, rd64(s, kOff0x08));
    // 0xbc2be4e  mov rax,[rdx+0x10]; 0xbc2be52  mov [rcx+0x10],rax
    wr64(d, kOff0x10, rd64(s, kOff0x10));

    // 0xbc2be56..0xbc2be5e: src+0x8 zeroed, dst+0x18 zeroed, dst+0x28 = 0.
    // 0xbc2be56  movups [rdx+8],xmm0; 0xbc2be5a  movups [rcx+0x18],xmm0; 0xbc2be5e  mov qword ptr [rcx+0x28],0
    wr128(s, kOff0x08, _mm_setzero_si128());
    wr128(d, kOff0x18, _mm_setzero_si128());
    wr64(d, kOff0x28, 0);

    // 0xbc2be66..0xbc2be6a: byte field_0x30 copy src->dst.
    // 0xbc2be66  movzx eax,byte ptr [rdx+0x30]; 0xbc2be6a  mov [rcx+0x30],al
    wr8(d, kOff0x30, rd8(s, kOff0x30));

    // 0xbc2be6d..0xbc2be8d: field_0x38 and field_0x48 copied src->dst; src+0x40 and src+0x48 zeroed;
    // field_0x58 copied src->dst.
    // 0xbc2be6d  movups xmm1,[rdx+0x38]; 0xbc2be71  movups xmm2,[rdx+0x48]; 0xbc2be81  movups [rcx+0x38],xmm1; 0xbc2be85  movups [rcx+0x48],xmm2
    wr128(d, kOff0x38, rd128(s, kOff0x38));
    // 0xbc2be75  mov qword ptr [rdx+0x40],0
    wr64(s, kOff0x40, 0);
    // 0xbc2be7d  movups [rdx+0x48],xmm0
    wr128(s, kOff0x48, _mm_setzero_si128());
    // 0xbc2be89  mov rax,[rdx+0x58]; 0xbc2be8d  mov [rcx+0x58],rax
    wr64(d, kOff0x58, rd64(s, kOff0x58));

    // 0xbc2be91..0xbc2bea7: dst field_0x70 = 0xFF; tag = src field_0x70; switch through the
    // jump table at 0xF440D90 (entries [V] reconstructed from the disassembly of that region:
    // tag 0 -> 0xbc2bee8, tag 1 -> 0xbc2beb8, tag 2 -> 0xbc2bec0, tag 3 -> 0xbc2bec8;
    // tag > 3 falls through to 0xbc2beec).
    // 0xbc2be91  mov byte ptr [rcx+0x70],0xFF; 0xbc2be95  movzx eax,byte ptr [rdx+0x70];
    // 0xbc2be99  cmp rax,3; 0xbc2be9d  ja short 0xBC2BEEC; 0xbc2be9f  lea rcx,[r10+0x60];
    // 0xbc2bea3  lea rdx,[rsi+0x60]; 0xbc2bea7  lea r8,[0xF440D90]
    wr8(d, kOff0x70, 0xFF);
    u8 tag = rd8(s, kOff0x70);
    // 0xbc2beae..0xbc2beb5   switch index + indirect jump through the table at 0xF440D90
    // 0xbc2beae  movsxd r9,[r8+rax*4]; 0xbc2beb2  add r9,r8; 0xbc2beb5  jmp r9
    if (tag <= 3) {
        switch (tag) {
        case 0:                                              // 0xbc2bee8  mov [r10+0x70],al (nothing else written for tag 0)
            break;
        case 1:                                              // 0xbc2beb8  mov rdx,[rdx]; 0xbc2bebb  mov [rcx],rdx; 0xbc2bebe  jmp short 0xBC2BEE8
            wr64(d, kOff0x60, rd64(s, rd64(s, kOff0x60)));   // *(dst+0x60) = *(*(u64*)(src+0x60))
            break;
        case 2:                                              // 0xbc2bec0  movups xmm0,[rdx]; 0xbc2bec3  movups [rcx],xmm0; 0xbc2bec6  jmp short 0xBC2BEE8
            wr128(d, kOff0x60, rd128(s, kOff0x60));
            break;
        case 3:                                              // 0xbc2bec8..0xbc2bee4
            wr128(d, kOff0x60, _mm_setzero_si128());         // 0xbc2bec8  movups [rcx],xmm0
            {
                u64 p = rd64(s, kOff0x68);                   // 0xbc2becb  mov rcx,[rsi+0x68]
                if (p != 0) {                                // 0xbc2becf  test rcx,rcx; 0xbc2bed2  je short 0xBC2BED8
                    _InterlockedIncrement(reinterpret_cast<volatile LONG*>(reinterpret_cast<u8*>(p) + 8));  // 0xbc2bed4  lock inc dword ptr [rcx+8]
                }
            }
            // 0xbc2bed8  mov rcx,[rsi+0x60]; 0xbc2bedc  mov [r10+0x60],rcx
            wr64(d, kOff0x60, rd64(s, kOff0x60));
            // 0xbc2bee0  mov rcx,[rsi+0x68]; 0xbc2bee4  mov [r10+0x68],rcx
            wr64(d, kOff0x68, rd64(s, kOff0x68));
            break;
        }
        // 0xbc2bee8  mov [r10+0x70],al
        wr8(d, kOff0x70, tag);
    }
    // tag > 3 (0xbc2beec): dst field_0x70 keeps 0xFF, nothing else from the switch.

    // 0xbc2beec..0xbc2bf30: field_0x88, field_0x78, field_0x90 copied src->dst; stack spills
    // &dst+0x38 and dst; sub-object copy at +0x98.
    // 0xbc2beec  lea rax,[r10+0x38]; 0xbc2bef0  mov [rbp-0x10],rax (dead spill of &dst+0x38)
    // 0xbc2bef4  mov rax,[rsi+0x88]; 0xbc2befb  mov [r10+0x88],rax
    wr64(d, kOff0x88, rd64(s, kOff0x88));
    // 0xbc2bf02  movups xmm0,[rsi+0x78]; 0xbc2bf06  movups [r10+0x78],xmm0
    wr128(d, kOff0x78, rd128(s, kOff0x78));
    // 0xbc2bf0b  mov rax,[rsi+0x90]; 0xbc2bf12  mov [r10+0x90],rax
    wr64(d, kOff0x90, rd64(s, kOff0x90));
    // 0xbc2bf19  lea rcx,[r10+0x98]; 0xbc2bf20  lea rdx,[rsi+0x98]
    // 0xbc2bf2b  call 0xE869FF0
    native::sub_e869ff0(d + kOff0x98, s + kOff0x98);

    // 0xbc2bf30  nop
    // 0xbc2bf31  mov rax,[rsi+0x110]; 0xbc2bf38  mov rcx,[rbp-8] (dst reload); 0xbc2bf3c  mov [rcx+0x110],rax
    wr64(d, kOff0x110, rd64(s, kOff0x110));
    // 0xbc2bf43  mov qword ptr [rsi+0x110],0
    wr64(s, kOff0x110, 0);

    // 0xbc2bf4e  add rcx,0x118; 0xbc2bf55  lea rdx,[rsi+0x118]
    // 0xbc2bf5c  call 0x5669770
    // 0xbc2bf61  nop
    native::sub_5669770(d + kOff0x118, s + kOff0x118);

    // 0xbc2bf62..0xbc2bffe: tail field block (field_0x24C dword, field_0x23C 16 bytes,
    // field_0x250 byte, field_0x254/0x258/0x25C/0x260 floats, field_0x264/0x274/0x283 16 bytes
    // each, field_0x294 qword).
    // 0xbc2bf62  mov ecx,[rsi+0x24C]; 0xbc2bf68  mov rax,[rbp-8]; 0xbc2bf6c  mov [rax+0x24C],ecx
    wr32(d, kOff0x24C, rd32(s, kOff0x24C));
    // 0xbc2bf72  movups xmm0,[rsi+0x23C]; 0xbc2bf79  movups [rax+0x23C],xmm0
    wr128(d, kOff0x23C, rd128(s, kOff0x23C));
    // 0xbc2bf80  movzx ecx,byte ptr [rsi+0x250]; 0xbc2bf87  mov [rax+0x250],cl
    wr8(d, kOff0x250, rd8(s, kOff0x250));
    // 0xbc2bf8d  movss xmm0,[rsi+0x254]; ... 0xbc2bfc5  movss [rax+0x260],xmm0
    wr32(d, kOff0x254, rd32(s, kOff0x254));
    wr32(d, kOff0x258, rd32(s, kOff0x258));
    wr32(d, kOff0x25C, rd32(s, kOff0x25C));
    wr32(d, kOff0x260, rd32(s, kOff0x260));
    // 0xbc2bfcd  movups xmm0,[rsi+0x264]; 0xbc2bfd4  movups xmm1,[rsi+0x274]; 0xbc2bfdb  movups xmm2,[rsi+0x283];
    // 0xbc2bfe2  movups [rax+0x264],xmm0; 0xbc2bfe9  movups [rax+0x274],xmm1; 0xbc2bff0  movups [rax+0x283],xmm2
    wr128(d, kOff0x264, rd128(s, kOff0x264));
    wr128(d, kOff0x274, rd128(s, kOff0x274));
    wr128(d, kOff0x283, rd128(s, kOff0x283));
    // 0xbc2bff7  mov rcx,[rsi+0x294]; 0xbc2bffe  mov [rax+0x294],rcx
    wr64(d, kOff0x294, rd64(s, kOff0x294));

    // 0xbc2c005  add rsp,0x38; 0xbc2c009  pop rsi; 0xbc2c00a  pop rbp; 0xbc2c00b  ret  (rax = dst)
    return dst;
}

LIFT_FN(sub_bc2be20, "sub_bc2be20", 0xbc2be20, sub_bc2be20, nullptr);

} // namespace native::bgfx
