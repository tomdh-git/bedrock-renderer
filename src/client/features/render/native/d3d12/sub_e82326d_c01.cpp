// LIFT 0xe82326d size 0xa276 1.26.62.01 sub_e82326d
// CHUNK 0xe824a6a..0xe826261
#include "client/features/render/native/d3d12/sub_e82326d_c01.h"

#include <cstdint>

namespace native::d3d12 {

// Forward declarations for callees in the lift set
extern "C" void sub_e82dcc0(void* rcx, void* rdx, std::uint32_t r8d);   // 0xe82dcc0
extern "C" void sub_e82d960(void* rcx, void* rdx, std::uint16_t r8w, std::uint32_t r9d); // 0xe82d960
extern "C" void sub_ebce390(void* rcx, void* rdx, std::uint32_t r8d);   // 0xebce390 (memset-like thunk)
extern "C" bool sub_ebd1560(std::uint8_t v);                            // 0xebd1560 (format predicate)
extern "C" std::uint16_t sub_e820500(void* rcx, void* rdx, std::uint32_t r8d, void* r9); // 0xe820500
extern "C" void sub_e82de90(void* rcx, void* rdx, void* r8);           // 0xe82de90
extern "C" void sub_e935700(void* rcx);                                // 0xe935700 (jmp thunk)
extern "C" void sub_e835b50(void* rcx, std::uint32_t rdx);            // 0xe835b50
extern "C" void sub_e83ace0(void* rcx, std::uint64_t rdx);            // 0xe83ace0

// Vendor boundary thunk via data slot 0xF99FFA0 -> sub_eea6040 (jmp rax)
inline void eea6040_call(void* a1, void* a2, void* a3, std::uint32_t a4, std::uint32_t a5,
                         void* a6, void* a7, void* a8, void* a9) {
    using Fn = void (*)(void*, void*, void*, std::uint32_t, std::uint32_t,
                       void*, void*, void*, void*);
    Fn fn = reinterpret_cast<Fn>(*reinterpret_cast<std::uintptr_t*>(0xF99FFA0));
    fn(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

static inline void sub_e82326d_chunk_c01(ChunkState_e82326d_c01& s) {
    // 0xe824a6a..0xe826261
    // Map state to locals (live x64 registers across the chunk)
    std::uint8_t* rbx = reinterpret_cast<std::uint8_t*>(s.rbx);
    std::uint8_t* rdi = reinterpret_cast<std::uint8_t*>(s.rdi);
    std::uint8_t* rsi = reinterpret_cast<std::uint8_t*>(s.rsi);
    std::uint8_t* rdx = reinterpret_cast<std::uint8_t*>(s.rdx);
    std::uint8_t* rcx = reinterpret_cast<std::uint8_t*>(s.rcx);
    std::uint8_t* r9  = reinterpret_cast<std::uint8_t*>(s.r9);
    std::uint8_t* r10 = reinterpret_cast<std::uint8_t*>(s.r10);
    std::uint8_t* r11 = reinterpret_cast<std::uint8_t*>(s.r11);
    std::uint8_t* r12 = reinterpret_cast<std::uint8_t*>(s.r12);
    std::uint8_t* r13 = reinterpret_cast<std::uint8_t*>(s.r13);
    std::uint8_t* r14 = reinterpret_cast<std::uint8_t*>(s.r14);
    std::uint8_t* r15 = reinterpret_cast<std::uint8_t*>(s.r15);
    std::uint64_t rax = s.eax;
    std::uint32_t ecx = s.ecx;
    std::uint32_t edx32 = s.edx;
    std::uint32_t r8d = s.r8d;

    // 0xe824a6a..0xe824ab2
    // 0xe824a6a  mov rcx,rsi
    rcx = rsi;
    // 0xe824a6d  mov r8d,8
    r8d = 8;
    // 0xe824a73  call 0xE82DCC0
    sub_e82dcc0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8d);
    // 0xe824a78  nop
    // 0xe824a79  mov r14,[rbx+0x2C0]
    r14 = *reinterpret_cast<std::uint8_t**>(rbx + 0x2C0);
    // 0xe824a80  mov r9d,[rdi+0x34]
    s.r9d = *reinterpret_cast<std::uint32_t*>(rdi + 0x34);
    r9 = reinterpret_cast<std::uint8_t*>(s.r9d);
    // 0xe824a84  cmp byte ptr [rsi+0x13],1
    // 0xe824a88  jne 0xE8251C8
    if (*reinterpret_cast<std::uint8_t*>(rsi + 0x13) != 1) {
        // branch to 0xE8251C8 (later in chunk)
        goto L_0xe8251c8;
    }
    // 0xe824a8e  mov r11d,[rdi+0x30]
    s.r11d = *reinterpret_cast<std::uint32_t*>(rdi + 0x30);
    r11 = reinterpret_cast<std::uint8_t*>(s.r11d);
    // 0xe824a92  mov r10d,[rdi+0x44]
    s.r10d = *reinterpret_cast<std::uint32_t*>(rdi + 0x44);
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe824a96  movzx eax,byte ptr [rdi+0x65]
    rax = *reinterpret_cast<std::uint8_t*>(rdi + 0x65);
    // 0xe824a9a  and al,0x10
    rax &= 0x10;
    // 0xe824a9c  mov r8d,[rsi+4]
    r8d = *reinterpret_cast<std::uint32_t*>(rsi + 4);
    // 0xe824aa0  cmp al,1
    // 0xe824aa2  mov cl,2
    // 0xe824aa4  sbb cl,0
    ecx = 2 - (rax != 0 ? 0 : 1);  // sbb cl,0 after cmp al,1: cl=2-CF, CF=0 when al==1 else 1
    // 0xe824aa7  mov eax,[rdi+0x60]
    rax = *reinterpret_cast<std::uint32_t*>(rdi + 0x60);
    // 0xe824aaa  sub eax,r8d
    rax -= r8d;
    // 0xe824aad  shr r8d,cl
    r8d >>= (ecx & 0x1F);
    // 0xe824ab0  shr eax,cl
    rax >>= (ecx & 0x1F);
    // 0xe824ab2  jmp 0xE8251F0
    goto L_0xe8251f0;

    // 0xe8251c8..0xe8251ed (branch from 0xe824a88 jne)
L_0xe8251c8:
    // 0xe8251c8  movzx r10d,word ptr [rsi+8]
    s.r10d = *reinterpret_cast<std::uint16_t*>(rsi + 8);
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe8251cd  test r10d,r10d
    // 0xe8251d0  jne short 0xE8251D6
    if (s.r10d == 0) {
        // 0xe8251d2  mov r10d,[rdi+0x70]
        s.r10d = *reinterpret_cast<std::uint32_t*>(rdi + 0x70);
        r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    }
L_0xe8251d6:
    // 0xe8251d6  mov ecx,[rsi+4]
    ecx = *reinterpret_cast<std::uint32_t*>(rsi + 4);
    // 0xe8251d9  xor r11d,r11d
    s.r11d = 0;
    r11 = nullptr;
    // 0xe8251dc  mov eax,ecx
    rax = ecx;
    // 0xe8251de  xor edx,edx
    edx32 = 0;
    // 0xe8251e0  div r10d
    if (s.r10d != 0) {
        std::uint32_t quotient = rax / s.r10d;
        std::uint32_t remainder = rax % s.r10d;
        rax = quotient;
        edx32 = remainder;
    }
    // 0xe8251e3  mov r8d,eax
    r8d = static_cast<std::uint32_t>(rax);
    // 0xe8251e6  mov eax,[rdi+0x60]
    rax = *reinterpret_cast<std::uint32_t*>(rdi + 0x60);
    // 0xe8251e9  sub eax,ecx
    rax -= ecx;
    // 0xe8251eb  xor edx,edx
    edx32 = 0;
    // 0xe8251ed  div r10d
    if (s.r10d != 0) {
        std::uint32_t quotient = rax / s.r10d;
        std::uint32_t remainder = rax % s.r10d;
        rax = quotient;
        edx32 = remainder;
    }

    // 0xe8251f0..0xe825264 (common block from 0xe824ab2 jmp)
L_0xe8251f0:
    // 0xe8251f0  mov ecx,r8d
    ecx = r8d;
    // 0xe8251f3  mov [rbx+0xC0],r11d
    *reinterpret_cast<std::uint32_t*>(rbx + 0xC0) = s.r11d;
    // 0xe8251fa  mov [rbx+0xC4],r9d
    *reinterpret_cast<std::uint32_t*>(rbx + 0xC4) = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(r9));
    // 0xe825201  mov [rbx+0xC8],rcx
    *reinterpret_cast<std::uint64_t*>(rbx + 0xC8) = ecx;
    // 0xe825208  mov [rbx+0xD0],eax
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD0) = static_cast<std::uint32_t>(rax);
    // 0xe82520e  mov [rbx+0xD4],r10d
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD4) = s.r10d;
    // 0xe825215  movups xmm0,[rdi+0x48]
    // xmm0 load - skipped (memory op only)
    // 0xe825219  lea rax,[rbx+0xD4]
    rax = reinterpret_cast<std::uintptr_t>(rbx + 0xD4);
    // 0xe825220  movups [rax+4],xmm0
    // xmm0 store - skipped
    // 0xe825224  mov rax,[0x12BB4910]
    rax = *reinterpret_cast<std::uint64_t*>(0x12BB4910);
    // 0xe82522b  mov rcx,[rax+0x400]
    rcx = *reinterpret_cast<std::uint8_t**>(rax + 0x400);
    // 0xe825232  mov rax,[rbx+0xB8]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0xB8);
    // 0xe825239  mov r8,[rax+8]
    r8 = *reinterpret_cast<std::uint8_t**>(rax + 8);
    // 0xe82523d  mov rdx,[rdi]
    rdx = *reinterpret_cast<std::uint8_t**>(rdi);
    // 0xe825240  mov rax,[rcx]
    rax = *reinterpret_cast<std::uint64_t*>(rcx);
    // 0xe825243  mov rax,[rax+0x98]
    rax = *reinterpret_cast<std::uint64_t*>(rax + 0x98);
    // 0xe82524a  mov r10,[0xF99FFA0]
    r10 = *reinterpret_cast<std::uint8_t**>(0xF99FFA0);
    // 0xe825251  mov [rsp+0x20],r8
    // stack store for call
    // 0xe825256  xor r8d,r8d
    r8d = 0;
    // 0xe825259  lea r9,[rbx+0xC0]
    r9 = rbx + 0xC0;
    // 0xe825260  call r10
    using Fn_r10 = void(*)();
    reinterpret_cast<Fn_r10>(r10)();
    // 0xe825263  nop
    // 0xe825264  jmp 0xE825541
    goto L_0xe825541;

    // 0xe825269..0xe825284 (jbe target from 0xe824b69)
L_0xe825269:
    // 0xe825269  mov rcx,[rbx+0x1C0]
    rcx = *reinterpret_cast<std::uint8_t**>(rbx + 0x1C0);
    // 0xe825270  mov dword ptr [rbx+rcx*4+0x3B0],0
    *reinterpret_cast<std::uint32_t*>(rbx + reinterpret_cast<std::uintptr_t>(rcx)*4 + 0x3B0) = 0;
    // 0xe82527b  mov r10d,[rbx+0xF0]
    s.r10d = *reinterpret_cast<std::uint32_t*>(rbx + 0xF0);
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe825282  inc eax
    ++static_cast<std::uint32_t&>(rax);
    // 0xe825284  jmp 0xE82306E
    goto L_0xe82306e_exit;

    // 0xe825289..0xe8252ec (from 0xe824abe jne)
L_0xe825289:
    // 0xe825289  imul rax,rdi,0x78
    rax = reinterpret_cast<std::uintptr_t>(rdi) * 0x78;
    // 0xe82528d  mov rsi,[rbx+0x2C0]
    rsi = *reinterpret_cast<std::uint8_t**>(rbx + 0x2C0);
    // 0xe825294  lea r8,[r9+rax]
    r8 = r9 + rax;
    // 0xe825298  add r8,0x57A180
    r8 += 0x57A180;
    // 0xe82529f  mov rax,[0x12BB4910]
    rax = *reinterpret_cast<std::uint64_t*>(0x12BB4910);
    // 0xe8252a6  mov rcx,[rax+0x400]
    rcx = *reinterpret_cast<std::uint8_t**>(rax + 0x400);
    // 0xe8252ad  mov rax,[rbx+0xB8]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0xB8);
    // 0xe8252b4  mov r9,[rax+8]
    r9 = *reinterpret_cast<std::uint8_t**>(rax + 8);
    // 0xe8252b8  mov rax,[rcx]
    rax = *reinterpret_cast<std::uint64_t*>(rcx);
    // 0xe8252bb  mov rax,[rax+0x90]
    rax = *reinterpret_cast<std::uint64_t*>(rax + 0x90);
    // 0xe8252c2  xor edx,edx
    edx32 = 0;
    // 0xe8252c4  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);
    // 0xe8252ca  nop
    // 0xe8252cb  mov r8,[rbx+0xB8]
    r8 = *reinterpret_cast<std::uint8_t**>(rbx + 0xB8);
    // 0xe8252d2  mov eax,[r8+0x18]
    rax = *reinterpret_cast<std::uint32_t*>(r8 + 0x18);
    // 0xe8252d6  add [r8+8],rax
    *reinterpret_cast<std::uint64_t*>(r8 + 8) += rax;
    // 0xe8252da  mov r10d,[rbx+0xF0]
    s.r10d = *reinterpret_cast<std::uint32_t*>(rbx + 0xF0);
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe8252e1  mov ecx,r10d
    ecx = s.r10d;
    // 0xe8252e4  mov rax,[r8+0x10]
    rax = *reinterpret_cast<std::uint64_t*>(r8 + 0x10);
    // 0xe8252e8  mov [rsi+rcx*8],rax
    *reinterpret_cast<std::uint64_t*>(rsi + ecx*8) = rax;
    // 0xe8252ec  mov r9,[rbx+0xB0]
    r9 = *reinterpret_cast<std::uint8_t**>(rbx + 0xB0);

    // 0xe8252f3..0xe82531a (continuation from 0xe824aec jmp)
L_0xe8252f3:
    // 0xe8252f3  mov ecx,[r8+0x18]
    ecx = *reinterpret_cast<std::uint32_t*>(r8 + 0x18);
    // 0xe8252f7  add rcx,rax
    rcx += rax;
    // 0xe8252fa  mov [r8+0x10],rcx
    *reinterpret_cast<std::uint64_t*>(r8 + 0x10) = reinterpret_cast<std::uintptr_t>(rcx);
    // 0xe8252fe  inc r10d
    ++s.r10d;
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe825301  mov rax,[rbx+0x1C0]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0x1C0);
    // 0xe825308  mov dword ptr [rbx+rax*4+0x3B0],0
    *reinterpret_cast<std::uint32_t*>(rbx + rax*4 + 0x3B0) = 0;
    // 0xe825313  mov rdx,[rbx+0x110]
    rdx = *reinterpret_cast<std::uint8_t**>(rbx + 0x110);
    // 0xe82531a  jmp 0xE823066
    goto L_0xe823066_exit;

    // 0xe82531f..0xe82532d (from 0xe824fe0 jbe)
