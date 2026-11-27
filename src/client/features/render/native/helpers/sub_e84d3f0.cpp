// LIFT 0xe84d3f0 size 0x12f 1.26.62.01 sub_e84d3f0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_e84d3f0.h"
#include "client/features/render/native/helpers/sub_ebce650.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_e84d3f0, "sub_e84d3f0", 0xe84d3f0, sub_e84d3f0, nullptr);

// Verbatim call instructions from the disassembly of [0xe84d3f0, 0xe84d51f) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xe84d478  call 0xEBCE610
0xe84d4c8  call r10
0xe84d4fd  call 0xEBCE650
#endif

void sub_e84d3f0(void* start, void* end, void* output, void* unused) noexcept {
    // 0xe84d3f0..0xe84d41c: basic block 0
    // 0xe84d3f0  push rbp
    // 0xe84d3f1  push r15
    // 0xe84d3f3  push r14
    // 0xe84d3f5  push r12
    // 0xe84d3f7  push rsi
    // 0xe84d3f8  push rdi
    // 0xe84d3f9  push rbx
    // 0xe84d3fa  sub rsp,0x60
    // 0xe84d3fe  lea rbp,[rsp+0x60]
    // 0xe84d403  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
    // 0xe84d40b  mov [rbp-0x28],r8        // save output base
    // 0xe84d40f  mov [rbp-0x18],r9        // save unused arg (never read)
    // 0xe84d413  cmp rcx,rdx              // cmp start, end
    // 0xe84d416  je 0xE84D510             // if start == end goto L_0xe84d510 (return)
    // -> if start == end goto L_0xe84d510
    // -> if start != end goto L_0xe84d41c
    if (start == end)
        return;

    // 0xe84d41c..0xe84d42f: basic block 1
    // 0xe84d41c  mov rsi,rdx              // rsi = end
    // 0xe84d41f  mov rdi,rcx              // rdi = start
    // 0xe84d422  add rdi,0x20             // rdi = start + 0x20  (-> entry + 0x20)
    // 0xe84d426  lea r12,[0xF847A07]      // r12 = constant pointer
    // 0xe84d42d  jmp short 0xE84D449      // goto L_0xe84d449
    // -> if jmp goto L_0xe84d449
    void* rsi = end;
    char* rdi_base = (char*)start + 0x20;
    void* r12 = reinterpret_cast<void*>(0xF847A07ULL);
    OutputEntry* r8 = (OutputEntry*)output;

    // Main loop: blocks 3/4 alternate, blocks 5-11 handle non-zero flag entries
    for (;;) {
        // 0xe84d449..0xe84d46c: basic block 4
        // 0xe84d449  movups xmm0,[rdi-0x20]     // read 16 bytes at entry+0x00
        // 0xe84d44d  movups xmm1,[rdi-0x10]     // read 16 bytes at entry+0x10
        // 0xe84d451  movups [r8+0x10],xmm1      // write to out+0x10
        // 0xe84d456  movups [r8],xmm0           // write to out+0x00
        // 0xe84d45a  mov [r8+0x20],r12          // out->dst = r12
        // 0xe84d45e  mov dword ptr [r8+0x28],0  // out->result = 0
        // 0xe84d466  cmp dword ptr [rdi+8],0    // cmp entry->maxlen, 0
        // 0xe84d46a  je short 0xE84D430         // if entry->maxlen == 0 goto L_0xe84d430
        // -> if entry->maxlen == 0 goto L_0xe84d430
        // -> if entry->maxlen != 0 goto L_0xe84d46c
        InputEntry* entry = (InputEntry*)(rdi_base - 0x20);
        r8->data0 = entry->data0;
        r8->data1 = entry->data1;
        r8->data2 = entry->data2;
        r8->data3 = entry->data3;
        r8->dst = r12;
        r8->result = 0;

        if (entry->maxlen == 0) {
            // 0xe84d430..0xe84d449: basic block 3
            // 0xe84d430  lea rax,[rdi-0x20]     // rax = entry start
            // 0xe84d434  add r8,0x30            // r8 += 0x30
            // 0xe84d438  add rdi,0x30           // rdi += 0x30 (next entry + 0x20)
            // 0xe84d43c  add rax,0x30           // rax = entry start + 0x30 = next entry start
            // 0xe84d440  cmp rax,rsi            // cmp next_entry_start, end
            // 0xe84d443  je 0xE84D510           // if next_entry_start == end goto L_0xe84d510 (return)
            // -> if next_entry_start == end goto L_0xe84d510
            // -> if next_entry_start != end goto L_0xe84d449
            void* next_entry = (char*)entry + 0x30;
            r8 = (OutputEntry*)((char*)r8 + 0x30);
            rdi_base = (char*)rdi_base + 0x30;
            if (next_entry == rsi)
                return;
            // fall through to block 4 (loop continues)
        } else {
            // 0xe84d46c..0xe84d48c: basic block 5
            // 0xe84d46c  mov [rbp-0x10],r8      // saved_r8 = current output entry
            // 0xe84d470  mov rcx,rdi            // rcx = entry + 0x20
            // 0xe84d473  mov edx,0x7FFFFFFF     // edx = 0x7FFFFFFF
            // 0xe84d478  call 0xEBCE610         // ebx = sub_ebce610(entry+0x20, 0x7FFFFFFF)
            // 0xe84d47d  nop
            // 0xe84d47e  mov ebx,eax
            // 0xe84d480  mov rcx,[0x12ADF800]   // rcx = global pointer
            // 0xe84d487  test rcx,rcx
            // 0xe84d48a  je short 0xE84D4E0     // if global == 0 goto L_0xe84d4e0
            // -> if *(&data_12adf800) == 0 goto L_0xe84d4e0
            // -> if *(&data_12adf800) != 0 goto L_0xe84d48c
            OutputEntry* saved_r8 = r8;
            int ebx = sub_ebce610(rdi_base, 0x7FFFFFFF);
            void* g_12adf800 = *reinterpret_cast<void**>(0x12ADF800ULL);

            if (g_12adf800 == nullptr) {
                // 0xe84d4e0..0xe84d4e7: basic block 10
                // 0xe84d4e0  lea r14d,[rbx+1]   // r14d = ebx + 1
                // 0xe84d4e4  xor r15d,r15d      // r15 = 0
                // -> if fallthrough goto L_0xe84d4e7
                int r14d = ebx + 1;
                void* r15 = nullptr;

                // 0xe84d4e7..0xe84d510: basic block 11
                // 0xe84d4e7  mov rax,[rbp-0x10]   // rax = saved_r8
                // 0xe84d4eb  mov [rax+0x28],ebx   // saved_r8->result = ebx
                // 0xe84d4ee  mov rcx,r15          // rcx = r15 (nullptr)
                // 0xe84d4f1  mov edx,r14d         // edx = r14d (ebx + 1)
                // 0xe84d4f4  mov r8,rdi           // r8 = rdi (entry + 0x20 as SrcDesc*)
                // 0xe84d4f7  mov r9d,0x7FFFFFFF   // r9d = 0x7FFFFFFF
                // 0xe84d4fd  call 0xEBCE650       // sub_ebce650((char*)r15, ebx+1, SrcDesc*, 0x7FFFFFFF)
                // 0xe84d502  nop
                // 0xe84d503  mov r8,[rbp-0x10]    // r8 = saved_r8
                // 0xe84d507  mov [r8+0x20],r15    // saved_r8->dst = r15
                // 0xe84d50b  jmp 0xE84D430        // goto block 3
                saved_r8->result = ebx;
                native::sub_ebce650((char*)r15, r14d, (native::SrcDesc*)rdi_base, 0x7FFFFFFF);
                saved_r8->dst = r15;

                // Block 3 tail
                void* next_entry = (char*)entry + 0x30;
                r8 = (OutputEntry*)((char*)r8 + 0x30);
                rdi_base = (char*)rdi_base + 0x30;
                if (next_entry == rsi)
                    return;
                // loop continues to block 4
            } else {
                // 0xe84d48c..0xe84d49b: basic block 6
                // 0xe84d48c  mov rax,[rbp-0x10]     // rax = saved_r8
                // 0xe84d490  cmp dword ptr [rax+0x28],0  // cmp saved_r8->result, 0
                // 0xe84d494  mov edx,0              // edx = 0
                // 0xe84d499  je short 0xE84D49F     // if saved_r8->result == 0 goto L_0xe84d49f
                // -> if saved_r8->result == 0 goto L_0xe84d49f
                // -> if saved_r8->result != 0 goto L_0xe84d49b
                void* rdx;
                if (saved_r8->result == 0) {
                    rdx = nullptr;
                } else {
                    // 0xe84d49b..0xe84d49f: basic block 7
                    // 0xe84d49b  mov rdx,[rax+0x20]   // rdx = saved_r8->dst
                    // -> if fallthrough goto L_0xe84d49f
                    rdx = saved_r8->dst;
                }

                // 0xe84d49f..0xe84d4d1: basic block 8
                // 0xe84d49f  lea r14d,[rbx+1]     // r14d = ebx + 1
                // 0xe84d4a3  movsxd r8,r14d       // r8 = (long long)(int)(ebx + 1)
                // 0xe84d4a6  mov rax,[rcx]        // rax = *g_12ADF800 (vtable ptr; read but unused for call)
                // 0xe84d4a9  mov rax,[rax+8]      // rax = vtable[1] (read but unused for call)
                // 0xe84d4ad  mov r10,[0xF99FFA0]  // r10 = sub_eea6040 function pointer
                // 0xe84d4b4  mov dword ptr [rsp+0x28],0  // stack arg = 0
                // 0xe84d4bc  mov qword ptr [rsp+0x20],0  // stack arg = 0
                // 0xe84d4c5  xor r9d,r9d          // r9d = 0
                // 0xe84d4c8  call r10             // r15 = sub_eea6040(g_12ADF800, rdx, ebx+1, 0, 0, 0)
                // 0xe84d4cb  nop
                // 0xe84d4cc  mov r15,rax
                // 0xe84d4cf  jmp short 0xE84D4E7  // goto block 11
                int r14d = ebx + 1;
                long long r8_arg = (long long)(int)r14d;
                // Vtable reads at 0xe84d4a6 and 0xe84d4a9 are performed but their results
                // are not used for the call; the call goes through r10 = [0xF99FFA0].
                void* r15 = sub_eea6040(g_12adf800, rdx, r8_arg, 0, 0, 0);

                // 0xe84d4e7..0xe84d510: basic block 11
                // 0xe84d4e7  mov rax,[rbp-0x10]   // rax = saved_r8
                // 0xe84d4eb  mov [rax+0x28],ebx   // saved_r8->result = ebx
                // 0xe84d4ee  mov rcx,r15
                // 0xe84d4f1  mov edx,r14d         // edx = ebx + 1
                // 0xe84d4f4  mov r8,rdi           // r8 = rdi (entry + 0x20 as SrcDesc*)
                // 0xe84d4f7  mov r9d,0x7FFFFFFF   // r9d = 0x7FFFFFFF
                // 0xe84d4fd  call 0xEBCE650       // sub_ebce650((char*)r15, ebx+1, SrcDesc*, 0x7FFFFFFF)
                // 0xe84d502  nop
                // 0xe84d503  mov r8,[rbp-0x10]    // r8 = saved_r8
                // 0xe84d507  mov [r8+0x20],r15    // saved_r8->dst = r15
                // 0xe84d50b  jmp 0xE84D430        // goto block 3
                saved_r8->result = ebx;
                native::sub_ebce650((char*)r15, r14d, (native::SrcDesc*)rdi_base, 0x7FFFFFFF);
                saved_r8->dst = r15;

                // Block 3 tail
                void* next_entry = (char*)entry + 0x30;
                r8 = (OutputEntry*)((char*)r8 + 0x30);
                rdi_base = (char*)rdi_base + 0x30;
                if (next_entry == rsi)
                    return;
                // loop continues to block 4
            }
        }
    }
    // 0xe84d510..0xe84d51f: basic block 12
    // 0xe84d510  add rsp,0x60
    // 0xe84d514  pop rbx
    // 0xe84d515  pop rdi
    // 0xe84d516  pop rsi
    // 0xe84d517  pop r12
    // 0xe84d519  pop r14
    // 0xe84d51b  pop r15
    // 0xe84d51d  pop rbp
    // 0xe84d51e  ret
    // -> (fall-through / ret / end)
    // Unreachable: all paths return via the if (next_entry == rsi) return above
    // or the initial if (start == end) return.
    return;
}

