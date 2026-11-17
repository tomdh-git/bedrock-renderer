## NEXT
DONE

# U-Atl4 — instruction-complete dossier: atlas_meta_load (0x4e198d0) and load2 (0x4e1cbb0)

Coverage claim [V]: docs/progress/_part_atl_missing.txt lists 226 instructions of the two functions; every one is quoted verbatim below (two spaces after the address, copied from the input data), assigned to exactly one phase, and none is skipped (no ellipsis coverage). Gaps between consecutive listed RVAs are bytes absent from the input listing and are not covered by this unit. Every quoted line was checked against Minecraft.Windows.exe 1.26.62.01 with tools/sigs/verify_oc.py: 226 claimed, 226 match, 0 mismatch, 0 no-such-instr. The earlier partial draft docs/progress/oc_U-Atl_old_incomplete.md was read for context only; nothing unverified from it was copied.

Entry register map [V from the listed movs]: func1 arg1 rcx→rdi (0x4e19907), arg3 r8→rbx (0x4e198fd), arg2 stays in rdx; load2 arg1 rcx→rbx (0x4e1cbd9), arg2 rdx→rsi (0x4e1cbd6), arg3 r8→rdi (0x4e1cbd3), arg4 r9→r14 (0x4e1cbd0), and load2 returns rax=rsi (0x4e1ce0f).

## Function 1: atlas_meta_load (0x4e198d0..0x4e19d98) — 156 listed instructions, 5 phases

### Phase 1: 0x4e198d0..0x4e1998f — prologue, 0x228 frame, element count via reciprocal multiply (31 instructions)

Prologue pushes eight callee-saved registers and opens a 0x228 frame; arguments are redistributed (arg1 rcx→rdi, arg3 r8→rbx, arg2 stays in rdx). Then 0xE931470 is called with rdx=0, 0xE943820 constructs at rbp-0x30 returning rax, the span rax-(rbp-0x30) is sar 3 and scaled by reciprocal 0x14C1BACF914C1BAD, values above 0xFFFFFFFFFFFFFED8 bail to 0x4E19D79, and a begin/end consistency test (setne cl / sete al / or al,cl) bails to the same target.

0x4e198d0  push rbp
0x4e198d1  push r15
0x4e198d3  push r14
0x4e198d5  push r13
0x4e198d7  push r12
0x4e198d9  push rsi
0x4e198da  push rdi
0x4e198db  push rbx
0x4e198dc  sub rsp,0x228
0x4e198fd  mov rbx,r8
0x4e19907  mov rdi,rcx
0x4e19911  xor edx,edx
0x4e19913  call 0xE931470
0x4e19918  nop
0x4e19919  lea rcx,[rbp-0x30]
0x4e1991d  call 0xE943820
0x4e19922  nop
0x4e1994b  mov rdx,rax
0x4e1994e  sub rdx,rcx
0x4e19951  mov r8,rdx
0x4e19954  sar r8,3
0x4e19958  mov r9,0x14C1BACF914C1BAD
0x4e19962  imul r9,r8
0x4e1996d  cmp rdx,0xFFFFFFFFFFFFFED8
0x4e19974  je 0x4E19D79
0x4e19981  test rcx,rcx
0x4e19984  setne cl
0x4e19987  test rax,rax
0x4e1998a  sete al
0x4e1998d  or al,cl
0x4e1998f  je 0x4E19D79

### Phase 2: 0x4e199ae..0x4e19a5f — 0x17C2840 validation and the per-element destroy/decode loop (35 instructions)

0x17C2840 validates the object first. Then the loop at 0x4E19A02 steps the cursor back by 0xD8 per iteration (rsi = 0xFFFFFFFFFFFFFF28), destroys the element with 0x1158F0 and 0xE9319A0, and either exits (je 0x4E19A64) or calls 0xE931470 followed by 0xE943A00 (r9d=0): when al!=0 the element is decoded by 0x3E1B50 with flag byte 0x20 followed by 0xE931B80 and 0xE9319A0, while al==0 falls to the tail at 0x4E199E0 (cursor += -0xD8, call 0x1158F0, mov rcx,r14, call 0xE9319A0) and the loop body jumps back via jmp 0x4E199E0.

