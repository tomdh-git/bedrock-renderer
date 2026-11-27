#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_6639850 (0x6639850, size 0x6d, 1.26.62.01, "BgfxFrameBuilder slot 76").
//
// Reversed from the exe listing (rdis dis 0x6639850 0x6d); every offset below is a read
// performed by an instruction of the function, cited by address.
//
//   0x663985c  mov rax,[rcx]           ; R self+0x0 (vtable pointer)
//   0x663985f  mov rax,[rax+0x228]     ; R vtable+0x228 (slot-228 function pointer)
//   0x6639866  call qword ptr [0xF99FFA0]  ; -> sub_eea6040 [V boundary: vendor,
//       docs/data/native_boundary.tsv: "0xeea6040 vendor thunk via data slot 0xF99FFA0
//       (loader-resolved)"]. sub_eea6040 body [V]: `0xEEA6040  jmp rax` — tail-calls RAX
//       (= vtable+0x228 target) with RCX = self; result returns in AL.
//   0x6639870  mov rax,[rdi+0x278]     ; R self+0x278 (attachment pointer)
//   0x6639882  mov rcx,[rdi+0x280]     ; R self+0x280 (refObject pointer)
//   0x663988e  lock inc dword ptr [rcx+8]  ; R/W *(refObject+0x8) += 1 atomic refcount
//
// Behavior: OutPair* sub_6639850(BgfxFrameBuilder* self, OutPair* out):
//   uint8_t r = <vtable+0x228 target>(self);                 // via sub_eea6040 trampoline
//   if (r == 0 || self->attachment0x278 == nullptr) { zero 16B at out; return out; }
//   zero 16B at out;
//   if (self->refObject0x280 != nullptr) atomic++ dword at self->refObject0x280 + 0x8;
//   out = { self->attachment0x278, self->refObject0x280 };   // refObject may be nullptr
//   return out;
// Same reads (self+0x0, vtable+0x228, self+0x278, self+0x280, *(refObject)+0x8),
// same writes (out 16B, *(refObject)+0x8), same calls in the same order (one,
// sub_eea6040 through data slot 0xF99FFA0), same return (RAX = out). No null guard,
// no SEH; branches mirror the original jccs exactly.
//
// x64 Microsoft ABI: RCX = self (BgfxFrameBuilder*), RDX = out (OutPair*), return RAX = out.
//
static constexpr std::size_t kBgfxFrameBuilderOffsetAttachment0x278 = 0x278;
static constexpr std::size_t kBgfxFrameBuilderOffsetRefObject0x280 = 0x280;
static constexpr std::size_t kVtableSlotByteOffset0x228 = 0x228;
static constexpr std::size_t kRefCountOffset0x8 = 0x8;
static constexpr std::size_t kOutPairSize = 0x10;

// Layout mirrors what the function touches. Only offsets used by the function are members.
struct OutPair {
    void* attachment0x0;  // W out+0x0 at 0x66398ac; zeroed at 0x663987f/0x66398a5
    void* refObject0x8;   // W out+0x8 at 0x66398af
};
static_assert(offsetof(OutPair, attachment0x0) == 0,
              "sub_6639850: out+0x0 is the attachment field (W, 0x66398ac)");
static_assert(offsetof(OutPair, refObject0x8) == 8,
              "sub_6639850: out+0x8 is the refObject field (W, 0x66398af)");
static_assert(sizeof(OutPair) == kOutPairSize,
              "sub_6639850: the out object is 16 bytes (W at 0x663987f and 0x66398a5)");

struct BgfxFrameBuilder {
    std::uint8_t pad0x00[0x278];
    void* attachment0x278;  // pointer object, read at 0x6639870 and reloaded at 0x6639892
    void* refObject0x280;   // pointer object, read at 0x6639882 and reloaded at 0x6639899
};
static_assert(offsetof(BgfxFrameBuilder, attachment0x278) == kBgfxFrameBuilderOffsetAttachment0x278,
              "sub_6639850: self+0x278 is the attachment field (R, 0x6639870/0x6639892)");
static_assert(offsetof(BgfxFrameBuilder, refObject0x280) == kBgfxFrameBuilderOffsetRefObject0x280,
              "sub_6639850: self+0x280 is the refObject field (R, 0x6639882/0x6639899)");

struct RefCountedObject {
    std::uint8_t pad0x00[8];
    std::uint32_t refCount0x8;  // atomic dword incremented at 0x663988e lock inc [rcx+8]
};
static_assert(offsetof(RefCountedObject, refCount0x8) == kRefCountOffset0x8,
              "sub_6639850: refObject+0x8 is the refcount dword (R/W, 0x663988e)");

namespace native {

// Exact x64 Microsoft ABI mirror of the original function.
OutPair* sub_6639850(BgfxFrameBuilder* self, OutPair* out);

} // namespace native
