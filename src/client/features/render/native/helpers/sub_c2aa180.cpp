// LIFT 0xc2aa180 size 0xec 1.26.62.01 sub_c2aa180
#include "sub_c2aa180.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <intrin.h>

namespace native::helpers {

// Layout assertions (gate checks the .cpp file, not the .h).
static_assert(offsetof(sub_c2aa180_state, field0x8) == 0x08,   "sub_c2aa180: field0x8 at +0x08");
static_assert(offsetof(sub_c2aa180_state, field0x18) == 0x18,  "sub_c2aa180: field0x18 at +0x18");
static_assert(offsetof(sub_c2aa180_state, buffer_start) == 0x30, "sub_c2aa180: buffer_start at +0x30");
static_assert(offsetof(sub_c2aa180_state, buffer_end) == 0x40,  "sub_c2aa180: buffer_end at +0x40");
static_assert(offsetof(sub_c2aa180_state, refcounted) == 0x50, "sub_c2aa180: refcounted at +0x50");
static_assert(sizeof(sub_c2aa180_state) == 0x58,               "sub_c2aa180: this mirror size");

// sub_c2aa180 (0xc2aa180, size 0xec, 1.26.62.01).
//
// Teardown of the object passed in RCX (this):
//   0xc2aa197  rcx = *(this + 0x8)
//   0xc2aa19b  copy *(this + 0x18) (16 bytes) to stack; call sub_e3295f0(rcx, &stack)
//   0xc2aa1ad  test al,al ; if al != 0:
//       0xc2aa1b5  rcx = *(this + 0x8) (reload)
//       0xc2aa1b9  copy *(this + 0x18) (16 bytes) to stack; call sub_e32a220(rcx, &stack)
//       0xc2aa1ca  *(byte *)(this + 0x20) = 0
//   0xc2aa1ce  rdi = *(this + 0x50) (refcounted object); if rdi != 0:
//       0xc2aa1d7  lock dec dword ptr [rdi + 8]; if == 0:
//           0xc2aa1e6  call qword ptr [0xF99FFA0] -> boundary::g_eea6040_thunk(rdi, vfptr[0])
//       0xc2aa1ec  lock dec dword ptr [rdi + 0xC]; if == 0:
//           0xc2aa1fc  call qword ptr [0xF99FFA0] -> boundary::g_eea6040_thunk(rdi, vfptr[1])
//   0xc2aa202  rcx = *(this + 0x30) (buffer_start); if rcx != 0:
//       0xc2aa20f  size = *(this + 0x40) - buffer_start
//       0xc2aa212  if size >= 0x1000:
//           0xc2aa21b  rax = *(buffer - 8); delta = (buffer - 8) - rax
//           0xc2aa22a  if delta >= 0x20: failfast: call qword ptr [0xF9A8C78](0,0,0,0); int3
//           0xc2aa230  sub_e935700(*(buffer - 8))
//       0xc2aa219  if size < 0x1000: sub_e935700(buffer)
//       0xc2aa23f  zero 16 bytes at this + 0x30 (buffer_start + pad0x38)
//       0xc2aa242  zero 8 bytes at this + 0x40 (buffer_end)
//   epilogue: ret (return value in RAX, not explicitly set by the original)
//
// Calls [V]:
//   0xc2aa1a7  call 0xE3295F0   (sub_e3295f0 - unresolved target, not in lift set or boundary)
//   0xc2aa1c4  call 0xE32A220   (sub_e32a220 - unresolved target, not in lift set or boundary)
//   0xc2aa1e6  call qword ptr [0xF99FFA0]   (sub_eea6040 via boundary::g_eea6040_thunk)
//   0xc2aa1fc  call qword ptr [0xF99FFA0]   (sub_eea6040 via boundary::g_eea6040_thunk)
//   0xc2aa237  call 0xE935700   (native::sub_e935700, lift set)
//   0xc2aa265  call qword ptr [0xF9A8C78]   (failfast, data-slot read at call time)
// No null guards or SEH beyond the original's own tests; no stubs; no skipped branches.

uintptr_t sub_c2aa180(sub_c2aa180_state* self)
{
    auto* const a0 = self;   // 0xc2aa194 mov rsi,rcx  (a0 arrives in RCX)

    // 0xc2aa180..0xc2aa194: prologue (push rbp/rsi/rdi; sub rsp,0x60; lea rbp,[rsp+0x60];
    //                          mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE - dead store)

    // 0xc2aa194..0xc2aa1af: phase 1 - sub_e3295f0 call
    //   0xc2aa197  mov rcx,[rcx+8]       R a0+0x8
    //   0xc2aa19b  movups xmm0,[rsi+0x18]  R a0+0x18 (16 bytes)
    //   0xc2aa19f  movaps [rbp-0x30],xmm0  (stack copy)
    //   0xc2aa1a3  lea rdx,[rbp-0x30]
    //   0xc2aa1a7  call 0xE3295F0
    //   0xc2aa1ac  nop
    //   0xc2aa1ad  test al,al
    //   0xc2aa1af  je short 0xC2AA1CE
    const void* const field0x8 = a0->field0x8;          // 0xc2aa197 mov rcx,[rcx+8]
    std::uint8_t local0x30[16];
    std::memcpy(local0x30, a0->field0x18, 16);          // 0xc2aa19b/0xc2aa19f movups/movaps a0+0x18
    if (native::sub_e3295f0(const_cast<void*>(field0x8), local0x30)) {   // 0xc2aa1a7 call 0xE3295F0
        // 0xc2aa1b1..0xc2aa1ca: phase 2 - sub_e32a220 call (only when al != 0)
        //   0xc2aa1b1  lea rax,[rsi+0x18]
        //   0xc2aa1b5  mov rcx,[rsi+8]       R a0+0x8 (reload)
        //   0xc2aa1b9  movups xmm0,[rax]     R a0+0x18 (again)
        //   0xc2aa1bc  movaps [rbp-0x20],xmm0  (stack copy)
        //   0xc2aa1c0  lea rdx,[rbp-0x20]
        //   0xc2aa1c4  call 0xE32A220
        //   0xc2aa1c9  nop
        //   0xc2aa1ca  mov byte ptr [rsi+0x20],0   W a0+0x20
        std::uint8_t local0x20[16];
        std::memcpy(local0x20, a0->field0x18, 16);      // 0xc2aa1b9/0xc2aa1bc movups/movaps a0+0x18
        (void)native::sub_e32a220(const_cast<void*>(field0x8), local0x20);  // 0xc2aa1c4 call 0xE32A220
        a0->field0x18[8] = 0;   // 0xc2aa1ca mov byte ptr [rsi+0x20],0  (byte at +0x20 = field0x18[8])
    }

    // loc_c2aa1ce: phase 3 - refcounted object release
    //   0xc2aa1ce  mov rdi,[rsi+0x50]     R a0+0x50 (refcounted object)
    //   0xc2aa1d2  test rdi,rdi
    //   0xc2aa1d5  je short 0xC2AA202     if null, skip release
    void* const object = a0->refcounted;   // 0xc2aa1ce mov rdi,[rsi+0x50]
    if (object != nullptr) {               // 0xc2aa1d2 test rdi,rdi ; 0xc2aa1d5 je short 0xC2AA202
        auto* const obj = reinterpret_cast<RefcountedObj*>(object);

        // 0xc2aa1d7  lock dec dword ptr [rdi+8]   W *(object+0x8)
        // 0xc2aa1db  jne short 0xC2AA202          skip destructor when result != 0
        if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&obj->refcount1)) == 0) {
            // refcount1 reached 0 -> virtual destructor vfptr[0](object)
            //   0xc2aa1dd  mov rax,[rdi]      R object+0x00 (vfptr)
            //   0xc2aa1e0  mov rax,[rax]      R vfptr[0] -> RAX
            //   0xc2aa1e3  mov rcx,rdi         RCX = object
            //   0xc2aa1e6  call qword ptr [0xF99FFA0]   -> boundary::g_eea6040_thunk(object, vfptr[0])
            void** const vfptr = *reinterpret_cast<void***>(object);   // 0xc2aa1dd/0xc2aa1e0
            boundary::g_eea6040_thunk(object, vfptr[0]);   // 0xc2aa1e6 call qword ptr [0xF99FFA0]
        }

        // 0xc2aa1ec  lock dec dword ptr [rdi+0xC]   W *(object+0xC)
        // 0xc2aa1f0  jne short 0xC2AA202          skip operator delete when result != 0
        if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&obj->refcount2)) == 0) {
            // refcount2 reached 0 -> virtual delete vfptr[1](object)
            //   0xc2aa1f2  mov rax,[rdi]      R object+0x00 (vfptr)
            //   0xc2aa1f5  mov rax,[rax+8]    R vfptr[1] -> RAX
            //   0xc2aa1f9  mov rcx,rdi         RCX = object
            //   0xc2aa1fc  call qword ptr [0xF99FFA0]   -> boundary::g_eea6040_thunk(object, vfptr[1])
            void** const vfptr = *reinterpret_cast<void***>(object);   // 0xc2aa1f2/0xc2aa1f5
            boundary::g_eea6040_thunk(object, vfptr[1]);   // 0xc2aa1fc call qword ptr [0xF99FFA0]
        }
    }

    // loc_c2aa202: phase 4 - buffer dealloc
    //   0xc2aa202  mov rcx,[rsi+0x30]     R a0+0x30 (buffer_start)
    //   0xc2aa206  test rcx,rcx
    //   0xc2aa209  je short 0xC2AA24A     if null, skip dealloc
    void* const buffer = a0->buffer_start;   // 0xc2aa202 mov rcx,[rsi+0x30]
    if (buffer != nullptr) {               // 0xc2aa206 test rcx,rcx ; 0xc2aa209 je short 0xC2AA24A
        // 0xc2aa20b  mov rdx,[rsi+0x40]     R a0+0x40 (buffer_end)
        // 0xc2aa20f  sub rdx,rcx            size = buffer_end - buffer_start
        // 0xc2aa212  cmp rdx,0x1000
        // 0xc2aa219  jb short 0xC2AA233     if size < 0x1000, small path
        void* const bufferEnd = a0->buffer_end;   // 0xc2aa20b mov rdx,[rsi+0x40]
        const uintptr_t size =
            reinterpret_cast<uintptr_t>(bufferEnd) -
            reinterpret_cast<uintptr_t>(buffer);   // 0xc2aa20f sub rdx,rcx
        if (size < 0x1000) {               // 0xc2aa212 cmp rdx,0x1000 ; 0xc2aa219 jb short 0xC2AA233
            // 0xc2aa233  add rsi,0x30
            // 0xc2aa237  call 0xE935700     -> native::sub_e935700(buffer)
            native::sub_e935700(buffer);   // 0xc2aa237 call 0xE935700
        } else {
            // 0xc2aa21b  mov rax,[rcx-8]       R *(buffer - 8) (heap metadata)
            // 0xc2aa21f  add rcx,0xFFFFFFFFFFFFFFF8   rcx = buffer - 8
            // 0xc2aa223  sub rcx,rax           rcx = (buffer - 8) - heapMeta
            // 0xc2aa226  cmp rcx,0x20
            // 0xc2aa22a  jae short 0xC2AA252   if delta >= 0x20, failfast
            const uintptr_t heapMeta =
                *reinterpret_cast<const uintptr_t*>(
                    reinterpret_cast<const char*>(buffer) - 8);   // 0xc2aa21b mov rax,[rcx-8]
            const uintptr_t delta =
                (reinterpret_cast<uintptr_t>(buffer) - 8) - heapMeta;   // 0xc2aa21f/0xc2aa223
            if (delta >= 0x20) {           // 0xc2aa226 cmp rcx,0x20 ; 0xc2aa22a jae short 0xC2AA252
                // 0xc2aa252..0xc2aa26b failfast path
                //   0xc2aa252  mov qword ptr [rsp+0x20],0
                //   0xc2aa25b  xor ecx,ecx
                //   0xc2aa25d  xor edx,edx
                //   0xc2aa25f  xor r8d,r8d
                //   0xc2aa262  xor r9d,r9d
                //   0xc2aa265  call qword ptr [0xF9A8C78]   ; [data_f9a8c78]
                //   0xc2aa26b  int3
                using failfast_fn = void(__cdecl*)(void*, void*, void*, void*);
                failfast_fn const failfast = reinterpret_cast<failfast_fn>(
                    *reinterpret_cast<uintptr_t*>(
                        RewriteRegistry::imageBase() + sub_c2aa180Layout::kFailfastSlotRva));
                failfast(nullptr, nullptr, nullptr, nullptr);   // 0xc2aa265 call qword ptr [0xF9A8C78]
                __debugbreak();                                 // 0xc2aa26b int3
                __assume(false);
            }
            // 0xc2aa22c  add rdx,0x27           size + 0x27 (dead inside callee)
            // 0xc2aa230  mov rcx,rax            heapMeta
            // 0xc2aa233  add rsi,0x30
            // 0xc2aa237  call 0xE935700        -> native::sub_e935700(*(buffer - 8))
            native::sub_e935700(reinterpret_cast<void*>(heapMeta));   // 0xc2aa237 call 0xE935700
        }

        // 0xc2aa23f  movups [rsi],xmm0       zero 16 bytes at a0+0x30 (+0x30..+0x3F)
        // 0xc2aa242  mov qword ptr [rsi+0x10],0   zero 8 bytes at a0+0x40 (+0x40..+0x47)
        std::memset(&a0->buffer_start, 0, 24);   // 0xc2aa23f/0xc2aa242 zero buffer_start, +0x38, buffer_end
    }

    // loc_c2aa24a: epilogue
    //   0xc2aa24a  add rsp,0x60
    //   0xc2aa24e  pop rdi
    //   0xc2aa24f  pop rsi
    //   0xc2aa250  pop rbp
    //   0xc2aa251  ret
    return 0;   // return value in RAX: original does not explicitly set RAX before ret
}

} // namespace native::helpers

