DONE
step 2

# Weather description field map (checklist D6c)

## Loads from description in the case head
    0x66580f0  push rdi
    0x66580f1  or [rax-0x7B],cl
    0x66580f4  shl byte ptr [rcx+rbx*8-0x10],cl
    0x66580f8  inc dword ptr [rdx+8]
    0x66580fb  jmp short 0x66580D0

## Path taken when [r9+0x58] >= 2 and [r9+0x30] != 0 (16-byte {ptr, refcounted ctrl} copy at [rbp+0x400])
    0x5ad5813  mov qword ptr [rbp+0x40],0xFFFFFFFFFFFFFFFE
    0x5ad5849  mov [rbp+0x20],rcx
    0x5ad584d  mov byte ptr [rbp+0x28],0
    0x5ad5855  mov qword ptr [rbp+0x38],0
    0x5ad586d  mov [rbp+0x28],al
    0x5ad5870  mov [rbp+0x10],rdi
    0x5ad5874  mov byte ptr [rbp+0x18],9
    0x5ad58f8  mov [rsp+0x28],rax
    0x5ad58fd  mov dword ptr [rsp+0x20],0

## Table: extractor 0x674A3A0 argument -> description field
| offset | size | store site | read site | name |
|---|---|---|---|---|
| 0x5ad5813 | qword | [rbp+0x40] | — | |
| 0x5ad5849 | qword | [rbp+0x20] | — | |
| 0x5ad584d | byte | [rbp+0x28] | — | |
| 0x5ad5855 | qword | [rbp+0x38] | — | |
| 0x5ad586d | byte | [rbp+0x28] | — | |
| 0x5ad5870 | qword | [rbp+0x10] | — | |
| 0x5ad5874 | byte | [rbp+0x18] | — | |
| 0x5ad58f8 | qword | [rsp+0x28] | — | |
| 0x5ad58fd | dword | [rsp+0x20] | — | |
| 0x66580f0 | — | — | push rdi | |
| 0x66580f1 | — | — | or [rax-0x7B],cl | |
| 0x66580f4 | — | — | shl byte ptr [rcx+rbx*8-0x10],cl | |
| 0x66580f8 | — | — | inc dword ptr [rdx+8] | |
| 0x66580fb | — | — | jmp short 0x66580D0 | |