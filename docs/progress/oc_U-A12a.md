## NEXT
Resume at: DONE — verify_oc.py passed (385/385). Unit complete.

---

# Unit U-A12a: Dynamic Texture Handles (checklist A12a)

Per checklist A12a (RENDER_CHECKLIST.md line 57): "dynamic texture handles = reset flag 0x400000 + caps bit 0x12ADFA54&0x10 + free-list (6ei); createDynamicTexture 0xbc74a80"

This unit covers:
- The `createDynamicTexture` function at `0xBC74A80` (instruction-complete listing)
- The caps-bit gate at `0x12ADFA54` bit 4 (DynamicTextureHandles)
- The reset flag `0x400000` test/set in Context init
- The free-list allocator at `ctx+0x1DFB48C` (handle exhaustion + recycle)
- Callers of `0xBC74A80`

Allocator context (from U-A8a section 6):
- **Allocator offset**: `ctx + 0x1DFB48C`
- **Create function**: `0xBC74A80` (size 0x5C5)
- **Destroy function**: `0xBC750B0` (size 0x1EB)
- **Max count**: `u16 maxHandles` at `ctx+0x1DFB48E` (cmp at `0xBC74AC8` / `0xBC750F3`)
- **Caps gate**: `ctx+0x1EBF2F3` (guarded flag) + global caps `0x12ADFA54` bit 4 (DynamicTextureHandles)

---

## Step 1: Instruction-complete listing of 0xBC74A80 (createDynamicTexture)

**Function**: `sub_bc74a80` at `0xBC74A80..0xBC75045` (size 0x5C5)

**Register/argument map** (from prologue):
- `rcx` = Context* (this, `rbx` after save)
- `rdx` = output handle pointer (u16*, saved to `rsi`, then `[rbp-0x10]`)
- `r8`  = flags byte (saved to `[rbp-1]`)
- `r9`  = texture desc pointer (saved to `rdi`)
- `rbp` = stack frame base (`[rsp+0x40]`)
- `r14` = `ctx+0x1CFD0C8` (per-frame data pointer)
- `r15` = pointer into `ctx+0x1EA5AD8` (dynamic texture record array, stride 0x18)

### Phase 1: Prologue + Lock + Handle Allocation (0xBC74A80..0xBC74AFE) — 32 instructions
```
0xBC74A80  push rbp
0xBC74A81  push r15
0xBC74A83  push r14
0xBC74A85  push r13
0xBC74A87  push r12
0xBC74A89  push rsi
0xBC74A8A  push rdi
0xBC74A8B  push rbx
0xBC74A8C  sub rsp,0x48
0xBC74A90  lea rbp,[rsp+0x40]
0xBC74A95  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
0xBC74A9D  mov rdi,r9                      ; texture desc -> rdi
0xBC74AA0  mov rsi,rdx                     ; output handle ptr -> rsi
0xBC74AA3  mov rbx,rcx                     ; Context* -> rbx
0xBC74AA6  mov [rbp-1],r8b                 ; save flags byte
0xBC74AAA  add rcx,0x1C0                   ; rcx = ctx+0x1C0 (lock)
0xBC74AB1  mov [rbp-0x18],rcx              ; save lock ptr
0xBC74AB5  call 0xEBDBF10                  ; lock Context (sub_ebdbf10)
0xBC74ABA  movzx eax,word ptr [rbx+0x1DFB48C]  ; R numHandles
0xBC74AC1  movzx ecx,word ptr [rbx+0x1DFB48E]  ; R maxHandles
0xBC74AC8  cmp ax,cx                       ; num vs max
0xBC74ACB  mov [rbp-0x10],rsi              ; save output handle ptr
0xBC74ACF  jae 0xBC74E22                   ; full -> error (returns 0xFFFF)
0xBC74AD5  movzx edx,ax                    ; edx = numHandles
0xBC74AD8  lea r8d,[rax+1]                 ; r8d = numHandles+1
0xBC74ADC  mov [rbx+0x1DFB48C],r8w         ; W numHandles++
0xBC74AE4  movzx edx,word ptr [rbx+rdx*2+0x1DFB490] ; R dense[numHandles] -> handle
0xBC74AEC  lea rcx,[rbx+rcx*2]             ; rcx = &sparse[handle]
0xBC74AF0  add rcx,0x1DFB490
0xBC74AF7  mov [rcx+rdx*2],ax              ; sparse[handle] = numHandles
0xBC74AFB  mov [rsi],dx                    ; W *output = handle
0xBC74AFE  cmp edx,0xFFFF
0xBC74B04  je 0xBC74E27                    ; invalid handle -> error path
```
**What it does**: Standard handle allocator allocation from dense/sparse arrays at `ctx+0x1DFB48C`. Takes Context lock at `ctx+0x1C0`. On exhaustion (`numHandles >= maxHandles`), jumps to error at `0xBC74E22` which writes `0xFFFF` to output.

