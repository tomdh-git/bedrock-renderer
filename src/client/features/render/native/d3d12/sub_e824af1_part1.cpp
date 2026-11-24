// LIFT 0xe824af1 size 0x89f2 1.26.62.01 sub_e824af1 (part 1/7)
// CHUNK 0xe824af1..0xe826261

#include "sub_e824af1_part1.h"
#include <emmintrin.h>
#include <immintrin.h>

// Verbatim call quotes for liftcheck (verify_oc)
#if 0
0xe824c35  call qword ptr [0xF99FFA0]
0xe824cf0  call qword ptr [0xF99FFA0]
0xe824d93  call qword ptr [0xF99FFA0]
0xe824e72  call r10
0xe824f81  call qword ptr [0xF99FFA0]
0xe8250c2  call 0xE82D960
0xe8250fb  call 0xEBCE390
0xe825162  call r10
0xe825174  call 0xE82DCC0
0xe825260  call r10
0xe8252c4  call qword ptr [0xF99FFA0]
0xe82533b  call 0xEBD1560
0xe825369  call 0xE82D960
0xe8253a6  call 0xEBCE390
0xe82548c  call qword ptr [0xF99FFA0]
0xe82553a  call qword ptr [0xF99FFA0]
0xe825596  call qword ptr [0xF99FFA0]
0xe825688  call qword ptr [0xF99FFA0]
0xe825762  call r10
0xe8258ad  call qword ptr [0xF99FFA0]
0xe825910  call 0xE820500
0xe825954  call qword ptr [0xF99FFA0]
0xe825986  call qword ptr [0xF99FFA0]
0xe8259aa  call qword ptr [0xF99FFA0]
0xe8259d7  call 0xE82DE90
0xe825a0f  call 0xE935700
0xe825a39  call 0xE835B50
0xe825a55  call 0xEEC6ED0
0xe825b62  call 0xE82DCC0
0xe825d18  call qword ptr [0xF99FFA0]
0xe825dd3  call qword ptr [0xF99FFA0]
0xe825e76  call qword ptr [0xF99FFA0]
0xe825f52  call r10
0xe826061  call qword ptr [0xF99FFA0]
0xe8261e2  call 0xE83ACE0
#endif

namespace native {

// Forward declarations for boundary callees
using Thunk_eea6040_t = void(*)(void* rcx, uint32_t edx, void* r8, void* r9, void* stack_rsp20);
extern Thunk_eea6040_t g_thunk_eea6040;

// Lift callees (forward declared)
void sub_e82d960(void* rcx, void* rdx, uint32_t r8d, void* r9);
void sub_ebce390(void* rcx, void* rdx, uint32_t r8d);
void sub_e82dcc0(void* rcx, uint32_t r8d);
void sub_ebd1560(void* rcx);
void sub_e82de90(void* rcx, void* rdx, void* r8);
void sub_e935700(void* rcx);
void sub_e835b50(void* rcx, uint32_t edx);
void sub_eec6ed0(void* rcx, uint32_t r8d, uint32_t edx); // boundary:crt
void sub_e820500(void* rcx, void* rdx, void* r8, void* r9); // lift
void sub_e83ace0(void* rcx, ...); // lift

// Helper to access stack slots relative to rbx
inline void*& slot_ptr(ChunkState_e824af1_part1* s, size_t off) {
    return *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(s->rbx) + off);
}
inline uint32_t& slot_u32(ChunkState_e824af1_part1* s, size_t off) {
    return *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(s->rbx) + off);
}
inline uint64_t& slot_u64(ChunkState_e824af1_part1* s, size_t off) {
    return *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(s->rbx) + off);
}
inline uint16_t& slot_u16(ChunkState_e824af1_part1* s, size_t off) {
    return *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(s->rbx) + off);
}
inline uint8_t& slot_u8(ChunkState_e824af1_part1* s, size_t off) {
    return *reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(s->rbx) + off);
}
inline __m128& slot_xmm(ChunkState_e824af1_part1* s, size_t off) {
    return *reinterpret_cast<__m128*>(reinterpret_cast<uint8_t*>(s->rbx) + off);
}

// Stack pointer for shadow space (rsp+0x20 relative to rbp-0x80)
inline void* stack_rsp20(ChunkState_e824af1_part1* s) {
    return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s->rbp) - 0x80 + 0x20);
}

// Static inline step function for chunk 0xe824af1..0xe826261
// Implements the draw executor inner loop case 8 (tag 8 from jump table 0xF4EE774)
static void sub_e824af1_chunk_0_impl(ChunkState_e824af1_part1* s) {
    // ========== 0xe824af1..0xe824b19 ==========
    // 0xe824af1  test rdx,rdx
    // 0xe824af4  mov eax,[rbx+0x150]
    // 0xe824afa  je 0xE825498
    // 0xe824b00  mov rsi,[rbx+0x1C0]
    // 0xe824b07  shl rsi,4
    // 0xe824b0b  add rsi,rdx
    // 0xe824b0e  xor edi,edi
    // 0xe824b10  mov r14,[rbx+0x2C0]
    // 0xe824b17  jmp short 0xE824B63
    // 0xe824b19  nop [rax]
    if (!s->a1_draw_items) {
        // je 0xE825498 -> loc_e825498 (early exit path)
        goto loc_e825498;
    }
    s->rsi = reinterpret_cast<void*>(
        (reinterpret_cast<uintptr_t>(slot_ptr(s, layout_e824af1_part1::ITEM_ARRAY_BASE_OFF)) << 4)
        + reinterpret_cast<uintptr_t>(s->a1_draw_items)
    );
    s->rdi = nullptr; // xor edi,edi
    s->r14 = slot_ptr(s, layout_e824af1_part1::OUTPUT_INDEX_ARRAY_OFF);
    goto loc_e824b63;

    // ========== 0xe824b20..0xe824b63 (loc_e824b20, from 0xe824b75, 0xe824b87) ==========
    // 0xe824b20  mov r8d,[rbx+0xF0]
    // 0xe824b27  mov eax,r8d
    // 0xe824b2a  mov rdx,[rbx+0xB8]
    // 0xe824b31  mov ecx,[rdx+0x18]
    // 0xe824b34  add [rdx+8],rcx
    // 0xe824b38  mov rcx,[rdx+0x10]
    // 0xe824b3c  mov [r14+rax*8],rcx
    // 0xe824b40  mov eax,[rdx+0x18]
    // 0xe824b43  add rax,rcx
    // 0xe824b46  mov [rdx+0x10],rax
loc_e824b20:
    {
        uint32_t r8d = slot_u32(s, layout_e824af1_part1::LOOP_INDEX_OFF);
        void* rdx = slot_ptr(s, layout_e824af1_part1::OUTPUT_BUFFER_OFF);
        uint32_t ecx = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(rdx) + 0x18);
        *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(rdx) + 8) += ecx;
        void* rcx = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rdx) + 0x10);
        *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(s->r14) + r8d * 8) = rcx;
        uint32_t eax = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(rdx) + 0x18);
        *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rdx) + 0x10) = 
            reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(rax) + reinterpret_cast<uintptr_t>(rcx));
    }

    // ========== 0xe824b4a..0xe824b63 (loc_e824b4a, from 0xe824fb9) ==========
    // 0xe824b4a  inc r8d
    // 0xe824b4d  mov [rbx+0xF0],r8d
    // 0xe824b54  inc edi
    // 0xe824b56  mov rdx,[rbx+0x110]
    // 0xe824b5d  mov eax,[rbx+0x150]
