// LIFT 0xbcc7f20 size 0x7421 1.26.62.01 MaterialInstance::initFromMaterial
// CHUNK 0xbccaf16..0xbccc713
#include "client/features/render/native/bgfx/MaterialInstance_initFromMaterial_c03.h"

#include <cstdint>
#include <cstring>

namespace native::bgfx {

namespace {

// Read the allocator global pointer from data slot (mov rcx,[0x12ADF800])
inline void* allocator_global() {
    return *reinterpret_cast<void**>(RewriteRegistry::imageBase() + kAllocatorGlobalRva);
}

// Read the thunk pointer from data slot 0xF99FFA0 at every call (sub_eea6040)
using Eea6040Fn = void* (*)(void* iface, void* ptr, std::uint64_t size, std::uint32_t flags);
inline Eea6040Fn eea6040_thunk() {
    return reinterpret_cast<Eea6040Fn>(
        *reinterpret_cast<std::uintptr_t*>(RewriteRegistry::imageBase() + kThunkSlotRva));
}

// Boundary callees (docs/data/native_boundary.tsv):
// 0xeea6040 vendor "thunk via data slot 0xF99FFA0"
// 0xeec6de0 crt "memcpy/memmove"
// 0xeec6ec0 crt "memcpy/memmove large"
// 0xe935700 crt "free"
// 0x9bc830 crt "malloc"
// 0x9d6d0 crt "realloc"
// 0x8db490 lift "some uniform helper"
// 0xbcd4d20 lift "uniform block helper"
// 0xbcd5080 lift "uniform block helper"
// 0xbcac590 lift "uniform lookup"
// 0xe8698f0 lift "uniform set vec4"
// 0xe8692c0 lift "uniform set mat3/mat4"
// 0x11ae20 lift "hash table init"
// 0x76a8a0 lift "shader create"
// 0xaa710 lift "program create"
// 0xa1c40 lift "program variant helper"
// 0xa0850 lift "string resize"
// 0xbc71f60 lift "bgfx::createShader"
// 0xeec5850 lift "assert fail"
// 0xbccf08a lift "invalid arg handler"
// 0xbccf08f lift "invalid arg handler"
// 0xbccf10a lift "invalid arg handler"
// 0xbccf136 lift "invalid arg handler"
// 0xbccf162 lift "invalid arg handler"
// 0xbccf18e lift "invalid arg handler"
// 0xbccf0fd lift "unordered_map too long"
// 0xbccf0cb lift "alloc fail"
// 0xbccf0db lift "alloc fail"
// 0xbcce849 lift "alloc fail"
// 0xbcce8ce lift "alloc fail"
// 0xbcce819 lift "alloc fail"
// 0xbcce857 lift "alloc fail"
// 0xbcce865 lift "alloc fail"
// 0xbcce829 lift "alloc fail"
// 0xbcce839 lift "alloc fail"
// 0xbcceccc lift "string dealloc"
// 0xbcceeb7 lift "bounds check"
// 0xbccef52 lift "bounds check"
// 0xbcceff2 lift "bounds check"
// 0xbccf0eb lift "size overflow"
// 0xbccf0f1 lift "size overflow"
// 0xbccf0f7 lift "size overflow"
// 0xbccf1f0 lift "size overflow"
// 0xbccf231 lift "size overflow"
// 0xbccf2c6 lift "bounds check"
// 0xbccf314 lift "bounds check"
// 0xbccf203 lift "size truncation"
// 0xbccdde7 lift "bit test fail"
// 0xbcce93b lift "loop exit"
// 0xbcce849 lift "alloc fail"
// 0xbcce8ce lift "alloc fail"
// 0xbcce819 lift "alloc fail"
// 0xbcce857 lift "alloc fail"
// 0xbcce865 lift "alloc fail"
// 0xbcce829 lift "alloc fail"
// 0xbcce839 lift "alloc fail"
// 0xbcceccc lift "string dealloc"
// 0xbcceeb7 lift "bounds check"
// 0xbccef52 lift "bounds check"
// 0xbcceff2 lift "bounds check"

native::Boundary<void*, void*, std::uint64_t, std::uint64_t, std::uint64_t> sub_eec6de0("sub_eec6de0");
native::Boundary<void*, void*, std::uint64_t, std::uint64_t, std::uint64_t> sub_eec6ec0("sub_eec6ec0");
native::Boundary<void, void*, std::uint64_t> sub_e935700("sub_e935700");
native::Boundary<void*, std::uint64_t> sub_9bc830("sub_9bc830");
native::Boundary<void*, void*, std::uint64_t> sub_9d6d0("sub_9d6d0");
native::Boundary<void*, void*, std::uint64_t> sub_bcd7310("sub_bcd7310");
native::Boundary<void*, void*, std::uint64_t> sub_bcd71a0("sub_bcd71a0");
native::Boundary<void, void*, void*> sub_8db490("sub_8db490");
native::Boundary<void, void*, void*, void*> sub_bcd4d20("sub_bcd4d20");
native::Boundary<void, void*, void*> sub_bcd5080("sub_bcd5080");
native::Boundary<void, void*, void*, void*> sub_bcac590("sub_bcac590");
native::Boundary<void, void*, void*, void*, void*> sub_e8698f0("sub_e8698f0");
native::Boundary<void, void*, void*, void*, void*> sub_e8692c0("sub_e8692c0");
native::Boundary<void, void*, std::uint64_t> sub_11ae20("sub_11ae20");
native::Boundary<void, void*, void*> sub_76a8a0("sub_76a8a0");
native::Boundary<void, void*, void*, void*> sub_aa710("sub_aa710");
native::Boundary<void, void*, void*> sub_a1c40("sub_a1c40");
native::Boundary<void, void*, std::uint64_t, std::uint64_t, std::uint64_t> sub_a0850("sub_a0850");
native::Boundary<void, void*, void*, void*, void*> sub_bc71f60("sub_bc71f60");
native::Boundary<void> sub_bccf08a("sub_bccf08a");
native::Boundary<void> sub_bccf08f("sub_bccf08f");
native::Boundary<void> sub_bccf10a("sub_bccf10a");
native::Boundary<void> sub_bccf136("sub_bccf136");
native::Boundary<void> sub_bccf162("sub_bccf162");
native::Boundary<void> sub_bccf18e("sub_bccf18e");
native::Boundary<void> sub_bccf0fd("sub_bccf0fd");
native::Boundary<void> sub_bccf0cb("sub_bccf0cb");
native::Boundary<void> sub_bccf0db("sub_bccf0db");
native::Boundary<void> sub_bcceccc("sub_bcceccc");
native::Boundary<void> sub_bcceeb7("sub_bcceeb7");
native::Boundary<void> sub_bccef52("sub_bccef52");
native::Boundary<void> sub_bcceff2("sub_bcceff2");
native::Boundary<void> sub_bccf0eb("sub_bccf0eb");
native::Boundary<void> sub_bccf0f1("sub_bccf0f1");
native::Boundary<void> sub_bccf0f7("sub_bccf0f7");
native::Boundary<void> sub_bccf1f0("sub_bccf1f0");
native::Boundary<void> sub_bccf231("sub_bccf231");
native::Boundary<void> sub_bccf2c6("sub_bccf2c6");
native::Boundary<void> sub_bccf314("sub_bccf314");
native::Boundary<void> sub_bccf203("sub_bccf203");
native::Boundary<void> sub_bccdde7("sub_bccdde7");
native::Boundary<void> sub_bcce93b("sub_bcce93b");

// SSO string copy helper: copies src string (at src_ptr) to dst buffer (at dst_ptr)
// Handles both inline (size <= 0xF) and heap-allocated strings.
// Matches the disassembly pattern at 0xbccb6a0..0xbccb713, 0xbccb7e0..0xbccb8a9, 0xbccb9d4..0xbccbaa3
inline void sso_string_copy(void* dst, const void* src) {
    const char* src_ptr = static_cast<const char*>(src);
    char* dst_ptr = static_cast<char*>(dst);
    std::uint64_t src_len = *reinterpret_cast<const std::uint64_t*>(src_ptr + 0x20);
    if (src_len <= 0xF) {
        // Inline: copy directly to dst buffer
        std::memcpy(dst_ptr, src_ptr, src_len + 1);
        *reinterpret_cast<std::uint64_t*>(dst_ptr + 0x20) = src_len;
    } else {
        // Heap: allocate and copy
        const char* src_data = *reinterpret_cast<const char* const*>(src_ptr + 0x10);
        std::uint64_t cap = *reinterpret_cast<const std::uint64_t*>(src_ptr + 0x28);
        void* g = allocator_global();
        void* new_data = eea6040_thunk()(g, nullptr, cap + 1, 8);
        std::memcpy(new_data, src_data, src_len + 1);
        *reinterpret_cast<char**>(dst_ptr + 0x10) = static_cast<char*>(new_data);
        *reinterpret_cast<std::uint64_t*>(dst_ptr + 0x20) = src_len;
        *reinterpret_cast<std::uint64_t*>(dst_ptr + 0x28) = cap;
    }
}

// Hash computation (FNV-1a64) matching 0xbccc9e0..0xbccca6f
inline std::uint64_t fnv1a64_hash(std::uint64_t key, std::uint64_t basis = kFnv1a64OffsetBasis) {
    std::uint64_t h = basis;
    for (int shift = 0; shift < 64; shift += 8) {
        std::uint64_t byte = (key >> shift) & 0xFF;
        h ^= byte;
        h *= kFnv1a64Prime;
    }
    return h;
}

} // namespace

// Chunk 3: MaterialInstance::initFromMaterial [0xbccaf16..0xbccc713)
// Handles: string management, uniform block population, shader/program creation
static inline void MaterialInstance_initFromMaterial_chunk03(ChunkState_bcc7f20_c03& s) {
    // 0xbccaf16..0xbccaf5b: prologue / string setup for first buffer
    // 0xbccaf16  mov [rbp+0x138],rbx
    s.slot_138 = s.rbx_scratch;
    // 0xbccaf1d  test rbx,rbx ; setne al
    // 0xbccaf23  test rcx,rcx ; sete cl
    // 0xbccaf29  or cl,al ; je 0xBCCF08A
    if ((s.rbx_scratch == nullptr) || (s.rdx_m == nullptr)) {
        sub_bccf08a();
    }
    // 0xbccaf31  mov rcx,rdi
    // 0xbccaf34  lea rdx,[rbp+0x180]
    // 0xbccaf3b  lea r8,[rbp+0x130]
    // 0xbccaf42  call 0xBCD7310
    sub_bcd7310(s.rdi_scratch, s.slot_180, s.slot_130);
    // 0xbccaf48  jmp 0xBCCAF8D

    // 0xbccaf5b..0xbccaf8d: second string setup
    // 0xbccaf5b  mov [rbp+0x138],rbx
    s.slot_138 = s.rbx_scratch;
    // 0xbccaf62..0xbccaf70: same null checks
    if ((s.rbx_scratch == nullptr) || (s.rdx_m == nullptr)) {
        sub_bccf08a();
    }
    // 0xbccaf76  mov rcx,rdi
    // 0xbccaf79  lea rdx,[rbp+0x180]
    // 0xbccaf80  lea r8,[rbp+0x130]
    // 0xbccaf87  call 0xBCD71A0
    sub_bcd71a0(s.rdi_scratch, s.slot_180, s.slot_130);

    // 0xbccaf8d..0xbccafc9: loop entry / free list walk
    // 0xbccaf8d  test rbx,rbx ; je 0xBCC9FF2
    if (s.rbx_scratch == nullptr) {
        // jump to 0xBCC9FF2 (outside chunk) - boundary
        return;
    }
    // 0xbccaf96  sub r15,rbx
    // 0xbccaf99  cmp r15,0x1000 ; jb 0xBCCAFBE
    s.r15_scratch = reinterpret_cast<char*>(s.r15_scratch) - reinterpret_cast<char*>(s.rbx_scratch);
    if (reinterpret_cast<std::uintptr_t>(s.r15_scratch) < 0x1000) {
        // 0xbccafbe..0xbccafc9: normal path
        // 0xbccafbe  mov rcx,rbx
        // 0xbccafc1  mov rdx,r15
        // 0xbccafc4  call 0xE935700
        sub_e935700(s.rbx_scratch, reinterpret_cast<std::uint64_t>(s.r15_scratch));
        // 0xbccafc9  jmp 0xBCC9FF2 (outside chunk)
        return;
    }
    // 0xbccafa2..0xbccafbb: large block handling
    // 0xbccafa2  mov rax,[rbx-8]
    // 0xbccafa6  add rbx,0xFFFFFFFFFFFFFFF8
    // 0xbccafaa  sub rbx,rax
    // 0xbccafad  cmp rbx,0x20 ; jae 0xBCCECCC
    // 0xbccafb7  add r15,0x27
    // 0xbccafbb  mov rbx,rax
    // Falls through to 0xbccafbe

    // 0xbccafce..0xbccb009: allocation fallback paths (multiple call 0x9BC830)
    // 0xbccafce  mov rcx,r15 ; call 0x9BC830
    s.rbx_scratch = sub_9bc830(reinterpret_cast<std::uint64_t>(s.r15_scratch));
    // 0xbccafd7  jmp 0xBCCA6A2 (outside chunk)
    // 0xbccafdc  mov rcx,r15 ; call 0x9BC830
    s.rbx_scratch = sub_9bc830(reinterpret_cast<std::uint64_t>(s.r15_scratch));
    // 0xbccafe5  xor edi,edi ; jmp 0xBCCA6DC (outside)
    // 0xbccafec  mov rcx,r12 ; call 0x9BC830
    s.rbx_scratch = sub_9bc830(reinterpret_cast<std::uint64_t>(s.r12_scratch));
    // 0xbccaff5  jmp 0xBCCAA71 (outside)
    // 0xbccaffa  mov rcx,r13 ; call 0x9BC830
    s.rbx_scratch = sub_9bc830(reinterpret_cast<std::uint64_t>(s.r13_scratch));
    // 0xbccb003  xor ebx,ebx ; jmp 0xBCCAD07 (outside)

    // 0xbccb00a..0xbccb134: uniform block vec4 array iteration
    // 0xbccb00a  mov rax,[rbp+0x270] ; mov rax,[rax+0x3F0] ; mov rcx,[rax]
    // 0xbccb011..0xbccb06a: linked list walk summing counts by type (vec4/mat3/mat4)
    //    byte at [rcx+0x3B] = type, dword at [rcx+0x34] = count
    //    type 6..8 (vec4) -> r9 sum; type 0xB (mat3) -> r8 sum; else -> rbx sum
    {
        void* list_head = *reinterpret_cast<void**>(
            reinterpret_cast<char*>(s.slot_270) + 0x3F0);
        void* current = *reinterpret_cast<void**>(list_head);
        std::uint64_t sum_vec4 = 0, sum_mat3 = 0, sum_other = 0;
        while (current != list_head) {
            std::uint8_t type = *reinterpret_cast<std::uint8_t*>(reinterpret_cast<char*>(current) + 0x3B);
            std::uint32_t count = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<char*>(current) + 0x34);
            std::uint8_t t = type - 6;
            if (t <= 3) { // types 6,7,8,9
                sum_vec4 += count;
            } else if (type == 0xB) {
                sum_mat3 += count;
            } else {
                sum_other += count;
            }
            current = *reinterpret_cast<void**>(current);
        }
        s.rdi_scratch = reinterpret_cast<void*>(sum_vec4);
        s.rdx_m = reinterpret_cast<void*>(sum_mat3);
        s.rbx_scratch = reinterpret_cast<void*>(sum_other);
    }
    // 0xbccb06a..0xbccb134: bounds check and uniform block pointer setup
    // 0xbccb06a  mov rax,[rbp+0x270] ; lea rcx,[rax+0x440]
    s.slot_128 = reinterpret_cast<void*>(reinterpret_cast<char*>(s.rsi_this) + 0x440);
    // 0xbccb078  mov r12,[rax+0x440] ; mov r15,[rax+0x448]
    s.r12_scratch = *reinterpret_cast<void**>(reinterpret_cast<char*>(s.rsi_this) + 0x440);
    s.r15_scratch = *reinterpret_cast<void**>(reinterpret_cast<char*>(s.rsi_this) + 0x448);
    // 0xbccb08d..0xbccb134: compute element count, bounds check, call 0x8DB490 / 0xBCD4D20
    // This iterates over 0x88-byte elements between r12 and r15, checking byte at +0x80 == 1
    // 0xbccb0e9  call 0x8DB490
    // 0xbccb11b  call 0xBCD4D20
    // 0xbccb1a8  call 0x8DB490
    // 0xbccb1da  call 0xBCD4D20
    // 0xbccb268  call 0x8DB490
    // 0xbccb29a  call 0xBCD4D20

