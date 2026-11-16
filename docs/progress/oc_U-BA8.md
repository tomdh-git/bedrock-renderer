# Unit U-BA8 — bodyActor function 0x66d0a00 (1.26.62.01), continued from oc_U-BA7.md

## NEXT [current]
Next start RVA: 0x66d6562 (`xor r8d,r8d`, instruction 41 of U-BA7 phase 15 `dis 0x66d6486 41`, taken directly from rdis output via `dis 0x66d6552 4`).
Next call: `tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d6562 41`
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Static analysis only; game is closed.

## Phase 1 — 0x66d6562, 40 instructions [V]
```
0x66d6562  xor r8d,r8d
0x66d6565  jmp 0x66D7234
0x66d656a  lea rcx,[0x129F8FC0]
0x66d6571  call 0xE938CB0
0x66d6576  cmp dword ptr [0x129F8FC0],0xFFFFFFFF
0x66d657d  jne 0x66D1666
0x66d6583  lea rdx,[0xF56395E]
0x66d658a  lea r13,[rbp+0xA50]
0x66d6591  mov rcx,r13
0x66d6594  call 0x79580
0x66d6599  nop
0x66d659a  mov rdx,[rbp+0xA60]
0x66d65a1  cmp qword ptr [rbp+0xA68],0x10
0x66d65a9  jb short 0x66D65B2
0x66d65b2  test rdx,rdx
0x66d65b5  je 0x66D7282
0x66d65bb  mov eax,edx
0x66d65bd  and eax,3
0x66d65c0  cmp rdx,4
0x66d65c4  jae 0x66D72A6
0x66d65ca  mov rcx,0xCBF29CE484222325
0x66d65d4  xor r8d,r8d
0x66d65d7  jmp 0x66D7303
0x66d65dc  lea rcx,[0x129C13C0]
0x66d65e3  call 0xE938CB0
0x66d65e8  cmp dword ptr [0x129C13C0],0xFFFFFFFF
0x66d65ef  jne 0x66D262B
0x66d65f5  lea rcx,[0x4E05030]
0x66d65fc  call 0xE935740
0x66d6601  lea rcx,[0x129C13C0]
0x66d6608  call 0xE938D70
0x66d660d  jmp 0x66D262B
0x66d6612  lea rcx,[0x129C13C0]
0x66d6619  call 0xE938CB0
0x66d661e  cmp dword ptr [0x129C13C0],0xFFFFFFFF
0x66d6625  jne 0x66D277B
0x66d662b  lea rcx,[0x4E05030]
0x66d6632  call 0xE935740
0x66d6637  lea rcx,[0x129C13C0]
```
// [V] Phase 1 continues the post-`ret` cold uniform-lookup/hash series from U-BA7 phase 15 (not part of bodyActor live flow; seen in linear rdis walk) [I]. `xor r8d,r8d` (hash accumulator=0); `jmp 0x66d7234` (loc_66d7234, hash loop entry) [V]. `lea rcx,[0x129F8FC0] ([data_129f8fc0]); call sub_e938cb0; cmp dword ptr [0x129f8fc0],0xFFFFFFFF; jne 0x66d1666` — global-id init then branch out [V]. `lea rdx,[0xF56395E] ([data_f56395e] "MultiplicativeTintColor")` [V]; `lea r13,[rbp+0xA50]; mov rcx,r13; call sub_79580` (uniform lookup by name, ctx=&rbp+0xA50) [V] role [?]; `nop` [V]. `mov rdx,[rbp+0xA60] (data ptr); cmp qword ptr [rbp+0xA68],0x10 (size vs 16-byte threshold); jb short 0x66d65b2` (small path) [V]; loc_66d65b2: `test rdx,rdx; je 0x66d7282` (empty->exit) [V]; `mov eax,edx; and eax,3` (len mod 4) [V]; `cmp rdx,4; jae 0x66d72a6` (len>=4 -> long hash path) [V]; short path: `mov rcx,0xCBF29CE484222325` (FNV-1a 64-bit offset basis) [I]; `xor r8d,r8d` (hash accumulator=0); `jmp 0x66d7303` (hash loop entry) [V]. Not-taken cold block 0x66d65dc: `lea rcx,[0x129C13C0] ([data_129c13c0]); call sub_e938cb0; cmp dword ptr [0x129c13c0],0xFFFFFFFF; jne 0x66d262b` — global-id init then branch out [V]; `lea rcx,[0x4E05030] ([sub_4e05030]); call sub_e935740; lea rcx,[0x129c13c0]; call sub_e938d70; jmp 0x66d262b` [V]. Repeated pattern: `lea rcx,[0x129c13c0]; call sub_e938cb0; cmp dword ptr [0x129c13c0],0xFFFFFFFF; jne 0x66d277b` [V]; `lea rcx,[0x4e05030]; call sub_e935740; lea rcx,[0x129c13c0]` — instruction 41 `call 0xE938D70` at 0x66d663e continues phase 2 [V]. Fields touched: r8 W (hash accumulator), rdx/rax/rcx/r13 W chain [V]; [rbp+0xA60] R, [rbp+0xA68] R cmp, [rbp+0xA50] R->r13/rcx [V]. Roadata: [data_129f8fc0] R (ptr + dword cmp 0xFFFFFFFF), [data_f56395e] R ("MultiplicativeTintColor"), [data_129c13c0] R (ptr + dword cmp 0xFFFFFFFF) x3 [V]. Callees: sub_e938cb0 [V] x2 role [?], sub_79580 [V] role [?], sub_e935740 [V] x2 role [?], sub_e938d70 [V] x2 role [?], sub_66d1666/sub_66d262b/sub_66d277b [V] branch targets role [?].

## NEXT [current]
Next start RVA: 0x66d663e (`call 0xE938D70`, instruction 41 of phase 1, taken directly from rdis output).
Next call: `tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d663e 41`

## Phase 2 — 0x66d663e, 40 instructions [V]
```
0x66d663e  call 0xE938D70
0x66d6643  jmp 0x66D277B
0x66d6648  lea rcx,[0x129F90C0]
0x66d664f  call 0xE938CB0
0x66d6654  cmp dword ptr [0x129F90C0],0xFFFFFFFF
0x66d665b  jne 0x66D29A3
0x66d6661  lea rdx,[0xF7DE5C0]
0x66d6668  lea r13,[rbp+0xA50]
0x66d666f  mov rcx,r13
0x66d6672  call 0x79580
0x66d6677  nop
0x66d6678  mov rdx,[rbp+0xA60]
0x66d667f  cmp qword ptr [rbp+0xA68],0x10
0x66d6687  jb short 0x66D6690
0x66d6690  test rdx,rdx
0x66d6693  je 0x66D7291
0x66d6699  mov eax,edx
0x66d669b  and eax,3
0x66d669e  cmp rdx,4
0x66d66a2  jae 0x66D7351
0x66d66a8  mov rcx,0xCBF29CE484222325
0x66d66b2  xor r8d,r8d
0x66d66b5  jmp 0x66D73AE
0x66d66ba  lea rcx,[0x129F8FA0]
0x66d66c1  call 0xE938CB0
0x66d66c6  cmp dword ptr [0x129F8FA0],0xFFFFFFFF
0x66d66cd  jne 0x66D14B0
0x66d66d3  lea rdx,[0xF5DE988]
0x66d66da  lea r13,[rbp+0xA50]
0x66d66e1  mov rcx,r13
0x66d66e4  call 0x79580
0x66d66e9  nop
0x66d66ea  mov rdx,[rbp+0xA60]
0x66d66f1  cmp qword ptr [rbp+0xA68],0x10
0x66d66f9  jb short 0x66D6702
0x66d6702  test rdx,rdx
0x66d6705  je 0x66D7403
0x66d670b  mov eax,edx
```
// [V] Phase 2 continues the cold uniform-lookup series (not part of bodyActor live flow; seen in linear rdis walk) [I]. `call sub_e938d70` (completes phase-1 repeated pattern); `jmp 0x66d277b` (branch out) [V]. `lea rcx,[0x129F90C0] ([data_129f90c0]); call sub_e938cb0; cmp dword ptr [0x129f90c0],0xFFFFFFFF; jne 0x66d29a3` — global-id init then branch out [V]. `lea rdx,[0xF7DE5C0] ([data_f7de5c0] "MatTexture1")` [V]; `lea r13,[rbp+0xA50]; mov rcx,r13; call sub_79580` (uniform lookup by name, ctx=&rbp+0xA50) [V] role [?]; `nop` [V]; `mov rdx,[rbp+0xA60] (data ptr); cmp qword ptr [rbp+0xA68],0x10 (size vs 16-byte threshold); jb short 0x66d6690` (small path) [V]; loc_66d6690: `test rdx,rdx; je 0x66d7291` (empty->exit) [V]; `mov eax,edx; and eax,3` (len mod 4) [V]; `cmp rdx,4; jae 0x66d7351` (len>=4 -> long hash path) [V]; short path: `mov rcx,0xCBF29CE484222325` (FNV-1a 64-bit offset basis) [I]; `xor r8d,r8d` (hash accumulator=0); `jmp 0x66d73ae` (hash loop entry) [V]. Not-taken cold block 0x66d66ba: `lea rcx,[0x129F8FA0] ([data_129f8fa0]); call sub_e938cb0; cmp dword ptr [0x129f8fa0],0xFFFFFFFF; jne 0x66d14b0` — global-id init then branch out [V]. `lea rdx,[0xF5DE988] ([data_f5de988] "UVScale")` [V]; `lea r13,[rbp+0xA50]; mov rcx,r13; call sub_79580` [V] role [?]; `nop` [V]; `mov rdx,[rbp+0xA60]; cmp qword ptr [rbp+0xA68],0x10; jb short 0x66d6702` [V]; loc_66d6702: `test rdx,rdx; je 0x66d7403` [V]; `mov eax,edx; and eax,3` — instruction 41 at 0x66d670d continues phase 3 [V]. Fields touched: rdx/rax/rcx/r13 W chain [V]; [rbp+0xA60] R, [rbp+0xA68] R cmp, [rbp+0xA50] R->r13/rcx [V]. Roadata: [data_129f90c0] R (ptr + dword cmp 0xFFFFFFFF), [data_f7de5c0] R ("MatTexture1"), [data_129f8fa0] R (ptr + dword cmp 0xFFFFFFFF), [data_f5de988] R ("UVScale") [V]. Callees: sub_e938d70 [V] role [?], sub_66d277b [V] branch target role [?], sub_e938cb0 [V] x2 role [?], sub_79580 [V] x2 role [?], sub_66d29a3/sub_66d14b0 [V] branch targets role [?].

