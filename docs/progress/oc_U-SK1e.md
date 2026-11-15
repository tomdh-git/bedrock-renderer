# Unit U-SK1e — small gap fixes for the sky Stars decoder

## NEXT
Unit complete. Part 1 (0x665bc90..0x665bd31) and Part 2 (0x665c240..0x665c2d0) are disassembled below with real instruction lines and interpretations; gap 0x665c251..0x665c276 covered. No resume needed.

## Source
`tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x665bc70 64` and `dis 0x665c240 56` [V]. Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01); RVAs are image-relative [V].

## Part 1: 0x665bc90..0x665bd31
Stream validated from real boundary 0x665bc70 (function sub_665bc70 header, rdis) and reaches 0x665bd31 exactly on a boundary: the 1-byte nop at 0x665bd30 ends at 0x665bd31 [V]. 0x665bc90 itself is NOT a boundary — it lies inside `mov rax,[rax+0x10]` at 0x665bc8d (ends 0x665bc91) [V]; the first real line at/after 0x665bc90 is therefore at 0x665bc91 [V].

0x665bc91  mov dl,0x4A
// loads 0x4A into dl ahead of the indirect call [V]
0x665bc93  call qword ptr [0xF99FFA0]
// indirect call through IAT slot data_f99ffa0 (rdis resolves to sub_eea6040) [V]
0x665bc99  mov [rbp+0x540],al
// stores low byte of call result to local [V]
0x665bc9f  lea rdx,[rbp+0x438]
// rdx = address of local at rbp+0x438 [V]
0x665bca6  lea rcx,[rsi+0x648]
// rcx = rsi + 0x648 (address arithmetic; meaning of rsi not determined here) [I]
0x665bcad  call 0x675FB30
// direct call to sub_675fb30 [V]
0x665bcb2  nop
// one-byte pad [I]
0x665bcb3  mov rcx,[0x1233E1B0]
// loads global pointer data_1233e1b0 [V]
0x665bcba  mov rax,[rcx]
// dereferences the global pointer [V]
0x665bcbd  mov rax,[rax+0x10]
// loads qword field at offset 0x10 [V]
0x665bcc1  movzx edx,byte ptr [rbp+0x540]
// zero-extends the byte stored at 0x665bc99 [V]
0x665bcc8  call qword ptr [0xF99FFA0]
// second indirect call via data_f99ffa0 [V]
0x665bcce  nop
// one-byte pad [I]
0x665bccf  mov eax,[rsi+0x650]
// reads dword field at rsi+0x650 [V]
0x665bcd5  sub eax,[rsi+0x648]
// byte/4 difference between fields 0x650 and 0x648 [V; meaning of difference [I]]
0x665bcdb  shr eax,3
// divides by 8 (element count from byte difference) [I]
0x665bcde  imul eax,0xFFFF8E39
// multiplies by constant 0xFFFF8E39; meaning not determined [I]
0x665bce4  dec eax
// decrements [V]
0x665bce6  mov [rbp+0x222],ax
// stores result word to local [V]
0x665bced  mov rcx,[0x1233E1B0]
// reloads global pointer [V]
0x665bcf4  mov rax,[rcx]
// dereferences [V]
0x665bcf7  mov rax,[rax+0x10]
// loads qword field at offset 0x10 [V]
0x665bcfb  mov dl,0x4A
// loads 0x4A again [V]
0x665bcfd  call qword ptr [0xF99FFA0]
// third indirect call via data_f99ffa0 [V]
0x665bd03  nop
// one-byte pad [I]
0x665bd04  mov [rbp+0x540],al
// stores byte [V]
0x665bd0a  mov rbx,[rsi+0x770]
// reads qword field at rsi+0x770 (cursor-like pointer; meaning not determined) [V; meaning [I]]
0x665bd11  cmp rbx,[rsi+0x778]
// compares with qword field at rsi+0x778 (end-like pointer; meaning not determined) [V; meaning [I]]
0x665bd18  je short 0x665BD57
// branches to loc_665bd57 if equal [V]
0x665bd1a  mov rax,[rbp+0x3B0]
// reads local [V]
0x665bd21  mov [rbx],rax
// writes qword at cursor [V]
0x665bd24  lea rcx,[rbx+8]
// rcx = rbx + 8 (likely object init target; not determined) [V; meaning [I]]
0x665bd28  mov rdx,rdi
// passes rdi as second argument [V]
0x665bd2b  call 0xE869FF0
// direct call to sub_e869ff0 [V]
0x665bd30  nop
// one-byte pad; ends exactly at range end 0x665bd31 [V]

