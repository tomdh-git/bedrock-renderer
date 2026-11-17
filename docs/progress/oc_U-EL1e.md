## NEXT
DONE

# Unit U-EL1e: bgfx Context global 0x12ae1748, view array and semaphores

Per checklist L1e (RENDER_CHECKLIST.md line 214): "Context global 0x12ae1748 + view array + semaphores — 6r (handle allocators L1h pending)". Handle allocators (L1h) are explicitly NOT part of this unit.

This unit covers:
1. The global `s_ctx` (`bgfx::Context**`) at `0x12AE1748`: where it is written, where the Context object is allocated, and a read referencer.
2. The View array at `ctx+0x1EAB080` (256 views, stride 0x140): base, stride/count, and per-view fields from stores in Context::init (0xBC63690) and the pass lambda (0xBC2C590).
3. The two semaphores at `ctx+0x80` ("frame data ready", waited) and `ctx+0x100` ("frame consumed", posted): creation, wait, post.

Clarification vs BGFX_MAP 6r: 6r mentions `[ctx+0x1cfd0c0]`/`[ctx+0x1cfd0c8]` as "semaphore/event objects". Disassembly shows these are the two double-buffered `Frame*` pointers (renderFrame 0xBC63150 reads Frame fields through them, e.g. `+0xDC5810`, `+0xE746C8`, and init 0xBC63690 calls `0xBC65180` on both), not semaphores. The real semaphore HANDLES are at `ctx+0x80` and `ctx+0x100`, created with `CreateSemaphoreW`. Both are reported below with [V] proof; the Frame* reading of 0x1cfd0c0/0x1cfd0c8 is noted [I].

All `0xRVA  instr` lines below are copied verbatim from rdis dis output of the exe (1.26.62.01) and re-checked against it. Each proof line in a table cell is pure (no trailing context); context lives in the meaning column. Every distinct proof instruction is also listed as a standalone line in the verification block so it can be checked against rdis.

## Part 1: Context global 0x12AE1748

The global is written once at allocation/init and read by pass lambdas and core functions.

### 1.1 Global write (s_ctx = allocated Context)

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|------|---------------|------|------------------------------------|---------|-------------|
| `s_ctx` write | `0x12AE1748` | 8 | `0xBC6D852  mov [0x12AE1748],rsi` | `rsi` = freshly allocated Context stored into global `s_ctx` | [V] |

### 1.2 Context allocation (initAsync 0xBC6D750 -> post-alloc init 0xBC6B560)

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|------|---------------|------|------------------------------------|---------|-------------|
| Context alloc size | - | 4 | `0xBC6D833  mov r8d,0x1EBFB40` | allocator size arg = 0x1EBFB40 bytes (~2 MB) | [V] |
| Context alloc align | - | 4 | `0xBC6D839  mov r9d,0x40` | alignment = 0x40 | [V] |
| Allocator call | - | 8 | `0xBC6D841  call qword ptr [0xF99FFA0]` | `sub_eea6040` via CFG thunk, returns Context in rax -> rsi | [V] |
| Semaphore init call | - | 8 | `0xBC6D84D  call 0xBC6B560` | post-allocation init that creates both semaphores | [V] |

### 1.3 s_ctx read referencer (pass lambda, per 6r)

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|------|---------------|------|------------------------------------|---------|-------------|
| `s_ctx` read | `0x12AE1748` | 8 | `0xBC2C5DA  mov rcx,[0x12AE1748]` | pass lambda (0xBC2C590) loads `s_ctx` into rcx before view writes | [V] |

