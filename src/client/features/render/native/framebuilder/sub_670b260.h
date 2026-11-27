#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_670b260 (0x670b260, size 0x98, 1.26.62.01, "terrain/chunk draw builder").
//
//   0x670b260  push rsi                                       
//   0x670b261  push rdi                                       
//   0x670b262  sub rsp,0x38                                   
//   0x670b266  movaps [rsp+0x20],xmm6                         
//   0x670b26b  mov rsi,rcx                                    
//   0x670b26e  xorps xmm6,xmm6                                
//   0x670b271  movups [rcx+0x10],xmm6                         ; W a0+0x10..0x1F = 0
//   0x670b275  movups [rcx],xmm6                             ; W a0+0x0..0xF = 0
//   0x670b278  mov rcx,[0x1233E1A8]                          ; R data_1233e1a8 (allocator object)
//   0x670b27f  mov rax,[rcx]                                  ; R *allocator
//   0x670b282  mov rax,[rax+8]                                ; R *allocator+8 (dead: value unused)
//   0x670b286  mov edx,0x20                                   ; EDX = alloc size 0x20
//   0x670b28b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (vendor boundary via slot)
//   0x670b291  test rax,rax                                  
//   0x670b294  je short 0x670B2E6                            ; allocation failure
//   0x670b296  mov [rsi],rax                                 ; W a0+0x0 = record or NULL
//   0x670b299  mov qword ptr [rsi+0x10],0x12                 ; W a0+0x10
//   0x670b2a1  mov qword ptr [rsi+0x18],0x1F                 ; W a0+0x18
//   0x670b2a9  movups xmm0,[0xF55AF3F]                       ; R data_f55af3f "RenderAsBillboards"
//   0x670b2b0  movups [rax],xmm0                             ; W record+0x0..0xF
//   0x670b2b3  mov word ptr [rax+0x10],0x7364                ; W record+0x10 ('d','s')
//   0x670b2b9  mov byte ptr [rax+0x12],0                     ; W record+0x12
//   0x670b2bd  movups [rsi+0x20],xmm6                        ; W a0+0x20..0x2F = 0
//   0x670b2c1  mov qword ptr [rsi+0x30],2                    ; W a0+0x30
//   0x670b2c9  mov qword ptr [rsi+0x38],0xF                  ; W a0+0x38
//   0x670b2d1  mov word ptr [rsi+0x20],0x6E4F                ; W a0+0x20 (u16)
//   0x670b2d7  mov rax,rsi                                   ; return a0
//   0x670b2da  movaps xmm6,[rsp+0x20]                        
//   0x670b2df  add rsp,0x38                                  
//   0x670b2e3  pop rdi                                       
//   0x670b2e4  pop rsi                                       
//   0x670b2e5  ret                                           
//   0x670b2e6  mov ecx,0x20                                   ; failure path
//   0x670b2eb  mov rdi,rax                                    ; rax == 0
//   0x670b2ee  call 0x9BC830                                  ; sub_9bc830 (alloc boundary, noreturn OOM handler)
//   0x670b2f3  mov rax,rdi                                    ; unreachable
//   0x670b2f6  jmp short 0x670B296                            ; unreachable
//   0x670b2f8  int3 x8                                        ; padding past end of function (size 0x98)
//
// x64 Microsoft ABI: RCX = a0 (out object), RAX = return = a0.
// Calls: slot call via [0xF99FFA0] (sub_eea6040, vendor boundary — read the slot at call time),
//        direct call 0x9BC830 (sub_9bc830, class alloc boundary, native_boundary.tsv row 149).
// No null guard or SEH in the original (none added here).

// Data addresses (VA == RVA at the preferred image base, 1.26.62.01) [V disassembly]
static constexpr std::uintptr_t kGlobalAllocator      = 0x1233E1A8; // uint64_t* : the allocator object (read at 0x670b278)
static constexpr std::uintptr_t kSlotEea6040          = 0x000F99FFA0; // data slot holding sub_eea6040 (read at 0x670b28b)
static constexpr std::uintptr_t kRodataRenderAsBillboards = 0x00F55AF3F; // "RenderAsBillboards" (16-byte movups source at 0x670b2a9)

// Allocation size passed to the slot call (EDX at 0x670b286) and to sub_9bc830 (ECX at 0x670b2e6) [V]
static constexpr std::uint64_t kAllocSize = 0x20;