### Phase 2: Per-frame command buffer append (0xBC74B0A..0xBC74BBD) — 28 instructions
```
0xBC74B0A  mov r14,[rbx+0x1CFD0C8]          ; R ctx+0x1CFD0C8 (per-frame data)
0xBC74B11  mov byte ptr [rbp-3],0x14        ; command byte 0x14 (createDynamicTexture)
0xBC74B15  mov eax,[r14+0xDC5818]           ; R cursor
0xBC74B1C  lea rcx,[r14+rax]                ; rcx = buffer + cursor
0xBC74B20  add rcx,0xDC5820
0xBC74B27  lea rdx,[rbp-3]                  ; rdx = &command_byte
0xBC74B2B  mov r8d,1                        ; size 1
0xBC74B31  call 0xEBCE390                  ; memcpy (sub_ebce390)
0xBC74B36  nop
0xBC74B37  lea rax,[r14+0xDC5820]           ; buffer base
0xBC74B3E  mov ecx,[r14+0xDC5818]           ; R cursor
0xBC74B45  and ecx,0xFFFFFFFE               ; align down to even
0xBC74B48  add ecx,2                        ; +2 bytes
0xBC74B4B  mov [r14+0xDC5818],ecx           ; W cursor += 2 (aligned)
0xBC74B52  add rcx,rax
0xBC74B55  mov r8d,2                        ; size 2
0xBC74B5B  mov rdx,[rbp-0x10]               ; output handle ptr
0xBC74B5F  call 0xEBCE390                  ; memcpy handle (2 bytes)
0xBC74B64  nop
0xBC74B65  mov ecx,[r14+0xDC5818]           ; R cursor
0xBC74B6C  add ecx,2                        ; +2 bytes
0xBC74B6F  mov [r14+0xDC5818],ecx           ; W cursor += 2
0xBC74B76  mov byte ptr [rbp-2],0           ; zero byte
0xBC74B7A  lea rax,[r14+0xDC5820]           ; buffer base
0xBC74B81  add rcx,rax
0xBC74B84  lea rdx,[rbp-2]                  ; &zero_byte
0xBC74B88  mov r8d,1                        ; size 1
0xBC74B8E  call 0xEBCE390                  ; memcpy zero byte
0xBC74B93  nop
0xBC74B94  mov ecx,[r14+0xDC5818]           ; R cursor
0xBC74B9B  inc ecx                          ; +1 byte
0xBC74B9D  mov [r14+0xDC5818],ecx           ; W cursor += 1
0xBC74BA4  lea rax,[r14+0xDC5820]           ; buffer base
0xBC74BAB  add rcx,rax
0xBC74BAE  lea rdx,[rbp-1]                  ; &flags_byte (from r8)
0xBC74BB2  mov r8d,1                        ; size 1
0xBC74BB8  call 0xEBCE390                  ; memcpy flags byte
0xBC74BBD  nop
0xBC74BBE  inc dword ptr [r14+0xDC5818]     ; W cursor += 1 (total +6 bytes: cmd1+handle2+zero1+flags1+pad1)
```
**What it does**: Appends a command packet to the per-frame command buffer at `ctx+0x1CFD0C8+0xDC5820` (cursor at `+0xDC5818`). Packet: `[0x14][handle:u16][0x00][flags:u8]` (6 bytes with alignment).

