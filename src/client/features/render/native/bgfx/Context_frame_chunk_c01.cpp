// LIFT 0xbc66de0 size 0x19d7 1.26.62.01 bgfx::Context::frame
// CHUNK 0xbc685af..0xbc687b7
// Unit U-EX1.bc66de0.c01 -- chunk 2/2 (handle-alloc-B + frame-swap/handoff + epilogue)
// Static inline step function; live state in ContextFrameChunkC01State (docs/functions/bc66de0.md 'Chunk state').
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/Context_frame_chunk_c01.h"

#include <cstdint>
#include <cstring>

#if 0
0xbc685c0  call 0xEBCE650
0xbc68633  call 0xEBDBF20
0xbc686cc  call 0xEBCE430
0xbc68781  call qword ptr [0xF99FFA0]
0xbc687a0  call 0xEBCE430
#endif

namespace native { namespace bgfx {

namespace {

// Vendor boundary thunk via data slot 0xF99FFA0 -> sub_eea6040 (loader-resolved). The slot holds a "jmp rax"
// trampoline; the caller (0xbc68766..0xbc68769) loads the vtable function into rax first.
inline void* eea6040_call(void* alloc, void* oldBuf, uint64_t size, uint64_t align, uint64_t s0, uint64_t s1) {
    using Fn = void* (*)(void*, void*, uint64_t, uint64_t, uint64_t, uint64_t);
    Fn fn = reinterpret_cast<Fn>(*reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF99FFA0));
    return fn(alloc, oldBuf, size, align, s0, s1);
}

} // namespace

// Forward declaration for the step function
void Context_frame_chunk_c01_step(ContextFrameChunkC01State* state);

// LIFT_FN registration for the main function (chunk 2/2 of 0xbc66de0)
LIFT_FN(bgfx_Context_frame, "bgfx::Context::frame (chunk 2/2)", 0xbc66de0, Context_frame_chunk_c01_step, nullptr);

// Returns true if control goes back to the loop head 0xbc68570 (more views);
// false if the original function returns at 0xbc687b6.
void Context_frame_chunk_c01_step(ContextFrameChunkC01State* state) {
    // Map state to local variables matching the disassembly
    uint8_t* ctx = static_cast<uint8_t*>(state->ctx);   // rsi = this
    uint8_t* viewDst = state->viewDst;                  // rdi = current view-copy dst
    // 0xbc685af..0xbc685c5 -- finish current view: sub_ebce650(viewDst,0x100,&local18,0x7FFFFFFF)
    // 0xbc685af  mov rcx,rdi
    // 0xbc685b2  mov edx,0x100
    // 0xbc685b7  mov r8,rbx
    // 0xbc685ba  mov r9d,0x7FFFFFFF
    sub_ebce650(viewDst, 0x100u, &state->local18, 0x7FFFFFFFu);  // 0xbc685c0  call 0xEBCE650
    // 0xbc685c5  nop

    // 0xbc685c6..0xbc685e1 -- advance to next view; loop back to 0xbc68570 while r12 < u16[ctx+0x4E8]
    // 0xbc685c6  inc r12
    // 0xbc685c9  movzx eax,word ptr [rsi+0x4E8]
    // 0xbc685d0  add rdi,0x138
    // 0xbc685d7  add r15,0x138
    // 0xbc685de  cmp r12,rax
    // 0xbc685e1  jb short 0xBC68570
    ++state->r12;
    uint32_t viewCount = ld<uint16_t>(ctx + kViewCount_Off);
    viewDst += kViewStride;
    state->r15 += kViewStride;
    state->viewDst = viewDst;
    if (state->r12 < viewCount) {
        state->ctx = ctx;
        return;   // 0xbc685e1 jb 0xBC68570 (back-edge to chunk 1; caller re-runs loop)
    }

    // 0xbc685e3..0xbc685f4 -- copy view src-count into dst-count; skip copy if zero
    // 0xbc685e3  movzx eax,word ptr [rsi+0x13D00]
    // 0xbc685ea  mov [rsi+0x13CF0],ax
    // 0xbc685f1  test ax,ax
    // 0xbc685f4  je short 0xBC6862C
    uint16_t srcCount = ld<uint16_t>(ctx + kSrcCount_Off);
    st<uint16_t>(ctx + kCopySrcCount_Off, srcCount);
    if (srcCount != 0) {
        // 0xbc685f6..0xbc6862a -- memcpy srcCount*16 bytes: dst=[ctx+0x13CF8], src=[ctx+0x13D08]
        // 0xbc685f6  xor eax,eax
        // 0xbc685f8  xor ecx,ecx
        // 0xbc685fa  nop [rax+rax]
        uint8_t* dst = reinterpret_cast<uint8_t*>(ld<uint64_t>(ctx + kCopyDst_Off));  // 0xbc68600 mov rdx,[rsi+0x13CF8]
        uint8_t* src = reinterpret_cast<uint8_t*>(ld<uint64_t>(ctx + kCopySrc_Off));  // 0xbc68607 mov r8,[rsi+0x13D08]
        uint64_t off = 0;                                                              // 0xbc685f6 xor eax,eax
        uint32_t i = 0;                                                                // 0xbc685f8 xor ecx,ecx
        do {
            // 0xbc6860e  movdqu xmm0,[r8+rax]
            // 0xbc68614  movdqu [rdx+rax],xmm0
            std::memcpy(dst + off, src + off, 16);
            ++i;                                                                        // 0xbc68619 inc rcx
            uint16_t count = ld<uint16_t>(ctx + kCopySrcCount_Off);                     // 0xbc6861c movzx edx,word ptr [rsi+0x13CF0]
            off += 0x10;                                                                // 0xbc68623 add rax,0x10
            if (!(i < count)) break;                                                    // 0xbc68627 cmp rcx,rdx / 0xbc6862a jb
        } while (true);
    }

    // 0xbc6862c..0xbc68638 -- sub_ebdbf20(ctx+0x3D0)
    // 0xbc6862c  lea rcx,[rsi+0x3D0]
    sub_ebdbf20(ctx + kSub_Off);                                                        // 0xbc68633 call 0xEBDBF20
    // 0xbc68638  nop

    // 0xbc68639..0xbc686cc -- frame number read + swap + handoff fields + memset
    // 0xbc68639  mov rax,[rsi+0x1CFD0C0]
    // 0xbc68640  mov rcx,[rsi+0x1CFD0C8]
    uint64_t frame0 = ld<uint64_t>(ctx + kFramePtr0_Off);
    uint64_t frame1 = ld<uint64_t>(ctx + kFramePtr1_Off);
    // 0xbc68647  mov eax,[rax+0xE746D8]
    uint32_t frameNum = ld<uint32_t>(reinterpret_cast<uint8_t*>(frame0) + kFrameNum_Off);
    // 0xbc6864d  inc eax
    ++frameNum;
    // 0xbc6864f  movq xmm0,[rcx+0xDC57F0]
    // 0xbc68657  pshufd xmm0,xmm0,0xE1   (swap the two 32-bit halves of the low 64 bits)
    // 0xbc6865c  movq [rcx+0xE60E88],xmm0
    uint64_t sw = ld<uint64_t>(reinterpret_cast<uint8_t*>(frame1) + kSwapSrc_Off);
    uint32_t slo = (uint32_t)sw, shi = (uint32_t)(sw >> 32);
    st<uint64_t>(reinterpret_cast<uint8_t*>(frame1) + kSwapDst_Off, ((uint64_t)slo << 32) | shi);
    // 0xbc68664  mov dword ptr [rcx+0xD457C0],1
    st<uint32_t>(reinterpret_cast<uint8_t*>(frame1) + kFlag_Off, 1);
    // 0xbc6866e  mov dword ptr [rcx+0xDC57D0],0
    st<uint32_t>(reinterpret_cast<uint8_t*>(frame1) + kZero0_Off, 0);
    // 0xbc68678  mov dword ptr [rcx+0xDC57E8],0
    st<uint32_t>(reinterpret_cast<uint8_t*>(frame1) + kZero1_Off, 0);
    // 0xbc68682  mov word ptr [rcx+0xDC57EC],0
    st<uint16_t>(reinterpret_cast<uint8_t*>(frame1) + kZeroW_Off, 0);
    // 0xbc6868b  mov qword ptr [rcx+0xDC57F0],0
    st<uint64_t>(reinterpret_cast<uint8_t*>(frame1) + kZeroQ_Off, 0);
    // 0xbc68696  mov rdx,0x4000000000000
    // 0xbc686a0  mov [rcx+0xDC5818],rdx
    // 0xbc686a7  mov [rcx+0xE05820],rdx
    st<uint64_t>(reinterpret_cast<uint8_t*>(frame1) + kConst_Off, kSwapConst);
    st<uint64_t>(reinterpret_cast<uint8_t*>(frame1) + kConst2_Off, kSwapConst);
    // 0xbc686ae  mov word ptr [rcx+0xE74988],0
    st<uint16_t>(reinterpret_cast<uint8_t*>(frame1) + kZeroUW_Off, 0);
    // 0xbc686b7  mov [rcx+0xE746D8],eax
    st<uint32_t>(reinterpret_cast<uint8_t*>(frame1) + kFrameNum_Off, frameNum);
    // 0xbc686bd  lea rcx,[rsi+0x1EAAC60]
    // 0xbc686c4  mov r8d,0x400
    // 0xbc686ca  xor edx,edx
    // 0xbc686cc  call 0xEBCE430
    sub_ebce430(ctx + kMemsetDst_Off, 0, kMemsetCount);                              // 0xbc686cc  call 0xEBCE430

    // 0xbc686d1..0xbc68735 -- compute dims and compare against cached state
    // 0xbc686d1  mov rcx,[rsi+0x1CFD0C0]
    // 0xbc686d8  mov rax,[rsi+0x1CFD0C8]
    // 0xbc686df  mov rdi,[rax+0xE60DE0]
    uint8_t* stateObj = reinterpret_cast<uint8_t*>(ld<uint64_t>(reinterpret_cast<uint8_t*>(frame1) + kObjPtr_Off));
    // 0xbc686e6  mov eax,[rsi+0x1EBF198]
    uint32_t Hraw = ld<uint32_t>(ctx + kHigh_Off);
    // 0xbc686ec  mov r8d,[rsi+0x1EBF194]
    uint32_t Wraw = ld<uint32_t>(ctx + kWide_Off);
    // 0xbc686f3  mov rcx,[rcx+0xE60DE0]
    uint8_t* frame0Obj = reinterpret_cast<uint8_t*>(ld<uint64_t>(reinterpret_cast<uint8_t*>(frame0) + kObjPtr_Off));
    // 0xbc686fa  shr r8d,3
    // 0xbc686fe  cmp r8d,1
    // 0xbc68702  adc r8d,0
    uint32_t W = (Wraw >> 3);
    if (W < 1) W += 1;
    // 0xbc68706  movzx r9d,byte ptr [rcx+0x10]
    uint8_t shift = ld<uint8_t>(frame0Obj + kShiftByte_Off);
    // 0xbc6870b  mov cl,4
    // 0xbc6870d  sub cl,r9b
    uint32_t cl = (uint32_t)(4u - (uint32_t)shift);
    // 0xbc68710  shr eax,cl
    // 0xbc68712  cmp eax,1
    // 0xbc68715  adc eax,0
    uint32_t H = Hraw >> (cl & 31);
    if (H < 1) H += 1;
    // 0xbc68718  mov rdx,[rdi]
    uint64_t buf = ld<uint64_t>(stateObj);
    // 0xbc6871b  test rdx,rdx
    // 0xbc6871e  je short 0xBC68737
    bool rebuild = (buf == 0);
    if (!rebuild) {
        // 0xbc68720  movzx ecx,word ptr [rdi+0xC]
        // 0xbc68724  cmp r8d,ecx
        uint16_t cW = ld<uint16_t>(stateObj + 0xC);
        if (W != cW) rebuild = true;
        if (!rebuild) {
            // 0xbc68729  movzx ecx,word ptr [rdi+0xE]
            // 0xbc6872d  cmp eax,ecx
            uint16_t cH = ld<uint16_t>(stateObj + 0xE);
            if (H != cH) rebuild = true;
            if (!rebuild) {
                // 0xbc68731  cmp [rdi+0x10],r9b
                // 0xbc68735  je short 0xBC687A6
                uint8_t cflag = ld<uint8_t>(stateObj + 0x10);
                if (cflag == shift) {
                    state->ctx = ctx;
                    return;   // 0xbc68735 je 0xBC687A6 -> epilogue -> ret
                }
                rebuild = true;
            }
        }
    }

    if (rebuild) {
        // 0xbc68737..0xbc68753 -- update cached dims and size
        // 0xbc68737  mov [rdi+0x10],r9b
        st<uint8_t>(stateObj + 0x10, shift);
        // 0xbc6873b  mov [rdi+0xC],r8w
        st<uint16_t>(stateObj + 0xC, (uint16_t)W);
        // 0xbc68740  mov [rdi+0xE],ax
        st<uint16_t>(stateObj + 0xE, (uint16_t)H);
        // 0xbc68744  mov esi,[rdi+8]
        uint32_t oldSize = ld<uint32_t>(stateObj + 8);
        // 0xbc68747  movzx ecx,r8w
        // 0xbc6874b  movzx r8d,ax
        // 0xbc6874f  imul r8d,ecx
        uint32_t newSize = (uint16_t)H * (uint16_t)W;
        // 0xbc68753  mov [rdi+8],r8d
        st<uint32_t>(stateObj + 8, newSize);

        // 0xbc68757  mov rcx,[0x12ADF800]
        // 0xbc6875e  test rcx,rcx
        // 0xbc68761  je short 0xBC6878D
        uint64_t allocator = ld<uint64_t>(kAllocGlobal);
        uint64_t newbuf;
        if (allocator != 0) {
            // 0xbc68763  add r8d,r8d  (size*2)
            uint64_t allocSize = (uint64_t)newSize * 2;
            // 0xbc68766  mov rax,[rcx]
            // 0xbc68769  mov rax,[rax+8]  (vtable slot read; faithful)
            void* vfn = reinterpret_cast<void*>(ld<uint64_t>(ld<uint64_t>(allocator) + 8));
            (void)vfn;
            // 0xbc6876d  mov dword ptr [rsp+0x28],0
            // 0xbc68775  mov qword ptr [rsp+0x20],0
            // 0xbc6877e  xor r9d,r9d
            // 0xbc68781  call qword ptr [0xF99FFA0]  (slot -> sub_eea6040 jmp rax trampoline)
            newbuf = reinterpret_cast<uint64_t>(eea6040_call(reinterpret_cast<void*>(allocator), reinterpret_cast<void*>(buf), allocSize, 0, 0, 0));
        } else {
            // 0xbc6878d  xor eax,eax
            newbuf = 0;
        }
        // 0xbc6878f  mov [rdi],rax
        st<uint64_t>(stateObj, newbuf);

        // 0xbc68792  sub r8d,esi
        // 0xbc68795  jbe short 0xBC687A6   (return if newSize <= oldSize)
        if (newSize > oldSize) {
            // 0xbc68797  add r8,r8   (count*2)
            uint64_t cnt = (uint64_t)(newSize - oldSize) * 2;
            // 0xbc6879a  lea rcx,[rax+rsi*2]
            uint8_t* dst = reinterpret_cast<uint8_t*>(newbuf + (uint64_t)oldSize * 2);
            // 0xbc6879e  xor edx,edx
            // 0xbc687a0  call 0xEBCE430
            sub_ebce430(dst, 0, (uint32_t)cnt);                                      // 0xbc687a0  call 0xEBCE430
            // 0xbc687a5  nop
        }
    }

    // 0xbc687a6..0xbc687b6 -- epilogue: add rsp,0x58 / pops / ret
    // 0xbc687a6  add rsp,0x58
    // 0xbc687aa  pop rbx
    // 0xbc687ab  pop rdi
    // 0xbc687ac  pop rsi
    // 0xbc687ad  pop r12
    // 0xbc687af  pop r13
    // 0xbc687b1  pop r14
    // 0xbc687b3  pop r15
    // 0xbc687b5  pop rbp
    // 0xbc687b6  ret
    state->ctx = ctx;
    return;
}

} } // namespace native::bgfx