#pragma once

#include <cstddef>
#include <cstdint>

namespace native {

// Layout of the game's bgfx::EncoderImpl as accessed by 0xbc60d10
// (discard/reset, size 0x1fc bytes). Every offset below is read or written by
// that function [V]; field roles are inferred from the written values [I] and
// the struct is byte-identical to the game object, so the lifted function can
// write through these offsets directly.

struct EncoderImpl {
    std::uint8_t m_pad00[0x40];                    // +0x00..+0x3F untouched
    std::uint64_t m_field40;                       // +0x40 = 0xFFFFFFFF00000000
    std::uint8_t  m_pad48[0x60 - 0x48];            // +0x48..+0x5F untouched
    std::uint64_t m_field60;                       // +0x60 = 0x01000050000001F (rdis prints the imm64 with the leading zero stripped)
    std::uint64_t m_field68;                       // +0x68 = 0
    alignas(16) std::uint8_t m_field70[16];        // +0x70 = 0 (16 bytes)
    alignas(16) std::uint8_t m_field80[16];        // +0x80 = copy of the rodata constant at [0xF08EF70] (16 bytes)
    std::uint64_t m_field90;                       // +0x90 = 0x100000000
    std::uint64_t m_field98;                       // +0x98 = 0x0001FFFF00000000
    std::uint16_t m_fieldA0;                       // +0xA0 = 0xFFFF
    std::uint8_t  m_fieldA2;                       // +0xA2 = 0
    std::uint16_t m_fieldA3;                       // +0xA3 = 0xFF00 (byte +0xA4 becomes 0xFF)
    std::uint8_t  m_padA4[0xA8 - 0xA4];            // +0xA4..+0xA7 untouched
    std::uint32_t m_fieldA8;                       // +0xA8 = 0x7FFFFFFF
    std::uint64_t m_fieldAC;                       // +0xAC = 0
    std::uint64_t m_fieldB4;                       // +0xB4 = 0xFFFFFFFFFFFFFFFF
    std::uint64_t m_fieldC0;                       // +0xC0 = 0
    std::uint32_t m_fieldC8;                       // 0xC8 = 0
    std::uint16_t m_fieldCC;                       // +0xCC = 0xFFFF
    std::uint8_t  m_padCE[0xD0 - 0xCE];            // +0xCE..+0xCF untouched
    std::uint64_t m_fieldD0;                       // +0xD0 = 0
    std::uint32_t m_fieldD8;                       // +0xD8 = 0
    std::uint32_t m_fieldDC;                       // +0xDC = 0xFFFF0000
    std::uint16_t m_fieldE0;                       // +0xE0 = 0
    std::uint8_t  m_fieldE2;                       // +0xE2 = 0xFF
    std::uint8_t  m_fieldE3;                       // +0xE3 = 0
    std::uint8_t  m_padE4[0x680 - 0xE4];           // +0xE4..+0x67F untouched
    void* m_sideTable;                             // +0x680
    std::uint8_t m_bindDirty;                      // +0x688 = 1
    std::uint8_t m_pad689[0x6AD - 0x689];          // +0x689..+0x6AC untouched
    std::uint8_t m_discard;                        // +0x6AD = 0
};

// One side-table entry: +0x00 pointer freed through the allocator interface,
// the rest of the 16-byte entry is zeroed when the entry is released.
struct SideTableEntry {
    void* m_ptr;                                   // +0x00
    std::uint64_t m_reserved;                      // +0x08
};

// Side table: 65 entries of 0x10 bytes at +0x00, then a u32 count at +0x410.
struct SideTable {
    SideTableEntry m_entry[65];                    // +0x00..+0x40F
    std::uint32_t m_count;                         // +0x410
};

// One binding at m_bind + i*0x28 (i = 0..32). Only the listed fields are
// written; everything else in the 0x28-byte record is left untouched.
// m_f13 (word at +0x13) overlaps m_f14 (dword at +0x14) on byte +0x14, and
// m_f1c (dword at +0x1C) overlaps m_f1e (word at +0x1E) on bytes +0x1E/+0x1F;
// the write order in the source follows the disassembly exactly.
struct Binding {
    std::uint32_t m_f00;                           // +0x00 = 0
    std::uint8_t  m_pad04[0x0A - 0x04];            // +0x04..+0x09 untouched
    std::uint8_t  m_f0a;                           // +0x0A = 0
    std::uint8_t  m_pad0b[0x0C - 0x0B];            // +0x0B untouched
    std::uint32_t m_f0c;                           // +0x0C = 0xFFFFFFFF
    std::uint8_t  m_pad10[0x13 - 0x10];            // +0x10..+0x12 untouched
    std::uint16_t m_f13;                           // +0x13 = 0xFFFF
    std::uint32_t m_f14;                           // +0x14 = 0 (except on the last binding)
    std::uint8_t  m_pad18[0x1C - 0x18];            // +0x18..+0x1B untouched
    std::uint32_t m_f1c;                           // +0x1C = 0xFFFFFFFF
    std::uint16_t m_f1e;                           // +0x1E = 0xFFFF
    std::uint8_t  m_pad20[0x27 - 0x20];            // +0x20..+0x26 untouched
    std::uint8_t  m_f27;                           // +0x27 = 0
};

// Layout constants used by 0xbc60d10 [V].
static constexpr std::size_t kBindingBase = 0x140;          // m_bind array
static constexpr std::size_t kBindingStride = 0x28;         // bytes per binding
static constexpr std::uint32_t kBindingCount = 33;          // rax runs 0x167..0x667 step 0x28
static constexpr std::size_t kSideTableEntryCount = 65;     // 0x410 / 0x10 entries
static constexpr std::size_t kSideTableBytes = 0x410;       // bytes zeroed in the side table
static constexpr std::size_t kSideTableCountOffset = 0x410; // u32 count after the entries

// 0xbc60d10, size 0x1fc: void bgfx::EncoderImpl::discard(EncoderImpl* this);
// x64 Microsoft ABI: rcx = this, returns void.
extern "C" void EncoderImpl_discard(EncoderImpl* encoder);

} // namespace native