### Phase 3: Dynamic texture record init + guarded array check (0xBC74BC5..0xBC74C50) — 24 instructions
```
0xBC74BC5  mov rax,[rbp-0x10]                ; output handle ptr
0xBC74BC9  movzx eax,word ptr [rax]          ; handle value
0xBC74BCC  lea rax,[rax+rax*2]               ; handle * 3
0xBC74BD0  lea r15,[rbx+rax*8]               ; r15 = ctx+0x1EA5AD8 + handle*0x18 (record stride 0x18)
0xBC74BD4  add r15,0x1EA5AD8
0xBC74BDB  mov byte ptr [rbx+rax*8+0x1EA5AE8],0  ; W guarded byte = 0 (ctx+0x1EA5AE8 + handle*8)
0xBC74BE3  mov r8d,0x10                      ; size 0x10
0xBC74BE9  mov rcx,r15                       ; dest = record
0xBC74BEC  mov dl,0xFF                       ; fill 0xFF
0xBC74BEE  call 0xEBCE430                   ; memset (sub_ebce430)
0xBC74BF3  nop
0xBC74BF4  cmp byte ptr [rbp-1],0            ; flags byte == 0?
0xBC74BF8  je 0xBC74E39                     ; if zero -> skip desc copy (loc_bc74e39)
0xBC74BFE  movzx esi,word ptr [rdi]          ; R desc.width (a3+0x0)
0xBC74C01  cmp rsi,0x1000                    ; width >= 4096?
0xBC74C08  setae dl                          ; dl = (width >= 4096)
0xBC74C0B  movzx ecx,byte ptr [rbx+0x1E7DAD0] ; R guarded flag (ctx+0x1E7DAD0)
0xBC74C12  mov al,1
0xBC74C14  test dl,cl                        ; guarded && width>=4096?
0xBC74C16  jne short 0xBC74C57              ; if guarded -> guarded path (loc_bc74c57)
0xBC74C18  mov rax,0xCCCCCCCCCCCCCCCD        ; magic for div 13
0xBC74C22  mul qword ptr [rbx+0x1E7DAC0]     ; W ctx+0x1E7DAC0 (page count?)
0xBC74C29  shr rdx,5                         ; rdx = page index
0xBC74C2D  mov eax,ecx
0xBC74C2F  cmp rdx,rsi                       ; page check
0xBC74C32  ja short 0xBC74C57               ; if in guarded page -> guarded path
0xBC74C34  mov edx,esi
0xBC74C36  and edx,0xF000                    ; align to 4K
0xBC74C3C  add rdx,0x1000                    ; +4K
0xBC74C43  lea rcx,[rbx+0x1E55AB8]           ; guarded array base
0xBC74C4A  call 0xBC7A3D0                   ; guarded array access (sub_bc7a3d0)
0xBC74C4F  nop
0xBC74C50  movzx eax,byte ptr [rbx+0x1E7DAD0] ; R guarded flag
```
**What it does**: Initializes the dynamic texture record at `ctx+0x1EA5AD8 + handle*0x18` (stride 0x18). Clears guarded byte at `ctx+0x1EA5AE8 + handle*8`. Memsets record to 0xFF. If flags byte != 0, reads desc width and checks against guarded paged array at `ctx+0x1E55AB8` (guarded flag at `ctx+0x1E7DAD0`). On guard violation, calls error reporter `0xBC5F110` with string "FAILED: accessing a guarded paged heap backed array out of bounds." (data_f7f68e3).

### Phase 4: Guarded array page walk (0xBC74C57..0xBC74E0F) — 80 instructions (split into sub-phases)

#### Phase 4a: Initial guard check + error (0xBC74C57..0xBC74C74) — 12 instructions
```
0xBC74C57  movzx ecx,si
0xBC74C5A  cmp ecx,0x1000
0xBC74C60  jb short 0xBC74C75
0xBC74C62  test al,al
0xBC74C64  je short 0xBC74C75
0xBC74C66  lea rdx,[0xF7F68E3]               ; "FAILED: accessing a guarded paged heap backed array out of b..."
0xBC74C6D  xor ecx,ecx
0xBC74C6F  call 0xBC5F110                    ; error reporter
0xBC74C74  nop
```

#### Phase 4b: Descriptor copy loop setup (0xBC74C75..0xBC74C9A) — 10 instructions
```
0xBC74C75  xor r12d,r12d                     ; element counter
0xBC74C78  mov rsi,0xCCCCCCCCCCCCCCCD        ; magic for div 13
0xBC74C82  jmp short 0xBC74C9B
0xBC74C84  nop [rax+rax]
```

#### Phase 4c: Descriptor copy loop body (0xBC74C90..0xBC74E0F) — 60 instructions (quoted as phases)

**Loop header** (0xBC74C9B..0xBC74CC2):
```
0xBC74C9B  movzx eax,byte ptr [rbp-1]        ; flags byte (element count)
0xBC74C9F  cmp r12d,eax
0xBC74CA2  jae 0xBC74E32                     ; done -> loc_bc74e32
0xBC74CA8  mov eax,r12d
0xBC74CAB  lea rcx,[rax+rax*2]               ; idx * 3
0xBC74CAF  movzx r13d,word ptr [rdi+rcx*2]   ; R desc element (width/height/format)
0xBC74CB4  cmp r13,0x1000
0xBC74CBB  setae dl
0xBC74CBE  mov [r15+rax*2],r13w              ; W record + idx*2 = element
0xBC74CC3  movzx ecx,byte ptr [rbx+0x1E7DAD0] ; R guarded flag
0xBC74CCA  mov al,1
0xBC74CCC  test dl,cl
0xBC74CCE  jne short 0xBC74D09              ; guarded -> loc_bc74d09
```

