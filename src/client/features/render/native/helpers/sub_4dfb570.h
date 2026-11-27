#pragma once
// LIFT 0x4dfb570 size 0x120 1.26.62.01 resolve loaded texture
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Layout of every object this function walks, taken from the instruction operands
// of [0x4dfb570, 0x4dfb690) in Minecraft.Windows.exe 1.26.62.01.

// The texture handle (rdx on entry, "a1" in the rdis annotations): one pointer at +0x00.
#pragma pack(push, 1)
struct sub_4dfb570_handle {
    void* object;                 // +0x00: 0x4dfb57a R (mov rax,[rdx])
};
#pragma pack(pop)

// handle->object: the resource pointer lives at +0x18.
#pragma pack(push, 1)
struct sub_4dfb570_object {
    std::uint8_t pad0x00[0x18];
    void* resource;               // +0x18: 0x4dfb582 R (mov rsi,[rax+0x18])
};
#pragma pack(pop)

// The resource: a shared reference (pointer + control block) at +0x00 and the
// load-state byte at +0x68 (2 = loaded).
#pragma pack(push, 1)
struct sub_4dfb570_resource {
    void* shared_ptr;             // +0x00: 0x4dfb591 R, 0x4dfb5d2 R, 0x4dfb605 R
    void* shared_ctrl;            // +0x08: 0x4dfb5de R, 0x4dfb5eb R
    std::uint8_t pad0x10[0x58];   // +0x10..+0x67
    std::uint8_t state;           // +0x68: 0x4dfb58b R (cmp byte ptr [rsi+0x68],2)
};
#pragma pack(pop)

// The texture the shared reference points at: use counter at +0x10, flags at +0x12.
#pragma pack(push, 1)
struct sub_4dfb570_texture {
    std::uint8_t pad0x00[0x10];
    std::uint16_t use;            // +0x10: 0x4dfb5be W (lock inc), 0x4dfb5da R
    std::uint8_t flags;           // +0x12: 0x4dfb5c3 R (test al,1)
};
#pragma pack(pop)

// The shared-reference control block: vtable at +0x00, strong count at +0x08,
// weak count at +0x0C.
#pragma pack(push, 1)
struct sub_4dfb570_control {
    void** vtable;                // +0x00: 0x4dfb61e R, 0x4dfb639 R
    std::uint32_t uses;           // +0x08: 0x4dfb5e7 W (lock inc), 0x4dfb618 W (lock dec)
    std::uint32_t weaks;          // +0x0C: 0x4dfb633 W (lock dec)
};
#pragma pack(pop)

// The 16-byte value written through rcx (the hidden return slot, also returned in rax).
#pragma pack(push, 1)
struct sub_4dfb570_out {
    void* ptr;                    // +0x00: 0x4dfb5ce W, 0x4dfb608 W
    void* ctrl;                   // +0x08: 0x4dfb60b R, 0x4dfb60f W
};
#pragma pack(pop)

static_assert(offsetof(sub_4dfb570_handle, object) == 0x00, "handle+0x00 object");
static_assert(sizeof(sub_4dfb570_handle) == 0x08, "handle size");
static_assert(offsetof(sub_4dfb570_object, resource) == 0x18, "object+0x18 resource");
static_assert(offsetof(sub_4dfb570_resource, shared_ptr) == 0x00, "resource+0x00 shared_ptr");
static_assert(offsetof(sub_4dfb570_resource, shared_ctrl) == 0x08, "resource+0x08 shared_ctrl");
static_assert(offsetof(sub_4dfb570_resource, state) == 0x68, "resource+0x68 state");
static_assert(offsetof(sub_4dfb570_texture, use) == 0x10, "texture+0x10 use");
static_assert(offsetof(sub_4dfb570_texture, flags) == 0x12, "texture+0x12 flags");
static_assert(offsetof(sub_4dfb570_control, vtable) == 0x00, "control+0x00 vtable");
static_assert(offsetof(sub_4dfb570_control, uses) == 0x08, "control+0x08 uses");
static_assert(offsetof(sub_4dfb570_control, weaks) == 0x0C, "control+0x0C weaks");
static_assert(offsetof(sub_4dfb570_out, ptr) == 0x00, "out+0x00 ptr");
static_assert(offsetof(sub_4dfb570_out, ctrl) == 0x08, "out+0x08 ctrl");
static_assert(sizeof(sub_4dfb570_out) == 0x10, "out size");

// x64 Microsoft ABI: rcx = hidden return slot (the 16-byte value, also returned in
// rax), rdx = the texture handle. No other arguments are read.
sub_4dfb570_out* sub_4dfb570(sub_4dfb570_out* out, const sub_4dfb570_handle* h);

} // namespace native::helpers
