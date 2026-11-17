## NEXT
DONE

# UNIT U-Flm — flame ctor 0x668B160 and flame record builder 0x67411B0

Input data (read fully; all quoted `0xRVA  instr` lines below are copied verbatim from these files):
- docs/data/listings/effect_flame_ctor_668b160_668b400.txt
- docs/data/listings/effect_flame_record_67411b0_67416b0.txt

Tags: [V] = seen in the quoted listing line, [I] = inferred from instruction shape, [?] = unknown. Every instruction of both listings is inside a phase (no skipped ranges). Sizes come from the mnemonic (movups/movaps 16, movss 4, qword 8, dword 4, word 2, byte 1).

## Function 1 — ctor 0x668B160..0x668B3FA (listing ends 0x668b3ff, int3 pad)

Signature guess [I]: `void* __fastcall ctor(void* rcx=new, void* rdx, void* r8=src, float* r9=flt16, <byte,ptr,ptr,word,ptr,byte in caller home slots home+0x40..home+0x70>)`. `mov rax,rcx` @0x668b163 [V] then every store targets [rax]/[rcx]; nothing else is formed before `ret` @0x668b3fa [V]. rdx is stored as the object's first qword [V @0x668b166]; vftable or plain field [UNVERIFIED: 0x668b166 is [rcx]=rdx a vftable or a plain first field?].

### Phases (<=40 instructions each)

**0x668B160..0x668B21F** — Prologue saves rsi/rdi/rbx; `this` kept in rax; rdx stored at [rcx]; 16 floats copied one movss at a time from [r9] to new+0x8..new+0x44; xmm0 zeroed and 16 zero bytes stored at new+0x48; src+0x8 (control-block pointer of a shared-ptr pair) loaded for the next phase. [V all lines]

```asm
0x668b160  push rsi
0x668b161  push rdi
0x668b162  push rbx
0x668b163  mov rax,rcx
0x668b166  mov [rcx],rdx
0x668b169  movss xmm0,[r9]
0x668b16e  movss [rcx+8],xmm0
0x668b173  movss xmm0,[r9+4]
0x668b179  movss [rcx+0xC],xmm0
0x668b17e  movss xmm0,[r9+8]
0x668b184  movss [rcx+0x10],xmm0
0x668b189  movss xmm0,[r9+0xC]
0x668b18f  movss [rcx+0x14],xmm0
0x668b194  movss xmm0,[r9+0x10]
0x668b19a  movss [rcx+0x18],xmm0
0x668b19f  movss xmm0,[r9+0x14]
0x668b1a5  movss [rcx+0x1C],xmm0
0x668b1aa  movss xmm0,[r9+0x18]
0x668b1b0  movss [rcx+0x20],xmm0
0x668b1b5  movss xmm0,[r9+0x1C]
0x668b1bb  movss [rcx+0x24],xmm0
0x668b1c0  movss xmm0,[r9+0x20]
0x668b1c6  movss [rcx+0x28],xmm0
0x668b1cb  movss xmm0,[r9+0x24]
0x668b1d1  movss [rcx+0x2C],xmm0
0x668b1d6  movss xmm0,[r9+0x28]
0x668b1dc  movss [rcx+0x30],xmm0
0x668b1e1  movss xmm0,[r9+0x2C]
0x668b1e7  movss [rcx+0x34],xmm0
0x668b1ec  movss xmm0,[r9+0x30]
0x668b1f2  movss [rcx+0x38],xmm0
0x668b1f7  movss xmm0,[r9+0x34]
0x668b1fd  movss [rcx+0x3C],xmm0
0x668b202  movss xmm0,[r9+0x38]
0x668b208  movss [rcx+0x40],xmm0
0x668b20d  movss xmm0,[r9+0x3C]
0x668b213  movss [rcx+0x44],xmm0
0x668b218  xorps xmm0,xmm0
0x668b21b  movups [rcx+0x48],xmm0
0x668b21f  mov rcx,[r8+8]
```

**0x668B223..0x668B2BD** — Copies four shared-ptr-like pairs from src into the new object, each pair: load control block, `test`/`je`, `lock inc dword ptr [rcx+8]` (refcount bump [I]), then store ptr+control qwords; interleaved 16-byte zero inits and two byte copies; ends by spilling incoming home slots into r9/rsi/edx/r10/ebx. [V all lines]

```asm
0x668b223  test rcx,rcx
0x668b226  je short 0x668B22C
0x668b228  lock inc dword ptr [rcx+8]
0x668b22c  mov rcx,[r8]
0x668b22f  mov [rax+0x48],rcx
0x668b233  mov rcx,[r8+8]
0x668b237  mov [rax+0x50],rcx
0x668b23b  movups [rax+0x58],xmm0
0x668b23f  mov rcx,[r8+0x18]
0x668b243  test rcx,rcx
0x668b246  je short 0x668B24C
0x668b248  lock inc dword ptr [rcx+8]
0x668b24c  mov rcx,[r8+0x10]
0x668b250  mov [rax+0x58],rcx
0x668b254  mov rcx,[r8+0x18]
0x668b258  mov [rax+0x60],rcx
0x668b25c  movzx ecx,byte ptr [r8+0x20]
0x668b261  mov [rax+0x68],cl
0x668b264  movups [rax+0x70],xmm0
0x668b268  mov rcx,[r8+0x30]
0x668b26c  test rcx,rcx
0x668b26f  je short 0x668B275
0x668b271  lock inc dword ptr [rcx+8]
0x668b275  mov rcx,[r8+0x28]
0x668b279  mov [rax+0x70],rcx
0x668b27d  mov rcx,[r8+0x30]
0x668b281  mov [rax+0x78],rcx
0x668b285  movzx ecx,byte ptr [r8+0x38]
0x668b28a  mov [rax+0x80],cl
0x668b290  movups [rax+0x88],xmm0
0x668b297  mov rcx,[r8+0x48]
0x668b29b  test rcx,rcx
0x668b29e  je short 0x668B2A4
0x668b2a0  lock inc dword ptr [rcx+8]
0x668b2a4  movzx ecx,byte ptr [rsp+0x70]
0x668b2a9  mov r9,[rsp+0x68]
0x668b2ae  mov rsi,[rsp+0x60]
0x668b2b3  movzx edx,word ptr [rsp+0x58]
0x668b2b8  mov r10,[rsp+0x50]
0x668b2bd  movzx ebx,byte ptr [rsp+0x48]
```

**0x668B2C2..0x668B397** — Restores r11/r10/bl/cl args from home slots; continues the shared-pair copies (src+0x50/src+0x58 -> new+0x98/new+0xA0 with `lock inc` on the control block); copies 16 bytes from [rsi] to new+0xA8, a dword from rsi+0x10 to new+0xB8, a byte to new+0xBC, two floats from [r11] to new+0xC0/new+0xC4; then walks table r10: entries +0x70..+0x88 each yield a sub-object at +0x40 whose floats are stored to new+0xC8..new+0xE4. [V all lines]

```asm
0x668b2c2  mov r11,[rsp+0x40]
0x668b2c7  mov rdi,[r8+0x40]
0x668b2cb  mov [rax+0x88],rdi
0x668b2d2  mov rdi,[r8+0x48]
0x668b2d6  mov [rax+0x90],rdi
0x668b2dd  movups [rax+0x98],xmm0
0x668b2e4  mov rdi,[r8+0x58]
0x668b2e8  test rdi,rdi
0x668b2eb  je short 0x668B2F1
0x668b2ed  lock inc dword ptr [rdi+8]
0x668b2f1  mov rdi,[r8+0x50]
0x668b2f5  mov [rax+0x98],rdi
0x668b2fc  mov r8,[r8+0x58]
0x668b300  mov [rax+0xA0],r8
0x668b307  movups xmm0,[rsi]
0x668b30a  movups [rax+0xA8],xmm0
0x668b311  mov r8d,[rsi+0x10]
0x668b315  mov [rax+0xB8],r8d
0x668b31c  mov [rax+0xBC],bl
0x668b322  movss xmm0,[r11]
0x668b327  movss [rax+0xC0],xmm0
0x668b32f  movss xmm0,[r11+4]
0x668b335  movss [rax+0xC4],xmm0
0x668b33d  mov r8,[r10+0x70]
0x668b341  mov r8,[r8+0x40]
0x668b345  movss xmm0,[r8]
0x668b34a  movss [rax+0xC8],xmm0
0x668b352  movss xmm0,[r8+4]
0x668b358  movss [rax+0xCC],xmm0
0x668b360  movss xmm0,[r8+8]
0x668b366  movss [rax+0xD0],xmm0
0x668b36e  movss xmm0,[r8+0xC]
0x668b374  movss [rax+0xD4],xmm0
0x668b37c  mov r8,[r10+0x78]
0x668b380  mov r8,[r8+0x40]
0x668b384  movss xmm0,[r8]
0x668b389  movss [rax+0xD8],xmm0
0x668b391  movss xmm0,[r8+4]
0x668b397  movss [rax+0xDC],xmm0
```

