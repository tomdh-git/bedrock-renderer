// LIFT 0xbc2f1d0 size 0x1ec 1.26.62.01 sub_bc2f1d0
#include "sub_bc2f1d0.h"

#include <cstring>

namespace native {

// Lifted body of sub 0xbc2f1d0 (bgfx field move / take): move/take a render object from a1 (src) to a0 (dst).
// Body span 0xbc2f1d0..0xbc2f3bc, size 0x1ec, 1.26.62.01.
// Every block carries the instruction range it implements (// 0xA..0xB); every instruction is quoted verbatim
// beside it (0xADDR  instr, copied from rdis dis of Minecraft.Windows.exe 1.26.62.01). Control flow follows
// the original: one if per jcc; the f70 type byte switches through an indirect jump at [data 0xF440DB0].
//
// The two calls below target lift-classified game functions (docs/data/native_boundary.tsv rows
// 0xe869ff0 lift and 0x5669770 lift). They are declared in sub_bc2f1d0.h as native::sub_e869ff0 /
// native::sub_5669770 and are called here as plain C++ calls, same arguments, same order:
//   0xbc2f2db  call 0xE869FF0
//   0xbc2f30c  call 0x5669770

void SubBc2f1d0_lifted(Bc2f1d0Object* a0, Bc2f1d0Object* a1) {
    // 0xbc2f1d0..0xbc2f1e6  prologue + argument stash: push rbp / push rsi / sub rsp,0x38 /
    //                       lea rbp,[rsp+0x30]; frame cookie [rbp]=0xFFFFFFFFFFFFFFFE (unobservable);
    //                       rsi = rdx (a1 = src); r10 = rcx (a0 = dst)
    //   0xbc2f1d0  push rbp
    //   0xbc2f1d1  push rsi
    //   0xbc2f1d2  sub rsp,0x38
    //   0xbc2f1d6  lea rbp,[rsp+0x30]
    //   0xbc2f1db  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
    //   0xbc2f1e3  mov rsi,rdx
    //   0xbc2f1e6  mov r10,rcx
    // (frame and register stash: nothing to emit)

    // 0xbc2f1e9..0xbc2f1ec  a0->f00 = a1->f00
    //   0xbc2f1e9  mov rax,[rdx]
    //   0xbc2f1ec  mov [rcx],rax
    a0->f00 = a1->f00;

    // 0xbc2f1ef..0xbc2f1fa  xmm0 = 0; a0->f08 = 0 via xmm0 (dead store, clobbered below);
    //                       a0->f08 = a1->f08
    //   0xbc2f1ef  xorps xmm0,xmm0
    //   0xbc2f1f2  movups [rcx+8],xmm0
    //   0xbc2f1f6  mov rax,[rdx+8]
    //   0xbc2f1fa  mov [rcx+8],rax
    a0->f08 = a1->f08;

    // 0xbc2f1fe..0xbc2f202  a0->f10 = a1->f10
    //   0xbc2f1fe  mov rax,[rdx+0x10]
    //   0xbc2f202  mov [rcx+0x10],rax
    a0->f10 = a1->f10;

    // 0xbc2f206..0xbc2f20a  a1->f08 = 0 via xmm0; a0->f18 = 0, a0->f20 = 0 (16 bytes)
    //   0xbc2f206  movups [rdx+8],xmm0
    a1->f08 = 0;
    //   0xbc2f20a  movups [rcx+0x18],xmm0
    a0->f18 = 0;
    a0->f20 = 0;

    // 0xbc2f20e  mov qword ptr [rcx+0x28],0
    a0->f28 = 0;

    // 0xbc2f216..0xbc2f21a  a0->f30 = a1->f30 (byte)
    //   0xbc2f216  movzx eax,byte ptr [rdx+0x30]
    //   0xbc2f21a  mov [rcx+0x30],al
    a0->f30 = a1->f30;

    // 0xbc2f21d..0xbc2f235  a0->f38/f40 = a1->f38/f40 (16 bytes, xmm1 loaded before the source
    //                       zeroes); a0->f48/f50 = a1->f48/f50 (16 bytes, xmm2 loaded before the
    //                       source zeroes); a1->f40 = 0; a1->f48/f50 = 0
    //   0xbc2f21d  movups xmm1,[rdx+0x38]
    //   0xbc2f221  movups xmm2,[rdx+0x48]
    //   0xbc2f225  mov qword ptr [rdx+0x40],0
    //   0xbc2f22d  movups [rdx+0x48],xmm0
    //   0xbc2f231  movups [rcx+0x38],xmm1
    //   0xbc2f235  movups [rcx+0x48],xmm2
    std::memcpy(&a0->f38, &a1->f38, 16);
    a1->f40 = 0;
    std::memcpy(&a0->f48, &a1->f48, 16);
    a1->f48 = 0;
    a1->f50 = 0;

    // 0xbc2f239..0xbc2f23d  a0->f58 = a1->f58
    //   0xbc2f239  mov rax,[rdx+0x58]
    //   0xbc2f23d  mov [rcx+0x58],rax
    a0->f58 = a1->f58;

    // 0xbc2f241  mov byte ptr [rcx+0x70],0xFF
    a0->f70 = 0xFF;

    // 0xbc2f245..0xbc2f24d  type = a1->f70 (zero-extended byte); type > 3 skips the +0x60 block
    //   0xbc2f245  movzx eax,byte ptr [rdx+0x70]
    //   0xbc2f249  cmp rax,3
    //   0xbc2f24d  ja short 0xBC2F29C
    std::uint32_t type = static_cast<std::uint32_t>(a1->f70);
    if (type <= 3) {
        // 0xbc2f24f..0xbc2f265  indirect jump through the table at [data 0xF440DB0]
        //   0xbc2f24f  lea rcx,[r10+0x60]          // &a0->f60
        //   0xbc2f253  lea rdx,[rsi+0x60]          // &a1->f60
        //   0xbc2f257  lea r8,[0xF440DB0]          // jump table base
        //   0xbc2f25e  movsxd r9,[r8+rax*4]
        //   0xbc2f262  add r9,r8
        //   0xbc2f265  jmp r9
        switch (type) {
        case 0:
            // table[0] -> 0xbc2f298: nothing at +0x60/+0x68
            break;
        case 1:
            // 0xbc2f268  mov rdx,[rdx]
            // 0xbc2f26b  mov [rcx],rdx
            a0->f60 = a1->f60;
            break;
        case 2:
            // 0xbc2f270  movups xmm0,[rdx]
            // 0xbc2f273  movups [rcx],xmm0
            std::memcpy(&a0->f60, &a1->f60, 16);
            break;
        case 3:
            // 0xbc2f278  movups [rcx],xmm0   -- xmm0 == 0 at this entry: 16-byte zero store of
            //                        a0+0x60, clobbered by the qword stores below (dead store)
            // 0xbc2f27b  mov rcx,[rsi+0x68]
            // 0xbc2f27f  test rcx,rcx
            // 0xbc2f282  je short 0xBC2F288
            {
                void* refObj = a1->f68;
                if (refObj != nullptr) {
                    // 0xbc2f284  lock inc dword ptr [rcx+8]
                    ++*reinterpret_cast<std::uint32_t*>(reinterpret_cast<char*>(refObj) + 8);
                }
            }
            // 0xbc2f288  mov rcx,[rsi+0x60]
            // 0xbc2f28c  mov [r10+0x60],rcx
            // 0xbc2f290  mov rcx,[rsi+0x68]
            // 0xbc2f294  mov [r10+0x68],rcx
            a0->f60 = a1->f60;
            a0->f68 = a1->f68;
            break;
        }
        // 0xbc2f298  mov [r10+0x70],al  (reached from cases 0,1,2,3)
        a0->f70 = static_cast<std::uint8_t>(type);
    }

    // 0xbc2f29c..0xbc2f2a0  [rbp-0x10] = &a0->f38  -- stack slot, never read again (dead store)
    //   0xbc2f29c  lea rax,[r10+0x38]
    //   0xbc2f2a0  mov [rbp-0x10],rax
    {
        std::uint8_t* const dead_slot = reinterpret_cast<std::uint8_t*>(a0) + 0x38;
        (void)dead_slot;
    }

    // 0xbc2f2a4..0xbc2f2ab  a0->f88 = a1->f88
    //   0xbc2f2a4  mov rax,[rsi+0x88]
    //   0xbc2f2ab  mov [r10+0x88],rax
    a0->f88 = a1->f88;

    // 0xbc2f2b2..0xbc2f2b6  a0->f78/f80 = a1->f78/f80 (16 bytes)
    //   0xbc2f2b2  movups xmm0,[rsi+0x78]
    //   0xbc2f2b6  movups [r10+0x78],xmm0
    std::memcpy(&a0->f78, &a1->f78, 16);

    // 0xbc2f2bb..0xbc2f2c2  a0->f90 = a1->f90
    //   0xbc2f2bb  mov rax,[rsi+0x90]
    //   0xbc2f2c2  mov [r10+0x90],rax
    a0->f90 = a1->f90;

    // 0xbc2f2c9..0xbc2f2e0  sub_e869ff0(&a0->f98[0], &a1->f98[0]) (lift callee)
    //   0xbc2f2c9  lea rcx,[r10+0x98]          // &a0->f98[0]
    //   0xbc2f2d0  lea rdx,[rsi+0x98]          // &a1->f98[0]
    //   0xbc2f2d7  mov [rbp-8],r10             // save a0 across the call
    //   0xbc2f2db  call 0xE869FF0
    //   0xbc2f2e0  nop
    sub_e869ff0(&a0->f98[0], &a1->f98[0]);

    // 0xbc2f2e1..0xbc2f311  pointer take of f110, then sub_5669770(&a0->f118[0], &a1->f118[0])
    //                        (lift callee)
    //   0xbc2f2e1  mov rax,[rsi+0x110]
    //   0xbc2f2e8  mov rcx,[rbp-8]
    //   0xbc2f2ec  mov [rcx+0x110],rax
    //   0xbc2f2f3  mov qword ptr [rsi+0x110],0
    //   0xbc2f2fe  add rcx,0x118
    //   0xbc2f305  lea rdx,[rsi+0x118]
    //   0xbc2f30c  call 0x5669770
    //   0xbc2f311  nop
    a0->f110 = a1->f110;
    a1->f110 = nullptr;
    sub_5669770(&a0->f118[0], &a1->f118[0]);

    // 0xbc2f312..0xbc2f31c  a0->f24c = a1->f24c
    //   0xbc2f312  mov ecx,[rsi+0x24C]
    //   0xbc2f318  mov rax,[rbp-8]
    //   0xbc2f31c  mov [rax+0x24C],ecx
    a0->f24c = a1->f24c;

    // 0xbc2f322..0xbc2f329  a0->f23c/f244 = a1->f23c/f244 (16 bytes)
    //   0xbc2f322  movups xmm0,[rsi+0x23C]
    //   0xbc2f329  movups [rax+0x23C],xmm0
    std::memcpy(&a0->f23c, &a1->f23c, 16);

    // 0xbc2f330..0xbc2f337  a0->f250 = a1->f250
    //   0xbc2f330  movzx ecx,byte ptr [rsi+0x250]
    //   0xbc2f337  mov [rax+0x250],cl
    a0->f250 = a1->f250;

    // 0xbc2f33d..0xbc2f375  a0->f254..f260 = a1->f254..f260 (floats)
    //   0xbc2f33d  movss xmm0,[rsi+0x254]
    //   0xbc2f345  movss [rax+0x254],xmm0
    //   0xbc2f34d  movss xmm0,[rsi+0x258]
    //   0xbc2f355  movss [rax+0x258],xmm0
    //   0xbc2f35d  movss xmm0,[rsi+0x25C]
    //   0xbc2f365  movss [rax+0x25C],xmm0
    //   0xbc2f36d  movss xmm0,[rsi+0x260]
    //   0xbc2f375  movss [rax+0x260],xmm0
    a0->f254 = a1->f254;
    a0->f258 = a1->f258;
    a0->f25c = a1->f25c;
    a0->f260 = a1->f260;

    // 0xbc2f37d..0xbc2f3a0  a0->f264/f274/f283 = a1->... (16 bytes each)
    //   0xbc2f37d  movups xmm0,[rsi+0x264]
    //   0xbc2f384  movups xmm1,[rsi+0x274]
    //   0xbc2f38b  movups xmm2,[rsi+0x283]
    //   0xbc2f392  movups [rax+0x264],xmm0
    //   0xbc2f399  movups [rax+0x274],xmm1
    //   0xbc2f3a0  movups [rax+0x283],xmm2
    std::memcpy(&a0->f264, &a1->f264, 16);
    std::memcpy(&a0->f274, &a1->f274, 16);
    std::memcpy(&a0->f283, &a1->f283, 16);

    // 0xbc2f3a7..0xbc2f3ae  a0->f294 = a1->f294
    //   0xbc2f3a7  movzx ecx,word ptr [rsi+0x294]
    //   0xbc2f3ae  mov [rax+0x294],cx
    a0->f294 = a1->f294;

    // 0xbc2f3b5..0xbc2f3bb  epilogue: add rsp,0x38; pop rsi; pop rbp; ret
    //   0xbc2f3b5  add rsp,0x38
    //   0xbc2f3b9  pop rsi
    //   0xbc2f3ba  pop rbp
    //   0xbc2f3bb  ret
    return;
}

LIFT_FN(bc2f1d0, "sub_bc2f1d0", 0xBC2F1D0, SubBc2f1d0_lifted, nullptr);

} // namespace native
