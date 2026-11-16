# Unit U-E4X-B3: chunk extractor 0x66ea3d0 body B — lines 1401..2050 of docs/data/listings/e4_B.txt
## NEXT
Next line to do: 1401 (phase 1 of 17 complete)
Base RVA: 0x66f0fab; end RVA at line 2050: 0x66f1c32
Context: body B = K==13 light_source inline body of ChunkGeometry extractor at 0x66ea3d0 (docs/functions/66ea3d0.md)

### lines 1401..1440
```asm
0x66f0fab  mov [rbx+0x80],rax
0x66f0fb2  mov qword ptr [rbp+0x14D0],0
0x66f0fbd  add qword ptr [r15+0x770],0x88
0x66f0fc8  jmp short 0x66F0FE1
0x66f0fca  lea rcx,[r15+0x768]
0x66f0fd1  mov rdx,rbx
0x66f0fd4  lea r8,[rbp+0x1450]
0x66f0fdb  call 0x6760710
0x66f0fe0  nop
0x66f0fe1  mov rcx,[0x1233E1B0]
0x66f0fe8  mov rax,[rcx]
0x66f0feb  mov rax,[rax+0x10]
0x66f0fef  movzx edx,byte ptr [rbp+0x16D4]
0x66f0ff6  call qword ptr [0xF99FFA0]
0x66f0ffc  nop
0x66f0ffd  mov qword ptr [rbp+0x1130],0x2007803
0x66f1008  mov eax,[r15+0x770]
0x66f100f  sub eax,[r15+0x768]
0x66f1016  shr eax,3
0x66f1019  imul eax,0xFFFFF0F1
0x66f101f  dec eax
0x66f1021  mov [rbp+0x115A],ax
0x66f1028  mov rcx,[0x1233E1B0]
0x66f102f  mov rax,[rcx]
0x66f1032  mov rax,[rax+0x10]
0x66f1036  mov dl,0x4A
0x66f1038  call qword ptr [0xF99FFA0]
0x66f103e  nop
0x66f103f  mov [rbp+0x16D4],al
0x66f1045  mov rdx,[r15+0x680]
0x66f104c  cmp rdx,[r15+0x688]
0x66f1053  je short 0x66F1085
0x66f1055  movss xmm0,[rbp+0x1444]
0x66f105d  movss [rdx],xmm0
0x66f1061  movss xmm0,[rbp+0x1448]
0x66f1069  movss [rdx+4],xmm0
0x66f106e  movss xmm0,[rbp+0x144C]
0x66f1076  movss [rdx+8],xmm0
0x66f107b  add qword ptr [r15+0x680],0xC
0x66f1083  jmp short 0x66F1099
0x66f1085  lea rcx,[r15+0x678]
0x66f108c  lea r8,[rbp+0x1444]
0x66f1093  call 0x1770A70
0x66f1098  nop
0x66f1099  mov rcx,[0x1233E1B0]
0x66f10a0  mov rax,[rcx]
0x66f10a3  mov rax,[rax+0x10]
0x66f10a7  movzx edx,byte ptr [rbp+0x16D4]
0x66f10ae  call qword ptr [0xF99FFA0]
0x66f10b4  nop
0x66f10b5  mov eax,[r15+0x680]
0x66f10bc  sub eax,[r15+0x678]
0x66f10c3  shr eax,2
0x66f10c6  imul eax,0xFFFFAAAB
0x66f10cc  dec eax
0x66f10ce  mov [rbp+0x116E],ax
```
Meaning: Fast-path store [rbx+0x80]=rax, clear [rbp+0x14D0], advance [r15+0x770] by 0x88, jump to feature-flag block 0x66F0FE1 [V]. Slow path: call 0x6760710(&[r15+0x768], rbx, &[rbp+0x1450]) then fall through to 0x66F0FE1 [V]. At 0x66F0FE1: vcall qword [0xF99FFA0]([0x1233E1B0]+0x10, dl=[rbp+0x16D4]) -> [rbp+0x16D4] [V]. Store tag [rbp+0x1130]=0x2007803, compute count = ([r15+0x770]-[r15+0x768])>>3 via magic multiply 0xFFFFF0F1 -> [rbp+0x115A] [V]. Second vcall flag 0x4A [V]. Fast path: store 3 float fields [rbp+0x1444/48/4C] to [r15+0x680], add [r15+0x680] by 0xC [V]. Slow path: call 0x1770A70(&[r15+0x678], &[rbp+0x1444]) then fall through [V]. Compute count2 = ([r15+0x680]-[r15+0x678])>>2 via 0xFFFFAAAB -> [rbp+0x116E] [V].

## NEXT
Next line to do: 1441 (phase 2 of 17 complete)

### lines 1441..1480
```asm
0x66f10d5  mov rcx,[0x1233E1B0]
0x66f10dc  mov rax,[rcx]
0x66f10df  mov rax,[rax+0x10]
0x66f10e3  mov dl,0x4A
0x66f10e5  call qword ptr [0xF99FFA0]
0x66f10eb  nop
0x66f10ec  mov [rbp+0x16D4],al
0x66f10f2  mov rdx,[r15+0x608]
0x66f10f9  cmp rdx,[r15+0x610]
0x66f1100  je short 0x66F110E
0x66f1102  inc rdx
0x66f1105  mov [r15+0x608],rdx
0x66f110c  jmp short 0x66F111E
0x66f110e  mov rcx,r15
0x66f1111  add rcx,0x600
0x66f1118  call 0x6760E60
0x66f111d  nop
0x66f111e  mov rcx,[0x1233E1B0]
0x66f1125  mov rax,[rcx]
0x66f1128  mov rax,[rax+0x10]
0x66f112c  movzx edx,byte ptr [rbp+0x16D4]
0x66f1133  call qword ptr [0xF99FFA0]
0x66f1139  nop
0x66f113a  mov qword ptr [rbp+0x1130],0x12807803
0x66f1145  mov eax,[r15+0x600]
0x66f114c  not eax
0x66f114e  add eax,[r15+0x608]
0x66f1155  mov [rbp+0x1178],ax
0x66f115c  mov rcx,[0x1233E1B0]
0x66f1163  mov rax,[rcx]
0x66f1166  mov rax,[rax+0x10]
0x66f116a  mov dl,0x4A
0x66f116c  call qword ptr [0xF99FFA0]
0x66f1172  nop
0x66f1173  mov [rbp+0x16D4],al
0x66f1179  mov rdx,[r15+8]
0x66f117d  cmp rdx,[r15+0x10]
0x66f1181  je short 0x66F119E
0x66f1183  mov r8d,0xC8
0x66f1189  mov rcx,rdx
0x66f118c  mov rdx,r12
0x66f118f  call 0xEEC6EC0
0x66f1194  add qword ptr [r15+8],0xC8
0x66f119c  jmp short 0x66F11AA
0x66f119e  mov rcx,r15
0x66f11a1  mov r8,r12
0x66f11a4  call 0x5ABA6D0
0x66f11a9  nop
0x66f11aa  mov rcx,[0x1233E1B0]
0x66f11b1  mov rax,[rcx]
0x66f11b4  mov rax,[rax+0x10]
0x66f11b8  movzx edx,byte ptr [rbp+0x16D4]
0x66f11bf  call qword ptr [0xF99FFA0]
0x66f11c5  nop
0x66f11c6  lea rcx,[rbp+0x1440]
0x66f11cd  call 0x67E1660
0x66f11d2  lea rcx,[rbp+0xF70]
0x66f11d9  call 0x67E1660
0x66f11de  jmp 0x66F26C0
```
Meaning: Third vcall flag 0x4A -> [rbp+0x16D4] [V]. Fast path: inc [r15+0x608] [V]. Slow path: call 0x6760E60(r15+0x600) then fall through [V]. Fourth vcall flag 0x4A [V]. Store tag [rbp+0x1130]=0x12807803, compute ~[r15+0x600]+[r15+0x608] -> [rbp+0x1178] [V]. Fifth vcall flag 0x4A [V]. Fast path: call 0xEEC6EC0(rcx=[r15+8], rdx=r12, r8=0xC8), add [r15+8] by 0xC8 [V]. Slow path: call 0x5ABA6D0(r15, r12) then fall through [V]. Sixth vcall flag 0x4A [V]. Destroy geometry: call 0x67E1660([rbp+0x1440]), 0x67E1660([rbp+0xF70]), then jmp exit 0x66F26C0 [V].

## NEXT
Next line to do: 1481 (phase 3 of 17 complete)

