## NEXT
All steps complete. File verified with verify_oc.py.

---

# Unit U-A10: bgfx render thread procedure 0xbc63150

## Step 1: Preflight and BGFX_MAP 6as

Ran `PYTHONUTF8=1 python tools/preflight.py 0xbc63150 --n 400` -> `docs/progress/pre/0xbc63150.md` (452 lines).

Key data from BGFX_MAP 6as (lines 750-754):
- `0xbc63150` = `bgfx::Context::renderFrame(int32_t msecs)` (rcx = ctx, edx = timeout)
- Return: `RenderFrame::Enum` (0 NoContext, 1 Render, 2 Timeout, **3 Exiting**)
- Thread proc `0xbc65720` loops `while (renderFrame(5000) != Exiting)`
- Prologue clears reset-flag bit 0x40000 in `[ctx+0x1CFD0C0]+0xDC5810`
- If `byte ctx+0x1EBF2EE == 1` calls RendererContext vtable slot 9 (`+0x48`) and clears it
- If `ctx+0x1EBF2EC == 1 && ctx+0x1EBF2ED == 0` calls slot 6 (`+0x30`) and, when reset-flag bit 0x800000 (`[ctx+0x1EBF19C]`) also set, slot 53 (`+0x1A8`)
- If `ctx+0x1EBF2F1 == 0` (not shutting down) waits on `ctx+0x80` with timeout; timeout returns 2
- Semaphores: `ctx+0x80` = "frame data ready" gate, `ctx+0x100` = "frame consumed" (signalled via `0xebdbc50(.., 1)`)
- Surface array: `ctx+0x13D18` stride 0x700

---

## Step 2: Instruction-complete listing of 0xbc63150

Function range: `0xbc63150..0xbc634ad` (size 0x35d = 861 bytes). Full disassembly from `tools/sigs/disrange.py` / rdis:

### Phase 1: Prologue and reset-flag clear (0xbc63150..0xbc63188)

```
bc63150  push r14
bc63152  push rsi
bc63153  push rdi
bc63154  push rbp
bc63155  push rbx
bc63156  sub rsp,0x70
bc6315a  mov edi,edx
bc6315c  mov rsi,rcx
bc6315f  mov rax,[0x1230A0C0]
bc63166  xor rax,rsp
bc63169  mov [rsp+0x68],rax
bc6316e  mov rax,[rcx+0x1CFD0C0]
bc63175  mov ebp,[rax+0xDC5810]
bc6317b  mov ecx,ebp
bc6317d  and ecx,0xFFFBFFFF
bc63183  mov [rax+0xDC5810],ecx
```

### Phase 2: Init-state flag 0x1EBF2EE handling (0xbc63189..0xbc631AC)

```
bc63189  cmp byte ptr [rsi+0x1EBF2EE],1
bc63190  jne short bc631AD
bc63192  mov rcx,[rsi+0x1EBF2D0]
bc63199  mov rax,[rcx]
bc6319c  mov rax,[rax+0x48]
bc631a0  call qword ptr [0xF99FFA0]
bc631a6  mov byte ptr [rsi+0x1EBF2EE],0
```

### Phase 3: Reset/device-notify flags (0xbc631AD..0xbc63214)

```
bc631ad  mov r14d,[rsi+0x1EBF19C]
bc631b4  cmp byte ptr [rsi+0x1EBF2F0],0
bc631bb  jne short bc63215
bc631bd  cmp byte ptr [rsi+0x1EBF2EC],1
bc631c4  jne short bc631E3
bc631c6  cmp byte ptr [rsi+0x1EBF2ED],0
bc631cd  jne short bc631E3
bc631cf  mov rcx,[rsi+0x1EBF2D0]
bc631d6  mov rax,[rcx]
bc631d9  mov rax,[rax+0x30]
bc631dd  call qword ptr [0xF99FFA0]
bc631e3  test r14d,0x800000
bc631ea  je short bc63215
bc631ec  cmp byte ptr [rsi+0x1EBF2EC],1
bc631f3  jne short bc63215
bc631f5  cmp byte ptr [rsi+0x1EBF2ED],0
bc631fc  jne short bc63215
bc631fe  mov rcx,[rsi+0x1EBF2D0]
bc63205  mov rax,[rcx]
bc63208  mov rax,[rax+0x1A8]
bc6320f  call qword ptr [0xF99FFA0]
```