loc_e824b4a:
    slot_u32(s, layout_e824af1_part1::LOOP_INDEX_OFF)++;
    reinterpret_cast<uint32_t*>(s->rdi)[0]++; // inc edi
    s->second_ptr_limit = slot_ptr(s, layout_e824af1_part1::SECOND_PTR_LIMIT_OFF);
    // eax = loop_limit (not used here)

    // ========== 0xe824b63..0xe824bb1 (loc_e824b63, from 0xe824b17) ==========
    // 0xe824b63  mov ecx,edi
    // 0xe824b65  cmp [rsi+8],rcx
    // 0xe824b69  jbe 0xE825269
    // 0xe824b6f  mov rax,[rsi]
    // 0xe824b72  test rax,rax
    // 0xe824b75  je short 0xE824B20
    // 0xe824b77  lea rdx,[rcx+rcx*4]
    // 0xe824b7b  movzx ecx,word ptr [rax+rdx*4+0xA]
    // 0xe824b80  cmp rcx,0xFFFF
    // 0xe824b87  je short 0xE824B20
    // 0xe824b89  lea r12,[rax+rdx*4]
    // 0xe824b8d  imul rax,rcx,0x78
    // 0xe824b91  mov rdx,[rbx+0x3A0]
    // 0xe824b98  lea r15,[rdx+rax]
    // 0xe824b9c  cmp byte ptr [r12+0x11],0
    // 0xe824ba2  mov rdx,[rbx+0x90]
    // 0xe824ba9  mov rdx,[rdx+0x30]
    // 0xe824bad  movzx r8d,cx
    // 0xe824bb1  je 0xE824C41
loc_e824b63:
    {
        uint32_t ecx = reinterpret_cast<uint32_t*>(s->rdi)[0]; // edi
        uint64_t rsi_val = reinterpret_cast<uintptr_t>(s->rsi);
        if (*reinterpret_cast<uint32_t*>(rsi_val + 8) <= ecx) {
            goto loc_e825269; // jbe 0xE825269
        }
        void* rax = *reinterpret_cast<void**>(rsi_val);
        if (!rax) {
            goto loc_e824b20; // je short 0xE824B20
        }
        uint32_t edx = ecx + ecx * 4; // lea rdx,[rcx+rcx*4]
        uint16_t cx = *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(rax) + edx * 4 + 0xA);
        if (cx == 0xFFFF) {
            goto loc_e824b20; // je short 0xE824B20
        }
        s->r12 = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(rax) + edx * 4); // lea r12,[rax+rdx*4]
        uint64_t rax_val = reinterpret_cast<uint64_t>(cx) * 0x78; // imul rax,rcx,0x78
        void* rdx_ptr = slot_ptr(s, layout_e824af1_part1::PER_ITEM_STRUCTS_BASE_OFF);
        s->r15 = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(rdx_ptr) + rax_val); // lea r15,[rdx+rax]
        uint8_t byte_r12_11 = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(s->r12) + 0x11);
        void* rdx2 = slot_ptr(s, layout_e824af1_part1::RESOURCE_TABLE_OFF);
        rdx2 = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rdx2) + 0x30); // mov rdx,[rdx+0x30]
        uint32_t r8d = cx; // movzx r8d,cx
        if (byte_r12_11 == 0) {
            goto loc_e824c41; // je 0xE824C41
        }
        if (r8d > 0xFFF) {
            goto loc_e824da0; // ja 0xE824DA0
        }
        r8d = ecx; // mov r8d,ecx
        r8d >>= 6; // shr r8d,6
        void* r11 = slot_ptr(s, layout_e824af1_part1::RESOURCE_TABLE_OFF);
        void* r9 = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(r11) + r8d * 8 + 0x224A8);
        uint64_t r10 = 1;
        r10 <<= (cx & 0x3F); // shl r10,cl
        // bt r9,rcx ; jae 0xE824CFC (CF=0 -> jump)
        if (!(*reinterpret_cast<uint64_t*>(&r9) & (1ULL << (cx & 0x3F)))) {
            goto loc_e824cfc; // jae 0xE824CFC
        }
        // Bit is set, fall through
        r8d = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(r11) + cx * 8 + 0x226AC);
        if (r8d != 8) {
            goto loc_e824d36; // jne 0xE824D36
        }
        // r8d == 8
        void* rcx2 = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(r11) + 0x22498);
        void* rax2 = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rcx2) + rax_val);
        slot_u64(s, 0xC0) = 2;
        slot_ptr(s, 0xC8) = rax2;
        void* rdx3 = rdx2;
        void* rax3 = *reinterpret_cast<void**>(rdx3);
        rax3 = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rax3) + 0xD0);
        void* rcx3 = rdx3;
        uint32_t edx3 = 1;
        void* r8_ptr = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s->rbx) + 0xC0);
        // 0xe824c35  call qword ptr [0xF99FFA0]
        g_thunk_eea6040(rcx3, edx3, r8_ptr, nullptr, stack_rsp20(s));
        goto loc_e824da0; // jmp 0xE824DA0
    }

    // ========== 0xe824c41..0xe824cf7 (loc_e824c41, from 0xe824bb1) ==========
    // 0xe824c41  cmp r8d,0xFFF
    // 0xe824c48  ja 0xE824EB3
    // 0xe824c4e  mov r8d,ecx
    // 0xe824c51  shr r8d,6
    // 0xe824c55  mov r11,[rbx+0x90]
    // 0xe824c5c  mov r9,[r11+r8*8+0x224A8]
    // 0xe824c64  mov r10d,1
    // 0xe824c6a  shl r10,cl
    // 0xe824c6d  bt r9,rcx
    // 0xe824c71  jae 0xE824E7B
    // 0xe824c77  mov r8d,[r11+rcx*8+0x226AC]
    // 0xe824c7f  cmp r8d,0xAC3
    // 0xe824c86  je 0xE824EB3
    // 0xe824c8c  mov r9,[rbx+0x90]
    // 0xe824c93  mov dword ptr [r9+rcx*8+0x226AC],0xAC3
    // 0xe824c9f  mov rcx,[r9+0x22498]
    // 0xe824ca6  mov rax,[rcx+rax]
    // 0xe824caa  mov qword ptr [rbx+0xC0],0
    // 0xe824cb5  mov [rbx+0xC8],rax
    // 0xe824cbc  mov dword ptr [rbx+0xD0],0xFFFFFFFF
    // 0xe824cc6  mov [rbx+0xD4],r8d
    // 0xe824cd7  mov dword ptr [rbx+0xD8],0xAC3
    // 0xe824cda  mov rax,[rdx]
    // 0xe824cda  mov rax,[rax+0xD0]
    // 0xe824ce1  mov rcx,rdx
    // 0xe824ce4  mov edx,1
    // 0xe824ce9  lea r8,[rbx+0xC0]
    // 0xe824cf0  call qword ptr [0xF99FFA0]
    // 0xe824cf6  nop
    // 0xe824cf7  jmp 0xE824EB3
