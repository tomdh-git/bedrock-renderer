## NEXT
DONE

# UNIT U-Sa6 — instruction slice 0x66a80db..0x66a8515

Slice: chunk 6 of 7 of effect_shadow_extractor_alt_66a6830_66a88c8 (shadow extractor alt 0x66a6830), RVAs relative to the 1.26.62.01 image base.
Input: docs/progress/_part_Sa6.txt (250 instructions). All 250 are quoted verbatim in the phases below and re-indexed by offset in the field map. Every claim is [V] (seen in this disassembly; the input listing was diffed against rdis on the exe — 0 mismatches). Field-map meaning is '-' unless an instruction or string in the slice shows it.

## Phase 1: 0x66a80db..0x66a80f9 — First extractor call: ax is stored at [rbp+0x2BE], then rcx = *[0x1233E1B0], rax = *rcx, call *qword ptr [0xF99FFA0] with rax = *(rax+0x10) and dl = 0x4A, and AL is stored at [rbp+0x580].
0x66a80db  mov [rbp+0x2BE],ax
0x66a80e2  mov rcx,[0x1233E1B0]
0x66a80e9  mov rax,[rcx]
0x66a80ec  mov rax,[rax+0x10]
0x66a80f0  mov dl,0x4A
0x66a80f2  call qword ptr [0xF99FFA0]
0x66a80f8  nop
0x66a80f9  mov [rbp+0x580],al

## Phase 2: 0x66a80ff..0x66a8189 — Shadow-record fast path: if cursor [rsi+0x758] != end [rsi+0x760] (else jump to 0x66A818B), copy one 0x58-byte record from the local staging area addressed via [rbp+0x364] into [rdx] = [rsi+0x758]: dword [rcx+0x10], 16-byte block [rcx], byte flag [rbp+0x378] -> [rdx+0x14], floats [rbp+0x37C..0x388] -> [rdx+0x18..0x24], 16-byte blocks [rbp+0x38C]/[rbp+0x39C]/[rbp+0x3AB] -> [rdx+0x28/+0x38/+0x47], then add 0x58 to [rsi+0x758] and jump to 0x66A81A2.
0x66a80ff  mov rdx,[rsi+0x758]
0x66a8106  cmp rdx,[rsi+0x760]
0x66a810d  je short 0x66A818B
0x66a810f  lea rcx,[rbp+0x364]
0x66a8116  mov eax,[rcx+0x10]
0x66a8119  mov [rdx+0x10],eax
0x66a811c  movups xmm0,[rcx]
0x66a811f  movups [rdx],xmm0
0x66a8122  movzx eax,byte ptr [rbp+0x378]
0x66a8129  mov [rdx+0x14],al
0x66a812c  movss xmm0,[rbp+0x37C]
0x66a8134  movss [rdx+0x18],xmm0
0x66a8139  movss xmm0,[rbp+0x380]
0x66a8141  movss [rdx+0x1C],xmm0
0x66a8146  movss xmm0,[rbp+0x384]
0x66a814e  movss [rdx+0x20],xmm0
0x66a8153  movss xmm0,[rbp+0x388]
0x66a815b  movss [rdx+0x24],xmm0
0x66a8160  movups xmm0,[rbp+0x38C]
0x66a8167  movups xmm1,[rbp+0x39C]
0x66a816e  movups xmm2,[rbp+0x3AB]
0x66a8175  movups [rdx+0x28],xmm0
0x66a8179  movups [rdx+0x38],xmm1
0x66a817d  movups [rdx+0x47],xmm2
0x66a8181  add qword ptr [rsi+0x758],0x58
0x66a8189  jmp short 0x66A81A2

