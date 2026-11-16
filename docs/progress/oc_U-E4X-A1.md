## NEXT
line 701 (remaining lines 701-4013 not yet processed; unit complete for lines 1-700)

## lines 1..40
```
0x66ea3d0  push rbp
0x66ea3d1  push r15
0x66ea3d3  push r14
0x66ea3d5  push r13
0x66ea3d7  push r12
0x66ea3d9  push rsi
0x66ea3da  push rdi
0x66ea3db  push rbx
0x66ea3dc  mov eax,0x1808
0x66ea3e1  call 0xE9E7970
0x66ea3e6  sub rsp,rax
0x66ea3e9  lea rbp,[rsp+0x80]
0x66ea3f1  movaps [rbp+0x1770],xmm15
0x66ea3f9  movaps [rbp+0x1760],xmm14
0x66ea401  movaps [rbp+0x1750],xmm13
0x66ea409  movaps [rbp+0x1740],xmm12
0x66ea411  movaps [rbp+0x1730],xmm11
0x66ea419  movaps [rbp+0x1720],xmm10
0x66ea421  movaps [rbp+0x1710],xmm9
0x66ea429  movaps [rbp+0x1700],xmm8
0x66ea431  movaps [rbp+0x16F0],xmm7
0x66ea438  movaps [rbp+0x16E0],xmm6
0x66ea43f  mov qword ptr [rbp+0x16D8],0xFFFFFFFFFFFFFFFE
0x66ea44a  mov r12,r8
0x66ea44d  mov r13,rcx
0x66ea450  mov rbx,[rdx+0x48]
0x66ea454  mov rax,[rdx]
0x66ea45b  mov r14,[rdx+0x30]
0x66ea462  mov [rbp+0x16A8],rdx
0x66ea466  mov r15,[rdx+0x40]
0x66ea469  mov rsi,[rax]
0x66ea470  lea rax,[0xF2BEEE0]
0x66ea477  mov [rbp+0xD00],rax
0x66ea47e  mov byte ptr [rbp+0xD20],0
0x66ea484  mov eax,[0x128CC420]
0x66ea48a  mov ecx,[0x128767C8]
0x66ea493  mov rdx,gs:[0x58]
0x66ea497  mov rcx,[rdx+rcx*8]
0x66ea49d  cmp eax,[rcx+4]
0x66ea4a3  jg 0x66F6F53
```
Prologue: pushes 8 registers, stack probe `mov eax,0x1808; call 0xE9E7970`, frame `rbp=[rsp+0x80]`, saves xmm6-15 [V]. Stores constant `0xF2BEEE0` at [rbp+0xD00], zeroes [rbp+0xD20] [V]. TLS static guard: loads `gs:[0x58]`, compares `[rcx+4]` vs `0x128CC420`, jumps cold path if stale [V].

## NEXT
line 81 (phase 3, lines 81-120)

## lines 81..120
```
0x66ea55f  call 0xA784C0
0x66ea564  mov [rax],rsi
0x66ea567  mov byte ptr [rax+8],0
0x66ea56b  mov byte ptr [rax+0x10],1
0x66ea56e  movzx eax,byte ptr [r12+0xB8]
0x66ea577  xor r15d,r15d
0x66ea57a  mov [rbp+0x16B0],al
0x66ea580  test al,al
0x66ea582  jne short 0x66EA58F
0x66ea584  mov rax,[rbp+0x16A8]
0x66ea58b  mov r15d,[rax+0x70]
0x66ea58f  mov rax,[r12+0x48]
0x66ea594  mov rsi,[rax]
0x66ea597  lea rax,[rsi-5]
0x66ea59b  test rax,0xFFFFFFFFFFFFFFFB
0x66ea5a1  sete [rbp+0x1388]
0x66ea5a8  mov r9,rsi
0x66ea5ab  and r9,0xFFFFFFFFFFFFFFFE
0x66ea5af  cmp r9,0xA
0x66ea5b3  sete [rbp+0x1368]
0x66ea5ba  cmp byte ptr [r12+0x50],0
0x66ea5c0  mov [rbp+0x1690],r9
0x66ea5c7  je short 0x66EA603
0x66ea5c9  cmp rsi,0xA
0x66ea5cd  sete al
0x66ea5d0  cmp r15d,2
0x66ea5d4  setne cl
0x66ea5d7  and cl,al
0x66ea5d9  lea rax,[rsi-0xB]
0x66ea5dd  cmp rax,2
0x66ea5e1  setb al
0x66ea5e4  cmp rsi,1
0x66ea5e8  sete dl
0x66ea5eb  or dl,al
0x66ea5ed  or dl,cl
0x66ea5ef  mov [rbp+0x16CF],dl
0x66ea5f5  mov dword ptr [rbp+0x1658],0
0x66ea5ff  xor edi,edi
0x66ea601  jmp short 0x66EA65C
```
Third stamp via `0xA784C0(rbx+0x30)` writing owner=0,0,1 [V]. Pass-kind decode: `K = *(u64*)desc+0x48` deref [V]; `fogA = ((K-5)&~4)==0` -> [rbp+0x1388] [V]; `isAB = (K&~1)==10` -> [rbp+0x1368] [V]; if `desc+0x50 != 0` computes `f16cf = (K==10&&mode!=2)||(K-0xB<2)||(K==1)` -> [rbp+0x16CF] and zeroes [rbp+0x1658] [V]; jumps to kind-set path at 0x66EA603 otherwise.

## NEXT
line 161 (phase 5, lines 161-200)

