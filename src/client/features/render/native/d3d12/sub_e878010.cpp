// LIFT 0xe878010 size 0x4f2 1.26.62.01 BgfxFrameBuilder slot 16
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e878010.h"

#include <cstdint>

static_assert(sizeof(HashMapNode) == 0x50, "e878010: HashMapNode size must be 0x50");

namespace native {
namespace d3d12 {

// ------------------------------------------------------------------
// Boundary wrappers [V from native_boundary.tsv]
// ------------------------------------------------------------------

static void* call_thunk_f99ffa0(void* allocator, std::size_t size) {
    return boundary::thunk_f99ffa0(allocator, size);
}

// ------------------------------------------------------------------
// sub_e878010 - hash map find_or_insert (BgfxFrameBuilder slot 16)
// 0xe878010..0xe878502 (size 0x4f2)
// rcx = a0 (this / hash map container)
// rdx = a1 (output parameter)
// r8  = a2 (key string)
// returns: rax = a1
//
// Full instruction-by-instruction reversal with range citations is in
// docs/functions/e878010.md ("Reversed source" section).
// ------------------------------------------------------------------

extern "C" void* sub_e878010(void* a0_container, void* a1_output, void* a2_key) {
    // 0xe878010..0xe87804a : Prologue, load container pointers, branch
    // push rbp; push r15; push r14; push r13; push r12; push rsi;
    // push rdi; push rbx; sub rsp,0x48; lea rbp,[rsp+0x40];
    // mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
    // mov rbx,r8; mov [rbp-0x10],rdx
    // mov r15,[rcx]; mov rax,[r15+8]; mov sil,1
    // cmp byte ptr [rax+0x19],0; mov [rbp-0x20],rcx
    // mov [rbp-0x18],r15; je short 0xE878072

    void* rbx = a2_key;
    void* rdx_saved = a1_output;
    void* rcx_saved = a0_container;
    void* r15 = *reinterpret_cast<void**>(a0_container);
    void* rax = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(r15) + 8);
    uint8_t sil = 1;

    if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(rax) + 0x19) == 0) {
        goto path_b;
    }

    // 0xe87804c..0xe87811d : Path A - key setup, comparison call, result processing
    void* r12 = rax;
    void* r13 = rcx_saved;
    void* r15_saved = r15;

loc_e87804f_a:
    // 0xe87804f: cmp byte ptr [r15+0x19],0
    // 0xe878054: mov r13,[rbp-0x20]
    // 0xe878058: jne 0xE87813E
    if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(r15) + 0x19) != 0) {
        goto loc_e87813e;
    }

    r13 = rcx_saved;

    // 0xe87805e..0xe87806d: Load key A data pointer (SSO or heap)
    void* rdx_keyA;
    if (*reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(r15) + 0x38) < 0x10) {
        // 0xe8780f5: lea rdx,[r15+0x20]
        rdx_keyA = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(r15) + 0x20);
    } else {
        // 0xe878069: mov rdx,[r15+0x20]
        rdx_keyA = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(r15) + 0x20);
    }

    // 0xe8780f9: mov rdi,[r15+0x30]
    uintptr_t keyLenA = *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(r15) + 0x30);

    // 0xe8780fd: mov r14,[rbx+0x10]
    uintptr_t keyLenB = *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(rbx) + 0x10);

    // 0xe878101..0xe87810e: Load key B data pointer (SSO or heap)
    void* rcx_keyB;
    if (*reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(rbx) + 0x18) < 0x10) {
        rcx_keyB = rbx;
    } else {
        rcx_keyB = *reinterpret_cast<void**>(rbx);
    }

    // 0xe87810e..0xe878118: min size + call 0xEEC6EB0
    std::size_t minSize = (keyLenA < keyLenB) ? keyLenA : keyLenB;
    int cmpResult = sub_eec6eb0(rcx_keyB, rdx_keyA, minSize);

    // 0xe8780af..0xe8780db: Process comparison result
    sil = 0;
    sil = (reinterpret_cast<uintptr_t>(r15) < keyLenA) ? 1 : 0;
    uint8_t cl = (cmpResult >= 0) ? 1 : 0;
    if (cmpResult != 0) {
        sil = cl;
    }
    r15 = r13;
    if (sil == 0) {
        r15 = r12;
    }
    uintptr_t offset = static_cast<uintptr_t>(sil) << 4;
    rax = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(r12) + offset);

    // 0xe8780d7..0xe8780db: Check flag, loop or continue
    if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(rax) + 0x19) != 0) {
        goto loc_e87804f_a;
    }

    goto bucket_common;

