// LIFT 0xbc6a9d0 size 0x200 1.26.62.01 rendererUpdateUniforms
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/rendererUpdateUniforms.h"

#include <algorithm>
#include <cstddef>
#include <cstring>

// Reversed from the disassembly of [0xbc6a9d0, 0xbc6abd0), Minecraft Windows 1.26.62.01
// (rdis dis output). Every block carries the instruction range it implements as
// // 0xA..0xB beside it; every call is quoted verbatim (two spaces after the address)
// beside the statement it implements and in the verbatim call log below.
//
// Argument map (x64 MSVC ABI) [V]:
//   rcx = renderer (RendererContextI*), rdx = ub (UniformBuffer*),
//   r8d = begin (uint32_t), r9d = end (uint32_t),
//   caller stack +0x20 = touched (std::vector<uint16_t>*, 5th arg, may be null),
//   caller stack +0x28 = ctx (void*, 6th arg, per-job D3D12 context).
//   Seen at 0xbc6a9e0..0xbc6a9ec: mov r15d,r9d / mov edi,r8d / mov rbx,rdx /
//   mov r14,rcx / mov rcx,[rsp+0xA0]. Stack frame 0x38, no cookie, no saved xmm.
//
// Verbatim call log (rdis dis output, two spaces after the address):
//   0xbc6aa3b  call qword ptr [0xF99FFA0]   ; tail call via sub_eea6040 (jmp rax) = renderer->setMarker, vtable slot 47
//   0xbc6aa5d  call 0xEBCE390              ; memcpy(&op, ub->data + pos, 4)
//   0xbc6ab2f  call 0xEEC6DE0              ; memmove shift in the touched-vector insert
//   0xbc6ab45  call 0x74C9C0                ; boundary, class stl: touched->insert-with-growth
//   0xbc6abaf  call qword ptr [0xF99FFA0]   ; tail call via sub_eea6040 (jmp rax) = renderer->updateUniform, vtable slot 46
//
// [0xF99FFA0] holds sub_eea6040, a 5-byte jmp rax tail-call trampoline
// (docs/progress/pre/0xEEA6040.md); the compiler loads the renderer vtable slot
// ([rax+0x170] / [rax+0x178]) into rax before each tail call, so these two call
// sites are the renderer virtuals updateUniform (slot 46) and setMarker (slot 47).
// 0xEBCE390 is a tail-forwarder to sub_eec6ec0 (memcpy: rcx=dst, rdx=src, r8=count);
// 0xEEC6DE0 is memmove (rcx=dst, rdx=src, r8=count). Both are compiler library
// intrinsics called with the same argument registers as memcpy/memmove.

// Layout assertions (full set in rendererUpdateUniforms.h; repeated here so liftcheck sees them).
static_assert(offsetof(native::Uniform16Vector, first) == 0x00, "rendererUpdateUniforms: vector first at +0x00");
static_assert(offsetof(native::Uniform16Vector, last) == 0x08, "rendererUpdateUniforms: vector last at +0x08");
static_assert(offsetof(native::Uniform16Vector, end_storage) == 0x10, "rendererUpdateUniforms: vector end_storage at +0x10");
static_assert(sizeof(native::Uniform16Vector) == 0x18, "rendererUpdateUniforms: vector size 0x18");
static_assert(offsetof(native::UniformBuffer, size) == 0x00, "rendererUpdateUniforms: UniformBuffer size at +0x00");
static_assert(offsetof(native::UniformBuffer, pos) == 0x04, "rendererUpdateUniforms: UniformBuffer pos at +0x04");
static_assert(sizeof(native::UniformBuffer) == 0x08, "rendererUpdateUniforms: UniformBuffer data at +0x08");
static_assert(46 * 8 == 0x170, "rendererUpdateUniforms: updateUniform vtable slot at +0x170");
static_assert(47 * 8 == 0x178, "rendererUpdateUniforms: setMarker vtable slot at +0x178");