## Phase 3: 0x66a818b..0x66a81bd — Cursor-full path: rcx = rsi+0x750, r8 = &staging area [rbp+0x364], call 0x6760A80, nop, then the global-indirect call rcx = *[0x1233E1B0], rax = *rcx, rax = *(rax+0x10), dl = 0x4A, call *qword ptr [0xF99FFA0], nop (AL is stored at [rbp+0x580] in the next phase).
0x66a818b  mov rcx,rsi
0x66a818e  add rcx,0x750
0x66a8195  lea r8,[rbp+0x364]
0x66a819c  call 0x6760A80
0x66a81a1  nop
0x66a81a2  mov rcx,[0x1233E1B0]
0x66a81a9  mov rax,[rcx]
0x66a81ac  mov rax,[rax+0x10]
0x66a81b0  movzx edx,byte ptr [rbp+0x580]
0x66a81b7  call qword ptr [0xF99FFA0]
0x66a81bd  nop

## Phase 4: 0x66a81be..0x66a81fd — Straight-line join point (target of the jmp at 0x66a8189, fall-through of the call-0x6760A80 path): store constant qword 0x2807021 at [rbp+0x280]; compute eax = (([rsi+0x758] - [rsi+0x750]) >> 3) * 0xFFFF8BA3 - 1 and store ax at [rbp+0x2AC]; then the global-indirect call rcx = *[0x1233E1B0], rax = *rcx, rax = *(rax+0x10), dl = 0x4A, call *qword ptr [0xF99FFA0], nop.
0x66a81be  mov qword ptr [rbp+0x280],0x2807021
0x66a81c9  mov eax,[rsi+0x758]
0x66a81cf  sub eax,[rsi+0x750]
0x66a81d5  shr eax,3
0x66a81d8  imul eax,0xFFFF8BA3
0x66a81de  dec eax
0x66a81e0  mov [rbp+0x2AC],ax
0x66a81e7  mov rcx,[0x1233E1B0]
0x66a81ee  mov rax,[rcx]
0x66a81f1  mov rax,[rax+0x10]
0x66a81f5  mov dl,0x4A
0x66a81f7  call qword ptr [0xF99FFA0]
0x66a81fd  nop

## Phase 5: 0x66a81fe..0x66a821a — Cursor advance: edx = eax (call result); if write cursor [rsi+0x1E8] < end [rsi+0x1F0], increment it, store [rsi+0x1E8], jump to 0x66A838E; otherwise fall into the buffer grow path at 0x66A821F.
0x66a81fe  mov edx,eax
0x66a8200  mov rbx,[rsi+0x1E8]
0x66a8207  cmp rbx,[rsi+0x1F0]
0x66a820e  je short 0x66A821F
0x66a8210  inc rbx
0x66a8213  mov [rsi+0x1E8],rbx
0x66a821a  jmp 0x66A838E

## Phase 6: 0x66a821f..0x66a8266 — Grow-size computation: r13 = used = cursor [rsi+0x1E8] - base [rsi+0x1E0]; rax = i64::MAX (0x7FFFFFFFFFFFFFFF); if used == rax jump to 0x66A8818; r12 = used+1; rdi = used + (used>>1) with an xor mask against i64::MAX, clamped below to r12 and above to i64::MAX; if the result is 0 jump to 0x66A82DD.
0x66a821f  mov r13,rbx
0x66a8222  sub r13,[rsi+0x1E0]
0x66a8229  mov rax,0x7FFFFFFFFFFFFFFF
0x66a8233  cmp r13,rax
0x66a8236  mov [rbp+0x580],dl
0x66a823c  je 0x66A8818
0x66a8242  lea r12,[r13+1]
0x66a8246  mov rdi,r13
0x66a8249  shr rdi,1
0x66a824c  mov rcx,rdi
0x66a824f  xor rcx,rax
0x66a8252  add rdi,r13
0x66a8255  cmp rdi,r12
0x66a8258  cmovbe rdi,r12
0x66a825c  cmp r13,rcx
0x66a825f  cmova rdi,rax
0x66a8263  test rdi,rdi
0x66a8266  je short 0x66A82DD

