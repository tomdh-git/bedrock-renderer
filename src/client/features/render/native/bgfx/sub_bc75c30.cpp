// LIFT 0xbc75c30 size 0x2a9 1.26.62.01 sub_bc75c30
#include "sub_bc75c30.h"
#include "client/features/render/native/Lift.h"

namespace native {

// Lifted body of sub 0xbc75c30 (size 0x2a9, 0xbc75c30..0xbc75ed9), 1.26.62.01.
// Same reads, same writes (value and order), same calls in the same order,
// same return (void) as the exe function. Each block carries the instruction
// range it implements; every call is quoted verbatim beside the call site.
//
// Calls out:
//   0xbc75c5c  call 0xEBDBF10    sub_ebdbf10(lock)             [lift, forward-declared]
//   0xbc75cdc  call r10          via data slot 0xF99FFA0       [vendor sub_eea6040, rule 69]
//   0xbc75e86  call 0xEBCE390    sub_ebce390(dst,&tag,1)       [lift]
//   0xbc75eb2  call 0xEBCE390    sub_ebce390(dst,&savedIdx,2)  [lift]
//   0xbc75ec6  call 0xEBDBF20    sub_ebdbf20(lock)             [lift, every path]

extern "C" void sub_bc75c30(Ctx* ctx, std::uint16_t idx) {
    // 0xbc75c30..0xbc75c70: prologue (pushes, sub rsp,0x48, frame cookie),
    //   lock = ctx + 0x1C0 (lea, no load), sub_ebdbf10(lock),
    //   savedIdx = idx (spilled to [rbp-4]),
    //   slot = slot object at ctx + 0x1E1DAA8 + idx*0x18,
    //   --slot->refCount (ctx + 0x1E1DABE + idx*0x18); nonzero -> epilogue.
    //   0xbc75c30  push rbp
    //   0xbc75c31  push r15
    //   0xbc75c33  push r14
    //   0xbc75c35  push rsi
    //   0xbc75c36  push rdi
    //   0xbc75c37  push rbx
    //   0xbc75c38  sub rsp,0x48
    //   0xbc75c3c  lea rbp,[rsp+0x40]
    //   0xbc75c41  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
    //   0xbc75c49  mov edi,edx
    //   0xbc75c4b  mov rsi,rcx
    //   0xbc75c4e  mov [rbp-4],dx
    //   0xbc75c52  lea rbx,[rcx+0x1C0]
    //   0xbc75c59  mov rcx,rbx
    //   0xbc75c5c  call 0xEBDBF10        ; -> sub_ebdbf10
    //   0xbc75c61  movzx eax,di
    //   0xbc75c64  lea rax,[rax+rax*2]
    //   0xbc75c68  dec word ptr [rsi+rax*8+0x1E1DABE]
    //   0xbc75c70  jne 0xBC75EC3        ; -> loc_bc75ec3
    void* lock = &ctx->lockField;                         // 0xbc75c52  lea rbx,[rcx+0x1C0]
    sub_ebdbf10(lock);                                    // 0xbc75c5c  call 0xEBDBF10   [`0xbc75c5c  call 0xEBDBF10`]
    std::uint16_t savedIdx = idx;                         // 0xbc75c4e  mov [rbp-4], dx
    SlotObject* slot = reinterpret_cast<SlotObject*>(
        reinterpret_cast<char*>(ctx) + kSlotObjectBase +
        static_cast<std::size_t>(idx) * kSlotObjectStride);  // 0xbc75c97  lea rbx,[rsi+rax*8]
                                                            // 0xbc75c9b  add rbx,0x1E1DAA8
    --slot->refCount;                                     // 0xbc75c68  dec word ptr [slot+0x16]
    if (slot->refCount != 0u) {                           // 0xbc75c70  jne 0xBC75EC3
        // 0xbc75ec3..0xbc75ed9: epilogue (shared with the fall-through path)
        //   0xbc75ec3  mov rcx,rbx        ; rbx = [rbp-0x10] = lock
        //   0xbc75ec6  call 0xEBDBF20     ; -> sub_ebdbf20
        //   0xbc75ecc  add rsp,0x48
        //   0xbc75ed0  pop rbx
        //   0xbc75ed1  pop rdi
        //   0xbc75ed2  pop rsi
        //   0xbc75ed3  pop r14
        //   0xbc75ed5  pop r15
        //   0xbc75ed7  pop rbp
        //   0xbc75ed8  ret
        sub_ebdbf20(lock);                                // 0xbc75ec6  call 0xEBDBF20   [`0xbc75ec6  call 0xEBDBF20`]
        return;
    }

    // 0xbc75c76..0xbc75ce0: reference count reached zero; append idx to the
    //   free list at P + 0xE509DC (P = ctx->stream, count at P + 0xE50DDC).
    //   0xbc75c76  mov [rbp-0x10],rbx                ; save lock
    //   0xbc75c7a  mov rcx,[rsi+0x1CFD0C8]           ; P = ctx->stream
    //   0xbc75c81  movzx edx,word ptr [rcx+0xE50DDC] ; count = P->freeListCount
    //   0xbc75c88  mov [rcx+rdx*2+0xE509DC],di       ; P->freeList[count] = idx
    //   0xbc75c90  inc word ptr [rcx+0xE50DDC]       ; ++P->freeListCount
    StreamFrame* P = ctx->stream;                       // 0xbc75c7a  mov rcx,[rsi+0x1CFD0C8]
    P->freeList[P->freeListCount] = idx;                // 0xbc75c88  mov [rcx+rdx*2+0xE509DC],di
    ++P->freeListCount;                                 // 0xbc75c90  inc word ptr [rcx+0xE50DDC]

    //   0xbc75c97  lea rbx,[rsi+rax*8]
    //   0xbc75c9b  add rbx,0x1E1DAA8
    //   0xbc75ca2  cmp dword ptr [rbx+8],0
    //   0xbc75ca6  je short 0xBC75CF1    ; -> loc_bc75cf1   (slot->flag == 0 -> skip)
    if (slot->flag != 0u) {                               // 0xbc75ca2  cmp dword ptr [slot+8],0
                                                          // 0xbc75ca6  je short 0xBC75CF1
        //   0xbc75ca8  mov rcx,[0x12ADF800]          ; g = data_12adf800
        //   0xbc75caf  test rcx,rcx
        //   0xbc75cb2  je short 0xBC75CE0            ; -> loc_bc75ce0   (g == 0 -> default state)
        void* g = *reinterpret_cast<void**>(0x12ADF800);  // 0xbc75ca8  mov rcx,[0x12ADF800]
        if (g != nullptr) {                             // 0xbc75caf  test rcx,rcx
                                                          // 0xbc75cb2  je short 0xBC75CE0
            // 0xbc75cb4..0xbc75cdf: call the loader-resolved thunk via data
            //   slot 0xF99FFA0 ([data_f99ffa0] = sub_eea6040, rule 69).
            //   0xbc75cb4  mov rdx,[rbx]             ; rdx = slot->ptr
            //   0xbc75cb7  mov rax,[rcx]             ; (dead read of g->vtable[1])
            //   0xbc75cba  mov rax,[rax+8]
            //   0xbc75cbe  mov r10,[0xF99FFA0]       ; r10 = thunk pointer
            //   0xbc75cc5  mov dword ptr [rsp+0x28],0
            //   0xbc75ccd  mov qword ptr [rsp+0x20],0
            //   0xbc75cd6  xor r8d,r8d
            //   0xbc75cd9  xor r9d,r9d
            //   0xbc75cdc  call r10                  ; -> sub_eea6040 via slot
            Eea6040Fn eea6040 = reinterpret_cast<Eea6040Fn>(
                *reinterpret_cast<void**>(0xF99FFA0));  // 0xbc75cbe  mov r10,[0xF99FFA0]
            eea6040(g, slot->ptr, 0u, 0u, 0ull, 0ull);  // 0xbc75cdc  call r10   [`0xbc75cdc  call r10`]
        } else {
            // 0xbc75ce0..0xbc75cea: g == 0 -> reset the slot to the default
            //   pointer at data 0xF847A07 and clear the flag.
            //   0xbc75ce0  lea rax,[0xF847A07]       ; [data_f847a07]
            //   0xbc75ce7  mov [rbx],rax             ; slot->ptr = data_f847a07
            //   0xbc75cea  mov dword ptr [rbx+8],0  ; slot->flag = 0
            slot->ptr = *reinterpret_cast<void**>(0xF847A07);  // 0xbc75ce7  mov [rbx],rax
            slot->flag = 0u;                                   // 0xbc75cea  mov dword ptr [rbx+8],0
        }
    }

    // 0xbc75cf1..0xbc75e60: open-addressing hash-set delete of key idx from
    //   entries[] at ctx + 0x1E1D2A4 (keys, empty 0xFFFF), with aux[] at
    //   ctx + 0x1E1C2A4 and count at ctx + 0x1E1C2A0, capacity 0x400.
    //   hash(v) = ((v * 0x5EBCA77) >> 0x13) * 0x1B1 & 0x3FF.
    //   Skipped entirely when idx == 0xFFFF (0xbc75cf5  je 0xBC75E60).
    //   On a hit at k: entries[k] = 0xFFFF, count--, then rehash/drop the
    //   following occupied cluster (j = k+1, j+1, ... up to the first empty
    //   slot) by probing from hash(aux[slot]); the scan then continues at k+1.
    //   0xbc75cf1  cmp di,0xFFFF
    //   0xbc75cf5  je 0xBC75E60          ; -> loc_bc75e60
    //   0xbc75cfb  lea rax,[rsi+0x1E1D2A4]   ; rax = &entries[0]
    //   0xbc75d02  mov edx,[rsi+0x1E1C2A0]   ; edx = count
    //   0xbc75d08  xor ecx,ecx             ; k = 0
    //   0xbc75d0a  jmp short 0xBC75D20
    //   0xbc75d0c  nop [rax]               ; R a0+0x1E1D2A4+0x0
    if (idx != 0xFFFFu) {
        std::uint16_t* entries = ctx->entries;
        std::uint32_t* aux = ctx->aux;
        const std::uint32_t count = ctx->entryCount;  // 0xbc75d02  mov edx,[rsi+0x1E1C2A0]
        std::uint32_t k = 0;                          // 0xbc75d08  xor ecx,ecx
        for (;;) {                                    // 0xbc75d0a  jmp short 0xBC75D20
            // 0xbc75d20  cmp [rax+rcx*2],di
            // 0xbc75d24  jne short 0xBC75D10
            while (entries[k] != idx) {
                ++k;                                  // 0xbc75d10  inc rcx
                // 0xbc75d13  cmp rcx,0x400
                // 0xbc75d1a  je 0xBC75E60            ; -> loc_bc75e60
                if (k == kHashCapacity) goto doneHash;
            }
            // 0xbc75d26  mov word ptr [rsi+rcx*2+0x1E1D2A4],0xFFFF
            // 0xbc75d30  dec edx
            // 0xbc75d32  mov [rsi+0x1E1C2A0],edx     ; count = N - 1
            // 0xbc75d38  inc rcx                     ; j = k + 1
            entries[k] = kHashEmpty;
            ctx->entryCount = count - 1u;
            ++k;
            // 0xbc75d3b  mov r11d,ecx
            // 0xbc75d3e  and r11d,0x3FF              ; q = (k + 1) & 0x3FF
            // 0xbc75d45  lea r10d,[r11+r11]
            // 0xbc75d49  movzx r9d,word ptr [rsi+r10+0x1E1D2A4]   ; keyQ = entries[q]
            // 0xbc75d52  cmp r9w,0xFFFF
            // 0xbc75d57  je short 0xBC75D13          ; -> loc_bc75d13 (empty -> scan continues)
            std::uint32_t q = k & 0x3FFu;
            while (entries[q] != kHashEmpty) {        // 0xbc75d87..0xbc75da2 (occupied -> rehash/drop)
                // 0xbc75da8  mov r11d,[rsi+r11*4+0x1E1C2A4]   ; v2 = aux[q]
                // 0xbc75db0  imul ebx,r11d,0x5EBCA77
                // 0xbc75db7  shr ebx,0x13
                // 0xbc75dba  imul ebx,0x1B1
                // 0xbc75dc0  and ebx,0x3FF              ; h2 = hash(v2)
                // 0xbc75dc6  mov r14d,ebx
                const std::uint32_t v2 = aux[q];
                const std::uint32_t h2 = hashAux(v2);
                const std::uint16_t keyQ = entries[q];
                bool kept = false;
                // 0xbc75dd0  mov r15d,r14d            ; p = h2
                // 0xbc75dd3  cmp word ptr [rax+r15*2],0xFFFF
                // 0xbc75dd9  je short 0xBC75E10      ; -> loc_bc75e10 (empty -> free q)
                // 0xbc75ddb  cmp [rsi+r15*4+0x1E1C2A4],r11d
                // 0xbc75de3  je short 0xBC75E00      ; -> loc_bc75e00 (aux[p] == v2)
                // 0xbc75de5  inc r14d
                // 0xbc75de8  and r14d,0x3FF
                // 0xbc75def  cmp r14d,ebx
                // 0xbc75df2  jne short 0xBC75DD0
                // 0xbc75df4  jmp short 0xBC75E10     ; full cycle -> free q
                // 0xbc75e00  cmp r8d,r14d            ; p == q?
                // 0xbc75e03  je short 0xBC75D87      ; yes -> keep q
                std::uint32_t p = h2;
                for (;;) {
                    if (entries[p] == kHashEmpty) goto freeQ;
                    if (aux[p] == v2) {
                        if (p == q) {
                            kept = true;
                            break;
                        }
                        goto freeQ;
                    }
                    p = (p + 1u) & 0x3FFu;
                    if (p == h2) goto freeQ;
                }
                if (kept) {                            // 0xbc75d87
                    q = (q + 1u) & 0x3FFu;
                    continue;
                }
              freeQ:;
                // 0xbc75e10  mov word ptr [r10],0xFFFF   ; entries[q] = 0xFFFF
                // 0xbc75e16  lea r10d,[rdx-1]            ; intermediate N - 2
                // 0xbc75e1a  mov [rsi+0x1E1C2A0],r10d
                entries[q] = kHashEmpty;
                // 0xbc75e30  mov r15d,r14d            ; p = h2 (probe 2)
                // 0xbc75e33  cmp word ptr [rax+r15*2],0xFFFF
                // 0xbc75e39  je 0xBC75D70            ; -> loc_bc75d70 (empty -> place q's entry)
                // 0xbc75e3f  cmp [rsi+r15*4+0x1E1C2A4],r11d
                // 0xbc75e47  je short 0xBC75E58      ; -> loc_bc75e58 (aux match -> drop q)
                // 0xbc75e49  inc r14d
                // 0xbc75e4c  and r14d,0x3FF
                // 0xbc75e53  cmp r14d,ebx
                // 0xbc75e56  jne short 0xBC75E30
                // 0xbc75e58  mov edx,r10d            ; N - 2 -> 0xbc75d81
                // 0xbc75d70  mov [rsi+r15*4+0x1E1C2A4],r11d   ; aux[p] = v2
                // 0xbc75d78  mov [rsi+r15*2+0x1E1D2A4],r9w      ; entries[p] = keyQ
                // 0xbc75d81  mov [rsi+0x1E1C2A0],edx          ; count
                p = h2;
                bool relocated = false;
                for (;;) {
                    if (entries[p] == kHashEmpty) {
                        aux[p] = v2;
                        entries[p] = keyQ;
                        ctx->entryCount = count - 1u;  // stale edx = N - 1
                        relocated = true;
                        break;
                    }
                    if (aux[p] == v2) goto dropQ;
                    p = (p + 1u) & 0x3FFu;
                    if (p == h2) goto dropQ;
                }
                if (relocated) {
                    q = (q + 1u) & 0x3FFu;             // 0xbc75d87
                    continue;
                }
              dropQ:;
                // 0xbc75e58/0xbc75d81: q dropped without reinsert; count = N - 2
                ctx->entryCount = count - 2u;
                q = (q + 1u) & 0x3FFu;                 // 0xbc75d87
            }
            // 0xbc75d13: cascade exit (entries[q] empty); i == 0x400 -> tail
            // 0xbc75d13  cmp rcx,0x400
            // 0xbc75d1a  je 0xBC75E60
            if (k == kHashCapacity) goto doneHash;
        }
      doneHash:;
    }

    // 0xbc75e60..0xbc75ec3: append a stream record: tag byte 0x25, then the
    //   saved index as a u16. P = ctx->stream (reloaded), pos = P->writePos.
    //   0xbc75e60  mov rsi,[rsi+0x1CFD0C8]          ; P = ctx->stream (reload)
    //   0xbc75e67  mov byte ptr [rbp-1],0x25
    //   0xbc75e6b  mov eax,[rsi+0xE05820]           ; pos = P->writePos
    //   0xbc75e71  lea rcx,[rsi+rax]
    //   0xbc75e75  add rcx,0xE05828                 ; &P->data[pos]
    //   0xbc75e7c  lea rdx,[rbp-1]                  ; &tag
    //   0xbc75e80  mov r8d,1
    //   0xbc75e86  call 0xEBCE390                   ; -> sub_ebce390(&P->data[pos], &tag, 1)
    //   0xbc75e8b  nop
    //   0xbc75e8c  lea rax,[rsi+0xE05828]
    //   0xbc75e93  mov ecx,[rsi+0xE05820]           ; pos reloaded
    //   0xbc75e99  and ecx,0xFFFFFFFE
    //   0xbc75e9c  add ecx,2
    //   0xbc75e9f  mov [rsi+0xE05820],ecx           ; P->writePos = (pos & ~1) + 2
    //   0xbc75ea5  add rcx,rax                      ; &P->data[newPos]
    //   0xbc75ea8  lea rdx,[rbp-4]                  ; &savedIdx
    //   0xbc75eac  mov r8d,2
    //   0xbc75eb2  call 0xEBCE390                   ; -> sub_ebce390(&P->data[newPos], &savedIdx, 2)
    //   0xbc75eb7  nop
    //   0xbc75eb8  add dword ptr [rsi+0xE05820],2   ; P->writePos += 2
    //   0xbc75ebf  mov rbx,[rbp-0x10]               ; rbx = lock
    P = ctx->stream;                                  // 0xbc75e60  mov rsi,[rsi+0x1CFD0C8]
    std::uint8_t tag = kStreamTag;                    // 0xbc75e67  mov byte ptr [rbp-1],0x25
    sub_ebce390(P->data + P->writePos, &tag, 1u);     // 0xbc75e86  call 0xEBCE390   [`0xbc75e86  call 0xEBCE390`]
    std::uint32_t c = P->writePos;                    // 0xbc75e93  mov ecx,[rsi+0xE05820]
    c = (c & 0xFFFFFFFEu) + 2u;                       // 0xbc75e99  and ecx,0xFFFFFFFE ; 0xbc75e9c  add ecx,2
    P->writePos = c;                                  // 0xbc75e9f  mov [rsi+0xE05820],ecx
    sub_ebce390(P->data + c, &savedIdx, 2u);          // 0xbc75eb2  call 0xEBCE390   [`0xbc75eb2  call 0xEBCE390`]
    P->writePos = c + 2u;                             // 0xbc75eb8  add dword ptr [rsi+0xE05820],2

    // 0xbc75ec3..0xbc75ed9: epilogue: sub_ebdbf20(lock), restore registers, ret.
    //   0xbc75ec3  mov rcx,rbx
    //   0xbc75ec6  call 0xEBDBF20        ; -> sub_ebdbf20
    //   0xbc75ecb  nop
    //   0xbc75ecc  add rsp,0x48
    //   0xbc75ed0  pop rbx
    //   0xbc75ed1  pop rdi
    //   0xbc75ed2  pop rsi
    //   0xbc75ed3  pop r14
    //   0xbc75ed5  pop r15
    //   0xbc75ed7  pop rbp
    //   0xbc75ed8  ret
    sub_ebdbf20(lock);                                // 0xbc75ec6  call 0xEBDBF20   [`0xbc75ec6  call 0xEBDBF20`]
    return;
}

static std::uint32_t hashAux(std::uint32_t v) {       // 0xbc75db0..0xbc75dc6
    // 0xbc75db0  imul ebx,r11d,0x5EBCA77
    // 0xbc75db7  shr ebx,0x13
    // 0xbc75dba  imul ebx,0x1B1
    // 0xbc75dc0  and ebx,0x3FF
    std::uint32_t h = v * kHashMul1;
    h >>= kHashShift;
    h *= kHashMul2;
    h &= kHashMask;
    return h;
}

static_assert(offsetof(Ctx, lockField) == 0x1C0, "sub_bc75c30: Ctx+0x1C0 lockField");
static_assert(offsetof(Ctx, stream) == 0x1CFD0C8, "sub_bc75c30: Ctx+0x1CFD0C8 stream");
static_assert(offsetof(Ctx, entryCount) == 0x1E1C2A0, "sub_bc75c30: Ctx+0x1E1C2A0 entryCount");
static_assert(offsetof(Ctx, aux) == 0x1E1C2A4, "sub_bc75c30: Ctx+0x1E1C2A4 aux");
static_assert(offsetof(Ctx, entries) == 0x1E1D2A4, "sub_bc75c30: Ctx+0x1E1D2A4 entries");
static_assert(offsetof(StreamFrame, writePos) == 0xE05820, "sub_bc75c30: StreamFrame+0xE05820 writePos");
static_assert(offsetof(StreamFrame, data) == 0xE05828, "sub_bc75c30: StreamFrame+0xE05828 data");
static_assert(offsetof(StreamFrame, freeList) == 0xE509DC, "sub_bc75c30: StreamFrame+0xE509DC freeList");
static_assert(offsetof(StreamFrame, freeListCount) == 0xE50DDC, "sub_bc75c30: StreamFrame+0xE50DDC freeListCount");
static_assert(offsetof(SlotObject, refCount) == 0x16, "sub_bc75c30: SlotObject+0x16 refCount");

LIFT_FN(sub_bc75c30, "native::sub_bc75c30", 0xbc75c30, sub_bc75c30, nullptr);

} // namespace native
