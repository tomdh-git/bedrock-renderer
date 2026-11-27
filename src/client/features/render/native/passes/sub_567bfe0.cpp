// LIFT 0x567bfe0 size 0xbd 1.26.62.01 sub_567bfe0
#include "sub_567bfe0.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstring>

namespace native {

// sub_567bfe0 (0x567bfe0, size 0xbd, 1.26.62.01, "VV frame-graph builder").
//
// Copies 0x48-byte records from [src, end) to dst, with a type-discriminated
// middle section selected by the index byte at chunk+0x30, and zeroes part of
// the source record when index <= 2. All targets of the jump table at
// data_f25cf78 are inline code within this function; there are no `call`
// instructions and no callees [V].
//
// Reads per iteration (chunk = rcx - 0x28): chunk+0x00(16B), chunk+0x10,
// chunk+0x18(8B, only index<=2), chunk+0x20(16B), chunk+0x30(index byte),
// chunk+0x38(8B), chunk+0x40(1B).
// Writes per iteration: dst+0x00(16B), dst+0x10, dst+0x20, dst+0x30,
// dst+0x38(8B), dst+0x40(1B); plus chunk+0x18(8B) and chunk+0x20(16B) zeroed
// when index <= 2.
// Return: void. Same reads, same writes, same (absence of) calls, same return.
// No null guards or SEH beyond the original's own tests [V].

// 0x567bfe0..0x567c09d
void sub_567bfe0(unsigned char* src, unsigned char* end, unsigned char* dst)
{
    // RCX = src (a0), RDX = end (a1), R8 = dst (a2). R9 (4th argument) unused [V].

    // 0x567bfe0  push rsi                                              (prologue; callee-saved scratch)
    // 0x567bfe1  mov rax,r8                                            ; rax = dst
    // 0x567bfe4  cmp rcx,rdx
    // 0x567bfe7  je 0x567C09B                                           ; src == end -> return
    if (src == end) {                                                    // 0x567bfe4  cmp rcx,rdx
        return;                                                          // 0x567bfe7  je 0x567C09B
    }
    // 0x567bfed  add rcx,0x28                                          ; rcx = src + 0x28
    // 0x567bff1  lea r8,[0xF25CF78]                                    ; jump table base
    // 0x567bff8  xorps xmm0,xmm0                                       ; xmm0 = 0
    // 0x567bffd  nop [rax]                                             ; padding (unreachable)
    // 0x567bffb  jmp short 0x567C046                                   ; loop top
    unsigned char* chunk = src;                                          // = rcx - 0x28
    unsigned char* wdst = dst;                                           // = rax
    goto loop_top;                                                       // 0x567bffb  jmp short 0x567C046

for (;;) {
loop_top:
    // 0x567c046  movups xmm1,[rcx-0x28]                                ; dst+0x00 = chunk+0x00 (16 B)
    // 0x567c04a  movups [rax],xmm1
    std::memcpy(wdst + kRecField0x00, chunk + kRecField0x00, 16);        // 0x567c046  movups xmm1,[rcx-0x28]
                                                                           // 0x567c04a  movups [rax],xmm1
    // 0x567c04d  mov byte ptr [rax+0x30],0xFF                          ; dst+0x30 = 0xFF (tentative)
    wdst[kRecField0x30] = 0xFF;                                          // 0x567c04d  mov byte ptr [rax+0x30],0xFF
    // 0x567c051  movzx r9d,byte ptr [rcx+8]                            ; index = chunk+0x30 (rcx = chunk+0x28)
    // 0x567c056  cmp r9,6
    // 0x567c05a  ja short 0x567C020                                    ; index > 6: skip table path
    unsigned char index = chunk[kRecField0x30];                          // 0x567c051  movzx r9d,byte ptr [rcx+8]
    if (index <= 6) {                                                    // 0x567c056  cmp r9,6 / 0x567c05a  ja short 0x567C020
        // 0x567c05c  lea r10,[rax+0x10]                                ; r10 = dst+0x10
        // 0x567c060  lea r11,[rcx-0x18]                                ; r11 = chunk+0x10
        unsigned char* r10 = wdst + kRecField0x10;
        unsigned char* r11 = chunk + kRecField0x10;
        // 0x567c064  movsxd rsi,[r8+r9*4]                              ; table entry (int32)
        // 0x567c068  add rsi,r8                                        ; target = table + entry
        // 0x567c06b  jmp rsi                                            ; tail jump to inline target
        switch (index) {
        // index 0..2 -> 0x567c000
        case 0:
        case 1:
        case 2: {                                                        // 0x567c06b  jmp rsi (to 0x567c000)
            // 0x567c000  movups xmm1,[rcx-0x18]                        ; chunk+0x10 (16 B)
            // 0x567c004  movups xmm2,[rcx-8]                           ; chunk+0x20 (16 B)
            // 0x567c014  movups [rax+0x10],xmm1                        ; dst+0x10 = chunk+0x10
            // 0x567c018  movups [rax+0x20],xmm2                        ; dst+0x20 = chunk+0x20
            std::memcpy(r10, r11, 16);                                   // 0x567c000  movups xmm1,[rcx-0x18]
                                                                           // 0x567c014  movups [rax+0x10],xmm1
            std::memcpy(wdst + kRecField0x20, chunk + kRecField0x20, 16);// 0x567c004  movups xmm2,[rcx-8]
                                                                           // 0x567c018  movups [rax+0x20],xmm2
            // 0x567c008  mov qword ptr [rcx-0x10],0                    ; zero chunk+0x18 (8 B)
            // 0x567c010  movups [rcx-8],xmm0                           ; zero chunk+0x20 (16 B)
            std::memset(chunk + kRecField0x18, 0, 8);                    // 0x567c008  mov qword ptr [rcx-0x10],0
            std::memset(chunk + kRecField0x20, 0, 16);                   // 0x567c010  movups [rcx-8],xmm0
            goto l567c01c;                                               // 0x567c01c  mov [rax+0x30],r9b (falls through)
        }
        // index 3 -> 0x567c06D
        case 3: {                                                        // 0x567c06b  jmp rsi (to 0x567c06D)
            // 0x567c06d  movups xmm1,[r11]                             ; chunk+0x10 (16 B)
            // 0x567c071  movups xmm2,[r11+0x10]                        ; chunk+0x20 (16 B)
            // 0x567c076  movups [r10+0x10],xmm2                        ; dst+0x20 = chunk+0x20
            // 0x567c07b  movups [r10],xmm1                             ; dst+0x10 = chunk+0x10
            std::memcpy(wdst + kRecField0x20, chunk + kRecField0x20, 16);// 0x567c071  movups xmm2,[r11+0x10]
                                                                           // 0x567c076  movups [r10+0x10],xmm2
            std::memcpy(r10, r11, 16);                                   // 0x567c06d  movups xmm1,[r11]
                                                                           // 0x567c07b  movups [r10],xmm1
            goto l567c01c;
        }
        // index 4 -> 0x567c081
        case 4: {                                                        // 0x567c06b  jmp rsi (to 0x567c081)
            // 0x567c081  movzx r11d,word ptr [r11]                     ; chunk+0x10 (2 B)
            // 0x567c085  mov [r10],r11w                                ; dst+0x10 (2 B)
            *reinterpret_cast<std::uint16_t*>(r10) =
                *reinterpret_cast<std::uint16_t*>(r11);                  // 0x567c081  movzx r11d,word ptr [r11]
                                                                           // 0x567c085  mov [r10],r11w
            goto l567c01c;
        }
        // index 5 -> 0x567c08B
        case 5: {                                                        // 0x567c06b  jmp rsi (to 0x567c08B)
            // 0x567c08b  mov r11d,[r11]                                 ; chunk+0x10 (4 B)
            // 0x567c08e  mov [r10],r11d                                ; dst+0x10 (4 B)
            *reinterpret_cast<std::uint32_t*>(r10) =
                *reinterpret_cast<std::uint32_t*>(r11);                  // 0x567c08b  mov r11d,[r11]
                                                                           // 0x567c08e  mov [r10],r11d
            goto l567c01c;
        }
        // index 6 -> 0x567c093
        case 6: {                                                        // 0x567c06b  jmp rsi (to 0x567c093)
            // 0x567c093  mov r11,[r11]                                  ; chunk+0x10 (8 B)
            // 0x567c096  mov [r10],r11                                 ; dst+0x10 (8 B)
            *reinterpret_cast<std::uint64_t*>(r10) =
                *reinterpret_cast<std::uint64_t*>(r11);                  // 0x567c093  mov r11,[r11]
                                                                           // 0x567c096  mov [r10],r11
            goto l567c01c;
        }
        }
    }
    // index > 6 skips the table path: dst+0x30 stays 0xFF, loc_567c01c is
    // not reached, fall straight to loc_567c020.

l567c01c:
    // 0x567c01c  mov [rax+0x30],r9b                                    ; dst+0x30 = index
    wdst[kRecField0x30] = index;                                         // 0x567c01c  mov [rax+0x30],r9b

l567c020:
    // 0x567c020  lea r9,[rcx-0x28]                                     ; r9 = chunk
    // 0x567c024  movzx r10d,byte ptr [r9+0x40]                         ; dst+0x40 = chunk+0x40 (1 B)
    // 0x567c029  mov [rax+0x40],r10b
    wdst[kRecField0x40] = chunk[kRecField0x40];                          // 0x567c024  movzx r10d,byte ptr [r9+0x40]
                                                                           // 0x567c029  mov [rax+0x40],r10b
    // 0x567c02d  mov r10,[r9+0x38]                                     ; dst+0x38 = chunk+0x38 (8 B)
    // 0x567c031  mov [rax+0x38],r10
    *reinterpret_cast<std::uint64_t*>(wdst + kRecField0x38) =
        *reinterpret_cast<std::uint64_t*>(chunk + kRecField0x38);        // 0x567c02d  mov r10,[r9+0x38]
                                                                           // 0x567c031  mov [rax+0x38],r10
    // 0x567c035  add rax,0x48                                          ; dst += 0x48
    // 0x567c039  add rcx,0x48                                          ; chunk += 0x48 (rcx = chunk+0x28)
    // 0x567c03d  add r9,0x48                                           ; r9 = next chunk
    wdst += kRecSize;
    chunk += kRecSize;
    // 0x567c041  cmp r9,rdx
    // 0x567c044  je short 0x567C09B                                    ; if next chunk == end, return
    if (chunk == end) {                                                  // 0x567c041  cmp r9,rdx
        return;                                                          // 0x567c044  je short 0x567C09B
    }
    // loop back to loop_top (0x567bffb  jmp short 0x567C046)
}
// 0x567c09b  pop rsi                                              (epilogue; callee-saved restored)
// 0x567c09c  ret
}

// Registry entry. No callees, no boundary calls; footprint null (writes
// caller memory, not a pure function).
LIFT_FN(sub_567bfe0, "sub_567bfe0", 0x567BFE0, ::native::sub_567bfe0, nullptr);

} // namespace native

