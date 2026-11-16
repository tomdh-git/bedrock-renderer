# Unit U-E4-H10 progress — builder 0x6722cb0 (ends 0x672a464)

## NEXT
UNIT COMPLETE. All 29 phases (0x6728f55–0x672a464) are appended below as fenced `0xRVA  mnemonic operands` blocks each followed by a `// interpretation` line. Builder function proper ends at ret 0x672a30e [V]; phases 28-29 cover the next function's failure/FNV path ending exactly at 0x672a464 [V]. No further work; no (bad) instructions encountered.

## Status (complete)
- [x] Phases 1-27: builder function 0x6728f55–0x672a315 (epilogue ret 0x672a30e [V]) — appended below
- [x] Phases 28-29: next function failure/FNV path 0x672a31a–0x672a45f (ends at 0x672a464 [V]) — appended below
- [x] All 29 phases appended — no remaining work

## Phase 1 (0x6728f55–0x6729018)
```
0x6728f55  mov rcx, qword ptr [rip + 0xbc15254]
0x6728f5c  mov rax, qword ptr [rcx]
0x6728f5f  mov rax, qword ptr [rax + 0x10]
0x6728f63  movzx edx, byte ptr [rbp + 0x827]
0x6728f6a  call qword ptr [rip + 0x9277030]
0x6728f70  nop
0x6728f71  mov eax, dword ptr [r14 + 0x770]
0x6728f78  sub eax, dword ptr [r14 + 0x768]
0x6728f7f  shr eax, 3
0x6728f82  imul eax, eax, 0xfffff0f1
0x6728f88  dec eax
0x6728f8a  mov word ptr [rbp + 0x2ca], ax
0x6728f91  mov rcx, qword ptr [rip + 0xbc15218]
0x6728f98  mov rax, qword ptr [rcx]
0x6728f9b  mov rax, qword ptr [rax + 0x10]
0x6728f9f  mov dl, 0x4a
0x6728fa1  call qword ptr [rip + 0x9276ff9]
0x6728fa7  nop
0x6728fa8  mov byte ptr [rbp + 0x827], al
0x6728fae  mov rdx, qword ptr [r14 + 0x2d8]
0x6728fb5  cmp rdx, qword ptr [r14 + 0x2e0]
0x6728fbc  je 0x6729073
0x6728fc2  inc rdx
0x6728fc5  mov qword ptr [r14 + 0x2d8], rdx
0x6728fcc  jmp 0x6729080
0x6728fd1  lea rcx, [r14 + 0x6a8]
0x6728fd8  call 0x6760e60
0x6728fdd  nop
0x6728fde  mov rcx, qword ptr [rip + 0xbc151cb]
0x6728fe5  mov rax, qword ptr [rcx]
0x6728fe8  mov rax, qword ptr [rax + 0x10]
0x6728fec  movzx edx, byte ptr [rbp + 0x827]
0x6728ff3  call qword ptr [rip + 0x9276fa7]
0x6728ff9  nop
0x6728ffa  mov eax, dword ptr [r14 + 0x6a8]
0x6729001  not eax
0x6729003  add eax, dword ptr [r14 + 0x6b0]
0x672900a  mov word ptr [rbp + 0x2da], ax
0x6729011  mov rcx, qword ptr [rip + 0xbc15198]
0x6729018  mov rax, qword ptr [rcx]
```
// interpretation: Phase 1 sets up vtable/interface dispatch: loads a global pointer via [rip], reads [rcx] and [rax+0x10] (vtable+method), reads a flag byte [rbp+0x827], calls an interface method [rip+0x9277030]. Computes a field difference ([r14+0x770]-[r14+0x768])>>3, scales by 0xfffff0f1 (magic multiply for /10), decrements, stores to [rbp+0x2ca]. Repeats the dispatch pattern for [rip+0x9276ff9] with dl=0x4a, stores result to [rbp+0x827]. Checks iterator bounds [r14+0x2d8] vs [r14+0x2e0]; if at end calls 0x6760e60 to refill, else increments and jumps to 0x6729080. Then another dispatch at 0x6728fde–0x6728ff9 for [rip+0x9276fa7]. Computes ~(dword)[r14+0x6a8] + [r14+0x6b0] and stores to [rbp+0x2da]. Finally starts a fourth dispatch at 0x6729011–0x6729018 for [rip+0x9276f79]. [V] every instruction address/op copied from disrange output at 0x6728f55–0x6729018.

## Phase 2 (0x672901b–0x67290e1)
```
0x672901b  mov rax, qword ptr [rax + 0x10]
0x672901f  mov dl, 0x4a
0x6729021  call qword ptr [rip + 0x9276f79]
0x6729027  nop
0x6729028  mov byte ptr [rbp + 0x827], al
0x672902e  mov rdx, qword ptr [r14 + 0x590]
0x6729035  cmp rdx, qword ptr [r14 + 0x598]
0x672903c  je 0x6729104
0x6729042  lea rax, [rdx + 0x10]
0x6729046  mov qword ptr [rdx], rax
0x6729049  movabs rax, 0x100000000
0x6729053  mov qword ptr [rdx + 8], rax
0x6729057  mov rcx, rdx
0x672905a  lea rdx, [rbp + 0x560]
0x6729061  call 0x6764990
0x6729066  add qword ptr [r14 + 0x590], 0x30
0x672906e  jmp 0x672911b
0x6729073  lea rcx, [r14 + 0x2d0]
0x672907a  call 0x6760e60
0x672907f  nop
0x6729080  mov rcx, qword ptr [rip + 0xbc15129]
0x6729087  mov rax, qword ptr [rcx]
0x672908a  mov rax, qword ptr [rax + 0x10]
0x672908e  movzx edx, byte ptr [rbp + 0x827]
0x6729095  call qword ptr [rip + 0x9276f05]
0x672909b  nop
0x672909c  movabs rax, 0x4000000002007009
0x67290a6  mov qword ptr [rbp + 0x2a0], rax
0x67290ad  mov eax, dword ptr [r14 + 0x2d0]
0x67290b4  not eax
0x67290b6  add eax, dword ptr [r14 + 0x2d8]
0x67290bd  mov word ptr [rbp + 0x32c], ax
0x67290c4  mov rcx, qword ptr [rip + 0xbc150e5]
0x67290cb  mov rax, qword ptr [rcx]
0x67290ce  mov rax, qword ptr [rax + 0x10]
0x67290d2  mov dl, 0x4a
0x67290d4  call qword ptr [rip + 0x9276ec6]
0x67290da  nop
0x67290db  mov byte ptr [rbp + 0x827], al
0x67290e1  mov rdx, qword ptr [r14 + 0x6b0]
```
// interpretation: Phase 2 completes the fourth dispatch started at end of Phase 1: [rax+0x10] vtable method, dl=0x4a, call [rip+0x9276f79], store al to [rbp+0x827]. Checks iterator [r14+0x590] vs [r14+0x598]; if at end (je 0x6729104) takes a refill path via 0x6765870 at 0x6729104 (skipped here), else writes rax into [rdx] and rax=0x100000000 into [rdx+8], advances [r14+0x590] by 0x30 via call 0x6764990, jumps to 0x672911b. The not-taken refill path at 0x6729073 calls 0x6760e60 on [r14+0x2d0]. Then a fifth dispatch at 0x6729080–0x672909b (load [rip], vtable, call [rip+0x9276f05]), stores rax=0x4000000002007009 to [rbp+0x2a0]. Computes ~[r14+0x2d0]+[r14+0x2d8] -> [rbp+0x32c]. Starts sixth dispatch at 0x67290c4–0x67290db (call [rip+0x9276ec6]), stores al to [rbp+0x827], loads [r14+0x6b0]. [V] every instruction address/op copied from disrange output at 0x672901b–0x67290e1.

## Phase 3 (0x67290e8–0x67291b0)
```
0x67290e8  cmp rdx, qword ptr [r14 + 0x6b8]
0x67290ef  je 0x67291b5
0x67290f5  inc rdx
0x67290f8  mov qword ptr [r14 + 0x6b0], rdx
0x67290ff  jmp 0x67291c2
0x6729104  mov rcx, r14
0x6729107  add rcx, 0x588
0x672910e  lea r8, [rbp + 0x560]
0x6729115  call 0x6765870
0x672911a  nop
0x672911b  mov rcx, qword ptr [rip + 0xbc1508e]
0x6729122  mov rax, qword ptr [rcx]
0x6729125  mov rax, qword ptr [rax + 0x10]
0x6729129  movzx edx, byte ptr [rbp + 0x827]
0x6729130  call qword ptr [rip + 0x9276e6a]
0x6729136  nop
0x6729137  movabs rax, 0x202207009
0x6729141  mov qword ptr [rbp + 0x2a0], rax
0x6729148  mov eax, dword ptr [r14 + 0x590]
0x672914f  sub eax, dword ptr [r14 + 0x588]
0x6729156  shr eax, 4
0x6729159  imul eax, eax, 0xffffaaab
0x672915f  dec eax
0x6729161  mov word ptr [rbp + 0x2f2], ax
0x6729168  mov rcx, qword ptr [rip + 0xbc15041]
0x672916f  mov rax, qword ptr [rcx]
0x6729172  mov rax, qword ptr [rax + 0x10]
0x6729176  mov dl, 0x4a
0x6729178  call qword ptr [rip + 0x9276e22]
0x672917e  nop
0x672917f  mov byte ptr [rbp + 0x827], al
0x6729185  mov rdx, qword ptr [r14 + 8]
0x6729189  cmp rdx, qword ptr [r14 + 0x10]
0x672918d  je 0x6729257
0x6729193  mov r8d, 0xc8
0x6729199  mov rcx, rdx
0x672919c  lea rdx, [rbp + 0x2a0]
0x67291a3  call 0xeec6ec0
0x67291a8  add qword ptr [r14 + 8], 0xc8
0x67291b0  jmp 0x6729267
```
// interpretation: Phase 3 continues the iterator check: cmp [r14+0x6b0] vs [r14+0x6b8]; if at end (je 0x67291b5) takes refill via 0x6760e60 on [r14+0x6a8], else increments [r14+0x6b0] and jumps to 0x67291c2. The refill path at 0x6729104 calls 0x6765870(r14+0x588, &[rbp+0x560]). Then a dispatch at 0x672911b–0x6729136 (call [rip+0x9276e6a]), stores rax=0x202207009 to [rbp+0x2a0]. Computes ([r14+0x590]-[r14+0x588])>>4, scales by 0xffffaaab (magic /10), decrements, stores to [rbp+0x2f2]. Another dispatch at 0x6729168–0x672917e (call [rip+0x9276e22]), stores al to [rbp+0x827]. Checks buffer [r14+8] vs [r14+0x10]; if full (je 0x6729257) calls 0x5aba6d0, else r8d=0xc8, call 0xeec6ec0(rdx, &[rbp+0x2a0]), advances [r14+8] by 0xc8, jumps to 0x6729267. [V] every instruction address/op copied from disrange output at 0x67290e8–0x67291b0.

