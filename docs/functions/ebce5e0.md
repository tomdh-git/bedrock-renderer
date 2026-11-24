# sub_ebce5e0 (0xebce5e0) - reversed function dossier

## Source
Minecraft Bedrock 1.26.62.01 (`C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe`), RVAs relative to image base.

## Function row (docs/data/native_functions.tsv)
```
0xebce5e0	0x8	0	7	root	D0		added 0xebce5e0
```
Size: 0x8 bytes, depth 0, milestone 7, region root, status D0. 0 callees in set, 0 callees outside set.

## Signature (x64 Microsoft ABI)
```
extern "C" std::int32_t sub_ebce5e0(const char* str, std::int32_t maxlen);
```
- rcx = str (const char*) — the NUL-terminated string to measure
- rdx = maxlen (std::int32_t) — upper bound on bytes examined (signed compare)
- eax = length (std::int32_t) — number of non-NUL bytes before a NUL terminator or maxlen

This is a bounded C-string length (strnlen-like). Cross-referenced as `sub_ebce5e0 = strlen-like (rdx=0x7FFFFFFF max, len in eax)` in existing analysis (docs/progress/oc_U-B9b.md). Callers pass a NUL-terminated string pointer in rcx and consume the length in eax.

## Register / argument map
| Register | Meaning | Type |
|---|---|---|
| rcx | str | const char* |
| rdx | maxlen | std::int32_t |
| rax/eax | length result (return) | std::int32_t |
| rax (scratch in body) | running pointer p = str + i | const char* |

## Disassembly (verbatim, [0xebce5e0, 0xebce601))
```
0xebce5e0  test rcx,rcx
0xebce5e3  jne short 0xEBCE5E8
0xebce5e5  xor eax,eax
0xebce5e7  ret
0xebce5e8  mov rax,rcx
0xebce5eb  test edx,edx
0xebce5ed  jle short 0xEBCE5FE
0xebce5ef  nop
0xebce5f0  cmp byte ptr [rax],0
0xebce5f3  je short 0xEBCE5FE
0xebce5f5  inc rax
0xebce5f8  dec edx
0xebce5fa  test edx,edx
0xebce5fc  jg short 0xEBCE5F0
0xebce5fe  sub eax,ecx
0xebce600  ret
```
The data file records the guard portion `[0xebce5e0, 0xebce5e8)` as size 0x8; the bounded-length body continues contiguously at `[0xebce5e8, 0xebce601]`. There are no `call` instructions and no callees. The `jne`/`je`/`jg`/`jle` are branches, not calls.

## Phases

**0xebce5e0..0xebce5e8 — null guard**
```
// 0xebce5e0  test rcx,rcx
// 0xebce5e3  jne short 0xEBCE5E8
if (str == nullptr) {
    // 0xebce5e5  xor eax,eax
    // 0xebce5e7  ret
    return 0;
}
// 0xebce5e3  jne short 0xEBCE5E8 -> body
```

**0xebce5e8..0xebce601 — bounded-length body**
```
// 0xebce5e8  mov rax,rcx          ; p = str
const char* p = str;
// 0xebce5eb  test edx,edx
// 0xebce5ed  jle short 0xEBCE5FE
if (maxlen <= 0) {
    // 0xebce5fe  sub eax,ecx   ; eax = p - str = 0
    // 0xebce600  ret
    return (std::int32_t)(p - str);
}
// 0xebce5ef  nop
for (;;) {                       // 0xebce5f0 loop head
    // 0xebce5f0  cmp byte ptr [rax],0
    // 0xebce5f3  je short 0xEBCE5FE
    if (*p == '\0') {
        // 0xebce5fe  sub eax,ecx   ; eax = p - str
        // 0xebce600  ret
        return (std::int32_t)(p - str);
    }
    // 0xebce5f5  inc rax
    ++p;
    // 0xebce5f8  dec edx
    --maxlen;
    // 0xebce5fa  test edx,edx
    // 0xebce5fc  jg short 0xEBCE5F0
    if (maxlen <= 0) {
        // 0xebce5fe  sub eax,ecx   ; eax = p - str
        // 0xebce600  ret
        return (std::int32_t)(p - str);
    }
}
```

All three exits reach `0xebce5fe  sub eax,ecx` (return p - str) then `0xebce600  ret`.

## Struct fields touched
None. The only memory read is one byte at `[rax + 0]` (the current string character, `cmp byte ptr [rax],0` at 0xebce5f0); base is `?` (no struct field). No writes to any object. No layout constants for struct fields are required; only ABI constants (see `SubEbce5e0Layout` in `sub_ebce5e0.h`).

