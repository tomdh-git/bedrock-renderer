// LIFT 0xe878550 size 0x225 1.26.62.01 BgfxFrameBuilder_slot16
#include "sub_e878550.h"
#include "client/features/render/native/Lift.h"

#if 0
0xe8785a9  call r8                                    ; vendor via data slot 0xF99FFA0 (sub_eea6040)
0xe878649  call r8                                    ; vendor via data slot 0xF99FFA0 (sub_eea6040)
0xe87867a  call r8                                    ; vendor via data slot 0xF99FFA0 (sub_eea6040)
0xe8786a5  call 0xEEC6EC0                             ; -> native::sub_eec6ec0 (lift)
0xe8786df  call 0xE878550                             ; -> native::sub_e878550 (recursive)
0xe8786f3  call 0xE878550                             ; -> native::sub_e878550 (recursive)
0xe878725  call 0x9BC830                              ; -> native::boundary::sub_9bc830 (alloc, noreturn)
0xe87873f  call 0x9BC830                              ; -> native::boundary::sub_9bc830 (alloc, noreturn)
0xe87875a  call 0x9BC830                              ; -> native::boundary::sub_9bc830 (alloc, noreturn)
0xe87876e  call 0x75720                               ; -> native::boundary::sub_75720 (stl, noreturn)
#endif

static_assert(0x50 == 0x50, "FrameBuilderNode layout size verified [V]");

namespace native {
namespace d3d12 {

extern "C" FrameBuilderNode* sub_e878550(void* builder, void* inputNode, void* userParam) {
    // Arguments per x64 ABI: rcx = builder, rdx = inputNode, r8 = userParam
    // Registers used (non-volatile): r13, r14, r15, rdi, rsi, rbx, r12
    // Stack frame: sub rsp, 0x48; rbp = rsp + 0x40; [rbp] = -1 (cookie)

    // 0xe878550..0xe87856d: Prologue
    // 0xe87856d: mov r13, [rcx]         ; r13 = builder->field0
    void* r13 = *reinterpret_cast<void**>(builder);

    // 0xe878570..0xe878579: Early exit check
    // 0xe878570: cmp byte ptr [rdx+0x19], 0
    // 0xe878574: je loc_e87857e
    // 0xe878576: mov rax, r13
    // 0xe878579: jmp loc_e878704
    if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(inputNode) + 0x19) != 0) {
        // loc_e878704..0xe878714: Epilogue + return r13
        return reinterpret_cast<FrameBuilderNode*>(r13);
    }

    // loc_e87857e:
    // 0xe87857e: mov rbx, r8            ; rbx = userParam
    // 0xe878581: mov rdi, rdx           ; rdi = inputNode
    // 0xe878584: mov rsi, rcx           ; rsi = builder
    void* rbx = userParam;
    void* rdi = inputNode;
    void* rsi = builder;

    // 0xe878587..0xe8785a9: Allocate new node (0x50 bytes)
    // 0xe878587: mov rcx, [0x1233E1A8]  ; allocator object
    // 0xe87858e: mov rax, [rcx]
    // 0xe878591: mov rax, [rax+8]       ; allocator->vtable[1] (alloc function)
    // 0xe878595: mov r8, [0xF99FFA0]    ; vendor thunk (sub_eea6040)
    // 0xe87859c: mov qword ptr [rbp-0x10], 0
    // 0xe8785a4: mov edx, 0x50          ; size = 0x50
    // 0xe8785a9: call r8                ; thunk_f99ffa0(allocator, 0x50)
    void* allocator = *reinterpret_cast<void**>(kDataSlotAllocator);
    void* node = boundary::thunk_f99ffa0(allocator, 0x50);
    FrameBuilderNode* r9 = reinterpret_cast<FrameBuilderNode*>(node);

    // 0xe8785b0..0xe8785b3: Check allocation success
    // 0xe8785b0: test rax, rax
    // 0xe8785b3: je loc_e878715
    if (r9 == nullptr) {
        // loc_e878715..0xe87872d: OOM path
        // 0xe878715: mov qword ptr [rbp-0x10], 0
        // 0xe87871d: mov ecx, 0x50
        // 0xe878722: mov r14, r9
        // 0xe878725: call 0x9BC830      ; sub_9bc830(0x50) - noreturn
        boundary::sub_9bc830(0x50);
    }