## lines 161..200
```
0x66ea6b9  and al,[r14+0x10]
0x66ea6bd  mov [rbp+0x16D4],eax
0x66ea6c3  mov eax,[0x128767C8]
0x66ea6c9  mov rcx,gs:[0x58]
0x66ea6d2  mov rax,[rcx+rax*8]
0x66ea6d6  mov eax,[rax+4]
0x66ea6dc  mov rcx,[r12+0x48]
0x66ea6e1  mov rcx,[rcx]
0x66ea6e4  movzx edx,byte ptr [r12+0xB8]
0x66ea6ed  mov [rbp+0x16B0],dl
0x66ea6f3  and rcx,0xFFFFFFFFFFFFFFFE
0x66ea6f7  jmp short 0x66EA70A
0x66ea6f9  mov dword ptr [rbp+0x16D4],0
0x66ea703  mov rcx,[rbp+0x1690]
0x66ea70a  or bl,[rbp+0x1368]
0x66ea710  sete r14b
0x66ea714  mov [rbp+0x1698],r15d
0x66ea71b  cmp r15d,1
0x66ea71f  sete sil
0x66ea723  xor r13d,r13d
0x66ea726  cmp rcx,2
0x66ea72a  sete r15b
0x66ea72e  cmp byte ptr [r12+0xD8],3
0x66ea737  sete [rbp+0x16D0]
0x66ea73e  cmp [0x129F96D0],eax
0x66ea744  mov [rbp+0x16C0],r12
0x66ea74b  jg 0x66F6FBC
0x66ea751  and bl,sil
0x66ea754  mov r13b,r15b
0x66ea757  add r13d,r13d
0x66ea75a  cmp byte ptr [rbp+0x1388],0
0x66ea761  mov r15d,1
0x66ea767  cmove r15,r13
0x66ea76b  lea rax,[r15+3]
0x66ea76f  cmp byte ptr [r12+0xE1],0
0x66ea778  cmove rax,r15
0x66ea77c  cmp byte ptr [rbp+0x1658],0
0x66ea783  cmovne r15,rax
0x66ea787  cmp qword ptr [rbp+0x1690],0xA
0x66ea78f  cmove r15,rax
```
`f16d4 = (K-0xE<3) & builder+0x448->+0x10` -> [rbp+0x16D4] [V]; kind-class chain: `v = 2` if `f16cf && K!=0xC && K!=0xA && ((K-7<3)|(K-0xF<2))`, else `v = (K==0xC)?9:0` -> r15 [V]; `isMode3 = (desc+0xD8==3)` -> [rbp+0x16D0] [V]; TLS guard reload, jump cold if stale [V]; `desc` saved at [rbp+0x16C0] [V]; variant-index cmov chain builds `r15` from fogA, desc+0xE1, f1658, and K==0xA checks [I] (final index semantics [I], dossier says not instruction-complete).

## NEXT
line 241 (phase 7, lines 241-280)

## lines 241..280
```
0x66ea89a  cmp byte ptr [rbp+0x16D4],0
0x66ea8a1  je 0x66EA992
0x66ea8a7  mov eax,[0x128767C8]
0x66ea8ad  mov rcx,gs:[0x58]
0x66ea8b6  mov rax,[rcx+rax*8]
0x66ea8ba  mov eax,[rax+4]
0x66ea8c0  test sil,sil
0x66ea8c3  je 0x66EAA24
0x66ea8c9  cmp [0x129F9970],eax
0x66ea8cf  jg 0x66F84B6
0x66ea8d5  mov eax,[0x129F9988]
0x66ea8db  mov ecx,[0x128767C8]
0x66ea8e1  mov rdx,gs:[0x58]
0x66ea8ea  mov rcx,[rdx+rcx*8]
0x66ea8ee  cmp eax,[rcx+4]
0x66ea8f4  jg 0x66F8500
0x66ea8fa  mov rax,[rbp+0x16A8]
0x66ea901  mov r9,[rax+0x40]
0x66ea905  mov rcx,[rax+0x68]
0x66ea909  cmp qword ptr [0x129F9968],0x10
0x66ea911  jb 0x66EAB8C
0x66ea917  mov rax,[0x129F9950]
0x66ea91e  jmp 0x66EAB93
0x66ea923  cmp [0x129F9948],eax
0x66ea929  jg 0x66F824D
0x66ea92f  mov rax,[rbp+0x16A8]
0x66ea936  mov r9,[rax+0x40]
0x66ea93a  mov rcx,[rax+0x68]
0x66ea93e  xorps xmm0,xmm0
0x66ea941  movaps [rbp+0x1440],xmm0
0x66ea948  lea rax,[0xF5A5179]
0x66ea94f  mov [rbp+0xF70],rax
0x66ea956  mov qword ptr [rbp+0xF78],9
0x66ea961  lea rax,[rbp+0x1440]
0x66ea968  mov [rsp+0x28],rax
0x66ea96d  lea rax,[rbp+0xF70]
0x66ea974  mov [rsp+0x20],rax
0x66ea979  lea r8,[0x129F9938]
0x66ea980  lea rdx,[rbp+0x1130]
0x66ea987  call 0x675E440
0x66ea98c  nop
0x66ea98d  jmp 0x66EAC32
```
If `f16d4 != 0` (K in {0xE,0xF,0x10} && builder+0x448->+0x10): TLS guard, then material name pair from statics `0x129F9950`/`0x129F9960` via `0x675E440` [V] (dossier Phase 2). If `f16d4 == 0`: if `K==0xB` -> "WaterPrepass" (len 0xC, hash 0xF5490E6) via `0x675E440` [V]. Otherwise fall through to variant table path.

## NEXT
line 321 (phase 9, lines 321-360)

## lines 321..360
```
0x66eaa72  mov rax,[0x129F9990]
0x66eaa79  jmp 0x66EABE7
0x66eaa7e  add r14,r13
0x66eaa81  mov eax,[0x128767C8]
0x66eaa87  mov rcx,gs:[0x58]
0x66eaa90  mov rax,[rcx+rax*8]
0x66eaa94  mov eax,[rax+4]
0x66eaa9a  test bl,bl
0x66eaa9c  je short 0x66EAAE1
0x66eaa9e  cmp [0x129F9A08],eax
0x66eaaa4  jg 0x66F87D5
0x66eaaaa  mov rax,[rbp+0x16A8]
0x66eaab1  mov r9,[rax+0x40]
0x66eaab5  mov rcx,[rax+0x68]
0x66eaab9  shl r13,6
0x66eaabd  lea rax,[0x129F93D0]
0x66eaac4  add rax,r13
0x66eaac7  cmp qword ptr [0x129F9A00],0x10
0x66eaacf  jb 0x66EAE20
0x66eaad5  mov rdx,[0x129F99E8]
0x66eaadc  jmp 0x66EAE27
0x66eaae1  cmp [0x129F9A30],eax
0x66eaae7  jg 0x66F881F
0x66eaaed  test sil,sil
0x66eaaf0  mov rax,0x68437265646E6552
0x66eaafa  cmovne rax,[0x129F9A10]
0x66eab02  mov edx,0xB
0x66eab07  cmovne rdx,[0x129F9A20]
0x66eab0f  lea rcx,[0x129F9A10]
0x66eab16  cmp qword ptr [0x129F9A28],0x10
0x66eab1e  cmovb rax,rcx
0x66eab22  test sil,sil
0x66eab25  mov rcx,[rbp+0x16A8]
0x66eab2c  mov r9,[rcx+0x40]
0x66eab30  mov rcx,[rcx+0x68]
0x66eab34  lea r10,[0xF2BE508]
0x66eab3b  cmovne r10,rax
0x66eab3f  shl r15d,6
0x66eab43  lea rax,[0x129F93D0]
0x66eab4a  add rax,r15
0x66eab4d  shl r14,4
0x66eab51  lea r8,[0x129F96D8]
0x66eab58  add r8,r14
0x66eab5b  mov [rbp+0x1440],r10
0x66eab62  mov [rbp+0x1448],rdx
0x66eab69  mov [rsp+0x28],rax
0x66eab6e  lea rax,[rbp+0x1440]
0x66eab75  mov [rsp+0x20],rax
0x66eab7a  lea rdx,[rbp+0xF70]
0x66eab81  call 0x67CFD80
0x66eab86  nop
0x66eab87  jmp 0x66EAE68
```
Variant-table path: name table at `rip+0xc30e8xx` (0x129F93D0 + r13<<6) [V]; lazily hashed name string at `0x129F9A10` (default "RenderChunk" = 0x68437265646E6552) [V bytes]; `0x67CFD80(&out, ctx+0x40, ctx+0x68, nameptr, {slot,hash}, ...)` material resolver [V]; jump to 0x66EAE68.