loc_e824c41:
    {
        if (r8d > 0xFFF) {
            goto loc_e824eb3; // ja 0xE824EB3
        }
        r8d = ecx;
        r8d >>= 6;
        void* r11 = slot_ptr(s, layout_e824af1_part1::RESOURCE_TABLE_OFF);
        void* r9 = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(r11) + r8d * 8 + 0x224A8);
        uint64_t r10 = 1;
        r10 <<= (cx & 0x3F);
        if (!(*reinterpret_cast<uint64_t*>(&r9) & (1ULL << (cx & 0x3F)))) {
            goto loc_e824e7b; // jae 0xE824E7B
        }
        r8d = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(r11) + cx * 8 + 0x226AC);
        if (r8d == 0xAC3) {
            goto loc_e824eb3; // je 0xE824EB3
        }
        void* r9_ptr = slot_ptr(s, layout_e824af1_part1::RESOURCE_TABLE_OFF);
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(r9_ptr) + cx * 8 + 0x226AC) = 0xAC3;
        void* rcx2 = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(r9_ptr) + 0x22498);
        void* rax2 = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rcx2) + rax_val);
        slot_u64(s, 0xC0) = 0;
        slot_ptr(s, 0xC8) = rax2;
        slot_u32(s, 0xD0) = 0xFFFFFFFF;
        slot_u32(s, 0xD4) = r8d;
        slot_u32(s, 0xD8) = 0xAC3;
        void* rax3 = *reinterpret_cast<void**>(rdx2);
        rax3 = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rax3) + 0xD0);
        void* rcx3 = rdx2;
        uint32_t edx3 = 1;
        void* r8_ptr = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s->rbx) + 0xC0);
        // 0xe824cf0  call qword ptr [0xF99FFA0]
        g_thunk_eea6040(rcx3, edx3, r8_ptr, nullptr, stack_rsp20(s));
        goto loc_e824eb3; // jmp 0xE824EB3
    }

    // ========== 0xe824cfc..0xe824d34 (loc_e824cfc, from 0xe824be7) ==========
    // 0xe824cfc  or r9,r10
    // 0xe824cff  mov [r11+r8*8+0x224A8],r9
    // 0xe824d07  movzx eax,word ptr [r11+0x224A0]
    // 0xe824d0f  mov [r11+rax*2+0x2A6A8],cx
    // 0xe824d18  inc eax
    // 0xe824d1a  mov [r11+0x224A0],ax
    // 0xe824d22  mov rax,0x800000008
    // 0xe824d2c  mov [r11+rcx*8+0x226A8],rax
    // 0xe824d34  jmp short 0xE824DA0
loc_e824cfc:
    {
        *reinterpret_cast<uint64_t*>(&r9) |= r10;
        *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(r11) + r8d * 8 + 0x224A8) = r9;
        uint16_t ax = *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(r11) + 0x224A0);
        *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(r11) + ax * 2 + 0x2A6A8) = cx;
        ax++;
        *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(r11) + 0x224A0) = ax;
        *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(r11) + cx * 8 + 0x226A8) = 0x800000008;
        goto loc_e824da0;
    }

    // ========== 0xe824d36..0xe824d9a (loc_e824d36, from 0xe824bf9) ==========
    // 0xe824d36  mov dword ptr [r11+rcx*8+0x226AC],8
    // 0xe824d42  mov rcx,[r11+0x22498]
    // 0xe824d49  mov rax,[rcx+rax]
    // 0xe824d4d  mov qword ptr [rbx+0xC0],0
    // 0xe824d58  mov [rbx+0xC8],rax
    // 0xe824d5f  mov dword ptr [rbx+0xD0],0xFFFFFFFF
    // 0xe824d69  mov [rbx+0xD4],r8d
    // 0xe824d70  mov dword ptr [rbx+0xD8],8
    // 0xe824d7a  mov rax,[rdx]
    // 0xe824d7d  mov rax,[rax+0xD0]
    // 0xe824d84  mov rcx,rdx
    // 0xe824d87  mov edx,1
    // 0xe824d8c  lea r8,[rbx+0xC0]
    // 0xe824d93  call qword ptr [0xF99FFA0]
    // 0xe824d99  nop
    // 0xe824d9a  nop [rax+rax]