### lines 1481..1520
```asm
0x66f11e3  xor eax,eax
0x66f11e5  mov rcx,[rcx+0x20]
0x66f11e9  mov [rbp+0x1410],rcx
0x66f11f0  mov [rbp+0x1418],rax
0x66f11f7  lea rax,[rbp+0x1660]
0x66f11fe  mov [rsp+0x38],rax
0x66f1203  lea rax,[rbp+0x1410]
0x66f120a  mov [rsp+0x30],rax
0x66f120f  mov eax,[rbp+0x1688]
0x66f1215  mov [rsp+0x28],ax
0x66f121a  mov rax,[rbp+0x16C0]
0x66f1221  mov [rsp+0x20],rax
0x66f1226  mov dword ptr [rsp+0x48],0xFFFFFF00
0x66f122e  mov dword ptr [rsp+0x40],0xFFFFFF00
0x66f1236  lea rcx,[rbp+0x12E0]
0x66f123d  lea rdx,[rbp+0x1420]
0x66f1244  movzx r8d,byte ptr [rbp+0x16D0]
0x66f124c  mov r9,0xFFFFFFFFFFFFFFFF
0x66f1253  call 0x673CC80
0x66f1258  movaps [rbp+0x1390],xmm6
0x66f125f  mov rax,[rbp+0x12E8]
0x66f1266  test rax,rax
0x66f1269  je short 0x66F1278
0x66f126b  lock inc dword ptr [rax+8]
0x66f126f  mov rax,[rbp+0x12E8]
0x66f1276  jmp short 0x66F127A
0x66f1278  xor eax,eax
0x66f127a  mov rcx,[rbp+0x12E0]
0x66f1281  mov [rbp+0x1390],rcx
0x66f1288  mov [rbp+0x1398],rax
0x66f128f  lea rdx,[rbp+0x12F0]
0x66f1296  movzx eax,word ptr [rdx+0x10]
0x66f129a  lea rcx,[rbp+0x13A0]
0x66f12a1  mov [rcx+0x10],ax
0x66f12a5  movups xmm0,[rdx]
0x66f12a8  movups [rcx],xmm0
0x66f12ab  movups [rcx+0x18],xmm6
0x66f12af  mov rax,[rbp+0x1310]
0x66f12b6  test rax,rax
0x66f12b9  je short 0x66F12C8
0x66f12bb  lock inc dword ptr [rax+8]
0x66f12bf  mov rax,[rbp+0x1310]
0x66f12c6  jmp short 0x66F12CA
0x66f12c8  xor eax,eax
0x66f12ca  mov rcx,[rbp+0x1308]
0x66f12d1  mov [rbp+0x13B8],rcx
0x66f12d8  mov [rbp+0x13C0],rax
0x66f12df  lea rax,[rbp+0x13A0]
0x66f12e6  movups [rax+0x28],xmm6
0x66f12ea  mov rax,[rbp+0x1320]
0x66f12f1  test rax,rax
0x66f12f4  je short 0x66F1303
0x66f12f6  lock inc dword ptr [rax+8]
0x66f12fa  mov rax,[rbp+0x1320]
0x66f1301  jmp short 0x66F1305
0x66f1303  xor eax,eax
0x66f1305  (bad)
```
Meaning: Kind==9/5 fallback (from 0x66EFEE8/0x66EFEF6): [rbp+0x1410]=[rcx+0x20], [rbp+0x1418]=0 [V]. Set up call args: [rsp+0x38]=&[rbp+0x1660], [rsp+0x30]=&[rbp+0x1410], [rsp+0x28]=[rbp+0x1688] ax, [rsp+0x20]=[rbp+0x16C0], [rsp+0x48/0x40]=0xFFFFFF00 [V]. Call 0x673CC80(&[rbp+0x12E0], &[rbp+0x1420], r8d=[rbp+0x16D0], r9=-1) — descriptor init [V]. Shared_ptr copy: if [rbp+0x12E8]!=0 lock inc [rax+8], else rax=0; store [rbp+0x1390]=[rbp+0x12E0], [rbp+0x1398]=rax [V]. Word field [rbp+0x13A0+0x10]=[rdx+0x10] where rdx=&[rbp+0x12F0], copy xmm0=[rdx] to [rcx], zero [rcx+0x18] [V]. More shared_ptr copies for [rbp+0x1310] and [rbp+0x1320] with lock inc [V]. Call 0x6760E60 at (bad) 0x66F1305 — instruction marked (bad) [V].

## NEXT
Next line to do: 1521 (phase 4 of 17 complete)

### lines 1521..1560
```asm
0x66f1306  mov ecx,[rbp+0x1318]
0x66f130c  mov [rbp+0x13C8],rcx
0x66f1313  mov [rbp+0x13D0],rax
0x66f131a  lea rax,[rbp+0x13A0]
0x66f1321  movups [rax+0x38],xmm6
0x66f1325  mov rax,[rbp+0x1330]
0x66f132c  test rax,rax
0x66f132f  je short 0x66F133E
0x66f1331  lock inc dword ptr [rax+8]
0x66f1335  mov r15,[rbp+0x1330]
0x66f133c  jmp short 0x66F1341
0x66f133e  xor r15d,r15d
0x66f1341  mov rax,[rbp+0x1328]
0x66f1348  mov rcx,[rbp+0x1338]
0x66f134f  mov [rbp+0x13D8],rax
0x66f1356  mov [rbp+0x13E0],r15
0x66f135d  mov [rbp+0x13E8],rcx
0x66f1364  lea rcx,[rbp+0xEA8]
0x66f136b  lea rsi,[rbp+0xF70]
0x66f1372  mov rdx,rsi
0x66f1375  call 0x678CF10
0x66f137a  nop
0x66f137b  lea rax,[rbp+0x1390]
0x66f1382  mov [rsp+0x20],rax
0x66f1387  lea rcx,[rbp+0x1440]
0x66f138e  mov rdx,r13
0x66f1391  lea r8,[rbp+0xFF8]
0x66f1398  mov r9,rsi
0x66f139b  call 0x678EF40
0x66f13a0  nop
0x66f13a1  mov eax,[r13+0x68]
0x66f13a5  lea rcx,[rbp+0x15E0]
0x66f13ac  mov [rcx+0x10],eax
0x66f13af  movups xmm0,[r13+0x58]
0x66f13b4  movups [rcx],xmm0
0x66f13b7  movzx eax,byte ptr [rbp+0x10BC]
0x66f13be  mov [rbp+0x15F4],al
0x66f13c4  movups xmm0,[rbp+0x10C0]
0x66f13cb  movups [rbp+0x15F8],xmm0
0x66f13d2  movups xmm0,[r13+0x80]
0x66f13da  movups xmm1,[r13+0x90]
0x66f13e2  movups xmm2,[r13+0x9F]
0x66f13ea  lea rax,[rbp+0x1444]
0x66f13f1  movups [rax+0x1E3],xmm2
0x66f13f8  movups [rax+0x1D4],xmm1
0x66f13ff  movups [rax+0x1C4],xmm0
0x66f1406  movzx eax,word ptr [rbp+0x1100]
0x66f140d  mov [rbp+0x1638],ax
```
Meaning: Finish shared_ptr fields: [rbp+0x13C8]=[rbp+0x1318], [rbp+0x13D0]=rax, zero [rbp+0x13A0+0x38], shared_ptr copy [rbp+0x1330] lock inc -> r15 [V]. Store [rbp+0x13D8]=[rbp+0x1328], [rbp+0x13E0]=r15, [rbp+0x13E8]=[rbp+0x1338] [V]. Call 0x678CF10(&[rbp+0xEA8], rsi=[rbp+0xF70]) binder [V]. Call 0x678EF40(&[rbp+0x1440], r13, &[rbp+0xFF8], rsi) — alternate geometry pack [V]. Staging store [rbp+0x15E0]: [rcx+0x10]=[r13+0x68], [rcx]=[r13+0x58], byte [rbp+0x15F4]=[rbp+0x10BC], [rbp+0x15F8]=[rbp+0x10C0], xmm0/1/2=[r13+0x80/90/9F] -> [rbp+0x1444+0x1C4/0x1D4/0x1E3], word [rbp+0x1638]=[rbp+0x1100] [V]. Callee RVAs: 0x678cf10, 0x678ef40 [V].

## NEXT
Next line to do: 1561 (phase 5 of 17 complete)

