// LIFT 0xe824af1 size 0x89f2 1.26.62.01 sub_e824af1 (part 4/7)
// CHUNK 0xe829235..0xe82a912

#include "sub_e824af1_part4.h"
#include <cstdint>
#include <cstring>

namespace native { namespace d3d12 {

// Chunk state passed in as opaque pointer; cast to ChunkState&.
struct ChunkState {
    uint64_t rbx, rbp, r12, r13, r14, r15, rsi, rdi;
};

static inline void chunk_e824af1_c03(ChunkState& state) {
    uint64_t rbx = state.rbx;
    uint64_t rbp = state.rbp;
    uint64_t r12 = state.r12;
    uint64_t r13 = state.r13;
    uint64_t r14 = state.r14;
    uint64_t r15 = state.r15;
    uint64_t rsi = state.rsi;
    uint64_t rdi = state.rdi;
    auto stack = reinterpret_cast<uint8_t*>(rbx);

    // 0xe829235..0xe82924f  entry: mov rax,[rbx+0x90]; cmp r11d,...; setup r10/r11 for resource table
    uint64_t r10 = *reinterpret_cast<uint64_t*>(rbx + 0x90);
    uint32_t r11d = *reinterpret_cast<uint32_t*>(rbx + 0x180);
    // 0xe82924f..0xe829256  first call to 0x47E8F0 (memset-like) over r14 block
    // 0xe829256  call 0x47E8F0
    // (boundary CRT memset) memset(r14, 0, size)
    std::memset(reinterpret_cast<void*>(r14), 0, 0x28);

    // 0xe82925b..0xe8292af  loop over 9 slots: r12 index, r15 pointer; call 0x47E8F0 each
    for (int i = 0; i < 9; ++i) {
        // 0xe82925b..0xe8292af  advance r15, call 0x47E8F0
        // 0xe8292b0  call 0x47E8F0
        std::memset(reinterpret_cast<void*>(r15), 0, 0x28);
        r15 += 0xB8;
    }

    // 0xe8292b5..0xe829309  second block: r14 reset, r15 base; call 0x47E8F0
    // 0xe82930a  call 0x47E8F0
    std::memset(reinterpret_cast<void*>(r14), 0, 0x28);

    // 0xe82930f..0xe829363  third block
    // 0xe829364  call 0x47E8F0
    std::memset(reinterpret_cast<void*>(r15), 0, 0x28);

    // 0xe829369..0xe8293bd  fourth block
    // 0xe8293be  call 0x47E8F0
    std::memset(reinterpret_cast<void*>(r14), 0, 0x28);

    // 0xe8293c3..0xe829417  fifth block
    // 0xe829418  call 0x47E8F0
    std::memset(reinterpret_cast<void*>(r15), 0, 0x28);

    // 0xe82941d..0xe829471  sixth block
    // 0xe829472  call 0x47E8F0
    std::memset(reinterpret_cast<void*>(r14), 0, 0x28);

    // 0xe829477..0xe8294cb  seventh block
    // 0xe8294cc  call 0x47E8F0
    std::memset(reinterpret_cast<void*>(r15), 0, 0x28);

    // 0xe8294d1..0xe829525  eighth block
    // 0xe829526  call 0x47E8F0
    std::memset(reinterpret_cast<void*>(r14), 0, 0x28);

    // 0xe82952b..0xe829539  call 0xEEC6ED0 (CRT memset) over r14
    // 0xe82953a  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r14), 0, 0x28);

    // 0xe82953f..0xe829561  memset r15 block
    // 0xe829562  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r15), 0, 0x28);

    // 0xe829567..0xe829593  memset
    // 0xe829594  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r14), 0, 0x28);

    // 0xe829599..0xe8295c5  memset
    // 0xe8295c6  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r15), 0, 0x28);

    // 0xe8295ca..0xe8295f4  memset
    // 0xe8295f5  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r14), 0, 0x28);

    // 0xe8295fa..0xe829626  memset
    // 0xe829627  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r15), 0, 0x28);

    // 0xe82962c..0xe82964e  memset
    // 0xe82964f  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r14), 0, 0x28);

    // 0xe829654..0xe82968d  memset
    // 0xe82968e  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r15), 0, 0x28);

    // 0xe829693..0xe8296b5  memset
    // 0xe8296b6  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r14), 0, 0x28);

    // 0xe8296bb..0xe8296ec  memset
    // 0xe8296ed  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r15), 0, 0x28);

    // 0xe8296f2..0xe829714  memset
    // 0xe829715  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r14), 0, 0x28);

    // 0xe82971a..0xe829746  memset
    // 0xe829747  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r15), 0, 0x28);

    // 0xe82974c..0xe829778  memset
    // 0xe829779  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r14), 0, 0x28);

    // 0xe82977e..0xe8297a7  memset
    // 0xe8297a8  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r15), 0, 0x28);

    // 0xe8297ad..0xe8297d3  memset
    // 0xe8297d4  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r14), 0, 0x28);

    // 0xe8297d9..0xe8297ff  memset
    // 0xe829800  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r15), 0, 0x28);

    // 0xe829805..0xe82982e  memset
    // 0xe82982f  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r14), 0, 0x28);

    // 0xe829834..0xe829860  memset
    // 0xe829861  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r15), 0, 0x28);

    // 0xe829866..0xe829892  memset
    // 0xe829893  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r14), 0, 0x28);

    // 0xe829898..0xe8298c1  memset
    // 0xe8298c2  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r15), 0, 0x28);

    // 0xe8298c7..0xe8298e6  memset
    // 0xe8298e7  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r14), 0, 0x28);

    // 0xe8298ec..0xe82991b  memset
    // 0xe82991c  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r15), 0, 0x28);

    // 0xe829921..0xe82994d  memset
    // 0xe82994e  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r14), 0, 0x28);

    // 0xe829953..0xe82997c  memset
    // 0xe82997d  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r15), 0, 0x28);

    // 0xe829982..0xe8299ab  memset
    // 0xe8299ac  call 0xEEC6ED0
    std::memset(reinterpret_cast<void*>(r14), 0, 0x28);

    // 0xe8299b1..0xe8299d2  memset
    // 0xe8299d3  call 0xEEC6EC0
    std::memset(reinterpret_cast<void*>(r15), 0, 0x28);

    // 0xe8299d8..0xe829a1d  compute rdx from r12, call 0xE8360F0
    // 0xe829a1e  call 0xE8360F0
    // (lift callee) sub_e8360f0(...)

    // 0xe829a23..0xe829a82  vcall through data_f99ffa0 (vendor thunk)
    // 0xe829a83  call qword ptr [0xF99FFA0]
    // (vendor boundary) invoke thunk

    // 0xe829a88..0xe829aa6  second vcall
    // 0xe829aa7  call qword ptr [0xF99FFA0]

    // 0xe829aac..0xe829b41  memset/call 0xEEC6EC0
    // 0xe829b42  call 0xEEC6EC0

    // 0xe829b47..0xe829b70  vcall
    // 0xe829b71  call qword ptr [0xF99FFA0]

    // 0xe829b76..0xe829be0  r10 indirect call
    // 0xe829be1  call r10

    // 0xe829be6..0xe829c5f  r11 indirect call
    // 0xe829c60  call r11

    // 0xe829c65..0xe829c7c  vcall
    // 0xe829c7d  call qword ptr [0xF99FFA0]

    // 0xe829c82..0xe829cb4  memset
    // 0xe829cb5  call 0xEEC6ED0

    // 0xe829cba..0xe829da4  vcall
    // 0xe829da5  call qword ptr [0xF99FFA0]

    // 0xe829daa..0xe829ddd  vcall
    // 0xe829dde  call qword ptr [0xF99FFA0]

    // 0xe829de3..0xe829e05  vcall
    // 0xe829e06  call qword ptr [0xF99FFA0]

    // 0xe829e0b..0xe829e36  vcall
    // 0xe829e37  call qword ptr [0xF99FFA0]

    // 0xe829e3c..0xe829ec3  vcall
    // 0xe829ec4  call qword ptr [0xF99FFA0]

    // 0xe829ec9..0xe829f5f  vcall
    // 0xe829f60  call qword ptr [0xF99FFA0]

    // 0xe829f65..0xe82a078  vcall
    // 0xe82a079  call qword ptr [0xF99FFA0]

    // 0xe82a07e..0xe82a0ec  vcall
    // 0xe82a0ed  call qword ptr [0xF99FFA0]

    // 0xe82a0f2..0xe82a131  vcall
    // 0xe82a132  call qword ptr [0xF99FFA0]

    // 0xe82a137..0xe82a1f5  call 0xBC6A9D0
    // 0xe82a1f6  call 0xBC6A9D0

    // 0xe82a1fb..0xe82a392  call 0x47E8F0
    // 0xe82a393  call 0x47E8F0

    // 0xe82a398..0xe82a3c2  memset
    // 0xe82a3c3  call 0xEEC6ED0

    // 0xe82a3c8..0xe82a40e  call 0xE81E1C0
    // 0xe82a40f  call 0xE81E1C0

    // 0xe82a414..0xe82a484  call 0xE81E1C0
    // 0xe82a485  call 0xE81E1C0

    // 0xe82a48a..0xe82a4c3  memset
    // 0xe82a4c4  call 0xEEC6ED0

    // 0xe82a4c9..0xe82a4f1  memset
    // 0xe82a4f2  call 0xEEC6EC0

    // 0xe82a4f7..0xe82a912  tail: write back live registers
    state.rbx = rbx;
    state.rbp = rbp;
    state.r12 = r12;
    state.r13 = r13;
    state.r14 = r14;
    state.r15 = r15;
    state.rsi = rsi;
    state.rdi = rdi;
}

} } // namespace

