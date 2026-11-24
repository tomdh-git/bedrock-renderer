#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Lift callees of sub_0xe81d660. All three are 6-byte `jmp qword ptr [...]` import
// thunks (loader-resolved) classified `lift` in docs/data/native_boundary.tsv and
// docs/data/native_functions.tsv (roots, D0). They are forward-declared here with the
// ABI observed at the call sites and called through their native symbol; each is lifted
// by its own unit and links at the milestone gate.
//   sub_eec59f0  `jmp qword ptr [0xF9A75A8]`  (rcx=lock) -> int   (0xe81d693, nonzero = fail)
//   sub_eec5a00  `jmp qword ptr [0xF9A72F0]`  (ecx=code)           (0xe81d7f5 code 5, 0xe81d809 code 6)
//                The original has no `ret` on either path and pads with int3 at 0xe81d80e,
//                so this callee does not return (fatal); marked [[noreturn]].
//   sub_eec5a10  `jmp qword ptr [0xF9A75B8]`  (rcx=lock)          (0xe81d7d8, matching release)
int sub_eec59f0(void* lock);
[[noreturn]] void sub_eec5a00(int code);
void sub_eec5a10(void* lock);

} // namespace native

namespace native::d3d12 {

// LIFT 0xe81d660 size 0x1af 1.26.62.01 D3D12 submit RTX override
//
// Records one draw/dispatch slot into a per-frame ring (3 cursors) of a D3D12 submit
// context, bumps a per-stream counter, then issues a CFG-guarded virtual call on an
// object owned by the caller (a1) and advances the ring tail. Returns the ring tail
// value that was current on entry.
//
//   rcx = a0 = this  (RendererContextD3D12*-like per-job submit context)
//   rdx = a1 = owner (struct with a pointer at +0x30 whose vtable slot +0x1A8 is called)
//   r8d = a2 (u32) slot/stream selector, stored into counter[a2] and record.field0
//   r9d = a3 (u32) stored into record.field4
//   return eax = a0->[0x783C] (ring tail read at entry)
//
// Every offset below is an instruction [reg+off] seen in [0xe81d660, 0xe81d80f) [V].

// ---- this (a0) fields [V] ----
constexpr std::size_t kLockOff     = 0x7850; // submit lock object (lea r13,[rcx+0x7850], 0xe81d689)
constexpr std::size_t kModOff      = 0x7838; // u32 ring modulus / size           (R 0xe81d6b0, 0xe81d79e)
constexpr std::size_t kTailOff     = 0x783C; // u32 ring tail (returned, advanced) (R 0xe81d6b7,0xe81d7a4; W 0xe81d7ce)
constexpr std::size_t kCursor0Off  = 0x7840; // u32 cursor0                        (R 0xe81d6c8,0xe81d798; W 0xe81d745)
constexpr std::size_t kCursor1Off  = 0x7844; // u32 cursor1                        (R 0xe81d6c1; W 0xe81d739)
constexpr std::size_t kSentinelOff = 0x789C; // u32 abort sentinel                  (R 0xe81d6a0; W 0xe81d7fa)
constexpr std::size_t kVcallArgOff = 0x7828; // u64 2nd arg of the guarded vcall    (R 0xe81d77a)
constexpr std::size_t kCounterBase = 0x18;   // u32 counter[a2] array base          (W 0xe81d752)
constexpr std::size_t kCounterStride = 24;   // a2*3*8                             (0xe81d74e)
constexpr std::size_t kSlotBase    = 0x1820; // per-slot record array base          (W 0xe81d75a)
constexpr std::size_t kSlotStride  = 24;     // tail*3*8                            (0xe81d756)

// ---- a1 (owner) fields [V] ----
constexpr std::size_t kVcallObjOff = 0x30;   // object whose vtable is called       (R 0xe81d776 [rbx+0x30])

// ---- record (per-slot) sub-fields [V] ----
constexpr std::size_t kSlotField0Off = 0x00; // u32 a2   (0x1820)                   (W 0xe81d75a)
constexpr std::size_t kSlotField4Off = 0x04; // u32 a3   (0x1824)                   (W 0xe81d76a)
constexpr std::size_t kSlotFlagOff   = 0x10; // u8  zero (0x1830)                   (W 0xe81d762)

// ---- constants [V] ----
constexpr std::size_t   kVtableSlot   = 0x1A8;     // vtable byte offset called       (0xe81d784)
constexpr std::uintptr_t kGuardSlot  = 0xF99FFA0u; // data slot = sub_eea6040 (jmp rax thunk) (0xe81d791)
constexpr std::uint32_t kAbortSentinel = 0x7FFFFFFFu; // "aborted" marker             (0xe81d6a0)
constexpr std::uint32_t kAbortedValue  = 0x7FFFFFFEu; // value written when aborting   (0xe81d7fa)

static_assert(kTailOff == kModOff + 4, "e81d660: mod then tail");
static_assert(kCursor0Off == kTailOff + 4, "e81d660: tail then cursor0");
static_assert(kCursor1Off == kCursor0Off + 4, "e81d660: cursor0 then cursor1");
static_assert(kSentinelOff > kCursor1Off, "e81d660: sentinel follows the cursor block");
static_assert(kSlotField4Off == kSlotField0Off + 4, "e81d660: record a2 then a3");
static_assert(kSlotFlagOff == 0x10 && kSlotFlagOff < kSlotStride, "e81d660: flag inside the record");
static_assert(kCounterStride == kSlotStride, "e81d660: both per-index arrays stride 24");
static_assert(kSlotBase > kCounterBase, "e81d660: slot array above the counter array");

// sub_0xe81d660: record one submit slot and fire the guarded virtual call.
// rcx=this, rdx=a1 (owner), r8d=a2, r9d=a3; returns the ring tail value read at entry.
std::uint32_t sub_e81d660(void* a0, void* a1, std::uint32_t a2, std::uint32_t a3);

} // namespace native::d3d12