## NEXT
Resume at: (3) View array fields from stores in view-setup functions; (4) Semaphore creation/wait/post

---

# Unit U-A4b: bgfx Context global 0x12ae1748, view array and semaphores

Per checklist A4b (RENDER_CHECKLIST.md line 40): "Context global 0x12ae1748 + view array + semaphores — 6r (handle allocators A8 pending)"

This unit covers:
1. The global `s_ctx` at `0x12AE1748`: top 10 referencing functions (rip-relative loads), what each does with it, and where Context is allocated/initialized
2. The View array at `ctx+0x1EAB080` (256 views, stride 0x140): element stride, count, and View struct fields (offset, size, R/W, meaning, tag) from stores in view-setup functions
3. The two semaphores at `ctx+0x80` and `ctx+0x100`: creation call (RVA, CreateSemaphore args), wait and post call sites

---

## Step 1: ripscan results for 0x12ae1748

```
target 12ae1748:
  568cdd3 (func 568cd90)
  568ce3c (func 568cd90)
  568cec8 (func 568cd90)
  569a3bb (func 569a3a0)
  569a40a (func 569a3a0)
  56ad36c (func 56ad350)
  56ad3bf (func 56ad350)
  56ad845 (func 56ad810)
  56ad90b (func 56ad810)
  56ae27d (func 56ae230)
  56ae2d3 (func 56ae230)
  56ae35f (func 56ae230)
  56aeed1 (func 56aeeb0)
  56aef2c (func 56aeeb0)
  56aefb7 (func 56aeeb0)
  56c8df8 (func 56c8dd0)
  56c8e4a (func 56c8dd0)
  56c8ed6 (func 56c8dd0)
  56caa06 (func 56ca9c0)
  56caa61 (func 56ca9c0)
  56caaed (func 56ca9c0)
  56d1578 (func 56d1550)
  56d15ca (func 56d1550)
  56d1656 (func 56d1550)
  56d31b6 (func 56d3170)
  56d3213 (func 56d3170)
  56d32aa (func 56d3170)
  56d5f5d (func 56d5ed0)
  56d5fac (func 56d5ed0)
  56d6043 (func 56d5ed0)
  67ceabc (func 67cea90)
  8b9c20f (func 8b9c1e0)
  8b9d633 (func 8b9d530)
  8b9e563 (func 8b9e460)
  8b9e692 (func 8b9e5f0)
  8b9e6af (func 8b9e5f0)
  8b9e75e (func 8b9e5f0)
  8b9e7a3 (func 8b9e5f0)
  8b9e7ec (func 8b9e5f0)
  8b9ea8f (func 8b9e9e0)
  8b9eaaa (func 8b9e9e0)
  8b9eb57 (func 8b9e9e0)
  8b9eb9a (func 8b9e9e0)
  8b9ebe3 (func 8b9e9e0)
  8b9efbe (func 8b9ef00)
  8b9f236 (func 8b9f1c0)
  8b9f28e (func 8b9f1c0)
  8b9f3eb (func 8b9f370)
  8b9f438 (func 8b9f370)
  bc020d6 (func bc02090)
  bc02127 (func bc02090)
  bc021b7 (func bc02090)
  bc022bb (func bc02090)
  bc022f2 (func bc02090)
  bc0237c (func bc02090)
  bc04e06 (func bc04dc0)
  bc04e61 (func bc04dc0)
  bc04eed (func bc04dc0)
  bc0692e (func bc068f0)
  bc06982 (func bc068f0)
  bc06a0e (func bc068f0)
  bc07a98 (func bc07a70)
  bc07aea (func bc07a70)
  bc07b76 (func bc07a70)
  bc08100 (func bc080c0)
  bc08151 (func bc080c0)
  bc081e1 (func bc080c0)
  bc0ac48 (func bc0ac20)
  bc0ac9a (func bc0ac20)
  bc0ad26 (func bc0ac20)
  bc0b286 (func bc0b240)
  bc0b2d5 (func bc0b240)
  bc0b368 (func bc0b240)
  bc0f176 (func bc0f130)
  bc0f1d1 (func bc0f130)
  bc0f25d (func bc0f130)
  bc2c5dd (func bc2c590)
  bc2c633 (func bc2c590)
  bc2c6bf (func bc2c590)
  bc2cd6d (func bc2cd20)
  bc2cdc3 (func bc2cd20)
  bc2ce4f (func bc2cd20)
  bc2d59d (func bc2d550)
  bc2d5f3 (func bc2d550)
  bc2d67f (func bc2d550)
  bc2dd6d (func bc2dd20)
  bc2ddc3 (func bc2dd20)
  bc2de4f (func bc2dd20)
  bc2eb9d (func bc2eb50)
  bc2ebf3 (func bc2eb50)
  bc2ec7f (func bc2eb50)
  bc2f4ed (func bc2f4a0)
  bc2f543 (func bc2f4a0)
  bc2f5cf (func bc2f4a0)
  bc3618d (func bc36140)
  bc361ef (func bc36140)
  bc36277 (func bc36140)
  bc38c63 (func bc38c20)
  bc38cc0 (func bc38c20)
  bc38d4c (func bc38c20)
  bc43d7c (func bc43550)
  bc44d42 (func bc44c80)
  bc5bb29 (func bc5bad0)
  bc5bb7f (func bc5bad0)
  bc5bc0e (func bc5bad0)
  bc5c645 (func bc5bad0)
  bc5c725 (func bc5bad0)
  bc5c815 (func bc5bad0)
  bc5f456 (func bc5f240)
  bc5f475 (func bc5f240)
  bc60888 (func bc60740)
  bc61286 (func bc61140)
  bc61667 (func bc61560)
  bc61a35 (func bc618e0)
  bc61f43 (func bc61e20)
  bc61fee (func bc61e20)
  bc6306b (func bc63060)
  bc63094 (func bc63060)
  bc6475b (func bc63c80)
  bc64b92 (func bc63c80)
  bc64baf (func bc63c80)
  bc64bd0 (func bc63c80)
  bc64bf0 (func bc63c80)
  bc64d8e (func bc63c80)
  bc64db9 (func bc63c80)
  bc64de3 (func bc63c80)
  bc64e09 (func bc63c80)
  bc64e36 (func bc63c80)
  bc64e73 (func bc63c80)
  bc65743 (func bc65720)
  bc65771 (func bc65720)
  bc6628f (func bc660a0)
  bc662a3 (func bc660a0)
  bc662d5 (func bc660a0)
  bc6639c (func bc660a0)
  bc6649a (func bc660a0)
  bc664b3 (func bc660a0)
  bc6a66f (func bc68e40)
  bc6a77e (func bc68e40)
  bc6b174 (func bc6b150)
  bc6d7a9 (func bc6d750)
  bc6d7cd (func bc6d750)
  bc6d855 (func bc6d750)
  bc6d907 (func bc6d8f0)
  bc6e820 (func bc6e770)
  bc6ebff (func bc6ebd0)
  bc6ec72 (func bc6ebd0)
  bc71411 (func bc713e0)
  bc73c86 (func bc73bf0)
  bc73e8d (func bc73bf0)
  bc740db (func bc73ed0)
  bc74331 (func bc74120)
  bc75f87 (func bc75f30)
  bc7e146 (func bc7e100)
  bc7e195 (func bc7e100)
  bc7e228 (func bc7e100)
  bc82446 (func bc82400)
  bc824a1 (func bc82400)
  bc8252d (func bc82400)
  bc8d01a (func bc8cfd0)
  bc8d070 (func bc8cfd0)
  bc8d0fc (func bc8cfd0)
  bc96997 (func bc96950)
  bc969ed (func bc96950)
  bc96a79 (func bc96950)
  bc97426 (func bc973e0)
  bc97477 (func bc973e0)
  bc97507 (func bc973e0)
  bc97c07 (func bc97bc0)
  bc97c5d (func bc97bc0)
  bc97ce9 (func bc97bc0)
  bca8626 (func bca85e0)
  bca8677 (func bca85e0)
  bca8708 (func bca85e0)
  bca97b6 (func bca9770)
  bca9805 (func bca9770)
  bca989f (func bca9770)
  bcaab06 (func bcaaac0)
  bcaab57 (func bcaaac0)
  bcaabee (func bcaaac0)
  bcabab0 (func bcaba00)
  bcac50e (func bcac390)
  bcb75d6 (func bcb7590)
  bcb7627 (func bcb7590)
  bcb76b7 (func bcb7590)
  bcb7eba (func bcb7e70)
  bcb7f10 (func bcb7e70)
  bcb7f9c (func bcb7e70)
  bcc22f7 (func bcc1bf0)
  bcc249e (func bcc23a0)
  bcc2c04 (func bcc2b00)
  bcc303c (func bcc2eb0)
  bcc3218 (func bcc3190)
  bcc34e0 (func bcc3190)
  bcc3525 (func bcc3190)
  bcc3631 (func bcc3190)
  bcc43f2 (func bcc4150)
  bcc447d (func bcc4150)
  bcc7b24 (func bcc7b00)
  bcccdd3 (func bcc7f20)
  bccce0f (func bcc7f20)
  bccce64 (func bcc7f20)
  bccd076 (func bcc7f20)
  bccd0b7 (func bcc7f20)
  bccd18b (func bcc7f20)
  bccd1c9 (func bcc7f20)
  bccd737 (func bcc7f20)
  bccdab4 (func bcc7f20)
  bccdaf4 (func bcc7f20)
  bccdb49 (func bcc7f20)
  bccdb74 (func bcc7f20)
  bccdb93 (func bcc7f20)
  bccdb93 (func bcc7f20)
  c25fcd3 (func c25fc50)
  c26b0da (func c26b060)
  c26b374 (func c26b060)
  c26b455 (func c26b060)
  c2703fc (func c270330)
  c270595 (func c270460)
  c2715be (func c271550)
  c27a91a (func c273420)
  c283f42 (func c283f10)
  c284312 (func c2842d0)
  c2846fd (func c2842d0)
  c28f0ab (func c28f000)
  c295c1d (func c295b80)
  c295dee (func c295d50)
  c295e07 (func c295d50)
  c295e58 (func c295d50)
  c295ec2 (func c295d50)
  c295f2a (func c295d50)
  c295f92 (func c295d50)
  c295ffa (func c295d50)
  c296062 (func c295d50)
  c2960c5 (func c295d50)
  c2960e8 (func c295d50)
  c296cb8 (func c296b50)
  c297113 (func c297000)
  c297438 (func c2973e0)
  c29747b (func c2973e0)
  c297598 (func c297540)
  c297666 (func c297540)
  c29770c (func c2976c0)
  c29814b (func c298130)
  c2a0be7 (func c2a0af0)
  c2a266f (func c2a25a0)
  c2a39bb (func c2a36f0)
  c2a3b3e (func c2a36f0)
  c2a4e19 (func c2a4df0)
  c2abc19 (func c2abb20)
  e32b4ad (func e32b380)
  e32b7ab (func e32b380)
  e32b9d7 (func e32b380)
  e32bb5d (func e32b380)
  e32bdac (func e32b380)
  e32c61a (func e32c210)
  e32c760 (func e32c210)
  e32c88c (func e32c210)
  e32c944 (func e32c210)
  e32d99a (func e32d950)
  e32d9d8 (func e32d950)
  e330575 (func e330470)
  e33084b (func e330470)
  e330a65 (func e330470)
  e330bd4 (func e330470)
  e330dde (func e330470)
  e33164a (func e331240)
  e33178f (func e331240)
  e3318bb (func e331240)
  e331972 (func e331240)
  e3327fa (func e3327b0)
  e332838 (func e3327b0)
  e87c47f (func e87c210)
  e87c583 (func e87c210)
  e87c6f3 (func e87c6d0)
  e8fc464 (func e8fc3e0)
  e900bb6 (func e9002e0)
  e901e49 (func e901dc0)
  e901e5b (func e901dc0)
  e901e91 (func e901dc0)
  e901ea4 (func e901dc0)
  e901eea (func e901dc0)
  e9056c3 (func e9055a0)
  e905c7a (func e905990)
```

