// LIFT 0xbc45c40 size 0x16b 1.26.62.01 BgfxFrameBuilder slot 0
#include "client/features/render/native/bgfx/sub_bc45c40.h"

#include <atomic>
#include <cstdint>
#include <cstdlib>

// Layout assertions used by this function (full set in sub_bc45c40.h).
static_assert(offsetof(native::bgfx::FbSlot0, mCount) == 0x10,
              "sub_bc45c40 reads/writes this+0x10 as count");
static_assert(offsetof(native::bgfx::FbSlot0, mCapacity) == 0x20,
              "sub_bc45c40 branches on this+0x20 capacity");
static_assert(offsetof(native::bgfx::FbSlot0, mFree) == 0x28,
              "sub_bc45c40 uses this+0x28 as free-list head");
static_assert(offsetof(native::bgfx::FbSlot0Node, mNext) == 0x1030,
              "sub_bc45c40 uses node+0x1030 as claim count");
static_assert(offsetof(native::bgfx::FbSlot0Node, mBack) == 0x1038,
              "sub_bc45c40 writes node+0x1038 on pop/alloc");
static_assert(offsetof(native::bgfx::FbSlot0Node, mInit) == 0x1040,
              "sub_bc45c40 writes node+0x1040 = 1");
static_assert(sizeof(native::bgfx::FbSlot0Node) == 0x1048,
              "allocated node size is 0x1048");

// Verbatim call instructions from the disassembly of [0xbc45c40, 0xbc45dab):
// 0xbc45d3e  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040, imported allocator: block = malloc(0x1048)
// 0xbc45da4  call 0x9BC830                ; -> sub_9bc830, boundary alloc out-of-memory handler (noreturn), 0xbc45da9 jmp short 0xBC45D4C is dead code
// UNRESOLVED CALL = none.
// Every instruction of [0xbc45c40, 0xbc45dab), verbatim (verify_oc quotes):
// `0xbc45c40  push rsi`
// `0xbc45c41  sub rsp,0x20`
// `0xbc45c45  mov rax,[rcx+0x10]`
// `0xbc45c49  cmp rax,[rcx+0x20]`
// `0xbc45c4d  jae short 0xBC45C79`
// `0xbc45c4f  mov eax,1`
// `0xbc45c54  lock xadd [rcx+0x10],rax`
// `0xbc45c5a  cmp rax,[rcx+0x20]`
// `0xbc45c5e  setae dl`
// `0xbc45c61  mov rsi,[rcx+0x18]`
// `0xbc45c65  test rsi,rsi`
// `0xbc45c68  sete r8b`
// `0xbc45c6c  or r8b,dl`
// `0xbc45c6f  cmp r8b,1`
// `0xbc45c73  jne 0xBC45D82`
// `0xbc45c79  mov rdx,[rcx+0x28]`
// `0xbc45c7d  test rdx,rdx`
// `0xbc45c80  je 0xBC45D23`
// `0xbc45c86  mov rsi,rdx`
// `0xbc45c89  mov r8,rdx`
// `0xbc45c8c  jmp short 0xBC45CA3`
// `0xbc45c8e  xchg ax,ax`
// `0xbc45c90  mov rdx,[rcx+0x28]`
// `0xbc45c94  mov rsi,rdx`
// `0xbc45c97  mov r8,rdx`
// `0xbc45c9a  test rdx,rdx`
// `0xbc45c9d  je 0xBC45D23`
// `0xbc45ca3  mov eax,[rsi+0x1030]`
// `0xbc45ca9  test eax,0x7FFFFFFF`
// `0xbc45cae  je short 0xBC45C90`
// `0xbc45cb0  lea edx,[rax+1]`
// `0xbc45cb3  lock cmpxchg [rsi+0x1030],edx`
// `0xbc45cbb  jne short 0xBC45C90`
// `0xbc45cbd  mov rdx,[rsi+0x1038]`
// `0xbc45cc4  mov rax,r8`
// `0xbc45cc7  lock cmpxchg [rcx+0x28],rdx`
// `0xbc45ccd  je 0xBC45D8E`
// `0xbc45cd3  mov rdx,rax`
// `0xbc45cd6  mov eax,0xFFFFFFFF`
// `0xbc45cdb  lock xadd [rsi+0x1030],eax`
// `0xbc45ce3  cmp eax,0x80000001`
// `0xbc45ce8  jne short 0xBC45C94`
// `0xbc45cea  mov rax,[rcx+0x28]`
// `0xbc45cee  xchg ax,ax`
// `0xbc45cf0  mov [rsi+0x1038],rax`
// `0xbc45cf7  mov dword ptr [rsi+0x1030],1`
// `0xbc45d01  lock cmpxchg [rcx+0x28],r8`
// `0xbc45d07  je short 0xBC45C94`
// `0xbc45d09  mov r9d,0x7FFFFFFF`
// `0xbc45d0f  lock xadd [rsi+0x1030],r9d`
// `0xbc45d18  cmp r9d,1`
// `0xbc45d1c  je short 0xBC45CF0`
// `0xbc45d1e  jmp 0xBC45C94`
// `0xbc45d23  mov rsi,rdx`
// `0xbc45d26  test rdx,rdx`
// `0xbc45d29  jne short 0xBC45D96`
// `0xbc45d2b  mov rcx,[0x1233E1A8]`
// `0xbc45d32  mov rax,[rcx]`
// `0xbc45d35  mov rax,[rax+8]`
// `0xbc45d39  mov edx,0x1048`
// `0xbc45d3e  call qword ptr [0xF99FFA0]`
// `0xbc45d44  mov rsi,rax`
// `0xbc45d47  test rax,rax`
// `0xbc45d4a  je short 0xBC45D9F`
// `0xbc45d4c  mov qword ptr [rsi+0x1038],0`
// `0xbc45d57  xorps xmm0,xmm0`
// `0xbc45d5a  movups [rsi+0x1000],xmm0`
// `0xbc45d61  movups [rsi+0x1010],xmm0`
// `0xbc45d68  movups [rsi+0x1020],xmm0`
// `0xbc45d6f  mov dword ptr [rsi+0x1030],0`
// `0xbc45d79  mov byte ptr [rsi+0x1040],1`
// `0xbc45d80  jmp short 0xBC45D96`
// `0xbc45d82  imul rax,0x1048`
// `0xbc45d89  add rsi,rax`
// `0xbc45d8c  jmp short 0xBC45D96`
// `0xbc45d8e  lock add dword ptr [rsi+0x1030],0xFFFFFFFE`
// `0xbc45d96  mov rax,rsi`
// `0xbc45d99  add rsp,0x20`
// `0xbc45d9d  pop rsi`
// `0xbc45d9e  ret`
// `0xbc45d9f  mov ecx,0x1048`
// `0xbc45da4  call 0x9BC830`
// `0xbc45da9  jmp short 0xBC45D4C`

