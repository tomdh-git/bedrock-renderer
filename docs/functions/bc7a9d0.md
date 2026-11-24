# Dossier: sub_bc7a9d0 (0xbc7a9d0, size 0x5e3, 1.26.62.01)

## Source
- `src/client/features/render/native/bgfx/sub_bc7a9d0.cpp` (first line: `// LIFT 0xbc7a9d0 size 0x5e3 1.26.62.01 sub_bc7a9d0`)
- `src/client/features/render/native/bgfx/sub_bc7a9d0.h` (layout constants + static_asserts, forward declarations, footprint declaration)
- Registry entry: `LIFT_FN(bc7a9d0, "sub_bc7a9d0", 0xBC7A9D0, sub_bc7a9d0, sub_bc7a9d0_footprint)` in the .cpp.

## Signature (x64 Microsoft ABI)
```
// LIFT 0xbc7a9d0 size 0x5e3 1.26.62.01 sub_bc7a9d0
extern "C" void sub_bc7a9d0(std::uint32_t* keys, std::uint32_t* workKeys,
                            std::uint32_t* parIn, std::uint32_t* parOut,
                            std::uint32_t count);
```
- rcx = keys, rdx = workKeys, r8 = parIn, r9 = parOut (ABI register args).
- 5th argument `count` is stack-passed: the caller (0xbc6aeb0) stores it at its [rsp+0x20]; this function reads it as [rsp+0x2090] after the 0x2028-byte stack probe [V: `0xbc7a9f5  mov ebp,[rsp+0x2090]`].
- Return: void (no return value observed; epilogue `ret` at 0xbc7afa1).

## Register / argument map
| ABI | local role | source |
|---|---|---|
| rcx (r14) | keys input/output buffer | `0xbc7a9f2  mov r14,rcx` |
| rdx (rbx) | workKeys buffer | `0xbc7a9ef  mov rbx,rdx` |
| r8 (rdi) | parIn input array | `0xbc7a9ec  mov rdi,r8` |
| r9 (rsi) | parOut output array | `0xbc7a9e9  mov rsi,r9` |
| stack arg | count (u32) | `0xbc7a9f5  mov ebp,[rsp+0x2090]` |

## Memory model
- One stack frame: probe `mov eax,0x2028; call sub_e9e7970; sub rsp,rax` [V: `0xbc7a9dc..0xbc7a9e6`], then home/save 0x20 bytes, `u32 counters[0x800]` at [rsp+0x20], `u64 cookie` at [rsp+0x2020] = `[0x1230A0C0] ^ rsp` [V: `0xbc7a9fc  mov rax,[0x1230A0C0]`; `0xbc7aa03  xor rax,rsp`; `0xbc7aa06  mov [rsp+0x2020],rax`].
- Cookie verified at epilogue: `[0x1230A0C0] == ([rsp+0x2020] ^ rsp)`; mismatch -> `call sub_e951550` (noreturn) at `0xbc7afad` then int3 padding [V: `0xbc7af77..0xbc7afb2`].
- Only global read: data_1230a0c0 (cookie secret), twice [V: `0xbc7a9fc`, `0xbc7af82`]. No heap, no other globals, no fields of game objects. Stack-only locals; pointers to caller buffers are not stored anywhere persistent.

## Phases
Each phase covers every instruction of its range (ranges are inclusive and partition 0xbc7a9d0..0xbc7afb2; the int3 padding at 0xbc7afb2 is inside the cookie-fail range). Every `call` is quoted verbatim beside its site.

### 0xbc7a9d0..0xbc7aa1b — prologue, probe, cookie, counter clear
Pushes callee-saved registers, `mov eax,0x2028; call 0xE9E7970; sub rsp,rax`, copies the four pointer args, loads count from [rsp+0x2090], stores the cookie, clears counters with `call 0xEBCE430` (fill 0).
C-like:
```
// 0xbc7a9dc  mov eax,0x2028
// 0xbc7a9e1  call 0xE9E7970        ; -> sub_e9e7970
// 0xbc7a9e6  sub rsp,rax
(void)sub_e9e7970(kStackSize);     // 0xbc7a9e1 call 0xE9E7970
std::memset(counters, 0, kCounterBytes);   // 0xbc7aa1b call 0xEBCE430 (memset counters,0,0x2000)
```

### 0xbc7aa20..0xbc7aa22 — empty-input early exit
`test ebp,ebp; je short 0xBC7AF77` — count == 0 skips straight to the epilogue (cookie check + ret) [V].

