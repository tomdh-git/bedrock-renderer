// LIFT 0x675b550 size 0xc8 1.26.62.01 BgfxFrameBuilder::endFrame
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/framebuilder/sub_675b550.h"

#include <cstdint>
#include <cstring>
#include <intrin.h>
#include <vector>

namespace native {

// Layout assertions (definitions and the full set of offset static_asserts live in
// sub_675b550.h; repeated here so liftcheck sees them in the source file).
static_assert(kObjOffsetVector == 0x10, "sub_675b550: this+0x10 is the vector object (R)");
static_assert(kObjOffsetMylast == 0x18, "sub_675b550: this+0x18 is vector._Mylast (R)");
static_assert(kObjOffsetMyend == 0x20, "sub_675b550: this+0x20 is vector._Myend (R)");
static_assert(kEntrySize == 0x58, "sub_675b550: vector element size is 0x58");
static_assert(sizeof(FrameEntry) == 0x58, "sub_675b550: FrameEntry size 0x58");
static_assert(kStackFlagOffset == 0x00, "sub_675b550: [rbp+0x00] is the flag byte");
static_assert(kStackCookieOffset == 0x10, "sub_675b550: [rbp+0x10] is the cookie store");
static_assert(kStackSizeOutOffset == 0x18, "sub_675b550: [rbp-0x18] is read if flag == 1");
static_assert(kStackPtrOutOffset == 0x30, "sub_675b550: [rbp-0x30] is read if flag == 1");
static_assert(sizeof(void*) == 8, "sub_675b550: x64 pointers are 8 bytes");

// Verbatim instructions of the function (matches rdis dis 0x675b550 0xc8 from the exe,
// machine-checked with tools/sigs/verify_oc.py).
// The call at 0x675b5aa to sub_b0ad0 (stl boundary) is replaced by std::vector::push_back.
// The call at 0x675b5ec to sub_e935700 (lift) is a direct native call.
// The call at 0x675b611 is an indirect call through data slot 0xF9A8C78.
#if 0
0x675b550  push rbp
0x675b551  push rsi
0x675b552  sub rsp,0x98
0x675b559  lea rbp,[rsp+0x80]
0x675b561  mov qword ptr [rbp+0x10],0xFFFFFFFFFFFFFFFE
0x675b569  mov rsi,rcx
0x675b56c  movups xmm0,[0xF2BE868]
0x675b573  movaps [rbp-0x40],xmm0
0x675b577  movups xmm1,[0xF2BE858]
0x675b57e  movaps [rbp-0x50],xmm1
0x675b582  mov byte ptr [rbp],0
0x675b586  mov rdx,[rcx+0x18]
0x675b58a  cmp rdx,[rcx+0x20]
0x675b58e  je short 0x675B5A2
0x675b590  movups [rdx+0x10],xmm0
0x675b594  movups [rdx],xmm1
0x675b597  mov byte ptr [rdx+0x50],0
0x675b59b  add qword ptr [rsi+0x18],0x58
0x675b5a0  jmp short 0x675B5F1
0x675b5a2  lea rcx,[rsi+0x10]
0x675b5a6  lea r8,[rbp-0x50]
0x675b5aa  call 0xB0AD0
0x675b5af  nop
0x675b5b0  cmp byte ptr [rbp],1
0x675b5b4  jne short 0x675B5F1
0x675b5b6  mov rax,[rbp-0x18]
0x675b5ba  cmp rax,0x10
0x675b5be  jb short 0x675B5F1
0x675b5c0  mov rcx,[rbp-0x30]
0x675b5c4  lea rdx,[rax+1]
0x675b5c8  cmp rdx,0x1000
0x675b5cf  jb short 0x675B5EC
0x675b5d1  mov r8,[rcx-8]
0x675b5d5  add rcx,0xFFFFFFFFFFFFFFF8
0x675b5d9  sub rcx,r8
0x675b5dc  cmp rcx,0x20
0x675b5e0  jae short 0x675B5FE
0x675b5e2  add rax,0x28
0x675b5e6  mov rdx,rax
0x675b5e9  mov rcx,r8
0x675b5ec  call 0xE935700
0x675b5f1  mov rax,rsi
0x675b5f4  add rsp,0x98
0x675b5fb  pop rsi
0x675b5fc  pop rbp
0x675b5fd  ret
0x675b5fe  mov qword ptr [rsp+0x20],0
0x675b607  xor ecx,ecx
0x675b609  xor edx,edx
0x675b60b  xor r8d,r8d
0x675b60e  xor r9d,r9d
0x675b611  call qword ptr [0xF9A8C78]
0x675b617  int3
#endif

void* sub_675b550(void* a0) {
    // 0x675b550  push rbp
    // 0x675b551  push rsi
    // 0x675b552  sub rsp,0x98
    // 0x675b559  lea rbp,[rsp+0x80]   (compiler frame setup)
    void* const thisObj = a0;          // 0x675b569  mov rsi,rcx  (save this)

    // 0x675b561  mov qword ptr [rbp+0x10],0xFFFFFFFFFFFFFFFE   (frame cookie store, dead)
    // 0x675b582  mov byte ptr [rbp],0                             (flag = 0)
    bool flag = false;                 // [rbp+0x00]

    // 0x675b56c  movups xmm0,[0xF2BE868]
    // 0x675b573  movaps [rbp-0x40],xmm0
    // 0x675b577  movups xmm1,[0xF2BE858]
    // 0x675b57e  movaps [rbp-0x50],xmm1
    // Build the default entry in a local buffer:
    //   entry+0x00 = [0xF2BE858] (16 bytes)
    //   entry+0x10 = [0xF2BE868] (16 bytes)
    FrameEntry entry{};
    std::memcpy(entry.data, reinterpret_cast<const std::uint8_t*>(kDataF2BE858), 16);
    std::memcpy(entry.data + 0x10, reinterpret_cast<const std::uint8_t*>(kDataF2BE868), 16);
    entry.data[0x50] = 0;              // same constant byte written to entry+0x50 in both paths

    // 0x675b586  mov rdx,[rcx+0x18]    ; rdx = vector._Mylast
    // 0x675b58a  cmp rdx,[rcx+0x20]    ; compare with vector._Myend
    // 0x675b58e  je short 0x675B5A2    ; if equal (full), go to growth path
    auto& vec = *reinterpret_cast<std::vector<FrameEntry>*>(reinterpret_cast<std::uint8_t*>(thisObj) + kObjOffsetVector);
    if (vec.size() < vec.capacity()) { // 0x675b58a..0x675b58e  (_Mylast != _Myend -> space available)
        // 0x675b590  movups [rdx+0x10],xmm0    ; W *(_Mylast+0x10) = [0xF2BE868]
        // 0x675b594  movups [rdx],xmm1         ; W *(_Mylast+0x00) = [0xF2BE858]
        // 0x675b597  mov byte ptr [rdx+0x50],0 ; W *(_Mylast+0x50) = 0
        // 0x675b59b  add qword ptr [rsi+0x18],0x58  ; W _Mylast += 0x58
        // 0x675b5a0  jmp short 0x675B5F1       ; -> epilogue
        vec.push_back(entry);           // constructs entry at _Mylast, advances _Mylast by sizeof(FrameEntry) == 0x58
    } else {
        // 0x675b5a2  lea rcx,[rsi+0x10]     ; RCX = &vector
        // 0x675b5a6  lea r8,[rbp-0x50]      ; R8 = &entry data
        // 0x675b5aa  call 0xB0AD0           ; sub_b0ad0 (stl boundary: vector growth + push_back)
        // Replaced by std::vector::push_back which handles growth internally.
        vec.push_back(entry);           // 0x675b5aa  call 0xB0AD0 (STL equivalent)
        // [rbp] / flag is still false: push_back does not modify our stack flag.
    }

    // 0x675b5b0  cmp byte ptr [rbp],1      ; flag == 1? (never: push_back doesn't set it)
    // 0x675b5b4  jne short 0x675B5F1       ; skip (always taken)
    if (flag) {                         // 0x675b5b0..0x675b5b4  (unreachable dead code)
        // 0x675b5b6  mov rax,[rbp-0x18]    ; uninitialized stack read
        // 0x675b5ba  cmp rax,0x10
        // 0x675b5be  jb short 0x675B5F1
        std::uint64_t rax = 0;          // [rbp-0x18] (uninitialized in original)
        if (rax >= 0x10) {
            // 0x675b5c0  mov rcx,[rbp-0x30]  ; uninitialized stack read
            // 0x675b5c4  lea rdx,[rax+1]
            // 0x675b5c8  cmp rdx,0x1000
            // 0x675b5cf  jb short 0x675B5EC
            void* rcx = reinterpret_cast<void*>(0);  // [rbp-0x30] (uninitialized in original)
            std::uint64_t rdx = rax + 1;
            if (rdx < 0x1000) {
                // 0x675b5ec  call 0xE935700   ; sub_e935700(rcx, rdx) (RDX dead)
                sub_e935700(rcx);       // 0x675b5ec  call 0xE935700
            } else {
                // 0x675b5d1  mov r8,[rcx-8]
                // 0x675b5d5  add rcx,0xFFFFFFFFFFFFFFF8
                // 0x675b5d9  sub rcx,r8
                // 0x675b5dc  cmp rcx,0x20
                // 0x675b5e0  jae short 0x675B5FE
                // 0x675b5e2  add rax,0x28
                // 0x675b5e6  mov rdx,rax
                // 0x675b5e9  mov rcx,r8
                // 0x675b5ec  call 0xE935700
                std::uintptr_t r8 = *reinterpret_cast<const std::uintptr_t*>(reinterpret_cast<std::uintptr_t>(rcx) - 8);
                rcx = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(rcx) - 8 - r8);
                if (reinterpret_cast<std::uintptr_t>(rcx) >= 0x20) {
                    // 0x675b5fe..0x675b617  failure path (see below)
                } else {
                    rax += 0x28;
                    sub_e935700(reinterpret_cast<void*>(r8));  // 0x675b5ec  call 0xE935700 (rcx=r8)
                }
            }
        }
    }

