## NEXT
line 741 (remaining lines 741-1400 not yet processed; unit complete for lines 701-740)

## lines 701..740
```
0x66eb1d3  cmp [r10+0x28],r8
0x66eb1d7  je short 0x66EB1E5
0x66eb1d9  add rcx,0x30
0x66eb1dd  add r9,0xFFFFFFFFFFFFFFD0
0x66eb1e1  jne short 0x66EB1D0
0x66eb1e3  jmp short 0x66EB24B
0x66eb1e5  add rdx,rax
0x66eb1e8  cmp rcx,rdx
0x66eb1eb  jae short 0x66EB24B
0x66eb1ed  sub ecx,eax
0x66eb1ef  shr ecx,4
0x66eb1f2  imul eax,ecx,0xFFFFAAAB
0x66eb1f8  mov [rbp+0xC78],ax
0x66eb1ff  mov byte ptr [rbp+0xC7A],1
0x66eb206  mov [rbp+0x1440],si
0x66eb20d  mov dword ptr [rbp+0x1444],0
0x66eb217  mov byte ptr [rbp+0x1448],1
0x66eb21e  mov byte ptr [rbp+0x144C],1
0x66eb225  mov dword ptr [rsp+0x20],0
0x66eb22d  lea rcx,[rbp+0xEE8]
0x66eb234  lea rdx,[rbp+0xC78]
0x66eb23b  lea r9,[rbp+0x1440]
0x66eb242  mov r8,r15
0x66eb245  call 0xBCABA00
0x66eb24a  nop
0x66eb24b  test r14,r14
0x66eb24e  je short 0x66EB27D
0x66eb250  lock dec dword ptr [r14+8]
0x66eb255  jne short 0x66EB27D
0x66eb257  mov rax,[r14]
0x66eb25a  mov rax,[rax]
0x66eb25d  mov rcx,r14
0x66eb260  call qword ptr [0xF99FFA0]
0x66eb266  lock dec dword ptr [r14+0xC]
0x66eb26b  jne short 0x66EB27D
0x66eb26d  mov rax,[r14]
0x66eb270  mov rax,[rax+8]
0x66eb274  mov rcx,r14
0x66eb277  call qword ptr [0xF99FFA0]
0x66eb27d  mov r14,[rbp+0xF78]
```
Search loop over table entries at [r10+0x28] vs r8, stride 0x30, sentinel 0xFFFFFFD0; on match computes (rcx-rdx)/16 scaled by magic 0xFFFFAAAB, stores word at [rbp+0xC78] valid byte at [rbp+0xC7A] [V]. Fills struct [rbp+0x1440..0x144C] (si, 0, 1, 1) and calls 0xBCABA00(&EE8, &C78, &1440, r15) [V]. Then refcount-releases r14 via [r14+8] and [r14+0xC], calling qword ptr [0xF99FFA0] on each zero transition [V].

## lines 741..780
```
0x66eb284  test r14,r14
0x66eb287  mov r15d,[rbp+0x1698]
0x66eb28e  je 0x66EB581
0x66eb294  lock dec dword ptr [r14+8]
0x66eb299  jne 0x66EB581
0x66eb29f  mov rax,[r14]
0x66eb2a2  mov rax,[rax]
0x66eb2a5  mov rcx,r14
0x66eb2a8  call qword ptr [0xF99FFA0]
0x66eb2ae  lock dec dword ptr [r14+0xC]
0x66eb2b3  jne 0x66EB581
0x66eb2b9  mov rax,[r14]
0x66eb2bc  mov rax,[rax+8]
0x66eb2c0  mov rcx,r14
0x66eb2c3  call qword ptr [0xF99FFA0]
0x66eb2c9  jmp 0x66EB581
0x66eb2ce  add r8,rcx
0x66eb2d1  cmp rdx,r8
0x66eb2d4  jae short 0x66EB334
0x66eb2d6  sub edx,ecx
0x66eb2d8  shr edx,4
0x66eb2db  imul ecx,edx,0xFFFFAAAB
0x66eb2e1  mov [rbp+0xF70],cx
0x66eb2e8  mov byte ptr [rbp+0xF72],1
0x66eb2ef  mov [rbp+0x1440],ax
0x66eb2f6  mov dword ptr [rbp+0x1444],0
0x66eb300  mov byte ptr [rbp+0x1448],1
0x66eb307  mov byte ptr [rbp+0x144C],1
0x66eb30e  mov dword ptr [rsp+0x20],0
0x66eb316  lea rcx,[rbp+0xEE8]
0x66eb31d  lea rdx,[rbp+0xF70]
0x66eb324  lea r9,[rbp+0x1440]
0x66eb32b  mov r8,rbx
0x66eb32e  call 0xBCABA00
0x66eb333  nop
0x66eb334  mov eax,[0x129F9A68]
0x66eb33a  mov ecx,[0x128767C8]
0x66eb340  mov rdx,gs:[0x58]
0x66eb349  mov rcx,[rdx+rcx*8]
0x66eb34d  cmp eax,[rcx+4]
```
Refcount-release r14 if non-null: dec [r14+8] then destructor qword ptr [0xF99FFA0], dec [r14+0xC] then destructor again, jump to 0x66EB581 [V]. Second search loop: r8+=rcx, bounds rdx vs r8, computes (rdx-rcx)/16*0xFFFFAAAB -> word [rbp+0xF70], valid flag [rbp+0xF72], fills struct [rbp+0x1440]={ax,0,1,1}, calls 0xBCABA00(&EE8,&F70,&1440,rbx) [V]. Then TLS static guard: eax=[0x129F9A68] cmp [rcx+4] [V].

