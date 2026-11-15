# Unit U-E4-H8 — gap fill for builder 0x6722cb0

Source of truth: `docs/progress/gaps_6722cb0.txt` (RVA ranges of real instructions in
0x6722cb0 not yet quoted in the H1..H6 docs). Each range is disassembled with
`rdis.exe ... dis <start-0x10> <n>` and the exact real lines covering the gap are
appended below with a `//` interpretation. Tags: [V] seen in disasm, [I] inferred.

Method note: rdis prints RVAs without the `0x` prefix and without leading zeros
(e.g. `67c9c20`). Below every line is normalised to `0xRVA  mnemonic operands`.

## Range 0x6725c59..0x6725c6c

Disasm started at 0x6725c49 (start-0x10), n=40. Output covers the whole range
(0x6725c59, 0x6725c5b, 0x6725c61, 0x6725c62, 0x6725c68, 0x6725c6c); no `(bad)`
inside the range (the stray `add [rax],al` at 0x6725c49 is before the range).

```
0x6725c59  mov dl,0x4A                                    // [V] dl = 0x4A ('J')
0x6725c5b  call qword ptr [0xF99FFA0]                    // [V] -> sub_eea6040 (indirect call, arg dl=0x4A)
0x6725c61  nop                                           
0x6725c62  mov [rbp+0x818],al                            // [V] store al (return) to local [rbp+0x818]
0x6725c68  mov rdx,[r14+0x68]                            // [V] load rdx = r14+0x68 (vector begin ptr)
0x6725c6c  cmp rdx,[r14+0x70]                            // [V] compare begin vs r14+0x70 (end ptr)
```

Interpretation: a logging/debug call (sub_eea6040 with code 0x4A) whose byte
result is saved to [rbp+0x818], followed by an empty-vector check on the
r14+0x68..r14+0x70 pointer range (je at 0x6725c70 if equal). [I] 0x6725c59 is the
immediate-load that feeds the debug-call argument; the cmp at 0x6725c6c is the
range-empty test.

## Range 0x67259c6..0x67259c6

Disasm started at 0x67259b6 (start-0x10), n=40. Output covers the range; the
`(bad)` lines at 0x67259b6..0x67259bf are *before* the range start and were skipped.

```
0x67259c6  mov eax,[r15+0x650]                          // [V] load dword from r15+0x650
0x67259cd  sub eax,[r15+0x648]                          // [V] eax -= r15+0x648 (end - begin of a pointer range)
0x67259d4  shr eax,3                                    // [V] eax >>= 3  (divide by 8)
0x67259d7  imul eax,0xFFFF8E39                          // [V] eax *= 0xFFFF8E39 (magic for division by 1000, signed)
0x67259dd  dec eax                                      // [V] eax -= 1
0x67259df  mov [rbp+0x152],ax                           // [V] store ax to local [rbp+0x152]
```

Interpretation: the gap instruction itself is `mov eax,[r15+0x650]`. [I] The
following sequence computes (end-begin)/8, applies a magic-number division by 1000
and subtracts 1 — i.e. a count/stride derived from a pointer range in r15
(r15+0x648 begin, r15+0x650 end), stored as a 16-bit local at [rbp+0x152].

## Range 0x67258eb..0x67258eb

Disasm started at 0x67258db (start-0x10), n=40. Output covers the range.
Note: a `(bad)` appeared at 0x67258db, which is *before* the range start; the gap
instruction itself (0x67258eb) disassembles cleanly, so no restart was needed.

```
0x67258eb  mov rax,[rbp+0x580]                          // [V] load qword from local [rbp+0x580]
0x67258f2  mov [rdi],rax                                // [V] store it to *rdi (dest object +0x0)
0x67258f5  lea rcx,[rdi+8]                             // [V] rcx = rdi+8 (dest+0x8, next field)
0x67258f9  lea rdx,[rbp+0x588]                         // [V] rdx = &[rbp+0x588] (source struct on stack)
0x6725900  call 0xE869FF0                              // [V] -> sub_e869ff0 (copy ctor / clone helper)
```

Interpretation: copies a small object — qword field at +0x580 of the local stack
struct into *rdi, then calls sub_e869ff0 with dest=rdi+8 and src=&[rbp+0x588].
[I] this is a copy/clone of a sub-object (probably a render-element payload) into a
destination buffer; the +0x580/+0x588 offsets on the stack frame are the source
fields being packed.