L_0xe82531f:
    // 0xe82531f  add r8,[rbx+0x1F8]
    r8 += *reinterpret_cast<std::int64_t*>(rbx + 0x1F8);
    // 0xe825326  mov r14,r8
    r14 = r8;
    // 0xe825329  cmp byte ptr [rsi+0x11],0
    // 0xe82532d  jne 0xE8250A5
    if (*reinterpret_cast<std::uint8_t*>(rsi + 0x11) != 0) {
        goto L_0xe8250a5;
    }

    // 0xe825333..0xe82536e
L_0xe825333:
    // 0xe825333  movzx ecx,byte ptr [r14+0xB0]
    ecx = *reinterpret_cast<std::uint8_t*>(r14 + 0xB0);
    // 0xe82533b  call 0xEBD1560
    bool pred = sub_ebd1560(static_cast<std::uint8_t>(ecx));
    // 0xe825340  nop
    // 0xe825341  test al,al
    // 0xe825343  mov r9d,0xAC3
    std::uint32_t r9d_val = 0xAC3;
    // 0xe825349  mov eax,0x60
    rax = 0x60;
    // 0xe82534e  cmovne r9d,eax
    if (!pred) r9d_val = static_cast<std::uint32_t>(rax);
    // 0xe825352  movzx r8d,word ptr [rsi+0xA]
    r8d = *reinterpret_cast<std::uint16_t*>(rsi + 0xA);
    // 0xe825357  mov rax,[rbx+0x90]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0x90);
    // 0xe82535e  mov rdx,[rax+0x30]
    rdx = *reinterpret_cast<std::uint8_t**>(rax + 0x30);
    // 0xe825362  mov rcx,[rbx+0x238]
    rcx = *reinterpret_cast<std::uint8_t**>(rbx + 0x238);
    // 0xe825369  call 0xE82D960
    sub_e82d960(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx),
                static_cast<std::uint16_t>(r8d), r9d_val);
    // 0xe82536e  nop

    // 0xe82536f..0xe8253d9 (test r12d etc.)
    // 0xe82536f  movzx r12d,byte ptr [rsi+0x12]
    std::uint32_t r12d = *reinterpret_cast<std::uint8_t*>(rsi + 0x12);
    // 0xe825374  lea r10,[r14+0x40]
    r10 = r14 + 0x40;
    // 0xe825378  mov r15,[rbx+0x2C0]
    r15 = *reinterpret_cast<std::uint8_t**>(rbx + 0x2C0);
    // 0xe82537f  mov rax,[0x12BB4910]
    rax = *reinterpret_cast<std::uint64_t*>(0x12BB4910);
    // 0xe825386  mov rdi,[rax+0x400]
    rdi = *reinterpret_cast<std::uint8_t**>(rax + 0x400);
    // 0xe82538d  test r12d,r12d
    // 0xe825390  je 0xE825578
    if (r12d == 0) {
        goto L_0xe825578;
    }
    // 0xe825396  mov r8d,0x28
    r8d = 0x28;
    // 0xe82539c  lea rcx,[rbx+0xC0]
    rcx = rbx + 0xC0;
    // 0xe8253a3  mov rdx,r10
    rdx = r10;
    // 0xe8253a6  call 0xEBCE390
    sub_ebce390(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8d);
    // 0xe8253ab  nop
    // 0xe8253ac  mov eax,[r14+0x44]
    rax = *reinterpret_cast<std::uint32_t*>(r14 + 0x44);
    // 0xe8253b0  mov [rbx+0xD0],r12d
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD0) = r12d;
    // 0xe8253b7  mov dword ptr [rbx+0xD4],1
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD4) = 1;
    // 0xe8253c1  cmp eax,8
    // 0xe8253c4  je short 0xE8253CF
    // 0xe8253c6  cmp eax,9
    // 0xe8253c9  jne 0xE825566
    if (rax == 8) {
        goto L_0xe8253cf;
    } else if (rax == 9) {
        // fall through
    } else {
        goto L_0xe825566;
    }
L_0xe8253cf:
    // 0xe8253cf  mov dword ptr [rbx+0xD8],0
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD8) = 0;
    // 0xe8253d9  jmp 0xE825571
    goto L_0xe825571;

    // 0xe8253de..0xe825493 (cmp ecx,0xFFF etc.)
    // 0xe8253de  cmp ecx,0xFFF
    // 0xe8253e4  ja 0xE8257DE
    if (ecx > 0xFFF) {
        goto L_0xe8257de;
    }
    // 0xe8253ea  mov r8d,edi
    r8d = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(rdi));
    // 0xe8253ed  shr r8d,6
    r8d >>= 6;
    // 0xe8253f1  mov r11,[rbx+0x90]
    r11 = *reinterpret_cast<std::uint8_t**>(rbx + 0x90);
    // 0xe8253f8  mov r9,[r11+r8*8+0x224A8]
    r9 = *reinterpret_cast<std::uint8_t**>(r11 + r8*8 + 0x224A8);
    // 0xe825400  mov r10d,1
    s.r10d = 1;
    r10 = reinterpret_cast<std::uint8_t*>(1);
    // 0xe825406  mov ecx,edi
    ecx = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(rdi));
    // 0xe825408  shl r10,cl
    r10 = reinterpret_cast<std::uint8_t*>(1ULL << (ecx & 0x3F));
    // 0xe82540b  bt r9,rdi
    // 0xe82540f  jae 0xE8257A6
    if ((reinterpret_cast<std::uintptr_t>(r9) & (1ULL << (reinterpret_cast<std::uintptr_t>(rdi) & 0x3F))) == 0) {
        goto L_0xe8257a6;
    }
    // 0xe825415  mov ecx,[r11+rdi*8+0x226AC]
    ecx = *reinterpret_cast<std::uint32_t*>(r11 + reinterpret_cast<std::uintptr_t>(rdi)*8 + 0x226AC);
    // 0xe82541d  cmp ecx,0xAC3
    // 0xe825423  je 0xE8257DE
    if (ecx == 0xAC3) {
        goto L_0xe8257de;
    }
    // 0xe825429  mov r8,[rbx+0x90]
    r8 = *reinterpret_cast<std::uint8_t**>(rbx + 0x90);
    // 0xe825430  mov dword ptr [r8+rdi*8+0x226AC],0xAC3
    *reinterpret_cast<std::uint32_t*>(r8 + reinterpret_cast<std::uintptr_t>(rdi)*8 + 0x226AC) = 0xAC3;
    // 0xe82543c  mov r8,[r8+0x22498]
    r8 = *reinterpret_cast<std::uint8_t**>(r8 + 0x22498);
    // 0xe825443  mov rax,[r8+rax]
    rax = *reinterpret_cast<std::uint64_t*>(r8 + rax);
    // 0xe825447  mov qword ptr [rbx+0xC0],0
    *reinterpret_cast<std::uint64_t*>(rbx + 0xC0) = 0;
    // 0xe825452  mov [rbx+0xC8],rax
    *reinterpret_cast<std::uint64_t*>(rbx + 0xC8) = rax;
    // 0xe825459  mov dword ptr [rbx+0xD0],0xFFFFFFFF
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD0) = 0xFFFFFFFF;
    // 0xe825463  mov [rbx+0xD4],ecx
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD4) = ecx;
    // 0xe825469  mov dword ptr [rbx+0xD8],0xAC3
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD8) = 0xAC3;
    // 0xe825473  mov rax,[rdx]
    rax = *reinterpret_cast<std::uint64_t*>(rdx);
    // 0xe825476  mov rax,[rax+0xD0]
    rax = *reinterpret_cast<std::uint64_t*>(rax + 0xD0);
    // 0xe82547d  mov rcx,rdx
    rcx = rdx;
    // 0xe825480  mov edx,1
    edx32 = 1;
    // 0xe825485  lea r8,[rbx+0xC0]
    r8 = rbx + 0xC0;
    // 0xe82548c  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);
    // 0xe825492  nop
    // 0xe825493  jmp 0xE8257DE
    goto L_0xe8257de;

    // 0xe825498..0xe8254a1 (from 0xe824afa je)
L_0xe825498:
    // 0xe825498  mov r10d,[rbx+0xF0]
    s.r10d = *reinterpret_cast<std::uint32_t*>(rbx + 0xF0);
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe82549f  inc eax
    ++static_cast<std::uint32_t&>(rax);
    // 0xe8254a1  jmp 0xE82306E
    goto L_0xe82306e_exit;

    // 0xe8254a6..0xe82553a (from 0xe82518d jne)
L_0xe8254a6:
    // 0xe8254a6  movzx r11d,word ptr [rsi+8]
    s.r11d = *reinterpret_cast<std::uint16_t*>(rsi + 8);
    r11 = reinterpret_cast<std::uint8_t*>(s.r11d);
    // 0xe8254ab  test r11d,r11d
    // 0xe8254ae  jne short 0xE8254B4
    if (s.r11d == 0) {
        // 0xe8254b0  mov r11d,[rdi+0x70]
        s.r11d = *reinterpret_cast<std::uint32_t*>(rdi + 0x70);
        r11 = reinterpret_cast<std::uint8_t*>(s.r11d);
    }
L_0xe8254b4:
    // 0xe8254b4  mov ecx,[rsi+4]
    ecx = *reinterpret_cast<std::uint32_t*>(rsi + 4);
    // 0xe8254b7  xor r15d,r15d
    std::uint32_t r15d = 0;
    // 0xe8254ba  mov eax,ecx
    rax = ecx;
    // 0xe8254bc  xor edx,edx
    edx32 = 0;
    // 0xe8254be  div r11d
    if (s.r11d != 0) {
        std::uint32_t q = rax / s.r11d;
        std::uint32_t r = rax % s.r11d;
        rax = q;
        edx32 = r;
    }
    // 0xe8254c1  mov r9d,eax
    std::uint32_t r9d_local = static_cast<std::uint32_t>(rax);
    // 0xe8254c4  sub r8d,ecx
    r8d -= ecx;
    // 0xe8254c7  mov eax,r8d
    rax = r8d;
    // 0xe8254ca  xor edx,edx
    edx32 = 0;
    // 0xe8254cc  div r11d
    if (s.r11d != 0) {
        std::uint32_t q = rax / s.r11d;
        std::uint32_t r = rax % s.r11d;
        rax = q;
        edx32 = r;
    }
    // 0xe8254cf  mov r8d,eax
    r8d = static_cast<std::uint32_t>(rax);

    // 0xe8254d2..0xe82553a (common block from 0xe8251b5 jmp)
L_0xe8254d2:
    // 0xe8254d2  mov eax,r9d
    rax = r9d_local;
    // 0xe8254d5  mov [rbx+0xC0],r15d
    *reinterpret_cast<std::uint32_t*>(rbx + 0xC0) = r15d;
    // 0xe8254dc  mov ecx,[rdi+0x14]
    ecx = *reinterpret_cast<std::uint32_t*>(rdi + 0x14);
    // 0xe8254df  lea rdx,[rbx+0xD4]
    rdx = rbx + 0xD4;
    // 0xe8254e6  mov [rdx-8],ecx
    *reinterpret_cast<std::uint32_t*>(rbx + 0xCC) = ecx;  // rdx-8 = rbx+0xCC
    // 0xe8254e9  mov rcx,[rdi+0xC]
    rcx = *reinterpret_cast<std::uint8_t**>(rdi + 0xC);
    // 0xe8254ed  mov [rdx-0x10],rcx
    *reinterpret_cast<std::uint64_t*>(rbx + 0xC4) = reinterpret_cast<std::uintptr_t>(rcx);  // rdx-0x10 = rbx+0xC4
    // 0xe8254f1  mov [rbx+0xD0],rax
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD0) = static_cast<std::uint32_t>(rax);
    // 0xe8254f8  mov [rbx+0xD8],r8d
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD8) = r8d;
    // 0xe8254ff  mov [rbx+0xDC],r11d
    *reinterpret_cast<std::uint32_t*>(rbx + 0xDC) = s.r11d;
    // 0xe825506  mov [rbx+0xE0],r10
    *reinterpret_cast<std::uint64_t*>(rbx + 0xE0) = reinterpret_cast<std::uintptr_t>(r10);
    // 0xe82550d  mov rax,[0x12BB4910]
    rax = *reinterpret_cast<std::uint64_t*>(0x12BB4910);
    // 0xe825514  mov rcx,[rax+0x400]
    rcx = *reinterpret_cast<std::uint8_t**>(rax + 0x400);
    // 0xe82551b  mov rax,[rbx+0xB8]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0xB8);
    // 0xe825522  mov r9,[rax+8]
    r9 = *reinterpret_cast<std::uint8_t**>(rax + 8);
    // 0xe825526  mov rdx,[rdi]
    rdx = *reinterpret_cast<std::uint8_t**>(rdi);
    // 0xe825529  mov rax,[rcx]
    rax = *reinterpret_cast<std::uint64_t*>(rcx);
    // 0xe82552c  mov rax,[rax+0x90]
    rax = *reinterpret_cast<std::uint64_t*>(rax + 0x90);
    // 0xe825533  lea r8,[rbx+0xC0]
    r8 = rbx + 0xC0;
    // 0xe82553a  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);

    // 0xe825540  nop
    // 0xe825541..0xe825561 (from 0xe825264 jmp)
L_0xe825541:
    // 0xe825541  mov rdx,[rbx+0xB8]
    rdx = *reinterpret_cast<std::uint8_t**>(rbx + 0xB8);
    // 0xe825548  mov eax,[rdx+0x18]
    rax = *reinterpret_cast<std::uint32_t*>(rdx + 0x18);
    // 0xe82554b  add [rdx+8],rax
    *reinterpret_cast<std::uint64_t*>(rdx + 8) += rax;
    // 0xe82554f  mov r10d,[rbx+0xF0]
    s.r10d = *reinterpret_cast<std::uint32_t*>(rbx + 0xF0);
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe825556  mov eax,r10d
    rax = s.r10d;
    // 0xe825559  mov rcx,[rdx+0x10]
    rcx = *reinterpret_cast<std::uint8_t**>(rdx + 0x10);
    // 0xe82555d  mov [r14+rax*8],rcx
    *reinterpret_cast<std::uint64_t*>(r14 + rax*8) = reinterpret_cast<std::uintptr_t>(rcx);
    // 0xe825561  jmp 0xE825786
    goto L_0xe825786;

    // 0xe825566..0xe825571 (from 0xe8253c9 jne)
L_0xe825566:
    // 0xe825566  mov qword ptr [rbx+0xD8],0
    *reinterpret_cast<std::uint64_t*>(rbx + 0xD8) = 0;
L_0xe825571:
    // 0xe825571  lea r10,[rbx+0xC0]
    r10 = rbx + 0xC0;

    // 0xe825578..0xe8255c3 (from 0xe825390 je)
