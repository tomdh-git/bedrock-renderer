# Unit U-BA9 â€” bodyActor function 0x66d0a00 (1.26.62.01), continued from oc_U-BA8.md

## NEXT [current]
Next start RVA: 0x66d715d (`imul rcx,r9`, instruction 41 of oc_U-BA8 phase 15 `dis 0x66d70a9 41`, taken directly from rdis output via `dis 0x66d70a9 41`).
Next call: `tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d715d 41`
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Static analysis only; game is closed.

## Phase 1 â€” 0x66d715d, 40 instructions [V]
```
0x66d715d  imul rcx,r9
0x66d7161  movzx r10d,byte ptr [r13+r8+2]
0x66d7167  xor r10,rcx
0x66d716a  imul r10,r9
0x66d716e  movzx ecx,byte ptr [r13+r8+3]
0x66d7174  xor rcx,r10
0x66d7177  imul rcx,r9
0x66d717b  add r8,4
0x66d717f  cmp rdx,r8
0x66d7182  jne short 0x66D7147
0x66d7184  test rax,rax
0x66d7187  je short 0x66D71B3
0x66d7189  add r13,r8
0x66d718c  xor edx,edx
0x66d718e  mov r8,0x100000001B3
0x66d7198  mov r9,rcx
0x66d719b  movzx ecx,byte ptr [r13+rdx]
0x66d71a1  xor rcx,r9
0x66d71a4  imul rcx,r8
0x66d71a8  inc rdx
0x66d71ab  mov r9,rcx
0x66d71ae  cmp rax,rdx
0x66d71b1  jne short 0x66D719B
0x66d71b3  mov [0x129F90D8],rcx
0x66d71ba  lea rcx,[rbp+0xA50]
0x66d71c1  call 0x73150
0x66d71c6  lea rcx,[0x129F90E0]
0x66d71cd  call 0xE938D70
0x66d71d2  jmp 0x66D2B9E
0x66d71d7  and rdx,0xFFFFFFFFFFFFFFFC
0x66d71db  mov rcx,0xCBF29CE484222325
0x66d71e5  xor r8d,r8d
0x66d71e8  mov r9,0x100000001B3
0x66d71f2  movzx r10d,byte ptr [r13+r8]
0x66d71f8  xor r10,rcx
0x66d71fb  imul r10,r9
0x66d71ff  movzx ecx,byte ptr [r13+r8+1]
0x66d7205  xor rcx,r10
0x66d7208  imul rcx,r9
0x66d720c  movzx r10d,byte ptr [r13+r8+2]
```
// [V] Phase 1 is the 7th consecutive FNV-1a hash instance in this cold series (U-BA8 phases 10-15 stored to [0x129F9038]..[0x129F90A8] and branched to sub_66d1d07/sub_66d1e78/sub_66d1e9d/sub_66d1ec2/sub_66d1ee7/sub_66d28ca; this one stores to [0x129F90D8] and branches to sub_66d2b9e). Entered mid-loop at `imul rcx,r9` (rcx=rolling hash, r9=prime live-in). Finishes the 4-byte unrolled loop: `movzx r10d,byte ptr [r13+r8+2]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+3]; xor rcx,r10; imul rcx,r9; add r8,4; cmp rdx,r8; jne short 0x66d7147` (loop back to `movzx r10d,byte ptr [r13+r8]` at 0x66d7147) [V]. Exit `test rax,rax; je short 0x66d71b3` â€” rax==0 (empty data) skips tail loop to store [V]. Tail setup: `add r13,r8` (ptr += processed bytes); `xor edx,edx` (tail index=0); `mov r8,0x100000001B3` (FNV prime) [V][I meaning]; `mov r9,rcx` [V]. loc_66d719b tail loop: `movzx ecx,byte ptr [r13+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; mov r9,rcx; cmp rax,rdx; jne short 0x66d719b` [V]. Store: `mov [0x129F90D8],rcx` ([data_129f90d8] hash result slot) [V]. Post-hash: `lea rcx,[rbp+0xA50]; call sub_73150`; `lea rcx,[0x129F90E0] ([data_129f90e0]); call sub_E938D70`; `jmp sub_66d2b9e` [V]. Then an 8th hash preamble begins: `and rdx,0xFFFFFFFFFFFFFFFC` (len aligned down to multiple of 4) [V]; `mov rcx,0xCBF29CE484222325` (FNV-1a 64-bit offset basis) [I]; `xor r8d,r8d` (byte index=0) [V]; `mov r9,0x100000001B3` (FNV prime) [I]; loc_66d71f2: `movzx r10d,byte ptr [r13+r8]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+1]; xor rcx,r10; imul rcx,r9; movzx r10d,byte ptr [r13+r8+2]` â€” instruction 41 `xor r10,rcx` at 0x66d7212 continues phase 2 [V]. All tags [V] except FNV basis/prime meaning [I] and callee/branch-target roles [?].

## Phase 2 â€” 0x66d7212, 40 instructions [V]
```
0x66d7212  xor r10,rcx
0x66d7215  imul r10,r9
0x66d7219  movzx ecx,byte ptr [r13+r8+3]
0x66d721f  xor rcx,r10
0x66d7222  imul rcx,r9
0x66d7226  add r8,4
0x66d722a  cmp rdx,r8
0x66d722d  jne short 0x66D71F2
0x66d722f  test rax,rax
0x66d7232  je short 0x66D725E
0x66d7234  add r13,r8
0x66d7237  xor edx,edx
0x66d7239  mov r8,0x100000001B3
0x66d7243  mov r9,rcx
0x66d7246  movzx ecx,byte ptr [r13+rdx]
0x66d724c  xor rcx,r9
0x66d724f  imul rcx,r8
0x66d7253  inc rdx
0x66d7256  mov r9,rcx
0x66d7259  cmp rax,rdx
0x66d725c  jne short 0x66D7246
0x66d725e  mov [0x129F90E8],rcx
0x66d7265  lea rcx,[rbp+0xA50]
0x66d726c  call 0x73150
0x66d7271  lea rcx,[0x129F90F0]
0x66d7278  call 0xE938D70
0x66d727d  jmp 0x66D2DF7
0x66d7282  mov rcx,0xCBF29CE484222325
0x66d728c  jmp 0x66D732D
0x66d7291  mov rcx,0xCBF29CE484222325
0x66d729b  jmp 0x66D73D8
0x66d72a0  call 0x1166E0
0x66d72a5  nop
0x66d72a6  and rdx,0xFFFFFFFFFFFFFFFC
0x66d72aa  mov rcx,0xCBF29CE484222325
0x66d72b4  xor r8d,r8d
0x66d72b7  mov r9,0x100000001B3
0x66d72c1  movzx r10d,byte ptr [r13+r8]
0x66d72c7  xor r10,rcx
0x66d72ca  imul r10,r9
0x66d72ce  movzx ecx,byte ptr [r13+r8+1]
```
// [V] Phase 2 finishes the 8th FNV-1a hash instance of this cold series (stores to [0x129F90E8]; phases 10-15 of U-BA8 and phase 1 here stored to [0x129F9038]..[0x129F90D8], branching to sub_66d1d07/sub_66d1e78/sub_66d1e9d/sub_66d1ec2/sub_66d1ee7/sub_66d28ca/sub_66d2b9e; this one branches to sub_66d2df7): entered mid-loop at `xor r10,rcx` (rcx=rolling hash, r9=prime live-in). Loop tail: `imul r10,r9; movzx ecx,byte ptr [r13+r8+3]; xor rcx,r10; imul rcx,r9; add r8,4; cmp rdx,r8; jne short 0x66d71f2` (loop back to `movzx r10d,byte ptr [r13+r8]` at 0x66d71f2) [V]. Exit `test rax,rax; je short 0x66d725e` â€” rax==0 (empty) skips tail loop to store [V]. Tail setup: `add r13,r8`; `xor edx,edx`; `mov r8,0x100000001B3` (FNV prime) [I meaning]; `mov r9,rcx` [V]. loc_66d7246 tail loop: `movzx ecx,byte ptr [r13+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; mov r9,rcx; cmp rax,rdx; jne short 0x66d7246` [V]. Store: `mov [0x129F90E8],rcx` ([data_129f90e8] hash result slot) [V]. Post-hash: `lea rcx,[rbp+0xA50]; call sub_73150`; `lea rcx,[0x129F90F0] ([data_129f90f0]); call sub_E938D70`; `jmp sub_66d2df7` [V]. Then a chain of per-instance headers: `mov rcx,0xCBF29CE484222325; jmp 0x66d732d` (9th instance header, loops at 0x66d732d outside this phase) [V]; `mov rcx,0xCBF29CE484222325; jmp 0x66d73d8` (10th instance header, loops at 0x66d73d8 outside this phase) [V]; `call sub_1166e0; nop` [V] roles [?]. Then an 11th hash preamble: `and rdx,0xFFFFFFFFFFFFFFFC` (len aligned down to multiple of 4) [V]; `mov rcx,0xCBF29CE484222325` (FNV-1a 64-bit offset basis) [I]; `xor r8d,r8d` (byte index=0) [V]; `mov r9,0x100000001B3` (FNV prime) [I]; loc_66d72c1: `movzx r10d,byte ptr [r13+r8]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+1]` — instruction 41 `movzx ecx,byte ptr [r13+r8+1]` at 0x66d72ce continues phase 3 [V]. All tags [V] except FNV basis/prime meaning [I] and callee/branch-target roles [?].