## lines 781..820
```
0x66eb353  jg 0x66F893B
0x66eb359  movzx eax,word ptr [0x128C1A5C]
0x66eb360  mov rcx,[rbp+0xF30]
0x66eb367  movzx r9d,word ptr [rbp+0xF3A]
0x66eb36f  mov edx,r9d
0x66eb372  shl edx,4
0x66eb375  lea r8,[rdx+rdx*2]
0x66eb379  mov rdx,rcx
0x66eb37c  test r9,r9
0x66eb37f  je short 0x66EB3A5
0x66eb381  mov r9,[0x129F9A60]
0x66eb388  mov r10,r8
0x66eb38b  mov rdx,rcx
0x66eb38e  xchg ax,ax
0x66eb390  mov r11,[rdx]
0x66eb393  cmp [r11+0x28],r9
0x66eb397  je short 0x66EB3A5
0x66eb399  add rdx,0x30
0x66eb39d  add r10,0xFFFFFFFFFFFFFFD0
0x66eb3a1  jne short 0x66EB390
0x66eb3a3  jmp short 0x66EB40C
0x66eb3a5  add r8,rcx
0x66eb3a8  cmp rdx,r8
0x66eb3ab  jae short 0x66EB40C
0x66eb3ad  lea r8,[rbx+0x10]
0x66eb3b1  sub edx,ecx
0x66eb3b3  shr edx,4
0x66eb3b6  imul ecx,edx,0xFFFFAAAB
0x66eb3bc  mov [rbp+0xF70],cx
0x66eb3c3  mov byte ptr [rbp+0xF72],1
0x66eb3ca  mov [rbp+0x1440],ax
0x66eb3d1  mov dword ptr [rbp+0x1444],0
0x66eb3db  mov byte ptr [rbp+0x1448],0
0x66eb3e2  mov byte ptr [rbp+0x144C],1
0x66eb3e9  mov dword ptr [rsp+0x20],0
0x66eb3f1  lea rcx,[rbp+0xEE8]
0x66eb3f8  lea rdx,[rbp+0xF70]
0x66eb3ff  lea r9,[rbp+0x1440]
0x66eb406  call 0xBCABA00
0x66eb40b  nop
```
TLS static guard cold path -> 0x66F893B [V]. Loads count word [0x128C1A5C] -> eax, base rcx=[rbp+0xF30], index word [rbp+0xF3A] -> r9d, stride = r9d*0x30 (shl 4 + lea r8,[rdx+rdx*2]) [V]. Linear search over entries stride 0x30 comparing [entry+0x28] vs r9=[0x129F9A60], sentinel 0xFFFFFFD0 [V]. On found: r8=rcx+r8; else bounds-check rdx vs r8 -> 0x66EB40C [V]. Computes (rdx-rcx)/16*0xFFFFAAAB -> [rbp+0xF70], valid flag [rbp+0xF72], fills struct [rbp+0x1440]={ax,0,0,1}, calls 0xBCABA00(&EE8,&F70,&1440,...) [V].

## lines 821..860
```
0x66eb40c  cmp qword ptr [rbx+0x30],3
0x66eb411  setae al
0x66eb414  test [rbp+0x1388],al
0x66eb41a  je short 0x66EB493
0x66eb41c  mov eax,[0x129F9A78]
0x66eb422  mov ecx,[0x128767C8]
0x66eb428  mov rdx,gs:[0x58]
0x66eb431  mov rcx,[rdx+rcx*8]
0x66eb435  cmp eax,[rcx+4]
0x66eb43b  jg 0x66F89EF
0x66eb441  movzx eax,word ptr [0x128C1A58]
0x66eb448  mov [rbp+0x1440],ax
0x66eb44f  mov dword ptr [rbp+0x1444],0
0x66eb459  mov byte ptr [rbp+0x1448],0
0x66eb460  lea r9,[rbx+0x20]
0x66eb464  lea rax,[rbp+0x1440]
0x66eb46b  mov [rsp+0x20],rax
0x66eb470  mov dword ptr [rsp+0x28],0
0x66eb478  lea r8,[0x129F9A70]
0x66eb47f  lea rcx,[rbp+0xEE8]
0x66eb486  lea rdx,[rbp+0xF70]
0x66eb48d  call 0xBCAB8F0
0x66eb492  nop
0x66eb493  cmp byte ptr [rbp+0x16D4],0
0x66eb49a  je 0x66EB581
0x66eb4a0  mov eax,[0x129F9A88]
0x66eb4a6  mov ecx,[0x128767C8]
0x66eb4ac  mov rdx,gs:[0x58]
0x66eb4b5  mov rcx,[rdx+rcx*8]
0x66eb4b9  cmp eax,[rcx+4]
0x66eb4bf  jg 0x66F8A61
0x66eb4c5  xorps xmm0,xmm0
0x66eb4c8  movaps [rbp+0x1440],xmm0
0x66eb4cf  mov rax,[r13+0x450]
0x66eb4d6  test rax,rax
0x66eb4d9  je short 0x66EB529
0x66eb4db  lock inc dword ptr [rax+8]
0x66eb4df  mov r14,[rbp+0x1448]
0x66eb4e6  movups xmm0,[r13+0x448]
0x66eb4ee  movaps [rbp+0x1440],xmm0
```
Checks [rbx+0x30]>=3 -> al, tests [rbp+0x1388]&al, skips if zero [V]. TLS static guard eax=[0x129F9A78] cmp [rcx+4], cold path 0x66F89EF [V]. Loads word [0x128C1A58] -> [rbp+0x1440] (ax), zeroes [rbp+0x1444] and flag [rbp+0x1448]=0, sets r9=[rbx+0x20], calls 0xBCAB8F0(&EE8,&F70,&1440,r8=0x129F9A70) [V]. If [rbp+0x16D4]!=0: TLS guard eax=[0x129F9A88], cold path 0x66F8A61 [V]. Zeroes xmm0 -> [rbp+0x1440]; loads rax=[r13+0x450], if non-null lock inc [rax+8]; r14=[rbp+0x1448]; movups [r13+0x448] -> [rbp+0x1440] [V].

