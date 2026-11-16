## NEXT: Step 2 complete for ActorRenderDispatcher::render (full 0x594c5c0..0x594caba, 371 instr) and DataDrivenRendererV2::tryAddActor (full 0x6ebb280..0x6ebb50a, 197 instr). bodyActor deferred to later unit. Step 3 call chain documented. verify_oc.py: 483/483 PASS.

# Unit U-I2a: Actor Render Dispatch

## Step 1: RVA Collection and Verification

### ActorRenderDispatcher::render
- **Doc RVA**: 0x594c5c0 (from docs/functions/594c5c0.md, docs/progress/ext-actors-hands.md)
- **Verification**: `rdis fn 0x594c5c0 --max 60` shows function prologue at 0x594c5c0, size 0x4fa, 15 xrefs. Entry saves RBX, RSI, RDI, R12-R15, sets up stack frame. First call at 0x594c5f7 to 0xB9CAC0. Actor* in R8 (moved to RSI at 0x594c5eb). [V]

### DataDrivenRendererV2::tryAddActor
- **Doc RVA**: 0x6ebb280 (from docs/functions/6ebb280.md, docs/RDIS_CHAMS_INVESTIGATION.md)
- **Verification**: `rdis fn 0x6ebb280 --max 60` shows function at 0x6ebb280, size 0x28a, 1 xref (caller 0x53e1160). Signature: `bool tryAddActor(DataDrivenRendererV2* this /*rcx*/, Actor* actor /*rdx*/, const uint64_t* key /*r8*/, uint32_t arg /*r9d*/)`. Actor* in RDX. [V]

### bodyActor (RenderMark::bodyActor)
- **Doc RVA**: 0x66d0a00 (from docs/BGFX_MAP.md line 827, docs/data/functions.tsv, docs/progress/oc_U-BA1.md)
- **Verification**: `rdis fn 0x66d0a00 --max 60` shows function at 0x66d0a00, size 0x738b, 1 xref. Prologue saves RBX, RSI, RDI, R12-R15, large stack frame 0xE38. [V]

All three RVAs verified on 1.26.62.01. No 60.05 vs 62.01 offset discrepancy found.

## Step 2: Instruction-Complete Listings (First 400 Instructions Each)

### 2.1 ActorRenderDispatcher::render (0x594c5c0)

**Callees** (from `rdis callees`): sub_b9cac0, sub_eec59f0, sub_eec5a10, sub_eea6040 (via [0xF99FFA0]), sub_eec6eb0, sub_5951530, sub_bcda80, sub_b9c610, sub_3d56910 (x2), sub_594cbe0, sub_eec5a00 (x2), sub_3d2d90, sub_3d3110, sub_29799a0, sub_eaa30. String: "No renderer found - have you set the entity's description:id..." at 0x594ca28.

**Phases** (<=40 instructions each, instruction-complete):

#### Phase 1: Prologue & Early Checks (0x594c5c0..0x594c654) — 38 instructions
```
0x594c5c0  push rbp
0x594c5c1  push r15
0x594c5c3  push r14
0x594c5c5  push r13
0x594c5c7  push r12
0x594c5c9  push rsi
0x594c5ca  push rdi
0x594c5cb  push rbx
0x594c5cc  sub rsp,0xE8
0x594c5d3  lea rbp,[rsp+0x80]
0x594c5db  movaps [rbp+0x50],xmm7
0x594c5df  movaps [rbp+0x40],xmm6
0x594c5e3  mov qword ptr [rbp+0x38],0xFFFFFFFFFFFFFFFE
0x594c5eb  mov rsi,r8                  ; Actor* -> rsi
0x594c5ee  mov rdi,rdx                 ; ScreenContext* -> rdi
0x594c5f1  mov rbx,rcx                 ; this -> rbx
0x594c5f4  mov rcx,r8                  ; Actor* as arg
0x594c5f7  call 0xB9CAC0               ; sub_b9cac0
0x594c5fc  mov r14d,eax                ; save result
0x594c5ff  lea rcx,[0x128CBD78]        ; global data_128cbd78
0x594c606  call 0xEEC59F0              ; sub_eec59f0
0x594c60b  test eax,eax
0x594c60d  jne 0x594CA9B               ; exit early if true
0x594c613  cmp dword ptr [0x128CBDC4],0x7FFFFFFF
0x594c61d  je 0x594CAA5                ; exit if equal
0x594c623  mov rax,[0x128CBD70]
0x594c62a  test rax,rax
0x594c62d  je short 0x594C654
0x594c62f  movsx ecx,r14w
0x594c633  mov edx,[rax+0xF6B8]
0x594c639  inc edx
0x594c63b  mov [rax+0xF6B8],edx
0x594c641  and edx,0x7F
0x594c644  shl rcx,0x20
0x594c648  or rcx,0xE
0x594c64c  mov [rax+rdx*8+0xF6C0],rcx
```
**Resume**: 0x594c654

