// LIFT 0xbc57460 size 0x2e2f 1.26.62.01 sub_bc57460
// CHUNK 0xbc58a85..0xbc5a261

// chunk state documented in docs/functions/bc57460.md section 'Chunk state'
struct ChunkState_bc57460_c01 {
    void* rbp;
    void* r12_ctx;
    void* r15;
    void* rsi;
    void* rdi;
    void* rbx;
};

#if 0
0xbc58a85  lea rsi,[rbp+0x98]
0xbc58a8c  mov [rbp+0x1B0],rcx
0xbc58a93  mov [rbp+0x1B8],rax
0xbc58aa8  call 0x568AD40
0xbc58cdc  call qword ptr [0xF99FFA0]
0xbc58df8  call 0x76A8A0
0xbc58e5b  mov r9,[rbp+0x770]
0xbc58f36  mov rcx,[rax+0x30]
0xbc5914f  mov rax,[rcx]
0xbc59159  call qword ptr [0xF99FFA0]
0xbc5917f  call qword ptr [0xF99FFA0]
0xbc5920f  call qword ptr [0xF99FFA0]
0xbc592b1  call qword ptr [0xF99FFA0]
0xbc592d7  call qword ptr [0xF99FFA0]
0xbc59577  call qword ptr [0xF99FFA0]
0xbc595a2  call qword ptr [0xF99FFA0]
0xbc595e5  call 0xEEC6EC0
0xbc59618  jmp 0xBC59828
0xbc596c4  call qword ptr [0xF99FFA0]
0xbc596f9  call qword ptr [0xF99FFA0]
0xbc5970b  call 0x9BC830
0xbc59714  mov rax,[rbp+0x870]
0xbc59718  call 0x130EE0
0xbc5981d  mov rcx,[rbp+0x8A0]
0xbc59828  lea rdx,[rbp+0x670]
0xbc5983b  call 0x56939C0
0xbc5984f  mov rcx,[rbp+0x8A0]
0xbc59856  call 0x56939C0
0xbc59863  mov rcx,[rbp+0x8A0]
0xbc5986a  call 0x56939C0
0xbc598bf  call 0x9D6D0
0xbc598de  call 0xEEC6DE0
0xbc59950  call 0xE935700
0xbc59955  mov qword ptr [rbp+0x638],0
0xbc59972  lea rcx,[rbp+0x410]
0xbc59979  call 0xBC5B720
0xbc599be  call 0xE935700
0xbc59a03  call 0xE935700
0xbc59a48  call 0xE935700
0xbc59a54  call 0xBC5B720
0xbc59a99  call 0xE935700
0xbc59ade  call 0xE935700
0xbc59b23  call 0xE935700
0xbc59b6e  movss [r14+0x34],xmm1
0xbc59b9e  mov rcx,[rbp+0x180]
0xbc59bd9  lea rsi,[rbp+0x180]
0xbc59be0  call 0xE935700
0xbc59bf3  mov rdi,[rbp+0x40]
0xbc59c0b  call qword ptr [0xF99FFA0]
0xbc59c21  call qword ptr [0xF99FFA0]
0xbc59c27  mov rdi,[rbp+0x758]
0xbc59c42  call qword ptr [0xF99FFA0]
0xbc59c58  call qword ptr [0xF99FFA0]
0xbc59c61  movaps xmm6,[rbp+0x8C0]
0xbc59c68  movaps xmm7,[rbp+0x8D0]
0xbc59cc2  ret
0xbc59cc3  call 0x78ED0
0xbc59cce  call 0x9BC830
0xbc59cd9  mov ecx,0x130
0xbc59ce3  nop
0xbc59ce4  jmp 0xBC58CEF
0xbc59ce9  mov ecx,0x258
0xbc59cf3  nop
0xbc59cf4  jmp 0xBC59222
0xbc59cf9  mov rcx,r15
0xbc59d01  nop
0xbc59d02  jmp 0xBC5958A
0xbc59d07  mov rcx,r15
0xbc59d0a  call 0x9BC830
0xbc59d10  xor r14d,r14d
0xbc59d13  jmp 0xBC595B5
0xbc59d18  mov rcx,r12
0xbc59d1b  call 0x9BC830
0xbc59d20  nop
0xbc59d21  jmp 0xBC596D7
0xbc59d26  mov qword ptr [rsp+0x20],0
0xbc59d39  call qword ptr [0xF9A8C78]
0xbc59d46  call 0xE938CB0
0xbc59d6c  call 0x79580
0xbc59da2  mov rcx,0xCBF29CE484222325
0xbc59db4  lea rcx,[0x12ADF760]
0xbc59dbb  call 0xE938CB0
0xbc59dd7  lea r12,[rbp+0x410]
0xbc59de1  call 0x79580
0xbc59e29  lea rcx,[0x12ADF770]
0xbc59e30  call 0xE938CB0
0xbc59e4c  lea r12,[rbp+0x410]
0xbc59e56  call 0x79580
0xbc59e9e  lea rcx,[0x12ADF780]
0xbc59ea5  call 0xE938CB0
0xbc59ec8  mov rcx,r12
0xbc59ecb  call 0x79580
0xbc59f1e  lea rcx,[0x12ADF798]
0xbc59f25  call 0xE938CB0
0xbc59f3e  lea rax,[0xF5B49BF]
0xbc59f57  lea rcx,[0x12ADF788]
0xbc59f65  lea r8,[rbp-0x20]
0xbc59f69  call 0x5668AC0
0xbc59f6f  lea rcx,[0x12ADF798]
0xbc59f76  call 0xE938D70
0xbc59f7b  jmp 0xBC57724
0xbc59f80  mov [rbp+0x880],r8
0xbc59f87  call 0x75720
0xbc59f8d  mov [rbp+0x878],rcx
0xbc59f94  mov [rbp+0x880],r9
0xbc59f9b  call 0x75740
0xbc59fa0  nop
0xbc5a062  mov [0x12ADF748],rcx
0xbc5a069  lea rcx,[rbp+0x410]
0xbc5a070  call 0x73150
0xbc5a075  lea rcx,[0x12ADF750]
0xbc5a07c  call 0xE938D70
0xbc5a081  mov r12,r13
0xbc5a084  jmp 0xBC575B7
0xbc5a10e  mov [0x12ADF758],rcx
0xbc5a115  lea rcx,[rbp+0x410]
0xbc5a11c  call 0x73150
0xbc5a121  lea rcx,[0x12ADF760]
0xbc5a128  call 0xE938D70
0xbc5a12d  mov r12,r13
0xbc5a130  mov r13,[rbp+0x8A0]
0xbc5a137  jmp 0xBC5761A
0xbc5a1c1  mov [0x12ADF768],rcx
0xbc5a1c8  lea rcx,[rbp+0x410]
0xbc5a1cf  call 0x73150
0xbc5a1d4  lea rcx,[0x12ADF770]
0xbc5a1db  call 0xE938D70
0xbc5a1e0  mov r12,r13
0xbc5a1e3  mov r13,[rbp+0x8A0]
0xbc5a1ea  jmp 0xBC57676
0xbc5a261  mov [0x12ADF778],rcx
0xbc5a268  lea rcx,[rbp+0x410]
0xbc5a26f  call 0x73150
0xbc5a274  lea rcx,[0x12ADF780]
0xbc5a27b  call 0xE938D70
0xbc5a280  mov r12,r13
0xbc5a283  jmp 0xBC576FF
#endif