### lines 1561..1600
```asm
0x66f1414  mov rax,[rbp+0x16A8]
0x66f141b  mov rcx,[rax+0x10]
0x66f141f  mov eax,0x9D0
0x66f1424  add rcx,rax
0x66f1427  call 0x5ABA5C0
0x66f142c  nop
0x66f142d  mov r12,rax
0x66f1430  movaps [rbp+0x11E0],xmm6
0x66f1437  movaps [rbp+0x11D0],xmm6
0x66f143e  movaps [rbp+0x11C0],xmm6
0x66f1445  movaps [rbp+0x11B0],xmm6
0x66f144c  movaps [rbp+0x11A0],xmm6
0x66f1453  movaps [rbp+0x1190],xmm6
0x66f145a  movaps [rbp+0x1180],xmm6
0x66f1461  movaps [rbp+0x1170],xmm6
0x66f1468  movaps [rbp+0x1160],xmm6
0x66f146f  movaps [rbp+0x1150],xmm6
0x66f1476  movaps [rbp+0x1140],xmm6
0x66f147d  movaps [rbp+0x1130],xmm6
0x66f1484  mov qword ptr [rbp+0x11F0],0
0x66f148f  mov rcx,[0x1233E1B0]
0x66f1496  mov rax,[rcx]
0x66f1499  mov rax,[rax+0x10]
0x66f149d  mov dl,0x4A
0x66f149f  call qword ptr [0xF99FFA0]
0x66f14a5  nop
0x66f14a6  mov [rbp+0x16D4],al
0x66f14ac  mov rdx,[r12+0x8A8]
0x66f14b4  cmp rdx,[r12+0x8B0]
0x66f14bc  je short 0x66F14D3
0x66f14be  movzx eax,word ptr [rbp+0x1638]
0x66f14c5  mov [rdx],ax
0x66f14c8  add qword ptr [r12+0x8A8],2
0x66f14d1  jmp short 0x66F14E8
0x66f14d3  lea rcx,[r12+0x8A0]
0x66f14db  lea r8,[rbp+0x1638]
0x66f14e2  call 0x1EF6F90
0x66f14e7  nop
0x66f14e8  mov rcx,[0x1233E1B0]
0x66f14ef  mov rax,[rcx]
0x66f14f2  mov rax,[rax+0x10]
0x66f14f6  movzx edx,byte ptr [rbp+0x16D4]
0x66f14fd  call qword ptr [0xF99FFA0]
0x66f1503  nop
0x66f1504  mov eax,[r12+0x8A8]
0x66f150c  sub eax,[r12+0x8A0]
0x66f1514  shr eax,1
0x66f1516  dec eax
0x66f1518  mov [rbp+0x1140],ax
0x66f151f  mov rcx,[0x1233E1B0]
0x66f1526  mov rax,[rcx]
0x66f1529  mov rax,[rax+0x10]
0x66f152d  mov dl,0x4A
0x66f152f  call qword ptr [0xF99FFA0]
0x66f1535  nop
0x66f1536  mov [rbp+0x16D4],al
```
Meaning: Push u16 [rbp+0x1638] to pass pool [r12+0x8A8] via 0x5ABA5C0(*[rbp+0x16A8]+0x10+0x9D0) -> r12=pass ptr [V], or slow path 0x1EF6F90([r12+0x8A0], &[rbp+0x1638]) [V]. Zero 16 xmm staging slots [rbp+0x1130..0x11F0] [V]. vcall flag 0x4A -> [rbp+0x16D4] [V]. Compute pool index count = ([r12+0x8A8]-[r12+0x8A0])>>1 - 1 -> [rbp+0x1140] [V]. Another vcall flag 0x4A -> [rbp+0x16D4] [V]. Callee RVAs: 0x5aba5c0, [0xF99FFA0], 0x1ef6f90 [V/I].

### lines 1601..1640
```asm
0x66f153c  mov rdx,[r12+0x758]
0x66f1544  cmp rdx,[r12+0x760]
0x66f154c  je 0x66F15D6
0x66f1552  lea rcx,[rbp+0x15E0]
0x66f1559  mov eax,[rcx+0x10]
0x66f155c  mov [rdx+0x10],eax
0x66f155f  movups xmm0,[rcx]
0x66f1562  movups [rdx],xmm0
0x66f1565  movzx eax,byte ptr [rbp+0x15F4]
0x66f156c  mov [rdx+0x14],al
0x66f156f  movss xmm0,[rbp+0x15F8]
0x66f1577  movss [rdx+0x18],xmm0
0x66f157c  movss xmm0,[rbp+0x15FC]
0x66f1584  movss [rdx+0x1C],xmm0
0x66f1589  movss xmm0,[rbp+0x1600]
0x66f1591  movss [rdx+0x20],xmm0
0x66f1596  movss xmm0,[rbp+0x1604]
0x66f159e  movss [rdx+0x24],xmm0
0x66f15a3  lea rax,[rbp+0x1444]
0x66f15aa  movups xmm0,[rax+0x1C4]
0x66f15b1  movups xmm1,[rax+0x1D4]
0x66f15b8  movups xmm2,[rax+0x1E3]
0x66f15bf  movups [rdx+0x28],xmm0
0x66f15c3  movups [rdx+0x38],xmm1
0x66f15c7  movups [rdx+0x47],xmm2
0x66f15cb  add qword ptr [r12+0x758],0x58
0x66f15d4  jmp short 0x66F15EB
0x66f15d6  lea rcx,[r12+0x750]
0x66f15de  lea r8,[rbp+0x15E0]
0x66f15e5  call 0x6760A80
0x66f15ea  nop
0x66f15eb  mov rcx,[0x1233E1B0]
0x66f15f2  mov rax,[rcx]
0x66f15f5  mov rax,[rax+0x10]
0x66f15f9  movzx edx,byte ptr [rbp+0x16D4]
0x66f1600  call qword ptr [0xF99FFA0]
0x66f1606  nop
0x66f1607  mov qword ptr [rbp+0x1130],0x4001
0x66f1612  mov eax,[r12+0x758]
0x66f161a  sub eax,[r12+0x750]
0x66f1622  shr eax,3
0x66f1625  imul eax,0xFFFF8BA3
0x66f162b  dec eax
0x66f162d  mov [rbp+0x115C],ax
0x66f1634  mov rcx,[0x1233E1B0]
0x66f163b  mov rax,[rcx]
0x66f163e  mov rax,[rax+0x10]
0x66f1642  mov dl,0x4A
0x66f1644  call qword ptr [0xF99FFA0]
0x66f164a  nop
0x66f164b  mov [rbp+0x16D4],al
```
Meaning: Fast path: store staging [rbp+0x15E0] to pool entry [rdx+0x10/0x14/0x18/0x1C/0x20/0x24] and xmm [rdx+0x28/0x38/0x47] from [rbp+0x1444+0x1C4/0x1D4/0x1E3], advance [r12+0x758] by 0x58 [V]. Slow path: call 0x6760A80(&[r12+0x750], &[rbp+0x15E0]) then fall through [V]. vcall flag 0x4A -> [rbp+0x16D4] [V]. Tag [rbp+0x1130]=0x4001, compute count = ([r12+0x758]-[r12+0x750])>>3 via magic 0xFFFF8BA3 -> [rbp+0x115C] [V]. Another vcall flag 0x4A -> [rbp+0x16D4] [V]. Callee RVAs: 0x6760a80, [0xF99FFA0] [V].

## NEXT
Next line to do: 1641 (phase 8 of 17 complete)

### lines 1641..1680
```asm
0x66f1651  mov rdx,[r12+0x890]
0x66f1659  cmp rdx,[r12+0x898]
0x66f1661  je short 0x66F1670
0x66f1663  inc rdx
0x66f1666  mov [r12+0x890],rdx
0x66f166e  jmp short 0x66F167E
0x66f1670  lea rcx,[r12+0x888]
0x66f1678  call 0x6760E60
0x66f167d  nop
0x66f167e  mov rcx,[0x1233E1B0]
0x66f1685  mov rax,[rcx]
0x66f1688  mov rax,[rax+0x10]
0x66f168c  movzx edx,byte ptr [rbp+0x16D4]
0x66f1693  call qword ptr [0xF99FFA0]
0x66f1699  nop
0x66f169a  mov eax,[r12+0x888]
0x66f16a2  not eax
0x66f16a4  add eax,[r12+0x890]
0x66f16ac  mov [rbp+0x1142],ax
0x66f16b3  mov rcx,[0x1233E1B0]
0x66f16ba  mov rax,[rcx]
0x66f16bd  mov rax,[rax+0x10]
0x66f16c1  mov dl,0x4A
0x66f16c3  call qword ptr [0xF99FFA0]
0x66f16c9  nop
0x66f16ca  mov [rbp+0x16D4],al
0x66f16d0  mov rdx,[r12+0x7A0]
0x66f16d8  cmp rdx,[r12+0x7A8]
0x66f16e0  je short 0x66F16EF
0x66f16e2  inc rdx
0x66f16e5  mov [r12+0x7A0],rdx
0x66f16ed  jmp short 0x66F16FD
0x66f16ef  lea rcx,[r12+0x798]
0x66f16f7  call 0x6760E60
0x66f16fc  nop
0x66f16fd  mov rcx,[0x1233E1B0]
0x66f1704  mov rax,[rcx]
0x66f1707  mov rax,[rax+0x10]
0x66f170b  movzx edx,byte ptr [rbp+0x16D4]
0x66f1712  call qword ptr [0xF99FFA0]
0x66f1718  nop
0x66f1719  mov eax,[r12+0x798]
0x66f1721  not eax
0x66f1723  add eax,[r12+0x7A0]
0x66f172b  mov [rbp+0x1156],ax
0x66f1732  mov rcx,[0x1233E1B0]
0x66f1739  mov rax,[rcx]
0x66f173c  mov rax,[rax+0x10]
0x66f1740  mov dl,0x4A
0x66f1742  call qword ptr [0xF99FFA0]
0x66f1748  nop
0x66f1748  nop
0x66f1748  mov [rbp+0x16D4],al
0x66f174e  lea rcx,[r12+0x648]
0x66f1756  lea rdx,[rbp+0x1588]
0x66f175d  call 0x675FB30
0x66f1762  nop
```
Meaning: vcall flag 0x4A [V]. Fast path: inc [r12+0x890] [V]. Slow path: call 0x6760E60(&[r12+0x888]) then fall through [V]. vcall flag 0x4A [V]. Compute ~[r12+0x888]+[r12+0x890] -> [rbp+0x1142] [V]. Another vcall flag 0x4A [V]. Fast path: inc [r12+0x7A0] [V]. Slow path: call 0x6760E60(&[r12+0x798]) then fall through [V]. vcall flag 0x4A [V]. Compute ~[r12+0x798]+[r12+0x7A0] -> [rbp+0x1156] [V]. Another vcall flag 0x4A -> [rbp+0x16D4] [V]. Call 0x675FB30(&[r12+0x648], &[rbp+0x1588]) [V]. Callee RVAs: 0x6760e60, [0xF99FFA0], 0x675fb30 [V].