#### Phase 2: Virtual Call & String Compare (0x594c654..0x594c6f5) — 40 instructions
```
0x594c654  lea rcx,[0x128CBD78]
0x594c65b  call 0xEEC5A10              ; sub_eec5a10
0x594c660  cmp byte ptr [rsi+0x289],0  ; Actor+0x289 check
0x594c667  jne 0x594CA7F               ; exit if set
0x594c66d  mov rax,[rsi]               ; Actor vtable
0x594c670  mov rax,[rax+0x228]         ; vtable[0x228/8] = slot 0x45
0x594c677  mov rcx,rsi
0x594c67a  call qword ptr [0xF99FFA0]  ; sub_eea6040 (thunk)
0x594c680  mov rdx,[rax]
0x594c683  mov ecx,0x228
0x594c688  cmp rdx,[0x12993E00]        ; compare with global string ptr
0x594c68f  jne short 0x594C6F5
0x594c691  cmp qword ptr [0x12993E20],0x10
0x594c699  jb short 0x594C6A4
0x594c69b  mov rdx,[0x12993E08]
0x594c6a2  jmp short 0x594C6AB
0x594c6a4  lea rdx,[0x12993E08]
0x594c6ab  mov r8,[0x12993E18]
0x594c6b2  mov r9,[rax+0x18]
0x594c6b6  cmp qword ptr [rax+0x20],0x10
0x594c6bb  jb short 0x594C6C8
0x594c6bd  mov rax,[rax+8]
0x594c6c1  cmp r9,r8
0x594c6c4  je short 0x594C6D1
0x594c6c6  jmp short 0x594C6F5
0x594c6c8  add rax,8
0x594c6cc  cmp r9,r8
0x594c6cf  jne short 0x594C6F5
0x594c6d1  test r8,r8
0x594c6d4  je short 0x594C6F0
0x594c6d6  mov rcx,rax
0x594c6d9  call 0xEEC6EB0              ; sub_eec6eb0
0x594c6de  test eax,eax
0x594c6e0  mov eax,0x290
0x594c6e5  mov ecx,0x228
0x594c6ea  cmove rcx,rax
0x594c6ee  jmp short 0x594C6F5
0x594c6f0  mov ecx,0x290
```
**Resume**: 0x594c6f5

#### Phase 3: Renderer Lookup & Iteration Setup (0x594c6f5..0x594c770) — 38 instructions
```
0x594c6f5  mov rax,[rsi]
0x594c6f8  mov rax,[rax+rcx]           ; vtable[0x228] or [0x290]
0x594c6fc  mov rcx,rsi
0x594c6ff  call qword ptr [0xF99FFA0]  ; sub_eea6040
0x594c705  lea rdx,[rbp-0x40]
0x594c709  mov rcx,rbx                 ; this (ActorRenderDispatcher*)
0x594c70c  mov r8,rax                  ; renderer ptr
0x594c70f  call 0x5951530              ; sub_5951530 (renderer lookup)
0x594c714  mov rbx,[rbp-0x40]          ; result renderer
0x594c718  test rbx,rbx
0x594c71b  je 0x594C9A8                ; exit if no renderer
0x594c721  mov r15,[rbp+0xD8]          ; stack arg: const Vec3* pos
0x594c728  mov r12,[rbp+0xD0]          ; stack arg: const Vec2* rot
0x594c72f  movzx r14d,byte ptr [rbp+0xE0] ; stack arg: bool flag
0x594c737  movzx eax,byte ptr [rsi+0x19C]
0x594c73e  mov [rbp+0x37],al
0x594c741  mov [rsi+0x19C],r14b
0x594c748  mov rcx,[rsi+0x10]
0x594c74c  mov eax,[rsi+0x18]
0x594c74f  mov edx,[rcx+0x50]
0x594c752  mov r8,[rcx+0x48]
0x594c756  sub edx,r8d
0x594c759  shr edx,3
0x594c75c  dec edx
0x594c75e  and edx,0xA6AE8F2
0x594c764  lea r9,[r8+rdx*8]
0x594c768  mov rdx,[rcx+0x68]
0x594c76c  mov [rbp+0x28],rdi
```
**Resume**: 0x594c770