## Callees
None (0 callees in set, 0 outside). No `call` instructions exist in the function; all control flow is direct branches.

## Ownership / threading
Pure function of its arguments (reads only the string bytes at [str, str+length], writes nothing). Thread-safe for the duration of the call provided the string buffer is not concurrently mutated. Footprint = nullptr (no declared writes).

## Reversed source (complete)

```cpp
// LIFT 0xebce5e0 size 0x8 1.26.62.01 sub_ebce5e0
// Source: src/client/features/render/native/helpers/sub_ebce5e0.cpp
//
// rcx = str (const char*), rdx = maxlen (std::int32_t); eax = length (std::int32_t).
//
//   0xebce5e0  test rcx,rcx
//   0xebce5e3  jne short 0xEBCE5E8
//   0xebce5e5  xor eax,eax
//   0xebce5e7  ret
//   0xebce5e8  mov rax,rcx
//   0xebce5eb  test edx,edx
//   0xebce5ed  jle short 0xEBCE5FE
//   0xebce5ef  nop
//   0xebce5f0  cmp byte ptr [rax],0
//   0xebce5f3  je short 0xEBCE5FE
//   0xebce5f5  inc rax
//   0xebce5f8  dec edx
//   0xebce5fa  test edx,edx
//   0xebce5fc  jg short 0xEBCE5F0
//   0xebce5fe  sub eax,ecx
//   0xebce600  ret
//
// Citation: 0xebce5e0..0xebce5e8 (null guard), 0xebce5e8..0xebce601 (bounded-length body)
static_assert(sizeof(std::int32_t) == 4, "sub_ebce5e0: maxlen and length are 32-bit (edx/eax)");
std::int32_t sub_ebce5e0_lifted(const char* str, std::int32_t maxlen) {
    // 0xebce5e0..0xebce5e8
    // 0xebce5e0  test rcx,rcx
    // 0xebce5e3  jne short 0xEBCE5E8
    if (str == nullptr) {
        // 0xebce5e5  xor eax,eax
        // 0xebce5e7  ret
        return 0;                                // 0xebce5e5 xor eax,eax ; 0xebce5e7 ret
    }
    // 0xebce5e3  jne short 0xEBCE5E8 -> body below
    // 0xebce5e8  mov rax,rcx
    const char* p = str;
    // 0xebce5e8..0xebce601
    // 0xebce5eb  test edx,edx
    // 0xebce5ed  jle short 0xEBCE5FE
    if (maxlen <= 0) {
        // 0xebce5fe  sub eax,ecx   (eax = p - str = 0)
        // 0xebce600  ret
        return (std::int32_t)(p - str);          // 0xebce5fe sub eax,ecx ; 0xebce600 ret
    }
    // 0xebce5ef  nop
    for (;;) {                                   // 0xebce5f0 loop head
        // 0xebce5f0  cmp byte ptr [rax],0
        // 0xebce5f3  je short 0xEBCE5FE
        if (*p == '\0') {
            // 0xebce5fe  sub eax,ecx   (eax = p - str)
            // 0xebce600  ret
            return (std::int32_t)(p - str);      // 0xebce5fe sub eax,ecx ; 0xebce600 ret
        }
        // 0xebce5f5  inc rax
        ++p;
        // 0xebce5f8  dec edx
        --maxlen;
        // 0xebce5fa  test edx,edx
        // 0xebce5fc  jg short 0xEBCE5F0
        if (maxlen <= 0) {
            // 0xebce5fe  sub eax,ecx   (eax = p - str)
            // 0xebce600  ret
            return (std::int32_t)(p - str);      // 0xebce5fe sub eax,ecx ; 0xebce600 ret
        }
    }
}
LIFT_FN(sub_ebce5e0, "sub_ebce5e0", 0xEBCE5E0, sub_ebce5e0_lifted, nullptr);
```

## Version anchors
- Game: Minecraft Bedrock 1.26.62.01
- Function: sub_ebce5e0 at 0xebce5e0, size 0x8 (guard) / logical extent to 0xebce601

## Verification
- `python tools/sigs/liftcheck.py 0xebce5e0` must print `LIFTCHECK OK 0xebce5e0`.
- No `call` instructions; all branches cited; no struct fields touched; registry entry via `LIFT_FN` in `sub_ebce5e0.cpp`.
