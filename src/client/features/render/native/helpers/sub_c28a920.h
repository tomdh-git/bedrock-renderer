#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// sub_c28a920 (0xc28a920, size 0xeb, 1.26.62.01).
//
// Walks the entry array [self->begin, self->end) and releases each entry's heap
// buffer together with the entry object itself (via native::sub_e935700), then
// resets self->begin/end/limit to zero and returns. On the corruption path
// (heap bias >= 0x20) it calls the fail handler through data slot [0xF9A8C78]
// (noreturn; int3 padding follows the call).
//
// x64 Microsoft ABI: argument (this/self) arrives in RCX; result leaves in RAX
// (result of the final sub_e935700 call).
//
// Calls [V]:
//   0xc28a950  call 0xE935700   -> native::sub_e935700 (lift set)
//   0xc28a95d  call 0xE935700   -> native::sub_e935700 (lift set)
//   0xc28a9d4  call 0xE935700   -> native::sub_e935700 (lift set)
//   0xc28aa04  call qword ptr [0xF9A8C78]  -> fail handler via data slot (brief rule 69)
//
// Struct field accesses ([V] from the disassembly of [0xc28a920, 0xc28aa0b)):
//   self + 0x00  void* begin   [R/W] entry-array cursor; read at entry, zeroed at exit
//   self + 0x08  void* end     [R]   entry-array end (loop bound)
//   self + 0x10  void* limit   [R/W] backing limit; (limit - begin) = total size; zeroed at exit
//   entry + 0x28 void* buffer  [R]   entry's heap-buffer start
//   entry + 0x38 void* bufferEnd [R] entry's heap-buffer end
// Raw heap reads (not struct fields): *(entry->buffer - 8) at 0xc28a98c and
// *(self->begin - 8) at 0xc28a9b9 (heap size header preceding an allocation).

struct sub_c28a920_entry {
    std::uint8_t pad0x00[0x28];
    void* buffer;            // + 0x28 [R] buffer start
    std::uint8_t pad0x30[0x38 - 0x30];
    void* bufferEnd;         // + 0x38 [R] buffer end
};

struct sub_c28a920_state {
    void* begin;             // + 0x00 [R/W]
    void* end;               // + 0x08 [R]
    void* limit;             // + 0x10 [R/W]
};

struct sub_c28a920Layout {
    static_assert(offsetof(sub_c28a920_state, begin) == 0x00,
                  "sub_c28a920_state: begin at +0x00");
    static_assert(offsetof(sub_c28a920_state, end) == 0x08,
                  "sub_c28a920_state: end at +0x08");
    static_assert(offsetof(sub_c28a920_state, limit) == 0x10,
                  "sub_c28a920_state: limit at +0x10");
    static_assert(offsetof(sub_c28a920_entry, buffer) == 0x28,
                  "sub_c28a920_entry: buffer at +0x28");
    static_assert(offsetof(sub_c28a920_entry, bufferEnd) == 0x38,
                  "sub_c28a920_entry: bufferEnd at +0x38");
    static_assert(sizeof(void*) == 8,
                  "sub_c28a920: x64 pointer-sized arguments (Microsoft x64 ABI)");
    static constexpr std::uintptr_t kFailSlotRva = 0xF9A8C78;  // call qword ptr [0xF9A8C78]
    static_assert(kFailSlotRva == 0xF9A8C78,
                  "sub_c28a920: fail-handler data slot RVA 0xF9A8C78");
};

// sub_e935700 is lift set; forward-declared here. Signature: void* sub_e935700(void* a0).
namespace native {
void* sub_e935700(void* a0);
}

// uintptr_t sub_c28a920(sub_c28a920_state* self)
//   self arrives in RCX. Every returning path ends with a call to sub_e935700;
//   the return value is that call's result. The null-self path returns with
//   RAX indeterminate (modeled as 0).
uintptr_t sub_c28a920(sub_c28a920_state* self);

} // namespace native::helpers