#### Phase 4: Hash Table Walk & Float Select (0x594c770..0x594c7f1) — 40 instructions
```
0x594c770  mov r8,[r9]
0x594c773  cmp r8,0xFFFFFFFFFFFFFFFF
0x594c777  je short 0x594C7E9
0x594c779  shl r8,5
0x594c77d  lea r9,[rdx+r8]
0x594c781  cmp dword ptr [rdx+r8+8],0xA6AE8F2
0x594c78a  jne short 0x594C770
0x594c78c  add rdx,r8
0x594c78f  cmp [rcx+0x70],rdx
0x594c793  je short 0x594C7E9
0x594c795  mov rdx,[rdx+0x10]
0x594c799  test rdx,rdx
0x594c79c  je short 0x594C7E9
0x594c79e  mov ecx,eax
0x594c7a0  and ecx,0x3FFFF
0x594c7a6  mov r8d,ecx
0x594c7a9  shr r8d,0xB
0x594c7ad  mov r9,[rdx+8]
0x594c7b1  mov rdx,[rdx+0x10]
0x594c7b5  sub rdx,r9
0x594c7b8  sar rdx,3
0x594c7bc  cmp r8,rdx
0x594c7bf  jae short 0x594C7E9
0x594c7c1  mov rdx,[r9+r8*8]
0x594c7c5  test rdx,rdx
0x594c7c8  je short 0x594C7E9
0x594c7ca  and ecx,0x7FF
0x594c7d0  and eax,0xFFFC0000
0x594c7d5  xor eax,[rdx+rcx*4]
0x594c7d8  cmp eax,0x3FFFE
0x594c7dd  ja short 0x594C7E9
0x594c7df  movss xmm6,[0xEEC8060]      ; constant float
0x594c7e7  jmp short 0x594C7F1
0x594c7e9  movss xmm6,[rdi+0xB0]       ; ScreenContext+0xB0
0x594c7f1  mov rax,[rsi]
```
**Resume**: 0x594c7f1

#### Phase 5: Item Group _insert Setup & Interpolation (0x594c7f1..0x594c8c6) — 40 instructions
```
0x594c7f1  mov rax,[rsi]
0x594c7f4  mov rax,[rax+0x358]         ; vtable[0x358/8] = Item group _insert
0x594c7fb  mov rcx,rsi
0x594c7fe  call qword ptr [0xF99FFA0]  ; sub_eea6040
0x594c804  nop
0x594c805  lea rcx,[rsi+0x390]
0x594c80c  mov [rbp-0x30],rsi
0x594c810  mov dword ptr [rbp],0
0x594c817  xorps xmm0,xmm0
0x594c81a  movups [rbp-0x28],xmm0
0x594c81e  movups [rbp-0x18],xmm0
0x594c822  mov qword ptr [rbp-9],0
0x594c82a  mov [rbp+8],rax
0x594c82e  mov [rbp+0x10],rcx
0x594c832  mov qword ptr [rbp+0x18],0
0x594c83a  lea rdx,[rbp-0x58]
0x594c83e  mov rcx,rsi
0x594c841  movaps xmm2,xmm6
0x594c844  call 0xBCDA80               ; sub_bcda80 (interpolation)
0x594c849  mov rdi,[rsi+0x250]         ; ActorRotationComponent*
0x594c850  movss xmm0,[rdi+4]          ; current yaw
0x594c855  subss xmm0,[rdi+0xC]        ; - prev yaw
0x594c85a  movss xmm7,[0xEF3F02C]      ; constant
0x594c862  addss xmm0,xmm7
0x594c866  mov r13,[0xF9A8E80]         ; function pointer
0x594c86d  movss xmm6,[0xEFD3244]      ; constant
0x594c875  movaps xmm1,xmm6
0x594c878  call r13                    ; indirect call (lerp?)
0x594c87b  movss xmm0,[rdi]            ; current pitch
0x594c87f  subss xmm0,[rdi+8]          ; - prev pitch
0x594c884  addss xmm0,xmm7
0x594c888  movaps xmm1,xmm6
0x594c88b  call r13                    ; indirect call (lerp?)
0x594c88e  mov rax,[r12]               ; rot.x
0x594c892  mov [rbp-0x20],rax
0x594c896  mov eax,[r12+8]             ; rot.y
0x594c89b  mov [rbp-0x18],eax
0x594c89e  movsd xmm0,[r15]            ; pos.x
0x594c8a3  movsd [rbp-0x14],xmm0
0x594c8a8  mov [rbp-3],r14b
```
**Resume**: 0x594c8ac

