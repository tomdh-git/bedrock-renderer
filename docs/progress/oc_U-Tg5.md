## NEXT
DONE

# UNIT U-Tg5 — texgroup_load 0x5421c90, slice 0x5422e4c..0x542322f (chunk 5 of 6)

Goal: instruction-complete dossier of the listed slice; every instruction covered by a phase, then a field map of every [reg+off] load/store.
Source listing: docs/progress/_part_Tg5.txt (250 instructions, precomputed by the orchestrator; not re-dumped as-is).
Coverage: phases 1-10 below cover all 250 instructions exactly once; nothing is skipped. All RVAs and instruction lines are verbatim from the listing [V].

## Phase 1: 0x5422e4c..0x5422e90 — allocate and clear the new object
Allocates a 0x70-byte object through the allocator at [0xF99FFA0], null-checks the result into rbx, and stores [rbp+0x1C0] at rbx+0x20. Zeroes rbx+0x28 and rbx+0x38 with xmm0 (32 bytes), loads r14 = [rbp+0x1D8], and when [rbp+0x1E0] is at most 0x10 saves [rbp+0x1C8] at [rbp+0x120].
0x5422e4c  mov edx,0x70
0x5422e51  call qword ptr [0xF99FFA0]
0x5422e57  nop
0x5422e58  mov rbx,rax
0x5422e5b  test rax,rax
0x5422e5e  je 0x5423427
0x5422e64  mov eax,[rbp+0x1C0]
0x5422e6a  mov [rbx+0x20],eax
0x5422e6d  xorps xmm0,xmm0
0x5422e70  movups [rbx+0x28],xmm0
0x5422e74  movups [rbx+0x38],xmm0
0x5422e78  mov r14,[rbp+0x1D8]
0x5422e7f  cmp qword ptr [rbp+0x1E0],0x10
0x5422e87  jb short 0x5422E97
0x5422e89  mov rax,[rbp+0x1C8]
0x5422e90  mov [rbp+0x120],rax

## Phase 2: 0x5422e97..0x5422eca — sign test, backpointer save, SSO fast path
Tests r14 (negative jumps to 0x5423577), saves rbx at [rbp+0x230], and for r14 at most 0xF takes the inline SSO path: stores length r14 at rbx+0x38 and capacity 0xF at rbx+0x40, copies up to 16 bytes from [rbp+0x120] into rbx+0x28 via movups, and jumps to the shared tail at 0x5422F6E.
0x5422e97  test r14,r14
0x5422e9a  mov [rbp+0x230],rbx
0x5422ea1  js 0x5423577
0x5422ea7  cmp r14,0xF
0x5422eab  ja short 0x5422ECF
0x5422ead  lea rax,[rbx+0x28]
0x5422eb1  mov [rbx+0x38],r14
0x5422eb5  mov qword ptr [rbx+0x40],0xF
0x5422ebd  mov rcx,[rbp+0x120]
0x5422ec4  movups xmm0,[rcx]
0x5422ec7  movups [rax],xmm0
0x5422eca  jmp 0x5422F6E

## Phase 3: 0x5422ecf..0x5422f52 — slow-path heap allocation
Slow path: size = r14|0xF, clamped to at least 0x16; allocates rdi+0x28 bytes when that exceeds 0xFFF else rdi+1 bytes via [0xF99FFA0], null-checks into rsi (failure targets 0x5423500 / 0x542350E), applies the aligned-allocation fix-up storing the raw pointer at [rsi-8], then stores buffer rsi at rbx+0x28, length r14 at rbx+0x38, capacity rdi at rbx+0x40, and increments r14.
0x5422ecf  mov rdx,r14
0x5422ed2  or rdx,0xF
0x5422ed6  cmp rdx,0x17
0x5422eda  mov edi,0x16
0x5422edf  cmovae rdi,rdx
0x5422ee3  mov rcx,[0x1233E1A8]
0x5422eea  mov rax,[rcx]
0x5422eed  mov rax,[rax+8]
0x5422ef1  cmp rdx,0xFFF
0x5422ef8  jb short 0x5422F25
0x5422efa  lea rbx,[rdi+0x28]
0x5422efe  mov rdx,rbx
0x5422f01  call qword ptr [0xF99FFA0]
0x5422f07  nop
0x5422f08  mov rsi,rax
0x5422f0b  test rax,rax
0x5422f0e  je 0x5423500
0x5422f14  mov rax,rsi
0x5422f17  add rsi,0x27
0x5422f1b  and rsi,0xFFFFFFFFFFFFFFE0
0x5422f1f  mov [rsi-8],rax
0x5422f23  jmp short 0x5422F3F
0x5422f25  lea rbx,[rdi+1]
0x5422f29  mov rdx,rbx
0x5422f2c  call qword ptr [0xF99FFA0]
0x5422f32  nop
0x5422f33  mov rsi,rax
0x5422f36  test rax,rax
0x5422f39  je 0x542350E
0x5422f3f  mov rbx,[rbp+0x230]
0x5422f46  mov [rbx+0x28],rsi
0x5422f4a  mov [rbx+0x38],r14
0x5422f4e  mov [rbx+0x40],rdi
0x5422f52  inc r14

