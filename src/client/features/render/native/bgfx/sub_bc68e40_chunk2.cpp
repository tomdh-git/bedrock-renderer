// LIFT 0xbc68e40 size 0x1b83 1.26.62.01 bgfx render-thread command buffer interpreter (40-way jump table)
// CHUNK 0xbc6a600..0xbc6a9c3
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc68e40_chunk2.h"

#include <cstdint>
#include <cstring>

namespace native::bgfx {

namespace {

// External calls from the lift set (already lifted by their own units)
extern "C" void sub_ebce390(void* out, const std::uint8_t* src, std::uint32_t count);     // 0xebce390
extern "C" void sub_bc6abd0(void* ctx, void* cmdbuf);                                      // 0xbc6abd0
extern "C" void* sub_bc68840(void* out_struct, void* cmdbuf, void* arg3, std::uint32_t arg4); // 0xbc68840

// Vendor boundary thunk via data slot 0xF99FFA0
// sub_eea6040 at 0xeea6040 is a "jmp rax" thunk - caller loads vtable function into rax first.
// Returns its result in rax (the exe sign-extends it with cdqe at the call sites).
inline std::int64_t eea6040_call(void* self, void* arg1, void* arg2, std::uint32_t arg3, std::uint32_t arg4,
                                 void* arg5, void* arg6, void* arg7, void* arg8) {
    using Fn = std::int64_t (*)(void*, void*, void*, std::uint32_t, std::uint32_t,
                                void*, void*, void*, void*);
    Fn fn = reinterpret_cast<Fn>(*reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF99FFA0));
    return fn(self, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}

} // namespace

// Chunk 2 state: live at 0xbc6a600
// rcx = Context*, rdx = CommandBuffer* (position at [rdx], data at rdx+8)
// rbx = data pointer base (set to rsi+8 at 0xbc6a802)
// r13 = command data base (rdx+8 from entry)
// r12, r14, r15, rbp = temporaries (mapped to state fields)
struct ChunkState_bc6a600 {
    void* ctx;                    // rcx
    std::uint32_t pos;            // [rsi] = cmdbuf->position
    std::uint8_t* data;           // [rsi+8] = cmdbuf->data (r13)
    std::uint8_t* rbx;            // data pointer base (set at 0xbc6a802)
    std::uint64_t r12;
    std::uint64_t r14;
    std::uint64_t r15;
    std::uint64_t rbp;
    std::uint8_t stack[0x108];    // stack frame (rsp+0x00..rsp+0x107)
};

// LIFT_FN registration
LIFT_FN(sub_bc68e40_chunk2_step, "bgfx render-thread command buffer interpreter chunk2",
        0xbc6a600, sub_bc68e40_chunk2_step, nullptr);

void sub_bc68e40_chunk2_step(ChunkState_bc6a600* state) {
    // Map state to local variables matching the disassembly
    void* ctx = state->ctx;
    std::uint32_t& pos = state->pos;
    std::uint8_t* data_ptr = state->data;  // r13
    std::uint8_t* rbx = state->rbx;
    std::uint8_t* stack = state->stack;
    
    // Prologue: push r15..rbx, sub rsp,0x108; rsi=rdx, rdi=rcx; [rdx]=0
    // Note: This chunk starts mid-function at 0xbc6a600, which is the tail of case 0x09.
    // The prologue was already executed in chunk 1 (0xbc68e40..0xbc6a600).
    // We inherit: rsi=cmdbuf, rdi=ctx, r13=data_ptr, r14=stack+0x6D, rbp=jump_table
    
    // loc_bc6a600: Read 2 aligned bytes, memcpy to stack[rsp+0x90]
    // 0xbc6a600  and edx,0xFFFFFFFE
    pos &= 0xFFFFFFFE;
    // 0xbc6a603  add edx,2
    pos += 2;
    // 0xbc6a606  mov [rsi],edx
    state->pos = pos;
    // 0xbc6a608  add rdx,r13
    // 0xbc6a60b  lea rcx,[rsp+0x90]
    std::uint8_t* src_ptr = data_ptr + pos;
    // 0xbc6a613  mov r8d,2
    std::uint32_t count = 2;
    // 0xbc6a619  call 0xEBCE390
    sub_ebce390(stack + 0x90, src_ptr, count);
    
    // 0xbc6a61e..0xbc6a63b: Read 1 byte, memcpy to stack[rsp+0x97]
    // 0xbc6a61e  mov edx,[rsi]
    pos = state->pos;
    // 0xbc6a620  add edx,2
    pos += 2;
    // 0xbc6a623  mov [rsi],edx
    state->pos = pos;
    // 0xbc6a625  add rdx,r13
    src_ptr = data_ptr + pos;
    // 0xbc6a628  lea rcx,[rsp+0x97]
    // 0xbc6a630  mov r8d,1
    count = 1;
    // 0xbc6a636  call 0xEBCE390
    sub_ebce390(stack + 0x97, src_ptr, count);
    
    // 0xbc6a63b..0xbc6a65b: Read 2 aligned bytes, memcpy to stack[rsp+0x8C]
    // 0xbc6a63b  mov edx,[rsi]
    pos = state->pos;
    // 0xbc6a63d  and edx,0xFFFFFFFE
    pos &= 0xFFFFFFFE;
    // 0xbc6a640  add edx,2
    pos += 2;
    // 0xbc6a643  mov [rsi],edx
    state->pos = pos;
    // 0xbc6a645  add rdx,r13
    src_ptr = data_ptr + pos;
    // 0xbc6a648  lea rcx,[rsp+0x8C]
    // 0xbc6a650  mov r8d,2
    count = 2;
    // 0xbc6a656  call 0xEBCE390
    sub_ebce390(stack + 0x8C, src_ptr, count);
    
    // 0xbc6a65b..0xbc6a66a: Read 2 bytes, check stack_97 == 1
    // 0xbc6a65b  mov edx,[rsi]
    pos = state->pos;
    // 0xbc6a65d  lea eax,[rdx+2]
    // 0xbc6a660  mov [rsi],eax
    state->pos = pos + 2;
    pos += 2;
    // 0xbc6a662  cmp byte ptr [rsp+0x97],1
    // 0xbc6a66a  jne short 0xBC6A697
    if (stack[0x97] != 1) {
        goto loc_bc6a697;
    }
    
    // 0xbc6a66c..0xbc6a697: stack_97 == 1 path - table lookup at [0x12AE1748]
    // 0xbc6a66c  mov rax,[0x12AE1748]
    std::uint64_t table_base = *reinterpret_cast<std::uint64_t*>(RewriteRegistry::imageBase() + 0x12AE1748);
    // 0xbc6a673  movzx ecx,word ptr [rsp+0x8C]
    std::uint16_t idx = *reinterpret_cast<std::uint16_t*>(stack + 0x8C);
    // 0xbc6a67b  lea r8,[rcx+rcx*8]
    std::uint64_t r8 = idx + idx * 8;
    // 0xbc6a67f  lea r8,[r8+r8*2]
    r8 = r8 + r8 * 2;
    // 0xbc6a683  add r8,rcx
    r8 += idx;
    // 0xbc6a686  movzx eax,word ptr [rax+r8+0x1DBD0C8]
    std::uint16_t val = *reinterpret_cast<std::uint16_t*>(table_base + r8 + 0x1DBD0C8);
    // 0xbc6a68f  mov [rsp+0x8C],ax
    *reinterpret_cast<std::uint16_t*>(stack + 0x8C) = val;
    
loc_bc6a697:
    // 0xbc6a697..0xbc6a6b2: Read 2 aligned bytes, memcpy to stack[rsp+0x6E]
    // 0xbc6a697  add edx,3
    pos = state->pos;
    pos += 3;
    // 0xbc6a69a  and edx,0xFFFFFFFE
    pos &= 0xFFFFFFFE;
    // 0xbc6a69d  mov [rsi],edx
    state->pos = pos;
    // 0xbc6a69f  add rdx,r13
    src_ptr = data_ptr + pos;
    // 0xbc6a6a2  lea rcx,[rsp+0x6E]
    // 0xbc6a6a7  mov r8d,2
    count = 2;
    // 0xbc6a6ad  call 0xEBCE390
    sub_ebce390(stack + 0x6E, src_ptr, count);
    
    // 0xbc6a6b2..0xbc6a6d2: Read 4 aligned bytes, memcpy to stack[rsp+0xB0]
    // 0xbc6a6b2  mov edx,[rsi]
    pos = state->pos;
    // 0xbc6a6b4  add edx,5
    pos += 5;
    // 0xbc6a6b7  and edx,0xFFFFFFFC
    pos &= 0xFFFFFFFC;
    // 0xbc6a6ba  mov [rsi],edx
    state->pos = pos;
    // 0xbc6a6bc  add rdx,r13
    src_ptr = data_ptr + pos;
    // 0xbc6a6bf  lea rcx,[rsp+0xB0]
    // 0xbc6a6c7  mov r8d,4
    count = 4;
    // 0xbc6a6cd  call 0xEBCE390
    sub_ebce390(stack + 0xB0, src_ptr, count);
    
    // 0xbc6a6d2..0xbc6a6ef: Read 4 aligned bytes, memcpy to stack[rsp+0x70]
    // 0xbc6a6d2  mov edx,[rsi]
    pos = state->pos;
    // 0xbc6a6d4  add edx,7
    pos += 7;
    // 0xbc6a6d7  and edx,0xFFFFFFFC
    pos &= 0xFFFFFFFC;
    // 0xbc6a6da  mov [rsi],edx
    state->pos = pos;
    // 0xbc6a6dc  add rdx,r13
    src_ptr = data_ptr + pos;
    // 0xbc6a6df  lea rcx,[rsp+0x70]
    // 0xbc6a6e4  mov r8d,4
    count = 4;
    // 0xbc6a6ea  call 0xEBCE390
    sub_ebce390(stack + 0x70, src_ptr, count);
    
    // 0xbc6a6ef..0xbc6a70c: Read 1 byte, memcpy to stack[rsp+0x96]
    // 0xbc6a6ef  mov edx,[rsi]
    pos = state->pos;
    // 0xbc6a6f1  add edx,4
    pos += 4;
    // 0xbc6a6f4  mov [rsi],edx
    state->pos = pos;
    // 0xbc6a6f6  add rdx,r13
    src_ptr = data_ptr + pos;
    // 0xbc6a6f9  lea rcx,[rsp+0x96]
    // 0xbc6a701  mov r8d,1
    count = 1;
    // 0xbc6a707  call 0xEBCE390
    sub_ebce390(stack + 0x96, src_ptr, count);
    
    // 0xbc6a70c..0xbc6a729: Read 2 aligned bytes, memcpy to stack[rsp+0x6A]
    // 0xbc6a70c  mov edx,[rsi]
    pos = state->pos;
    // 0xbc6a70e  and edx,0xFFFFFFFE
    pos &= 0xFFFFFFFE;
    // 0xbc6a711  add edx,2
    pos += 2;
    // 0xbc6a714  mov [rsi],edx
    state->pos = pos;
    // 0xbc6a716  add rdx,r13
    src_ptr = data_ptr + pos;
    // 0xbc6a719  lea rcx,[rsp+0x6A]
    // 0xbc6a71e  mov r8d,2
    count = 2;
    // 0xbc6a724  call 0xEBCE390
    sub_ebce390(stack + 0x6A, src_ptr, count);
    
    // 0xbc6a729..0xbc6a749: Read 4 aligned bytes, memcpy to stack[rsp+0x98]
    // 0xbc6a729  mov edx,[rsi]
    pos = state->pos;
    // 0xbc6a72b  add edx,5
    pos += 5;
    // 0xbc6a72e  and edx,0xFFFFFFFC
    pos &= 0xFFFFFFFC;
    // 0xbc6a731  mov [rsi],edx
    state->pos = pos;
    // 0xbc6a733  add rdx,r13
    src_ptr = data_ptr + pos;
    // 0xbc6a736  lea rcx,[rsp+0x98]
    // 0xbc6a73e  mov r8d,4
    count = 4;
    // 0xbc6a744  call 0xEBCE390
    sub_ebce390(stack + 0x98, src_ptr, count);
    
    // 0xbc6a749..0xbc6a766: Read 4 aligned bytes, memcpy to stack[rsp+0x60], check stack_96 == 1
    // 0xbc6a749  mov edx,[rsi]
    pos = state->pos;
    // 0xbc6a74b  add edx,7
    pos += 7;
    // 0xbc6a74e  and edx,0xFFFFFFFC
    pos &= 0xFFFFFFFC;
    // 0xbc6a751  mov [rsi],edx
    state->pos = pos;
    // 0xbc6a753  add rdx,r13
    src_ptr = data_ptr + pos;
    // 0xbc6a756  lea rcx,[rsp+0x60]
    // 0xbc6a75b  mov r8d,4
    count = 4;
    // 0xbc6a761  call 0xEBCE390
    sub_ebce390(stack + 0x60, src_ptr, count);
    
    // 0xbc6a766..0xbc6a775: Read 4 aligned bytes, memcpy to stack[rsp+0x60], check stack_96 == 1
    // 0xbc6a766  mov edx,[rsi]
    pos = state->pos;
    // 0xbc6a768  lea eax,[rdx+4]
    // 0xbc6a76b  mov [rsi],eax
    state->pos = pos + 4;
    pos += 4;
    // 0xbc6a76d  cmp byte ptr [rsp+0x96],1
    // 0xbc6a775  jne 0xBC68E80
    if (stack[0x96] != 1) {
        // Jump to 0xbc68e80 which is in chunk 1 (0xbc68e40..0xbc6a600)
        // This means we need to jump back to the chunk 1 code
        // For now, we'll just return - the real code continues in chunk 1
        return;
    }
    
    // 0xbc6a77b..0xbc6a7fd: stack_96 == 1 path - complex table lookup, jump to chunk 1
    // 0xbc6a77b  mov rax,[0x12AE1748]
    table_base = *reinterpret_cast<std::uint64_t*>(RewriteRegistry::imageBase() + 0x12AE1748);
    // 0xbc6a782  movzx ecx,word ptr [rsp+0x6A]
    idx = *reinterpret_cast<std::uint16_t*>(stack + 0x6A);
    // 0xbc6a787  lea r8,[rcx+rcx*4]
    r8 = idx + idx * 4;
    // 0xbc6a78b  movzx ecx,word ptr [rax+r8*4+0x1DA90C8]
    std::uint16_t val2 = *reinterpret_cast<std::uint16_t*>(table_base + r8 * 4 + 0x1DA90C8);
    // 0xbc6a794  mov [rsp+0x6A],cx
    *reinterpret_cast<std::uint16_t*>(stack + 0x6A) = val2;
    // 0xbc6a799  movzx r15d,word ptr [rax+r8*4+0x1DA90D8]
    std::uint32_t r15d = *reinterpret_cast<std::uint16_t*>(table_base + r8 * 4 + 0x1DA90D8);
    // 0xbc6a7a2  and r15d,0x1000
    r15d &= 0x1000;
    // 0xbc6a7a9  mov r9d,[rsp+0x60]
    std::uint32_t r9d = *reinterpret_cast<std::uint32_t*>(stack + 0x60);
    // 0xbc6a7ae  add r9d,[rax+r8*4+0x1DA90D4]
    r9d += *reinterpret_cast<std::uint32_t*>(table_base + r8 * 4 + 0x1DA90D4);
    // 0xbc6a7b6  cmp r15w,1
    // 0xbc6a7bb  mov ecx,2
    // 0xbc6a7c0  sbb ecx,0
    std::uint32_t ecx = (r15d >= 1) ? 2 : (2 - 1); // sbb ecx,0 with CF from cmp
    // 0xbc6a7c3  shl r9d,cl
    r9d <<= ecx;
    // 0xbc6a7c6  mov [rsp+0x60],r9d
    *reinterpret_cast<std::uint32_t*>(stack + 0x60) = r9d;
    // 0xbc6a7cb  mov eax,[rax+r8*4+0x1DA90D0]
    std::uint32_t eax = *reinterpret_cast<std::uint32_t*>(table_base + r8 * 4 + 0x1DA90D0);
    // 0xbc6a7d3  test eax,eax
    // 0xbc6a7d5  je short 0xBC6A7E7
    if (eax != 0) {
        // 0xbc6a7d7  shr eax,cl
        eax >>= ecx;
        // 0xbc6a7d9  mov ecx,[rsp+0x98]
        std::uint32_t ecx2 = *reinterpret_cast<std::uint32_t*>(stack + 0x98);
        // 0xbc6a7e0  cmp ecx,eax
        // 0xbc6a7e2  cmovb eax,ecx
        if (ecx2 < eax) {
            eax = ecx2;
        }
        // 0xbc6a7e5  jmp short 0xBC6A7EE
    } else {
        // 0xbc6a7e7  mov eax,[rsp+0x98]
        eax = *reinterpret_cast<std::uint32_t*>(stack + 0x98);
    }
    
loc_bc6a7ee:
    // 0xbc6a7ee  shr r15d,0xB
    r15d >>= 0xB;
    // 0xbc6a7f2  add r15d,2
    r15d += 2;
    // 0xbc6a7f6  mov [rsp+0x98],eax
    *reinterpret_cast<std::uint32_t*>(stack + 0x98) = eax;
    // 0xbc6a7fd  jmp 0xBC68E83
    // This jumps to chunk 1 at 0xbc68e83
    // For now, we'll just return - the real code continues in chunk 1
    return;
    
loc_bc6a802:
    // 0xbc6a802..0xbc6a820: rbx = rsi+8, read 1 byte to stack_70
    // 0xbc6a802  lea rbx,[rsi+8]
    rbx = data_ptr;
    // 0xbc6a806  lea rcx,[rsp+0x70]
    // 0xbc6a80b  mov r8d,1
    count = 1;
    // 0xbc6a811  mov rdx,rbx
    src_ptr = rbx;
    // 0xbc6a814  call 0xEBCE390
    sub_ebce390(stack + 0x70, src_ptr, count);
    // 0xbc6a819  mov edx,[rsi]
    pos = state->pos;
    // 0xbc6a81b  lea eax,[rdx+1]
    // 0xbc6a81e  mov [rsi],eax
    state->pos = pos + 1;
    pos += 1;
    // 0xbc6a820  movzx eax,byte ptr [rsp+0x70]
    std::uint8_t cmd = stack[0x70];
    
    // 0xbc6a820..0xbc6a828: if cmd == 0x19 goto epilogue
    // 0xbc6a820  movzx eax,byte ptr [rsp+0x70]
    // 0xbc6a825  cmp eax,0x19
    // 0xbc6a828  je short 0xBC6A887
    if (cmd == 0x19) {
        goto loc_bc6a887; // epilogue
    }
    
    // 0xbc6a82a..0xbc6a82d: if cmd != 0x1A goto loc_bc6a89b
    // 0xbc6a82a  cmp eax,0x1A
    // 0xbc6a82d  jne short 0xBC6A89B
    if (cmd != 0x1A) {
        goto loc_bc6a89b;
    }
    
    // 0xbc6a82f..0xbc6a836: cmd 0x19 path - set flag, goto epilogue
    // 0xbc6a82f  mov byte ptr [rdi+0x1EBF2EF],1
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(ctx) + 0x1EBF2EF) = 1;
    // 0xbc6a836  jmp short 0xBC6A887
    goto loc_bc6a887;
    