## lines 861..900
```
0x66eb4f5  test r14,r14
0x66eb4f8  je short 0x66EB542
0x66eb4fa  lock dec dword ptr [r14+8]
0x66eb4ff  jne short 0x66EB542
0x66eb501  mov rax,[r14]
0x66eb504  mov rax,[rax]
0x66eb507  mov rcx,r14
0x66eb50a  call qword ptr [0xF99FFA0]
0x66eb510  lock dec dword ptr [r14+0xC]
0x66eb515  jne short 0x66EB542
0x66eb517  mov rax,[r14]
0x66eb51a  mov rax,[rax+8]
0x66eb51e  mov rcx,r14
0x66eb521  call qword ptr [0xF99FFA0]
0x66eb527  jmp short 0x66EB542
0x66eb529  mov rax,[r13+0x448]
0x66eb530  mov [rbp+0x1440],rax
0x66eb537  mov qword ptr [rbp+0x1448],0
0x66eb542  mov dword ptr [rsp+0x28],0
0x66eb54a  mov byte ptr [rsp+0x20],1
0x66eb54f  lea r8,[0x129F9A80]
0x66eb556  lea rcx,[rbp+0xEE8]
0x66eb55d  lea rdx,[rbp+0xF70]
0x66eb564  lea r9,[rbp+0x1440]
0x66eb56b  call 0xBCAC390
0x66eb570  nop
0x66eb571  mov r14,[rbp+0x1448]
0x66eb578  test r14,r14
0x66eb57b  jne 0x66EB294
0x66eb581  mov eax,[0x129F9A98]
0x66eb587  mov ecx,[0x128767C8]
0x66eb58d  mov rdx,gs:[0x58]
0x66eb596  mov rcx,[rdx+rcx*8]
0x66eb59a  cmp eax,[rcx+4]
0x66eb5a0  jg 0x66F82D4
0x66eb5a6  mov eax,[0x129F9AA8]
0x66eb5ac  mov ecx,[0x128767C8]
0x66eb5b2  mov rdx,gs:[0x58]
0x66eb5bb  mov rcx,[rdx+rcx*8]
0x66eb5bf  cmp eax,[rcx+4]
```
Refcount-release r14 if non-null: dec [r14+8], destructor qword ptr [0xF99FFA0], dec [r14+0xC], destructor again [V]. Else path [rbp+0x1440]=[r13+0x448], [rbp+0x1448]=0 [V]. Sets up call args: [rsp+0x28]=0, [rsp+0x20]=1, r8=0x129F9A80, calls 0xBCAC390(&EE8,&F70,&1440) [V]. r14=[rbp+0x1448]; if non-zero loop back to 0x66EB294 release [V]. Then TLS static guards eax=[0x129F9A98] and eax=[0x129F9AA8], each cmp [rcx+4], cold paths 0x66F82D4 / (next) [V].

## lines 901..940
```
0x66eb5c5  jg 0x66F8346
0x66eb5cb  mov eax,[0x129F9AB8]
0x66eb5d1  mov ecx,[0x128767C8]
0x66eb5d7  mov rdx,gs:[0x58]
0x66eb5e0  mov rcx,[rdx+rcx*8]
0x66eb5e4  cmp eax,[rcx+4]
0x66eb5ea  jg 0x66F83B8
0x66eb5f0  movzx eax,byte ptr [rbx+0xB8]
0x66eb5f7  test al,al
0x66eb5f9  jne short 0x66EB600
0x66eb5fb  xorps xmm0,xmm0
0x66eb5fe  jmp short 0x66EB608
0x66eb600  movss xmm0,[0xEEC8060]
0x66eb608  movss [rbp+0x1440],xmm0
0x66eb610  mov qword ptr [rbp+0x1444],0
0x66eb61b  mov dword ptr [rbp+0x144C],0
0x66eb625  mov qword ptr [rbp+0xF70],1
0x66eb630  lea rsi,[rbp+0x1440]
0x66eb637  mov [rbp+0xF78],rsi
0x66eb63e  mov rcx,[rbp+0xF20]
0x66eb645  movzx r9d,word ptr [rbp+0xF2A]
0x66eb64d  mov r8d,r9d
0x66eb650  shl r8d,4
0x66eb654  mov rdx,rcx
0x66eb657  test r9d,r9d
0x66eb65a  je short 0x66EB685
0x66eb65c  mov r9,[0x129F9AB0]
0x66eb663  mov r10,r8
0x66eb666  mov rdx,rcx
0x66eb669  nop [rax]
0x66eb670  mov r11,[rdx]
0x66eb673  cmp [r11+0x28],r9
0x66eb677  je short 0x66EB685
0x66eb679  add rdx,0x10
0x66eb67d  add r10,0xFFFFFFFFFFFFFFF0
0x66eb681  jne short 0x66EB670
0x66eb683  jmp short 0x66EB6C2
0x66eb685  add r8,rcx
0x66eb688  cmp rdx,r8
0x66eb68b  jae short 0x66EB6C2
```
TLS static guards eax=[0x129F9AB8] (cold 0x66F8346) and eax=[0x129F9AB8] (cold 0x66F83B8) cmp [rcx+4] [V]. If byte [rbx+0xB8]==0: xmm0=0 else movss xmm0,[0xEEC8060] -> [rbp+0x1440] [V]. Zeroes [rbp+0x1444], [rbp+0x144C]; [rbp+0xF70]=1; rsi=&[rbp+0x1440]; [rbp+0xF78]=rsi [V]. rcx=[rbp+0xF20], count word [rbp+0xF2A] -> r9d, stride r8d=r9d*0x10 [V]. Linear search entries stride 0x10 comparing [entry+0x28] vs r9=[0x129F9AB0], sentinel 0xFFFFFFF0 [V]. On found r8=rcx+r8 else bounds-check rdx vs r8 -> 0x66EB6C2 [V].

