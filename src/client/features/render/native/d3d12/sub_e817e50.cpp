// LIFT 0xe817e50 size 0x1fe 1.26.62.01 sub_e817e50
#include "client/features/render/native/d3d12/sub_e817e50.h"
#include "client/features/render/native/Lift.h"

#include <cstddef>
#include <cstdint>

// Verbatim disassembly of [0xe817e50, 0xe81804e) (Minecraft Windows 1.26.62.01).
#if 0
0xe817e50  push r15
0xe817e52  push r14
0xe817e54  push r12
0xe817e56  push rsi
0xe817e57  push rdi
0xe817e58  push rbx
0xe817e59  sub rsp,0x38
0xe817e5d  mov esi,edx
0xe817e5f  mov rdi,rcx
0xe817e62  mov rbx,[rcx+0x19F60]
0xe817e69  mov r14,[rcx+0x19F68]
0xe817e70  cmp rbx,r14
0xe817e73  je short 0xE817ED2
0xe817e75  movzx r15d,si
0xe817e79  jmp short 0xE817E95
0xe817e7b  nop [rax+rax]
0xe817e80  mov qword ptr [r12+r15*8+0x1250],0
0xe817e8c  add rbx,8
0xe817e90  cmp rbx,r14
0xe817e93  je short 0xE817ED2
0xe817e95  mov r12,[rbx]
0xe817e98  mov rcx,[0x12ADF800]
0xe817e9f  test rcx,rcx
0xe817ea2  je short 0xE817E80
0xe817ea4  mov rdx,[r12+r15*8+0x1250]
0xe817eac  mov rax,[rcx]
0xe817eaf  mov rax,[rax+8]
0xe817eb3  mov dword ptr [rsp+0x28],0
0xe817ebb  mov qword ptr [rsp+0x20],0
0xe817ec4  xor r8d,r8d
0xe817ec7  xor r9d,r9d
0xe817eca  call qword ptr [0xF99FFA0]
0xe817ed0  jmp short 0xE817E80
0xe817ed2  cmp si,0xFFFF
0xe817ed6  je 0xE818040
0xe817edc  lea rax,[rdi+0xC9BAA0]
0xe817ee3  mov edx,[rdi+0xC9AA9C]
0xe817ee9  xor ecx,ecx
0xe817eeb  jmp short 0xE817F00
0xe817eed  nop [rax]
0xe817ef0  inc rcx
0xe817ef3  cmp rcx,0x400
0xe817efa  je 0xE818040
0xe817f00  cmp [rax+rcx*2],si
0xe817f04  jne short 0xE817EF0
0xe817f06  mov word ptr [rdi+rcx*2+0xC9BAA0],0xFFFF
0xe817f10  dec edx
0xe817f12  mov [rdi+0xC9AA9C],edx
0xe817f18  inc rcx
0xe817f1b  mov r11d,ecx
0xe817f1e  and r11d,0x3FF
0xe817f25  lea r10d,[r11+r11]
0xe817f29  movzx r9d,word ptr [rdi+r10+0xC9BAA0]
0xe817f32  cmp r9w,0xFFFF
0xe817f37  je short 0xE817EF3
0xe817f39  add r10,rax
0xe817f3c  mov r8d,ecx
0xe817f3f  and r8d,0x3FF
0xe817f46  jmp short 0xE817F88
0xe817f48  nop [rax+rax]
0xe817f50  mov [rdi+r14*4+0xC9AAA0],r11d
0xe817f58  mov [rdi+r14*2+0xC9BAA0],r9w
0xe817f61  mov [rdi+0xC9AA9C],edx
0xe817f67  inc r8d
0xe817f6a  and r8d,0x3FF
0xe817f71  lea r10,[rax+r8*2]
0xe817f75  movzx r9d,word ptr [rax+r8*2]
0xe817f7a  mov r11,r8
0xe817f7d  cmp r9w,0xFFFF
0xe817f82  je 0xE817EF3
0xe817f88  mov r11d,[rdi+r11*4+0xC9AAA0]
0xe817f90  imul ebx,r11d,0x5EBCA77
0xe817f97  shr ebx,0x13
0xe817f9a  imul ebx,0x1B1
0xe817fa0  and ebx,0x3FF
0xe817fa6  mov r14d,ebx
0xe817fa9  nop [rax]
0xe817fb0  mov r14d,r14d
0xe817fb3  cmp word ptr [rax+r14*2],0xFFFF
0xe817fb9  je short 0xE817FF0
0xe817fbb  cmp [rdi+r14*4+0xC9AAA0],r11d
0xe817fc3  je short 0xE817FE0
0xe817fc5  inc r14d
0xe817fc8  and r14d,0x3FF
0xe817fcf  cmp r14d,ebx
0xe817fd2  jne short 0xE817FB0
0xe817fd4  jmp short 0xE817FF0
0xe817fd6  nop [rax+rax]
0xe817fe0  cmp r8d,r14d
0xe817fe3  je short 0xE817F67
0xe817fe5  nop [rax+rax]
0xe817ff0  mov word ptr [r10],0xFFFF
0xe817ff6  lea r10d,[rdx-1]
0xe817ffa  mov [rdi+0xC9AA9C],r10d
0xe818001  mov r14d,ebx
0xe818004  nop [rax+rax]
0xe818010  mov r14d,r14d
0xe818013  cmp word ptr [rax+r14*2],0xFFFF
0xe818019  je 0xE817F50
0xe81801f  cmp [rdi+r14*4+0xC9AAA0],r11d
0xe818027  je short 0xE818038
0xe818029  inc r14d
0xe81802c  and r14d,0x3FF
0xe818033  cmp r14d,ebx
0xe818036  jne short 0xE818010
0xe818038  mov edx,r10d
0xe81803b  jmp 0xE817F67
0xe818040  add rsp,0x38
0xe818044  pop rbx
0xe818045  pop rdi
0xe818046  pop rsi
0xe818047  pop r12
0xe818049  pop r14
0xe81804b  pop r15
0xe81804d  ret
#endif