End boundary check: last line ends at 0x665bd31 = range end [V].

## Part 2: 0x665c240..0x665c2d0
0x665c240 is the real function start (sub_665c240 header per rdis) [V]. Gap 0x665c251..0x665c276 (oc_U-SK1b ended at 0x665c251; oc_U-SK1c resumes at 0x665c276) is covered by real lines 0x665c251..0x665c26f, ending exactly at 0x665c276 [V]. Range end 0x665c2d0 falls INSIDE `mov rax,[rax]` at 0x665c2ce (its last byte); that instruction's start is inside the range so it is listed, with the overrun noted [V].

0x665c240  or rdx,0x27
// sets flag bits 0x27 in rdx [V]
0x665c244  mov rcx,rax
// rcx = rax [V]
0x665c247  call 0xE935700
// direct call to sub_e935700 [V]
0x665c24c  jmp 0x665CF64
// unconditional jump to loc_665cf64 [V]
0x665c251  xor r11d,r11d
// zeroes r11d; gap start (oc_U-SK1b ended here) [V]
0x665c254  mov rdi,[rbp+0x208]
// reads qword local at rbp+0x208 [V]
0x665c25b  mov [rbp+0x4A0],rdi
// stores it to local at rbp+0x4A0 [V]
0x665c262  mov [rbp+0x4A8],r11
// zeroes local at rbp+0x4A8 [V]
0x665c269  mov [rbp+0x4B0],cl
// stores cl to local at rbp+0x4B0 [V]
0x665c26f  mov rcx,[rbp+0x230]
// reads qword local at rbp+0x230; instruction ends at 0x665c276 (oc_U-SK1c resume point) [V]
0x665c276  mov [rbp+0x4C8],rcx
// stores it to local at rbp+0x4C8; gap 0x665c251..0x665c276 fully covered with real lines [V]
0x665c27d  movaps xmm0,[rbp+0x220]
// loads 16 bytes from local at rbp+0x220 [V]
0x665c284  movups [rbp+0x4B8],xmm0
// stores 16 bytes to local at rbp+0x4B8 [V]
0x665c28b  mov ecx,0x9D0
// ecx = 0x9D0 [V]
0x665c290  add rcx,[rsi+0x10]
// rcx += qword field at rsi+0x10 [V]
0x665c294  mov [rsp+0x28],rax
// spills rax to stack [V]
0x665c299  mov [rsp+0x20],r10
// spills r10 to stack [V]
0x665c29e  call 0x67B40D0
// direct call to sub_67b40d0 [V]
0x665c2a3  nop
// one-byte pad [I]
0x665c2a4  lea rcx,[rbp+0x340]
// rcx = address of local at rbp+0x340 [V]
0x665c2ab  call 0x66A9AD0
// direct call to sub_66a9ad0 [V]
0x665c2b0  cmp byte ptr [rbp+0x218],3
// compares byte local at rbp+0x218 with 3 [V]
0x665c2b7  jne short 0x665C2F0
// branches to loc_665c2f0 if not equal [V]
0x665c2b9  mov rsi,[rbp+0x210]
// reads qword local pointer at rbp+0x210 [V]
0x665c2c0  test rsi,rsi
// null test on rsi [V]
0x665c2c3  je short 0x665C2F0
// branches to loc_665c2f0 if null [V]
0x665c2c5  lock dec dword ptr [rsi+8]
// decrements dword at rsi+8 with lock (release/refcount-like; meaning not determined) [V; meaning [I]]
0x665c2c9  jne short 0x665C2F0
// branches to loc_665c2f0 if result nonzero [V]
0x665c2cb  mov rax,[rsi]
// loads qword at rsi (likely vtable pointer; not determined) [V; meaning [I]]
0x665c2ce  mov rax,[rax]
// loads vtable[0] (likely destructor entry; not determined); starts inside range, bytes run to 0x665c2d1, one byte past range end 0x665c2d0 [V; meaning [I]]
