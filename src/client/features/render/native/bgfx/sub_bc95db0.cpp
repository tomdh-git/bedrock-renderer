// LIFT 0xbc95db0 size 0x391 1.26.62.01 sub_bc95db0
#include "client/features/render/native/bgfx/sub_bc95db0.h"

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "client/features/render/native/Lift.h"

// Verbatim call instructions from the disassembly of [0xbc95db0, 0xbc96141).
// 0xbc95eae  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
// 0xbc95eda  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
// 0xbc95ef7  call 0xEEC6EC0                                ; -> sub_eec6ec0 (memcpy lift)
// 0xbc95f94  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
// 0xbc95fbc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
// 0xbc95fd9  call 0xEEC6EC0                                ; -> sub_eec6ec0 (memcpy lift)
// 0xbc96081  call 0xE935700                                ; -> sub_e935700 (free lift)
// 0xbc960e6  call 0x9BC830                                 ; -> sub_9bc830 (alloc OOM boundary)
// 0xbc960f4  call 0x9BC830                                 ; -> sub_9bc830
// 0xbc960fa  lea rcx,[rsi+0x28]                             ; (allocSize = cap + 0x28)
// 0xbc960fe  call 0x9BC830                                 ; -> sub_9bc830
// 0xbc9610d  call 0x9BC830                                 ; -> sub_9bc830
// 0xbc9611b  call 0x75720                                  ; -> sub_75720 (stl boundary, noreturn)
// 0xbc96121  call 0x75720                                  ; -> sub_75720
// 0xbc9613a  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78] = _invoke_watson (noreturn)
// UNRESOLVED CALL = none.

namespace {

extern "C" {
uint64_t data_12ae1c50;
uint64_t data_12ae1c58;
uint64_t data_12ae1c60;
uint64_t data_12ae1c68;
uint64_t data_12ae1c70;
uint64_t data_12ae1c78;
uint64_t data_12ae1c88;
uint64_t data_12ae1c90;
uint64_t data_12ae1c98;
uint64_t data_12ae1ca0;
uint64_t data_12ae1ca8;
uint64_t data_12ae1cb0;
}

native::Boundary<void, void*> sub_75720("sub_75720");
native::Boundary<void, uint64_t> sub_9bc830("sub_9bc830");

} // namespace