## Phase 4: 0x5422f55..0x5422fb2 — buffer fill, metadata stores
Calls 0xEEC6EC0 with rcx=rsi, rdx=[rbp+0x120], r8=r14 to fill the buffer, then loads rsi=[rbp+0x228], copies 16 bytes from [rbp+0x1E8] to rbx+0x48, and stores [rbp+0x1F8] at rbx+0x58.
0x5422f55  mov rcx,rsi
0x5422f58  mov rdx,[rbp+0x120]
0x5422f5f  mov r8,r14
0x5422f62  call 0xEEC6EC0
0x5422f67  mov rsi,[rbp+0x228]
0x5422f6e  lea rax,[rbp+0x1E8]
0x5422f75  movups xmm0,[rax]
0x5422f78  movups [rbx+0x48],xmm0
0x5422f7c  mov eax,[rbp+0x1F8]
0x5422f82  mov [rbx+0x58],eax

## Phase 5: 0x5422f85..0x5423006 — object header init, intrusive list insert
Zeroes rbx+0x60, copies [rbp+0x130] into rbx/rbx+8/rbx+0x10, clears the word at rbx+0x18, increments the counter at [rsi+0x250], and loads the limit [rsi+0x248]. Then performs an intrusive list insert against rax=[rsi+0x248]: equal rewires the head slots [rax]/[rax+8]/[rax+0x10] to rbx, otherwise links [r12+0x10]=rbx and fixes tail [rax+0x10]; when r15b==0 it also rewires [r12] and head [rax]. Finally rcx=[rdx], rsi=[rbp+0x78]; if byte [rcx+0x18]==0 it exits to cold path 0x54231CD, else rbx=[rax+8] and flag byte [rbx+0x18]=1.
0x5422f85  xorps xmm0,xmm0
0x5422f88  movups [rbx+0x60],xmm0
0x5422f8c  mov rax,[rbp+0x130]
0x5422f93  mov [rbx],rax
0x5422f96  mov [rbx+8],rax
0x5422f9a  mov [rbx+0x10],rax
0x5422f9e  mov word ptr [rbx+0x18],0
0x5422fa4  inc qword ptr [rsi+0x250]
0x5422fab  mov rax,[rsi+0x248]
0x5422fb2  mov [rbx+8],r12
0x5422fb6  cmp r12,rax
0x5422fb9  je short 0x5422FD8
0x5422fbb  mov rdx,rbx
0x5422fbe  add rdx,8
0x5422fc2  test r15b,r15b
0x5422fc5  je short 0x5422FE5
0x5422fc7  mov [r12+0x10],rbx
0x5422fcc  cmp r12,[rax+0x10]
0x5422fd0  jne short 0x5422FF1
0x5422fd2  mov [rax+0x10],rbx
0x5422fd6  jmp short 0x5422FF1
0x5422fd8  mov [rax],rbx
0x5422fdb  mov [rax+8],rbx
0x5422fdf  mov [rax+0x10],rbx
0x5422fe3  jmp short 0x5423006
0x5422fe5  mov [r12],rbx
0x5422fe9  cmp r12,[rax]
0x5422fec  jne short 0x5422FF1
0x5422fee  mov [rax],rbx
0x5422ff1  mov rcx,[rdx]
0x5422ff4  cmp byte ptr [rcx+0x18],0
0x5422ff8  mov rsi,[rbp+0x78]
0x5422ffc  je 0x54231CD
0x5423002  mov rbx,[rax+8]
0x5423006  mov byte ptr [rbx+0x18],1