### 0xbc7aa28..0xbc7aa9d — pass 1 histogram + already-sorted test
Digit = `key & 0x7FF`. Pairwise loop over keys: bin each of the pair into counters, update the sortedness flag `cl` = AND over `(keys[2k+1] <= keys[2k+2])` (values compared, not digits). Odd `n` handles the last element, but NOTE the listing OVERWRITES the accumulated flag with just `(keys[n-2] <= keys[n-1])` at 0xbc7aab9..0xbc7aabe [V]. If sorted -> epilogue (data already in keys, untouched) [V: `0xbc7aa9d  jmp 0xBC7AF77`].
C-like: `pass1Sorted` computed pairwise; odd tail sets `pass1Sorted = (prev <= keys[limit])` discarding the accumulated flag; `if (pass1Sorted) goto L_epilogue;` [V: `0xbc7aa99  test cl,cl`; `0xbc7aa9d  jmp 0xBC7AF77`].

### 0xbc7aac9..0xbc7ab02 — pass 1 prefix scan
Group-of-4 exclusive prefix scan over counters[0..0x7FF] (rax walks 3,7,...,0x7FF, carry passed between groups) [V].

### 0xbc7ab04..0xbc7aba8 — pass 1 distribute
Pairwise scatter of keys (from r14) into workKeys (rbx) and parIn (rdi) into parOut (rsi), using counters as positions (pos-then-increment), plus odd tail [V].

### 0xbc7abb8..0xbc7ac25 — pass 2: clear + histogram + sorted test
`call 0xEBCE430` re-clears counters [V]. Digit = `(key >> 9) & 0x1FFC` (the listing addresses bins by this byte offset; equivalent u32 bin is `(key >> 9) & 0x7FF`). Same pairwise histogram + sortedness-over-values structure as pass 1, including the odd-tail flag overwrite [V: `0xbc7ac45..0xbc7ac4a`]. If sorted -> jump to the tail copy at 0xbc7aebf [V: `0xbc7ac25  jmp 0xBC7AEBF`].

### 0xbc7ac54..0xbc7ac92 — pass 2 prefix scan
Same group-of-4 exclusive scan [V].

### 0xbc7ac94..0xbc7ad40 — pass 2 distribute
Scatter from workKeys into keys and from parOut into parIn [V], plus odd tail.

### 0xbc7ad40..0xbc7ad50 — pass 3: counter clear
`call 0xEBCE430` re-clears counters [V].

### 0xbc7ad55..0xbc7adb7 — pass 3 histogram + sorted test
Digit = `key >> 22` (bins 0..0x3FF, u32-indexed directly). Same sortedness structure; if sorted -> epilogue [V: `0xbc7adb7  jmp 0xBC7AF77`] (keys in `keys` are already fully sorted in value).

### 0xbc7addf..0xbc7ae22 — pass 3 prefix scan
Same scan, rax walks 0,4,...,0x7FC [V].

### 0xbc7ae24..0xbc7ae99 — pass 3 distribute
Scatter from keys into workKeys and parIn into parOut [V], plus odd tail.

### 0xbc7aebf..0xbc7aed0 — tail: copy sorted keys back
`lea r15,[r12*4]` (byte count = count*4); `call 0xEBCE390` -> `sub_ebce390(keys, workKeys, count*4)` = memcpy(keys, workKeys, count*4) [V]. Skipped only on the pass-1 sorted exit (data was already in keys).

### 0xbc7aed5..0xbc7af75 — tail: parallel-array copy parOut -> parIn
`al = (count < 8)`; `cl = ((uint64)(parIn - parOut) < 0x20)`.
- If `count >= 8 && (uint64)(parIn - parOut) >= 0x20` (buffers far): `movups` 32-byte chunks for (count & ~7) u32, then remainder (single-u32 loop for count & 3, then a wrapped-compare decides between epilogue and a 4-u32 loop) [V: `0xbc7aed5..0xbc7af75`].
- Else: single-u32 loop for count & 3, wrapped compare `-count >u 0xFFFFFFFC` (i.e. count < 4) -> epilogue, else 4-u32 loop [V: `0xbc7aeec..0xbc7af75`].

### 0xbc7af77..0xbc7afa1 — cookie check + epilogue
`mov rax,[rsp+0x2020]; xor rax,rsp; mov rcx,[0x1230A0C0]; cmp rcx,rax; jne short 0xBC7AFA2`; else `add rsp,0x2028; pop rbx,rbp,rdi,rsi,r12,r13,r14,r15; ret` [V].

