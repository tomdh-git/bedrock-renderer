#pragma once

// The typed table of frame descriptions for the probe: for every (group, tag) its name from the SDK headers (FrameBuilder.h tags, Descriptions.h structs) and its size, which is
// the sizeof of the typed struct (each static_assert-ed against the reversed constructor in Descriptions.h). A size of 0 means the description is not typed yet (the probe dumps
// 0x40 bytes of it).
enum class RewriteGroup : uint8_t { Editor, Effect, Ui, Sky, Item, Light };

struct RewriteDescInfo {
    RewriteGroup group;
    uint64_t tag;
    const char* name;
    size_t size;
};

struct RewriteDescriptions {
    static const RewriteDescInfo* find(RewriteGroup group, uint64_t tag);
    static const char* groupName(RewriteGroup group);
    static size_t count();
};