## Phase 4 (0x67291b5–0x6729275)
```
0x67291b5  lea rcx, [r14 + 0x6a8]
0x67291bc  call 0x6760e60
0x67291c1  nop
0x67291c2  mov rcx, qword ptr [rip + 0xbc14fe7]
0x67291c9  mov rax, qword ptr [rcx]
0x67291cc  mov rax, qword ptr [rax + 0x10]
0x67291d0  movzx edx, byte ptr [rbp + 0x827]
0x67291d7  call qword ptr [rip + 0x9276dc3]
0x67291dd  nop
0x67291de  mov eax, dword ptr [r14 + 0x6a8]
0x67291e5  not eax
0x67291e7  add eax, dword ptr [r14 + 0x6b0]
0x67291ee  mov word ptr [rbp + 0x2da], ax
0x67291f5  mov rcx, qword ptr [rip + 0xbc14fb4]
0x67291fc  mov rax, qword ptr [rcx]
0x67291ff  mov rax, qword ptr [rax + 0x10]
0x6729203  mov dl, 0x4a
0x6729205  call qword ptr [rip + 0x9276d95]
0x672920b  nop
0x672920c  mov byte ptr [rbp + 0x827], al
0x6729212  mov rdx, qword ptr [r14 + 0x590]
0x6729219  cmp rdx, qword ptr [r14 + 0x598]
0x6729220  je 0x6729963
0x6729226  lea rax, [rdx + 0x10]
0x672922a  mov qword ptr [rdx], rax
0x672922d  movabs rax, 0x100000000
0x6729237  mov qword ptr [rdx + 8], rax
0x672923b  mov rcx, rdx
0x672923e  lea rdx, [rbp + 0x560]
0x6729245  call 0x6764990
0x672924a  add qword ptr [r14 + 0x590], 0x30
0x6729252  jmp 0x672997a
0x6729257  mov rcx, r14
0x672925a  lea r8, [rbp + 0x2a0]
0x6729261  call 0x5aba6d0
0x6729266  nop
0x6729267  mov rcx, qword ptr [rip + 0xbc14f42]
0x672926e  mov rax, qword ptr [rcx]
0x6729271  mov rax, qword ptr [rax + 0x10]
0x6729275  movzx edx, byte ptr [rbp + 0x827]
```
// interpretation: Phase 4 handles the iterator-end path: at 0x67291b5 calls 0x6760e60 to refill [r14+0x6a8], then falls through to 0x67291c2. Dispatch at 0x67291c2–0x67291dd (call [rip+0x9276dc3]). Computes ~[r14+0x6a8]+[r14+0x6b0] -> [rbp+0x2da]. Dispatch at 0x67291f5–0x672920b (call [rip+0x9276d95]), stores al to [rbp+0x827]. Checks iterator [r14+0x590] vs [r14+0x598]; if at end (je 0x6729963) calls 0x6765870(r14+0x588, &[rbp+0x560]), else writes [rdx]=rax, [rdx+8]=0x100000000, advances [r14+0x590] by 0x30 via 0x6764990, jumps to 0x672997a. The full-buffer path at 0x6729257 calls 0x5aba6d0(r14, &[rbp+0x2a0]). Then starts a new dispatch at 0x6729267–0x6729275 (load [rip], vtable, movzx edx [rbp+0x827]). [V] every instruction address/op copied from disrange output at 0x67291b5–0x6729275.

## Phase 5 (0x672927c–0x6729327)
```
0x672927c  call qword ptr [rip + 0x9276d1e]
0x6729282  nop
0x6729283  cmp byte ptr [rbp + 0x6b8], 1
0x672928a  jne 0x67292de
0x672928c  mov rcx, qword ptr [rbp + 0x678]
0x6729293  test rcx, rcx
0x6729296  je 0x67292de
0x6729298  mov rdx, qword ptr [rbp + 0x688]
0x672929f  sub rdx, rcx
0x67292a2  cmp rdx, 0x1000
0x67292a9  jb 0x67292c7
0x67292ab  mov rax, qword ptr [rcx - 8]
0x67292af  add rcx, -8
0x67292b3  sub rcx, rax
0x67292b6  cmp rcx, 0x20
0x67292ba  jae 0x672a337
0x67292c0  or rdx, 0x27
0x67292c4  mov rcx, rax
0x67292c7  call 0xe935700
0x67292cc  lea rax, [rbp + 0x678]
0x67292d3  movups xmmword ptr [rax], xmm6
0x67292d6  mov qword ptr [rax + 0x10], 0
0x67292de  lea rcx, [rbp + 0x560]
0x67292e5  call 0x6792c20
0x67292ea  mov r14, qword ptr [rbp + 0x760]
0x67292f1  mov edi, dword ptr [rbp + 0x768]
0x67292f7  test rdi, rdi
0x67292fa  je 0x6729346
0x67292fc  shl rdi, 5
0x6729300  xor r15d, r15d
0x6729303  jmp 0x6729319
0x6729305  nop word ptr cs:[rax + rax]
0x6729310  add r15, 0x20
0x6729314  cmp rdi, r15
0x6729317  je 0x6729338
0x6729319  mov rcx, qword ptr [r14 + r15 + 8]
0x672931e  test rcx, rcx
0x6729321  je 0x6729310
0x6729323  lock dec dword ptr [rcx + 0xc]
0x6729327  jne 0x6729310
```
// interpretation: Phase 5 completes the dispatch started at 0x6729267 (call [rip+0x9276d1e]). If byte [rbp+0x6b8]==1 and [rbp+0x678]!=0: computes size [rbp+0x688]-[rbp+0x678]; if >=0x1000 reads header [rcx-8] and computes size [rcx]-[rax] (allocator metadata unlink pattern); if size>=0x20 jumps to 0x672a337 (failure path), else or rdx,0x27 and calls 0xe935700 (free/dealloc), then zeroes [rbp+0x678] block with xmm6 and qword [rax+0x10]=0. Calls 0x6792c20(&[rbp+0x560]). Then a release loop over [rbp+0x760] entries: rdi = count<<5; for each [r14+r15+8] if nonzero, lock dec [rcx+0xc]; if zero, load [rcx], call [rip+...] via [rax+8] (destructor/release), at 0x6729327 jne 0x6729310 continues loop (fall-through at 0x6729329 not yet reached). [V] every instruction address/op copied from disrange output at 0x672927c–0x6729327.

## Phase 6 (0x6729329–0x67293c6)
```
0x6729329  mov rax, qword ptr [rcx]
0x672932c  mov rax, qword ptr [rax + 8]
0x6729330  call qword ptr [rip + 0x9276c6a]
0x6729336  jmp 0x6729310
0x6729338  mov r14, qword ptr [rbp + 0x760]
0x672933f  lea r15, [rbp + 0x110]
0x6729346  lea rax, [rbp + 0x770]
0x672934d  cmp rax, r14
0x6729350  je 0x672936f
0x6729352  mov rcx, qword ptr [rip + 0xbc14e4f]
0x6729359  test r14, r14
0x672935c  je 0x672936f
0x672935e  mov rax, qword ptr [rcx]
0x6729361  mov rax, qword ptr [rax + 0x10]
0x6729365  mov rdx, r14
0x6729368  call qword ptr [rip + 0x9276c32]
0x672936e  nop
0x672936f  mov r14, qword ptr [rbp + 0x7a0]
0x6729376  mov edi, dword ptr [rbp + 0x7a8]
0x672937c  test rdi, rdi
0x672937f  je 0x67293c6
0x6729381  shl rdi, 5
0x6729385  xor r15d, r15d
0x6729388  jmp 0x6729399
0x672938a  nop word ptr [rax + rax]
0x6729390  add r15, 0x20
0x6729394  cmp rdi, r15
0x6729397  je 0x67293b8
0x6729399  mov rcx, qword ptr [r14 + r15 + 8]
0x672939e  test rcx, rcx
0x67293a1  je 0x6729390
0x67293a3  lock dec dword ptr [rcx + 0xc]
0x67293a7  jne 0x6729390
0x67293a9  mov rax, qword ptr [rcx]
0x67293ac  mov rax, qword ptr [rax + 8]
0x67293b0  call qword ptr [rip + 0x9276bea]
0x67293b6  jmp 0x6729390
0x67293b8  mov r14, qword ptr [rbp + 0x7a0]
0x67293bf  lea r15, [rbp + 0x110]
0x67293c6  lea rax, [rbp + 0x7b0]
```
// interpretation: Phase 6 completes the release loop body: if refcount reaches zero, mov rax,[rcx]; mov rax,[rax+8]; call qword ptr [rip+0x9276c6a] (final release/destructor), jmp back to loop increment. Loop ends at 0x6729338 with r14=[rbp+0x760], r15=&[rbp+0x110]. Then if [rbp+0x770] != r14 and r14!=0, dispatch call [rip+0x9276c32](rdx=r14) to release another resource. Then a second release loop over [rbp+0x7a0] count ([rbp+0x7a8]<<5): for each [r14+r15+8], lock dec [rcx+0xc]; if zero call qword ptr [rip+0x9276bea]([rax+8]) destructor, jmp loop increment. Ends at 0x67293b8 reloading r14/r15, falls to 0x67293c6 lea rax,[rbp+0x7b0]. [V] every instruction address/op copied from disrange output at 0x6729329–0x67293c6.

## Phase 7 (0x67293cd–0x6729460)
```
0x67293cd  cmp rax, r14
0x67293d0  je 0x67293ef
0x67293d2  mov rcx, qword ptr [rip + 0xbc14dcf]
0x67293d9  test r14, r14
0x67293dc  je 0x67293ef
0x67293de  mov rax, qword ptr [rcx]
0x67293e1  mov rax, qword ptr [rax + 0x10]
0x67293e5  mov rdx, r14
0x67293e8  call qword ptr [rip + 0x9276bb2]
0x67293ee  nop
0x67293ef  mov r14, qword ptr [rbp + 0x7e0]
0x67293f6  test r14, r14
0x67293f9  je 0x6729475
0x67293fb  mov rdi, qword ptr [rbp + 0x7e8]
0x6729402  cmp r14, rdi
0x6729405  jne 0x6729419
0x6729407  jmp 0x672943e
0x6729409  nop dword ptr [rax]
0x6729410  add r14, 0x20
0x6729414  cmp r14, rdi
0x6729417  je 0x6729437
0x6729419  mov rcx, qword ptr [r14 + 8]
0x672941d  test rcx, rcx
0x6729420  je 0x6729410
0x6729422  lock dec dword ptr [rcx + 0xc]
0x6729426  jne 0x6729410
0x6729428  mov rax, qword ptr [rcx]
0x672942b  mov rax, qword ptr [rax + 8]
0x672942f  call qword ptr [rip + 0x9276b6b]
0x6729435  jmp 0x6729410
0x6729437  mov r14, qword ptr [rbp + 0x7e0]
0x672943e  mov rdx, qword ptr [rbp + 0x7f0]
0x6729445  sub rdx, r14
0x6729448  cmp rdx, 0x1000
0x672944f  jb 0x672946d
0x6729451  mov rax, qword ptr [r14 - 8]
0x6729455  add r14, -8
0x6729459  sub r14, rax
0x672945c  cmp r14, 0x20
0x6729460  jae 0x672a337
```
// interpretation: Phase 7 completes a release call: if [rbp+0x7b0] != r14 and r14!=0, dispatch call qword ptr [rip+0x9276bb2](rdx=r14) via [rcx+0x10] vtable. Then r14=[rbp+0x7e0]; if nonzero, rdi=[rbp+0x7e8]; third release loop over entries spaced 0x20: if [r14+8]!=0 lock dec [rcx+0xc]; if zero call qword ptr [rip+0x9276b6b]([rax+8]) destructor, jmp increment r14+=0x20. Loop ends at 0x6729437 reloading r14=[rbp+0x7e0], then 0x672943e: rdx=[rbp+0x7f0]-r14 (remaining buffer); if rdx<0x1000 jump to 0x672946d, else read header [r14-8], compute size [r14]-[rax], if size>=0x20 jump to 0x672a337 failure path. [V] every instruction address/op copied from disrange output at 0x67293cd–0x6729460.