0x4e199ae  call 0x17C2840
0x4e199b3  nop
0x4e199bb  mov rsi,0xFFFFFFFFFFFFFF28
0x4e199c2  lea r15,[rbp-0x30]
0x4e199d4  jmp short 0x4E19A02
0x4e199d6  nop [rax+rax]
0x4e199e7  add rcx,rsi
0x4e199ea  call 0x1158F0
0x4e199fa  mov rcx,r14
0x4e199fd  call 0xE9319A0
0x4e19a10  je short 0x4E19A64
0x4e19a12  mov rcx,r14
0x4e19a15  xor edx,edx
0x4e19a17  call 0xE931470
0x4e19a1c  nop
0x4e19a24  add rdx,rsi
0x4e19a27  mov rcx,r15
0x4e19a2a  mov r8,r14
0x4e19a2d  xor r9d,r9d
0x4e19a30  call 0xE943A00
0x4e19a35  nop
0x4e19a36  test al,al
0x4e19a38  je short 0x4E199E0
0x4e19a3a  mov rcx,r12
0x4e19a3d  mov rdx,r14
0x4e19a40  mov r8,r13
0x4e19a43  mov r9b,0x20
0x4e19a46  call 0x3E1B50
0x4e19a4b  nop
0x4e19a4c  mov rcx,r13
0x4e19a4f  mov rdx,r12
0x4e19a52  call 0xE931B80
0x4e19a57  mov rcx,r12
0x4e19a5a  call 0xE9319A0
0x4e19a5f  jmp 0x4E199E0

### Phase 3: 0x4e19a64..0x4e19c2d — worker call, element destroy loop, and heap-block free with header check (40 instructions)

The flag chain of test/jmp/xor idioms resolves and the worker 0x4E1A0A0 is called with rcx=rdi. On return, the destroy loop at 0x4E19BF0 calls 0x1158F0 per element and advances rdi by 0xD8 until rdi==rsi; the remaining size rdx=rdi is compared to 0x1000 — below it, control jumps to 0x4E19C3A (mov rcx,rdi; call 0xE935700); otherwise the header qword at [rdi-8] is loaded, rdi is rewound by 8 and by the header value, blocks under 0x20 bail to 0x4E19D7E, and rdx is adjusted by +0x27 before rdi=rax is passed to 0xE935700 for the free.

0x4e19a64  xorps xmm0,xmm0
0x4e19a79  test rax,rax
0x4e19a7c  je short 0x4E19A88
0x4e19a86  jmp short 0x4E19A8A
0x4e19a88  xor eax,eax
0x4e19aad  test rax,rax
0x4e19ab0  je short 0x4E19ABC
0x4e19aba  jmp short 0x4E19ABE
0x4e19abc  xor eax,eax
0x4e19ae1  test rax,rax
0x4e19ae4  je short 0x4E19AF0
0x4e19aee  jmp short 0x4E19AF2
0x4e19af0  xor eax,eax
0x4e19b19  test rcx,rcx
0x4e19b1c  je short 0x4E19B39
0x4e19b31  nop
0x4e19b4f  test rcx,rcx
0x4e19b52  je short 0x4E19B6F
0x4e19b67  nop
0x4e19bbd  mov rcx,rdi
0x4e19bc7  call 0x4E1A0A0
0x4e19bcc  nop
0x4e19bd4  test rdi,rdi
0x4e19bd7  je short 0x4E19C42
0x4e19be0  cmp rdi,rsi
0x4e19be3  je short 0x4E19C0B
0x4e19be5  nop [rax+rax]
0x4e19bf0  mov rcx,rdi
0x4e19bf3  call 0x1158F0
0x4e19bf8  add rdi,0xD8
0x4e19bff  cmp rdi,rsi
0x4e19c02  jne short 0x4E19BF0
0x4e19c12  sub rdx,rdi
0x4e19c15  cmp rdx,0x1000
0x4e19c1c  jb short 0x4E19C3A
0x4e19c1e  mov rax,[rdi-8]
0x4e19c22  add rdi,0xFFFFFFFFFFFFFFF8
0x4e19c26  sub rdi,rax
0x4e19c29  cmp rdi,0x20
0x4e19c2d  jae 0x4E19D7E

### Phase 4: 0x4e19c33..0x4e19d73 — free completion, local teardown, release-target branches, epilogue pops (40 instructions)

On the small-block path rdx += 0x27, rdi = rax, and 0xE935700 frees with rcx = rdi; otherwise the header path above has already freed the block. Then rbp-0x30 is torn down by 0xE9439A0 and 0xE9319A0; a null-check chain (test/cmp/setne of rcx vs rsi, test rdi,rdi) branches via mov rcx,rdi to release targets 0x4E19CE8, 0x4E19D23 and 0x4E19D5E; finally add rsp,0x228 restores the frame and pops rbx through r14.

