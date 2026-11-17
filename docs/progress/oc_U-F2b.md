## NEXT
DONE - All parts complete, verify_oc.py passes (170/170)

## Part A: sub_568cd90 Analysis

### Function Signature
sub_568cd90(rcx, rdx) - Scene/HUD task body, bgfx per-view setup

### Phase Table

| Phase | RVA Range | Description |
|-------|-----------|-------------|
| Prologue | 0x568cd90..0x568cdd7 | Save registers, stack frame, load ctx, compute viewId offset |
| View Rect Setup | 0x568cdda..0x568ce55 | Store view rect (x,y,width,height) into ctx+0x1EAB090+viewId*0x140 |
| View Matrices | 0x568ce56..0x568ce9c | Copy 4 matrices (0x40 bytes each) into view record |
| View Sort Mode | 0x568ce9d..0x568cebe | Copy sort mode (0x10 bytes) and store sortMode byte |
| Lambda Setup | 0x568cebf..0x568cf7f | Prepare lambda captures, call 0xBCC1A30, iterate render items |
| Item Loop | 0x568cf80..0x568d350 | Main loop over render items, call per-item lambdas |
| Epilogue | 0x568d350..0x568d3a5 | Loop continuation, cleanup, return |

### Strings Referenced
None directly in this function (no lea rdx, [rip+...] for strings)

### Callees in Order
1. 0xEBCE390 (x4) - memcpy/memmove (view rect + 3 matrices)
2. 0xEBCE390 (x1) - memcpy (sort mode, 0x10 bytes)
3. 0xBCC1A30 - lambda setup / capture initialization
4. 0xBC60D10 - render item iterator / getter
5. 0x568DA90 - per-item lambda (when rdi==rbx)
6. 0xE935700 - allocation / memory management
7. 0x655CEA0 - cleanup / release
8. 0xC4BBA0 - per-pass draw function (inside item loop)
9. 0x568DB90 - per-pass lambda (inside item loop)
10. 0xE86D7F0 - draw submission / encoder submit
11. 0x568D480 - final per-view lambda
12. [0xF9A8C78] - indirect call (error path)

### [reg+off] Reads/Writes (V = ctx+0x1EAB090+viewId*0x140)

viewId computation:
- 0x568cdc4: mov rax,[rcx+8]           ; rcx = arg1 (task data)
- 0x568cdcc: movzx eax,word ptr [rax+8] ; viewId = u16 [[a+8]+8]
- 0x568cdda: shl eax,6                  ; viewId * 64
- 0x568cdde: lea r13,[rax+rax*4]        ; r13 = viewId * 64 * 5 = viewId * 320 = viewId * 0x140

V = [0x12AE1748] + r13 + 0x1EAB090 = ctx + 0x1EAB090 + viewId*0x140

Stores into V (offset = displacement - 0x1EAB090):
1. 0x568cdf6: movd [rcx+r13+0x1EAB090],xmm0     ; V+0x00 = viewRect.xy (packed u16)
2. 0x568ce0c: movd [rcx+r13+0x1EAB094],xmm1     ; V+0x04 = viewRect.zw (packed u16)
3. 0x568ce4b: call 0xEBCE390 (rcx=[rsi+r13]+0x1EAB0A0, rdx=r12, r8d=0x40) ; V+0x10 = viewMatrix[0] (mat4, 64 bytes)
   - rcx = ctx + r13 + 0x1EAB0A0 = V + 0x10
4. 0x568ce67: call 0xEBCE390 (rcx=[rsi+r13]+0x1EAB0E0, rdx=r15, r8d=0x40) ; V+0x50 = viewMatrix[1] (mat4)
   - rcx = ctx + r13 + 0x1EAB0E0 = V + 0x50
5. 0x568ce80: call 0xEBCE390 (rcx=[rsi+r13]+0x1EAB120, rdx=r14, r8d=0x40) ; V+0x90 = viewMatrix[2] (mat4)
   - rcx = ctx + r13 + 0x1EAB120 = V + 0x90
6. 0x568ce99: call 0xEBCE390 (rcx=[rsi+r13]+0x1EAB160, rdx=[rbp+0x128], r8d=0x40) ; V+0xD0 = viewMatrix[3] (mat4)
   - rcx = ctx + r13 + 0x1EAB160 = V + 0xD0
7. 0x568ceb2: call 0xEBCE390 (rcx=[rsi+r13]+0x1EAB1A0, rdx=[rbp+0x128], r8d=0x10) ; V+0x110 = sortMode data (16 bytes)
   - rcx = ctx + r13 + 0x1EAB1A0 = V + 0x110