namespace native { namespace d3d12 {

// Layout assertions (authoritative copies live in sub_e817e50.h).
static_assert(kContextArrayEnd - kContextArrayBegin == 8, "context array is one pointer");
static_assert(kHandleMapCount == 0xC9AA9C, "count offset");
static_assert(kHandleMapKeys == 0xC9AAA0, "keys offset");
static_assert(kHandleMapHandles == 0xC9BAA0, "handles offset");
static_assert(kHandleMapCapacity == 0x400, "capacity");
static_assert(kValueSlotBase == 0x1250, "value slot base");

// Boundary thunk note (same mechanism as sub_e8141e0 / sub_bc75c30):
//   call qword ptr [0xF99FFA0]  ->  sub_eea6040, a "jmp rax" thunk.
// sub_eea6040 is classified vendor/boundary in docs/data/native_boundary.tsv
// (row "0xeea6040 vendor thunk via data slot 0xF99FFA0"). The caller first loads
// the real target into rax (rax = (*(rcx))->[+8] with rcx = *[0x12ADF800]); the
// thunk transfers control to that rax with the current registers, so the lifted
// code calls the loaded target directly with the same register arguments.

extern "C" void sub_e817e50(void* a0, unsigned short a1) {
    using boundary_fn = void (*)(void* rcx, void* rdx, void* r8, void* r9, void* s5, int s6);
    const std::uintptr_t base = RewriteRegistry::imageBase();
    char* const ctx = static_cast<char*>(a0);            // rdi
    const std::uint16_t handle = a1;                     // si

    // 0xe817e50..0xe817e7b : prologue, begin/end of the context pointer array,
    //   skip the loop when empty, r15 = zero-extended handle.
    char* rbx = *reinterpret_cast<char**>(ctx + kContextArrayBegin);   // 0xe817e62 mov rbx,[rcx+0x19F60]
    char* const rEnd = *reinterpret_cast<char**>(ctx + kContextArrayEnd); // 0xe817e69 mov r14,[rcx+0x19F68]
    if (rbx != rEnd) {                                   // 0xe817e70 cmp rbx,r14 ; 0xe817e73 je L_ed2
        const std::size_t slotOff = static_cast<std::size_t>(handle) * kValueSlotStride + kValueSlotBase; // r15*8+0x1250
        do {
            // 0xe817e80..0xe817ed0 : clear the value slot; before clearing, release
            //   the old pointer through the allocator vtable[1] thunk.
            void* r12 = *reinterpret_cast<void**>(rbx);                    // 0xe817e95 mov r12,[rbx]
            void* g = *reinterpret_cast<void**>(base + kAllocatorGlobal);  // 0xe817e98 mov rcx,[0x12ADF800]
            if (g != nullptr) {                                            // 0xe817e9f test rcx,rcx ; 0xe817ea2 je L_e80
                void* rdx = *reinterpret_cast<void**>(reinterpret_cast<char*>(r12) + slotOff); // 0xe817ea4 mov rdx,[r12+r15*8+0x1250]
                void* target = *reinterpret_cast<void**>(g);               // 0xe817eac mov rax,[rcx]
                target = *reinterpret_cast<void**>(reinterpret_cast<char*>(target) + 0x8); // 0xe817eaf mov rax,[rax+8]
                reinterpret_cast<boundary_fn>(target)(g, rdx, nullptr, nullptr, nullptr, 0); // 0xe817eca call qword ptr [0xF99FFA0]
            }
            *reinterpret_cast<void**>(reinterpret_cast<char*>(r12) + slotOff) = nullptr; // 0xe817e80 mov qword ptr [r12+r15*8+0x1250],0
            rbx += 8;                                                      // 0xe817e8c add rbx,8
        } while (rbx != rEnd);                                             // 0xe817e90 cmp rbx,r14 ; 0xe817e93 je L_ed2
    }

    // 0xe817ed2..0xe818040 : remove handle from the 0x400-entry open-addressing map
    //   (backward-shift deletion; identical algorithm to sub_bc75c30).
    //   0xe817ed2 cmp si,0xFFFF ; 0xe817ed6 je L_8040
    if (handle == kHandleEmpty) return;

    std::uint16_t* const handles = reinterpret_cast<std::uint16_t*>(ctx + kHandleMapHandles); // rax
    std::uint32_t* const keys    = reinterpret_cast<std::uint32_t*>(ctx + kHandleMapKeys);
    std::uint32_t* const pCount  = reinterpret_cast<std::uint32_t*>(ctx + kHandleMapCount);
    std::uint32_t edx = *pCount;                         // 0xe817ee3 mov edx,[rdi+0xC9AA9C]
    std::uint32_t ecx = 0;                               // 0xe817ee9 xor ecx,ecx
    std::uint32_t r8d = 0, r9d = 0, r11d = 0, ebx = 0, r14d = 0, r10d = 0;
    std::uint16_t* r10 = nullptr;                        // r10 = &handles[q]; r10d reuses the register later

    goto L_f00;
  L_ef0:                                                 // 0xe817ef0 inc rcx
    ++ecx;
  L_ef3:                                                 // 0xe817ef3 cmp rcx,0x400 ; 0xe817efa je L_8040
    if (ecx == kHandleMapCapacity) return;
  L_f00:                                                 // 0xe817f00 cmp [rax+rcx*2],si ; 0xe817f04 jne L_ef0
    if (handles[ecx] != handle) goto L_ef0;
    handles[ecx] = kHandleEmpty;                         // 0xe817f06 mov word ptr [rdi+rcx*2+0xC9BAA0],0xFFFF
    --edx;                                               // 0xe817f10 dec edx
    *pCount = edx;                                       // 0xe817f12 mov [rdi+0xC9AA9C],edx
    ++ecx;                                               // 0xe817f18 inc rcx
    r11d = ecx & kHashMask;                              // 0xe817f1b mov r11d,ecx ; 0xe817f1e and r11d,0x3FF
    r9d = handles[r11d];                                 // 0xe817f25 lea r10d,[r11+r11] ; 0xe817f29 movzx r9d,[rdi+r10+0xC9BAA0]
    if (r9d == kHandleEmpty) goto L_ef3;                 // 0xe817f32 cmp r9w,0xFFFF ; 0xe817f37 je L_ef3
    r10 = handles + r11d;                                // 0xe817f39 add r10,rax
    r8d = ecx & kHashMask;                               // 0xe817f3c mov r8d,ecx ; 0xe817f3f and r8d,0x3FF
    goto L_f88;                                          // 0xe817f46 jmp L_f88
  L_f67:                                                 // 0xe817f67 inc r8d ; 0xe817f6a and r8d,0x3FF
    r8d = (r8d + 1u) & kHashMask;
    r10 = handles + r8d;                                 // 0xe817f71 lea r10,[rax+r8*2]
    r9d = handles[r8d];                                  // 0xe817f75 movzx r9d,[rax+r8*2]
    r11d = r8d;                                          // 0xe817f7a mov r11,r8
    if (r9d == kHandleEmpty) goto L_ef3;                 // 0xe817f7d cmp r9w,0xFFFF ; 0xe817f82 je L_ef3
  L_f88:                                                 // 0xe817f88 mov r11d,[rdi+r11*4+0xC9AAA0]
    r11d = keys[r11d];                                   // v2 = keys[q]
    ebx = r11d * kHashMul1;                              // 0xe817f90 imul ebx,r11d,0x5EBCA77
    ebx >>= kHashShift;                                  // 0xe817f97 shr ebx,0x13
    ebx *= kHashMul2;                                    // 0xe817f9a imul ebx,0x1B1
    ebx &= kHashMask;                                    // 0xe817fa0 and ebx,0x3FF
    r14d = ebx;                                          // 0xe817fa6 mov r14d,ebx
  L_fb0:                                                 // 0xe817fb3 cmp word [rax+r14*2],0xFFFF ; 0xe817fb9 je L_ff0
    if (handles[r14d] == kHandleEmpty) goto L_ff0;
    if (keys[r14d] == r11d) goto L_fe0;                  // 0xe817fbb cmp [rdi+r14*4+0xC9AAA0],r11d ; 0xe817fc3 je L_fe0
    r14d = (r14d + 1u) & kHashMask;                      // 0xe817fc5 inc r14d ; 0xe817fc8 and r14d,0x3FF
    if (r14d == ebx) goto L_ff0;                         // 0xe817fcf cmp r14d,ebx ; 0xe817fd2 jne L_fb0
    goto L_fb0;
  L_fe0:                                                 // 0xe817fe0 cmp r8d,r14d ; 0xe817fe3 je L_f67
    if (r8d == r14d) goto L_f67;
  L_ff0:                                                 // 0xe817ff0 mov word ptr [r10],0xFFFF
    *r10 = kHandleEmpty;
    r10d = edx - 1u;                                     // 0xe817ff6 lea r10d,[rdx-1]
    *pCount = r10d;                                      // 0xe817ffa mov [rdi+0xC9AA9C],r10d
    r14d = ebx;                                          // 0xe818001 mov r14d,ebx
  L_8010:                                                // 0xe818013 cmp word [rax+r14*2],0xFFFF ; 0xe818019 je L_f50
    if (handles[r14d] == kHandleEmpty) goto L_f50;
    if (keys[r14d] == r11d) goto L_8038;                 // 0xe81801f cmp [rdi+r14*4+0xC9AAA0],r11d ; 0xe818027 je L_8038
    r14d = (r14d + 1u) & kHashMask;                      // 0xe818029 inc r14d ; 0xe81802c and r14d,0x3FF
    if (r14d != ebx) goto L_8010;                        // 0xe818033 cmp r14d,ebx ; 0xe818036 jne L_8010
  L_8038:                                                // 0xe818038 mov edx,r10d ; 0xe81803b jmp L_f67
    edx = r10d;
    goto L_f67;
  L_f50:                                                 // 0xe817f50 mov [rdi+r14*4+0xC9AAA0],r11d
    keys[r14d] = r11d;
    handles[r14d] = static_cast<std::uint16_t>(r9d);     // 0xe817f58 mov [rdi+r14*2+0xC9BAA0],r9w
    *pCount = edx;                                       // 0xe817f61 mov [rdi+0xC9AA9C],edx
    goto L_f67;                                          // fall into L_f67
    // 0xe818040..0xe81804d : epilogue (add rsp,0x38 ; pop rbx/rdi/rsi/r12/r14/r15 ; ret) - compiler.
}

} } // namespace native::d3d12

// Registry entry: NAME = Sigs.json symbol (sig anchors are appended at the milestone gate).
LIFT_FN(sub_e817e50, "RendererContextD3D12 base slot 43", 0xe817e50, sub_e817e50, nullptr);