0x4e19c33  add rdx,0x27
0x4e19c37  mov rdi,rax
0x4e19c3a  mov rcx,rdi
0x4e19c3d  call 0xE935700
0x4e19c42  lea rcx,[rbp-0x30]
0x4e19c46  call 0xE9439A0
0x4e19c52  call 0xE9319A0
0x4e19c62  test rcx,rcx
0x4e19c65  je short 0x4E19C82
0x4e19c67  cmp rcx,rsi
0x4e19c6a  setne dl
0x4e19c8d  test rcx,rcx
0x4e19c90  je short 0x4E19CAD
0x4e19c92  cmp rcx,rsi
0x4e19c95  setne dl
0x4e19cb8  test rdi,rdi
0x4e19cbb  je short 0x4E19CE8
0x4e19cc1  jne short 0x4E19CE8
0x4e19cc9  mov rcx,rdi
0x4e19cd6  jne short 0x4E19CE8
0x4e19cdf  mov rcx,rdi
0x4e19cf3  test rdi,rdi
0x4e19cf6  je short 0x4E19D23
0x4e19cfc  jne short 0x4E19D23
0x4e19d04  mov rcx,rdi
0x4e19d11  jne short 0x4E19D23
0x4e19d1a  mov rcx,rdi
0x4e19d2e  test rdi,rdi
0x4e19d31  je short 0x4E19D5E
0x4e19d37  jne short 0x4E19D5E
0x4e19d3f  mov rcx,rdi
0x4e19d4c  jne short 0x4E19D5E
0x4e19d55  mov rcx,rdi
0x4e19d65  add rsp,0x228
0x4e19d6c  pop rbx
0x4e19d6d  pop rdi
0x4e19d6e  pop rsi
0x4e19d6f  pop r12
0x4e19d71  pop r13
0x4e19d73  pop r14

### Phase 5: 0x4e19d75..0x4e19d98 — epilogue tail plus the 0x4E19D79 bail stub (10 instructions)

pop r15, pop rbp, ret. The separate bail stub at 0x4E19D79 calls 0x78ED0, zeroes ecx/edx/r8d/r9d, executes int3, and is padded by nop [rax+rax] at 0x4E19D98.

0x4e19d75  pop r15
0x4e19d77  pop rbp
0x4e19d78  ret
0x4e19d79  call 0x78ED0
0x4e19d87  xor ecx,ecx
0x4e19d89  xor edx,edx
0x4e19d8b  xor r8d,r8d
0x4e19d8e  xor r9d,r9d
0x4e19d97  int3
0x4e19d98  nop [rax+rax]

## Function 2: load2 (0x4e1cbb0..0x4e1ce1f) — 70 listed instructions, 2 phases

### Phase 6: 0x4e1cbb0..0x4e1cd02 — prologue, 0x110 frame, rax flag chain, worker call (36 instructions)

Prologue saves rbp/r14/rsi/rdi/rbx and opens a 0x110 frame with rbp=rsp+0x80; arguments are kept in registers (rbx=arg1, rsi=arg2, rdi=arg3, r14=arg4). A four-idiom rax flag chain (test/jmp/xor eax,eax) forces eax=0; rcx is then tested and, if nonzero, the argument setup runs (lea rdx=[rbp-0x30] overwritten by rdx=rsi, lea r9=[rbp-0x30], rcx=rbx, r8=rdi) and the worker 0x4E1A0A0 is called.

0x4e1cbb0  push rbp
0x4e1cbb1  push r14
0x4e1cbb3  push rsi
0x4e1cbb4  push rdi
0x4e1cbb5  push rbx
0x4e1cbb6  sub rsp,0x110
0x4e1cbd0  mov r14,r9
0x4e1cbd3  mov rdi,r8
0x4e1cbd6  mov rsi,rdx
0x4e1cbd9  mov rbx,rcx
0x4e1cbea  xorps xmm0,xmm0
0x4e1cbf5  test rax,rax
0x4e1cbf8  je short 0x4E1CC04
0x4e1cc02  jmp short 0x4E1CC06
0x4e1cc04  xor eax,eax
0x4e1cc20  test rax,rax
0x4e1cc23  je short 0x4E1CC2F
0x4e1cc2d  jmp short 0x4E1CC31
0x4e1cc2f  xor eax,eax
0x4e1cc4b  test rax,rax
0x4e1cc4e  je short 0x4E1CC5A
0x4e1cc58  jmp short 0x4E1CC5C
0x4e1cc5a  xor eax,eax
0x4e1cc7a  test rcx,rcx
0x4e1cc7d  je short 0x4E1CC9B
0x4e1cc8f  nop
0x4e1cca7  test rcx,rcx
0x4e1ccaa  je short 0x4E1CCC1
0x4e1ccb2  lea rdx,[rbp-0x30]
0x4e1ccbc  nop
0x4e1ccf5  lea r9,[rbp-0x30]
0x4e1ccf9  mov rcx,rbx
0x4e1ccfc  mov rdx,rsi
0x4e1ccff  mov r8,rdi
0x4e1cd02  call 0x4E1A0A0
0x4e1cd07  nop