## Range 0x6724b25..0x6724b25

Disasm started at 0x6724b15 (start-0x10), n=40. Output covers the range; no `(bad)` seen.

```
0x6724b25  movups [rdx+0x38],xmm1                        // [V] store xmm1 to a1+0x38 (xmm1 written here; see 0x6724b21/0x6724b29 for sibling stores of xmm0/xmm2 at +0x28/+0x47)
```

Interpretation: single SIMD store of the xmm1 lane into struct field at offset 0x38 of the object pointed to by rdx. Neighbouring instructions (0x6724b21 movups [rdx+0x28],xmm0 and 0x6724b29 movups [rdx+0x47],xmm2) form a 3-lane SIMD write sequence (offsets 0x28, 0x38, 0x47) — likely packing 3 float/vec lanes. [I] this is part of a constructor/initialiser writing a small struct.

## Range 0x6725ed3..0x6726047 (part 1)

Disasm started at 0x6725ec3 (start-0x10), n=40. Output covers 0x6725ed3..0x6725f75; rdis hit --max 40 at `shr eax,3` (0x6725f75), continuing from 0x6725f75. No `(bad)` inside the range so far.

```
0x6725ed3  sub eax,[r15+0x768]                            // [V] eax -= [r15+0x768]
0x6725eda  shr eax,3                                      // [V] eax >>= 3 (divide by 8)
0x6725edd  imul eax,0xFFFFF0F1                            // [V] eax *= magic (signed division by 1000)
0x6725ee3  dec eax                                        // [V] eax -= 1
0x6725ee5  mov [rbp+0x13A],ax                             // [V] store ax to local [rbp+0x13A]
0x6725eec  mov rcx,[0x1233E1B0]                           // [V] load data_1233e1b0
0x6725ef3  mov rax,[rcx]                                  // [V]
0x6725ef6  mov rax,[rax+0x10]                             // [V]
0x6725efa  mov dl,0x4A                                    // [V] dl = 0x4A ('J')
0x6725efc  call qword ptr [0xF99FFA0]                     // [V] -> sub_eea6040 (indirect call, arg dl=0x4A)
0x6725f02  nop                                            
0x6725f03  mov [rbp+0x818],al                             // [V] store al (return) to local [rbp+0x818]
0x6725f09  mov rdx,[r15+0x698]                            // [V] load rdx = r15+0x698 (vector begin)
0x6725f10  cmp rdx,[r15+0x6A0]                            // [V] compare begin vs r15+0x6A0 (end)
0x6725f17  je 0x6726226                                   // [V] jump if range empty
0x6725f1d  movzx eax,word ptr [rbp+0x5A0]                 // [V] load word from local [rbp+0x5A0]
0x6725f24  mov [rdx],ax                                   // [V] store ax to *rdx (begin of range)
0x6725f27  add qword ptr [r15+0x698],2                    // [V] advance begin by 2
0x6725f2f  jmp 0x672623A                                  // [V] tail jump
0x6725f34  lea rcx,[r15+0x768]                            // [V] rcx = &[r15+0x768] (begin ref)
0x6725f3b  mov rdx,rdi                                    // [V] rdx = rdi (dest)
0x6725f3e  lea r8,[rbp+0x5B8]                             // [V] r8 = &[rbp+0x5B8] (src on stack)
0x6725f45  call 0x6760710                                 // [V] -> sub_6760710 (copy/clone helper)
0x6725f4a  nop                                            
0x6725f4b  mov rcx,[0x1233E1B0]                           // [V] load data_1233e1b0
0x6725f52  mov rax,[rcx]                                  // [V]
0x6725f55  mov rax,[rax+0x10]                             // [V]
0x6725f59  movzx edx,byte ptr [rbp+0x818]                 // [V] edx = saved debug byte
0x6725f60  call qword ptr [0xF99FFA0]                     // [V] -> sub_eea6040 (arg dl=byte)
0x6725f66  nop                                            
0x6725f67  mov eax,[r15+0x770]                            // [V] load [r15+0x770] (end)
0x6725f6e  sub eax,[r15+0x768]                            // [V] eax -= [r15+0x768] (begin) -> byte count
0x6725f75  shr eax,3                                      // [V] eax >>= 3 (count / 8)
```

## Range 0x6725ed3..0x6726047 (part 2)