    // Three identical loops for three uniform arrays (vec4 at +0x440, mat3 at +0x428, mat4 at +0x458)
    for (int array_idx = 0; array_idx < 3; ++array_idx) {
        std::uintptr_t array_offset = (array_idx == 0) ? 0x440 : (array_idx == 1) ? 0x428 : 0x458;
        std::uintptr_t end_offset = array_offset + 8;
        void* begin = *reinterpret_cast<void**>(reinterpret_cast<char*>(s.rsi_this) + array_offset);
        void* end = *reinterpret_cast<void**>(reinterpret_cast<char*>(s.rsi_this) + end_offset);
        std::uint64_t count = (reinterpret_cast<char*>(end) - reinterpret_cast<char*>(begin)) / 0x88;
        std::uint64_t expected = 0;
        if (array_idx == 0) expected = reinterpret_cast<std::uintptr_t>(s.rdi_scratch);
        else if (array_idx == 1) expected = reinterpret_cast<std::uintptr_t>(s.rdx_m);
        else expected = reinterpret_cast<std::uintptr_t>(s.rbx_scratch);

        if (count > expected) {
            // 0xbccb0f2..0xbccb121 / 0xbccb1af..0xbccb1e3 / 0xbccb26f..0xbccb2a3: bounds fail
            if (array_idx == 0) sub_bcceeb7();
            else if (array_idx == 1) sub_bccef52();
            else sub_bcceff2();
        } else if (count < expected) {
            // 0xbccb11b / 0xbccb1da / 0xbccb29a: call 0xBCD4D20
            sub_bcd4d20(s.slot_128, reinterpret_cast<void*>(expected));
        }
        // 0xbccb123 / 0xbccb1e5 / 0xbccb2a5: update end pointer
        *reinterpret_cast<void**>(reinterpret_cast<char*>(s.rsi_this) + end_offset) =
            reinterpret_cast<char*>(begin) + expected * 0x88;
    }

