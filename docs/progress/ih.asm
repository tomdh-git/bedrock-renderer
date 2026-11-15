6698e30: push rbp
6698e31: push r15
6698e33: push r14
6698e35: push r13
6698e37: push r12
6698e39: push rsi
6698e3a: push rdi
6698e3b: push rbx
6698e3c: mov eax, 0x2158
6698e41: call 0xe9e7970
6698e46: sub rsp, rax
6698e49: lea rbp, [rsp + 0x80]
6698e51: movaps xmmword ptr [rbp + 0x20c0], xmm9
6698e59: movaps xmmword ptr [rbp + 0x20b0], xmm8
6698e61: movaps xmmword ptr [rbp + 0x20a0], xmm7
6698e68: movaps xmmword ptr [rbp + 0x2090], xmm6
6698e6f: mov qword ptr [rbp + 0x2088], 0xfffffffffffffffe
6698e7a: mov r14, r8
6698e7d: mov rdi, rdx
6698e80: mov qword ptr [rbp + 0x2078], rcx
6698e87: movzx ecx, byte ptr [r8 + 0x78]
6698e8c: movzx eax, byte ptr [r8 + 0x79]
6698e91: mov r15d, eax
6698e94: xor r15b, 1
6698e98: mov byte ptr [rbp + 0x2087], cl
6698e9e: and cl, 1
6698ea1: mov byte ptr [rbp + 0x2077], cl
6698ea7: or cl, al
6698ea9: setne r8b
6698ead: movzx ecx, byte ptr [r14 + 0x7a]
6698eb2: or r8b, cl
6698eb5: mov edx, dword ptr [rdx + 0x70]
6698eb8: cmp edx, 1
6698ebb: sete r12b
6698ebf: and r12b, r15b
6698ec2: and r12b, r8b
6698ec5: je 0x6698ece
6698ec7: mov bl, 1
6698ec9: xor r13d, r13d
6698ecc: jmp 0x6698ede
6698ece: cmp edx, 1
6698ed1: sete dl
6698ed4: or cl, al
6698ed6: sete bl
6698ed9: and bl, dl
6698edb: mov r13d, ebx
6698ede: mov rax, qword ptr [r14 + 0x28]
6698ee2: test rax, rax
6698ee5: je 0x6698eed
6698ee7: mov rsi, qword ptr [rax + 0x40]
6698eeb: jmp 0x6698eef
6698eed: xor esi, esi
6698eef: and r15b, byte ptr [rdi + 0x75]
6698ef3: cmp byte ptr [rsi + 0x25c], 1
6698efa: mov qword ptr [rbp + 0x2068], r14
6698f01: jne 0x6698f0b
6698f03: mov esi, dword ptr [rsi + 0x258]
6698f09: jmp 0x6698f46
6698f0b: lea rdx, [rsi + 0x98]
6698f12: lea rcx, [rbp + 0x1bb0]
6698f19: call 0xbb68930
6698f1e: mov ecx, dword ptr [rbp + 0x1bb0]
6698f24: movabs rax, 0x100000000
6698f2e: or rax, rcx
6698f31: mov qword ptr [rsi + 0x258], rax
6698f38: mov rsi, rcx
6698f3b: movzx eax, byte ptr [r14 + 0x78]
6698f40: mov byte ptr [rbp + 0x2087], al
6698f46: mov byte ptr [rbp + 0x2086], r15b
6698f4d: mov eax, esi
6698f4f: shr eax, 3
6698f52: and eax, 2
6698f55: test bl, bl
6698f57: mov r14d, 2
6698f5d: cmove r14, rax
6698f61: mov eax, dword ptr [rip + 0xc35f629]
6698f67: mov ecx, dword ptr [rip + 0xc1dd85b]
6698f6d: mov rdx, qword ptr gs:[0x58]
6698f76: mov rcx, qword ptr [rdx + rcx*8]
6698f7a: cmp eax, dword ptr [rcx + 4]
6698f80: mov qword ptr [rbp + 0x2060], rdi
6698f87: mov qword ptr [rbp + 0x2050], rsi
6698f8e: jg 0x669cc4b
6698f94: movzx eax, byte ptr [rdi + 0x74]
6698f98: shl eax, 2
6698f9b: xor r15d, r15d
6698f9e: test r12b, r12b
6698fa1: cmovne r15, rax
6698fa5: mov eax, dword ptr [rip + 0xc35f76d]
6698fab: mov ecx, dword ptr [rip + 0xc1dd817]
6698fb1: mov rdx, qword ptr gs:[0x58]
6698fba: mov rcx, qword ptr [rdx + rcx*8]
6698fbe: cmp eax, dword ptr [rcx + 4]
6698fc4: jg 0x669d284
6698fca: mov eax, dword ptr [rip + 0xc35f8d0]
6698fd0: mov ecx, dword ptr [rip + 0xc1dd7f2]
6698fd6: mov rdx, qword ptr gs:[0x58]
6698fdf: mov rcx, qword ptr [rdx + rcx*8]
6698fe3: cmp eax, dword ptr [rcx + 4]
6698fe9: jg 0x669d983
6698fef: mov eax, dword ptr [rip + 0xc35fa33]
6698ff5: mov ecx, dword ptr [rip + 0xc1dd7cd]
6698ffb: mov rdx, qword ptr gs:[0x58]
6699004: mov rcx, qword ptr [rdx + rcx*8]
6699008: cmp eax, dword ptr [rcx + 4]
669900e: jg 0x669e088
6699014: mov ebx, esi
6699016: and ebx, 0x200
669901c: mov eax, ebx
669901e: shr eax, 9
6699021: or r14, rax
6699024: or r14, r15
6699027: movzx eax, r12b
669902b: shl eax, 4
669902e: movzx ecx, r13b
6699032: mov rdx, rsi
6699035: lea esi, [rax + rcx*8]
6699038: or rsi, r14
669903b: mov byte ptr [rbp + 0x1fb0], 0
6699042: test edx, 0x800
6699048: je 0x66990cf
669904e: test byte ptr [rbp + 0x2087], 0x40
6699055: mov r15, qword ptr [rbp + 0x2060]
669905c: jne 0x6699167
6699062: mov qword ptr [rbp + 0x1bc0], 0xf
669906d: mov qword ptr [rbp + 0x1bc8], 0xf
6699078: movabs rax, 0x61486e496d657449
6699082: mov qword ptr [rbp + 0x1bb0], rax
6699089: movabs rax, 0x726f6c6f43646e61
6699093: mov qword ptr [rbp + 0x1bb7], rax
669909a: mov byte ptr [rbp + 0x1bbf], 0
66990a1: test r12b, r12b
66990a4: je 0x6699326
66990aa: lea r9, [rip + 0x9131223]
66990b1: lea rcx, [rbp + 0x1bb0]
66990b8: mov edx, 0x14
66990bd: call 0x9d6d0
66990c2: nop 
66990c3: mov r12, qword ptr [rbp + 0x2078]
66990ca: jmp 0x669934b
66990cf: mov qword ptr [rbp + 0x1bb8], 0
66990da: mov rcx, qword ptr [rip + 0xbca50c7]
66990e1: mov rax, qword ptr [rcx]
66990e4: mov rax, qword ptr [rax + 8]
66990e8: mov edx, 0x20
66990ed: call qword ptr [rip + 0x9306ead]
66990f3: test rax, rax
66990f6: mov r15, qword ptr [rbp + 0x2060]
66990fd: je 0x669cbcb
6699103: mov qword ptr [rbp + 0x1bb0], rax
669910a: mov qword ptr [rbp + 0x1bc0], 0x12
6699115: mov qword ptr [rbp + 0x1bc8], 0x1f
6699120: movups xmm0, xmmword ptr [rip + 0x8f5bd80]
6699127: movups xmmword ptr [rax], xmm0
669912a: mov word ptr [rax + 0x10], 0x6465
6699130: mov byte ptr [rax + 0x12], 0
6699134: test r12b, r12b
6699137: je 0x6699200
669913d: mov qword ptr [rbp + 0x1bc0], 0x1c
6699148: movups xmm0, xmmword ptr [rip + 0x8f5bd77]
669914f: movups xmmword ptr [rax + 0xc], xmm0
6699153: movups xmm0, xmmword ptr [rip + 0x8f5bd60]
669915a: movups xmmword ptr [rax], xmm0
669915d: mov edx, 0x1c
6699162: jmp 0x669922f
6699167: mov qword ptr [rbp + 0x1bb8], 0
6699172: mov rcx, qword ptr [rip + 0xbca502f]
6699179: mov rax, qword ptr [rcx]
669917c: mov rax, qword ptr [rax + 8]
6699180: mov edx, 0x20
6699185: call qword ptr [rip + 0x9306e15]
669918b: test rax, rax
669918e: je 0x669cbe0
6699194: mov qword ptr [rbp + 0x1bb0], rax
669919b: mov qword ptr [rbp + 0x1bc0], 0x14
66991a6: mov qword ptr [rbp + 0x1bc8], 0x1f
66991b1: movups xmm0, xmmword ptr [rip + 0x8e98b8d]
66991b8: movups xmmword ptr [rax], xmm0
66991bb: mov dword ptr [rax + 0x10], 0x746e696c
66991c2: mov byte ptr [rax + 0x14], 0
66991c6: test r12b, r12b
66991c9: je 0x6699382
66991cf: mov qword ptr [rbp + 0x1bc0], 0x19
66991da: movups xmm0, xmmword ptr [rip + 0x8e98b94]
66991e1: movups xmmword ptr [rax + 9], xmm0
66991e5: movups xmm0, xmmword ptr [rip + 0x8e98b80]
66991ec: movups xmmword ptr [rax], xmm0
66991ef: mov edx, 0x19
66991f4: mov r12, qword ptr [rbp + 0x2078]
66991fb: jmp 0x66993bb
6699200: mov edx, 0x12
6699205: test r13b, r13b
6699208: je 0x6699233
669920a: mov qword ptr [rbp + 0x1bc0], 0x19
6699215: movups xmm0, xmmword ptr [rip + 0x8f5bc7a]
669921c: movups xmmword ptr [rax + 9], xmm0
6699220: movups xmm0, xmmword ptr [rip + 0x8f5bc66]
6699227: movups xmmword ptr [rax], xmm0
669922a: mov edx, 0x19
669922f: mov byte ptr [rax + rdx], 0
6699233: mov r9, qword ptr [r15 + 0x40]
6699237: mov rcx, qword ptr [r15 + 0x68]
669923b: shl r14d, 6
669923f: lea r10, [rip + 0xc35f14a]
6699246: add r10, r14
6699249: shl esi, 4
669924c: lea r8, [rip + 0xc35f345]
6699253: add r8, rsi
6699256: mov qword ptr [rbp + 0x1880], rax
669925d: mov qword ptr [rbp + 0x1888], rdx
6699264: mov qword ptr [rsp + 0x28], r10
6699269: lea rax, [rbp + 0x1880]
6699270: mov qword ptr [rsp + 0x20], rax
6699275: lea rdx, [rbp + 0x1fd0]
669927c: call 0x67cfd80
6699281: nop 
6699282: mov rsi, qword ptr [rbp + 0x1fd0]
6699289: mov rdi, qword ptr [rsi]
669928c: test rdi, rdi
669928f: je 0x669988c
6699295: mov eax, dword ptr [rip + 0xc331345]
669929b: mov ecx, dword ptr [rip + 0xc1dd527]
66992a1: mov rdx, qword ptr gs:[0x58]
66992aa: mov rcx, qword ptr [rdx + rcx*8]
66992ae: cmp eax, dword ptr [rcx + 4]
66992b4: jg 0x669e78d
66992ba: cmp byte ptr [rdi + 0x10], 1
66992be: jne 0x669988c
66992c4: mov rax, qword ptr [rsi + 8]
66992c8: test rax, rax
66992cb: je 0x6699596
66992d1: lock inc dword ptr [rax + 8]
66992d5: mov rax, qword ptr [rsi]
66992d8: mov r14, qword ptr [rsi + 8]
66992dc: mov rax, qword ptr [rax + 0x18]
66992e0: mov rsi, qword ptr [rax]
66992e3: test r14, r14
66992e6: je 0x66995a0
66992ec: lock dec dword ptr [r14 + 8]
66992f1: jne 0x66995a0
66992f7: mov rax, qword ptr [r14]
66992fa: mov rax, qword ptr [rax]
66992fd: mov rcx, r14
6699300: call qword ptr [rip + 0x9306c9a]
6699306: lock dec dword ptr [r14 + 0xc]
669930b: jne 0x66995a0
6699311: mov rax, qword ptr [r14]
6699314: mov rax, qword ptr [rax + 8]
6699318: mov rcx, r14
669931b: call qword ptr [rip + 0x9306c7f]
6699321: jmp 0x66995a0
6699326: test r13b, r13b
6699329: mov r12, qword ptr [rbp + 0x2078]
6699330: je 0x669934b
6699332: lea r9, [rip + 0x8eafe77]
6699339: lea rcx, [rbp + 0x1bb0]
6699340: mov edx, 0x11
6699345: call 0x9d6d0
669934a: nop 
669934b: mov r9, qword ptr [r15 + 0x40]
669934f: mov rcx, qword ptr [r15 + 0x68]
6699353: shl r14d, 6
6699357: lea rax, [rip + 0xc35f032]
669935e: add rax, r14
6699361: mov rdx, qword ptr [rbp + 0x1bc0]
6699368: cmp qword ptr [rbp + 0x1bc8], 0x10
6699370: jb 0x66994b2
6699376: mov r10, qword ptr [rbp + 0x1bb0]
669937d: jmp 0x66994b9
6699382: mov edx, 0x14
6699387: test r13b, r13b
669938a: mov r12, qword ptr [rbp + 0x2078]
6699391: je 0x66993bf
6699393: mov qword ptr [rbp + 0x1bc0], 0x16
669939e: movups xmm0, xmmword ptr [rip + 0x8e9897e]
66993a5: movups xmmword ptr [rax], xmm0
66993a8: movabs rcx, 0x746e696c47737361
66993b2: mov qword ptr [rax + 0xe], rcx
66993b6: mov edx, 0x16
66993bb: mov byte ptr [rax + rdx], 0
66993bf: mov r9, qword ptr [r15 + 0x40]
66993c3: mov rcx, qword ptr [r15 + 0x68]
66993c7: shl r14d, 6
66993cb: lea r10, [rip + 0xc35efbe]
66993d2: add r10, r14
66993d5: shl esi, 4
66993d8: lea r8, [rip + 0xc35f4c9]
66993df: add r8, rsi
66993e2: mov qword ptr [rbp + 0x1880], rax
66993e9: mov qword ptr [rbp + 0x1888], rdx
66993f0: mov qword ptr [rsp + 0x28], r10
66993f5: lea rax, [rbp + 0x1880]
66993fc: mov qword ptr [rsp + 0x20], rax
6699401: lea rdx, [rbp + 0x1fd0]
6699408: call 0x67cfd80
669940d: nop 
669940e: mov rsi, qword ptr [rbp + 0x1fd0]
6699415: mov rdi, qword ptr [rsi]
6699418: test rdi, rdi
669941b: je 0x669988c
6699421: mov eax, dword ptr [rip + 0xc3311b9]
6699427: mov ecx, dword ptr [rip + 0xc1dd39b]
669942d: mov rdx, qword ptr gs:[0x58]
6699436: mov rcx, qword ptr [rdx + rcx*8]
669943a: cmp eax, dword ptr [rcx + 4]
6699440: jg 0x669e97e
6699446: cmp byte ptr [rdi + 0x10], 1
669944a: jne 0x669988c
6699450: mov rax, qword ptr [rsi + 8]
6699454: test rax, rax
6699457: je 0x66996c7
669945d: lock inc dword ptr [rax + 8]
6699461: mov rax, qword ptr [rsi]
6699464: mov r14, qword ptr [rsi + 8]
6699468: mov rax, qword ptr [rax + 0x18]
669946c: mov rsi, qword ptr [rax]
669946f: test r14, r14
6699472: je 0x66996d1
6699478: lock dec dword ptr [r14 + 8]
669947d: jne 0x66996d1
6699483: mov rax, qword ptr [r14]
6699486: mov rax, qword ptr [rax]
6699489: mov rcx, r14
669948c: call qword ptr [rip + 0x9306b0e]
6699492: lock dec dword ptr [r14 + 0xc]
6699497: jne 0x66996d1
669949d: mov rax, qword ptr [r14]
66994a0: mov rax, qword ptr [rax + 8]
66994a4: mov rcx, r14
66994a7: call qword ptr [rip + 0x9306af3]
66994ad: jmp 0x66996d1
66994b2: lea r10, [rbp + 0x1bb0]
66994b9: shl esi, 4
66994bc: lea r8, [rip + 0xc35f25d]
66994c3: add r8, rsi
66994c6: mov qword ptr [rbp + 0x1880], r10
66994cd: mov qword ptr [rbp + 0x1888], rdx
66994d4: mov qword ptr [rsp + 0x28], rax
66994d9: lea rax, [rbp + 0x1880]
66994e0: mov qword ptr [rsp + 0x20], rax
66994e5: lea rdx, [rbp + 0x1fd0]
66994ec: call 0x67cfd80
66994f1: nop 
66994f2: mov rsi, qword ptr [rbp + 0x1fd0]
66994f9: mov rdi, qword ptr [rsi]
66994fc: test rdi, rdi
66994ff: je 0x669988c
6699505: mov eax, dword ptr [rip + 0xc3310d5]
669950b: mov ecx, dword ptr [rip + 0xc1dd2b7]
6699511: mov rdx, qword ptr gs:[0x58]
669951a: mov rcx, qword ptr [rdx + rcx*8]
669951e: cmp eax, dword ptr [rcx + 4]
6699524: jg 0x669e9cf
669952a: cmp byte ptr [rdi + 0x10], 1
669952e: jne 0x669988c
6699534: mov rax, qword ptr [rsi + 8]
6699538: test rax, rax
669953b: je 0x66996fa
6699541: lock inc dword ptr [rax + 8]
6699545: mov rax, qword ptr [rsi]
6699548: mov r14, qword ptr [rsi + 8]
669954c: mov rax, qword ptr [rax + 0x18]
6699550: mov rsi, qword ptr [rax]
6699553: test r14, r14
6699556: je 0x6699704
669955c: lock dec dword ptr [r14 + 8]
6699561: jne 0x6699704
6699567: mov rax, qword ptr [r14]
669956a: mov rax, qword ptr [rax]
669956d: mov rcx, r14
6699570: call qword ptr [rip + 0x9306a2a]
6699576: lock dec dword ptr [r14 + 0xc]
669957b: jne 0x6699704
6699581: mov rax, qword ptr [r14]
6699584: mov rax, qword ptr [rax + 8]
6699588: mov rcx, r14
669958b: call qword ptr [rip + 0x9306a0f]
6699591: jmp 0x6699704
6699596: mov rax, qword ptr [rsi]
6699599: mov rax, qword ptr [rax + 0x18]
669959d: mov rsi, qword ptr [rax]
66995a0: test rsi, rsi
66995a3: je 0x669988c
66995a9: mov r8, qword ptr [r15]
66995ac: mov rdx, qword ptr [rbp + 0x1fd0]
66995b3: mov byte ptr [rbp + 0x1fb0], 0
66995ba: lea rcx, [rbp + 0x1f28]
66995c1: call 0x675dd80
66995c6: nop 
66995c7: mov byte ptr [rbp + 0x1fb0], 1
66995ce: or r12b, r13b
66995d1: cmp r12b, 1
66995d5: mov r12, qword ptr [rbp + 0x2078]
66995dc: jne 0x6699732
66995e2: mov eax, dword ptr [rip + 0xc35f450]
66995e8: mov ecx, dword ptr [rip + 0xc1dd1da]
66995ee: mov rdx, qword ptr gs:[0x58]
66995f7: mov rcx, qword ptr [rdx + rcx*8]
66995fb: cmp eax, dword ptr [rcx + 4]
6699601: jg 0x669ea34
6699607: mov rax, qword ptr [r12 + 0x430]
669960f: test rax, rax
6699612: je 0x669962c
6699614: cmp byte ptr [rax], 1
6699617: jne 0x669962c
6699619: mov rax, qword ptr [r12 + 0x440]
6699621: mov esi, 0xc0
6699626: add rsi, qword ptr [rax + 0x18]
669962a: jmp 0x6699658
669962c: mov eax, dword ptr [rip + 0xc361b36]
6699632: mov ecx, dword ptr [rip + 0xc1dd190]
6699638: mov rdx, qword ptr gs:[0x58]
6699641: mov rcx, qword ptr [rdx + rcx*8]
6699645: lea rsi, [rip + 0xc361b0c]
669964c: cmp eax, dword ptr [rcx + 4]
6699652: jg 0x669eabe
6699658: xorps xmm0, xmm0
669965b: movaps xmmword ptr [rbp + 0x1880], xmm0
6699662: mov rax, qword ptr [rsi + 8]
6699666: test rax, rax
6699669: je 0x669aa8c
669966f: lock inc dword ptr [rax + 8]
6699673: mov r14, qword ptr [rbp + 0x1888]
669967a: movups xmm0, xmmword ptr [rsi]
669967d: movaps xmmword ptr [rbp + 0x1880], xmm0
6699684: test r14, r14
6699687: je 0x669aaa1
669968d: lock dec dword ptr [r14 + 8]
6699692: jne 0x669aaa1
6699698: mov rax, qword ptr [r14]
669969b: mov rax, qword ptr [rax]
669969e: mov rcx, r14
66996a1: call qword ptr [rip + 0x93068f9]
66996a7: lock dec dword ptr [r14 + 0xc]
66996ac: jne 0x669aaa1
66996b2: mov rax, qword ptr [r14]
66996b5: mov rax, qword ptr [rax + 8]
66996b9: mov rcx, r14
66996bc: call qword ptr [rip + 0x93068de]
66996c2: jmp 0x669aaa1
66996c7: mov rax, qword ptr [rsi]
66996ca: mov rax, qword ptr [rax + 0x18]
66996ce: mov rsi, qword ptr [rax]
66996d1: test rsi, rsi
66996d4: je 0x669988c
66996da: mov r8, qword ptr [r15]
66996dd: mov rdx, qword ptr [rbp + 0x1fd0]
66996e4: mov byte ptr [rbp + 0x1fb0], 0
66996eb: lea rcx, [rbp + 0x1f28]
66996f2: call 0x675dd80
66996f7: nop 
66996f8: jmp 0x669972b
66996fa: mov rax, qword ptr [rsi]
66996fd: mov rax, qword ptr [rax + 0x18]
6699701: mov rsi, qword ptr [rax]
6699704: test rsi, rsi
6699707: je 0x669988c
669970d: mov r8, qword ptr [r15]
6699710: mov rdx, qword ptr [rbp + 0x1fd0]
6699717: mov byte ptr [rbp + 0x1fb0], 0
669971e: lea rcx, [rbp + 0x1f28]
6699725: call 0x675dd80
669972a: nop 
669972b: mov byte ptr [rbp + 0x1fb0], 1
6699732: mov r14, qword ptr [rbp + 0x1fd8]
6699739: test r14, r14
669973c: je 0x669976b
669973e: lock dec dword ptr [r14 + 8]
6699743: jne 0x669976b
6699745: mov rax, qword ptr [r14]
6699748: mov rax, qword ptr [rax]
669974b: mov rcx, r14
669974e: call qword ptr [rip + 0x930684c]
6699754: lock dec dword ptr [r14 + 0xc]
6699759: jne 0x669976b
669975b: mov rax, qword ptr [r14]
669975e: mov rax, qword ptr [rax + 8]
6699762: mov rcx, r14
6699765: call qword ptr [rip + 0x9306835]
669976b: mov rax, qword ptr [rbp + 0x1bc8]
6699772: cmp rax, 0x10
6699776: mov rsi, qword ptr [rbp + 0x2068]
669977d: jb 0x66997b7
669977f: mov rcx, qword ptr [rbp + 0x1bb0]
6699786: lea rdx, [rax + 1]
669978a: cmp rdx, 0x1000
6699791: jb 0x66997b2
6699793: mov r8, qword ptr [rcx - 8]
6699797: add rcx, -8
669979b: sub rcx, r8
669979e: cmp rcx, 0x20
66997a2: jae 0x669e7d7
66997a8: add rax, 0x28
66997ac: mov rdx, rax
66997af: mov rcx, r8
66997b2: call 0xe935700
66997b7: mov r14, qword ptr [rsi]
66997ba: mov rax, qword ptr [r14 + 0x60]
66997be: sub rax, qword ptr [r14 + 0x58]
66997c2: shr rax, 2
66997c6: imul eax, eax, 0xaaaaaaab
66997cc: test eax, eax
66997ce: je 0x66997fc
66997d0: mov edx, 0x250
66997d5: add rdx, qword ptr [rbp + 0x1f28]
66997dc: lea r15, [rbp + 0x1bb0]
66997e3: mov rcx, r15
66997e6: xor r8d, r8d
66997e9: call 0xbbd7c70
66997ee: mov rcx, r14
66997f1: mov rdx, r15
66997f4: call 0x4dedd00
66997f9: mov r14, qword ptr [rsi]
66997fc: mov rax, qword ptr [rbp + 0x2050]
6699803: xor ecx, ecx
6699805: cmp byte ptr [r14 + 0x1d4], 0
669980d: je 0x6699816
669980f: mov ecx, dword ptr [r14 + 0x1d0]
6699816: mov dword ptr [rbp + 0x1eec], ecx
669981c: test eax, 0x800
6699821: mov rsi, qword ptr [rbp + 0x2068]
6699828: jne 0x6699977
669982e: movzx eax, word ptr [rip + 0xc228229]
6699835: mov rcx, qword ptr [rbp + 0x1f70]
669983c: movzx r9d, word ptr [rbp + 0x1f7a]
6699844: mov edx, r9d
6699847: shl edx, 4
669984a: lea r8, [rdx + rdx*2]
669984e: mov rdx, rcx
6699851: test r9, r9
6699854: je 0x6699911
669985a: mov r9, qword ptr [rip + 0xc35eab7]
6699861: mov r10, r8
6699864: mov rdx, rcx
6699867: nop word ptr [rax + rax]
6699870: mov r11, qword ptr [rdx]
6699873: cmp qword ptr [r11 + 0x28], r9
6699877: je 0x6699911
669987d: add rdx, 0x30
6699881: add r10, -0x30
6699885: jne 0x6699870
6699887: jmp 0x6699977
669988c: mov rsi, qword ptr [rbp + 0x1fd8]
6699893: test rsi, rsi
6699896: je 0x66998c3
6699898: lock dec dword ptr [rsi + 8]
669989c: jne 0x66998c3
669989e: mov rax, qword ptr [rsi]
66998a1: mov rax, qword ptr [rax]
66998a4: mov rcx, rsi
66998a7: call qword ptr [rip + 0x93066f3]
66998ad: lock dec dword ptr [rsi + 0xc]
66998b1: jne 0x66998c3
66998b3: mov rax, qword ptr [rsi]
66998b6: mov rax, qword ptr [rax + 8]
66998ba: mov rcx, rsi
66998bd: call qword ptr [rip + 0x93066dd]
66998c3: mov rax, qword ptr [rbp + 0x1bc8]
66998ca: cmp rax, 0x10
66998ce: jb 0x669c9e7
66998d4: mov rcx, qword ptr [rbp + 0x1bb0]
66998db: lea rdx, [rax + 1]
66998df: cmp rdx, 0x1000
66998e6: jb 0x6699907
66998e8: mov r8, qword ptr [rcx - 8]
66998ec: add rcx, -8
66998f0: sub rcx, r8
66998f3: cmp rcx, 0x20
66998f7: jae 0x669e7d7
66998fd: add rax, 0x28
6699901: mov rdx, rax
6699904: mov rcx, r8
6699907: call 0xe935700
669990c: jmp 0x669c9e7
6699911: add r8, rcx
6699914: cmp rdx, r8
6699917: jae 0x6699977
6699919: lea r8, [rsi + 8]
669991d: sub edx, ecx
669991f: shr edx, 4
6699922: imul ecx, edx, 0xffffaaab
6699928: mov word ptr [rbp + 0x1880], cx
669992f: mov byte ptr [rbp + 0x1882], 1
6699936: mov word ptr [rbp + 0x1bb0], ax
669993d: mov dword ptr [rbp + 0x1bb4], 0
6699947: mov byte ptr [rbp + 0x1bb8], 1
669994e: mov byte ptr [rbp + 0x1bbc], 1
6699955: mov dword ptr [rsp + 0x20], 0
669995d: lea rcx, [rbp + 0x1f28]
6699964: lea rdx, [rbp + 0x1880]
669996b: lea r9, [rbp + 0x1bb0]
6699972: call 0xbcaba00
6699977: mov rdi, r12
669997a: lea rcx, [rbp + 0x1f28]
6699981: call 0x66a08b0
6699986: movups xmm0, xmmword ptr [rsi + 0xc0]
669998d: movaps xmmword ptr [rbp + 0x1bb0], xmm0
6699994: mov qword ptr [rbp + 0x1880], 1
669999f: lea r12, [rbp + 0x1bb0]
66999a6: mov qword ptr [rbp + 0x1888], r12
66999ad: mov rax, qword ptr [rbp + 0x1f60]
66999b4: movzx edx, word ptr [rbp + 0x1f6a]
66999bb: mov ecx, edx
66999bd: shl ecx, 4
66999c0: mov r8, rax
66999c3: test edx, edx
66999c5: je 0x66999f8
66999c7: mov r9, qword ptr [rip + 0xc35e952]
66999ce: xor r8d, r8d
66999d1: nop word ptr cs:[rax + rax]
66999e0: mov r10, qword ptr [rax + r8]
66999e4: cmp qword ptr [r10 + 0x28], r9
66999e8: je 0x66999f5
66999ea: add r8, 0x10
66999ee: cmp rcx, r8
66999f1: jne 0x66999e0
66999f3: jmp 0x6699a44
66999f5: add r8, rax
66999f8: lea r9, [rax + rcx]
66999fc: cmp r8, r9
66999ff: jae 0x6699a44
6699a01: sub r8d, eax
6699a04: shr r8d, 4
6699a08: mov word ptr [rbp + 0x1fd0], r8w
6699a10: mov byte ptr [rbp + 0x1fd2], 1
6699a17: lea rdx, [rbp + 0x1fd0]
6699a1e: lea r8, [rbp + 0x1880]
6699a25: lea rcx, [rbp + 0x1f30]
6699a2c: call 0x5679db0
6699a31: mov rax, qword ptr [rbp + 0x1f60]
6699a38: movzx edx, word ptr [rbp + 0x1f6a]
6699a3f: mov ecx, edx
6699a41: shl ecx, 4
6699a44: movsd xmm0, qword ptr [rsi + 0xd0]
6699a4c: movups xmmword ptr [rbp + 0x1bb0], xmm0
6699a53: mov qword ptr [rbp + 0x1880], 1
6699a5e: mov qword ptr [rbp + 0x1888], r12
6699a65: mov r8, rax
6699a68: test dx, dx
6699a6b: je 0x6699a98
6699a6d: mov r9, qword ptr [rip + 0xc35e8b4]
6699a74: xor r8d, r8d
6699a77: nop word ptr [rax + rax]
6699a80: mov r10, qword ptr [rax + r8]
6699a84: cmp qword ptr [r10 + 0x28], r9
6699a88: je 0x6699a95
6699a8a: add r8, 0x10
6699a8e: cmp rcx, r8
6699a91: jne 0x6699a80
6699a93: jmp 0x6699ae4
6699a95: add r8, rax
6699a98: lea r9, [rax + rcx]
6699a9c: cmp r8, r9
6699a9f: jae 0x6699ae4
6699aa1: sub r8d, eax
6699aa4: shr r8d, 4
6699aa8: mov word ptr [rbp + 0x1fd0], r8w
6699ab0: mov byte ptr [rbp + 0x1fd2], 1
6699ab7: lea rdx, [rbp + 0x1fd0]
6699abe: lea r8, [rbp + 0x1880]
6699ac5: lea rcx, [rbp + 0x1f30]
6699acc: call 0x5679db0
6699ad1: mov rax, qword ptr [rbp + 0x1f60]
6699ad8: movzx edx, word ptr [rbp + 0x1f6a]
6699adf: mov ecx, edx
6699ae1: shl ecx, 4
6699ae4: movups xmm0, xmmword ptr [rsi + 0xd8]
6699aeb: movaps xmmword ptr [rbp + 0x1bb0], xmm0
6699af2: mov qword ptr [rbp + 0x1880], 1
6699afd: mov qword ptr [rbp + 0x1888], r12
6699b04: mov r8, rax
6699b07: test dx, dx
6699b0a: je 0x6699b38
6699b0c: mov r9, qword ptr [rip + 0xc35e81d]
6699b13: xor r8d, r8d
6699b16: nop word ptr cs:[rax + rax]
6699b20: mov r10, qword ptr [rax + r8]
6699b24: cmp qword ptr [r10 + 0x28], r9
6699b28: je 0x6699b35
6699b2a: add r8, 0x10
6699b2e: cmp rcx, r8
6699b31: jne 0x6699b20
6699b33: jmp 0x6699b84
6699b35: add r8, rax
6699b38: lea r9, [rax + rcx]
6699b3c: cmp r8, r9
6699b3f: jae 0x6699b84
6699b41: sub r8d, eax
6699b44: shr r8d, 4
6699b48: mov word ptr [rbp + 0x1fd0], r8w
6699b50: mov byte ptr [rbp + 0x1fd2], 1
6699b57: lea rdx, [rbp + 0x1fd0]
6699b5e: lea r8, [rbp + 0x1880]
6699b65: lea rcx, [rbp + 0x1f30]
6699b6c: call 0x5679db0
6699b71: mov rax, qword ptr [rbp + 0x1f60]
6699b78: movzx edx, word ptr [rbp + 0x1f6a]
6699b7f: mov ecx, edx
6699b81: shl ecx, 4
6699b84: movups xmm0, xmmword ptr [rsi + 0xa0]
6699b8b: movaps xmmword ptr [rbp + 0x1bb0], xmm0
6699b92: mov qword ptr [rbp + 0x1880], 1
6699b9d: mov qword ptr [rbp + 0x1888], r12
6699ba4: mov r8, rax
6699ba7: test dx, dx
6699baa: je 0x6699bd8
6699bac: mov r9, qword ptr [rip + 0xc35e78d]
6699bb3: xor r8d, r8d
6699bb6: nop word ptr cs:[rax + rax]
6699bc0: mov r10, qword ptr [rax + r8]
6699bc4: cmp qword ptr [r10 + 0x28], r9
6699bc8: je 0x6699bd5
6699bca: add r8, 0x10
6699bce: cmp rcx, r8
6699bd1: jne 0x6699bc0
6699bd3: jmp 0x6699c24
6699bd5: add r8, rax
6699bd8: lea r9, [rax + rcx]
6699bdc: cmp r8, r9
6699bdf: jae 0x6699c24
6699be1: sub r8d, eax
6699be4: shr r8d, 4
6699be8: mov word ptr [rbp + 0x1fd0], r8w
6699bf0: mov byte ptr [rbp + 0x1fd2], 1
6699bf7: lea rdx, [rbp + 0x1fd0]
6699bfe: lea r8, [rbp + 0x1880]
6699c05: lea rcx, [rbp + 0x1f30]
6699c0c: call 0x5679db0
6699c11: mov rax, qword ptr [rbp + 0x1f60]
6699c18: movzx edx, word ptr [rbp + 0x1f6a]
6699c1f: mov ecx, edx
6699c21: shl ecx, 4
6699c24: movups xmm0, xmmword ptr [rsi + 0xe8]
6699c2b: movaps xmmword ptr [rbp + 0x1bb0], xmm0
6699c32: mov qword ptr [rbp + 0x1880], 1
6699c3d: mov qword ptr [rbp + 0x1888], r12
6699c44: mov r8, rax
6699c47: test dx, dx
6699c4a: je 0x6699c7c
6699c4c: mov r9, qword ptr [rip + 0xc35e6f5]
6699c53: xor r8d, r8d
6699c56: nop word ptr cs:[rax + rax]
6699c60: mov r10, qword ptr [rax + r8]
6699c64: cmp qword ptr [r10 + 0x28], r9
6699c68: je 0x6699c79
6699c6a: add r8, 0x10
6699c6e: cmp rcx, r8
6699c71: jne 0x6699c60
6699c73: mov dx, 1
6699c77: jmp 0x6699cc8
6699c79: add r8, rax
6699c7c: lea r9, [rax + rcx]
6699c80: cmp r8, r9
6699c83: jae 0x6699cc8
6699c85: sub r8d, eax
6699c88: shr r8d, 4
6699c8c: mov word ptr [rbp + 0x1fd0], r8w
6699c94: mov byte ptr [rbp + 0x1fd2], 1
6699c9b: lea rdx, [rbp + 0x1fd0]
6699ca2: lea r8, [rbp + 0x1880]
6699ca9: lea rcx, [rbp + 0x1f30]
6699cb0: call 0x5679db0
6699cb5: mov rax, qword ptr [rbp + 0x1f60]
6699cbc: movzx edx, word ptr [rbp + 0x1f6a]
6699cc3: mov ecx, edx
6699cc5: shl ecx, 4
6699cc8: movsx r8d, byte ptr [rsi + 0x7c]
6699ccd: xorps xmm0, xmm0
6699cd0: cvtsi2ss xmm0, r8d
6699cd5: shufps xmm0, xmm0, 0
6699cd9: movaps xmmword ptr [rbp + 0x1bb0], xmm0
6699ce0: mov qword ptr [rbp + 0x1880], 1
6699ceb: mov qword ptr [rbp + 0x1888], r12
6699cf2: mov r8, rax
6699cf5: test dx, dx
6699cf8: je 0x6699d25
6699cfa: mov rdx, qword ptr [rip + 0xc35e687]
6699d01: mov r9, rcx
6699d04: mov r8, rax
6699d07: nop word ptr [rax + rax]
6699d10: mov r10, qword ptr [r8]
6699d13: cmp qword ptr [r10 + 0x28], rdx
6699d17: je 0x6699d25
6699d19: add r8, 0x10
6699d1d: add r9, -0x10
6699d21: jne 0x6699d10
6699d23: jmp 0x6699d5d
6699d25: add rcx, rax
6699d28: cmp r8, rcx
6699d2b: jae 0x6699d5d
6699d2d: sub r8d, eax
6699d30: shr r8d, 4
6699d34: mov word ptr [rbp + 0x1fd0], r8w
6699d3c: mov byte ptr [rbp + 0x1fd2], 1
6699d43: lea rdx, [rbp + 0x1fd0]
6699d4a: lea r8, [rbp + 0x1880]
6699d51: lea rcx, [rbp + 0x1f30]
6699d58: call 0x5679db0
6699d5d: movss xmm0, dword ptr [rsi + 0x100]
6699d65: cmp byte ptr [rsi + 0x79], 1
6699d69: jne 0x6699de8
6699d6b: movsd xmm1, qword ptr [rip + 0x893957d]
6699d73: movsd qword ptr [rbp + 0x1bb0], xmm1
6699d7b: movss dword ptr [rbp + 0x1bb8], xmm0
6699d83: mov dword ptr [rbp + 0x1bbc], 0
6699d8d: mov qword ptr [rbp + 0x1880], 1
6699d98: mov qword ptr [rbp + 0x1888], r12
6699d9f: mov rax, qword ptr [rbp + 0x1f60]
6699da6: movzx r8d, word ptr [rbp + 0x1f6a]
6699dae: mov edx, r8d
6699db1: shl edx, 4
6699db4: mov rcx, rax
6699db7: test r8d, r8d
6699dba: je 0x6699e55
6699dc0: mov r8, qword ptr [rip + 0xc35e589]
6699dc7: mov r9, rdx
6699dca: mov rcx, rax
6699dcd: nop dword ptr [rax]
6699dd0: mov r10, qword ptr [rcx]
6699dd3: cmp qword ptr [r10 + 0x28], r8
6699dd7: je 0x6699e55
6699dd9: add rcx, 0x10
6699ddd: add r9, -0x10
6699de1: jne 0x6699dd0
6699de3: jmp 0x6699e8a
6699de8: movsd xmm1, qword ptr [rsi + 0xf8]
6699df0: xorps xmm2, xmm2
6699df3: movss xmm2, xmm0
6699df7: movlhps xmm1, xmm2
6699dfa: movups xmmword ptr [rbp + 0x1bb0], xmm1
6699e01: mov qword ptr [rbp + 0x1880], 1
6699e0c: mov qword ptr [rbp + 0x1888], r12
6699e13: mov rax, qword ptr [rbp + 0x1f60]
6699e1a: movzx r8d, word ptr [rbp + 0x1f6a]
6699e22: mov edx, r8d
6699e25: shl edx, 4
6699e28: mov rcx, rax
6699e2b: test r8d, r8d
6699e2e: je 0x6699e55
6699e30: mov r8, qword ptr [rip + 0xc35e519]
6699e37: mov r9, rdx
6699e3a: mov rcx, rax
6699e3d: nop dword ptr [rax]
6699e40: mov r10, qword ptr [rcx]
6699e43: cmp qword ptr [r10 + 0x28], r8
6699e47: je 0x6699e55
6699e49: add rcx, 0x10
6699e4d: add r9, -0x10
6699e51: jne 0x6699e40
6699e53: jmp 0x6699e8a
6699e55: add rdx, rax
6699e58: cmp rcx, rdx
6699e5b: jae 0x6699e8a
6699e5d: sub ecx, eax
6699e5f: shr ecx, 4
6699e62: mov word ptr [rbp + 0x1fd0], cx
6699e69: mov byte ptr [rbp + 0x1fd2], 1
6699e70: lea rdx, [rbp + 0x1fd0]
6699e77: lea r8, [rbp + 0x1880]
6699e7e: lea rcx, [rbp + 0x1f30]
6699e85: call 0x5679db0
6699e8a: xorps xmm0, xmm0
6699e8d: test byte ptr [rbp + 0x2050], 4
6699e94: je 0x6699e9e
6699e96: movss xmm0, dword ptr [rip + 0x882e1c2]
6699e9e: shufps xmm0, xmm0, 0
6699ea2: movaps xmmword ptr [rbp + 0x1bb0], xmm0
6699ea9: mov qword ptr [rbp + 0x1880], 1
6699eb4: mov qword ptr [rbp + 0x1888], r12
6699ebb: mov rax, qword ptr [rbp + 0x1f60]
6699ec2: movzx r8d, word ptr [rbp + 0x1f6a]
6699eca: mov edx, r8d
6699ecd: shl edx, 4
6699ed0: mov rcx, rax
6699ed3: test r8d, r8d
6699ed6: je 0x6699f05
6699ed8: mov r8, qword ptr [rip + 0xc35e459]
6699edf: mov r9, rdx
6699ee2: mov rcx, rax
6699ee5: nop word ptr cs:[rax + rax]
6699ef0: mov r10, qword ptr [rcx]
6699ef3: cmp qword ptr [r10 + 0x28], r8
6699ef7: je 0x6699f05
6699ef9: add rcx, 0x10
6699efd: add r9, -0x10
6699f01: jne 0x6699ef0
6699f03: jmp 0x6699f3a
6699f05: add rdx, rax
6699f08: cmp rcx, rdx
6699f0b: jae 0x6699f3a
6699f0d: sub ecx, eax
6699f0f: shr ecx, 4
6699f12: mov word ptr [rbp + 0x1fd0], cx
6699f19: mov byte ptr [rbp + 0x1fd2], 1
6699f20: lea rdx, [rbp + 0x1fd0]
6699f27: lea r8, [rbp + 0x1880]
6699f2e: lea rcx, [rbp + 0x1f30]
6699f35: call 0x5679db0
6699f3a: mov eax, dword ptr [rip + 0xc35eb08]
6699f40: mov ecx, dword ptr [rip + 0xc1dc882]
6699f46: mov rdx, qword ptr gs:[0x58]
6699f4f: mov rcx, qword ptr [rdx + rcx*8]
6699f53: cmp eax, dword ptr [rcx + 4]
6699f59: jg 0x669e802
6699f5f: test ebx, ebx
6699f61: je 0x669a00a
6699f67: movups xmm0, xmmword ptr [rsi + 0xb0]
6699f6e: movaps xmmword ptr [rbp + 0x1bb0], xmm0
6699f75: mov qword ptr [rbp + 0x1880], 1
6699f80: mov qword ptr [rbp + 0x1888], r12
6699f87: mov rax, qword ptr [rbp + 0x1f60]
6699f8e: movzx r8d, word ptr [rbp + 0x1f6a]
6699f96: mov edx, r8d
6699f99: shl edx, 4
6699f9c: mov rcx, rax
6699f9f: test r8d, r8d
6699fa2: je 0x6699fd5
6699fa4: mov r8, qword ptr [rip + 0xc35ea95]
6699fab: mov r9, rdx
6699fae: mov rcx, rax
6699fb1: nop word ptr cs:[rax + rax]
6699fc0: mov r10, qword ptr [rcx]
6699fc3: cmp qword ptr [r10 + 0x28], r8
6699fc7: je 0x6699fd5
6699fc9: add rcx, 0x10
6699fcd: add r9, -0x10
6699fd1: jne 0x6699fc0
6699fd3: jmp 0x669a00a
6699fd5: add rdx, rax
6699fd8: cmp rcx, rdx
6699fdb: jae 0x669a00a
6699fdd: sub ecx, eax
6699fdf: shr ecx, 4
6699fe2: mov word ptr [rbp + 0x1fd0], cx
6699fe9: mov byte ptr [rbp + 0x1fd2], 1
6699ff0: lea rdx, [rbp + 0x1fd0]
6699ff7: lea r8, [rbp + 0x1880]
6699ffe: lea rcx, [rbp + 0x1f30]
669a005: call 0x5679db0
669a00a: test dword ptr [rbp + 0x2050], 0x80000
669a014: je 0x669a0ba
669a01a: movups xmm0, xmmword ptr [rsi + 0x90]
669a021: movaps xmmword ptr [rbp + 0x1bb0], xmm0
669a028: mov qword ptr [rbp + 0x1880], 1
669a033: mov qword ptr [rbp + 0x1888], r12
669a03a: mov rax, qword ptr [rbp + 0x1f60]
669a041: movzx r8d, word ptr [rbp + 0x1f6a]
669a049: mov edx, r8d
669a04c: shl edx, 4
669a04f: mov rcx, rax
669a052: test r8d, r8d
669a055: je 0x669a085
669a057: mov r8, qword ptr [rip + 0xc35e302]
669a05e: mov r9, rdx
669a061: mov rcx, rax
669a064: nop word ptr cs:[rax + rax]
669a070: mov r10, qword ptr [rcx]
669a073: cmp qword ptr [r10 + 0x28], r8
669a077: je 0x669a085
669a079: add rcx, 0x10
669a07d: add r9, -0x10
669a081: jne 0x669a070
669a083: jmp 0x669a0ba
669a085: add rdx, rax
669a088: cmp rcx, rdx
669a08b: jae 0x669a0ba
669a08d: sub ecx, eax
669a08f: shr ecx, 4
669a092: mov word ptr [rbp + 0x1fd0], cx
669a099: mov byte ptr [rbp + 0x1fd2], 1
669a0a0: lea rdx, [rbp + 0x1fd0]
669a0a7: lea r8, [rbp + 0x1880]
669a0ae: lea rcx, [rbp + 0x1f30]
669a0b5: call 0x5679db0
669a0ba: test byte ptr [rbp + 0x2087], 0x40
669a0c1: je 0x669a33d
669a0c7: mov rax, qword ptr [rbp + 0x1f70]
669a0ce: movzx r8d, word ptr [rbp + 0x1f7a]
669a0d6: mov ecx, r8d
669a0d9: shl ecx, 4
669a0dc: lea rdx, [rcx + rcx*2]
669a0e0: mov rcx, rax
669a0e3: test r8, r8
669a0e6: je 0x669a115
669a0e8: mov r8, qword ptr [rip + 0xc35e281]
669a0ef: mov r9, rdx
669a0f2: mov rcx, rax
669a0f5: nop word ptr cs:[rax + rax]
669a100: mov r10, qword ptr [rcx]
669a103: cmp qword ptr [r10 + 0x28], r8
669a107: je 0x669a115
669a109: add rcx, 0x30
669a10d: add r9, -0x30
669a111: jne 0x669a100
669a113: jmp 0x669a163
669a115: add rdx, rax
669a118: cmp rcx, rdx
669a11b: jae 0x669a163
669a11d: lea r8, [rsi + 0x18]
669a121: sub ecx, eax
669a123: shr ecx, 4
669a126: imul eax, ecx, 0xffffaaab
669a12c: mov word ptr [rbp + 0x1880], ax
669a133: mov byte ptr [rbp + 0x1882], 1
669a13a: mov byte ptr [rbp + 0x1bbc], 0
669a141: mov dword ptr [rsp + 0x20], 0
669a149: lea rcx, [rbp + 0x1f28]
669a150: lea rdx, [rbp + 0x1880]
669a157: lea r9, [rbp + 0x1bb0]
669a15e: call 0xbcaba00
669a163: movups xmm0, xmmword ptr [rsi + 0x104]
669a16a: movaps xmmword ptr [rbp + 0x1bb0], xmm0
669a171: mov qword ptr [rbp + 0x1880], 1
669a17c: mov qword ptr [rbp + 0x1888], r12
669a183: mov rax, qword ptr [rbp + 0x1f60]
669a18a: movzx edx, word ptr [rbp + 0x1f6a]
669a191: mov ecx, edx
669a193: shl ecx, 4
669a196: mov r8, rax
669a199: test edx, edx
669a19b: je 0x669a1c8
669a19d: mov r9, qword ptr [rip + 0xc35e1c4]
669a1a4: xor r8d, r8d
669a1a7: nop word ptr [rax + rax]
669a1b0: mov r10, qword ptr [rax + r8]
669a1b4: cmp qword ptr [r10 + 0x28], r9
669a1b8: je 0x669a1c5
669a1ba: add r8, 0x10
669a1be: cmp rcx, r8
669a1c1: jne 0x669a1b0
669a1c3: jmp 0x669a214
669a1c5: add r8, rax
669a1c8: lea r9, [rax + rcx]
669a1cc: cmp r8, r9
669a1cf: jae 0x669a214
669a1d1: sub r8d, eax
669a1d4: shr r8d, 4
669a1d8: mov word ptr [rbp + 0x1fd0], r8w
669a1e0: mov byte ptr [rbp + 0x1fd2], 1
669a1e7: lea rdx, [rbp + 0x1fd0]
669a1ee: lea r8, [rbp + 0x1880]
669a1f5: lea rcx, [rbp + 0x1f30]
669a1fc: call 0x5679db0
669a201: mov rax, qword ptr [rbp + 0x1f60]
669a208: movzx edx, word ptr [rbp + 0x1f6a]
669a20f: mov ecx, edx
669a211: shl ecx, 4
669a214: movsd xmm0, qword ptr [rsi + 0x114]
669a21c: movups xmmword ptr [rbp + 0x1bb0], xmm0
669a223: mov qword ptr [rbp + 0x1880], 1
669a22e: mov qword ptr [rbp + 0x1888], r12
669a235: mov r8, rax
669a238: test dx, dx
669a23b: je 0x669a26c
669a23d: mov r9, qword ptr [rip + 0xc35e134]
669a244: xor r8d, r8d
669a247: nop word ptr [rax + rax]
669a250: mov r10, qword ptr [rax + r8]
669a254: cmp qword ptr [r10 + 0x28], r9
669a258: je 0x669a269
669a25a: add r8, 0x10
669a25e: cmp rcx, r8
669a261: jne 0x669a250
669a263: mov dx, 1
669a267: jmp 0x669a2b8
669a269: add r8, rax
669a26c: lea r9, [rax + rcx]
669a270: cmp r8, r9
669a273: jae 0x669a2b8
669a275: sub r8d, eax
669a278: shr r8d, 4
669a27c: mov word ptr [rbp + 0x1fd0], r8w
669a284: mov byte ptr [rbp + 0x1fd2], 1
669a28b: lea rdx, [rbp + 0x1fd0]
669a292: lea r8, [rbp + 0x1880]
669a299: lea rcx, [rbp + 0x1f30]
669a2a0: call 0x5679db0
669a2a5: mov rax, qword ptr [rbp + 0x1f60]
669a2ac: movzx edx, word ptr [rbp + 0x1f6a]
669a2b3: mov ecx, edx
669a2b5: shl ecx, 4
669a2b8: movups xmm0, xmmword ptr [rsi + 0x80]
669a2bf: movaps xmmword ptr [rbp + 0x1bb0], xmm0
669a2c6: mov qword ptr [rbp + 0x1880], 1
669a2d1: mov qword ptr [rbp + 0x1888], r12
669a2d8: mov r8, rax
669a2db: test dx, dx
669a2de: je 0x669a305
669a2e0: mov rdx, qword ptr [rip + 0xc35e099]
669a2e7: mov r9, rcx
669a2ea: mov r8, rax
669a2ed: nop dword ptr [rax]
669a2f0: mov r10, qword ptr [r8]
669a2f3: cmp qword ptr [r10 + 0x28], rdx
669a2f7: je 0x669a305
669a2f9: add r8, 0x10
669a2fd: add r9, -0x10
669a301: jne 0x669a2f0
669a303: jmp 0x669a33d
669a305: add rcx, rax
669a308: cmp r8, rcx
669a30b: jae 0x669a33d
669a30d: sub r8d, eax
669a310: shr r8d, 4
669a314: mov word ptr [rbp + 0x1fd0], r8w
669a31c: mov byte ptr [rbp + 0x1fd2], 1
669a323: lea rdx, [rbp + 0x1fd0]
669a32a: lea r8, [rbp + 0x1880]
669a331: lea rcx, [rbp + 0x1f30]
669a338: call 0x5679db0
669a33d: mov eax, dword ptr [rip + 0xc35e715]
669a343: mov ecx, dword ptr [rip + 0xc1dc47f]
669a349: mov rdx, qword ptr gs:[0x58]
669a352: mov rcx, qword ptr [rdx + rcx*8]
669a356: cmp eax, dword ptr [rcx + 4]
669a35c: jg 0x669e874
669a362: movsx eax, byte ptr [rsi + 0x7d]
669a366: xorps xmm0, xmm0
669a369: cvtsi2ss xmm0, eax
669a36d: shufps xmm0, xmm0, 0
669a371: movaps xmmword ptr [rbp + 0x1bb0], xmm0
669a378: mov qword ptr [rbp + 0x1880], 1
669a383: mov qword ptr [rbp + 0x1888], r12
669a38a: mov rax, qword ptr [rbp + 0x1f60]
669a391: movzx r8d, word ptr [rbp + 0x1f6a]
669a399: mov edx, r8d
669a39c: shl edx, 4
669a39f: mov rcx, rax
669a3a2: test r8d, r8d
669a3a5: mov r12, rdi
669a3a8: je 0x669a3d5
669a3aa: mov r8, qword ptr [rip + 0xc35e69f]
669a3b1: mov r9, rdx
669a3b4: mov rcx, rax
669a3b7: nop word ptr [rax + rax]
669a3c0: mov r10, qword ptr [rcx]
669a3c3: cmp qword ptr [r10 + 0x28], r8
669a3c7: je 0x669a3d5
669a3c9: add rcx, 0x10
669a3cd: add r9, -0x10
669a3d1: jne 0x669a3c0
669a3d3: jmp 0x669a40a
669a3d5: add rdx, rax
669a3d8: cmp rcx, rdx
669a3db: jae 0x669a40a
669a3dd: sub ecx, eax
669a3df: shr ecx, 4
669a3e2: mov word ptr [rbp + 0x1fd0], cx
669a3e9: mov byte ptr [rbp + 0x1fd2], 1
669a3f0: lea rdx, [rbp + 0x1fd0]
669a3f7: lea r8, [rbp + 0x1880]
669a3fe: lea rcx, [rbp + 0x1f30]
669a405: call 0x5679db0
669a40a: mov rax, qword ptr [rsi]
669a40d: mov qword ptr [rbp + 0x1fc0], rax
669a414: mov rsi, qword ptr [rsi + 0x120]
669a41b: lea rdi, [r12 + 0x288]
669a423: mov rcx, rdi
669a426: call 0xeec59f0
669a42b: test eax, eax
669a42d: jne 0x669e8e6
669a433: mov qword ptr [rbp + 0x1f20], rdi
669a43a: cmp dword ptr [r12 + 0x2d4], 0x7fffffff
669a446: je 0x669e8f0
669a44c: mov rdi, rsi
669a44f: shr rdi, 8
669a453: mov r11, rsi
669a456: shr r11, 0x10
669a45a: mov r10, rsi
669a45d: shr r10, 0x18
669a461: mov r9, rsi
669a464: shr r9, 0x20
669a468: mov r8, rsi
669a46b: shr r8, 0x28
669a46f: mov rcx, rsi
669a472: shr rcx, 0x30
669a476: mov rax, rsi
669a479: shr rax, 0x38
669a47d: movzx edx, sil
669a481: movabs r15, 0xcbf29ce484222325
669a48b: mov qword ptr [rbp + 0x1f10], rdx
669a492: xor rdx, r15
669a495: movabs rbx, 0x100000001b3
669a49f: imul rdx, rbx
669a4a3: movzx edi, dil
669a4a7: mov qword ptr [rbp + 0x1f18], rdi
669a4ae: xor rdx, rdi
669a4b1: imul rdx, rbx
669a4b5: movzx r11d, r11b
669a4b9: xor rdx, r11
669a4bc: imul rdx, rbx
669a4c0: movzx r10d, r10b
669a4c4: xor rdx, r10
669a4c7: imul rdx, rbx
669a4cb: movzx r9d, r9b
669a4cf: xor rdx, r9
669a4d2: imul rdx, rbx
669a4d6: movzx r13d, r8b
669a4da: xor rdx, r13
669a4dd: imul rdx, rbx
669a4e1: movzx r14d, cl
669a4e5: xor rdx, r14
669a4e8: imul rdx, rbx
669a4ec: xor rdx, rax
669a4ef: imul rdx, rbx
669a4f3: mov eax, 0x9e3779b9
669a4f8: add rdx, rax
669a4fb: mov rcx, rdx
669a4fe: shl rcx, 6
669a502: mov r8, rdx
669a505: shr r8, 2
669a509: add r8, rcx
669a50c: movabs rcx, 0x83288085322e9a6
669a516: add rcx, r8
669a519: xor rcx, rdx
669a51c: mov rax, qword ptr [rbp + 0x1fc0]
669a523: mov edx, eax
669a525: and edx, 0xf8
669a52b: mov qword ptr [rbp + 0x2058], r15
669a532: xor rdx, r15
669a535: imul rdx, rbx
669a539: movzx edi, ah
669a53c: xor rdi, rdx
669a53f: imul rdi, rbx
669a543: mov edx, eax
669a545: shr edx, 0x10
669a548: movzx edx, dl
669a54b: xor rdx, rdi
669a54e: imul rdx, rbx
669a552: mov r8d, eax
669a555: shr r8d, 0x18
669a559: xor r8, rdx
669a55c: imul r8, rbx
669a560: mov rdx, rax
669a563: shr rdx, 0x20
669a567: movzx edx, dl
669a56a: xor rdx, r8
669a56d: imul rdx, rbx
669a571: mov r8, rax
669a574: shr r8, 0x28
669a578: movzx r8d, r8b
669a57c: xor r8, rdx
669a57f: imul r8, rbx
669a583: mov rdx, rax
669a586: shr rdx, 0x30
669a58a: movzx edx, dl
669a58d: xor rdx, r8
669a590: imul rdx, rbx
669a594: shr rax, 0x38
669a598: xor rax, rdx
669a59b: imul rax, rbx
669a59f: mov rdx, rcx
669a5a2: shl rdx, 6
669a5a6: add rdx, rax
669a5a9: mov rax, rcx
669a5ac: shr rax, 2
669a5b0: mov r8d, 0x9e3779b9
669a5b6: add rax, r8
669a5b9: add rax, rdx
669a5bc: xor rax, rcx
669a5bf: mov rcx, qword ptr [r12 + 0x278]
669a5c7: mov qword ptr [rbp + 0x1fc8], rax
669a5ce: and rcx, rax
669a5d1: mov rax, qword ptr [r12 + 0x250]
669a5d9: mov rdx, qword ptr [r12 + 0x260]
669a5e1: shl rcx, 4
669a5e5: mov r15, qword ptr [rdx + rcx + 8]
669a5ea: cmp r15, rax
669a5ed: mov qword ptr [rbp + 0x1798], r14
669a5f4: je 0x669a695
669a5fa: mov rcx, qword ptr [rdx + rcx]
669a5fe: movabs rdx, 0xff00000000000000
669a608: and rdx, rsi
669a60b: shl r14, 0x30
669a60f: or r14, rdx
669a612: mov rdx, r13
669a615: shl rdx, 0x28
669a619: or rdx, r14
669a61c: mov r8, r9
669a61f: shl r8, 0x20
669a623: or r8, rdx
669a626: mov edx, r10d
669a629: shl edx, 0x18
669a62c: or rdx, r8
669a62f: mov r8d, r11d
669a632: shl r8d, 0x10
669a636: or r8, rdx
669a639: mov r12, qword ptr [rbp + 0x1f18]
669a640: mov edx, r12d
669a643: shl edx, 8
669a646: or rdx, r8
669a649: mov rdi, qword ptr [rbp + 0x1f10]
669a650: or rdx, rdi
669a653: mov r8, qword ptr [rbp + 0x1fc0]
669a65a: cmp rdx, qword ptr [r15 + 0x10]
669a65e: jne 0x669a690
669a660: jmp 0x669a67a
669a662: nop word ptr cs:[rax + rax]
669a670: mov r15, qword ptr [r15 + 8]
669a674: cmp rdx, qword ptr [r15 + 0x10]
669a678: jne 0x669a690
669a67a: cmp word ptr [r15 + 0x18], 0
669a680: jne 0x669a690
669a682: cmp r8, qword ptr [r15 + 0x20]
669a686: je 0x669a698
669a688: nop dword ptr [rax + rax]
669a690: cmp r15, rcx
669a693: jne 0x669a670
669a695: xor r15d, r15d
669a698: test r15, r15
669a69b: cmove r15, rax
669a69f: cmp r15, rax
669a6a2: jne 0x669affb
669a6a8: mov qword ptr [rbp + 0x1828], r13
669a6af: mov qword ptr [rbp + 0x1820], r9
669a6b6: mov qword ptr [rbp + 0x1818], r10
669a6bd: mov qword ptr [rbp + 0x1810], r11
669a6c4: mov rax, qword ptr [rbp + 0x2060]
669a6cb: mov rax, qword ptr [rax + 0x10]
669a6cf: mov rcx, qword ptr [rbp + 0x2068]
669a6d6: movups xmm6, xmmword ptr [rcx + 0x38]
669a6da: movups xmm7, xmmword ptr [rcx + 0x48]
669a6de: movups xmm8, xmmword ptr [rcx + 0x58]
669a6e3: movups xmm9, xmmword ptr [rcx + 0x68]
669a6e8: mov rdi, qword ptr [rax + 0xa80]
669a6ef: mov r15b, byte ptr [rax + 0xa88]
669a6f6: mov rcx, qword ptr [rip + 0xbca3aab]
669a6fd: mov rax, qword ptr [rcx]
669a700: mov rax, qword ptr [rax + 8]
669a704: mov edx, 0x48
669a709: call qword ptr [rip + 0x9305891]
669a70f: nop 
669a710: mov r12, rax
669a713: test rax, rax
669a716: je 0x669cbf5
669a71c: xor eax, eax
669a71e: test r15b, 1
669a722: cmovne rax, rdi
669a726: movups xmmword ptr [r12], xmm6
669a72b: movups xmmword ptr [r12 + 0x10], xmm7
669a731: movups xmmword ptr [r12 + 0x20], xmm8
669a737: movups xmmword ptr [r12 + 0x30], xmm9
669a73d: mov qword ptr [r12 + 0x40], rax
669a742: mov rax, qword ptr [rbp + 0x2078]
669a749: mov rcx, qword ptr [rax + 0x278]
669a750: and rcx, qword ptr [rbp + 0x1fc8]
669a757: mov rdi, qword ptr [rax + 0x250]
669a75e: mov rdx, qword ptr [rax + 0x260]
669a765: shl rcx, 4
669a769: mov rax, qword ptr [rdx + rcx + 8]
669a76e: cmp rax, rdi
669a771: mov r14, qword ptr [rbp + 0x1798]
669a778: je 0x669a828
669a77e: mov rcx, qword ptr [rdx + rcx]
669a782: movabs rdx, 0xff00000000000000
669a78c: and rdx, rsi
669a78f: mov r8, r14
669a792: shl r8, 0x30
669a796: or r8, rdx
669a799: mov rdx, qword ptr [rbp + 0x1828]
669a7a0: shl rdx, 0x28
669a7a4: or rdx, r8
669a7a7: mov r8, qword ptr [rbp + 0x1820]
669a7ae: shl r8, 0x20
669a7b2: or r8, rdx
669a7b5: mov rdx, qword ptr [rbp + 0x1818]
669a7bc: shl edx, 0x18
669a7bf: or rdx, r8
669a7c2: mov r8, qword ptr [rbp + 0x1810]
669a7c9: shl r8d, 0x10
669a7cd: or r8, rdx
669a7d0: mov rdx, qword ptr [rbp + 0x1f18]
669a7d7: shl edx, 8
669a7da: or rdx, r8
669a7dd: or rdx, qword ptr [rbp + 0x1f10]
669a7e4: mov r8, qword ptr [rbp + 0x1fc0]
669a7eb: cmp rdx, qword ptr [rax + 0x10]
669a7ef: jne 0x669a820
669a7f1: jmp 0x669a80a
669a7f3: nop word ptr cs:[rax + rax]
669a800: mov rax, qword ptr [rax + 8]
669a804: cmp rdx, qword ptr [rax + 0x10]
669a808: jne 0x669a820
669a80a: cmp word ptr [rax + 0x18], 0
669a80f: jne 0x669a820
669a811: cmp r8, qword ptr [rax + 0x20]
669a815: je 0x669e7f0
669a81b: nop dword ptr [rax + rax]
669a820: cmp rax, rcx
669a823: jne 0x669a800
669a825: mov rdi, rax
669a828: movabs rax, 0x555555555555555
669a832: mov rcx, qword ptr [rbp + 0x2078]
669a839: cmp qword ptr [rcx + 0x258], rax
669a840: je 0x669ea20
669a846: lea rax, [rcx + 0x250]
669a84d: mov qword ptr [rbp + 0x1bb0], rax
669a854: mov rcx, qword ptr [rip + 0xbca394d]
669a85b: mov rax, qword ptr [rcx]
669a85e: mov rax, qword ptr [rax + 8]
669a862: mov r8, qword ptr [rip + 0x9305737]
669a869: mov qword ptr [rbp + 0x1fb8], r12
669a870: mov edx, 0x30
669a875: call r8
669a878: nop 
669a879: mov r15, rax
669a87c: test rax, rax
669a87f: je 0x669cc05
669a885: mov qword ptr [rbp + 0x1bb8], r15
669a88c: movabs rax, 0xff00000000000000
669a896: and rsi, rax
669a899: shl r14, 0x30
669a89d: or r14, rsi
669a8a0: mov rax, qword ptr [rbp + 0x1828]
669a8a7: shl rax, 0x28
669a8ab: or rax, r14
669a8ae: mov rcx, qword ptr [rbp + 0x1820]
669a8b5: shl rcx, 0x20
669a8b9: or rcx, rax
669a8bc: mov rax, qword ptr [rbp + 0x1818]
669a8c3: shl eax, 0x18
669a8c6: or rax, rcx
669a8c9: mov rcx, qword ptr [rbp + 0x1810]
669a8d0: shl ecx, 0x10
669a8d3: or rcx, rax
669a8d6: mov rax, qword ptr [rbp + 0x1f18]
669a8dd: shl eax, 8
669a8e0: or rax, rcx
669a8e3: or rax, qword ptr [rbp + 0x1f10]
669a8ea: mov qword ptr [r15 + 0x10], rax
669a8ee: mov word ptr [r15 + 0x18], 0
669a8f5: mov rax, qword ptr [rbp + 0x1fc0]
669a8fc: mov qword ptr [r15 + 0x20], rax
669a900: mov qword ptr [r15 + 0x28], r12
669a904: mov rdx, qword ptr [rbp + 0x2078]
669a90b: mov rax, qword ptr [rdx + 0x258]
669a912: inc rax
669a915: js 0x669a91e
669a917: cvtsi2ss xmm0, rax
669a91c: jmp 0x669a933
669a91e: mov rcx, rax
669a921: shr rcx, 1
669a924: and eax, 1
669a927: or rax, rcx
669a92a: cvtsi2ss xmm0, rax
669a92f: addss xmm0, xmm0
669a933: mov r10, qword ptr [rbp + 0x1fc8]
669a93a: movss xmm1, dword ptr [rdx + 0x248]
669a942: mov r13, qword ptr [rdx + 0x280]
669a949: test r13, r13
669a94c: js 0x669a955
669a94e: cvtsi2ss xmm2, r13
669a953: jmp 0x669a96d
669a955: mov rax, r13
669a958: shr rax, 1
669a95b: mov ecx, r13d
669a95e: and ecx, 1
669a961: or rcx, rax
669a964: cvtsi2ss xmm2, rcx
669a969: addss xmm2, xmm2
669a96d: movaps xmm3, xmm0
669a970: divss xmm3, xmm2
669a974: ucomiss xmm3, xmm1
669a977: jbe 0x669af94
669a97d: divss xmm0, xmm1
669a981: call 0xeec73f0
669a986: cvttss2si rax, xmm0
669a98b: mov rcx, rax
669a98e: subss xmm0, dword ptr [rip + 0x884bd6a]
669a996: cvttss2si rdx, xmm0
669a99b: sar rcx, 0x3f
669a99f: and rdx, rcx
669a9a2: or rdx, rax
669a9a5: cmp rdx, 9
669a9a9: mov eax, 8
669a9ae: cmovae rax, rdx
669a9b2: cmp r13, rax
669a9b5: jae 0x669a9d4
669a9b7: lea rcx, [r13*8]
669a9bf: cmp rcx, rax
669a9c2: cmovbe rcx, rax
669a9c6: cmp r13, 0x200
669a9cd: cmovae rcx, rax
669a9d1: mov r13, rcx
669a9d4: movabs rax, 0x800000000000001
669a9de: cmp r13, rax
669a9e1: jae 0x669eab1
669a9e7: lea rax, [r13 - 1]
669a9eb: or rax, 1
669a9ef: bsr rcx, rax
669a9f3: inc rcx
669a9f6: mov edi, 1
669a9fb: shl rdi, cl
669a9fe: mov r9d, 2
669aa04: shl r9, cl
669aa07: mov rax, qword ptr [rbp + 0x2078]
669aa0e: mov rsi, qword ptr [rax + 0x250]
669aa15: mov rdx, qword ptr [rax + 0x260]
669aa1c: mov rax, qword ptr [rax + 0x268]
669aa23: mov r8, rax
669aa26: sub r8, rdx
669aa29: mov r10, r8
669aa2c: sar r10, 3
669aa30: cmp r10, r9
669aa33: jae 0x669ab1a
669aa39: mov r12d, 0x10
669aa3f: shl r12, cl
669aa42: cmp r13, 0x81
669aa49: jb 0x669ab40
669aa4f: lea r14, [r12 + 0x27]
669aa54: mov rcx, qword ptr [rip + 0xbca374d]
669aa5b: mov rax, qword ptr [rcx]
669aa5e: mov rax, qword ptr [rax + 8]
669aa62: mov rdx, r14
669aa65: call qword ptr [rip + 0x9305535]
669aa6b: nop 
669aa6c: mov r13, rax
669aa6f: test rax, rax
669aa72: je 0x669cc2c
669aa78: mov rax, r13
669aa7b: add r13, 0x27
669aa7f: and r13, 0xffffffffffffffe0
669aa83: mov qword ptr [r13 - 8], rax
669aa87: jmp 0x669ab64
669aa8c: mov rax, qword ptr [rsi]
669aa8f: mov qword ptr [rbp + 0x1880], rax
669aa96: mov qword ptr [rbp + 0x1888], 0
669aaa1: mov dword ptr [rsp + 0x28], 0
669aaa9: mov byte ptr [rsp + 0x20], 1
669aaae: lea r8, [rip + 0xc35df7b]
669aab5: lea rcx, [rbp + 0x1f28]
669aabc: lea rdx, [rbp + 0x1830]
669aac3: lea r9, [rbp + 0x1880]
669aaca: call 0xbcac390
669aacf: nop 
669aad0: mov r14, qword ptr [rbp + 0x1888]
669aad7: test r14, r14
669aada: je 0x6699732
669aae0: lock dec dword ptr [r14 + 8]
669aae5: jne 0x6699732
669aaeb: mov rax, qword ptr [r14]
669aaee: mov rax, qword ptr [rax]
669aaf1: mov rcx, r14
669aaf4: call qword ptr [rip + 0x93054a6]
669aafa: lock dec dword ptr [r14 + 0xc]
669aaff: jne 0x6699732
669ab05: mov rax, qword ptr [r14]
669ab08: mov rax, qword ptr [rax + 8]
669ab0c: mov rcx, r14
669ab0f: call qword ptr [rip + 0x930548b]
669ab15: jmp 0x6699732
669ab1a: cmp rdx, rax
669ab1d: mov r12, qword ptr [rbp + 0x2078]
669ab24: je 0x669ac9c
669ab2a: add r8, -8
669ab2e: cmp r8, 0x18
669ab32: jae 0x669ac4e
669ab38: mov rcx, rdx
669ab3b: jmp 0x669ac90
669ab40: mov rcx, qword ptr [rip + 0xbca3661]
669ab47: mov rax, qword ptr [rcx]
669ab4a: mov rax, qword ptr [rax + 8]
669ab4e: mov rdx, r12
669ab51: call qword ptr [rip + 0x9305449]
669ab57: nop 
669ab58: mov r13, rax
669ab5b: test rax, rax
669ab5e: je 0x669cc3a
669ab64: mov rax, qword ptr [rbp + 0x2078]
669ab6b: mov rcx, qword ptr [rax + 0x260]
669ab72: mov rdx, qword ptr [rax + 0x270]
669ab79: sub rdx, rcx
669ab7c: je 0x669aba8
669ab7e: cmp rdx, 0x1000
669ab85: jb 0x669aba3
669ab87: mov rax, qword ptr [rcx - 8]
669ab8b: add rcx, -8
669ab8f: sub rcx, rax
669ab92: cmp rcx, 0x20
669ab96: jae 0x669e7d7
669ab9c: add rdx, 0x27
669aba0: mov rcx, rax
669aba3: call 0xe935700
669aba8: mov rcx, qword ptr [rbp + 0x2078]
669abaf: mov qword ptr [rcx + 0x260], r13
669abb6: lea rax, [r12 + r13]
669abba: mov qword ptr [rcx + 0x268], rax
669abc1: mov qword ptr [rcx + 0x270], rax
669abc8: add r12, -8
669abcc: cmp r12, 0x18
669abd0: jae 0x669abde
669abd2: mov rcx, r13
669abd5: mov r12, qword ptr [rbp + 0x2078]
669abdc: jmp 0x669ac40
669abde: shr r12, 3
669abe2: inc r12
669abe5: mov rdx, r12
669abe8: and rdx, 0xfffffffffffffffc
669abec: lea rcx, [rdx*8]
669abf4: add rcx, r13
669abf7: movq xmm0, rsi
669abfc: pshufd xmm0, xmm0, 0x44
669ac01: xor r8d, r8d
669ac04: nop word ptr cs:[rax + rax]
669ac10: movdqu xmmword ptr [r13 + r8*8], xmm0
669ac17: movdqu xmmword ptr [r13 + r8*8 + 0x10], xmm0
669ac1e: add r8, 4
669ac22: cmp rdx, r8
669ac25: jne 0x669ac10
669ac27: cmp r12, rdx
669ac2a: mov r12, qword ptr [rbp + 0x2078]
669ac31: je 0x669ac9c
669ac33: nop word ptr cs:[rax + rax]
669ac40: mov qword ptr [rcx], rsi
669ac43: add rcx, 8
669ac47: cmp rcx, rax
669ac4a: jne 0x669ac40
669ac4c: jmp 0x669ac9c
669ac4e: shr r8, 3
669ac52: inc r8
669ac55: mov r9, r8
669ac58: and r9, 0xfffffffffffffffc
669ac5c: lea rcx, [rdx + r9*8]
669ac60: movq xmm0, rsi
669ac65: pshufd xmm0, xmm0, 0x44
669ac6a: xor r10d, r10d
669ac6d: movdqu xmmword ptr [rdx + r10*8], xmm0
669ac73: movdqu xmmword ptr [rdx + r10*8 + 0x10], xmm0
669ac7a: add r10, 4
669ac7e: cmp r9, r10
669ac81: jne 0x669ac6d
669ac83: cmp r8, r9
669ac86: je 0x669ac9c
669ac88: nop dword ptr [rax + rax]
669ac90: mov qword ptr [rcx], rsi
669ac93: add rcx, 8
669ac97: cmp rcx, rax
669ac9a: jne 0x669ac90
669ac9c: lea rcx, [rdi - 1]
669aca0: mov qword ptr [r12 + 0x278], rcx
669aca8: mov qword ptr [r12 + 0x280], rdi
669acb0: mov rdi, qword ptr [r12 + 0x250]
669acb8: mov rax, qword ptr [rdi]
669acbb: cmp rax, rsi
669acbe: je 0x669af2b
669acc4: movabs rcx, 0xcbf29ce484222325
669acce: mov edx, 0x9e3779b9
669acd3: jmp 0x669acf2
669acd5: nop word ptr cs:[rax + rax]
669ace0: mov qword ptr [r10 + r9], r8
669ace4: mov qword ptr [r10 + r9 + 8], r8
669ace9: cmp rax, rsi
669acec: je 0x669af1b
669acf2: mov r8, rax
669acf5: mov rax, qword ptr [rax]
669acf8: movzx r9d, byte ptr [r8 + 0x10]
669acfd: xor r9, rcx
669ad00: imul r9, rbx
669ad04: movzx r10d, byte ptr [r8 + 0x11]
669ad09: xor r10, r9
669ad0c: imul r10, rbx
669ad10: movzx r9d, byte ptr [r8 + 0x12]
669ad15: xor r9, r10
669ad18: imul r9, rbx
669ad1c: movzx r10d, byte ptr [r8 + 0x13]
669ad21: xor r10, r9
669ad24: imul r10, rbx
669ad28: movzx r9d, byte ptr [r8 + 0x14]
669ad2d: xor r9, r10
669ad30: imul r9, rbx
669ad34: movzx r10d, byte ptr [r8 + 0x15]
669ad39: xor r10, r9
669ad3c: imul r10, rbx
669ad40: movzx r11d, byte ptr [r8 + 0x16]
669ad45: xor r11, r10
669ad48: imul r11, rbx
669ad4c: movzx r9d, byte ptr [r8 + 0x17]
669ad51: xor r9, r11
669ad54: imul r9, rbx
669ad58: add r9, rdx
669ad5b: movzx r10d, byte ptr [r8 + 0x18]
669ad60: xor r10, rcx
669ad63: imul r10, rbx
669ad67: movzx r11d, byte ptr [r8 + 0x19]
669ad6c: xor r11, r10
669ad6f: imul r11, rbx
669ad73: mov rdi, r9
669ad76: shl rdi, 6
669ad7a: add rdi, r11
669ad7d: mov r10, r9
669ad80: shr r10, 2
669ad84: add r10, rdx
669ad87: add r10, rdi
669ad8a: xor r10, r9
669ad8d: movzx r9d, byte ptr [r8 + 0x20]
669ad92: xor r9, rcx
669ad95: imul r9, rbx
669ad99: movzx r11d, byte ptr [r8 + 0x21]
669ad9e: xor r11, r9
669ada1: imul r11, rbx
669ada5: movzx r9d, byte ptr [r8 + 0x22]
669adaa: xor r9, r11
669adad: imul r9, rbx
669adb1: movzx r11d, byte ptr [r8 + 0x23]
669adb6: xor r11, r9
669adb9: imul r11, rbx
669adbd: movzx r9d, byte ptr [r8 + 0x24]
669adc2: xor r9, r11
669adc5: imul r9, rbx
669adc9: movzx r11d, byte ptr [r8 + 0x25]
669adce: xor r11, r9
669add1: imul r11, rbx
669add5: movzx edi, byte ptr [r8 + 0x26]
669adda: xor rdi, r11
669addd: imul rdi, rbx
669ade1: movzx r9d, byte ptr [r8 + 0x27]
669ade6: xor r9, rdi
669ade9: imul r9, rbx
669aded: mov r11, r10
669adf0: shl r11, 6
669adf4: mov rdi, r10
669adf7: shr rdi, 2
669adfb: add rdi, r11
669adfe: add r9, rdx
669ae01: add r9, rdi
669ae04: xor r9, r10
669ae07: and r9, qword ptr [r12 + 0x278]
669ae0f: mov r10, qword ptr [r12 + 0x260]
669ae17: shl r9, 4
669ae1b: mov rdi, qword ptr [r10 + r9]
669ae1f: cmp rdi, rsi
669ae22: je 0x669ace0
669ae28: mov r11, qword ptr [r10 + r9 + 8]
669ae2d: mov r12, qword ptr [r8 + 0x10]
669ae31: cmp r12, qword ptr [r11 + 0x10]
669ae35: jne 0x669ae60
669ae37: movzx r13d, word ptr [r8 + 0x18]
669ae3c: cmp r13w, word ptr [r11 + 0x18]
669ae41: jne 0x669ae60
669ae43: mov r13, qword ptr [r8 + 0x20]
669ae47: cmp r13, qword ptr [r11 + 0x20]
669ae4b: je 0x669aee9
669ae51: nop word ptr cs:[rax + rax]
669ae60: cmp rdi, r11
669ae63: je 0x669aeb0
669ae65: mov r11, qword ptr [r11 + 8]
669ae69: cmp r12, qword ptr [r11 + 0x10]
669ae6d: jne 0x669ae60
669ae6f: movzx r13d, word ptr [r8 + 0x18]
669ae74: cmp r13w, word ptr [r11 + 0x18]
669ae79: jne 0x669ae60
669ae7b: mov r13, qword ptr [r8 + 0x20]
669ae7f: cmp r13, qword ptr [r11 + 0x20]
669ae83: jne 0x669ae60
669ae85: mov r9, qword ptr [r11]
669ae88: mov r10, qword ptr [r8 + 8]
669ae8c: mov qword ptr [r10], rax
669ae8f: mov r11, qword ptr [rax + 8]
669ae93: mov qword ptr [r11], r9
669ae96: mov rdi, qword ptr [r9 + 8]
669ae9a: mov qword ptr [rdi], r8
669ae9d: mov qword ptr [r9 + 8], r11
669aea1: mov qword ptr [rax + 8], r10
669aea5: mov qword ptr [r8 + 8], rdi
669aea9: jmp 0x669aed7
669aeab: nop dword ptr [rax + rax]
669aeb0: mov rdi, qword ptr [r8 + 8]
669aeb4: mov qword ptr [rdi], rax
669aeb7: mov r12, qword ptr [rax + 8]
669aebb: mov qword ptr [r12], r11
669aebf: mov r13, qword ptr [r11 + 8]
669aec3: mov qword ptr [r13], r8
669aec7: mov qword ptr [r11 + 8], r12
669aecb: mov qword ptr [rax + 8], rdi
669aecf: mov qword ptr [r8 + 8], r13
669aed3: mov qword ptr [r10 + r9], r8
669aed7: mov r12, qword ptr [rbp + 0x2078]
669aede: cmp rax, rsi
669aee1: jne 0x669acf2
669aee7: jmp 0x669af1b
669aee9: mov r11, qword ptr [r11]
669aeec: cmp r11, r8
669aeef: je 0x669af14
669aef1: mov rdi, qword ptr [r8 + 8]
669aef5: mov qword ptr [rdi], rax
669aef8: mov r12, qword ptr [rax + 8]
669aefc: mov qword ptr [r12], r11
669af00: mov r13, qword ptr [r11 + 8]
669af04: mov qword ptr [r13], r8
669af08: mov qword ptr [r11 + 8], r12
669af0c: mov qword ptr [rax + 8], rdi
669af10: mov qword ptr [r8 + 8], r13
669af14: mov qword ptr [r10 + r9 + 8], r8
669af19: jmp 0x669aed7
669af1b: mov rdi, qword ptr [r12 + 0x250]
669af23: mov rcx, qword ptr [r12 + 0x278]
669af2b: mov r10, qword ptr [rbp + 0x1fc8]
669af32: and rcx, r10
669af35: mov rdx, qword ptr [r12 + 0x260]
669af3d: shl rcx, 4
669af41: mov rax, qword ptr [rdx + rcx + 8]
669af46: cmp rax, rdi
669af49: je 0x669af94
669af4b: mov rcx, qword ptr [rdx + rcx]
669af4f: mov rdx, qword ptr [r15 + 0x10]
669af53: movzx r8d, word ptr [r15 + 0x18]
669af58: mov r9, qword ptr [r15 + 0x20]
669af5c: cmp rdx, qword ptr [rax + 0x10]
669af60: jne 0x669af87
669af62: jmp 0x669af7a
669af64: nop word ptr cs:[rax + rax]
669af70: mov rax, qword ptr [rax + 8]
669af74: cmp rdx, qword ptr [rax + 0x10]
669af78: jne 0x669af87
669af7a: cmp r8w, word ptr [rax + 0x18]
669af7f: jne 0x669af87
669af81: cmp r9, qword ptr [rax + 0x20]
669af85: je 0x669af91
669af87: cmp rax, rcx
669af8a: jne 0x669af70
669af8c: mov rdi, rax
669af8f: jmp 0x669af94
669af91: mov rdi, qword ptr [rax]
669af94: mov qword ptr [rbp + 0x1bb8], 0
669af9f: mov rcx, qword ptr [rdi + 8]
669afa3: mov r8, qword ptr [rbp + 0x2078]
669afaa: inc qword ptr [r8 + 0x258]
669afb1: mov qword ptr [r15], rdi
669afb4: mov qword ptr [r15 + 8], rcx
669afb8: mov qword ptr [rcx], r15
669afbb: mov qword ptr [rdi + 8], r15
669afbf: mov rax, qword ptr [r8 + 0x260]
669afc6: and r10, qword ptr [r8 + 0x278]
669afcd: shl r10, 4
669afd1: mov rdx, qword ptr [rax + r10]
669afd5: cmp rdx, qword ptr [r8 + 0x250]
669afdc: je 0x669afec
669afde: cmp rdx, rdi
669afe1: je 0x669aff7
669afe3: cmp qword ptr [rax + r10 + 8], rcx
669afe8: jne 0x669affb
669afea: jmp 0x669aff0
669afec: mov qword ptr [rax + r10], r15
669aff0: mov qword ptr [rax + r10 + 8], r15
669aff5: jmp 0x669affb
669aff7: mov qword ptr [rax + r10], r15
669affb: mov eax, dword ptr [rip + 0xc35da67]
669b001: mov ecx, dword ptr [rip + 0xc1db7c1]
669b007: mov rdx, qword ptr gs:[0x58]
669b010: mov rcx, qword ptr [rdx + rcx*8]
669b014: cmp eax, dword ptr [rcx + 4]
669b01a: jg 0x669e906
669b020: mov r9, qword ptr [r15 + 0x28]
669b024: lea r8, [rip + 0xc35da35]
669b02b: lea rdx, [rbp + 0x1bb0]
669b032: lea rcx, [rbp + 0x1f30]
669b039: call 0x56d55e0
669b03e: nop 
669b03f: mov rax, qword ptr [r15 + 0x28]
669b043: mov r14, qword ptr [rbp + 0x2068]
669b04a: movss xmm0, dword ptr [r14 + 0x38]
669b050: movss dword ptr [rax], xmm0
669b054: movss xmm0, dword ptr [r14 + 0x3c]
669b05a: movss dword ptr [rax + 4], xmm0
669b05f: movss xmm0, dword ptr [r14 + 0x40]
669b065: movss dword ptr [rax + 8], xmm0
669b06a: movss xmm0, dword ptr [r14 + 0x44]
669b070: movss dword ptr [rax + 0xc], xmm0
669b075: movss xmm0, dword ptr [r14 + 0x48]
669b07b: movss dword ptr [rax + 0x10], xmm0
669b080: movss xmm0, dword ptr [r14 + 0x4c]
669b086: movss dword ptr [rax + 0x14], xmm0
669b08b: movss xmm0, dword ptr [r14 + 0x50]
669b091: movss dword ptr [rax + 0x18], xmm0
669b096: movss xmm0, dword ptr [r14 + 0x54]
669b09c: movss dword ptr [rax + 0x1c], xmm0
669b0a1: movss xmm0, dword ptr [r14 + 0x58]
669b0a7: movss dword ptr [rax + 0x20], xmm0
669b0ac: movss xmm0, dword ptr [r14 + 0x5c]
669b0b2: movss dword ptr [rax + 0x24], xmm0
669b0b7: movss xmm0, dword ptr [r14 + 0x60]
669b0bd: movss dword ptr [rax + 0x28], xmm0
669b0c2: movss xmm0, dword ptr [r14 + 0x64]
669b0c8: movss dword ptr [rax + 0x2c], xmm0
669b0cd: movss xmm0, dword ptr [r14 + 0x68]
669b0d3: movss dword ptr [rax + 0x30], xmm0
669b0d8: movss xmm0, dword ptr [r14 + 0x6c]
669b0de: movss dword ptr [rax + 0x34], xmm0
669b0e3: movss xmm0, dword ptr [r14 + 0x70]
669b0e9: movss dword ptr [rax + 0x38], xmm0
669b0ee: movss xmm0, dword ptr [r14 + 0x74]
669b0f4: movss dword ptr [rax + 0x3c], xmm0
669b0f9: mov rax, qword ptr [rbp + 0x2060]
669b100: mov rax, qword ptr [rax + 0x10]
669b104: test byte ptr [rax + 0xa88], 1
669b10b: je 0x669b116
669b10d: mov rax, qword ptr [rax + 0xa80]
669b114: jmp 0x669b118
669b116: xor eax, eax
669b118: mov r13, qword ptr [rbp + 0x2078]
669b11f: mov rcx, qword ptr [rbp + 0x1f20]
669b126: mov rdx, qword ptr [r15 + 0x28]
669b12a: mov qword ptr [rdx + 0x40], rax
669b12e: call 0xeec5a10
669b133: movzx eax, byte ptr [r14 + 0x78]
669b138: test al, 8
669b13a: sete cl
669b13d: movzx esi, byte ptr [r14 + 0x7a]
669b142: add cl, cl
669b144: add cl, 2
669b147: cmp byte ptr [rbp + 0x2077], 0
669b14e: movzx ecx, cl
669b151: mov edi, 2
669b156: cmovne edi, ecx
669b159: test al, 8
669b15b: jne 0x669b181
669b15d: mov rax, qword ptr [r14 + 0x28]
669b161: mov rax, qword ptr [rax + 0x40]
669b165: movzx eax, byte ptr [rax + 0x1a8]
669b16c: xor ecx, ecx
669b16e: cmp al, 1
669b170: sete cl
669b173: add ecx, ecx
669b175: cmp al, 2
669b177: mov ebx, 1
669b17c: cmovne ebx, ecx
669b17f: jmp 0x669b198
669b181: mov rax, qword ptr [rbp + 0x2050]
669b188: shr eax, 0xb
669b18b: and eax, 1
669b18e: mov ecx, esi
669b190: xor cl, 1
669b193: and cl, al
669b195: movzx ebx, cl
669b198: lea rcx, [rbp + 0x1880]
669b19f: mov r8d, 0x330
669b1a5: xor edx, edx
669b1a7: call 0xeec6ed0
669b1ac: movzx eax, word ptr [r14 + 0x11c]
669b1b4: mov byte ptr [rbp + 0x19fa], 1
669b1bb: mov word ptr [rbp + 0x19f8], ax
669b1c2: movups xmm0, xmmword ptr [r14 + 0x158]
669b1ca: movups xmmword ptr [rbp + 0x19c8], xmm0
669b1d1: movsd xmm0, qword ptr [r14 + 0x168]
669b1da: movsd qword ptr [rbp + 0x19d8], xmm0
669b1e2: movups xmm0, xmmword ptr [r14 + 0x170]
669b1ea: movups xmmword ptr [rbp + 0x19e4], xmm0
669b1f1: mov byte ptr [rbp + 0x19f4], 1
669b1f8: mov rax, qword ptr [r14]
669b1fb: xorps xmm0, xmm0
669b1fe: movaps xmmword ptr [rbp + 0x17e0], xmm0
669b205: mov rcx, qword ptr [rax + 0x1b0]
669b20c: test rcx, rcx
669b20f: je 0x669b215
669b211: movzx ecx, word ptr [rcx + 0x10]
669b215: mov rcx, qword ptr [rax + 0x1b8]
669b21c: test rcx, rcx
669b21f: je 0x669b22e
669b221: lock inc dword ptr [rcx + 8]
669b225: mov rcx, qword ptr [rax + 0x1b8]
669b22c: jmp 0x669b230
669b22e: xor ecx, ecx
669b230: mov rax, qword ptr [rax + 0x1b0]
669b237: mov qword ptr [rbp + 0x17e0], rax
669b23e: mov r15, qword ptr [rbp + 0x17e8]
669b245: mov qword ptr [rbp + 0x17e8], rcx
669b24c: test r15, r15
669b24f: je 0x669b27e
669b251: lock dec dword ptr [r15 + 8]
669b256: jne 0x669b27e
669b258: mov rax, qword ptr [r15]
669b25b: mov rax, qword ptr [rax]
669b25e: mov rcx, r15
669b261: call qword ptr [rip + 0x9304d39]
669b267: lock dec dword ptr [r15 + 0xc]
669b26c: jne 0x669b27e
669b26e: mov rax, qword ptr [r15]
669b271: mov rax, qword ptr [rax + 8]
669b275: mov rcx, r15
669b278: call qword ptr [rip + 0x9304d22]
669b27e: mov r8, qword ptr [r13 + 0x3b8]
669b285: mov rax, qword ptr [rbp + 0x2060]
669b28c: mov rdx, qword ptr [rax]
669b28f: mov eax, dword ptr [rbp + 0x1eec]
669b295: mov dword ptr [rsp + 0x20], eax
669b299: mov dword ptr [rsp + 0x30], 0
669b2a1: mov dword ptr [rsp + 0x28], 0
669b2a9: lea rcx, [rbp + 0x1fd0]
669b2b0: lea r9, [rbp + 0x17e0]
669b2b7: call 0x66a0f60
669b2bc: nop 
669b2bd: movaps xmm0, xmmword ptr [rbp + 0x1fd0]
669b2c4: movaps xmm1, xmmword ptr [rbp + 0x1fe0]
669b2cb: mov qword ptr [rbp + 0x1fd8], 0
669b2d6: movaps xmmword ptr [rbp + 0x1bb0], xmm0
669b2dd: xorps xmm0, xmm0
669b2e0: movaps xmmword ptr [rbp + 0x1fe0], xmm0
669b2e7: movaps xmmword ptr [rbp + 0x1bc0], xmm1
669b2ee: mov rax, qword ptr [rbp + 0x1ff0]
669b2f5: mov qword ptr [rbp + 0x1bd0], rax
669b2fc: mov byte ptr [rbp + 0x1be8], 0xff
669b303: movzx eax, byte ptr [rbp + 0x2008]
669b30a: cmp rax, 3
669b30e: ja 0x669b380
669b310: lea rcx, [rbp + 0x1bd8]
669b317: lea rdx, [rip + 0x8c2448a]
669b31e: movsxd r8, dword ptr [rdx + rax*4]
669b322: add r8, rdx
669b325: jmp r8
669b328: mov rcx, qword ptr [rbp + 0x1ff8]
669b32f: mov qword ptr [rbp + 0x1bd8], rcx
669b336: jmp 0x669b37a
669b338: lea rdx, [rbp + 0x1ff8]
669b33f: movups xmm0, xmmword ptr [rdx]
669b342: movups xmmword ptr [rcx], xmm0
669b345: jmp 0x669b37a
669b347: movups xmmword ptr [rcx], xmm0
669b34a: mov rcx, qword ptr [rbp + 0x2000]
669b351: test rcx, rcx
669b354: je 0x669b363
669b356: lock inc dword ptr [rcx + 8]
669b35a: mov rcx, qword ptr [rbp + 0x2000]
669b361: jmp 0x669b365
669b363: xor ecx, ecx
669b365: mov rdx, qword ptr [rbp + 0x1ff8]
669b36c: mov qword ptr [rbp + 0x1bd8], rdx
669b373: mov qword ptr [rbp + 0x1be0], rcx
669b37a: mov byte ptr [rbp + 0x1be8], al
669b380: mov rax, qword ptr [rbp + 0x2020]
669b387: mov qword ptr [rbp + 0x1c00], rax
669b38e: movaps xmm0, xmmword ptr [rbp + 0x2010]
669b395: movaps xmmword ptr [rbp + 0x1bf0], xmm0
669b39c: lea rcx, [rbp + 0x1b50]
669b3a3: lea rdx, [rbp + 0x1bb0]
669b3aa: call 0x67d0750
669b3af: cmp byte ptr [rbp + 0x1be8], 3
669b3b6: jne 0x669b3f5
669b3b8: mov r12, qword ptr [rbp + 0x1be0]
669b3bf: test r12, r12
669b3c2: je 0x669b3f5
669b3c4: lock dec dword ptr [r12 + 8]
669b3ca: jne 0x669b3f5
669b3cc: mov rax, qword ptr [r12]
669b3d0: mov rax, qword ptr [rax]
669b3d3: mov rcx, r12
669b3d6: call qword ptr [rip + 0x9304bc4]
669b3dc: lock dec dword ptr [r12 + 0xc]
669b3e2: jne 0x669b3f5
669b3e4: mov rax, qword ptr [r12]
669b3e8: mov rax, qword ptr [rax + 8]
669b3ec: mov rcx, r12
669b3ef: call qword ptr [rip + 0x9304bab]
669b3f5: mov r14, qword ptr [rbp + 0x1bb8]
669b3fc: test r14, r14
669b3ff: je 0x669b45c
669b401: mov r15, qword ptr [rbp + 0x1bc0]
669b408: jmp 0x669b414
669b40a: nop word ptr [rax + rax]
669b410: add r14, 0x28
669b414: cmp r14, r15
669b417: je 0x669b45c
669b419: cmp byte ptr [r14 + 0x18], 2
669b41e: jne 0x669b410
669b420: mov r12, qword ptr [r14 + 8]
669b424: test r12, r12
669b427: je 0x669b410
669b429: lock dec dword ptr [r12 + 8]
669b42f: jne 0x669b410
669b431: mov rax, qword ptr [r12]
669b435: mov rax, qword ptr [rax]
669b438: mov rcx, r12
669b43b: call qword ptr [rip + 0x9304b5f]
669b441: lock dec dword ptr [r12 + 0xc]
669b447: jne 0x669b410
669b449: mov rax, qword ptr [r12]
669b44d: mov rax, qword ptr [rax + 8]
669b451: mov rcx, r12
669b454: call qword ptr [rip + 0x9304b46]
669b45a: jmp 0x669b410
669b45c: mov rax, qword ptr [rbp + 0x2068]
669b463: movups xmm0, xmmword ptr [rax + 0x38]
669b467: movaps xmmword ptr [rbp + 0x1830], xmm0
669b46e: movups xmm1, xmmword ptr [rax + 0x48]
669b472: movaps xmmword ptr [rbp + 0x1840], xmm1
669b479: movups xmm2, xmmword ptr [rax + 0x58]
669b47d: movaps xmmword ptr [rbp + 0x1850], xmm2
669b484: movups xmm3, xmmword ptr [rax + 0x68]
669b488: movaps xmmword ptr [rbp + 0x1860], xmm3
669b48f: mov byte ptr [rbp + 0x1870], 0
669b496: movaps xmmword ptr [rbp + 0x1bb0], xmm0
669b49d: movaps xmmword ptr [rbp + 0x1bc0], xmm1
669b4a4: movaps xmmword ptr [rbp + 0x1bd0], xmm2
669b4ab: movaps xmmword ptr [rbp + 0x1be0], xmm3
669b4b2: mov byte ptr [rbp + 0x1bf0], 0
669b4b9: lea rcx, [rbp + 0x1a70]
669b4c0: lea rdx, [rbp + 0x1bb0]
669b4c7: call 0x67d0b00
669b4cc: cmp byte ptr [rbp + 0x1bf0], 1
669b4d3: jne 0x669b515
669b4d5: mov rcx, qword ptr [rbp + 0x1bb0]
669b4dc: test rcx, rcx
669b4df: je 0x669b515
669b4e1: mov rdx, qword ptr [rbp + 0x1bc0]
669b4e8: sub rdx, rcx
669b4eb: cmp rdx, 0x1000
669b4f2: jb 0x669b510
669b4f4: mov rax, qword ptr [rcx - 8]
669b4f8: add rcx, -8
669b4fc: sub rcx, rax
669b4ff: cmp rcx, 0x20
669b503: jae 0x669e7d7
669b509: or rdx, 0x27
669b50d: mov rcx, rax
669b510: call 0xe935700
669b515: add esi, esi
669b517: mov byte ptr [rbp + 0x1a14], 7
669b51e: mov dword ptr [rbp + 0x1a18], ebx
669b524: mov byte ptr [rbp + 0x1a1c], 1
669b52b: mov byte ptr [rbp + 0x1a1e], dil
669b532: mov dword ptr [rbp + 0x1a20], 0
669b53c: cmp byte ptr [rbp + 0x1a68], 0
669b543: jne 0x669b54c
669b545: mov byte ptr [rbp + 0x1a68], 1
669b54c: mov byte ptr [rbp + 0x1a1d], 1
669b553: mov dword ptr [rbp + 0x1a38], 0
669b55d: mov qword ptr [rbp + 0x1a3c], 0
669b568: mov byte ptr [rbp + 0x1a44], 8
669b56f: mov qword ptr [rbp + 0x1a48], 0
669b57a: mov dword ptr [rbp + 0x1a50], 0
669b584: mov byte ptr [rbp + 0x1a54], 8
669b58b: mov qword ptr [rbp + 0x1a58], 0
669b596: mov qword ptr [rbp + 0x1a5e], 0
669b5a1: mov byte ptr [rbp + 0x1a66], 0xff
669b5a8: mov dword ptr [rbp + 0x1a10], esi
669b5ae: mov byte ptr [rbp + 0x1a24], 0
669b5b5: xorps xmm0, xmm0
669b5b8: movups xmmword ptr [rbp + 0x1a28], xmm0
669b5bf: mov rax, qword ptr [rbp + 0x1f28]
669b5c6: mov qword ptr [rbp + 0x1bb0], rax
669b5cd: lea rsi, [rbp + 0x1bb8]
669b5d4: mov rcx, rsi
669b5d7: lea rdx, [rbp + 0x1f30]
669b5de: call 0xe869ff0
669b5e3: nop 
669b5e4: mov rbx, qword ptr [rbp + 0x2060]
669b5eb: mov r15b, byte ptr [rbp + 0x2086]
669b5f2: mov rax, qword ptr [rbp + 0x1fa8]
669b5f9: mov qword ptr [rbp + 0x1c30], rax
669b600: mov qword ptr [rbp + 0x1fa8], 0
669b60b: movzx eax, byte ptr [rbp + 0x1b48]
669b612: mov rcx, qword ptr [rbp + 0x1bb0]
669b619: mov qword ptr [rbp + 0x1ac0], rcx
669b620: lea rcx, [rbp + 0x1ac8]
669b627: cmp al, 1
669b629: jne 0x669b64d
669b62b: mov rdx, rsi
669b62e: call 0xe86a0d0
669b633: nop 
669b634: mov rax, qword ptr [rbp + 0x1c30]
669b63b: mov qword ptr [rbp + 0x1b40], rax
669b642: cmp byte ptr [rbp + 0x2008], 3
669b649: je 0x669b674
669b64b: jmp 0x669b6ad
669b64d: mov rdx, rsi
669b650: call 0xe869ff0
669b655: nop 
669b656: mov rax, qword ptr [rbp + 0x1c30]
669b65d: mov qword ptr [rbp + 0x1b40], rax
669b664: mov byte ptr [rbp + 0x1b48], 1
669b66b: cmp byte ptr [rbp + 0x2008], 3
669b672: jne 0x669b6ad
669b674: mov r14, qword ptr [rbp + 0x2000]
669b67b: test r14, r14
669b67e: je 0x669b6ad
669b680: lock dec dword ptr [r14 + 8]
669b685: jne 0x669b6ad
669b687: mov rax, qword ptr [r14]
669b68a: mov rax, qword ptr [rax]
669b68d: mov rcx, r14
669b690: call qword ptr [rip + 0x930490a]
669b696: lock dec dword ptr [r14 + 0xc]
669b69b: jne 0x669b6ad
669b69d: mov rax, qword ptr [r14]
669b6a0: mov rax, qword ptr [rax + 8]
669b6a4: mov rcx, r14
669b6a7: call qword ptr [rip + 0x93048f3]
669b6ad: mov rsi, qword ptr [rbp + 0x1fd8]
669b6b4: test rsi, rsi
669b6b7: je 0x669b717
669b6b9: mov rdi, qword ptr [rbp + 0x1fe0]
669b6c0: jmp 0x669b6d4
669b6c2: nop word ptr cs:[rax + rax]
669b6d0: add rsi, 0x28
669b6d4: cmp rsi, rdi
669b6d7: je 0x669b717
669b6d9: cmp byte ptr [rsi + 0x18], 2
669b6dd: jne 0x669b6d0
669b6df: mov r14, qword ptr [rsi + 8]
669b6e3: test r14, r14
669b6e6: je 0x669b6d0
669b6e8: lock dec dword ptr [r14 + 8]
669b6ed: jne 0x669b6d0
669b6ef: mov rax, qword ptr [r14]
669b6f2: mov rax, qword ptr [rax]
669b6f5: mov rcx, r14
669b6f8: call qword ptr [rip + 0x93048a2]
669b6fe: lock dec dword ptr [r14 + 0xc]
669b703: jne 0x669b6d0
669b705: mov rax, qword ptr [r14]
669b708: mov rax, qword ptr [rax + 8]
669b70c: mov rcx, r14
669b70f: call qword ptr [rip + 0x930488b]
669b715: jmp 0x669b6d0
669b717: mov r8, qword ptr [rbp + 0x2068]
669b71e: cmp byte ptr [r8 + 0x79], 1
669b723: jne 0x669b911
669b729: cmp byte ptr [r8 + 0x150], 3
669b731: jne 0x669b98f
669b737: mov byte ptr [rbp + 0x1832], 0
669b73e: mov word ptr [rbp + 0x1830], 0
669b747: mov edi, dword ptr [r8 + 0x138]
669b74e: mov esi, dword ptr [r8 + 0x13c]
669b755: mov r14, qword ptr [rbx + 0x48]
669b759: mov rcx, qword ptr [rip + 0xbca2a48]
669b760: mov rax, qword ptr [rcx]
669b763: mov rax, qword ptr [rax + 8]
669b767: mov edx, 0x30
669b76c: call qword ptr [rip + 0x930482e]
669b772: nop 
669b773: mov r12, rax
669b776: test rax, rax
669b779: je 0x669cc1c
669b77f: movups xmm0, xmmword ptr [rip + 0x8f2b362]
669b786: movups xmmword ptr [r12 + 0x10], xmm0
669b78c: movups xmm0, xmmword ptr [rip + 0x8f2b345]
669b793: movups xmmword ptr [r12], xmm0
669b798: mov byte ptr [r12 + 0x20], 0
669b79e: mov dword ptr [rbp + 0x1bb0], edi
669b7a4: mov dword ptr [rbp + 0x1bb4], esi
669b7aa: mov dword ptr [rbp + 0x1bb8], 0x1c
669b7b4: movzx eax, word ptr [rbp + 0x1830]
669b7bb: mov word ptr [rbp + 0x1bbc], ax
669b7c2: movzx eax, byte ptr [rbp + 0x1832]
669b7c9: mov byte ptr [rbp + 0x1bbe], al
669b7cf: movabs rbx, 0x100000001
669b7d9: mov qword ptr [rbp + 0x1bc0], rbx
669b7e0: mov qword ptr [rbp + 0x1bc8], r12
669b7e7: mov qword ptr [rbp + 0x1bd0], 0
669b7f2: mov qword ptr [rbp + 0x1bd8], 0x20
669b7fd: mov qword ptr [rbp + 0x1be0], 0x2f
669b808: lea rdx, [rbp + 0x1fd0]
669b80f: lea r8, [rbp + 0x1bb0]
669b816: mov rcx, r14
669b819: call 0x5ab9970
669b81e: nop 
669b81f: mov r15, qword ptr [rbp + 0x1fd0]
669b826: mov r14, qword ptr [rbp + 0x1fd8]
669b82d: xorps xmm0, xmm0
669b830: movaps xmmword ptr [rbp + 0x1fd0], xmm0
669b837: mov rax, qword ptr [rbp + 0x1be0]
669b83e: cmp rax, 0x10
669b842: jb 0x669b87c
669b844: mov rcx, qword ptr [rbp + 0x1bc8]
669b84b: lea rdx, [rax + 1]
669b84f: cmp rdx, 0x1000
669b856: jb 0x669b877
669b858: mov r8, qword ptr [rcx - 8]
669b85c: add rcx, -8
669b860: sub rcx, r8
669b863: cmp rcx, 0x20
669b867: jae 0x669e7d7
669b86d: add rax, 0x28
669b871: mov rdx, rax
669b874: mov rcx, r8
669b877: call 0xe935700
669b87c: mov rax, qword ptr [rbp + 0x2068]
669b883: movzx eax, byte ptr [rax + 0x7b]
669b887: cmp byte ptr [rbp + 0x197c], 0
669b88e: jne 0x669b897
669b890: mov byte ptr [rbp + 0x197c], 1
669b897: mov dword ptr [rbp + 0x1978], eax
669b89d: mov eax, dword ptr [r13 + 0x3b0]
669b8a4: inc eax
669b8a6: mov word ptr [r13 + 0x3b0], ax
669b8ae: cmp byte ptr [rbp + 0x18c2], 0
669b8b5: jne 0x669b8be
669b8b7: mov byte ptr [rbp + 0x18c2], 1
669b8be: mov word ptr [rbp + 0x18c0], ax
669b8c5: test r14, r14
669b8c8: je 0x669b8cf
669b8ca: lock inc dword ptr [r14 + 8]
669b8cf: movzx eax, byte ptr [rbp + 0x1832]
669b8d6: mov byte ptr [rbp + 0x1fd2], al
669b8dc: movzx eax, word ptr [rbp + 0x1830]
669b8e3: mov word ptr [rbp + 0x1fd0], ax
669b8ea: mov rcx, qword ptr [rbp + 0x2068]
669b8f1: mov rax, qword ptr [rcx + 0x148]
669b8f8: test rax, rax
669b8fb: je 0x669bacf
669b901: lock inc dword ptr [rax + 8]
669b905: mov r12, qword ptr [rcx + 0x148]
669b90c: jmp 0x669bad2
669b911: cmp byte ptr [rbp + 0x2077], 0
669b918: jne 0x669b9f7
669b91e: cmp byte ptr [r8 + 0x7a], 1
669b923: jne 0x669ba27
669b929: movsd xmm0, qword ptr [r8 + 0x6c]
669b92f: movss xmm1, dword ptr [r8 + 0x68]
669b935: movss dword ptr [rbp + 0x1a00], xmm1
669b93d: cmp byte ptr [rbp + 0x1a0c], 0
669b944: jne 0x669b94d
669b946: mov byte ptr [rbp + 0x1a0c], 1
669b94d: movlps qword ptr [rbp + 0x1a04], xmm0
669b954: cmp byte ptr [rbp + 0x19b9], 0
669b95b: jne 0x669b964
669b95d: mov byte ptr [rbp + 0x19b9], 1
669b964: test byte ptr [r8 + 0x78], 0x20
669b969: jne 0x669be8a
669b96f: mov r14b, 2
669b972: mov si, 0x8800
669b976: cmp byte ptr [rbp + 0x19a1], 0
669b97d: jne 0x669bd5d
669b983: mov byte ptr [rbp + 0x19a1], 1
669b98a: jmp 0x669bd5d
669b98f: cmp byte ptr [rbp + 0x19b1], 0
669b996: jne 0x669b99f
669b998: mov byte ptr [rbp + 0x19b1], 1
669b99f: cmp byte ptr [rbp + 0x1981], 0
669b9a6: jne 0x669b9af
669b9a8: mov byte ptr [rbp + 0x1981], 1
669b9af: movzx eax, byte ptr [r8 + 0x7b]
669b9b4: cmp byte ptr [rbp + 0x197c], 0
669b9bb: jne 0x669b9c4
669b9bd: mov byte ptr [rbp + 0x197c], 1
669b9c4: mov dword ptr [rbp + 0x1978], eax
669b9ca: mov eax, dword ptr [r13 + 0x3b0]
669b9d1: inc eax
669b9d3: mov word ptr [r13 + 0x3b0], ax
669b9db: cmp byte ptr [rbp + 0x18c2], 0
669b9e2: jne 0x669b9eb
669b9e4: mov byte ptr [rbp + 0x18c2], 1
669b9eb: mov word ptr [rbp + 0x18c0], ax
669b9f2: jmp 0x669bd56
669b9f7: cmp byte ptr [r8 + 0x7b], 1
669b9fc: jne 0x669ba71
669b9fe: cmp byte ptr [rbp + 0x19a9], 0
669ba05: jne 0x669ba0e
669ba07: mov byte ptr [rbp + 0x19a9], 1
669ba0e: mov r14b, 4
669ba11: mov si, 0x9000
669ba15: cmp byte ptr [rbp + 0x1999], 0
669ba1c: jne 0x669bd5d
669ba22: jmp 0x669cb0b
669ba27: cmp byte ptr [r8 + 0x7b], 0
669ba2c: jne 0x669be56
669ba32: cmp byte ptr [r8 + 0x7d], 0
669ba37: jne 0x669be56
669ba3d: cmp byte ptr [rbp + 0x19c1], 0
669ba44: jne 0x669ba4d
669ba46: mov byte ptr [rbp + 0x19c1], 1
669ba4d: test byte ptr [r8 + 0x78], 0x20
669ba52: jne 0x669cb17
669ba58: cmp byte ptr [rbp + 0x18c9], 0
669ba5f: jne 0x669cb27
669ba65: mov byte ptr [rbp + 0x18c9], 1
669ba6c: jmp 0x669cb27
669ba71: mov eax, dword ptr [rbx + 0x70]
669ba74: dec eax
669ba76: cmp eax, 2
669ba79: setb dl
669ba7c: movzx ecx, byte ptr [r8 + 0x7a]
669ba81: and dl, cl
669ba83: cmp dl, 1
669ba86: jne 0x669beaa
669ba8c: movsd xmm0, qword ptr [r8 + 0x6c]
669ba92: movss xmm1, dword ptr [r8 + 0x68]
669ba98: movss dword ptr [rbp + 0x1a00], xmm1
669baa0: cmp byte ptr [rbp + 0x1a0c], 0
669baa7: jne 0x669bab0
669baa9: mov byte ptr [rbp + 0x1a0c], 1
669bab0: movlps qword ptr [rbp + 0x1a04], xmm0
669bab7: cmp byte ptr [rbp + 0x19b9], 0
669babe: jne 0x669bac7
669bac0: mov byte ptr [rbp + 0x19b9], 1
669bac7: mov r14b, 5
669baca: jmp 0x669cafa
669bacf: xor r12d, r12d
669bad2: mov rax, qword ptr [rcx + 0x140]
669bad9: test r14, r14
669badc: je 0x669bae3
669bade: lock inc dword ptr [r14 + 8]
669bae3: movzx ecx, byte ptr [rbp + 0x1fd2]
669baea: mov byte ptr [rbp + 0x1bb2], cl
669baf0: movzx ecx, word ptr [rbp + 0x1fd0]
669baf7: mov word ptr [rbp + 0x1bb0], cx
669bafe: cmp byte ptr [rbp + 0x18b8], 1
669bb05: jne 0x669bbfd
669bb0b: test r12, r12
669bb0e: je 0x669bb16
669bb10: lock inc dword ptr [r12 + 8]
669bb16: mov qword ptr [rbp + 0x1880], rax
669bb1d: mov r13, qword ptr [rbp + 0x1888]
669bb24: mov qword ptr [rbp + 0x1888], r12
669bb2b: test r13, r13
669bb2e: je 0x669bb5f
669bb30: lock dec dword ptr [r13 + 8]
669bb35: jne 0x669bb5f
669bb37: mov rax, qword ptr [r13]
669bb3b: mov rax, qword ptr [rax]
669bb3e: mov rcx, r13
669bb41: call qword ptr [rip + 0x9304459]
669bb47: lock dec dword ptr [r13 + 0xc]
669bb4c: jne 0x669bb5f
669bb4e: mov rax, qword ptr [r13]
669bb52: mov rax, qword ptr [rax + 8]
669bb56: mov rcx, r13
669bb59: call qword ptr [rip + 0x9304441]
669bb5f: test r14, r14
669bb62: je 0x669bb69
669bb64: lock inc dword ptr [r14 + 8]
669bb69: mov qword ptr [rbp + 0x1890], r15
669bb70: mov r13, qword ptr [rbp + 0x1898]
669bb77: mov qword ptr [rbp + 0x1898], r14
669bb7e: test r13, r13
669bb81: je 0x669bbb2
669bb83: lock dec dword ptr [r13 + 8]
669bb88: jne 0x669bbb2
669bb8a: mov rax, qword ptr [r13]
669bb8e: mov rax, qword ptr [rax]
669bb91: mov rcx, r13
669bb94: call qword ptr [rip + 0x9304406]
669bb9a: lock dec dword ptr [r13 + 0xc]
669bb9f: jne 0x669bbb2
669bba1: mov rax, qword ptr [r13]
669bba5: mov rax, qword ptr [rax + 8]
669bba9: mov rcx, r13
669bbac: call qword ptr [rip + 0x93043ee]
669bbb2: mov dword ptr [rbp + 0x18a0], edi
669bbb8: mov dword ptr [rbp + 0x18a4], esi
669bbbe: mov dword ptr [rbp + 0x18a8], 0x1c
669bbc8: movzx eax, word ptr [rbp + 0x1bb0]
669bbcf: mov word ptr [rbp + 0x18ac], ax
669bbd6: movzx eax, byte ptr [rbp + 0x1bb2]
669bbdd: mov byte ptr [rbp + 0x18ae], al
669bbe3: mov qword ptr [rbp + 0x18b0], rbx
669bbea: mov rbx, qword ptr [rbp + 0x2060]
669bbf1: mov r13, qword ptr [rbp + 0x2078]
669bbf8: jmp 0x669bc85
669bbfd: xorps xmm0, xmm0
669bc00: movaps xmmword ptr [rbp + 0x1880], xmm0
669bc07: test r12, r12
669bc0a: je 0x669bc12
669bc0c: lock inc dword ptr [r12 + 8]
669bc12: mov qword ptr [rbp + 0x1880], rax
669bc19: mov qword ptr [rbp + 0x1888], r12
669bc20: movaps xmmword ptr [rbp + 0x1890], xmm0
669bc27: test r14, r14
669bc2a: je 0x669bc31
669bc2c: lock inc dword ptr [r14 + 8]
669bc31: mov qword ptr [rbp + 0x1890], r15
669bc38: mov qword ptr [rbp + 0x1898], r14
669bc3f: mov dword ptr [rbp + 0x18a0], edi
669bc45: mov dword ptr [rbp + 0x18a4], esi
669bc4b: mov dword ptr [rbp + 0x18a8], 0x1c
669bc55: movzx eax, word ptr [rbp + 0x1bb0]
669bc5c: mov word ptr [rbp + 0x18ac], ax
669bc63: movzx eax, byte ptr [rbp + 0x1bb2]
669bc6a: mov byte ptr [rbp + 0x18ae], al
669bc70: mov qword ptr [rbp + 0x18b0], rbx
669bc77: mov byte ptr [rbp + 0x18b8], 1
669bc7e: mov rbx, qword ptr [rbp + 0x2060]
669bc85: movzx r15d, byte ptr [rbp + 0x2086]
669bc8d: test r14, r14
669bc90: je 0x669bcbf
669bc92: lock dec dword ptr [r14 + 8]
669bc97: jne 0x669bcbf
669bc99: mov rax, qword ptr [r14]
669bc9c: mov rax, qword ptr [rax]
669bc9f: mov rcx, r14
669bca2: call qword ptr [rip + 0x93042f8]
669bca8: lock dec dword ptr [r14 + 0xc]
669bcad: jne 0x669bcbf
669bcaf: mov rax, qword ptr [r14]
669bcb2: mov rax, qword ptr [rax + 8]
669bcb6: mov rcx, r14
669bcb9: call qword ptr [rip + 0x93042e1]
669bcbf: test r12, r12
669bcc2: je 0x669bcf5
669bcc4: lock dec dword ptr [r12 + 8]
669bcca: jne 0x669bcf5
669bccc: mov rax, qword ptr [r12]
669bcd0: mov rax, qword ptr [rax]
669bcd3: mov rcx, r12
669bcd6: call qword ptr [rip + 0x93042c4]
669bcdc: lock dec dword ptr [r12 + 0xc]
669bce2: jne 0x669bcf5
669bce4: mov rax, qword ptr [r12]
669bce8: mov rax, qword ptr [rax + 8]
669bcec: mov rcx, r12
669bcef: call qword ptr [rip + 0x93042ab]
669bcf5: test r14, r14
669bcf8: je 0x669bd56
669bcfa: lea rsi, [r14 + 8]
669bcfe: lock dec dword ptr [r14 + 8]
669bd03: jne 0x669bd2b
669bd05: mov rax, qword ptr [r14]
669bd08: mov rax, qword ptr [rax]
669bd0b: mov rcx, r14
669bd0e: call qword ptr [rip + 0x930428c]
669bd14: lock dec dword ptr [r14 + 0xc]
669bd19: jne 0x669bd2b
669bd1b: mov rax, qword ptr [r14]
669bd1e: mov rax, qword ptr [rax + 8]
669bd22: mov rcx, r14
669bd25: call qword ptr [rip + 0x9304275]
669bd2b: lock dec dword ptr [rsi]
669bd2e: jne 0x669bd56
669bd30: mov rax, qword ptr [r14]
669bd33: mov rax, qword ptr [rax]
669bd36: mov rcx, r14
669bd39: call qword ptr [rip + 0x9304261]
669bd3f: lock dec dword ptr [r14 + 0xc]
669bd44: jne 0x669bd56
669bd46: mov rax, qword ptr [r14]
669bd49: mov rax, qword ptr [rax + 8]
669bd4d: mov rcx, r14
669bd50: call qword ptr [rip + 0x930424a]
669bd56: mov si, 0x8000
669bd5a: xor r14d, r14d
669bd5d: test r15b, r15b
669bd60: je 0x669c2a6
669bd66: add r13, 0x1b0
669bd6d: mov rax, qword ptr [rbp + 0x2068]
669bd74: mov rdx, qword ptr [rax]
669bd77: mov rcx, rbx
669bd7a: mov r8, r13
669bd7d: call 0x6693850
669bd82: nop 
669bd83: test rax, rax
669bd86: je 0x669c2a6
669bd8c: mov rcx, qword ptr [rax + 8]
669bd90: test rcx, rcx
669bd93: je 0x669bded
669bd95: lock inc dword ptr [rcx + 8]
669bd99: mov rdi, qword ptr [rax]
669bd9c: mov rbx, qword ptr [rax + 8]
669bda0: test rbx, rbx
669bda3: je 0x669bddc
669bda5: lock dec dword ptr [rbx + 8]
669bda9: jne 0x669bddc
669bdab: mov rcx, qword ptr [rbx]
669bdae: mov rdx, qword ptr [rcx]
669bdb1: mov rcx, rbx
669bdb4: mov r15, rax
669bdb7: mov rax, rdx
669bdba: call qword ptr [rip + 0x93041e0]
669bdc0: mov rax, r15
669bdc3: lock dec dword ptr [rbx + 0xc]
669bdc7: jne 0x669bddc
669bdc9: mov rax, qword ptr [rbx]
669bdcc: mov rax, qword ptr [rax + 8]
669bdd0: mov rcx, rbx
669bdd3: call qword ptr [rip + 0x93041c7]
669bdd9: mov rax, r15
669bddc: test rdi, rdi
669bddf: mov rbx, qword ptr [rbp + 0x2060]
669bde6: jne 0x669bdf7
669bde8: jmp 0x669c2a6
669bded: cmp qword ptr [rax], 0
669bdf1: je 0x669c2a6
669bdf7: mov ecx, esi
669bdf9: or ecx, 0x4000
669bdff: test byte ptr [rbp + 0x2087], 0x40
669be06: cmove ecx, esi
669be09: test dword ptr [rbp + 0x2050], 0x800
669be13: je 0x669be2b
669be15: xorps xmm0, xmm0
669be18: movaps xmmword ptr [rbp + 0x17a0], xmm0
669be1f: lea r10, [rbp + 0x1fd0]
669be26: jmp 0x669bf30
669be2b: xorps xmm0, xmm0
669be2e: movaps xmmword ptr [rbp + 0x17a0], xmm0
669be35: mov r8, qword ptr [rbp + 0x2068]
669be3c: mov rdx, qword ptr [r8 + 0x10]
669be40: test rdx, rdx
669be43: je 0x669bf15
669be49: lock inc dword ptr [rdx + 8]
669be4d: mov rdx, qword ptr [r8 + 0x10]
669be51: jmp 0x669bf17
669be56: cmp byte ptr [rbp + 0x19a9], 0
669be5d: jne 0x669be66
669be5f: mov byte ptr [rbp + 0x19a9], 1
669be66: test byte ptr [r8 + 0x78], 0x20
669be6b: jne 0x669ca19
669be71: cmp byte ptr [rbp + 0x18c9], 0
669be78: jne 0x669ca29
669be7e: mov byte ptr [rbp + 0x18c9], 1
669be85: jmp 0x669ca29
669be8a: mov r14b, 2
669be8d: mov si, 0x8800
669be91: cmp byte ptr [rbp + 0x1991], 0
669be98: jne 0x669bd5d
669be9e: mov byte ptr [rbp + 0x1991], 1
669bea5: jmp 0x669bd5d
669beaa: cmp eax, 2
669bead: setae dl
669beb0: or dl, cl
669beb2: movsd xmm0, qword ptr [r8 + 0x6c]
669beb8: movss xmm1, dword ptr [r8 + 0x68]
669bebe: movzx eax, byte ptr [rbp + 0x1a0c]
669bec5: movss dword ptr [rbp + 0x1a00], xmm1
669becd: test dl, 1
669bed0: je 0x669cad5
669bed6: test al, al
669bed8: jne 0x669bee1
669beda: mov byte ptr [rbp + 0x1a0c], 1
669bee1: movlps qword ptr [rbp + 0x1a04], xmm0
669bee8: cmp byte ptr [rbp + 0x19b9], 0
669beef: jne 0x669bef8
669bef1: mov byte ptr [rbp + 0x19b9], 1
669bef8: mov si, 0x8000
669befc: cmp byte ptr [rbp + 0x1999], 0
669bf03: jne 0x669bd5a
669bf09: mov byte ptr [rbp + 0x1999], 1
669bf10: jmp 0x669bd5a
669bf15: xor edx, edx
669bf17: lea r10, [rbp + 0x1fd0]
669bf1e: mov r8, qword ptr [r8 + 8]
669bf22: mov qword ptr [rbp + 0x17a0], r8
669bf29: mov qword ptr [rbp + 0x17a8], rdx
669bf30: movaps xmmword ptr [rbp + 0x1260], xmm0
669bf37: mov rdx, qword ptr [rax + 8]
669bf3b: test rdx, rdx
669bf3e: je 0x669bf4a
669bf40: lock inc dword ptr [rdx + 8]
669bf44: mov rdx, qword ptr [rax + 8]
669bf48: jmp 0x669bf4c
669bf4a: xor edx, edx
669bf4c: mov rax, qword ptr [rax]
669bf4f: mov qword ptr [rbp + 0x1260], rax
669bf56: mov qword ptr [rbp + 0x1268], rdx
669bf5d: mov rax, qword ptr [rbp + 0x2068]
669bf64: mov r9, qword ptr [rax + 0x120]
669bf6b: movaps xmmword ptr [rbp + 0x1fd0], xmm0
669bf72: movaps xmmword ptr [rbp + 0x1830], xmm0
669bf79: lea rax, [rbp + 0x1830]
669bf80: mov qword ptr [rsp + 0x38], rax
669bf85: mov qword ptr [rsp + 0x30], r10
669bf8a: mov word ptr [rsp + 0x28], cx
669bf8f: lea rax, [rbp + 0x17a0]
669bf96: mov qword ptr [rsp + 0x20], rax
669bf9b: mov dword ptr [rsp + 0x48], 0xffffff00
669bfa3: mov dword ptr [rsp + 0x40], 0xffffff00
669bfab: lea rcx, [rbp + 0x1bb0]
669bfb2: lea rdx, [rbp + 0x1260]
669bfb9: mov r8d, r14d
669bfbc: call 0x673cc80
669bfc1: lea rcx, [rbp + 0x1910]
669bfc8: cmp byte ptr [rbp + 0x1970], 1
669bfcf: jne 0x669bfe9
669bfd1: lea rdx, [rbp + 0x1bb0]
669bfd8: call 0x67d1120
669bfdd: mov rdi, qword ptr [rbp + 0x1c00]
669bfe4: jmp 0x669c0f5
669bfe9: xorps xmm0, xmm0
669bfec: movups xmmword ptr [rcx], xmm0
669bfef: mov rax, qword ptr [rbp + 0x1bb8]
669bff6: test rax, rax
669bff9: je 0x669c008
669bffb: lock inc dword ptr [rax + 8]
669bfff: mov rax, qword ptr [rbp + 0x1bb8]
669c006: jmp 0x669c00a
669c008: xor eax, eax
669c00a: mov rcx, qword ptr [rbp + 0x1bb0]
669c011: mov qword ptr [rbp + 0x1910], rcx
669c018: mov qword ptr [rbp + 0x1918], rax
669c01f: movups xmm1, xmmword ptr [rbp + 0x1bc0]
669c026: movaps xmmword ptr [rbp + 0x1920], xmm1
669c02d: movzx eax, word ptr [rbp + 0x1bd0]
669c034: mov word ptr [rbp + 0x1930], ax
669c03b: movups xmmword ptr [rbp + 0x1938], xmm0
669c042: mov rax, qword ptr [rbp + 0x1be0]
669c049: test rax, rax
669c04c: je 0x669c05b
669c04e: lock inc dword ptr [rax + 8]
669c052: mov rax, qword ptr [rbp + 0x1be0]
669c059: jmp 0x669c05d
669c05b: xor eax, eax
669c05d: mov rdx, qword ptr [rbp + 0x1bd8]
669c064: mov rcx, qword ptr [rbp + 0x1bf0]
669c06b: mov qword ptr [rbp + 0x1938], rdx
669c072: mov qword ptr [rbp + 0x1940], rax
669c079: movups xmmword ptr [rbp + 0x1948], xmm0
669c080: test rcx, rcx
669c083: je 0x669c092
669c085: lock inc dword ptr [rcx + 8]
669c089: mov rax, qword ptr [rbp + 0x1bf0]
669c090: jmp 0x669c094
669c092: xor eax, eax
669c094: mov rdx, qword ptr [rbp + 0x1be8]
669c09b: mov rcx, qword ptr [rbp + 0x1c00]
669c0a2: mov qword ptr [rbp + 0x1948], rdx
669c0a9: mov qword ptr [rbp + 0x1950], rax
669c0b0: movups xmmword ptr [rbp + 0x1958], xmm0
669c0b7: test rcx, rcx
669c0ba: je 0x669c0c9
669c0bc: lock inc dword ptr [rcx + 8]
669c0c0: mov rdi, qword ptr [rbp + 0x1c00]
669c0c7: jmp 0x669c0cb
669c0c9: xor edi, edi
669c0cb: mov rax, qword ptr [rbp + 0x1bf8]
669c0d2: mov rcx, qword ptr [rbp + 0x1c08]
669c0d9: mov qword ptr [rbp + 0x1958], rax
669c0e0: mov qword ptr [rbp + 0x1960], rdi
669c0e7: mov qword ptr [rbp + 0x1968], rcx
669c0ee: mov byte ptr [rbp + 0x1970], 1
669c0f5: test rdi, rdi
669c0f8: je 0x669c125
669c0fa: lock dec dword ptr [rdi + 8]
669c0fe: jne 0x669c125
669c100: mov rax, qword ptr [rdi]
669c103: mov rax, qword ptr [rax]
669c106: mov rcx, rdi
669c109: call qword ptr [rip + 0x9303e91]
669c10f: lock dec dword ptr [rdi + 0xc]
669c113: jne 0x669c125
669c115: mov rax, qword ptr [rdi]
669c118: mov rax, qword ptr [rax + 8]
669c11c: mov rcx, rdi
669c11f: call qword ptr [rip + 0x9303e7b]
669c125: mov rdi, qword ptr [rbp + 0x1bf0]
669c12c: test rdi, rdi
669c12f: je 0x669c15c
669c131: lock dec dword ptr [rdi + 8]
669c135: jne 0x669c15c
669c137: mov rax, qword ptr [rdi]
669c13a: mov rax, qword ptr [rax]
669c13d: mov rcx, rdi
669c140: call qword ptr [rip + 0x9303e5a]
669c146: lock dec dword ptr [rdi + 0xc]
669c14a: jne 0x669c15c
669c14c: mov rax, qword ptr [rdi]
669c14f: mov rax, qword ptr [rax + 8]
669c153: mov rcx, rdi
669c156: call qword ptr [rip + 0x9303e44]
669c15c: mov rdi, qword ptr [rbp + 0x1be0]
669c163: test rdi, rdi
669c166: je 0x669c193
669c168: lock dec dword ptr [rdi + 8]
669c16c: jne 0x669c193
669c16e: mov rax, qword ptr [rdi]
669c171: mov rax, qword ptr [rax]
669c174: mov rcx, rdi
669c177: call qword ptr [rip + 0x9303e23]
669c17d: lock dec dword ptr [rdi + 0xc]
669c181: jne 0x669c193
669c183: mov rax, qword ptr [rdi]
669c186: mov rax, qword ptr [rax + 8]
669c18a: mov rcx, rdi
669c18d: call qword ptr [rip + 0x9303e0d]
669c193: mov rdi, qword ptr [rbp + 0x1bb8]
669c19a: test rdi, rdi
669c19d: je 0x669c1ca
669c19f: lock dec dword ptr [rdi + 8]
669c1a3: jne 0x669c1ca
669c1a5: mov rax, qword ptr [rdi]
669c1a8: mov rax, qword ptr [rax]
669c1ab: mov rcx, rdi
669c1ae: call qword ptr [rip + 0x9303dec]
669c1b4: lock dec dword ptr [rdi + 0xc]
669c1b8: jne 0x669c1ca
669c1ba: mov rax, qword ptr [rdi]
669c1bd: mov rax, qword ptr [rax + 8]
669c1c1: mov rcx, rdi
669c1c4: call qword ptr [rip + 0x9303dd6]
669c1ca: mov rdi, qword ptr [rbp + 0x1838]
669c1d1: test rdi, rdi
669c1d4: je 0x669c201
669c1d6: lock dec dword ptr [rdi + 8]
669c1da: jne 0x669c201
669c1dc: mov rax, qword ptr [rdi]
669c1df: mov rax, qword ptr [rax]
669c1e2: mov rcx, rdi
669c1e5: call qword ptr [rip + 0x9303db5]
669c1eb: lock dec dword ptr [rdi + 0xc]
669c1ef: jne 0x669c201
669c1f1: mov rax, qword ptr [rdi]
669c1f4: mov rax, qword ptr [rax + 8]
669c1f8: mov rcx, rdi
669c1fb: call qword ptr [rip + 0x9303d9f]
669c201: mov rdi, qword ptr [rbp + 0x1fd8]
669c208: test rdi, rdi
669c20b: je 0x669c238
669c20d: lock dec dword ptr [rdi + 8]
669c211: jne 0x669c238
669c213: mov rax, qword ptr [rdi]
669c216: mov rax, qword ptr [rax]
669c219: mov rcx, rdi
669c21c: call qword ptr [rip + 0x9303d7e]
669c222: lock dec dword ptr [rdi + 0xc]
669c226: jne 0x669c238
669c228: mov rax, qword ptr [rdi]
669c22b: mov rax, qword ptr [rax + 8]
669c22f: mov rcx, rdi
669c232: call qword ptr [rip + 0x9303d68]
669c238: mov rdi, qword ptr [rbp + 0x1268]
669c23f: test rdi, rdi
669c242: je 0x669c26f
669c244: lock dec dword ptr [rdi + 8]
669c248: jne 0x669c26f
669c24a: mov rax, qword ptr [rdi]
669c24d: mov rax, qword ptr [rax]
669c250: mov rcx, rdi
669c253: call qword ptr [rip + 0x9303d47]
669c259: lock dec dword ptr [rdi + 0xc]
669c25d: jne 0x669c26f
669c25f: mov rax, qword ptr [rdi]
669c262: mov rax, qword ptr [rax + 8]
669c266: mov rcx, rdi
669c269: call qword ptr [rip + 0x9303d31]
669c26f: mov rdi, qword ptr [rbp + 0x17a8]
669c276: test rdi, rdi
669c279: je 0x669c2a6
669c27b: lock dec dword ptr [rdi + 8]
669c27f: jne 0x669c2a6
669c281: mov rax, qword ptr [rdi]
669c284: mov rax, qword ptr [rax]
669c287: mov rcx, rdi
669c28a: call qword ptr [rip + 0x9303d10]
669c290: lock dec dword ptr [rdi + 0xc]
669c294: jne 0x669c2a6
669c296: mov rax, qword ptr [rdi]
669c299: mov rax, qword ptr [rax + 8]
669c29d: mov rcx, rdi
669c2a0: call qword ptr [rip + 0x9303cfa]
669c2a6: lea rax, [rip + 0x8c22b23]
669c2ad: mov qword ptr [rbp + 0x1bb0], rax
669c2b4: mov byte ptr [rbp + 0x1bf0], 0
669c2bb: cmp byte ptr [rbp + 0x18b8], 1
669c2c2: lea rax, [rbp + 0x1bb8]
669c2c9: jne 0x669c35f
669c2cf: xorps xmm0, xmm0
669c2d2: movups xmmword ptr [rax], xmm0
669c2d5: mov rax, qword ptr [rbp + 0x1888]
669c2dc: test rax, rax
669c2df: je 0x669c2ee
669c2e1: lock inc dword ptr [rax + 8]
669c2e5: mov rax, qword ptr [rbp + 0x1888]
669c2ec: jmp 0x669c2f0
669c2ee: xor eax, eax
669c2f0: mov rdx, qword ptr [rbp + 0x1880]
669c2f7: mov rcx, qword ptr [rbp + 0x1898]
669c2fe: mov qword ptr [rbp + 0x1bb8], rdx
669c305: mov qword ptr [rbp + 0x1bc0], rax
669c30c: movups xmmword ptr [rbp + 0x1bc8], xmm0
669c313: test rcx, rcx
669c316: je 0x669c325
669c318: lock inc dword ptr [rcx + 8]
669c31c: mov rax, qword ptr [rbp + 0x1898]
669c323: jmp 0x669c327
669c325: xor eax, eax
669c327: mov rcx, qword ptr [rbp + 0x1890]
669c32e: mov qword ptr [rbp + 0x1bc8], rcx
669c335: mov qword ptr [rbp + 0x1bd0], rax
669c33c: movaps xmm0, xmmword ptr [rbp + 0x18a0]
669c343: movups xmmword ptr [rbp + 0x1bd8], xmm0
669c34a: mov rax, qword ptr [rbp + 0x18b0]
669c351: mov qword ptr [rbp + 0x1be8], rax
669c358: mov byte ptr [rbp + 0x1bf0], 1
669c35f: mov eax, dword ptr [rbp + 0x18c0]
669c365: mov dword ptr [rbp + 0x1bf8], eax
669c36b: movzx eax, word ptr [rbp + 0x18c8]
669c372: mov word ptr [rbp + 0x1c00], ax
669c379: mov byte ptr [rbp + 0x1c38], 0
669c380: cmp byte ptr [rbp + 0x1900], 1
669c387: jne 0x669c3c2
669c389: lea rdx, [rbp + 0x18d0]
669c390: lea rcx, [rbp + 0x1c08]
669c397: lea rax, [rbp + 0x1c18]
669c39e: mov qword ptr [rbp + 0x1c08], rax
669c3a5: movabs rax, 0x100000000
669c3af: mov qword ptr [rbp + 0x1c10], rax
669c3b6: call 0x6764990
669c3bb: mov byte ptr [rbp + 0x1c38], 1
669c3c2: movzx eax, word ptr [rbp + 0x1908]
669c3c9: mov word ptr [rbp + 0x1c40], ax
669c3d0: lea rax, [rbp + 0x1c48]
669c3d7: mov byte ptr [rbp + 0x1ca8], 0
669c3de: cmp byte ptr [rbp + 0x1970], 1
669c3e5: jne 0x669c4f7
669c3eb: xorps xmm0, xmm0
669c3ee: movups xmmword ptr [rax], xmm0
669c3f1: mov rax, qword ptr [rbp + 0x1918]
669c3f8: test rax, rax
669c3fb: je 0x669c40a
669c3fd: lock inc dword ptr [rax + 8]
669c401: mov rax, qword ptr [rbp + 0x1918]
669c408: jmp 0x669c40c
669c40a: xor eax, eax
669c40c: mov rcx, qword ptr [rbp + 0x1910]
669c413: mov qword ptr [rbp + 0x1c48], rcx
669c41a: mov qword ptr [rbp + 0x1c50], rax
669c421: movaps xmm1, xmmword ptr [rbp + 0x1920]
669c428: movups xmmword ptr [rbp + 0x1c58], xmm1
669c42f: movzx eax, word ptr [rbp + 0x1930]
669c436: mov word ptr [rbp + 0x1c68], ax
669c43d: movups xmmword ptr [rbp + 0x1c70], xmm0
669c444: mov rax, qword ptr [rbp + 0x1940]
669c44b: test rax, rax
669c44e: je 0x669c45d
669c450: lock inc dword ptr [rax + 8]
669c454: mov rax, qword ptr [rbp + 0x1940]
669c45b: jmp 0x669c45f
669c45d: xor eax, eax
669c45f: mov rdx, qword ptr [rbp + 0x1938]
669c466: mov rcx, qword ptr [rbp + 0x1950]
669c46d: mov qword ptr [rbp + 0x1c70], rdx
669c474: mov qword ptr [rbp + 0x1c78], rax
669c47b: movups xmmword ptr [rbp + 0x1c80], xmm0
669c482: test rcx, rcx
669c485: je 0x669c494
669c487: lock inc dword ptr [rcx + 8]
669c48b: mov rax, qword ptr [rbp + 0x1950]
669c492: jmp 0x669c496
669c494: xor eax, eax
669c496: mov rdx, qword ptr [rbp + 0x1948]
669c49d: mov rcx, qword ptr [rbp + 0x1960]
669c4a4: mov qword ptr [rbp + 0x1c80], rdx
669c4ab: mov qword ptr [rbp + 0x1c88], rax
669c4b2: movups xmmword ptr [rbp + 0x1c90], xmm0
669c4b9: test rcx, rcx
669c4bc: je 0x669c4cb
669c4be: lock inc dword ptr [rcx + 8]
669c4c2: mov rax, qword ptr [rbp + 0x1960]
669c4c9: jmp 0x669c4cd
669c4cb: xor eax, eax
669c4cd: mov rcx, qword ptr [rbp + 0x1958]
669c4d4: mov rdx, qword ptr [rbp + 0x1968]
669c4db: mov qword ptr [rbp + 0x1c90], rcx
669c4e2: mov qword ptr [rbp + 0x1c98], rax
669c4e9: mov qword ptr [rbp + 0x1ca0], rdx
669c4f0: mov byte ptr [rbp + 0x1ca8], 1
669c4f7: mov rax, qword ptr [rbp + 0x1978]
669c4fe: mov qword ptr [rbp + 0x1cb0], rax
669c505: movzx eax, word ptr [rbp + 0x1980]
669c50c: mov word ptr [rbp + 0x1cb8], ax
669c513: movzx eax, word ptr [rbp + 0x1988]
669c51a: mov word ptr [rbp + 0x1cc0], ax
669c521: movzx eax, word ptr [rbp + 0x1990]
669c528: mov word ptr [rbp + 0x1cc8], ax
669c52f: movzx eax, word ptr [rbp + 0x1998]
669c536: mov word ptr [rbp + 0x1cd0], ax
669c53d: movzx eax, word ptr [rbp + 0x19a0]
669c544: mov word ptr [rbp + 0x1cd8], ax
669c54b: movzx eax, word ptr [rbp + 0x19a8]
669c552: mov word ptr [rbp + 0x1ce0], ax
669c559: movzx eax, word ptr [rbp + 0x19b0]
669c560: mov word ptr [rbp + 0x1ce8], ax
669c567: movzx eax, word ptr [rbp + 0x19b8]
669c56e: mov word ptr [rbp + 0x1cf0], ax
669c575: movzx eax, word ptr [rbp + 0x19c0]
669c57c: mov word ptr [rbp + 0x1cf8], ax
669c583: mov byte ptr [rbp + 0x1d2c], 0
669c58a: cmp byte ptr [rbp + 0x19f4], 1
669c591: jne 0x669c5dd
669c593: mov byte ptr [rbp + 0x1d18], 0xff
669c59a: cmp byte ptr [rbp + 0x19e0], 0xff
669c5a1: je 0x669c5c8
669c5a3: movups xmm0, xmmword ptr [rbp + 0x19c8]
669c5aa: movups xmmword ptr [rbp + 0x1d00], xmm0
669c5b1: movsd xmm0, qword ptr [rbp + 0x19d8]
669c5b9: movsd qword ptr [rbp + 0x1d10], xmm0
669c5c1: mov byte ptr [rbp + 0x1d18], 0
669c5c8: movups xmm0, xmmword ptr [rbp + 0x19e4]
669c5cf: movups xmmword ptr [rbp + 0x1d1c], xmm0
669c5d6: mov byte ptr [rbp + 0x1d2c], 1
669c5dd: mov eax, dword ptr [rbp + 0x19f8]
669c5e3: mov dword ptr [rbp + 0x1d30], eax
669c5e9: mov byte ptr [rbp + 0x1d44], 0
669c5f0: cmp byte ptr [rbp + 0x1a0c], 1
669c5f7: jne 0x669c620
669c5f9: movsd xmm0, qword ptr [rbp + 0x1a00]
669c601: movsd qword ptr [rbp + 0x1d38], xmm0
669c609: movss xmm0, dword ptr [rbp + 0x1a08]
669c611: movss dword ptr [rbp + 0x1d40], xmm0
669c619: mov byte ptr [rbp + 0x1d44], 1
669c620: mov byte ptr [rbp + 0x1da0], 0
669c627: cmp byte ptr [rbp + 0x1a68], 1
669c62e: jne 0x669c68d
669c630: lea rax, [rbp + 0x1a38]
669c637: mov ecx, dword ptr [rax - 0x18]
669c63a: mov dword ptr [rbp + 0x1d58], ecx
669c640: movups xmm0, xmmword ptr [rax - 0x28]
669c644: movups xmmword ptr [rbp + 0x1d48], xmm0
669c64b: movzx ecx, byte ptr [rbp + 0x1a24]
669c652: mov byte ptr [rbp + 0x1d5c], cl
669c658: movups xmm0, xmmword ptr [rbp + 0x1a28]
669c65f: movups xmmword ptr [rbp + 0x1d60], xmm0
669c666: movups xmm0, xmmword ptr [rax]
669c669: movups xmm1, xmmword ptr [rax + 0x10]
669c66d: movups xmm2, xmmword ptr [rax + 0x1f]
669c671: movups xmmword ptr [rbp + 0x1d70], xmm0
669c678: movups xmmword ptr [rbp + 0x1d80], xmm1
669c67f: movups xmmword ptr [rbp + 0x1d8f], xmm2
669c686: mov byte ptr [rbp + 0x1da0], 1
669c68d: mov byte ptr [rbp + 0x1df0], 0
669c694: cmp byte ptr [rbp + 0x1ab8], 1
669c69b: jne 0x669c748
669c6a1: mov byte ptr [rbp + 0x1de8], 0xff
669c6a8: movzx eax, byte ptr [rbp + 0x1ab0]
669c6af: movzx ecx, al
669c6b2: cmp ecx, 1
669c6b5: jg 0x669c6f5
669c6b7: test ecx, ecx
669c6b9: jne 0x669c70a
669c6bb: movaps xmm0, xmmword ptr [rbp + 0x1a70]
669c6c2: movaps xmm1, xmmword ptr [rbp + 0x1a80]
669c6c9: movaps xmm2, xmmword ptr [rbp + 0x1a90]
669c6d0: movaps xmm3, xmmword ptr [rbp + 0x1aa0]
669c6d7: movups xmmword ptr [rbp + 0x1da8], xmm0
669c6de: movups xmmword ptr [rbp + 0x1db8], xmm1
669c6e5: movups xmmword ptr [rbp + 0x1dc8], xmm2
669c6ec: movups xmmword ptr [rbp + 0x1dd8], xmm3
669c6f3: jmp 0x669c73b
669c6f5: cmp ecx, 2
669c6f8: jne 0x669c741
669c6fa: mov rcx, qword ptr [rbp + 0x1a70]
669c701: mov qword ptr [rbp + 0x1da8], rcx
669c708: jmp 0x669c73b
669c70a: mov rcx, qword ptr [rbp + 0x1a80]
669c711: mov qword ptr [rbp + 0x1a80], 0
669c71c: movaps xmm0, xmmword ptr [rbp + 0x1a70]
669c723: xorps xmm1, xmm1
669c726: movaps xmmword ptr [rbp + 0x1a70], xmm1
669c72d: movups xmmword ptr [rbp + 0x1da8], xmm0
669c734: mov qword ptr [rbp + 0x1db8], rcx
669c73b: mov byte ptr [rbp + 0x1de8], al
669c741: mov byte ptr [rbp + 0x1df0], 1
669c748: mov byte ptr [rbp + 0x1e80], 0
669c74f: cmp byte ptr [rbp + 0x1b48], 1
669c756: jne 0x669c79a
669c758: mov rax, qword ptr [rbp + 0x1ac0]
669c75f: mov qword ptr [rbp + 0x1df8], rax
669c766: lea rcx, [rbp + 0x1e00]
669c76d: lea rdx, [rbp + 0x1ac8]
669c774: call 0xe869ff0
669c779: nop 
669c77a: mov rax, qword ptr [rbp + 0x1b40]
669c781: mov qword ptr [rbp + 0x1e78], rax
669c788: mov qword ptr [rbp + 0x1b40], 0
669c793: mov byte ptr [rbp + 0x1e80], 1
669c79a: lea r10, [rbp + 0x1bf8]
669c7a1: lea r11, [rbp + 0x1c00]
669c7a8: lea rax, [rbp + 0x1c40]
669c7af: lea r12, [rbp + 0x1ce8]
669c7b6: lea r13, [rbp + 0x1cf0]
669c7bd: cmp byte ptr [rbp + 0x1ba8], 1
669c7c4: mov byte ptr [rbp + 0x1ee0], 0
669c7cb: lea rsi, [rbp + 0x1d00]
669c7d2: lea rdi, [rbp + 0x1d30]
669c7d9: lea r9, [rbp + 0x1da8]
669c7e0: jne 0x669c8cd
669c7e6: movaps xmm0, xmmword ptr [rbp + 0x1b50]
669c7ed: movaps xmm1, xmmword ptr [rbp + 0x1b60]
669c7f4: mov qword ptr [rbp + 0x1b58], 0
669c7ff: movups xmmword ptr [rbp + 0x1e88], xmm0
669c806: xorps xmm0, xmm0
669c809: movaps xmmword ptr [rbp + 0x1b60], xmm0
669c810: movups xmmword ptr [rbp + 0x1e98], xmm1
669c817: mov rcx, qword ptr [rbp + 0x1b70]
669c81e: mov qword ptr [rbp + 0x1ea8], rcx
669c825: mov byte ptr [rbp + 0x1ec0], 0xff
669c82c: movzx ecx, byte ptr [rbp + 0x1b88]
669c833: cmp rcx, 3
669c837: ja 0x669c8aa
669c839: lea r14, [rbp + 0x1eb0]
669c840: lea r8, [rip + 0x8c22f71]
669c847: movsxd rdx, dword ptr [r8 + rcx*4]
669c84b: add rdx, r8
669c84e: jmp rdx
669c850: mov rdx, qword ptr [rbp + 0x1b78]
669c857: mov qword ptr [rbp + 0x1eb0], rdx
669c85e: jmp 0x669c8a4
669c860: lea rdx, [rbp + 0x1b78]
669c867: movups xmm0, xmmword ptr [rdx]
669c86a: movups xmmword ptr [r14], xmm0
669c86e: jmp 0x669c8a4
669c870: movups xmmword ptr [r14], xmm0
669c874: mov rdx, qword ptr [rbp + 0x1b80]
669c87b: test rdx, rdx
669c87e: je 0x669c88d
669c880: lock inc dword ptr [rdx + 8]
669c884: mov rdx, qword ptr [rbp + 0x1b80]
669c88b: jmp 0x669c88f
669c88d: xor edx, edx
669c88f: mov r8, qword ptr [rbp + 0x1b78]
669c896: mov qword ptr [rbp + 0x1eb0], r8
669c89d: mov qword ptr [rbp + 0x1eb8], rdx
669c8a4: mov byte ptr [rbp + 0x1ec0], cl
669c8aa: mov rcx, qword ptr [rbp + 0x1ba0]
669c8b1: mov qword ptr [rbp + 0x1ed8], rcx
669c8b8: movaps xmm0, xmmword ptr [rbp + 0x1b90]
669c8bf: movups xmmword ptr [rbp + 0x1ec8], xmm0
669c8c6: mov byte ptr [rbp + 0x1ee0], 1
669c8cd: mov ecx, 0x9d0
669c8d2: add rcx, qword ptr [rbx + 0x10]
669c8d6: lea rbx, [rbp + 0x1c08]
669c8dd: lea r14, [rbp + 0x1d38]
669c8e4: lea r15, [rbp + 0x1d48]
669c8eb: lea r8, [rbp + 0x1df8]
669c8f2: lea rdx, [rbp + 0x1e88]
669c8f9: mov qword ptr [rsp + 0xb0], r10
669c901: mov qword ptr [rsp + 0xa8], r11
669c909: mov qword ptr [rsp + 0xa0], rbx
669c911: mov qword ptr [rsp + 0x98], rax
669c919: lea rax, [rbp + 0x1c48]
669c920: mov qword ptr [rsp + 0x90], rax
669c928: lea rax, [rbp + 0x1cb0]
669c92f: mov qword ptr [rsp + 0x88], rax
669c937: lea rax, [rbp + 0x1cb8]
669c93e: mov qword ptr [rsp + 0x80], rax
669c946: lea rax, [rbp + 0x1cc0]
669c94d: mov qword ptr [rsp + 0x78], rax
669c952: lea rax, [rbp + 0x1cc8]
669c959: mov qword ptr [rsp + 0x70], rax
669c95e: lea rax, [rbp + 0x1cd0]
669c965: mov qword ptr [rsp + 0x68], rax
669c96a: lea rax, [rbp + 0x1cd8]
669c971: mov qword ptr [rsp + 0x60], rax
669c976: lea rax, [rbp + 0x1ce0]
669c97d: mov qword ptr [rsp + 0x58], rax
669c982: mov qword ptr [rsp + 0x50], r12
669c987: mov qword ptr [rsp + 0x48], r13
669c98c: lea rax, [rbp + 0x1cf8]
669c993: mov qword ptr [rsp + 0x40], rax
669c998: mov qword ptr [rsp + 0x38], rsi
669c99d: mov qword ptr [rsp + 0x30], rdi
669c9a2: mov qword ptr [rsp + 0x28], r14
669c9a7: mov qword ptr [rsp + 0x20], r15
669c9ac: lea rax, [rbp + 0x1bb8]
669c9b3: mov qword ptr [rsp + 0xb8], rax
669c9bb: call 0x67d14e0
669c9c0: nop 
669c9c1: lea rax, [rip + 0x8c22408]
669c9c8: mov qword ptr [rbp + 0x1bb0], rax
669c9cf: lea rcx, [rbp + 0x1bb8]
669c9d6: call 0x675df40
669c9db: lea rcx, [rbp + 0x1880]
669c9e2: call 0x675df40
669c9e7: movaps xmm6, xmmword ptr [rbp + 0x2090]
669c9ee: movaps xmm7, xmmword ptr [rbp + 0x20a0]
669c9f5: movaps xmm8, xmmword ptr [rbp + 0x20b0]
669c9fd: movaps xmm9, xmmword ptr [rbp + 0x20c0]
669ca05: add rsp, 0x2158
669ca0c: pop rbx
669ca0d: pop rdi
669ca0e: pop rsi
669ca0f: pop r12
669ca11: pop r13
669ca13: pop r14
669ca15: pop r15
669ca17: pop rbp
669ca18: ret 
669ca19: cmp byte ptr [rbp + 0x1991], 0
669ca20: jne 0x669ca29
669ca22: mov byte ptr [rbp + 0x1991], 1
669ca29: mov r14b, 1
669ca2c: mov si, 0x8000
669ca30: cmp dword ptr [rbx + 0x70], 1
669ca34: jne 0x669bd5d
669ca3a: cmp byte ptr [rbp + 0x1909], 0
669ca41: jne 0x669ca4a
669ca43: mov byte ptr [rbp + 0x1909], 1
669ca4a: mov rax, qword ptr [rbp + 0x2068]
669ca51: movss xmm0, dword ptr [rax + 0x70]
669ca56: movsd xmm1, qword ptr [rax + 0x68]
669ca5b: movsd qword ptr [rbp + 0x1fd0], xmm1
669ca63: movss dword ptr [rbp + 0x1fd8], xmm0
669ca6b: lea rdi, [r13 + 0x470]
669ca72: lea rdx, [r13 + 0x480]
669ca79: lea r13, [rbp + 0x1bb0]
669ca80: mov rcx, r13
669ca83: call 0x66a17c0
669ca88: lea r12, [rbp + 0x1240]
669ca8f: mov rcx, r12
669ca92: mov rdx, r13
669ca95: mov r13, qword ptr [rbp + 0x2078]
669ca9c: call 0x66a1820
669caa1: nop 
669caa2: lea rcx, [rbp + 0x1880]
669caa9: lea r9, [rbp + 0x1fd0]
669cab0: mov rdx, r12
669cab3: mov r8, rdi
669cab6: call 0x66a1420
669cabb: nop 
669cabc: cmp byte ptr [rbp + 0x1989], 0
669cac3: jne 0x669bd5d
669cac9: mov byte ptr [rbp + 0x1989], 1
669cad0: jmp 0x669bd5d
669cad5: test al, al
669cad7: jne 0x669cae0
669cad9: mov byte ptr [rbp + 0x1a0c], 1
669cae0: movlps qword ptr [rbp + 0x1a04], xmm0
669cae7: cmp byte ptr [rbp + 0x19c1], 0
669caee: jne 0x669caf7
669caf0: mov byte ptr [rbp + 0x19c1], 1
669caf7: mov r14b, 3
669cafa: mov si, 0x8000
669cafe: cmp byte ptr [rbp + 0x1999], 0
669cb05: jne 0x669bd5d
669cb0b: mov byte ptr [rbp + 0x1999], 1
669cb12: jmp 0x669bd5d
669cb17: cmp byte ptr [rbp + 0x1991], 0
669cb1e: jne 0x669cb27
669cb20: mov byte ptr [rbp + 0x1991], 1
669cb27: mov si, 0x8000
669cb2b: cmp dword ptr [rbx + 0x70], 1
669cb2f: jne 0x669bd5a
669cb35: cmp byte ptr [rbp + 0x1909], 0
669cb3c: jne 0x669cb45
669cb3e: mov byte ptr [rbp + 0x1909], 1
669cb45: movss xmm0, dword ptr [r8 + 0x70]
669cb4b: movsd xmm1, qword ptr [r8 + 0x68]
669cb51: movsd qword ptr [rbp + 0x1fd0], xmm1
669cb59: movss dword ptr [rbp + 0x1fd8], xmm0
669cb61: lea r14, [r13 + 0x470]
669cb68: lea rdx, [r13 + 0x480]
669cb6f: lea r12, [rbp + 0x1bb0]
669cb76: mov rcx, r12
669cb79: call 0x66a17c0
669cb7e: lea r13, [rbp + 0x1250]
669cb85: mov rcx, r13
669cb88: mov rdx, r12
669cb8b: call 0x66a1820
669cb90: nop 
669cb91: lea rcx, [rbp + 0x1880]
669cb98: lea r9, [rbp + 0x1fd0]
669cb9f: mov rdx, r13
669cba2: mov r13, qword ptr [rbp + 0x2078]
669cba9: mov r8, r14
669cbac: call 0x66a1420
669cbb1: nop 
669cbb2: cmp byte ptr [rbp + 0x1989], 0
669cbb9: jne 0x669bd5a
669cbbf: mov byte ptr [rbp + 0x1989], 1
669cbc6: jmp 0x669bd5a
669cbcb: mov ecx, 0x20
669cbd0: mov rdi, rax
669cbd3: call 0x9bc830
669cbd8: mov rax, rdi
669cbdb: jmp 0x6699103
669cbe0: mov ecx, 0x20
669cbe5: mov rdi, rax
669cbe8: call 0x9bc830
669cbed: mov rax, rdi
669cbf0: jmp 0x6699194
669cbf5: mov ecx, 0x48
669cbfa: call 0x9bc830
669cbff: nop 
669cc00: jmp 0x669a71c
669cc05: mov qword ptr [rbp + 0x1fb8], r12
669cc0c: mov ecx, 0x30
669cc11: call 0x9bc830
669cc16: nop 
669cc17: jmp 0x669a885
669cc1c: mov ecx, 0x30
669cc21: call 0x9bc830
669cc26: nop 
669cc27: jmp 0x669b77f
669cc2c: mov rcx, r14
669cc2f: call 0x9bc830
669cc34: nop 
669cc35: jmp 0x669aa78
669cc3a: mov rcx, r12
669cc3d: call 0x9bc830
669cc42: nop 
669cc43: xor r13d, r13d
669cc46: jmp 0x669ab64
669cc4b: lea rcx, [rip + 0xc35b93e]
669cc52: call 0xe938cb0
669cc57: cmp dword ptr [rip + 0xc35b932], -1
669cc5e: jne 0x6698f94
669cc64: mov dword ptr [rbp + 0x1bb0], 0
669cc6e: lea rcx, [rip + 0xc35b71b]
669cc75: mov qword ptr [rbp + 0x17f8], rcx
669cc7c: lea rdx, [rbp + 0x1bb0]
669cc83: lea r15, [rbp + 0x1880]
669cc8a: mov r8, r15
669cc8d: call 0x9b020
669cc92: nop 
669cc93: mov qword ptr [rbp + 0x1838], 0
669cc9e: mov qword ptr [rbp + 0x1840], 0xe
669cca9: mov qword ptr [rbp + 0x1848], 0xf
669ccb4: movabs rax, 0x6c6f4369746c754d
669ccbe: mov qword ptr [rbp + 0x1830], rax
669ccc5: movabs rax, 0x746e6954726f6c6f
669cccf: mov qword ptr [rbp + 0x1836], rax
669ccd6: xorps xmm6, xmm6
669ccd9: movups xmmword ptr [rbp + 0x1850], xmm6
669cce0: mov qword ptr [rbp + 0x1860], 2
669cceb: mov qword ptr [rbp + 0x1868], 0xf
669ccf6: mov word ptr [rbp + 0x1850], 0x6e4f
669ccff: lea rax, [rbp + 0x1830]
669cd06: mov qword ptr [rbp + 0x12a8], rax
669cd0d: lea rax, [rbp + 0x1870]
669cd14: mov qword ptr [rbp + 0x12b0], rax
669cd1b: lea rcx, [rip + 0xc35b6ae]
669cd22: mov qword ptr [rbp + 0x1800], rcx
669cd29: lea rdx, [rbp + 0x12a8]
669cd30: call 0x7d7890
669cd35: nop 
669cd36: mov qword ptr [rbp + 0x17b0], 5
669cd41: mov qword ptr [rbp + 0x17b8], 0xf
669cd4c: mov qword ptr [rbp + 0x17a5], 0
669cd57: mov dword ptr [rbp + 0x17ac], 0
669cd61: mov ebx, dword ptr [rip + 0x8e80332]
669cd67: mov dword ptr [rbp + 0x17a0], ebx
669cd6d: mov sil, byte ptr [rip + 0x8e80329]
669cd74: mov byte ptr [rbp + 0x17a4], sil
669cd7b: movups xmmword ptr [rbp + 0x17c0], xmm6
669cd82: mov qword ptr [rbp + 0x17d0], 2
669cd8d: mov qword ptr [rbp + 0x17d8], 0xf
669cd98: mov word ptr [rbp + 0x17c0], 0x6e4f
669cda1: lea rax, [rbp + 0x17a0]
669cda8: mov qword ptr [rbp + 0x12b8], rax
669cdaf: lea rax, [rbp + 0x17e0]
669cdb6: mov qword ptr [rbp + 0x12c0], rax
669cdbd: lea rcx, [rip + 0xc35b64c]
669cdc4: mov qword ptr [rbp + 0x1808], rcx
669cdcb: lea rdx, [rbp + 0x12b8]
669cdd2: call 0x7d7890
669cdd7: nop 
669cdd8: mov qword ptr [rbp + 0x1890], 5
669cde3: mov qword ptr [rbp + 0x1898], 0xf
669cdee: mov qword ptr [rbp + 0x1885], 0
669cdf9: mov dword ptr [rbp + 0x188c], 0
669ce03: mov dword ptr [rbp + 0x1880], ebx
669ce09: mov byte ptr [rbp + 0x1884], sil
669ce10: xorps xmm0, xmm0
669ce13: movups xmmword ptr [rbp + 0x18a0], xmm0
669ce1a: mov qword ptr [rbp + 0x18b0], 2
669ce25: mov qword ptr [rbp + 0x18b8], 0xf
669ce30: mov word ptr [rbp + 0x18a0], 0x6e4f
669ce39: mov qword ptr [rbp + 0x18c8], 0
669ce44: mov qword ptr [rbp + 0x18d0], 0xe
669ce4f: mov qword ptr [rbp + 0x18d8], 0xf
669ce5a: movabs rax, 0x6c6f4369746c754d
669ce64: mov qword ptr [rbp + 0x18c0], rax
669ce6b: movabs rax, 0x746e6954726f6c6f
669ce75: mov qword ptr [rbp + 0x18c6], rax
669ce7c: movups xmmword ptr [rbp + 0x18e0], xmm0
669ce83: mov qword ptr [rbp + 0x18f0], 2
669ce8e: mov qword ptr [rbp + 0x18f8], 0xf
669ce99: mov word ptr [rbp + 0x18e0], 0x6e4f
669cea2: mov qword ptr [rbp + 0x12c8], r15
669cea9: lea rax, [rbp + 0x1900]
669ceb0: mov qword ptr [rbp + 0x12d0], rax
669ceb7: lea rcx, [rip + 0xc35b592]
669cebe: mov qword ptr [rbp + 0x1ef0], rcx
669cec5: lea rdx, [rbp + 0x12c8]
669cecc: call 0x7d7890
669ced1: nop 
669ced2: lea rax, [rip + 0xc35b5b7]
669ced9: mov rdi, rax
669cedc: mov qword ptr [rbp + 0x1ef0], rax
669cee3: lea rdx, [rip + 0x8f1af1d]
669ceea: lea r8, [rip + 0x8efbe49]
669cef1: lea r15, [rbp + 0x1260]
669cef8: mov rcx, r15
669cefb: call 0xf2ea00
669cf00: nop 
669cf01: mov qword ptr [rbp + 0x12d8], r15
669cf08: lea rax, [rbp + 0x12a0]
669cf0f: mov qword ptr [rbp + 0x12e0], rax
669cf16: mov qword ptr [rbp + 0x1ef8], rdi
669cf1d: lea rdx, [rbp + 0x12d8]
669cf24: mov rcx, rdi
669cf27: call 0x7d7890
669cf2c: nop 
669cf2d: lea r15, [rip + 0xc35b59c]
669cf34: mov qword ptr [rbp + 0x1ef8], r15
669cf3b: lea rdx, [rip + 0x8f1aec5]
669cf42: lea r8, [rip + 0x8efbdf1]
669cf49: lea rdi, [rbp + 0x1f28]
669cf50: mov rcx, rdi
669cf53: call 0xf2ea00
669cf58: nop 
669cf59: mov qword ptr [rbp + 0x1f70], 0
669cf64: mov qword ptr [rbp + 0x1f78], 0xe
669cf6f: mov qword ptr [rbp + 0x1f80], 0xf
669cf7a: movabs rax, 0x6c6f4369746c754d
669cf84: mov qword ptr [rbp + 0x1f68], rax
669cf8b: movabs rax, 0x746e6954726f6c6f
669cf95: mov qword ptr [rbp + 0x1f6e], rax
669cf9c: xorps xmm0, xmm0
669cf9f: movups xmmword ptr [rbp + 0x1f88], xmm0
669cfa6: mov qword ptr [rbp + 0x1f98], 2
669cfb1: mov qword ptr [rbp + 0x1fa0], 0xf
669cfbc: mov word ptr [rbp + 0x1f88], 0x6e4f
669cfc5: mov qword ptr [rbp + 0x12e8], rdi
669cfcc: lea rax, [rbp + 0x1fa8]
669cfd3: mov qword ptr [rbp + 0x12f0], rax
669cfda: mov qword ptr [rbp + 0x1f00], r15
669cfe1: lea rdx, [rbp + 0x12e8]
669cfe8: mov rcx, r15
669cfeb: call 0x7d7890
669cff0: nop 
669cff1: lea r15, [rip + 0xc35b518]
669cff8: mov qword ptr [rbp + 0x1f00], r15
669cfff: lea rdx, [rip + 0x8f1ae01]
669d006: lea r8, [rip + 0x8efbd2d]
669d00d: lea rdi, [rbp + 0x1fd0]
669d014: mov rcx, rdi
669d017: call 0xf2ea00
669d01c: nop 
669d01d: mov qword ptr [rbp + 0x2020], 5
669d028: mov qword ptr [rbp + 0x2028], 0xf
669d033: mov qword ptr [rbp + 0x2015], 0
669d03e: mov dword ptr [rbp + 0x201c], 0
669d048: mov dword ptr [rbp + 0x2010], ebx
669d04e: mov byte ptr [rbp + 0x2014], sil
669d055: xorps xmm0, xmm0
669d058: movups xmmword ptr [rbp + 0x2030], xmm0
669d05f: mov qword ptr [rbp + 0x2040], 2
669d06a: mov qword ptr [rbp + 0x2048], 0xf
669d075: mov word ptr [rbp + 0x2030], 0x6e4f
669d07e: mov qword ptr [rbp + 0x12f8], rdi
669d085: lea rax, [rbp + 0x2050]
669d08c: mov qword ptr [rbp + 0x1300], rax
669d093: mov qword ptr [rbp + 0x1f08], r15
669d09a: lea rdx, [rbp + 0x12f8]
669d0a1: mov rcx, r15
669d0a4: call 0x7d7890
669d0a9: nop 
669d0aa: lea rax, [rip + 0xc35b49f]
669d0b1: mov qword ptr [rbp + 0x1f08], rax
669d0b8: lea rdx, [rip + 0x8f1ad48]
669d0bf: lea r8, [rip + 0x8efbc74]
669d0c6: lea r15, [rbp + 0x1bb0]
669d0cd: mov rcx, r15
669d0d0: call 0xf2ea00
669d0d5: nop 
669d0d6: mov qword ptr [rbp + 0x1c00], 5
669d0e1: mov qword ptr [rbp + 0x1c08], 0xf
669d0ec: mov qword ptr [rbp + 0x1bf5], 0
669d0f7: mov dword ptr [rbp + 0x1bfc], 0
669d101: mov dword ptr [rbp + 0x1bf0], ebx
669d107: mov byte ptr [rbp + 0x1bf4], sil
669d10e: xorps xmm0, xmm0
669d111: movups xmmword ptr [rbp + 0x1c10], xmm0
669d118: mov qword ptr [rbp + 0x1c20], 2
669d123: mov qword ptr [rbp + 0x1c28], 0xf
669d12e: mov word ptr [rbp + 0x1c10], 0x6e4f
669d137: mov qword ptr [rbp + 0x1c38], 0
669d142: mov qword ptr [rbp + 0x1c40], 0xe
669d14d: mov qword ptr [rbp + 0x1c48], 0xf
669d158: movabs rax, 0x746e6954726f6c6f
669d162: mov qword ptr [rbp + 0x1c36], rax
669d169: movabs rax, 0x6c6f4369746c754d
669d173: mov qword ptr [rbp + 0x1c30], rax
669d17a: movups xmmword ptr [rbp + 0x1c50], xmm0
669d181: mov qword ptr [rbp + 0x1c60], 2
669d18c: mov qword ptr [rbp + 0x1c68], 0xf
669d197: mov word ptr [rbp + 0x1c50], 0x6e4f
669d1a0: mov qword ptr [rbp + 0x1308], r15
669d1a7: lea rax, [rbp + 0x1c70]
669d1ae: mov qword ptr [rbp + 0x1310], rax
669d1b5: lea rcx, [rip + 0xc35b394]
669d1bc: lea rdx, [rbp + 0x1308]
669d1c3: call 0x7d7890
669d1c8: nop 
669d1c9: lea rcx, [rbp + 0x1c30]
669d1d0: call 0x9b250
669d1d5: lea rcx, [rbp + 0x1bf0]
669d1dc: call 0x9b250
669d1e1: lea rcx, [rbp + 0x1bb0]
669d1e8: call 0x9b250
669d1ed: lea rcx, [rbp + 0x2010]
669d1f4: call 0x9b250
669d1f9: lea rcx, [rbp + 0x1fd0]
669d200: call 0x9b250
669d205: lea rcx, [rbp + 0x1f68]
669d20c: call 0x9b250
669d211: lea rcx, [rbp + 0x1f28]
669d218: call 0x9b250
669d21d: lea rcx, [rbp + 0x1260]
669d224: call 0x9b250
669d229: lea rcx, [rbp + 0x18c0]
669d230: call 0x9b250
669d235: lea rcx, [rbp + 0x1880]
669d23c: call 0x9b250
669d241: lea rcx, [rbp + 0x17a0]
669d248: call 0x9b250
669d24d: lea rcx, [rbp + 0x1830]
669d254: call 0x9b250
669d259: lea rcx, [rip + 0x2ed0]
669d260: call 0xe935740
669d265: lea rcx, [rip + 0xc35b324]
669d26c: call 0xe938d70
669d271: mov rdi, qword ptr [rbp + 0x2060]
669d278: mov rsi, qword ptr [rbp + 0x2050]
669d27f: jmp 0x6698f94
669d284: lea rcx, [rip + 0xc35b48d]
669d28b: call 0xe938cb0
669d290: cmp dword ptr [rip + 0xc35b481], -1
669d297: jne 0x6698fca
669d29d: mov rdi, rsi
669d2a0: lea rdx, [rip + 0xc35b0e9]
669d2a7: lea rcx, [rbp + 0x40]
669d2ab: lea r8, [rbp + 0x1bb0]
669d2b2: call 0xaa710
669d2b7: nop 
669d2b8: lea rsi, [rip + 0x8f57be8]
669d2bf: mov qword ptr [rbp + 0x1318], rsi
669d2c6: mov qword ptr [rbp + 0x1320], 0x12
669d2d1: lea rcx, [rip + 0xc35b2c0]
669d2d8: lea rdx, [rbp + 0x1318]
669d2df: lea r8, [rbp + 0x40]
669d2e3: call 0x66a02d0
669d2e8: nop 
669d2e9: lea rdx, [rip + 0xc35b0e0]
669d2f0: lea rcx, [rbp + 0x80]
669d2f7: lea r8, [rbp + 0x1bb0]
669d2fe: call 0xaa710
669d303: nop 
669d304: mov qword ptr [rbp + 0x1328], rsi
669d30b: mov qword ptr [rbp + 0x1330], 0x12
669d316: lea rcx, [rip + 0xc35b28b]
669d31d: lea rdx, [rbp + 0x1328]
669d324: lea r8, [rbp + 0x80]
669d32b: call 0x66a02d0
669d330: nop 
669d331: lea rdx, [rip + 0xc35b0d8]
669d338: lea rcx, [rbp + 0xc0]
669d33f: lea r8, [rbp + 0x1bb0]
669d346: call 0xaa710
669d34b: nop 
669d34c: mov qword ptr [rbp + 0x1338], rsi
669d353: mov qword ptr [rbp + 0x1340], 0x12
669d35e: lea rcx, [rip + 0xc35b253]
669d365: lea rdx, [rbp + 0x1338]
669d36c: lea r8, [rbp + 0xc0]
669d373: call 0x66a02d0
669d378: nop 
669d379: lea rdx, [rip + 0xc35b0d0]
669d380: lea rcx, [rbp + 0x100]
669d387: lea r8, [rbp + 0x1bb0]
669d38e: call 0xaa710
669d393: nop 
669d394: mov qword ptr [rbp + 0x1348], rsi
669d39b: mov qword ptr [rbp + 0x1350], 0x12
669d3a6: lea rcx, [rip + 0xc35b21b]
669d3ad: lea rdx, [rbp + 0x1348]
669d3b4: lea r8, [rbp + 0x100]
669d3bb: call 0x66a02d0
669d3c0: nop 
669d3c1: lea rdx, [rip + 0xc35b0c8]
669d3c8: lea rcx, [rbp + 0x140]
669d3cf: lea r8, [rbp + 0x1bb0]
669d3d6: call 0xaa710
669d3db: nop 
669d3dc: mov qword ptr [rbp + 0x1358], rsi
669d3e3: mov qword ptr [rbp + 0x1360], 0x12
669d3ee: lea rcx, [rip + 0xc35b1e3]
669d3f5: lea rdx, [rbp + 0x1358]
669d3fc: lea r8, [rbp + 0x140]
669d403: call 0x66a02d0
669d408: nop 
669d409: lea rdx, [rip + 0xc35b0c0]
669d410: lea rcx, [rbp + 0x180]
669d417: lea r8, [rbp + 0x1bb0]
669d41e: call 0xaa710
669d423: nop 
669d424: mov qword ptr [rbp + 0x1368], rsi
669d42b: mov qword ptr [rbp + 0x1370], 0x12
669d436: lea rcx, [rip + 0xc35b1ab]
669d43d: lea rdx, [rbp + 0x1368]
669d444: lea r8, [rbp + 0x180]
669d44b: call 0x66a02d0
669d450: nop 
669d451: lea rdx, [rip + 0xc35b0b8]
669d458: lea rcx, [rbp + 0x1c0]
669d45f: lea r8, [rbp + 0x1bb0]
669d466: call 0xaa710
669d46b: nop 
669d46c: mov qword ptr [rbp + 0x1378], rsi
669d473: mov qword ptr [rbp + 0x1380], 0x12
669d47e: lea rcx, [rip + 0xc35b173]
669d485: lea rdx, [rbp + 0x1378]
669d48c: lea r8, [rbp + 0x1c0]
669d493: call 0x66a02d0
669d498: nop 
669d499: lea rdx, [rip + 0xc35b0b0]
669d4a0: lea rcx, [rbp + 0x200]
669d4a7: lea r8, [rbp + 0x1bb0]
669d4ae: call 0xaa710
669d4b3: nop 
669d4b4: mov qword ptr [rbp + 0x1388], rsi
669d4bb: mov qword ptr [rbp + 0x1390], 0x12
669d4c6: lea rcx, [rip + 0xc35b13b]
669d4cd: lea rdx, [rbp + 0x1388]
669d4d4: lea r8, [rbp + 0x200]
669d4db: call 0x66a02d0
669d4e0: nop 
669d4e1: lea rdx, [rip + 0xc35aea8]
669d4e8: lea rcx, [rbp + 0x240]
669d4ef: lea r8, [rbp + 0x1bb0]
669d4f6: call 0xaa710
669d4fb: nop 
669d4fc: lea rsi, [rip + 0x8f5798a]
669d503: mov qword ptr [rbp + 0x1398], rsi
669d50a: mov qword ptr [rbp + 0x13a0], 0x19
669d515: lea rcx, [rip + 0xc35b0fc]
669d51c: lea rdx, [rbp + 0x1398]
669d523: lea r8, [rbp + 0x240]
669d52a: call 0x66a02d0
669d52f: nop 
669d530: lea rdx, [rip + 0xc35ae99]
669d537: lea rcx, [rbp + 0x280]
669d53e: lea r8, [rbp + 0x1bb0]
669d545: call 0xaa710
669d54a: nop 
669d54b: mov qword ptr [rbp + 0x13a8], rsi
669d552: mov qword ptr [rbp + 0x13b0], 0x19
669d55d: lea rcx, [rip + 0xc35b0c4]
669d564: lea rdx, [rbp + 0x13a8]
669d56b: lea r8, [rbp + 0x280]
669d572: call 0x66a02d0
669d577: nop 
669d578: lea rdx, [rip + 0xc35ae91]
669d57f: lea rcx, [rbp + 0x2c0]
669d586: lea r8, [rbp + 0x1bb0]
669d58d: call 0xaa710
669d592: nop 
669d593: mov qword ptr [rbp + 0x13b8], rsi
669d59a: mov qword ptr [rbp + 0x13c0], 0x19
669d5a5: lea rcx, [rip + 0xc35b08c]
669d5ac: lea rdx, [rbp + 0x13b8]
669d5b3: lea r8, [rbp + 0x2c0]
669d5ba: call 0x66a02d0
669d5bf: nop 
669d5c0: lea rdx, [rip + 0xc35ae89]
669d5c7: lea rcx, [rbp + 0x300]
669d5ce: lea r8, [rbp + 0x1bb0]
669d5d5: call 0xaa710
669d5da: nop 
669d5db: mov qword ptr [rbp + 0x13c8], rsi
669d5e2: mov qword ptr [rbp + 0x13d0], 0x19
669d5ed: lea rcx, [rip + 0xc35b054]
669d5f4: lea rdx, [rbp + 0x13c8]
669d5fb: lea r8, [rbp + 0x300]
669d602: call 0x66a02d0
669d607: nop 
669d608: lea rdx, [rip + 0xc35ae81]
669d60f: lea rcx, [rbp + 0x340]
669d616: lea r8, [rbp + 0x1bb0]
669d61d: call 0xaa710
669d622: nop 
669d623: mov qword ptr [rbp + 0x13d8], rsi
669d62a: mov qword ptr [rbp + 0x13e0], 0x19
669d635: lea rcx, [rip + 0xc35b01c]
669d63c: lea rdx, [rbp + 0x13d8]
669d643: lea r8, [rbp + 0x340]
669d64a: call 0x66a02d0
669d64f: nop 
669d650: lea rdx, [rip + 0xc35ae79]
669d657: lea rcx, [rbp + 0x380]
669d65e: lea r8, [rbp + 0x1bb0]
669d665: call 0xaa710
669d66a: nop 
669d66b: mov qword ptr [rbp + 0x13e8], rsi
669d672: mov qword ptr [rbp + 0x13f0], 0x19
669d67d: lea rcx, [rip + 0xc35afe4]
669d684: lea rdx, [rbp + 0x13e8]
669d68b: lea r8, [rbp + 0x380]
669d692: call 0x66a02d0
669d697: nop 
669d698: lea rdx, [rip + 0xc35ae71]
669d69f: lea rcx, [rbp + 0x3c0]
669d6a6: lea r8, [rbp + 0x1bb0]
669d6ad: call 0xaa710
669d6b2: nop 
669d6b3: mov qword ptr [rbp + 0x13f8], rsi
669d6ba: mov qword ptr [rbp + 0x1400], 0x19
669d6c5: lea rcx, [rip + 0xc35afac]
669d6cc: lea rdx, [rbp + 0x13f8]
669d6d3: lea r8, [rbp + 0x3c0]
669d6da: call 0x66a02d0
669d6df: nop 
669d6e0: lea rdx, [rip + 0xc35ae69]
669d6e7: lea rcx, [rbp + 0x400]
669d6ee: lea r8, [rbp + 0x1bb0]
669d6f5: call 0xaa710
669d6fa: nop 
669d6fb: mov qword ptr [rbp + 0x1408], rsi
669d702: mov qword ptr [rbp + 0x1410], 0x19
669d70d: lea rcx, [rip + 0xc35af74]
669d714: lea rdx, [rbp + 0x1408]
669d71b: lea r8, [rbp + 0x400]
669d722: call 0x66a02d0
669d727: nop 
669d728: lea rdx, [rip + 0xc35ac61]
669d72f: lea rcx, [rbp + 0x440]
669d736: lea r8, [rbp + 0x1bb0]
669d73d: call 0xaa710
669d742: nop 
669d743: lea rsi, [rip + 0x8f57770]
669d74a: mov qword ptr [rbp + 0x1418], rsi
669d751: mov qword ptr [rbp + 0x1420], 0x1c
669d75c: lea rcx, [rip + 0xc35af35]
669d763: lea rdx, [rbp + 0x1418]
669d76a: lea r8, [rbp + 0x440]
669d771: call 0x66a02d0
669d776: nop 
669d777: lea rdx, [rip + 0xc35ac52]
669d77e: lea rcx, [rbp + 0x480]
669d785: lea r8, [rbp + 0x1bb0]
669d78c: call 0xaa710
669d791: nop 
669d792: mov qword ptr [rbp + 0x1428], rsi
669d799: mov qword ptr [rbp + 0x1430], 0x1c
669d7a4: lea rcx, [rip + 0xc35aefd]
669d7ab: lea rdx, [rbp + 0x1428]
669d7b2: lea r8, [rbp + 0x480]
669d7b9: call 0x66a02d0
669d7be: nop 
669d7bf: lea rdx, [rip + 0xc35ac4a]
669d7c6: lea rcx, [rbp + 0x4c0]
669d7cd: lea r8, [rbp + 0x1bb0]
669d7d4: call 0xaa710
669d7d9: nop 
669d7da: mov qword ptr [rbp + 0x1438], rsi
669d7e1: mov qword ptr [rbp + 0x1440], 0x1c
669d7ec: lea rcx, [rip + 0xc35aec5]
669d7f3: lea rdx, [rbp + 0x1438]
669d7fa: lea r8, [rbp + 0x4c0]
669d801: call 0x66a02d0
669d806: nop 
669d807: lea rdx, [rip + 0xc35ac42]
669d80e: lea rcx, [rbp + 0x500]
669d815: lea r8, [rbp + 0x1bb0]
669d81c: call 0xaa710
669d821: nop 
669d822: mov qword ptr [rbp + 0x1448], rsi
669d829: mov qword ptr [rbp + 0x1450], 0x1c
669d834: lea rcx, [rip + 0xc35ae8d]
669d83b: lea rdx, [rbp + 0x1448]
669d842: lea r8, [rbp + 0x500]
669d849: call 0x66a02d0
669d84e: nop 
669d84f: lea rdx, [rip + 0xc35ac3a]
669d856: lea rcx, [rbp + 0x540]
669d85d: lea r8, [rbp + 0x1bb0]
669d864: call 0xaa710
669d869: nop 
669d86a: mov qword ptr [rbp + 0x1458], rsi
669d871: mov qword ptr [rbp + 0x1460], 0x1c
669d87c: lea rcx, [rip + 0xc35ae55]
669d883: lea rdx, [rbp + 0x1458]
669d88a: lea r8, [rbp + 0x540]
669d891: call 0x66a02d0
669d896: nop 
669d897: lea rdx, [rip + 0xc35ac32]
669d89e: lea rcx, [rbp + 0x580]
669d8a5: lea r8, [rbp + 0x1bb0]
669d8ac: call 0xaa710
669d8b1: nop 
669d8b2: mov qword ptr [rbp + 0x1468], rsi
669d8b9: mov qword ptr [rbp + 0x1470], 0x1c
669d8c4: lea rcx, [rip + 0xc35ae1d]
669d8cb: lea rdx, [rbp + 0x1468]
669d8d2: lea r8, [rbp + 0x580]
669d8d9: call 0x66a02d0
669d8de: nop 
669d8df: lea rdx, [rip + 0xc35ac2a]
669d8e6: lea rcx, [rbp + 0x5c0]
669d8ed: lea r8, [rbp + 0x1bb0]
669d8f4: call 0xaa710
669d8f9: nop 
669d8fa: mov qword ptr [rbp + 0x1478], rsi
669d901: mov qword ptr [rbp + 0x1480], 0x1c
669d90c: lea rcx, [rip + 0xc35ade5]
669d913: lea rdx, [rbp + 0x1478]
669d91a: lea r8, [rbp + 0x5c0]
669d921: call 0x66a02d0
669d926: nop 
669d927: lea rdx, [rip + 0xc35ac22]
669d92e: lea rcx, [rbp + 0x600]
669d935: lea r8, [rbp + 0x1bb0]
669d93c: call 0xaa710
669d941: nop 
669d942: mov qword ptr [rbp + 0x1488], rsi
669d949: mov qword ptr [rbp + 0x1490], 0x1c
669d954: lea rcx, [rip + 0xc35adad]
669d95b: lea rdx, [rbp + 0x1488]
669d962: lea r8, [rbp + 0x600]
669d969: call 0x66a02d0
669d96e: nop 
669d96f: lea rcx, [rip + 0xc35ada2]
669d976: call 0xe938d70
669d97b: mov rsi, rdi
669d97e: jmp 0x6698fca
669d983: lea rcx, [rip + 0xc35af16]
669d98a: call 0xe938cb0
669d98f: cmp dword ptr [rip + 0xc35af0a], -1
669d996: jne 0x6698fef
669d99c: mov rdi, rsi
669d99f: lea rdx, [rip + 0xc35a9ea]
669d9a6: lea rcx, [rbp + 0x640]
669d9ad: lea r8, [rbp + 0x1bb0]
669d9b4: call 0xaa710
669d9b9: nop 
669d9ba: lea rsi, [rip + 0x8ec632e]
669d9c1: mov qword ptr [rbp + 0x1498], rsi
669d9c8: mov qword ptr [rbp + 0x14a0], 0xf
669d9d3: lea rcx, [rip + 0xc35ad46]
669d9da: lea rdx, [rbp + 0x1498]
669d9e1: lea r8, [rbp + 0x640]
669d9e8: call 0x66a02d0
669d9ed: nop 
669d9ee: lea rdx, [rip + 0xc35a9db]
669d9f5: lea rcx, [rbp + 0x680]
669d9fc: lea r8, [rbp + 0x1bb0]
669da03: call 0xaa710
669da08: nop 
669da09: mov qword ptr [rbp + 0x14a8], rsi
669da10: mov qword ptr [rbp + 0x14b0], 0xf
669da1b: lea rcx, [rip + 0xc35ad0e]
669da22: lea rdx, [rbp + 0x14a8]
669da29: lea r8, [rbp + 0x680]
669da30: call 0x66a02d0
669da35: nop 
669da36: lea rdx, [rip + 0xc35a9d3]
669da3d: lea rcx, [rbp + 0x6c0]
669da44: lea r8, [rbp + 0x1bb0]
669da4b: call 0xaa710
669da50: nop 
669da51: mov qword ptr [rbp + 0x14b8], rsi
669da58: mov qword ptr [rbp + 0x14c0], 0xf
669da63: lea rcx, [rip + 0xc35acd6]
669da6a: lea rdx, [rbp + 0x14b8]
669da71: lea r8, [rbp + 0x6c0]
669da78: call 0x66a02d0
669da7d: nop 
669da7e: lea rdx, [rip + 0xc35a9cb]
669da85: lea rcx, [rbp + 0x700]
669da8c: lea r8, [rbp + 0x1bb0]
669da93: call 0xaa710
669da98: nop 
669da99: mov qword ptr [rbp + 0x14c8], rsi
669daa0: mov qword ptr [rbp + 0x14d0], 0xf
669daab: lea rcx, [rip + 0xc35ac9e]
669dab2: lea rdx, [rbp + 0x14c8]
669dab9: lea r8, [rbp + 0x700]
669dac0: call 0x66a02d0
669dac5: nop 
669dac6: lea rdx, [rip + 0xc35a9c3]
669dacd: lea rcx, [rbp + 0x740]
669dad4: lea r8, [rbp + 0x1bb0]
669dadb: call 0xaa710
669dae0: nop 
669dae1: mov qword ptr [rbp + 0x14d8], rsi
669dae8: mov qword ptr [rbp + 0x14e0], 0xf
669daf3: lea rcx, [rip + 0xc35ac66]
669dafa: lea rdx, [rbp + 0x14d8]
669db01: lea r8, [rbp + 0x740]
669db08: call 0x66a02d0
669db0d: nop 
669db0e: lea rdx, [rip + 0xc35a9bb]
669db15: lea rcx, [rbp + 0x780]
669db1c: lea r8, [rbp + 0x1bb0]
669db23: call 0xaa710
669db28: nop 
669db29: mov qword ptr [rbp + 0x14e8], rsi
669db30: mov qword ptr [rbp + 0x14f0], 0xf
669db3b: lea rcx, [rip + 0xc35ac2e]
669db42: lea rdx, [rbp + 0x14e8]
669db49: lea r8, [rbp + 0x780]
669db50: call 0x66a02d0
669db55: nop 
669db56: lea rdx, [rip + 0xc35a9b3]
669db5d: lea rcx, [rbp + 0x7c0]
669db64: lea r8, [rbp + 0x1bb0]
669db6b: call 0xaa710
669db70: nop 
669db71: mov qword ptr [rbp + 0x14f8], rsi
669db78: mov qword ptr [rbp + 0x1500], 0xf
669db83: lea rcx, [rip + 0xc35abf6]
669db8a: lea rdx, [rbp + 0x14f8]
669db91: lea r8, [rbp + 0x7c0]
669db98: call 0x66a02d0
669db9d: nop 
669db9e: lea rdx, [rip + 0xc35a9ab]
669dba5: lea rcx, [rbp + 0x800]
669dbac: lea r8, [rbp + 0x1bb0]
669dbb3: call 0xaa710
669dbb8: nop 
669dbb9: mov qword ptr [rbp + 0x1508], rsi
669dbc0: mov qword ptr [rbp + 0x1510], 0xf
669dbcb: lea rcx, [rip + 0xc35abbe]
669dbd2: lea rdx, [rbp + 0x1508]
669dbd9: lea r8, [rbp + 0x800]
669dbe0: call 0x66a02d0
669dbe5: nop 
669dbe6: lea rdx, [rip + 0xc35a7a3]
669dbed: lea rcx, [rbp + 0x840]
669dbf4: lea r8, [rbp + 0x1bb0]
669dbfb: call 0xaa710
669dc00: nop 
669dc01: lea rsi, [rip + 0x8eab5a8]
669dc08: mov qword ptr [rbp + 0x1518], rsi
669dc0f: mov qword ptr [rbp + 0x1520], 0x11
669dc1a: lea rcx, [rip + 0xc35ab7f]
669dc21: lea rdx, [rbp + 0x1518]
669dc28: lea r8, [rbp + 0x840]
669dc2f: call 0x66a02d0
669dc34: nop 
669dc35: lea rdx, [rip + 0xc35a794]
669dc3c: lea rcx, [rbp + 0x880]
669dc43: lea r8, [rbp + 0x1bb0]
669dc4a: call 0xaa710
669dc4f: nop 
669dc50: mov qword ptr [rbp + 0x1528], rsi
669dc57: mov qword ptr [rbp + 0x1530], 0x11
669dc62: lea rcx, [rip + 0xc35ab47]
669dc69: lea rdx, [rbp + 0x1528]
669dc70: lea r8, [rbp + 0x880]
669dc77: call 0x66a02d0
669dc7c: nop 
669dc7d: lea rdx, [rip + 0xc35a78c]
669dc84: lea rcx, [rbp + 0x8c0]
669dc8b: lea r8, [rbp + 0x1bb0]
669dc92: call 0xaa710
669dc97: nop 
669dc98: mov qword ptr [rbp + 0x1538], rsi
669dc9f: mov qword ptr [rbp + 0x1540], 0x11
669dcaa: lea rcx, [rip + 0xc35ab0f]
669dcb1: lea rdx, [rbp + 0x1538]
669dcb8: lea r8, [rbp + 0x8c0]
669dcbf: call 0x66a02d0
669dcc4: nop 
669dcc5: lea rdx, [rip + 0xc35a784]
669dccc: lea rcx, [rbp + 0x900]
669dcd3: lea r8, [rbp + 0x1bb0]
669dcda: call 0xaa710
669dcdf: nop 
669dce0: mov qword ptr [rbp + 0x1548], rsi
669dce7: mov qword ptr [rbp + 0x1550], 0x11
669dcf2: lea rcx, [rip + 0xc35aad7]
669dcf9: lea rdx, [rbp + 0x1548]
669dd00: lea r8, [rbp + 0x900]
669dd07: call 0x66a02d0
669dd0c: nop 
669dd0d: lea rdx, [rip + 0xc35a77c]
669dd14: lea rcx, [rbp + 0x940]
669dd1b: lea r8, [rbp + 0x1bb0]
669dd22: call 0xaa710
669dd27: nop 
669dd28: mov qword ptr [rbp + 0x1558], rsi
669dd2f: mov qword ptr [rbp + 0x1560], 0x11
669dd3a: lea rcx, [rip + 0xc35aa9f]
669dd41: lea rdx, [rbp + 0x1558]
669dd48: lea r8, [rbp + 0x940]
669dd4f: call 0x66a02d0
669dd54: nop 
669dd55: lea rdx, [rip + 0xc35a774]
669dd5c: lea rcx, [rbp + 0x980]
669dd63: lea r8, [rbp + 0x1bb0]
669dd6a: call 0xaa710
669dd6f: nop 
669dd70: mov qword ptr [rbp + 0x1568], rsi
669dd77: mov qword ptr [rbp + 0x1570], 0x11
669dd82: lea rcx, [rip + 0xc35aa67]
669dd89: lea rdx, [rbp + 0x1568]
669dd90: lea r8, [rbp + 0x980]
669dd97: call 0x66a02d0
669dd9c: nop 
669dd9d: lea rdx, [rip + 0xc35a76c]
669dda4: lea rcx, [rbp + 0x9c0]
669ddab: lea r8, [rbp + 0x1bb0]
669ddb2: call 0xaa710
669ddb7: nop 
669ddb8: mov qword ptr [rbp + 0x1578], rsi
669ddbf: mov qword ptr [rbp + 0x1580], 0x11
669ddca: lea rcx, [rip + 0xc35aa2f]
669ddd1: lea rdx, [rbp + 0x1578]
669ddd8: lea r8, [rbp + 0x9c0]
669dddf: call 0x66a02d0
669dde4: nop 
669dde5: lea rdx, [rip + 0xc35a764]
669ddec: lea rcx, [rbp + 0xa00]
669ddf3: lea r8, [rbp + 0x1bb0]
669ddfa: call 0xaa710
669ddff: nop 
669de00: mov qword ptr [rbp + 0x1588], rsi
669de07: mov qword ptr [rbp + 0x1590], 0x11
669de12: lea rcx, [rip + 0xc35a9f7]
669de19: lea rdx, [rbp + 0x1588]
669de20: lea r8, [rbp + 0xa00]
669de27: call 0x66a02d0
669de2c: nop 
669de2d: lea rdx, [rip + 0xc35a55c]
669de34: lea rcx, [rbp + 0xa40]
669de3b: lea r8, [rbp + 0x1bb0]
669de42: call 0xaa710
669de47: nop 
669de48: lea rsi, [rip + 0x912c485]
669de4f: mov qword ptr [rbp + 0x1598], rsi
669de56: mov qword ptr [rbp + 0x15a0], 0x14
669de61: lea rcx, [rip + 0xc35a9b8]
669de68: lea rdx, [rbp + 0x1598]
669de6f: lea r8, [rbp + 0xa40]
669de76: call 0x66a02d0
669de7b: nop 
669de7c: lea rdx, [rip + 0xc35a54d]
669de83: lea rcx, [rbp + 0xa80]
669de8a: lea r8, [rbp + 0x1bb0]
669de91: call 0xaa710
669de96: nop 
669de97: mov qword ptr [rbp + 0x15a8], rsi
669de9e: mov qword ptr [rbp + 0x15b0], 0x14
669dea9: lea rcx, [rip + 0xc35a980]
669deb0: lea rdx, [rbp + 0x15a8]
669deb7: lea r8, [rbp + 0xa80]
669debe: call 0x66a02d0
669dec3: nop 
669dec4: lea rdx, [rip + 0xc35a545]
669decb: lea rcx, [rbp + 0xac0]
669ded2: lea r8, [rbp + 0x1bb0]
669ded9: call 0xaa710
669dede: nop 
669dedf: mov qword ptr [rbp + 0x15b8], rsi
669dee6: mov qword ptr [rbp + 0x15c0], 0x14
669def1: lea rcx, [rip + 0xc35a948]
669def8: lea rdx, [rbp + 0x15b8]
669deff: lea r8, [rbp + 0xac0]
669df06: call 0x66a02d0
669df0b: nop 
669df0c: lea rdx, [rip + 0xc35a53d]
669df13: lea rcx, [rbp + 0xb00]
669df1a: lea r8, [rbp + 0x1bb0]
669df21: call 0xaa710
669df26: nop 
669df27: mov qword ptr [rbp + 0x15c8], rsi
669df2e: mov qword ptr [rbp + 0x15d0], 0x14
669df39: lea rcx, [rip + 0xc35a910]
669df40: lea rdx, [rbp + 0x15c8]
669df47: lea r8, [rbp + 0xb00]
669df4e: call 0x66a02d0
669df53: nop 
669df54: lea rdx, [rip + 0xc35a535]
669df5b: lea rcx, [rbp + 0xb40]
669df62: lea r8, [rbp + 0x1bb0]
669df69: call 0xaa710
669df6e: nop 
669df6f: mov qword ptr [rbp + 0x15d8], rsi
669df76: mov qword ptr [rbp + 0x15e0], 0x14
669df81: lea rcx, [rip + 0xc35a8d8]
669df88: lea rdx, [rbp + 0x15d8]
669df8f: lea r8, [rbp + 0xb40]
669df96: call 0x66a02d0
669df9b: nop 
669df9c: lea rdx, [rip + 0xc35a52d]
669dfa3: lea rcx, [rbp + 0xb80]
669dfaa: lea r8, [rbp + 0x1bb0]
669dfb1: call 0xaa710
669dfb6: nop 
669dfb7: mov qword ptr [rbp + 0x15e8], rsi
669dfbe: mov qword ptr [rbp + 0x15f0], 0x14
669dfc9: lea rcx, [rip + 0xc35a8a0]
669dfd0: lea rdx, [rbp + 0x15e8]
669dfd7: lea r8, [rbp + 0xb80]
669dfde: call 0x66a02d0
669dfe3: nop 
669dfe4: lea rdx, [rip + 0xc35a525]
669dfeb: lea rcx, [rbp + 0xbc0]
669dff2: lea r8, [rbp + 0x1bb0]
669dff9: call 0xaa710
669dffe: nop 
669dfff: mov qword ptr [rbp + 0x15f8], rsi
669e006: mov qword ptr [rbp + 0x1600], 0x14
669e011: lea rcx, [rip + 0xc35a868]
669e018: lea rdx, [rbp + 0x15f8]
669e01f: lea r8, [rbp + 0xbc0]
669e026: call 0x66a02d0
669e02b: nop 
669e02c: lea rdx, [rip + 0xc35a51d]
669e033: lea rcx, [rbp + 0xc00]
669e03a: lea r8, [rbp + 0x1bb0]
669e041: call 0xaa710
669e046: nop 
669e047: mov qword ptr [rbp + 0x1608], rsi
669e04e: mov qword ptr [rbp + 0x1610], 0x14
669e059: lea rcx, [rip + 0xc35a830]
669e060: lea rdx, [rbp + 0x1608]
669e067: lea r8, [rbp + 0xc00]
669e06e: call 0x66a02d0
669e073: nop 
669e074: lea rcx, [rip + 0xc35a825]
669e07b: call 0xe938d70
669e080: mov rsi, rdi
669e083: jmp 0x6698fef
669e088: lea rcx, [rip + 0xc35a999]
669e08f: call 0xe938cb0
669e094: cmp dword ptr [rip + 0xc35a98d], -1
669e09b: jne 0x6699014
669e0a1: mov rdi, rsi
669e0a4: lea rdx, [rip + 0xc35a2e5]
669e0ab: lea rcx, [rbp + 0xc40]
669e0b2: lea r8, [rbp + 0x1bb0]
669e0b9: call 0xaa710
669e0be: nop 
669e0bf: lea rsi, [rip + 0x8e93c7f]
669e0c6: mov qword ptr [rbp + 0x1618], rsi
669e0cd: mov qword ptr [rbp + 0x1620], 0x14
669e0d8: lea rcx, [rip + 0xc35a7c9]
669e0df: lea rdx, [rbp + 0x1618]
669e0e6: lea r8, [rbp + 0xc40]
669e0ed: call 0x66a02d0
669e0f2: nop 
669e0f3: lea rdx, [rip + 0xc35a2d6]
669e0fa: lea rcx, [rbp + 0xc80]
669e101: lea r8, [rbp + 0x1bb0]
669e108: call 0xaa710
669e10d: nop 
669e10e: mov qword ptr [rbp + 0x1628], rsi
669e115: mov qword ptr [rbp + 0x1630], 0x14
669e120: lea rcx, [rip + 0xc35a791]
669e127: lea rdx, [rbp + 0x1628]
669e12e: lea r8, [rbp + 0xc80]
669e135: call 0x66a02d0
669e13a: nop 
669e13b: lea rdx, [rip + 0xc35a2ce]
669e142: lea rcx, [rbp + 0xcc0]
669e149: lea r8, [rbp + 0x1bb0]
669e150: call 0xaa710
669e155: nop 
669e156: mov qword ptr [rbp + 0x1638], rsi
669e15d: mov qword ptr [rbp + 0x1640], 0x14
669e168: lea rcx, [rip + 0xc35a759]
669e16f: lea rdx, [rbp + 0x1638]
669e176: lea r8, [rbp + 0xcc0]
669e17d: call 0x66a02d0
669e182: nop 
669e183: lea rdx, [rip + 0xc35a2c6]
669e18a: lea rcx, [rbp + 0xd00]
669e191: lea r8, [rbp + 0x1bb0]
669e198: call 0xaa710
669e19d: nop 
669e19e: mov qword ptr [rbp + 0x1648], rsi
669e1a5: mov qword ptr [rbp + 0x1650], 0x14
669e1b0: lea rcx, [rip + 0xc35a721]
669e1b7: lea rdx, [rbp + 0x1648]
669e1be: lea r8, [rbp + 0xd00]
669e1c5: call 0x66a02d0
669e1ca: nop 
669e1cb: lea rdx, [rip + 0xc35a2be]
669e1d2: lea rcx, [rbp + 0xd40]
669e1d9: lea r8, [rbp + 0x1bb0]
669e1e0: call 0xaa710
669e1e5: nop 
669e1e6: mov qword ptr [rbp + 0x1658], rsi
669e1ed: mov qword ptr [rbp + 0x1660], 0x14
669e1f8: lea rcx, [rip + 0xc35a6e9]
669e1ff: lea rdx, [rbp + 0x1658]
669e206: lea r8, [rbp + 0xd40]
669e20d: call 0x66a02d0
669e212: nop 
669e213: lea rdx, [rip + 0xc35a2b6]
669e21a: lea rcx, [rbp + 0xd80]
669e221: lea r8, [rbp + 0x1bb0]
669e228: call 0xaa710
669e22d: nop 
669e22e: mov qword ptr [rbp + 0x1668], rsi
669e235: mov qword ptr [rbp + 0x1670], 0x14
669e240: lea rcx, [rip + 0xc35a6b1]
669e247: lea rdx, [rbp + 0x1668]
669e24e: lea r8, [rbp + 0xd80]
669e255: call 0x66a02d0
669e25a: nop 
669e25b: lea rdx, [rip + 0xc35a2ae]
669e262: lea rcx, [rbp + 0xdc0]
669e269: lea r8, [rbp + 0x1bb0]
669e270: call 0xaa710
669e275: nop 
669e276: mov qword ptr [rbp + 0x1678], rsi
669e27d: mov qword ptr [rbp + 0x1680], 0x14
669e288: lea rcx, [rip + 0xc35a679]
669e28f: lea rdx, [rbp + 0x1678]
669e296: lea r8, [rbp + 0xdc0]
669e29d: call 0x66a02d0
669e2a2: nop 
669e2a3: lea rdx, [rip + 0xc35a2a6]
669e2aa: lea rcx, [rbp + 0xe00]
669e2b1: lea r8, [rbp + 0x1bb0]
669e2b8: call 0xaa710
669e2bd: nop 
669e2be: mov qword ptr [rbp + 0x1688], rsi
669e2c5: mov qword ptr [rbp + 0x1690], 0x14
669e2d0: lea rcx, [rip + 0xc35a641]
669e2d7: lea rdx, [rbp + 0x1688]
669e2de: lea r8, [rbp + 0xe00]
669e2e5: call 0x66a02d0
669e2ea: nop 
669e2eb: lea rdx, [rip + 0xc35a09e]
669e2f2: lea rcx, [rbp + 0xe40]
669e2f9: lea r8, [rbp + 0x1bb0]
669e300: call 0xaa710
669e305: nop 
669e306: lea rsi, [rip + 0x8e93a16]
669e30d: mov qword ptr [rbp + 0x1698], rsi
669e314: mov qword ptr [rbp + 0x16a0], 0x16
669e31f: lea rcx, [rip + 0xc35a602]
669e326: lea rdx, [rbp + 0x1698]
669e32d: lea r8, [rbp + 0xe40]
669e334: call 0x66a02d0
669e339: nop 
669e33a: lea rdx, [rip + 0xc35a08f]
669e341: lea rcx, [rbp + 0xe80]
669e348: lea r8, [rbp + 0x1bb0]
669e34f: call 0xaa710
669e354: nop 
669e355: mov qword ptr [rbp + 0x16a8], rsi
669e35c: mov qword ptr [rbp + 0x16b0], 0x16
669e367: lea rcx, [rip + 0xc35a5ca]
669e36e: lea rdx, [rbp + 0x16a8]
669e375: lea r8, [rbp + 0xe80]
669e37c: call 0x66a02d0
669e381: nop 
669e382: lea rdx, [rip + 0xc35a087]
669e389: lea rcx, [rbp + 0xec0]
669e390: lea r8, [rbp + 0x1bb0]
669e397: call 0xaa710
669e39c: nop 
669e39d: mov qword ptr [rbp + 0x16b8], rsi
669e3a4: mov qword ptr [rbp + 0x16c0], 0x16
669e3af: lea rcx, [rip + 0xc35a592]
669e3b6: lea rdx, [rbp + 0x16b8]
669e3bd: lea r8, [rbp + 0xec0]
669e3c4: call 0x66a02d0
669e3c9: nop 
669e3ca: lea rdx, [rip + 0xc35a07f]
669e3d1: lea rcx, [rbp + 0xf00]
669e3d8: lea r8, [rbp + 0x1bb0]
669e3df: call 0xaa710
669e3e4: nop 
669e3e5: mov qword ptr [rbp + 0x16c8], rsi
669e3ec: mov qword ptr [rbp + 0x16d0], 0x16
669e3f7: lea rcx, [rip + 0xc35a55a]
669e3fe: lea rdx, [rbp + 0x16c8]
669e405: lea r8, [rbp + 0xf00]
669e40c: call 0x66a02d0
669e411: nop 
669e412: lea rdx, [rip + 0xc35a077]
669e419: lea rcx, [rbp + 0xf40]
669e420: lea r8, [rbp + 0x1bb0]
669e427: call 0xaa710
669e42c: nop 
669e42d: mov qword ptr [rbp + 0x16d8], rsi
669e434: mov qword ptr [rbp + 0x16e0], 0x16
669e43f: lea rcx, [rip + 0xc35a522]
669e446: lea rdx, [rbp + 0x16d8]
669e44d: lea r8, [rbp + 0xf40]
669e454: call 0x66a02d0
669e459: nop 
669e45a: lea rdx, [rip + 0xc35a06f]
669e461: lea rcx, [rbp + 0xf80]
669e468: lea r8, [rbp + 0x1bb0]
669e46f: call 0xaa710
669e474: nop 
669e475: mov qword ptr [rbp + 0x16e8], rsi
669e47c: mov qword ptr [rbp + 0x16f0], 0x16
669e487: lea rcx, [rip + 0xc35a4ea]
669e48e: lea rdx, [rbp + 0x16e8]
669e495: lea r8, [rbp + 0xf80]
669e49c: call 0x66a02d0
669e4a1: nop 
669e4a2: lea rdx, [rip + 0xc35a067]
669e4a9: lea rcx, [rbp + 0xfc0]
669e4b0: lea r8, [rbp + 0x1bb0]
669e4b7: call 0xaa710
669e4bc: nop 
669e4bd: mov qword ptr [rbp + 0x16f8], rsi
669e4c4: mov qword ptr [rbp + 0x1700], 0x16
669e4cf: lea rcx, [rip + 0xc35a4b2]
669e4d6: lea rdx, [rbp + 0x16f8]
669e4dd: lea r8, [rbp + 0xfc0]
669e4e4: call 0x66a02d0
669e4e9: nop 
669e4ea: lea rdx, [rip + 0xc35a05f]
669e4f1: lea rcx, [rbp + 0x1000]
669e4f8: lea r8, [rbp + 0x1bb0]
669e4ff: call 0xaa710
669e504: nop 
669e505: mov qword ptr [rbp + 0x1708], rsi
669e50c: mov qword ptr [rbp + 0x1710], 0x16
669e517: lea rcx, [rip + 0xc35a47a]
669e51e: lea rdx, [rbp + 0x1708]
669e525: lea r8, [rbp + 0x1000]
669e52c: call 0x66a02d0
669e531: nop 
669e532: lea rdx, [rip + 0xc359e57]
669e539: lea rcx, [rbp + 0x1040]
669e540: lea r8, [rbp + 0x1bb0]
669e547: call 0xaa710
669e54c: nop 
669e54d: lea rsi, [rip + 0x8e93818]
669e554: mov qword ptr [rbp + 0x1718], rsi
669e55b: mov qword ptr [rbp + 0x1720], 0x19
669e566: lea rcx, [rip + 0xc35a43b]
669e56d: lea rdx, [rbp + 0x1718]
669e574: lea r8, [rbp + 0x1040]
669e57b: call 0x66a02d0
669e580: nop 
669e581: lea rdx, [rip + 0xc359e48]
669e588: lea rcx, [rbp + 0x1080]
669e58f: lea r8, [rbp + 0x1bb0]
669e596: call 0xaa710
669e59b: nop 
669e59c: mov qword ptr [rbp + 0x1728], rsi
669e5a3: mov qword ptr [rbp + 0x1730], 0x19
669e5ae: lea rcx, [rip + 0xc35a403]
669e5b5: lea rdx, [rbp + 0x1728]
669e5bc: lea r8, [rbp + 0x1080]
669e5c3: call 0x66a02d0
669e5c8: nop 
669e5c9: lea rdx, [rip + 0xc359e40]
669e5d0: lea rcx, [rbp + 0x10c0]
669e5d7: lea r8, [rbp + 0x1bb0]
669e5de: call 0xaa710
669e5e3: nop 
669e5e4: mov qword ptr [rbp + 0x1738], rsi
669e5eb: mov qword ptr [rbp + 0x1740], 0x19
669e5f6: lea rcx, [rip + 0xc35a3cb]
669e5fd: lea rdx, [rbp + 0x1738]
669e604: lea r8, [rbp + 0x10c0]
669e60b: call 0x66a02d0
669e610: nop 
669e611: lea rdx, [rip + 0xc359e38]
669e618: lea rcx, [rbp + 0x1100]
669e61f: lea r8, [rbp + 0x1bb0]
669e626: call 0xaa710
669e62b: nop 
669e62c: mov qword ptr [rbp + 0x1748], rsi
669e633: mov qword ptr [rbp + 0x1750], 0x19
669e63e: lea rcx, [rip + 0xc35a393]
669e645: lea rdx, [rbp + 0x1748]
669e64c: lea r8, [rbp + 0x1100]
669e653: call 0x66a02d0
669e658: nop 
669e659: lea rdx, [rip + 0xc359e30]
669e660: lea rcx, [rbp + 0x1140]
669e667: lea r8, [rbp + 0x1bb0]
669e66e: call 0xaa710
669e673: nop 
669e674: mov qword ptr [rbp + 0x1758], rsi
669e67b: mov qword ptr [rbp + 0x1760], 0x19
669e686: lea rcx, [rip + 0xc35a35b]
669e68d: lea rdx, [rbp + 0x1758]
669e694: lea r8, [rbp + 0x1140]
669e69b: call 0x66a02d0
669e6a0: nop 
669e6a1: lea rdx, [rip + 0xc359e28]
669e6a8: lea rcx, [rbp + 0x1180]
669e6af: lea r8, [rbp + 0x1bb0]
669e6b6: call 0xaa710
669e6bb: nop 
669e6bc: mov qword ptr [rbp + 0x1768], rsi
669e6c3: mov qword ptr [rbp + 0x1770], 0x19
669e6ce: lea rcx, [rip + 0xc35a323]
669e6d5: lea rdx, [rbp + 0x1768]
669e6dc: lea r8, [rbp + 0x1180]
669e6e3: call 0x66a02d0
669e6e8: nop 
669e6e9: lea rdx, [rip + 0xc359e20]
669e6f0: lea rcx, [rbp + 0x11c0]
669e6f7: lea r8, [rbp + 0x1bb0]
669e6fe: call 0xaa710
669e703: nop 
669e704: mov qword ptr [rbp + 0x1778], rsi
669e70b: mov qword ptr [rbp + 0x1780], 0x19
669e716: lea rcx, [rip + 0xc35a2eb]
669e71d: lea rdx, [rbp + 0x1778]
669e724: lea r8, [rbp + 0x11c0]
669e72b: call 0x66a02d0
669e730: nop 
669e731: lea rdx, [rip + 0xc359e18]
669e738: lea rcx, [rbp + 0x1200]
669e73f: lea r8, [rbp + 0x1bb0]
669e746: call 0xaa710
669e74b: nop 
669e74c: mov qword ptr [rbp + 0x1788], rsi
669e753: mov qword ptr [rbp + 0x1790], 0x19
669e75e: lea rcx, [rip + 0xc35a2b3]
669e765: lea rdx, [rbp + 0x1788]
669e76c: lea r8, [rbp + 0x1200]
669e773: call 0x66a02d0
669e778: nop 
669e779: lea rcx, [rip + 0xc35a2a8]
669e780: call 0xe938d70
669e785: mov rsi, rdi
669e788: jmp 0x6699014
669e78d: lea rcx, [rip + 0xc32be4c]
669e794: call 0xe938cb0
669e799: cmp dword ptr [rip + 0xc32be40], -1
669e7a0: jne 0x66992ba
669e7a6: lea rcx, [rip + 0xc32bdbb]
669e7ad: call 0x567db00
669e7b2: nop 
669e7b3: lea rcx, [rip - 0x1020c1a]
669e7ba: call 0xe935740
669e7bf: lea rcx, [rip + 0xc32be1a]
669e7c6: call 0xe938d70
669e7cb: mov r15, qword ptr [rbp + 0x2060]
669e7d2: jmp 0x66992ba
669e7d7: mov qword ptr [rsp + 0x20], 0
669e7e0: xor ecx, ecx
669e7e2: xor edx, edx
669e7e4: xor r8d, r8d
669e7e7: xor r9d, r9d
669e7ea: call qword ptr [rip + 0x930a488]
669e7f0: mov edx, 0x48
669e7f5: mov rcx, r12
669e7f8: call 0xe935700
669e7fd: call 0x78ed0
669e802: lea rcx, [rip + 0xc35a23f]
669e809: call 0xe938cb0
669e80e: cmp dword ptr [rip + 0xc35a233], -1
669e815: jne 0x6699f5f
669e81b: lea rdx, [rip + 0x8ec513c]
669e822: lea r15, [rbp + 0x1bb0]
669e829: mov rcx, r15
669e82c: call 0x79580
669e831: nop 
669e832: mov rdx, qword ptr [rbp + 0x1bc0]
669e839: cmp qword ptr [rbp + 0x1bc8], 0x10
669e841: jb 0x669e84a
669e843: mov r15, qword ptr [rbp + 0x1bb0]
669e84a: test rdx, rdx
669e84d: je 0x669eaf7
669e853: mov eax, edx
669e855: and eax, 3
669e858: cmp rdx, 4
669e85c: jae 0x669eb15
669e862: movabs rcx, 0xcbf29ce484222325
669e86c: xor r8d, r8d
669e86f: jmp 0x669eb71
669e874: lea rcx, [rip + 0xc35a1dd]
669e87b: call 0xe938cb0
669e880: cmp dword ptr [rip + 0xc35a1d1], -1
669e887: jne 0x669a362
669e88d: lea rdx, [rip + 0x8f3c277]
669e894: lea r15, [rbp + 0x1bb0]
669e89b: mov rcx, r15
669e89e: call 0x79580
669e8a3: nop 
669e8a4: mov rdx, qword ptr [rbp + 0x1bc0]
669e8ab: cmp qword ptr [rbp + 0x1bc8], 0x10
669e8b3: jb 0x669e8bc
669e8b5: mov r15, qword ptr [rbp + 0x1bb0]
669e8bc: test rdx, rdx
669e8bf: je 0x669eb06
669e8c5: mov eax, edx
669e8c7: and eax, 3
669e8ca: cmp rdx, 4
669e8ce: jae 0x669ebcc
669e8d4: movabs rcx, 0xcbf29ce484222325
669e8de: xor r8d, r8d
669e8e1: jmp 0x669ec28
669e8e6: mov ecx, 5
669e8eb: call 0xeec5a00
669e8f0: mov dword ptr [r12 + 0x2d4], 0x7ffffffe
669e8fc: mov ecx, 6
669e901: call 0xeec5a00
669e906: lea rcx, [rip + 0xc35a15b]
669e90d: call 0xe938cb0
669e912: cmp dword ptr [rip + 0xc35a14f], -1
669e919: jne 0x669b020
669e91f: lea rdx, [rip + 0x8f5028e]
669e926: lea r12, [rbp + 0x1bb0]
669e92d: mov rcx, r12
669e930: call 0x79580
669e935: nop 
669e936: mov rcx, qword ptr [rbp + 0x1bc0]
669e93d: cmp qword ptr [rbp + 0x1bc8], 0x10
669e945: jb 0x669e94e
669e947: mov r12, qword ptr [rbp + 0x1bb0]
669e94e: test rcx, rcx
669e951: je 0x669ed10
669e957: mov eax, ecx
669e959: and eax, 3
669e95c: cmp rcx, 4
669e960: jae 0x669ec83
669e966: movabs rcx, 0xcbf29ce484222325
669e970: mov qword ptr [rbp + 0x2058], rcx
669e977: xor edx, edx
669e979: jmp 0x669ece6
669e97e: lea rcx, [rip + 0xc32bc5b]
669e985: call 0xe938cb0
669e98a: cmp dword ptr [rip + 0xc32bc4f], -1
669e991: jne 0x6699446
669e997: lea rcx, [rip + 0xc32bbca]
669e99e: call 0x567db00
669e9a3: nop 
669e9a4: lea rcx, [rip - 0x1020e0b]
669e9ab: call 0xe935740
669e9b0: lea rcx, [rip + 0xc32bc29]
669e9b7: call 0xe938d70
669e9bc: mov r15, qword ptr [rbp + 0x2060]
669e9c3: mov r12, qword ptr [rbp + 0x2078]
669e9ca: jmp 0x6699446
669e9cf: lea rcx, [rip + 0xc32bc0a]
669e9d6: call 0xe938cb0
669e9db: cmp dword ptr [rip + 0xc32bbfe], -1
669e9e2: jne 0x669952a
669e9e8: lea rcx, [rip + 0xc32bb79]
669e9ef: call 0x567db00
669e9f4: nop 
669e9f5: lea rcx, [rip - 0x1020e5c]
669e9fc: call 0xe935740
669ea01: lea rcx, [rip + 0xc32bbd8]
669ea08: call 0xe938d70
669ea0d: mov r15, qword ptr [rbp + 0x2060]
669ea14: mov r12, qword ptr [rbp + 0x2078]
669ea1b: jmp 0x669952a
669ea20: mov qword ptr [rbp + 0x1fb8], r12
669ea27: lea rcx, [rip + 0x8f1419f]
669ea2e: call 0xeec5850
669ea33: nop 
669ea34: lea rcx, [rip + 0xc359ffd]
669ea3b: call 0xe938cb0
669ea40: cmp dword ptr [rip + 0xc359ff1], -1
669ea47: jne 0x6699607
669ea4d: lea rdx, [rip + 0x8f6e5a2]
669ea54: lea r14, [rbp + 0x1880]
669ea5b: mov rcx, r14
669ea5e: call 0x79580
669ea63: nop 
669ea64: mov r8, qword ptr [rbp + 0x1890]
669ea6b: cmp qword ptr [rbp + 0x1898], 0x10
669ea73: jb 0x669ea7c
669ea75: mov r14, qword ptr [rbp + 0x1880]
669ea7c: test r8, r8
669ea7f: je 0x669ed3b
669ea85: mov eax, r8d
669ea88: and eax, 3
669ea8b: movabs rcx, 0x100000001b3
669ea95: cmp r8, 4
669ea99: jae 0x669ed47
669ea9f: movabs rdx, 0xcbf29ce484222325
669eaa9: xor r9d, r9d
669eaac: jmp 0x669ed99
669eab1: lea rcx, [rip + 0x8e91cd6]
669eab8: call 0xeec5850
669eabd: nop 
669eabe: lea rcx, [rip + 0xc35c6a3]
669eac5: call 0xe938cb0
669eaca: cmp dword ptr [rip + 0xc35c697], -1
669ead1: jne 0x669eaeb
669ead3: lea rcx, [rip + 0xbf3c6]
669eada: call 0xe935740
669eadf: lea rcx, [rip + 0xc35c682]
669eae6: call 0xe938d70
669eaeb: mov r12, qword ptr [rbp + 0x2078]
669eaf2: jmp 0x6699658
669eaf7: movabs rcx, 0xcbf29ce484222325
669eb01: jmp 0x669eb9a
669eb06: movabs rcx, 0xcbf29ce484222325
669eb10: jmp 0x669ec51
669eb15: and rdx, 0xfffffffffffffffc
669eb19: movabs rcx, 0xcbf29ce484222325
669eb23: xor r8d, r8d
669eb26: movabs r9, 0x100000001b3
669eb30: movzx r10d, byte ptr [r15 + r8]
669eb35: xor r10, rcx
669eb38: imul r10, r9
669eb3c: movzx ecx, byte ptr [r15 + r8 + 1]
669eb42: xor rcx, r10
669eb45: imul rcx, r9
669eb49: movzx r10d, byte ptr [r15 + r8 + 2]
669eb4f: xor r10, rcx
669eb52: imul r10, r9
669eb56: movzx ecx, byte ptr [r15 + r8 + 3]
669eb5c: xor rcx, r10
669eb5f: imul rcx, r9
669eb63: add r8, 4
669eb67: cmp rdx, r8
669eb6a: jne 0x669eb30
669eb6c: test rax, rax
669eb6f: je 0x669eb9a
669eb71: add r15, r8
669eb74: xor edx, edx
669eb76: movabs r8, 0x100000001b3
669eb80: mov r9, rcx
669eb83: movzx ecx, byte ptr [r15 + rdx]
669eb88: xor rcx, r9
669eb8b: imul rcx, r8
669eb8f: inc rdx
669eb92: mov r9, rcx
669eb95: cmp rax, rdx
669eb98: jne 0x669eb83
669eb9a: mov qword ptr [rip + 0xc359e9f], rcx
669eba1: lea rcx, [rbp + 0x1bb0]
669eba8: call 0x73150
669ebad: lea rcx, [rip + 0xc359e94]
669ebb4: call 0xe938d70
669ebb9: mov rsi, qword ptr [rbp + 0x2068]
669ebc0: mov rdi, qword ptr [rbp + 0x2078]
669ebc7: jmp 0x6699f5f
669ebcc: and rdx, 0xfffffffffffffffc
669ebd0: movabs rcx, 0xcbf29ce484222325
669ebda: xor r8d, r8d
669ebdd: movabs r9, 0x100000001b3
669ebe7: movzx r10d, byte ptr [r15 + r8]
669ebec: xor r10, rcx
669ebef: imul r10, r9
669ebf3: movzx ecx, byte ptr [r15 + r8 + 1]
669ebf9: xor rcx, r10
669ebfc: imul rcx, r9
669ec00: movzx r10d, byte ptr [r15 + r8 + 2]
669ec06: xor r10, rcx
669ec09: imul r10, r9
669ec0d: movzx ecx, byte ptr [r15 + r8 + 3]
669ec13: xor rcx, r10
669ec16: imul rcx, r9
669ec1a: add r8, 4
669ec1e: cmp rdx, r8
669ec21: jne 0x669ebe7
669ec23: test rax, rax
669ec26: je 0x669ec51
669ec28: add r15, r8
669ec2b: xor edx, edx
669ec2d: movabs r8, 0x100000001b3
669ec37: mov r9, rcx
669ec3a: movzx ecx, byte ptr [r15 + rdx]
669ec3f: xor rcx, r9
669ec42: imul rcx, r8
669ec46: inc rdx
669ec49: mov r9, rcx
669ec4c: cmp rax, rdx
669ec4f: jne 0x669ec3a
669ec51: mov qword ptr [rip + 0xc359df8], rcx
669ec58: lea rcx, [rbp + 0x1bb0]
669ec5f: call 0x73150
669ec64: lea rcx, [rip + 0xc359ded]
669ec6b: call 0xe938d70
669ec70: mov rsi, qword ptr [rbp + 0x2068]
669ec77: mov rdi, qword ptr [rbp + 0x2078]
669ec7e: jmp 0x669a362
669ec83: and rcx, 0xfffffffffffffffc
669ec87: movabs rdx, 0xcbf29ce484222325
669ec91: mov qword ptr [rbp + 0x2058], rdx
669ec98: xor edx, edx
669ec9a: movzx r8d, byte ptr [r12 + rdx]
669ec9f: xor r8, qword ptr [rbp + 0x2058]
669eca6: imul r8, rbx
669ecaa: movzx r9d, byte ptr [r12 + rdx + 1]
669ecb0: xor r9, r8
669ecb3: imul r9, rbx
669ecb7: movzx r8d, byte ptr [r12 + rdx + 2]
669ecbd: xor r8, r9
669ecc0: imul r8, rbx
669ecc4: movzx r9d, byte ptr [r12 + rdx + 3]
669ecca: xor r9, r8
669eccd: imul r9, rbx
669ecd1: mov qword ptr [rbp + 0x2058], r9
669ecd8: add rdx, 4
669ecdc: cmp rcx, rdx
669ecdf: jne 0x669ec9a
669ece1: test rax, rax
669ece4: je 0x669ed10
669ece6: add r12, rdx
669ece9: xor ecx, ecx
669eceb: mov rdx, qword ptr [rbp + 0x2058]
669ecf2: movzx r8d, byte ptr [r12 + rcx]
669ecf7: xor r8, rdx
669ecfa: imul r8, rbx
669ecfe: inc rcx
669ed01: mov qword ptr [rbp + 0x2058], r8
669ed08: mov rdx, r8
669ed0b: cmp rax, rcx
669ed0e: jne 0x669ecf2
669ed10: mov rax, qword ptr [rbp + 0x2058]
669ed17: mov qword ptr [rip + 0xc359d42], rax
669ed1e: lea rcx, [rbp + 0x1bb0]
669ed25: call 0x73150
669ed2a: lea rcx, [rip + 0xc359d37]
669ed31: call 0xe938d70
669ed36: jmp 0x669b020
669ed3b: movabs rdx, 0xcbf29ce484222325
669ed45: jmp 0x669edb9
669ed47: and r8, 0xfffffffffffffffc
669ed4b: movabs rdx, 0xcbf29ce484222325
669ed55: xor r9d, r9d
669ed58: movzx r10d, byte ptr [r14 + r9]
669ed5d: xor r10, rdx
669ed60: imul r10, rcx
669ed64: movzx edx, byte ptr [r14 + r9 + 1]
669ed6a: xor rdx, r10
669ed6d: imul rdx, rcx
669ed71: movzx r10d, byte ptr [r14 + r9 + 2]
669ed77: xor r10, rdx
669ed7a: imul r10, rcx
669ed7e: movzx edx, byte ptr [r14 + r9 + 3]
669ed84: xor rdx, r10
669ed87: imul rdx, rcx
669ed8b: add r9, 4
669ed8f: cmp r8, r9
669ed92: jne 0x669ed58
669ed94: test rax, rax
669ed97: je 0x669edb9
669ed99: add r14, r9
669ed9c: xor r8d, r8d
669ed9f: mov r9, rdx
669eda2: movzx edx, byte ptr [r14 + r8]
669eda7: xor rdx, r9
669edaa: imul rdx, rcx
669edae: inc r8
669edb1: mov r9, rdx
669edb4: cmp rax, r8
669edb7: jne 0x669eda2
669edb9: mov qword ptr [rip + 0xc359c70], rdx
669edc0: lea rcx, [rbp + 0x1880]
669edc7: call 0x73150
669edcc: lea rcx, [rip + 0xc359c65]
669edd3: call 0xe938d70
669edd8: mov r12, qword ptr [rbp + 0x2078]
669eddf: jmp 0x6699607
