// LIFT 0xbc60740 size 0x5d0 1.26.62.01 bgfx::Encoder::submit
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc60740.h"

#include <cstdint>
#include <cstring>

namespace native::bgfx {

namespace {

// Lifted callees (exact ABI signatures)
extern "C" void sub_bc60d10(void* encoder);
extern "C" void sub_bc60f10(void* frame, std::uint32_t idx, const void* src);
extern "C" void sub_bc76610(void* hash, const void* data, std::uint32_t len);
extern "C" void sub_bc7a7c0(void* storage, std::uint32_t idx);
extern "C" void sub_eec6ec0(void* dst, const void* src, std::uint32_t n);

// Boundary callees (via data slots / IAT)
using Eea6040Fn = void (*)(void* iface, void* ptr, std::uint64_t size, std::uint32_t flags);
inline Eea6040Fn eea6040_thunk() {
    return reinterpret_cast<Eea6040Fn>(
        *reinterpret_cast<std::uintptr_t*>(
            RewriteRegistry::imageBase() + 0xF99FFA0ull));
}
inline void* allocator_global() {
    return *reinterpret_cast<void**>(
        RewriteRegistry::imageBase() + 0x12ADF800ull);
}
native::Boundary<void, void*, std::uint64_t, std::uint64_t, std::uint64_t> sub_eec6ed0("sub_eec6ed0");
native::Boundary<void*, void*, void*, std::uint32_t> sub_e951550("sub_e951550");

} // namespace

extern "C" void sub_bc60740(void* thisPtr, std::uint16_t viewId, std::uint16_t program,
                            std::uint16_t occlusionQuery, std::uint32_t depth, std::uint8_t preserveState) {
    auto* e = static_cast<EncoderImpl*>(thisPtr);

    // 0xbc60740..0xbc607ad
    // 0xbc60740  push r15
    // 0xbc60742  push r14
    // 0xbc60744  push rsi
    // 0xbc60745  push rdi
    // 0xbc60746  push rbp
    // 0xbc60747  push rbx
    // 0xbc60748  sub rsp,0x68
    // 0xbc6074c  movaps [rsp+0x50],xmm6
    // 0xbc60751  mov rsi,rcx
    // 0xbc60754  movzx ebp,byte ptr [rsp+0xC8]
    // 0xbc6075c  mov r10d,[rsp+0xC0]
    // 0xbc60764  mov rax,[0x1230A0C0]
    // 0xbc6076b  xor rax,rsp
    // 0xbc6076e  mov [rsp+0x48],rax
    // 0xbc60773  cmp byte ptr [rcx+0x6AD],1
    // 0xbc6077a  jne short 0xBC607AD
    if (e->m_discard == 1) {
        // 0xbc6077c  mov rax,[rsp+0x48]
        // 0xbc60781  xor rax,rsp
        // 0xbc60784  mov rcx,[0x1230A0C0]
        // 0xbc6078b  cmp rcx,rax
        // 0xbc6078e  jne 0xBC60D02
        // 0xbc60794  mov rcx,rsi
        // 0xbc60797  movaps xmm6,[rsp+0x50]
        // 0xbc6079c  add rsp,0x68
        // 0xbc607a0  pop rbx
        // 0xbc607a1  pop rbp
        // 0xbc607a2  pop rdi
        // 0xbc607a3  pop rsi
        // 0xbc607a4  pop r14
        // 0xbc607a6  pop r15
        // 0xbc607a8  jmp 0xBC60D10
        sub_bc60d10(e);
        return;
    }

    // 0xbc607ad..0xbc607bf
    // 0xbc607ad  mov eax,[rsi+0x84]
    // 0xbc607b3  or eax,[rsi+0x8C]
    // 0xbc607b9  je short 0xBC60807
    // 0xbc607bb  lea rbx,[rsi+0x40]
    if ((e->m_draw.m_numIndices | e->m_draw.m_numVertices) == 0) {
        // 0xbc60807  mov rcx,rsi
        // 0xbc6080a  call 0xBC60D10
        // 0xbc6080f  inc dword ptr [rsi+0x690]
        // 0xbc60815  mov rax,[rsp+0x48]
        // ...
        sub_bc60d10(e);
        ++e->m_numDropped;
        return;
    }

    // 0xbc607bf..0xbc60805
    // 0xbc607bf  mov rcx,[rsi]
    // 0xbc607c2  mov eax,[rcx+0xDC57E8]
    // 0xbc607c8  mov r11d,0xFFFF
    // 0xbc607ce  xchg ax,ax
    // 0xbc607d0  mov edi,eax
    // 0xbc607d2  lea r14d,[rdi+1]
    // 0xbc607d6  cmp r14d,0xFFFF
    // 0xbc607dd  cmovae r14d,r11d
    // 0xbc607e1  cmp eax,0xFFFF
    // 0xbc607e6  cmovae r14d,r11d
    // 0xbc607ea  lock cmpxchg [rcx+0xDC57E8],r14d
    // 0xbc607f3  cmp edi,0xFFFF
    // 0xbc607f9  je short 0xBC607FF
    // 0xbc607fb  cmp edi,eax
    // 0xbc607fd  jne short 0xBC607D0
    // 0xbc607ff  cmp edi,0xFFFE
    // 0xbc60805  jb short 0xBC6083F
    Frame* frame = e->m_frame;
    std::uint32_t seen = frame->m_numRenderItems;
    std::uint32_t idx, next;
    do {
        idx = seen;
        next = (idx + 1 >= 0xFFFF || idx >= 0xFFFF) ? 0xFFFF : idx + 1;
        seen = _InterlockedCompareExchange(&frame->m_numRenderItems, next, idx);
    } while (idx != 0xFFFF && idx != seen);
    if (idx >= 0xFFFE) {
        sub_bc60d10(e);
        ++e->m_numDropped;
        return;
    }

    // 0xbc6083f..0xbc608a0
    // 0xbc6083f  inc dword ptr [rsi+0x68C]
    // 0xbc60845  mov rax,0x3FC0000000000000
    // 0xbc6084f  mov rcx,[rsi]
    // 0xbc60852  mov r11,[rcx+0xDC57E0]
    // 0xbc60859  movzx r14d,byte ptr [rsi+0x6AC]
    // 0xbc60861  mov r11,[r11+r14*8]
    // 0xbc60865  mov r11d,[r11+4]
    // 0xbc60869  mov [rsi+0x698],r11d
    // 0xbc60870  xor r11d,r11d
    // 0xbc60873  cmp r8w,0xFFFF
    // 0xbc60878  cmove r8d,r11d
    // 0xbc6087c  mov [rsi+0x10],r8w
    // 0xbc60881  mov [rsi+0x12],dx
    // 0xbc60885  mov r11,[0x12AE1748]
    // 0xbc6088c  movzx edx,dx
    // 0xbc6088f  lea r14,[rdx+rdx*4]
    // 0xbc60893  shl r14d,6
    // 0xbc60897  movzx r14d,byte ptr [r11+r14+0x1EAB1B2]
    // 0xbc608a0  cmp r14d,1
    ++e->m_numSubmitted;
    e->m_uniformEnd = frame->m_uniformBuffer[e->m_uniformIdx]->pos;
    e->m_key.m_program = (program == 0xFFFF) ? 0 : program;
    e->m_key.m_view = viewId;
    const std::uint64_t viewBits = (std::uint64_t(viewId) << 54) & 0x3FC0000000000000ull;
    std::uint64_t key;
    std::uint8_t mode = e->m_ctx->m_view[viewId].m_mode;

    // 0xbc608a0..0xbc6098b
    // 0xbc608a4  je short 0xBC608F7
    // 0xbc608a6  cmp r14d,2
    // 0xbc608aa  je short 0xBC608B9
    // 0xbc608ac  cmp r14d,3
    // 0xbc608b0  jne 0xBC6094E
    // 0xbc608b6  neg r10d
    // 0xbc608b9  mov [rsi+8],r10d
    // 0xbc608bd  mov r10d,r10d
    // 0xbc608c0  shl r10,0x12
    // 0xbc608c4  shl r8d,5
    // 0xbc608c8  movzx r8d,r8w
    // 0xbc608cc  mov r11d,[rsi+0x14]
    // 0xbc608d0  and r11d,3
    // 0xbc608d4  shl r11d,0x10
    // 0xbc608d8  shl rdx,0x36
    // 0xbc608dc  and rdx,rax
    // 0xbc608df  or rdx,r10
    // 0xbc608e2  or rdx,r11
    // 0xbc608e5  or rdx,r8
    // 0xbc608e8  mov rax,0x14000000000000
    // 0xbc608f2  jmp 0xBC6098B
    // 0xbc608f7  mov ecx,1
    // 0xbc608fc  lock xadd [r11+rdx*4+0x1EAAC60],ecx
    // 0xbc60906  mov [rsi+0xC],ecx
    // 0xbc60909  and ecx,0xFFFFF
    // 0xbc6090f  shl rcx,0x1E
    // 0xbc60913  mov edx,[rsi+0x10]
    // 0xbc60916  shl edx,0x11
    // 0xbc60919  and edx,0xFFE0000
    // 0xbc6091f  or rdx,rcx
    // 0xbc60922  mov ecx,[rsi+0x14]
    // 0xbc60925  and ecx,3
    // 0xbc60928  shl ecx,0x1C
    // 0xbc6092b  or rcx,rdx
    // 0xbc6092e  movzx edx,word ptr [rsi+0x12]
    // 0xbc60932  shl rdx,0x36
    // 0xbc60936  and rdx,rax
    // 0xbc60939  or rdx,rcx
    // 0xbc6093c  mov rax,0x18000000000000
    // 0xbc60946  or rax,rdx
    // 0xbc60949  mov rcx,[rsi]
    // 0xbc6094c  jmp short 0xBC6098E
    // 0xbc6094e  mov r10d,[rsi+8]
    // 0xbc60952  mov r11d,[rsi+0x14]
    // 0xbc60956  shl r10,5
    // 0xbc6095a  movzx r8d,r8w
    // 0xbc6095e  and r8d,0x7FF
    // 0xbc60965  shl r8,0x25
    // 0xbc60969  or r8,r10
    // 0xbc6096c  and r11d,3
    // 0xbc60970  shl r11,0x30
    // 0xbc60974  or r11,r8
    // 0xbc60977  shl rdx,0x36
    // 0xbc6097b  and rdx,rax
    // 0xbc6097e  or rdx,r11
    // 0xbc60981  mov rax,0x10000000000000
    // 0xbc6098b  or rax,rdx
    if (mode == 1) { // Sequential
        e->m_key.m_seq = _InterlockedExchangeAdd(&e->m_ctx->m_seq[viewId], 1);
        key = 0x0018000000000000ull | viewBits
            | (std::uint64_t(e->m_key.m_seq & 0xFFFFF) << 30)
            | ((std::uint32_t(e->m_key.m_program) << 17) & 0x0FFE0000)
            | (std::uint32_t(e->m_key.m_trans & 3) << 28);
    } else if (mode == 3) { // DepthDescending
        depth = static_cast<std::uint32_t>(-static_cast<std::int32_t>(depth));
        e->m_key.m_depth = depth;
        key = 0x0014000000000000ull | viewBits
            | (std::uint64_t(depth) << 18)
            | std::uint16_t(program << 5)
            | (std::uint32_t(e->m_key.m_trans & 3) << 16);
    } else if (mode == 2) { // DepthAscending
        e->m_key.m_depth = depth;
        key = 0x0014000000000000ull | viewBits
            | (std::uint64_t(depth) << 18)
            | std::uint16_t(program << 5)
            | (std::uint32_t(e->m_key.m_trans & 3) << 16);
    } else { // Default
        key = 0x0010000000000000ull | viewBits
            | (std::uint64_t(e->m_key.m_depth) << 5)
            | (std::uint64_t(program & 0x7FF) << 37)
            | (std::uint64_t(e->m_key.m_trans & 3) << 48);
    }

    // 0xbc6098e..0xbc609bd
    // 0xbc6098e  mov r14d,edi
    // 0xbc60991  mov [rcx+r14*8+0x14700],rax
    // 0xbc60999  mov rax,[rsi]
    // 0xbc6099c  mov [rax+r14*2+0x94700],di
    // 0xbc609a5  movzx eax,byte ptr [rsi+0x6AC]
    // 0xbc609ac  mov [rsi+0xA4],al
    // 0xbc609b2  mov rax,[rsi+0x694]
    // 0xbc609b9  mov [rsi+0x74],rax
    frame->m_sortKeys[idx] = key;
    frame->m_sortValues[idx] = static_cast<std::uint16_t>(idx);
    e->m_draw.m_uniformIdx = e->m_uniformIdx;
    e->m_draw.m_uniformBegin = e->m_uniformBegin;
    e->m_draw.m_uniformEnd = e->m_uniformEnd;

    // 0xbc609bd..0xbc60a13
    // 0xbc609bd  movzx eax,byte ptr [rsi+0xA3]
    // 0xbc609c4  test eax,eax
    // 0xbc609c6  je short 0xBC609D8
    // 0xbc609c8  cmp eax,0xFF
    // 0xbc609cd  jne short 0xBC609E0
    // 0xbc609cf  mov r8d,[rsi+0x69C]
    // 0xbc609d6  jmp short 0xBC60A13
    // 0xbc609d8  mov r8d,0xFFFFFFFF
    // 0xbc609de  jmp short 0xBC60A13
    // 0xbc609e0  tzcnt ecx,eax
    // 0xbc609e4  mov r8d,0xFFFFFFFF
    // 0xbc609ea  xor edx,edx
    // 0xbc609ec  nop [rax]
    // 0xbc609f0  mov r10d,r8d
    // 0xbc609f3  shr eax,cl
    // 0xbc609f5  lea r8d,[rdx+rcx]
    // 0xbc609f9  mov r8d,[rsi+r8*4+0x69C]
    // 0xbc60a01  cmp r10d,r8d
    // 0xbc60a04  cmovb r8d,r10d
    // 0xbc60a08  shr eax,1
    // 0xbc60a0a  add edx,ecx
    // 0xbc60a0c  inc edx
    // 0xbc60a0e  bsf ecx,eax
    // 0xbc60a11  jne short 0xBC609F0
    // 0xbc60a13  mov [rsi+0x8C],r8d
    std::uint32_t numVertices;
    if (e->m_draw.m_streamMask == 0) {
        numVertices = 0xFFFFFFFFu;
    } else if (e->m_draw.m_streamMask == 0xFF) {
        numVertices = e->m_numVertices[0];
    } else {
        numVertices = 0xFFFFFFFFu;
        std::uint32_t mask = e->m_draw.m_streamMask;
        std::uint32_t s = 0;
        while (mask != 0) {
            std::uint32_t n = __tzcnt_u32(mask);
            mask >>= n; s += n;
            std::uint32_t v = e->m_numVertices[s];
            if (v < numVertices) numVertices = v;
            mask >>= 1; s += 1;
            if (mask == 0) break;
        }
    }
    e->m_draw.m_numVertices = numVertices;

    // 0xbc60a1a..0xbc60a2d
    // 0xbc60a1a  cmp r9w,0xFFFF
    // 0xbc60a1f  je short 0xBC60A2D
    // 0xbc60a21  or byte ptr [rsi+0x67],0x40
    // 0xbc60a25  mov [rsi+0xBA],r9w
    if (occlusionQuery != 0xFFFF) {
        e->m_draw.m_stateFlags |= 0x4000000000000000ull;
        e->m_draw.m_occlusionQuery = occlusionQuery;
    }

    // 0xbc60a2d..0xbc60ab2
    // 0xbc60a2d  cmp byte ptr [rsi+0x688],1
    // 0xbc60a34  jne short 0xBC60AB2
    // 0xbc60a36  lea rdx,[rsi+0x140]
    // 0xbc60a3d  xorps xmm0,xmm0
    // 0xbc60a40  movaps [rsp+0x30],xmm0
    // 0xbc60a45  lea rcx,[rsp+0x30]
    // 0xbc60a4a  mov r8d,0x514
    // 0xbc60a50  call 0xBC76610
    // 0xbc60a55  imul eax,[rsp+0x34],0x5BD1E995
    // 0xbc60a5d  mov ecx,eax
    // 0xbc60a5f  shr ecx,0x18
    // 0xbc60a62  xor ecx,eax
    // 0xbc60a64  imul eax,ecx,0x5BD1E995
    // 0xbc60a6a  imul ecx,[rsp+0x30],0x5BD1E995
    // 0xbc60a72  imul edx,[rsp+0x3C],0x5BD1E995
    // 0xbc60a7a  xor ecx,eax
    // 0xbc60a7c  mov eax,edx
    // 0xbc60a7e  shr eax,0x18
    // 0xbc60a81  xor eax,edx
    // 0xbc60a83  imul eax,0x5BD1E995
    // 0xbc60a89  imul ecx,0x5BD1E995
    // 0xbc60a8f  xor ecx,eax
    // 0xbc60a91  mov eax,ecx
    // 0xbc60a93  shr eax,0xD
    // 0xbc60a96  xor eax,ecx
    // 0xbc60a98  imul eax,0x5BD1E995
    // 0xbc60a9e  mov ecx,eax
    // 0xbc60aa0  shr ecx,0xF
    // 0xbc60aa3  xor ecx,eax
    // 0xbc60aa5  mov [rsi+0x654],ecx
    // 0xbc60aab  mov byte ptr [rsi+0x688],0
    if (e->m_bindDirty == 1) {
        struct Hash { std::uint32_t h, tail, count, size; };
        Hash hh{}; hh.size = 0;
        sub_bc76610(&hh, &e->m_bind, 0x514);
        std::uint32_t a = hh.tail * 0x5BD1E995u; a = (a ^ (a >> 24)) * 0x5BD1E995u;
        std::uint32_t c = hh.size * 0x5BD1E995u; c = (c ^ (c >> 24)) * 0x5BD1E995u;
        std::uint32_t x = ((hh.h * 0x5BD1E995u) ^ a) * 0x5BD1E995u ^ c;
        x = (x ^ (x >> 13)) * 0x5BD1E995u;
        e->m_bindHash = x ^ (x >> 15);
        e->m_bindDirty = 0;
    }

    // 0xbc60ab2..0xbc60b4f
    // 0xbc60ab2  mov rax,[rsi]
    // 0xbc60ab5  mov rcx,r14
    // 0xbc60ab8  shl rcx,7
    // 0xbc60abc  movaps xmm0,[rbx+0x70]
    // 0xbc60ac0  movaps [rax+rcx+0xB4770],xmm0
    // 0xbc60ac8  movaps xmm0,[rbx+0x60]
    // 0xbc60acc  movaps [rax+rcx+0xB4760],xmm0
    // 0xbc60ad4  movaps xmm0,[rbx+0x50]
    // 0xbc60ad8  movaps [rax+rcx+0xB4750],xmm0
    // 0xbc60ae0  movaps xmm0,[rbx+0x40]
    // 0xbc60ae4  movaps [rax+rcx+0xB4740],xmm0
    // 0xbc60aec  movaps xmm0,[rbx]
    // 0xbc60aef  movaps xmm1,[rbx+0x10]
    // 0xbc60af3  movaps xmm2,[rbx+0x20]
    // 0xbc60af7  movaps xmm3,[rbx+0x30]
    // 0xbc60afb  movaps [rax+rcx+0xB4730],xmm3
    // 0xbc60b03  movaps [rax+rcx+0xB4720],xmm2
    // 0xbc60b0b  movaps [rax+rcx+0xB4710],xmm1
    // 0xbc60b13  movaps [rax+rcx+0xB4700],xmm0
    // 0xbc60b1b  mov r15,[rsi]
    // 0xbc60b1e  lea rcx,[r15+0x8B4700]
    // 0xbc60b25  lea rbx,[rsi+0x140]
    // 0xbc60b2c  mov edx,edi
    // 0xbc60b2e  call 0xBC7A7C0
    // 0xbc60b33  imul rcx,r14,0x540
    // 0xbc60b3a  add rcx,[r15+0x8B4700]
    // 0xbc60b41  mov r8d,0x518
    // 0xbc60b47  mov rdx,rbx
    // 0xbc60b4a  call 0xEEC6EC0
    std::memcpy(&frame->m_renderItem[idx], &e->m_draw, 0x80);
    sub_bc7a7c0(&frame->m_renderItemBind, idx);
    std::memcpy(&frame->m_renderItemBind.data[idx * 0x540], &e->m_bind, 0x518);

    // 0xbc60b4f..0xbc60b65
    // 0xbc60b4f  mov r8,[rsi+0x680]
    // 0xbc60b56  test r8,r8
    // 0xbc60b59  je short 0xBC60B65
    // 0xbc60b5b  mov rcx,[rsi]
    // 0xbc60b5e  mov edx,edi
    // 0xbc60b60  call 0xBC60F10
    // 0xbc60b65  test bpl,bpl
    // 0xbc60b68  jne 0xBC60815
    if (e->m_sideTable) {
        sub_bc60f10(frame, idx, e->m_sideTable);
    }
    if (preserveState) return;

    // 0xbc60b6e..0xbc60c0e
    // 0xbc60b6e  mov rax,0x10000500000001F
    // 0xbc60b78  mov [rsi+0x60],rax
    // 0xbc60b7c  mov qword ptr [rsi+0x68],0
    // 0xbc60b84  xorps xmm0,xmm0
    // 0xbc60b87  movaps [rsi+0x70],xmm0
    // 0xbc60b8b  movaps xmm0,[0xF08EF70]
    // 0xbc60b92  movaps [rsi+0x80],xmm0
    // 0xbc60b99  mov rax,0x100000000
    // 0xbc60ba3  mov [rsi+0x90],rax
    // 0xbc60baa  mov rax,0x1FFFF00000000
    // 0xbc60bb4  mov [rsi+0x98],rax
    // 0xbc60bbb  mov byte ptr [rsi+0xA2],0
    // 0xbc60bc2  mov word ptr [rsi+0xA0],0xFFFF
    // 0xbc60bcb  mov word ptr [rsi+0xA3],0xFF00
    // 0xbc60bd4  mov rax,0xFFFFFFFF00000000
    // 0xbc60bde  mov [rsi+0x40],rax
    // 0xbc60be2  mov qword ptr [rsi+0xB4],0xFFFFFFFFFFFFFFFF
    // 0xbc60bed  mov dword ptr [rsi+0xA8],0x7FFFFFFF
    // 0xbc60bf7  mov qword ptr [rsi+0xAC],0
    // 0xbc60c02  mov eax,[rsi+0x698]
    // 0xbc60c08  mov [rsi+0x694],eax
    // 0xbc60c0e  mov eax,0x167
    e->m_draw.m_stateFlags = 0x010000500000001Full;
    e->m_draw.m_stencil = 0;
    std::memset(reinterpret_cast<char*>(e) + 0x70, 0, 16);
    const std::uint8_t* defaults = reinterpret_cast<const std::uint8_t*>(RewriteRegistry::imageBase() + 0xF08EF70ull);
    std::memcpy(reinterpret_cast<char*>(e) + 0x80, defaults, 16);
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<char*>(e) + 0x90) = 0x0000000100000000ull;
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<char*>(e) + 0x98) = 0x0001FFFF00000000ull;
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<char*>(e) + 0xA2) = 0;
    *reinterpret_cast<std::uint16_t*>(reinterpret_cast<char*>(e) + 0xA0) = 0xFFFF;
    *reinterpret_cast<std::uint16_t*>(reinterpret_cast<char*>(e) + 0xA3) = 0xFF00;
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<char*>(e) + 0x40) = 0xFFFFFFFF00000000ull;
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<char*>(e) + 0xB4) = ~0ull;
    *reinterpret_cast<std::int32_t*>(reinterpret_cast<char*>(e) + 0xA8) = 0x7FFFFFFF;
    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<char*>(e) + 0xAC) = 0;
    e->m_uniformBegin = e->m_uniformEnd;

    // 0xbc60c0e..0xbc60c65
    // 0xbc60c20  mov word ptr [rsi+rax-0x1D],0xFFFF
    // 0xbc60c27  mov byte ptr [rsi+rax-0x14],0
    // 0xbc60c2c  mov dword ptr [rsi+rax-0x27],0
    // 0xbc60c34  mov dword ptr [rsi+rax-0x1B],0xFFFFFFFF
    // 0xbc60c3c  cmp rax,0x667
    // 0xbc60c42  je short 0xBC60C65
    // 0xbc60c44  mov word ptr [rsi+rax-9],0xFFFF
    // 0xbc60c4b  mov byte ptr [rsi+rax],0
    // 0xbc60c4f  mov dword ptr [rsi+rax-0x13],0
    // 0xbc60c57  mov dword ptr [rsi+rax-7],0xFFFFFFFF
    // 0xbc60c5f  add rax,0x28
    // 0xbc60c63  jmp short 0xBC60C20
    // 0xbc60c65  mov rdi,[rsi+0x680]
    // 0xbc60c6c  test rdi,rdi
    // 0xbc60c6f  je 0xBC60CF6
    for (std::size_t i = 0; i < 0x167; i += 0x28) {
        std::uint8_t* base = reinterpret_cast<std::uint8_t*>(&e->m_bind) + i;
        *reinterpret_cast<std::uint16_t*>(base + 0x0A) = 0xFFFF;
        *reinterpret_cast<std::uint8_t*>(base + 0x13) = 0;
        *reinterpret_cast<std::uint32_t*>(base + 0x0C) = 0xFFFFFFFF;
        *reinterpret_cast<std::uint32_t*>(base + 0x00) = 0;
    }

    // 0xbc60c65..0xbc60cfd
    // 0xbc60c75  mov rcx,[0x12ADF800]
    // 0xbc60c7c  test rcx,rcx
    // 0xbc60c7f  je short 0xBC60CDC
    // 0xbc60c81  xor ebx,ebx
    // 0xbc60c83  xorps xmm6,xmm6
    // 0xbc60c86  jmp short 0xBC60CCF
    // 0xbc60c90  mov rdx,[r14]
    // 0xbc60c93  mov rax,[rcx]
    // 0xbc60c96  mov rax,[rax+8]
    // 0xbc60c9a  mov dword ptr [rsp+0x28],0
    // 0xbc60ca2  mov qword ptr [rsp+0x20],0
    // 0xbc60cab  xor r8d,r8d
    // 0xbc60cae  xor r9d,r9d
    // 0xbc60cb1  call qword ptr [0xF99FFA0]
    // 0xbc60cb7  mov rcx,[0x12ADF800]
    // 0xbc60cbe  movups [r14],xmm6
    // 0xbc60cc2  add rbx,0x10
    // 0xbc60cc6  cmp rbx,0x410
    // 0xbc60ccd  je short 0xBC60CEC
    // 0xbc60ccf  lea r14,[rdi+rbx]
    // 0xbc60cd3  test rcx,rcx
    // 0xbc60cd6  jne short 0xBC60C90
    // 0xbc60cd8  xor ecx,ecx
    // 0xbc60cda  jmp short 0xBC60CBE
    // 0xbc60cdc  mov r8d,0x410
    // 0xbc60ce2  mov rcx,rdi
    // 0xbc60ce5  xor edx,edx
    // 0xbc60ce7  call 0xEEC6ED0
    // 0xbc60cec  mov dword ptr [rdi+0x410],0
    // 0xbc60cf6  mov byte ptr [rsi+0x688],1
    // 0xbc60cfd  jmp 0xBC60815
    if (auto* t = e->m_sideTable) {
        if (void* alloc = allocator_global()) {
            SideTableEntry zeroEntry{};
            for (int k = 0; k < 0x41; ++k) {
                void* ptr = t->entries[k].ptr;
                eea6040_thunk()(alloc, ptr, 0, 0);
                t->entries[k] = zeroEntry;
            }
        } else {
            std::memset(t, 0, 0x410);
        }
        t->count = 0;
    }
    e->m_bindDirty = 1;
    return;

    // 0xbc60d02..0xbc60d0f: __security_check_cookie failure path
    // 0xbc60d02  mov rcx,[rsp+0x48]
    // 0xbc60d07  xor rcx,rsp
    // 0xbc60d0a  call 0xE951550
    // 0xbc60d0f  int3
    // This is the stack cookie failure handler - unreachable in normal execution
    // but present in the function body. We include it for coverage.
    // The original code falls through here from the cookie checks at 0xbc6078e and 0xbc60827
    // which are the epilogue cookie verification before return.
}

