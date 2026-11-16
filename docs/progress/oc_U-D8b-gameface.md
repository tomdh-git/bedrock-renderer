# UNIT U-D8b-gameface — Gameface extractor flag reads

## NEXT
Resume at: run `python tools/sigs/verify_oc.py docs/progress/oc_U-D8b-gameface.md` to validate all quoted `0xRVA  instr` lines; fix any mismatches; then the unit is done.

## Source & method
- Extractor: `0x66ade80..0x66b0ea5`, UI group tag 0. Listing: `docs/data/listings/gameface_66ade80_66b0eb0.txt` (2414 lines).
- Header (read only): `src\sdk\mc\deps\minecraft_renderer\framebuilder\Descriptions.h`, `RenderGameFaceDescription` lines 410-426, size 0x78. Only read offsets are certain; all field meanings are [?].
- Description register: `rsi = r8` arg (`0x66adec4  mov rsi,r8`). descscan2.py with reg r9 tracked nothing useful (UI visitor reg map says r9, but this extractor receives the desc in r8->rsi), so the listing was used as the authoritative source [V].
- Live capture `docs/data/live/gameface_extractor.txt`: header only, no sample data lines. [V live] not available.

## Description reads from rsi (the description object) [V listing]
| offset | width | RVA | mnemonic | notes |
|---|---|---|---|---|
| +0x00 | qword | 0x66ae25d | `mov eax,[rsi]` | mHead — jump-table switch index (FLAG 3) |
| +0x28 | addr | 0x66adf1b | `lea r8,[rsi+0x28]` | address passed to callee, not a read |
| +0x30 | qword | 0x66adf73 | `mov rcx,[rsi+0x30]` | mValue30 shared ref — gated by mByte38==1 |
| +0x38 | byte | 0x66adf1f | `movzx ecx,byte ptr [rsi+0x38]` | mByte38 FLAG (FLAG 1) |
| +0x40 | addr | 0x66ae0a7 | `lea r8,[rsi+0x40]` | address passed to callee, not a read |
| +0x48 | qword | 0x66ae0fc/109 | `mov rax,[rsi+0x48]` | mValue48 shared ref — gated by mByte50==1 |
| +0x50 | byte | 0x66ae0ab | `movzx eax,byte ptr [rsi+0x50]` | mByte50 FLAG (FLAG 2) |
| +0x58 | xmmword | 0x66ae227 | `movups xmm0,[rsi+0x58]` | mVec58 — unconditional |
| +0x68 | xmmword | 0x66ae232 | `movups xmm0,[rsi+0x68]` | mVec68 — unconditional |

All reads through registers loaded FROM a description field (pointer chasing) are NOT attributed to the description per the tool's rule; none appear here beyond the shared-ref addref chains on mValue30/mValue48.

## Scratch used by the flag paths [V listing]
- `[rbp+0x320]` = material pointer scratch; `[rbp+0x328]` = material ctrl/ref scratch.
- `[rbp+0x4E8]` = `[rdi+0x470]` context field (`0x66adeee  mov rcx,[rdi+0x470]` / `0x66adef5  mov [rbp+0x4E8],rcx`) [I: context+0x470].
- `0x55F0270(&[rbp+0x4E8], &[rbp+0x320])` — material helper; what it returns is not followed [I unknown].
- `0x67D6D70(rcx=r15=ctx+0x68, rdx=&[rbp+0x208], r8=perm, r9=desc)` — called after every mHead case; outputs material at `[rbp+0x208]` [I: material bind].
- `[rbp+0x530]` = blend mode 0..0xA computed from context bytes r14+4/+5/+6/+7 — NOT a description field.