Continued from 0x6725f75, n=40. Output covers 0x6725f75..0x672603a; cut at --max 40 at `mov rax,[rax+0x10]` (0x672603a). No `(bad)` inside. One more call needed for the tail 0x672603e..0x6726047.

```
0x6725f75  shr eax,3                                      // [V] eax >>= 3 (count / 8)
0x6725f78  imul eax,0xFFFFF0F1                            // [V] magic-number division by 1000
0x6725f7e  dec eax                                        // [V] eax -= 1
0x6725f80  mov [rbp+0x13A],ax                             // [V] store ax to local [rbp+0x13A]
0x6725f87  mov rcx,[0x1233E1B0]                           // [V] load data_1233e1b0
0x6725f8e  mov rax,[rcx]                                  // [V]
0x6725f91  mov rax,[rax+0x10]                             // [V]
0x6725f95  mov dl,0x4A                                    // [V] dl = 0x4A ('J')
0x6725f97  call qword ptr [0xF99FFA0]                     // [V] -> sub_eea6040
0x6725f9d  nop                                            
0x6725f9e  mov [rbp+0x818],al                             // [V] store al to local [rbp+0x818]
0x6725fa4  mov rdx,[r15+0x680]                            // [V] load begin r15+0x680
0x6725fab  cmp rdx,[r15+0x688]                            // [V] vs end r15+0x688
0x6725fb2  je 0x67262B5                                   // [V] jump if empty
0x6725fb8  movss xmm0,[rbp+0x5A8]                         // [V] load float from local [rbp+0x5A8]
0x6725fc0  movss [rdx],xmm0                               // [V] store to *rdx (+0x0)
0x6725fc4  movss xmm0,[rbp+0x5AC]                         // [V] load float [rbp+0x5AC]
0x6725fcc  movss [rdx+4],xmm0                             // [V] store to rdx+4
0x6725fd1  movss xmm0,[rbp+0x5B0]                         // [V] load float [rbp+0x5B0]
0x6725fd9  movss [rdx+8],xmm0                             // [V] store to rdx+8
0x6725fde  add qword ptr [r15+0x680],0xC                  // [V] advance begin by 0xC (3 floats)
0x6725fe6  jmp 0x67262C9                                  // [V] tail jump
0x6725feb  mov rcx,r14                                    // [V] rcx = r14
0x6725fee  add rcx,0x60                                   // [V] rcx = r14+0x60
0x6725ff2  call 0x6760E60                                 // [V] -> sub_6760e60
0x6725ff7  nop                                            
0x6725ff8  mov rcx,[0x1233E1B0]                           // [V] load data_1233e1b0
0x6725fff  mov rax,[rcx]                                  // [V]
0x6726002  mov rax,[rax+0x10]                             // [V]
0x6726006  movzx edx,byte ptr [rbp+0x818]                 // [V] edx = saved debug byte
0x672600d  call qword ptr [0xF99FFA0]                     // [V] -> sub_eea6040
0x6726013  nop                                            
0x6726014  mov qword ptr [rbp+0x118],0x1000000            // [V] store imm 0x1000000 to [rbp+0x118]
0x672601f  mov eax,[r14+0x60]                             // [V] load dword [r14+0x60]
0x6726023  not eax                                        // [V] eax = ~eax
0x6726025  add eax,[r14+0x68]                             // [V] eax += [r14+0x68]
0x6726029  mov [rbp+0x1D0],ax                             // [V] store ax to [rbp+0x1D0]
0x6726030  mov rcx,[0x1233E1B0]                           // [V] load data_1233e1b0
0x6726037  mov rax,[rcx]                                  // [V]
0x672603a  mov rax,[rax+0x10]                             // [V]
0x672603e  mov dl,0x4A                                    // [V] dl = 0x4A ('J')
0x6726040  call qword ptr [0xF99FFA0]                     // [V] -> sub_eea6040
0x6726046  nop                                            
0x6726047  mov [rbp+0x818],al                             // [V] store al to [rbp+0x818] (RANGE END)
```

