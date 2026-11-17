## NEXT
DONE answer table + claim lines + CLOSES? written; verify_oc 10/10; delegate check passed; CLOSES=NO (writer of ctx+0x1F0 / OptionID reader in frame-graph builder not located)

# Unit U-EL17h — L17h graphics options plumbing (OptionSync)

GOAL: close checklist item "L17h graphics options plumbing (OptionSync) pending".
Pending part (from docs/RENDER_CHECKLIST.md L17h): "OptionSync plumbing for graphics options not traced (options.upscalingPercentage and related strings found, writers not located)" and "the OptionID of upscaling percentage / target resolution and its reader in the frame-graph builder (strings upscaling_percentage 0xf5e13cc and options.targetResolution 0xf5850de have no direct code refs: registered through a table)".

All evidence below is static, Minecraft.Windows.exe 1.26.62.01, read from saved rdis outputs (tools/sigs/out_opt_upsc_mode.txt, out_67c73d0.txt, out_ef_callsite3.txt).

## Answer table

| name | offset | size | read/store address | verbatim instr | meaning | tag |
|---|---|---|---|---|---|---|
| upscaling_mode default value store | 0x5b3e915 | 4 | [rbp+0x1E0] store (u32 = 1) | `0x5b3e915  mov dword ptr [rbp+0x1E0],1` | default value for upscaling_mode option in Options ctor 0x5b3e8a0 | [V] |
| upscaling_mode count store | 0x5b3e91f | 4 | [rbp+0x180] store (u32 = 1) | `0x5b3e91f  mov dword ptr [rbp+0x180],1` | count = 1 for upscaling_mode | [V] |
| upscaling_mode max/limit store | 0x5b3e929 | 4 | [rbp+0x160] store (u32 = 0x244) | `0x5b3e929  mov dword ptr [rbp+0x160],0x244` | max/limit = 0x244 (580) for upscaling_mode | [V] |
| upscaling_mode name address load | 0x5b3e950 | 8 | [0xF5E4372] address loaded into rax | `0x5b3e950  lea rax,[0xF5E4372]` | "upscaling_mode" option-name string passed to registration | [V] |
| upscalingMode translation key load | 0x5b3e95c | 8 | [0xF5E4CBB] address loaded into rax | `0x5b3e95c  lea rax,[0xF5E4CBB]` | "options.upscalingMode" translation key passed to registration | [V] |
| OptionSync registration helper call | 0x5b3e987 | - | - | `0x5b3e987  call 0x5BC0530` | 0x5BC0530 registers option (name rdx, translation r8, default/count r9) — OptionSync plumbing entry | [V] |
| endFrame calls frame-param struct copy | 0x662def4 | - | - | `0x662def4  call 0x67C73D0` | endFrame 0x66232b0 calls 0x67C73D0 per 0x2B0-byte frame-param element; rcx=dst `rbx-0x2B0`, rdx=src `r13` | [V] |
| frame-param copy read +0x1DC | 0x67c78bc | 4 | [rsi+0x1DC] read | `0x67c78bc  movss xmm0,[rsi+0x1DC]` | option-derived value +0x1DC copied into dst struct per frame | [V] |
| frame-param copy read +0x1E0 | 0x67c78cc | 4 | [rsi+0x1E0] read | `0x67c78cc  movss xmm0,[rsi+0x1E0]` | +0x1E0 field copied; L10c: u16 dims / render-size state | [V] |
| frame-param copy read +0x1F0 | 0x67c7917 | 4 | [rsi+0x1F0] read | `0x67c7917  movss xmm0,[rsi+0x1F0]` | +0x1F0 render/display ratio copied; SOURCE WRITER NOT LOCATED | [V] |
| string "upscaling_percentage" | 0xf5e1458 | - | - | - | string exists; xref returns NO code refs (registered through table, reader not found) | [?] |
| string "options.targetResolution" | 0xf5850de | - | - | - | string exists; xref returns NO code refs (registered through table, reader not found) | [?] |

## Claim lines

0x5b3e915  mov dword ptr [rbp+0x1E0],1
0x5b3e91f  mov dword ptr [rbp+0x180],1
0x5b3e929  mov dword ptr [rbp+0x160],0x244
0x5b3e950  lea rax,[0xF5E4372]
0x5b3e95c  lea rax,[0xF5E4CBB]
0x5b3e987  call 0x5BC0530
0x662def4  call 0x67C73D0
0x67c78bc  movss xmm0,[rsi+0x1DC]
0x67c78cc  movss xmm0,[rsi+0x1E0]
0x67c7917  movss xmm0,[rsi+0x1F0]

## CLOSES?

NO. Single blocking fact: the writer of ctx+0x1F0 (render/display ratio, consumed by TAAU body 0xbc8cfd0) and the OptionID reader in the frame-graph builder that maps upscaling_percentage/options.targetResolution to ctx+0x1F0 are not located. Strings upscaling_percentage (0xf5e13cc/0xf5e1458) and options.targetResolution (0xf5850de) have NO direct code refs (registered through a table), and only upscaling_mode/options.upscalingMode are reached in code (Options ctor 0x5b0c1b0 at 0x5b3e950/0x5b3e95c, preset parser 0x11493a0 at 0x115050e). endFrame 0x66232b0 copies option-derived fields (+0x1DC/+0x1E0/+0x1F0) via 0x67C73D0 at 0x662def4, but the source struct writer upstream of endFrame is not traced.

## TOOL REQUESTS

None — used saved rdis/xref outputs only; no helper script written.