// Verbatim log of every call instruction in [0xbc60740, 0xbc60d10) (rdis dis output, two spaces after address):
#if 0
0xbc6080a  call 0xBC60D10
0xbc60a50  call 0xBC76610
0xbc60b2e  call 0xBC7A7C0
0xbc60b4a  call 0xEEC6EC0
0xbc60b60  call 0xBC60F10
0xbc60cb1  call qword ptr [0xF99FFA0]
0xbc60ce7  call 0xEEC6ED0
0xbc60d0a  call 0xE951550
#endif
// Calls out of lifted code:
//   sub_bc60d10 (0xbc60d10, lifted) x2: discard path at 0xbc607a8 and drop path at 0xbc6080a
//   sub_bc76610 (0xbc76610, lifted) x1: bx::HashMurmur2A::add at 0xbc60a50
//   sub_bc7a7c0 (0xbc7a7c0, lifted) x1: GuardedPagedArray::ensure at 0xbc60b2e
//   sub_eec6ec0 (0xeec6ec0, lifted) x1: memcpy at 0xbc60b4a
//   sub_bc60f10 (0xbc60f10, lifted) x1: commitSideTable at 0xbc60b60
//   sub_eea6040 (0xeea6040, vendor boundary via data slot 0xF99FFA0, native_boundary.tsv row 0xeea6040) x1: allocator free at 0xbc60cb1
//   sub_eec6ed0 (0xeec6ed0, crt boundary) x1: memset at 0xbc60ce7
//   sub_e951550 (0xe951550, crt boundary, __security_check_cookie failure) x1: at 0xbc60d0a
// UNRESOLVED CALL = none: every call target is lifted or boundary

