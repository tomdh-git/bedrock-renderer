// LIFT 0xbc735b0 size 0x1b2 1.26.62.01 sub_bc735b0
// 0xbc736c6  call 0xEBCE5E0
// 0xbc736f4  call 0xEBCE5E0
// 0xbc7373c  call 0xEBCE5E0
// 0xbc7375b  call 0xBC76330
#include "sub_bc735b0.h"
#include <cstdint>

static_assert(0x0 == 0x0);
static_assert(0x8 == 0x8);
static_assert(0x10 == 0x10);

extern "C" int sub_ebce5e0(char* s, int n);

namespace native::bgfx {

void sub_bc735b0(std::int32_t cx, std::uint8_t dl, std::uint16_t r8w, std::int32_t r9d, std::uint32_t stackFlags, void* errSlot) {
    // 0xbc735b0  push rsi
    // 0xbc735b1  push rdi
    // 0xbc736c6  call 0xEBCE5E0
    // 0xbc736f4  call 0xEBCE5E0
    // 0xbc7373c  call 0xEBCE5E0
    // 0xbc7375b  call 0xBC76330
    // 0xbc735b2  sub rsp,0x38
    // 0xbc735b6  mov eax,edx
    // 0xbc735b8  xor al,1
    // 0xbc735ba  mov rsi,[rsp+0x78]
    // 0xbc735bf  cmp cx,2
    // 0xbc735c3  setb r10b
    // 0xbc735c7  or r10b,al
    // 0xbc735ca  jne short 0xBC735D8
    char* msg = nullptr;
    char* rdi = nullptr;
    if (cx >= 2 && dl == 1) {
        // 0xbc735cc  lea rdi,[0xF806679]
        // 0xbc735d3  jmp 0xBC736BE
        rdi = reinterpret_cast<char*>(0xF806679);
        goto finish;
    }

    // 0xbc735d8..0xbc735f3
    // 0xbc735d8  cmp cx,2
    // 0xbc735dc  jb short 0xBC735F3
    // 0xbc735de  test byte ptr [0x12ADFA52],1
    // 0xbc735e5  jne short 0xBC735F3
    // 0xbc735e7  lea rdi,[0xF7F5BA8]
    // 0xbc735ee  jmp 0xBC736BE
    if (!(cx < 2)) {
        if ((reinterpret_cast<volatile std::uint8_t*>(0x12ADFA52)[0] & 1) == 0) {
            rdi = reinterpret_cast<char*>(0xF7F5BA8);
            goto finish;
        }
    }

    // 0xbc735f3..0xbc73616
    // 0xbc735f3  mov eax,[rsp+0x70]
    // 0xbc735f7  test eax,0xF000
    // 0xbc735fc  je short 0xBC73616
    // 0xbc735fe  mov r10d,eax
    // 0xbc73601  and r10d,0x800000
    // 0xbc73608  je short 0xBC73616
    // 0xbc7360a  lea rdi,[0xF80273C]
    // 0xbc73611  jmp 0xBC736BE
    {
        std::uint32_t eax = stackFlags;
        if ((eax & 0xF000) && (eax & 0x800000)) {
            rdi = reinterpret_cast<char*>(0xF80273C);
            goto finish;
        }
    }

    // 0xbc73616..0xbc73632
    // 0xbc73616  cmp r8w,2
    // 0xbc7361b  jb short 0xBC73632
    // 0xbc7361d  test byte ptr [0x12ADFA51],0x80
    // 0xbc73624  jne short 0xBC73632
    // 0xbc73626  lea rdi,[0xF7F5B33]
    // 0xbc7362d  jmp 0xBC736BE
    if (!(r8w < 2)) {
        if ((reinterpret_cast<volatile std::uint8_t*>(0x12ADFA51)[0] & 0x80) == 0) {
            rdi = reinterpret_cast<char*>(0xF7F5B33);
            goto finish;
        }
    }

    // 0xbc73632..0xbc73681
    // 0xbc73632  cmp cx,2
    // 0xbc73636  movsxd rcx,r9d
    // 0xbc73639  lea r8,[0x12ADF818]
    // 0xbc73640  movzx ecx,word ptr [r8+rcx*2+0x15AC]
    // 0xbc73649  mov r8d,0x10
    // 0xbc7364f  mov r9d,2
    // 0xbc73655  cmovae r9,r8
    // 0xbc73659  mov r8d,0x38
    // 0xbc7365f  mov r10d,7
    // 0xbc73665  cmovae r10d,r8d
    // 0xbc73669  test dl,dl
    // 0xbc7366b  mov edx,0x80
    // 0xbc73670  cmove rdx,r9
    // 0xbc73674  mov r8d,0x1C0
    // 0xbc7367a  cmove r8d,r10d
    // 0xbc7367e  and r8d,ecx
    std::uint32_t ecx = *reinterpret_cast<std::uint16_t*>(0x12ADF818 + static_cast<std::int64_t>(r9d) * 2 + 0x15AC);
    std::uint64_t r9v = (cx >= 2) ? 0x10u : 2u;
    std::uint32_t r10v = (cx >= 2) ? 0x38u : 7u;
    std::uint64_t edxv = (dl == 0) ? r9v : 0x80u;
    std::uint32_t r8v = (dl == 0) ? r10v : 0x1C0u;
    r8v &= ecx;

    // 0xbc73681..0xbc7369e
    // 0xbc73681  test eax,0xF000
    // 0xbc73686  je short 0xBC7369E
    // 0xbc73688  test r8d,r8d
    // 0xbc7368b  je short 0xBC7369E
    // 0xbc7368d  test ecx,0x800
    // 0xbc73693  jne short 0xBC736A3
    // 0xbc73695  lea rdi,[0xF7EFB38]
    // 0xbc7369c  jmp short 0xBC736BE
    if ((stackFlags & 0xF000) && r8v && !(ecx & 0x800)) {
        rdi = reinterpret_cast<char*>(0xF7EFB38);
        goto finish;
    }

    // 0xbc7369e..0xbc736a3
    // 0xbc7369e  test r8d,r8d
    // 0xbc736a1  je short 0xBC73695
    if (r8v == 0) {
        rdi = reinterpret_cast<char*>(0xF7EFB38);
        goto finish;
    }

    // 0xbc736a3..0xbc736b7
    // 0xbc736a3  test eax,0x800
    // 0xbc736a8  sete r8b
    // 0xbc736ac  shr ecx,0xD
    // 0xbc736af  and ecx,1
    // 0xbc736b2  or cl,r8b
    // 0xbc736b5  jne short 0xBC7370A
    // 0xbc736b7  lea rdi,[0xF80C0B2]
    {
        std::uint32_t eax = stackFlags;
        std::uint8_t r8b = ((eax & 0x800) == 0) ? 1 : 0;
        std::uint8_t cl = static_cast<std::uint8_t>((ecx >> 13) & 1);
        if (((cl | r8b) & 1) == 0) {
            rdi = reinterpret_cast<char*>(0xF80C0B2);
            goto finish;
        }

        // 0xbc7370a..0xbc73760
        // 0xbc7370a  test eax,0x200000
        // 0xbc7370f  je short 0xBC73703
        // 0xbc73711  test [0x12ADFA50],edx
        // 0xbc73717  jne short 0xBC73703
        // 0xbc73719  lea rax,[0xF847A07]
        // 0xbc73720  mov [rsp+0x28],rax
        // 0xbc73725  mov dword ptr [rsp+0x30],0
        // 0xbc7372d  lea rdi,[0xF80C07A]
        // 0xbc73734  mov rcx,rdi
        // 0xbc73737  mov edx,0x7FFFFFFF
        // 0xbc7373c  call 0xEBCE5E0                                ; -> sub_ebce5e0
        // 0xbc73741  test eax,eax
        // 0xbc73743  je short 0xBC7374E
        // 0xbc73745  mov [rsp+0x30],eax
        // 0xbc73749  mov [rsp+0x28],rdi
        // 0xbc7374e  lea r8,[rsp+0x28]
        // 0xbc73753  mov rcx,rsi
        // 0xbc73756  mov edx,0x1006762
        // 0xbc7375b  call 0xBC76330                                ; -> sub_bc76330
        // 0xbc73760  jmp short 0xBC73703
        if ((eax & 0x200000) && (reinterpret_cast<volatile std::uint8_t*>(0x12ADFA50)[0] & static_cast<std::uint8_t>(edxv)) == 0) {
            struct Slot { char* p; std::int32_t n; };
            Slot slot;
            slot.p = reinterpret_cast<char*>(0xF847A07);
            slot.n = 0;
            rdi = reinterpret_cast<char*>(0xF80C07A);
            std::int32_t len = sub_ebce5e0(rdi, 0x7FFFFFFF);
            if (len != 0) {
                slot.n = len;
                slot.p = rdi;
            }
            sub_bc76330(errSlot, 0x1006762, &slot);
            goto done_return;
        }
    }

finish:
    // 0xbc736be..0xbc73703
    // 0xbc736be  mov rcx,rdi
    // 0xbc736c1  mov edx,0x7FFFFFFF
    // 0xbc736c6  call 0xEBCE5E0                                ; -> sub_ebce5e0
    // 0xbc736cb  test eax,eax
    // 0xbc736cd  lea rcx,[0xF847A07]
    // 0xbc736d4  cmove rdi,rcx
    // 0xbc736d8  cmp dword ptr [rsi+0x10],0
    // 0xbc736dc  jne short 0xBC73703
    // 0xbc736de  mov dword ptr [rsi+0x10],0x1006762
    // 0xbc736e5  mov [rsi],rcx
    // 0xbc736e8  mov dword ptr [rsi+8],0
    // 0xbc736ef  mov rcx,rdi
    // 0xbc736f2  mov edx,eax
    // 0xbc736f4  call 0xEBCE5E0                                ; -> sub_ebce5e0
    // 0xbc736f9  test eax,eax
    // 0xbc736fb  je short 0xBC73703
    // 0xbc736fd  mov [rsi+8],eax
    // 0xbc73700  mov [rsi],rdi
    {
        std::uint32_t a = static_cast<std::uint32_t>(sub_ebce5e0(rdi, 0x7FFFFFFF));
        char* rcx = reinterpret_cast<char*>(0xF847A07);
        if (a == 0) {
            rdi = rcx;
        }
        std::uint8_t* slot = reinterpret_cast<std::uint8_t*>(errSlot);
        if (*reinterpret_cast<std::uint32_t*>(slot + 0x10) == 0) {
            *reinterpret_cast<std::uint32_t*>(slot + 0x10) = 0x1006762;
            *reinterpret_cast<char**>(slot + 0x0) = rcx;
            *reinterpret_cast<std::uint32_t*>(slot + 0x8) = 0;
            std::uint32_t b = static_cast<std::uint32_t>(sub_ebce5e0(rdi, static_cast<std::int32_t>(a)));
            if (b != 0) {
                *reinterpret_cast<std::uint32_t*>(slot + 0x8) = b;
                *reinterpret_cast<char**>(slot + 0x0) = rdi;
            }
        }
    }

done_return:
    // 0xbc73703  add rsp,0x38
    // 0xbc73707  pop rdi
    // 0xbc73708  pop rsi
    // 0xbc73709  ret
    return;
}

LIFT_FN(sub_bc735b0, "sub_bc735b0", 0xbc735b0, sub_bc735b0, nullptr);

} // namespace native::bgfx