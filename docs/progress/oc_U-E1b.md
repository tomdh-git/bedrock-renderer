## NEXT
Step 1: Instruction-complete listing of tag 0 (EnvironmentalText) handler 0x6646a10 and tag 4 (ChunkOccluders) handler 0x6646a89 up to tail call/return, naming the callee that consumes the description.

---

# Unit U-E1b: Item visitor tags 0 and 4

## Step 1: Handler Listings (Instruction-Complete)

### Tag 0: EnvironmentalText handler at 0x6646a10
**Entry**: Jumped to from visitor 0x6646980 jump table (tag 0). `rdi` = description pointer (from visitor arg3+0x0). `rbx` = FrameBuilder `this`. `rbp+0x8A0` = frame context pointer (from visitor arg2).

```
0x6646a10  mov rax, [rdi+0x78]                    ; Load mText.mPtr (SharedRef.ptr)
0x6646a14  test rax, rax
0x6646a17  je 0x664EBD7                           ; -> sub_664ebd7 (early exit if no text object)
0x6646a1d  cmp qword ptr [rax+0x40], 0            ; Check mText.mPtr+0x40 (text object field)
0x6646a22  je 0x664EBD7                           ; -> sub_664ebd7 (early exit if field zero)
0x6646a28  xorps xmm0, xmm0
0x6646a2b  movaps [rbp+0x1A0], xmm0               ; Zero stack buffer (16 bytes)
0x6646a32  mov qword ptr [rbp+0x1B0], 0           ; Zero stack buffer +0x10
0x6646a3d  mov qword ptr [rbp+0x1B8], 0xF         ; Set stack buffer +0x18 = 0xF (capacity/flags)
0x6646a48  mov rcx, [rbp+0x8A0]                   ; Load frame context pointer
0x6646a4f  cmp dword ptr [rcx+0x70], 1            ; Check frame context +0x70 == 1
0x6646a53  setne sil                              ; sil = (context+0x70 != 1)
0x6646a57  or sil, [rdi+0x89]                     ; sil |= description+0x89 (mByte89)
0x6646a5e  test sil, 1
0x6646a62  je 0x66476BB                           ; -> loc_66476bb (alternate path if sil&1==0)
0x6646a68  mov r14, rbx                           ; Save FrameBuilder this
0x6646a6b  lea r9, [0xF563B37]                    ; "MeshFallbackPosUVNormalColor" string
0x6646a72  lea rcx, [rbp+0x1A0]                   ; Stack buffer (output)
0x6646a79  mov edx, 0x1C                          ; Length 28
0x6646a7e  call 0x9D6D0                           ; -> sub_9d6d0 (string copy/init helper)
0x6646a83  nop
0x6646a84  jmp 0x6647BB4                          ; -> loc_6647bb4 (SHARED TAIL)
```

**Tail call**: Jumps to shared tail at **0x6647BB4** (loc_6647bb4), which continues processing and eventually calls **sub_67cfd80** (at 0x6647cbe).

**Callee consuming description**: **sub_67cfd80** (called at 0x6647cbe with `rcx` = frame_context+0x68, `rdx` = stack buffer at rbp+0x5A0, `r8` = stack buffer at rbp+0x140, `r9` = frame_context+0x40). The frame_context = `[FrameBuilder+0xF0]` (set by caller 0x66466e0). The description pointer is NOT in frame_context; it's in visitor's `rdi` (from arg3). sub_67cfd80 likely accesses the description via the visitor stack frame (rdx=rbp) or FrameBuilder.

---

### Tag 4: ChunkOccluders handler at 0x6646a89
**Entry**: Jumped to from visitor 0x6646980 jump table (tag 4). `rdi` = description pointer. `rbx` = FrameBuilder `this` (initially). `rbp+0x8A0` = frame context pointer.