## Phase 3 â€” 0x66d72ce, 40 instructions [V]
```
0x66d72ce  movzx ecx,byte ptr [r13+r8+1]
0x66d72d4  xor rcx,r10
0x66d72d7  imul rcx,r9
0x66d72db  movzx r10d,byte ptr [r13+r8+2]
0x66d72e1  xor r10,rcx
0x66d72e4  imul r10,r9
0x66d72e8  movzx ecx,byte ptr [r13+r8+3]
0x66d72ee  xor rcx,r10
0x66d72f1  imul rcx,r9
0x66d72f5  add r8,4
0x66d72f9  cmp rdx,r8
0x66d72fc  jne short 0x66D72C1
0x66d72fe  test rax,rax
0x66d7301  je short 0x66D732D
0x66d7303  add r13,r8
0x66d7306  xor edx,edx
0x66d7308  mov r8,0x100000001B3
0x66d7312  mov r9,rcx
0x66d7315  movzx ecx,byte ptr [r13+rdx]
0x66d731b  xor rcx,r9
0x66d731e  imul rcx,r8
0x66d7322  inc rdx
0x66d7325  mov r9,rcx
0x66d7328  cmp rax,rdx
0x66d732b  jne short 0x66D7315
0x66d732d  mov [0x129F8FB8],rcx
0x66d7334  lea rcx,[rbp+0xA50]
0x66d733b  call 0x73150
0x66d7340  lea rcx,[0x129F8FC0]
0x66d7347  call 0xE938D70
0x66d734c  jmp 0x66D1666
0x66d7351  and rdx,0xFFFFFFFFFFFFFFFC
0x66d7355  mov rcx,0xCBF29CE484222325
0x66d735f  xor r8d,r8d
0x66d7362  mov r9,0x100000001B3
0x66d736c  movzx r10d,byte ptr [r13+r8]
0x66d7372  xor r10,rcx
0x66d7375  imul r10,r9
0x66d7379  movzx ecx,byte ptr [r13+r8+1]
0x66d737f  xor rcx,r10
0x66d7382  imul rcx,r9
```
// [V] Phase 3 finishes the 11th FNV-1a hash instance (stores to [0x129F8FB8] â€” note the different rodata slot vs phases 1-2's [0x129F90D8]/[0x129F90E8]; U-BA8 phases 10-15 used [0x129F9038]..[0x129F90A8]) and branches to sub_66d1666 (a branch target seen earlier in this cold series, role [?]): entered mid-loop at `movzx ecx,byte ptr [r13+r8+1]` (rcx=rolling hash, r10/r9 live-in). Loop tail: `xor rcx,r10; imul rcx,r9; movzx r10d,byte ptr [r13+r8+2]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+3]; xor rcx,r10; imul rcx,r9; add r8,4; cmp rdx,r8; jne short 0x66d72c1` (loop back to `movzx r10d,byte ptr [r13+r8]` at 0x66d72c1) [V]. Exit `test rax,rax; je short 0x66d732d` â€” rax==0 (empty) skips tail loop to store [V]. Tail setup: `add r13,r8`; `xor edx,edx`; `mov r8,0x100000001B3` (FNV prime) [I meaning]; `mov r9,rcx` [V]. loc_66d7315 tail loop: `movzx ecx,byte ptr [r13+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; mov r9,rcx; cmp rax,rdx; jne short 0x66d7315` [V]. Store: `mov [0x129F8FB8],rcx` ([data_129f8fb8] hash result slot) [V]. Post-hash: `lea rcx,[rbp+0xA50]; call sub_73150`; `lea rcx,[0x129F8FC0] ([data_129f8fc0]); call sub_E938D70`; `jmp sub_66d1666` [V]. Then a 12th hash preamble begins: `and rdx,0xFFFFFFFFFFFFFFFC` (len aligned down to multiple of 4) [V]; `mov rcx,0xCBF29CE484222325` (FNV-1a 64-bit offset basis) [I]; `xor r8d,r8d` (byte index=0) [V]; `mov r9,0x100000001B3` (FNV prime) [I]; loc_66d736c: `movzx r10d,byte ptr [r13+r8]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+1]; xor rcx,r10; imul rcx,r9` â€” instruction 41 `imul rcx,r9` at 0x66d7382 continues phase 4 [V]. All tags [V] except FNV basis/prime meaning [I] and callee/branch-target roles [?].

## Phase 4 â€” 0x66d7382, 40 instructions [V]
```
0x66d7382  imul rcx,r9
0x66d7386  movzx r10d,byte ptr [r13+r8+2]
0x66d738c  xor r10,rcx
0x66d738f  imul r10,r9
0x66d7393  movzx ecx,byte ptr [r13+r8+3]
0x66d7399  xor rcx,r10
0x66d739c  imul rcx,r9
0x66d73a0  add r8,4
0x66d73a4  cmp rdx,r8
0x66d73a7  jne short 0x66D736C
0x66d73a9  test rax,rax
0x66d73ac  je short 0x66D73D8
0x66d73ae  add r13,r8
0x66d73b1  xor edx,edx
0x66d73b3  mov r8,0x100000001B3
0x66d73bd  mov r9,rcx
0x66d73c0  movzx ecx,byte ptr [r13+rdx]
0x66d73c6  xor rcx,r9
0x66d73c9  imul rcx,r8
0x66d73cd  inc rdx
0x66d73d0  mov r9,rcx
0x66d73d3  cmp rax,rdx
0x66d73d6  jne short 0x66D73C0
0x66d73d8  mov [0x129F90B8],rcx
0x66d73df  lea rcx,[rbp+0xA50]
0x66d73e6  call 0x73150
0x66d73eb  lea rcx,[0x129F90C0]
0x66d73f2  call 0xE938D70
0x66d73f7  mov rbx,[rbp+0xD90]
0x66d73fe  jmp 0x66D29A3
0x66d7403  mov rcx,0xCBF29CE484222325
0x66d740d  jmp 0x66D74F3
0x66d7412  mov rdx,0xCBF29CE484222325
0x66d741c  jmp 0x66D758B
0x66d7421  mov rcx,0xCBF29CE484222325
0x66d742b  jmp 0x66D7636
0x66d7430  mov rcx,0xCBF29CE484222325
0x66d743a  jmp 0x66D76E1
0x66d743f  mov rcx,0xCBF29CE484222325
0x66d7449  jmp 0x66D7793
0x66d744e  mov rcx,0xCBF29CE484222325
```
// [V] Phase 4 finishes the 12th FNV-1a hash instance (stores to [0x129F90B8]; note the variant post-hash tail `mov rbx,[rbp+0xD90]` before `jmp sub_66d29a3`, unlike prior instances' plain `jmp`; branch target roles [?]): entered mid-loop at `imul rcx,r9` (rcx=rolling hash, r9=prime live-in). Loop tail: `movzx r10d,byte ptr [r13+r8+2]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+3]; xor rcx,r10; imul rcx,r9; add r8,4; cmp rdx,r8; jne short 0x66d736c` (loop back to `movzx r10d,byte ptr [r13+r8]` at 0x66d736c) [V]. Exit `test rax,rax; je short 0x66d73d8` â€” rax==0 (empty) skips tail loop to store [V]. Tail setup: `add r13,r8`; `xor edx,edx`; `mov r8,0x100000001B3` (FNV prime) [I meaning]; `mov r9,rcx` [V]. loc_66d73c0 tail loop: `movzx ecx,byte ptr [r13+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; mov r9,rcx; cmp rax,rdx; jne short 0x66d73c0` [V]. Store: `mov [0x129F90B8],rcx` ([data_129f90b8] hash result slot) [V]. Post-hash: `lea rcx,[rbp+0xA50]; call sub_73150`; `lea rcx,[0x129F90C0] ([data_129f90c0]); call sub_E938D70`; `mov rbx,[rbp+0xD90]`; `jmp sub_66d29a3` [V]. Then a chain of per-instance headers, each `mov <reg>,0xCBF29CE484222325; jmp <loop target outside this phase>`: `mov rcx,basis; jmp 0x66d74f3` (instance 13 header) [V]; `mov rdx,basis; jmp 0x66d758b` (instance 14 header, note rdx instead of rcx) [V]; `mov rcx,basis; jmp 0x66d7636` (instance 15) [V]; `mov rcx,basis; jmp 0x66d76e1` (instance 16) [V]; `mov rcx,basis; jmp 0x66d7793` (instance 17) [V]; then instruction 41 `mov rcx,0xCBF29CE484222325` at 0x66d744e (instance 18 header) continues phase 5 [V]. All tags [V] except FNV basis meaning [I] and callee/branch-target roles [?].

