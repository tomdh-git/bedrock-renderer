// LIFT 0x67576c0 size 0xf8 1.26.62.01 sub_67576c0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_67576c0.h"
#include "client/features/render/native/helpers/sub_6ae330.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_67576c0, "sub_67576c0", 0x67576c0, sub_67576c0, nullptr);

// sub_67576c0 (0x67576c0, size 0xf8, 1.26.62.01): walks the element range [this+0x00 .. this+0x08)
// in steps of 0x10. For each element it releases the object referenced at [elem+0x18] through its
// vfptr (slot 0, flag 1), clears [elem+0x10], then releases/refcount-drops the object at [elem+0x08]
// (lock-dec +0x8; if zero, call vfptr[0] destructor; lock-dec +0xC; if zero, call vfptr[8] delete).
// After the loop it calls sub_6ae330(this+0x18) and zeroes [this+0x18] (16 bytes) and [this+0x28].
// RCX = this ('this'), return value is whatever RAX holds at ret (not explicitly set).
//
// Verbatim call instructions from the disassembly of [0x67576c0, 0x67577b8) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
// The three `call qword ptr [0xF99FFA0]` calls route through sub_eea6040, which is a `jmp rax` thunk:
// RAX holds the vfptr entry that is actually jumped to. The lifted code calls that vfptr entry
// directly as a function pointer, which is behaviorally identical (same target, same arguments).
#if 0
0x675774c  call qword ptr [0xF99FFA0]
0x675776f  call qword ptr [0xF99FFA0]
0x6757789  call qword ptr [0xF99FFA0]
0x6757798  call 0x6AE330
#endif