## Phase 7: 0x66a8268..0x66a82b2 — Allocate: if rdi < 0x1000 jump to 0x66A82B4; if rdi >= 0xFFFFFFFFFFFFFFD9 jump to 0x66A88C0; r15 = rdi+0x27; call *qword ptr [0xF99FFA0] via rcx = *[0x1233E1A8] chain with rdx = r15; if NULL jump to 0x66A861F; r14 = rax aligned up by 0x27 then & ~0x1F; store original size rax at [r14-8]; jump to 0x66A82E0.
0x66a8268  cmp rdi,0x1000
0x66a826f  jb short 0x66A82B4
0x66a8271  cmp rdi,0xFFFFFFFFFFFFFFD9
0x66a8275  jae 0x66A88C0
0x66a827b  lea r15,[rdi+0x27]
0x66a827f  mov rcx,[0x1233E1A8]
0x66a8286  mov rax,[rcx]
0x66a8289  mov rax,[rax+8]
0x66a828d  mov rdx,r15
0x66a8290  call qword ptr [0xF99FFA0]
0x66a8296  nop
0x66a8297  mov r14,rax
0x66a829a  test rax,rax
0x66a829d  je 0x66A861F
0x66a82a3  mov rax,r14
0x66a82a6  add r14,0x27
0x66a82aa  and r14,0xFFFFFFFFFFFFFFE0
0x66a82ae  mov [r14-8],rax
0x66a82b2  jmp short 0x66A82E0

## Phase 8: 0x66a82b4..0x66a82dd — Small allocation (< 0x1000): same allocator chain at *[0x1233E1A8] -> [rax+8] with rdx = rdi; r14 = rax; if rax != 0 jump to 0x66A82E0; else call 0x9BC830 (out of memory) and set r14 = 0.
0x66a82b4  mov rcx,[0x1233E1A8]
0x66a82bb  mov rax,[rcx]
0x66a82be  mov rax,[rax+8]
0x66a82c2  mov rdx,rdi
0x66a82c5  call qword ptr [0xF99FFA0]
0x66a82cb  nop
0x66a82cc  mov r14,rax
0x66a82cf  test rax,rax
0x66a82d2  jne short 0x66A82E0
0x66a82d4  mov rcx,rdi
0x66a82d7  call 0x9BC830
0x66a82dc  nop
0x66a82dd  xor r14d,r14d

## Phase 9: 0x66a82e0..0x66a8324 — Relocate existing data into the new buffer r14: if old cursor rbx == current cursor [rsi+0x1E8] jump to 0x66A8317; else memmove(0xEEC6DE0, rcx = r14, rdx = base [rsi+0x1E0], r8 = old cursor - base) then memmove(rcx = r14+r13+1, rdx = old cursor, r8 = current cursor - old cursor); at 0x66A8317: rbx = old cursor - base [rsi+0x1E0], memmove(rcx = r14, rdx = base, r8 = rbx).
0x66a82e0  cmp rbx,[rsi+0x1E8]
0x66a82e7  je short 0x66A8317
0x66a82e9  lea r15,[r14+r13]
0x66a82ed  inc r15
0x66a82f0  mov rdx,[rsi+0x1E0]
0x66a82f7  mov r8,rbx
0x66a82fa  sub r8,rdx
0x66a82fd  mov rcx,r14
0x66a8300  call 0xEEC6DE0
0x66a8305  mov r8,[rsi+0x1E8]
0x66a830c  sub r8,rbx
0x66a830f  mov rcx,r15
0x66a8312  mov rdx,rbx
0x66a8315  jmp short 0x66A8327
0x66a8317  mov rdx,[rsi+0x1E0]
0x66a831e  sub rbx,rdx
0x66a8321  mov rcx,r14
0x66a8324  mov r8,rbx
0x66a8327  call 0xEEC6DE0