## NEXT [current]
Next start RVA: 0x66d670d (`and eax,3`, instruction 41 of phase 2, taken directly from rdis output).
Next call: `tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d670d 41`

## Phase 3 — 0x66d670d, 40 instructions [V]
```
0x66d670d  and eax,3
0x66d6710  cmp rdx,4
0x66d6714  jae 0x66D746C
0x66d671a  mov rcx,0xCBF29CE484222325
0x66d6724  xor r8d,r8d
0x66d6727  jmp 0x66D74C9
0x66d672c  lea rcx,[0x129F8FB0]
0x66d6733  call 0xE938CB0
0x66d6738  cmp dword ptr [0x129F8FB0],0xFFFFFFFF
0x66d673f  jne 0x66D14D5
0x66d6745  lea rdx,[0xF563953]
0x66d674c  lea r13,[rbp+0xA50]
0x66d6753  mov rcx,r13
0x66d6756  call 0x79580
0x66d675b  nop
0x66d675c  mov r8,[rbp+0xA60]
0x66d6763  cmp qword ptr [rbp+0xA68],0x10
0x66d676b  jb short 0x66D6774
0x66d6774  test r8,r8
0x66d6777  je 0x66D7412
0x66d677d  mov eax,r8d
0x66d6780  and eax,3
0x66d6783  mov rcx,0x100000001B3
0x66d678d  cmp r8,4
0x66d6791  jae 0x66D7517
0x66d6797  mov rdx,0xCBF29CE484222325
0x66d67a1  xor r9d,r9d
0x66d67a4  jmp 0x66D756A
0x66d67a9  lea rcx,[0x129F8FD0]
0x66d67b0  call 0xE938CB0
0x66d67b5  cmp dword ptr [0x129F8FD0],0xFFFFFFFF
0x66d67bc  jne 0x66D174A
0x66d67c2  lea rdx,[0xF5C0654]
0x66d67c9  lea r13,[rbp+0xA50]
0x66d67d0  mov rcx,r13
0x66d67d3  call 0x79580
0x66d67d8  nop
0x66d67d9  mov rdx,[rbp+0xA60]
0x66d67e0  cmp qword ptr [rbp+0xA68],0x10
```
// [V] Phase 3 continues the cold uniform-lookup series (not part of bodyActor live flow; seen in linear rdis walk) [I]. `and eax,3` (len mod 4, from phase-2 tail); `cmp rdx,4; jae 0x66d746c` (len>=4 -> long hash path) [V]; short path: `mov rcx,0xCBF29CE484222325` (FNV-1a basis) [I]; `xor r8d,r8d`; `jmp 0x66d74c9` (hash loop entry) [V]. Not-taken cold block 0x66d672c: `lea rcx,[0x129F8FB0] ([data_129f8fb0]); call sub_e938cb0; cmp dword ptr [0x129f8fb0],0xFFFFFFFF; jne 0x66d14d5` — global-id init then branch out [V]. `lea rdx,[0xF563953] ([data_f563953] "GlintColor")` [V]; `lea r13,[rbp+0xA50]; mov rcx,r13; call sub_79580` (uniform lookup by name, ctx=&rbp+0xA50) [V] role [?]; `nop` [V]; `mov r8,[rbp+0xA60] (data ptr); cmp qword ptr [rbp+0xA68],0x10 (size vs 16-byte threshold); jb short 0x66d6774` (small path) [V]; loc_66d6774: `test r8,r8; je 0x66d7412` (empty->exit) [V]; `mov eax,r8d; and eax,3` (len mod 4) [V]; `mov rcx,0x100000001B3` (64-bit immediate) [V]; `cmp r8,4; jae 0x66d7517` (len>=4 -> long hash path) [V]; short path: `mov rdx,0xCBF29CE484222325` (FNV-1a basis) [I]; `xor r9d,r9d` (hash accumulator=0); `jmp 0x66d756a` (hash loop entry) [V]. Not-taken cold block 0x66d67a9: `lea rcx,[0x129F8FD0] ([data_129f8fd0]); call sub_e938cb0; cmp dword ptr [0x129f8fd0],0xFFFFFFFF; jne 0x66d174a` — global-id init then branch out [V]. `lea rdx,[0xF5C0654] ([data_f5c0654] "UseAlphaRewrite")` [V]; `lea r13,[rbp+0xA50]; mov rcx,r13; call sub_79580` [V] role [?]; `nop` [V]; `mov rdx,[rbp+0xA60]; cmp qword ptr [rbp+0xA68],0x10` [V]; `jb short 0x66d67f1` — instruction 41 at 0x66d67e8 continues phase 4 [V]. Fields touched: eax/r8/rdx/rcx/r9 W chain [V]; [rbp+0xA60] R x2, [rbp+0xA68] R cmp x2, [rbp+0xA50] R->r13/rcx x2 [V]. Roadata: [data_129f8fb0] R (ptr + dword cmp 0xFFFFFFFF), [data_f563953] R ("GlintColor"), [data_129f8fd0] R (ptr + dword cmp 0xFFFFFFFF), [data_f5c0654] R ("UseAlphaRewrite") [V]. Callees: sub_e938cb0 [V] x2 role [?], sub_79580 [V] x2 role [?], sub_66d14d5/sub_66d174a [V] branch targets role [?].

## NEXT [current]
Next start RVA: 0x66d67e8 (`jb short 0x66D67F1`, instruction 41 of phase 3, taken directly from rdis output).
Next call: `tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d67e8 41`

## Phase 4 — 0x66d67e8, 40 instructions [V]
```
0x66d67e8  jb short 0x66D67F1
0x66d67ea  mov r13,[rbp+0xA50]
0x66d67f1  test rdx,rdx
0x66d67f4  je 0x66D7421
0x66d67fa  mov eax,edx
0x66d67fc  and eax,3
0x66d67ff  cmp rdx,4
0x66d6803  jae 0x66D75AF
0x66d6809  mov rcx,0xCBF29CE484222325
0x66d6813  xor r8d,r8d
0x66d6816  jmp 0x66D760C
0x66d681b  lea rcx,[0x129F8FE0]
0x66d6822  call 0xE938CB0
0x66d6827  cmp dword ptr [0x129F8FE0],0xFFFFFFFF
0x66d682e  jne 0x66D1833
0x66d6834  lea rdx,[0xF549ED0]
0x66d683b  lea r13,[rbp+0xA50]
0x66d6842  mov rcx,r13
0x66d6845  call 0x79580
0x66d684a  nop
0x66d684b  mov rdx,[rbp+0xA60]
0x66d6852  cmp qword ptr [rbp+0xA68],0x10
0x66d685a  jb short 0x66D6863
0x66d6863  test rdx,rdx
0x66d6866  je 0x66D7430
0x66d686c  mov eax,edx
0x66d686e  and eax,3
0x66d6871  cmp rdx,4
0x66d6875  jae 0x66D765A
0x66d687b  mov rcx,0xCBF29CE484222325
0x66d6885  xor r8d,r8d
0x66d6888  jmp 0x66D76B7
0x66d688d  lea rcx,[0x129F8FF0]
0x66d6894  call 0xE938CB0
0x66d6899  cmp dword ptr [0x129F8FF0],0xFFFFFFFF
0x66d68a0  jne 0x66D1997
0x66d68a6  lea rdx,[0xF558FB1]
0x66d68ad  lea r13,[rbp+0xA50]
```
// [V] Phase 4 continues the cold uniform-lookup series (not part of bodyActor live flow; seen in linear rdis walk) [I]. `jb short 0x66d67f1` (from phase-3 `cmp qword ptr [rbp+0xA68],0x10` small-path branch); `mov r13,[rbp+0xA50]` [V]; loc_66d67f1: `test rdx,rdx; je 0x66d7421` (empty->exit) [V]; `mov eax,edx; and eax,3` (len mod 4) [V]; `cmp rdx,4; jae 0x66d75af` (len>=4 -> long hash path) [V]; short path: `mov rcx,0xCBF29CE484222325` (FNV-1a basis) [I]; `xor r8d,r8d`; `jmp 0x66d760c` (hash loop entry) [V]. Not-taken cold block 0x66d681b: `lea rcx,[0x129F8FE0] ([data_129f8fe0]); call sub_e938cb0; cmp dword ptr [0x129f8fe0],0xFFFFFFFF; jne 0x66d1833` — global-id init then branch out [V]. `lea rdx,[0xF549ED0] ([data_f549ed0] "BannerColors")` [V]; `lea r13,[rbp+0xA50]; mov rcx,r13; call sub_79580` (uniform lookup by name, ctx=&rbp+0xA50) [V] role [?]; `nop` [V]; `mov rdx,[rbp+0xA60]; cmp qword ptr [rbp+0xA68],0x10; jb short 0x66d6863` [V]; loc_66d6863: `test rdx,rdx; je 0x66d7430` [V]; `mov eax,edx; and eax,3` (len mod 4) [V]; `cmp rdx,4; jae 0x66d765a` [V]; short path: `mov rcx,0xCBF29CE484222325`; `xor r8d,r8d`; `jmp 0x66d76b7` (hash loop entry) [V]. Not-taken cold block 0x66d688d: `lea rcx,[0x129F8FF0] ([data_129f8ff0]); call sub_e938cb0; cmp dword ptr [0x129f8ff0],0xFFFFFFFF; jne 0x66d1997` — global-id init then branch out [V]. `lea rdx,[0xF558FB1] ([data_f558fb1] "BannerUVOffsetsAndScales")` [V]; `lea r13,[rbp+0xA50]; mov rcx,r13` — instruction 41 `call 0x79580` at 0x66d68b7 continues phase 5 [V]. Fields touched: rdx/rax/rcx/r8/r13 W chain [V]; [rbp+0xA60] R x2, [rbp+0xA68] R cmp x2, [rbp+0xA50] R->r13/rcx x2 [V]. Roadata: [data_129f8fe0] R (ptr + dword cmp 0xFFFFFFFF), [data_f549ed0] R ("BannerColors"), [data_129f8ff0] R (ptr + dword cmp 0xFFFFFFFF), [data_f558fb1] R ("BannerUVOffsetsAndScales") [V]. Callees: sub_e938cb0 [V] x2 role [?], sub_79580 [V] role [?] (1 of 2), sub_66d1833/sub_66d1997 [V] branch targets role [?].