## Phase 5 â€” 0x66d744e, 40 instructions [V]
```
0x66d744e  mov rcx,0xCBF29CE484222325
0x66d7458  jmp 0x66D783E
0x66d745d  mov rcx,0xCBF29CE484222325
0x66d7467  jmp 0x66D78E9
0x66d746c  and rdx,0xFFFFFFFFFFFFFFFC
0x66d7470  mov rcx,0xCBF29CE484222325
0x66d747a  xor r8d,r8d
0x66d747d  mov r9,0x100000001B3
0x66d7487  movzx r10d,byte ptr [r13+r8]
0x66d748d  xor r10,rcx
0x66d7490  imul r10,r9
0x66d7494  movzx ecx,byte ptr [r13+r8+1]
0x66d749a  xor rcx,r10
0x66d749d  imul rcx,r9
0x66d74a1  movzx r10d,byte ptr [r13+r8+2]
0x66d74a7  xor r10,rcx
0x66d74aa  imul r10,r9
0x66d74ae  movzx ecx,byte ptr [r13+r8+3]
0x66d74b4  xor rcx,r10
0x66d74b7  imul rcx,r9
0x66d74bb  add r8,4
0x66d74bf  cmp rdx,r8
0x66d74c2  jne short 0x66D7487
0x66d74c4  test rax,rax
0x66d74c7  je short 0x66D74F3
0x66d74c9  add r13,r8
0x66d74cc  xor edx,edx
0x66d74ce  mov r8,0x100000001B3
0x66d74d8  mov r9,rcx
0x66d74db  movzx ecx,byte ptr [r13+rdx]
0x66d74e1  xor rcx,r9
0x66d74e4  imul rcx,r8
0x66d74e8  inc rdx
0x66d74eb  mov r9,rcx
0x66d74ee  cmp rax,rdx
0x66d74f1  jne short 0x66D74DB
0x66d74f3  mov [0x129F8F98],rcx
0x66d74fa  lea rcx,[rbp+0xA50]
0x66d7501  call 0x73150
0x66d7506  lea rcx,[0x129F8FA0]
0x66d750d  call 0xE938D70
```
// [V] Phase 5 opens with two per-instance headers (`mov rcx,0xCBF29CE484222325; jmp 0x66d783e` instance 18 header; `mov rcx,0xCBF29CE484222325; jmp 0x66d78e9` instance 19 header; loop targets outside this phase) [V], then a complete FNV-1a hash instance (instance 20; stores to [0x129F8F98]; U-BA8 phases 10-15 used [0x129F9038]..[0x129F90A8], phases 1-4 here used [0x129F90D8]/[0x129F90E8]/[0x129F8FB8]/[0x129F90B8]; branch target role [?]): preamble `and rdx,0xFFFFFFFFFFFFFFFC` (len aligned down to multiple of 4) [V]; `mov rcx,0xCBF29CE484222325` (FNV-1a 64-bit offset basis) [I]; `xor r8d,r8d` (byte index=0) [V]; `mov r9,0x100000001B3` (FNV prime) [I]. loc_66d7487 4-byte unrolled loop: `movzx r10d,byte ptr [r13+r8]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+1]; xor rcx,r10; imul rcx,r9; movzx r10d,byte ptr [r13+r8+2]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+3]; xor rcx,r10; imul rcx,r9; add r8,4; cmp rdx,r8; jne short 0x66d7487` [V]. Exit `test rax,rax; je short 0x66d74f3` â€” rax==0 (empty) skips tail loop to store [V]. Tail setup: `add r13,r8`; `xor edx,edx`; `mov r8,prime`; `mov r9,rcx` [V]. loc_66d74db tail loop: `movzx ecx,byte ptr [r13+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; mov r9,rcx; cmp rax,rdx; jne short 0x66d74db` [V]. Store: `mov [0x129F8F98],rcx` ([data_129f8f98] hash result slot) [V]. Post-hash start: `lea rcx,[rbp+0xA50]; call sub_73150`; `lea rcx,[0x129F8FA0] ([data_129f8fa0]); call sub_E938D70` â€” instruction 41 is that call; the instance's closing `jmp <sub_x>` lies at the start of phase 6 [V]. All tags [V] except FNV basis/prime meaning [I] and callee/branch-target roles [?].

## Phase 6 â€” 0x66d750d, 40 instructions [V]
```
0x66d750d  call 0xE938D70
0x66d7512  jmp 0x66D14B0
0x66d7517  and r8,0xFFFFFFFFFFFFFFFC
0x66d751b  mov rdx,0xCBF29CE484222325
0x66d7525  xor r9d,r9d
0x66d7528  movzx r10d,byte ptr [r13+r9]
0x66d752e  xor r10,rdx
0x66d7531  imul r10,rcx
0x66d7535  movzx edx,byte ptr [r13+r9+1]
0x66d753b  xor rdx,r10
0x66d753e  imul rdx,rcx
0x66d7542  movzx r10d,byte ptr [r13+r9+2]
0x66d7548  xor r10,rdx
0x66d754b  imul r10,rcx
0x66d754f  movzx edx,byte ptr [r13+r9+3]
0x66d7555  xor rdx,r10
0x66d7558  imul rdx,rcx
0x66d755c  add r9,4
0x66d7560  cmp r8,r9
0x66d7563  jne short 0x66D7528
0x66d7565  test rax,rax
0x66d7568  je short 0x66D758B
0x66d756a  add r13,r9
0x66d756d  xor r8d,r8d
0x66d7570  mov r9,rdx
0x66d7573  movzx edx,byte ptr [r13+r8]
0x66d7579  xor rdx,r9
0x66d757c  imul rdx,rcx
0x66d7580  inc r8
0x66d7583  mov r9,rdx
0x66d7586  cmp rax,r8
0x66d7589  jne short 0x66D7573
0x66d758b  mov [0x129F8FA8],rdx
0x66d7592  lea rcx,[rbp+0xA50]
0x66d7599  call 0x73150
0x66d759e  lea rcx,[0x129F8FB0]
0x66d75a5  call 0xE938D70
0x66d75aa  jmp 0x66D14D5
0x66d75af  and rdx,0xFFFFFFFFFFFFFFFC
0x66d75b3  mov rcx,0xCBF29CE484222325
0x66d75bd  xor r8d,r8d
```
// [V] Phase 6 closes instance 20 (opened in phase 5; stores to [0x129F8FA8], branches to sub_66d14d5; branch target role [?]): `call sub_E938D70` (completes phase-5's `lea rcx,[0x129F8FA0]`); `jmp sub_66d14b0` [V]. Then instance 21 with a VARIANT register mapping (len in r8, basis in rdx, index in r9, prime in rcx live-in; hash result stored in rdx): preamble `and r8,0xFFFFFFFFFFFFFFFC` (len aligned down to multiple of 4, variant: r8 not rdx) [V]; `mov rdx,0xCBF29CE484222325` (FNV basis) [I]; `xor r9d,r9d` (index=0) [V]. loc_66d7528 loop: `movzx r10d,byte ptr [r13+r9]; xor r10,rdx; imul r10,rcx; movzx edx,byte ptr [r13+r9+1]; xor rdx,r10; imul rdx,rcx; movzx r10d,byte ptr [r13+r9+2]; xor r10,rdx; imul r10,rcx; movzx edx,byte ptr [r13+r9+3]; xor rdx,r10; imul rdx,rcx; add r9,4; cmp r8,r9; jne short 0x66d7528` [V]. Exit `test rax,rax; je short 0x66d758b` [V]. Tail setup: `add r13,r9`; `xor r8d,r8d`; `mov r9,rdx` [V]. loc_66d7573 tail loop: `movzx edx,byte ptr [r13+r8]; xor rdx,r9; imul rdx,rcx; inc r8; mov r9,rdx; cmp rax,r8; jne short 0x66d7573` [V]. Store: `mov [0x129F8FA8],rdx` ([data_129f8fa8] hash result slot) [V]. Post-hash: `lea rcx,[rbp+0xA50]; call sub_73150`; `lea rcx,[0x129F8FB0] ([data_129f8fb0]); call sub_E938D70`; `jmp sub_66d14d5` [V]. Then instance 22 preamble: `and rdx,0xFFFFFFFFFFFFFFFC` [V]; `mov rcx,0xCBF29CE484222325` (FNV-1a 64-bit offset basis) [I]; `xor r8d,r8d` (byte index=0) â€” instruction 41 at 0x66d75bd continues phase 7 [V]. All tags [V] except FNV basis meaning [I] and callee/branch-target roles [?].

