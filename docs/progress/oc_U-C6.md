# U-C6: Deferred Texture/Buffer Transactions flush @ 0x6632bf0

BGFX_MAP section 6dv, checklist C6. Unit flush (endFrame 0x66232b0) that runs two labelled `std::vector<Transaction*>` members of a `DeferredTransactions` arg (rcx) through a merge+run+delete pipeline.

## NEXT

Phase 1 — prologue + capture the two vector members into stack slots, zero originals (0x6632bf0..0x6632c49, 22 instr):
```
0x6632bf0  push rbp
0x6632bf1  push rsi
0x6632bf2  push rdi
0x6632bf3  sub rsp,0xA0
0x6632bfa  lea rbp,[rsp+0x80]
0x6632c02  mov qword ptr [rbp+0x18],0xFFFFFFFFFFFFFFFE
0x6632c0a  mov rax,[rcx+0x10]
0x6632c0e  movups xmm0,[rcx]
0x6632c11  movaps [rbp-0x50],xmm0
0x6632c15  mov [rbp-0x40],rax
0x6632c19  lea rax,[0xF54E8AF]
0x6632c20  mov [rbp-0x38],rax
0x6632c24  mov rax,[rcx+0x28]
0x6632c28  movups xmm0,[rcx+0x18]
0x6632c2c  xorps xmm1,xmm1
0x6632c2f  movups [rcx+0x20],xmm1
0x6632c33  movups [rcx],xmm1
0x6632c36  movups [rcx+0x10],xmm1
0x6632c3a  movaps [rbp-0x30],xmm0
0x6632c3e  mov [rbp-0x20],rax
0x6632c42  lea rax,[0xF54E847]
0x6632c49  mov [rbp-0x18],rax
```

Phase 2 — merge BUFFER vector (+0x18) via sub_12893d0, then run-loop (slot 1=[vtbl+8]) over its elements (0x6632c4d..0x6632c9c, 25 instr):
```
0x6632c4d  lea rcx,[rbp-0x30]
0x6632c51  lea rdx,[rbp-8]
0x6632c55  call 0x12893D0
0x6632c5a  nop
0x6632c5b  mov rsi,[rbp]
0x6632c5f  mov rdi,[rbp+8]
0x6632c63  cmp rsi,rdi
0x6632c66  jne short 0x6632C79
0x6632c68  jmp short 0x6632C9E
0x6632c6a  nop [rax+rax]
0x6632c70  add rsi,8
0x6632c74  cmp rsi,rdi
0x6632c77  je short 0x6632C91
0x6632c79  mov rcx,[rsi]
0x6632c7c  test rcx,rcx
0x6632c7f  je short 0x6632C70
0x6632c81  mov rax,[rcx]
0x6632c84  mov rax,[rax+8]
0x6632c88  call qword ptr [0xF99FFA0]
0x6632c8e  nop
0x6632c8f  jmp short 0x6632C70
0x6632c91  mov rsi,[rbp]
0x6632c95  mov rdi,[rbp+8]
0x6632c99  cmp rsi,rdi
0x6632c9c  jne short 0x6632CB9
```

Phase 3 — delete-loop (slot 0=[vtbl+0], edx=1) over BUFFER elements, then free the buffer block via sub_e935700 (0x6632c9e..0x6632d15, 32 instr):
```
0x6632c9e  test rsi,rsi
0x6632ca1  jne short 0x6632CE1
0x6632ca3  jmp short 0x6632D16
0x6632ca5  nop [rax+rax]
0x6632cb0  add rsi,8
0x6632cb4  cmp rsi,rdi
0x6632cb7  je short 0x6632CD4
0x6632cb9  mov rcx,[rsi]
0x6632cbc  test rcx,rcx
0x6632cbf  je short 0x6632CB0
0x6632cc1  mov rax,[rcx]
0x6632cc4  mov rax,[rax]
0x6632cc7  mov edx,1
0x6632ccc  call qword ptr [0xF99FFA0]
0x6632cd2  jmp short 0x6632CB0
0x6632cd4  mov rsi,[rbp]
0x6632cd8  mov [rbp+8],rsi
0x6632cdc  test rsi,rsi
0x6632cdf  je short 0x6632D16
0x6632ce1  mov rdx,[rbp+0x10]
0x6632ce5  sub rdx,rsi
0x6632ce8  cmp rdx,0x1000
0x6632cef  jb short 0x6632D0D
0x6632cf1  mov rax,[rsi-8]
0x6632cf5  add rsi,0xFFFFFFFFFFFFFFF8
0x6632cf9  sub rsi,rax
0x6632cfc  cmp rsi,0x20
0x6632d00  jae 0x6632F21
0x6632d06  add rdx,0x27
0x6632d0a  mov rsi,rax
0x6632d0d  mov rcx,rsi
0x6632d10  call 0xE935700
0x6632d15  nop
```

