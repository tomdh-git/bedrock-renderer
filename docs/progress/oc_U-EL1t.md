## NEXT
DONE

# Unit U-EL1t: 0xbc63150 renderFrame internals — field map

## Step 1: Field access table from 0xbc63150 disassembly

Source: `docs/progress/pre/0xbc63150.md` (preflight listing from rdis).
Function range: `0xbc63150..0xbc634ad` (size 0x35d = 861 bytes).
Arguments: rcx = ctx, rsi = ctx (copy), edx = timeout.

One row per distinct context/frame/renderer offset accessed, with all instruction sites listed.
Sizes come from the instruction (movups/movaps 16, qword 8, dword 4, word 2, byte 1).
`lea` computes an address (no memory size). Proof lines copied verbatim from the input data.

| Field | Size | Offset | R/W | `0xRVA  instr` proof line(s) | Meaning + Tag |
|-------|------|--------|-----|------------------------------|---------------|
| ctx+0x1CFD0C0 (Frame* current submit buffer) | 8 | 0x1CFD0C0 | R | `0xbc6316e  mov rax,[rcx+0x1CFD0C0]`<br>`0xbc6324b  mov rcx,[rsi+0x1CFD0C0]`<br>`0xbc63358  mov rax,[rsi+0x1CFD0C0]`<br>`0xbc63371  add rdx,[rsi+0x1CFD0C0]`<br>`0xbc633ba  add rdx,[rsi+0x1CFD0C0]` | [V] |
| Frame+0xDC5810 (reset flags word) | 4 | 0xDC5810 | R/W | `0xbc63175  mov ebp,[rax+0xDC5810]`<br>`0xbc63183  mov [rax+0xDC5810],ecx` | [V] bit 0x40000 cleared in prologue |
| ctx+0x1EBF2EE (init-state flag byte) | 1 | 0x1EBF2EE | R/W | `0xbc63189  cmp byte ptr [rsi+0x1EBF2EE],1`<br>`0xbc631a6  mov byte ptr [rsi+0x1EBF2EE],0`<br>`0xbc6346b  mov byte ptr [rsi+0x1EBF2EE],1` | [V] 1=needs vtable slot 9 call, cleared after |
| ctx+0x1EBF2D0 (RendererContext* pointer) | 8 | 0x1EBF2D0 | R/W | `0xbc63192  mov rcx,[rsi+0x1EBF2D0]`<br>`0xbc631cf  mov rcx,[rsi+0x1EBF2D0]`<br>`0xbc6327b  mov rcx,[rsi+0x1EBF2D0]`<br>`0xbc6328f  mov rcx,[rsi+0x1EBF2D0]`<br>`0xbc632ab  mov rcx,[rsi+0x1EBF2D0]`<br>`0xbc63389  mov rcx,[rsi+0x1EBF2D0]`<br>`0xbc633fc  mov rcx,[rsi+0x1EBF2D0]`<br>`0xbc6342d  mov rcx,[rsi+0x1EBF2D0]`<br>`0xbc63457  mov rcx,[rsi+0x1EBF2D0]`<br>`0xbc63345  mov [rsi+0x1EBF2D0],rax` | [V] renderer object, overwritten by bc68840 |
| renderer+0x0 (vtable read) | 8 | renderer+0x0 | R | `0xbc63199  mov rax,[rcx]`<br>`0xbc631d6  mov rax,[rcx]`<br>`0xbc63205  mov rax,[rcx]`<br>`0xbc63282  mov rax,[rcx]`<br>`0xbc63296  mov rax,[rcx]`<br>`0xbc632b7  mov rax,[rcx]`<br>`0xbc633a5  mov rax,[rcx]`<br>`0xbc63403  mov rax,[rcx]`<br>`0xbc63434  mov rax,[rcx]`<br>`0xbc6345e  mov rax,[rcx]` | [V] load vtable pointer from renderer object |
| ctx+0x1EBF19C (reset flags copy dword) | 4 | 0x1EBF19C | R | `0xbc631ad  mov r14d,[rsi+0x1EBF19C]` | [V] bit 0x800000 = device reset |
| ctx+0x1EBF2F0 (shutdown-in-progress flag byte) | 1 | 0x1EBF2F0 | R | `0xbc631b4  cmp byte ptr [rsi+0x1EBF2F0],0`<br>`0xbc633e6  cmp byte ptr [rsi+0x1EBF2F0],1` | [V] |
| ctx+0x1EBF2EC (reset requested flag byte) | 1 | 0x1EBF2EC | R | `0xbc631bd  cmp byte ptr [rsi+0x1EBF2EC],1`<br>`0xbc631ec  cmp byte ptr [rsi+0x1EBF2EC],1`<br>`0xbc6326e  cmp byte ptr [rsi+0x1EBF2EC],1`<br>`0xbc63380  cmp byte ptr [rsi+0x1EBF2EC],1`<br>`0xbc633df  movzx eax,byte ptr [rsi+0x1EBF2EC]`<br>`0xbc63444  movzx eax,byte ptr [rsi+0x1EBF2EC]` | [V] |
| ctx+0x1EBF2ED (reset acknowledged flag byte) | 1 | 0x1EBF2ED | R/W | `0xbc631c6  cmp byte ptr [rsi+0x1EBF2ED],0`<br>`0xbc631f5  cmp byte ptr [rsi+0x1EBF2ED],0`<br>`0xbc633f3  cmp byte ptr [rsi+0x1EBF2ED],0`<br>`0xbc63424  cmp byte ptr [rsi+0x1EBF2ED],0`<br>`0xbc63366  mov [rsi+0x1EBF2ED],al` | [V] written from Frame+0xE74989 |
| renderer+0x48 (vtable slot 9) | 8 | renderer+0x48 | R | `0xbc6319c  mov rax,[rax+0x48]` | [V] init-state notify callback |
| renderer+0x30 (vtable slot 6) | 8 | renderer+0x30 | R | `0xbc631d9  mov rax,[rax+0x30]`<br>`0xbc63406  mov rax,[rax+0x30]` | [V] device reset notify |
| renderer+0x1A8 (vtable slot 53) | 8 | renderer+0x1A8 | R | `0xbc63208  mov rax,[rax+0x1A8]`<br>`0xbc63437  mov rax,[rax+0x1A8]` | [V] device reset/resize notify |
| ctx+0x80 (semaphore wait gate "frame data ready") | - | 0x80 | LEA | `0xbc63226  lea rcx,[rsi+0x80]` | [V] address passed to ebdbc60 (WaitForSingleObject) |
| ctx+0x1CFD0C8 (Frame* previous double buffer) | 8 | 0x1CFD0C8 | R | `0xbc63259  mov rax,[rsi+0x1CFD0C8]` | [V] |
| Frame+0xE746C8 (render thread wait duration qword) | 8 | 0xE746C8 | R/W | `0xbc63252  mov [rcx+0xE746C8],rax`<br>`0xbc63260  mov rcx,[rax+0xE746C8]` | [V] t1-t0 wait stat |
| Frame+0xE60E40 (previous frame wait duration qword) | 8 | 0xE60E40 | W | `0xbc63267  mov [rax+0xE60E40],rcx` | [V] copy of previous frame's wait |
| renderer+0x38 (vtable slot 7) | 8 | renderer+0x38 | R | `0xbc63285  mov rax,[rax+0x38]` | [V] post-wait device notify |
| renderer+0x28 (vtable slot 5) | 8 | renderer+0x28 | R | `0xbc63299  mov rax,[rax+0x28]` | [V] capability query |
| renderer+0x8 (vtable slot 1) | 8 | renderer+0x8 | R | `0xbc632ba  mov rax,[rax+8]` | [V] get caps |
| Frame+0xE74989 (byte) | 1 | 0xE74989 | R | `0xbc6335f  movzx eax,byte ptr [rax+0xE74989]` | [V] copied to ctx+0x1EBF2ED |
| renderer+0x190 (vtable slot 50 = submit) | 8 | renderer+0x190 | R | `0xbc633a8  mov rax,[rax+0x190]` | [V] **submit(Frame*)** — the frame render call |
| ctx+0x1EBF2F1 (shutdown state byte) | 1 | 0x1EBF2F1 | R | `0xbc63215  cmp byte ptr [rsi+0x1EBF2F1],0`<br>`0xbc633c9  cmp byte ptr [rsi+0x1EBF2F1],0` | [V] 0=running, skips semaphore wait when 1 |
| ctx+0x1EBF2EF (shutdown byte for return value) | 1 | 0x1EBF2EF | R | `0xbc63472  movzx eax,byte ptr [rsi+0x1EBF2EF]` | [V] return = byte*2+1 (0->1 Render, 1->3 Exiting) |
| renderer+0x40 (vtable slot 8) | 8 | renderer+0x40 | R | `0xbc63461  mov rax,[rax+0x40]` | [V] flush/wait idle |
| rsp+0x68 (stack security cookie) | 8 | 0x68 | R/W | `0xbc63169  mov [rsp+0x68],rax`<br>`0xbc63480  mov rcx,[rsp+0x68]`<br>`0xbc6349f  mov rcx,[rsp+0x68]` | [V] stack cookie |
| 0x1230A0C0 (security cookie data) | 8 | 0x1230A0C0 | R | `0xbc6315f  mov rax,[0x1230A0C0]`<br>`0xbc63488  mov rdx,[0x1230A0C0]` | [V] global security cookie |