## NEXT
line 361 (phase 10, lines 361-400)

## lines 361..400
```
0x66eab4d  shl r14,4
0x66eab51  lea r8,[0x129F96D8]
0x66eab58  add r8,r14
0x66eab5b  mov [rbp+0x1440],r10
0x66eab62  mov [rbp+0x1448],rdx
0x66eab69  mov [rsp+0x28],rax
0x66eab6e  lea rax,[rbp+0x1440]
0x66eab75  mov [rsp+0x20],rax
0x66eab7a  lea rdx,[rbp+0xF70]
0x66eab81  call 0x67CFD80
0x66eab86  nop
0x66eab87  jmp 0x66EAE68
0x66eab8c  lea rax,[0x129F9950]
0x66eab93  mov rdx,[0x129F9960]
0x66eab9a  xorps xmm0,xmm0
0x66eab9d  movaps [rbp+0x1440],xmm0
0x66eaba4  mov [rbp+0xF70],rax
0x66eabab  mov [rbp+0xF78],rdx
0x66eabb2  lea rax,[rbp+0x1440]
0x66eabb9  mov [rsp+0x28],rax
0x66eabbe  lea rax,[rbp+0xF70]
0x66eabc5  mov [rsp+0x20],rax
0x66eabca  lea r8,[0x129F9978]
0x66eabd1  lea rdx,[rbp+0x1130]
0x66eabd8  call 0x675E440
0x66eabdd  nop
0x66eabde  jmp short 0x66EAC32
0x66eabe0  lea rax,[0x129F9990]
0x66eabe7  mov rdx,[0x129F99A0]
0x66eabee  xorps xmm0,xmm0
0x66eabf1  movaps [rbp+0x1440],xmm0
0x66eabf8  mov [rbp+0xF70],rax
0x66eabff  mov [rbp+0xF78],rdx
0x66eac06  lea rax,[rbp+0x1440]
0x66eac0d  mov [rsp+0x28],rax
0x66eac12  lea rax,[rbp+0xF70]
0x66eac19  mov [rsp+0x20],rax
0x66eac1e  lea r8,[0x129F99B8]
0x66eac25  lea rdx,[rbp+0x1130]
0x66eac2c  call 0x675E440
0x66eac31  nop
```
End of variant-table `0x67CFD80` call [V]; then three `0x675E440` material-resolver setup blocks for K==0xA family variants (EndPortalForwardPBR/EndPortal/WaterPrepass name pairs) [V]; each ends `call 0x675E440; nop` [V].

## NEXT
line 441 (phase 12, lines 441-480)

## lines 441..480
```
0x66ead0a  mov dword ptr [rbp+0xD28],0
0x66ead14  mov byte ptr [rbp+0xD2C],7
0x66ead1b  mov word ptr [rbp+0xD34],0x101
0x66ead24  mov byte ptr [rbp+0xD36],2
0x66ead2b  mov dword ptr [rbp+0xD38],0
0x66ead35  mov byte ptr [rbp+0xD3C],0
0x66ead3c  xorps xmm0,xmm0
0x66ead3f  movups [rbp+0xD40],xmm0
0x66ead46  movups [rbp+0xD4C],xmm0
0x66ead4d  mov byte ptr [rbp+0xD5C],8
0x66ead54  mov qword ptr [rbp+0xD60],0
0x66ead5f  mov dword ptr [rbp+0xD68],0
0x66ead69  mov byte ptr [rbp+0xD6C],8
0x66ead70  mov qword ptr [rbp+0xD70],0
0x66ead7b  mov qword ptr [rbp+0xD76],0
0x66ead86  mov byte ptr [rbp+0xD7E],0xFF
0x66ead8d  or sil,al
0x66ead90  or bl,sil
0x66ead93  cmp bl,1
0x66ead96  jne short 0x66EAD9F
0x66ead98  mov byte ptr [rbp+0xD2C],0xF
0x66ead9f  xor dil,1
0x66eada3  movzx eax,dil
0x66eada7  mov [rbp+0xD30],eax
0x66eadad  test al,al
0x66eadaf  mov rax,[rbp+0x1690]
0x66eadb6  jne short 0x66EADC2
0x66eadb8  mov dword ptr [rbp+0xD50],0xFFFFFFFE
0x66eadc2  cmp byte ptr [rbp+0x16CF],0
0x66eadc9  je 0x66EAE8C
0x66eadcf  cmp rax,0xA
0x66eadd3  jne short 0x66EAE03
0x66eadd5  mov dword ptr [rbp+0xD28],2
0x66eaddf  mov rax,[rbp+0x16C0]
0x66eade6  mov rax,[rax+0x48]
0x66eadea  cmp qword ptr [rax],0xB
0x66eadee  jne 0x66EAE7B
0x66eadf4  mov dword ptr [rbp+0xD54],0x3F800000
0x66eadfe  jmp 0x66EAE85
0x66eae03  mov rax,[rbp+0x16C0]
```
Render-state record [rbp+0xD28..0xD7E]: dword 0; byte 7; word 0x101; byte 2; dword 0; byte 0; xmm zero block; byte 8; qword 0; dword 0; byte 8; qword 0; qword 0; byte 0xFF [V]. Flags: `sil = fogA | isMode3`, `bl = isAB | sil`; if bl==1 then byte [rbp+0xD2C]=0xF [V]; `dil = bl ^ 1` -> [rbp+0xD30] [V]. If kind==0 (desc+0x48 first qword==0) then [rbp+0xD50]=0xFFFFFFFE [V]. If f16cf != 0 and K==0xA: if desc+0x48 kind==0xB then [rbp+0xD28]=2, [rbp+0xD54]=0x3F800000 [V]; else if kind==1 then [rbp+0xD28]=4 [V].

