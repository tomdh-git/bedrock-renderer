// LIFT 0xbc6ef50 size 0xf1 1.26.62.01 sub_bc6ef50
#include "client/features/render/native/bgfx/sub_bc6ef50.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstring>

// Full function extent: 0xbc6ef50..0xbc6f041 (size 0xf1). Every instruction in this range
// is covered by the range citation above; individual call instructions are quoted below.
// Verbatim log of every call instruction in [0xbc6ef50, 0xbc6f041) (rdis dis output,
// two spaces after the address):
#if 0
0xbc6ef7e  call 0xEBDBF10
0xbc6efcc  call 0xEEC6EC0
0xbc6efe4  call 0xEBCE5E0
0xbc6f006  call 0xEBCE650
0xbc6f02a  call 0xEBDBF20
#endif
// All five call targets are lift-classified helpers (sub_ebdbf10 lock, sub_eec6ec0 memcpy,
// sub_ebce5e0 bounded strlen, sub_ebce650 bounded copy, sub_ebdbf20 unlock). No indirect
// calls, no data slots, every call target is in the lift set.

namespace native::bgfx {

// Layout assertions (definitions live in sub_bc6ef50.h; repeated here so liftcheck
// sees them in the source file).
static_assert(offsetof(native::bgfx::FrameBlock, data) == 0x00, "sub_bc6ef50: FrameBlock::data must be at +0x00");
static_assert(sizeof(native::bgfx::FrameBlock) == 0x138, "sub_bc6ef50: FrameBlock must be 0x138 bytes");

// x64 Microsoft ABI:
//   rcx = void* a0    this / a0 (reads uint16_t count at a0+0x4E8, block array base at a0+0x4F0)
//   rdx = int   a2    count cap (arg2), unsigned; effective count = min(cap, *(uint16_t*)(a0+0x4E8))
//   r8  = void* a3    destination block base (must be non-null; each block gets 0x138 bytes +
//                     a bounded string copy at its start)
//   r9 = unused
//   return = int      number of blocks processed (esi), or 0 if effective count == 0;
//                     if a3 == nullptr, returns the raw count from a0+0x4E8 uncapped
extern "C" int sub_bc6ef50(void* a0, int a2, void* a3) noexcept {
    // 0xbc6ef50..0xbc6ef7d: prologue — push rbp/r15/r14/r12/rsi/rdi/rbx; sub rsp,0x40;
    // lea rbp,[rsp+0x40]; [rbp-8] = -2 (EH state slot, never read).
    void* dstBase = a3;              // 0xbc6ef6b  mov rdi,r8
    int cap = a2;                    // 0xbc6ef6e  mov r14d,edx
    uint8_t* a0b = reinterpret_cast<uint8_t*>(a0);
    void* lockAddr = reinterpret_cast<void*>(a0b + 0x3D0);  // 0xbc6ef74  lea r15,[rcx+0x3D0]

    // 0xbc6ef7e: call sub_ebdbf10(lockAddr) [lock]
    ::native::sub_ebdbf10(lockAddr);

    // 0xbc6ef83: esi = movzx word [rbx+0x4E8]  (raw count from a0+0x4E8)
    uint16_t rawCount = *reinterpret_cast<uint16_t*>(a0b + 0x4E8);
    int esi = static_cast<int>(rawCount);

    // 0xbc6ef8a: test rdi,rdi; 0xbc6ef8d: je loc_bc6f027  (dst==nullptr: skip to unlock,
    // return raw count uncapped)
    if (dstBase == nullptr) {
        ::native::sub_ebdbf20(lockAddr);
        return esi;
    }

    // 0xbc6ef93: cmp r14w, si; 0xbc6ef97: cmovb esi, r14d
    //   esi = min((uint16_t)cap, (uint16_t)rawCount)  [unsigned 16-bit compare]
    uint16_t cap16 = static_cast<uint16_t>(cap);
    uint16_t count16 = static_cast<uint16_t>(rawCount);
    if (cap16 < count16) {
        esi = static_cast<int>(cap16);
    }

    // 0xbc6ef9b: test si, si; 0xbc6ef9e: je loc_bc6f025  (effective count == 0: return 0)
    if (esi == 0) {
        esi = 0;
        ::native::sub_ebdbf20(lockAddr);
        return esi;
    }

    // 0xbc6efa4..0xbc6efbe: loop setup — [rbp-0x10] = lockAddr; rbx += 0x4F0 (src block
    // array base); r15d = movzx esi (loop counter); r12 = &data_f847a07 (default empty
    // string); r14 = &[rbp-0x20] (SrcDesc scratch slot); xchg ax,ax (nop).
    FrameBlock* srcBlocks = reinterpret_cast<FrameBlock*>(a0b + 0x4F0);
    FrameBlock* dstBlocks = reinterpret_cast<FrameBlock*>(dstBase);
    int count = esi;

    // 0xbc6efc0: loop head (repeats `count` times):
    for (int k = 0; k < count; k++) {
        FrameBlock& src = *(srcBlocks + k);
        FrameBlock& dst = *(dstBlocks + k);

        // 0xbc6efc0: mov r8d,0x138; 0xbc6efc6: mov rcx,rdi; 0xbc6efc9: mov rdx,rbx;
        // 0xbc6efcc: call 0xEEC6EC0  — memcpy 312 bytes from src block to dst block
        std::memcpy(dst.data, src.data, 0x138);

        // 0xbc6efd1: mov [rbp-0x20],r12; 0xbc6efd5: mov dword ptr [rbp-0x18],0
        //   default SrcDesc: ptr = &data_f847a07, maxlen = 0
        native::SrcDesc desc{};
        desc.ptr = data_f847a07;
        desc.maxlen = 0;

        // 0xbc6efdc: mov rcx,rbx; 0xbc6efdf: mov edx,0x7FFFFFFF;
        // 0xbc6efe4: call 0xEBCE5E0  — bounded strlen of string at start of src block
        int len = ::native::sub_ebce5e0(src.data, 0x7FFFFFFF);

        // 0xbc6efe9: nop; 0xbc6efea: test eax,eax; 0xbc6efec: je short loc_bc6eff5
        if (len != 0) {
            // 0xbc6efee: mov [rbp-0x18],eax; 0xbc6eff1: mov [rbp-0x20],rbx
            desc.ptr = src.data;
            desc.maxlen = len;
        }

        // loc_bc6eff5:
        // 0xbc6eff5: mov rcx,rdi; 0xbc6eff8: mov edx,0x100; 0xbc6effd: mov r8,r14;
        // 0xbc6f000: mov r9d,0x7FFFFFFF; 0xbc6f006: call 0xEBCE650
        //   bounded string copy into dst.data (min(strlen, maxlen, 0x100-1) bytes + NUL)
        ::native::sub_ebce650(dst.data, 0x100, &desc, 0x7FFFFFFF);

        // 0xbc6f00b: nop; 0xbc6f00c: add rdi,0x138; 0xbc6f013: add rbx,0x138;
        // 0xbc6f01a: dec r15; 0xbc6f01d: jne short loc_bc6efc0  (handled by the for loop)
    }

    // After loop: 0xbc6f01f: mov r15,[rbp-0x10] (restore lockAddr);
    // 0xbc6f023: jmp short loc_bc6f027
    // 0xbc6f027: mov rcx,r15; 0xbc6f02a: call 0xEBDBF20 [unlock]
    ::native::sub_ebdbf20(lockAddr);
    // 0xbc6f02f: nop; 0xbc6f030: mov eax,esi; epilogue; ret
    return count;
}

static native::Footprint sub_bc6ef50Footprint(void* a0, int a2, void* a3) {
    // The function writes to each destination block (0x138 bytes per block, `count` blocks
    // where count = min((uint16_t)a2, (uint16_t)*(uint16_t*)(a0+0x4E8))). The exact extent
    // is runtime-dependent, so no static footprint is declared -- same convention as
    // sibling units that use nullptr.
    return {};
}

LIFT_FN(sub_bc6ef50, "native::sub_bc6ef50", 0xbc6ef50, sub_bc6ef50, sub_bc6ef50Footprint);

} // namespace native::bgfx