## Phase 8 (0x6729466–0x672951e)
```
0x6729466  add rdx, 0x27
0x672946a  mov r14, rax
0x672946d  mov rcx, r14
0x6729470  call 0xe935700
0x6729475  mov rax, qword ptr [rbp + 0x558]
0x672947c  cmp qword ptr [rbp + 0x818], rax
0x6729483  jne 0x6729952
0x6729489  mov rax, qword ptr [rbp + 0x808]
0x6729490  mov rcx, qword ptr [rax + 0x10]
0x6729494  mov eax, 0x9d0
0x6729499  add rcx, rax
0x672949c  call 0x5aba5c0
0x67294a1  nop
0x67294a2  mov r14, rax
0x67294a5  lea rax, [rbp + 0x568]
0x67294ac  movups xmmword ptr [rax + 0xb0], xmm6
0x67294b3  movups xmmword ptr [rax + 0xa0], xmm6
0x67294ba  movups xmmword ptr [rax + 0x90], xmm6
0x67294c1  movups xmmword ptr [rax + 0x80], xmm6
0x67294c8  movups xmmword ptr [rax + 0x70], xmm6
0x67294cc  movups xmmword ptr [rax + 0x60], xmm6
0x67294d0  movups xmmword ptr [rax + 0x50], xmm6
0x67294d4  movups xmmword ptr [rax + 0x40], xmm6
0x67294d8  movups xmmword ptr [rax + 0x30], xmm6
0x67294dc  movups xmmword ptr [rax + 0x20], xmm6
0x67294e0  movups xmmword ptr [rax + 0x10], xmm6
0x67294e4  movups xmmword ptr [rax], xmm6
0x67294e7  mov rcx, qword ptr [rip + 0xbc14cc2]
0x67294ee  mov rax, qword ptr [rcx]
0x67294f1  mov rax, qword ptr [rax + 0x10]
0x67294f5  mov dl, 0x4a
0x67294f7  call qword ptr [rip + 0x9276aa3]
0x67294fd  nop
0x67294fe  mov byte ptr [rbp + 0x818], al
0x6729504  mov rdx, qword ptr [r14 + 0x8a8]
0x672950b  cmp rdx, qword ptr [r14 + 0x8b0]
0x6729512  je 0x6729528
0x6729514  movzx eax, word ptr [rbp + 0x500]
0x672951b  mov word ptr [rdx], ax
0x672951e  add qword ptr [r14 + 0x8a8], 2
```
// interpretation: Phase 8 completes the allocator free path: add rdx,0x27; mov r14,rax; call 0xe935700(rcx=r14) to free the buffer. Then if qword [rbp+0x818] != [rbp+0x558] jump to 0x6729952 (skip block); else rax=[rbp+0x808], rcx=[rax+0x10]+0x9d0, call 0x5aba5c0 -> r14 (allocation). Zeroes a 0xb0-byte block at [rbp+0x568] with 13 movups xmm6 stores ([rax+0x00..0xb0]). Dispatch call qword ptr [rip+0x9276aa3] with dl=0x4a, stores al to [rbp+0x818]. Then rdx=[r14+0x8a8]; if ==[r14+0x8b0] jump to 0x6729528 (refill via 0x1ef6f90), else movzx eax,word [rbp+0x500]; store word to [rdx]; add [r14+0x8a8],2. [V] every instruction address/op copied from disrange output at 0x6729466–0x672951e.

## Phase 9 (0x6729526–0x67295e8)
```
0x6729526  jmp 0x672953c
0x6729528  lea rcx, [r14 + 0x8a0]
0x672952f  lea r8, [rbp + 0x500]
0x6729536  call 0x1ef6f90
0x672953b  nop
0x672953c  mov rcx, qword ptr [rip + 0xbc14c6d]
0x6729543  mov rax, qword ptr [rcx]
0x6729546  mov rax, qword ptr [rax + 0x10]
0x672954a  movzx edx, byte ptr [rbp + 0x818]
0x6729551  call qword ptr [rip + 0x9276a49]
0x6729557  nop
0x6729558  mov qword ptr [rbp + 0x560], 1
0x6729563  mov eax, dword ptr [r14 + 0x8a8]
0x672956a  sub eax, dword ptr [r14 + 0x8a0]
0x6729571  shr eax, 1
0x6729573  dec eax
0x6729575  mov word ptr [rbp + 0x570], ax
0x672957c  mov rcx, qword ptr [rip + 0xbc14c2d]
0x6729583  mov rax, qword ptr [rcx]
0x6729586  mov rax, qword ptr [rax + 0x10]
0x672958a  mov dl, 0x4a
0x672958c  call qword ptr [rip + 0x9276a0e]
0x6729592  nop
0x6729593  mov byte ptr [rbp + 0x818], al
0x6729599  mov rdx, qword ptr [r14 + 0x758]
0x67295a0  cmp rdx, qword ptr [r14 + 0x760]
0x67295a7  je 0x6729625
0x67295a9  lea rcx, [rbp + 0x4a8]
0x67295b0  mov eax, dword ptr [rcx + 0x10]
0x67295b3  mov dword ptr [rdx + 0x10], eax
0x67295b6  movups xmm0, xmmword ptr [rcx]
0x67295b9  movups xmmword ptr [rdx], xmm0
0x67295bc  movzx eax, byte ptr [rbp + 0x4bc]
0x67295c3  mov byte ptr [rdx + 0x14], al
0x67295c6  movss xmm0, dword ptr [rbp + 0x4c0]
0x67295ce  movss dword ptr [rdx + 0x18], xmm0
0x67295d3  movss xmm0, dword ptr [rbp + 0x4c4]
0x67295db  movss dword ptr [rdx + 0x1c], xmm0
0x67295e0  movss xmm0, dword ptr [rbp + 0x4c8]
0x67295e8  movss dword ptr [rdx + 0x20], xmm0
```
// interpretation: Phase 9: jmp to 0x672953c. Refill path at 0x6729528 calls 0x1ef6f90(rcx=&[r14+0x8a0], r8=&[rbp+0x500]). Then dispatch call qword ptr [rip+0x9276a49](dl=[rbp+0x818]); stores [rbp+0x560]=1. Computes ([r14+0x8a8]-[r14+0x8a0])>>1 -1 -> [rbp+0x570]. Dispatch call qword ptr [rip+0x9276a0e](dl=0x4a); stores al to [rbp+0x818]. Then writes an element at [r14+0x758]: if [r14+0x758]==[r14+0x760] jump to 0x6729625 (refill via 0x6760a80); else copies [rbp+0x4a8] dword[0x10] to [rdx+0x10], movups [rdx]=[rcx] (0x10 bytes), byte [rbp+0x4bc]->[rdx+0x14], then float fields [rbp+0x4c0]->[rdx+0x18], [rbp+0x4c4]->[rdx+0x1c], [rbp+0x4c8]->[rdx+0x20]. [V] every instruction address/op copied from disrange output at 0x6729526–0x67295e8.

## Phase 10 (0x67295ed–0x67296ae)
```
0x67295ed  movss xmm0, dword ptr [rbp + 0x4cc]
0x67295f5  movss dword ptr [rdx + 0x24], xmm0
0x67295fa  movups xmm0, xmmword ptr [rbx + 0x80]
0x6729601  movups xmm1, xmmword ptr [rbx + 0x90]
0x6729608  movups xmm2, xmmword ptr [rbx + 0x9f]
0x672960f  movups xmmword ptr [rdx + 0x28], xmm0
0x6729613  movups xmmword ptr [rdx + 0x38], xmm1
0x6729617  movups xmmword ptr [rdx + 0x47], xmm2
0x672961b  add qword ptr [r14 + 0x758], 0x58
0x6729623  jmp 0x6729639
0x6729625  lea rcx, [r14 + 0x750]
0x672962c  lea r8, [rbp + 0x4a8]
0x6729633  call 0x6760a80
0x6729638  nop
0x6729639  mov rcx, qword ptr [rip + 0xbc14b70]
0x6729640  mov rax, qword ptr [rcx]
0x6729643  mov rax, qword ptr [rax + 0x10]
0x6729647  movzx edx, byte ptr [rbp + 0x818]
0x672964e  call qword ptr [rip + 0x927694c]
0x6729654  nop
0x6729655  mov eax, dword ptr [r14 + 0x758]
0x672965c  sub eax, dword ptr [r14 + 0x750]
0x6729663  shr eax, 3
0x6729666  imul eax, eax, 0xffff8ba3
0x672966c  dec eax
0x672966e  mov word ptr [rbp + 0x58c], ax
0x6729675  mov rcx, qword ptr [rip + 0xbc14b34]
0x672967c  mov rax, qword ptr [rcx]
0x672967f  mov rax, qword ptr [rax + 0x10]
0x6729683  mov dl, 0x4a
0x6729685  call qword ptr [rip + 0x9276915]
0x672968b  nop
0x672968c  mov byte ptr [rbp + 0x818], al
0x6729692  mov rdx, qword ptr [r14 + 0x860]
0x6729699  cmp rdx, qword ptr [r14 + 0x868]
0x67296a0  je 0x67296ae
0x67296a2  inc rdx
0x67296a5  mov qword ptr [r14 + 0x860], rdx
0x67296ac  jmp 0x67296bb
0x67296ae  lea rcx, [r14 + 0x858]
```
// interpretation: Phase 10 completes the element write: float [rbp+0x4cc]->[rdx+0x24]; movups [rbx+0x80]->[rdx+0x28], [rbx+0x90]->[rdx+0x38], [rbx+0x9f]->[rdx+0x47] (16-byte unaligned copies); advances [r14+0x758] by 0x58; jmp 0x6729639. Refill path at 0x6729625 calls 0x6760a80(rcx=&[r14+0x750], r8=&[rbp+0x4a8]). Then dispatch call qword ptr [rip+0x927694c](dl=[rbp+0x818]). Computes ([r14+0x758]-[r14+0x750])>>3, scales by 0xffff8ba3 (magic /7), decrements, stores to [rbp+0x58c]. Dispatch call qword ptr [rip+0x9276915](dl=0x4a); stores al to [rbp+0x818]. Then rdx=[r14+0x860]; if ==[r14+0x868] jump to 0x67296ae (refill via 0x6760e60 on [r14+0x858]); else inc [r14+0x860], jmp 0x67296bb. Ends at lea rcx,[r14+0x858] (refill target). [V] every instruction address/op copied from disrange output at 0x67295ed–0x67296ae.

## Phase 11 (0x67296b5–0x6729779)
```
0x67296b5  call 0x6760e60
0x67296ba  nop
0x67296bb  mov rcx, qword ptr [rip + 0xbc14aee]
0x67296c2  mov rax, qword ptr [rcx]
0x67296c5  mov rax, qword ptr [rax + 0x10]
0x67296c9  movzx edx, byte ptr [rbp + 0x818]
0x67296d0  call qword ptr [rip + 0x92768ca]
0x67296d6  nop
0x67296d7  mov eax, dword ptr [r14 + 0x858]
0x67296de  not eax
0x67296e0  add eax, dword ptr [r14 + 0x860]
0x67296e7  mov word ptr [rbp + 0x576], ax
0x67296ee  mov rcx, qword ptr [rip + 0xbc14abb]
0x67296f5  mov rax, qword ptr [rcx]
0x67296f8  mov rax, qword ptr [rax + 0x10]
0x67296fc  mov dl, 0x4a
0x67296fe  call qword ptr [rip + 0x927689c]
0x6729704  mov byte ptr [rbp + 0x818], al
0x672970a  lea rcx, [r14 + 0x648]
0x6729711  lea rdx, [rbp + 0x458]
0x6729718  call 0x675fb30
0x672971d  nop
0x672971e  mov rcx, qword ptr [rip + 0xbc14a8b]
0x6729725  mov rax, qword ptr [rcx]
0x6729728  mov rax, qword ptr [rax + 0x10]
0x672972c  movzx edx, byte ptr [rbp + 0x818]
0x6729733  call qword ptr [rip + 0x9276867]
0x6729739  nop
0x672973a  mov eax, dword ptr [r14 + 0x650]
0x6729741  sub eax, dword ptr [r14 + 0x648]
0x6729748  shr eax, 3
0x672974b  imul eax, eax, 0xffff8e39
0x6729751  dec eax
0x6729753  mov word ptr [rbp + 0x5a2], ax
0x672975a  lea rcx, [r14 + 0x780]
0x6729761  lea rdx, [rbp + 0x400]
0x6729768  call 0x675f3b0
0x672976d  nop
0x672976e  mov qword ptr [rbp + 0x560], 0x2005009
0x6729779  mov eax, dword ptr [r14 + 0x788]
```
// interpretation: Phase 11 completes refill path: call 0x6760e60(rcx=&[r14+0x858]). Dispatch call qword ptr [rip+0x92768ca](dl=[rbp+0x818]). Computes ~[r14+0x858]+[r14+0x860] -> [rbp+0x576]. Dispatch call qword ptr [rip+0x927689c](dl=0x4a); stores al to [rbp+0x818]. Calls 0x675fb30(rcx=&[r14+0x648], rdx=&[rbp+0x458]) (copy/convert). Dispatch call qword ptr [rip+0x9276867](dl=[rbp+0x818]). Computes ([r14+0x650]-[r14+0x648])>>3, scales by 0xffff8e39 (magic /7), decrements, stores to [rbp+0x5a2]. Calls 0x675f3b0(rcx=&[r14+0x780], rdx=&[rbp+0x400]). Stores [rbp+0x560]=0x2005009. Loads eax=[r14+0x788]. [V] every instruction address/op copied from disrange output at 0x67296b5–0x6729779.

