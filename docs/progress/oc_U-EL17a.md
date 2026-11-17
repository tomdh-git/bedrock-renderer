## NEXT
DONE (2026-11-16): U-EL17a 6aw slot-60 reset/resize body fully decoded [V]; delegate.py check exits 0; CLOSES? YES for L17a (6av/6ay closed by U-B6/U-EL17f, 6az by dossiers 0xe817880/6a/0xe817c00, 6aw pending remainder now proven by [V] rows)

# L17a swapchain/DXGI/present and resize — pending part: 6aw slot-60 reset/resize body

Unit U-EL17a (output file docs/progress/oc_U-EL17a.md, no other file).
Static analysis only (Minecraft.Windows.exe 1.26.62.01; RVAs relative to image base).

Scope of checklist item "L17a swapchain/DXGI/present and resize (partly hooked) — 6av, 6ay, 6az, 6aw":
- 6av (command-queue wrapper this+0xCC9268, current list this+0x19F58, slots 8/61/62, fence wait) — closed [V] by U-B6/U-EL2l; not re-decoded here.
- 6ay (Present slot 6 `0xe811fb0`: SyncInterval = bit 7 of this+0x19F80, Flags, extra windows, GetLastPresentCount, QPC timestamps) — closed [V] by U-EL17f; not re-decoded here.
- 6az (slot 39 `0xe817880` create window-backed frame buffer/swapchain; record fields +0x10/+0x20/+0x30/+0x32) — dossiers docs/functions/0xe817880.md, 0xe8176a0.md, 0xe817c00.md and A8b record rows [V doc]; not re-decoded here.
- 6aw (slot 60 `0xe81a610` RendererContext::reset = swapchain/backbuffer resize): U-EL17f covered only the present-interval byte derivation (this+0x19FD8 := 1/0x10 from Frame-reset bit 0x100; byte this+0x19FDC := (flags>>17)&1). **This unit decodes ONLY that pending remainder: kick/flush at reset entry, the this+0x19FD8 meaning (6ax: MaxAnisotropy consumed by sampler builder 0xe820500 at [desc+0x14] vs 6aw's "sync interval"), the this+0x19FDC-driven surface rebuild (0xe81a0c0 over the this+0x19F60/68 vector), back-buffer size fields this+0xC9C6C0/64/66, the pixelCount*2 allocation via the global allocator, device resize/CreateCommittedResource/Release calls, and HRESULT→TDR funneling.**

Notes:
- U-EL17f's 6dn row named this+0x19FD8 "applied sync interval"; 6ax corrected that this field is consumed as MaxAnisotropy by the sampler builder. Both are [V]: reset stores 1/0x10 into it and `0xe8206ab  mov ebp,[rax+0x19FD8]` / `0xe8207d2  mov [rsp+0x84],ebp` feed D3D12_SAMPLER_DESC+0x14 (MaxAnisotropy). Dual-purpose field; naming is [I], the accesses are [V].
- Live capture (platform-versioning-live.md) reads obj+0xC9C6C0 = 17040 = 240*71 and calls it a tile grid, contradicting 6aw's "back-buffer size" wording; the static code computes pixelCount = width*height (u16 at 0xC9C6C4/0xC9C6C6) into the dword at 0xC9C6C0 [V], so the live-value interpretation is [?], non-blocking for static closure.

Sources: `rdis ... dis 0xe81a610` (slot 60 base reset, 0xe81a610..0xe81ac80, size 0x670); `rdis ... dis 0xe820500` (sampler builder consuming this+0x19FD8). One row per distinct offset; every read/store site of that offset is listed in the address cell; instruction cell holds all verbatim `0xRVA  instr` lines `<br>`-separated; sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1); meaning only where the instruction/string shows it, else '-'. Tag [V] = seen in the disassembly at the cited RVA.

