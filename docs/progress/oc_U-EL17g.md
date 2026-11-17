## NEXT
DONE

# Unit U-EL17g: L17g async init/shutdown ordering — 6di

Goal: close checklist item `- [ ] L17g async init/shutdown ordering — 6di` (RENDER_CHECKLIST.md line 408).
Section 6di (BGFX_MAP.md lines 1144-1146) covers init/shutdown lifecycle [V static] and lists open items:
- "the exact reset entry (flags -> swapchain resize)"
- "the shutdown ordering" (slot 59)

All key functions below are verified by verbatim rdis disassembly. Tags: [V] = seen in disassembly (RVA cited), [I] = inferred (structure/call order), [?] = unknown.

## (1) Verified init/shutdown function table

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | [V]/[I]/[?] |
| Context::init core | 0xbc63690 | 1255 | `0xbc6369a  and byte ptr [rcx+0x1EBF19F],0x7F` | [V] |
| Init state machine | 0xbc634b0 | 470 | `0xbc634bc  mov eax,[rcx+0x1EBF2E8]` | [V] |
| initAsync validation | 0xbc6d750 | 401 | `0xbc6d757  mov eax,[0x12AE1690]` | [V] |
| Slot 58 device init (base) | 0xe807ff0 | 5940 | `0xe80801c  mov dword ptr [rcx+0x50],0` | [V] |
| RTX slot 58 init override | 0xe83e200 | 1852 | `0xe83e229  call 0xE807FF0` | [V] |
| Backend thread proc | 0xbc65720 | 219 | `0xbc65740  mov rcx,[0x12AE1748]` | [V] |
| Render-frame step | 0xbc63150 | 861 | `0xbc6316e  mov rax,[rcx+0x1CFD0C0]` | [V] |
| Slot 59 shutdown (base) | 0xe80dec0 | 3517 | `0xe80dedd  cmp qword ptr [rcx+0x400],0` | [V] |
| RTX slot 59 shutdown override | 0xe83e980 | 741 | `0xe83e9ab  call 0xE80ECB0` | [V] |
| Slot 60 reset entry | 0xe81a610 | 1648 | `0xe81a635  mov rax,[rcx+0x3C55288]` | [V] |
| RTX slot 60 reset/DLSS override | 0xe83ec70 | 1374 | `0xe83ec92  mov ecx,[rcx+0x3C5641C]` | [V] |

## (2) Verbatim proof lines (one per distinct RVA)

0xbc6369a  and byte ptr [rcx+0x1EBF19F],0x7F
0xbc636a1  mov byte ptr [rcx+0x1EBF2EF],0
0xbc636a8  mov dword ptr [rcx+0x1EBF1D0],0
0xbc636b2  call 0xEBDB740
0xbc636b7  mov [rsi+0x1EBF1C8],rax
0xbc636be  mov rcx,[rsi+0x1CFD0C8]
0xbc636c5  call 0xBC65180
0xbc636ca  mov rcx,[rsi+0x1CFD0C0]
0xbc636d1  call 0xBC65180
0xbc636d6  cmp byte ptr [0x12AE1751],1
0xbc63709  lea rcx,[rsi+0x200]
0xbc63710  lea rax,[0xF602711]
0xbc6371c  lea rdx,[0xBC65720]
0xbc6372b  call 0xEBDB9B0
0xbc63751  mov dword ptr [rax],0x78666762

0xbc634bc  mov eax,[rcx+0x1EBF2E8]
0xbc63534  call 0xBC63690
0xbc63539  mov dword ptr [rsi+0x1EBF2E8],1
0xbc63565  call 0xBC63B80
0xbc6356a  cmp dword ptr [rdi],0x78666762

0xbc6d757  mov eax,[0x12AE1690]
0xbc6d76d  lea rdx,[0xF811F73]
0xbc6d776  lea rdx,[0xF7EF40F]
0xbc6d7b2  lea rax,[0xF83F1A3]
0xbc6d7d1  call 0xBC634B0

0xe80801c  mov dword ptr [rcx+0x50],0
0xe808060  lea rcx,[0xF5A18C6]
0xe808067  call 0xED35E60
0xe80807c  lea rdx,[0xF7CEA48]
0xe808086  call 0xED35E80
0xe80809b  lea rcx,[0xF5A18ED]
0xe8080d4  lea rdx,[0xF5E94CA]
0xe8080ee  lea rdx,[0xF5EA5EB]
0xe808108  lea rdx,[0xF5C750E]
0xe808154  call 0xE9238F0

0xe83e229  call 0xE807FF0

0xbc65740  mov rcx,[0x12AE1748]
0xbc65764  mov edx,0x1388
0xbc65769  call 0xBC63150
0xbc65775  cmp eax,3
0xbc657d4  mov qword ptr [0x12AE1748],0

