# UNIT U-A7c — Per-draw constant stream cursor + 20-byte binding records (types 0-8)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred (say from what), [?] = unknown. Nothing invented.

## NEXT
Step 1: Document 20-byte binding record field layout for each type 0..8 with quoted instructions. Step 2: Document constant-stream cursor (register/fields, stride, advance logic). Step 3: Document opcode set (binding types 0-8, jump table 0xF4EE774, compare/jump instructions, handler RVAs). Then run verify_oc.py.

---

## (1) 20-byte binding record — field layout per binding type

The per-draw binding records are 20 bytes (stride 20 = `lea rax,[rax+rax*4]` at `0xe823086` ×4 in addressing). The main loop at `0xe82306e..0xe8230c6` reads two fields before dispatch:
- `+0x0A` (word): handle — `0xe823091  movzx edi,word ptr [rcx+rax*4+0xA]`
- `+0x13` (byte): type — `0xe8230aa  movzx eax,byte ptr [rsi+0x13]`

If handle == 0xFFFF, the record is a **constant-stream cursor advance** (no type dispatch): `0xe823096  cmp rdi,0xFFFF` / `0xe82309d  je short 0xE823030`.

Otherwise the type byte (0..8) selects a handler via jump table at `0xF4EE774` (see §3). Each handler reads additional record fields as follows:

### Type 0, 3 — texture (guarded paged array) — handler `0xe8230c8`
No additional binding-record fields read. Handler uses the handle (already in `edi`/`r13d`) to index the guarded paged array at `[r9+0xC96180]` (stride 0xB8, guard byte at `+0xC96190`).
Quoted handler entry [V]:
```
e8230c8  movzx ecx,byte ptr [r9+0xC96190]
e8230d0  movzx r13d,di
e8230d4  cmp r13d,0x1000
e8230db  setae dl
e8230de  mov al,1
e8230e0  test dl,cl
e8230e2  jne 0xE823236
e8230e8  mov rax,[r9+0xC96180]
e8230ef  shr rax,3
```

### Type 1 — buffer (0x78-stride table at `rbx+0x5D8`) — handler `0xe824a42`
Reads binding-record `+0x11` (access flag byte) and `+0x13` (type sub-check), and `+0x04` (dword).
Quoted instructions [V]:
```
e824a59  cmp byte ptr [rsi+0x11],0          ; +0x11 access flag
e824a84  cmp byte ptr [rsi+0x13],1          ; +0x13 type sub-check (expect 1)
e824a9c  mov r8d,[rsi+4]                    ; +0x04 dword field
```
Then reads buffer-record fields at `[rdi+0x30]`, `[rdi+0x44]`, `[rdi+0x60]`, `[rdi+0x65]` (not binding record).

### Type 2 — buffer (0x80-stride table at `rbx+0x588`) — handler `0xe824a4f`
Falls through to same code as type 1 at `0xe824a59` (shares the `cmp byte ptr [rsi+0x11],0` path). No additional unique binding-record reads.

### Type 4 — framebuffer/render target — handler `0xe824991`
Reads handle (already in `rdi`) and uses it twice: `handle * 0x78` for framebuffer table at `rbx+0x3A0`, and `handle >> 6` for framebuffer-attachment array at `[r11+r8*8+0x224A8]`.
Quoted instructions [V]:
```
e824991  imul rax,rdi,0x78                  ; handle * 0x78
e8249c7  shr r8d,6                          ; handle >> 6
e8249d2  mov r9,[r11+r8*8+0x224A8]          ; framebuffer-attachment array
```

### Type 5 — inline constant/uniform stream copy — handler `0xe824ab7`
Does not read additional binding-record fields. Consumes one stride from the constant stream (see §2). Advances stream cursor and writes current stream pointer to descriptor table.
Quoted instructions [V]:
```
e824ab7  test byte ptr [0x12ADFA53],0x80    ; global flag
e824ad2  mov eax,[r8+0x18]                  ; stream stride
e824ad6  add [r8+8],rax                     ; cursor += stride
e824ae4  mov rax,[r8+0x10]                  ; current stream pointer
e824ae8  mov [rcx+rdx*8],rax                ; write to descriptor table
e824aec  jmp 0xE8252F3                      ; advance stream pointer
```
Stream pointer advance at `0xe8252f3` [V]:
```
e8252f3  mov ecx,[r8+0x18]
e8252f7  add rcx,rax
e8252fa  mov [r8+0x10],rcx
```

### Type 6, 7 — descriptor-table list (loop over 16-byte-stride array, each entry a 20-byte record) — handler `0xe82326d`
Reads nested 20-byte records from the descriptor list. For each nested record: reads `+0x0A` (handle), `+0x11` (access flag), `+0x12` (flag byte).
Quoted instructions [V]:
```
e823283  shl rcx,4                          ; index * 16 (descriptor list stride)
e8232fc  lea r10,[rax+rax*4]                ; nested index * 5 (20-byte stride)
e823300  movzx r12d,word ptr [r14+r10*4+0xA] ; nested +0x0A handle
e823306  cmp r12,0x1000
e82375b  cmp byte ptr [rax+0x11],0          ; nested +0x11 access flag
e823798  movzx r14d,byte ptr [rax+0x12]     ; nested +0x12 flag byte
```

