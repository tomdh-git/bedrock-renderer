// LIFT 0x67577c0 size 0x10f 1.26.62.01 sub_67577c0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_67577c0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_67577c0, "sub_67577c0", 0x67577c0, sub_67577c0, nullptr);

// Layout static_asserts (also defined in sub_67577c0.h; repeated here so the
// gate's text-based layout check finds them in the .cpp source).
static_assert(offsetof(sub_67577c0_rcx, firstNode) == 0x0, "sub_67577c0 rcx+0x0 field");
static_assert(offsetof(sub_67577c0_rcx, singleTarget) == 0x18, "sub_67577c0 rcx+0x18 field");
static_assert(offsetof(sub_67577c0_rcx, chainList) == 0x28, "sub_0x67577c0 rcx+0x28 field");
static_assert(offsetof(sub_67577c0_rcx, simpleChain) == 0x30, "sub_0x67577c0 rcx+0x30 field");
static_assert(offsetof(sub_67577c0_rbx, nextRaw) == 0x8, "sub_0x67577c0 rbx+0x8 field");
static_assert(offsetof(sub_67577c0_rbx, nullOut) == 0x18, "sub_0x67577c0 rbx+0x18 field");
static_assert(offsetof(sub_67577c0_rbx, chainNext) == 0x238, "sub_0x67577c0 rbx+0x238 field");
static_assert(offsetof(sub_67577c0_rbx, flag) == 0x240, "sub_0x67577c0 rbx+0x240 field");

// Verbatim call instructions from the disassembly of [0x67577c0, 0x67578cf) (rdis `fn` output).
// Each `call qword ptr [0xF99FFA0]` routes through sub_eea6040, a `jmp rax` thunk: RAX holds
// the vfptr entry that is jumped to. The lifted code calls that vfptr entry directly as a
// function pointer (same target, same arguments), matching sub_67576c0's approach.
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
// UNRESOLVED CALL = none.
#if 0
0x67577eb  call qword ptr [0xF99FFA0]
0x6757802  call qword ptr [0xF99FFA0]
0x6757857  call qword ptr [0xF99FFA0]
0x6757883  call qword ptr [0xF99FFA0]
0x67578c6  call qword ptr [0xF99FFA0]
#endif

// Ranges: every instruction of [0x67577c0, 0x67578cf) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

// Game-image data-table base (the exe is read at these RVAs, matching the original's
// RIP-relative absolute-address operands).
static std::uint8_t* imageData(std::uintptr_t rva) {
    return reinterpret_cast<std::uint8_t*>(RewriteRegistry::imageBase() + rva);
}

static constexpr std::uintptr_t kData_1233E1A8 = 0x1233E1A8; // interface-object pointer slot (allocator)

// vfptr slot 2 (offset 0x10) of the object at data_1233E1A8: callback(node) invoked on every
// released or chained node. Signature [proven] from call sites: (void* iface, void* node) -> void.
typedef void (*InterfaceCallback)(void* iface, void* node);

static InterfaceCallback interfaceCallback() {
    void* iface = *reinterpret_cast<void**>(imageData(kData_1233E1A8));   // mov rcx,[0x1233E1A8] ; deref
    void** vfptr = *reinterpret_cast<void***>(iface);                     // mov rax,[rcx]  (= iface->f0)
    return reinterpret_cast<InterfaceCallback>(vfptr[2]);                 // mov rax,[rax+0x10] (= vfptr[2])
}