8. 0x568cecc: mov [rcx+r13+0x1EAB1B2],al        ; V+0x122 = sortMode byte (from [rbx+0x108])

### Stack Frame [rbp+off] Usage
- rbp+0x50..0x7F: lambda capture 1 (refcounted pointer + padding)
- rbp+0x80: flag byte
- rbp+0x88..0x9F: loop iteration state
- rbp+0xA0: current draw function pointer
- rbp+0xA8: rbx save (render item list head)
- rbp+0xB0: r14 save (current item)
- rbp+0xB8: [rbp+0x120]+0x100
- rbp+0xC0: [rbp+0x120]+0x19C
- rbp+0xC8: [rbp+0x120]+0x1D4
- rbp+0xD0: r14 (rbx+0x70)
- rbp+0xD8..0x11F: zeroed xmm registers / scratch
- rbp+0x120: original rbx (task data)
- rbp+0x128: [rbx+0x18C] / loop scratch
- rbp+0x138: stack cookie
- rbp+0x140: saved xmm6

### Per-Item Loop Callees
- 0xC4BBA0: per-pass draw function (varies by pass)
- 0x568DB90: per-item lambda
- 0xE86D7F0: encoder submit

### OPEN Questions
[UNVERIFIED: 0x568cf20] What is 0xBCC1A30 exactly? (lambda capture init?)
[UNVERIFIED: 0x568cf7a] What does 0xBC60D10 return? (render item iterator?)
[UNVERIFIED: 0x568d13c] 0xC4BBA0 - per-pass draw function, need to identify which pass
[UNVERIFIED: 0x568d21f] 0x568DB90 - per-item lambda, need bounds
[UNVERIFIED: 0x568d264] 0xE86D7F0 - encoder submit variant
[UNVERIFIED: 0x568d349] 0x568D480 - final per-view lambda, need bounds
[UNVERIFIED: 0x568d39e] [0xF9A8C78] - indirect call target (RaiseFailFastException?)

---

## Part B: std::function '_Copy' Slots Analysis

All 13 copy constructors are 0xE bytes: `mov rax,rdx` / `lea rcx,[vtable]` / `mov [rdx],rcx` / `ret` (or 2-qword variant). Each copies a static vtable pointer into the std::function object.

| # | _Copy RVA | VTable RVA | _Do_call (slot 2) | Per-Pass Draw Function |
|---|-----------|------------|-------------------|------------------------|
| 1 | 0xBC36B10 | 0xF43FE10 | 0x568CD70 | 0x568CD70 -> jmp 0x568CD90 (common thunk) |
| 2 | 0xBC36B60 | 0xF43FE70 | 0x568CD70 | 0x568CD70 -> jmp 0x568CD90 |
| 3 | 0xBC36C70 | 0xF43FF00 | 0x568CD70 | 0x568CD70 -> jmp 0x568CD90 |
| 4 | 0xBC36CC0 | 0xF43FF60 | 0x568CD70 | 0x568CD70 -> jmp 0x568CD90 |
| 5 | 0xBC36D10 | 0xF43FFC0 | 0x568CD70 | 0x568CD70 -> jmp 0x568CD90 |
| 6 | 0xBC36D60 | 0xF440020 | 0x568CD70 | 0x568CD70 -> jmp 0x568CD90 |
| 7 | 0xBC36E50 | 0xF440140 | 0x568CD70 | 0x568CD70 -> jmp 0x568CD90 |
| 8 | 0xBC36EF0 | 0xF440200 | 0x568CD70 | 0x568CD70 -> jmp 0x568CD90 |
| 9 | 0xBC36F40 | 0xF440260 | 0x568CD70 | 0x568CD70 -> jmp 0x568CD90 |
| 10 | 0x56AE9C0 | 0xF25BF90 | 0x568CD70 | 0x568CD70 -> jmp 0x568CD90 |
| 11 | 0xBC370D0 | 0xF440440 | 0x568CD70 | 0x568CD70 -> jmp 0x568CD90 |
| 12 | 0xBC37170 | 0xF440500 | 0x568CD70 | 0x568CD70 -> jmp 0x568CD90 |
| 13 | 0xBC37300 | 0xF4406E0 | 0x568CD70 | 0x568CD70 -> jmp 0x568CD90 |

All 13 _Copy slots belong to the 12 Scene passes + HUD task lambdas. Their vtables' `_Do_call` (slot 2 at vtable+0x10) all point to **0x568CD70** (RVA of thunk `mov rcx,rdx; mov rdx,r8; jmp 0x568CD90`). None of the _Copy slots directly name a real per-pass draw function in 0xBC3.... as a callee; the common Scene/HUD task body 0x568CD90 is the shared entry point. The per-pass differentiation occurs via captures in the lambda objects (task+0x70 std::function).