## Phase 12 (0x6729780–0x672984a)
```
0x6729780  sub eax, dword ptr [r14 + 0x780]
0x6729787  shr eax, 3
0x672978a  imul eax, eax, 0xffff8ba3
0x6729790  dec eax
0x6729792  mov word ptr [rbp + 0x588], ax
0x6729799  mov rcx, qword ptr [rip + 0xbc14a10]
0x67297a0  mov rax, qword ptr [rcx]
0x67297a3  mov rax, qword ptr [rax + 0x10]
0x67297a7  mov dl, 0x4a
0x67297a9  call qword ptr [rip + 0x92767f1]
0x67297af  mov byte ptr [rbp + 0x818], al
0x67297b5  mov rdi, qword ptr [r14 + 0x770]
0x67297bc  cmp rdi, qword ptr [r14 + 0x778]
0x67297c3  je 0x6729806
0x67297c5  mov rax, qword ptr [rbp + 0x378]
0x67297cc  mov qword ptr [rdi], rax
0x67297cf  lea rcx, [rdi + 8]
0x67297d3  lea rdx, [rbp + 0x380]
0x67297da  call 0xe869ff0
0x67297df  nop
0x67297e0  mov rax, qword ptr [rbp + 0x3f8]
0x67297e7  mov qword ptr [rdi + 0x80], rax
0x67297ee  mov qword ptr [rbp + 0x3f8], 0
0x67297f9  add qword ptr [r14 + 0x770], 0x88
0x6729804  jmp 0x672981d
0x6729806  lea rcx, [r14 + 0x768]
0x672980d  mov rdx, rdi
0x6729810  lea r8, [rbp + 0x378]
0x6729817  call 0x6760710
0x672981c  nop
0x672981d  mov rcx, qword ptr [rip + 0xbc1498c]
0x6729824  mov rax, qword ptr [rcx]
0x6729827  mov rax, qword ptr [rax + 0x10]
0x672982b  movzx edx, byte ptr [rbp + 0x818]
0x6729832  call qword ptr [rip + 0x9276768]
0x6729838  nop
0x6729839  mov eax, dword ptr [r14 + 0x770]
0x6729840  sub eax, dword ptr [r14 + 0x768]
0x6729847  shr eax, 3
0x672984a  imul eax, eax, 0xfffff0f1
```
// interpretation: Phase 12 completes the count computation: ([r14+0x788]-[r14+0x780])>>3, scales by 0xffff8ba3 (/7), decrements, stores to [rbp+0x588]. Dispatch call qword ptr [rip+0x92767f1](dl=0x4a); stores al to [rbp+0x818]. Then writes an element at [r14+0x770] (size 0x88 stride): if [r14+0x770]==[r14+0x778] jump to 0x6729806 (refill via 0x6760710 on [r14+0x768]); else [rdi]=[rbp+0x378], call 0xe869ff0(rcx=rdi+8, rdx=&[rbp+0x380]), [rdi+0x80]=[rbp+0x3f8], [rbp+0x3f8]=0, advance [r14+0x770]+=0x88, jmp 0x672981d. Refill path calls 0x6760710(rdx=rdi, r8=&[rbp+0x378]). Then dispatch call qword ptr [rip+0x9276768](dl=[rbp+0x818]). Computes ([r14+0x770]-[r14+0x768])>>3. Ends at imul eax,eax,0xfffff0f1 (/10 magic). [V] every instruction address/op copied from disrange output at 0x6729780–0x672984a.

## Phase 13 (0x6729850–0x6729905)
```
0x6729850  dec eax
0x6729852  mov word ptr [rbp + 0x58a], ax
0x6729859  mov rcx, qword ptr [rip + 0xbc14950]
0x6729860  mov rax, qword ptr [rcx]
0x6729863  mov rax, qword ptr [rax + 0x10]
0x6729867  mov dl, 0x4a
0x6729869  call qword ptr [rip + 0x9276731]
0x672986f  nop
0x6729870  mov byte ptr [rbp + 0x818], al
0x6729876  mov rdx, qword ptr [r14 + 0x6b0]
0x672987d  cmp rdx, qword ptr [r14 + 0x6b8]
0x6729884  je 0x6729892
0x6729886  inc rdx
0x6729889  mov qword ptr [r14 + 0x6b0], rdx
0x6729890  jmp 0x67298a2
0x6729892  mov rcx, r14
0x6729895  add rcx, 0x6a8
0x672989c  call 0x6760e60
0x67298a1  nop
0x67298a2  mov rcx, qword ptr [rip + 0xbc14907]
0x67298a9  mov rax, qword ptr [rcx]
0x67298ac  mov rax, qword ptr [rax + 0x10]
0x67298b0  movzx edx, byte ptr [rbp + 0x818]
0x67298b7  call qword ptr [rip + 0x92766e3]
0x67298bd  nop
0x67298be  mov qword ptr [rbp + 0x560], 0x2207009
0x67298c9  mov eax, dword ptr [r14 + 0x6a8]
0x67298d0  not eax
0x67298d2  add eax, dword ptr [r14 + 0x6b0]
0x67298d9  mov word ptr [rbp + 0x59a], ax
0x67298e0  mov rcx, qword ptr [rip + 0xbc148c9]
0x67298e7  mov rax, qword ptr [rcx]
0x67298ea  mov rax, qword ptr [rax + 0x10]
0x67298ee  mov dl, 0x4a
0x67298f0  call qword ptr [rip + 0x92766aa]
0x67298f6  nop
0x67298f7  mov byte ptr [rbp + 0x818], al
0x67298fd  mov rdx, qword ptr [r14 + 8]
0x6729901  cmp rdx, qword ptr [r14 + 0x10]
0x6729905  je 0x6729926
```
// interpretation: Phase 13 completes count: dec eax; store [rbp+0x58a]. Dispatch call qword ptr [rip+0x9276731](dl=0x4a); stores al to [rbp+0x818]. Iterator check [r14+0x6b0] vs [r14+0x6b8]: if at end (je 0x6729892) refill via call 0x6760e60(rcx=r14+0x6a8); else inc [r14+0x6b0], jmp 0x67298a2. Dispatch call qword ptr [rip+0x92766e3](dl=[rbp+0x818]). Stores [rbp+0x560]=0x2207009. Computes ~[r14+0x6a8]+[r14+0x6b0] -> [rbp+0x59a]. Dispatch call qword ptr [rip+0x927689c](dl=0x4a); stores al to [rbp+0x818]. Then rdx=[r14+8]; if ==[r14+0x10] jump to 0x6729926 (full-buffer path via 0x5aba6d0). [V] every instruction address/op copied from disrange output at 0x6729850–0x6729905.

## Phase 14 (0x6729907–0x67299ce)
```
0x6729907  mov r8d, 0xc8
0x672990d  mov rcx, rdx
0x6729910  lea rdx, [rbp + 0x2a0]
0x6729917  call 0xeec6ec0
0x672991c  add qword ptr [r14 + 8], 0xc8
0x6729924  jmp 0x6729936
0x6729926  mov rcx, r14
0x6729929  lea r8, [rbp + 0x560]
0x6729930  call 0x5aba6d0
0x6729935  nop
0x6729936  mov rcx, qword ptr [rip + 0xbc14873]
0x672993d  mov rax, qword ptr [rcx]
0x6729940  mov rax, qword ptr [rax + 0x10]
0x6729944  movzx edx, byte ptr [rbp + 0x818]
0x672994b  call qword ptr [rip + 0x927664f]
0x6729951  nop
0x6729952  lea rcx, [rbp + 0x370]
0x6729959  call 0x67e1840
0x672995e  jmp 0x672a198
0x6729963  mov rcx, r14
0x6729966  add rcx, 0x588
0x672996d  lea r8, [rbp + 0x560]
0x6729974  call 0x6765870
0x6729979  nop
0x672997a  mov rcx, qword ptr [rip + 0xbc1482f]
0x6729981  mov rax, qword ptr [rcx]
0x6729984  mov rax, qword ptr [rax + 0x10]
0x6729988  movzx edx, byte ptr [rbp + 0x827]
0x672998f  call qword ptr [rip + 0x927660b]
0x6729995  nop
0x6729996  movabs rax, 0x4000000202207009
0x67299a0  mov qword ptr [rbp + 0x2a0], rax
0x67299a7  mov eax, dword ptr [r14 + 0x590]
0x67299ae  sub eax, dword ptr [r14 + 0x588]
0x67299b5  shr eax, 4
0x67299b8  imul eax, eax, 0xffffaaab
0x67299be  dec eax
0x67299c0  mov word ptr [rbp + 0x2f2], ax
0x67299c7  mov rcx, qword ptr [rip + 0xbc147e2]
0x67299ce  mov rax, qword ptr [rcx]
```
// interpretation: Phase 14: if buffer not full, r8d=0xc8, call 0xeec6ec0(rcx=rdx, rdx=&[rbp+0x2a0]), advance [r14+8]+=0xc8, jmp 0x6729936. Full-buffer path at 0x6729926 calls 0x5aba6d0(r14, &[rbp+0x560]). Then dispatch call qword ptr [rip+0x927664f](dl=[rbp+0x818]). If qword [rbp+0x818] != [rbp+0x558] (tested earlier at 0x672947c) jump to 0x6729952: call 0x67e1840(&[rbp+0x370]), jmp 0x672a198 (epilogue). Else (this region) the iterator-end refill at 0x6729963 calls 0x6765870(r14+0x588, &[rbp+0x560]). Then a new block at 0x672997a: dispatch call qword ptr [rip+0x927660b](dl=[rbp+0x827]); stores rax=0x4000000202207009 to [rbp+0x2a0]. Computes ([r14+0x590]-[r14+0x588])>>4, scales by 0xffffaaab (/10), decrements, stores to [rbp+0x2f2]. Starts dispatch at 0x67299c7–0x67299ce (load [rip], vtable). [V] every instruction address/op copied from disrange output at 0x6729907–0x67299ce.

## Phase 15 (0x67299d1–0x6729a7a)
```
0x67299d1  mov rax, qword ptr [rax + 0x10]
0x67299d5  mov dl, 0x4a
0x67299d7  call qword ptr [rip + 0x92765c3]
0x67299dd  nop
0x67299de  mov byte ptr [rbp + 0x827], al
0x67299e4  mov rdx, qword ptr [r14 + 8]
0x67299e8  cmp rdx, qword ptr [r14 + 0x10]
0x67299ec  je 0x6729a0d
0x67299ee  mov r8d, 0xc8
0x67299f4  mov rcx, rdx
0x67299f7  lea rdx, [rbp + 0x2a0]
0x67299fe  call 0xeec6ec0
0x6729a03  add qword ptr [r14 + 8], 0xc8
0x6729a0b  jmp 0x6729a1d
0x6729a0d  mov rcx, r14
0x6729a10  lea r8, [rbp + 0x2a0]
0x6729a17  call 0x5aba6d0
0x6729a1c  nop
0x6729a1d  mov rcx, qword ptr [rip + 0xbc1478c]
0x6729a24  mov rax, qword ptr [rcx]
0x6729a27  mov rax, qword ptr [rax + 0x10]
0x6729a2b  movzx edx, byte ptr [rbp + 0x827]
0x6729a32  call qword ptr [rip + 0x9276568]
0x6729a38  nop
0x6729a39  cmp byte ptr [rbp + 0x6c0], 1
0x6729a40  jne 0x6729a94
0x6729a42  mov rcx, qword ptr [rbp + 0x680]
0x6729a49  test rcx, rcx
0x6729a4c  je 0x6729a94
0x6729a4e  mov rdx, qword ptr [rbp + 0x690]
0x6729a55  sub rdx, rcx
0x6729a58  cmp rdx, 0x1000
0x6729a5f  jb 0x6729a7d
0x6729a61  mov rax, qword ptr [rcx - 8]
0x6729a65  add rcx, -8
0x6729a69  sub rcx, rax
0x6729a6c  cmp rcx, 0x20
0x6729a70  jae 0x672a337
0x6729a76  or rdx, 0x27
0x6729a7a  mov rcx, rax
```
// interpretation: Phase 15 completes dispatch: mov rax,[rax+0x10]; dl=0x4a; call qword ptr [rip+0x92765c3]; stores al to [rbp+0x827]. Buffer write: rdx=[r14+8]; if ==[r14+0x10] jump to 0x6729a0d (full path via 0x5aba6d0); else r8d=0xc8, call 0xeec6ec0(rcx=rdx, rdx=&[rbp+0x2a0]), advance [r14+8]+=0xc8, jmp 0x6729a1d. Dispatch call qword ptr [rip+0x9276568](dl=[rbp+0x827]). If byte [rbp+0x6c0]==1 and [rbp+0x680]!=0: rdx=[rbp+0x690]-[rbp+0x680] (size); if >=0x1000 read header [rcx-8], compute size [rcx]-[rax], if >=0x20 jump to 0x672a337 failure; else or rdx,0x27; mov rcx,rax (prepare free call 0xe935700). Falls through to 0x6729a7d. [V] every instruction address/op copied from disrange output at 0x67299d1–0x6729a7a.