## Phase 7 â€” 0x66d75bd, 40 instructions [V]
```
0x66d75bd  xor r8d,r8d
0x66d75c0  mov r9,0x100000001B3
0x66d75ca  movzx r10d,byte ptr [r13+r8]
0x66d75d0  xor r10,rcx
0x66d75d3  imul r10,r9
0x66d75d7  movzx ecx,byte ptr [r13+r8+1]
0x66d75dd  xor rcx,r10
0x66d75e0  imul rcx,r9
0x66d75e4  movzx r10d,byte ptr [r13+r8+2]
0x66d75ea  xor r10,rcx
0x66d75ed  imul r10,r9
0x66d75f1  movzx ecx,byte ptr [r13+r8+3]
0x66d75f7  xor rcx,r10
0x66d75fa  imul rcx,r9
0x66d75fe  add r8,4
0x66d7602  cmp rdx,r8
0x66d7605  jne short 0x66D75CA
0x66d7607  test rax,rax
0x66d760a  je short 0x66D7636
0x66d760c  add r13,r8
0x66d760f  xor edx,edx
0x66d7611  mov r8,0x100000001B3
0x66d761b  mov r9,rcx
0x66d761e  movzx ecx,byte ptr [r13+rdx]
0x66d7624  xor rcx,r9
0x66d7627  imul rcx,r8
0x66d762b  inc rdx
0x66d762e  mov r9,rcx
0x66d7631  cmp rax,rdx
0x66d7634  jne short 0x66D761E
0x66d7636  mov [0x129F8FC8],rcx
0x66d763d  lea rcx,[rbp+0xA50]
0x66d7644  call 0x73150
0x66d7649  lea rcx,[0x129F8FD0]
0x66d7650  call 0xE938D70
0x66d7655  jmp 0x66D174A
0x66d765a  and rdx,0xFFFFFFFFFFFFFFFC
0x66d765e  mov rcx,0xCBF29CE484222325
0x66d7668  xor r8d,r8d
0x66d766b  mov r9,0x100000001B3
0x66d7675  movzx r10d,byte ptr [r13+r8]
```
// [V] Phase 7 finishes instance 22 (opened in phase 6; stores to [0x129F8FC8]; branches to sub_66d174a, role [?]): entered at `xor r8d,r8d` (index=0) with rcx=basis and r9=prime live-in from phase 6's preamble. Loop loc_66d75ca: `movzx r10d,byte ptr [r13+r8]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+1]; xor rcx,r10; imul rcx,r9; movzx r10d,byte ptr [r13+r8+2]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+3]; xor rcx,r10; imul rcx,r9; add r8,4; cmp rdx,r8; jne short 0x66d75ca` [V]. Exit `test rax,rax; je short 0x66d7636` â€” rax==0 (empty) skips tail loop to store [V]. Tail setup: `add r13,r8`; `xor edx,edx`; `mov r8,prime`; `mov r9,rcx` [V]. loc_66d761e tail loop: `movzx ecx,byte ptr [r13+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; mov r9,rcx; cmp rax,rdx; jne short 0x66d761e` [V]. Store: `mov [0x129F8FC8],rcx` ([data_129f8fc8] hash result slot) [V]. Post-hash: `lea rcx,[rbp+0xA50]; call sub_73150`; `lea rcx,[0x129F8FD0] ([data_129f8fd0]); call sub_E938D70`; `jmp sub_66d174a` [V]. Then instance 23 preamble: `and rdx,0xFFFFFFFFFFFFFFFC` (len aligned to 4) [V]; `mov rcx,0xCBF29CE484222325` (FNV basis) [I]; `xor r8d,r8d` (index=0) [V]; `mov r9,0x100000001B3` (FNV prime) [I]; loc_66d7675: `movzx r10d,byte ptr [r13+r8]` â€” instruction 41 at 0x66d7675 continues phase 8 [V]. All tags [V] except FNV basis/prime meaning [I] and callee/branch-target roles [?].

## Phase 8 â€” 0x66d7675, 40 instructions [V]
```
0x66d7675  movzx r10d,byte ptr [r13+r8]
0x66d767b  xor r10,rcx
0x66d767e  imul r10,r9
0x66d7682  movzx ecx,byte ptr [r13+r8+1]
0x66d7688  xor rcx,r10
0x66d768b  imul rcx,r9
0x66d768f  movzx r10d,byte ptr [r13+r8+2]
0x66d7695  xor r10,rcx
0x66d7698  imul r10,r9
0x66d769c  movzx ecx,byte ptr [r13+r8+3]
0x66d76a2  xor rcx,r10
0x66d76a5  imul rcx,r9
0x66d76a9  add r8,4
0x66d76ad  cmp rdx,r8
0x66d76b0  jne short 0x66D7675
0x66d76b2  test rax,rax
0x66d76b5  je short 0x66D76E1
0x66d76b7  add r13,r8
0x66d76ba  xor edx,edx
0x66d76bc  mov r8,0x100000001B3
0x66d76c6  mov r9,rcx
0x66d76c9  movzx ecx,byte ptr [r13+rdx]
0x66d76cf  xor rcx,r9
0x66d76d2  imul rcx,r8
0x66d76d6  inc rdx
0x66d76d9  mov r9,rcx
0x66d76dc  cmp rax,rdx
0x66d76df  jne short 0x66D76C9
0x66d76e1  mov [0x129F8FD8],rcx
0x66d76e8  lea rcx,[rbp+0xA50]
0x66d76ef  call 0x73150
0x66d76f4  lea rcx,[0x129F8FE0]
0x66d76fb  call 0xE938D70
0x66d7700  mov r14,[rbp+0xD78]
0x66d7707  jmp 0x66D1833
0x66d770c  and rdx,0xFFFFFFFFFFFFFFFC
0x66d7710  mov rcx,0xCBF29CE484222325
0x66d771a  xor r8d,r8d
0x66d771d  mov r9,0x100000001B3
0x66d7727  movzx r10d,byte ptr [r13+r8]
0x66d772d  xor r10,rcx
```
// [V] Phase 8 finishes instance 23 (opened in phase 7; stores to [0x129F8FD8]; variant post-hash tail `mov r14,[rbp+0xD78]; jmp sub_66d1833`, role [?]): loop tail `xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+1]; xor rcx,r10; imul rcx,r9; movzx r10d,byte ptr [r13+r8+2]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+3]; xor rcx,r10; imul rcx,r9; add r8,4; cmp rdx,r8; jne short 0x66d7675` [V]. Exit `test rax,rax; je short 0x66d76e1` â€” rax==0 (empty) skips tail loop to store [V]. Tail setup: `add r13,r8`; `xor edx,edx`; `mov r8,prime`; `mov r9,rcx` [V]. loc_66d76c9 tail loop: `movzx ecx,byte ptr [r13+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; mov r9,rcx; cmp rax,rdx; jne short 0x66d76c9` [V]. Store: `mov [0x129F8FD8],rcx` ([data_129f8fd8] hash result slot) [V]. Post-hash: `lea rcx,[rbp+0xA50]; call sub_73150`; `lea rcx,[0x129F8FE0] ([data_129f8fe0]); call sub_E938D70`; `mov r14,[rbp+0xD78]`; `jmp sub_66d1833` [V]. Then instance 24 preamble + loop head: `and rdx,0xFFFFFFFFFFFFFFFC` (len aligned to 4) [V]; `mov rcx,0xCBF29CE484222325` (FNV basis) [I]; `xor r8d,r8d` (index=0) [V]; `mov r9,0x100000001B3` (FNV prime) [I]; loc_66d7727: `movzx r10d,byte ptr [r13+r8]; xor r10,rcx` â€” instruction 41 `xor r10,rcx` at 0x66d772d continues phase 9 [V]. All tags [V] except FNV basis/prime meaning [I] and callee/branch-target roles [?].