## NEXT [current]
Next start RVA: 0x66d68b7 (`call 0x79580`, instruction 41 of phase 4, taken directly from rdis output).
Next call: `tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d68b7 41`

## Phase 5 — 0x66d68b7, 40 instructions [V]
```
0x66d68b7  call 0x79580
0x66d68bc  nop
0x66d68bd  mov rdx,[rbp+0xA60]
0x66d68c4  cmp qword ptr [rbp+0xA68],0x10
0x66d68cc  jb short 0x66D68D5
0x66d68d5  test rdx,rdx
0x66d68d8  je 0x66D743F
0x66d68de  mov eax,edx
0x66d68e0  and eax,3
0x66d68e3  cmp rdx,4
0x66d68e7  jae 0x66D770C
0x66d68ed  mov rcx,0xCBF29CE484222325
0x66d68f7  xor r8d,r8d
0x66d68fa  jmp 0x66D7769
0x66d68ff  lea rcx,[0x129F90D0]
0x66d6906  call 0xE938CB0
0x66d690b  cmp dword ptr [0x129F90D0],0xFFFFFFFF
0x66d6912  jne 0x66D2AC3
0x66d6918  lea rdx,[0xF7DA300]
0x66d691f  lea r13,[rbp+0xA50]
0x66d6926  mov rcx,r13
0x66d6929  call 0x79580
0x66d692e  nop
0x66d692f  mov rdx,[rbp+0xA60]
0x66d6936  cmp qword ptr [rbp+0xA68],0x10
0x66d693e  jb short 0x66D6947
0x66d6947  test rdx,rdx
0x66d694a  je 0x66D744E
0x66d6950  mov eax,edx
0x66d6952  and eax,3
0x66d6955  cmp rdx,4
0x66d6959  jae 0x66D77B7
0x66d695f  mov rcx,0xCBF29CE484222325
0x66d6969  xor r8d,r8d
0x66d696c  jmp 0x66D7814
0x66d6971  lea rcx,[0x129F9000]
0x66d6978  call 0xE938CB0
0x66d697d  cmp dword ptr [0x129F9000],0xFFFFFFFF
```
// [V] Phase 5 continues the cold uniform-lookup series (not part of bodyActor live flow; seen in linear rdis walk) [I]. `call sub_79580` (rcx=&rbp+0xA50, uniform lookup by name — completes phase-4 "BannerUVOffsetsAndScales" lookup) [V] role [?]; `nop` [V]; `mov rdx,[rbp+0xA60]; cmp qword ptr [rbp+0xA68],0x10; jb short 0x66d68d5` [V]; loc_66d68d5: `test rdx,rdx; je 0x66d743f` (empty->exit) [V]; `mov eax,edx; and eax,3` (len mod 4) [V]; `cmp rdx,4; jae 0x66d770c` (len>=4 -> long hash path) [V]; short path: `mov rcx,0xCBF29CE484222325` (FNV-1a basis) [I]; `xor r8d,r8d`; `jmp 0x66d7769` (hash loop entry) [V]. Not-taken cold block 0x66d68ff: `lea rcx,[0x129F90D0] ([data_129f90d0]); call sub_e938cb0; cmp dword ptr [0x129f90d0],0xFFFFFFFF; jne 0x66d2ac3` — global-id init then branch out [V]. `lea rdx,[0xF7DA300] ([data_f7da300] "MatTexture2")` [V]; `lea r13,[rbp+0xA50]; mov rcx,r13; call sub_79580` [V] role [?]; `nop` [V]; `mov rdx,[rbp+0xA60]; cmp qword ptr [rbp+0xA68],0x10; jb short 0x66d6947` [V]; loc_66d6947: `test rdx,rdx; je 0x66d744e` [V]; `mov eax,edx; and eax,3` (len mod 4) [V]; `cmp rdx,4; jae 0x66d77b7` [V]; short path: `mov rcx,0xCBF29CE484222325`; `xor r8d,r8d`; `jmp 0x66d7814` (hash loop entry) [V]. Not-taken cold block 0x66d6971: `lea rcx,[0x129F9000] ([data_129f9000]); call sub_e938cb0; cmp dword ptr [0x129f9000],0xFFFFFFFF; jne 0x66d1a60` — instruction 41 at 0x66d6984 continues phase 6 [V]. Fields touched: rdx/rax/rcx/r8/r13 W chain [V]; [rbp+0xA60] R x2, [rbp+0xA68] R cmp x2, [rbp+0xA50] R->r13/rcx x2 [V]. Roadata: [data_129f90d0] R (ptr + dword cmp 0xFFFFFFFF), [data_f7da300] R ("MatTexture2"), [data_129f9000] R (ptr + dword cmp 0xFFFFFFFF) [V]. Callees: sub_79580 [V] x2 role [?], sub_e938cb0 [V] x2 role [?], sub_66d2ac3/sub_66d1a60 [V] branch targets role [?].

## NEXT [current]
Next start RVA: 0x66d6984 (`jne 0x66D1A60`, instruction 41 of phase 5, taken directly from rdis output).
Next call: `tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d6984 41`

