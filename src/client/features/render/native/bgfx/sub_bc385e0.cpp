// LIFT 0xbc385e0 size 0x34b 1.26.62.01 sub_bc385e0
#include "client/features/render/native/bgfx/sub_bc385e0.h"
#include "client/features/render/native/Lift.h"

#include <cstring>

// Layout assertions (definitions live in sub_bc385e0.h; repeated here so
// liftcheck sees them in the source file).
static_assert(offsetof(native::bgfx::Bc385e0State, vptr) == 0x00);
static_assert(offsetof(native::bgfx::Bc385e0State, f28) == 0x28);
static_assert(offsetof(native::bgfx::Bc385e0State, f30) == 0x30);
static_assert(offsetof(native::bgfx::Bc385e0State, f38) == 0x38);
static_assert(offsetof(native::bgfx::Bc385e0State, f70) == 0x70);
static_assert(offsetof(native::bgfx::Bc385e0State, f78) == 0x78);
static_assert(offsetof(native::bgfx::Bc385e0State, f80) == 0x80);
static_assert(offsetof(native::bgfx::Bc385e0State, f88) == 0x88);
static_assert(offsetof(native::bgfx::Bc385e0State, pad_0x90) == 0x90);
static_assert(offsetof(native::bgfx::Bc385e0State, fA0) == 0xA0);
static_assert(offsetof(native::bgfx::Bc385e0State, fA8) == 0xA8);
static_assert(offsetof(native::bgfx::Bc385e0State, fB0) == 0xB0);
static_assert(offsetof(native::bgfx::Bc385e0State, pad_0xB8) == 0xB8);
static_assert(offsetof(native::bgfx::Bc385e0State, pad_0xC8) == 0xC8);
static_assert(offsetof(native::bgfx::Bc385e0State, fD8) == 0xD8);
static_assert(offsetof(native::bgfx::Bc385e0State, pad_0xE0) == 0xE0);
static_assert(offsetof(native::bgfx::Bc385e0State, pad_0xF0) == 0xF0);
static_assert(offsetof(native::bgfx::Bc385e0State, pad_0x214) == 0x214);
static_assert(offsetof(native::bgfx::Bc385e0State, pad_0x224) == 0x224);
static_assert(offsetof(native::bgfx::Bc385e0State, f234) == 0x234);
static_assert(offsetof(native::bgfx::Bc385e0State, f238) == 0x238);
static_assert(offsetof(native::bgfx::Bc385e0State, f23C) == 0x23C);
static_assert(offsetof(native::bgfx::Bc385e0State, f240) == 0x240);
static_assert(offsetof(native::bgfx::Bc385e0State, f244) == 0x244);
static_assert(offsetof(native::bgfx::Bc385e0State, f248) == 0x248);
static_assert(offsetof(native::bgfx::Bc385e0State, pad_0x24C) == 0x24C);
static_assert(offsetof(native::bgfx::Bc385e0State, pad_0x25C) == 0x25C);
static_assert(offsetof(native::bgfx::Bc385e0State, pad_0x26C) == 0x26C);
static_assert(offsetof(native::bgfx::Bc385e0State, pad_0x27A) == 0x27A);
static_assert(offsetof(native::bgfx::Bc385e0State, f28C) == 0x28C);
static_assert(offsetof(native::bgfx::Bc385e0State, f290) == 0x290);
static_assert(offsetof(native::bgfx::Bc385e0State, f298) == 0x298);
static_assert(offsetof(native::bgfx::Bc385e0State, f2A0) == 0x2A0);
static_assert(offsetof(native::bgfx::Bc385e0State, f2A8) == 0x2A8);
static_assert(sizeof(native::bgfx::Bc385e0State) == 0x2B0);
static_assert(offsetof(native::bgfx::Bc385e0SmallString, data) == 0x00);
static_assert(offsetof(native::bgfx::Bc385e0SmallString, size) == 0x08);
static_assert(sizeof(native::bgfx::Bc385e0SmallString) == 0x10);

