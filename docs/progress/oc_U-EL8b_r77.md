## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression (RETRY #1)

Source checklist line (docs/RENDER_CHECKLIST.md:345): `- [ ] L8b Atlases (terrain, items), mipmaps and compression pending`.
Goal: close it — answer table (name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | [V]/[I]/[?]) + final `CLOSES?` line.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; exe is data, never launched; no game process touched by me. Read-only live captures under docs/data/live/*.txt were produced by the orchestrator; I only read them on disk. livemem reads (read-only VM_READ handle) only after an unsettled rdis finding, at most 12 calls, max 0x400 bytes per read.

Tags: [V] saw in disassembly or read-only live capture (RVA cited, verbatim line quoted); [V live] read-only live capture (cite file + line); [V via xref] xref.py tool result; [I] inferred (say from what); [?] unknown / not located.
Row rule: one annotated row per distinct offset; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied from rdis) | meaning ONLY if an instruction/string shows it, else '-' | tag. Sizes come from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No skipped offsets, no catch-all rows, no raw listing dumps, no catch-all abbreviation of remaining sites.
