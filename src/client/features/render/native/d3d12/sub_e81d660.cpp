// LIFT 0xe81d660 size 0x1af 1.26.62.01 D3D12 submit RTX override
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e81d660.h"

#include <cstddef>
#include <cstdint>

static_assert(sizeof(void*) == 8, "ptr");

namespace native::d3d12 {
namespace {

// The CFG-guard thunk sub_eea6040 (0xeea6040) is a single `jmp rax`; it forwards to
// whatever rax holds, so `call qword ptr [0xF99FFA0]` is a guard-dispatched indirect
// call whose real target is rax = vtable[kVtableSlot] (loaded at 0xe81d781/0xe81d784).
// It is classified `vendor` (thunk via data slot 0xF99FFA0) in docs/data/native_boundary.tsv.
using GuardedVirtualFn = void (*)(void* self, void* arg1, std::uint32_t arg2, std::uint32_t arg3);

} // namespace

// 0xe81d660..0xe81d80f  (prolog push/sub rsp/lea rbp/[rbp]=-2 at 0xe81d660..0xe81d675 and
// the epilog add rsp,0x38 / pops / ret at 0xe81d7df..0xe81d7ef are emitted by the compiler;
// 0xe81d80e int3 is noreturn padding after the fatal sub_eec5a00(6) call.)
std::uint32_t sub_e81d660(void* a0, void* a1, std::uint32_t a2, std::uint32_t a3) {
    char* const self = static_cast<char*>(a0);                 // 0xe81d686 mov rsi,rcx
    char* const lock = self + kLockOff;                        // 0xe81d689 lea r13,[rcx+0x7850]

    // 0xe81d690..0xe81d69a  acquire the submit lock; a nonzero result aborts (fatal).
    const int locked = native::sub_eec59f0(lock);              // 0xe81d690 mov rcx,r13 ; 0xe81d693 call 0xEEC59F0 ; 0xe81d698 test eax,eax
    if (locked != 0) {                                         // 0xe81d69a jne 0xE81D7F0
        // 0xe81d7f0..0xe81d7f5  fatal (code 5); sub_eec5a00 does not return, so nothing after runs.
        native::sub_eec5a00(5);                               // 0xe81d7f0 mov ecx,5 ; 0xe81d7f5 call 0xEEC5A00
    }

    // 0xe81d6a0..0xe81d6aa  (reached only when the lock was acquired): abort if already aborted.
    if (*reinterpret_cast<std::uint32_t*>(self + kSentinelOff) == kAbortSentinel) { // 0xe81d6a0 cmp dword ptr [rsi+0x789C],0x7FFFFFFF ; 0xe81d6aa je 0xE81D7FA
        // 0xe81d7fa..0xe81d809  mark aborted and fail fast (code 6); sub_eec5a00 does not return.
        *reinterpret_cast<std::uint32_t*>(self + kSentinelOff) = kAbortedValue;      // 0xe81d7fa mov dword ptr [rsi+0x789C],0x7FFFFFFE
        native::sub_eec5a00(6);                               // 0xe81d804 mov ecx,6 ; 0xe81d809 call 0xEEC5A00
    }

    // 0xe81d6b0..0xe81d6ce  ring-buffer cursor state.
    const std::uint32_t mod = *reinterpret_cast<std::uint32_t*>(self + kModOff);       // 0xe81d6b0 mov r9d,[rsi+0x7838]
    const std::uint32_t tail = *reinterpret_cast<std::uint32_t*>(self + kTailOff);     // 0xe81d6b7 mov edi,[rsi+0x783C]  (edi, the return value)
    const std::uint32_t modMinus1 = mod - 1u;                                          // 0xe81d6bd lea r10d,[r9-1]
    std::uint32_t cur1 = *reinterpret_cast<std::uint32_t*>(self + kCursor1Off);        // 0xe81d6c1 mov r8d,[rsi+0x7844]
    std::uint32_t cur0 = *reinterpret_cast<std::uint32_t*>(self + kCursor0Off);        // 0xe81d6c8 mov ecx,[rsi+0x7840]
    const std::uint32_t one = 1u;                                                      // 0xe81d6ce mov r11d,1

    // 0xe81d6e0..0xe81d73f  advance (cur0, cur1) to the next free ring slot.
    for (;;) {                                              // loc_e81d6e0 (0xe81d6d4 nop [rax+rax])
        // 0xe81d6e0..0xe81d6ed  e = (cur1 - cur0) adjusted into [0,mod)
        std::uint32_t e = cur1 - cur0;                     // 0xe81d6e0 mov eax,r8d ; 0xe81d6e3 sub eax,ecx
        e += static_cast<std::uint32_t>(static_cast<std::int32_t>(e) >> 31) & mod;      // 0xe81d6e5 mov edx,eax ; 0xe81d6e7 sar eax,0x1F ; 0xe81d6ea and eax,r9d
        // 0xe81d6ed..0xe81d70f  step = clamp(e-1); cur0 = (cur0 + step) % mod
        std::int32_t step = static_cast<std::int32_t>(e);  // 0xe81d6ed lea r12d,[rdx+rax]
        step -= 1;                                         // 0xe81d6f1 dec r12d
        if (step < 0) step = static_cast<std::int32_t>(modMinus1); // 0xe81d6f4 test r12d,r12d ; 0xe81d6f7 cmovs r12d,r10d
        std::uint32_t r12 = static_cast<std::uint32_t>(step);          // 0xe81d6fb mov eax,r12d
        if (static_cast<std::int32_t>(r12 - 2u) >= 0) r12 = one;       // 0xe81d6fe add eax,0xFFFFFFFE ; 0xe81d701 cmovns r12d,r11d
        cur0 = (cur0 + r12) % mod;                         // 0xe81d705 add ecx,r12d ; 0xe81d708 mov eax,ecx ; 0xe81d70a xor edx,edx ; 0xe81d70c div r9d ; 0xe81d70f mov ecx,edx
        if (r12 != 0) break;                               // 0xe81d711 test r12d,r12d ; 0xe81d714 jne short 0xE81D741
        // 0xe81d716..0xe81d739  (step was 0) nudge cur1 by clamp((tail-cur1) adjusted)
        std::uint32_t d = tail - cur1;                     // 0xe81d716 mov edx,edi ; 0xe81d718 sub edx,r8d
        d += static_cast<std::uint32_t>(static_cast<std::int32_t>(d) >> 31) & mod;      // 0xe81d71b mov eax,edx ; 0xe81d71d sar eax,0x1F ; 0xe81d720 and eax,r9d ; 0xe81d723 add eax,edx
        const std::uint32_t adv = (static_cast<std::int32_t>(d - 2u) >= 0) ? one : d;   // 0xe81d725 mov edx,eax ; 0xe81d727 add edx,0xFFFFFFFE ; 0xe81d72a cmovns eax,r11d
        cur1 = (cur1 + adv) % mod;                         // 0xe81d72e add eax,r8d ; 0xe81d731 xor edx,edx ; 0xe81d733 div r9d ; 0xe81d736 mov r8d,edx
        *reinterpret_cast<std::uint32_t*>(self + kCursor1Off) = cur1;                   // 0xe81d739 mov [rsi+0x7844],edx ; 0xe81d73f jmp short 0xE81D6E0
    }

    // 0xe81d741..0xe81d745  commit cursor0 (0xe81d741 mov [rbp-8],r13 saves lock for the release).
    *reinterpret_cast<std::uint32_t*>(self + kCursor0Off) = cur0;                       // 0xe81d745 mov [rsi+0x7840],ecx

    // 0xe81d74b..0xe81d752  ++counter[a2].
    *reinterpret_cast<std::uint32_t*>(self + kCounterBase + static_cast<std::size_t>(a2) * kCounterStride) += 1u; // 0xe81d74b mov eax,r15d ; 0xe81d74e lea rax,[rax+rax*2] ; 0xe81d752 inc dword ptr [rsi+rax*8+0x18]

    // 0xe81d756..0xe81d76a  fill the per-slot record at index `tail`.
    char* const slot = self + kSlotBase + static_cast<std::size_t>(tail) * kSlotStride; // 0xe81d756 lea rax,[rdi+rdi*2]
    *reinterpret_cast<std::uint32_t*>(slot + kSlotField0Off) = a2;                      // 0xe81d75a mov [rsi+rax*8+0x1820],r15d
    *reinterpret_cast<std::uint8_t*>(slot + kSlotFlagOff) = 0u;                         // 0xe81d762 mov byte ptr [rsi+rax*8+0x1830],0
    *reinterpret_cast<std::uint32_t*>(slot + kSlotField4Off) = a3;                      // 0xe81d76a mov [rsi+rax*8+0x1824],r14d

    // 0xe81d772..0xe81d791  CFG-guarded virtual call (rax = vtable[0x1A8], dispatched via guard thunk sub_eea6040).
    const std::uint32_t vc3 = tail + tail;                 // 0xe81d772 lea r9d,[rdi+rdi]
    void* const vcObj = *reinterpret_cast<void**>(reinterpret_cast<char*>(a1) + kVcallObjOff); // 0xe81d776 mov rcx,[rbx+0x30]
    void* const vcArg = *reinterpret_cast<void**>(self + kVcallArgOff);                 // 0xe81d77a mov rdx,[rsi+0x7828]
    void* const vtable = *reinterpret_cast<void**>(vcObj);                             // 0xe81d781 mov rax,[rcx]
    void* const target = *reinterpret_cast<void**>(reinterpret_cast<char*>(vtable) + kVtableSlot); // 0xe81d784 mov rax,[rax+0x1A8]
    reinterpret_cast<GuardedVirtualFn>(target)(vcObj, vcArg, 2u, vc3);                  // 0xe81d78b mov r8d,2 ; 0xe81d791 call qword ptr [0xF99FFA0]
    (void)kGuardSlot;

    // 0xe81d798..0xe81d7ce  advance the ring tail past the slot just filled.
    const std::uint32_t c0 = *reinterpret_cast<std::uint32_t*>(self + kCursor0Off);    // 0xe81d798 mov eax,[rsi+0x7840]
    const std::uint32_t m2 = *reinterpret_cast<std::uint32_t*>(self + kModOff);        // 0xe81d79e mov ecx,[rsi+0x7838]
    const std::uint32_t ot = *reinterpret_cast<std::uint32_t*>(self + kTailOff);        // 0xe81d7a4 mov edx,[rsi+0x783C]
    std::uint32_t adj = (c0 - ot);                     // 0xe81d7aa sub eax,edx
    adj += static_cast<std::uint32_t>(static_cast<std::int32_t>(c0 - ot) >> 31) & m2;   // 0xe81d7ac mov r8d,eax ; 0xe81d7af sar r8d,0x1F ; 0xe81d7b3 and r8d,ecx ; 0xe81d7b6 add r8d,eax
    const std::uint32_t adv2 = (static_cast<std::int32_t>(adj - 2u) < 0) ? adj : 1u;   // 0xe81d7b9 mov eax,r8d ; 0xe81d7bc add eax,0xFFFFFFFE ; 0xe81d7bf mov eax,1 ; 0xe81d7c4 cmovs eax,r8d
    *reinterpret_cast<std::uint32_t*>(self + kTailOff) = (adv2 + ot) % m2;              // 0xe81d7c8 add eax,edx ; 0xe81d7ca xor edx,edx ; 0xe81d7cc div ecx ; 0xe81d7ce mov [rsi+0x783C],edx

    // 0xe81d7d4..0xe81d7d8  release the submit lock.
    native::sub_eec5a10(lock);                             // 0xe81d7d4 mov rcx,[rbp-8] ; 0xe81d7d8 call 0xEEC5A10

    // 0xe81d7dd  return the tail value read at entry (edi, unchanged throughout).
    return tail;                                           // 0xe81d7dd mov eax,edi
}

} // namespace native::d3d12