## 6aw — Slot 60 `0xe81a610` reset/resize body (pending remainder)

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| Pending surface/frame-context count (this+0x3C55288) | 0x3C55288 | 8 | R: 0xe81a635 [rcx+0x3C55288]; W: 0xe81a70f [rsi+0x3C55288] | `0xe81a635  mov rax,[rcx+0x3C55288]<br>0xe81a70f  mov qword ptr [rsi+0x3C55288],0` | u64 count of pending frame contexts drained by the reset-entry kick (same loop as slot 62, 6av), then zeroed | [V] |
| Kick ring entries (this+0x3C55290 + idx*8) | 0x3C55290 | 8 | W: 0xe81a666 [rsi+r9*8+0x3C55290] | `0xe81a666  mov [rsi+r9*8+0x3C55290],r8` | surface command-list pointers collected into the stack array for one ExecuteCommandLists | [V] |
| Fence wrapper pointer (this+0x3C563B0) | 0x3C563B0 | 8 | R: 0xe81a66e [rsi+0x3C563B0] | `0xe81a66e  mov r9,[rsi+0x3C563B0]` | fence object whose +0x28 holds the current signal value | [V] |
| Fence current signal value (fence+0x28) | 0x28 | 8 | R: 0xe81a675 [r9+0x28] | `0xe81a675  mov r9,[r9+0x28]` | u64 fence value stamped into each pending surface | [V] |
| Surface fence-value stamp (surface+0x2CBD0) | 0x2CBD0 | 8 | W: 0xe81a679 [r8+0x2CBD0] | `0xe81a679  mov [r8+0x2CBD0],r9` | obj+0x2CBD0 = current fence value (kick step 1, 6av) | [V] |
| Surface submitted flag (surface+0x2CBD8) | 0x2CBD8 | 1 | W: 0xe81a680 [r8+0x2CBD8] | `0xe81a680  mov byte ptr [r8+0x2CBD8],1` | u8 = 1 marks the surface submitted | [V] |
| Surface command-list pointer (surface+0x30) | 0x30 | 8 | R: 0xe81a688 [r8+0x30] | `0xe81a688  mov r8,[r8+0x30]` | obj+0x30 = ID3D12CommandList* collected into ExecuteCommandLists array | [V] |
| Command-queue wrapper (this+0xCC9268) | 0xCC9268 | 8 | R: 0xe81a6f6 [rsi+0xCC9268] | `0xe81a6f6  mov rcx,[rsi+0xCC9268]` | wrapper whose vtable +0x50 is ExecuteCommandLists (6av) | [V] |
| Present-interval class (this+0x19FD8) | 0x19FD8 | 4 | W: 0xe81a72e [rsi+0x19FD8] | `0xe81a721  mov eax,1<br>0xe81a726  mov ecx,0x10<br>0xe81a72b  cmove ecx,eax<br>0xe81a72e  mov [rsi+0x19FD8],ecx` | = 0x10 when Frame-reset flags (test [rdi+8],0x100 at 0xe81a71a) bit 0x100 set, else 1 (cmove); also consumed as MaxAnisotropy by sampler builder 0xe820500 (`0xe8206ab  mov ebp,[rax+0x19FD8]`, `0xe8207d2  mov [rsp+0x84],ebp` -> D3D12_SAMPLER_DESC+0x14 per 6ax) — dual-purpose field [I naming] | [V] |
| Surface-rebuild mode byte (this+0x19FDC) | 0x19FDC | 1 | R: 0xe81a737 [rsi+0x19FDC]; W: 0xe81a748 [rsi+0x19FDC] | `0xe81a737  movzx ecx,byte ptr [rsi+0x19FDC]<br>0xe81a73e  shr eax,0x11<br>0xe81a741  and eax,1<br>0xe81a744  cmp eax,ecx<br>0xe81a748  mov [rsi+0x19FDC],al` | byte := (Frame-reset flags >> 17) & 1, written only when it differs (je skips the write); when changed, surfaces at this+0x19F60..0x19F68 are rebuilt | [V] |
| Surface vector begin/end (this+0x19F60 / this+0x19F68) | 0x19F60 | 8 | R: 0xe81a74e [rsi+0x19F60]; R: 0xe81a755 [rsi+0x19F68] | `0xe81a74e  mov rbx,[rsi+0x19F60]<br>0xe81a755  mov r14,[rsi+0x19F68]` | [ptr, end) of 8-byte surface pointers walked when this+0x19FDC changed | [V] |
| Surface object pointer (vector element) | 0x0 | 8 | R: 0xe81a770 [rbx] | `0xe81a770  mov rcx,[rbx]` | each surface ptr passed to sub_e81a0c0 | [V] |
| Surface rebuild call | 0xe81a0c0 | - | C: 0xe81a773 | `0xe81a773  call 0xE81A0C0` | sub_e81a0c0(surface) rebuilds one surface (vector element stride 8, `0xe81a778  add rbx,8`) | [V] |
| Frame-reset flag byte (ResetParams+0xA / Frame+0xDC5812) | 0xA | 1 | R: 0xe81a781 [rdi+0xA] | `0xe81a781  movzx eax,byte ptr [rdi+0xA]<br>0xe81a785  shr al,6` | bit 6 gates setting this+0x19F80 bit 0x400000 | [V] |
| Context flags dword (this+0x19F80) | 0x19F80 | 4 | R: 0xe81a788 [rsi+0x19F80]; W: 0xe81a7a4 [rsi+0x19F80]; W: 0xe81a82e [rsi+0x19F80] | `0xe81a788  mov ebp,[rsi+0x19F80]<br>0xe81a78e  test ebp,0x400000<br>0xe81a79e  or ebp,0x400000<br>0xe81a7a4  mov [rsi+0x19F80],ebp<br>0xe81a82e  mov [rsi+0x19F80],eax` | bit 0x400000 set when byte above bit 6 set; then eax = (ResetParams+8 flags) & 0x7FFFFFFF stored here (size-change path at 0xe81a81f..0xe81a82e) | [V] |
| Global dword (data) | 0x12AE0D7C | 4 | W: 0xe81a7aa [0x12AE0D7C] | `0xe81a7aa  mov dword ptr [0x12AE0D7C],0xFFFF` | global set to 0xFFFF during reset (meaning '-') | [V] |
| Context bytes (this+0xC96190, this+0xCBCB18) | 0xC96190 | 1 | W: 0xe81a7b4 [rsi+0xC96190]; W: 0xe81a7bb [rsi+0xCBCB18] | `0xe81a7b4  mov byte ptr [rsi+0xC96190],0<br>0xe81a7bb  mov byte ptr [rsi+0xCBCB18],0` | u8 bytes cleared during reset (meaning '-') | [V] |
| Pending-frame-context ptr (this+0x3C549F0) | 0x3C549F0 | 8 | R: 0xe81a7c2 [rsi+0x3C549F0] | `0xe81a7c2  mov rax,[rsi+0x3C549F0]` | ptr null-checked (`0xe81a7c9  test rax,rax`) before the strided clear loop | [V] |
| Strided clear base (this+0xCE96E8) | 0xCE96E8 | 1 | W: 0xe81a7e0 [rcx], rcx = rsi+0xCE96E8+idx*0x2CBF8 | `0xe81a7ce  lea rcx,[rsi+0xCE96E8]<br>0xe81a7e0  mov byte ptr [rcx],0<br>0xe81a7e6  add rcx,0x2CBF8` | u8 byte at base + idx*0x2CBF8 cleared for idx in [1, count) (meaning '-') | [V] |
| Size-change detected inputs (ResetParams+0 / +4 / +8) | 0x0 | 4 | R: 0xe81a7fa [rdi]; R: 0xe81a7fc [rdi+4]; R: 0xe81a7ff [rsi+0x19F7C]; R: 0xe81a805 [rdi+8] | `0xe81a7fa  xor ecx,[rdi]<br>0xe81a7fc  mov edx,[rdi+4]<br>0xe81a7ff  xor edx,[rsi+0x19F7C]<br>0xe81a805  mov eax,[rdi+8]<br>0xe81a808  xor ebp,eax<br>0xe81a80c  setne bl` | ResetParams dwords compared against context state (0x19F78/0x19F7C/0x19F80); setne bl = any field changed | [V] |
| Copied ResetParams+0 (this+0x19F78) | 0x19F78 | 8 | W: 0xe81a827 [rsi+0x19F78] | `0xe81a81f  and eax,0x7FFFFFFF<br>0xe81a824  mov rcx,[rdi]<br>0xe81a827  mov [rsi+0x19F78],rcx` | qword [ResetParams+0] copied to context when fields changed (field semantics [I]) | [V] |
| Size-change compare outputs (width/height dwords >>3/>>4) | 0x0 | 4 | R: 0xe81a834 [rdi] | `0xe81a834  mov eax,[rdi]<br>0xe81a839  shr eax,3<br>0xe81a842  shr ecx,4` | ResetParams width/height dwords shifted and compared with stored u16 width/height at 0xC9C6C4/0xC9C6C6 (`0xe81a85f  cmp eax,r8d`, `0xe81a86c  cmp ecx,r8d`) | [I] |
| Back-buffer temp buffer pointer (this+0xC9C6B8) | 0xC9C6B8 | 8 | R: 0xe81a84b [rsi+0xC9C6B8]; W: 0xe81a8ea [rsi+0xC9C6B8] | `0xe81a84b  mov rdx,[rsi+0xC9C6B8]<br>0xe81a8ea  mov [rsi+0xC9C6B8],rdx` | u64 pointer to the pixel-count*2 temp buffer; reallocated when pixel count changes; old buffer memcpy'd (`0xe81a902  call 0xEBCE430`), new buffer memzero'd (`0xe81a91d  call 0xEBCE430`) | [V] |
| u16 back-buffer width (this+0xC9C6C4) | 0xC9C6C4 | 2 | R: 0xe81a857 [rsi+0xC9C6C4]; W: 0xe81a885 [rsi+0xC9C6C4] | `0xe81a857  movzx r8d,word ptr [rsi+0xC9C6C4]<br>0xe81a885  mov [rsi+0xC9C6C4],ax` | u16 width rewritten from ResetParams when size changed | [V] |
| u16 back-buffer height (this+0xC9C6C6) | 0xC9C6C6 | 2 | R: 0xe81a864 [rsi+0xC9C6C6]; W: 0xe81a88c [rsi+0xC9C6C6] | `0xe81a864  movzx r8d,word ptr [rsi+0xC9C6C6]<br>0xe81a88c  mov [rsi+0xC9C6C6],cx` | u16 height rewritten from ResetParams when size changed | [V] |
| Size-changed flag (this+0xC9C6C8) | 0xC9C6C8 | 1 | R: 0xe81a871 [rsi+0xC9C6C8]; W: 0xe81a87e [rsi+0xC9C6C8] | `0xe81a871  cmp byte ptr [rsi+0xC9C6C8],0<br>0xe81a87e  mov byte ptr [rsi+0xC9C6C8],0` | u8 flag; zeroed, and the realloc path is skipped when it was 0 (`0xe81a878  je 0xE81A90E`) | [V] |
| Pixel count dword (this+0xC9C6C0) | 0xC9C6C0 | 4 | R: 0xe81a893 [rsi+0xC9C6C0]; W: 0xe81a8a5 [rsi+0xC9C6C0]; R: 0xe81a90e [rsi+0xC9C6C0] | `0xe81a893  mov r14d,[rsi+0xC9C6C0]<br>0xe81a8a1  imul r8d,eax<br>0xe81a8a5  mov [rsi+0xC9C6C0],r8d<br>0xe81a90e  mov r8d,[rsi+0xC9C6C0]` | u32 pixel count = u16 width * u16 height (`0xe81a8a1  imul r8d,eax`); note: live capture read 17040 = 240*71 here and labelled it a tile grid, contradicting the pixel interpretation — live reading [?], static computation [V] | [V] |
| Global allocator (data) | 0x12ADF800 | 8 | R: 0xe81a8ac [0x12ADF800]; R: 0xe81a8bb [rcx]; R: 0xe81a8be [rax+8] | `0xe81a8ac  mov rcx,[0x12ADF800]<br>0xe81a8bb  mov rax,[rcx]<br>0xe81a8be  mov rax,[rax+8]` | global allocator object; allocation via its vtable +8 through thunk `0xe81a8d6  call qword ptr [0xF99FFA0]`; size pixelCount*2 bytes (`0xe81a8b8  add r8d,r8d`) | [V] |
| Width/height dwords stored (this+0x19F90 / this+0x19F94) | 0x19F90 | 4 | W: 0xe81a924 [rsi+0x19F90]; W: 0xe81a92d [rsi+0x19F94] | `0xe81a922  mov eax,[rdi]<br>0xe81a924  mov [rsi+0x19F90],eax<br>0xe81a92a  mov eax,[rdi+4]<br>0xe81a92d  mov [rsi+0x19F94],eax` | u32 width/height dwords stored from ResetParams+0/+4 | [V] |
| Flush-and-wait call (slot 61 helper) | 0xe80ee80 | - | C: 0xe81a938 | `0xe81a938  call 0xE80EE80` | sub_e80ee80(rcx=this, edx=ebx=changed?) flush+wait idle at reset entry (slot 61 path per U-EL2l/6av) | [V] |
| Old command-list wrapper (this+0x2E0) | 0x2E0 | 8 | R: 0xe81a93d [rsi+0x2E0]; R: 0xe81a949 [rcx]; R: 0xe81a94c [rax+0x10]; W: 0xe81a956 [rsi+0x2E0] | `0xe81a93d  mov rcx,[rsi+0x2E0]<br>0xe81a949  mov rax,[rcx]<br>0xe81a94c  mov rax,[rax+0x10]<br>0xe81a956  mov qword ptr [rsi+0x2E0],0` | old wrapper released via its vtable +0x10 (`0xe81a950  call qword ptr [0xF99FFA0]`) then cleared (guard dword at [rsp+0x60] == 1 at `0xe81ab13`) | [V] |
| Swapchain / resize object (this+0x2D8) | 0x2D8 | 8 | R: 0xe81a996 [rsi+0x2D8] | `0xe81a996  mov rcx,[rsi+0x2D8]` | object whose vtable +0x138 performs the back-buffer resize (slot 39 per 6aw; interface name [I]) | [V] |
| Back-buffer count (this+0x19FBC) | 0x19FBC | 4 | R: 0xe81a99d [rsi+0x19FBC] | `0xe81a99d  mov r10d,[rsi+0x19FBC]` | u32 buffer count passed to the resize call | [V] |
| Back-buffer format (this+0x19F98) | 0x19F98 | 4 | R: 0xe81a9a4 [rsi+0x19F98]; R: 0xe81a9fb [rsi+0x19F98] | `0xe81a9a4  mov r11d,[rsi+0x19F98]<br>0xe81a9fb  mov edx,[rsi+0x19F98]` | u32 DXGI format passed to the resize/format-select path | [V] |
| Format class (this+0x19FAC) | 0x19FAC | 4 | R: 0xe81a9b9 [rsi+0x19FAC] | `0xe81a9b9  mov edx,[rsi+0x19FAC]` | u32 format class passed as edx to the resize call | [V] |
| Device object (this+0x400) | 0x400 | 8 | R: 0xe81aaad [rsi+0x400] | `0xe81aaad  mov rcx,[rsi+0x400]` | device; CreateCommittedResource via vtable +0xD8 | [V] |
| Device vtable +0x138 resize call | 0xe81a9c2 | - | R: 0xe81a9bf [rcx]; R: 0xe81a9c2 [rax+0x138]; C: 0xe81a9e7 | `0xe81a9bf  mov rax,[rcx]<br>0xe81a9c2  mov rax,[rax+0x138]<br>0xe81a9e7  call qword ptr [0xF99FFA0]` | back-buffer resize through [this+0x2D8] vtable +0x138 (slot 39 per 6aw) with formatClass/width/height/count/format args; negative HRESULT branches to `0xe81ab33` | [V] |
| Device vtable +0xD8 CreateCommittedResource call | 0xe81aac6 | - | R: 0xe81aac6 [rax+0xD8]; C: 0xe81ab00 | `0xe81aaad  mov rcx,[rsi+0x400]<br>0xe81aac6  mov rax,[rax+0xD8]<br>0xe81ab00  call qword ptr [0xF99FFA0]` | per-buffer committed-resource creation (stack-built desc at rsp+0x40, Format from this+0x19FA0 via `0xe81aa1f  mov [rsi+0x19FA0],rax`); out resource pointer written to [rsp+0x40] | [V] |
| Release guard / Release call | 0xe81ab21 | - | R: 0xe81ab1e [rdi]; R: 0xe81ab21 [rax+0x58]; C: 0xe81ab28 | `0xe81ab0e  mov rdi,[rsp+0x40]<br>0xe81ab1e  mov rax,[rdi]<br>0xe81ab21  mov rax,[rax+0x58]<br>0xe81ab28  call qword ptr [0xF99FFA0]` | Release (vtable +0x58 = slot 2) on the old resource when dword at [rsp+0x60] == 1 (`0xe81ab13  cmp dword ptr [rsp+0x60],1`), per 6aw | [V] |
| Device-lost / init level (this+0x19F88) | 0x19F88 | 4 | R: 0xe81ab49 [rsi+0x19F88]; W: 0xe81ac51 [rsi+0x19F88]; R: 0xe81aba6 [rcx+0x19F88]; W: 0xe81abf2 [rcx+0x19F88] | `0xe81ab49  cmp dword ptr [rsi+0x19F88],5<br>0xe81ac51  mov [rsi+0x19F88],ecx<br>0xe81aba6  cmp dword ptr [rcx+0x19F88],5<br>0xe81abf2  mov [rcx+0x19F88],edx` | u32 init/device-lost level (live: = 5 init-complete); reset failure sets it to 2/3/4 depending on HRESULT; TDR funnel only when >= 5 (`0xe81ab50  jl 0xE81AC5D` skips handling below 5); same offsets on global [0x12BB4910] (live-known RendererContext global, 6b) | [V] |
| HRESULT dword (this+0x19F8C) | 0x19F8C | 4 | W: 0xe81ac57 [rsi+0x19F8C]; W: 0xe81abf8 [rcx+0x19F8C] | `0xe81ab5e  cmp eax,0x887A0004<br>0xe81ab8f  cmp eax,0x88760826<br>0xe81ac57  mov [rsi+0x19F8C],eax<br>0xe81abf8  mov [rcx+0x19F8C],eax` | u32 HRESULT of a failed resize; compared against DXGI_ERROR_UNSUPPORTED 0x887A0004 and device-removed 0x88760826; funnel to TDR code (6ak) when level >= 5 | [V] |
| Live-known context global (data) | 0x12BB4910 | 8 | R: 0xe81ab9f [0x12BB4910] | `0xe81ab9f  mov rcx,[0x12BB4910]` | global context object on the RTX/failure path (identity as RendererContextD3D12 per 6b live correction) | [V] |
| Chosen DXGI format (this+0x19FA0) | 0x19FA0 | 8 | W: 0xe81aa1f [rsi+0x19FA0]; R: 0xe81aa09 [rsi+0x19F80] | `0xe81aa09  mov eax,[rsi+0x19F80]<br>0xe81aa14  lea rcx,[0x1285DC90]<br>0xe81aa1b  mov rax,[rax+rcx]<br>0xe81aa1f  mov [rsi+0x19FA0],rax` | u64 format selected from global table `0x1285DC90` indexed by (flags>>1)&0x38 when format class != current (`0xe81aa26  cmp eax,2`) | [V] |