Phase 4 — merge TEXTURE vector (+0x00) via sub_12893d0, then run-loop (slot 1=[vtbl+8]) over its elements (0x6632d16..0x6632d6c, 27 instr):
```
0x6632d16  lea rcx,[rbp-0x50]
0x6632d1a  lea rdx,[rbp-8]
0x6632d1e  call 0x12893D0
0x6632d23  nop
0x6632d24  mov rsi,[rbp]
0x6632d28  mov rdi,[rbp+8]
0x6632d2c  cmp rsi,rdi
0x6632d2f  jne short 0x6632D49
0x6632d31  jmp short 0x6632D6E
0x6632d33  nop [rax+rax]
0x6632d40  add rsi,8
0x6632d44  cmp rsi,rdi
0x6632d47  je short 0x6632D61
0x6632d49  mov rcx,[rsi]
0x6632d4c  test rcx,rcx
0x6632d4f  je short 0x6632D40
0x6632d51  mov rax,[rcx]
0x6632d54  mov rax,[rax+8]
0x6632d58  call qword ptr [0xF99FFA0]
0x6632d5e  nop
0x6632d5f  jmp short 0x6632D40
0x6632d61  mov rsi,[rbp]
0x6632d65  mov rdi,[rbp+8]
0x6632d69  cmp rsi,rdi
0x6632d6c  jne short 0x6632D89
```

Phase 5 — delete-loop (slot 0=[vtbl+0], edx=1) over TEXTURE elements, then free the texture block via sub_e935700 (0x6632d6e..0x6632de0, 31 instr):
```
0x6632d6e  test rsi,rsi
0x6632d71  jne short 0x6632DB1
0x6632d73  jmp short 0x6632DE5
0x6632d75  nop [rax+rax]
0x6632d80  add rsi,8
0x6632d84  cmp rsi,rdi
0x6632d87  je short 0x6632DA4
0x6632d89  mov rcx,[rsi]
0x6632d8c  test rcx,rcx
0x6632d8f  je short 0x6632D80
0x6632d91  mov rax,[rcx]
0x6632d94  mov rax,[rax]
0x6632d97  mov edx,1
0x6632d9c  call qword ptr [0xF99FFA0]
0x6632da2  jmp short 0x6632D80
0x6632da4  mov rsi,[rbp]
0x6632da8  mov [rbp+8],rsi
0x6632dac  test rsi,rsi
0x6632daf  je short 0x6632DE5
0x6632db1  mov rdx,[rbp+0x10]
0x6632db5  sub rdx,rsi
0x6632db8  cmp rdx,0x1000
0x6632dbf  jb short 0x6632DDD
0x6632dc1  mov rax,[rsi-8]
0x6632dc5  add rsi,0xFFFFFFFFFFFFFFF8
0x6632dc9  sub rsi,rax
0x6632dcc  cmp rsi,0x20
0x6632dd0  jae 0x6632F21
0x6632dd6  add rdx,0x27
0x6632dda  mov rsi,rax
0x6632ddd  mov rcx,rsi
0x6632de0  call 0xE935700
```