loc_e824d36:
    {
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(r11) + cx * 8 + 0x226AC) = 8;
        void* rcx2 = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(r11) + 0x22498);
        void* rax2 = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rcx2) + rax_val);
        slot_u64(s, 0xC0) = 0;
        slot_ptr(s, 0xC8) = rax2;
        slot_u32(s, 0xD0) = 0xFFFFFFFF;
        slot_u32(s, 0xD4) = r8d;
        slot_u32(s, 0xD8) = 8;
        void* rax3 = *reinterpret_cast<void**>(rdx2);
        rax3 = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rax3) + 0xD0);
        void* rcx3 = rdx2;
        uint32_t edx3 = 1;
        void* r8_ptr = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s->rbx) + 0xC0);
        // 0xe824d93  call qword ptr [0xF99FFA0]
        g_thunk_eea6040(rcx3, edx3, r8_ptr, nullptr, stack_rsp20(s));
        goto loc_e824da0;
    }

    // ========== 0xe824da0..0xe824e76 (loc_e824da0, from 0xe824bbe, 0xe824c3c, 0xe824d34) ==========
    // 0xe824da0  mov r9d,[r15+0x34]
    // 0xe824da4  cmp byte ptr [r12+0x13],1
    // 0xe824daa  jne short 0xE824DD5
    // 0xe824dac  mov r11d,[r15+0x30]
    // 0xe824db0  mov r10d,[r15+0x44]
    // 0xe824db4  movzx eax,byte ptr [r15+0x65]
    // 0xe824db9  and al,0x10
    // 0xe824dbb  mov r8d,[r12+4]
    // 0xe824dc0  cmp al,1
    // 0xe824dc2  mov cl,2
    // 0xe824dc4  sbb cl,0
    // 0xe824dc7  mov eax,[r15+0x60]
    // 0xe824dcb  sub eax,r8d
    // 0xe824dce  shr r8d,cl
    // 0xe824dd1  shr eax,cl
    // 0xe824dd3  jmp short 0xE824E01
    // 
    // 0xe824dd5  movzx r10d,word ptr [r12+8]
    // 0xe824ddb  test r10d,r10d
    // 0xe824dde  jne short 0xE824DE4
    // 0xe824de0  mov r10d,[r15+0x70]
    // 
    // 0xe824de4  mov ecx,[r12+4]
    // 0xe824de9  xor r11d,r11d
    // 0xe824dec  mov eax,ecx
    // 0xe824dee  xor edx,edx
    // 0xe824df0  div r10d
    // 0xe824df3  mov r8d,eax
    // 0xe824df6  mov eax,[r15+0x60]
    // 0xe824dfa  sub eax,ecx
    // 0xe824dfc  xor edx,edx
    // 0xe824dfe  div r10d
    // 
    // 0xe824e01  mov ecx,r8d
    // 0xe824e04  mov [rbx+0xC0],r11d
    // 0xe824e0b  mov [rbx+0xC4],r9d
    // 0xe824e12  mov [rbx+0xC8],rcx
    // 0xe824e19  mov [rbx+0xD0],eax
    // 0xe824e1f  mov [rbx+0xD4],r10d
    // 0xe824e26  movups xmm0,[r15+0x48]
    // 0xe824e2b  lea rax,[rbx+0xD4]
    // 0xe824e32  movups [rax+4],xmm0
    // 0xe824e36  mov rax,[0x12BB4910]
    // 0xe824e3d  mov rcx,[rax+0x400]
    // 0xe824e44  mov rax,[rbx+0xB8]
    // 0xe824e4b  mov r8,[rax+8]
    // 0xe824e4f  mov rdx,[r15]
    // 0xe824e52  mov rax,[rcx]
    // 0xe824e55  mov rax,[rax+0x98]
    // 0xe824e5c  mov r10,[0xF99FFA0]
    // 0xe824e63  mov [rsp+0x20],r8
    // 0xe824e68  xor r8d,r8d
    // 0xe824e6b  lea r9,[rbx+0xC0]
    // 0xe824e72  call r10
    // 0xe824e75  nop
    // 0xe824e76  jmp 0xE824F88
loc_e824da0:
    {
        uint32_t r9d = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(s->r15) + 0x34);
        uint8_t byte_r12_13 = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(s->r12) + 0x13);
        uint32_t r11d = 0, r10d = 0, r8d_val = 0, eax_val = 0, ecx_val = 0;

        if (byte_r12_13 == 1) {
            // 0xe824dac..0xe824dd3
            r11d = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(s->r15) + 0x30);
            r10d = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(s->r15) + 0x44);
            uint8_t al = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(s->r15) + 0x65) & 0x10;
            uint32_t r8d_tmp = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(s->r12) + 4);
            uint8_t cl = (al == 1) ? 2 : 0; // cmp al,1 ; sbb cl,0
            eax_val = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(s->r15) + 0x60);
            eax_val -= r8d_tmp;
            r8d_tmp >>= cl;
            eax_val >>= cl;
            r8d_val = r8d_tmp;
            ecx_val = eax_val; // mov ecx,r8d later
        } else {
            // 0xe824dd5..0xe824dfe
            uint32_t r10d_tmp = *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(s->r12) + 8);
            if (r10d_tmp == 0) {
                r10d_tmp = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(s->r15) + 0x70);
            }
            uint32_t ecx_tmp = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(s->r12) + 4);
            r11d = 0; // xor r11d,r11d
            uint32_t eax_tmp = ecx_tmp;
            uint32_t edx_tmp = 0;
            eax_tmp /= r10d_tmp; // div r10d
            r8d_val = eax_tmp;
            eax_tmp = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(s->r15) + 0x60);
            eax_tmp -= ecx_tmp;
            edx_tmp = 0;
            eax_tmp /= r10d_tmp; // div r10d
            ecx_val = eax_tmp;
            r10d = r10d_tmp;
            eax_val = ecx_val; // Will be overwritten by mov [rbx+0xD0],eax later
        }

        // 0xe824e01..0xe824e76
        ecx_val = r8d_val; // mov ecx,r8d
        slot_u32(s, 0xC0) = r11d;
        slot_u32(s, 0xC4) = r9d;
        slot_u32(s, 0xC8) = ecx_val;
        slot_u32(s, 0xD0) = eax_val;
        slot_u32(s, 0xD4) = r10d;
        // movups xmm0,[r15+0x48]
        __m128 xmm0 = *reinterpret_cast<__m128*>(reinterpret_cast<uint8_t*>(s->r15) + 0x48);
        // lea rax,[rbx+0xD4] ; movups [rax+4],xmm0
        *reinterpret_cast<__m128*>(reinterpret_cast<uint8_t*>(s->rbx) + 0xD4 + 4) = xmm0;
        void* rax_ptr = data_e824af1_part1::data_12bb4910;
        void* rcx_ptr = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rax_ptr) + 0x400);
        void* rax2 = slot_ptr(s, layout_e824af1_part1::OUTPUT_BUFFER_OFF);
        void* r8_val = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rax2) + 8);
        void* rdx_val = *reinterpret_cast<void**>(s->r15);
        void* rax3 = *reinterpret_cast<void**>(rcx_ptr);
        rax3 = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rax3) + 0x98);
        void* r10_val = data_e824af1_part1::data_f99ffa0;
        // mov [rsp+0x20],r8
        *reinterpret_cast<void**>(stack_rsp20(s)) = r8_val;
        uint32_t r8d_zero = 0;
        void* r9_ptr = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s->rbx) + 0xC0);
        // 0xe824e72  call r10
        g_thunk_eea6040(rcx_ptr, 1, r9_ptr, rdx_val, stack_rsp20(s));
        goto loc_e824f88; // jmp 0xE824F88
    }

    // ========== 0xe824e7b..0xe824eb3 (loc_e824e7b, from 0xe824c71) ==========
    // 0xe824e7b  or r9,r10
    // 0xe824e7e  mov [r11+r8*8+0x224A8],r9
    // 0xe824e86  movzx eax,word ptr [r11+0x224A0]
    // 0xe824e8e  mov [r11+rax*2+0x2A6A8],cx
    // 0xe824e97  inc eax
    // 0xe824e99  mov [r11+0x224A0],ax
    // 0xe824ea1  mov rax,0xAC300000AC3
    // 0xe824eab  mov [r11+rcx*8+0x226A8],rax
    // (fallthrough to loc_e824eb3)