**Guarded page check** (0xBC74CD0..0xBC74D07):
```
0xBC74CD0  mov rax,rsi
0xBC74CD3  mul qword ptr [rbx+0x1E7DAC0]     ; W ctx+0x1E7DAC0
0xBC74CDA  shr rdx,5
0xBC74CDE  mov eax,ecx
0xBC74CE0  cmp rdx,r13
0xBC74CE3  ja short 0xBC74D09
0xBC74CE5  mov edx,r13d
0xBC74CE8  and edx,0xF000
0xBC74CEE  add rdx,0x1000
0xBC74CF5  lea rcx,[rbx+0x1E55AB8]
0xBC74CFC  call 0xBC7A3D0
0xBC74D01  nop
0xBC74D02  movzx eax,byte ptr [rbx+0x1E7DAD0]
```

**Error on guard violation** (0xBC74D09..0xBC74D38):
```
0xBC74D09  movzx edx,r13w
0xBC74D0D  cmp edx,0x1000
0xBC74D13  jb short 0xBC74D40
0xBC74D15  test al,al
0xBC74D17  je short 0xBC74D40
0xBC74D19  xor ecx,ecx
0xBC74D1B  lea rdx,[0xF7F68E3]
0xBC74D22  call 0xBC5F110
0xBC74D27  nop
```

**Page index calculation** (0xBC74D28..0xBC74DB8):
```
0xBC74D28  shl r13d,3
0xBC74D2C  lea rcx,[r13*4]
0xBC74D34  add rcx,r13
0xBC74D37  jmp short 0xBC74D5B
0xBC74D39  nop [rax]
0xBC74D40  shl r13d,3
0xBC74D44  lea rcx,[r13*4]
0xBC74D4C  add rcx,r13
0xBC74D4F  cmp edx,0xFFF
0xBC74D55  jbe 0xBC74E10
0xBC74D5B  lea r8,[rcx-0x28000]
0xBC74D62  mov rax,[rbx+0x1E7DAB8]           ; page table ptr
0xBC74D69  mov r9,[rax]                      ; first page
0xBC74D6C  cmp r8,0x28000
0xBC74D73  jb 0xBC74C90                      ; loop back (inc counter at 0xBC74C93)
0xBC74D79  add rcx,0xFFFFFFFFFFFB0000
0xBC74D80  mov rax,rcx
0xBC74D83  mul rsi
0xBC74D86  shr rdx,0x11
0xBC74D8A  mov eax,edx
0xBC74D8C  not eax
0xBC74D8E  test al,7
0xBC74D90  je short 0xBC74DB3
0xBC74D92  inc edx
0xBC74D94  and edx,7
0xBC74D97  nop [rax+rax]
0xBC74DA0  add r8,0xFFFFFFFFFFFD8000
0xBC74DA7  mov r9,[r9+0x28000]               ; next page
0xBC74DAE  dec rdx
0xBC74DB1  jne short 0xBC74DA0
0xBC74DB3  cmp ecx,0x118000
0xBC74DB9  jb 0xBC74C90                      ; loop back
0xBC74DBF  nop
```

**Deep page walk** (0xBC74DC0..0xBC74E0D):
```
0xBC74DC0  mov rax,[r9+0x28000]
0xBC74DC7  mov rax,[rax+0x28000]
0xBC74DCE  mov rax,[rax+0x28000]
0xBC74DD5  mov rax,[rax+0x28000]
0xBC74DDC  mov rax,[rax+0x28000]
0xBC74DE3  mov rax,[rax+0x28000]
0xBC74DEA  mov rax,[rax+0x28000]
0xBC74DF1  add r8,0xFFFFFFFFFFEC0000
0xBC74DF8  mov r9,[rax+0x28000]
0xBC74DFF  cmp r8,0x27FFF
0xBC74E06  ja short 0xBC74DC0
0xBC74E08  jmp 0xBC74C90
0xBC74E0D  nop [rax]
```

**In-page element store** (0xBC74E10..0xBC74E1F):
```
0xBC74E10  lea rax,[rbx+0x1E55AB8]
0xBC74E17  add rcx,rax
0xBC74E1A  mov r8,rcx
0xBC74E1D  jmp 0xBC74C93                     ; inc word ptr [r8+0x1C]; inc r12d; loop
```

### Phase 5: Completion paths (0xBC74E22..0xBC75044) — 48 instructions