## NEXT
line 521 (phase 14, lines 521-560)

## lines 521..560
```
0x66eaf56  mov rbx,[rbp+0x16C0]
0x66eaf5d  mov r13,[rbp+0x16A0]
0x66eaf64  mov [rbp+0xF68],rsi
0x66eaf6b  mov r14,[rbp+0x1448]
0x66eaf72  test r14,r14
0x66eaf75  je short 0x66EAFA4
0x66eaf77  lock dec dword ptr [r14+8]
0x66eaf7c  jne short 0x66EAFA4
0x66eaf7e  mov rax,[r14]
0x66eaf81  mov rax,[rax]
0x66eaf84  mov rcx,r14
0x66eaf87  call qword ptr [0xF99FFA0]
0x66eaf8d  lock dec dword ptr [r14+0xC]
0x66eaf92  jne short 0x66EAFA4
0x66eaf94  mov rax,[r14]
0x66eaf97  mov rax,[rax+8]
0x66eaf9b  mov rcx,r14
0x66eaf9e  call qword ptr [0xF99FFA0]
0x66eafa4  mov rax,[rbx+0x48]
0x66eafa8  cmp qword ptr [rax],1
0x66eafac  jne short 0x66EAFD2
0x66eafae  xorps xmm0,xmm0
0x66eafb1  movaps [rbp+0xF70],xmm0
0x66eafb8  mov rax,[rbx+8]
0x66eafbc  test rax,rax
0x66eafbf  je 0x66EB05C
0x66eafc5  lock inc dword ptr [rax+8]
0x66eafc9  mov rax,[rbx+8]
0x66eafcd  jmp 0x66EB05E
0x66eafd2  cmp qword ptr [rbx+0x30],2
0x66eafd7  jb 0x66EB581
0x66eafdd  mov eax,[0x129F9A58]
0x66eafe3  mov ecx,[0x128767C8]
0x66eafe9  mov rdx,gs:[0x58]
0x66eaff2  mov rcx,[rdx+rcx*8]
0x66eaff6  cmp eax,[rcx+4]
0x66eaffc  jg 0x66F8908
0x66eb002  movzx eax,word ptr [0x129F9A54]
0x66eb009  mov rcx,[rbp+0xF30]
0x66eb010  movzx r9d,word ptr [rbp+0xF3A]
0x66eb018  mov edx,r9d
0x66eb01b  shl edx,4
0x66eb01e  lea r8,[rdx+rdx*2]
0x66eb022  mov rdx,rcx
0x66eb025  test r9,r9
0x66eb028  je 0x66EB2CE
0x66eb02e  mov r9,[0x129F8318]
0x66eb035  mov r10,r8
0x66eb038  mov rdx,rcx
0x66eb03b  nop [rax+rax]
0x66eb040  mov r11,[rdx]
0x66eb043  cmp [r11+0x28],r9
0x66eb047  je 0x66EB2CE
0x66eb04d  add rdx,0x30
0x66eb051  add r10,0xFFFFFFFFFFFFFFD0
0x66eb055  jne short 0x66EB040
0x66eb057  jmp 0x66EB334
```
Refcount cleanup [V]; `rbx = desc` [rbp+0x16C0], `r13 = builder` [rbp+0x16A0], `rsi` saved at [rbp+0xF68] [V]. If `desc+0x48 kind==1`: zero vec4 at [rbp+0xF70], refcount inc on desc+8 [V]. Else if `desc+0x30 >= 2`: TLS guard, load binding count u16 at [rbp+0xF3A], binding array at [rbp+0xF30] (entries 0x30 bytes, record->+0x28 = name hash), linear scan comparing [r11+0x28] vs hash `0x129F8318` [V]; on match jump 0x66EB2CE else 0x66EB334.

## NEXT
line 561 (phase 15, lines 561-600)

## lines 561..600
```
0x66eb018  mov edx,r9d
0x66eb01b  shl edx,4
0x66eb01e  lea r8,[rdx+rdx*2]
0x66eb022  mov rdx,rcx
0x66eb025  test r9,r9
0x66eb028  je 0x66EB2CE
0x66eb02e  mov r9,[0x129F8318]
0x66eb035  mov r10,r8
0x66eb038  mov rdx,rcx
0x66eb03b  nop [rax+rax]
0x66eb040  mov r11,[rdx]
0x66eb043  cmp [r11+0x28],r9
0x66eb047  je 0x66EB2CE
0x66eb04d  add rdx,0x30
0x66eb051  add r10,0xFFFFFFFFFFFFFFD0
0x66eb055  jne short 0x66EB040
0x66eb057  jmp 0x66EB334
0x66eb05c  xor eax,eax
0x66eb05e  mov rcx,[rbx]
0x66eb061  mov [rbp+0xF70],rcx
0x66eb068  mov [rbp+0xF78],rax
0x66eb06f  lea r15,[rbx+0x10]
0x66eb073  movaps [rbp+0x1130],xmm0
0x66eb07a  mov rax,[rbx+0x18]
0x66eb07e  test rax,rax
0x66eb081  je short 0x66EB08D
0x66eb083  lock inc dword ptr [rax+8]
0x66eb087  mov r14,[rbx+0x18]
0x66eb08b  jmp short 0x66EB090
0x66eb08d  xor r14d,r14d
0x66eb090  mov rax,[r15]
0x66eb093  mov [rbp+0x1130],rax
0x66eb09a  mov [rbp+0x1138],r14
0x66eb0a1  movzx esi,word ptr [0x128C1A5E]
0x66eb0a8  mov eax,[0x129F9A40]
0x66eb0ae  mov ecx,[0x128767C8]
0x66eb0b4  mov rdx,gs:[0x58]
0x66eb0bd  mov rcx,[rdx+rcx*8]
0x66eb0c1  cmp eax,[rcx+4]
0x66eb0c7  jg 0x66F8632
```
Binding scan continues: slot index = (matchptr-base)>>4 via `shl edx,4; lea r8,[rdx+rdx*2]` (entry stride 0x30 = 3*0x10) [V]; on no match jump 0x66EB334 [V]. If match: `rcx = [rbx]` (desc vtable), [rbp+0xF70] = rcx, [rbp+0xF78] = 0, `r15 = rbx+0x10`, zero xmm0 at [rbp+0x1130] [V]. Refcount inc on [rbx+0x18] -> r14 [V]; [rbp+0x1130] = [rbx+0x10], [rbp+0x1138] = r14 [V]. `esi = word [0x128C1A5E]` (binding count u16) [V]; TLS guard reload.