### Phase 4: Main wait on semaphore ctx+0x80 (0xbc63215..0xbc6326D)

```
bc63215  cmp byte ptr [rsi+0x1EBF2F1],0
bc6321c  jne short bc6326E
bc6321e  call ebdb740
bc63223  mov rbx,rax
bc63226  lea rcx,[rsi+0x80]
bc6322d  mov edx,edi
bc6322f  call ebdbc60
bc63234  mov ecx,eax
bc63236  mov eax,2
bc6323b  test cl,cl
bc6323d  je bc63480
bc63243  call ebdb740
bc63248  sub rax,rbx
bc6324b  mov rcx,[rsi+0x1CFD0C0]
bc63252  mov [rcx+0xE746C8],rax
bc63259  mov rax,[rsi+0x1CFD0C8]
bc63260  mov rcx,[rax+0xE746C8]
bc63267  mov [rax+0xE60E40],rcx
```

### Phase 5: Reset/device-notify post-wait (0xbc6326E..0xbc6336B)

```
bc6326e  cmp byte ptr [rsi+0x1EBF2EC],1
bc63275  jne bc6336C
bc6327b  mov rcx,[rsi+0x1EBF2D0]
bc63282  mov rax,[rcx]
bc63285  mov rax,[rax+0x38]
bc63289  call qword ptr [0xF99FFA0]
bc6328f  mov rcx,[rsi+0x1EBF2D0]
bc63296  mov rax,[rcx]
bc63299  mov rax,[rax+0x28]
bc6329d  call qword ptr [0xF99FFA0]
bc632a3  test al,al
bc632a5  je bc63358
bc632ab  mov rcx,[rsi+0x1EBF2D0]
bc632b2  test rcx,rcx
bc632b5  je short bc632DC
bc632b7  mov rax,[rcx]
bc632ba  mov rax,[rax+8]
bc632be  call qword ptr [0xF99FFA0]
bc632c4  cdqe
bc632c6  lea rax,[rax+rax*4]
bc632ca  lea rcx,[0x127CA010]
bc632d1  mov rax,[rcx+rax*8+8]
bc632d6  call qword ptr [0xF99FFA0]
bc632dc  mov word ptr [rsp+0x30],0
bc632e3  mov rax,0x2D000000500
bc632ed  mov [rsp+0x34],rax
bc632f2  mov dword ptr [rsp+0x3C],0
bc632fa  xorps xmm0,xmm0
bc632fd  movups [rsp+0x50],xmm0
bc63302  mov qword ptr [rsp+0x60],0
bc6330b  mov word ptr [rsp+0x40],8
bc63312  mov rax,0x20000000600000
bc6331c  mov [rsp+0x44],rax
bc63321  mov byte ptr [rsp+0x4C],1
bc63326  mov qword ptr [rsp+0x28],0
bc6332f  mov byte ptr [rsp+0x27],0
bc63334  lea rcx,[rsp+0x28]
bc63339  lea r8,[rsp+0x27]
bc6333e  xor edx,edx
bc63340  call bc68840
bc63345  mov [rsi+0x1EBF2D0],rax
bc6334c  mov dword ptr [0x12ADF818],0
bc63356  jmp short bc6336C
bc63358  mov rax,[rsi+0x1CFD0C0]
bc6335f  movzx eax,byte ptr [rax+0xE74989]
bc63366  mov [rsi+0x1EBF2ED],al
```

### Phase 6: Command buffer processing (0xbc6336C..0xbc633DA)