## lines 941..980
```
0x66eb68d  sub edx,ecx
0x66eb68f  shr edx,4
0x66eb692  mov [rbp+0x1130],dx
0x66eb699  mov byte ptr [rbp+0x1132],1
0x66eb6a0  lea rdx,[rbp+0x1130]
0x66eb6a7  lea r8,[rbp+0xF70]
0x66eb6ae  lea rcx,[rbp+0xEF0]
0x66eb6b5  call 0x5679DB0
0x66eb6ba  nop
0x66eb6bb  movzx eax,byte ptr [rbx+0xB8]
0x66eb6c2  movss xmm0,[rbx+0x74]
0x66eb6c7  test al,al
0x66eb6c9  je 0x66EB750
0x66eb6cf  mov qword ptr [rbp+0x1440],0
0x66eb6da  mov dword ptr [rbp+0x1448],0
0x66eb6e4  movss [rbp+0x144C],xmm0
0x66eb6ec  mov qword ptr [rbp+0xF70],1
0x66eb6f7  mov [rbp+0xF78],rsi
0x66eb6fe  mov rax,[rbp+0xF20]
0x66eb705  movzx edx,word ptr [rbp+0xF2A]
0x66eb70c  mov ecx,edx
0x66eb70e  shl ecx,4
0x66eb711  mov r8,rax
0x66eb714  test edx,edx
0x66eb716  je 0x66EB7E3
0x66eb71c  mov r9,[0x129F9A90]
0x66eb723  xor r8d,r8d
0x66eb726  nop [rax+rax]
0x66eb730  mov r10,[rax+r8]
0x66eb734  cmp [r10+0x28],r9
0x66eb738  je 0x66EB7E0
0x66eb73e  add r8,0x10
0x66eb742  cmp rcx,r8
0x66eb745  jne short 0x66EB730
0x66eb747  mov dx,1
0x66eb74b  jmp 0x66EB830
0x66eb750  movss xmm1,[rbx+0xEC]
0x66eb758  movsd xmm2,[rbx+0xE4]
0x66eb760  movsd [rbp+0x1440],xmm2
0x66eb768  movss [rbp+0x1448],xmm1
```
Computes (rdx-rcx)/16 -> dx, stores word [rbp+0x1130], valid flag [rbp+0x1132]=1, calls 0x5679DB0(&EF0,&F70,&1130) [V]. If byte [rbx+0xB8]==0: zeros [rbp+0x1440] qword and [rbp+0x1448] dword, movss [rbx+0x74] -> [rbp+0x144C], [rbp+0xF70]=1, [rbp+0xF78]=rsi [V]. Else path: movss [rbx+0xEC]->xmm1, movsd [rbx+0xE4]->xmm2, movsd xmm2->[rbp+0x1440], movss xmm1->[rbp+0x1448] [V]. Then rcx=[rbp+0xF20], count word [rbp+0xF2A]->edx, stride ecx=edx*0x10, r8=rax, search entries stride 0x10 [entry+0x28] vs r9=[0x129F9A90], sentinel, on not-found dx=1 jump 0x66EB830 [V].

## lines 981..1020
```
0x66eb770  movss [rbp+0x144C],xmm0
0x66eb778  mov qword ptr [rbp+0xF70],1
0x66eb783  mov [rbp+0xF78],rsi
0x66eb78a  mov rax,[rbp+0xF20]
0x66eb791  movzx edx,word ptr [rbp+0xF2A]
0x66eb798  mov ecx,edx
0x66eb79a  shl ecx,4
0x66eb79d  mov r8,rax
0x66eb7a0  test edx,edx
0x66eb7a2  je 0x66EB8CD
0x66eb7a8  mov r9,[0x129F9A90]
0x66eb7af  xor r8d,r8d
0x66eb7b2  nop [rax+rax]
0x66eb7c0  mov r10,[rax+r8]
0x66eb7c4  cmp [r10+0x28],r9
0x66eb7c8  je 0x66EB8CA
0x66eb7ce  add r8,0x10
0x66eb7d2  cmp rcx,r8
0x66eb7d5  jne short 0x66EB7C0
0x66eb7d7  mov dx,1
0x66eb7db  jmp 0x66EB91A
0x66eb7e0  add r8,rax
0x66eb7e3  lea r9,[rax+rcx]
0x66eb7e7  cmp r8,r9
0x66eb7ea  jae short 0x66EB830
0x66eb7ec  sub r8d,eax
0x66eb7ef  shr r8d,4
0x66eb7f3  mov [rbp+0x1130],r8w
0x66eb7fb  mov byte ptr [rbp+0x1132],1
0x66eb802  lea rdx,[rbp+0x1130]
0x66eb809  lea r8,[rbp+0xF70]
0x66eb810  lea rcx,[rbp+0xEF0]
0x66eb817  call 0x5679DB0
0x66eb81c  nop
0x66eb81d  mov rax,[rbp+0xF20]
0x66eb824  movzx edx,word ptr [rbp+0xF2A]
0x66eb82b  mov ecx,edx
0x66eb82d  shl ecx,4
0x66eb830  movaps xmm0,[0xF2BDE40]
0x66eb837  movaps [rbp+0x1440],xmm0
```
movss xmm0->[rbp+0x144C], [rbp+0xF70]=1, [rbp+0xF78]=rsi [V]. rcx=[rbp+0xF20], count word [rbp+0xF2A]->edx, stride ecx=edx*0x10, r8=rax; if edx==0 jump 0x66EB8CD [V]. Search entries stride 0x10 [entry+0x28] vs r9=[0x129F9A90]; on found add r8,rax; else if not found dx=1 jump 0x66EB91A [V]. On found: r8=rax+r8, end r9=rax+rcx; if r8>=r9 jump 0x66EB830 else compute (r8d-eax)/16 -> word [rbp+0x1130], valid flag=1, call 0x5679DB0(&EF0,&F70,&1130) [V]. Reload rax=[rbp+0xF20], count->edx, stride; movaps xmm0,[0xF2BDE40] -> [rbp+0x1440] [V].

