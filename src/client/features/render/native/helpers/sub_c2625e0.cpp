// LIFT 0xc2625e0 size 0x130 1.26.62.01 sub_c2625e0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_c2625e0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_c2625e0, "sub_c2625e0", 0xc2625e0, sub_c2625e0, nullptr);

// Layout assertions for 0xc2625e0 (field offsets live in sub_c2625e0.h).
static_assert(offsetof(sub_c2625e0_rax, f0) == 0x0, "sub_c2625e0 layout rax+0x0");
static_assert(offsetof(sub_c2625e0_rax, f50) == 0x50, "sub_c2625e0 layout rax+0x50");

// Verbatim call instructions from the disassembly of [0xc2625e0, 0xc262710) (rdis `fn` output).
// Bare lines (two spaces after the address) are parsed by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
// All four calls target boundary functions:
//   0xc262666  call qword ptr [0xF99FFA0]  -> sub_eea6040   (boundary: vendor allocator thunk)
//   0xc2626d0  call qword ptr [0xF99FFA0]  -> sub_eea6040   (refcounted-target vtable slot 0)
//   0xc2626e7  call qword ptr [0xF99FFA0]  -> sub_eea6040   (refcounted-target vtable slot 1)
//   0xc262705  call 0x9BC830               -> sub_9bc830    (boundary: alloc)
// All calls target boundary functions; none are pending.
#if 0
0xc262666  call qword ptr [0xF99FFA0]
0xc2626d0  call qword ptr [0xF99FFA0]
0xc2626e7  call qword ptr [0xF99FFA0]
0xc262705  call 0x9BC830
#endif

// Ranges: every instruction of [0xc2625e0, 0xc262710) is covered by a block range comment
// and/or a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

extern "C" void* sub_eea6040(void* allocator, std::uint64_t size);
extern "C" void* sub_9bc830(std::uint64_t size);

namespace {

// Refcounted-target (base r14) vtable slot calls.
//   0xc2626c7  mov rax,[r14]      ; vtable pointer
//   0xc2626ca  mov rax,[rax]      ; slot 0
//   0xc2626d0  call ...           ; RCX = r14
static void vtableSlot0(void* object) {
    void** vtable = reinterpret_cast<void**>(*reinterpret_cast<void**>(object));
    reinterpret_cast<void(*)(void*)>(vtable[0])(object);
}

//   0xc2626dd  mov rax,[r14]
//   0xc2626e0  mov rax,[rax+8]    ; slot 1
//   0xc2626e7  call ...           ; RCX = r14
static void vtableSlot1(void* object) {
    void** vtable = reinterpret_cast<void**>(*reinterpret_cast<void**>(object));
    reinterpret_cast<void(*)(void*)>(vtable[1])(object);
}

} // namespace

