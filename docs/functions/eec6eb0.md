# Function 0xeec6eb0 (sub_eec6eb0)

## Signature
```cpp
int32_t sub_eec6eb0(void* arg1, void* arg2, void* arg3);
```
- Calling convention: Microsoft x64 (rcx, rdx, r8, r9 for first 4 args; return in rax)
- Observed from callers: 3 args in rcx, rdx, r8; return tested via `test eax,eax`

## Disassembly (0xeec6eb0..0xeec6eb6)
```
0xeec6eb0  jmp qword ptr [0xF9A8A90]    ; 6 bytes: FF 25 8A 1D 0C 00
0xeec6eb6  int3                          ; padding
```

## Reversed source (complete)

### 0xeec6eb0..0xeec6eb6: Tail call through IAT slot
```c
// 0xeec6eb0..0xeec6eb6
// 0xeec6eb0  jmp qword ptr [0xF9A8A90]
return ((int32_t(*)(void*, void*, void*))*(uint64_t*)0xF9A8A90)(arg1, arg2, arg3);
```
The function is a 6-byte import thunk. It performs an indirect tail jump through the 8-byte pointer stored at RVA 0xF9A8A90 (in .rdata). The loader resolves this IAT entry to a CRT function (e.g., `memcmp`, `strncmp`, or similar 3-arg int-returning function). All 7300+ callers pass three arguments (rcx, rdx, r8) and check the integer return in eax.

## Struct fields touched
None.

## Callees
| RVA | Classification | Name | Note |
|-----|----------------|------|------|
| 0xF9A8A90 (data slot) | indirect / loader-resolved | (CRT function) | IAT entry; target resolved at load time. Called as function pointer with 3 args. [V] |

## Ownership / threading
Pure forwarder; no memory accesses of its own. Thread-safe as the target CRT function.

## Version anchors
- 1.26.62.01: RVA 0xeec6eb0, size 0x6, IAT slot 0xF9A8A90

## Verification
- `python tools/sigs/liftcheck.py 0xeec6eb0` must pass.
- Every instruction in [0xeec6eb0, 0xeec6eb6) cited.
- Call quoted verbatim: `0xeec6eb0  jmp qword ptr [0xF9A8A90]`
- No `[?]`/`[I]`/`TODO`/`UNVERIFIED` tags.
- Layout assertions: none (no struct access).
- Registry entry `LIFT_FN(0xeec6eb0, ...)` present in .cpp.

## OPEN questions
- Exact identity of the CRT function at IAT slot 0xF9A8A90 (requires live capture or loader analysis). Not needed for lifting: the thunk forwards generically.