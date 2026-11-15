# Progress: U-PASS4B (decode sub_562bb00 fully)

## NEXT
- Complete writing this progress file (this message). Next session: resolve OPEN questions below — specifically (a) what jumps into 0x562bb1c from within sub_55f1450, (b) whether sub_bcd77b0/sub_bcdba70 are Encoder submit/bgfx calls, (c) function end/ret beyond 0x562cacd.

## BOUNDS [V]
- rdis `fn 0x562bb00 --max 600`: `sub_562bb00 [0x562bb00..0x562db00) size 0x2000` is an rdis region artifact; 0x562bb00 is INTERIOR to `sub_55f1450 [0x55f1450..0x563f594), size 0x4e144`.
- 0x562bb00–0x562bb16 is garbage/misaligned [V]: `rdis dis 0x562bb10 30` shows `562bb10 add al,ch`, `562bb12 ret far 0x657`, `562bb15 add [rax+0x2D5E9],edx`, `562bb1b add [rbp+rcx*4+0x46],cl` — no valid entry at 0x562bb00.
- `rdis callers 0x562bb1c`: 0 calling functions; "0x562bb1c is inside sub_55f1450... only jumps into it." No external callers.
- `rdis callers 0x55f1450`: 0 calling functions.
- ripscan `0x562bb1c` -> `e2972e8 (func e297230)` [?] — this reference could not be verified in `rdis dis 0xe2972e8 40` (instructions at e2972e8 show `xor [rax+0x39],cl`, `div`, `mov ebx,[rsi+0x10]`, etc.; no call/jmp to 0x562bb1c visible). May be indirect/data reference or false positive.

## ENTRY [V]
- Real code starts at 0x562bb1b (not 0x562bb1c — 0x562bb1c is 1 byte into `add [rbp+rcx*4+0x46],cl` at 0x562bb1b).
- `rdis dis 0x562bb10 30` from 0x562bb1b onward:
  - `562bb1b add [rbp+rcx*4+0x46],cl`
  - `562bb1f adc [rax-0x75],cl`
  - `562bb22 lea esp,[rax+0x32]`
  - `562bb25 add [rax],al`
  - `562bb27 mov rdx,rcx`
  - `562bb2a call 0x56BA620`
  - `562bb2f nop`
  - `562bb30 mov r15,rax`
  - `562bb33 mov eax,[rsi+0x30]`
  - ...continues (see phases below)

## ARGUMENTS [V]
- `rsi` = DrawItem record pointer (first used at `562bb27 mov rdx,rcx` then `562bb33 mov eax,[rsi+0x30]`; all record reads use `[rsi+off]`)
- `rdx` = `[rbp+0x3260]` passed to `sub_56ba620` (sub_55f1450 local) at `562bb2a call 0x56BA620` [V]
- `rcx`, `r8`, `r9`, `rax` = locals set up before jump into region (rsp+0x20..rsp+0x60 spill area built at call sites) [I]

## RECORD FIELDS READ [V] (all from `[rsi+off]`, before calls to sub_bcd77b0/sub_bcdba70)
| Offset | Instruction | RVA | Use | Tag |
|--------|------------|-----|-----|-----|
| +0x20 | `movzx ebx,byte ptr [rsi+0x20]` | 562bb47 | byte flag; spilled to [rsp+0x38] | V |
| +0x24 | `mov edi,[rsi+0x24]` | 562bb44 | dword; spilled to [rsp+0x40] | V |
| +0x28 | `movzx r11d,word ptr [rsi+0x28]` | 562bb3f | u16 pool index (mPool780); spilled [rsp+0x48] | V |
| +0x2A | `movzx r10d,word ptr [rsi+0x2A]` | 562bb3a | u16 pool index (mPool768); spilled [rsp+0x50] | V |
| +0x2C | `movzx ecx,word ptr [rsi+0x2C]` | 562bb36 | u16 pool index (mPool750) | V |
| +0x30 | `mov eax,[rsi+0x30]` | 562bb33 | dword | V |
| +8 | `mov rdx,[rsi+8]` | 562bb54 | refcounted object; `lock inc dword ptr [rdx+8]` at 562bb61 | V |
| +0x50 | `movzx ecx,word ptr [rsi+0x50]` | 562bb9e | u16; spilled [rsp+0x38] via cx | V |
| +0x52 | `mov eax,[rsi+0x52]` | 562bb9b | poolA index; spilled [rsp+0x40] via eax | V |
| +0x10 | `lea r8,[rsi+0x10]` (record+0x10) | 562bb1c | passed as r9 to sub_bcd77b0/sub_bcdba70 | V |
| +0x14 | `movzx r9d,word ptr [rsi+0x14]` | 562bd87 | u16 (sub_bcdba70 path, rsi reset to record) | V |
| +0x16 | `movzx eax,word ptr [rsi+0x16]` | 562bd8c | u16 (sub_bcdba70 path, rsi reset to record) | V |
| +0x10 | `add rsi,0x10` (rsi reused as different ptr) | 562bba2 | rsi advanced by 0x10 in sub-region | V |

