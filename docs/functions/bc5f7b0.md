# Dossier: D3D12 submit RTX override (sub 0xbc5f7b0)

## Mechanical facts

- size 0x11e bytes, span [0xbc5f7b0, 0xbc5f8ce), 82 instructions, 6 direct call sites, 1 xref in [V: rdis dis listing saved at %TEMP%/opencode/bc5f7b0_listing.txt]
- name "D3D12 submit RTX override", region bgfx, depth 4, milestone 1, status L1 [V: src/client/features/render/native/bgfx/sub_bc5f7b0.cpp (+.h); liftcheck printed LIFTCHECK OK 0xbc5f7b0]
- root/callee in the lift set: 0xbc76380 (X1.bc76380, lifted; native symbol Bc76380_lifted) [V: same data file; sub_bc76380.cpp]
- callees outside the lift set: 0xEBCE5E0, 0xEBCE570, 0xE951550 — all reached through native::Boundary<R,A...> wrappers in sub_bc5f7b0.cpp (symbols sub_ebce5e0/sub_ebce570/sub_e951550; sig anchors added at the milestone gate, units do not edit Sigs.json); 0xE951550 is crt row line 467 in docs/data/native_boundary.tsv (X0b5) [V: checked both files]
- x64 Microsoft ABI: rcx = a0 (uintptr_t*, [rcx+0x0] read and written), edx = arg (uint32_t carried in ebx), return eax = ebx (uint32_t) [V]

## Argument use

- rcx/a0: +0x0 read (0xbc5f7cf mov r15,[rcx]; 0xbc5f7db cmp byte ptr [r15],0x5B) and written (0xbc5f898 mov [rsi],r15 with rsi = rcx) [V]
- edx/arg: moved to ebx at 0xbc5f7be; returned in eax at 0xbc5f8af unless the accepted path replaces it [V]

## Direct callees (verbatim quotes from the disassembly)

| caller address | quote | target | class |
| 0xbc5f80b | `0xbc5f80b  call 0xEBCE5E0` | 0xEBCE5E0 | boundary wrapper native::Boundary<uint32_t,const char*,uint32_t>(symbol "sub_ebce5e0"); callee class verified as bounded strlen [V: rdis dis 0xebce5e0..0xebce600] |
| 0xbc5f832 | `0xbc5f832  call 0xEBCE5E0` | 0xEBCE5E0 | same wrapper, second call site [V] |
| 0xbc5f854 | `0xbc5f854  call 0xEBCE570` | 0xEBCE570 | boundary wrapper native::Boundary<int32_t,const Pair*,const Pair*,uint32_t>(symbol "sub_ebce570"); callee class verified as bounded {ptr,len} compare [V: rdis dis 0xebce570..0xebce5d5] |
| 0xbc5f86e | `0xbc5f86e  call 0xBC76380` | 0xBC76380 | lifted, native symbol Bc76380_lifted (CALLEES list) |
| 0xbc5f880 | `0xbc5f880  call 0xBC76380` | 0xBC76380 | lifted, native symbol Bc76380_lifted (CALLEES list) |
| 0xbc5f8c8 | `0xbc5f8c8  call 0xE951550` | 0xE951550 | boundary wrapper native::Boundary<void>(symbol "sub_e951550"); crt row line 467 in docs/data/native_boundary.tsv, noreturn cookie failure [V: X0b5] |

## Structs touched

- argument *a0 at +0x0: R (0xbc5f7cf mov r15,[rcx]; 0xbc5f7db cmp byte ptr [r15],0x5B) and W (0xbc5f898 mov [rsi],r15, rsi = rcx) [V]
- raw stack frame (sub rsp,0x50): pairB at [rsp+0x20]/[rsp+0x28], pairA at [rsp+0x30]/[rsp+0x38], savedPtr at [rsp+0x40], cookie at [rsp+0x48] [V] (no struct type, raw [reg+off] slots)
- global [0x1230A0C0]: R at 0xbc5f7c0 and 0xbc5f8a3 (stack cookie) [V]
- immediate pointer constants (lea immediates, not memory reads): 0xF847A07 (0xbc5f7e8), 0xF59FECD (0xbc5f7fc) [V]

