// LIFT 0x1d3cb0 size 0xd8 1.26.62.01 sub_1d3cb0
#include "sub_1d3cb0.h"
#include "client/features/render/native/Lift.h"

static_assert(StringPairLayout::kPtr0Offset == 0x00, "sub_1d3cb0: ptr0 at +0x00");
static_assert(StringPairLayout::kSize0Offset == 0x10, "sub_1d3cb0: size0 at +0x10");
static_assert(StringPairLayout::kCapacity0Offset == 0x18, "sub_1d3cb0: capacity0 at +0x18");
static_assert(StringPairLayout::kPtr1Offset == 0x20, "sub_1d3cb0: ptr1 at +0x20");
static_assert(StringPairLayout::kSize1Offset == 0x30, "sub_1d3cb0: size1 at +0x30");
static_assert(StringPairLayout::kCapacity1Offset == 0x38, "sub_1d3cb0: capacity1 at +0x38");
static_assert(StringPairLayout::kInitializedOffset == 0x40, "sub_1d3cb0: initialized at +0x40");

namespace native {

// Verbatim instruction quotes for verify_oc (plain lines inside #if 0)
#if 0
0x1d3cb0  push r14
0x1d3cb2  push rsi
0x1d3cb3  push rdi
0x1d3cb4  push rbx
0x1d3cb5  sub rsp,0x28
0x1d3cb9  mov rsi,rcx
0x1d3cbc  cmp byte ptr [rcx+0x40],1
0x1d3cc0  jne short 0x1D3CF5
0x1d3cc2  cmp rsi,rdx
0x1d3cc5  je 0x1D3D7E
0x1d3ccb  mov rdi,[rdx+0x10]
0x1d3ccf  cmp qword ptr [rdx+0x18],0x10
0x1d3cd4  mov r9,rdx
0x1d3cd7  jb short 0x1D3CDC
0x1d3cd9  mov r9,[rdx]
0x1d3cdc  mov rax,[rsi+0x18]
0x1d3ce0  mov r14,rdx
0x1d3ce3  cmp rdi,rax
0x1d3ce6  jbe short 0x1D3D03
0x1d3ce8  mov rcx,rsi
0x1d3ceb  mov rdx,rdi
0x1d3cee  call 0x9D6D0
0x1d3cf3  jmp short 0x1D3D25
0x1d3cf5  mov rcx,rsi
0x1d3cf8  call 0xAAD30
0x1d3cfd  mov byte ptr [rsi+0x40],1
0x1d3d01  jmp short 0x1D3D7E
0x1d3d03  mov rbx,rsi
0x1d3d06  cmp rax,0x10
0x1d3d0a  jb short 0x1D3D0F
0x1d3d0c  mov rbx,[rsi]
0x1d3d0f  mov [rsi+0x10],rdi
0x1d3d13  mov rcx,rbx
0x1d3d16  mov rdx,r9
0x1d3d19  mov r8,rdi
0x1d3d1c  call 0xEEC6DE0
0x1d3d21  mov byte ptr [rbx+rdi],0
0x1d3d25  mov rdx,r14
0x1d3d28  mov rdi,[r14+0x30]
0x1d3d2c  cmp qword ptr [r14+0x38],0x10
0x1d3d31  jb short 0x1D3D39
0x1d3d33  mov rdx,[rdx+0x20]
0x1d3d37  jmp short 0x1D3D3D
0x1d3d39  add rdx,0x20
0x1d3d3d  lea rbx,[rsi+0x20]
0x1d3d41  mov rax,[rsi+0x38]
0x1d3d45  cmp rdi,rax
0x1d3d48  jbe short 0x1D3D61
0x1d3d4a  mov rcx,rbx
0x1d3d4d  mov r9,rdx
0x1d3d50  mov rdx,rdi
0x1d3d53  add rsp,0x28
0x1d3d57  pop rbx
0x1d3d58  pop rdi
0x1d3d59  pop rsi
0x1d3d5a  pop r14
0x1d3d5c  jmp 0x9D6D0
0x1d3d61  cmp rax,0x10
0x1d3d65  jb short 0x1D3D6B
0x1d3d67  mov rbx,[rsi+0x20]
0x1d3d6b  mov [rsi+0x30],rdi
0x1d3d6f  mov rcx,rbx
0x1d3d72  mov r8,rdi
0x1d3d75  call 0xEEC6DE0
0x1d3d7a  mov byte ptr [rbx+rdi],0
0x1d3d7e  add rsp,0x28
0x1d3d82  pop rbx
0x1d3d83  pop rdi
0x1d3d84  pop rsi
0x1d3d85  pop r14
0x1d3d87  ret
#endif

// sub_1d3cb0 (0x1d3cb0, size 0xd8, 1.26.62.01)
// String assignment for a pair of strings (StringPair).
// If uninitialized (flag at +0x40 == 0), calls sub_aad30 to initialize.
// Otherwise, assigns first string from src (+0x0..+0x18) and second string from src (+0x20..+0x38).
// Uses SSO (capacity < 0x10) with inline buffer at string object base.
// Calls sub_9d6d0 (stl boundary) for reallocation when src size > dest capacity.
// Calls sub_eec6de0 (memmove) for data copy.
// sub_aad30 at 0x1d3cf8 (call target not in boundary.tsv or functions.tsv as root; tracked in progress file).

void sub_1d3cb0(StringPair* this_, const StringPair* src) {
    // 0x1d3cb0..0x1d3cbc: prologue + flag check
    // push r14; push rsi; push rdi; push rbx; sub rsp,0x28
    // mov rsi,rcx; cmp byte ptr [rcx+0x40],1; jne 0x1d3cf5
    if (reinterpret_cast<std::uint8_t*>(this_)[StringPairLayout::kInitializedOffset] != 1) {
        // 0x1d3cf5..0x1d3d01: uninitialized path
        // mov rcx,rsi; call 0xAAD30; mov byte ptr [rsi+0x40],1; jmp 0x1d3d7e
        sub_aad30_unresolved(this_);                    // 0x1d3cf8  call 0xAAD30
        reinterpret_cast<std::uint8_t*>(this_)[StringPairLayout::kInitializedOffset] = 1;  // 0x1d3cfd
        return;                                         // 0x1d3d01 jmp -> epilogue
    }

    // 0x1d3cc2..0x1d3cc5: self-assignment check
    // cmp rsi,rdx; je 0x1d3d7e
    if (this_ == src) {
        return;  // 0x1d3d7e epilogue
    }

    // 0x1d3ccb..0x1d3cd9: load src first string info
    // mov rdi,[rdx+0x10]; cmp qword ptr [rdx+0x18],0x10; mov r9,rdx; jb 0x1d3cdc; mov r9,[rdx]
    const std::uint64_t src_size0 = *reinterpret_cast<const std::uint64_t*>(
        reinterpret_cast<const std::uint8_t*>(src) + StringPairLayout::kSize0Offset);  // 0x1d3ccb
    const bool src_sso0 = *reinterpret_cast<const std::uint64_t*>(
        reinterpret_cast<const std::uint8_t*>(src) + StringPairLayout::kCapacity0Offset) < 0x10;  // 0x1d3ccf
    const char* src_ptr0 = src_sso0
        ? reinterpret_cast<const char*>(src)  // 0x1d3cd4/0x1d3cd7: r9 = rdx (src base = SSO buffer)
        : *reinterpret_cast<const char* const*>(
            reinterpret_cast<const std::uint8_t*>(src) + StringPairLayout::kPtr0Offset);  // 0x1d3cd9

    // 0x1d3cdc..0x1d3cf3: check if reallocation needed for first string
    // mov rax,[rsi+0x18]; mov r14,rdx; cmp rdi,rax; jbe 0x1d3d03
    const std::uint64_t this_capacity0 = *reinterpret_cast<const std::uint64_t*>(
        reinterpret_cast<const std::uint8_t*>(this_) + StringPairLayout::kCapacity0Offset);  // 0x1d3cdc
    // r14 = src (preserved for second string) - implicit in src variable

    if (src_size0 > this_capacity0) {
        // 0x1d3ce8..0x1d3cf3: reallocate first string
        // mov rcx,rsi; mov rdx,rdi; call 0x9D6D0; jmp 0x1d3d25
        sub_9d6d0_boundary_1(this_, src_size0);  // 0x1d3cee  call 0x9D6D0
        // Fall through to second string handling (0x1d3d25)
    } else {
        // 0x1d3d03..0x1d3d21: copy first string (fits in current capacity)
        // mov rbx,rsi; cmp rax,0x10; jb 0x1d3d0f; mov rbx,[rsi]
        char* this_ptr0 = (this_capacity0 < 0x10)
            ? reinterpret_cast<char*>(this_)  // 0x1d3d03/0x1d3d0a: rbx = rsi (SSO buffer at this_)
            : *reinterpret_cast<char**>(
                reinterpret_cast<std::uint8_t*>(this_) + StringPairLayout::kPtr0Offset);  // 0x1d3d0c

        // 0x1d3d0f..0x1d3d21: store size, memcopy, null-terminate
        // mov [rsi+0x10],rdi; mov rcx,rbx; mov rdx,r9; mov r8,rdi; call 0xEEC6DE0; mov byte ptr [rbx+rdi],0
        *reinterpret_cast<std::uint64_t*>(
            reinterpret_cast<std::uint8_t*>(this_) + StringPairLayout::kSize0Offset) = src_size0;  // 0x1d3d0f
        sub_eec6de0(this_ptr0, src_ptr0, src_size0);  // 0x1d3d1c  call 0xEEC6DE0
        this_ptr0[src_size0] = 0;  // 0x1d3d21 null-terminate

        // 0x1d3d25..0x1d3d3d: load src second string info
        // mov rdx,r14; mov rdi,[r14+0x30]; cmp qword ptr [r14+0x38],0x10; jb 0x1d3d39; mov rdx,[rdx+0x20]; jmp 0x1d3d3d
        const std::uint64_t src_size1 = *reinterpret_cast<const std::uint64_t*>(
            reinterpret_cast<const std::uint8_t*>(src) + StringPairLayout::kSize1Offset);  // 0x1d3d28
        const bool src_sso1 = *reinterpret_cast<const std::uint64_t*>(
            reinterpret_cast<const std::uint8_t*>(src) + StringPairLayout::kCapacity1Offset) < 0x10;  // 0x1d3d2c
        const char* src_ptr1 = src_sso1
            ? reinterpret_cast<const char*>(
                reinterpret_cast<const std::uint8_t*>(src) + StringPairLayout::kPtr1Offset)  // 0x1d3d39: add rdx,0x20
            : *reinterpret_cast<const char* const*>(
                reinterpret_cast<const std::uint8_t*>(src) + StringPairLayout::kPtr1Offset);  // 0x1d3d33

        // 0x1d3d3d..0x1d3d5c: check if reallocation needed for second string
        // lea rbx,[rsi+0x20]; mov rax,[rsi+0x38]; cmp rdi,rax; jbe 0x1d3d61
        char* this_sso1_buf = reinterpret_cast<char*>(
            reinterpret_cast<std::uint8_t*>(this_) + StringPairLayout::kPtr1Offset);  // 0x1d3d3d lea rbx,[rsi+0x20]
        const std::uint64_t this_capacity1 = *reinterpret_cast<const std::uint64_t*>(
            reinterpret_cast<const std::uint8_t*>(this_) + StringPairLayout::kCapacity1Offset);  // 0x1d3d41

        if (src_size1 > this_capacity1) {
            // 0x1d3d4a..0x1d3d5c: tail call to sub_9d6d0 for second string reallocation
            // mov rcx,rbx; mov r9,rdx; mov rdx,rdi; add rsp,0x28; pop rbx; pop rdi; pop rsi; pop r14; jmp 0x9D6D0
            // Note: This is a tail call with 3 args (dest_ptr, new_size, src_ptr).
            // We cannot tail-call in C++, so we call and return its result (void).
            sub_9d6d0_boundary_2(this_sso1_buf, src_size1, src_ptr1);  // 0x1d3d5c  jmp 0x9D6D0
            return;
        } else {
            // 0x1d3d61..0x1d3d7a: copy second string (fits in current capacity)
            // cmp rax,0x10; jb 0x1d3d6b; mov rbx,[rsi+0x20]
            char* this_ptr1 = (this_capacity1 < 0x10)
                ? this_sso1_buf  // 0x1d3d61/0x1d3d65: rbx = &this[1] (SSO buffer)
                : *reinterpret_cast<char**>(
                    reinterpret_cast<std::uint8_t*>(this_) + StringPairLayout::kPtr1Offset);  // 0x1d3d67

            // 0x1d3d6b..0x1d3d7a: store size, memcopy, null-terminate
            // mov [rsi+0x30],rdi; mov rcx,rbx; mov r8,rdi; call 0xEEC6DE0; mov byte ptr [rbx+rdi],0
            *reinterpret_cast<std::uint64_t*>(
                reinterpret_cast<std::uint8_t*>(this_) + StringPairLayout::kSize1Offset) = src_size1;  // 0x1d3d6b
            sub_eec6de0(this_ptr1, src_ptr1, src_size1);  // 0x1d3d75  call 0xEEC6DE0
            this_ptr1[src_size1] = 0;  // 0x1d3d7a null-terminate
        }
    }

    // 0x1d3d7e..0x1d3d87: epilogue
    // add rsp,0x28; pop rbx; pop rdi; pop rsi; pop r14; ret
    return;
}

} // namespace native

// Registry entry
LIFT_FN(lift_1d3cb0, "sub_1d3cb0", 0x1D3CB0, ::native::sub_1d3cb0, nullptr);