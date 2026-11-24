#pragma once

#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// Layout reconstructed from the disassembly of 0xbc70ff0 (size 0xf1, Minecraft 1.26.62.01).
// Every offset below is read or written by that function [V]; instruction RVAs are cited
// beside each statement in sub_bc70ff0.cpp. The structs are layout overlays only: no object
// of these types is ever instantiated here, and the real C++ class names of the game objects
// are unknown.
//
// 0xbc70ff0 receives a render context (rcx). At ctx+0x1CFD0C8 it loads a pointer to the
// command-post state object [V 0xbc71023  mov rdi,[rsi+0x1CFD0C8]]. That object holds the
// byte-append cursor at +0xDC5818 (u32) and the buffer base pointer at +0xDC5820 [V
// 0xbc7102e  mov eax,[rdi+0xDC5818]; 0xbc7104f  lea rsi,[rdi+0xDC5820]]. The function appends a
// tagged record (tag byte 0x13, then u16/u32/u64 fields, each written at an advance-aligned
// cursor that the function advances itself) into that buffer [V 0xbc71049/0xbc71075/0xbc7109a/
// 0xbc710c2  call 0xEBCE390], brackets the work with sub_ebdbf10(ctx + 0x1C0) /
// sub_ebdbf20(ctx + 0x1C0) [V 0xbc7101e/0xbc710d3  call 0xEBDBF10/0xEBDBF20], and returns void.
//
// sub_ebce390's entry at 0xEBCE390 tails to 0xEEC6EC0; it copies size bytes [V 0xebce390
// jmp 0xEEC6EC0]. All three callees are classified `lift` (native_functions.tsv depth-0 root
// rows; native_boundary.tsv `lift`/`auto-unresolved->lift` rows 0xebce390/0xebdbf10/0xebdbf20)
// and are forward-declared here with their exe names; the lifted callee bodies are linked at
// the milestone gate. They are called directly, never through a boundary wrapper.
namespace native {

struct RenderContext;

// Command-post state object reached at RenderContext+0x1CFD0C8 [V].
struct CmdPostState {
    char pad_0x0000[0xDC5818];
    std::uint32_t postCursor;  // +0xDC5818 u32 append cursor; R/W by 0xbc70ff0
    char pad_0xDC581C[4];      // +0xDC581C padding; postData lands 8-aligned at +0xDC5820
    std::uint8_t* postData;    // +0xDC5820 byte buffer base; R by 0xbc70ff0
};                             // sizeof == 0xDC5828

static_assert(offsetof(CmdPostState, postCursor) == 0xDC5818,
              "sub_bc70ff0: CmdPostState::postCursor must be at +0xDC5818");
static_assert(offsetof(CmdPostState, postData) == 0xDC5820,
              "sub_bc70ff0: CmdPostState::postData must be at +0xDC5820");

// Render context ('this' = rcx at entry). Opaque lock subobject at +0x1C0 whose address is
// passed to sub_ebdbf10/sub_ebdbf20 [V 0xbc71013  add rcx,0x1C0]; command-post state pointer
// at +0x1CFD0C8 [V].
struct RenderContext {
    char pad_0x0000[0x1CFD0C8];
    CmdPostState* cmdPost;  // +0x1CFD0C8
};

static_assert(offsetof(RenderContext, cmdPost) == 0x1CFD0C8,
              "sub_bc70ff0: RenderContext::cmdPost must be at +0x1CFD0C8");

// Exact x64 Microsoft ABI signature of 0xbc70ff0: rcx = RenderContext*, rdx = u16,
// r8 = u32, r9 = u64; return void (rax dead). [V register map from the prologue stores]
void sub_bc70ff0(RenderContext* ctx, std::uint16_t dx, std::uint32_t d32, std::uint64_t q64);

// Callees of 0xbc70ff0, forward-declared with their exe names (classified `lift`, not boundary;
// call them directly like any lifted function):
//   void sub_ebdbf10(void* lock)       0xbc7101e  call 0xEBDBF10   ; lock = ctx + 0x1C0
//   void sub_ebce390(void*, const void*, std::uint32_t size)  0xbc71049/0xbc71075/0xbc7109a/0xbc710c2
//                                                                  call 0xEBCE390
//   void sub_ebdbf20(void* lock)       0xbc710d3  call 0xEBDBF20   ; unlock
void sub_ebdbf10(void* lock);                                    // 0xbc7101e  call 0xEBDBF10   ; jmp qword ptr [0xF9A7B10]
void sub_ebce390(void* dst, const void* src, std::uint32_t size); // 0xbc71049 etc.  call 0xEBCE390   ; jmp 0xEEC6EC0
void sub_ebdbf20(void* lock);                                    // 0xbc710d3  call 0xEBDBF20   ; jmp qword ptr [0xF9A7B28]

} // namespace native