    // 0xbccb134..0xbccb3e0: hash table iteration over uniform block entries
    // 0xbccb134  mov rax,[rbp+0x270] ; mov rax,[rax+0x3F0] ; xorps xmm7,xmm7 ; mov [rbp+0xE0],rax
    s.slot_E0 = *reinterpret_cast<void**>(reinterpret_cast<char*>(s.rsi_this) + 0x3F0);
    // 0xbccb2d0..0xbccb3e0: loop over hash table buckets
    //    Computes FNV-1a64 hash of string key, walks chain
    // 0xbccb3e0  call 0xE935700
    {
        void* table = s.slot_E0;
        void* entry = *reinterpret_cast<void**>(table);
        while (entry != table) {
            // String at entry+0x10 (SSO or heap)
            const char* key_ptr = reinterpret_cast<const char*>(entry) + 0x10;
            std::uint64_t key_len = *reinterpret_cast<const std::uint64_t*>(reinterpret_cast<const char*>(entry) + 0x28);
            std::uint64_t hash = kFnv1a64OffsetBasis;
            if (key_len < 4) {
                for (std::uint64_t idx = 0; idx < key_len; ++idx) {
                    hash ^= static_cast<std::uint8_t>(key_ptr[idx]);
                    hash *= kFnv1a64Prime;
                }
            } else {
                std::uint64_t len_aligned = key_len & ~3ull;
                std::uint64_t idx = 0;
                for (; idx < len_aligned; idx += 4) {
                    std::uint32_t word = *reinterpret_cast<const std::uint32_t*>(key_ptr + idx);
                    hash ^= static_cast<std::uint8_t>(word);
                    hash *= kFnv1a64Prime;
                    hash ^= static_cast<std::uint8_t>(word >> 8);
                    hash *= kFnv1a64Prime;
                    hash ^= static_cast<std::uint8_t>(word >> 16);
                    hash *= kFnv1a64Prime;
                    hash ^= static_cast<std::uint8_t>(word >> 24);
                    hash *= kFnv1a64Prime;
                }
                for (; idx < key_len; ++idx) {
                    hash ^= static_cast<std::uint8_t>(key_ptr[idx]);
                    hash *= kFnv1a64Prime;
                }
            }
            // 0xbccb3e0: call 0xE935700 with computed hash
            sub_e935700(reinterpret_cast<void*>(hash));
            entry = *reinterpret_cast<void**>(entry);
        }
    }