## Phase 6 — 0x66d6984, 40 instructions [V]
```
0x66d6984  jne 0x66D1A60
0x66d698a  lea rdx,[0xF60CB9D]
0x66d6991  lea r13,[rbp+0xA50]
0x66d6998  mov rcx,r13
0x66d699b  call 0x79580
0x66d69a0  nop
0x66d69a1  mov rdx,[rbp+0xA60]
0x66d69a8  cmp qword ptr [rbp+0xA68],0x10
0x66d69b0  jb short 0x66D69B9
0x66d69b9  test rdx,rdx
0x66d69bc  je 0x66D745D
0x66d69c2  mov eax,edx
0x66d69c4  and eax,3
0x66d69c7  cmp rdx,4
0x66d69cb  jae 0x66D7862
0x66d69d1  mov rcx,0xCBF29CE484222325
0x66d69db  xor r8d,r8d
0x66d69de  jmp 0x66D78BF
0x66d69e3  lea rcx,[0x129F9090]
0x66d69ea  call 0xE938CB0
0x66d69ef  cmp dword ptr [0x129F9090],0xFFFFFFFF
0x66d69f6  jne 0x66D267B
0x66d69fc  lea rdx,[0xF5C6EEE]
0x66d6a03  lea rcx,[rbp+0xA50]
0x66d6a0a  mov [rbp+0x7D8],rcx
0x66d6a11  call 0x79580
0x66d6a16  nop
0x66d6a17  mov rdx,[rbp+0xA60]
0x66d6a1e  cmp qword ptr [rbp+0xA68],0x10
0x66d6a26  jb short 0x66D6A36
0x66d6a36  test rdx,rdx
0x66d6a39  je 0x66D790D
0x66d6a3f  mov eax,edx
0x66d6a41  and eax,3
0x66d6a44  cmp rdx,4
0x66d6a48  jae 0x66D793A
0x66d6a4e  mov rcx,0xCBF29CE484222325
0x66d6a58  xor r8d,r8d
0x66d6a5b  jmp 0x66D799D
0x66d6a60  lea rcx,[0x129F90A0]
```
// [V] Phase 6 continues the cold uniform-lookup series (not part of bodyActor live flow; seen in linear rdis walk) [I]. `jne 0x66d1a60` (from phase-5 `cmp dword ptr [0x129f9000],0xFFFFFFFF`, branch out) [V]. `lea rdx,[0xF60CB9D] ([data_f60cb9d] "BannerBasePBRTextureData")` [V]; `lea r13,[rbp+0xA50]; mov rcx,r13; call sub_79580` (uniform lookup by name, ctx=&rbp+0xA50) [V] role [?]; `nop` [V]; `mov rdx,[rbp+0xA60]; cmp qword ptr [rbp+0xA68],0x10; jb short 0x66d69b9` [V]; loc_66d69b9: `test rdx,rdx; je 0x66d745d` (empty->exit) [V]; `mov eax,edx; and eax,3` (len mod 4) [V]; `cmp rdx,4; jae 0x66d7862` (len>=4 -> long hash path) [V]; short path: `mov rcx,0xCBF29CE484222325` (FNV-1a basis) [I]; `xor r8d,r8d`; `jmp 0x66d78bf` (hash loop entry) [V]. Not-taken cold block 0x66d69e3: `lea rcx,[0x129F9090] ([data_129f9090]); call sub_e938cb0; cmp dword ptr [0x129f9090],0xFFFFFFFF; jne 0x66d267b` — global-id init then branch out [V]. `lea rdx,[0xF5C6EEE] ([data_f5c6eee] "MERSTexture")` [V]; `lea rcx,[rbp+0xA50]; mov [rbp+0x7D8],rcx` (out-arg slot) [V]; `call sub_79580` [V] role [?]; `nop` [V]; `mov rdx,[rbp+0xA60]; cmp qword ptr [rbp+0xA68],0x10; jb short 0x66d6a36` [V]; loc_66d6a36: `test rdx,rdx; je 0x66d790d` [V]; `mov eax,edx; and eax,3` (len mod 4) [V]; `cmp rdx,4; jae 0x66d793a` [V]; short path: `mov rcx,0xCBF29CE484222325`; `xor r8d,r8d` [V]; `jmp 0x66d799d` (hash loop entry) [V]; `lea rcx,[0x129F90A0] ([data_129f90a0])` [V] — instruction 41 `call 0xE938CB0` at 0x66d6a67 continues phase 7 [V]. Fields touched: rdx/rax/rcx/r8/r13 W chain [V]; [rbp+0x7D8] W (ctx ptr slot), [rbp+0xA60] R x2, [rbp+0xA68] R cmp x2, [rbp+0xA50] R->rcx x2 [V]. Roadata: [data_f60cb9d] R ("BannerBasePBRTextureData"), [data_129f9090] R (ptr + dword cmp 0xFFFFFFFF), [data_f5c6eee] R ("MERSTexture"), [data_129f90a0] R (ptr) [V]. Callees: sub_79580 [V] x2 role [?], sub_e938cb0 [V] role [?], sub_66d1a60/sub_66d267b [V] branch targets role [?].

## NEXT [current]
Next start RVA: 0x66d6a67 (`call 0xE938CB0`, instruction 41 of phase 6, taken directly from rdis output).
Next call: `tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d6a67 41`

## Phase 7 — 0x66d6a67, 40 instructions [V]
```
0x66d6a67  call 0xE938CB0
0x66d6a6c  cmp dword ptr [0x129F90A0],0xFFFFFFFF
0x66d6a73  jne 0x66D27E1
0x66d6a79  lea rdx,[0xF5C6DAA]
0x66d6a80  lea rcx,[rbp+0xA50]
0x66d6a87  mov [rbp+0xD80],rcx
0x66d6a8e  call 0x79580
0x66d6a93  nop
0x66d6a94  mov rdx,[rbp+0xA60]
0x66d6a9b  cmp qword ptr [rbp+0xA68],0x10
0x66d6aa3  jb short 0x66D6AB3
0x66d6ab3  test rdx,rdx
0x66d6ab6  je 0x66D791C
0x66d6abc  mov eax,edx
0x66d6abe  and eax,3
0x66d6ac1  cmp rdx,4
0x66d6ac5  jae 0x66D79F4
0x66d6acb  mov rcx,0xCBF29CE484222325
0x66d6ad5  xor r8d,r8d
0x66d6ad8  jmp 0x66D7A57
0x66d6add  lea rcx,[0x129F8F70]
0x66d6ae4  call 0xE938CB0
0x66d6ae9  cmp dword ptr [0x129F8F70],0xFFFFFFFF
0x66d6af0  jne 0x66D38C0
0x66d6af6  lea rdx,[0xF5C0654]
0x66d6afd  lea rsi,[rbp+0xA50]
0x66d6b04  mov rcx,rsi
0x66d6b07  call 0x79580
0x66d6b0c  nop
0x66d6b0d  mov rdx,[rbp+0xA60]
0x66d6b14  cmp qword ptr [rbp+0xA68],0x10
0x66d6b1c  jb short 0x66D6B25
0x66d6b25  test rdx,rdx
0x66d6b28  je 0x66D792B
0x66d6b2e  mov eax,edx
0x66d6b30  and eax,3
0x66d6b33  cmp rdx,4
0x66d6b37  jae 0x66D7AAE
0x66d6b3d  mov rcx,0xCBF29CE484222325
0x66d6b47  xor r8d,r8d
```
// [V] Phase 7 continues the cold uniform-lookup series (not part of bodyActor live flow; seen in linear rdis walk) [I]. `call sub_e938cb0` (completes phase-6 "MERSTexture" lookup); `cmp dword ptr [0x129f90a0],0xFFFFFFFF; jne 0x66d27e1` — global-id check then branch out [V]. `lea rdx,[0xF5C6DAA] ([data_f5c6daa] "NormalTexture")` [V]; `lea rcx,[rbp+0xA50]; mov [rbp+0xD80],rcx` (out-arg slot) [V]; `call sub_79580` (uniform lookup by name, ctx=&rbp+0xA50) [V] role [?]; `nop` [V]; `mov rdx,[rbp+0xA60]; cmp qword ptr [rbp+0xA68],0x10; jb short 0x66d6ab3` [V]; loc_66d6ab3: `test rdx,rdx; je 0x66d791c` (empty->exit) [V]; `mov eax,edx; and eax,3` (len mod 4) [V]; `cmp rdx,4; jae 0x66d79f4` (len>=4 -> long hash path) [V]; short path: `mov rcx,0xCBF29CE484222325` (FNV-1a basis) [I]; `xor r8d,r8d`; `jmp 0x66d7a57` (hash loop entry) [V]. Not-taken cold block 0x66d6add: `lea rcx,[0x129F8F70] ([data_129f8f70]); call sub_e938cb0; cmp dword ptr [0x129f8f70],0xFFFFFFFF; jne 0x66d38c0` — global-id init then branch out [V]. `lea rdx,[0xF5C0654] ([data_f5c0654] "UseAlphaRewrite", repeat name) ` [V]; `lea rsi,[rbp+0xA50]; mov rcx,rsi; call sub_79580` [V] role [?]; `nop` [V]; `mov rdx,[rbp+0xA60]; cmp qword ptr [rbp+0xA68],0x10; jb short 0x66d6b25` [V]; loc_66d6b25: `test rdx,rdx; je 0x66d792b` [V]; `mov eax,edx; and eax,3` (len mod 4) [V]; `cmp rdx,4; jae 0x66d7aae` [V]; short path continues: `mov rcx,0xCBF29CE484222325` (instr 39); `xor r8d,r8d` (instr 40) — instruction 41 `jmp 0x66d7b0a` at 0x66d6b4a continues phase 8 [V]. Fields touched: rdx/rax/rcx/r8/rsi W chain [V]; [rbp+0xD80] W (ctx ptr slot), [rbp+0xA60] R x2, [rbp+0xA68] R cmp x2, [rbp+0xA50] R->rcx/rsi x2 [V]. Roadata: [data_129f90a0] R (dword cmp 0xFFFFFFFF), [data_f5c6daa] R ("NormalTexture"), [data_129f8f70] R (ptr + dword cmp 0xFFFFFFFF), [data_f5c0654] R ("UseAlphaRewrite") [V]. Callees: sub_e938cb0 [V] x2 role [?], sub_79580 [V] x2 role [?], sub_66d27e1/sub_66d38c0 [V] branch targets role [?].

## NEXT [current]
Next start RVA: 0x66d6b4a (`jmp 0x66D7B0A`, instruction 41 of phase 7, taken directly from rdis output).
Next call: `tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d6b4a 41`

