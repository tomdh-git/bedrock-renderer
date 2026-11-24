#pragma once
#include <cstddef>
#include <cstdint>

// LIFT 0xe81d850 size 0x1cd 1.26.62.01 sub_e81d850
//
// RendererContextD3D12-family "submit RTX override" step (d3d12 region, depth 2,
// status D0; docs/data/native_functions.tsv row 0xe81d850). Marks one meta slot of
// an inline ring-buffer table ready (flag=1, stamp=<global>), issues two virtual
// submit calls on the device object at arg1->[0x30], then under a mutex at this+0x7850
// drains the ring: for each ready slot it decrements the output slot's refcount and
// copies the source pair into the output slot, advancing the cursor modulo capacity.
//
// `this` (rcx) field offsets touched [V: 0xe81d850..0xe81da1c]:
//   +0x08    OutEntry[] output ring base (inline, 0x18-byte slots)
//   +0x1820  MetaEntry[] ring table base (inline, 0x18-byte slots)
//   +0x7820  void*  p7820  (call2 arg6)
//   +0x7828  void*  p7828  (call1/call2 arg2)
//   +0x7830  SrcEntry* p7830  source ring (0x10-byte slots)
//   +0x7838  uint32  capacity (M)  ring modulus
//   +0x783C  uint32  writeIdx (A)
//   +0x7844  uint32  cursor   (c)  ring read cursor
//   +0x7850  uint8[0x4C] lock  mutex passed to sub_eec59f0/sub_eec5a10
//   +0x789C  uint32  recursion guard (0x7FFFFFFF = invalid / use-after-shutdown)

namespace native {

// IAT forwarders reached by direct call (hard rule 69: a jmp-to-another-function
// thunk is a normal lift item, forward-declared here and called like any lifted
// function). sub_eec59f0 = _Mtx_lock (jmp [0xF9A75A8], returns eax tested for 0),
// sub_eec5a10 = _Mtx_unlock (jmp [0xF9A75B8], return unused),
// sub_eec5a00 = _Throw_Cpp_error (jmp [0xF9A72F0], takes ecx=5/6, original follows
// it with int3). Their import targets are loader-resolved.
extern "C" int32_t sub_eec59f0(void* mtx);   // 0xeec59f0: jmp qword ptr [0xF9A75A8]
extern "C" void   sub_eec5a10(void* mtx);    // 0xeec5a10: jmp qword ptr [0xF9A75B8]
extern "C" void   sub_eec5a00(uint32_t code); // 0xeec5a00: jmp qword ptr [0xF9A72F0]

} // namespace native

