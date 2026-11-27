// LIFT 0x66a0820 size 0x84 1.26.62.01 sub_66a0820
#include "client/features/render/native/framebuilder/sub_66a0820.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>

namespace native {

// Boundary callees (class os, docs/data/native_boundary.tsv lines 457-459).
// All take a single uintptr_t argument in RCX, return void (RAX ignored).
// Signatures inferred from call sites: RCX = address of global or callback.
native::Boundary<void, std::uintptr_t> sub_e938cb0("sub_e938cb0");
native::Boundary<void, std::uintptr_t> sub_e935740("sub_e935740");
native::Boundary<void, std::uintptr_t> sub_e938d70("sub_e938d70");

// 0x66a0820..0x66a0841: Fast-path type check and compute
void* sub_66a0820(void* a0) {
    // 0x66a0820  push rsi
    // 0x66a0821  sub rsp,0x20
    // 0x66a0825  mov rax,[rcx]        ; R a0+0x0
    void* ptr0 = *reinterpret_cast<void**>(a0);
    // 0x66a0828  test rax,rax
    // 0x66a082b  je short 0x66a0841
    if (ptr0 == nullptr) {
        goto slow_path;
    }
    // 0x66a082d  cmp byte ptr [rax],1 ; R *ptr0+0x0
    // 0x66a0830  jne short 0x66a0841
    if (*reinterpret_cast<uint8_t*>(ptr0) != 1) {
        goto slow_path;
    }

    // 0x66a0832  mov rcx,[rcx+0x10]   ; R a0+0x10
    void* ptr10;
    // 0x66a0836  mov eax,0xC0
    // 0x66a083b  add rax,[rcx+0x18]   ; R *ptr10+0x18
    std::uintptr_t result;
    ptr10 = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(a0) + kObjOffsetPtr10);
    result = 0xC0 + *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<uint8_t*>(ptr10) + kPtr10OffsetField18);
    // 0x66a083f  jmp short 0x66a0869  ; -> epilogue
    return reinterpret_cast<void*>(result);

slow_path:
    // 0x66a0841  mov ecx,[0x129FB168]          ; R data_129FB168
    std::uint32_t counter = *reinterpret_cast<std::uint32_t*>(kGlobalCounter);
    // 0x66a0847  mov eax,[0x128767C8]          ; R data_128767C8
    std::uint32_t tls_index = *reinterpret_cast<std::uint32_t*>(kGlobalTlsIndex);
    // 0x66a04d  mov rdx,gs:[0x58]             ; R TEB
    // 0x66a056  mov rdx,[rdx+rax*8]           ; R TEB slot array
    std::uintptr_t teb = __readgsqword(0x58);
    std::uintptr_t* slot_array = *reinterpret_cast<std::uintptr_t**>(teb + tls_index * 8);
    // 0x66a05a  lea rax,[0x129FB158]          ; R data_129FB158 (address)
    void* slow_ret = reinterpret_cast<void*>(kGlobalSlowRetPtr);
    // 0x66a061  cmp ecx,[rdx+4]               ; compare counter vs slot_array[1]
    // 0x66a067  jg short 0x66a06f
    if (counter > *reinterpret_cast<std::uint32_t*>(slot_array + 1)) {
        goto error_path;
    }

    // 0x66a069  add rsp,0x20
    // 0x66a06d  pop rsi
    // 0x66a06e  ret
    return slow_ret;

error_path:
    // 0x66a06f  mov rsi,rax                   ; save slow_ret
    void* saved_ret = slow_ret;
    // 0x66a072  lea rcx,[0x129FB168]
    // 0x66a079  call 0xE938CB0                ; sub_e938cb0
    sub_e938cb0(kGlobalCounter);
    // 0x66a07e  cmp dword ptr [0x129FB168],0xFFFFFFFF
    // 0x66a085  jne short 0x66a09f
    if (*reinterpret_cast<std::uint32_t*>(kGlobalCounter) != 0xFFFFFFFFu) {
        goto return_saved;
    }

    // 0x66a087  lea rcx,[0x675DEA0]
    // 0x66a08e  call 0xE935740                ; sub_e935740
    sub_e935740(kGlobalCallbackPtr);
    // 0x66a093  lea rcx,[0x129FB168]
    // 0x66a09a  call 0xE938D70                ; sub_e938d70
    sub_e938d70(kGlobalCounter);

return_saved:
    // 0x66a09f  mov rax,rsi
    // 0x66a0a2  jmp short 0x66a069         ; -> epilogue
    return saved_ret;
}

// Footprint: the function writes no memory directly (all writes are via boundary callees).
// The only observable state changes are through the three os boundary calls.
// For V2 differential verification, we declare an empty footprint because the lifted
// function itself performs no writes; the boundary calls are recorded/replayed separately.
// However, the original *does* read globals and TEB. The footprint mechanism snapshots
// regions before/after; since we don't write them, an empty footprint is correct.
// (If the boundary wrappers are recorded, their effects are compared via the tape.)
static native::Footprint sub_66a0820Footprint(void* /*a0*/) {
    return {}; // no direct writes by this function
}

// Verbatim instructions of the function (matches `rdis dis 0x66a0820 0x84` from the exe,
// machine-checked with tools/sigs/verify_oc.py):
#if 0
0x66a0820  push rsi
0x66a0821  sub rsp,0x20
0x66a0825  mov rax,[rcx]
0x66a0828  test rax,rax
0x66a082b  je short 0x66a0841
0x66a082d  cmp byte ptr [rax],1
0x66a0830  jne short 0x66a0841
0x66a0832  mov rcx,[rcx+0x10]
0x66a0836  mov eax,0xC0
0x66a083b  add rax,[rcx+0x18]
0x66a083f  jmp short 0x66a0869
0x66a0841  mov ecx,[0x129FB168]
0x66a0847  mov eax,[0x128767C8]
0x66a084d  mov rdx,gs:[0x58]
0x66a0856  mov rdx,[rdx+rax*8]
0x66a085a  lea rax,[0x129FB158]
0x66a0861  cmp ecx,[rdx+4]
0x66a0867  jg short 0x66a086f
0x66a0869  add rsp,0x20
0x66a086d  pop rsi
0x66a086e  ret
0x66a086f  mov rsi,rax
0x66a0872  lea rcx,[0x129FB168]
0x66a0879  call 0xE938CB0
0x66a087e  cmp dword ptr [0x129FB168],0xFFFFFFFF
0x66a0885  jne short 0x66a089f
0x66a0887  lea rcx,[0x675DEA0]
0x66a088e  call 0xE935740
0x66a0893  lea rcx,[0x129FB168]
0x66a089a  call 0xE938D70
0x66a089f  mov rax,rsi
0x66a08a2  jmp short 0x66a0869
#endif

LIFT_FN(sub_66a0820, "sub_66a0820", 0x66a0820, sub_66a0820, &sub_66a0820Footprint);

} // namespace native