## NEXT
Next line to do: 1681 (phase 9 of 17 complete)

### lines 1681..1720
```asm
0x66f1763  mov rcx,[0x1233E1B0]
0x66f176a  mov rax,[rcx]
0x66f176d  mov rax,[rax+0x10]
0x66f1771  movzx edx,byte ptr [rbp+0x16D4]
0x66f1778  call qword ptr [0xF99FFA0]
0x66f177e  nop
0x66f177f  mov eax,[r12+0x650]
0x66f1787  sub eax,[r12+0x648]
0x66f178f  shr eax,3
0x66f1792  imul eax,0xFFFF8E39
0x66f1798  dec eax
0x66f179a  mov [rbp+0x1172],ax
0x66f17a1  lea rcx,[r12+0x780]
0x66f17a9  lea rdx,[rbp+0x1530]
0x66f17b0  call 0x675F3B0
0x66f17b5  nop
0x66f17b6  mov qword ptr [rbp+0x1130],0x2005803
0x66f17c1  mov eax,[r12+0x788]
0x66f17c9  sub eax,[r12+0x780]
0x66f17d1  shr eax,3
0x66f17d4  imul eax,0xFFFF8BA3
0x66f17da  dec eax
0x66f17dc  mov [rbp+0x1158],ax
0x66f17e3  mov rcx,[0x1233E1B0]
0x66f17ea  mov rax,[rcx]
0x66f17ed  mov rax,[rax+0x10]
0x66f17f1  mov dl,0x4A
0x66f17f3  call qword ptr [0xF99FFA0]
0x66f17f9  nop
0x66f17fa  mov [rbp+0x16D4],al
0x66f1800  mov rbx,[r12+0x770]
0x66f1808  cmp rbx,[r12+0x778]
0x66f1810  je short 0x66F1854
0x66f1812  mov rax,[rbp+0x14A8]
0x66f1819  mov [rbx],rax
0x66f181c  lea rcx,[rbx+8]
0x66f1820  lea rdx,[rbp+0x14B0]
0x66f1827  call 0xE869FF0
0x66f182c  nop
0x66f182d  mov rax,[rbp+0x1528]
0x66f1834  mov [rbx+0x80],rax
0x66f183b  mov qword ptr [rbp+0x1528],0
0x66f1846  add qword ptr [r12+0x770],0x88
0x66f1852  jmp short 0x66F186C
0x66f1854  lea rcx,[r12+0x768]
0x66f185c  mov rdx,rbx
0x66f185f  lea r8,[rbp+0x14A8]
0x66f1866  call 0x6760710
0x66f186b  nop
0x66f186c  mov rcx,[0x1233E1B0]
0x66f1873  mov rax,[rcx]
0x66f1876  mov rax,[rax+0x10]
0x66f187a  movzx edx,byte ptr [rbp+0x16D4]
0x66f1881  call qword ptr [0xF99FFA0]
0x66f1887  nop
0x66f1888  mov eax,[r12+0x770]
0x66f1890  sub eax,[r12+0x768]
0x66f1898  shr eax,3
0x66f189b  imul eax,0xFFFFF0F1
0x66f18a1  dec eax
0x66f18a3  mov [rbp+0x115A],ax
```
Meaning: vcall flag 0x4A -> [rbp+0x16D4] [V]. Compute ([r12+0x650]-[r12+0x648])>>3 via magic 0xFFFF8E39 -> [rbp+0x1172] [V]. Call 0x675F3B0(&[r12+0x780], &[rbp+0x1530]) [V]. Tag [rbp+0x1130]=0x2005803, compute ([r12+0x788]-[r12+0x780])>>3 via magic 0xFFFF8BA3 -> [rbp+0x1158] [V]. vcall flag 0x4A -> [rbp+0x16D4] [V]. Fast path: store [rax]=[rbp+0x14A8] at [rbx], call 0xE869FF0(rcx=[rbx+8], rdx=&[rbp+0x14B0]), store [rbx+0x80]=[rbp+0x1528], clear [rbp+0x1528]=0, advance [r12+0x770] by 0x88 [V]. Slow path: call 0x6760710(&[r12+0x768], rbx, &[rbp+0x14A8]) then fall through [V]. vcall flag 0x4A [V]. Compute count = ([r12+0x770]-[r12+0x768])>>3 via magic 0xFFFFF0F1 -> [rbp+0x115A] [V]. Callee RVAs: 0x675f3b0, 0xe869ff0, 0x6760710, [0xF99FFA0] [V].

## NEXT
Next line to do: 1721 (phase 10 of 17 complete)

### lines 1721..1760
```asm
0x66f18aa  mov rcx,[0x1233E1B0]
0x66f18b1  mov rax,[rcx]
0x66f18b4  mov rax,[rax+0x10]
0x66f18b8  mov dl,0x4A
0x66f18ba  call qword ptr [0xF99FFA0]
0x66f18c0  nop
0x66f18c1  mov [rbp+0x16D4],al
0x66f18c7  mov rdx,[r12+0x2D8]
0x66f18cf  cmp rdx,[r12+0x2E0]
0x66f18d7  je short 0x66F18E6
0x66f18d9  inc rdx
0x66f18dc  mov [r12+0x2D8],rdx
0x66f18e4  jmp short 0x66F18F4
0x66f18e6  lea rcx,[r12+0x2D0]
0x66f18ee  call 0x6760E60
0x66f18f3  nop
0x66f18f4  mov rcx,[0x1233E1B0]
0x66f18fb  mov rax,[rcx]
0x66f18fe  mov rax,[rax+0x10]
0x66f1902  movzx edx,byte ptr [rbp+0x16D4]
0x66f1909  call qword ptr [0xF99FFA0]
0x66f190f  nop
0x66f1910  mov eax,[r12+0x2D0]
0x66f1918  not eax
0x66f191a  add eax,[r12+0x2D8]
0x66f1922  mov [rbp+0x11BC],ax
0x66f1929  mov rcx,r12
0x66f192c  add rcx,0x5D0
0x66f1933  lea rdx,[rbp+0x1440]
0x66f193a  call 0x678D690
0x66f193f  nop
0x66f1940  mov rax,0x4000000042007803
0x66f194a  mov [rbp+0x1130],rax
0x66f1951  mov eax,[r12+0x5D8]
0x66f1959  sub eax,[r12+0x5D0]
0x66f1961  shr eax,5
0x66f1964  imul eax,0xFFFFAAAB
0x66f196a  dec eax
0x66f196c  mov [rbp+0x117C],ax
0x66f1973  mov rcx,[0x1233E1B0]
0x66f197a  mov rax,[rcx]
0x66f197d  mov rax,[rax+0x10]
0x66f1981  mov dl,0x4A
0x66f1983  call qword ptr [0xF99FFA0]
0x66f1989  nop
0x66f198a  mov [rbp+0x16D4],al
0x66f1990  mov rdx,[r12+8]
0x66f1995  cmp rdx,[r12+0x10]
0x66f199a  je short 0x66F19BC
0x66f199c  mov r8d,0xC8
0x66f19a2  mov rcx,rdx
0x66f19a5  lea rdx,[rbp+0x1130]
0x66f19ac  call 0xEEC6EC0
0x66f19b1  add qword ptr [r12+8],0xC8
0x66f19ba  jmp short 0x66F19CC
0x66f19bc  mov rcx,r12
0x66f19bf  lea r8,[rbp+0x1130]
0x66f19c6  call 0x5ABA6D0
0x66f19cb  nop
0x66f19cc  mov rcx,[0x1233E1B0]
0x66f19d3  mov rax,[rcx]
0x66f19d6  mov rax,[rax+0x10]
0x66f19da  movzx edx,byte ptr [rbp+0x16D4]
0x66f19e1  call qword ptr [0xF99FFA0]
0x66f19e7  nop
0x66f19e8  cmp byte ptr [rbp+0x15C8],1
0x66f19ef  lea r12,[rbp+0x1130]
0x66f19f6  jne short 0x66F1A4A
0x66f19f8  mov rcx,[rbp+0x1588]
0x66f19ff  test rcx,rcx
0x66f1a02  je short 0x66F1A4A
0x66f1a04  mov rdx,[rbp+0x1598]
0x66f1a0b  sub rdx,rcx
0x66f1a0e  cmp rdx,0x1000
0x66f1a15  jb short 0x66F1A33
0x66f1a17  mov rax,[rcx-8]
0x66f1a1b  add rcx,0xFFFFFFFFFFFFFFF8
0x66f1a1f  sub rcx,rax
0x66f1a22  cmp rcx,0x20
0x66f1a26  jae 0x66F82BB
0x66f1a2c  or rdx,0x27
0x66f1a30  mov rcx,rax
0x66f1a33  call 0xE935700
0x66f1a38  lea rax,[rbp+0x1588]
0x66f1a3f  movups [rax],xmm6
0x66f1a42  mov qword ptr [rax+0x10],0
0x66f1a4a  lea rcx,[rbp+0x1440]
0x66f1a51  call 0x678F260
0x66f1a56  lea rcx,[rbp+0xF70]
0x66f1a5d  call 0x67E23F0
0x66f1a62  test r15,r15
0x66f1a65  je short 0x66F1AA0
0x66f1a67  lock dec dword ptr [r15+8]
0x66f1a6c  jne short 0x66F1AA0
0x66f1a6e  mov rax,[r15]
0x66f1a71  mov rax,[rax]
0x66f1a74  mov rcx,r15
0x66f1a77  call qword ptr [0xF99FFA0]
0x66f1a7d  lock dec dword ptr [r15+0xC]
0x66f1a82  jne short 0x66F1AA0
0x66f1a84  mov rax,[r15]
0x66f1a87  mov rax,[rax+8]
0x66f1a8b  mov rcx,r15
0x66f1a8e  call qword ptr [0xF99FFA0]
0x66f1a94  nop [rax+rax]
```
Meaning: vcall flag 0x4A -> [rbp+0x16D4] [V]. Fast path: inc [r12+0x2D8] [V]. Slow path: call 0x6760E60(&[r12+0x2D0]) then fall through [V]. vcall flag 0x4A [V]. Compute ~[r12+0x2D0]+[r12+0x2D8] -> [rbp+0x11BC] [V]. Call 0x678D690(rcx=r12+0x5D0, rdx=&[rbp+0x1440]) — descriptor write [V]. Tag [rbp+0x1130]=0x4000000042007803, compute ([r12+0x5D8]-[r12+0x5D0])>>5 via magic 0xFFFFAAAB - 1 -> [rbp+0x117C] [V]. vcall flag 0x4A [V]. Fast path: call 0xEEC6EC0(rcx=[r12+8], rdx=&[rbp+0x1130], r8=0xC8), add [r12+8] by 0xC8 [V]. Slow path: call 0x5ABA6D0(r12, &[rbp+0x1130]) then fall through [V]. vcall flag 0x4A [V]. If [rbp+0x15C8]==1 and [rbp+0x1588]!=0: compute free space [rbp+0x1598]-[rbp+0x1588], if >=0x1000 do heap-free via 0xE935700 (with size checks) else or rdx,0x27 and free [V]. Zero [rbp+0x1588] (xmm6) and [rax+0x10]=0 [V]. Call 0x678F260([rbp+0x1440]) then 0x67E23F0([rbp+0xF70]) destroy [V]. Shared_ptr release of r15: lock dec [r15+8], if 0 call dtor via [0xF99FFA0], lock dec [r15+0xC], if 0 call dtor2 via [0xF99FFA0] [V]. Callee RVAs: 0x678d690, 0xeec6ec0, 0x5aba6d0, 0xe935700, 0x678f260, 0x67e23f0, [0xF99FFA0] [V].

