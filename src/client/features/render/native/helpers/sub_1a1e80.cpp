// LIFT 0x1a1e80 size 0xd2 1.26.62.01 sub_1a1e80
#include "sub_1a1e80.h"

#include "client/features/render/native/Lift.h"
#include <intrin.h>

// sub_e935700 is lift set; forward-declared here rather than including sub_e935700.h
// (that unit's header has a static_assert on its own layout type that MSVC rejects).
// Signature matches sub_e935700.h exactly: void* sub_e935700(void* a0).
namespace native {
void* sub_e935700(void* a0);

// sub_1a1e80 (0x1a1e80, size 0xd2, 1.26.62.01).
//
// Clears both sub-buffers of the object passed in RCX (a0 = this):
//   if (*(u8 *)(a0 + 0x40) != 1) return;                                   // 0x1a1e85 cmp byte ptr [rcx+0x40],1 ; 0x1a1e89 jne 0x1A1F32
//   bufferA = *(void **)(a0 + 0x20);  sizeA = *(u64 *)(a0 + 0x38);
//   if (sizeA > 0x10) release bufferA via sub_e935700;                       // 0x1a1e92..0x1a1ec8
//   *(u64 *)(a0 + 0x30) = 0; *(u64 *)(a0 + 0x38) = 0xF; *(u8 *)(a0 + 0x20) = 0;   // 0x1a1ecd..0x1a1edd
//   bufferB = *(void **)(a0 + 0x0);  sizeB = *(u64 *)(a0 + 0x18);
//   if (sizeB > 0x10) release bufferB via sub_e935700;                       // 0x1a1ee1..0x1a1f16
//   *(u64 *)(a0 + 0x10) = 0; *(u64 *)(a0 + 0x18) = 0xF; *(u8 *)(a0 + 0x0) = 0; *(u8 *)(a0 + 0x40) = 0;   // 0x1a1f1b..0x1a1f2e
// Release path for one buffer (ptr, size field):
//   if ((u64)(size + 1) < 0x1000) sub_e935700(ptr);                          // fast path
//   else {
//       bias = (ptr - 8) - *(u64 *)(ptr - 8);
//       if (bias >= 0x20) { call qword ptr [0xF9A8C78](0,0,0,0); int3; }     // 0x1a1f38..0x1a1f51 failfast
//       sub_e935700(*(void **)(ptr - 8));                                    // large path
//   }
//
// Calls [V]: 0x1a1ec8 call 0xE935700; 0x1a1f16 call 0xE935700
//   (native::sub_e935700, lift set);
//   0x1a1f4b call qword ptr [0xF9A8C78] (failfast path, target read from the data slot).
// No null guards or SEH beyond the original's own tests; no skipped branches; no return value.

void sub_1a1e80(void* a0) {
    auto* const self = reinterpret_cast<sub_1a1e80_this*>(a0);   // 0x1a1e8f mov rsi,rcx  (a0 arrives in RCX)

    // 0x1a1e80..0x1a1e85: push rsi; sub rsp,0x30
    // 0x1a1e85  cmp byte ptr [rcx+0x40],1     R a0+0x40 (enable flag)
    // 0x1a1e89  jne 0x1A1F32                  flag != 1 -> nothing to do
    if (*reinterpret_cast<std::uint8_t*>(reinterpret_cast<char*>(self) + 0x40) != 1) {  // 0x1a1e85 cmp byte ptr [rcx+0x40],1 ; 0x1a1e89 jne 0x1A1F32
        return;                                                // 0x1a1f32 add rsp,0x30 ; 0x1a1f36 pop rsi ; 0x1a1f37 ret
    }

    // ---- buffer A: this + 0x20 (ptr), + 0x30, + 0x38 ----

    // 0x1a1e92  mov rax,[rcx+0x38]        R a0+0x38 (size field A)
    // 0x1a1e96  cmp rax,0x10
    // 0x1a1e9a  jb short 0x1A1ECD         sizeA <= 0x10 -> small-buffer reset, no release
    std::uint64_t const sizeA = self->fieldA0x38;   // 0x1a1e92 mov rax,[rcx+0x38]
    if (sizeA > 0x10) {               // 0x1a1e96 cmp rax,0x10 ; 0x1a1e9a jb short 0x1A1ECD
        // 0x1a1e9c  mov rcx,[rsi+0x20]    R a0+0x20 (buffer pointer A)
        // 0x1a1ea0  lea rdx,[rax+1]       sizeA + 1
        // 0x1a1ea4  cmp rdx,0x1000
        // 0x1a1eab  jb short 0x1A1EC8     sizeA + 1 < 0x1000 -> release path A1
        void* const bufferA = self->bufferA;   // 0x1a1e9c mov rcx,[rsi+0x20]
        if ((sizeA + 1) < 0x1000) {  // 0x1a1ea0 lea rdx,[rax+1] ; 0x1a1ea4 cmp rdx,0x1000 ; 0x1a1eab jb short 0x1A1EC8
            // 0x1a1ec8  call 0xE935700    -> native::sub_e935700(bufferA)  (RDX = sizeA + 1, dead inside callee)
            native::sub_e935700(bufferA);     // 0x1a1ec8 call 0xE935700
        } else {
            // 0x1a1ead  mov r8,[rcx-8]              R *(bufferA - 8)
            // 0x1a1eb1  add rcx,0xFFFFFFFFFFFFFFF8
            // 0x1a1eb5  sub rcx,r8                  bias = (bufferA - 8) - *(u64*)(bufferA - 8)
            // 0x1a1eb8  cmp rcx,0x20
            // 0x1a1ebc  jae short 0x1A1F38          bias >= 0x20 -> failfast
            uintptr_t const biasA =
                reinterpret_cast<uintptr_t>(bufferA) - 8 -
                *reinterpret_cast<uintptr_t*>(reinterpret_cast<char*>(bufferA) - 8);
                // 0x1a1ead mov r8,[rcx-8] ; 0x1a1eb1 add rcx,... ; 0x1a1eb5 sub rcx,r8
            if (biasA >= 0x20) {    // 0x1a1eb8 cmp rcx,0x20 ; 0x1a1ebc jae short 0x1A1F38
                // 0x1a1f38..0x1a1f52 failfast path:
                //   mov qword ptr [rsp+0x20],0   (dead home-slot store; not observable)
                //   xor ecx,ecx ; xor edx,edx ; xor r8d,r8d ; xor r9d,r9d
                //   0x1a1f4b  call qword ptr [0xF9A8C78]   ; [data_f9a8c78]
                //   0x1a1f51  int3                         trap if the call returns
                using failfast_fn = void(__cdecl*)(void*, void*, void*, void*);
                failfast_fn const failfast = reinterpret_cast<failfast_fn>(
                    *reinterpret_cast<uintptr_t*>(
                        RewriteRegistry::imageBase() + sub_1a1e80Layout::kFailfastSlotRva));
                failfast(nullptr, nullptr, nullptr, nullptr);   // 0x1a1f4b call qword ptr [0xF9A8C78]
                __debugbreak();                                 // 0x1a1f51 int3 (only reached if failfast returns)
                __assume(0);
            }
            // 0x1a1ebe  add rax,0x28            sizeA + 0x28 (dead: callee overwrites RDX first)
            // 0x1a1ec2  mov rdx,rax
            // 0x1a1ec5  mov rcx,r8              [bufferA - 8]
            // 0x1a1ec8  call 0xE935700          -> native::sub_e935700(*(bufferA - 8))
            native::sub_e935700(
                *reinterpret_cast<void**>(reinterpret_cast<char*>(bufferA) - 8));  // 0x1a1ec8 call 0xE935700
        }
    }

    // 0x1a1ecd  mov qword ptr [rsi+0x30],0     W a0+0x30 = 0
    // 0x1a1ed5  mov qword ptr [rsi+0x38],0xF   W a0+0x38 = 0xF
    // 0x1a1edd  mov byte ptr [rsi+0x20],0      W a0+0x20 low byte = 0
    self->fieldA0x30 = 0;                       // 0x1a1ecd mov qword ptr [rsi+0x30],0
    self->fieldA0x38 = 0x0F;                    // 0x1a1ed5 mov qword ptr [rsi+0x38],0xF
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<char*>(self) + 0x20) = 0;  // 0x1a1edd mov byte ptr [rsi+0x20],0