## Step 2: Semaphores and surface array stride

**Semaphore ctx+0x80 (frame data ready / wait gate):** Directly accessed in 0xbc63150.
- `0xbc63226  lea rcx,[rsi+0x80]` computes the address, passed to `call 0xEBDBC60` at `0xbc6322f` (WaitForSingleObject with timeout=edi). Timeout (return != 0) leads to `0xbc6323d  je 0xBC63480` → return 2 (Timeout). [V]

**Semaphore ctx+0x100 (frame consumed / post gate):** NOT directly addressed as `[reg+0x100]` anywhere in 0xbc63150's disassembly. The post is performed by `call 0xEBDBC50` at `0xbc633da` with `rcx=rsi` (=ctx) and `edx=1`. Per BGFX_MAP 6as [V], `0xebdbc50(.., 1)` signals the "frame consumed" semaphore at ctx+0x100, but the +0x100 offset itself is not a memory operand in this function — it is read inside `0xebdbc50`.

**Surface array stride 0x700 (ctx+0x13D18):** Not referenced anywhere in 0xbc63150's disassembly. Per BGFX_MAP line 752 [V], `ctx+0x13D18` stride 0x700 is accessed in `0xbc65800` (the API-side `Context::frame`), not in `0xbc63150`.

**Return value:** `0xbc63479  lea eax,[rax*2+1]` where al = byte [rsi+0x1EBF2EF] → 0→1 (Render), 1→3 (Exiting). [V]