namespace native::bgfx {

extern "C" __declspec(noreturn) void sub_9bc830(std::uint64_t allocSize);  // 0x9BC830: boundary alloc (class alloc, native_boundary.tsv oc_U-EX0b1.md)

extern "C" void* sub_bc45c40(FbSlot0* that)
{
    // 0xbc45c40  push rsi                     (prologue)
    // 0xbc45c41  sub rsp,0x20                 (prologue)

    // 0xbc45c45  mov rax,[rcx+0x10]           // mCount
    // 0xbc45c49  cmp rax,[rcx+0x20]           // mCapacity
    // 0xbc45c4d  jae short 0xBC45C79          // count >= capacity -> pop from the free list
    if (that->mCount.load(std::memory_order_relaxed) >= that->mCapacity)
        goto pop_list;

    // 0xbc45c4f  mov eax,1
    // 0xbc45c54  lock xadd [rcx+0x10],rax     // mCount += 1; rax = old count
    const std::uint32_t oldCount = that->mCount.fetch_add(1u, std::memory_order_seq_cst);

    // 0xbc45c5a  cmp rax,[rcx+0x20]
    // 0xbc45c5e  setae dl                     // dl = (oldCount >= mCapacity)
    const bool full = oldCount >= that->mCapacity;

    // 0xbc45c61  mov rsi,[rcx+0x18]           // mBase
    // 0xbc45c65  test rsi,rsi
    // 0xbc45c68  sete r8b                     // r8b = (mBase == 0)
    // 0xbc45c6c  or r8b,dl                    // r8b = full || (mBase == 0)
    FbSlot0Node* const base = that->mBase;
    const bool needSlot = full || (base == nullptr);

    // 0xbc45c6f  cmp r8b,1
    // 0xbc45c73  jne 0xBC45D82                // hand out slab slot oldCount
    if (needSlot) {
        // 0xbc45d82  imul rax,0x1048          // rax = oldCount * 0x1048
        // 0xbc45d89  add rsi,rax              // rsi = mBase + oldCount * 0x1048 (mBase may be null)
        // 0xbc45d8c  jmp short 0xBC45D96      // epilogue: rax = rsi
        return reinterpret_cast<void*>(
            reinterpret_cast<std::uintptr_t>(base) +
            static_cast<std::uintptr_t>(oldCount) * 0x1048ULL);   // 0xbc45d96  mov rax,rsi (return value)
    }

pop_list:                                    // 0xbc45c79  mov rdx,[rcx+0x28]   // mFree
    // 0xbc45c7d  test rdx,rdx
    // 0xbc45c80  je 0xBC45D23                 // empty list -> allocate a fresh node
    // 0xbc45c86  mov rsi,rdx                  // candidate node
    // 0xbc45c89  mov r8,rdx                   // snapshot candidate (expected head for the pop CAS)
    // 0xbc45c8c  jmp short 0xBC45CA3
    // 0xbc45c8e  xchg ax,ax                   // padding nop
    FbSlot0Node* head = that->mFree.load(std::memory_order_relaxed);
    if (head == nullptr)
        goto allocate_node;

retry_pop:                                   // 0xbc45c90  mov rdx,[rcx+0x28]
    head = that->mFree.load(std::memory_order_relaxed);
    // 0xbc45c94  mov rsi,rdx                  // candidate node
    // 0xbc45c97  mov r8,rdx                   // snapshot candidate (expected head for the pop CAS)
    // 0xbc45c9a  test rdx,rdx
    // 0xbc45c9d  je 0xBC45D23                 // empty -> allocate
    FbSlot0Node* const node = head;
    const FbSlot0Node* const snap = head;
    if (node == nullptr)
        goto allocate_node;

claim:                                        // 0xbc45ca3  mov eax,[rsi+0x1030]   // node->mNext
    // 0xbc45ca9  test eax,0x7FFFFFFF
    // 0xbc45cae  je short 0xBC45C90           // claim count 0 -> reload
    std::uint32_t next = node->mNext.load(std::memory_order_relaxed);
    if ((next & 0x7FFFFFFFu) == 0u)
        goto retry_pop;

    // 0xbc45cb0  lea edx,[rax+1]
    // 0xbc45cb3  lock cmpxchg [rsi+0x1030],edx   // node->mNext: next -> next + 1 (claim)
    // 0xbc45cbb  jne short 0xBC45C90            // lost the race -> reload
    const std::uint32_t claimed = next + 1u;
    if (!node->mNext.compare_exchange_strong(next, claimed, std::memory_order_seq_cst))
        goto retry_pop;

    // 0xbc45cbd  mov rdx,[rsi+0x1038]         // desired new head = node->mBack
    // 0xbc45cc4  mov rax,r8                   // expected = snap (candidate at entry of this pass)
    // 0xbc45cc7  lock cmpxchg [rcx+0x28],rdx  // mFree = node->mBack, only if mFree == snap
    // 0xbc45ccd  je 0xBC45D8E                 // pop succeeded
    std::uint64_t expected = static_cast<std::uint64_t>(reinterpret_cast<std::uintptr_t>(snap));
    const std::uint64_t back = node->mBack;
    if (that->mFree.compare_exchange_strong(expected, back, std::memory_order_seq_cst)) {
        // 0xbc45ccd  je 0xBC45D8E
        // 0xbc45d8e  lock add dword ptr [rsi+0x1030],0xFFFFFFFE   // claim - 2
        node->mNext.fetch_add(0xFFFFFFFEu, std::memory_order_seq_cst);
        // 0xbc45d96  mov rax,rsi              // return the popped node
        // 0xbc45d99  add rsp,0x20
        // 0xbc45d9d  pop rsi
        // 0xbc45d9e  ret
        return reinterpret_cast<void*>(node);
    }
    // 0xbc45cd3  mov rdx,rax                 // rax = current mFree (failed cmpxchg stores it into expected)
    // 0xbc45cd6  mov eax,0xFFFFFFFF
    // 0xbc45cdb  lock xadd [rsi+0x1030],eax   // node->mNext -= 1; rax = old claim count
    // 0xbc45ce3  cmp eax,0x80000001
    // 0xbc45ce8  jne short 0xBC45C94          // old != 0x80000001 -> reload (candidate = current head)
    const std::uint32_t prev = node->mNext.fetch_add(0xFFFFFFFFu, std::memory_order_seq_cst);
    if (prev != 0x80000001u)
        goto retry_pop;
    // 0xbc45cea  mov rax,[rcx+0x28]           // current head (already in `expected`)
    // 0xbc45cee  xchg ax,ax                   // padding nop
cf0:
    // 0xbc45cf0  mov [rsi+0x1038],rax         // node->mBack = current head
    // 0xbc45cf7  mov dword ptr [rsi+0x1030],1 // node->mNext = 1
    node->mBack = expected;
    node->mNext.store(1u, std::memory_order_seq_cst);
    // 0xbc45d01  lock cmpxchg [rcx+0x28],r8   // install snap as head if mFree == expected
    // 0xbc45d07  je short 0xBC45C94           // installed -> reload
    if (that->mFree.compare_exchange_strong(expected,
                                            static_cast<std::uint64_t>(reinterpret_cast<std::uintptr_t>(snap)),
                                            std::memory_order_seq_cst))
        goto retry_pop;
    // 0xbc45d09  mov r9d,0x7FFFFFFF
    // 0xbc45d0f  lock xadd [rsi+0x1030],r9d   // node->mNext += 0x7FFFFFFF; r9d = old claim count
    // 0xbc45d18  cmp r9d,1
    // 0xbc45d1c  je short 0xBC45CF0           // old == 1 -> back=head, mNext=1, retry install
    // 0xbc45d1e  jmp 0xBC45C94                // otherwise reload
    const std::uint32_t prev2 = node->mNext.fetch_add(0x7FFFFFFFu, std::memory_order_seq_cst);
    if (prev2 == 1u)
        goto cf0;
    goto retry_pop;

allocate_node:                               // 0xbc45d23  mov rsi,rdx          (entered with rsi == rdx == 0)
    // 0xbc45d26  test rdx,rdx
    // 0xbc45d29  jne short 0xBC45D96          // not taken here: we only enter with rdx == 0
    // 0xbc45d2b  mov rcx,[0x1233E1A8]         // global allocator object
    // 0xbc45d32  mov rax,[rcx]                // vtable
    // 0xbc45d35  mov rax,[rax+8]              // vtable slot 1 (dead: the call target is the IAT slot [0xF99FFA0])
    {
        void* const allocator = *reinterpret_cast<void* const volatile*>(0x1233E1A8ULL);
        (void)*reinterpret_cast<void* const volatile*>(allocator);
        (void)*reinterpret_cast<void* const volatile*>(reinterpret_cast<std::uint8_t*>(allocator) + 8);
    }
    // 0xbc45d39  mov edx,0x1048
    // 0xbc45d3e  call qword ptr [0xF99FFA0]   // sub_eea6040: imported allocator, block = malloc(0x1048)
    FbSlot0Node* const block = reinterpret_cast<FbSlot0Node*>(std::malloc(0x1048));
    // 0xbc45d44  mov rsi,rax
    // 0xbc45d47  test rax,rax
    // 0xbc45d4a  je short 0xBC45D9F           // allocation failed -> out-of-memory handler
    if (block == nullptr) {
        // 0xbc45d9f  mov ecx,0x1048
        // 0xbc45da4  call 0x9BC830            // sub_9bc830(0x1048): boundary alloc OOM handler (noreturn)
        // 0xbc45da9  jmp short 0xBC45D4C      // dead code: sub_9bc830 does not return
        sub_9bc830(0x1048);
    }
    // 0xbc45d4c  mov qword ptr [rsi+0x1038],0   // block->mBack = 0
    block->mBack = 0;
    // 0xbc45d57  xorps xmm0,xmm0
    // 0xbc45d5a  movups [rsi+0x1000],xmm0       // [block+0x1000, block+0x1030) = 0  (48 bytes)
    // 0xbc45d61  movups [rsi+0x1010],xmm0
    // 0xbc45d68  movups [rsi+0x1020],xmm0
    {
        std::uint64_t* const z = reinterpret_cast<std::uint64_t*>(&block->mReserved0000[0x1000]);
        z[0] = 0; z[1] = 0; z[2] = 0; z[3] = 0; z[4] = 0; z[5] = 0;
    }
    // 0xbc45d6f  mov dword ptr [rsi+0x1030],0   // block->mNext = 0
    block->mNext.store(0u, std::memory_order_seq_cst);
    // 0xbc45d79  mov byte ptr [rsi+0x1040],1    // block->mInit = 1
    block->mInit = 1;
    // 0xbc45d80  jmp short 0xBC45D96
    goto done;                                // 0xbc45d96  mov rax,rsi (return block)

done:
    // 0xbc45d99  add rsp,0x20
    // 0xbc45d9d  pop rsi
    // 0xbc45d9e  ret
    return reinterpret_cast<void*>(block);
}

LIFT_FN(sub_bc45c40, "sub_bc45c40", 0xbc45c40, sub_bc45c40, nullptr);

} // namespace native::bgfx