**0x668B39F..0x668B3FF** — Same table walk for entries +0x80/+0x88 (one float each into new+0xE0/new+0xE4); two floats from restored r9 into new+0xE8/new+0xEC; byte cl into new+0xF0 and word dx into new+0xF2; epilogue pops and `ret`; five int3 pads close the function. [V all lines]

```asm
0x668b39f  mov r8,[r10+0x80]
0x668b3a6  mov r8,[r8+0x40]
0x668b3aa  movss xmm0,[r8]
0x668b3af  movss [rax+0xE0],xmm0
0x668b3b7  mov r8,[r10+0x88]
0x668b3be  mov r8,[r8+0x40]
0x668b3c2  movss xmm0,[r8]
0x668b3c7  movss [rax+0xE4],xmm0
0x668b3cf  movss xmm0,[r9]
0x668b3d4  movss [rax+0xE8],xmm0
0x668b3dc  movss xmm0,[r9+4]
0x668b3e2  movss [rax+0xEC],xmm0
0x668b3ea  mov [rax+0xF0],cl
0x668b3f0  mov [rax+0xF2],dx
0x668b3f7  pop rbx
0x668b3f8  pop rdi
0x668b3f9  pop rsi
0x668b3fa  ret
0x668b3fb  int3
0x668b3fc  int3
0x668b3fd  int3
0x668b3fe  int3
0x668b3ff  int3
```

### Field table — every [reg+off] site of the ctor, one row per (object, offset), all sites listed

Shared-ptr pair pattern = `mov rcx,[src+X]`/`test`/`je`/`lock inc dword ptr [rcx+8]` then two qword stores into the new object [I from the repeated shape]. Rows with mixed sizes list the movups/movaps site first.

| offset | size | dir | verbatim site line(s) | meaning |
|---|---|---|---|---|
| new+0x0 | 8 | W | 0x668b166  mov [rcx],rdx | [I] first qword of the object, written first (vftable or lead field) |
| new+0x8 | 4 | W | 0x668b16e  movss [rcx+8],xmm0 | - |
| new+0xC | 4 | W | 0x668b179  movss [rcx+0xC],xmm0 | - |
| new+0x10 | 4 | W | 0x668b184  movss [rcx+0x10],xmm0 | - |
| new+0x14 | 4 | W | 0x668b18f  movss [rcx+0x14],xmm0 | - |
| new+0x18 | 4 | W | 0x668b19a  movss [rcx+0x18],xmm0 | - |
| new+0x1C | 4 | W | 0x668b1a5  movss [rcx+0x1C],xmm0 | - |
| new+0x20 | 4 | W | 0x668b1b0  movss [rcx+0x20],xmm0 | - |
| new+0x24 | 4 | W | 0x668b1bb  movss [rcx+0x24],xmm0 | - |
| new+0x28 | 4 | W | 0x668b1c6  movss [rcx+0x28],xmm0 | - |
| new+0x2C | 4 | W | 0x668b1d1  movss [rcx+0x2C],xmm0 | - |
| new+0x30 | 4 | W | 0x668b1dc  movss [rcx+0x30],xmm0 | - |
| new+0x34 | 4 | W | 0x668b1e7  movss [rcx+0x34],xmm0 | - |
| new+0x38 | 4 | W | 0x668b1f2  movss [rcx+0x38],xmm0 | - |
| new+0x3C | 4 | W | 0x668b1fd  movss [rcx+0x3C],xmm0 | - |
| new+0x40 | 4 | W | 0x668b208  movss [rcx+0x40],xmm0 | - |
| new+0x44 | 4 | W | 0x668b213  movss [rcx+0x44],xmm0 | - |
| new+0x48 | 16 (movups), 8 (qword) | W | 0x668b21b  movups [rcx+0x48],xmm0<br>0x668b22f  mov [rax+0x48],rcx | [I] 16-byte zero init then shared-ptr pair member 1 |
| new+0x50 | 8 | W | 0x668b237  mov [rax+0x50],rcx | [I] shared-ptr pair member 2 (control block) |
| new+0x58 | 16 (movups), 8 (qword) | W | 0x668b23b  movups [rax+0x58],xmm0<br>0x668b250  mov [rax+0x58],rcx | [I] zero init then shared-ptr pair member 1 |
| new+0x60 | 8 | W | 0x668b258  mov [rax+0x60],rcx | [I] shared-ptr pair member 2 |
| new+0x68 | 1 | W | 0x668b261  mov [rax+0x68],cl | byte copied from src+0x20 |
| new+0x70 | 16 (movups), 8 (qword) | W | 0x668b264  movups [rax+0x70],xmm0<br>0x668b279  mov [rax+0x70],rcx | [I] zero init then shared-ptr pair member 1 |
| new+0x78 | 8 | W | 0x668b281  mov [rax+0x78],rcx | [I] shared-ptr pair member 2 |
| new+0x80 | 1 | W | 0x668b28a  mov [rax+0x80],cl | byte copied from src+0x38 |
| new+0x88 | 16 (movups), 8 (qword) | W | 0x668b290  movups [rax+0x88],xmm0<br>0x668b2cb  mov [rax+0x88],rdi | [I] zero init then shared-ptr pair member 1 |
| new+0x90 | 8 | W | 0x668b2d6  mov [rax+0x90],rdi | qword copied from src+0x48 |
| new+0x98 | 16 (movups), 8 (qword) | W | 0x668b2dd  movups [rax+0x98],xmm0<br>0x668b2f5  mov [rax+0x98],rdi | [I] zero init then shared-ptr pair member 1 |
| new+0xA0 | 8 | W | 0x668b300  mov [rax+0xA0],r8 | [I] shared-ptr pair member 2 |
| new+0xA8 | 16 | W | 0x668b30a  movups [rax+0xA8],xmm0 | 16 bytes copied from pos+0x0 |
| new+0xB8 | 4 | W | 0x668b315  mov [rax+0xB8],r8d | dword copied from pos+0x10 |
| new+0xBC | 1 | W | 0x668b31c  mov [rax+0xBC],bl | byte from home+0x48 (bl) |
| new+0xC0 | 4 | W | 0x668b327  movss [rax+0xC0],xmm0 | float from rgb+0x0 |
| new+0xC4 | 4 | W | 0x668b335  movss [rax+0xC4],xmm0 | float from rgb+0x4 |
| new+0xC8 | 4 | W | 0x668b34a  movss [rax+0xC8],xmm0 | float from vec+0x0 of tbl+0x70 entry |
| new+0xCC | 4 | W | 0x668b358  movss [rax+0xCC],xmm0 | float from vec+0x4 |
| new+0xD0 | 4 | W | 0x668b366  movss [rax+0xD0],xmm0 | float from vec+0x8 |
| new+0xD4 | 4 | W | 0x668b374  movss [rax+0xD4],xmm0 | float from vec+0xC |
| new+0xD8 | 4 | W | 0x668b389  movss [rax+0xD8],xmm0 | float from vec+0x0 of tbl+0x78 entry |
| new+0xDC | 4 | W | 0x668b397  movss [rax+0xDC],xmm0 | float from vec+0x4 |
| new+0xE0 | 4 | W | 0x668b3af  movss [rax+0xE0],xmm0 | float from vec+0x0 of tbl+0x80 entry |
| new+0xE4 | 4 | W | 0x668b3c7  movss [rax+0xE4],xmm0 | float from vec+0x0 of tbl+0x88 entry |
| new+0xE8 | 4 | W | 0x668b3d4  movss [rax+0xE8],xmm0 | float from flt+0x0 (second pass) |
| new+0xEC | 4 | W | 0x668b3e2  movss [rax+0xEC],xmm0 | float from flt+0x4 (second pass) |
| new+0xF0 | 1 | W | 0x668b3ea  mov [rax+0xF0],cl | byte from home+0x70 |
| new+0xF2 | 2 | W | 0x668b3f0  mov [rax+0xF2],dx | word from home+0x58 |