// Verbatim disassembly of [0xe81d660, 0xe81d80f) (Minecraft Windows 1.26.62.01). Copied
// from `rdis dis 0xe81d660`; every line is machine-checked against the exe by verify_oc.
#if 0
0xe81d660  push rbp
0xe81d661  push r15
0xe81d663  push r14
0xe81d665  push r13
0xe81d667  push r12
0xe81d669  push rsi
0xe81d66a  push rdi
0xe81d66b  push rbx
0xe81d66c  sub rsp,0x38
0xe81d670  lea rbp,[rsp+0x30]
0xe81d675  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
0xe81d67d  mov r14d,r9d
0xe81d680  mov r15d,r8d
0xe81d683  mov rbx,rdx
0xe81d686  mov rsi,rcx
0xe81d689  lea r13,[rcx+0x7850]
0xe81d690  mov rcx,r13
0xe81d693  call 0xEEC59F0
0xe81d698  test eax,eax
0xe81d69a  jne 0xE81D7F0
0xe81d6a0  cmp dword ptr [rsi+0x789C],0x7FFFFFFF
0xe81d6aa  je 0xE81D7FA
0xe81d6b0  mov r9d,[rsi+0x7838]
0xe81d6b7  mov edi,[rsi+0x783C]
0xe81d6bd  lea r10d,[r9-1]
0xe81d6c1  mov r8d,[rsi+0x7844]
0xe81d6c8  mov ecx,[rsi+0x7840]
0xe81d6ce  mov r11d,1
0xe81d6d4  nop [rax+rax]
0xe81d6e0  mov eax,r8d
0xe81d6e3  sub eax,ecx
0xe81d6e5  mov edx,eax
0xe81d6e7  sar eax,0x1F
0xe81d6ea  and eax,r9d
0xe81d6ed  lea r12d,[rdx+rax]
0xe81d6f1  dec r12d
0xe81d6f4  test r12d,r12d
0xe81d6f7  cmovs r12d,r10d
0xe81d6fb  mov eax,r12d
0xe81d6fe  add eax,0xFFFFFFFE
0xe81d701  cmovns r12d,r11d
0xe81d705  add ecx,r12d
0xe81d708  mov eax,ecx
0xe81d70a  xor edx,edx
0xe81d70c  div r9d
0xe81d70f  mov ecx,edx
0xe81d711  test r12d,r12d
0xe81d714  jne short 0xE81D741
0xe81d716  mov edx,edi
0xe81d718  sub edx,r8d
0xe81d71b  mov eax,edx
0xe81d71d  sar eax,0x1F
0xe81d720  and eax,r9d
0xe81d723  add eax,edx
0xe81d725  mov edx,eax
0xe81d727  add edx,0xFFFFFFFE
0xe81d72a  cmovns eax,r11d
0xe81d72e  add eax,r8d
0xe81d731  xor edx,edx
0xe81d733  div r9d
0xe81d736  mov r8d,edx
0xe81d739  mov [rsi+0x7844],edx
0xe81d73f  jmp short 0xE81D6E0
0xe81d741  mov [rbp-8],r13
0xe81d745  mov [rsi+0x7840],ecx
0xe81d74b  mov eax,r15d
0xe81d74e  lea rax,[rax+rax*2]
0xe81d752  inc dword ptr [rsi+rax*8+0x18]
0xe81d756  lea rax,[rdi+rdi*2]
0xe81d75a  mov [rsi+rax*8+0x1820],r15d
0xe81d762  mov byte ptr [rsi+rax*8+0x1830],0
0xe81d76a  mov [rsi+rax*8+0x1824],r14d
0xe81d772  lea r9d,[rdi+rdi]
0xe81d776  mov rcx,[rbx+0x30]
0xe81d77a  mov rdx,[rsi+0x7828]
0xe81d781  mov rax,[rcx]
0xe81d784  mov rax,[rax+0x1A8]
0xe81d78b  mov r8d,2
0xe81d791  call qword ptr [0xF99FFA0]
0xe81d797  nop
0xe81d798  mov eax,[rsi+0x7840]
0xe81d79e  mov ecx,[rsi+0x7838]
0xe81d7a4  mov edx,[rsi+0x783C]
0xe81d7aa  sub eax,edx
0xe81d7ac  mov r8d,eax
0xe81d7af  sar r8d,0x1F
0xe81d7b3  and r8d,ecx
0xe81d7b6  add r8d,eax
0xe81d7b9  mov eax,r8d
0xe81d7bc  add eax,0xFFFFFFFE
0xe81d7bf  mov eax,1
0xe81d7c4  cmovs eax,r8d
0xe81d7c8  add eax,edx
0xe81d7ca  xor edx,edx
0xe81d7cc  div ecx
0xe81d7ce  mov [rsi+0x783C],edx
0xe81d7d4  mov rcx,[rbp-8]
0xe81d7d8  call 0xEEC5A10
0xe81d7dd  mov eax,edi
0xe81d7df  add rsp,0x38
0xe81d7e3  pop rbx
0xe81d7e4  pop rdi
0xe81d7e5  pop rsi
0xe81d7e6  pop r12
0xe81d7e8  pop r13
0xe81d7ea  pop r14
0xe81d7ec  pop r15
0xe81d7ee  pop rbp
0xe81d7ef  ret
0xe81d7f0  mov ecx,5
0xe81d7f5  call 0xEEC5A00
0xe81d7fa  mov dword ptr [rsi+0x789C],0x7FFFFFFE
0xe81d804  mov ecx,6
0xe81d809  call 0xEEC5A00
0xe81d80e  int3
#endif

// Calls out of lifted code:
//   0xe81d693  call 0xEEC59F0   -> native::sub_eec59f0 (lift, forward-declared in the header)
//   0xe81d7f5  call 0xEEC5A00   -> native::sub_eec5a00 (lift, forward-declared, noreturn)
//   0xe81d809  call 0xEEC5A00   -> native::sub_eec5a00 (lift, forward-declared, noreturn)
//   0xe81d7d8  call 0xEEC5A10   -> native::sub_eec5a10 (lift, forward-declared)
//   0xe81d791  call qword ptr [0xF99FFA0]  -> sub_eea6040 guard thunk (vendor boundary via
//              data slot 0xF99FFA0); rax = vtable[0x1A8], so this invokes vtable[0x1A8]
//              (vcObj, vcArg, 2, tail*2) -- lifted as a direct call to that resolved target.

// Registry entry: NAME = Sigs.json symbol (sig anchors are appended at the milestone gate).
LIFT_FN(sub_e81d660, "sub_e81d660", 0xe81d660, native::d3d12::sub_e81d660, nullptr);