```
bc6336c  mov edx,0xDC5818
bc63371  add rdx,[rsi+0x1CFD0C0]
bc63378  mov rcx,rsi
bc6337b  call bc68e40
bc63380  cmp byte ptr [rsi+0x1EBF2EC],1
bc63387  jne short bc633B5
bc63389  mov rcx,[rsi+0x1EBF2D0]
bc63390  lea r9,[rsi+0x1EBF1F0]
bc63397  lea r8,[rsi+0x1EBF260]
bc6339e  mov rdx,[rsi+0x1CFD0C0]
bc633a5  mov rax,[rcx]
bc633a8  mov rax,[rax+0x190]
bc633af  call qword ptr [0xF99FFA0]
bc633b5  mov edx,0xE05820
bc633ba  add rdx,[rsi+0x1CFD0C0]
bc633c1  mov rcx,rsi
bc633c4  call bc68e40
```

### Phase 7: Signal semaphore ctx+0x100 and return (0xbc633C9..0xbc6349E)

```
bc633c9  cmp byte ptr [rsi+0x1EBF2F1],0
bc633d0  jne short bc633DF
bc633d2  mov rcx,rsi
bc633d5  mov edx,1
bc633da  call ebdbc50
bc633df  movzx eax,byte ptr [rsi+0x1EBF2EC]
bc633e6  cmp byte ptr [rsi+0x1EBF2F0],1
bc633ed  jne short bc6344B
bc633ef  test al,al
bc633f1  je short bc63417
bc633f3  cmp byte ptr [rsi+0x1EBF2ED],0
bc633fa  jne short bc63417
bc633fc  mov rcx,[rsi+0x1EBF2D0]
bc63403  mov rax,[rcx]
bc63406  mov rax,[rax+0x30]
bc6340a  call qword ptr [0xF99FFA0]
bc63410  movzx eax,byte ptr [rsi+0x1EBF2EC]
bc63417  test r14d,0x800000
bc6341e  je short bc6344B
bc63420  test al,al
bc63422  je short bc6344B
bc63424  cmp byte ptr [rsi+0x1EBF2ED],0
bc6342b  jne short bc6344B
bc6342d  mov rcx,[rsi+0x1EBF2D0]
bc63434  mov rax,[rcx]
bc63437  mov rax,[rax+0x1A8]
bc6343e  call qword ptr [0xF99FFA0]
bc63444  movzx eax,byte ptr [rsi+0x1EBF2EC]
bc6344b  test ebp,0x40000
bc63451  je short bc63472
bc63453  test al,al
bc63455  je short bc63472
bc63457  mov rcx,[rsi+0x1EBF2D0]
bc6345e  mov rax,[rcx]
bc63461  mov rax,[rax+0x40]
bc63465  call qword ptr [0xF99FFA0]
bc6346b  mov byte ptr [rsi+0x1EBF2EE],1
bc63472  movzx eax,byte ptr [rsi+0x1EBF2EF]
bc63479  lea eax,[rax*2+1]
```

### Phase 8: Epilogue and return (0xbc63480..0xbc634AD)

```
bc63480  mov rcx,[rsp+0x68]
bc63485  xor rcx,rsp
bc63488  mov rdx,[0x1230A0C0]
bc6348f  cmp rdx,rcx
bc63492  jne short bc6349F
bc63494  add rsp,0x70
bc63498  pop rbx
bc63499  pop rbp
bc6349a  pop rdi
bc6349b  pop rsi
bc6349c  pop r14
bc6349e  ret
bc6349f  mov rcx,[rsp+0x68]
bc634a4  xor rcx,rsp
bc634a7  call e951550
bc634ac  int3
```

### Phase 9: Shutdown/init path (0xbc634B0..0xbc6368D) - separate function chunk

```
bc634b0  push r14
bc634b2  push rsi
bc634b3  push rdi
bc634b4  push rbx
bc634b5  sub rsp,0x28
bc634b9  mov rsi,rcx
bc634bc  mov eax,[rcx+0x1EBF2E8]
bc634c2  test dl,dl
bc634c4  je bc635A9
... (this appears to be a different entry point, likely Context::init or shutdown handler)
```

---

## Step 3: [reg+off] read/write table and ordered callees

### Context/Frame object field accesses (rsi = ctx, rax/rcx = Frame*)