## Claim lines (verbatim, unindented so verify_oc reads them)

0xe81a635  mov rax,[rcx+0x3C55288]
0xe81a70f  mov qword ptr [rsi+0x3C55288],0
0xe81a666  mov [rsi+r9*8+0x3C55290],r8
0xe81a66e  mov r9,[rsi+0x3C563B0]
0xe81a675  mov r9,[r9+0x28]
0xe81a679  mov [r8+0x2CBD0],r9
0xe81a680  mov byte ptr [r8+0x2CBD8],1
0xe81a688  mov r8,[r8+0x30]
0xe81a6f6  mov rcx,[rsi+0xCC9268]
0xe81a6fd  mov rax,[rcx]
0xe81a700  mov rax,[rax+0x50]
0xe81a709  call qword ptr [0xF99FFA0]
0xe81a71a  test dword ptr [rdi+8],0x100
0xe81a721  mov eax,1
0xe81a726  mov ecx,0x10
0xe81a72b  cmove ecx,eax
0xe81a72e  mov [rsi+0x19FD8],ecx
0xe81a737  movzx ecx,byte ptr [rsi+0x19FDC]
0xe81a73e  shr eax,0x11
0xe81a741  and eax,1
0xe81a744  cmp eax,ecx
0xe81a748  mov [rsi+0x19FDC],al
0xe81a74e  mov rbx,[rsi+0x19F60]
0xe81a755  mov r14,[rsi+0x19F68]
0xe81a770  mov rcx,[rbx]
0xe81a773  call 0xE81A0C0
0xe81a778  add rbx,8
0xe81a781  movzx eax,byte ptr [rdi+0xA]
0xe81a785  shr al,6
0xe81a788  mov ebp,[rsi+0x19F80]
0xe81a78e  test ebp,0x400000
0xe81a79e  or ebp,0x400000
0xe81a7a4  mov [rsi+0x19F80],ebp
0xe81a7aa  mov dword ptr [0x12AE0D7C],0xFFFF
0xe81a7b4  mov byte ptr [rsi+0xC96190],0
0xe81a7bb  mov byte ptr [rsi+0xCBCB18],0
0xe81a7c2  mov rax,[rsi+0x3C549F0]
0xe81a7c9  test rax,rax
0xe81a7ce  lea rcx,[rsi+0xCE96E8]
0xe81a7e0  mov byte ptr [rcx],0
0xe81a7e6  add rcx,0x2CBF8
0xe81a7f4  mov ecx,[rsi+0x19F78]
0xe81a7fa  xor ecx,[rdi]
0xe81a7fc  mov edx,[rdi+4]
0xe81a7ff  xor edx,[rsi+0x19F7C]
0xe81a805  mov eax,[rdi+8]
0xe81a808  xor ebp,eax
0xe81a80c  setne bl
0xe81a81f  and eax,0x7FFFFFFF
0xe81a824  mov rcx,[rdi]
0xe81a827  mov [rsi+0x19F78],rcx
0xe81a82e  mov [rsi+0x19F80],eax
0xe81a834  mov eax,[rdi]
0xe81a839  shr eax,3
0xe81a842  shr ecx,4
0xe81a84b  mov rdx,[rsi+0xC9C6B8]
0xe81a852  test rdx,rdx
0xe81a857  movzx r8d,word ptr [rsi+0xC9C6C4]
0xe81a85f  cmp eax,r8d
0xe81a864  movzx r8d,word ptr [rsi+0xC9C6C6]
0xe81a86c  cmp ecx,r8d
0xe81a871  cmp byte ptr [rsi+0xC9C6C8],0
0xe81a87e  mov byte ptr [rsi+0xC9C6C8],0
0xe81a885  mov [rsi+0xC9C6C4],ax
0xe81a88c  mov [rsi+0xC9C6C6],cx
0xe81a893  mov r14d,[rsi+0xC9C6C0]
0xe81a8a1  imul r8d,eax
0xe81a8a5  mov [rsi+0xC9C6C0],r8d
0xe81a8ac  mov rcx,[0x12ADF800]
0xe81a8bb  mov rax,[rcx]
0xe81a8be  mov rax,[rax+8]
0xe81a8d6  call qword ptr [0xF99FFA0]
0xe81a8ea  mov [rsi+0xC9C6B8],rdx
0xe81a902  call 0xEBCE430
0xe81a90e  mov r8d,[rsi+0xC9C6C0]
0xe81a915  add r8,r8
0xe81a91d  call 0xEBCE430
0xe81a922  mov eax,[rdi]
0xe81a924  mov [rsi+0x19F90],eax
0xe81a92a  mov eax,[rdi+4]
0xe81a92d  mov [rsi+0x19F94],eax
0xe81a938  call 0xE80EE80
0xe81a93d  mov rcx,[rsi+0x2E0]
0xe81a949  mov rax,[rcx]
0xe81a94c  mov rax,[rax+0x10]
0xe81a950  call qword ptr [0xF99FFA0]
0xe81a956  mov qword ptr [rsi+0x2E0],0
0xe81a980  mov rax,[rsi+0xCC9268]
0xe81a996  mov rcx,[rsi+0x2D8]
0xe81a99d  mov r10d,[rsi+0x19FBC]
0xe81a9a4  mov r11d,[rsi+0x19F98]
0xe81a9bf  mov rax,[rcx]
0xe81a9c2  mov rax,[rax+0x138]
0xe81a9e7  call qword ptr [0xF99FFA0]
0xe81a9ed  test eax,eax
0xe81a9ef  js 0xE81AB33
0xe81a9f5  test bpl,0x70
0xe81a9fb  mov edx,[rsi+0x19F98]
0xe81aa01  mov rcx,rsi
0xe81aa04  call 0xE80AFC0
0xe81aa09  mov eax,[rsi+0x19F80]
0xe81aa14  lea rcx,[0x1285DC90]
0xe81aa1b  mov rax,[rax+rcx]
0xe81aa1f  mov [rsi+0x19FA0],rax
0xe81aaad  mov rcx,[rsi+0x400]
0xe81aac6  mov rax,[rax+0xD8]
0xe81ab00  call qword ptr [0xF99FFA0]
0xe81ab0e  mov rdi,[rsp+0x40]
0xe81ab13  cmp dword ptr [rsp+0x60],1
0xe81ab1e  mov rax,[rdi]
0xe81ab21  mov rax,[rax+0x58]
0xe81ab28  call qword ptr [0xF99FFA0]
0xe81ab49  cmp dword ptr [rsi+0x19F88],5
0xe81ab5e  cmp eax,0x887A0004
0xe81ab8f  cmp eax,0x88760826
0xe81ab9f  mov rcx,[0x12BB4910]
0xe81aba6  cmp dword ptr [rcx+0x19F88],5
0xe81abf2  mov [rcx+0x19F88],edx
0xe81abf8  mov [rcx+0x19F8C],eax
0xe81ac51  mov [rsi+0x19F88],ecx
0xe81ac57  mov [rsi+0x19F8C],eax
0xe8206ab  mov ebp,[rax+0x19FD8]
0xe8207d2  mov [rsp+0x84],ebp

