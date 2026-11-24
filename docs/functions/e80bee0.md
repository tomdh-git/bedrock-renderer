# sub_e80bee0 — RendererContextD3D12 base slot 58

- RVA: 0xe80bee0, size 0xa5 (1.26.62.01)
- Lifted at: `src/client/features/render/native/d3d12/sub_e80bee0.cpp` (+ `.h`), registry entry `LIFT_FN(sub_e80bee0, "RendererContextD3D12 base slot 58", 0xe80bee0, sub_e80bee0, nullptr)`.
- Role [V]: initialise a 256-entry table embedded in the `RendererContextD3D12` object and set its ready flag.

## Signature

`extern "C" void sub_e80bee0(void* a0, void* a1)`
- `a0` = rcx = `this` (`RendererContextD3D12*`), later rsi/r15.
- `a1` = rdx = object pointer (rdi) stored into every one of the 256 table entries.
- returns void.

## Register map

- rsi = a0 (this); r12 = a0 + 0x10000 (table base); r15 = per-call cursor starting at a0, +=0x100.
- rdi = a1 (stored pointer); ebx = loop index i (0..0xFF); r14 = image base + 0xF842BBA (data ptr "%3d   ").
- xmm6 = 0 (16-byte zero source for entry init).

## Reversed source (complete)

See `src/client/features/render/native/d3d12/sub_e80bee0.cpp`; the C++ block there reproduces every instruction of [0xe80bee0, 0xe80bf85) with `// 0xA..0xB` citations and verbatim call quotes. Summary of phases:

- 0xe80bee0..0xe80bf19: prologue (push r15/r14/r12/rsi/rdi/rbx, sub rsp,0x38, save xmm6), set rdi=rdx, rsi=rcx, r12=this+0x10000, [this+0x12000]=0, ebx=0, xmm6=0, r14=imageBase+0xF842BBA, r15=rcx, nop.
- 0xe80bf20..0xe80bf69: loop, 256 times: read idx=[this+0x12000], off=idx<<5; store a1 at [base+off+0], 16 zero bytes at [base+off+8], dword 0xFFFFFFFF at [base+off+0x18]; inc [this+0x12000]; call sub_ebcf4e0(r15,7,r14,i); ++i; r15+=0x100; loop while i!=0x100.
- 0xe80bf6b..0xe80bf84: [this+0x12018]=1; restore xmm6/stack, pop r15/r14/r12/rsi/rdi/rbx, ret.

## Struct fields touched

| offset | size | dir | meaning | tag |
|---|---|---|---|---|
| this+0x10000 | 0x20*256 | W | table of 256 entries (ptr@+0, 16 zero@+8, dword -1@+0x18) | [V] 0xe80bef8..0xe80bf35 |
| this+0x12000 | 8 | W/R | entry write cursor / count (reset to 0, incremented per entry) | [V] 0xe80beff,0xe80bf20,0xe80bf3e |
| this+0x12018 | 1 | W | ready flag = 1 at end | [V] 0xe80bf6b |

## Callees

- 0xebcf4e0  call target sub_ebcf4e0 — boundary (docs/data/native_boundary.tsv: vendor), called 256x as sub_ebcf4e0(r15,7,r14,i) [V] 0xe80bf53.

## Notes

- r14 (`lea r14,[0xF842BBA]`) is a RIP-relative LEA to a format/data string; lifted as `imageBase()+0xF842BBA` (same idiom as sub_e809f40).
- No null guards, no error branches: the loop is unconditional and the function is straight-line apart from the fixed 256-count loop.