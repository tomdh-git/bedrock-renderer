// LIFT 0xe81b4d0 size 0x24f 1.26.62.01 setVertexBuffers
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/setVertexBuffers.h"

#include <cstdint>
#include <intrin.h>

// Layout constants live in setVertexBuffers.h; the target model is x64 [V].
static_assert(sizeof(void*) == 8, "e81b4d0: x64 target");

namespace native {

namespace {

// 0xE951550: __security_check_cookie (crt boundary, noreturn on failure) [V],
// docs/data/native_boundary.tsv row 0xe951550 = crt. Called at 0xe81b719 with
// rcx = cookieStored ^ frame when the /GS cookie check at 0xe81b6f8 fails.
native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");

// The call at 0xe81b606 is `call qword ptr [0xF99FFA0]`. The cell at 0xF99FFA0 holds
// sub_eea6040 (docs/data/native_boundary.tsv: vendor thunk), whose single instruction
// is `jmp rax`; rax is preloaded from the command list's vtable slot 0xD0 just before
// the call (0xe81b5f5). So it is a guarded (CFG) virtual call to
// ID3D12GraphicsCommandList::ResourceBarrier; expressing it as the resolved vtable-slot
// invocation is exactly what the jmp-rax chain does.
// UNRESOLVED CALL = none: the only direct call (sub_e951550) is a crt boundary and the
// single indirect call is a CFG-guarded vtable call whose target slot is a D3D12 API.

} // namespace

extern "C" std::uint8_t setVertexBuffers(void* ctx, void* out, const void* draw, std::uint32_t* outNumVertices) {
    // 0xe81b4d0..0xe81b4ef: push 8 regs; sub rsp,0x58; mov [rsp+0x28],rcx;
    //   /GS: rax = [0x1230A0C0] ^ rsp; mov [rsp+0x50],rax.
    std::uintptr_t cookieSlot = 0;
    const std::uintptr_t cookieStored =
        *reinterpret_cast<std::uintptr_t*>(kGblCookie) ^ reinterpret_cast<std::uintptr_t>(&cookieSlot);

    char* const c = static_cast<char*>(ctx);
    char* const o = static_cast<char*>(out);
    const char* const d = static_cast<const char*>(draw);

    // Register images, declared up front so the goto-shaped control flow below matches
    // the original's branch layout without crossing any initialization.
    std::uint32_t eax_value = 0; // eax at the loop-continue point (0xe81b530)
    std::uint32_t mask = 0;      // ebp
    std::uint32_t idx = 0;       // r12d
    std::uint32_t tz = 0;        // ecx
    std::uint32_t numStreams = 0;// r15d (returned in r15b)
    std::uint32_t handle = 0;    // r13d
    char* g = nullptr;           // rsi/r11 = s_renderD3D12

    // 0xe81b4f4..0xe81b4f8: *outNumVertices = draw->numVertices (+0x4C)
    *outNumVertices = *reinterpret_cast<const std::uint32_t*>(d + kDrawNumVertices);
    // 0xe81b4fb movzx ebp,byte ptr [r8+0x63]
    mask = *reinterpret_cast<const std::uint8_t*>(d + kDrawStreamMask);
    // 0xe81b500..0xe81b50e: if (uint8_t(mask-1) > 0xFD) -> epilogue with numStreams = 0
    idx = 0;        // 0xe81b503 xor r12d,r12d
    numStreams = 0; // 0xe81b506 mov r15d,0
    if (static_cast<std::uint8_t>(mask - 1u) > kMaskEarlyOut)
        goto epilogue;
    // 0xe81b514..0xe81b524: r14=r9, rdi=r8, rbx=rdx; tz=tzcnt(mask); jmp loc_e81b547
    tz = _tzcnt_u32(mask); // 0xe81b51d tzcnt ecx,ebp
    goto loc_e81b547;

loc_e81b530: // 0xe81b530..0xe81b541: store the reduced vertex count, advance to the next set bit
    *outNumVertices = eax_value; // 0xe81b530 mov [r14],eax
    mask >>= 1;                  // 0xe81b533 shr ebp,1
    ++idx;                       // 0xe81b535 inc r12d
    tz = _tzcnt_u32(mask);       // 0xe81b538 tzcnt ecx,ebp
    ++numStreams;                // 0xe81b53c inc r15b
    if (mask == 0)               // 0xe81b53f test ebp,ebp ; 0xe81b541 je 0xE81B6E9
        goto epilogue;
    // fall through to loc_e81b547

loc_e81b547: // 0xe81b547..0xe81b563: pick the stream, read its handle, bail if above 0xFFF
    mask >>= tz;          // 0xe81b547 shr ebp,cl
    idx += tz;            // 0xe81b549 add r12d,ecx
    handle = *reinterpret_cast<const std::uint16_t*>(d + idx * kStreamStride + kStreamHandleOff); // 0xe81b54c movzx r13d,word ptr [rdi+r12*8+4]
    g = *reinterpret_cast<char**>(kGblRenderD3D12); // 0xe81b552 mov rsi,[0x12BB4910]
    if (handle > kHandleMax) // 0xe81b55c cmp r13d,0xFFF ; 0xe81b563 ja 0xE81B650
        goto loc_e81b650;

    // 0xe81b569..0xe81b5a3: read the per-handle "seen" bitmap bit.
    {
        const std::uint64_t bitmask = std::uint64_t(1) << (handle & 63); // 0xe81b57c..0xe81b585 shl r8,cl
        const std::uint64_t seen =
            *reinterpret_cast<const std::uint64_t*>(c + kVbTouchedBitmap + (handle >> 6) * 8); // 0xe81b574
        if ((seen & (std::uint64_t(1) << (handle & 63))) == 0) // 0xe81b588 bt rdx,r13 ; 0xe81b58c jae 0xE81B615
            goto loc_e81b615;
        // 0xe81b592..0xe81b5a3: already seen; transition to GENERIC_READ unless already there.
        const std::uint32_t before =
            *reinterpret_cast<const std::uint32_t*>(c + kVbState + handle * kVbStateStride + kVbStateCurrentOff); // 0xe81b592 (+0xA45C)
        if (before == kGenericRead) // 0xe81b59d cmp edx,0xAC3 ; 0xe81b5a3 je 0xE81B650
            goto loc_e81b650;
        // 0xe81b5a9..0xe81b5b2: state.current = GENERIC_READ
        *reinterpret_cast<std::uint32_t*>(c + kVbState + handle * kVbStateStride + kVbStateCurrentOff) = kGenericRead;
        // 0xe81b5be..0xe81b5cc: resource = ctx->m_vbResources[handle]
        void* const commandList = *reinterpret_cast<void**>(c + kCommandList); // 0xe81b5ae [rax+0x30]
        char* const resources = *reinterpret_cast<char**>(c + kVbResources);   // 0xe81b5be [rax+0xA248]
        void* const resource = *reinterpret_cast<void**>(resources + handle * kVbResourceStride); // 0xe81b5cc
        // 0xe81b5d0..0xe81b5ea: build the D3D12_RESOURCE_BARRIER on the stack.
        ResourceBarrier barrier;
        barrier.type = 0;                        // 0xe81b5d0 qword 0 (type + flags)
        barrier.flags = 0;
        barrier.pResource = resource;            // 0xe81b5d9 [rsp+0x38]
        barrier.subresource = kAllSubresources;  // 0xe81b5de [rsp+0x40]
        barrier.stateBefore = before;            // 0xe81b5e6 [rsp+0x44]
        barrier.stateAfter = kGenericRead;       // 0xe81b5ea [rsp+0x48]
        // 0xe81b5f2..0xe81b606: CFG-guarded virtual call commandList->vtable[0xD0](commandList,1,&barrier)
        void** const vtbl = *reinterpret_cast<void***>(commandList);          // 0xe81b5f2 mov rax,[rcx]
        void* const target = vtbl[kVslotResourceBarrier / 8];                 // 0xe81b5f5 mov rax,[rax+0xD0]
        reinterpret_cast<void (*)(void*, std::uint32_t, void*)>(target)(       // 0xe81b5fc mov edx,1 ; 0xe81b601 lea r8 ; 0xe81b606 call qword ptr [0xF99FFA0]
            commandList, 1u, &barrier);
        // 0xe81b60c mov rax,[0x12BB4910] ; 0xe81b613 jmp 0xE81B650
        g = *reinterpret_cast<char**>(kGblRenderD3D12);
        goto loc_e81b650;
    }

loc_e81b615: // 0xe81b615..0xe81b64d: first touch -> mark seen, record the handle, seed both states
    *reinterpret_cast<std::uint64_t*>(c + kVbTouchedBitmap + (handle >> 6) * 8) =
        *reinterpret_cast<std::uint64_t*>(c + kVbTouchedBitmap + (handle >> 6) * 8) |
        (std::uint64_t(1) << (handle & 63)); // 0xe81b615 or rdx,r8 ; 0xe81b618 mov [r9+rax*8+0xA258],rdx
    {
        const std::uint16_t count = *reinterpret_cast<std::uint16_t*>(c + kVbTouchedCount); // 0xe81b620 movzx eax,word ptr [r9+0xA250]
        *reinterpret_cast<std::uint16_t*>(c + kVbTouchedList + std::size_t(count) * 2) =
            static_cast<std::uint16_t>(handle); // 0xe81b628 mov [r9+rax*2+0x12458],r13w
        *reinterpret_cast<std::uint16_t*>(c + kVbTouchedCount) =
            static_cast<std::uint16_t>(count + 1); // 0xe81b631 inc eax ; 0xe81b633 mov [r9+0xA250],ax
    }
    *reinterpret_cast<std::uint64_t*>(c + kVbState + handle * kVbStateStride) = kPairGenericRead; // 0xe81b63b..0xe81b645 mov [r9+r13*8+0xA458],rax
    // 0xe81b64d mov rax,rsi (g already = s_renderD3D12)

loc_e81b650: // 0xe81b650..0xe81b6b4: build out[numStreams] = {gpuVA+startVertex*stride, size-startVertex*stride, stride}
    {
        const char* const stream = d + idx * kStreamStride; // 0xe81b650 lea rdx,[rdi+r12*8]
        char* const vb = g + handle * kVertexBufferStride + kVertexBuffers; // 0xe81b654..0xe81b65c
        // 0xe81b663..0xe81b674: layout = (vb->layoutHandle != 0xFFFF) ? vb->layoutHandle : stream->layoutHandle
        const std::uint16_t vbLayout =
            *reinterpret_cast<const std::uint16_t*>(vb + kVbLayoutHandle); // 0xe81b663 cmp word ptr [rcx+0x78],0xFFFF
        const std::uint16_t layout =
            (vbLayout != 0xFFFF)
                ? vbLayout
                : *reinterpret_cast<const std::uint16_t*>(stream + kStreamLayoutOff); // 0xe81b66a lea r8,[rcx+0x78] / 0xe81b670 lea r8,[rdx+6]
        // 0xe81b674..0xe81b67c: stride = s_renderD3D12->m_vertexLayouts[layout].stride (u16 at +0xC9619C)
        const std::uint32_t stride = *reinterpret_cast<const std::uint16_t*>(
            g + std::size_t(layout) * kVertexLayoutStride + kVertexLayouts + kVertexLayoutStrideOff); // 0xe81b67c
        const std::uint32_t startVertex = *reinterpret_cast<const std::uint32_t*>(stream); // 0xe81b689 mov r11d,[rdx]
        const std::uint32_t startOffset = startVertex * stride; // 0xe81b68c imul r11d,r8d
        const std::uint64_t gpuVA =
            *reinterpret_cast<const std::uint64_t*>(vb + kVbGpuVA) + startOffset; // 0xe81b690 add r11,[rcx+0x58]
        const std::uint32_t n16 = numStreams << 4; // 0xe81b685 movzx r10d,r15b ; 0xe81b694 shl r10d,4
        *reinterpret_cast<std::uint64_t*>(o + n16 + kVbvBufferLocation) = gpuVA; // 0xe81b698 mov [rbx+r10],r11
        const std::uint32_t stride2 = *reinterpret_cast<const std::uint16_t*>(
            g + std::size_t(layout) * kVertexLayoutStride + kVertexLayouts + kVertexLayoutStrideOff); // 0xe81b69c
        *reinterpret_cast<std::uint32_t*>(o + n16 + kVbvStrideInBytes) = stride2; // 0xe81b6a4 mov [rbx+r10+0xC],eax
        const std::uint32_t size = *reinterpret_cast<const std::uint32_t*>(vb + kVbSize); // 0xe81b6a9 mov eax,[rcx+0x60]
        const std::uint32_t used = startVertex * stride; // 0xe81b6ac..0xe81b6ae mov edx,[rdx] ; imul edx,r8d
        *reinterpret_cast<std::uint32_t*>(o + n16 + kVbvSizeInBytes) = size - used; // 0xe81b6b2 sub eax,edx ; 0xe81b6b4
        // 0xe81b6b9..0xe81b6e4: numVertices = min(current, (numVertices==0xFFFFFFFF)? size/stride : numVertices)
        const std::uint32_t cur = *outNumVertices; // 0xe81b6b9 mov r10d,[r14]
        const std::uint32_t nv = *reinterpret_cast<const std::uint32_t*>(d + kDrawNumVertices); // 0xe81b6bc mov eax,[rdi+0x4C]
        std::uint32_t candidate; // eax
        if (nv == kAllSubresources) // 0xe81b6bf cmp eax,0xFFFFFFFF ; 0xe81b6c2 je 0xE81B6D0
            candidate = size / stride; // 0xe81b6d0..0xe81b6d5 mov eax,[rcx+0x60] ; div r8d
        else
            candidate = nv;
        eax_value = (candidate < cur) ? candidate : cur; // 0xe81b6c4/0xe81b6c7/0xe81b6cd + 0xe81b6d8/0xe81b6db + 0xe81b6e1
        goto loc_e81b530; // 0xe81b6e4 jmp 0xE81B530
    }

epilogue: // 0xe81b6e9..0xe81b710: /GS cookie check, then return r15b
    if (*reinterpret_cast<std::uintptr_t*>(kGblCookie) !=
        (cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot))) { // 0xe81b6f8 cmp rcx,rax ; 0xe81b6fb jne 0xE81B711
        // 0xe81b711..0xe81b71e: cookie mismatch -> __security_check_cookie (noreturn)
        sub_e951550(cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot)); // 0xe81b719 call 0xE951550
        __assume(false); // 0xe81b71e int3 (unreachable)
    }
    return static_cast<std::uint8_t>(numStreams); // 0xe81b6fd mov eax,r15d
}

