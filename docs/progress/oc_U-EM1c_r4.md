## NEXT
DONE

# Unit U-EM1c — M1c Dossiers (D2): status + verified field map (GraphicsTasks Execute 0xc25fc50)

Canonical output file for unit U-EM1c (no other file). Step 1 created it with `## NEXT` / `step 2`; line 2 is flipped to `DONE` only after `python tools/delegate.py check docs/progress/oc_U-EM1c.md` exits 0.

## Source and constraints

- Binary: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01), RVAs relative to image base. Treated as data only: passed to rdis as an argument, never launched, never a shell command.
- Static analysis only. No build, no game launch/attach, no debugger/Cheat Engine/injector.
- No edits to HookManager.cpp, Sigs.json, CMake, existing hook registrations, CLAUDE.md, docs/BGFX_MAP.md, docs/RENDER_CHECKLIST.md.
- Only file created: docs/progress/oc_U-EM1c.md (this note).
- Every `0xRVA  instr` line below is copied verbatim from rdis `dis` output and verified by tools/sigs/verify_oc.py.

## M1c D2 status (census + prior rounds)

- Context::init 0xbc63690 D2 [oc_U-EM1c_r2.md]; Context::frame 0xbc66de0 D2 [progress text]
- Encoder::submit family D2: submit docs/functions/bc60740.md, EncoderImpl::submit fully reversed [6fd]
- Frame::sort fully reversed [6fd]; submit 0xe82e230 D2
- executor 0xe821120 + wrapper D2; PSO builder D2; endFrame 0xc270460 D2
- GraphicsTasks Execute 0xc25fc50 D2; GraphicsTasks Render lambda 0xc267200 D1
- dispatch 0xe9002e0 D2
- generate 0xc273420 D1 (not D2)
- shutdown sequence 0xbc660a0 D2 [oc_U-EM1c_r1.md]; vtable slots 39-45 D2 [oc_U-EM1c_r3.md]
- Census: 838 functions on direct-call frame path, 22 at D2 [docs/data/frame_path_functions.tsv, tools/sigs/closure.py]

## Field map: GraphicsTasks Execute 0xc25fc50 (size 0x14a, D2)

`this` = rcx = rsi at entry. Body range 0xc25fc50..0xc25fd9a. One annotated row per distinct field offset accessed (this-relative + state globals; stack [rbp+/rsp+] locals excluded per prior-round convention), all sites listed, size from the instruction, verbatim rdis line.

| offset | size | site | `0xRVA  instr` | meaning |
|---|---|---|---|---|
| 0x5 | 1 | R 0xc25fcca, W 0xc25fce3 | `0xc25fcca  movzx edx,byte ptr [rsi+5]`; `0xc25fce3  mov byte ptr [rsi+5],0` | per-frame flag byte at this+0x5 read, then cleared [V] |
| 0x58 | 8 | R 0xc25fc79 | `0xc25fc79  mov rdx,gs:[0x58]` | TLS array pointer read from TEBA+0x58 [V] |
| 0x4 | 4 | R 0xc25fc86 | `0xc25fc86  cmp eax,[rcx+4]` | thread-slot field +4 compared against init flag [V] |
| 0x68 | 8 | R 0xc25fcc0 | `0xc25fcc0  mov rcx,[rsi+0x68]` | this+0x68 passed to task runner sub_c25fe20 [V] |
| 0x78 | 8 | R 0xc25fce7 | `0xc25fce7  mov rcx,[rsi+0x78]` | this+0x78 passed to task runner sub_c25fe20 [V] |
| 0x140 | 4 | R/W 0xc25fcdd | `0xc25fcdd  xchg [rsi+0x140],eax` | atomic exchange on this+0x140 [V] |
| 0x12AEB928 | 4 | R 0xc25fc6d, R 0xc25fd26 | `0xc25fc6d  mov eax,[0x12AEB928]`; `0xc25fd26  cmp dword ptr [0x12AEB928],0xFFFFFFFF` | init/thread-flag global read and compared to 0xFFFFFFFF [V] |
| 0x128767C8 | 4 | R 0xc25fc73 | `0xc25fc73  mov ecx,[0x128767C8]` | thread-index global read for TLS slot selection [V] |
| 0x12AE1748 | 8 | R 0xc25fcd0 | `0xc25fcd0  mov rcx,[0x12AE1748]` | state global read, passed to Context::frame sub_bc65800 [V] |

## Phase summary (from the same verified listing)

1. 0xc25fc50..0xc25fc8c: prologue, `this`=rsi, read init flag global 0x12AEB928, thread index 0x128767C8, TLS base gs:0x58, compare slot+4 against flag; if `jg` go to cold path at 0xc25fd1a [V].
2. 0xc25fc92..0xc25fd19: hot path — clear locals, call sub_39a7d40 store byte to [rbp+0x20], read this+0x68 → task runner sub_c25fe20, read byte this+0x5, double it, call Context::frame sub_bc65800 with global 0x12AE1748, atomic xchg this+0x140, clear byte this+0x5, read this+0x78 → task runner sub_c25fe20, branch on [rbp+0x20]==1, optionally call sub_77a2500, epilogue ret [V].
3. 0xc25fd1a..0xc25fd95: cold path — call sub_e938cb0, compare global 0x12AEB928 to 0xFFFFFFFF, if equal build a task (lea string 0xF5D1019, movups 0xF2BEFB0, mov dword 0x228B22, call sub_2fe330, sub_e935740 with sub_c262390, sub_e938d70) then jump back to hot path [V].

## CLOSES?

NO — the M1c item ("every structural function of L1-L3 at D2") is not met by what exists on disk now. Single blocking fact: generate 0xc273420 is D1 (not D2) and GraphicsTasks Render lambda 0xc267200 is D1; this unit only verifies Execute 0xc25fc50's field map. The verified field map itself is complete with [V] rows.

## TOOL REQUESTS

None — used rdis dis 0xc25fc50 and tools/sigs/verify_oc.py.