## lines 1021..1060
```
0x66eb83e  mov qword ptr [rbp+0xF70],1
0x66eb849  mov [rbp+0xF78],rsi
0x66eb850  mov r8,rax
0x66eb853  test dx,dx
0x66eb856  je short 0x66EB888
0x66eb858  mov rdx,[0x129F9AA0]
0x66eb85f  mov r9,rcx
0x66eb862  mov r8,rax
0x66eb865  nop [rax+rax]
0x66eb870  mov r10,[r8]
0x66eb873  cmp [r10+0x28],rdx
0x66eb877  je short 0x66EB888
0x66eb879  add r8,0x10
0x66eb87d  add r9,0xFFFFFFFFFFFFFFF0
0x66eb881  jne short 0x66EB870
0x66eb883  jmp 0x66EB99E
0x66eb888  add rcx,rax
0x66eb88b  cmp r8,rcx
0x66eb88e  jae 0x66EB99E
0x66eb894  sub r8d,eax
0x66eb897  shr r8d,4
0x66eb89b  mov [rbp+0x1130],r8w
0x66eb8a3  mov byte ptr [rbp+0x1132],1
0x66eb8aa  lea rdx,[rbp+0x1130]
0x66eb8b1  lea r8,[rbp+0xF70]
0x66eb8b8  lea rcx,[rbp+0xEF0]
0x66eb8bf  call 0x5679DB0
0x66eb8c4  nop
0x66eb8c5  jmp 0x66EB99E
0x66eb8ca  add r8,rax
0x66eb8cd  lea r9,[rax+rcx]
0x66eb8d1  cmp r8,r9
0x66eb8d4  jae short 0x66EB91A
0x66eb8d6  sub r8d,eax
0x66eb8d9  shr r8d,4
0x66eb8dd  mov [rbp+0x1130],r8w
0x66eb8e5  mov byte ptr [rbp+0x1132],1
0x66eb8ec  lea rdx,[rbp+0x1130]
0x66eb8f3  lea r8,[rbp+0xF70]
0x66eb8fa  lea rcx,[rbp+0xEF0]
```
[rbp+0xF70]=1, [rbp+0xF78]=rsi, r8=rax; if dx==0 jump 0x66EB888 [V]. Search entries stride 0x10 [entry+0x28] vs rdx=[0x129F9AA0]; if found jump 0x66EB888 else if not found jump 0x66EB99E [V]. On path: rcx+=rax, bounds r8 vs rcx; if r8>=rcx jump 0x66EB99E else compute (r8d-eax)/16 -> word [rbp+0x1130], valid flag=1, call 0x5679DB0(&EF0,&F70,&1130), jump 0x66EB99E [V]. Alternate: r8+=rax, end r9=rax+rcx; if r8>=r9 jump 0x66EB91A else compute (r8d-eax)/16 -> word [rbp+0x1130], valid flag=1 [V].

## lines 1061..1100
```
0x66eb901  call 0x5679DB0
0x66eb906  nop
0x66eb907  mov rax,[rbp+0xF20]
0x66eb90e  movzx edx,word ptr [rbp+0xF2A]
0x66eb915  mov ecx,edx
0x66eb917  shl ecx,4
0x66eb91a  movups xmm0,[rbx+0x64]
0x66eb91e  movaps [rbp+0x1440],xmm0
0x66eb925  mov qword ptr [rbp+0xF70],1
0x66eb930  mov [rbp+0xF78],rsi
0x66eb937  mov r8,rax
0x66eb93a  test dx,dx
0x66eb93d  je short 0x66EB965
0x66eb93f  mov rdx,[0x129F9AA0]
0x66eb946  mov r9,rcx
0x66eb949  mov r8,rax
0x66eb94c  nop [rax]
0x66eb950  mov r10,[r8]
0x66eb953  cmp [r10+0x28],rdx
0x66eb957  je short 0x66EB965
0x66eb959  add r8,0x10
0x66eb95d  add r9,0xFFFFFFFFFFFFFFF0
0x66eb961  jne short 0x66EB950
0x66eb963  jmp short 0x66EB99E
0x66eb965  add rcx,rax
0x66eb968  cmp r8,rcx
0x66eb96b  jae short 0x66EB99E
0x66eb96d  sub r8d,eax
0x66eb970  shr r8d,4
0x66eb974  mov [rbp+0x1130],r8w
0x66eb97c  mov byte ptr [rbp+0x1132],1
0x66eb983  lea rdx,[rbp+0x1130]
0x66eb98a  lea r8,[rbp+0xF70]
0x66eb991  lea rcx,[rbp+0xEF0]
0x66eb998  call 0x5679DB0
0x66eb99d  nop
0x66eb99e  movups xmm0,[rbx+0x54]
0x66eb9a2  movaps [rbp+0x1440],xmm0
0x66eb9a9  mov qword ptr [rbp+0xF70],1
0x66eb9b4  mov [rbp+0xF78],rsi
```
call 0x5679DB0(&EF0,&F70,&1130) [V]. Reload rax=[rbp+0xF20], count word [rbp+0xF2A]->edx, stride ecx=edx*0x10; movups [rbx+0x64]->xmm0 -> [rbp+0x1440], [rbp+0xF70]=1, [rbp+0xF78]=rsi, r8=rax; if dx==0 jump 0x66EB965 [V]. Search entries stride 0x10 [entry+0x28] vs rdx=[0x129F9AA0]; if found jump 0x66EB965 else if not found jump 0x66EB99E [V]. rcx+=rax, bounds r8 vs rcx; if >= jump 0x66EB99E else compute (r8d-eax)/16 -> word [rbp+0x1130], valid flag=1, call 0x5679DB0(&EF0,&F70,&1130) [V]. Then movups [rbx+0x54]->xmm0 -> [rbp+0x1440], [rbp+0xF70]=1, [rbp+0xF78]=rsi [V].