## Material strings referenced from the extractor [V xref.py str]
| RVA in extractor | string RVA | string | used by |
|---|---|---|---|
| 0x66ae69a | 0xF2BE4C8 | "Gameface/Renoir" | mHead case 6 |
| 0x66ae4e7 | 0xF2BE4E8 | "Gameface/Path" | mHead case 7 |
| 0x66b0550 | 0xF5EBA2C | "Gameface/Standard" | cold >2 block (both bytes) |
| 0x66b070e | 0xF5A28D8 | "Gameface/Stencil" | cold block 0x66B060F+ |
| 0x66b062f | 0xF5AF3BF | "Gameface/StencilPath" | cold block 0x66B05B4+ |
| 0x66b0989 | 0xF5CA488 | "Gameface/StandardRare" | cold block 0x66B07CD+ |
| 0x66b0a68 | 0xF5FDA27 | "Gameface/ClearQuad" | cold block 0x66B0A48+ |
| 0x66b0c04 | 0xF51FB1A | "Gameface/TexturesWithColorMix" | cold block 0x66B090E+ |
| 0x66b00dd | 0xF7C8D0F | "Data_VS" | uniform (0x66b00dd) |
| 0x66b0066 | 0xF7C9168 | "Data_PS" | uniform (0x66b0066) |

## Per-flag detail

### FLAG 1 — mByte38 at description +0x38 (RVA 0x66adf1f)

`0x66adf1f  movzx ecx,byte ptr [rsi+0x38]` loads the flag byte.
`0x66adf23  cmp ecx,1` compares it with 1.
`0x66adf2c  jg short 0x66ADF3E` branches when value > 1.

Branch A (jg, taken target = 0x66ADF3E, first 6 instructions):
```
0x66adf3e  cmp ecx,2
0x66adf41  jne 0x66B0524
0x66adf47  lea rcx,[rbp+0x4E8]
0x66adf4e  lea rdx,[rbp+0x320]
0x66adf55  call 0x55F0270
0x66adf5a  nop
```
Then `0x66adf5b  jmp 0x66AE000`. Effect (value == 2): `[rbp+0x320]` = result of `0x55F0270(context+0x4E8)` — a material chosen by the helper [I unknown which material]. Branch A fall-through (value <= 1) continues at `0x66adf2e`.

Branch A cold-target `0x66B0524` (value > 2):
```
0x66b0524  call 0x1166E0
0x66b0529  nop
0x66b052a  call 0x1166E0
0x66b052f  nop
0x66b0530  lea rcx,[0x129F8D40]
0x66b0537  call 0xE938CB0
```
... leading to `0x66b0550  lea rdx,[0xF5EBA2C]` = "Gameface/Standard" then `jmp 0x66AE29E`. Effect (value > 2): material "Gameface/Standard" [V xref].

Branch B (`0x66adf2e  test ecx,ecx`, taken target = 0x66ADF60 when value == 1, first 6 instructions):
```
0x66adf60  movaps [rbp+0x320],xmm0
0x66adf67  mov rcx,[r8]              ; r8 = [rsi+0x28]
0x66adf6a  test rcx,rcx
0x66adf6d  je short 0x66ADF73
0x66adf6f  movzx ecx,word ptr [rcx+0x10]
0x66adf73  mov rcx,[rsi+0x30]        ; READ mValue30 shared ref
```
Then shared-ref addref chain; `[rbp+0x328]` = mValue30 ptr, `[rbp+0x320]` = `[r8]` = `[rsi+0x28]` [V]. Effect (value == 1): mValue30 shared ref becomes the material [V].

Branch B fall-through (value == 0), first 6 instructions from 0x66adf32:
```
0x66adf32  movaps [rbp+0x320],xmm0   ; zero [rbp+0x320]
0x66adf39  jmp 0x66ADFD0
0x66adf3e  cmp ecx,2                 ; (next block, only reached via the >1 path)
...
```
Effect (value == 0): `[rbp+0x320]` = 0 (no material); `[rbp+0x328]` is not updated in this path [V].