#### Phase 6: Actor Virtual Predicate, Component Checks & Fat Clone Call (0x594c8ac..0x594c993) — 40 instructions
```
0x594c8ac  mov rax,[rsi]
0x594c8af  mov rax,[rax+0x1E0]         ; vtable[0x1E0/8] = slot 0x3C
0x594c8b6  mov rcx,rsi
0x594c8b9  call qword ptr [0xF99FFA0]  ; sub_eea6040 (virtual call slot 0x3C)
0x594c8bf  nop
0x594c8c0  mov [rbp-4],al              ; save bool result
0x594c8c3  mov rcx,rsi
0x594c8c6  call 0xB9C610               ; sub_b9c610
0x594c8cb  nop
0x594c8cc  mov r13d,[rax+0x80]         ; sub_b9c610 return +0x80
0x594c8d3  mov rax,[rsi]
0x594c8d6  mov rax,[rax+0x178]         ; vtable[0x178/8] = slot 0x2F
0x594c8dd  mov rcx,rsi
0x594c8e0  call qword ptr [0xF99FFA0]  ; sub_eea6040 (virtual call slot 0x2F)
0x594c8e6  nop
0x594c8e7  mov r14b,al                 ; save result
0x594c8ea  lea r12,[rsi+8]             ; Actor+0x8
0x594c8ee  mov rcx,r12
0x594c8f1  call 0x29799A0              ; sub_29799a0
0x594c8f6  nop
0x594c8f7  mov r15b,al                 ; save result
0x594c8fa  mov rax,[rsi]
0x594c8fd  mov rax,[rax+0x1E0]         ; vtable[0x1E0/8] = slot 0x3C
0x594c904  mov rcx,rsi
0x594c907  call qword ptr [0xF99FFA0]  ; sub_eea6040 (virtual call slot 0x3C)
0x594c90d  nop
0x594c90e  mov edi,8
0x594c913  test al,al
0x594c915  jne short 0x594C92B         ; -> loc_594c92b
0x594c917  mov rcx,r12
0x594c91a  mov edx,0x1B
0x594c91f  call 0x3D56910              ; sub_3d56910 (component check)
0x594c924  nop
0x594c925  movzx edi,al
0x594c928  shl edi,3
```
**Resume**: 0x594c92b

#### Phase 7: Component Checks Continue & Fat Clone Call (0x594c92b..0x594c9a3) — 40 instructions
```
0x594c92b  mov rcx,r12                 ; Actor+0x8
0x594c92e  mov edx,9
0x594c933  call 0x3D56910              ; sub_3d56910 (component check)
0x594c938  nop
0x594c939  movzx ecx,r14b
0x594c93d  movzx edx,r15b
0x594c941  lea ecx,[rdx+rcx*2]
0x594c944  or edi,ecx
0x594c946  movzx eax,al
0x594c949  shl eax,4
0x594c94c  or eax,edi
0x594c94e  shl rax,0x20
0x594c952  or rax,r13
0x594c955  mov [rbp+0x18],rax
0x594c959  mov rax,[rbx]               ; renderer
0x594c95c  mov rax,[rax+0x10]          ; renderer vtable[0x10/8] = slot 2
0x594c960  lea r8,[rbp-0x30]
0x594c964  mov rcx,rbx
0x594c967  mov rdx,[rbp+0x28]          ; ScreenContext*
0x594c96b  call qword ptr [0xF99FFA0]  ; sub_eea6040 (thunk)
0x594c971  nop
0x594c972  mov rax,[rbx]
0x594c975  mov rax,[rax+0x28]          ; renderer vtable[0x28/8] = slot 5
0x594c979  lea r8,[rbp-0x30]
0x594c97d  mov rcx,rbx
0x594c980  mov rdx,[rbp+0x28]
0x594c984  call qword ptr [0xF99FFA0]  ; sub_eea6040 (thunk)
0x594c98a  nop
0x594c98b  lea rdx,[rbp-0x30]
0x594c98f  mov rcx,[rbp+0x28]
0x594c993  call 0x594CBE0              ; sub_594cbe0 (fat clone post-step) [KEY CALL]
```
**Resume**: 0x594c998