### Type 8 — list variant of 5/6 (loops 16-byte-stride array, each entry a 20-byte record, binds via 0x78-stride table) — handler `0xe824af1`
Reads nested 20-byte records: `+0x0A` (handle), `+0x11` (access flag), `+0x13` (type sub-check).
Quoted instructions [V]:
```
e824b07  shl rsi,4                          ; index * 16 (descriptor list stride)
e824b77  lea rdx,[rcx+rcx*4]                ; nested index * 5 (20-byte stride)
e824b7b  movzx ecx,word ptr [rax+rdx*4+0xA] ; nested +0x0A handle
e824b80  cmp rcx,0xFFFF
e824b9c  cmp byte ptr [r12+0x11],0          ; nested +0x11 access flag
e824b89  lea r12,[rax+rdx*4]                ; nested record pointer
e824b8d  imul rax,rcx,0x78                  ; nested handle * 0x78
e824c41  cmp r8d,0xFFF
```

---

## (2) Constant-stream cursor

**Stream object**: at `rbx+0xB8` (loaded into `r8` at `0xe82303d  mov r8,[rbx+0xB8]`).

**Fields of the stream object** [V]:
| Offset | Size | Meaning | Advance instruction |
|--------|------|---------|---------------------|
| `+0x08` | 4/8 bytes | Cursor offset (count of strides consumed) | `0xe823048  add [r8+8],rdx` (rdx = stride) |
| `+0x10` | 8 bytes | Current data pointer (address of next constant record) | `0xe82304c  mov rdx,[r8+0x10]` (read) → `0xe823058  add rax,rdx` → `0xe823062  mov [r8+0x10],rax` (write) |
| `+0x18` | 4 bytes | Stride (bytes per constant record) | `0xe823044  mov edx,[r8+0x18]` (read once per advance) |

**Stream end/size**: at `rbx+0x110` (loaded at `0xe82305b  mov rdx,[rbx+0x110]`). Used as bound check in several places.

**Advance logic** (executed when a binding record has handle == 0xFFFF) at `loc_e823030` [V]:
```
e823030  mov eax,r10d
e823033  inc r10d
e823036  mov rcx,[rbx+0x2C0]           ; descriptor table base
e82303d  mov r8,[rbx+0xB8]             ; stream object
e823044  mov edx,[r8+0x18]             ; stride
e823048  add [r8+8],rdx                ; cursor += stride
e82304c  mov rdx,[r8+0x10]             ; current data pointer
e823050  mov [rcx+rax*8],rdx           ; write pointer to descriptor table
e823054  mov eax,[r8+0x18]             ; stride
e823058  add rax,rdx                   ; next data pointer = current + stride
e82305b  mov rdx,[rbx+0x110]           ; stream end (bound)
e823062  mov [r8+0x10],rax             ; update stream current pointer
```

**Register that advances through it**: `r8` holds the stream object pointer; the fields `[r8+8]` and `[r8+10]` are updated in-place. The descriptor table index is `r10d` (incremented at `0xe823033` and `0xe82306c`).

---

## (3) Opcode set — binding types 0..8 dispatch

The "opcodes" are the binding-record type byte values 0..8. Dispatch is via a jump table at `0xF4EE774` (9 entries, int32 signed offsets). The compare/jump sequence in the main loop [V]:

```
e8230aa  movzx eax,byte ptr [rsi+0x13]   ; load type byte (0..8)
e8230ae  cmp rax,8
e8230b2  ja 0xE824FBE                    ; type > 8 -> default handler
e8230b8  lea rcx,[0xF4EE774]            ; jump table base
e8230bf  movsxd rax,[rcx+rax*4]          ; rax = table[type] (int32 offset)
e8230c3  add rax,rcx                     ; rax = base + offset = handler RVA
e8230c6  jmp rax                         ; indirect jump to handler
```

**Jump table** at `0xF4EE774` (decoded with `python tools/sigs/jt.py 0xF4EE774 9`) [V]:

| Opcode (type) | Handler RVA | What it binds |
|---------------|-------------|---------------|
| 0 | 0xe8230c8 | Texture (guarded paged array, stride 0xB8) |
| 1 | 0xe824a42 | Buffer (0x78-stride table at `rbx+0x5D8`) |
| 2 | 0xe824a4f | Buffer (0x80-stride table at `rbx+0x588`) |
| 3 | 0xe8230c8 | Texture (same as type 0) |
| 4 | 0xe824991 | Framebuffer/render target (0x78-stride + attachment array) |
| 5 | 0xe824ab7 | Inline constant/uniform stream copy (consumes 1 stride) |
| 6 | 0xe82326d | Descriptor-table list (16-byte stride, nested 20-byte records) |
| 7 | 0xe82326d | Descriptor-table list (same as type 6) |
| 8 | 0xe824af1 | List variant of 5/6 (16-byte stride, nested records, 0x78-stride table) |

**Default handler** (type > 8): `0xe824fbe` (not individually quoted here; marked [UNVERIFIED: 0xe824fbe default handler]).

---

## Verification tags

All quoted `0xRVA  instr` lines are copied verbatim from `rdis dis` output. Tags:
- [V] = verified in disassembly (RVA cited)
- [I] = inferred from context (e.g., field meaning from usage)
- [?] = unknown

---

## Gaps / UNVERIFIED

- [UNVERIFIED: 0xe824fbe default handler for type > 8]
- [UNVERIFIED: exact meaning of binding-record `+0x00..+0x09` (10 bytes) — not read by any handler observed]
- [UNVERIFIED: exact meaning of binding-record `+0x0C`, `+0x0E`, `+0x10` (2 bytes each) — not read by any handler observed]
- [UNVERIFIED: stream end structure at `rbx+0x110` — field at `+0x410` read at `0xe822b49` but meaning unclear]

---

## TOOL REQUESTS

None needed for this unit; all data from rdis/jt.py/disassembly already in tools/sigs.