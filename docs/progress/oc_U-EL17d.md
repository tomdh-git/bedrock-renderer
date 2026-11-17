# UNIT U-EL17d — L17d device lost/TDR — 6ak (slot 7) (BGFX_MAP 6ak)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.
Checklist item: docs/RENDER_CHECKLIST.md line 405 `- [ ] L17d device lost/TDR — 6ak (slot 7)` — whole item is open/pending.
Reference: docs/BGFX_MAP.md section 6ak ("TDR / device-lost and init facts (B5, B8b)").

Method (static analysis only, all from the exe; every quoted instruction below was re-checked against rdis dis on the live exe):
- rdis fn 0xe8102b0 -> sub_e8102b0 [0xe8102b0..0xe811bd4) size 0x1924, 0 xrefs in. Every instruction quoted below is verbatim from rdis dis of that range.
- String contents and jump tables read from .rdata at the RVAs shown by the lea sites (byte-exact vs rdis string comments): state jump table at 0xF4EE60C (4 entries), HRESULT name tables at 0xF4EE61C and 0xF4EE694, DRED op table at 0xF4EE4A8.
- Submit side: rdis fn 0xe82e230 (size 0x4D91), lines e82e81d / e82ef54 / e832b9a / e832c62.
- Vtable/dispatch: rdis vt 0xF4ED2D0 slot 7 (+0x38) -> sub_e8102b0 size 0x1924 [V]; dword at 0xF4ED308 (base vtable slot 7) and at 0xF4EEEB8 (RTX vtable 0xF4EEE80 slot 7) both read back as 0xe8102b0 with the CFG guard bit [V]; slot 7 is not overridden by the RTX class; rdis imm 0xe8102b0 -> 0 hits (no code loads its address as an immediate) [V]; rdis fld 0x38 -> 200 loads of [reg+0x38], none followed within 0x20 bytes by a call of that register [V] - no static call site to slot 7 exists anywhere in .text; it is reached only via virtual dispatch on vtable slot 7. The named _initiateTDR path: FrameBuilder slot 113 (+0x388) = 0x768f0 = a bare ret [V] (fn header: sub_768f0 [0x768f0..0x768f1) size 0x1, 189 xrefs in).
- Submit-side coupling that IS visible [V]: submit writes slot-7's input fields (0xC9C6D0 at e82e81d, qword at 0x19F88 at e82ef54) and reads the queue 0xCC9268 at e832b9a/e832c62.

## NEXT
DONE

## Piece 1 — RendererContext fields read/written by slot 7 (this = rcx/rbx/rsi/rdi)