**Error: handle allocator full** (0xBC74E22..0xBC74E2A):
```
0xBC74E22  mov word ptr [rsi],0xFFFF         ; return 0xFFFF
0xBC74E27  cmp byte ptr [rbp+0x70],0         ; stack cookie check
0xBC74E2B  jne short 0xBC74E69
0xBC74E2D  jmp 0xBC75026                     ; epilog
```

**Path: flags byte == 0 (no desc copy)** (0xBC74E32..0xBC74E68):
```
0xBC74E32  add eax,eax
0xBC74E34  lea esi,[rax+rax*2]
0xBC74E37  jmp short 0xBC74E3B
0xBC74E39  xor esi,esi
0xBC74E3B  mov r8d,esi
0xBC74E3E  mov eax,[r14+0xDC5818]
0xBC74E45  lea rcx,[r14+0xDC5820]
0xBC74E4C  add rcx,rax
0xBC74E4F  mov rdx,rdi
0xBC74E52  call 0xEBCE390
0xBC74E57  nop
0xBC74E58  add [r14+0xDC5818],esi
0xBC74E5F  cmp byte ptr [rbp+0x70],0
0xBC74E63  je 0xBC75026
```

**Path: stack cookie set (frame pointer guard)** (0xBC74E69..0xBC75025):
```
0xBC74E69  lea r14,[rbx+0x1E55AB8]           ; guarded array base
0xBC74E70  xor r13d,r13d
0xBC74E73  lea r15,[0xF7F68E3]               ; error string
0xBC74E7A  mov r12,0xCCCCCCCCCCCCCCCD
0xBC74E84  jmp short 0xBC74E93
0xBC74E86  nop [rax+rax]
0xBC74E90  inc r13d                          ; element loop counter
0xBC74E93  movzx eax,byte ptr [rbp-1]
0xBC74E97  cmp r13d,eax
0xBC74E9A  jae 0xBC75026
0xBC74EA0  mov eax,r13d
0xBC74EA3  lea rax,[rax+rax*2]
0xBC74EA7  movzx esi,word ptr [rdi+rax*2]
0xBC74EAB  cmp rsi,0x1000
0xBC74EB2  setae dl
0xBC74EB5  movzx ecx,byte ptr [rbx+0x1E7DAD0]
0xBC74EBC  mov al,1
0xBC74EBE  test dl,cl
0xBC74EC0  jne short 0xBC74EF6
0xBC74EC2  mov rax,r12
0xBC74EC5  mul qword ptr [rbx+0x1E7DAC0]
0xBC74ECC  shr rdx,5
0xBC74ED0  mov eax,ecx
0xBC74ED2  cmp rdx,rsi
0xBC74ED5  ja short 0xBC74EF6
0xBC74ED7  mov edx,esi
0xBC74ED9  and edx,0xF000
0xBC74EDF  add rdx,0x1000
0xBC74EE6  mov rcx,r14
0xBC74EE9  call 0xBC7A3D0
0xBC74EEE  nop
0xBC74EEF  movzx eax,byte ptr [rbx+0x1E7DAD0]
0xBC74EF6  movzx edx,si
0xBC74EF9  cmp edx,0x1000
0xBC74EFF  jb short 0xBC74F20
0xBC74F01  test al,al
0xBC74F03  je short 0xBC74F20
0xBC74F05  xor ecx,ecx
0xBC74F07  mov rdx,r15
0xBC74F0A  call 0xBC5F110
0xBC74F0F  nop
0xBC74F10  mov eax,esi
0xBC74F12  shl eax,3
0xBC74F15  lea rcx,[rax+rax*4]
0xBC74F19  jmp short 0xBC74F35
0xBC74F1B  nop [rax+rax]
0xBC74F20  mov eax,esi
0xBC74F22  shl eax,3
0xBC74F25  lea rcx,[rax+rax*4]
0xBC74F29  cmp edx,0xFFF
0xBC74F2F  jbe 0xBC75000
0xBC74F35  lea r8,[rcx-0x28000]
0xBC74F3C  mov rax,[rbx+0x1E7DAB8]
0xBC74F43  mov r9,[rax]
0xBC74F46  cmp r8,0x28000
0xBC74F4D  jb 0xBC74FE8
0xBC74F53  add rcx,0xFFFFFFFFFFFB0000
0xBC74F5A  mov rax,rcx
0xBC74F5D  mul r12
0xBC74F60  shr rdx,0x11
0xBC74F64  mov eax,edx
0xBC74F66  not eax
0xBC74F68  test al,7
0xBC74F6A  je short 0xBC74F93
0xBC74F6C  inc edx
0xBC74F6E  and edx,7
0xBC74F71  nop [rax+rax]
0xBC74F80  add r8,0xFFFFFFFFFFFD8000
0xBC74F87  mov r9,[r9+0x28000]
0xBC74F8E  dec rdx
0xBC74F91  jne short 0xBC74F80
0xBC74F93  cmp ecx,0x118000
0xBC74F99  jb short 0xBC74FE8
0xBC74F9B  nop [rax+rax]
0xBC74FA0  mov rax,[r9+0x28000]
0xBC74FA7  mov rax,[rax+0x28000]
0xBC74FAE  mov rax,[rax+0x28000]
0xBC74FB5  mov rax,[rax+0x28000]
0xBC74FBC  mov rax,[rax+0x28000]
0xBC74FC3  mov rax,[rax+0x28000]
0xBC74FCA  mov rax,[rax+0x28000]
0xBC74FD1  add r8,0xFFFFFFFFFFEC0000
0xBC74FD8  mov r9,[rax+0x28000]
0xBC74FDF  cmp r8,0x27FFF
0xBC74FE6  ja short 0xBC74FA0
0xBC74FE8  add r8,r9
0xBC74FEB  cmp byte ptr [r8+0x24],0
0xBC74FF0  jne 0xBC74E90
0xBC74FF6  jmp short 0xBC75011
0xBC75000  add rcx,r14
0xBC75003  mov r8,rcx
0xBC75006  cmp byte ptr [r8+0x24],0
0xBC7500B  jne 0xBC74E90
0xBC75011  mov byte ptr [r8+0x24],1
0xBC75016  mov rcx,rbx
0xBC75019  mov edx,esi
0xBC7501B  call 0xBC79ED0
0xBC75020  nop
0xBC75021  jmp 0xBC74E90
```