## Phase 9 â€” 0x66d772d, 40 instructions [V]
```
0x66d772d  xor r10,rcx
0x66d7730  imul r10,r9
0x66d7734  movzx ecx,byte ptr [r13+r8+1]
0x66d773a  xor rcx,r10
0x66d773d  imul rcx,r9
0x66d7741  movzx r10d,byte ptr [r13+r8+2]
0x66d7747  xor r10,rcx
0x66d774a  imul r10,r9
0x66d774e  movzx ecx,byte ptr [r13+r8+3]
0x66d7754  xor rcx,r10
0x66d7757  imul rcx,r9
0x66d775b  add r8,4
0x66d775f  cmp rdx,r8
0x66d7762  jne short 0x66D7727
0x66d7764  test rax,rax
0x66d7767  je short 0x66D7793
0x66d7769  add r13,r8
0x66d776c  xor edx,edx
0x66d776e  mov r8,0x100000001B3
0x66d7778  mov r9,rcx
0x66d777b  movzx ecx,byte ptr [r13+rdx]
0x66d7781  xor rcx,r9
0x66d7784  imul rcx,r8
0x66d7788  inc rdx
0x66d778b  mov r9,rcx
0x66d778e  cmp rax,rdx
0x66d7791  jne short 0x66D777B
0x66d7793  mov [0x129F8FE8],rcx
0x66d779a  lea rcx,[rbp+0xA50]
0x66d77a1  call 0x73150
0x66d77a6  lea rcx,[0x129F8FF0]
0x66d77ad  call 0xE938D70
0x66d77b2  jmp 0x66D1997
0x66d77b7  and rdx,0xFFFFFFFFFFFFFFFC
0x66d77bb  mov rcx,0xCBF29CE484222325
0x66d77c5  xor r8d,r8d
0x66d77c8  mov r9,0x100000001B3
0x66d77d2  movzx r10d,byte ptr [r13+r8]
0x66d77d8  xor r10,rcx
0x66d77db  imul r10,r9
0x66d77df  movzx ecx,byte ptr [r13+r8+1]
```
// [V] Phase 9 finishes instance 24 (opened in phase 8; stores to [0x129F8FE8]; branches to sub_66d1997, role [?]): entered at `xor r10,rcx` with rcx=rolling hash, r9=prime live-in. Loop tail: `imul r10,r9; movzx ecx,byte ptr [r13+r8+1]; xor rcx,r10; imul rcx,r9; movzx r10d,byte ptr [r13+r8+2]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+3]; xor rcx,r10; imul rcx,r9; add r8,4; cmp rdx,r8; jne short 0x66d7727` [V]. Exit `test rax,rax; je short 0x66d7793` â€” rax==0 (empty) skips tail loop to store [V]. Tail setup: `add r13,r8`; `xor edx,edx`; `mov r8,prime`; `mov r9,rcx` [V]. loc_66d777b tail loop: `movzx ecx,byte ptr [r13+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; mov r9,rcx; cmp rax,rdx; jne short 0x66d777b` [V]. Store: `mov [0x129F8FE8],rcx` ([data_129f8fe8] hash result slot) [V]. Post-hash: `lea rcx,[rbp+0xA50]; call sub_73150`; `lea rcx,[0x129F8FF0] ([data_129f8ff0]); call sub_E938D70`; `jmp sub_66d1997` [V]. Then instance 25 preamble + loop head: `and rdx,0xFFFFFFFFFFFFFFFC` (len aligned to 4) [V]; `mov rcx,0xCBF29CE484222325` (FNV basis) [I]; `xor r8d,r8d` (index=0) [V]; `mov r9,0x100000001B3` (FNV prime) [I]; loc_66d77d2: `movzx r10d,byte ptr [r13+r8]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+1]` â€” instruction 41 `movzx ecx,byte ptr [r13+r8+1]` at 0x66d77df continues phase 10 [V]. All tags [V] except FNV basis/prime meaning [I] and callee/branch-target roles [?].

## Phase 10 â€” 0x66d77df, 40 instructions [V]
```
0x66d77df  movzx ecx,byte ptr [r13+r8+1]
0x66d77e5  xor rcx,r10
0x66d77e8  imul rcx,r9
0x66d77ec  movzx r10d,byte ptr [r13+r8+2]
0x66d77f2  xor r10,rcx
0x66d77f5  imul r10,r9
0x66d77f9  movzx ecx,byte ptr [r13+r8+3]
0x66d77ff  xor rcx,r10
0x66d7802  imul rcx,r9
0x66d7806  add r8,4
0x66d780a  cmp rdx,r8
0x66d780d  jne short 0x66D77D2
0x66d780f  test rax,rax
0x66d7812  je short 0x66D783E
0x66d7814  add r13,r8
0x66d7817  xor edx,edx
0x66d7819  mov r8,0x100000001B3
0x66d7823  mov r9,rcx
0x66d7826  movzx ecx,byte ptr [r13+rdx]
0x66d782c  xor rcx,r9
0x66d782f  imul rcx,r8
0x66d7833  inc rdx
0x66d7836  mov r9,rcx
0x66d7839  cmp rax,rdx
0x66d783c  jne short 0x66D7826
0x66d783e  mov [0x129F90C8],rcx
0x66d7845  lea rcx,[rbp+0xA50]
0x66d784c  call 0x73150
0x66d7851  lea rcx,[0x129F90D0]
0x66d7858  call 0xE938D70
0x66d785d  jmp 0x66D2AC3
0x66d7862  and rdx,0xFFFFFFFFFFFFFFFC
0x66d7866  mov rcx,0xCBF29CE484222325
0x66d7870  xor r8d,r8d
0x66d7873  mov r9,0x100000001B3
0x66d787d  movzx r10d,byte ptr [r13+r8]
0x66d7883  xor r10,rcx
0x66d7886  imul r10,r9
0x66d788a  movzx ecx,byte ptr [r13+r8+1]
0x66d7890  xor rcx,r10
0x66d7893  imul rcx,r9
```
// [V] Phase 10 finishes instance 25 (opened in phase 9; stores to [0x129F90C8]; branches to sub_66d2ac3, role [?]): entered at `movzx ecx,byte ptr [r13+r8+1]` with rcx=rolling hash, r10/r9 live-in. Loop tail: `xor rcx,r10; imul rcx,r9; movzx r10d,byte ptr [r13+r8+2]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+3]; xor rcx,r10; imul rcx,r9; add r8,4; cmp rdx,r8; jne short 0x66d77d2` [V]. Exit `test rax,rax; je short 0x66d783e` â€” rax==0 (empty) skips tail loop to store [V]. Tail setup: `add r13,r8`; `xor edx,edx`; `mov r8,prime`; `mov r9,rcx` [V]. loc_66d7826 tail loop: `movzx ecx,byte ptr [r13+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; mov r9,rcx; cmp rax,rdx; jne short 0x66d7826` [V]. Store: `mov [0x129F90C8],rcx` ([data_129f90c8] hash result slot) [V]. Post-hash: `lea rcx,[rbp+0xA50]; call sub_73150`; `lea rcx,[0x129F90D0] ([data_129f90d0]); call sub_E938D70`; `jmp sub_66d2ac3` [V]. Then instance 26 preamble + loop head: `and rdx,0xFFFFFFFFFFFFFFFC` (len aligned to 4) [V]; `mov rcx,0xCBF29CE484222325` (FNV basis) [I]; `xor r8d,r8d` (index=0) [V]; `mov r9,0x100000001B3` (FNV prime) [I]; loc_66d787d: `movzx r10d,byte ptr [r13+r8]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+1]; xor rcx,r10; imul rcx,r9` â€” instruction 41 `imul rcx,r9` at 0x66d7893 continues phase 11 [V]. All tags [V] except FNV basis/prime meaning [I] and callee/branch-target roles [?].

## Phase 11 â€” 0x66d7893, 40 instructions [V]
```
0x66d7893  imul rcx,r9
0x66d7897  movzx r10d,byte ptr [r13+r8+2]
0x66d789d  xor r10,rcx
0x66d78a0  imul r10,r9
0x66d78a4  movzx ecx,byte ptr [r13+r8+3]
0x66d78aa  xor rcx,r10
0x66d78ad  imul rcx,r9
0x66d78b1  add r8,4
0x66d78b5  cmp rdx,r8
0x66d78b8  jne short 0x66D787D
0x66d78ba  test rax,rax
0x66d78bd  je short 0x66D78E9
0x66d78bf  add r13,r8
0x66d78c2  xor edx,edx
0x66d78c4  mov r8,0x100000001B3
0x66d78ce  mov r9,rcx
0x66d78d1  movzx ecx,byte ptr [r13+rdx]
0x66d78d7  xor rcx,r9
0x66d78da  imul rcx,r8
0x66d78de  inc rdx
0x66d78e1  mov r9,rcx
0x66d78e4  cmp rax,rdx
0x66d78e7  jne short 0x66D78D1
0x66d78e9  mov [0x129F8FF8],rcx
0x66d78f0  lea rcx,[rbp+0xA50]
0x66d78f7  call 0x73150
0x66d78fc  lea rcx,[0x129F9000]
0x66d7903  call 0xE938D70
0x66d7908  jmp 0x66D1A60
0x66d790d  mov rcx,0xCBF29CE484222325
0x66d7917  jmp 0x66D79D0
0x66d791c  mov rcx,0xCBF29CE484222325
0x66d7926  jmp 0x66D7A8A
0x66d792b  mov rcx,0xCBF29CE484222325
0x66d7935  jmp 0x66D7B32
0x66d793a  and rdx,0xFFFFFFFFFFFFFFFC
0x66d793e  mov rcx,0xCBF29CE484222325
0x66d7948  xor r8d,r8d
0x66d794b  mov r9,0x100000001B3
0x66d7955  mov r11,[rbp+0x7D8]
0x66d795c  movzx r10d,byte ptr [r11+r8]
```
// [V] Phase 11 finishes instance 26 (opened in phase 10; stores to [0x129F8FF8]; branches to sub_66d1a60, role [?]): entered at `imul rcx,r9`. Loop tail `movzx r10d,byte ptr [r13+r8+2]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+3]; xor rcx,r10; imul rcx,r9; add r8,4; cmp rdx,r8; jne short 0x66d787d` [V]. Exit `test rax,rax; je short 0x66d78e9` â€” rax==0 (empty) skips tail loop to store [V]. Tail setup: `add r13,r8`; `xor edx,edx`; `mov r8,prime`; `mov r9,rcx` [V]. loc_66d78d1 tail loop: `movzx ecx,byte ptr [r13+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; mov r9,rcx; cmp rax,rdx; jne short 0x66d78d1` [V]. Store: `mov [0x129F8FF8],rcx` ([data_129f8ff8] hash result slot) [V]. Post-hash: `lea rcx,[rbp+0xA50]; call sub_73150`; `lea rcx,[0x129F9000] ([data_129f9000]); call sub_E938D70`; `jmp sub_66d1a60` [V]. Then three per-instance headers `mov rcx,0xCBF29CE484222325; jmp <loop outside this phase>`: to 0x66d79d0 (instance 27) [V]; to 0x66d7a8a (instance 28) [V]; to 0x66d7b32 (instance 29) [V]. Then instance 30 preamble â€” NEW VARIANT: `and rdx,0xFFFFFFFFFFFFFFFC` (len aligned to 4) [V]; `mov rcx,0xCBF29CE484222325` (FNV basis) [I]; `xor r8d,r8d` (index=0) [V]; `mov r9,0x100000001B3` (FNV prime) [I]; `mov r11,[rbp+0x7D8]` â€” data base loaded from the [rbp+0x7D8] out-arg slot (ctx ptr stored there in U-BA8 phases 6-7 at 0x66d6a0a/0x66d6a87) instead of using r13 directly [V]. loc_66d795c: `movzx r10d,byte ptr [r11+r8]` â€” instruction 41 at 0x66d795c continues phase 12 [V]. All tags [V] except FNV basis/prime meaning [I] and callee/branch-target roles [?].