### lines 1761..1800
```asm
0x66f1aa0  mov rbx,[rbp+0x13D0]
0x66f1aa7  test rbx,rbx
0x66f1aaa  je short 0x66F1AE0
0x66f1aac  lock dec dword ptr [rbx+8]
0x66f1ab0  jne short 0x66F1AE0
0x66f1ab2  mov rax,[rbx]
0x66f1ab5  mov rax,[rax]
0x66f1ab8  mov rcx,rbx
0x66f1abb  call qword ptr [0xF99FFA0]
0x66f1ac1  lock dec dword ptr [rbx+0xC]
0x66f1ac5  jne short 0x66F1AE0
0x66f1ac7  mov rax,[rbx]
0x66f1aca  mov rax,[rax+8]
0x66f1ace  mov rcx,rbx
0x66f1ad1  call qword ptr [0xF99FFA0]
0x66f1ad7  nop [rax+rax]
0x66f1ae0  mov rbx,[rbp+0x13C0]
0x66f1ae7  test rbx,rbx
0x66f1aea  je short 0x66F1B20
0x66f1aec  lock dec dword ptr [rbx+8]
0x66f1af0  jne short 0x66F1B20
0x66f1af2  mov rax,[rbx]
0x66f1af5  mov rax,[rax]
0x66f1af8  mov rcx,rbx
0x66f1afb  call qword ptr [0xF99FFA0]
0x66f1b01  lock dec dword ptr [rbx+0xC]
0x66f1b05  jne short 0x66F1B20
0x66f1b07  mov rax,[rbx]
0x66f1b0a  mov rax,[rax+8]
0x66f1b0e  mov rcx,rbx
0x66f1b11  call qword ptr [0xF99FFA0]
0x66f1b17  nop [rax+rax]
0x66f1b20  mov rbx,[rbp+0x1398]
0x66f1b27  test rbx,rbx
0x66f1b2a  je short 0x66F1B60
0x66f1b2c  lock dec dword ptr [rbx+8]
0x66f1b30  jne short 0x66F1B60
0x66f1b32  mov rax,[rbx]
0x66f1b35  mov rax,[rax]
0x66f1b38  mov rcx,rbx
0x66f1b3b  call qword ptr [0xF99FFA0]
0x66f1b41  lock dec dword ptr [rbx+0xC]
0x66f1b45  jne short 0x66F1B60
0x66f1b47  mov rax,[rbx]
0x66f1b4a  mov rax,[rax+8]
0x66f1b4e  mov rcx,rbx
0x66f1b51  call qword ptr [0xF99FFA0]
0x66f1b57  nop [rax+rax]
0x66f1b60  mov rbx,[rbp+0x1330]
0x66f1b67  test rbx,rbx
0x66f1b6a  je short 0x66F1BA0
0x66f1b6c  lock dec dword ptr [rbx+8]
0x66f1b70  jne short 0x66F1BA0
0x66f1b72  mov rax,[rbx]
0x66f1b75  mov rax,[rax]
0x66f1b78  mov rcx,rbx
0x66f1b7b  call qword ptr [0xF99FFA0]
0x66f1b81  lock dec dword ptr [rbx+0xC]
0x66f1b85  jne short 0x66F1BA0
0x66f1b87  mov rax,[rbx]
0x66f1b8a  mov rax,[rax+8]
0x66f1b8e  mov rcx,rbx
0x66f1b91  call qword ptr [0xF99FFA0]
0x66f1b97  nop [rax+rax]
0x66f1ba0  mov rbx,[rbp+0x1320]
0x66f1ba7  test rbx,rbx
0x66f1baa  je short 0x66F1BE0
0x66f1bac  lock dec dword ptr [rbx+8]
0x66f1bb0  jne short 0x66F1BE0
0x66f1bb2  mov rax,[rbx]
0x66f1bb5  mov rax,[rax]
0x66f1bb8  mov rcx,rbx
0x66f1bbb  call qword ptr [0xF99FFA0]
0x66f1bc1  lock dec dword ptr [rbx+0xC]
0x66f1bc5  jne short 0x66F1BE0
0x66f1bc7  mov rax,[rbx]
0x66f1bca  mov rax,[rax+8]
0x66f1bce  mov rcx,rbx
0x66f1bd1  call qword ptr [0xF99FFA0]
0x66f1bd7  nop [rax+rax]
0x66f1be0  mov rbx,[rbp+0x1310]
0x66f1be7  test rbx,rbx
0x66f1bea  je short 0x66F1C20
0x66f1bec  lock dec dword ptr [rbx+8]
0x66f1bf0  jne short 0x66F1C20
0x66f1bf2  mov rax,[rbx]
0x66f1bf5  mov rax,[rax]
0x66f1bf8  mov rcx,rbx
0x66f1bfb  call qword ptr [0xF99FFA0]
0x66f1c01  lock dec dword ptr [rbx+0xC]
0x66f1c05  jne short 0x66F1C20
0x66f1c07  mov rax,[rbx]
0x66f1c0a  mov rax,[rax+8]
0x66f1c0e  mov rcx,rbx
0x66f1c11  call qword ptr [0xF99FFA0]
0x66f1c17  nop [rax+rax]
0x66f1c20  mov rbx,[rbp+0x12E8]
0x66f1c27  test rbx,rbx
0x66f1c2a  je short 0x66F1C60
0x66f1c2c  lock dec dword ptr [rbx+8]
0x66f1c30  jne short 0x66F1C60
```
Meaning: Shared_ptr release cascade: for each of [rbp+0x13D0], [rbp+0x13C0], [rbp+0x1398], [rbp+0x1330], [rbp+0x1320], [rbp+0x1310], [rbp+0x12E8]: test null -> skip; lock dec [+8], if nonzero skip; load vtable, call dtor via qword [0xF99FFA0](this); lock dec [+0xC], if nonzero skip; call dtor2 via qword [0xF99FFA0](this+8) [V]. Each release follows identical pattern [V]. Callee RVA: [0xF99FFA0] [V].

## NEXT
Next line to do: 1801 (phase 13 of 17 complete)