## lines 1101..1140
```
0x66eb9bb  mov rax,[rbp+0xF20]
0x66eb9c2  movzx r8d,word ptr [rbp+0xF2A]
0x66eb9ca  mov edx,r8d
0x66eb9cd  shl edx,4
0x66eb9d0  mov rcx,rax
0x66eb9d3  test r8d,r8d
0x66eb9d6  je short 0x66EBA05
0x66eb9d8  mov r8,[0x129F8348]
0x66eb9df  mov r9,rdx
0x66eb9e2  mov rcx,rax
0x66eb9e5  nop [rax+rax]
0x66eb9f0  mov r10,[rcx]
0x66eb9f3  cmp [r10+0x28],r8
0x66eb9f7  je short 0x66EBA05
0x66eb9f9  add rcx,0x10
0x66eb9fd  add r9,0xFFFFFFFFFFFFFFF0
0x66eba01  jne short 0x66EB9F0
0x66eba03  jmp short 0x66EBA3B
0x66eba05  add rdx,rax
0x66eba08  cmp rcx,rdx
0x66eba0b  jae short 0x66EBA3B
0x66eba0d  sub ecx,eax
0x66eba0f  shr ecx,4
0x66eba12  mov [rbp+0x1130],cx
0x66eba19  mov byte ptr [rbp+0x1132],1
0x66eba20  lea rdx,[rbp+0x1130]
0x66eba27  lea r8,[rbp+0xF70]
0x66eba2e  lea rcx,[rbp+0xEF0]
0x66eba35  call 0x5679DB0
0x66eba3a  nop
0x66eba3b  cmp r15d,1
0x66eba3f  jne 0x66EBB93
0x66eba45  mov eax,[0x129F9AC8]
0x66eba4b  mov ecx,[0x128767C8]
0x66eba51  mov rdx,gs:[0x58]
0x66eba5a  mov rcx,[rdx+rcx*8]
0x66eba5e  cmp eax,[rcx+4]
0x66eba64  jg 0x66F8716
0x66eba6a  mov rax,[r13+0x430]
0x66eba71  test rax,rax
```
rax=[rbp+0xF20], count word [rbp+0xF2A]->r8d, stride edx=r8d*0x10, rcx=rax; if r8d==0 jump 0x66EBA05 [V]. r8=[0x129F8348], search entries stride 0x10 [entry+0x28] vs r8; if found jump 0x66EBA05 else if not found jump 0x66EBA3B [V]. On found: rdx+=rax, bounds rcx vs rdx; if >= jump 0x66EBA3B else compute (ecx-eax)/16 -> word [rbp+0x1130], valid flag=1, call 0x5679DB0(&EF0,&F70,&1130) [V]. If r15d==1: TLS static guard eax=[0x129F9AC8] cmp [rcx+4], cold path 0x66F8716 [V]. rax=[r13+0x430], test rax,rax [V].

## lines 1141..1180
```
0x66eba74  je short 0x66EBA8D
0x66eba76  cmp byte ptr [rax],1
0x66eba79  jne short 0x66EBA8D
0x66eba7b  mov rax,[r13+0x440]
0x66eba82  mov esi,0xC0
0x66eba87  add rsi,[rax+0x18]
0x66eba8b  jmp short 0x66EBAB9
0x66eba8d  mov eax,[0x129FB168]
0x66eba93  mov ecx,[0x128767C8]
0x66eba99  mov rdx,gs:[0x58]
0x66ebaa2  mov rcx,[rdx+rcx*8]
0x66ebaa6  lea rsi,[0x129FB158]
0x66ebaad  cmp eax,[rcx+4]
0x66ebab3  jg 0x66F878E
0x66ebab9  xorps xmm0,xmm0
0x66ebabc  movaps [rbp+0x1440],xmm0
0x66ebac3  mov rax,[rsi+8]
0x66ebac7  test rax,rax
0x66ebaca  je short 0x66EBB15
0x66ebacc  lock inc dword ptr [rax+8]
0x66ebad0  mov r14,[rbp+0x1448]
0x66ebad7  movups xmm0,[rsi]
0x66ebada  movaps [rbp+0x1440],xmm0
0x66ebae1  test r14,r14
0x66ebae4  je short 0x66EBB2A
0x66ebae6  lock dec dword ptr [r14+8]
0x66ebaeb  jne short 0x66EBB2A
0x66ebaed  mov rax,[r14]
0x66ebaf0  mov rax,[rax]
0x66ebaf3  mov rcx,r14
0x66ebaf6  call qword ptr [0xF99FFA0]
0x66ebafc  lock dec dword ptr [r14+0xC]
0x66ebb01  jne short 0x66EBB2A
0x66ebb03  mov rax,[r14]
0x66ebb06  mov rax,[rax+8]
0x66ebb0a mov rcx,r14
0x66ebb0d  call qword ptr [0xF99FFA0]
0x66ebb13  jmp short 0x66EBB2A
0x66ebb15  mov rax,[rsi]
0x66ebb18  mov [rbp+0x1440],rax
```
If rax!=0 and byte [rax]==1: rax=[r13+0x440], esi=0xC0 + [rax+0x18] -> rsi, jump 0x66EBAB9 [V]. Else: TLS static guard eax=[0x129FB168] cmp [rcx+4], cold path 0x66F878E [V]; rsi=&0x129FB158. xmm0=0 -> [rbp+0x1440]; rax=[rsi+8], if non-null lock inc [rax+8]; r14=[rbp+0x1448]; movups [rsi] -> [rbp+0x1440] [V]. Refcount-release r14 if non-null: dec [r14+8], destructor qword ptr [0xF99FFA0], dec [r14+0xC], destructor again [V]. Else path [rbp+0x1440]=[rsi] [V].