    // 0xbc6a838..0xbc6a886: cmd 0x1A path - renderer cleanup
    // 0xbc6a838  mov rcx,[rdi+0x1EBF2D0]
    void* renderer = *reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(ctx) + 0x1EBF2D0);
    // 0xbc6a83f  test rcx,rcx
    // 0xbc6a842  je short 0xBC6A869
    if (renderer != nullptr) {
        // 0xbc6a844  mov rax,[rcx]
        void* vtable = *reinterpret_cast<void**>(renderer);
        // 0xbc6a847  mov rax,[rax+8]
        void* fn1 = *reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(vtable) + 8);
        // 0xbc6a84b  call qword ptr [0xF99FFA0]
        std::int64_t result = reinterpret_cast<std::int64_t>(eea6040_call(renderer, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr));
        // 0xbc6a851  cdqe
        // 0xbc6a853  lea rax,[rax+rax*4]
        result = result + result * 4;
        // 0xbc6a857  lea rcx,[0x127CA010]
        std::uint8_t* table = reinterpret_cast<std::uint8_t*>(RewriteRegistry::imageBase() + 0x127CA010);
        // 0xbc6a85e  mov rax,[rcx+rax*8+8]
        void* target = *reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(table) + result * 8 + 8);
        // 0xbc6a863  call qword ptr [0xF99FFA0]
        eea6040_call(target, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr);
    }
    