    // ---- buffer B: this + 0x00 (ptr), + 0x10, + 0x18 ----

    // 0x1a1ee1  mov rax,[rsi+0x18]        R a0+0x18 (size field B)
    // 0x1a1ee5  cmp rax,0x10
    // 0x1a1ee9  jb short 0x1A1F1B         sizeB <= 0x10 -> small-buffer reset, no release
    std::uint64_t const sizeB = self->fieldB0x18;   // 0x1a1ee1 mov rax,[rsi+0x18]
    if (sizeB > 0x10) {               // 0x1a1ee5 cmp rax,0x10 ; 0x1a1ee9 jb short 0x1A1F1B
        // 0x1a1eeb  mov rcx,[rsi]         R a0+0x00 (buffer pointer B)
        // 0x1a1eee  lea rdx,[rax+1]       sizeB + 1
        // 0x1a1ef2  cmp rdx,0x1000
        // 0x1a1ef9  jb short 0x1A1F16     sizeB + 1 < 0x1000 -> release path B1
        void* const bufferB = self->bufferB;   // 0x1a1eeb mov rcx,[rsi]
        if ((sizeB + 1) < 0x1000) {  // 0x1a1eee lea rdx,[rax+1] ; 0x1a1ef2 cmp rdx,0x1000 ; 0x1a1ef9 jb short 0x1A1F16
            // 0x1a1f16  call 0xE935700    -> native::sub_e935700(bufferB)  (RDX = sizeB + 1, dead inside callee)
            native::sub_e935700(bufferB);     // 0x1a1f16 call 0xE935700
        } else {
            // 0x1a1efb  mov r8,[rcx-8]              R *(bufferB - 8)
            // 0x1a1eff  add rcx,0xFFFFFFFFFFFFFFF8
            // 0x1a1f03  sub rcx,r8                  bias = (bufferB - 8) - *(u64*)(bufferB - 8)
            // 0x1a1f06  cmp rcx,0x20
            // 0x1a1f0a  jae short 0x1A1F38          bias >= 0x20 -> failfast
            uintptr_t const biasB =
                reinterpret_cast<uintptr_t>(bufferB) - 8 -
                *reinterpret_cast<uintptr_t*>(reinterpret_cast<char*>(bufferB) - 8);
            if (biasB >= 0x20) {    // 0x1a1f06 cmp rcx,0x20 ; 0x1a1f0a jae short 0x1A1F38
                // failfast path shared with buffer A (falls into the same block at 0x1a1f38)
                using failfast_fn = void(__cdecl*)(void*, void*, void*, void*);
                failfast_fn const failfast = reinterpret_cast<failfast_fn>(
                    *reinterpret_cast<uintptr_t*>(
                        RewriteRegistry::imageBase() + sub_1a1e80Layout::kFailfastSlotRva));
                failfast(nullptr, nullptr, nullptr, nullptr);   // 0x1a1f4b call qword ptr [0xF9A8C78]
                __debugbreak();                                 // 0x1a1f51 int3
                __assume(0);
            }
            // 0x1a1f0c  add rax,0x28
            // 0x1a1f10  mov rdx,rax
            // 0x1a1f13  mov rcx,r8              [bufferB - 8]
            // 0x1a1f16  call 0xE935700          -> native::sub_e935700(*(bufferB - 8))
            native::sub_e935700(
                *reinterpret_cast<void**>(reinterpret_cast<char*>(bufferB) - 8));  // 0x1a1f16 call 0xE935700
        }
    }