// Verbatim instructions of [0x567bfe0, 0x567c09d) (rdis dis 0x567bfe0 0xbd);
// machine-checked by tools/sigs/verify_oc.py against the exe.
#if 0
0x567bfe0  push rsi
0x567bfe1  mov rax,r8
0x567bfe4  cmp rcx,rdx
0x567bfe7  je 0x567C09B
0x567bfed  add rcx,0x28
0x567bff1  lea r8,[0xF25CF78]
0x567bff8  xorps xmm0,xmm0
0x567bffd  nop [rax]
0x567bffb  jmp short 0x567C046
0x567c046  movups xmm1,[rcx-0x28]
0x567c04a  movups [rax],xmm1
0x567c04d  mov byte ptr [rax+0x30],0xFF
0x567c051  movzx r9d,byte ptr [rcx+8]
0x567c056  cmp r9,6
0x567c05a  ja short 0x567C020
0x567c05c  lea r10,[rax+0x10]
0x567c060  lea r11,[rcx-0x18]
0x567c064  movsxd rsi,[r8+r9*4]
0x567c068  add rsi,r8
0x567c06b  jmp rsi
0x567c000  movups xmm1,[rcx-0x18]
0x567c004  movups xmm2,[rcx-8]
0x567c008  mov qword ptr [rcx-0x10],0
0x567c010  movups [rcx-8],xmm0
0x567c014  movups [rax+0x10],xmm1
0x567c018  movups [rax+0x20],xmm2
0x567c01c  mov [rax+0x30],r9b
0x567c020  lea r9,[rcx-0x28]
0x567c024  movzx r10d,byte ptr [r9+0x40]
0x567c029  mov [rax+0x40],r10b
0x567c02d  mov r10,[r9+0x38]
0x567c031  mov [rax+0x38],r10
0x567c035  add rax,0x48
0x567c039  add rcx,0x48
0x567c03d  add r9,0x48
0x567c041  cmp r9,rdx
0x567c044  je short 0x567C09B
0x567c046  movups xmm1,[rcx-0x28]
0x567c04a  movups [rax],xmm1
0x567c04d  mov byte ptr [rax+0x30],0xFF
0x567c051  movzx r9d,byte ptr [rcx+8]
0x567c056  cmp r9,6
0x567c05a  ja short 0x567C020
0x567c05c  lea r10,[rax+0x10]
0x567c060  lea r11,[rcx-0x18]
0x567c064  movsxd rsi,[r8+r9*4]
0x567c068  add rsi,r8
0x567c06b  jmp rsi
0x567c06d  movups xmm1,[r11]
0x567c071  movups xmm2,[r11+0x10]
0x567c076  movups [r10+0x10],xmm2
0x567c07b  movups [r10],xmm1
0x567c07f  jmp short 0x567C01C
0x567c081  movzx r11d,word ptr [r11]
0x567c085  mov [r10],r11w
0x567c089  jmp short 0x567C01C
0x567c08b  mov r11d,[r11]
0x567c08e  mov [r10],r11d
0x567c091  jmp short 0x567C01C
0x567c093  mov r11,[r11]
0x567c096  mov [r10],r11
0x567c099  jmp short 0x567C01C
0x567c09b  pop rsi
0x567c09c  ret
#endif
