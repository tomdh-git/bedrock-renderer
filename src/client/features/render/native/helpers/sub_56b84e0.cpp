// LIFT 0x56b84e0 size 0x116 1.26.62.01 sub_56b84e0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_56b84e0.h"

#include <cstdint>
#include <cstddef>

namespace native::helpers {

// Layout assertions (offsets/widths proven from the instruction operands).
static_assert(offsetof(sub_56b84e0_rcx, buffer) == 0x0, "sub_56b84e0 rcx+0x0 field");
static_assert(offsetof(sub_56b84e0_rcx, bufferEnd) == 0x8, "sub_56b84e0 rcx+0x8 field");
static_assert(offsetof(sub_56b84e0_rcx, frameEnd) == 0x10, "sub_56b84e0 rcx+0x10 field");
static_assert(sizeof(sub_56b84e0_rcx) >= 0x18, "sub_56b84e0 rcx sizeof lower bound");

static_assert(offsetof(sub_56b84e0_r8, current) == 0x0, "sub_56b84e0 r8+0x0 field");
static_assert(sizeof(sub_56b84e0_r8) >= 0x8, "sub_56b84e0 r8 sizeof lower bound");

static_assert(offsetof(sub_56b84e0_r9, end) == 0x0, "sub_56b84e0 r9+0x0 field");
static_assert(sizeof(sub_56b84e0_r9) >= 0x8, "sub_56b84e0 r9 sizeof lower bound");

static_assert(offsetof(sub_56b84e0_rax, vtable) == 0x0, "sub_56b84e0 rax+0x0 field");
static_assert(offsetof(sub_56b84e0_rax, allocFunc) == 0x8, "sub_56b84e0 rax+0x8 field");
static_assert(sizeof(sub_56b84e0_rax) >= 0x10, "sub_56b84e0 rax sizeof lower bound");

LIFT_FN(sub_56b84e0, "sub_56b84e0", 0x56b84e0, sub_56b84e0, nullptr);

// Verbatim call instructions from the disassembly of [0x56b84e0, 0x56b85f6) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
// The global heap pointer is read from [0x1233E1A8]; the allocator is vtable slot 1 of that
// heap object (loaded into rax before each call through the [0xF99FFA0] = sub_eea6040 thunk,
// which tail-jumps to rax).
#if 0
0x56b852f  mov rcx,[0x1233E1A8]
0x56b8536  mov rax,[rcx]
0x56b8539  mov rax,[rax+8]
0x56b8540  call qword ptr [0xF99FFA0]
0x56b8560  mov rcx,[0x1233E1A8]
0x56b8567  mov rax,[rcx]
0x56b856a  mov rax,[rax+8]
0x56b8571  call qword ptr [0xF99FFA0]
0x56b85a6  call 0x8DA480
0x56b85d6  call 0x9BC830
0x56b85e6  call 0x9BC830
0x56b85f0  call 0x75B60
#endif

// Ranges: every instruction of [0x56b84e0, 0x56b85f6) is covered by a block range comment
// and/or a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

namespace {

// Heap object pointer stored at the global [0x1233E1A8].
inline void* heapObject() {
    return *reinterpret_cast<void**>(0x1233E1A8);
}

// Allocator = heap vtable slot 1, invoked as allocFunc(heap, size). This performs the same
// reads ([0x1233E1A8], [heap], [heap+8]) and the same call as the [0xF99FFA0] thunk sequence.
inline void* heapAlloc(uint64_t size) {
    void* heap = heapObject();                                    // mov rcx,[0x1233E1A8]
    const sub_56b84e0_rax* h = reinterpret_cast<const sub_56b84e0_rax*>(heap);
    void* vtable = h->vtable;                                     // mov rax,[rcx]
    void* allocFunc = h->allocFunc;                               // mov rax,[rax+8]
    using alloc_fn = void*(*)(void*, uint64_t);
    return reinterpret_cast<alloc_fn>(allocFunc)(heap, size);     // call [0xF99FFA0] -> sub_eea6040 (jmp rax)
}

} // namespace

uintptr_t sub_56b84e0(void* self, uint64_t count,
                      sub_56b84e0_r8* srcCur, sub_56b84e0_r9* srcEnd) {
    sub_56b84e0_rcx* fb = reinterpret_cast<sub_56b84e0_rcx*>(self);
    void* buf = nullptr;
    void* start = nullptr;
    uintptr_t rax = 0;
    uint64_t total = 0;
    void* dest = nullptr;
    void* src = nullptr;
    const void* srcEndPtr = nullptr;
    uintptr_t end = 0;

    // 0x56b84e0..0x56b8502: basic block 0
    // 0x56b84e0  push rbp
    // 0x56b84e1  push r15
    // 0x56b84e3  push r14
    // 0x56b84e5  push rsi
    // 0x56b84e6  push rdi
    // 0x56b84e7  push rbx
    // 0x56b84e8  sub rsp,0x38
    // 0x56b84ec  lea rbp,[rsp+0x30]
    // 0x56b84f1  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
    // 0x56b84f9  test rdx,rdx
    // 0x56b84fc  je 0x56B85C3
    // -> if count == 0 goto L_0x56b85c3
    // -> if count != 0 goto L_0x56b8502
    if (count == 0) goto L_0x56b85c3;
    L_0x56b84e0:;

    // 0x56b8502..0x56b8515: basic block 1
    // 0x56b8502  mov rax,0x70381C0E070382
    // 0x56b850c  cmp rdx,rax
    // 0x56b850f  jae 0x56B85F0
    // -> if count >=u 0x70381C0E070382 goto L_0x56b85f0
    // -> if count <u 0x70381C0E070382 goto L_0x56b8515
    if (count >= 0x70381C0E070382ULL) goto L_0x56b85f0;
    L_0x56b8502:;

    // 0x56b8515..0x56b852b: basic block 2
    // 0x56b8515  mov rbx,r9          ; end cell
    // 0x56b8518  mov rdi,r8          ; cursor cell
    // 0x56b851b  mov rsi,rcx         ; self
    // 0x56b851e  imul r14,rdx,0x248  ; total = count * 0x248
    // 0x56b8525  cmp rdx,8
    // 0x56b8529  jb short 0x56B8560
    // -> if count <u 8 goto L_0x56b8560
    // -> if count >=u 8 goto L_0x56b852b
    total = count * 0x248ULL;
    if (count < 8) goto L_0x56b8560;
    L_0x56b8515:;

    // 0x56b852b..0x56b854f: basic block 3
    // 0x56b852b  lea r15,[r14+0x27]  ; size = total + 0x27
    // 0x56b852f  mov rcx,[0x1233E1A8]
    // 0x56b8536  mov rax,[rcx]
    // 0x56b8539  mov rax,[rax+8]
    // 0x56b853d  mov rdx,r15
    // 0x56b8540  call qword ptr [0xF99FFA0]
    // 0x56b8546  test rax,rax
    // 0x56b8549  je 0x56B85D0
    // -> if alloc result == 0 goto L_0x56b85d0
    // -> if alloc result != 0 goto L_0x56b854f
    buf = heapAlloc(total + 0x27);
    if (buf == nullptr) goto L_0x56b85d0;
    L_0x56b852b:;

    // 0x56b854f..0x56b8560: basic block 4
    // 0x56b854f  mov r15,rax         ; r15 = buf
    // 0x56b8552  add r15,0x27
    // 0x56b8556  and r15,0xFFFFFFFFFFFFFFE0   ; align_down(buf + 0x27, 32)
    // 0x56b855a  mov [r15-8],rax     ; [start - 8] = original buf
    // 0x56b855e  jmp short 0x56B857F
    rax = reinterpret_cast<uintptr_t>(buf);
    start = reinterpret_cast<void*>((rax + 0x27) & ~0x1FULL);
    *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(start) - 8) = buf;
    goto L_0x56b857f;
    L_0x56b854f:;

