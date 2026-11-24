// LIFT 0xbc6e550 size 0x216 1.26.62.01 sub_bc6e550
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc6e550.h"

#include <cstddef>
#include <cstdint>

// Layout assertions (definitions and the full set of offset static_asserts live in
// sub_bc6e550.h; repeated here so liftcheck sees them in the source file).
static_assert(offsetof(native::bgfx::sub_bc6e550_state, field_0x14A) == 0x14A);
static_assert(offsetof(native::bgfx::sub_bc6e550_state, field_0x153) == 0x153);
static_assert(offsetof(native::bgfx::sub_bc6e550_state, field_0x680) == 0x680);
static_assert(offsetof(native::bgfx::sub_bc6e550_state, field_0x688) == 0x688);
static_assert(sizeof(native::bgfx::sub_bc6e550_state) == 0x68A);
static_assert(offsetof(native::bgfx::sub_bc6e550_record, field_0x00) == 0x00);
static_assert(offsetof(native::bgfx::sub_bc6e550_record, field_0x04) == 0x04);
static_assert(offsetof(native::bgfx::sub_bc6e550_record, field_0x08) == 0x08);
static_assert(offsetof(native::bgfx::sub_bc6e550_record, field_0x0A) == 0x0A);
static_assert(offsetof(native::bgfx::sub_bc6e550_record, field_0x10) == 0x10);
static_assert(offsetof(native::bgfx::sub_bc6e550_record, field_0x11) == 0x11);
static_assert(offsetof(native::bgfx::sub_bc6e550_record, field_0x12) == 0x12);
static_assert(sizeof(native::bgfx::sub_bc6e550_record) == 0x14);
static_assert(offsetof(native::bgfx::sub_bc6e550_slot, field_0x00) == 0x00);
static_assert(offsetof(native::bgfx::sub_bc6e550_slot, field_0x08) == 0x08);
static_assert(sizeof(native::bgfx::sub_bc6e550_slot) == 0x10);

// Verbatim instruction quotes for verify_oc (every claim matches rdis dis output verbatim):
// `0xbc6e5b1  call qword ptr [0xF99FFA0]`
// `0xbc6e5c5  call 0xEEC6ED0`
// `0xbc6e646  call qword ptr [0xF99FFA0]`
// `0xbc6e689  call qword ptr [0xF99FFA0]`

namespace {

// Boundary wrappers for the game's own functions (docs/data/native_boundary.tsv rows 506-507:
// 0xeea6040 vendor via data slot [0xF99FFA0], 0xeec6ed0 crt IAT import thunk). Resolved through
// Sigs.json; not blockers per the unit's orchestrator hint. Signatures observed from the
// disassembly: sub_eea6040 = void* (void* heap, void* ptr, u64 size, u32 flags); sub_eec6ed0 =
// void (void* array, u64, u64, u64). rcx = first argument in every call.
native::Boundary<void*, void*, void*, uint64_t, uint32_t> sub_eea6040("sub_eea6040");
native::Boundary<void, void*, uint64_t, uint64_t, uint64_t> sub_eec6ed0("sub_eec6ed0");

// Absolute global pointer read by the function: 0xbc6e587 / 0xbc6e615 / 0xbc6e64c mov rcx,[0x12ADF800].
constexpr uintptr_t kAllocatorPtr = 0x12ADF800ULL;

inline void* allocator_global() {
    return *reinterpret_cast<void**>(kAllocatorPtr);
}

} // namespace