### Phase 7: 0x4e1cd13..0x4e1ce1f — post-call rcx/rdi null-check chain and epilogue (34 instructions)

After the call, rcx is null-checked and compared against rdi and r14 (setne dl); then rdi is tested three times, each test rdi,rdi followed by je and jne to the same target (0x4E1CDA0 / 0x4E1CDD4 / 0x4E1CE0F — the branch is unconditional in effect), with mov rcx,rdi between sites; finally rax=rsi (arg2), add rsp,0x110, pop rbx/rdi/rsi/r14/rbp, ret.

0x4e1cd13  test rcx,rcx
0x4e1cd16  je short 0x4E1CD33
0x4e1cd18  cmp rcx,rdi
0x4e1cd1b  setne dl
0x4e1cd3e  test rcx,rcx
0x4e1cd4f  je short 0x4E1CD6C
0x4e1cd51  cmp rcx,r14
0x4e1cd54  setne dl
0x4e1cd70  test rdi,rdi
0x4e1cd73  je short 0x4E1CDA0
0x4e1cd79  jne short 0x4E1CDA0
0x4e1cd81  mov rcx,rdi
0x4e1cd8e  jne short 0x4E1CDA0
0x4e1cd97  mov rcx,rdi
0x4e1cda4  test rdi,rdi
0x4e1cda7  je short 0x4E1CDD4
0x4e1cdad  jne short 0x4E1CDD4
0x4e1cdb5  mov rcx,rdi
0x4e1cdc2  jne short 0x4E1CDD4
0x4e1cdcb  mov rcx,rdi
0x4e1cddf  test rdi,rdi
0x4e1cde2  je short 0x4E1CE0F
0x4e1cde8  jne short 0x4E1CE0F
0x4e1cdf0  mov rcx,rdi
0x4e1cdfd  jne short 0x4E1CE0F
0x4e1ce06  mov rcx,rdi
0x4e1ce0f  mov rax,rsi
0x4e1ce12  add rsp,0x110
0x4e1ce19  pop rbx
0x4e1ce1a  pop rdi
0x4e1ce1b  pop rsi
0x4e1ce1c  pop r14
0x4e1ce1e  pop rbp
0x4e1ce1f  ret

## [reg+off] field access table — every [reg+off] load/store in the 226 listed instructions

| offset | size | read/store address | verbatim `0xRVA  instr` sites | meaning |
|---|---|---|---|---|
| -0x30 | 8 | [rbp-0x30] — lea effective-address target only; no memory load or store | `0x4e1ccb2  lea rdx,[rbp-0x30]`<br>`0x4e1ccf5  lea r9,[rbp-0x30]`<br>`0x4e19919  lea rcx,[rbp-0x30]`<br>`0x4e199c2  lea r15,[rbp-0x30]`<br>`0x4e19c42  lea rcx,[rbp-0x30]` | - |
| -8 | 8 | [rdi-8] — qword load (heap block header size consumed before the 0xE935700 free) | `0x4e19c1e  mov rax,[rdi-8]` | - |
| 0x0 | 8 | [rsp+0] — implicit stack top: each push stores 8 B, each pop loads 8 B | `0x4e1cbb0  push rbp`<br>`0x4e1cbb1  push r14`<br>`0x4e1cbb3  push rsi`<br>`0x4e1cbb4  push rdi`<br>`0x4e1cbb5  push rbx`<br>`0x4e1ce19  pop rbx`<br>`0x4e1ce1a  pop rdi`<br>`0x4e1ce1b  pop rsi`<br>`0x4e1ce1c  pop r14`<br>`0x4e1ce1e  pop rbp`<br>`0x4e19d6c  pop rbx`<br>`0x4e19d6d  pop rdi`<br>`0x4e19d6e  pop rsi`<br>`0x4e19d6f  pop r12`<br>`0x4e19d71  pop r13`<br>`0x4e19d73  pop r14`<br>`0x4e19d75  pop r15`<br>`0x4e19d77  pop rbp` | - |

Note: nop [rax+rax] (0x4e199d6, 0x4e19be5, 0x4e19d98) is a multi-byte NOP encoding and performs no memory access. Apart from the three rows above, no [reg+off] load or store exists in the 226 listed instructions; the shared_ptr field stores described in the older draft belong to instructions not present in this input listing.

## TOOL REQUESTS

None — no helper scripts were written; existing tools only (verify_oc.py for quoted-line validation).