namespace native::bgfx {

// Footprint: writes only within *dst and *src objects (0x20 bytes each) and the globals.
static native::Footprint sub_bc95db0_footprint(VvSmallString* dst, VvSmallString* src) {
    return { { { dst, 0x20 }, { src, 0x20 } } };
}

void sub_bc95db0(VvSmallString* dst, VvSmallString* src) {
    // 0xbc95db0..0xbc95e3a — prologue: save callee-saved; clear src then dst.
    // 0xbc95dd3  mov r8,[rdx]                                ; R src.mData
    // 0xbc95dd6  mov r9,[rdx+0x18]                           ; R src.mCapacity
    // 0xbc95dda  mov qword ptr [rdx+0x18],0xF                ; W src.mCapacity = 0xF
    // 0xbc95de2  mov byte ptr [rdx],0                         ; W src.mData[0] = 0
    // 0xbc95de5  mov rsi,[rdx+0x10]                          ; R src.mSize
    // 0xbc95de9  movups xmm0,[rdx+8]                         ; R src.mBuf (16B)
    // 0xbc95ded  mov qword ptr [rdx+0x10],0                   ; W src.mSize = 0
    void* saved_src_mData = src->mData;
    uint64_t saved_src_mCap = src->mCapacity;
    uint64_t saved_src_mSize = src->mSize;
    uint64_t src_buf_lo = reinterpret_cast<const uint64_t*>(src->mBuf)[0];
    uint64_t src_buf_hi = reinterpret_cast<const uint64_t*>(src->mBuf)[1];
    src->mCapacity = 0xFULL;
    src->mData = nullptr;
    src->mSize = 0;

    // 0xbc95df5  movzx eax,byte ptr [rcx]                    ; R dst.mData[0]
    // 0xbc95df8  mov rdx,[rcx+8]                             ; R dst.mBuf[0..7]
    // 0xbc95dfc  mov [rbp+8],rdx                             ; (save)
    // 0xbc95e00  mov rdx,[rcx+1]                             ; R dst.mData[1..7]+mBuf[0]
    // 0xbc95e04  mov [rbp+1],rdx                             ; (save)
    // 0xbc95e08  mov r15,[rcx+0x10]                          ; R dst.mSize
    // 0xbc95e0c  mov r13,[rcx+0x18]                          ; R dst.mCapacity
    // 0xbc95e10  mov qword ptr [rcx+0x10],0                   ; W dst.mSize = 0
    // 0xbc95e18  mov qword ptr [rcx+0x18],0xF                 ; W dst.mCapacity = 0xF
    // 0xbc95e20  mov byte ptr [rcx],0                         ; W dst.mData[0] = 0
    void* saved_dst_mData = dst->mData;
    uint64_t saved_dst_mCap = dst->mCapacity;
    uint64_t saved_dst_mSize = dst->mSize;
    (void)src_buf_lo; (void)src_buf_hi;
    dst->mSize = 0;
    dst->mCapacity = 0xFULL;
    dst->mData = nullptr;

    // 0xbc95e3a  cmp r9,0x10                                  ; src.mCapacity >= 0x10 ?
    // 0xbc95e3e  lea rax,[rbp-0x20]                          ; rax = &frame.src.mData slot
    // 0xbc95e42  mov rdi,rax                                  ; rdi = &slot
    // 0xbc95e45  cmovae rdi,r8                                ; if src.mCap>=0x10: rdi = src.mData
    // 0xbc95e49  test rsi,rsi                                 ; src.mSize < 0 ?
    // 0xbc95e4c  js 0xBC9611B                                  ; -> sub_75720 (noreturn)
    // rsi = saved_src_mSize here
    if (static_cast<int64_t>(saved_src_mSize) < 0) {
        // 0xbc9611b  call 0x75720                             ; -> sub_75720 (noreturn)
        sub_75720(dst);
        __builtin_unreachable();
    }

    // ---- src path selection by size ----
    // 0xbc95e52  cmp rsi,0xF                                  ; src.mSize > 0xF ?
    // 0xbc95e5e  ja short 0xBC95E7A                            ; heap src path
    void* new_src_buf = nullptr;   // r14 after src path
    uint64_t rax_val = 0;         // rax after src path
    uint64_t new_cap = 0;         // r12 after src path
    if (saved_src_mSize > 0xFULL) {
        // 0xbc95e7a..0xbc95efc — heap src path: alloc + copy
        // 0xbc95e7a  mov rdx,rsi
        // 0xbc95e7d  or rdx,0xF
        // 0xbc95e81  cmp rdx,0x17
        // 0xbc95e85  mov r12d,0x16
        // 0xbc95e8b  cmovae r12,rdx
        uint64_t rdxv = saved_src_mSize | 0xFULL;
        new_cap = (rdxv >= 0x17ULL) ? rdxv : 0x16ULL;
        // 0xbc95e8f  mov rcx,[0x1233E1A8]                     ; allocator object (side-effect loads)
        // 0xbc95e96  mov rax,[rcx]
        // 0xbc95e99  mov rax,[rax+8]
        // 0xbc95e9d  cmp rdx,0xFFF
        // 0xbc95ea4  jb short 0xBC95ED2
        uint64_t allocSize;
        if (rdxv < 0x1000ULL) {
            // 0xbc95ed2  lea rbx,[r12+1]
            allocSize = new_cap + 1ULL;
        } else {
            // 0xbc95ea6  lea rbx,[r12+0x28]
            allocSize = new_cap + 0x28ULL;
        }
        // 0xbc95eae/0xbc95eda  call qword ptr [0xF99FFA0]    ; -> sub_eea6040 (compiled to std::malloc)
        void* result = std::malloc(allocSize);
        if (result == nullptr) {
            // 0xbc960e3/0xbc960f1/0xbc960fa/0xbc96109 — OOM handlers
            // 0xbc960e6  call 0x9BC830                       ; -> sub_9bc830 (allocSize)
            sub_9bc830(allocSize);
            // handler returns in one path; treat as noreturn here for fail-fast
            __builtin_unreachable();
        }
        // 0xbc95ec1  mov r14,rax
        // 0xbc95ec4  add r14,0x27
        // 0xbc95ec8  and r14,0xFFFFFFFFFFFFFFE0
        // 0xbc95ecc  mov [r14-8],rax                          ; cookie
        // 0xbc95eed  lea r8,[rsi+1]
        // 0xbc95ef1  mov rcx,r14
        // 0xbc95ef4  mov rdx,rdi                              ; rdi = src.mData (heap)
        // 0xbc95ef7  call 0xEEC6EC0                            ; memcpy(r14, src.mData, src.mSize+1)
        // 0xbc95efc  xor eax,eax
        new_src_buf = reinterpret_cast<void*>((reinterpret_cast<uintptr_t>(result) + 0x27ULL) & ~0x1FULL);
        *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(new_src_buf) - 8) = result;
        // rdi = src.mData (heap) — saved_src_mData is the heap ptr
        std::memcpy(new_src_buf, saved_src_mData, saved_src_mSize + 1);
        rax_val = 0;
    } else {
        // 0xbc95e60..0xbc95e75 — SSO src path
        // r14 = src.mData (saved), rax = src.mBuf[0..7], r12 = 0xF
        new_src_buf = saved_src_mData;
        rax_val = src_buf_lo; // src.mBuf[0..7]
        new_cap = 0xFULL;
    }

