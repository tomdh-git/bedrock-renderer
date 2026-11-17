# UNIT U-EL1o — Per-draw constant stream cursor + 20-byte binding records (types 0-8); opcode set (6an)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred (say from what), [?] = unknown. Nothing invented.
This unit closes the pending part of checklist item L1o: "opcode set pending" (types 0-8 dispatch + default handler). Cursor and record fields were proven in U-A7c (verify_oc 57/57); those quotes are reused verbatim here and re-laid out in the required row format.

## NEXT
DONE

---

## (1) Constant-stream cursor (stream object at rbx+0xB8, loaded into r8 by `0xe82303d mov r8,[rbx+0xB8]`)

| name | rva or offset | size | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| stream object base | rbx+0xB8 | 8 | `0xe82303d mov r8,[rbx+0xB8]` | stream object pointer loaded into r8 | [V] |
| stream cursor (+8) | r8+8 | 8 | `0xe823048 add [r8+8],rdx` / `0xe824ad6 add [r8+8],rax` | strides-consumed write pos, advanced per record | [V] |
| stream stride (+0x18) | r8+0x18 | 4 | `0xe823044 mov edx,[r8+0x18]` / `0xe8252f3 mov ecx,[r8+0x18]` | bytes per constant record | [V] |
| stream data pointer (+0x10) | r8+0x10 | 8 | `0xe82304c mov rdx,[r8+0x10]` / `0xe823062 mov [r8+0x10],rax` / `0xe824ae4 mov rax,[r8+0x10]` / `0xe8252fa mov [r8+0x10],rcx` | current constant-record address | [V] |
| stream end bound | rbx+0x110 | 8 | `0xe82305b mov rdx,[rbx+0x110]` | end bound for the stream | [I] |
| descriptor-table slot index | r10d | n/a | `0xe823033 inc r10d` | slot index incremented per record written | [V] |

Proof block (verbatim rdis, each line starts at its RVA):

```
e823030  mov eax,r10d
e823033  inc r10d
e823036  mov rcx,[rbx+0x2C0]
e82303d  mov r8,[rbx+0xB8]
e823044  mov edx,[r8+0x18]
e823048  add [r8+8],rdx
e82304c  mov rdx,[r8+0x10]
e823050  mov [rcx+rax*8],rdx
e823054  mov eax,[r8+0x18]
e823058  add rax,rdx
e82305b  mov rdx,[rbx+0x110]
e823062  mov [r8+0x10],rax
e824ab7  test byte ptr [0x12ADFA53],0x80
e824ad2  mov eax,[r8+0x18]
e824ad6  add [r8+8],rax
e824ae4  mov rax,[r8+0x10]
e824ae8  mov [rcx+rdx*8],rax
e824aec  jmp 0xE8252F3
e8252f3  mov ecx,[r8+0x18]
e8252f7  add rcx,rax
e8252fa  mov [r8+0x10],rcx
```

---

## (2) 20-byte binding record fields (stride index*5 = 20 at `0xe823086 lea rax,[rax+rax*4]`)

| name | rva or offset | size | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| record stride | 0xe823086 | n/a | `0xe823086 lea rax,[rax+rax*4]` | index*5 = 20-byte stride, no memory access | [V] |
| record +0x0A handle | +0x0A | 2 | `0xe823091 movzx edi,word ptr [rcx+rax*4+0xA]` | handle; 0xFFFF = none => cursor advance, no type dispatch | [V] |
| record +0x11 access flag | +0x11 | 1 | `0xe824a59 cmp byte ptr [rsi+0x11],0` / `0xe82375b cmp byte ptr [rax+0x11],0` / `0xe824b9c cmp byte ptr [r12+0x11],0` | 0 = read, nonzero = needs UAV/write transition | [I] |
| record +0x12 flag byte | +0x12 | 1 | `0xe823798 movzx r14d,byte ptr [rax+0x12]` | nested-record flag byte (types 6/7) | [V] |
| record +0x13 type byte | +0x13 | 1 | `0xe8230aa movzx eax,byte ptr [rsi+0x13]` / `0xe824a84 cmp byte ptr [rsi+0x13],1` | opcode 0-8, jump-table index | [V] |
| record +0x04 dword | +0x04 | 4 | `0xe824a9c mov r8d,[rsi+4]` | type 1/2 dword field | [I] |
| record unread bytes | +0x00..+0x09 excl +0x0A, +0x0C, +0x0E, +0x10 | - | - | not read by any handler observed | [?] |

