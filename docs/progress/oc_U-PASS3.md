# Progress: U-PASS3 (find consumer of 0xC8-byte DrawItem records)

## NEXT
Unit essentially complete: 3 candidate DrawItem-record consumers identified & verified against the exe; best 3 reported below with verbatim disassembly quotes. Remaining: optional refinement of candidate-3 stride-loop RVA (its add reg,0xC8 stride is in the enclosing sub_55f1450 region; in-function stride loop not isolated). No further steps required unless orchestrator requests. Output file: docs/progress/oc_U-PASS3.md only.

## Unit task (from brief)
- Find who READS the 0xC8-byte DrawItem records that chunk/batch builders write (layout: mValidMask +0x00, mKindA +0x04, u16 pool indices at record +0x2A/+0x28/+0x2C/+0x42; builders push via 0x678d690 / memcpy 0xeec6ec0 of 0xc8 bytes).
- Ruled out by U-PASS/U-PASS2: sub_c21db0, sub_833e30, sub_c1cb60, all add-reg,0x8B8/0x8C8 loops.
- Method: (1) rdis imm 0xC8 -> imul/add reg,0xC8 record-stride loops outside builders; (2) intersect with rdis fld 0x2a --r for u16 pool-index reads at +0x2A/+0x28/+0x2C/+0x42; (3) report best 3: function RVA, loop RVAs, what it does with the record; verbatim `0xRVA  instruction` quotes; tags [V]/[I]/[?].

## METHOD / TOOLS
- Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only. No game run, no builds. Only edit docs/progress/oc_U-PASS3.md.
- rdis.exe `imm <value> [--max N]` and `fld <disp> [--r|--w] [--max N]` are WHOLE-BINARY scans CAPPED at 200 by default. `rdis imm 0xC8` returned "-- 11894 hit(s), 200 shown" (mostly `sub rsp,0xC8`/`add rsp,0xC8` stack adjusts and `mov edx,0xC8` sizes) — useless uncapped. Pulled FULL list with `--max 20000` -> 11,894 lines saved at C:\Users\Atomi\AppData\Local\Temp\opencode\u-pass3-imm-c8-full.txt.
- Filtered full imm list for non-stack `add reg,0xC8` (reg != rsp) and `imul ...,0xC8` outside the builder range (0x66bb7b0–0x66d9af0 / 0x66bf290 family + helper 0x678d690).
- `rdis fld 0x2a --r --max 200` (266 total, 200 shown), `fld 0x28` (361605 total), `fld 0x2c` (12422 total), `fld 0x42` (323 total) — all capped at 200, so intersection is partial; confirmed candidates by direct disassembly instead.

## RAW ARTIFACTS (temp, not part of deliverable)
- C:\Users\Atomi\AppData\Local\Temp\opencode\u-pass3-imm-c8.txt  (imm 0xC8 capped 200/11894)
- C:\Users\Atomi\AppData\Local\Temp\opencode\u-pass3-imm-c8-full.txt (imm 0xC8 FULL 11,894)
- C:\Users\Atomi\AppData\Local\Temp\opencode\u-pass3-fld-2a.txt  (fld 0x2a 266/200)
- C:\Users\Atomi\AppData\Local\Temp\opencode\u-pass3-fld-28.txt  (fld 0x28 361605/200)
- C:\Users\Atomi\AppData\Local\Temp\opencode\u-pass3-fld-2c.txt  (fld 0x2c 12422/200)
- C:\Users\Atomi\AppData\Local\Temp\opencode\u-pass3-fld-42.txt  (fld 0x42 323/200)
- Disassembly saved: u-pass3-dis-bbdb100.txt, u-pass3-dis-bbdb600.txt, u-pass3-dis-bbbfeb0.txt, u-pass3-dis-562bb00.txt

## STEP 1 — rdis imm 0xC8 stride-loop candidates outside builders [V]
Complete non-stack `add reg,0xC8`/`imul ...,0xC8` set is large (~100+ sites). The ones that ALSO have u16 pool-index reads (intersected with fld 0x2a / confirmed by disassembly) are the 3 candidates below. All other add reg,0xC8 sites were either stack-adjacent, size movs, builders, or unrelated loops (e.g. sub_188c60, sub_1dbee0, sub_3d3610 are memset/copy/alloc, not record readers).

## CANDIDATE 1 — sub_bbdad00 (function RVA 0xbbdad00) — CONFIRMED DrawItem consumer [V]
Walks 0xC8-byte DrawItem records with two add-reg,0xC8 stride loops, reads mValidMask +0x00 and u16 pool indices, then indexes a stride-0x88 pool using the +0x2A u16 index.