## Phase 10: 0x66a832c..0x66a83a2 — Free old buffer: rcx = base [rsi+0x1E0]; if zero jump to 0x66A836C; rdx = end [rsi+0x1F0] - base; if < 0x1000 jump to 0x66A8367; rax = [rcx-8]; rcx = (rcx + 0xFFFFFFFFFFFFFFF8) - rax; if >= 0x20 jump out of slice to 0x66A87F8; else rdx += 0x27, rcx = rax, call 0xE935700. At 0x66a836c: install [rsi+0x1E0] = r14, [rsi+0x1E8] = r12 (= old cursor + used), [rsi+0x1F0] = rdi; reload [rbp+0x580] into edx.
0x66a832c  mov rcx,[rsi+0x1E0]
0x66a8333  test rcx,rcx
0x66a8336  je short 0x66A836C
0x66a8338  mov rdx,[rsi+0x1F0]
0x66a833f  sub rdx,rcx
0x66a8342  cmp rdx,0x1000
0x66a8349  jb short 0x66A8367
0x66a834b  mov rax,[rcx-8]
0x66a834f  add rcx,0xFFFFFFFFFFFFFFF8
0x66a8353  sub rcx,rax
0x66a8356  cmp rcx,0x20
0x66a835a  jae 0x66A87F8
0x66a8360  add rdx,0x27
0x66a8364  mov rcx,rax
0x66a8367  call 0xE935700
0x66a836c  mov [rsi+0x1E0],r14
0x66a8373  add r12,r14
0x66a8376  mov [rsi+0x1E8],r12
0x66a837d  add rdi,r14
0x66a8380  mov [rsi+0x1F0],rdi
0x66a8387  movzx edx,byte ptr [rbp+0x580]

## Phase 11: 0x66a838e..0x66a83da — The global-indirect call chain resumes (rcx = *[0x1233E1B0], rax = *rcx, rax = *(rax+0x10), dl = 0x4A, call *qword ptr [0xF99FFA0], nop), then store qword 0x100 at [rbp+0x288], compute word (~[rsi+0x1E0] + [rsi+0x1E8]) at [rbp+0x320], repeat the global-indirect call (rcx = *[0x1233E1B0] chain, dl = 0x4A), and store AL at [rbp+0x580].
0x66a838e  mov rcx,[0x1233E1B0]
0x66a8395  mov rax,[rcx]
0x66a8398  mov rax,[rax+0x10]
0x66a839c  call qword ptr [0xF99FFA0]
0x66a83a2  nop
0x66a83a3  mov qword ptr [rbp+0x288],0x100
0x66a83ae  mov eax,[rsi+0x1E0]
0x66a83b4  not eax
0x66a83b6  add eax,[rsi+0x1E8]
0x66a83bc  mov [rbp+0x320],ax
0x66a83c3  mov rcx,[0x1233E1B0]
0x66a83ca  mov rax,[rcx]
0x66a83cd  mov rax,[rax+0x10]
0x66a83d1  mov dl,0x4A
0x66a83d3  call qword ptr [0xF99FFA0]
0x66a83d9  nop
0x66a83da  mov [rbp+0x580],al

## Phase 12: 0x66a83e0..0x66a841c — If [rsi+8] != [rsi+0x10] (else call 0x5ABA6D0 with rcx=rsi, rdx=[rsi+8], r8=[rbp+0x280]): memcpy(0xEEC6EC0, rcx = [rsi+8], rdx = &[rbp+0x280], r8d = 0xC8) copies 0xC8 bytes from [rsi+8] to [rbp+0x280], then add 0xC8 to [rsi+8] and jump to 0x66A841C.
0x66a83e0  mov rax,[rsi+8]
0x66a83e4  cmp rax,[rsi+0x10]
0x66a83e8  je short 0x66A8409
0x66a83ea  lea rdx,[rbp+0x280]
0x66a83f1  mov r8d,0xC8
0x66a83f7  mov rcx,rax
0x66a83fa  call 0xEEC6EC0
0x66a83ff  add qword ptr [rsi+8],0xC8
0x66a8407  jmp short 0x66A841C
0x66a8409  lea r8,[rbp+0x280]
0x66a8410  mov rcx,rsi
0x66a8413  mov rdx,rax
0x66a8416  call 0x5ABA6D0
0x66a841b  nop