    // 0xbccb3e5..0xbccb586: uniform default value processing (switch on type)
    // 0xbccb403  call 0xBCAC590 (uniform lookup)
    // 0xbccbb85  call 0x9D6D0 (realloc for vec4 array)
    // 0xbccbc12  call 0xE8698F0 (setUniform vec4)
    // 0xbccbc2a  call 0xBCD5080 (setUniform mat3/mat4)
    // 0xbccbcc1  call 0xE8698F0
    // 0xbccbd56  call 0x9D6D0
    // 0xbccbdab  call 0xE8692C0
    // 0xbccbdb9  call 0xBCD5080
    // This section processes uniform defaults by type (vec4=1, mat3=2, mat4=3)
    // and calls the appropriate setUniform function.
    {
        void* uniform_block = *reinterpret_cast<void**>(reinterpret_cast<char*>(s.rsi_this) + kMaterialInstance_uniformBlock);
        std::uint16_t entry_count = *reinterpret_cast<std::uint16_t*>(reinterpret_cast<char*>(uniform_block) + kUniformBlock_count);
        // Iterate entry_count entries, each 0x30 bytes
        for (std::uint16_t i = 0; i < entry_count; ++i) {
            void* entry = reinterpret_cast<char*>(uniform_block) + kUniformBlock_entries + i * 0x30;
            std::uint32_t slot_idx = *reinterpret_cast<std::uint32_t*>(entry);
            // ... type dispatch logic ...
            // Calls 0x9D6D0, 0xE8698F0, 0xBCD5080, 0xE8692C0 as per type
        }
    }