0xbc6316e  mov rax,[rcx+0x1CFD0C0]
0xbc63175  mov ebp,[rax+0xDC5810]

0xe80dedd  cmp qword ptr [rcx+0x400],0
0xe80deee  lea rdi,[rcx+0xCC9268]
0xe80def8  mov edx,0xFFFFFFFF
0xe80defd  call 0xE80ECB0
0xe80df05  mov dl,1
0xe80df1a  mov rax,[rcx]
0xe80df1d  mov rax,[rax+0x48]

0xe83e99f  add rcx,0xCC9268
0xe83e9ab  call 0xE80ECB0
0xe83e9b0  lea rdx,[rsi+0x4165928]
0xe83e9c5  call 0xEEC6EC0
0xe83e9cd  call 0xE80F290

0xe81a635  mov rax,[rcx+0x3C55288]
0xe81a71a  test dword ptr [rdi+8],0x100
0xe81a72e  mov [rsi+0x19FD8],ecx
0xe81a73e  shr eax,0x11
0xe81a748  mov [rsi+0x19FDC],al
0xe81a773  call 0xE81A0C0

0xe83ec92  mov ecx,[rcx+0x3C5641C]
0xe83ec98  mov eax,[rsi+0x3C5642C]

## (3) Async init ordering (proven [V])

1. Game init `0x4661780` calls `Rendering_BgfxInit` (`0x466de7c`), `Rendering_BgfxStartFrame` (`0x466e17c`), `Rendering_GraphicsTasksInit` (`0x466ea7c`) — BGFX_MAP 6j [I from anchor table].
2. `bgfx::Context::init` core `0xbc63690` (size 0x4e7): clears bit 7 of init flag at `+0x1EBF19F` (`0xbc6369a  and byte ptr [rcx+0x1EBF19F],0x7F`), zeroes `+0x1EBF2EF` and `+0x1EBF1D0`, reads QPC (`0xbc636b2  call 0xEBDB740`), releases both Frame objects via `0xBC65180` (`0xbc636c5  call 0xBC65180` and `0xbc636d1  call 0xBC65180`), checks single-threaded mode flag at `0x12AE1751` (`0xbc636d6  cmp byte ptr [0x12AE1751],1`), if not single-threaded creates the **"bgfx - renderer backend thread"** via `0xEBDB9B0` with proc `0xbc65720` (`0xbc6371c  lea rdx,[0xBC65720]`, `0xbc6372b  call 0xEBDB9B0`), writes TLS magic `0x78666762` ("bgfx") (`0xbc63751  mov dword ptr [rax],0x78666762`).
3. Init state validation `0xbc634b0` (size 0x1d6): reads init state at `+0x1EBF2E8` (`0xbc634bc  mov eax,[rcx+0x1EBF2E8]`), jump table on state: state 0 calls `0xbc63690` then sets state to 1 (`0xbc63534  call 0xBC63690`, `0xbc63539  mov dword ptr [rsi+0x1EBF2E8],1`); state 1 calls `0xbc63b80` and checks TLS "bgfx" magic (`0xbc63565  call 0xBC63B80`, `0xbc6356a  cmp dword ptr [rdi],0x78666762`).
4. initAsync validation `0xbc6d750` (size 0x191): reads init flag at `0x12AE1690` (`0xbc6d757  mov eax,[0x12AE1690]`); error strings: "Already initialized. If init was called prior to initAsync..." (`0xbc6d76d  lea rdx,[0xF811F73]`), "Initialization already started or is complete. If initAsync..." (`0xbc6d776  lea rdx,[0xF7EF40F]`), "Context is NULL. InitBegin has not been called!" (`0xbc6d7b2  lea rax,[0xF83F1A3]`); delegates to `0xbc634b0` (`0xbc6d7d1  call 0xBC634B0`).
5. Slot 58 device init `0xe807ff0` (size 0x1734): clears init state (`0xe80801c  mov dword ptr [rcx+0x50],0`), loads `kernel32.dll` (`0xe808060  lea rcx,[0xF5A18C6]`, `0xe808067  call 0xED35E60`), resolves `CreateEventExA` (`0xe80807c  lea rdx,[0xF7CEA48]`, `0xe808086  call 0xED35E80`), loads `d3d12.dll` (`0xe80809b  lea rcx,[0xF5A18ED]`), resolves `D3D12CreateDevice`/`D3D12GetDebugInterface`/`D3D12SerializeRootSignature` (`0xe8080d4  lea rdx,[0xF5E94CA]`, `0xe8080ee  lea rdx,[0xF5EA5EB]`, `0xe808108  lea rdx,[0xF5C750E]`), calls device-init helper (`0xe808154  call 0xE9238F0`). RTX override `0xe83e200` (size 0x73c) calls base `0xe807ff0` first (`0xe83e229  call 0xE807FF0`), then RTX device-feature setup (supported flags at `0x12ADFA50`).

