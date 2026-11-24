// LIFT 0xbc2e890 size 0x1de 1.26.62.01 sub_bc2e890
#include "client/features/render/native/bgfx/sub_bc2e890.h"

#include <cstring>

namespace native::bgfx {

// Moves one render object out of another, field by field, clearing the source fields
// it consumes. Exact x64 ABI: rcx = dest (a0), rdx = src (a1), returns rax.
// Calls two lift callees, forward-declared in the header (namespace native);
// each callee is lifted by its own unit:
//   0xbc2e99b  call 0xE869FF0  sub_e869ff0(dest + 0x98, src + 0x98)    ; -> sub_e869ff0  [0xE869FF0..0xE86A0C1, size 0xD1]
//   0xbc2e9cc  call 0x5669770 sub_5669770(dest + 0x118, src + 0x118)   ; -> sub_5669770  [0x5669770..0x5669ADA, size 0x36A]
// Both return values are unused at the call sites (rax is redefined before any use).

uint64_t sub_bc2e890(Bc2e890Object* dest, Bc2e890Object* src) {
    // 0xbc2e890..0xbc2e8a6: prologue; dest = rcx (held in r10), src = rdx (held in rsi);
    // [rbp] = -2 is a dead store to stack slot [rbp], never read again.
    //   0xbc2e890  push rbp
    //   0xbc2e891  push rsi
    //   0xbc2e892  sub rsp,0x38
    //   0xbc2e896  lea rbp,[rsp+0x30]
    //   0xbc2e89b  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
    //   0xbc2e8a3  mov rsi,rdx
    //   0xbc2e8a6  mov r10,rcx
    [[maybe_unused]] const uint64_t _sentinel = 0xFFFFFFFFFFFFFFFEull;
    (void)_sentinel;

    // 0xbc2e8a9..0xbc2e8c6: header copy dest+0x00..0x18 from src. dest+0x08..0x18 is
    // zeroed first, then [0x08,0x10) and [0x10,0x18) are overwritten from src; src+0x08..0x18
    // is then zeroed (16-byte store covers src->f10 too).
    //   0xbc2e8a9  mov rax,[rdx]
    //   0xbc2e8ac  mov [rcx],rax
    //   0xbc2e8af  xorps xmm0,xmm0
    //   0xbc2e8b2  movups [rcx+8],xmm0
    //   0xbc2e8b6  mov rax,[rdx+8]
    //   0xbc2e8ba  mov [rcx+8],rax
    //   0xbc2e8be  mov rax,[rdx+0x10]
    //   0xbc2e8c2  mov [rcx+0x10],rax
    //   0xbc2e8c6  movups [rdx+8],xmm0
    dest->f00 = src->f00;                                 // 0xbc2e8a9  mov rax,[rdx] / 0xbc2e8ac  mov [rcx],rax
    std::memset(&dest->f08, 0, 16);                       // 0xbc2e8b2  movups [rcx+8],xmm0   (16 bytes: 0x08..0x18)
    dest->f08 = src->f08;                                 // 0xbc2e8b6  mov rax,[rdx+8] / 0xbc2e8ba  mov [rcx+8],rax
    dest->f10 = src->f10;                                 // 0xbc2e8be  mov rax,[rdx+0x10] / 0xbc2e8c2  mov [rcx+0x10],rax
    std::memset(&src->f08, 0, 16);                        // 0xbc2e8c6  movups [rdx+8],xmm0   (16 bytes: 0x08..0x18)

    // 0xbc2e8ca..0xbc2e8ce: dest+0x18..0x28 = 0; dest+0x28 = 0.
    //   0xbc2e8ca  movups [rcx+0x18],xmm0
    //   0xbc2e8ce  mov qword ptr [rcx+0x28],0
    std::memset(&dest->f18, 0, 16);                       // 0xbc2e8ca  movups [rcx+0x18],xmm0   (16 bytes: 0x18..0x28)
    dest->f28 = 0;                                        // 0xbc2e8ce  mov qword ptr [rcx+0x28],0

    // 0xbc2e8d6..0xbc2e8fd: dest+0x30 = src+0x30; then src+0x38..0x48 and
    // src+0x48..0x58 are read BEFORE src+0x40 and src+0x48 are zeroed; the saved
    // values are written to dest afterwards.
    //   0xbc2e8d6  movzx eax,byte ptr [rdx+0x30]
    //   0xbc2e8da  mov [rcx+0x30],al
    //   0xbc2e8dd  movups xmm1,[rdx+0x38]
    //   0xbc2e8e1  movups xmm2,[rdx+0x48]
    //   0xbc2e8e5  mov qword ptr [rdx+0x40],0
    //   0xbc2e8ed  movups [rdx+0x48],xmm0
    //   0xbc2e8f1  movups [rcx+0x38],xmm1
    //   0xbc2e8f5  movups [rcx+0x48],xmm2
    //   0xbc2e8f9  mov rax,[rdx+0x58]
    //   0xbc2e8fd  mov [rcx+0x58],rax
    dest->f30 = src->f30;                                 // 0xbc2e8d6  movzx eax,byte ptr [rdx+0x30] / 0xbc2e8da  mov [rcx+0x30],al
    {
        std::byte saved38[16];
        std::byte saved48[16];
        std::memcpy(saved38, &src->f38, 16);              // 0xbc2e8dd  movups xmm1,[rdx+0x38]
        std::memcpy(saved48, &src->f48, 16);              // 0xbc2e8e1  movups xmm2,[rdx+0x48]
        std::memset(&src->f40, 0, 8);                     // 0xbc2e8e5  mov qword ptr [rdx+0x40],0
        std::memset(&src->f48, 0, 16);                    // 0xbc2e8ed  movups [rdx+0x48],xmm0
        std::memcpy(&dest->f38, saved38, 16);             // 0xbc2e8f1  movups [rcx+0x38],xmm1
        std::memcpy(&dest->f48, saved48, 16);             // 0xbc2e8f5  movups [rcx+0x48],xmm2
    }
    dest->f58 = src->f58;                                 // 0xbc2e8f9  mov rax,[rdx+0x58] / 0xbc2e8fd  mov [rcx+0x58],rax

    // 0xbc2e901..0xbc2e90d: dest+0x70 = 0xFF; switch value v = src+0x70; values > 3
    // jump to 0xbc2e95c and skip the case block, so dest+0x70 keeps 0xFF there.
    //   0xbc2e901  mov byte ptr [rcx+0x70],0xFF
    //   0xbc2e905  movzx eax,byte ptr [rdx+0x70]
    //   0xbc2e909  cmp rax,3
    //   0xbc2e90d  ja short 0xBC2E95C
    dest->f70 = 0xFF;                                     // 0xbc2e901  mov byte ptr [rcx+0x70],0xFF
    const uint8_t v = src->f70;                           // 0xbc2e905  movzx eax,byte ptr [rdx+0x70]

    if (v <= 3) {                                         // 0xbc2e909  cmp rax,3 / 0xbc2e90d  ja short 0xBC2E95C
        // Jump table data_f440da0 (4 int32 entries relative to table base; raw bytes
        // b8 db 7e fc 88 db 7e fc 90 db 7e fc 98 db 7e fc):
        //   0 -> 0xbc2e958, 1 -> 0xbc2e928, 2 -> 0xbc2e930, 3 -> 0xbc2e938
        //   0xbc2e90f  lea rcx,[r10+0x60]
        //   0xbc2e913  lea rdx,[rsi+0x60]
        //   0xbc2e917  lea r8,[0xF440DA0]
        //   0xbc2e91e  movsxd r9,[r8+rax*4]
        //   0xbc2e922  add r9,r8
        //   0xbc2e925  jmp r9
        switch (v) {
        case 0:                                           // 0xbc2e958 (table entry 0): +0x60/+0x68 untouched
            break;
        case 1:                                           // 0xbc2e928..0xbc2e92e: u64 copy +0x60
            //   0xbc2e928  mov rdx,[rdx]
            //   0xbc2e92b  mov [rcx],rdx
            dest->f60 = src->f60;
            break;
        case 2:                                           // 0xbc2e930..0xbc2e936: 16-byte copy +0x60
            //   0xbc2e930  movups xmm0,[rdx]
            //   0xbc2e933  movups [rcx],xmm0
            std::memcpy(&dest->f60, &src->f60, 16);
            break;
        case 3: {                                         // 0xbc2e938..0xbc2e954: dest+0x60..0x70 = 0, refcount, pointer move
            //   0xbc2e938  movups [rcx],xmm0    (xmm0 == 0 from 0xbc2e8af; 16 bytes: 0x60..0x70)
            //   0xbc2e93b  mov rcx,[rsi+0x68]
            //   0xbc2e93f  test rcx,rcx
            //   0xbc2e942  je short 0xBC2E948
            //   0xbc2e944  lock inc dword ptr [rcx+8]
            // loc_bc2e948:
            //   0xbc2e948  mov rcx,[rsi+0x60]
            //   0xbc2e94c  mov [r10+0x60],rcx
            //   0xbc2e950  mov rcx,[rsi+0x68]
            //   0xbc2e954  mov [r10+0x68],rcx
            dest->f60 = 0;                                // 0xbc2e938  movups [rcx],xmm0   (part of 16-byte store 0x60..0x70)
            dest->f68 = 0;                                // 0xbc2e938  movups [rcx],xmm0   (same store)
            const uintptr_t p = src->f68;                 // 0xbc2e93b  mov rcx,[rsi+0x68]
            if (p != 0) {                                 // 0xbc2e93f  test rcx,rcx / 0xbc2e942  je short 0xBC2E948
                ++*reinterpret_cast<uint32_t*>(p + 8);    // 0xbc2e944  lock inc dword ptr [rcx+8]
            }
            dest->f60 = src->f60;                         // 0xbc2e948  mov rcx,[rsi+0x60] / 0xbc2e94c  mov [r10+0x60],rcx
            dest->f68 = src->f68;                         // 0xbc2e950  mov rcx,[rsi+0x68] / 0xbc2e954  mov [r10+0x68],rcx
            break;
        }
        // 0xbc2e958  mov [r10+0x70],al  (common tail of cases 0..3; not reached on default)
        dest->f70 = v;                                    // 0xbc2e958  mov [r10+0x70],al
    }

    // 0xbc2e95c..0xbc2e960: dead store &dest+0x38 to stack slot [rbp-0x10],
    // never read again.
    //   0xbc2e95c  lea rax,[r10+0x38]
    //   0xbc2e960  mov [rbp-0x10],rax
    [[maybe_unused]] auto* const _slot38 = &dest->f38;    // 0xbc2e95c  lea rax,[r10+0x38] / 0xbc2e960  mov [rbp-0x10],rax
    (void)_slot38;

    // 0xbc2e964..0xbc2e982: u64 +0x88, 16 bytes +0x78, u64 +0x90. Note the original
    // order: +0x88 first, then +0x78, then +0x90.
    //   0xbc2e964  mov rax,[rsi+0x88]
    //   0xbc2e96b  mov [r10+0x88],rax
    //   0xbc2e972  movups xmm0,[rsi+0x78]
    //   0xbc2e976  movups [r10+0x78],xmm0
    //   0xbc2e97b  mov rax,[rsi+0x90]
    //   0xbc2e982  mov [r10+0x90],rax
    dest->f88 = src->f88;                                 // 0xbc2e964  mov rax,[rsi+0x88] / 0xbc2e96b  mov [r10+0x88],rax
    std::memcpy(&dest->f78, &src->f78, 16);               // 0xbc2e972  movups xmm0,[rsi+0x78] / 0xbc2e976  movups [r10+0x78],xmm0
    dest->f90 = src->f90;                                 // 0xbc2e97b  mov rax,[rsi+0x90] / 0xbc2e982  mov [r10+0x90],rax

    // 0xbc2e989..0xbc2e9a0: sub_e869ff0(dest + 0x98, src + 0x98); dest is saved to
    // [rbp-8] across the call.
    //   0xbc2e989  lea rcx,[r10+0x98]
    //   0xbc2e990  lea rdx,[rsi+0x98]
    //   0xbc2e997  mov [rbp-8],r10
    //   `0xbc2e99b  call 0xE869FF0`
    //   0xbc2e9a0  nop
    native::sub_e869ff0(reinterpret_cast<uint8_t*>(&dest->f98[0]),
                        reinterpret_cast<uint8_t*>(&src->f98[0]));

    // 0xbc2e9a1..0xbc2e9b3: return value = src+0x110 read before it is zeroed; rax
    // survives to ret. dest+0x110 is written through the [rbp-8] copy of dest.
    //   0xbc2e9a1  mov rax,[rsi+0x110]
    //   0xbc2e9a8  mov rcx,[rbp-8]
    //   0xbc2e9ac  mov [rcx+0x110],rax
    //   0xbc2e9b3  mov qword ptr [rsi+0x110],0
    const uint64_t _ret = src->f110;                      // 0xbc2e9a1  mov rax,[rsi+0x110]
    dest->f110 = src->f110;                               // 0xbc2e9a8  mov rcx,[rbp-8] / 0xbc2e9ac  mov [rcx+0x110],rax
    src->f110 = 0;                                        // 0xbc2e9b3  mov qword ptr [rsi+0x110],0

    // 0xbc2e9be..0xbc2e9d1: sub_5669770(dest + 0x118, src + 0x118). rcx holds dest
    // ([rbp-8]); add rcx,0x118 forms dest + 0x118.
    //   0xbc2e9be  add rcx,0x118
    //   0xbc2e9c5  lea rdx,[rsi+0x118]
    //   `0xbc2e9cc  call 0x5669770`
    //   0xbc2e9d1  nop
    native::sub_5669770(reinterpret_cast<uint8_t*>(&dest->pad118[0]),
                        reinterpret_cast<uint8_t*>(&src->pad118[0]));

    // 0xbc2e9d2..0xbc2ea60: u32 +0x24C written first, then 16 bytes +0x23C, byte
    // +0x250, f32 +0x254..0x260; the three 16-byte blocks +0x264/+0x274/+0x283 are
    // all read from src before any is written to dest.
    //   0xbc2e9d2  mov ecx,[rsi+0x24C]
    //   0xbc2e9d8  mov rax,[rbp-8]
    //   0xbc2e9dc  mov [rax+0x24C],ecx
    //   0xbc2e9e2  movups xmm0,[rsi+0x23C]
    //   0xbc2e9e9  movups [rax+0x23C],xmm0
    //   0xbc2e9f0  movzx ecx,byte ptr [rsi+0x250]
    //   0xbc2e9f7  mov [rax+0x250],cl
    //   0xbc2e9fd  movss xmm0,[rsi+0x254]
    //   0xbc2ea05  movss [rax+0x254],xmm0
    //   0xbc2ea0d  movss xmm0,[rsi+0x258]
    //   0xbc2ea15  movss [rax+0x258],xmm0
    //   0xbc2ea1d  movss xmm0,[rsi+0x25C]
    //   0xbc2ea25  movss [rax+0x25C],xmm0
    //   0xbc2ea2d  movss xmm0,[rsi+0x260]
    //   0xbc2ea35  movss [rax+0x260],xmm0
    //   0xbc2ea3d  movups xmm0,[rsi+0x264]
    //   0xbc2ea44  movups xmm1,[rsi+0x274]
    //   0xbc2ea4b  movups xmm2,[rsi+0x283]
    //   0xbc2ea52  movups [rax+0x264],xmm0
    //   0xbc2ea59  movups [rax+0x274],xmm1
    //   0xbc2ea60  movups [rax+0x283],xmm2
    dest->f24c = src->f24c;                               // 0xbc2e9d2  mov ecx,[rsi+0x24C] / 0xbc2e9dc  mov [rax+0x24C],ecx  (rax = dest, reloaded at 0xbc2e9d8)
    std::memcpy(&dest->f23c, &src->f23c, 16);             // 0xbc2e9e2  movups xmm0,[rsi+0x23C] / 0xbc2e9e9  movups [rax+0x23C],xmm0
    dest->f250 = src->f250;                               // 0xbc2e9f0  movzx ecx,byte ptr [rsi+0x250] / 0xbc2e9f7  mov [rax+0x250],cl
    dest->f254 = src->f254;                               // 0xbc2e9fd  movss xmm0,[rsi+0x254] / 0xbc2ea05  movss [rax+0x254],xmm0
    dest->f258 = src->f258;                               // 0xbc2ea0d  movss xmm0,[rsi+0x258] / 0xbc2ea15  movss [rax+0x258],xmm0
    dest->f25c = src->f25c;                               // 0xbc2ea1d  movss xmm0,[rsi+0x25C] / 0xbc2ea25  movss [rax+0x25C],xmm0
    dest->f260 = src->f260;                               // 0xbc2ea2d  movss xmm0,[rsi+0x260] / 0xbc2ea35  movss [rax+0x260],xmm0
    {
        std::byte v264[16];
        std::byte v274[16];
        std::byte v283[16];
        std::memcpy(v264, &src->f264, 16);                // 0xbc2ea3d  movups xmm0,[rsi+0x264]
        std::memcpy(v274, &src->f274, 16);                // 0xbc2ea44  movups xmm1,[rsi+0x274]
        std::memcpy(v283, &src->f283, 16);                // 0xbc2ea4b  movups xmm2,[rsi+0x283]
        std::memcpy(&dest->f264, v264, 16);               // 0xbc2ea52  movups [rax+0x264],xmm0
        std::memcpy(&dest->f274, v274, 16);               // 0xbc2ea59  movups [rax+0x274],xmm1
        std::memcpy(&dest->f283, v283, 16);               // 0xbc2ea60  movups [rax+0x283],xmm2
    }

    // 0xbc2ea67..0xbc2ea6d: epilogue; rax == _ret at ret
    //   0xbc2ea67  add rsp,0x38
    //   0xbc2ea6b  pop rsi
    //   0xbc2ea6c  pop rbp
    //   0xbc2ea6d  ret
    return _ret;
}

LIFT_FN(sub_bc2e890, "sub_bc2e890", 0xbc2e890, sub_bc2e890, sub_bc2e890_footprint);

} // namespace native::bgfx