## lines 1181..1220
```
0x66ebb1f  mov qword ptr [rbp+0x1448],0
0x66ebb2a  mov dword ptr [rsp+0x28],0
0x66ebb32  mov byte ptr [rsp+0x20],1
0x66ebb37  lea r8,[0x129F9AC0]
0x66ebb3e  lea rcx,[rbp+0xEE8]
0x66ebb45  lea rdx,[rbp+0xF70]
0x66ebb4c  lea r9,[rbp+0x1440]
0x66ebb53  call 0xBCAC390
0x66ebb58  nop
0x66ebb59  mov r14,[rbp+0x1448]
0x66ebb60  test r14,r14
0x66ebb63  je short 0x66EBB93
0x66ebb65  lock dec dword ptr [r14+8]
0x66ebb6a  jne short 0x66EBB93
0x66ebb6c  mov rax,[r14]
0x66ebb6f  mov rax,[rax]
0x66ebb72  mov rcx,r14
0x66ebb75  call qword ptr [0xF99FFA0]
0x66ebb7b  lock dec dword ptr [r14+0xC]
0x66ebb80  jne short 0x66EBB93
0x66ebb82  mov rax,[r14]
0x66ebb85  mov rax,[rax+8]
0x66ebb89  mov rcx,r14
0x66ebb8c  call qword ptr [0xF99FFA0]
0x66ebb92  nop
0x66ebb93  lea rcx,[rbp+0xEE8]
0x66ebb9a  call 0x66A08B0
0x66ebb9f  nop
0x66ebba0  mov rsi,[rbx+0x48]
0x66ebba4  mov eax,[0x129FA890]
0x66ebbaa  mov ecx,[0x128767C8]
0x66ebbb0  mov rdx,gs:[0x58]
0x66ebbb9  mov rcx,[rdx+rcx*8]
0x66ebbbd  cmp eax,[rcx+4]
0x66ebbc3  jg 0x66F842A
0x66ebbc9  mov eax,[rsi]
0x66ebbcb  mov [rbp+0xF70],eax
0x66ebbd1  mov qword ptr [rbp+0xF74],0
0x66ebbd1  mov qword ptr [rbp+0xF7C],0
0x66ebbed  lea rcx,[rbp+0xEE8]
```
[rbp+0x1448]=0, [rsp+0x28]=0, [rsp+0x20]=1, r8=0x129F9AC0, calls 0xBCAC390(&EE8,&F70,&1440) [V]. r14=[rbp+0x1448]; refcount-release r14 if non-null: dec [r14+8], destructor qword ptr [0xF99FFA0], dec [r14+0xC], destructor again [V]. Then rcx=&EE8, call 0x66A08B0 [V]. rsi=[rbx+0x48], TLS static guard eax=[0x129FA890] cmp [rcx+4], cold path 0x66F842A [V]. eax=[rsi] -> [rbp+0xF70], zeroes [rbp+0xF74] and [rbp+0xF7C] [V]. lea rcx=&EE8 [V].

## lines 1221..1260
```
0x66ebbed  lea rcx,[rbp+0xEE8]
0x66ebbf4  lea rdx,[rbp+0x1440]
0x66ebbfb  lea r9,[rbp+0xF70]
0x66ebc02  call 0x66D93C0
0x66ebc07  nop
0x66ebc08  cmp byte ptr [rbp+0x1458],1
0x66ebc0f  jne short 0x66EBC51
0x66ebc11  mov rcx,[rbp+0x1440]
0x66ebc18  test rcx,rcx
0x66ebc1b  je short 0x66EBC51
0x66ebc1d  mov rdx,[rbp+0x1450]
0x66ebc24  sub rdx,rcx
0x66ebc27  cmp rdx,0x1000
0x66ebc2e  jb short 0x66EBC4C
0x66ebc30  mov rax,[rcx-8]
0x66ebc34  add rcx,0xFFFFFFFFFFFFFFF8
0x66ebc38  sub rcx,rax
0x66ebc3b  cmp rcx,0x20
0x66ebc3f  jae 0x66F82BB
0x66ebc45  add rdx,0x27
0x66ebc49  mov rcx,rax
0x66ebc4c  call 0xE935700
0x66ebc51  cmp byte ptr [rbp+0x16CF],0
0x66ebc58  je 0x66EBF85
0x66ebc5e  mov rax,[rbx+0x48]
0x66ebc62  cmp qword ptr [rax],0xD
0x66ebc66  jne 0x66EBD5C
0x66ebc6c  lea rax,[rbp+0xDA8]
0x66ebc73  mov [rbp+0x1370],rax
0x66ebc7a  lea rax,[rbp+0x168F]
0x66ebc81  mov [rbp+0x1378],rax
0x66ebc88  lea rax,[rbp+0x111F]
0x66ebc8f  mov [rbp+0x1380],rax
0x66ebc96  cmp byte ptr [rbp+0x1688],0
0x66ebc9d  je 0x66EBE3F
0x66ebca3  cmp byte ptr [rbx+0xB8],0
0x66ebcaa  jne 0x66EBE3F
0x66ebcb0  mov rax,[r13+0x3B8]
0x66ebcb7  mov [rbp+0x1698],rax
0x66ebcbe  mov eax,[0x129FB1E8]
```
calls 0x66D93C0(&EE8,&1440,&F70) [V]. If byte [rbp+0x1458]==1 and [rbp+0x1440]!=0: rdx=[rbp+0x1450]-[rbp+0x1440]; if rdx>=0x1000: rax=[rcx-8], rcx-=8, rcx-=rax; if rcx>=0x20 jump 0x66F82BB [V]; else rdx+=0x27, rcx=rax, call 0xE935700 [V]. If byte [rbp+0x16CF]==0 jump 0x66EBF85 [V]. rax=[rbx+0x48]; if qword [rax]!=0xD jump 0x66EBD5C [V]. Sets [rbp+0x1370]=&DA8, [rbp+0x1378]=&168F, [rbp+0x1380]=&111F [V]. If byte [rbp+0x1688]==0 or byte [rbx+0xB8]!=0 jump 0x66EBE3F [V]. rax=[r13+0x3B8] -> [rbp+0x1698]; eax=[0x129FB1E8] [V].