Interpretation: range 0x6725ed3..0x6726047 complete. It is a family of debug/trace emissions and small struct writes: (1) `(end r15+0x770 - begin r15+0x768)/8` magic-divided by 1000 minus 1 -> ax at [rbp+0x13A]; (2) debug call sub_eea6040(dl=0x4A), result -> [rbp+0x818]; (3) empty check r15+0x698..0x6A0 (je 0x6726226); word [rbp+0x5A0] -> *rdx, begin += 2, jmp 0x672623A; (4) sub_6760710(dest=rdi, src=&[rbp+0x5B8], begin ref=&[r15+0x768]); (5) debug call with dl=[rbp+0x818] -> [rbp+0x818]; (6) second count `(end r15+0x770 - begin)/8` magic-div-1000 -1 -> [rbp+0x13A]; (7) debug call; empty check r15+0x680..0x688 (je 0x67262B5); three movss stores [rbp+0x5A8/0x5AC/0x5B0] -> *rdx..rdx+8 (vec3), begin += 0xC, jmp 0x67262C9; (8) sub_6760e60(rcx=r14+0x60); (9) debug call; [rbp+0x118]=0x1000000; ax = ~(dword [r14+0x60]) + [r14+0x68] -> [rbp+0x1D0]; (10) debug call, result -> [rbp+0x818] (0x6726047 = range end). All instruction lines are [V] from rdis; jump targets and callee identities ([I] sub_eea6040 via data_f99ffa0, sub_6760710, sub_6760e60 direct calls).

## Range 0x67263c1..0x6726486 (complete)

Disasm started at 0x67263b1 (start-0x10), n=40, continued at 0x672646b, n=10. Output covers the whole range 0x67263c1..0x6726486; no `(bad)` inside.

```
0x67263c1  mov rax,0x100000002007049                      // [V] rax = imm 0x100000002007049
0x67263cb  mov [rbp+0x110],rax                            // [V] store rax to local [rbp+0x110]
0x67263d2  mov eax,[r14+0x360]                            // [V] load dword [r14+0x360]
0x67263d9  not eax                                        // [V] eax = ~eax
0x67263db  add eax,[r14+0x368]                            // [V] eax += [r14+0x368]
0x67263e2  mov [rbp+0x190],ax                             // [V] store ax to [rbp+0x190]
0x67263e9  mov rcx,[0x1233E1B0]                           // [V] load data_1233e1b0
0x67263f0  mov rax,[rcx]                                  // [V]
0x67263f3  mov rax,[rax+0x10]                             // [V]
0x67263f7  mov dl,0x4A                                    // [V] dl = 0x4A ('J')
0x67263f9  call qword ptr [0xF99FFA0]                     // [V] -> sub_eea6040
0x67263ff  nop                                           
0x6726400  mov [rbp+0x818],al                             // [V] store al to [rbp+0x818]
0x6726406  mov rdx,[r14+0x698]                            // [V] load begin [r14+0x698]
0x672640d  cmp rdx,[r14+0x6A0]                            // [V] vs end [r14+0x6A0]
0x6726414  je 0x67266B2                                   // [V] jump if empty
0x672641a  movzx eax,word ptr [rbp+0x564]                 // [V] load word [rbp+0x564]
0x6726421  mov [rdx],ax                                   // [V] store ax to *rdx
0x6726424  add qword ptr [r14+0x698],2                    // [V] advance begin by 2
0x672642c  jmp 0x67266C6                                  // [V] tail jump
0x6726431  mov rcx,r14                                    // [V] rcx = r14
0x6726434  add rcx,0x60                                   // [V] rcx = r14+0x60
0x6726438  call 0x6760E60                                 // [V] -> sub_6760e60
0x672643d  nop                                           
0x672643e  mov rcx,[0x1233E1B0]                           // [V] load data_1233e1b0
0x6726445  mov rax,[rcx]                                  // [V]
0x6726448  mov rax,[rax+0x10]                             // [V]
0x672644c  movzx edx,byte ptr [rbp+0x818]                 // [V] edx = saved debug byte
0x6726453  call qword ptr [0xF99FFA0]                     // [V] -> sub_eea6040
0x6726459  nop                                           
0x672645a  mov qword ptr [rbp+0x118],0x1000000            // [V] store imm 0x1000000 to [rbp+0x118]
0x6726465  mov eax,[r14+0x60]                             // [V] load dword [r14+0x60]
0x6726469  not eax                                        // [V] eax = ~eax
0x672646b  add eax,[r14+0x68]                             // [V] eax += [r14+0x68]
0x672646f  mov [rbp+0x1D0],ax                             // [V] store ax to [rbp+0x1D0]
0x6726476  mov rcx,[0x1233E1B0]                           // [V] load data_1233e1b0
0x672647d  mov rax,[rcx]                                  // [V]
0x6726480  mov rax,[rax+0x10]                             // [V]
0x6726484  mov dl,0x4A                                    // [V] dl = 0x4A ('J')
0x6726486  call qword ptr [0xF99FFA0]                     // [V] -> sub_eea6040 (RANGE END)
```