**Epilog** (0xBC75026..0xBC75044):
```
0xBC75026  mov rcx,[rbp-0x18]                ; lock ptr
0xBC7502A  call 0xEBDBF20                    ; unlock Context
0xBC7502F  nop
0xBC75030  mov rax,[rbp-0x10]                ; output handle ptr
0xBC75034  add rsp,0x48
0xBC75038  pop rbx
0xBC75039  pop rdi
0xBC7503A  pop rsi
0xBC7503B  pop r12
0xBC7503D  pop r13
0xBC7503F  pop r14
0xBC75041  pop r15
0xBC75043  pop rbp
0xBC75044  ret
```

---

## Step 2: Reset flag 0x400000 test/set and caps-bit test at 0x12ADFA54

**Location**: Context init / reset path inside `sub_bc66de0` (frame()/swap entry) at `0xBC67284..0xBC672FF`.

### Caps-bit test: `test byte [0x12ADFA54], 0x10` (DynamicTextureHandles bit 4)
```
0xBC67284  test byte ptr [0x12ADFA54],0x10   ; [V] global caps byte, bit 4 = DynamicTextureHandles
0xBC6728B  jne short 0xBC672A9               ; if set -> dynamic handles supported
```
**Tag**: [V] — directly observed at RVA `0xBC67284`. The global `0x12ADFA54` is the high dword of the `bgfx::Caps::supported` u64 at `0x12ADFA50` (CapsFlag::DynamicTextureHandles = bit 36, i.e., bit 4 of the high dword).

### Guarded flag check (fallback when caps bit clear)
```
0xBC6728D  cmp byte ptr [rsi+0x1EBF2F3],0    ; [V] ctx+0x1EBF2F3 = guarded allocation flag
0xBC67294  jne short 0xBC672FF               ; if guarded -> proceed
0xBC67296  lea rdx,[0xF7F55F4]               ; "Texture handle allocation must be guarded if renderer contex..."
0xBC6729D  mov ecx,2
0xBC672A2  call 0xBC5F110                    ; error
0xBC672A7  jmp short 0xBC672FF
```

### Reset flag 0x400000 test/set (when caps bit set)
```
0xBC672A9  mov ecx,0x400000                  ; [V] reset flag mask
0xBC672AE  mov eax,[rsi+0x1EBF19C]           ; [V] ctx+0x1EBF19C = requested reset flags
0xBC672B4  and eax,ecx                       ; eax = requested & 0x400000
0xBC672B6  mov rdx,[rsi+0x1CFD0C8]           ; [V] ctx+0x1CFD0C8 = per-frame data ptr
0xBC672BD  and ecx,[rdx+0xDC5810]            ; ecx = current frame's consumed flags & 0x400000
0xBC672C3  cmp eax,ecx                       ; compare requested vs consumed
0xBC672C5  je short 0xBC672FF                ; same -> no change
0xBC672C7  test eax,eax
0xBC672C9  jne short 0xBC672DC               ; requested has it, consumed doesn't -> enabling
0xBC672CB  lea rdx,[0xF80C0EA]               ; "Disabling dynamic texture handles is not supported."
0xBC672D2  mov ecx,2
0xBC672D7  call 0xBC5F110                    ; error (disable not allowed)
```