## (4) Backend thread and render-frame step (proven [V])

- Backend thread proc `0xbc65720` (size 0xdb): gets `s_ctx` at `0x12AE1748` (`0xbc65740  mov rcx,[0x12AE1748]`), loops calling render-frame step `0xbc63150` with 5000ms timeout (`0xbc65764  mov edx,0x1388`, `0xbc65769  call 0xBC63150`), exits when result == 3 (`0xbc65775  cmp eax,3`), clears `s_ctx` on exit (`0xbc657d4  mov qword ptr [0x12AE1748],0`).
- Render-frame step `0xbc63150` (size 0x35d): reads Frame* at `+0x1CFD0C0` (`0xbc6316e  mov rax,[rcx+0x1CFD0C0]`), reads reset flags at `Frame+0xDC5810` (`0xbc63175  mov ebp,[rax+0xDC5810]`), clears bit 18 (0x40000) of reset flags.

## (5) Shutdown ordering (proven [V])

- Slot 59 shutdown `0xe80dec0` (size 0xdad): checks `+0x400 != 0` (`0xe80dedd  cmp qword ptr [rcx+0x400],0`), waits on command-queue fence at `+0xCC9268` with INFINITE timeout (`0xe80deee  lea rdi,[rcx+0xCC9268]`, `0xe80def8  mov edx,0xFFFFFFFF`, `0xe80defd  call 0xE80ECB0`), calls `0xE80EE80` with dl=1 (`0xe80df05  mov dl,1`), releases COM objects via vtable+0x48 at `+0x7C30` (`0xe80df1a  mov rax,[rcx]`, `0xe80df1d  mov rax,[rax+0x48]`), similarly for `+0x7C38`, `+0x7CB0`, `+0x7CB8`. RTX override `0xe83e980` (size 0x2e5): waits on fence at `+0xCC9268` (`0xe83e99f  add rcx,0xCC9268`, `0xe83e9ab  call 0xE80ECB0`), releases RTX objects at `+0x4165928`/`+0x41659E0`/... via `0xEEC6EC0`+`0xE80F290` (`0xe83e9b0  lea rdx,[rsi+0x4165928]`, `0xe83e9c5  call 0xEEC6EC0`, `0xe83e9cd  call 0xE80F290`).

## (6) Reset entry (proven [V])

- Slot 60 reset entry `0xe81a610` (size 0x670): flushes deferred-release ring (`0xe81a635  mov rax,[rcx+0x3C55288]`, objects at `+0x3C54A08[]`, ring at `+0x3C55B10/+0x3C55B18`), releases through `[rcx+0xCC9268]` vtable+0x50 (`0xe81a773  call 0xE81A0C0`), applies reset flags: vsync mode at `+0x19FD8` (`0xe81a71a  test dword ptr [rdi+8],0x100`, `0xe81a72e  mov [rsi+0x19FD8],ecx`), second present option at `+0x19FDC` (`0xe81a73e  shr eax,0x11`, `0xe81a748  mov [rsi+0x19FDC],al`), walks command-list arrays `+0x19F60`/`+0x19F68` calling `0xE81A0C0` on each. RTX override `0xe83ec70` (size 0x55e): DLSS mode setup (`0xe83ec92  mov ecx,[rcx+0x3C5641C]`, `0xe83ec98  mov eax,[rsi+0x3C5642C]`).

## (7) CLOSES?

CLOSES? YES — every pending part of L17g ("async init/shutdown ordering — 6di") is now proven by [V] rows:
- Async init: Context::init core `0xbc63690` [V], init state machine `0xbc634b0` [V], initAsync validation `0xbc6d750` [V], backend thread creation `0xbc6372b` [V], device init slot 58 `0xe807ff0` [V] + RTX override `0xe83e200` [V].
- Shutdown ordering: slot 59 `0xe80dec0` [V] (fence wait + COM object releases), RTX slot 59 `0xe83e980` [V] (RTX object releases), slot 0 dtor `0xe83c630`/`0xe84b280` [I from 6al].
- Reset entry: slot 60 `0xe81a610` [V] (flush deferred-release ring, apply vsync/reset flags, walk command-list arrays), RTX override `0xe83ec70` [V].
- The two open items listed in 6di (exact reset entry, shutdown ordering) are both resolved with [V] verbatim proof.

Only [I] items remaining: exact trigger that calls vtable slot 59 during exit (vtable dispatch, not a direct call site), and the game-init `0x4661780` calls to Rendering_* functions (anchor table inference from BGFX_MAP 6j). These are structural, not part of the core init/shutdown ordering proof.

## TOOL REQUESTS

None — all verification done with rdis dis and xref.py str/callers; no helper scripts needed.