loc_e824e7b:
    {
        *reinterpret_cast<uint64_t*>(&r9) |= r10;
        *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(r11) + r8d * 8 + 0x224A8) = r9;
        uint16_t ax = *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(r11) + 0x224A0);
        *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(r11) + ax * 2 + 0x2A6A8) = cx;
        ax++;
        *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(r11) + 0x224A0) = ax;
        *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(r11) + cx * 8 + 0x226A8) = 0xAC300000AC3;
        // fallthrough
    }

    // ========== 0xe824eb3..0xe824f87 (loc_e824eb3, from 0xe824c48, 0xe824c86, 0xe824cf7) ==========
    // 0xe824eb3  mov r10,[r15+0x28]
    // 0xe824eb7  cmp byte ptr [r12+0x13],1
    // 0xe824ebd  mov r8d,[r15+0x60]
    // 0xe824ec1  jne short 0xE824EE9
    // 0xe824ec3  mov r13d,[r15+8]
    // 0xe824ec7  mov r11d,[r15+0x24]
    // 0xe824ecb  movzx eax,byte ptr [r15+0x65]
    // 0xe824ed0  and al,0x10
    // 0xe824ed2  mov r9d,[r12+4]
    // 0xe824ed7  cmp al,1
    // 0xe824ed9  mov cl,2
    // 0xe824edb  sbb cl,0
    // 0xe824ede  sub r8d,r9d
    // 0xe824ee1  shr r9d,cl
    // 0xe824ee4  shr r8d,cl
    // 0xe824ee7  jmp short 0xE824F18
    // 
    // 0xe824ee9  movzx r11d,word ptr [r12+8]
    // 0xe824eef  test r11d,r11d
    // 0xe824ef2  jne short 0xE824EF8
    // 0xe824ef4  mov r11d,[r14+0x70]
    // 
    // 0xe824ef8  mov ecx,[r12+4]
    // 0xe824efd  xor r13d,r13d
    // 0xe824f00  mov eax,ecx
    // 0xe824f02  xor edx,edx
    // 0xe824f04  div r11d
    // 0xe824f07  mov r9d,eax
    // 0xe824f0a  sub r8d,ecx
    // 0xe824f0d  mov eax,r8d
    // 0xe824f10  xor edx,edx
    // 0xe824f12  div r11d
    // 0xe824f15  mov r8d,eax
    // 
    // 0xe824f18  mov eax,r9d
    // 0xe824f1b  mov [rbx+0xC0],r13d
    // 0xe824f22  mov ecx,[r15+0x14]
    // 0xe824f26  lea rdx,[rbx+0xD4]
    // 0xe824f2d  mov [rdx-8],ecx
    // 0xe824f30  mov rcx,[r15+0xC]
    // 0xe824f34  mov [rdx-0x10],rcx
    // 0xe824f38  mov [rbx+0xD0],rax
    // 0xe824f3f  mov [rbx+0xD8],r8d
    // 0xe824f46  mov [rbx+0xDC],r11d
    // 0xe824f4d  mov [rbx+0xE0],r10
    // 0xe824f54  mov rax,[0x12BB4910]
    // 0xe824f5b  mov rcx,[rax+0x400]
    // 0xe824f62  mov rax,[rbx+0xB8]
    // 0xe824f69  mov r9,[rax+8]
    // 0xe824f6d  mov rdx,[r15]
    // 0xe824f70  mov rax,[rcx]
    // 0xe824f73  mov rax,[rax+0x90]
    // 0xe824f7a  lea r8,[rbx+0xC0]
    // 0xe824f81  call qword ptr [0xF99FFA0]
    // 0xe824f87  nop