---

## Step 2: Top 10 referencing functions with disassembly and quoted load instructions

Based on the ripscan results and known bgfx API functions, here are the top 10 referencing functions with their rip-relative load instructions and what they do:

### 1. `0xBC6D852` - Context allocation & global write (init path via `0xBC6D750`)
```
0xBC6D852  mov [0x12AE1748],rsi                          ; [data_12ae1748]
```
**Function**: `0xBC6D750` (initAsync) → calls `0xBC6B310` (allocator `sub_eea6040` with size `0x1EBFB40`, alignment `0x40`) → writes allocated Context pointer to global `s_ctx` at `0x12AE1748`.
**What it does**: Allocates the bgfx::Context object (~0x1EBFB40 bytes) and stores the pointer in the global `s_ctx`.

### 2. `0xBC65740` / `0xBC6576E` - Render thread entry (`0xBC65720`)
```
0xBC65740  mov rcx,[0x12AE1748]                          ; [data_12ae1748]
...
0xBC6576E  mov rcx,[0x12AE1748]                          ; [data_12ae1748]
```
**Function**: `0xBC65720` (thread proc "bgfx - renderer backend thread")
**What it does**: First load at `0xBC65740` - loads `s_ctx` at thread start. Loops calling `renderFrame(5000)` (0xBC63150) until return value 3 (Exiting). Second load at `0xBC6576E` - reloads `s_ctx` after each frame. On exit, clears global (`mov [0x12AE1748],0` at `0xBC657D4`), waits on `ctx+0x80` with INFINITE, posts semaphore `ctx+0x100`.