## CLOSES?

YES. Every part of the item line "L17a swapchain/DXGI/present and resize (partly hooked) — 6av, 6ay, 6az, 6aw" is now covered by [V] rows: 6av (queue wrapper/slots 8/61/62/kick mechanics, incl. this+0x3C55288 count, this+0x3C563B0 fence, ExecuteCommandLists via this+0xCC9268 vtable +0x50) closed by U-B6/U-EL2l and re-cited here; 6ay (Present slot 6 `0xe811fb0`, SyncInterval bit 7 of this+0x19F80, Flags, extra windows) closed by U-EL17f; 6az (slot 39 `0xe817880` swapchain/create window FB, record fields +0x10/+0x20/+0x30/+0x32) closed by dossiers docs/functions/0xe817880.md, 0xe8176a0.md, 0xe817c00.md; and the pending 6aw reset/resize body is fully decoded statically here: kick+flush entry (`0xe80ee80`), surface rebuild via `0xe81a0c0` over this+0x19F60/68 gated by byte this+0x19FDC := (flags>>17)&1, present-interval class this+0x19FD8 := 1/0x10 (dual-use: MaxAnisotropy for sampler builder 0xe820500 at `0xe8206ab`/`0xe8207d2`, per 6ax), u16 width/height this+0xC9C6C4/0xC9C6C6, pixel count this+0xC9C6C0 = width*height, pixelCount*2 temp buffer via global allocator `0x12ADF800` vtable +8, back-buffer resize via [this+0x2D8] vtable +0x138 (slot 39 per 6aw), CreateCommittedResource via device this+0x400 vtable +0xD8, Release via vtable +0x58 guarded by dword==1, and HRESULT→device-lost funnel (0x887A0004 / 0x88760826) into this+0x19F88/0x19F8C with TDR only when this+0x19F88 >= 5. Non-blocking open items: exact ResetParams field semantics ([I]); live value of this+0xC9C6C0 (17040 = 240*71 tile-grid claim) contradicting the static pixel-count meaning ([?]); chosen-DXGI-format table lookup ([I] table semantics).

## TOOL REQUESTS

None — used only rdis.exe `dis`/`fn` on 0xe81a610 and 0xe820500 plus docs/BGFX_MAP.md sections 6av/6aw/6ax/6ay/6az/6b; no helper scripts written, no temporary files left behind.