## Phase 13: 0x66a841c..0x66a8444 — Fifth global call through *qword ptr [0xF99FFA0] (dl = 0x4A); call 0x66A9C10 with rcx = &local [rbp+0x360]; if byte [rbp+0x538] != 3 jump to 0x66A8484.
0x66a841c  mov rcx,[0x1233E1B0]
0x66a8423  mov rax,[rcx]
0x66a8426  mov rax,[rax+0x10]
0x66a842a  movzx edx,byte ptr [rbp+0x580]
0x66a8431  call qword ptr [0xF99FFA0]
0x66a8437  nop
0x66a8438  lea rcx,[rbp+0x360]
0x66a843f  call 0x66A9C10
0x66a8444  cmp byte ptr [rbp+0x538],3
0x66a844b  jne short 0x66A8484

## Phase 14: 0x66a844d..0x66a847e — Release refcounted object rsi = [rbp+0x530] (skip if NULL): lock dec dword [rsi+8]; if != 0 jump 0x66A8484; rax = [rsi]; rax = [rax]; call *qword ptr [0xF99FFA0] (dtor); lock dec dword [rsi+0xC]; if != 0 jump 0x66A8484; rax = [rsi]; rax = [rax+8]; call *qword ptr [0xF99FFA0] (dealloc).
0x66a844d  mov rsi,[rbp+0x530]
0x66a8454  test rsi,rsi
0x66a8457  je short 0x66A8484
0x66a8459  lock dec dword ptr [rsi+8]
0x66a845d  jne short 0x66A8484
0x66a845f  mov rax,[rsi]
0x66a8462  mov rax,[rax]
0x66a8465  mov rcx,rsi
0x66a8468  call qword ptr [0xF99FFA0]
0x66a846e  lock dec dword ptr [rsi+0xC]
0x66a8472  jne short 0x66A8484
0x66a8474  mov rax,[rsi]
0x66a8477  mov rax,[rax+8]
0x66a847b  mov rcx,rsi
0x66a847e  call qword ptr [0xF99FFA0]

## Phase 15: 0x66a8484..0x66a84e3 — Walk element array [rbp+0x508) .. [rbp+0x510) step 0x28 (rdi walks to rbx = [rbp+0x510]); for each element with byte [rdi+0x18] == 2, release the object at [rdi+8] with the same lock-dec / dtor [rax] / lock-dec [rsi+0xC] / dealloc [rax+8] sequence; advance rdi += 0x28 until rdi == rbx.
0x66a8484  mov rdi,[rbp+0x508]
0x66a848b  test rdi,rdi
0x66a848e  je short 0x66A84E5
0x66a8490  mov rbx,[rbp+0x510]
0x66a8497  jmp short 0x66A84A4
0x66a8499  nop [rax]
0x66a84a0  add rdi,0x28
0x66a84a4  cmp rdi,rbx
0x66a84a7  je short 0x66A84E5
0x66a84a9  cmp byte ptr [rdi+0x18],2
0x66a84ad  jne short 0x66A84A0
0x66a84af  mov rsi,[rdi+8]
0x66a84b3  test rsi,rsi
0x66a84b6  je short 0x66A84A0
0x66a84b8  lock dec dword ptr [rsi+8]
0x66a84bc  jne short 0x66A84A0
0x66a84be  mov rax,[rsi]
0x66a84c1  mov rax,[rax]
0x66a84c4  mov rcx,rsi
0x66a84c7  call qword ptr [0xF99FFA0]
0x66a84cd  lock dec dword ptr [rsi+0xC]
0x66a84d1  jne short 0x66A84A0
0x66a84d3  mov rax,[rsi]
0x66a84d6  mov rax,[rax+8]
0x66a84da  mov rcx,rsi
0x66a84dd  call qword ptr [0xF99FFA0]
0x66a84e3  jmp short 0x66A84A0