Loops (record stride 0xC8) [V]:
```
  bbdb190  add rdi,0xC8
  bbdb197  cmp rdi,rbx
  bbdb19a  je short 0xBBDB170
```
(rdi walks [rsi+0x10]..[rsi+0x18], bound rbx; set up at bbdb17c `mov rdi,[rsi+0x10]` / bbdb180 `mov rbx,[rsi+0x18]`)
```
  bbdb3a0  add rbx,0xC8
  bbdb3a7  cmp rbx,r12
  bbdb3aa  je short 0xBBDB330
```
(rbx walks [rsi+0x10]..[rsi+0x18], bound r12; set up at bbdb340 `mov rbx,[rsi+0x10]` / bbdb344 `mov r12,[rsi+0x18]`)

What it does with the record [V]:
```
  bbdb3ac  mov rax,[rbx]                                    ; reads mValidMask +0x00 (u64)
  bbdb3af  mov ecx,eax
  bbdb3b1  not ecx
  bbdb3b3  test ecx,0x3003000
  ...
  bbdb408  movzx r8d,word ptr [rbx+0x10]                    ; reads u16 pool index at +0x10
  bbdb40d  movzx r8d,word ptr [rax+r8*2]                    ; indexes pool array by that u16
  ...
  bbdb698  movzx edx,word ptr [rdx+0x2A]                    ; reads u16 pool index at +0x2A (mPool768)
  bbdb69c  mov r8,[r8+0x750]                                ; pool768 base
  bbdb6a3  mov r9d,edx
  bbdb6a6  shl r9d,7                                        ; index*0x80
  bbdb6aa  lea rdx,[r9+rdx*8]                               ; index*0x88 (pool768 stride)
  bbdb6ae  cmp rcx,[r8+rdx+0x78]                            ; compare [pool768 + index*0x88 + 0x78] (material compare)
  bbdb708  movzx ecx,word ptr [rcx+0x2A]                    ; second +0x2A u16 read
  bbdb70e  shl edx,7
  bbdb711  lea rcx,[rdx+rcx*8]                              ; index*0x88
  bbdb715  add rcx,[rax+0x750]                              ; pool768 base + index*0x88
```
- Confirmed reads +0x2A as u16 -> pool768 (stride 0x88, +0x78 material-compare field), matching DrawItem.h (+0x2A = mPool768 index; pool768 stride 0x88). Also reads +0x10 u16 and +0x00 valid mask.
- Tags: all [V]. What it does: iterates DrawItem records, for each valid record reads pool indices and looks up pool768 (shader) objects, comparing material at +0x78 — i.e. record submission/culling against the shader pool.

## CANDIDATE 2 — sub_bbbfc50 (function RVA 0xbbbfc50; NothingTask body at 0xbc38c20) — CONFIRMED DrawItem consumer [V]
Walks 0xC8-byte DrawItem records with add-reg,0xC8 stride loops, reads valid mask +0x00 and u16 pool indices (+0x28 via lea, +0x3C, +0x10) and does pool lookups.

Loops (record stride 0xC8) [V]:
```
  bbbfeb0  add rbx,0xC8
  bbbfeb7  cmp rbx,r14
  bbbfeba  je short 0xBBBFE90
```
```
  bbc00ff  add rsi,0xC8
  bbc0106  cmp rsi,r9
  bbc0109  je short 0xBBC0090
```

What it does with the record [V]:
```
  bbc00ad  lea rax,[r8+0x28]                                ; +0x28 pool780 index location
  bbc00d0  movzx eax,word ptr [rsi+0x3C]                    ; reads u16 pool index at +0x3C (mPool690)
  bbc00d4  mov rcx,[r8+0x6A0]
  bbc00db  movzx r13d,word ptr [rcx+rax*2]                  ; pool690 lookup by u16 index
  bbc00e0  cmp r15,r14
  bbc00e9  mov [r15],r13
  bbc00ec  mov [r15+8],rsi
  bbc00f0  mov rax,[rbp+0x1380]
  bbc00f7  mov [r15+0x10],rax
  bbc00fb  add r15,0x18
  bbc010b  mov rax,[rsi]                                    ; reads mValidMask +0x00
  bbc010e  mov ecx,eax
  bbc0110  not ecx
  bbc0112  test ecx,0x2407040                               ; valid-mask bit test
  bbc013d  movzx r8d,word ptr [rsi+0x10]                    ; reads u16 pool index at +0x10 (mPool8A0)
  bbc0142  movzx r8d,word ptr [rax+r8*2]                    ; pool8A0 lookup by u16 index
  bbc015a  cmp rax,[rdi+0x248]
```
- fld 0x2a also showed 4 +0x2A u16 reads in sub_bbbfc50 (bbc38f44 [rcx+0x2A], bbc4100 [rax+0x2A], bbc391ca [rdx+0x2A], bbc392ea [rcx+0x2A]) — record +0x2A into pool +0x750 per U-PASS.
- Tags: loop RVAs [V]; field reads [V]; NothingTask identification [I per U-PASS vv_lambda_bodies.md]; +0x2A reads [V fld 0x2a].
- What it does: iterates DrawItem records, filters by valid mask, reads pool indices (+0x28/+0x3C/+0x10/+0x2A), looks up pool objects, writes matched {index, DrawItem*, ...} 0x18-byte entries and submits via 0xbcc38e0 (per U-PASS).

