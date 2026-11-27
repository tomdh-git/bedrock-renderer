// LIFT 0xe87c6d0 size 0x9d 1.26.62.01 sub_e87c6d0
#include "sub_e87c6d0.h"

#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc75c30.h"

#include <cstdint>
#include <intrin.h>

namespace native { namespace d3d12 {

void sub_e87c6d0(void* a0)
{
    // 0xe87c6d0..0xe87c6e3: push rbp; push rsi; sub rsp,0x38; lea rbp,[rsp+0x30];
    // mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE  (frame setup + sentinel store;
    // nothing observable escapes this frame)
    ArgLayout* a = reinterpret_cast<ArgLayout*>(a0);   // 0xe87c6e3  mov rsi,rcx

    // 0xe87c6e6  cmp byte ptr [rcx+0x34],1
    // 0xe87c6ea  jne short 0xE87C6FD
    if (a->field34 == 1) {                  // 0xe87c6e6..0xe87c6ea
        // 0xe87c6ec  movzx edx,word ptr [rsi+0x32]
        // 0xe87c6f0  mov rcx,[0x12AE1748]    ; [data_12ae1748]
        // 0xe87c6f7  call 0xBC75C30          ; -> sub_bc75c30 (lift set)
        // 0xe87c6fc  nop
        std::uintptr_t ctxv = *reinterpret_cast<std::uintptr_t*>(0x12AE1748);
        ::native::sub_bc75c30(reinterpret_cast<::native::Ctx*>(ctxv),
                              static_cast<std::uint16_t>(a->field32));
    }
    // 0xe87c6fd  mov rax,[rsi+0x20]
    if (a->field20 >= 0x10ULL) {            // 0xe87c6fd..0xe87c705 (rax >= 0x10 falls through)
        // 0xe87c701  cmp rax,0x10
        // 0xe87c705  jb short 0xE87C738      (rax < 0x10 skips straight to the reset below)
        // 0xe87c707  mov rcx,[rsi+8]
        void* ptr = a->field08;
        // 0xe87c70b  lea rdx,[rax+1]
        std::uint64_t rdx = a->field20 + 1;
        // 0xe87c70f  cmp rdx,0x1000
        // 0xe87c716  jb short 0xE87C733
        if (rdx < 0x1000ULL) {              // 0xe87c70f..0xe87c718
            // 0xe87c733  call 0xE935700      ; rcx = ptr, rdx = rax + 1 (lift set)
            ::native::sub_e935700(ptr);
        } else {
            // 0xe87c718  mov r8,[rcx-8]
            std::uint64_t r8 = *reinterpret_cast<std::uint64_t*>(
                reinterpret_cast<char*>(ptr) - 8);
            // 0xe87c71c  add rcx,0xFFFFFFFFFFFFFFF8
            // 0xe87c720  sub rcx,r8
            std::uint64_t rcx = (reinterpret_cast<std::uintptr_t>(ptr) - 8) - r8;
            // 0xe87c723  cmp rcx,0x20
            // 0xe87c727  jae short 0xE87C753
            if (rcx >= 0x20ULL) {           // 0xe87c723..0xe87c729
                // 0xe87c753  mov qword ptr [rsp+0x20],0   (5th stack argument home slot)
                // 0xe87c75c  xor ecx,ecx
                // 0xe87c75e  xor edx,edx
                // 0xe87c760  xor r8d,r8d
                // 0xe87c763  xor r9d,r9d
                // 0xe87c766  call qword ptr [0xF9A8C78]   ; loader-resolved data slot -> FailFn
                // 0xe87c76c  int3                         ; function ends here
                std::uintptr_t failv = *reinterpret_cast<std::uintptr_t*>(0xF9A8C78);
                using FailFn = void (*)(void*, void*, void*, void*, void*);
                FailFn fail = reinterpret_cast<FailFn>(failv);
                fail(nullptr, nullptr, nullptr, nullptr, nullptr);
                __debugbreak();
                return;
            }
            // 0xe87c729  add rax,0x28
            // 0xe87c72d  mov rdx,rax
            // 0xe87c730  mov rcx,r8
            rdx = a->field20 + 0x28ULL;
            // 0xe87c733  call 0xE935700      ; rcx = r8, rdx = rax + 0x28 (lift set)
            ::native::sub_e935700(reinterpret_cast<void*>(r8));
        }
    }
    // 0xe87c738  mov qword ptr [rsi+0x18],0
    // 0xe87c740  mov qword ptr [rsi+0x20],0xF
    // 0xe87c748  mov byte ptr [rsi+8],0
    // 0xe87c74c  add rsp,0x38
    // 0xe87c750  pop rsi
    // 0xe87c751  pop rbp
    // 0xe87c752  ret
    a->field18 = 0;
    a->field20 = 0xFULL;
    a->field08 = nullptr;
}

#if 0
// Verbatim instructions of 0xe87c6d0 (range [0xe87c6d0, 0xe87c76d)), copied
// from rdis.exe output; every call is quoted here as a plain line.
0xe87c6d0  push rbp
0xe87c6d1  push rsi
0xe87c6d2  sub rsp,0x38
0xe87c6d6  lea rbp,[rsp+0x30]
0xe87c6db  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
0xe87c6e3  mov rsi,rcx
0xe87c6e6  cmp byte ptr [rcx+0x34],1
0xe87c6ea  jne short 0xE87C6FD
0xe87c6ec  movzx edx,word ptr [rsi+0x32]
0xe87c6f0  mov rcx,[0x12AE1748]
0xe87c6f7  call 0xBC75C30
0xe87c6fc  nop
0xe87c6fd  mov rax,[rsi+0x20]
0xe87c701  cmp rax,0x10
0xe87c705  jb short 0xE87C738
0xe87c707  mov rcx,[rsi+8]
0xe87c70b  lea rdx,[rax+1]
0xe87c70f  cmp rdx,0x1000
0xe87c716  jb short 0xE87C733
0xe87c718  mov r8,[rcx-8]
0xe87c71c  add rcx,0xFFFFFFFFFFFFFFF8
0xe87c720  sub rcx,r8
0xe87c723  cmp rcx,0x20
0xe87c727  jae short 0xE87C753
0xe87c729  add rax,0x28
0xe87c72d  mov rdx,rax
0xe87c730  mov rcx,r8
0xe87c733  call 0xE935700
0xe87c738  mov qword ptr [rsi+0x18],0
0xe87c740  mov qword ptr [rsi+0x20],0xF
0xe87c748  mov byte ptr [rsi+8],0
0xe87c74c  add rsp,0x38
0xe87c750  pop rsi
0xe87c751  pop rbp
0xe87c752  ret
0xe87c753  mov qword ptr [rsp+0x20],0
0xe87c75c  xor ecx,ecx
0xe87c75e  xor edx,edx
0xe87c760  xor r8d,r8d
0xe87c763  xor r9d,r9d
0xe87c766  call qword ptr [0xF9A8C78]
0xe87c76c  int3
#endif

static_assert(offsetof(ArgLayout, field08) == 0x08, "sub_e87c6d0 ArgLayout+0x08 field08");
static_assert(offsetof(ArgLayout, field18) == 0x18, "sub_e87c6d0 ArgLayout+0x18 field18");
static_assert(offsetof(ArgLayout, field20) == 0x20, "sub_e87c6d0 ArgLayout+0x20 field20");
static_assert(offsetof(ArgLayout, field32) == 0x32, "sub_e87c6d0 ArgLayout+0x32 field32");
static_assert(offsetof(ArgLayout, field34) == 0x34, "sub_e87c6d0 ArgLayout+0x34 field34");
static_assert(sizeof(ArgLayout) == 0x38, "sub_e87c6d0 ArgLayout size");

LIFT_FN(sub_e87c6d0, "sub_e87c6d0", 0xe87c6d0, sub_e87c6d0, nullptr);

} } // namespace native::d3d12