| offset | size | read/store address | verbatim instr | meaning |
| 0x2D8 | 8 | e8102e0 | e8102e0  cmp qword ptr [rcx+0x2D8],0 | entry gate: slot-7 TDR body runs only when [this+0x2D8] != 0 (and state >= 5) [V] |
| 0x19F88 | 4 | e8102eb | e8102eb  mov ecx,[rcx+0x19F88] | renderer state dword: cmp ecx,5 skips the handler when state < 5; (state-1) indexes jump table 0xF4EE60C (4 entries, states 1..4); re-read at e810398 after the body [V] |
| 0xC9C6D0 | 4 | e810302 | e810302  mov ebx,[rbx+0xC9C6D0] | device-lost error code: slot 7 loads it as ebx (e810302), indexes [this+ebx*8+0x30] at e810390 and passes it as r8d (HRESULT) to the log; submit writes it at e82e81d (from the [this+0x2D8] object's vtable+0x120 result) [V] |
| 0xCC9268 | 8 | e810312 | e810312  mov rcx,[rax+0xCC9268] | D3D12 command queue object (6b: context+0xCC9268 = command queue); slot 7 calls [this+0xCC9268]+0x70 via the CFG thunk at e810328; submit takes its address at e832b9a and e832c62 [V] |
| 0x19F85 | 1 | e8103a9 | e8103a9  cmp byte ptr [rbx+0x19F85],0 | once-only flag: cmp byte [rbx+0x19F85],0 bails if already set; mov byte [rbx+0x19F85],1 sets it at e8103b6 [V] |
| 0x19F8C | 4 | e8103d9 | e8103d9  mov r8d,[rbx+0x19F8C] | HRESULT passed as r8d to the log (call 0xBC5F110) at every failure site: e8103d9, e8103f1, e8104a1, e8104b6, e811a1e, e811aaa [V] |
| 0x400 | 8 | e811a2e | e811a2e  mov rcx,[rbx+0x400] | object pointer; the state-4 path calls [rcx+0x128] on it via the thunk at e811a38 (e811a3f) - GetDeviceRemovedReason-style query [V] |
| 0x30 | 8 | e810390 | e810390  mov [r12+rbx*8+0x30],rax | state-log slot at this+0x30+ebx*8 written by slot 7 itself [V] |

Verbatim proof lines (Piece 1):
```
e8102e0  cmp qword ptr [rcx+0x2D8],0
e8102eb  mov ecx,[rcx+0x19F88]
e810302  mov ebx,[rbx+0xC9C6D0]
e810312  mov rcx,[rax+0xCC9268]
e8103a9  cmp byte ptr [rbx+0x19F85],0
e8103b6  mov byte ptr [rbx+0x19F85],1
e8103d9  mov r8d,[rbx+0x19F8C]
e811a25  cmp r8d,0x887A0005
e811a2e  mov rcx,[rbx+0x400]
e810390  mov [r12+rbx*8+0x30],rax
e82e81d  mov [rsi+0xC9C6D0],eax
e82ef54  mov [rsi+0x19F88],rax
e832b9a  mov rcx,[rdi+0xCC9268]
e832c62  mov rcx,[rcx+0xCC9268]
```

## Piece 2 — Failure/DRED strings referenced by slot 7 (offset = string RVA, size = string byte length [V] from .rdata)

| offset | size | read/store address | verbatim instr | meaning |
| 0xF52121e | 29 | e8103e0 | e8103e0  lea rdx,[0xF52121e] | "Invalid Shader. FAILED 0x%08x" — state 1 of the state jump table (ecx=1) [V] |
| 0xF52123c | 32 | e8104a8 | e8104a8  lea rdx,[0xF52123c] | "Unable Initialize. FAILED 0x%08x" — state 2 (ecx=2) [V] |
| 0xF52125d | 40 | e8103f8 | e8103f8  lea rdx,[0xF52125d] | "Failed to create resource. FAILED 0x%08x" — state 3 (ecx=3) [V] |
| 0xF521278 | 13 | e8104bd | e8104bd  lea rdx,[0xF521278] | "FAILED 0x%08x" — fallback for states outside 1..4 (shared by the e8104b6 path) [V] |
| 0xF83fb15 | 5 | e810c50 | e810c50  lea r9,[0xF83fb15] | " Ops " — DRED breadcrumb label; stored as dword 0x73704F20 at e810c7e [V] |
| 0xF7ca42c | 10 | e810eed | e810eed  lea rbx,[0xF7ca42c] | "UNKNOWN OP" — DRED op-name fallback; real names come from the DRED op table at 0xF4EE4A8 indexed by op id (e810eea/e810f01) [V] |
| 0xF521286 | 17 | e811573 | e811573  lea r8,[0xF521286] | "PageFaultVA %I64x" — DRED page-fault format [V] |
| 0xF840a62 | 27 | e81184f | e81184f  lea rax,[0xF840a62] | "DRED Data unavailable hr = " — DRED fallback [V] |
| 0xF82130d | 33 | e811b14 | e811b14  lea rdx,[0xF82130d] | "Device Lost FAILED 0x%08x %s (%s)" — final TDR message; logged via call 0xBC5F110 at e811b20 [V] |
| 0xF57ef49 | 7 | e811a69 | e811a69  lea rax,[0xF57ef49] | "no info" — HRESULT-name fallback for states outside the table [V] |

Verbatim proof lines (Piece 2):
```
e8103e0  lea rdx,[0xF52121e]
e8104a8  lea rdx,[0xF52123c]
e8103f8  lea rdx,[0xF52125d]
e8104bd  lea rdx,[0xF521278]
e810c50  lea r9,[0xF83fb15]
e810eed  lea rbx,[0xF7ca42c]
e811573  lea r8,[0xF521286]
e81184f  lea rax,[0xF840a62]
e811b14  lea rdx,[0xF82130d]
e811a69  lea rax,[0xF57ef49]
```

## Piece 3 — HRESULT name table entries materialized by slot 7 (offset = string RVA [V] from .rdata)

| offset | size | read/store address | verbatim instr | meaning |
| 0xF7cda28 | 25 | e811a60 | e811a60  lea rax,[0xF7cda28] | "DXGI_ERROR_DEVICE_REMOVED" — HRESULT name table entry (table at 0xF4EE61C, entry 0 = state-4/hr==0x887A0005 path) [V] |
| 0xF7cb1bc | 4 | e811a76 | e811a76  lea rax,[0xF7cb1bc] | "S_OK" — HRESULT name table entry (table at 0xF4EE61C) [V] |
| 0xF7cf670 | 16 | e811a7f | e811a7f  lea rax,[0xF7cf670] | "Unknown HRESULT?" — HRESULT name table entry (table at 0xF4EE61C) [V] |
| 0xF7cc819 | 34 | e811a88 | e811a88  lea rax,[0xF7cc819] | "DXGI_ERROR_NOT_CURRENTLY_AVAILABLE" — HRESULT name table entry (table at 0xF4EE694) [V] |
| 0xF7c8b0b | 23 | e811a91 | e811a91  lea rax,[0xF7c8b0b] | "DXGI_ERROR_DEVICE_RESET" — HRESULT name table entry (table at 0xF4EE694) [V] |
| 0xF7cbacd | 22 | e811a9a | e811a9a  lea rax,[0xF7cbacd] | "DXGI_ERROR_DEVICE_HUNG" — HRESULT name table entry (table at 0xF4EE694) [V] |
| 0xF7c9c32 | 32 | e811aa3 | e811aa3  lea rax,[0xF7c9c32] | "DXGI_ERROR_DRIVER_INTERNAL_ERROR" — HRESULT name table entry (table at 0xF4EE694) [V] |

Verbatim proof lines (Piece 3):
```
e811a60  lea rax,[0xF7cda28]
e811a76  lea rax,[0xF7cb1bc]
e811a7f  lea rax,[0xF7cf670]
e811a88  lea rax,[0xF7cc819]
e811a91  lea rax,[0xF7c8b0b]
e811a9a  lea rax,[0xF7cbacd]
e811aa3  lea rax,[0xF7c9c32]
```

State jump table (decoded from .rdata at 0xF4EE60C, 4 relative i32 entries, base-relative) [V]:
- entry 0 -> e8103d9: "Invalid Shader. FAILED 0x%08x" (state 1)
- entry 1 -> e8104a1: "Unable Initialize. FAILED 0x%08x" (state 2)
- entry 2 -> e8103f1: "Failed to create resource. FAILED 0x%08x" (state 3)
- entry 3 -> e810409: DRED path - if byte [0x12AE16F0]==1 then e811a1e: HRESULT=[rbx+0x19F8C], cmp r8d,0x887A0005 (DXGI_ERROR_DEVICE_REMOVED), GetDeviceRemovedReason via [rbx+0x400]->vtable+0x128, name table 0xF4EE61C, final "Device Lost FAILED 0x%08x %s (%s)" logged via call 0xBC5F110 at e811b20; else flush the log buffers (state 4)

CLOSES? YES - every concrete claim in 6ak about slot 7 is [V]-proven by the rows above: fn 0xe8102b0 size 0x1924 is the device-lost/TDR handler (base vtable 0xF4ED2D0 and RTX vtable 0xF4EEE80, slot 7 at +0x38, dword read-back verified at 0xF4ED308/0xF4EEEB8); the failure strings Invalid Shader / Failed to create resource / Unable Initialize / FAILED 0x%08x; the state->string jump table (0xF4EE60C, states 1..4); the DRED strings Ops / UNKNOWN OP / PageFaultVA %I64x / DRED Data unavailable hr = / no info; the HRESULT name table (DXGI_ERROR_DEVICE_REMOVED, S_OK, Unknown HRESULT?, DXGI_ERROR_NOT_CURRENTLY_AVAILABLE, DXGI_ERROR_DEVICE_RESET, DXGI_ERROR_DEVICE_HUNG, DXGI_ERROR_DRIVER_INTERNAL_ERROR); the final Device Lost FAILED 0x%08x %s (%s) message logged via call 0xBC5F110; and the field reads 0xCC9268 (command queue), 0xC9C6D0, 0x19F85, 0x19F88, 0x19F8C (plus the 0x2D8 gate, 0x400 object, and the 0x30 state-log write). Submit prepares the same inputs [V]: writes 0xC9C6D0 at e82e81d, writes qword {0x887A0005, 4} at 0x19F88 at e82ef54, reads queue 0xCC9268 at e832b9a/e832c62. Dispatch limit noted for the record: slot 7 has no static call site (virtual dispatch only; _initiateTDR stub 0x768f0 is a bare ret) - this is a wiring fact, not part of the item line.

## TOOL REQUESTS
None
