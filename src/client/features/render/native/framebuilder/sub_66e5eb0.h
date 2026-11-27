#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_66e5eb0 (0x66e5eb0, size 0xae, 1.26.62.01, "L4L5_builder").
//
//   0x66e5eb0..0x66e5eb6  prologue: push rbp, push rsi, sub rsp,0x38
//   0x66e5eb6..0x66e5ebb  lea rbp,[rsp+0x30]; mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE (dead stack store = -2)
//   0x66e5ebb..0x66e5edb  mov qword ptr [rcx+8],0 / [rcx+0x10],9 / [rcx+0x18],0xF ; W a0+0x8..0xF=0, a0+0x10=9, a0+0x18=0xF
//   0x66e5edb..0x66e5eec  mov rax,0x7365546168706C41 ("AlphaTes"); mov [rcx],rax ; W a0+0x0..0x7
//   0x66e5eec..0x66e5f02  xorps xmm0,xmm0; mov byte ptr [rcx+8],0x74 ('t'); movups [rcx+0x20],xmm0 ; W a0+0x8='t', a0+0x20..0x2F=0
//   0x66e5f02..0x66e5f0e  mov [rbp-8],rcx (save a0); movups [rcx+0x30],xmm0 ; W a0+0x30..0x3F=0
//   0x66e5f0e..0x66e5f1b  call qword ptr [0xF99FFA0] (sub_eea6040 vendor boundary via slot); test rax,rax; je 0x66E5F51
//   0x66e5f1d..0x66e5f35  mov rax,[rbp-8]; mov [rax+0x20],rsi; mov qword ptr [rax+0x30],0x14; mov qword ptr [rax+0x38],0x1F
//   0x66e5f35..0x66e5f4a  movups xmm0,[0xF5F4D16]; movups [rsi],xmm0; mov dword [rsi+0x10],0x64657361; mov byte [rsi+0x14],0
//   0x66e5f4a..0x66e5f50  add rsp,0x38; pop rsi; pop rbp; ret  ; return a0
//   0x66e5f51..0x66e5f5e  failure: mov ecx,0x20; call 0x9BC830 (alloc boundary, noreturn OOM); nop; jmp short 0x66E5F1D (unreachable)
//
// x64 Microsoft ABI: RCX = a0 (out object), RAX = return = a0.
// Calls: slot call via [0xF99FFA0] (sub_eea6040, class vendor boundary — read the slot at call time),
//        direct call 0x9BC830 (class alloc boundary, native_boundary.tsv row 149).
// No null guard or SEH in the original (none added here). sub_9bc830 does not return on OOM.
//
// Data addresses (VA == RVA at the preferred image base, 1.26.62.01) [V disassembly]
static constexpr std::uintptr_t kGlobalAllocator          = 0x1233E1A8; // uint64_t* : allocator object (read at 0x66e5efb)
static constexpr std::uintptr_t kSlotEea6040              = 0x000F99FFA0; // data slot holding sub_eea6040 (read at 0x66e5f0e)
static constexpr std::uintptr_t kRodataOnDiscardValueB    = 0x00F5F4D16; // 16-byte movups source "On_DiscardValueB" (read at 0x66e5f35)

// Allocation size (EDX at 0x66e5f09; ECX for sub_9bc830 at 0x66e5f51) [V]
static constexpr std::uint32_t kAllocSize = 0x20;

// Constants written into the out object (a0) [V 0x66e5ec3..0x66e5f2d]
static constexpr std::uint64_t kOutField10Value = 9ull;   // a0+0x10
static constexpr std::uint64_t kOutField18Value = 0xFull; // a0+0x18
static constexpr std::uint64_t kOutField30Value = 0x14ull; // a0+0x30
static constexpr std::uint64_t kOutField38Value = 0x1Full; // a0+0x38

// Immediate stored to a0+0x0..0x7 (0x66e5edb): little-endian bytes "AlphaTes"
static constexpr char kAlphaTest[8] = {'A','l','p','h','a','T','e','s'};