L_0xe825578:
    // 0xe825578  mov rax,[rbx+0xB8]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0xB8);
    // 0xe82557f  mov r9,[rax+8]
    r9 = *reinterpret_cast<std::uint8_t**>(rax + 8);
    // 0xe825583  mov rdx,[r14]
    rdx = *reinterpret_cast<std::uint8_t**>(r14);
    // 0xe825586  mov rax,[rdi]
    rax = *reinterpret_cast<std::uint64_t*>(rdi);
    // 0xe825589  mov rax,[rax+0x90]
    rax = *reinterpret_cast<std::uint64_t*>(rax + 0x90);
    // 0xe825590  mov rcx,rdi
    rcx = rdi;
    // 0xe825593  mov r8,r10
    r8 = r10;
    // 0xe825596  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);
    // 0xe82559c  nop
    // 0xe82559d  mov rdx,[rbx+0xB8]
    rdx = *reinterpret_cast<std::uint8_t**>(rbx + 0xB8);
    // 0xe8255a4  mov eax,[rdx+0x18]
    rax = *reinterpret_cast<std::uint32_t*>(rdx + 0x18);
    // 0xe8255a7  add [rdx+8],rax
    *reinterpret_cast<std::uint64_t*>(rdx + 8) += rax;
    // 0xe8255ab  mov eax,[rbx+0xF0]
    rax = *reinterpret_cast<std::uint32_t*>(rbx + 0xF0);
    // 0xe8255b1  mov rcx,[rdx+0x10]
    rcx = *reinterpret_cast<std::uint8_t**>(rdx + 0x10);
    // 0xe8255b5  mov [r15+rax*8],rcx
    *reinterpret_cast<std::uint64_t*>(r15 + rax*8) = reinterpret_cast<std::uintptr_t>(rcx);
    // 0xe8255b9  mov eax,[rdx+0x18]
    rax = *reinterpret_cast<std::uint32_t*>(rdx + 0x18);
    // 0xe8255bc  add rax,rcx
    rax += reinterpret_cast<std::uintptr_t>(rcx);
    // 0xe8255bf  mov [rdx+0x10],rax
    *reinterpret_cast<std::uint64_t*>(rdx + 0x10) = rax;
    // 0xe8255c3  mov eax,[rsi]
    rax = *reinterpret_cast<std::uint32_t*>(rsi);
    // 0xe8255c5  test eax,0x20000000
    // 0xe8255ca  je short 0xE8255D3
    if ((rax & 0x20000000) == 0) {
        goto L_0xe8255d3;
    }
    // 0xe8255cc  mov eax,[r14+0x98]
    rax = *reinterpret_cast<std::uint32_t*>(r14 + 0x98);
L_0xe8255d3:
    // 0xe8255d3  and eax,0x1F0F07FF
    rax &= 0x1F0F07FF;
    // 0xe8255d8  mov rcx,[rbx+0x1C0]
    rcx = *reinterpret_cast<std::uint8_t**>(rbx + 0x1C0);
    // 0xe8255df  mov [rbx+rcx*4+0x3B0],eax
    *reinterpret_cast<std::uint32_t*>(rbx + reinterpret_cast<std::uintptr_t>(rcx)*4 + 0x3B0) = static_cast<std::uint32_t>(rax);
    // 0xe8255e6  mov r10d,[rbx+0xF0]
    s.r10d = *reinterpret_cast<std::uint32_t*>(rbx + 0xF0);
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe8255ed  jmp 0xE825790
    goto L_0xe825790;

    // 0xe8255f2..0xe82568e (from 0xe825554 or 0xe82562a jmp)
    // 0xe8255f2  or r9,r10
    r9 = reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(r9) | reinterpret_cast<std::uintptr_t>(r10));
    // 0xe8255f5  mov [r11+r8*8+0x224A8],r9
    *reinterpret_cast<std::uint8_t**>(r11 + reinterpret_cast<std::uintptr_t>(r8)*8 + 0x224A8) = r9;
    // 0xe8255fd  movzx eax,word ptr [r11+0x224A0]
    rax = *reinterpret_cast<std::uint16_t*>(r11 + 0x224A0);
    // 0xe825605  mov [r11+rax*2+0x2A6A8],di
    *reinterpret_cast<std::uint16_t*>(r11 + rax*2 + 0x2A6A8) = static_cast<std::uint16_t>(reinterpret_cast<std::uintptr_t>(rdi));
    // 0xe82560e  inc eax
    ++static_cast<std::uint32_t&>(rax);
    // 0xe825610  mov [r11+0x224A0],ax
    *reinterpret_cast<std::uint16_t*>(r11 + 0x224A0) = static_cast<std::uint16_t>(rax);
    // 0xe825618  mov rax,0x800000008
    rax = 0x800000008;
    // 0xe825622  mov [r11+rdi*8+0x226A8],rax
    *reinterpret_cast<std::uint64_t*>(r11 + reinterpret_cast<std::uintptr_t>(rdi)*8 + 0x226A8) = rax;
    // 0xe82562a  jmp short 0xE82568F
    goto L_0xe82568f;

    // 0xe82562c..0xe82568e
    // 0xe82562c  mov dword ptr [r11+rdi*8+0x226AC],8
    *reinterpret_cast<std::uint32_t*>(r11 + reinterpret_cast<std::uintptr_t>(rdi)*8 + 0x226AC) = 8;
    // 0xe825638  mov r8,[r11+0x22498]
    r8 = *reinterpret_cast<std::uint8_t**>(r11 + 0x22498);
    // 0xe82563f  mov rax,[r8+rax]
    rax = *reinterpret_cast<std::uint64_t*>(r8 + rax);
    // 0xe825643  mov qword ptr [rbx+0xC0],0
    *reinterpret_cast<std::uint64_t*>(rbx + 0xC0) = 0;
    // 0xe82564e  mov [rbx+0xC8],rax
    *reinterpret_cast<std::uint64_t*>(rbx + 0xC8) = rax;
    // 0xe825655  mov dword ptr [rbx+0xD0],0xFFFFFFFF
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD0) = 0xFFFFFFFF;
    // 0xe82565f  mov [rbx+0xD4],ecx
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD4) = ecx;
    // 0xe825665  mov dword ptr [rbx+0xD8],8
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD8) = 8;
    // 0xe82566f  mov rax,[rdx]
    rax = *reinterpret_cast<std::uint64_t*>(rdx);
    // 0xe825672  mov rax,[rax+0xD0]
    rax = *reinterpret_cast<std::uint64_t*>(rax + 0xD0);
    // 0xe825679  mov rcx,rdx
    rcx = rdx;
    // 0xe82567c  mov edx,1
    edx32 = 1;
    // 0xe825681  lea r8,[rbx+0xC0]
    r8 = rbx + 0xC0;
    // 0xe825688  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);
    // 0xe82568e  nop

    // 0xe82568f..0xe825765
L_0xe82568f:
    // 0xe82568f  mov rdi,[rbx+0x2C0]
    rdi = *reinterpret_cast<std::uint8_t**>(rbx + 0x2C0);
    // 0xe825696  mov r9d,[r14+0x34]
    std::uint32_t r9d_local2 = *reinterpret_cast<std::uint32_t*>(r14 + 0x34);
    r9 = reinterpret_cast<std::uint8_t*>(r9d_local2);
    // 0xe82569a  cmp byte ptr [rsi+0x13],1
    // 0xe82569e  jne short 0xE8256C8
    if (*reinterpret_cast<std::uint8_t*>(rsi + 0x13) != 1) {
        goto L_0xe8256c8;
    }
    // 0xe8256a0  mov r11d,[r14+0x30]
    s.r11d = *reinterpret_cast<std::uint32_t*>(r14 + 0x30);
    r11 = reinterpret_cast<std::uint8_t*>(s.r11d);
    // 0xe8256a4  mov r10d,[r14+0x44]
    s.r10d = *reinterpret_cast<std::uint32_t*>(r14 + 0x44);
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe8256a8  movzx eax,byte ptr [r14+0x65]
    rax = *reinterpret_cast<std::uint8_t*>(r14 + 0x65);
    // 0xe8256ad  and al,0x10
    rax &= 0x10;
    // 0xe8256af  mov r8d,[rsi+4]
    r8d = *reinterpret_cast<std::uint32_t*>(rsi + 4);
    // 0xe8256b3  cmp al,1
    // 0xe8256b5  mov cl,2
    // 0xe8256b7  sbb cl,0
    ecx = 2 - (rax != 0 ? 0 : 1);
    // 0xe8256ba  mov eax,[r14+0x60]
    rax = *reinterpret_cast<std::uint32_t*>(r14 + 0x60);
    // 0xe8256be  sub eax,r8d
    rax -= r8d;
    // 0xe8256c1  shr r8d,cl
    r8d >>= (ecx & 0x1F);
    // 0xe8256c4  shr eax,cl
    rax >>= (ecx & 0x1F);
    // 0xe8256c6  jmp short 0xE8256F1
    goto L_0xe8256f1;

    // 0xe8256c8..0xe8256f1 (from 0xe82569e jne)
L_0xe8256c8:
    // 0xe8256c8  movzx r10d,word ptr [rsi+8]
    s.r10d = *reinterpret_cast<std::uint16_t*>(rsi + 8);
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe8256cd  test r10d,r10d
    // 0xe8256d0  jne short 0xE8256D6
    if (s.r10d == 0) {
        // 0xe8256d2  mov r10d,[r14+0x70]
        s.r10d = *reinterpret_cast<std::uint32_t*>(r14 + 0x70);
        r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    }
L_0xe8256d6:
    // 0xe8256d6  mov ecx,[rsi+4]
    ecx = *reinterpret_cast<std::uint32_t*>(rsi + 4);
    // 0xe8256d9  xor r11d,r11d
    s.r11d = 0;
    r11 = nullptr;
    // 0xe8256dc  mov eax,ecx
    rax = ecx;
    // 0xe8256de  xor edx,edx
    edx32 = 0;
    // 0xe8256e0  div r10d
    if (s.r10d != 0) {
        std::uint32_t q = rax / s.r10d;
        std::uint32_t r = rax % s.r10d;
        rax = q;
        edx32 = r;
    }
    // 0xe8256e3  mov r8d,eax
    r8d = static_cast<std::uint32_t>(rax);
    // 0xe8256e6  mov eax,[r14+0x60]
    rax = *reinterpret_cast<std::uint32_t*>(r14 + 0x60);
    // 0xe8256ea  sub eax,ecx
    rax -= ecx;
    // 0xe8256ec  xor edx,edx
    edx32 = 0;
    // 0xe8256ee  div r10d
    if (s.r10d != 0) {
        std::uint32_t q = rax / s.r10d;
        std::uint32_t r = rax % s.r10d;
        rax = q;
        edx32 = r;
    }

L_0xe8256f1:
    // 0xe8256f1  mov ecx,r8d
    ecx = r8d;
    // 0xe8256f4  mov [rbx+0xC0],r11d
    *reinterpret_cast<std::uint32_t*>(rbx + 0xC0) = s.r11d;
    // 0xe8256fb  mov [rbx+0xC4],r9d
    *reinterpret_cast<std::uint32_t*>(rbx + 0xC4) = r9d_local2;
    // 0xe825702  mov [rbx+0xC8],rcx
    *reinterpret_cast<std::uint64_t*>(rbx + 0xC8) = ecx;
    // 0xe825709  mov [rbx+0xD0],eax
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD0) = static_cast<std::uint32_t>(rax);
    // 0xe82570f  mov [rbx+0xD4],r10d
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD4) = s.r10d;
    // 0xe825716  movups xmm0,[r14+0x48]
    // 0xe82571b  lea rax,[rbx+0xD4]
    rax = reinterpret_cast<std::uintptr_t>(rbx + 0xD4);
    // 0xe825722  movups [rax+4],xmm0
    // 0xe825726  mov rax,[0x12BB4910]
    rax = *reinterpret_cast<std::uint64_t*>(0x12BB4910);
    // 0xe82572d  mov rcx,[rax+0x400]
    rcx = *reinterpret_cast<std::uint8_t**>(rax + 0x400);
    // 0xe825734  mov rax,[rbx+0xB8]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0xB8);
    // 0xe82573b  mov r8,[rax+8]
    r8 = *reinterpret_cast<std::uint8_t**>(rax + 8);
    // 0xe82573f  mov rdx,[r14]
    rdx = *reinterpret_cast<std::uint8_t**>(r14);
    // 0xe825742  mov rax,[rcx]
    rax = *reinterpret_cast<std::uint64_t*>(rcx);
    // 0xe825745  mov rax,[rax+0x98]
    rax = *reinterpret_cast<std::uint64_t*>(rax + 0x98);
    // 0xe82574c  mov r10,[0xF99FFA0]
    r10 = *reinterpret_cast<std::uint8_t**>(0xF99FFA0);
    // 0xe825753  mov [rsp+0x20],r8
    // 0xe825758  xor r8d,r8d
    r8d = 0;
    // 0xe82575b  lea r9,[rbx+0xC0]
    r9 = rbx + 0xC0;
    // 0xe825762  call r10
    reinterpret_cast<Fn_r10>(r10)();
    // 0xe825765  nop

    // 0xe825766..0xe82578c
L_0xe825766:
    // 0xe825766  mov rdx,[rbx+0xB8]
    rdx = *reinterpret_cast<std::uint8_t**>(rbx + 0xB8);
    // 0xe82576d  mov eax,[rdx+0x18]
    rax = *reinterpret_cast<std::uint32_t*>(rdx + 0x18);
    // 0xe825770  add [rdx+8],rax
    *reinterpret_cast<std::uint64_t*>(rdx + 8) += rax;
    // 0xe825774  mov r10d,[rbx+0xF0]
    s.r10d = *reinterpret_cast<std::uint32_t*>(rbx + 0xF0);
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe82577b  mov eax,r10d
    rax = s.r10d;
    // 0xe82577e  mov rcx,[rdx+0x10]
    rcx = *reinterpret_cast<std::uint8_t**>(rdx + 0x10);
    // 0xe825782  mov [rdi+rax*8],rcx
    *reinterpret_cast<std::uint64_t*>(rdi + rax*8) = reinterpret_cast<std::uintptr_t>(rcx);

L_0xe825786:
    // 0xe825786  mov eax,[rdx+0x18]
    rax = *reinterpret_cast<std::uint32_t*>(rdx + 0x18);
    // 0xe825789  add rax,rcx
    rax += reinterpret_cast<std::uintptr_t>(rcx);
    // 0xe82578c  mov [rdx+0x10],rax
    *reinterpret_cast<std::uint64_t*>(rdx + 0x10) = rax;

L_0xe825790:
    // 0xe825790  inc r10d
    ++s.r10d;
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe825793  mov r9,[rbx+0xB0]
    r9 = *reinterpret_cast<std::uint8_t**>(rbx + 0xB0);
    // 0xe82579a  mov rdx,[rbx+0x110]
    rdx = *reinterpret_cast<std::uint8_t**>(rbx + 0x110);
    // 0xe8257a1  jmp 0xE823066
    goto L_0xe823066_exit;

    // 0xe8257a6..0xe8257d6 (from 0xe82540f jae)