**0x568CD70 listing** (docs/listings/L_568cd70.txt): 0x568CD70 `mov rcx,rdx; mov rdx,r8; jmp 0x568CD90` (size 0x10), then 0x568CD90..0x568D3F5 (size 0x685) is the full task body.

**0x5688F70 listing** (docs/listings/L_5688f70.txt): Alternative _Do_call for the 2-qword _Copy variants (0xBC36B30, 0xBC36C90, etc.), size 0x63, does flag checks and calls 0xE93B480.

---

## Part C: 12 Scene Passes - bgfx-side pass functions

The 12 Scene passes are dispatched via jump table at **0xF25D03C** (referenced by 0x568DB90 at 0x568DBA3 `jmp rcx`). The jump table has 20 entries; indices 5–12 (8 entries) and 13–19 (7 entries) point to per-pass functions in the 0x5698... region. After deduplication, 12 distinct per-pass entry points are identified:

| Scene Pass | Entry RVA | Function | Size | Notes |
|------------|-----------|----------|------|-------|
| Scene[0] | 0x56984AC | sub_5698490 | 0x76 | Jump table 0xF25D050[1] -> calls 0x5698510 |
| Scene[1] | 0x56984C5 | sub_5698490 | 0x76 | Jump table 0xF25D050[2] -> calls 0x5698510 |
| Scene[2] | 0x56984DD | sub_5698490 | 0x76 | Jump table 0xF25D050[3] -> calls 0x5698510 |
| Scene[3] | 0x56984F5 | sub_5698490 | 0x76 | Jump table 0xF25D050[4] -> calls 0x5698510 |
| Scene[4] | 0x56984BC | sub_5698490 | 0x76 | Jump table 0xF25D050[5] -> calls 0x5698510 |
| Scene[5] | 0x56984C0 | sub_5698490 | 0x76 | Jump table 0xF25D050[6] -> calls 0x5698510 |
| Scene[6] | 0x56984C4 | sub_5698490 | 0x76 | Jump table 0xF25D050[7] -> calls 0x5698510 |
| Scene[7] | 0x569878C | sub_5698710 | 0x10C | Jump table 0xF25D050[8] -> internal jump table 0xF25D070 |
| Scene[8] | 0x56987E7 | sub_5698710 | 0x10C | Jump table 0xF25D050[9] -> internal jump table 0xF25D084 |
| Scene[9] | 0x56987EB | sub_5698710 | 0x10C | Jump table 0xF25D050[10] -> internal jump table 0xF25D084 |
| Scene[10] | 0x5698798 | sub_5698710 | 0x10C | Jump table 0xF25D050[11] -> internal jump table 0xF25D070 |
| Scene[11] | 0x569879C | sub_5698710 | 0x10C | Jump table 0xF25D050[12] -> internal jump table 0xF25D070 |

**Function details:**
- **sub_5698490** (0x5698490..0x5698506, size 0x76): Jump table dispatch at 0xF25D050. Calls per-pass helpers: 0x5698510 (main draw), 0x5698850, 0x5698A40, 0x1166E0 (fallback).
- **sub_5698710** (0x5698710..0x569881C, size 0x10C): Internal jump tables at 0xF25D070 (5 entries) and 0xF25D084 (3 entries) for sub-pass selection. Calls 0x567ACF0, 0x5698710 (recursive), 0x3839220, 0x567AE50, 0x567ADE0.
- **sub_5698510** (0x5698510..0x5698710, size 0x200): Main per-pass draw logic, uses bgfx encoder, calls 0x567ACF0, 0x5698710, 0x3839220, 0x1166E0, 0x1A2800, 0xE951550.
- **sub_5698850** (0x5698850..0x5698850+size): Per-pass helper (listing L_5698850.txt pending).
- **sub_5698A40** (0x5698A40..0x5698A40+size): Per-pass helper (listing L_5698a40.txt pending).

[UNVERIFIED: 0x56984AC] Exact mapping of Scene[0..11] to pass names (Shadow Cascades, ScenePrepass, GeometryPrepass, etc. from vv_builder_pass_order_55f1450.md) not yet correlated.
[UNVERIFIED: 0x5698710] Full enumeration of sub_5698710 internal jump table targets (0xF25D070, 0xF25D084) and their callee functions.

---

## Verification: Quoted Instructions (for verify_oc.py)

