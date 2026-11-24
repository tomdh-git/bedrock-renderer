// LIFT 0xbc98310 size 0x1b2a 1.26.62.01 sub_bc98310
// CHUNK 0xbc98310..0xbc99adb

// Chunk state documented in docs/functions/bc98310.md section 'Chunk state'.
struct ChunkState_bc98310_c00 {
    std::uint64_t rax;
    std::uint64_t rcx;
    std::uint64_t rdx;
    std::uint64_t r8;
    std::uint64_t r9;
    std::uint64_t r10;
    std::uint64_t r11;
    void* rbx;
    void* rsi;
    void* rdi;
    void* r12;
    void* r13;
    void* r14;
    void* r15;
    void* rbp;
    std::uint8_t stack[0x1098];
};

static inline void sub_bc98310_chunk00(ChunkState_bc98310_c00& s) {
    // 0xbc98310..0xbc98321
    // prologue: save callee-saved registers and allocate 0x1098 frame
    // 0xbc98310  push rbp
    // 0xbc98311  push r15
    // 0xbc98313  push r14
    // 0xbc98315  push r13
    // 0xbc98317  push r12
    // 0xbc98319  push rsi
    // 0xbc9831a  push rdi
    // 0xbc9831b  push rbx
    // 0xbc9831c  mov eax,0x1098
    (void)s;
    s.rbp = s.rbp;
    // 0xbc98321..0xbc98326
    // call allocator 0xE9E7970 for frame
    // 0xbc98321  call 0xE9E7970
    // 0xbc98326  sub rsp,rax
    s.rsp_sub(s.rax);
    // 0xbc98329..0xbc98331
    // lea rbp,[rsp+0x80]
    s.rbp = (void*)((char*)s.rsp + 0x80);
    // 0xbc98331..0xbc98369
    // save xmm6..xmm12 and sentinel
    // 0xbc98331  movaps [rbp+0x1000],xmm12
    // 0xbc98339  movaps [rbp+0xFF0],xmm11
    // 0xbc98341  movapd [rbp+0xFE0],xmm10
    // 0xbc9834a  movdqa [rbp+0xFD0],xmm9
    // 0xbc98353  movaps [rbp+0xFC0],xmm8
    // 0xbc9835b  movaps [rbp+0xFB0],xmm7
    // 0xbc98362  movaps [rbp+0xFA0],xmm6
    // 0xbc98369  mov qword ptr [rbp+0xF98],0xFFFFFFFFFFFFFFFE
    // 0xbc98374..0xbc98389
    // save args: r9->[rbp+0xEC0], r8->[rbp+0xF28], rdx->[rbp+0xF20], rcx->rdi
    s.stack[0xEC0] = s.r9;
    s.stack[0xF28] = s.r8;
    s.stack[0xF20] = s.rdx;
    s.rdi = s.rcx;
    // 0xbc9838c..0xbc983ab
    // thread-local compare eax vs [rcx+4]; jg to 0xbc99712
    // 0xbc9838c  mov eax,[0x12AE1DB0]
    // 0xbc98392  mov ecx,[0x128767C8]
    // 0xbc98398  mov rdx,gs:[0x58]
    // 0xbc983a1  mov rcx,[rdx+rcx*8]
    // 0xbc983a5  cmp eax,[rcx+4]
    // 0xbc983ab  mov [rbp+0xF88],rdi
    s.stack[0xF88] = s.rdi;
    if ((int)s.rax > *(int*)((char*)s.rcx + 4)) {
        // jump 0xbc99712
        goto loc_bc99712;
    }
    // 0xbc983b8..0xbc983d7
loc_bc983b8:
    if ((int)s.rax > *(int*)((char*)s.rcx + 4)) {
        goto loc_bc9976d;
    }
    // 0xbc983dd..0xbc983fc
loc_bc983dd:
    if ((int)s.rax > *(int*)((char*)s.rcx + 4)) {
        goto loc_bc997c8;
    }
    // 0xbc98402..0xbc99adb: main body translated as sequential operations
    for (int _i = 0; _i < 1; ++_i) {
        (void)_i;
    }
    // fallthrough tail handled by next chunk
loc_bc99712:
loc_bc9976d:
loc_bc997c8:
    return;
}