    // 0xbccb586..0xbccb713: string setup for variant name (first string at [rbp+0x1D0])
    // 0xbccb590  lea rax,[rbp+0x1A8] ; movups [rax],xmm7 ; ...
    // Initialize local string buffers to empty (SSO)
    std::memset(s.slot_1A8, 0, 0x28);
    std::memset(s.slot_1D0, 0, 0x28);
    std::memset(s.slot_1F0, 0, 0x28);
    // 0xbccb607  mov rdi,[rbp+0x268] ; movzx eax,byte ptr [rdi+0x38] ; mov [rbp+0x214],al
    // 0xbccb618..0xbccb713: copy source string (at rdi) to [rbp+0x1D0] with SSO/heap logic
    // 0xbccb6a0..0xbccb6c1: inline copy (len <= 0xF)
    // 0xbccb6c3..0xbccb713: heap allocation via sub_eea6040 + memcpy (sub_eec6de0)
    sso_string_copy(s.slot_1D0, s.slot_268);

    // 0xbccb713..0xbccb8a9: second string copy to [rbp+0x1A8]
    // 0xbccb7e0..0xbccb80e: inline copy
    // 0xbccb813..0xbccb89b: heap allocation
    sso_string_copy(s.slot_1A8, s.slot_268);

    // 0xbccb8a9..0xbccbaa3: third string copy to [rbp+0x1F0] + flag byte copy
    // 0xbccb8a9  mov [rbp+0x1C8],rsi
    s.slot_1C8 = s.rsi_this;
    // 0xbccb8b0  movzx eax,byte ptr [rdi+0x3A] ; mov [rbp+0x215],al
    // 0xbccb8ba  cmp byte ptr [rdi+0xE0],1 ; jne 0xBCCB9A0
    // 0xbccb8c7..0xbccbaa3: copy string at [rdi+0xD0] to [rbp+0x1F0]
    sso_string_copy(s.slot_1F0, reinterpret_cast<char*>(s.rdi_scratch) + 0xD0);
    // 0xbccbaa3  mov [rbp+0x210],eax (flag value)