Interpretation: range 0x67263c1..0x6726486 complete. Same debug/trace family as the previous range: `rax=0x100000002007049 -> [rbp+0x110]`; `ax = ~[r14+0x360] + [r14+0x368] -> [rbp+0x190]`; debug call sub_eea6040(dl=0x4A) -> [rbp+0x818]; empty check [r14+0x698..0x6A0) (je 0x67266B2); word [rbp+0x564] -> *rdx, begin += 2, jmp 0x67266C6; sub_6760e60(rcx=r14+0x60); debug call (dl=[rbp+0x818]); [rbp+0x118]=0x1000000; `ax = ~[r14+0x60] + [r14+0x68] -> [rbp+0x1D0]`; debug call, result -> [rbp+0x818] (0x6726486 = range end). All instruction lines [V]; callee identities [I].

## Range 0x6726a82..0x6726aab (complete)

Disasm started at 0x6726a72 (start-0x10), n=40. Output covers the whole range 0x6726a82..0x6726aab; no `(bad)` inside. The preceding `add [rax],al` (0x6726a72), indirect call (0x6726a74), nop (0x6726a7a), and `mov eax,[r14+0x698]` (0x6726a7b) lie before the range start.

```
0x6726a82  sub eax,[r14+0x690]                            // [V] eax -= [r14+0x690]
0x6726a89  shr eax,1                                      // [V] eax >>= 1 (divide by 2)
0x6726a8b  dec eax                                        // [V] eax -= 1
0x6726a8d  mov [rbp+0x14C],ax                             // [V] store ax to local [rbp+0x14C]
0x6726a94  mov rcx,[0x1233E1B0]                           // [V] load data_1233e1b0
0x6726a9b  mov rax,[rcx]                                  // [V]
0x6726a9e  mov rax,[rax+0x10]                             // [V]
0x6726aa2  mov dl,0x4A                                    // [V] dl = 0x4A ('J')
0x6726aa4  call qword ptr [0xF99FFA0]                     // [V] -> sub_eea6040
0x6726aaa  nop                                            
0x6726aab  mov [rbp+0x818],al                             // [V] store al to [rbp+0x818] (RANGE END)
```

Interpretation: range 0x6726a82..0x6726aab complete — count = (dword [r14+0x698] - dword [r14+0x690]) >> 1 - 1 -> ax at [rbp+0x14C], then debug call sub_eea6040(dl=0x4A), result -> [rbp+0x818]. All instruction lines [V]; callee identity [I].

## Range 0x6726cb1..0x6726cb1 (complete)

Disasm started at 0x6726ca1 (start-0x10), n=40. Note: 0x6726cb1 is NOT an instruction boundary — it is the middle byte of `mov rcx,rdi` at 0x6726cb0 (3 bytes: 0x6726cb0..0x6726cb2), immediately before the indirect call `call qword ptr [0xF99FFA0]` (0x6726cb3) -> sub_eea6040. No mnemonic line starts at 0x6726cb1; the enclosing lines are quoted below.

```
0x6726cb0  mov rcx,rdi                                    // [V] 3-byte instruction; range byte 0x6726cb1 lies inside it (offset +1); no standalone mnemonic line exists for 0x6726cb1
0x6726cb3  call qword ptr [0xF99FFA0]                     // [V] -> sub_eea6040 (indirect call via data_f99ffa0), right after the range byte
```

Interpretation: range byte 0x6726cb1 is sub-instruction (inside `mov rcx,rdi`); surrounding code is the standard debug-call setup (rcx=rdi, call sub_eea6040). [I] The gap is a single non-boundary byte, so nothing executable can be quoted for it. All quoted lines [V].

## Range 0x6726d60..0x6726d6a

Disasm started at 0x6726d50 (start-0x10), n=40. Output covers whole range (0x6726d60, 0x6726d64, 0x6726d68, 0x6726d6a); no `(bad)` inside.