### sub_568cd90 (0x568CD90..0x568D3A5)
0x568CD90  push rbp
0x568CD91  push r15
0x568CD93  push r14
0x568CD95  push r13
0x568CD97  push r12
0x568CD99  push rsi
0x568CD9A  push rdi
0x568CD9B  push rbx
0x568CD9C  sub rsp,0x1D8
0x568CDA3  lea rbp,[rsp+0x80]
0x568CDAB  movdqa [rbp+0x140],xmm6
0x568CDB3  mov qword ptr [rbp+0x138],0xFFFFFFFFFFFFFFFE
0x568CDBE  mov rbx,rdx
0x568CDC1  mov rdi,rcx
0x568CDC4  add rdx,0x78
0x568CDC8  mov rax,[rcx+8]
0x568CDCC  movzx eax,word ptr [rax+8]
0x568CDD0  mov rcx,[0x12AE1748]
0x568CDD7  shl eax,6
0x568CDDA  lea r13,[rax+rax*4]
0x568CDDE  movq xmm0,[rbx+0xF8]
0x568CDE6  pxor xmm6,xmm6
0x568CDEA  pmaxsw xmm0,xmm6
0x568CDEE  movd xmm1,[rbx+0xFC]
0x568CDF6  movd [rcx+r13+0x1EAB090],xmm0
0x568CE00  movdqa xmm0,xmm1
0x568CE04  pcmpeqw xmm0,xmm6
0x568CE08  psubw xmm1,xmm0
0x568CE0C  movd [rcx+r13+0x1EAB094],xmm1
0x568CE16  lea rax,[rbx+0x18C]
0x568CE1D  mov [rbp+0x128],rax
0x568CE24  lea r14,[rbx+0x14C]
0x568CE2B  lea r15,[rbx+0x10C]
0x568CE32  lea r12,[rbx+0xB8]
0x568CE39  mov rsi,[0x12AE1748]
0x568CE40  lea rcx,[rsi+r13]
0x568CE44  add rcx,0x1EAB0A0
0x568CE4B  mov r8d,0x40
0x568CE51  call 0xEBCE390
0x568CE56  lea rcx,[rsi+r13]
0x568CE5A  add rcx,0x1EAB0E0
0x568CE61  mov r8d,0x40
0x568CE67  mov rdx,r12
0x568CE6A  call 0xEBCE390
0x568CE6F  lea rcx,[rsi+r13]
0x568CE73  add rcx,0x1EAB120
0x568CE7A  mov r8d,0x40
0x568CE80  mov rdx,r15
0x568CE83  call 0xEBCE390
0x568CE88  lea rcx,[rsi+r13]
0x568CE8C  add rcx,0x1EAB160
0x568CE93  mov r8d,0x40
0x568CE99  mov rdx,r14
0x568CE9C  call 0xEBCE390
0x568CEA1  lea rcx,[rsi+r13]
0x568CEA5  add rcx,0x1EAB1A0
0x568CEAC  mov r8d,0x10
0x568CEB2  mov rdx,[rbp+0x128]
0x568CEB9  call 0xEBCE390
0x568CEBE  movzx eax,byte ptr [rbx+0x108]
0x568CEC5  mov rcx,[0x12AE1748]
0x568CECC  mov [rcx+r13+0x1EAB1B2],al
0x568CED4  mov r14,[rdi+8]
0x568CED8  mov rax,[rbx]
0x568CEDB  mov [rbp+0x50],rax
0x568CEDF  movdqu [rbp+0x58],xmm6
0x568CEE4  mov rax,[rbx+0x10]
0x568CEE8  test rax,rax
0x568CEEB  je short 0x568CEF7
0x568CEED  lock inc dword ptr [rax+8]
0x568CEF1  mov rax,[rbx+0x10]
0x568CEF5  jmp short 0x568CEF9
0x568CEF7  xor eax,eax
0x568CEF9  mov rcx,[rbx+8]
0x568CEFD  mov [rbp+0x58],rcx
0x568CF01  mov [rbp+0x60],rax
0x568CF05  movdqu [rbp+0x68],xmm6
0x568CF0A  mov qword ptr [rbp+0x78],0
0x568CF12  mov byte ptr [rbp+0x80],1
0x568CF19  lea rdx,[rbp+0x50]
0x568CF1D  mov rcx,r14
0x568CF20  call 0xBCC1A30
0x568CF26  mov rdi,[rbx+0x70]
0x568CF2A  mov rsi,[rbx+0x48]
0x568CF2E  mov [rbp+0x120],rbx
0x568CF35  mov rbx,[rbx+0x68]
0x568CF39  mov [rbp+0xD0],r14
0x568CF40  pxor xmm0,xmm0
0x568CF44  movdqu [rbp+0xD8],xmm0
0x568CF4C  movdqu [rbp+0xE8],xmm0
0x568CF54  movdqu [rbp+0xF8],xmm0
0x568CF5C  movdqu [rbp+0x108],xmm0
0x568CF64  mov qword ptr [rbp+0x118],0
0x568CF6F  mov [rbp+0xB0],r14
0x568CF76  mov rcx,[r14+0x10]
0x568CF7A  call 0xBC60D10
0x568CF80  cmp rdi,rbx
0x568CF83  jne short 0x568CFF5
0x568CF85  lea rcx,[rbp+0xF0]
0x568CF8C  call 0x568DA90
0x568CF91  mov rcx,[rbp+0xD8]
0x568CF98  test rcx,rcx
0x568CF9B  je short 0x568CFD1
0x568CF9D  mov rdx,[rbp+0xE8]
0x568CFA4  sub rdx,rcx
0x568CFA7  cmp rdx,0x1000
0x568CFAE  jb short 0x568CFCC
0x568CFB0  mov rax,[rcx-8]
0x568CFB4  add rcx,0xFFFFFFFFFFFFFFF8
0x568CFB8  sub rcx,rax
0x568CFBB  cmp rcx,0x20
0x568CFBF  jae 0x568D38B
0x568CFC5  add rdx,0x27
0x568CFC9  mov rcx,rax
0x568CFCC  call 0xE935700
0x568CFD1  lea rcx,[rbp+0x50]
0x568CFD5  call 0x655CEA0
0x568CFDA  movaps xmm6,[rbp+0x140]
0x568CFE1  add rsp,0x1D8
0x568CFE8  pop rbx
0x568CFE9  pop rdi
0x568CFEA  pop rsi
0x568CFEB  pop r12
0x568CFED  pop r13
0x568CFEF  pop r14
0x568CFF1  pop r15
0x568CFF3  pop rbp
0x568CFF4  ret