## Phase 8 — 0x66d6b4a, 40 instructions [V]
```
0x66d6b4a  jmp 0x66D7B0A
0x66d6b4f  lea rcx,[0x129F9010]
0x66d6b56  call 0xE938CB0
0x66d6b5b  cmp dword ptr [0x129F9010],0xFFFFFFFF
0x66d6b62  jne 0x66D18CF
0x66d6b68  lea rdx,[0xF549EDD]
0x66d6b6f  lea r13,[rbp+0xA50]
0x66d6b76  mov rcx,r13
0x66d6b79  call 0x79580
0x66d6b7e  nop
0x66d6b7f  mov rdx,[rbp+0xA60]
0x66d6b86  cmp qword ptr [rbp+0xA68],0x10
0x66d6b8e  jb short 0x66D6B97
0x66d6b97  test rdx,rdx
0x66d6b9a  je 0x66D7B56
0x66d6ba0  mov eax,edx
0x66d6ba2  and eax,3
0x66d6ba5  cmp rdx,4
0x66d6ba9  jae 0x66D7B83
0x66d6baf  mov rcx,0xCBF29CE484222325
0x66d6bb9  xor r8d,r8d
0x66d6bbc  jmp 0x66D7BE0
0x66d6bc1  lea rcx,[0x129F9020]
0x66d6bc8  call 0xE938CB0
0x66d6bcd  cmp dword ptr [0x129F9020],0xFFFFFFFF
0x66d6bd4  jne 0x66D1B62
0x66d6bda  lea rdx,[0xF558FCA]
0x66d6be1  lea r13,[rbp+0xA50]
0x66d6be8  mov rcx,r13
0x66d6beb  call 0x79580
0x66d6bf0  nop
0x66d6bf1  mov rdx,[rbp+0xA60]
0x66d6bf8  cmp qword ptr [rbp+0xA68],0x10
0x66d6c00  jb short 0x66D6C09
0x66d6c09  test rdx,rdx
0x66d6c0c  je 0x66D7B65
0x66d6c12  mov eax,edx
0x66d6c14  and eax,3
0x66d6c17  cmp rdx,4
0x66d6c1b  jae 0x66D7C35
```
// [V] Phase 8 continues the cold uniform-lookup series (not part of bodyActor live flow; seen in linear rdis walk) [I]. `jmp 0x66d7b0a` (phase-7 instruction-41 target, hash loop entry) [V]. `lea rcx,[0x129F9010] ([data_129f9010]); call sub_e938cb0; cmp dword ptr [0x129f9010],0xFFFFFFFF; jne 0x66d18cf` — global-id init then branch out [V]. `lea rdx,[0xF549EDD] ([data_f549edd] "PatternColors")` [V]; `lea r13,[rbp+0xA50]; mov rcx,r13; call sub_79580` (uniform lookup by name, ctx=&rbp+0xA50) [V] role [?]; `nop` [V]; `mov rdx,[rbp+0xA60]; cmp qword ptr [rbp+0xA68],0x10; jb short 0x66d6b97` [V]; loc_66d6b97: `test rdx,rdx; je 0x66d7b56` (empty->exit) [V]; `mov eax,edx; and eax,3` (len mod 4) [V]; `cmp rdx,4; jae 0x66d7b83` (len>=4 -> long hash path) [V]; short path: `mov rcx,0xCBF29CE484222325` (FNV-1a basis) [I]; `xor r8d,r8d`; `jmp 0x66d7be0` (hash loop entry) [V]. Not-taken cold block 0x66d6bc1: `lea rcx,[0x129F9020] ([data_129f9020]); call sub_e938cb0; cmp dword ptr [0x129f9020],0xFFFFFFFF; jne 0x66d1b62` — global-id init then branch out [V]. `lea rdx,[0xF558FCA] ([data_f558fca] "PatternUVOffsetsAndScales")` [V]; `lea r13,[rbp+0xA50]; mov rcx,r13; call sub_79580` [V] role [?]; `nop` [V]; `mov rdx,[rbp+0xA60]; cmp qword ptr [rbp+0xA68],0x10; jb short 0x66d6c09` [V]; loc_66d6c09: `test rdx,rdx; je 0x66d7b65` [V]; `mov eax,edx; and eax,3` (instr 38) [V]; `cmp rdx,4` (instr 39) [V]; `jae 0x66d7c35` (instr 40) [V] — instruction 41 `mov rcx,0xCBF29CE484222325` at 0x66d6c21 continues phase 9 [V]. Fields touched: rdx/rax/rcx/r8/r13 W chain [V]; [rbp+0xA60] R x2, [rbp+0xA68] R cmp x2, [rbp+0xA50] R->r13/rcx x2 [V]. Roadata: [data_129f9010] R (ptr + dword cmp 0xFFFFFFFF), [data_f549edd] R ("PatternColors"), [data_129f9020] R (ptr + dword cmp 0xFFFFFFFF), [data_f558fca] R ("PatternUVOffsetsAndScales") [V]. Callees: sub_e938cb0 [V] x2 role [?], sub_79580 [V] x2 role [?], sub_66d18cf/sub_66d1b62 [V] branch targets role [?].

## NEXT [current]
Next start RVA: 0x66d6c21 (`mov rcx,0xCBF29CE484222325`, instruction 41 of phase 8, taken directly from rdis output).
Next call: `tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d6c21 41`

## Phase 9 — 0x66d6c21, 40 instructions [V]
```
0x66d6c21  mov rcx,0xCBF29CE484222325
0x66d6c2b  xor r8d,r8d
0x66d6c2e  jmp 0x66D7C92
0x66d6c33  call 0x1166E0
0x66d6c38  nop
0x66d6c39  lea rcx,[0x129F9030]
0x66d6c40  call 0xE938CB0
0x66d6c45  cmp dword ptr [0x129F9030],0xFFFFFFFF
0x66d6c4c  jne 0x66D1C30
0x66d6c52  lea rdx,[0xF530CF6]
0x66d6c59  lea r13,[rbp+0xA50]
0x66d6c60  mov rcx,r13
0x66d6c63  call 0x79580
0x66d6c68  nop
0x66d6c69  mov rdx,[rbp+0xA60]
0x66d6c70  cmp qword ptr [rbp+0xA68],0x10
0x66d6c78  jb short 0x66D6C81
0x66d6c81  test rdx,rdx
0x66d6c84  je 0x66D7B74
0x66d6c8a  mov eax,edx
0x66d6c8c  and eax,3
0x66d6c8f  cmp rdx,4
0x66d6c93  jae 0x66D7CE0
0x66d6c99  mov rcx,0xCBF29CE484222325
0x66d6ca3  xor r8d,r8d
0x66d6ca6  jmp 0x66D7D3D
0x66d6cab  mov rcx,0xCBF29CE484222325
0x66d6cb5  jmp 0x66D6DAA
0x66d6cba  mov rcx,0xCBF29CE484222325
0x66d6cc4  jmp 0x66D6E5C
0x66d6cc9  mov rcx,0xCBF29CE484222325
0x66d6cd3  jmp 0x66D6F07
0x66d6cd8  mov rcx,0xCBF29CE484222325
0x66d6ce2  jmp 0x66D6FB2
0x66d6ce7  mov rcx,0xCBF29CE484222325
0x66d6cf1  jmp 0x66D705D
0x66d6cf6  mov rcx,0xCBF29CE484222325
0x66d6d00  jmp 0x66D7108
0x66d6d05  mov rcx,0xCBF29CE484222325
0x66d6d0f  jmp 0x66D71B3
```
// [V] Phase 9 continues the cold uniform-lookup/hash series (not part of bodyActor live flow; seen in linear rdis walk) [I]. `mov rcx,0xCBF29CE484222325` (FNV-1a basis, from phase-8 tail fallthrough) [I]; `xor r8d,r8d` (hash accumulator=0); `jmp 0x66d7c92` (hash loop entry) [V]. `call 0x1166E0 (sub_1166e0)` [V] role [?]; `nop` [V]. `lea rcx,[0x129F9030] ([data_129f9030]); call sub_e938cb0; cmp dword ptr [0x129f9030],0xFFFFFFFF; jne 0x66d1c30` — global-id init then branch out [V]. `lea rdx,[0xF530CF6] ([data_f530cf6] "PatternCount")` [V]; `lea r13,[rbp+0xA50]; mov rcx,r13; call sub_79580` (uniform lookup by name, ctx=&rbp+0xA50) [V] role [?]; `nop` [V]; `mov rdx,[rbp+0xA60]; cmp qword ptr [rbp+0xA68],0x10; jb short 0x66d6c81` [V]; loc_66d6c81: `test rdx,rdx; je 0x66d7b74` (empty->exit) [V]; `mov eax,edx; and eax,3` (len mod 4) [V]; `cmp rdx,4; jae 0x66d7ce0` (len>=4 -> long hash path) [V]; short path: `mov rcx,0xCBF29CE484222325`; `xor r8d,r8d`; `jmp 0x66d7d3d` (hash loop entry) [V]. Then a jump-table style chain of `mov rcx,0xCBF29CE484222325; jmp <loop>` blocks (instrs 27-40) with targets 0x66d6daa, 0x66d6e5c, 0x66d6f07, 0x66d6fb2, 0x66d705d, 0x66d7108, 0x66d7113? no — 0x66d7108 (instr 38), then instr 39 `mov rcx,0xCBF29CE484222325` at 0x66d6d05; instr 40 `jmp 0x66d71b3` at 0x66d6d0f — instruction 41 `mov rcx,0xCBF29CE484222325` at 0x66d6d14 continues phase 10 [V]. Fields touched: rcx/r8 W chain [V]; [rbp+0xA60] R, [rbp+0xA68] R cmp, [rbp+0xA50] R->r13/rcx [V]. Roadata: [data_129f9030] R (ptr + dword cmp 0xFFFFFFFF), [data_f530cf6] R ("PatternCount") [V]. Callees: sub_1166e0 [V] role [?], sub_e938cb0 [V] role [?], sub_79580 [V] role [?], sub_66d1c30 [V] branch target role [?].

## NEXT [current]
Next start RVA: 0x66d6d14 (`mov rcx,0xCBF29CE484222325`, instruction 41 of phase 9, taken directly from rdis output).
Next call: `tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d6d14 41`

