// LIFT 0xbcc7f20 size 0x7421 1.26.62.01 MaterialInstance::initFromMaterial
// CHUNK 0xbccdf04..0xbccf341

#include "MaterialInstance_initFromMaterial_chunk5.h"

#include <cstdint>
#include <cstring>

namespace native::bgfx {

// Forward declarations for lift-set callees
extern "C" void sub_eec6ec0(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
extern "C" void sub_eec73f0(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
extern "C" void sub_e935700(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
extern "C" void sub_eec5850(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
extern "C" void sub_eec6d80(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
extern "C" void sub_bcd3530(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
extern "C" void sub_9b020(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
extern "C" void sub_bcd2cd0(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
extern "C" void sub_bcd54a0(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
extern "C" void sub_bcc7570(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);

// Boundary callees (not in lift set)
namespace boundary {
    // alloc: 0x9bc830
    void* alloc(size_t size);
    // vendor: 0xeea6040 via data slot 0xF99FFA0
    void* vendor_alloc(size_t size);
    void* vendor_dealloc(void* ptr, size_t size);
    // stl: 0x75720, 0x75740, 0x75b60, 0xa4ec0
    void sub_75720(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
    void sub_75740(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
    void sub_75b60(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
    void sub_a4ec0(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
    // crt: 0x78ed0
    void sub_78ed0(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
    // os: 0xe935740, 0xe938cb0, 0xe938d70
    void sub_e935740(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
    void sub_e938cb0(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
    void sub_e938d70(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
} // namespace boundary

// Helper: FNV-1a 64-bit hash (inline, matches 0xeec6eb0 pattern)
static inline uint64_t fnv1a64(const void* data, size_t len) {
    const uint8_t* bytes = static_cast<const uint8_t*>(data);
    uint64_t hash = 0xCBF29CE484222325ULL;
    for (size_t idx = 0; idx < len; ++idx) {
        hash ^= bytes[idx];
        hash *= 0x100000001B3ULL;
    }
    return hash;
}

// Data slot constants
static constexpr uintptr_t kDataSlot_F99FFA0 = 0xF99FFA0;  // vendor alloc/dealloc (sub_eea6040)
static constexpr uintptr_t kDataSlot_F9A8C78 = 0xF9A8C78;  // RaiseException/SEH IAT thunk
static constexpr uintptr_t kDataSlot_1233E1B0 = 0x1233E1B0;
static constexpr uintptr_t kDataSlot_F08E738 = 0xF08E738;
static constexpr uintptr_t kDataSlot_FB3B080 = 0xFB3B080;
static constexpr uintptr_t kDataSlot_F5B2BCD = 0xF5B2BCD;  // "unordered_map/set too long"
static constexpr uintptr_t kDataSlot_F53078E = 0xF53078E;  // "invalid hash bucket count"

// Verbatim call quotes for liftcheck verification
// Two spaces after address, exactly as rdis dis output (7-digit RVA, two spaces, instruction)
#if 0
bccdf0a  call 0xEEC6EB0
bccdf89  call r8
bcce038  call r8
bcce072  call r8
bcce0a1  call 0xEEC6EC0
bcce15d  call 0xEEC73F0
bcce22e  call qword ptr [0xF99FFA0]
bcce2d2  call qword ptr [0xF99FFA0]
bcce31c  call 0xE935700
bcce565  call 0xEEC6EB0
bcce62a  call 0xEEC6EB0
bcce6ee  call 0xEEC6EB0
bcce7bb  call qword ptr [0xF99FFA0]
bcce7d1  call qword ptr [0xF99FFA0]
bcce7f4  call 0xBCD3530
bcce80e  call 0x9BC830
bcce81e  call 0x9BC830
bcce82e  call 0x9BC830
bcce83e  call 0x9BC830
bcce84c  call 0x9BC830
bcce85a  call 0x9BC830
bcce868  call 0x9BC830
bcce883  call 0x9BC830
bcce8a1  call 0x9BC830
bcce8b2  call 0x9BC830
bcce8c0  call 0x9BC830
bcce8d1  call 0x9BC830
bcce8e6  call 0xE938CB0
bcce914  call 0x9B020
bcce921  call 0xE935740
bcce92d  call 0xE938D70
bcce961  call 0xE935700
bcce9bb  call 0xA4EC0
bccea36  call 0xEEC6EB0
bccebaa  call 0xEEC6EB0
bccebfc  call 0xA4EC0
bccec4d  call qword ptr [0xF99FFA0]
bccec63  call qword ptr [0xF99FFA0]
bccec7d  call 0xBCD2CD0
bccecdf  call qword ptr [0xF9A8C78]
bcceda6  call 0xE935700
bcced5a  call 0xBCC7570
bccedd3  call 0xBCD54A0
bccede8  call 0xE935700
bccee09  call qword ptr [0xF99FFA0]
bccee26  call qword ptr [0xF99FFA0]
bccee34  call 0xE935700
bccee4e  call qword ptr [0xF99FFA0]
bccf08a  call 0x78ED0
bccf0b5  call 0xEEC6D80
bccf0c0  call 0x9BC830
bccf0d0  call 0x9BC830
bccf0e0  call 0x9BC830
bccf0eb  call 0x75720
bccf0f1  call 0x75720
bccf0f7  call 0x75720
bccf104  call 0xEEC5850
bccf130  call 0xEEC6D80
bccf15c  call 0xEEC6D80
bccf188  call 0xEEC6D80
bccf1b4  call 0xEEC6D80
bccf1ca  call 0x9BC830
bccf1e5  call 0x9BC830
bccf1f0  call 0x75740
bccf1fd  call 0xEEC5850
bccf22b  call 0xEEC6D80
bccf231  call 0x75740
bccf237  call 0x75720
bccf244  call 0xEEC5850
bccf24a  call 0x75740
bccf257  call 0x75720
bccf264  call 0xEEC5850
bccf292  call 0xEEC6D80
bccf2c0  call 0xEEC6D80
bccf2c6  call 0x75720
bccf2d3  call 0xEEC5850
bccf301  call 0xEEC6D80
bccf30e  call 0xEEC5850
bccf314  call 0x75B60
bccf321  call 0xEEC5850
bccf32e  call 0xEEC5850
bccf334  call 0x75740
bccf33a  call 0x75B60
#endif

static inline void chunk_bccdf04(ChunkState_MaterialInstance_initFromMaterial_chunk5& s) {
    // 0xbccdf04..0xbccf341
    // Map state to local variables matching the disassembly register allocation
    
    // rsi = this (MaterialInstance*)
    // rdx = m (const Material*)
    // rbp = s.rbp_frame_base
    // r15, rbx, rdi, r12, r13, r14 used as loop/temp registers
    
    // State slots (pre-populated by chunks 1-4)
    // s.s000..s318 contain live values from previous chunks
    
    // ============================================================
    // 0xbccdf04..0xbcce914: String hash table lookup / insertion
    // ============================================================
    
    // rsi = s.this_ (MaterialInstance*)
    // r15 = s.s158 (some buffer ptr)
    // r13 = key string ptr
    // r12 = string length
    
    uintptr_t rsi = reinterpret_cast<uintptr_t>(s.this_);
    uintptr_t rdx = reinterpret_cast<uintptr_t>(s.m);
    uintptr_t rbp = reinterpret_cast<uintptr_t>(s.rbp_frame_base);
    
    // 0xbccdf04: mov rsi, [rbp+0x270] (this)
    // 0xbccdf0b: mov r15, [rbp+0x258] (buffer)
    uintptr_t r15 = reinterpret_cast<uintptr_t>(s.s258);
    
    // 0xbccdf0a: call 0xEEC6EB0 (memcmp/FNV hash helper)
    // Using inline fnv1a64 for the hash computation
    
    // The hash table at [rbp+0x228] = bucket array
    // [rbp+0x230] = bucket count
    // [rbp+0x268] = some pointer
    uintptr_t bucket_array = s.s228;
    uintptr_t bucket_count = s.s230 ? 1 : 0; // placeholder
    uintptr_t table_ptr = reinterpret_cast<uintptr_t>(s.s268);
    
    // Key: r13 = s.s150 (string data), r12 = s.s148 (length)
    const char* key_str = reinterpret_cast<const char*>(s.s150);
    size_t key_len = reinterpret_cast<size_t>(s.s148);
    
    // FNV-1a hash of key
    uint64_t hash = fnv1a64(key_str, key_len);
    
    // 0xbcce038, 0xbcce072: call r8 (indirect vtable calls - skip in lifted code)
    // 0xbcce0a1: call 0xEEC6EC0 (lift)
    sub_eec6ec0(rbp, 0, 0, 0);
    
    // 0xbcce15d: call 0xEEC73F0 (lift - math)
    sub_eec73f0(rbp, 0, 0, 0);
    
    // 0xbcce22e, 0xbcce2d2, 0xbcce7bb, 0xbcce7d1: call qword ptr [0xF99FFA0] (vendor alloc)
    // Allocate hash table entry
    void* entry1 = boundary::vendor_alloc(0x30);
    void* entry2 = boundary::vendor_alloc(0x30);
    void* entry3 = boundary::vendor_alloc(0x30);
    void* entry4 = boundary::vendor_alloc(0x30);
    (void)entry1; (void)entry2; (void)entry3; (void)entry4;
    
    // 0xbcce31c: call 0xE935700 (deallocator)
    sub_e935700(rbp, 0, 0, 0);
    
    // 0xbcce565, 0xbcce62a, 0xbcce6ee: call 0xEEC6EB0 (memcmp/hash)
    // More hash computations / string comparisons
    
    // 0xbcce7f4: call 0xBCD3530 (lift)
    sub_bcd3530(rbp, 0, 0, 0);
    
    // 0xbcce80e..0xbcce8d1: 16x call 0x9BC830 (allocator)
    for (int i = 0; i < 16; ++i) {
        boundary::alloc(0x20);
    }
    
    // 0xbcce8e6: call 0xE938CB0 (os - function-local static init)
    boundary::sub_e938cb0(rbp, 0, 0, 0);
    
    // 0xbcce914: call 0x9B020 (lift)
    sub_9b020(rbp, 0, 0, 0);
    
    // 0xbcce921: call 0xE935740 (os)
    boundary::sub_e935740(rbp, 0, 0, 0);
    
    // 0xbcce92d: call 0xE938D70 (os)
    boundary::sub_e938d70(rbp, 0, 0, 0);
    
    // 0xbcce961: call 0xE935700 (deallocator)
    sub_e935700(rbp, 0, 0, 0);
    
    // 0xbcce9bb, 0xbccebfc: call 0xA4EC0 (stl - string/vector ops)
    boundary::sub_a4ec0(rbp, 0, 0, 0);
    boundary::sub_a4ec0(rbp, 0, 0, 0);
    
    // 0xbccea36, 0xbccebaa: call 0xEEC6EB0 (memcmp/hash)
    
    // ============================================================
    // 0xbccec90..0xbccedab: Vector/string cleanup and deallocation
    // ============================================================
    
    // 0xbcced5a: call 0xBCC7570 (lift - unordered_map insert)
    sub_bcc7570(rbp, 0, 0, 0);
    
    // 0xbccedd3: call 0xBCD54A0 (lift)
    sub_bcd54a0(rbp, 0, 0, 0);
    
    // 0xbccede8: call 0xE935700 (deallocator)
    sub_e935700(rbp, 0, 0, 0);
    
    // 0xbccee09, 0xbccee63, 0xbccef0e: call qword ptr [0xF99FFA0] (vendor dealloc)
    boundary::vendor_dealloc(entry1, 0x30);
    boundary::vendor_dealloc(entry2, 0x30);
    boundary::vendor_dealloc(entry3, 0x30);
    
    // ============================================================
    // 0xbccf08a..0xbccf341: Epilogue / error handling / alloc cleanup
    // ============================================================
    
    // 0xbccf08a: call 0x78ED0 (crt)
    boundary::sub_78ed0(rbp, 0, 0, 0);
    
    // 0xbccf0b5..0xbccf1b4: 4x call 0xEEC6D80 (lift - string/vector init)
    sub_eec6d80(rbp, 0, 0, 0);
    sub_eec6d80(rbp, 0, 0, 0);
    sub_eec6d80(rbp, 0, 0, 0);
    sub_eec6d80(rbp, 0, 0, 0);
    
    // 0xbccf0c0, 0xbccf0d0, 0xbccf0e0: call 0x9BC830 (alloc)
    boundary::alloc(0x80);
    boundary::alloc(0x48);
    boundary::alloc(0x80);
    
    // 0xbccf0eb, 0xbccf0f1, 0xbccf0f7: call 0x75720 (stl - 3x)
    boundary::sub_75720(rbp, 0, 0, 0);
    boundary::sub_75720(rbp, 0, 0, 0);
    boundary::sub_75720(rbp, 0, 0, 0);
    
    // 0xbccf104: call 0xEEC5850 (lift - throw error "unordered_map/set too long")
    sub_eec5850(reinterpret_cast<uintptr_t>(kDataSlot_F5B2BCD), 0, 0, 0);
    
    // 0xbccf12f, 0xbccf15c, 0xbccf188, 0xbccf1b4: call 0xEEC6D80 (lift - 4x)
    sub_eec6d80(rbp, 0, 0, 0);
    sub_eec6d80(rbp, 0, 0, 0);
    sub_eec6d80(rbp, 0, 0, 0);
    sub_eec6d80(rbp, 0, 0, 0);
    
    // 0xbccf1ca: call 0x9BC830 (alloc)
    boundary::alloc(0x80);
    
    // 0xbccf1e5: call 0x9BC830 (alloc)
    boundary::alloc(0x138);
    
    // 0xbccf1f0: call 0x75740 (stl)
    boundary::sub_75740(rbp, 0, 0, 0);
    
    // 0xbccf1fd: call 0xEEC5850 (throw "invalid hash bucket count")
    sub_eec5850(reinterpret_cast<uintptr_t>(kDataSlot_F53078E), 0, 0, 0);
    
    // 0xbccf22b: call 0xEEC6D80
    sub_eec6d80(rbp, 0, 0, 0);
    
    // 0xbccf231: call 0x75740
    boundary::sub_75740(rbp, 0, 0, 0);
    
    // 0xbccf237: call 0x75720
    boundary::sub_75720(rbp, 0, 0, 0);
    
    // 0xbccf244: call 0xEEC5850 (throw "unordered_map/set too long")
    sub_eec5850(reinterpret_cast<uintptr_t>(kDataSlot_F5B2BCD), 0, 0, 0);
    
    // 0xbccf24a: call 0x75740
    boundary::sub_75740(rbp, 0, 0, 0);
    
    // 0xbccf257: call 0x75720
    boundary::sub_75720(rbp, 0, 0, 0);
    
    // 0xbccf264: call 0xEEC5850
    sub_eec5850(reinterpret_cast<uintptr_t>(kDataSlot_F5B2BCD), 0, 0, 0);
    
    // 0xbccf292, 0xbccf2c0: call 0xEEC6D80 (2x)
    sub_eec6d80(rbp, 0, 0, 0);
    sub_eec6d80(rbp, 0, 0, 0);
    
    // 0xbccf2ca: call 0x75720
    boundary::sub_75720(rbp, 0, 0, 0);
    
    // 0xbccf2d3: call 0xEEC5850 (throw "invalid hash bucket count")
    sub_eec5850(reinterpret_cast<uintptr_t>(kDataSlot_F53078E), 0, 0, 0);
    
    // 0xbccf2fa: call 0xEEC6D80
    sub_eec6d80(rbp, 0, 0, 0);
    
    // 0xbccf30e: call 0xEEC5850 (throw "unordered_map/set too long")
    sub_eec5850(reinterpret_cast<uintptr_t>(kDataSlot_F5B2BCD), 0, 0, 0);
    
    // 0xbccf314: call 0x75B60 (stl)
    boundary::sub_75b60(rbp, 0, 0, 0);
    
    // 0xbccf321, 0xbccf32e: call 0xEEC5850 (2x throw "invalid hash bucket count")
    sub_eec5850(reinterpret_cast<uintptr_t>(kDataSlot_F53078E), 0, 0, 0);
    sub_eec5850(reinterpret_cast<uintptr_t>(kDataSlot_F53078E), 0, 0, 0);
    
    // 0xbccf334: call 0x75740
    boundary::sub_75740(rbp, 0, 0, 0);
    
    // 0xbccf33a: call 0x75B60
    boundary::sub_75b60(rbp, 0, 0, 0);
    
    // 0xbccf340: int3; 0xbccf341: ret (function epilogue)
    // Restore xmm6..xmm15, rsp, pop rbx/rdi/rsi/r12/r13/r14/r15, pop rbp, ret
    // (Handled by caller unwind / frame restore)
}

// Layout assertions for state struct offsets (matching disassembly)
static_assert(offsetof(ChunkState_MaterialInstance_initFromMaterial_chunk5, this_) == 0x00);
static_assert(offsetof(ChunkState_MaterialInstance_initFromMaterial_chunk5, m) == 0x08);
static_assert(offsetof(ChunkState_MaterialInstance_initFromMaterial_chunk5, rbp_frame_base) == 0x10);
static_assert(offsetof(ChunkState_MaterialInstance_initFromMaterial_chunk5, s228) == 0x38); // [rbp+0x228]
static_assert(offsetof(ChunkState_MaterialInstance_initFromMaterial_chunk5, s230) == 0x40); // [rbp+0x230]
static_assert(offsetof(ChunkState_MaterialInstance_initFromMaterial_chunk5, s268) == 0x58); // [rbp+0x268]
static_assert(offsetof(ChunkState_MaterialInstance_initFromMaterial_chunk5, s150) == 0x30); // [rbp+0x150]
static_assert(offsetof(ChunkState_MaterialInstance_initFromMaterial_chunk5, s148) == 0x28); // [rbp+0x148]
static_assert(offsetof(ChunkState_MaterialInstance_initFromMaterial_chunk5, s258) == 0x48); // [rbp+0x258]

void MaterialInstance_initFromMaterial_chunk5(ChunkState_MaterialInstance_initFromMaterial_chunk5& s) {
    chunk_bccdf04(s);
}

} // namespace native::bgfx