```
0x6646a89  mov r15, rbx                           ; Save FrameBuilder this in r15
0x6646a8c  mov eax, [0x129F9AE0]                  ; TLS guard check 1
0x6646a92  mov ecx, [0x128767C8]
0x6646a98  mov rdx, gs:[0x58]
0x6646aa1  mov rcx, [rdx+rcx*8]
0x6646aa5  cmp eax, [rcx+4]
0x6646aab  jg 0x664EE3A                           ; -> sub_664ee3a (TLS fail)
0x6646ab1  mov rbx, [rbp+0x8A0]                   ; rbx = description pointer (from frame context)
0x6646ab8  mov rcx, [rbx+0x68]                    ; Load description+0x68
0x6646abc  mov eax, [0x129FB1B0]                  ; TLS guard check 2
0x6646ac2  mov edx, [0x128767C8]
0x6646ac8  mov r8, gs:[0x58]
0x6646ad1  mov rdx, [r8+rdx*8]
0x6646ad5  cmp eax, [rdx+4]
0x6646adb  jg 0x664EEA4                           ; -> sub_664eea4 (TLS fail)
0x6646ae1  mov r9, [rbx+0x40]                     ; r9 = description+0x40 (mMesh pointer)
0x6646ae5  lea rax, [0xF2BE528]                   ; "ChunkOccluder" string
0x6646aec  mov [rbp+0x220], rax
0x6646af3  mov qword ptr [rbp+0x228], 0xD         ; String length 13
0x6646afe  lea rax, [0x129FB170]
0x6646b05  mov [rsp+0x28], rax
0x6646b0a  lea rax, [rbp+0x220]
0x6646b11  mov [rsp+0x20], rax
0x6646b16  lea r8, [0x129F9AD0]
0x6646b1d  mov rdx, rbp                           ; Visitor stack frame
0x6646b20  call 0x67D6D70                         ; -> sub_67d6d70 (PRIMARY CALLEE)
0x6646b25  mov rsi, [rbp]                         ; Result from callee (shared_ptr pair)
0x6646b29  mov rbx, [rsi]
0x6646b2c  test rbx, rbx
0x6646b2f  je 0x664E2D6                           ; -> sub_664e2d6 (null result)
0x6646b35  mov eax, [0x129CA5E0]                  ; TLS guard check 3
0x6646b3b  mov ecx, [0x128767C8]
0x6646b41  mov rdx, gs:[0x58]
0x6646b4a  mov rcx, [rdx+rcx*8]
0x6646b4e  cmp eax, [rcx+4]
0x6646b54  jg 0x664EF17                           ; -> sub_664ef17 (TLS fail)
0x6646b5a  cmp byte ptr [rbx+0x10], 1             ; Check result object byte +0x10 == 1
0x6646b5e  jne 0x664E2D6                          ; -> sub_664e2d6 (not valid)
0x6646b64  mov rax, [rsi+8]                       ; Load control block
0x6646b68  test rax, rax
0x6646b6b  je 0x66477CE                           ; -> loc_66477ce (no control block)
0x6646b71  lock inc dword ptr [rax+8]             ; Inc strong ref
0x6646b75  mov rax, [rsi]
0x6646b78  mov r14, [rsi+8]
0x6646b7c  mov rax, [rax+0x18]
0x6646b80  mov rsi, [rax]
0x6646b83  test r14, r14
0x6646b86  je 0x66477D8                           ; -> loc_66477d8 (shared tail)
0x6646b8c  lock dec dword ptr [r14+8]             ; Dec strong ref
0x6646b91  jne 0x66477D8                          ; -> loc_66477d8
0x6646b97  mov rax, [r14]
0x6646b9a  mov rax, [rax]
0x6646b9d  mov rcx, r14
0x6646ba0  call qword ptr [0xF99FFA0]             ; -> sub_eea6040 (destructor)
0x6646ba6  lock dec dword ptr [r14+0xC]           ; Dec weak ref
0x6646bab  jne 0x66477D8                          ; -> loc_66477d8
0x6646bb1  mov rax, [r14]
0x6646bb4  mov rax, [rax+8]
0x6646bb8  mov rcx, r14
0x6646bbb  call qword ptr [0xF99FFA0]             ; -> sub_eea6040 (destructor)
0x6646bc1  jmp 0x66477D8                          ; -> loc_66477d8 (SHARED TAIL)
```

**Tail call**: Jumps to shared tail at **0x66477D8** (loc_66477d8), which merges with other tag handlers and eventually returns to visitor epilogue at 0x6646d5f.

**Callee consuming description**: **sub_67d6d70** (called at 0x6646b20). Arguments:
- `rcx` = r15 = FrameBuilder `this`
- `rdx` = rbp = visitor stack frame (contains description pointer at rbp+0x8A0)
- `r8` = 0x129FB170 (constant data)
- `r9` = description+0x40 (mMesh pointer)
- Stack args: "ChunkOccluder" string + length, 0x129FB170