    // 0x56b8560..0x56b857f: basic block 5
    // 0x56b8560  mov rcx,[0x1233E1A8]
    // 0x56b8567  mov rax,[rcx]
    // 0x56b856a  mov rax,[rax+8]
    // 0x56b856e  mov rdx,r14         ; size = total
    // 0x56b8571  call qword ptr [0xF99FFA0]
    // 0x56b8577  mov r15,rax         ; r15 = buf
    // 0x56b857a  test rax,rax
    // 0x56b857d  je short 0x56B85E3
    // -> if alloc result == 0 goto L_0x56b85e3
    // -> if alloc result != 0 goto L_0x56b857f
    buf = heapAlloc(total);
    if (buf == nullptr) goto L_0x56b85e3;
    rax = reinterpret_cast<uintptr_t>(buf);
    start = buf;
    goto L_0x56b857f;
    L_0x56b8560:;

    // 0x56b857f..0x56b859c: basic block 6
    // 0x56b857f  mov [rsi],r15              ; fb->buffer = start
    // 0x56b8582  mov [rsi+8],r15            ; fb->bufferEnd = start
    // 0x56b8586  add r14,r15                ; r14 = total + start = end
    // 0x56b8589  mov [rsi+0x10],r14         ; fb->frameEnd = end
    // 0x56b858d  mov [rbp-8],rsi            ; stack slot = self
    // 0x56b8591  mov rbx,[rbx]              ; rbx = srcEnd->end
    // 0x56b8594  mov rdi,[rdi]              ; rdi = srcCur->current
    // 0x56b8597  cmp rdi,rbx
    // 0x56b859a  je short 0x56B85BF
    // -> if srcCur->current == srcEnd->end goto L_0x56b85bf
    // -> if srcCur->current != srcEnd->end goto L_0x56b859c
    fb->buffer = start;
    fb->bufferEnd = start;
    end = reinterpret_cast<uintptr_t>(start) + total;
    fb->frameEnd = reinterpret_cast<void*>(end);
    dest = start;
    src = srcCur->current;
    srcEndPtr = srcEnd->end;
    if (src == srcEndPtr) goto L_0x56b85bf;
    L_0x56b857f:;