| Offset | Size | R/W | Meaning | Tag |
|--------|------|-----|---------|-----|
| ctx+0x1CFD0C0 | 8 | R | Pointer to current submit Frame buffer | [V] |
| ctx+0x1CFD0C8 | 8 | R | Pointer to previous Frame buffer (double-buffered) | [V] |
| Frame+0xDC5810 | 4 | R/W | Reset flags (bit 0x40000 cleared in prologue) | [V] |
| ctx+0x1EBF2EE | 1 | R/W | Init-state flag (1=needs slot 9 call, cleared after) | [V] |
| ctx+0x1EBF2F0 | 1 | R | Shutdown-in-progress flag | [V] |
| ctx+0x1EBF2EC | 1 | R | Reset requested flag | [V] |
| ctx+0x1EBF2ED | 1 | R/W | Reset acknowledged flag | [V] |
| ctx+0x1EBF19C | 4 | R | Reset flags copy (bit 0x800000 = device reset) | [V] |
| ctx+0x1EBF2D0 | 8 | R/W | RendererContextD3D12* pointer | [V] |
| ctx+0x1EBF2F1 | 1 | R/W | Shutdown state (0=running, 1=shutting down, set at 0xbc6374a) | [V] |
| ctx+0x80 | - | R | Semaphore: "frame data ready" (waited via ebdbc60) | [V] |
| ctx+0x100 | - | W | Semaphore: "frame consumed" (signalled via ebdbc50) | [V] |
| Frame+0xE746C8 | 8 | W | Render thread wait duration (t1-t0) | [V] |
| Frame+0xE60E40 | 8 | W | Previous frame's wait duration | [V] |
| Frame+0xDC5818 | - | R | Pre-command buffer position | [V] |
| Frame+0xE05820 | - | R | Post-command buffer position | [V] |
| Frame+0xE74989 | 1 | R | Byte copied to ctx+0x1EBF2ED | [V] |
| ctx+0x1EBF2EF | 1 | R | Shutdown state byte (used for return value) | [V] |
| ctx+0x1EBF1F0 | - | R | Passed to submit (slot 50) as r9 | [V] |
| ctx+0x1EBF260 | - | R | Passed to submit (slot 50) as r8 | [V] |
| ctx+0x1EBF1C8 | 8 | W | QPC timestamp from init | [V] |
| ctx+0x1EBF1D0 | 4 | W | Zeroed during init | [V] |
| ctx+0x1EAAA60..0x1EAAC10 | 0x1B0 | W | Clear-color palette (16 xmm stores) | [V] |
| ctx+0x1EBF2E8 | 4 | R/W | Init/shutdown state machine (written in Phase 9) | [V] |

### Ordered callees (with tags)

| RVA | What | Tag |
|-----|------|-----|
| ebdb740 | QueryPerformanceCounter (QPC timestamp) | [V] |
| ebdbc60 | WaitForSingleObject on ctx+0x80 (semaphore wait) | [V] |
| ebdbc50 | ReleaseSemaphore on ctx+0x100 (semaphore post) | [V] |
| bc68e40 | Process command buffer (pre-commands at Frame+0xDC5818) | [V] |
| bc68e40 | Process command buffer (post-commands at Frame+0xE05820) | [V] |
| RendererContext vtable +0x48 (slot 9) | Device notify / init callback | [V] |
| RendererContext vtable +0x30 (slot 6) | Device reset notify | [V] |
| RendererContext vtable +0x1A8 (slot 53) | Device reset/resize notify | [V] |
| RendererContext vtable +0x38 (slot 7) | Post-wait device notify | [V] |
| RendererContext vtable +0x28 (slot 5) | Capability query? | [V] |
| RendererContext vtable +0x8 (slot 1) | Get caps? | [V] |
| RendererContext vtable +0x190 (slot 50) | **submit(Frame*)** - THE FRAME RENDER CALL | [V] |
| RendererContext vtable +0x40 (slot 8) | Flush/wait idle? | [V] |
| bc68840 | Create/initialize RendererContextD3D12 | [V] |
| bc63690 | Context::init (called from shutdown path) | [V] |
| bc63b80 | Shutdown helper | [I] |
| bc63c80 | TextVideoMemBlitter/debug font setup | [I] |
| bc5f110 | Error logging | [V] |
| e951550 | __security_check_cookie failure handler | [V] |