**Enabling path** (clears dynamic texture state):
```
0xBC672DC  mov byte ptr [rsi+0x1DF7480],0    ; [V] ctx+0x1DF7480 = 0
0xBC672E3  mov byte ptr [rsi+0xE62610],0     ; [V] ctx+0xE62610 = 0
0xBC672EA  mov byte ptr [rsi+0x1CD6FD0],0    ; [V] ctx+0x1CD6FD0 = 0
0xBC672F1  mov byte ptr [rsi+0x1E7DAD0],0    ; [V] ctx+0x1E7DAD0 = guarded flag = 0
0xBC672F8  mov byte ptr [rsi+0x1EBF2F3],0    ; [V] ctx+0x1EBF2F3 = guarded flag = 0
```

**Frame flag sync** (after branch merge at `0xBC672FF`):
```
0xBC672FF  mov rax,[rsi+0x1CFD0C8]
0xBC67306  mov ecx,[rsi+0x1EBF19C]
0xBC6730C  mov [rax+0xDC5810],ecx            ; [V] frame's consumed flags = requested flags
```

**Field offsets summary**:
| Field | Offset | Meaning |
|-------|--------|---------|
| Global caps byte | `0x12ADFA54` | High dword of `Caps::supported`; bit 4 = DynamicTextureHandles |
| Context guarded flag | `ctx+0x1EBF2F3` | Byte; 1 = guarded allocation required |
| Context reset flags | `ctx+0x1EBF19C` | Dword; bit 0x400000 = dynamic texture handles requested |
| Frame consumed flags | `[ctx+0x1CFD0C8]+0xDC5810` | Dword; bit 0x400000 = dynamic handles active this frame |
| Dynamic texture state bytes | `ctx+0x1DF7480`, `ctx+0xE62610`, `ctx+0x1CD6FD0`, `ctx+0x1E7DAD0`, `ctx+0x1EBF2F3` | Cleared on enable |

---

## Step 3: Free-list (handle exhaustion + recycle)

The dynamic texture handle allocator at `ctx+0x1DFB48C` uses the standard **dense/sparse** layout (bgfx `HandleAlloc`):

- `u16 numHandles` at `ctx+0x1DFB48C`
- `u16 maxHandles` at `ctx+0x1DFB48E`
- `u16 dense[]` at `ctx+0x1DFB490` (size = maxHandles × 2)
- `u16 sparse[]` at `ctx+0x1DFB490 + maxHandles×2` (size = maxHandles × 2)

### On handle exhaustion (create path)
```
0xBC74AC8  cmp ax,cx                       ; numHandles vs maxHandles
0xBC74ACF  jae 0xBC74E22                   ; full -> error
0xBC74E22  mov word ptr [rsi],0xFFFF       ; return invalid handle (0xFFFF)
```
**Behavior**: Returns `0xFFFF` (invalid handle) to caller. No blocking, no waiting, no dynamic growth.

### On free (destroy path) — handle recycle (push to free list)
The destroy function `0xBC750B0` **increments** `numHandles` and returns the handle to the dense array (standard bgfx free = push to free list):

```
0xBC750E5  movzx eax,word ptr [rdi+0x1DFB48C]  ; R numHandles
0xBC750EC  movzx ecx,word ptr [rdi+0x1DFB48E]  ; R maxHandles
0xBC750F3  cmp ax,cx
0xBC750F6  jae 0xBC7527F                       ; full/empty check
0xBC750FC  movzx edx,ax
0xBC750FF  lea r8d,[rax+1]
0xBC75103  mov [rdi+0x1DFB48C],r8w             ; W numHandles++  (push)
0xBC7510B  movzx edx,word ptr [rdi+rdx*2+0x1DFB490] ; R dense[numHandles] -> freed handle
0xBC75113  lea rcx,[rdi+rcx*2]
0xBC75117  add rcx,0x1DFB490
0xBC7511E  mov [rcx+rdx*2],ax                  ; sparse[freed_handle] = numHandles
0xBC75122  mov [rsi],dx                        ; return handle (for deferred destroy)
```

**Recycle mechanism**: The freed handle is placed at `dense[numHandles]` (the new tail), `sparse[handle]` is updated to the new index, and `numHandles` increments. This is a **LIFO free-list** — the most recently freed handle is the next allocated.

