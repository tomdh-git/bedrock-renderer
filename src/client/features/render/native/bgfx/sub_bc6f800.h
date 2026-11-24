#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_bc6f800: bgfx destroy-handle enqueue (cmd 0x1D) — size 0xbb, 1.26.62.01.
// void sub_bc6f800(Context* ctx /*rcx*/, std::uint16_t handle /*dx*/), returns void.
//
// Layout mirrors of the game structs, pinned by static_assert. Only the fields
// the function touches are laid out; everything else is explicit pad so each
// offset below is the exact address the exe reads/writes, taken from the
// disassembly of 0xbc6f800 (not from BGFX_MAP/SDK hypotheses):
//
//   Context+0x1C0        u32   bgfxLock            lock, passed to sub_ebdbf10 / sub_ebdbf20
//   Context+0x1CFD0C8    Frame* fillFrame
//   Frame+0xE05820       u32   cmdPostCursor
//   Frame+0xE05828       u8[]  cmdPostData
//   Frame+0xE478AC       u16   handleList[256]     (0x200 bytes; handleListCount follows at 0xE498AC)
//   Frame+0xE498AC       u16   handleListCount
namespace native {

struct Frame;

struct Context {
    std::uint8_t pad0[0x1C0];
    std::uint32_t bgfxLock;             // 0x1C0
    std::uint8_t pad1[0x1CFD0C8 - 0x1C4];
    Frame* fillFrame;                   // 0x1CFD0C8
};
static_assert(offsetof(Context, bgfxLock) == 0x1C0, "sub_bc6f800: Context+0x1C0 bgfxLock");
static_assert(offsetof(Context, fillFrame) == 0x1CFD0C8, "sub_bc6f800: Context+0x1CFD0C8 fillFrame");

struct Frame {
    std::uint8_t pad0[0xE05820];
    std::uint32_t cmdPostCursor;        // 0xE05820
    std::uint8_t cmdPostData[0xE478AC - 0xE05828];  // 0xE05828
    std::uint16_t handleList[256];      // 0xE478AC, 0x200 bytes; handleListCount sits right after
    std::uint16_t handleListCount;      // 0xE498AC
};
static_assert(offsetof(Frame, cmdPostCursor) == 0xE05820, "sub_bc6f800: Frame+0xE05820 cmdPostCursor");
static_assert(offsetof(Frame, cmdPostData) == 0xE05828, "sub_bc6f800: Frame+0xE05828 cmdPostData");
static_assert(offsetof(Frame, handleList) == 0xE478AC, "sub_bc6f800: Frame+0xE478AC handleList");
static_assert(offsetof(Frame, handleListCount) == 0xE498AC, "sub_bc6f800: Frame+0xE498AC handleListCount");

void sub_bc6f800(Context* ctx, std::uint16_t handle);

// Callees of sub 0xbc6f800: all class lift in docs/data/native_boundary.tsv
// (0xebce390 / 0xebdbf10 / 0xebdbf20). Forward-declared here and called
// directly (brief rule 6 / spec section 6): their bodies are lifted by their
// own units and linked at the milestone gate. Signatures from the call sites
// of 0xbc6f800 (rcx/rdx/r8, void return); the disassembly contradicts none of
// this, and no callee sits outside the lift set.
void sub_ebdbf10(std::uint32_t* lock);                    // 0xbc6f828  call 0xEBDBF10  ; rcx = &ctx->bgfxLock
void sub_ebce390(void* dst, const void* src, std::uint32_t size);  // 0xbc6f870 / 0xbc6f89c ; rcx=dst, rdx=src, r8d=size
void sub_ebdbf20(std::uint32_t* lock);                    // 0xbc6f8ad  call 0xEBDBF20  ; rcx = lockPtr

} // namespace native
