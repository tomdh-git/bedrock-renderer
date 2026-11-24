// LIFT 0xbc7a9d0 size 0x5e3 1.26.62.01 sub_bc7a9d0
#include "client/features/render/native/bgfx/sub_bc7a9d0.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstring>
#include <intrin.h>

namespace native {

// Lifted body of sub 0xbc7a9d0 (size 0x5e3, 0xbc7a9d0..0xbc7afb3), 1.26.62.01.
// Three-pass LSD radix sort over u32 keys with a parallel u32 array:
//   pass 1: digit = key & 0x7FF                    keys + parIn  -> workKeys + parOut
//   pass 2: digit = (key >> 9) & 0x1FFC            workKeys + parOut -> keys + parIn
//   pass 3: digit = key >> 22                      keys + parIn  -> workKeys + parOut
// Each pass is a counting sort: clear the 0x800-u32 counter array (0x2000 bytes),
// pairwise histogram that also tests whether the input is already sorted in value
// order (pairwise non-decreasing), group-of-4 exclusive prefix scan over the
// counters, then pairwise distribute plus an odd tail. A pass whose input is
// already sorted short-circuits: pass 1 -> epilogue (data left in place),
// pass 2/3 -> the tail copies the sorted run back to the caller buffers.
// Same reads, same writes (value and order), same calls in the same order,
// same return (void) as the exe function. Each block carries the instruction
// range it implements; every call is quoted verbatim beside the call site.
//
// Calls out:
//   0xbc7a9e1  call 0xE9E7970   -> sub_e9e7970   [boundary crt, __chkstk-style probe]
//   0xbc7aa1b  call 0xEBCE430   -> sub_ebce430   [lift forwarder; filled 0 => std::memset intrinsic]
//   0xbc7abb8  call 0xEBCE430   [idem]
//   0xbc7ad50  call 0xEBCE430   [idem]
//   0xbc7aed0  call 0xEBCE390   -> sub_ebce390   [lift memcpy]
//   0xbc7afad  call 0xE951550   -> sub_e951550  [boundary crt, cookie failure, noreturn]

namespace {

// 0xE9E7970: stack probe (__chkstk-style); eax = requested size, then `sub rsp,rax`.
// crt row in docs/data/native_boundary.tsv [V]. Boundary so the call is recorded
// and replayed in differential runs. Called at 0xbc7a9e1 with eax = 0x2028.
native::Boundary<std::uintptr_t, std::uintptr_t> sub_e9e7970("sub_e9e7970");

// 0xE951550: stack-cookie failure (__report_gsfailure style), noreturn; the failure
// value passed is cookieStored ^ mix-in address. crt row in native_boundary.tsv [V].
// Called at 0xbc7afad on cookie mismatch only.
native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");

} // namespace

extern "C" void sub_bc7a9d0(std::uint32_t* keys, std::uint32_t* workKeys,
                            std::uint32_t* parIn, std::uint32_t* parOut,
                            std::uint32_t count) {
    // 0xbc7a9d0..0xbc7aa0e: prologue, stack probe, and cookie store.
    //   0xbc7a9d0  push r15
    //   0xbc7a9d2  push r14
    //   0xbc7a9d4  push r13
    //   0xbc7a9d6  push r12
    //   0xbc7a9d8  push rsi
    //   0xbc7a9d9  push rdi
    //   0xbc7a9da  push rbp
    //   0xbc7a9db  push rbx
    //   0xbc7a9dc  mov eax,0x2028
    //   0xbc7a9e1  call 0xE9E7970   ; -> sub_e9e7970
    //   0xbc7a9e6  sub rsp,rax
    //   0xbc7a9e9  mov rsi,r9
    //   0xbc7a9ec  mov rdi,r8
    //   0xbc7a9ef  mov rbx,rdx
    //   0xbc7a9f2  mov r14,rcx
    //   0xbc7a9f5  mov ebp,[rsp+0x2090]          ; count (5th stack argument)
    //   0xbc7a9fc  mov rax,[0x1230A0C0]         ; [data_1230a0c0] cookie secret
    //   0xbc7aa03  xor rax,rsp
    //   0xbc7aa06  mov [rsp+0x2020],rax         ; cookie slot
    // 0xbc7a9d0..0xbc7aa0e
    std::uintptr_t cookieSlot;
    std::uint32_t counters[kCounterBins];
    const std::uintptr_t cookieStored =
        *reinterpret_cast<std::uintptr_t*>(kGblCookie) ^
        reinterpret_cast<std::uintptr_t>(&cookieSlot);   // 0xbc7a9fc..0xbc7aa06
    // 0xbc7a9e1  call 0xE9E7970   ; -> sub_e9e7970  (eax = 0x2028; sub rsp,rax)
    (void)sub_e9e7970(kStackSize);

    // 0xbc7aa0e..0xbc7aa1b: counter array clear via sub_ebce430 (fill 0).
    //   0xbc7aa0e  lea rcx,[rsp+0x20]
    //   0xbc7aa13  mov r8d,0x2000
    //   0xbc7aa19  xor edx,edx
    //   0xbc7aa1b  call 0xEBCE430   ; -> sub_ebce430
    // 0xbc7aa0e..0xbc7aa1b
    std::memset(counters, 0, kCounterBytes);   // 0xbc7aa1b call 0xEBCE430  (memset counters,0,0x2000)

    // 0xbc7aa20..0xbc7aa22: count == 0 goes straight to the epilogue.
    //   0xbc7aa20  test ebp,ebp
    //   0xbc7aa22  je short 0xBC7AF77    ; -> loc_bc7af77
    if (count == 0u) goto L_epilogue;     // 0xbc7aa20 test ebp,ebp / 0xbc7aa22 je 0xBC7AF77

    // ---------- Pass 1: digit = key & 0x7FF, out = workKeys / parOut ----------
    // 0xbc7aa28..0xbc7aa91: pairwise histogram + sortedness flag (values, not digits).
    //   0xbc7aa28  mov eax,[r14]                    ; prev = keys[0]
    //   0xbc7aa2b  mov r12d,ebp                     ; n
    //   0xbc7aa2e  mov r15,r12                      ; n - 1 (dec below)
    //   0xbc7aa31  dec r15
    //   0xbc7aa34  je short 0xBC7AAA2               ; -> loc_bc7aaa2  (n == 1)
    //   0xbc7aa36  mov r8d,r12d
    //   0xbc7aa39  and r8d,0xFFFFFFFE               ; n & ~1 (pair limit)
    //   0xbc7aa3d  mov cl,1                         ; sorted flag (cl)
    //   0xbc7aa3f  xor edx,edx                      ; pair index
    //   0xbc7aa41  nop [rax+rax]
    // loc_bc7aa50:
    //   0xbc7aa50  mov r9d,[r14+rdx*4]              ; cur = keys[idx]
    //   0xbc7aa54  mov r10d,r9d
    //   0xbc7aa57  and r10d,0x7FF                   ; bin = cur & 0x7FF
    //   0xbc7aa5e  inc dword ptr [rsp+r10*4+0x20]   ; ++counters[bin]
    //   0xbc7aa63  cmp eax,r9d                      ; prev <= cur ?
    //   0xbc7aa66  setbe r10b
    //   0xbc7aa6a  mov eax,[r14+rdx*4+4]            ; nxt = keys[i+1]; eax = nxt (next prev)
    //   0xbc7aa6f  mov r11d,eax
    //   0xbc7aa72  and r11d,0x7FF                   ; bin = nxt & 0x7FF
    //   0xbc7aa79  inc dword ptr [rsp+r11*4+0x20]   ; ++counters[bin]
    //   0xbc7aa7e  and r10b,cl                      ; (prev<=cur) && sorted-so-far
    //   0xbc7aa81  cmp r9d,eax                      ; cur <= nxt ?  (cl OVERWRITTEN)
    //   0xbc7aa84  setbe cl
    //   0xbc7aa87  and cl,r10b                      ; cl = (cur<=nxt) && (prev<=cur) && sorted
    //   0xbc7aa8a  add rdx,2
    //   0xbc7aa8e  cmp r8,rdx
    //   0xbc7aa91  jne short 0xBC7AA50              ; -> loc_bc7aa50
    // 0xbc7aa93..0xbc7aa9d: odd tail / sorted branch.
    //   0xbc7aa93  test r12b,1                      ; n odd ?
    //   0xbc7aa97  jne short 0xBC7AAA6              ; -> loc_bc7aaaa6
    //   0xbc7aa99  test cl,cl                       ; even n: sorted flag decides
    //   0xbc7aa9b  je short 0xBC7AAC9               ; -> loc_bc7aac9  (not sorted)
    //   0xbc7aa9d  jmp 0xBC7AF77                    ; sorted -> epilogue, data in place
    bool pass1Sorted = true;
    {
        std::uint32_t prev = keys[0];                // 0xbc7aa28 mov eax,[r14]
        std::uint32_t limit = count & ~1u;           // 0xbc7aa39 and r8d,0xFFFFFFFE
        std::uint32_t idx = 0;
        // 0xbc7aa50..0xbc7aa91
        for (; idx < limit; idx += 2u) {
            const std::uint32_t cur = keys[idx];       // 0xbc7aa50 mov r9d,[r14+rdx*4]
            ++counters[cur & kDigitMaskA];           // 0xbc7aa57..0xbc7aa5e ++counters[cur & 0x7FF]
            const bool lePrev = (prev <= cur);       // 0xbc7aa63..0xbc7aa66 setbe r10b
            const std::uint32_t nxt = keys[idx + 1u];  // 0xbc7aa6a mov eax,[r14+rdx*4+4]
            ++counters[nxt & kDigitMaskA];           // 0xbc7aa6f..0xbc7aa79 ++counters[nxt & 0x7FF]
            // 0xbc7aa7e..0xbc7aa87
            pass1Sorted = (cur <= nxt) && lePrev && pass1Sorted;
            prev = nxt;                              // eax reused as next iteration's prev
        }
        // 0xbc7aa93..0xbc7aa9d
        if (count & 1u) {                            // 0xbc7aa93 test r12b,1 / 0xbc7aa97 jne loc_bc7aaa6
            // loc_bc7aaa6: odd n, last element at index limit == count - 1
            ++counters[keys[limit] & kDigitMaskA];   // 0xbc7aaa9..0xbc7aab5 ++counters[keys[n-1] & 0x7FF]
            // 0xbc7aab9..0xbc7aac3: NOTE the accumulated sorted flag is OVERWRITTEN here
            //   (keys[n-2] <= keys[n-1]) only, matching the listing's setbe cl / and cl,r8b.
            pass1Sorted = (prev <= keys[limit]);     // 0xbc7aab9 cmp eax,ecx / 0xbc7aabb setbe cl / 0xbc7aabe and cl,r8b
        }
    }
    // 0xbc7aa99..0xbc7aa9d
    if (pass1Sorted) goto L_epilogue;                // 0xbc7aa9b je loc_bc7aac9 (not sorted) / 0xbc7aa9d jmp epilogue (sorted)

    // 0xbc7aac9..0xbc7ab02: group-of-4 exclusive prefix scan over counters[0..0x7FF].
    //   0xbc7aac9  xor ecx,ecx                      ; carry = 0
    //   0xbc7aacb  mov eax,3                        ; group base index (rax-3 .. rax)
    // loc_bc7aad0:
    //   0xbc7aad0  mov edx,[rsp+rax*4+0x14]
    //   0xbc7aad4  add edx,ecx
    //   0xbc7aad6  mov [rsp+rax*4+0x14],ecx
    //   0xbc7aada  mov ecx,[rsp+rax*4+0x18]
    //   0xbc7aade  add ecx,edx
    //   0xbc7aae0  mov [rsp+rax*4+0x18],edx
    //   0xbc7aae4  mov edx,[rsp+rax*4+0x1C]
    //   0xbc7aae8  add edx,ecx
    //   0xbc7aaea  mov [rsp+rax*4+0x1C],ecx
    //   0xbc7aaee  mov ecx,[rsp+rax*4+0x20]
    //   0xbc7aaf2  add ecx,edx
    //   0xbc7aaf4  mov [rsp+rax*4+0x20],edx
    //   0xbc7aaf8  add rax,4
    //   0xbc7aafc  cmp rax,0x803
    //   0xbc7ab02  jne short 0xBC7AAD0              ; -> loc_bc7aad0
    // 0xbc7aac9..0xbc7ab02
    {
        std::uint32_t carry = 0;                     // ecx
        for (std::uint32_t g = 0; g < kCounterBins; g += 4u) {  // rax = 3,7,...,0x7FF => slots rax-3..rax
            const std::uint32_t c0 = counters[g];     counters[g]     = carry; carry += c0;   // 0xbc7aad0..0xbc7aad6
            const std::uint32_t c1 = counters[g + 1]; counters[g + 1] = carry; carry += c1;   // 0xbc7aada..0xbc7aae0
            const std::uint32_t c2 = counters[g + 2]; counters[g + 2] = carry; carry += c2;   // 0xbc7aae4..0xbc7aaea
            const std::uint32_t c3 = counters[g + 3]; counters[g + 3] = carry; carry += c3;   // 0xbc7aaee..0xbc7aaf4
        }                                            // 0xbc7aaf8..0xbc7ab02
    }

    // 0xbc7ab04..0xbc7ab7f: pairwise distribute from keys to workKeys / parOut.
    //   0xbc7ab04  test r15,r15
    //   0xbc7ab07  je short 0xBC7AB81               ; -> loc_bc7ab81   (n == 1, unreachable here)
    //   0xbc7ab09  mov ecx,r12d
    //   0xbc7ab0c  and ecx,0xFFFFFFFE               ; pair limit
    //   0xbc7ab0f  xor eax,eax                      ; index
    //   0xbc7ab11  nop [rax+rax]
    // loc_bc7ab20:
    //   0xbc7ab20  mov edx,[r14+rax*4]              ; cur = keys[idx]
    //   0xbc7ab24  mov r8d,edx
    //   0xbc7ab27  and r8d,0x7FF                    ; bin
    //   0xbc7ab2e  mov r9d,[rsp+r8*4+0x20]          ; pos = counters[bin]
    //   0xbc7ab33  lea r10d,[r9+1]
    //   0xbc7ab37  mov [rsp+r8*4+0x20],r10d         ; ++counters[bin]
    //   0xbc7ab3c  mov [rbx+r9*4],edx               ; workKeys[pos] = cur
    //   0xbc7ab40  mov edx,[rdi+rax*4]              ; parOut[pos] = parIn[idx]
    //   0xbc7ab43  mov [rsi+r9*4],edx
    //   0xbc7ab47  mov edx,[r14+rax*4+4]            ; nxt = keys[i+1]
    //   0xbc7ab4c  mov r8d,edx
    //   0xbc7ab4f  and r8d,0x7FF                    ; bin
    //   0xbc7ab56  mov r9d,[rsp+r8*4+0x20]          ; pos = counters[bin]
    //   0xbc7ab5b  lea r10d,[r9+1]
    //   0xbc7ab5f  mov [rsp+r8*4+0x20],r10d         ; ++counters[bin]
    //   0xbc7ab64  mov [rbx+r9*4],edx               ; workKeys[pos] = nxt
    //   0xbc7ab68  mov edx,[rdi+rax*4+4]            ; parOut[pos] = parIn[i+1]
    //   0xbc7ab6c  mov [rsi+r9*4],edx
    //   0xbc7ab70  add rax,2
    //   0xbc7ab74  cmp rcx,rax
    //   0xbc7ab77  jne short 0xBC7AB20              ; -> loc_bc7ab20
    //   0xbc7ab79  test r12b,1
    //   0xbc7ab7d  jne short 0xBC7AB83              ; odd tail
    //   0xbc7ab7f  jmp short 0xBC7ABA8
    // loc_bc7ab81: xor eax,eax                        ; n == 1 path (dead here)
    // loc_bc7ab83: odd tail (index rax == count - 1)
    //   0xbc7ab83  mov ecx,[r14+rax*4]
    //   0xbc7ab87  mov edx,ecx
    //   0xbc7ab89  and edx,0x7FF
    //   0xbc7ab8f  mov r8d,[rsp+rdx*4+0x20]
    //   0xbc7ab94  lea r9d,[r8+1]
    //   0xbc7ab98  mov [rsp+rdx*4+0x20],r9d
    //   0xbc7ab9d  mov [rbx+r8*4],ecx
    //   0xbc7aba1  mov eax,[rdi+rax*4]
    //   0xbc7aba4  mov [rsi+r8*4],eax
    // loc_bc7aba8:
    {
        std::uint32_t idx = 0;
        const std::uint32_t lim = count & ~1u;
        // 0xbc7ab20..0xbc7ab77
        for (; idx < lim; idx += 2u) {
            const std::uint32_t cur = keys[idx];             // 0xbc7ab20
            std::uint32_t pos = counters[cur & kDigitMaskA]++;   // 0xbc7ab24..0xbc7ab37
            workKeys[pos] = cur;                             // 0xbc7ab3c
            parOut[pos] = parIn[idx];                        // 0xbc7ab40..0xbc7ab43
            const std::uint32_t nxt = keys[idx + 1u];        // 0xbc7ab47
            pos = counters[nxt & kDigitMaskA]++;             // 0xbc7ab4c..0xbc7ab5f
            workKeys[pos] = nxt;                             // 0xbc7ab64
            parOut[pos] = parIn[idx + 1u];                   // 0xbc7ab68..0xbc7ab6c
        }
        // 0xbc7ab79..0xbc7aba4
        if (count & 1u) {                                    // 0xbc7ab79 / 0xbc7ab7d
            const std::uint32_t cur = keys[count - 1u];      // 0xbc7ab83 (rax == count - 1)
            std::uint32_t pos = counters[cur & kDigitMaskA]++; // 0xbc7ab87..0xbc7ab98
            workKeys[pos] = cur;                             // 0xbc7ab9d
            parOut[pos] = parIn[count - 1u];                 // 0xbc7aba1..0xbc7aba4
        }
    } // loc_bc7aba8

    // ---------- Pass 2: digit = (key >> 9) & 0x1FFC, out = keys / parIn ----------
    // 0xbc7abb8..0xbc7ac19: clear counters, pairwise histogram over workKeys.
    //   0xbc7abb8  call 0xEBCE430   ; -> sub_ebce430   (memset counters,0,0x2000)
    //   0xbc7abbd  mov eax,[rbx]                    ; prev = workKeys[0]
    //   0xbc7abbf  test r15,r15
    //   0xbc7abc2  je short 0xBC7AC2A               ; -> loc_bc7ac2a  (n == 1)
    //   0xbc7abc4  mov edx,r12d
    //   0xbc7abc7  and edx,0xFFFFFFFE               ; n & ~1
    //   0xbc7abca  mov cl,1
    //   0xbc7abcc  xor r13d,r13d                    ; pair index
    //   0xbc7abcf  nop
    // loc_bc7abd0:
    //   0xbc7abd0  mov r8d,[rbx+r13*4]              ; cur = workKeys[idx]
    //   0xbc7abd4  mov r9d,r8d
    //   0xbc7abd7  shr r9d,9
    //   0xbc7abdb  and r9d,0x1FFC                   ; byte-offset bin
    //   0xbc7abe2  inc dword ptr [rsp+r9+0x20]      ; ++counters[bin]
    //   0xbc7abe7  cmp eax,r8d                      ; prev <= cur ?
    //   0xbc7abea  setbe r9b
    //   0xbc7abee  mov eax,[rbx+r13*4+4]            ; nxt = workKeys[i+1]
    //   0xbc7abf3  mov r10d,eax
    //   0xbc7abf6  shr r10d,9
    //   0xbc7abfa  and r10d,0x1FFC
    //   0xbc7ac01  inc dword ptr [rsp+r10+0x20]     ; ++counters[bin]
    //   0xbc7ac06  and r9b,cl
    //   0xbc7ac09  cmp r8d,eax                      ; cur <= nxt ?  (cl OVERWRITTEN)
    //   0xbc7ac0c  setbe cl
    //   0xbc7ac0f  and cl,r9b
    //   0xbc7ac12  add r13,2
    //   0xbc7ac16  cmp rdx,r13
    //   0xbc7ac19  jne short 0xBC7ABD0              ; -> loc_bc7abd0
    //   0xbc7ac1b  test r12b,1
    //   0xbc7ac1f  jne short 0xBC7AC2C
    //   0xbc7ac21  test cl,cl
    //   0xbc7ac23  je short 0xBC7AC54               ; not sorted -> scan + distribute
    //   0xbc7ac25  jmp 0xBC7AEBF                    ; sorted -> tail copy
    std::memset(counters, 0, kCounterBytes);         // 0xbc7abb8 call 0xEBCE430
    bool pass2Sorted = true;
    {
        std::uint32_t prev = workKeys[0];            // 0xbc7abbd mov eax,[rbx]
        std::uint32_t limit = count & ~1u;
        std::uint32_t idx = 0;
        // 0xbc7abd0..0xbc7ac19
        for (; idx < limit; idx += 2u) {
            const std::uint32_t cur = workKeys[idx];                       // 0xbc7abd0
            ++counters[((cur >> 9u) & kDigitMaskB) >> 2u];               // 0xbc7abd4..0xbc7abe2 (byte-offset bin)
            const bool lePrev = (prev <= cur);                           // 0xbc7abe7..0xbc7abea
            const std::uint32_t nxt = workKeys[i + 1u];                  // 0xbc7abee
            ++counters[((nxt >> 9u) & kDigitMaskB) >> 2u];               // 0xbc7abf3..0xbc7ac01
            // 0xbc7ac06..0xbc7ac0f
            pass2Sorted = (cur <= nxt) && lePrev && pass2Sorted;
            prev = nxt;
        }
        // 0xbc7ac1b..0xbc7ac25
        if (count & 1u) {
            ++counters[((workKeys[limit] >> 9u) & kDigitMaskB) >> 2u];   // 0xbc7ac2e..0xbc7ac40
            pass2Sorted = (prev <= workKeys[limit]);                     // 0xbc7ac45..0xbc7ac4a (flag overwritten)
        }
    }
    // 0xbc7ac21..0xbc7ac25
    if (pass2Sorted) goto L_tail;                          // 0xbc7ac23 je loc_bc7ac54 / 0xbc7ac25 jmp loc_bc7aebf

    // 0xbc7ac54..0xbc7ac92: group-of-4 exclusive prefix scan over counters.
    //   0xbc7ac54  xor ecx,ecx
    //   0xbc7ac56  mov eax,3
    //   0xbc7ac5b  nop [rax+rax]
    // loc_bc7ac60:
    //   0xbc7ac60  mov edx,[rsp+rax*4+0x14]
    //   0xbc7ac64  add edx,ecx
    //   0xbc7ac66  mov [rsp+rax*4+0x14],ecx
    //   0xbc7ac6a  mov ecx,[rsp+rax*4+0x18]
    //   0xbc7ac6e  add ecx,edx
    //   0xbc7ac70  mov [rsp+rax*4+0x18],edx
    //   0xbc7ac74  mov edx,[rsp+rax*4+0x1C]
    //   0xbc7ac78  add edx,ecx
    //   0xbc7ac7a  mov [rsp+rax*4+0x1C],ecx
    //   0xbc7ac7e  mov ecx,[rsp+rax*4+0x20]
    //   0xbc7ac82  add ecx,edx
    //   0xbc7ac84  mov [rsp+rax*4+0x20],edx
    //   0xbc7ac88  add rax,4
    //   0xbc7ac8c  cmp rax,0x803
    //   0xbc7ac92  jne short 0xBC7AC60
    // 0xbc7ac54..0xbc7ac92
    {
        std::uint32_t carry = 0;
        for (std::uint32_t g = 0; g < kCounterBins; g += 4u) {
            const std::uint32_t c0 = counters[g];     counters[g]     = carry; carry += c0;
            const std::uint32_t c1 = counters[g + 1]; counters[g + 1] = carry; carry += c1;
            const std::uint32_t c2 = counters[g + 2]; counters[g + 2] = carry; carry += c2;
            const std::uint32_t c3 = counters[g + 3]; counters[g + 3] = carry; carry += c3;
        }
    }

    // 0xbc7ac94..0xbc7ad3c: pairwise distribute from workKeys to keys / parIn.
    //   0xbc7ac94  test r15,r15
    //   0xbc7ac97  je short 0xBC7AD17               ; -> loc_bc7ad17
    //   0xbc7ac99  mov ecx,r12d
    //   0xbc7ac9c  and ecx,0xFFFFFFFE
    //   0xbc7ac9f  xor eax,eax
    //   0xbc7aca1  nop [rax+rax]
    // loc_bc7acb0:
    //   0xbc7acb0  mov edx,[rbx+rax*4]              ; cur = workKeys[idx]
    //   0xbc7acb3  mov r8d,edx
    //   0xbc7acb6  shr r8d,9
    //   0xbc7acba  and r8d,0x1FFC                   ; byte-offset bin
    //   0xbc7acc1  mov r9d,[rsp+r8+0x20]            ; pos = counters[bin]
    //   0xbc7acc6  lea r10d,[r9+1]
    //   0xbc7acca  mov [rsp+r8+0x20],r10d           ; ++counters[bin]
    //   0xbc7accf  mov [r14+r9*4],edx               ; keys[pos] = cur
    //   0xbc7acd3  mov edx,[rsi+rax*4]              ; parIn[pos] = parOut[idx]
    //   0xbc7acd6  mov [rdi+r9*4],edx
    //   0xbc7acda  mov edx,[rbx+rax*4+4]            ; nxt = workKeys[i+1]
    //   0xbc7acde  mov r8d,edx
    //   0xbc7ace1  shr r8d,9
    //   0xbc7ace5  and r8d,0x1FFC
    //   0xbc7acec  mov r9d,[rsp+r8+0x20]
    //   0xbc7acf1  lea r10d,[r9+1]
    //   0xbc7acf5  mov [rsp+r8+0x20],r10d           ; ++counters[bin]
    //   0xbc7acfa  mov [r14+r9*4],edx               ; keys[pos] = nxt
    //   0xbc7acfe  mov edx,[rsi+rax*4+4]            ; parIn[pos] = parOut[i+1]
    //   0xbc7ad02  mov [rdi+r9*4],edx
    //   0xbc7ad06  add rax,2
    //   0xbc7ad0a  cmp rcx,rax
    //   0xbc7ad0d  jne short 0xBC7ACB0
    //   0xbc7ad0f  test r12b,1
    //   0xbc7ad13  jne short 0xBC7AD19
    //   0xbc7ad15  jmp short 0xBC7AD40
    // loc_bc7ad17: xor eax,eax
    // loc_bc7ad19: odd tail
    //   0xbc7ad19  mov ecx,[rbx+rax*4]
    //   0xbc7ad1c  mov edx,ecx
    //   0xbc7ad1e  shr edx,9
    //   0xbc7ad21  and edx,0x1FFC
    //   0xbc7ad27  mov r8d,[rsp+rdx+0x20]
    //   0xbc7ad2c  lea r9d,[r8+1]
    //   0xbc7ad30  mov [rsp+rdx+0x20],r9d
    //   0xbc7ad35  mov [r14+r8*4],ecx
    //   0xbc7ad39  mov eax,[rsi+rax*4]
    //   0xbc7ad3c  mov [rdi+r8*4],eax
    {
        std::uint32_t idx = 0;
        const std::uint32_t lim = count & ~1u;
        // 0xbc7acb0..0xbc7ad0d
        for (; idx < lim; idx += 2u) {
            const std::uint32_t cur = workKeys[idx];
            std::uint32_t pos = counters[((cur >> 9u) & kDigitMaskB) >> 2u]++;
            keys[pos] = cur;
            parIn[pos] = parOut[idx];
            const std::uint32_t nxt = workKeys[idx + 1u];
            pos = counters[((nxt >> 9u) & kDigitMaskB) >> 2u]++;
            keys[pos] = nxt;
            parIn[pos] = parOut[idx + 1u];
        }
        // 0xbc7ad0f..0xbc7ad3c
        if (count & 1u) {
            const std::uint32_t cur = workKeys[count - 1u];
            std::uint32_t pos = counters[((cur >> 9u) & kDigitMaskB) >> 2u]++;
            keys[pos] = cur;
            parIn[pos] = parOut[count - 1u];
        }
    } // loc_bc7ad40

    // ---------- Pass 3: digit = key >> 22, out = workKeys / parOut ----------
    // 0xbc7ad40..0xbc7adab: clear counters, pairwise histogram over keys.
    //   0xbc7ad40  xor r13d,r13d
    //   0xbc7ad43  lea rcx,[rsp+0x20]
    //   0xbc7ad48  mov r8d,0x2000
    //   0xbc7ad4e  xor edx,edx
    //   0xbc7ad50  call 0xEBCE430   ; -> sub_ebce430   (memset counters,0,0x2000)
    //   0xbc7ad55  mov eax,[r14]                    ; prev = keys[0]
    //   0xbc7ad58  test r15,r15
    //   0xbc7ad5b  je short 0xBC7ADBC               ; -> loc_bc7adbc  (n == 1)
    //   0xbc7ad5d  mov edx,r12d
    //   0xbc7ad60  and edx,0xFFFFFFFE
    //   0xbc7ad63  mov cl,1
    //   0xbc7ad65  xor r13d,r13d
    //   0xbc7ad68  nop [rax+rax]
    // loc_bc7ad70:
    //   0xbc7ad70  mov r8d,[r14+r13*4]              ; cur = keys[idx]
    //   0xbc7ad74  mov r9d,r8d
    //   0xbc7ad77  shr r9d,0x16                     ; bin = cur >> 22
    //   0xbc7ad7b  inc dword ptr [rsp+r9*4+0x20]    ; ++counters[bin]
    //   0xbc7ad80  cmp eax,r8d                      ; prev <= cur ?
    //   0xbc7ad83  setbe r9b
    //   0xbc7ad87  mov eax,[r14+r13*4+4]            ; nxt = keys[i+1]
    //   0xbc7ad8c  mov r10d,eax
    //   0xbc7ad93  inc dword ptr [rsp+r10*4+0x20]   ; ++counters[bin]
    //   0xbc7ad98  and r9b,cl
    //   0xbc7ad9b  cmp r8d,eax                      ; cur <= nxt ?  (cl OVERWRITTEN)
    //   0xbc7ad9e  setbe cl
    //   0xbc7ada1  and cl,r9b
    //   0xbc7ada4  add r13,2
    //   0xbc7ada8  cmp rdx,r13
    //   0xbc7adab  jne short 0xBC7AD70
    //   0xbc7adad  test r12b,1
    //   0xbc7adb1  jne short 0xBC7ADBE
    //   0xbc7adb3  test cl,cl
    //   0xbc7adb5  je short 0xBC7ADDF               ; not sorted -> scan + distribute
    //   0xbc7adb7  jmp 0xBC7AF77                    ; sorted -> epilogue (keys in place)
    std::memset(counters, 0, kCounterBytes);         // 0xbc7ad50 call 0xEBCE430
    bool pass3Sorted = true;
    {
        std::uint32_t prev = keys[0];                // 0xbc7ad55 mov eax,[r14]
        std::uint32_t limit = count & ~1u;
        std::uint32_t idx = 0;
        // 0xbc7ad70..0xbc7adab
        for (; idx < limit; idx += 2u) {
            const std::uint32_t cur = keys[idx];       // 0xbc7ad70
            ++counters[cur >> 22u];                  // 0xbc7ad74..0xbc7ad7b
            const bool lePrev = (prev <= cur);       // 0xbc7ad80..0xbc7ad83
            const std::uint32_t nxt = keys[idx + 1u];  // 0xbc7ad87
            ++counters[nxt >> 22u];                  // 0xbc7ad8c..0xbc7ad93
            // 0xbc7ad98..0xbc7ada1
            pass3Sorted = (cur <= nxt) && lePrev && pass3Sorted;
            prev = nxt;
        }
        // 0xbc7adad..0xbc7adb7
        if (count & 1u) {
            ++counters[keys[limit] >> 22u];          // 0xbc7adc0..0xbc7adcb
            pass3Sorted = (prev <= keys[limit]);     // 0xbc7add0..0xbc7add5 (flag overwritten)
        }
    }
    // 0xbc7adb3..0xbc7adb7
    if (pass3Sorted) goto L_epilogue;                // 0xbc7adb5 je loc_bc7addf / 0xbc7adb7 jmp epilogue

    // 0xbc7addf..0xbc7ae22: group-of-4 exclusive prefix scan over counters.
    //   0xbc7addf  xor ecx,ecx
    //   0xbc7ade1  xor eax,eax                      ; rax = 0
    //   0xbc7ade3  nop [rax+rax]
    // loc_bc7adf0:
    //   0xbc7adf0  mov edx,[rsp+rax*4+0x20]
    //   0xbc7adf4  add edx,ecx
    //   0xbc7adf6  mov [rsp+rax*4+0x20],ecx
    //   0xbc7adfa  mov ecx,[rsp+rax*4+0x24]
    //   0xbc7adfe  add ecx,edx
    //   0xbc7ae00  mov [rsp+rax*4+0x24],edx
    //   0xbc7ae04  mov edx,[rsp+rax*4+0x28]
    //   0xbc7ae08  add edx,ecx
    //   0xbc7ae0a  mov [rsp+rax*4+0x28],ecx
    //   0xbc7ae0e  mov ecx,[rsp+rax*4+0x2C]
    //   0xbc7ae12  add ecx,edx
    //   0xbc7ae14  mov [rsp+rax*4+0x2C],edx
    //   0xbc7ae18  add rax,4
    //   0xbc7ae1c  cmp rax,0x800
    //   0xbc7ae22  jne short 0xBC7ADF0
    // 0xbc7addf..0xbc7ae22
    {
        std::uint32_t carry = 0;
        for (std::uint32_t g = 0; g < kCounterBins; g += 4u) {
            const std::uint32_t c0 = counters[g];     counters[g]     = carry; carry += c0;
            const std::uint32_t c1 = counters[g + 1]; counters[g + 1] = carry; carry += c1;
            const std::uint32_t c2 = counters[g + 2]; counters[g + 2] = carry; carry += c2;
            const std::uint32_t c3 = counters[g + 3]; counters[g + 3] = carry; carry += c3;
        }
    }

    // 0xbc7ae24..0xbc7ae9d: pairwise distribute from keys to workKeys / parOut.
    //   0xbc7ae24  test r15,r15
    //   0xbc7ae27  je short 0xBC7AE9B               ; -> loc_bc7ae9b
    //   0xbc7ae29  mov ecx,r12d
    //   0xbc7ae2c  and ecx,0xFFFFFFFE
    //   0xbc7ae2f  xor eax,eax
    //   0xbc7ae31  nop [rax+rax]
    // loc_bc7ae40:
    //   0xbc7ae40  mov edx,[r14+rax*4]              ; cur = keys[idx]
    //   0xbc7ae44  mov r8d,edx
    //   0xbc7ae47  shr r8d,0x16                     ; bin
    //   0xbc7ae4b  mov r9d,[rsp+r8*4+0x20]          ; pos = counters[bin]
    //   0xbc7ae50  lea r10d,[r9+1]
    //   0xbc7ae54  mov [rsp+r8*4+0x20],r10d         ; ++counters[bin]
    //   0xbc7ae59  mov [rbx+r9*4],edx               ; workKeys[pos] = cur
    //   0xbc7ae5d  mov edx,[rdi+rax*4]              ; parOut[pos] = parIn[idx]
    //   0xbc7ae60  mov [rsi+r9*4],edx
    //   0xbc7ae64  mov edx,[r14+rax*4+4]            ; nxt = keys[i+1]
    //   0xbc7ae69  mov r8d,edx
    //   0xbc7ae6c  shr r8d,0x16
    //   0xbc7ae70  mov r9d,[rsp+r8*4+0x20]
    //   0xbc7ae75  lea r10d,[r9+1]
    //   0xbc7ae79  mov [rsp+r8*4+0x20],r10d         ; ++counters[bin]
    //   0xbc7ae7e  mov [rbx+r9*4],edx               ; workKeys[pos] = nxt
    //   0xbc7ae82  mov edx,[rdi+rax*4+4]            ; parOut[pos] = parIn[i+1]
    //   0xbc7ae86  mov [rsi+r9*4],edx
    //   0xbc7ae8a  add rax,2
    //   0xbc7ae8e  cmp rcx,rax
    //   0xbc7ae91  jne short 0xBC7AE40
    //   0xbc7ae93  test r12b,1
    //   0xbc7ae97  jne short 0xBC7AE9D
    //   0xbc7ae99  jmp short 0xBC7AEBF
    // loc_bc7ae9b: xor eax,eax
    // loc_bc7ae9d: odd tail
    //   0xbc7ae9d  mov ecx,[r14+rax*4]
    //   0xbc7aea1  mov edx,ecx
    //   0xbc7aea3  shr edx,0x16
    //   0xbc7aea6  mov r8d,[rsp+rdx*4+0x20]
    //   0xbc7aeab  lea r9d,[r8+1]
    //   0xbc7aeaf  mov [rsp+rdx*4+0x20],r9d
    //   0xbc7aeb4  mov [rbx+r8*4],ecx
    //   0xbc7aea8  mov eax,[rdi+rax*4]
    //   0xbc7aebb  mov [rsi+r8*4],eax
    {
        std::uint32_t idx = 0;
        const std::uint32_t lim = count & ~1u;
        // 0xbc7ae40..0xbc7ae91
        for (; idx < lim; idx += 2u) {
            const std::uint32_t cur = keys[idx];
            std::uint32_t pos = counters[cur >> 22u]++;
            workKeys[pos] = cur;
            parOut[pos] = parIn[idx];
            const std::uint32_t nxt = keys[idx + 1u];
            pos = counters[nxt >> 22u]++;
            workKeys[pos] = nxt;
            parOut[pos] = parIn[idx + 1u];
        }
        // 0xbc7ae93..0xbc7aebb
        if (count & 1u) {
            const std::uint32_t cur = keys[count - 1u];
            std::uint32_t pos = counters[cur >> 22u]++;
            workKeys[pos] = cur;
            parOut[pos] = parIn[count - 1u];
        }
    } // falls into the tail copy below

L_tail:
    // 0xbc7aebf..0xbc7aed0: copy the sorted keys back to the caller's key buffer.
    //   0xbc7aebf  lea r15,[r12*4]              ; byte count = count * 4
    //   0xbc7aec7  mov rcx,r14                  ; dst = keys
    //   0xbc7aeca  mov rdx,rbx                  ; src = workKeys
    //   0xbc7aecd  mov r8,r15                   ; size
    //   0xbc7aed0  call 0xEBCE390               ; -> sub_ebce390  memcpy(keys, workKeys, count*4)
    // 0xbc7aebf..0xbc7aed0
    sub_ebce390(keys, workKeys,
                static_cast<std::uint64>(count) * 4u);   // 0xbc7aed0 call 0xEBCE390

    // 0xbc7aed5..0xbc7af75: copy the parallel array parOut -> parIn (count u32).
    //   0xbc7aed5  cmp ebp,8
    //   0xbc7aed8  setb al                        ; al = (count < 8)
    //   0xbc7aedb  mov rcx,rdi
    //   0xbc7aede  sub rcx,rsi                    ; rcx = (uint64)(parIn - parOut)
    //   0xbc7aee1  cmp rcx,0x20
    //   0xbc7aee5  setb cl                        ; cl = ((uint64)(parIn - parOut) < 0x20)
    //   0xbc7aee8  or cl,al
    //   0xbc7aeea  je short 0xBC7AEF0             ; count >= 8 && buffers far apart: movups bulk path
    //   0xbc7aeec  xor eax,eax
    //   0xbc7aeee  jmp short 0xBC7AF20
    if (count >= 8u &&
        static_cast<std::uint64>(
            reinterpret_cast<std::uintptr_t>(parIn) -
            reinterpret_cast<std::uintptr_t>(parOut)) >= 0x20u) {
        // 0xbc7aef0..0xbc7af1e: movups bulk path, 32-byte (8 u32) chunks.
        //   0xbc7aef0  mov eax,r12d
        //   0xbc7aef3  and eax,0xFFFFFFF8         ; count & ~7
        //   0xbc7aef6  and r15,0xFFFFFFFFFFFFFFE0 ; byte count rounded down to 32
        //   0xbc7aefa  xor ecx,ecx                ; byte index
        // loc_bc7af00:
        //   0xbc7af00  movups xmm0,[rsi+rcx]
        //   0xbc7af04  movups xmm1,[rsi+rcx+0x10]
        //   0xbc7af09  movups [rdi+rcx],xmm0
        //   0xbc7af0d  movups [rdi+rcx+0x10],xmm1
        //   0xbc7af12  add rcx,0x20
        //   0xbc7af16  cmp r15,rcx
        //   0xbc7af19  jne short 0xBC7AF00
        //   0xbc7af1b  cmp eax,r12d
        //   0xbc7af1e  je short 0xBC7AF77        ; (count & ~7) == count -> epilogue
        std::uint32_t idx = 0;
        const std::uint32_t lim8 = count & ~7u;
        // 0xbc7af00..0xbc7af19
        for (; idx < lim8; idx += 8u) {          // 8 u32 = 32 bytes per iteration (movups x2)
            parOut[idx + 0] = parIn[idx + 0];
            parOut[idx + 1] = parIn[idx + 1];
            parOut[idx + 2] = parIn[idx + 2];
            parOut[idx + 3] = parIn[idx + 3];
            parOut[idx + 4] = parIn[idx + 4];
            parOut[idx + 5] = parIn[idx + 5];
            parOut[idx + 6] = parIn[idx + 6];
            parOut[idx + 7] = parIn[idx + 7];
        }
        // 0xbc7af1b..0xbc7af1e
        if (lim8 == count) goto L_epilogue;

        // 0xbc7af20..0xbc7af75: remainder (shared with the close-buffers path below).
        //   0xbc7af20  mov rdx,r12
        //   0xbc7af23  mov rcx,rax                ; rax = count & ~7 (index)
        //   0xbc7af26  and rdx,3                  ; count & 3
        //   0xbc7af2a  je short 0xBC7AF40
        // loc_bc7af30:
        //   0xbc7af30  mov r8d,[rsi+rcx*4]
        //   0xbc7af34  mov [rdi+rcx*4],r8d
        //   0xbc7af38  inc rcx
        //   0xbc7af3b  dec rdx
        //   0xbc7af3e  jne short 0xBC7AF30
        //   0xbc7af40  sub rax,r12                ; (count & ~7) - count, wrapped u32
        //   0xbc7af43  cmp rax,0xFFFFFFFFFFFFFFFC
        //   0xbc7af47  ja short 0xBC7AF77        ; epilogue when count % 8 < 4
        // loc_bc7af50:
        //   0xbc7af50  mov eax,[rsi+rcx*4]
        //   0xbc7af53  mov [rdi+rcx*4],eax
        //   0xbc7af56  mov eax,[rsi+rcx*4+4]
        //   0xbc7af5a  mov [rdi+rcx*4+4],eax
        //   0xbc7af5e  mov eax,[rsi+rcx*4+8]
        //   0xbc7af62  mov [rdi+rcx*4+8],eax
        //   0xbc7af66  mov eax,[rsi+rcx*4+0xC]
        //   0xbc7af6a  mov [rdi+rcx*4+0xC],eax
        //   0xbc7af6e  add rcx,4
        //   0xbc7af72  cmp r12,rcx
        //   0xbc7af75  jne short 0xBC7AF50
        // 0xbc7af20..0xbc7af75
        {
            std::uint32_t rem = count & 3u;
            std::uint32_t r = lim8;
            // 0xbc7af30..0xbc7af3e
            for (; rem != 0u; --rem) {           // count & 3 single u32 copies
                parOut[r] = parIn[r];
                ++r;
            }
            // 0xbc7af40..0xbc7af47: (count & ~7) - count > 0xFFFFFFFC (wrapped u32) => epilogue
            if (static_cast<std::uint64>(static_cast<std::uint32_t>(lim8 - count)) >
                0xFFFFFFFCull) goto L_epilogue;
            // 0xbc7af50..0xbc7af75: 4 u32 per iteration
            for (; r != count; r += 4u) {        // 0xbc7af50..0xbc7af72
                parOut[r + 0] = parIn[r + 0];
                parOut[r + 1] = parIn[r + 1];
                parOut[r + 2] = parIn[r + 2];
                parOut[r + 3] = parIn[r + 3];
            }
        }
    } else {
        // 0xbc7aeec..0xbc7af75: close-buffers / small-count path, u32 loops only.
        //   0xbc7aeec  xor eax,eax
        //   0xbc7af20  mov rdx,r12
        //   0xbc7af23  mov rcx,rax                ; rax = 0 (index)
        //   0xbc7af26  and rdx,3                  ; count & 3
        //   0xbc7af2a  je short 0xBC7AF40
        // loc_bc7af30: ... (single u32 copies) ...
        //   0xbc7af40  sub rax,r12                ; -count (wrapped u32)
        //   0xbc7af43  cmp rax,0xFFFFFFFFFFFFFFFC
        //   0xbc7af47  ja short 0xBC7AF77        ; epilogue when count < 4
        // loc_bc7af50: ... (4-u32 copies) ...
        // 0xbc7aeec..0xbc7af75
        std::uint32_t rem = count & 3u;
        std::uint32_t r = 0;
        // 0xbc7af30..0xbc7af3e
        for (; rem != 0u; --rem) {
            parOut[r] = parIn[r];
            ++r;
        }
        // 0xbc7af40..0xbc7af47: -count > 0xFFFFFFFC (wrapped u32) <=> count < 4
        if (static_cast<std::uint64>(static_cast<std::uint32_t>(0u - count)) >
            0xFFFFFFFCull) goto L_epilogue;
        // 0xbc7af50..0xbc7af75
        for (; r != count; r += 4u) {
            parOut[r + 0] = parIn[r + 0];
            parOut[r + 1] = parIn[r + 1];
            parOut[r + 2] = parIn[r + 2];
            parOut[r + 3] = parIn[r + 3];
        }
    }

L_epilogue:
    // 0xbc7af77..0xbc7afa1: stack cookie check and epilogue.
    //   0xbc7af77  mov rax,[rsp+0x2020]         ; cookie slot
    //   0xbc7af7f  xor rax,rsp
    //   0xbc7af82  mov rcx,[0x1230A0C0]         ; [data_1230a0c0]
    //   0xbc7af89  cmp rcx,rax
    //   0xbc7af8c  jne short 0xBC7AFA2          ; -> loc_bc7afa2   (cookie mismatch)
    //   0xbc7af8e  add rsp,0x2028
    //   0xbc7af95  pop rbx
    //   0xbc7af96  pop rbp
    //   0xbc7af97  pop rdi
    //   0xbc7af98  pop rsi
    //   0xbc7af99  pop r12
    //   0xbc7af9b  pop r13
    //   0xbc7af9d  pop r14
    //   0xbc7af9f  pop r15
    //   0xbc7afa1  ret
    // 0xbc7af77..0xbc7afa1
    if (*reinterpret_cast<std::uintptr_t*>(kGblCookie) !=
        (cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot))) {
        // loc_bc7afa2: 0xbc7afa2..0xbc7afb2
        //   0xbc7afa2  mov rcx,[rsp+0x2020]
        //   0xbc7afaa  xor rcx,rsp
        //   0xbc7afad  call 0xE951550   ; -> sub_e951550  (noreturn)
        //   0xbc7afb2  int3              ; unreachable padding
        sub_e951550(cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot));
        __assume(false);   // noreturn; the listing continues with int3 padding only
    }
    // 0xbc7af8e..0xbc7afa1: add rsp,0x2028; pop rbx,rbp,rdi,rsi,r12,r13,r14,r15; ret
}

static_assert(offsetof(Bc7a9d0Frame, counters) == 0x0000u, "sub_bc7a9d0: counters at frame base");
static_assert(offsetof(Bc7a9d0Frame, cookie) == 0x2000u, "sub_bc7a9d0: cookie at +0x2000");
static_assert(sizeof(Bc7a9d0Frame) == 0x2008u, "sub_bc7a9d0: frame size");

native::Footprint sub_bc7a9d0_footprint(std::uint32_t* keys, std::uint32_t* workKeys,
                                        std::uint32_t* parIn, std::uint32_t* parOut,
                                        std::uint32_t count) {
    return {
        {keys, static_cast<std::size_t>(count) * 4u},
        {workKeys, static_cast<std::size_t>(count) * 4u},
        {parIn, static_cast<std::size_t>(count) * 4u},
        {parOut, static_cast<std::size_t>(count) * 4u},
    };
}

LIFT_FN(bc7a9d0, "sub_bc7a9d0", 0xBC7A9D0, sub_bc7a9d0, sub_bc7a9d0_footprint);

} // namespace native
