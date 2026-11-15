# Unit U-SK6: Sky visitor 0x66560f0 — Sky tag-5 case entered at 0x66574d8

Per OPENCODE_BRIEF.md: STATIC ANALYSIS ONLY; exe is 1.26.62.01 Minecraft.Windows.exe; RVAs image-relative.
Every claim tagged [V] (seen in disassembly, cite RVA), [I] (inferred, say from what), [?] (unknown).
No description field offset, size, or meaning written unless seen in `[reg+off]` quotes.
Instruction-complete until it exits or joins an already-decoded region (that address named here).

## RESULT — EXIT REACHED
The Sky tag-5 case body entered at 0x66574d8 exits via `0x66578DB jmp 0x665D154` (sub_665d154, the null/not-ready exit epilogue named in docs/functions/66560f0.md section 1 [V]). Exit address named: 0x665D154.
Decode is instruction-complete from 0x66574d8 through the exit jmp at 0x66578DB (phases 1-6 cover every instruction in 0x66574d8..0x66578DB inclusive; no instruction skipped).
Post-exit fall-through block 0x66578E0..0x6657913 is present in the disassembly but is reached only from undecoded intra-function branch targets (0x6658445/0x665845A/0x66585B4/0x66585C9/0x66587CF/0x66587E4) [?] — not on the main flow to the exit.

BOUNDARY RULES (hard-earned in this unit):
- A `je/jne rel32` (`0F 8x`) is 6 bytes, not 2. A `lock dec dword ptr [r14+off]` is 5 bytes (REX prefix for r14). `mov rcx,[imm32]` absolute = 7 bytes. `jmp rel32` (E9) = 5 bytes.
- If a phase's first line is misaligned garbage (e.g. `sub [rax],dl`, `or [rdi],cl`, `mov [imm],eax`), back up to the clean instruction after the garbage and re-request 40 from there. Verify with a 3-instruction probe at the suspected boundary before trusting a phase.

Branch targets NOT yet decoded (intra-function): 0x6658445, 0x665845A, 0x66585B4, 0x66585C9, 0x66587CF, 0x66587E4, 0x6657717 (taken when cmp rbx,[rsi+0x158] is equal).
External targets: 0x665AEE8 = sub_665aee8 (Cubemap shared-body exit, already decoded by SK2b/SK2c [V]); 0x665B56E = LegacyCubemap material-resolve join (decode status [?], referenced from phase 2 `je 0x665B56E` [V] and LegacyCubemap E3 `jne 0x665b56e` [V]).
Register context: rdi = description pointer arg ([V] per frame map, used as rdx=rdi in allocator call 0x665767E); rsi = frame context (rdx of visitor); r14 = desc ptr at entry (`test r14,r14`, [V]); r15 = allocated pool entry base; rbx = pool cursor; r13 = value source [?] (used as u16 index `r13w` at 0x6657804 and allocator rdx at 0x66578EE, not set in phases 1-6).
Note on description fields: NO description `[reg+off]` field was dereferenced in phases 1-6 — only `test r14,r14` on the entry desc pointer. rdi is passed to the allocator but not dereferenced as description fields in this body. Description field reads (if any) occur only before 0x66574d8 (in the Sky case head) or not at all in this body [?].