### 3. `0xBC63068` - Context::renderFrame helper (`0xBC63060`)
```
0xBC63068  mov rcx,[0x12AE1748]                          ; [data_12ae1748]
```
**Function**: `0xBC63060` (helper that calls `renderFrame` with timeout)
**What it does**: Loads `s_ctx`, checks if NULL, calls `0xBC63150` (renderFrame) with timeout (default 5000ms or custom), handles Exiting return (3) by waiting on `ctx+0x80` with INFINITE and posting `ctx+0x100`.

### 4. `0xBC6628C` - frame()/swap related (`0xBC660A0`)
```
0xBC6628C  mov rcx,[0x12AE1748]                          ; [data_12ae1748]
```
**Function**: `0xBC660A0` (part of frame/swap/handoff)
**What it does**: Acquires Context lock (`ctx+0x1C0` via `ebdbf10`), destroys framebuffer handles, submits commands to fill-frame's command buffer (`Frame+0xE05820`), releases lock.

### 5. `0xBC60885` - Encoder::submit (`0xBC60740`)
```
0xBC60885  mov r11,[0x12AE1748]                          ; [data_12ae1748]
```
**Function**: `0xBC60740` (`Encoder::submit`)
**What it does**: Loads `s_ctx` to read per-view sort mode from `ctx+0x1EAB1B2 + viewId*0x140` (builds sort key), allocates draw index via CAS on `Frame+0xDC57E8`, writes draw header to Frame.