L_0xe8257a6:
    // 0xe8257a6  or r9,r10
    r9 = reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(r9) | reinterpret_cast<std::uintptr_t>(r10));
    // 0xe8257a9  mov [r11+r8*8+0x224A8],r9
    *reinterpret_cast<std::uint8_t**>(r11 + reinterpret_cast<std::uintptr_t>(r8)*8 + 0x224A8) = r9;
    // 0xe8257b1  movzx eax,word ptr [r11+0x224A0]
    rax = *reinterpret_cast<std::uint16_t*>(r11 + 0x224A0);
    // 0xe8257b9  mov [r11+rax*2+0x2A6A8],di
    *reinterpret_cast<std::uint16_t*>(r11 + rax*2 + 0x2A6A8) = static_cast<std::uint16_t>(reinterpret_cast<std::uintptr_t>(rdi));
    // 0xe8257c2  inc eax
    ++static_cast<std::uint32_t&>(rax);
    // 0xe8257c4  mov [r11+0x224A0],ax
    *reinterpret_cast<std::uint16_t*>(r11 + 0x224A0) = static_cast<std::uint16_t>(rax);
    // 0xe8257cc  mov rax,0xAC300000AC3
    rax = 0xAC300000AC3;
    // 0xe8257d6  mov [r11+rdi*8+0x226A8],rax
    *reinterpret_cast<std::uint64_t*>(r11 + reinterpret_cast<std::uintptr_t>(rdi)*8 + 0x226A8) = rax;

    // 0xe8257de..0xe8258f0 (from 0xe8253e4/0xe825423/0xe825493 ja)
L_0xe8257de:
    // 0xe8257de  mov rdi,[rbx+0x2C0]
    rdi = *reinterpret_cast<std::uint8_t**>(rbx + 0x2C0);
    // 0xe8257e5  mov r10,[r14+0x28]
    r10 = *reinterpret_cast<std::uint8_t**>(r14 + 0x28);
    // 0xe8257e9  cmp byte ptr [rsi+0x13],1
    // 0xe8257ed  mov r8d,[r14+0x60]
    r8d = *reinterpret_cast<std::uint32_t*>(r14 + 0x60);
    // 0xe8257f1  jne short 0xE825818
    if (*reinterpret_cast<std::uint8_t*>(rsi + 0x13) != 1) {
        goto L_0xe825818;
    }
    // 0xe8257f3  mov r15d,[r14+8]
    std::uint32_t r15d_2 = *reinterpret_cast<std::uint32_t*>(r14 + 8);
    // 0xe8257f7  mov r11d,[r14+0x24]
    s.r11d = *reinterpret_cast<std::uint32_t*>(r14 + 0x24);
    r11 = reinterpret_cast<std::uint8_t*>(s.r11d);
    // 0xe8257fb  movzx eax,byte ptr [r14+0x65]
    rax = *reinterpret_cast<std::uint8_t*>(r14 + 0x65);
    // 0xe825800  and al,0x10
    rax &= 0x10;
    // 0xe825802  mov r9d,[rsi+4]
    std::uint32_t r9d_local3 = *reinterpret_cast<std::uint32_t*>(rsi + 4);
    r9 = reinterpret_cast<std::uint8_t*>(r9d_local3);
    // 0xe825806  cmp al,1
    // 0xe825808  mov cl,2
    // 0xe82580a  sbb cl,0
    ecx = 2 - (rax != 0 ? 0 : 1);
    // 0xe82580d  sub r8d,r9d
    r8d -= r9d_local3;
    // 0xe825810  shr r9d,cl
    r9d_local3 >>= (ecx & 0x1F);
    // 0xe825813  shr r8d,cl
    r8d >>= (ecx & 0x1F);
    // 0xe825816  jmp short 0xE825844
    goto L_0xe825844;

    // 0xe825818..0xe825844 (from 0xe8257f1 jne)
L_0xe825818:
    // 0xe825818  movzx r11d,word ptr [rsi+8]
    s.r11d = *reinterpret_cast<std::uint16_t*>(rsi + 8);
    r11 = reinterpret_cast<std::uint8_t*>(s.r11d);
    // 0xe82581d  test r11d,r11d
    // 0xe825820  jne short 0xE825826
    if (s.r11d == 0) {
        // 0xe825822  mov r11d,[r14+0x70]
        s.r11d = *reinterpret_cast<std::uint32_t*>(r14 + 0x70);
        r11 = reinterpret_cast<std::uint8_t*>(s.r11d);
    }
L_0xe825826:
    // 0xe825826  mov ecx,[rsi+4]
    ecx = *reinterpret_cast<std::uint32_t*>(rsi + 4);
    // 0xe825829  xor r15d,r15d
    std::uint32_t r15d_3 = 0;
    // 0xe82582c  mov eax,ecx
    rax = ecx;
    // 0xe82582e  xor edx,edx
    edx32 = 0;
    // 0xe825830  div r11d
    if (s.r11d != 0) {
        std::uint32_t q = rax / s.r11d;
        std::uint32_t r = rax % s.r11d;
        rax = q;
        edx32 = r;
    }
    // 0xe825833  mov r9d,eax
    std::uint32_t r9d_local4 = static_cast<std::uint32_t>(rax);
    // 0xe825836  sub r8d,ecx
    r8d -= ecx;
    // 0xe825839  mov eax,r8d
    rax = r8d;
    // 0xe82583c  xor edx,edx
    edx32 = 0;
    // 0xe82583e  div r11d
    if (s.r11d != 0) {
        std::uint32_t q = rax / s.r11d;
        std::uint32_t r = rax % s.r11d;
        rax = q;
        edx32 = r;
    }
    // 0xe825841  mov r8d,eax
    r8d = static_cast<std::uint32_t>(rax);

L_0xe825844:
    // 0xe825844  mov eax,r9d
    rax = r9d_local4;
    // 0xe825847  mov [rbx+0xC0],r15d
    *reinterpret_cast<std::uint32_t*>(rbx + 0xC0) = r15d_3;
    // 0xe82584e  mov ecx,[r14+0x14]
    ecx = *reinterpret_cast<std::uint32_t*>(r14 + 0x14);
    // 0xe825852  lea rdx,[rbx+0xD4]
    rdx = rbx + 0xD4;
    // 0xe825859  mov [rdx-8],ecx
    *reinterpret_cast<std::uint32_t*>(rbx + 0xCC) = ecx;
    // 0xe82585c  mov rcx,[r14+0xC]
    rcx = *reinterpret_cast<std::uint8_t**>(r14 + 0xC);
    // 0xe825860  mov [rdx-0x10],rcx
    *reinterpret_cast<std::uint64_t*>(rbx + 0xC4) = reinterpret_cast<std::uintptr_t>(rcx);
    // 0xe825864  mov [rbx+0xD0],rax
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD0) = static_cast<std::uint32_t>(rax);
    // 0xe82586b  mov [rbx+0xD8],r8d
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD8) = r8d;
    // 0xe825872  mov [rbx+0xDC],r11d
    *reinterpret_cast<std::uint32_t*>(rbx + 0xDC) = s.r11d;
    // 0xe825879  mov [rbx+0xE0],r10
    *reinterpret_cast<std::uint64_t*>(rbx + 0xE0) = reinterpret_cast<std::uintptr_t>(r10);
    // 0xe825880  mov rax,[0x12BB4910]
    rax = *reinterpret_cast<std::uint64_t*>(0x12BB4910);
    // 0xe825887  mov rcx,[rax+0x400]
    rcx = *reinterpret_cast<std::uint8_t**>(rax + 0x400);
    // 0xe82588e  mov rax,[rbx+0xB8]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0xB8);
    // 0xe825895  mov r9,[rax+8]
    r9 = *reinterpret_cast<std::uint8_t**>(rax + 8);
    // 0xe825899  mov rdx,[r14]
    rdx = *reinterpret_cast<std::uint8_t**>(r14);
    // 0xe82589c  mov rax,[rcx]
    rax = *reinterpret_cast<std::uint64_t*>(rcx);
    // 0xe82589f  mov rax,[rax+0x90]
    rax = *reinterpret_cast<std::uint64_t*>(rax + 0x90);
    // 0xe8258a6  lea r8,[rbx+0xC0]
    r8 = rbx + 0xC0;
    // 0xe8258ad  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);
    // 0xe8258b3  nop
    // 0xe8258b4  mov rdx,[rbx+0xB8]
    rdx = *reinterpret_cast<std::uint8_t**>(rbx + 0xB8);
    // 0xe8258bb  mov eax,[rdx+0x18]
    rax = *reinterpret_cast<std::uint32_t*>(rdx + 0x18);
    // 0xe8258be  add [rdx+8],rax
    *reinterpret_cast<std::uint64_t*>(rdx + 8) += rax;
    // 0xe8258c2  mov r10d,[rbx+0xF0]
    s.r10d = *reinterpret_cast<std::uint32_t*>(rbx + 0xF0);
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe8258c9  mov eax,r10d
    rax = s.r10d;
    // 0xe8258cc  mov rcx,[rdx+0x10]
    rcx = *reinterpret_cast<std::uint8_t**>(rdx + 0x10);
    // 0xe8258d0  mov [rdi+rax*8],rcx
    *reinterpret_cast<std::uint64_t*>(rdi + rax*8) = reinterpret_cast<std::uintptr_t>(rcx);
    // 0xe8258d4  mov eax,[rdx+0x18]
    rax = *reinterpret_cast<std::uint32_t*>(rdx + 0x18);
    // 0xe8258d7  add rax,rcx
    rax += reinterpret_cast<std::uintptr_t>(rcx);
    // 0xe8258da  mov [rdx+0x10],rax
    *reinterpret_cast<std::uint64_t*>(rdx + 0x10) = rax;
    // 0xe8258de  mov rax,[rbx+0x1C0]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0x1C0);
    // 0xe8258e5  mov dword ptr [rbx+rax*4+0x3B0],0
    *reinterpret_cast<std::uint32_t*>(rbx + rax*4 + 0x3B0) = 0;
    // 0xe8258f0  jmp 0xE825790
    goto L_0xe825790;

    // 0xe8258f5..0xe825915
    // 0xe8258f5  mov rcx,[rbx+0xA0]
    rcx = *reinterpret_cast<std::uint8_t**>(rbx + 0xA0);
    // 0xe8258fc  lea rdx,[rbx+0x3B0]
    rdx = rbx + 0x3B0;
    // 0xe825903  mov r8d,0x41
    r8d = 0x41;
    // 0xe825909  mov r9,[rbx+0x388]
    r9 = *reinterpret_cast<std::uint8_t**>(rbx + 0x388);
    // 0xe825910  call 0xE820500
    {
        using Fn = std::uint16_t(*)(void*, void*, std::uint32_t, void*);
        std::uint16_t ret = Fn(sub_e820500)(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8d, reinterpret_cast<void*>(r9));
        rax = ret;
    }
    // 0xe825915  nop
    // 0xe825916  mov esi,eax
    std::uint32_t esi = static_cast<std::uint32_t>(rax);
    // 0xe825918  cmp ax,[rbx+0x10C]
    // 0xe82591f  je short 0xE825962
    if (static_cast<std::uint16_t>(rax) == *reinterpret_cast<std::uint16_t*>(rbx + 0x10C)) {
        goto L_0xe825962;
    }
    // 0xe825921  mov rax,[rbx+0x90]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0x90);
    // 0xe825928  mov rcx,[rax+0x30]
    rcx = *reinterpret_cast<std::uint8_t**>(rax + 0x30);
    // 0xe82592c  movzx eax,si
    rax = static_cast<std::uint16_t>(esi);
    // 0xe82592f  mov rdx,[rbx+0xA0]
    rdx = *reinterpret_cast<std::uint8_t**>(rbx + 0xA0);
    // 0xe825936  movzx r8d,word ptr [rdx+0x24]
    r8d = *reinterpret_cast<std::uint16_t*>(rdx + 0x24);
    // 0xe82593b  imul r8d,eax
    r8d *= static_cast<std::uint32_t>(rax);
    // 0xe82593f  imul r8d,[rdx+0x20]
    r8d *= *reinterpret_cast<std::uint32_t*>(rdx + 0x20);
    // 0xe825944  add r8,[rdx+0x18]
    r8 = reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(r8) + *reinterpret_cast<std::uint64_t*>(rdx + 0x18));
    // 0xe825948  mov rax,[rcx]
    rax = *reinterpret_cast<std::uint64_t*>(rcx);
    // 0xe82594b  mov rax,[rax+0xF8]
    rax = *reinterpret_cast<std::uint64_t*>(rax + 0xF8);
    // 0xe825952  xor edx,edx
    edx32 = 0;
    // 0xe825954  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);
    // 0xe82595a  nop
    // 0xe82595b  mov [rbx+0x10C],si
    *reinterpret_cast<std::uint16_t*>(rbx + 0x10C) = static_cast<std::uint16_t>(esi);