## Phase 6: 0x542300a..0x54230b3 — slot replacement with release/acquire
Zeroes [rbp+0x140], then, at object rcx=[rbp+0x230], stores [rbp+0x128] at +0x60, releases the old refcounted value at +0x68 (lock-dec +8, destructor via vtable at +0, lock-dec +0xC, free), stores [rbp+0x208] at +0x68 and lock-increments its +8. Finally reads +0x60 into [r13] and the acquired +0x68 into [r13+8].
0x542300a  xorps xmm0,xmm0
0x542300d  movaps [rbp+0x140],xmm0
0x5423014  mov rcx,[rbp+0x230]
0x542301b  mov rax,[rbp+0x128]
0x5423022  mov [rcx+0x60],rax
0x5423026  mov rsi,[rcx+0x68]
0x542302a  mov rax,[rbp+0x208]
0x5423031  mov [rcx+0x68],rax
0x5423035  test rsi,rsi
0x5423038  mov rdi,[rbp+0x218]
0x542303f  mov rbx,[rbp+0x100]
0x5423046  mov r13,[rbp+0x138]
0x542304d  mov r14,[rbp+0x200]
0x5423054  je short 0x542308C
0x5423056  lock dec dword ptr [rsi+8]
0x542305a  jne short 0x5423081
0x542305c  mov rax,[rsi]
0x542305f  mov rax,[rax]
0x5423062  mov rcx,rsi
0x5423065  call qword ptr [0xF99FFA0]
0x542306b  lock dec dword ptr [rsi+0xC]
0x542306f  jne short 0x5423081
0x5423071  mov rax,[rsi]
0x5423074  mov rax,[rax+8]
0x5423078  mov rcx,rsi
0x542307b  call qword ptr [0xF99FFA0]
0x5423081  mov rax,[rbp+0x230]
0x5423088  mov rax,[rax+0x68]
0x542308c  test rax,rax
0x542308f  je short 0x54230A2
0x5423091  lock inc dword ptr [rax+8]
0x5423095  mov rcx,[rbp+0x230]
0x542309c  mov rax,[rcx+0x68]
0x54230a0  jmp short 0x54230AB
0x54230a2  xor eax,eax
0x54230a4  mov rcx,[rbp+0x230]
0x54230ab  mov rcx,[rcx+0x60]
0x54230af  mov [r13],rcx
0x54230b3  mov [r13+8],rax

## Phase 7: 0x54230b7..0x542311f — release two frame objects
Releases the two frame objects rsi=[rbp+0x148] and rsi=[rbp+0x118]: each via lock-dec at +8 (destructor via vtable at +0 on zero) and lock-dec at +0xC (free path on zero).
0x54230b7  mov rsi,[rbp+0x148]
0x54230be  test rsi,rsi
0x54230c1  je short 0x54230EE
0x54230c3  lock dec dword ptr [rsi+8]
0x54230c7  jne short 0x54230EE
0x54230c9  mov rax,[rsi]
0x54230cc  mov rax,[rax]
0x54230cf  mov rcx,rsi
0x54230d2  call qword ptr [0xF99FFA0]
0x54230d8  lock dec dword ptr [rsi+0xC]
0x54230dc  jne short 0x54230EE
0x54230de  mov rax,[rsi]
0x54230e1  mov rax,[rax+8]
0x54230e5  mov rcx,rsi
0x54230e8  call qword ptr [0xF99FFA0]
0x54230ee  mov rsi,[rbp+0x118]
0x54230f5  test rsi,rsi
0x54230f8  je short 0x5423125
0x54230fa  lock dec dword ptr [rsi+8]
0x54230fe  jne short 0x5423125
0x5423100  mov rax,[rsi]
0x5423103  mov rax,[rax]
0x5423106  mov rcx,rsi
0x5423109  call qword ptr [0xF99FFA0]
0x542310f  lock dec dword ptr [rsi+0xC]
0x5423113  jne short 0x5423125
0x5423115  mov rax,[rsi]
0x5423118  mov rax,[rax+8]
0x542311c  mov rcx,rsi
0x542311f  call qword ptr [0xF99FFA0]

