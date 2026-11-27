// LIFT 0x661a2f0 size 0xce 1.26.62.01 sub_661a2f0
#include "client/features/render/native/framebuilder/sub_661a2f0.h"
#include "client/features/render/native/Lift.h"

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <intrin.h>
#include <xmmintrin.h>

// Layout assertions (mirror of sub_661a2f0.h, also present there).
static_assert(offsetof(Slot30, field_0x6EA) == kSlot30Field0x6EA, "sub_661a2f0: Slot30+0x6EA");
static_assert(offsetof(Slot30, field_0x6EC) == kSlot30Field0x6EC, "sub_661a2f0: Slot30+0x6EC");
static_assert(offsetof(Slot30, field_0x6EE) == kSlot30Field0x6EE, "sub_661a2f0: Slot30+0x6EE");
static_assert(offsetof(Slot30, field_0x6F0) == kSlot30Field0x6F0, "sub_661a2f0: Slot30+0x6F0");

namespace native {

namespace {

// 0x1230A0C0: MSVC security cookie global (__security_cookie), read via absolute address
// [V: 0x661a2f4 mov rax,[0x1230A0C0] and 0x661a37a mov rcx,[0x1230A0C0]].
static std::uintptr_t* const kSecurityCookieAddr = reinterpret_cast<std::uintptr_t*>(0x1230A0C0);

// sub_eec6d80 (0xeec6d80, lift set): tail-jumps to _CxxThrowException via data slot
// 0xF9A8A18, noreturn [V: sub_eec6d80.h / sub_eec6d80.cpp]. Forward-declared here with its
// exact x64 ABI signature; linked at the milestone gate.
void sub_eec6d80(void* a0, std::uintptr_t a1, std::uintptr_t a2, std::uintptr_t a3);

// sub_e951550 (0xe951550, boundary crt, __report_gsfailure style, noreturn).
// rcx = cookie ^ rsp. crt row in native_boundary.tsv [V]. Called at 0x661a3b8.
// R = std::uintptr_t (return unobserved: the real function never returns).
native::Boundary<std::uintptr_t, std::uintptr_t> sub_e951550("sub_e951550");

} // namespace

// sub_661a2f0 (0x661a2f0, size 0xce, 1.26.62.01, "BgfxFrameBuilder slot 30").
//
// Exact x64 Microsoft ABI: RCX = a0 (Slot30*, u16 fields at +0x6EA/+0x6EC/+0x6EE/+0x6F0),
// RDX = a1 (float[2], read at +0x0 and +0x4). Returns void.
//
// Same reads, same writes (value and order), same calls in the same order, same return.
// No null guard or SEH (the original has none; none added here). [V] every instruction
// line below, from the exe disassembly of [0x661a2f0, 0x661a3be).
//
// Phase 1: 0x661a2f0..0x661a303  prologue + stack cookie
// Phase 2: 0x661a303..0x661a336  validate a1[0], store (u16)(int)a1[0] to a0+0x6EE
// Phase 3: 0x661a33d..0x661a36b  validate a1[4], store (u16)(int)a1[4] to a0+0x6F0
// Phase 4: 0x661a372..0x661a38a  stack cookie check, epilogue, ret
// Phase 5: 0x661a38b..0x661a3ab  error path: build exception object, call sub_eec6d80 (noreturn)
// Phase 6: 0x661a3b0..0x661a3b8  cookie-failure path: call sub_e951550 (noreturn)

void sub_661a2f0(Slot30* a0, float* a1) {
    // 0x661a2f0  sub rsp,0x48                                   ; prologue
    // 0x661a2f4  mov rax,[0x1230A0C0]                          ; security cookie global
    // 0x661a2fb  xor rax,rsp                                   
    // 0x661a2fe  mov [rsp+0x40],rax                             ; cookie slot
    std::uintptr_t cookieSlot;
    cookieSlot = *kSecurityCookieAddr ^ reinterpret_cast<std::uintptr_t>(&cookieSlot);  // 0x661a2f4..0x661a2fe

    float v0 = 0.0f;
    std::int32_t i0 = 0;
    std::uint16_t u0 = 0;
    float v1 = 0.0f;
    std::int32_t i1 = 0;
    std::uint16_t u1 = 0;
    std::uintptr_t loaded = 0;

    // ----- validate and convert a1[0] -> a0+0x6EE -----
    // 0x661a303  movss xmm0,[rdx]                              ; R a1+0x0
    v0 = a1[0];                                                // 0x661a303 movss xmm0,[rdx]

    // 0x661a307  xorps xmm1,xmm1                               
    // 0x661a30a  ucomiss xmm1,xmm0                              ; 0.0 vs a1[0]
    // 0x661a30d  ja short 0x661A38B                            ; a1[0] < 0.0 -> error
    if (0.0f > v0) {                                           // 0x661a30a ucomiss xmm1,xmm0 ; 0x661a30d ja short 0x661A38B
        goto errorThrow;
    }

    // 0x661a30f  cvttss2si eax,xmm0                             ; (int)a1[0]
    i0 = _mm_cvttss_si32(_mm_set_ss(v0));                     // 0x661a30f cvttss2si eax,xmm0

    // 0x661a313  movzx r8d,ax                                   ; low16 of (int)a1[0]
    u0 = static_cast<std::uint16_t>(i0);                       // 0x661a313 movzx r8d,ax

    // 0x661a317  xorps xmm1,xmm1                               
    // 0x661a31a  cvtsi2ss xmm1,r8d                              ; (float)low16
    // 0x661a31f  ucomiss xmm0,xmm1                              ; a1[0] vs (float)low16
    // 0x661a322  jne short 0x661A38B                           ; not equal -> error
    // 0x661a324  jp short 0x661A38B                            ; unordered (NaN) -> error
    if (!(static_cast<float>(u0) == v0)) {                     // 0x661a31f ucomiss xmm0,xmm1 ; 0x661a322 jne ; 0x661a324 jp
        goto errorThrow;
    }

    // 0x661a326  movzx r8d,word ptr [rcx+0x6EA]                ; R a0+0x6EA
    // 0x661a32e  cmp r8w,ax                                    
    // 0x661a332  cmovb eax,r8d                                  ; dead: result never read
    // 0x661a336  mov [rcx+0x6EE],ax                            ; W a0+0x6EE
    (void)a0->field_0x6EA;                                     // 0x661a326 movzx r8d,word ptr [rcx+0x6EA] (read, feeds dead cmovb)
    a0->field_0x6EE = u0;                                      // 0x661a336 mov [rcx+0x6EE],ax

    // ----- validate and convert a1[4] -> a0+0x6F0 -----
    // 0x661a33d  movss xmm0,[rdx+4]                            ; R a1+0x4
    v1 = a1[1];                                                // 0x661a33d movss xmm0,[rdx+4]

    // 0x661a342  xorps xmm1,xmm1                               
    // 0x661a345  ucomiss xmm1,xmm0                              ; 0.0 vs a1[4]
    // 0x661a348  ja short 0x661A38B                            ; a1[4] < 0.0 -> error
    if (0.0f > v1) {                                           // 0x661a345 ucomiss xmm1,xmm0 ; 0x661a348 ja short 0x661A38B
        goto errorThrow;
    }

    // 0x661a34a  cvttss2si eax,xmm0                             ; (int)a1[4]
    i1 = _mm_cvttss_si32(_mm_set_ss(v1));                     // 0x661a34a cvttss2si eax,xmm0

    // 0x661a34e  movzx edx,ax                                   ; low16 of (int)a1[4]
    u1 = static_cast<std::uint16_t>(i1);                       // 0x661a34e movzx edx,ax

    // 0x661a351  xorps xmm1,xmm1                               
    // 0x661a354  cvtsi2ss xmm1,edx                              ; (float)low16
    // 0x661a358  ucomiss xmm0,xmm1                              ; a1[4] vs (float)low16
    // 0x661a35b  jne short 0x661A38B                           ; not equal -> error
    // 0x661a35d  jp short 0x661A38B                            ; unordered (NaN) -> error
    if (!(static_cast<float>(u1) == v1)) {                     // 0x661a358 ucomiss xmm0,xmm1 ; 0x661a35b jne ; 0x661a35d jp
        goto errorThrow;
    }

    // 0x661a35f  mov edx,[rcx+0x6EC]                           ; R a0+0x6EC (u32, low16 used)
    // 0x661a365  cmp dx,ax                                     
    // 0x661a368  cmovb eax,edx                                  ; dead: result never read
    // 0x661a36b  mov [rcx+0x6F0],ax                            ; W a0+0x6F0
    (void)a0->field_0x6EC;                                     // 0x661a35f mov edx,[rcx+0x6EC] (read, feeds dead cmovb)
    a0->field_0x6F0 = u1;                                      // 0x661a36b mov [rcx+0x6F0],ax

    // ----- stack cookie check + epilogue -----
    // 0x661a372  mov rax,[rsp+0x40]                            
    // 0x661a377  xor rax,rsp                                   
    // 0x661a37a  mov rcx,[0x1230A0C0]                          
    // 0x661a381  cmp rcx,rax                                   
    // 0x661a384  jne short 0x661A3B0                           ; cookie mismatch -> cookie failure
    loaded = cookieSlot ^ reinterpret_cast<std::uintptr_t>(&cookieSlot);  // 0x661a372 mov rax,[rsp+0x40] ; 0x661a377 xor rax,rsp
    if (loaded != *kSecurityCookieAddr) {                     // 0x661a37a mov rcx,[0x1230A0C0] ; 0x661a381 cmp rcx,rax ; 0x661a384 jne short 0x661A3B0
        // 0x661a3b0  mov rcx,[rsp+0x40]                            
        // 0x661a3b5  xor rcx,rsp                                   
        // 0x661a3b8  call 0xE951550                             ; -> sub_e951550 (noreturn)
        // 0x661a3bd  int3                                          ; dead padding after noreturn call (in [0x661a2f0, 0x661a3be))
        sub_e951550(loaded);                                   // 0x661a3b8 call 0xE951550
        __assume(false);
    }

    // 0x661a386  add rsp,0x48                                   ; epilogue
    // 0x661a38a  ret                                            ; epilogue
    return;

    // ----- error path: loc_661a38b -----
errorThrow:
    // 0x661a38b  xorps xmm0,xmm0                               
    // 0x661a38e  movups [rsp+0x30],xmm0                         ; zero 16-byte exception object
    // 0x661a393  lea rax,[0xF08E738]                           ; [data_f08e738]
    // 0x661a39a  mov [rsp+0x28],rax                             ; exception object qword = 0xF08E738
    // 0x661a39f  lea rdx,[0xFB3B080]                           ; [data_fb3b080] throw info
    // 0x661a3a6  lea rcx,[rsp+0x28]                             ; rcx = &exception object
    // 0x661a3ab  call 0xEEC6D80                                ; -> sub_eec6d80 (noreturn, throws)
    std::uint8_t excObj[16] = {};
    *reinterpret_cast<std::uintptr_t*>(excObj) = 0xF08E738ull;  // 0x661a38b..0x661a39a
    sub_eec6d80(excObj, 0xFB3B080ull, 0, 0);                   // 0x661a3ab  call 0xEEC6D80  (noreturn)
    __assume(false);
}

// Verbatim instructions of the function (matches `rdis dis 0x661a2f0 0xce` from the exe,
// machine-checked with tools/sigs/verify_oc.py):
#if 0
0x661a2f0  sub rsp,0x48
0x661a2f4  mov rax,[0x1230A0C0]
0x661a2fb  xor rax,rsp
0x661a2fe  mov [rsp+0x40],rax
0x661a303  movss xmm0,[rdx]
0x661a307  xorps xmm1,xmm1
0x661a30a  ucomiss xmm1,xmm0
0x661a30d  ja short 0x661A38B
0x661a30f  cvttss2si eax,xmm0
0x661a313  movzx r8d,ax
0x661a317  xorps xmm1,xmm1
0x661a31a  cvtsi2ss xmm1,r8d
0x661a31f  ucomiss xmm0,xmm1
0x661a322  jne short 0x661A38B
0x661a324  jp short 0x661A38B
0x661a326  movzx r8d,word ptr [rcx+0x6EA]
0x661a32e  cmp r8w,ax
0x661a332  cmovb eax,r8d
0x661a336  mov [rcx+0x6EE],ax
0x661a33d  movss xmm0,[rdx+4]
0x661a342  xorps xmm1,xmm1
0x661a345  ucomiss xmm1,xmm0
0x661a348  ja short 0x661A38B
0x661a34a  cvttss2si eax,xmm0
0x661a34e  movzx edx,ax
0x661a351  xorps xmm1,xmm1
0x661a354  cvtsi2ss xmm1,edx
0x661a358  ucomiss xmm0,xmm1
0x661a35b  jne short 0x661A38B
0x661a35d  jp short 0x661A38B
0x661a35f  mov edx,[rcx+0x6EC]
0x661a365  cmp dx,ax
0x661a368  cmovb eax,edx
0x661a36b  mov [rcx+0x6F0],ax
0x661a372  mov rax,[rsp+0x40]
0x661a377  xor rax,rsp
0x661a37a  mov rcx,[0x1230A0C0]
0x661a381  cmp rcx,rax
0x661a384  jne short 0x661A3B0
0x661a386  add rsp,0x48
0x661a38a  ret
0x661a38b  xorps xmm0,xmm0
0x661a38e  movups [rsp+0x30],xmm0
0x661a393  lea rax,[0xF08E738]
0x661a39a  mov [rsp+0x28],rax
0x661a39f  lea rdx,[0xFB3B080]
0x661a3a6  lea rcx,[rsp+0x28]
0x661a3ab  call 0xEEC6D80
0x661a3b0  mov rcx,[rsp+0x40]
0x661a3b5  xor rcx,rsp
0x661a3b8  call 0xE951550
#endif

native::Footprint sub_661a2f0Footprint(Slot30* /*a0*/, float* /*a1*/) {
    // Writes go through run-time pointer a0 (fields +0x6EE, +0x6F0), not declared statically,
    // mirroring sub_bc04530's empty-footprint convention.
    return native::Footprint();
}

LIFT_FN(sub_661a2f0, "sub_661a2f0", 0x661a2f0, sub_661a2f0, sub_661a2f0Footprint);

} // namespace native