    // ---- 0xbc95efe..0xbc95f27 — common tail after src copy ----
    // 0xbc95efe  lea rbx,[rbp]                                ; (frame base)
    // 0xbc95f02  mov rdx,0x1000000010
    // 0xbc95f0c  mov [rbp-0x58],rdx
    // 0xbc95f10  mov dword ptr [rbp-0x50],1
    // 0xbc95f17  mov [rbp-0x48],r14
    // 0xbc95f1b  mov [rbp-0x40],rax
    // 0xbc95f1f  mov [rbp-0x38],rsi
    // 0xbc95f23  mov [rbp-0x30],r12
    // 0xbc95f27  cmp r13,0x10                                 ; dst.mCapacity >= 0x10 ?
    // saved values: r14=new_src_buf, rax=rax_val, rsi=saved_src_mSize, r12=new_cap
    // r13=saved_dst_mCap, r15=saved_dst_mSize
    // rdi = saved_dst_mData (reconstructed)
    rdi = saved_dst_mData;

    // ---- dst old-data handling ----
    // 0xbc95f2f  cmovae rbx,rdi                                ; if dst.mCap>=0x10: rbx = dst.mData (heap ptr for free)
    // 0xbc95f33  test r15,r15                                    ; dst.mSize < 0 ?
    // 0xbc95f36  js 0xBC96121                                  ; -> sub_75720
    // 0xbc95f3c  cmp r15,0xF                                    ; dst.mSize > 0xF ?
    // 0xbc95f40  ja short 0xBC95F62                            ; heap dst path
    if (static_cast<int64_t>(saved_dst_mSize) < 0) {
        // 0xbc96121  call 0x75720                              ; -> sub_75720 (noreturn)
        sub_75720(dst);
        __builtin_unreachable();
    }
    if (saved_dst_mSize > 0xFULL) {
        // 0xbc95f62..0xbc95fde — heap dst path: alloc + copy old dst
        // 0xbc95f62  mov r12,rdx                                 ; r12 = rdx (=0x1000000010)
        // 0xbc95f65  mov rdx,r15                                  ; rdx = dst.mSize
        // 0xbc95f68  or rdx,0xF
        // 0xbc95f6c  cmp rdx,0x17
        // 0xbc95f70  mov esi,0x16
        // 0xbc95f75  cmovae rsi,rdx
        uint64_t rdxv2 = saved_dst_mSize | 0xFULL;
        uint64_t esi2 = (rdxv2 >= 0x17ULL) ? rdxv2 : 0x16ULL;
        // 0xbc95f79  mov rcx,[0x1233E1A8]
        // 0xbc95f80  mov rax,[rcx]
        // 0xbc95f83  mov rax,[rax+8]
        // 0xbc95f87  cmp rdx,0xFFF
        // 0xbc95f8e  jb short 0xBC95FB8
        // 0xbc95f90  lea rdx,[rsi+0x28]
        // 0xbc95f94  call qword ptr [0xF99FFA0]
        // 0xbc95f9a  nop
        // 0xbc95f9b  mov r14,rax
        // 0xbc95f9e  test rax,rax
        // 0xbc95fa1  je 0xBC960FA
        // 0xbc95fa7  mov rax,r14
        // 0xbc95faa  add r14,0x27
        // 0xbc95fae  and r14,0xFFFFFFFFFFFFFFE0
        // 0xbc95fb2  mov [r14-8],rax
        // 0xbc95fb6  jmp short 0xBC95FCF
        // 0xbc95fb8  lea rdx,[rsi+1]
        // 0xbc95fbc  call qword ptr [0xF99FFA0]
        // 0xbc95fc2  nop
        // 0xbc95fc3  mov r14,rax
        // 0xbc95fc6  test rax,rax
        // 0xbc95fc9  je 0xBC96109
        // 0xbc95fcf  lea r8,[r15+1]
        // 0xbc95fd3  mov rcx,r14
        // 0xbc95fd6  mov rdx,rbx
        // 0xbc95fd9  call 0xEEC6EC0                             ; memcpy(r14, oldDst.mData, oldDst.mSize+1)
        // 0xbc95fde  xor eax,eax
        // 0xbc95fe0  mov rdx,r12                                ; rdx = 0x1000000010
        uint64_t allocSize2;
        if (rdxv2 < 0x1000ULL) {
            allocSize2 = esi2 + 1ULL;
        } else {
            allocSize2 = esi2 + 0x28ULL;
        }
        void* result2 = std::malloc(allocSize2);
        if (result2 == nullptr) {
            sub_9bc830(allocSize2);
            __builtin_unreachable();
        }
        r14 = reinterpret_cast<void*>((reinterpret_cast<uintptr_t>(result2) + 0x27ULL) & ~0x1FULL);
        *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(r14) - 8) = result2;
        std::memcpy(r14, saved_dst_mData, saved_dst_mSize + 1);
        rax_val = 0;
        new_cap = 0x1000000010ULL; // r12 = 0x1000000010
        (void)esi2;
    } else {
        // 0xbc95f42..0xbc95f5d — SSO dst path
        // 0xbc95f42  lea rax,[rdi+8]                            ; rax = dst.mData + 8
        // 0xbc95f46  cmp r13,0x10
        // 0xbc95f4a  mov r14,[rbx]                              ; r14 = [rbx]
        // 0xbc95f4d  lea rcx,[rbp+8]                            ; rcx = &frame.dst.mBuf[0..7]
        // 0xbc95f51  cmovae rcx,rax                            ; if dst.mCap>=0x10: rcx = rax
        // 0xbc95f55  mov rax,[rcx]                              ; rax = dst.mBuf[0..7]
        // 0xbc95f58  mov esi,0xF                                ; esi = 0xF
        // 0xbc95f5d  jmp 0xBC95FE3
        r14 = saved_dst_mData; // [rbx] where rbx = rbp (SSO) → frame dst.mData[0..7] approximated
        rax_val = reinterpret_cast<const uint64_t*>(saved_dst_mData)[1]; // dst.mBuf[0..7] (approx)
        (void)rax_val;
        // keep rsi = saved_src_mSize (unchanged; esi=0xF only sets low register)
    }

    // ---- 0xbc95fe3..0xbc96044 — globals writes ----
    // 0xbc95fe3  lea rcx,[rbp-0x48]
    // 0xbc95fe7  mov [0x12AE1C50],rdx                          ; rdx = 0x1000000010
    // 0xbc95fee  mov dword ptr [0x12AE1C58],1
    // 0xbc95ff8  movups xmm0,[rcx]                             ; xmm0 = [rbp-0x48..-0x39] = r14, rax
    // 0xbc95ffb  movups xmm1,[rcx+0x10]                        ; xmm1 = [rbp-0x38..-0x29] = rsi, r12
    // 0xbc95fff  movups [0x12AE1C60],xmm0
    // 0xbc96006  movups [0x12AE1C70],xmm1
    // 0xbc9600d  mov rcx,0x800000010
    // 0xbc96017  mov [0x12AE1C88],rcx
    // 0xbc9601e  mov dword ptr [0x12AE1C90],1
    // 0xbc96028  mov [0x12AE1C98],r14
    // 0xbc9602f  mov [0x12AE1CA0],rax
    // 0xbc96036  mov [0x12AE1CA8],r15
    // 0xbc9603d  mov [0x12AE1CB0],rsi
    data_12ae1c50 = 0x1000000010ULL;
    data_12ae1c58 = 1ULL;
    data_12ae1c60 = reinterpret_cast<uint64_t>(new_src_buf);
    data_12ae1c68 = rax_val;
    data_12ae1c70 = saved_src_mSize;
    data_12ae1c78 = new_cap;
    data_12ae1c88 = 0x800000010ULL;
    data_12ae1c90 = 1ULL;
    data_12ae1c98 = reinterpret_cast<uint64_t>(new_src_buf);
    data_12ae1ca0 = rax_val;
    data_12ae1ca8 = saved_dst_mSize;
    data_12ae1cb0 = saved_src_mSize;

    // ---- 0xbc96044..0xbc96086 — free old dst heap buffer if heap ----
    // 0xbc96044  cmp r13,0x10
    // 0xbc96048  mov rsi,[rbp+0x20]
    // 0xbc9604c  mov rbx,[rbp+0x28]
    // 0xbc96050  jb short 0xBC96086                            ; if dst.mCap < 0x10: skip
    // 0xbc96052..0xbc96081  free old dst heap buffer
    if (saved_dst_mCap >= 0x10ULL) {
        uint64_t rdxv = saved_dst_mCap + 1ULL;
        if (rdxv < 0x1000ULL) {
            // 0xbc9607e  mov rcx,rdi
            // 0xbc96081  call 0xE935700                          ; -> sub_e935700(free) (rdi = saved_dst_mData)
            sub_e935700(saved_dst_mData);
        } else {
            // 0xbc9605f  mov rax,[rdi-8]
            // 0xbc96063  add rdi,0xFFFFFFFFFFFFFFF8
            // 0xbc96067  sub rdi,rax
            // 0xbc9606a  cmp rdi,0x20
            // 0xbc9606e  jae 0xBC96127                           ; watson (integrity)
            // 0xbc96074  add r13,0x28
            // 0xbc96078  mov rdx,r13
            // 0xbc9607b  mov rdi,rax
            // 0xbc9607e  mov rcx,rdi
            // 0xbc96081  call 0xE935700
            void* cookie = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(saved_dst_mData) - 8);
            void* ptr = cookie;
            sub_e935700(ptr);
        }
    }

    // ---- 0xbc96086..0xbc960ca/0xbc960cf — free old src heap buffer (tail) or return ----
    // 0xbc96086  cmp rbx,0x10                                  ; src.mCap (saved) >= 0x10 ?
    // 0xbc9608a  jb short 0xBC960CF                             ; if SSO src: just return
    // 0xbc9608c..0xbc960b4  free old src heap buffer
    // 0xbc960b7  add rsp,0xB8 / pops / 0xbc960ca  jmp 0xE935700  ; tail-call free
    // 0xbc960cf  add rsp,0xB8 / pops / 0xbc960e2  ret
    if (saved_src_mCap >= 0x10ULL) {
        // free old src heap buffer via tail call
        void* cookie = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(saved_src_mData) - 8);
        void* ptr = cookie;
        sub_e935700(ptr);
    }
    // return (void)
}

static_assert(offsetof(native::bgfx::VvSmallString, mData) == 0x00, "sub_bc95db0 reads/writes +0x00 mData");
static_assert(offsetof(native::bgfx::VvSmallString, mBuf) == 0x08, "sub_bc95db0 reads/writes +0x08 mBuf");
static_assert(offsetof(native::bgfx::VvSmallString, mSize) == 0x10, "sub_bc95db0 reads/writes +0x10 mSize");
static_assert(offsetof(native::bgfx::VvSmallString, mCapacity) == 0x18, "sub_bc95db0 reads/writes +0x18 mCapacity");
static_assert(sizeof(native::bgfx::VvSmallString) == 0x20, "sub_bc95db0 small-string is 0x20 bytes");

} // namespace native::bgfx

LIFT_FN(sub_bc95db0, "sub_bc95db0", 0xbc95db0, sub_bc95db0, &sub_bc95db0_footprint);
