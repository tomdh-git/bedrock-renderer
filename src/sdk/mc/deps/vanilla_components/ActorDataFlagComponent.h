// Hand-completed: tools/sdkgen/gen_types.py emits this component with no fields, which makes sizeof 1. The pool's payload pages are indexed by sizeof, so every entity past
// the first on a page was read 0x17 bytes per entity too close (garbage flags, invisible/bot verdicts at random). The real size is 0x18 (the std::bitset<119> of status flags
// plus padding; ClientMovementPredictionSyncPacketPayload carries it as 0x18 bytes). Keep this when regenerating.
#pragma once

#pragma pack(push, 1)
struct ActorDataFlagComponent {
    static constexpr uint32_t enttHash = 0xC67426F3;
    std::byte mFlags[0x18]; // std::bitset<119> mFlags, padded
};
#pragma pack(pop)
static_assert(sizeof(ActorDataFlagComponent) == 0x18);
