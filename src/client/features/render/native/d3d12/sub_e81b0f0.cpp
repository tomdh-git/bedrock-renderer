// LIFT 0xe81b0f0 size 0x14b 1.26.62.01 RendererContextD3D12 base slot 62
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e81b0f0.h"

#include <cstdint>
#include <intrin.h>

// Layout constants live in sub_e81b0f0.h; cross-check the target model here [V].
static_assert(sizeof(void*) == 8, "e81b0f0: x64 target");

namespace native {

namespace {

// 0xE951550: __security_check_cookie (crt boundary, noreturn on failure) [V],
// docs/data/native_boundary.tsv row 0xe951550 = crt. Called at 0xe81b235 with
// rcx = cookieStored ^ frame when the /GS cookie check at 0xe81b21c fails.
native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");

// Calls at 0xe81b119 and 0xe81b1f9 are `call qword ptr [0xF99FFA0]`. The cell at
// 0xF99FFA0 holds sub_eea6040 (docs/data/native_boundary.tsv: vendor thunk), whose
// single instruction is `jmp rax`; rax is preloaded from a vtable slot just before
// each call (0xe81b110 / 0xe81b1f0). So each is a guarded virtual call; expressing
// it as the resolved vtable-slot invocation is exactly what the jmp-rax chain does.
// UNRESOLVED CALL = none: both indirect calls resolve to a vtable slot of a game
// object, and the only direct call (sub_e951550) is a crt boundary.

} // namespace

extern "C" void sub_e81b0f0(void* a0) {
    // 0xe81b0f0..0xe81b105: push rsi; sub rsp,0x8B0; mov rsi,rcx; /GS cookie:
    //   rax = [0x1230A0C0] ^ rsp; mov [rsp+0x8A8],rax.
    std::uintptr_t cookieSlot = 0;
    const std::uintptr_t cookieStored =
        *reinterpret_cast<std::uintptr_t*>(kGblCookie) ^ reinterpret_cast<std::uintptr_t>(&cookieSlot);

    char* const self = static_cast<char*>(a0);

    // 0xe81b10d..0xe81b119: this->vtable[0x1E8](this, 0).
    {
        void** const vtbl = *reinterpret_cast<void***>(self);              // 0xe81b10d mov rax,[rcx]
        void* const target = vtbl[kVslotBegin / 8];                        // 0xe81b110 mov rax,[rax+0x1E8]
        reinterpret_cast<void (*)(void*, std::uint32_t)>(target)(a0, 0u);  // 0xe81b117 xor edx,edx ; 0xe81b119 call qword ptr [0xF99FFA0]
    }

    // 0xe81b11f..0xe81b129: if (this->pendingCount == 0) skip the whole body.
    const std::uint64_t count = *reinterpret_cast<std::uint64_t*>(self + kPendingCount); // 0xe81b11f mov rax,[rsi+0x3C55288]
    if (count != 0) {
        // 0xe81b12f shl rax,3 : remaining = count*8, decremented by 8 each turn.
        std::uint64_t remaining = count << 3;

        // 0xe81b17f mov [rsp+r9*8+0x20],r8 : stack array of collected next-pointers,
        // indexed by the loop counter. Ring capacity bounds the live element count.
        void* nextPtrs[kRingCapacity];

        std::uint64_t idx = 0; // rdx: loop counter
        for (;;) { // loc_e81b18d
            // 0xe81b18d mov r8,[rsi+rdx*8+0x3C54A08]
            void* const element = *reinterpret_cast<void**>(self + kSrcArray + idx * 8);
            // 0xe81b195 mov r10,[rsi+0x3C55B18]
            const std::uint64_t head = *reinterpret_cast<std::uint64_t*>(self + kRingHead);
            std::uint64_t slot;
            if (head == kRingCapacity) { // 0xe81b19c cmp r10,0x110 ; 0xe81b1a3 je 0xE81B150
                // 0xe81b150 movups [rcx],xmm0 : zero both tail (0x3C55B10) and head (0x3C55B18).
                *reinterpret_cast<std::uint64_t*>(self + kRingTail) = 0;
                *reinterpret_cast<std::uint64_t*>(self + kRingHead) = 0;
                slot = 0; // 0xe81b153 xor r9d,r9d
            } else {
                // 0xe81b1a5 inc r10 ; 0xe81b1a8 cmp r10,0x110 ; 0xe81b1af/0xe81b1b5 cmovne:
                //   newhead = (head+1 == 0x110) ? 0 : head+1.
                const std::uint64_t h = head + 1;
                const std::uint64_t newhead = (h == kRingCapacity) ? 0u : h;
                *reinterpret_cast<std::uint64_t*>(self + kRingHead) = newhead; // 0xe81b1b9 mov [rsi+0x3C55B18],r9
                slot = newhead;
                // 0xe81b1c0 cmp r9,[rsi+0x3C55B10] ; 0xe81b1c7 jne 0xE81B156
                if (newhead == *reinterpret_cast<std::uint64_t*>(self + kRingTail)) {
                    // 0xe81b1c9 lea r10,[r9+1] ; 0xe81b1cd cmp r10,0x110 ; 0xe81b1d4/0xe81b1da cmovne:
                    //   tail = (newhead+1 == 0x110) ? 0 : newhead+1.
                    const std::uint64_t t = newhead + 1;
                    *reinterpret_cast<std::uint64_t*>(self + kRingTail) =
                        (t == kRingCapacity) ? 0u : t; // 0xe81b1de mov [rcx],r11
                }
                // 0xe81b1e1 jmp 0xE81B156
            }

            // 0xe81b156 mov [rsi+r9*8+0x3C55290],r8
            *reinterpret_cast<void**>(self + kDstArray + slot * 8) = element;

            char* const elem = static_cast<char*>(element);
            // 0xe81b15e mov r9,[rsi+0x3C563B0] ; 0xe81b165 mov r9,[r9+0x28]
            void* const valueObj = *reinterpret_cast<void**>(self + kValueObj);
            void* const stamped = *reinterpret_cast<void**>(
                reinterpret_cast<char*>(valueObj) + kValueObjField);
            // 0xe81b169 mov [r8+0x2CBD0],r9
            *reinterpret_cast<void**>(elem + kElemStateWord) = stamped;
            // 0xe81b170 mov byte ptr [r8+0x2CBD8],1
            *reinterpret_cast<std::uint8_t*>(elem + kElemReadyFlag) = 1;
            // 0xe81b178 mov r8,[r8+0x30]
            void* const next = *reinterpret_cast<void**>(elem + kElemNext);
            // 0xe81b17c mov r9d,edx ; 0xe81b17f mov [rsp+r9*8+0x20],r8
            nextPtrs[idx] = next;
            // 0xe81b184 inc rdx ; 0xe81b187 add rax,0xFFFFFFFFFFFFFFF8 ; 0xe81b18b je 0xE81B1E6
            ++i;
            remaining -= 8;
            if (remaining == 0) break;
        }

        // 0xe81b1e6..0xe81b1f9: flushObj = this->[0xCC9268];
        //   flushObj->vtable[0x50](flushObj, i, &nextPtrs).
        void* const flushObj = *reinterpret_cast<void**>(self + kFlushObj); // 0xe81b1e6 mov rcx,[rsi+0xCC9268]
        void** const vtbl2 = *reinterpret_cast<void***>(flushObj);          // 0xe81b1ed mov rax,[rcx]
        void* const target2 = vtbl2[kVslotFlush / 8];                       // 0xe81b1f0 mov rax,[rax+0x50]
        reinterpret_cast<void (*)(void*, std::uint64_t, void**)>(target2)(   // 0xe81b1f4 lea r8,[rsp+0x20] ; 0xe81b1f9 call qword ptr [0xF99FFA0]
            flushObj, idx, nextPtrs);
        // 0xe81b1ff mov qword ptr [rsi+0x3C55288],0
        *reinterpret_cast<std::uint64_t*>(self + kPendingCount) = 0;
    }

    // 0xe81b20a..0xe81b229: /GS epilogue. rax = cookieStored ^ frame;
    //   cmp with [0x1230A0C0]; jne -> failure.
    if (*reinterpret_cast<std::uintptr_t*>(kGblCookie) !=
        (cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot))) {
        // 0xe81b22a..0xe81b23a: cookie mismatch (cold path, never taken unless the
        //   stack frame was corrupted, exactly as the original /GS check).
        sub_e951550(cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot)); // 0xe81b235 call 0xE951550
        __assume(false); // 0xe81b23a int3 (unreachable)
    }
    // 0xe81b221 add rsp,0x8B0 ; 0xe81b228 pop rsi ; 0xe81b229 ret
}

