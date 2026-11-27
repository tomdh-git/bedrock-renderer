// LIFT 0xaaa6e0 size 0xd7 1.26.62.01 sub_aaa6e0
#include "client/features/render/native/Lift.h"
#include "sub_aaa6e0.h"

namespace native {

// sub_e935700 is a lift-set callee (completed lift, docs/data/native_boundary.tsv class 'lift').
// Called through its native symbol; ABI: argument in RCX, result in RAX (it tail-calls sub_392960).
extern void* sub_e935700(void* a0);

// sub_a89240 is a direct callee at 0xaaa72c. It is not present in docs/data/native_functions.tsv
// (only referenced as callees_outside_set) and not present in docs/data/native_boundary.tsv
// (present only as `0xa89240 3 ?` in native_boundary_candidates.tsv, unclassified).
// No native symbol exists for it; no wrapper is invented here. Signature and return value are
// unknown; the return value is discarded by the caller (RCX is overwritten before any use).
// Declared here only so the call site can be written.
extern void sub_a89240(void* a0);

// 0xaaa7b0 call qword ptr [0xF9A8C78] is an indirect call through data slot 0xF9A8C78
// (noreturn terminate / range-check-failure path). Not a blocker per rule 68: the pointer is
// read from the slot at call time and invoked as a function pointer; the slot RVA is documented.
extern "C" __declspec(noreturn) void f9a8c78_slot_call(void);

// Verbatim instructions of [0xaaa6e0, 0xaaa7b7) (rdis dis 0xaaa6e0; exact listing matches
// docs/progress/pack/aaa6e0.md lines 16-84). The function ends at 0xaaa7b7; 0xaaa7b6 int3 is
// the final byte (padding), 0xaaa7b7+ belongs to the following function.
#if 0
0xaaa6e0  push r14
0xaaa6e2  push rsi
0xaaa6e3  push rdi
0xaaa6e4  push rbx
0xaaa6e5  sub rsp,0x48
0xaaa6e9  movaps [rsp+0x30],xmm6
0xaaa6ee  mov rsi,rcx
0xaaa6f1  mov rax,[rcx]
0xaaa6f4  mov rcx,[rax+8]
0xaaa6f8  mov qword ptr [rcx],0
0xaaa6ff  mov rdi,[rax]
0xaaa702  test rdi,rdi
0xaaa705  je short 0xAAA782
0xaaa707  xorps xmm6,xmm6
0xaaa70a  jmp short 0xAAA746
0xaaa70c  nop [rax]
0xaaa710  lea r14,[rdi+0x178]
0xaaa717  call 0xE935700
0xaaa71c  movups [r14],xmm6
0xaaa720  mov qword ptr [r14+0x10],0
0xaaa728  lea rcx,[rdi+0x18]
0xaaa72c  call 0xA89240
0xaaa731  mov edx,0x190
0xaaa736  mov rcx,rdi
0xaaa739  call 0xE935700
0xaaa73e  mov rdi,rbx
0xaaa741  test rbx,rbx
0xaaa744  je short 0xAAA782
0xaaa746  mov rbx,[rdi]
0xaaa749  mov rcx,[rdi+0x178]
0xaaa750  test rcx,rcx
0xaaa753  je short 0xAAA728
0xaaa755  mov rdx,[rdi+0x188]
0xaaa75c  sub rdx,rcx
0xaaa75f  cmp rdx,0x1000
0xaaa766  jb short 0xAAA710
0xaaa768  mov rax,[rcx-8]
0xaaa76c  add rcx,0xFFFFFFFFFFFFFFF8
0xaaa770  sub rcx,rax
0xaaa773  cmp rcx,0x20
0xaaa777  jae short 0xAAA79D
0xaaa779  add rdx,0x27
0xaaa77d  mov rcx,rax
0xaaa780  jmp short 0xAAA710
0xaaa782  mov rcx,[rsi]
0xaaa785  mov edx,0x190
0xaaa78a  movaps xmm6,[rsp+0x30]
0xaaa78f  add rsp,0x48
0xaaa793  pop rbx
0xaaa794  pop rdi
0xaaa795  pop rsi
0xaaa796  pop r14
0xaaa798  jmp 0xE935700
0xaaa79d  mov qword ptr [rsp+0x20],0
0xaaa7a6  xor ecx,ecx
0xaaa7a8  xor edx,edx
0xaaa7aa  xor r8d,r8d
0xaaa7ad  xor r9d,r9d
0xaaa7b0  call qword ptr [0xF9A8C78]
0xaaa7b6  int3
#endif

void* sub_aaa6e0(void* a0) {
    // All locals declared up front so gotos never skip an initialization (MSVC rule).
    void* rsi = nullptr;
    void* rax = nullptr;
    void* P = nullptr;
    void* rdi = nullptr;
    void* rbx = nullptr;
    void* rcx = nullptr;
    void* r14 = nullptr;
    uintptr_t rdx = 0;

    // 0xaaa6e0..0xaaa70c: prologue; a0->RCX saved to RSI; P=[a0]; clear [P+8]; rdi=[P];
    //   0xaaa6e0  push r14
    //   0xaaa6e2  push rsi
    //   0xaaa6e3  push rdi
    //   0xaaa6e4  push rbx
    //   0xaaa6e5  sub rsp,0x48
    //   0xaaa6e9  movaps [rsp+0x30],xmm6
    //   0xaaa6ee  mov rsi,rcx                 ; RSI = a0
    //   0xaaa6f1  mov rax,[rcx]               ; RAX = P = [a0+0x0]
    //   0xaaa6f4  mov rcx,[rax+8]
    //   0xaaa6f8  mov qword ptr [rcx],0     ; [P+0x8] = 0
    //   0xaaa6ff  mov rdi,[rax]               ; RDI = [P+0x0]
    //   0xaaa702  test rdi,rdi
    //   0xaaa705  je short 0xAAA782           ; if rdi==0 -> tail to sub_e935700([a0])
    //   0xaaa707  xorps xmm6,xmm6             ; xmm6 = 0
    //   0xaaa70a  jmp short 0xAAA746          ; -> loop entry
    //   0xaaa70c  nop [rax]                   ; padding (unreachable)
    rsi = a0;
    rax = reinterpret_cast<void*>(*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(a0)));
    P = rax;
    *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(P) + 0x8) = 0;
    rdi = reinterpret_cast<void*>(*reinterpret_cast<uintptr_t*>(P));
    if (rdi == nullptr)
        goto loc_aaa782;
    // xmm6 = 0 (used below as zero to store)
    goto loc_aaa746;