## Reversed source (complete)

Body span [0xbc5f7b0, 0xbc5f8ce). Phases follow the branch structure of the original; every instruction is inside a cited range (the same ranges are cited beside each block in src/client/features/render/native/bgfx/sub_bc5f7b0.cpp) and every call is quoted verbatim below; quotes match the exe exactly (verify_oc on the .cpp: claimed=43 match=43 mismatch=0; liftcheck printed LIFTCHECK OK 0xbc5f7b0, see docs/progress/oc_U-EX1.bc5f7b0.md).

phase 1: prologue, argument stash, cookie, range 0xbc5f7b0..0xbc5f7ca
0xbc5f7b0  push r15
0xbc5f7b2  push r14
0xbc5f7b4  push r12
0xbc5f7b6  push rsi
0xbc5f7b7  push rdi
0xbc5f7b8  push rbp
0xbc5f7b9  push rbx
0xbc5f7ba  sub rsp,0x50
0xbc5f7be  mov ebx,edx
0xbc5f7c0  mov rax,[0x1230A0C0]
0xbc5f7c7  xor rax,rsp
0xbc5f7ca  mov [rsp+0x48],rax

phase 2: '[' test and early exit, range 0xbc5f7cf..0xbc5f7df
0xbc5f7cf  mov r15,[rcx]
0xbc5f7d2  lea rdi,[r15+1]
0xbc5f7d6  mov [rsp+0x40],rdi
0xbc5f7db  cmp byte ptr [r15],0x5B
0xbc5f7df  jne 0xBC5F89B

phase 3: pairA init and first length call, range 0xbc5f7e5..0xbc5f818
0xbc5f7e5  mov rsi,rcx
0xbc5f7e8  lea r12,[0xF847A07]
0xbc5f7ef  mov [rsp+0x30],r12
0xbc5f7f4  mov dword ptr [rsp+0x38],0
0xbc5f7fc  lea r14,[0xF59FECD]
0xbc5f803  mov rcx,r14
0xbc5f806  mov edx,0x7FFFFFFF
0xbc5f80b  call 0xEBCE5E0
0xbc5f810  test eax,eax
0xbc5f812  je short 0xBC5F81D
0xbc5f814  mov [rsp+0x38],eax
0xbc5f818  mov [rsp+0x30],r14

phase 4: pairB reset and second length call, range 0xbc5f81d..0xbc5f83f
0xbc5f81d  mov [rsp+0x20],r12
0xbc5f822  mov dword ptr [rsp+0x28],0
0xbc5f82a  mov rcx,rdi
0xbc5f82d  mov edx,0x7FFFFFFF
0xbc5f832  call 0xEBCE5E0
0xbc5f837  test eax,eax
0xbc5f839  je short 0xBC5F844
0xbc5f83b  mov [rsp+0x28],eax
0xbc5f83f  mov [rsp+0x20],rdi

phase 5: compare and branch, range 0xbc5f844..0xbc5f85b
0xbc5f844  lea rcx,[rsp+0x20]
0xbc5f849  lea rdx,[rsp+0x30]
0xbc5f84e  mov r8d,2
0xbc5f854  call 0xEBCE570
0xbc5f859  test eax,eax
0xbc5f85b  je short 0xBC5F894

phase 6: accepted path (two lifted callee calls + pack), range 0xbc5f85d..0xbc5f898
0xbc5f85d  mov r8d,ebx
0xbc5f860  and r8b,0xF
0xbc5f864  lea rdi,[rsp+0x40]
0xbc5f869  mov rcx,rdi
0xbc5f86c  mov dl,0x3B
0xbc5f86e  call 0xBC76380
0xbc5f873  mov ebp,eax
0xbc5f875  shr bl,4
0xbc5f878  mov rcx,rdi
0xbc5f87b  mov dl,0x6D
0xbc5f87d  mov r8d,ebx
0xbc5f880  call 0xBC76380
0xbc5f885  mov ebx,eax
0xbc5f887  shl bl,4
0xbc5f88a  or bl,bpl
0xbc5f88d  mov r15,[rsp+0x40]
0xbc5f892  jmp short 0xBC5F898
0xbc5f898  mov [rsi],r15