namespace native::bgfx {

// Calls out of this function, quoted verbatim from the disassembly of
// [0xbc385e0, 0xbc3892b) (rdis dis output):
// `0xbc3865a  call qword ptr [0xF99FFA0]`
// `0xbc3867a  call qword ptr [0xF99FFA0]`
// `0xbc3873e  call 0x5669770`
// `0xbc38894  call qword ptr [0xF99FFA0]`
// `0xbc388bc  call qword ptr [0xF99FFA0]`
// `0xbc388ec  call 0xEEC6EC0`
// `0xbc3890e  call 0x9BC830`
// `0xbc38919  call 0x9BC830`
// `0xbc38924  call 0x75720`
//
// The four [0xF99FFA0] calls are indirect calls through the CFG thunk
// (gadget at 0xeea6040 is `jmp rax`, rax = the vtable entry loaded just before
// the call). There is no static callee target, so no boundary wrapper is
// involved; they are reproduced as calls through function pointers read from
// the object's vtable / global allocator table, exactly as sub_bc55ea0 and
// sub_bc2bca0 do.
//
// sub_5669770 ([0x5669770, 0x5669AD9]) copies exactly [0x00, 0x124) bytes from
// src to dst via movss/movups stores: it is memcpy(dst, src, 0x124), a CRT
// intrinsic inlined by the original compiler. Replaced with std::memcpy here.
// sub_eec6ec0 is memcpy per docs/BGFX_MAP.md; replaced with std::memcpy.
//
// sub_75720 (stl boundary) and sub_9bc830 (alloc boundary) are called through
// their native symbols as plain extern "C" functions; both are noreturn error
// paths (followed by int3 in the original), so control never continues after
// them. Lifted code mirrors that with __declspec(noreturn) and __assume(false).

extern "C" __declspec(noreturn) void sub_75720();           // boundary stl
extern "C" __declspec(noreturn) void sub_9bc830(std::uint64_t size);  // boundary alloc

// data_f440770: the vtable address loaded by `lea rax,[0xF440770]` at 0xbc38623
// and stored at out+0x00 as the object's vptr. RVA 0xF440770 -> VA 0x14F440770
// at image base 0x140000000. [V: rdis dis, data_f440770]
static constexpr void* g_vtable_f440770 = reinterpret_cast<void*>(0x14F440770ULL);

// Global at VA 0x15233E1A8 (= image base 0x140000000 + RVA 0x1233E1A8).
// Holds a pointer P to an allocator object; the allocator function is
// (*P)[1] = vtable[1], called as allocFn(P, size) with rcx=P, rdx=size
// via the CFG thunk [0xF99FFA0]. [V: rdis dis, data_1233e1a8]
static void** g_allocObj = reinterpret_cast<void**>(0x15233E1A8ULL);

// footprint: every byte written to *a0. Writes to a1+0x38 (zeroed), a3+0x8/0x48/0x50
// (zeroed) are out-of-function side effects on inputs, not declared (same
// convention as sub_bc2bca0).
static native::Footprint sub_bc385e0Footprint(void* a0, void*, void*, void*) {
    return { { a0, sizeof(Bc385e0State) } };
}

extern "C" void* sub_bc385e0(void* a0, void* a1, void* a2, void* a3) {
    auto* out = reinterpret_cast<Bc385e0State*>(a0);
    std::uint8_t* a1b = reinterpret_cast<std::uint8_t*>(a1);
    std::uint8_t* a3b = reinterpret_cast<std::uint8_t*>(a3);
    auto* ss = reinterpret_cast<Bc385e0SmallString*>(a2);

    // 0xbc385e0..0xbc38631: prologue + field init
    //   0xbc385e0  push rbp
    //   0xbc385e1  push r15
    //   0xbc385e3  push r14
    //   0xbc385e5  push r12
    //   0xbc385e7  push rsi
    //   0xbc385e8  push rdi
    //   0xbc385e9  push rbx
    //   0xbc385ea  sub rsp,0x50
    //   0xbc385ee  lea rbp,[rsp+0x50]
    //   0xbc385f3  movaps [rbp-0x10],xmm6
    //   0xbc385f7  mov qword ptr [rbp-0x18],0xFFFFFFFFFFFFFFFE
    //   0xbc385ff  mov rdi,r9                 rdi = a3
    //   0xbc38602  mov rsi,r8                 rsi = a2
    //   0xbc38605  mov r14,rcx                r14 = a0 = out
    //   0xbc38608  xorps xmm6,xmm6            xmm6 = 0
    //   0xbc3860b  movups [rcx+0x18],xmm6     out+0x18 = 0 (16 bytes)
    //   0xbc3860f  movups [rcx+8],xmm6        out+0x8 = 0 (16 bytes)
    //   0xbc38613  mov qword ptr [rcx+0x28],0xF   out->f28 = 0xF
    //   0xbc3861b  mov qword ptr [rcx+0x30],0     out->f30 = 0
    //   0xbc38623  lea rax,[0xF440770]        rax = g_vtable_f440770
    //   0xbc3862a  mov [rcx],rax              out->vptr = g_vtable_f440770
    //   0xbc3862d  lea r15,[rcx+0x38]         r15 = &out->f38
    //   0xbc38631  mov qword ptr [rcx+0x70],0   out->f70 = 0
    std::memset(out->pad_0x08, 0, sizeof(out->pad_0x08));   // 0xbc3860b + 0xbc3860f: out+0x08..0x27 = 0
    out->f28 = 0xF;                                          // 0xbc38613
    out->f30 = 0;                                            // 0xbc3861b
    out->vptr = g_vtable_f440770;                            // 0xbc38623..0xbc3862a
    out->f70 = 0;                                            // 0xbc38631

    // 0xbc38631..0xbc38688: [a1+0x38] handling
    //   0xbc38639  mov rcx,[rdx+0x38]   rcx = [a1+0x38]
    //   0xbc3863d  test rcx,rcx
    //   0xbc38640  je short 0xBC38688   if zero, skip
    //   0xbc38642  mov rbx,rdx           rbx = a1
    //   0xbc38645  cmp rcx,rdx           [a1+0x38] vs a1
    //   0xbc38648  je short 0xBC38650    if equal -> first virtual call (vtable[8])
    //   0xbc3864a  mov [r14+0x70],rcx    out->f70 = [a1+0x38]
    //   0xbc3864e  jmp short 0xBC38680
    // loc_bc38650:
    //   0xbc38650  mov rax,[rcx]         rax = [a1_f38] (vptr)
    //   0xbc38653  mov rax,[rax+8]       rax = vtable[8]
    //   0xbc38657  mov rdx,r15           rdx = &out->f38
    //   0xbc3865a  call qword ptr [0xF99FFA0]   vtable[8](a1_f38, &out->f38)
    //   0xbc38660  mov [r14+0x70],rax    out->f70 = result
    //   0xbc38664  mov rcx,[rbx+0x38]    rcx = [a1+0x38]
    //   0xbc38668  test rcx,rcx
    //   0xbc3866b  je short 0xBC38688
    //   0xbc3866d  cmp rcx,rbx           [a1+0x38] vs a1
    //   0xbc38670  setne dl              dl = ([a1+0x38] != a1) ? 1 : 0
    //   0xbc38673  mov rax,[rcx]         rax = vptr
    //   0xbc38676  mov rax,[rax+0x20]    rax = vtable[4]
    //   0xbc3867a  call qword ptr [0xF99FFA0]   vtable[4](a1_f38, dl)
    // loc_bc38680:
    //   0xbc38680  mov qword ptr [rbx+0x38],0   [a1+0x38] = 0
    {
        void* a1_f38 = *reinterpret_cast<void**>(a1b + 0x38);   // 0xbc38639
        if (a1_f38 != nullptr) {                                // 0xbc3863d..0xbc38640
            if (a1_f38 == a1) {                                 // 0xbc38645..0xbc38648 (equal -> first vcall)
                // 0xbc38650  mov rax,[rcx]
                // 0xbc38653  mov rax,[rax+8]                   vtable[8] = [vtable+8]
                void** vt = *reinterpret_cast<void***>(a1_f38);
                using VCall8 = void* (*)(void*, void*);
                VCall8 fn8 = reinterpret_cast<VCall8>(vt[1]);
                // 0xbc38657  mov rdx,r15  (rdx = &out->f38)
                // 0xbc3865a  call qword ptr [0xF99FFA0]
                out->f70 = fn8(a1_f38, &out->f38);              // 0xbc3865a..0xbc38660
            } else {                                            // 0xbc38648 (not equal -> direct store)
                out->f70 = a1_f38;                              // 0xbc3864a
            }
            // 0xbc38664..0xbc3867a: second virtual call, always when [a1+0x38] != 0
            // 0xbc38664  mov rcx,[rbx+0x38]  (rcx = a1_f38)
            // 0xbc3866d  cmp rcx,rbx
            // 0xbc38670  setne dl           dl = (a1_f38 != a1) ? 1 : 0
            // 0xbc38673  mov rax,[rcx]
            // 0xbc38676  mov rax,[rax+0x20]  vtable[4] = [vtable+0x20]
            void** vt2 = *reinterpret_cast<void***>(a1_f38);
            using VCall4 = void* (*)(void*, std::uint8_t);
            VCall4 fn4 = reinterpret_cast<VCall4>(vt2[4]);
            // 0xbc3867a  call qword ptr [0xF99FFA0]  (rdx = dl)
            (void)fn4(a1_f38, static_cast<std::uint8_t>(a1_f38 != a1 ? 1 : 0)); // 0xbc3867a
        }
        // 0xbc38680: [a1+0x38] = 0  (all paths where [a1+0x38] != 0)
        *reinterpret_cast<void**>(a1b + 0x38) = nullptr;      // 0xbc38680
    }

    // 0xbc38688..0xbc3871b: copy from a3 part 1
    //   0xbc38688  mov [rbp-0x30],r15              stack = &out->f38
    //   0xbc3868c  mov rax,[rdi]                   rax = [a3+0x00]
    //   0xbc3868f  mov [r14+0x78],rax              out->f78 = [a3+0x00]
    //   0xbc38693  movups [r14+0x80],xmm6          out->f80 = 0 (16 bytes) -- overwritten below
    //   0xbc3869b  mov rax,[rdi+8]                 rax = [a3+0x08]
    //   0xbc3869f  mov [r14+0x80],rax              out->f80 = [a3+0x08]
    //   0xbc386a6  mov rax,[rdi+0x10]              rax = [a3+0x10]
    //   0xbc386aa  mov [r14+0x88],rax              out->f88 = [a3+0x10]
    //   0xbc386b1  movups [rdi+8],xmm6             [a3+0x08] = 0 (16 bytes)  WRITE to input
    //   0xbc386b5  movups [r14+0x90],xmm6          out+0x90 = 0 (16 bytes)
    //   0xbc386bd  mov qword ptr [r14+0xA0],0      out->fA0 = 0
    //   0xbc386c8  movzx eax,byte ptr [rdi+0x30]   eax = byte [a3+0x30]
    //   0xbc386cc  mov [r14+0xA8],al               out->fA8 = byte [a3+0x30]
    //   0xbc386d3  mov byte ptr [r14+0xD8],0       out->fD8 = 0
    //   0xbc386db  cmp byte ptr [rdi+0x60],1       if byte [a3+0x60] == 1:
    //   0xbc386df  jne short 0xBC3871B
    //   0xbc386e1  mov rax,[rdi+0x38]              rax = [a3+0x38]
    //   0xbc386e5  mov [r14+0xB0],rax              out->fB0 = [a3+0x38]
    //   0xbc386ec  movups xmm0,[rdi+0x40]          xmm0 = [a3+0x40] (16 bytes)
    //   0xbc386f0  movups xmm1,[rdi+0x50]          xmm1 = [a3+0x50] (16 bytes)
    //   0xbc386f4  mov qword ptr [rdi+0x48],0      [a3+0x48] = 0               WRITE to input
    //   0xbc386fc  xorps xmm2,xmm2                 xmm2 = 0
    //   0xbc386ff  movups [rdi+0x50],xmm2          [a3+0x50] = 0 (16 bytes)   WRITE to input
    //   0xbc38703  movups [r14+0xB8],xmm0          out->pad_0xB8 = [a3+0x40]
    //   0xbc3870b  movups [r14+0xC8],xmm1          out->pad_0xC8 = [a3+0x50]
    //   0xbc38713  mov byte ptr [r14+0xD8],1       out->fD8 = 1
    out->f78 = *reinterpret_cast<void**>(a3b + 0x00);        // 0xbc3868c..0xbc3868f
    out->f80 = *reinterpret_cast<std::uint64_t*>(a3b + 0x08); // 0xbc3869b..0xbc3869f
    out->f88 = *reinterpret_cast<std::uint64_t*>(a3b + 0x10); // 0xbc386a6..0xbc386aa
    std::memset(a3b + 0x08, 0, 16);                          // 0xbc386b1: [a3+0x08..0x17] = 0
    std::memset(out->pad_0x90, 0, sizeof(out->pad_0x90));    // 0xbc386b5: out+0x90..0x9F = 0
    out->fA0 = 0;                                            // 0xbc386bd
    out->fA8 = a3b[0x30];                                    // 0xbc386c8..0xbc386cc
    out->fD8 = 0;                                            // 0xbc386d3
    if (a3b[0x60] == 1) {                                    // 0xbc386db..0xbc386df
        out->fB0 = *reinterpret_cast<void**>(a3b + 0x38);    // 0xbc386e1..0xbc386e5
        std::memcpy(out->pad_0xB8, a3b + 0x40, 16);          // 0xbc386ec..0xbc38703
        *reinterpret_cast<std::uint64_t*>(a3b + 0x48) = 0;   // 0xbc386f4: [a3+0x48] = 0
        std::memcpy(out->pad_0xC8, a3b + 0x50, 16);          // 0xbc386f0..0xbc3870b
        *reinterpret_cast<std::uint64_t*>(a3b + 0x50) = 0;   // 0xbc386fc..0xbc386ff: [a3+0x50..0x5F] = 0
        out->fD8 = 1;                                        // 0xbc38713
    }

    // 0xbc3871b..0xbc38743: memcpy setup + call + restore
    //   0xbc3871b  lea rax,[r14+0x78]         rax = &out->f78
    //   0xbc3871f  mov [rbp-0x28],rax         stack = &out->f78
    //   0xbc38723  movups xmm0,[rdi+0x68]     xmm0 = [a3+0x68] (16 bytes)
    //   0xbc38727  movups [r14+0xE0],xmm0     out->pad_0xE0 = [a3+0x68]
    //   0xbc3872f  lea rcx,[r14+0xF0]         rcx = &out->pad_0xF0
    //   0xbc38736  lea rdx,[rdi+0x78]         rdx = &a3+0x78
    //   0xbc3873a  mov [rbp-0x20],r14         stack = out
    //   0xbc3873e  call 0x5669770             sub_5669770(&out->pad_0xF0, &a3+0x78, 0x124) == memcpy
    //   0xbc38743  nop
    //   0xbc38744  mov r14,[rbp-0x20]         r14 = out (restored)
    std::memcpy(out->pad_0xE0, a3b + 0x68, 16);              // 0xbc38723..0xbc38727
    // 0xbc3873e  call 0x5669770  (memcpy 0x124 bytes)
    std::memcpy(out->pad_0xF0, a3b + 0x78, 0x124);           // 0xbc3873e

    // 0xbc38748..0xbc3882a: f28C + conditional copy from a3
    //   0xbc38748  mov byte ptr [r14+0x28C],0   out->f28C = 0
    //   0xbc38750  cmp byte ptr [rdi+0x214],1   if byte [a3+0x214] == 1:
    //   0xbc38757  jne 0xBC3882A
    //   0xbc3875d  movups xmm0,[rdi+0x19C]      xmm0 = [a3+0x19C] (16 bytes)
    //   0xbc38764  movups xmm1,[rdi+0x1AC]      xmm1 = [a3+0x1AC] (16 bytes)
    //   0xbc3876b  movups [r14+0x224],xmm1      out->pad_0x224 = [a3+0x1AC]
    //   0xbc38773  movups [r14+0x214],xmm0      out->pad_0x214 = [a3+0x19C]
    //   0xbc3877b  mov byte ptr [r14+0x248],0   out->f248 = 0
    //   0xbc38783  cmp byte ptr [rdi+0x1D0],1   if byte [a3+0x1D0] == 1:
    //   0xbc3878a  jne short 0xBC387E6
    //   0xbc3878c  movzx eax,byte ptr [rdi+0x1BC]  al = byte [a3+0x1BC]
    //   0xbc38793  mov [r14+0x234],al           out->f234 = byte [a3+0x1BC]
    //   0xbc3879a  movss xmm0,[rdi+0x1C0]       xmm0 = float [a3+0x1C0]
    //   0xbc387a2  movss [r14+0x238],xmm0       out->f238 = float [a3+0x1C0]
    //   0xbc387ab  movss xmm0,[rdi+0x1C4]
    //   0xbc387b3  movss [r14+0x23C],xmm0       out->f23C = float [a3+0x1C4]
    //   0xbc387bc  movss xmm0,[rdi+0x1C8]
    //   0xbc387c4  movss [r14+0x240],xmm0       out->f240 = float [a3+0x1C8]
    //   0xbc387cd  movss xmm0,[rdi+0x1CC]
    //   0xbc387d5  movss [r14+0x244],xmm0       out->f244 = float [a3+0x1CC]
    //   0xbc387de  mov byte ptr [r14+0x248],1   out->f248 = 1
    // loc_bc387e6:
    //   0xbc387e6  movups xmm0,[rdi+0x1D4]      xmm0 = [a3+0x1D4] (16 bytes)
    //   0xbc387ed  movups xmm1,[rdi+0x1E4]      xmm1 = [a3+0x1E4] (16 bytes)
    //   0xbc387f4  movups xmm2,[rdi+0x1F4]      xmm2 = [a3+0x1F4] (16 bytes)
    //   0xbc387fb  movups xmm3,[rdi+0x202]      xmm3 = [a3+0x202] (16 bytes)
    //   0xbc38802  movups [r14+0x27A],xmm3      out->pad_0x27A = [a3+0x202]
    //   0xbc3880a  movups [r14+0x26C],xmm2      out->pad_0x26C = [a3+0x1F4]
    //   0xbc38812  movups [r14+0x25C],xmm1      out->pad_0x25C = [a3+0x1E4]
    //   0xbc3881a  movups [r14+0x24C],xmm0      out->pad_0x24C = [a3+0x1D4]
    //   0xbc38822  mov byte ptr [r14+0x28C],1   out->f28C = 1
    out->f28C = 0;                                           // 0xbc38748
    if (a3b[0x214] == 1) {                                   // 0xbc38750..0xbc38757
        std::memcpy(out->pad_0x224, a3b + 0x1AC, 16);        // 0xbc38764..0xbc3876b
        std::memcpy(out->pad_0x214, a3b + 0x19C, 16);        // 0xbc3875d..0xbc38773
        out->f248 = 0;                                       // 0xbc3877b
        if (a3b[0x1D0] == 1) {                               // 0xbc38783..0xbc3878a
            out->f234 = a3b[0x1BC];                          // 0xbc3878c..0xbc38793
            out->f238 = *reinterpret_cast<const float*>(a3b + 0x1C0); // 0xbc3879a..0xbc387a2
            out->f23C = *reinterpret_cast<const float*>(a3b + 0x1C4); // 0xbc387ab..0xbc387b3
            out->f240 = *reinterpret_cast<const float*>(a3b + 0x1C8); // 0xbc387bc..0xbc387c4
            out->f244 = *reinterpret_cast<const float*>(a3b + 0x1CC); // 0xbc387cd..0xbc387d5
            out->f248 = 1;                                   // 0xbc387de
        }
        std::memcpy(out->pad_0x24C, a3b + 0x1D4, 16);        // 0xbc387e6..0xbc3881a
        std::memcpy(out->pad_0x25C, a3b + 0x1E4, 16);
        std::memcpy(out->pad_0x26C, a3b + 0x1F4, 16);
        std::memcpy(out->pad_0x27A, a3b + 0x202, 16);
        out->f28C = 1;                                       // 0xbc38822
    }

    // 0xbc3882a..0xbc388d5: zero small-string fields, get a2 size
    //   0xbc3882a  xorps xmm0,xmm0
    //   0xbc3882d  movups [r14+0x2A0],xmm0      out+0x2A0 = 0 (16 bytes: f2A0+f2A8)
    //   0xbc38835  movups [r14+0x290],xmm0      out+0x290 = 0 (16 bytes: f290+f298)
    //   0xbc3883d  mov rdi,[rsi+8]              rdi = ss->size
    //   0xbc38841  test rdi,rdi
    //   0xbc38844  js 0xBC38924                 if size < 0 -> sub_75720
    //   0xbc3884a  lea rbx,[r14+0x290]          rbx = &out->f290 (SSO buffer)
    //   0xbc38851  mov rsi,[rsi]                rsi = ss->data
    //   0xbc38854  mov r12d,0xF                 r12 = 0xF
    //   0xbc3885a  cmp rdi,0x10                 size vs 0x10
    //   0xbc3885e  jb short 0xBC388D5           if size < 0x10 -> SSO path
    out->f290 = nullptr;                                     // 0xbc3882d: out+0x290..0x29F = 0
    out->f298 = 0;
    out->f2A0 = 0;                                           // 0xbc3882d: out+0x2A0..0x2AF = 0
    out->f2A8 = 0;
    const std::uint64_t size = ss->size;                     // 0xbc3883d
    if (static_cast<std::int64_t>(size) < 0) {               // 0xbc38841..0xbc38844
        // 0xbc38924  call 0x75720  (boundary stl, noreturn)
        sub_75720();                                         // 0xbc38924
        __assume(false);
    }
    void* data = ss->data;                                   // 0xbc38851
    const std::uint64_t capacity = 0xF;                      // 0xbc38854

    // 0xbc388d5..0xbc388ec: heap alloc or SSO
    //   loc_bc388D5 (from 0xbc3885e, size < 0x10):
    //   0xbc388d5  mov [r14+0x2A0],rdi   out->f2A0 = size
    //   0xbc388dc  mov [r14+0x2A8],r12   out->f2A8 = 0xF
    //   0xbc388e3  mov rcx,rbx           rcx = buffer (&out->f290 for SSO)
    //   size >= 0x10 path:
    //   0xbc38860  mov rdx,rdi           rdx = size
    //   0xbc38863  or rdx,0xF            rdx = size | 0xF
    //   0xbc38867  cmp rdx,0x17
    //   0xbc3886b  mov r12d,0x16         r12 = 0x16
    //   0xbc38871  cmovae r12,rdx        if (size|0xF) >= 0x17: r12 = size|0xF
    //   0xbc38875  mov rcx,[0x1233E1A8]  rcx = P (*g_allocObj)
    //   0xbc3887c  mov rax,[rcx]         rax = *P = vtable
    //   0xbc3887f  mov rax,[rax+8]       rax = vtable[1] = allocFn
    //   0xbc38883  cmp rdx,0xFFF         rdx vs 0xFFF
    //   0xbc3888a  jb short 0xBC388B4    if < 0xFFF -> small alloc
    //   big alloc:
    //   0xbc3888c  lea r15,[r12+0x28]    r15 = r12 + 0x28
    //   0xbc38891  mov rdx,r15           rdx = allocSize
    //   0xbc38894  call qword ptr [0xF99FFA0]  rax = allocFn(P, r15)
    //   0xbc3889a  nop
    //   0xbc3889b  mov r14,rax           r14 = raw buffer
    //   0xbc3889e  test rax,rax
    //   0xbc388a1  je short 0xBC3890B    if 0 -> sub_9bc830
    //   loc_bc388a3:
    //   0xbc388a3  mov rax,r14           rax = raw
    //   0xbc388a6  add r14,0x27          r14 = raw + 0x27
    //   0xbc388aa  and r14,~0x1F         r14 = align_down(raw + 0x27, 32)
    //   0xbc388ae  mov [r14-8],rax       [aligned-8] = raw
    //   0xbc388b2  jmp short 0xBC388CB
    //   small alloc:
    //   loc_bc388B4:
    //   0xbc388b4  lea r15,[r12+1]       r15 = r12 + 1
    //   0xbc388b9  mov rdx,r15           rdx = allocSize
    //   0xbc388bc  call qword ptr [0xF99FFA0]  rax = allocFn(P, r15)
    //   0xbc388c2  nop
    //   0xbc388c3  mov r14,rax           r14 = raw buffer
    //   0xbc388c6  test rax,rax
    //   0xbc388c9  je short 0xBC38916    if 0 -> sub_9bc830
    //   loc_bc388CB:
    //   0xbc388cb  mov [rbx],r14         out->f290 = r14 (aligned or raw)
    //   0xbc388ce  mov rbx,r14           rbx = r14 (buffer)
    //   0xbc388d1  mov r14,[rbp-0x20]    r14 = out (restored)
    void* buffer = nullptr;
    if (size >= 0x10) {                                       // 0xbc3885a..0xbc3885e (not taken)
        const std::uint64_t sizeOrF = size | 0xF;             // 0xbc38860..0xbc38863
        const std::uint64_t r12 = (sizeOrF >= 0x17) ? sizeOrF : 0x16ull; // 0xbc38867..0xbc38871
        // 0xbc38875..0xbc3887f: allocFn = (*g_allocObj)[1]
        void* P = *g_allocObj;                                // 0xbc38875
        void** vt = reinterpret_cast<void**>(P);              // 0xbc3887c: rax = [rcx] = *P
        using AllocFn = void* (*)(void*, std::uint64_t);
        AllocFn allocFn = reinterpret_cast<AllocFn>(vt[1]);   // 0xbc3887f: rax = [rax+8] = vtable[1]
        const std::uint64_t allocSize =                       // 0xbc38883..0xbc3888a
            (sizeOrF < 0xFFF) ? (r12 + 1) : (r12 + 0x28);   // jb -> small: r12+1 ; else big: r12+0x28
        // 0xbc38894 / 0xbc388bc: call qword ptr [0xF99FFA0]  rax = allocFn(P, allocSize)
        void* raw = allocFn(P, allocSize);                    // 0xbc38894 / 0xbc388bc
        if (raw == nullptr) {                                 // 0xbc3889e / 0xbc388c6
            // 0xbc388a1 / 0xbc388c9: je -> sub_9bc830
            // 0xbc3890b / 0xbc38916: call 0x9BC830 (boundary alloc, noreturn)
            sub_9bc830(allocSize);                            // 0xbc3890b / 0xbc38916
            __assume(false);
        }
        if (sizeOrF >= 0xFFF) {                               // 0xbc3888a not taken (big alloc)
            // 0xbc3888c..0xbc388ae: align raw + 0x27 down to 32, store raw at aligned-8
            const std::uintptr_t aligned =
                (reinterpret_cast<std::uintptr_t>(raw) + 0x27) & ~0x1FULL; // 0xbc388a6..0xbc388aa
            *reinterpret_cast<void**>(aligned - 8) = raw;     // 0xbc388ae
            buffer = reinterpret_cast<void*>(aligned);        // 0xbc388a3..0xbc388b2 (r14 = aligned)
        } else {
            buffer = raw;                                     // small alloc: r14 = raw
        }
        out->f290 = buffer;                                   // 0xbc388cb: [rbx] = r14
    } else {
        // SSO path: 0xbc388d5..0xbc388dc
        out->f2A0 = size;                                     // 0xbc388d5
        out->f2A8 = capacity;                                 // 0xbc388dc
        buffer = &out->f290;                                  // rbx = &out->f290 (set before branch)
    }

    // 0xbc388e3..0xbc3890a: memcpy data + null terminator + epilogue
    //   0xbc388e3  mov rcx,rbx           rcx = buffer
    //   0xbc388e6  mov rdx,rsi           rdx = data
    //   0xbc388e9  mov r8,rdi            r8 = size
    //   0xbc388ec  call 0xEEC6EC0        memcpy(buffer, data, size)
    //   0xbc388f1  mov byte ptr [rbx+rdi],0   buffer[size] = 0
    //   0xbc388f5  mov rax,r14           rax = out
    //   0xbc388f8  movaps xmm6,[rbp-0x10]
    //   0xbc388fc  add rsp,0x50
    //   0xbc38900  pop rbx
    //   0xbc38901  pop rdi
    //   0xbc38902  pop rsi
    //   0xbc38903  pop r12
    //   0xbc38905  pop r14
    //   0xbc38907  pop r15
    //   0xbc38909  pop rbp
    //   0xbc3890a  ret
    // 0xbc388ec  call 0xEEC6EC0  (memcpy)
    std::memcpy(buffer, data, size);                         // 0xbc388ec
    static_cast<std::uint8_t*>(buffer)[size] = 0;            // 0xbc388f1: buffer[size] = 0
    return a0;                                               // 0xbc388f5..0xbc3890a: rax = out, ret
}

LIFT_FN(sub_bc385e0, "sub_bc385e0", 0xbc385e0, sub_bc385e0, sub_bc385e0Footprint);

} // namespace native::bgfx