The callee **sub_67d6d70** performs FNV-1a hash of a 16-byte key at `r8` (0x129FB170), looks up in a hash table in FrameBuilder (at `rcx`+0x58), and calls **sub_567d280** to create/return a render object.

---

## Step 2: Field Read Tables

### Tag 0 (EnvironmentalText) - Handler 0x6646a10 reads from description (`rdi`)

| Offset | Size | Instruction (RVA) | Use | Tag | Field Name (Descriptions.h) |
|--------|------|-------------------|-----|-----|----------------------------|
| +0x78  | 8    | 0x6646a10 `mov rax,[rdi+0x78]` | Read mText.mPtr | 0 | `mText.mPtr` (SharedRef.ptr) |
| +0x78+0x40 | 8 | 0x6646a1d `cmp qword ptr [rax+0x40],0` | Check text object field | 0 | `mText.mPtr+0x40` (text object internal) |
| +0x89  | 1    | 0x6646a57 `or sil,[rdi+0x89]` | Flag test (sil |= byte) | 0 | `mByte89` |
| +0x78 (via rbp+0x8A0) | 8 | 0x6646a48 `mov rcx,[rbp+0x8A0]` then 0x6646a4f `cmp dword ptr [rcx+0x70],1` | Frame context check | 0 | Frame context +0x70 (not description field) |

**Shared tail (0x6647BB4) reads frame_context fields**:
- `frame_context+0x40` and `frame_context+0x68` are loaded (0x6647c1b, 0x6647c1f) and passed to sub_67cfd80 as r9/rcx.
- frame_context = `[FrameBuilder+0xF0]` (set by caller 0x66466e0 at 0x6646765).
- The description pointer is in visitor's `rdi` (from arg3+0x0), not in frame_context.

### Tag 4 (ChunkOccluders) - Handler 0x6646a89 reads

| Offset | Size | Instruction (RVA) | Use | Tag | Field Name |
|--------|------|-------------------|-----|-----|------------|
| frame_ctx+0x68 | 8 | 0x6646ab8 `mov rcx,[rbx+0x68]` | TLS guard check (rbx=frame_context) | 4 | FrameBuilder context field at `[FrameBuilder+0xF0]+0x68` |
| desc+0x40 | 8 | 0x6646ae1 `mov r9,[rbx+0x40]` | **BUG IN ORIGINAL**: rbx=frame_context here! Actually reads frame_context+0x40 | 4 | FrameBuilder context field at `[FrameBuilder+0xF0]+0x40` |

**Correction**: At 0x6646ab1, `rbx` is loaded from `[rbp+0x8A0]` = frame_context (NOT description). So:
- 0x6646ab8 reads **frame_context+0x68** (for TLS check)
- 0x6646ae1 reads **frame_context+0x40** (passed as r9 to sub_67d6d70)

The description pointer is in `rdi` (from visitor entry `mov rdi,[r8]`). The handler does NOT directly read the description struct; it passes frame_context fields to sub_67d6d70.

**Callee sub_67d6d70** (0x67d6d70) receives:
- `rcx` = r15 = FrameBuilder `this`
- `rdx` = rbp = visitor stack frame
- `r8` = 0x129FB170 (constant)
- `r9` = frame_context+0x40 (from handler)
- Stack: "ChunkOccluder" string, 0x129FB170

sub_67d6d70 uses `r9` (frame_context+0x40) as a 16-byte FNV-1a hash key.

---

## Step 3: Live Data Comparison

### Tag 0 (EnvironmentalText) - Live dump sample 0 (descptr=1496E0)

From `docs/data/live/item_visitor.txt` line 6, decoded by `livedec.py`:

| Offset | Raw Bytes (LE) | Decoded Value | Struct Field (Descriptions.h) | Notes |
|--------|----------------|---------------|-------------------------------|-------|
| +0x00  | 00 AB AA 59 46 03 00 00 | ptr-heap 0x34659AAAB00 | `mSource` | |
| +0x08  | B0 AD 52 3D 46 03 00 00 | ptr-heap 0x3463D52ADB0 | `mTexture.mPtr` | |
| +0x10  | A0 AD 52 3D 46 03 00 00 | ptr-heap 0x3463D52ADA0 | `mTexture.mCtrl` | |
| +0x18  | AB AA 2A BC 00 00 00 80 | float2 (-0.010417, 0) | `mMatrix[0..1]` | |
| +0x20  | 93 51 7A 30 00 00 00 00 | other (0x307A5193) | `mMatrix[2..3]` | [I] matrix row 1 |
| +0x28  | 80 00 00 00 AB AA 2A BC | float2 (-0, -0.010417) | `mMatrix[4..5]` | |
| +0x30  | 80 00 00 00 80 00 00 00 | float2 (-0, -0) | `mMatrix[6..7]` | |
| +0x38  | 93 51 7A 30 00 00 00 80 | other | `mMatrix[8..9]` | |
| +0x40  | 80 00 00 00 3C 2A AA AB | float2 (0.010417, -0) | `mMatrix[10..11]` | |
| +0x48  | 20 16 43 42 A0 8C 05 BF | float2 (48.772, -0.52168) | `mMatrix[12..13]` | Translation X,Y |
| +0x50  | 7D C5 51 41 80 00 00 3F | float2 (13.111, 1) | `mMatrix[14..15]` | Translation Z, W=1 |
| +0x58  | 20 16 43 42 A0 8C 05 BF | float2 (48.772, -0.52168) | `mPosition[0..1]` | Matches matrix translation |
| +0x60  | 7D C5 51 41 C4 C3 C3 3E | float2 (13.111, 0.38235) | `mPosition[2], mBlock64[0]` | |
| +0x68  | 6C 6C 3E AC 6C F4 B3 3E | float2 (0.35343, 0.33676) | `mBlock64[1..2]` | |
| +0x70  | 00 00 00 3F 00 00 80 3F | float2 (1, 0) | `mBlock64[3], mPad74` | |
| +0x78  | 70 15 D4 00 46 03 00 00 | ptr-heap 0x34600D41570 | **`mText.mPtr`** | **READ by handler at 0x6646a10** |
| +0x80  | 60 15 D4 00 46 03 00 00 | ptr-heap 0x34600D41560 | `mText.mCtrl` | |
| +0x88  | C4 C3 43 3F FF FF 00 00 | other (0xFFFFC4C3433F) | `mByte88=0x3F, mByte89=0x43, mPad8A=0xC3C4, mParamD8[0]=-1.0` | |
| +0x89  | (byte 1 of +0x88) | **0x43** | **`mByte89`** | **READ by handler at 0x6646a57** |
| +0x8C  | ... | float2... | `mParamD8[1..2]` | |
| ... | ... | ... | ... | |
| +0xE4  | ... | ... | `mFlags` | |

**Handler-read fields verified live**:
- `mText.mPtr` at +0x78 = 0x34600D41570 (non-zero, passes test at 0x6646a14)
- `mText.mPtr+0x40` — not directly observable (points into text object)
- `mByte89` at +0x89 = 0x43 (non-zero, contributes to `sil` flag)

---

### Tag 4 (ChunkOccluders) - **NO LIVE SAMPLES CAPTURED**

The live capture `docs/data/live/item_visitor.txt` contains tags: 10, 6, 7, 0, 1, 2, 3, 1, 3, 0, 7, 6, 2, 10. **Tag 4 is absent**.

**Struct definition (Descriptions.h)** — unchanged, size 0x50:
```cpp
struct RenderChunkOccludersDescription {
    float mTransform[16];      // +0x00
    const void* mMesh;         // +0x40
    uint16_t mValue48;         // +0x48
    uint8_t mPad4A[6];
}; // size 0x50
```

**Handler reads (CORRECTED)**: The handler does NOT read the description struct directly. After `mov rbx, [rbp+0x8A0]` (0x6646ab1), `rbx` = frame_context = `[FrameBuilder+0xF0]`. All subsequent reads via `rbx` are on frame_context:
- 0x6646ab8: `mov rcx, [rbx+0x68]` → reads **frame_context+0x68** (TLS guard)
- 0x6646ae1: `mov r9, [rbx+0x40]` → reads **frame_context+0x40**, passed to sub_67d6d70 as hash key

The description pointer is in `rdi` (from visitor entry) but unused in this handler path.

**Callee sub_67d6d70** reads 16 bytes from `r9` (frame_context+0x40) as FNV-1a hash key. The description's mMesh at +0x40 is NOT read by this handler.

---

## Gaps / Open Questions (RESOLVED 1-3)

