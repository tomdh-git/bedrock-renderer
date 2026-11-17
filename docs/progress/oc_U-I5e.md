## NEXT
Step 1 complete. Step 2: list vtable slots at 0xF2BE2F8 and 10 callers of sub_2FE330 with string args. Step 3: find constructor of a0 object (stores to [a0+0x20], +0xF0, +0x100, +0x260, +0x380).

## Step 1: Who invokes sub_6664760 and what builds its a0 object

### sub_6664760 (FrameBuilder - Insert UI) at 0x6664760
- **No direct callers**: `python tools/sigs/xref.py callers 0x6664760` returns empty. `rdis xr 0x6664760` shows 0 xrefs.
- **Invoked via vtable**: Found in vtable at **0xF2BE1F8** (slot 4, offset +0x20):
  ```
  0xF2BE1F8+0x00: sub_668ACC0
  0xF2BE1F8+0x08: sub_6685F30
  0xF2BE1F8+0x10: sub_6674050 (FrameBuilder - Insert editor)
  0xF2BE1F8+0x18: sub_666AA00 (FrameBuilder - Insert effect)
  0xF2BE1F8+0x20: sub_6664760 (FrameBuilder - Insert UI)  <-- TARGET
  0xF2BE1F8+0x28: sub_6655DE0 (FrameBuilder - Insert sky)
  0xF2BE1F8+0x30: sub_66466E0 (FrameBuilder - Insert item)
  0xF2BE1F8+0x38: sub_6640AE0 (FrameBuilder - Insert light)
  0xF2BE1F8+0x40: sub_768F0
  ```
  [V] Verified via `rdis vt 0xF2BE1F8` and raw .rdata dump.

- **Call to sub_2FE330 at 0x6664955**:
  ```
  666492f  lea rax,[0xF2BE2F8]          ; [data_f2be2f8]
  6664936  mov [rsp+0x28],rax           ; 6th stack arg -> becomes a4 (r14) in sub_2FE330
  666493b  mov dword ptr [rsp+0x20],0   ; 5th stack arg -> becomes a5 (ebp) in sub_2FE330
  6664943  lea rcx,[0x129FAD98]         ; 1st arg (a0)
  666494a  lea rdx,[rbp-0x50]           ; 2nd arg (a1)
  666494e  lea r9,[rbp+0x50]            ; 4th arg (a3) -> points to "FrameBuilder - Insert UI" string
  6664952  mov r8b,1                    ; 3rd arg (a2) = 1
  6664955  call 0x2FE330                ; -> sub_2FE330
  ```
  [V] Verified via `rdis dis 0x66648D0 100`.

### Data at 0xF2BE2F8 (passed as a4 to sub_2FE330)
Raw bytes (from .rdata at file offset 0xF2BCCF8):
```
+0x000: 0x000000014F578D05  (non-code, > .text range)
+0x008: 0x000000014F821C69  (non-code)
+0x010: 0x00000054000009A9  (non-code)
+0x018: 0x0000005000000058  (non-code)
+0x020: 0x000000014F578D05
+0x028: 0x000000014F821B6C
+0x030: 0x00000058000009AE
+0x038: 0x0000005400000058
+0x040: 0x000000014F578D05
+0x048: 0x000000014F821BC1
+0x050: 0x00000058000009B4
+0x058: 0x0000005400000058
+0x060: 0x00000001467ED670  -> CODE RVA 0x67ED670 (sub_67ED670)  [V]
+0x068: 0x3F800000BF800000  (float data)
+0x070: 0x3F8000003F800000
...
```
**Conclusion**: 0xF2BE2F8 is NOT a vtable containing 0x6664760. It is a data table with one code pointer at slot 12 (offset 0x60) pointing to **sub_67ED670**. The sibling slots (0-11, 13+) contain non-code data (appear to be float constants and large integers).

