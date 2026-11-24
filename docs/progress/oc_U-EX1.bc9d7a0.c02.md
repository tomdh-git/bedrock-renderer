## NEXT
DONE: Unit U-EX1.bc9d7a0.c02: LIFT CHUNK sub_bc9d7a0 part 3/5 range 0xbc9f890..0xbca1080.
Progress file created. Disassembly dumped to C:/Users/Atomi/AppData/Local/Temp/opencode/dis_c02.txt (1798 lines).
Step 1: Created src/client/features/render/native/bgfx/sub_bc9d7a0_chunk_c02.cpp + .h with CHUNK marker and #if 0 call quotes, ran liftcheck --range (OK).
Step 2: Wrote real C++ implementation into sub_bc9d7a0_chunk_c02.cpp with // 0xA..0xB range citations beside every block, preserved #if 0 call quotes (59 unique calls).
Step 3: Added 'Reversed source (chunk c02)' section to docs/functions/bc9d7a0.md.
Final liftcheck --range bc9d7a0 0xbc9f890 0xbca1080 --explain: LIFTCHECK OK.
All checks pass: coverage, call quotes, verify_oc (mismatch=0 no-such-instr=0).