## Phase 10 — 0x66d6d14, 40 instructions [V]
```
0x66d6d14  mov rcx,0xCBF29CE484222325                    
0x66d6d1e  jmp 0x66D725E                                 ; -> loc_66d725e
0x66d6d23  and rdx,0xFFFFFFFFFFFFFFFC                    
0x66d6d27  mov rcx,0xCBF29CE484222325                    
0x66d6d31  xor r8d,r8d                                   
0x66d6d34  mov r9,0x100000001B3                          
0x66d6d3e  movzx r10d,byte ptr [r13+r8]                  
0x66d6d44  xor r10,rcx                                   
0x66d6d47  imul r10,r9                                   
0x66d6d4b  movzx ecx,byte ptr [r13+r8+1]                 
0x66d6d51  xor rcx,r10                                   
0x66d6d54  imul rcx,r9                                   
0x66d6d58  movzx r10d,byte ptr [r13+r8+2]                
0x66d6d5e  xor r10,rcx                                   
0x66d6d61  imul r10,r9                                   
0x66d6d65  movzx ecx,byte ptr [r13+r8+3]                 
0x66d6d6b  xor rcx,r10                                   
0x66d6d6e  imul rcx,r9                                   
0x66d6d72  add r8,4                                      
0x66d6d76  cmp rdx,r8                                    
0x66d6d79  jne short 0x66D6D3E                           ; -> loc_66d6d3e
0x66d6d7b  test rax,rax                                  
0x66d6d7e  je short 0x66D6DAA                            ; -> loc_66d6daa
0x66d6d80  add r13,r8                                    
0x66d6d83  xor edx,edx                                   
0x66d6d85  mov r8,0x100000001B3                          
0x66d6d8f  mov r9,rcx                                    
0x66d6d92  movzx ecx,byte ptr [r13+rdx]                  
0x66d6d98  xor rcx,r9                                    
0x66d6d9b  imul rcx,r8                                   
0x66d6d9f  inc rdx                                       
0x66d6da2  mov r9,rcx                                    
0x66d6da5  cmp rax,rdx                                   
0x66d6da8  jne short 0x66D6D92                           ; -> loc_66d6d92
0x66d6daa  mov [0x129F9038],rcx                          ; [data_129f9038]
  0x66d6db1  lea rcx,[rbp+0xA50]                           
  0x66d6db8  call 0x73150                                  ; -> sub_73150
  0x66d6dbd  lea rcx,[0x129F9040]                          ; [data_129f9040]
  0x66d6dc4  call 0xE938D70                                ; -> sub_e938d70
  0x66d6dc9  mov rbx,[rbp+0xD90]                           
```
// [V] Phase 10 is the real FNV-1a hash loop code (not part of bodyActor live flow; seen in linear rdis walk) [I]. Continuation of phase-9 jump-table chain: `mov rcx,0xCBF29CE484222325` (FNV-1a 64-bit offset basis) [I]; `jmp 0x66d725e` (hash loop entry outside this phase) [V]; then `and rdx,0xFFFFFFFFFFFFFFFC` (length aligned down to multiple of 4) [V]; `mov rcx,0xCBF29CE484222325` (basis reset) [V]; `xor r8d,r8d` (byte index=0) [V]; `mov r9,0x100000001B3` (FNV-1a 64-bit prime) [V][I meaning]. loc_66d6d3e: 4-byte-unrolled loop, each iteration `movzx r10d,byte ptr [r13+r8]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+1]; xor rcx,r10; imul rcx,r9; movzx r10d,byte ptr [r13+r8+2]; xor r10,rcx; imul r10,r9; movzx ecx,byte ptr [r13+r8+3]; xor rcx,r10; imul rcx,r9; add r8,4; cmp rdx,r8; jne short 0x66d6d3e` (FNV-1a mix per byte) [V]; `test rax,rax; je short 0x66d6daa` (zero-length tail skip) [V]. loc_66d6daa join via fallthrough setup: `add r13,r8` (advance data ptr) [V]; `xor edx,edx` (tail index=0) [V]; `mov r8,0x100000001B3` (prime) [V]; `mov r9,rcx` (carry running hash) [V]. loc_66d6d92: byte-at-a-time tail loop `movzx ecx,byte ptr [r13+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; mov r9,rcx; cmp rax,rdx; jne short 0x66d6d92` [V]. Finish: `mov [0x129F9038],rcx` (store final hash to rodata/global [data_129f9038]) [V]; `lea rcx,[rbp+0xA50]; call 0x73150 (sub_73150)` [V] role [?]; `lea rcx,[0x129F9040]; call 0xE938D70 (sub_e938d70)` [V]; `mov rbx,[rbp+0xD90]` [V]. Fields touched: rcx/r8/r9/edx/r10/rax/r13 W chain, rbx W [V]; rdx R (len) W [V]; [0x129F9038] W, [rbp+0xA50] R (call arg), [rbp+0xD90] R->rbx W [V]; rodata [data_129f9038] W [V]. Callees: sub_73150 [V] role [?], sub_e938d70 [V] role [?].
## NEXT [current]
Next start RVA: 0x66d6dd0 (`jmp 0x66D1D07`, instruction 41 of phase 10, taken directly from rdis output via `dis 0x66d6db8 6`).
Next call: `tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d6dd0 41`
## Phase 11 — 0x66d6dd0, 40 instructions [V]
```
0x66d6dd0  jmp 0x66D1D07                                 ; -> sub_66d1d07
0x66d6dd5  and rdx,0xFFFFFFFFFFFFFFFC                    
0x66d6dd9  mov rcx,0xCBF29CE484222325                    
0x66d6de3  xor r8d,r8d                                   
0x66d6de6  mov r9,0x100000001B3                          
0x66d6df0  movzx r10d,byte ptr [r13+r8]                  
0x66d6df6  xor r10,rcx                                   
0x66d6df9  imul r10,r9                                   
0x66d6dfd  movzx ecx,byte ptr [r13+r8+1]                 
0x66d6e03  xor rcx,r10                                   
0x66d6e06  imul rcx,r9                                   
0x66d6e0a  movzx r10d,byte ptr [r13+r8+2]                
0x66d6e10  xor r10,rcx                                   
0x66d6e13  imul r10,r9                                   
0x66d6e17  movzx ecx,byte ptr [r13+r8+3]                 
0x66d6e1d  xor rcx,r10                                   
0x66d6e20  imul rcx,r9                                   
0x66d6e24  add r8,4                                      
0x66d6e28  cmp rdx,r8                                    
0x66d6e2b  jne short 0x66D6DF0                           ; -> loc_66d6df0
0x66d6e2d  test rax,rax                                  
0x66d6e30  je short 0x66D6E5C                            ; -> loc_66d6e5c
0x66d6e32  add r13,r8                                    
0x66d6e35  xor edx,edx                                   
0x66d6e37  mov r8,0x100000001B3                          
0x66d6e41  mov r9,rcx                                    
0x66d6e44  movzx ecx,byte ptr [r13+rdx]                  
0x66d6e4a  xor rcx,r9                                    
0x66d6e4d  imul rcx,r8                                   
0x66d6e51  inc rdx                                       
0x66d6e54  mov r9,rcx                                    
0x66d6e57  cmp rax,rdx                                   
0x66d6e5a  jne short 0x66D6E44                           ; -> loc_66d6e44
0x66d6e5c  mov [0x129F9048],rcx                          ; [data_129f9048]
0x66d6e63  lea rcx,[rbp+0xA50]                           
0x66d6e6a  call 0x73150                                  ; -> sub_73150
0x66d6e6f  lea rcx,[0x129F9050]                          ; [data_129f9050]
0x66d6e76  call 0xE938D70                                ; -> sub_e938d70
0x66d6e7b  jmp 0x66D1E78                                 ; -> sub_66d1e78
0x66d6e80  and rdx,0xFFFFFFFFFFFFFFFC                    
```
// [V] Phase 11 is a second FNV-1a hash instance (stores to [0x129F9048]; phase 10 stored to [0x129F9038] and branched to sub_66d1d07, here branches to sub_66d1e78): entered `jmp 0x66D1D07` then fall-through hash preamble `and rdx,0xFFFFFFFFFFFFFFFC` (len aligned down to 4-byte multiple); `mov rcx,0xCBF29CE484222325` (FNV-1a 64-bit offset basis) [I]; `xor r8d,r8d` (index=0); `mov r9,0x100000001B3` (FNV prime) [I]. 4-byte unrolled loop at loc_66d6df0: per byte `movzx r10d,[r13+r8]; xor r10,rcx; imul r10,r9` rolling the mix across [r13+r8+0..+3]; `add r8,4; cmp rdx,r8; jne loc_66d6df0` [V]. Exit `test rax,rax; je short 0x66d6e5c` — rax==0 (empty data) skips the tail loop and jumps straight to the store [V]. Tail setup: `add r13,r8` (ptr += processed bytes); `xor edx,edx` (tail index=0); `mov r8,prime`; `mov r9,rcx` [V]. Tail loop loc_66d6e44: `movzx ecx,byte ptr [r13+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; cmp rax,rdx; jne loc_66d6e44` [V]. Store result: `mov [0x129F9048],rcx` ([data_129f9048], hash result slot) [V]. Post-hash: `lea rcx,[rbp+0xA50]; call 0x73150 (sub_73150)`; `lea rcx,[0x129F9050] ([data_129f9050]); call 0xE938D70 (sub_e938d70)`; `jmp 0x66D1E78 (sub_66d1e78)` [V]. All tags [V] except FNV basis/prime meaning [I].

## NEXT [resume]
Phase 11 complete: last quoted RVA 0x66d6e80 (instruction 40). Resume RVA (instruction 41): 0x66d6e84 `mov rcx,0xCBF29CE484222325` — taken directly from `dis 0x66d6e6f 6` output, NOT hand-computed [V].
Next call:
`tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d6e84 41`