L_0xe825962:
    // 0xe825962  mov rax,[rbx+0x90]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0x90);
    // 0xe825969  mov rcx,[rax+0x30]
    rcx = *reinterpret_cast<std::uint8_t**>(rax + 0x30);
    // 0xe82596d  mov rdi,[rbx+0x2C0]
    rdi = *reinterpret_cast<std::uint8_t**>(rbx + 0x2C0);
    // 0xe825974  mov r8,[rdi]
    r8 = *reinterpret_cast<std::uint8_t**>(rdi);
    // 0xe825977  mov rax,[rcx]
    rax = *reinterpret_cast<std::uint64_t*>(rcx);
    // 0xe82597a  mov rax,[rax+0xF8]
    rax = *reinterpret_cast<std::uint64_t*>(rax + 0xF8);
    // 0xe825981  mov edx,1
    edx32 = 1;
    // 0xe825986  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);
    // 0xe82598c  nop
    // 0xe82598d  mov rax,[rbx+0x90]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0x90);
    // 0xe825994  mov rcx,[rax+0x30]
    rcx = *reinterpret_cast<std::uint8_t**>(rax + 0x30);
    // 0xe825998  mov r8,[rdi]
    r8 = *reinterpret_cast<std::uint8_t**>(rdi);
    // 0xe82599b  mov rax,[rcx]
    rax = *reinterpret_cast<std::uint64_t*>(rcx);
    // 0xe82599e  mov rax,[rax+0xF8]
    rax = *reinterpret_cast<std::uint64_t*>(rax + 0xF8);
    // 0xe8259a5  mov edx,4
    edx32 = 4;
    // 0xe8259aa  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);
    // 0xe8259b0  nop
    // 0xe8259b1  mov rax,[rdi]
    rax = *reinterpret_cast<std::uint64_t*>(rdi);
    // 0xe8259b4  mov [rbx+0xC0],rax
    *reinterpret_cast<std::uint64_t*>(rbx + 0xC0) = rax;
    // 0xe8259bb  mov [rbx+0xC8],si
    *reinterpret_cast<std::uint64_t*>(rbx + 0xC8) = static_cast<std::uint16_t>(esi);
    // 0xe8259c2  lea rcx,[rbx+0x670]
    rcx = rbx + 0x670;
    // 0xe8259c9  mov rdx,[rbx+0x178]
    rdx = *reinterpret_cast<std::uint8_t**>(rbx + 0x178);
    // 0xe8259d0  lea r8,[rbx+0xC0]
    r8 = rbx + 0xC0;
    // 0xe8259d7  call 0xE82DE90
    sub_e82de90(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), reinterpret_cast<void*>(r8));
    // 0xe8259dc  nop
    // 0xe8259dd  mov rdx,[rbx+0x2D0]
    rdx = *reinterpret_cast<std::uint8_t**>(rbx + 0x2D0);
    // 0xe8259e4  sub rdx,rdi
    rdx = reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(rdx) - reinterpret_cast<std::uintptr_t>(rdi));
    // 0xe8259e7  cmp rdx,0x1000
    // 0xe8259ee  jb short 0xE825A0C
    if (reinterpret_cast<std::uintptr_t>(rdx) < 0x1000) {
        goto L_0xe825a0c;
    }
    // 0xe8259f0  mov rax,[rdi-8]
    rax = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uintptr_t>(rdi) - 8);
    // 0xe8259f4  add rdi,0xFFFFFFFFFFFFFFF8
    rdi = reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(rdi) - 8);
    // 0xe8259f8  sub rdi,rax
    rdi = reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(rdi) - rax);
    // 0xe8259fb  cmp rdi,0x20
    // 0xe8259ff  jae 0xE82D4C4
    if (reinterpret_cast<std::uintptr_t>(rdi) >= 0x20) {
        // jumps out of chunk - treat as exit
        goto L_0xe82d4c4_exit;
    }
    // 0xe825a05  add rdx,0x27
    rdx = reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(rdx) + 0x27);
    // 0xe825a09  mov rdi,rax
    rdi = reinterpret_cast<std::uint8_t*>(rax);

L_0xe825a0c:
    // 0xe825a0c  mov rcx,rdi
    rcx = rdi;
    // 0xe825a0f  call 0xE935700
    sub_e935700(reinterpret_cast<void*>(rcx));
    // 0xe825a14  jmp 0xE827C85
    goto L_0xe827c85_exit;

    // 0xe825a19..0xe825a5a
    // 0xe825a19  movdqa [rbx+0x220],xmm9
    // xmm9 store - skipped
    // 0xe825a22  mov qword ptr [rbx+0x230],0
    *reinterpret_cast<std::uint64_t*>(rbx + 0x230) = 0;
    // 0xe825a2d  mov edx,0x41
    edx32 = 0x41;
    // 0xe825a32  lea rcx,[rbx+0x220]
    rcx = rbx + 0x220;
    // 0xe825a39  call 0xE835B50
    sub_e835b50(reinterpret_cast<void*>(rcx), edx32);
    // 0xe825a3e  nop
    // 0xe825a3f  add [rbx+0x200],rdi
    *reinterpret_cast<std::uint64_t*>(rbx + 0x200) += reinterpret_cast<std::uintptr_t>(rdi);
    // 0xe825a46  mov r8d,0x104
    r8d = 0x104;
    // 0xe825a4c  lea rcx,[rbx+0x3B0]
    rcx = rbx + 0x3B0;
    // 0xe825a53  xor edx,edx
    edx32 = 0;
    // 0xe825a55  call 0xEEC6ED0
    // sub_eec6ed0 not in lift set - boundary call via data slot
    eea6040_call(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);
    // 0xe825a5a  xor eax,eax
    rax = 0;
    // 0xe825a5c  xor r10d,r10d
    s.r10d = 0;
    r10 = nullptr;
    // 0xe825a5f  mov r9,[rbx+0xB0]
    r9 = *reinterpret_cast<std::uint8_t**>(rbx + 0xB0);
    // 0xe825a66  jmp short 0xE825AB3
    goto L_0xe825ab3;

    // 0xe825a70..0xe825ab3 (loop body)
L_0xe825a70:
    // 0xe825a70  mov rax,[rbx+0x220]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0x220);
    // 0xe825a77  mov r8,[rbx+0xB8]
    r8 = *reinterpret_cast<std::uint8_t**>(rbx + 0xB8);
    // 0xe825a7e  mov ecx,[r8+0x18]
    ecx = *reinterpret_cast<std::uint32_t*>(r8 + 0x18);
    // 0xe825a82  add [r8+8],rcx
    *reinterpret_cast<std::uint64_t*>(r8 + 8) += ecx;
    // 0xe825a86  mov ecx,r10d
    ecx = s.r10d;
    // 0xe825a89  inc r10d
    ++s.r10d;
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe825a8c  mov rdx,[r8+0x10]
    rdx = *reinterpret_cast<std::uint8_t**>(r8 + 0x10);
    // 0xe825a90  mov [rax+rcx*8],rdx
    *reinterpret_cast<std::uint64_t*>(rax + ecx*8) = reinterpret_cast<std::uintptr_t>(rdx);
    // 0xe825a94  mov eax,[r8+0x18]
    rax = *reinterpret_cast<std::uint32_t*>(r8 + 0x18);
    // 0xe825a98  add rax,rdx
    rax += reinterpret_cast<std::uintptr_t>(rdx);
    // 0xe825a9b  mov [r8+0x10],rax
    *reinterpret_cast<std::uint64_t*>(r8 + 0x10) = rax;
    // 0xe825a9f  mov dword ptr [rbx+r11*4+0x3B0],0
    *reinterpret_cast<std::uint32_t*>(rbx + rax*4 + 0x3B0) = 0;
    // 0xe825aab  mov eax,[rbx+0x1D0]
    rax = *reinterpret_cast<std::uint32_t*>(rbx + 0x1D0);
    // 0xe825ab1  inc eax
    ++static_cast<std::uint32_t&>(rax);

L_0xe825ab3:
    // 0xe825ab3  mov r8d,[0x12AE0D80]
    r8d = *reinterpret_cast<std::uint32_t*>(0x12AE0D80);
    // 0xe825aba  cmp eax,r8d
    // 0xe825abd  jae 0xE827A11
    if (static_cast<std::uint32_t>(rax) >= r8d) {
        goto L_0xe827a11_exit;
    }
    // 0xe825ac3  mov [rbx+0x1D0],eax
    *reinterpret_cast<std::uint32_t*>(rbx + 0x1D0) = static_cast<std::uint32_t>(rax);
    // 0xe825ac9  mov r11d,eax
    std::uint32_t r11d_local = static_cast<std::uint32_t>(rax);
    // 0xe825acc  lea rax,[r11+r11*4]
    rax = r11d_local * 5;
    // 0xe825ad0  mov rcx,[rbx+0x200]
    rcx = *reinterpret_cast<std::uint8_t**>(rbx + 0x200);
    // 0xe825ad7  movzx edi,word ptr [rcx+rax*4+0xA]
    std::uint32_t edi_local = *reinterpret_cast<std::uint16_t*>(rcx + rax*4 + 0xA);
    // 0xe825adc  cmp rdi,0xFFFF
    // 0xe825ae3  je short 0xE825A70
    if (edi_local == 0xFFFF) {
        goto L_0xe825a70;
    }
    // 0xe825ae5  mov [rbx+0x130],r11
    *reinterpret_cast<std::uint64_t*>(rbx + 0x130) = r11d_local;
    // 0xe825aec  mov [rbx+0x110],r10d
    *reinterpret_cast<std::uint32_t*>(rbx + 0x110) = s.r10d;
    // 0xe825af3  lea rsi,[rcx+rax*4]
    rsi = rcx + rax*4;
    // 0xe825af7  movzx eax,byte ptr [rsi+0x13]
    rax = *reinterpret_cast<std::uint8_t*>(rsi + 0x13);
    // 0xe825afb  cmp rax,9
    // 0xe825aff  ja 0xE8270E2
    if (rax > 9) {
        goto L_0xe8270e2_exit;
    }
    // 0xe825b05  lea rcx,[0xF4EE7D0]
    rcx = reinterpret_cast<std::uint8_t*>(0xF4EE7D0);
    // 0xe825b0c  movsxd rax,[rcx+rax*4]
    rax = *reinterpret_cast<std::int32_t*>(rcx + rax*4);
    // 0xe825b10  add rax,rcx
    rax += reinterpret_cast<std::uintptr_t>(rcx);
    // 0xe825b13  jmp rax
    // indirect jump - switch dispatch; for lift, note as exit path
    goto L_0xe825b13_exit;

    // 0xe825b15..0xe825b67
    // 0xe825b15  mov rax,[rbx+0x130]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0x130);
    // 0xe825b1c  mov dword ptr [rbx+rax*4+0x3B0],0
    *reinterpret_cast<std::uint32_t*>(rbx + rax*4 + 0x3B0) = 0;
    // 0xe825b27  movzx edi,word ptr [rsi+0xA]
    edi_local = *reinterpret_cast<std::uint16_t*>(rsi + 0xA);
    // 0xe825b2b  imul rax,rdi,0x78
    rax = edi_local * 0x78;
    // 0xe825b2f  add rax,[rbx+0x5D8]
    rax += *reinterpret_cast<std::uint64_t*>(rbx + 0x5D8);
    // 0xe825b36  shl edi,7
    edi_local <<= 7;
    // 0xe825b39  add rdi,[rbx+0x588]
    rdi = reinterpret_cast<std::uint8_t*>(edi_local + *reinterpret_cast<std::uint64_t*>(rbx + 0x588));
    // 0xe825b40  cmp byte ptr [rsi+0x13],1
    // 0xe825b44  cmove rdi,rax
    if (*reinterpret_cast<std::uint8_t*>(rsi + 0x13) == 1) {
        rdi = reinterpret_cast<std::uint8_t*>(rax);
    }
    // 0xe825b48  cmp byte ptr [rsi+0x11],0
    // 0xe825b4c  je 0xE827245
    if (*reinterpret_cast<std::uint8_t*>(rsi + 0x11) == 0) {
        goto L_0xe827245_exit;
    }
    // 0xe825b52  mov rcx,rsi
    rcx = rsi;
    // 0xe825b55  mov rdx,[rbx+0x90]
    rdx = *reinterpret_cast<std::uint8_t**>(rbx + 0x90);
    // 0xe825b5c  mov r8d,8
    r8d = 8;
    // 0xe825b62  call 0xE82DCC0
    sub_e82dcc0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), r8d);
    // 0xe825b67  nop
    // 0xe825b68  mov r14,[rbx+0x220]
    r14 = *reinterpret_cast<std::uint8_t**>(rbx + 0x220);
    // 0xe825b6f  mov r9d,[rdi+0x34]
    s.r9d = *reinterpret_cast<std::uint32_t*>(rdi + 0x34);
    r9 = reinterpret_cast<std::uint8_t*>(s.r9d);
    // 0xe825b73  cmp byte ptr [rsi+0x13],1
    // 0xe825b77  jne 0xE82729B
    if (*reinterpret_cast<std::uint8_t*>(rsi + 0x13) != 1) {
        goto L_0xe82729b_exit;
    }
    // 0xe825b7d  mov r11d,[rdi+0x30]
    s.r11d = *reinterpret_cast<std::uint32_t*>(rdi + 0x30);
    r11 = reinterpret_cast<std::uint8_t*>(s.r11d);
    // 0xe825b81  mov r10d,[rdi+0x44]
    s.r10d = *reinterpret_cast<std::uint32_t*>(rdi + 0x44);
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe825b85  movzx eax,byte ptr [rdi+0x65]
    rax = *reinterpret_cast<std::uint8_t*>(rdi + 0x65);
    // 0xe825b89  and al,0x10
    rax &= 0x10;
    // 0xe825b8b  mov r8d,[rsi+4]
    r8d = *reinterpret_cast<std::uint32_t*>(rsi + 4);
    // 0xe825b8f  cmp al,1
    // 0xe825b91  mov cl,2
    // 0xe825b93  sbb cl,0
    ecx = 2 - (rax != 0 ? 0 : 1);
    // 0xe825b96  mov eax,[rdi+0x60]
    rax = *reinterpret_cast<std::uint32_t*>(rdi + 0x60);
    // 0xe825b99  sub eax,r8d
    rax -= r8d;
    // 0xe825b9c  shr r8d,cl
    r8d >>= (ecx & 0x1F);
    // 0xe825b9f  shr eax,cl
    rax >>= (ecx & 0x1F);
    // 0xe825ba1  jmp 0xE8272C3
    goto L_0xe8272c3_exit;

    // 0xe825ba6..0xe825bdc
    // 0xe825ba6  mov rax,[rbx+0x220]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0x220);
    // 0xe825bad  mov r8,[rbx+0xB8]
    r8 = *reinterpret_cast<std::uint8_t**>(rbx + 0xB8);
    // 0xe825bb4  mov ecx,[r8+0x18]
    ecx = *reinterpret_cast<std::uint32_t*>(r8 + 0x18);
    // 0xe825bb8  add [r8+8],rcx
    *reinterpret_cast<std::uint64_t*>(r8 + 8) += ecx;
    // 0xe825bbc  mov r10d,[rbx+0x110]
    s.r10d = *reinterpret_cast<std::uint32_t*>(rbx + 0x110);
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe825bc3  mov ecx,r10d
    ecx = s.r10d;
    // 0xe825bc6  inc r10d
    ++s.r10d;
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe825bc9  mov rdx,[r8+0x10]
    rdx = *reinterpret_cast<std::uint8_t**>(r8 + 0x10);
    // 0xe825bcd  mov [rax+rcx*8],rdx
    *reinterpret_cast<std::uint64_t*>(rax + ecx*8) = reinterpret_cast<std::uintptr_t>(rdx);
    // 0xe825bd1  mov eax,[r8+0x18]
    rax = *reinterpret_cast<std::uint32_t*>(r8 + 0x18);
    // 0xe825bd5  add rax,rdx
    rax += reinterpret_cast<std::uintptr_t>(rdx);
    // 0xe825bd8  mov [r8+0x10],rax
    *reinterpret_cast<std::uint64_t*>(r8 + 0x10) = rax;
    // 0xe825bdc  jmp 0xE8273D2
    goto L_0xe8273d2_exit;

    // 0xe825be1..0xe825c44
    // 0xe825be1  mov rax,[rbx+0x140]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0x140);
    // 0xe825be8  test rax,rax
    // 0xe825beb  je 0xE8270E2
    if (rax == 0) {
        goto L_0xe8270e2_exit;
    }
    // 0xe825bf1  mov rsi,[rbx+0x130]
    rsi = *reinterpret_cast<std::uint8_t**>(rbx + 0x130);
    // 0xe825bf8  shl rsi,4
    rsi = reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(rsi) << 4);
    // 0xe825bfc  add rsi,rax
    rsi += rax;
    // 0xe825bff  xor edi,edi
    edi_local = 0;
    // 0xe825c01  mov r14,[rbx+0x220]
    r14 = *reinterpret_cast<std::uint8_t**>(rbx + 0x220);
    // 0xe825c08  jmp short 0xE825C46
    goto L_0xe825c46;

    // 0xe825c10..0xe825c46 (loop body)