// Verbatim disassembly of [0xe81b0f0, 0xe81b23b) (rdis dis output; two spaces after
// each address, trailing "; ..." annotations omitted):
#if 0
0xe81b0f0  push rsi
0xe81b0f1  sub rsp,0x8B0
0xe81b0f8  mov rsi,rcx
0xe81b0fb  mov rax,[0x1230A0C0]
0xe81b102  xor rax,rsp
0xe81b105  mov [rsp+0x8A8],rax
0xe81b10d  mov rax,[rcx]
0xe81b110  mov rax,[rax+0x1E8]
0xe81b117  xor edx,edx
0xe81b119  call qword ptr [0xF99FFA0]
0xe81b11f  mov rax,[rsi+0x3C55288]
0xe81b126  test rax,rax
0xe81b129  je 0xE81B20A
0xe81b12f  shl rax,3
0xe81b133  lea rcx,[rsi+0x3C55B10]
0xe81b13a  xor edx,edx
0xe81b13c  xorps xmm0,xmm0
0xe81b13f  jmp short 0xE81B18D
0xe81b141  nop [rax+rax]
0xe81b150  movups [rcx],xmm0
0xe81b153  xor r9d,r9d
0xe81b156  mov [rsi+r9*8+0x3C55290],r8
0xe81b15e  mov r9,[rsi+0x3C563B0]
0xe81b165  mov r9,[r9+0x28]
0xe81b169  mov [r8+0x2CBD0],r9
0xe81b170  mov byte ptr [r8+0x2CBD8],1
0xe81b178  mov r8,[r8+0x30]
0xe81b17c  mov r9d,edx
0xe81b17f  mov [rsp+r9*8+0x20],r8
0xe81b184  inc rdx
0xe81b187  add rax,0xFFFFFFFFFFFFFFF8
0xe81b18b  je short 0xE81B1E6
0xe81b18d  mov r8,[rsi+rdx*8+0x3C54A08]
0xe81b195  mov r10,[rsi+0x3C55B18]
0xe81b19c  cmp r10,0x110
0xe81b1a3  je short 0xE81B150
0xe81b1a5  inc r10
0xe81b1a8  cmp r10,0x110
0xe81b1af  mov r9d,0
0xe81b1b5  cmovne r9,r10
0xe81b1b9  mov [rsi+0x3C55B18],r9
0xe81b1c0  cmp r9,[rsi+0x3C55B10]
0xe81b1c7  jne short 0xE81B156
0xe81b1c9  lea r10,[r9+1]
0xe81b1cd  cmp r10,0x110
0xe81b1d4  mov r11d,0
0xe81b1da  cmovne r11,r10
0xe81b1de  mov [rcx],r11
0xe81b1e1  jmp 0xE81B156
0xe81b1e6  mov rcx,[rsi+0xCC9268]
0xe81b1ed  mov rax,[rcx]
0xe81b1f0  mov rax,[rax+0x50]
0xe81b1f4  lea r8,[rsp+0x20]
0xe81b1f9  call qword ptr [0xF99FFA0]
0xe81b1ff  mov qword ptr [rsi+0x3C55288],0
0xe81b20a  mov rax,[rsp+0x8A8]
0xe81b212  xor rax,rsp
0xe81b215  mov rcx,[0x1230A0C0]
0xe81b21c  cmp rcx,rax
0xe81b21f  jne short 0xE81B22A
0xe81b221  add rsp,0x8B0
0xe81b228  pop rsi
0xe81b229  ret
0xe81b22a  mov rcx,[rsp+0x8A8]
0xe81b232  xor rcx,rsp
0xe81b235  call 0xE951550
0xe81b23a  int3
#endif

LIFT_FN(e81b0f0, "sub_e81b0f0", 0xE81B0F0, sub_e81b0f0, nullptr);

} // namespace native