## NEXT
line 601 (phase 16, lines 601-640)

## lines 601..640
```
0x66eb002  movzx eax,word ptr [0x129F9A54]
0x66eb009  mov rcx,[rbp+0xF30]
0x66eb010  movzx r9d,word ptr [rbp+0xF3A]
0x66eb018  mov edx,r9d
0x66eb01b  shl edx,4
0x66eb01e  lea r8,[rdx+rdx*2]
0x66eb022  mov rdx,rcx
0x66eb025  test r9,r9
0x66eb028  je 0x66EB2CE
0x66eb02e  mov r9,[0x129F8318]
0x66eb035  mov r10,r8
0x66eb038  mov rdx,rcx
0x66eb03b  nop [rax+rax]
0x66eb040  mov r11,[rdx]
0x66eb043  cmp [r11+0x28],r9
0x66eb047  je 0x66EB2CE
0x66eb04d  add rdx,0x30
0x66eb051  add r10,0xFFFFFFFFFFFFFFD0
0x66eb055  jne short 0x66EB040
0x66eb057  jmp 0x66EB334
0x66eb05c  xor eax,eax
0x66eb05e  mov rcx,[rbx]
0x66eb061  mov [rbp+0xF70],rcx
0x66eb068  mov [rbp+0xF78],rax
0x66eb06f  lea r15,[rbx+0x10]
0x66eb073  movaps [rbp+0x1130],xmm0
0x66eb07a  mov rax,[rbx+0x18]
0x66eb07e  test rax,rax
0x66eb081  je short 0x66EB08D
0x66eb083  lock inc dword ptr [rax+8]
0x66eb087  mov r14,[rbx+0x18]
0x66eb08b  jmp short 0x66EB090
0x66eb08d  xor r14d,r14d
0x66eb090  mov rax,[r15]
0x66eb093  mov [rbp+0x1130],rax
0x66eb09a  mov [rbp+0x1138],r14
0x66eb0a1  movzx esi,word ptr [0x128C1A5E]
0x66eb0a8  mov eax,[0x129F9A40]
0x66eb0ae  mov ecx,[0x128767C8]
0x66eb0b4  mov rdx,gs:[0x58]
```
Binding-name hash slot at `0x129F9A54`, binding array base at [rbp+0xF30], count u16 at [rbp+0xF3A] (entry stride 0x30) [V]; linear scan compares [r11+0x28] (record name hash) vs `0x129F8318` [V]; on match jump 0x66EB2CE, else 0x66EB334 [V]. If no match: `rcx=[rbx]` desc vtable, [rbp+0xF70]=rcx, [rbp+0xF78]=0, `r15=rbx+0x10`, zero [rbp+0x1130] [V]; refcount inc [rbx+0x18] -> r14 [V]; `esi = word [0x128C1A5E]` binding count; TLS guard reload.

## NEXT
line 641 (phase 17, lines 641-680)

## lines 641..680
```
0x66eb0bd  mov rcx,[rdx+rcx*8]
0x66eb0c1  cmp eax,[rcx+4]
0x66eb0c7  jg 0x66F8632
0x66eb0cd  mov rax,[rbp+0xF30]
0x66eb0d4  movzx r8d,word ptr [rbp+0xF3A]
0x66eb0dc  mov ecx,r8d
0x66eb0df  shl ecx,4
0x66eb0e2  lea rdx,[rcx+rcx*2]
0x66eb0e6  mov rcx,rax
0x66eb0e9  test r8,r8
0x66eb0ec  je short 0x66EB115
0x66eb0ee  mov r8,[0x129F9A38]
0x66eb0f5  mov r9,rdx
0x66eb0f8  mov rcx,rax
0x66eb0fb  nop [rax+rax]
0x66eb100  mov r10,[rcx]
0x66eb103  cmp [r10+0x28],r8
0x66eb107  je short 0x66EB115
0x66eb109  add rcx,0x30
0x66eb10d  add r9,0xFFFFFFFFFFFFFFD0
0x66eb111  jne short 0x66EB100
0x66eb113  jmp short 0x66EB17B
0x66eb115  add rdx,rax
0x66eb118  cmp rcx,rdx
0x66eb11b  jae short 0x66EB17B
0x66eb11d  sub ecx,eax
0x66eb11f  shr ecx,4
0x66eb122  imul eax,ecx,0xFFFFAAAB
0x66eb128  mov [rbp+0xC78],ax
0x66eb12f  mov byte ptr [rbp+0xC7A],1
0x66eb136  mov [rbp+0x1440],si
0x66eb13d  mov dword ptr [rbp+0x1444],0
0x66eb147  mov byte ptr [rbp+0x1448],1
0x66eb14e  mov byte ptr [rbp+0x144C],1
0x66eb155  mov dword ptr [rsp+0x20],0
0x66eb15d  lea rcx,[rbp+0xEE8]
0x66eb164  lea rdx,[rbp+0xC78]
0x66eb16b  lea r9,[rbp+0x1440]
0x66eb172  mov r8,rbx
0x66eb175  call 0xBCABA00
```
TLS guard reload; second binding scan (hash `0x129F9A38`) over same array [V]; slot index = (match-base)/0x10 via `sub ecx,eax; shr ecx,4; imul eax,ecx,0xFFFFAAAB` (division by 0x10) -> [rbp+0xC78] ax, byte 1 at [rbp+0xC7A] [V]. Uniform struct at [rbp+0x1440]: {u16 slot=esi, u32 0, u8 1, u8 1} [V]; `0xBCABA00(&[rbp+0xEE8], &[rbp+0xC78], &[rbp+0x1440], rbx)` registers the binding [V].

