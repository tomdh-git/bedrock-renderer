// LIFT 0xbc79790 size 0x2ce 1.26.62.01 sub_bc79790
#include "sub_bc79790.h"
#include "sub_bc75c30.h"
#include "client/features/render/native/Lift.h"

namespace native {

static_assert(kSlotStride == 0x20, "sub_bc79790 layout");
extern "C" void sub_bc79790(Ctx79790* ctx, std::uint16_t idx) {
    // 0xbc79790..0xbc797bb
    std::uint16_t savedIdx = idx;  // 0xbc797a8  mov [rsp+0x3C],dx

    SlotObject79790* slot = reinterpret_cast<SlotObject79790*>(
        reinterpret_cast<char*>(ctx) + kSlotBase +
        static_cast<std::size_t>(idx) * kSlotStride);  // 0xbc797e2  lea rdi,[rcx+rax] ; 0xbc797e6  add rdi,0x1E2CAB0
    --slot->refCount;  // 0xbc797b3  dec word ptr [rcx+rax+0x1E2CACC]
    if (slot->refCount != 0u) {  // 0xbc797bb  je short 0xBC797DF
        // 0xbc797bd..0xbc797de epilogue
    // 0xbc79a50..0xbc79a5d  security cookie failure path
    //   0xbc79a50  mov rcx,[rsp+0x40]
    //   0xbc79a55  xor rcx,rsp
    //   0xbc79a58  call 0xE951550
    //   0xbc79a5d  int3
    return;
    }

    // 0xbc797df..0xbc79864
    StreamFrame79790* P = ctx->stream;  // 0xbc797ed  mov rax,[rcx+0x1CFD0C8]
    {
        std::uint16_t c = P->freeListCount;  // 0xbc797f4  movzx ecx,word ptr [rax+0xE4B8AE]
        P->freeList[c] = savedIdx;           // 0xbc797fb  mov [rax+rcx*2+0xE498AE],dx
        ++P->freeListCount;                  // 0xbc79803  inc word ptr [rax+0xE4B8AE]
    }
    P = ctx->stream;  // 0xbc7980a  mov rbx,[rsi+0x1CFD0C8]
    std::uint8_t tag = 0x20;  // 0xbc79811  mov byte ptr [rsp+0x3F],0x20
    sub_ebce390(P->data + P->writePos, &tag, 1u);  // 0xbc79832  call 0xEBCE390   [`0xbc79832  call 0xEBCE390`]
    {
        std::uint32_t pos = P->writePos;  // 0xbc79837  mov eax,[rbx+0xE05820]
        pos = (pos & 0xFFFFFFFEu) + 2u;   // 0xbc7983d  and eax,0xFFFFFFFE ; 0xbc79840  add eax,2
        P->writePos = pos;                // 0xbc79843  mov [rbx+0xE05820],eax
        sub_ebce390(P->data + pos, &savedIdx, 2u);  // 0xbc7985f  call 0xEBCE390   [`0xbc7985f  call 0xEBCE390`]
    }
    P->writePos += 2u;  // 0xbc79864  add dword ptr [rbx+0xE05820],2

    // 0xbc7986b..0xbc798d8
    std::uint16_t slotCount = slot->count;  // 0xbc7986b  movzx ebx,word ptr [rdi+0x1E]
    if (slotCount != 0u) {  // 0xbc7986f  test rbx,rbx ; 0xbc79872  je short 0xBC798D8
        for (std::uint32_t r14 = 0u; r14 < slotCount; ++r14) {  // 0xbc79874  xor r14d,r14d ; 0xbc79890  inc r14 ; 0xbc79893  cmp rbx,r14 ; 0xbc79896  jne short 0xBC79880
            std::uint16_t v = static_cast<const std::uint16_t*>(slot->ptr)[r14];  // 0xbc79883  movzx edx,word ptr [rax+r14*2]
            sub_bc75c30(reinterpret_cast<Ctx*>(ctx), v);  // 0xbc7988b  call 0xBC75C30   [`0xbc7988b  call 0xBC75C30`]
        }
        void* g = *reinterpret_cast<void**>(0x12ADF800);  // 0xbc79898  mov rcx,[0x12ADF800]
        if (g != nullptr) {  // 0xbc7989f  test rcx,rcx ; 0xbc798a2  je short 0xBC798CB
            Eea6040Fn79790 fn = reinterpret_cast<Eea6040Fn79790>(
                *reinterpret_cast<void**>(0xF99FFA0));  // 0xbc798be  mov r10,[0xF99FFA0]
            fn(g, slot->ptr, 0u, 0u, 0ull, 0ull);  // 0xbc798c5  call qword ptr [0xF99FFA0]   [`0xbc798c5  call qword ptr [0xF99FFA0]`]
        } else {
            slot->ptr = *reinterpret_cast<void**>(0xF847A07);  // 0xbc798ce  lea rax,[0xF847A07] ; 0xbc798d5  mov [rbx],rax
        }
        slot->ptr = nullptr;  // 0xbc798cb  mov qword ptr [rdi],0
        slot->count = 0u;     // 0xbc798d2  mov word ptr [rdi+0x1E],0
    }

    // 0xbc798d8..0xbc798e1
    if (savedIdx == 0xFFFFu) {  // 0xbc798dd  cmp ax,0xFFFF ; 0xbc798e1  je 0xBC797BD
        return;
    }

    // 0xbc798e7..0xbc79a4b hash-set delete
    std::uint16_t* entries = ctx->entries;  // 0xbc798e7  lea rcx,[rsi+0x1E28AB0]
    std::uint32_t* aux = ctx->aux;          // aux base [rsi+0x1E20AB0]
    std::uint32_t r8 = ctx->hashCount;      // 0xbc798ee  mov r8d,[rsi+0x1E20AAC]
    std::uint32_t rdx = 0u;                 // 0xbc798f5  xor edx,edx

scan_top:  // 0xbc79910
    if (entries[rdx] != savedIdx) {  // 0xbc79910  cmp [rcx+rdx*2],ax ; 0xbc79914  jne short 0xBC79900
        ++rdx;  // 0xbc79900  inc rdx
        if (rdx == 0x2000u) {  // 0xbc79903  cmp rdx,0x2000 ; 0xbc7990a  je 0xBC797BD
            return;
        }
        goto scan_top;
    }

found:  // 0xbc79916
    entries[rdx] = 0xFFFFu;  // 0xbc79916  mov word ptr [rsi+rdx*2+0x1E28AB0],0xFFFF
    --r8;                     // 0xbc79920  dec r8d
    ctx->hashCount = r8;      // 0xbc79923  mov [rsi+0x1E20AAC],r8d
    ++rdx;                    // 0xbc7992a  inc rdx
    std::uint32_t edi = rdx & 0x1FFFu;  // 0xbc7992d  mov edi,edx ; 0xbc7992f  and edi,0x1FFF
    std::uint16_t r10 = entries[edi];    // 0xbc79939  movzx r10d,word ptr [rsi+r11+0x1E28AB0]
    if (r10 == 0xFFFFu) {  // 0xbc79942  cmp r10w,0xFFFF ; 0xbc79947  je short 0xBC79903
        if (rdx == 0x2000u) return;  // 0xbc79903
        goto scan_top;
    }
    std::uint16_t* r11p = &entries[edi];  // 0xbc79949  add r11,rcx
    (void)r11p;
    std::uint32_t r9 = rdx & 0x1FFFu;  // 0xbc7994c  mov r9d,edx ; 0xbc7994f  and r9d,0x1FFF

cascade:  // 0xbc79999
    {
        std::uint32_t ediVal = aux[edi];  // 0xbc79999  mov edi,[rsi+rdi*4+0x1E20AB0]
        std::uint32_t ebx = (ediVal * kHashMul1);
        ebx >>= kHashShift;
        ebx *= kHashMul2;
        ebx &= kHashMask;
        std::uint32_t r14 = ebx;
        // 0xbc799c0..0xbc799e4
        for (;;) {
            if (entries[r14] == 0xFFFFu) goto at_a00;  // 0xbc799c3  je short 0xBC79A00
            if (aux[r14] == ediVal) {  // 0xbc799cb  cmp [rsi+r14*4+0x1E20AB0],edi ; 0xbc799d3  je short 0xBC799F0
                if (r9 == r14) goto continue_scan;  // 0xbc799f0  cmp r9d,r14d ; 0xbc799f3  je short 0xBC79978
                goto at_a00;
            }
            ++r14;  // 0xbc799d5  inc r14d
            r14 &= 0x1FFFu;  // 0xbc799d8  and r14d,0x1FFF
            if (r14 == ebx) goto at_a00;  // 0xbc799df  cmp r14d,ebx ; 0xbc799e2  jne short 0xBC799C0 ; 0xbc799e4  jmp short 0xBC79A00
        }
    at_a00:  // 0xbc79a00
        entries[edi] = 0xFFFFu;  // 0xbc79a00  mov word ptr [r11],0xFFFF
        std::uint32_t r11d = r8 - 1u;  // 0xbc79a06  lea r11d,[r8-1]
        ctx->hashCount = r11d;          // 0xbc79a0a  mov [rsi+0x1E20AAC],r11d
        r14 = ebx;  // 0xbc79a11  mov r14d,ebx
        // 0xbc79a20..0xbc79a46
        for (;;) {
            if (entries[r14] == 0xFFFFu) goto at_960;  // 0xbc79a23  je 0xBC79960
            if (aux[r14] == ediVal) goto at_a48;      // 0xbc79a2f  cmp ... ; 0xbc79a37  je short 0xBC79A48
            ++r14;  // 0xbc79a39  inc r14d
            r14 &= 0x1FFFu;  // 0xbc79a3c  and r14d,0x1FFF
            if (r14 == ebx) goto at_a48;  // 0xbc79a43  cmp r14d,ebx ; 0xbc79a46  jne short 0xBC79A20
        }
    at_960:  // 0xbc79960
        aux[r14] = ediVal;  // 0xbc79960  mov [rsi+r14*4+0x1E20AB0],edi
        entries[r14] = r10; // 0xbc79968  mov [rsi+r14*2+0x1E28AB0],r10w
        ctx->hashCount = r8; // 0xbc79971  mov [rsi+0x1E20AAC],r8d
        goto continue_scan;
    at_a48:  // 0xbc79a48
        r8 = r11d;  // 0xbc79a48  mov r8d,r11d
        goto continue_scan;
    continue_scan:  // 0xbc79978
        ++r9;  // 0xbc79978  inc r9d
        r9 &= 0x1FFFu;  // 0xbc7997b  and r9d,0x1FFF
        r10 = entries[r9];  // 0xbc79986  movzx r10d,word ptr [rcx+r9*2]
        edi = r9;  // 0xbc7998b  mov rdi,r9
        if (r10 == 0xFFFFu) {  // 0xbc7998e  cmp r10w,0xFFFF ; 0xbc79993  je 0xBC79903
            if (rdx == 0x2000u) return;  // 0xbc79903
            goto scan_top;
        }
        r11p = &entries[edi];
        goto cascade;
    }
}

LIFT_FN(sub_bc79790, "native::sub_bc79790", 0xbc79790, sub_bc79790, nullptr);

} // namespace native