## Phase 12 — 0x66d6e84, 40 instructions [V]
```
0x66d6e84  mov rcx,0xCBF29CE484222325                    
0x66d6e8e  xor r8d,r8d                                   
0x66d6e91  mov r9,0x100000001B3                          
0x66d6e9b  movzx r10d,byte ptr [r13+r8]                  
0x66d6ea1  xor r10,rcx                                   
0x66d6ea4  imul r10,r9                                   
0x66d6ea8  movzx ecx,byte ptr [r13+r8+1]                 
0x66d6eae  xor rcx,r10                                   
0x66d6eb1  imul rcx,r9                                   
0x66d6eb5  movzx r10d,byte ptr [r13+r8+2]                
0x66d6ebb  xor r10,rcx                                   
0x66d6ebe  imul r10,r9                                   
0x66d6ec2  movzx ecx,byte ptr [r13+r8+3]                 
0x66d6ec8  xor rcx,r10                                   
0x66d6ecb  imul rcx,r9                                   
0x66d6ecf  add r8,4                                      
0x66d6ed3  cmp rdx,r8                                    
0x66d6ed6  jne short 0x66D6E9B                           ; -> loc_66d6e9b
0x66d6ed8  test rax,rax                                  
0x66d6edb  je short 0x66D6F07                            ; -> loc_66d6f07
0x66d6edd  add r13,r8                                    
0x66d6ee0  xor edx,edx                                   
0x66d6ee2  mov r8,0x100000001B3                          
0x66d6eec  mov r9,rcx                                    
0x66d6eef  movzx ecx,byte ptr [r13+rdx]                  
0x66d6ef5  xor rcx,r9                                    
0x66d6ef8  imul rcx,r8                                   
0x66d6efc  inc rdx                                       
0x66d6eff  mov r9,rcx                                    
0x66d6f02  cmp rax,rdx                                   
0x66d6f05  jne short 0x66D6EEF                           ; -> loc_66d6eef
0x66d6f07  mov [0x129F9058],rcx                          ; [data_129f9058]
0x66d6f0e  lea rcx,[rbp+0xA50]                           
0x66d6f15  call 0x73150                                  ; -> sub_73150
0x66d6f1a  lea rcx,[0x129F9060]                          ; [data_129f9060]
0x66d6f21  call 0xE938D70                                ; -> sub_e938d70
0x66d6f26  jmp 0x66D1E9D                                 ; -> sub_66d1e9d
0x66d6f2b  and rdx,0xFFFFFFFFFFFFFFFC                    
0x66d6f2f  mov rcx,0xCBF29CE484222325                    
0x66d6f39  xor r8d,r8d                                   
```
// [V] Phase 12 is a third FNV-1a hash instance (stores to [0x129F9058]; phases 10/11 stored to [0x129F9038]/[0x129F9048] and branched to sub_66d1d07/sub_66d1e78, here branches to sub_66d1e9d): preamble `mov rcx,0xCBF29CE484222325` (FNV-1a 64-bit offset basis) [I]; `xor r8d,r8d` (index=0); `mov r9,0x100000001B3` (FNV prime) [I]. 4-byte unrolled loop at loc_66d6e9b: per byte `movzx r10d,[r13+r8]; xor r10,rcx; imul r10,r9` rolling across [r13+r8+0..+3]; `add r8,4; cmp rdx,r8; jne loc_66d6e9b` [V]. Exit `test rax,rax; je short 0x66d6f07` — rax==0 (empty) skips tail loop to the store [V]. Tail setup: `add r13,r8`; `xor edx,edx`; `mov r8,prime`; `mov r9,rcx` [V]. Tail loop loc_66d6eef: `movzx ecx,byte ptr [r13+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; cmp rax,rdx; jne loc_66d6eef` [V]. Store: `mov [0x129F9058],rcx` ([data_129f9058], hash result slot) [V]. Post-hash: `lea rcx,[rbp+0xA50]; call 0x73150 (sub_73150)`; `lea rcx,[0x129F9060] ([data_129f9060]); call 0xE938D70 (sub_e938d70)`; `jmp 0x66D1E9D (sub_66d1e9d)` [V]. All tags [V] except FNV basis/prime meaning [I].

## NEXT [resume]
Phase 12 complete: last quoted RVA 0x66d6f39 (instruction 40). Resume RVA (instruction 41): 0x66d6f3c `mov r9,0x100000001B3` — taken directly from the `dis 0x66d6e84 41` output above, NOT hand-computed [V].
Next call:
`tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d6f3c 41`

## Phase 13 — 0x66d6f3c, 40 instructions [V]
```
0x66d6f3c  mov r9,0x100000001B3                          
0x66d6f46  movzx r10d,byte ptr [r13+r8]                  
0x66d6f4c  xor r10,rcx                                   
0x66d6f4f  imul r10,r9                                   
0x66d6f53  movzx ecx,byte ptr [r13+r8+1]                 
0x66d6f59  xor rcx,r10                                   
0x66d6f5c  imul rcx,r9                                   
0x66d6f60  movzx r10d,byte ptr [r13+r8+2]                
0x66d6f66  xor r10,rcx                                   
0x66d6f69  imul r10,r9                                   
0x66d6f6d  movzx ecx,byte ptr [r13+r8+3]                 
0x66d6f73  xor rcx,r10                                   
0x66d6f76  imul rcx,r9                                   
0x66d6f7a  add r8,4                                      
0x66d6f7e  cmp rdx,r8                                    
0x66d6f81  jne short 0x66D6F46                           ; -> loc_66d6f46
0x66d6f83  test rax,rax                                  
0x66d6f86  je short 0x66D6FB2                            ; -> loc_66d6fb2
0x66d6f88  add r13,r8                                    
0x66d6f8b  xor edx,edx                                   
0x66d6f8d  mov r8,0x100000001B3                          
0x66d6f97  mov r9,rcx                                    
0x66d6f9a  movzx ecx,byte ptr [r13+rdx]                  
0x66d6fa0  xor rcx,r9                                    
0x66d6fa3  imul rcx,r8                                   
0x66d6fa7  inc rdx                                       
0x66d6faa  mov r9,rcx                                    
0x66d6fad  cmp rax,rdx                                   
0x66d6fb0  jne short 0x66D6F9A                           ; -> loc_66d6f9a
0x66d6fb2  mov [0x129F9068],rcx                          ; [data_129f9068]
0x66d6fb9  lea rcx,[rbp+0xA50]                           
0x66d6fc0  call 0x73150                                  ; -> sub_73150
0x66d6fc5  lea rcx,[0x129F9070]                          ; [data_129f9070]
0x66d6fcc  call 0xE938D70                                ; -> sub_e938d70
0x66d6fd1  jmp 0x66D1EC2                                 ; -> sub_66d1ec2
0x66d6fd6  and rdx,0xFFFFFFFFFFFFFFFC                    
0x66d6fda  mov rcx,0xCBF29CE484222325                    
0x66d6fe4  xor r8d,r8d                                   
0x66d6fe7  mov r9,0x100000001B3                          
0x66d6ff1  movzx r10d,byte ptr [r13+r8]                  
```
// [V] Phase 13 is a fourth FNV-1a hash instance (stores to [0x129F9068]; phases 10-12 stored to [0x129F9038]/[0x129F9048]/[0x129F9058] and branched to sub_66d1d07/sub_66d1e78/sub_66d1e9d, here branches to sub_66d1ec2): entered at `mov r9,0x100000001B3` (FNV prime) [I] with rcx=rolling hash, r8d=index, rdx=len live-in from the preceding cold block. 4-byte unrolled loop at loc_66d6f46: per byte `movzx r10d,[r13+r8]; xor r10,rcx; imul r10,r9` rolling across [r13+r8+0..+3]; `add r8,4; cmp rdx,r8; jne loc_66d6f46` [V]. Exit `test rax,rax; je short 0x66d6fb2` — rax==0 (empty) skips tail loop to the store [V]. Tail setup: `add r13,r8`; `xor edx,edx`; `mov r8,prime`; `mov r9,rcx` [V]. Tail loop loc_66d6f9a: `movzx ecx,byte ptr [r13+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; cmp rax,rdx; jne loc_66d6f9a` [V]. Store: `mov [0x129F9068],rcx` ([data_129f9068], hash result slot) [V]. Post-hash: `lea rcx,[rbp+0xA50]; call 0x73150 (sub_73150)`; `lea rcx,[0x129F9070] ([data_129f9070]); call 0xE938D70 (sub_e938d70)`; `jmp 0x66D1EC2 (sub_66d1ec2)` [V]. All tags [V] except FNV prime/basis meaning [I].

## NEXT [resume]
Phase 13 complete: last quoted RVA 0x66d6ff1 (instruction 40). Resume RVA (instruction 41): 0x66d6ff7 `xor r10,rcx` — taken directly from the `dis 0x66d6f3c 41` output above, NOT hand-computed [V].
Next call:
`tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d6ff7 41`