Phase 6 — destroy merged Job* vector A ([rbp-0x30]..[rbp-0x28], stride 0x18): run+refcount-delete per entry, then free its block (0x6632de5..0x6632e74, 38 instr):
```
0x6632de5  mov rsi,[rbp-0x30]
0x6632de9  test rsi,rsi
0x6632dec  je 0x6632E79
0x6632df2  mov rdi,[rbp-0x28]
0x6632df6  cmp rsi,rdi
0x6632df9  jne short 0x6632E09
0x6632dfb  jmp short 0x6632E45
0x6632dfd  nop [rax]
0x6632e00  add rsi,0x18
0x6632e04  cmp rsi,rdi
0x6632e07  je short 0x6632E41
0x6632e09  mov rcx,[rsi+0x10]
0x6632e0d  test rcx,rcx
0x6632e10  je short 0x6632E23
0x6632e12  mov rax,[rcx]
0x6632e15  mov rax,[rax]
0x6632e18  mov edx,1
0x6632e1d  call qword ptr [0xF99FFA0]
0x6632e23  mov rcx,[rsi+8]
0x6632e27  test rcx,rcx
0x6632e2a  je short 0x6632E00
0x6632e2c  lock dec dword ptr [rcx+0xC]
0x6632e30  jne short 0x6632E00
0x6632e32  mov rax,[rcx]
0x6632e35  mov rax,[rax+8]
0x6632e39  call qword ptr [0xF99FFA0]
0x6632e3f  jmp short 0x6632E00
0x6632e41  mov rsi,[rbp-0x30]
0x6632e45  mov rdx,[rbp-0x20]
0x6632e49  sub rdx,rsi
0x6632e4c  cmp rdx,0x1000
0x6632e53  jb short 0x6632E71
0x6632e55  mov rax,[rsi-8]
0x6632e59  add rsi,0xFFFFFFFFFFFFFFF8
0x6632e5d  sub rsi,rax
0x6632e60  cmp rsi,0x20
0x6632e64  jae 0x6632F21
0x6632e6a  add rdx,0x27
0x6632e6e  mov rsi,rax
0x6632e71  mov rcx,rsi
0x6632e74  call 0xE935700
```

Phase 7 — destroy merged Job* vector B ([rbp-0x50]..[rbp-0x48], stride 0x18): run+refcount-delete per entry, then free its block (0x6632e79..0x6632f0a, 40 instr):
```
0x6632e79  mov rsi,[rbp-0x50]
0x6632e7d  test rsi,rsi
0x6632e80  je 0x6632F16
0x6632e86  mov rdi,[rbp-0x48]
0x6632e8a  cmp rsi,rdi
0x6632e8d  jne short 0x6632EA9
0x6632e8f  jmp short 0x6632EE5
0x6632e91  nop [rax+rax]
0x6632ea0  add rsi,0x18
0x6632ea4  cmp rsi,rdi
0x6632ea7  je short 0x6632EE1
0x6632ea9  mov rcx,[rsi+0x10]
0x6632ead  test rcx,rcx
0x6632eb0  je short 0x6632EC3
0x6632eb2  mov rax,[rcx]
0x6632eb5  mov rax,[rax]
0x6632eb8  mov edx,1
0x6632ebd  call qword ptr [0xF99FFA0]
0x6632ec3  mov rcx,[rsi+8]
0x6632ec7  test rcx,rcx
0x6632eca  je short 0x6632EA0
0x6632ecc  lock dec dword ptr [rcx+0xC]
0x6632ed0  jne short 0x6632EA0
0x6632ed2  mov rax,[rcx]
0x6632ed5  mov rax,[rax+8]
0x6632ed9  call qword ptr [0xF99FFA0]
0x6632edf  jmp short 0x6632EA0
0x6632ee1  mov rsi,[rbp-0x50]
0x6632ee5  mov rdx,[rbp-0x40]
0x6632ee9  sub rdx,rsi
0x6632eec  cmp rdx,0x1000
0x6632ef3  jb short 0x6632F0D
0x6632ef5  mov rax,[rsi-8]
0x6632ef9  add rsi,0xFFFFFFFFFFFFFFF8
0x6632efd  sub rsi,rax
0x6632f00  cmp rsi,0x20
0x6632f04  jae short 0x6632F21
0x6632f06  add rdx,0x27
0x6632f0a  mov rsi,rax
```

Phase 8 — epilogue / debugbreak guard (0x6632f0d..0x6632f3b, 16 instr):
```
0x6632f0d  mov rcx,rsi
0x6632f10  call 0xE935700
0x6632f15  nop
0x6632f16  add rsp,0xA0
0x6632f1d  pop rdi
0x6632f1e  pop rsi
0x6632f1f  pop rbp
0x6632f20  ret
0x6632f21  mov qword ptr [rsp+0x20],0
0x6632f2a  xor ecx,ecx
0x6632f2c  xor edx,edx
0x6632f2e  xor r8d,r8d
0x6632f31  xor r9d,r9d
0x6632f34  call qword ptr [0xF9A8C78]
0x6632f3a  int3
0x6632f3b  nop [rax+rax]
```

## Members — two labelled std::vector<Transaction*> on DeferredTransactions (rcx arg)

Each vector is `{begin, end, cap}`; each is followed by a trace-scope name pointer.