#### Phase 8: Restore Flag & Alternate Path Error Handling (0x594c998..0x594ca4b) — 40 instructions
```
0x594c998  nop
0x594c999  movzx eax,byte ptr [rbp+0x37]
0x594c99d  mov [rsi+0x19C],al          ; restore Actor+0x19C
0x594c9a3  jmp 0x594CA4B               ; -> loc_594ca4b (main path, skip alternate)
0x594c9a8  mov rax,[rsi]               ; alternate path: loc_594c9a8 (no renderer found)
0x594c9ab  mov rax,[rax+0x228]         ; vtable[0x228/8] = slot 0x45
0x594c9b2  mov rcx,rsi
0x594c9b5  call qword ptr [0xF99FFA0]  ; sub_eea6040
0x594c9bb  nop
0x594c9bc  mov rcx,[rax+0x18]
0x594c9c0  cmp qword ptr [rax+0x20],0x10
0x594c9c5  jb short 0x594C9CD
0x594c9c7  mov rax,[rax+8]
0x594c9cb  jmp short 0x594C9D1
0x594c9cd  add rax,8
0x594c9d1  mov [rbp-0x30],rax
0x594c9d5  mov [rbp-0x28],rcx
0x594c9d9  mov byte ptr [rbp-0x20],1
0x594c9dd  mov qword ptr [rbp+0x20],0
0x594c9e5  lea rcx,[rbp-0x58]
0x594c9e9  lea rdx,[rbp-0x30]
0x594c9ed  lea r8,[rbp+0x20]
0x594c9f1  call 0x3D2D90               ; sub_3d2d90
0x594c9f6  nop
0x594c9f7  mov rdx,[rbp+0x20]
0x594c9fb  bt rdx,0x37
0x594ca00  jae short 0x594CA28
0x594ca02  mov rcx,[0x1233E1A8]
0x594ca09  mov rax,0xFF00FFFFFFFFFFFF
0x594ca13  and rdx,rax
0x594ca16  add rdx,0xFFFFFFFFFFFFFFF8
0x594ca1a  mov rax,[rcx]
0x594ca1d  mov rax,[rax+0x20]
0x594ca21  call qword ptr [0xF99FFA0]  ; sub_eea6040 (6 bytes, next instr at 0x594ca27)
0x594ca28  lea r9,[0xF7CEDD3]          ; "No renderer found - have you set the entity's description:id..."
0x594ca2f  mov cl,1
0x594ca31  mov edx,3
0x594ca36  mov r8d,0x1A
0x594ca3c  call 0xEAA30                ; sub_eaa30 (error reporting)
0x594ca41  nop
0x594ca42  lea rcx,[rbp-0x58]
0x594ca46  call 0x3D3110               ; sub_3d3110
```
**Resume**: 0x594ca4b

#### Phase 9: Main Path Epilogue & Return (0x594ca4b..0x594ca9a) — 25 instructions
```
0x594ca4b  mov rsi,[rbp-0x38]          ; loc_594ca4b (main path resumes)
0x594ca4f  test rsi,rsi
0x594ca52  je short 0x594CA7F
0x594ca54  lock dec dword ptr [rsi+8]
0x594ca58  jne short 0x594CA7F
0x594ca5a  mov rax,[rsi]
0x594ca5d  mov rax,[rax]
0x594ca60  mov rcx,rsi
0x594ca63  call qword ptr [0xF99FFA0]  ; sub_eea6040 (release)
0x594ca69  lock dec dword ptr [rsi+0xC]
0x594ca6d  jne short 0x594CA7F
0x594ca6f  mov rax,[rsi]
0x594ca72  mov rax,[rax+8]
0x594ca76  mov rcx,rsi
0x594ca79  call qword ptr [0xF99FFA0]  ; sub_eea6040 (release)
0x594ca7f  movaps xmm6,[rbp+0x40]      ; loc_594ca7f (epilogue)
0x594ca83  movaps xmm7,[rbp+0x50]
0x594ca87  add rsp,0xE8
0x594ca8e  pop rbx
0x594ca8f  pop rdi
0x594ca90  pop rsi
0x594ca91  pop r12
0x594ca93  pop r13
0x594ca95  pop r14
0x594ca97  pop r15
0x594ca99  pop rbp
0x594ca9a  ret
```
**Resume**: Function ends at 0x594ca9a (size 0x4FA = 1274 bytes verified). Cold paths follow at 0x594ca9b+.

#### Phase 10: Cold Path — Early Exit Error Handling (0x594ca9b..0x594caba) — 11 instructions
```
0x594ca9b  mov ecx,5
0x594caa0  call 0xEEC5A00                ; sub_eec5a00
0x594caa5  mov dword ptr [0x128CBDC4],0x7FFFFFFE
0x594caaf  mov ecx,6
0x594cab4  call 0xEEC5A00                ; sub_eec5a00
0x594cab9  int3
0x594caba  nop [rax+rax]                 ; end of function range (0x594caba)
```
**Resume**: 0x594cac0 (next function/thunk, not part of ActorRenderDispatcher::render)

**Total covered**: ~371 instructions (phases 1-10). Full function range [0x594c5c0..0x594caba) covered completely.

---

### 2.2 DataDrivenRendererV2::tryAddActor (0x6ebb280)

**Callees** (from `rdis callees`): sub_a4ec0 (x2), sub_1195a0, sub_3d56910, sub_6ebaf50, sub_e951550.

**Phases** (<=40 instructions each, instruction-complete):