## Phase 16 (0x6729a7d–0x6729b1f)
```
0x6729a7d  call 0xe935700
0x6729a82  lea rax, [rbp + 0x680]
0x6729a89  movups xmmword ptr [rax], xmm6
0x6729a8c  mov qword ptr [rax + 0x10], 0
0x6729a94  lea rcx, [rbp + 0x560]
0x6729a9b  call 0x6792400
0x6729aa0  mov r14, qword ptr [rbp + 0x760]
0x6729aa7  mov edi, dword ptr [rbp + 0x768]
0x6729aad  test rdi, rdi
0x6729ab0  je 0x6729af6
0x6729ab2  shl rdi, 5
0x6729ab6  xor r15d, r15d
0x6729ab9  jmp 0x6729ac9
0x6729abb  nop dword ptr [rax + rax]
0x6729ac0  add r15, 0x20
0x6729ac4  cmp rdi, r15
0x6729ac7  je 0x6729ae8
0x6729ac9  mov rcx, qword ptr [r14 + r15 + 8]
0x6729ace  test rcx, rcx
0x6729ad1  je 0x6729ac0
0x6729ad3  lock dec dword ptr [rcx + 0xc]
0x6729ad7  jne 0x6729ac0
0x6729ad9  mov rax, qword ptr [rcx]
0x6729adc  mov rax, qword ptr [rax + 8]
0x6729ae0  call qword ptr [rip + 0x92764ba]
0x6729ae6  jmp 0x6729ac0
0x6729ae8  mov r14, qword ptr [rbp + 0x760]
0x6729aef  lea r15, [rbp + 0x110]
0x6729af6  lea rax, [rbp + 0x770]
0x6729afd  cmp rax, r14
0x6729b00  je 0x6729b1f
0x6729b02  mov rcx, qword ptr [rip + 0xbc1469f]
0x6729b09  test r14, r14
0x6729b0c  je 0x6729b1f
0x6729b0e  mov rax, qword ptr [rcx]
0x6729b11  mov rax, qword ptr [rax + 0x10]
0x6729b15  mov rdx, r14
0x6729b18  call qword ptr [rip + 0x9276482]
0x6729b1e  nop
0x6729b1f  mov r14, qword ptr [rbp + 0x7a0]
```
// interpretation: Phase 16: completes the free from Phase 15: call 0xe935700(rcx=rax); zeroes [rbp+0x680] block (movups [rax]=xmm6, qword [rax+0x10]=0). Calls 0x6792400(&[rbp+0x560]). Release loop over [rbp+0x760] (count [rbp+0x768]<<5): for each [r14+r15+8] if nonzero lock dec [rcx+0xc]; if zero call qword ptr [rip+0x92764ba]([rax+8]) destructor, jmp increment r15+=0x20. Loop ends at 0x6729ae8 reloading r14/r15. Then if [rbp+0x770]!=r14 and r14!=0, dispatch call qword ptr [rip+0x9276482](rdx=r14) via vtable. Ends at 0x6729b1f mov r14,[rbp+0x7a0] (start of next release loop). [V] every instruction address/op copied from disrange output at 0x6729a7d–0x6729b1f.

## Phase 17 (0x6729b26–0x6729bb9)
```
0x6729b26  mov edi, dword ptr [rbp + 0x7a8]
0x6729b2c  test rdi, rdi
0x6729b2f  je 0x6729b76
0x6729b31  shl rdi, 5
0x6729b35  xor r15d, r15d
0x6729b38  jmp 0x6729b49
0x6729b3a  nop word ptr [rax + rax]
0x6729b40  add r15, 0x20
0x6729b44  cmp rdi, r15
0x6729b47  je 0x6729b68
0x6729b49  mov rcx, qword ptr [r14 + r15 + 8]
0x6729b4e  test rcx, rcx
0x6729b51  je 0x6729b40
0x6729b53  lock dec dword ptr [rcx + 0xc]
0x6729b57  jne 0x6729b40
0x6729b59  mov rax, qword ptr [rcx]
0x6729b5c  mov rax, qword ptr [rax + 8]
0x6729b60  call qword ptr [rip + 0x927643a]
0x6729b66  jmp 0x6729b40
0x6729b68  mov r14, qword ptr [rbp + 0x7a0]
0x6729b6f  lea r15, [rbp + 0x110]
0x6729b76  lea rax, [rbp + 0x7b0]
0x6729b7d  cmp rax, r14
0x6729b80  je 0x6729b9f
0x6729b82  mov rcx, qword ptr [rip + 0xbc1461f]
0x6729b89  test r14, r14
0x6729b8c  je 0x6729b9f
0x6729b8e  mov rax, qword ptr [rcx]
0x6729b91  mov rax, qword ptr [rax + 0x10]
0x6729b95  mov rdx, r14
0x6729b98  call qword ptr [rip + 0x9276402]
0x6729b9e  nop
0x6729b9f  mov r14, qword ptr [rbp + 0x7e0]
0x6729ba6  test r14, r14
0x6729ba9  je 0x6729c25
0x6729bab  mov rdi, qword ptr [rbp + 0x7e8]
0x6729bb2  cmp r14, rdi
0x6729bb5  jne 0x6729bc9
0x6729bb7  jmp 0x6729bee
0x6729bb9  nop dword ptr [rax]
```
// interpretation: Phase 17: second release loop over [rbp+0x7a0] (count [rbp+0x7a8]<<5): for each [r14+r15+8] if nonzero lock dec [rcx+0xc]; if zero call qword ptr [rip+0x927643a]([rax+8]) destructor, jmp increment r15+=0x20. Loop ends at 0x6729b68 reloading r14/r15. Then if [rbp+0x7b0]!=r14 and r14!=0, dispatch call qword ptr [rip+0x9276402](rdx=r14) via vtable [rcx+0x10]. Then r14=[rbp+0x7e0]; if zero jump to 0x6729c25 (skip buffer free). Else rdi=[rbp+0x7e8]; if r14==rdi jump to 0x6729bee, else (r14!=rdi) fall to 0x6729bc9 to start buffer-release loop. Ends at nop dword ptr [rax] (padding before 0x6729410-style loop). [V] every instruction address/op copied from disrange output at 0x6729b26–0x6729bb9.

## Phase 18 (0x6729bc0–0x6729c6a)
```
0x6729bc0  add r14, 0x20
0x6729bc4  cmp r14, rdi
0x6729bc7  je 0x6729be7
0x6729bc9  mov rcx, qword ptr [r14 + 8]
0x6729bcd  test rcx, rcx
0x6729bd0  je 0x6729bc0
0x6729bd2  lock dec dword ptr [rcx + 0xc]
0x6729bd6  jne 0x6729bc0
0x6729bd8  mov rax, qword ptr [rcx]
0x6729bdb  mov rax, qword ptr [rax + 8]
0x6729bdf  call qword ptr [rip + 0x92763bb]
0x6729be5  jmp 0x6729bc0
0x6729be7  mov r14, qword ptr [rbp + 0x7e0]
0x6729bee  mov rdx, qword ptr [rbp + 0x7f0]
0x6729bf5  sub rdx, r14
0x6729bf8  cmp rdx, 0x1000
0x6729bff  jb 0x6729c1d
0x6729c01  mov rax, qword ptr [r14 - 8]
0x6729c05  add r14, -8
0x6729c09  sub r14, rax
0x6729c0c  cmp r14, 0x20
0x6729c10  jae 0x672a337
0x6729c16  add rdx, 0x27
0x6729c1a  mov r14, rax
0x6729c1d  mov rcx, r14
0x6729c20  call 0xe935700
0x6729c25  mov rax, qword ptr [rbp + 0x558]
0x6729c2c  cmp qword ptr [rbp + 0x818], rax
0x6729c33  jne 0x672a18c
0x6729c39  mov rax, qword ptr [rbp + 0x808]
0x6729c40  mov rcx, qword ptr [rax + 0x10]
0x6729c44  mov eax, 0x9d0
0x6729c49  add rcx, rax
0x6729c4c  call 0x5aba5c0
0x6729c51  nop
0x6729c52  mov r14, rax
0x6729c55  lea rax, [rbp + 0x568]
0x6729c5c  movups xmmword ptr [rax + 0xb0], xmm6
0x6729c63  movups xmmword ptr [rax + 0xa0], xmm6
0x6729c6a  movups xmmword ptr [rax + 0x90], xmm6
```
// interpretation: Phase 18: buffer-release loop over [rbp+0x7e0]..[rbp+0x7e8] step 0x20: for each [r14+8] if nonzero lock dec [rcx+0xc]; if zero call qword ptr [rip+0x92763bb]([rax+8]) destructor, jmp increment r14+=0x20. Loop ends at 0x6729be7 reloading r14=[rbp+0x7e0]. Then rdx=[rbp+0x7f0]-[rbp+0x7e0] (remaining); if <0x1000 jump to 0x6729c1d, else read header [r14-8], compute size [r14]-[rax], if >=0x20 jump to 0x672a337 failure; else add rdx,0x27; mov r14,rax. Call 0xe935700(rcx=r14) to free. Then if qword [rbp+0x818] != [rbp+0x558] jump to 0x672a18c (skip allocation); else rax=[rbp+0x808], rcx=[rax+0x10]+0x9d0, call 0x5aba5c0 -> r14 (allocate). Zeroes [rbp+0x568] block starting: movups [rax+0xb0]=xmm6, [rax+0xa0]=xmm6, [rax+0x90]=xmm6 (continues). [V] every instruction address/op copied from disrange output at 0x6729bc0–0x6729c6a.

## Phase 19 (0x6729c71–0x6729d2c)
```
0x6729c71  movups xmmword ptr [rax + 0x80], xmm6
0x6729c78  movups xmmword ptr [rax + 0x70], xmm6
0x6729c7c  movups xmmword ptr [rax + 0x60], xmm6
0x6729c80  movups xmmword ptr [rax + 0x50], xmm6
0x6729c84  movups xmmword ptr [rax + 0x40], xmm6
0x6729c88  movups xmmword ptr [rax + 0x30], xmm6
0x6729c8c  movups xmmword ptr [rax + 0x20], xmm6
0x6729c90  movups xmmword ptr [rax + 0x10], xmm6
0x6729c94  movups xmmword ptr [rax], xmm6
0x6729c97  mov rcx, qword ptr [rip + 0xbc14512]
0x6729c9e  mov rax, qword ptr [rcx]
0x6729ca1  mov rax, qword ptr [rax + 0x10]
0x6729ca5  mov dl, 0x4a
0x6729ca7  call qword ptr [rip + 0x92762f3]
0x6729cad  nop
0x6729cae  mov byte ptr [rbp + 0x818], al
0x6729cb4  mov rdx, qword ptr [r14 + 0x8a8]
0x6729cbb  cmp rdx, qword ptr [r14 + 0x8b0]
0x6729cc2  je 0x6729cd8
0x6729cc4  movzx eax, word ptr [rbp + 0x500]
0x6729ccb  mov word ptr [rdx], ax
0x6729cce  add qword ptr [r14 + 0x8a8], 2
0x6729cd6  jmp 0x6729cec
0x6729cd8  lea rcx, [r14 + 0x8a0]
0x6729cdf  lea r8, [rbp + 0x500]
0x6729ce6  call 0x1ef6f90
0x6729ceb  nop
0x6729cec  mov rcx, qword ptr [rip + 0xbc144bd]
0x6729cf3  mov rax, qword ptr [rcx]
0x6729cf6  mov rax, qword ptr [rax + 0x10]
0x6729cfa  movzx edx, byte ptr [rbp + 0x818]
0x6729d01  call qword ptr [rip + 0x9276299]
0x6729d07  nop
0x6729d08  mov qword ptr [rbp + 0x560], 1
0x6729d13  mov eax, dword ptr [r14 + 0x8a8]
0x6729d1a  sub eax, dword ptr [r14 + 0x8a0]
0x6729d21  shr eax, 1
0x6729d23  dec eax
0x6729d25  mov word ptr [rbp + 0x570], ax
0x6729d2c  mov rcx, qword ptr [rip + 0xbc1447d]
```
// interpretation: Phase 19: completes zeroing [rbp+0x568] block: movups [rax+0x80..0x00]=xmm6 (14 stores total across Phases 18-19, 0xb0 bytes). Dispatch call qword ptr [rip+0x92762f3](dl=0x4a); stores al to [rbp+0x818]. Then rdx=[r14+0x8a8]; if ==[r14+0x8b0] jump to 0x6729cd8 (refill via 0x1ef6f90 on [r14+0x8a0]); else movzx eax,word [rbp+0x500]; store word to [rdx]; add [r14+0x8a8]+=2, jmp 0x6729cec. Refill path calls 0x1ef6f90(rcx=&[r14+0x8a0], r8=&[rbp+0x500]). Then dispatch call qword ptr [rip+0x9276299](dl=[rbp+0x818]); stores [rbp+0x560]=1. Computes ([r14+0x8a8]-[r14+0x8a0])>>1 -1 -> [rbp+0x570]. Starts dispatch at 0x6729d2c (load [rip], vtable). [V] every instruction address/op copied from disrange output at 0x6729c71–0x6729d2c.

