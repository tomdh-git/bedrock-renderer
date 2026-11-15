#pragma once

// Numeric block ids (BlockLegacy::mBlockId, see BlockApi::id) the client cares about, and the network id the server's UpdateBlock uses for redstone
// ore on this build (network ids are sequential, not hashes: they move with the game version).
namespace BlockIds {
inline constexpr uint16_t kAir = 0;
inline constexpr uint16_t kFlowingWater = 8;
inline constexpr uint16_t kWater = 9;
inline constexpr uint16_t kFlowingLava = 10;
inline constexpr uint16_t kLava = 11;
inline constexpr uint16_t kGoldOre = 14;
inline constexpr uint16_t kIronOre = 15;
inline constexpr uint16_t kLapisOre = 21;
inline constexpr uint16_t kDiamondOre = 56;
inline constexpr uint16_t kRedstoneOre = 73;
inline constexpr uint16_t kLitRedstoneOre = 74;
inline constexpr uint16_t kEmeraldOre = 129;
inline constexpr uint16_t kChest = 54;
inline constexpr uint16_t kEnderChest = 130;
inline constexpr uint16_t kTrappedChest = 146;
inline constexpr bool isChest(uint16_t id) { return id == kChest || id == kEnderChest || id == kTrappedChest; }
inline constexpr uint32_t kRedstoneOreNetworkId = 8594; // 1.26.51

// Ores that are a real find (iron, gold, lapis, diamond, emerald).
inline constexpr bool isRealOre(uint16_t id) { return id == kIronOre || id == kGoldOre || id == kLapisOre || id == kDiamondOre || id == kEmeraldOre; }
inline constexpr bool isRedstoneOre(uint16_t id) { return id == kRedstoneOre || id == kLitRedstoneOre; }
} // namespace BlockIds