### sub_67ED670 (at 0x67ED670, from slot 12 of 0xF2BE2F8)
```
sub_67ED670:
  67ED670  push rsi
  67ED671  push rdi
  67ED672  push rbx
  67ED673  sub rsp,0x20
  67ED677  mov edi,edx
  67ED679  mov rsi,rcx
  67ED67C  lea rax,[0xF2BE358]        ; vtable for task object
  67ED683  mov [rcx],rax              ; W a0+0x0 = vtable pointer
  67ED686  mov rbx,[rcx+0x18]         ; R a0+0x18
  67ED68A  test rbx,rbx
  67ED68D  je short 0x67ED6A4
  67ED68F  mov rcx,rbx
  67ED692  call 0x67CD130
  67ED697  mov edx,0x130
  67ED69C  mov rcx,rbx
  67ED69F  call 0xE935700
  ...
```
This function writes the vtable pointer (0xF2BE358) to [a0+0x0] and appears to be a destructor/cleanup function for the task object.

### Vtable at 0xF2BE358 (referenced by sub_67ED670)
```
+0x000: 0x00000001467ED670 -> code RVA 0x67ED670 (self-referential first slot)
+0x008: 0x3F800000BF800000 (float data)
...
```
Only slot 0 is a code pointer (back to sub_67ED670).

## Step 2: Vtable slots at 0xF2BE2F8 and 10 callers of sub_2FE330

### 0xF2BE2F8 slots summary
| Slot | Offset | Value | Type |
|------|--------|-------|------|
| 0 | +0x00 | 0x14F578D05 | non-code |
| 1 | +0x08 | 0x14F821C69 | non-code |
| 2 | +0x10 | 0x54000009A9 | non-code |
| 3 | +0x18 | 0x5000000058 | non-code |
| 4 | +0x20 | 0x14F578D05 | non-code |
| 5 | +0x28 | 0x14F821B6C | non-code |
| 6 | +0x30 | 0x58000009AE | non-code |
| 7 | +0x38 | 0x5400000058 | non-code |
| 8 | +0x40 | 0x14F578D05 | non-code |
| 9 | +0x48 | 0x14F821BC1 | non-code |
| 10 | +0x50 | 0x58000009B4 | non-code |
| 11 | +0x58 | 0x5400000058 | non-code |
| 12 | +0x60 | **0x1467ED670** | **code -> sub_67ED670** [V] |
| 13+ | +0x68... | float data | non-code |

### 10 callers of sub_2FE330 (FrameBuilder family) with string arguments
All follow the same pattern: load string pointer, load data table pointer, call sub_2FE330.

| # | Caller RVA | Call Site RVA | String (RVA) | String Text | Data Table (RVA) |
|---|------------|---------------|--------------|-------------|------------------|
| 1 | 0x660B1A0 | 0x660B507 | 0xF52E07A | "FrameBuilder - Insert" | 0xF2BDAD0 |
| 2 | 0x6640AE0 | 0x6640CD1 | 0xF53AEA6 | "FrameBuilder - Insert light" | 0xF2BE298 |
| 3 | 0x66466E0 | 0x66468D5 | 0xF59F12F | "FrameBuilder - Insert item" | 0xF2BE2B8 |
| 4 | 0x6655DE0 | 0x6656044 | 0xF51B8A2 | "FrameBuilder - Insert sky" | 0xF2BE2D8 |
| 5 | 0x6664760 | 0x6664955 | 0xF7CB7C5 | "FrameBuilder - Insert UI" | 0xF2BE2F8 |
| 6 | 0x666AA00 | 0x666ABF5 | 0xF540E58 | "FrameBuilder - Insert effect" | 0xF2BE318 |
| 7 | 0x6674050 | 0x6674241 | 0xF55F87E | "FrameBuilder - Insert editor" | 0xF2BE338 |
| 8 | 0x66232B0 | 0x662E536 | 0xF56F675 | "FrameBuilder - End frame wait for render" | 0xF2BE278 |
| 9 | 0xE71330 | 0xE7228C | 0xF52E07A | "FrameBuilder - Insert" | (different) |
| 10 | 0xE9AED0 | 0xE9B8F6 | 0xF52E07A | "FrameBuilder - Insert" | (different) |

**Pattern**: Each caller:
1. `lea rax, [string]` -> `mov [rbp+0x50], rax`
2. `mov qword ptr [rbp+0x58], <length>`
3. `movups xmm0, [0xF0BCBF8]` -> `movaps [rbp-0x50], xmm0`
4. `lea rax, [data_table]` -> `mov [rsp+0x28], rax`
5. `mov dword ptr [rsp+0x20], 0` (or 0xFF0000 for endFrame)
6. `lea rcx, [data_129Fxxx]` -> `lea rdx, [rbp-0x50]` -> `lea r9, [rbp+0x50]` -> `mov r8b, 1` (or 2)
7. `call 0x2FE330`