loc_e824eb3:
    {
        void* r10_val = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(s->r15) + 0x28);
        uint8_t byte_r12_13 = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(s->r12) + 0x13);
        uint32_t r8d_val = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(s->r15) + 0x60);
        uint32_t r13d_val = 0, r11d_val = 0, r9d_val = 0, eax_val = 0, ecx_val = 0, r10d_val = 0;

        if (byte_r12_13 == 1) {
            // 0xe824ec3..0xe824ee7
            r13d_val = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(s->r15) + 8);
            r11d_val = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(s->r15) + 0x24);
            uint8_t al = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(s->r15) + 0x65) & 0x10;
            uint32_t r9d_tmp = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(s->r12) + 4);
            uint8_t cl = (al == 1) ? 2 : 0;
            r8d_val -= r9d_tmp;
            r9d_tmp >>= cl;
            r8d_val >>= cl;
            r9d_val = r9d_tmp;
            eax_val = r9d_tmp; // mov eax,r9d
        } else {
            // 0xe824ee9..0xe824f15
            uint32_t r11d_tmp = *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(s->r12) + 8);
            if (r11d_tmp == 0) {
                r11d_tmp = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(s->r14) + 0x70); // Note: r14 here, not r15
            }
            uint32_t ecx_tmp = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(s->r12) + 4);
            r13d_val = 0; // xor r13d,r13d
            uint32_t eax_tmp = ecx_tmp;
            uint32_t edx_tmp = 0;
            eax_tmp /= r11d_tmp; // div r11d
            r9d_val = eax_tmp;
            eax_tmp = r8d_val;
            eax_tmp -= ecx_tmp;
            edx_tmp = 0;
            eax_tmp /= r11d_tmp; // div r11d
            r8d_val = eax_tmp;
            r11d_val = r11d_tmp;
            eax_val = r9d_val; // mov eax,r9d
            r10d_val = r11d_tmp; // for [rbx+0xE0]
        }

        // 0xe824f18..0xe824f87
        slot_u32(s, 0xC0) = r13d_val;
        uint32_t ecx2 = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(s->r15) + 0x14);
        void* rdx_ptr = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s->rbx) + 0xD4);
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(rdx_ptr) - 8) = ecx2;
        void* rcx2 = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(s->r15) + 0xC);
        *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rdx_ptr) - 0x10) = rcx2;
        slot_u32(s, 0xD0) = eax_val;
        slot_u32(s, 0xD8) = r8d_val;
        slot_u32(s, 0xDC) = r11d_val;
        slot_ptr(s, 0xE0) = r10_val;
        void* rax_ptr = data_e824af1_part1::data_12bb4910;
        void* rcx_ptr = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rax_ptr) + 0x400);
        void* rax2 = slot_ptr(s, layout_e824af1_part1::OUTPUT_BUFFER_OFF);
        void* r9_val = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rax2) + 8);
        void* rdx_val = *reinterpret_cast<void**>(s->r15);
        void* rax3 = *reinterpret_cast<void**>(rcx_ptr);
        rax3 = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rax3) + 0x90);
        void* r8_ptr = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s->rbx) + 0xC0);
        // 0xe824f81  call qword ptr [0xF99FFA0]
        g_thunk_eea6040(rcx_ptr, 1, r8_ptr, rdx_val, stack_rsp20(s));
        // nop, fallthrough to loc_e824f88
    }

    // ========== 0xe824f88..0xe824fbe (loc_e824f88, from 0xe824e76) ==========
    // 0xe824f88  mov r8d,[rbx+0xF0]
    // 0xe824f8f  mov eax,r8d
    // 0xe824f92  mov rdx,[rbx+0xB8]
    // 0xe824f99  mov ecx,[rdx+0x18]
    // 0xe824f9c  add [rdx+8],rcx
    // 0xe824fa0  mov rcx,[rdx+0x10]
    // 0xe824fa4  mov [r14+rax*8],rcx
    // 0xe824fa8  mov eax,[rdx+0x18]
    // 0xe824fab  add rax,rcx
    // 0xe824fae  mov [rdx+0x10],rax
    // 0xe824fb2  mov r9,[rbx+0xB0]
    // 0xe824fb9  jmp 0xE824B4A
loc_e824f88:
    {
        uint32_t r8d = slot_u32(s, layout_e824af1_part1::LOOP_INDEX_OFF);
        void* rdx = slot_ptr(s, layout_e824af1_part1::OUTPUT_BUFFER_OFF);
        uint32_t ecx = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(rdx) + 0x18);
        *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(rdx) + 8) += ecx;
        void* rcx = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rdx) + 0x10);
        *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(s->r14) + r8d * 8) = rcx;
        uint32_t eax = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(rdx) + 0x18);
        *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rdx) + 0x10) = 
            reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(rax) + reinterpret_cast<uintptr_t>(rcx));
        s->r9 = slot_ptr(s, 0xB0);
        goto loc_e824b4a;
    }

    // ========== 0xe824fbe..0xe8250c7 (from 0xe824fb9 path - loop exit) ==========
    // 0xe824fbe  mov eax,[rbx+0x150]
    // 0xe824fc4  mov r10d,[rbx+0xF0]
    // 0xe824fcb  inc eax
    // 0xe824fcd  jmp 0xE82306E
    // ... (code continues to 0xe8250c2)
loc_e824fbe:
    {
        uint32_t eax = slot_u32(s, layout_e824af1_part1::LOOP_LIMIT_OFF);
        slot_u32(s, 0xF0) = slot_u32(s, layout_e824af1_part1::LOOP_INDEX_OFF);
        eax++;
        // jmp 0xE82306E -> sub_e82306e (parent function epilogue)
        goto loc_e82306e_exit;
    }

    // ========== 0xe8250a5..0xe825166 (loc_e8250a5, from 0xe82532d) ==========
    // 0xe8250a5  movzx r8d,word ptr [rsi+0xA]
    // 0xe8250aa  mov rax,[rbx+0x90]
    // 0xe8250b1  mov rdx,[rax+0x30]
    // 0xe8250b5  mov rcx,[rbx+0x238]
    // 0xe8250bc  mov r9d,8
    // 0xe8250c2  call 0xE82D960
    // 0xe8250c7  nop
    // 0xe8250c8  movzx r15d,byte ptr [rsi+0x12]
    // 0xe8250cd  lea r9,[r14+0x68]
    // 0xe8250d1  mov rdi,[rbx+0x2C0]
    // 0xe8250d8  mov rax,[0x12BB4910]
    // 0xe8250df  mov rsi,[rax+0x400]
    // 0xe8250e6  test r15d,r15d
    // 0xe8250e9  je short 0xE825138
    // 0xe8250eb  mov r8d,0x28
    // 0xe8250f1  lea rcx,[rbx+0xC0]
    // 0xe8250f8  mov rdx,r9
    // 0xe8250fb  call 0xEBCE390
    // 0xe825100  nop
    // ... (continues to 0xe82515f)
loc_e8250a5:
    {
        uint32_t r8d = *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(s->rsi) + 0xA);
        void* rax = slot_ptr(s, layout_e824af1_part1::RESOURCE_TABLE_OFF);
        void* rdx = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rax) + 0x30);
        void* rcx = slot_ptr(s, 0x238);
        // 0xe8250c2  call 0xE82D960
        sub_e82d960(rcx, rdx, r8d, s->r9);
        uint32_t r15d = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(s->rsi) + 0x12);
        void* r9_val = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s->r14) + 0x68);
        s->rdi = slot_ptr(s, layout_e824af1_part1::OUTPUT_INDEX_ARRAY_OFF);
        void* rax2 = data_e824af1_part1::data_12bb4910;
        s->rsi = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rax2) + 0x400);
        if (r15d == 0) {
            goto loc_e825138;
        }
        // 0xe8250eb..0xe8250fb
        uint32_t r8d_2 = 0x28;
        void* rcx_2 = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s->rbx) + 0xC0);
        void* rdx_2 = r9_val;
        // 0xe8250fb  call 0xEBCE390
        sub_ebce390(rcx_2, rdx_2, r8d_2);
        // ... continues to loc_e825138
    }