phase 7: *a0 += 3 path, range 0xbc5f894..0xbc5f898
0xbc5f894  add r15,3

phase 8: cookie check, epilogue, fail path, range 0xbc5f89b..0xbc5f8cd
0xbc5f89b  mov rax,[rsp+0x48]
0xbc5f8a0  xor rax,rsp
0xbc5f8a3  mov rcx,[0x1230A0C0]
0xbc5f8aa  cmp rcx,rax
0xbc5f8ad  jne short 0xBC5F8C0
0xbc5f8af  mov eax,ebx
0xbc5f8b1  add rsp,0x50
0xbc5f8b5  pop rbx
0xbc5f8b6  pop rbp
0xbc5f8b7  pop rdi
0xbc5f8b8  pop rsi
0xbc5f8b9  pop r12
0xbc5f8bb  pop r14
0xbc5f8bd  pop r15
0xbc5f8bf  ret
0xbc5f8c0  mov rcx,[rsp+0x48]
0xbc5f8c5  xor rcx,rsp
0xbc5f8c8  call 0xE951550
0xbc5f8cd  int3

C++ (lifted body, src/client/features/render/native/bgfx/sub_bc5f7b0.cpp; first line of the file is the `// LIFT 0xbc5f7b0 size 0x11e ...` marker):