uintptr_t sub_67576c0(void* self) {
    // 0x67576c0..0x67576d7: basic block 0 (prologue)
    // 0x67576c0  push r15
    // 0x67576c2  push r14
    // 0x67576c4  push rsi
    // 0x67576c5  push rdi
    // 0x67576c6  push rbx
    // 0x67576c7  sub rsp,0x20
    // 0x67576cb  mov rsi,rcx
    // 0x67576ce  mov rbx,[rcx]
    // 0x67576d1  mov r14,[rcx+8]
    // 0x67576d5  jmp short 0x67576E4   -> if jmp goto L_0x67576e4
    L_0x67576c0:;
    void* const rsi = self;
    void* rbx = *reinterpret_cast<void**>(rsi);                        // 0x67576ce  mov rbx,[rcx]
    void* const r14 = *reinterpret_cast<void**>(
        reinterpret_cast<char*>(rsi) + 8);                             // 0x67576d1  mov r14,[rcx+8]

    // 0x67576d7..0x67576e0: basic block 1 (unreachable nop padding)
    // 0x67576d7  nop [rax+rax]   -> if fallthrough goto L_0x67576e0
    L_0x67576d7:;

    for (;;) {
        // Declare all loop-body locals here so that `goto` cannot jump over an
        // initialization (C++ forbids jumping into the scope of a variable with
        // an initializer). Values are assigned at their real instruction sites.
        void* rcx = nullptr;
        std::uint32_t eax = 0;
        std::uint32_t edx = 0;
        void* r15 = nullptr;
        void* rdi = nullptr;
        void* rax = nullptr;
        void* rcx2 = nullptr;

        // 0x67576e0..0x67576e4: basic block 2 (loop increment)
        // 0x67576e0  add rbx,0x10   -> if fallthrough goto L_0x67576e4
        L_0x67576e0:;
        rbx = reinterpret_cast<void*>(reinterpret_cast<char*>(rbx) + 0x10);

        // 0x67576e4..0x67576ed: basic block 3
        // 0x67576e4  cmp rbx,r14
        // 0x67576e7  je 0x6757794   -> if rbx == r14 goto L_0x6757794
        L_0x67576e4:;
        if (rbx == r14) {
            goto L_0x6757794;
        }

        // 0x67576ed..0x67576f6: basic block 4
        // 0x67576ed  mov rcx,[rbx+8]
        // 0x67576f1  test rcx,rcx
        // 0x67576f4  je short 0x67576E0   -> if rcx == 0 goto L_0x67576e0
        L_0x67576ed:;
        rcx = *reinterpret_cast<void**>(
            reinterpret_cast<char*>(rbx) + 8);                         // 0x67576ed  mov rcx,[rbx+8]
        if (rcx == nullptr) {
            goto L_0x67576e0;
        }

        // 0x67576f6..0x6757700: basic block 5
        // 0x67576f6  mov eax,[rcx+8]
        // 0x67576f9  nop [rax]   -> if fallthrough goto L_0x6757700
        L_0x67576f6:;
        eax = *reinterpret_cast<std::uint32_t*>(
            reinterpret_cast<char*>(rcx) + 8);                         // 0x67576f6  mov eax,[rcx+8]

        // 0x6757700..0x6757704: basic block 6
        // 0x6757700  test eax,eax
        // 0x6757702  je short 0x67576E0   -> if eax == 0 goto L_0x67576e0
        L_0x6757700:;
        if (eax == 0) {
            goto L_0x67576e0;
        }

        // 0x6757704..0x675770e: basic block 7
        // 0x6757704  lea edx,[rax+1]
        // 0x6757707  lock cmpxchg [rcx+8],edx
        // 0x675770c  jne short 0x6757700   -> if flags(Cmpxchg) != goto L_0x6757700
        L_0x6757704:;
        edx = eax + 1;                                                 // 0x6757704  lea edx,[rax+1]
        if (_InterlockedCompareExchange(
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<char*>(rcx) + 8),
                static_cast<long>(edx),
                static_cast<long>(eax)) != static_cast<long>(eax)) {   // 0x6757707 lock cmpxchg [rcx+8],edx
            goto L_0x6757700;                                          // 0x675770c jne short 0x6757700
        }

        // 0x675770e..0x675771a: basic block 8
        // 0x675770e  mov r15,[rbx]
        // 0x6757711  mov rdi,[rbx+8]
        // 0x6757715  test r15,r15
        // 0x6757718  je short 0x6757757   -> if r15 == 0 goto L_0x6757757
        L_0x675770e:;
        r15 = *reinterpret_cast<void**>(rbx);                          // 0x675770e  mov r15,[rbx]
        rdi = *reinterpret_cast<void**>(
            reinterpret_cast<char*>(rbx) + 8);                         // 0x6757711  mov rdi,[rbx+8]
        if (r15 == nullptr) {
            goto L_0x6757757;
        }

        // 0x675771a..0x6757741: basic block 9
        // 0x675771a  mov rax,[r15+0x18]
        // 0x675771e  mov dword ptr [rax],0xFFFF
        // 0x6757724  mov qword ptr [rax+4],0
        // 0x675772c  mov byte ptr [rax+0xC],0
        // 0x6757730  mov rcx,[rax+0x10]
        // 0x6757734  mov qword ptr [rax+0x10],0
        // 0x675773c  test rcx,rcx
        // 0x675773f  je short 0x6757752   -> if rcx == 0 goto L_0x6757752
        L_0x675771a:;
        rax = *reinterpret_cast<void**>(
            reinterpret_cast<char*>(r15) + 0x18);                      // 0x675771a  mov rax,[r15+0x18]
        *reinterpret_cast<std::uint32_t*>(rax) = 0xFFFFu;              // 0x675771e  mov dword ptr [rax],0xFFFF
        *reinterpret_cast<std::uint64_t*>(
            reinterpret_cast<char*>(rax) + 4) = 0;                     // 0x6757724  mov qword ptr [rax+4],0
        *reinterpret_cast<std::uint8_t*>(
            reinterpret_cast<char*>(rax) + 0xC) = 0;                   // 0x675772c  mov byte ptr [rax+0xC],0
        rcx2 = *reinterpret_cast<void**>(
            reinterpret_cast<char*>(rax) + 0x10);                      // 0x6757730  mov rcx,[rax+0x10]
        *reinterpret_cast<void**>(
            reinterpret_cast<char*>(rax) + 0x10) = nullptr;            // 0x6757734  mov qword ptr [rax+0x10],0
        if (rcx2 != nullptr) {
            // 0x6757741..0x6757752: basic block 10
            // 0x6757741  mov rax,[rcx]
            // 0x6757744  mov rax,[rax]
            // 0x6757747  mov edx,1
            // 0x675774c  call qword ptr [0xF99FFA0]   -> sub_eea6040 (RAX=vfptr[0], RCX=rcx2, RDX=1)
            // Calls vfptr2[0](rcx2, 1) through the sub_eea6040 (jmp rax) thunk.
            L_0x6757741:;
            void** const vfptr2 = *reinterpret_cast<void***>(rcx2);    // 0x6757741  mov rax,[rcx]
                                                                         // 0x6757744  mov rax,[rax]
            typedef void (*ReleaseFn)(void*, int);
            ReleaseFn const release = reinterpret_cast<ReleaseFn>(vfptr2[0]);
            release(rcx2, 1);                                          // 0x6757747 mov edx,1 ; 0x675774c call [0xF99FFA0]
        }

        // 0x6757752..0x6757757: basic block 11
        // 0x6757752  mov byte ptr [r15+0x10],0   -> if fallthrough goto L_0x6757757
        L_0x6757752:;
        *reinterpret_cast<std::uint8_t*>(
            reinterpret_cast<char*>(r15) + 0x10) = 0;                  // 0x6757752  mov byte ptr [r15+0x10],0

        // 0x6757757..0x675775c: basic block 12
        // 0x6757757  test rdi,rdi
        // 0x675775a  je short 0x67576E0   -> if rdi == 0 goto L_0x67576e0
        L_0x6757757:;
        if (rdi == nullptr) {
            goto L_0x67576e0;
        }

        // 0x675775c..0x6757766: basic block 13
        // 0x675775c  lock dec dword ptr [rdi+8]
        // 0x6757760  jne 0x67576E0   -> if (Dec) != 0 goto L_0x67576e0
        L_0x675775c:;
        if (_InterlockedDecrement(
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<char*>(rdi) + 8)) != 0) {         // 0x675775c lock dec dword ptr [rdi+8]
            goto L_0x67576e0;                                          // 0x6757760 jne 0x67576E0
        }

        // 0x6757766..0x675777f: basic block 14
        // 0x6757766  mov rax,[rdi]
        // 0x6757769  mov rax,[rax]
        // 0x675776c  mov rcx,rdi
        // 0x675776f  call qword ptr [0xF99FFA0]   -> sub_eea6040 (RAX=vfptr[0], RCX=rdi)
        // 0x6757775  lock dec dword ptr [rdi+0xC]
        // 0x6757779  jne 0x67576E0   -> if (Dec) != 0 goto L_0x67576e0
        L_0x6757766:;
        {
            void** const vfptr = *reinterpret_cast<void***>(rdi);      // 0x6757766  mov rax,[rdi]
                                                                        // 0x6757769  mov rax,[rax]
            typedef void (*DtorFn)(void*);
            DtorFn const dtor = reinterpret_cast<DtorFn>(vfptr[0]);    // 0x675776c mov rcx,rdi ; 0x675776f call [0xF99FFA0]
            dtor(rdi);                                                 // calls vfptr[0](rdi)
        }
        if (_InterlockedDecrement(
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<char*>(rdi) + 0xC)) != 0) {       // 0x6757775 lock dec dword ptr [rdi+0xC]
            goto L_0x67576e0;                                          // 0x6757779 jne 0x67576E0
        }

        // 0x675777f..0x6757794: basic block 15
        // 0x675777f  mov rax,[rdi]
        // 0x6757782  mov rax,[rax+8]
        // 0x6757786  mov rcx,rdi
        // 0x6757789  call qword ptr [0xF99FFA0]   -> sub_eea6040 (RAX=vfptr[8], RCX=rdi)
        // 0x675778f  jmp 0x67576E0   -> if jmp goto L_0x67576e0
        L_0x675777f:;
        {
            void** const vfptr = *reinterpret_cast<void***>(rdi);      // 0x675777f  mov rax,[rdi]
            typedef void (*DeleteFn)(void*);
            DeleteFn const del = reinterpret_cast<DeleteFn>(vfptr[8]); // 0x6757782 mov rax,[rax+8] ; 0x6757786 mov rcx,rdi ; 0x6757789 call [0xF99FFA0]
            del(rdi);                                                  // calls vfptr[8](rdi)
        }
        goto L_0x67576e0;                                              // 0x675778f  jmp 0x67576E0