L_0xe825c10:
    // 0xe825c10  mov r8d,[rbx+0x110]
    r8d = *reinterpret_cast<std::uint32_t*>(rbx + 0x110);
    // 0xe825c17  mov eax,r8d
    rax = r8d;
    // 0xe825c1a  mov rdx,[rbx+0xB8]
    rdx = *reinterpret_cast<std::uint8_t**>(rbx + 0xB8);
    // 0xe825c21  mov ecx,[rdx+0x18]
    ecx = *reinterpret_cast<std::uint32_t*>(rdx + 0x18);
    // 0xe825c24  add [rdx+8],rcx
    *reinterpret_cast<std::uint64_t*>(rdx + 8) += ecx;
    // 0xe825c28  mov rcx,[rdx+0x10]
    rcx = *reinterpret_cast<std::uint8_t**>(rdx + 0x10);
    // 0xe825c2c  mov [r14+rax*8],rcx
    *reinterpret_cast<std::uint64_t*>(r14 + rax*8) = reinterpret_cast<std::uintptr_t>(rcx);
    // 0xe825c30  mov eax,[rdx+0x18]
    rax = *reinterpret_cast<std::uint32_t*>(rdx + 0x18);
    // 0xe825c33  add rax,rcx
    rax += reinterpret_cast<std::uintptr_t>(rcx);
    // 0xe825c36  mov [rdx+0x10],rax
    *reinterpret_cast<std::uint64_t*>(rdx + 0x10) = rax;
    // 0xe825c3a  inc r8d
    ++r8d;
    // 0xe825c3d  mov [rbx+0x110],r8d
    *reinterpret_cast<std::uint32_t*>(rbx + 0x110) = r8d;
    // 0xe825c44  inc edi
    ++edi_local;

L_0xe825c46:
    // 0xe825c46  mov ecx,edi
    ecx = edi_local;
    // 0xe825c48  cmp [rsi+8],rcx
    // 0xe825c4c  jbe 0xE82733C
    if (*reinterpret_cast<std::uint64_t*>(rsi + 8) <= ecx) {
        goto L_0xe82733c_exit;
    }
    // 0xe825c52  mov rax,[rsi]
    rax = *reinterpret_cast<std::uint64_t*>(rsi);
    // 0xe825c55  test rax,rax
    // 0xe825c58  je short 0xE825C10
    if (rax == 0) {
        goto L_0xe825c10;
    }
    // 0xe825c5a  lea rdx,[rcx+rcx*4]
    rdx = reinterpret_cast<std::uint8_t*>(rcx * 5);
    // 0xe825c5e  movzx ecx,word ptr [rax+rdx*4+0xA]
    ecx = *reinterpret_cast<std::uint16_t*>(rax + reinterpret_cast<std::uintptr_t>(rdx)*4 + 0xA);
    // 0xe825c63  cmp rcx,0xFFFF
    // 0xe825c6a  je short 0xE825C10
    if (ecx == 0xFFFF) {
        goto L_0xe825c10;
    }
    // 0xe825c6c  lea r12,[rax+rdx*4]
    r12 = rax + reinterpret_cast<std::uintptr_t>(rdx)*4;
    // 0xe825c70  imul rax,rcx,0x78
    rax = ecx * 0x78;
    // 0xe825c74  mov rdx,[rbx+0x3A0]
    rdx = *reinterpret_cast<std::uint8_t**>(rbx + 0x3A0);
    // 0xe825c7b  lea r15,[rdx+rax]
    r15 = rdx + rax;
    // 0xe825c7f  cmp byte ptr [r12+0x11],0
    // 0xe825c85  mov rdx,[rbx+0x90]
    rdx = *reinterpret_cast<std::uint8_t**>(rbx + 0x90);
    // 0xe825c8c  mov rdx,[rdx+0x30]
    rdx = *reinterpret_cast<std::uint8_t**>(rdx + 0x30);
    // 0xe825c90  movzx r8d,cx
    r8d = static_cast<std::uint32_t>(ecx);
    // 0xe825c94  je 0xE825D24
    if (*reinterpret_cast<std::uint8_t*>(r12 + 0x11) == 0) {
        goto L_0xe825d24;
    }
    // 0xe825c9a  cmp r8d,0xFFF
    // 0xe825ca1  ja 0xE825E80
    if (r8d > 0xFFF) {
        goto L_0xe825e80;
    }
    // 0xe825ca7  mov r8d,ecx
    r8d = static_cast<std::uint32_t>(ecx);
    // 0xe825caa  shr r8d,6
    r8d >>= 6;
    // 0xe825cae  mov r11,[rbx+0x90]
    r11 = *reinterpret_cast<std::uint8_t**>(rbx + 0x90);
    // 0xe825cb5  mov r9,[r11+r8*8+0x224A8]
    r9 = *reinterpret_cast<std::uint8_t**>(r11 + r8*8 + 0x224A8);
    // 0xe825cbd  mov r10d,1
    s.r10d = 1;
    r10 = reinterpret_cast<std::uint8_t*>(1);
    // 0xe825cc3  shl r10,cl
    r10 = reinterpret_cast<std::uint8_t*>(1ULL << (ecx & 0x3F));
    // 0xe825cc6  bt r9,rcx
    // 0xe825cca  jae 0xE825DDF
    if ((reinterpret_cast<std::uintptr_t>(r9) & (1ULL << (ecx & 0x3F))) == 0) {
        goto L_0xe825ddf;
    }
    // 0xe825cd0  mov r8d,[r11+rcx*8+0x226AC]
    r8d = *reinterpret_cast<std::uint32_t*>(r11 + ecx*8 + 0x226AC);
    // 0xe825cd8  cmp r8d,8
    // 0xe825cdc  jne 0xE825E19
    if (r8d != 8) {
        goto L_0xe825e19;
    }
    // 0xe825ce2  mov rcx,[r11+0x22498]
    rcx = *reinterpret_cast<std::uint8_t**>(r11 + 0x22498);
    // 0xe825ce9  mov rax,[rcx+rax]
    rax = *reinterpret_cast<std::uint64_t*>(rcx + rax);
    // 0xe825ced  mov qword ptr [rbx+0xC0],2
    *reinterpret_cast<std::uint64_t*>(rbx + 0xC0) = 2;
    // 0xe825cf8  mov [rbx+0xC8],rax
    *reinterpret_cast<std::uint64_t*>(rbx + 0xC8) = rax;
    // 0xe825cff  mov rax,[rdx]
    rax = *reinterpret_cast<std::uint64_t*>(rdx);
    // 0xe825d02  mov rax,[rax+0xD0]
    rax = *reinterpret_cast<std::uint64_t*>(rax + 0xD0);
    // 0xe825d09  mov rcx,rdx
    rcx = rdx;
    // 0xe825d0c  mov edx,1
    edx32 = 1;
    // 0xe825d11  lea r8,[rbx+0xC0]
    r8 = rbx + 0xC0;
    // 0xe825d18  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);
    // 0xe825d1e  nop
    // 0xe825d1f  jmp 0xE825E80
    goto L_0xe825e80;

    // 0xe825d24..0xe825d69
L_0xe825d24:
    // 0xe825d24  cmp r8d,0xFFF
    // 0xe825d2b  ja 0xE825F93
    if (r8d > 0xFFF) {
        goto L_0xe825f93;
    }
    // 0xe825d31  mov r8d,ecx
    r8d = static_cast<std::uint32_t>(ecx);
    // 0xe825d34  shr r8d,6
    r8d >>= 6;
    // 0xe825d38  mov r11,[rbx+0x90]
    r11 = *reinterpret_cast<std::uint8_t**>(rbx + 0x90);
    // 0xe825d3f  mov r9,[r11+r8*8+0x224A8]
    r9 = *reinterpret_cast<std::uint8_t**>(r11 + r8*8 + 0x224A8);
    // 0xe825d47  mov r10d,1
    s.r10d = 1;
    r10 = reinterpret_cast<std::uint8_t*>(1);
    // 0xe825d4d  shl r10,cl
    r10 = reinterpret_cast<std::uint8_t*>(1ULL << (ecx & 0x3F));
    // 0xe825d50  bt r9,rcx
    // 0xe825d54  jae 0xE825F5B
    if ((reinterpret_cast<std::uintptr_t>(r9) & (1ULL << (ecx & 0x3F))) == 0) {
        goto L_0xe825f5b;
    }
    // 0xe825d5a  mov r8d,[r11+rcx*8+0x226AC]
    r8d = *reinterpret_cast<std::uint32_t*>(r11 + ecx*8 + 0x226AC);
    // 0xe825d62  cmp r8d,0xAC3
    // 0xe825d69  je 0xE825F93
    if (r8d == 0xAC3) {
        goto L_0xe825f93;
    }
    // 0xe825d6f  mov r9,[rbx+0x90]
    r9 = *reinterpret_cast<std::uint8_t**>(rbx + 0x90);
    // 0xe825d76  mov dword ptr [r9+rcx*8+0x226AC],0xAC3
    *reinterpret_cast<std::uint32_t*>(r9 + ecx*8 + 0x226AC) = 0xAC3;
    // 0xe825d82  mov rcx,[r9+0x22498]
    rcx = *reinterpret_cast<std::uint8_t**>(r9 + 0x22498);
    // 0xe825d89  mov rax,[rcx+rax]
    rax = *reinterpret_cast<std::uint64_t*>(rcx + rax);
    // 0xe825d8d  mov qword ptr [rbx+0xC0],0
    *reinterpret_cast<std::uint64_t*>(rbx + 0xC0) = 0;
    // 0xe825d98  mov [rbx+0xC8],rax
    *reinterpret_cast<std::uint64_t*>(rbx + 0xC8) = rax;
    // 0xe825d9f  mov dword ptr [rbx+0xD0],0xFFFFFFFF
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD0) = 0xFFFFFFFF;
    // 0xe825da9  mov [rbx+0xD4],r8d
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD4) = r8d;
    // 0xe825db0  mov dword ptr [rbx+0xD8],0xAC3
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD8) = 0xAC3;
    // 0xe825dba  mov rax,[rdx]
    rax = *reinterpret_cast<std::uint64_t*>(rdx);
    // 0xe825dbd  mov rax,[rax+0xD0]
    rax = *reinterpret_cast<std::uint64_t*>(rax + 0xD0);
    // 0xe825dc4  mov rcx,rdx
    rcx = rdx;
    // 0xe825dc7  mov edx,1
    edx32 = 1;
    // 0xe825dcc  lea r8,[rbx+0xC0]
    r8 = rbx + 0xC0;
    // 0xe825dd3  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);
    // 0xe825dd9  nop
    // 0xe825dda  jmp 0xE825F93
    goto L_0xe825f93;

    // 0xe825ddf..0xe825e17
L_0xe825ddf:
    // 0xe825ddf  or r9,r10
    r9 = reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(r9) | reinterpret_cast<std::uintptr_t>(r10));
    // 0xe825de2  mov [r11+r8*8+0x224A8],r9
    *reinterpret_cast<std::uint8_t**>(r11 + reinterpret_cast<std::uintptr_t>(r8)*8 + 0x224A8) = r9;
    // 0xe825dea  movzx eax,word ptr [r11+0x224A0]
    rax = *reinterpret_cast<std::uint16_t*>(r11 + 0x224A0);
    // 0xe825df2  mov [r11+rax*2+0x2A6A8],cx
    *reinterpret_cast<std::uint16_t*>(r11 + rax*2 + 0x2A6A8) = static_cast<std::uint16_t>(ecx);
    // 0xe825dfb  inc eax
    ++static_cast<std::uint32_t&>(rax);
    // 0xe825dfd  mov [r11+0x224A0],ax
    *reinterpret_cast<std::uint16_t*>(r11 + 0x224A0) = static_cast<std::uint16_t>(rax);
    // 0xe825e05  mov rax,0x800000008
    rax = 0x800000008;
    // 0xe825e0f  mov [r11+rcx*8+0x226A8],rax
    *reinterpret_cast<std::uint64_t*>(r11 + ecx*8 + 0x226A8) = rax;
    // 0xe825e17  jmp short 0xE825E80
    goto L_0xe825e80;

    // 0xe825e19..0xe825e7d
L_0xe825e19:
    // 0xe825e19  mov dword ptr [r11+rcx*8+0x226AC],8
    *reinterpret_cast<std::uint32_t*>(r11 + ecx*8 + 0x226AC) = 8;
    // 0xe825e25  mov rcx,[r11+0x22498]
    rcx = *reinterpret_cast<std::uint8_t**>(r11 + 0x22498);
    // 0xe825e2c  mov rax,[rcx+rax]
    rax = *reinterpret_cast<std::uint64_t*>(rcx + rax);
    // 0xe825e30  mov qword ptr [rbx+0xC0],0
    *reinterpret_cast<std::uint64_t*>(rbx + 0xC0) = 0;
    // 0xe825e3b  mov [rbx+0xC8],rax
    *reinterpret_cast<std::uint64_t*>(rbx + 0xC8) = rax;
    // 0xe825e42  mov dword ptr [rbx+0xD0],0xFFFFFFFF
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD0) = 0xFFFFFFFF;
    // 0xe825e4c  mov [rbx+0xD4],r8d
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD4) = r8d;
    // 0xe825e53  mov dword ptr [rbx+0xD8],8
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD8) = 8;
    // 0xe825e5d  mov rax,[rdx]
    rax = *reinterpret_cast<std::uint64_t*>(rdx);
    // 0xe825e60  mov rax,[rax+0xD0]
    rax = *reinterpret_cast<std::uint64_t*>(rax + 0xD0);
    // 0xe825e67  mov rcx,rdx
    rcx = rdx;
    // 0xe825e6a  mov edx,1
    edx32 = 1;
    // 0xe825e6f  lea r8,[rbx+0xC0]
    r8 = rbx + 0xC0;
    // 0xe825e76  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);
    // 0xe825e7c  nop
    // 0xe825e7d  nop [rax]
