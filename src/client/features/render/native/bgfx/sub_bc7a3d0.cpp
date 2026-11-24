// LIFT 0xbc7a3d0 size 0x3cc 1.26.62.01 sub_bc7a3d0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc7a3d0.h"

#include <cstdint>
#include <cstring>

namespace native::bgfx {

namespace {

// Read the CFG-thunk pointer from data slot 0xF99FFA0 at every call, exactly as the
// original does (mov r10,[0xF99FFA0] / call r10 ; call qword ptr [0xF99FFA0]).
using Eea6040Fn = void* (*)(void* iface, void* ptr, std::uint64_t size, std::uint32_t flags);
inline Eea6040Fn eea6040_thunk() {
    return reinterpret_cast<Eea6040Fn>(
        *reinterpret_cast<std::uintptr_t*>(
            RewriteRegistry::imageBase() + sub_bc7a3d0_state::kThunkSlotRva));
}

inline void* allocator_global() {                      // mov rcx,[0x12ADF800]
    return *reinterpret_cast<void**>(
        RewriteRegistry::imageBase() + sub_bc7a3d0_state::kAllocatorGlobalRva);
}

// Boundary callees (docs/data/native_boundary.tsv rows 506-507; both classified out of the
// lift set): 0xeea6040 vendor "thunk via data slot 0xF99FFA0 (loader-resolved)",
// 0xeec6ed0 crt "jmp qword ptr [IAT] import thunk (CRT/memory)". The data-slot pointer is
// read at every call (slot is loader-resolved, not a static callee address); each wrapper
// forwards the same arguments in the same order as the instruction.
native::Boundary<void*, void*, void*, std::uint64_t, std::uint32_t> sub_eea6040("sub_eea6040");
native::Boundary<void, void*, std::uint64_t, std::uint64_t, std::uint64_t> sub_eec6ed0("sub_eec6ed0");

// Element at index `index` of the paged store: indices <= 0xFFF live inline at
// [self, self+0x28000); larger indices walk the block chain (chainHead=[self+0x28000],
// chainHead[0]=first block, each block holds 0x28000 bytes of elements and its next-pointer
// at +0x28000). Reads match the disassembly order: [head], then [head[0]], then each
// [block+0x28000] while the byte offset stays above 0x27FFF.
inline sub_bc7a3d0_elem* elemPtr(std::uint8_t* self, std::uint64_t index) {
    const std::uint64_t off = index * sub_bc7a3d0_state::kElemStride;
    if (index < sub_bc7a3d0_state::kInlineElemCount) {    // cmp rdx,0xFFF; jbe -> inline
        return reinterpret_cast<sub_bc7a3d0_elem*>(self + off);
    }
    std::uint64_t pageOff = off - sub_bc7a3d0_state::kInlineElemBytes;  // add rcx,0xFFFFFFFFFFFD8000
    sub_bc7a3d0_elem* block = reinterpret_cast<sub_bc7a3d0_elem*>(
        *reinterpret_cast<void**>(self + sub_bc7a3d0_state::kStateChainHead));  // r8 = [head]
    block = reinterpret_cast<sub_bc7a3d0_elem*>(   // r8 = [r8] = head[0] = first block
        *reinterpret_cast<void**>(block));
    while (pageOff >= sub_bc7a3d0_state::kBlockElemBytes) {   // cmp rcx,0x28000;jb ... ; cmp rcx,0x27FFF;ja
        pageOff -= sub_bc7a3d0_state::kBlockElemBytes;        // add rcx,0xFFFFFFFFFFFD8000
        block = reinterpret_cast<sub_bc7a3d0_elem*>(   // r8 = [r8+0x28000] = next block
            *reinterpret_cast<void**>(
                reinterpret_cast<std::uint8_t*>(block) + sub_bc7a3d0_state::kBlockElemBytes));
    }
    return reinterpret_cast<sub_bc7a3d0_elem*>(
        reinterpret_cast<std::uint8_t*>(block) + pageOff);
}

} // namespace

std::uint64_t sub_bc7a3d0(sub_bc7a3d0_state* self, std::uint64_t count) {
    std::uint8_t* const s = reinterpret_cast<std::uint8_t*>(self);
    const void* const tombstone = reinterpret_cast<void*>(RewriteRegistry::imageBase() + sub_bc7a3d0_state::kTombstoneRva);

    // 0xbc7a3d0..0xbc7a417: prologue. rsi=self, rdi=count.
    //   elemCount = [self+0x28008] / 40   (magic multiply 0xCCCCCCCCCCCCCCCD, shr 5)
    //   if (count >= elemCount) skip the destroy loop (0xbc7a411 jae 0xBC7A504)
    std::uint64_t elemCount =
        *reinterpret_cast<std::uint64_t*>(s + sub_bc7a3d0_state::kStateUsedBytes) /
        sub_bc7a3d0_state::kElemStride;

    // 0xbc7a417..0xbc7a504: destroy loop over indices [count, elemCount)
    if (count < elemCount) {
        std::uint64_t i = count;                              // mov r14,rdi
        for (;;) {
            // 0xbc7a45a..0xbc7a4c0: element address (inline or paged, see elemPtr);
            //   test dword ptr [elem+8],0; jne -> destroy this element
            sub_bc7a3d0_elem* const e = elemPtr(s, i);
            if (e->live != 0) {
                // 0xbc7a4c2: g = [0x12ADF800] (allocator interface);
                //   mov rax,[rcx]; mov rax,[rax+8]  (vtable slot loads: values unused - dead reads)
                void* const g = allocator_global();
                if (g != nullptr) {                         // test rcx,rcx; je 0xBC7A430
                    // 0xbc7a4fb  call r10       ; r10 = [0xF99FFA0] == sub_eea6040
                    //   rcx=g, rdx=e->ptr, r8=0, r9=0; home slots [rsp+0x28]=0, [rsp+0x20]=0 (dead stores)
                    sub_eea6040(g, e->ptr, 0ull, 0u);       // 0xbc7a4fb  call r10
                    // return value ignored (jmp 0xBC7A430)
                }
            }
            // 0xbc7a430  mov [r12],rbx        ; rbx = 0xF847A07 (lea rbx,[0xF847A07])
            // 0xbc7a434  mov dword ptr [r12+8],0
            e->ptr = tombstone;               // 0xbc7a430
            e->live = 0;                      // 0xbc7a434
            ++i;                              // 0xbc7a44a inc r14
            // 0xbc7a43d  mov rcx,[rsi+0x28008]  ; (usedBytes reloaded every iteration)
            //   elemCount = rcx / 40
            elemCount = *reinterpret_cast<std::uint64_t*>(s + sub_bc7a3d0_state::kStateUsedBytes) /
                        sub_bc7a3d0_state::kElemStride;
            // 0xbc7a451  cmp r14,rdx; jae 0xBC7A504
            if (i >= elemCount) break;
        }
    }

    // 0xbc7a504..0xbc7a6be: phase 2 - grow storage to hold `count` elements, then update
    //   capacityBytes. rdx (entering the 0xbc7a6be block) is path-dependent:
    //     count < 0x1001      -> rdx = count                              (0xbc7a683 mov rdx,rdi)
    //     count <= capElems   -> rdx = count                              (0xbc7a532 jbe 0xBC7A6BE)
    //     grow path           -> rdx = headCap / 40 + 0x1000              (0xbc7a6a6..0xbc7a6b0)
    std::uint64_t rdx;
    if (count < 0x1001ull) {
        rdx = count;
    } else {
        const std::uint64_t capacity = *reinterpret_cast<std::uint64_t*>(s + sub_bc7a3d0_state::kStateCapacityBytes);
        const std::uint64_t capElems = capacity / sub_bc7a3d0_state::kElemStride;  // mul/shr /40
        if (count > capElems) {                                       // cmp rdi,rax; jbe not taken
            // 0xbc7a538..0xbc7a660: grow the chained block storage
            std::uint64_t remaining = count * sub_bc7a3d0_state::kElemStride -
                                      sub_bc7a3d0_state::kInlineElemBytes;  // r12 = needed - 0x28000
            void* head = *reinterpret_cast<void**>(s + sub_bc7a3d0_state::kStateChainHead);  // r8/rax = [head]
            if (remaining == 0) {                                     // je 0xBC7A688
                if (head != nullptr) {
                    rdx = *reinterpret_cast<std::uint64_t*>(
                              reinterpret_cast<std::uint8_t*>(head) + 0x10) /
                              sub_bc7a3d0_state::kElemStride +
                          0x1000ull;                                  // 0xbc7a688..0xbc7a6b0
                } else {
                    rdx = 0x1000ull;                                  // 0xbc7a68d xor ecx,ecx
                }
            } else {
                if (head == nullptr) {                                // test rax,rax; jne not taken -> 0xbc7a559
                    // 0xbc7a559..0xbc7a59d: allocate the head descriptor (0x18 bytes)
                    void* const g = allocator_global();
                    // mov rax,[rcx]; mov rax,[rax+8]  (dead vtable reads - omitted)
                    head = sub_eea6040(g, nullptr, 0x18ull, 8ull);    // 0xbc7a589 call qword ptr [0xF99FFA0]
                    std::memset(head, 0, 16);                         // 0xbc7a592 movups [rax],xmm0
                    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint8_t*>(head) + 0x10) = 0;  // 0xbc7a595
                    *reinterpret_cast<void**>(s + sub_bc7a3d0_state::kStateChainHead) = head;  // 0xbc7a59d
                }
                // 0xbc7a5a4: rcx = [head+0x10]
                const std::uint64_t headCap =
                    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint8_t*>(head) + 0x10);
                if (remaining <= headCap) {                           // sub r12,rcx; jbe 0xBC7A6A6
                    rdx = headCap / sub_bc7a3d0_state::kElemStride + 0x1000ull;  // 0xbc7a6a6..0xbc7a6b0
                } else {
                    remaining -= headCap;
                    // 0xbc7a5b1..0xbc7a5c3: r13 = &tail-next field
                    std::uint8_t* r13;
                    void* const tail = *reinterpret_cast<void**>(
                        reinterpret_cast<std::uint8_t*>(head) + 8);
                    r13 = tail != nullptr
                        ? reinterpret_cast<std::uint8_t*>(tail) + sub_bc7a3d0_state::kBlockElemBytes  // lea r13,[rcx+0x28000]
                        : reinterpret_cast<std::uint8_t*>(head) + 8;      // cmove r13,rax (rax=head+8)
                    bool checkTail = true;   // 0xbc7a5c7 mov ebx,0x28000 (block stride for the walk)
                    for (;;) {
                        // 0xbc7a5cc cmp qword [r13],0; jne 0xBC7A660
                        if (checkTail && *reinterpret_cast<void**>(r13) != nullptr) goto growWalk;
                        checkTail = true;
                        // 0xbc7a5e0..0xbc7a629: allocate block and link at *r13
                        void* const g = allocator_global();           // no null check on g here [V]
                        void* const block = sub_eea6040(g, nullptr, sub_bc7a3d0_state::kBlockSize, 8ull);  // 0xbc7a610 call qword ptr [0xF99FFA0]
                        sub_eec6ed0(block, 0ull, sub_bc7a3d0_state::kBlockSize, 8ull);  // 0xbc7a624 call 0xEEC6ED0
                        *reinterpret_cast<void**>(r13) = block;       // 0xbc7a629 mov [r13],r14
                        *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(head) + 8) = block;  // 0xbc7a634 [head+8] = block
                        *reinterpret_cast<std::uint64_t*>(s + sub_bc7a3d0_state::kStateCapacityBytes) +=
                            sub_bc7a3d0_state::kBlockElemBytes;       // 0xbc7a63f head[0x10] += 0x28000
                        if (*reinterpret_cast<void**>(s + sub_bc7a3d0_state::kStateChainHead) != nullptr) goto growWalk;  // 0xbc7a64e jne 0xBC7A660
                        *reinterpret_cast<void**>(s + sub_bc7a3d0_state::kStateChainHead) = block;  // 0xbc7a654/658 [head] = block (first block)
                    growWalk:
                        // 0xbc7a660 cmp r12,0x28001; jb 0xBC7A691
                        if (remaining <= 0x28000ull) goto growFinalize;
                        // 0xbc7a669/66d r13 = [r13] + 0x28000 (&next->next); 0xbc7a670 r12 -= 0x28000
                        r13 = reinterpret_cast<std::uint8_t*>(
                                *reinterpret_cast<void**>(r13)) +
                            sub_bc7a3d0_state::kBlockElemBytes;
                        remaining -= sub_bc7a3d0_state::kBlockElemBytes;
                        // 0xbc7a677 cmp [r13],0; jne 0xBC7A660 ; 0xbc7a67e jmp 0xBC7A5E0 (allocate again without re-reading [r13])
                        if (*reinterpret_cast<void**>(r13) != nullptr) {
                            goto growWalk;                            // 0xbc7a67c taken
                        }
                        checkTail = false;                            // 0xbc7a67e not taken
                    }
                growFinalize:
                    // 0xbc7a691..0xbc7a6a2: rax=[head]; rcx=[head+0x10]
                    rdx = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint8_t*>(head) + 0x10) /
                              sub_bc7a3d0_state::kElemStride +
                          0x1000ull;                                  // 0xbc7a6a6..0xbc7a6b0
                }
            }
        } else {
            rdx = count;                                              // 0xbc7a6be with rdx=rdi
        }
    }

    // 0xbc7a6be..0xbc7a6da: r8 = rdx * 40; capacityBytes = max(capacityBytes, r8)
    {
        const std::uint64_t r8 = rdx * sub_bc7a3d0_state::kElemStride;   // shl rdx,3; lea r8,[rdx+rdx*4]
        std::uint64_t capacity = *reinterpret_cast<std::uint64_t*>(s + sub_bc7a3d0_state::kStateCapacityBytes);
        if (capacity > r8) capacity = r8;                              // cmova r8,rax
        *reinterpret_cast<std::uint64_t*>(s + sub_bc7a3d0_state::kStateCapacityBytes) = capacity;  // 0xbc7a6da
    }

    // 0xbc7a6d4..0xbc7a6e8: elemCount = [usedBytes] / 40; if elemCount >= count -> finalize
    elemCount = *reinterpret_cast<std::uint64_t*>(s + sub_bc7a3d0_state::kStateUsedBytes) /
                sub_bc7a3d0_state::kElemStride;
    if (elemCount < count) {                                           // cmp rdx,rdi; jae 0xBC7A77C not taken
        // 0xbc7a6ee..0xbc7a726: zero-initialize elements [elemCount, count)
        std::uint64_t idx = elemCount;                                 // rdx = elemCount (shr at 0xbc7a6e1)
        for (;;) {
            // 0xbc7a728..0xbc7a700: element address (inline or paged walk)
            sub_bc7a3d0_elem* const e = elemPtr(s, idx);
            // 0xbc7a703 mov [rcx],rax     rax = tombstone (lea rax,[0xF847A07] at 0xbc7a6ee)
            e->ptr = tombstone;
            // 0xbc7a706 mov dword ptr [rcx+8],0
            e->live = 0;
            ++idx;                                                     // 0xbc7a70d inc rdx
            // 0xbc7a710 movups [rcx+0x10],xmm0
            std::memset(e->zero0x10, 0, sizeof(e->zero0x10));
            // 0xbc7a714 mov byte ptr [rcx+0x20],0
            e->b0x20 = 0;
            // 0xbc7a718 mov dword ptr [rcx+0x22],0
            e->d0x22 = 0;
            // 0xbc7a71f mov byte ptr [rcx+0x26],0
            e->b0x26 = 0;
            // 0xbc7a723 cmp rdx,rdi; je 0xBC7A77C
            if (idx == count) break;
        }
    }

    // 0xbc7a77c..0xbc7a79b: finalize + epilogue
    //   rax = count * 40 (return value); [self+0x28008] = rax
    *reinterpret_cast<std::uint64_t*>(s + sub_bc7a3d0_state::kStateUsedBytes) =
        count * sub_bc7a3d0_state::kElemStride;   // 0xbc7a780/0xbc7a784
    return count * sub_bc7a3d0_state::kElemStride;  // rax at ret
}

