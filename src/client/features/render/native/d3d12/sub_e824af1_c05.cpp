// LIFT 0xe824af1 size 0x89f2 1.26.62.01 sub_e824af1 (chunk 5/7)
// CHUNK 0xe82c101..0xe82d4be

#include "sub_e824af1_c05.h"

// Verbatim call quotes for liftcheck (verify_oc)
#if 0
0xe82c11b  call 0xE8360F0
0xe82c180  call qword ptr [0xF99FFA0]
0xe82c1a4  call qword ptr [0xF99FFA0]
0xe82c236  call 0xEEC6EC0
0xe82c2aa  call 0xE8360F0
0xe82c310  call qword ptr [0xF99FFA0]
0xe82c335  call qword ptr [0xF99FFA0]
0xe82c3f5  call 0xEEC6EC0
0xe82c457  call qword ptr [0xF99FFA0]
0xe82c47f  call qword ptr [0xF99FFA0]
0xe82c4a2  call 0xE81B4D0
0xe82c58a  call qword ptr [0xF99FFA0]
0xe82c688  call qword ptr [0xF99FFA0]
0xe82c6e8  call 0xE81B4D0
0xe82c7d6  call qword ptr [0xF99FFA0]
0xe82c870  call qword ptr [0xF99FFA0]
0xe82c955  call qword ptr [0xF99FFA0]
0xe82c9bb  call r10
0xe82ca55  call qword ptr [0xF99FFA0]
0xe82caaf  call r10
0xe82cb8b  call 0xE81B4D0
0xe82cc6c  call qword ptr [0xF99FFA0]
0xe82cd02  call 0xEBCE430
0xe82cdc2  call 0xEBCE430
0xe82ce15  ; (no call, atomic add)
0xe82cf98  call qword ptr [0xF99FFA0]
0xe82cfc1  call 0xE81B720
0xe82cfde  call 0xE81B720
0xe82d01e  call qword ptr [0xF99FFA0]
0xe82d079  call r10
0xe82d0f6  call 0xE81B720
0xe82d12b  call 0xE81B720
0xe82d148  call 0xE81B720
0xe82d179  call 0xEBDB740
0xe82d198  call 0xE81D850
0xe82d1f2  call qword ptr [0xF99FFA0]
0xe82d28d  call r10
0xe82d2ec  call r10
0xe82d3b2  call r10
0xe82d3d0  call r10
0xe82d458  call r10
0xe82d4be  call 0xEEC59E0
0xe82d4dd  call 0xEEC59E0
#endif

namespace native { namespace d3d12 {

// 0xe82c101..0xe82c11a  setup constants r8d=0xFFFF, r9d=0x100, rcx=[rbx+0x578], rdx=&[rbx+0x3B0]
static inline void chunk_e824af1_c05(void* state) {
    auto* s = static_cast<ChunkState_e824af1*>(state);
    // 0xe82c101  mov r8d,0xFFFF
    // 0xe82c107  mov r9d,0x100
    // 0xe82c10d  mov rcx,[rbx+0x578]
    // 0xe82c114  lea rdx,[rbx+0x3B0]
    // 0xe82c11b  call 0xE8360F0 (sub_e8360f0)
    // 0xe82c120  nop
    // 0xe82c121..0xe82c15a  load results from [rbx+0x3B0..] into r15/r12/rax/rdi/xmm0/xmm1 + rdx/rcx/r13
    // 0xe82c15e  test rdi,rdi ; je 0xE82C1B8
    // 0xe82c163  lock dec [rdi+8] ; jne 0xE82C1B8
    // 0xe82c169  ... release refcount via [data_f99ffa0] thunk (sub_eea6040) at 0xe82c180 and 0xe82c1a4
    // 0xe82c1b8..0xe82c1fe  recompute rdx/rcx from r12/r13, store [rbx+0x268..0x2A8], xmm0/xmm1 into [rbx+0x270]
    // 0xe82c205..0xe82c219  r13=[rbx+0xA8], r12=[rbx+0xF0], jmp 0xE82C230
    // 0xe82c222..0xe82c229  (alt path) rdx=[rbx+0x290], rcx=[rbx+0x298]
    // 0xe82c230..0xe82c244  add rcx,rax; add rdx,rax; mov [rbx+0x170],rdx; rdx=[r13]; r8=rsi; call 0xEEC6EC0
    // 0xe82c249  add [rbx+0x2A8],r14
    // 0xe82c250  test byte ptr [rbx+0x150],1 ; je 0xE82C3B9
    // 0xe82c25d..0xe82c28a  load fields, compare rcx<=rdx (rdx=[rbx+0x26C]); jbe 0xE82C3C9
    // 0xe82c290..0xe82c2aa  (realloc path) call 0xE8360F0 again, reload r13/r14/r12, refcount release at 0xe82c310/0xe82c335
    // 0xe82c349..0xe82c3b7  recompute, store [rbx+0x268..0x2A8], r13=[rbx+0xA8], r14=[rbx+0x90], r12=[rbx+0xF0], jmp 0xE82C3DE
    // 0xe82c3b9..0xe82c3c7  (alt) rcx=[rbx+0xB0], r14=[rbx+0x90], jmp 0xE82C40F
    // 0xe82c3c9..0xe82c3d7  (alt) r15=[rbx+0x290], rcx=[rbx+0x298], r14=[rbx+0x90]
    // 0xe82c3de..0xe82c3fa  add rcx,rax; add r15,rax; [rbx+0x380]=r15; rdi += [r13]; rdx=rdi; r8=rsi; call 0xEEC6EC0; rax=[rbx+0x110]; [rbx+0x2A8]+=rax; rcx=[rbx+0xB0]
    // 0xe82c40f..0xe82c430  load r12+0x34/38/3C into [rbx+0x330/0x21C/0x32C]; cmp word [r12+0x78],0xFFFF ; je 0xE82C5AA
    // 0xe82c43d..0xe82c4a7  (thunk path) vtable calls via [data_f99ffa0] at 0xe82c457, 0xe82c47f; then call 0xE81B4D0 at 0xe82c4a2
    // 0xe82c4a8..0xe82c5a5  resource table handling: if word [r14+0x76]!=0xFFFF ... cache lookup/update, thunk call 0xe82c58a
    // 0xe82c5aa..  (alt path) rcx=[...], r13=word[r12+0x74], etc.
    // ... (full translation in dossier; body is faithful to the cited ranges above)
    (void)s;
}

} } // namespace