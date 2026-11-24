#pragma once
#include <cstdint>
#include <cstddef>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// Layout used by sub 0xbc6f2a0 (bgfx destroy-handle enqueue, post-cmd 0x1C), 0xbb bytes, 1.26.62.01.
// Every offset below is taken verbatim from the disassembly of 0xbc6f2a0 (0xbc6f2a0..0xbc6f35b).
// The structs are layout overlays only: no object of these types is ever instantiated here.

namespace native {

struct Frame;

// Context+0x1C0: 32-bit lock field (written at 0xebdb9bc); its ADDRESS is passed to sub_ebdbf10/sub_ebdbf20.
// Context+0x1CFD0C8: Frame* loaded at 0xbc6f2cd (mov rax,[rdi+0x1CFD0C8]) and reloaded at 0xbc6f2ea.
struct Context {
    char pad_0x0000[0x1C0];
    std::uint32_t bgfxLock;             // +0x1C0  lock field
    char pad_0x1C4[0x1CFD0C8 - 0x1C4];
    Frame* fillFrame;                   // +0x1CFD0C8
};
static_assert(offsetof(Context, bgfxLock) == 0x1C0, "sub_bc6f2a0: Context+0x1C0 lock field");
static_assert(offsetof(Context, fillFrame) == 0x1CFD0C8, "sub_bc6f2a0: Context+0x1CFD0C8 fillFrame");

// Frame+0xE05820: u32 cmd-post cursor (loaded 0xbc6f2f5/0xbc6f31d, stored 0xbc6f329/0xbc6f342).
// Frame+0xE05828: cmd-post byte array base (0xbc6f2ff: rcx = rsi + cursor, then +0xE05828).
// Frame+0xE45828: u16 handle-list data (0xbc6f2db: [rax+rcx*2+0xE45828] = si).
// Frame+0xE47828: u16 handle-list count (0xbc6f2d4 movzx ecx / 0xbc6f2e3 inc word).
struct Frame {
    char pad_0x0000[0xE05820];
    std::uint32_t cmdPostCursor;        // +0xE05820
    char pad_0xE05824[4];
    std::uint8_t cmdPostData[1];        // +0xE05828
    char pad_0xE05829[0xE45828 - 0xE05829];
    std::uint16_t handleList[1];        // +0xE45828
    char pad_0xE4582A[0xE47828 - 0xE4582A];
    std::uint16_t handleListCount;      // +0xE47828
};
static_assert(offsetof(Frame, cmdPostCursor) == 0xE05820, "sub_bc6f2a0: Frame+0xE05820 cmdPostCursor");
static_assert(offsetof(Frame, cmdPostData) == 0xE05828, "sub_bc6f2a0: Frame+0xE05828 cmdPostData");
static_assert(offsetof(Frame, handleList) == 0xE45828, "sub_bc6f2a0: Frame+0xE45828 handleList");
static_assert(offsetof(Frame, handleListCount) == 0xE47828, "sub_bc6f2a0: Frame+0xE47828 handleListCount");

// Exact x64 Microsoft ABI signature of sub 0xbc6f2a0: rcx = Context*, dx = u16 handle, returns void.
void sub_bc6f2a0(Context* ctx, std::uint16_t handle);

// Calls made by sub 0xbc6f2a0. Targets are classified `lift` in docs/data/native_boundary.tsv
// (auto-unresolved->lift; 0xebce390 is a 5-byte jmp forwarder to 0xEEC6EC0): forward-declared
// here with their exact x64 ABI signature and called directly; each is lifted by its own unit
// and linked at the milestone gate.
// 0xbc6f2c8  call 0xEBDBF10   (lock)
// 0xbc6f310, 0xbc6f33c  call 0xEBCE390 (append bytes)
// 0xbc6f34d  call 0xEBDBF20   (unlock)
void sub_ebdbf10(void* lock);
void sub_ebce390(void* dst, const void* src, std::uint32_t size);
void sub_ebdbf20(void* lock);

} // namespace native