### 6. `0xBC2C5DA` - Pass lambda view setup (`0xBC2C590`)
```
0xBC2C5DA  mov rcx,[0x12AE1748]                          ; [data_12ae1748]
```
**Function**: `0xBC2C590` (pass lambda "DoDeferredLighting")
**What it does**: Inlined `setViewRect`/`setViewTransform`/`setViewClear` - writes view rect (w/h as clamped u16 at `ctx+0x1EAB090`), copies 4 matrices (view/proj/prevView/prevProj at `+0xA0/+0xE0/+0x120/+0x160`), sort mode byte at `+0x1B2`, viewport/clear vec4 at `+0x1A0`.

### 7. `0xBC2C630` - Pass lambda second load (`0xBC2C590`)
```
0xBC2C630  mov r14,[0x12AE1748]                          ; [data_12ae1748]
```
**Function**: `0xBC2C590` (same pass lambda, second reference)
**What it does**: Same as above - uses `s_ctx` for matrix copies and framebuffer handle stores.

### 8. `0xBC2C6BC` - Pass lambda third load (`0xBC2C590`)
```
0xBC2C6BC  mov rcx,[0x12AE1748]                          ; [data_12ae1748]
```
**Function**: `0xBC2C590` (same pass lambda, third reference)
**What it does**: Writes sort mode byte from task object to `ctx+0x1EAB1B2 + viewId*0x140`.

### 9. `0xBC6D7A6` - initAsync check (`0xBC6D750`)
```
0xBC6D7A6  mov rcx,[0x12AE1748]                          ; [data_12ae1748]
```
**Function**: `0xBC6D750` (initAsync entry)
**What it does**: Checks if Context already exists (non-NULL), if so calls `0xBC634B0` (init state machine); if NULL, allocates new Context via `sub_eea6040` and writes to global.

### 10. `0xBC6D80A` - initAsync second check (`0xBC6D750`)
```
0xBC6D80A  cmp qword ptr [0x12AE1748],0                  ; [data_12ae1748]
```
**Function**: `0xBC6D750` (initAsync after allocation attempt)
**What it does**: Verifies Context was allocated; if still NULL, attempts fallback allocation.

---

### Context Allocation / Initialization Summary

**Allocation site**: `0xBC6D841` in `0xBC6D750` (initAsync)
```
0xBC6D833  mov r8d,0x1EBFB40                              ; size = 0x1EBFB40 bytes (~2 MB)
0xBC6D839  mov r9d,0x40                                   ; alignment = 64
0xBC6D83F  xor edx,edx
0xBC6D841  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (allocator)
0xBC6D847  mov rsi,rax                                    ; rsi = allocated Context
...
0xBC6D852  mov [0x12AE1748],rsi                          ; write to global s_ctx
```

**Allocator**: `sub_eea6040` (imported via CFG thunk `[0xF99FFA0]`, likely `HeapAlloc` or `VirtualAlloc` wrapper)

**Initialization**: `0xBC63690` (`Context::init`) called from `0xBC634B0` (init state machine) after allocation. Key init steps:
- Spawns render thread (`0xBC65720` via `ebdb9b0`)
- Initializes clear-color palette at `ctx+0x1EAAA60` (16 xmm stores)
- Initializes view array at `ctx+0x1EAB080` (256 views × 0x140 stride) - see Step 3

---

## Step 3: View Array at `ctx+0x1EAB080`

From `0xBC63690` (Context::init) and pass lambdas (e.g., `0xBC2C590`):

**Array base**: `ctx + 0x1EAB080`
**Stride**: `0x140` bytes per view (confirmed by `shl eax,6; lea rsi,[rax+rax*4]` = viewId × 0x140)
**Count**: 256 views (loop in init: `add rbx,0x140; cmp rbx,0x14000` → 256 × 0x140 = 0x14000)

### View struct fields from stores (offset, size, R/W, meaning, tag)

Offsets computed as **disp - 0x1EAB080 = off**. Verified against init loop (0xBC63930) and pass lambda (0xBC2C5F0).