## Phase 14 — 0x66d6ff7, 40 instructions [V]
```
0x66d6ff7  xor r10,rcx                                   
0x66d6ffa  imul r10,r9                                   
0x66d6ffe  movzx ecx,byte ptr [r13+r8+1]                 
0x66d7004  xor rcx,r10                                   
0x66d7007  imul rcx,r9                                   
0x66d700b  movzx r10d,byte ptr [r13+r8+2]                
0x66d7011  xor r10,rcx                                   
0x66d7014  imul r10,r9                                   
0x66d7018  movzx ecx,byte ptr [r13+r8+3]                 
0x66d701e  xor rcx,r10                                   
0x66d7021  imul rcx,r9                                   
0x66d7025  add r8,4                                      
0x66d7029  cmp rdx,r8                                    
0x66d702c  jne short 0x66D6FF1                           ; -> sub_66d6ff1
0x66d702e  test rax,rax                                  
0x66d7031  je short 0x66D705D                            ; -> loc_66d705d
0x66d7033  add r13,r8                                    
0x66d7036  xor edx,edx                                   
0x66d7038  mov r8,0x100000001B3                          
0x66d7042  mov r9,rcx                                    
0x66d7045  movzx ecx,byte ptr [r13+rdx]                  
0x66d704b  xor rcx,r9                                    
0x66d704e  imul rcx,r8                                   
0x66d7052  inc rdx                                       
0x66d7055  mov r9,rcx                                    
0x66d7058  cmp rax,rdx                                   
0x66d705b  jne short 0x66D7045                           ; -> loc_66d7045
0x66d705d  mov [0x129F9078],rcx                          ; [data_129f9078]
0x66d7064  lea rcx,[rbp+0xA50]                           
0x66d706b  call 0x73150                                  ; -> sub_73150
0x66d7070  lea rcx,[0x129F9080]                          ; [data_129f9080]
0x66d7077  call 0xE938D70                                ; -> sub_e938d70
0x66d707c  jmp 0x66D1EE7                                 ; -> sub_66d1ee7
0x66d7081  and rdx,0xFFFFFFFFFFFFFFFC                    
0x66d7085  mov rcx,0xCBF29CE484222325                    
0x66d708f  xor r8d,r8d                                   
0x66d7092  mov r9,0x100000001B3                          
0x66d709c  movzx r10d,byte ptr [r13+r8]                  
0x66d70a2  xor r10,rcx                                   
0x66d70a5  imul r10,r9                                   
```
// [V] Phase 14 is a fifth FNV-1a hash instance (stores to [0x129F9078]; phases 10-13 stored to [0x129F9038]/[0x129F9048]/[0x129F9058]/[0x129F9068] and branched to sub_66d1d07/sub_66d1e78/sub_66d1e9d/sub_66d1ec2, here branches to sub_66d1ee7): entered mid-loop at `xor r10,rcx` (rcx=rolling hash, r9=prime live-in). Continues the 4-byte unrolled loop: `movzx ecx,[r13+r8+1]; xor rcx,r10; imul rcx,r9; movzx r10d,[r13+r8+2]; ... movzx ecx,[r13+r8+3]; xor rcx,r10; imul rcx,r9; add r8,4; cmp rdx,r8; jne 0x66d6ff1` [V]. Exit `test rax,rax; je short 0x66d705d` — rax==0 (empty) skips tail loop to store [V]. Tail setup: `add r13,r8`; `xor edx,edx`; `mov r8,prime`; `mov r9,rcx` [V]. Tail loop loc_66d7045: `movzx ecx,byte ptr [r13+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; cmp rax,rdx; jne loc_66d7045` [V]. Store: `mov [0x129F9078],rcx` ([data_129f9078], hash result slot) [V]. Post-hash: `lea rcx,[rbp+0xA50]; call 0x73150 (sub_73150)`; `lea rcx,[0x129F9080] ([data_129f9080]); call 0xE938D70 (sub_e938d70)`; `jmp 0x66D1EE7 (sub_66d1ee7)` [V]. All tags [V] except FNV prime/basis meaning [I].

## NEXT [resume]
Phase 14 complete: last quoted RVA 0x66d70a5 (instruction 40). Resume RVA (instruction 41): 0x66d70a9 `movzx ecx,byte ptr [r13+r8+1]` — taken directly from the `dis 0x66d6ff7 41` output above, NOT hand-computed [V].
Next call:
`tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d70a9 41`

## Phase 15 — 0x66d70a9, 40 instructions [V]
```
0x66d70a9  movzx ecx,byte ptr [r13+r8+1]                 
0x66d70af  xor rcx,r10                                   
0x66d70b2  imul rcx,r9                                   
0x66d70b6  movzx r10d,byte ptr [r13+r8+2]                
0x66d70bc  xor r10,rcx                                   
0x66d70bf  imul r10,r9                                   
0x66d70c3  movzx ecx,byte ptr [r13+r8+3]                 
0x66d70c9  xor rcx,r10                                   
0x66d70cc  imul rcx,r9                                   
0x66d70d0  add r8,4                                      
0x66d70d4  cmp rdx,r8                                    
0x66d70d7  jne short 0x66D709C                           ; -> sub_66d709c
0x66d70d9  test rax,rax                                  
0x66d70dc  je short 0x66D7108                            ; -> loc_66d7108
0x66d70de  add r13,r8                                    
0x66d70e1  xor edx,edx                                   
0x66d70e3  mov r8,0x100000001B3                          
0x66d70ed  mov r9,rcx                                    
0x66d70f0  movzx ecx,byte ptr [r13+rdx]                  
0x66d70f6  xor rcx,r9                                    
0x66d70f9  imul rcx,r8                                   
0x66d70fd  inc rdx                                       
0x66d7100  mov r9,rcx                                    
0x66d7103  cmp rax,rdx                                   
0x66d7106  jne short 0x66D70F0                           ; -> loc_66d70f0
0x66d7108  mov [0x129F90A8],rcx                          ; [data_129f90a8]
0x66d710f  lea rcx,[rbp+0xA50]                           
0x66d7116  call 0x73150                                  ; -> sub_73150
0x66d711b  lea rcx,[0x129F90B0]                          ; [data_129f90b0]
0x66d7122  call 0xE938D70                                ; -> sub_e938d70
0x66d7127  jmp 0x66D28CA                                 ; -> sub_66d28ca
0x66d712c  and rdx,0xFFFFFFFFFFFFFFFC                    
0x66d7130  mov rcx,0xCBF29CE484222325                    
0x66d713a  xor r8d,r8d                                   
0x66d713d  mov r9,0x100000001B3                          
0x66d7147  movzx r10d,byte ptr [r13+r8]                  
0x66d714d  xor r10,rcx                                   
0x66d7150  imul r10,r9                                   
0x66d7154  movzx ecx,byte ptr [r13+r8+1]                 
0x66d715a  xor rcx,r10                                   
```
// [V] Phase 15 is a sixth and final FNV-1a hash instance of this unit (stores to [0x129F90A8]; phases 10-14 stored to [0x129F9038]/[0x129F9048]/[0x129F9058]/[0x129F9068]/[0x129F9078] and branched to sub_66d1d07/sub_66d1e78/sub_66d1e9d/sub_66d1ec2/sub_66d1ee7, here branches to sub_66d28ca): entered mid-loop at `movzx ecx,[r13+r8+1]` (rcx=rolling hash, r10/r9 live-in). Continues the 4-byte unrolled loop: `xor rcx,r10; imul rcx,r9; movzx r10d,[r13+r8+2]; xor r10,rcx; imul r10,r9; movzx ecx,[r13+r8+3]; xor rcx,r10; imul rcx,r9; add r8,4; cmp rdx,r8; jne 0x66d709c` [V]. Exit `test rax,rax; je short 0x66d7108` — rax==0 (empty) skips tail loop to store [V]. Tail setup: `add r13,r8`; `xor edx,edx`; `mov r8,prime`; `mov r9,rcx` [V]. Tail loop loc_66d70f0: `movzx ecx,byte ptr [r13+rdx]; xor rcx,r9; imul rcx,r8; inc rdx; cmp rax,rdx; jne loc_66d70f0` [V]. Store: `mov [0x129F90A8],rcx` ([data_129f90a8], hash result slot) [V]. Post-hash: `lea rcx,[rbp+0xA50]; call 0x73150 (sub_73150)`; `lea rcx,[0x129F90B0] ([data_129f90b0]); call 0xE938D70 (sub_e938d70)`; `jmp 0x66D28CA (sub_66d28ca)` [V]. All tags [V] except FNV prime/basis meaning [I].

## NEXT [done]
Unit U-BA8 complete: 15/15 phases written (0x66d6562..0x66d715a, last quoted RVA 0x66d715a). Resume RVA (instruction 41 of phase 15): 0x66d715d `imul rcx,r9` — taken directly from `dis 0x66d70a9 41` output, NOT hand-computed [V]. No further phases needed per unit scope. All phases are post-`ret` cold uniform-name hash/lookup blocks (not bodyActor live flow): per block `lea rdx,[data] "<name>" (sub_79580 lookup by name via rcx=&rbp+0xA50)` + FNV-1a hash of [rbp+0xA60] (len [rbp+0xA68]) into a per-uniform rodata slot ([0x129F9038..0x129F90A8]) followed by `lea rcx,[rbp+0xA50]; call sub_73150; lea rcx,[data]; call sub_e938d70; jmp <sub_x>`. Slot/names: [0x129F9038]?(phase10, name [?]—phase-10 name block was in oc_U-BA7 range), [0x129F9048]/[data_129f9050] (phase 11), [0x129F9058]/[data_129f9060] (phase 12), [0x129F9068]/[data_129f9070] (phase 13), [0x129F9078]/[data_129f9080] (phase 14), [0x129F90A8]/[data_129f90b0] (phase 15). Callees: sub_73150 [V], sub_e938d70 [V] (roles [I]), branch targets sub_66d1e78/sub_66d1e9d/sub_66d1ec2/sub_66d1ee7/sub_66d28ca [V] (roles [I]). Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Static analysis only; game closed.