## Phase 1 — 0x66574d8..0x6657586 (40 instr): shared_ptr retain/release preamble
`test r14,r14` -> null desc => `jmp 0x665AEE8` (joins already-decoded Cubemap shared-body exit sub_665aee8 [V]).
`r14=[rsi]` (frame-context field 0, [V]); `rax=[rbp+0x320]`; zero+store `[rbp+0x340]`; `rcx=[rax+8]` (=[rbp+0x320]+8) null => `0x6658445` [V].
Retain: `lock inc dword [rcx+8]`; `rbx=[rbp+0x348]`; `movups xmm0,[rax]` -> `[rbp+0x340]`; null rbx => `0x665845A` [V].
Release old rbx: `lock dec [rbx+8]`; `call [0xF99FFA0]` (sub_eea6040, rcx=rbx); `lock dec [rbx+0xC]`; second `call [0xF99FFA0]` (rax=[rbx]+8); `jmp 0x665845A` [V].
Second block (0x6657558, reached from elsewhere): `rax=[rax]; rax=[rax+0x18]; r15=[rax]`; null r15 => `0x665AEE8` [V].
`r15=[rsi]`; `rax=[rbp+0x320]`; zero `[rbp+0x340]`; `rcx=[rax+8]` null => `0x66585B4` [V].
Field reads: [rsi+0x00] qword (r14, [V]); [rbp+0x320] qword local holding a ctrl/shared_ptr (r14's new value, [V]); [rbp+0x340] 16 B (movups store, [V]); [rbp+0x348] qword (old ctrl, [V]); ctrl block fields +0x00 (vtable, `mov rax,[rbx]; mov rax,[rax]`), +0x08 (refcount, `lock inc/dec`), +0x0C (weakcount, `lock dec`) [V].
Callees: via [0xF99FFA0] = sub_eea6040 (release helper, [V]); targets 0x6658445 / 0x66585B4 / 0x665845A are intra-function, not yet decoded [?].

## Phase 2 — 0x665758C..0x665763C (39 instr): second compiler-duplicated retain/release block
(0x6657588/0x665758a were misaligned bytes of the phase-1 `je 0x66585B4`; real start 0x665758C [V].)
`lock inc dword [rcx+8]`; `r14=[rbp+0x348]`; `movups xmm0,[rax]` -> `[rbp+0x340]`; null r14 => `0x66585C9` [V].
Release r14: `lock dec [r14+8]`; `call [0xF99FFA0]` (rcx=r14); `lock dec [r14+0xC]`; `call [0xF99FFA0]` (rax=[r14]+8); `jmp 0x66585C9` [V].
Third block (0x66575E4): `rax=[rax]; rax=[rax+0x18]; r15=[rax]`; null r15 => `0x665B56E` [V].
`r15=[rsi]`; `rax=[rbp+0x320]`; zero `[rbp+0x340]`; `rcx=[rax+8]` null => `0x66587CF` [V].
Retain: `lock inc [rcx+8]`; `r14=[rbp+0x348]`; `movups xmm0,[rax]` -> `[rbp+0x340]`; null r14 => `0x66587E4` [V]; `lock dec [r14+8]` (last instr of phase 2, 0x6657636, 5 bytes due to REX prefix for r14; `jne 0x66587E4` at 0x665763B, 6 bytes rel32 -> next clean boundary 0x6657641) [V].
Field reads: [rbp+0x348] qword (old ctrl, [V]); [rbp+0x320] qword ctrl (rax, [V]); [rbp+0x340] 16 B (movups, [V]); ctrl block +0x00/+0x08/+0x0C as in phase 1 [V].
This block is instruction-identical in shape to phase 1's two blocks (compiler duplication of the shared_ptr retain/release, [I]).

## Phase 3 — 0x6657641..0x66576EC (40 instr): release r14 finish + allocate 0x58-byte entry
Finish release of r14: `mov rax,[r14]; mov rax,[rax]; call [0xF99FFA0]`; `lock dec [r14+0xC]; jne 0x66587E4`; `mov rax,[r14]; mov rax,[rax+8]; call [0xF99FFA0]` (rax=[r14]+8); `jmp 0x66587E4` [V].
Allocator call: `mov rcx,[0x1233E1A8]` (data_1233e1a8, allocator vtable/global [V]); `mov rax,[rcx]; mov rax,[rax+8]; mov rdx,rdi; call [0xF99FFA0]` -> rax [V]. `mov r15,rax; test rax,rax; jne short 0x665769C`; if null: `mov rcx,rdi; call 0x9BC830` (sub_9bc830, allocator/fallback [V]); `xor r15d,r15d` [V].
loc_665769c: copy 0x58 bytes from [r12+0x00..0x50] into [r15+r14+0x00..0x50]: `mov rax,[r12+0x50]` -> `[r15+r14+0x50]`; movups [r12+0x40]->[r15+r14+0x40]; [r12+0x00]->[r15+r14+0x00]; [r12+0x10]->[r15+r14+0x10]; [r12+0x20]->[r15+r14+0x20]; [r12+0x30]->[r15+r14+0x30] (6 movups covering 0x58 bytes) [V].
`cmp rbx,[rsi+0x158]`; `je short 0x6657717` [V]; `add r14,r15; add r14,0x58` [V]; `mov rdx,[rsi+0x150]` (41st instr, start phase 4) [V].
Field reads: ctrl block r14 +0x00/+0x08/+0x0C (release, [V]); [0x1233E1A8] qword (allocator, [V]); [r12+0x00/0x10/0x20/0x30/0x40/0x50] (6 qword/16B source reads for the 0x58-byte copy, [V]); [rsi+0x158] qword (pool end cursor, [V]); [rsi+0x150] qword (pool base, [V]). Writes: [r15+r14+0x00..0x50] (0x58-byte entry copy [W]); [r14] is read not written here.
Callees: [0xF99FFA0]=sub_eea6040 (release, [V]); allocator via [0x1233E1A8]->[+8] (rcx=rdi, [V]); 0x9BC830 sub_9bc830 (fallback alloc, rcx=rdi, [V]).

## Phase 4 — 0x66576F0..0x66577A1 (40 instr): memmove pool to new alloc + shrink old block + update base/cursor/end
`mov rdx,[rsi+0x150]` (pool base); `r8=rbx; sub r8,rdx` (size = cursor - base); `mov rcx,r15`; `call 0xEEC6DE0` (sub_eec6de0, memmove: dest=r15, src=old base, size=cursor-base) [V].
`r8=[rsi+0x158]; sub r8,rbx` (size = end - cursor); `rcx=r14; rdx=rbx; jmp short 0x6657727` [V].
loc_6657717 (taken when cmp rbx,[rsi+0x158] equal): `rdx=[rsi+0x150]; rbx-=rdx; rcx=r15; r8=rbx` [V].
loc_6657727: `call 0xEEC6DE0` (memmove #2: dest=r15, src=rbx, size=end-cursor) [V].
`rcx=[rsi+0x150]; test rcx,rcx; je short 0x665776C` [V].
`rdx=[rsi+0x160]; sub rdx,rcx` (rdx = end - base = pool size); `cmp rdx,0x1000; jb short 0x6657767` [V].
`rax=[rcx-8]` (read heap metadata at base-8 [V]); `rcx += 0xFFFFFFFFFFFFFFF8` (rcx = base-8 [V]); `rcx -= rax` [V]; `cmp rcx,0x20; jae 0x665D43A` (sub_665d43a, heap helper — also in Stars cold range [V]) [V].
`rdx += 0x27; rcx=rax` [V].
loc_6657767: `call 0xE935700` (sub_e935700, heap free/shrink [V]) [V].
loc_665776c: `[rsi+0x150]=r15` (update pool base [V]); `imul rax,[rbp+0x1C8],0x58` (count*0x58 from local [rbp+0x1C8] [V]); `rax+=r15; [rsi+0x158]=rax` (end cursor = r15 + count*0x58 [V]); `add rdi,r15; [rsi+0x160]=rdi` (cursor = rdi + r15 [V]).
`movzx r9d,byte ptr [rbp+0x540]` (read count-tag result saved earlier [V]); `mov rcx,[0x1233E1B0]` (data_1233e1b0 [V]); `mov rax,[rcx]; mov rax,[rax+0x10]` (41st instr, start phase 5) [V].
Field reads: [rsi+0x150] pool base ([V], read+written), [rsi+0x158] end cursor ([V] read+written), [rsi+0x160] cursor ([V] read+written), [rbp+0x1C8] count local ([V] read via imul), [rbp+0x540] count-tag byte ([V] read). Writes: [rsi+0x150], [rsi+0x158], [rsi+0x160] (pool base/end/cursor [W]).
Callees: 0xEEC6DE0 memmove (2 calls [V]); 0x665D43A sub_665d43a heap helper ([V]); 0xE935700 sub_e935700 heap free/shrink ([V]); allocator [0x1233E1B0]->[+0x10] (count-tag sub_eea6040 path, [V]).

## Phase 5 — 0x66577A5..0x6657867 (40 instr): count-tag call, index-array u16 push, magic multiply /0x58
`mov edx,r9d` (r9d = count-tag byte from [rbp+0x540]); `call [0xF99FFA0]` (sub_eea6040 count-tag #1 [V]); nop [V].
`mov qword ptr [rbp+0x348],0x4000` [V].
`mov eax,[rsi+0x158]; sub eax,[rsi+0x150]` (pool size bytes); `shr eax,3` (/8); `imul eax,0xFFFF8BA3` (magic multiply /0x58 [I]); `dec eax`; `mov [rbp+0x3EC],ax` (u16 index local [V]).
`mov rcx,[0x1233E1B0]; mov rax,[rcx]; mov rax,[rax+0x10]`; `mov dl,0x4A`; `call [0xF99FFA0]` (sub_eea6040 count-tag #2, dl=0x4A [V]); `mov [rbp+0x540],al` (save count-tag result [V]).
`mov rdx,[rsi+0x8A8]` (cursor); `cmp rdx,[rsi+0x8B0]` (end); `je short 0x6657812` [V].
`mov [rdx],r13w` (u16 index word write to [cursor] [V]); `add qword [rsi+0x8A8],2` (bump cursor [V]); `jmp short 0x6657829` [V].
loc_6657812 (array full): `mov rcx,rsi; add rcx,0x8A0` (rcx = rsi+0x8A0 array base [V]); `lea r8,[rbp+0x1E0]`; `call 0x1EF6F90` (sub_1ef6f90, u16 array grow helper, rcx=rsi+0x8A0 [V]); nop [V].
loc_6657829: `mov rcx,[0x1233E1B0]; mov rax,[rcx]; mov rax,[rax+0x10]`; `movzx edx,byte ptr [rbp+0x540]`; `call [0xF99FFA0]` (sub_eea6040 count-tag #3, dl=[rbp+0x540] [V]); nop [V].
`mov qword ptr [rbp+0x340],1` [V]; `mov eax,[rsi+0x8A8]; sub eax,[rsi+0x8A0]` (cursor - base); `shr eax,1` (/2); `dec eax`; `mov [rbp+0x350],ax` (u16 index local [V]).
`mov rcx,[0x1233E1B0]` (41st instr, start phase 6) [V].
Field reads: [rsi+0x158] end cursor ([V] read), [rsi+0x150] pool base ([V] read), [rbp+0x540] count-tag byte ([V] read+written), [rsi+0x8A8] u16 cursor ([V] read+written), [rsi+0x8B0] u16 end ([V] read), [rsi+0x8A0] u16 array base ([V] read), [rbp+0x3EC] u16 index ([V] write), [rbp+0x340] flag ([V] write), [rbp+0x350] u16 index ([V] write). Writes: [rsi+0x8A8] (cursor [W]), [rbp+0x3EC]/[rbp+0x350]/[rbp+0x340]/[rbp+0x540] ([W]). U16 index word write `[rdx]=r13w` where rdx=[rsi+0x8A8] [V].
Callees: [0xF99FFA0]=sub_eea6040 (count-tag, 3 calls [V]); 0x1EF6F90 sub_1ef6f90 (u16 array grow, [V]).

## Phase 6 — 0x665786E..0x6657913 (40 instr): 0xC8 record append into [rsi+8] + count-tag + EXIT jmp 0x665D154
`mov rax,[rcx]; mov rax,[rax+0x10]`; `mov dl,0x4A`; `call [0xF99FFA0]` (sub_eea6040 count-tag, dl=0x4A [V]); `mov [rbp+0x540],al` [V].
`mov rax,[rsi+8]` (pass-object cursor base [V]); `cmp rax,[rsi+0x10]` (pass-object end [V]); `je short 0x66578AC` [V].
`lea rdx,[rbp+0x340]`; `mov r8d,0xC8`; `mov rcx,rax`; `call 0xEEC6EC0` (sub_eec6ec0, 0xC8 record append: rcx=dest=[rsi+8], rdx=&[rbp+0x340], r8=0xC8 [V]); `add qword [rsi+8],0xC8` (bump cursor [V]); `jmp short 0x66578BF` [V].
loc_66578ac (record full): `lea r8,[rbp+0x340]`; `mov rcx,rsi`; `mov rdx,rax` (=old [rsi+8] base); `call 0x5ABA6D0` (sub_5aba6d0, 0xC8 record grow/free, rcx=rsi [V]); nop [V].
loc_66578bf: `mov rcx,[0x1233E1B0]; mov rax,[rcx]; mov rax,[rax+0x10]`; `movzx edx,byte ptr [rbp+0x540]`; `call [0xF99FFA0]` (sub_eea6040 count-tag, dl=[rbp+0x540] [V]); nop [V].
`jmp 0x665D154` (EXIT — sub_665d154 null/not-ready exit epilogue [V]; EXIT ADDRESS = 0x665D154) [V].
Post-exit fall-through (reached only from undecoded branch targets [?]): 0x66578E0 `mov rcx,[0x1233E1A8]`; `mov rax,[rcx]; mov rax,[rax+8]`; `mov rdx,r13`; `call [0xF99FFA0]` -> rax [V]; `mov rbx,rax`; `test rax,rax`; `jne short 0x665790C`; `mov rcx,[rbp+0x40]`; `call 0x9BC830` (sub_9bc830, rcx=[rbp+0x40] [V]); nop; `xor ebx,ebx`; loc_665790c `mov rax,[rbp+0x540]` (40th instr).
Field reads: [rsi+8] pass-object cursor base ([V] read+written), [rsi+0x10] pass-object end ([V] read), [rbp+0x540] count-tag byte ([V] read+written), [rbp+0x340] local ([V] read), [rbp+0x40] local ([V] read, post-exit block), [0x1233E1B0]->[+0x10] count-tag object ([V] read). Writes: [rsi+8] (cursor [W]), [rbp+0x540] ([W]). U16 index write `[rdx]=r13w` referenced in phase 5.
Callees: [0xF99FFA0]=sub_eea6040 (count-tag, 2 calls in this phase [V]); 0xEEC6EC0 sub_eec6ec0 (0xC8 record append [V]); 0x5ABA6D0 sub_5aba6d0 (0xC8 record grow/free [V]); 0x9BC830 sub_9bc830 (allocator, post-exit block [V]).

## Description fields touched (offset, size, direction, meaning, tag)
NONE read as `[reg+off]` description fields in phases 1-6 — only `test r14,r14` on the entry desc pointer (rdi/r14 = desc ptr, null-checked at 0x66574d8 [V]); rdi is passed as rdx to the allocator (0x665767E) but not dereferenced as description fields [V]. Any description field reads occur only before 0x66574d8 (Sky case head) [?].

## Callees (rva, what it is, tag)
- [0xF99FFA0] = sub_eea6040 (count-tag/release hook, rcx=obj, dl=0x4A or byte) [V] — many calls
- sub_665aee8 at 0x665AEE8 (Cubemap shared-body exit, already decoded [V])
- 0x665B56E (LegacyCubemap material-resolve join, status [?])
- 0xEEC6DE0 (memmove, 2 calls) [V]; 0xEEC6EC0 (0xC8 record append) [V]; 0x5ABA6D0 (0xC8 record grow/free) [V]
- 0x665D43A (sub_665d43a heap helper, Stars cold range) [V]; 0xE935700 (sub_e935700 heap free/shrink) [V]
- 0x9BC830 (sub_9bc830 allocator/fallback) [V]; 0x1EF6F90 (sub_1ef6f90 u16 array grow) [V]
- Allocator globals: [0x1233E1A8]->[+8], [0x1233E1B0]->[+0x10] [V]

## OPEN
- Whether 0x665D154 (sub_665d154 exit) is itself an already-decoded region: NOT listed in the coverage table [?]. Named here as the exit address.
- Description field reads for Sky tag-5: none in this body [?]; check the Sky case head (before 0x66574d8) and docs/functions/66560f0.md companion.
- Post-exit block 0x66578E0.. reachable only from undecoded intra-function targets [?].
- r13 value source [?]; meaning of count-tag call (sub_eea6040 dl=0x4A) and [rbp+0x540] [?].