loc_aaa746:                                   // 0xaaa746  ; loop entry
    //   0xaaa746  mov rbx,[rdi]               ; RBX = [rdi+0x0]
    //   0xaaa749  mov rcx,[rdi+0x178]         ; RCX = [rdi+0x178]
    //   0xaaa750  test rcx,rcx
    //   0xaaa753  je short 0xAAA728           ; if [rdi+0x178]==0 -> 0xaaa728
    //   0xaaa755  mov rdx,[rdi+0x188]         ; RDX = [rdi+0x188]
    //   0xaaa75c  sub rdx,rcx                 ; RDX -= RCX
    //   0xaaa75f  cmp rdx,0x1000
    //   0xaaa766  jb short 0xAAA710           ; if RDX < 0x1000 -> 0xaaa710
    //   0xaaa768  mov rax,[rcx-8]
    //   0xaaa76c  add rcx,0xFFFFFFFFFFFFFFF8  ; RCX -= 8
    //   0xaaa770  sub rcx,rax                 ; RCX -= RAX
    //   0xaaa773  cmp rcx,0x20
    //   0xaaa777  jae short 0xAAA79D          ; if RCX >= 0x20 -> terminate
    //   0xaaa779  add rdx,0x27                ; RDX += 0x27
    //   0xaaa77d  mov rcx,rax                 ; RCX = RAX
    //   0xaaa780  jmp short 0xAAA710          ; -> 0xaaa710
    rbx = reinterpret_cast<void*>(*reinterpret_cast<uintptr_t*>(rdi));
    rcx = reinterpret_cast<void*>(*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(rdi) + 0x178));
    if (rcx == nullptr)
        goto loc_aaa728;
    rdx = *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(rdi) + 0x188) - reinterpret_cast<uintptr_t>(rcx);
    if (rdx < 0x1000)
        goto loc_aaa710;
    rax = reinterpret_cast<void*>(*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(rcx) - 8));
    rcx = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(rcx) - 8);
    rcx = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(rcx) - reinterpret_cast<uintptr_t>(rax));
    if (reinterpret_cast<uintptr_t>(rcx) >= 0x20)
        goto loc_aaa79d;
    rdx += 0x27;
    rcx = rax;
    goto loc_aaa710;