static native::Footprint sub_bc7a3d0_footprint(sub_bc7a3d0_state* self) {
    // Bytes written directly by this function: [self, self+0x28018) covers the inline element
    // array plus chainHead/usedBytes/capacityBytes. Block pages reached via chainHead are
    // written directly by the zero-init loop and by the boundary allocator/memset calls; those
    // side effects are compared through the boundary tape (same convention as sub_bc6e550).
    return { { self, 0x28018ull } };
}

// Layout assertions (full set in sub_bc7a3d0.h; repeated here so liftcheck sees them).
static_assert(offsetof(native::bgfx::sub_bc7a3d0_elem, ptr) == 0x00, "sub_0xbc7a3d0: elem ptr at +0x00");
static_assert(offsetof(native::bgfx::sub_bc7a3d0_elem, live) == 0x08, "sub_0xbc7a3d0: elem live at +0x08");
static_assert(offsetof(native::bgfx::sub_bc7a3d0_elem, zero0x10) == 0x10, "sub_0xbc7a3d0: elem zero block at +0x10");
static_assert(offsetof(native::bgfx::sub_bc7a3d0_elem, b0x20) == 0x20, "sub_0xbc7a3d0: elem b0x20 at +0x20");
static_assert(offsetof(native::bgfx::sub_bc7a3d0_elem, d0x22) == 0x22, "sub_0xbc7a3d0: elem d0x22 at +0x22");
static_assert(offsetof(native::bgfx::sub_bc7a3d0_elem, b0x26) == 0x26, "sub_0xbc7a3d0: elem b0x26 at +0x26");
static_assert(sizeof(native::bgfx::sub_bc7a3d0_elem) == 0x28, "sub_0xbc7a3d0: elem size 0x28");
static_assert(offsetof(native::bgfx::sub_bc7a3d0_state, chainHead) == 0x28000, "sub_0xbc7a3d0: state chainHead at +0x28000");
static_assert(offsetof(native::bgfx::sub_bc7a3d0_state, usedBytes) == 0x28008, "sub_0xbc7a3d0: state usedBytes at +0x28008");
static_assert(offsetof(native::bgfx::sub_bc7a3d0_state, capacityBytes) == 0x28010, "sub_0xbc7a3d0: state capacityBytes at +0x28010");
static_assert(sizeof(native::bgfx::sub_bc7a3d0_state) == 0x28018, "sub_0xbc7a3d0: state size 0x28018");

// Verbatim log of every call instruction in [0xbc7a3d0, 0xbc7a79c) (rdis dis output,
// two spaces after the address):
#if 0
0xbc7a4fb  call r10
0xbc7a589  call qword ptr [0xF99FFA0]
0xbc7a610  call qword ptr [0xF99FFA0]
0xbc7a624  call 0xEEC6ED0
#endif
// Calls out of lifted code:
//   sub_eea6040 (0xeea6040, vendor boundary via data slot 0xF99FFA0, docs/data/native_boundary.tsv
//   row 506) x3: (g, e->ptr, 0, 0) in the destroy loop; (g, nullptr, 0x18, 8) and
//   (g, nullptr, 0x28008, 8) in the grow path. Read through the slot at every call.
//   sub_eec6ed0 (0xeec6ed0, crt boundary, row 507) x1: (block, 0, 0x28008, 8) = memset.
//   UNRESOLVED CALL = none: every call target is in docs/data/native_boundary.tsv.

LIFT_FN(sub_bc7a3d0, "sub_bc7a3d0", 0xbc7a3d0, sub_bc7a3d0, sub_bc7a3d0_footprint);

} // namespace native::bgfx