## Phase 20 (0x6729d33–0x6729df7)
```
0x6729d33  mov rax, qword ptr [rcx]
0x6729d36  mov rax, qword ptr [rax + 0x10]
0x6729d3a  mov dl, 0x4a
0x6729d3c  call qword ptr [rip + 0x927625e]
0x6729d42  nop
0x6729d43  mov byte ptr [rbp + 0x818], al
0x6729d49  mov rdx, qword ptr [r14 + 0x758]
0x6729d50  cmp rdx, qword ptr [r14 + 0x760]
0x6729d57  je 0x6729dd5
0x6729d59  lea rcx, [rbp + 0x4a8]
0x6729d60  mov eax, dword ptr [rcx + 0x10]
0x6729d63  mov dword ptr [rdx + 0x10], eax
0x6729d66  movups xmm0, xmmword ptr [rcx]
0x6729d69  movups xmmword ptr [rdx], xmm0
0x6729d6c  movzx eax, byte ptr [rbp + 0x4bc]
0x6729d73  mov byte ptr [rdx + 0x14], al
0x6729d76  movss xmm0, dword ptr [rbp + 0x4c0]
0x6729d7e  movss dword ptr [rdx + 0x18], xmm0
0x6729d83  movss xmm0, dword ptr [rbp + 0x4c4]
0x6729d8b  movss dword ptr [rdx + 0x1c], xmm0
0x6729d90  movss xmm0, dword ptr [rbp + 0x4c8]
0x6729d98  movss dword ptr [rdx + 0x20], xmm0
0x6729d9d  movss xmm0, dword ptr [rbp + 0x4cc]
0x6729da5  movss dword ptr [rdx + 0x24], xmm0
0x6729daa  movups xmm0, xmmword ptr [rbx + 0x80]
0x6729db1  movups xmm1, xmmword ptr [rbx + 0x90]
0x6729db8  movups xmm2, xmmword ptr [rbx + 0x9f]
0x6729dbf  movups xmmword ptr [rdx + 0x28], xmm0
0x6729dc3  movups xmmword ptr [rdx + 0x38], xmm1
0x6729dc7  movups xmmword ptr [rdx + 0x47], xmm2
0x6729dcb  add qword ptr [r14 + 0x758], 0x58
0x6729dd3  jmp 0x6729de9
0x6729dd5  lea rcx, [r14 + 0x750]
0x6729ddc  lea r8, [rbp + 0x4a8]
0x6729de3  call 0x6760a80
0x6729de8  nop
0x6729de9  mov rcx, qword ptr [rip + 0xbc143c0]
0x6729df0  mov rax, qword ptr [rcx]
0x6729df3  mov rax, qword ptr [rax + 0x10]
0x6729df7  movzx edx, byte ptr [rbp + 0x818]
```
// interpretation: Phase 20: completes dispatch call qword ptr [rip+0x927625e](dl=0x4a); stores al to [rbp+0x818]. Writes element at [r14+0x758]: if [r14+0x758]==[r14+0x760] jump to 0x6729dd5 (refill via 0x6760a80 on [r14+0x750]); else copies [rbp+0x4a8] dword[0x10] to [rdx+0x10], movups [rdx]=[rcx], byte [rbp+0x4bc]->[rdx+0x14], floats [rbp+0x4c0]->[rdx+0x18], [rbp+0x4c4]->[rdx+0x1c], [rbp+0x4c8]->[rdx+0x20], [rbp+0x4cc]->[rdx+0x24], movups [rbx+0x80]->[rdx+0x28], [rbx+0x90]->[rdx+0x38], [rbx+0x9f]->[rdx+0x47]. Advances [r14+0x758]+=0x58, jmp 0x6729de9. Refill path calls 0x6760a80(rcx=&[r14+0x750], r8=&[rbp+0x4a8]). Then starts dispatch at 0x6729de9–0x6729df7 (load [rip], vtable, movzx edx [rbp+0x818]). [V] every instruction address/op copied from disrange output at 0x6729d33–0x6729df7.

## Phase 21 (0x6729dfe–0x6729eb9)
```
0x6729dfe  call qword ptr [rip + 0x927619c]
0x6729e04  nop
0x6729e05  mov eax, dword ptr [r14 + 0x758]
0x6729e0c  sub eax, dword ptr [r14 + 0x750]
0x6729e13  shr eax, 3
0x6729e16  imul eax, eax, 0xffff8ba3
0x6729e1c  dec eax
0x6729e1e  mov word ptr [rbp + 0x58c], ax
0x6729e25  mov rcx, qword ptr [rip + 0xbc14384]
0x6729e2c  mov rax, qword ptr [rcx]
0x6729e2f  mov rax, qword ptr [rax + 0x10]
0x6729e33  mov dl, 0x4a
0x6729e35  call qword ptr [rip + 0x9276165]
0x6729e3b  nop
0x6729e3c  mov byte ptr [rbp + 0x818], al
0x6729e42  mov rdx, qword ptr [r14 + 0x860]
0x6729e49  cmp rdx, qword ptr [r14 + 0x868]
0x6729e50  je 0x6729e5e
0x6729e52  inc rdx
0x6729e55  mov qword ptr [r14 + 0x860], rdx
0x6729e5c  jmp 0x6729e6b
0x6729e5e  lea rcx, [r14 + 0x858]
0x6729e65  call 0x6760e60
0x6729e6a  nop
0x6729e6b  mov rcx, qword ptr [rip + 0xbc1433e]
0x6729e72  mov rax, qword ptr [rcx]
0x6729e75  mov rax, qword ptr [rax + 0x10]
0x6729e79  movzx edx, byte ptr [rbp + 0x818]
0x6729e80  call qword ptr [rip + 0x927611a]
0x6729e86  nop
0x6729e87  mov qword ptr [rbp + 0x560], 0x4009
0x6729e92  mov eax, dword ptr [r14 + 0x858]
0x6729e99  not eax
0x6729e9b  add eax, dword ptr [r14 + 0x860]
0x6729ea2  mov word ptr [rbp + 0x576], ax
0x6729ea9  mov rcx, qword ptr [rip + 0xbc14300]
0x6729eb0  mov rax, qword ptr [rcx]
0x6729eb3  mov rax, qword ptr [rax + 0x10]
0x6729eb7  mov dl, 0x4a
0x6729eb9  call qword ptr [rip + 0x92760e1]
```
// interpretation: Phase 21: completes dispatch call qword ptr [rip+0x927619c]. Computes ([r14+0x758]-[r14+0x750])>>3, scales by 0xffff8ba3 (/7), decrements, stores to [rbp+0x58c]. Dispatch call qword ptr [rip+0x9276165](dl=0x4a); stores al to [rbp+0x818]. rdx=[r14+0x860]; if ==[r14+0x868] jump to 0x6729e5e (refill via 0x6760e60 on [r14+0x858]); else inc [r14+0x860], jmp 0x6729e6b. Dispatch call qword ptr [rip+0x927611a](dl=[rbp+0x818]); stores [rbp+0x560]=0x4009. Computes ~[r14+0x858]+[r14+0x860] -> [rbp+0x576]. Starts dispatch at 0x6729ea9–0x6729eb9 (load [rip], vtable, dl=0x4a, call qword ptr [rip+0x92760e1]). [V] every instruction address/op copied from disrange output at 0x6729dfe–0x6729eb9.

## Phase 22 (0x6729ebf–0x6729f83)
```
0x6729ebf  mov byte ptr [rbp + 0x818], al
0x6729ec5  lea rcx, [r14 + 0x648]
0x6729ecc  lea rdx, [rbp + 0x458]
0x6729ed3  call 0x675fb30
0x6729ed8  nop
0x6729ed9  mov rcx, qword ptr [rip + 0xbc142d0]
0x6729ee0  mov rax, qword ptr [rcx]
0x6729ee3  mov rax, qword ptr [rax + 0x10]
0x6729ee7  movzx edx, byte ptr [rbp + 0x818]
0x6729eee  call qword ptr [rip + 0x92760ac]
0x6729ef4  nop
0x6729ef5  mov eax, dword ptr [r14 + 0x650]
0x6729efc  sub eax, dword ptr [r14 + 0x648]
0x6729f03  shr eax, 3
0x6729f06  imul eax, eax, 0xffff8e39
0x6729f0c  dec eax
0x6729f0e  mov word ptr [rbp + 0x5a2], ax
0x6729f15  lea rcx, [r14 + 0x780]
0x6729f1c  lea rdx, [rbp + 0x400]
0x6729f23  call 0x675f3b0
0x6729f28  nop
0x6729f29  mov eax, dword ptr [r14 + 0x788]
0x6729f30  sub eax, dword ptr [r14 + 0x780]
0x6729f37  shr eax, 3
0x6729f3a  imul eax, eax, 0xffff8ba3
0x6729f40  dec eax
0x6729f42  mov word ptr [rbp + 0x588], ax
0x6729f49  mov rcx, qword ptr [rip + 0xbc14260]
0x6729f50  mov rax, qword ptr [rcx]
0x6729f53  mov rax, qword ptr [rax + 0x10]
0x6729f57  mov dl, 0x4a
0x6729f59  call qword ptr [rip + 0x9276041]
0x6729f5f  mov byte ptr [rbp + 0x818], al
0x6729f65  mov rdi, qword ptr [r14 + 0x770]
0x6729f6c  cmp rdi, qword ptr [r14 + 0x778]
0x6729f73  je 0x6729fb6
0x6729f75  mov rax, qword ptr [rbp + 0x378]
0x6729f7c  mov qword ptr [rdi], rax
0x6729f7f  lea rcx, [rdi + 8]
0x6729f83  lea rdx, [rbp + 0x380]
```
// interpretation: Phase 22: stores al to [rbp+0x818]. Calls 0x675fb30(rcx=&[r14+0x648], rdx=&[rbp+0x458]). Dispatch call qword ptr [rip+0x92760ac](dl=[rbp+0x818]). Computes ([r14+0x650]-[r14+0x648])>>3, scales by 0xffff8e39 (/7), decrements, stores to [rbp+0x5a2]. Calls 0x675f3b0(rcx=&[r14+0x780], rdx=&[rbp+0x400]). Computes ([r14+0x788]-[r14+0x780])>>3, scales by 0xffff8ba3 (/7), decrements, stores to [rbp+0x588]. Dispatch call qword ptr [rip+0x9276041](dl=0x4a); stores al to [rbp+0x818]. Then rdi=[r14+0x770]; if ==[r14+0x778] jump to 0x6729fb6 (refill via 0x6760710); else [rdi]=[rbp+0x378], lea rcx,[rdi+8], lea rdx,[rbp+0x380] (prepares call 0xe869ff0). [V] every instruction address/op copied from disrange output at 0x6729ebf–0x6729f83.