### lines 1801..1840
```asm
0x66f1c32  mov rax,[rbx]
0x66f1c35  mov rax,[rax]
0x66f1c38  mov rcx,rbx
0x66f1c3b  call qword ptr [0xF99FFA0]
0x66f1c41  lock dec dword ptr [rbx+0xC]
0x66f1c47  jne short 0x66F1C60
0x66f1c49  mov rax,[rbx]
0x66f1c4c  mov rax,[rax+8]
0x66f1c50  mov rcx,rbx
0x66f1c53  call qword ptr [0xF99FFA0]
0x66f1c59  nop [rax+rax]
0x66f1c5a  jmp 0x66F1CA0
0x66f1c60  mov rbx,[rbp+0x13D0]
0x66f1c67  test rbx,rbx
0x66f1c6a  je short 0x66F1CA0
0x66f1c6c  lock dec dword ptr [rbx+8]
0x66f1c70  jne short 0x66F1CA0
0x66f1c72  mov rax,[rbx]
0x66f1c75  mov rax,[rax]
0x66f1c78  mov rcx,rbx
0x66f1c7b  call qword ptr [0xF99FFA0]
0x66f1c81  lock dec dword ptr [rbx+0xC]
0x66f1c87  jne short 0x66F1CA0
0x66f1c89  mov rax,[rbx]
0x66f1c8c  mov rax,[rax+8]
0x66f1c8f  mov rcx,rbx
0x66f1c92  call qword ptr [0xF99FFA0]
0x66f1c99  nop [rax+rax]
0x66f1c9a  jmp 0x66F1CA0
0x66f1c9f  nop [rax+rax]
0x66f1ca0  mov rbx,[rbp+0x13C0]
0x66f1ca7  test rbx,rbx
0x66f1caa  je short 0x66F1D20
0x66f1cac  lock dec dword ptr [rbx+8]
0x66f1cb0  jne short 0x66F1D20
0x66f1cb2  mov rax,[rbx]
0x66f1cb5  mov rax,[rax]
0x66f1cb8  mov rcx,rbx
0x66f1cbb  call qword ptr [0xF99FFA0]
0x66f1cc1  lock dec dword ptr [rbx+0xC]
0x66f1cc7  jne short 0x66F1D20
0x66f1cc9  mov rax,[rbx]
0x66f1ccc  mov rax,[rax+8]
0x66f1cd0  mov rcx,rbx
0x66f1cd3  call qword ptr [0xF99FFA0]
0x66f1cd9  nop [rax+rax]
0x66f1cda  jmp 0x66F1D20
0x66f1cdf  nop [rax+rax]
0x66f1ce0  mov rbx,[rbp+0x1398]
0x66f1ce7  test rbx,rbx
0x66f1cea  je short 0x66F1D20
0x66f1cec  lock dec dword ptr [rbx+8]
0x66f1cf0  jne short 0x66F1D20
0x66f1cf2  mov rax,[rbx]
0x66f1cf5  mov rax,[rax]
0x66f1cf8  mov rcx,rbx
0x66f1cfb  call qword ptr [0xF99FFA0]
0x66f1d01  lock dec dword ptr [rbx+0xC]
0x66f1d07  jne short 0x66F1D20
0x66f1d09  mov rax,[rbx]
0x66f1d0c  mov rax,[rax+8]
0x66f1d0f  mov rcx,rbx
0x66f1d12  call qword ptr [0xF99FFA0]
0x66f1d18  nop [rax+rax]
0x66f1d1a  jmp 0x66F1D20
0x66f1d1f  nop [rax+rax]
0x66f1d20  mov rbx,[rbp+0x1330]
0x66f1d27  test rbx,rbx
0x66f1d2a  je short 0x66F1D60
0x66f1d2c  lock dec dword ptr [rbx+8]
0x66f1d30  jne short 0x66F1D60
0x66f1d32  mov rax,[rbx]
0x66f1d35  mov rax,[rax]
0x66f1d38  mov rcx,rbx
0x66f1d3b  call qword ptr [0xF99FFA0]
0x66f1d41  lock dec dword ptr [rbx+0xC]
0x66f1d47  jne short 0x66F1D60
0x66f1d49  mov rax,[rbx]
0x66f1d4c  mov rax,[rax+8]
0x66f1d4f  mov rcx,rbx
0x66f1d52  call qword ptr [0xF99FFA0]
0x66f1d59  nop [rax+rax]
0x66f1d5a  jmp 0x66F1D60
0x66f1d5f  nop [rax+rax]
0x66f1d60  mov rbx,[rbp+0x1320]
0x66f1d67  test rbx,rbx
0x66f1d6a  je short 0x66F1DA0
0x66f1d6c  lock dec dword ptr [rbx+8]
0x66f1d70  jne short 0x66F1DA0
0x66f1d72  mov rax,[rbx]
0x66f1d75  mov rax,[rax]
0x66f1d78  mov rcx,rbx
0x66f1d7b  call qword ptr [0xF99FFA0]
0x66f1d81  lock dec dword ptr [rbx+0xC]
0x66f1d87  jne short 0x66F1DA0
0x66f1d89  mov rax,[rbx]
0x66f1d8c  mov rax,[rax+8]
0x66f1d8f  mov rcx,rbx
0x66f1d92  call qword ptr [0xF99FFA0]
0x66f1d99  nop [rax+rax]
0x66f1d9a  jmp 0x66F1DA0
0x66f1d9f  nop [rax+rax]
```
Meaning: Continued shared_ptr release cascade for [rbp+0x12E8] (from phase 12): dtor via [0xF99FFA0](this), dtor2 via [0xF99FFA0](this+8), then jmp 0x66F1CA0 [V]. Same pattern for [rbp+0x13D0] (jmp 0x66F1CA0), then [rbp+0x13C0] (jmp 0x66F1D20), [rbp+0x1398] (jmp 0x66F1D20), [rbp+0x1330] (jmp 0x66F1D60), [rbp+0x1320] (jmp 0x66F1DA0) [V]. Each uses identical lock-dec + dual-vtable-destructor pattern via qword [0xF99FFA0] [V]. Callee RVA: [0xF99FFA0] [V].

## NEXT
Next line to do: 1841 (phase 14 of 17 complete)

### lines 1841..1880
```asm
0x66f1da0  mov rbx,[rbp+0x1310]
0x66f1da7  test rbx,rbx
0x66f1daa  je short 0x66F1DE0
0x66f1dac  lock dec dword ptr [rbx+8]
0x66f1db0  jne short 0x66F1DE0
0x66f1db2  mov rax,[rbx]
0x66f1db5  mov rax,[rax]
0x66f1db8  mov rcx,rbx
0x66f1dbb  call qword ptr [0xF99FFA0]
0x66f1dc1  lock dec dword ptr [rbx+0xC]
0x66f1dc7  jne short 0x66F1DE0
0x66f1dc9  mov rax,[rbx]
0x66f1dcc  mov rax,[rax+8]
0x66f1dcf  mov rcx,rbx
0x66f1dd2  call qword ptr [0xF99FFA0]
0x66f1dd8  nop [rax+rax]
0x66f1dd9  jmp 0x66F1DE0
0x66f1dde  nop [rax+rax]
0x66f1de0  mov rbx,[rbp+0x12E8]
0x66f1de7  test rbx,rbx
0x66f1dea  je short 0x66F1E20
0x66f1dec  lock dec dword ptr [rbx+8]
0x66f1df0  jne short 0x66F1E20
0x66f1df2  mov rax,[rbx]
0x66f1df5  mov rax,[rax]
0x66f1df8  mov rcx,rbx
0x66f1dfb  call qword ptr [0xF99FFA0]
0x66f1e01  lock dec dword ptr [rbx+0xC]
0x66f1e07  jne short 0x66F1E20
0x66f1e09  mov rax,[rbx]
0x66f1e0c  mov rax,[rax+8]
0x66f1e0f  mov rcx,rbx
0x66f1e12  call qword ptr [0xF99FFA0]
0x66f1e18  nop [rax+rax]
0x66f1e19  jmp 0x66F1E20
0x66f1e1e  nop [rax+rax]
0x66f1e20  mov rbx,[rbp+0x13D0]
0x66f1e27  test rbx,rbx
0x66f1e2a  je short 0x66F1EA0
0x66f1e2c  lock dec dword ptr [rbx+8]
0x66f1e30  jne short 0x66F1EA0
0x66f1e32  mov rax,[rbx]
0x66f1e35  mov rax,[rax]
0x66f1e38  mov rcx,rbx
0x66f1e3b  call qword ptr [0xF99FFA0]
0x66f1e41  lock dec dword ptr [rbx+0xC]
0x66f1e47  jne short 0x66F1EA0
0x66f1e49  mov rax,[rbx]
0x66f1e4c  mov rax,[rax+8]
0x66f1e4f  mov rcx,rbx
0x66f1e52  call qword ptr [0xF99FFA0]
0x66f1e58  nop [rax+rax]
0x66f1e59  jmp 0x66F1EA0
0x66f1e5e  nop [rax+rax]
0x66f1e60  mov rbx,[rbp+0x13C0]
0x66f1e67  test rbx,rbx
0x66f1e6a  je short 0x66F1F20
0x66f1e6c  lock dec dword ptr [rbx+8]
0x66f1e70  jne short 0x66F1F20
0x66f1e72  mov rax,[rbx]
0x66f1e75  mov rax,[rax]
0x66f1e78  mov rcx,rbx
0x66f1e7b  call qword ptr [0xF99FFA0]
0x66f1e81  lock dec dword ptr [rbx+0xC]
0x66f1e87  jne short 0x66F1F20
0x66f1e89  mov rax,[rbx]
0x66f1e8c  mov rax,[rax+8]
0x66f1e8f  mov rcx,rbx
0x66f1e92  call qword ptr [0xF99FFA0]
0x66f1e99  nop [rax+rax]
0x66f1e9a  jmp 0x66F1F20
0x66f1e9f  nop [rax+rax]
0x66f1ea0  mov rbx,[rbp+0x1398]
0x66f1ea7  test rbx,rbx
0x66f1eaa  je short 0x66F1F20
0x66f1eac  lock dec dword ptr [rbx+8]
0x66f1eb0  jne short 0x66F1F20
0x66f1eb2  mov rax,[rbx]
0x66f1eb5  mov rax,[rax]
0x66f1eb8  mov rcx,rbx
0x66f1ebb  call qword ptr [0xF99FFA0]
0x66f1ec1  lock dec dword ptr [rbx+0xC]
0x66f1ec7  jne short 0x66F1F20
0x66f1ec9  mov rax,[rbx]
0x66f1ecc  mov rax,[rax+8]
0x66f1ecf  mov rcx,rbx
0x66f1ed2  call qword ptr [0xF99FFA0]
0x66f1ed8  nop [rax+rax]
0x66f1ed9  jmp 0x66F1F20
0x66f1ede  nop [rax+rax]
```
Meaning: Final shared_ptr releases: [rbp+0x1310] (jmp 0x66F1DE0), [rbp+0x12E8] (jmp 0x66F1E20), [rbp+0x13D0] (jmp 0x66F1EA0), [rbp+0x13C0] (jmp 0x66F1F20), [rbp+0x1398] (jmp 0x66F1F20) [V]. Every release: test null -> skip; lock dec [+8]; if zero: call dtor via qword [0xF99FFA0](this); lock dec [+0xC]; if zero: call dtor2 via qword [0xF99FFA0](this+8); nop padding [V]. Callee RVA: [0xF99FFA0] [V].

