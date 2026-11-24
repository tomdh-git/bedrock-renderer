// LIFT 0xbc431b0 size 0x129 1.26.62.01 sub_bc431b0
#include "client/features/render/native/bgfx/sub_bc431b0.h"

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "client/features/render/native/Lift.h"

// Verbatim call instructions from the disassembly of [0xbc431b0, 0xbc432d9).
// [0xF99FFA0] = allocator allocate (IAT thunk, resolves to sub_eea6040): compiled to std::malloc,
// the STL equivalent the original inlines (spec section 5).
// 0xEEC6EC0 = memcpy thunk: compiled to std::memcpy (spec section 5).
// 0x75720 (docs/data/native_boundary.tsv: stl) and 0x9BC830 (native_boundary.tsv: alloc)
// are boundary callees, called through native::Boundary wrappers with their native symbols.
// UNRESOLVED CALL = none.
// 0xbc43250  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
// 0xbc43274  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
// 0xbc43297  call 0xEEC6EC0
// 0xbc432c1  call 0x9BC830
// 0xbc432d3  call 0x9BC830
// 0xbc432cb  call 0x75720

namespace {

// Boundary wrappers for the two classified callees (docs/data/native_boundary.tsv).
// Addresses resolve from Sigs.json at install; both are noreturn on the paths that reach them.
native::Boundary<void, void*> sub_75720("sub_75720");          // 0x75720: invalid_parameter-like handler, reached when size < 0
native::Boundary<void, uint64_t> sub_9bc830("sub_9bc830");     // 0x9bc830: heap-failure handler, reached when allocation returns NULL; argument = alloc size

} // namespace