```cpp
std::uint32_t sub_bc5f7b0(std::uintptr_t* a0, std::uint32_t arg) {
    // 0xbc5f7b0..0xbc5f7ba
    // 0xbc5f7b0  push r15
    // 0xbc5f7b2  push r14
    // 0xbc5f7b4  push r12
    // 0xbc5f7b6  push rsi
    // 0xbc5f7b7  push rdi
    // 0xbc5f7b8  push rbp
    // 0xbc5f7b9  push rbx
    // 0xbc5f7ba  sub rsp,0x50
    // 0xbc5f7be  mov ebx,edx
    std::uint32_t ebx = arg;                               // 0xbc5f7be

    // 0xbc5f7c0..0xbc5f7ca
    // 0xbc5f7c0  mov rax,[0x1230A0C0]
    // 0xbc5f7c7  xor rax,rsp
    // 0xbc5f7ca  mov [rsp+0x48],rax
    std::uintptr_t cookieSlot = 0;                         // address stands in for the rsp-relative slot
    const std::uintptr_t cookieStored =
        *reinterpret_cast<std::uintptr_t*>(0x1230A0C0) ^ reinterpret_cast<std::uintptr_t>(&cookieSlot);  // 0xbc5f7c0..0xbc5f7ca

    // 0xbc5f7cf..0xbc5f7df
    // 0xbc5f7cf  mov r15,[rcx]
    // 0xbc5f7d2  lea rdi,[r15+1]
    // 0xbc5f7d6  mov [rsp+0x40],rdi
    // 0xbc5f7db  cmp byte ptr [r15],0x5B
    // 0xbc5f7df  jne 0xBC5F89B
    const std::uintptr_t r15 = *a0;                        // 0xbc5f7cf
    std::uintptr_t savedPtr = r15 + 1;                     // 0xbc5f7d2..0xbc5f7d6
    std::uintptr_t* const slot = &savedPtr;                // &[rsp+0x40]

    if (*reinterpret_cast<const unsigned char*>(r15) == 0x5B) {  // 0xbc5f7db / 0xbc5f7df
        // 0xbc5f7e5  mov rsi,rcx        rsi = a0 (result sink)
        // 0xbc5f7e8  lea r12,[0xF847A07]
        // 0xbc5f7ef  mov [rsp+0x30],r12
        // 0xbc5f7f4  mov dword ptr [rsp+0x38],0
        Pair pairA{0xF847A07, 0};                          // 0xbc5f7e5..0xbc5f7f4

        // `0xbc5f7fc  lea r14,[0xF59FECD]`
        // `0xbc5f803  mov rcx,r14`
        // `0xbc5f806  mov edx,0x7FFFFFFF`
        // `0xbc5f80b  call 0xEBCE5E0`
        const std::uint32_t lenA =
            sub_ebce5e0(reinterpret_cast<const char*>(0xF59FECD), 0x7FFFFFFFu);
        // `0xbc5f810  test eax,eax`
        // `0xbc5f812  je short 0xBC5F81D`
        if (lenA != 0) {                                   // 0xbc5f810..0xbc5f812
            // `0xbc5f814  mov [rsp+0x38],eax`
            // `0xbc5f818  mov [rsp+0x30],r14`
            pairA.ptr = 0xF59FECD;                         // 0xbc5f818
            pairA.len = lenA;                              // 0xbc5f814
        }

        // 0xbc5f81d  mov [rsp+0x20],r12
        // 0xbc5f822  mov dword ptr [rsp+0x28],0
        Pair pairB{0xF847A07, 0};                          // 0xbc5f81d..0xbc5f822

        // `0xbc5f82a  mov rcx,rdi`
        // `0xbc5f82d  mov edx,0x7FFFFFFF`
        // `0xbc5f832  call 0xEBCE5E0`
        const std::uint32_t lenB =
            sub_ebce5e0(reinterpret_cast<const char*>(savedPtr), 0x7FFFFFFFu);
        // `0xbc5f837  test eax,eax`
        // `0xbc5f839  je short 0xBC5F844`
        if (lenB != 0) {                                   // 0xbc5f837..0xbc5f839
            // `0xbc5f83b  mov [rsp+0x28],eax`
            // `0xbc5f83f  mov [rsp+0x20],rdi`
            pairB.ptr = savedPtr;                          // 0xbc5f83f
            pairB.len = lenB;                              // 0xbc5f83b
        }

        // `0xbc5f844  lea rcx,[rsp+0x20]`
        // `0xbc5f849  lea rdx,[rsp+0x30]`
        // `0xbc5f84e  mov r8d,2`
        // `0xbc5f854  call 0xEBCE570`
        const std::int32_t cmp =
            sub_ebce570(&pairB, &pairA, 2u);
        // `0xbc5f859  test eax,eax`
        // `0xbc5f85b  je short 0xBC5F894`
        if (cmp == 0) {                                    // 0xbc5f859..0xbc5f85b
            // 0xbc5f894  add r15,3
            // 0xbc5f898  mov [rsi],r15
            *a0 = r15 + 3;                                 // 0xbc5f894..0xbc5f898
        } else {
            // `0xbc5f85d  mov r8d,ebx`
            // `0xbc5f860  and r8b,0xF`
            // `0xbc5f864  lea rdi,[rsp+0x40]`
            // `0xbc5f869  mov rcx,rdi`
            // `0xbc5f86c  mov dl,0x3B`
            // `0xbc5f86e  call 0xBC76380`
            const std::uint32_t depth1 = (arg & 0xFFFFFF00u) | (arg & 0x0Fu);
            const std::uint32_t eax1 =
                Bc76380_lifted(slot, 0x3BULL, depth1, 0u);
            // `0xbc5f873  mov ebp,eax`
            const std::uint32_t ebp = eax1;                // 0xbc5f873

            // `0xbc5f875  shr bl,4`
            // `0xbc5f878  mov rcx,rdi`
            // `0xbc5f87b  mov dl,0x6D`
            // `0xbc5f87d  mov r8d,ebx`
            // `0xbc5f880  call 0xBC76380`
            const std::uint32_t depth2 = (arg & 0xFFFFFF00u) | ((arg >> 4) & 0x0Fu);
            const std::uint32_t eax2 =
                Bc76380_lifted(slot, 0x6DULL, depth2, 0u);

            // `0xbc5f885  mov ebx,eax`
            // `0xbc5f887  shl bl,4`
            // `0xbc5f88a  or bl,bpl`
            ebx = (eax2 & 0xFFFFFF00u) |
                static_cast<std::uint32_t>(static_cast<std::uint8_t>(
                    (eax2 & 0x0Fu) << 4 | static_cast<std::uint8_t>(eax1 & 0xFFu)));

            // `0xbc5f88d  mov r15,[rsp+0x40]`
            // `0xbc5f892  jmp short 0xBC5F898`
            // `0xbc5f898  mov [rsi],r15`
            *a0 = *slot;                                   // 0xbc5f88d..0xbc5f898
        }
    } else {
        // 0xbc5f894  add r15,3
        // 0xbc5f898  mov [rsi],r15
        *a0 = r15 + 3;                                     // 0xbc5f894..0xbc5f898
    }

    // 0xbc5f89b..0xbc5f8ad
    // 0xbc5f89b  mov rax,[rsp+0x48]
    // 0xbc5f8a0  xor rax,rsp
    // 0xbc5f8a3  mov rcx,[0x1230A0C0]
    // 0xbc5f8aa  cmp rcx,rax
    // 0xbc5f8ad  jne short 0xBC5F8C0
    if (*reinterpret_cast<std::uintptr_t*>(0x1230A0C0) !=
        (cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot))) {  // 0xbc5f89b..0xbc5f8ad
        // `0xbc5f8c0  mov rcx,[rsp+0x48]`
        // `0xbc5f8c5  xor rcx,rsp`
        // `0xbc5f8c8  call 0xE951550`
        // `0xbc5f8cd  int3`
        sub_e951550();                                     // 0xbc5f8c0..0xbc5f8c8  call 0xE951550
        __assume(false);                                   // 0xbc5f8cd  int3
    }

    // 0xbc5f8af  mov eax,ebx
    // 0xbc5f8b1..0xbc5f8bf  add rsp,0x50; pop rbx,rbp,rdi,rsi,r12,r14,r15; ret
    return ebx;                                            // 0xbc5f8af..0xbc5f8bf
}

LIFT_FN(bc5f7b0, "D3D12 submit RTX override", 0xBC5F7B0, sub_bc5f7b0, sub_bc5f7b0_footprint);
```

