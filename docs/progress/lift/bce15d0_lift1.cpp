// LIFT 0xbce15d0 size 0x91 1.26.62.01 lift1
#include <cstdint>
#include <cstring>
#include <intrin.h>
#include <immintrin.h>

static uint8_t mem[1<<24]; // 16MB
static inline uint8_t  R8(uint64_t a)  { return mem[a & 0xFFFFFF]; }
static inline void     W8(uint64_t a, uint8_t  v) { mem[a & 0xFFFFFF] = v; }
static inline uint16_t R16(uint64_t a) { uint16_t v; std::memcpy(&v, &mem[a & 0xFFFFFF], 2); return v; }
static inline void     W16(uint64_t a, uint16_t v) { std::memcpy(&mem[a & 0xFFFFFF], &v, 2); }
static inline uint32_t R32(uint64_t a) { uint32_t v; std::memcpy(&v, &mem[a & 0xFFFFFF], 4); return v; }
static inline void     W32(uint64_t a, uint32_t v) { std::memcpy(&mem[a & 0xFFFFFF], &v, 4); }
static inline uint64_t R64(uint64_t a) { uint64_t v; std::memcpy(&v, &mem[a & 0xFFFFFF], 8); return v; }
static inline void     W64(uint64_t a, uint64_t v) { std::memcpy(&mem[a & 0xFFFFFF], &v, 8); }
static inline __m128i  RXmm(uint64_t a) { __m128i v; std::memcpy(&v, &mem[a & 0xFFFFFF], 16); return v; }
static inline void     WXmm(uint64_t a, __m128i v) { std::memcpy(&mem[a & 0xFFFFFF], &v, 16); }
static inline int parity(uint64_t v) { v ^= v >> 32; v ^= v >> 16; v ^= v >> 8; v ^= v >> 4; v &= 0xF; return (0x6996 >> v) & 1; }

extern "C" uint64_t lift1_bce15d0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    uint64_t rax = a0, rcx = a1, rdx = a2, rbx = 0, rsp = 0, rbp = 0, rsi = 0, rdi = 0;
    uint64_t r8 = a3, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0, rip = 0;
    uint8_t cf = 0, pf = 0, af = 0, zf = 0, sf = 0, of = 0;