loc_aaa710:                                   // 0xaaa710
    //   0xaaa710  lea r14,[rdi+0x178]         ; R14 = rdi + 0x178
    //   0xaaa717  call 0xE935700              ; sub_e935700(RCX)  [verbatim above]
    //   0xaaa71c  movups [r14],xmm6           ; [rdi+0x178] = 0
    //   0xaaa720  mov qword ptr [r14+0x10],0  ; [rdi+0x180] = 0
    r14 = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(rdi) + 0x178);
    sub_e935700(rcx);
    *reinterpret_cast<uintptr_t*>(r14) = 0;
    *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(r14) + 0x10) = 0;

loc_aaa728:                                   // 0xaaa728
    //   0xaaa728  lea rcx,[rdi+0x18]          ; RCX = rdi + 0x18
    //   0xaaa72c  call 0xA89240               ; sub_a89240(rdi+0x18)  - verbatim above
    //   0xaaa731  mov edx,0x190
    //   0xaaa736  mov rcx,rdi
    //   0xaaa739  call 0xE935700              ; sub_e935700(rdi)  [verbatim above]
    //   0xaaa73e  mov rdi,rbx
    //   0xaaa741  test rbx,rbx
    //   0xaaa744  je short 0xAAA782           ; if rbx==0 -> 0xaaa782
    sub_a89240(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(rdi) + 0x18));
    sub_e935700(rdi);
    rdi = rbx;
    if (rbx == nullptr)
        goto loc_aaa782;
    goto loc_aaa746;

loc_aaa782:                                   // 0xaaa782  ; rdi==0 or rbx==0 path -> tail call
    //   0xaaa782  mov rcx,[rsi]               ; RCX = [a0+0x0] = P
    //   0xaaa785  mov edx,0x190
    //   0xaaa78a  movaps xmm6,[rsp+0x30]      ; restore xmm6
    //   0xaaa78f  add rsp,0x48
    //   0xaaa793  pop rbx
    //   0xaaa794  pop rdi
    //   0xaaa795  pop rsi
    //   0xaaa796  pop r14
    //   0xaaa798  jmp 0xE935700               ; tail call sub_e935700(P); return its result
    return sub_e935700(P);

loc_aaa79d:                                   // 0xaaa79d  ; terminate path
    //   0xaaa79d  mov qword ptr [rsp+0x20],0
    //   0xaaa7a6  xor ecx,ecx
    //   0xaaa7a8  xor edx,edx
    //   0xaaa7aa  xor r8d,r8d
    //   0xaaa7ad  xor r9d,r9d
    //   0xaaa7b0  call qword ptr [0xF9A8C78]  ; terminate via data slot 0xF9A8C78 [verbatim above]
    //   0xaaa7b6  int3                        ; unreachable padding
    f9a8c78_slot_call();
    __assume(false);
}

} // namespace native

LIFT_FN(aaa6e0, "sub_aaa6e0", 0xAAA6E0, ::native::sub_aaa6e0, nullptr);