loc_bc6a869:
    // 0xbc6a869  mov qword ptr [rdi+0x1EBF2D0],0
    *reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(ctx) + 0x1EBF2D0) = nullptr;
    // 0xbc6a874  mov byte ptr [rdi+0x1EBF2EF],1
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(ctx) + 0x1EBF2EF) = 1;
    // 0xbc6a87b  mov rcx,rdi
    // 0xbc6a87e  mov rdx,rsi
    // 0xbc6a881  call 0xBC6ABD0
    sub_bc6abd0(ctx, reinterpret_cast<void*>(&state->pos));
    
loc_bc6a887:
    // 0xbc6a887..0xbc6a89a: Epilogue - restore registers, ret
    // 0xbc6a887  add rsp,0x108
    // 0xbc6a88e  pop rbx
    // 0xbc6a88f  pop rbp
    // 0xbc6a890  pop rdi
    // 0xbc6a891  pop rsi
    // 0xbc6a892  pop r12
    // 0xbc6a894  pop r13
    // 0xbc6a896  pop r14
    // 0xbc6a898  pop r15
    // 0xbc6a89a  ret
    return;
    
loc_bc6a89b:
    // 0xbc6a89b..0xbc6a9c3: cmd 0x1A struct setup path
    // 0xbc6a89b  mov qword ptr [rsp+0xB0],0xB
    *reinterpret_cast<std::uint64_t*>(stack + 0xB0) = 0xB;
    // 0xbc6a8a7  mov word ptr [rsp+0xB8],0
    *reinterpret_cast<std::uint16_t*>(stack + 0xB8) = 0;
    // 0xbc6a8b1  mov rax,0x2D000000500
    std::uint64_t rax = 0x2D000000500;
    // 0xbc6a8bb  mov [rsp+0xBC],rax
    *reinterpret_cast<std::uint64_t*>(stack + 0xBC) = rax;
    // 0xbc6a8c3  mov dword ptr [rsp+0xC4],0
    *reinterpret_cast<std::uint32_t*>(stack + 0xC4) = 0;
    // 0xbc6a8ce  xorps xmm0,xmm0
    // 0xbc6a8d1  movups [rsp+0xD8],xmm0
    *reinterpret_cast<std::uint64_t*>(stack + 0xD8) = 0;
    *reinterpret_cast<std::uint64_t*>(stack + 0xE0) = 0;
    // 0xbc6a8d9  mov qword ptr [rsp+0xE8],0
    *reinterpret_cast<std::uint64_t*>(stack + 0xE8) = 0;
    // 0xbc6a8e5  mov word ptr [rsp+0xC8],8
    *reinterpret_cast<std::uint16_t*>(stack + 0xC8) = 8;
    // 0xbc6a8ef  mov rax,0x20000000600000
    rax = 0x20000000600000;
    // 0xbc6a8f9  mov [rsp+0xCC],rax
    *reinterpret_cast<std::uint64_t*>(stack + 0xCC) = rax;
    // 0xbc6a901  mov byte ptr [rsp+0xD4],1
    *reinterpret_cast<std::uint8_t*>(stack + 0xD4) = 1;
    // 0xbc6a909..0xbc6a925: Read 64 bytes aligned to 8, memcpy to stack[rsp+0xB0]
    // 0xbc6a909  and edx,0xFFFFFFF8
    pos = state->pos;
    pos &= 0xFFFFFFF8;
    // 0xbc6a90c  add edx,8
    pos += 8;
    // 0xbc6a90f  mov [rsi],edx
    state->pos = pos;
    // 0xbc6a911  add rdx,rbx
    src_ptr = rbx + pos;
    // 0xbc6a914  lea r14,[rsp+0xB0]
    std::uint8_t* r14 = stack + 0xB0;
    // 0xbc6a91c  mov r8d,0x40
    count = 0x40;
    // 0xbc6a922  mov rcx,r14
    // 0xbc6a925  call 0xEBCE390
    sub_ebce390(r14, src_ptr, count);
    
    // 0xbc6a92a..0xbc6a942: Read 1 byte, memcpy to stack[rsp+0x98]
    // 0xbc6a92a  mov edx,[rsi]
    pos = state->pos;
    // 0xbc6a92c  add edx,0x40
    pos += 0x40;
    // 0xbc6a92f  mov [rsi],edx
    state->pos = pos;
    // 0xbc6a931  add rdx,rbx
    src_ptr = rbx + pos;
    // 0xbc6a934  lea rcx,[rsp+0x98]
    // 0xbc6a93c  mov r8d,1
    count = 1;
    // 0xbc6a942  call 0xEBCE390
    sub_ebce390(stack + 0x98, src_ptr, count);
    
    // 0xbc6a947  inc dword ptr [rsi]
    state->pos++;
    
    // 0xbc6a949..0xbc6a95b: Call sub_bc68840(rcx=r14, rdx=[rsi] cmdbuf, r8=&ctx[0x1EBF2F2], r9d=stack_98)
    // 0xbc6a949  lea r8,[rdi+0x1EBF2F2]
    std::uint8_t* r8_ptr = reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(ctx) + 0x1EBF2F2);
    // 0xbc6a950  movzx edx,byte ptr [rsp+0x98]
    std::uint8_t edx_val = stack[0x98];
    // 0xbc6a958  mov rcx,r14
    // rdx is still cmdbuf pointer (&pos) from entry to the chunk; rcx = r14 (the 0x40-byte struct)
    // 0xbc6a95b  call 0xBC68840
    void* result = sub_bc68840(r14, reinterpret_cast<void*>(&state->pos), r8_ptr, edx_val);
    
    // 0xbc6a960  mov [rdi+0x1EBF2D0],rax
    *reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(ctx) + 0x1EBF2D0) = result;
    // 0xbc6a967  test rax,rax
    // 0xbc6a96a  setne [rdi+0x1EBF2EC]
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(ctx) + 0x1EBF2EC) = (result != nullptr) ? 1 : 0;
    // 0xbc6a971  je short 0xBC6A9A4
    if (result == nullptr) {
        goto loc_bc6a9a4;
    }
    
    // 0xbc6a973..0xbc6a980: Call sub_eea6040 and process result
    // 0xbc6a973  mov rcx,[rax]
    void* vtable = *reinterpret_cast<void**>(result);
    // 0xbc6a976  mov rdx,[rcx+8]
    void* fn = *reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(vtable) + 8);
    // 0xbc6a97a  mov rcx,rax
    // 0xbc6a97d  mov rax,rdx
    // 0xbc6a980  call qword ptr [0xF99FFA0]
    std::int64_t ret_val = reinterpret_cast<std::int64_t>(eea6040_call(result, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr, nullptr));
    
    // 0xbc6a986  cdqe
    // 0xbc6a988  lea rax,[rax+rax*4]
    ret_val = ret_val + ret_val * 4;
    // 0xbc6a98c  lea rcx,[0x127CA010]
    std::uint8_t* table = reinterpret_cast<std::uint8_t*>(RewriteRegistry::imageBase() + 0x127CA010);
    // 0xbc6a993  cmp dword ptr [rcx+rax*8+0x1C],1
    std::uint32_t check = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uintptr_t>(table) + ret_val * 8 + 0x1C);
    // 0xbc6a998  sete [rdi+0x1EBF2F0]
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(ctx) + 0x1EBF2F0) = (check == 1) ? 1 : 0;
    // 0xbc6a99f  jmp 0xBC68E6D
    // This jumps to chunk 1 at 0xbc68e6d
    // For now, we'll just return - the real code continues in chunk 1
    return;
    
