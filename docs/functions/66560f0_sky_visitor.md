# Sky visitor 0x66560f0: per-case phase tables (merge of opencode units U-SK1..U-SK3c)

Companion of docs/functions/66560f0.md (dispatch, strings, struct list). Exe 1.26.62.01, RVAs image-relative. Evidence rule: only instruction
quotes that match the exe count. Source files: docs/progress/oc_U-SK1{,b,c,d,e}.md (Stars), oc_U-SK2{,b,c}.md (Cubemap, EndSky/LegacyCubemap),
oc_U-SK3{,b,c}.md (SkyAmbientSamples, VolumetricFog). Prose in those files is [I] unless re-checked here ("rdis-checked" = re-run by the merge agent).
Tags: [V] instruction seen, [I] inference, [?] unknown.

## 0. Coverage measured by the merge agent (script: per quoted `RVA instr` vs `rdis dis`, text-normalised)
Number of exe instructions in range that appear with identical text in the unit files (union of the unit's files):
| Range | Case | exe instr | text-matched | Not matched |
|---|---|---|---|---|
| 0x6659615..0x665aee8 | Cubemap shared body (also reached by Legacy/Celestial/Sky paths) | 1194 | 1189 | 0x6659e08 `mov r8,[0x129F9FE0]`, 0x6659e0f `mov r9,rdx`, 0x6659e12 `mov rcx,rax` (SK2c cut Phase at 0x6659e06), 0x665a9ec `jmp short 0x665AA02` (after `add qword [rsi+0x8A8],2`), 0x665abf3 `movups xmm2,[rbp+0x38B]` (SK2c wrote a garbled line) [V rdis] |
| 0x6656b2b..0x6656d4d | LegacyCubemap/EndSky material resolve | 110 | 110 | none |
| 0x665708b..0x665803c | SkyAmbientSamples body | 836 | 833 | 0x6657ee5 `mov [rdx],ax` (3-byte instr cut in SK3), part of 0x6657ee8 `add qword [rsi+0x8A8],2`, 0x6657ef0 `jmp short 0x6657F09` [V rdis] |
| 0x66569b1..0x6657e4a | VolumetricFog | 1031 | 1031 | none |
| 0x665b624..0x665c269 | Stars join 3 | 637 | 637 | none |
| 0x665c269..0x665cf64 | Stars joins 1/2 + shared body | 765 | 765 | none |
| 0x665cf64..0x665d7e5 | cold range (Stars/Legacy/Sky resource lookups) | 412 | 412 | none |
NOT covered by any opencode unit: Stars case head (0x6656812..0x66568xx), Stars base draw 0x6658ffc..0x6659340 and PBR twin 0x66590aa..0x66592c4
(statement level only in ext_particle_sky_callees.md; CORRECTION: 0x6658ffc..0x6659340 is the EndSky (tag 3) tail, reached by fall-through from 0x6658ff5, not a Stars draw; Stars/Sky/Celestial/EndSky are now decoded in 66560f0_sky_cases.md), Sky (tag 5, 0x66574d8) and CelestialBody/SunMoon (tag 7, 0x6656516 head, 0x665935d body)
heads, EndSky (tag 3) head 0x665649c..0x6656516 and its body at 0x6656bec, Atmosphere 0x6656d4b join. Celestial is therefore not documented here.

## 1. Frame/argument map (shared by all cases) [V from the unit files, rdis-checked at the quoted sites]
rdi = description pointer (r8 of the visitor, `[r8]`), rsi = frame context (rdx), r14/r15 = shared_ptr/mesh temporaries, rbp = frame (locals up to +0x540).
Frame context reads: `cmp dword [rsi+0x70],1` selects the PBR material (0x6656388 Cubemap, 0x665685c Stars, 0x665621a Legacy), `[rsi+0x40]`, `[rsi+0x68]` are the resource-cache
arguments (0x6656391, 0x66563a7), `[rsi+0x10]` + 0x9D0 is the pass-object allocation argument (0x66570a2, 0x66569b8..0x66569bd, 0x665c28b..0x665c290).
Pass object: `call 0x5ABA5C0` (ThreadLocalObject::get, rcx = 0x9D0 + [rsi+0x10]) -> rax, rsi := rax in the push tails (0x66570a6/0x66570ac, 0x6656a0f/0x6656a14, 0x665bb55..0x665bb64).
All cases leave through `jmp 0x665D124` (epilogue; SkyAmbientSamples at 0x6657ff4, Cubemap at 0x665aeef after `mov rsi,[rbp+0x328]` 0x665aee8 [V rdis]) or the null/not-ready exits 0x665d11d / 0x665d154.

### 1.1 Pass-record writes common to the sky cases (instruction level, role names [I])
Written into the pass object (rsi after the 0x5ABA5C0 call). Offsets are the pass-object field offsets seen in `[rsi+X]` quotes:
| Pass +off | Access seen | Quote | Meaning |
|---|---|---|---|
| +0x648 / +0x650 | cursor/end, 8-byte stride, `call 0x675FB30` push helper (rcx=rsi+0x648, rdx=&[rbp+0x428]) | oc_U-SK1.md join-2 phase 3 (`call 0x675FB30`, rdx=&[rbp+0x428]), SK2c | pool 0x648 push [I: DrawItem pool, see docs/functions/66560f0.md callee table] |
| +0x750 / +0x758 / +0x760 | stride 0x58 store: u32 +0x10, 16 B +0x00, byte +0x14, 4 floats +0x18..+0x24, 3x16 B at +0x28/+0x38/+0x47 then `add qword [rsi+0x758],0x58`; full => `call 0x6760A80` (rcx=rsi+0x750) | oc_U-SK1.md join-2 phase 6 (0x665c6a9..0x665c747) | 0x58-byte entry pool [I] |
| +0x768 / +0x770 / +0x778 | stride 0x88: [rbx]=[rbp+0x3A0], `call 0xE869FF0`(rbx+8), [rbx+0x80]=[rbp+0x430], `add qword [rsi+0x770],0x88` (0x665bd4a [V rdis]); full => `call 0x6760710` (0x665bd68) | SK1b phase 1 | 0x88-byte entry pool [I] |
| +0x780 / +0x788 | `lea rcx,[rax+0x780]; call 0x675F3B0` | SK1 join-2 phase 3 | pool 0x780 push [I] |
| +0x858 / +0x860 / +0x868 | byte counter: `inc [rsi+0x860]` else `call 0x6760E60` (rcx=rsi+0x858) (0x665c627..0x665c64d [V rdis]) | SK1 | byte pool [I] |
| +0x8A0 / +0x8A8 / +0x8B0 | u16 array: `mov [rdx],ax`, `add qword [rsi+0x8A8],2` else `call 0x1EF6F90` (rcx=rsi+0x8A0) (0x6657ee5..0x6657ef2 [V rdis], 0x665a9e4..0x665a9fc) | SK1/SK2c/SK3 | u16 index array [I] |
| +0x008 / +0x010 | 0xC8-byte record append: `mov r8d,0xC8; call 0xEEC6EC0` into [rsi+8], `add [rsi+8],0xC8`; full => `call 0x5ABA6D0` | SK3 phases 12/20/21 | the 0xC8 DrawItem stream [V: matches U-PASS3] |
| +0x150 / +0x158 / +0x160 | stride 0x58 record table: `add qword [rsi+0x158],0x58` (0x6656adf [V rdis]), grow with memmove `call 0xEEC6DE0`, free `call 0xE935700` | SK3 phases 9-11, 22-23 | the VolumetricFog / SkyAmbientSamples record table [I] |
| +0x540 / +0x548 / +0x550 | stride 0x130 record table (epilogue loop: `add r14,0x130`, `mov r15,[r14+0x38]; lock dec [r15+8]` 0x6657dd0..0x6657de5) | SK3b phase 48 | 0x130-byte record table [I] |
| +0x0B0 / +0x0B8 | cursor/end of an entry list (SkyAmbientSamples phase 1: `r15=[rsi+0xB0]`, `cmp [rsi+0xB8]`) | SK3 | list walked with the /0x58 and /0x130 magic multiplies [I] |
"Count tag" call: `mov rcx,[0x1233E1B0]; mov rax,[rcx]; mov rax,[rax+0x10]; mov dl,0x4A; call [0xF99FFA0]` (= sub_eea6040) repeated around each push (0x665c60a..0x665c620 [V rdis]); result byte saved to [rbp+0x540]. Role [?] (a per-push stat/fence hook); not interpreted.
Per-push index words are computed with magic multiplies on cursor deltas: `* 0xFFFF8BA3` (/0x58 stride... [I]), `* 0xFFFF8E39`, `* 0xFFFFF0F1`, `* 0x2E8BA2E8BA2E8BA3`, `* 0x86BCA1AF286BCA1B` ([I] = division by the stride; recomputed value stored in `[rbp+0x208/0x20A/0x20C/0x222/0x3EC/0xA8]` as u16).

## 2. Case Cubemap (tag 2): head 0x66562d5, shared body 0x6659615..0x665aee8
| Phase | RVA range | What it does | Evidence |
|---|---|---|---|
| H1 | 0x66562d5..0x6656313 | `r14=[rdi]` (null => 0x665d154); TLS slot checks (cold branches 0x665d453, data_129c13c0); `lock inc word [r14+0x10]`; `movzx eax,byte [r14+0x12]`, `test al,1`, `je 0x665d154` | [V rdis-checked] |
| H2 | 0x6656319..0x66563f2 | three more TLS slot checks; `cmp dword [rsi+0x70],1` -> `rdx = "Cubemap"` (0xF2BE568) or `"CubemapHDRi"` (0xF2BE588) via cmove; `r9=[rsi+0x40]`, `rcx=[rsi+0x68]`; key name block at [rbp+0x340]/[rbp+0x348]; `call 0x67D6D70` (rdx=&[rbp+0x330]) | [V rdis-checked]; 0x67d6d70 = resource lookup [I] |
| H3 | 0x66563f7..0x6656441 | `r14=[rbp+0x330]`, `r15=[r14]` (null => 0x665d11d); `cmp byte [r15+0x10],1` else 0x665d11d (loaded flag); `rax=[r14+8]`; null => `je 0x6659615` | [V rdis-checked] |
| H4 | 0x6656447..0x6656497 | retain ctrl `lock inc [rax+8]`, `rax=[[r14]+0x18]`, `r15=[rax]`, release old `r14` (dec [r14+8]/[r14+0xC] + `call [0xF99FFA0]`), `jmp 0x665961f` | [V rdis-checked] |
| C1..C2 | 0x6659615..0x6659779 | owner chain `[r14]->[+0x18]->[0]` (null => 0x665d11d); shared_ptr assign at [rbp+0x340]; `call 0xE86B370` (material getter, rdx=[rax+0x170]); `call 0x66A08B0` (mesh header); `cmp [rsi+0x70],2` -> `call 0xBBD7F70` | oc_U-SK2.md C1-C2 (SK2 verified 349/351) |
| C3 | 0x6659779..0x6659815 | `call 0x6693320` (rcx=&[rbp+0x30], rdx=rsi, r9d=r14d); flags `test dword [rdi+0x6C],0xFFFFFFFD; setne; shl eax,9; add eax,0x200` (0x66597a8..0x66597b5); `lea rcx,[rdi+8]`; mesh item count `(([r15+0x60]-[r15+0x58])>>2)*0xAAAAAAAB`-style (reads on r15 = mesh, not rdi) | SK2 + SK2b fix (0x6659815/17 are garbage; real 0x6659818 `mov rcx,r15`) |
| C4..C6 | 0x6659818..0x6659a75 | `call 0x4DEDD00` (mesh bind), 3 TLS slot checks, two table lookups over 16-byte entries (feature table [rbp+0x88], u16 count [rbp+0x92]) -> `call 0x5679DB0` (UniformBlock::setUniform {idx,1}); LegacyCubemap byte tests `+0x3E`/`+0x3F` at 0x66599a8..0x66599b4 and matrix pointer `[rdi+0x18]` at 0x66599be | SK2 C4-C6 |
| 1..49 | 0x6659a75..0x665aee8 | DrawState constants (`mov dword [rbp+0x344],N; byte [rbp+0x348]=7; dword [rbp+0x34C]=..` etc.), UB copy `call 0xE869FF0(&[rbp+0x3A8], rbx)`, 4-way payload variants selected by byte [rbp+0x518], Cubemap block copy at 0x665a205..0x665a261, then shared SKY-PUSH tail (`0x5ABA5C0` then `0x675F3B0` ... region 0x665a8e5), exit `0x665aee8 mov rsi,[rbp+0x328]; 0x665aeef jmp 0x665D124` | oc_U-SK2b + oc_U-SK2c (915/916) |
Description fields read (offset, size, meaning, tag):
- +0x00 qword texture/resource ptr, read at 0x66562d5 and 0x665973d [V]; the pointee: u16 at +0x10 (lock inc, 0x6656306) and byte +0x12 bit0 (0x665630c) [V]. NOTE: docs/functions/66560f0.md lists "desc+0x10 word, +0x12 byte"; the exe shows these are fields of `*desc`, not of the description. Correction recorded here.
- +0x08 address taken only (`lea rcx,[rdi+8]` 0x66597ba, `lea r8,[rdi+8]` 0x6659d7c); never dereferenced in the decoded range [V]
- +0x10..+0x4F four vec4 (0x665a22a/0x665a235/0x665a240/0x665a24d, also second shape 0x665a411..0x665a434) copied to [rbp+0x4E0..0x510]; guard byte +0x52 == 1 (0x665a220) else second shape [V]
- +0x50 u16 (0x665a261 `mov di,[rdi+0x50]`; second shape 0x665a448) [V]
Written to the pass record: the vec4 block lands at [rbp+0x4E0..0x51F] with [rbp+0x520]=0 (0x665a22e..0x665a25a), then DrawState: `[rbp+0x344]=0 (dword), [rbp+0x348]=7 (byte), [rbp+0x34C]=2, word [rbp+0x350]=1, byte [rbp+0x352]=2, dword [rbp+0x354]=0` (0x665a27f..0x665a2aa) [V rdis]. Mapping of these DrawState words to bgfx state is [?].
Callees: 0x56D55E0 (0x665a21a, rcx=r14, rdx=&[rbp+0x340], r8=data_129f9c30, r9=desc+0x10; role [?]), 0x66A6190 (0x665a279, mesh-object builder, rcx=&[rbp+0x1E0], rdx=[rsi], r8=rbx+0x358), 0x6693320, 0x4DEDD00, 0xBBD7C70 (0x665980b), 0x66A08B0, 0xE86B370, 0xE869FF0, 0x5679DB0, 0x5ABA5C0, 0x675F3B0, 0xEEC6EC0, 0xE935700.

## 3. Case LegacyCubemap (tag 4) and EndSky resource resolve
Head 0x66561cc: TLS checks (data_129f9c50, data_129f9c68), `r15d=[rsi+0x70]; cmp r15d,1` -> "LegacyCubemapForwardPBR" (0x6656241) vs "LegacyCubemap" (0x6656af3 `lea rax,[0xF57DBCE]`, `[rbp+0x1E8]=0xD`) [V rdis]; the head reads byte +0x3E (0x6656221).
| Phase | RVA range | What it does | Evidence |
|---|---|---|---|
| E1 | 0x6656b2b..0x6656bec | `call 0x675E440`; `rbx=[rbp+0x330]` (null => 0x665d11d); TLS slot data_129ca5e0; `cmp byte [rbx+0x10],1; jne 0x665d11d`; retain [rax+8], release old rbx, `jmp 0x665744e`; `lea r12,[rbp+0x120]; mov eax,0xF` | oc_U-SK2 E1 (instruction-complete, 110/110 text match) |
| E2 | 0x6656bec..0x6656c54 | `[rbp+0x130]=r15`, `[rbp+0x138]=0xF`; `call 0xEEC6EC0(&[rbp+0x120], r14, r8=r15)`; `byte [r12+r13]=0`; TLS data_129f9d00; `r9=[rsi+0x40]`, `rcx=[rsi+0x68]`; SSO test `cmp qword [rbp+0x138],0x10` | E2 |
| E3 | 0x6656c54..0x6656d22 | args at [rbp+0x1E0]/[rbp+0x1E8], `call 0x675E440(&[rbp+0x1E0], &[rbp+0x320], r8=[0x129F9CF0])`; `r14=[[rbp+0x320]]`; `cmp byte [r14+0x10],1; jne 0x665b56e`; retain/release as E1 | E3 |
| E4 | 0x6656d22..0x6656d4d | finish release of r14 (dec [r14+0xC] etc.), `jmp 0x66575ee`; next instr at 0x6656d4b is the Atmosphere join (`xor eax,eax; mov rcx,[rdi+0xD8]`) | E4 |
Only frame-context fields are read in this range ([rsi+0x40], [rsi+0x68]); no description field. This range is the string/material resolve for the "LegacyCubemap" material (and the generic mesh-material helper shared with EndSky), NOT an EndSky description reader. The EndSky head (tag 3, 0x665649c..0x6656516: "EndSkyForwardPBR"/"EndSky" at 0x66564b2/0x66564b9, size r13d = 0x10 or 6, allocator [0x1233E1A8]) was not decoded by the units: [I] from docs/functions/66560f0.md only.
LegacyCubemap description fields read in the shared body (offset, size, meaning, tag): +0x3E byte (0x66599a8, `test al,al; je 0x6659b9b`), +0x3F byte (0x66599b4 `cmp byte [rdi+0x3F],1; jne 0x6659edd`), +0x18 qword POINTER to four vec4 (0x66599be: `movups xmm6..9,[rax],[rax+0x10],[rax+0x20],[rax+0x30]` -> [rbp+0x1E0..0x210], `[rbp+0x220]=0`), +0x3C u16 (0x6659a05, 0x6659bec), +0x30 qword (0x6659b9b movsd), +0x38 dword (0x6659ba0 movss) when +0x3E==0 [V rdis-checked 0x66599a8..0x66599e4, 0x6659b9b..0x6659bd8]. The body then sets DrawState `[rbp+0x344]=3` (0x6659a09) for this path versus 0 for the Cubemap block [V]. Attribution of the +0x3C/+0x30/+0x38 reads to tag 4 rather than another case sharing the body is [I] (layout agrees with the producer 0x660b1a0 stores listed in Descriptions.h).

## 4. Case SkyAmbientSamples (tag 10): head 0x6656983, body 0x665708b..0x665803c
Description reads [V rdis-checked at 0x6656983..0x66569ac, 0x665708b..0x6657096]: `+0x00 u16` (movzx ebx -> [rbp+0x1E0]), `+0x10 qword` (shared-ptr ctrl: null => 0x6657088, else `lock inc dword [rax+8]`, r12=[rdi+0x10]) and `+0x08 qword` (`mov r14,[rdi+8]` -> [rbp+0x1E8]); r12 -> [rbp+0x1F0].
| Phase | RVA range | What it does | Evidence |
|---|---|---|---|
| 1 | 0x665708b..0x6657160 | save desc ptr pair, `ecx=0x9D0; add rcx,[rsi+0x10]; call 0x5ABA5C0`; `rsi=rax`; zero [rbp+0x340..0x3FF] (13 movaps) + qword; count-tag call (dl=0x4A) -> edx; entry list `r15=[rsi+0xB0]` vs `[rsi+0xB8]` | SK3 ph.1 |
| 2-4 | 0x6657160..0x66572f6 | index from cursor delta (`/0x58` magic 0x2E8BA2E8BA2E8BA3, clamp), hash call, 32-byte aligned bucket alloc (`[rbx-8]=base`), empty-list index path | SK3 ph.2-4 + SK3b/SK3c fixes at 0x665721c..0x6657387 (garbled lines in SK3 replaced by the real lines in oc_U-SK3b.md) |
| 5-8 | 0x66572f6..0x665756x | record store, release blocks (retain [rcx+8], release rbx via `[0xF99FFA0]`) | SK3 ph.5-8 + SK3c (10 neighbourhoods all re-decoded, SK3c: none of SK3's quoted RVAs at those spots were real boundaries) |
| 9-12 | 0x6657670..0x66578ff | small-index insert, memmove (`call 0xEEC6DE0`), growable stride-0x58 buffer at [rsi+0x150..0x160], word array [rsi+0x8A0..0x8B0], 0xC8 record append into [rsi+8] (`mov r8d,0xC8; call 0xEEC6EC0`) | SK3 ph.9-12 |
| 13-17 | 0x665790c..0x6657d9f | record write at stride 0x130 ([r13+0x30..0x6C] copy loop, `r8d=0xAD` copy at +0x70, [r12+0x120]), loops 1-3 | SK3 ph.13-17 + SK3c |
| 18-21 | 0x6657da4..0x665803c | epilogue release loop over 0x130-stride records (`lock dec [r15+8]`), heap shrink (`cmp rdx,0x1000`, `call 0xE935700`), u16 write `mov [rdx],ax`/`add qword [rsi+0x8A8],2`, 0xC8 record append, final release, `0x6657ff4 jmp 0x665D124` | SK3 ph.18-21 + SK3b ph.48 |
Pass-record side: this case appends exactly one 0x58-byte entry (VolumetricFog) / one 0xC8 DrawItem-style record per execution and bumps u16 index arrays; there is NO draw-state/material lookup in this case [V: no material string reference in 0x665708b..0x665803c]. Meaning of "samples" as sky-light sample data is [I].
Resolved ambiguity of the dossier: the dossier says "ref on ctrl block [desc+0x10]" - confirmed [V].

## 5. Case VolumetricFog (tag 8): 0x66569b1..0x6657e4a (continues into the SkyAmbientSamples body)
Description fields read [V rdis-checked at 0x66569b1..0x6656a0f]: `+0x00 u16` (0x6656a03), `+0x04/+0x14/+0x24/+0x34` four vec4 (0x66569d7..0x66569e3), `+0x44` vec4 (0x66569cc), `+0x54` qword (0x66569c1). These 0x58 bytes minus the head word are laid out at [rbp+0x1E4..0x23B]; later phases read single floats at +0x08/+0x0C/+0x10 from the description (`movsd xmm2,[rdi+8]`, `movss xmm1,[rdi+0xC]`, `movss xmm2,[rdi+0x10]`, `subss`, clamp against `[0xEEC8060]`, SK3 ph.26-27 around 0x6656dff..0x6656eda) [V quotes; attribution to rdi not re-checked in the exe here, [I]].
| Phase | RVA range | What it does | Evidence |
|---|---|---|---|
| 22 | 0x66569b1..0x6656a99 | copy of desc into [rbp+0x1E0..0x23B], `call 0x5ABA5C0`, zero 0x70-byte local | SK3 ph.22 |
| 23 | 0x6656a99..0x6656aec | `cmp rbx,[rsi+0x160]` -> `je 0x6657173` into SkyAmbientSamples phase 2; else the 0x58-byte store `[rbx+0x50]=[r12+0x50]`, 4+1 movups, `add qword [rsi+0x158],0x58`, `jmp 0x6657797` [V rdis 0x6656aa0..0x6656ae7] | SK3 ph.23 |
| 24-25 | 0x6656af3..0x6656d0a | the "LegacyCubemap" material string ref (0x6656af3) and string SSO select, `call 0x675E440` | SK3 ph.23-25 (garbled 0x6656b81/0x6656d0a..0x6656d0f replaced per SK3b) |
| 26-29 | 0x6656d0f..0x66570ac | release, fog scratch copy, record header fields, second 0x9D0 allocation, record write, `jmp` into SkyAmbientSamples phase 1 | SK3 ph.26-29 |
| 30-47 | 0x66570ac..0x6657da4 | instruction-identical to SkyAmbientSamples phases 1-18 (shared code) | SK3 ph.30-47 |
| 48 | 0x6657da4..0x6657e4a | tail: release loop over `[rsi+0x540]..[rsi+0x548]` stride 0x130, heap check | oc_U-SK3b.md ph.48 |
Open: the exact separation between "VolumetricFog record" and "SkyAmbientSamples record" inside the shared body (which fields feed which pool) is [?]; the units describe the flow only.

## 6. Case Stars (tag 6): joins 0x665b624 / 0x665c269 / 0x665c38a and cold range 0x665cf64..0x665d7e5
The three joins are the shared SKY-PUSH tail used by the Stars, Sky and SunMoon material paths (compiler-duplicated copies, see ext_particle_sky_callees.md).
| Phase | RVA range | What it does | Evidence |
|---|---|---|---|
| J3 | 0x665b624..0x665c269 | stores type byte [rbp+0x470]; first switch on byte [rbp+0x88] (0..3, table data_f2bf3c8) building the payload at [rbp+0x4A0..0x4B8]; second switch on byte [rbp+0x1A8] (table data_f2bf3d8): index 1 -> `jmp 0x665C269`, 2 -> `jmp 0x665C38A`; `0x665bb55..0x665bb64` pass-object get (0x9D0), zero 192 B; `0x665bd4a` stride-0x88 append | SK1 phases join-3 (1414 quoted lines, 5 mismatched/25 no-such mostly in 0x665bd31..0x665c272, redone by SK1b/SK1e: 694/694 and 65/65) |
| J1 | 0x665c269..0x665c38a | `[rbp+0x4B0]=cl`, `[rbp+0x4C8]=[rbp+0x230]`, `call 0x67B40D0`, `call 0x66A9AD0` (rcx=&[rbp+0x340]); `cmp byte [rbp+0x218],3` -> release of [rbp+0x210]; teardown loop over 0x28-stride array of type-2 entries (`cmp byte [rdi+0x18],2; rsi=[rdi+8]`) | SK1 ph.1-2 |
| J2 | 0x665c38a..0x665cf64 | `call 0x5ABA5C0`, zero 192 B, `lea rcx,[rax+0x780]; call 0x675F3B0`, pool 0x780 index `*0xFFFF8BA3`; u16 write to [rsi+0x8A8]; `call 0x675FB30`(rsi+0x648); `[rbp+0x1E0]=0x2001001`; stride-0x88 entry; byte pool +0x858; entry tag words `0x2003009`, `0x2027009`; stride-0x58 entry at +0x758 with growth/realloc (`0x7FFFFFFFFFFFFFFF` sentinel, alloc via [0x1233E1A8] vslot +8) | SK1 ph.3-6 + SK1c residual tail (0x665c276..0x665cf64, 1040/1040) |
| exit | 0x665cec1..0x665cf64 | `cmp byte [rbp+0xA8]`; teardown loops; `0x665cf64 mov rsi,[rbp+0x28]; jmp 0x665D124` | SK1 |
| cold | 0x665cf64..0x665d7e5 | out-of-line TLS-slot initialisers: `lea rcx,[data_129f9xxx]; call 0xE938CB0` / `cmp dword [data],0xFFFFFFFF` / `call 0x5668AC0 (name, flags)` / `call 0xE938D70`, with the string pairs "Stars"/"StarsForwardPBR" (0x665686f/0x6656868 refs; `[rbp+0x128]=5`, `[rbp+0x318]=0xF`), call-back jumps to 0x6656837/0x665685C/0x6656713; heap helper `0x665d43a` | SK1b/SK1c/SK1d (53/53) |
[SUPERSEDED, see 66560f0_sky_cases.md section 5: Stars reads +0x00 mesh, +0x08 StarsColor, +0x18 matrix, +0x58 u16 in the body 0x66585b4..0x6658cd3; +0x5A is not read] The Stars DESCRIPTION reads (+0x00 mesh, +0x18 matrix, +0x58 flags, +0x5A) occur in the Stars head/base draw (0x6656812.., 0x6658ffc..0x6659615) which no unit decoded: the Stars description layout is therefore NOT closed by these units [?]. The joins consume locals ([rbp+0x4E0..], [rbp+0x520], etc.), not description fields.

## 7. Cases not documented here
Celestial (tag 7, SunMoon material "SunMoonForwardPBR"/"SunMoon" at 0x6656585/0x665658c, body 0x665935d), Sky (tag 5, "Sky" 0x6656725, body 0x66574d8), EndSky body, Atmosphere (0x6656174 -> 0x6656d4b), Clouds/Weather tail jumps: no opencode unit; statement-level only in ext_particle_sky_callees.md.
Quoted reads in the shared body that match the Celestial layout (not attributed here): +0x28/+0x38/+0x48 vec4 (0x6659e5e/0x6659e69/0x6659e74), +0x58/+0x60 qword (0x6659e59/0x6659e87), +0x68 u16 (0x6659e9b), +0x6C (0x66597a8), +0x80 (0x6659dba).

## 8. Open questions
1. [CLOSED in 66560f0_sky_cases.md; 0x6658ffc is the EndSky tail] Stars head and base draw (description fields +0x00/+0x18/+0x58/+0x5A) have no instruction-complete decode.
2. Which cases enter the shared body at 0x6659615 / 0x665961f besides Cubemap (0x6656441, 0x665645c..0x6656497) is not enumerated; attributions of per-field reads inside it to Legacy/Celestial are [I].
3. Role of the count-tag call (sub_eea6040 with dl=0x4A) and of `[rbp+0x540]`.
4. Pass-object pool names (+0x150, +0x540, +0x750, +0x768, +0x858) are structural; the consumer is the 0xBB.. task bodies per oc_verification U-PASS3.