**Summary FLAG 1:** mByte38 selects the material source: 0 -> none ([rbp+0x320]=0), 1 -> mValue30 shared ref + [rbp+0x320]=[rsi+0x28], 2 -> `0x55F0270(context+0x4E8)` result, >2 -> "Gameface/Standard". Writes `[rbp+0x320]`/`[rbp+0x328]` scratch that feeds `0x67D6D70`.
Suggested name: `mMaterialSlot0` [I] — effect clear (material selector), exact per-value semantics inferred from scratch usage.

### FLAG 2 — mByte50 at description +0x50 (RVA 0x66ae0ab)

`0x66ae0ab  movzx eax,byte ptr [rsi+0x50]` loads the flag byte.
`0x66ae0af  cmp eax,1` compares it with 1.
`0x66ae0b2  jg short 0x66AE0C7` branches when value > 1.

Branch A (jg, taken target = 0x66AE0C7, first 6 instructions):
```
0x66ae0c7  cmp eax,2
0x66ae0ca  jne 0x66B052A
0x66ae0d0  lea rcx,[rbp+0x4E8]
0x66ae0d7  lea rdx,[rbp+0x320]
0x66ae0de  call 0x55F0270
0x66ae0e3  nop
```
Then `0x66ae0e4  jmp 0x66AE189`. Effect (value == 2): `[rbp+0x320]` = `0x55F0270(context+0x4E8)` [I unknown material]. Branch A fall-through (<=1) continues at `0x66ae0b4`.

Branch A cold-target `0x66B052A` (value > 2): identical code to `0x66B0524` (`call 0x1166E0` x2, then same version-check chain) leading to `0x66b0550  lea rdx,[0xF5EBA2C]` = "Gameface/Standard", `jmp 0x66AE29E`. Effect (value > 2): material "Gameface/Standard" [V xref].

Branch B (`0x66ae0b7  test eax,eax`, taken target = 0x66AE0E9 when value == 1, first 6 instructions):
```
0x66ae0e9  movaps [rbp+0x320],xmm0
0x66ae0f0  mov rax,[r8]              ; r8 = [rsi+0x40]
0x66ae0f3  test rax,rax
0x66ae0f6  je short 0x66AE0FC
0x66ae0f8  movzx eax,word ptr [rax+0x10]
0x66ae0fc  mov rax,[rsi+0x48]        ; READ mValue48 shared ref
```
Then shared-ref addref chain; `[rbp+0x328]` = mValue48 ptr, `[rbp+0x320]` = `[r8]` = `[rsi+0x40]` [V]. Effect (value == 1): mValue48 shared ref becomes the material [V].

Branch B fall-through (value == 0), first 6 instructions from 0x66ae0bb:
```
0x66ae0bb  movaps [rbp+0x320],xmm0   ; zero [rbp+0x320]
0x66ae0c2  jmp 0x66AE159
...
```
Effect (value == 0): `[rbp+0x320]` = 0 (no material) [V].

**Summary FLAG 2:** mByte50 selects the material source identically to FLAG 1 but on mValue48: 0 -> none, 1 -> mValue48 shared ref + [rbp+0x320]=[rsi+0x40], 2 -> `0x55F0270(context+0x4E8)`, >2 -> "Gameface/Standard". Overwrites the same `[rbp+0x320]`/`[rbp+0x328]` scratch, so FLAG 2's result takes precedence over FLAG 1's [I: same scratch].
Suggested name: `mMaterialSlot1` [I] — effect clear (material selector).

### FLAG 3 — mHead at description +0x00 (qword switch index, RVA 0x66ae25d)

`0x66ae25d  mov eax,[rsi]` loads the mHead qword.
`0x66ae25f  cmp rax,8` compares it with 8.
`0x66ae263  ja 0x66AE77A` branches when mHead > 8 (default case).