namespace native::bgfx {

static native::Footprint sub_bc431b0_footprint(VvFrameGraphBuilder* dst, const VvFrameGraphBuilder* /*src*/) {
    return { { { dst, 0x40ull } } }; // the function writes only within the dst object [V]
}

VvFrameGraphBuilder* sub_bc431b0(VvFrameGraphBuilder* dst, const VvFrameGraphBuilder* src) {
    const VvFrameGraphBuilder* s = src;

    // 0xbc431b0..0xbc431d8 — prologue: save callee-saved registers, home space;
    // copy src+0x00 (16B) and src+0x10 (8B) to dst; zero dst+0x18 and dst+0x28.
    dst->mField10 = s->mField10;                        // 0xbc431c3  mov rax,[rdx+0x10] / 0xbc431c7  mov [rcx+0x10],rax
    std::memcpy(dst, s, 16);                            // 0xbc431cb  movups xmm0,[rdx] / 0xbc431ce  movups [rcx],xmm0
    std::memset(&dst->mData, 0, 16);                    // 0xbc431d1  xorps xmm0,xmm0 / 0xbc431d4  movups [rcx+0x18],xmm0
    std::memset(&dst->mSize, 0, 16);                    // 0xbc431d8  movups [rcx+0x28],xmm0

    // 0xbc431dc..0xbc431ed — size = src+0x28; src data = inline &src+0x18 when src+0x30 < 0x10,
    // otherwise the heap pointer at src+0x18.
    uint64_t size = s->mSize;                           // 0xbc431dc  mov rbx,[rdx+0x28]
    void* srcData;
    if (s->mCapacity < 0x10ULL) {                       // 0xbc431e0  cmp qword ptr [rdx+0x30],0x10 / 0xbc431e5  jb short 0xBC431ED
        srcData = reinterpret_cast<void*>(reinterpret_cast<const uint8_t*>(s) + 0x18);  // 0xbc431ed  lea r14,[rdi+0x18]  (&src+0x18)
    } else {                                            // 0xbc431e7  mov r14,[rdi+0x18] / 0xbc431eb  jmp short 0xBC431F1
        srcData = s->mData;                             // 0xbc431e7  mov r14,[rdi+0x18]
    }

    // 0xbc431f1..0xbc43217 — reject a negative size; heap destination when size > 0xF,
    // otherwise SSO destination writing 16 inline bytes.
    if (static_cast<int64_t>(size) < 0) {               // 0xbc431f1  test rbx,rbx / 0xbc431f4  js 0xBC432CB
        sub_75720(dst);                                 // 0xbc432cb  call 0x75720  (noreturn)
    }
    if (size > 0xFULL) {                                // 0xbc431fa  cmp rbx,0xF / 0xbc431fe  ja short 0xBC4321C
        // 0xbc4321c..0xbc43297 — heap destination: size class, allocator call, align, cookie, copy.
        uint64_t rdx = size | 0xFULL;                   // 0xbc4321c  mov rdx,rbx / 0xbc4321f  or rdx,0xF
        uint64_t capacity = 0x16ULL;                    // 0xbc43227  mov r12d,0x16
        if (rdx >= 0x17ULL) capacity = rdx;             // 0xbc43223  cmp rdx,0x17 / 0xbc4322d  cmovae r12,rdx
        // 0xbc43231  mov rcx,[0x1233E1A8] / 0xbc43238  mov rax,[rcx] / 0xbc4323b  mov rax,[rax+8]
        //                  allocator object in rcx (vtable slot load is dead before the call)
        uint64_t allocSize;
        if (rdx < 0x1000ULL) {                          // 0xbc4323f  cmp rdx,0xFFF / 0xbc43246  jb short 0xBC4326C
            allocSize = capacity + 1ULL;                // 0xbc4326c  lea r15,[r12+1]
        } else {                                        // 0xbc43248  lea r15,[r12+0x28]
            allocSize = capacity + 0x28ULL;
        }
        void* result = std::malloc(allocSize);          // 0xbc43250  call qword ptr [0xF99FFA0]  ; [data_f99ffa0] = sub_eea6040  (rcx = allocator, rdx = allocSize)
        if (result == nullptr) {                        // 0xbc43256  test rax,rax / 0xbc43259  je short 0xBC432BB
            sub_9bc830(allocSize);                      // 0xbc432bb  mov rcx,r15 / 0xbc432c1  call 0x9BC830  (noreturn; arg = alloc size)
        }
        uint8_t* aligned = (reinterpret_cast<uint8_t*>(result) + 0x27ULL) & ~0x1FULL;  // 0xbc4325b  mov rcx,rax / 0xbc4325e  add rcx,0x27 / 0xbc43262  and rcx,0xFFFFFFFFFFFFFFE0
        *reinterpret_cast<void**>(aligned - 8) = result;// 0xbc43266  mov [rcx-8],rax
        dst->mData = aligned;                           // 0xbc43282  mov [rsi+0x18],rcx
        dst->mSize = size;                              // 0xbc43286  mov [rsi+0x28],rbx
        dst->mCapacity = capacity;                      // 0xbc4328a  mov [rsi+0x30],r12
        size++;                                         // 0xbc4328e  inc rbx
        std::memcpy(dst->mData, srcData, size);         // 0xbc43291  mov rdx,r14 / 0xbc43294  mov r8,rbx / 0xbc43297  call 0xEEC6EC0  (count = size + 1)
    } else {
        // 0xbc43200..0xbc43217 — SSO destination: mSize = size, mCapacity = 0xF, copy 16 inline bytes.
        dst->mSize = size;                              // 0xbc43204  mov [rsi+0x28],rbx
        dst->mCapacity = 0xFULL;                        // 0xbc43208  mov qword ptr [rsi+0x30],0xF
        std::memcpy(dst->mData, srcData, 16);           // 0xbc43200  lea rax,[rsi+0x18] / 0xbc43210  movups xmm0,[r14] / 0xbc43214  movups [rax],xmm0
    }

    // 0xbc4329c..0xbc432ba — tail: metadata fields from src, return dst.
    dst->mField3C = s->mField3C;                        // 0xbc4329c  movzx eax,word ptr [rdi+0x3C] / 0xbc432a0  mov [rsi+0x3C],ax
    dst->mField38 = s->mField38;                        // 0xbc432a4  mov eax,[rdi+0x38] / 0xbc432a7  mov [rsi+0x38],eax
    return dst;                                         // 0xbc432aa  mov rax,rsi / ... / 0xbc432ba  ret
}

static_assert(offsetof(VvFrameGraphBuilder, mSize) == 0x28, "sub_bc431b0 reads src+0x28 as size");
static_assert(offsetof(VvFrameGraphBuilder, mCapacity) == 0x30, "sub_bc431b0 branches on src+0x30 as capacity");

LIFT_FN(sub_bc431b0, "sub_bc431b0", 0xbc431b0, sub_bc431b0, &sub_bc431b0_footprint);

} // namespace native::bgfx
