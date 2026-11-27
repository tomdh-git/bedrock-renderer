# Dossier: sub_ebce570 (0xebce570)

Generated/lifted from `Minecraft.Windows.exe` 1.26.62.01. Mechanical facts read from the disassembly; analyst claims carry [V]/[I]/[?] tags.

## Mechanical facts

- size 0x5c bytes per docs/data/native_functions.tsv, range [0xebce570, 0xebce5cc)
- 0 direct callees, 0 indirect callees, no calls, no writes
- stack: leaf function, no prologue, no frame
- return: eax (int32_t)

### Argument use

- rcx = a0: pointer to { char* ptr @+0x0; int32_t size @+0x8 }; reads a0->size (+0x8), a0->ptr (+0x0), bytes through a0->ptr [V]
- rdx = a1: pointer to { char* ptr @+0x0; int32_t size @+0x8 }; reads a1->size (+0x8), a1->ptr (+0x0), bytes through a1->ptr [V]
- r8d = count: int32 bound [V]

### Direct callees

none [V]

### Indirect calls

none [V]

### Strings

none [V]

### Loops

- 0xebce5a0..0xebce5c0 (compare loop, back-edge 0xebce5c0 -> 0xebce5a0) [V]

### Notable constants

0x7FFFFFFF seen as count at callers (e.g. 0xbc601a8) [I]

## Reversed source (complete)

The function is a bounded strncmp-like compare: bound = min(a0->size, a1->size, count) with signed compares, then a byte loop that returns (signed char)*a0 - (signed char)*a1 on the first difference or on null termination, and 0 when the bound is exhausted with equal size-mins. Every instruction of [0xebce570, 0xebce5cc) is cited below; the contiguous difference block [0xebce5cc, 0xebce5d6) is cited for completeness (it is reached by branches from within the function).

Bound computation  // 0xebce570..0xebce5a0
```
0xebce570  cmp [rdx+8],r8d           ; a1->size vs count
0xebce574  mov r11d,r8d              ; r11d = count
0xebce577  mov r9,[rdx]              ; r9 = a1->ptr
0xebce57a  mov r10d,r8d              ; r10d = count
0xebce57d  cmovl r11d,[rdx+8]        ; r11d = min(count, a1->size)  [signed]
0xebce582  cmp [rcx+8],r8d           ; a0->size vs count
0xebce586  mov rdx,[rcx]             ; rdx = a0->ptr (overwrites a1->ptr)
0xebce589  cmovl r10d,[rcx+8]        ; r10d = min(count, a0->size)  [signed]
0xebce58e  cmp r10d,r11d
0xebce591  mov eax,r10d              ; eax = r10d
0xebce594  cmovge eax,r11d           ; eax = min(r10d,r11d) = bound
0xebce598  test eax,eax
0xebce59a  jle short 0xEBCE5C2       ; bound <= 0 -> epilogue
0xebce59c  nop [rax]
```
Compare loop  // 0xebce5a0..0xebce5c0
```
0xebce5a0  movzx ecx,byte ptr [r9]   ; cl = (unsigned char)*a1_ptr
0xebce5a4  movzx r8d,byte ptr [rdx]  ; r8b = (unsigned char)*a0_ptr
0xebce5a8  cmp r8b,cl                ; compare *a0_ptr vs *a1_ptr
0xebce5ab  jne short 0xEBCE5CC       ; differ -> difference
0xebce5ad  test r8b,r8b              ; *a0_ptr == 0 ?
0xebce5b0  je short 0xEBCE5CC        ; null -> difference
0xebce5b2  test cl,cl                ; *a1_ptr == 0 ?
0xebce5b4  je short 0xEBCE5CC        ; null -> difference
0xebce5b6  inc rdx                   ; a0_ptr++
0xebce5b9  inc r9                    ; a1_ptr++
0xebce5bc  dec eax                   ; count--
0xebce5be  test eax,eax
0xebce5c0  jg short 0xEBCE5A0        ; count > 0 -> loop
```
Epilogue (equal-within-bound)  // 0xebce5c2..0xebce5cc
```
0xebce5c2  jne short 0xEBCE5CC       ; taken only if bound was negative
0xebce5c4  cmp r10d,r11d             ; a0-size-min vs a1-size-min
0xebce5c7  jne short 0xEBCE5CC       ; size-mins differed -> difference
0xebce5c9  xor eax,eax               ; return 0 (equal)
0xebce5cb  ret
```
Difference  // 0xebce5cc..0xebce5d6
```
0xebce5cc  movsx eax,byte ptr [rdx]  ; eax = (signed char)*a0_ptr
0xebce5cf  movsx ecx,byte ptr [r9]   ; ecx = (signed char)*a1_ptr
0xebce5d3  sub eax,ecx               ; return *a0 - *a1
0xebce5d5  ret
```

Struct fields touched (offset, size, direction, meaning, tag):
- a0->size +0x08, 4 bytes, R, int32 size field [V]
- a0->ptr +0x00, 8 bytes, R, char* pointer [V]
- bytes through a0->ptr, R, compared payload [V]
- a1->size +0x08, 4 bytes, R, int32 size field [V]
- a1->ptr +0x00, 8 bytes, R, char* pointer [V]
- bytes through a1->ptr, R, compared payload [V]

Callees: none (0 in lift set, 0 outside). No boundary calls, no unresolved calls.

## Ownership / threading

Pure function: reads only, writes nothing, no calls. Thread-safe for immutable inputs. [V]

## Verification

liftcheck target: `python tools/sigs/liftcheck.py 0xebce570` -> expect `LIFTCHECK OK 0xebce570`. [V]