namespace native::d3d12 {

// One 0x18-byte metadata ring slot at this+0x1820.
struct MetaEntry {
    int32_t  sub;    // +0x00  index into the output ring (OutEntry[])
    int32_t  val;    // +0x04  copied to OutEntry.val
    uint64_t stamp;  // +0x08  stamped (== *(G2+0x28)) and gate-checked (> *(G2+0x30))
    uint8_t  flag;   // +0x10  1 = ready (set to 1 for the submitted slot)
    uint8_t  pad[7]; // +0x11
};

// One 0x18-byte output ring slot at this+0x08.
struct OutEntry {
    uint64_t a;      // +0x00  <- SrcEntry.a
    uint64_t b;      // +0x08  <- SrcEntry.b
    int32_t  count;  // +0x10  decremented
    int32_t  val;    // +0x14  <- MetaEntry.val
};

// One 0x10-byte source ring slot at *this+0x7830.
struct SrcEntry {
    uint64_t a;      // +0x00
    uint64_t b;      // +0x08
};

// `this`: only the bytes sub_e81d850 touches are named; the rest is padding.
struct S81d850 {
    uint8_t     pad_0x00[0x08];     // +0x00
    uint8_t     out_ring;           // +0x08  OutEntry[] base (inline)
    uint8_t     pad_0x09[0x1817];   // +0x09
    uint8_t     meta_ring;          // +0x1820 MetaEntry[] base (inline)
    uint8_t     pad_0x1821[0x5FFF]; // +0x1821
    void*       p7820;              // +0x7820
    void*       p7828;              // +0x7828
    SrcEntry*   p7830;              // +0x7830
    uint32_t    capacity;           // +0x7838  (M)
    uint32_t    writeIdx;           // +0x783C  (A)
    uint32_t    pad_0x7840;         // +0x7840
    uint32_t    cursor;             // +0x7844  (c)
    uint8_t     pad_0x7848[0x08];   // +0x7848
    uint8_t     lock;               // +0x7850  mutex
    uint8_t     pad_0x7851[0x4B];   // +0x7851
    uint32_t    guard;              // +0x789C
};

static_assert(sizeof(void*) == 8, "sub_e81d850: 64-bit target");
static_assert(sizeof(MetaEntry) == 0x18, "sub_e81d850: MetaEntry size");
static_assert(offsetof(MetaEntry, sub)  == 0x00, "sub_e81d850: MetaEntry.sub @ +0x00");
static_assert(offsetof(MetaEntry, val)  == 0x04, "sub_e81d850: MetaEntry.val @ +0x04");
static_assert(offsetof(MetaEntry, stamp) == 0x08, "sub_e81d850: MetaEntry.stamp @ +0x08");
static_assert(offsetof(MetaEntry, flag) == 0x10, "sub_e81d850: MetaEntry.flag @ +0x10");
static_assert(sizeof(OutEntry) == 0x18, "sub_e81d850: OutEntry size");
static_assert(offsetof(OutEntry, a) == 0x00, "sub_e81d850: OutEntry.a @ +0x00");
static_assert(offsetof(OutEntry, b) == 0x08, "sub_e81d850: OutEntry.b @ +0x08");
static_assert(offsetof(OutEntry, count) == 0x10, "sub_e81d850: OutEntry.count @ +0x10");
static_assert(offsetof(OutEntry, val) == 0x14, "sub_e81d850: OutEntry.val @ +0x14");
static_assert(sizeof(SrcEntry) == 0x10, "sub_e81d850: SrcEntry size");
static_assert(offsetof(SrcEntry, a) == 0x00, "sub_e81d850: SrcEntry.a @ +0x00");
static_assert(offsetof(SrcEntry, b) == 0x08, "sub_e81d850: SrcEntry.b @ +0x08");
static_assert(offsetof(S81d850, out_ring) == 0x08, "sub_e81d850: out_ring @ +0x08");
static_assert(offsetof(S81d850, meta_ring) == 0x1820, "sub_e81d850: meta_ring @ +0x1820");
static_assert(offsetof(S81d850, p7820) == 0x7820, "sub_e81d850: p7820 @ +0x7820");
static_assert(offsetof(S81d850, p7828) == 0x7828, "sub_e81d850: p7828 @ +0x7828");
static_assert(offsetof(S81d850, p7830) == 0x7830, "sub_e81d850: p7830 @ +0x7830");
static_assert(offsetof(S81d850, capacity) == 0x7838, "sub_e81d850: capacity @ +0x7838");
static_assert(offsetof(S81d850, writeIdx) == 0x783C, "sub_e81d850: writeIdx @ +0x783C");
static_assert(offsetof(S81d850, cursor) == 0x7844, "sub_e81d850: cursor @ +0x7844");
static_assert(offsetof(S81d850, lock) == 0x7850, "sub_e81d850: lock @ +0x7850");
static_assert(offsetof(S81d850, guard) == 0x789C, "sub_e81d850: guard @ +0x789C");

} // namespace native::d3d12

// Exact x64 Microsoft ABI signature: __fastcall, this in rcx, a1 in rdx, index in r8d,
// no return value (tail-jumps to sub_eec5a10 which returns void). C linkage.
extern "C" void sub_e81d850(void* rcx, void* rdx, uint32_t r8d);