## NEXT
step 2

# M1f D3 pass — remaining submit/frame-path D2 claims (static proof rows + existing live data)

GOAL: Close checklist item M1f "Every D2 dossier gets a D3 pass: one live poll-only read or in-game check per claim that can be checked (never a debugger/breakpoint session: it crashed the game twice)" (docs/RENDER_CHECKLIST.md line 443). Entry state: PARTIAL = NOT DONE. Passes already live-done: 6ij (frame pair spacing 0xE749C0, counters Frame+0xDC57E8=514 items, frame counter Frame+0xE746D8=31416/31417, backbuffer {1920,1137} Frame+0xDC5808), 6il (IB/VB/layout records end-to-end for one draw), 6im (texture records), 6in (program/shader records), 6io (sort keys/sorted ids). Remaining: every other D2 claim — submit 0xe82e230, Encoder::submit 0xbc60740, draw executor 0xe821120, PSO builder 0xe81e860, draw flush/batcher 0xe81b720, endFrame 0xc270460, task dispatch 0xe9002e0, view-setup task. Static instruction proof rows (verbatim from rdis on Minecraft.Windows.exe 1.26.62.01, exe passed as argument only — never launched, no debugger, no breakpoints). Live claims cited to docs/data/live/*.txt per the live-data README.

D2 dossier RVA list: submit 0xe82e230; Encoder::submit 0xbc60740; executor 0xe821120; PSO builder 0xe81e860; draw flush 0xe81b720; endFrame 0xc270460; generate 0xc273420; task dispatch 0xe9002e0; view-setup task 0x568cdcc.

All RVAs relative to image base; exe = C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe. Size class rules: movups/movdqu/movaps = 16 bytes; qword/lea/loads of 64-bit = 8; dword/movss/movd = 4; word/movzx/movsx of 16-bit = 2; byte/movzx byte = 1. Offsets are offsets into the named object (Frame / RendererContext / per-view record / batcher / task object / header).

## Verified rows (verbatim `0xRVA  instr` lines; one row per distinct offset, all sites listed)
