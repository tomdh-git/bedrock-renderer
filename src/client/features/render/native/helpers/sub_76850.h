#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_76850 (0x76850, size 0x78, 1.26.62.01): initializes a caller buffer with a pointer to data_efc6c70, zeros 16 bytes at +0x8,
// builds a 9-byte stack argument block {a2, 1}, calls an unresolved function at 0xEEC6E20 with (&block, a0+8),
// restores the buffer pointer, verifies the stack cookie, returns a0 on success or calls __security_check_cookie on mismatch.
// x64 Microsoft ABI: RCX = a0 (caller buffer), RDX = a2, returns RAX = a0.
//
/// 0x76850  push rsi
/// 0x76851  sub rsp,0x40
/// 0x76855  mov rsi,rcx
/// 0x76858  mov rax,[0x1230A0C0]
/// 0x7685f  xor rax,rsp
/// 0x76862  mov [rsp+0x38],rax
/// 0x76867  lea rax,[0xEFC6C70]
/// 0x7686e  mov [rcx],rax
/// 0x76871  lea rax,[rcx+8]
/// 0x76875  xorps xmm0,xmm0
/// 0x76878  movups [rcx+8],xmm0
/// 0x7687c  mov [rsp+0x28],rdx
/// 0x76881  mov byte ptr [rsp+0x30],1
/// 0x76886  lea rcx,[rsp+0x28]
/// 0x7688b  mov rdx,rax
/// 0x7688e  call 0xEEC6E20
/// 0x76893  lea rax,[0xEFC6C70]
/// 0x7689a  mov [rsi],rax
/// 0x7689d  mov rax,[rsp+0x38]
/// 0x768a2  xor rax,rsp
/// 0x768a5  mov rcx,[0x1230A0C0]
/// 0x768ac  cmp rcx,rax
/// 0x768af  jne short 0x768BA
/// 0x768b1  mov rax,rsi
/// 0x768b4  add rsp,0x40
/// 0x768b8  pop rsi
/// 0x768b9  ret
/// 0x768ba  mov rcx,[rsp+0x38]
/// 0x768bf  xor rcx,rsp
/// 0x768c2  call 0xE951550

struct sub_76850Layout {
    static_assert(sizeof(void*) == 8, "sub_76850: x64 ABI, pointer-sized address space");
    // Caller buffer (a0) layout
    static constexpr std::uintptr_t kBufferPtrOffset = 0x0;   // void* at a0+0x0 = address of data_efc6c70
    static constexpr std::uintptr_t kBufferZeroStart = 0x8;   // 16 bytes zeroed at a0+0x8..0x18
    static constexpr std::uintptr_t kBufferZeroSize = 0x10;   // 16 bytes
    // Stack frame slots (private, not part of a struct)
    static constexpr std::uintptr_t kCookieSlotOffset = 0x38; // cookie stash at [rsp+0x38]
    static constexpr std::uintptr_t kBlockQwordOffset = 0x28; // block.qword (a2) at [rsp+0x28]
    static constexpr std::uintptr_t kBlockByteOffset = 0x30;  // block.byte (1) at [rsp+0x30]
    static constexpr std::uintptr_t kBlockSize = 9;           // block size in bytes
    // Global data addresses
    static constexpr std::uintptr_t kGblCookieRva = 0x1230A0C0;    // data_1230a0c0: /GS stack cookie
    static constexpr std::uintptr_t kDataEfc6c70Rva = 0xEFC6C70;   // data_efc6c70: address loaded via lea
    // Callee addresses
    static constexpr std::uintptr_t kUnresolvedCalleeRva = 0xEEC6E20; // UNRESOLVED CALL target
    static constexpr std::uintptr_t kSecurityCheckCookieRva = 0xE951550; // crt boundary: __security_check_cookie
    static_assert(kBufferPtrOffset == 0x0, "sub_76850: buffer ptr at +0x0");
    static_assert(kBufferZeroStart == 0x8, "sub_76850: zero region starts at +0x8");
    static_assert(kBufferZeroSize == 0x10, "sub_76850: zero region size 0x10");
    static_assert(kCookieSlotOffset == 0x38, "sub_76850: cookie slot at [rsp+0x38]");
    static_assert(kBlockQwordOffset == 0x28, "sub_76850: block qword at [rsp+0x28]");
    static_assert(kBlockByteOffset == 0x30, "sub_76850: block byte at [rsp+0x30]");
    static_assert(kBlockSize == 9, "sub_76850: block size 9");
    static_assert(kGblCookieRva == 0x1230A0C0, "sub_76850: stack cookie global at 0x1230A0C0");
    static_assert(kDataEfc6c70Rva == 0xEFC6C70, "sub_76850: data_efc6c70 at 0xEFC6C70");
};

namespace native {

// sub_e951550 (0xE951550, crt boundary, docs/data/native_boundary.tsv line 467): __security_check_cookie.
// Called with RCX = decoded cookie (cookie ^ rsp). Noreturn on mismatch.
native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");

// sub_76850 (0x76850, 0x78 bytes, 1.26.62.01): argument `a0` in RCX, `a2` in RDX, returns RAX = a0.
// See the instruction block above for the instruction-by-instruction reversal.
void* sub_76850(void* a0, void* a2);

} // namespace native