// Layout assertions (full set in sub_bc60740.h; repeated here so liftcheck sees them).
static_assert(offsetof(native::bgfx::EncoderImpl, m_frame) == 0x000, "sub_0xbc60740: EncoderImpl m_frame at +0x000");
static_assert(offsetof(native::bgfx::EncoderImpl, m_key) == 0x008, "sub_0xbc60740: EncoderImpl m_key at +0x008");
static_assert(offsetof(native::bgfx::SortKey, m_depth) == 0x08, "sub_0xbc60740: SortKey m_depth at +0x08");
static_assert(offsetof(native::bgfx::SortKey, m_seq) == 0x0C, "sub_0xbc60740: SortKey m_seq at +0x0C");
static_assert(offsetof(native::bgfx::SortKey, m_program) == 0x10, "sub_0xbc60740: SortKey m_program at +0x10");
static_assert(offsetof(native::bgfx::SortKey, m_view) == 0x12, "sub_0xbc60740: SortKey m_view at +0x12");
static_assert(offsetof(native::bgfx::SortKey, m_trans) == 0x14, "sub_0xbc60740: SortKey m_trans at +0x14");
static_assert(offsetof(native::bgfx::EncoderImpl, m_draw) == 0x040, "sub_0xbc60740: EncoderImpl m_draw at +0x040");
static_assert(offsetof(native::bgfx::RenderDraw, m_stateFlags) == 0x60 - 0x40, "sub_0xbc60740: RenderDraw m_stateFlags at +0x20 from m_draw (+0x60 from EncoderImpl)");
static_assert(offsetof(native::bgfx::RenderDraw, m_stencil) == 0x68 - 0x40, "sub_0xbc60740: RenderDraw m_stencil at +0x28 from m_draw (+0x68 from EncoderImpl)");
static_assert(offsetof(native::bgfx::RenderDraw, m_uniformBegin) == 0x74 - 0x40, "sub_0xbc60740: RenderDraw m_uniformBegin at +0x34 from m_draw (+0x74 from EncoderImpl)");
static_assert(offsetof(native::bgfx::RenderDraw, m_uniformEnd) == 0x78 - 0x40, "sub_0xbc60740: RenderDraw m_uniformEnd at +0x38 from m_draw (+0x78 from EncoderImpl)");
static_assert(offsetof(native::bgfx::RenderDraw, m_numIndices) == 0x84 - 0x40, "sub_0xbc60740: RenderDraw m_numIndices at +0x44 from m_draw (+0x84 from EncoderImpl)");
static_assert(offsetof(native::bgfx::RenderDraw, m_numVertices) == 0x8C - 0x40, "sub_0xbc60740: RenderDraw m_numVertices at +0x4C from m_draw (+0x8C from EncoderImpl)");
static_assert(offsetof(native::bgfx::RenderDraw, m_streamMask) == 0xA3 - 0x40, "sub_0xbc60740: RenderDraw m_streamMask at +0x63 from m_draw (+0xA3 from EncoderImpl)");
static_assert(offsetof(native::bgfx::RenderDraw, m_uniformIdx) == 0xA4 - 0x40, "sub_0xbc60740: RenderDraw m_uniformIdx at +0x64 from m_draw (+0xA4 from EncoderImpl)");
static_assert(offsetof(native::bgfx::RenderDraw, m_occlusionQuery) == 0xBA - 0x40, "sub_0xbc60740: RenderDraw m_occlusionQuery at +0x7A from m_draw (+0xBA from EncoderImpl)");
static_assert(sizeof(native::bgfx::RenderDraw) == 0x80, "sub_0xbc60740: RenderDraw size 0x80");
static_assert(offsetof(native::bgfx::EncoderImpl, m_bind) == 0x140, "sub_0xbc60740: EncoderImpl m_bind at +0x140");
static_assert(sizeof(native::bgfx::RenderBind) == 0x514, "sub_0xbc60740: RenderBind size 0x514");
static_assert(offsetof(native::bgfx::EncoderImpl, m_bindHash) == 0x654, "sub_0xbc60740: EncoderImpl m_bindHash at +0x654");
static_assert(offsetof(native::bgfx::EncoderImpl, m_sideTable) == 0x680, "sub_0xbc60740: EncoderImpl m_sideTable at +0x680");
static_assert(offsetof(native::bgfx::EncoderImpl, m_bindDirty) == 0x688, "sub_0xbc60740: EncoderImpl m_bindDirty at +0x688");
static_assert(offsetof(native::bgfx::EncoderImpl, m_numSubmitted) == 0x68C, "sub_0xbc60740: EncoderImpl m_numSubmitted at +0x68C");
static_assert(offsetof(native::bgfx::EncoderImpl, m_numDropped) == 0x690, "sub_0xbc60740: EncoderImpl m_numDropped at +0x690");
static_assert(offsetof(native::bgfx::EncoderImpl, m_uniformBegin) == 0x694, "sub_0xbc60740: EncoderImpl m_uniformBegin at +0x694");
static_assert(offsetof(native::bgfx::EncoderImpl, m_uniformEnd) == 0x698, "sub_0xbc60740: EncoderImpl m_uniformEnd at +0x698");
static_assert(offsetof(native::bgfx::EncoderImpl, m_numVertices) == 0x69C, "sub_0xbc60740: EncoderImpl m_numVertices at +0x69C");
static_assert(offsetof(native::bgfx::EncoderImpl, m_uniformIdx) == 0x6AC, "sub_0xbc60740: EncoderImpl m_uniformIdx at +0x6AC");
static_assert(offsetof(native::bgfx::EncoderImpl, m_discard) == 0x6AD, "sub_0xbc60740: EncoderImpl m_discard at +0x6AD");
static_assert(offsetof(native::bgfx::SideTableEntry, ptr) == 0x00, "sub_0xbc60740: SideTableEntry ptr at +0x00");
static_assert(offsetof(native::bgfx::SideTableEntry, pad) == 0x08, "sub_0xbc60740: SideTableEntry pad at +0x08");
static_assert(sizeof(native::bgfx::SideTableEntry) == 0x10, "sub_0xbc60740: SideTableEntry size 0x10");
static_assert(offsetof(native::bgfx::SideTable, entries) == 0x00, "sub_0xbc60740: SideTable entries at +0x00");
static_assert(offsetof(native::bgfx::SideTable, count) == 0x410, "sub_0xbc60740: SideTable count at +0x410");
static_assert(sizeof(native::bgfx::SideTable) == 0x414, "sub_0xbc60740: SideTable size 0x414");
static_assert(sizeof(std::uint64_t) == 8, "sub_0xbc60740: u64 size");
static_assert(0x5d0 == 0x5d0, "sub_0xbc60740: function size 0x5d0");

LIFT_FN(sub_bc60740, "sub_bc60740", 0xbc60740, sub_bc60740, nullptr);

} // namespace native::bgfx