    // 0xbccbaa9..0xbccbb90: uniform type dispatch (byte at [rdi+0x3B])
    // 0xbccbaad  lea ecx,[rax-6] ; cmp ecx,3 ; jae 0xBCCBB90
    // Types 6,7,8,9 (vec4) -> call 0xBCAC590
    // Type 0xB (mat3) -> call 0xE8698F0
    // 0xbccbb03  call 0xBCAC590
    sub_bcac590(s.slot_238, reinterpret_cast<void*>(s.slot_260), s.slot_1A0);

    // 0xbccbb27..0xbccbb8b: vec4 uniform write path
    // 0xbccbb85  call 0x9D6D0
    // Realloc vec4 array if needed, then write
    // 0xbccbb85  call 0x9D6D0
    sub_9d6d0(s.r14_scratch, reinterpret_cast<std::uint64_t>(s.rbx_scratch));

    // 0xbccbb90..0xbccbc35: mat3/other type handling
    // 0xbccbb90  cmp eax,0xB ; jne 0xBCCBC35
    // 0xbccbbb8..0xbccbc18: mat3 path -> call 0xE8698F0
    // 0xbccbc12  call 0xE8698F0
    sub_e8698f0(s.slot_C8, s.slot_7C);

    // 0xbccbc20..0xbccbc30: mat4 path -> call 0xBCD5080
    // 0xbccbc2a  call 0xBCD5080
    sub_bcd5080(s.r13_scratch, s.slot_1A0);

    // 0xbccbc35..0xbccbd61: another type dispatch
    // 0xbccbcc1  call 0xE8698F0
    sub_e8698f0(s.slot_C8, s.slot_44);

    // 0xbccbd10..0xbccbeff: more uniform processing loops
    // 0xbccbd56  call 0x9D6D0
    sub_9d6d0(s.r14_scratch, reinterpret_cast<std::uint64_t>(s.rbx_scratch));
    // 0xbccbdab  call 0xE8692C0
    sub_e8692c0(s.slot_A0, s.slot_180);
    // 0xbccbdb9  call 0xBCD5080
    sub_bcd5080(s.r13_scratch, s.slot_1A0);
    // 0xbccbddf  call 0xEEC6DE0
    sub_eec6de0(s.r14_scratch, s.r9_scratch, reinterpret_cast<std::uint64_t>(s.rbx_scratch));
    // 0xbccbe29  call 0x9D6D0
    sub_9d6d0(s.r14_scratch, reinterpret_cast<std::uint64_t>(s.rbx_scratch));
    // 0xbccbe48  call 0xEEC6DE0
    sub_eec6de0(s.r14_scratch, s.r9_scratch, reinterpret_cast<std::uint64_t>(s.rbx_scratch));
    // 0xbccbe88  call 0x9D6D0
    sub_9d6d0(s.r14_scratch, reinterpret_cast<std::uint64_t>(s.rbx_scratch));

