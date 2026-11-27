// LIFT 0x56ae910 size 0x79 1.26.62.01 sub_56ae910
#include "sub_56ae910.h"

namespace native {

// Lifted body of sub_56ae910 (Item group visitor).
// Body span [0x56ae910, 0x56ae989), size 0x79, 1.26.62.01.
//
// Control flow follows the original exactly:
//   0x56ae910  push rsi
//   0x56ae911  sub rsp,0x30
//   0x56ae915  cmp byte ptr [rcx+0x40],1       ; if flag != 1, skip
//   0x56ae919  jne short 0x56AE969             ; -> epilogue
//   0x56ae91b  mov rax,[rcx]                   ; vtable = *a0
//   0x56ae91e  test rax,rax
//   0x56ae921  je short 0x56AE969              ; if vtable == 0, skip
//   0x56ae923  mov rdx,[rcx+0x10]              ; rdx = a0->some_ptr
//   0x56ae927  sub rdx,rax                     ; rdx -= vtable
//   0x56ae92a  cmp rdx,0x1000
//   0x56ae931  jb short 0x56AE950              ; if rdx < 0x1000, skip heap check
//   0x56ae933  mov r8,[rax-8]                  ; r8 = heap header at vtable-8
//   0x56ae937  add rax,0xFFFFFFFFFFFFFFF8      ; rax = vtable - 8
//   0x56ae93b  sub rax,r8                      ; rax = vtable - 8 - heap_header
//   0x56ae93e  cmp rax,0x20
//   0x56ae942  jae short 0x56AE96F             ; if rax >= 0x20, heap corrupt -> watson
//   0x56ae944  mov rsi,rcx                     ; rsi = a0
//   0x56ae947  or rdx,0x27                     ; rdx |= 0x27 (dead write)
//   0x56ae94b  mov rax,r8                      ; rax = r8
//   0x56ae94e  jmp short 0x56AE953             ; -> call sub_e935700(r8)
//   0x56ae950  mov rsi,rcx                     ; rsi = a0 (rdx < 0x1000 path)
//   0x56ae953  mov rcx,rax                     ; rcx = argument for sub_e935700
//   0x56ae956  call 0xE935700                  ; sub_e935700(rcx)
//   0x56ae95b  xorps xmm0,xmm0                 ; xmm0 = 0
//   0x56ae95e  movups [rsi],xmm0               ; *a0 = 0 (16 bytes)
//   0x56ae961  mov qword ptr [rsi+0x10],0      ; a0->some_ptr = 0 (8 bytes)
//   0x56ae969  add rsp,0x30                    ; epilogue
//   0x56ae96d  pop rsi
//   0x56ae96e  ret
//   0x56ae96f  mov qword ptr [rsp+0x20],0      ; watson arg 5 (reserved) = 0
//   0x56ae978  xor ecx,ecx                     ; expression = nullptr
//   0x56ae97a  xor edx,edx                     ; function = nullptr
//   0x56ae97c  xor r8d,r8d                     ; file = nullptr
//   0x56ae97f  xor r9d,r9d                     ; line = 0
//   0x56ae982  call qword ptr [0xF9A8C78]      ; _invoke_watson(nullptr,nullptr,nullptr,0,0)
//   0x56ae988  int3                            ; noreturn pad (unreachable)
//
void* sub_56ae910(void* a0)
{
    // 0x56ae910..0x56ae989
    static_assert(sizeof(void*) == 8, "sub_56ae910: x64 pointer-sized fields are 8 bytes");
    // 0x56ae910..0x56ae919
    if (reinterpret_cast<uint8_t*>(a0)[Sub56ae910Layout::kOffFlag] != 1) {
        // 0x56ae969  add rsp,0x30 / pop rsi / ret  (rax is entry value, undefined)
        return nullptr;
    }

    // 0x56ae91b..0x56ae921
    void* vtable = reinterpret_cast<void**>(a0)[0];
    if (vtable == nullptr) {
        // rax == 0 -> ret
        return nullptr;
    }

    // 0x56ae923..0x56ae931
    uintptr_t rdx = reinterpret_cast<uintptr_t>(reinterpret_cast<void**>(a0)[2])
                  - reinterpret_cast<uintptr_t>(vtable);

    void* result = nullptr;

    if (rdx >= 0x1000) {
        // 0x56ae933..0x56ae942
        uintptr_t r8 = *reinterpret_cast<uintptr_t*>(reinterpret_cast<uint8_t*>(vtable) - 8);
        uintptr_t rax_computed = reinterpret_cast<uintptr_t>(vtable) - 8 - r8;

        if (rax_computed >= 0x20) {
            // 0x56ae96f..0x56ae989
            auto watson_fn = reinterpret_cast<void (*)(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, unsigned int)>(
                *reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + kRvaWatsonSlot));
            watson_fn(nullptr, nullptr, nullptr, 0, 0);
            // noreturn: control never continues past this call (0x56ae988 int3 is unreachable pad)
        }

        // 0x56ae944..0x56ae94e
        rdx |= 0x27;  // 0x56ae947  or rdx,0x27 (dead write, not read afterward)

        // 0x56ae953..0x56ae956
        result = sub_e935700(reinterpret_cast<void*>(r8));
    } else {
        // 0x56ae950..0x56ae950  (mov rsi,rcx; rsi = a0, implicit via direct use of a0 below)

        // 0x56ae953..0x56ae956
        result = sub_e935700(vtable);
    }

