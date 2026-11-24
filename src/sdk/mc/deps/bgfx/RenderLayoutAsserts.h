#pragma once

// Structure assertions for the renderer SDK, checked against the running game (SelfTest, world phase).
//
// Every offset, stride and magic number the bgfx / RenderDragon headers rely on is used by the game's own code as an immediate or a
// displacement. Each entry names an anchor function (a Sigs.json symbol) and the constants that function must contain; a constant that
// is no longer there means that layout changed in this build, and the line names the SDK constant to re-derive. Nothing here is
// dereferenced as game data: the check only reads the code bytes of functions the signature database already resolved.
//
// The same list lives in docs/data/layout_asserts.json and is checked offline by tools/sigs/layoutcheck.py, which decodes every
// immediate and displacement and also prints the nearby values a moved field most likely went to. Keep the two in step by hand when an
// entry is added. Sizes are the 1.26.62.01 function sizes: the scan window, not a promise.
namespace renderlayout {

struct Constant {
    uint64_t value;    // searched as 4 little-endian bytes (8 when it does not fit in 32 bits), then as a disp8/imm8 operand
    const char* backs; // the SDK constant or documented fact that depends on it
};

struct Function {
    const char* symbol; // Sigs.json name
    size_t size;        // bytes of code scanned from the function start
    const Constant* constants;
    size_t count;
};

inline constexpr Constant kEncoderSubmit[] = {
    {0xDC57E8, "Frame item count (draw slot counter)"},
    {0x14700, "Frame sort keys"},
    {0x94700, "FrameOffsets::kSortedItems"},
    {0xB4700, "FrameOffsets::kDrawHeaders"},
    {0x8B4700, "Frame RenderDraw array"},
    {0x540, "RenderDraw record stride"},
    {0x518, "RenderBind copy size"},
    {0x5BD1E995, "bind hash = MurmurHash2"},
    {0x010000500000001F, "default draw state"},
    {0x6AD, "Encoder discard byte"},
    {0xFFFE, "max draw calls cap"},
    {0xDC57E0, "Frame UniformBuffer* table"},
    {0x3FC0000000000000, "SortKey::kViewMask"},
    {0x1EAB1B2, "bgfx Context view[i].mode"},
    {0x1EAAC60, "bgfx Context m_seq[256]"},
    {0x680, "EncoderOffsets::kPostCallback (side table)"},
    {0x688, "EncoderOffsets::kBindDirty"},
    {0x69C, "EncoderOffsets::kNumVertices"},
    {0x654, "EncoderOffsets::kBindHash"},
    {0x514, "RenderBind size = 65 bindings x 0x14"},
};
inline constexpr Constant kEncoderReset[] = {
    {0x010000500000001F, "default draw state"},
    {0x6AD, "Encoder discard byte"},
    {0x667, "EncoderOffsets::kBindingCount = 65 (clear loop end)"},
    {0x410, "side table = 0x41 entries of 16 bytes"},
    {0x688, "EncoderOffsets::kBindDirty"},
};
inline constexpr Constant kUpdateUniforms[] = {
    {0x27FFFFFF, "UniformType::Count = 5"},
    {0x3FF, "uniform opcode num field"},
    {0x170, "D3D12Slots::kUpdateUniform (46)"},
    {0x178, "D3D12Slots::kSetMarker (47)"},
};
inline constexpr Constant kEncoderDispatch[] = {
    {0x1EAAC60, "bgfx Context m_seq[256]"},
    {0xB4720, "compute item = 0x24 bytes of the render item slot"},
    {0xFF0000, "RenderCompute clear value"},
};
inline constexpr Constant kEncoderSubmitCustom[] = {
    {0x0020000000000000, "SortKey::kCustomBit"},
    {0x100, "EncoderOffsets::kCustomItem"},
    {0x108, "custom item second payload word"},
};
inline constexpr Constant kEncoderSubmitFrameParams[] = {
    {0xE746DC, "FrameOffsets::kFrameParamsA"},
    {0x1E8, "frame parameter block A size"},
    {0xE748C8, "FrameOffsets::kFrameParamsB"},
    {0xE74908, "frame parameter block B shared_ptr control block"},
};
inline constexpr Constant kFrameSort[] = {
    {0x14700, "Frame sort keys"},
    {0x94700, "FrameOffsets::kSortedItems"},
    {0xDC57E8, "FrameOffsets::kItemCount"},
    {0xDC57EC, "FrameOffsets::kBlitCount"},
    {0x934778, "FrameOffsets::kBlitKeys"},
    {0xC03FFFFFFFFFFFFF, "SortKey view field = bits 54..61"},
    {0x1CFD0D0, "bgfx Context m_tempKeys"},
    {0x1D7D0C8, "bgfx Context m_tempValues"},
};
inline constexpr Constant kBgfxContextEndFrame[] = {
    {0xDC57E0, "Frame per-view tail block table"},
    {0x6AC, "surface object slot byte"},
    {0x6F8, "surface object timestamp"},
};
inline constexpr Constant kFrameGraphGenerate[] = {
    {0xAAAAAAAAAAAAAAAB, "names vector element = 0x30 bytes"},
    {0xCCCCCCCCCCCCCCCD, "dependency record = 40 bytes"},
};
inline constexpr Constant kTaskDispatch[] = {
    {0x298, "DragonFrameResources task vector begin"},
    {0x2A0, "DragonFrameResources task vector end"},
    {0xFFFFFF80, "task entry stride 0x80 (imm8 49 83 EC 80 = sub r12,-0x80)"},
};
inline constexpr Constant kDrawExecutor[] = {
    {0x94700, "FrameOffsets::kSortedItems"},
    {0xB4700, "FrameOffsets::kDrawHeaders"},
    {0x8B4700, "Frame RenderDraw array"},
    {0x540, "RenderDraw record stride"},
    {0x514, "bind hash offset inside RenderDraw"},
    {0x8B4778, "FrameOffsets::kSideTables"},
    {0x14700, "FrameOffsets::kSortKeys (item class read from the key)"},
    {0x14300, "FrameOffsets::kOcclusion"},
    {0x0030000000000000, "item class mask = SortKey::kDrawBit | kCustomBit"},
    {0x0020000000000000, "SortKey::kCustomBit"},
    {0x000C000000000000, "draw sort-type field, bits 50..51"},
    {0x9B21F0, "vertex buffer record +0x78 = layout handle"},
    {0x9B21D0, "VertexBufferRecord::kGpuAddress (+0x58)"},
    {0x93A178, "D3D12Tables::kIndexBuffers (indexed append)"},
    {0x19F48, "command signature for indirect draws"},
    {0x19F50, "command signature for indirect indexed draws"},
    {0xAC3, "D3D12_RESOURCE_STATE_GENERIC_READ (buffer transitions)"},
    {0xA45C, "vertex buffer tracked-state words"},
    {0x24C, "index buffer tracked-state words"},
    {0x90A8, "job view rect (ViewRect predefined)"},
    {0x90A0, "job view matrices (View predefined)"},
    {0x2F8, "job model matrix cache"},
    {0xE174, "job cached InvView flag"},
    {0x224A8, "ranged-binding texture touched bitmap"},
    {0x226AC, "ranged-binding texture tracked states"},
    {0x22498, "ranged-binding texture records"},
    {0x104, "per-stage SRV state array = 65 x u32"},
    {0x0007000000000000, "state primitive-type field, bits 48..50"},
    {0x4000000000000000, "BGFX_STATE_INTERNAL_OCCLUSION_QUERY (bit 62)"},
    {0x00FC5D1543EC5F01, "bind-state cache bucket hash multiplier"},
    {0x1003F, "bind-state cache bucket hash polynomial"},
    {0xB62178, "D3D12Tables::kPrograms"},
    {0x9B2178, "D3D12Tables::kVertexBuffers"},
    {0xC97698, "D3D12Tables::kFrameBuffers"},
    {0xD457D0, "FrameOffsets::kScissorRects"},
};
inline constexpr Constant kSetVertexBuffers[] = {
    {0x9B2178, "D3D12Tables::kVertexBuffers"},
    {0xC9619C, "D3D12Tables::kVertexLayouts + VertexLayoutRecord::kStride"},
    {0xA248, "D3D12StateOffsets::kVbResources"},
    {0xA250, "D3D12StateOffsets::kVbTouchedCount"},
    {0xA258, "D3D12StateOffsets::kVbTouched"},
    {0xA45C, "D3D12StateOffsets::kVbState + 4"},
    {0xA458, "D3D12StateOffsets::kVbState"},
    {0x12458, "D3D12StateOffsets::kVbTouchedList"},
    {0x00000AC300000AC3, "initial state pair {GENERIC_READ, GENERIC_READ}"},
};
inline constexpr Constant kPsoBuilder[] = {
    {0x0707007FFFFFF0FF, "PSO key mask of the state word"},
    {0xFFFFFF00FFFFFF00, "PSO key mask of the second state word"},
    {0xB62178, "D3D12Tables::kPrograms"},
    {0xBDE178, "D3D12Tables::kTextures"},
    {0xC97698, "D3D12Tables::kFrameBuffers"},
    {0xC976B0, "FrameBufferRecord::kWindow (+0x18)"},
    {0xC96178, "D3D12Tables::kTextureOverflowPages"},
    {0xC96190, "D3D12Tables::kDynamicTextureGuard"},
    {0xB8000, "texture page = 4096 x 0xB8"},
    {0x290, "sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC)"},
    {0x1248, "renderer root signature"},
    {0x3FFFFFFFF, "SampleMask 0xFFFFFFFF + FillMode SOLID"},
    {0x19FDC, "renderer depth-clamp byte"},
    {0x0FFFF000, "blend-enable test, factor bits 12..27"},
    {0x400, "D3D12RendererOffsets::kDevice"},
    {0x19F88, "D3D12RendererOffsets::kDeviceState"},
    {0x19F98, "D3D12RendererOffsets::kBackBufferFormat"},
};
inline constexpr Constant kDrawFlush[] = {
    {0x1D8, "ID3D12GraphicsCommandList::ExecuteIndirect (index 59)"},
    {0xF28, "DrawBatcherOffsets::kRingSlot"},
    {0x10C0, "DrawBatcherOffsets::kVbCache"},
    {0x1110, "DrawBatcherOffsets::kIbCache"},
    {0x1120, "DrawBatcherOffsets::kLastCbv"},
    {0x1148, "DrawBatcherOffsets::kStatDirect"},
    {0x1150, "DrawBatcherOffsets::kStatOverflow"},
    {0x115C, "DrawBatcherOffsets::kCapacity"},
    {0x1164, "DrawBatcherOffsets::kIndirectEnabled"},
};
inline constexpr Constant kVisitSky[] = {
    {0x548, "Atmosphere queue: Sky-pass vector at pass+0x548 (6ih)"},
    {0x138, "sizeof(RenderAtmosphereDescription)"},
    {0x128, "Atmosphere description last 16-byte read +0x128"},
    {0x11C, "Atmosphere description read +0x11C"},
    {0x10C, "Atmosphere description read +0x10C"},
};
inline constexpr Constant kVisitLight[] = {
    {0x800, "Light pass vector +0x800 (R6)"},
    {0x648, "Light pass vector +0x648 (R6)"},
    {0x4A0, "Light pass vector +0x4A0 (R6)"},
    {0x1D0, "Light pass vector +0x1D0 (R6)"},
    {0x84, "sizeof(RenderLightTag2Description)"},
};
inline constexpr Constant kVisitItem[] = {
    {0x140, "Item description read +0x140 (ItemInHand/BatchActor tail)"},
    {0xC8, "sizeof item payload / DrawItem index record (0xC8)"},
    {0xE8, "Item description read +0xE8"},
    {0xC0, "Item description read +0xC0"},
};
inline constexpr Constant kVisitEffect[] = {
    {0xF8, "sizeof(RenderFlameBillboardDescription)"},
    {0xA0, "sizeof(RenderBlitFlipbookDescription)"},
    {0xB0, "sizeof(RenderParticleDescription)"},
};
inline constexpr Constant kVisitUI[] = {
    {0x90, "UIMesh description size lower bound (R10, >= 0x90)"},
};
inline constexpr Constant kVisitEditor[] = {
    {0x64, "Editor description +0x64 16-byte movups block read (disp8 0F 10 77 64)"},
    {0xD0, "Editor description +0xD0 u16 word read (disp32)"},
    {0x3C, "Editor description +0x3C byte cmp to 1 (disp8 80 7F 3C 01)"},
    {0x122, "Editor description +0x122 byte cmp to 1 (disp32 80 BF 22 01 00 00 01)"},
};
inline constexpr Constant kRendererContextD3D12Submit[] = {
    {0x1778, "submit stack frame size (stack probe)"},
    {0x19F88, "renderer state; <5 skips submit work"},
    {0xDC5808, "Frame backbuffer size {u32 width, u32 h}"},
    {0xE746D8, "Frame counter u32, +1 per frame"},
    {0x19F58, "RendererContext resource-table ptr"},
    {0xDC57E8, "Frame item count (draw slot counter, cap 0xFFFE)"},
    {0x14700, "Frame sort keys u64[]"},
    {0x410, "per-view setup side table"},
};

#define BS_RENDER_LAYOUT_FN(symbol, size, table) Function{symbol, size, table, sizeof(table) / sizeof(table[0])}
inline constexpr Function kFunctions[] = {
    BS_RENDER_LAYOUT_FN("Encoder::submit", 0x5D0, kEncoderSubmit),
    BS_RENDER_LAYOUT_FN("Encoder::reset", 0x1FC, kEncoderReset),
    BS_RENDER_LAYOUT_FN("Encoder::updateUniforms", 0x200, kUpdateUniforms),
    BS_RENDER_LAYOUT_FN("Encoder::dispatch", 0x411, kEncoderDispatch),
    BS_RENDER_LAYOUT_FN("Encoder::submitCustom", 0x372, kEncoderSubmitCustom),
    BS_RENDER_LAYOUT_FN("Encoder::submitFrameParams", 0x535, kEncoderSubmitFrameParams),
    BS_RENDER_LAYOUT_FN("Encoder::frameSort", 0x215, kFrameSort),
    BS_RENDER_LAYOUT_FN("FrameGraph::endFrame", 0x2AA, kBgfxContextEndFrame),
    BS_RENDER_LAYOUT_FN("FrameGraph::generate", 0x8A73, kFrameGraphGenerate),
    BS_RENDER_LAYOUT_FN("FrameGraph::taskDispatch", 0xC3A, kTaskDispatch),
    BS_RENDER_LAYOUT_FN("D3D12Context::drawExecutor", 0xC3C3, kDrawExecutor),
    BS_RENDER_LAYOUT_FN("D3D12Context::setVertexBuffers", 0x24F, kSetVertexBuffers),
    BS_RENDER_LAYOUT_FN("D3D12Context::psoBuilder", 0x1C9A, kPsoBuilder),
    BS_RENDER_LAYOUT_FN("D3D12Context::drawFlush", 0x803, kDrawFlush),
    BS_RENDER_LAYOUT_FN("FrameBuilder::visitSky", 0x86BE, kVisitSky),
    BS_RENDER_LAYOUT_FN("FrameBuilder::visitLight", 0x401A, kVisitLight),
    BS_RENDER_LAYOUT_FN("FrameBuilder::visitItem", 0x9425, kVisitItem),
    BS_RENDER_LAYOUT_FN("FrameBuilder::visitEffect", 0x6C7C, kVisitEffect),
    BS_RENDER_LAYOUT_FN("FrameBuilder::visitUI", 0x3B10, kVisitUI),
    BS_RENDER_LAYOUT_FN("FrameBuilder::visitEditor", 0x9F91, kVisitEditor),
    BS_RENDER_LAYOUT_FN("RendererContextD3D12::submit", 0x4D91, kRendererContextD3D12Submit),
};
#undef BS_RENDER_LAYOUT_FN

// Small field offsets are encoded by the compiler as an 8-bit displacement or immediate, not as a 4-byte constant, so a raw
// value search cannot see them. Recognise the three instruction shapes the game code uses for such operands:
//   - SSE load/store with [reg+disp8]        (0F 10..17 / 0F 28..2F / 0F 6F / 0F 7F /r)
//   - byte group-1 op with [reg+disp8],imm8  (80 /r ib, e.g. cmp byte ptr [rdi+0x3C],1)
//   - REX.W group-1 op with reg,imm8         (48..4F 83 /r ib, e.g. sub r12,-0x80)
// The surrounding opcode bytes keep the match specific: a stray byte cannot satisfy a full template.
inline bool containsSmallOperand(const uint8_t* code, size_t size, uint8_t value) {
    for (size_t i = 0; i + 3 < size; ++i) {
        if (code[i] == 0x0F) {
            const uint8_t op = code[i + 1];
            const bool sse = (op >= 0x10 && op <= 0x17) || (op >= 0x28 && op <= 0x2F) || op == 0x6F || op == 0x7F;
            if (sse && (code[i + 2] & 0xC0) == 0x40 && (code[i + 2] & 0x07) != 0x04 && code[i + 3] == value)
                return true;
        }
        if (code[i] == 0x80 && (code[i + 1] & 0xC0) == 0x40 && (code[i + 1] & 0x07) != 0x04 && code[i + 2] == value)
            return true;
        if (code[i] >= 0x48 && code[i] <= 0x4F && code[i + 1] == 0x83 && (code[i + 2] & 0xC0) == 0xC0 && code[i + 3] == value)
            return true;
    }
    return false;
}

// True when `value` appears in [code, code + size) as a little-endian immediate/displacement (4 bytes, or 8 for a 64-bit value),
// or, for a value that fits in a signed byte, as the disp8/imm8 form the compiler emits for small offsets.
inline bool contains(const uint8_t* code, size_t size, uint64_t value) {
    const size_t width = (value >> 32) ? 8 : 4;
    if (size >= width) {
        for (size_t i = 0; i + width <= size; ++i)
            if (std::memcmp(code + i, &value, width) == 0)
                return true;
    }
    const int64_t signedValue = static_cast<int64_t>(static_cast<int32_t>(value));
    if (signedValue < -128 || signedValue > 127)
        return false;
    return containsSmallOperand(code, size, static_cast<uint8_t>(signedValue));
}

// K-P9: every slot of a renderer vtable must point into the module's code. `vtable` is the live vtable (read through the renderer object),
// `slots` its slot count (65 for RendererContextD3D12 and its RTX subclass, docs/data/d3d12_vtable_1.26.62.01.txt), [textBegin, textEnd)
// the module .text range. Returns the index of the first slot outside it, or `slots` when all are inside. Called by SelfTest's
// checkRendererVtables on both static renderer vtables; the offline twin is tools/sigs/slotcheck.py.
inline size_t firstSlotOutsideText(const uintptr_t* vtable, size_t slots, uintptr_t textBegin, uintptr_t textEnd) {
    for (size_t i = 0; i < slots; ++i)
        if (vtable[i] < textBegin || vtable[i] >= textEnd)
            return i;
    return slots;
}

} // namespace renderlayout
