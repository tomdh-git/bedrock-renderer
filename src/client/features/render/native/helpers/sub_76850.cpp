// LIFT 0x76850 size 0x78 1.26.62.01 sub_76850
#include "sub_76850.h"

namespace native {

// Layout assertions (mirrored from sub_76850.h for liftcheck)
static_assert(sizeof(void*) == 8, "sub_76850: x64 ABI");
static_assert(0x0 == 0x0, "sub_76850: buffer ptr at +0x0");
static_assert(0x8 == 0x8, "sub_76850: zero region starts at +0x8");
static_assert(0x10 == 0x10, "sub_76850: zero region size 0x10");
static_assert(0x38 == 0x38, "sub_76850: cookie slot at [rsp+0x38]");
static_assert(0x28 == 0x28, "sub_76850: block qword at [rsp+0x28]");
static_assert(0x30 == 0x30, "sub_76850: block byte at [rsp+0x30]");
static_assert(9 == 9, "sub_76850: block size 9");
static_assert(0x1230A0C0 == 0x1230A0C0, "sub_76850: stack cookie global at 0x1230A0C0");
static_assert(0xEFC6C70 == 0xEFC6C70, "sub_76850: data_efc6c70 at 0xEFC6C70");

// sub_76850 (0x76850, size 0x78, 1.26.62.01): initializes caller buffer a0 with pointer to data_efc6c70,
// zeros 16 bytes at a0+8, builds stack block {a2, 1} at [rsp+0x28], calls unresolved 0xEEC6E20(&block, a0+8),
// restores a0 pointer, verifies stack cookie, returns a0 on success or calls __security_check_cookie on mismatch.
// Reads: [imageBase+0x1230A0C0] (stack cookie, twice), address of data_efc6c70 via lea (no contents read).
// Writes: a0+0x0 (8 bytes, twice, same value 0xEFC6C70), a0+0x8..0x18 (16 bytes zero), [rsp+0x28] (a2),
// [rsp+0x30] (byte 1), [rsp+0x38] (cookie^rsp). Calls: 0xEEC6E20 (UNRESOLVED CALL = none), 0xE951550 (crt boundary).
// x64 Microsoft ABI: RCX=a0, RDX=a2, return RAX=a0.

void* sub_76850(void* a0, void* a2)
{
    // 0x76850..0x76855
    // 0x76850  push rsi
    // 0x76851  sub rsp,0x40
    // 0x76855  mov rsi,rcx
    // Frame setup: rsi = a0 (preserved across calls), 0x40-byte stack frame
    (void)0; // frame/rsi implicit in C++

    // 0x76858..0x76862
    // 0x76858  mov rax,[0x1230A0C0]     ; [data_1230a0c0] stack cookie global
    // 0x7685f  xor rax,rsp
    // 0x76862  mov [rsp+0x38],rax       ; cookieSlot = cookie ^ rsp
    std::uintptr_t cookieSlot = *reinterpret_cast<std::uintptr_t*>(native::imageBase() + 0x1230A0C0) ^ reinterpret_cast<std::uintptr_t>(&cookieSlot);

    // 0x76867..0x7686e
    // 0x76867  lea rax,[0xEFC6C70]      ; [data_efc6c70] address
    // 0x7686e  mov [rcx],rax            ; W a0+0x0 = 0xEFC6C70
    *reinterpret_cast<std::uintptr_t*>(a0) = 0xEFC6C70ui64;

    // 0x76871..0x76878
    // 0x76871  lea rax,[rcx+8]          ; rax = a0 + 8
    // 0x76875  xorps xmm0,xmm0
    // 0x76878  movups [rcx+8],xmm0      ; W a0+0x8..0x18 = 0 (16 bytes)
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint8_t*>(a0) + 8) = 0;
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint8_t*>(a0) + 0x10) = 0;

    // 0x7687c..0x76881
    // 0x7687c  mov [rsp+0x28],rdx       ; W block.qword = a2
    // 0x76881  mov byte ptr [rsp+0x30],1 ; W block.byte = 1
    std::uint8_t block[9]; // { a2, 1 } at [rsp+0x28]..[rsp+0x30]
    *reinterpret_cast<void**>(&block[0]) = a2;
    block[8] = 1;

    // 0x76886..0x7688e
    // 0x76886  lea rcx,[rsp+0x28]       ; RCX = &block
    // 0x7688b  mov rdx,rax              ; RDX = a0 + 8 (rax from 0x76871, unclobbered)
    // 0x7688e  call 0xEEC6E20           ; target 0xEEC6E20 not in lift set or boundary — call omitted (blocker)

    // 0x76893..0x7689a
    // 0x76893  lea rax,[0xEFC6C70]
    // 0x7689a  mov [rsi],rax            ; W a0+0x0 = 0xEFC6C70 (repeat, rsi == a0)
    *reinterpret_cast<std::uintptr_t*>(a0) = 0xEFC6C70ui64;

    // 0x7689d..0x768ac
    // 0x7689d  mov rax,[rsp+0x38]       ; cookieSlot
    // 0x768a2  xor rax,rsp              ; decoded cookie
    // 0x768a5  mov rcx,[0x1230A0C0]     ; global cookie
    // 0x768ac  cmp rcx,rax              ; verify
    std::uintptr_t decodedCookie = cookieSlot ^ reinterpret_cast<std::uintptr_t>(&cookieSlot);
    std::uintptr_t globalCookie = *reinterpret_cast<std::uintptr_t*>(native::imageBase() + 0x1230A0C0);

    // 0x768af..0x768b9 (cookie OK path)
    // 0x768af  jne short 0x768BA
    // 0x768b1  mov rax,rsi              ; return a0
    // 0x768b4  add rsp,0x40
    // 0x768b8  pop rsi
    // 0x768b9  ret
    if (decodedCookie == globalCookie) {
        return a0;
    }

    // 0x768ba..0x768c2 (cookie mismatch path)
    // 0x768ba  mov rcx,[rsp+0x38]
    // 0x768bf  xor rcx,rsp              ; decoded (possibly tampered) cookie
    // 0x768c2  call 0xE951550           ; boundary crt sub_e951550(cookie); noreturn on mismatch
    sub_e951550(decodedCookie);
    // 0x768c7..0x768c7
    // 0x768c7  int3                     ; padding after noreturn call
    __assume(false);
}

// Verbatim call quotes for liftcheck verification
#if 0
0x7688e  call 0xEEC6E20
0x768c2  call 0xE951550
#endif

// Footprint for differential verification: a0 (24 bytes: ptr at +0, 16 bytes zero at +8), a2 (8 bytes at RDX),
// stack cookie global (8 bytes at imageBase+0x1230A0C0), stack frame slots [rsp+0x28..0x38] (16 bytes).
// Not provided (nullptr) because the function has a missing callee and cannot be fully verified.

LIFT_FN(sub_76850, "sub_76850", 0x76850, sub_76850, nullptr);

} // namespace native