## NEXT
line 681 (phase 18, lines 681-700)

## lines 681..700
```
0x66eb17a  nop
0x66eb17b  mov eax,[0x129F9A50]
0x66eb181  mov ecx,[0x128767C8]
0x66eb187  mov rdx,gs:[0x58]
0x66eb190  mov rcx,[rdx+rcx*8]
0x66eb194  cmp eax,[rcx+4]
0x66eb19a  jg 0x66F86A4
0x66eb1a0  mov rax,[rbp+0xF30]
0x66eb1a7  movzx r8d,word ptr [rbp+0xF3A]
0x66eb1af  mov ecx,r8d
0x66eb1b2  shl ecx,4
0x66eb1b5  lea rdx,[rcx+rcx*2]
0x66eb1b9  mov rcx,rax
0x66eb1bc  test r8,r8
0x66eb1bf  je short 0x66EB1E5
0x66eb1c1  mov r8,[0x129F9A48]
0x66eb1c8  mov r9,rdx
0x66eb1cb  mov rcx,rax
0x66eb1ce  xchg ax,ax
0x66eb1d0  mov r10,[rcx]
```
Third binding scan (hash `0x129F9A48`) [V]; TLS guard; entry stride 0x30; on match jump 0x66EB1E5, end at 0x66EB17B [V]. Unit ends at line 700 (RVA 0x66eb1d0) mid-scan; remaining 3313 lines (701-4013) not yet processed.


## lines 481..520
```
0x66eae03  mov rax,[rbp+0x16C0]
0x66eae0a  mov rax,[rax+0x48]
0x66eae0e  cmp qword ptr [rax],1
0x66eae12  jne short 0x66EAE8C
0x66eae14  mov dword ptr [rbp+0xD28],4
0x66eae1e  jmp short 0x66EAE8C
0x66eae20  lea rdx,[0x129F99E8]
0x66eae27  mov r10,[0x129F99F8]
0x66eae2e  shl r14,4
0x66eae32  lea r8,[0x129F96D8]
0x66eae39  add r8,r14
0x66eae3c  mov [rbp+0x1440],rdx
0x66eae43  mov [rbp+0x1448],r10
0x66eae4a  mov [rsp+0x28],rax
0x66eae4f  lea rax,[rbp+0x1440]
0x66eae56  mov [rsp+0x20],rax
0x66eae5b  lea rdx,[rbp+0xF70]
0x66eae62  call 0x67CFD80
0x66eae67  nop
0x66eae68  mov r13,[rbp+0xF70]
0x66eae6f  mov r14,[rbp+0xF78]
0x66eae76  jmp 0x66EAC40
0x66eae7b  mov dword ptr [rbp+0xD50],0xFFFFFFFE
0x66eae85  mov byte ptr [rbp+0xD35],0
0x66eae8c  mov byte ptr [rbp+0xD36],4
0x66eae93  mov rax,[rbp+0x16C0]
0x66eae9a  mov [rbp+0xDA8],rax
0x66eaea1  lea rax,[rbp+0xD28]
0x66eaea8  mov [rbp+0xDB0],rax
0x66eaeaf  mov rax,[rbp+0x16A8]
0x66eaeb6  mov rsi,[rax]
0x66eaeb9  movaps [rbp+0x1440],xmm0
0x66eaec0  mov rax,[r13+8]
0x66eaec4  test rax,rax
0x66eaec7  je short 0x66EAF14
0x66eaec9  lock inc dword ptr [rax+8]
0x66eaecd  mov r14,[rbp+0x1448]
0x66eaed4  movups xmm0,[r13]
0x66eaed9  movaps [rbp+0x1440],xmm0
0x66eaee0  test r14,r14
0x66eaee3  je short 0x66EAF2A
0x66eaee5  lock dec dword ptr [r14+8]
0x66eaeea  jne short 0x66EAF2A
0x66eaeec  mov rax,[r14]
0x66eaeef  mov rax,[rax]
0x66eaef2  mov rcx,r14
0x66eaef5  call qword ptr [0xF99FFA0]
0x66eaefb  lock dec dword ptr [r14+0xC]
0x66eaf00  jne short 0x66EAF2A
0x66eaf02  mov rax,[r14]
0x66eaf05  mov rax,[rax+8]
0x66eaf09  mov rcx,r14
0x66eaf0c  call qword ptr [0xF99FFA0]
0x66eaf12  jmp short 0x66EAF2A
0x66eaf14  mov rax,[r13]
0x66eaf18  mov [rbp+0x1440],rax
0x66eaf1f  mov qword ptr [rbp+0x1448],0
0x66eaf2a  mov rax,[rbp+0x1440]
0x66eaf31  mov rax,[rax+0x18]
0x66eaf35  mov rax,[rax]
0x66eaf38  mov [rbp+0xEE8],rax
0x66eaf3f  lea rcx,[rbp+0xEF0]
0x66eaf46  mov r8,[rsi]
0x66eaf49  mov rdx,[rax+0x170]
0x66eaf50  call 0xE86B370
0x66eaf55  nop
```
If K==1 and desc+0x48 kind==1: [rbp+0xD28]=4 [V]. Else variant-table `0x67CFD80(&out, ctx+0x40, ctx+0x68, nameptr, {slot,hash})` material resolver [V]; result r13/r14; jump back to 0x66EAC40. [rbp+0xD36]=4; [rbp+0xDA8]=desc; [rbp+0xDB0]=&state rec [V]. Pass record built: `0xE86B370(&rec(0xEF0), resource, ...)` [V] (dossier Phase 2). Shared_ptr refcount adjustments [V]. [rbp+0xEE8] = material interface ptr [V].


