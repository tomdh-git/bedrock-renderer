// LIFT 0xbc771f0 size 0x157 1.26.62.01 sub_bc771f0

#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc771f0.h"

#include <cstdint>

// Reversed from the disassembly of [0xbc771f0, 0xbc77347), Minecraft Windows 1.26.62.01

// (rdis dis output). The function has NO call instructions. Every block carries the instruction

// range it implements as // 0xA..0xB beside it; the verbatim log quotes a sample of the

// instructions (copied verbatim, two spaces after the address). Control flow follows the

// original branch structure (one goto per jmp/jcc target), so a reviewer can walk the source

// and the disassembly side by side.

//

// Layout ([V] from this body): the object at rcx is native::Alloc { u32 pad00 @ +0x00; u32

// count @ +0x04; u32 dense[128] @ +0x08..+0x207; u16 sparse[128] @ +0x208..+0x307 (handle or

// 0xFFFF) }; the per-handle refcount u16[] lives at +0x308, indexed by handle*2. All offsets

// are asserted in sub_bc771f0.h.

//

// Calls out of lifted code: none. UNRESOLVED CALL = none: there are no call instructions in

// [0xbc771f0, 0xbc77347).

//

// Verbatim log of sampled instructions (rdis dis output, two spaces after the address;

// wrapped in #if 0 so the lines are not compiled but remain visible to verify_oc):

#if 0
0xbc771f6  mov rax,rdx
0xbc7720c  dec word ptr [rcx+r9*2+0x308]
0xbc77346  ret
#endif

namespace native::bgfx {

uint16_t* sub_bc771f0(Alloc* a, uint16_t* out, uint16_t handle)
{
    // Register mirror (x64 ABI): rcx = a, rdx = out (saved into rax), r8 = handle.

    // rcx/a is constant; rax is returned verbatim.

    uint16_t* rax = out;                                          // 0xbc771f6  mov rax,rdx

    uint16_t dx = 0xFFFF;                                         // 0xbc771f9  mov dx,0xFFFF

    uint32_t r9 = 0, r10 = 0, ebx = 0, esi = 0, edi = 0, ebp = 0, r11 = 0, r14 = 0;

    // 0xbc771f0..0xbc7722c: prologue, invalid-handle early out, refcount decrement, setup.

    //   0xbc771f0  push r14; push rsi; push rdi; push rbp; push rbx

    //   0xbc771f6  mov rax,rdx

    //   0xbc771f9  mov dx,0xFFFF

    //   0xbc771fd  cmp r8w,0xFFFF ; 0xbc77202  je 0xBC7733D

    //   0xbc77208  movzx r9d,r8w

    //   0xbc7720c  dec word ptr [rcx+r9*2+0x308] ; 0xbc77215  jne 0xBC7733D

    //   0xbc7721b  lea rdx,[rcx+0x208] ; 0xbc77222  mov r10d,[rcx+4] ; 0xbc77226  xor r9d,r9d

    //   0xbc77229  jmp short 0xBC77240 ; 0xbc7722b  nop [rax+rax] (dead pad)

    if ((uint16_t)handle == 0xFFFFu) {                            // 0xbc771fd  cmp r8w,0xFFFF ; 0xbc77202  je 0xBC7733D

        goto L_33d;                                               // -> 0xbc7733d  mov [rax],dx

    }
    r9 = (uint32_t)handle;                                        // 0xbc77208  movzx r9d,r8w

    if (--reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(a) + 0x308)[r9] != 0) {  // 0xbc7720c  dec ... ; 0xbc77215  jne 0xBC7733D

        goto L_33d;
    }
    uint16_t* const sparse = reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(a) + 0x208);  // 0xbc7721b  lea rdx,[rcx+0x208]

    r10 = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(a) + 0x4);   // 0xbc77222  mov r10d,[rcx+4]

    r9 = 0;                                                       // 0xbc77226  xor r9d,r9d

    goto L_240;                                                   // 0xbc77229  jmp short 0xBC77240


L_240:                                                            // 0xbc77240..0xbc77246

    //   0xbc77240  cmp [rdx+r9*2],r8w ; 0xbc77245  jne short 0xBC77230

    if (sparse[r9] != (uint16_t)handle) goto L_230;               // 0xbc77245  jne short 0xBC77230

    goto L_247;                                                   // handle found at sparse slot r9


L_230:                                                            // 0xbc77230..0xbc7723b

    //   0xbc77230  inc r9

    ++r9;
L_233:                                                            // 0xbc77233..0xbc7723a

    //   0xbc77233  cmp r9,0x80 ; 0xbc7723a  je 0xBC7733A

    if (r9 == 0x80u) goto L_33a;                                  // 0xbc7723a  je 0xBC7733A  (not present in table)

    goto L_240;