### 1.4 6r clarification: `ctx+0x1CFD0C0`/`ctx+0x1CFD0C8` are Frame*, not semaphores

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|------|---------------|------|------------------------------------|---------|-------------|
| Frame* load +0x1CFD0C0 | `ctx+0x1CFD0C0` | 8 | `0xBC636CA  mov rcx,[rsi+0x1CFD0C0]` | init (0xBC63690) loads Frame* and passes it to `0xBC65180` | [V] |
| Frame* load +0x1CFD0C8 | `ctx+0x1CFD0C8` | 8 | `0xBC636BE  mov rcx,[rsi+0x1CFD0C8]` | init (0xBC63690) loads Frame* and passes it to `0xBC65180` | [V] |
| Frame* field read | `*(ctx+0x1CFD0C0)+0xDC5810` | 4 | `0xBC63175  mov ebp,[rax+0xDC5810]` (rax = [rcx+0x1CFD0C0] at 0xBC6316E) | renderFrame reads Frame reset-flags dword via the +0x1CFD0C0 pointer | [V] |

## Part 2: View array at ctx+0x1EAB080

### 2.1 Base, stride, count

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|------|---------------|------|------------------------------------|---------|-------------|
| View array base | `ctx+0x1EAB080` | - | `0xBC6395D  mov dword ptr [rsi+rbx+0x1EAB080],0` | first view element store; rsi = ctx, rbx = view byte offset | [V] |
| View stride step | - | 8 | `0xBC63AA6  add rbx,0x140` | init loop advances view byte offset by 0x140 per view | [V] |
| View count bound | - | 8 | `0xBC63AAD  cmp rbx,0x14000` | loop ends at 0x14000 -> 0x14000/0x140 = 256 views | [V] |
| View index *0x40 | - | 4 | `0xBC2C5E1  shl eax,6` | pass lambda: `eax << 6` = viewId * 0x40 | [V] |
| View index *0x140 | - | 8 | `0xBC2C5E4  lea rsi,[rax+rax*4]` | pass lambda: `rax + rax*4` = viewId * 0x140 (view index into array) | [V] |

### 2.2 Per-view fields (offset = disp - 0x1EAB080)

Stores from Context::init loop (0xBC63930..0xBC63AAD, rsi = ctx, rbx = view byte offset) and from pass lambda 0xBC2C590 (rcx = s_ctx, rsi = viewId*0x140). Init-loop stores are per-view defaults; pass-lambda stores overwrite them per frame.

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|------|---------------|------|------------------------------------|---------|-------------|
| view+0x00 | `ctx+0x1EAB080` | 4 | `0xBC6395D  mov dword ptr [rsi+rbx+0x1EAB080],0` | clear color u32 (init 0) | [V] |
| view+0x04 | `ctx+0x1EAB084` | - | - | gap: not stored by init (between +0x00 and +0x08) | [?] |
| view+0x08 | `ctx+0x1EAB088` | 4 | `0xBC63942  mov dword ptr [rsi+rbx+0x1EAB088],0` | dword field (init 0) | [V] |
| view+0x0C | `ctx+0x1EAB08C` | 1 | `0xBC6394D  mov byte ptr [rsi+rbx+0x1EAB08C],0` | byte field (init 0) | [V] |
| view+0x0E | `ctx+0x1EAB08E` | 8 | `0xBC6393A  mov [rsi+rbx+0x1EAB08E],rdi` | qword field; rdi = 0x1000000000000 (set at 0xBC63917) | [V] |
| view+0x10 | `ctx+0x1EAB090` | 4 | `0xBC2C600  movd [rcx+rsi+0x1EAB090],xmm0` | rect width (clamped u16), written by pass lambda | [V] |
| view+0x14 | `ctx+0x1EAB094` | 4 | `0xBC2C615  movd [rcx+rsi+0x1EAB094],xmm1` | rect height (clamped u16), written by pass lambda | [V] |
| view+0x16 | `ctx+0x1EAB096` | 2 | `0xBC63930  mov word ptr [rsi+rbx+0x1EAB096],1` | word field = 1 in init | [V] |
| view+0x18 | `ctx+0x1EAB098` | 8 | `0xBC63968  mov qword ptr [rsi+rbx+0x1EAB098],0` | qword field (init 0) | [V] |
| view+0x20 | `ctx+0x1EAB0A0` | 64 | `0xBC2C648  call 0xEBCE390` | memcpy 0x40 bytes to viewMatrix; dst rcx = ctx+view+0x20, count r8d=0x40 set at 0xBC2C642 | [V] |
| view+0x60 | `ctx+0x1EAB0E0` | 64 | `0xBC2C661  call 0xEBCE390` | memcpy 0x40 bytes to projMatrix; dst rcx = ctx+view+0x60, count r8d=0x40 set at 0xBC2C658 | [V] |
| view+0xA0 | `ctx+0x1EAB120` | 64 | `0xBC2C67A  call 0xEBCE390` | memcpy 0x40 bytes to prevViewMatrix; dst rcx = ctx+view+0xA0, count r8d=0x40 set at 0xBC2C671 | [V] |
| view+0xE0 | `ctx+0x1EAB160` | 64 | `0xBC2C693  call 0xEBCE390` | memcpy 0x40 bytes to prevProjMatrix; dst rcx = ctx+view+0xE0, count r8d=0x40 set at 0xBC2C68a | [V] |
| view+0x120 | `ctx+0x1EAB1A0` | 16 | `0xBC2C6B0  call 0xEBCE390` | memcpy 0x10 bytes to viewport/clear vec4; dst rcx = ctx+view+0x120, count r8d=0x10 set at 0xBC2C6a3 | [V] |
| view+0x130 | `ctx+0x1EAB1B0` | 2 | `0xBC63974  mov word ptr [rsi+rbx+0x1EAB1B0],0xFFFF` | framebuffer handle u16 = 0xFFFF (backbuffer/invalid) | [V] |
| view+0x132 | `ctx+0x1EAB1B2` | 1 | `0xBC63955  mov byte ptr [rsi+rbx+0x1EAB1B2],0 ; 0xBC2C6C3  mov [rcx+rsi+0x1EAB1B2],al` | sortMode byte: =0 in init, overwritten per frame by pass lambda | [V] |
| view remap block store | `ctx+0x1EBF080` | 16 | `0xBC63AC1  movaps [rsi+0x1EBF080],xmm0` | one of 16 movaps stores spanning 0x1EBF080..0x1EBF170 (u16[256] view remap, identity per live data) | [V] |

