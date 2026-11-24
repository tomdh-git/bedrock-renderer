#pragma once

#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_bc2e890 (0xbc2e890, size 0x1de, 1.26.62.01, region bgfx): moves one render object
// (dest in rcx/a0) out of another (src in rdx/a1), field by field, clearing the source
// fields it consumes. The original type name is not available from the disassembly, so
// the layout is declared member by member at the offsets the body uses; members are
// named f<offset>. Every offset is [V] from a [reg+disp] operand in [0xbc2e890, 0xbc2ea6e).
// No semantics beyond the observed read/write are assigned.
// Calls two lift callees (own lift units, class `lift` in docs/data/native_boundary.tsv):
//   0xbc2e99b  call 0xE869FF0  rcx = dest + 0x98, rdx = src + 0x98; return value unused
//   0xbc2e9cc  call 0x5669770   rcx = dest + 0x118, rdx = src + 0x118; return value unused
// They are forward-declared here (namespace native) and called from the .cpp; each callee
// is lifted by its own unit and links at the milestone gate.

namespace native {
void sub_e869ff0(uint8_t* dest, uint8_t* src);
void sub_5669770(uint8_t* dest, uint8_t* src);
} // namespace native

namespace native::bgfx {

struct Bc2e890Object {
    uint64_t f00;                    // +0x00  u64: read src, written dest
    uint64_t f08;                    // +0x08  u64: read src, written dest; src+0x08..0x18 then zeroed
    uint64_t f10;                    // +0x10  u64: read src, written dest
    std::byte f18[16];               // +0x18  16 bytes: written 0 in dest
    uint64_t f28;                    // +0x28  u64: written 0 in dest
    uint8_t f30;                     // +0x30  u8:  read src, written dest
    std::byte pad31[7];              // +0x31  padding to +0x38
    uint64_t f38;                    // +0x38  u64: low half of the +0x38 16-byte copy
    uint64_t f40;                    // +0x40  u64: read as part of the +0x38 copy; then zeroed in src
    std::byte f48[16];               // +0x48  16 bytes: read src, written dest; src then zeroed
    uint64_t f58;                    // +0x58  u64: read src, written dest
    uint64_t f60;                    // +0x60  u64: access kind depends on src+0x70 (switch)
    uint64_t f68;                    // +0x68  u64: pointer, refcounted when switch value == 3
    uint8_t f70;                     // +0x70  u8:  switch value; dest prewritten 0xFF, then the value (only when src+0x70 <= 3)
    std::byte pad71[7];              // +0x71  padding to +0x78
    std::byte f78[16];               // +0x78  16 bytes: read src, written dest
    uint64_t f88;                    // +0x88  u64: read src, written dest
    uint64_t f90;                    // +0x90  u64: read src, written dest
    std::byte f98[0x18];             // +0x98  0x18 bytes: passed to sub_e869ff0(dest + 0x98, src + 0x98)
    uint64_t f110;                   // +0x110 u64: read src (return value), written dest, zeroed in src
    std::byte pad118[0x124];         // +0x118 passed to sub_5669770(dest + 0x118, src + 0x118); ends at 0x23C
    std::byte f23c[16];              // +0x23C 16 bytes: read src, written dest
    uint32_t f24c;                   // +0x24C u32:  read src, written dest
    uint8_t f250;                    // +0x250 u8:   read src, written dest
    std::byte pad251[3];             // +0x251 padding to +0x254
    float f254;                      // +0x254 f32: read src, written dest
    float f258;                      // +0x258 f32: read src, written dest
    float f25c;                      // +0x25C f32: read src, written dest
    float f260;                      // +0x260 f32: read src, written dest
    std::byte f264[16];              // +0x264 16 bytes: read src, written dest
    std::byte f274[16];              // +0x274 16 bytes: read src, written dest (overlaps f283 at 0x283)
    std::byte f283[16];              // +0x283 16 bytes: read src, written dest (last field touched)
};

static_assert(offsetof(Bc2e890Object, f00) == 0x000, "bc2e890: layout +0x000");
static_assert(offsetof(Bc2e890Object, f08) == 0x008, "bc2e890: layout +0x008");
static_assert(offsetof(Bc2e890Object, f10) == 0x010, "bc2e890: layout +0x010");
static_assert(offsetof(Bc2e890Object, f28) == 0x028, "bc2e890: layout +0x028");
static_assert(offsetof(Bc2e890Object, f30) == 0x030, "bc2e890: layout +0x030");
static_assert(offsetof(Bc2e890Object, f38) == 0x038, "bc2e890: layout +0x038");
static_assert(offsetof(Bc2e890Object, f40) == 0x040, "bc2e890: layout +0x040");
static_assert(offsetof(Bc2e890Object, f48) == 0x048, "bc2e890: layout +0x048");
static_assert(offsetof(Bc2e890Object, f58) == 0x058, "bc2e890: layout +0x058");
static_assert(offsetof(Bc2e890Object, f60) == 0x060, "bc2e890: layout +0x060");
static_assert(offsetof(Bc2e890Object, f68) == 0x068, "bc2e890: layout +0x068");
static_assert(offsetof(Bc2e890Object, f70) == 0x070, "bc2e890: layout +0x070");
static_assert(offsetof(Bc2e890Object, f88) == 0x088, "bc2e890: layout +0x088");
static_assert(offsetof(Bc2e890Object, f90) == 0x090, "bc2e890: layout +0x090");
static_assert(offsetof(Bc2e890Object, f98) == 0x098, "bc2e890: layout +0x098");
static_assert(offsetof(Bc2e890Object, f110) == 0x110, "bc2e890: layout +0x110");
static_assert(offsetof(Bc2e890Object, f23c) == 0x23c, "bc2e890: layout +0x23c");
static_assert(offsetof(Bc2e890Object, f24c) == 0x24c, "bc2e890: layout +0x24c");
static_assert(offsetof(Bc2e890Object, f250) == 0x250, "bc2e890: layout +0x250");
static_assert(offsetof(Bc2e890Object, f254) == 0x254, "bc2e890: layout +0x254");
static_assert(offsetof(Bc2e890Object, f258) == 0x258, "bc2e890: layout +0x258");
static_assert(offsetof(Bc2e890Object, f25c) == 0x25c, "bc2e890: layout +0x25c");
static_assert(offsetof(Bc2e890Object, f260) == 0x260, "bc2e890: layout +0x260");
static_assert(offsetof(Bc2e890Object, f264) == 0x264, "bc2e890: layout +0x264");
static_assert(offsetof(Bc2e890Object, f274) == 0x274, "bc2e890: layout +0x274");
static_assert(offsetof(Bc2e890Object, f283) == 0x283, "bc2e890: layout +0x283");

static constexpr uint32_t kBc2e890TouchedEnd = 0x293; // f283[16] ends at 0x293 [V]
static_assert(kBc2e890TouchedEnd == 0x293, "bc2e890: last touched byte");

// Footprint for the differential harness: every byte the body reads or writes,
// for both arguments. The callees (sub_e869ff0 at +0x98, sub_5669770 at +0x118)
// are lift units and declare their own footprints.
static native::Footprint sub_bc2e890_footprint(Bc2e890Object* dest, Bc2e890Object* src) {
    return { {dest, sizeof(Bc2e890Object)}, {src, sizeof(Bc2e890Object)} };
}

uint64_t sub_bc2e890(Bc2e890Object* dest, Bc2e890Object* src);

} // namespace native::bgfx