namespace native::bgfx {

void rendererUpdateUniforms(RendererContextI* renderer, UniformBuffer* ub, uint32_t begin, uint32_t end,
                            std::vector<uint16_t>* touched, void* ctx) {
    // 0xbc6a9d0..0xbc6aa06: prologue, then touched->clear() when touched != null
    //   0xbc6a9d0  push r15
    //   0xbc6a9d2  push r14
    //   0xbc6a9d4  push r13
    //   0xbc6a9d6  push r12
    //   0xbc6a9d8  push rsi
    //   0xbc6a9d9  push rdi
    //   0xbc6a9da  push rbp
    //   0xbc6a9db  push rbx
    //   0xbc6a9dc  sub rsp,0x38
    //   0xbc6a9e0  mov r15d,r9d      ; end
    //   0xbc6a9e3  mov edi,r8d       ; begin
    //   0xbc6a9e6  mov rbx,rdx       ; ub
    //   0xbc6a9e9  mov r14,rcx       ; renderer
    //   0xbc6a9ec  mov rcx,[rsp+0xA0]; touched (5th stack arg)
    //   0xbc6a9f4  test rcx,rcx
    //   0xbc6a9f7  je short 0xBC6AA06
    //   0xbc6a9f9  mov rax,[rcx]     ; touched->first
    //   0xbc6a9fc  cmp rax,[rcx+8]   ; touched->last
    //   0xbc6aa00  je short 0xBC6AA06
    //   0xbc6aa02  mov [rcx+8],rax   ; touched->last = touched->first
    Uniform16Vector* v = nullptr;
    if (touched != 0) {
        v = reinterpret_cast<Uniform16Vector*>(touched);
        v->last = v->first; // 0xbc6aa02  mov [rcx+8],rax
    }

    // 0xbc6aa06  cmp edi,r15d  ; pos >= end -> exit  (loop-entry test and back-edge test)
    // 0xbc6aa09  jae 0xBC6ABBF
    uint8_t* const ubData = reinterpret_cast<uint8_t*>(ub) + kUniformBufferDataOffset; // rbx = ub + 0x08 (0xbc6aa0f)
    uint32_t pos = begin;
    const uint32_t endLimit = end;
    for (;;) {
        // 0xbc6aa06  cmp edi,r15d
        // 0xbc6aa09  jae 0xBC6ABBF
        if (pos >= endLimit) break;

        // 0xbc6aa0f  add rbx,8                 (ubData above)
        // 0xbc6aa13  lea r13,[rsp+0x2C]        ; op scratch
        // 0xbc6aa18  mov [rsp+0x34],r15d       ; save end
        // 0xbc6aa1d  jmp short 0xBC6AA4F
        // 0xbc6aa1f  nop
        // 0xbc6aa4f  mov edx,edi               ; pos
        // 0xbc6aa51  add rdx,rbx               ; &ub->data[pos]
        // 0xbc6aa54  mov r8d,4
        // 0xbc6aa5a  mov rcx,r13               ; &op
        // 0xbc6aa5d  call 0xEBCE390            ; memcpy(&op, ub->data + pos, 4)
        uint32_t op;
        std::memcpy(&op, ubData + pos, 4);

        // 0xbc6aa62  mov ebp,[rsp+0x2C]   ; ebp = op
        // 0xbc6aa66  cmp rbp,1
        // 0xbc6aa6a  je 0xBC6ABBF         ; op == 1 (UniformType::End) -> exit loop
        if (op == 1u) break;

        // 0xbc6aa70  lea r12d,[rdi+4]     ; r12d = pos + 4
        // 0xbc6aa74  mov esi,ebp
        // 0xbc6aa76  shr esi,1
        // 0xbc6aa78  and esi,0x3FF        ; count field = (op >> 1) & 0x3FF
        // 0xbc6aa7e  mov eax,ebp
        // 0xbc6aa80  shr eax,0x1B         ; type = op >> 27
        // 0xbc6aa83  lea rcx,[0xF441930]  ; read-only size table {4, 0, 16, 36, 64}
        // 0xbc6aa8a  imul esi,[rcx+rax*4] ; size = countField * kUniformTypeSize[type]
        // 0xbc6aa8e  add r12,rbx          ; r12 = ub->data + pos + 4 (payload pointer)
        // 0xbc6aa91  cmp ebp,0x27FFFFFF
        // 0xbc6aa97  ja short 0xBC6AA20   ; op > 0x27FFFFFF -> marker op
        const uint8_t* const payload = ubData + pos + 4;
        const uint32_t countField = ((op >> 1) & 0x3FFu);
        const uint32_t type = op >> 27;
        const uint32_t size = countField * kUniformTypeSize[type];
        if (op > kMaxUniformOp) {
            // 0xbc6aa20..0xbc6aa3b: marker op -> renderer->setMarker(ctx, payload, size)
            //   0xbc6aa20  mov rax,[r14]          ; renderer object
            //   0xbc6aa23  mov rax,[rax+0x178]    ; slot 47 (setMarker) -> rax
            //   0xbc6aa2a  mov rcx,r14            ; this
            //   0xbc6aa2d  mov rdx,[rsp+0xA8]     ; ctx (6th stack arg)
            //   0xbc6aa35  mov r8,r12             ; data = payload
            //   0xbc6aa38  mov r9d,esi            ; size
            //   0xbc6aa3b  call qword ptr [0xF99FFA0]   ; tail call via jmp-rax trampoline (sub_eea6040)
            renderer->setMarker(ctx, payload, size);
            // 0xbc6abb5  lea r13,[rsp+0x2C]
            // 0xbc6abba  jmp 0xBC6AA41            ; loop increment (shared below)
        } else {
            // 0xbc6aa99..0xbc6ab60: record handle in touched (sorted, unique)
            //   0xbc6aa99  mov r13d,ebp
            //   0xbc6aa9c  shr r13d,0xB         ; handle = op >> 11
            //   0xbc6aaa0  mov r10,[rsp+0xA0]   ; touched
            //   0xbc6aaa8  test r10,r10
            //   0xbc6aaab  je 0xBC6AB65         ; touched == null -> skip recording
            //   0xbc6aab1  mov [rsp+0x32],r13w  ; spill handle
            const uint16_t handle = static_cast<uint16_t>(op >> 11);
            uint16_t handleSlot = handle; // [rsp+0x32]
            if (touched != 0) {
                uint16_t* const first = v->first;       // 0xbc6aab7  mov r15,[r10]
                uint16_t* last = v->last;               // 0xbc6aaba  mov rcx,[r10+8]
                uint16_t* const cap = v->end_storage;   // 0xbc6ab0b  cmp rcx,[r10+0x10]

                // 0xbc6aabe..0xbc6aafe: lower_bound in 2-byte elements over [first, last)
                //   byte offsets; first element >= handle
                //   0xbc6aabe  mov rax,rcx
                //   0xbc6aac1  sub rax,r15
                //   0xbc6aac4  sar rax,1
                //   0xbc6aac7  test rax,rax
                //   0xbc6aaca  jle short 0xBC6AB00
                //   0xbc6aacc  nop [rax]
                //   0xbc6aad0  mov rdx,r15
                //   0xbc6aad3  mov r8,rax
                //   0xbc6aad6  shr r8,1
                //   0xbc6aad9  mov r9,r8
                //   0xbc6aadc  not r9
                //   0xbc6aadf  add r9,rax
                //   0xbc6aae2  and rax,0xFFFFFFFFFFFFFFFE
                //   0xbc6aae6  cmp [r15+rax],r13w
                //   0xbc6aaeb  lea r15,[r15+rax+2]
                //   0xbc6aaf0  cmovae r15,rdx
                //   0xbc6aaf4  cmovae r9,r8
                //   0xbc6aaf8  mov rax,r9
                //   0xbc6aafb  test r9,r9
                //   0xbc6aafe  jg short 0xBC6AAD0
                uint16_t* ip = std::lower_bound(first, last, handle);

                // 0xbc6ab00  cmp rcx,r15           ; ip == last?
                // 0xbc6ab03  je short 0xBC6AB0B
                // 0xbc6ab05  cmp [r15],r13w        ; *ip <= handle -> duplicate
                // 0xbc6ab09  jbe short 0xBC6AB60
                if (ip < last && *ip <= handle) {
                    // duplicate: nothing written, 0xbc6ab60  mov r15d,[rsp+0x34]
                } else {
                    // 0xbc6ab0b  cmp rcx,[r10+0x10] ; last == cap -> growth needed
                    // 0xbc6ab0f  je short 0xBC6AB3A
                    if (last == cap) {
                        // 0xbc6ab3a  mov rcx,r10       ; vec
                        // 0xbc6ab3d  mov rdx,r15       ; position = ip
                        //   0xbc6ab40  lea r8,[rsp+0x32] ; &handle
                        //   0xbc6ab45  call 0x74C9C0     ; boundary (class stl)
                        native::sub_74c9c0(v, ip, &handleSlot);
                    } else if (ip == last) {
                        // 0xbc6ab11  cmp rcx,r15       ; last == ip -> append
                        //   0xbc6ab4c  mov [rcx],r13w    ; *last = handle
                        //   0xbc6ab50  add qword ptr [r10+8],2 ; last += 2 bytes
                        //   0xbc6ab55  nop [rax+rax]
                        *last = handle;    // 0xbc6ab4c  mov [rcx],r13w
                        v->last = last + 1;// 0xbc6ab50  add qword ptr [r10+8],2
                    } else {
                        // 0xbc6ab16..0xbc6ab38: shift [ip, last) right by one element,
                        //   pre-writing the vacated last slot, then store handle at ip
                        //   0xbc6ab16  movzx eax,word ptr [rcx-2] ; *last = *(last - 1)
                        //   0xbc6ab1a  mov [rcx],ax
                        //   0xbc6ab1d  add qword ptr [r10+8],2  ; last += 2 bytes (memory)
                        //   0xbc6ab22  lea r8,[rcx-2]
                        //   0xbc6ab26  sub r8,r15               ; count = (last - 2 - ip) bytes
                        //   0xbc6ab29  sub rcx,r8               ; dst = ip + 1 element
                        //   0xbc6ab2c  mov rdx,r15              ; src = ip
                        //   0xbc6ab2f  call 0xEEC6DE0            ; memmove(ip + 1, ip, count)
                        //   0xbc6ab34  mov [r15],r13w           ; *ip = handle
                        // 0xbc6ab2f  call 0xEEC6DE0
                        uint16_t* const oldLast = last;
                        *oldLast = *(oldLast - 1); // 0xbc6ab16  movzx eax,word ptr [rcx-2]
                                                   // 0xbc6ab1a  mov [rcx],ax
                        v->last = oldLast + 1;     // 0xbc6ab1d  add qword ptr [r10+8],2
                        std::memmove(ip + 1, ip,
                                     (size_t)((uint8_t*)oldLast - (uint8_t*)ip - 2));
                        *ip = handle;              // 0xbc6ab34  mov [r15],r13w
                    }
                }
                // 0xbc6ab60  mov r15d,[rsp+0x34] ; restore end (endLimit unchanged)
            }

            // 0xbc6ab65  test bpl,1             ; op & 1 (bpl = low byte of op)
            // 0xbc6ab69  jne short 0xBC6AB90    ; op&1 == 1 -> inline source bytes
            // 0xbc6ab6b  mov r9,[r12]           ; op&1 == 0 -> source is the pointer stored inline
            const void* src = (op & 1u) ? payload
                                        : *reinterpret_cast<const void* const*>(payload);

            // 0xbc6ab6f..0xbc6abaf: renderer->updateUniform(ctx, handle, src, size)
            //   0xbc6ab6f  mov rax,[r14]          ; renderer object
            //   0xbc6ab72  mov rax,[rax+0x170]    ; slot 46 (updateUniform) -> rax
            //   0xbc6ab79  mov [rsp+0x20],esi     ; spill size
            //   0xbc6ab7d  mov rcx,r14            ; this
            //   0xbc6ab80  mov rdx,[rsp+0xA8]     ; ctx
            //   0xbc6ab88  mov r8d,r13d           ; handle
            //   0xbc6abac  mov r9,r12             ; data = src
            //   0xbc6abaf  call qword ptr [0xF99FFA0]   ; tail call via jmp-rax trampoline (sub_eea6040)
            renderer->updateUniform(ctx, handle, src, size);
            // 0xbc6abb5  lea r13,[rsp+0x2C]
            // 0xbc6abba  jmp 0xBC6AA41            ; loop increment (shared below)
        }

        // 0xbc6aa41  add edi,esi        ; pos += size
        // 0xbc6aa43  add edi,4          ; pos += 4 (op size)
        // 0xbc6aa46  cmp edi,r15d
        // 0xbc6aa49  jae 0xBC6ABBF      ; pos >= end -> exit
        pos += size + 4u;
    }
    // 0xbc6abbf..0xbc6abcf: epilogue
    //   0xbc6abbf  add rsp,0x38
    //   0xbc6abc3  pop rbx
    //   0xbc6abc4  pop rbp
    //   0xbc6abc5  pop rdi
    //   0xbc6abc6  pop rsi
    //   0xbc6abc7  pop r12
    //   0xbc6abc9  pop r13
    //   0xbc6abcb  pop r14
    //   0xbc6abcd  pop r15
    //   0xbc6abcf  ret
}

LIFT_FN(rendererUpdateUniforms, "updateUniforms", 0xbc6a9d0, rendererUpdateUniforms, nullptr);

} // namespace native::bgfx