| offset | size | dir | verbatim site line(s) | meaning |
|---|---|---|---|---|
| src+0x0 | 8 | R | 0x668b22c  mov rcx,[r8] | [I] object ptr of shared-ptr pair |
| src+0x8 | 8 | R | 0x668b21f  mov rcx,[r8+8]<br>0x668b233  mov rcx,[r8+8] | [I] control-block ptr of pair (AddRef'd) |
| src+0x10 | 8 | R | 0x668b24c  mov rcx,[r8+0x10] | [I] object ptr of pair |
| src+0x18 | 8 | R | 0x668b23f  mov rcx,[r8+0x18]<br>0x668b254  mov rcx,[r8+0x18] | [I] control-block ptr of pair |
| src+0x20 | 1 | R | 0x668b25c  movzx ecx,byte ptr [r8+0x20] | - |
| src+0x28 | 8 | R | 0x668b275  mov rcx,[r8+0x28] | [I] object ptr of pair |
| src+0x30 | 8 | R | 0x668b268  mov rcx,[r8+0x30]<br>0x668b27d  mov rcx,[r8+0x30] | [I] control-block ptr of pair |
| src+0x38 | 1 | R | 0x668b285  movzx ecx,byte ptr [r8+0x38] | - |
| src+0x40 | 8 | R | 0x668b2c7  mov rdi,[r8+0x40] | - |
| src+0x48 | 8 | R | 0x668b2d2  mov rdi,[r8+0x48] | - |
| src+0x50 | 8 | R | 0x668b2f1  mov rdi,[r8+0x50] | [I] object ptr of pair |
| src+0x58 | 8 | R | 0x668b2e4  mov rdi,[r8+0x58]<br>0x668b2fc  mov r8,[r8+0x58] | [I] control-block ptr of pair |

| offset | size | dir | verbatim site line(s) | meaning |
|---|---|---|---|---|
| ctrl+0x8 | 4 | RW | 0x668b228  lock inc dword ptr [rcx+8]<br>0x668b248  lock inc dword ptr [rcx+8]<br>0x668b271  lock inc dword ptr [rcx+8]<br>0x668b2a0  lock inc dword ptr [rcx+8]<br>0x668b2ed  lock inc dword ptr [rdi+8] | [I] atomic refcount increment on shared-ptr control block (test/je/lock inc idiom) |

| offset | size | dir | verbatim site line(s) | meaning |
|---|---|---|---|---|
| flt+0x0 | 4 | R | 0x668b169  movss xmm0,[r9]<br>0x668b3cf  movss xmm0,[r9] | float[16] source; element 0 read twice |
| flt+0x4 | 4 | R | 0x668b173  movss xmm0,[r9+4]<br>0x668b3dc  movss xmm0,[r9+4] | element 1 read twice |
| flt+0x8 | 4 | R | 0x668b17e  movss xmm0,[r9+8] | - |
| flt+0xC | 4 | R | 0x668b189  movss xmm0,[r9+0xC] | - |
| flt+0x10 | 4 | R | 0x668b194  movss xmm0,[r9+0x10] | - |
| flt+0x14 | 4 | R | 0x668b19f  movss xmm0,[r9+0x14] | - |
| flt+0x18 | 4 | R | 0x668b1aa  movss xmm0,[r9+0x18] | - |
| flt+0x1C | 4 | R | 0x668b1b5  movss xmm0,[r9+0x1C] | - |
| flt+0x20 | 4 | R | 0x668b1c0  movss xmm0,[r9+0x20] | - |
| flt+0x24 | 4 | R | 0x668b1cb  movss xmm0,[r9+0x24] | - |
| flt+0x28 | 4 | R | 0x668b1d6  movss xmm0,[r9+0x28] | - |
| flt+0x2C | 4 | R | 0x668b1e1  movss xmm0,[r9+0x2C] | - |
| flt+0x30 | 4 | R | 0x668b1ec  movss xmm0,[r9+0x30] | - |
| flt+0x34 | 4 | R | 0x668b1f7  movss xmm0,[r9+0x34] | - |
| flt+0x38 | 4 | R | 0x668b202  movss xmm0,[r9+0x38] | - |
| flt+0x3C | 4 | R | 0x668b20d  movss xmm0,[r9+0x3C] | - |

| offset | size | dir | verbatim site line(s) | meaning |
|---|---|---|---|---|
| tbl+0x70 | 8 | R | 0x668b33d  mov r8,[r10+0x70] | [I] ptr to entry holding a float sub-object |
| tbl+0x78 | 8 | R | 0x668b37c  mov r8,[r10+0x78] | - |
| tbl+0x80 | 8 | R | 0x668b39f  mov r8,[r10+0x80] | - |
| tbl+0x88 | 8 | R | 0x668b3b7  mov r8,[r10+0x88] | - |
| inner+0x40 | 8 | R | 0x668b341  mov r8,[r8+0x40]<br>0x668b380  mov r8,[r8+0x40]<br>0x668b3a6  mov r8,[r8+0x40]<br>0x668b3be  mov r8,[r8+0x40] | [I] float base fetched from each tbl entry |
| vec+0x0 | 4 | R | 0x668b345  movss xmm0,[r8]<br>0x668b384  movss xmm0,[r8]<br>0x668b3aa  movss xmm0,[r8]<br>0x668b3c2  movss xmm0,[r8] | - |
| vec+0x4 | 4 | R | 0x668b352  movss xmm0,[r8+4]<br>0x668b391  movss xmm0,[r8+4] | - |
| vec+0x8 | 4 | R | 0x668b360  movss xmm0,[r8+8] | - |
| vec+0xC | 4 | R | 0x668b36e  movss xmm0,[r8+0xC] | - |
| rgb+0x0 | 4 | R | 0x668b322  movss xmm0,[r11] | - |
| rgb+0x4 | 4 | R | 0x668b32f  movss xmm0,[r11+4] | - |
| pos+0x0 | 16 | R | 0x668b307  movups xmm0,[rsi] | - |
| pos+0x10 | 4 | R | 0x668b311  mov r8d,[rsi+0x10] | - |

| offset | size | dir | verbatim site line(s) | meaning |
|---|---|---|---|---|
| home+0x40 | 8 | R | 0x668b2c2  mov r11,[rsp+0x40] | [I] caller register home slot (incoming arg) |
| home+0x48 | 1 | R | 0x668b2bd  movzx ebx,byte ptr [rsp+0x48] | [I] home slot of an incoming byte arg |
| home+0x50 | 8 | R | 0x668b2b8  mov r10,[rsp+0x50] | [I] home slot (tbl source) |
| home+0x58 | 2 | R | 0x668b2b3  movzx edx,word ptr [rsp+0x58] | [I] home slot of an incoming word arg |
| home+0x60 | 8 | R | 0x668b2ae  mov rsi,[rsp+0x60] | [I] home slot (pos source) |
| home+0x68 | 8 | R | 0x668b2a9  mov r9,[rsp+0x68] | [I] home slot (flt16 tail source) |
| home+0x70 | 1 | R | 0x668b2a4  movzx ecx,byte ptr [rsp+0x70] | [I] home slot of an incoming byte arg |

Ctor layout summary [I from the store pattern]: new+0x8..new+0x44 = 16 floats from flt; five shared-ptr-like members at +0x48, +0x58, +0x70, +0x88, +0x98 (each zero-init 16 bytes, then ptr qword, then control-block qword at +0x50, +0x60, +0x78, +0x90, +0xA0); bytes at +0x68, +0x80, +0xBC, +0xF0; qwords +0x90/+0xA0 region fed from src+0x40..src+0x58; 16-byte block +0xA8 plus dword +0xB8 from pos; floats +0xC0..+0xE4 from rgb and the tbl/inner/vec chain; word +0xF2 last.

## Function 2 — record builder 0x67411B0..0x67415D5 + tails, and two small helpers 0x6741620/0x6741660 (listing 0x67411b0..0x67416af)

Signature guess [I]: `void __fastcall build_record(Provider* rcx=self, Record* rdx=out)`. rdx is kept in r14 and every write of the produced record goes through it [V]; rcx only feeds field loads [V]; no return value is formed before `ret` @0x67415d5 [V]. Stack frame: rbp=[rsp+0x80] @0x67411c3 [V].

### Phases (<=40 instructions each)

**0x67411B0..0x6741204** — Prologue (8 pushes, 0x118 frame); EH/cookie qword -2 at fr+0x90 [I]; captures r14=out(rdx), rsi=self(rcx), r12=self+0x8, r15=self+0x28 (cfg source), rax=self+0x10 (rec); copies 64 bytes from rec+0x8..rec+0x47 to frame slots fr-0x40..fr-0x10 via four movups/movaps pairs. [V all lines]

```asm
0x67411b0  push rbp
0x67411b1  push r15
0x67411b3  push r14
0x67411b5  push r13
0x67411b7  push r12
0x67411b9  push rsi
0x67411ba  push rdi
0x67411bb  push rbx
0x67411bc  sub rsp,0x118
0x67411c3  lea rbp,[rsp+0x80]
0x67411cb  mov qword ptr [rbp+0x90],0xFFFFFFFFFFFFFFFE
0x67411d6  mov r14,rdx
0x67411d9  mov rsi,rcx
0x67411dc  mov r12,[rcx+8]
0x67411e0  mov r15,[rcx+0x28]
0x67411e4  mov rax,[rcx+0x10]
0x67411e8  movups xmm0,[rax+8]
0x67411ec  movaps [rbp-0x40],xmm0
0x67411f0  movups xmm0,[rax+0x18]
0x67411f4  movaps [rbp-0x30],xmm0
0x67411f8  movups xmm0,[rax+0x28]
0x67411fc  movaps [rbp-0x20],xmm0
0x6741200  movups xmm0,[rax+0x38]
0x6741204  movaps [rbp-0x10],xmm0
```

**0x6741208..0x6741261** — fr+0x0 byte zeroed; rbx=self+0x20 (component); word rec+0xF2 copied to fr+0x8E; r13d = dword at [self+0x18]; rax = [rec] (deref to obj); 16 zero bytes to fr+0x70; shared-ptr-like assign into fr+0x70/fr+0x78 from obj+0x1B0/obj+0x1B8 with conditional word read at objin+0x10 and AddRef `lock inc` on the control block. [V all lines]

```asm
0x6741208  mov byte ptr [rbp],0
0x674120c  mov rbx,[rcx+0x20]
0x6741210  movzx ecx,word ptr [rax+0xF2]
0x6741217  mov [rbp+0x8E],cx
0x674121e  mov rcx,[rsi+0x18]
0x6741222  mov r13d,[rcx]
0x6741225  mov rax,[rax]
0x6741228  xorps xmm0,xmm0
0x674122b  movaps [rbp+0x70],xmm0
0x674122f  mov rcx,[rax+0x1B0]
0x6741236  test rcx,rcx
0x6741239  je short 0x674123F
0x674123b  movzx ecx,word ptr [rcx+0x10]
0x674123f  mov rcx,[rax+0x1B8]
0x6741246  test rcx,rcx
0x6741249  je short 0x6741258
0x674124b  lock inc dword ptr [rcx+8]
0x674124f  mov rcx,[rax+0x1B8]
0x6741256  jmp short 0x674125A
0x6741258  xor ecx,ecx
0x674125a  mov rax,[rax+0x1B0]
0x6741261  mov [rbp+0x70],rax
```

**0x6741265..0x67412CD** — Completes the stack shared_ptr (control qword to fr+0x78) then releases the previous fr+0x78 value: double `lock dec` (+0x8 then +0xC) with `call qword ptr [0xF99FFA0]` destroy idiom [I]; sets up and calls 0x66A0F60 (rcx=fr+0x10, rdx=vtable-of-vtable of *self, r8=[r12+0x3B8], r9=fr+0x70, shadow dwords r13d/0/0) constructing/initializing an object at fr+0x10 [I]. [V all lines]

```asm
0x6741265  mov rdi,[rbp+0x78]
0x6741269  mov [rbp+0x78],rcx
0x674126d  test rdi,rdi
0x6741270  je short 0x674129D
0x6741272  lock dec dword ptr [rdi+8]
0x6741276  jne short 0x674129D
0x6741278  mov rax,[rdi]
0x674127b  mov rax,[rax]
0x674127e  mov rcx,rdi
0x6741281  call qword ptr [0xF99FFA0]
0x6741287  lock dec dword ptr [rdi+0xC]
0x674128b  jne short 0x674129D
0x674128d  mov rax,[rdi]
0x6741290  mov rax,[rax+8]
0x6741294  mov rcx,rdi
0x6741297  call qword ptr [0xF99FFA0]
0x674129d  mov r8,[r12+0x3B8]
0x67412a5  mov rax,[rsi]
0x67412a8  mov rdx,[rax]
0x67412ab  mov [rsp+0x20],r13d
0x67412b0  mov dword ptr [rsp+0x30],0
0x67412b8  mov dword ptr [rsp+0x28],0
0x67412c0  lea rcx,[rbp+0x10]
0x67412c4  lea r9,[rbp+0x70]
0x67412c8  call 0x66A0F60
0x67412cd  nop
```

**0x67412CE..0x6741335** — Copies the cfg struct (r15) into the out record r14: dword +0x10 first, 16 bytes at +0x0, byte +0x14, four floats +0x18..+0x24, then three 16-byte blocks +0x28/+0x38/+0x47; writes constant 0xFF to out+0x98. [V all lines]

```asm
0x67412ce  mov eax,[r15+0x10]
0x67412d2  mov [r14+0x10],eax
0x67412d6  movups xmm0,[r15]
0x67412da  movups [r14],xmm0
0x67412de  movzx eax,byte ptr [r15+0x14]
0x67412e3  mov [r14+0x14],al
0x67412e7  movss xmm0,[r15+0x18]
0x67412ed  movss [r14+0x18],xmm0
0x67412f3  movss xmm0,[r15+0x1C]
0x67412f9  movss [r14+0x1C],xmm0
0x67412ff  movss xmm0,[r15+0x20]
0x6741305  movss [r14+0x20],xmm0
0x674130b  movss xmm0,[r15+0x24]
0x6741311  movss [r14+0x24],xmm0
0x6741317  movups xmm0,[r15+0x28]
0x674131c  movups xmm1,[r15+0x38]
0x6741321  movups xmm2,[r15+0x47]
0x6741326  movups [r14+0x28],xmm0
0x674132b  movups [r14+0x38],xmm1
0x6741330  movups [r14+0x47],xmm2
0x6741335  mov byte ptr [r14+0x98],0xFF
```

**0x674133D..0x67413A5** — Variant switch on the fr+0x0 byte (set in phase R1..R2 region): 0 copies all four 16-byte frame blocks to out+0x58..out+0x88; 2 copies only the first qword to out+0x58; 1 moves (loads + zero-sources the frame qwords) out+0x58/out+0x68; other values skip; finally the tag byte is stored to out+0x98. [V all lines]

```asm
0x674133d  movzx eax,byte ptr [rbp]
0x6741341  movzx ecx,al
0x6741344  cmp ecx,1
0x6741347  jg short 0x6741376
0x6741349  test ecx,ecx
0x674134b  jne short 0x6741385
0x674134d  movaps xmm0,[rbp-0x40]
0x6741351  movups [r14+0x58],xmm0
0x6741356  movaps xmm0,[rbp-0x30]
0x674135a  movups [r14+0x68],xmm0
0x674135f  movaps xmm0,[rbp-0x20]
0x6741363  movups [r14+0x78],xmm0
0x6741368  movaps xmm0,[rbp-0x10]
0x674136c  movups [r14+0x88],xmm0
0x6741374  jmp short 0x67413A5
0x6741376  cmp ecx,2
0x6741379  jne short 0x67413AC
0x674137b  mov rcx,[rbp-0x40]
0x674137f  mov [r14+0x58],rcx
0x6741383  jmp short 0x67413A5
0x6741385  mov rcx,[rbp-0x30]
0x6741389  mov qword ptr [rbp-0x30],0
0x6741391  movaps xmm0,[rbp-0x40]
0x6741395  xorps xmm1,xmm1
0x6741398  movaps [rbp-0x40],xmm1
0x674139c  movups [r14+0x58],xmm0
0x67413a1  mov [r14+0x68],rcx
0x67413a5  mov [r14+0x98],al
```

**0x67413AC..0x67413F5** — comp(rbx): first qword to out+0xA0; `lea rcx,[r14+0xA8]`/`lea rdx,[rbx+8]` and `call 0xE869FF0` move-constructs the out+0xA8 member from the component [I]; r14 reloaded from fr+0x80 into r9; moves qword comp+0x80 -> out+0x120 and zeroes the source; word fr+0x8E -> out+0x128. [V all lines]

```asm
0x67413ac  mov rax,[rbx]
0x67413af  mov [r14+0xA0],rax
0x67413b6  lea rcx,[r14+0xA8]
0x67413bd  lea rdx,[rbx+8]
0x67413c1  mov [rbp+0x80],r14
0x67413c8  call 0xE869FF0
0x67413cd  nop
0x67413ce  mov rax,[rbx+0x80]
0x67413d5  mov r9,[rbp+0x80]
0x67413dc  mov [r9+0x120],rax
0x67413e3  mov qword ptr [rbx+0x80],0
0x67413ee  movzx eax,word ptr [rbp+0x8E]
0x67413f5  mov [r9+0x128],ax
```

**0x67413FD..0x6741445** — Moves the object built by 0x66A0F60 from fr+0x10 into the record: 16 bytes fr+0x10 -> out+0x130 with fr+0x18 zeroed, 16 bytes fr+0x20 -> out+0x140 zeroed, qword fr+0x30 -> out+0x150; 0xFF to out+0x168; loads the fr+0x48 byte, `cmp rax,3` / `ja 0x6741517` (default), and computes the switch target rcx=[r9+0x158]. [V all lines]

```asm
0x67413fd  movaps xmm0,[rbp+0x10]
0x6741401  mov qword ptr [rbp+0x18],0
0x6741409  movups [r9+0x130],xmm0
0x6741411  movaps xmm0,[rbp+0x20]
0x6741415  xorps xmm1,xmm1
0x6741418  movaps [rbp+0x20],xmm1
0x674141c  movups [r9+0x140],xmm0
0x6741424  mov rax,[rbp+0x30]
0x6741428  mov [r9+0x150],rax
0x674142f  mov byte ptr [r9+0x168],0xFF
0x6741437  movzx eax,byte ptr [rbp+0x48]
0x674143b  cmp rax,3
0x674143f  ja 0x6741517
0x6741445  lea rcx,[r9+0x158]
```

**0x674144C..0x674148E** — Jump-table dispatch (int32 table at 0xF2BFC40, 4 entries for the fr+0x48 byte): cases copy qword or 16 bytes from fr+0x38 to [rcx]=out+0x158, store the tag in al to out+0x168, then common tail copies 16 bytes fr+0x50 -> out+0x170 and qword fr+0x60 -> out+0x180 and jumps to the loop at 0x674152E. [V all lines]

```asm
0x674144c  lea rdx,[0xF2BFC40]
0x6741453  movsxd r8,[rdx+rax*4]
0x6741457  add r8,rdx
0x674145a  jmp r8
0x674145d  mov rdx,[rbp+0x38]
0x6741461  mov [rcx],rdx
0x6741464  jmp short 0x6741470
0x6741466  lea rdx,[rbp+0x38]
0x674146a  movups xmm0,[rdx]
0x674146d  movups [rcx],xmm0
0x6741470  mov [r9+0x168],al
0x6741477  movaps xmm0,[rbp+0x50]
0x674147b  movups [r9+0x170],xmm0
0x6741483  mov rax,[rbp+0x60]
0x6741487  mov [r9+0x180],rax
0x674148e  jmp 0x674152E
```

**0x6741493..0x6741526** — Case-3 path: zeroes [rcx]=out+0x158; if fr+0x40 is non-null AddRefs its control block (`lock inc [rax+8]`) and takes rsi as a temporary, else jumps to the 0x67415D6 tail; sets al = (fr+0x48 byte != 3); copies 16 bytes fr+0x38 -> out+0x158, tag 3 to out+0x168, fr+0x50 -> out+0x170, fr+0x60 -> out+0x180; releases the rsi temporary with the double lock-dec + `call qword ptr [0xF99FFA0]` idiom [I]; the default case (>3) at 0x6741517 only copies fr+0x60/fr+0x50. [V all lines]

```asm
0x6741493  xorps xmm0,xmm0
0x6741496  movups [rcx],xmm0
0x6741499  mov rax,[rbp+0x40]
0x674149d  test rax,rax
0x67414a0  je 0x67415D6
0x67414a6  lock inc dword ptr [rax+8]
0x67414aa  cmp byte ptr [rbp+0x48],3
0x67414ae  setne al
0x67414b1  mov rsi,[rbp+0x40]
0x67414b5  movups xmm0,[rbp+0x38]
0x67414b9  movups [r9+0x158],xmm0
0x67414c1  mov byte ptr [r9+0x168],3
0x67414c9  movaps xmm0,[rbp+0x50]
0x67414cd  movups [r9+0x170],xmm0
0x67414d5  mov rcx,[rbp+0x60]
0x67414d9  mov [r9+0x180],rcx
0x67414e0  test rsi,rsi
0x67414e3  sete cl
0x67414e6  or cl,al
0x67414e8  jne short 0x674152E
0x67414ea  lock dec dword ptr [rsi+8]
0x67414ee  jne short 0x674152E
0x67414f0  mov rax,[rsi]
0x67414f3  mov rax,[rax]
0x67414f6  mov rcx,rsi
0x67414f9  call qword ptr [0xF99FFA0]
0x67414ff  lock dec dword ptr [rsi+0xC]
0x6741503  jne short 0x674152E
0x6741505  mov rax,[rsi]
0x6741508  mov rax,[rax+8]
0x674150c  mov rcx,rsi
0x674150f  call qword ptr [0xF99FFA0]
0x6741515  jmp short 0x674152E
0x6741517  mov rax,[rbp+0x60]
0x674151b  mov [r9+0x180],rax
0x6741522  movaps xmm0,[rbp+0x50]
0x6741526  movups [r9+0x170],xmm0
```

**0x674152E..0x6741583** — Walks the vector [fr+0x18, fr+0x20) in 0x28-byte elements (`add rdi,0x28` shows the stride [I]); each element whose byte el+0x18 == 2 has its el+0x8 control block released: double `lock dec` (+0x8, +0xC) with `call qword ptr [0xF99FFA0]` destroy idiom [I]; loop continues until end pointer. [V all lines]

```asm
0x674152e  mov rdi,[rbp+0x18]
0x6741532  test rdi,rdi
0x6741535  je short 0x6741585
0x6741537  mov rbx,[rbp+0x20]
0x674153b  jmp short 0x6741544
0x674153d  nop [rax]
0x6741540  add rdi,0x28
0x6741544  cmp rdi,rbx
0x6741547  je short 0x6741585
0x6741549  cmp byte ptr [rdi+0x18],2
0x674154d  jne short 0x6741540
0x674154f  mov rsi,[rdi+8]
0x6741553  test rsi,rsi
0x6741556  je short 0x6741540
0x6741558  lock dec dword ptr [rsi+8]
0x674155c  jne short 0x6741540
0x674155e  mov rax,[rsi]
0x6741561  mov rax,[rax]
0x6741564  mov rcx,rsi
0x6741567  call qword ptr [0xF99FFA0]
0x674156d  lock dec dword ptr [rsi+0xC]
0x6741571  jne short 0x6741540
0x6741573  mov rax,[rsi]
0x6741576  mov rax,[rax+8]
0x674157a  mov rcx,rsi
0x674157d  call qword ptr [0xF99FFA0]
0x6741583  jmp short 0x6741540
```

**0x6741585..0x67415D5** — If the fr+0x0 tag byte is 1 and fr-0x40 is non-null, frees the heap buffer [fr-0x40, fr-0x30): the 0x1000 threshold, `[rcx-8]` size probe, 0x20 alignment check (failure jumps 0x67415F9) and `call 0xE935700` are the MSVC `operator delete` bookkeeping [I]; then the full epilogue and `ret`. [V all lines]

```asm
0x6741585  cmp byte ptr [rbp],1
0x6741589  jne short 0x67415C2
0x674158b  mov rcx,[rbp-0x40]
0x674158f  test rcx,rcx
0x6741592  je short 0x67415C2
0x6741594  mov rdx,[rbp-0x30]
0x6741598  sub rdx,rcx
0x674159b  cmp rdx,0x1000
0x67415a2  jb short 0x67415BC
0x67415a4  mov rax,[rcx-8]
0x67415a8  add rcx,0xFFFFFFFFFFFFFFF8
0x67415ac  sub rcx,rax
0x67415af  cmp rcx,0x20
0x67415b3  jae short 0x67415F9
0x67415b5  or rdx,0x27
0x67415b9  mov rcx,rax
0x67415bc  call 0xE935700
0x67415c1  nop
0x67415c2  add rsp,0x118
0x67415c9  pop rbx
0x67415ca  pop rdi
0x67415cb  pop rsi
0x67415cc  pop r12
0x67415ce  pop r13
0x67415d0  pop r14
0x67415d2  pop r15
0x67415d4  pop rbp
0x67415d5  ret
```

**0x67415D6..0x6741612** — Two tails of the main function: (a) 0x67415D6 reached when fr+0x40 was null — qword fr+0x38 -> out+0x158, zero to out+0x160, tag 3 to out+0x168, `jmp 0x6741477`; (b) 0x67415F9 reached on the delete bookkeeping failure — zeroes rcx/edx/r8d/r9d and `call qword ptr [0xF9A8C78]` (invalid-parameter/abort import [I]), then int3. [V all lines]

```asm
0x67415d6  mov rax,[rbp+0x38]
0x67415da  mov [r9+0x158],rax
0x67415e1  mov qword ptr [r9+0x160],0
0x67415ec  mov byte ptr [r9+0x168],3
0x67415f4  jmp 0x6741477
0x67415f9  mov qword ptr [rsp+0x20],0
0x6741602  xor ecx,ecx
0x6741604  xor edx,edx
0x6741606  xor r8d,r8d
0x6741609  xor r9d,r9d
0x674160c  call qword ptr [0xF9A8C78]
0x6741612  int3
```

**0x6741613..0x6741657** — nop pads then helper (b): spills rdx to its home slot fr2+0x10, 8 pushes + 0x38 frame, `lea rbp,[rdx+0x80]`, `lea rcx,[rbp-0x40]` (= rdx+0x40) and `call 0x56AE910` — single destructor-style call on the rdx+0x40 member [I]; epilogue and `ret`; nop pad. [V all lines]

```asm
0x6741613  nop [rax+rax]
0x6741620  mov [rsp+0x10],rdx
0x6741625  push rbp
0x6741626  push r15
0x6741628  push r14
0x674162a  push r13
0x674162c  push r12
0x674162e  push rsi
0x674162f  push rdi
0x6741630  push rbx
0x6741631  sub rsp,0x38
0x6741635  lea rbp,[rdx+0x80]
0x674163c  lea rcx,[rbp-0x40]
0x6741640  call 0x56AE910
0x6741645  nop
0x6741646  add rsp,0x38
0x674164a  pop rbx
0x674164b  pop rdi
0x674164c  pop rsi
0x674164d  pop r12
0x674164f  pop r13
0x6741651  pop r14
0x6741653  pop r15
0x6741655  pop rbp
0x6741656  ret
0x6741657  nop [rax+rax]
```

**0x6741660..0x67416AF** — Helper (c): same shape; rbp=[rdx+0x80]; loads qword [rbp+0x80] (= rdx+0x100) and `call 0x67B5310` on it; then `lea rcx,[rbp+0x10]` (= rdx+0x90) and `call 0x566D290` — two member destructor-style calls [I]; epilogue, `ret`, then int3 pads to the end of the listing. [V all lines]

```asm
0x6741660  mov [rsp+0x10],rdx
0x6741665  push rbp
0x6741666  push r15
0x6741668  push r14
0x674166a  push r13
0x674166c  push r12
0x674166e  push rsi
0x674166f  push rdi
0x6741670  push rbx
0x6741671  sub rsp,0x38
0x6741675  lea rbp,[rdx+0x80]
0x674167c  mov rcx,[rbp+0x80]
0x6741683  call 0x67B5310
0x6741688  lea rcx,[rbp+0x10]
0x674168c  call 0x566D290
0x6741691  nop
0x6741692  add rsp,0x38
0x6741696  pop rbx
0x6741697  pop rdi
0x6741698  pop rsi
0x6741699  pop r12
0x674169b  pop r13
0x674169d  pop r14
0x674169f  pop r15
0x67416a1  pop rbp
0x67416a2  ret
0x67416a3  int3
0x67416a4  int3
0x67416a5  int3
0x67416a6  int3
0x67416a7  int3
0x67416a8  int3
0x67416a9  int3
0x67416aa  int3
0x67416ab  int3
0x67416ac  int3
0x67416ad  int3
0x67416ae  int3
0x67416af  int3
```

### Field table — every [reg+off] site of the record builder + helpers, one row per (object, offset), all sites listed

Base names: self=rcx/rsi (provider), rec=[self+0x10], obj=[rec], objin=[obj+0x1B0], sub0=[self+0x18], comp=[self+0x20], cfg=[self+0x28], svc=[self+0x8]...svc deref arg, out=r14/r9 (produced record), cb=[element/stack shared-ptr control block], el=0x28-byte vector element, fr=rbp frame (=[rsp+0x80]), frsp=rsp slots, obj2=rdx of helpers (b)/(c).

| offset | size | dir | verbatim site line(s) | meaning |
|---|---|---|---|---|
| self+0x0 | 8 | R | 0x67412a5  mov rax,[rsi] | [I] first qword (vftable or lead field); deref'd again for the call arg |
| vtvt+0x0 | 8 | R | 0x67412a8  mov rdx,[rax] | [I] second-level qword passed as rdx to 0x66A0F60 |
| self+0x8 | 8 | R | 0x67411dc  mov r12,[rcx+8] | [I] later yields svc arg via svc+0x3B8 |
| self+0x10 | 8 | R | 0x67411e4  mov rax,[rcx+0x10] | [I] ptr to rec |
| self+0x18 | 8 | R | 0x674121e  mov rcx,[rsi+0x18] | [I] ptr to sub0 |
| self+0x20 | 8 | R | 0x674120c  mov rbx,[rcx+0x20] | [I] ptr to comp |
| self+0x28 | 8 | R | 0x67411e0  mov r15,[rcx+0x28] | [I] ptr to cfg |
| rec+0x0 | 8 | R | 0x6741225  mov rax,[rax] | [I] deref to obj |
| rec+0x8 | 16 | R | 0x67411e8  movups xmm0,[rax+8] | 16 bytes staged to fr-0x40 |
| rec+0x18 | 16 | R | 0x67411f0  movups xmm0,[rax+0x18] | staged to fr-0x30 |
| rec+0x28 | 16 | R | 0x67411f8  movups xmm0,[rax+0x28] | staged to fr-0x20 |
| rec+0x38 | 16 | R | 0x6741200  movups xmm0,[rax+0x38] | staged to fr-0x10 |
| rec+0xF2 | 2 | R | 0x6741210  movzx ecx,word ptr [rax+0xF2] | word staged to fr+0x8E |
| obj+0x1B0 | 8 | R | 0x674122f  mov rcx,[rax+0x1B0]<br>0x674125a  mov rax,[rax+0x1B0] | [I] object ptr of shared-ptr pair |
| obj+0x1B8 | 8 | R | 0x674123f  mov rcx,[rax+0x1B8]<br>0x674124f  mov rcx,[rax+0x1B8] | [I] control-block ptr (AddRef'd) |
| objin+0x10 | 2 | R | 0x674123b  movzx ecx,word ptr [rcx+0x10] | read only when obj+0x1B0 non-null [I] |
| sub0+0x0 | 4 | R | 0x6741222  mov r13d,[rcx] | dword passed as shadow arg to 0x66A0F60 |
| svc+0x3B8 | 8 | R | 0x674129d  mov r8,[r12+0x3B8] | [I] r8 arg of 0x66A0F60 |
| comp+0x0 | 8 | R | 0x67413ac  mov rax,[rbx] | qword stored to out+0xA0 |
| comp+0x8 | - | A | 0x67413bd  lea rdx,[rbx+8] | [I] address passed as source arg to 0xE869FF0 |
| comp+0x80 | 8 | RW | 0x67413ce  mov rax,[rbx+0x80]<br>0x67413e3  mov qword ptr [rbx+0x80],0 | [I] moved into out+0x120 then nulled |
| cfg+0x0 | 16 | R | 0x67412d6  movups xmm0,[r15] | 16 bytes to out+0x0 |
| cfg+0x10 | 4 | R | 0x67412ce  mov eax,[r15+0x10] | to out+0x10 (stored before the block) |
| cfg+0x14 | 1 | R | 0x67412de  movzx eax,byte ptr [r15+0x14] | to out+0x14 |
| cfg+0x18 | 4 | R | 0x67412e7  movss xmm0,[r15+0x18] | to out+0x18 |
| cfg+0x1C | 4 | R | 0x67412f3  movss xmm0,[r15+0x1C] | to out+0x1C |
| cfg+0x20 | 4 | R | 0x67412ff  movss xmm0,[r15+0x20] | to out+0x20 |
| cfg+0x24 | 4 | R | 0x674130b  movss xmm0,[r15+0x24] | to out+0x24 |
| cfg+0x28 | 16 | R | 0x6741317  movups xmm0,[r15+0x28] | to out+0x28 |
| cfg+0x38 | 16 | R | 0x674131c  movups xmm1,[r15+0x38] | to out+0x38 |
| cfg+0x47 | 16 | R | 0x6741321  movups xmm2,[r15+0x47] | to out+0x47 |

| offset | size | dir | verbatim site line(s) | meaning |
|---|---|---|---|---|
| out+0x0 | 16 | W | 0x67412da  movups [r14],xmm0 | from cfg+0x0 |
| out+0x10 | 4 | W | 0x67412d2  mov [r14+0x10],eax | from cfg+0x10 |
| out+0x14 | 1 | W | 0x67412e3  mov [r14+0x14],al | from cfg+0x14 |
| out+0x18 | 4 | W | 0x67412ed  movss [r14+0x18],xmm0 | from cfg+0x18 |
| out+0x1C | 4 | W | 0x67412f9  movss [r14+0x1C],xmm0 | from cfg+0x1C |
| out+0x20 | 4 | W | 0x6741305  movss [r14+0x20],xmm0 | from cfg+0x20 |
| out+0x24 | 4 | W | 0x6741311  movss [r14+0x24],xmm0 | from cfg+0x24 |
| out+0x28 | 16 | W | 0x6741326  movups [r14+0x28],xmm0 | from cfg+0x28 |
| out+0x38 | 16 | W | 0x674132b  movups [r14+0x38],xmm1 | from cfg+0x38 |
| out+0x47 | 16 | W | 0x6741330  movups [r14+0x47],xmm2 | from cfg+0x47 |
| out+0x58 | 16 (movups), 8 (qword) | W | 0x6741351  movups [r14+0x58],xmm0<br>0x674139c  movups [r14+0x58],xmm0<br>0x674137f  mov [r14+0x58],rcx | [I] variant member 1 (fr+0x0 tag: 0/1 copy 16 bytes, 2 qword) |
| out+0x68 | 16 (movups), 8 (qword) | W | 0x674135a  movups [r14+0x68],xmm0<br>0x67413a1  mov [r14+0x68],rcx | [I] variant member 2 |
| out+0x78 | 16 | W | 0x6741363  movups [r14+0x78],xmm0 | from fr-0x20 |
| out+0x88 | 16 | W | 0x674136c  movups [r14+0x88],xmm0 | from fr-0x10 |
| out+0x98 | 1 | W | 0x6741335  mov byte ptr [r14+0x98],0xFF<br>0x67413a5  mov [r14+0x98],al | [I] 0xFF init then variant tag byte |
| out+0xA0 | 8 | W | 0x67413af  mov [r14+0xA0],rax | from comp+0x0 |
| out+0xA8 | - | A | 0x67413b6  lea rcx,[r14+0xA8] | [I] dst arg of 0xE869FF0 |
| out+0x120 | 8 | W | 0x67413dc  mov [r9+0x120],rax | from comp+0x80 (moved) |
| out+0x128 | 2 | W | 0x67413f5  mov [r9+0x128],ax | from fr+0x8E |
| out+0x130 | 16 | W | 0x6741409  movups [r9+0x130],xmm0 | from fr+0x10 (moved) |
| out+0x140 | 16 | W | 0x674141c  movups [r9+0x140],xmm0 | from fr+0x20 (moved) |
| out+0x150 | 8 | W | 0x6741428  mov [r9+0x150],rax | from fr+0x30 |
| out+0x158 | 16 (movups), 8 (qword) | W | 0x674146d  movups [rcx],xmm0<br>0x6741496  movups [rcx],xmm0<br>0x67414b9  movups [r9+0x158],xmm0<br>0x6741461  mov [rcx],rdx<br>0x67415da  mov [r9+0x158],rax | [I] union member, 16B or qword per switch case; rcx=[r9+0x158] via lea @0x6741445 |
| out+0x160 | 8 | W | 0x67415e1  mov qword ptr [r9+0x160],0 | [I] zeroed in the fr+0x40-null tail |
| out+0x168 | 1 | W | 0x674142f  mov byte ptr [r9+0x168],0xFF<br>0x6741470  mov [r9+0x168],al<br>0x67414c1  mov byte ptr [r9+0x168],3<br>0x67415ec  mov byte ptr [r9+0x168],3 | [I] type tag byte (0xFF init; al = switch value; 3 for case 3) |
| out+0x170 | 16 | W | 0x674147b  movups [r9+0x170],xmm0<br>0x67414cd  movups [r9+0x170],xmm0<br>0x6741526  movups [r9+0x170],xmm0 | from fr+0x50 |
| out+0x180 | 8 | W | 0x6741487  mov [r9+0x180],rax<br>0x67414d9  mov [r9+0x180],rcx<br>0x674151b  mov [r9+0x180],rax | from fr+0x60 |

| offset | size | dir | verbatim site line(s) | meaning |
|---|---|---|---|---|
| cb+0x0 | 8 | R | 0x6741278  mov rax,[rdi]<br>0x674155e  mov rax,[rsi]<br>0x67414f0  mov rax,[rsi] | [I] vtable of control block |
| cb+0x8 | 4 | RW | 0x6741272  lock dec dword ptr [rdi+8]<br>0x6741558  lock dec dword ptr [rsi+8]<br>0x67414ea  lock dec dword ptr [rsi+8] | [I] atomic refcount decrement (release idiom) |
| cb+0xC | 4 | RW | 0x6741287  lock dec dword ptr [rdi+0xC]<br>0x674156d  lock dec dword ptr [rsi+0xC]<br>0x67414ff  lock dec dword ptr [rsi+0xC] | [I] second count, decremented after the destroy call |
| cbvt+0x0 | 8 | R | 0x674127b  mov rax,[rax]<br>0x6741561  mov rax,[rax]<br>0x67414f3  mov rax,[rax] | [I] destroy slot from cb vtable |
| cbvt+0x8 | 8 | R | 0x6741290  mov rax,[rax+8]<br>0x6741576  mov rax,[rax+8]<br>0x6741508  mov rax,[rax+8] | [I] second destroy slot |
| el+0x8 | 8 | R | 0x674154f  mov rsi,[rdi+8] | [I] control block held by the element |
| el+0x18 | 1 | R | 0x6741549  cmp byte ptr [rdi+0x18],2 | [I] element tag; only value 2 gets released |

| offset | size | dir | verbatim site line(s) | meaning |
|---|---|---|---|---|
| fr-0x40 | 16 (movaps), 8 (qword) | RW | 0x67411ec  movaps [rbp-0x40],xmm0<br>0x674134d  movaps xmm0,[rbp-0x40]<br>0x6741391  movaps xmm0,[rbp-0x40]<br>0x674137b  mov rcx,[rbp-0x40]<br>0x674158b  mov rcx,[rbp-0x40] | [I] staged 16B block from rec+0x8; also heap base ptr freed when fr+0x0 == 1 |
| fr-0x30 | 16 (movaps), 8 (qword) | RW | 0x67411f4  movaps [rbp-0x30],xmm0<br>0x6741356  movaps xmm0,[rbp-0x30]<br>0x6741385  mov rcx,[rbp-0x30]<br>0x6741389  mov qword ptr [rbp-0x30],0<br>0x6741594  mov rdx,[rbp-0x30] | [I] staged 16B block from rec+0x18; +0x8 qword is the heap end ptr in the free path |
| fr-0x20 | 16 | RW | 0x67411fc  movaps [rbp-0x20],xmm0<br>0x674135f  movaps xmm0,[rbp-0x20] | staged block from rec+0x28 |
| fr-0x10 | 16 | RW | 0x6741204  movaps [rbp-0x10],xmm0<br>0x6741368  movaps xmm0,[rbp-0x10] | staged block from rec+0x38 |
| fr+0x0 | 1 | RW | 0x6741208  mov byte ptr [rbp],0<br>0x674133d  movzx eax,byte ptr [rbp]<br>0x6741585  cmp byte ptr [rbp],1 | [I] variant tag: 0/1/2 pick copy style; ==1 selects the free path |
| fr+0x8E | 2 | RW | 0x6741217  mov [rbp+0x8E],cx<br>0x67413ee  movzx eax,word ptr [rbp+0x8E] | staged word from rec+0xF2, stored to out+0x128 |
| fr+0x10 | 16 | R | 0x67413fd  movaps xmm0,[rbp+0x10] | [I] object built by 0x66A0F60 (rcx arg = lea fr+0x10 @0x67412c0) |
| fr+0x18 | 8 | RW | 0x6741401  mov qword ptr [rbp+0x18],0<br>0x674152e  mov rdi,[rbp+0x18] | [I] vector begin (walked, then released) |
| fr+0x20 | 16 (movaps), 8 (qword) | RW | 0x6741418  movaps [rbp+0x20],xmm1<br>0x6741537  mov rbx,[rbp+0x20] | [I] moved to out+0x140 then zeroed; qword = vector end |
| fr+0x30 | 8 | R | 0x6741424  mov rax,[rbp+0x30] | qword moved to out+0x150 |
| fr+0x38 | 16 (movups), 8 (qword) | R | 0x674146a  movups xmm0,[rdx]<br>0x67414b5  movups xmm0,[rbp+0x38]<br>0x674145d  mov rdx,[rbp+0x38]<br>0x67415d6  mov rax,[rbp+0x38] | [I] union source for out+0x158 (lea fr+0x38 @0x6741466) |
| fr+0x40 | 8 | R | 0x6741499  mov rax,[rbp+0x40]<br>0x67414b1  mov rsi,[rbp+0x40] | [I] optional shared-ptr object ptr (AddRef'd, then temp released) |
| fr+0x48 | 1 | R | 0x6741437  movzx eax,byte ptr [rbp+0x48]<br>0x67414aa  cmp byte ptr [rbp+0x48],3 | [I] switch selector 0..3 (ja default; jt 0xF2BFC40) |
| fr+0x50 | 16 | R | 0x6741477  movaps xmm0,[rbp+0x50]<br>0x67414c9  movaps xmm0,[rbp+0x50]<br>0x6741522  movaps xmm0,[rbp+0x50] | 16 bytes copied to out+0x170 |
| fr+0x60 | 8 | R | 0x6741483  mov rax,[rbp+0x60]<br>0x67414d5  mov rcx,[rbp+0x60]<br>0x6741517  mov rax,[rbp+0x60] | qword copied to out+0x180 |
| fr+0x70 | 16 (movaps), 8 (qword) | RW | 0x674122b  movaps [rbp+0x70],xmm0<br>0x6741261  mov [rbp+0x70],rax | [I] stack shared_ptr: zero-init, object ptr from obj+0x1B0 (r9 arg = lea fr+0x70 @0x67412c4) |
| fr+0x78 | 8 | RW | 0x6741265  mov rdi,[rbp+0x78]<br>0x6741269  mov [rbp+0x78],rcx | [I] control qword of that shared_ptr, swapped then old released |
| fr+0x80 | 8 | RW | 0x67413c1  mov [rbp+0x80],r14<br>0x67413d5  mov r9,[rbp+0x80] | [I] spill of out across the 0xE869FF0 call |
| fr+0x90 | 8 | W | 0x67411cb  mov qword ptr [rbp+0x90],0xFFFFFFFFFFFFFFFE | [I] MSVC EH/init cookie |

| offset | size | dir | verbatim site line(s) | meaning |
|---|---|---|---|---|
| frsp+0x10 | 8 | W | 0x6741620  mov [rsp+0x10],rdx<br>0x6741660  mov [rsp+0x10],rdx | [I] home slot for the rdx arg of the helper calls |
| frsp+0x20 | 4 (dword), 8 (qword) | W | 0x67412ab  mov [rsp+0x20],r13d<br>0x67415f9  mov qword ptr [rsp+0x20],0 | [I] shadow arg for 0x66A0F60 / zeroed for the 0xF9A8C78 call |
| frsp+0x28 | 4 | W | 0x67412b8  mov dword ptr [rsp+0x28],0 | [I] shadow arg (0) |
| frsp+0x30 | 4 | W | 0x67412b0  mov dword ptr [rsp+0x30],0 | [I] shadow arg (0) |
| obj2+0x40 | - | A | 0x674163c  lea rcx,[rbp-0x40] | [I] rbp=[rdx+0x80] @0x6741635, so rcx=rdx+0x40; arg of 0x56AE910 |
| obj2+0x90 | - | A | 0x6741688  lea rcx,[rbp+0x10] | [I] rdx+0x90; arg of 0x566D290 |
| obj2+0x100 | 8 | R | 0x674167c  mov rcx,[rbp+0x80] | [I] rdx+0x100; arg of 0x67B5310 |

### Callees and call targets

- 0x66A0F60 (call @0x67412c8) — args rcx=fr+0x10, rdx=vtvt, r8=svc+0x3B8, r9=fr+0x70, shadow r13d/0/0; builds/initializes the object later moved to out+0x130..out+0x150 [I]
- 0xE869FF0 (call @0x67413c8) — move-construct/copy into out+0xA8 from comp+0x8 [I]
- 0xE935700 (call @0x67415bc) — operator delete for the fr-0x40 buffer [I from the 0x1000/0x20 bookkeeping]
- qword ptr [0xF99FFA0] (calls @0x6741281, 0x6741297, 0x67414f9, 0x674150f, 0x6741567, 0x674157d) — control-block destroy/delete import [I]
- qword ptr [0xF9A8C78] (call @0x674160c) — called with all-zero regs on delete bookkeeping failure [UNVERIFIED: 0x674160c identity of the 0xF9A8C78 import]
- 0x56AE910 (call @0x6741640), 0x67B5310 (call @0x6741683), 0x566D290 (call @0x674168c) — destructor-style member calls of helpers (b)/(c) [I]

### OPEN

- [UNVERIFIED: 0x668b166 is [rcx]=rdx a vftable or a plain first field?]
- [UNVERIFIED: 0x67412c8 what object type 0x66A0F60 constructs at fr+0x10]
- The fr+0x0 variant byte and fr+0x48 switch selector semantics are inferred from branch shape only [I].

## TOOL REQUESTS

None