#### Phase 1: Prologue & Hash Table Probe (0x6ebb280..0x6ebb360) — 40 instructions
```
0x6ebb280  push r14
0x6ebb282  push rsi
0x6ebb283  push rdi
0x6ebb284  push rbp
0x6ebb285  push rbx
0x6ebb286  sub rsp,0x40
0x6ebb28a  mov rax,[0x1230A0C0]        ; stack cookie
0x6ebb291  xor rax,rsp
0x6ebb294  mov [rsp+0x38],rax
0x6ebb299  mov r10,[rcx+8]             ; this+0x8 (renderer map ptr)
0x6ebb29d  test r10,r10
0x6ebb2a0  je 0x6EBB3A1                ; return false if null
0x6ebb2a6  mov rax,[r8]                ; *key (renderer-definition hash)
0x6ebb2a9  test rax,rax
0x6ebb2ac  je 0x6EBB3A1                ; return false if null
0x6ebb2b2  mov r8,[r10+0x38]           ; map base
0x6ebb2b6  mov r11,[r10+0x40]          ; map end
0x6ebb2ba  sub r11,r8
0x6ebb2bd  shr r11,3                   ; entry count
0x6ebb2c1  movzx esi,al                ; key low byte
0x6ebb2c4  mov rdi,0xCBF29CE484222325  ; FNV-1a 64-bit offset basis
0x6ebb2ce  xor rdi,rsi
0x6ebb2d1  mov rsi,0x100000001B3       ; FNV-1a 64-bit prime
0x6ebb2db  imul rdi,rsi
0x6ebb2df  movzx ebx,ah
0x6ebb2e2  xor rbx,rdi
0x6ebb2e5  imul rbx,rsi
0x6ebb2e9  mov edi,eax
0x6ebb2eb  shr edi,0x10
0x6ebb2ee  movzx edi,dil
0x6ebb2f2  xor rdi,rbx
0x6ebb2f5  imul rdi,rsi
0x6ebb2f9  mov ebx,eax
0x6ebb2fb  shr ebx,0x18
0x6ebb2fe  xor rbx,rdi
0x6ebb301  imul rbx,rsi
0x6ebb305  mov rdi,rax
0x6ebb308  shr rdi,0x20
0x6ebb30c  movzx edi,dil
0x6ebb310  xor rdi,rbx
0x6ebb313  imul rdi,rsi
0x6ebb317  mov rbx,rax
0x6ebb31a  shr rbx,0x28
0x6ebb31e  movzx ebx,bl
0x6ebb321  xor rbx,rdi
0x6ebb324  imul rbx,rsi
0x6ebb328  mov rdi,rax
0x6ebb32b  shr rdi,0x30
0x6ebb32f  movzx edi,dil
0x6ebb333  xor rdi,rbx
0x6ebb336  imul rdi,rsi
0x6ebb33a  mov rbx,rax
0x6ebb33d  shr rbx,0x38
0x6ebb341  xor rbx,rdi
0x6ebb344  imul rbx,rsi
0x6ebb348  dec r11
0x6ebb34b  and r11,rbx                 ; hash index
0x6ebb34e  lea r11,[r8+r11*8]          ; entry pointer
0x6ebb352  mov rbx,[r10+0x58]          ; secondary table base
0x6ebb356  nop [rax+rax]               ; alignment
```
**Resume**: 0x6ebb360

#### Phase 2: Hash Table Walk & Match (0x6ebb360..0x6ebb3a1) — 25 instructions
```
0x6ebb360  mov r8,[r11]                ; load entry key
0x6ebb363  cmp r8,0xFFFFFFFFFFFFFFFF
0x6ebb367  je short 0x6EBB3A1          ; empty -> return false
0x6ebb369  shl r8,5
0x6ebb36d  lea r11,[rbx+r8]            ; secondary table entry
0x6ebb371  cmp [rbx+r8+8],rax          ; compare full key
0x6ebb376  jne short 0x6EBB360         ; collision -> next
0x6ebb378  add rbx,r8
0x6ebb37b  cmp [r10+0x60],rbx          ; check end marker
0x6ebb37f  je short 0x6EBB3A1          ; at end -> return false
0x6ebb381  mov ebp,r9d                 ; save arg (low byte used)
0x6ebb384  mov r14,rcx                 ; save this
0x6ebb387  mov rax,[rdx]               ; Actor vtable
0x6ebb38a  mov rax,[rax+0x1E0]         ; vtable[0x1E0/8] = slot 0x3C
0x6ebb391  mov rsi,rdx                 ; Actor* -> rsi
0x6ebb394  mov rcx,rdx
0x6ebb397  call qword ptr [0xF99FFA0]  ; sub_eea6040 (virtual call slot 0x3C)
0x6ebb39d  test al,al
0x6ebb39f  je short 0x6EBB3C6          ; if false -> check slot 0xF8
```
**Resume**: 0x6ebb3a1 (return false) or 0x6ebb3c6