LIFT_FN(sub_c2aa180, "sub_c2aa180", 0xc2aa180, ::native::helpers::sub_c2aa180, nullptr);

#if 0
// Verbatim instructions of [0xc2aa180, 0xc2aa26c) (rdis dis 0xc2aa180 0xec);
// machine-checked by tools/sigs/verify_oc.py against the exe.
0xc2aa180  push rbp
0xc2aa181  push rsi
0xc2aa182  push rdi
0xc2aa183  sub rsp,0x60
0xc2aa187  lea rbp,[rsp+0x60]
0xc2aa18c  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
0xc2aa194  mov rsi,rcx
0xc2aa197  mov rcx,[rcx+8]
0xc2aa19b  movups xmm0,[rsi+0x18]
0xc2aa19f  movaps [rbp-0x30],xmm0
0xc2aa1a3  lea rdx,[rbp-0x30]
0xc2aa1a7  call 0xE3295F0
0xc2aa1ac  nop
0xc2aa1ad  test al,al
0xc2aa1af  je short 0xC2AA1CE
0xc2aa1b1  lea rax,[rsi+0x18]
0xc2aa1b5  mov rcx,[rsi+8]
0xc2aa1b9  movups xmm0,[rax]
0xc2aa1bc  movaps [rbp-0x20],xmm0
0xc2aa1c0  lea rdx,[rbp-0x20]
0xc2aa1c4  call 0xE32A220
0xc2aa1c9  nop
0xc2aa1ca  mov byte ptr [rsi+0x20],0
0xc2aa1ce  mov rdi,[rsi+0x50]
0xc2aa1d2  test rdi,rdi
0xc2aa1d5  je short 0xC2AA202
0xc2aa1d7  lock dec dword ptr [rdi+8]
0xc2aa1db  jne short 0xC2AA202
0xc2aa1dd  mov rax,[rdi]
0xc2aa1e0  mov rax,[rax]
0xc2aa1e3  mov rcx,rdi
0xc2aa1e6  call qword ptr [0xF99FFA0]
0xc2aa1ec  lock dec dword ptr [rdi+0xC]
0xc2aa1f0  jne short 0xC2AA202
0xc2aa1f2  mov rax,[rdi]
0xc2aa1f5  mov rax,[rax+8]
0xc2aa1f9  mov rcx,rdi
0xc2aa1fc  call qword ptr [0xF99FFA0]
0xc2aa202  mov rcx,[rsi+0x30]
0xc2aa206  test rcx,rcx
0xc2aa209  je short 0xC2AA24A
0xc2aa20b  mov rdx,[rsi+0x40]
0xc2aa20f  sub rdx,rcx
0xc2aa212  cmp rdx,0x1000
0xc2aa219  jb short 0xC2AA233
0xc2aa21b  mov rax,[rcx-8]
0xc2aa21f  add rcx,0xFFFFFFFFFFFFFFF8
0xc2aa223  sub rcx,rax
0xc2aa226  cmp rcx,0x20
0xc2aa22a  jae short 0xC2AA252
0xc2aa22c  add rdx,0x27
0xc2aa230  mov rcx,rax
0xc2aa233  add rsi,0x30
0xc2aa237  call 0xE935700
0xc2aa23c  xorps xmm0,xmm0
0xc2aa23f  movups [rsi],xmm0
0xc2aa242  mov qword ptr [rsi+0x10],0
0xc2aa24a  add rsp,0x60
0xc2aa24e  pop rdi
0xc2aa24f  pop rsi
0xc2aa250  pop rbp
0xc2aa251  ret
0xc2aa252  mov qword ptr [rsp+0x20],0
0xc2aa25b  xor ecx,ecx
0xc2aa25d  xor edx,edx
0xc2aa25f  xor r8d,r8d
0xc2aa262  xor r9d,r9d
0xc2aa265  call qword ptr [0xF9A8C78]
0xc2aa26b  int3
#endif