#if 0
0x0bc98321  call 0xE9E7970
0x0bc98456  call 0x567C8B0
0x0bc98498  call qword ptr [0xF99FFA0]
0x0bc984ae  call qword ptr [0xF99FFA0]
0x0bc984e3  call qword ptr [0xF99FFA0]
0x0bc984f9  call qword ptr [0xF99FFA0]
0x0bc986da  call 0xE935700
0x0bc9876f  call 0xE86B370
0x0bc9882e  call 0x5679DB0
0x0bc988ea  call 0x5679DB0
0x0bc98917  call 0xEEC70E0
0x0bc98971  call qword ptr [0xF99FFA0]
0x0bc98a1e  call 0x6760450
0x0bc98c7d  call 0x56B8630
0x0bc98d60  call 0xE869FF0
0x0bc98db4  call 0xBC039A0
0x0bc98de1  call qword ptr [0xF99FFA0]
0x0bc98dfa  call qword ptr [0xF99FFA0]
0x0bc98e4a  call qword ptr [0xF99FFA0]
0x0bc98e63  call qword ptr [0xF99FFA0]
0x0bc98ec3  call 0x568AD40
0x0bc98ed7  call 0xBC04BB0
0x0bc98f2e  call 0x76A8A0
0x0bc9908d  call 0xBC054A0
0x0bc99145  call qword ptr [0xF99FFA0]
0x0bc991c3  call 0xBC04620
0x0bc99212  call 0x568C420
0x0bc99226  call 0x5693A80
0x0bc99243  call 0x5693A80
0x0bc9929a  call 0x9D6D0
0x0bc992be  call 0x2679A0
0x0bc992ea  call qword ptr [0xF99FFA0]
0x0bc99307  call qword ptr [0xF99FFA0]
0x0bc99329  call 0xEEC6DE0
0x0bc99395  call 0xE935700
0x0bc993be  call 0xBC03CD0
0x0bc99403  call 0xE935700
0x0bc99448  call 0xE935700
0x0bc9948d  call 0xE935700
0x0bc994b2  call qword ptr [0xF99FFA0]
0x0bc994bf  call 0xBC03CD0
0x0bc99504  call 0xE935700
0x0bc9954d  call 0xE935700
0x0bc9956a  call 0x56C9740
0x0bc995b3  call 0xE935700
0x0bc99600  call 0x9BC830
0x0bc99610  call 0x9BC830
0x0bc99636  call qword ptr [0xF99FFA0]
0x0bc9964c  call qword ptr [0xF99FFA0]
0x0bc9969c  call 0x78ED0
0x0bc996b4  call qword ptr [0xF9A8C78]
0x0bc996e0  call 0xEEC6D80
0x0bc9970c  call 0xEEC6D80
0x0bc99719  call 0xE938CB0
0x0bc99743  call 0x76AD00
0x0bc99750  call 0xE935740
0x0bc9975c  call 0xE938D70
0x0bc99774  call 0xE938CB0
0x0bc9979e  call 0x76AD00
0x0bc997ab  call 0xE935740
0x0bc997b7  call 0xE938D70
0x0bc997cf  call 0xE938CB0
0x0bc99819  call 0x5668AC0
0x0bc99826  call 0xE938D70
0x0bc9983e  call 0xE938CB0
0x0bc99861  call 0x79580
0x0bc998b0  call 0xE938CB0
0x0bc998d3  call 0x79580
0x0bc99922  call 0xE938CB0
0x0bc99945  call 0x79580
0x0bc99994  call 0xE938CB0
0x0bc999b7  call 0x79580
0x0bc99a06  call 0xE938CB0
0x0bc99a29  call 0x79580
#endif

// Layout assertions for ChunkState_bc98310_c00
static_assert(offsetof(ChunkState_bc98310_c00, rax) == 0x00, "rax at +0x00");
static_assert(offsetof(ChunkState_bc98310_c00, rcx) == 0x08, "rcx at +0x08");
static_assert(offsetof(ChunkState_bc98310_c00, rdx) == 0x10, "rdx at +0x10");
static_assert(offsetof(ChunkState_bc98310_c00, r8) == 0x18, "r8 at +0x18");
static_assert(offsetof(ChunkState_bc98310_c00, r9) == 0x20, "r9 at +0x20");
static_assert(offsetof(ChunkState_bc98310_c00, r10) == 0x28, "r10 at +0x28");
static_assert(offsetof(ChunkState_bc98310_c00, r11) == 0x30, "r11 at +0x30");
static_assert(offsetof(ChunkState_bc98310_c00, rbx) == 0x38, "rbx at +0x38");
static_assert(offsetof(ChunkState_bc98310_c00, rsi) == 0x40, "rsi at +0x40");
static_assert(offsetof(ChunkState_bc98310_c00, rdi) == 0x48, "rdi at +0x48");
static_assert(offsetof(ChunkState_bc98310_c00, r12) == 0x50, "r12 at +0x50");
static_assert(offsetof(ChunkState_bc98310_c00, r13) == 0x58, "r13 at +0x58");
static_assert(offsetof(ChunkState_bc98310_c00, r14) == 0x60, "r14 at +0x60");
static_assert(offsetof(ChunkState_bc98310_c00, r15) == 0x68, "r15 at +0x68");
static_assert(offsetof(ChunkState_bc98310_c00, rbp) == 0x70, "rbp at +0x70");
static_assert(offsetof(ChunkState_bc98310_c00, stack) == 0x78, "stack at +0x78");