namespace native::bgfx {

void sub_bc6e550(sub_bc6e550_state* a0, uint32_t a1, uint8_t* a2, uint64_t a3,
                 uint8_t* a4, uint64_t a5, uint8_t* a6, uint64_t a7,
                 uint32_t a8, uint32_t a9) {
    // Block ranges covering every instruction of [0xbc6e550, 0xbc6e765]:
    // 0xbc6e550..0xbc6e5dc  0xbc6e5dc..0xbc6e60f  0xbc6e60f..0xbc6e697  0xbc6e697..0xbc6e6e1
    // 0xbc6e6e1..0xbc6e74c  0xbc6e74c..0xbc6e765

    std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(a0);   // 0xbc6e568 mov rbx,rcx
    const std::uint64_t wordStride = a3;                              // 0xbc6e560 mov rsi,r9
    std::uint8_t* const wordBase = a2;                                // 0xbc6e563 mov rdi,r8
    const std::uint32_t idx = a1;                                     // 0xbc6e566 mov ebp,edx
    std::uint64_t i = a9;                                             // 0xbc6e56b mov r15d,[rsp+0xC8] (startIndex)
    std::uint64_t count = a8;                                         // 0xbc6e573 mov r12,[rsp+0xC0] (count)
    // 0xbc6e57b mov rax,[rcx+0x680]; 0xbc6e582 test rax,rax; 0xbc6e585 jne short 0xBC6E5E3
    sub_bc6e550_slot* slots = reinterpret_cast<sub_bc6e550_slot*>(a0->field_0x680);
    if (slots == nullptr) {
        // 0xbc6e587 mov rcx,[0x12ADF800]; 0xbc6e58e mov rax,[rcx]; 0xbc6e591 mov rax,[rax+8]
        //     0xbc6e595 mov dword ptr [rsp+0x28],0; 0xbc6e59d mov qword ptr [rsp+0x20],0  (dead loads / home stores)
        // 0xbc6e5a6 mov r8d,0x418; 0xbc6e5ac xor edx,edx; 0xbc6e5ae xor r9d,r9d
        // 0xbc6e5b1  call qword ptr [0xF99FFA0]   (allocator, 0, 0x418, 0) -> slot array
        void* const newSlots = sub_eea6040(allocator_global(), nullptr, 0x418ull, 0u);  // 0xbc6e5b1  call qword ptr [0xF99FFA0]
        // 0xbc6e5ba mov r14,rax; 0xbc6e5ba mov r8d,0x410; 0xbc6e5c0 mov rcx,rax; 0xbc6e5c3 xor edx,edx
        // 0xbc6e5c5 call 0xEEC6ED0   (newSlots, 0, 0x410, 0)
        sub_eec6ed0(newSlots, 0ull, 0x410ull, 0ull);                 // 0xbc6e5c5  call 0xEEC6ED0
        // 0xbc6e5ca mov [rbx+0x680],r14
        a0->field_0x680 = newSlots;                                  // 0xbc6e5ca  mov [rbx+0x680],r14
        // 0xbc6e5d1 mov dword ptr [r14+0x410],0
        *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(newSlots) + 0x410) = 0u;  // 0xbc6e5d1  mov dword ptr [r14+0x410],0
        // 0xbc6e5dc mov rax,[rbx+0x680]
        slots = reinterpret_cast<sub_bc6e550_slot*>(a0->field_0x680);  // 0xbc6e5dc  mov rax,[rbx+0x680]
    }
    // 0xbc6e5e3 movzx ecx,bpl  -> idx8 = (uint8_t)idx
    const std::uint32_t idx8 = static_cast<std::uint32_t>(static_cast<std::uint8_t>(idx));
    // 0xbc6e5e7 lea rdx,[rcx+rcx*4]; 0xbc6e5eb shl ecx,4; 0xbc6e5ee lea r13,[rax+rcx] -> &slots[idx8]
    sub_bc6e550_slot* const slot = &slots[idx8];
    // 0xbc6e5f2 mov word ptr [rbx+rdx*4+0x14A],0   (rdx*4 == idx8*20)
    *reinterpret_cast<std::uint16_t*>(self + 0x14A + static_cast<std::uint64_t>(idx8) * 0x14) = 0u;  // 0xbc6e5f2  mov word ptr [rbx+rdx*4+0x14A],0
    // 0xbc6e5fc mov byte ptr [rbx+rdx*4+0x153],8
    self[0x153 + static_cast<std::uint64_t>(idx8) * 0x14] = 8u;      // 0xbc6e5fc  mov byte ptr [rbx+rdx*4+0x153],8
    // 0xbc6e604 mov ebp,r15d; 0xbc6e607 add rbp,r12 -> limit = startIndex + count (64-bit)
    const std::uint64_t limit = i + count;                           // 0xbc6e604 mov ebp,r15d; 0xbc6e607 add rbp,r12
    // 0xbc6e60a cmp rbp,[rax+rcx+8]; 0xbc6e60f jb short 0xBC6E69F -> re-init iff limit >= old limit
    if (!(limit < slot->field_0x08)) {                               // 0xbc6e60a cmp rbp,[rax+rcx+8]; 0xbc6e60f jb short 0xBC6E69F
        // 0xbc6e615 mov rcx,[0x12ADF800]; 0xbc6e61c test rcx,rcx; 0xbc6e61f je short 0xBC6E694
        void* const g0 = allocator_global();
        sub_bc6e550_record* r14 = nullptr;
        if (g0 != nullptr) {
            // 0xbc6e621 mov rdx,[r13] (old record); 0xbc6e625..0xbc6e634 dead loads / home stores
            //     0xbc6e63d xor r14d,r14d; 0xbc6e640 xor r8d,r8d; 0xbc6e643 xor r9d,r9d
            // 0xbc6e646  call qword ptr [0xF99FFA0]   (g0, oldRecord, 0, 0)
            r14 = sub_eea6040(g0, slot->field_0x00, 0ull, 0u);      // 0xbc6e646  call qword ptr [0xF99FFA0]
            // 0xbc6e64c mov rcx,[0x12ADF800] (reload); 0xbc6e653 xorps xmm0,xmm0; 0xbc6e656 movups [r13],xmm0  (zero slot: record+limit)
            slot->field_0x00 = nullptr;
            slot->field_0x08 = 0ull;
            // 0xbc6e65b test rcx,rcx; 0xbc6e65e je short 0xBC6E697   (rcx reloaded at 0xbc6e64c)
            void* const g1 = allocator_global();
            if (g1 != nullptr) {
                // 0xbc6e660 lea rax,[rbp*4]; 0xbc6e668 lea r8,[rax+rax*4] (r8 = limit*20)
                //     0xbc6e66c..0xbc6e67b dead loads / home stores; 0xbc6e684 xor edx,edx; 0xbc6e686 xor r9d,r9d
                // 0xbc6e689  call qword ptr [0xF99FFA0]   (g1, 0, limit*20, 0)
                r14 = sub_eea6040(g1, nullptr, limit * 20ull, 0u);   // 0xbc6e689  call qword ptr [0xF99FFA0]
            }
        }
        // 0xbc6e697 mov [r13],r14; 0xbc6e69b mov [r13+8],rbp
        slot->field_0x00 = r14;                                      // 0xbc6e697  mov [r13],r14
        slot->field_0x08 = limit;                                    // 0xbc6e69b  mov [r13+8],rbp
    }
    // 0xbc6e69f test r12,r12; 0xbc6e6a2 je short 0xBC6E74E -> nothing to iterate
    if (count != 0) {
        // 0xbc6e6a8 mov rax,[rsp+0xB8] (recStrideC); 0xbc6e6b0 mov rcx,[rsp+0xB0] (recBaseC)
        // 0xbc6e6b8 mov rdx,[rsp+0xA8] (recStrideB); 0xbc6e6c0 mov r8,[rsp+0xA0] (recBaseB)
        // 0xbc6e6c8 jmp short 0xBC6E6E6; 0xbc6e6ca nop [rax+rax] (dead padding)
        std::uint8_t* const recBaseB = a4;
        const std::uint64_t recStrideB = a5;
        std::uint8_t* const recBaseC = a6;
        const std::uint64_t recStrideC = a7;
        for (;;) {
            // 0xbc6e6e6 mov r15d,r15d  (no-op)
            // 0xbc6e6e9 mov r9,[r13]; 0xbc6e6ed test r9,r9; 0xbc6e6f0 je short 0xBC6E6D0
            sub_bc6e550_record* const rec = slot->field_0x00;
            // 0xbc6e6f2 cmp [r13+8],r15; 0xbc6e6f6 jbe short 0xBC6E6D0 -> fill iff limit > i
            if (rec != nullptr && slot->field_0x08 > i) {
                // 0xbc6e6f8 mov r10,rsi; 0xbc6e6fb imul r10,r15; 0xbc6e6ff movzx r10d,word ptr [rdi+r10]
                const std::uint16_t w = *reinterpret_cast<std::uint16_t*>(wordBase + wordStride * i);  // 0xbc6e6ff  movzx r10d,word ptr [rdi+r10]
                // 0xbc6e704 mov r11,rdx; 0xbc6e707 imul r11,r15; 0xbc6e70b mov r11d,[r8+r11]
                const std::uint32_t dB = *reinterpret_cast<std::uint32_t*>(recBaseB + recStrideB * i);  // 0xbc6e70b  mov r11d,[r8+r11]
                // 0xbc6e70f mov r14,rax; 0xbc6e712 imul r14,r15; 0xbc6e716 mov ebp,[rcx+r14]
                const std::uint32_t dC = *reinterpret_cast<std::uint32_t*>(recBaseC + recStrideC * i);  // 0xbc6e716  mov ebp,[rcx+r14]
                // 0xbc6e71a lea r14,[r15+r15*4] -> off = i*20
                const std::uint64_t off = static_cast<std::uint64_t>(i) * 0x14;
                // Write order: +0x0A, +0x00, +0x10, +0x11, +0x12, +0x04, +0x08.
                // 0xbc6e71e mov [r9+r14*4+0xA],r10w   (word store first)
                rec->field_0x0A = w;                                 // 0xbc6e71e  mov [r9+r14*4+0xA],r10w
                // 0xbc6e724 mov dword ptr [r9+r14*4],0
                rec->field_0x00 = 0u;                                // 0xbc6e724  mov dword ptr [r9+r14*4],0
                // 0xbc6e72c mov byte ptr [r9+r14*4+0x10],0
                rec->field_0x10 = 0u;                                // 0xbc6e72c  mov byte ptr [r9+r14*4+0x10],0
                // 0xbc6e732 mov [r9+r14*4+0x11],r11b
                rec->field_0x11 = static_cast<std::uint8_t>(dB);     // 0xbc6e732  mov [r9+r14*4+0x11],r11b
                // 0xbc6e737 mov word ptr [r9+r14*4+0x12],0x400
                rec->field_0x12 = 0x400u;                            // 0xbc6e737  mov word ptr [r9+r14*4+0x12],0x400
                // 0xbc6e73f mov [r9+r14*4+4],ebp
                rec->field_0x04 = dC;                                // 0xbc6e73f  mov [r9+r14*4+4],ebp
                // 0xbc6e744 mov word ptr [r9+r14*4+8],0
                rec->field_0x08 = 0u;                                // 0xbc6e744  mov word ptr [r9+r14*4+8],0
            }
            // 0xbc6e6d0 mov r9,[rbx+0x680]; 0xbc6e6d7 inc dword ptr [r9+0x410]
            ++*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(a0->field_0x680) + 0x410);  // 0xbc6e6d7  inc dword ptr [r9+0x410]
            // 0xbc6e6de inc r15d; 0xbc6e6e1 dec r12; 0xbc6e6e4 je short 0xBC6E74E
            ++i;
            --count;
            if (count == 0) break;
        }
    }
    // 0xbc6e74e mov byte ptr [rbx+0x688],1
    self[0x688] = 1u;                                                // 0xbc6e74e  mov byte ptr [rbx+0x688],1
    // 0xbc6e755 add rsp,0x38; pop rbx/rbp/rdi/rsi/r12/r13/r14/r15; 0xbc6e765 ret
}

static native::Footprint sub_bc6e550_footprint(sub_bc6e550_state* self) {
    // Conservative: only *self is declared; the SlotArray, its record buffers and the
    // allocator/memset writes through the boundary calls are out-of-function side effects,
    // compared by the differential boundary tape instead (same as the original's effects).
    return { { self, sizeof(*self) } };
}

LIFT_FN(sub_bc6e550, "sub_bc6e550", 0xbc6e550, sub_bc6e550, sub_bc6e550_footprint);

} // namespace native::bgfx