## Phase 16: 0x66a84e5..0x66a8515 — Tail (slice ends at 0x66a8515): if byte [rbp+0x240] == 1 and rcx = [rbp+0x200] is non-zero (else jump 0x66A852E): rdx = [rbp+0x210] - rcx; if rdx < 0x1000 jump to 0x66A8529; rax = [rcx-8]; rcx = rcx + 0xFFFFFFFFFFFFFFF8; rcx = rcx - rax (allocation total size from its header at [rcx-8]).
0x66a84e5  cmp byte ptr [rbp+0x240],1
0x66a84ec  jne short 0x66A852E
0x66a84ee  mov rcx,[rbp+0x200]
0x66a84f5  test rcx,rcx
0x66a84f8  je short 0x66A852E
0x66a84fa  mov rdx,[rbp+0x210]
0x66a8501  sub rdx,rcx
0x66a8504  cmp rdx,0x1000
0x66a850b  jb short 0x66A8529
0x66a850d  mov rax,[rcx-8]
0x66a8511  add rcx,0xFFFFFFFFFFFFFFF8
0x66a8515  sub rcx,rax

## Field map — every [reg+off] load/store in the slice, one row per distinct offset, all sites listed.
Offset is the displacement as written in the instruction ("0" = bare [reg], "-8" = [reg-8]). Size is the access size of the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). Direction R/W (R/W = read-modify-write). Meaning is "-" unless an instruction or string in the slice shows it.

