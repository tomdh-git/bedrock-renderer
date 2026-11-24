// LIFT 0xbcc7f20 chunk state (part 3/5)
// ChunkState for MaterialInstance::initFromMaterial chunk 3 [0xbccaf16..0xbccc713):
// this (MaterialInstance*) in rsi/[rbp+0x270], m (const Material*) originally in rdx,
// rbp frame base, callee-saved registers rbx/rsi/rdi/r12/r13/r14/r15,
// and key stack slots per the dossier.
struct ChunkState_bcc7f20_c03 {
    void* rsi_this;           // MaterialInstance* (kept in rsi, saved at [rbp+0x270])
    void* rdx_m;              // const Material* (original rdx, spilled/reloaded)
    void* rbp_frame_base;     // rbp
    void* rbx_scratch;
    void* rdi_scratch;
    void* r12_scratch;
    void* r13_scratch;
    void* r14_scratch;
    void* r15_scratch;
    // Key stack slots (rbp-relative) live across this chunk:
    void* slot_138;  // [rbp+0x138]
    void* slot_130;  // [rbp+0x130]
    void* slot_180;  // [rbp+0x180]
    void* slot_E0;   // [rbp+0xE0]
    void* slot_120;  // [rbp+0x120]
    void* slot_128;  // [rbp+0x128]
    void* slot_230;  // [rbp+0x230]
    void* slot_228;  // [rbp+0x228]
    void* slot_258;  // [rbp+0x258]
    void* slot_260;  // [rbp+0x260]
    void* slot_268;  // [rbp+0x268]
    void* slot_1A0;  // [rbp+0x1A0]
    void* slot_1A8;  // [rbp+0x1A8]
    void* slot_1B8;  // [rbp+0x1B8]
    void* slot_1C0;  // [rbp+0x1C0]
    void* slot_1C8;  // [rbp+0x1C8]
    void* slot_1D0;  // [rbp+0x1D0]
    void* slot_1E0;  // [rbp+0x1E0]
    void* slot_1E8;  // [rbp+0x1E8]
    void* slot_1F0;  // [rbp+0x1F0]
    void* slot_200;  // [rbp+0x200]
    void* slot_208;  // [rbp+0x208]
    void* slot_210;  // [rbp+0x210]
    void* slot_214;  // [rbp+0x214] (word)
    void* slot_218;  // [rbp+0x218]
    void* slot_A0;   // [rbp+0xA0]
    void* slot_A2;   // [rbp+0xA2] (byte)
    void* slot_C8;   // [rbp+0xC8] (word)
    void* slot_CA;   // [rbp+0xCA] (byte)
    void* slot_7C;   // [rbp+0x7C] (word)
    void* slot_80;   // [rbp+0x80] (dword)
    void* slot_84;   // [rbp+0x84] (byte)
    void* slot_44;   // [rbp+0x44] (word)
    void* slot_48;   // [rbp+0x48] (dword)
    void* slot_4C;   // [rbp+0x4C] (byte)
    void* slot_1B0;  // [rbp+0x1B0]
    void* slot_1B8;  // duplicate for clarity
    void* slot_90;   // [rbp+0x90]
    void* slot_98;   // [rbp+0x98]
    void* slot_238;  // [rbp+0x238]
    void* slot_10;   // [rbp+0x10]
    void* slot_8;    // [rbp+0x8]
    void* slot_140;  // [rbp+0x140]
    void* slot_148;  // [rbp+0x148]
    void* slot_150;  // [rbp+0x150]
    void* slot_158;  // [rbp+0x158]
    void* slot_160;  // [rbp+0x160]
    void* slot_168;  // [rbp+0x168]
    void* slot_178;  // [rbp+0x178]
    void* slot_190;  // [rbp+0x190]
    void* slot_198;  // [rbp+0x198]
    void* slot_D0;   // [rbp+0xD0]
    void* slot_D8;   // [rbp+0xD8]
    void* slot_60;   // [rbp+0x60]
    void* slot_28;   // [rbp+0x28]
    void* slot_E0b;  // [rbp+0xE0] (byte)
    void* slot_30;   // [rbp+0x30]
    void* slot_38;   // [rbp+0x38]
    void* slot_50;   // [rbp+0x50]
    void* slot_68;   // [rbp+0x68]
    void* slot_70;   // [rbp+0x70]
};

// Layout constants for MaterialInstance and related structs (offsets used in this chunk)
namespace native::bgfx {

// MaterialInstance field offsets [V from disassembly]
static constexpr std::ptrdiff_t kMaterialInstance_name = 0x128;
static constexpr std::ptrdiff_t kMaterialInstance_uniformBlock = 0x170;
static constexpr std::ptrdiff_t kMaterialInstance_variantArray = 0x290; // +0x290 variant array start
static constexpr std::ptrdiff_t kMaterialInstance_flagTable = 0x2A8;
static constexpr std::ptrdiff_t kMaterialInstance_allocatorTag = 0x2F;

// Material field offsets [V from disassembly]
static constexpr std::ptrdiff_t kMaterial_name = 0x40;

// UniformBlock offsets [V from disassembly]
static constexpr std::ptrdiff_t kUniformBlock_data = 0x40;
static constexpr std::ptrdiff_t kUniformBlock_entrySize = 0x30;
static constexpr std::ptrdiff_t kUniformBlock_count = 0x4A; // word at +0x4A
static constexpr std::ptrdiff_t kUniformBlock_entries = 0x50; // vec4 entries
static constexpr std::ptrdiff_t kUniformBlock_mat3Count = 0x5A; // word at +0x5A
static constexpr std::ptrdiff_t kUniformBlock_mat3Entries = 0x60; // mat3 entries
static constexpr std::ptrdiff_t kUniformBlock_mat4Count = 0x6A; // word at +0x6A
static constexpr std::ptrdiff_t kUniformBlock_mat4Entries = 0x70; // mat4 entries

// String/buffer layout (SSO threshold 0x10) [V from disassembly]
static constexpr std::size_t kSSOThreshold = 0x10;
static constexpr std::size_t kStringSize = 0x28;

// Magic constants [V from disassembly]
static constexpr std::uint64_t kFnv1a64OffsetBasis = 0xCBF29CE484222325ull;
static constexpr std::uint64_t kFnv1a64Prime = 0x100000001B3ull;
static constexpr std::uint64_t kMagicDiv40 = 0xF0F0F0F0F0F0F0F1ull;
static constexpr std::uint64_t kMagicDiv24 = 0xFFFFCCCDull; // for /24 (0x18 stride)
static constexpr std::uint64_t kMagicDiv16 = 0xFFFFAAABull; // for /16 (0x10 stride)
static constexpr std::uint64_t kMagicDiv8 = 0x7FFFFFFFFFFFFFFFull;
static constexpr std::uintptr_t kTombstoneRva = 0xF847A07;
static constexpr std::uintptr_t kAllocatorGlobalRva = 0x12ADF800;
static constexpr std::uintptr_t kThunkSlotRva = 0xF99FFA0; // sub_eea6040
static constexpr std::uintptr_t kData1233E1A8 = 0x1233E1A8;
static constexpr std::uintptr_t kDataF44B6E0 = 0xF44B6E0;
static constexpr std::uintptr_t kDataF44C0F0 = 0xF44C0F0;
static constexpr std::uintptr_t kData128C1A58 = 0x128C1A58;
static constexpr std::uintptr_t kData12ADFA50 = 0x12ADFA50;
static constexpr std::uintptr_t kData12ADF800 = 0x12ADF800;
static constexpr std::uintptr_t kData12AE1748 = 0x12AE1748;

} // namespace native::bgfx