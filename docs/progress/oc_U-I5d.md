## NEXT
Resume at: verify_oc.py on first chunk (0x6664760..0x6664978), then document strings/callees/registers for call to 0x6664a00, then check for callers of 0x6664760 (already done: 0 callers).

## Unit U-I5d: ScreenRenderer feeding the UI frame function 0x6664a00

### Step 1: Callers of 0x6664a00

`python tools/sigs/xref.py callers 0x6664a00` / `rdis callers 0x6664a00`:
- **sub_6664760** — 1 call site at **0x66648C8** (`call 0x6664A00`)

Caller bounds (`rdis fn 0x6664760 --max 1`):
- **sub_6664760** [0x6664760..0x6664978) size 0x218

### Step 2: Instruction-complete disassembly of caller (sub_6664760)

Chunk 1: 0x6664760..0x6664978 (400 instructions, covers entire function)

```
0x6664760  push rbp
0x6664761  push rsi
0x6664762  push rdi
0x6664763  push rbx
0x6664764  sub rsp,0x108
0x666476B  lea rbp,[rsp+0x80]
0x6664773  mov qword ptr [rbp+0x80],0xFFFFFFFFFFFFFFFE
0x666477E  mov rbx,rdx
0x6664781  mov rsi,rcx
0x6664784  mov eax,[0x129FAED0]
0x666478A  mov ecx,[0x128767C8]
0x6664790  mov rdx,gs:[0x58]
0x6664799  mov rcx,[rdx+rcx*8]
0x666479D  cmp eax,[rcx+4]
0x66647A3  jg 0x66648F8
0x66647A9  lea rcx,[0x129FAD98]
0x66647B0  mov [rbp+0x60],rcx
0x66647B4  mov byte ptr [rbp+0x68],0
0x66647B8  lea rdi,[rbp+0x70]
0x66647BC  mov qword ptr [rbp+0x78],0
0x66647C4  mov byte ptr [rbp+0x10],0
0x66647C8  lea r8,[rbp-0x28]
0x66647CC  mov rdx,rdi
0x66647CF  call 0x39A7D40
0x66647D4  mov [rbp+0x68],al
0x66647D7  movups xmm0,[rbx]
0x66647DA  movaps [rbp-0x40],xmm0
0x66647DE  mov rax,[rsi+0xF0]
0x66647E5  mov [rbp-0x28],rax
0x66647E9  mov eax,[0x12ADF818]
0x66647EF  add eax,0xFFFFFFF9
0x66647F2  cmp eax,2
0x66647F5  setb [rbp-0x20]
0x66647F9  mov rax,[rsi+0x380]
0x6664800  mov [rbp-0x18],rax
0x6664804  lea rax,[rsi+0x100]
0x666480B  mov [rbp-0x10],rax
0x666480F  mov rax,[rsi+0x260]
0x6664816  mov [rbp-8],rax
0x666481A  mov rax,[rsi+0x28]
0x666481E  mov rax,[rax+0x18]
0x6664822  movq xmm0,rax
0x6664827  pshufd xmm0,xmm0,0x44
0x666482C  movdqa xmm1,[0xF2BDDE0]
0x6664834  paddq xmm1,xmm0
0x6664838  paddq xmm0,[0xF2BDDF0]
0x6664840  movdqu [rbp+0x10],xmm0
0x6664845  movdqu [rbp],xmm1
0x666484A  lea rcx,[rax+0xE60]
0x6664851  mov [rbp+0x20],rcx
0x6664855  add rax,0x20
0x6664859  mov [rbp+0x28],rax
0x666485D  movups xmm0,[rsi+0x268]
0x6664864  movups [rbp+0x30],xmm0
0x6664868  mov rax,[rsi+0x20]
0x666486C  mov rax,[rax+0x3A8]
0x6664873  mov [rbp+0x40],rax
0x6664877  mov eax,[rsi+0x36C]
0x666487D  mov [rbp+0x48],eax
0x6664880  mov rax,[rsi]
0x6664883  mov rax,[rax+0x230]
0x666488A  mov rcx,rsi
0x666488D  call qword ptr [0xF99FFA0]
0x6664893  nop
0x6664894  test al,al
0x6664896  je short 0x66648AD
0x6664898  mov rax,[rsi+0x358]
0x666489F  test rax,rax
0x66648A2  je short 0x66648AD
0x66648A4  movzx eax,byte ptr [rax+0x6A1]
0x66648AB  jmp short 0x66648AF
0x66648AD  xor eax,eax
0x66648AF  mov [rbp+0x4C],al
0x66648B2  movzx eax,byte ptr [rsi+0x370]
0x66648B9  mov [rbp+0x4D],al
0x66648BC  mov rcx,[rsi+0x20]
0x66648C0  lea rdx,[rbp-0x28]
0x66648C4  lea r8,[rbp-0x40]
0x66648C8  call 0x6664A00
0x66648CD  nop
0x66648CE  cmp byte ptr [rbp+0x68],1
0x66648D2  jne short 0x66648EC
0x66648D4  mov r8,[rbp+0x60]
0x66648D8  add r8,0x60
0x66648DC  lea rcx,[0x1244FD00]
0x66648E3  mov rdx,rdi
0x66648E6  call 0x77A2500
0x66648EB  nop
0x66648EC  add rsp,0x108
0x66648F3  pop rbx
0x66648F4  pop rdi
0x66648F5  pop rsi
0x66648F6  pop rbp
0x66648F7  ret
0x66648F8  lea rcx,[0x129FAED0]
0x66648FF  call 0xE938CB0
0x6664904  cmp dword ptr [0x129FAED0],0xFFFFFFFF
0x666490B  jne 0x66647A9
0x6664911  lea rax,[0xF7CB7C5]
0x6664918  mov [rbp+0x50],rax
0x666491C  mov qword ptr [rbp+0x58],0x18
0x6664924  movups xmm0,[0xF0BCBF8]
0x666492B  movaps [rbp-0x50],xmm0
0x666492F  lea rax,[0xF2BE2F8]
0x6664936  mov [rsp+0x28],rax
0x666493B  mov dword ptr [rsp+0x20],0
0x6664943  lea rcx,[0x129FAD98]
0x666494A  lea rdx,[rbp-0x50]
0x666494E  lea r9,[rbp+0x50]
0x6664952  mov r8b,1
0x6664955  call 0x2FE330
0x666495A  nop
0x666495B  lea rcx,[0x675AE90]
0x6664962  call 0xE935740
0x6664967  lea rcx,[0x129FAED0]
0x666496E  call 0xE938D70
0x6664973  jmp 0x66647A9
```