L_0xe825e80:
    // 0xe825e80  mov r9d,[r15+0x34]
    s.r9d = *reinterpret_cast<std::uint32_t*>(r15 + 0x34);
    r9 = reinterpret_cast<std::uint8_t*>(s.r9d);
    // 0xe825e84  cmp byte ptr [r12+0x13],1
    // 0xe825e8a  jne short 0xE825EB5
    if (*reinterpret_cast<std::uint8_t*>(r12 + 0x13) != 1) {
        goto L_0xe825eb5;
    }
    // 0xe825e8c  mov r11d,[r15+0x30]
    s.r11d = *reinterpret_cast<std::uint32_t*>(r15 + 0x30);
    r11 = reinterpret_cast<std::uint8_t*>(s.r11d);
    // 0xe825e90  mov r10d,[r15+0x44]
    s.r10d = *reinterpret_cast<std::uint32_t*>(r15 + 0x44);
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe825e94  movzx eax,byte ptr [r15+0x65]
    rax = *reinterpret_cast<std::uint8_t*>(r15 + 0x65);
    // 0xe825e99  and al,0x10
    rax &= 0x10;
    // 0xe825e9b  mov r8d,[r12+4]
    r8d = *reinterpret_cast<std::uint32_t*>(r12 + 4);
    // 0xe825ea0  cmp al,1
    // 0xe825ea2  mov cl,2
    // 0xe825ea4  sbb cl,0
    ecx = 2 - (rax != 0 ? 0 : 1);
    // 0xe825ea7  mov eax,[r15+0x60]
    rax = *reinterpret_cast<std::uint32_t*>(r15 + 0x60);
    // 0xe825eab  sub eax,r8d
    rax -= r8d;
    // 0xe825eae  shr r8d,cl
    r8d >>= (ecx & 0x1F);
    // 0xe825eb1  shr eax,cl
    rax >>= (ecx & 0x1F);
    // 0xe825eb3  jmp short 0xE825EE1
    goto L_0xe825ee1;

    // 0xe825eb5..0xe825ee1
L_0xe825eb5:
    // 0xe825eb5  movzx r10d,word ptr [r12+8]
    s.r10d = *reinterpret_cast<std::uint16_t*>(r12 + 8);
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe825ebb  test r10d,r10d
    // 0xe825ebe  jne short 0xE825EC4
    if (s.r10d == 0) {
        // 0xe825ec0  mov r10d,[r15+0x70]
        s.r10d = *reinterpret_cast<std::uint32_t*>(r15 + 0x70);
        r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    }
L_0xe825ec4:
    // 0xe825ec4  mov ecx,[r12+4]
    ecx = *reinterpret_cast<std::uint32_t*>(r12 + 4);
    // 0xe825ec9  xor r11d,r11d
    s.r11d = 0;
    r11 = nullptr;
    // 0xe825ecc  mov eax,ecx
    rax = ecx;
    // 0xe825ece  xor edx,edx
    edx32 = 0;
    // 0xe825ed0  div r10d
    if (s.r10d != 0) {
        std::uint32_t q = rax / s.r10d;
        std::uint32_t r = rax % s.r10d;
        rax = q;
        edx32 = r;
    }
    // 0xe825ed3  mov r8d,eax
    r8d = static_cast<std::uint32_t>(rax);
    // 0xe825ed6  mov eax,[r15+0x60]
    rax = *reinterpret_cast<std::uint32_t*>(r15 + 0x60);
    // 0xe825eda  sub eax,ecx
    rax -= ecx;
    // 0xe825edc  xor edx,edx
    edx32 = 0;
    // 0xe825ede  div r10d
    if (s.r10d != 0) {
        std::uint32_t q = rax / s.r10d;
        std::uint32_t r = rax % s.r10d;
        rax = q;
        edx32 = r;
    }
    // 0xe825ee1  mov ecx,r8d
    ecx = r8d;
L_0xe825ee1:
    // 0xe825ee4  mov [rbx+0xC0],r11d
    *reinterpret_cast<std::uint32_t*>(rbx + 0xC0) = s.r11d;
    // 0xe825eeb  mov [rbx+0xC4],r9d
    *reinterpret_cast<std::uint32_t*>(rbx + 0xC4) = s.r9d;
    // 0xe825ef2  mov [rbx+0xC8],rcx
    *reinterpret_cast<std::uint64_t*>(rbx + 0xC8) = ecx;
    // 0xe825ef9  mov [rbx+0xD0],eax
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD0) = static_cast<std::uint32_t>(rax);
    // 0xe825eff  mov [rbx+0xD4],r10d
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD4) = s.r10d;
    // 0xe825f06  movups xmm0,[r15+0x48]
    // xmm0 load - skipped
    // 0xe825f0b  lea rax,[rbx+0xD4]
    rax = reinterpret_cast<std::uintptr_t>(rbx + 0xD4);
    // 0xe825f12  movups [rax+4],xmm0
    // xmm0 store - skipped
    // 0xe825f16  mov rax,[0x12BB4910]
    rax = *reinterpret_cast<std::uint64_t*>(0x12BB4910);
    // 0xe825f1d  mov rcx,[rax+0x400]
    rcx = *reinterpret_cast<std::uint8_t**>(rax + 0x400);
    // 0xe825f24  mov rax,[rbx+0xB8]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0xB8);
    // 0xe825f2b  mov r8,[rax+8]
    r8 = *reinterpret_cast<std::uint8_t**>(rax + 8);
    // 0xe825f2f  mov rdx,[r15]
    rdx = *reinterpret_cast<std::uint8_t**>(r15);
    // 0xe825f32  mov rax,[rcx]
    rax = *reinterpret_cast<std::uint64_t*>(rcx);
    // 0xe825f35  mov rax,[rax+0x98]
    rax = *reinterpret_cast<std::uint64_t*>(rax + 0x98);
    // 0xe825f3c  mov r10,[0xF99FFA0]
    r10 = *reinterpret_cast<std::uint8_t**>(0xF99FFA0);
    // 0xe825f43  mov [rsp+0x20],r8
    // stack store for call
    // 0xe825f48  xor r8d,r8d
    r8d = 0;
    // 0xe825f4b  lea r9,[rbx+0xC0]
    r9 = rbx + 0xC0;
    // 0xe825f52  call r10
    using Fn_r10 = void(*)();
    reinterpret_cast<Fn_r10>(r10)();
    // 0xe825f55  nop
    // 0xe825f56  jmp 0xE826068
    goto L_0xe826068;

    // 0xe825f5b..0xe825f93
L_0xe825f5b:
    // 0xe825f5b  or r9,r10
    r9 = reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(r9) | reinterpret_cast<std::uintptr_t>(r10));
    // 0xe825f5e  mov [r11+r8*8+0x224A8],r9
    *reinterpret_cast<std::uint8_t**>(r11 + reinterpret_cast<std::uintptr_t>(r8)*8 + 0x224A8) = r9;
    // 0xe825f66  movzx eax,word ptr [r11+0x224A0]
    rax = *reinterpret_cast<std::uint16_t*>(r11 + 0x224A0);
    // 0xe825f6e  mov [r11+rax*2+0x2A6A8],cx
    *reinterpret_cast<std::uint16_t*>(r11 + rax*2 + 0x2A6A8) = static_cast<std::uint16_t>(ecx);
    // 0xe825f77  inc eax
    ++static_cast<std::uint32_t&>(rax);
    // 0xe825f79  mov [r11+0x224A0],ax
    *reinterpret_cast<std::uint16_t*>(r11 + 0x224A0) = static_cast<std::uint16_t>(rax);
    // 0xe825f81  mov rax,0xAC300000AC3
    rax = 0xAC300000AC3;
    // 0xe825f8b  mov [r11+rcx*8+0x226A8],rax
    *reinterpret_cast<std::uint64_t*>(r11 + ecx*8 + 0x226A8) = rax;

    // 0xe825f93..0xe826067
L_0xe825f93:
    // 0xe825f93  mov r10,[r15+0x28]
    r10 = *reinterpret_cast<std::uint8_t**>(r15 + 0x28);
    // 0xe825f97  cmp byte ptr [r12+0x13],1
    // 0xe825f9d  mov r8d,[r15+0x60]
    r8d = *reinterpret_cast<std::uint32_t*>(r15 + 0x60);
    // 0xe825fa1  jne short 0xE825FC9
    if (*reinterpret_cast<std::uint8_t*>(r12 + 0x13) != 1) {
        goto L_0xe825fc9;
    }
    // 0xe825fa3  mov r13d,[r15+8]
    std::uint32_t r13d_local = *reinterpret_cast<std::uint32_t*>(r15 + 8);
    // 0xe825fa7  mov r11d,[r15+0x24]
    s.r11d = *reinterpret_cast<std::uint32_t*>(r15 + 0x24);
    r11 = reinterpret_cast<std::uint8_t*>(s.r11d);
    // 0xe825fab  movzx eax,byte ptr [r15+0x65]
    rax = *reinterpret_cast<std::uint8_t*>(r15 + 0x65);
    // 0xe825fb0  and al,0x10
    rax &= 0x10;
    // 0xe825fb2  mov r9d,[r12+4]
    std::uint32_t r9d_local5 = *reinterpret_cast<std::uint32_t*>(r12 + 4);
    r9 = reinterpret_cast<std::uint8_t*>(r9d_local5);
    // 0xe825fb7  cmp al,1
    // 0xe825fb9  mov cl,2
    // 0xe825fbb  sbb cl,0
    ecx = 2 - (rax != 0 ? 0 : 1);
    // 0xe825fbe  sub r8d,r9d
    r8d -= r9d_local5;
    // 0xe825fc1  shr r9d,cl
    r9d_local5 >>= (ecx & 0x1F);
    // 0xe825fc4  shr r8d,cl
    r8d >>= (ecx & 0x1F);
    // 0xe825fc7  jmp short 0xE825FF8
    goto L_0xe825ff8;

    // 0xe825fc9..0xe825ff8
L_0xe825fc9:
    // 0xe825fc9  movzx r11d,word ptr [r12+8]
    s.r11d = *reinterpret_cast<std::uint16_t*>(r12 + 8);
    r11 = reinterpret_cast<std::uint8_t*>(s.r11d);
    // 0xe825fcf  test r11d,r11d
    // 0xe825fd2  jne short 0xE825FD8
    if (s.r11d == 0) {
        // 0xe825fd4  mov r11d,[r15+0x70]
        s.r11d = *reinterpret_cast<std::uint32_t*>(r15 + 0x70);
        r11 = reinterpret_cast<std::uint8_t*>(s.r11d);
    }
L_0xe825fd8:
    // 0xe825fd8  mov ecx,[r12+4]
    ecx = *reinterpret_cast<std::uint32_t*>(r12 + 4);
    // 0xe825fdd  xor r13d,r13d
    std::uint32_t r13d_local2 = 0;
    // 0xe825fe0  mov eax,ecx
    rax = ecx;
    // 0xe825fe2  xor edx,edx
    edx32 = 0;
    // 0xe825fe4  div r11d
    if (s.r11d != 0) {
        std::uint32_t q = rax / s.r11d;
        std::uint32_t r = rax % s.r11d;
        rax = q;
        edx32 = r;
    }
    // 0xe825fe7  mov r9d,eax
    std::uint32_t r9d_local6 = static_cast<std::uint32_t>(rax);
    // 0xe825fea  sub r8d,ecx
    r8d -= ecx;
    // 0xe825fed  mov eax,r8d
    rax = r8d;
    // 0xe825ff0  xor edx,edx
    edx32 = 0;
    // 0xe825ff2  div r11d
    if (s.r11d != 0) {
        std::uint32_t q = rax / s.r11d;
        std::uint32_t r = rax % s.r11d;
        rax = q;
        edx32 = r;
    }
    // 0xe825ff5  mov r8d,eax
    r8d = static_cast<std::uint32_t>(rax);
L_0xe825ff8:
    // 0xe825ff8  mov eax,r9d
    rax = r9d_local6;
    // 0xe825ffb  mov [rbx+0xC0],r13d
    *reinterpret_cast<std::uint32_t*>(rbx + 0xC0) = r13d_local2;
    // 0xe826002  mov ecx,[r15+0x14]
    ecx = *reinterpret_cast<std::uint32_t*>(r15 + 0x14);
    // 0xe826006  lea rdx,[rbx+0xD4]
    rdx = rbx + 0xD4;
    // 0xe82600d  mov [rdx-8],ecx
    *reinterpret_cast<std::uint32_t*>(rbx + 0xCC) = ecx;
    // 0xe826010  mov rcx,[r15+0xC]
    rcx = *reinterpret_cast<std::uint8_t**>(r15 + 0xC);
    // 0xe826014  mov [rdx-0x10],rcx
    *reinterpret_cast<std::uint64_t*>(rbx + 0xC4) = reinterpret_cast<std::uintptr_t>(rcx);
    // 0xe826018  mov [rbx+0xD0],rax
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD0) = static_cast<std::uint32_t>(rax);
    // 0xe82601f  mov [rbx+0xD8],r8d
    *reinterpret_cast<std::uint32_t*>(rbx + 0xD8) = r8d;
    // 0xe826026  mov [rbx+0xDC],r11d
    *reinterpret_cast<std::uint32_t*>(rbx + 0xDC) = s.r11d;
    // 0xe82602d  mov [rbx+0xE0],r10
    *reinterpret_cast<std::uint64_t*>(rbx + 0xE0) = reinterpret_cast<std::uintptr_t>(r10);
    // 0xe826034  mov rax,[0x12BB4910]
    rax = *reinterpret_cast<std::uint64_t*>(0x12BB4910);
    // 0xe82603b  mov rcx,[rax+0x400]
    rcx = *reinterpret_cast<std::uint8_t**>(rax + 0x400);
    // 0xe826042  mov rax,[rbx+0xB8]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0xB8);
    // 0xe826049  mov r9,[rax+8]
    r9 = *reinterpret_cast<std::uint8_t**>(rax + 8);
    // 0xe82604d  mov rdx,[r15]
    rdx = *reinterpret_cast<std::uint8_t**>(r15);
    // 0xe826050  mov rax,[rcx]
    rax = *reinterpret_cast<std::uint64_t*>(rcx);
    // 0xe826053  mov rax,[rax+0x90]
    rax = *reinterpret_cast<std::uint64_t*>(rax + 0x90);
    // 0xe82605a  lea r8,[rbx+0xC0]
    r8 = rbx + 0xC0;
    // 0xe826061  call qword ptr [0xF99FFA0]
    eea6040_call(nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);
    // 0xe826067  nop

    // 0xe826068..0xe826099