#if 0
// Verbatim instructions of the function:
0xbce15d0  sub rsp,0x28
0xbce15d4  mov rax,[rdx]
0xbce15d7  test rax,rax
0xbce15da  je short 0xBCE1640
0xbce15dc  mov rax,[rax+0x18]
0xbce15e0  test rax,rax
0xbce15e3  je short 0xBCE1640
0xbce15e5  mov rcx,[r8]
0xbce15e8  test rcx,rcx
0xbce15eb  je short 0xBCE1640
0xbce15ed  mov rcx,[rcx+0x18]
0xbce15f1  test rcx,rcx
0xbce15f4  je short 0xBCE1640
0xbce15f6  movsx rdx,byte ptr [rax+2]
0xbce15fb  movsx r8,byte ptr [rcx+2]
0xbce1600  lea rdx,[rdx+rdx*2]
0xbce1604  add rdx,r8
0xbce1607  add rdx,4
0xbce160b  lea r8,[0xF44C2F0]
0xbce1612  movsxd rdx,[r8+rdx*4]
0xbce1616  add rdx,r8
0xbce1619  jmp rdx
0xbce161b  movzx ecx,word ptr [rcx]
0xbce161e  movzx eax,word ptr [rax]
0xbce1621  cmp ax,cx
0xbce1624  sete dl
0xbce1627  cmp ax,0xFFFF
0xbce162b  setne r8b
0xbce162f  cmp cx,0xFFFF
0xbce1633  setne al
0xbce1636  and al,r8b
0xbce1639  and al,dl
0xbce163b  add rsp,0x28
0xbce163f  ret
0xbce1640  xor eax,eax
0xbce1642  add rsp,0x28
0xbce1646  ret
0xbce1647  call 0xB432E0
0xbce164c  call 0xB432E0
0xbce1651  call 0xB432E0
0xbce1656  call 0xB432E0
0xbce165b  call 0xB432E0
0xbce1660  int3
#endif

    // 0xbce15d4  mov rax,[rdx]
    rax = R64(rdx);
    // 0xbce15d7  test rax,rax
    // FLAGS: Test rax rax (size=8)
    pf = parity(zf); af = 0; // approximate
    // 0xbce15da  je short 0xBCE1640
    if (zf) goto loc_bce1640;
    // 0xbce15dc  mov rax,[rax+0x18]
    rax = R64(rax + 24);
    // 0xbce15e0  test rax,rax
    // FLAGS: Test rax rax (size=8)
    pf = parity(zf); af = 0; // approximate
    // 0xbce15e3  je short 0xBCE1640
    if (zf) goto loc_bce1640;
    // 0xbce15e5  mov rcx,[r8]
    rcx = R64(r8);
    // 0xbce15e8  test rcx,rcx
    // FLAGS: Test rcx rcx (size=8)
    pf = parity(zf); af = 0; // approximate
    // 0xbce15eb  je short 0xBCE1640
    if (zf) goto loc_bce1640;
    // 0xbce15ed  mov rcx,[rcx+0x18]
    rcx = R64(rcx + 24);
    // 0xbce15f1  test rcx,rcx
    // FLAGS: Test rcx rcx (size=8)
    pf = parity(zf); af = 0; // approximate
    // 0xbce15f4  je short 0xBCE1640
    if (zf) goto loc_bce1640;
    // 0xbce15f6  movsx rdx,byte ptr [rax+2]
    rdx = (int64_t)(int8_t)(R64(rax + 2));
    // 0xbce15fb  movsx r8,byte ptr [rcx+2]
    r8 = (int64_t)(int8_t)(R64(rcx + 2));
    // 0xbce1600  lea rdx,[rdx+rdx*2]
    rdx = rdx + (rdx * 2);
    // 0xbce1604  add rdx,r8
    // FLAGS: rdx + r8 (size=8)
    rdx = (rdx + r8);
    // 0xbce1607  add rdx,4
    // FLAGS: rdx + 4 (size=8)
    rdx = (rdx + 4);
    // 0xbce160b  lea r8,[0xF44C2F0]
    r8 = rip + 256164592;
    // 0xbce1612  movsxd rdx,[r8+rdx*4]
    rdx = (int64_t)(int32_t)(R64(r8 + (rdx * 4)));
    // 0xbce1616  add rdx,r8
    // FLAGS: rdx + r8 (size=8)
    rdx = (rdx + r8);
    // 0xbce1619  jmp rdx
    // DECISION: indirect jmp
    // 0xbce161b  movzx ecx,word ptr [rcx]
    rcx = (uint64_t)(uint32_t)((uint64_t)(R16(rcx)));
    // 0xbce161e  movzx eax,word ptr [rax]
    rax = (uint64_t)(uint32_t)((uint64_t)(R16(rax)));
    // 0xbce1621  cmp ax,cx
    // FLAGS: Cmp (uint16_t)rax (uint16_t)rcx (size=2)
    pf = parity(zf); af = 0; // approximate
    // 0xbce1624  sete dl
    // UNMODELED: 0xbce1624 Sete
    // 0xbce1627  cmp ax,0xFFFF
    // CMP/TEST unhandled
    // 0xbce162b  setne r8b
    // UNMODELED: 0xbce162b Setne
    // 0xbce162f  cmp cx,0xFFFF
    // CMP/TEST unhandled
    // 0xbce1633  setne al
    // UNMODELED: 0xbce1633 Setne
    // 0xbce1636  and al,r8b
    // FLAGS: rax & (uint8_t)r8 (size=1)
    rax = (uint64_t)(uint8_t)((rax & (uint8_t)r8));
    // 0xbce1639  and al,dl
    // FLAGS: rax & (uint8_t)rdx (size=1)
    rax = (uint64_t)(uint8_t)((rax & (uint8_t)rdx));
    // 0xbce163f  ret
    return rax;
    // 0xbce1646  ret
    return rax;
    // 0xbce1647  call 0xB432E0
    rax = sub_b432e0(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    // 0xbce164c  call 0xB432E0
    rax = sub_b432e0(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    // 0xbce1651  call 0xB432E0
    rax = sub_b432e0(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    // 0xbce1656  call 0xB432E0
    rax = sub_b432e0(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    // 0xbce165b  call 0xB432E0
    rax = sub_b432e0(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    // 0xbce1660  int3
    __debugbreak();
    return rax;
}

// DECISIONS
// - Dead instructions (unreachable blocks, folded sub/add rsp, dead flag writes) omitted.
// - Stack frame base unknown.
// - Memory model wraps at 16MB.