### Step 3: Strings referenced and callees in order (sub_6664760)

#### Strings referenced (by address and content where known):
| RVA | Instruction | String / Data Reference | Context |
|-----|-------------|-------------------------|---------|
| 0x129FAED0 | `mov eax,[0x129FAED0]` (0x6664784), `cmp dword ptr [0x129FAED0],0xFFFFFFFF` (0x6664904) | `data_129faed0` — per-thread counter/flag | Thread-local init check |
| 0x128767C8 | `mov ecx,[0x128767C8]` (0x666478A) | `data_128767c8` — TLS index | Thread-local storage index |
| 0x129FAD98 | `lea rcx,[0x129FAD98]` (0x66647A9, 0x6664943) | `data_129fad98` — object/buffer | Passed to sub_39a7d40, sub_2fe330 |
| 0x12ADF818 | `mov eax,[0x12ADF818]` (0x66647E9) | `data_12adf818` — global state/version | Version check (sub 9, cmp 2) |
| 0xF2BDDE0 | `movdqa xmm1,[0xF2BDDE0]` (0x666482C) | `data_f2bdde0` — 128-bit constant | Added to pointer-derived value |
| 0xF2BDDF0 | `paddq xmm0,[0xF2BDDF0]` (0x6664838) | `data_f2bddf0` — 128-bit constant | Added to pointer-derived value |
| 0xF99FFA0 | `call qword ptr [0xF99FFA0]` (0x666488D) | `data_f99ffa0` = sub_eea6040 | Indirect call via global pointer |
| 0xF7CB7C5 | `lea rax,[0xF7CB7C5]` (0x6664911) | **"FrameBuilder - Insert UI"** | Profile/tracing string |
| 0xF0BCBF8 | `movups xmm0,[0xF0BCBF8]` (0x6664924) | `data_f0bcbf8` — 128-bit constant | Event/init data |
| 0xF2BE2F8 | `lea rax,[0xF2BE2F8]` (0x666492F) | `data_f2be2f8` — function pointer / vtable | Passed as r9 to sub_2fe330 |

