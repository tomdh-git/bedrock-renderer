#pragma once

// Item group visitor 0x6646980 (1.26.62.01): jump-table tags and the payload offsets each handler path reads.
// Source: tools/sigs/ext_cv_cfg.py control-flow trace (docs/data/item_visitor_tag_reads_1.26.62.01.txt). Offsets are payload byte
// offsets from [r8] (the description pointer); only offsets, not field names, are asserted. Meanings in comments are [I] unless noted.
namespace mc::framebuilder::itemvisitor {

enum class Tag : uint8_t { Tag0 = 0, Tag1 = 1, Tag2 = 2, Tag3 = 3, Tag4 = 4, Tag5 = 5, Tag6 = 6, Tag7 = 7, Tag8 = 8, Tag9 = 9, Tag10 = 10 };
constexpr size_t kTagCount = 11;
// Handler entry rvas (jump table 0xf2bf2d0) and, for forwarders, the extractor they tail-call.
struct HandlerRva { Tag tag; uint32_t entry; uint32_t tailCall; };
constexpr HandlerRva kHandlers[kTagCount] = {
    {Tag::Tag0, 0x6646a10, 0},         {Tag::Tag1, 0x6646f5b, 0},         {Tag::Tag2, 0x6646c8d, 0},
    {Tag::Tag3, 0x6646d5f, 0x66ea3d0}, // terrain extractor
    {Tag::Tag4, 0x6646a89, 0},         {Tag::Tag5, 0x66471de, 0},
    {Tag::Tag6, 0x6647320, 0x6698e30}, // ItemInHand extractor
    {Tag::Tag7, 0x6646dc2, 0},
    {Tag::Tag8, 0x66473e6, 0x66e75f0},
    {Tag::Tag9, 0x6646bc6, 0},
    {Tag::Tag10, 0x6647383, 0x66d9af0},
};
static_assert(kHandlers[3].tailCall == 0x66ea3d0 && kHandlers[6].tailCall == 0x6698e30);

// Offsets read by the reachable code of each non-forwarder tag (union over inner data-driven switches).
constexpr uint16_t kTag0Reads[] = {0x00,0x18,0x1c,0x20,0x22,0x30,0x40,0x50,0x58,0x5c,0x64,0x78,0x88,0x89,0x8c,0x9c,0xa4,0xb4,0xc4,0xcc,0xd0,0xe0,0xe4};
constexpr uint16_t kTag4Reads[] = {0x00,0x08,0x10,0x18,0x20,0x22,0x30,0x38,0x40,0x48,0x88,0xd0,0xd4,0xdf,0x170,0x188,0x190,0x192};
constexpr uint16_t kTag9Reads[] = {0x00,0x10,0x18,0x20,0x22};
constexpr uint16_t kTag5Reads[] = {0x00,0x18,0x20,0x22};
constexpr uint16_t kTag7Reads[] = {0x00,0x08,0x10,0x18,0x20,0x22,0x30,0x88,0xb0,0xb8,0xc0,0xc8,0xd0,0xd4,0xdf,0xe0,0xe8,0x140,0x148,0x154,0x170,0x188,0x190,0x192,0x198,0x1a0,0x1a8,0x1b0,0x1cc};
constexpr size_t kTag7MaterialNode = 0x140; // [V live 6cn/6cv]: node ptr, name hash at node+0x10
constexpr size_t kTag7ModelMatrix = 0x00, kTag7PrevMatrix = 0x40, kTag7LocalAabb = 0x80; // [V live 6cv]
static_assert(sizeof(kTag7Reads) / sizeof(kTag7Reads[0]) == 29 && sizeof(kTag0Reads) / sizeof(kTag0Reads[0]) == 23);
static_assert(kTag7MaterialNode == 0x140 && kTag7PrevMatrix == 2 * 0x20);

} // namespace mc::framebuilder::itemvisitor
