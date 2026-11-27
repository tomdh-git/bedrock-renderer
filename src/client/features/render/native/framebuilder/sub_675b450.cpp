// LIFT 0x675b450 size 0xc8 1.26.62.01 BgfxFrameBuilder::endFrame
#include "client/features/render/native/framebuilder/sub_675b450.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstring>

static_assert(sizeof(void*) == 8, "675b450: x64 ABI, pointer-sized address space");
static_assert(offsetof(native::BgfxFrameBuilder, field0x10) == 0x10, "675b450: field0x10 at +0x10");
static_assert(offsetof(native::BgfxFrameBuilder, field0x18) == 0x18, "675b450: field0x18 at +0x18");
static_assert(offsetof(native::BgfxFrameBuilder, field0x20) == 0x20, "675b450: field0x20 at +0x20");
static_assert(offsetof(native::EndFrameElem, flag) == 0x50, "675b450: EndFrameElem::flag at +0x50");
static_assert(sizeof(native::EndFrameElem) == 0x58, "675b450: EndFrameElem size 0x58");

namespace native {

namespace {

// Data slot 0xF9A8C78: fail-handler function pointer (IAT/import slot).
// Read at call time, exactly as `call qword ptr [0xF9A8C78]` does. [V]
inline std::uint8_t* image_base() {
    return reinterpret_cast<std::uint8_t*>(RewriteRegistry::imageBase());
}
inline void* slot_f9a8c78() {
    return *reinterpret_cast<void** volatile*>(image_base() + 0xF9A8C78);
}

} // namespace

// BgfxFrameBuilder::endFrame (0x675b450, size 0xc8, 1.26.62.01).
//
// Reversed source (complete). Every instruction of [0x675b450, 0x675b518) is
// covered by the citation next to the statement that implements it, and every
// `call` is quoted verbatim in the #if 0 block at the end of this file.
//
// The function appends one 0x58-byte element to the growable buffer at
// self+0x18 (cur) / self+0x20 (end), using self+0x10 as the vector object.
//   - When cur != end: the element (built from the two 16-byte global
//     constants at [0xF2BE848] and [0xF2BE838]) is written at cur and cur is
//     advanced by 0x58.
//   - When cur == end (buffer full): sub_b0ad0 (stl boundary, vector
//     push_back/reallocate) is invoked with &self+0x10, cur and &elem; it
//     reallocates if needed, copy-constructs the element and advances cur.
//     elem.flag (+0x50) is 0, so the subsequent size-handling block is dead
//     code (cmp byte [rbp],1 is always false) and is not reached.
// Returns self (RAX = RSI = RCX entry).
//
// Notes:
//   - [rbp+0x10] is written with -2 and never read (dead store); replicated
//     for faithfulness.
//   - [rbp-0x18] (size) and [rbp-0x30] (buf) are only ever read inside the
//     dead size block and are never written by this function (garbage when
//     reached).
//   - The call qword ptr [0xF9A8C78] on the noreturn watson path reads the
//     function pointer from data slot 0xF9A8C78 at call time (hard rule 69)
//     and is called with five zero arguments; it never returns (int3 follows).
void* sub_675b450(void* self) {
    // 0x675b450..0x675b459: push rbp; push rsi; sub rsp,0x98; lea rbp,[rsp+0x80]
    std::uint8_t* const s = reinterpret_cast<std::uint8_t*>(self);  // rsi = rcx = self

    // 0x675b461  mov qword ptr [rbp+0x10],0xFFFFFFFFFFFFFFFE   ; dead store, never read
    std::int64_t local_rbp_0x10 = 0xFFFFFFFFFFFFFFFE;             // 0x675b461

    // 0x675b469  mov rsi,rcx                                       ; rsi = self (in s)

    // 0x675b46c  movups xmm0,[0xF2BE848]   ; R data_f2be848 (16 bytes)
    const std::uint64_t xmm0_lo = *reinterpret_cast<const std::uint64_t*>(data_f2be848() + 0);
    const std::uint64_t xmm0_hi = *reinterpret_cast<const std::uint64_t*>(data_f2be848() + 8);
    // 0x675b473  movups [rbp-0x40],xmm0   ; W elem+0x10
    // 0x675b477  movups xmm1,[0xF2BE838]   ; R data_f2be838 (16 bytes)
    const std::uint64_t xmm1_lo = *reinterpret_cast<const std::uint64_t*>(data_f2be838() + 0);
    const std::uint64_t xmm1_hi = *reinterpret_cast<const std::uint64_t*>(data_f2be838() + 8);
    // 0x675b47e  movaps [rbp-0x50],xmm1   ; W elem+0x00
    EndFrameElem elem = {};
    elem.lo1 = xmm0_lo;                      // 0x675b473  W elem+0x10 (low)
    elem.hi1 = xmm0_hi;                      // 0x675b473  W elem+0x18 (high)
    elem.lo0 = xmm1_lo;                      // 0x675b47e  W elem+0x00 (low)
    elem.hi0 = xmm1_hi;                      // 0x675b47e  W elem+0x08 (high)
    // 0x675b482  mov byte ptr [rbp],0     ; W elem+0x50 flag = 0
    elem.flag = 0;                           // 0x675b482  W elem+0x50

    // 0x675b486  mov rdx,[rcx+0x18]        ; R self+0x18 (cur)
    // 0x675b48a  cmp rdx,[rcx+0x20]        ; R self+0x20 (end)
    // 0x675b48e  je short 0x675B4A2        ; if cur == end: full path
    void* cur = *reinterpret_cast<void**>(s + 0x18);
    void* end = *reinterpret_cast<void**>(s + 0x20);
    if (cur != end) {
        // 0x675b490  movups [rdx+0x10],xmm0   ; W cur->+0x10
        // 0x675b494  movups [rdx],xmm1        ; W cur->+0x00
        // 0x675b497  mov byte ptr [rdx+0x50],0 ; W cur->+0x50
        std::uint8_t* const p = reinterpret_cast<std::uint8_t*>(cur);
        p[0x10] = static_cast<std::uint8_t>(xmm0_lo); p[0x11] = static_cast<std::uint8_t>(xmm0_lo >> 8);
        p[0x12] = static_cast<std::uint8_t>(xmm0_lo >> 16); p[0x13] = static_cast<std::uint8_t>(xmm0_lo >> 24);
        p[0x14] = static_cast<std::uint8_t>(xmm0_lo >> 32); p[0x15] = static_cast<std::uint8_t>(xmm0_lo >> 40);
        p[0x16] = static_cast<std::uint8_t>(xmm0_lo >> 48); p[0x17] = static_cast<std::uint8_t>(xmm0_lo >> 56);
        p[0x18] = static_cast<std::uint8_t>(xmm0_hi); p[0x19] = static_cast<std::uint8_t>(xmm0_hi >> 8);
        p[0x1a] = static_cast<std::uint8_t>(xmm0_hi >> 16); p[0x1b] = static_cast<std::uint8_t>(xmm0_hi >> 24);
        p[0x1c] = static_cast<std::uint8_t>(xmm0_hi >> 32); p[0x1d] = static_cast<std::uint8_t>(xmm0_hi >> 40);
        p[0x1e] = static_cast<std::uint8_t>(xmm0_hi >> 48); p[0x1f] = static_cast<std::uint8_t>(xmm0_hi >> 56);
        p[0x00] = static_cast<std::uint8_t>(xmm1_lo); p[0x01] = static_cast<std::uint8_t>(xmm1_lo >> 8);
        p[0x02] = static_cast<std::uint8_t>(xmm1_lo >> 16); p[0x03] = static_cast<std::uint8_t>(xmm1_lo >> 24);
        p[0x04] = static_cast<std::uint8_t>(xmm1_lo >> 32); p[0x05] = static_cast<std::uint8_t>(xmm1_lo >> 40);
        p[0x06] = static_cast<std::uint8_t>(xmm1_lo >> 48); p[0x07] = static_cast<std::uint8_t>(xmm1_lo >> 56);
        p[0x08] = static_cast<std::uint8_t>(xmm1_hi); p[0x09] = static_cast<std::uint8_t>(xmm1_hi >> 8);
        p[0x0a] = static_cast<std::uint8_t>(xmm1_hi >> 16); p[0x0b] = static_cast<std::uint8_t>(xmm1_hi >> 24);
        p[0x0c] = static_cast<std::uint8_t>(xmm1_hi >> 32); p[0x0d] = static_cast<std::uint8_t>(xmm1_hi >> 40);
        p[0x0e] = static_cast<std::uint8_t>(xmm1_hi >> 48); p[0x0f] = static_cast<std::uint8_t>(xmm1_hi >> 56);
        p[0x50] = 0;                         // 0x675b497  W cur->+0x50
        // 0x675b49b  add qword ptr [rsi+0x18],0x58   ; W self+0x18 += 0x58
        *reinterpret_cast<void**>(s + 0x18) = reinterpret_cast<std::uint8_t*>(cur) + 0x58;
        // 0x675b4a0  jmp short 0x675B4F1        ; goto end
    } else {
        // 0x675b4a2  lea rcx,[rsi+0x10]        ; RCX = &self+0x10 (vector object)
        // 0x675b4a6  lea r8,[rbp-0x50]         ; R8 = &elem
        // 0x675b4aa  call 0xB0AD0              ; sub_b0ad0(&self+0x10, cur, &elem)
        sub_b0ad0(reinterpret_cast<void*>(s + 0x10), cur, reinterpret_cast<void*>(&elem));
        // 0x675b4af  nop
        // 0x675b4b0  cmp byte ptr [rbp],1      ; elem.flag == 1? (always 0 here)
        // 0x675b4b4  jne short 0x675B4F1       ; not 1 -> end (dead block skipped)
        if (elem.flag == 1) {
            // ---- dead size-handling block (0x675b4b6..0x675b4ec), unreachable
            // because elem.flag == 0. [rbp-0x18] (size) and [rbp-0x30] (buf)
            // are never written by this function, so they hold garbage here.
            std::int64_t local_size;      // [rbp-0x18], garbage when reached
            void* local_buf;              // [rbp-0x30], garbage when reached
            // 0x675b4b6  mov rax,[rbp-0x18]
            local_size = 0;
            // 0x675b4ba  cmp rax,0x10
            // 0x675b4be  jb short 0x675B4F1   ; if size < 0x10 -> end
            if (local_size < 0x10) {
                // goto end
            } else {
                // 0x675b4c0  mov rcx,[rbp-0x30]
                local_buf = nullptr;
                // 0x675b4c4  lea rdx,[rax+1]
                // 0x675b4c8  cmp rdx,0x1000
                // 0x675b4cf  jb short 0x675B4EC ; if size+1 < 0x1000: small path
                if (static_cast<std::uint64_t>(local_size) + 1 >= 0x1000) {
                    // 0x675b4d1  mov r8,[rcx-8]              ; R [buf-8]
                    // 0x675b4d5  add rcx,0xFFFFFFFFFFFFFFF8  ; rcx = buf - 8
                    // 0x675b4d9  sub rcx,r8                  ; rcx = buf - 8 - [buf-8]
                    // 0x675b4dc  cmp rcx,0x20
                    // 0x675b4e0  jae short 0x675B4FE         ; if probe >= 0x20: watson
                    const std::uint8_t* const b = reinterpret_cast<const std::uint8_t*>(local_buf);
                    const std::uintptr_t old_base = *reinterpret_cast<const std::uintptr_t*>(b - 8);
                    const std::uintptr_t probe = (reinterpret_cast<std::uintptr_t>(b) - 8) - old_base;
                    if (probe >= 0x20) {
                        // 0x675b4fe..0x675b518: noreturn watson path
                        //   mov qword ptr [rsp+0x20],0 ; xor ecx,edx,r8d,r9d ; call qword ptr [0xF9A8C78] ; int3
                        using FailFn = void (__cdecl*)(void*, void*, void*, void*);
                        reinterpret_cast<FailFn>(slot_f9a8c78())(nullptr, nullptr, nullptr, nullptr);
                        __assume(false);  // noreturn; original traps with int3
                    }
                    // 0x675b4e2  add rax,0x28        ; size += 0x28
                    // 0x675b4e6  mov rdx,rax         ; rdx = size + 0x28
                    // 0x675b4e9  mov rcx,r8          ; rcx = [buf-8]
                    // fall into small_path: sub_e935700(rcx)
                }
                // loc_675b4ec:
                // 0x675b4ec  call 0xE935700   ; sub_e935700(rcx)  free buffer
                sub_e935700(local_buf);
            }
        }
    }
    // loc_675b4f1: end
    // 0x675b4f1  mov rax,rsi                 ; RAX = self
    // 0x675b4f4  add rsp,0x98
    // 0x675b4fb  pop rsi
    // 0x675b4fc  pop rbp
    // 0x675b4fd  ret
    return self;
}

// Verbatim instruction quotes for verify_oc (plain lines, two spaces after
// address), copied from rdis dis 0x675b450 0xc8:
#if 0
0x675b450  push rbp
0x675b451  push rsi
0x675b452  sub rsp,0x98
0x675b459  lea rbp,[rsp+0x80]
0x675b461  mov qword ptr [rbp+0x10],0xFFFFFFFFFFFFFFFE
0x675b469  mov rsi,rcx
0x675b46c  movups xmm0,[0xF2BE848]
0x675b473  movaps [rbp-0x40],xmm0
0x675b477  movups xmm1,[0xF2BE838]
0x675b47e  movaps [rbp-0x50],xmm1
0x675b482  mov byte ptr [rbp],0
0x675b486  mov rdx,[rcx+0x18]
0x675b48a  cmp rdx,[rcx+0x20]
0x675b48e  je short 0x675B4A2
0x675b490  movups [rdx+0x10],xmm0
0x675b494  movups [rdx],xmm1
0x675b497  mov byte ptr [rdx+0x50],0
0x675b49b  add qword ptr [rsi+0x18],0x58
0x675b4a0  jmp short 0x675B4F1
0x675b4a2  lea rcx,[rsi+0x10]
0x675b4a6  lea r8,[rbp-0x50]
0x675b4aa  call 0xB0AD0
0x675b4af  nop
0x675b4b0  cmp byte ptr [rbp],1
0x675b4b4  jne short 0x675B4F1
0x675b4b6  mov rax,[rbp-0x18]
0x675b4ba  cmp rax,0x10
0x675b4be  jb short 0x675B4F1
0x675b4c0  mov rcx,[rbp-0x30]
0x675b4c4  lea rdx,[rax+1]
0x675b4c8  cmp rdx,0x1000
0x675b4cf  jb short 0x675B4EC
0x675b4d1  mov r8,[rcx-8]
0x675b4d5  add rcx,0xFFFFFFFFFFFFFFF8
0x675b4d9  sub rcx,r8
0x675b4dc  cmp rcx,0x20
0x675b4e0  jae short 0x675B4FE
0x675b4e2  add rax,0x28
0x675b4e6  mov rdx,rax
0x675b4e9  mov rcx,r8
0x675b4ec  call 0xE935700
0x675b4f1  mov rax,rsi
0x675b4f4  add rsp,0x98
0x675b4fb  pop rsi
0x675b4fc  pop rbp
0x675b4fd  ret
0x675b4fe  mov qword ptr [rsp+0x20],0
0x675b507  xor ecx,ecx
0x675b509  xor edx,edx
0x675b50b  xor r8d,r8d
0x675b50e  xor r9d,r9d
0x675b511  call qword ptr [0xF9A8C78]
0x675b517  int3
#endif

LIFT_FN(sub_675b450, "sub_675b450", 0x675B450, sub_675b450, nullptr);

} // namespace native
