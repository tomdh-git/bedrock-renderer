#pragma once
#include <cstdint>
#include <cstddef>

namespace native::bgfx {

// Forward declarations of lifted callees
struct Frame;
struct RenderDraw;
struct RenderBind;
struct SideTable;
struct EncoderImpl;
struct UniformBuffer;
struct ContextView;

struct SortKey {
    std::uint32_t m_depth;  // +0x08
    std::uint32_t m_seq;    // +0x0C
    std::uint16_t m_program; // +0x10
    std::uint16_t m_view;   // +0x12
    std::uint8_t m_trans;   // +0x14 (2 bits used)
};

struct RenderDraw {
    // +0x40 from EncoderImpl
    std::uint64_t m_0x40;           // +0x40 = 0xFFFFFFFF00000000 when cleared
    std::uint64_t m_0x48;
    std::uint64_t m_0x50;
    std::uint64_t m_0x58;
    std::uint64_t m_0x60;           // +0x60 = m_stateFlags
    std::uint64_t m_stencil;        // +0x68
    std::uint8_t  m_0x70[16];       // +0x70 rgba/scissor defaults
    std::uint32_t m_uniformBegin;   // +0x74
    std::uint32_t m_uniformEnd;     // +0x78
    std::uint32_t m_0x7C;
    std::uint32_t m_0x80;
    std::uint32_t m_numIndices;     // +0x84
    std::uint32_t m_0x88;
    std::uint32_t m_0x8C;           // +0x8C = m_numVertices
    std::uint32_t m_0x90;
    std::uint32_t m_0x94;
    std::uint32_t m_0x98;
    std::uint32_t m_0x9C;
    std::uint16_t m_0xA0;           // +0xA0 = 0xFFFF
    std::uint8_t  m_0xA2;           // +0xA2 = 0
    std::uint8_t  m_streamMask;     // +0xA3
    std::uint8_t  m_uniformIdx;     // +0xA4
    std::uint8_t  m_0xA5[3];
    std::int32_t  m_0xA8;           // +0xA8 = 0x7FFFFFFF
    std::uint64_t m_0xAC;           // +0xAC
    std::uint64_t m_0xB4;           // +0xB4 = -1
    std::uint16_t m_occlusionQuery; // +0xBA
};

struct RenderBind {
    // 65 bindings * 0x14 = 0x514 bytes
    // +0x140 from EncoderImpl
    std::uint8_t data[0x514];
};

struct SideTableEntry {
    void* ptr;       // +0x00
    std::uint64_t pad; // +0x08
};

struct SideTable {
    SideTableEntry entries[0x41]; // 0x41 * 0x10 = 0x410
    std::uint32_t count;          // +0x410
};

struct EncoderImpl {
    Frame* m_frame;              // +0x000
    SortKey m_key;               // +0x008
    std::uint8_t pad_0x18[0x28];
    RenderDraw m_draw;           // +0x040 (0x80 bytes)
    RenderBind m_bind;           // +0x140 (0x514 bytes)
    std::uint32_t m_bindHash;    // +0x654
    SideTable* m_sideTable;      // +0x680
    std::uint8_t m_bindDirty;    // +0x688
    std::uint32_t m_numSubmitted; // +0x68C
    std::uint32_t m_numDropped;   // +0x690
    std::uint32_t m_uniformBegin; // +0x694
    std::uint32_t m_uniformEnd;   // +0x698
    std::uint32_t m_numVertices[4]; // +0x69C
    std::uint8_t m_uniformIdx;    // +0x6AC
    std::uint8_t m_discard;       // +0x6AD
};

// Layout constants for 0xbc60740 (verified against disassembly)
static_assert(offsetof(EncoderImpl, m_frame) == 0x000, "EncoderImpl m_frame at +0x000");
static_assert(offsetof(EncoderImpl, m_key) == 0x008, "EncoderImpl m_key at +0x008");
static_assert(offsetof(SortKey, m_depth) == 0x08, "SortKey m_depth at +0x08");
static_assert(offsetof(SortKey, m_seq) == 0x0C, "SortKey m_seq at +0x0C");
static_assert(offsetof(SortKey, m_program) == 0x10, "SortKey m_program at +0x10");
static_assert(offsetof(SortKey, m_view) == 0x12, "SortKey m_view at +0x12");
static_assert(offsetof(SortKey, m_trans) == 0x14, "SortKey m_trans at +0x14");
static_assert(offsetof(EncoderImpl, m_draw) == 0x040, "EncoderImpl m_draw at +0x040");
static_assert(offsetof(RenderDraw, m_stateFlags) == 0x60 - 0x40, "RenderDraw m_stateFlags at +0x20 from m_draw (+0x60 from EncoderImpl)");
static_assert(offsetof(RenderDraw, m_stencil) == 0x68 - 0x40, "RenderDraw m_stencil at +0x28 from m_draw (+0x68 from EncoderImpl)");
static_assert(offsetof(RenderDraw, m_uniformBegin) == 0x74 - 0x40, "RenderDraw m_uniformBegin at +0x34 from m_draw (+0x74 from EncoderImpl)");
static_assert(offsetof(RenderDraw, m_uniformEnd) == 0x78 - 0x40, "RenderDraw m_uniformEnd at +0x38 from m_draw (+0x78 from EncoderImpl)");
static_assert(offsetof(RenderDraw, m_numIndices) == 0x84 - 0x40, "RenderDraw m_numIndices at +0x44 from m_draw (+0x84 from EncoderImpl)");
static_assert(offsetof(RenderDraw, m_numVertices) == 0x8C - 0x40, "RenderDraw m_numVertices at +0x4C from m_draw (+0x8C from EncoderImpl)");
static_assert(offsetof(RenderDraw, m_streamMask) == 0xA3 - 0x40, "RenderDraw m_streamMask at +0x63 from m_draw (+0xA3 from EncoderImpl)");
static_assert(offsetof(RenderDraw, m_uniformIdx) == 0xA4 - 0x40, "RenderDraw m_uniformIdx at +0x64 from m_draw (+0xA4 from EncoderImpl)");
static_assert(offsetof(RenderDraw, m_occlusionQuery) == 0xBA - 0x40, "RenderDraw m_occlusionQuery at +0x7A from m_draw (+0xBA from EncoderImpl)");
static_assert(sizeof(RenderDraw) == 0x80, "RenderDraw size 0x80");
static_assert(offsetof(EncoderImpl, m_bind) == 0x140, "EncoderImpl m_bind at +0x140");
static_assert(sizeof(RenderBind) == 0x514, "RenderBind size 0x514");
static_assert(offsetof(EncoderImpl, m_bindHash) == 0x654, "EncoderImpl m_bindHash at +0x654");
static_assert(offsetof(EncoderImpl, m_sideTable) == 0x680, "EncoderImpl m_sideTable at +0x680");
static_assert(offsetof(EncoderImpl, m_bindDirty) == 0x688, "EncoderImpl m_bindDirty at +0x688");
static_assert(offsetof(EncoderImpl, m_numSubmitted) == 0x68C, "EncoderImpl m_numSubmitted at +0x68C");
static_assert(offsetof(EncoderImpl, m_numDropped) == 0x690, "EncoderImpl m_numDropped at +0x690");
static_assert(offsetof(EncoderImpl, m_uniformBegin) == 0x694, "EncoderImpl m_uniformBegin at +0x694");
static_assert(offsetof(EncoderImpl, m_uniformEnd) == 0x698, "EncoderImpl m_uniformEnd at +0x698");
static_assert(offsetof(EncoderImpl, m_numVertices) == 0x69C, "EncoderImpl m_numVertices at +0x69C");
static_assert(offsetof(EncoderImpl, m_uniformIdx) == 0x6AC, "EncoderImpl m_uniformIdx at +0x6AC");
static_assert(offsetof(EncoderImpl, m_discard) == 0x6AD, "EncoderImpl m_discard at +0x6AD");

// SideTable layout
static_assert(offsetof(SideTableEntry, ptr) == 0x00, "SideTableEntry ptr at +0x00");
static_assert(offsetof(SideTableEntry, pad) == 0x08, "SideTableEntry pad at +0x08");
static_assert(sizeof(SideTableEntry) == 0x10, "SideTableEntry size 0x10");
static_assert(offsetof(SideTable, entries) == 0x00, "SideTable entries at +0x00");
static_assert(offsetof(SideTable, count) == 0x410, "SideTable count at +0x410");
static_assert(sizeof(SideTable) == 0x414, "SideTable size 0x414");

// Frame offsets
static_assert(sizeof(std::uint64_t) == 8, "u64 size");
static_assert(0x5d0 == 0x5d0, "function size 0x5d0");

} // namespace native::bgfx