**Key identifications:**
- **Semaphore wait**: `ebdbc60` at `bc6322f` on `ctx+0x80`
- **Semaphore post**: `ebdbc50` at `bc633da` on `ctx+0x100` (edx=1)
- **Frame-render call**: RendererContext vtable slot 50 (`+0x190`) at `bc633af` - this is `submit(Frame*)`
- **Swap/present call**: NOT in this function. Present is in RendererContext slot 6 (`e811fb0`, per 6ay). The render thread calls submit; the API thread calls frame()/swap which eventually calls present.

---

## Step 4: Loop structure description

The render thread procedure is **NOT** at 0xbc63150. Per BGFX_MAP 6as and callers list:
- `0xbc65720` = thread entry (`bgfx - renderer backend thread`)
- `0xbc63150` = `Context::renderFrame(int32_t msecs)` - single frame step
- Thread proc loops: `while (renderFrame(5000) != 3) ;` // 3 = Exiting

### renderFrame (0xbc63150) internal structure:

**Entry** (bc63150):
- Save registers, setup stack cookie
- Clear reset flag bit 0x40000 in Frame+0xDC5810
- Handle init-state flag (ctx+0x1EBF2EE) -> call RendererContext slot 9

**Wait** (bc63215..bc6326D):
```
if (ctx+0x1EBF2F1 == 0) {           // not shutting down
    t0 = QPC();
    wait_result = WaitForSingleObject(ctx+0x80, timeout);  // semaphore "frame data ready"
    if (wait_result != WAIT_OBJECT_0) return 2;            // Timeout
    t1 = QPC();
    Frame+0xE746C8 = t1 - t0;          // record wait duration
    Frame(prev)+0xE60E40 = Frame+0xE746C8;  // copy to previous frame
}
```
- Jump: `bc6323d  je bc63480` (timeout -> exit with return 2)

**Work** (bc6326E..bc633DA):
- Post-wait reset/device notifications (slots 7, 5, 1, 53)
- Process pre-command buffer: `bc68e40(ctx, Frame+0xDC5818)`
- **If reset requested**: CALL RendererContext slot 50 (**submit**) at `bc633af`
- Process post-command buffer: `bc68e40(ctx, Frame+0xE05820)`
- Signal semaphore: `ReleaseSemaphore(ctx+0x100, 1)` at `bc633da` - "frame consumed"

**Signal & Exit Condition** (bc633DF..bc6349E):
```
if (ctx+0x1EBF2F0 == 1) {              // shutdown complete flag
    // ...final reset notifications (slots 6, 53, 8)...
}
return (ctx+0x1EBF2EF == 0) ? 1 : 3;   // 1=Render, 3=Exiting
```
- Jump: `bc633ED  jne bc6344B` (shutdown complete -> final cleanup)
- Jump: `bc63479  lea eax,[rax*2+1]` computes return: `eax = byte*2+1` -> 0->1, 1->3
- Normal return: `1` (Render) at `bc6349E`
- Timeout return: `2` at `bc63480` (via `je bc63480` at `bc6323D`)
- Exiting return: `3` when shutdown state byte is 1

### Thread loop (0xbc65720) - from BGFX_MAP 6as:
```
loop:
    result = renderFrame(5000);  // 0xbc63150
    if (result == 3) break;      // Exiting
    // continue
```

---

## Verification status

- [x] Preflight run and read
- [x] BGFX_MAP 6as read
- [x] Instruction-complete listing (all 861 bytes / ~300 instructions covered in phases)
- [x] [reg+off] read/write table
- [x] Ordered callees with semaphore wait/post, submit, swap identification
- [x] Loop structure with quoted jumps

## TOOL REQUESTS

None - all analysis done with existing tools (preflight, disrange, BGFX_MAP).