### 0xbc7afa2..0xbc7afb2 — cookie-failure path
`mov rcx,[rsp+0x2020]; xor rcx,rsp; call 0xE951550` (noreturn); `int3` padding [V].

## Struct fields touched
None: the function touches no game-object fields. Stack frame overlay `Bc7a9d0Frame` (counters at frame base +0x0000, cookie at +0x2000, sizeof 0x2008) lives in `sub_bc7a9d0.h` with static_asserts; the 0x20 bytes below the frame base are home space.

## Callees
| RVA | target | class | call site | notes |
|---|---|---|---|---|
| 0xE9E7970 | sub_e9e7970 | boundary (crt, __chkstk-style probe) | `0xbc7a9e1  call 0xE9E7970` | eax = 0x2028, then `sub rsp,rax` [V] |
| 0xEBCE430 | sub_ebce430 | lift forwarder (5 bytes: `movzx edx,dl; jmp 0xEEC6ED0`; target 0xEEC6ED0 = crt IAT memset thunk) | `0xbc7aa1b`, `0xbc7abb8`, `0xbc7ad50` `call 0xEBCE430` | all three calls pass fill 0; lifted as `std::memset(counters, 0, 0x2000)` [V; hard rule 69 forwarder; REPLACED by the std::memset intrinsic, an allowed library intrinsic per spec section 5 — not called directly] |
| 0xEBCE390 | sub_ebce390 | lift (0x5-byte `jmp 0xEEC6EC0`, unit X7.ebce390) | `0xbc7aed0  call 0xEBCE390` | memcpy(keys, workKeys, count*4) [V] |
| 0xE951550 | sub_e951550 | boundary (crt, stack-cookie failure, noreturn) | `0xbc7afad  call 0xE951550` | only on cookie mismatch [V] |

Every call target is either a boundary function (native_boundary.tsv crt rows) or a lift-set function (native_functions.tsv: 0xebce390 at line 1621); sub_ebce430 is a resolved forwarder whose calls are replaced by the memset intrinsic it tail-calls with fill 0, so every call target is resolved.

## OPEN questions
None. All instruction addresses in 0xbc7a9d0..0xbc7afb3 are accounted for; every call target resolved; all constants and offsets taken verbatim from the listing [V].

## Reversed source (complete)
See `src/client/features/render/native/bgfx/sub_bc7a9d0.cpp`: every instruction of 0xbc7a9d0..0xbc7afb2 is quoted verbatim beside its block (e.g. `// 0xbc7a9e1  call 0xE9E7970`) and carries a `// 0xA..0xB` range cite; the C++ statements below are the instruction-for-instruction translation.

### Prologue / probe / cookie / clear (0xbc7a9d0..0xbc7aa1b)
```
// 0xbc7a9dc  mov eax,0x2028
// 0xbc7a9e1  call 0xE9E7970
// 0xbc7a9e6  sub rsp,rax
// 0xbc7a9f5  mov ebp,[rsp+0x2090]
// 0xbc7a9fc  mov rax,[0x1230A0C0]
// 0xbc7aa03  xor rax,rsp
// 0xbc7aa06  mov [rsp+0x2020],rax
// 0xbc7aa0e  lea rcx,[rsp+0x20]
// 0xbc7aa13  mov r8d,0x2000
// 0xbc7aa19  xor edx,edx
// 0xbc7aa1b  call 0xEBCE430
(void)sub_e9e7970(kStackSize);             // 0xbc7a9e1 call 0xE9E7970; 0xbc7a9e6 sub rsp,rax
std::memset(counters, 0, kCounterBytes);   // 0xbc7aa1b call 0xEBCE430
if (count == 0u) goto L_epilogue;          // 0xbc7aa20 test ebp,ebp / 0xbc7aa22 je 0xBC7AF77
```