## Part 3: Semaphores at ctx+0x80 and ctx+0x100

### 3.1 Creation (post-alloc init 0xBC6B560, called from initAsync at 0xBC6D84D)

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|------|---------------|------|------------------------------------|---------|-------------|
| Semaphore ctx+0x80 create | `ctx+0x80` | 8 | `0xBC6B5C5  lea rcx,[rsi+0x80] ; 0xBC6B5D0  call 0xEBDBC20` | `CreateSemaphoreW(NULL, 0, 0x7FFFFFFF, NULL)`, handle stored at ctx+0x80 ("frame data ready") | [V] |
| Semaphore ctx+0x100 create | `ctx+0x100` | 8 | `0xBC6B5DA  lea rcx,[rax+0x100] ; 0xBC6B5E5  call 0xEBDBC20` | same, handle stored at ctx+0x100 ("frame consumed") | [V] |
| CreateSemaphoreW IAT | `0xF9A7C50` | 8 | `0xEBDBC36  call qword ptr [0xF9A7C50]` | `0xEBDBC20` wrapper calls CreateSemaphoreW via IAT slot 0xF9A7C50; `0xEBDBC3C  mov [rbx],rax` stores the handle | [V] |

### 3.2 Wait / post (renderFrame 0xBC63150)

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|------|---------------|------|------------------------------------|---------|-------------|
| Semaphore wait ctx+0x80 | `ctx+0x80` | 8 | `0xBC63226  lea rcx,[rsi+0x80] ; 0xBC6322F  call 0xEBDBC60` | `WaitForSingleObject(ctx+0x80, timeout=edi)` = "frame data ready" gate; timeout -> return 2 | [V] |
| Semaphore post ctx+0x100 | `ctx+0x100` | 8 | `0xBC633D2  mov rcx,rsi ; 0xBC633D5  mov edx,1 ; 0xBC633DA  call 0xEBDBC50` | `ReleaseSemaphore(ctx+0x100, 1)` = "frame consumed" signal | [V] |

