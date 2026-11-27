// LIFT 0x568db90 size 0x80 1.26.62.01 sub_568db90
#include "client/features/render/native/passes/sub_568db90.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

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

using FailFn = void (__cdecl*)(void*, void*, void*, void*);

} // namespace

// sub_568db90: Scene/HUD view-setup task element cleanup.
// x64 Microsoft ABI: rcx = switch index (element->index + 1), rdx = unused, r8 = element.
// Return: void (rax = sub_e935700's result, ignored by caller [V: 0x568dace caller does not use rax]).
//
// 0x568db90..0x568dba5: prologue + jump-table switch on index
//   0x568db90  push rsi
//   0x568db91  sub rsp,0x30
//   0x568db95  lea rax,[0xF25D03C]
//   0x568db9c  movsxd rcx,[rax+rcx*4]
//   0x568dba0  add rcx,rax
//   0x568dba3  jmp rcx
void sub_568db90(std::uint8_t index, void* /*unused*/, ViewElem* elem) {
    // 0x568db90..0x568dba5
    switch (index) {
    case 1:
    case 2: {
        // 0x568dba5..0x568dbbd: null check + size = end - ptr
        //   0x568dba5  mov rcx,[r8]              ; ptr = elem->ptr
        //   0x568dba8  test rcx,rcx
        //   0x568dbab  je short 0x568DBF0        ; if null -> epilogue + ret
        //   0x568dbad  mov rdx,[r8+0x10]         ; end = elem->end
        //   0x568dbb1  sub rdx,rcx               ; size = end - ptr
        //   0x568dbb4  cmp rdx,0x1000
        //   0x568dbbb  jb short 0x568DBDA        ; if size < 0x1000 -> small-buffer path
        void* const ptr = elem->ptr;
        if (ptr == nullptr) return;
        void* const end = elem->end;
        const std::uint64_t size =
            reinterpret_cast<std::uint8_t*>(end) - reinterpret_cast<std::uint8_t*>(ptr);
        if (size < 0x1000ui64) {
            // 0x568dbda..0x568dbdd: small-buffer path, no heap validation
            //   0x568dbda  mov rsi,r8            ; rsi = elem
            //   0x568dbdd  call 0xE935700        ; (rcx = ptr, rdx = size)
            sub_e935700(ptr, size);
        } else {
            // 0x568dbbd..0x568dbcc: heap-header validation
            //   0x568dbbd  mov rax,[rcx-8]       ; old_base = [ptr - 8]
            //   0x568dbc1  add rcx,0xFFFFFFFFFFFFFFF8  ; rcx = ptr - 8
            //   0x568dbc5  sub rcx,rax           ; probe = (ptr - 8) - old_base
            //   0x568dbc8  cmp rcx,0x20
            //   0x568dbcc  jae short 0x568DBF6   ; if probe >= 0x20 -> dead fail path
            void* const old_base = *reinterpret_cast<void** volatile*>(
                reinterpret_cast<std::uint8_t*>(ptr) - 8);
            const std::uint64_t probe =
                (reinterpret_cast<std::uint8_t*>(ptr) - 8) -
                reinterpret_cast<std::uint8_t*>(old_base);
            if (probe >= 0x20ui64) {
                // 0x568dbf6..0x568dc0f: dead fail handler (noreturn)
                //   0x568dbf6  mov qword ptr [rsp+0x20],0
                //   0x568dbff  xor ecx,ecx
                //   0x568dc01  xor edx,edx
                //   0x568dc03  xor r8d,r8d
                //   0x568dc06  xor r9d,r9d
                //   0x568dc09  call qword ptr [0xF9A8C78]  ; fail handler, 0 args
                //   0x568dc0f  int3                          ; trap
                reinterpret_cast<FailFn>(slot_f9a8c78())(nullptr, nullptr, nullptr, nullptr);
                __assume(false);  // int3: noreturn, matches original's trap
            }
            // 0x568dbce..0x568dbdd: large-buffer path
            //   0x568dbce  mov rsi,r8            ; rsi = elem
            //   0x568dbd1  add rdx,0x27          ; size += 0x27
            //   0x568dbd5  mov rcx,rax           ; rcx = old_base
            //   0x568dbdd  call 0xE935700        ; (rcx = old_base, rdx = size + 0x27)
            sub_e935700(old_base, size + 0x27ui64);
        }
        // 0x568dbe2..0x568dbe8: clear element fields
        //   0x568dbe2  xorps xmm0,xmm0
        //   0x568dbe5  movups [rsi],xmm0         ; [elem+0x00] = 0 (16 bytes: ptr + pad0)
        //   0x568dbe8  mov qword ptr [rsi+0x10],0 ; [elem+0x10] = 0 (end field)
        elem->ptr = nullptr;
        elem->end = nullptr;
        // 0x568dbf0..0x568dbf5: epilogue + ret
        //   0x568dbf0  add rsp,0x30
        //   0x568dbf4  pop rsi
        //   0x568dbf5  ret
        return;
    }
    // case 0, 3, 4: 0x568dbf0..0x568dbf5 epilogue + ret (fall through to end of function)
}

#if 0
0x568db90  push rsi
0x568db91  sub rsp,0x30
0x568db95  lea rax,[0xF25D03C]
0x568db9c  movsxd rcx,[rax+rcx*4]
0x568dba0  add rcx,rax
0x568dba3  jmp rcx
0x568dba5  mov rcx,[r8]
0x568dba8  test rcx,rcx
0x568dbab  je short 0x568DBF0
0x568dbad  mov rdx,[r8+0x10]
0x568dbb1  sub rdx,rcx
0x568dbb4  cmp rdx,0x1000
0x568dbbb  jb short 0x568DBDA
0x568dbbd  mov rax,[rcx-8]
0x568dbc1  add rcx,0xFFFFFFFFFFFFFFF8
0x568dbc5  sub rcx,rax
0x568dbc8  cmp rcx,0x20
0x568dbcc  jae short 0x568DBF6
0x568dbce  mov rsi,r8
0x568dbd1  add rdx,0x27
0x568dbd5  mov rcx,rax
0x568dbd8  jmp short 0x568DBDD
0x568dbda  mov rsi,r8
0x568dbdd  call 0xE935700
0x568dbe2  xorps xmm0,xmm0
0x568dbe5  movups [rsi],xmm0
0x568dbe8  mov qword ptr [rsi+0x10],0
0x568dbf0  add rsp,0x30
0x568dbf4  pop rsi
0x568dbf5  ret
0x568dbf6  mov qword ptr [rsp+0x20],0
0x568dbff  xor ecx,ecx
0x568dc01  xor edx,edx
0x568dc03  xor r8d,r8d
0x568dc06  xor r9d,r9d
0x568dc09  call qword ptr [0xF9A8C78]
0x568dc0f  int3
#endif

} // namespace native

LIFT_FN(sub_568db90, "sub_568db90", 0x568DB90, sub_568db90, nullptr);
