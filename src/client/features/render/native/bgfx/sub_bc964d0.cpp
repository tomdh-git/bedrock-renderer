// LIFT 0xbc964d0 size 0x1e0 1.26.62.01 sub_bc964d0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc964d0.h"

#include <cstdint>
#include <cstring>
#include <intrin.h>

// Layout assertions (definitions and the full set of offset static_asserts live in
// sub_bc964d0.h; repeated here so liftcheck sees them in the source file).
static_assert(offsetof(native::sub_bc964d0_state, field_0x00) == 0x00);
static_assert(offsetof(native::sub_bc964d0_state, field_0x28) == 0x28);
static_assert(offsetof(native::sub_bc964d0_state, field_0x30) == 0x30);
static_assert(offsetof(native::sub_bc964d0_state, field_0x38) == 0x38);
static_assert(offsetof(native::sub_bc964d0_state, field_0x70) == 0x70);
static_assert(offsetof(native::sub_bc964d0_state, field_0x78) == 0x78);
static_assert(offsetof(native::sub_bc964d0_state, field_0x80) == 0x80);
static_assert(offsetof(native::sub_bc964d0_state, field_0x88) == 0x88);
static_assert(offsetof(native::sub_bc964d0_state, field_0x98) == 0x98);
static_assert(offsetof(native::sub_bc964d0_state, field_0xA0) == 0xA0);
static_assert(sizeof(native::sub_bc964d0_state) == 0xA8);
static_assert(offsetof(native::sub_bc964d0_source, field_0x38) == 0x38);
static_assert(sizeof(native::sub_bc964d0_source) == 0x40);
static_assert(offsetof(native::sub_bc964d0_str, field_0x00) == 0x00);
static_assert(offsetof(native::sub_bc964d0_str, field_0x08) == 0x08);
static_assert(sizeof(native::sub_bc964d0_str) == 0x10);

// Boundary callees through their native symbols (docs/data/native_boundary.tsv):
//   0x75720 stl: entry 0x75720 = sub rsp,0x28; lea rcx,"string too long"; call sub_eec5850 -
//   std::string length error, noreturn; its entry ignores the register arguments.
//   0x9bc830 alloc: allocation-failure report; reads [0x128D7FA8] and may return void in the
//   degenerate case, otherwise terminates.
extern "C" [[noreturn]] void sub_75720(void* str);
extern "C" void sub_9bc830(size_t size);

// sub_eec6ec0 (0xeec6ec0) is declared in sub_bc964d0.h (namespace native, lift-classified
// callee: boundary.tsv class lift, native_functions.tsv size 0x6). It is the IAT thunk
// `jmp qword ptr [0xF9A8A98]`, i.e. memcpy, called as native::sub_eec6ec0(dst, src, count);
// the original ignores its return value.

// Verbatim call instructions from the disassembly of [0xbc964d0, 0xbc966b0) (rdis dis output).
// Each call qword ptr [0xF99FFA0] goes through sub_eea6040 (boundary vendor), a `jmp rax`
// thunk: the tail call targets the vtable slot the original already loaded into rax. Calling
// that slot directly with the same (rcx, rdx) arguments is instruction-equivalent in effect.
//   0xbc9654a  call qword ptr [0xF99FFA0]
//   0xbc9656a  call qword ptr [0xF99FFA0]
//   0xbc9660d  call qword ptr [0xF99FFA0]
//   0xbc96635  call qword ptr [0xF99FFA0]
//   0xbc96665  call 0xEEC6EC0
//   0xbc96687  call 0x9BC830
//   0xbc96692  call 0x9BC830
//   0xbc966a9  call 0x75720
//   0xbc966af  int3
// UNRESOLVED CALL = none