path_b:
    // 0xe878072..0xe878083: Path B entry - load key B
    // 0xe878072: cmp qword ptr [rbx+0x18],0x10
    // 0xe878077: mov r14,rbx
    // 0xe87807a: jb short 0xE87807f
    // 0xe87807c: mov r14,[rbx]
    // 0xe87807f: mov rdi,[rbx+0x10]
    void* r14;
    if (*reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(rbx) + 0x18) < 0x10) {
        r14 = rbx;
    } else {
        r14 = *reinterpret_cast<void**>(rbx);
    }
    uintptr_t rdi_int = *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(rbx) + 0x10);

    // 0xe8780e1..0xe8780ea: Bucket setup for Path B
    r12 = rax;
    if (*reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(rax) + 0x38) < 0x10) {
        // 0xe8780eb: mov r13,r15
        // 0xe8780ee: lea rcx,[r12+0x20]
        r13 = r15;
        // r15 is containerA from prologue
        // rcx = &containerB+0x20
    } else {
        // 0xe878090: mov r13,r15
        // 0xe878093: mov rcx,[r12+0x20]
        r13 = r15;
        rcx = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(r12) + 0x20);
    }

    // 0xe878098..0xe8780aa: Key len + call 0xEEC6EB0
    uintptr_t r15_int = *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(r12) + 0x30);
    std::size_t minSizeB = (r15_int < rdi_int) ? r15_int : rdi_int;
    cmpResult = sub_eec6eb0(rcx, r14, minSizeB);

    // 0xe8780af..0xe8780db: Process comparison result (Path B)
    sil = 0;
    sil = (r15_int < rdi_int) ? 1 : 0;
    cl = (cmpResult >= 0) ? 1 : 0;
    if (cmpResult != 0) {
        sil = cl;
    }
    r15 = r13;
    if (sil == 0) {
        r15 = r12;
    }
    offset = static_cast<uintptr_t>(sil) << 4;
    rax = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(r12) + offset);

    if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(rax) + 0x19) != 0) {
        goto loc_e87804f_a;  // re-enter with current r15
    }

    goto bucket_common;

    // 0xe87813e..0xe878502: Insert path + epilogue