## Phase 23 (0x6729f8a–0x672a054)
```
0x6729f8a  call 0xe869ff0
0x6729f8f  nop
0x6729f90  mov rax, qword ptr [rbp + 0x3f8]
0x6729f97  mov qword ptr [rdi + 0x80], rax
0x6729f9e  mov qword ptr [rbp + 0x3f8], 0
0x6729fa9  add qword ptr [r14 + 0x770], 0x88
0x6729fb4  jmp 0x6729fcd
0x6729fb6  lea rcx, [r14 + 0x768]
0x6729fbd  mov rdx, rdi
0x6729fc0  lea r8, [rbp + 0x378]
0x6729fc7  call 0x6760710
0x6729fcc  nop
0x6729fcd  mov rcx, qword ptr [rip + 0xbc141dc]
0x6729fd4  mov rax, qword ptr [rcx]
0x6729fd7  mov rax, qword ptr [rax + 0x10]
0x6729fdb  movzx edx, byte ptr [rbp + 0x818]
0x6729fe2  call qword ptr [rip + 0x9275fb8]
0x6729fe8  nop
0x6729fe9  mov qword ptr [rbp + 0x560], 0x2007009
0x6729ff4  mov eax, dword ptr [r14 + 0x770]
0x6729ffb  sub eax, dword ptr [r14 + 0x768]
0x672a002  shr eax, 3
0x672a005  imul eax, eax, 0xfffff0f1
0x672a00b  dec eax
0x672a00d  mov word ptr [rbp + 0x58a], ax
0x672a014  mov rcx, qword ptr [rip + 0xbc14195]
0x672a01b  mov rax, qword ptr [rcx]
0x672a01e  mov rax, qword ptr [rax + 0x10]
0x672a022  mov dl, 0x4a
0x672a024  call qword ptr [rip + 0x9275f76]
0x672a02a  nop
0x672a02b  mov byte ptr [rbp + 0x818], al
0x672a031  mov rdx, qword ptr [r14 + 0x2d8]
0x672a038  cmp rdx, qword ptr [r14 + 0x2e0]
0x672a03f  je 0x672a04d
0x672a041  inc rdx
0x672a044  mov qword ptr [r14 + 0x2d8], rdx
0x672a04b  jmp 0x672a05a
0x672a04d  lea rcx, [r14 + 0x2d0]
0x672a054  call 0x6760e60
```
// interpretation: Phase 23: call 0xe869ff0(rcx=[rdi+8], rdx=&[rbp+0x380]) — fills from tail buffer. rax=[rbp+0x3f8]; [rdi+0x80]=rax; [rbp+0x3f8]=0. [r14+0x770]+=0x88, jmp 0x6729fcd. Refill path (je taken at 0x6729f73): lea rcx,[r14+0x768], rdx=rdi, lea r8,[rbp+0x378], call 0x6760710(refill). Then 0x6729fcd starts dispatch: load [rip], vtable, movzx edx [rbp+0x818], call qword ptr [rip+0x9275fb8]. Store [rbp+0x560]=0x2007009. Computes ([r14+0x770]-[r14+0x768])>>3, scales by 0xfffff0f1 (/15), decrements, stores to [rbp+0x58a]. Next dispatch at 0x672a014–0x672a02b (vtable, dl=0x4a, call qword ptr [rip+0x9275f76]; al->[rbp+0x818]). rdx=[r14+0x2d8]; if ==[r14+0x2e0] jump to 0x672a04d (refill via 0x6760e60 on [r14+0x2d0]); else inc [r14+0x2d8], jmp 0x672a05a. [V] every instruction address/op copied from disrange output at 0x6729f8a–0x672a054.

## Phase 24 (0x672a059–0x672a113)
```
0x672a059  nop
0x672a05a  mov rcx, qword ptr [rip + 0xbc1414f]
0x672a061  mov rax, qword ptr [rcx]
0x672a064  mov rax, qword ptr [rax + 0x10]
0x672a068  movzx edx, byte ptr [rbp + 0x818]
0x672a06f  call qword ptr [rip + 0x9275f2b]
0x672a075  nop
0x672a076  mov eax, dword ptr [r14 + 0x2d0]
0x672a07d  not eax
0x672a07f  add eax, dword ptr [r14 + 0x2d8]
0x672a086  mov word ptr [rbp + 0x5ec], ax
0x672a08d  mov rcx, qword ptr [rip + 0xbc1411c]
0x672a094  mov rax, qword ptr [rcx]
0x672a097  mov rax, qword ptr [rax + 0x10]
0x672a09b  mov dl, 0x4a
0x672a09d  call qword ptr [rip + 0x9275efd]
0x672a0a3  nop
0x672a0a4  mov byte ptr [rbp + 0x818], al
0x672a0aa  mov rdx, qword ptr [r14 + 0x6b0]
0x672a0b1  cmp rdx, qword ptr [r14 + 0x6b8]
0x672a0b8  je 0x672a0c6
0x672a0ba  inc rdx
0x672a0bd  mov qword ptr [r14 + 0x6b0], rdx
0x672a0c4  jmp 0x672a0d6
0x672a0c6  mov rcx, r14
0x672a0c9  add rcx, 0x6a8
0x672a0d0  call 0x6760e60
0x672a0d5  nop
0x672a0d6  mov rcx, qword ptr [rip + 0xbc140d3]
0x672a0dd  mov rax, qword ptr [rcx]
0x672a0e0  mov rax, qword ptr [rax + 0x10]
0x672a0e4  movzx edx, byte ptr [rbp + 0x818]
0x672a0eb  call qword ptr [rip + 0x9275eaf]
0x672a0f1  nop
0x672a0f2  movabs rax, 0x4000000002207009
0x672a0fc  mov qword ptr [rbp + 0x560], rax
0x672a103  mov eax, dword ptr [r14 + 0x6a8]
0x672a10a  not eax
0x672a10c  add eax, dword ptr [r14 + 0x6b0]
0x672a113  mov word ptr [rbp + 0x59a], ax
```
// interpretation: Phase 24: finishes prior dispatch (nop at 0x672a059). Dispatch 0x672a05a–0x672a075 (load [rip], vtable, movzx edx [rbp+0x818], call qword ptr [rip+0x9275f2b]). Computes ~[r14+0x2d0]+[r14+0x2d8] -> [rbp+0x5ec]. Dispatch 0x672a08d–0x672a0a4 (vtable, dl=0x4a, call qword ptr [rip+0x9275efd]; al->[rbp+0x818]). rdx=[r14+0x6b0]; if ==[r14+0x6b8] jump to 0x672a0c6 (refill: mov rcx,r14; add rcx,0x6a8; call 0x6760e60); else inc [r14+0x6b0], jmp 0x672a0d6. Dispatch 0x672a0d6–0x672a0eb (vtable, movzx edx [rbp+0x818], call qword ptr [rip+0x9275eaf]). Store [rbp+0x560]=0x4000000002207009. Computes ~[r14+0x6a8]+[r14+0x6b0] -> [rbp+0x59a]. [V] every instruction address/op copied from disrange output at 0x672a059–0x672a113.

## Phase 25 (0x672a11a–0x672a1c0)
```
0x672a11a  mov rcx, qword ptr [rip + 0xbc1408f]
0x672a121  mov rax, qword ptr [rcx]
0x672a124  mov rax, qword ptr [rax + 0x10]
0x672a128  mov dl, 0x4a
0x672a12a  call qword ptr [rip + 0x9275e70]
0x672a130  nop
0x672a131  mov byte ptr [rbp + 0x818], al
0x672a137  mov rdx, qword ptr [r14 + 8]
0x672a13b  cmp rdx, qword ptr [r14 + 0x10]
0x672a13f  je 0x672a160
0x672a141  mov r8d, 0xc8
0x672a147  mov rcx, rdx
0x672a14a  lea rdx, [rbp + 0x560]
0x672a151  call 0xeec6ec0
0x672a156  add qword ptr [r14 + 8], 0xc8
0x672a15e  jmp 0x672a170
0x672a160  mov rcx, r14
0x672a163  lea r8, [rbp + 0x560]
0x672a16a  call 0x5aba6d0
0x672a16f  nop
0x672a170  mov rcx, qword ptr [rip + 0xbc14039]
0x672a177  mov rax, qword ptr [rcx]
0x672a17a  mov rax, qword ptr [rax + 0x10]
0x672a17e  movzx edx, byte ptr [rbp + 0x818]
0x672a185  call qword ptr [rip + 0x9275e15]
0x672a18b  nop
0x672a18c  lea rcx, [rbp + 0x370]
0x672a193  call 0x67e1840
0x672a198  mov rcx, r15
0x672a19b  nop dword ptr [rax + rax]
0x672a1a0  call 0x67e23f0
0x672a1a5  cmp byte ptr [rbp + 0x80], 3
0x672a1ac  jne 0x672a1f0
0x672a1ae  mov rdi, qword ptr [rbp + 0x78]
0x672a1b2  test rdi, rdi
0x672a1b5  je 0x672a1f0
0x672a1b7  lock dec dword ptr [rdi + 8]
0x672a1bb  jne 0x672a1f0
0x672a1bd  mov rax, qword ptr [rdi]
0x672a1c0  mov rax, qword ptr [rax]
```
// interpretation: Phase 25: dispatch 0x672a11a–0x672a131 (vtable, dl=0x4a, call qword ptr [rip+0x9275e70]; al->[rbp+0x818]). rdx=[r14+8]; if ==[r14+0x10] jump to 0x672a160 (refill path: mov rcx,r14; lea r8,[rbp+0x560]; call 0x5aba6d0); else mov r8d,0xc8; mov rcx,rdx; lea rdx,[rbp+0x560]; call 0xeec6ec0; [r14+8]+=0xc8; jmp 0x672a170. Dispatch 0x672a170–0x672a18b (vtable, movzx edx [rbp+0x818], call qword ptr [rip+0x9275e15]). lea rcx,[rbp+0x370]; call 0x67e1840; mov rcx,r15; nop; call 0x67e23f0. cmp byte [rbp+0x80],3; jne 0x672a1f0 (failure path). mov rdi,[rbp+0x78]; test rdi,rdi; je 0x672a1f0; lock dec dword ptr [rdi+8]; jne 0x672a1f0; mov rax,[rdi]; mov rax,[rax]. [V] every instruction address/op copied from disrange output at 0x672a11a–0x672a1c0.

## Phase 26 (0x672a1c3–0x672a266)
```
0x672a1c3  mov rcx, rdi
0x672a1c6  call qword ptr [rip + 0x9275dd4]
0x672a1cc  lock dec dword ptr [rdi + 0xc]
0x672a1d0  jne 0x672a1f0
0x672a1d2  mov rax, qword ptr [rdi]
0x672a1d5  mov rax, qword ptr [rax + 8]
0x672a1d9  mov rcx, rdi
0x672a1dc  call qword ptr [rip + 0x9275dbe]
0x672a1e2  nop word ptr cs:[rax + rax]
0x672a1f0  mov r14, qword ptr [rbp + 0x50]
0x672a1f4  test r14, r14
0x672a1f7  je 0x67230b0
0x672a1fd  mov r15, qword ptr [rbp + 0x58]
0x672a201  jmp 0x672a214
0x672a203  nop word ptr cs:[rax + rax]
0x672a210  add r14, 0x28
0x672a214  cmp r14, r15
0x672a217  je 0x67230b0
0x672a21d  cmp byte ptr [r14 + 0x18], 2
0x672a222  jne 0x672a210
0x672a224  mov rdi, qword ptr [r14 + 8]
0x672a228  test rdi, rdi
0x672a22b  je 0x672a210
0x672a22d  lock dec dword ptr [rdi + 8]
0x672a231  jne 0x672a210
0x672a233  mov rax, qword ptr [rdi]
0x672a236  mov rax, qword ptr [rax]
0x672a239  mov rcx, rdi
0x672a23c  call qword ptr [rip + 0x9275d5e]
0x672a242  lock dec dword ptr [rdi + 0xc]
0x672a246  jne 0x672a210
0x672a248  mov rax, qword ptr [rdi]
0x672a24b  mov rax, qword ptr [rax + 8]
0x672a24f  mov rcx, rdi
0x672a252  call qword ptr [rip + 0x9275d48]
0x672a258  jmp 0x672a210
0x672a25a  mov rsi, qword ptr [rbp + 0x548]
0x672a261  test rsi, rsi
0x672a264  je 0x672a291
0x672a266  lock dec dword ptr [rsi + 8]
```
// interpretation: Phase 26: call qword ptr [rip+0x9275dd4](rcx=rdi); lock dec dword ptr [rdi+0xc]; jne 0x672a1f0. If not: mov rax,[rdi]; mov rax,[rax+8]; mov rcx,rdi; call qword ptr [rip+0x9275dbe]; nop. Then 0x672a1f0: r14=[rbp+0x50]; test r14,r14; je 0x67230b0 (function exit). r15=[rbp+0x58]; jmp 0x672a214. Loop 0x672a210: r14+=0x28; cmp r14,r15; je 0x67230b0; cmp byte [r14+0x18],2; jne 0x672a210 (loop). If ==2: rdi=[r14+8]; test rdi,rdi; je 0x672a210; lock dec dword ptr [rdi+8]; jne 0x672a210; mov rax,[rdi]; mov rax,[rax]; mov rcx,rdi; call qword ptr [rip+0x9275d5e]; lock dec dword ptr [rdi+0xc]; jne 0x672a210; mov rax,[rdi]; mov rax,[rax+8]; mov rcx,rdi; call qword ptr [rip+0x9275d48]; jmp 0x672a210 (loop). After loop: rsi=[rbp+0x548]; test rsi,rsi; je 0x672a291; lock dec dword ptr [rsi+8]. [V] every instruction address/op copied from disrange output at 0x672a1c3–0x672a266.