    // 0x1a1f1b  mov qword ptr [rsi+0x10],0     W a0+0x10 = 0
    // 0x1a1f23  mov qword ptr [rsi+0x18],0xF   W a0+0x18 = 0xF
    // 0x1a1f2b  mov byte ptr [rsi],0           W a0+0x00 low byte = 0
    // 0x1a1f2e  mov byte ptr [rsi+0x40],0      W a0+0x40 = 0
    self->fieldB0x10 = 0;                       // 0x1a1f1b mov qword ptr [rsi+0x10],0
    self->fieldB0x18 = 0x0F;                    // 0x1a1f23 mov qword ptr [rsi+0x18],0xF
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<char*>(self) + 0x00) = 0;  // 0x1a1f2b mov byte ptr [rsi],0
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<char*>(self) + 0x40) = 0;  // 0x1a1f2e mov byte ptr [rsi+0x40],0

    // 0x1a1f32  add rsp,0x30
    // 0x1a1f36  pop rsi
    // 0x1a1f37  ret
    return;
}

} // namespace native

LIFT_FN(sub_1a1e80, "sub_1a1e80", 0x1a1e80, ::native::sub_1a1e80, nullptr);

#if 0
// Verbatim instructions of [0x1a1e80, 0x1a1f52) (rdis dis 0x1a1e80 0xd2);
// machine-checked by tools/sigs/verify_oc.py against the exe.
0x1a1e80  push rsi
0x1a1e81  sub rsp,0x30
0x1a1e85  cmp byte ptr [rcx+0x40],1
0x1a1e89  jne 0x1A1F32
0x1a1e8f  mov rsi,rcx
0x1a1e92  mov rax,[rcx+0x38]
0x1a1e96  cmp rax,0x10
0x1a1e9a  jb short 0x1A1ECD
0x1a1e9c  mov rcx,[rsi+0x20]
0x1a1ea0  lea rdx,[rax+1]
0x1a1ea4  cmp rdx,0x1000
0x1a1eab  jb short 0x1A1EC8
0x1a1ead  mov r8,[rcx-8]
0x1a1eb1  add rcx,0xFFFFFFFFFFFFFFF8
0x1a1eb5  sub rcx,r8
0x1a1eb8  cmp rcx,0x20
0x1a1ebc  jae short 0x1A1F38
0x1a1ebe  add rax,0x28
0x1a1ec2  mov rdx,rax
0x1a1ec5  mov rcx,r8
0x1a1ec8  call 0xE935700
0x1a1ecd  mov qword ptr [rsi+0x30],0
0x1a1ed5  mov qword ptr [rsi+0x38],0xF
0x1a1edd  mov byte ptr [rsi+0x20],0
0x1a1ee1  mov rax,[rsi+0x18]
0x1a1ee5  cmp rax,0x10
0x1a1ee9  jb short 0x1A1F1B
0x1a1eeb  mov rcx,[rsi]
0x1a1eee  lea rdx,[rax+1]
0x1a1ef2  cmp rdx,0x1000
0x1a1ef9  jb short 0x1A1F16
0x1a1efb  mov r8,[rcx-8]
0x1a1eff  add rcx,0xFFFFFFFFFFFFFFF8
0x1a1f03  sub rcx,r8
0x1a1f06  cmp rcx,0x20
0x1a1f0a  jae short 0x1A1F38
0x1a1f0c  add rax,0x28
0x1a1f10  mov rdx,rax
0x1a1f13  mov rcx,r8
0x1a1f16  call 0xE935700
0x1a1f1b  mov qword ptr [rsi+0x10],0
0x1a1f23  mov qword ptr [rsi+0x18],0xF
0x1a1f2b  mov byte ptr [rsi],0
0x1a1f2e  mov byte ptr [rsi+0x40],0
0x1a1f32  add rsp,0x30
0x1a1f36  pop rsi
0x1a1f37  ret
0x1a1f38  mov qword ptr [rsp+0x20],0
0x1a1f41  xor ecx,ecx
0x1a1f43  xor edx,edx
0x1a1f45  xor r8d,r8d
0x1a1f48  xor r9d,r9d
0x1a1f4b  call qword ptr [0xF9A8C78]
0x1a1f51  int3
#endif