L_0xe826068:
    // 0xe826068  mov r8d,[rbx+0x110]
    r8d = *reinterpret_cast<std::uint32_t*>(rbx + 0x110);
    // 0xe82606f  mov eax,r8d
    rax = r8d;
    // 0xe826072  mov rdx,[rbx+0xB8]
    rdx = *reinterpret_cast<std::uint8_t**>(rbx + 0xB8);
    // 0xe826079  mov ecx,[rdx+0x18]
    ecx = *reinterpret_cast<std::uint32_t*>(rdx + 0x18);
    // 0xe82607c  add [rdx+8],rcx
    *reinterpret_cast<std::uint64_t*>(rdx + 8) += ecx;
    // 0xe826080  mov rcx,[rdx+0x10]
    rcx = *reinterpret_cast<std::uint8_t**>(rdx + 0x10);
    // 0xe826084  mov [r14+rax*8],rcx
    *reinterpret_cast<std::uint64_t*>(r14 + rax*8) = reinterpret_cast<std::uintptr_t>(rcx);
    // 0xe826088  mov eax,[rdx+0x18]
    rax = *reinterpret_cast<std::uint32_t*>(rdx + 0x18);
    // 0xe82608b  add rax,rcx
    rax += reinterpret_cast<std::uintptr_t>(rcx);
    // 0xe82608e  mov [rdx+0x10],rax
    *reinterpret_cast<std::uint64_t*>(rdx + 0x10) = rax;
    // 0xe826092  mov r9,[rbx+0xB0]
    r9 = *reinterpret_cast<std::uint8_t**>(rbx + 0xB0);
    // 0xe826099  jmp 0xE825C3A
    goto L_0xe825c3a_exit;

    // 0xe82609e..0xe8260d3
    // 0xe82609e  test byte ptr [0x12ADFA53],0x80
    // 0xe8260a5  jne 0xE82735A
    if ((*reinterpret_cast<std::uint8_t*>(0x12ADFA53) & 0x80) != 0) {
        goto L_0xe82735a_exit;
    }
    // 0xe8260ab  mov rcx,[rbx+0x220]
    rcx = *reinterpret_cast<std::uint8_t**>(rbx + 0x220);
    // 0xe8260b2  mov r8,[rbx+0xB8]
    r8 = *reinterpret_cast<std::uint8_t**>(rbx + 0xB8);
    // 0xe8260b9  mov eax,[r8+0x18]
    rax = *reinterpret_cast<std::uint32_t*>(r8 + 0x18);
    // 0xe8260bd  add [r8+8],rax
    *reinterpret_cast<std::uint64_t*>(r8 + 8) += rax;
    // 0xe8260c1  mov r10d,[rbx+0x110]
    s.r10d = *reinterpret_cast<std::uint32_t*>(rbx + 0x110);
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe8260c8  mov edx,r10d
    edx32 = s.r10d;
    // 0xe8260cb  mov rax,[r8+0x10]
    rax = *reinterpret_cast<std::uint64_t*>(r8 + 0x10);
    // 0xe8260cf  mov [rcx+rdx*8],rax
    *reinterpret_cast<std::uint64_t*>(rcx + edx32*8) = rax;
    // 0xe8260d3  jmp 0xE8273C4
    goto L_0xe8273c4_exit;

    // 0xe8260d8..0xe82625f
    // 0xe8260d8  mov rax,[rbx+0x140]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0x140);
    // 0xe8260df  test rax,rax
    // 0xe8260e2  je 0xE8270E2
    if (rax == 0) {
        goto L_0xe8270e2_exit;
    }
    // 0xe8260e8  mov r11,[rbx+0x130]
    r11 = *reinterpret_cast<std::uint8_t**>(rbx + 0x130);
    // 0xe8260ef  shl r11,4
    r11 = reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(r11) << 4);
    // 0xe8260f3  add r11,rax
    r11 += rax;
    // 0xe8260f6  xor ecx,ecx
    ecx = 0;
    // 0xe8260f8  mov r10d,[rbx+0x110]
    s.r10d = *reinterpret_cast<std::uint32_t*>(rbx + 0x110);
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe8260ff  mov [rbx+0x1C0],r11
    *reinterpret_cast<std::uint64_t*>(rbx + 0x1C0) = reinterpret_cast<std::uintptr_t>(r11);
    // 0xe826106  jmp short 0xE82614E
    goto L_0xe82614e;

    // 0xe826110..0xe82614e (loop body)
L_0xe826110:
    // 0xe826110  mov rcx,[rbx+0x220]
    rcx = *reinterpret_cast<std::uint8_t**>(rbx + 0x220);
    // 0xe826117  mov r8,[rbx+0xB8]
    r8 = *reinterpret_cast<std::uint8_t**>(rbx + 0xB8);
    // 0xe82611e  mov eax,[r8+0x18]
    rax = *reinterpret_cast<std::uint32_t*>(r8 + 0x18);
    // 0xe826122  add [r8+8],rax
    *reinterpret_cast<std::uint64_t*>(r8 + 8) += rax;
    // 0xe826126  mov edx,r10d
    edx32 = s.r10d;
    // 0xe826129  mov rax,[r8+0x10]
    rax = *reinterpret_cast<std::uint64_t*>(r8 + 0x10);
    // 0xe82612d  mov [rcx+rdx*8],rax
    *reinterpret_cast<std::uint64_t*>(rcx + edx32*8) = rax;
    // 0xe826131  mov ecx,[r8+0x18]
    ecx = *reinterpret_cast<std::uint32_t*>(r8 + 0x18);
    // 0xe826135  add rcx,rax
    rcx += rax;
    // 0xe826138  mov [r8+0x10],rcx
    *reinterpret_cast<std::uint64_t*>(r8 + 0x10) = reinterpret_cast<std::uintptr_t>(rcx);
    // 0xe82613c  inc r10d
    ++s.r10d;
    r10 = reinterpret_cast<std::uint8_t*>(s.r10d);
    // 0xe82613f  mov ecx,[rbx+0x150]
    ecx = *reinterpret_cast<std::uint32_t*>(rbx + 0x150);
    // 0xe826145  inc ecx
    ++ecx;
    // 0xe826147  mov r9,[rbx+0xB0]
    r9 = *reinterpret_cast<std::uint8_t**>(rbx + 0xB0);
L_0xe82614e:
    // 0xe82614e  mov eax,ecx
    rax = ecx;
    // 0xe826150  cmp [r11+8],rax
    // 0xe826154  jbe 0xE8273D2
    if (*reinterpret_cast<std::uint64_t*>(r11 + 8) <= rax) {
        goto L_0xe8273d2_exit;
    }
    // 0xe82615a  mov [rbx+0x150],ecx
    *reinterpret_cast<std::uint32_t*>(rbx + 0x150) = ecx;
    // 0xe826160  mov r15,[r11]
    r15 = *reinterpret_cast<std::uint8_t**>(r11);
    // 0xe826163  test r15,r15
    // 0xe826166  je short 0xE826110
    if (r15 == nullptr) {
        goto L_0xe826110;
    }
    // 0xe826168  lea r12,[rax+rax*4]
    r12 = reinterpret_cast<std::uint8_t*>(rax * 5);
    // 0xe82616c  movzx r13d,word ptr [r15+r12*4+0xA]
    std::uint32_t r13d_local3 = *reinterpret_cast<std::uint16_t*>(r15 + reinterpret_cast<std::uintptr_t>(r12)*4 + 0xA);
    // 0xe826172  cmp r13,0x1000
    // 0xe826179  setae dl
    // 0xe82617c  mov rax,[rbx+0xB0]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0xB0);
    // 0xe826183  movzx ecx,byte ptr [rax+0xC96190]
    ecx = *reinterpret_cast<std::uint8_t*>(rax + 0xC96190);
    // 0xe82618a  mov al,1
    rax = 1;
    // 0xe82618c  test dl,cl
    // 0xe82618e  mov [rbx+0x110],r10d
    *reinterpret_cast<std::uint32_t*>(rbx + 0x110) = s.r10d;
    // 0xe826195  jne 0xE8262F5
    if ((ecx & 1) != 0) {
        goto L_0xe8262f5_exit;
    }
    // 0xe82619b  mov rax,[rbx+0xB0]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0xB0);
    // 0xe8261a2  mov rax,[rax+0xC96180]
    rax = *reinterpret_cast<std::uint64_t*>(rax + 0xC96180);
    // 0xe8261a9  shr rax,3
    rax >>= 3;
    // 0xe8261ad  mov rdx,0x1642C8590B21642D
    rdx = reinterpret_cast<std::uint8_t*>(0x1642C8590B21642D);
    // 0xe8261b7  mul rdx
    rax = rax * reinterpret_cast<std::uintptr_t>(rdx);
    // 0xe8261ba  shr rdx,1
    rdx = reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(rdx) >> 1);
    // 0xe8261bd  mov eax,ecx
    rax = ecx;
    // 0xe8261bf  cmp rdx,r13
    // 0xe8261c2  ja 0xE8262F5
    if (reinterpret_cast<std::uintptr_t>(rdx) > r13d_local3) {
        goto L_0xe8262f5_exit;
    }
    // 0xe8261c8  mov esi,r13d
    esi = r13d_local3;
    // 0xe8261cb  and esi,0xF000
    esi &= 0xF000;
    // 0xe8261d1  add rsi,0x1000
    rsi = reinterpret_cast<std::uint8_t*>(esi + 0x1000);
    // 0xe8261d8  mov rcx,[rbx+0x1F8]
    rcx = *reinterpret_cast<std::uint8_t**>(rbx + 0x1F8);
    // 0xe8261df  mov rdx,rsi
    rdx = rsi;
    // 0xe8261e2  call 0xE83ACE0
    sub_e83ace0(reinterpret_cast<void*>(rcx), reinterpret_cast<std::uint64_t>(rsi));
    // 0xe8261e7  nop
    // 0xe8261e8  mov rax,[rbx+0xB0]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0xB0);
    // 0xe8261ef  mov rax,[rax+0xC96180]
    rax = *reinterpret_cast<std::uint64_t*>(rax + 0xC96180);
    // 0xe8261f6  shr rax,3
    rax >>= 3;
    // 0xe8261fa  mov rcx,0x1642C8590B21642D
    rcx = reinterpret_cast<std::uint8_t*>(0x1642C8590B21642D);
    // 0xe826204  mul rcx
    rax = rax * reinterpret_cast<std::uintptr_t>(rcx);
    // 0xe826207  mov rdi,rdx
    rdi = rdx;
    // 0xe82620a  shr rdi,1
    rdi = reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(rdi) >> 1);
    // 0xe82620d  cmp rdi,rsi
    // 0xe826210  jae 0xE8262D9
    if (reinterpret_cast<std::uintptr_t>(rdi) >= reinterpret_cast<std::uintptr_t>(rsi)) {
        goto L_0xe8262d9_exit;
    }
    // 0xe826216  nop [rax+rax]
    // 0xe826220  imul r14,rdi,0xB8
    r14 = reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(rdi) * 0xB8);
    // 0xe826227  cmp rdi,0xFFF
    // 0xe82622e  ja short 0xE826240
    if (reinterpret_cast<std::uintptr_t>(rdi) > 0xFFF) {
        goto L_0xe826240;
    }
    // 0xe826230  add r14,[rbx+0x1F8]
    r14 += *reinterpret_cast<std::uint64_t*>(rbx + 0x1F8);
    // 0xe826237  jmp short 0xE82628A
    goto L_0xe82628a_exit;
    // 0xe826239  nop [rax]
L_0xe826240:
    // 0xe826240  add r14,0xFFFFFFFFFFF48000
    r14 = reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(r14) + 0xFFFFFFFFFFF48000);
    // 0xe826247  mov rax,[rbx+0xB0]
    rax = *reinterpret_cast<std::uint64_t*>(rbx + 0xB0);
    // 0xe82624e  mov rax,[rax+0xC96178]
    rax = *reinterpret_cast<std::uint64_t*>(rax + 0xC96178);
    // 0xe826255  mov rax,[rax]
    rax = *reinterpret_cast<std::uint64_t*>(rax);
    // 0xe826258  cmp r14,0xB8000
    // 0xe82625f  jb short 0xE826287
    if (reinterpret_cast<std::uintptr_t>(r14) < 0xB8000) {
        goto L_0xe826287_exit;
    }
    // 0xe826261 is end of range (exclusive)
    // last instruction 0xe82625c jmp 0xE82306E already covered by branch above

L_0xe823066_exit:
L_0xe82306e_exit:
L_0xe82d4c4_exit:
L_0xe827c85_exit:
L_0xe8270e2_exit:
L_0xe827a11_exit:
L_0xe82733c_exit:
L_0xe82735a_exit:
L_0xe8273c4_exit:
L_0xe8273d2_exit:
L_0xe8262f5_exit:
L_0xe8262d9_exit:
L_0xe82628a_exit:
L_0xe826287_exit:
    // 0xe82625c  jmp 0xE82306E
    // final exit from chunk
    goto L_0xe82306e_exit;

    // Write back state
    s.rbx = reinterpret_cast<std::uintptr_t>(rbx);
    s.rdi = reinterpret_cast<std::uintptr_t>(rdi);
    s.rsi = reinterpret_cast<std::uintptr_t>(rsi);
    s.rdx = reinterpret_cast<std::uintptr_t>(rdx);
    s.rcx = reinterpret_cast<std::uintptr_t>(rcx);
    s.r9 = reinterpret_cast<std::uintptr_t>(r9);
    s.r10 = reinterpret_cast<std::uintptr_t>(r10);
    s.r11 = reinterpret_cast<std::uintptr_t>(r11);
    s.r12 = reinterpret_cast<std::uintptr_t>(r12);
    s.r13 = reinterpret_cast<std::uintptr_t>(r13);
    s.r14 = reinterpret_cast<std::uintptr_t>(r14);
    s.r15 = reinterpret_cast<std::uintptr_t>(r15);
    s.eax = static_cast<std::uint32_t>(rax);
    s.ecx = ecx;
    s.edx = edx32;

    // Call quotes (verbatim)
#if 0
    0xe824a73  call 0xE82DCC0
    0xe824c35  call qword ptr [0xF99FFA0]
    0xe824cf0  call qword ptr [0xF99FFA0]
    0xe824d93  call qword ptr [0xF99FFA0]
    0xe824e72  call r10
    0xe824f81  call qword ptr [0xF99FFA0]
    0xe8250c2  call 0xE82D960
    0xe8250fb  call 0xEBCE390
    0xe825162  call r10
    0xe825174  call 0xE82DCC0
    0xe825260  call r10
    0xe8252c4  call qword ptr [0xF99FFA0]
    0xe82533b  call 0xEBD1560
    0xe825369  call 0xE82D960
    0xe8253a6  call 0xEBCE390
    0xe82548c  call qword ptr [0xF99FFA0]
    0xe82553a  call qword ptr [0xF99FFA0]
    0xe825596  call qword ptr [0xF99FFA0]
    0xe825688  call qword ptr [0xF99FFA0]
    0xe825762  call r10
    0xe8258ad  call qword ptr [0xF99FFA0]
    0xe825910  call 0xE820500
    0xe825954  call qword ptr [0xF99FFA0]
    0xe825986  call qword ptr [0xF99FFA0]
    0xe8259aa  call qword ptr [0xF99FFA0]
    0xe8259d7  call 0xE82DE90
    0xe825a0f  call 0xE935700
    0xe825a39  call 0xE835B50
    0xe825a55  call 0xEEC6ED0
    0xe825b62  call 0xE82DCC0
    0xe825d18  call qword ptr [0xF99FFA0]
    0xe825dd3  call qword ptr [0xF99FFA0]
    0xe825e76  call qword ptr [0xF99FFA0]
    0xe825f52  call r10
    0xe826061  call qword ptr [0xF99FFA0]
    0xe8261e2  call 0xE83ACE0
#endif

    s.r8d = r8d;
}

// static_assert for state struct
static_assert(sizeof(ChunkState_e82326d_c01) > 0, "ChunkState_e82326d_c01 defined");

// LIFT_FN registration
// LIFT_FN(sub_e82326d, "sub_e82326d c01 chunk", 0xe82326d, sub_e82326d_chunk_c01, nullptr);

} // namespace native::d3d12