L_247:                                                            // 0xbc77247..0xbc77272

    //   0xbc77247  mov word ptr [rcx+r9*2+0x208],0xFFFF

    //   0xbc77252  dec r10d ; 0xbc77255  mov [rcx+4],r10d

    //   0xbc77259  inc r9 ; 0xbc7725c  mov ebx,r9d ; 0xbc7725f  and ebx,0x7F

    //   0xbc77262  lea edi,[rbx+rbx]

    //   0xbc77265  movzx esi,word ptr [rcx+rdi+0x208] ; 0xbc7726d  cmp si,0xFFFF ; 0xbc77271  je short 0xBC77233

    sparse[r9] = 0xFFFF;                                          // 0xbc77247  mark slot free

    --r10;                                                        // 0xbc77252  dec r10d

    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(a) + 0x4) = r10;  // 0xbc77255  mov [rcx+4],r10d

    ++r9;                                                         // 0xbc77259  inc r9

    ebx = r9 & 0x7Fu;                                             // 0xbc7725c  mov ebx,r9d ; 0xbc7725f  and ebx,0x7F

    edi = ebx + ebx;                                              // 0xbc77262  lea edi,[rbx+rbx]

    esi = sparse[ebx];                                            // 0xbc77265  movzx esi,word ptr [rcx+rdi+0x208]

    if (esi == 0xFFFFu) goto L_233;                               // 0xbc77271  je short 0xBC77233

    // 0xbc77273  add rdi,rdx (rdi = &sparse[ebx]; pointer value not dereferenced again)

    (void)(sparse + ebx);
    r11 = r9 & 0x7Fu;                                             // 0xbc77276  mov r11d,r9d ; 0xbc77279  and r11d,0x7F

    goto L_2ab;                                                   // 0xbc7727d  jmp short 0xBC772AB

    // 0xbc7727f  nop (dead pad, covered by range 0xbc77247..0xbc7727f)


L_280:                                                            // 0xbc77280..0xbc77291

    //   0xbc77280  mov [rcx+r14*4+8],ebx

    //   0xbc77285  mov [rcx+r14*2+0x208],si

    //   0xbc7728e  mov [rcx+4],r10d

    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(a) + 0x8 + r14 * 4u) = ebx;  // 0xbc77280  dense[r14] = ebx

    sparse[r14] = (uint16_t)esi;                                  // 0xbc77285  sparse[r14] = si

    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(a) + 0x4) = r10;  // 0xbc7728e  mov [rcx+4],r10d

    goto L_292;

L_292:                                                            // 0xbc77292..0xbc772a6

    //   0xbc77292  inc r11d ; 0xbc77295  and r11d,0x7F

    //   0xbc77299  lea rdi,[rdx+r11*2] (rdi = &sparse[r11]; not dereferenced here)

    //   0xbc7729d  movzx esi,word ptr [rdx+r11*2]

    //   0xbc772a2  mov rbx,r11 ; 0xbc772a5  cmp si,0xFFFF ; 0xbc772a9  je short 0xBC77233

    ++r11;                                                        // 0xbc77292  inc r11d

    r11 &= 0x7Fu;                                                 // 0xbc77295  and r11d,0x7F

    (void)(sparse + r11);                                         // 0xbc77299  lea rdi,[rdx+r11*2]

    esi = sparse[r11];                                            // 0xbc7729d  movzx esi,word ptr [rdx+r11*2]

    ebx = r11;                                                    // 0xbc772a2  mov rbx,r11

    if (esi == 0xFFFFu) goto L_233;                               // 0xbc772a9  je short 0xBC77233

    goto L_2ab;

L_2ab:                                                            // 0xbc772ab..0xbc772cf

    //   0xbc772ab  mov ebx,[rcx+rbx*4+8]

    //   0xbc772af  imul ebp,ebx,0x1EBCA77 ; 0xbc772b5  shr ebp,0x13

    //   0xbc772b8  imul ebp,0x31 ; 0xbc772bb  and ebp,0x7F

    //   0xbc772be  mov r14d,ebp ; 0xbc772c1  nop [rax+rax]

    ebx = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(a) + 0x8 + ebx * 4u);  // 0xbc772ab  ebx = dense[ebx]

    ebp = (((ebx * 0x1EBCA77u) >> 19u) * 49u) & 0x7Fu;            // 0xbc772af..0xbc772bb  multiplicative hash

    r14 = ebp;                                                    // 0xbc772be  mov r14d,ebp

    goto L_2d0;
    // 0xbc772c1  nop [rax+rax] (dead pad, covered by range 0xbc772ab..0xbc772cf)