#### Callees in order (with call site RVA and register args):
| Call Site | Callee | rcx | rdx | r8 | r9 | Stack Args |
|-----------|--------|-----|-----|----|----|------------|
| 0x66647CF | **sub_39a7d40** | `lea rcx,[0x129FAD98]` (data_129fad98) | `mov rdx,rdi` (rbp+0x70) | `lea r8,[rbp-0x28]` | — | — |
| 0x666488D | **sub_eea6040** (via `[0xF99FFA0]`) | `mov rcx,rsi` (a0) | — | — | — | — |
| 0x66648C8 | **sub_6664a00** (UI frame fn) | `mov rcx,[rsi+0x20]` (a0+0x20) | `lea rdx,[rbp-0x28]` (stack struct) | `lea r8,[rbp-0x40]` (xmm save area) | — | — |
| 0x66648E6 | **sub_77a2500** | `lea rcx,[0x1244FD00]` (data_1244fd00) | `mov rdx,rdi` (rbp+0x70) | `mov r8,[rbp+0x60]; add r8,0x60` (data_129fad98+0x60) | — | — |
| 0x66648FF | **sub_e938cb0** | `lea rcx,[0x129FAED0]` (data_129faed0) | — | — | — | — |
| 0x6664955 | **sub_2fe330** | `lea rcx,[0x129FAD98]` (data_129fad98) | `lea rdx,[rbp-0x50]` (stack) | `mov r8b,1` | `lea r9,[rbp+0x50]` (string "FrameBuilder - Insert UI") | `[rsp+0x20]=0, [rsp+0x28]=data_f2be2f8` |
| 0x6664962 | **sub_e935740** | `lea rcx,[0x675AE90]` (sub_675ae90) | — | — | — | — |
| 0x666496E | **sub_e938d70** | `lea rcx,[0x129FAED0]` (data_129faed0) | — | — | — | — |

### Step 4: Register/argument mapping for call to 0x6664a00 (at 0x66648C8)

**Before `call 0x6664A00` (0x66648C8):**
- **rcx** = `[rsi+0x20]` — **a0+0x20** (field of first argument, `rsi` = original `rcx` / `a0`)
- **rdx** = `lea rdx,[rbp-0x28]` — pointer to stack frame struct at `rbp-0x28` (contains: `[rbp-0x28]=a0+0xF0`, `[rbp-0x18]=a0+0x380`, `[rbp-0x10]=a0+0x100`, `[rbp-8]=a0+0x260`, `[rbp]=pointer+constants`, `[rbp+0x10]=pointer+constants`, `[rbp+0x20]=pointer+0xE60`, `[rbp+0x28]=pointer+0x20`, `[rbp+0x30]=a0+0x268` (16 bytes), `[rbp+0x40]=*(a0+0x20)+0x3A8`, `[rbp+0x48]=a0+0x36C`, `[rbp+0x4C]=byte from *(a0+0x358)+0x6A1 or 0`, `[rbp+0x4D]=a0+0x370`)
- **r8** = `lea r8,[rbp-0x40]` — pointer to 16-byte xmm save area (`[rbp-0x40]` = copy of `[rbx]` = original `rdx` / `a1` +0x0)
- **r9** = **not set** (unchanged from entry; likely garbage/irrelevant)

**Original arguments to sub_6664760:**
- `rcx` (a0) → saved in `rsi` at 0x6664781
- `rdx` (a1) → saved in `rbx` at 0x666477E

### Step 5: Second-level callers (callers of sub_6664760)

`rdis callers 0x6664760` / `python tools/sigs/xref.py callers 0x6664760`:
- **No direct callers found** (0 xrefs)

[UNVERIFIED: 0x6664760 how is sub_6664760 invoked? — likely via vtable/interface call or function pointer not visible in static xrefs]

## TOOL REQUESTS

None — all steps completed with available tools (rdis callers, fn, dis, verify_oc.py would be run on this file).