## Phase 12 â€” 0x66d795c, 40 instructions [V]
```
0x66d795c  movzx r10d,byte ptr [r11+r8]
0x66d7961  xor r10,rcx
0x66d7964  imul r10,r9
0x66d7968  movzx ecx,byte ptr [r11+r8+1]
0x66d796e  xor rcx,r10
0x66d7971  imul rcx,r9
0x66d7975  movzx r10d,byte ptr [r11+r8+2]
0x66d797b  xor r10,rcx
0x66d797e  imul r10,r9
0x66d7982  movzx ecx,byte ptr [r11+r8+3]
0x66d7988  xor rcx,r10
0x66d798b  imul rcx,r9
0x66d798f  add r8,4
0x66d7993  cmp rdx,r8
0x66d7996  jne short 0x66D795C
0x66d7998  test rax,rax
0x66d799b  je short 0x66D79D0
0x66d799d  add [rbp+0x7D8],r8
0x66d79a4  xor edx,edx
0x66d79a6  mov r8,0x100000001B3
0x66d79b0  mov r9,rcx
0x66d79b3  mov rcx,[rbp+0x7D8]
0x66d79ba  movzx ecx,byte ptr [rcx+rdx]
0x66d79be  xor rcx,r9
0x66d79c1  imul rcx,r8
0x66d79c5  inc rdx
0x66d79c8  mov r9,rcx
0x66d79cb  cmp rax,rdx
0x66d79ce  jne short 0x66D79B3
0x66d79d0  mov [0x129F9088],rcx
0x66d79d7  lea rcx,[rbp+0xA50]
0x66d79de  call 0x73150
0x66d79e3  lea rcx,[0x129F9090]
0x66d79ea  call 0xE938D70
0x66d79ef  jmp 0x66D267B
0x66d79f4  and rdx,0xFFFFFFFFFFFFFFFC
0x66d79f8  mov rcx,0xCBF29CE484222325
0x66d7a02  xor r8d,r8d
0x66d7a05  mov r9,0x100000001B3
0x66d7a0f  mov r11,[rbp+0xD80]
0x66d7a16  movzx r10d,byte ptr [r11+r8]
```
// [V] Phase 12 finishes instance 30 (opened in phase 11; stores to [0x129F9088]; branches to sub_66d267b, role [?]): VARIANT tail handling â€” `add [rbp+0x7D8],r8` advances the saved ctx slot in memory instead of a register; tail loop reloads `mov rcx,[rbp+0x7D8]; movzx ecx,byte ptr [rcx+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; mov r9,rcx; cmp rax,rdx; jne short 0x66d79b3` [V]. Loop (instance 30, base in r11=[rbp+0x7D8]): `movzx r10d,byte ptr [r11+r8]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r11+r8+1]; xor rcx,r10; imul rcx,r9; movzx r10d,byte ptr [r11+r8+2]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r11+r8+3]; xor rcx,r10; imul rcx,r9; add r8,4; cmp rdx,r8; jne short 0x66d795c` [V]. Exit `test rax,rax; je short 0x66d79d0` â€” rax==0 (empty) skips tail loop to store [V]. Store: `mov [0x129F9088],rcx` ([data_129f9088] hash result slot) [V]. Post-hash: `lea rcx,[rbp+0xA50]; call sub_73150`; `lea rcx,[0x129F9090] ([data_129f9090]); call sub_E938D70`; `jmp sub_66d267b` [V]. Then instance 31 preamble â€” another slot base: `and rdx,0xFFFFFFFFFFFFFFFC` (len aligned to 4) [V]; `mov rcx,0xCBF29CE484222325` (FNV basis) [I]; `xor r8d,r8d` (index=0) [V]; `mov r9,0x100000001B3` (FNV prime) [I]; `mov r11,[rbp+0xD80]` â€” base from the [rbp+0xD80] out-arg slot (stored there in U-BA8 phase 7 at 0x66d6a87) [V]. loc_66d7a16: `movzx r10d,byte ptr [r11+r8]` â€” instruction 41 at 0x66d7a16 continues phase 13 [V]. All tags [V] except FNV basis/prime meaning [I] and callee/branch-target roles [?].

## Phase 13 â€” 0x66d7a16, 40 instructions [V]
```
0x66d7a16  movzx r10d,byte ptr [r11+r8]
0x66d7a1b  xor r10,rcx
0x66d7a1e  imul r10,r9
0x66d7a22  movzx ecx,byte ptr [r11+r8+1]
0x66d7a28  xor rcx,r10
0x66d7a2b  imul rcx,r9
0x66d7a2f  movzx r10d,byte ptr [r11+r8+2]
0x66d7a35  xor r10,rcx
0x66d7a38  imul r10,r9
0x66d7a3c  movzx ecx,byte ptr [r11+r8+3]
0x66d7a42  xor rcx,r10
0x66d7a45  imul rcx,r9
0x66d7a49  add r8,4
0x66d7a4d  cmp rdx,r8
0x66d7a50  jne short 0x66D7A16
0x66d7a52  test rax,rax
0x66d7a55  je short 0x66D7A8A
0x66d7a57  add [rbp+0xD80],r8
0x66d7a5e  xor edx,edx
0x66d7a60  mov r8,0x100000001B3
0x66d7a6a  mov r9,rcx
0x66d7a6d  mov rcx,[rbp+0xD80]
0x66d7a74  movzx ecx,byte ptr [rcx+rdx]
0x66d7a78  xor rcx,r9
0x66d7a7b  imul rcx,r8
0x66d7a7f  inc rdx
0x66d7a82  mov r9,rcx
0x66d7a85  cmp rax,rdx
0x66d7a88  jne short 0x66D7A6D
0x66d7a8a  mov [0x129F9098],rcx
0x66d7a91  lea rcx,[rbp+0xA50]
0x66d7a98  call 0x73150
0x66d7a9d  lea rcx,[0x129F90A0]
0x66d7aa4  call 0xE938D70
0x66d7aa9  jmp 0x66D27E1
0x66d7aae  and rdx,0xFFFFFFFFFFFFFFFC
0x66d7ab2  mov rcx,0xCBF29CE484222325
0x66d7abc  xor r8d,r8d
0x66d7abf  mov r9,0x100000001B3
0x66d7ac9  movzx r10d,byte ptr [rsi+r8]
0x66d7ace  xor r10,rcx
```
// [V] Phase 13 finishes instance 31 (opened in phase 12; stores to [0x129F9098]; branches to sub_66d27e1, role [?]): VARIANT tail `add [rbp+0xD80],r8` advances the saved slot in memory; tail loop reloads `mov rcx,[rbp+0xD80]; movzx ecx,byte ptr [rcx+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; mov r9,rcx; cmp rax,rdx; jne short 0x66d7a6d` [V]. Loop (instance 31, base r11=[rbp+0xD80]): `movzx r10d,byte ptr [r11+r8]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r11+r8+1]; xor rcx,r10; imul rcx,r9; movzx r10d,byte ptr [r11+r8+2]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r11+r8+3]; xor rcx,r10; imul rcx,r9; add r8,4; cmp rdx,r8; jne short 0x66d7a16` [V]. Exit `test rax,rax; je short 0x66d7a8a` â€” rax==0 (empty) skips tail loop to store [V]. Store: `mov [0x129F9098],rcx` ([data_129f9098] hash result slot) [V]. Post-hash: `lea rcx,[rbp+0xA50]; call sub_73150`; `lea rcx,[0x129F90A0] ([data_129f90a0]); call sub_E938D70`; `jmp sub_66d27e1` [V]. Then instance 32 preamble â€” yet another base register: `and rdx,0xFFFFFFFFFFFFFFFC` (len aligned to 4) [V]; `mov rcx,0xCBF29CE484222325` (FNV basis) [I]; `xor r8d,r8d` (index=0) [V]; `mov r9,0x100000001B3` (FNV prime) [I]; loc_66d7ac9: `movzx r10d,byte ptr [rsi+r8]` â€” base in rsi (set earlier in U-BA8 phase 7: `lea rsi,[rbp+0xA50]`) [V]; `xor r10,rcx` â€” instruction 41 at 0x66d7ace continues phase 14 [V]. All tags [V] except FNV basis/prime meaning [I] and callee/branch-target roles [?].