// Constants written into the out object (a0) [V 0x670b299..0x670b2d1]
static constexpr std::uint64_t kOutField10Value = 0x12ull; // a0+0x10
static constexpr std::uint64_t kOutField18Value = 0x1Full; // a0+0x18
static constexpr std::uint16_t  kOutField20Value = 0x6E4Fu; // a0+0x20 (u16)
static constexpr std::uint64_t kOutField30Value = 2ull;     // a0+0x30
static constexpr std::uint64_t kOutField38Value = 0xFull;   // a0+0x38

// Constants written into the allocated record [V 0x670b2b0..0x670b2b9]
static constexpr std::uint16_t kRecordTag = 0x7364u; // record+0x10: 'd','s', completes "RenderAsBillboards"

// Offsets within the out object (a0) [V 0x670b271..0x670b2d1]
static constexpr std::size_t kOutOffsetBuffer   = 0x00; // void* : record pointer or NULL
static constexpr std::size_t kOutOffsetZero08   = 0x08; // always 0 (initial 16-byte clear)
static constexpr std::size_t kOutOffsetField10  = 0x10; // uint64_t = 0x12
static constexpr std::size_t kOutOffsetField18  = 0x18; // uint64_t = 0x1F
static constexpr std::size_t kOutOffsetField20  = 0x20; // uint16_t = 0x6E4F (after a 16-byte zero at +0x20..0x2F)
static constexpr std::size_t kOutOffsetField30  = 0x30; // uint64_t = 2
static constexpr std::size_t kOutOffsetField38  = 0x38; // uint64_t = 0xF

// Offsets within the allocated record [V 0x670b2a9..0x670b2b9]
static constexpr std::size_t kRecordOffsetId   = 0x00; // 16 bytes: "RenderAsBillboards\0"
static constexpr std::size_t kRecordOffsetTag  = 0x10; // uint16_t = 0x7364
static constexpr std::size_t kRecordOffsetNull = 0x12; // uint8_t = 0

// Out layout: every offset written by sub_670b260 is a named member with a static_assert [V]
struct Out {
    void*            buffer;     // +0x00
    std::uint64_t    zero0x08;   // +0x08
    std::uint64_t    field10;    // +0x10
    std::uint64_t    field18;    // +0x18
    std::uint16_t    field20;    // +0x20
    std::uint8_t     pad0x22[0x0E]; // +0x22..0x2F
    std::uint64_t    field30;    // +0x30
    std::uint64_t    field38;    // +0x38
}; // sizeof == 0x40
static_assert(offsetof(Out, buffer)   == kOutOffsetBuffer,   "sub_670b260: Out+0x00 is written as buffer");
static_assert(offsetof(Out, zero0x08) == kOutOffsetZero08,  "sub_670b260: Out+0x08 is written zero");
static_assert(offsetof(Out, field10)  == kOutOffsetField10, "sub_670b260: Out+0x10 is written as field10");
static_assert(offsetof(Out, field18)  == kOutOffsetField18, "sub_670b260: Out+0x18 is written as field18");
static_assert(offsetof(Out, field20)  == kOutOffsetField20, "sub_670b260: Out+0x20 is written as field20");
static_assert(offsetof(Out, field30)  == kOutOffsetField30, "sub_670b260: Out+0x30 is written as field30");
static_assert(offsetof(Out, field38)  == kOutOffsetField38, "sub_670b260: Out+0x38 is written as field38");
static_assert(sizeof(Out) == 0x40, "sub_670b260: Out covers exactly the a0 range written by the function (0x40 bytes)");

// Record layout: the 0x20-byte allocation filled by the function [V]
struct Record {
    char             id[16];     // +0x00 "RenderAsBillboards\0"
    std::uint16_t    tag;        // +0x10 = 0x7364
    std::uint8_t     null;       // +0x12 = 0
}; // sizeof == 0x14 (alignment padding), allocation is 0x20 bytes
static_assert(offsetof(Record, id)   == kRecordOffsetId,   "sub_670b260: Record+0x00 is the 16-byte id");
static_assert(offsetof(Record, tag)  == kRecordOffsetTag,  "sub_670b260: Record+0x10 is written as tag u16");
static_assert(offsetof(Record, null) == kRecordOffsetNull, "sub_670b260: Record+0x12 is written as null byte");
static_assert(sizeof(Record) <= kAllocSize, "sub_670b260: Record must fit into the 0x20-byte allocation");

namespace native {

// Exact x64 Microsoft ABI mirror of the original: RCX = a0, RAX = return value = a0.
void* sub_670b260(void* a0);

} // namespace native