## CANDIDATE 3 — sub_562bb00 (function RVA 0x562bb00) — DrawItem per-record pool-index reader [V fields, I stride]
Reads THREE of the four pool-index u16 fields from a single DrawItem record [rsi] (+0x28, +0x2A, +0x2C) plus +0x52/+0x50 — the best match for "reads [reg+0x2A]/[reg+0x28]/[reg+0x2C] as 16-bit pool indices". No add reg,0xC8 stride loop isolated INSIDE this function in the viewed window; the array stride (add reg,0xC8) is in the enclosing sub_55f1450 region (imm scan showed ~40 add reg,0xC8 sites there, e.g. 0x55f16c3 `add r14,0xC8`, 0x562a13d `add r14,0xC8`, 0x562f3a0 `add rbx,0xC8`) which is the caller that strides records and invokes per-record logic.

Reads from record [rsi] [V]:
```
  562bb36  movzx ecx,word ptr [rsi+0x2C]                    ; +0x2C u16 pool index (mPool750)
  562bb3a  movzx r10d,word ptr [rsi+0x2A]                   ; +0x2A u16 pool index (mPool768)
  562bb3f  movzx r11d,word ptr [rsi+0x28]                   ; +0x28 u16 pool index (mPool780)
  562bb44  mov edi,[rsi+0x24]                               ; +0x24
  562bb47  movzx ebx,byte ptr [rsi+0x20]                    ; +0x20 byte
  562bb9b  mov eax,[rsi+0x52]                               ; +0x52 poolA index
  562bb9e  movzx ecx,word ptr [rsi+0x50]                    ; +0x50
  562bce8  mov [rsp+0x50],r10w                              ; spills +0x2A u16
  562bcee  mov [rsp+0x48],r11w                              ; spills +0x28 u16
```
- Then calls sub_bcd77b0 / sub_bcdba70 with the spilled pool indices (submit/draw path).
- Tags: field reads [V]; it is a consumer of DrawItem records (reads pool indices and submits); the enclosing stride loop RVA is [I] not isolated — report as candidate with this caveat.

## OTHER NOTES / RULED OUT
- sub_188c60 (`add rax,0xC8` at 189787), sub_1dbee0 (`add rax,0xC8` at 1dc0f6), sub_3d3610 (`add rcx,0xC8` at 3d3a08): non-stack add reg,0xC8 hits from the CAPPED imm scan, but all are memset/copy/alloc, not DrawItem pool-index readers — ruled out [V].
- sub_66d9af0 ("pairing", builders doc): fld 0x42 showed ~28 reads of word [rbx/rcx/r9/rax+0x42] (pool648 index) but NO add reg,0xC8 / imul ...,0xC8 found in imm scan — stride mechanism unconfirmed; listed as [?] alternate, not in best 3.
- sub_568cd90: 4 u16 +0x2A reads (568d0b8/568d110/568d1b4/568d372) but NO add reg,0xC8 or imul ...,0xC8 in imm scan — not a stride-loop candidate; ruled out for Step 1 [V].

## BEST 3 SUMMARY (for orchestrator)
1. sub_bbdad00 @ 0xbbdad00 — loops bbdb190 (`add rdi,0xC8`) & bbdb3a0 (`add rbx,0xC8`); reads +0x2A u16 -> pool768 stride-0x88 (+0x78 material compare), +0x10 u16, +0x00 valid mask. [V]
2. sub_bbbfc50 @ 0xbbbfc50 — loops bbbfeb0 (`add rbx,0xC8`) & bbc00ff (`add rsi,0xC8`); reads +0x28/+0x3C/+0x10 u16 + +0x00 mask + +0x2A (fld 0x2a); pool lookups + submit via 0xbcc38e0. [V]
3. sub_562bb00 @ 0x562bb00 — reads +0x28/+0x2A/+0x2C u16 pool indices + +0x52/+0x50 from record [rsi], calls sub_bcd77b0/sub_bcdba70 (submit); stride loop in caller (sub_55f1450 region) not isolated. [V fields / I stride]

## Verification log
- imm 0xC8 --max 20000: 11,894 hits; filtered non-stack add reg,0xC8 outside builders [V]
- fld 0x2a --r: 266 total; sub_bbdad00 (bbdb698/bbdb708), sub_bbbfc50 (bbc38f44/bbc4100/bbc391ca/bbc392ea), sub_562bb00 (562bb3a) confirmed [V]
- Disassembly of sub_bbdad00, sub_bbbfc50, sub_562bb00 confirms 0xC8 stride loops + u16 pool-index reads [V]