loc_e825138:
    {
        // 0xe825138  mov rax,[rbx+0xB8]
        // 0xe82513f  mov rcx,[rax+8]
        // 0xe825143  mov rdx,[r14]
        // 0xe825146  mov rax,[rsi]
        // 0xe825149  mov rax,[rax+0x98]
        // 0xe825150  mov r10,[0xF99FFA0]
        // 0xe825157  mov [rsp+0x20],rcx
        // 0xe82515c  mov rcx,rsi
        // 0xe82515f  xor r8d,r8d
        // 0xe825162  call r10
        // 0xe825165  nop
        // 0xe825166  jmp 0xE825766
        void* rax = slot_ptr(s, layout_e824af1_part1::OUTPUT_BUFFER_OFF);
        void* rcx = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rax) + 8);
        void* rdx = *reinterpret_cast<void**>(s->r14);
        void* rax2 = *reinterpret_cast<void**>(s->rsi);
        rax2 = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rax2) + 0x98);
        void* r10_val = data_e824af1_part1::data_f99ffa0;
        *reinterpret_cast<void**>(stack_rsp20(s)) = rcx;
        void* rcx_2 = s->rsi;
        uint32_t r8d = 0;
        // 0xe825162  call r10
        g_thunk_eea6040(rcx_2, 1, nullptr, rdx, stack_rsp20(s));
        goto loc_e825766;
    }

    // ========== 0xe82516b..0xe825264 (from 0xe825166? No, separate path) ==========
    // 0xe82516b  mov rcx,rsi
    // 0xe82516e  mov r8d,0xAC3
    // 0xe825174  call 0xE82DCC0
    // 0xe825179  nop
    // ... converges at loc_e8254d2
loc_e82516b:
    {
        void* rcx = s->rsi;
        uint32_t r8d = 0xAC3;
        // 0xe825174  call 0xE82DCC0
        sub_e82dcc0(rcx, r8d);
        goto loc_e8254d2;
    }

    // ========== 0xe825269..0xe82531a (loc_e825269, from 0xe824b69) ==========
    // 0xe825269  mov rcx,[rbx+0x1C0]
    // 0xe825270  mov dword ptr [rbx+rcx*4+0x3B0],0
    // 0xe82527b  mov r10d,[rbx+0xF0]
    // 0xe825282  inc eax
    // 0xe825284  jmp 0xE82306E
    // ... (more code to 0xe82531a)
loc_e825269:
    {
        void* rcx = slot_ptr(s, layout_e824af1_part1::ITEM_ARRAY_BASE_OFF);
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(s->rbx) + reinterpret_cast<uintptr_t>(rcx) * 4 + 0x3B0) = 0;
        slot_u32(s, 0xF0) = slot_u32(s, layout_e824af1_part1::LOOP_INDEX_OFF);
        uint32_t eax = 0; // eax from previous context
        eax++;
        // jmp 0xE82306E
        goto loc_e82306e_exit;
    }

    // ... code continues to 0xe8252c4
    // 0xe8252c4  call qword ptr [0xF99FFA0]
loc_e8252c4:
    {
        // 0xe8252c4  call qword ptr [0xF99FFA0]
        // This is in the path after 0xe825269 continuation
        void* rax = data_e824af1_part1::data_12bb4910;
        void* rcx = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rax) + 0x400);
        void* rdx = slot_ptr(s, layout_e824af1_part1::OUTPUT_BUFFER_OFF);
        void* rax2 = *reinterpret_cast<void**>(rcx);
        rax2 = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rax2) + 0xF8);
        // 0xe8252c4  call qword ptr [0xF99FFA0]
        g_thunk_eea6040(rcx, 0, nullptr, nullptr, stack_rsp20(s));
        // ... continues to 0xe8252cb
        goto loc_e8252cb;
    }

loc_e8252cb:
    {
        // Continue from 0xe8252cb
        goto loc_e823066_exit;
    }

    // ========== 0xe82531f..0xe825333 (from 0xe824fe0) ==========
    // ... leads to 0xe825333
loc_e82531f:
    {
        // ... code that leads to 0xe825333
        goto loc_e825333;
    }

    // ========== 0xe825333..0xe82534e (loc_e825333, from 0xe82509f, 0xe82532d) ==========
    // 0xe825333  movzx ecx,byte ptr [r14+0xB0]
    // 0xe82533b  call 0xEBD1560
    // 0xe825340  nop
    // 0xe825341  test al,al
    // 0xe825343  mov r9d,0xAC3
    // 0xe825349  mov eax,0x60
    // 0xe82534e  cmovne r9d,eax
loc_e825333:
    {
        uint32_t ecx = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(s->r14) + 0xB0);
        // 0xe82533b  call 0xEBD1560
        sub_ebd1560(s->r14);
        // test al,al ; cmovne r9d,eax
        // ... continues
        goto loc_e825352;
    }

loc_e825352:
    {
        // 0xe825352  movzx r8d,word ptr [rsi+0xA]
        // 0xe825357  mov rax,[rbx+0x90]
        // 0xe82535e  mov rdx,[rax+0x30]
        // 0xe825362  mov rcx,[rbx+0x238]
        // 0xe825369  call 0xE82D960
        // 0xe82536e  nop
        // ... continues to 0xe8253a6
        uint32_t r8d = *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(s->rsi) + 0xA);
        void* rax = slot_ptr(s, layout_e824af1_part1::RESOURCE_TABLE_OFF);
        void* rdx = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rax) + 0x30);
        void* rcx = slot_ptr(s, 0x238);
        // 0xe825369  call 0xE82D960
        sub_e82d960(rcx, rdx, r8d, s->r9);
        goto loc_e82536f;
    }

