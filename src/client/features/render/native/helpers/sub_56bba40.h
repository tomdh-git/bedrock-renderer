#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed layouts for sub_56bba40, taken from the instruction operands of
// [0x56bba40, 0x56bbb59), Minecraft Windows 1.26.62.01. Offsets and widths are fixed
// by the disassembly. The structs are packed so each field sits at its observed offset;
// sizeof is a lower bound because the real objects may carry alignment padding.

#pragma pack(push, 1)

// a0 (rcx): slot holding the destination object pointer.
struct sub_56bba40_rcx {
    void* sink;                                          // +0x00  R   (0x56bba49, 0x56bba6d, 0x56bba92)
};

// rdx: while rdx still holds a1 it addresses the source pair pointer; after
// `mov rdx,[rcx]` it addresses the destination object (0x56bba6d..0x56bba95).
struct sub_56bba40_rdx {
    void* object;                                        // +0x00  R/W (0x56bba87 W; a1 slot 0x56bba6a R)
    void* control;                                       // +0x08  W   (0x56bba8e)
    std::uint8_t pad0x10[0x8];                           // +0x10..+0x17
    std::uint8_t state;                                  // +0x18  W   (0x56bba95 via rax = [rcx])
};

// r8: control block, strong reference count incremented on addref.
struct sub_56bba40_r8 {
    std::uint8_t pad0x00[0x8];                           // +0x00..+0x07
    std::uint32_t strong;                                // +0x08  RMW (0x56bba7f lock inc)
};

// rax: source pair at +0x0/+0x8, then aliases the control-block vtable and the
// destination object (the +0x18 byte store at 0x56bba95 uses rax = [rcx]).
struct sub_56bba40_rax {
    void* object;                                        // +0x00  R   (0x56bba84, 0x56bbb06)
    void* control;                                       // +0x08  R   (0x56bba76, 0x56bba8a, 0x56bbaf1)
    std::uint8_t pad0x10[0x8];                           // +0x10..+0x17
    std::uint8_t state;                                  // +0x18  W   (0x56bba95)
};

// rdi: destination object (rdi = *a0).
struct sub_56bba40_rdi {
    void* object;                                        // +0x00  R/W (0x56bbb09 W)
    void* control;                                       // +0x08  R/W (0x56bbaa3 R, 0x56bbb0c R, 0x56bbb10 W)
    std::uint8_t pad0x10[0x8];                           // +0x10..+0x17
    std::uint8_t state;                                  // +0x18  R/W (0x56bba4c R, 0x56bba66 W)
};

// rsi: shared-pointer control block.
struct sub_56bba40_rsi {
    void** vftable;                                      // +0x00  R   (0x56bbab2, 0x56bbad3, 0x56bbb23, 0x56bbb3c)
    std::uint32_t strong;                                // +0x08  RMW (0x56bbaac, 0x56bbb19 lock dec)
    std::uint32_t weak;                                  // +0x0C  RMW (0x56bbacd, 0x56bbb32 lock dec)
};

#pragma pack(pop)

static_assert(offsetof(sub_56bba40_rcx, sink) == 0x0, "sub_0x56bba40 rcx+0x0 field");
static_assert(sizeof(sub_56bba40_rcx) >= 0x8, "sub_0x56bba40 rcx sizeof lower bound");

static_assert(offsetof(sub_56bba40_rdx, object) == 0x0, "sub_0x56bba40 rdx+0x0 field");
static_assert(offsetof(sub_56bba40_rdx, control) == 0x8, "sub_0x56bba40 rdx+0x8 field");
static_assert(offsetof(sub_56bba40_rdx, state) == 0x18, "sub_0x56bba40 rdx+0x18 field");
static_assert(sizeof(sub_56bba40_rdx) >= 0x19, "sub_0x56bba40 rdx sizeof lower bound");

static_assert(offsetof(sub_56bba40_r8, strong) == 0x8, "sub_0x56bba40 r8+0x8 field");
static_assert(sizeof(sub_56bba40_r8) >= 0xc, "sub_0x56bba40 r8 sizeof lower bound");

static_assert(offsetof(sub_56bba40_rax, object) == 0x0, "sub_0x56bba40 rax+0x0 field");
static_assert(offsetof(sub_56bba40_rax, control) == 0x8, "sub_0x56bba40 rax+0x8 field");
static_assert(offsetof(sub_56bba40_rax, state) == 0x18, "sub_0x56bba40 rax+0x18 field");
static_assert(sizeof(sub_56bba40_rax) >= 0x19, "sub_0x56bba40 rax sizeof lower bound");

static_assert(offsetof(sub_56bba40_rdi, object) == 0x0, "sub_0x56bba40 rdi+0x0 field");
static_assert(offsetof(sub_56bba40_rdi, control) == 0x8, "sub_0x56bba40 rdi+0x8 field");
static_assert(offsetof(sub_56bba40_rdi, state) == 0x18, "sub_0x56bba40 rdi+0x18 field");
static_assert(sizeof(sub_56bba40_rdi) >= 0x19, "sub_0x56bba40 rdi sizeof lower bound");

static_assert(offsetof(sub_56bba40_rsi, vftable) == 0x0, "sub_0x56bba40 rsi+0x0 field");
static_assert(offsetof(sub_56bba40_rsi, strong) == 0x8, "sub_0x56bba40 rsi+0x8 field");
static_assert(offsetof(sub_56bba40_rsi, weak) == 0xc, "sub_0x56bba40 rsi+0xc field");
static_assert(sizeof(sub_56bba40_rsi) >= 0x10, "sub_0x56bba40 rsi sizeof lower bound");

// x64 Microsoft ABI: RCX = a0 (destination slot), RDX = a1 (source object);
// no value is produced deliberately, so the return type is void.
void sub_56bba40(void* a0, void* a1);

} // namespace native::helpers