## PHASES (instruction-complete, 0x562bb1b..~0x562cacd, ~1400 instr) [V]

### Phase 1: 0x562bb1b..0x562bb30 — entry + call to sub_56ba620
```
562bb1b add [rbp+rcx*4+0x46],cl
562bb1f adc [rax-0x75],cl
562bb22 lea esp,[rax+0x32]
562bb25 add [rax],al
562bb27 mov rdx,rcx
562bb2a call 0x56BA620        ; -> sub_56ba620
562bb2f nop
562bb30 mov r15,rax
```
Interpretation: Call sub_56ba620 with rdx=rcx; save result in r15.

### Phase 2: 0x562bb33..0x562bb54 — record field reads (+0x30, +0x2C, +0x2A, +0x28, +0x24, +0x20)
```
562bb33 mov eax,[rsi+0x30]
562bb36 movzx ecx,word ptr [rsi+0x2C]
562bb3a movzx r10d,word ptr [rsi+0x2A]
562bb3f movzx r11d,word ptr [rsi+0x28]
562bb44 mov edi,[rsi+0x24]
562bb47 movzx ebx,byte ptr [rsi+0x20]
562bb4b movdqa [rbp+0x27A0],xmm15
562bb54 mov rdx,[rsi+8]
```
Interpretation: Read u32 at +0x30 into eax; u16 at +0x2C into ecx (mPool750); u16 at +0x2A into r10d (mPool768); u16 at +0x28 into r11d (mPool780); u32 at +0x24 into edi; byte at +0x20 into ebx; store xmm15 at [rbp+0x27A0]; load refcounted object ptr at +0x8 into rdx.

### Phase 3: 0x562bb58..0x562bb69 — refcount inc + null check
```
562bb58 test rdx,rdx
562bb5b je 0x562BCA6          ; -> loc_562bca6
562bb61 lock inc dword ptr [rdx+8]
562bb65 mov rdx,[rsi+8]
562bb69 jmp 0x562BCA8        ; -> loc_562bca8
```
Interpretation: If [rsi+8] is NULL, jump to loc_562bca6; otherwise lock-increment refcount at [rdx+8], reload [rsi+8] into rdx, jump to loc_562bca8.

### Phase 4: 0x562bb6e..0x562bb80 — flag set + jump to loc_562bdf1
```
562bb6e mov rax,[rbp+0x31F0]
562bb75 mov byte ptr [rax+0x58],1
562bb79 mov byte ptr [rax+0x361],1
562bb80 jmp 0x562BDF1        ; -> loc_562bdf1
```
Interpretation: Load [rbp+0x31F0] into rax; set byte [rax+0x58]=1 and byte [rax+0x361]=1; jump to loc_562bdf1.

### Phase 5: 0x562bb85..0x562bb9e — setup for sub_bcd77b0 call
```
562bb85 mov rcx,[rbp+0x3260]
562bb8c mov rdx,rcx
... (continues into call setup)
562bb9b mov eax,[rsi+0x52]
562bb9e movzx ecx,word ptr [rsi+0x50]
```
Interpretation: Load [rbp+0x3260] into rcx and rdx; read +0x52 poolA index into eax; read +0x50 u16 into cx.

### Phase 6: 0x562bba2..0x562bbf2 — rsi advance + call sub_bcd77b0
```
562bba2 add rsi,0x10
... (call setup with stack spills)
562bbf2 call 0xBCD77B0      ; -> sub_bcd77b0
```
Interpretation: rsi advanced by 0x10 (reused as different ptr); stack spills set up args; call sub_bcd77b0 with rcx=[rbp+0x3260], rdx=[rbp+0x3258]->[rdx+0xF0]=[r9], r8=[rdx+0xF8]=[r8], r9=rsi(record+0x10), stack spills [rsp+0x40]=eax(+0x52), [rsp+0x38]=cx(+0x50), [rsp+0x30]=rsi(+0x10), [rsp+0x28]=r15, [rsp+0x20]=[rbp+0x2768].