uintptr_t sub_c2625e0(void* self, sub_c2625e0_rdx* a1, sub_c2625e0_r8* a2) {
    // x64 Microsoft ABI: RCX = self (out-pair), RDX = a1, R8 = a2; RAX = self.

    // 0xc2625e0..0xc262612: basic block 0
    // 0xc2625e0  push rbp
    // 0xc2625e1  push r15
    // 0xc2625e3  push r14
    // 0xc2625e5  push rsi
    // 0xc2625e6  push rdi
    // 0xc2625e7  push rbx
    // 0xc2625e8  sub rsp,0x98
    // 0xc2625ef  lea rbp,[rsp+0x80]
    // 0xc2625f7  mov qword ptr [rbp+0x10],0xFFFFFFFFFFFFFFFE
    // 0xc2625ff  mov rsi,rcx
    // 0xc262602  xorps xmm0,xmm0
    // 0xc262605  movaps [rbp-0x20],xmm0
    // 0xc262609  mov rax,[rdx+8]            ; R a1+0x8
    // 0xc26260d  test rax,rax
    // 0xc262610  je short 0xC26261C         ; -> if *(a1+0x8) == 0 goto L_0xc26261c
    // 0xc262612  lock inc dword ptr [rax+8] ; -> if *(a1+0x8) != 0 goto L_0xc262612
    // 0xc262616  mov rax,[rdx+8]
    // 0xc26261a  jmp short 0xC26261E
    sub_c2625e0_r14* refTarget = a1->f8;           // 0xc262609 mov rax,[rdx+8]
    if (refTarget != nullptr) {                    // 0xc26260d test / 0xc262610 je
        // 0xc262612..0xc26261c: basic block 1
        _InterlockedIncrement(
            reinterpret_cast<volatile LONG*>(&refTarget->f8));  // 0xc262612 lock inc dword [rax+8]
        refTarget = a1->f8;                        // 0xc262616 mov rax,[rdx+8]
    }                                              // 0xc26261a jmp L_0xc26261e
    // 0xc26261c..0xc26261e: basic block 2 (refTarget == nullptr; eax = 0)

    // 0xc26261e..0xc262679: basic block 3
    // 0xc26261e  mov [rbp],rdx
    // 0xc262622  mov r14,[rdx]
    // 0xc262625  mov rbx,[r8]
    // 0xc262628  mov [rbp-0x10],rbx
    // 0xc26262c  lea r15,[0xF478480]
    // 0xc262633  mov [rbp-0x60],r15
    // 0xc262637  mov [rbp-0x58],r14
    // 0xc26263b  mov [rbp+8],rax
    // 0xc26263f  mov [rbp-0x50],rax
    // 0xc262643  movaps [rbp-0x20],xmm0
    // 0xc262647  mov [rbp-0x48],rbx
    // 0xc26264b  lea rax,[rbp-0x60]
    // 0xc26264f  mov [rbp-0x28],rax
    // 0xc262653  mov rcx,[0x01233E1A8]
    // 0xc26265a  mov rax,[rcx]
    // 0xc26265d  mov rax,[rax+8]
    // 0xc262661  mov edx,0x58
    // 0xc262666  call qword ptr [0xF99FFA0]       ; -> sub_eea6040
    // 0xc26266c  nop
    // 0xc26266d  mov rdi,rax
    // 0xc262670  test rax,rax
    // 0xc262673  je 0xC262700                     ; -> if alloc == null goto L_0xc262700
    sub_c2625e0_rsi* out = reinterpret_cast<sub_c2625e0_rsi*>(self);   // 0xc2625ff mov rsi,rcx
    void* const a1_vtable = a1->f0;                // 0xc262622 mov r14,[rdx]
    void* const a2_user = a2->f0;                  // 0xc262625 mov rbx,[r8]
    sub_c2625e0_r14* savedRefTarget = refTarget;   // [rbp+0x08] = rax (read at 0xc2626a0)
    sub_c2625e0_rcx* const allocatorInterface =
        reinterpret_cast<sub_c2625e0_rcx*>(
            *reinterpret_cast<void**>(0x01233E1A8)); // 0xc262653 mov rcx,[0x01233E1A8]
    (void)allocatorInterface->f0;                  // 0xc26265a mov rax,[rcx] (dead read)
    (void)*reinterpret_cast<void**>(
        reinterpret_cast<uintptr_t>(allocatorInterface) + 8); // 0xc26265d mov rax,[rax+8] (dead read)
    sub_c2625e0_rax* obj =
        reinterpret_cast<sub_c2625e0_rax*>(sub_eea6040(allocatorInterface, 0x58ULL));
                                                     // 0xc262661 edx=0x58; 0xc262666 call [0xF99FFA0]
    if (obj == nullptr) {                          // 0xc262670 test / 0xc262673 je L_0xc262700
        // 0xc262700..0xc262710: basic block 9
        // 0xc262700  mov ecx,0x58
        // 0xc262705  call 0x9BC830                ; -> sub_9bc830
        // 0xc26270a  nop
        // 0xc26270b  jmp 0xC262679                ; -> goto block 4
        sub_9bc830(0x58ULL);
        // Original falls into block 4 with RDI untouched (its entry/caller value);
        // here obj is null, so the block-4 stores below target null and fault the
        // same way the original faults/corrupts on a stale RDI.
    }

    // 0xc262679..0xc2626c0: basic block 4
    // 0xc262679  mov rax,0x100000001
    // 0xc262683  mov [rdi+8],rax
    // 0xc262687  lea rax,[0xEFFC850]
    // 0xc26268e  mov [rdi],rax
    // 0xc262698  mov [rdi+0x10],r15      ; r15 = 0x00F478480 (0xc26262c)
    // 0xc26269c  mov [rdi+0x18],r14      ; r14 = a1->f0
    // 0xc2626a0  mov r14,[rbp+8]         ; r14 = saved refTarget
    // 0xc2626a4  mov [rdi+0x20],r14
    // 0xc2626a8  mov [rdi+0x28],rbx      ; rbx = a2->f0
    // 0xc262691  mov rax,rdi
    // 0xc262694  add rax,0x10
    // 0xc2626ac  mov [rdi+0x48],rax
    // 0xc2626b0  mov byte ptr [rdi+0x50],1
    // 0xc2626b4  mov [rsi],rax
    // 0xc2626b7  mov [rsi+8],rdi
    // 0xc2626bb  test r14,r14
    // 0xc2626be  je short 0xC2626ED      ; -> if r14 == 0 goto L_0xc2626ed
    obj->f8 = 0x100000001ULL;                         // 0xc262683
    obj->f0 = reinterpret_cast<void*>(0x00EFFC850ULL); // 0xc26268e
    obj->f10 = reinterpret_cast<void*>(0x00F478480ULL); // 0xc262698
    obj->f18 = a1_vtable;                            // 0xc26269c
    sub_c2625e0_r14* r14 = savedRefTarget;           // 0xc2626a0 mov r14,[rbp+8]
    obj->f20 = r14;                                  // 0xc2626a4
    obj->f28 = a2_user;                              // 0xc2626a8
    void* const payload =
        reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(obj) + 0x10); // 0xc262691/0xc262694
    obj->f48 = payload;                              // 0xc2626ac
    obj->f50 = 1;                                    // 0xc2626b0
    out->f0 = payload;                               // 0xc2626b4 mov [rsi],rax
    out->f8 = obj;                                   // 0xc2626b7 mov [rsi+8],rdi
    if (r14 == nullptr) goto blockReleaseDone;       // 0xc2626bb test / 0xc2626be je L_0xc2626ed

    // 0xc2626c0..0xc2626c7: basic block 5
    // 0xc2626c0  lock dec dword ptr [r14+8]
    // 0xc2626c5  jne short 0xC2626ED                ; -> if dec != 0 goto L_0xc2626ed
    if (_InterlockedDecrement(
            reinterpret_cast<volatile LONG*>(&r14->f8)) != 0) goto blockReleaseDone;
    // 0xc2626c7..0xc2626dd: basic block 6
    // 0xc2626c7  mov rax,[r14]
    // 0xc2626ca  mov rax,[rax]
    // 0xc2626cd  mov rcx,r14
    // 0xc2626d0  call qword ptr [0xF99FFA0]        ; vtable slot 0
    // 0xc2626d6  lock dec dword ptr [r14+0xC]
    // 0xc2626db  jne short 0xC2626ED               ; -> if dec != 0 goto L_0xc2626ed
    vtableSlot0(r14);
    if (_InterlockedDecrement(
            reinterpret_cast<volatile LONG*>(&r14->fc)) != 0) goto blockReleaseDone;
    // 0xc2626dd..0xc2626ed: basic block 7
    // 0xc2626dd  mov rax,[r14]
    // 0xc2626e0  mov rax,[rax+8]
    // 0xc2626e4  mov rcx,r14
    // 0xc2626e7  call qword ptr [0xF99FFA0]        ; vtable slot 1
    vtableSlot1(r14);
blockReleaseDone:;
    // 0xc2626ed..0xc262700: basic block 8
    // 0xc2626ed  mov rax,rsi
    // 0xc2626f0  add rsp,0x98
    // 0xc2626f7  pop rbx
    // 0xc2626f8  pop rdi
    // 0xc2626f9  pop rsi
    // 0xc2626fa  pop r14
    // 0xc2626fc  pop r15
    // 0xc2626fe  pop rbp
    // 0xc2626ff  ret
    return reinterpret_cast<uintptr_t>(self);
}

} // namespace native::helpers