    // 0x56b859c..0x56b85a0: basic block 7 (nop [rax], fallthrough)
    // 0x56b859c  nop [rax]
    // -> fallthrough goto L_0x56b85a0
    L_0x56b859c:;

    // 0x56b85a0..0x56b85bf: basic block 8 (copy loop)
    // 0x56b85a0  mov rcx,r15               ; dest
    // 0x56b85a3  mov rdx,rdi               ; src
    // 0x56b85a6  call 0x8DA480             ; sub_8da480(dest, src) copies 0x248 bytes
    // 0x56b85ab  nop
    // 0x56b85ac  add r15,0x248             ; dest += 0x248
    // 0x56b85b3  add rdi,0x248             ; src  += 0x248
    // 0x56b85ba  cmp rdi,rbx
    // 0x56b85bd  jne short 0x56B85A0
    // -> if src != srcEnd goto L_0x56b85a0
    // -> if src == srcEnd goto L_0x56b85bf
    L_0x56b85a0:;
    for (;;) {
        sub_8da480(dest, src);
        rax = reinterpret_cast<uintptr_t>(dest);
        dest = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(dest) + 0x248);
        src = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(src) + 0x248);
        if (src == srcEndPtr) break;
    }
    goto L_0x56b85bf;

    // 0x56b85bf..0x56b85c3: basic block 9
    // 0x56b85bf  mov [rsi+8],r15            ; fb->bufferEnd = r15 (end)
    // -> fallthrough goto L_0x56b85c3
    L_0x56b85bf:;
    fb->bufferEnd = dest;

    // 0x56b85c3..0x56b85d0: basic block 10 (epilogue/ret)
    // 0x56b85c3  add rsp,0x38
    // 0x56b85c7  pop rbx
    // 0x56b85c8  pop rdi
    // 0x56b85c9  pop rsi
    // 0x56b85ca  pop r14
    // 0x56b85cc  pop r15
    // 0x56b85ce  pop rbp
    // 0x56b85cf  ret
    L_0x56b85c3:;
    return rax - 0x248;  // rax = last chunk destination (block 8 leaves rax = dest before final increment)

    // 0x56b85d0..0x56b85e3: basic block 11 (sub_9bc830 is noreturn)
    // 0x56b85d0  mov rcx,r15
    // 0x56b85d3  mov r15,rax
    // 0x56b85d6  call 0x9BC830   -> sub_9bc830
    // 0x56b85db  mov rax,r15
    // 0x56b85de  jmp 0x56B854F
    L_0x56b85d0:;
    sub_9bc830(total + 0x27);   // noreturn; noreturn block keeps rax = size value semantics

    // 0x56b85e3..0x56b85f0: basic block 12 (sub_9bc830 is noreturn)
    // 0x56b85e3  mov rcx,r14
    // 0x56b85e6  call 0x9BC830   -> sub_9bc830
    // 0x56b85eb  xor r15d,r15d
    // 0x56b85ee  jmp short 0x56B857F
    L_0x56b85e3:;
    sub_9bc830(total);          // noreturn

    // 0x56b85f0..0x56b85f6: basic block 13 (sub_75b60 is noreturn)
    // 0x56b85f0  call 0x75B60   -> sub_75b60  ("vector too long", noreturn)
    // 0x56b85f5  int3
    L_0x56b85f0:;
    sub_75b60();                // noreturn
}

} // namespace native::helpers
