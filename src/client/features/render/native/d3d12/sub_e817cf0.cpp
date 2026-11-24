// LIFT 0xe817cf0 size 0x15a 1.26.62.01 sub_e817cf0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e817cf0.h"

#include <cstddef>
#include <cstdint>

static_assert(sizeof(void*) == 8, "ptr");

// Verbatim disassembly of [0xe817cf0, 0xe817e4a) (Minecraft Windows 1.26.62.01).
#if 0
0xe817cf0  push r15
0xe817cf2  push r14
0xe817cf4  push r13
0xe817cf6  push r12
0xe817cf8  push rsi
0xe817cf9  push rdi
0xe817cfa  push rbp
0xe817cfb  push rbx
0xe817cfc  sub rsp,0x48
0xe817d00  mov [rsp+0x36],dx
0xe817d05  mov rax,[rsp+0xB0]
0xe817d0d  mov [rsp+0x40],rax
0xe817d12  mov r12,[rcx+0x19F60]
0xe817d19  mov [rsp+0x38],rcx
0xe817d1e  mov r13,[rcx+0x19F68]
0xe817d25  cmp r12,r13
0xe817d28  je 0xE817E1F
0xe817d2e  movzx ebp,word ptr [rsp+0x36]
0xe817d33  movsxd rdi,r8d
0xe817d36  movzx esi,r9w
0xe817d3a  jmp short 0xE817D8B
0xe817d3c  nop [rax]
0xe817d40  mov rax,[rcx]
0xe817d43  mov rax,[rax+8]
0xe817d47  mov dword ptr [rsp+0x28],0
0xe817d4f  mov qword ptr [rsp+0x20],0
0xe817d58  xor edx,edx
0xe817d5a  mov r8,r14
0xe817d5d  xor r9d,r9d
0xe817d60  call qword ptr [0xF99FFA0]
0xe817d66  mov r15,rax
0xe817d69  mov rcx,r15
0xe817d6c  xor edx,edx
0xe817d6e  mov r8,r14
0xe817d71  call 0xEBCE430
0xe817d76  mov [rbx+rbp*8+0x1250],r15
0xe817d7e  add r12,8
0xe817d82  cmp r12,r13
0xe817d85  je 0xE817E1F
0xe817d8b  mov rbx,[r12]
0xe817d8f  mov rdx,[rbx+rbp*8+0x1250]
0xe817d97  mov rcx,[0x12ADF800]
0xe817d9e  test rdx,rdx
0xe817da1  je short 0xE817DD3
0xe817da3  test rcx,rcx
0xe817da6  je short 0xE817E00
0xe817da8  mov rax,[rcx]
0xe817dab  mov rax,[rax+8]
0xe817daf  mov dword ptr [rsp+0x28],0
0xe817db7  mov qword ptr [rsp+0x20],0
0xe817dc0  xor r8d,r8d
0xe817dc3  xor r9d,r9d
0xe817dc6  call qword ptr [0xF99FFA0]
0xe817dcc  mov rcx,[0x12ADF800]
0xe817dd3  lea rax,[0xF441930]
0xe817dda  mov r14d,[rax+rdi*4]
0xe817dde  imul r14d,esi
0xe817de2  add r14d,0xF
0xe817de6  and r14d,0xFFFFFFF0
0xe817dea  test rcx,rcx
0xe817ded  jne 0xE817D40
0xe817df3  xor r15d,r15d
0xe817df6  jmp 0xE817D69
0xe817dfb  nop [rax+rax]
0xe817e00  lea rax,[0xF441930]
0xe817e07  mov r14d,[rax+rdi*4]
0xe817e0b  imul r14d,esi
0xe817e0f  add r14d,0xF
0xe817e13  and r14d,0xFFFFFFF0
0xe817e17  xor r15d,r15d
0xe817e1a  jmp 0xE817D69
0xe817e1f  mov rcx,[rsp+0x38]
0xe817e24  add rcx,0xC9AA98
0xe817e2b  movzx edx,word ptr [rsp+0x36]
0xe817e30  mov r8,[rsp+0x40]
0xe817e35  add rsp,0x48
0xe817e39  pop rbx
0xe817e3a  pop rbp
0xe817e3b  pop rdi
0xe817e3c  pop rsi
0xe817e3d  pop r12
0xe817e3f  pop r13
0xe817e41  pop r14
0xe817e43  pop r15
0xe817e45  jmp 0xE804590
#endif