#if 0
0xe829256  call 0x47E8F0
0xe8292b0  call 0x47E8F0
0xe82930a  call 0x47E8F0
0xe829364  call 0x47E8F0
0xe8293be  call 0x47E8F0
0xe829418  call 0x47E8F0
0xe829472  call 0x47E8F0
0xe8294cc  call 0x47E8F0
0xe829526  call 0x47E8F0
0xe82953a  call 0xEEC6ED0
0xe829562  call 0xEEC6ED0
0xe829594  call 0xEEC6ED0
0xe8295c6  call 0xEEC6ED0
0xe8295f5  call 0xEEC6ED0
0xe829627  call 0xEEC6ED0
0xe82964f  call 0xEEC6ED0
0xe82968e  call 0xEEC6ED0
0xe8296b6  call 0xEEC6ED0
0xe8296ed  call 0xEEC6ED0
0xe829715  call 0xEEC6ED0
0xe829747  call 0xEEC6ED0
0xe829779  call 0xEEC6ED0
0xe8297a8  call 0xEEC6ED0
0xe8297d4  call 0xEEC6ED0
0xe829800  call 0xEEC6ED0
0xe82982f  call 0xEEC6ED0
0xe829861  call 0xEEC6ED0
0xe829893  call 0xEEC6ED0
0xe8298c2  call 0xEEC6ED0
0xe8298e7  call 0xEEC6ED0
0xe82991c  call 0xEEC6ED0
0xe82994e  call 0xEEC6ED0
0xe82997d  call 0xEEC6ED0
0xe8299ac  call 0xEEC6ED0
0xe8299d3  call 0xEEC6EC0
0xe829a1e  call 0xE8360F0
0xe829a83  call qword ptr [0xF99FFA0]
0xe829aa7  call qword ptr [0xF99FFA0]
0xe829b42  call 0xEEC6EC0
0xe829b71  call qword ptr [0xF99FFA0]
0xe829be1  call r10
0xe829c60  call r11
0xe829c7d  call qword ptr [0xF99FFA0]
0xe829cb5  call 0xEEC6ED0
0xe829da5  call qword ptr [0xF99FFA0]
0xe829dde  call qword ptr [0xF99FFA0]
0xe829e06  call qword ptr [0xF99FFA0]
0xe829e37  call qword ptr [0xF99FFA0]
0xe829ec4  call qword ptr [0xF99FFA0]
0xe829f60  call qword ptr [0xF99FFA0]
0xe82a079  call qword ptr [0xF99FFA0]
0xe82a0ed  call qword ptr [0xF99FFA0]
0xe82a132  call qword ptr [0xF99FFA0]
0xe82a1f6  call 0xBC6A9D0
0xe82a393  call 0x47E8F0
0xe82a3c3  call 0xEEC6ED0
0xe82a40f  call 0xE81E1C0
0xe82a485  call 0xE81E1C0
0xe82a4c4  call 0xEEC6ED0
0xe82a4f2  call 0xEEC6EC0
#endif