## Phase 8: 0x5423125..0x54231b1 — release self object, long-string tail free
Releases r14=[rbp+0x200] via lock-dec at +0xC, then lock-dec's the object's own refcount [rbx]; on zero it calls the destructor through [rdi]'s vtable and releases [rbp+0x108]. The long-string tail frees the old heap buffer [rbp+0x1C8] via 0xE935700 when size field [rbp+0x1E0] exceeds 0x10.
0x5423125  test r14,r14
0x5423128  je short 0x5423141
0x542312a  lock dec dword ptr [r14+0xC]
0x542312f  jne short 0x5423141
0x5423131  mov rax,[r14]
0x5423134  mov rax,[rax+8]
0x5423138  mov rcx,r14
0x542313b  call qword ptr [0xF99FFA0]
0x5423141  lock dec dword ptr [rbx]
0x5423144  jne short 0x5423171
0x5423146  mov rax,[rdi]
0x5423149  mov rax,[rax]
0x542314c  mov rcx,rdi
0x542314f  call qword ptr [0xF99FFA0]
0x5423155  mov rax,[rbp+0x108]
0x542315c  lock dec dword ptr [rax]
0x542315f  jne short 0x5423171
0x5423161  mov rax,[rdi]
0x5423164  mov rax,[rax+8]
0x5423168  mov rcx,rdi
0x542316b  call qword ptr [0xF99FFA0]
0x5423171  mov rax,[rbp+0x1E0]
0x5423178  cmp rax,0x10
0x542317c  jb short 0x54231B6
0x542317e  mov rcx,[rbp+0x1C8]
0x5423185  lea rdx,[rax+1]
0x5423189  cmp rdx,0x1000
0x5423190  jb short 0x54231B1
0x5423192  mov r8,[rcx-8]
0x5423196  add rcx,0xFFFFFFFFFFFFFFF8
0x542319a  sub rcx,r8
0x542319d  cmp rcx,0x20
0x54231a1  jae 0x542357D
0x54231a7  add rax,0x28
0x54231ab  mov rdx,rax
0x54231ae  mov rcx,r8
0x54231b1  call 0xE935700

## Phase 9: 0x54231b6..0x54231cc — epilogue
Returns rax=r13, restores the frame (add rsp,0x2C8; pop rbx, rdi, rsi, r12, r13, r14, r15, rbp) and rets.
0x54231b6  mov rax,r13
0x54231b9  add rsp,0x2C8
0x54231c0  pop rbx
0x54231c1  pop rdi
0x54231c2  pop rsi
0x54231c3  pop r12
0x54231c5  pop r13
0x54231c7  pop r14
0x54231c9  pop r15
0x54231cb  pop rbp
0x54231cc  ret

## Phase 10: 0x54231cd..0x542322f — cold list-node loop
Cold path entered from 0x5422ffc: a list-node loop marking flag bytes at +0x18 while walking forward links [rcx+8], exiting back to 0x5423002 on an already-marked node; the slice ends at 0x542322f with rdx=rcx.
0x54231cd  lea r10,[rcx+0x18]
0x54231d1  jmp short 0x5423214
0x54231d3  nop [rax+rax]
0x54231e0  mov byte ptr [r10],1
0x54231e4  mov byte ptr [r11+0x18],1
0x54231e9  mov rcx,[rdx]
0x54231ec  mov rcx,[rcx+8]
0x54231f0  mov byte ptr [rcx+0x18],0
0x54231f4  mov rcx,[rdx]
0x54231f7  mov rcx,[rcx+8]
0x54231fb  mov rbx,rcx
0x54231fe  lea rdx,[rcx+8]
0x5423202  mov rcx,[rcx+8]
0x5423206  lea r10,[rcx+0x18]
0x542320a  cmp byte ptr [rcx+0x18],0
0x542320e  jne 0x5423002
0x5423214  mov r8,[rcx+8]
0x5423218  mov r11,[r8]
0x542321b  cmp rcx,r11
0x542321e  je short 0x5423240
0x5423220  cmp byte ptr [r11+0x18],0
0x5423225  je short 0x54231E0
0x5423227  mov rdx,[rcx]
0x542322a  cmp rbx,rdx
0x542322d  je short 0x542325F
0x542322f  mov rdx,rcx

