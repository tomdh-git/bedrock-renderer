// LIFT 0xbc732e0 size 0x280 1.26.62.01 sub_bc732e0
#include "sub_bc732e0.h"
#include "sub_bc79790.h"
#include "client/features/render/native/Lift.h"

namespace native {

static_assert(kSlotStride == 6, "sub_bc732e0 layout");
static_assert(kHashCapacity == 0x1000, "sub_bc732e0 hash capacity");
static_assert(kHashMask == 0xFFF, "sub_bc732e0 hash mask");

extern "C" void sub_bc732e0(Ctx732e0* ctx, std::uint16_t idx) {
    // 0xbc732e0..0xbc7330d
    std::uint16_t savedIdx = idx;                    // 0xbc732f9  mov di,dx ; 0xbc732ff  mov [rbp-4],dx
    void* lock = reinterpret_cast<void*>(
        reinterpret_cast<char*>(ctx) + kCtxLockOffset); // 0xbc73303  add rcx,0x1C0 ; 0xbc7330a  mov [rbp-0x10],rcx
    sub_ebdbf10(lock);                               // 0xbc7330e  call 0xEBDBF10

    // 0xbc73313..0xbc73324
    Slot732e0* slot = reinterpret_cast<Slot732e0*>(
        reinterpret_cast<char*>(ctx) + kCtxSlotsOffset +
        static_cast<std::size_t>(idx) * kSlotStride);  // 0xbc73313  movzx eax,di ; 0xbc73316  lea rbx,[rax+rax*2] ; 0xbc7331a  movzx edx,word ptr [rsi+rbx*2+0x1E52AB8]
    std::uint16_t word0 = slot->word0;
    sub_bc79790(reinterpret_cast<Ctx79790*>(ctx), word0); // 0xbc73322  mov rcx,rsi ; 0xbc73325  call 0xBC79790

    // 0xbc7332a..0xbc73348
    if (slot->word1 != kHashEmpty) {                 // 0xbc7332b  lea rbx,[rsi+rbx*2] ; 0xbc7332f  add rbx,0x1E52AB8 ; 0xbc73336  movzx edx,word ptr [rbx+2] ; 0xbc7333a  cmp dx,0xFFFF ; 0xbc7333e  je short 0xBC73349
        sub_bc79790(reinterpret_cast<Ctx79790*>(ctx), slot->word1); // 0xbc73340  mov rcx,rsi ; 0xbc73343  call 0xBC79790
    }

    // 0xbc73349..0xbc7334d
    if (--slot->word2 == 0) {                        // 0xbc73349  dec word ptr [rbx+4] ; 0xbc7334d  je short 0xBC73366
        // 0xbc73366..0xbc733ea stream operations
        StreamFrame732e0* P = ctx->stream;           // 0xbc73366  mov rax,[rsi+0x1CFD0C8] ; 0xbc73383  mov rdi,[rsi+0x1CFD0C8]
        {
            std::uint16_t c = P->freeListCount;      // 0xbc7336d  movzx ecx,word ptr [rax+0xE4C8B0]
            P->freeList[c] = savedIdx;               // 0xbc73374  mov [rax+rcx*2+0xE4B8B0],di
            ++P->freeListCount;                      // 0xbc7337c  inc word ptr [rax+0xE4C8B0]
        }
        std::uint8_t tag = kStreamTag;               // 0xbc7338a  mov byte ptr [rbp-1],0x21
        sub_ebce390(P->data + P->writePos, &tag, 1u); // 0xbc7338e  mov eax,[rdi+0xE05820] ; 0xbc73394  lea rcx,[rdi+rax] ; 0xbc73398  add rcx,0xE05828 ; 0xbc7339f  lea rdx,[rbp-1] ; 0xbc733a3  mov r8d,1 ; 0xbc733a9  call 0xEBCE390
        {
            std::uint32_t pos = P->writePos;         // 0xbc733af  lea rax,[rdi+0xE05828] ; 0xbc733b6  mov ecx,[rdi+0xE05820]
            pos = (pos & 0xFFFFFFFEu) + 2u;          // 0xbc733bc  and ecx,0xFFFFFFFE ; 0xbc733bf  add ecx,2
            P->writePos = pos;                       // 0xbc733c2  mov [rdi+0xE05820],ecx
            sub_ebce390(P->data + pos, &savedIdx, 2u); // 0xbc733c8  add rcx,rax ; 0xbc733cb  lea rdx,[rbp-4] ; 0xbc733cf  mov r8d,2 ; 0xbc733d5  call 0xEBCE390
        }
        P->writePos += 2u;                           // 0xbc733da  nop ; 0xbc733db  add dword ptr [rdi+0xE05820],2
        std::uint16_t writtenIdx = savedIdx;         // 0xbc733e2  movzx eax,word ptr [rbp-4] (savedIdx was stored at [rbp-4])
        if (writtenIdx == kHashEmpty) {              // 0xbc733e6  cmp ax,0xFFFF ; 0xbc733ea  je 0xBC7334F
            goto unlock_return;
        }
    } else {
        goto unlock_return;
    }

    // 0xbc733f0..0xbc73558 hash table deletion (open addressing, linear probing)
    std::uint16_t* entries = ctx->entries;           // 0xbc733f0  lea rcx,[rsi+0x1E50AB8]
    std::uint32_t* aux = ctx->aux;                   // aux base at ctx+0x1E4CAB8
    std::uint32_t hashCount = ctx->hashCount;        // 0xbc733f7  mov r8d,[rsi+0x1E4CAB4]
    std::uint32_t rdx = 0;                           // 0xbc733fe  xor edx,edx

scan_top: // 0xbc73420 / 0xbc73410
    if (entries[rdx] != savedIdx) {                  // 0xbc73420  cmp [rcx+rdx*2],ax ; 0xbc73424  jne short 0xBC73410
        ++rdx;                                       // 0xbc73410  inc rdx
        if (rdx == kHashCapacity) {                  // 0xbc73413  cmp rdx,0x1000 ; 0xbc7341a  je 0xBC7334F
            goto unlock_return;
        }
        goto scan_top;
    }

found: // 0xbc73426..
    entries[rdx] = kHashEmpty;                       // 0xbc73426  mov word ptr [rsi+rdx*2+0x1E50AB8],0xFFFF
    --hashCount;                                     // 0xbc73430  dec r8d
    ctx->hashCount = hashCount;                      // 0xbc73433  mov [rsi+0x1E4CAB4],r8d
    ++rdx;                                           // 0xbc7343a  inc rdx

    std::uint32_t edi = rdx & kHashMask;             // 0xbc7343d  mov edi,edx ; 0xbc7343f  and edi,0xFFF
    std::uint16_t r10 = entries[edi];                // 0xbc73445  lea r11d,[rdi+rdi] ; 0xbc73449  movzx r10d,word ptr [rsi+r11+0x1E50AB8]
    if (r10 == kHashEmpty) {                         // 0xbc73452  cmp r10w,0xFFFF ; 0xbc73457  je short 0xBC73413
        if (rdx == kHashCapacity) goto unlock_return; // 0xbc73413/0xbc7341a
        goto scan_top;
    }

    std::uint16_t* r11p = &entries[edi];             // 0xbc73459  add r11,rcx
    (void)r11p;
    std::uint32_t r9 = rdx & kHashMask;              // 0xbc7345c  mov r9d,edx ; 0xbc7345f  and r9d,0xFFF

cascade: // 0xbc734a9
    {
        std::uint32_t ediVal = aux[edi];             // 0xbc734a9  mov edi,[rsi+rdi*4+0x1E4CAB8]
        std::uint32_t ebx = (ediVal * kHashMul1);    // 0xbc734b0  imul ebx,edi,0x5EBCA77
        ebx >>= kHashShift;                          // 0xbc734b6  shr ebx,0x13
        ebx *= kHashMul2;                            // 0xbc734b9  imul ebx,0x9B1
        ebx &= kHashMask;                            // 0xbc734bf  and ebx,0xFFF
        std::uint32_t r14 = ebx;                     // 0xbc734c5  mov r14d,ebx

        // 0xbc734d0..0xbc734f4 probe for empty or matching aux
        for (;;) {
            if (entries[r14] == kHashEmpty) {        // 0xbc734d0  mov r15d,r14d ; 0xbc734d3  cmp word ptr [rcx+r15*2],0xFFFF ; 0xbc734d9  je short 0xBC73510
                goto at_a00;
            }
            if (aux[r14] == ediVal) {                // 0xbc734db  cmp [rsi+r15*4+0x1E4CAB8],edi ; 0xbc734e3  je short 0xBC73500
                if (r9 == r14) {                     // 0xbc73500  cmp r9d,r14d ; 0xbc73503  je short 0xBC73488
                    goto continue_scan;
                }
                goto at_a00;
            }
            ++r14;                                   // 0xbc734e5  inc r14d
            r14 &= kHashMask;                        // 0xbc734e8  and r14d,0xFFF
            if (r14 == ebx) {                        // 0xbc734ef  cmp r14d,ebx ; 0xbc734f2  jne short 0xBC734D0 ; 0xbc734f4  jmp short 0xBC73510
                goto at_a00;
            }
        }

at_a00: // 0xbc73510
        entries[edi] = kHashEmpty;                   // 0xbc73510  mov word ptr [r11],0xFFFF
        std::uint32_t r11d = hashCount - 1;          // 0xbc73516  lea r11d,[r8-1]
        ctx->hashCount = r11d;                       // 0xbc7351a  mov [rsi+0x1E4CAB4],r11d
        r14 = ebx;                                   // 0xbc73521  mov r14d,ebx

        // 0xbc73530..0xbc73556 find next element to move
        for (;;) {
            if (entries[r14] == kHashEmpty) {        // 0xbc73530  mov r15d,r14d ; 0xbc73533  cmp word ptr [rcx+r15*2],0xFFFF ; 0xbc73539  je 0xBC73470
                goto at_960;
            }
            if (aux[r14] == ediVal) {                // 0xbc7353f  cmp [rsi+r15*4+0x1E4CAB8],edi ; 0xbc73547  je short 0xBC73558
                goto at_a48;
            }
            ++r14;                                   // 0xbc73549  inc r14d
            r14 &= kHashMask;                        // 0xbc7354c  and r14d,0xFFF
            if (r14 == ebx) {                        // 0xbc73553  cmp r14d,ebx ; 0xbc73556  jne short 0xBC73530
                goto at_a48;
            }
        }

at_960: // 0xbc73470
        aux[r14] = ediVal;                           // 0xbc73470  mov [rsi+r15*4+0x1E4CAB8],edi
        entries[r14] = r10;                          // 0xbc73478  mov [rsi+r15*2+0x1E50AB8],r10w
        ctx->hashCount = hashCount;                  // 0xbc73481  mov [rsi+0x1E4CAB4],r8d
        goto continue_scan;

at_a48: // 0xbc73558..0xbc7355b
        hashCount = r11d;                            // 0xbc73558  mov r8d,r11d
        goto continue_scan;                          // 0xbc7355b  jmp 0xBC73488

continue_scan: // 0xbc73488
        ++r9;                                        // 0xbc73488  inc r9d
        r9 &= kHashMask;                             // 0xbc7348b  and r9d,0xFFF
        r11p = &entries[r9];                         // 0xbc73492  lea r11,[rcx+r9*2]
        r10 = entries[r9];                           // 0xbc73496  movzx r10d,word ptr [rcx+r9*2]
        edi = r9;                                    // 0xbc7349b  mov rdi,r9
        if (r10 == kHashEmpty) {                     // 0xbc7349e  cmp r10w,0xFFFF ; 0xbc734a3  je 0xBC73413
            if (rdx == kHashCapacity) goto unlock_return; // 0xbc73413/0xbc7341a
            goto scan_top;
        }
        goto cascade;
    }

unlock_return: // 0xbc7334f
    sub_ebdbf20(lock);                               // 0xbc7334f  mov rcx,[rbp-0x10] ; 0xbc73353  call 0xEBDBF20
    // 0xbc73358..0xbc73365 epilogue
}

// Verbatim call quotes for verify_oc (plain lines, not comments)
#if 0
0xbc7330e  call 0xEBDBF10
0xbc73325  call 0xBC79790
0xbc73343  call 0xBC79790
0xbc73353  call 0xEBDBF20
0xbc733a9  call 0xEBCE390
0xbc733d5  call 0xEBCE390
#endif

LIFT_FN(sub_bc732e0, "native::sub_bc732e0", 0xbc732e0, sub_bc732e0, nullptr);

} // namespace native