## NEXT
DONE

# U-EM1e: M1e Pass lambdas (L6) — bloom down run (0xbc99739 / 0xbc99794)

This run covers bloom down body 0xbc99739 / 0xbc99794: DFDownSample (0xbc99739) and ThresholdedDownSample (0xbc99794) hash-static registration sites in builder 0xbc98310 ("Bloom"), plus their executed bodies 0xbc9ac80 / 0xbc9ad10.

Ground truth from rdis (this run, re-checked against the exe): each site loads the pass FNV-1 64 hash into rdx, calls sub_76ad00 (hash resolve), then passes the execute-body address to sub_e935740 and the pass slot to sub_e938D70. The executed bodies are 0xbc9ac80 (DFDownSample) and 0xbc9ad10 (ThresholdedDownSample) — NOT ScreenDraw 0xbc04dc0 (the r4/r10 claim that the executed body is ScreenDraw is contradicted by the disassembly). Each body is a thin wrapper: read ring-buffer globals, then `call qword ptr [0xF9A8C78]` indirect dispatch. The dispatch target held in data slot 0xF9A8C78 and its UAV/texture in/out are not statically decoded here.

## Verified rows — bloom down (offset | size | address | verbatim `0xRVA  instr` | meaning | tag)

| offset | size | address | verbatim `0xRVA  instr` | meaning | tag |
| 0xbc99739 | 8 | imm | `0xbc99739  mov rdx,0x34E743CD5E04564D` | DFDownSample FNV-1 64 hash loaded into rdx before call 0x76AD00 (sub_76ad00 hash resolve) | [V] |
| 0xbc99743 | - | call | `0xbc99743  call 0x76AD00` | sub_76ad00 resolves the DFDownSample hash | [V] |
| 0xbc99749 | 8 | imm | `0xbc99749  lea rcx,[0xBC9AC80]` | DFDownSample execute-body address passed as arg 1 to sub_e935740 | [V] |
| 0xbc99750 | - | call | `0xbc99750  call 0xE935740` | register DFDownSample execute body 0xbc9ac80 via sub_e935740 | [V] |
| 0xbc99755 | 8 | imm | `0xbc99755  lea rcx,[0x12AE1DB0]` | DFDownSample pass slot passed as arg 1 to sub_e938D70 | [V] |
| 0xbc9975c | - | call | `0xbc9975c  call 0xE938D70` | register DFDownSample pass slot 0x12AE1DB0 via sub_e938D70 | [V] |
| 0xbc99794 | 8 | imm | `0xbc99794  mov rdx,0x714FFC3B4FD51617` | ThresholdedDownSample FNV-1 64 hash loaded into rdx before call 0x76AD00 | [V] |
| 0xbc9979e | - | call | `0xbc9979e  call 0x76AD00` | sub_76ad00 resolves the ThresholdedDownSample hash | [V] |
| 0xbc997a4 | 8 | imm | `0xbc997a4  lea rcx,[0xBC9AD10]` | ThresholdedDownSample execute-body address passed as arg 1 to sub_e935740 | [V] |
| 0xbc997ab | - | call | `0xbc997ab  call 0xE935740` | register ThresholdedDownSample execute body 0xbc9ad10 via sub_e935740 | [V] |
| 0xbc997b0 | 8 | imm | `0xbc997b0  lea rcx,[0x12AE1DE8]` | ThresholdedDownSample pass slot passed as arg 1 to sub_e938D70 | [V] |
| 0xbc997b7 | - | call | `0xbc997b7  call 0xE938D70` | register ThresholdedDownSample pass slot 0x12AE1DE8 via sub_e938D70 | [V] |
| 0xbc9ac80 | - | [none] | `0xbc9ac80  sub rsp,0x28` | DFDownSample execute body 0xbc9ac80 prologue | [V] |
| 0xbc9ac84 | 8 | [data_12ae1da0] | `0xbc9ac84  mov rax,[0x12AE1DA0]` | In: DFDownSample ring-buffer count read from data_12ae1da0 | [V] |
| 0xbc9ac91 | 8 | [data_12ae1d88] | `0xbc9ac91  mov rcx,[0x12AE1D88]` | In: DFDownSample ring-buffer base read from data_12ae1d88 | [V] |
| 0xbc9acfa | - | [data_f9a8c78] | `0xbc9acfa  call qword ptr [0xF9A8C78]` | Out/dispatch: DFDownSample indirect dispatch via data slot 0xF9A8C78; dispatch target and UAV/texture writes not decoded here | [?] |
| 0xbc9ad10 | - | [none] | `0xbc9ad10  sub rsp,0x28` | ThresholdedDownSample execute body 0xbc9ad10 prologue | [V] |
| 0xbc9ad14 | 8 | [data_12ae1dd8] | `0xbc9ad14  mov rax,[0x12AE1DD8]` | In: ThresholdedDownSample ring-buffer count read from data_12ae1dd8 | [V] |
| 0xbc9ad21 | 8 | [data_12ae1dc0] | `0xbc9ad21  mov rcx,[0x12AE1DC0]` | In: ThresholdedDownSample ring-buffer base read from data_12ae1dc0 | [V] |
| 0xbc9ad8a | - | [data_f9a8c78] | `0xbc9ad8a  call qword ptr [0xF9A8C78]` | Out/dispatch: ThresholdedDownSample indirect dispatch via data slot 0xF9A8C78; dispatch target and UAV/texture writes not decoded here | [?] |

## What changed on disk

- Created docs/progress/oc_U-EM1e.md (this file). No other file created, edited, or deleted. No build run; the game was not launched; static analysis only, exe used only as an argument to rdis.exe.

## CLOSES?

CLOSES? NO — single blocking fact: bloom down bodies 0xbc9ac80/0xbc9ad10 are proven [V] as registration wrappers that dispatch through data slot [0xF9A8C78], but the dispatch target and their full UAV/texture in/out are not statically decoded, so bloom down full in/out is [?]; the remaining ordered bodies (bloom up 0xbc9bbd4/0xbc9bc28, local exposure 0xbca2671, tail 0x568d480/0x568d750, RTX denoise UAV writes 0xbcc4b90, Fancy data sites, mismatch fixes 0x568cdbe/0x568d0b8) are not covered by this run.

## TOOL REQUESTS

- rdis.exe | exe + RVA -> instruction listing | used for every quoted `0xRVA  instr` line.
- verify_oc.py | md -> mismatch/no-such-instr report | validates quoted instruction lines against the exe.
