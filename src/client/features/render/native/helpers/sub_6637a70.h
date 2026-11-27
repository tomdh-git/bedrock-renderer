#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// sub_6637a70 (0x6637a70, size 0xf6, 1.26.62.01): BgfxFrameBuilder::endFrame helper.
//
//   0x6637a70  push rsi; push rdi; sub rsp,0x28; mov rsi,rcx   (self = rcx)
//   0x6637a79  mov rcx,[0x1233E1A8]                            ; global context
//   0x6637a80  mov rax,[rcx]                                   ; rax = [global]
//   0x6637a83  mov rax,[rax+8]                                 ; rax = [rax+8] (dead, overwritten by call)
//   0x6637a87  mov edx,0xB0                                    ; size
//   0x6637a8c  call qword ptr [0xF99FFA0]                    ; vendor alloc thunk (global, 0xB0)
//   0x6637a92  test rax,rax                                    ; if alloc == 0 goto fallback
//   0x6637a9b..0x6637b51   init the allocated object
//   0x6637b51..0x6637b66   fallback: call sub_9bc830(0xB0), then init
//   0x6637b40  mov [rsi],rcx                                   ; self[0] = object_ptr
//   0x6637b43  mov [rsi+8],rax                                 ; self[8] = base_ptr
//   0x6637b47  mov rax,rsi                                     ; return self
//
// x64 Microsoft ABI: RCX = self (output pointer pair), return RAX = self.
// No null guards and no SEH beyond the original's own test/jz.

// Output pointer pair written at self+0x00 and self+0x08.
struct SelfOut {
    void* object_ptr;   // +0x00 [W] object pointer (alloc+0x10)
    void* base_ptr;     // +0x08 [W] allocation base pointer (alloc)
};

// Allocation header at alloc+0x00 / alloc+0x08.
struct AllocHeader {
    void* vtable;      // +0x00 [W] vtable pointer (read from data 0xF121010)
    std::uint64_t tag; // +0x08 [W] 0x100000001
};

// Initialized object at alloc+0x10 (sizeof 0xA0).
#pragma pack(push, 1)
struct AllocObject {
    double f0x00;               // +0x00 [W] rax+0x10: 1.0 (from data 0xF2BDD80)
    double f0x08;               // +0x08 [W] rax+0x18: 0.00078125 (from data 0xF2BDD80+8)
    std::uint8_t pad0x10[4];    // +0x10 [W] rax+0x20..0x23: zeroed
    float f0x14;                // +0x14 [W] rax+0x24: bit pattern 0x42055555
    double f0x18;               // +0x18 [W] rax+0x28: 0.1 (from data 0xF2BDD90)
    double f0x20;               // +0x20 [W] rax+0x30: 1.0 (from data 0xF2BDD90+8)
    std::uint8_t f0x28;         // +0x28 [W] rax+0x38: 1
    std::uint8_t pad0x29[7];    // +0x29 [W] rax+0x39..0x3f: zeroed
    double f0x30;               // +0x30 [W] rax+0x40: 0.1
    std::uint8_t pad0x38[8];    // +0x38 [W] rax+0x48..0x4f: zeroed
    std::uint8_t pad0x40[8];    // +0x40 [W] rax+0x50..0x57: zeroed
    double f0x48;               // +0x48 [W] rax+0x58: 0.1
    std::uint8_t pad0x50[8];    // +0x50 [W] rax+0x60..0x67: zeroed
    std::uint8_t pad0x58[8];    // +0x58 [W] rax+0x68..0x6f: zeroed
    double f0x60;               // +0x60 [W] rax+0x70: 0.1
    std::uint8_t pad0x68[8];    // +0x68 [W] rax+0x78..0x7f: zeroed
    std::uint8_t pad0x70[8];    // +0x70 [W] rax+0x80..0x87: zeroed
    double f0x78;               // +0x78 [W] rax+0x88: bit pattern 0x4040AAAAA0000000
    std::uint8_t pad0x80[0x10]; // +0x80 [W] rax+0x90..0x9f: zeroed
    std::uint8_t pad0x90[0x10]; // +0x90 [W] rax+0xa0..0xaf: zeroed
};
#pragma pack(pop)

static_assert(offsetof(SelfOut, object_ptr) == 0x0, "sub_6637a70: self+0x0");
static_assert(offsetof(SelfOut, base_ptr) == 0x8, "sub_6637a70: self+0x8");
static_assert(sizeof(SelfOut) >= 0x10, "sub_6637a70: self sizeof lower bound");

static_assert(offsetof(AllocHeader, vtable) == 0x0, "sub_6637a70: alloc+0x0");
static_assert(offsetof(AllocHeader, tag) == 0x8, "sub_6637a70: alloc+0x8");
static_assert(sizeof(AllocHeader) >= 0x10, "sub_6637a70: alloc header sizeof lower bound");

static_assert(offsetof(AllocObject, f0x00) == 0x00, "sub_6637a70: obj+0x00");
static_assert(offsetof(AllocObject, f0x08) == 0x08, "sub_6637a70: obj+0x08");
static_assert(offsetof(AllocObject, pad0x10) == 0x10, "sub_6637a70: obj+0x10");
static_assert(offsetof(AllocObject, f0x14) == 0x14, "sub_6637a70: obj+0x14");
static_assert(offsetof(AllocObject, f0x18) == 0x18, "sub_6637a70: obj+0x18");
static_assert(offsetof(AllocObject, f0x20) == 0x20, "sub_6637a70: obj+0x20");
static_assert(offsetof(AllocObject, f0x28) == 0x28, "sub_6637a70: obj+0x28");
static_assert(offsetof(AllocObject, pad0x29) == 0x29, "sub_6637a70: obj+0x29");
static_assert(offsetof(AllocObject, f0x30) == 0x30, "sub_6637a70: obj+0x30");
static_assert(offsetof(AllocObject, pad0x38) == 0x38, "sub_6637a70: obj+0x38");
static_assert(offsetof(AllocObject, pad0x40) == 0x40, "sub_6637a70: obj+0x40");
static_assert(offsetof(AllocObject, f0x48) == 0x48, "sub_6637a70: obj+0x48");
static_assert(offsetof(AllocObject, pad0x50) == 0x50, "sub_6637a70: obj+0x50");
static_assert(offsetof(AllocObject, pad0x58) == 0x58, "sub_6637a70: obj+0x58");
static_assert(offsetof(AllocObject, f0x60) == 0x60, "sub_6637a70: obj+0x60");
static_assert(offsetof(AllocObject, pad0x68) == 0x68, "sub_6637a70: obj+0x68");
static_assert(offsetof(AllocObject, pad0x70) == 0x70, "sub_6637a70: obj+0x70");
static_assert(offsetof(AllocObject, f0x78) == 0x78, "sub_6637a70: obj+0x78");
static_assert(offsetof(AllocObject, pad0x80) == 0x80, "sub_6637a70: obj+0x80");
static_assert(offsetof(AllocObject, pad0x90) == 0x90, "sub_6637a70: obj+0x90");
static_assert(sizeof(AllocObject) == 0xA0, "sub_6637a70: object size 0xA0");

// Signature (x64 Microsoft ABI).
uintptr_t sub_6637a70(void* self);

} // namespace native::helpers
