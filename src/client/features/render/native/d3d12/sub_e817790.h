#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Layout recovered from the disassembly of 0xe817790 (size 0xe8, 1.26.62.01).
// This is RendererContextD3D12 virtual slot 40 ("register a frame-buffer handle"):
// given a 16-bit handle (key) and a 32-bit value it records the handle in a 128-bit
// "seen" bitmap + an append-only key list, stores the value in the per-key record, and
// (if a connection object exists for that handle) notifies it through three guarded
// virtual calls. Every offset below is an instruction [reg+off] seen in the listing [V].

// Per-key record, 8 bytes, one per handle. self->perKey[key] lives at self + 0x20 + key*8:
//   +0x00  u32 v0   ([rax+r9*8+0x20] = value)
//   +0x04  u32 v1   ([rax+r9*8+0x24] = value)
struct E817790PerKey {
    std::uint32_t v0;  // +0x00
    std::uint32_t v1;  // +0x04
};
static_assert(sizeof(E817790PerKey) == 0x08, "e817790: per-key record is 8 bytes (key*8 stride)");
static_assert(offsetof(E817790PerKey, v0) == 0x00, "e817790: perKey::v0 at +0x00");
static_assert(offsetof(E817790PerKey, v1) == 0x04, "e817790: perKey::v1 at +0x04");

// The registry object (self / rcx). Only the fields 0xe817790 touches are named:
//   +0x00  void*   slots       self->slots                 (mov rsi,[rax])
//   +0x08  u16     count       append cursor for keyList   (movzx ecx,word[rax+8] / mov [rax+8],cx)
//   +0x10  u64[2]  present     128-bit seen bitmap         (mov r11,[rax+r10*8+0x10])
//   +0x20  PerKey[128] perKey   per-handle value pair       (mov [rax+r9*8+0x20/0x24],r8d)
//   +0x420 u16[128] keyList     appended handle list        (mov [rax+rcx*2+0x420],dx)
struct E817790Registry {
    void*            slots;         // +0x000
    std::uint16_t    count;         // +0x008
    std::uint8_t     pad0[0x10 - 0x0A]; // +0x00A..0x010
    std::uint64_t    present[2];    // +0x010  128-bit "handle already seen" bitmap
    E817790PerKey    perKey[128];   // +0x020  128 * 8 = 0x400  (-> 0x420)
    std::uint16_t    keyList[128];  // +0x420  128 * 2 = 0x100  (-> 0x520)
};
static_assert(offsetof(E817790Registry, slots) == 0x000, "e817790: slots at +0x00");
static_assert(offsetof(E817790Registry, count) == 0x008, "e817790: count at +0x08");
static_assert(offsetof(E817790Registry, present) == 0x010, "e817790: present at +0x10");
static_assert(offsetof(E817790Registry, perKey) == 0x020, "e817790: perKey at +0x20");
static_assert(offsetof(E817790Registry, keyList) == 0x420, "e817790: keyList at +0x420");
static_assert(offsetof(E817790Registry, perKey[1]) == 0x028, "e817790: perKey stride 8");
static_assert(sizeof(E817790Registry) == 0x520, "e817790: registry footprint is 0x520 bytes");

// One element of self->slots: an array of 0x68-byte records, one per handle.
//   +0x18  void* connection   ([slots + key*0x68 + 0x18]); when non-null it receives the 3 calls.
struct E817790Slot {
    std::uint8_t pad0[0x18];
    void*        connection;        // +0x18
    std::uint8_t pad1[0x68 - 0x20];
};
static_assert(sizeof(E817790Slot) == 0x68, "e817790: slots record stride 0x68 (imul r9,0x68)");
static_assert(offsetof(E817790Slot, connection) == 0x18, "e817790: connection at +0x18");

// Read-only data / globals referenced by the function [V].
static constexpr std::uintptr_t kGblCookie     = 0x1230A0C0u; // mov rcx,[0x1230A0C0]  (/GS stack cookie)
static constexpr std::uintptr_t kData_f4ed2c0  = 0xF4ED2C0u;  // lea r8,[0xF4ED2C0]   (Close arg2)
static constexpr std::uintptr_t kGuardSlot     = 0xF99FFA0u;  // call qword ptr [0xF99FFA0] (jmp rax thunk)

// vtable byte offsets read before each guarded call (slot index = offset / 8) [V].
static constexpr std::uintptr_t kVslotNotify = 0x120u; // 0xe81780c mov rax,[rax+0x120] -> slot 36 (returns a byte)
static constexpr std::uintptr_t kVslotClose  = 0x048u; // 0xe817823 mov rax,[rax+0x48]  -> slot 9  (Close)
static constexpr std::uintptr_t kVslotRelease= 0x010u; // 0xe817846 mov rax,[rax+0x10]  -> slot 2  (Release)
static_assert(kVslotNotify / 8 == 0x24u, "e817790: vtable slot 0x120 = index 0x24 (36)");
static_assert(kVslotClose  / 8 == 0x09u, "e817790: vtable slot 0x48 = index 9");
static_assert(kVslotRelease/ 8 == 0x02u, "e817790: vtable slot 0x10 = index 2");

// Record stride inside self->slots (imul rax,r9,0x68).
static constexpr std::size_t kSlotStride = 0x68u;

// x64 Microsoft ABI: rcx = self (registry), rdx = key (u16 handle), r8 = value (u32).
// Return: void (rax is only the /GS cookie at the ret; never a meaningful result) [V].
extern "C" void sub_e817790(void* self, std::uint16_t key, std::uint32_t value);

} // namespace native