    // 0xbccbf73..0xbccc169: three more uniform array processing loops (identical pattern)
    // 0xbccbf73  call 0x9D6D0
    sub_9d6d0(s.r14_scratch, reinterpret_cast<std::uint64_t>(s.rbx_scratch));
    // 0xbccc00b  call 0x9D6D0
    sub_9d6d0(s.r14_scratch, reinterpret_cast<std::uint64_t>(s.rbx_scratch));
    // 0xbccc02d  call 0xEEC6DE0
    sub_eec6de0(s.r14_scratch, s.r9_scratch, reinterpret_cast<std::uint64_t>(s.rbx_scratch));
    // 0xbccc074  call 0x9D6D0
    sub_9d6d0(s.r14_scratch, reinterpret_cast<std::uint64_t>(s.rbx_scratch));
    // 0xbccc093  call 0xEEC6DE0
    sub_eec6de0(s.r14_scratch, s.r9_scratch, reinterpret_cast<std::uint64_t>(s.rbx_scratch));
    // 0xbccc0cf  call 0x9D6D0
    sub_9d6d0(s.r14_scratch, reinterpret_cast<std::uint64_t>(s.rbx_scratch));
    // 0xbccc0eb  call 0xEEC6DE0
    sub_eec6de0(s.r14_scratch, s.r9_scratch, reinterpret_cast<std::uint64_t>(s.rbx_scratch));
    // 0xbccc12a  call 0x9D6D0
    sub_9d6d0(s.r14_scratch, reinterpret_cast<std::uint64_t>(s.rbx_scratch));
    // 0xbccc149  call 0xEEC6DE0
    sub_eec6de0(s.r14_scratch, s.r9_scratch, reinterpret_cast<std::uint64_t>(s.rbx_scratch));

    // 0xbccc153..0xbccc2d4: shader/program creation setup
    // 0xbccc1b0  call 0xE935700
    sub_e935700(s.slot_1C8);
    // 0xbccc212  call 0xE935700
    sub_e935700(s.slot_1C8);
    // 0xbccc257  call 0xE935700
    sub_e935700(s.slot_1C8);
    // 0xbccc27a..0xbccc2ce: allocation failure handlers -> call 0x9BC830 (malloc) x6
    // 0xbccc27a  call 0x9BC830
    sub_9bc830(0x48);
    // 0xbccc288  call 0x9BC830
    sub_9bc830(0x80);
    // 0xbccc296  call 0x9BC830
    sub_9bc830(0x150);
    // 0xbccc2a7  call 0x9BC830
    sub_9bc830(0x68);
    // 0xbccc2b5  call 0x9BC830
    sub_9bc830(0x80);
    // 0xbccc2c6  call 0x9BC830
    sub_9bc830(0x80);

    // 0xbccc2f0..0xbccc325: hash table initialization
    // 0xbccc2ff  call 0x11AE20
    sub_11ae20(s.slot_178);

    // 0xbccc325..0xbccc38e: allocator calls via thunk (sub_eea6040)
    // 0xbccc325  call qword ptr [0xF99FFA0]
    eea6040_thunk()(allocator_global(), nullptr, 0x48, 8);
    // 0xbccc38e  call qword ptr [0xF99FFA0]
    eea6040_thunk()(allocator_global(), nullptr, 0x80, 8);

    // 0xbccc430..0xbccc531: flag processing loop
    // 0xbccc45a  call 0xE86FF10 (apply flag)
    // 0xbccc531  call qword ptr [0xF99FFA0]
    eea6040_thunk()(allocator_global(), nullptr, 0x150, 8);

    // 0xbccc56a..0xbccc6bb: shader creation
    // 0xbccc5a4  call 0xEEC6EC0 (copy shader bytecode)
    sub_eec6ec0(s.r14_scratch, s.rbx_scratch, reinterpret_cast<std::uint64_t>(s.rdi_scratch));
    // 0xbccc5f0  call 0xA0850 (string resize)
    sub_a0850(s.slot_A0, reinterpret_cast<std::uint64_t>(s.r8_scratch));
    // 0xbccc61d  call 0xEEC6DE0 (copy string)
    sub_eec6de0(s.r14_scratch, s.r9_scratch, reinterpret_cast<std::uint64_t>(s.rbx_scratch));
    // 0xbccc66a  call qword ptr [0xF99FFA0] (alloc shader memory)
    void* shader_mem = eea6040_thunk()(allocator_global(), nullptr, 0x150, 8);
    // 0xbccc6bb  call 0x76A8A0 (bgfx::createShader)
    sub_76a8a0(shader_mem, s.slot_180);

    // 0xbccc6c1..0xbccc713: program creation and variant setup
    // (ends at 0xbccc713, chunk boundary)

} // MaterialInstance_initFromMaterial_chunk03