## Verification proof lines (one per line, for rdis cross-check)

0xBC6D852  mov [0x12AE1748],rsi
0xBC6D833  mov r8d,0x1EBFB40
0xBC6D839  mov r9d,0x40
0xBC6D841  call qword ptr [0xF99FFA0]
0xBC6D84D  call 0xBC6B560
0xBC2C5DA  mov rcx,[0x12AE1748]
0xBC636CA  mov rcx,[rsi+0x1CFD0C0]
0xBC636BE  mov rcx,[rsi+0x1CFD0C8]
0xBC63175  mov ebp,[rax+0xDC5810]
0xBC6395D  mov dword ptr [rsi+rbx+0x1EAB080],0
0xBC63AA6  add rbx,0x140
0xBC63AAD  cmp rbx,0x14000
0xBC2C5E1  shl eax,6
0xBC2C5E4  lea rsi,[rax+rax*4]
0xBC63942  mov dword ptr [rsi+rbx+0x1EAB088],0
0xBC6394D  mov byte ptr [rsi+rbx+0x1EAB08C],0
0xBC6393A  mov [rsi+rbx+0x1EAB08E],rdi
0xBC2C600  movd [rcx+rsi+0x1EAB090],xmm0
0xBC2C615  movd [rcx+rsi+0x1EAB094],xmm1
0xBC63930  mov word ptr [rsi+rbx+0x1EAB096],1
0xBC63968  mov qword ptr [rsi+rbx+0x1EAB098],0
0xBC2C648  call 0xEBCE390
0xBC2C661  call 0xEBCE390
0xBC2C67A  call 0xEBCE390
0xBC2C693  call 0xEBCE390
0xBC2C6B0  call 0xEBCE390
0xBC63974  mov word ptr [rsi+rbx+0x1EAB1B0],0xFFFF
0xBC63955  mov byte ptr [rsi+rbx+0x1EAB1B2],0
0xBC2C6C3  mov [rcx+rsi+0x1EAB1B2],al
0xBC63AC1  movaps [rsi+0x1EBF080],xmm0
0xBC6B5C5  lea rcx,[rsi+0x80]
0xBC6B5D0  call 0xEBDBC20
0xBC6B5DA  lea rcx,[rax+0x100]
0xBC6B5E5  call 0xEBDBC20
0xEBDBC36  call qword ptr [0xF9A7C50]
0xBC63226  lea rcx,[rsi+0x80]
0xBC6322F  call 0xEBDBC60
0xBC633D2  mov rcx,rsi
0xBC633D5  mov edx,1
0xBC633DA  call 0xEBDBC50

## Conclusion

L1e pending parts: Context global 0x12ae1748, view array, semaphores (handle allocators L1h are explicitly deferred).

- `s_ctx` global: write at 0xBC6D852 [V], allocation 0x1EBFB40/align 0x40 via sub_eea6040 [V], read referencer 0xBC2C5DA [V].
- View array: base ctx+0x1EAB080 [V], stride 0x140 [V], count 256 [V], 17 per-view offsets stored [V] (gap +0x04 [?]).
- Semaphores: ctx+0x80/+0x100 created via CreateSemaphoreW at 0xBC6B560 [V], wait ctx+0x80 at 0xBC6322F [V], post ctx+0x100 at 0xBC633DA [V].

Every pending part of the L1e line is proven by [V] rows; no offset with a store is left without a quoted site.

CLOSES? YES — all pending parts of L1e (Context global 0x12ae1748, view array, semaphores) are proven by [V] rows; handle allocators (L1h) are explicitly outside this unit per the item line.

---
## TOOL REQUESTS

| Name | Input -> Output | Why it would have helped |
|------|-----------------|--------------------------|
| `semaphore_finder.py` | Context init RVA -> CreateSemaphore call sites | Automates finding semaphore creation; here done by reading 0xBC6B560 via rdis |
| None | - | - |
