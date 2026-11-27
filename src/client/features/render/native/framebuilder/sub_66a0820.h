#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_66a0820 (0x66a0820, size 0x84, 1.26.62.01, "group insert effect").
//
//   0x66a0820  push rsi
//   0x66a0821  sub rsp,0x20
//   0x66a0825  mov rax,[rcx]                                 ; R a0+0x0 (ptr0)
//   0x66a0828  test rax,rax
//   0x66a082b  je short 0x66a0841
//   0x66a082d  cmp byte ptr [rax],1                          ; R *ptr0+0x0 (tag)
//   0x66a0830  jne short 0x66a0841
//   0x66a0832  mov rcx,[rcx+0x10]                            ; R a0+0x10 (ptr10)
//   0x66a0836  mov eax,0xC0
//   0x66a083b  add rax,[rcx+0x18]                            ; R *ptr10+0x18
//   0x66a083f  jmp short 0x66a0869
//   0x66a0841  mov ecx,[0x129FB168]                          ; R data_129FB168 (counter)
//   0x66a0847  mov eax,[0x128767C8]                          ; R data_128767C8 (tls_index)
//   0x66a084d  mov rdx,gs:[0x58]                             ; R TEB
//   0x66a0856  mov rdx,[rdx+rax*8]                           ; R TEB slot array
//   0x66a085a  lea rax,[0x129FB158]                          ; R data_129FB158 (slow path return)
//   0x66a0861  cmp ecx,[rdx+4]                               ; compare counter vs slot_array[1]
//   0x66a0867  jg short 0x66a086f
//   0x66a0869  add rsp,0x20
//   0x66a086d  pop rsi
//   0x66a086e  ret
//   0x66a086f  mov rsi,rax
//   0x66a0872  lea rcx,[0x129FB168]
//   0x66a0879  call 0xE938CB0                                ; sub_e938cb0 (os boundary)
//   0x66a087e  cmp dword ptr [0x129FB168],0xFFFFFFFF
//   0x66a0885  jne short 0x66a089f
//   0x66a0887  lea rcx,[0x675DEA0]
//   0x66a088e  call 0xE935740                                ; sub_e935740 (os boundary)
//   0x66a0893  lea rcx,[0x129FB168]
//   0x66a089a  call 0xE938D70                                ; sub_e938d70 (os boundary)
//   0x66a089f  mov rax,rsi
//   0x66a08a2  jmp short 0x66a0869
//
// x64 Microsoft ABI: RCX = a0 (input object), RAX = return pointer.
// Reads a0+0x0, a0+0x10; conditionally reads *a0+0x0 (byte), *a0+0x10+0x18.
// Slow path reads globals 0x129FB168, 0x128767C8, 0x129FB158, 0x675DEA0,
// TEB at gs:[0x58], and per-thread slot array.
// Calls three os-class boundary functions: sub_e938cb0, sub_e935740, sub_e938d70.
// No null guard or SEH in the original (none added here).

// Offsets within the input object (a0) [V 0x66a0820..0x66a083f]
static constexpr std::size_t kObjOffsetPtr0 = 0x0;   // a0+0x0: void* ptr0
static constexpr std::size_t kObjOffsetPtr10 = 0x10; // a0+0x10: void* ptr10

// Offsets within *ptr0 [V 0x66a082d]
static constexpr std::size_t kPtr0OffsetTag = 0x0;   // *ptr0+0x0: uint8_t tag (must be 1)

// Offsets within *ptr10 [V 0x66a083b]
static constexpr std::size_t kPtr10OffsetField18 = 0x18; // *ptr10+0x18: uintptr_t value added to 0xC0

// Global data addresses (RVAs from 1.26.62.01 preferred base) [V disassembly]
static constexpr std::uintptr_t kGlobalCounter     = 0x129FB168; // uint32_t
static constexpr std::uintptr_t kGlobalTlsIndex    = 0x128767C8; // uint32_t
static constexpr std::uintptr_t kGlobalSlowRetPtr  = 0x129FB158; // void*
static constexpr std::uintptr_t kGlobalCallbackPtr = 0x675DEA0;  // void* (function pointer)

// Layout assertions for every struct offset the function touches [V from disassembly]
// Input object (a0): reads at +0x0 (ptr0) and +0x10 (ptr10)
struct Obj {
    void* ptr0;        // +0x0
    uint8_t pad[0x8];  // +0x8..0xF (gap, 8 bytes)
    void* ptr10;       // +0x10
};
static_assert(offsetof(Obj, ptr0) == kObjOffsetPtr0,
              "sub_66a0820: Obj+0x0 is read as ptr0");
static_assert(offsetof(Obj, ptr10) == kObjOffsetPtr10,
              "sub_66a0820: Obj+0x10 is read as ptr10");
static_assert(sizeof(Obj) >= 0x18,
              "sub_66a0820: Obj must be at least 0x18 bytes");

// *ptr0 pointee: reads byte tag at +0x0
struct Ptr0 {
    uint8_t tag; // +0x0
};
static_assert(offsetof(Ptr0, tag) == kPtr0OffsetTag,
              "sub_66a0820: *ptr0+0x0 is read as tag byte");

// *ptr10 pointee: reads uintptr_t at +0x18
struct Ptr10 {
    uint8_t pad[0x18];   // +0x0..0x17
    std::uintptr_t f18;  // +0x18
};
static_assert(offsetof(Ptr10, f18) == kPtr10OffsetField18,
              "sub_66a0820: *ptr10+0x18 is read as field18");
static_assert(sizeof(Ptr10) >= 0x20,
              "sub_66a0820: *ptr10 must be at least 0x20 bytes");

namespace native {

// Exact x64 Microsoft ABI mirror of the original: RCX = a0, RAX = return value.
void* sub_66a0820(void* a0);

} // namespace native