1. **[RESOLVED: 0x6646ab8]** Tag 4 handler `mov rbx, [rbp+0x8A0]` (0x6646ab1) loads the **frame_context pointer**, not the description pointer. The frame_context is set by the visitor caller (0x66466e0) at `mov rax,[rsi+0xF0]; mov [rbp-0x28],rax` where rsi=FrameBuilder this, so frame_context = `[FrameBuilder+0xF0]`. The subsequent `mov rcx, [rbx+0x68]` (0x6646ab8) reads **frame_context+0x68 = [FrameBuilder+0xF0]+0x68**, NOT description+0x68. The description pointer is in `rdi` (from visitor arg3+0x0). The RenderChunkOccludersDescription size 0x50 is correct; the +0x68 read is on a different object (frame_context).

   Evidence (caller 0x66466e0 -> visitor 0x6646980 -> tag4 0x6646a89):
   - 0x6646765: `mov rax,[rsi+0xF0]; mov [rbp-0x28],rax` — frame_context = [FrameBuilder+0xF0]
   - 0x6646844: `lea rdx,[rbp-0x28]` — arg2 = frame_context
   - 0x6646980: `mov [rbp+0x8A0],rdx` — store frame_context
   - 0x6646ab1: `mov rbx,[rbp+0x8A0]` — rbx = frame_context
   - 0x6646ab8: `mov rcx,[rbx+0x68]` — reads frame_context+0x68

2. **[RESOLVED: 0x6646a1d]** Tag 0 handler: `rax = [rdi+0x78]` = `description.mText.mPtr` (SharedRef.ptr to text object). The check `cmp qword ptr [rax+0x40], 0` reads the **text object's +0x40 field**. The text object is the font atlas GPU texture/resource created by `sub_4dfb570` (resolveTexture) from the description's mTexture SharedRef. `sub_4dfb570` takes a texture reference and returns a SharedRef to a texture resource object; the text object at mText.mPtr is this resource. Offset +0x40 in this resource object is a valid field (likely a GPU resource pointer or state flag). The handler validates the text resource is properly initialized before proceeding.

   Evidence (builder 0x668b400 -> handler 0x6646a10):
   - 0x668b532: `mov rcx,[r12]` — rcx = texture resource ptr
   - 0x668b53e: `mov [rsi+0x78],rcx` — description.mText.mPtr = texture resource
   - 0x6646a10: `mov rax,[rdi+0x78]` — rax = mText.mPtr
   - 0x6646a1d: `cmp qword ptr [rax+0x40],0` — check texture_resource+0x40

3. **[RESOLVED: 0x6647cbe]** Shared tail at 0x6647c14-0x6647c1f loads `frame_context+0x40` and `frame_context+0x68` into r12/r13, passes as r9/rcx to sub_67cfd80 (0x6647cbe). Since frame_context = `[FrameBuilder+0xF0]` (from caller 0x66466e0), these are:
   - `frame_context+0x40` = `[FrameBuilder+0xF0]+0x40` → passed as **r9** to sub_67cfd80
   - `frame_context+0x68` = `[FrameBuilder+0xF0]+0x68` → passed as **rcx** to sub_67cfd80

   These are fields of the FrameBuilder-derived context object (not the description). The description pointer itself is accessed via the frame_context by sub_67cfd80 (which reads it from frame_context+0x0 or similar).

   Evidence (shared tail 0x6647BB4):
   - 0x6647c14: `mov rax,[rbp+0x8A0]` — rax = frame_context
   - 0x6647c1b: `mov r12,[rax+0x40]` — r12 = frame_context+0x40
   - 0x6647c1f: `mov r13,[rax+0x68]` — r13 = frame_context+0x68
   - 0x6647cbe: `call 0x67CFD80` — rcx=r13, r9=r12

4. **Missing live data**: Tag 4 (ChunkOccluders) has no live captures. Request orchestrator to add tag 4 to livecap targets.

5. **[UNVERIFIED: 0x67d6d70 +0xE4]** sub_67d6d70 reads `r14+0xE4` (FrameBuilder+0xE4) compared to 0x7FFFFFFF. Purpose unknown.

---

## TOOL REQUESTS

| Name | Input -> Output | Why it would help |
|------|-----------------|-------------------|
| `descscan2.py` enhancement | RVA + reg -> field read table with callee tracing | Currently casewalk.py walks entire visitor CFG; need per-handler isolation. Manual filtering is error-prone. |
| `livedec.py` struct-aware mode | Live dump + struct definition -> mapped fields | Currently outputs generic float2/ptr-heap; would be faster to auto-map to struct field names. |
| Jump table cross-ref | JT RVA -> tag->handler mapping (already have jt.py) | jt.py works well; no new tool needed. |