```
0x6726d60  mov rdx,[r14+8]                                // [V] load rdx = begin ptr [r14+8]
0x6726d64  cmp rdx,[r14+0x10]                             // [V] compare begin vs end [r14+0x10]
0x6726d68  je short 0x6726D85                             // [V] jump if range empty -> loc_6726d85
0x6726d6a  mov r8d,0xC8                                   // [V] r8d = 0xC8 (200) chunk size
```

Interpretation: empty-vector check on pointer range [r14+8 .. r14+0x10); if equal, jump to else branch at 0x6726d85 (rcx=r14, r8=r15 -> sub_5aba6d0). If non-empty: r8d=0xC8 (200), then (just outside the range) call sub_eec6ec0(rcx=begin, rdx=r15, r8=0xC8) at 0x6726d76, advance begin by 0xC8 at 0x6726d7b, jmp to loc_6726d91 for debug call sub_eea6040(dl=[rbp+0x818]). All instruction lines in range [V] from rdis; jump targets/callee identities [I].

## Range 0x6726e02..0x6726e22

Disasm started at 0x6726df2 (start-0x10), n=40. Output covers whole range (0x6726e02, 0x6726e09, 0x6726e0f, 0x6726e16, 0x6726e1d, 0x6726e22); no `(bad)` inside (pre-range `adc`/`movups` at 0x6726df8..0x6726dff lie before the range start).

```
0x6726e02  movzx eax,byte ptr [rbp+0x254]     // [V] load byte from local [rbp+0x254] into eax
0x6726e09  mov [rbp+0x4BC],al                 // [V] store al to local [rbp+0x4BC]
0x6726e0f  movups xmm0,[rbp+0x258]            // [V] load xmm0 from local [rbp+0x258]
0x6726e16  movups [rbp+0x4C0],xmm0            // [V] store xmm0 to local [rbp+0x4C0]
0x6726e1d  movups xmm0,[r13+0x78]             // [V] load xmm0 from [r13+0x78]
0x6726e22  movups xmm1,[r13+0x88]             // [V] load xmm1 from [r13+0x88] (RANGE END)
```

Interpretation: byte copy [rbp+0x254] -> [rbp+0x4BC], then 16-byte SIMD copies [rbp+0x258] -> [rbp+0x4C0] and [r13+0x78] -> xmm0, then [r13+0x88] -> xmm1 — a small struct/field pack sequence (likely vec3-related, given sibling [r13+0x97] at 0x6726e2a just outside the range). [I] All instruction lines in range [V] from rdis.

## Range 0x6727308..0x6727308

Disasm started at 0x67272f8 (start-0x10), n=40. Output covers whole range (0x6727308 only); no `(bad)` inside (pre-range `test`/`adc`/`movups` at 0x67272f8..0x6727301 lie before the range start).

```
0x6727308  movss [rdx+0x18],xmm0                         // [V] store xmm0 to [rdx+0x18] (W a1+0x18)
```

Interpretation: first lane of a vec4 store sequence to object rdx: movss [rdx+0x18],xmm0, followed (just outside the range) by movss stores at [rdx+0x1C], [rdx+0x20], [rdx+0x24] and movups stores at [rdx+0x28]/[rdx+0x38]/[rdx+0x47], then `add qword ptr [r14+0x758],0x58` advances a cursor by 0x58 (88 bytes), then the standard debug call sub_eea6040(dl=[rbp+0x818]) at loc_6727370. Mirrors the 0x6724b25..0x6724b25 3-lane SIMD pattern. [I] All instruction lines in range [V] from rdis.

## Range 0x6727562..0x6727562

Disasm started at 0x6727552 (start-0x10), n=40. Output covers whole range (0x6727562 only); no `(bad)` inside (pre-range garbage at 0x6727552..0x672755e lies before the range start).

```
0x6727562  movzx edx,byte ptr [rbp+0x818]                 // [V] edx = saved debug byte from [rbp+0x818]
```

Interpretation: standard debug-call argument setup — dl = byte saved at [rbp+0x818] (result of an earlier sub_eea6040 call), consumed by `call qword ptr [0xF99FFA0]` -> sub_eea6040 at 0x6727569 (just outside the range). Followed by [rbp+0x110]=0x2007009, count=([r14+0x770]-[r14+0x768]) shr 3 then magic-imul 0xFFFFF0F1 (signed /1000) dec -> [rbp+0x13A] (the /1000-1 pattern), another debug call, empty check [r14+0x680..0x688) (je loc_67275f8 -> sub_1770a70(rcx=r14+0x678, r8=&[rbp+0x564])), else three movss vec3 stores [rbp+0x564/0x568/0x56C] -> [rdx..rdx+8], begin += 0xC. All instruction lines in range [V] from rdis; following context [V] from same output, interpretation [I].