static inline void sub_bc57460_chunk_c01(ChunkState_bc57460_c01& s) {
    // 0xbc58a85..0xbc58a9a
    // lea rsi,[rbp+0x98]; mov [rbp+0x1B0],rcx; mov [rbp+0x1B8],rax; lea rcx,[rbp+0x6C0]; lea rdx,[rbp+0x1B0]
    // 0xbc58aa8..0xbc58aad
    // call 0x568AD40 (sub_568ad40)
    // 0xbc58aae..0xbc58aca
    // movups xmm0,[rbp+0x6C0]; movups xmm1,[rbp+0x6D0]; movaps [rbp+0x1E0],xmm1; movaps [rbp+0x1D0],xmm0
    // 0xbc58aca..0xbc58ae7
    // mov qword ptr [rbp+0x6D0],0; mov qword ptr [rbp+0x6D8],0xF; mov byte ptr [rbp+0x6C0],0
    // 0xbc58ae7..0xbc58b6f
    // movaps xmm0,[rbp]; ... (copy frame locals into scratch slot [rbp+0x1F0..0x278])
    // 0xbc58b6f..0xbc58b7d
    // mov rax,[rsi+0x10]; mov [rbp+0x298],rax; movups xmm1,[rsi]; movups [rbp+0x288],xmm1
    // 0xbc58b84..0xbc58c66
    // movaps [rbp+0x2A0..0x340], xmm from [rbp+0xB0..0x160]; movsd [rbp+0x350]; movss [rbp+0x358]; mov [rbp+0x36C]; movups [rbp+0x35C]
    // 0xbc58c66..0xbc58ca4
    // mov byte ptr [rbp+0x388],0; cmp byte ptr [rbp+0x198],1; jne loc_bc58ca4; (conditional copy of [rbp+0x180..0x190] into [rbp+0x370..0x380] setting byte [rbp+0x388]=1)
    // 0xbc58ca4..0xbc58ce3
    // mov [rbp+0x398],[rbp+0x1A8]; mov [rbp+0x390],[rbp+0x1A0]; mov qword ptr [rbp+0x3D8],0; mov rcx,[0x1233E1A8]; mov rax,[rcx]; mov rax,[rax+8]; mov edx,0x130; call qword ptr [0xF99FFA0] (alloc 0x130 bytes -> rdi)
    // 0xbc58ce6..0xbc58cef
    // test rax,rax; je 0xBC59CD9
    // 0xbc58cef..0xbc58dd5
    // init allocated block rdi with identity-ish transform constants (0x3F800000, xmm0 zero, xmm1 from [0xEFD3400])
    // 0xbc58dd5..0xbc58de3
    // cmp qword ptr [rbp+0x3D8],0; jne 0xBC59CC3; mov [rbp+0x3D8],rdi
    // 0xbc58dea..0xbc58dfd
    // lea rcx,[rbp+0x830]; lea rdx,[rbp+0x790]; call 0x76A8A0 (sub_76a8a0)
    // 0xbc58dfe..0xbc58f36
    // move [rbp+0x1F0..] into [rbp+0x7E8..0x850] and [rbp+0x6F0..0x748]; zero [rbp+0x1D0]
    // 0xbc58f36..0xbc58f61
    // mov rcx,[rax+0x30]; mov [rbp+0x460],rcx; movups [rbp+0x430..0x450] from [rax+0x0..0x20]
    // 0xbc58f61..0xbc5911c
    // copy [rbp+0x228..0x388] into [rbp+0x468..0x5D8] (conditional copy of [rbp+0x370..0x380] into [rbp+0x5B0..0x5C0] with byte flag)
    // 0xbc5911c..0xbc59190
    // lea rbx,[rbp+0x5E0]; mov qword ptr [rbp+0x618],0; if [rbp+0x3D8] (rcx) nonzero and != rdi (rbp+0x3A0) allocate via [0xF99FFA0] or destroy; zero [rbp+0x3D8]
    // 0xbc59190..0xbc5920f
    // movups from rsi-0x28/rsi into [rbp+0x628..0x670]; zero counters; mov rax,[rbp+0x6F0]; mov [rbp+0x620],rax; movups from rsi+0x0..+0x20 into [rbp+0x650..0x670]; mov rcx,[0x1233E1A8]; mov rax,[rcx]; mov rax,[rax+8]; mov edx,0x258; call qword ptr [0xF99FFA0] (alloc 0x258 -> r15)
    // 0xbc59215..0xbc5921c
    // test rax,rax; je 0xBC59CE9
    // 0xbc59222..0xbc592e8
    // init r15 block: r14=rbp+0x430; mov [r15+8]=0x100000001; [r15]=data_f098020; r12=[rbp+0x428]; rsi=[rbp+0x410]; rdi=[rbp+0x420]; xmm6=0; zero [r15+0x18..0x40]; [r15+0x10]=data_f4412b0; r13=r15+0x48; [r15+0x80]=0; if [rbp+0x618] nonzero allocate/destroy into [r15+0x80]; zero [rbp+0x618]
    // 0xbc592e8..0xbc594da
    // copy r14 (rbp+0x430) fields into r15+0x88..0x220; copy [rbp+0x468] into [r15+0xC0]; conditional copy of [rbp+0x5B0..0x5C0] into [r15+0x208..0x218] with byte flag [r15+0x220]; set [rbp+0x878]=r13; rdx=r15+0x10; r8=r15+0x88; [r15+0x230]=ecx (from rax+8); [r15+0x228]=rax (from rax); zero [r15+0x238..0x250]; [rbp+0x8A8]=r15; [rbp+0x870]=rdx
    // 0xbc59500..0xbc595ee
    // if rdi (length) js -> loc; allocate buffer rbx (r15+0x238) of size derived from rdi via alloc at [0x1233E1A8]; copy src rsi/r12 into rbx via sub_eec6ec0; mov byte ptr [rbx+rdi],0
    // 0xbc595ee..0xbc59619
    // rsi=[rcx+0x10] (ctx+0x10); if rsi==[rcx+0x18] (full) goto grow (0xBC5961E); else store [rsi]=rdx (rbp+0x870), [rsi+8]=r14 (r15); advance [rcx+0x10]+=0x10; jump 0xBC59828
    // 0xbc5961e..0xbc5980c
    // grow vector: compute new capacity (rsi-rdi base)/16, +1, grow half, clamp to max; allocate via alloc (with alignment path for >=0x100); copy old elements (16 bytes) into new buffer, zeroing old; call sub_130ee0 to move
    // 0xbc5980c..0xbc59828
    // mov rcx,rdi; mov rdx,r15; mov r8,rbx; mov r9,r14; call 0x130EE0; mov rcx,[rbp+0x8A0]; mov rax,[rcx+0x10]
    // 0xbc59828..0xbc598e7
    // lea rdx,[rbp+0x670]; mov byte ptr [rcx+0x60],1; mov [rcx+0x58],rax (prev-0x10); call 0x56939C0 (x3 with rdx=[rbp+0x660],[rbp+0x650]); copy [rbp+0x620] into [rsi+8] etc; string copy into [rsi+0x10] via sub_9d6d0/sub_eec6de0 if needed
    // 0xbc598e7..0xbc59972
    // free [rbp+0x628] string if capacity>=0x10; zero counters; free [rbp+0x6F8] string; free [rbp+0x7F0] string; free [rbp+0x838] string
    // 0xbc59972..0xbc5997e
    // lea rcx,[rbp+0x410]; call 0xBC5B720 (sub_bc5b720)
    // 0xbc5997e..0xbc59a9e
    // free strings at [rbp+0x710],[rbp+0x808],[rbp+0x850],[rbp+0x1D0],[rbp+0x6D8],[rbp+0x400],[rbp+0x7A8]
    // 0xbc59a9e..0xbc59b28
    // rax=[rbp+0x760]; store into [r14+0x0/0x8/0x18/0x20]; cvtsi2ss xmm0,[rsi]; set bytes [r14+0x10]=1,[r14+0x28]=1; store xmm1 from [rbp+0x7C0] into [r14+0x30], [rbp+0x7D0] into [r14+0x34], [rbp+0x894] into [r14+0x38], xmm0 into [r14+0x3C], xmm7 into [r14+0x40]
    // 0xbc59b28..0xbc59b95
    // if byte [rbp+0x198]==1 and [rbp+0x180] nonzero: free [rbp+0x180..0x190] string via sub_e935700; zero it
    // 0xbc59b95..0xbc59c27
    // rdi=[rbp+0x40]; if nonzero lock dec [rdi+8], if zero free via vtable slot 0 and slot 8 (alloc)
    // 0xbc59c27..0xbc59c5e
    // rdi=[rbp+0x758]; if nonzero lock dec [rdi+8], if zero free via vtable slot 0 and slot 8 (alloc)
    // 0xbc59c5e..0xbc59cc2
    // rax=r14 (return value); restore xmm6..xmm15; add rsp,0x9E8; pop rbx/rdi/rsi/r12/r13/r14/r15/rbp; ret
    // 0xbc59cc3..0xbc59ce4
    // call sub_78ed0; mov ecx,0x20; call sub_9bc830; jmp 0xBC589D0  (error path, never returns normally)
    // 0xbc59cd9..0xbc59ce4
    // mov ecx,0x130; call sub_9bc830; nop; jmp 0xBC58CEF
    // 0xbc59ce9..0xbc59cf4
    // mov ecx,0x258; call sub_9bc830; nop; jmp 0xBC59222
    // 0xbc59cf9..0xbc59d14
    // mov rcx,r15; call sub_9bc830; nop; xor r14d,r14d; jmp 0xBC595B5
    // 0xbc59d18..0xbc59d21
    // mov rcx,r12; call sub_9bc830; nop; jmp 0xBC596D7
    // 0xbc59d26..0xbc59fa0
    // error/lookup path: call [0xF9A8C78]; call sub_e938cb0 on 0x12ADF750; if not -1 jump 0xBC575B7; compute FNV hash of r12/rbp+0x410 string for "zLights"/"Extends"/"zLightLookupArray"/"ClusterDimensions"; store into 0x12ADF748/0x12ADF758/0x12ADF768/0x12ADF778; call sub_73150 + sub_e938d70 to release; jump back to main loop at 0xBC575B7/0xBC5761A/0xBC57676/0xBC576FF
    // 0xbc59fa1..0xbc59fbf
    // rcx = 0xCBF29CE484222325 (FNV offset basis) for empty-string cases
    // 0xbc59fce..0xbc5a283
    // FNV hash tail loops storing into 0x12ADF778; release; jump 0xBC576FF
    // 0xbc5a288..0xbc5a28f
    // call sub_75740; nop; int3; nop (unreachable terminator)
    (void)s;
}