// Layout static_asserts (also declared in the header; repeated here for liftcheck source scan)
static_assert(offsetof(InputEntry, data0) == 0x00, "sub_0xe84d3f0 input+0x0 field");
static_assert(offsetof(InputEntry, data1) == 0x08, "sub_0xe84d3f0 input+0x8 field");
static_assert(offsetof(InputEntry, data2) == 0x10, "sub_0xe84d3f0 input+0x10 field");
static_assert(offsetof(InputEntry, data3) == 0x18, "sub_0xe84d3f0 input+0x18 field");
static_assert(offsetof(InputEntry, src) == 0x20, "sub_0xe84d3f0 input+0x20 field");
static_assert(offsetof(InputEntry, maxlen) == 0x28, "sub_0xe84d3f0 input+0x28 field");
static_assert(sizeof(InputEntry) >= 0x2c, "sub_0xe84d3f0 input sizeof lower bound");

static_assert(offsetof(OutputEntry, data0) == 0x00, "sub_0xe84d3f0 output+0x0 field");
static_assert(offsetof(OutputEntry, data1) == 0x08, "sub_0xe84d3f0 output+0x8 field");
static_assert(offsetof(OutputEntry, data2) == 0x10, "sub_0xe84d3f0 output+0x10 field");
static_assert(offsetof(OutputEntry, data3) == 0x18, "sub_0xe84d3f0 output+0x18 field");
static_assert(offsetof(OutputEntry, dst) == 0x20, "sub_0xe84d3f0 output+0x20 field");
static_assert(offsetof(OutputEntry, result) == 0x28, "sub_0xe84d3f0 output+0x28 field");
static_assert(sizeof(OutputEntry) >= 0x2c, "sub_0xe84d3f0 output sizeof lower bound");

} // namespace native::helpers