## Field map: every [reg+off] load/store in the slice
Columns: offset | size | direction | sites | meaning
Direction: R = read, W = store, R/W = mixed across sites, RW = read-modify-write (lock inc/dec). Size comes from the instruction (movups/movaps 16, qword 8, dword 4, word 2, byte 1). Meaning is given only when an instruction shows it, otherwise '-'. Sites are verbatim `0xRVA  instr` lines; one row per distinct offset.

| offset | size | direction | sites | meaning |
| -8 | 8 | R/W | 0x5422f1f  mov [rsi-8],rax<br>0x5423192  mov r8,[rcx-8] | - |
| 0 | 16, 8, 4, 1 | R/W | 0x5422ec4  movups xmm0,[rcx]<br>0x5422ec7  movups [rax],xmm0<br>0x5422f75  movups xmm0,[rax]<br>0x5422f93  mov [rbx],rax<br>0x5422fd8  mov [rax],rbx<br>0x5422fe5  mov [r12],rbx<br>0x5422fe9  cmp r12,[rax]<br>0x5422fee  mov [rax],rbx<br>0x5422ff1  mov rcx,[rdx]<br>0x542305c  mov rax,[rsi]<br>0x54230af  mov [r13],rcx<br>0x54230c9  mov rax,[rsi]<br>0x54230de  mov rax,[rsi]<br>0x5423100  mov rax,[rsi]<br>0x5423115  mov rax,[rsi]<br>0x5423131  mov rax,[r14]<br>0x5423141  lock dec dword ptr [rbx]<br>0x5423146  mov rax,[rdi]<br>0x542315c  lock dec dword ptr [rax]<br>0x5423161  mov rax,[rdi]<br>0x54231e0  mov byte ptr [r10],1<br>0x54231e9  mov rcx,[rdx]<br>0x54231f4  mov rcx,[rdx]<br>0x5423218  mov r11,[r8]<br>0x5423227  mov rdx,[rcx] | - |
| 8 | 8, 4 | R/W | 0x5422f96  mov [rbx+8],rax<br>0x5422fb2  mov [rbx+8],r12<br>0x5422fdb  mov [rax+8],rbx<br>0x5423002  mov rbx,[rax+8]<br>0x5423056  lock dec dword ptr [rsi+8]<br>0x5423074  mov rax,[rax+8]<br>0x5423091  lock inc dword ptr [rax+8]<br>0x54230b3  mov [r13+8],rax<br>0x54230c3  lock dec dword ptr [rsi+8]<br>0x54230e1  mov rax,[rax+8]<br>0x54230fa  lock dec dword ptr [rsi+8]<br>0x5423118  mov rax,[rax+8]<br>0x5423164  mov rax,[rax+8]<br>0x54231ec  mov rcx,[rcx+8]<br>0x54231f7  mov rcx,[rcx+8]<br>0x5423202  mov rcx,[rcx+8]<br>0x5423214  mov r8,[rcx+8] | - |
| c | 4 | RW | 0x542306b  lock dec dword ptr [rsi+0xC]<br>0x54230d8  lock dec dword ptr [rsi+0xC]<br>0x542310f  lock dec dword ptr [rsi+0xC]<br>0x542312a  lock dec dword ptr [r14+0xC] | refcount: lock-dec release path |
| 10 | 8 | R/W | 0x5422f9a  mov [rbx+0x10],rax<br>0x5422fc7  mov [r12+0x10],rbx<br>0x5422fcc  cmp r12,[rax+0x10]<br>0x5422fd2  mov [rax+0x10],rbx<br>0x5422fdf  mov [rax+0x10],rbx | - |
| 18 | 1, 2 | R/W | 0x5422f9e  mov word ptr [rbx+0x18],0<br>0x5422ff4  cmp byte ptr [rcx+0x18],0<br>0x5423006  mov byte ptr [rbx+0x18],1<br>0x54231e4  mov byte ptr [r11+0x18],1<br>0x54231f0  mov byte ptr [rcx+0x18],0<br>0x542320a  cmp byte ptr [rcx+0x18],0<br>0x5423220  cmp byte ptr [r11+0x18],0 | flag byte: word-cleared at init, set to 1 when linked, tested by list walk |
| 20 | 4 | W | 0x5422e6a  mov [rbx+0x20],eax | - |
| 28 | 16, 8 | W | 0x5422e70  movups [rbx+0x28],xmm0<br>0x5422f46  mov [rbx+0x28],rsi | data pointer: inline SSO buffer (zeroed/copied here) or heap pointer |
| 38 | 16, 8 | W | 0x5422e74  movups [rbx+0x38],xmm0<br>0x5422eb1  mov [rbx+0x38],r14<br>0x5422f4a  mov [rbx+0x38],r14 | length: r14 stored here |
| 40 | 8 | W | 0x5422eb5  mov qword ptr [rbx+0x40],0xF<br>0x5422f4e  mov [rbx+0x40],rdi | capacity: 0xF for SSO, computed rdi otherwise |
| 48 | 16 | W | 0x5422f78  movups [rbx+0x48],xmm0 | - |
| 58 | 4 | W | 0x5422f82  mov [rbx+0x58],eax | - |
| 60 | 16, 8 | R/W | 0x5422f88  movups [rbx+0x60],xmm0<br>0x5423022  mov [rcx+0x60],rax<br>0x54230ab  mov rcx,[rcx+0x60] | object slot: [rbp+0x128] stored here, read back into [r13] |
| 68 | 8 | R/W | 0x5423026  mov rsi,[rcx+0x68]<br>0x5423031  mov [rcx+0x68],rax<br>0x5423088  mov rax,[rax+0x68]<br>0x542309c  mov rax,[rcx+0x68] | slot: old refcounted value released before new value is stored and acquired |
| 78 | 8 | R | 0x5422ff8  mov rsi,[rbp+0x78] | - |
| 100 | 8 | R | 0x542303f  mov rbx,[rbp+0x100] | - |
| 118 | 8 | R | 0x54230ee  mov rsi,[rbp+0x118] | - |
| 120 | 8 | R/W | 0x5422e90  mov [rbp+0x120],rax<br>0x5422ebd  mov rcx,[rbp+0x120]<br>0x5422f58  mov rdx,[rbp+0x120] | saved copy source [rbp+0x1C8] |
| 128 | 8 | R | 0x542301b  mov rax,[rbp+0x128] | - |
| 130 | 8 | R | 0x5422f8c  mov rax,[rbp+0x130] | - |
| 138 | 8 | R | 0x5423046  mov r13,[rbp+0x138] | - |
| 140 | 16 | W | 0x542300d  movaps [rbp+0x140],xmm0 | - |
| 148 | 8 | R | 0x54230b7  mov rsi,[rbp+0x148] | - |
| 1c0 | 4 | R | 0x5422e64  mov eax,[rbp+0x1C0] | - |
| 1c8 | 8 | R | 0x5422e89  mov rax,[rbp+0x1C8]<br>0x542317e  mov rcx,[rbp+0x1C8] | - |
| 1d8 | 8 | R | 0x5422e78  mov r14,[rbp+0x1D8] | length: loaded into r14 |
| 1e0 | 8 | R | 0x5422e7f  cmp qword ptr [rbp+0x1E0],0x10<br>0x5423171  mov rax,[rbp+0x1E0] | SSO threshold compared to 0x10 |
| 1f8 | 4 | R | 0x5422f7c  mov eax,[rbp+0x1F8] | - |
| 200 | 8 | R | 0x542304d  mov r14,[rbp+0x200] | - |
| 218 | 8 | R | 0x5423038  mov rdi,[rbp+0x218] | - |
| 228 | 8 | R | 0x5422f67  mov rsi,[rbp+0x228] | - |
| 230 | 8 | R/W | 0x5422e9a  mov [rbp+0x230],rbx<br>0x5422f3f  mov rbx,[rbp+0x230]<br>0x5423014  mov rcx,[rbp+0x230]<br>0x5423081  mov rax,[rbp+0x230]<br>0x5423095  mov rcx,[rbp+0x230]<br>0x54230a4  mov rcx,[rbp+0x230] | object backpointer: rbx saved here |
| 248 | 8 | R | 0x5422fab  mov rax,[rsi+0x248] | intrusive list head (rax): [rax]/[rax+8]/[rax+0x10] rewired on insert |
| 250 | 8 | RW | 0x5422fa4  inc qword ptr [rsi+0x250] | counter: incremented |

## TOOL REQUESTS
None