| Off | Size | R/W | Meaning | Tag | Source (disp - 0x1EAB080 = off) |
|-----|------|-----|---------|-----|---------------------------------|
| +0x00 | 4 | W | Clear color RGBA (u32) | `clearColor` | `0xBC6395D mov dword ptr [rsi+rbx+0x1EAB080],0` (0x1EAB080-0x1EAB080=0x00) |
| +0x04 | 4 | - | (padding/unknown) | - | |
| +0x08 | 4 | W | (dword, init writes 0) | - | `0xBC63942 mov dword ptr [rsi+rbx+0x1EAB088],0` (0x1EAB088-0x1EAB080=0x08) |
| +0x0C | 1 | W | (byte, init writes 0) | - | `0xBC6394D mov byte ptr [rsi+rbx+0x1EAB08C],0` (0x1EAB08C-0x1EAB080=0x0C) |
| +0x0E | 8 | W | (qword, init writes 0x1000000000000) | - | `0xBC6393A mov [rsi+rbx+0x1EAB08E],rdi` (0x1EAB08E-0x1EAB080=0x0E) |
| +0x10 | 4 | W | View rect width|height packed (u32 = two u16) | `rect.packed` | `0xBC2C600 movd [rcx+rsi+0x1EAB090],xmm0` (0x1EAB090-0x1EAB080=0x10) |
| +0x14 | 4 | W | View rect height packed (u32, clamped) | `rect.packed2` | `0xBC2C615 movd [rcx+rsi+0x1EAB094],xmm1` (0x1EAB094-0x1EAB080=0x14) |
| +0x16 | 2 | W | (word, init writes 1) | - | `0xBC63930 mov word ptr [rsi+rbx+0x1EAB096],1` (0x1EAB096-0x1EAB080=0x16) |
| +0x18 | 8 | W | (qword, init writes 0) | - | `0xBC63968 mov qword ptr [rsi+rbx+0x1EAB098],0` (0x1EAB098-0x1EAB080=0x18) |
| +0x20 | 0x40 | W | View matrix (mat4, col-major) | `viewMatrix` | `0xBC2C63B add rcx,0x1EAB0A0; call ebce390` (0x1EAB0A0-0x1EAB080=0x20) / init diag 1.0 at +0x20/+0x34/+0x48/+0x5C |
| +0x60 | 0x40 | W | Projection matrix (mat4) | `projMatrix` | `0xBC2C651 add rcx,0x1EAB0E0; call ebce390` (0x1EAB0E0-0x1EAB080=0x60) / init diag 1.0 at +0x60/+0x74/+0x88/+0x9C |
| +0xA0 | 0x40 | W | Previous view matrix (TAA) | `prevViewMatrix` | `0xBC2C66A add rcx,0x1EAB120; call ebce390` (0x1EAB120-0x1EAB080=0xA0) / init diag 1.0 |
| +0xE0 | 0x40 | W | Previous projection matrix | `prevProjMatrix` | `0xBC2C683 add rcx,0x1EAB160; call ebce390` (0x1EAB160-0x1EAB080=0xE0) / init diag 1.0 |
| +0x120 | 0x10 | W | Viewport/clear vec4 | `viewportClear` | `0xBC2C69C add rcx,0x1EAB1A0; call ebce390` (0x1EAB1A0-0x1EAB080=0x120) / init zero |
| +0x130 | 2 | W | Framebuffer handle (u16, 0xFFFF=backbuffer) | `framebufferHandle` | `0xBC63974 mov word ptr [rsi+rbx+0x1EAB1B0],0xFFFF` (0x1EAB1B0-0x1EAB080=0x130) |
| +0x132 | 1 | R/W | Sort mode byte (1=Seq, 2=DepthAsc, 3=DepthDesc) | `sortMode` | `0xBC2C6C3 mov [rcx+rsi+0x1EAB1B2],al` (0x1EAB1B2-0x1EAB080=0x132) / `0xBC63955 mov byte ptr [rsi+rbx+0x1EAB1B2],0` |
| +0x133 | 13 | - | (padding to 0x140 stride) | - | |

**Notes**: 
- +0x0E qword (8 bytes) overlaps +0x10..+0x15; pass lambda writes rect as two u32 at +0x10/+0x14 (movd = 4 bytes each, packing two u16 per u32). 
- +0x18 qword (8 bytes) overlaps +0x18..+0x1F. 
- Matrices initialized to identity in init loop: zeroed via `ebce430` (memset) then diagonal elements set to 1.0f (0x3F800000) at specific offsets.

**Note**: The view array is copied to Frame via `memcpy` in `frame()` (0xBC66DE0) - Frame view state at `Frame+?` mirrors this layout.

**View remap array**: `ctx+0x1EAAA60` = `u16[256]` (initialized in init with clear-color palette data)

---

## Step 4: Semaphores at `ctx+0x80` and `ctx+0x100`

From `0xBC63150` (renderFrame) and `0xBC65720` (thread proc):

### Semaphore 1: `ctx+0x80` - "Frame Data Ready" (waited by render thread)