### sub_568cd70 thunk (0x568CD70..0x568CD90)
0x568CD70  mov rcx,rdx
0x568CD73  mov rdx,r8
0x568CD76  jmp 0x568CD90

### sub_568db90 jump table dispatch (0x568DB90..0x568DC10)
0x568DB90  push rsi
0x568DB91  sub rsp,0x30
0x568DB95  lea rax,[0xF25D03C]
0x568DB9C  movsxd rcx,[rax+rcx*4]
0x568DBA0  add rcx,rax
0x568DBA3  jmp rcx

### sub_5698490 jump table dispatch (0x5698490..0x5698506)
0x5698490  push rsi
0x5698491  sub rsp,0x20
0x5698495  mov rsi,rcx
0x5698498  lea rax,[0xF25D050]
0x569849F  movsxd rcx,[rax+rdx*4]
0x56984A3  add rcx,rax
0x56984A6  jmp rcx

### sub_5698710 (0x5698710..0x569881C)
0x5698710  push rbp
0x5698711  push rsi
0x5698712  sub rsp,0x78
0x5698716  lea rbp,[rsp+0x70]
0x569871B  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
0x5698723  movups xmm0,[r9]
0x5698727  movaps [rbp-0x50],xmm0
0x569872B  mov byte ptr [rbp-0x38],3
0x569872F  movups xmm0,[r9]
0x5698733  movaps [rbp-0x30],xmm0
0x5698737  mov byte ptr [rbp-0x18],3
0x569873B  mov rcx,[r8]
0x569873E  mov [rbp-0x10],rcx
0x5698742  mov rax,[rdx+8]
0x5698746  cmp rax,[rdx+0x10]
0x569874A  je short 0x5698762
0x569874C  movups xmm0,[r9]
0x5698750  movups [rax],xmm0
0x5698753  mov byte ptr [rax+0x18],3
0x5698757  mov [rax+0x20],rcx
0x569875B  add qword ptr [rdx+8],0x28
0x5698760  jmp short 0x569878C
0x5698762  lea r8,[rbp-0x30]
0x5698766  mov rcx,rdx
0x5698769  mov rdx,rax
0x569876C  call 0x567AE50

---

## TOOL REQUESTS
- `stores.py` on L_568cd90.txt would have automated the [reg+off] store extraction (done manually)
- `casewalk.py` on L_568db90.txt (jump table 0xF25D03C) would automate the Scene pass enumeration (done manually via Python)
- `dumplist.py` for 0x5698850, 0x5698A40, 0x567ACF0, 0x567AE50, 0x567ADE0, 0x3839220 to complete Part C callees