L_0x6757794:
        // 0x6757794..0x67577b8: basic block 16
        // 0x6757794  lea rcx,[rsi+0x18]
        // 0x6757798  call 0x6AE330   -> sub_6ae330
        // 0x675779d  xorps xmm0,xmm0
        // 0x67577a0  movups [rsi+0x18],xmm0
        // 0x67577a4  mov qword ptr [rsi+0x28],0
        // 0x67577ac  add rsp,0x20
        // 0x67577b0  pop rbx
        // 0x67577b1  pop rdi
        // 0x67577b2  pop rsi
        // 0x67577b3  pop r14
        // 0x67577b5  pop r15
        // 0x67577b7  ret
        native::sub_6ae330(reinterpret_cast<void*>(
            reinterpret_cast<char*>(rsi) + 0x18));                     // 0x6757794 lea rcx,[rsi+0x18] ; 0x6757798 call 0x6AE330
        *reinterpret_cast<std::uint64_t*>(
            reinterpret_cast<char*>(rsi) + 0x18) = 0;                  // 0x675779d xorps ; 0x67577a0 movups [rsi+0x18],xmm0
        *reinterpret_cast<std::uint64_t*>(
            reinterpret_cast<char*>(rsi) + 0x20) = 0;                  // part of the 16-byte movups clear
        *reinterpret_cast<std::uint64_t*>(
            reinterpret_cast<char*>(rsi) + 0x28) = 0;                  // 0x67577a4  mov qword ptr [rsi+0x28],0
        return 0;                                                      // return value: RAX not explicitly set by original
    }
}

} // namespace native::helpers