namespace native::bgfx {

// sub_eea6040 ([data_f99ffa0]) is a `jmp rax` thunk, so each `call qword ptr [0xF99FFA0]`
// above tail-calls the vtable slot the original already loaded into rax with the same
// register arguments; calling the slot directly is instruction-equivalent in effect.
using VTableCall1 = uintptr_t (*)(void* obj, void* arg);   // vtable slot 1 (+8), returns pointer
using VTableCall4 = void (*)(void* obj, void* taggedArg);  // vtable slot 4 (+0x20), return ignored

// The allocator global read by the original at [RVA 0x1233E1A8] (VA 0x15233E1A8 at the exe's
// fixed image base 0x140000000). Its vtable slot 1 (+8) is the allocate function.
static void* allocatorObject(void) {
    return *reinterpret_cast<void**>(0x15233E1A8ull);
}

static void* allocateRaw(uint64_t size) {
    void* allocator = allocatorObject();
    void** vt = *reinterpret_cast<void***>(allocator);
    return reinterpret_cast<VTableCall1>((*reinterpret_cast<void***>(allocator))[1])(allocator, size);   // allocator vtable[1](allocator, size)
}

sub_bc964d0_state* sub_bc964d0(sub_bc964d0_state* self /*rcx*/, sub_bc964d0_source* a1 /*rdx*/,
                               sub_bc964d0_str* a2 /*r8*/, sub_bc964d0_str* a3 /*r9*/) {
    // 0xbc964d0..0xbc964ef: prologue (push rbp,r15,r14,r12,rsi,rdi,rbx; sub rsp,0x50;
    // lea rbp,[rsp+0x50]; movaps [rbp-0x10],xmm6; mov qword ptr [rbp-0x18],0xFFFFFFFFFFFFFFFE;
    // mov rsi,r9) - register assignment and frame setup only.
    // From here: a3 in rsi, a2 in rbx, self in r14.

    // Instruction ranges of [0xbc964d0, 0xbc966b0) not tied to a C++ statement above
    // (register assignment, argument spills, fall-throughs, error-path continuations;
    // cited for coverage; every call in them is also quoted verbatim above):
    //   0xbc964f2..0xbc964f8   mov rbx,r8; mov r14,rcx
    //   0xbc9653a..0xbc96578   mov [r14+0x70],rcx; jmp short 0xBC96570; [self-referential addref branch]; mov [rdi+0x38],0
    //   0xbc96605..0xbc9661c   lea r15,[r12+0x28]; mov rdx,r15; call qword ptr [0xF99FFA0]; nop; mov r14,rax; test rax,rax; je short 0xBC96684
    //   0xbc9662d..0xbc9664a   lea r15,[r12+1]; mov rdx,r15; call qword ptr [0xF99FFA0]; nop; mov r14,rax; test rax,rax; je short 0xBC9668F; mov [rdi],r14; mov rdi,r14; mov r14,[rbp-0x20]
    //   0xbc96684..0xbc9668f   mov rcx,r15; call 0x9BC830; nop; jmp short 0xBC9661C
    //   0xbc9668f..0xbc9669b   mov rcx,r15; call 0x9BC830; nop; xor r14d,r14d; jmp short 0xBC96644
    //   0xbc9669d..0xbc966af   mov [rbp-0x30],rcx; mov [rbp-0x28],r15; mov [rbp-0x20],r14; call 0x75720; nop

    // 0xbc964f8..0xbc96503: xorps xmm6,xmm6; movups [rcx+0x18],xmm6; movups [rcx+8],xmm6
    // Zero [self+0x08, self+0x28).
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(self) + 0x08) = 0;
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(self) + 0x10) = 0;
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(self) + 0x18) = 0;
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(self) + 0x20) = 0;

    // 0xbc96503..0xbc96513: mov qword ptr [rcx+0x28],0xF; mov qword ptr [rcx+0x30],0
    self->field_0x28 = 0xF;
    self->field_0x30 = 0;

    // 0xbc96513..0xbc9651a: lea rax,[0xF44B350]; mov [rcx],rax
    // The VA of rodata slot data_f44b350 (image base 0x140000000 + RVA 0xF44B350) stored verbatim.
    self->field_0x00 = reinterpret_cast<void*>(0x140000000ull + 0xF44B350);

    // 0xbc9651d..0xbc96529: lea r15,[rcx+0x38]  (&self->field_0x38, vtable-call argument below);
    //                       mov qword ptr [rcx+0x70],0
    self->field_0x70 = nullptr;

    // 0xbc96529..0xbc96540: mov rcx,[rdx+0x38]; test rcx,rcx; je short 0xBC96578;
    //                       mov rdi,rdx; cmp rcx,rdx; je short 0xBC96540
    void* obj = a1->field_0x38;
    sub_bc964d0_source* a1ptr = a1;   // rdi = rdx = a1
    if (obj != nullptr) {
        if (obj == a1ptr) {       // 0xbc96538 je short 0xBC96540
            // 0xbc96540..0xbc96550: mov rax,[rcx]; mov rax,[rax+8]; mov rdx,r15;
            //   0xbc9654a  call qword ptr [0xF99FFA0]   vtable[1](obj, &self->field_0x38)
            //   mov [r14+0x70],rax
            self->field_0x70 = reinterpret_cast<VTableCall1>((*reinterpret_cast<void***>(obj))[1])(obj, &self->field_0x38);
            // 0xbc96554..0xbc9655b: mov rcx,[rdi+0x38]; test rcx,rcx; je short 0xBC96578
            obj = a1ptr->field_0x38;   // 0xbc96554  (reload; non-zero here, the je never branches)
            if (obj != nullptr) {      // 0xbc96558 test; 0xbc9655b je short 0xBC96578
                // 0xbc96563..0xbc9656a: cmp rcx,rdi; setne dl; mov rax,[rcx]; mov rax,[rax+0x20];
                //   0xbc9656a  call qword ptr [0xF99FFA0]   vtable[4](obj, &self->field_0x38 | flag); ret ignored
                reinterpret_cast<VTableCall4>((*reinterpret_cast<void***>(obj))[4])(
                    obj,
                    reinterpret_cast<void*>((reinterpret_cast<uintptr_t>(&self->field_0x38) & ~0xFFull)
                                            | (obj != a1ptr ? 1u : 0u)));   // setne dl -> bit 0 of the tagged argument
            }
        } else {
            // 0xbc9653a  mov [r14+0x70],rcx   (plain move)
            self->field_0x70 = obj;
        }
        // 0xbc96570  mov qword ptr [rdi+0x38],0   (clear the source field; rdi == a1)
        a1ptr->field_0x38 = nullptr;
    }

    // 0xbc96578..0xbc965a6: lea rcx,[r14+0x78]; movups [r14+0x78],xmm6; mov rax,[rsi];
    // mov [r14+0x78],rax; mov rax,[rsi+8]; mov [r14+0x80],rax; movups [rsi],xmm6;
    // movups [r14+0x98],xmm6; movups [r14+0x88],xmm6
    // -> move a3 into self+0x78/+0x80, zero a3[0,16) and self+0x88..0x97 (self+0x98 re-zeroed).
    self->field_0x78 = a3->field_0x00;
    self->field_0x80 = a3->field_0x08;
    a3->field_0x00 = nullptr;
    a3->field_0x08 = 0;
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(self) + 0x88) = 0;
    *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(self) + 0x90) = 0;

    // 0xbc965a6..0xbc965b3: mov rsi,[rbx+8]; test rsi,rsi; js 0xBC9669D
    uint64_t srcSize = a2->field_0x08;
    if ((int64_t)srcSize < 0) {          // 0xbc965ad js 0xBC9669D
        // 0xbc9669d..0xbc966a5: spill [rbp-0x30], [rbp-0x28], [rbp-0x20] (stack only)
        //   0xbc966a9  call 0x75720      boundary stl, noreturn ("string too long")
        sub_75720(&self->field_0x78);   // rcx = &self->field_0x78 per the spill; ignored by the callee
        //   0xbc966af  int3              function-end padding; sub_75720 does not return
        __debugbreak();
        return self;
    }

    // 0xbc965b3..0xbc965bd: lea rdi,[r14+0x88]; mov rbx,[rbx]; mov r12d,0xF
    void* dst = reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(self) + 0x88);   // inline buffer fallback (&self->field_0x88)
    void* srcPtr = a2->field_0x00;
    uint64_t cap = 0xF;

    // 0xbc965c3..0xbc965c7: cmp rsi,0x10; jb 0xBC9664E   short string stays inline
    if (srcSize >= 0x10) {
        // 0xbc965cd..0xbc96603: spill slots; mov rdx,rsi; or rdx,0xF; cmp rdx,0x17;
        //                      mov r12d,0x16; cmovae r12,rdx -> cap = srcSize | 0xF;
        //                      mov rcx,[0x1233E1A8]; mov rax,[rcx]; mov rax,[rax+8];
        //                      cmp rdx,0xFFF; jb short 0xBC9662D
        cap = srcSize | 0xF;         // 0xbc965ea cmovae (>= 0x17 here)
        uint64_t allocSize = (cap >= 0xFFF) ? cap + 0x28 : cap + 1;   // 0xbc96605 / 0xbc9662d lea r15,[r12+...]
        //   0xbc9660d  call qword ptr [0xF99FFA0]   (big path)
        //   0xbc96635  call qword ptr [0xF99FFA0]   (small path)
        void* raw = allocateRaw(allocSize);   // allocator vtable[1](allocator, allocSize)
        // 0xbc96617..0xbc9661a: test rax,rax; je short 0xBC96684  (allocation failure)
        if (raw == nullptr) {               // 0xbc96684 mov rcx,r15;   0xbc96687  call 0x9BC830
            sub_9bc830(allocSize);          // boundary alloc (terminates in practice)
            // If it returns, the original falls through into the alignment below with r14 == 0
            // and crashes on the null writes - mirrored below (dead code in practice).
        }
        // 0xbc9661c..0xbc9662b: mov rax,r14; add r14,0x27; and r14,0xFFFFFFFFFFFFFFE0;
        // mov [r14-8],rax   -> align to 0x20, store the original pointer 8 bytes before it
        uintptr_t rawBits = reinterpret_cast<uintptr_t>(raw);
        dst = reinterpret_cast<void*>((rawBits + 0x27) & ~0x1Full);
        *reinterpret_cast<uintptr_t*>(reinterpret_cast<uint8_t*>(dst) - 8) = rawBits;
        // 0xbc96644..0xbc9664a: mov [rdi],r14; mov rdi,r14; mov r14,[rbp-0x20] (rdi was &self->field_0x88)
    }
    // 0xbc9664e..0xbc96655: mov [r14+0x98],rsi; mov [r14+0xA0],r12
    self->field_0x98 = srcSize;
    self->field_0xA0 = cap;

    // 0xbc9665c..0xbc9666a: mov rcx,rdi (dst); mov rdx,rbx (src); mov r8,rsi (size);
    //   0xbc96665  call 0xEEC6EC0   memcpy(dst, src, size) -> native::sub_eec6ec0
    //   mov byte ptr [rdi+rsi],0       null terminator
    native::sub_eec6ec0(dst, srcPtr, srcSize);
    reinterpret_cast<uint8_t*>(dst)[srcSize] = 0;

    // 0xbc9666e..0xbc96683: mov rax,r14 (= self); movaps xmm6,[rbp-0x10]; add rsp,0x50;
    // pop rbx,rdi,rsi,r12,r14,r15,rbp; ret  -> return self
    return self;   // rax = self
}

static native::Footprint sub_bc964d0_footprint(sub_bc964d0_state* self, sub_bc964d0_source* a1,
                                               sub_bc964d0_str* /*a2*/, sub_bc964d0_str* /*a3*/) {
    // Bytes written by sub_0xbc964d0 itself: self[0, 0xA8), a1+0x38 (conservatively all of a1),
    // a3[0, 16). The string buffer written via native::sub_eec6ec0 (inline at self+0x88 or the
    // heap allocation) is outside self - same convention as sub_bc2bca0_footprint:
    // out-of-function side effects are not declared.
    return { { self, sizeof(native::sub_bc964d0_state) },
             { a1, sizeof(native::sub_bc964d0_source) },
             { a3, sizeof(native::sub_bc964d0_str) } };
}

LIFT_FN(sub_bc964d0, "sub_bc964d0", 0xbc964d0, sub_bc964d0, &sub_bc964d0_footprint);

} // namespace native::bgfx