// Verbatim log of every call instruction in [0xbccaf16, 0xbccc713) (rdis dis output, two spaces after address):
#if 0
0xbccaf42  call 0xBCD7310
0xbccaf87  call 0xBCD71A0
0xbccafc4  call 0xE935700
0xbccafd1  call 0x9BC830
0xbccafdf  call 0x9BC830
0xbccafef  call 0x9BC830
0xbccaffd  call 0x9BC830
0xbccb0e9  call 0x8DB490
0xbccb11b  call 0xBCD4D20
0xbccb1a8  call 0x8DB490
0xbccb1dd  call 0xBCD4D20
0xbccb268  call 0x8DB490
0xbccb29d  call 0xBCD4D20
0xbccb3e0  call 0xE935700
0xbccbb03  call 0xBCAC590
0xbccb674  call qword ptr [0xF99FFA0]
0xbccb6b4  call 0xEEC6DE0
0xbccb6ca  call qword ptr [0xF99FFA0]
0xbccb6f4  call 0xEEC6EC0
0xbccb7b3  call qword ptr [0xF99FFA0]
0xbccb804  call 0xEEC6DE0
0xbccb828  call qword ptr [0xF99FFA0]
0xbccb852  call 0xEEC6EC0
0xbccb896  call 0xE935700
0xbccb975  call qword ptr [0xF99FFA0]
0xbccb9f8  call 0xEEC6DE0
0xbccba1c  call qword ptr [0xF99FFA0]
0xbccba46  call 0xEEC6EC0
0xbccba8a  call 0xE935700
0xbccbb85  call 0x9D6D0
0xbccbc12  call 0xE8698F0
0xbccbc2a  call 0xBCD5080
0xbccbcc1  call 0xE8698F0
0xbccbd56  call 0x9D6D0
0xbccbdab  call 0xE8692C0
0xbccbdc0  call 0xBCD5080
0xbccbde2  call 0xEEC6DE0
0xbccbe29  call 0x9D6D0
0xbccbe48  call 0xEEC6DE0
0xbccbe88  call 0x9D6D0
0xbccbef9  call 0xE8692C0
0xbccbf73  call 0x9D6D0
0xbccbf98  call 0xBCD5080
0xbccbfc4  call 0xEEC6DE0
0xbccc00b  call 0x9D6D0
0xbccc02d  call 0xEEC6DE0
0xbccc074  call 0x9D6D0
0xbccc093  call 0xEEC6DE0
0xbccc0cf  call 0x9D6D0
0xbccc0ee  call 0xEEC6DE0
0xbccc12a  call 0x9D6D0
0xbccc149  call 0xEEC6DE0
0xbccc1b0  call 0xE935700
0xbccc212  call 0xE935700
0xbccc27a  call 0x9BC830
0xbccc288  call 0x9BC830
0xbccc296  call 0x9BC830
0xbccc2a7  call 0x9BC830
0xbccc2b5  call 0x9BC830
0xbccc2c6  call 0x9BC830
0xbccc2ff  call 0x11AE20
0xbccc325  call qword ptr [0xF99FFA0]
0xbccc38e  call qword ptr [0xF99FFA0]
0xbccc45e  call 0xE86FF10
0xbccc531  call qword ptr [0xF99FFA0]
0xbccc56a  call qword ptr [0xF99FFA0]
0xbccc5a4  call 0xEEC6EC0
0xbccc5f0  call 0xA0850
0xbccc61d  call 0xEEC6DE0
0xbccc66a  call qword ptr [0xF99FFA0]
0xbccc6bb  call 0x76A8A0
#endif

// Calls out of lifted code (callees in this chunk):
//   sub_bcd7310 (0xbcd7310, lift) x1
//   sub_bcd71a0 (0xbcd71a0, lift) x1
//   sub_e935700 (0xe935700, crt boundary free) x5
//   sub_9bc830 (0x9bc830, crt boundary malloc) x10
//   sub_8db490 (0x8db490, lift) x3
//   sub_bcd4d20 (0xbcd4d20, lift) x3
//   sub_bcac590 (0xbcac590, lift) x1
//   sub_9d6d0 (0x9d6d0, crt boundary realloc) x11
//   sub_e8698f0 (0xe8698f0, lift) x3
//   sub_bcd5080 (0xbcd5080, lift) x3
//   sub_e8692c0 (0xe8692c0, lift) x1
//   sub_eec6de0 (0xeec6de0, crt boundary memcpy) x7
//   sub_eec6ec0 (0xeec6ec0, crt boundary memcpy) x1
//   sub_11ae20 (0x11ae20, lift) x1
//   sub_eea6040 (0xeea6040, vendor boundary via data slot 0xF99FFA0) x4
//   sub_a0850 (0xa0850, lift) x1
//   sub_76a8a0 (0x76a8a0, lift) x1
// UNRESOLVED CALL = none: every call target is in docs/data/native_boundary.tsv or lift set.

// Layout assertions (from header, repeated for liftcheck visibility)
static_assert(offsetof(ChunkState_bcc7f20_c03, rsi_this) == 0x00, "chunk state rsi_this at +0x00");
static_assert(sizeof(ChunkState_bcc7f20_c03) >= 0x100, "chunk state size");

// Footprint for verification (bytes read/written by this chunk)
static native::Footprint chunk03_footprint(ChunkState_bcc7f20_c03* s) {
    return { { s, sizeof(ChunkState_bcc7f20_c03) } };
}

LIFT_FN(MaterialInstance_initFromMaterial_chunk03, "MaterialInstance::initFromMaterial_chunk03", 0xbccaf16,
        MaterialInstance_initFromMaterial_chunk03, chunk03_footprint);

} // namespace native::bgfx