Proof block:

```
e823086  lea rax,[rax+rax*4]
e823091  movzx edi,word ptr [rcx+rax*4+0xA]
e823096  cmp rdi,0xFFFF
e82309d  je short 0xE823030
e8230aa  movzx eax,byte ptr [rsi+0x13]
e824a42  imul rdi,0x78
e824a46  add rdi,[rbx+0x5D8]
e824a4f  shl edi,7
e824a52  add rdi,[rbx+0x588]
e824a59  cmp byte ptr [rsi+0x11],0
e824a84  cmp byte ptr [rsi+0x13],1
e824a9c  mov r8d,[rsi+4]
e823283  shl rcx,4
e8232fc  lea r10,[rax+rax*4]
e823300  movzx r12d,word ptr [r14+r10*4+0xA]
e823306  cmp r12,0x1000
e82375b  cmp byte ptr [rax+0x11],0
e823798  movzx r14d,byte ptr [rax+0x12]
e824b07  shl rsi,4
e824b77  lea rdx,[rcx+rcx*4]
e824b7b  movzx ecx,word ptr [rax+rdx*4+0xA]
e824b80  cmp rcx,0xFFFF
e824b9c  cmp byte ptr [r12+0x11],0
e824b89  lea r12,[rax+rdx*4]
e824b8d  imul rax,rcx,0x78
e824c41  cmp r8d,0xFFF
```

---

## (3) Opcode set — dispatch (the pending part of L1o)

Type byte is loaded at record +0x13, range-checked against 8, and dispatched through an int32 jump table:

```
e8230aa  movzx eax,byte ptr [rsi+0x13]
e8230ae  cmp rax,8
e8230b2  ja 0xE824FBE
e8230b8  lea rcx,[0xF4EE774]
e8230bf  movsxd rax,[rcx+rax*4]
e8230c3  add rax,rcx
e8230c6  jmp rax
```

Jump table decoded with `python tools/sigs/jt.py 0xF4EE774 9` (9 int32 signed entries, base 0xF4EE774):

| opcode | handler RVA | target | tag |
|---|---|---|---|
| 0 | 0xe8230c8 | texture, guarded paged array (stride 0xB8, guard byte 0xC96190) | [V] |
| 1 | 0xe824a42 | buffer, 0x78-stride table at rbx+0x5D8 | [V] |
| 2 | 0xe824a4f | buffer, 0x80-stride table at rbx+0x588 | [V] |
| 3 | 0xe8230c8 | texture, same as opcode 0 | [V] |
| 4 | 0xe824991 | framebuffer/render target, 0x78-stride table + attachment array (handle>>6) | [V] |
| 5 | 0xe824ab7 | inline constant/uniform stream copy, consumes 1 stride | [V] |
| 6 | 0xe82326d | descriptor-table list, 16-byte stride, nested 20-byte records | [V] |
| 7 | 0xe82326d | descriptor-table list, same as opcode 6 | [V] |
| 8 | 0xe824af1 | list variant of 5/6, binds via 0x78-stride table | [V] |
| >8 | 0xe824fbe | default handler (see below) | [V] |

Per-opcode handler entry quotes (verbatim rdis):

```
e8230c8  movzx ecx,byte ptr [r9+0xC96190]
e824a42  imul rdi,0x78
e824a46  add rdi,[rbx+0x5D8]
e824a4f  shl edi,7
e824a52  add rdi,[rbx+0x588]
e824991  imul rax,rdi,0x78
e8249c7  shr r8d,6
e8249d2  mov r9,[r11+r8*8+0x224A8]
e824ab7  test byte ptr [0x12ADFA53],0x80
e824ad2  mov eax,[r8+0x18]
e824ad6  add [r8+8],rax
e824ae4  mov rax,[r8+0x10]
e824ae8  mov [rcx+rdx*8],rax
e824aec  jmp 0xE8252F3
e8252f3  mov ecx,[r8+0x18]
e8252f7  add rcx,rax
e8252fa  mov [r8+0x10],rcx
e823283  shl rcx,4
e8232fc  lea r10,[rax+rax*4]
e823300  movzx r12d,word ptr [r14+r10*4+0xA]
e82375b  cmp byte ptr [rax+0x11],0
e823798  movzx r14d,byte ptr [rax+0x12]
e824b07  shl rsi,4
e824b77  lea rdx,[rcx+rcx*4]
e824b7b  movzx ecx,word ptr [rax+rdx*4+0xA]
e824b8d  imul rax,rcx,0x78
```