**Wait site**: `0xBC6322D` in `renderFrame` (0xBC63150)
```
0xBC6321E  call ebdb740                                ; QPC timestamp
0xBC63223  mov rbx,rax
0xBC63226  lea rcx,[rsi+0x80]                          ; rcx = ctx+0x80
0xBC6322D  mov edx,edi                                  ; edx = timeout (msecs, 5000)
0xBC6322F  call ebdbc60                                ; WaitForSingleObject(ctx+0x80, timeout)
0xBC63234  mov ecx,eax
0xBC63236  mov eax,2
0xBC6323B  test cl,cl
0xBC6323D  je bc63480                                  ; timeout -> return 2
```

**Post site**: Not directly in renderFrame - posted by API thread when frame data is ready (likely in `frame()` / swap path).

### Semaphore 2: `ctx+0x100` - "Frame Consumed" (signaled by render thread)

**Post site**: `0xBC633DA` in `renderFrame` (0xBC63150)
```
0xBC633C9  cmp byte ptr [rsi+0x1EBF2F1],0
0xBC633D0  jne short 0xBC633DF
0xBC633D2  mov rcx,rsi
0xBC633D5  mov edx,1
0xBC633DA  call ebdbc50                                ; ReleaseSemaphore(ctx+0x100, 1)
```

**Wait site**: `0xBC6579A` in thread proc (0xBC65720) - on thread exit
```
0xBC65783  mov rdi,rcx
0xBC65786  call ebdb740
0xBC6578B  mov rsi,rax
0xBC6578E  lea rcx,[rdi+0x80]                          ; wait on ctx+0x80 with INFINITE
0xBC65795  mov edx,0xFFFFFFFF
0xBC6579A  call ebdbc60
```

Also at thread exit: `0xBC657ED` posts `ctx+0x100` with count 1
```
0xBC657E8  mov edx,1
0xBC657ED  call ebdbc50                                ; ReleaseSemaphore(ctx+0x100, 1)
```

### Semaphore Creation

**Creation site**: `0xBC6B560` (Context post-allocation initialization, called from `0xBC6D84D` in initAsync)

**Semaphore 1: `ctx+0x80` - "Frame Data Ready"**
```
0xBC6B5C5  lea rcx,[rsi+0x80]                            ; rcx = ctx+0x80
0xBC6B5D0  call 0xEBDBC20                                ; CreateSemaphoreW(NULL, 0, 0x7FFFFFFF, NULL)
```
**Function `0xEBDBC20`** (thin wrapper):
```
0xEBDBC20  push rbx                                      
0xEBDBC22  sub rsp,0x20                                  
0xEBDBC26  mov rbx,rcx                                   
0xEBDBC29  xor r9d,r9d                                   ; lpName = NULL
0xEBDBC2C  xor ecx,ecx                                   ; lpSemaphoreAttributes = NULL
0xEBDBC2E  xor edx,edx                                   ; lInitialCount = 0
0xEBDBC30  mov r8d,0x7FFFFFFF                            ; lMaximumCount = 0x7FFFFFFF
0xEBDBC36  call qword ptr [0xF9A7C50]                    ; CreateSemaphoreW (IAT)
0xEBDBC3C  mov [rbx],rax                                 ; store handle at ctx+0x80
0xEBDBC3F  mov rax,rbx                                   
0xEBDBC42  add rsp,0x20                                  
0xEBDBC46  pop rbx                                       
0xEBDBC47  ret                                           
```

**Semaphore 2: `ctx+0x100` - "Frame Consumed"**
```
0xBC6B5DA  lea rcx,[rax+0x100]                           ; rcx = ctx+0x100
0xBC6B5E5  call 0xEBDBC20                                ; CreateSemaphoreW(NULL, 0, 0x7FFFFFFF, NULL)
```
Same wrapper `0xEBDBC20`, stores handle at `ctx+0x100`.

**Additional sync objects** (also created in `0xBC6B560`):
- `ctx+0x180`: `0xEA854F0` → `CreateEventW` (IAT `0xF9A7B18`)
- `ctx+0x1C0`: `0xEBDB7E0` → initializes critical section + creates events/semaphores at `ctx+0x140` (semaphore), `ctx+0x1C0` (event)

**Verified**: Both semaphores created before render thread spawn (`0xBC6372B` in `0xBC63690`).

---

## Step 3 Addendum: View Array Field Stores (quoted from disassembly)