Taken target `0x66AE77A` (default, first 6 instructions):
```
0x66ae77a  xor ebx,ebx
0x66ae77c  xor esi,esi
0x66ae77e  mov r14,[rbp+0x520]
0x66ae785  jmp 0x66AEA14
0x66ae78a  lea rax,[0x129F8E20]       ; (7th instr, at 0x66AEA14 join)
0x66ae791  mov rcx,[0x129F8E30]
```
Effect (mHead > 8): default path; `[rbp+0x520]` (=rsi, the desc ptr) preserved in r14; no material string loaded here — the join at 0x66AEA14 loads material buffer `0x129F8E20`/`0x129F8E30` [V].

Fall-through (mHead <= 8), first 6 instructions from 0x66ae269:
```
0x66ae269  lea rcx,[0xF2BF8A8]        ; jump-table base
0x66ae270  movsxd rax,[rcx+rax*4]     ; case offset
0x66ae274  add rax,rcx
0x66ae277  jmp rax                     ; indirect jump to case
```
Jump table at `0xF2BF8A8`, 9 entries decoded [V]:
- case 0 -> 0x66ae279, case 1 -> 0x66ae53e, case 2 -> 0x66ae38b, case 3 -> 0x66ae414, case 4 -> 0x66ae302, case 5 -> 0x66ae5c7, case 6 -> 0x66ae650, case 7 -> 0x66ae49d, case 8 -> 0x66ae6f1.

Each case checks its own global version trio, then sets `[rbp+0x320]`/`[rbp+0x328]` to a material buffer and `r8` to a case-specific perm string, then calls `0x67D6D70`. Two cases load a literal material string directly [V xref]:
- Case 6 (0x66ae69a): `lea rax,[0xF2BE4C8]` = "Gameface/Renoir", `[rbp+0x328]=0xF`, perm=0x129F8EA0 [V].
- Case 7 (0x66ae4e7): `lea rax,[0xF2BE4E8]` = "Gameface/Path", `[rbp+0x328]=0xD`, perm=0x129F8EB8 [V].
- Cases 0-5, 8: material from runtime buffer globals (`0x129F8D20`/`0x129F8D60`/…/`0x129F8ED0`) + perm string (`0x129F8D48`/`88`/`C8`/`08`/`48`/`88`/`A0`) [I: perm meaning unknown].

**Summary FLAG 3:** mHead is a 9-way material/permutation selector via jump table. Cases 6/7 bind literal "Gameface/Renoir" / "Gameface/Path"; other cases bind runtime-resolved material buffers with case-specific perms.
Suggested name: `mMaterialIndex` [I] — effect clear (material selector via switch).

## UNVERIFIED items
- `[UNVERIFIED: 0x55F0270 what material does it return?]` — `0x55F0270(&[rbp+0x4E8], &[rbp+0x320])` is called for byte==2 in both FLAG 1 and FLAG 2; the returned material is not followed in this listing.
- `[UNVERIFIED: 0x67D6D70 how does it use [rbp+0x320]/[rbp+0x328]?]` — the material bind call; not confirmed it reads the scratch.
- `[UNVERIFIED: perm string meanings 0x129F8D48/88/C8/08/48/88/A0]` — case-specific perm globals, not resolved to strings.
- `[UNVERIFIED: mVec58 (+0x58) and mVec68 (+0x68) usage]` — read unconditionally into `[rbp+0x2F0]`/`[rbp+0x300]`; downstream consumer not traced.
- `[UNVERIFIED: mValue30 (+0x30) / mValue48 (+0x48) shared-ref target type]` — addref chain confirms shared_ref but the pointed-to type is unknown.
- `[UNVERIFIED: mHead default case material]` — mHead>8 path joins at 0x66AEA14 which loads buffer `0x129F8E20`; not confirmed as a specific material name.

## Philosophy compliance
- Loaded: code-philosophy (5 laws). Applied: Early Exit (guard clauses on flag values), Fail Fast (invalid mHead>8 goes to default; `ja` handles out-of-range), Intentional Naming (suggested names tagged [I]).
- Note: this is reverse-engineered disassembly, not source I authored; the 5 laws are applied to the *naming/documentation* of recovered fields, not to rewriting the exe.