// Constant written into the allocated record +0x10 (0x66e5f3f): little-endian bytes "ased"
static constexpr std::uint32_t kRecordTagDword = 0x64657361u;

// Offsets within the out object (a0) [V]
static constexpr std::size_t kOutOffsetName    = 0x00; // char[16] : "AlphaTest\0..."
static constexpr std::size_t kOutOffsetField10 = 0x10; // uint64_t = 9
static constexpr std::size_t kOutOffsetField18 = 0x18; // uint64_t = 0xF
static constexpr std::size_t kOutOffsetRecord  = 0x20; // void*  : allocated record pointer
static constexpr std::size_t kOutOffsetField28 = 0x28; // uint64_t = 0
static constexpr std::size_t kOutOffsetField30 = 0x30; // uint64_t = 0x14
static constexpr std::size_t kOutOffsetField38 = 0x38; // uint64_t = 0x1F

// Offsets within the allocated record [V 0x66e5f35..0x66e5f46]
static constexpr std::size_t kRecordOffsetId       = 0x00; // 16 bytes from rodata 0xF5F4D16
static constexpr std::size_t kRecordOffsetTagDword = 0x10; // uint32_t = 0x64657361 ("ased")
static constexpr std::size_t kRecordOffsetNull     = 0x14; // uint8_t = 0

// Out layout: every offset written by sub_66e5eb0 is a named member with a static_assert [V]
struct Out {
    char             name[16];     // +0x00 "AlphaTest\0..."
    std::uint64_t    field10;      // +0x10 = 9
    std::uint64_t    field18;      // +0x18 = 0xF
    void*            record;       // +0x20
    std::uint64_t    field28;      // +0x28 = 0
    std::uint64_t    field30;      // +0x30 = 0x14
    std::uint64_t    field38;      // +0x38 = 0x1F
}; // sizeof == 0x40
static_assert(offsetof(Out, name)    == kOutOffsetName,    "sub_66e5eb0: Out+0x00 is name");
static_assert(offsetof(Out, field10) == kOutOffsetField10, "sub_66e5eb0: Out+0x10 is field10");
static_assert(offsetof(Out, field18) == kOutOffsetField18, "sub_66e5eb0: Out+0x18 is field18");
static_assert(offsetof(Out, record)  == kOutOffsetRecord,  "sub_66e5eb0: Out+0x20 is record");
static_assert(offsetof(Out, field28) == kOutOffsetField28, "sub_66e5eb0: Out+0x28 is field28");
static_assert(offsetof(Out, field30) == kOutOffsetField30, "sub_66e5eb0: Out+0x30 is field30");
static_assert(offsetof(Out, field38) == kOutOffsetField38, "sub_66e5eb0: Out+0x38 is field38");
static_assert(sizeof(Out) == 0x40, "sub_66e5eb0: Out covers exactly the a0 range written (0x40 bytes)");

// Record layout: the 0x20-byte allocation filled by the function [V]
struct Record {
    char             id[16];          // +0x00 16 bytes from rodata 0xF5F4D16
    std::uint32_t    tagDword;        // +0x10 = 0x64657361 ("ased")
    std::uint8_t     null;            // +0x14 = 0
    char             pad[0x0B];       // +0x15..0x1F untouched
}; // sizeof == 0x20
static_assert(offsetof(Record, id)          == kRecordOffsetId,          "sub_66e5eb0: Record+0x00 is id");
static_assert(offsetof(Record, tagDword)    == kRecordOffsetTagDword,    "sub_66e5eb0: Record+0x10 is tagDword");
static_assert(offsetof(Record, null)        == kRecordOffsetNull,        "sub_66e5eb0: Record+0x14 is null");
static_assert(sizeof(Record) == kAllocSize, "sub_66e5eb0: Record exactly fills the 0x20-byte allocation");

namespace native {

// Exact x64 Microsoft ABI mirror of the original: RCX = a0, RAX = return value = a0.
void* sub_66e5eb0(void* a0);

} // namespace native
