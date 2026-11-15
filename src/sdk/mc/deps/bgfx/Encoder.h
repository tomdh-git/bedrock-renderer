#pragma once

namespace bgfx {

// bgfx::Encoder as laid out in 1.26.62.01 (docs/BGFX_MAP.md 6cq, 6cr, 6cw). [V] = read in the submit code, live-consistent where noted.
// The setters (setState, setTransform, setScissor, setBuffer, ...) are inlined stores into this object; there are no setter functions to hook.
// RVAs below are for 1.26.62.01 (add 0xC00 to the 1.26.60.05 values quoted in older notes).
struct EncoderOffsets {
    static constexpr uintptr_t kFrame = 0x00;            // [V] Frame* (the buffer of FrameOffsets)
    static constexpr uintptr_t kDepthSeq = 0x08;         // [V] u32 depth / sequence value passed to submit
    static constexpr uintptr_t kSeqResult = 0x0C;        // [V] u32 sequence counter result (mode 1 keys)
    static constexpr uintptr_t kProgram = 0x10;          // [V] u16 program handle (0xFFFF = none)
    static constexpr uintptr_t kViewId = 0x12;           // [V] u16
    static constexpr uintptr_t kFlags = 0x14;            // [V] u32, low 2 bits go into the sort key
    static constexpr uintptr_t kHeader = 0x40;           // [V] 0x80 bytes copied verbatim to Frame+0xB4700+idx*0x80 (header[k] = encoder[0x40+k])
    static constexpr uintptr_t kState = 0x60;            // [V] u64 draw state (= header+0x20), default 0x010000500000001F, see DrawState below
    static constexpr uintptr_t kState2 = 0x68;           // [V] u64 stencil state (= header+0x28)
    static constexpr uintptr_t kViewSlot = 0x6AC;        // [V] u8 m_uniformIdx: index into Frame's UniformBuffer* table at Frame+0xDC57E0 (not a view slot; name kept for callers)
    static constexpr uintptr_t kDiscard = 0x6AD;         // [V] u8, 1 = encoder discarded (submit tail-jumps to reset)
    static constexpr uintptr_t kRenderBind = 0x140;      // [V] 65 bindings of kBindingSize = 0x514 bytes, hashed into +0x654 and memcpy'd (0x518 bytes) to Frame[0x8B4700] + idx*0x540
    static constexpr size_t kBindingSize = 0x14;         // [V] Binding { u32 +0x00; u16 idx +0x0A (0xFFFF = unbound); u32 +0x0C; u8 type +0x13 }
    static constexpr size_t kBindingCount = 65;          // [V] (0x514 / 0x14), the clear loop in submit
    static constexpr uintptr_t kBindHash = 0x654;        // [V] u32, recomputed in submit when kBindDirty is 1
    static constexpr uintptr_t kPostCallback = 0x680;    // [V] side table* (0x41 entries of 16 bytes + u32 count at +0x410), non-null -> 0xbc60f10(Frame, idx, table) after submit
    static constexpr uintptr_t kBindDirty = 0x688;       // [V] u8, set to 1 after every non-preserving submit
    static constexpr uintptr_t kSubmitted = 0x68C;       // [V] u32 counter
    static constexpr uintptr_t kDiscarded = 0x690;       // [V] u32 counter
    static constexpr uintptr_t kUniformBegin = 0x694;    // [V] u32, copied to header +0x34
    static constexpr uintptr_t kUniformEnd = 0x698;      // [V] u32 = UniformBuffer pos at submit, copied to header +0x38
    static constexpr uintptr_t kNumVertices = 0x69C;     // [V] u32 per vertex stream; the minimum over the stream mask goes to header +0x4C
    // Inside the 0x80-byte header at kHeader (offsets from the encoder; subtract 0x40 for the header):
    static constexpr uintptr_t kNumIndices = 0x84;       // [V] u32 (header +0x44); submit drops the draw when this and kHeaderNumVertices are both 0
    static constexpr uintptr_t kHeaderNumVertices = 0x8C; // [V] u32 (header +0x4C)
    static constexpr uintptr_t kStreamMask = 0xA3;       // [V] u8 (header +0x63), 0xFF = stream 0 only
    static constexpr uintptr_t kOcclusionQuery = 0xBA;   // [V] u16 (header +0x7A); sets state bit 62 when valid
    // The other item kinds (docs/functions/submit_variants.md). They share the 0x80-byte Frame slot with a draw.
    static constexpr uintptr_t kCompute = 0xC0;          // [V] 0x24-byte RenderCompute: uniformBegin/End +0, startMatrix +8, indirect u16 +0xC, numX/Y/Z +0x10/+0x14/+0x18, numMatrices u16 +0x20, uniformIdx u8 +0x22, subtype u8 +0x23
    static constexpr size_t kComputeSize = 0x24;
    static constexpr uintptr_t kCustomItem = 0x100;      // [V] 16 bytes: the two payload words of the custom item (key bit 53)
};

struct EncoderRvas {              // 1.26.62.01
    static constexpr uintptr_t kSubmit = 0xBC60740;       // submit(this, u16 view, u16 program, u16 occlusionQuery, u32 depth, u8 preserveState): fully reversed in docs/functions/bc60740.md
    static constexpr uintptr_t kSubmitVariant1 = 0xBC61140;
    static constexpr uintptr_t kSubmitVariant2 = 0xBC61560; // dispatch-style (key 0x0020000000000000)
    static constexpr uintptr_t kSubmitVariant3 = 0xBC618E0; // no-program / indirect-like
    static constexpr uintptr_t kReset = 0xBC60D10;        // restores defaults after a submit
    static constexpr uintptr_t kFrameSort = 0xBC61E20;    // Frame::sort (radix sort of keys at +0x14700 into +0x94700)
};

// One binding stage of the RenderBind block (65 of them at EncoderOffsets::kRenderBind, copied into the Frame per draw).
// Fields from the encoder clear loop (bc60740.md) and the executor's descriptor build (e821120.md, 6fp). [V offsets, names partly I]
#pragma pack(push, 1)
struct Binding {
    uint32_t samplerFlags;   // +0x00 cleared to 0
    uint32_t firstElement;   // +0x04 buffer bindings: first element (shifted by the element size)
    uint8_t _08[2];          // +0x08
    uint16_t idx;            // +0x0A resource handle, 0xFFFF = unbound
    uint32_t extra;          // +0x0C cleared to 0xFFFFFFFF
    uint8_t _10;             // +0x10
    uint8_t access;          // +0x11 non-zero = written by the shader (UAV)
    uint8_t _12;             // +0x12
    uint8_t type;            // +0x13 BindingType
};
#pragma pack(pop)
static_assert(sizeof(Binding) == EncoderOffsets::kBindingSize);
static_assert(EncoderOffsets::kBindingCount * sizeof(Binding) == 0x514);
enum class BindingType : uint8_t { // the executor's descriptor build (BGFX_MAP 6fp/6fq)
    Reserved = 0,          // descriptor slot reserved, no view written [?]
    IndexBuffer = 1,       // index buffer as a shader buffer (SRV, or UAV when access != 0)
    VertexBuffer = 2,      // vertex buffer as a shader buffer
    Texture = 3,           // texture table (D3D12Tables::kTextures)
    ShaderBuffer = 4,      // shader-buffer table (D3D12Tables::kShaderBuffers), read or UAV
    AccelerationStructure = 5, // ray-tracing TLAS/BLAS SRV: taken only when the caps byte at rva 0x12ADFA53 has bit 0x80 (= CapsFlag::RayTracing, bit 31), else a reserved slot; the SRV is built from the record in the 0x78-stride table at renderer+0x57A178 (D3D12Tables::kAccelerationStructures) via device vtbl +0x90 CreateShaderResourceView(NULL, record+8, slot) [V static 0xe82609e / 0xe82735a; live the byte is 0xBB (bit set) while the whole table is zero, so the bit label RayTracing for bit 31 is Caps.h's inference, not independently proven]
    RangedTexture = 6,     // every entry of the draw's side table for this stage, as textures
    Ignored = 7,
    RangedShaderBuffer = 8,// every side-table entry, as shader buffers
    Sampler = 9,           // only the sampler flags (binding +0x00 & 0x1F0F07FF) are recorded for the stage; slot reserved
};

// Draw state u64 bit map, every field the PSO builder decodes (docs/functions/e81e860.md "PSO description", BGFX_MAP 6fs). The field
// values index the game's own D3D12 enum tables, which were dumped and match stock bgfx's order exactly. [V static]
struct DrawState {
    static constexpr uint64_t kWriteMask = 0xF;           // bits 0-3: RenderTargetWriteMask (R, G, B, A)
    static constexpr int kDepthFuncShift = 4;             // bits 4-7: 0 = depth test off, 1 LESS, 2 LEQUAL, 3 EQUAL, 4 GEQUAL, 5 GREATER, 6 NOTEQUAL, 7 NEVER, 8 ALWAYS
    static constexpr int kBlendSrcRgbShift = 12;          // bits 12-27: four 4-bit factors; 1 ZERO 2 ONE 3 SRC_COLOR 4 INV_SRC_COLOR 5 SRC_ALPHA 6 INV_SRC_ALPHA
    static constexpr int kBlendDstRgbShift = 16;          //   7 DST_ALPHA 8 INV_DST_ALPHA 9 DST_COLOR 10 INV_DST_COLOR 11 SRC_ALPHA_SAT 12 FACTOR 13 INV_FACTOR
    static constexpr int kBlendSrcAlphaShift = 20;        //   blend is enabled when any of the 16 bits is non-zero
    static constexpr int kBlendDstAlphaShift = 24;
    static constexpr int kBlendEquationShift = 28;        // bits 28-30 rgb, 31-33 alpha: 0 ADD 1 SUB 2 REVSUB 3 MIN 4 MAX
    static constexpr int kBlendEquationAlphaShift = 31;
    static constexpr int kIndependentBlendBit = 34;
    static constexpr int kAlphaToCoverageBit = 35;
    static constexpr int kCullShift = 36;                 // bits 36-37: 0 none, 1 front, 2 back
    static constexpr int kDepthWriteBit = 38;
    static constexpr int kAlphaRefShift = 40;             // bits 40-47: not in the PSO key (dynamic)
    static constexpr int kPrimitiveShift = 48;            // bits 48-50: index into the primitive table (topology)
    static constexpr int kMsaaBit = 56;                   // MultisampleEnable
    static constexpr int kLineAABit = 57;                 // AntialiasedLineEnable
    static constexpr int kConservativeRasterBit = 58;
    static constexpr int kOcclusionQueryBit = 62;         // internal: this draw is an occlusion query
};
// The 32-bit stencil words (low = front, high = back; back = front when the high word is 0). Ref and read mask are dynamic state.
struct StencilState {
    static constexpr int kRefShift = 0;       // bits 0-7 (OMSetStencilRef)
    static constexpr int kReadMaskShift = 8;  // bits 8-15
    static constexpr int kFuncShift = 16;     // bits 16-19: same table as the depth function
    static constexpr int kFailShift = 20;     // bits 20-23: 0 ZERO 1 KEEP 2 REPLACE 3 INCR 4 INCRSAT 5 DECR 6 DECRSAT 7 INVERT
    static constexpr int kDepthFailShift = 24;
    static constexpr int kPassShift = 28;
};

// Sort key (u64 at Frame+0x14700+idx*8), from the fully reversed submit and Frame::sort: view in bits 54..61 (8 bits, remapped to view
// order by Frame::sort), bit 52 = draw, bits 50..51 = sort type (program 0x10, depth 0x14, sequence 0x18 as the 48..53 tag).
struct SortKey {
    static constexpr int kViewShift = 54;
    static constexpr uint64_t kViewMask = 0x3FC0000000000000ull;
    static constexpr uint64_t kTagProgram = 0x0010000000000000ull;  // depth << 5 | (program & 0x7FF) << 37 | trans << 48
    static constexpr uint64_t kTagDepth = 0x0014000000000000ull;    // depth << 18 | u16(program << 5) | trans << 16
    static constexpr uint64_t kTagSequence = 0x0018000000000000ull; // (seq & 0xFFFFF) << 30 | (program << 17 & 0x0FFE0000) | trans << 28
    static constexpr uint64_t kDrawBit = 0x0010000000000000ull;     // bit 52: set on every draw key, clear on compute and custom items
    static constexpr uint64_t kCustomBit = 0x0020000000000000ull;   // bit 53: the custom item (0xbc61560); compute keys have neither bit
    static constexpr uint8_t viewOf(uint64_t key) { return static_cast<uint8_t>(key >> kViewShift); }
    static constexpr bool isDraw(uint64_t key) { return (key & kDrawBit) != 0; }
    // Field decoders for the three sort types, from Encoder::submit (bc60740.md); sequence type live-verified on 1078 keys of one frame:
    // every decoded program index had a non-null D3D12 program record, seq strictly increasing per view with no duplicates.
    static constexpr uint64_t kTypeMask = 0x001C000000000000ull;    // bits 50..52 only: (0x10 program, 0x14 depth, 0x18 sequence) << 48. Bits 48..49 belong to the payload (depth / seq high bits / trans)
    static constexpr uint64_t tag(uint64_t key) { return key & kTypeMask; }
    static constexpr uint32_t programOfSequence(uint64_t key) { return static_cast<uint32_t>((key >> 17) & 0x7FF); } // (program << 17) & 0x0FFE0000
    static constexpr uint32_t seqOfSequence(uint64_t key) { return static_cast<uint32_t>((key >> 30) & 0xFFFFF); }    // 20-bit per-view counter
    static constexpr uint32_t transOfSequence(uint64_t key) { return static_cast<uint32_t>((key >> 28) & 3); }       // Encoder flags low 2 bits
    static constexpr uint32_t programOfDepth(uint64_t key) { return static_cast<uint32_t>((key & 0xFFFF) >> 5); }     // uint16(program << 5): the trans bits (16..17) sit above it
    static constexpr uint32_t depthOfDepth(uint64_t key) { return static_cast<uint32_t>((key >> 18) & 0xFFFFFFFFull); } // u32 depth << 18 occupies bits 18..49
    static constexpr uint32_t transOfDepth(uint64_t key) { return static_cast<uint32_t>((key >> 16) & 3); }
    static constexpr uint32_t programOfProgram(uint64_t key) { return static_cast<uint32_t>((key >> 37) & 0x7FF); }  // (program & 0x7FF) << 37
    static constexpr uint32_t transOfProgram(uint64_t key) { return static_cast<uint32_t>((key >> 48) & 3); }
};
static_assert(SortKey::viewOf(SortKey::kViewMask) == 0xFF);
static_assert((SortKey::kViewMask & (SortKey::kTagProgram | SortKey::kTagDepth | SortKey::kTagSequence)) == 0);
static_assert(SortKey::tag(SortKey::kTagProgram) == SortKey::kTagProgram && SortKey::tag(SortKey::kTagDepth) == SortKey::kTagDepth && SortKey::tag(SortKey::kTagSequence) == SortKey::kTagSequence);
static_assert(SortKey::programOfSequence(SortKey::kTagSequence | (uint64_t(0x2A5) << 17)) == 0x2A5 && SortKey::seqOfSequence(SortKey::kTagSequence | (uint64_t(0xABCDE) << 30)) == 0xABCDE);
static_assert(SortKey::programOfProgram(SortKey::kTagProgram | (uint64_t(0x7FF) << 37)) == 0x7FF && SortKey::programOfDepth(SortKey::kTagDepth | (0x2A5u << 5)) == 0x2A5);

} // namespace bgfx