## Phase 14 â€” 0x66d7ace, 40 instructions [V]
```
0x66d7ace  xor r10,rcx
0x66d7ad1  imul r10,r9
0x66d7ad5  movzx ecx,byte ptr [rsi+r8+1]
0x66d7adb  xor rcx,r10
0x66d7ade  imul rcx,r9
0x66d7ae2  movzx r10d,byte ptr [rsi+r8+2]
0x66d7ae8  xor r10,rcx
0x66d7aeb  imul r10,r9
0x66d7aef  movzx ecx,byte ptr [rsi+r8+3]
0x66d7af5  xor rcx,r10
0x66d7af8  imul rcx,r9
0x66d7afc  add r8,4
0x66d7b00  cmp rdx,r8
0x66d7b03  jne short 0x66D7AC9
0x66d7b05  test rax,rax
0x66d7b08  je short 0x66D7B32
0x66d7b0a  add rsi,r8
0x66d7b0d  xor edx,edx
0x66d7b0f  mov r8,0x100000001B3
0x66d7b19  mov r9,rcx
0x66d7b1c  movzx ecx,byte ptr [rsi+rdx]
0x66d7b20  xor rcx,r9
0x66d7b23  imul rcx,r8
0x66d7b27  inc rdx
0x66d7b2a  mov r9,rcx
0x66d7b2d  cmp rax,rdx
0x66d7b30  jne short 0x66D7B1C
0x66d7b32  mov [0x129F8F68],rcx
0x66d7b39  lea rcx,[rbp+0xA50]
0x66d7b40  call 0x73150
0x66d7b45  lea rcx,[0x129F8F70]
0x66d7b4c  call 0xE938D70
0x66d7b51  jmp 0x66D38C0
0x66d7b56  mov rcx,0xCBF29CE484222325
0x66d7b60  jmp 0x66D7C0A
0x66d7b65  mov rcx,0xCBF29CE484222325
0x66d7b6f  jmp 0x66D7CBC
0x66d7b74  mov rcx,0xCBF29CE484222325
0x66d7b7e  jmp 0x66D7D67
0x66d7b83  and rdx,0xFFFFFFFFFFFFFFFC
0x66d7b87  mov rcx,0xCBF29CE484222325
```
// [V] Phase 14 finishes instance 32 (opened in phase 13; stores to [0x129F8F68]; branches to sub_66d38c0, role [?]): entered at `xor r10,rcx` with rcx=rolling hash, r9=prime, base rsi live-in. Loop tail `imul r10,r9; movzx ecx,byte ptr [rsi+r8+1]; xor rcx,r10; imul rcx,r9; movzx r10d,byte ptr [rsi+r8+2]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [rsi+r8+3]; xor rcx,r10; imul rcx,r9; add r8,4; cmp rdx,r8; jne short 0x66d7ac9` [V]. Exit `test rax,rax; je short 0x66d7b32` â€” rax==0 (empty) skips tail loop to store [V]. Tail setup: `add rsi,r8`; `xor edx,edx`; `mov r8,prime`; `mov r9,rcx` [V]. loc_66d7b1c tail loop: `movzx ecx,byte ptr [rsi+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; mov r9,rcx; cmp rax,rdx; jne short 0x66d7b1c` [V]. Store: `mov [0x129F8F68],rcx` ([data_129f8f68] hash result slot) [V]. Post-hash: `lea rcx,[rbp+0xA50]; call sub_73150`; `lea rcx,[0x129F8F70] ([data_129f8f70]); call sub_E938D70`; `jmp sub_66d38c0` [V]. Then three per-instance headers `mov rcx,0xCBF29CE484222325; jmp <loop target outside this phase>`: to 0x66d7c0a (instance 33) [V]; to 0x66d7cbc (instance 34) [V]; to 0x66d7d67 (instance 35 â€” note 0x66d7d67 < 0x66d7d8b unit end, still in range) [V]. Then instance 36 preamble: `and rdx,0xFFFFFFFFFFFFFFFC` (len aligned to 4) [V]; `mov rcx,0xCBF29CE484222325` (FNV basis) [I] â€” instruction 41 at 0x66d7b87 continues phase 15 [V]. All tags [V] except FNV basis meaning [I] and callee/branch-target roles [?].

## Phase 15 â€” 0x66d7b87, 40 instructions [V]
```
0x66d7b87  mov rcx,0xCBF29CE484222325
0x66d7b91  xor r8d,r8d
0x66d7b94  mov r9,0x100000001B3
0x66d7b9e  movzx r10d,byte ptr [r13+r8]
0x66d7ba4  xor r10,rcx
0x66d7ba7  imul r10,r9
0x66d7bab  movzx ecx,byte ptr [r13+r8+1]
0x66d7bb1  xor rcx,r10
0x66d7bb4  imul rcx,r9
0x66d7bb8  movzx r10d,byte ptr [r13+r8+2]
0x66d7bbe  xor r10,rcx
0x66d7bc1  imul r10,r9
0x66d7bc5  movzx ecx,byte ptr [r13+r8+3]
0x66d7bcb  xor rcx,r10
0x66d7bce  imul rcx,r9
0x66d7bd2  add r8,4
0x66d7bd6  cmp rdx,r8
0x66d7bd9  jne short 0x66D7B9E
0x66d7bdb  test rax,rax
0x66d7bde  je short 0x66D7C0A
0x66d7be0  add r13,r8
0x66d7be3  xor edx,edx
0x66d7be5  mov r8,0x100000001B3
0x66d7bef  mov r9,rcx
0x66d7bf2  movzx ecx,byte ptr [r13+rdx]
0x66d7bf8  xor rcx,r9
0x66d7bfb  imul rcx,r8
0x66d7bff  inc rdx
0x66d7c02  mov r9,rcx
0x66d7c05  cmp rax,rdx
0x66d7c08  jne short 0x66D7BF2
0x66d7c0a  mov [0x129F9008],rcx
0x66d7c11  lea rcx,[rbp+0xA50]
0x66d7c18  call 0x73150
0x66d7c1d  lea rcx,[0x129F9010]
0x66d7c24  call 0xE938D70
0x66d7c29  mov r15,[rbp+0xE20]
0x66d7c30  jmp 0x66D18CF
0x66d7c35  and rdx,0xFFFFFFFFFFFFFFFC
0x66d7c39  mov rcx,0xCBF29CE484222325
0x66d7c43  xor r8d,r8d
```
// [V] Phase 15 = instance 36 complete (stores to [0x129F9008]; variant post-hash tail `mov r15,[rbp+0xE20]; jmp sub_66d18cf`, role [?]): `mov rcx,0xCBF29CE484222325` (FNV basis) [I]; `xor r8d,r8d` (index=0) [V]; `mov r9,0x100000001B3` (FNV prime) [I]. loc_66d7b9e loop: `movzx r10d,byte ptr [r13+r8]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+1]; xor rcx,r10; imul rcx,r9; movzx r10d,byte ptr [r13+r8+2]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+3]; xor rcx,r10; imul rcx,r9; add r8,4; cmp rdx,r8; jne short 0x66d7b9e` [V]. Exit `test rax,rax; je short 0x66d7c0a` â€” rax==0 (empty) skips tail loop to store [V]. Tail setup: `add r13,r8`; `xor edx,edx`; `mov r8,prime`; `mov r9,rcx` [V]. loc_66d7bf2 tail loop: `movzx ecx,byte ptr [r13+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; mov r9,rcx; cmp rax,rdx; jne short 0x66d7bf2` [V]. Store: `mov [0x129F9008],rcx` ([data_129f9008] hash result slot) [V]. Post-hash: `lea rcx,[rbp+0xA50]; call sub_73150`; `lea rcx,[0x129F9010] ([data_129f9010]); call sub_E938D70`; `mov r15,[rbp+0xE20]`; `jmp sub_66d18cf` [V]. Then instance 37 preamble: `and rdx,0xFFFFFFFFFFFFFFFC` (len aligned to 4) [V]; `mov rcx,0xCBF29CE484222325` (FNV basis) [I]; `xor r8d,r8d` (index=0) â€” instruction 41 at 0x66d7c43 continues phase 16 [V]. All tags [V] except FNV basis/prime meaning [I] and callee/branch-target roles [?].