## lines 1261..1300
```
0x66ebcc4  mov ecx,[0x128767C8]
0x66ebcca  mov rdx,gs:[0x58]
0x66ebcd3  mov rcx,[rdx+rcx*8]
0x66ebcd7  cmp eax,[rcx+4]
0x66ebcdd  jg 0x66F8ADE
0x66ebce3  xorps xmm0,xmm0
0x66ebce6  movaps [rbp+0x1440],xmm0
0x66ebced  mov qword ptr [rbp+0xF70],1
0x66ebcf8  lea rax,[rbp+0x1440]
0x66ebcff  mov [rbp+0xF78],rax
0x66ebd06  mov rax,[rbp+0xF20]
0x66ebd0d  movzx r8d,word ptr [rbp+0xF2A]
0x66ebd15  mov edx,r8d
0x66ebd18  shl edx,4
0x66ebd1b  mov rcx,rax
0x66ebd1e  test r8d,r8d
0x66ebd21  je 0x66EF2C9
0x66ebd27  mov r8,[0x129FB1E0]
0x66ebd2e  mov r9,rdx
0x66ebd31  mov rcx,rax
0x66ebd34  nop [rax+rax]
0x66ebd40  mov r10,[rcx]
0x66ebd43  cmp [r10+0x28],r8
0x66ebd47  je 0x66EF2C9
0x66ebd4d  add rcx,0x10
0x66ebd51  add r9,0xFFFFFFFFFFFFFFF0
0x66ebd55  jne short 0x66EBD40
0x66ebd57  jmp 0x66EF301
0x66ebd5c  cmp byte ptr [rbp+0x1658],0
0x66ebd63  je 0x66EBEA1
0x66ebd69  lea rax,[rbp+0xDA8]
0x66ebd70  mov [rbp+0x1410],rax
0x66ebd77  lea rax,[rbp+0x168F]
0x66ebd7e  mov [rbp+0x1418],rax
0x66ebd85  cmp byte ptr [rbp+0x1688],0
0x66ebd8c  je 0x66EF391
0x66ebd92  cmp byte ptr [rbx+0xB8],0
0x66ebd99  jne 0x66EF391
0x66ebd9f  mov rax,[r13+0x3B8]
0x66ebda6  mov [rbp+0x1698],rax
```
TLS static guard eax=[0x129FB1E8] cmp [rcx+4], cold path 0x66F8ADE [V]. xmm0=0 -> [rbp+0x1440], [rbp+0xF70]=1, rsi=&[rbp+0x1440], [rbp+0xF78]=rax [V]. rax=[rbp+0xF20], count word [rbp+0xF2A]->r8d, stride edx=r8d*0x10, rcx=rax; if r8d==0 jump 0x66EF2C9 [V]. r8=[0x129FB1E0], search entries stride 0x10 [entry+0x28] vs r8; if found jump 0x66EF2C9 else if not found jump 0x66EF301 [V]. If byte [rbp+0x1658]==0 jump 0x66EBEA1 [V]. Sets [rbp+0x1410]=&DA8, [rbp+0x1418]=&168F [V]. If byte [rbp+0x1688]==0 or byte [rbx+0xB8]!=0 jump 0x66EF391 [V]. rax=[r13+0x3B8] -> [rbp+0x1698] [V].

## lines 1301..1340
```
0x66ebdad  mov eax,[0x129FB208]
0x66ebdb3  mov ecx,[0x128767C8]
0x66ebdb9  mov rdx,gs:[0x58]
0x66ebdc2  mov rcx,[rdx+rcx*8]
0x66ebdc6  cmp eax,[rcx+4]
0x66ebdcc  jg 0x66F8F3E
0x66ebdd2  xorps xmm0,xmm0
0x66ebdd5  movaps [rbp+0x1440],xmm0
0x66ebddc  mov qword ptr [rbp+0xF70],1
0x66ebde7  lea rax,[rbp+0x1440]
0x66ebdee  mov [rbp+0xF78],rax
0x66ebdf5  mov rax,[rbp+0xF20]
0x66ebdfc  movzx r8d,word ptr [rbp+0xF2A]
0x66ebe04  mov edx,r8d
0x66ebe07  shl edx,4
0x66ebe0a  mov rcx,rax
0x66ebe0d  test r8d,r8d
0x66ebe10  je 0x66EF3E9
0x66ebe16  mov r8,[0x129FB200]
0x66ebe1d  mov r9,rdx
0x66ebe20  mov rcx,rax
0x66ebe23  mov r10,[rcx]
0x66ebe26  cmp [r10+0x28],r8
0x66ebe2a  je 0x66EF3E9
0x66ebe30  add rcx,0x10
0x66ebe34  add r9,0xFFFFFFFFFFFFFFF0
0x66ebe38  jne short 0x66EBE23
0x66ebe3a  jmp 0x66F2819
0x66ebe3f  lea rax,[r13+0x3B0]
0x66ebe46  mov rcx,[r13+0x3B8]
0x66ebe4d  cmp qword ptr [rbp+0x1690],0xA
0x66ebe55  mov [rsp+0x48],rax
0x66ebe5a  lea rax,[rbp+0x1370]
0x66ebe61  sete [rsp+0x30]
0x66ebe66  mov [rsp+0x40],rax
0x66ebe6b  mov eax,[rbp+0x1658]
0x66ebe71  mov [rsp+0x38],al
0x66ebe75  lea rax,[rbp+0xEE8]
0x66ebe7c  mov [rsp+0x28],rax
0x66ebe81  mov [rsp+0x20],rcx
```
TLS static guard eax=[0x129FB208] cmp [rcx+4], cold path 0x66F8F3E [V]. xmm0=0 -> [rbp+0x1440], [rbp+0xF70]=1, rsi=&[rbp+0x1440], [rbp+0xF78]=rax [V]. rax=[rbp+0xF20], count word [rbp+0xF2A]->r8d, stride edx=r8d*0x10, rcx=rax; if r8d==0 jump 0x66EF3E9 [V]. r8=[0x129FB200], search entries stride 0x10 [entry+0x28] vs r8; if found jump 0x66EF3E9 else if not found jump 0x66F2819 [V]. Builds stack args: [rsp+0x48]=[r13+0x3B0], rcx=[r13+0x3B8], compares [rbp+0x1690] vs 0xA (sete -> [rsp+0x30]), [rsp+0x40]=[rbp+0x1370], [rsp+0x38]=[rbp+0x1658] byte, [rsp+0x28]=&EE8, [rsp+0x20]=rcx [V].

## NEXT
line 1381 (remaining lines 1381-1400 not yet processed; unit complete for lines 701-1340)