## Structs touched (name -> header file, offsets confirmed)

- Pair: src/client/features/render/native/bgfx/sub_bc5f7b0.h (+0x00 ptr, +0x08 len), asserted with static_assert [V]
- *a0 argument: +0x0 read/write, no header struct (uintptr_t*) [V]

## Version-stable anchors

- immediate constants 0xF847A07, 0xF59FECD, 0x1230A0C0, 0x7FFFFFFF [V]

## Verification

Static only. All 82 instructions of [0xbc5f7b0, 0xbc5f8ce) are cited in the
ranges above; all 6 calls are quoted verbatim; the .cpp carries the
`// LIFT 0xbc5f7b0 size 0x11e ...` first line, the LIFT_FN registry entry and
the Pair static_asserts (src/client/features/render/native/bgfx/sub_bc5f7b0.cpp).
verify_oc on the .cpp: claimed=43 match=43 mismatch=0 no-such-instr=0.
liftcheck.py 0xbc5f7b0 printed `LIFTCHECK OK 0xbc5f7b0` (exact output pasted
into docs/progress/oc_U-EX1.bc5f7b0.md under ## LIFTCHECK).

Status: L1 — lift complete and verified statically; every call goes to a
lifted function (0xBC76380) or a native::Boundary wrapper (0xEBCE5E0 x2,
0xEBCE570, 0xE951550); no unresolved calls, no stubs, no [?]/[I]/TODO/UNVERIFIED/UNRESOLVED CALL tokens.