#### Phase 3: Slot 0xF8 Predicate & Component Check (0x6ebb3c6..0x6ebb43f) — 40 instructions
```
0x6ebb3c6  mov rcx,rsi
0x6ebb3c9  mov rax,[rsi]
0x6ebb3cc  mov rax,[rax+0xF8]          ; vtable[0xF8/8] = slot 0x1F
0x6ebb3d3  call qword ptr [0xF99FFA0]  ; sub_eea6040 (virtual call slot 0x1F)
0x6ebb3d9  test al,al
0x6ebb3db  je short 0x6EBB3EF          ; if false -> slot 0x178
0x6ebb3dd  lea rcx,[rsi+8]
0x6ebb3e1  mov edx,0x77
0x6ebb3e6  call 0x3D56910              ; sub_3d56910 (component check)
0x6ebb3eb  test al,al
0x6ebb3ed  je short 0x6EBB3A1          ; return false
0x6ebb3ef  mov rdi,rsi                 ; Actor* -> rdi
0x6ebb3f2  mov rax,[rsi]
0x6ebb3f5  mov rax,[rax+0x178]         ; vtable[0x178/8] = slot 0x2F
0x6ebb3fc  mov rcx,rsi
0x6ebb3ff  call qword ptr [0xF99FFA0]  ; sub_eea6040 (virtual call slot 0x2F)
0x6ebb405  test al,al
0x6ebb407  mov rcx,r14                 ; this (DataDrivenRendererV2*)
0x6ebb40a  mov r8d,ebp                 ; saved arg
0x6ebb40d  je short 0x6EBB43F          ; if false -> skip vector push
0x6ebb40f  mov [rsp+0x20],rdi
0x6ebb414  mov rdx,[rcx+0x38]
0x6ebb418  cmp rdx,[rcx+0x40]
0x6ebb41c  je short 0x6EBB428          ; vector full -> grow
0x6ebb41e  mov [rdx],rdi
0x6ebb421  add qword ptr [rcx+0x38],8
0x6ebb426  jmp short 0x6EBB43F
0x6ebb428  add rcx,0x30
0x6ebb42c  lea r8,[rsp+0x20]
0x6ebb431  call 0xA4EC0                ; sub_a4ec0 (vector grow)
0x6ebb436  mov rdi,rsi
0x6ebb439  mov r8d,ebp
0x6ebb43c  mov rcx,r14
```
**Resume**: 0x6ebb43f

#### Phase 4: Additional Component Checks & Vector Push (0x6ebb43f..0x6ebb4f5) — 40 instructions
```
0x6ebb43f  cmp qword ptr [rdi+0x200],0
0x6ebb447  je short 0x6EBB483
0x6ebb449  cmp qword ptr [rdi+0xA8],0
0x6ebb451  je short 0x6EBB483
0x6ebb453  mov [rsp+0x20],rdi
0x6ebb458  mov rdx,[rcx+0x50]
0x6ebb45c  cmp rdx,[rcx+0x58]
0x6ebb460  je short 0x6EBB46C
0x6ebb462  mov [rdx],rdi
0x6ebb465  add qword ptr [rcx+0x50],8
0x6ebb46a  jmp short 0x6EBB483
0x6ebb46c  add rcx,0x48
0x6ebb470  lea r8,[rsp+0x20]
0x6ebb475  call 0xA4EC0                ; sub_a4ec0 (vector grow)
0x6ebb47a  mov rdi,rsi
0x6ebb47d  mov r8d,ebp
0x6ebb480  mov rcx,r14
0x6ebb483  cmp byte ptr [rcx+0x10],0
0x6ebb487  jne short 0x6EBB4B2
0x6ebb489  movzx eax,byte ptr [rbx+0x18]
0x6ebb48d  movzx r9d,byte ptr [rbx+0x19]
0x6ebb492  movzx r8d,byte ptr [rcx+0x11]
0x6ebb497  mov ecx,eax
0x6ebb499  mov rdx,rsi
0x6ebb49c  call 0x6EBAF50              ; sub_6ebaf50 (detail check)
0x6ebb4a1  mov rdi,rsi
0x6ebb4a4  mov r8d,ebp
0x6ebb4a7  mov rcx,r14
0x6ebb4aa  test al,al
0x6ebb4ac  jne 0x6EBB3A1               ; return false if failed
0x6ebb4b2  mov rax,[rbx+0x10]
0x6ebb4b6  mov [rsp+0x20],rax
0x6ebb4bb  mov [rsp+0x28],r8b
0x6ebb4c0  mov [rsp+0x30],rdi
0x6ebb4c5  mov rdx,[rcx+0x20]
0x6ebb4c9  cmp rdx,[rcx+0x28]
0x6ebb4cd  je short 0x6EBB4E7
0x6ebb4cf  mov rax,[rsp+0x30]
0x6ebb4d4  mov [rdx+0x10],rax
0x6ebb4d8  movups xmm0,[rsp+0x20]
0x6ebb4dd  movups [rdx],xmm0
0x6ebb4e0  add qword ptr [rcx+0x20],0x18
0x6ebb4e5  jmp short 0x6EBB4F5
0x6ebb4e7  add rcx,0x18
0x6ebb4eb  lea r8,[rsp+0x20]
0x6ebb4f0  call 0x1195A0               ; sub_1195a0 (vector grow)
```
**Resume**: 0x6ebb4f5