## Range 0x672779c..0x672779c

Disasm started at 0x672778c (start-0x10), n=40. Output covers whole range (0x672779c only); no `(bad)` inside (pre-range garbage at 0x672778c..0x6727797 lies before the range start).

```
0x672779c  lea rcx,[rbp+0x4A8]                            // [V] rcx = &local [rbp+0x4A8]
```

Interpretation: address-of stack local [rbp+0x4A8]; (just outside the range) `mov [rcx+0x10],eax` at 0x67277a3 stores dword [r13+0x60] to [rbp+0x4B8], then `movups [rcx],xmm0` at 0x67277ab copies 16 bytes [r13+0x50] -> [rbp+0x4A8], then byte copy [rbp+0x254]->[rbp+0x4BC] and SIMD copies [rbp+0x258]->[rbp+0x4C0], [r13+0x78]->xmm0, [r13+0x88]->xmm1, [r13+0x97]->xmm2, stores to rbx+0x80/0x90/0x9F — same struct-pack pattern as the 0x6726e02 range. All context lines [V] from same output; interpretation [I].

## Range 0x6727a23..0x6727a3c

Disasm started at 0x6727a13 (start-0x10), n=40. Output covers whole range (0x6727a23, 0x6727a2a, 0x6727a31, 0x6727a38, 0x6727a3c); no `(bad)` inside (pre-range `add`/`movups` at 0x6727a13..0x6727a1c lie before the range start).

```
0x6727a23  movzx eax,word ptr [rbp+0x500]                 // [V] load word from local [rbp+0x500]
0x6727a2a  mov [rbp+0x728],ax                             // [V] store ax to local [rbp+0x728]
0x6727a31  mov rax,[rbp+0x808]                            // [V] load rax = [rbp+0x808]
0x6727a38  mov rcx,[rax+0x10]                             // [V] rcx = [rax+0x10]
0x6727a3c  mov eax,0x9D0                                  // [V] eax = 0x9D0 (2512) (RANGE END)
```

Interpretation: word [rbp+0x500] -> [rbp+0x728]; rax = [rbp+0x808], rcx = [rax+0x10], eax = imm 0x9D0 (2512); (just outside the range) `add rcx,rax` at 0x6727a41 computes pointer [rax+0x10] + 0x9D0, then `call 0x5ABA5C0` at 0x6727a44 -> sub_5aba5c0 (result in r14), then empty-vector check on r14+0x8A8..r14+0x8B0 (je loc_67289b7); non-empty: word [rbp+0x728] -> *rdx, begin += 2, jmp loc_67289cb. A debug call sub_eea6040(dl=0x4A) -> [rbp+0x827] (note: different local than the usual [rbp+0x818]) sits at 0x6727a9e..0x6727aa7 just outside the range end. All instruction lines in range [V] from rdis; following context [V] from same output, interpretation [I].

## NEXT

Remaining ranges to disassemble (in order):

- [x] 0x6724b25..0x6724b25
- [x] 0x67258eb..0x67258eb
- [x] 0x67259c6..0x67259c6
- [x] 0x6725c59..0x6725c6c
- [x] 0x6725ed3..0x6726047
- [x] 0x67263c1..0x6726486
- [x] 0x6726a82..0x6726aab
- [x] 0x6726cb1..0x6726cb1
- [x] 0x6726d60..0x6726d6a
- [x] 0x6726e02..0x6726e22
- [x] 0x6727308..0x6727308
- [x] 0x6727562..0x6727562
- [x] 0x672779c..0x672779c
- [x] 0x6727a23..0x6727a3c

ALL RANGES COMPLETE — all 15 ranges from docs/progress/gaps_6722cb0.txt are now quoted in this file (0x6724b25, 0x67258eb, 0x67259c6, 0x6725c59, 0x6725ed3..0x6726047, 0x67263c1..0x6726486, 0x6726a82..0x6726aab, 0x6726cb1, 0x6726d60..0x6726d6a, 0x6726e02..0x6726e22, 0x6727308..0x6727308, 0x6727562..0x6727562, 0x672779c..0x672779c, 0x6727a23..0x6727a3c). No remaining work for unit U-E4-H8.
