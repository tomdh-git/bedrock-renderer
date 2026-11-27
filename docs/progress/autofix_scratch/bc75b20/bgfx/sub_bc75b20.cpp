// LIFT 0xbc75b20 size 0xb9 1.26.62.01 sub_bc75b20

#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc75b20.h"

#include <cstddef>
#include <cstdint>
#include <utility>

namespace native::bgfx {

// Layout assertions repeated in the source file so liftcheck sees them here too.

static_assert(sizeof(GroupItem) == 0x18, "sub_bc75b20: GroupItem is 24 bytes");
static_assert(offsetof(GroupItem, name)  == kOffGroupItemName,  "sub_bc75b20: GroupItem::name at +0x00");
static_assert(offsetof(GroupItem, value) == kOffGroupItemValue, "sub_bc75b20: GroupItem::value at +0x10");
static_assert(offsetof(GroupItem, flags) == kOffGroupItemFlags, "sub_bc75b20: GroupItem::flags at +0x14");
static_assert(CtxLayout::kLockOffset       == 0x1C0,       "sub_bc75b20: ctx lock offset is 0x1C0");
static_assert(CtxLayout::kGroupItemsOffset == 0x1E1DAA8,   "sub_bc75b20: ctx group array offset is 0x1E1DAA8");

// Verbatim call instructions from the disassembly of [0xbc75b20, 0xbc75bd9).

// 0xbc75b4a  call 0xEBDBF10                                ; -> sub_ebdbf10

// 0xbc75b7d  call 0xEBCE5E0                                ; -> sub_ebce5e0

// 0xbc75ba0  call 0xEBCE650                                ; -> sub_ebce650

// 0xbc75bc8  call 0xEBDBF20                                ; -> sub_ebdbf20

// All four targets are lift-set callees (class lift in docs/data/native_boundary.tsv),

// called directly through their native symbols. UNRESOLVED CALL = none.


void sub_bc75b20(void* ctx, std::uint32_t idx, char* out) noexcept {
    std::uint8_t* ctxBytes = reinterpret_cast<std::uint8_t*>(ctx);

    // 0xbc75b20..0xbc75b4a: prologue + lock acquire

    //   0xbc75b20  push rbp

    //   0xbc75b21  push r14

    //   0xbc75b23  push rsi

    //   0xbc75b24  push rdi

    //   0xbc75b25  push rbx

    //   0xbc75b26  sub rsp,0x40

    //   0xbc75b2a  lea rbp,[rsp+0x40]

    //   0xbc75b2f  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE

    //   0xbc75b37  mov rsi,r8                ; out

    //   0xbc75b3a  mov ebx,edx               ; idx

    //   0xbc75b3c  mov rdi,rcx               ; ctx

    //   0xbc75b3f  add rcx,0x1C0             ; ctx + 0x1C0 (lock address)

    //   0xbc75b46  mov [rbp-0x10],rcx        ; save lock address

    //   0xbc75b4a  call 0xEBDBF10            ; sub_ebdbf10(lock)

    void* lockAddress = ctxBytes + CtxLayout::kLockOffset;   // ctx + 0x1C0

    native::sub_ebdbf10(lockAddress);                        // 0xbc75b4a  call 0xEBDBF10


    // 0xbc75b4f..0xbc75b8a: read group item name, measure length, choose source

    //   0xbc75b4f  movzx eax,bx              ; idx (zero-extended)

    //   0xbc75b52  lea r14,[rax+rax*2]       ; r14 = idx*3

    //   0xbc75b56  mov rbx,[rdi+r14*8+0x1E1DAA8]   ; entry = *(char**)(ctx + 0x1E1DAA8 + idx*24 + 0)

    //   0xbc75b5e  lea rax,[0xF847A07]       ; default empty string (RVA)

    //   0xbc75b65  mov [rbp-0x20],rax        ; localDesc.ptr = default string

    //   0xbc75b69  mov dword ptr [rbp-0x18],0 ; localDesc.maxlen = 0

    //   0xbc75b70  test rbx,rbx

    //   0xbc75b73  je short 0xBC75B8E        ; if entry == NULL, skip to copy

    //   0xbc75b75  mov rcx,rbx

    //   0xbc75b78  mov edx,0x7FFFFFFF

    //   0xbc75b7d  call 0xEBCE5E0            ; sub_ebce5e0(entry, 0x7FFFFFFF) -> len in eax

    //   0xbc75b83  test eax,eax

    //   0xbc75b85  je short 0xBC75B8E        ; if len == 0, skip to copy

    //   0xbc75b87  mov [rbp-0x18],eax        ; localDesc.maxlen = len

    //   0xbc75b8a  mov [rbp-0x20],rbx        ; localDesc.ptr = entry

    GroupItem& item = reinterpret_cast<GroupItem*>(ctxBytes + CtxLayout::kGroupItemsOffset)[idx];
    char* entry = item.name;                // 0xbc75b56  mov rbx,[rdi+r14*8+0x1E1DAA8]


    char* srcPtr = reinterpret_cast<char*>(RewriteRegistry::imageBase() + kEmptyStringRva);  // 0xbc75b5e/0xbc75b65

    std::int32_t srcMax = 0;                // 0xbc75b69  mov dword ptr [rbp-0x18],0

    if (entry != nullptr) {                 // 0xbc75b70  test rbx,rbx ; je short 0xBC75B8E

        std::int32_t len = native::sub_ebce5e0(entry, 0x7FFFFFFF);  // 0xbc75b7d  call 0xEBCE5E0

        if (len != 0) {                     // 0xbc75b83  test eax,eax ; je short 0xBC75B8E

            srcMax = len;                   // 0xbc75b87  mov [rbp-0x18],eax

            srcPtr = entry;                 // 0xbc75b8a  mov [rbp-0x20],rbx

        }
    }

    // 0xbc75b8e..0xbc75ba0: call sub_ebce650(out, 0x100, &localDesc, 0x7FFFFFFF)

    //   0xbc75b8e  lea r8,[rbp-0x20]         ; &localDesc

    //   0xbc75b92  mov rcx,rsi               ; out

    //   0xbc75b95  mov edx,0x100             ; dstSize = 256

    //   0xbc75b9a  mov r9d,0x7FFFFFFF        ; maxlen

    //   0xbc75ba0  call 0xEBCE650            ; sub_ebce650(out, 0x100, &localDesc, 0x7FFFFFFF)

    native::SrcDesc localDesc{ srcPtr, srcMax };
    native::sub_ebce650(out, 0x100, &localDesc, 0x7FFFFFFF);   // 0xbc75ba0  call 0xEBCE650


    // 0xbc75ba6..0xbc75bbd: copy value and flags from group item

    //   0xbc75ba6  lea rax,[rdi+r14*8]       ; ctx + idx*24

    //   0xbc75baa  add rax,0x1E1DAA8         ; &GroupItem[idx]

    //   0xbc75bb0  mov ecx,[rax+0x10]        ; item.value

    //   0xbc75bb3  mov [rsi+0x100],ecx       ; out + 0x100 = item.value

    //   0xbc75bb9  movzx eax,word ptr [rax+0x14]   ; item.flags

    //   0xbc75bbd  mov [rsi+0x104],ax        ; out + 0x104 = item.flags

    *reinterpret_cast<std::int32_t*>(out + 0x100) = item.value;   // 0xbc75bb0/0xbc75bb3

    *reinterpret_cast<std::uint16_t*>(out + 0x104) = item.flags;  // 0xbc75bb9/0xbc75bbd


    // 0xbc75bc4..0xbc75bd8: release lock + epilogue

    //   0xbc75bc4  mov rcx,[rbp-0x10]        ; lock address

    //   0xbc75bc8  call 0xEBDBF20            ; sub_ebdbf20(lock)

    //   0xbc75bcd  nop

    //   0xbc75bce  add rsp,0x40

    //   0xbc75bd2  pop rbx

    //   0xbc75bd3  pop rdi

    //   0xbc75bd4  pop rsi

    //   0xbc75bd5  pop r14

    //   0xbc75bd7  pop rbp

    //   0xbc75bd8  ret

    native::sub_ebdbf20(lockAddress);                          // 0xbc75bc8  call 0xEBDBF20

}

LIFT_FN(sub_bc75b20, "sub_bc75b20", 0xbc75b20, sub_bc75b20, nullptr);

} // namespace native::bgfx