## Phase 16 â€” 0x66d7c43, 40 instructions [V]
```
0x66d7c43  xor r8d,r8d
0x66d7c46  mov r9,0x100000001B3
0x66d7c50  movzx r10d,byte ptr [r13+r8]
0x66d7c56  xor r10,rcx
0x66d7c59  imul r10,r9
0x66d7c5d  movzx ecx,byte ptr [r13+r8+1]
0x66d7c63  xor rcx,r10
0x66d7c66  imul rcx,r9
0x66d7c6a  movzx r10d,byte ptr [r13+r8+2]
0x66d7c70  xor r10,rcx
0x66d7c73  imul r10,r9
0x66d7c77  movzx ecx,byte ptr [r13+r8+3]
0x66d7c7d  xor rcx,r10
0x66d7c80  imul rcx,r9
0x66d7c84  add r8,4
0x66d7c88  cmp rdx,r8
0x66d7c8b  jne short 0x66D7C50
0x66d7c8d  test rax,rax
0x66d7c90  je short 0x66D7CBC
0x66d7c92  add r13,r8
0x66d7c95  xor edx,edx
0x66d7c97  mov r8,0x100000001B3
0x66d7ca1  mov r9,rcx
0x66d7ca4  movzx ecx,byte ptr [r13+rdx]
0x66d7caa  xor rcx,r9
0x66d7cad  imul rcx,r8
0x66d7cb1  inc rdx
0x66d7cb4  mov r9,rcx
0x66d7cb7  cmp rax,rdx
0x66d7cba  jne short 0x66D7CA4
0x66d7cbc  mov [0x129F9018],rcx
0x66d7cc3  lea rcx,[rbp+0xA50]
0x66d7cca  call 0x73150
0x66d7ccf  lea rcx,[0x129F9020]
0x66d7cd6  call 0xE938D70
0x66d7cdb  jmp 0x66D1B62
0x66d7ce0  and rdx,0xFFFFFFFFFFFFFFFC
0x66d7ce4  mov rcx,0xCBF29CE484222325
0x66d7cee  xor r8d,r8d
0x66d7cf1  mov r9,0x100000001B3
0x66d7cfb  movzx r10d,byte ptr [r13+r8]
```
// [V] Phase 16 = instance 37 complete (stores to [0x129F9018]; branches to sub_66d1b62, role [?]): `xor r8d,r8d` (index=0); `mov r9,0x100000001B3` (FNV prime) [I] with rcx=basis live-in from phase 15's preamble. loc_66d7c50 loop: `movzx r10d,byte ptr [r13+r8]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+1]; xor rcx,r10; imul rcx,r9; movzx r10d,byte ptr [r13+r8+2]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+3]; xor rcx,r10; imul rcx,r9; add r8,4; cmp rdx,r8; jne short 0x66d7c50` [V]. Exit `test rax,rax; je short 0x66d7cbc` â€” rax==0 (empty) skips tail loop to store [V]. Tail setup: `add r13,r8`; `xor edx,edx`; `mov r8,prime`; `mov r9,rcx` [V]. loc_66d7ca4 tail loop: `movzx ecx,byte ptr [r13+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; mov r9,rcx; cmp rax,rdx; jne short 0x66d7ca4` [V]. Store: `mov [0x129F9018],rcx` ([data_129f9018] hash result slot) [V]. Post-hash: `lea rcx,[rbp+0xA50]; call sub_73150`; `lea rcx,[0x129F9020] ([data_129f9020]); call sub_E938D70`; `jmp sub_66d1b62` [V]. Then instance 38 preamble + loop head: `and rdx,0xFFFFFFFFFFFFFFFC` (len aligned to 4) [V]; `mov rcx,0xCBF29CE484222325` (FNV basis) [I]; `xor r8d,r8d` (index=0) [V]; `mov r9,0x100000001B3` (FNV prime) [I]; loc_66d7cfb: `movzx r10d,byte ptr [r13+r8]` â€” instruction 41 at 0x66d7cfb continues phase 17 [V]. All tags [V] except FNV basis/prime meaning [I] and callee/branch-target roles [?].

## Phase 17 â€” 0x66d7cfb, 34 instructions [V] (LAST PHASE â€” unit end 0x66d7d8b exclusive)
```
0x66d7cfb  movzx r10d,byte ptr [r13+r8]
0x66d7d01  xor r10,rcx
0x66d7d04  imul r10,r9
0x66d7d08  movzx ecx,byte ptr [r13+r8+1]
0x66d7d0e  xor rcx,r10
0x66d7d11  imul rcx,r9
0x66d7d15  movzx r10d,byte ptr [r13+r8+2]
0x66d7d1b  xor r10,rcx
0x66d7d1e  imul r10,r9
0x66d7d22  movzx ecx,byte ptr [r13+r8+3]
0x66d7d28  xor rcx,r10
0x66d7d2b  imul rcx,r9
0x66d7d2f  add r8,4
0x66d7d33  cmp rdx,r8
0x66d7d36  jne short 0x66D7CFB
0x66d7d38  test rax,rax
0x66d7d3b  je short 0x66D7D67
0x66d7d3d  add r13,r8
0x66d7d40  xor edx,edx
0x66d7d42  mov r8,0x100000001B3
0x66d7d4c  mov r9,rcx
0x66d7d4f  movzx ecx,byte ptr [r13+rdx]
0x66d7d55  xor rcx,r9
0x66d7d58  imul rcx,r8
0x66d7d5c  inc rdx
0x66d7d5f  mov r9,rcx
0x66d7d62  cmp rax,rdx
0x66d7d65  jne short 0x66D7D4F
0x66d7d67  mov [0x129F9028],rcx
0x66d7d6e  lea rcx,[rbp+0xA50]
0x66d7d75  call 0x73150
0x66d7d7a  lea rcx,[0x129F9030]
0x66d7d81  call 0xE938D70
0x66d7d86  jmp 0x66D1C30
```
// [V] Phase 17 = instance 38 complete (stores to [0x129F9028]; branches to sub_66d1c30, role [?]) â€” the last hash instance before the function end at 0x66d7d8b: entered at `movzx r10d,byte ptr [r13+r8]` (index=0) with rcx=basis, r9=prime live-in from phase 16's preamble. loc_66d7cfb loop: `movzx r10d,byte ptr [r13+r8]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+1]; xor rcx,r10; imul rcx,r9; movzx r10d,byte ptr [r13+r8+2]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+3]; xor rcx,r10; imul rcx,r9; add r8,4; cmp rdx,r8; jne short 0x66d7cfb` [V]. Exit `test rax,rax; je short 0x66d7d67` â€” rax==0 (empty) skips tail loop to store [V]. Tail setup: `add r13,r8`; `xor edx,edx`; `mov r8,0x100000001B3` (FNV prime) [I meaning]; `mov r9,rcx` [V]. loc_66d7d4f tail loop: `movzx ecx,byte ptr [r13+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; mov r9,rcx; cmp rax,rdx; jne short 0x66d7d4f` [V]. Store: `mov [0x129F9028],rcx` ([data_129f9028] hash result slot) [V]. Post-hash: `lea rcx,[rbp+0xA50]; call sub_73150`; `lea rcx,[0x129F9030] ([data_129f9030]); call sub_E938D70`; `jmp sub_66d1c30` [V]. Unit end: the next instruction is at 0x66d7d8b `nop [rax+rax]` â€” rdis's function-end marker ("ret@e938d70+0x0+idx") exactly at the exclusive bound 0x66d7d8b, so it is NOT quoted per unit scope [V]. rdis instruction 41 would be 0x66d7d9c `push r12` >= 0x66d7d8b â†’ STOP: unit U-BA9 range 0x66d715d..0x66d7d8b fully covered [V]. All tags [V] except FNV prime meaning [I] and callee/branch-target roles [?].

## NEXT [done]
Unit U-BA9 complete: phases 1-17 (17/20 max) cover 0x66d715d..0x66d7d8b, the full unit range (function end exclusive). Next start 0x66d7d9c (instruction 41 of phase 17) >= 0x66d7d8b â†’ stop, per unit scope. Output file: docs/progress/oc_U-BA9.md (only file created/edited). No other files touched.