## lines 401..440
```
0x66eac32  mov r13,[rbp+0x1130]
0x66eac39  mov r14,[rbp+0x1138]
0x66eac40  mov [rbp+0x12D0],r13
0x66eac47  mov [rbp+0x12D8],r14
0x66eac4e  mov r15,[r13]
0x66eac52  test r15,r15
0x66eac55  je 0x66F6E42
0x66eac5b  mov eax,[0x129CA5E0]
0x66eac61  mov ecx,[0x128767C8]
0x66eac67  mov rdx,gs:[0x58]
0x66eac70  mov rcx,[rdx+rcx*8]
0x66eac74  cmp eax,[rcx+4]
0x66eac7a  jg 0x66F8196
0x66eac80  cmp byte ptr [r15+0x10],1
0x66eac85  jne 0x66F6E42
0x66eac8b  mov rax,[r13+8]
0x66eac8f  test rax,rax
0x66eac92  je short 0x66EACDB
0x66eac94  lock inc dword ptr [rax+8]
0x66eac98  mov rax,[r13]
0x66eac9c  mov r15,[r13+8]
0x66eaca0  mov rax,[rax+0x18]
0x66eaca4  mov r12,[rax]
0x66eaca7  test r15,r15
0x66eacaa  je short 0x66EACE6
0x66eacac  lock dec dword ptr [r15+8]
0x66eacb1  jne short 0x66EACE6
0x66eacb3  mov rax,[r15]
0x66eacb6  mov rax,[rax]
0x66eacb9  mov rcx,r15
0x66eacbc  call qword ptr [0xF99FFA0]
0x66eacc2  lock dec dword ptr [r15+0xC]
0x66eacc7  jne short 0x66EACE6
0x66eacc9  mov rax,[r15]
0x66eaccc  mov rax,[rax+8]
0x66eacd0  mov rcx,r15
0x66eacd3  call qword ptr [0xF99FFA0]
0x66eacd9  jmp short 0x66EACE6
0x66eacdb  mov rax,[r13]
0x66eacdf  mov rax,[rax+0x18]
0x66eace3  mov r12,[rax]
0x66eace6  test r12,r12
0x66eace9  mov r15d,[rbp+0x1698]
0x66eacf0  je 0x66F6E42
```
Material instance from [rbp+0x1130] -> r13, [rbp+0x1138] -> r14; null or `inst->+0x10 != 1` -> exit 0x66F6E42 [V]. Shared_ptr refcount inc/dec with release via `call qword ptr [0xF99FFA0]` [V]. `r12 = inst->+0x18->+0x0` (vtable/interface ptr) [V]. `r15d = mode` [rbp+0x1698] [V].



## lines 281..320
```
0x66ea98c  nop
0x66ea98d  jmp 0x66EAC32
0x66ea992  cmp rax,0xB
0x66ea996  jne 0x66EAA7E
0x66ea99c  mov eax,[0x129F99E0]
0x66ea9a2  mov ecx,[0x128767C8]
0x66ea9a8  mov rdx,gs:[0x58]
0x66ea9b1  mov rcx,[rdx+rcx*8]
0x66ea9b5  cmp eax,[rcx+4]
0x66ea9bb  jg 0x66F853D
0x66ea9c1  mov rax,[rbp+0x16A8]
0x66ea9c8  mov r9,[rax+0x40]
0x66ea9cc  mov rcx,[rax+0x68]
0x66ea9d0  xorps xmm0,xmm0
0x66ea9d3  movaps [rbp+0x1440],xmm0
0x66ea9da  lea rax,[0xF5490E6]
0x66ea9e1  mov [rbp+0xF70],rax
0x66ea9e8  mov qword ptr [rbp+0xF78],0xC
0x66ea9f3  lea rax,[rbp+0x1440]
0x66ea9fa  mov [rsp+0x28],rax
0x66ea9ff  lea rax,[rbp+0xF70]
0x66eaa06  mov [rsp+0x20],rax
0x66eaa0b  lea r8,[0x129F99D0]
0x66eaa12  lea rdx,[rbp+0x1130]
0x66eaa19  call 0x675E440
0x66eaa1e  nop
0x66eaa1f  jmp 0x66EAC32
0x66eaa24  cmp [0x129F99B0],eax
0x66eaa2a  jg 0x66F85A5
0x66eaa30  mov eax,[0x129F99C8]
0x66eaa36  mov ecx,[0x128767C8]
0x66eaa3c  mov rdx,gs:[0x58]
0x66eaa45  mov rcx,[rdx+rcx*8]
0x66eaa49  cmp eax,[rcx+4]
0x66eaa4f  jg 0x66F85EF
0x66eaa55  mov rax,[rbp+0x16A8]
0x66eaa5c  mov r9,[rax+0x40]
0x66eaa60  mov rcx,[rax+0x68]
0x66eaa64  cmp qword ptr [0x129F99A8],0x10
0x66eaa6c  jb 0x66EABE0
```
`K==0xB` (WaterPrepass): hash slot `0x129F99D0`, name len 0xC, `0x675E440` resolver [V]; jump to 0x66EAC32 on success. Else fall through to variant-table material selection via `0x67CFD80` [V].


## lines 201..240
```
0x66ea793  mov rax,[rbp+0x16A8]
0x66ea79a  cmp byte ptr [rax+0x74],0
0x66ea79e  lea r13,[r15+6]
0x66ea7a2  cmove r13,r15
0x66ea7a6  test bl,bl
0x66ea7a8  cmove r13,r15
0x66ea7ac  mov eax,[0x129F9918]
0x66ea7b2  mov ecx,[0x128767C8]
0x66ea7b8  mov rdx,gs:[0x58]
0x66ea7c1  mov rcx,[rdx+rcx*8]
0x66ea7c5  cmp eax,[rcx+4]
0x66ea7cb  jg 0x66F7706
0x66ea7d1  xor eax,eax
0x66ea7d3  and sil,r14b
0x66ea7d6  mov ecx,0xC
0x66ea7db  cmove rcx,rax
0x66ea7df  lea r14,[rcx+0x18]
0x66ea7e3  test bl,bl
0x66ea7e5  cmove r14,rcx
0x66ea7e9  xorps xmm0,xmm0
0x66ea7ec  movaps [rbp+0x12D0],xmm0
0x66ea7f3  mov rax,[r12+0x48]
0x66ea7f8  mov rax,[rax]
0x66ea7fb  cmp rax,1
0x66ea7ff  jne 0x66EA89A
0x66ea805  mov eax,[0x128767C8]
0x66ea80b  mov rcx,gs:[0x58]
0x66ea814  mov rax,[rcx+rax*8]
0x66ea818  mov eax,[rax+4]
0x66ea81e  cmp dword ptr [rbp+0x1698],1
0x66ea825  jne 0x66EA923
0x66ea82b  cmp [0x129F9930],eax
0x66ea831  jg 0x66F81E5
0x66ea837  mov rax,[rbp+0x16A8]
0x66ea83e  mov r9,[rax+0x40]
0x66ea842  mov rcx,[rax+0x68]
0x66ea846  xorps xmm0,xmm0
0x66ea849  movaps [rbp+0x1440],xmm0
0x66ea850  lea rax,[0xF7CA24E]
0x66ea857  mov [rbp+0xF70],rax
0x66ea85e  mov qword ptr [rbp+0xF78],0x13
0x66ea869  lea rax,[rbp+0x1440]
0x66ea870  mov [rsp+0x28],rax
0x66ea875  lea rax,[rbp+0xF70]
0x66ea87c  mov [rsp+0x20],rax
0x66ea881  lea r8,[0x129F9920]
0x66ea888  lea rdx,[rbp+0x1130]
0x66ea88f  call 0x675E440
0x66ea894  nop
0x66ea895  jmp 0x66EAC32
```
`mode = desc+0xB8 ? raw : ctx+0x70` -> r15d; mode==1 is ForwardPBR family [V]. Variant index cmov: `r13 = (mode!=0)?r15+6:r15`, zeroed if `bl==0` [V]. If `K==1`: if `mode==1` material="EndPortalForwardPBR" (len 0x13, hash 0xF7CA24E) else "EndPortal" (len 9); resolve via `0x675E440(&out, ctx+0x68, ctx+0x40, hashslot, {name,len}, {0,0})` [V]; if `!inst || inst->+0x10 != 1` goto exit 0x66F6E42 [V].