L_2d0:                                                            // 0xbc772d0..0xbc772ef

    //   0xbc772d0  mov r14d,r14d

    //   0xbc772d3  cmp word ptr [rdx+r14*2],0xFFFF ; 0xbc772d9  je short 0xBC77300

    //   0xbc772db  cmp [rcx+r14*4+8],ebx ; 0xbc772e0  je short 0xBC772F0

    //   0xbc772e2  inc r14d ; 0xbc772e5  and r14d,0x7F ; 0xbc772e9  cmp r14d,ebp ; 0xbc772ec  jne short 0xBC772D0

    //   0xbc772ee  jmp short 0xBC77300

    if (sparse[r14] == 0xFFFFu) goto L_300;                       // 0xbc772d9  je short 0xBC77300

    if (*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(a) + 0x8 + r14 * 4u) == ebx) goto L_2f0;  // 0xbc772e0  je short 0xBC772F0

    r14 = (r14 + 1u) & 0x7Fu;                                     // 0xbc772e2  inc r14d ; 0xbc772e5  and r14d,0x7F

    if (r14 != ebp) goto L_2d0;                                   // 0xbc772ec  jne short 0xBC772D0

    goto L_300;                                                   // 0xbc772ee  jmp short 0xBC77300 (full circle)


L_2f0:                                                            // 0xbc772f0..0xbc772f6

    //   0xbc772f0  cmp r11d,r14d ; 0xbc772f3  je short 0xBC77292

    //   0xbc772f5  nop [rax+rax] (dead pad, falls to 0xbc77300)

    if (r11 == r14) goto L_292;                                   // 0xbc772f3  je short 0xBC77292

    goto L_300;                                                   // fall through the dead-pad nop to 0xbc77300


L_300:                                                            // 0xbc77300..0xbc7730f

    //   0xbc77300  mov word ptr [rdi],0xFFFF   (rdi = &sparse[r11])

    //   0xbc77305  lea edi,[r10-1] ; 0xbc77309  mov [rcx+4],edi

    //   0xbc7730c  mov r14d,ebp ; 0xbc7730f  nop

    sparse[r11] = 0xFFFF;                                         // 0xbc77300  mov word ptr [rdi],0xFFFF

    edi = r10 - 1u;                                               // 0xbc77305  lea edi,[r10-1]

    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(a) + 0x4) = edi;  // 0xbc77309  mov [rcx+4],edi

    r14 = ebp;                                                    // 0xbc7730c  mov r14d,ebp

    goto L_310;

L_310:                                                            // 0xbc77310..0xbc77331

    //   0xbc77310  mov r14d,r14d

    //   0xbc77313  cmp word ptr [rdx+r14*2],0xFFFF ; 0xbc77319  je 0xBC77280

    //   0xbc7731f  cmp [rcx+r14*4+8],ebx ; 0xbc77324  je short 0xBC77332

    //   0xbc77326  inc r14d ; 0xbc77329  and r14d,0x7F ; 0xbc7732d  cmp r14d,ebp ; 0xbc77330  jne short 0xBC77310

    if (sparse[r14] == 0xFFFFu) goto L_280;                       // 0xbc77319  je 0xBC77280

    if (*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(a) + 0x8 + r14 * 4u) == ebx) goto L_332;  // 0xbc77324  je short 0xBC77332

    r14 = (r14 + 1u) & 0x7Fu;                                     // 0xbc77326  inc r14d ; 0xbc77329  and r14d,0x7F

    if (r14 != ebp) goto L_310;                                   // 0xbc77330  jne short 0xBC77310

    goto L_332;                                                   // exhausted the probe circle


L_332:                                                            // 0xbc77332..0xbc77336

    //   0xbc77332  mov r10d,edi ; 0xbc77335  jmp 0xBC77292

    r10 = edi;                                                    // 0xbc77332  mov r10d,edi

    goto L_292;

L_33a:                                                            // 0xbc7733a..0xbc7733b

    //   0xbc7733a  mov edx,r8d

    dx = (uint16_t)handle;                                        // 0xbc7733a  mov edx,r8d  (not present -> report handle)


L_33d:                                                            // 0xbc7733d..0xbc77346

    //   0xbc7733d  mov [rax],dx

    //   0xbc77340..0xbc77344  pop rbx; pop rbp; pop rdi; pop rsi; pop r14

    //   0xbc77346  ret

    *rax = dx;                                                    // 0xbc7733d  mov [rax],dx

    return rax;                                                   // 0xbc77346  ret  (rax = out)

}

LIFT_FN(sub_bc771f0, "sub_bc771f0", 0xbc771f0, sub_bc771f0, nullptr);

} // namespace native::bgfx

