#pragma once

#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// Layout recovered from the disassembly of 0xbc5e120 (size 0xc1).
// Every offset below is read or written by the function at that exact offset [V].
// Role names (id, version, dataPtr, dataEnd, kind, found) are inferred from the
// access pattern [I]: they are the lifter's names, not symbols from the image.

struct Entry; // 0x48-byte entry of a searched range (defined below)

// Object at *(view + 0x08): the entry range being searched.
struct EntryRange {
    // +0x00..0x07 not read by this function
    const Entry* begin; // +0x08 first entry (walk pointer rax starts here)
    const Entry* end;   // +0x10 one-past-last entry (walk ends here)
};

// One entry of the range; consecutive entries are 0x48 bytes apart [V].
struct Entry {
    std::uint64_t id;     // +0x00 compared with key->id
    std::uint8_t version; // +0x08 compared with key->version
    // +0x09..0x17 not read by this function
    std::uint64_t dataPtr; // +0x18 out->value1 when both payload fields are nonzero
    std::uint64_t dataEnd; // +0x20 out->value0 = dataEnd - dataPtr
    // +0x28..0x2f not read by this function
    std::uint8_t kind; // +0x30 jump-table index; 0..2 -> payload, 3..6 -> not found
};

// The view argument (rcx): only +0x08 is read.
struct View {
    // +0x00..0x07 not read by this function
    const EntryRange* range; // +0x08 *(view + 0x08)
};

// The key argument (r8).
struct LookupKey {
    std::uint64_t id;     // +0x00
    std::uint8_t version; // +0x08; 0xFF selects the wildcard scan
};

// The result argument (rdx), which is also the return value (rax = out).
struct LookupResult {
    std::uint64_t value0; // +0x00
    std::uint64_t value1; // +0x08
    std::uint8_t found;   // +0x10; 0 = not found, 1 = found
};

static_assert(sizeof(View) == 0x10, "View must be 0x10 bytes");
static_assert(offsetof(View, range) == 0x08, "View::range must be at +0x08");
static_assert(sizeof(EntryRange) == 0x18, "EntryRange must be 0x18 bytes");
static_assert(offsetof(EntryRange, begin) == 0x08, "EntryRange::begin must be at +0x08");
static_assert(offsetof(EntryRange, end) == 0x10, "EntryRange::end must be at +0x10");
static_assert(sizeof(Entry) == 0x48, "Entry stride must be 0x48");
static_assert(offsetof(Entry, id) == 0x00, "Entry::id must be at +0x00");
static_assert(offsetof(Entry, version) == 0x08, "Entry::version must be at +0x08");
static_assert(offsetof(Entry, dataPtr) == 0x18, "Entry::dataPtr must be at +0x18");
static_assert(offsetof(Entry, dataEnd) == 0x20, "Entry::dataEnd must be at +0x20");
static_assert(offsetof(Entry, kind) == 0x30, "Entry::kind must be at +0x30");
static_assert(sizeof(LookupKey) == 0x10, "LookupKey must be 0x10 bytes");
static_assert(offsetof(LookupKey, id) == 0x00, "LookupKey::id must be at +0x00");
static_assert(offsetof(LookupKey, version) == 0x08, "LookupKey::version must be at +0x08");
static_assert(sizeof(LookupResult) == 0x18, "LookupResult must be 0x18 bytes");
static_assert(offsetof(LookupResult, value0) == 0x00, "LookupResult::value0 must be at +0x00");
static_assert(offsetof(LookupResult, value1) == 0x08, "LookupResult::value1 must be at +0x08");
static_assert(offsetof(LookupResult, found) == 0x10, "LookupResult::found must be at +0x10");

// Lifted function: 0xbc5e120, size 0xc1.
// x64 Microsoft ABI: rcx = view, rdx = out, r8 = key; returns rax = out.
extern "C" LookupResult* sub_bc5e120(const View* view, LookupResult* out, const LookupKey* key);

} // namespace native::bgfx