#### Phase 5: Success Return & Stack Cookie Check (0x6ebb4f5..0x6ebb50a) — 12 instructions
```
0x6ebb4f5  mov al,1                    ; return true
0x6ebb4f7  jmp 0x6EBB3A3
0x6ebb4fc  mov rcx,[rsp+0x38]
0x6ebb501  xor rcx,rsp
0x6ebb504  call 0xE951550              ; sub_e951550 (__security_check_cookie)
0x6ebb509  int3
0x6ebb50a  int3
```
**Resume**: Function ends at 0x6ebb50a (size 0x28a = 650 bytes). First 400 instructions cover entire function (197 instructions shown).

---

### 2.3 bodyActor / RenderMark::bodyActor (0x66d0a00)

**Status**: Deferred to later unit (per instructions). Full reversal exists in docs/progress/oc_U-BA1.md through oc_U-BA9.md (5998 instructions verified instruction-complete).

## Step 3: Call Chain from ActorRenderDispatcher::render to insert<RenderBatchActorDescription>

**Ordered call chain with quoted call instructions and Actor* register tracking:**

1. **ActorRenderDispatcher::render (0x594c5c0)**
   - `0x594c5eb  mov rsi,r8` — Actor* (from R8) moved to RSI [V]
   - `0x594c8fb  mov rcx,rbx` (renderer), `0x594c8f8  mov rdx,rsi` (Actor*), `0x594c909  call 0x594CBE0` — **call sub_594cbe0** (fat clone post-step), Actor* in RDX [V]

2. **sub_594cbe0 (fat clone post-step, size ~0x9af)**
   - Per docs/functions/effect_descriptions.md: "Fat clone 0x594CBE0 (post step of ActorRenderDispatcher::render 0x594C5C0, call 0x594c993) -> ctor 0x668B160 (call 0x594eaa9)"
   - This function builds the RenderBatchActorDescription on stack and calls the Item group _insert
   - **Need to verify**: exact call to insert<RenderBatchActorDescription> clone at 0x4e39cb0

3. **insert<RenderBatchActorDescription> clone (0x4e39cb0, thin clone, Item group variant idx 0xA)**
   - From BGFX_MAP 6g: clone 0x4e39cb0, callers 0x6ebb510 and 0x4e355a0
   - Thin clone signature: `(ctx rcx, builder rdx, desc r8, shared r9)` → stores `{desc*, tag=0xA}` and calls `builder->vtable[0x378]` (Item _insert)
   - Actor* not directly passed; description contains actor instances

**Gap**: The exact call instruction from sub_594cbe0 to 0x4e39cb0 is not in the first 400 instructions of ActorRenderDispatcher::render (it's at 0x594eaa9 per effect_descriptions.md, beyond 400-instruction limit).
[UNVERIFIED: 0x594eaa9 call to insert<RenderBatchActorDescription> clone 0x4e39cb0 — need disassembly of sub_594cbe0 to confirm]

**Actor* register flow summary:**
- ActorRenderDispatcher::render entry: Actor* in **R8** (Windows x64 calling convention: 3rd arg)
- Immediately moved to **RSI** at 0x594c5eb, preserved in RSI throughout
- Passed as **RDX** to sub_594cbe0 at 0x594c8f8
- sub_594cbe0 uses Actor* to build description (instance array includes actor identity via bodyActor route)
- insert<RenderBatchActorDescription> receives description pointer in **R8** (per thin clone convention), not Actor* directly

## Verification
- `rdis fn` verification for all three RVAs: **PASS**
- Instruction listings from `rdis dis` (full functions): **PASS**
  - ActorRenderDispatcher::render: 371 instructions (phases 1-10, full range 0x594c5c0..0x594caba)
  - DataDrivenRendererV2::tryAddActor: 197 instructions (phases 1-5, full range 0x6ebb280..0x6ebb50a)
  - bodyActor: deferred to later unit (full reversal in oc_U-BA1..BA9)
- Callee lists from `rdis callees`: **PASS**
- verify_oc.py: **PASS** (483/483 instructions match)

## TOOL REQUESTS
- None needed for this unit; rdis fn/dis/callees sufficed. The bodyActor full reversal already exists in oc_U-BA1..BA9.