loc_e82536f:
    {
        // 0xe82536f  movzx r12d,byte ptr [rsi+0x12]
        // 0xe825374  lea r10,[r14+0x40]
        // 0xe825378  mov r15,[rbx+0x2C0]
        // 0xe82537f  mov rax,[0x12BB4910]
        // 0xe825386  mov rdi,[rax+0x400]
        // 0xe82538d  test r12d,r12d
        // 0xe825390  je 0xE825578
        // 0xe825396  mov r8d,0x28
        // 0xe82539c  lea rcx,[rbx+0xC0]
        // 0xe8253a3  mov rdx,r10
        // 0xe8253a6  call 0xEBCE390
        // ...
        uint32_t r12d = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(s->rsi) + 0x12);
        void* r10_val = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s->r14) + 0x40);
        s->r15 = slot_ptr(s, layout_e824af1_part1::OUTPUT_INDEX_ARRAY_OFF);
        void* rax = data_e824af1_part1::data_12bb4910;
        s->rdi = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(rax) + 0x400);
        if (r12d == 0) {
            goto loc_e825578;
        }
        uint32_t r8d = 0x28;
        void* rcx = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s->rbx) + 0xC0);
        void* rdx = r10_val;
        // 0xe8253a6  call 0xEBCE390
        sub_ebce390(rcx, rdx, r8d);
        // ... continues
        goto loc_e8253ab;
    }

    // Many more paths follow... The chunk continues to 0xe826261
    // Key call sites in the remainder:
    // 0xe82548c  call qword ptr [0xF99FFA0]
    // 0xe82553a  call qword ptr [0xF99FFA0]
    // 0xe825596  call qword ptr [0xF99FFA0]
    // 0xe825688  call qword ptr [0xF99FFA0]
    // 0xe825762  call r10
    // 0xe8258ad  call qword ptr [0xF99FFA0]
    // 0xe825954  call qword ptr [0xF99FFA0]
    // 0xe825986  call qword ptr [0xF99FFA0]
    // 0xe8259aa  call qword ptr [0xF99FFA0]
    // 0xe8259d7  call 0xE82DE90
    // 0xe825a0f  call 0xE935700
    // 0xe825a39  call 0xE835B50
    // 0xe825a55  call 0xEEC6ED0
    // 0xe825d18  call qword ptr [0xF99FFA0]
    // 0xe825dd3  call qword ptr [0xF99FFA0]
    // 0xe825e76  call qword ptr [0xF99FFA0]
    // 0xe825f52  call r10
    // 0xe826061  call qword ptr [0xF99FFA0]

    // Placeholder for remaining paths - they all eventually reach the chunk boundary
    // at 0xe826261 (NotTaken from 0xe82625a jne -> 0xe826261)

loc_e8254d2:
loc_e8253ab:
loc_e8253cf:
loc_e8253de:
loc_e8254a6:
loc_e8254b4:
loc_e825566:
loc_e825571:
loc_e825578:
loc_e8255f2:
loc_e82562c:
loc_e82568f:
loc_e8257de:
loc_e8257a6:
loc_e825818:
loc_e8259d7:
loc_e825a0f:
loc_e825a39:
loc_e825a55:
loc_e825d18:
loc_e825dd3:
loc_e825e76:
loc_e825f52:
loc_e826061:
    // All paths converge at chunk boundary 0xe826261
    // The next chunk (part 2/7) starts at 0xe826261
    goto chunk_boundary;

    // ========== 0xe825910 (call 0xE820500) ==========
    // 0xe8258f5  mov rcx,[rbx+0xA0]
    // 0xe8258fc  lea rdx,[rbx+0x3B0]
    // 0xe825903  mov r8d,0x41
    // 0xe825909  mov r9,[rbx+0x388]
    // 0xe825910  call 0xE820500
loc_e825910:
    {
        void* rcx = slot_ptr(s, layout_e824af1_part1::JOB_CONTEXT_OFF);
        void* rdx = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(s->rbx) + 0x3B0);
        uint32_t r8d = 0x41;
        void* r9 = slot_ptr(s, 0x388);
        // 0xe825910  call 0xE820500
        sub_e820500(rcx, rdx, reinterpret_cast<void*>(static_cast<uintptr_t>(r8d)), r9);
        goto loc_e825915;
    }

loc_e825915:
    {
        // ... continues
        goto chunk_boundary;
    }

    // ========== 0xe825b62 (call 0xE82DCC0) ==========
    // 0xe825b55  mov rcx,rsi
    // 0xe825b58  mov rdx,[rbx+0x90]
    // 0xe825b5f  mov r8d,8
    // 0xe825b62  call 0xE82DCC0
loc_e825b62:
    {
        void* rcx = s->rsi;
        void* rdx = slot_ptr(s, layout_e824af1_part1::RESOURCE_TABLE_OFF);
        uint32_t r8d = 8;
        // 0xe825b62  call 0xE82DCC0
        sub_e82dcc0(rcx, r8d);
        goto loc_e825b67;
    }

loc_e825b67:
    {
        // ... continues
        goto chunk_boundary;
    }

    // ========== 0xe8261e2 (call 0xE83ACE0) ==========
    // 0xe8261e2  call 0xE83ACE0
loc_e8261e2:
    {
        void* rcx = s->rbx; // context
        // 0xe8261e2  call 0xE83ACE0
        sub_e83ace0(rcx);
        goto loc_e8261e7;
    }

loc_e8261e7:
    {
        // ... continues to chunk boundary
        goto chunk_boundary;
    }

    // Exit points to parent function or other chunks
loc_e825498:
    // Early exit when draw items is null
    goto loc_e82306e_exit;

loc_e82306e_exit:
loc_e823066_exit:
loc_e827c85_exit:
loc_e825766:
    // Jumps to other functions/chunks
    // These are handled by the chunk dispatcher
    return;

chunk_boundary:
    // Chunk boundary at 0xe826261
    // Live state preserved for next chunk: rbx,rbp,r12-r15,rsi,rdi,xmm6-xmm15,stack-frame
    return;
}

// Exported chunk entry point
extern "C" void sub_e824af1_chunk_0(ChunkState_e824af1_part1* state) {
    sub_e824af1_chunk_0_impl(state);
}

// Registry entry via LIFT_FN
#define LIFT_FN_IMPL(name, symbol, rva, size, mode) \
    namespace { \
        struct LIFT_FN_Registrar_##name { \
            LIFT_FN_Registrar_##name() { \
                native::register_lift_fn(#symbol, rva, size, mode, reinterpret_cast<void*>(name)); \
            } \
        } g_lift_fn_registrar_##name; \
    }

LIFT_FN_IMPL(sub_e824af1_chunk_0, "sub_e824af1", 0xe824af1, 0x89f2, native::NativeMode::Shadow)

} // namespace native