---

## Verification Lines for verify_oc.py

### Tag 0 handler (0x6646a10 - 0x6646a84)
0x6646a10  mov rax,[rdi+78]
0x6646a14  test rax,rax
0x6646a17  je 0x664ebd7
0x6646a1d  cmp qword ptr [rax+40],0
0x6646a22  je 0x664ebd7
0x6646a28  xorps xmm0,xmm0
0x6646a2b  movaps [rbp+1a0],xmm0
0x6646a32  mov qword ptr [rbp+1b0],0
0x6646a3d  mov qword ptr [rbp+1b8],f
0x6646a48  mov rcx,[rbp+8a0]
0x6646a4f  cmp dword ptr [rcx+70],1
0x6646a53  setne sil
0x6646a57  or sil,[rdi+89]
0x6646a5e  test sil,1
0x6646a62  je 0x66476bb
0x6646a68  mov r14,rbx
0x6646a6b  lea r9,[0xf563b37]
0x6646a72  lea rcx,[rbp+1a0]
0x6646a79  mov edx,1c
0x6646a7e  call 0x9d6d0
0x6646a83  nop
0x6646a84  jmp 0x6647bb4

### Tag 4 handler (0x6646a89 - 0x6646bc1)
0x6646a89  mov r15,rbx
0x6646a8c  mov eax,[0x129f9ae0]
0x6646a92  mov ecx,[0x128767c8]
0x6646a98  mov rdx,gs:[58]
0x6646aa1  mov rcx,[rdx+rcx*8]
0x6646aa5  cmp eax,[rcx+4]
0x6646aab  jg 0x664ee3a
0x6646ab1  mov rbx,[rbp+8a0]
0x6646ab8  mov rcx,[rbx+68]
0x6646abc  mov eax,[0x129fb1b0]
0x6646ac2  mov edx,[0x128767c8]
0x6646ac8  mov r8,gs:[58]
0x6646ad1  mov rdx,[r8+rdx*8]
0x6646ad5  cmp eax,[rdx+4]
0x6646adb  jg 0x664eea4
0x6646ae1  mov r9,[rbx+40]
0x6646ae5  lea rax,[0xf2be528]
0x6646aec  mov [rbp+220],rax
0x6646af3  mov qword ptr [rbp+228],d
0x6646afe  lea rax,[0x129fb170]
0x6646b05  mov [rsp+28],rax
0x6646b0a  lea rax,[rbp+220]
0x6646b11  mov [rsp+20],rax
0x6646b16  lea r8,[0x129f9ad0]
0x6646b1d  mov rdx,rbp
0x6646b20  call 0x67d6d70
0x6646b25  mov rsi,[rbp]
0x6646b29  mov rbx,[rsi]
0x6646b2c  test rbx,rbx
0x6646b2f  je 0x664e2d6
0x6646b35  mov eax,[0x129ca5e0]
0x6646b3b  mov ecx,[0x128767c8]
0x6646b41  mov rdx,gs:[58]
0x6646b4a  mov rcx,[rdx+rcx*8]
0x6646b4e  cmp eax,[rcx+4]
0x6646b54  jg 0x664ef17
0x6646b5a  cmp byte ptr [rbx+10],1
0x6646b5e  jne 0x664e2d6
0x6646b64  mov rax,[rsi+8]
0x6646b68  test rax,rax
0x6646b6b  je 0x66477ce
0x6646b71  lock inc dword ptr [rax+8]
0x6646b75  mov rax,[rsi]
0x6646b78  mov r14,[rsi+8]
0x6646b7c  mov rax,[rax+18]
0x6646b80  mov rsi,[rax]
0x6646b83  test r14,r14
0x6646b86  je 0x66477d8
0x6646b8c  lock dec dword ptr [r14+8]
0x6646b91  jne 0x66477d8
0x6646b97  mov rax,[r14]
0x6646b9a  mov rax,[rax]
0x6646b9d  mov rcx,r14
0x6646ba0  call qword ptr [0xf99ffa0]
0x6646ba6  lock dec dword ptr [r14+c]
0x6646bab  jne 0x66477d8
0x6646bb1  mov rax,[r14]
0x6646bb4  mov rax,[rax+8]
0x6646bb8  mov rcx,r14
0x6646bbb  call qword ptr [0xf99ffa0]
0x6646bc1  jmp 0x66477d8