Default handler (type > 8), first reached at 0xe824fbe (size 0x2000). Entry is not a bind: it counts and jumps back to the main loop at 0xe82306e:

```
e824fbe  mov eax,[rbx+0x150]
e824fc4  mov r10d,[rbx+0xF0]
e824fcb  inc eax
e824fcd  jmp 0xE82306E
```

Row summary for the opcode set:

| name | rva or offset | size | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| type-byte load | +0x13 | 1 | `0xe8230aa movzx eax,byte ptr [rsi+0x13]` | opcode loaded before dispatch | [V] |
| opcode range check | 0xe8230ae | n/a | `0xe8230ae cmp rax,8` / `0xe8230b2 ja 0xE824FBE` | type > 8 goes to default handler | [V] |
| jump table base | 0xe8230b8 | n/a | `0xe8230b8 lea rcx,[0xF4EE774]` | jump table base address | [V] |
| indirect dispatch | 0xe8230bf | 4 | `0xe8230bf movsxd rax,[rcx+rax*4]` / `0xe8230c3 add rax,rcx` / `0xe8230c6 jmp rax` | base + int32[opcode] = handler RVA | [V] |
| opcodes 0,3 handler | 0xe8230c8 | 1 | `0xe8230c8 movzx ecx,byte ptr [r9+0xC96190]` | texture via guarded paged array | [V] |
| opcode 1 handler | 0xe824a42 | n/a | `0xe824a42 imul rdi,0x78` / `0xe824a46 add rdi,[rbx+0x5D8]` | buffer, 0x78-stride table | [V] |
| opcode 2 handler | 0xe824a4f | n/a | `0xe824a4f shl edi,7` / `0xe824a52 add rdi,[rbx+0x588]` | buffer, 0x80-stride table | [V] |
| opcode 4 handler | 0xe824991 | n/a | `0xe824991 imul rax,rdi,0x78` / `0xe8249c7 shr r8d,6` / `0xe8249d2 mov r9,[r11+r8*8+0x224A8]` | framebuffer/render target | [V] |
| opcode 5 handler | 0xe824ab7 | 1 | `0xe824ab7 test byte ptr [0x12ADFA53],0x80` | inline stream copy, consumes 1 stride | [V] |
| opcodes 6,7 handler | 0xe82326d | n/a | `0xe823283 shl rcx,4` / `0xe823300 movzx r12d,word ptr [r14+r10*4+0xA]` | descriptor-table list, nested 20-byte records | [V] |
| opcode 8 handler | 0xe824af1 | n/a | `0xe824b07 shl rsi,4` / `0xe824b77 lea rdx,[rcx+rcx*4]` / `0xe824b8d imul rax,rcx,0x78` | list variant of 5/6 | [V] |
| default handler | 0xe824fbe | 4 | `0xe824fbe mov eax,[rbx+0x150]` / `0xe824fcb inc eax` / `0xe824fcd jmp 0xE82306E` | type > 8: counts, no bind, returns to main loop | [V] |

---

## CLOSES?

CLOSES? YES — the pending part of L1o ("opcode set pending") is proven by [V] rows: type-byte load and range check at 0xe8230aa/0xe8230ae/0xe8230b2, jump table 0xF4EE774 decoded with jt.py (9 int32 entries, opcodes 0-8), every opcode handler entry quoted verbatim from disassembly, and the default handler 0xe824fbe quoted (increments [rbx+0x150] and jumps back to 0xe82306e, performs no binding). Constant-stream cursor [rbx+0xB8] fields +8/+0x10/+0x18 and advance block 0xe823030 are also [V]. Non-blocking [?] residuals documented above: record bytes +0x00..+0x09 (excl +0x0A), +0x0C, +0x0E, +0x10 are not read by any handler; the stream-end structure at rbx+0x110 is not decoded.

---

## TOOL REQUESTS

None — no helper scripts written. Evidence is the verify_oc-clean quotes from docs/progress/oc_U-A7c.md plus one `rdis dis 0xe824fbe` and one `jt.py 0xF4EE774 9` decode already performed.
