#pragma once

namespace bgfx {

// The bgfx uniform registry inside bgfx::Context (docs/BGFX_MAP.md 6ag / 6ah, re-read live in the bgfx-d3d12-dragon pass: 54 uniforms, names,
// types and counts decoded from the records below). [V] = disassembly of createUniform 0xbc75440 and nameToPredefinedUniform 0xbc60100, live-read.

// Same numbering as stock bgfx::UniformType (live histogram: 8 Sampler, 45 Vec4, 1 Mat4).
enum class UniformType : int32_t { Sampler = 0, End = 1, Vec4 = 2, Mat3 = 3, Mat4 = 4, Count = 5 };

// Predefined uniforms (stock bgfx PredefinedUniform::Enum minus u_alphaRef, plus Mojang's three). 0xbc60100 maps a name to this index with a
// linear compare over the table of C-string pointers at rva 0xF4418C0 (VAs, 14 entries), 14 = not predefined.
enum class PredefinedUniform : uint8_t {
    ViewRect, ViewTexel, View, InvView, Proj, InvProj, ViewProj, InvViewProj,
    PrevViewProj,       // Mojang addition (temporal passes)
    Model, ModelView, ModelViewProj,
    PrevWorldPosOffset, // Mojang addition
    AlphaRef4,          // u_alphaRef4 (vec4) replaces stock u_alphaRef
    Count,              // 14, also the "not found" result of nameToPredefinedUniform
};
static_assert(static_cast<int>(PredefinedUniform::Count) == 14);

struct UniformRegistry {
    static constexpr uintptr_t kCreateUniform = 0xBC75440;            // createUniform(ctx, UniformHandle* out, const char* name, UniformType type, u16 num)
    static constexpr uintptr_t kNameToPredefined = 0xBC60100;
    static constexpr uintptr_t kPredefinedNameTableRva = 0xF4418C0;   // 14 x u64 VA of the name string (e.g. 0x14F541060 -> "u_viewRect")
    static constexpr uintptr_t kNameHash = 0xBC76610;                 // 16-byte digest, folded to the u32 key with MurmurHash2 mixing (m = 0x5BD1E995)
    // Context-relative:
    static constexpr uintptr_t kHashKeys = 0x1E1C2A4;                 // u32[1024], 0 = empty slot (live read of slot 0 = 0)
    static constexpr uintptr_t kHashHandles = 0x1E1D2A4;              // u16[1024], 0xFFFF = empty
    static constexpr uintptr_t kRecords = 0x1E1DAA8;                  // UniformRecord[512], stride 0x18, indexed by handle
    static constexpr size_t kHashSlots = 1024;
    static constexpr size_t kMaxUniforms = 512;                       // = CapsLimit::MaxUniforms and the allocator capacity (Handles.h kUniforms)
    // Probe: slot = ((hash * 0x5EBCA77) >> 0x13) * 0x1B1 & 0x3FF, linear probing with wrap & 0x3FF.
    static constexpr uint32_t kProbeMul = 0x5EBCA77;
    static constexpr int kProbeShift = 0x13;
    static constexpr uint32_t kProbeMul2 = 0x1B1;
};
static_assert(UniformRegistry::kHashKeys + 4 * UniformRegistry::kHashSlots == UniformRegistry::kHashHandles);
static_assert(UniformRegistry::kHashHandles + 2 * UniformRegistry::kHashSlots + 4 == UniformRegistry::kRecords);

struct UniformRecord {      // stride 0x18
    char* name;             // +0x00 owned copy of the name (freed through the allocator on reuse)
    int32_t nameLength;     // +0x08 strlen (live: "FogColor" -> 8)
    int32_t _0C;            // +0x0C unread by createUniform [?]
    UniformType type;       // +0x10
    uint16_t num;           // +0x14 array count (live: bgfx_clear_color has 8, DitherParams2 has 3)
    uint16_t _16;           // +0x16 pad
};
static_assert(sizeof(UniformRecord) == 0x18);
static_assert(offsetof(UniformRecord, nameLength) == 0x08 && offsetof(UniformRecord, type) == 0x10 && offsetof(UniformRecord, num) == 0x14);
static_assert(UniformRegistry::kRecords + UniformRegistry::kMaxUniforms * sizeof(UniformRecord) + 4 == 0x1E20AAC); // the next member (shader allocator area, createShader 0xbc71f60 touches +0x1E20AAC)

} // namespace bgfx
