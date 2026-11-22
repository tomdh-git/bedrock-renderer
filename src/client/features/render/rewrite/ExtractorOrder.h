#pragma once

// Q3b: the seven extractors in cost order (BatchActor, ChunkGeometry, Nametag, Particle, Sky, Clouds, Weather), i.e. the order a
// table-driven rewrite walks them. Every RVA below was read verbatim from rdis disassembly of Minecraft.Windows.exe 1.26.62.01 and
// is tagged [V] in docs/progress/oc_U-EQ3b.md. Self-contained, read-only source: includes Descriptions.h + DrawItem.h only, no
// detours, no hooks, no build and no game run required. Rank uniqueness is enforced by a constexpr static_assert.
//
// An entry with insertCloneRva == 0 has no thin insert clone on disk (its fat extractor clone doubles as the entry).
//
// The description type of each extractor: BatchActor is typed here by the new header
// src/sdk/mc/deps/minecraft_renderer/framebuilder/BatchActorDescription.h (it was size 0 = untyped in
// RewriteDescriptions.cpp:18, the last untyped of Q3b's seven -> that header closes M2c for BatchActor); the other six are typed in
// Descriptions.h / SkyDescriptions.h / WeatherDescription.h.


#include "sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h"
#include "sdk/mc/deps/minecraft_renderer/framebuilder/DrawItem.h"

namespace bluey::render::rewrite {

enum class ExtractorGroup : uint8_t { Item, Effect, Sky };

struct ExtractorEntry {
    const char* name;             // description / extractor name
    uint32_t extractorRva;        // extractor entry point (the fat clone when no thin insert clone exists)
    uint32_t insertCloneRva;      // thin insert clone entry point, 0 when none was found on disk
    uint8_t costRank;             // 1 = extracted first (cheapest) ... 7 = most expensive
    ExtractorGroup group;         // variant group the insert clone targets
    uint64_t tag;                 // variant tag the insert clone stores before its group-slot call
    const char* descriptionType;  // typed description struct the extractor reads
};

// Cost order: cheapest first. Rank i+1 at index i.
static constexpr ExtractorEntry kExtractorsInCostOrder[7] = {
    {"BatchActor",   0x66d9af0, 0x4e39cb0, 1, ExtractorGroup::Item,  10, "bluey::batchactor::Description (BatchActorDescription.h)"},
    {"ChunkGeometry",0x66ea3d0, 0x15a6880, 2, ExtractorGroup::Item,   3, "mce::framebuilder::RenderChunkGeometryDescription (Descriptions.h, 0xF0 [V])"},
    {"Nametag",      0x1127330, 0,          3, ExtractorGroup::Item,  1, "mce::framebuilder::RenderNametagDescription (Descriptions.h, 0x98 [V])"},
    {"Particle",     0x67417f0, 0x5b8d520, 4, ExtractorGroup::Effect, 2, "mce::framebuilder::RenderParticleDescription (Descriptions.h, 0xB0 [V])"},
    {"Sky",          0x5369b30, 0,          5, ExtractorGroup::Sky,   1, "mce::framebuilder::RenderSkyColorsDescription (tag 5) / RenderStarsDescription (tag 6) (Descriptions.h, 0xB0 [V])"},
    {"Clouds",       0x67375a0, 0x53e88a0, 6, ExtractorGroup::Sky,   1, "mce::framebuilder::RenderCloudsDescription (Descriptions.h, 0xA8 [V])"},
    {"Weather",      0x6745440, 0x5ad5800, 7, ExtractorGroup::Sky,   9, "mce::framebuilder::RenderWeatherDescription (Descriptions.h, 0x130 [V])"},
};

// Every rank 1..7 exactly once.
static_assert(sizeof(kExtractorsInCostOrder) / sizeof(kExtractorsInCostOrder[0]) == 7);
static_assert(
    kExtractorsInCostOrder[0].costRank == 1 && kExtractorsInCostOrder[1].costRank == 2 &&
    kExtractorsInCostOrder[2].costRank == 3 && kExtractorsInCostOrder[3].costRank == 4 &&
    kExtractorsInCostOrder[4].costRank == 5 && kExtractorsInCostOrder[5].costRank == 6 &&
    kExtractorsInCostOrder[6].costRank == 7,
    "cost ranks must be 1..7 in the declared cost order");

// Frame-side comparison offsets used to verify a rewrite by comparing the extractor-emitted DrawItems
// (0xC8 pass-item records, DrawItem.h) against the Frame draw headers consumed by submit 0xe82e230:
// sorted u16 ids at Frame+0x94700 (65536 entries ending at Frame+0xB4700), then 0x80-byte draw headers at
// Frame+0xB4700 (header+0x7A u16 handle, 0xFFFF = none), draw count u32 at Frame+0xDC57E8, per-item
// 0x540-record field at +0x514 of the Frame tail block (Frame+0x8B4700).
static constexpr uintptr_t kFrameDrawHeaders = 0xB4700;
static constexpr uintptr_t kFrameHeaderStride = 0x80;
static constexpr uintptr_t kFrameSortedIds = 0x94700;
static constexpr uintptr_t kFrameDrawCount = 0xDC57E8;
static_assert(kFrameSortedIds + 65536ull * sizeof(uint16_t) == kFrameDrawHeaders);
static_assert(sizeof(mce::framebuilder::DrawItem) == 0xC8);

} // namespace bluey::render::rewrite