| offset | size | read/store address (sites) | verbatim instruction lines | meaning |
| 0x2BE | 2 | W [rbp+0x2BE] (0x66a80db) | 0x66a80db  mov [rbp+0x2BE],ax | - |
| 0 | 16/8 | R [rcx] (0x66a80e9, 0x66a81a9, 0x66a8286, 0x66a82bb); R [rsi] (0x66a845f, 0x66a8474, 0x66a84be); R [rax] (0x66a8462, 0x66a84c1); W [rdx] (0x66a811f) | 0x66a80e9  mov rax,[rcx] ; 0x66a811c  movups xmm0,[rcx] ; 0x66a811f  movups [rdx],xmm0 ; 0x66a81a9  mov rax,[rcx] ; 0x66a8286  mov rax,[rcx] ; 0x66a82bb  mov rax,[rcx] ; 0x66a845f  mov rax,[rsi] ; 0x66a8462  mov rax,[rax] ; 0x66a8474  mov rax,[rsi] ; 0x66a84be  mov rax,[rsi] ; 0x66a84c1  mov rax,[rax] | - |
| 0x10 | 8/4 | R [rax+0x10] (0x66a80ec, 0x66a81ac, 0x66a8426); R [rcx+0x10] (0x66a8116); W [rdx+0x10] (0x66a8119); R [rsi+0x10] (0x66a83e4) | 0x66a80ec  mov rax,[rax+0x10] ; 0x66a8116  mov eax,[rcx+0x10] ; 0x66a8119  mov [rdx+0x10],eax ; 0x66a81ac  mov rax,[rax+0x10] ; 0x66a83e4  cmp rax,[rsi+0x10] ; 0x66a8426  mov rax,[rax+0x10] | - |
| 0x580 | 1 | W [rbp+0x580] (0x66a80f9, 0x66a8236, 0x66a83da); R [rbp+0x580] (0x66a81b0, 0x66a8387, 0x66a842a) | 0x66a80f9  mov [rbp+0x580],al ; 0x66a81b0  movzx edx,byte ptr [rbp+0x580] ; 0x66a8236  mov [rbp+0x580],dl ; 0x66a8387  movzx edx,byte ptr [rbp+0x580] ; 0x66a83da  mov [rbp+0x580],al ; 0x66a842a  movzx edx,byte ptr [rbp+0x580] | - |
| 0x758 | 8/4 | R [rsi+0x758] (0x66a80ff, 0x66a81c9); R/W [rsi+0x758] (0x66a8181) | 0x66a80ff  mov rdx,[rsi+0x758] ; 0x66a8181  add qword ptr [rsi+0x758],0x58 ; 0x66a81c9  mov eax,[rsi+0x758] | - |
| 0x760 | 8 | R [rsi+0x760] (0x66a8106) | 0x66a8106  cmp rdx,[rsi+0x760] | - |
| 0x378 | 1 | R [rbp+0x378] (0x66a8122) | 0x66a8122  movzx eax,byte ptr [rbp+0x378] | - |
| 0x14 | 1 | W [rdx+0x14] (0x66a8129) | 0x66a8129  mov [rdx+0x14],al | - |
| 0x37C | 4 | R [rbp+0x37C] (0x66a812c) | 0x66a812c  movss xmm0,[rbp+0x37C] | - |
| 0x18 | 4/1 | W [rdx+0x18] (0x66a8134); R [rdi+0x18] (0x66a84a9) | 0x66a8134  movss [rdx+0x18],xmm0 ; 0x66a84a9  cmp byte ptr [rdi+0x18],2 | - |
| 0x380 | 4 | R [rbp+0x380] (0x66a8139) | 0x66a8139  movss xmm0,[rbp+0x380] | - |
| 0x1C | 4 | W [rdx+0x1C] (0x66a8141) | 0x66a8141  movss [rdx+0x1C],xmm0 | - |
| 0x384 | 4 | R [rbp+0x384] (0x66a8146) | 0x66a8146  movss xmm0,[rbp+0x384] | - |
| 0x20 | 4 | W [rdx+0x20] (0x66a814e) | 0x66a814e  movss [rdx+0x20],xmm0 | - |
| 0x388 | 4 | R [rbp+0x388] (0x66a8153) | 0x66a8153  movss xmm0,[rbp+0x388] | - |
| 0x24 | 4 | W [rdx+0x24] (0x66a815b) | 0x66a815b  movss [rdx+0x24],xmm0 | - |
| 0x38C | 16 | R [rbp+0x38C] (0x66a8160) | 0x66a8160  movups xmm0,[rbp+0x38C] | - |
| 0x39C | 16 | R [rbp+0x39C] (0x66a8167) | 0x66a8167  movups xmm1,[rbp+0x39C] | - |
| 0x3AB | 16 | R [rbp+0x3AB] (0x66a816e) | 0x66a816e  movups xmm2,[rbp+0x3AB] | - |
| 0x28 | 16 | W [rdx+0x28] (0x66a8175) | 0x66a8175  movups [rdx+0x28],xmm0 | - |
| 0x38 | 16 | W [rdx+0x38] (0x66a8179) | 0x66a8179  movups [rdx+0x38],xmm1 | - |
| 0x47 | 16 | W [rdx+0x47] (0x66a817d) | 0x66a817d  movups [rdx+0x47],xmm2 | - |
| 0x280 | 8 | W [rbp+0x280] (0x66a81be) | 0x66a81be  mov qword ptr [rbp+0x280],0x2807021 | - |
| 0x750 | 4 | R [rsi+0x750] (0x66a81cf) | 0x66a81cf  sub eax,[rsi+0x750] | - |
| 0x2AC | 2 | W [rbp+0x2AC] (0x66a81e0) | 0x66a81e0  mov [rbp+0x2AC],ax | - |
| 0x1E8 | 8/4 | R [rsi+0x1E8] (0x66a8200, 0x66a82e0, 0x66a8305); W [rsi+0x1E8] (0x66a8213, 0x66a8376); R [rsi+0x1E8] dword (0x66a83b6) | 0x66a8200  mov rbx,[rsi+0x1E8] ; 0x66a8213  mov [rsi+0x1E8],rbx ; 0x66a82e0  cmp rbx,[rsi+0x1E8] ; 0x66a8305  mov r8,[rsi+0x1E8] ; 0x66a8376  mov [rsi+0x1E8],r12 ; 0x66a83b6  add eax,[rsi+0x1E8] | - |
| 0x1F0 | 8 | R [rsi+0x1F0] (0x66a8207, 0x66a8338); W [rsi+0x1F0] (0x66a8380) | 0x66a8207  cmp rbx,[rsi+0x1F0] ; 0x66a8338  mov rdx,[rsi+0x1F0] ; 0x66a8380  mov [rsi+0x1F0],rdi | - |
| 0x1E0 | 8/4 | R [rsi+0x1E0] (0x66a8222, 0x66a82f0, 0x66a8317, 0x66a832c); W [rsi+0x1E0] (0x66a836c); R [rsi+0x1E0] dword (0x66a83ae) | 0x66a8222  sub r13,[rsi+0x1E0] ; 0x66a82f0  mov rdx,[rsi+0x1E0] ; 0x66a8317  mov rdx,[rsi+0x1E0] ; 0x66a832c  mov rcx,[rsi+0x1E0] ; 0x66a836c  mov [rsi+0x1E0],r14 ; 0x66a83ae  mov eax,[rsi+0x1E0] | - |
| -8 | 8 | W [r14-8] (0x66a82ae); R [rcx-8] (0x66a834b, 0x66a850d) | 0x66a82ae  mov [r14-8],rax ; 0x66a834b  mov rax,[rcx-8] ; 0x66a850d  mov rax,[rcx-8] | - |
| 8 | 8/4 | R [rax+8] (0x66a8289, 0x66a82be, 0x66a8477, 0x66a84d6); R [rsi+8] (0x66a83e0); R/W [rsi+8] (0x66a83ff); W [rsi+8] dword lock (0x66a8459, 0x66a84b8); R [rdi+8] (0x66a84af) | 0x66a8289  mov rax,[rax+8] ; 0x66a82be  mov rax,[rax+8] ; 0x66a83e0  mov rax,[rsi+8] ; 0x66a83ff  add qword ptr [rsi+8],0xC8 ; 0x66a8459  lock dec dword ptr [rsi+8] ; 0x66a8477  mov rax,[rax+8] ; 0x66a84af  mov rsi,[rdi+8] ; 0x66a84b8  lock dec dword ptr [rsi+8] ; 0x66a84d6  mov rax,[rax+8] | - |
| 0x288 | 8 | W [rbp+0x288] (0x66a83a3) | 0x66a83a3  mov qword ptr [rbp+0x288],0x100 | - |
| 0x320 | 2 | W [rbp+0x320] (0x66a83bc) | 0x66a83bc  mov [rbp+0x320],ax | - |
| 0x538 | 1 | R [rbp+0x538] (0x66a8444) | 0x66a8444  cmp byte ptr [rbp+0x538],3 | - |
| 0x530 | 8 | R [rbp+0x530] (0x66a844d) | 0x66a844d  mov rsi,[rbp+0x530] | - |
| 0xC | 4 | W [rsi+0xC] (0x66a846e, 0x66a84cd) | 0x66a846e  lock dec dword ptr [rsi+0xC] ; 0x66a84cd  lock dec dword ptr [rsi+0xC] | - |
| 0x508 | 8 | R [rbp+0x508] (0x66a8484) | 0x66a8484  mov rdi,[rbp+0x508] | - |
| 0x510 | 8 | R [rbp+0x510] (0x66a8490) | 0x66a8490  mov rbx,[rbp+0x510] | - |
| 0x240 | 1 | R [rbp+0x240] (0x66a84e5) | 0x66a84e5  cmp byte ptr [rbp+0x240],1 | - |
| 0x200 | 8 | R [rbp+0x200] (0x66a84ee) | 0x66a84ee  mov rcx,[rbp+0x200] | - |
| 0x210 | 8 | R [rbp+0x210] (0x66a84fa) | 0x66a84fa  mov rdx,[rbp+0x210] | - |

## TOOL REQUESTS
cmp_sa6.py (throwaway, kept in %TEMP%, not added to the repo) | compared the 250 precomputed input lines of docs/progress/_part_Sa6.txt against an rdis dis of the exe | confirmed 0/250 mismatches so verbatim quoting in this file is safe; no further tooling needed