// Verbatim disassembly of [0xe81b4d0, 0xe81b71f) (rdis dis output; two spaces after
// each address, trailing "; ..." annotations omitted):
#if 0
0xe81b4d0  push r15
0xe81b4d2  push r14
0xe81b4d4  push r13
0xe81b4d6  push r12
0xe81b4d8  push rsi
0xe81b4d9  push rdi
0xe81b4da  push rbp
0xe81b4db  push rbx
0xe81b4dc  sub rsp,0x58
0xe81b4e0  mov [rsp+0x28],rcx
0xe81b4e5  mov rax,[0x1230A0C0]
0xe81b4ec  xor rax,rsp
0xe81b4ef  mov [rsp+0x50],rax
0xe81b4f4  mov eax,[r8+0x4C]
0xe81b4f8  mov [r9],eax
0xe81b4fb  movzx ebp,byte ptr [r8+0x63]
0xe81b500  lea eax,[rbp-1]
0xe81b503  xor r12d,r12d
0xe81b506  mov r15d,0
0xe81b50c  cmp al,0xFD
0xe81b50e  ja 0xE81B6E9
0xe81b514  mov r14,r9
0xe81b517  mov rdi,r8
0xe81b51a  mov rbx,rdx
0xe81b51d  tzcnt ecx,ebp
0xe81b521  xor r15d,r15d
0xe81b524  jmp short 0xE81B547
0xe81b526  nop [rax+rax]
0xe81b530  mov [r14],eax
0xe81b533  shr ebp,1
0xe81b535  inc r12d
0xe81b538  tzcnt ecx,ebp
0xe81b53c  inc r15b
0xe81b53f  test ebp,ebp
0xe81b541  je 0xE81B6E9
0xe81b547  shr ebp,cl
0xe81b549  add r12d,ecx
0xe81b54c  movzx r13d,word ptr [rdi+r12*8+4]
0xe81b552  mov rsi,[0x12BB4910]
0xe81b559  mov rax,rsi
0xe81b55c  cmp r13d,0xFFF
0xe81b563  ja 0xE81B650
0xe81b569  mov eax,r13d
0xe81b56c  shr eax,6
0xe81b56f  mov r9,[rsp+0x28]
0xe81b574  mov rdx,[r9+rax*8+0xA258]
0xe81b57c  mov r8d,1
0xe81b582  mov ecx,r13d
0xe81b585  shl r8,cl
0xe81b588  bt rdx,r13
0xe81b58c  jae 0xE81B615
0xe81b592  mov edx,[r9+r13*8+0xA45C]
0xe81b59a  mov rax,rsi
0xe81b59d  cmp edx,0xAC3
0xe81b5a3  je 0xE81B650
0xe81b5a9  mov rax,[rsp+0x28]
0xe81b5ae  mov rcx,[rax+0x30]
0xe81b5b2  mov dword ptr [rax+r13*8+0xA45C],0xAC3
0xe81b5be  mov rax,[rax+0xA248]
0xe81b5c5  mov r8d,r13d
0xe81b5c8  shl r8d,7
0xe81b5cc  mov rax,[rax+r8]
0xe81b5d0  mov qword ptr [rsp+0x30],0
0xe81b5d9  mov [rsp+0x38],rax
0xe81b5de  mov dword ptr [rsp+0x40],0xFFFFFFFF
0xe81b5e6  mov [rsp+0x44],edx
0xe81b5ea  mov dword ptr [rsp+0x48],0xAC3
0xe81b5f2  mov rax,[rcx]
0xe81b5f5  mov rax,[rax+0xD0]
0xe81b5fc  mov edx,1
0xe81b601  lea r8,[rsp+0x30]
0xe81b606  call qword ptr [0xF99FFA0]
0xe81b60c  mov rax,[0x12BB4910]
0xe81b613  jmp short 0xE81B650
0xe81b615  or rdx,r8
0xe81b618  mov [r9+rax*8+0xA258],rdx
0xe81b620  movzx eax,word ptr [r9+0xA250]
0xe81b628  mov [r9+rax*2+0x12458],r13w
0xe81b631  inc eax
0xe81b633  mov [r9+0xA250],ax
0xe81b63b  mov rax,0xAC300000AC3
0xe81b645  mov [r9+r13*8+0xA458],rax
0xe81b64d  mov rax,rsi
0xe81b650  lea rdx,[rdi+r12*8]
0xe81b654  shl r13d,7
0xe81b658  lea rcx,[rsi+r13]
0xe81b65c  add rcx,0x9B2178
0xe81b663  cmp word ptr [rcx+0x78],0xFFFF
0xe81b668  je short 0xE81B670
0xe81b66a  lea r8,[rcx+0x78]
0xe81b66e  jmp short 0xE81B674
0xe81b670  lea r8,[rdx+6]
0xe81b674  movzx r8d,word ptr [r8]
0xe81b678  imul rsi,r8,0x54
0xe81b67c  movzx r8d,word ptr [rax+rsi+0xC9619C]
0xe81b685  movzx r10d,r15b
0xe81b689  mov r11d,[rdx]
0xe81b68c  imul r11d,r8d
0xe81b690  add r11,[rcx+0x58]
0xe81b694  shl r10d,4
0xe81b698  mov [rbx+r10],r11
0xe81b69c  movzx eax,word ptr [rax+rsi+0xC9619C]
0xe81b6a4  mov [rbx+r10+0xC],eax
0xe81b6a9  mov eax,[rcx+0x60]
0xe81b6ac  mov edx,[rdx]
0xe81b6ae  imul edx,r8d
0xe81b6b2  sub eax,edx
0xe81b6b4  mov [rbx+r10+8],eax
0xe81b6b9  mov r10d,[r14]
0xe81b6bc  mov eax,[rdi+0x4C]
0xe81b6bf  cmp eax,0xFFFFFFFF
0xe81b6c2  je short 0xE81B6D0
0xe81b6c4  cmp eax,r10d
0xe81b6c7  jb 0xE81B530
0xe81b6cd  jmp short 0xE81B6E1
0xe81b6cf  nop
0xe81b6d0  mov eax,[rcx+0x60]
0xe81b6d3  xor edx,edx
0xe81b6d5  div r8d
0xe81b6d8  cmp eax,r10d
0xe81b6db  jb 0xE81B530
0xe81b6e1  mov eax,r10d
0xe81b6e4  jmp 0xE81B530
0xe81b6e9  mov rax,[rsp+0x50]
0xe81b6ee  xor rax,rsp
0xe81b6f1  mov rcx,[0x1230A0C0]
0xe81b6f8  cmp rcx,rax
0xe81b6fb  jne short 0xE81B711
0xe81b6fd  mov eax,r15d
0xe81b700  add rsp,0x58
0xe81b704  pop rbx
0xe81b705  pop rbp
0xe81b706  pop rdi
0xe81b707  pop rsi
0xe81b708  pop r12
0xe81b70a  pop r13
0xe81b70c  pop r14
0xe81b70e  pop r15
0xe81b710  ret
0xe81b711  mov rcx,[rsp+0x50]
0xe81b716  xor rcx,rsp
0xe81b719  call 0xE951550
0xe81b71e  int3
#endif

LIFT_FN(e81b4d0, "setVertexBuffers", 0xE81B4D0, setVertexBuffers, nullptr);

} // namespace native