    // 0x675b5f1  mov rax,rsi        ; return this
    // 0x675b5f4  add rsp,0x98
    // 0x675b5fb  pop rsi
    // 0x675b5fc  pop rbp
    // 0x675b5fd  ret
    return thisObj;                   // 0x675b5f1  mov rax,rsi
}

// 0x675b5fe..0x675b617  unreachable failure path (only reachable from the dead flag==1 block):
//   0x675b5fe  mov qword ptr [rsp+0x20],0
//   0x675b607  xor ecx,ecx
//   0x675b609  xor edx,edx
//   0x675b60b  xor r8d,r8d
//   0x675b60e  xor r9d,r9d
//   0x675b611  call qword ptr [0xF9A8C78]   ; indirect call through data slot 0xF9A8C78, args all zero
//   0x675b617  int3
static void failurePath() {
    using FailureHandler = void (__cdecl*)(std::uint64_t, std::uint64_t, std::uint64_t, std::uint64_t);
    FailureHandler handler =
        reinterpret_cast<FailureHandler>(*reinterpret_cast<const std::uintptr_t*>(kFailureHandlerSlot));
    handler(0, 0, 0, 0);               // 0x675b611  call qword ptr [0xF9A8C78]  (RCX=RDX=R8=R9=0)
    __debugbreak();                    // 0x675b617  int3
}

LIFT_FN(sub_675b550, "sub_675b550", 0x675B550, ::native::sub_675b550, nullptr);

} // namespace native