## NEXT
Next line to do: 1881 (phase 15 of 17 complete)

### lines 1881..1920
```asm
0x66f1f20  mov rbx,[rbp+0x1330]
0x66f1f27  test rbx,rbx
0x66f1f2a  je short 0x66F1F60
0x66f1f2c  lock dec dword ptr [rbx+8]
0x66f1f30  jne short 0x66F1F60
0x66f1f32  mov rax,[rbx]
0x66f1f35  mov rax,[rax]
0x66f1f38  mov rcx,rbx
0x66f1f3b  call qword ptr [0xF99FFA0]
0x66f1f41  lock dec dword ptr [rbx+0xC]
0x66f1f47  jne short 0x66F1F60
0x66f1f49  mov rax,[rbx]
0x66f1f4c  mov rax,[rax+8]
0x66f1f4f  mov rcx,rbx
0x66f1f52  call qword ptr [0xF99FFA0]
0x66f1f59  nop [rax+rax]
0x66f1f5a  jmp 0x66F1F60
0x66f1f5f  nop [rax+rax]
0x66f1f60  mov rbx,[rbp+0x1320]
0x66f1f67  test rbx,rbx
0x66f1f6a  je short 0x66F1FA0
0x66f1f6c  lock dec dword ptr [rbx+8]
0x66f1f70  jne short 0x66F1FA0
0x66f1f72  mov rax,[rbx]
0x66f1f75  mov rax,[rax]
0x66f1f78  mov rcx,rbx
0x66f1f7b  call qword ptr [0xF99FFA0]
0x66f1f81  lock dec dword ptr [rbx+0xC]
0x66f1f87  jne short 0x66F1FA0
0x66f1f89  mov rax,[rbx]
0x66f1f8c  mov rax,[rax+8]
0x66f1f8f  mov rcx,rbx
0x66f1f92  call qword ptr [0xF99FFA0]
0x66f1f99  nop [rax+rax]
0x66f1f9a  jmp 0x66F1FA0
0x66f1f9f  nop [rax+rax]
0x66f1fa0  mov rbx,[rbp+0x1310]
0x66f1fa7  test rbx,rbx
0x66f1faa  je short 0x66F1FE0
0x66f1fac  lock dec dword ptr [rbx+8]
0x66f1fb0  jne short 0x66F1FE0
0x66f1fb2  mov rax,[rbx]
0x66f1fb5  mov rax,[rax]
0x66f1fb8  mov rcx,rbx
0x66f1fbb  call qword ptr [0xF99FFA0]
0x66f1fc1  lock dec dword ptr [rbx+0xC]
0x66f1fc7  jne short 0x66F1FE0
0x66f1fc9  mov rax,[rbx]
0x66f1fcc  mov rax,[rax+8]
0x66f1fcf  mov rcx,rbx
0x66f1fd2  call qword ptr [0xF99FFA0]
0x66f1fd8  nop [rax+rax]
0x66f1fd9  jmp 0x66F1FE0
0x66f1fde  nop [rax+rax]
0x66f1fe0  mov rbx,[rbp+0x12E8]
0x66f1fe7  test rbx,rbx
0x66f1fea  je short 0x66F2020
0x66f1fec  lock dec dword ptr [rbx+8]
0x66f1ff0  jne short 0x66F2020
0x66f1ff2  mov rax,[rbx]
0x66f1ff5  mov rax,[rax]
0x66f1ff8  mov rcx,rbx
0x66f1ffb  call qword ptr [0xF99FFA0]
0x66f2001  lock dec dword ptr [rbx+0xC]
0x66f2007  jne short 0x66F2020
0x66f2009  mov rax,[rbx]
0x66f200c  mov rax,[rax+8]
0x66f200f  mov rcx,rbx
0x66f2012  call qword ptr [0xF99FFA0]
0x66f2018  nop [rax+rax]
0x66f2019  jmp 0x66F2020
0x66f201e  nop [rax+rax]
0x66f2020  mov rbx,[rbp+0x13D0]
0x66f2027  test rbx,rbx
0x66f202a  je short 0x66F2060
0x66f202c  lock dec dword ptr [rbx+8]
0x66f2030  jne short 0x66F2060
0x66f2032  mov rax,[rbx]
0x66f2035  mov rax,[rax]
0x66f2038  mov rcx,rbx
0x66f203b  call qword ptr [0xF99FFA0]
0x66f2041  lock dec dword ptr [rbx+0xC]
0x66f2047  jne short 0x66F2060
0x66f2049  mov rax,[rbx]
0x66f204c  mov rax,[rax+8]
0x66f204f  mov rcx,rbx
0x66f2052  call qword ptr [0xF99FFA0]
0x66f2058  nop [rax+rax]
0x66f2059  jmp 0x66F2060
0x66f205e  nop [rax+rax]
```
Meaning: More shared_ptr releases: [rbp+0x1330] (jmp 0x66F1F60), [rbp+0x1320] (jmp 0x66F1FA0), [rbp+0x1310] (jmp 0x66F1FE0), [rbp+0x12E8] (jmp 0x66F2020), [rbp+0x13D0] (jmp 0x66F2060) [V]. Same lock-dec + dual-destructor pattern via qword [0xF99FFA0] [V]. Callee RVA: [0xF99FFA0] [V].

### lines 1921..1960
```asm
0x66f1a1f  sub rcx,rax
0x66f1a22  cmp rcx,0x20
0x66f1a26  jae 0x66F82BB
0x66f1a2c  or rdx,0x27
0x66f1a30  mov rcx,rax
0x66f1a33  call 0xE935700
0x66f1a38  lea rax,[rbp+0x1588]
0x66f1a3f  movups [rax],xmm6
0x66f1a42  mov qword ptr [rax+0x10],0
0x66f1a4a  lea rcx,[rbp+0x1440]
0x66f1a51  call 0x678F260
0x66f1a56  lea rcx,[rbp+0xF70]
0x66f1a5d  call 0x67E23F0
0x66f1a62  test r15,r15
0x66f1a65  je short 0x66F1AA0
0x66f1a67  lock dec dword ptr [r15+8]
0x66f1a6c  jne short 0x66F1AA0
0x66f1a6e  mov rax,[r15]
0x66f1a71  mov rax,[rax]
0x66f1a74  mov rcx,r15
0x66f1a77  call qword ptr [0xF99FFA0]
0x66f1a7d  lock dec dword ptr [r15+0xC]
0x66f1a82  jne short 0x66F1AA0
0x66f1a84  mov rax,[r15]
0x66f1a87  mov rax,[rax+8]
0x66f1a8b  mov rcx,r15
0x66f1a8e  call qword ptr [0xF99FFA0]
0x66f1a94  nop [rax+rax]
0x66f1aa0  mov rbx,[rbp+0x13D0]
0x66f1aa7  test rbx,rbx
0x66f1aaa  je short 0x66F1AE0
0x66f1aac  lock dec dword ptr [rbx+8]
0x66f1ab0  jne short 0x66F1AE0
0x66f1ab2  mov rax,[rbx]
0x66f1ab5  mov rax,[rax]
0x66f1ab8  mov rcx,rbx
0x66f1abb  call qword ptr [0xF99FFA0]
0x66f1ac1  lock dec dword ptr [rbx+0xC]
0x66f1ac5  jne short 0x66F1AE0
0x66f1ac7  mov rax,[rbx]
```
Meaning: Heap-free path from 0x66F1A17: cmp free space vs 0x20, jae throw 0x66F82BB, else or rdx,0x27, call 0xE935700 free [V]. Zero [rbp+0x1588] (xmm6) and [rax+0x10]=0 [V]. Call 0x678F260([rbp+0x1440]) destroy, then 0x67E23F0([rbp+0xF70]) destroy [V]. Shared_ptr release r15: lock dec [r15+8], if 0 call dtor via [0xF99FFA0](r15), lock dec [r15+0xC], if 0 call dtor2 via [0xF99FFA0](r15+8) [V]. Same pattern for [rbp+0x13D0] (jmp 0x66F1AE0) [V]. Callee RVAs: 0xe935700, 0x678f260, 0x67e23f0, [0xF99FFA0] [V].