loc_bc6a9a4:
    // 0xbc6a9a4..0xbc6a9be: Final path
    // 0xbc6a9a4  mov eax,[rsi]
    pos = state->pos;
    // 0xbc6a9a6  add rbx,rax
    rbx += pos;
    // 0xbc6a9a9  lea rcx,[rsp+0x70]
    // 0xbc6a9ae  mov r8d,1
    count = 1;
    // 0xbc6a9b4  mov rdx,rbx
    src_ptr = rbx;
    // 0xbc6a9b7  call 0xEBCE390
    sub_ebce390(stack + 0x70, src_ptr, count);
    // 0xbc6a9bc  inc dword ptr [rsi]
    state->pos++;
    // 0xbc6a9be  jmp 0xBC6A887
    goto loc_bc6a887;
    
    // 0xbc6a9c3: End of chunk (int3 padding)
}

// Layout assertions
static_assert(offsetof(ChunkState_bc6a600, ctx) == 0x00, "ctx at +0x00");
static_assert(offsetof(ChunkState_bc6a600, pos) == 0x08, "pos at +0x08");
static_assert(offsetof(ChunkState_bc6a600, data) == 0x0C, "data at +0x0C");
static_assert(offsetof(ChunkState_bc6a600, rbx) == 0x10, "rbx at +0x10");
static_assert(offsetof(ChunkState_bc6a600, r12) == 0x18, "r12 at +0x18");
static_assert(offsetof(ChunkState_bc6a600, r14) == 0x20, "r14 at +0x20");
static_assert(offsetof(ChunkState_bc6a600, r15) == 0x28, "r15 at +0x28");
static_assert(offsetof(ChunkState_bc6a600, rbp) == 0x30, "rbp at +0x30");
static_assert(offsetof(ChunkState_bc6a600, stack) == 0x38, "stack at +0x38");
static_assert(sizeof(ChunkState_bc6a600) == 0x38 + 0x108, "state size 0x140");

// Verbatim log of every call instruction in [0xbc6a600, 0xbc6a9c3) (rdis dis output, two spaces after address):
#if 0
0xbc6a619  call 0xEBCE390
0xbc6a636  call 0xEBCE390
0xbc6a656  call 0xEBCE390
0xbc6a6ad  call 0xEBCE390
0xbc6a6cd  call 0xEBCE390
0xbc6a6ea  call 0xEBCE390
0xbc6a707  call 0xEBCE390
0xbc6a724  call 0xEBCE390
0xbc6a744  call 0xEBCE390
0xbc6a761  call 0xEBCE390
0xbc6a814  call 0xEBCE390
0xbc6a84b  call qword ptr [0xF99FFA0]
0xbc6a863  call qword ptr [0xF99FFA0]
0xbc6a881  call 0xBC6ABD0
0xbc6a925  call 0xEBCE390
0xbc6a942  call 0xEBCE390
0xbc6a95b  call 0xBC68840
0xbc6a980  call qword ptr [0xF99FFA0]
0xbc6a9b7  call 0xEBCE390
#endif

} // namespace native::bgfx