[V] Verified via disassembly of each caller (0x660B1A0, 0x6640AE0, 0x66466E0, 0x6655DE0, 0x6664760, 0x666AA00, 0x6674050, 0x66232B0, 0xE71330, 0xE9AED0).

## Step 3: a0 object constructor (stores to [a0+0x20], +0xF0, +0x100, +0x260, +0x380)

### Offsets read by sub_6664760 from a0 (rsi):
```
66647DE  mov rax,[rsi+0xF0]      ; R a0+0xF0
66647E5  mov [rbp-0x28],rax
66647F9  mov rax,[rsi+0x380]     ; R a0+0x380
6664800  mov [rbp-0x18],rax
6664804  lea rax,[rsi+0x100]     ; R a0+0x100 (address)
666480B  mov [rbp-0x10],rax
666480F  mov rax,[rsi+0x260]     ; R a0+0x260
6664816  mov [rbp-8],rax
666481A  mov rax,[rsi+0x28]      ; R a0+0x28
666481E  mov rax,[rax+0x18]      ; R *(a0+0x28)+0x18
...
6664868  mov rax,[rsi+0x20]      ; R a0+0x20
666486C  mov rax,[rax+0x3A8]     ; R *(a0+0x20)+0x3A8
```

### Constructor search
The a0 object is passed to sub_6664760 in RCX (moved to RSI). The constructor must initialize:
- [a0+0x20] - pointer to object with field at +0x3A8
- [a0+0xF0] - pointer
- [a0+0x100] - address taken (lea), likely embedded sub-object
- [a0+0x260] - pointer
- [a0+0x380] - pointer

**Search for stores to these offsets on same base register**:
- `rdis rw 0x380` shows 125 functions, including `sub_78F7ED0` at 0x78F7EEB: `mov [rcx+0x380], rax` (writes sub_11D3EF0)
- `rdis rw 0x20` shows 149 functions, too many to filter manually
- Need function that writes to **all five offsets** on same object

**Candidate**: `sub_78F7ED0` (at 0x78F7ED0) writes to:
- [rcx+0x380] at 0x78F7EEB: `mov [rcx+0x380], rax` (value = sub_11D3EF0)
- [rcx+0x3A0] at 0x78F80D3: `mov [rcx+0x3A0], rax` (value = sub_11D3D60)
- [rcx+0x368] at 0x78F80BA: `mov [rcx+0x368], r13`
- Many other offsets in 0x200-0x300 range

But does not obviously write to 0x20, 0xF0, 0x100, 0x260.

**Another candidate**: The vtable at 0xF2BDAD0 (for "FrameBuilder - Insert" base) has slots pointing to:
- +0x40: sub_660B8F0 (copies a0+0x8, +0x18, +0x28 to a1)
- +0x50: sub_660B920 (complex comparison)
- +0x58: sub_660C1E0 (returns data_125D14B0)
- +0x60: sub_718D20 (destructor)
- +0x68: sub_79570 (returns a0+0x8)

**Gap**: Could not definitively identify single constructor function writing all 5 offsets. The object appears to be a FrameBuilder task context built incrementally.

[UNVERIFIED: 0x78F7ED0 question] Does sub_78F7ED0 construct the a0 object for FrameBuilder tasks? It writes to +0x380 but not clearly to +0x20, +0xF0, +0x100, +0x260.

[UNVERIFIED: 0xF2BE1F8 question] What code loads the BgfxFrameBuilder vtable (0xF2BE1F8) into objects? No rip-relative or immediate references found to 0xF2BE1F8.

## Verification
Run `python tools/sigs/verify_oc.py docs/progress/oc_U-I5e.md`

## TOOL REQUESTS
- Need better cross-reference search for vtable usage (constructor pattern: lea rax, [vtable] + mov [rcx], rax)
- Need field-write correlation tool: given function, list all [reg+off] writes grouped by base register
- The `descscan2.py` script failed with argument parsing error; needs fix for explicit --start/--end mode