## NEXT
Next line to do: 1961 (phase 15 of 17 complete)

### lines 1961..2000
```asm
0x66f1aca  mov rax,[rax+8]
0x66f1ace  mov rcx,rbx
0x66f1ad1  call qword ptr [0xF99FFA0]
0x66f1ad7  nop [rax+rax]
0x66f1ae0  mov rbx,[rbp+0x13C0]
0x66f1ae7  test rbx,rbx
0x66f1aea  je short 0x66F1B20
0x66f1aec  lock dec dword ptr [rbx+8]
0x66f1af0  jne short 0x66F1B20
0x66f1af2  mov rax,[rbx]
0x66f1af5  mov rax,[rax]
0x66f1af8  mov rcx,rbx
0x66f1afb  call qword ptr [0xF99FFA0]
0x66f1b01  lock dec dword ptr [rbx+0xC]
0x66f1b05  jne short 0x66F1B20
0x66f1b07  mov rax,[rbx]
0x66f1b0a  mov rax,[rax+8]
0x66f1b0e  mov rcx,rbx
0x66f1b11  call qword ptr [0xF99FFA0]
0x66f1b17  nop [rax+rax]
0x66f1b20  mov rbx,[rbp+0x1398]
0x66f1b27  test rbx,rbx
0x66f1b2a  je short 0x66F1B60
0x66f1b2c  lock dec dword ptr [rbx+8]
0x66f1b30  jne short 0x66F1B60
0x66f1b32  mov rax,[rbx]
0x66f1b35  mov rax,[rax]
0x66f1b38  mov rcx,rbx
0x66f1b3b  call qword ptr [0xF99FFA0]
0x66f1b41  lock dec dword ptr [rbx+0xC]
0x66f1b45  jne short 0x66F1B60
0x66f1b47  mov rax,[rbx]
0x66f1b4a  mov rax,[rax+8]
0x66f1b4e  mov rcx,rbx
0x66f1b51  call qword ptr [0xF99FFA0]
0x66f1b57  nop [rax+rax]
0x66f1b60  mov rbx,[rbp+0x1330]
0x66f1b67  test rbx,rbx
0x66f1b6a  je short 0x66F1BA0
0x66f1b6c  lock dec dword ptr [rbx+8]
```
Meaning: Finish [rbp+0x13D0] release: dtor2 via [0xF99FFA0](this+8) [V]. Same lock-dec + dual-destructor pattern via qword [0xF99FFA0] for [rbp+0x13C0] (jmp 0x66F1B20), [rbp+0x1398] (jmp 0x66F1B60), start of [rbp+0x1330] (lock dec [+8]) [V]. Callee RVA: [0xF99FFA0] [V].

## NEXT
Next line to do: 2001 (phase 16 of 17 complete)

### lines 2001..2040
```asm
0x66f1b70  jne short 0x66F1BA0
0x66f1b72  mov rax,[rbx]
0x66f1b75  mov rax,[rax]
0x66f1b78  mov rcx,rbx
0x66f1b7b  call qword ptr [0xF99FFA0]
0x66f1b81  lock dec dword ptr [rbx+0xC]
0x66f1b85  jne short 0x66F1BA0
0x66f1b87  mov rax,[rbx]
0x66f1b8a  mov rax,[rax+8]
0x66f1b8e  mov rcx,rbx
0x66f1b91  call qword ptr [0xF99FFA0]
0x66f1b97  nop [rax+rax]
0x66f1b99  jmp 0x66F1BA0
0x66f1b9e  nop [rax+rax]
0x66f1ba0  mov rbx,[rbp+0x1320]
0x66f1ba7  test rbx,rbx
0x66f1baa  je short 0x66F1BE0
0x66f1bac  lock dec dword ptr [rbx+8]
0x66f1bb0  jne short 0x66F1BE0
0x66f1bb2  mov rax,[rbx]
0x66f1bb5  mov rax,[rax]
0x66f1bb8  mov rcx,rbx
0x66f1bbb  call qword ptr [0xF99FFA0]
0x66f1bc1  lock dec dword ptr [rbx+0xC]
0x66f1bc5  jne short 0x66F1BE0
0x66f1bc7  mov rax,[rbx]
0x66f1bca  mov rax,[rax+8]
0x66f1bce  mov rcx,rbx
0x66f1bd1  call qword ptr [0xF99FFA0]
0x66f1bd7  nop [rax+rax]
0x66f1bd9  jmp 0x66F1BE0
0x66f1bde  nop [rax+rax]
0x66f1be0  mov rbx,[rbp+0x1310]
0x66f1be7  test rbx,rbx
0x66f1bea  je short 0x66F1C20
0x66f1bec  lock dec dword ptr [rbx+8]
0x66f1bf0  jne short 0x66F1C20
0x66f1bf2  mov rax,[rbx]
0x66f1bf5  mov rax,[rax]
0x66f1bf8  mov rcx,rbx
0x66f1bfb  call qword ptr [0xF99FFA0]
0x66f1c01  lock dec dword ptr [rbx+0xC]
0x66f1c05  jne short 0x66F1C20
0x66f1c07  mov rax,[rbx]
0x66f1c0a  mov rax,[rax+8]
0x66f1c0e  mov rcx,rbx
0x66f1c11  call qword ptr [0xF99FFA0]
0x66f1c17  nop [rax+rax]
0x66f1c19  jmp 0x66F1C20
0x66f1c1e  nop [rax+rax]
0x66f1c20  mov rbx,[rbp+0x12E8]
0x66f1c27  test rbx,rbx
0x66f1c2a  je short 0x66F1C60
0x66f1c2c  lock dec dword ptr [rbx+8]
0x66f1c30  jne short 0x66F1C60
0x66f1c32  mov rax,[rbx]
0x66f1c35  mov rax,[rax]
0x66f1c38  mov rcx,rbx
0x66f1c3b  call qword ptr [0xF99FFA0]
0x66f1c41  lock dec dword ptr [rbx+0xC]
0x66f1c47  jne short 0x66F1C60
0x66f1c49  mov rax,[rbx]
0x66f1c4c  mov rax,[rax+8]
0x66f1c50  mov rcx,rbx
0x66f1c53  call qword ptr [0xF99FFA0]
0x66f1c59  nop [rax+rax]
0x66f1c5a  jmp 0x66F1C60
0x66f1c5f  nop [rax+rax]
```
Meaning: Finish [rbp+0x1330] release (dtor+dtor2 via [0xF99FFA0]) [V]. Same lock-dec + dual-destructor pattern for [rbp+0x1320] (jmp 0x66F1BE0), [rbp+0x1310] (jmp 0x66F1C20), [rbp+0x12E8] (jmp 0x66F1C60) [V]. Every release: test null -> skip; lock dec [+8]; if zero: call dtor via qword [0xF99FFA0](this); lock dec [+0xC]; if zero: call dtor2 via qword [0xF99FFA0](this+8); nop padding [V]. Callee RVA: [0xF99FFA0] [V].

## NEXT
Next line to do: 2041 (phase 17 of 17 complete)

### lines 2041..2050
```asm
0x66f1c0a  mov rax,[rax+8]
0x66f1c0e  mov rcx,rbx
0x66f1c11  call qword ptr [0xF99FFA0]
0x66f1c17  nop [rax+rax]
0x66f1c19  jmp 0x66F1C20
0x66f1c1e  nop [rax+rax]
0x66f1c20  mov rbx,[rbp+0x12E8]
0x66f1c27  test rbx,rbx
0x66f1c2a  je short 0x66F1C60
0x66f1c2c  lock dec dword ptr [rbx+8]
0x66f1c30  jne short 0x66F1C60
0x66f1c32  mov rax,[rbx]
```
Meaning: Tail of [rbp+0x1310] release: dtor2 via [0xF99FFA0](this+8), jmp 0x66F1C20 [V]. Start of [rbp+0x12E8] release: test null, lock dec [+8], jne skip, mov rax,[rbx] (load vtable) [V]. Callee RVA: [0xF99FFA0] [V].

## NEXT
All 17 phases complete (lines 1401..2050). File complete.