## Phase 27 (0x672a26a–0x672a315)
```
0x672a26a  jne 0x672a291
0x672a26c  mov rax, qword ptr [rsi]
0x672a26f  mov rax, qword ptr [rax]
0x672a272  mov rcx, rsi
0x672a275  call qword ptr [rip + 0x9275d25]
0x672a27b  lock dec dword ptr [rsi + 0xc]
0x672a27f  jne 0x672a291
0x672a281  mov rax, qword ptr [rsi]
0x672a284  mov rax, qword ptr [rax + 8]
0x672a288  mov rcx, rsi
0x672a28b  call qword ptr [rip + 0x9275d0f]
0x672a291  mov rcx, qword ptr [rip + 0xbc13f18]
0x672a298  mov rax, qword ptr [rcx]
0x672a29b  mov rax, qword ptr [rax + 0x10]
0x672a29f  movzx edx, byte ptr [rbp + 0x817]
0x672a2a6  call qword ptr [rip + 0x9275cf4]
0x672a2ac  nop
0x672a2ad  movaps xmm6, xmmword ptr [rbp + 0x830]
0x672a2b4  movaps xmm7, xmmword ptr [rbp + 0x840]
0x672a2bb  movaps xmm8, xmmword ptr [rbp + 0x850]
0x672a2c3  movaps xmm9, xmmword ptr [rbp + 0x860]
0x672a2cb  movaps xmm10, xmmword ptr [rbp + 0x870]
0x672a2d3  movaps xmm11, xmmword ptr [rbp + 0x880]
0x672a2db  movaps xmm12, xmmword ptr [rbp + 0x890]
0x672a2e3  movaps xmm13, xmmword ptr [rbp + 0x8a0]
0x672a2eb  movaps xmm14, xmmword ptr [rbp + 0x8b0]
0x672a2f3  movaps xmm15, xmmword ptr [rbp + 0x8c0]
0x672a2fb  add rsp, 0x958
0x672a302  pop rbx
0x672a303  pop rdi
0x672a304  pop rsi
0x672a305  pop r12
0x672a307  pop r13
0x672a309  pop r14
0x672a30b  pop r15
0x672a30d  pop rbp
0x672a30e  ret
0x672a30f  call 0x78ed0
0x672a314  nop
0x672a315  mov ecx, 0x30
```
// interpretation: Phase 27: jne 0x672a291 (skip release); mov rax,[rsi]; mov rax,[rax]; mov rcx,rsi; call qword ptr [rip+0x9275d25]; lock dec dword ptr [rsi+0xc]; jne 0x672a291. Else: mov rax,[rsi]; mov rax,[rax+8]; mov rcx,rsi; call qword ptr [rip+0x9275d0f]. Then 0x672a291: dispatch (load [rip], vtable, movzx edx [rbp+0x817], call qword ptr [rip+0x9275cf4]). Restore XMM6-XMM15 from [rbp+0x830..0x8c0], add rsp,0x958, pop rbx/rdi/rsi/r12/r13/r14/r15/rbp, ret at 0x672a30e [V] = builder epilogue (function ends here per disassembly). Subsequent code 0x672a30f+ (call 0x78ed0, mov ecx,0x30, call 0x9bc830, jmp 0x6722ef2...) appears to be the following function per linear continuation toward 0x672a464. [V] every instruction address/op copied from disrange output at 0x672a26a–0x672a315.

## Phase 28 (0x672a31a–0x672a3cc)
```
0x672a31a  call 0x9bc830
0x672a31f  nop
0x672a320  jmp 0x6722ef2
0x672a325  call 0xb432e0
0x672a32a  nop
0x672a32b  call 0x1166e0
0x672a330  nop
0x672a331  call 0x1166e0
0x672a336  nop
0x672a337  mov qword ptr [rsp + 0x20], 0
0x672a340  xor ecx, ecx
0x672a342  xor edx, edx
0x672a344  xor r8d, r8d
0x672a347  xor r9d, r9d
0x672a34a  call qword ptr [rip + 0x927e928]
0x672a350  lea rcx, [rip + 0xc2d1051]
0x672a357  call 0xe938cb0
0x672a35c  cmp dword ptr [rip + 0xc2d1045], -1
0x672a363  jne 0x6722d79
0x672a369  lea rdx, [rip + 0x8ee3e33]
0x672a370  lea r14, [rbp + 0x560]
0x672a377  mov rcx, r14
0x672a37a  call 0x79580
0x672a37f  nop
0x672a380  mov r8, qword ptr [rbp + 0x570]
0x672a387  cmp qword ptr [rbp + 0x578], 0x10
0x672a38f  jb 0x672a398
0x672a391  mov r14, qword ptr [rbp + 0x560]
0x672a398  test r8, r8
0x672a39b  je 0x672a3c2
0x672a39d  mov eax, r8d
0x672a3a0  and eax, 3
0x672a3a3  movabs rcx, 0x100000001b3
0x672a3ad  cmp r8, 4
0x672a3b1  jae 0x672a3ce
0x672a3b3  movabs rdx, 0xcbf29ce484222325
0x672a3bd  xor r9d, r9d
0x672a3c0  jmp 0x672a420
0x672a3c2  movabs rdx, 0xcbf29ce484222325
0x672a3cc  jmp 0x672a440
```
// interpretation: Phase 28: this is post-builder code (builder ret at 0x672a30e); appears to be the following function's failure path. call 0x9bc830; jmp 0x6722ef2; call 0xb432e0; call 0x1166e0; call 0x1166e0; [rsp+0x20]=0; xor ecx/edx/r8d/r9d; call qword ptr [rip+0x927e928] (GetLastError likely); lea rcx,[rip+0xc2d1051]; call 0xe938cb0; cmp dword [rip+0xc2d1045],-1; jne 0x6722d79. lea rdx,[rip+0x8ee3e33]; lea r14,[rbp+0x560]; mov rcx,r14; call 0x79580. r8=[rbp+0x570]; cmp qword [rbp+0x578],0x10; jb 0x672a398 (small-buffer); else r14=[rbp+0x560]. test r8,r8; je 0x672a3c2 (empty). eax=r8d & 3; movabs rcx,0x100000001b3 (FNV prime); cmp r8,4; jae 0x672a3ce (aligned loop). Else: movabs rdx,0xcbf29ce484222325 (FNV offset basis); xor r9d,r9d; jmp 0x672a420 (scalar loop). Empty: movabs rdx,0xcbf29ce484222325; jmp 0x672a440. [V] every instruction address/op copied from disrange output at 0x672a31a–0x672a3cc. Note: 0x672a30f–0x672a464 is the next function, not the builder (builder ended at ret 0x672a30e [V]); continuing linearly per task end marker 0x672a464.

## Phase 29 (0x672a3ce–0x672a45f) — FINAL (reaches end marker 0x672a464)
```
0x672a3ce  and r8, 0xfffffffffffffffc
0x672a3d2  movabs rdx, 0xcbf29ce484222325
0x672a3dc  xor r9d, r9d
0x672a3df  movzx r10d, byte ptr [r14 + r9]
0x672a3e4  xor r10, rdx
0x672a3e7  imul r10, rcx
0x672a3eb  movzx edx, byte ptr [r14 + r9 + 1]
0x672a3f1  xor rdx, r10
0x672a3f4  imul rdx, rcx
0x672a3f8  movzx r10d, byte ptr [r14 + r9 + 2]
0x672a3fe  xor r10, rdx
0x672a401  imul r10, rcx
0x672a405  movzx edx, byte ptr [r14 + r9 + 3]
0x672a40b  xor rdx, r10
0x672a40e  imul rdx, rcx
0x672a412  add r9, 4
0x672a416  cmp r8, r9
0x672a419  jne 0x672a3df
0x672a41b  test rax, rax
0x672a41e  je 0x672a440
0x672a420  add r14, r9
0x672a423  xor r8d, r8d
0x672a426  mov r9, rdx
0x672a429  movzx edx, byte ptr [r14 + r8]
0x672a42e  xor rdx, r9
0x672a431  imul rdx, rcx
0x672a435  inc r8
0x672a438  mov r9, rdx
0x672a43b  cmp rax, r8
0x672a43e  jne 0x672a429
0x672a440  mov qword ptr [rip + 0xc2d0f59], rdx
0x672a447  lea rcx, [rbp + 0x560]
0x672a44e  call 0x73150
0x672a453  lea rcx, [rip + 0xc2d0f4e]
0x672a45a  call 0xe938d70
0x672a45f  jmp 0x6722d79
```
// interpretation: Phase 29 (final): FNV-1a hash loop. and r8, 0xfffffffffffffffc (align down to 4); movabs rdx, 0xcbf29ce484222325 (FNV offset basis); xor r9d,r9d. Aligned loop 0x672a3df: movzx r10d,[r14+r9]; xor r10,rdx; imul r10,rcx(0x100000001b3 FNV prime); process bytes +1,+2,+3 similarly; add r9,4; cmp r8,r9; jne 0x672a3df. test rax,rax; je 0x672a440 (done). Scalar tail 0x672a420: add r14,r9; xor r8d,r8d; mov r9,rdx; movzx edx,[r14+r8]; xor rdx,r9; imul rdx,rcx; inc r8; mov r9,rdx; cmp rax,r8; jne 0x672a429. Store hash: mov qword [rip+0xc2d0f59], rdx. lea rcx,[rbp+0x560]; call 0x73150 (cleanup/free). lea rcx,[rip+0xc2d0f4e]; call 0xe938d70; jmp 0x6722d79 at 0x672a45f (5 bytes) ends exactly at 0x672a464 = task end marker [V]. UNIT COMPLETE: full range 0x6728f55–0x672a464 disassembled in 29 phases (phases 1-27 builder function ending at ret 0x672a30e [V]; phases 28-29 next function's failure/FNV path ending at 0x672a464). No (bad) instructions encountered.

## NEXT
UNIT COMPLETE. All phases 1-29 written to docs/progress/oc_U-E4-H10.md covering 0x6728f55–0x672a464. No further work.

## Status (complete)
- [x] Phases 1-27: builder function 0x6728f55–0x672a315 (epilogue ret 0x672a30e [V])
- [x] Phases 28-29: next function failure/FNV path 0x672a31a–0x672a45f (ends at 0x672a464 [V])
- [x] All 29 phases appended as fenced `0xRVA  mnemonic operands` blocks + // interpretation, tagged [V]


## Notes
- Unit target: builder 0x6722cb0, ends 0x672a464. This progress covers the range starting 0x6728f55 through 0x672a464.
- rdis exe: tools/rdis/target/release/rdis.exe
- Target exe: C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe
- All claims tagged [V] (seen in disassembly) / [I] (inferred) / [?] (unknown).