    // 0x56ae95b..0x56ae961
    {
        uint64_t* p = reinterpret_cast<uint64_t*>(a0);
        p[0] = 0;   // 0x56ae95e  movups [rsi],xmm0  (16-byte zero store at +0x00)
        p[1] = 0;
        p[2] = 0;   // 0x56ae961  mov qword ptr [rsi+0x10],0  (8-byte zero store at +0x10)
    }

    // 0x56ae969..0x56ae96e
    return result;
}

// Verbatim instruction quotes for verify_oc (plain lines, two spaces after address).
#if 0
0x56ae910  push rsi
0x56ae911  sub rsp,0x30
0x56ae915  cmp byte ptr [rcx+0x40],1
0x56ae919  jne short 0x56AE969
0x56ae91b  mov rax,[rcx]
0x56ae91e  test rax,rax
0x56ae921  je short 0x56AE969
0x56ae923  mov rdx,[rcx+0x10]
0x56ae927  sub rdx,rax
0x56ae92a  cmp rdx,0x1000
0x56ae931  jb short 0x56AE950
0x56ae933  mov r8,[rax-8]
0x56ae937  add rax,0xFFFFFFFFFFFFFFF8
0x56ae93b  sub rax,r8
0x56ae93e  cmp rax,0x20
0x56ae942  jae short 0x56AE96F
0x56ae944  mov rsi,rcx
0x56ae947  or rdx,0x27
0x56ae94b  mov rax,r8
0x56ae94e  jmp short 0x56AE953
0x56ae950  mov rsi,rcx
0x56ae953  mov rcx,rax
0x56ae956  call 0xE935700
0x56ae95b  xorps xmm0,xmm0
0x56ae95e  movups [rsi],xmm0
0x56ae961  mov qword ptr [rsi+0x10],0
0x56ae969  add rsp,0x30
0x56ae96d  pop rsi
0x56ae96e  ret
0x56ae96f  mov qword ptr [rsp+0x20],0
0x56ae978  xor ecx,ecx
0x56ae97a  xor edx,edx
0x56ae97c  xor r8d,r8d
0x56ae97f  xor r9d,r9d
0x56ae982  call qword ptr [0xF9A8C78]
0x56ae988  int3
#endif

LIFT_FN(sub_56ae910, "sub_56ae910", 0x56AE910, sub_56ae910, nullptr);

} // namespace native