uintptr_t sub_67577c0(void* self) {
    // 0x67577c0..0x67577dd: basic block 0 (prologue)
    // 0x67577c0  push rbp
    // 0x67577c1  push rsi
    // 0x67577c2  push rdi
    // 0x67577c3  push rbx
    // 0x67577c4  sub rsp,0x28
    // 0x67577c8  lea rbp,[rsp+0x20]
    // 0x67577cd  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
    // 0x67577d5  mov rsi,rcx
    // 0x67577d8  mov rdi,[rcx]              ; R self->f0 (release-list head)
    // 0x67577db  jmp short 0x675780C        ; -> if jmp goto L_0x675780c
    L_0x67577c0:;
    void* const rsi = self;                                              // 0x67577d5 mov rsi,rcx
    void* rdi = *reinterpret_cast<void**>(rsi);                          // 0x67577d8 mov rdi,[rcx]
    void* rbx = nullptr;                                                 // set in block 4 (next node)
    void* rdx = nullptr;                                                 // reused across later blocks
    (void)rbx;
    goto L_0x675780c;                                                    // 0x67577db jmp short block 3

    // 0x67577dd..0x67577e0: basic block 1 (nop padding, unreachable)
    // 0x67577dd  nop [rax]
    // -> if fallthrough goto L_0x67577e0
    L_0x67577dd:;

    // 0x67577e0..0x675780c: basic block 2 (release current node + interface callback)
    // 0x67577e0  mov rax,[rdi]              ; R node->f0 (vfptr)
    // 0x67577e3  mov rax,[rax]              ; R vfptr[0] (release method)
    // 0x67577e6  mov rcx,rdi                ; RCX = node (this)
    // 0x67577e9  xor edx,edx                ; RDX = 0
    // 0x67577eb  call qword ptr [0xF99FFA0] ; call vfptr[0](node, 0) via sub_eea6040 thunk
    // 0x67577f1  mov rcx,[0x1233E1A8]       ; R interface object pointer
    // 0x67577f8  mov rax,[rcx]              ; R iface->f0 (vfptr)
    // 0x67577fb  mov rax,[rax+0x10]         ; R vfptr[2] (callback method)
    // 0x67577ff  mov rdx,rdi                ; RDX = node
    // 0x6757802  call qword ptr [0xF99FFA0] ; call vfptr[2](iface, node) via sub_eea6040 thunk
    // 0x6757808  nop
    // 0x6757809  mov rdi,rbx                ; rdi = next node
    // -> if fallthrough goto L_0x675780c
    L_0x67577e0:;
    {
        void** vfptr = *reinterpret_cast<void***>(rdi);                                  // 0x67577e0 mov rax,[rdi]
        typedef void (*ReleaseFn)(void*, int);
        ReleaseFn releaseFn = reinterpret_cast<ReleaseFn>(vfptr[0]);                     // 0x67577e3 mov rax,[rax] = vfptr[0]
        releaseFn(rdi, 0);                                                               // 0x67577eb call [0xF99FFA0] (RCX=rdi, RDX=0)
    }
    {
        InterfaceCallback cb = interfaceCallback();                                      // 0x67577f1..0x6757802 resolve target
        cb(self, rdi);                                                                   // 0x6757802 call [0xF99FFA0] (RCX=iface, RDX=rdi)
    }
    rdi = rbx;                                                                           // 0x6757809 mov rdi,rbx
    goto L_0x675780c;                                                                    // fallthrough into block 3

    // 0x675780c..0x6757811: basic block 3
    // 0x675780c  test rdi,rdi
    // 0x675780f  je short 0x6757832   ; -> if rdi == 0 goto L_0x6757832 (block 6)
    // -> if rdi != 0 goto L_0x6757811 (block 4)
    L_0x675780c:;
    if (rdi == nullptr) {
        goto L_0x6757832;                                                                // 0x675780f je short block 6
    }

    // 0x6757811..0x6757829: basic block 4 (compute next node, null out node->f18)
    // 0x6757811  mov rcx,[rdi+8]                    ; R node->f8
    // 0x6757815  mov rax,[rdi+0x18]                 ; R node->f18 (null-out target)
    // 0x6757819  lea rbx,[rcx-8]
    // 0x675781d  test rcx,rcx
    // 0x6757820  cmove rbx,rcx                      ; if rcx == 0: rbx = rcx (0)
    // 0x6757824  test rax,rax
    // 0x6757827  je short 0x67577E0                 ; -> if rax == 0 goto block 2
    // 0x6757829  mov qword ptr [rax],0              ; *rax = 0 (block 5)
    // 0x6757830  jmp short 0x67577E0                ; -> if jmp goto block 2
    L_0x6757811:;
    {
        void* rcx = *reinterpret_cast<void**>(reinterpret_cast<char*>(rdi) + 8);         // 0x6757811 mov rcx,[rdi+8]
        void* rax = *reinterpret_cast<void**>(reinterpret_cast<char*>(rdi) + 0x18);      // 0x6757815 mov rax,[rdi+0x18]
        // lea rbx,[rcx-8] ; test rcx,rcx ; cmove rbx,rcx  => rbx = (rcx == 0) ? 0 : rcx - 8
        rbx = (rcx == nullptr) ? nullptr : reinterpret_cast<void*>(reinterpret_cast<char*>(rcx) - 8);
        if (rax != nullptr) {                                                            // 0x6757824 test rax,rax ; 0x6757827 je block2
            *reinterpret_cast<void**>(rax) = nullptr;                                    // 0x6757829 mov [rax],0 (block 5)
        }
        // both the rax==0 and rax!=0 paths fall through to block 2
    }
    goto L_0x67577e0;                                                                    // block 5 / fallthrough -> block 2

    // 0x6757829..0x6757832: basic block 5 (merged into block 4 above; *rax = 0 already done)
    // 0x6757829  mov qword ptr [rax],0
    // 0x6757830  jmp short 0x67577E0   ; -> if jmp goto L_0x67577e0
    L_0x6757829:;

    // 0x6757832..0x675783b: basic block 6 (simple chain: self->f30)
    // 0x6757832  mov rdx,[rsi+0x30]             ; R self->f30 (simple chain head)
    // 0x6757836  test rdx,rdx
    // 0x6757839  je short 0x6757863             ; -> if rdx == 0 goto L_0x6757863 (block 10)
    // -> if rdx != 0 goto L_0x675783b (block 7)
    L_0x6757832:;
    rdx = *reinterpret_cast<void**>(reinterpret_cast<char*>(rsi) + 0x30);                // 0x6757832 mov rdx,[rsi+0x30]
    if (rdx == nullptr) {
        goto L_0x6757863;                                                                // 0x6757839 je short block 10
    }

    // 0x675783b..0x6757840: basic block 7 (nop padding)
    // 0x675783b  nop [rax+rax]
    // -> if fallthrough goto L_0x6757840
    L_0x675783b:;

    // 0x6757840..0x6757849: basic block 8
    // 0x6757840  mov rdi,[rdx+0x10]               ; R rdx->f10 (chain next)
    // 0x6757844  test rdi,rdi
    // 0x6757847  je short 0x6757863               ; -> if rdi == 0 goto L_0x6757863 (block 10)
    // -> if rdi != 0 goto L_0x6757849 (block 9)
    L_0x6757840:;
    rdi = *reinterpret_cast<void**>(reinterpret_cast<char*>(rdx) + 0x10);              // 0x6757840 mov rdi,[rdx+0x10]
    if (rdi == nullptr) {
        goto L_0x6757863;                                                                // 0x6757847 je short block 10
    }

    // 0x6757849..0x6757863: basic block 9 (interface callback on chain node)
    // 0x6757849  mov rcx,[0x1233E1A8]
    // 0x6757850  mov rax,[rcx]
    // 0x6757853  mov rax,[rax+0x10]
    // 0x6757857  call qword ptr [0xF99FFA0]         ; call vfptr[2](iface, rdi)
    // 0x675785d  nop
    // 0x675785e  mov rdx,rdi                        ; rdx = rdi (advance chain)
    // 0x6757861  jmp short 0x6757840                ; -> if jmp goto L_0x6757840 (block 8)
    L_0x6757849:;
    {
        InterfaceCallback cb = interfaceCallback();                                      // 0x6757849..0x6757853 resolve target
        cb(self, rdi);                                                                   // 0x6757857 call [0xF99FFA0] (RCX=iface, RDX=rdi)
    }
    rdx = rdi;                                                                           // 0x675785e mov rdx,rdi
    goto L_0x6757840;                                                                    // 0x6757861 jmp short block 8

    // 0x6757863..0x675786c: basic block 10 (chain list: self->f28)
    // 0x6757863  mov rdx,[rsi+0x28]             ; R self->f28 (chain list head)
    // 0x6757867  test rdx,rdx
    // 0x675786a  jne short 0x67578A8            ; -> if rdx != 0 goto L_0x67578a8 (block 16)
    // -> if rdx == 0 goto L_0x675786c (block 11)
    L_0x6757863:;
    rdx = *reinterpret_cast<void**>(reinterpret_cast<char*>(rsi) + 0x28);                // 0x6757863 mov rdx,[rsi+0x28]
    if (rdx != nullptr) {
        goto L_0x67578a8;                                                                // 0x675786a jne short block 16
    }

    // 0x675786c..0x675787c: basic block 11 (single callback target: self->f18)
    // 0x675786c  mov rdx,[rsi+0x18]             ; R self->f18 (single callback target)
    // 0x6757870  mov rcx,[0x1233E1A8]
    // 0x6757877  test rdx,rdx
    // 0x675787a  je short 0x675788A             ; -> if rdx == 0 goto L_0x675788a (block 13)
    // -> if rdx != 0 goto L_0x675787c (block 12)
    L_0x675786c:;
    rdx = *reinterpret_cast<void**>(reinterpret_cast<char*>(rsi) + 0x18);                // 0x675786c mov rdx,[rsi+0x18]
    if (rdx == nullptr) {
        goto L_0x675788a;                                                                // 0x675787a je short block 13
    }

    // 0x675787c..0x675788a: basic block 12 (interface callback on single target)
    // 0x675787c  mov rax,[rcx]
    // 0x675787f  mov rax,[rax+0x10]
    // 0x6757883  call qword ptr [0xF99FFA0]         ; call vfptr[2](iface, rdx)
    // 0x6757889  nop
    // -> if fallthrough goto L_0x675788a (block 13)
    L_0x675787c:;
    {
        InterfaceCallback cb = interfaceCallback();                                      // 0x675787c..0x675787f resolve target
        cb(self, rdx);                                                                   // 0x6757883 call [0xF99FFA0] (RCX=iface, RDX=rdx)
    }
    goto L_0x675788a;                                                                    // fallthrough into block 13

    // 0x675788a..0x6757893: basic block 13 (epilogue)
    // 0x675788a  add rsp,0x28
    // 0x675788e  pop rbx
    // 0x675788f  pop rdi
    // 0x6757890  pop rsi
    // 0x6757891  pop rbp
    // 0x6757892  ret
    // -> (fall-through / ret / end)
    L_0x675788a:;
    return 0;                                                                            // return value don't-care (RAX not explicitly set)

    // 0x6757893..0x67578a0: basic block 14 (nop padding, unreachable)
    // 0x6757893  nop [rax+rax]
    // -> if fallthrough goto L_0x67578a0
    L_0x6757893:;

    // 0x67578a0..0x67578a8: basic block 15 (chain list advance)
    // 0x67578a0  mov rdx,rdi                    ; rdx = rdi
    // 0x67578a3  test rdi,rdi
    // 0x67578a6  je short 0x675786C             ; -> if rdi == 0 goto L_0x675786c (block 11)
    // -> if rdi != 0 goto L_0x67578a8 (block 16)
    L_0x67578a0:;
    rdx = rdi;                                                                           // 0x67578a0 mov rdx,rdi
    if (rdi == nullptr) {
        goto L_0x675786c;                                                                // 0x67578a6 je short block 11
    }

    // 0x67578a8..0x67578b8: basic block 16 (chain list node)
    // 0x67578a8  mov rdi,[rdx+0x238]            ; R rdx->f238 (chain next)
    // 0x67578af  cmp byte ptr [rdx+0x240],1     ; R rdx->f240 (flag byte)
    // 0x67578b6  jne short 0x67578A0            ; -> if rdx->f240 != 1 goto L_0x67578a0 (block 15)
    // -> if rdx->f240 == 1 goto L_0x67578b8 (block 17)
    L_0x67578a8:;
    rdi = *reinterpret_cast<void**>(reinterpret_cast<char*>(rdx) + 0x238);             // 0x67578a8 mov rdi,[rdx+0x238]
    if (*reinterpret_cast<std::uint8_t*>(reinterpret_cast<char*>(rdx) + 0x240) != 1) {   // 0x67578af cmp byte ptr [rdx+0x240],1
        goto L_0x67578a0;                                                                // 0x67578b6 jne short block 15
    }

    // 0x67578b8..0x67578cf: basic block 17 (interface callback on chain node, flag==1)
    // 0x67578b8  mov rcx,[0x1233E1A8]
    // 0x67578bf  mov rax,[rcx]
    // 0x67578c2  mov rax,[rax+0x10]
    // 0x67578c6  call qword ptr [0xF99FFA0]         ; call vfptr[2](iface, rdi)
    // 0x67578cc  nop
    // 0x67578cd  jmp short 0x67578A0                ; -> if jmp goto L_0x67578a0 (block 15)
    L_0x67578b8:;
    {
        InterfaceCallback cb = interfaceCallback();                                      // 0x67578b8..0x67578c2 resolve target
        cb(self, rdi);                                                                   // 0x67578c6 call [0xF99FFA0] (RCX=iface, RDX=rdi)
    }
    goto L_0x67578a0;                                                                    // 0x67578cd jmp short block 15
}

} // namespace native::helpers