namespace native::d3d12 {

namespace {

// The single data-slot call used for both the release and the allocate:
//   0xe817d60 / 0xe817dc6  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
// The two instructions that precede each call (`mov rax,[rcx]` ; `mov rax,[rax+8]`)
// load vtable[1] into rax, but the call goes through the slot and never reads rax,
// so in the original they are dead loads. They are reproduced here (volatile) so the
// lifted function performs the same reads at the same point.
using SlotFn = void* (*)(void* rcx, void* rdx, std::uint64_t r8, std::uint64_t r9,
                         std::uint64_t stack5, std::uint32_t stack6);

void deadVtableLoad(void* obj) {
    void* volatile vt = *reinterpret_cast<void* volatile*>(obj);    // mov rax,[rcx]
    void* volatile slot1 = reinterpret_cast<void**>(vt)[1];         // mov rax,[rax+8]  (vtable[1])
    (void)vt;
    (void)slot1;
}

SlotFn loadSlot(std::uintptr_t base) {
    // read the function pointer out of the slot at call time (call qword ptr [0xF99FFA0])
    return reinterpret_cast<SlotFn>(*reinterpret_cast<void**>(base + kIndCallSlotRva));
}

} // namespace

extern "C" void sub_e817cf0(void* a0, std::uint16_t a1, std::int32_t a2, std::uint16_t a3, std::uint64_t a4) {
    const std::uintptr_t base = RewriteRegistry::imageBase();
    char* const self = static_cast<char*>(a0);                        // mov [rsp+0x38],rcx

    const std::uint16_t handle = a1;                                  // movzx ebp,word ptr [rsp+0x36]
    const std::int64_t  idx    = static_cast<std::int64_t>(a2);       // movsxd rdi,r8d
    const std::uint32_t mul    = static_cast<std::uint32_t>(a3);      // movzx esi,r9w
    const std::uint64_t arg4   = a4;                                  // mov rax,[rsp+0xB0] ; mov [rsp+0x40],rax

    // 0xe817d12..0xe817d28  iterate [this+0x19F60 .. this+0x19F68); empty range -> tail
    char** it  = *reinterpret_cast<char***>(self + kContextBeginOff); // mov r12,[rcx+0x19F60]
    char** end = *reinterpret_cast<char***>(self + kContextEndOff);   // mov r13,[rcx+0x19F68]

    while (it != end) {                                               // cmp r12,r13 ; je 0xE817E1F
        // 0xe817d8b..0xe817d97
        char* const ctx   = *it;                                      // mov rbx,[r12]
        void** const slot = reinterpret_cast<void**>(ctx + handle * kContextStride + kBufArrayOff); // [rbx+rbp*8+0x1250]
        void* const old   = *slot;                                    // mov rdx,[rbx+rbp*8+0x1250]
        void* alloc = *reinterpret_cast<void**>(base + kAllocatorGlobalRva); // mov rcx,[0x12ADF800]

        // 0xe817d9e..0xe817dcc  release the previous buffer (only when old != 0 and allocator != 0)
        if (old != nullptr && alloc != nullptr) {
            deadVtableLoad(alloc);                                    // mov rax,[rcx] ; mov rax,[rax+8]
            loadSlot(base)(alloc, old, 0, 0, 0, 0);                   // call qword ptr [0xF99FFA0]  (release)
            alloc = *reinterpret_cast<void**>(base + kAllocatorGlobalRva); // mov rcx,[0x12ADF800]
        }

        // 0xe817dd3..0xe817e1a  size = (sizeTable[idx] * mul + 0xF) & ~0xF  (round up to 16)
        std::uint32_t size = *reinterpret_cast<std::uint32_t*>(base + kSizeTableRva + idx * 4); // mov r14d,[rax+rdi*4]
        size = size * mul;                                            // imul r14d,esi
        size = (size + kSizeRoundAdd) & kSizeAlignMask;              // add r14d,0xF ; and r14d,0xFFFFFFF0

        // 0xe817dea..0xe817d66  allocate a fresh buffer when the allocator is present
        void* newbuf;
        if (alloc != nullptr) {                                       // test rcx,rcx ; jne 0xE817D40
            deadVtableLoad(alloc);                                    // mov rax,[rcx] ; mov rax,[rax+8]
            newbuf = loadSlot(base)(alloc, nullptr, size, 0, 0, 0);   // call qword ptr [0xF99FFA0]  (alloc) -> rax
        } else {
            newbuf = nullptr;                                         // xor r15d,r15d
        }

        // 0xe817d69..0xe817d76  zero-fill the new buffer and store the pointer
        native::sub_ebce430(newbuf, 0, size);                         // call 0xEBCE430
        *slot = newbuf;                                               // mov [rbx+rbp*8+0x1250],r15

        ++it;                                                         // add r12,8 ; cmp r12,r13 ; je 0xE817E1F
    }

    // 0xe817e1f..0xe817e45  tail call sub_e804590(this + 0xC9AA98, handle, arg4)
    native::sub_e804590(self + kTailThisOff, handle, arg4);           // jmp 0xE804590
}

} // namespace native::d3d12

// Registry entry: NAME is the registry key / Sigs.json symbol (sig anchors are appended at the milestone gate).
LIFT_FN(sub_e817cf0, "sub_e817cf0", 0xe817cf0, native::d3d12::sub_e817cf0, nullptr);