**Key callees (from preflight callees list):** `ebdb740` x2 (QPC), `ebdbc60` x1 (semaphore wait ctx+0x80), `ebdbc50` x1 (semaphore post ctx+0x100), `bc68e40` x2 (command buffer pre/post), `bc68840` x1 (renderer context init), `e951550` x1 (security cookie failure). Indirect vtable calls: slots 1,5,6,7,8,9,50,53. [V]

### Standalone verified instruction samples

0xbc63226  lea rcx,[rsi+0x80]
0xbc6322f  call 0xEBDBC60
0xbc633da  call 0xEBDBC50
0xbc633a8  mov rax,[rax+0x190]
0xbc63479  lea eax,[rax*2+1]

CLOSES? NO — the semaphore ctx+0x100 post and the surface array stride 0x700 (ctx+0x13D18) cannot be proven by [V] rows from 0xbc63150's disassembly alone: ctx+0x100 is not a `[reg+0x100]` memory operand in this function (only reached via `call 0xEBDBC50` at 0xbc633da), and ctx+0x13D18/stride 0x700 does not appear in 0xbc63150 at all (it is in 0xbc65800 per BGFX_MAP 752). All other pending internals of 0xbc63150 are proven by [V] rows above.

## TOOL REQUESTS

None — all data from preflight listing, rdis, BGFX_MAP 6as/751-754, and RENDER_CHECKLIST L1t line.