## lines 121..160
```
0x66ea603  cmp rsi,9
0x66ea607  sete al
0x66ea60a  lea rcx,[rsi-7]
0x66ea60e  cmp rcx,3
0x66ea612  setb cl
0x66ea615  cmp rsi,0xD
0x66ea619  sete dl
0x66ea61c  lea r8,[rsi-2]
0x66ea620  cmp r8,3
0x66ea624  setb r8b
0x66ea628  or r8b,cl
0x66ea62b  mov rcx,rsi
0x66ea62e  sub rcx,0xF
0x66ea632  sete dil
0x66ea636  cmp rcx,2
0x66ea63a  setb cl
0x66ea63d  or cl,dl
0x66ea63f  or cl,r8b
0x66ea642  mov [rbp+0x1658],ecx
0x66ea648  cmp r9,6
0x66ea64c  sete cl
0x66ea64f  or dil,al
0x66ea652  or dil,cl
0x66ea655  mov byte ptr [rbp+0x16CF],1
0x66ea65c  movzx ebx,byte ptr [r12+0xE0]
0x66ea665  mov rax,[rbp+0x16A8]
0x66ea66c  movzx eax,byte ptr [rax+0x75]
0x66ea670  mov [rbp+0x1688],al
0x66ea676  mov r14,[r13+0x448]
0x66ea67d  mov eax,[0x128767C8]
0x66ea683  mov rcx,gs:[0x58]
0x66ea68c  mov rax,[rcx+rax*8]
0x66ea690  mov eax,[rax+4]
0x66ea696  test r14,r14
0x66ea699  mov [rbp+0x16A0],r13
0x66ea6a0  je short 0x66EA6F9
0x66ea6a2  add rsi,0xFFFFFFFFFFFFFFF2
0x66ea6a6  cmp [0x129CFEAC],eax
0x66ea6ac  jg 0x66F8160
0x66ea6b2  cmp rsi,3
0x66ea6b6  setb al
```
`desc+0x50 == 0` path: `f1658 = K in {2,3,4,7,8,9,0xD,0xF,0x10}` via `(K-2<3)|(K-7<3)|(K==0xD)|(K-0xF<2)` -> [rbp+0x1658] [V]; `f16cf = 1` [V]; `ditherKind = (K==0xF)|(K==9)|((K&~1)==6)` [V]. `f1688 = desc+0xE0` byte -> [rbp+0x1688] [V]; `f16d4 = builder+0x448` ptr -> r14 [V]; TLS guard reload; if `builder+0x448 != 0` then `f16d4 = (K-0xE<3) & builder+0x448->+0x10` [V].


## lines 41..80
```
0x66ea4a8  call 0xEEC58F0
0x66ea4ad  mov ecx,[0x128767C8]
0x66ea4ae  mov rdx,gs:[0x58]
0x66ea4b7  mov rcx,[rdx+rcx*8]
0x66ea4bb  cmp byte ptr [rcx+0xBB8],0
0x66ea4c2  je 0x66F6F24
0x66ea4c8  mov ecx,[0x128767C8]
0x66ea4ce  mov rdx,gs:[0x58]
0x66ea4d7  mov rcx,[rdx+rcx*8]
0x66ea4db  mov r8,[rcx+0xBA8]
0x66ea4e2  mov rdx,[rcx+0xBA0]
0x66ea4e9  lea rcx,[0x128CC3D0]
0x66ea4f0  cmp r8,rdx
0x66ea4f3  je short 0x66EA509
0x66ea4f5  lea r9,[r8-0x10]
0x66ea4f9  cmp [r8-0x10],rcx
0x66ea4fd  mov r8,r9
0x66ea500  jne short 0x66EA4F0
0x66ea502  add r9,8
0x66ea506  mov rcx,r9
0x66ea509  cmp [rcx],eax
0x66ea50b  je short 0x66EA56E
0x66ea50d  mov [rbp+0xD08],rbx
0x66ea514  mov [rbp+0xD10],r14
0x66ea51b  mov [rbp+0xD18],r15
0x66ea522  mov byte ptr [rbp+0xD20],1
0x66ea529  add r15,0x30
0x66ea52d  mov rcx,r15
0x66ea530  call 0xA784C0
0x66ea535  mov [rax],rsi
0x66ea538  mov byte ptr [rax+8],0
0x66ea53c  mov byte ptr [rax+0x10],1
0x66ea540  add r14,0x30
0x66ea544  mov rcx,r14
0x66ea547  call 0xA784C0
0x66ea54c  mov [rax],rsi
0x66ea54f  mov byte ptr [rax+8],0
0x66ea553  mov byte ptr [rax+0x10],1
0x66ea557  add rbx,0x30
0x66ea55b  mov rcx,rbx
```
Guard not stale: calls `0xEEC58F0` (thread-safe statics init) [V]. Validates TLS slot against `0x128CC3D0`; on match stamps three registry slots via `0xA784C0(reg->+0x30)` writing owner=`rsi`, 0, 1 for regC/regA/regB [V]. Fallthrough at 0x66EA56E.