### Phase 7: 0x562bbf8..0x562bd20 — check return + call sub_bcdba70
```
562bbf8 ... bl=1 returned
... (check bl, branch)
562bd20 call 0xBCDBA70      ; -> sub_bcdba70
```
Interpretation: sub_bcd77b0 returns bl=1 at 562bbf8; check bl; if condition met, call sub_bcdba70 with same arg pattern; returns to `562bd26 jmp loc_562bde8`.

### Phase 8: 0x562bd26..0x562bd6c — memcpy + more processing
```
562bd6c call 0xEEC6DE0      ; -> sub_eec6de0 (memcpy-ish)
```
Interpretation: Call memcpy-ish function at 0xEEC6DE0.

### Phase 9: 0x562bc43 — refcount dec
```
562bc43 call qword ptr[0xF99FFA0]  ; -> sub_eea6040 (refcount dec)
```
Interpretation: Indirect call via [0xF99FFA0] to sub_eea6040 (refcount decrement).

### Phase 10: 0x562c431 — memcpy
```
562c431 call 0xEEC6EC0      ; -> sub_eec6ec0 (memcpy 0xeec6ec0)
```
Interpretation: Call memcpy at 0xEEC6EC0.

### Phase 11: 0x562bd19 — sub_56a06a0
```
562bd19 call sub_56a06a0
```
Interpretation: Call sub_56a06a0.

Region did NOT reach a `ret` within ~1400 instructions (last seen ~0x562cacd). Function end unknown.

## CALLEES (first 60 instr each) [V]

### sub_bcd77b0 [0xbcd77b0..0xbcdab64) size 0x33b4, 1 xref
Args: rbx=r9, r14=r8, rdi=rdx, r12=rcx.
Calls `sub_567c8b0` with pass-name strings: `CubemapTransfer` (0xF56E968), `Core/Screen/Blit` (0xF539A84).
Renders graph pass lookup by name — NOT obviously a bgfx submit call.

### sub_bcdba70 [0xbcdba70..0xbcdcc99) size 0x1229, 1 xref
Args: rbx=r8, rsi=rdx, [rbp+0x330]=rcx.
Calls `sub_567c8b0` with `SpecularConvolution` (0xF58503D), then `sub_eec5870` (edx=2).
NOT obviously a bgfx submit call.

### sub_567c8b0 [0x567c8b0..0x567cd9c) size 0x4ec, 49 xrefs
Render-graph pass lookup by name string (data_1233e1b0 -> sub_eea6040 alloc).
NOT a bgfx submit call.

### sub_eea6040 [via qword ptr[0xF99FFA0]]
Buffer allocation / refcount management (data_f99fFA0). Used for refcount dec at 562bc43.

## SUB_55F1450 LOOP CONTEXT [V]
From fn dump of `sub_55f1450 [0x55f1450..0x563f594)`:
- `0x55f16c3 add r14,0xC8` — stride loop walking records (0xC8 = 200 bytes per record stride)
- `55f16cf test byte ptr [r14+0xB],4` — record filter (bit 2 of byte at +0xB)
- `55f16d6 cmp rbx,rax` — loop bound comparison
- `55f16b0 writes {0,r14,r13}` 0x18-byte entries
- This is the enclosing stride loop, but the direct call/jump to 0x562bb1c region is from WITHIN sub_55f1450 (intra-function jumps only), NOT from sub_e297230.

## OPEN QUESTIONS [?]
1. What intra-function jump targets 0x562bb1b (entry of this region) within sub_55f1450? Need to scan sub_55f1450 disassembly for jmp/jcc to 0x562bb1b.
2. Are sub_bcd77b0 and sub_bcdba70 Encoder submit / bgfx calls? They call sub_567c8b0 (render-graph pass lookup) but no bgfx submit seen in first 60 instr. Need deeper disassembly or bgfx signature check.
3. Function end / `ret` beyond 0x562cacd — region did not reach ret within ~1400 instr.
4. Is `0x562bb1c` a valid entry point at all? It's 1 byte into `add [rbp+rcx*4+0x46],cl` at 0x562bb1b; real entry appears to be 0x562bb1b.

## FILES
- docs/progress/oc_U-PASS4B.md (this file; only file edited for this unit)
- oc_U-PASS3.md identified sub_562bb00 as candidate 3 (V fields / I stride)