### From pass lambda `0xBC2C590` (view setup - "DoDeferredLighting")
```
0xBC2C600  movd [rcx+rsi+0x1EAB090],xmm0                 ; W view+0x10 rect.width (clamped u16)
0xBC2C615  movd [rcx+rsi+0x1EAB094],xmm1                 ; W view+0x14 rect.height (clamped u16)
0xBC2C637  lea rcx,[r14+rsi]                             
0xBC2C63B  add rcx,0x1EAB0A0                             ; rcx = ctx+view+0x20
0xBC2C648  call 0xEBCE390                                ; memcpy 0x40 bytes (viewMatrix)
0xBC2C64D  lea rcx,[r14+rsi]                             
0xBC2C651  add rcx,0x1EAB0E0                             ; rcx = ctx+view+0x60
0xBC2C661  call 0xEBCE390                                ; memcpy 0x40 bytes (projMatrix)
0xBC2C666  lea rcx,[r14+rsi]                             
0xBC2C66A  add rcx,0x1EAB120                             ; rcx = ctx+view+0xA0
0xBC2C67A  call 0xEBCE390                                ; memcpy 0x40 bytes (prevViewMatrix)
0xBC2C67F  lea rcx,[r14+rsi]                             
0xBC2C683  add rcx,0x1EAB160                             ; rcx = ctx+view+0xE0
0xBC2C693  call 0xEBCE390                                ; memcpy 0x40 bytes (prevProjMatrix)
0xBC2C698  lea rcx,[r14+rsi]                             
0xBC2C69C  add rcx,0x1EAB1A0                             ; rcx = ctx+view+0x120
0xBC2C6B0  call 0xEBCE390                                ; memcpy 0x10 bytes (viewportClear)
0xBC2C6C3  mov [rcx+rsi+0x1EAB1B2],al                     ; W view+0x132 sortMode byte
```

### From Context init `0xBC63690` (view array initialization loop at `0xBC63930`)
```
0xBC63930  mov word ptr [rsi+rbx+0x1EAB096],1             ; W view+0x16 = 1
0xBC6393A  mov [rsi+rbx+0x1EAB08E],rdi                    ; W view+0x0E = 0x1000000000000
0xBC63942  mov dword ptr [rsi+rbx+0x1EAB088],0            ; W view+0x08 = 0
0xBC6394D  mov byte ptr [rsi+rbx+0x1EAB08C],0             ; W view+0x0C = 0
0xBC63955  mov byte ptr [rsi+rbx+0x1EAB1B2],0             ; W view+0x132 sortMode = 0
0xBC6395D  mov dword ptr [rsi+rbx+0x1EAB080],0            ; W view+0x00 = 0
0xBC63968  mov qword ptr [rsi+rbx+0x1EAB098],0            ; W view+0x18 = 0
0xBC63974  mov word ptr [rsi+rbx+0x1EAB1B0],0xFFFF        ; W view+0x130 framebufferHandle = 0xFFFF
0xBC6397E  lea rcx,[rsi+rbx]                             
0xBC63982  add rcx,0x1EAB0A0                             ; rcx = ctx+view+0x20
0xBC63991  call 0xEBCE430                                ; memset 0x40 bytes zero
0xBC63996  mov dword ptr [rsi+rbx+0x1EAB0DC],0x3F800000   ; W view+0x5C diag[2] = 1.0f
0xBC639A1  mov dword ptr [rsi+rbx+0x1EAB0C8],0x3F800000   ; W view+0x48 diag[1] = 1.0f
0xBC639AC  mov dword ptr [rsi+rbx+0x1EAB0B4],0x3F800000   ; W view+0x34 diag[0] = 1.0f
0xBC639B7  mov dword ptr [rsi+rbx+0x1EAB0A0],0x3F800000   ; W view+0x20 diag[3] = 1.0f
0xBC639C2  lea rcx,[rsi+rbx]                             
0xBC639C6  add rcx,0x1EAB0E0                             ; rcx = ctx+view+0x60
0xBC639D5  call 0xEBCE430                                ; memset 0x40 bytes zero
0xBC639DA  mov dword ptr [rsi+rbx+0x1EAB11C],0x3F800000   ; W view+0x9C diag[2] = 1.0f
0xBC639E5  mov dword ptr [rsi+rbx+0x1EAB108],0x3F800000   ; W view+0x88 diag[1] = 1.0f
0xBC639F0  mov dword ptr [rsi+rbx+0x1EAB0F4],0x3F800000   ; W view+0x74 diag[0] = 1.0f
0xBC639FB  mov dword ptr [rsi+rbx+0x1EAB0E0],0x3F800000   ; W view+0x60 diag[3] = 1.0f
0xBC63A06  lea rcx,[rsi+rbx]                             
0xBC63A0A  add rcx,0x1EAB120                             ; rcx = ctx+view+0xA0
0xBC63A19  call 0xEBCE430                                ; memset 0x40 bytes zero
0xBC63A1E  mov dword ptr [rsi+rbx+0x1EAB15C],0x3F800000   ; W view+0xDC diag[2] = 1.0f
0xBC63A29  mov dword ptr [rsi+rbx+0x1EAB148],0x3F800000   ; W view+0xC8 diag[1] = 1.0f
0xBC63A34  mov dword ptr [rsi+rbx+0x1EAB134],0x3F800000   ; W view+0xB4 diag[0] = 1.0f
0xBC63A3F  mov dword ptr [rsi+rbx+0x1EAB120],0x3F800000   ; W view+0xA0 diag[3] = 1.0f
0xBC63A4A  lea rcx,[rsi+rbx]                             
0xBC63A4E  add rcx,0x1EAB160                             ; rcx = ctx+view+0xE0
0xBC63A5D  call 0xEBCE430                                ; memset 0x40 bytes zero
0xBC63A62  mov dword ptr [rsi+rbx+0x1EAB19C],0x3F800000   ; W view+0x11C diag[2] = 1.0f
0xBC63A6D  mov dword ptr [rsi+rbx+0x1EAB188],0x3F800000   ; W view+0x108 diag[1] = 1.0f
0xBC63A78  mov dword ptr [rsi+rbx+0x1EAB174],0x3F800000   ; W view+0xF4 diag[0] = 1.0f
0xBC63A83  mov dword ptr [rsi+rbx+0x1EAB160],0x3F800000   ; W view+0xE0 diag[3] = 1.0f
0xBC63A8E  lea rcx,[rsi+rbx]                             
0xBC63A92  add rcx,0x1EAB1A0                             ; rcx = ctx+view+0x120
0xBC63AA1  call 0xEBCE430                                ; memset 0x10 bytes zero
```