    // loc_e8785b9:
    // 0xe8785b9: xorps xmm0, xmm0
    // 0xe8785bc: movups [r9+0x30], xmm0 ; r9->strLen = 0
    // 0xe8785c1: movups [r9+0x20], xmm0 ; r9->strData = 0
    r9->strLen = 0;
    r9->strData = nullptr;

    // 0xe8785c6..0xe8785db: Get input node's string length and data pointer
    // 0xe8785c6: mov r14, [rdi+0x30]    ; r14 = inputNode->strLen
    // 0xe8785ca: cmp qword ptr [rdi+0x38], 0x10
    // 0xe8785cf: jb loc_e8785d7
    // 0xe8785d1: mov r15, [rdi+0x20]    ; r15 = inputNode->strData (heap)
    // 0xe8785d5: jmp loc_e8785db
    // loc_e8785d7:
    // 0xe8785d7: lea r15, [rdi+0x20]    ; r15 = &inputNode->inlineBuffer (SSO)
    // loc_e8785db:
    uint64_t r14 = *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(rdi) + 0x30);
    void* r15;
    if (*reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(rdi) + 0x38) < 0x10) {
        r15 = reinterpret_cast<uint8_t*>(rdi) + 0x20; // inline buffer
    } else {
        r15 = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(rdi) + 0x20); // heap pointer
    }

    // 0xe8785db..0xe8785ec: Check string length
    // 0xe8785db: test r14, r14
    // 0xe8785de: js loc_e87876a       ; if negative -> invalid param
    // 0xe8785e4: cmp r14, 0xF
    // 0xe8785e8: mov [rbp-8], r9      ; save node pointer
    // 0xe8785ec: ja loc_e87860d       ; if > 0xF -> heap allocation needed
    FrameBuilderNode* r9_save = r9;

    if (static_cast<int64_t>(r14) < 0) {
        // loc_e87876a: invalid parameter (negative length)
        // 0xe87876a: mov [rbp-0x10], r9
        // 0xe87876e: call 0x75720     ; sub_75720() - noreturn
        boundary::sub_75720();
    }

    // r14 <= 0xF: SSO (small string optimization) path
    if (r14 <= 0xF) {
        // 0xe8785ee..0xe878608
        // 0xe8785ee: mov rax, r9
        // 0xe8785f1: add rax, 0x20
        // 0xe8785f5: mov [r9+0x30], r14      ; node->strLen = r14
        // 0xe8785f9: mov qword ptr [r9+0x38], 0xF ; node->strCap = 0xF
        // 0xe878601: movups xmm0, [r15]
        // 0xe878605: movups [rax], xmm0      ; copy 16 bytes to inline buffer
        // 0xe878608: jmp loc_e8786ad
        r9->strData = reinterpret_cast<uint8_t*>(r9) + 0x20;
        r9->strLen = r14;
        r9->strCap = 0xF;
        sub_eec6ec0(r9->strData, r15, 0x10);
    } else {
        // loc_e87860d: r14 > 0xF - need heap allocation for string
        // 0xe87860d: mov rdx, r14
        // 0xe878610: or rdx, 0xF
        // 0xe878614: cmp rdx, 0x17
        // 0xe878618: mov r12d, 0x16
        // 0xe87861e: cmovae r12, rdx         ; r12 = max(0x16, rdx)
        uint64_t rdx = r14 | 0xF;
        uint64_t r12 = (rdx >= 0x17) ? rdx : 0x16;

        // 0xe878622..0xe878637: Get allocator again
        // 0xe878622: mov rcx, [0x1233E1A8]
        // 0xe878629: mov rax, [rcx]
        // 0xe87862c: mov rax, [rax+8]
        // 0xe878630: cmp rdx, 0xFFF
        // 0xe878637: jb loc_e87866a
        void* allocator2 = *reinterpret_cast<void**>(kDataSlotAllocator);

        if (rdx < 0xFFF) {
            // loc_e87866a: Small allocation (rdx < 0xFFF)
            // 0xe87866a: lea rdx, [r12+1]     ; size = r12 + 1
            // 0xe87866f: mov r8, [0xF99FFA0]  ; thunk
            // 0xe878676: mov [rbp-0x10], r9
            // 0xe87867a: call r8              ; thunk_f99ffa0(allocator, r12+1)
            // 0xe87867d: mov r9, [rbp-8]      ; restore node pointer
            // 0xe878681: test rax, rax
            // 0xe878684: je loc_e878751
            // Falls through to loc_e87868a
            void* rax = boundary::thunk_f99ffa0(allocator2, r12 + 1);
            if (rax == nullptr) {
                // loc_e878751: allocation failed
                // 0xe878751: mov [rbp-0x10], r9
                // 0xe878755: lea rcx, [r12+1]
                // 0xe87875a: call 0x9BC830    ; sub_9bc830(r12+1) - noreturn
                boundary::sub_9bc830(r12 + 1);
            }

            // loc_e87868a: (from loc_e87866a success and loc_e878659)
            // 0xe87868a: mov [r9+0x20], rax   ; node->strData = rax
            // 0xe87868e: mov [r9+0x30], r14   ; node->strLen = r14
            // 0xe878692: mov [r9+0x38], r12   ; node->strCap = r12
            // 0xe878696: inc r14              ; r14++
            // 0xe878699: mov rcx, rax         ; dst = rax
            // 0xe87869c: mov rdx, r15         ; src = r15
            // 0xe87869f: mov r8, r14          ; count = r14 (incremented)
            // 0xe8786a2: mov r14, r9          ; save node in r14
            // 0xe8786a5: call 0xEEC6EC0       ; sub_eec6ec0(dst, src, count)
            // 0xe8786aa: mov r9, r14          ; restore node in r9
            r9->strData = rax;
            r9->strLen = r14;
            r9->strCap = r12;
            uint64_t copyCount = r14 + 1;
            sub_eec6ec0(rax, r15, copyCount);
            // r9 unchanged (was saved/restored)
        } else {
            // loc_e878639: Large allocation (rdx >= 0xFFF)
            // 0xe878639: lea rdx, [r12+0x28]  ; size = r12 + 0x28 (with alignment padding)
            // 0xe87863e: mov r8, [0xF99FFA0]
            // 0xe878645: mov [rbp-0x10], r9
            // 0xe878649: call r8              ; thunk_f99ffa0(allocator, r12+0x28)
            // 0xe87864c: mov r9, [rbp-8]
            // 0xe878650: test rax, rax
            // 0xe878653: je loc_e878732
            // Falls through to loc_e878659
            void* rax = boundary::thunk_f99ffa0(allocator2, r12 + 0x28);
            if (rax == nullptr) {
                // loc_e878732: allocation failed
                // 0xe878732: mov [rbp-0x10], r9
                // 0xe878736: lea rcx, [r12+0x28]
                // 0xe87873b: mov [rbp-0x18], rax
                // 0xe87873f: call 0x9BC830    ; sub_9bc830(r12+0x28) - noreturn
                boundary::sub_9bc830(r12 + 0x28);
            }

            // loc_e878659: Align result to 32 bytes and store original ptr
            // 0xe878659: mov rcx, rax
            // 0xe87865c: add rax, 0x27
            // 0xe878660: and rax, 0xFFFFFFFFFFFFFFE0  ; align down to 32
            // 0xe878664: mov [rax-8], rcx             ; store original ptr at aligned-8
            // 0xe878668: jmp loc_e87868a
            uintptr_t originalPtr = reinterpret_cast<uintptr_t>(rax);
            uintptr_t alignedPtr = (originalPtr + 0x27) & ~0x1Fu;
            *reinterpret_cast<void**>(alignedPtr - 8) = rax;
            rax = reinterpret_cast<void*>(alignedPtr);

            // loc_e87868a (same as above)
            // 0xe87868a: mov [r9+0x20], rax   ; node->strData = aligned rax
            // 0xe87868e: mov [r9+0x30], r14   ; node->strLen = r14
            // 0xe878692: mov [r9+0x38], r12   ; node->strCap = r12
            // 0xe878696: inc r14              ; r14++
            // 0xe878699: mov rcx, rax         ; dst = rax
            // 0xe87869c: mov rdx, r15         ; src = r15
            // 0xe87869f: mov r8, r14          ; count = r14 (incremented)
            // 0xe8786a2: mov r14, r9          ; save node in r14
            // 0xe8786a5: call 0xEEC6EC0       ; sub_eec6ec0(dst, src, count)
            // 0xe8786aa: mov r9, r14          ; restore node in r9
            r9->strData = rax;
            r9->strLen = r14;
            r9->strCap = r12;
            uint64_t copyCount = r14 + 1;
            sub_eec6ec0(rax, r15, copyCount);
            // r9 unchanged (was saved/restored)
        }
    }

    // loc_e8786ad: Populate node fields and make recursive calls
    // 0xe8786ad: mov eax, [rdi+0x48]
    // 0xe8786b0: mov [r9+0x48], eax
    // 0xe8786b4: mov rax, [rdi+0x40]
    // 0xe8786b8: mov [r9+0x40], rax
    // 0xe8786bc: mov [r9], r13
    // 0xe8786bf: mov [r9+0x10], r13
    // 0xe8786c3: mov word ptr [r9+0x18], 0
    // 0xe8786ca: mov [r9+8], rbx
    // 0xe8786ce: movzx eax, byte ptr [rdi+0x18]
    // 0xe8786d2: mov [r9+0x18], al
    r9->field48 = *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(rdi) + 0x48);
    r9->field40 = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(rdi) + 0x40);
    r9->leftChild = r13;     // overwritten below by left recursive result
    r9->rightChild = r13;    // overwritten below by right recursive result
    r9->flags = 0;
    r9->userParam = rbx;
    uint8_t byte18 = *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(rdi) + 0x18);
    r9->flags = static_cast<uint16_t>(byte18);

    // 0xe8786d6..0xe8786df: First recursive call (left child)
    // 0xe8786d6: mov rdx, [rdi]         ; left child = inputNode->left
    // 0xe8786d9: mov rcx, rsi           ; rcx = builder
    // 0xe8786dc: mov r8, r9             ; r8 = node (userParam for recursive)
    // 0xe8786df: call 0xE878550
    void* leftResult = sub_e878550(rsi, *reinterpret_cast<void**>(rdi), r9);

    // 0xe8786e5..0xe8786e9: Store left result in node->parentContext
    // 0xe8786e5: mov r8, [rbp-8]        ; r8 = node pointer (saved at 0xe8785e8)
    // 0xe8786e9: mov [r8], rax          ; node->parentContext = leftResult
    *reinterpret_cast<void**>(r9_save) = leftResult;

    // 0xe8786ec..0xe8786f3: Second recursive call (right child)
    // 0xe8786ec: mov rdx, [rdi+0x10]    ; right child = inputNode->right
    // 0xe8786f0: mov rcx, rsi           ; rcx = builder
    // 0xe8786f3: call 0xE878550
    void* rightResult = sub_e878550(rsi, *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(rdi) + 0x10), r9_save);

    // 0xe8786f9..0xe878701: Store right result and return node
    // 0xe8786f9: mov rcx, [rbp-8]       ; rcx = node pointer
    // 0xe8786fd: mov [rcx+0x10], rax    ; node->parentContext2 = rightResult
    // 0xe878701: mov rax, rcx           ; rax = node pointer (return value)
    *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(r9_save) + 0x10) = rightResult;

    // loc_e878704..0xe878714: Epilogue
    // 0xe878704: add rsp, 0x48
    // 0xe878708: pop rbx; pop rdi; pop rsi; pop r12; pop r13; pop r14; pop r15; pop rbp
    // 0xe878714: ret
    return r9_save;
}

} // namespace d3d12
} // namespace native

LIFT_FN(sub_e878550, "BgfxFrameBuilder_slot16", 0xe878550, sub_e878550, nullptr);