### Pass 1 (0xbc7aa28..0xbc7aba8)
```
// 0xbc7aa28  mov eax,[r14]
// 0xbc7aa50  mov r9d,[r14+rdx*4]        (pair loop: cur = keys[idx])
// 0xbc7aa57  and r10d,0x7FF             (bin = cur & 0x7FF)
// 0xbc7aa5e  inc dword ptr [rsp+r10*4+0x20]
// 0xbc7aa63  cmp eax,r9d                (prev <= cur)
// ... (all instructions 0xbc7aa28..0xbc7aba8 quoted in the .cpp)
bool pass1Sorted = true;
{
    std::uint32_t prev = keys[0];
    std::uint32_t limit = count & ~1u;
    std::uint32_t idx = 0;
    for (; idx < limit; idx += 2u) {
        const std::uint32_t cur = keys[idx];
        ++counters[cur & kDigitMaskA];
        const bool lePrev = (prev <= cur);
        const std::uint32_t nxt = keys[idx + 1u];
        ++counters[nxt & kDigitMaskA];
        pass1Sorted = (cur <= nxt) && lePrev && pass1Sorted;
        prev = nxt;
    }
    if (count & 1u) {
        ++counters[keys[limit] & kDigitMaskA];
        pass1Sorted = (prev <= keys[limit]);   // flag overwrite, matches 0xbc7aab9..0xbc7aac3
    }
}
if (pass1Sorted) goto L_epilogue;
// 0xbc7aac9..0xbc7ab02: exclusive prefix scan (groups of 4, carry between groups)
// 0xbc7ab04..0xbc7aba8: pairwise distribute keys->workKeys, parIn->parOut, odd tail
{ ... prefix scan ... distribute ... }  // full C++ in sub_bc7a9d0.cpp, ranges cited per statement
```

### Pass 2 (0xbc7abb8..0xbc7ad40)
```
// 0xbc7abb8  call 0xEBCE430       (clear counters)
// 0xbc7abbd  mov eax,[rbx]         (prev = workKeys[0])
// 0xbc7abd7  shr r9d,9
// 0xbc7abdb  and r9d,0x1FFC        (byte-offset bin; u32 bin == (key>>9)&0x7FF)
// ... all instructions 0xbc7abb8..0xbc7ad40 quoted in the .cpp
std::memset(counters, 0, kCounterBytes);   // 0xbc7abb8 call 0xEBCE430
// same histogram/scan/distribute structure as pass 1, digit ((cur >> 9) & kDigitMaskB) >> 2,
// output keys/parIn; if pass2Sorted goto L_tail (tail copies workKeys back to keys)
```

### Pass 3 (0xbc7ad40..0xbc7ae99)
```
// 0xbc7ad50  call 0xEBCE430       (clear counters)
// 0xbc7ad55  mov eax,[r14]         (prev = keys[0])
// 0xbc7ad77  shr r9d,0x16          (bin = key >> 22)
// ... all instructions 0xbc7ad40..0xbc7ae99 quoted in the .cpp
std::memset(counters, 0, kCounterBytes);   // 0xbc7ad50 call 0xEBCE430
// histogram digit cur >> 22; if pass3Sorted goto L_epilogue (keys in place);
// scan + distribute keys->workKeys, parIn->parOut
```

### Tail copy (0xbc7aebf..0xbc7af75)
```
// 0xbc7aed0  call 0xEBCE390        memcpy(keys, workKeys, count*4)
// 0xbc7aed5  cmp ebp,8
// 0xbc7aed8  setb al               (count < 8)
// 0xbc7aede  sub rcx,rsi           ((uint64)(parIn - parOut))
// 0xbc7aee1  cmp rcx,0x20
sub_ebce390(keys, workKeys, (std::uint64)count * 4);   // 0xbc7aed0 call 0xEBCE390
// movups 32-byte bulk path when count >= 8 && buffers far, else u32 loops;
// wrapped compares (lim8 - count >u 0xFFFFFFFC / -count >u 0xFFFFFFFC) select epilogue vs 4-u32 loop
```

### Epilogue (0xbc7af77..0xbc7afb2)
```
// 0xbc7af77  mov rax,[rsp+0x2020]
// 0xbc7af7f  xor rax,rsp
// 0xbc7af82  mov rcx,[0x1230A0C0]
// 0xbc7af89  cmp rcx,rax
// 0xbc7af8c  jne short 0xBC7AFA2
// 0xbc7af8e  add rsp,0x2028
// ... pops ... ret
if (*reinterpret_cast<std::uintptr_t*>(kGblCookie) !=
    (cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot))) {
    sub_e951550(cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot));  // 0xbc7afad call 0xE951550
    __assume(false);   // noreturn; 0xbc7afb2 int3 padding only
}
```

## Version anchors
- Game: Minecraft.Windows.exe 1.26.62.01; RVAs relative to image base; function extent per .pdata: 0xbc7a9d0..0xbc7afb3 (size 0x5e3) [V: rdis `sum`].
- Caller: 0xbc6aeb0 (`0xbc6aefd  call 0xBC7A9D0`) [V].

## Verification
- Static: `python tools/sigs/liftcheck.py 0xbc7a9d0` -> LIFTCHECK OK (target).
- V2 footprint: keys, workKeys, parIn, parOut, each `count * 4` bytes (declared in `sub_bc7a9d0_footprint`).