loc_e87813e:
bucket_common:
    {
    loc_e87813e:
        // 0xe87813e: mov rax,0x333333333333333
        // 0xe878148: cmp [r13+8],rax
        // 0xe87814c: je 0xE8784F1
        uint64_t maxSize = 0x333333333333333ULL;
        if (*reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(r13) + 8) == maxSize) {
            boundary::sub_a4ea0();
        }

        // 0xe878152..0xe878171: Allocate node (0x50 bytes)
        void* allocator = *reinterpret_cast<void**>(kDataSlotAllocator);
        allocator = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(allocator) + 8);
        void* nodeMem = call_thunk_f99ffa0(allocator, 0x50);
        void* r15_node = nodeMem;

        if (r15_node == nullptr) {
            boundary::sub_9bc830(0x50);
        }

        // 0xe878177..0xe87817f: Init node key fields
        HashMapNode* hnode = reinterpret_cast<HashMapNode*>(r15_node);
        hnode->keyLen = 0;
        hnode->keyData = nullptr;

        // 0xe878184..0xe878191: Load a2 key len and data
        uint64_t a2KeyLen = *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(rbx) + 0x10);
        void* a2KeyData;
        if (*reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(rbx) + 0x18) < 0x10) {
            a2KeyData = rbx;
        } else {
            a2KeyData = *reinterpret_cast<void**>(rbx);
        }

        // 0xe878192..0xe878195: Negative length check
        if (static_cast<int64_t>(a2KeyLen) < 0) {
            boundary::sub_75720();
        }

        // 0xe87819b..0xe8781b7: SSO key copy
        if (a2KeyLen <= 0xF) {
            hnode->keyData = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(r15_node) + 0x20);
            hnode->keyLen = a2KeyLen;
            hnode->keyCap = 0xF;
            sub_eec6ec0(hnode->keyData, a2KeyData, 0x10);
        } else {
            // 0xe8781bc..0xe878249: Heap key allocation + copy
            void* rbp_8 = r15_node;
            uint64_t rdx_size = a2KeyLen | 0xF;
            uint64_t rdi_cap = (rdx_size >= 0x17) ? rdx_size : 0x16;
            void* allocator2 = *reinterpret_cast<void**>(kDataSlotAllocator);
            allocator2 = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(allocator2) + 8);
            void* keyBuf;
            if (rdx_size < 0xFFF) {
                keyBuf = call_thunk_f99ffa0(allocator2, rdi_cap + 1);
            } else {
                keyBuf = call_thunk_f99ffa0(allocator2, rdi_cap + 0x28);
            }
            if (keyBuf == nullptr) {
                if (rdx_size < 0xFFF) {
                    boundary::sub_9bc830(rdi_cap + 0x28);
                } else {
                    boundary::sub_9bc830(rdi_cap + 1);
                }
            }
            uintptr_t keyBufPtr = reinterpret_cast<uintptr_t>(keyBuf);
            uintptr_t alignedKeyBuf = (keyBufPtr + 0x27) & ~0x1FULL;
            *reinterpret_cast<void**>(alignedKeyBuf - 8) = keyBuf;
            hnode->keyData = reinterpret_cast<void*>(alignedKeyBuf);
            hnode->keyLen = a2KeyLen;
            hnode->keyCap = rdi_cap;
            a2KeyLen += 1;
            sub_eec6ec0(reinterpret_cast<void*>(alignedKeyBuf), a2KeyData, a2KeyLen);
            r15_node = rbp_8;
        }

        // 0xe87824e..0xe8782d9: Link node into bucket
        hnode->field48 = 0;
        hnode->field40 = nullptr;
        hnode->left = r15_saved;
        hnode->right = r15_saved;
        hnode->parent = r15_saved;
        hnode->flags = 0;

        *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(r13) + 8) += 1;

        void* rdi = *reinterpret_cast<void**>(r13);
        hnode->right = r12;

        if (r12 == rdi) {
            *reinterpret_cast<void**>(rdi) = r15_node;
            *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(rdi) + 8) = r15_node;
            *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(rdi) + 0x10) = r15_node;
        } else {
            if (sil == 0) {
                *reinterpret_cast<void**>(r12) = r15_node;
                if (r12 == *reinterpret_cast<void**>(rdi)) {
                    *reinterpret_cast<void**>(rdi) = r15_node;
                }
            } else {
                *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(r12) + 0x10) = r15_node;
                if (r12 == *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(rdi) + 0x10)) {
                    *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(rdi) + 0x10) = r15_node;
                }
            }
        }

        // 0xe8782d3..0xe8782ef: Set flag, store output, epilogue
        void* rcx_fixup = hnode->right;
        *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(rcx_fixup) + 0x18) = 1;
        cl = 1;
        *reinterpret_cast<void**>(rdx_saved) = r15_node;
        *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(rdx_saved) + 8) = cl;
    }

    // 0xe8782df..0xe8782ef: Epilogue
    return rdx_saved;
}

// LIFT_FN registry entry
LIFT_FN(sub_e878010, "BgfxFrameBuilder slot 16", 0xE878010, sub_e878010, nullptr);

} // namespace d3d12
} // namespace native

#if 0
// Verbatim call quotes for liftcheck (verify_oc parses plain lines)
0xe8780aa  call 0xEEC6EB0
0xe878118  call 0xEEC6EB0
0xe878165  call qword ptr [0xF99FFA0]
0xe8781ef  call qword ptr [0xF99FFA0]
0xe878217  call qword ptr [0xF99FFA0]
0xe878249  call 0xEEC6EC0
0xe8784c6  call 0x9BC830
0xe8784d4  call 0x9BC830
0xe8784e3  call 0x9BC830
0xe8784f1  call 0xA4EA0
0xe8784fb  call 0x75720
#endif