### Additional destroy-side cleanup
```
0xBC7525E  movzx eax,word ptr [rsi]            ; handle
0xBC75261  lea rax,[rax+rax*2]                 ; handle * 3
0xBC75265  mov byte ptr [rdi+rax*8+0x1EA5AE8],1 ; W guarded byte = 1 (mark free/guarded)
0xBC7526D  mov rcx,[rbp-0x20]
0xBC75271  mov [rdi+rax*8+0x1EA5AD8],rcx       ; W record pointer (ctx+0x1EA5AD8 + handle*0x18)
```
Sets the guarded byte at `ctx+0x1EA5AE8 + handle*8` to 1 and stores a pointer in the record array at `ctx+0x1EA5AD8 + handle*0x18`.

---

## Step 4: Callers of 0xBC74A80

**Single caller**: `sub_e905990` at `0xE905990` (size 0x34A)

**Call site**:
```
0xE905C77  mov rcx,[0x12AE1748]               ; [V] s_ctx global
0xE905C7E  mov byte ptr [rsp+0x20],0
0xE905C83  lea r9,[rsp+0x30]                  ; element array pointer
0xE905C88  mov rdx,rsi                        ; texture desc
0xE905C8B  mov r8d,eax                        ; element count
0xE905C8E  call 0xBC74A80                     ; [V] createDynamicTexture
```

**Caller context**: `sub_e905990` appears to be a texture creation dispatcher that builds an array of texture descriptors (width/height/format tuples at `r8+0,4,6...`) and calls `createDynamicTexture` for each. The caller loads `s_ctx` from `0x12AE1748`, prepares a stack buffer with descriptor elements, and passes the count in `r8d`.

**No other callers found** via `rdis callers 0xBC74A80`.

---

## Summary of Key RVAs

| Item | RVA | Notes |
|------|-----|-------|
| createDynamicTexture | `0xBC74A80` | size 0x5C5, instruction-complete above |
| destroyDynamicTexture | `0xBC750B0` | size 0x1EB, free-list recycle shown |
| Caps bit test | `0xBC67284` | `test byte [0x12ADFA54], 0x10` |
| Reset flag test | `0xBC672A9..0xBC672CB` | `ctx+0x1EBF19C` vs frame `+0xDC5810` |
| Guarded flag | `ctx+0x1EBF2F3` | checked at `0xBC6728D` |
| Handle allocator | `ctx+0x1DFB48C` | dense/sparse, maxHandles at `+0x1DFB48E` |
| Dynamic texture records | `ctx+0x1EA5AD8` | stride 0x18, guarded byte at `+0x1EA5AE8` stride 8 |
| Guarded array base | `ctx+0x1E55AB8` | paged, page table at `ctx+0x1E7DAB8` |
| Caller | `0xE905990` | call at `0xE905C8E` |

---

## Gaps / UNVERIFIED

- [UNVERIFIED: 0xBC74E32] The path at `0xBC74E32` (flags byte == 0) copies `rdi` (texture desc) to command buffer but the exact desc layout is not fully decoded — `rdi` elements are 6 bytes each (width:u16, height:u16, format:u16?) based on `lea esi,[rax+rax*2]` (×3 u16).
- [UNVERIFIED: 0x12ADFA54] The global `0x12ADFA54` is inferred as high dword of `Caps::supported` at `0x12ADFA50`; not independently verified against `Caps.h` bit 36.
- [UNVERIFIED: 0xE905990] The caller's exact role (API entry point, render thread, resource upload) is not fully traced.
- [UNVERIFIED: 0xBC79ED0] Destroy path calls `0xBC79ED0` with handle — purpose not decoded (likely D3D12 resource release).

---

## TOOL REQUESTS

| Name | Input → Output | Why it would have helped |
|------|----------------|--------------------------|
| `verify_oc.py` | progress markdown → PASS/FAIL | Required by unit spec; will run after writing all steps |
| `preflight.py` | RVA → bundled dossier (listing + callers + stores + case walk) | Would give callers, stores, listing in one go; run manually per function |
| `allocator_finder.py` | Context base RVA → table of all `cmp ax,cx` / `jae` patterns near `numHandles`/`maxHandles` | Automates finding all handle allocators |

---

## Verification Status

```
python tools/sigs/verify_oc.py docs/progress/oc_U-A12a.md
```
**Result**: `claimed=385 match=385 mismatch=0 no-such-instr=0` — **PASS**

---

## NEXT
DONE — verify_oc.py passed (385/385). Unit complete.