| Offset | begin | end | cap | label (string RVA) | Stored stack slot |
|--------|-------|-----|-----|--------------------|-------------------|
| `+0x00` | `+0x00` | `+0x08` | `+0x10` | "Deferred Texture Transactions" (0x6632c19, lea at 0x6632c19 -> [rbp-0x38]) | [rbp-0x50]/{begin}, [rbp-0x40]/{cap} |
| `+0x18` | `+0x18` | `+0x20` | `+0x28` | "Deferred Buffer Transactions" (0x6632c42, lea at 0x6632c42 -> [rbp-0x18]) | [rbp-0x30]/{begin}, [rbp-0x20]/{cap} |

Processing ORDER (confirmed by code flow + BGFX_MAP line 1489): BUFFER vector (+0x18) FIRST, then TEXTURE vector (+0x00) SECOND. Each vector is copied to a stack slot, then the original members are zeroed with 3x `movups` (rcx+0x0, rcx+0x10, rcx+0x20).

## Transaction object layout

| Vtable slot | Offset | Meaning | Observed at |
|-------------|--------|---------|-------------|
| slot 0 | `[vtbl+0]` | delete (deleting destructor, `edx`=1) | `mov rax,[rcx]; mov rax,[rax]; mov edx,1; call [0xF99FFA0]` |
| slot 1 | `[vtbl+8]` | run | `mov rax,[rcx]; mov rax,[rax+8]; call [0xF99FFA0]` |

Indirect call target `[data_f99ffa0]` = `sub_eea6040` (IAT-style thunk). Data-member offsets beyond the vtable pointer are NOT decoded from this function.

Transaction object SIZE: [UNVERIFIED: 0x6632bf0 question] — no `sizeof(Transaction)` or field offsets beyond vtable[0]/vtable[8] are observable in this function; object size must come from the class definition or another constructor/destructor.

## Callers / who pushes into the vectors

Callers of `0x6632bf0` (rdis `callers` + `ripscan.py 0x6632bf0`, exactly 2 call sites, both inside `endFrame` `sub_66232b0`):
- `0x66233ae`  `call 0x6632BF0`
- `0x662e3b4`  `call 0x6632BF0`

CORRECTION vs BGFX_MAP line 1241: BGFX_MAP claims call sites `0x66244e7`/`0x66264e6`, but at those RVAs the instruction is `lea rax,[string]` (trace-scope name loads), NOT calls. The real call sites are `0x66233ae` and `0x662e3b4`, verified via `rdis dis` at those RVAs.

Who PUSHES into the two vectors (the producers that record deferred texture/buffer uploads): NOT located in `0x6632bf0`. This function only consumes/flushes. Pushers are callers of the vector push_back elsewhere in the codebase; no xref to a push site was decoded here. [UNVERIFIED: 0x6632bf0 question] — identify pushers via xrefs to the vector members at DeferredTransactions+0x00/+0x18 (e.g., find writers to rcx+0x8/end or rcx+0x20/end).

## Aliasing logic

Searched "Deferred Transaction", "6632bf0", and "alias"/"aliasing" in BGFX_MAP + the preflight listing.

- Inside `0x6632bf0` itself: NO aliasing logic. The function moves each vector to the stack, zeroes the originals, runs `Transaction::run` (slot 1) then `Transaction::delete` (slot 0, edx=1), frees the blocks, and destroys the merged Job* vectors. No pointer rebinding, no `shared_ptr` aliasing constructor, no alias-tracking observed.
- BGFX_MAP 6dv line 1244 states: "no code in this path aliases memory; resource lifetime is by shared_ptr handles in pass dependency records + Bind declarations."

Conclusion: no aliasing logic exists in this flush path; lifetime is handled externally via shared_ptr handles.

## TOOL REQUESTS

1. `python tools/sigs/verify_oc.py docs/progress/oc_U-C6.md` — run to confirm all claimed `0xRVA  instr` lines match rdis (target: match=all, mismatch=0, no-such-instr=0).
2. Resolve Transaction object size and full data-member layout (offsets beyond vtable[0]/vtable[8]) — likely from the Transaction vtable/constructor or a sibling function; mark any guess `[UNVERIFIED: 0x6632bf0 question]`.
3. Identify who pushes into the two vectors: trace writers to `DeferredTransactions+0x08/end` (texture) and `+0x20/end` (buffer) / callers of vector `push_back`; mark `[UNVERIFIED: 0x6632bf0 question]` until located.
