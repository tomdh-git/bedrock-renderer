// LIFT 0xbc60f10 size 0x22a 1.26.62.01 commitSideTable
#include "client/features/render/native/bgfx/sub_bc60f10.h"
#include "client/features/render/native/Lift.h"

#include <cstddef>
#include <cstring>

namespace native {

// Layout assertions for every struct offset this function touches.
static_assert(offsetof(SideEntry, data) == native::kSideEntryDataOffset, "SideEntry::data must be at +0x00");
static_assert(offsetof(SideEntry, count) == native::kSideEntryCountOffset, "SideEntry::count must be at +0x08");
static_assert(sizeof(SideEntry) == native::kSideEntrySize, "SideEntry must be 0x10 bytes");
static_assert(offsetof(SideTable, used) == native::kSideTableUsedOffset, "SideTable::used must be at +0x410");
static_assert(sizeof(SideTable) == native::kSideTableSize, "SideTable must be 0x418 bytes");
static_assert(offsetof(Frame, m_sideTable) == native::kFrameSideTableOffset, "Frame::m_sideTable must be at +0x8B4778");

// Calls out of the lifted function (same calls, same order, as the original):
//   0xbc60f72  call qword ptr [0xF99FFA0]   realloc(alloc, nullptr, 0x418, 0, 0, 0)  allocate dst
//   0xbc60f86  call 0xEEC6ED0               memset(dst, 0, 0x410)
//   0xbc60ffc  call qword ptr [0xF99FFA0]   realloc(alloc, oldData, 0, 0, 0, 0)      free old entry array
//   0xbc61044  call qword ptr [0xF99FFA0]   realloc(alloc, nullptr, n*0x14, 0, 0, 0)  allocate entry array
//   0xbc61070  call 0xEBCE390               memcpy(p, source entry i data, n*0x14)
//   0xbc610f1  call qword ptr [0xF99FFA0]   realloc(alloc, entry data, 0, 0, 0, 0)    free entry array (stale-table clear)
//   0xbc61126  call 0xEEC6ED0               memset(dst, 0, 0x410) (allocator null path)
// The four [0xF99FFA0] calls have no static callee target: the slot holds sub_eea6040 (`jmp rax`)
// and rax is allocator->vtable[1] = realloc, loaded just before each call ([V] 0xbc60f4f-0xbc60f52 etc.).
// memset/memcpy (0xEEC6ED0, 0xEBCE390) are CRT intrinsics the compiler would inline [V].

extern "C" void commitSideTable(Frame* frame, std::uint32_t idx, const SideTable* src) {
    // 0xbc60f10..0xbc60f3d: prologue; dst = frame->m_sideTable[idx]; if src->used == 0 goto 0xbc610a9
    //   0xbc60f10  push r15
    //   0xbc60f12  push r14
    //   0xbc60f14  push r13
    //   0xbc60f16  push r12
    //   0xbc60f18  push rsi
    //   0xbc60f19  push rdi
    //   0xbc60f1a  push rbx
    //   0xbc60f1b  sub rsp,0x40
    //   0xbc60f1f  movaps [rsp+0x30],xmm6
    //   0xbc60f24  cmp dword ptr [r8+0x410],0
    //   0xbc60f2c  mov r14d,edx
    //   0xbc60f2f  mov rsi,[rcx+r14*8+0x8B4778]
    //   0xbc60f37  je 0xBC610A9
    SideTable* dst = frame->m_sideTable[idx];
    if (src->used == 0) {
        // 0xbc610a9..0xbc610d0: src->used == 0. dst == null or dst->used == 0 -> nothing to do.
        // Otherwise free every entry array and zero the table.
        //   0xbc610a9  test rsi,rsi
        //   0xbc610ac  je short 0xBC61094
        //   0xbc610ae  cmp dword ptr [rsi+0x410],0
        //   0xbc610b5  je short 0xBC61094
        //   0xbc610b7  mov rcx,[0x12ADF800]
        //   0xbc610be  test rcx,rcx
        //   0xbc610c1  je short 0xBC6111B
        //   0xbc610c3  xor edi,edi
        //   0xbc610c5  xorps xmm6,xmm6
        //   0xbc610c8  jmp short 0xBC6110E
        if (dst != nullptr && dst->used != 0) {
            AllocatorI* alloc = g_allocator();
            if (alloc == nullptr) {
                // 0xbc6111b..0xbc61126: allocator missing -> blanket memset of the 0x410-byte entry area
                //   0xbc6111b  mov r8d,0x410
                //   0xbc61121  mov rcx,rsi
                //   0xbc61124  xor edx,edx
                //   0xbc61126  call 0xEEC6ED0
                std::memset(dst, 0, 0x410);
            } else {
                // 0xbc610d0..0xbc61119: per entry (byte offset 0..0x400, step 0x10):
                // free entry data, then zero the 16-byte entry; stop when the offset reaches 0x410
                //   0xbc610d0  mov rdx,[rbx]
                //   0xbc610d3  mov rax,[rcx]
                //   0xbc610d6  mov rax,[rax+8]
                //   0xbc610da  mov dword ptr [rsp+0x28],0
                //   0xbc610e2  mov qword ptr [rsp+0x20],0
                //   0xbc610eb  xor r8d,r8d
                //   0xbc610ee  xor r9d,r9d
                //   0xbc610f1  call qword ptr [0xF99FFA0]
                //   0xbc610f7  mov rcx,[0x12ADF800]
                //   0xbc610fe  movups [rbx],xmm6
                //   0xbc61101  add rdi,0x10
                //   0xbc61105  cmp rdi,0x410
                //   0xbc6110c  je short 0xBC6112B
                //   0xbc6110e  lea rbx,[rsi+rdi]
                //   0xbc61112  test rcx,rcx
                //   0xbc61115  jne short 0xBC610D0
                //   0xbc61117  xor ecx,ecx
                //   0xbc61119  jmp short 0xBC610FE
                for (std::uint32_t i = 0; i < kSideTableStageCount; ++i) {
                    SideEntry& e = *(dst->entry + i);
                    allocatorRealloc(alloc, e.data, 0, 0, nullptr, 0);
                    e.data = nullptr;
                    e.count = 0;
                }
            }
            // 0xbc6112b..0xbc61135: dst->used = 0, then epilogue
            //   0xbc6112b  mov dword ptr [rsi+0x410],0
            //   0xbc61135  jmp 0xBC61094
            dst->used = 0;
        }
        // 0xbc61094..0xbc610a8: epilogue (shared with the normal return path)
        return;
    }

    // 0xbc60f3d..0xbc60f48: rbx = src, rdi = frame; allocate dst when it does not exist yet
    //   0xbc60f3d  mov rbx,r8
    //   0xbc60f40  mov rdi,rcx
    //   0xbc60f43  test rsi,rsi
    //   0xbc60f46  jne short 0xBC60F93
    //   0xbc60f48  mov rcx,[0x12ADF800]
    //   0xbc60f4f  mov rax,[rcx]
    //   0xbc60f52  mov rax,[rax+8]
    //   0xbc60f56  mov dword ptr [rsp+0x28],0
    //   0xbc60f5e  mov qword ptr [rsp+0x20],0
    //   0xbc60f67  mov r8d,0x418
    //   0xbc60f6d  xor edx,edx
    //   0xbc60f6f  xor r9d,r9d
    //   0xbc60f72  call qword ptr [0xF99FFA0]
    //   0xbc60f78  mov rsi,rax
    //   0xbc60f7b  mov r8d,0x410
    //   0xbc60f81  mov rcx,rax
    //   0xbc60f84  xor edx,edx
    //   0xbc60f86  call 0xEEC6ED0
    //   0xbc60f8b  mov [rdi+r14*8+0x8B4778],rsi
    if (dst == nullptr) {
        AllocatorI* alloc = g_allocator();   // null allocator dereferences [rcx] here, same as the original
        ReallocFn realloc = allocatorRealloc(alloc);
        dst = reinterpret_cast<SideTable*>(realloc(alloc, nullptr, kSideTableAllocSize, 0, nullptr, 0));
        std::memset(dst, 0, 0x410);
        frame->m_sideTable[idx] = dst;
    }

    // 0xbc60f93..0xbc60fb0: dst == src -> nothing to copy; otherwise walk the 0x41 entries
    //   0xbc60f93  cmp rsi,rbx
    //   0xbc60f96  je 0xBC6107A
    //   0xbc60f9c  xor r15d,r15d
    //   0xbc60f9f  xorps xmm6,xmm6
    //   0xbc60fa2  jmp short 0xBC60FC1
    //   0xbc60fa4  nop [rax+rax]
    //   0xbc60fb0  add r15,0x10
    //   0xbc60fb4  cmp r15,0x410
    //   0xbc60fbb  je 0xBC6107A
    if (dst != src) {
        AllocatorI* alloc = g_allocator();
        // 0xbc60fc1..0xbc6107a: copy entry i (i = 0..0x40): load count, free old array
        // (allocator present), zero the entry, allocate count*0x14, store data+count,
        // memcpy when the source entry data is non-null, advance i by 0x10, stop at 0x410.
        //   0xbc60fc1  mov r12,[rbx+r15+8]
        //   0xbc60fc6  mov rcx,[0x12ADF800]
        //   0xbc60fcd  test rcx,rcx
        //   0xbc60fd0  je 0xBC61050
        //   0xbc60fd6  lea r13,[rsi+r15]
        //   0xbc60fda  mov rdx,[r13]
        //   0xbc60fde  mov rax,[rcx]
        //   0xbc60fe1  mov rax,[rax+8]
        //   0xbc60fe5  mov dword ptr [rsp+0x28],0
        //   0xbc60fed  mov qword ptr [rsp+0x20],0
        //   0xbc60ff6  xor r8d,r8d
        //   0xbc60ff9  xor r9d,r9d
        //   0xbc60ffc  call qword ptr [0xF99FFA0]
        //   0xbc61002  mov rdx,[0x12ADF800]
        //   0xbc61009  movups [r13],xmm6
        //   0xbc6100e  mov ecx,0
        //   0xbc61013  test rdx,rdx
        //   0xbc61016  je short 0xBC61052
        //   0xbc61018  lea rax,[r12*4]
        //   0xbc61020  lea r8,[rax+rax*4]
        //   0xbc61024  mov rax,[rdx]
        //   0xbc61027  mov rax,[rax+8]
        //   0xbc6102b  mov dword ptr [rsp+0x28],0
        //   0xbc61033  mov qword ptr [rsp+0x20],0
        //   0xbc6103c  mov rcx,rdx
        //   0xbc6103f  xor edx,edx
        //   0xbc61041  xor r9d,r9d
        //   0xbc61044  call qword ptr [0xF99FFA0]
        //   0xbc6104a  mov rcx,rax
        //   0xbc6104d  jmp short 0xBC61052
        //   0xbc6104f  nop
        //   0xbc61050  xor ecx,ecx
        //   0xbc61052  mov [rsi+r15],rcx
        //   0xbc61056  mov [rsi+r15+8],r12
        //   0xbc6105b  mov rdx,[rbx+r15]
        //   0xbc6105f  test rdx,rdx
        //   0xbc61062  je 0xBC60FB0
        //   0xbc61068  shl r12,2
        //   0xbc6106c  lea r8,[r12+r12*4]
        //   0xbc61070  call 0xEBCE390
        //   0xbc61075  jmp 0xBC60FB0
        for (std::uint32_t i = 0; i < kSideTableStageCount; ++i) {
            const SideEntry& se = *(src->entry + i);
            SideEntry& e = *(dst->entry + i);
            const std::uint64_t n = se.count;
            void* oldData = e.data;
            if (alloc != nullptr) {
                allocatorRealloc(alloc, oldData, 0, 0, nullptr, 0);   // free the old array
            }
            e.data = nullptr;   // movups [entry],xmm6 zeroes data and count
            e.count = 0;
            void* p = alloc != nullptr
                ? allocatorRealloc(alloc, nullptr, n * kBindingSize, 0, nullptr, 0)
                : nullptr;
            e.data = p;
            e.count = n;
            if (se.data != nullptr) {
                std::memcpy(p, se.data, n * kBindingSize);
            }
            // 0xbc61075: jmp 0xBC60FB0 (i += 0x10; exit when i == 0x410)
        }
    }

    // 0xbc6107a..0xbc61094: dst->used = src->used (stored twice in the original, via both pointers)
    //   0xbc6107a  mov eax,[rbx+0x410]
    //   0xbc61080  mov [rsi+0x410],eax
    //   0xbc61086  mov rcx,[rdi+r14*8+0x8B4778]
    //   0xbc6108e  mov [rcx+0x410],eax
    dst->used = src->used;
    // 0xbc61094..0xbc610a8: epilogue
    //   0xbc61094  movaps xmm6,[rsp+0x30]
    //   0xbc61099  add rsp,0x40
    //   0xbc6109d  pop rbx
    //   0xbc6109e  pop rdi
    //   0xbc6109f  pop rsi
    //   0xbc610a0  pop r12
    //   0xbc610a2  pop r13
    //   0xbc610a4  pop r14
    //   0xbc610a6  pop r15
    //   0xbc610a8  ret
}

static native::Footprint commitSideTableFootprint(Frame* frame, std::uint32_t idx, const SideTable* /*src*/) {
    native::Footprint fp;
    fp.push_back({reinterpret_cast<void*>(&frame->m_sideTable[idx]), sizeof(SideTable*)});
    if (frame != nullptr) {
        SideTable* dst = frame->m_sideTable[idx];
        if (dst != nullptr) {
            fp.push_back({dst->entry, sizeof(dst->entry)});
            fp.push_back({reinterpret_cast<void*>(&dst->used), sizeof(dst->used)});
        }
    }
    // The memcpy targets are freshly allocated buffers (realloc with nullptr); they carry no
    // pre-state that the differential snapshot needs to capture.
    return fp;
}

LIFT_FN(commitSideTable, "native::commitSideTable", 0xbc60f10, commitSideTable, commitSideTableFootprint);

} // namespace native