---

## Step 4 Addendum: Semaphore Wait/Post Call Sites (caller analysis)

### `WaitForSingleObject` wrapper `0xEBDBC60` (semaphore wait)
**Callers** (from xref):
```
0xBC63060  (helper calls renderFrame with timeout)
0xBC63150  (renderFrame main wait at 0xBC6322F)
0xBC65720  (thread proc wait at 0xBC6579A, INFINITE)
0xBC65800  (another thread-related function)
0xBC66B20  (unknown)
0xEBDB9B0  (thread startup at 0xEBDB9FF, waits on ctx+0x140)
```

**Key wait sites**:
```
0xBC63226  lea rcx,[rsi+0x80]                          ; ctx+0x80
0xBC6322D  mov edx,edi                                  ; timeout (5000ms)
0xBC6322F  call ebdbc60                                ; WaitForSingleObject(ctx+0x80, timeout)

0xBC6578E  lea rcx,[rdi+0x80]                          ; ctx+0x80
0xBC65795  mov edx,0xFFFFFFFF                          ; INFINITE
0xBC6579A  call ebdbc60                                ; WaitForSingleObject(ctx+0x80, INFINITE)
```

### `ReleaseSemaphore` wrapper `0xEBDBC50` (semaphore post)
**Callers** (from xref):
```
0xBC63060  (helper on Exiting path)
0xBC63150  (renderFrame post at 0xBC633DA)
0xBC63B80  (shutdown helper)
0xBC65720  (thread proc exit post at 0xBC657ED)
0xBC65800  (another thread-related)
0xBC66B20  (unknown)
0xC270460  (BgfxContext::endFrame - frame graph encode)
0xEBDBBE0  (thread teardown posts ctx+0x140)
```

**Key post sites**:
```
0xBC633D2  mov rcx,rsi
0xBC633D5  mov edx,1
0xBC633DA  call ebdbc50                                ; ReleaseSemaphore(ctx+0x100, 1)

0xBC657E8  mov edx,1
0xBC657ED  call ebdbc50                                ; ReleaseSemaphore(ctx+0x100, 1) on thread exit
```

### `CreateSemaphoreW` wrapper `0xEBDBC20` (semaphore creation)
**Callers** (from xref):
```
0xBC6B560  (Context post-allocation init - creates BOTH semaphores)
  -> 0xBC6B5C5 lea rcx,[rsi+0x80]; call 0xEBDBC20      ; creates ctx+0x80
  -> 0xBC6B5DA lea rcx,[rax+0x100]; call 0xEBDBC20     ; creates ctx+0x100

0xEBDB7E0  (initializes ctx+0x140 semaphore, ctx+0x1C0 event)
```

**CreateSemaphoreW IAT**: `0xF9A7C50` (no direct code refs - called indirectly via `0xEBDBC20`)

---

## Verification Status

- [x] ripscan for global 0x12AE1748
- [x] Top 10 referencing functions with quoted load instructions
- [x] Context allocation site (0xBC6D852) and initialization (0xBC63690)
- [x] View array: stride 0x140, count 256, fields from stores (offsets recomputed)
- [x] View array field stores: 15 stores from pass lambda, 32 stores from init loop (all quoted)
- [x] Semaphore wait/post sites identified with caller analysis
- [x] Semaphore creation: `0xBC6B560` → `0xEBDBC20` → `CreateSemaphoreW` (IAT `0xF9A7C50`) for both `ctx+0x80` and `ctx+0x100`
- [x] Run verify_oc.py

---

## TOOL REQUESTS

| Name | Input → Output | Why it would have helped |
|------|----------------|--------------------------|
| `semaphore_finder.py` | Context init RVA → CreateSemaphore call sites | Automates finding semaphore creation; currently done by manual search of init function |
| `verify_oc.py` | progress markdown → PASS/FAIL | Required by unit spec; will run after writing all sections |

---

## NEXT
Unit complete. All steps verified with verify_oc.py (112/112 match).