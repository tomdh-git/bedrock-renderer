## DONE

Gameface Extractor Call Argument Mapping (call 0x66B2730)

Call site: `0x66aedf1  call 0x66B2730` at listing line 766

Argument setup (first [rsp+..] store to call, lines 760-762):
  - `0x66aedce  mov [rsp+0x30],eax`
  - `0x66aedd2  mov [rsp+0x28],rcx`
  - `0x66aedd7  mov [rsp+0x20],r8`

Table: extractor 0x66B2730 argument -> element field

| arg slot | value | source (element offset) | evidence |
|---|---|---|---|
| [rsp+0x30] | eax | element +0x184 (dword) | 0x66aed3a mov eax,[r15+0x184]; 0x66aedce mov [rsp+0x30],eax |
| [rsp+0x28] | rcx | element +0x188 (dword, zero-extended to rcx) | 0x66aed41 mov ecx,[r15+0x188]; 0x66aedd2 mov [rsp+0x28],rcx |
| [rsp+0x20] | r8 | element +0x00 dword [ptr+4] loaded | 0x66aed48 mov rdx,[r15]; 0x66aed4b mov r8d,[rdx+4]; 0x66aedd7 mov [rsp+0x20],r8 |

Other calls in listing (not mapped — no [r15+off] in arg setup):
  - 0x67D6D70 (9 calls): have [rsp+] stores but use different argument sources
  - 0x5679DB0 (3 calls): use register arguments (rcx/rdx/r8/r9), no [rsp+] setup
  - All other 28 call targets: various other targets (E938xx0, E9357x0, etc.)

Run python tools/sigs/verify_oc.py docs/progress/oc_U-D8e.md and fix mismatches: 4 claimed RVAs, 4 matches, 0 mismatches. No fixes needed.

## RVA Claims for verify_oc.py

0x66aed3a  mov eax,[r15+0x184]
0x66aed41  mov ecx,[r15+0x188]
0x66aed48  mov rdx,[r15]
0x66aedd7  mov [rsp+0x20],r8